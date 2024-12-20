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
#include "document.h"

#include <algorithm>
#include <utility>
#include "../nodes/treenode.h"

#include "font.h"
#include "outline.h"
#include "page.h"
#include "pagelabel.h"

using namespace node;
using namespace std;

Document::Document()
{
    m_root = nullptr;
    m_info = nullptr;
    m_encrypted = false;
    m_tree_root = false;
    m_outline = nullptr;
    m_lang = "en";
}

void Document::SetTreeRoot(const bool tree_root)
{
    m_tree_root = tree_root;
}

bool Document::TreeRoot() const
{
    return m_tree_root;
}

void Document::AddFont(const shared_ptr<Font>& font)
{
    m_fonts.push_back(font);
}

std::shared_ptr<Font> Document::CurrentFont(const string& name)
{
    const auto filter = [name](auto& font)
    {
        return font->Name() == name;
    };

    if (const auto it = std::find_if(m_fonts.begin(), m_fonts.end(), filter); it != m_fonts.end())
    {
        return *it;
    }

    return nullptr;
}

void Document::SetEncrypted(const bool encrypt)
{
    m_encrypted = encrypt;
}

bool Document::Encrypted() const
{
    return m_encrypted;
}

std::shared_ptr<Page> Document::CurrentPage(const int id, const int generation)
{
    for (auto& m_page : m_pages)
    {
        if (m_page->Id() == id && m_page->Generation() == generation)
        {
            return m_page;
        }
    }

    return nullptr;
}

void Document::SetOutline(shared_ptr<Outline> outline)
{
    m_outline = std::move(outline);
}

std::shared_ptr<Outline> Document::CurrentOutline() const
{
    return m_outline;
}

void Document::setId(const string& id, const string& generation)
{
    m_id = id + generation;
}

void Document::AddPage(const std::shared_ptr<Page>& page)
{
    m_pages.push_back(page);
}

void Document::AddPageLabel(const std::shared_ptr<PageLabel>& label)
{
    m_page_label.push_back(label);
}

std::shared_ptr<Page> Document::CurrentPage(const size_t index) const
{
    return m_pages[index];
}

size_t Document::Pages() const
{
    return m_pages.size();
}

shared_ptr<TreeNode> Document::RootNode()
{
    return m_root;
}

shared_ptr<TreeNode> Document::InfoNode()
{
    return m_info;
}

string Document::Id()
{
    return m_id;
}

void Document::SetRoot(TreeNode& root)
{
    m_root = std::make_shared<TreeNode>(root);
}

void Document::SetInfo(TreeNode& info)
{
    m_info = make_shared<TreeNode>(info);
}

void Document::SetTitle(const string& title)
{
    m_title = title;
}

void Document::SetSubject(const string& subject)
{
    m_subject = subject;
}

void Document::SetAuthor(const string& author)
{
    m_author = author;
}

void Document::SetLang(const string& lang)
{
    if (not lang.empty())
    {
        m_lang = lang;
    }
}

string Document::Lang()
{
    return m_lang;
}

string Document::Title()
{
    return m_title;
}

string Document::Subject()
{
    return m_subject;
}

string Document::Author()
{
    return m_author;
}
