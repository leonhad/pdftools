/*
 * This file is part of PDF Tools.
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
#include "converter.h"
#include "parser/parser.h"
#include "utils.h"
#include "analyze.h"
#include "generator.h"
#include "parser/scanner.h"
#include "semantic/document.h"
#include "nodes/nodes.h"
#include "genericexception.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>

using namespace std;
using namespace parser;

Converter::Converter(const string& filein, const string& fileout, const string& format) :
m_filein(filein), m_format(format)
{
    // Calculate the output file name
    if (fileout.empty())
    {
        m_fileout = filein;
        auto last_dot = m_fileout.find_last_of('.');
        if (last_dot != string::npos)
        {
            m_fileout = m_fileout.substr(0, last_dot);
        }
        m_fileout += ".";
        m_fileout += format;
    }
    else
    {
        m_fileout = fileout;
    }
}

void Converter::convert()
{
    Analyze analyze(m_filein);
    
    Document* m_document = analyze.analyzeTree();
    
    wstring msg;
    msg += L"Analyzing file ";
    msg += ctow(m_filein);
    msg += L" Pages: ";
    msg += to_wstring(m_document->pages());
    msg += L" - Title: ";
    
    if (m_document->title().empty())
    {
        msg += L"No title";
    }
    else
    {
        msg += ctow(m_document->title());
    }
    
    verbose_message(msg);
    
    // Generate output file
    unique_ptr<Generator> instance(Generator::getInstance(m_format));
    if (instance.get())
    {
        if (not instance->generate(m_document, m_fileout))
        {
            throw GenericException("Cannot generate output file");
        }
    }
    else
    {
        throw GenericException("Invalid output format");
    }
}
