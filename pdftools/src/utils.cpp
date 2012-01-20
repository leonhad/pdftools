#include "utils.h"
#include "config.h"
#include <dirent.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstring>

using namespace std;

static bool _verbose = false;

void verbose_message(string msg)
{
    if (verbose_mode()) {
        cout << PACKAGE_NAME << ": " << msg << endl;
    }
}

void error_message(string msg)
{
    cerr << PACKAGE_NAME << ": " << msg << endl;
}

void set_verbose_mode(const bool verbose)
{
    _verbose = verbose;
}

bool verbose_mode()
{
    return _verbose;
}
