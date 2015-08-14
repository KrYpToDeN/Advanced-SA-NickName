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
	logprintf("\t[VODKA_SA:MP]: Плагин v2.0 by [KrYpToDeN] & [EC]Zero");
	logprintf("\t[VODKA_SA:MP]: Плагин поддержки русских никнеймов загружается..");

	int file_size = GetFileSize();

	if (!Unlock((void*)MEMORY_START, file_size))
	{
		logprintf("\n\tОШИБКА: Ошибка инициализации.\n\tОбратитесь в скайп kryptoden\n\n\tСворачиваемся..");
		logprintf("\t---------------------------------------------------------------\n\n");
		return false;
	}

	void * function_adress = 0;

#if (defined(WIN32) || defined(_WIN32)) && defined(_MSC_VER) // windows
	for (char * adress = (char *)MEMORY_START; adress < ((char *)MEMORY_START + file_size - 90); adress++)
	{
		if (CheckMemmory(adress, Adresses, 90))
		{
			function_adress = adress;
			logprintf("\t[VODKA_SA:MP]: Адрес '0x%x' найден.", function_adress);
			break;
		}
	}
#else // Linux
	for (char * adress = (char *)MEMORY_START; adress < ((char *)MEMORY_START + file_size - 117); adress++)
	{
		if (CheckMemmory(adress, Adresses, 117))
		{
			function_adress = adress;
			logprintf("\t[VODKA_SA:MP]: Адрес '0x%x' найден.", function_adress);
			break;
		}
	}
#endif	

	if (function_adress == 0)
	{
		logprintf("\n\tОШИБКА: Какая-то непредвиденная ошибка.\n\tВидимо вы запустили плагин на версии ниже 0.3a\n\tОбратитесь в скайп kryptoden\n\n\tСворачиваемся..");
		logprintf("\t---------------------------------------------------------------\n\n");
		return false;
	}

	JUMP_DATA* checkFunct = (JUMP_DATA*)function_adress;

	if (checkFunct != NULL)
	{
		checkFunct->jmp = 0xE9; // JMP
		checkFunct->adr = CalcDisp((void*)checkFunct, (void*)checkNickname); // funct address
		checkFunct->nop = 0x90; // NOP

		logprintf("\t[VODKA_SA:MP]: Плагин успешно запущен.");

#if (defined(WIN32) || defined(_WIN32)) && defined(_MSC_VER) // windows

		char * version_name = 0;

		for (char * adress = (char *)MEMORY_START; adress < ((char *)MEMORY_START + file_size - 14); adress++)
		{
			if (CheckMemmory(adress, samp_version_name, 14))
			{
				version_name = adress - 12;
				logprintf("\t[VODKA_SA:MP]: Версия сервера -  %s", version_name);
				break;
			}
		}
#endif
	}

	logprintf("\t[VODKA_SA:MP]: Ваши собутильники:[EC]Zero & [KrYpToDeN]!");
	logprintf("\t\t[EC]Zero\t\t| Skype: mactep_3epo");
	logprintf("\t\t[KrYpToDeN]\t\t| Skype: kryptoden");
	logprintf("\t[VODKA_SA:MP]: Приятного распития!");
	logprintf("\t---------------------------------------------------------------\n\n");
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
	logprintf("\t[VODKA_SA:MP]: Плагин v2.0 выгружен успешно!");
}