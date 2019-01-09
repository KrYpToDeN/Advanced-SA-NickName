#pragma once

/*
	For Linux only
*/

#include "headers.h"

#if (defined(WIN32) || defined(_WIN32)) && defined(_MSC_VER)
	#define MEMORY_START						0x401000
	#define MAX_VALID_NICKNAME_ADRESSES			0x5A
	#define MAX_REPEATED_NICKS_ADRESSES			0x59
	#define MAX_NICKNAME_LENGTH_ADRESSES		0xA
#else // Linux
	#define MEMORY_START					0x804B430
	#define MAX_VALID_NICKNAME_ADRESSES		0x75
	#define MAX_REPEATED_NICKS_ADRESSES		0x6D
	#define MAX_NICKNAME_LENGTH_ADRESSES	0x06

	#define DWORD				unsigned long
	#define BYTE				unsigned char

	#define __cdecl __attribute__((__cdecl__)) // for HOOK_RepeatedNicks

	#define PAGESIZE			4096
	#define MAX_PATH			260
#endif