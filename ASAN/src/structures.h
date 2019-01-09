#pragma once

#include "headers.h"

#pragma pack(push, 1)
struct JUMP_DATA
{
	BYTE jmp; // 0xE9 ; JMP
	DWORD adr;
	BYTE nop; // 0x90 ; NOP
};
#pragma pack(pop)

struct Plugin_Config_Structure
{
	int Max_Players;
	int Language;
};

struct ValidNick_Structure
{
	int EnableValidNickHOOK;
	std::regex RegexTemplate;
	int MaxAllowdedSpaces;
};

struct NickLength_Structure
{
	int EnableNickLengthHOOK;
	int MinNickLength;
	int MaxNickLength;
};

struct RepeatedNicks_Structure
{
	int EnableRepeatedNicksHOOK;
	int IgnoreRepeatedNicksCase;
	int MaxRepeatedNicks;
};

struct PlayerConnectionInfo
{
	int PlayerName[MAX_PLAYER_NAME + 1];
	bool Connected;
};