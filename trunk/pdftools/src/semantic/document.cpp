#include "document.h"

Document::Document()
{
    m_root = NULL;
    m_info = NULL;
    m_outlines = NULL;
    m_lang = "en";
}

Document::~Document()
{
    vector<Page *>::iterator i = m_pages.begin();
    while (i != m_pages.end()) {
        delete *i;
        i++;
    }
    vector<PageLabel *>::iterator l = m_page_label.begin();
    while (l != m_page_label.end()) {
        delete *l;
        l++;
    }
}

Page *Document::page(int id, int generation)
{
    vector<Page *>::iterator i = m_pages.begin();
    while (i != m_pages.end()) {
        register Page *page = *i;
        if (page->id() == id && page->generation() == generation) {
            return page;
        }
        i++;
    }
    return NULL;
}

void Document::set_outline(Outline *outline)
{
    m_outlines = outline;
}

Outline *Document::outline()
{
    return m_outlines;
}

void Document::set_id(string first, string second)
{
    m_id = first + second;
}

void Document::add_page(Page *page)
{
    m_pages.push_back(page);
}

void Document::add_page_label(PageLabel* label)
{
    m_page_label.push_back(label);
}

Page *Document::page(int index)
{
    return m_pages[index];
}

int Document::pages()
{
    return m_pages.size();
}

TreeNode *Document::root_node()
{
    return m_root;
}

TreeNode *Document::info_node()
{
    return m_info;
}

string Document::id()
{
    return m_id;
}

void Document::set_root(TreeNode *root)
{
    m_root = root;
}

void Document::set_info(TreeNode *info)
{
    m_info = info;
}

void Document::set_title(string title)
{
    m_title = title;
}

void Document::set_subject(string subject)
{
    m_subject = subject;
}

void Document::set_author(string author)
{
    m_author = author;
}

void Document::set_lang(string lang)
{
    if (!lang.empty()) {
        m_lang = lang;
    }
}

string Document::lang()
{
    return m_lang;
}

string Document::title()
{
    return m_title;
}

string Document::subject()
{
    return m_subject;
}

string Document::author()
{
    return m_author;
}