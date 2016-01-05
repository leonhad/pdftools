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

namespace node {
    class RootNode;
    class TreeNode;
    class MapNode;
    class ArrayNode;
    class ObjNode;
    class RefNode;
}

class Analyze {
private:
    const std::string m_filein;
    std::ifstream m_filestream;
    Document *m_document = nullptr;
    node::RootNode *m_tree = nullptr;
    node::TreeNode *m_page_tree = nullptr;
    std::map<std::string, node::TreeNode *> m_names;

public:
    Analyze(const std::string& filein) throw(std::exception);
    ~Analyze() noexcept;

    Document *analyze_tree() throw(std::exception);

private:
    void analyze_xref();
    void analyze_info();
    void analyze_root();
    void analyze_names(node::MapNode *values);
    void analyze_outlines(node::MapNode *values, Outline *parent = nullptr);
    void analyze_outline(node::ArrayNode *values, Outline *outline);
    void analyze_pages(node::TreeNode *page, node::ArrayNode *mediabox = nullptr);
    Font *analyze_font(node::MapNode *fontmap);

    Page *process_page(int id, int generation, std::stringstream *stream_value, node::MapNode *catalog, node::ArrayNode * mediabox);

    std::string get_string_value(node::TreeNode *value);
    double get_number_value(node::TreeNode *value, int default_value = 0);

    node::ObjNode *get_object(int id, int generation);
    node::ObjNode *get_object(node::RefNode *ref);
    node::TreeNode *get_real_value(node::TreeNode *value);
    node::TreeNode *get_real_obj_value(node::TreeNode *value);
    node::TreeNode *get_named_value(std::string name);
    void get_stream(node::ArrayNode *array, std::stringstream *stream_value);
    void get_stream(node::ObjNode *obj, std::stringstream *stream_value);
};

#endif
