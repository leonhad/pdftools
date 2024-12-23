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
#pragma once

#include <memory>
#include <string>

class Document;

class Font;

class Page;

/**
 * Stores a context for HTML generation.
 */
class Context
{
    /**
     * The document.
     */
    std::shared_ptr<Document> m_document;

    /**
     * The current page.
     */
    std::shared_ptr<Page> m_page;

    /**
     * The current font.
     */
    std::shared_ptr<Font> m_font;

    /**
     * Is the font is changed.
     */
    bool m_font_changed;

    /**
     * If use the font.
     */
    bool m_use_font;

    /**
     * The font size.
     */
    double m_font_size;

public:
    /**
     * Creates a new instance.
     *
     * @param document the document.
     */
    explicit Context(const std::shared_ptr<Document>& document);

    /**
     * Destroy the instance.
     */
    ~Context() = default;

    /**
     * Sets the use of font.
     *
     * @param use_font true if use the font.
     */
    void SetUseFont(bool use_font);

    /**
     * Sets if the font is changed.
     *
     * @param changed true if the font is changed.
     */
    void SetFontChanged(bool changed);

    /**
     * Sets the current font.
     *
     * @param alias the font alias.
     * @param size the font size.
     */
    void SetCurrentFont(std::string& alias, double size);

    /**
     * Sets the current page.
     *
     * @param page the current page.
     */
    void SetCurrentPage(const std::shared_ptr<Page>& page);

    /**
     * Sets the font size.
     *
     * @param size the font size.
     */
    void SetFontSize(double size);

    /**
     * Gets if we use font.
     *
     * @return true if we use font.
     */
    [[nodiscard]] bool UseFont() const;

    /**
     * Gets if font is changed.
     *
     * @return true if the font changed.
     */
    [[nodiscard]] bool FontChanged() const;

    /**
     * Gets the current font.
     *
     * @return the current font.
     */
    std::shared_ptr<Font> CurrentFont();

    /**
     * Gets the font size.
     *
     * @return the font size.
     */
    [[nodiscard]] double FontSize() const;

    /**
     * Gets the document.
     *
     * @return the document.
     */
    std::shared_ptr<Document> CurrentDocument();
};
