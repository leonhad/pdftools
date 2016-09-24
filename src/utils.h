/*
 * PDF Tools.
 * Copyright (C) 2012-2016 Leonardo Alves da Costa
 * mailto:leonhad AT gmail DOT com
 *
 * SonarQube is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * SonarQube is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <cstdint>
#include <stdexcept>

void error_message(const char *msg);
void error_message(const std::string &msg);
void verbose_message(const std::string &msg);
void verbose_message(const char *msg);
void set_verbose_mode(const bool verbose);
bool verbose_mode();
char *flat_decode(char *compressed, int size, int &deflated);
char *compress(const char *raw, size_t size, uint32_t &writed) throw (std::exception);
std::string utf16be_to_utf8(std::string &str);
std::string charset_to_utf8(std::string &str);

#endif
