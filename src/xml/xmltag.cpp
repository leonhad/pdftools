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

XmlTag::XmlTag(string name) noexcept: m_name(name)
{
}

XmlTag::~XmlTag() noexcept
{
    for (XmlTag *tag : m_children) {
        delete tag;
    }
}

string XmlTag::name() const noexcept
{
    return m_name;
}

std::string XmlTag::to_XML() const noexcept
{
    stringstream buffer;
    buffer << "<" << m_name;

    for (const auto &value : m_atributes) {
        buffer << " " << value.first << "=\"" << value.second << "\"";
    }

    buffer << ">";

    for (XmlTag *tag : m_children) {
        buffer << tag->to_XML();
    }

    buffer << "</" << m_name << ">" << endl;
    return buffer.str();
}

XmlTag *XmlTag::parent() const noexcept
{
    return m_parent;
}

void XmlTag::set_parent(XmlTag *parent) noexcept
{
    m_parent = parent;
}

void XmlTag::add_tag(XmlTag *tag) noexcept
{
    m_children.push_back(tag);
}

void XmlTag::add_attribute(const std::string& id, const std::string& value) noexcept
{
    m_atributes[id] = value;
}
