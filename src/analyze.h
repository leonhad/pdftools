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
#ifndef ANALYZE_H
#define ANALYZE_H

#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <string>
#include <stdexcept>

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
    const std::string m_filein;
    Document *m_document = nullptr;
    node::RootNode *m_tree = nullptr;
    node::TreeNode *m_page_tree = nullptr;
    std::map<std::string, node::TreeNode *> m_names;

public:
    explicit Analyze(const std::string& filein) throw (std::exception);
    ~Analyze();

    Document *analyzeTree() throw (std::exception);

private:
    void analyzeXref();
    void analyzeInfo();
    void analyzeRoot();
    void analyzeNames(node::MapNode *values);
    void analyzeOutlines(node::MapNode *values, Outline *parent = nullptr);
    void analyzeOutline(node::ArrayNode *values, Outline *outline);
    void analyzePages(node::TreeNode *page, node::ArrayNode *mediabox = nullptr);
    Font *analyzeFont(node::MapNode *fontmap);

    Page *processPage(int id, int generation, std::stringstream *stream_value,
            node::MapNode *catalog, node::ArrayNode * mediabox);

    std::string getStringValue(node::TreeNode *value);
    double getNumberValue(node::TreeNode *value, int default_value = 0);

    node::ObjNode *getObject(int id, int generation);
    node::ObjNode *getObject(node::RefNode *ref);
    node::TreeNode *getRealValue(node::TreeNode *value);
    node::TreeNode *getRealObjValue(node::TreeNode *value);
    node::TreeNode *getNamedValue(std::string name);
    void getStream(node::ArrayNode *array, std::stringstream *stream_value);
    void getStream(node::ObjNode *obj, std::stringstream *stream_value);
};

#endif
