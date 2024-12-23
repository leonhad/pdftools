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
#include "html.h"
#include <sstream>

using namespace std;

Html::Html()
{
    m_xml.StartDocument("1.0", "UTF-8");
    m_xml.SetDoctype("html", "-//W3C//DTD XHTML 1.1//EN",
            "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd");
}

void Html::BreakLine()
{
    m_xml.StartTag("br");
    m_xml.EndTag();
}

void Html::AddParagraph()
{
    m_xml.StartTag("p");
}

void Html::StartHeader()
{
    m_xml.StartTag("head");
}

void Html::StartBody()
{
    m_xml.StartTag("body");
}

void Html::SetTitle(const string& title)
{
    m_xml.StartTag("title");
    m_xml.AddElement(title);
    m_xml.EndTag();
}

void Html::AddFont(const double size, const bool bold, const bool italic, const bool fixed)
{
    m_xml.StartTag("div");

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

    m_xml.AddAttribute("class", css.str());
}

void Html::AddLink(const string &rel, const string &type, const string &href)
{
    m_xml.StartTag("link");
    m_xml.AddAttribute("rel", rel);
    m_xml.AddAttribute("type", type);
    m_xml.AddAttribute("href", href);
    m_xml.EndTag();
}

void Html::AddElement(const string& value)
{
    m_xml.AddElement(value);
}

void Html::AddSection(const std::string &name)
{
    m_xml.StartTag("div");
    m_xml.AddAttribute("class", "section");
    m_xml.AddAttribute("id", name);
}

void Html::EndTag()
{
    m_xml.EndTag();
}

void Html::StartDocument()
{
    m_xml.StartTag("html");
    m_xml.AddAttribute("xmlns", "http://www.w3.org/1999/xhtml");
}

void Html::EndDocument()
{
    EndTag();
    m_xml.EndDocument();
}
