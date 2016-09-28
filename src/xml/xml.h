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
#ifndef XML_H
#define XML_H

#include "xmltag.h"
#include <string>

class XML
{
private:
    XmlTag *m_root = nullptr;
    XmlTag *m_last_tag = nullptr;
    std::string m_version;
    std::string m_charset;

    std::string m_doctype_name;
    std::string m_public_id;
    std::string m_sys_id;

public:
    XML();
    ~XML();

    void startDocument(const std::string& version, const std::string& charset);
    void addDoctype(const std::string& name, const std::string& public_id, const std::string& sys_id);
    void addAttribute(const std::string& id, const std::string& value);
    void addElement(const std::string& value);
    void startTag(const std::string& tag_name);
    void endTag();
    void endDocument();
    const std::string content() const;
};

#endif
