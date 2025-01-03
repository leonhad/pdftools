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
#include <utility>

using namespace std;

XmlTag::XmlTag(string name) : m_name(std::move(name))
{
}

string XmlTag::Name() const
{
    return m_name;
}

std::string XmlTag::ToXML() const
{
    stringstream buffer;
    buffer << "<" << m_name;

    for (const auto& [fst, snd] : m_attributes)
    {
        buffer << " " << fst << "=\"" << snd << "\"";
    }

    buffer << ">";

    for (const auto& tag : m_children)
    {
        buffer << tag->ToXML();
    }

    buffer << "</" << m_name << ">" << endl;
    return buffer.str();
}

void XmlTag::AddTag(XmlTag* tag)
{
    m_children.push_back(shared_ptr<XmlTag>(tag));
}

void XmlTag::AddAttribute(const std::string& id, const std::string& value)
{
    m_attributes[id] = value;
}
