#include "converter.h"
#include "parser/parser.h"
#include "utils.h"
#include "analyze.h"
#include "generator.h"
#include "parser/scanner.h"
#include "semantic/document.h"
#include "nodes/nodes.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;
using namespace parser;

Converter::Converter(const string& filein, const string& fileout, const string& format) noexcept : m_filein{filein}, m_format{format}
{
    // Calculate the output file name
    if (fileout.empty()) {
        m_fileout = filein;
        auto last_dot = m_fileout.find_last_of('.');
        if (last_dot != string::npos) {
            m_fileout = m_fileout.substr(0, last_dot);
        }
        m_fileout += ".";
        m_fileout += format;
    } else {
        m_fileout = fileout;
    }
}

Converter::~Converter() noexcept {
    if (m_document) delete m_document;
}

void Converter::convert() throw(std::exception) {
    Analyze analyze(m_filein.c_str());

    m_document = analyze.analyze_tree();
    if (m_document) {
        stringstream msg;
        msg << "Parsing file " << m_filein << " " << "Pages: " << m_document->pages() << " - " << "Title: ";
        if (m_document->title().empty()) {
            msg << "no title";
        } else {
            msg << m_document->title();
        }
        verbose_message(msg.str().c_str());
        
        // Generate output file
        Generator *instance = Generator::get_instance(m_format.c_str());
        if (instance) {
            if (!instance->generate(m_document, m_fileout.c_str())) {
                error_message("Cannot generate output file");
            }
            delete instance;
        }
    } else {
        error_message("Invalid input file");
    }
}
