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
#ifndef EPUB_H
#define EPUB_H

#include "../generator.h"

class ZipFile;

class Document;

class Context;

class Outline;

class Page;

class XML;

/**
 * Generate an ePub file.
 */
class EPUB: public Generator
{
private:
    /**
     * The document to generate the ePub.
     */
    Document *document;

    /**
     * A pointer to ePub ZIP file.
     */
    ZipFile *zipFile;

    /**
     * The generated file order.
     */
    int order;

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
     * @param document the document to parse.
     * @param output the output file.
     */
    virtual bool Generate(Document *document, const std::string &output);

private:
    void GenerateContainer();

    void GeneratePages();

    void GenerateContent(const std::string &output);

    void GenerateToc(const std::string &output);

    void GenerateOutline(XML *xml, Outline *outline);

    void GenerateMimeType();

    void GenerateCss();
};

#endif
