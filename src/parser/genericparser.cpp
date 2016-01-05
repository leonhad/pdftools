#include "genericparser.h"
#include "../nodes/nodes.h"
#include "../utils.h"

using namespace std;
using namespace parser;
using namespace node;

GenericParser::GenericParser(std::istream *filein) noexcept
{
    m_scanner = new Scanner{filein};
}

GenericParser::~GenericParser() noexcept
{
    if (m_scanner) delete m_scanner;
}

bool GenericParser::match(TokenType type)
{
    if (m_token && m_token->type() == type) {
        next_token();
    } else {
#ifdef DEBUG
        string msg = "unexpected token: ";
        if (m_token) {
            msg += m_token->value();
        }
        error_message(msg.c_str());
#endif
        next_token();
        return false;
    }
    return true;
}

void GenericParser::next_token()
{
    m_token = m_scanner->next_token();
}

TreeNode *GenericParser::value_sequence()
{
    if (m_token->type() == TokenType::START_DICT) {
        match(TokenType::START_DICT);
        MapNode *map = new MapNode;

        while (m_scanner->good() && m_token && m_token->type() != TokenType::END_DICT) {
            string name = m_token->value();
            match(TokenType::NAME);
            TreeNode *value = value_sequence();
            NameNode *n = dynamic_cast<NameNode *>(value);
            if (n && n->name()[0] != '/') {
                value = value_sequence();
            }
            map->push(name, value);
        }
        match(TokenType::END_DICT);
        return map;
    } else if (m_token->type() == TokenType::TRUE) {
        match(TokenType::TRUE);
        return new BooleanNode(true);
    } else if (m_token->type() == TokenType::FALSE) {
        match(TokenType::FALSE);
        return new BooleanNode(false);
    } else if (m_token->type() == TokenType::NAME) {
        string name = m_token->value();
        match(TokenType::NAME);
        return new NameNode(name);
    } else if (m_token->type() == TokenType::STRING) {
        string value = m_token->value();
        match(TokenType::STRING);
        return new StringNode(value);
    } else if (m_token->type() == TokenType::NUM) {
        double value = m_token->to_number();
        size_t pos = m_scanner->pos();
        match(TokenType::NUM);

        if (m_token->type() == TokenType::NUM) {
            double generation = m_token->to_number();
            match(TokenType::NUM);
            if (m_token->type() == TokenType::NAME && m_token->value() == "R") {
                match(TokenType::NAME);
                return new RefNode(value, generation);
            } else {
                m_scanner->to_pos(pos);
            }
        } else {
            m_scanner->to_pos(pos);
        }
        next_token();
        return new NumberNode(value);
    } else if (m_token->type() == TokenType::START_ARRAY) {
        ArrayNode *array = new ArrayNode;
        match(TokenType::START_ARRAY);
        while (m_scanner->good() && m_token->type() != TokenType::END_ARRAY) {
            array->push(value_sequence());
        }
        match(TokenType::END_ARRAY);
        return array;
    }
    return nullptr;
}

