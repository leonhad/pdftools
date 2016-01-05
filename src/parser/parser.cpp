#include "parser.h"
#include "scanner.h"
#include "../utils.h"
#include "../nodes/nodes.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;
using namespace parser;
using namespace node;

inline bool pdf_versions(const string &version) {
    return version == "PDF-1.1"
            || version == "PDF-1.2"
            || version == "PDF-1.3"
            || version ==  "PDF-1.4"
            || version ==  "PDF-1.5"
            || version ==  "PDF-1.6"
            || version ==  "PDF-1.7";
}

Parser::Parser(ifstream *filein) throw(exception) : GenericParser{filein}
{
    m_linear = false;

    if (filein->is_open()) {
        next_token();
    } else {
        throw ios_base::failure("Invalid input file.");
    }
}

RootNode *Parser::parse()
{
    RootNode *root = new RootNode();
    bool error = false;
    match(TokenType::PERCENT);
    if (verify_version()) {
        while (m_scanner->good() && !error) {
            switch (m_token->type()) {
            case TokenType::PERCENT:
                comment_sequence();
                break;
            case TokenType::NUM:
                root->add_child(object_sequence());
                break;
            case TokenType::XREF:
                root->add_child(xref_sequence());
                break;
            case TokenType::START_XREF:
                startxref_sequence();
                break;
            default:
                next_token();
                error = true;
                break;
            }
        }
    } else {
        error_message("invalid input file");
    }
    m_scanner->clear();
    object_streams(root);
    return root;
}

void Parser::object_streams(RootNode *root_node)
{
    size_t size = root_node->size();

    for (size_t i = 0; i < size; i++) {
        ObjNode *root_object = dynamic_cast<ObjNode *> (root_node->get(i));
        if (root_object) {
            MapNode *map = dynamic_cast<MapNode *> (root_object->value());
            if (map) {
                NameNode *type = dynamic_cast<NameNode *> (map->get("/Type"));
                if (type && type->name() == "/ObjStm") {
                    int qtd = 0;
                    int length = 0;
                    NumberNode *number = dynamic_cast<NumberNode *> (map->get("/N"));
                    if (number) {
                        qtd = number->value();
                    }
                    NumberNode *length_node = dynamic_cast<NumberNode *> (map->get("/Length"));
                    if (number) {
                        length = length_node->value();
                    }
                    char *uncompressed = nullptr;
                    
                    m_scanner->to_pos(root_object->stream_pos());
                    char *stream = (char *)m_scanner->get_stream(length);

                    int total = length;
                    NameNode *filter = dynamic_cast<NameNode *> (map->get("/Filter"));
                    if (filter && filter->name() == "/FlateDecode") {
                        uncompressed = flat_decode(stream, length, total);
                        delete [] stream;
                    } else if (!filter) {
                        uncompressed = stream;
                    } else {
                        string msg{"compression not supported: "};
                        msg += filter->name();
                        error_message(msg.c_str());
                        return;
                    }
                    stringstream stream_value;
                    stream_value.write(uncompressed, total);
                    stream_value.seekg(0);
                    delete [] uncompressed;

                    Scanner *temp = m_scanner;
                    m_scanner = new Scanner{&stream_value};

                    vector<int> ids;
                    int loop;
                    for (loop = 0; loop < qtd; loop++) {
                        next_token();
                        ids.push_back(m_token->to_number());
                        next_token();
                    }
                    next_token();
                    vector<int>::iterator id;
                    for (id = ids.begin(); id < ids.end(); id++) {
                        ObjNode *new_obj = new ObjNode(*id, 0);
                        new_obj->set_value(value_sequence());
                        root_node->add_child(new_obj);
                    }
                    m_scanner = temp;
                }
            }
        }
    }
}

void Parser::comment_sequence()
{
    m_scanner->ignore_line();
    next_token();
}

TreeNode * Parser::xref_sequence()
{
    XREFNode *xref = new XREFNode;
    match(TokenType::XREF);

    do {
        uint16_t id = (uint16_t) m_token->to_number();
        match(TokenType::NUM);
        int count = (int) m_token->to_number();
        match(TokenType::NUM);

        for (int loop = 0; loop < count; loop++) {
            uint32_t address = (int) m_token->to_number();
            match(TokenType::NUM);
            uint16_t generation = (int) m_token->to_number();
            match(TokenType::NUM);
            string name = m_token->value();
            if (m_token->type() == TokenType::F_LO) {
                match(TokenType::F_LO);
            } else {
                match(TokenType::N);
            }
            xref->add_node(id, generation, address, name.at(0));
            id++;
        }
    } while (m_scanner->good() && (m_token->type() != TokenType::TRAILER));
    match(TokenType::TRAILER);
    xref->set_trailer(value_sequence());
    return xref;
}

void Parser::startxref_sequence()
{
    match(TokenType::START_XREF);
    match(TokenType::NUM);

    match(TokenType::PERCENT);
    match(TokenType::PERCENT);
    match(TokenType::END_PDF);
}

TreeNode *Parser::object_sequence()
{
    float number = m_token->to_number();
    match(TokenType::NUM);
    float generation_nunber = m_token->to_number();
    match(TokenType::NUM);

    ObjNode *node = new ObjNode((int) number, (int) generation_nunber);
    match(TokenType::OBJ);
    node->set_value(value_sequence());
    if (m_token && m_token->type() == TokenType::STREAM) {
        int length = -1;
        MapNode *map = dynamic_cast<MapNode *> (node->value());
        if (map) {
            NumberNode *number = dynamic_cast<NumberNode *> (map->get("/Length"));
            if (number) {
                length = number->value();
            }
        }
        node->set_stream_pos(m_scanner->ignore_stream(length));
        next_token();
        match(TokenType::END_STREAM);
    }
    match(TokenType::END_OBJ);

    return node;
}

bool Parser::verify_version()
{
    if (m_token) {
        string line = m_token->value();
        if (pdf_versions(line)) {
            match(TokenType::NAME);
            return true;
        }
    }
    return false;
}
