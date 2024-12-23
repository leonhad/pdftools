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
#pragma once

#include <memory>

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
class EPUB final : public Generator
{
    /**
     * The document to generate the ePub.
     */
    std::shared_ptr<Document> m_document;

    /**
     * A pointer to ePub ZIP file.
     */
    std::shared_ptr<ZipFile> m_zipFile;

    /**
     * The generated file order.
     */
    int m_order;

public:
    /**
     * Creates a new instance.
     */
    EPUB();

    /**
     * Destroy this instance.
     */
    ~EPUB() override = default;

    /**
     * Generate the ePub file.
     *
     * @param document the document to parse.
     * @param output the output file.
     */
    bool Generate(const std::shared_ptr<Document>& document, const std::string& output) override;

private:
    void GenerateContainer() const;

    void GeneratePages() const;

    void GenerateContent(const std::string& output) const;

    void GenerateToc(const std::string& output);

    void GenerateOutline(const std::shared_ptr<XML>& xml, const std::shared_ptr<Outline>& outline);

    void GenerateMimeType() const;

    void GenerateCss() const;
};
