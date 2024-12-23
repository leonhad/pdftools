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
#include <ctime>
#include <zlib.h>

AppendedFile::AppendedFile(const std::string& filename, const char* buffer, const size_t length,
                           const std::streampos position)
{
    this->position = position;
    this->date = CurrentDatetime();
    this->length = static_cast<uint32_t>(length);
    this->name = filename;

    const auto crc_code = static_cast<uint32_t>(crc32(0L, nullptr, 0));
    this->crc = static_cast<uint32_t>(crc32(crc_code, (Bytef*)buffer, (uInt)length));

    this->deflate_buffer = move(Compress(buffer, length, this->compressed_size));

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

uint32_t AppendedFile::CurrentDatetime()
{
    time_t rawTime = time(nullptr);
    tm t{};

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

    return static_cast<uint32_t>((t.tm_mday + (32 * (t.tm_mon + 1)) + (512 * t.tm_year)) << 16)
        | static_cast<uint32_t>((t.tm_sec / 2) + (32 * t.tm_min) + (2048 * t.tm_hour));
}
