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
#include "genericexception.h"
#include <fstream>
#include <utility>
#include <iostream>

using namespace std;
using namespace parser;
using namespace node;

Analyze::Analyze(string filein) : m_fileIn(std::move(filein))
{
}

void Analyze::AnalyzeXref()
{
    const size_t size = m_tree->Size();

    for (size_t i = 0; i < size; i++)
    {
        const auto value = m_tree->Get(i);
        if (const auto xref = std::dynamic_pointer_cast<XREFNode>(value))
        {
            const auto trailer = std::dynamic_pointer_cast<MapNode>(xref->Trailer());

            m_document->SetRoot(*GetRealValue(trailer->Get("/Root")));
            m_document->SetInfo(*GetRealValue(trailer->Get("/Info")));
            m_document->SetEncrypted(GetRealValue(trailer->Get("/Encrypt")) != nullptr);

            if (const auto array = std::dynamic_pointer_cast<ArrayNode>(trailer->Get("/ID")); array && array->Size() ==
                2)
            {
                const string first = GetStringValue(array->Value(0));
                const string second = GetStringValue(array->Value(1));
                m_document->setId(first, second);
            }

            break;
        }
        else
        {
            if (const auto obj = std::dynamic_pointer_cast<ObjNode>(value))
            {
                if (const auto values = std::dynamic_pointer_cast<MapNode>(obj->Value()))
                {
                    // analyze only XREF Objects
                    if (const auto type = std::dynamic_pointer_cast<NameNode>(values->Get("/Type")); type && type->
                        Name() == "/XRef")
                    {
                        m_document->SetRoot(*GetRealValue(values->Get("/Root")));
                        m_document->SetInfo(*GetRealValue(values->Get("/Info")));

                        if (const auto array = std::dynamic_pointer_cast<ArrayNode>(values->Get("/ID")); array && array
                            ->Size() == 2)
                        {
                            const string first = GetStringValue(array->Value(0));
                            const string second = GetStringValue(array->Value(1));
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
    const auto root = m_document->RootNode();
    if (const auto obj = std::dynamic_pointer_cast<ObjNode>(root))
    {
        if (const auto info = std::dynamic_pointer_cast<MapNode>(obj->Value()))
        {
            m_document->SetTitle(GetStringValue(info->Get("/Title")));
            m_document->SetAuthor(GetStringValue(info->Get("/Author")));
            m_document->SetSubject(GetStringValue(info->Get("/Subject")));
        }
    }
}

std::shared_ptr<TreeNode> Analyze::AnalyzeRoot()
{
    const auto root = m_document->RootNode();
    const auto obj_root = std::dynamic_pointer_cast<ObjNode>(root);
    if (not obj_root)
    {
        // Invalid file
        return nullptr;
    }

    const auto catalog = std::dynamic_pointer_cast<MapNode>(obj_root->Value());
    if (const auto name = std::dynamic_pointer_cast<NameNode>(catalog->Get("/Type")); not name || name->Name() !=
        "/Catalog")
    {
        // Invalid file
        return nullptr;
    }

    const auto m_page_tree = GetRealValue(catalog->Get("/Pages"));
    m_document->SetLang(GetStringValue(catalog->Get("/Lang")));

    if (const auto namesNode = std::dynamic_pointer_cast<MapNode>(GetRealObjValue(catalog->Get("/Names"))))
    {
        const auto destinations = std::dynamic_pointer_cast<MapNode>(GetRealObjValue(namesNode->Get("/Dests")));
        AnalyzeNames(destinations);
    }

    if (const auto page_labels = std::dynamic_pointer_cast<MapNode>(GetRealObjValue(catalog->Get("/PageLabels"))))
    {
        if (const auto array = std::dynamic_pointer_cast<ArrayNode>(GetRealValue(page_labels->Get("/Nums"))))
        {
            const size_t size = array->Size();

            for (size_t loop = 0; loop < size; loop += 2)
            {
                int page = static_cast<int>(GetNumberValue(array->Value(loop)));
                if (const auto attributes = std::dynamic_pointer_cast<MapNode>(GetRealObjValue(array->Value(loop + 1))))
                {
                    const auto name_type = std::dynamic_pointer_cast<NameNode>(attributes->Get("/S"));
                    page_type type = ARABIC;
                    if (name_type)
                    {
                        if (name_type->Name() == "D")
                        {
                            type = ARABIC;
                        }
                        else if (name_type->Name() == "R")
                        {
                            type = UPPERCASE_ROMAN;
                        }
                        else if (name_type->Name() == "r")
                        {
                            type = LOWERCASE_ROMAN;
                        }
                        else if (name_type->Name() == "A")
                        {
                            type = UPPERCASE_LETTERS;
                        }
                        else if (name_type->Name() == "a")
                        {
                            type = LOWERCASE_LETTERS;
                        }
                    }

                    string newName = GetStringValue(attributes->Get("/P"));
                    const int range = static_cast<int>(GetNumberValue(attributes->Get("/St"), 1));
                    m_document->AddPageLabel(std::make_shared<PageLabel>(page, range, type, newName));
                }
            }
        }
    }

    if (const auto outlines = std::dynamic_pointer_cast<MapNode>(GetRealObjValue(catalog->Get("/Outlines"))))
    {
        AnalyzeOutlines(outlines);
    }

    if (const auto tree_root = catalog->Get("/StructTreeRoot"))
    {
        m_document->SetTreeRoot(true);
    }

    return m_page_tree;
}

void Analyze::AnalyzeNames(const std::shared_ptr<MapNode>& values)
{
    if (const auto children = std::dynamic_pointer_cast<ArrayNode>(values->Get("/Kids")))
    {
        const size_t size = children->Size();

        for (size_t i = 0; i < size; i++)
        {
            const auto map_kids = std::dynamic_pointer_cast<MapNode>(GetRealObjValue(children->Value(i)));
            AnalyzeNames(map_kids);
        }
    }
    else
    {
        if (const auto namesNode = std::dynamic_pointer_cast<ArrayNode>(values->Get("/Names")))
        {
            const size_t size = namesNode->Size();

            for (size_t i = 0; i < size; i += 2)
            {
                string name = GetStringValue(namesNode->Value(i));
                this->m_names[name] = namesNode->Value(i + 1);
            }
        }
    }
}

std::shared_ptr<TreeNode> Analyze::GetNamedValue(const string& name)
{
    try
    {
        return m_names.at(name);
    }
    catch (out_of_range&)
    {
        return nullptr;
    }
}

void Analyze::AnalyzeOutlines(const std::shared_ptr<MapNode>& values, const std::shared_ptr<Outline>& parent)
{
    if (const auto type = std::dynamic_pointer_cast<NameNode>(values->Get("/Type")); type && type->Name() !=
        "/Outlines")
    {
        ErrorMessage(L"Invalid outlines");
        return;
    }

    auto outline = make_shared<Outline>();
    if (const string named_dest = GetStringValue(values->Get("/Dest")); not named_dest.empty())
    {
        if (const auto map = std::dynamic_pointer_cast<MapNode>(GetRealObjValue(GetNamedValue(named_dest))))
        {
            const auto dest = std::dynamic_pointer_cast<ArrayNode>(GetRealObjValue(map->Get("/D")));
            AnalyzeOutline(dest, outline);
        }
    }

    if (const auto destinations = std::dynamic_pointer_cast<ArrayNode>(values->Get("/Dest")); destinations &&
        destinations->Size() > 0)
    {
        AnalyzeOutline(destinations, outline);
    }
    else
    {
        if (const auto actions = std::dynamic_pointer_cast<MapNode>(GetRealObjValue(values->Get("/A"))))
        {
            if (const auto subtype = std::dynamic_pointer_cast<NameNode>(GetRealObjValue(actions->Get("/S"))); subtype
                && subtype->Name() == "/GoTo")
            {
                const auto dest = std::dynamic_pointer_cast<ArrayNode>(GetRealObjValue(actions->Get("/D")));
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

    if (const auto first = std::dynamic_pointer_cast<MapNode>(GetRealObjValue(values->Get("/First"))))
    {
        AnalyzeOutlines(first, outline);
    }

    if (const auto next = std::dynamic_pointer_cast<MapNode>(GetRealObjValue(values->Get("/Next"))); next && parent)
    {
        AnalyzeOutlines(next, parent);
    }
}

void Analyze::AnalyzeOutline(const std::shared_ptr<ArrayNode>& values, const std::shared_ptr<Outline>& outline)
{
    if (values && values->Size() > 0)
    {
        if (const auto ref = std::dynamic_pointer_cast<RefNode>(values->Value(0)))
        {
            outline->SetDestination(ref->Id(), ref->Generation());
        }

        if (const auto command = std::dynamic_pointer_cast<NameNode>(values->Value(1)); command && command->Name() ==
            "/XYZ")
        {
            double x = GetNumberValue(values->Value(2));
            double y = GetNumberValue(values->Value(3));
            outline->SetLocation(x, y);
        }
    }
}

std::shared_ptr<Document> Analyze::AnalyzeTree()
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
    m_document = make_shared<Document>();

    AnalyzeXref();
    AnalyzeInfo();

    if (m_document->Encrypted())
    {
        throw GenericException("Encrypted file is not supported.");
    }

    const auto m_page_tree = AnalyzeRoot();
    AnalyzePages(m_page_tree);
    return m_document;
}

std::shared_ptr<Page> Analyze::ProcessPage(const int id, const int generation, stringstream* stream_value,
                                           const std::shared_ptr<MapNode>& catalog, const std::shared_ptr<ArrayNode>&)
{
    const auto page = make_shared<Page>(m_document);
    page->SetDestination(id, generation);

    if (const auto resources = std::dynamic_pointer_cast<MapNode>(GetRealObjValue(catalog->Get("/Resources"))))
    {
        if (const auto fonts = std::dynamic_pointer_cast<MapNode>(GetRealObjValue(resources->Get("/Font"))))
        {
            const vector<string> namesList = fonts->Names();
            const size_t size = namesList.size();
            for (size_t loop = 0; loop < size; loop++)
            {
                string alias = namesList[loop];
                if (const auto fontmap = std::dynamic_pointer_cast<MapNode>(GetRealObjValue(fonts->Get(alias))))
                {
                    const auto font = AnalyzeFont(fontmap);
                    page->AddFontMap(alias, font->Name());
                }
            }
        }
    }

    stream_value->seekg(0);
    PageParser parser(stream_value);
    const auto root = parser.Parse();

    PageAnalyze analyze(m_document);
    page->SetRoot(analyze.AnalyzeTree(root));

    return page;
}

std::shared_ptr<Font> Analyze::AnalyzeFont(const std::shared_ptr<MapNode>& fontmap)
{
    std::shared_ptr<Font> font(new Font());

    font->SetName("Unnamed");
    const auto descriptor = std::dynamic_pointer_cast<MapNode>(GetRealObjValue(fontmap->Get("/FontDescriptor")));
    if (descriptor)
    {
        if (const auto name = std::dynamic_pointer_cast<NameNode>(descriptor->Get("/FontName")))
        {
            font->SetName(name->Name());
        }
    }

    if (const auto from_document = m_document->CurrentFont(font->Name()))
    {
        return from_document;
    }
    else
    {
        m_document->AddFont(font);
    }

    if (descriptor)
    {
        const int flags = static_cast<int>(GetNumberValue(GetRealObjValue(descriptor->Get("/Flags"))));
        if (flags & 1)
        {
            font->SetFixed(true);
        }

        if (flags & 64)
        {
            font->SetItalic(true);
        }
    }

    if (const auto to_unicode = std::dynamic_pointer_cast<ObjNode>(GetRealValue(fontmap->Get("/ToUnicode"))))
    {
        stringstream stream;
        GetStream(to_unicode, &stream);

        stream.seekg(0);
        CMapParser parser(&stream);

        if (const auto root = parser.Parse())
        {
            if (const auto code_space = root->CodeSpace())
            {
                font->SetCharMapStart(code_space->Start());
                font->SetCharMapFinish(code_space->Finish());
            }

            const size_t size = root->Nodes();
            for (size_t loop = 0; loop < size; loop++)
            {
                const auto cnode = root->Node(loop);
                font->AddCharMap(cnode->Character(), cnode->Unicode());
            }
        }
    }

    return font;
}

void Analyze::GetStream(const std::shared_ptr<ArrayNode>& array, stringstream* stream_value)
{
    if (array)
    {
        for (size_t loop = 0; loop < array->Size(); loop++)
        {
            const auto obj = std::dynamic_pointer_cast<ObjNode>(GetRealValue(array->Value(loop)));
            GetStream(obj, stream_value);
        }
    }
}

void Analyze::GetStream(const std::shared_ptr<ObjNode>& obj, stringstream* stream_value)
{
    const auto node = std::dynamic_pointer_cast<MapNode>(obj->Value());
    auto filter = std::dynamic_pointer_cast<NameNode>(GetRealObjValue(node->Get("/Filter")));
    const auto filter_array = std::dynamic_pointer_cast<ArrayNode>(GetRealObjValue(node->Get("/Filter")));
    const unsigned int length = static_cast<unsigned int>(GetNumberValue(GetRealObjValue(node->Get("/Length"))));

    ifstream filestream;
    filestream.open(m_fileIn, ios::binary);
    Scanner scanner{&filestream};
    scanner.ToPos(obj->StreamPos());

    const auto stream = scanner.Stream(length);
    filestream.close();

    auto total = static_cast<size_t>(length);
    if (filter && filter->Name() == "/FlateDecode")
    {
        const char* value = FlatDecode(stream.c_str(), length, total);
#ifdef DEBUG
        static int stream_count;
        stream_count++;

        ofstream out(m_fileIn + ".stream." + to_string(stream_count));
        out.write(value, length);
#endif
        (*stream_value).write(value, static_cast<streamsize>(total));
        delete [] value;
    }
    else if (filter_array)
    {
        if (size_t size = filter_array->Size(); size > 1)
        {
#ifdef DEBUG
            for (size_t loop = 0; loop < size; loop++)
            {
                filter = std::dynamic_pointer_cast<NameNode>(GetRealValue(filter_array->Value(loop)));
                cout << filter->Name() << endl;
            }
#endif
            ErrorMessage(L"More than one filter is not supported.");
        }
        else
        {
            for (size_t loop = 0; loop < size; loop++)
            {
                filter = std::dynamic_pointer_cast<NameNode>(GetRealValue(filter_array->Value(loop)));
                if (filter && filter->Name() == "/FlateDecode")
                {
                    const char* value = FlatDecode(stream.c_str(), length, total);
#ifdef DEBUG
                    cout << "Stream>\n" << value << "<\n";
#endif
                    stream_value->write(value, static_cast<streamsize>(total));
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
        stream_value->write(stream.c_str(), static_cast<streamsize>(total));
    }
    else
    {
        wstring message = L"Invalid filter ";
        message += SingleToWide(filter->Name());
        ErrorMessage(message);
    }
}

void Analyze::AnalyzePages(const std::shared_ptr<TreeNode>& page, const std::shared_ptr<ArrayNode>& media_box)
{
    const auto obj_pages = std::dynamic_pointer_cast<ObjNode>(page);
    if (not obj_pages)
    {
        // Invalid file.
        return;
    }

    const auto catalog = std::dynamic_pointer_cast<MapNode>(obj_pages->Value());
    if (const auto type = std::dynamic_pointer_cast<NameNode>(catalog->Get("/Type")))
    {
        if (type->Name() == "/Pages")
        {
            const auto children = std::dynamic_pointer_cast<ArrayNode>(catalog->Get("/Kids"));
            auto media = std::dynamic_pointer_cast<ArrayNode>(catalog->Get("/MediaBox"));
            if (not media)
            {
                media = media_box;
            }

            if (children)
            {
                const size_t children_size = children->Size();
                for (size_t loop = 0; loop < children_size; loop++)
                {
                    AnalyzePages(GetRealValue(children->Value(loop)), media);
                }
            }
        }
        else if (type->Name() == "/Page")
        {
            auto media = std::dynamic_pointer_cast<ArrayNode>(catalog->Get("/MediaBox"));
            if (not media)
            {
                media = media_box;
            }

            if (const auto contents = std::dynamic_pointer_cast<ObjNode>(GetRealValue(catalog->Get("/Contents"))))
            {
                stringstream stream_value;
                if (const auto snode = std::dynamic_pointer_cast<MapNode>(contents->Value()))
                {
                    GetStream(contents, &stream_value);
                }
                else
                {
                    const auto array = std::dynamic_pointer_cast<ArrayNode>(contents->Value());
                    GetStream(array, &stream_value);
                }

                m_document->AddPage(
                    ProcessPage(obj_pages->Id(), obj_pages->Generation(), &stream_value, catalog, media));
            }
        }
    }
}

std::shared_ptr<TreeNode> Analyze::GetRealValue(std::shared_ptr<TreeNode> value)
{
    if (const auto ref = std::dynamic_pointer_cast<RefNode>(value))
    {
        return GetObject(ref);
    }

    return value;
}

std::shared_ptr<TreeNode> Analyze::GetRealObjValue(std::shared_ptr<TreeNode> value)
{
    if (const auto ref = std::dynamic_pointer_cast<RefNode>(value))
    {
        if (const auto node = GetObject(ref))
        {
            return node->Value();
        }

        return nullptr;
    }

    return value;
}

string Analyze::GetStringValue(const std::shared_ptr<TreeNode>& value)
{
    if (const auto ref = std::dynamic_pointer_cast<RefNode>(value))
    {
        return GetStringValue(GetObject(ref)->Value());
    }

    if (const auto str = std::dynamic_pointer_cast<StringNode>(value))
    {
        return str->Value();
    }

    return "";
}

double Analyze::GetNumberValue(const std::shared_ptr<TreeNode>& value, const int default_value)
{
    if (const auto ref = std::dynamic_pointer_cast<RefNode>(value))
    {
        return GetNumberValue(GetObject(ref)->Value());
    }

    if (const auto num = std::dynamic_pointer_cast<NumberNode>(value))
    {
        return num->Value();
    }

    return default_value;
}

std::shared_ptr<ObjNode> Analyze::GetObject(const std::shared_ptr<RefNode>& ref) const
{
    if (not ref)
    {
        return nullptr;
    }

    return GetObject(ref->Id(), ref->Generation());
}

std::shared_ptr<ObjNode> Analyze::GetObject(const int id, const int generation) const
{
    const size_t size = m_tree->Size();
    std::shared_ptr<ObjNode> ret = nullptr;

    for (size_t i = 0; i < size; i++)
    {
        if (const auto obj = std::dynamic_pointer_cast<ObjNode>(m_tree->Get(i)); obj && obj->SameObject(id, generation))
        {
            // Value found
            ret = obj;
            break;
        }
    }

    return ret;
}
