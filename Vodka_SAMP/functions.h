#pragma once

#pragma pack(push, 1)

struct JUMP_DATA
{
	BYTE jmp; // 0xE9 ; JMP
	DWORD adr;
	BYTE nop; // 0x90 ; NOP
};

#pragma pack(pop)

typedef struct Settings
{
	int EnginePlugin;
	int MixSymbols;
};
Settings Config;

size_t CalcDisp(void* lpFirst, void* lpSecond)
{
	return reinterpret_cast<char*>(lpSecond) - (reinterpret_cast<char*>(lpFirst) + 5);
}

bool Unlock(void *address, int len) // by 009, edited by Roman1us
{
#ifdef WIN32
	DWORD
		oldp;
	// Shut up the warnings :D
	return !!VirtualProtect(address, len, PAGE_EXECUTE_READWRITE, &oldp);
#else
	return !mprotect((void*)(((int)address / PAGESIZE) * PAGESIZE), len, PROT_WRITE | PROT_READ | PROT_EXEC);
#endif
}

int checkNickname(char *name)
{
	int len = 0;
	while (*name)
	{
		if (!(
			*name >= '0' && *name <= '9' ||
			*name >= 'A' && *name <= 'Z' ||
			*name >= 'a' && *name <= 'z' ||

			*name >= 'А' && *name <= 'Я' ||
			*name >= 'а' && *name <= 'я' ||

			*name == 'Ё' || *name == 'ё' ||

			*name == ']' ||
			*name == '[' ||
			*name == '_' ||
			*name == '$' ||
			*name == '=' ||
			*name == ')' ||
			*name == '(' ||
			*name == '@' ||
			*name == '.'
			)) return 1;
		name++;
		len++;
	}

	if (len < 3 || len > 20) return 1;

	return 0;
}

int GetFileSize()
{
	FILE * samp_server_exe;

	char fPath[MAX_PATH];

#ifdef WIN32
	GetModuleFileName(NULL, fPath, sizeof(fPath));
	fopen_s(&samp_server_exe, fPath, "rb");
#else
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

void ChangeSymbols(cell &symbol)
{
	if ((symbol >= -64 && symbol <= -1) || symbol == -88 || symbol == -72)
		symbol = 256 + symbol;
}

static int Ini_Handler(void* user, const char* section, const char* name, const char* value)
{
	Settings* pconfig = (Settings*)user;

#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
	if (MATCH("Vodka_SAMP_Settings", "EnginePlugin")) {
		pconfig->EnginePlugin = atoi(value);
	}
	else if (MATCH("Vodka_SAMP_Settings", "AllowMixSymbols")) {
		pconfig->MixSymbols = atoi(value);
	}
	/*else if (MATCH("Section1", "var3")) {
	pconfig->email = strdup(value);
	}*/
	else {
		return 0;  /* unknown section/name, error */
	}
	return 1;
}

void ShowCopiratesInfo()
{
	logprintf("\t[VODKA_SA:MP]: Создатели:[EC]Zero & [KrYpToDeN]!");
	logprintf("\t\t[EC]Zero\t\t| Skype: mactep_3epo");
	logprintf("\t\t[KrYpToDeN]\t\t| Skype: kryptoden");
	logprintf("\t[VODKA_SA:MP]: Приятного распития!");
	logprintf("\t---------------------------------------------------------------\n\n");
}