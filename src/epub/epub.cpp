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
#include "epub.h"
#include "../utils.h"
#include "../xml/xml.h"
#include "../html/html.h"
#include "../zip/zipfile.h"
#include "../semantic/outline.h"
#include "../semantic/document.h"
#include "../semantic/context.h"
#include "../semantic/page.h"
#include <config.h>
#include <cstring>
#include <iostream>
#include <sstream>

using namespace std;

EPUB::EPUB() : Generator(), m_document(nullptr), m_zipfile(new ZipFile), m_order(0)
{
}

EPUB::~EPUB()
{
    if (m_zipfile)
    {
        delete m_zipfile;
    }
}

void EPUB::generate_mimetype()
{
    const char *mime = "application/epub+zip";
    m_zipfile->add_source("mimetype", mime);
}

void EPUB::generate_css()
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
    m_zipfile->add_source("style.css", css.str().c_str());
}

void EPUB::generate_container()
{
    XML xml;
    xml.start_document("1.0", "UTF-8");

    xml.start_tag("container");
    xml.add_attribute("version", "1.0");
    xml.add_attribute("xmlns", "urn:oasis:names:tc:opendocument:xmlns:container");
    xml.start_tag("rootfiles");
    xml.start_tag("rootfile");
    xml.add_attribute("full-path", "content.opf");
    xml.add_attribute("media-type", "application/oebps-package+xml");
    xml.end_tag();
    xml.end_tag();
    xml.end_tag();

    xml.end_document();
    string content = xml.content();
    m_zipfile->add_source("META-INF/container.xml", content.c_str(), content.size());
}

void EPUB::generate_content(const string& output)
{
    XML xml;
    xml.start_document("1.0", "UTF-8");

    xml.start_tag("package");
    xml.add_attribute("xmlns", "http://www.idpf.org/2007/opf");
    xml.add_attribute("unique-identifier", "dcidid");
    xml.add_attribute("version", "2.0");

    xml.start_tag("metadata");
    xml.add_attribute("xmlns:dc", "http://purl.org/dc/elements/1.1/");
    xml.add_attribute("xmlns:dcterms", "http://purl.org/dc/terms/");
    xml.add_attribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
    xml.add_attribute("xmlns:opf", "http://www.idpf.org/2007/opf");

    xml.start_tag("dc:title");
    if (!m_document->title().empty())
    {
        xml.add_element(m_document->title().c_str());
    }
    else
    {
        xml.add_element("No title");
    }

    xml.end_tag();

    xml.start_tag("dc:language");
    xml.add_attribute("xsi:type", "dcterms:RFC3066");
    xml.add_element(m_document->lang().c_str());
    xml.end_tag();

    xml.start_tag("dc:identifier");
    xml.add_attribute("id", "dcidid");
    xml.add_attribute("opf:scheme", "URI");
    xml.add_element(output);
    xml.end_tag();

    xml.start_tag("dc:subject");
    xml.add_element(m_document->subject().c_str());
    xml.end_tag();

    xml.start_tag("dc:relation");
    xml.add_element(PACKAGE_URL);
    xml.end_tag();

    xml.start_tag("dc:creator");
    if (m_document->author().empty())
    {
        xml.add_element(PACKAGE_STRING);
    }
    else
    {
        xml.add_element(m_document->author().c_str());
    }

    xml.end_tag();

    xml.start_tag("dc:publisher");
    xml.add_element(PACKAGE_STRING);
    xml.end_tag();

    xml.start_tag("dc:publisher");
    xml.add_element(m_document->author().c_str());
    xml.end_tag();

    xml.end_tag();

    xml.start_tag("manifest");

    xml.start_tag("item");
    xml.add_attribute("id", "ncx");
    xml.add_attribute("href", "toc.ncx");
    xml.add_attribute("media-type", "application/x-dtbncx+xml");
    xml.end_tag();

    for (size_t loop = 0; loop < m_document->pages(); loop++)
    {
        Page *page = m_document->page(loop);

        xml.start_tag("item");
        xml.add_attribute("id", page->link());
        xml.add_attribute("href", page->link() + ".html");
        xml.add_attribute("media-type", "application/xhtml+xml");
        xml.end_tag();
    }

    xml.start_tag("item");
    xml.add_attribute("id", "css");
    xml.add_attribute("href", "style.css");
    xml.add_attribute("media-type", "text/css");
    xml.end_tag();
    
    xml.end_tag();

    xml.start_tag("spine");
    xml.add_attribute("toc", "ncx");

    for (size_t loop = 0; loop < m_document->pages(); loop++)
    {
        Page *page = m_document->page(loop);

        xml.start_tag("itemref");
        xml.add_attribute("idref", page->link());
        xml.add_attribute("linear", "yes");
        xml.end_tag();
    }

    xml.end_tag();

    xml.end_tag();
    xml.end_document();
    string content = xml.content();
    m_zipfile->add_source("content.opf", content.c_str());
}

void EPUB::generate_outline(XML *xml, Outline *outline)
{
    Page *page = m_document->page(outline->id(), outline->generation());

    if (page)
    {
        string playorder{to_string(m_order)};
        string id{"navPoint-" + playorder};
        m_order++;

        xml->start_tag("navPoint");
        xml->add_attribute("id", playorder);

        xml->start_tag("navLabel");
        xml->start_tag("text");
        xml->add_element(outline->title());
        xml->end_tag();
        xml->end_tag();

        xml->start_tag("content");
        xml->add_attribute("src", page->link() + ".html");
        xml->end_tag();
    }

    size_t size = outline->size();
    for (size_t loop = 0; loop < size; loop++)
    {
        generate_outline(xml, outline->child(loop));
    }

    if (page)
    {
        xml->end_tag();
    }
}

void EPUB::generate_toc(const string& output)
{
    Outline *outline = m_document->outline();

    XML xml;
    xml.start_document("1.0", "UTF-8");

    xml.start_tag("ncx");
    xml.add_attribute("xmlns", "http://www.daisy.org/z3986/2005/ncx/");
    xml.add_attribute("version", "2005-1");

    xml.start_tag("head");
    xml.start_tag("meta");
    xml.add_attribute("name", "dtb:uid");
    xml.add_attribute("content", output);
    xml.end_tag();
    xml.start_tag("meta");
    xml.add_attribute("name", "dtb:depth");
    xml.add_attribute("content", "2");
    xml.end_tag();
    xml.start_tag("meta");
    xml.add_attribute("name", "dtb:totalPageCount");
    xml.add_attribute("content", "0");
    xml.end_tag();
    xml.start_tag("meta");
    xml.add_attribute("name", "dtb:maxPageNumber");
    xml.add_attribute("content", "0");
    xml.end_tag();
    xml.end_tag();

    xml.start_tag("docTitle");
    xml.start_tag("text");
    xml.add_element(m_document->title());
    xml.end_tag();
    xml.end_tag();

    xml.start_tag("navMap");
    if (outline)
    {
        generate_outline(&xml, outline);
    }
    else
    {
        xml.start_tag("navPoint");
        xml.add_attribute("id", "navPoint-1");
        xml.add_attribute("playOrder", "1");

        xml.start_tag("navLabel");
        xml.start_tag("text");
        xml.add_element("Main Title");
        xml.end_tag();
        xml.end_tag();

        xml.start_tag("content");
        xml.add_attribute("src", "pages.html");
        xml.end_tag();
        xml.end_tag();
    }

    xml.end_tag();

    xml.end_tag();
    xml.end_document();
    string content = xml.content();

    m_zipfile->add_source("toc.ncx", content.c_str());
}

void EPUB::generate_pages()
{
    size_t size = m_document->pages();
    for (size_t i = 0; i < size; i++)
    {
        Page *page = m_document->page(i);

        Html html;
        html.start_document();
        html.start_header();
        html.set_title(m_document->title());
        html.set_link("stylesheet", "text/css", "style.css");
        html.end_tag();
        html.start_body();

        page->execute(&html);

        html.end_tag();
        html.end_document();

        string fileout{page->link() + ".html"};
        m_zipfile->add_source(fileout.c_str(), html.content().c_str(), html.content().size());
    }
}

void EPUB::generate_page(Page *page)
{
    Html html;
    html.start_document();
    html.start_header();
    html.set_title("Page title.");
    html.end_tag();

    html.start_body();

    page->execute(&html);

    html.end_tag();
    html.end_document();

    m_zipfile->add_source(page->link().c_str(), html.content().c_str(), html.content().length());
}

bool EPUB::generate(Document* document, const string& output)
{
    m_document = document;
    m_order = 1;
    if (m_zipfile->open(output))
    {
        generate_mimetype();
        generate_css();
        generate_container();
        generate_content(output);
        generate_toc(output);
        generate_pages();
        m_zipfile->close();
    }
    else
    {
        return false;
    }

    return true;
}
