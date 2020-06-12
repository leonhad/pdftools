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

Converter::Converter(const string& in, const string& out, const string& format) :
    fileIn(in), format(format)
{
    // Calculate the output file name
    if (fileOut.empty())
    {
        fileOut = in;
        auto last_dot = fileOut.find_last_of('.');
        if (last_dot != string::npos)
        {
            fileOut = fileOut.substr(0, last_dot);
        }
        fileOut += ".";
        fileOut += format;
    }
    else
    {
        fileOut = out;
    }
}

void Converter::Convert()
{
    Analyze analyze(fileIn);
    
    Document* m_document = analyze.AnalyzeTree();
    
    wstring msg;
    msg += L"Analyzing file ";
    msg += SingleToWide(fileIn);
    msg += L" Pages: ";
    msg += to_wstring(m_document->pages());
    msg += L" - Title: ";
    
    if (m_document->title().empty())
    {
        msg += L"No title";
    }
    else
    {
        msg += SingleToWide(m_document->title());
    }
    
    VerboseMessage(msg);
    
    // Generate output file
    unique_ptr<Generator> instance(Generator::GetInstance(format));
    if (instance.get())
    {
        if (not instance->Generate(m_document, fileOut))
        {
            throw GenericException("Cannot generate output file");
        }
    }
    else
    {
        throw GenericException("Invalid output format");
    }
}
