#pragma once

#pragma pack(push, 1)

struct JUMP_DATA
{
	BYTE jmp; // 0xE9 ; JMP
	DWORD adr;
	BYTE nop; // 0x90 ; NOP
};

#pragma pack(pop)

size_t CalcDisp(void* lpFirst, void* lpSecond)
{
	return reinterpret_cast<char*>(lpSecond)-(reinterpret_cast<char*>(lpFirst)+5);
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

			*name >= 'À' && *name <= 'ß' ||
			*name >= 'à' && *name <= 'ÿ' ||

			*name == '¨' || *name == '¸' ||

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
	/*char szBuffer[256];

	GetModuleFileName(NULL, szBuffer, 256);*/

	FILE * samp_server_exe;

	samp_server_exe = fopen(SAMP_FILE_NAME1, "rb");
	if (!samp_server_exe)
		samp_server_exe = fopen(SAMP_FILE_NAME2, "rb");


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