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
#ifndef XMLTAG_H
#define XMLTAG_H

#include <string>
#include <vector>
#include <map>

class XmlTag
{
protected:
    std::string m_name;
    std::vector<XmlTag *> m_children;
    std::map<std::string, std::string> m_atributes;

    XmlTag *m_parent = nullptr;

public:
    XmlTag(const std::string &name);
    virtual ~XmlTag();

    std::string name() const;
    virtual std::string toXML() const;
    XmlTag *parent() const;

    void setParent(XmlTag *parent);
    void addTag(XmlTag *tag);
    void addAttribute(const std::string &id, const std::string &value);
};

#endif // XMLTAG_H
