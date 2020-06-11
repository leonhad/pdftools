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
#include "config.h"
#include "zipfile.h"
#include <zlib.h>
#include <cstring>

using namespace std;

ZipFile::ZipFile() : m_cd_address(0), m_cd_size(0)
{
}

ZipFile::~ZipFile()
{
    close();

    for (auto file : m_files)
    {
        delete file;
    }
}

bool ZipFile::open(const string &output)
{
    m_output.open(output, ios::binary);
    return m_output.is_open();
}

void ZipFile::close()
{
    if (m_output.is_open())
    {
        writeCentralFile();
        writeCentralDirectory();
        m_output.flush();
        m_output.close();
    }
}

void ZipFile::addSource(const string &filename, const string &buffer)
{
    addSource(filename, buffer.c_str(), buffer.size());
}

void ZipFile::addSource(const string &filename, const char *buffer, size_t length)
{
    AppendedFile *file = new AppendedFile(filename, buffer, length, m_output.tellp());

    writeString("\x50\x4B\x03\x04");
    // Unix Type
    write16(0xA);
    if (file->compressed)
    {
        // Bit flags
        write16(2);
        // Compression mode
        write16(Z_DEFLATED);
    }
    else
    {
        write16(0);
        write16(0);
    }
    
    write32(file->date);
    write32(file->crc);
    // Compressed
    write32((uint32_t)file->compressed_size);
    // Uncompressed
    write32(file->length);
    write16((uint16_t)filename.size());
    // file extra
    write16(0);
    writeString(filename);

    if (file->compressed)
    {
        m_output.write(file->deflate_buffer, file->compressed_size);
    }
    else
    {
        m_output.write(buffer, file->length);
    }

    m_files.push_back(file);
}

void ZipFile::writeCentralFile()
{
    size_t size = m_files.size();
    m_cd_address = (uint32_t) m_output.tellp();

    for (size_t i = 0; i < size; i++)
    {
        AppendedFile *file = m_files.at(i);

        writeString("\x50\x4B\x01\x02");
        write16(0x031E);
        write16(0x0A);

        if (file->compressed)
        {
            // bit flag
            write16(2);
            // compression
            write16(Z_DEFLATED);
        }
        else
        {
            write16(0);
            write16(0);
        }

        write32(file->date);
        write32(file->crc);
        // Compressed
        write32(static_cast<uint32_t>(file->compressed_size));
        // Uncompressed
        write32(file->length);
        write16(static_cast<u_int16_t>(file->name.length()));
        // file extra
        write16(0);
        // file comment length
        write16(0);
        // dist start
        write16(0);
        write16(0);
        write32(0x81A40000);
        write32(static_cast<uint32_t>(file->position));
        writeString(file->name);
    }
    
    m_cd_size = ((uint32_t) m_output.tellp()) - m_cd_address;
}

void ZipFile::writeCentralDirectory()
{
    writeString("\x50\x4B\x05\x06");
    // number of this disk
    write16(0);
    // number of this disk start
    write16(0);
    // number of files records (this disk)
    write16((uint16_t)m_files.size());

    // Total number of central directory records
    write16((uint16_t)m_files.size());
    // size of the central directory
    write32(m_cd_size);

    // offset of start of central
    write32(m_cd_address);

    // Comment size
    write16(0);
}

void ZipFile::writeString(const string &str)
{
    m_output << str;
}

void ZipFile::write16(uint16_t c)
{
    m_output.put(c & 0xFF);
    m_output.put((c >> 8) & 0xFF);
}

void ZipFile::write32(uint32_t c)
{
    m_output.put(c & 0xFF);
    m_output.put((c >> 8) & 0xFF);
    m_output.put((c >> 16) & 0xFF);
    m_output.put((c >> 24) & 0xFF);
}
