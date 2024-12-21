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
#ifndef APPENDEDFILE_H
#define APPENDEDFILE_H

#include <cstdint>
#include <memory>
#include <string>

/**
 * The ZIP header bytes.
 */
class AppendedFile
{
public:
    AppendedFile(const std::string& filename, const char* buffer, size_t length, std::streampos position);

    ~AppendedFile();

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
    size_t compressed_size;

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
    std::streampos position;

    std::unique_ptr<char*> deflate_buffer;

private:
    static uint32_t CurrentDatetime();
};

#endif
