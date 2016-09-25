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
#include "xml.h"
#include "element.h"
#include <sstream>
#include <stdexcept>
#include <vector>

using namespace std;

XML::XML()
{
}

XML::~XML()
{
    if (m_root)
    {
        delete m_root;
    }
}

const string XML::content() const
{
    stringstream m_buffer;
    m_buffer << "<?xml version=\"" << m_version << "\" encoding=\"" << m_charset << "\"?>" << endl;
    if (!m_doctype_name.empty())
    {
        m_buffer << "<!DOCTYPE " << m_doctype_name;
        if (!m_public_id.empty())
        {
            m_buffer << " PUBLIC \"" << m_public_id << "\"";
        }
        if (!m_sys_id.empty())
        {
            m_buffer << " \"" << m_sys_id << "\"";
        }
        m_buffer << ">" << endl;
    }
    if (m_root)
    {
        m_buffer << m_root->toXML();
    }
    return m_buffer.str();
}

void XML::startDocument(const string& version, const string& charset)
{
    m_version = version;
    m_charset = charset;
}

void XML::addDoctype(const string& name, const string& public_id, const string& sys_id)
{
    m_doctype_name = name;
    m_public_id = public_id;
    m_sys_id = sys_id;
}

void XML::endDocument()
{
}

void XML::addAttribute(const string& id, const string& value)
{
    if (m_last_tag)
    {
        m_last_tag->add_attribute(id, value);
    }
}

void XML::addElement(const string& value)
{
    if (m_last_tag)
    {
        m_last_tag->add_tag(new Element(value));
    }
}

void XML::startTag(const string& tag_name)
{
    XmlTag *tag = new XmlTag{tag_name};
    if (!m_root)
    {
        m_root = tag;
    }
    if (m_last_tag)
    {
        m_last_tag->add_tag(tag);
        tag->set_parent(m_last_tag);
    }
    m_last_tag = tag;
}

void XML::endTag()
{
    if (m_last_tag)
    {
        m_last_tag = m_last_tag->parent();
    }
}
