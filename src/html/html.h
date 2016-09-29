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
#ifndef HTML_H
#define HTML_H

#include "xml/xml.h"
#include <string>

/**
 * Generates a Html file.
 */
class Html
{
private:
    /**
     * The XML genetator.
     */
    XML m_xml;

public:
    /**
     * Creates a new instance.
     */
    Html();

    /**
     * Destroy the instance.
     */
    ~Html();

    /**
     * Starts the document.
     */
    void startDocument();

    /**
     * Starts the header section.
     */
    void startHeader();

    /**
     * Starts the body section.
     */
    void startBody();

    /**
     * Closes the document.
     */
    void endDocument();

    /**
     * Closes the current tag.
     */
    void endTag();

    /**
     * Add a break line.
     */
    void breakLine();

    /**
     * Add a paragraph tag.
     */
    void addParagraph();

    /**
     * Add a font tag.
     *
     * \param size the font size.
     * \param bold if the font has a bold modifier.
     * \param italic if the font has a italic modifier.
     * \param fixed  if the font has a fixed face modifier.
     */
    void addFont(int size, bool bold, bool italic, bool fixed);

    /**
     * Add a tag by its name.
     *
     * @param element the tag name.
     */
    void addElement(const std::string &element);

    /**
     * Add a section by its name.
     *
     * @param name the section name.
     */
    void addSection(const std::string &name);

    /**
     * Sets the document title.
     *
     * @param title the document title.
     */
    void setTitle(const std::string &title);

    /**
     * Add a link reference.
     *
     * \param rel the rel value.
     * \param type the link type.
     * \param href the link href.
     */
    void addLink(const std::string &rel, const std::string &type, const std::string &href);

    /**
     * Gets the HTML content.
     *
     * \return the HTML content.
     */
    inline const std::string content() const
    {
        return m_xml.content();
    }
};

#endif
