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
class RootNode;
class TreeNode;
class MapNode;
class ArrayNode;
class ObjNode;
class RefNode;
class Font;
class Page;

class Analyze {
private:
    const std::string m_filein;
    std::ifstream m_filestream;
    Document *m_document = nullptr;
    RootNode *m_tree = nullptr;
    TreeNode *m_page_tree = nullptr;
    std::map<std::string, TreeNode *> m_names;

public:
    Analyze(const std::string& filein) throw(std::exception);
    ~Analyze() noexcept;

    Document *analyze_tree();

private:
    void analyze_xref();
    void analyze_info();
    void analyze_root();
    void analyze_names(MapNode *values);
    void analyze_outlines(MapNode *values, Outline *parent = NULL);
    void analyze_outline(ArrayNode *values, Outline *outline);
    void analyze_pages(TreeNode *page, ArrayNode *mediabox = NULL);
    Font *analyze_font(MapNode *fontmap);

    Page *process_page(int id, int generation, std::stringstream *stream_value, MapNode *catalog, ArrayNode * mediabox);

    std::string get_string_value(TreeNode *value);
    double get_number_value(TreeNode *value, int default_value = 0);

    ObjNode *get_object(int id, int generation);
    ObjNode *get_object(RefNode *ref);
    TreeNode *get_real_value(TreeNode *value);
    TreeNode *get_real_obj_value(TreeNode *value);
    TreeNode *get_named_value(std::string name);
    void get_stream(ArrayNode *array, std::stringstream *stream_value);
    void get_stream(ObjNode *obj, std::stringstream *stream_value);
};

#endif
