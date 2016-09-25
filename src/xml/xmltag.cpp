/*
 * PDF Tools.
 * Copyright (C) 2012-2016 Leonardo Alves da Costa
 * mailto:leonhad AT gmail DOT com
 *
 * SonarQube is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * SonarQube is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#include "xmltag.h"
#include <sstream>

using namespace std;

XmlTag::XmlTag(string name) : m_name(name)
{
}

XmlTag::~XmlTag()
{
    for (XmlTag *tag : m_children)
    {
        delete tag;
    }
}

string XmlTag::name() const
{
    return m_name;
}

std::string XmlTag::toXML() const
{
    stringstream buffer;
    buffer << "<" << m_name;

    for (const auto &value : m_atributes)
    {
        buffer << " " << value.first << "=\"" << value.second << "\"";
    }

    buffer << ">";

    for (XmlTag *tag : m_children)
    {
        buffer << tag->toXML();
    }

    buffer << "</" << m_name << ">" << endl;
    return buffer.str();
}

XmlTag *XmlTag::parent() const
{
    return m_parent;
}

void XmlTag::set_parent(XmlTag *parent)
{
    m_parent = parent;
}

void XmlTag::add_tag(XmlTag *tag)
{
    m_children.push_back(tag);
}

void XmlTag::add_attribute(const std::string& id, const std::string& value)
{
    m_atributes[id] = value;
}
