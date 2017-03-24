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
    m_xml.startDocument("1.0", "UTF-8");
    m_xml.addDoctype("html", "-//W3C//DTD XHTML 1.1//EN",
            "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd");
}

Html::~Html()
{
}

void Html::breakLine()
{
    m_xml.startTag("br");
    m_xml.endTag();
}

void Html::addParagraph()
{
    m_xml.startTag("p");
}

void Html::startHeader()
{
    m_xml.startTag("head");
}

void Html::startBody()
{
    m_xml.startTag("body");
}

void Html::setTitle(const string& title)
{
    m_xml.startTag("title");
    m_xml.addElement(title);
    m_xml.endTag();
}

void Html::addFont(int size, bool bold, bool italic, bool fixed)
{
    m_xml.startTag("div");

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

    m_xml.addAttribute("class", css.str());
}

void Html::addLink(const string &rel, const string &type, const string &href)
{
    m_xml.startTag("link");
    m_xml.addAttribute("rel", rel);
    m_xml.addAttribute("type", type);
    m_xml.addAttribute("href", href);
    m_xml.endTag();
}

void Html::addElement(const string& value)
{
    m_xml.addElement(value);
}

void Html::addSection(const std::string &name)
{
    m_xml.startTag("div");
    m_xml.addAttribute("class", "section");
    m_xml.addAttribute("id", name);
}

void Html::endTag()
{
    m_xml.endTag();
}

void Html::startDocument()
{
    m_xml.startTag("html");
    m_xml.addAttribute("xmlns", "http://www.w3.org/1999/xhtml");
}

void Html::endDocument()
{
    endTag();
    m_xml.endDocument();
}
