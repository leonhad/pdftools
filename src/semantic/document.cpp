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
    m_outlines = nullptr;
    m_lang = "en";
}

Document::~Document()
{
    vector<Page *>::iterator iteratorPages = m_pages.begin();
    while (iteratorPages != m_pages.end())
    {
        delete *iteratorPages;
        iteratorPages++;
    }
    vector<PageLabel *>::iterator iteratorLavel = m_page_label.begin();
    while (iteratorLavel != m_page_label.end())
    {
        delete *iteratorLavel;
        iteratorLavel++;
    }
    vector<Font *>::iterator iteratorFonts = m_fonts.begin();
    while (iteratorFonts != m_fonts.end())
    {
        delete *iteratorFonts;
        iteratorFonts++;
    }
    if (m_outlines)
    {
        delete m_outlines;
    }
}

void Document::setTreeRoot(bool tree_root)
{
    m_tree_root = tree_root;
}

bool Document::treeRoot()
{
    return m_tree_root;
}

void Document::addFont(Font *font)
{
    m_fonts.push_back(font);
}

Font *Document::font(const char *name)
{
    vector<Font *>::iterator f = m_fonts.begin();
    while (f != m_fonts.end())
    {
        if ((*f)->name() == name)
        {
            return *f;
        }
        f++;
    }
    return nullptr;
}

void Document::setEncrypted(bool encrypt)
{
    m_encrypted = encrypt;
}

bool Document::encrypted()
{
    return m_encrypted;
}

Page *Document::page(int id, int generation)
{
    vector<Page *>::iterator iteratorPages = m_pages.begin();
    while (iteratorPages != m_pages.end())
    {
        Page *page = *iteratorPages;
        if (page->id() == id && page->generation() == generation)
        {
            return page;
        }
        iteratorPages++;
    }
    return nullptr;
}

void Document::setOutline(Outline *outline)
{
    m_outlines = outline;
}

Outline *Document::outline()
{
    return m_outlines;
}

void Document::setId(const string &first, const string &second)
{
    m_id = first + second;
}

void Document::addPage(Page *page)
{
    m_pages.push_back(page);
}

void Document::addPageLabel(PageLabel *label)
{
    m_page_label.push_back(label);
}

Page *Document::page(size_t index)
{
    return m_pages[index];
}

size_t Document::pages()
{
    return m_pages.size();
}

TreeNode *Document::rootNode()
{
    return m_root;
}

TreeNode *Document::infoNode()
{
    return m_info;
}

string Document::id()
{
    return m_id;
}

void Document::setRoot(TreeNode *root)
{
    m_root = root;
}

void Document::setInfo(TreeNode *info)
{
    m_info = info;
}

void Document::setTitle(string title)
{
    m_title = title;
}

void Document::setSubject(string subject)
{
    m_subject = subject;
}

void Document::setAuthor(string author)
{
    m_author = author;
}

void Document::setLang(string lang)
{
    if (!lang.empty())
    {
        m_lang = lang;
    }
}

string Document::lang()
{
    return m_lang;
}

string Document::title()
{
    return m_title;
}

string Document::subject()
{
    return m_subject;
}

string Document::author()
{
    return m_author;
}
