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
#include "html.h"
#include <sstream>

using namespace std;

Html::Html()
{
    m_xml.start_document("1.0", "UTF-8");
    m_xml.add_doctype("html", "-//W3C//DTD XHTML 1.1//EN", "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd");
}

Html::~Html()
{
}

void Html::break_line()
{
    m_xml.start_tag("br");
    m_xml.end_tag();
}

void Html::add_paragraph()
{
    m_xml.start_tag("p");
}

void Html::start_header()
{
    m_xml.start_tag("head");
}

void Html::start_body()
{
    m_xml.start_tag("body");
}

void Html::set_title(const string& title)
{
    m_xml.start_tag("title");
    m_xml.add_element(title);
    m_xml.end_tag();
}

void Html::add_font(int size, bool bold, bool italic, bool fixed)
{
    m_xml.start_tag("div");

    stringstream css;
    if (size <= 8)
    {
        css << "f8";
    }
    else if (size <= 10)
    {
        css << "f10";
    }
    else if (size <= 12)
    {
        css << "f12";
    }
    else if (size <= 14)
    {
        css << "f14";
    }
    else if (size <= 16)
    {
        css << "f16";
    }
    else
    {
        css << "f18";
    }

    if (italic)
    {
        css << " i";
    }
    else
    {
        css << " n";
    }

    if (bold)
    {
        css << " b";
    }
    else
    {
        css << " l";
    }

    if (fixed)
    {
        css << " m";
    }

    m_xml.add_attribute("class", css.str());
}

void Html::set_link(const string& rel, const string& type, const string& href)
{
    m_xml.start_tag("link");
    m_xml.add_attribute("rel", rel);
    m_xml.add_attribute("type", type);
    m_xml.add_attribute("href", href);
    m_xml.end_tag();
}

void Html::add_element(const string& value)
{
    m_xml.add_element(value);
}

void Html::add_section(const std::string &name)
{
    m_xml.start_tag("div");
    m_xml.add_attribute("class", "section");
    m_xml.add_attribute("id", name);
}

void Html::end_tag()
{
    m_xml.end_tag();
}

void Html::start_document()
{
    m_xml.start_tag("html");
    m_xml.add_attribute("xmlns", "http://www.w3.org/1999/xhtml");
}

void Html::end_document()
{
    end_tag();
    m_xml.end_document();
}
