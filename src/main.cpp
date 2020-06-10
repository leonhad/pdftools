/*
 * This file is part of PDF Tools.
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
#include "utils.h"
#include "converter.h"
#include "config.h"

#include <iostream>
#include <memory>
#include <getopt.h>

using namespace std;

/**
 * Start the application.
 *
 * \param argc total of program parameters.
 * \param argv the program parameters.
 * \return the program return code.
 */
int main(int argc, char *argv [])
{
    int verbose_flag = 0;
    bool error = false;
    string fileout;
    string format = "epub";
    
    const struct option long_options [] =
    {
        { "verbose", no_argument, &verbose_flag, 1 },
        { "help", no_argument, 0, 'h' },
        { "version", no_argument, 0, 'v' },
        { "o", required_argument, 0, 'o' },
        { "format", required_argument, 0, 'f' },
        { 0, 0, 0, 0 }
    };
    
    while (true)
    {
        int option_index = 0;
        auto c = getopt_long(argc, argv, "hvo:f:", long_options, &option_index);
        
        /* Detect the end of the options. */
        if (c == -1)
        {
            break;
        }
        
        switch (c)
        {
            case 'o':
                if (optarg)
                {
                    fileout = optarg;
                }
                
                break;
            case 'h':
                wcout << PACKAGE_NAME;
                wcout << L" is a high level tools to convert PDF files to ePUB format.\n\n";
                wcout << L"Usage: " << PACKAGE_NAME << " [options] file [...]\n";
                wcout << L"Options:\n";
                wcout << L"  -f <format>, --format=<format>\toutput file format [epub]\n";
                wcout << L"  -h, --help\t\t\t\tdisplay this information and quit\n";
                wcout << L"  -o <file>\t\t\t\tset the output file\n";
                wcout << L"  -v, --version\t\t\t\tdisplay the version information\n";
                wcout << L"  --verbose\t\t\t\trun in verbose mode\n\n";
                wcout << L"In conformance on copyright issues, ";
                wcout << L" this tool don't support encrypted files.\n";
                wcout << L"Report bugs to <https://github.com/leonhad/pdftools/issues>\n";
                return EXIT_SUCCESS;
            case 'v':
                wcout << PACKAGE_STRING;
                wcout << L"\n\nCopyright (C) 2014 Leonardo Alves da Costa.\n";
                wcout << L"License GPLv3+: GNU GPL version 3 or later ";
                wcout << L" <http://gnu.org/licenses/gpl.html>\n";
                wcout << L"This is free software: you are free to change and redistribute it.\n";
                wcout << L"There is NO WARRANTY, to the extent permitted by law.\n\n";
                wcout << L"Written by Leonardo Alves da Costa.\n";
                return EXIT_SUCCESS;
            case 'f':
                format = optarg;
                if (format != "epub")
                {
                    error_message(L"format not supported.");
                    error = true;
                    break;
                }
            default:
                break;
        }
    }
    
    if (verbose_flag)
    {
        set_verbose_mode(true);
    }
    
    if (optind >= argc && not error)
    {
        error_message(L"no input file");
        error = true;
    }
    
    if (error)
    {
        wcout << L"Try `" << PACKAGE_NAME << L" --help' for usage.\n";
        return EXIT_FAILURE;
    }
    else
    {
        for (int loop = optind; loop < argc; loop++)
        {
            try
            {
                Converter converter(argv[loop], fileout, format);
                converter.convert();
            }
            catch (exception &e)
            {
                error_message(e);
            }
        }
    }
    
    return EXIT_SUCCESS;
}
