#pragma once

#include <stdio.h>
#include <regex>

char samp_version_name[6] = ", (C)";

#define ASAN_DEFAULT_ENGINE			true
#define ASAN_DEFAULT_TEMPLATE		"[à-ÿÀ-ß¸¨a-zA-Z0-9\\[\\]\\_\\$\\=\\(\\)\\@\\.]+"
#define ASAN_DEFAULT_REGCASE		true
#define ASAN_DEFAULT_SPACE			false
#define ASAN_DEFAULT_MAX_SPACES		0

#include "SDK/plugin.h"

#include "main.h"
#include "os_info.h"
#include "functions.h"
#include "INI/INIReader.h"