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

#include <string>
#include <map>
#include <memory>

class Context;
class Document;
class Glyph;
class Html;

class Page
{
    int* m_mediaBox;
    int* m_cropBox;
    int m_id;
    int m_generation;
    std::string m_link;
    std::shared_ptr<Glyph> m_root;
    std::shared_ptr<Document> m_document;
    std::map<std::string, std::string> m_fontMap;

public:
    explicit Page(const std::shared_ptr<Document>& parent);
    ~Page();

    void SetMediaBox(int a, int b, int c, int d);
    void SetCropBox(int a, int b, int c, int d);
    void SetDestination(int id, int generation);
    void SetRoot(const std::shared_ptr<Glyph>& root);
    [[nodiscard]] int Id() const;
    [[nodiscard]] int Generation() const;
    std::string Link();

    void Execute(const std::shared_ptr<Html>& html);

    void AddFontMap(const std::string& alias, const std::string& font_name);
    std::string FontName(const std::string& alias);
};
