/*
    Инклуд v2.0 для плагина 'Vodka_SAMP' v3.0!
    Инклуд, позволящий устранить баг с длиной ника.
		1)Поместитите даннный файл в папку 'pawno/include'
		2)Обязательно во всех своих скриптах и модах сразу после '#include <a_samp>'
			пропишите '#include <Vodka_SAMP>'
		3)Для проверки ника на валидность, используйте функцию IsValidNickName(name[])
			Возвращает: true - ник валиден, false - в нике запрещённые символы.
    Создатель: [KrYpToDeN]
    Скайп: kryptoden
*/

#if !defined _samp_included
	#error Include 'Vodka_SAMP.inc' should be loaded after 'a_samp.inc'!
#endif

#if !defined _string_included
	#error Include 'Vodka_SAMP.inc' should be loaded after 'string.inc'!
#endif

#if defined _VodkaSAMP_included
	#endinput
#endif

#define _VodkaSAMP_included
#pragma library VodkaSAMP

native KryptoHook_GetPlayerName(name[]);

stock _GetPlayerName(playerid, name[], length)
{
    GetPlayerName(playerid, name, length);
    KryptoHook_GetPlayerName(name);
}

stock IsValidNickName(name[])
{
	new len = strlen(name);
	for(new i = 0; i < len; i++)
	{
		switch(name[i])
		{
		    case 0x30..0x39, 0x61..0x7A, 0x41..0x5A, 0x5B, 0x5D, 0x28, 0x29, 0x24, 0x40, 0x2E, 0x5F, 0x3D, 0xC0..0xDF, 0xE0..0xFF, 0xA8, 0xB8: continue;
		    default: return false;
		}
	}
	return true;
}

#if defined _ALS_GetPlayerName
    #undef GetPlayerName
#else
    #define _ALS_GetPlayerName
#endif
#define GetPlayerName _GetPlayerName

/*
    Инклуд v2.0 для плагина 'Vodka_SAMP' v3.0!
    Инклуд, позволящий устранить баг с длиной ника.
		1)Поместитите даннный файл в папку 'pawno/include'
		2)Обязательно во всех своих скриптах и модах сразу после '#include <a_samp>'
			пропишите '#include <Vodka_SAMP>'
		3)Для проверки ника на валидность, используйте функцию IsValidNickName(name[])
			Возвращает: true - ник валиден, false - в нике запрещённые символы.
    Создатель: [KrYpToDeN]
    Скайп: kryptoden
*/