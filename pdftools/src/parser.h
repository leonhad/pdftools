#pragma once
#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include "token.h"
#include "genericparser.h"

class Scanner;
class TreeNode;
class RootNode;

class Parser : public GenericParser {
private:
    bool m_linear;
    const char *m_version;
    const char *m_filein;
    ifstream m_filestream;

public:
    Parser(const char *filein);
    ~Parser();

    RootNode *parse();
    bool is_valid();

private:
    bool verify_version();
    void object_streams(RootNode *root);
    void startxref_sequence();

    void comment_sequence();
    TreeNode *object_sequence();
    TreeNode *xref_sequence();
};

#endif
