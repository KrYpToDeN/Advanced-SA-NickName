#define HAVE_STDINT_H

#include "includes.h"

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

	logprintf("\n\n\t-------------Advanced SA NickName (ASAN)-------------");
	logprintf("\t[ASAN]: ������ v4.0 by [KrYpToDeN] & [EC]Zero");
	logprintf("\t[ASAN]: ������ �����������..");

	INIReader reader("scriptfiles//ASAN_Config.ini");
	if (reader.ParseError() < 0)
	{
		logprintf("\t[ASAN | SETTINGS]: ������ ���� �������� `ASAN_Config.ini` � ����� `scriptfiles`");

		FILE *SettingFile;
		SettingFile = fopen("scriptfiles//ASAN_Config.ini", "wt");

		if (!SettingFile)
		{
			logprintf("\n\t[ASAN | ERROR]: ����������� ����� `scriptfiles` ��� ����� ��� ������.\n\t->�����..");
			ShowCopiratesInfo();
			return false;
		}

		Config.EnginePlugin		= ASAN_DEFAULT_ENGINE;
		std::regex temp_regex_template(ASAN_DEFAULT_TEMPLATE, std::regex::icase);
		Config.RegexTemplate	= temp_regex_template;
		Config.AllowSpace		= ASAN_DEFAULT_SPACE;
		Config.MaxSpaces		= ASAN_DEFAULT_MAX_SPACES;

		char ftext[608 + sizeof(ASAN_DEFAULT_TEMPLATE)];
		sprintf(ftext, "\
[ASAN_Settings]\n\n\
EnginePlugin = %d\n\
;�������� ������ - 1, ��������� ������ - 0\n\n\
RegexTemplate = %s\n\
;���������� ��������� (������� ������� ��������)\n\n\
AllowSpace = %d\n\
;�������� ������ ������� �������������(_) �� ������ �������( ) - 1, �� ��������� - 0\n\
;������. ���� 'AllowSpace = 1' -> 'John_Connor' ����� � ���� ��� 'John Connor' ����� ��������. �� ����������� ������� � ���� �����! ������ ��������� �������!\n\n\
MaxSpaces = %d\n\
;�������� ������, ���� `AllowSpace` = 1.\n\
;���������� ����� ������� (_) �� ������ (). ������ ���� ����� 1, �� ������� ������� ������ ������ 1 ���, � ��������� ���������!",
		Config.EnginePlugin, ASAN_DEFAULT_TEMPLATE, Config.AllowSpace, Config.MaxSpaces);

		fwrite(ftext, 1, strlen(ftext), SettingFile);
		
		fclose(SettingFile);
	}
	else
	{
		char RegexText[512];
		Config.EnginePlugin	= reader.GetBoolean("ASAN_Settings", "EnginePlugin", ASAN_DEFAULT_ENGINE);
		sprintf(RegexText, reader.Get("ASAN_Settings", "RegexTemplate", ASAN_DEFAULT_TEMPLATE).c_str());
		Config.AllowSpace = reader.GetBoolean("ASAN_Settings", "AllowSpace", ASAN_DEFAULT_SPACE);
		Config.MaxSpaces = reader.GetInteger("ASAN_Settings", "MaxSpaces", ASAN_DEFAULT_MAX_SPACES);

		std::regex temp_regex_template(RegexText);
		Config.RegexTemplate = temp_regex_template;
	}

	int file_size = GetFileSize();

	if (!Unlock((void*)MEMORY_START, file_size))
	{
		logprintf("\n\t[ASAN | ERROR]: �� ���� ��������� ������ SA:MP.\n\t�������� ������ � ussue, ����������!\n\t->�����..");
		ShowCopiratesInfo();
		return false;
	}

	void * function_adress = 0;

	for (char * address = (char *)MEMORY_START; address < ((char *)MEMORY_START + file_size - MAX_ADRESSES); address++)
	{
		if (CheckMemmory(address, reinterpret_cast<char*>(SAMP_Addresses), MAX_ADRESSES))
		{
			function_adress = address;
			logprintf("\t[ASAN]: ����� ������ '0x%x' ������.", function_adress);
			break;
		}
	}

	if (function_adress == 0)
	{
		logprintf("\n\t[ASAN | ERROR]: �� ���� ����� ����� ������ SA:MP.\n\t��������, ������ ������ ������� ����, ��� 0.3a\n\t���� ��� �� ���, �� �������� ������ � ussue, ����������!\n\t->�����..");
		ShowCopiratesInfo();
		return false;
	}

	char * version_name = 0;
	int vname_size = strlen(samp_version_name);

	for (char * address = (char *)MEMORY_START; address < ((char *)MEMORY_START + file_size - vname_size); address++)
	{
		if (CheckMemmory(address, samp_version_name, vname_size))
		{
			*address = 0; // �������� �������� ��������

			int start_pos = 0;

			while ((address - start_pos)[0] != 'v')
			{
				start_pos++;
			}

			version_name = address - (abs(start_pos) - 1); // 1 - ������ v

			logprintf("\t[ASAN]: ������ ������� - '%s'", version_name);
			break;
		}
	}

	if (!Config.EnginePlugin)
	{
		logprintf("\n\t[ASAN | DISABLED]: ������ ��� ��������. ��������� ��������� ����� `ASAN_Config.ini` � ����� `scriptfiles`!\n\t->�����..");
		ShowCopiratesInfo();
		return false;
	}

	JUMP_DATA* checkFunct = (JUMP_DATA*)function_adress;

	if (checkFunct != NULL)
	{
		checkFunct->jmp = 0xE9; // JMP
		checkFunct->adr = CalcDisp((void*)checkFunct, (void*)checkNickname); // funct address
		checkFunct->nop = 0x90; // NOP

		logprintf("\t[ASAN | SUCCESS]: ������ ������� �������.");

		ShowCopiratesInfo();
	}
	return true;
}

cell AMX_NATIVE_CALL hook_GetName(AMX *amx, cell *params)
{
	cell *destination = NULL;
	amx_GetAddr(amx, params[1], &destination);

	int len = 0;
	
	while (destination[len])
	{
		ChangeSymbols(destination[len]);
		len++;
	}
	return 1;
}

cell AMX_NATIVE_CALL CheckValidNickName(AMX *amx, cell *params)
{
	char* name = NULL;
	amx_StrParam(amx, params[1], name);
	if (name != NULL)
	{
		int len = strlen(name);
		if (!std::regex_match(name, Config.RegexTemplate) || len < 3 || len > 20)
			return false;
	}
	return true;
}

AMX_NATIVE_INFO PluginNatives[] =
{
	{ "ASAN_GetPlayerName", hook_GetName },
	{ "IsValidNickName", CheckValidNickName },
	{ 0, 0 }
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
	logprintf("\t[ASAN]: ������ v4.0 ������� ��������!");
}