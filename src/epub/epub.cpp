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
#include "epub.h"
#include "../xml/xml.h"
#include "../html/html.h"
#include "../zip/zipfile.h"
#include "../semantic/outline.h"
#include "../semantic/document.h"
#include "../semantic/context.h"
#include "../semantic/page.h"
#include "../../config.h"
#include <sstream>

using namespace std;

EPUB::EPUB() :
        Generator(), m_document(nullptr), m_zipfile(new ZipFile), m_order(0)
{
}

EPUB::~EPUB()
{
    if (m_zipfile)
    {
        delete m_zipfile;
    }
}

void EPUB::generateMimeType()
{
    const char *mime = "application/epub+zip";
    m_zipfile->addSource("mimetype", mime);
}

void EPUB::generateCss()
{
    stringstream css;
    css << ".b {font-weight: bold}\n";
    css << ".l {font-weight: normal}\n";
    css << ".i {font-style: italic}\n";
    css << ".n {font-style: normal}\n";
    css << ".m {font-family:courier,\"Courier New\",monospace}";
    css << ".f8 {font-size: 8pt}\n";
    css << ".f10 {font-size: 10pt}\n";
    css << ".f12 {font-size: 12pt}\n";
    css << ".f14 {font-size: 14pt}\n";
    css << ".f16 {font-size: 16pt}\n";
    css << ".f18 {font-size: 18pt}\n";
    css << "div {display:inline}\n";
    m_zipfile->addSource("style.css", css.str().c_str());
}

void EPUB::generateContainer()
{
    XML xml;
    xml.startDocument("1.0", "UTF-8");

    xml.startTag("container");
    xml.addAttribute("version", "1.0");
    xml.addAttribute("xmlns", "urn:oasis:names:tc:opendocument:xmlns:container");
    xml.startTag("rootfiles");
    xml.startTag("rootfile");
    xml.addAttribute("full-path", "content.opf");
    xml.addAttribute("media-type", "application/oebps-package+xml");
    xml.endTag();
    xml.endTag();
    xml.endTag();

    xml.endDocument();
    string content = xml.content();
    m_zipfile->addSource("META-INF/container.xml", content.c_str(), content.size());
}

void EPUB::generateContent(const string &output)
{
    XML xml;
    xml.startDocument("1.0", "UTF-8");

    xml.startTag("package");
    xml.addAttribute("xmlns", "http://www.idpf.org/2007/opf");
    xml.addAttribute("unique-identifier", "dcidid");
    xml.addAttribute("version", "2.0");

    xml.startTag("metadata");
    xml.addAttribute("xmlns:dc", "http://purl.org/dc/elements/1.1/");
    xml.addAttribute("xmlns:dcterms", "http://purl.org/dc/terms/");
    xml.addAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
    xml.addAttribute("xmlns:opf", "http://www.idpf.org/2007/opf");

    xml.startTag("dc:title");
    if (not m_document->title().empty())
    {
        xml.addElement(m_document->title().c_str());
    }
    else
    {
        xml.addElement("No title");
    }

    xml.endTag();

    xml.startTag("dc:language");
    xml.addAttribute("xsi:type", "dcterms:RFC3066");
    xml.addElement(m_document->lang().c_str());
    xml.endTag();

    xml.startTag("dc:identifier");
    xml.addAttribute("id", "dcidid");
    xml.addAttribute("opf:scheme", "URI");
    xml.addElement(output);
    xml.endTag();

    xml.startTag("dc:subject");
    xml.addElement(m_document->subject().c_str());
    xml.endTag();

    xml.startTag("dc:relation");
    xml.addElement(PACKAGE_URL);
    xml.endTag();

    xml.startTag("dc:creator");
    if (m_document->author().empty())
    {
        xml.addElement(PACKAGE_STRING);
    }
    else
    {
        xml.addElement(m_document->author().c_str());
    }

    xml.endTag();

    xml.startTag("dc:publisher");
    xml.addElement(PACKAGE_STRING);
    xml.endTag();

    xml.startTag("dc:publisher");
    xml.addElement(m_document->author().c_str());
    xml.endTag();

    xml.endTag();

    xml.startTag("manifest");

    xml.startTag("item");
    xml.addAttribute("id", "ncx");
    xml.addAttribute("href", "toc.ncx");
    xml.addAttribute("media-type", "application/x-dtbncx+xml");
    xml.endTag();

    for (size_t loop = 0; loop < m_document->pages(); loop++)
    {
        Page *page = m_document->page(loop);

        xml.startTag("item");
        xml.addAttribute("id", page->link());
        xml.addAttribute("href", page->link() + ".html");
        xml.addAttribute("media-type", "application/xhtml+xml");
        xml.endTag();
    }

    xml.startTag("item");
    xml.addAttribute("id", "css");
    xml.addAttribute("href", "style.css");
    xml.addAttribute("media-type", "text/css");
    xml.endTag();

    xml.endTag();

    xml.startTag("spine");
    xml.addAttribute("toc", "ncx");

    for (size_t loop = 0; loop < m_document->pages(); loop++)
    {
        Page *page = m_document->page(loop);

        xml.startTag("itemref");
        xml.addAttribute("idref", page->link());
        xml.addAttribute("linear", "yes");
        xml.endTag();
    }

    xml.endTag();

    xml.endTag();
    xml.endDocument();
    string content = xml.content();
    m_zipfile->addSource("content.opf", content.c_str());
}

void EPUB::generateOutline(XML *xml, Outline *outline)
{
    Page *page = m_document->page(outline->id(), outline->generation());

    if (page)
    {
        string playorder
        { to_string(m_order) };
        m_order++;

        xml->startTag("navPoint");
        xml->addAttribute("id", playorder);

        xml->startTag("navLabel");
        xml->startTag("text");
        xml->addElement(outline->title());
        xml->endTag();
        xml->endTag();

        xml->startTag("content");
        xml->addAttribute("src", page->link() + ".html");
        xml->endTag();
    }

    size_t size = outline->size();
    for (size_t loop = 0; loop < size; loop++)
    {
        generateOutline(xml, outline->child(loop));
    }

    if (page)
    {
        xml->endTag();
    }
}

void EPUB::generateToc(const string &output)
{
    Outline *outline = m_document->outline();

    XML xml;
    xml.startDocument("1.0", "UTF-8");

    xml.startTag("ncx");
    xml.addAttribute("xmlns", "http://www.daisy.org/z3986/2005/ncx/");
    xml.addAttribute("version", "2005-1");

    xml.startTag("head");
    xml.startTag("meta");
    xml.addAttribute("name", "dtb:uid");
    xml.addAttribute("content", output);
    xml.endTag();
    xml.startTag("meta");
    xml.addAttribute("name", "dtb:depth");
    xml.addAttribute("content", "2");
    xml.endTag();
    xml.startTag("meta");
    xml.addAttribute("name", "dtb:totalPageCount");
    xml.addAttribute("content", "0");
    xml.endTag();
    xml.startTag("meta");
    xml.addAttribute("name", "dtb:maxPageNumber");
    xml.addAttribute("content", "0");
    xml.endTag();
    xml.endTag();

    xml.startTag("docTitle");
    xml.startTag("text");
    xml.addElement(m_document->title());
    xml.endTag();
    xml.endTag();

    xml.startTag("navMap");
    if (outline)
    {
        generateOutline(&xml, outline);
    }
    else
    {
        xml.startTag("navPoint");
        xml.addAttribute("id", "navPoint-1");
        xml.addAttribute("playOrder", "1");

        xml.startTag("navLabel");
        xml.startTag("text");
        xml.addElement("Main Title");
        xml.endTag();
        xml.endTag();

        xml.startTag("content");
        xml.addAttribute("src", "pages.html");
        xml.endTag();
        xml.endTag();
    }

    xml.endTag();

    xml.endTag();
    xml.endDocument();
    string content = xml.content();

    m_zipfile->addSource("toc.ncx", content.c_str());
}

void EPUB::generatePages()
{
    size_t size = m_document->pages();
    for (size_t i = 0; i < size; i++)
    {
        Page *page = m_document->page(i);

        Html html;
        html.startDocument();
        html.startHeader();
        html.setTitle(m_document->title());
        html.addLink("stylesheet", "text/css", "style.css");
        html.endTag();
        html.startBody();

        page->execute(&html);

        html.endTag();
        html.endDocument();

        string fileout
        { page->link() + ".html" };
        m_zipfile->addSource(fileout.c_str(), html.content().c_str(), html.content().size());
    }
}

bool EPUB::generate(Document *document, const string &output)
{
    m_document = document;
    m_order = 1;
    if (m_zipfile->open(output))
    {
        generateMimeType();
        generateCss();
        generateContainer();
        generateContent(output);
        generateToc(output);
        generatePages();
        m_zipfile->close();
    }
    else
    {
        return false;
    }

    return true;
}
