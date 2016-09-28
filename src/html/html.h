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

class Html
{
private:
    XML m_xml;

public:
    Html();
    ~Html();

    void startDocument();
    void startHeader();
    void startBody();

    void endDocument();
    void endTag();

    void breakLine();

    void addParagraph();
    void addFont(int size, bool bold, bool italic, bool fixed);
    void addElement(const std::string &element);
    void addSection(const std::string &name);

    void setTitle(const std::string& title);
    void setLink(const std::string& rel, const std::string& type, const std::string& href);

    inline const std::string content() const
    {
        return m_xml.content();
    }
};

#endif
