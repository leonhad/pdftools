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
#ifndef ZIPFILE_H
#define ZIPFILE_H

#include "appendedfile.h"
#include <fstream>
#include <vector>
#include <stdint.h>
#include <string>

/**
 * Creates a ZIP file.
 */
class ZipFile
{
private:
    std::ofstream m_output;
    std::vector<AppendedFile *> m_files;
    uint32_t m_cd_address;
    uint32_t m_cd_size;

public:
    /**
     * Creates a new instance.
     */
    ZipFile();

    /**
     * Destry this intance.
     */
    ~ZipFile();

    /**
     * Open a zip file to write.
     *
     * @param output the output file.
     * @return true if ha success.
     */
    bool open(const std::string &output);

    /**
     * Close this file.
     */
    void close();

    /**
     * Add a file to this ZIP file.
     *
     * @param filename the file name.
     * @param buffer the buffer to read.
     * @param length the buffer length.
     */
    void addSource(const std::string &filename, const char *buffer, size_t length);

    /**
     * Add a file to this ZIP file based on a string buffer.
     *
     * @param filename the file name.
     * @param buffer the buffer to read.
     */
    void addSource(const std::string &filename, const std::string &buffer);
    
private:
    void writeCentralFile();

    void writeCentralDirectory();
    
    void write16(uint16_t c);

    void write32(uint32_t c);

    void writeString(const std::string &str);
};

#endif
