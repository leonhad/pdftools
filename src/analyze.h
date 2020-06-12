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
#ifndef ANALYZE_H
#define ANALYZE_H

#include <vector>
#include <map>
#include <sstream>
#include <fstream>
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
private:
    std::string fileIn;
    Document *document = nullptr;
    node::RootNode *tree = nullptr;
    std::map<std::string, node::TreeNode *> names;
    
public:
    explicit Analyze(const std::string& filein);
    ~Analyze();
    
    Document *AnalyzeTree();
    
private:
    void AnalyzeXref();
    void AnalyzeInfo();
    node::TreeNode *AnalyzeRoot();
    void AnalyzeNames(node::MapNode *values);
    void AnalyzeOutlines(node::MapNode *values, Outline *parent = nullptr);
    void AnalyzeOutline(node::ArrayNode *values, Outline *outline);
    void AnalyzePages(node::TreeNode *page, node::ArrayNode *mediabox = nullptr);
    Font *AnalyzeFont(node::MapNode *fontmap);
    
    Page *ProcessPage(int id, int generation, std::stringstream *stream_value,
                      node::MapNode *catalog, node::ArrayNode * mediabox);

    std::string GetStringValue(node::TreeNode *value);
    double GetNumberValue(node::TreeNode *value, int default_value = 0);
    
    node::ObjNode *GetObject(int id, int generation);
    node::ObjNode *GetObject(node::RefNode *ref);
    node::TreeNode *GetRealValue(node::TreeNode *value);
    node::TreeNode *GetRealObjValue(node::TreeNode *value);
    node::TreeNode *GetNamedValue(std::string name);
    void GetStream(node::ArrayNode *array, std::stringstream *stream_value);
    void GetStream(node::ObjNode *obj, std::stringstream *stream_value);
};

#endif
