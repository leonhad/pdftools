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
#include "xmltag.h"
#include <sstream>

using namespace std;

XmlTag::XmlTag(const string &name) :
        m_name(name)
{
}

XmlTag::~XmlTag()
{
    for (XmlTag *tag : m_children)
    {
        delete tag;
    }
}

string XmlTag::Name() const
{
    return m_name;
}

std::string XmlTag::ToXML() const
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
        buffer << tag->ToXML();
    }

    buffer << "</" << m_name << ">" << endl;
    return buffer.str();
}

XmlTag *XmlTag::Parent() const
{
    return m_parent;
}

void XmlTag::SetParent(XmlTag *parent)
{
    m_parent = parent;
}

void XmlTag::AddTag(XmlTag *tag)
{
    m_children.push_back(tag);
}

void XmlTag::AddAttribute(const std::string &id, const std::string &value)
{
    m_atributes [id] = value;
}
