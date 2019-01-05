#pragma once

#if (defined(WIN32) || defined(_WIN32)) && defined(_MSC_VER)
#include <windows.h>
#else // Linux
#include <sys/mman.h>
#include <unistd.h>
#include <string.h> // for strlen function
#endif

#include "addresses.h"

#include <regex>
#include "constants.h"