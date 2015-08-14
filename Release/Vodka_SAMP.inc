/*
    Инклуд  для плагина 'Vodka_SAMP' v2.0!
    Инклуд, позволящий устранить баг с длиной ника.
		1)Поместитите даннный файл в папку 'pawno/include'
		2)Обязательно во всех своих скриптах и модах после '#include <a_samp>'
			пропишите '#include <Vodka_SAMP>'
    Создатель: [KrYpToDeN]
    Скайп: kryptoden
*/

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
#define GetPlayerName _GetPlayerName

/*
    Инклуд  для плагина 'Vodka_SAMP' v2.0!
    Инклуд, позволящий устранить баг с длиной ника.
		1)Поместитите даннный файл в папку 'pawno/include'
		2)Обязательно во всех своих скриптах и модах после '#include <a_samp>'
			пропишите '#include <Vodka_SAMP>'
    Создатель: [KrYpToDeN]
    Скайп: kryptoden
*/
