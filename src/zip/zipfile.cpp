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
#include "zipfile.h"
#include <zlib.h>
#include <cstring>

using namespace std;

ZipFile::ZipFile() : m_cd_address(0), m_cd_size(0)
{
}

ZipFile::~ZipFile()
{
    Close();
}

bool ZipFile::Open(const string &output)
{
    m_output.open(output, ios::binary);
    return m_output.is_open();
}

void ZipFile::Close()
{
    if (m_output.is_open())
    {
        WriteCentralFile();
        WriteCentralDirectory();
        m_output.flush();
        m_output.close();
    }
}

void ZipFile::AddSource(const string &filename, const string &buffer)
{
    AddSource(filename, buffer.c_str(), buffer.size());
}

void ZipFile::AddSource(const string &filename, const char *buffer, const size_t length)
{
    const shared_ptr<AppendedFile> file(new AppendedFile(filename, buffer, length, m_output.tellp()));

    WriteString("\x50\x4B\x03\x04");
    // Unix Type
    Write16(0xA);
    if (file->compressed)
    {
        // Bit flags
        Write16(2);
        // Compression mode
        Write16(Z_DEFLATED);
    }
    else
    {
        Write16(0);
        Write16(0);
    }
    
    Write32(file->date);
    Write32(file->crc);
    
    // Compressed
    Write32(static_cast<uint32_t>(file->compressed_size));
    
    // Uncompressed
    Write32(file->length);
    Write16(static_cast<uint16_t>(filename.size()));
    
    // file extra
    Write16(0);
    WriteString(filename);

    if (file->compressed)
    {
        m_output.write(file->deflate_buffer.get(), static_cast<streamsize>(file->compressed_size));
    }
    else
    {
        m_output.write(buffer, file->length);
    }

    m_files.push_back(file);
}

void ZipFile::WriteCentralFile()
{
    const size_t size = m_files.size();
    m_cd_address = static_cast<uint32_t>(m_output.tellp());

    for (size_t i = 0; i < size; i++)
    {
        const auto file = m_files.at(i);

        WriteString("\x50\x4B\x01\x02");
        Write16(0x031E);
        Write16(0x0A);

        if (file->compressed)
        {
            // bit flag
            Write16(2);
            // compression
            Write16(Z_DEFLATED);
        }
        else
        {
            Write16(0);
            Write16(0);
        }

        Write32(file->date);
        Write32(file->crc);
        
        // Compressed
        Write32(static_cast<uint32_t>(file->compressed_size));
        
        // Uncompressed
        Write32(file->length);
        Write16(static_cast<uint16_t>(file->name.length()));
        
        // file extra
        Write16(0);
        
        // file comment length
        Write16(0);
        
        // dist start
        Write16(0);
        Write16(0);
        Write32(0x81A40000);
        Write32(file->position);
        WriteString(file->name);
    }
    
    m_cd_size = static_cast<uint32_t>(m_output.tellp()) - m_cd_address;
}

void ZipFile::WriteCentralDirectory()
{
    WriteString("\x50\x4B\x05\x06");
    
    // number of this disk
    Write16(0);
    
    // number of this disk start
    Write16(0);
    
    // number of files records (this disk)
    Write16(static_cast<uint16_t>(m_files.size()));

    // Total number of central directory records
    Write16(static_cast<uint16_t>(m_files.size()));
    
    // size of the central directory
    Write32(m_cd_size);

    // offset of start of central
    Write32(m_cd_address);

    // Comment size
    Write16(0);
}

void ZipFile::WriteString(const string &str)
{
    m_output << str;
}

void ZipFile::Write16(const uint16_t word)
{
    m_output.put(static_cast<char>(word & 0xFF));
    m_output.put(static_cast<char>(word >> 8 & 0xFF));
}

void ZipFile::Write32(const uint32_t double_word)
{
    m_output.put(static_cast<char>(double_word & 0xFF));
    m_output.put(static_cast<char>(double_word >> 8 & 0xFF));
    m_output.put(static_cast<char>(double_word >> 16 & 0xFF));
    m_output.put(static_cast<char>(double_word >> 24 & 0xFF));
}
