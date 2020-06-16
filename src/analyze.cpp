/*
 * This file is part of PDF Tools.
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

Analyze::Analyze(const string &filein) : m_fileIn(filein)
{
}

Analyze::~Analyze()
{
    for (auto i = m_names.begin(); i != m_names.end(); i++)
    {
        delete (*i).second;
    }
    
    if (m_document)
    {
        delete m_document;
    }
    
    if (m_tree)
    {
        delete m_tree;
    }
}

void Analyze::AnalyzeXref()
{
    size_t size = m_tree->Size();
    
    for (size_t i = 0; i < size; i++)
    {
        TreeNode *value = m_tree->Get(i);
        XREFNode *xref = dynamic_cast<XREFNode *>(value);
        if (xref)
        {
            MapNode *trailer = dynamic_cast<MapNode *>(xref->Trailer());
            
            m_document->SetRoot(GetRealValue(trailer->Get("/Root")));
            m_document->SetInfo(GetRealValue(trailer->Get("/Info")));
            m_document->SetEncrypted(GetRealValue(trailer->Get("/Encrypt")) != nullptr);
            
            ArrayNode *array = dynamic_cast<ArrayNode *>(trailer->Get("/ID"));
            if (array && array->Size() == 2)
            {
                string first = GetStringValue(array->Value(0));
                string second = GetStringValue(array->Value(1));
                m_document->setId(first, second);
            }
            
            break;
        }
        else
        {
            ObjNode *obj = dynamic_cast<ObjNode *>(value);
            if (obj)
            {
                MapNode *values = dynamic_cast<MapNode *>(obj->Value());
                if (values)
                {
                    NameNode *type = dynamic_cast<NameNode *>(values->Get("/Type"));
                    
                    // analyze only XREF Objects
                    if (type && type->Name() == "/XRef")
                    {
                        m_document->SetRoot(GetRealValue(values->Get("/Root")));
                        m_document->SetInfo(GetRealValue(values->Get("/Info")));
                        
                        ArrayNode *array = dynamic_cast<ArrayNode *>(values->Get("/ID"));
                        if (array && array->Size() == 2)
                        {
                            string first = GetStringValue(array->Value(0));
                            string second = GetStringValue(array->Value(1));
                            m_document->setId(first, second);
                        }
                        
                        break;
                    }
                }
            }
        }
    }
}

void Analyze::AnalyzeInfo()
{
    ObjNode *obj = dynamic_cast<ObjNode *>(m_document->InfoNode());
    if (obj)
    {
        MapNode *info = dynamic_cast<MapNode *>(obj->Value());
        if (info)
        {
            m_document->SetTitle(GetStringValue(info->Get("/Title")));
            m_document->SetAuthor(GetStringValue(info->Get("/Author")));
            m_document->SetSubject(GetStringValue(info->Get("/Subject")));
        }
    }
}

TreeNode *Analyze::AnalyzeRoot()
{
    ObjNode *obj_root = dynamic_cast<ObjNode *>(m_document->RootNode());
    if (not obj_root)
    {
        // Invalid file
        return nullptr;
    }
    
    MapNode *catalog = dynamic_cast<MapNode *>(obj_root->Value());
    NameNode *name = dynamic_cast<NameNode *>(catalog->Get("/Type"));
    if (not name || name->Name() != "/Catalog")
    {
        // Invalid file
        return nullptr;
    }
    
    node::TreeNode* m_page_tree = GetRealValue(catalog->Get("/Pages"));
    m_document->SetLang(GetStringValue(catalog->Get("/Lang")));
    
    MapNode *namesNode = dynamic_cast<MapNode *>(GetRealObjValue(catalog->Get("/Names")));
    if (namesNode)
    {
        MapNode *dests = dynamic_cast<MapNode *>(GetRealObjValue(namesNode->Get("/Dests")));
        AnalyzeNames(dests);
    }
    
    MapNode *page_labels = dynamic_cast<MapNode *>(GetRealObjValue(catalog->Get("/PageLabels")));
    if (page_labels)
    {
        ArrayNode *array = dynamic_cast<ArrayNode *>(GetRealValue(page_labels->Get("/Nums")));
        if (array)
        {
            size_t size = array->Size();
            
            for (size_t loop = 0; loop < size; loop += 2)
            {
                int page = (int) GetNumberValue(array->Value(loop));
                MapNode *attributes =
                    dynamic_cast<MapNode *>(GetRealObjValue(array->Value(loop + 1)));
                if (attributes)
                {
                    NameNode *name_type = dynamic_cast<NameNode *>(attributes->Get("/S"));
                    page_type type = ARABIC;
                    if (name_type)
                    {
                        if (name_type->Name() == "D")
                        {
                            type = ARABIC;
                        }
                        else if (name_type->Name() == "R")
                        {
                            type = UPCASE_ROMAN;
                        }
                        else if (name_type->Name() == "r")
                        {
                            type = LOWCASE_ROMAN;
                        }
                        else if (name_type->Name() == "A")
                        {
                            type = UPCASE_LETTERS;
                        }
                        else if (name_type->Name() == "a")
                        {
                            type = LOWCASE_LETTERS;
                        }
                    }
                    
                    string newName = GetStringValue(attributes->Get("/P"));
                    int range = (int) GetNumberValue(attributes->Get("/St"), 1);
                    m_document->AddPageLabel(new PageLabel(page, range, type, newName));
                }
            }
        }
    }
    
    MapNode *outlines = dynamic_cast<MapNode *>(GetRealObjValue(catalog->Get("/Outlines")));
    if (outlines)
    {
        AnalyzeOutlines(outlines);
    }
    
    TreeNode *tree_root = catalog->Get("/StructTreeRoot");
    if (tree_root)
    {
        m_document->SetTreeRoot(true);
    }
    
    return m_page_tree;
}

void Analyze::AnalyzeNames(MapNode *values)
{
    ArrayNode *kids = dynamic_cast<ArrayNode *>(values->Get("/Kids"));
    if (kids)
    {
        size_t size = kids->Size();
        
        for (size_t i = 0; i < size; i++)
        {
            MapNode *map_kids = dynamic_cast<MapNode *>(GetRealObjValue(kids->Value(i)));
            AnalyzeNames(map_kids);
        }
    }
    else
    {
        ArrayNode *namesNode = dynamic_cast<ArrayNode *>(values->Get("/Names"));
        if (namesNode)
        {
            size_t size = namesNode->Size();
            
            for (size_t i = 0; i < size; i += 2)
            {
                string name = GetStringValue(namesNode->Value(i));
                this->m_names[name] = namesNode->Value(i + 1);
            }
        }
    }
}

TreeNode *Analyze::GetNamedValue(string name)
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

void Analyze::AnalyzeOutlines(MapNode *values, Outline *parent)
{
    NameNode *type = dynamic_cast<NameNode *>(values->Get("/Type"));
    if (type && type->Name() != "/Outlines")
    {
        ErrorMessage(L"Invalid outlines");
        return;
    }
    
    Outline *outline = new Outline;
    string named_dest = GetStringValue(values->Get("/Dest"));
    if (not named_dest.empty())
    {
        MapNode *map = dynamic_cast<MapNode *>(GetRealObjValue(GetNamedValue(named_dest)));
        if (map)
        {
            ArrayNode *dest = dynamic_cast<ArrayNode *>(GetRealObjValue(map->Get("/D")));
            AnalyzeOutline(dest, outline);
        }
    }
    
    ArrayNode *destinations = dynamic_cast<ArrayNode *>(values->Get("/Dest"));
    if (destinations && destinations->Size() > 0)
    {
        AnalyzeOutline(destinations, outline);
    }
    else
    {
        MapNode *actions = dynamic_cast<MapNode *>(GetRealObjValue(values->Get("/A")));
        if (actions)
        {
            NameNode *subtype = dynamic_cast<NameNode *>(GetRealObjValue(actions->Get("/S")));
            if (subtype && subtype->Name() == "/GoTo")
            {
                ArrayNode *dest = dynamic_cast<ArrayNode *>(GetRealObjValue(actions->Get("/D")));
                AnalyzeOutline(dest, outline);
            }
        }
    }
    
    outline->SetTitle(GetStringValue(values->Get("/Title")));
    
    if (not parent)
    {
        // root node
        m_document->SetOutline(outline);
    }
    else
    {
        if (parent)
        {
            parent->AddChild(outline);
        }
    }
    
    MapNode *first = dynamic_cast<MapNode *>(GetRealObjValue(values->Get("/First")));
    if (first)
    {
        AnalyzeOutlines(first, outline);
    }
    
    MapNode *next = dynamic_cast<MapNode *>(GetRealObjValue(values->Get("/Next")));
    if (next && parent)
    {
        AnalyzeOutlines(next, parent);
    }
}

void Analyze::AnalyzeOutline(ArrayNode *values, Outline *outline)
{
    if (values && values->Size() > 0)
    {
        RefNode *ref = dynamic_cast<RefNode *>(values->Value(0));
        if (ref)
        {
            outline->SetDestination(ref->Id(), ref->Generation());
        }
        
        NameNode *command = dynamic_cast<NameNode *>(values->Value(1));
        if (command && command->Name() == "/XYZ")
        {
            double x = GetNumberValue(values->Value(2));
            double y = GetNumberValue(values->Value(3));
            outline->SetLocation(x, y);
        }
    }
}

Document *Analyze::AnalyzeTree()
{
    VerboseMessage(L"Parsing file " + SingleToWide(m_fileIn));
    
    ifstream filestream;
    filestream.open(m_fileIn, ios::binary);

    Parser parser(&filestream);
    m_tree = parser.Parse();
    filestream.close();
    
    if (not m_tree)
    {
        // Invalid tree
        throw GenericException("Invalid file.");
    }
    m_document = new Document;
    
    AnalyzeXref();
    AnalyzeInfo();
    
    if (m_document->Encrypted())
    {
        throw GenericException("Encrypted file is not supported.");
    }
    else
    {
        TreeNode *m_page_tree = AnalyzeRoot();
        AnalyzePages(m_page_tree);
        return m_document;
    }
}

Page *Analyze::ProcessPage(int id, int generation, stringstream *stream_value, MapNode *catalog, ArrayNode *)
{
    Page *page = new Page(m_document);
    page->SetDestination(id, generation);
    
    MapNode *resources = dynamic_cast<MapNode *>(GetRealObjValue(catalog->Get("/Resources")));
    if (resources)
    {
        MapNode *fonts = dynamic_cast<MapNode *>(GetRealObjValue(resources->Get("/Font")));
        if (fonts)
        {
            vector<string> namesList = fonts->Names();
            size_t size = namesList.size();
            for (size_t loop = 0; loop < size; loop++)
            {
                string alias = namesList[loop];
                MapNode *fontmap = dynamic_cast<MapNode *>(GetRealObjValue(fonts->Get(alias)));
                if (fontmap)
                {
                    Font *font = AnalyzeFont(fontmap);
                    page->AddFontMap(alias, font->Name());
                }
            }
        }
    }
    
    stream_value->seekg(0);
    PageParser parser(stream_value);
    RootNode *root = parser.Parse();
    
    PageAnalyze analyze(m_document);
    page->SetRoot(analyze.AnalyzeTree(root));
    
    return page;
}

Font *Analyze::AnalyzeFont(MapNode *fontmap)
{
    Font *font = new Font;
    
    font->SetName("Unnamed");
    MapNode *descriptor = dynamic_cast<MapNode *>(GetRealObjValue(fontmap->Get("/FontDescriptor")));
    if (descriptor)
    {
        NameNode *name = dynamic_cast<NameNode *>(descriptor->Get("/FontName"));
        if (name)
        {
            font->SetName(name->Name());
        }
    }
    
    Font *from_document = m_document->CurrentFont(font->Name().c_str());
    if (from_document)
    {
        delete font;
        return from_document;
    }
    else
    {
        m_document->AddFont(font);
    }
    
    if (descriptor)
    {
        int flags = (int) GetNumberValue(GetRealObjValue(descriptor->Get("/Flags")));
        if (flags & 1)
        {
            font->SetFixed(true);
        }
        
        if (flags & 64)
        {
            font->SetItalic(true);
        }
    }
    
    ObjNode *to_unicode = dynamic_cast<ObjNode *>(GetRealValue(fontmap->Get("/ToUnicode")));
    if (to_unicode)
    {
        stringstream stream;
        GetStream(to_unicode, &stream);
        
        stream.seekg(0);
        CMapParser parser(&stream);
        CMapNode *root = parser.Parse();
        
        if (root)
        {
            CodeSpaceNode *codespace = root->CodeSpace();
            if (codespace)
            {
                font->SetCharMapStart(codespace->Start());
                font->SetCharMapFinish(codespace->Finish());
            }
            
            size_t size = root->Nodes();
            for (size_t loop = 0; loop < size; loop++)
            {
                CharNode *cnode = root->Node(loop);
                font->AddCharMap(cnode->Character(), cnode->Unicode());
            }
        }
    }
    
    return font;
}

void Analyze::GetStream(ArrayNode *array, stringstream *stream_value)
{
    if (array)
    {
        for (size_t loop = 0; loop < array->Size(); loop++)
        {
            ObjNode *obj = dynamic_cast<ObjNode *>(GetRealValue(array->Value(loop)));
            GetStream(obj, stream_value);
        }
    }
}

void Analyze::GetStream(ObjNode *obj, stringstream *stream_value)
{
    MapNode *node = dynamic_cast<MapNode *>(obj->Value());
    NameNode *filter = dynamic_cast<NameNode *>(GetRealObjValue(node->Get("/Filter")));
    ArrayNode *filter_array = dynamic_cast<ArrayNode *>(GetRealObjValue(node->Get("/Filter")));
    unsigned int length = (unsigned int) GetNumberValue(GetRealObjValue(node->Get("/Length")));
    
    ifstream filestream;
    filestream.open(m_fileIn, ios::binary);
    Scanner scanner{ &filestream };
    scanner.ToPos(obj->StreamPos());
    
    char *stream = scanner.Stream(length);
    filestream.close();
    
    size_t total = (size_t)length;
    if (filter && filter->Name() == "/FlateDecode")
    {
        const char *value = FlatDecode(stream, length, total);
#ifdef DEBUG
        static int stream;
        stream++;
        
        ofstream out(m_fileIn + ".stream." + to_string(stream));
        out.write(value, length);
#endif
        (*stream_value).write(value, (streamsize)total);
        delete [] value;
    }
    else if (filter_array)
    {
        size_t size = filter_array->Size();
        if (size > 1)
        {
#ifdef DEBUG
            for (size_t loop = 0; loop < size; loop++)
            {
                filter = dynamic_cast<NameNode *> (GetRealValue(filter_array->Value(loop)));
                cout << filter->Name() << endl;
            }
#endif
            ErrorMessage(L"More than one filter is not supported.");
        }
        else
        {
            for (size_t loop = 0; loop < size; loop++)
            {
                filter = dynamic_cast<NameNode *>(GetRealValue(filter_array->Value(loop)));
                if (filter && filter->Name() == "/FlateDecode")
                {
                    const char *value = FlatDecode(stream, length, total);
#ifdef DEBUG
                    cout << "Stream>\n" << value << "<\n";
#endif
                    (*stream_value).write(value, (streamsize)total);
                    delete [] value;
                }
                else
                {
                    if (filter)
                    {
                        wstring message = L"Invalid filter ";
                        message += SingleToWide(filter->Name());
                        ErrorMessage(message);
                    }
                    else
                    {
                        ErrorMessage(L"Filter not found");
                    }
                }
            }
        }
    }
    else if (not filter)
    {
        (*stream_value).write(stream, (streamsize)total);
    }
    else
    {
        wstring message = L"Invalid filter ";
        message += SingleToWide(filter->Name());
        ErrorMessage(message);
    }
    
    delete [] stream;
}

void Analyze::AnalyzePages(TreeNode *page, ArrayNode *mediabox)
{
    ObjNode *obj_pages = dynamic_cast<ObjNode *>(page);
    if (not obj_pages)
    {
        // Invalid file.
        return;
    }
    
    MapNode *catalog = dynamic_cast<MapNode *>(obj_pages->Value());
    NameNode *type = dynamic_cast<NameNode *>(catalog->Get("/Type"));
    if (type)
    {
        if (type->Name() == "/Pages")
        {
            ArrayNode *kids = dynamic_cast<ArrayNode *>(catalog->Get("/Kids"));
            ArrayNode *media = dynamic_cast<ArrayNode *>(catalog->Get("/MediaBox"));
            if (not media)
            {
                media = mediabox;
            }
            
            if (kids)
            {
                size_t kids_size = kids->Size();
                for (size_t loop = 0; loop < kids_size; loop++)
                {
                    AnalyzePages(GetRealValue(kids->Value(loop)), media);
                }
            }
        }
        else if (type->Name() == "/Page")
        {
            ArrayNode *media = dynamic_cast<ArrayNode *>(catalog->Get("/MediaBox"));
            if (not media)
            {
                media = mediabox;
            }
            
            ObjNode *contents = dynamic_cast<ObjNode *>(GetRealValue(catalog->Get("/Contents")));
            if (contents)
            {
                stringstream stream_value;
                MapNode *snode = dynamic_cast<MapNode *>(contents->Value());
                if (snode)
                {
                    GetStream(contents, &stream_value);
                }
                else
                {
                    ArrayNode *array = dynamic_cast<ArrayNode *>(contents->Value());
                    GetStream(array, &stream_value);
                }
                
                m_document->AddPage(ProcessPage(obj_pages->Id(), obj_pages->Generation(),
                                                &stream_value, catalog, media));
            }
        }
    }
}

TreeNode *Analyze::GetRealValue(TreeNode *value)
{
    RefNode *ref = dynamic_cast<RefNode *>(value);
    if (ref)
    {
        return GetObject(ref);
    }
    
    return value;
}

TreeNode *Analyze::GetRealObjValue(TreeNode *value)
{
    RefNode *ref = dynamic_cast<RefNode *>(value);
    if (ref)
    {
        ObjNode *node = GetObject(ref);
        if (node)
        {
            return node->Value();
        }
        
        return nullptr;
    }
    
    return value;
}

string Analyze::GetStringValue(TreeNode *value)
{
    RefNode *ref = dynamic_cast<RefNode *>(value);
    if (ref)
    {
        return GetStringValue(GetObject(ref)->Value());
    }
    
    StringNode *str = dynamic_cast<StringNode *>(value);
    if (str)
    {
        return str->Value();
    }
    
    return string();
}

double Analyze::GetNumberValue(TreeNode *value, int default_value)
{
    RefNode *ref = dynamic_cast<RefNode *>(value);
    if (ref)
    {
        return GetNumberValue(GetObject(ref)->Value());
    }
    
    NumberNode *num = dynamic_cast<NumberNode *>(value);
    if (num)
    {
        return num->Value();
    }
    
    return default_value;
}

ObjNode *Analyze::GetObject(RefNode *ref)
{
    if (not ref)
    {
        return nullptr;
    }
    
    return GetObject(ref->Id(), ref->Generation());
}

ObjNode *Analyze::GetObject(int id, int generation)
{
    size_t size = m_tree->Size();
    ObjNode *ret = nullptr;
    bool done = false;
    
    for (size_t i = 0; i < size; i++)
    {
        if (not done)
        {
            ObjNode *obj = dynamic_cast<ObjNode *>(m_tree->Get(i));
            if (obj && obj->SameObject(id, generation))
            {
                // Value found
                done = true;
                ret = obj;
                break;
            }
        }
    }
    
    return ret;
}
