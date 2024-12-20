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

#include <memory>
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

/**
 * Stores a PDF document.
 */
class Document
{
private:
    /**
     * If the file is encrypted.
     */
    bool m_encrypted;

    /**
     * Stores the tree root parsed.
     */
    bool m_tree_root;

    /**
     * Stores the document id.
     */
    std::string m_id;

    /**
     * The document title.
     */
    std::string m_title;

    /**
     * The document subject.
     */
    std::string m_subject;

    /**
     * The document author.
     */
    std::string m_author;

    /**
     * The document language.
     */
    std::string m_lang;

    /**
     * Stores the document tree root.
     */
    std::shared_ptr<node::TreeNode> m_root;

    /**
     * Stores the document info node.
     */
    std::shared_ptr<node::TreeNode> m_info;

    /**
     * Stores the document outlines.
     */
    std::shared_ptr<Outline> m_outline;

    /**
     * The list of document fonts.
     */
    std::vector<std::shared_ptr<Font>> m_fonts;

    /**
     * The list of document pages.
     */
    std::vector<std::shared_ptr<Page>> m_pages;

    /**
     * The list of document page labels.
     */
    std::vector<std::shared_ptr<PageLabel>> m_page_label;

public:
    /**
     * Creates a new instance.
     */
    Document();

    /**
     * Destroy this instance.
     */
    ~Document() = default;

    /**
     * Sets the document id.
     *
     * @param id the id.
     * @param generation the generation.
     */
    void setId(const std::string &id, const std::string &generation);

    /**
     * Sets the document tree root.
     *
     * @param root the document tree root.
     */
    void SetRoot(node::TreeNode &root);

    /**
     * Sets the document info node.
     *
     * @param info the document info node.
     */
    void SetInfo(node::TreeNode &info);

    /**
     * Sets if the document is encrypted.
     *
     * @param encrypt true if the document is encrypted.
     */
    void SetEncrypted(bool encrypt);

    /**
     * Sets if the document tree root is parsed.
     *
     * @param tree_root true if the document tree root is parsed.
     */
    void SetTreeRoot(bool tree_root);

    /**
     * Sets the document title.
     *
     * @param title the document title.
     */
    void SetTitle(const std::string& title);

    /**
     * Sets the document subject.
     *
     * @param subject the document subject.
     */
    void SetSubject(const std::string& subject);

    /**
     * Sets the document author.
     *
     * @param author the document author.
     */
    void SetAuthor(const std::string& author);

    /**
     * Sets the document language.
     *
     * @param lang the document language.
     */
    void SetLang(const std::string& lang);

    /**
     * Sets the document outline.
     *
     * @param outline the document outline.
     */
    void SetOutline(std::shared_ptr<Outline> outline);

    /**
     * Gets the document outline.
     *
     * @return the document outline.
     */
    [[nodiscard]] std::shared_ptr<Outline> CurrentOutline() const;

    /**
     * Add a font to this document.
     *
     * @param font the font to add.
     */
    void AddFont(const std::shared_ptr<Font>& font);

    /**
     * Get a font by its name.
     *
     * @param name the font name.
     * @return the font by name.
     */
    std::shared_ptr<Font> CurrentFont(const std::string &name);

    /**
     * Adds a page to this document.
     *
     * @param page the page to add.
     */
    void AddPage(const std::shared_ptr<Page>& page);

    /**
     * Adds a page label to this document.
     *
     * @param label the page label to add.
     */
    void AddPageLabel(const std::shared_ptr<PageLabel>& label);

    /**
     * Gets a page by index.
     *
     * @param index the page index.
     * @return the page by index.
     */
    [[nodiscard]] std::shared_ptr<Page> CurrentPage(size_t index) const;

    /**
     * Gets the total count of document pages.
     *
     * @return the total count of document pages.
     */
    [[nodiscard]] size_t Pages() const;

    /**
     * Gets a page by its id.
     *
     * @param id the page id.
     * @param generation the page generation.
     * @return the page.
     */
    std::shared_ptr<Page> CurrentPage(int id, int generation);

    /**
     * Gets if this document is encrypted.
     *
     * @return true if this document is encrypted.
     */
    [[nodiscard]] bool Encrypted() const;

    /**
     * Gets if the tree node is parsed.
     *
     * @return true if the tree node is parsed.
     */
    [[nodiscard]] bool TreeRoot() const;

    /**
     * Gets the page language.
     *
     * @return the page language.
     */
    std::string Lang();

    /**
     * Gets the document id.
     *
     * @return the document id.
     */
    std::string Id();

    /**
     * Gets the document title.
     *
     * @return the document title.
     */
    std::string Title();

    /**
     * Gets the document subject.
     *
     * @return the document subject.
     */
    std::string Subject();

    /**
     * Gets the document author.
     *
     * @return the document author.
     */
    std::string Author();

    /**
     * Gets the document root node.
     *
     * @return the document root node.
     */
    std::shared_ptr<node::TreeNode> RootNode();

    /**
     * Gets the document info node.
     *
     * @return the document info node.
     */
    std::shared_ptr<node::TreeNode> InfoNode();
};

#endif
