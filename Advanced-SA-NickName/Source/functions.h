#pragma once

#pragma pack(push, 1)

struct JUMP_DATA
{
	BYTE jmp; // 0xE9 ; JMP
	DWORD adr;
	BYTE nop; // 0x90 ; NOP
};

#pragma pack(pop)

struct Settings
{
	bool EnginePlugin;
	std::regex RegexTemplate;
	bool AllowSpace;
	int MaxSpaces;
} Config;

size_t CalcDisp(void* lpFirst, void* lpSecond)
{
	return reinterpret_cast<char*>(lpSecond) - (reinterpret_cast<char*>(lpFirst) + 5);
}

bool Unlock(void *address, int len)
{
#if (defined(WIN32) || defined(_WIN32)) && defined(_MSC_VER)
	DWORD
		oldp;
	// Shut up the warnings :D
	return !!VirtualProtect(address, len, PAGE_EXECUTE_READWRITE, &oldp);
#else // Linux
	return !mprotect((void*)(((int)address / PAGESIZE) * PAGESIZE), len, PROT_WRITE | PROT_READ | PROT_EXEC);
#endif
}

int checkNickname(char *name)
{
	int len = strlen(name);
	if (std::regex_match(name, Config.RegexTemplate) && len >= 3 && len <= 20)
	{
		if (Config.MaxSpaces > 0 && Config.AllowSpace)
		{
			int total_spaces = 0;
			while (Config.MaxSpaces != total_spaces && *name)
			{
				if (*name == '_')
				{
					*name = ' ';
					total_spaces++;
				}
				name++;
			}
		}
		return 0;
	}
	return 1;
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

bool CheckMemmory(char*check, char*mas, int mas_length)
{
	for (int i = 0; i < mas_length; i++)
	{
		if (*check != *mas)
			return false;
		check++;
		mas++;
	}
	return true;
}

inline void ChangeSymbols(cell &symbol)
{
	if (symbol < 0)
	{
		symbol += 256;
	}
}

void ShowCopiratesInfo()
{
	logprintf("\t[ASAN]: https://github.com/KrYpToDeN/Advanced-SA-NickName");
	logprintf("\t-----------------------------------------------------\n\n");
}