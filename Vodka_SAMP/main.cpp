#include "includes.h"

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

	logprintf("\n\n\t---------------------------------------------------------------");
	logprintf("\t[VODKA_SA:MP]: ������ v2.5 by [KrYpToDeN] & [EC]Zero");
	logprintf("\t[VODKA_SA:MP]: ������ ��������� ������� ��������� �����������..");

	if (ini_parse("scriptfiles//Vodka_SAMP.ini", Ini_Handler, &Config) < 0) 
	{
		logprintf("\n\t[VODKA_SA:MP]: ���� �������� ����������� | ������ �� ������ \"scriptfiles//Vodka_SAMP.ini\"\n");
		FILE *SettingFile;
		SettingFile = fopen("scriptfiles//Vodka_SAMP.ini", "wt");

		if (!SettingFile)
		{
			logprintf("\n\t��������� �������������� ������ �������� ����� ��������. ��������, ����������� ������� \"scriptfiles\".\n\n\t�������������..");
			ShowCopiratesInfo();
			return false;
		}

		Config.EnginePlugin = 1;
		Config.MixSymbols = 1;

		fwrite("[Vodka_SAMP_Settings]\nEnginePlugin = 1\t\t;���.������ - 1, ����.������ - 0\nAllowMixSymbols = 1\t\t;���.���������� ������ - 1, ����.���������� ������ - 0", 1, strlen("[Vodka_SAMP_Settings]\nEnginePlugin = 1\t\t;���.������ - 1, ����.������ - 0\nAllowMixSymbols = 1\t\t;���.���������� ������ - 1, ����.���������� ������ - 0"), SettingFile);
		fclose(SettingFile);
	}

	int file_size = GetFileSize();

	if (!Unlock((void*)MEMORY_START, file_size))
	{
		logprintf("\n\t������: ������ �������������.\n\t���������� � ����� kryptoden\n\n\t�������������..");
		ShowCopiratesInfo();
		return false;
	}

	void * function_adress = 0;

#if (defined(WIN32) || defined(_WIN32)) && defined(_MSC_VER) // windows
	for (char * adress = (char *)MEMORY_START; adress < ((char *)MEMORY_START + file_size - 90); adress++)
	{
		if (CheckMemmory(adress, Adresses, 90))
		{
			function_adress = adress;
			logprintf("\t[VODKA_SA:MP]: ����� '0x%x' ������.", function_adress);
			break;
		}
	}
#else // Linux
	for (char * adress = (char *)MEMORY_START; adress < ((char *)MEMORY_START + file_size - 117); adress++)
	{
		if (CheckMemmory(adress, Adresses, 117))
		{
			function_adress = adress;
			logprintf("\t[VODKA_SA:MP]: ����� '0x%x' ������.", function_adress);
			break;
		}
	}
#endif	

	if (function_adress == 0)
	{
		logprintf("\n\t������: �����-�� �������������� ������.\n\t������ �� ��������� ������ �� ������ ���� 0.3a\n\t���������� � ����� kryptoden\n\n\t�������������..");
		logprintf("\t---------------------------------------------------------------\n\n");
		return false;
	}


	if (!Config.EnginePlugin)
	{
		logprintf("\n\t������ ��������. ���������� ���� �������� Vodka_SAMP.ini\n\n\t�������������..");
		ShowCopiratesInfo();
		return false;
	}

	JUMP_DATA* checkFunct = (JUMP_DATA*)function_adress;

	if (checkFunct != NULL)
	{
		checkFunct->jmp = 0xE9; // JMP
		checkFunct->adr = CalcDisp((void*)checkFunct, (void*)checkNickname); // funct address
		checkFunct->nop = 0x90; // NOP

		logprintf("\t[VODKA_SA:MP]: ������ ������� �������.");

#if (defined(WIN32) || defined(_WIN32)) && defined(_MSC_VER) // windows

		char * version_name = 0;

		for (char * adress = (char *)MEMORY_START; adress < ((char *)MEMORY_START + file_size - 14); adress++)
		{
			if (CheckMemmory(adress, samp_version_name, 14))
			{
				version_name = adress - 12;
				logprintf("\t[VODKA_SA:MP]: ������ ������� -  %s", version_name);
				break;
			}
		}
#endif
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
	{ "KryptoHook_GetPlayerName", hook_GetName },
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
	logprintf("\t[VODKA_SA:MP]: ������ v2.0 �������� �������!");
}