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

#include <string>
#include <cstdint>
#include <stdexcept>

std::wstring ctow(const std::string& str);
void error_message(const std::exception &e);
void error_message(const wchar_t *msg);
void error_message(const std::wstring& msg);
void verbose_message(const std::wstring &msg);
void verbose_message(const wchar_t *msg);
void set_verbose_mode(const bool verbose);
bool verbose_mode();
char *flat_decode(char *compressed, int size, int &deflated);
char *compress(const char *raw, size_t size, uint32_t &writed);
std::string utf16be_to_utf8(const std::string &str);
std::string charset_to_utf8(const std::string &str);
