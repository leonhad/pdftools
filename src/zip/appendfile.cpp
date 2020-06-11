#include "appendedfile.h"

AppendedFile::AppendedFile()
{
    name = "";
    length = 0;
    compressed = false;
    compressed_size = 0;
    date = 0;
    crc = 0;
    position = 0;
    
    char *deflate_buffer = nullptr;
    try
    {
        deflate_buffer = compress(buffer, length, file->compressed_size);

        if (file->compressed_size < file->length)
        {
            file->compressed = true;
        }
        else
        {
            file->compressed = false;
            file->compressed_size = file->length;
        }
    }
    catch (exception &)
    {
        // File in deflate
        file->compressed = false;
        file->compressed_size = file->length;
    }
}
