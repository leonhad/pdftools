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
    xml.startDocument("1.0", "UTF-8");
    xml.addDoctype("html", "-//W3C//DTD XHTML 1.1//EN",
            "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd");
}

Html::~Html()
{
}

void Html::BreakLine()
{
    xml.startTag("br");
    xml.endTag();
}

void Html::AddParagraph()
{
    xml.startTag("p");
}

void Html::StartHeader()
{
    xml.startTag("head");
}

void Html::StartBody()
{
    xml.startTag("body");
}

void Html::SetTitle(const string& title)
{
    xml.startTag("title");
    xml.addElement(title);
    xml.endTag();
}

void Html::AddFont(int size, bool bold, bool italic, bool fixed)
{
    xml.startTag("div");

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

    xml.addAttribute("class", css.str());
}

void Html::AddLink(const string &rel, const string &type, const string &href)
{
    xml.startTag("link");
    xml.addAttribute("rel", rel);
    xml.addAttribute("type", type);
    xml.addAttribute("href", href);
    xml.endTag();
}

void Html::AddElement(const string& value)
{
    xml.addElement(value);
}

void Html::AddSection(const std::string &name)
{
    xml.startTag("div");
    xml.addAttribute("class", "section");
    xml.addAttribute("id", name);
}

void Html::EndTag()
{
    xml.endTag();
}

void Html::StartDocument()
{
    xml.startTag("html");
    xml.addAttribute("xmlns", "http://www.w3.org/1999/xhtml");
}

void Html::EndDocument()
{
    EndTag();
    xml.endDocument();
}
