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
	logprintf("\t[ASAN]: Plugin v4.0 by [KrYpToDeN] & [EC]Zero");
	logprintf("\t[ASAN]: Plugin loading..");

	INIReader reader("scriptfiles//ASAN_Config.ini");
	if (reader.ParseError() < 0)
	{
		logprintf("\t[ASAN | SETTINGS]: Creating settings file `ASAN_Config.ini` in `scriptfiles` folder\n");

		FILE *SettingFile;
		SettingFile = fopen("scriptfiles//ASAN_Config.ini", "wt");

		if (!SettingFile)
		{
			logprintf("\n\t[ASAN | ERROR]: You don't have folder `scriptfiles` or rights to write.\n\n\tAborting..");
			ShowCopiratesInfo();
			return false;
		}

		Config.EnginePlugin		= ASAN_DEFAULT_ENGINE;
		std::regex temp_regex_template(ASAN_DEFAULT_TEMPLATE, std::regex::icase);
		Config.RegexTemplate	= temp_regex_template;
		Config.RegexCase		= ASAN_DEFAULT_REGCASE;
		Config.AllowSpace		= ASAN_DEFAULT_SPACE;


		char ftext[600];
		sprintf(ftext, "\
[ASAN_Settings]\n\
EnginePlugin = %d\t\t;Enable plugin - 1, Disable plugin - 0\n\
RegexTemplate = %s\t\t;Regular expression (WITHOUT regard to case)\n\
RegexCase = %d\t\t;Case sensitivity - 1, Case insensitive - 0\n\
AllowSpace = %d\t\t;Replace symbol(_) to symbol( ) - 1, Default - 0\n\
;Example if 'AllowSpace = 1' -> 'John_Connor' will be 'John Connor' after connect. DON'T WORK ON SA:MP MAIN WINDOW (ONLY SERVER SIDE).",
		Config.EnginePlugin, ASAN_DEFAULT_TEMPLATE, Config.RegexCase, Config.AllowSpace);


		fwrite(ftext, 1, strlen(ftext), SettingFile);
		
		fclose(SettingFile);
	}
	else
	{
		char RegexText[256];
		Config.EnginePlugin	= reader.GetBoolean("ASAN_Settings", "EnginePlugin", true);
		sprintf(RegexText, reader.Get("ASAN_Settings", "RegexTemplate", ASAN_DEFAULT_TEMPLATE).c_str());
		Config.RegexCase	= reader.GetBoolean("ASAN_Settings", "RegexCase", true);
		Config.AllowSpace = reader.GetBoolean("ASAN_Settings", "AllowSpace", true);

		if (Config.RegexCase)
		{
			std::regex temp_regex_template(RegexText, std::regex::icase);
			Config.RegexTemplate = temp_regex_template;
		}
		else
		{
			std::regex temp_regex_template(RegexText);
			Config.RegexTemplate = temp_regex_template;
		}
	}

	int file_size = GetFileSize();

	if (!Unlock((void*)MEMORY_START, file_size))
	{
		logprintf("\n\t[ASAN | ERROR]: Can't read SA:MP memmory.\n\tWrite me into ussue, please!\n\n\tAborting..");
		ShowCopiratesInfo();
		return false;
	}

	void * function_adress = 0;

	for (char * address = (char *)MEMORY_START; address < ((char *)MEMORY_START + file_size - MAX_ADRESSES); address++)
	{
		if (CheckMemmory(address, reinterpret_cast<char*>(SAMP_Addresses), MAX_ADRESSES))
		{
			function_adress = address;
			logprintf("\t[ASAN]: Memmory address '0x%x' was found.", function_adress);
			break;
		}
	}

	if (function_adress == 0)
	{
		logprintf("\n\t[ASAN | ERROR]: Can't find memmory address.\n\tMaybe, you your server has version less than 0.3a\n\tWrite me into ussue, please!\n\n\tAborting..");
		ShowCopiratesInfo();
		return false;
	}

	char * version_name = 0;
	int vname_size = strlen(samp_version_name);

	for (char * address = (char *)MEMORY_START; address < ((char *)MEMORY_START + file_size - vname_size); address++)
	{
		if (CheckMemmory(address, samp_version_name, vname_size))
		{
			*address = 0; // destroy unnecessary ending

			int start_pos = 0;

			while ((address - start_pos)[0] != 'v')
			{
				start_pos++;
			}

			version_name = address - (abs(start_pos) - 1); // 1 - symbol v

			logprintf("\t[ASAN]: Server version is - `%s`", version_name);
			break;
		}
	}

	if (!Config.EnginePlugin)
	{
		logprintf("\n\t[ASAN | DISABLED]: Plugin was disabled. Check settings file `ASAN_Config.ini` in `scriptfiles` folder!\n\n\tAborting..");
		ShowCopiratesInfo();
		return false;
	}

	JUMP_DATA* checkFunct = (JUMP_DATA*)function_adress;

	if (checkFunct != NULL)
	{
		checkFunct->jmp = 0xE9; // JMP
		checkFunct->adr = CalcDisp((void*)checkFunct, (void*)checkNickname); // funct address
		checkFunct->nop = 0x90; // NOP

		logprintf("\t[ASAN | SUCCESS]: Plugin was successfully started.");

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

AMX_NATIVE_INFO PluginNatives[] =
{
	{ "ASAN_GetPlayerName", hook_GetName },
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
	logprintf("\t[ASAN]: Plugin v4.0 was successfully unloaded!");
}