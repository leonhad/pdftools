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
#ifndef ZIPFILE_H
#define ZIPFILE_H

#include <fstream>
#include <vector>
#include <stdint.h>
#include <string>

struct appended_files
{
    std::string name;
    uint32_t length;
    bool compressed;
    uint32_t compressed_size;
    uint32_t date;
    uint32_t crc;
    uint32_t position;
};

class ZipFile
{
private:
    std::ofstream m_output;
    std::vector<appended_files> m_files;
    uint32_t m_cd_address;
    uint32_t m_cd_size;

public:
    ZipFile();
    ~ZipFile();

    bool open(const std::string& output);
    void close();
    void add_source(const char *filename, const char *buffer, size_t length = 0);

private:
    void write_central_file();
    void write_central_directory();

    void write8(uint8_t c);
    void write16(uint16_t c);
    void write32(uint32_t c);
    void write_string(const std::string& str);

    uint32_t current_datetime() const;
};

#endif
