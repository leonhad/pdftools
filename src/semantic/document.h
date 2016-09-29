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
#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <vector>

class Font;
class Outline;
class Page;
class PageLabel;

namespace node
{
    class TreeNode;
}

class Document
{
private:
    bool m_encrypted;
    bool m_tree_root;
    std::string m_id;
    std::string m_title;
    std::string m_subject;
    std::string m_author;
    std::string m_lang;
    node::TreeNode *m_root;
    node::TreeNode *m_info;
    Outline *m_outlines;
    std::vector<Font *> m_fonts;
    std::vector<Page *> m_pages;
    std::vector<PageLabel *> m_page_label;

public:
    Document();
    ~Document();

    void setId(const std::string &first, const std::string &second);
    void setRoot(node::TreeNode *root);
    void setInfo(node::TreeNode *info);
    void setEncrypted(bool encrypt);
    void setTreeRoot(bool tree_root);

    void setTitle(std::string title);
    void setSubject(std::string subject);
    void setAuthor(std::string author);
    void setLang(std::string lang);

    void setOutline(Outline *outline);
    Outline *outline();

    void addFont(Font *font);
    Font *font(const char *name);

    void addPage(Page *page);
    void addPageLabel(PageLabel *label);
    Page *page(size_t index);
    size_t pages();
    Page *page(int id, int generation);

    bool encrypted();
    bool treeRoot();
    std::string lang();
    std::string id();
    std::string title();
    std::string subject();
    std::string author();
    node::TreeNode *rootNode();
    node::TreeNode *infoNode();
};

#endif
