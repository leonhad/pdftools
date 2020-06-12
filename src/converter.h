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
#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>

/// PDF class converter.
class Converter
{
private:
    // The input file.
    const std::string fileIn;
    
    /// The output file format.
    const std::string format;
    
    /// The output file.
    std::string fileOut;
    
public:
    /// Creates a new converter instance.
    /// @param fileIn  the input file name.
    /// @param fileOut the file output name.
    /// @param format the desired format.
    Converter(const std::string& fileIn, const std::string& fileOut, const std::string& format);
    
    /// Convert the PDF file.
    void Convert();
};

#endif
