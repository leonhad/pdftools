/*
 * PDF Tools.
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
#pragma once

#include <memory>
#include <string>

std::wstring SingleToWide(const std::string& str);
void ErrorMessage(const std::exception& e);
void ErrorMessage(const wchar_t* msg);
void ErrorMessage(const std::wstring& msg);
void VerboseMessage(const std::wstring& msg);
void VerboseMessage(const wchar_t* msg);
void SetVerboseMode(bool verbose);
bool VerboseMode();
const char* FlatDecode(const char* compressed, size_t size, size_t& deflated);
std::unique_ptr<char*> Compress(const char* raw, size_t size, size_t& writen);
std::string UTF16beToUTF8(const std::string& str);
std::string CharsetToUTF8(const std::string& str);
