#pragma once

typedef void(*logprintf_t)(char* format, ...);

logprintf_t logprintf;
void **ppPluginData;
extern void *pAMXFunctions;

#define PLUGIN_VERSION								"5.1"
#define SAMP_VERSION_NAME							", (C)"

#define MAX_PLAYERS									0x3E8
#define MIN_PLAYER_NAME								0x03
#define MAX_PLAYER_NAME								0x18

#define ASAN_DEFAULT_MAX_PLAYERS					MAX_PLAYERS
#define ASAN_DEFAULT_LANGUAGE						0 // 0 - English, 1 - Russian

#define ASAN_DEFAULT_ENABLE_VALID_NICK_HOOK			1
#define ASAN_DEFAULT_REGEX_TEMPLATE					"([а-яА-ЯёЁ0-9\\[\\]\\_\\$\\=\\(\\)\\@\\.]+)|([a-zA-Z0-9\\[\\]\\_\\$\\=\\(\\)\\@\\.]+)"
#define ASAN_DEFAULT_MAX_ALLOWDED_SPACES			0

#define ASAN_DEFAULT_ENABLE_NICK_LENGTH_HOOK		1
#define ASAN_DEFAULT_MIN_NICK_LENGTH				MIN_PLAYER_NAME
#define ASAN_DEFAULT_MAX_NICK_LENGTH				0x14

#define ASAN_DEFAULT_ENABLE_REPEATED_NICKS_HOOK		0
#define ASAN_DEFAULT_IGNORE_REPEATED_NICKS_CASE		1
#define ASAN_DEFAULT_MAX_REPEATED_NICKS				-1


#define ASAN_ERROR_FIND_ADDRESS						0x3E8
#define ASAN_ERROR_HOOK_STRUCTURE					0x7D0

#include <regex>
#include "SDK/plugin.h"
#include "main.h"
#include "os_info.h"

#include "functions.h"
#include "pawn_hook.h"
#include "INI/INIReader.h"