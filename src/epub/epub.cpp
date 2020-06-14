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
#include "config.h"
#include <sstream>

using namespace std;

EPUB::EPUB() : Generator(), m_document(nullptr), m_zipFile(new ZipFile), m_order(0)
{
}

EPUB::~EPUB()
{
    if (m_zipFile)
    {
        delete m_zipFile;
    }
}

void EPUB::GenerateMimeType()
{
    const char *mime = "application/epub+zip";
    m_zipFile->AddSource("mimetype", mime);
}

void EPUB::GenerateCss()
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
    m_zipFile->AddSource("style.css", css.str());
}

void EPUB::GenerateContainer()
{
    XML xml;
    xml.StartDocument("1.0", "UTF-8");

    xml.StartTag("container");
    xml.AddAttribute("version", "1.0");
    xml.AddAttribute("xmlns", "urn:oasis:names:tc:opendocument:xmlns:container");
    xml.StartTag("rootfiles");
    xml.StartTag("rootfile");
    xml.AddAttribute("full-path", "content.opf");
    xml.AddAttribute("media-type", "application/oebps-package+xml");
    xml.EndTag();
    xml.EndTag();
    xml.EndTag();

    xml.EndDocument();
    string content = xml.Content();
    m_zipFile->AddSource("META-INF/container.xml", content);
}

void EPUB::GenerateContent(const string &output)
{
    XML xml;
    xml.StartDocument("1.0", "UTF-8");

    xml.StartTag("package");
    xml.AddAttribute("xmlns", "http://www.idpf.org/2007/opf");
    xml.AddAttribute("unique-identifier", "dcidid");
    xml.AddAttribute("version", "2.0");

    xml.StartTag("metadata");
    xml.AddAttribute("xmlns:dc", "http://purl.org/dc/elements/1.1/");
    xml.AddAttribute("xmlns:dcterms", "http://purl.org/dc/terms/");
    xml.AddAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
    xml.AddAttribute("xmlns:opf", "http://www.idpf.org/2007/opf");

    xml.StartTag("dc:title");
    if (not m_document->Title().empty())
    {
        xml.AddElement(m_document->Title());
    }
    else
    {
        xml.AddElement("No title");
    }

    xml.EndTag();

    xml.StartTag("dc:language");
    xml.AddAttribute("xsi:type", "dcterms:RFC3066");
    xml.AddElement(m_document->Lang().c_str());
    xml.EndTag();

    xml.StartTag("dc:identifier");
    xml.AddAttribute("id", "dcidid");
    xml.AddAttribute("opf:scheme", "URI");
    xml.AddElement(output);
    xml.EndTag();

    xml.StartTag("dc:subject");
    xml.AddElement(m_document->Subject());
    xml.EndTag();

    xml.StartTag("dc:relation");
    xml.AddElement(PACKAGE_URL);
    xml.EndTag();

    xml.StartTag("dc:creator");
    if (m_document->Author().empty())
    {
        xml.AddElement(PACKAGE_STRING);
    }
    else
    {
        xml.AddElement(m_document->Author());
    }

    xml.EndTag();

    xml.StartTag("dc:publisher");
    xml.AddElement(PACKAGE_STRING);
    xml.EndTag();

    xml.StartTag("dc:publisher");
    xml.AddElement(m_document->Author());
    xml.EndTag();

    xml.EndTag();

    xml.StartTag("manifest");

    xml.StartTag("item");
    xml.AddAttribute("id", "ncx");
    xml.AddAttribute("href", "toc.ncx");
    xml.AddAttribute("media-type", "application/x-dtbncx+xml");
    xml.EndTag();

    for (size_t loop = 0; loop < m_document->Pages(); loop++)
    {
        Page *page = m_document->CurrentPage(loop);

        xml.StartTag("item");
        xml.AddAttribute("id", page->Link());
        xml.AddAttribute("href", page->Link() + ".html");
        xml.AddAttribute("media-type", "application/xhtml+xml");
        xml.EndTag();
    }

    xml.StartTag("item");
    xml.AddAttribute("id", "css");
    xml.AddAttribute("href", "style.css");
    xml.AddAttribute("media-type", "text/css");
    xml.EndTag();

    xml.EndTag();

    xml.StartTag("spine");
    xml.AddAttribute("toc", "ncx");

    for (size_t loop = 0; loop < m_document->Pages(); loop++)
    {
        Page *page = m_document->CurrentPage(loop);

        xml.StartTag("itemref");
        xml.AddAttribute("idref", page->Link());
        xml.AddAttribute("linear", "yes");
        xml.EndTag();
    }

    xml.EndTag();

    xml.EndTag();
    xml.EndDocument();
    string content = xml.Content();
    m_zipFile->AddSource("content.opf", content);
}

void EPUB::GenerateOutline(XML *xml, Outline *outline)
{
    Page *page = m_document->CurrentPage(outline->Id(), outline->Generation());

    if (page)
    {
        string playorder{ to_string(m_order) };
        m_order++;

        xml->StartTag("navPoint");
        xml->AddAttribute("id", playorder);

        xml->StartTag("navLabel");
        xml->StartTag("text");
        xml->AddElement(outline->Title());
        xml->EndTag();
        xml->EndTag();

        xml->StartTag("content");
        xml->AddAttribute("src", page->Link() + ".html");
        xml->EndTag();
    }

    size_t size = outline->Size();
    for (size_t loop = 0; loop < size; loop++)
    {
        GenerateOutline(xml, outline->Child(loop));
    }

    if (page)
    {
        xml->EndTag();
    }
}

void EPUB::GenerateToc(const string &output)
{
    Outline *outline = m_document->CurrentOutline();

    XML xml;
    xml.StartDocument("1.0", "UTF-8");

    xml.StartTag("ncx");
    xml.AddAttribute("xmlns", "http://www.daisy.org/z3986/2005/ncx/");
    xml.AddAttribute("version", "2005-1");

    xml.StartTag("head");
    xml.StartTag("meta");
    xml.AddAttribute("name", "dtb:uid");
    xml.AddAttribute("content", output);
    xml.EndTag();
    xml.StartTag("meta");
    xml.AddAttribute("name", "dtb:depth");
    xml.AddAttribute("content", "2");
    xml.EndTag();
    xml.StartTag("meta");
    xml.AddAttribute("name", "dtb:totalPageCount");
    xml.AddAttribute("content", "0");
    xml.EndTag();
    xml.StartTag("meta");
    xml.AddAttribute("name", "dtb:maxPageNumber");
    xml.AddAttribute("content", "0");
    xml.EndTag();
    xml.EndTag();

    xml.StartTag("docTitle");
    xml.StartTag("text");
    xml.AddElement(m_document->Title());
    xml.EndTag();
    xml.EndTag();

    xml.StartTag("navMap");
    if (outline)
    {
        GenerateOutline(&xml, outline);
    }
    else
    {
        size_t size = m_document->Pages();
        for (size_t i = 0; i < size; i++)
        {
            Page *page = m_document->CurrentPage(i);

            xml.StartTag("navPoint");
            xml.AddAttribute("id", "navPoint-1");
            xml.AddAttribute("playOrder", "1");

            xml.StartTag("navLabel");
            xml.StartTag("text");
            xml.AddElement("Main Title");
            xml.EndTag();
            xml.EndTag();

            xml.StartTag("content");
            xml.AddAttribute("src", page->Link() + ".html");
            xml.EndTag();
            xml.EndTag();
        }
    }

    xml.EndTag();

    xml.EndTag();
    xml.EndDocument();
    string content = xml.Content();

    m_zipFile->AddSource("toc.ncx", content);
}

void EPUB::GeneratePages()
{
    size_t size = m_document->Pages();
    for (size_t i = 0; i < size; i++)
    {
        Page *page = m_document->CurrentPage(i);

        Html html;
        html.StartDocument();
        html.StartHeader();
        html.SetTitle(m_document->Title());
        html.AddLink("stylesheet", "text/css", "style.css");
        html.EndTag();
        html.StartBody();

        page->Execute(&html);

        html.EndTag();
        html.EndDocument();

        const string fileout = page->Link() + ".html";
        m_zipFile->AddSource(fileout, html.Content());
    }
}

bool EPUB::Generate(Document *doc, const string &output)
{
    this->m_document = doc;
    m_order = 1;
    if (m_zipFile->Open(output))
    {
        GenerateMimeType();
        GenerateCss();
        GenerateContainer();
        GenerateContent(output);
        GenerateToc(output);
        GeneratePages();
        m_zipFile->Close();
    }
    else
    {
        return false;
    }

    return true;
}
