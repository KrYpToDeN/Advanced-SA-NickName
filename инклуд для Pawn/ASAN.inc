/*
    Инклуд v3.0 для плагина 'Advanced-SA-NickName' v4.0!
    Инклуд, позволящий устранить баг с длиной ника.
		1)Поместитите даннный файл в папку 'pawno/include'
		2)Обязательно во всех своих скриптах и модах сразу после '#include <a_samp>'
			пропишите '#include <ASAN>'
		3)Для проверки ника на валидность, используйте функцию IsValidNickName(name[])
			Возвращает: true - ник валиден, false - в нике запрещённые символы.
    Создатель: [KrYpToDeN]
*/

#if !defined _samp_included
	#error Include 'ASAN.inc' should be loaded after 'a_samp.inc'!
#endif

#if !defined _string_included
	#error Include 'ASAN.inc' should be loaded after 'string.inc'!
#endif

#if defined _ASAN_included
	#endinput
#endif

#define _ASAN_included
#pragma library ASAN

native ASAN_GetPlayerName(name[]);
native IsValidNickName(name[]);

stock _GetPlayerName(playerid, name[], length)
{
    new return_value = GetPlayerName(playerid, name, length);
    ASAN_GetPlayerName(name);
	return return_value;
}

#if defined _ALS_GetPlayerName
    #undef GetPlayerName
#else
    #define _ALS_GetPlayerName
#endif
#define GetPlayerName _GetPlayerName

/*
    Инклуд v3.0 для плагина 'Advanced-SA-NickName' v4.0!
    Инклуд, позволящий устранить баг с длиной ника.
		1)Поместитите даннный файл в папку 'pawno/include'
		2)Обязательно во всех своих скриптах и модах сразу после '#include <a_samp>'
			пропишите '#include <ASAN>'
		3)Для проверки ника на валидность, используйте функцию IsValidNickName(name[])
			Возвращает: true - ник валиден, false - в нике запрещённые символы.
    Создатель: [KrYpToDeN]
*/