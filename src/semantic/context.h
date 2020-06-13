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
#ifndef CONTEXT_H
#define CONTEXT_H

#include <string>

class Document;

class Font;

class Page;

/**
 * Stores a context for HTML generation.
 */
class Context
{
private:
    /**
     * The document.
     */
    Document *m_document;

    /**
     * The current page.
     */
    Page *m_page;

    /**
     * The current font.
     */
    Font *m_font;

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
     * \param document the document.
     */
    explicit Context(Document *document);

    /**
     * Destroy the instance.
     */
    ~Context();

    /**
     * Sets the use of font.
     *
     * \param use_font true if use the font.
     */
    void setUseFont(bool use_font);

    /**
     * Sets if the font is changed.
     *
     * \param changed true if the font is changed.
     */
    void setFontChanged(bool changed);

    /**
     * Sets the current font.
     *
     * \param alias the font alias.
     * \param size the font size.
     */
    void setCurrentFont(std::string &alias, double size);

    /**
     * Sets the current page.
     *
     * \param page the current page.
     */
    void setCurrentPage(Page *page);

    /**
     * Sets the font size.
     *
     * \param size the font size.
     */
    void setFontSize(double size);

    /**
     * Gets if use font.
     *
     * \return true if use font.
     */
    bool useFont();

    /**
     * Gets if font is changed.
     *
     * \return true if the font changed.
     */
    bool fontChanged();

    /**
     * Gets the current font.
     *
     * \return the current font.
     */
    Font *font();

    /**
     * Gets the font size.
     *
     * \return the font size.
     */
    double fontSize();

    /**
     * Gets the document.
     *
     * \return the document.
     */
    Document *document();
};

#endif
