#pragma once

#include <stdio.h>

char samp_version_name[6] = ", (C)";

#define ASAN_DEFAULT_ENGINE			true
#define ASAN_DEFAULT_TEMPLATE		"([à-ÿÀ-ß¸¨0-9\\[\\]\\_\\$\\=\\(\\)\\@\\.]{3,20}$)|([a-zA-Z0-9\\[\\]\\_\\$\\=\\(\\)\\@\\.]{3,20}$)"
#define ASAN_DEFAULT_REGCASE		true
#define ASAN_DEFAULT_SPACE			false
#define ASAN_DEFAULT_MAX_SPACES		0

#include "SDK/plugin.h"

#include <regex>

#include "main.h"
#include "os_info.h"
#include "functions.h"
#include "INI/INIReader.h"