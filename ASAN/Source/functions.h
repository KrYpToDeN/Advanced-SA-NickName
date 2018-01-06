#pragma once

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
}Plugin_Config;

struct ValidNick_Structure
{
	int EnableValidNickHOOK;
	std::regex RegexTemplate;
	int MaxAllowdedSpaces;
} ValidNick_Config;

struct NickLength_Structure
{
	int EnableNickLengthHOOK;
	int MinNickLength;
	int MaxNickLength;
} NickLength_Config;

struct RepeatedNicks_Structure
{
	int EnableRepeatedNicksHOOK;
	int IgnoreRepeatedNicksCase;
	int MaxRepeatedNicks;
} RepeatedNicks_Config;

struct PlayerConnectionInfo
{
	int PlayerName[MAX_PLAYER_NAME + 1];
	bool Connected;
}PlayerInfo[MAX_PLAYERS];

size_t CalcDisp(void* lpFirst, void* lpSecond)
{
	return reinterpret_cast<char*>(lpSecond) - (reinterpret_cast<char*>(lpFirst) + 5);
}

bool UnblockMemory(void *address, int len)
{
#if (defined(WIN32) || defined(_WIN32)) && defined(_MSC_VER)
	DWORD
		oldp;
	return !!VirtualProtect(address, len, PAGE_EXECUTE_READWRITE, &oldp);
#else
	return !mprotect((void*)(((int)address / PAGESIZE) * PAGESIZE), len, PROT_WRITE | PROT_READ | PROT_EXEC);
#endif
}

int GetPlayerNameINT_Length(int name[])
{
	int rezult = 0;
	for (int i = 0; i < NickLength_Config.MaxNickLength; i++)
	{
		if (name[i] == EOF)
			break;
		rezult++;
	}
	return rezult;
}

bool IsNonCaseSymbolsMatch(int player_name[], char *connected_name)
{
	int str_lenght = GetPlayerNameINT_Length(player_name);
	if (str_lenght != strlen(connected_name))
		return false;

	for (int i = 0; i < str_lenght; i++)
	{
		int sym_str2 = (int)*connected_name;
		if (sym_str2 < 0)
			sym_str2 = (256 + sym_str2);
		connected_name++;
		if (player_name[i] != sym_str2 && (player_name[i] - 32) != sym_str2 && player_name[i] != (sym_str2 - 32) && (player_name[i] - 16) != sym_str2 && player_name[i] != (sym_str2 - 16))
			return false;
	}
	return true;
}

bool IsCaseSymbolsMatch(int player_name[], char *connected_name)
{
	int str_lenght = GetPlayerNameINT_Length(player_name);
	if (str_lenght != strlen(connected_name))
		return false;

	for (int i = 0; i < str_lenght; i++)
	{
		int sym_str2 = (int)*connected_name;
		if (sym_str2 < 0)
			sym_str2 = (256 + sym_str2);
		connected_name++;

		if (player_name[i] != sym_str2)
			return false;
	}
	return true;
}

int HOOK_ValidNickName(char *name) // Thanks to [EC]Zero for helping with this hook
{
	int name_length = strlen(name);
	if (name_length < NickLength_Config.MinNickLength || name_length > NickLength_Config.MaxNickLength)
		return 1; // DON'T Allow Connection

	if (std::regex_match(name, ValidNick_Config.RegexTemplate))
	{
		if (ValidNick_Config.MaxAllowdedSpaces > 0 || ValidNick_Config.MaxAllowdedSpaces == -1)
		{
			int total_spaces = 0;
			while (*name)
			{
				if (ValidNick_Config.MaxAllowdedSpaces == total_spaces)
					break;

				if (*name == '_')
				{
					*name = ' ';
					if(ValidNick_Config.MaxAllowdedSpaces > 0)
						total_spaces++;
				}
				name++;
			}
		}
		return 0; // Allow Connection
	}
	return 1; // DON'T Allow Connection
}

bool IsMaxRepeatedNicksError(char *name)
{
	if (RepeatedNicks_Config.MaxRepeatedNicks != ASAN_DEFAULT_MAX_REPEATED_NICKS)
	{
		int _max_repeated_nicks = 0;
		for (int i = 0; i < Plugin_Config.Max_Players; i++)
		{
			if (PlayerInfo[i].Connected == true)
			{
				if (IsCaseSymbolsMatch(PlayerInfo[i].PlayerName, name) == true || IsNonCaseSymbolsMatch(PlayerInfo[i].PlayerName, name) == true)
				{
					_max_repeated_nicks++;
					if (_max_repeated_nicks > RepeatedNicks_Config.MaxRepeatedNicks)
						return true;
				}
			}
		}
	}
	return false;
}

bool IsIgnoreRepeatedNicksCaseError(char *name)
{
	if (RepeatedNicks_Config.IgnoreRepeatedNicksCase == 0)
	{
		for (int i = 0; i < Plugin_Config.Max_Players; i++)
		{
			if (PlayerInfo[i].Connected == true)
			{
				if (IsCaseSymbolsMatch(PlayerInfo[i].PlayerName, name) == false && IsNonCaseSymbolsMatch(PlayerInfo[i].PlayerName, name) == true)
				{
					return true;
				}
			}
		}
	}
	return false;
}

#if (defined(WIN32) || defined(_WIN32)) && defined(_MSC_VER)
int __stdcall HOOK_RepeatedNicks(char *name)
#else
int __cdecl HOOK_RepeatedNicks(int, char *name)
#endif
{
	bool check_free_id = false;
	for (int i = 0; i < Plugin_Config.Max_Players; i++)
	{
		if (PlayerInfo[i].Connected == false)
		{
			check_free_id = true;
			break;
		}
	}

	if(check_free_id == false)
		return 1; // DON'T Allow Connection

	if (IsMaxRepeatedNicksError(name))
		return 1;  // DON'T Allow Connection

	if(IsIgnoreRepeatedNicksCaseError(name))
		return 1;  // DON'T Allow Connection

	return 0; // Allow Connection
}

int GetFileSize()
{
	FILE * samp_server_exe;

	char fPath[MAX_PATH];

#if (defined(WIN32) || defined(_WIN32)) && defined(_MSC_VER) // Windows
	GetModuleFileName(NULL, fPath, sizeof(fPath));
	fopen_s(&samp_server_exe, fPath, "rb");
#else // Linux
	int bytes = readlink("/proc/self/exe", fPath, sizeof(fPath) - 1);
	fPath[bytes] = '\0';
	samp_server_exe = fopen(fPath, "rb");
#endif

	int file_size = 0;
	if (samp_server_exe)
	{
		fseek(samp_server_exe, 0, SEEK_END);
		file_size = ftell(samp_server_exe);
		fclose(samp_server_exe);
	}
	return file_size;
}

bool GetNickLengthAddresses(char *address, char *&MinimumNickLength, char *&MaximumNickLength)
{
	char *_MinimumNickLength = 0;
	char *_MaximumNickLength = 0;

	int status = 0;
	for (int i = 0; i < MAX_NICKNAME_LENGTH_ADRESSES; i++)
	{
		if (NickLength_Addresses[i] == 0x3C)
		{
			status++;
			if(_MinimumNickLength == 0)
				_MinimumNickLength = (address + 1);
			else if (_MaximumNickLength == 0)
			{
				_MaximumNickLength = (address + 1);
				break;
			}
		}
		address++;
	}

	MinimumNickLength = _MinimumNickLength;
	MaximumNickLength = _MaximumNickLength;

	if (status != 2)
		return false;
	else return true;
}

bool CheckMemmory(char*check, char*mas, int mas_length, bool include_null = true) // If 'include_null = false' - Don't check NULL number
{
	for (int i = 0; i < mas_length; i++)
	{
		if (include_null == false && *mas == NULL) // Don't check NULL number
		{
			check++;
			mas++;
			continue;
		}

		if (*check != *mas)
			return false;
		check++;
		mas++;
	}
	return true;
}

void ShowErrorMessage(char hook_name[], int error_code)
{
	if (Plugin_Config.Language == 0)
		logprintf("\t[ASAN | %s | ERROR]:\tError code - 0x%x*\t->Missing..", hook_name, error_code);
	else
		logprintf("\t[ASAN | %s | ������]:\t��� ������ - 0x%x*\t->����������..", hook_name, error_code);
}

void ShowCopiratesInfo()
{
	if (Plugin_Config.Language == 0)
	{
		logprintf("\t[ASAN | WEBSITE]:\thttps://github.com/KrYpToDeN/Advanced-SA-NickName");
		logprintf("\t------------------------------------------------------------------\n\n");
	}
	else
	{
		logprintf("\t[ASAN | ����]:\t\thttps://github.com/KrYpToDeN/Advanced-SA-NickName");
		logprintf("\t------------------------------------------------------------------\n\n");
	}
}