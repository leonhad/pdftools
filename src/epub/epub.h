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
#ifndef EPUB_H
#define EPUB_H

#include "generator.h"

class ZipFile;
class Document;
class Context;
class Outline;
class Page;
class XML;

/**
 * Generate an ePub file.
 */
class EPUB : public Generator
{
private:
    Document *m_document;
    ZipFile *m_zipfile;
    int m_order;

public:
    /**
     * Creates a new instance.
     */
    EPUB();

    /**
     * Destroy this instance.
     */
    virtual ~EPUB();

    /**
     * Generate the ePub file.
     *
     * \param document the document to parse.
     * \param output the output file.
     */
    virtual bool generate(Document *document, const std::string& output);

private:
    void generate_container();
    void generate_pages();
    void generate_page(Page *page);
    void generate_content(const std::string& output);
    void generate_toc(const std::string& output);
    void generate_outline(XML *xml, Outline *outline);
    void generate_mimetype();
    void generate_css();
};

#endif
