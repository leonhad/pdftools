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
#include "appendedfile.h"
#include "../utils.h"
#include "config.h"
#include <stdexcept>
#include <ctime>
#include <zlib.h>

AppendedFile::AppendedFile(const std::string filename, const char *buffer, size_t length,
                           std::streampos position)
{
    this->position = position;
    this->date = currentDatetime();
    this->length = static_cast<uint32_t>(length);
    this->name = filename.c_str();

    uint32_t crc = (uint32_t) ::crc32(0L, Z_NULL, 0);
    this->crc = (uint32_t) ::crc32(crc, (Bytef *) buffer, (uInt) length);
    
    this->deflate_buffer = nullptr;

    this->deflate_buffer = compress(buffer, length, this->compressed_size);

    if (this->compressed_size < this->length)
    {
        this->compressed = true;
    }
    else
    {
        this->compressed = false;
        this->compressed_size = this->length;
    }
}

AppendedFile::~AppendedFile() {
    if (deflate_buffer)
    {
        delete [] deflate_buffer;
    }
}

uint32_t AppendedFile::currentDatetime() const
{
    time_t rawTime = time(nullptr);
    struct tm t;

#ifdef HAVE_LOCALTIME_S
    localtime_s(&t, &rawTime);
#else
#ifdef HAVE_LOCALTIME_R
    localtime_r(&rawTime, &t);
#else
#error The localtime_s or localtime_r is needed.
#endif
#endif

    if (t.tm_year >= 1980)
    {
        t.tm_year -= 1980;
    }
    else if (t.tm_year >= 80)
    {
        t.tm_year -= 80;
    }

    return (uint32_t) ((t.tm_mday + (32 * (t.tm_mon + 1)) + (512 * t.tm_year)) << 16)
            | ((t.tm_sec / 2) + (32 * t.tm_min) + (2048 * t.tm_hour));
}

