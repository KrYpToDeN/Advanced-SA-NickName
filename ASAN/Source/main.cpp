#define HAVE_STDINT_H

#include "main.h"

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

	Plugin_Config.Language = ASAN_DEFAULT_LANGUAGE;

	if (Plugin_Config.Language == 0)
	{
		logprintf("\n\n\t-------------------Advanced SA NickName (ASAN)--------------------");
		logprintf("\t[ASAN | Launching]:\tPlugin v%s by [KrYpToDeN]", PLUGIN_VERSION);
		logprintf("\t[ASAN | Loading]:\tPlugin loading..\n");
	}
	else
	{
		logprintf("\n\n\t-------------------Advanced SA NickName (ASAN)--------------------");
		logprintf("\t[ASAN | ������]:\t������ v%s by [KrYpToDeN]", PLUGIN_VERSION);
		logprintf("\t[ASAN | ��������]:\t������ �����������..\n");
	}

	INIReader reader("scriptfiles/ASAN_Config.ini");
	if (reader.ParseError() < 0)
	{
		if (Plugin_Config.Language == 0)
			logprintf("\t[ASAN | SETTINGS]:\tCreating file `ASAN_Config.ini` in `scriptfiles` folder\n");
		else
			logprintf("\t[ASAN | ���������]:\t������ ���� `ASAN_Config.ini` � ����� `scriptfiles`\n");

		FILE *SettingFile;
		SettingFile = fopen("scriptfiles/ASAN_Config.ini", "wt");

		if (!SettingFile)
		{
			if (Plugin_Config.Language == 0)
				logprintf("\t[ASAN | ERROR]:\tMissing `scriptfiles` folder or there are no rights to write to the disk.\n\t->Aborting..");
			else
				logprintf("\t[ASAN | ������]:\t����������� ����� `scriptfiles` ��� �� ����������� ����� ��� ������ �� ����.\n\t->�������������..");

			ShowCopiratesInfo();
			return false;
		}

		// Plugin_Config
		Plugin_Config.Max_Players						= ASAN_DEFAULT_MAX_PLAYERS;
		//Plugin_Config.Language						= ASAN_DEFAULT_LANGUAGE; // Located at the beginning of the function

		// ValidNick_Config
		ValidNick_Config.EnableValidNickHOOK			= ASAN_DEFAULT_ENABLE_VALID_NICK_HOOK;
		std::regex temp_regex_template(ASAN_DEFAULT_REGEX_TEMPLATE);
		ValidNick_Config.RegexTemplate					= temp_regex_template;
		ValidNick_Config.MaxAllowdedSpaces				= ASAN_DEFAULT_MAX_ALLOWDED_SPACES;

		// NickLength_Config
		NickLength_Config.EnableNickLengthHOOK			= ASAN_DEFAULT_ENABLE_NICK_LENGTH_HOOK;
		NickLength_Config.MinNickLength					= ASAN_DEFAULT_MIN_NICK_LENGTH;
		NickLength_Config.MaxNickLength					= ASAN_DEFAULT_MAX_NICK_LENGTH;

		// RepeatedNicks_Config
		RepeatedNicks_Config.EnableRepeatedNicksHOOK	= ASAN_DEFAULT_ENABLE_REPEATED_NICKS_HOOK;
		RepeatedNicks_Config.IgnoreRepeatedNicksCase	= ASAN_DEFAULT_IGNORE_REPEATED_NICKS_CASE;
		RepeatedNicks_Config.MaxRepeatedNicks			= ASAN_DEFAULT_MAX_REPEATED_NICKS;


		
		if (Plugin_Config.Language == 0)
		{
			char ftext[2321 + sizeof(ASAN_DEFAULT_REGEX_TEMPLATE)];
			sprintf(ftext, "\
[ASAN_Plugin_Config]\n\n\
Max_Players = %d\n\
;Max players of your server. DON'T SET meaning less, than was setted in your server.cfg.\n\
;By default it's = %d\n\n\
Language = %d\n\
;Plugin's log language. 0 - English, 1 - Russian\n\n\n\
[ASAN_ValidNick_Settings]\n\n\
EnableValidNickHOOK = %d\n\
;Enable symbols check hook - 1, Disable symbols check hook - 0\n\n\
RegexTemplate = %s\n\
;Regex Template! Don't include nick's length!\n\
;Some Regex templates you can find in plugin's archive\n\n\
MaxAllowdedSpaces = %d\n\
;Number of replace the underscore symbols(_) to space symbols( ), By Default it's = 0\n\
;(-1 - no restrictions(all symbols will be replaced), 0 - disabled(By default))\n\
;Example. If 'MaxAllowdedSpaces = 1' -> 'John_Connor' will be in server side (In TAB menu) such as 'John Connor' after player connected.\n\
;Another underscore symbols will be missing (John_Connor_Jr will be John Connor_Jr)\n\
;Be careful while using this function with your DataBase!\n\
;DON'T USE SPACES INTO CLIENT SIDE (SA-MP CLIENT WINDOW)! ONLY SERVER SIDE!\n\n\n\
[ASAN_NickLength_Settings]\n\n\
EnableNickLengthHOOK = %d\n\
;Enable nick length number hook - 1. Disable nick length number hook - 0.\n\n\
MinNickLength = %d\n\
;Minimum length of NickName. By default it's = %d\n\
;This should be > 0!\n\n\
MaxNickLength = %d\n\
;Maximum length of NickName. By default it's = %d\n\
;Do not increase it under than %d!\n\n\n\
[ASAN_RepeatedNicks_Settings]\n\n\
EnableRepeatedNicksHOOK = %d\n\
;Enable repeated nicknames hook - 1, Disable repeated nicknames hook - 0\n\
;Two or more players can use same NickNames\n\n\
IgnoreRepeatedNicksCase = %d\n\
;When set to - 1, the case doesn't matter - nickname 'heLLo' is the same as 'Hello'. When - 0, they're not the same.\n\
;Example. If 'IgnoreRepeatedNicksCase = 1' you can use same NickName (Example. Alex and ALEX) in any case at the same time. If it's = 0, only one case can be used (who was connected first)\n\
;Attention! This function was tested only with Russian and English symbols! Nobody knows how it will work with another language!\n\n\
MaxRepeatedNicks = %d\n\
;The number of repeated nicknames (-1 - no restrictions, 0 - is the same, as 'EnableRepeatedNicksHOOK = 0')\n\n\n\n\
;If you have any questions, please write me into Issue on GitHub - https://github.com/KrYpToDeN/Advanced-SA-NickName/issues",
			Plugin_Config.Max_Players, ASAN_DEFAULT_MAX_PLAYERS, Plugin_Config.Language,
			ValidNick_Config.EnableValidNickHOOK, ASAN_DEFAULT_REGEX_TEMPLATE, ValidNick_Config.MaxAllowdedSpaces,
			NickLength_Config.EnableNickLengthHOOK, NickLength_Config.MinNickLength, ASAN_DEFAULT_MIN_NICK_LENGTH, NickLength_Config.MaxNickLength, ASAN_DEFAULT_MAX_NICK_LENGTH, MAX_PLAYER_NAME,
			RepeatedNicks_Config.EnableRepeatedNicksHOOK, RepeatedNicks_Config.IgnoreRepeatedNicksCase, RepeatedNicks_Config.MaxRepeatedNicks);

			fwrite(ftext, 1, strlen(ftext), SettingFile);
		}
		else
		{
			char ftext[2505 + sizeof(ASAN_DEFAULT_REGEX_TEMPLATE)];
			sprintf(ftext, "\
[ASAN_Plugin_Config]\n\n\
Max_Players = %d\n\
;������������ ���������� ������� ������ �������. �� �������������� �������� ������, ��� ����������� � ����� server.cfg.\n\
;�� ��������� = %d\n\n\
Language = %d\n\
;���� � ����� �������. 0 - ����������, 1 - �������\n\n\n\
[ASAN_ValidNick_Settings]\n\n\
EnableValidNickHOOK = %d\n\
;�������� ��� �������� �������� - 1, ��������� ��� �������� �������� - 0\n\n\
RegexTemplate = %s\n\
;������ ����������� ��������� (Regex)! �� ��������� � ������ ����� ����!\n\
;��������� ������� �� ������ ����� � ������ �������\n\n\
MaxAllowdedSpaces = %d\n\
;���������� ����� �������� ������� �������������(_) �� ������� �������( )\n\
;(-1 - ��� �����������(��� ������� ����� ��������), 0 - ���������(�� ���������))\n\
;������. ���� 'MaxAllowdedSpaces = 1' -> 'John_Connor' ����� �� ��������� ������� (� TAB ����) ��� 'John Connor' ����� ����������� ������.\n\
;������ ������� ������� ������������� ����� ��������� (John_Connor_Jr ������ John Connor_Jr)\n\
;������ ���������, ��������� ������ ������� � ����� ����� ������!\n\
;�� ����������� ������� �� ������� ������� (���� SA-MP)! ������ ��������� �������!\n\n\n\
[ASAN_NickLength_Settings]\n\n\
EnableNickLengthHOOK = %d\n\
;�������� ��� ����� �������� ���� - 1. ��������� ��� ����� �������� ���� - 0.\n\n\
MinNickLength = %d\n\
;����������� ����� ��������. �� ��������� = %d\n\
;�������� ������ ���� > 0!\n\n\
MaxNickLength = %d\n\
;������������ ����� ��������. �� ��������� = %d\n\
;�� ������������ ��� ������� ������ ��� %d!\n\n\n\
[ASAN_RepeatedNicks_Settings]\n\n\
EnableRepeatedNicksHOOK = %d\n\
;�������� ��� ��������� ����� - 1, ��������� ��� ��������� ����� - 0\n\
;��� ��� ����� ������� ����� ������������ ���������� ��������\n\n\
IgnoreRepeatedNicksCase = %d\n\
;����� ����������� - 1, ������� �� ����������� - ��� '������' ���� �����, ��� � '������'. ����� - 0, ��� ��������� �������.\n\
;������. ���� 'IgnoreRepeatedNicksCase = 1' �� ������ ������������ ��� �� ����� ������� (������. ����� � �����) � ����� �������� ������������. ���� ��� = 0, ������ ���� ������� ����� ���� ����������� (���, ��� ����������� ������)\n\
;��������! ��� ������� ���� �������������� ������ � �������� � ����������� ���������! ����� �� �����, ��� ��� ����� �������� � ������ ������!\n\n\
MaxRepeatedNicks = %d\n\
;���������� ��������� ��������� (-1 - ��� �����������, 0 - ���� �����, ��� � 'EnableRepeatedNicksHOOK = 0')\n\n\n\n\
;���� � ��� ���� ����� - ���� �������, ���������� �������� ��� � Issue �� GitHub - https://github.com/KrYpToDeN/Advanced-SA-NickName/issues",
			Plugin_Config.Max_Players, ASAN_DEFAULT_MAX_PLAYERS, Plugin_Config.Language,
			ValidNick_Config.EnableValidNickHOOK, ASAN_DEFAULT_REGEX_TEMPLATE, ValidNick_Config.MaxAllowdedSpaces,
			NickLength_Config.EnableNickLengthHOOK, NickLength_Config.MinNickLength, ASAN_DEFAULT_MIN_NICK_LENGTH, NickLength_Config.MaxNickLength, ASAN_DEFAULT_MAX_NICK_LENGTH, MAX_PLAYER_NAME,
			RepeatedNicks_Config.EnableRepeatedNicksHOOK, RepeatedNicks_Config.IgnoreRepeatedNicksCase, RepeatedNicks_Config.MaxRepeatedNicks);

			fwrite(ftext, 1, strlen(ftext), SettingFile);
		}
		
		fclose(SettingFile);
	}
	else
	{
		// ASAN_Plugin_Config
		Plugin_Config.Max_Players = reader.GetInteger("ASAN_Plugin_Config", "Max_Players", ASAN_DEFAULT_MAX_PLAYERS);
		Plugin_Config.Language = reader.GetInteger("ASAN_Plugin_Config", "Language", ASAN_DEFAULT_MAX_PLAYERS);

		// ASAN_ValidNick_Settings
		char RegexText[512];
		ValidNick_Config.EnableValidNickHOOK = reader.GetInteger("ASAN_ValidNick_Settings", "EnableValidNickHOOK", ASAN_DEFAULT_ENABLE_VALID_NICK_HOOK);
		sprintf(RegexText, reader.Get("ASAN_ValidNick_Settings", "RegexTemplate", ASAN_DEFAULT_REGEX_TEMPLATE).c_str());
		std::regex temp_regex_template(RegexText);
		ValidNick_Config.RegexTemplate = temp_regex_template;
		ValidNick_Config.MaxAllowdedSpaces = reader.GetInteger("ASAN_ValidNick_Settings", "MaxAllowdedSpaces", ASAN_DEFAULT_MAX_ALLOWDED_SPACES);

		// ASAN_NickLength_Settings
		NickLength_Config.EnableNickLengthHOOK = reader.GetInteger("ASAN_NickLength_Settings", "EnableNickLengthHOOK", ASAN_DEFAULT_ENABLE_NICK_LENGTH_HOOK);
		NickLength_Config.MinNickLength = reader.GetInteger("ASAN_NickLength_Settings", "MinNickLength", ASAN_DEFAULT_MIN_NICK_LENGTH);
		NickLength_Config.MaxNickLength = reader.GetInteger("ASAN_NickLength_Settings", "MaxNickLength", ASAN_DEFAULT_MAX_NICK_LENGTH);

		// ASAN_RepeatedNicks_Settings
		RepeatedNicks_Config.EnableRepeatedNicksHOOK = reader.GetInteger("ASAN_RepeatedNicks_Settings", "EnableRepeatedNicksHOOK", ASAN_DEFAULT_ENABLE_REPEATED_NICKS_HOOK);
		RepeatedNicks_Config.IgnoreRepeatedNicksCase = reader.GetInteger("ASAN_RepeatedNicks_Settings", "IgnoreRepeatedNicksCase", ASAN_DEFAULT_IGNORE_REPEATED_NICKS_CASE);
		RepeatedNicks_Config.MaxRepeatedNicks = reader.GetInteger("ASAN_RepeatedNicks_Settings", "MaxRepeatedNicks", ASAN_DEFAULT_MAX_REPEATED_NICKS);
	}

	for (int i = 0; i < Plugin_Config.Max_Players; i++)
	{
		PlayerInfo[i].Connected = false;
		
		for (int j = 0; j < NickLength_Config.MaxNickLength; j++)
			PlayerInfo[i].PlayerName[j] = EOF;
	}

	int file_size = GetFileSize();

	if (!UnblockMemory((void*)MEMORY_START, file_size))
	{
		if (Plugin_Config.Language == 0)
			logprintf("\t[ASAN | ERROR]:\tCan't unblock SA:MP's memory.\n\tWrite into issue in GitHub, please! https://github.com/KrYpToDeN/Advanced-SA-NickName/issues \n\t->Aborting..");
		else
			logprintf("\t[ASAN | ������]:\t�� ���� �������������� ������ SA:MP.\n\t�������� ��� � issue �� GitHub, ����������! https://github.com/KrYpToDeN/Advanced-SA-NickName/issues \n\t->�������������..");
		
		ShowCopiratesInfo();
		return false;
	}

	bool 
		error_find_address = false,
		error_hook_strucrute = false;

	if (ValidNick_Config.EnableValidNickHOOK == 1)  // Thanks to [EC]Zero for helping with this hook
	{
		void *ValidNick_Func_ADDR = 0;
		for (char * address = (char *)MEMORY_START; address < ((char *)MEMORY_START + file_size - MAX_VALID_NICKNAME_ADRESSES); address++)
		{
			if (CheckMemmory(address, reinterpret_cast<char*>(ValidNickName_Addresses), MAX_VALID_NICKNAME_ADRESSES))
			{
				ValidNick_Func_ADDR = address; // Our function Address
				break;
			}
		}

		if (ValidNick_Func_ADDR == 0)
		{
			error_find_address = true;
			ShowErrorMessage("ValidNick", ASAN_ERROR_FIND_ADDRESS);
		}
		else
		{
			if (Plugin_Config.Language == 0)
				logprintf("\t[ASAN | ValidNick]:\tMemory address '0x%x' was found.", ValidNick_Func_ADDR);
			else
				logprintf("\t[ASAN | ValidNick]:\t����� ������ '0x%x' ��� ������.", ValidNick_Func_ADDR);

			JUMP_DATA* ValidNick_Func = (JUMP_DATA*)ValidNick_Func_ADDR;

			if (ValidNick_Func == NULL)
			{
				error_hook_strucrute = true;
				ShowErrorMessage("ValidNick", ASAN_ERROR_HOOK_STRUCTURE);
			}
			else
			{
				ValidNick_Func->jmp = 0xE9; // JMP
				ValidNick_Func->adr = CalcDisp((void*)ValidNick_Func, (void*)HOOK_ValidNickName);
				ValidNick_Func->nop = 0x90; // NOP
			}
		}
	}
	else
	{
		if (Plugin_Config.Language == 0)
			logprintf("\t[ASAN | ValidNick]:\tThis hook was disabled in ASAN_Config.ini.\t->Missing.");
		else
			logprintf("\t[ASAN | ValidNick]:\t���� ��� ��� �������� � ASAN_Config.ini.\t->����������.");
	}

	if (NickLength_Config.EnableNickLengthHOOK == 1)
	{
		// Nick Length
		char* NickLength_Min_Func_ADDR = 0;
		char* NickLength_Max_Func_ADDR = 0;
		for (char * address = (char *)MEMORY_START; address < ((char *)MEMORY_START + file_size - MAX_NICKNAME_LENGTH_ADRESSES); address++)
		{
			if (CheckMemmory(address, reinterpret_cast<char*>(NickLength_Addresses), MAX_NICKNAME_LENGTH_ADRESSES, false))
			{
				if (GetNickLengthAddresses(address, NickLength_Min_Func_ADDR, NickLength_Max_Func_ADDR) == true)
				{

#if !(defined(WIN32) || defined(_WIN32)) && !defined(_MSC_VER) // Linux min check is a bit another.
					*NickLength_Min_Func_ADDR++;
#endif
					if (Plugin_Config.Language == 0)
						logprintf("\t->>[ASAN | ValidNick - MinLength]:\tMemory address '0x%x' was found. (Value = %d)", NickLength_Min_Func_ADDR, *NickLength_Min_Func_ADDR);
					else
						logprintf("\t->>[ASAN | ValidNick - MinLength]:\t����� ������ '0x%x' ��� ������. (�������� = %d)", NickLength_Min_Func_ADDR, *NickLength_Min_Func_ADDR);

					if (Plugin_Config.Language == 0)
						logprintf("\t->>[ASAN | ValidNick - MaxLength]:\tMemory address '0x%x' was found. (Value = %d)", NickLength_Max_Func_ADDR, *NickLength_Max_Func_ADDR);
					else
						logprintf("\t->>[ASAN | ValidNick - MaxLength]:\t����� ������ '0x%x' ��� ������. (�������� = %d)", NickLength_Max_Func_ADDR, *NickLength_Max_Func_ADDR);

					if (NickLength_Config.MinNickLength != *NickLength_Min_Func_ADDR)
					{
						*NickLength_Min_Func_ADDR = NickLength_Config.MinNickLength;

#if !(defined(WIN32) || defined(_WIN32)) && !defined(_MSC_VER) // Linux min check is a bit another.
						*NickLength_Min_Func_ADDR--;
#endif
						if (Plugin_Config.Language == 0)
							logprintf("\t->>[ASAN | ValidNick - MinLength_SET]:\tValue was changed to %d from ASAN_Config.ini", *NickLength_Min_Func_ADDR);
						else
							logprintf("\t->>[ASAN | ValidNick - MinLength_SET]:\t�������� ���� �������� �� %d �� ASAN_Config.ini", *NickLength_Min_Func_ADDR);
					}

					if (NickLength_Config.MaxNickLength != *NickLength_Max_Func_ADDR)
					{
						*NickLength_Max_Func_ADDR = NickLength_Config.MaxNickLength;
						if (Plugin_Config.Language == 0)
							logprintf("\t->>[ASAN | ValidNick - MaxLength_SET]:\tValue was changed to %d from ASAN_Config.ini", *NickLength_Max_Func_ADDR);
						else
							logprintf("\t->>[ASAN | ValidNick - MaxLength_SET]:\t�������� ���� �������� �� %d �� ASAN_Config.ini", *NickLength_Max_Func_ADDR);
					}
					break;
				}
			}
		}
		if (NickLength_Min_Func_ADDR == 0)
		{
			error_find_address = true;
			ShowErrorMessage("NickLength_Min", ASAN_ERROR_FIND_ADDRESS);
		}

		if (NickLength_Max_Func_ADDR == 0)
		{
			error_find_address = true;
			ShowErrorMessage("NickLength_Max", ASAN_ERROR_FIND_ADDRESS);
		}
	}
	else
	{
		if (Plugin_Config.Language == 0)
			logprintf("\t[ASAN | NickLength]:\tThis hook was disabled in ASAN_Config.ini.\t->Missing.");
		else
			logprintf("\t[ASAN | NickLength]:\t���� ��� ��� �������� � ASAN_Config.ini.\t->����������.");
	}

	if (RepeatedNicks_Config.EnableRepeatedNicksHOOK == 1 && RepeatedNicks_Config.MaxRepeatedNicks != 0)
	{
		void *RepeatedNicks_Func_ADDR = 0;
		for (char * start_address = (char *)MEMORY_START; start_address < ((char *)MEMORY_START + file_size - MAX_REPEATED_NICKS_ADRESSES); start_address++)
		{
			if (CheckMemmory(start_address, reinterpret_cast<char*>(RepeatedNicks_Addresses), MAX_REPEATED_NICKS_ADRESSES, false))
			{
				RepeatedNicks_Func_ADDR = start_address;
			}
		}

		if (RepeatedNicks_Func_ADDR == 0)
		{
			error_find_address = true;
			ShowErrorMessage("RepeatedNicks", ASAN_ERROR_FIND_ADDRESS);
		}
		else
		{
			if (Plugin_Config.Language == 0)
				logprintf("\t[ASAN | RepeatedNicks]:\tMemory address '0x%x' was found.", RepeatedNicks_Func_ADDR);
			else
				logprintf("\t[ASAN | RepeatedNicks]:\t����� ������ '0x%x' ��� ������.", RepeatedNicks_Func_ADDR);

			JUMP_DATA* RepeatedNicks_Func = (JUMP_DATA*)RepeatedNicks_Func_ADDR;

			if (RepeatedNicks_Func == NULL)
			{
				error_hook_strucrute = true;
				ShowErrorMessage("RepeatedNicks", ASAN_ERROR_HOOK_STRUCTURE);
			}
			else
			{
				RepeatedNicks_Func->jmp = 0xE9; // JMP
				RepeatedNicks_Func->adr = CalcDisp((void*)RepeatedNicks_Func, (void*)HOOK_RepeatedNicks);
				RepeatedNicks_Func->nop = 0x90; // NOP
			}
		}
	}
	else
	{
		if (Plugin_Config.Language == 0)
			logprintf("\t[ASAN | RepeatedNicks]:\tThis hook was disabled in ASAN_Config.ini.\t->Missing.");
		else
			logprintf("\t[ASAN | RepeatedNicks]:\t���� ��� ��� �������� � ASAN_Config.ini.\t->����������.");
	}

	char * version_name = 0;
	int vname_size = strlen(SAMP_VERSION_NAME);

	for (char * address = (char *)MEMORY_START; address < ((char *)MEMORY_START + file_size - vname_size); address++)
	{
		if (CheckMemmory(address, SAMP_VERSION_NAME, vname_size))
		{
			*address = 0; // deleting ending of line..

			int start_pos = 0;

			while ((address - start_pos)[0] != 'v')
			{
				start_pos++;
			}

			version_name = address - (abs(start_pos) - 1); // 1 - symbol 'v'
			
			if (Plugin_Config.Language == 0)
				logprintf("\t[ASAN | SERVER]:\tThe number of server is - '%s'\n", version_name);
			else
				logprintf("\t[ASAN | ������]:\t������ ������� - '%s'\n", version_name);

			break;
		}
	}

	if (Plugin_Config.Language == 0)
		logprintf("\t[ASAN | LOADED]:\tPlugin v%s was started successfully.", PLUGIN_VERSION);
	else
		logprintf("\t[ASAN | ��������]:\t������ v%s ��� ������� �������.", PLUGIN_VERSION);

	if(error_find_address == true)
	{
		if (Plugin_Config.Language == 0)
			logprintf("\n\t*[ASAN | HELP | CODE - 0x%x]:\tThis code - an error in finding address in SA:MP's memory.\n\tMaybe, the number of your server is lower, then 0.3C R5\n\n", ASAN_ERROR_FIND_ADDRESS);
		else
			logprintf("\n\t*[ASAN | ������ | ��� - 0x%x]:\t������ ��� - ������ ���������� ������ � ������ SA:MP.\n\t��������, ������ ������ ������� ����, ��� 0.3C R5\n\n", ASAN_ERROR_HOOK_STRUCTURE);
	}

	if (error_hook_strucrute == true)
	{
		if (Plugin_Config.Language == 0)
			logprintf("\n\t*[ASAN | HELP | CODE - 0x%x]:\tThis code - an error initializing the hook structure!\n\tWrite into issue on GitHub, please! https://github.com/KrYpToDeN/Advanced-SA-NickName/issues \n\n", ASAN_ERROR_FIND_ADDRESS);
		else
			logprintf("\n\t*[ASAN | ������ | ��� - 0x%x]:\t������ ��� - ������ ������������� ��������� ����!\n\t�������� ��� � issue �� GitHub, ����������! https://github.com/KrYpToDeN/Advanced-SA-NickName/issues \n\n", ASAN_ERROR_HOOK_STRUCTURE);
	}

	ShowCopiratesInfo();
	return true;
}

AMX_NATIVE_INFO PluginNatives[] =
{
	{ "ASAN_HOOK_ConnectPlayer",		ASAN_HOOK_ConnectPlayer },
	{ "ASAN_HOOK_DisconnectPlayer",		ASAN_HOOK_DisconnectPlayer },
	{ "ASAN_HOOK_GetPlayerName",		ASAN_HOOK_GetPlayerName },
	{ "ASAN_IsValidNickName",			ASAN_IsValidNickName },
	{ "ASAN_GetMinNickLength",			ASAN_GetMinNickLength },
	{ "ASAN_GetMaxNickLength",			ASAN_GetMaxNickLength },
	{0, 0 }
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	return amx_Register(amx, PluginNatives, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
	return AMX_ERR_NONE;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	if (Plugin_Config.Language == 0)
		logprintf("\t[ASAN | UNLOADED]:\tPlugin v%s was unloaded successfully!", PLUGIN_VERSION);
	else
		logprintf("\t[ASAN | ��������]:\t������ v%s ��� �������� �������!", PLUGIN_VERSION);
}