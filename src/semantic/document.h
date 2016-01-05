#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <vector>

class Font;
class Outline;
class Page;
class PageLabel;

namespace node {
    class TreeNode;
}

class Document {
private:
    bool m_encrypted;
    bool m_tree_root;
    std::string m_id;
    std::string m_title;
    std::string m_subject;
    std::string m_author;
    std::string m_lang;
    node::TreeNode *m_root;
    node::TreeNode *m_info;
    Outline *m_outlines;
    std::vector<Font *> m_fonts;
    std::vector<Page *> m_pages;
    std::vector<PageLabel *> m_page_label;
    
public:
    Document();
    ~Document();
    
    void set_id(std::string first, std::string second);
    void set_root(node::TreeNode *root);
    void set_info(node::TreeNode *info);
    void set_encrypted(bool encrypt);
    void set_tree_root(bool tree_root);
    
    void set_title(std::string title);
    void set_subject(std::string subject);
    void set_author(std::string author);
    void set_lang(std::string lang);
    
    void set_outline(Outline *outline);
    Outline *outline();
    
    void add_font(Font *font);
    Font *get_font(const char *name);
    
    void add_page(Page *page);
    void add_page_label(PageLabel *label);
    Page *page(size_t index);
    size_t pages();
    Page *page(int id, int generation);
    
    bool encrypted();
    bool tree_root();
    std::string lang();
    std::string id();
    std::string title();
    std::string subject();
    std::string author();
    node::TreeNode *root_node();
    node::TreeNode *info_node();
};

#endif
