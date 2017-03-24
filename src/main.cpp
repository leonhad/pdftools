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
#include "utils.h"
#include "converter.h"
#include <getopt.h>
#include <iostream>
#include <config.h>

using namespace std;

/**
 * Start the application
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
    { 0, 0, 0, 0 } };

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
            cout << PACKAGE_NAME << " is a high level tools to convert PDF files to ePUB format."
                    << endl;
            cout << endl;
            cout << "Usage: " << PACKAGE_NAME << " [options] file..." << endl;
            cout << "Options:" << endl;
            cout << "  -f <format>, --format=<format>\toutput file format [epub]" << endl;
            cout << "  -h, --help\t\t\t\tdisplay this information and quit" << endl;
            cout << "  -o <file>\t\t\t\tset the output file" << endl;
            cout << "  -v, --version\t\t\t\tdisplay the version information" << endl;
            cout << "  --verbose\t\t\t\trun in verbose mode" << endl;
            cout << endl;
            cout << "In conformance on copyright issues, this tool don't support encrypted files."
                    << endl;
            cout << "Report bugs to <https://github.com/leonhad/pdftools/issues>" << endl;
            return EXIT_SUCCESS;
        case 'v':
            cout << PACKAGE_STRING << endl;
            cout << endl;
            cout << "Copyright (C) 2014 Leonardo Alves da Costa." << endl;
            cout << "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>"
                    << endl;
            cout << "This is free software: you are free to change and redistribute it." << endl;
            cout << "There is NO WARRANTY, to the extent permitted by law." << endl;
            cout << endl;
            cout << "Written by Leonardo Alves da Costa." << endl;
            return EXIT_SUCCESS;
        case 'f':
            format = optarg;
            if (format != "epub")
            {
                string msg = "format ";
                msg += format;
                msg += " not supported.";
                error_message(msg.c_str());
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

    if (optind >= argc && !error)
    {
        error_message("no input file");
        error = true;
    }

    if (error)
    {
        cout << "Try `" << PACKAGE_NAME << " --help' for usage." << endl;
        return EXIT_FAILURE;
    }
    else
    {
        for (int loop = optind; loop < argc; loop++)
        {
            try
            {
                Converter converter(argv [loop], fileout, format);
                converter.convert();
            } catch (exception &e)
            {
                error_message(e.what());
            }
        }
    }

    return EXIT_SUCCESS;
}
