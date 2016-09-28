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

#include <fstream>
#include <vector>
#include <stdint.h>
#include <string>

/**
 * The ZIP header bytes.
 */
struct appended_files
{
    /**
     * The file name.
     */
    std::string name;

    /**
     * The file length.
     */
    uint32_t length;

    /**
     * If this file is compressed.
     */
    bool compressed;

    /**
     * The compressed file size.
     */
    uint32_t compressed_size;

    /**
     * The file date.
     */
    uint32_t date;

    /**
     * The files CRC.
     */
    uint32_t crc;

    /**
     * The file position in ZIP file.
     */
    uint32_t position;
};

/**
 * Creates a ZIP file.
 */
class ZipFile
{
private:
    std::ofstream m_output;
    std::vector<appended_files> m_files;
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
     * \param output the output file.
     * \return true if ha success.
     */
    bool open(const std::string &output);

    /**
     * Close this file.
     */
    void close();

    /**
     * Add a file to this ZIP file.
     *
     * \param filename the file name.
     * \param buffer the buffer to read.
     * \param length the buffer length.
     */
    void addSource(const char *filename, const char *buffer, size_t length = 0);

private:
    void writeCentralFile();

    void writeCentralDirectory();

    void write16(uint16_t c);

    void write32(uint32_t c);

    void writeString(const std::string &str);

    uint32_t currentDatetime() const;
};

#endif
