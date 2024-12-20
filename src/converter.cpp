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
#include "semantic/document.h"
#include "genericexception.h"
#include <memory>
#include <utility>

using namespace std;
using namespace parser;

Converter::Converter(const string& in, const string& out, string format) :
    m_fileIn(in), m_format(std::move(format))
{
    // Calculate the output file name
    if (m_fileOut.empty())
    {
        m_fileOut = in;
        if (const auto last_dot = m_fileOut.find_last_of('.'); last_dot != string::npos)
        {
            m_fileOut = m_fileOut.substr(0, last_dot);
        }

        m_fileOut += ".";
        m_fileOut += m_format;
    }
    else
    {
        m_fileOut = out;
    }
}

void Converter::Convert() const
{
    Analyze analyze(m_fileIn);

    auto m_document = analyze.AnalyzeTree();

    wstring msg;
    msg += L"Analyzing file ";
    msg += SingleToWide(m_fileIn);
    msg += L" Pages: ";
    msg += to_wstring(m_document->Pages());
    msg += L" - Title: ";

    if (m_document->Title().empty())
    {
        msg += L"No title";
    }
    else
    {
        msg += SingleToWide(m_document->Title());
    }

    VerboseMessage(msg);

    // Generate output file
    if (const auto instance(Generator::GetInstance(m_format)); instance)
    {
        if (not instance->Generate(m_document, m_fileOut))
        {
            throw GenericException("Cannot generate output file");
        }
    }
    else
    {
        throw GenericException("Invalid output format");
    }
}
