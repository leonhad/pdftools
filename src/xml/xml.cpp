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
#include "xml.h"
#include "element.h"
#include <sstream>

using namespace std;

string XML::Content() const
{
    stringstream m_buffer;
    m_buffer << "<?xml version=\"" << m_version << "\" encoding=\"" << m_charset << "\"?>" << endl;
    if (not m_doctype_name.empty())
    {
        m_buffer << "<!DOCTYPE " << m_doctype_name;
        if (not m_public_id.empty())
        {
            m_buffer << " PUBLIC \"" << m_public_id << "\"";
        }
        if (not m_sys_id.empty())
        {
            m_buffer << " \"" << m_sys_id << "\"";
        }
        m_buffer << ">" << endl;
    }

    if (m_root)
    {
        m_buffer << m_root->ToXML();
    }

    return m_buffer.str();
}

void XML::StartDocument(const string& version, const string& charset)
{
    m_version = version;
    m_charset = charset;
}

void XML::SetDoctype(const string& name, const string& public_id, const string& sys_id)
{
    m_doctype_name = name;
    m_public_id = public_id;
    m_sys_id = sys_id;
}

void XML::EndDocument()
{
}

void XML::AddAttribute(const string& id, const string& value) const
{
    m_last_tag.back()->AddAttribute(id, value);
}

void XML::AddElement(const string& value) const
{
    m_last_tag.back()->AddTag(new Element(value));
}

void XML::StartTag(const string& tag_name)
{
    const auto tag = new XmlTag{tag_name};
    if (not m_root)
    {
        m_root = shared_ptr<XmlTag>(tag);
    }
    else
    {
        m_last_tag.back()->AddTag(tag);
    }

    m_last_tag.push_back(tag);
}

void XML::EndTag()
{
    m_last_tag.pop_back();
}
