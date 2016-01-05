#ifndef PAGEANALYZE_H
#define PAGEANALYZE_H

#include "graphics/graphicstate.h"
#include "glyphs/glyphs.h"

class Font;
class Document;

namespace node {
    class TreeNode;
    class TextNode;
    class RootNode;
    class FontNode;
    class TextMatrixNode;
}

class PageAnalyze {
private:
    GraphicState m_state;
    Document *m_document;
    Glyph *m_root;
    Font *m_font;

public:
    PageAnalyze(Document *document);
    ~PageAnalyze();

    Glyph *analyze_tree(node::RootNode *tree);

private:
    void analyze_tree(node::RootNode *tree, Glyph *parent);
    void analyze_text(node::TextNode *text, Glyph *parent);
    FontSizeGlyph *analyze_text_matrix(node::TextMatrixNode *text_matrix);
    FontGlyph *analyze_font(node::FontNode *font);
};

#endif
