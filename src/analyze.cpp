/*
 * PDF Tools.
 * Copyright (C) 2012-2016 Leonardo Alves da Costa
 * mailto:leonhad AT gmail DOT com
 *
 * PDF Tools is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * PDF Tools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#include "analyze.h"
#include "utils.h"
#include "parser/scanner.h"
#include "parser/parser.h"
#include "parser/pageparser.h"
#include "pageanalyze.h"
#include "parser/cmapparser.h"
#include "nodes/nodes.h"
#include "semantic/document.h"
#include "semantic/outline.h"
#include "semantic/font.h"
#include "semantic/page.h"
#include "semantic/pagelabel.h"
#include <iostream>
#include "genericexception.h"

using namespace std;
using namespace parser;
using namespace node;

Analyze::Analyze(const string &filein) throw(exception) : m_filein(filein)
{
    m_filestream.open(filein, ios::binary);

    if (!m_filestream.is_open())
    {
        string message{"Invalid input file name: "};
        message += filein;
        throw GenericException(message);
    }
}

Analyze::~Analyze()
{
    if (m_filestream.is_open())
    {
        m_filestream.close();
    }
}

void Analyze::analyzeXref()
{
    size_t size = m_tree->size();

    for (size_t i = 0; i < size; i++)
    {
        TreeNode *value = m_tree->get(i);
        XREFNode *xref = dynamic_cast<XREFNode *> (value);
        if (xref)
        {
            MapNode *trailer = dynamic_cast<MapNode *> (xref->trailer());

            TreeNode *rootValue = getRealValue(trailer->get("/Root"));
            TreeNode *encrypt = getRealValue(trailer->get("/Encrypt"));
            TreeNode *info = getRealValue(trailer->get("/Info"));
            if (rootValue)
            {
                m_document->setRoot(rootValue);
            }

            if (info)
            {
                m_document->setInfo(info);
            }

            if (encrypt)
            {
                m_document->setEncrypted(true);
            }

            ArrayNode *array = dynamic_cast<ArrayNode *> (trailer->get("/ID"));
            if (array && array->size() == 2)
            {
                string first = getStringValue(array->value(0));
                string second = getStringValue(array->value(1));
                m_document->setId(first, second);
            }
        }
        else
        {
            ObjNode *obj = dynamic_cast<ObjNode *> (value);
            if (obj)
            {
                MapNode *values = dynamic_cast<MapNode *> (obj->value());
                if (values)
                {
                    NameNode *type = dynamic_cast<NameNode *> (values->get("/Type"));
                    // analyze only XREF Objects
                    if (type && type->name() == "/XRef")
                    {
                        TreeNode *rootValue = getRealValue(values->get("/Root"));
                        TreeNode *info = getRealValue(values->get("/Info"));
                        if (rootValue)
                        {
                            m_document->setRoot(rootValue);
                        }

                        if (info)
                        {
                            m_document->setInfo(info);
                        }

                        ArrayNode *array = dynamic_cast<ArrayNode *> (values->get("/ID"));
                        if (array && array->size() == 2)
                        {
                            string first = getStringValue(array->value(0));
                            string second = getStringValue(array->value(1));
                            m_document->setId(first, second);
                        }
                    }
                }
            }
        }
    }
}

void Analyze::analyzeInfo()
{
    ObjNode *obj = dynamic_cast<ObjNode *> (m_document->infoNode());
    if (obj)
    {
        MapNode *info = dynamic_cast<MapNode *> (obj->value());
        if (info)
        {
            m_document->setTitle(getStringValue(info->get("/Title")));
            m_document->setAuthor(getStringValue(info->get("/Author")));
            m_document->setSubject(getStringValue(info->get("/Subject")));
        }
    }
}

void Analyze::analyzeRoot()
{
    ObjNode *obj_root = dynamic_cast<ObjNode *> (m_document->rootNode());
    if (!obj_root)
    {
        // Invalid file
        return;
    }

    MapNode *catalog = dynamic_cast<MapNode *> (obj_root->value());
    NameNode *name = dynamic_cast<NameNode *> (catalog->get("/Type"));
    if (!name || name->name() != "/Catalog")
    {
        // Invalid file
        return;
    }
    m_page_tree = getRealValue(catalog->get("/Pages"));
    m_document->setLang(getStringValue(catalog->get("/Lang")));

    MapNode *names = dynamic_cast<MapNode *> (getRealObjValue(catalog->get("/Names")));
    if (names)
    {
        MapNode *dests = dynamic_cast<MapNode *> (getRealObjValue(names->get("/Dests")));
        analyzeNames(dests);
    }

    MapNode *page_labels = dynamic_cast<MapNode *> (getRealObjValue(catalog->get("/PageLabels")));
    if (page_labels)
    {
        ArrayNode *array = dynamic_cast<ArrayNode *> (getRealValue(page_labels->get("/Nums")));
        if (array)
        {
            size_t size = array->size();

            for (size_t loop = 0; loop < size; loop += 2)
            {
                double page = getNumberValue(array->value(loop));
                MapNode *attributes = dynamic_cast<MapNode *> (getRealObjValue(array->value(loop + 1)));
                if (attributes)
                {
                    NameNode *name_type = dynamic_cast<NameNode *> (attributes->get("/S"));
                    page_type type = ARABIC;
                    if (name_type)
                    {
                        if (name_type->name() == "D")
                        {
                            type = ARABIC;
                        }
                        else if (name_type->name() == "R")
                        {
                            type = UPCASE_ROMAN;
                        }
                        else if (name_type->name() == "r")
                        {
                            type = LOWCASE_ROMAN;
                        }
                        else if (name_type->name() == "A")
                        {
                            type = UPCASE_LETTERS;
                        }
                        else if (name_type->name() == "a")
                        {
                            type = LOWCASE_LETTERS;
                        }
                    }
                    string newName = getStringValue(attributes->get("/P"));
                    int range = getNumberValue(attributes->get("/St"), 1);
                    m_document->addPageLabel(new PageLabel(page, range, type, newName));
                }
            }
        }
    }

    MapNode *outlines = dynamic_cast<MapNode *> (getRealObjValue(catalog->get("/Outlines")));
    if (outlines)
    {
        analyzeOutlines(outlines);
    }

    TreeNode *tree_root = catalog->get("/StructTreeRoot");
    if (tree_root)
    {
        m_document->setTreeRoot(true);
    }
}

void Analyze::analyzeNames(MapNode *values)
{
    ArrayNode *kids = dynamic_cast<ArrayNode *> (values->get("/Kids"));
    if (kids)
    {
        size_t size = kids->size();

        for (size_t i = 0; i < size; i++)
        {
            MapNode *map_kids = dynamic_cast<MapNode *> (getRealObjValue(kids->value(i)));
            analyzeNames(map_kids);
        }
    }
    else
    {
        ArrayNode *names = dynamic_cast<ArrayNode *> (values->get("/Names"));
        if (names)
        {
            size_t size = names->size();

            for (size_t i = 0; i < size; i += 2)
            {
                string name = getStringValue(names->value(i));
                m_names[name] = names->value(i + 1);
            }
        }
    }
}

TreeNode *Analyze::getNamedValue(string name)
{
    try
    {
        return m_names.at(name);
    }
    catch (out_of_range &)
    {
        return nullptr;
    }
}

void Analyze::analyzeOutlines(MapNode *values, Outline *parent)
{
    NameNode *type = dynamic_cast<NameNode *> (values->get("/Type"));
    if (type && type->name() != "/Outlines")
    {
        error_message("Invalid outlines");
        return;
    }

    Outline *outline = new Outline;
    string named_dest = getStringValue(values->get("/Dest"));
    if (!named_dest.empty())
    {
        MapNode *map = dynamic_cast<MapNode *> (getRealObjValue(getNamedValue(named_dest)));
        if (map)
        {
            ArrayNode *dest = dynamic_cast<ArrayNode *> (getRealObjValue(map->get("/D")));
            analyzeOutline(dest, outline);
        }
    }

    ArrayNode *destinations = dynamic_cast<ArrayNode *> (values->get("/Dest"));
    if (destinations && destinations->size() > 0)
    {
        analyzeOutline(destinations, outline);
    }
    else
    {
        MapNode *actions = dynamic_cast<MapNode *> (getRealObjValue(values->get("/A")));
        if (actions)
        {
            NameNode *subtype = dynamic_cast<NameNode *> (getRealObjValue(actions->get("/S")));
            if (subtype && subtype->name() == "/GoTo")
            {
                ArrayNode *dest = dynamic_cast<ArrayNode *> (getRealObjValue(actions->get("/D")));
                analyzeOutline(dest, outline);
            }
        }
    }

    outline->set_title(getStringValue(values->get("/Title")));

    if (!parent)
    {
        // root node
        m_document->setOutline(outline);
    }
    else
    {
        if (parent)
        {
            parent->add_child(outline);
        }
    }

    MapNode *first = dynamic_cast<MapNode *> (getRealObjValue(values->get("/First")));
    if (first)
    {
        analyzeOutlines(first, outline);
    }

    MapNode *next = dynamic_cast<MapNode *> (getRealObjValue(values->get("/Next")));
    if (next && parent)
    {
        analyzeOutlines(next, parent);
    }
}

void Analyze::analyzeOutline(ArrayNode *values, Outline *outline)
{
    if (values && values->size() > 0)
    {
        RefNode *ref = dynamic_cast<RefNode *> (values->value(0));
        if (ref)
        {
            outline->set_destination(ref->id(), ref->generation());
        }

        NameNode *command = dynamic_cast<NameNode *> (values->value(1));
        if (command && command->name() == "/XYZ")
        {
            double x = getNumberValue(values->value(2));
            double y = getNumberValue(values->value(3));
            outline->set_location(x, y);
        }
    }
}

Document *Analyze::analyzeTree() throw(exception)
{
    verbose_message("Parsing file " + m_filein);

    Parser parser(&m_filestream);

    m_tree = parser.parse();
    if (!m_tree)
    {
        // Invalid tree
        return nullptr;
    }
    m_document = new Document;

    analyzeXref();
    analyzeInfo();
    if (m_document->encrypted())
    {
        throw GenericException("Encrypted file is not supported.");
    }
    else
    {
        analyzeRoot();
        analyzePages(m_page_tree);
        return m_document;
    }
}

Page *Analyze::processPage(int id, int generation, stringstream *stream_value, MapNode *catalog, ArrayNode *)
{
    Page *page = new Page(m_document);
    page->set_destination(id, generation);

    MapNode *resources = dynamic_cast<MapNode *> (getRealObjValue(catalog->get("/Resources")));
    if (resources)
    {
        MapNode *fonts = dynamic_cast<MapNode *> (getRealObjValue(resources->get("/Font")));
        if (fonts)
        {
            vector<string> names = fonts->names();
            size_t size = names.size();
            for (size_t loop = 0; loop < size; loop++)
            {
                string alias = names[loop];
                MapNode *fontmap = dynamic_cast<MapNode *> (getRealObjValue(fonts->get(alias)));
                if (fontmap)
                {
                    Font *font = analyzeFont(fontmap);
                    page->add_fontmap(alias, font->name());
                }
            }
        }
    }

    stream_value->seekg(0);
    PageParser parser(stream_value);
    RootNode *root = parser.parse();

    PageAnalyze analyze(m_document);
    page->set_root(analyze.analyze_tree(root));

    return page;
}

Font *Analyze::analyzeFont(MapNode *fontmap)
{
    Font *font = new Font;

    font->set_name("Unnamed");
    MapNode *descriptor = dynamic_cast<MapNode *> (getRealObjValue(fontmap->get("/FontDescriptor")));
    if (descriptor)
    {
        NameNode *name = dynamic_cast<NameNode *> (descriptor->get("/FontName"));
        if (name)
        {
            font->set_name(name->name());
        }
    }

    Font *from_document = m_document->font(font->name().c_str());
    if (from_document)
    {
        delete font;
        return from_document;
    }
    else
    {
        m_document->addFont(font);
    }

    if (descriptor)
    {
        int flags = getNumberValue(getRealObjValue(descriptor->get("/Flags")));
        if (flags & 1)
        {
            font->set_fixed(true);
        }

        if (flags & 64)
        {
            font->set_italic(true);
        }
    }

    ObjNode *to_unicode = dynamic_cast<ObjNode *> (getRealValue(fontmap->get("/ToUnicode")));
    if (to_unicode)
    {
        stringstream stream;
        getStream(to_unicode, &stream);

        stream.seekg(0);
        CMapParser parser(&stream);
        CMapNode *root = parser.parse();

        if (root)
        {
            CodeSpaceNode *codespace = root->codeSpace();
            if (codespace)
            {
                font->set_charmap_start(codespace->start());
                font->set_charmap_finish(codespace->finish());
            }

            size_t size = root->nodes();
            for (size_t loop = 0; loop < size; loop++)
            {
                CharNode *cnode = root->node(loop);
                font->add_charmap(cnode->character(), cnode->unicode());
            }
        }
    }

    return font;
}

void Analyze::getStream(ArrayNode *array, stringstream *stream_value)
{
    if (array)
    {
        for (size_t loop = 0; loop < array->size(); loop++)
        {
            ObjNode *obj = dynamic_cast<ObjNode *> (getRealValue(array->value(loop)));
            getStream(obj, stream_value);
        }
    }
}

void Analyze::getStream(ObjNode *obj, stringstream *stream_value)
{
    MapNode *node = dynamic_cast<MapNode *> (obj->value());
    NameNode *filter = dynamic_cast<NameNode *> (getRealObjValue(node->get("/Filter")));
    ArrayNode *filter_array = dynamic_cast<ArrayNode *> (getRealObjValue(node->get("/Filter")));
    int length = getNumberValue(getRealObjValue(node->get("/Length")));

    ifstream filein;
    filein.open(m_filein, ios::binary);

    Scanner scanner{&m_filestream};
    scanner.to_pos(obj->streamPos());

    char *stream = scanner.get_stream(length);
    filein.close();

    int total = length;
    if (filter && filter->name() == "/FlateDecode")
    {
        const char *value = flat_decode(stream, length, total);
        (*stream_value).write(value, total);
        delete[] value;
    }
    else if (filter_array)
    {
        size_t size = filter_array->size();
        if (size > 1)
        {
#ifdef DEBUG
            for (size_t loop = 0; loop < size; loop++)
            {
                filter = dynamic_cast<NameNode *> (getRealValue(filter_array->value(loop)));
                cout << filter->name() << endl;
            }
#endif
            error_message("More than one filter is not supported.");
        }
        else
        {
            for (size_t loop = 0; loop < size; loop++)
            {
                filter = dynamic_cast<NameNode *> (getRealValue(filter_array->value(loop)));
                if (filter && filter->name() == "/FlateDecode")
                {
                    const char *value = flat_decode(stream, length, total);
                    (*stream_value).write(value, total);
                    delete[] value;
                }
                else
                {
                    if (filter)
                    {
                        error_message("Invalid filter " + filter->name());
                    }
                    else
                    {
                        error_message("Filter not found");
                    }
                }
            }
        }
    }
    else if (!filter)
    {
        (*stream_value).write(stream, total);
    }
    else
    {
        error_message("Invalid filter " + filter->name());
    }

    delete[] stream;
}

void Analyze::analyzePages(TreeNode *page, ArrayNode *mediabox)
{
    ObjNode *obj_pages = dynamic_cast<ObjNode *> (page);
    if (!obj_pages)
    {
        // Invalid file.
        return;
    }

    MapNode *catalog = dynamic_cast<MapNode *> (obj_pages->value());
    NameNode *type = dynamic_cast<NameNode *> (catalog->get("/Type"));
    if (type)
    {
        if (type->name() == "/Pages")
        {
            ArrayNode *kids = dynamic_cast<ArrayNode *> (catalog->get("/Kids"));
            ArrayNode *media = dynamic_cast<ArrayNode *> (catalog->get("/MediaBox"));
            if (!media)
            {
                media = mediabox;
            }

            if (kids)
            {
                size_t kids_size = kids->size();
                for (size_t loop = 0; loop < kids_size; loop++)
                {
                    analyzePages(getRealValue(kids->value(loop)), media);
                }
            }
        }
        else if (type->name() == "/Page")
        {
            ArrayNode *media = dynamic_cast<ArrayNode *> (catalog->get("/MediaBox"));
            if (!media)
            {
                media = mediabox;
            }

            ObjNode *contents = dynamic_cast<ObjNode *> (getRealValue(catalog->get("/Contents")));
            if (contents)
            {
                stringstream stream_value;
                MapNode *snode = dynamic_cast<MapNode *> (contents->value());
                if (snode)
                {
                    getStream(contents, &stream_value);
                }
                else
                {
                    ArrayNode *array = dynamic_cast<ArrayNode *> (contents->value());
                    getStream(array, &stream_value);
                }

                m_document->addPage(
                        processPage(obj_pages->id(), obj_pages->generation(), &stream_value, catalog, media));
            }
        }
    }
}

TreeNode *Analyze::getRealValue(TreeNode *value)
{
    RefNode *ref = dynamic_cast<RefNode *> (value);
    if (ref)
    {
        return getObject(ref);
    }

    return value;
}

TreeNode *Analyze::getRealObjValue(TreeNode *value)
{
    RefNode *ref = dynamic_cast<RefNode *> (value);
    if (ref)
    {
        ObjNode *node = getObject(ref);
        if (node)
        {
            return node->value();
        }

        return nullptr;
    }

    return value;
}

string Analyze::getStringValue(TreeNode *value)
{
    RefNode *ref = dynamic_cast<RefNode *> (value);
    if (ref)
    {
        return getStringValue(getObject(ref)->value());
    }

    StringNode *str = dynamic_cast<StringNode *> (value);
    if (str)
    {
        return str->value();
    }

    return string();
}

double Analyze::getNumberValue(TreeNode *value, int default_value)
{
    RefNode *ref = dynamic_cast<RefNode *> (value);
    if (ref)
    {
        return getNumberValue(getObject(ref)->value());
    }

    NumberNode *num = dynamic_cast<NumberNode *> (value);
    if (num)
    {
        return num->value();
    }

    return default_value;
}

ObjNode *Analyze::getObject(RefNode *ref)
{
    if (!ref)
    {
        return nullptr;
    }

    return getObject(ref->id(), ref->generation());
}

ObjNode *Analyze::getObject(int id, int generation)
{
    size_t size = m_tree->size();
    ObjNode *ret = nullptr;
    bool done = false;

    for (size_t i = 0; i < size; i++)
    {
        if (!done)
        {
            ObjNode *obj = dynamic_cast<ObjNode *> (m_tree->get(i));
            if (obj && obj->sameObject(id, generation))
            {
                // Value found
                done = true;
                ret = obj;
            }
        }
    }

    return ret;
}
