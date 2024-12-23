/*
 * This file is part of PDF Tools.
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

#include <map>
#include <memory>
#include <string>

class Outline;
class Document;
class Font;
class Page;

namespace node
{
    class RootNode;
    class TreeNode;
    class MapNode;
    class ArrayNode;
    class ObjNode;
    class RefNode;
}

class Analyze
{
    std::string m_fileIn;
    std::shared_ptr<Document> m_document = nullptr;
    std::shared_ptr<node::RootNode> m_tree = nullptr;
    std::map<std::string, std::shared_ptr<node::TreeNode>> m_names;

public:
    explicit Analyze(std::string filein);
    ~Analyze() = default;

    std::shared_ptr<Document> AnalyzeTree();

private:
    void AnalyzeXref();
    void AnalyzeInfo();
    std::shared_ptr<node::TreeNode> AnalyzeRoot();
    void AnalyzeNames(const std::shared_ptr<node::MapNode>& values);
    void AnalyzeOutlines(const std::shared_ptr<node::MapNode>& values,
                         const std::shared_ptr<Outline>& parent = nullptr);
    void AnalyzeOutline(const std::shared_ptr<node::ArrayNode>& values, const std::shared_ptr<Outline>& outline);
    void AnalyzePages(const std::shared_ptr<node::TreeNode>& page,
                      const std::shared_ptr<node::ArrayNode>& media_box = nullptr);
    std::shared_ptr<Font> AnalyzeFont(const std::shared_ptr<node::MapNode>& fontmap);

    std::shared_ptr<Page> ProcessPage(int id, int generation, std::stringstream* stream_value,
                                      const std::shared_ptr<node::MapNode>& catalog,
                                      const std::shared_ptr<node::ArrayNode>& media_box);

    std::string GetStringValue(const std::shared_ptr<node::TreeNode>& value);
    double GetNumberValue(const std::shared_ptr<node::TreeNode>& value, int default_value = 0);

    [[nodiscard]] std::shared_ptr<node::ObjNode> GetObject(int id, int generation) const;
    [[nodiscard]] std::shared_ptr<node::ObjNode> GetObject(const std::shared_ptr<node::RefNode>& ref) const;
    std::shared_ptr<node::TreeNode> GetRealValue(std::shared_ptr<node::TreeNode> value);
    std::shared_ptr<node::TreeNode> GetRealObjValue(std::shared_ptr<node::TreeNode> value);
    std::shared_ptr<node::TreeNode> GetNamedValue(const std::string& name);
    void GetStream(const std::shared_ptr<node::ArrayNode>& array, std::stringstream* stream_value);
    void GetStream(const std::shared_ptr<node::ObjNode>& obj, std::stringstream* stream_value);
};
