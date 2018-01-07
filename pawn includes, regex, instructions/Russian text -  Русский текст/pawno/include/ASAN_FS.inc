// Russian Version - Русская версия

/*
	Данный плагин поддерживается 2мя инклудами.
		1) ASAN.inc - основной инклуд для использования в GameMode.
			Не используйте его в Ваших FilterScripts!!!
		2) ASAN_FS.inc - дополнительный инклуд, содержащий в себе дополнительные функции, для использования Ваших FilterScripts.
			Не используйте его в Вашем GameMode!!!
*/

/*
	Дополниельный инклуд v1.0 для плагина 'Advanced-SA-NickName' v5.0!
	Требуется установка инклуда во все Ваши FilterScripts для корректной работы плагина!
	Не используйте его в Вашем GameMode!!!
	
	Для установки инклуда и корректной работы плагина:	
		1) Поместите данный файл в папку 'pawno/include';
		2) Во всех Ваших FilterScripts после строки
				#include <a_samp>
			обязательно пропишите данный инклуд
				#include "ASAN_FS"
				
	В инклуде присутствуют следующие хуки/natives для корректной работы плагина. НЕ ИЗМЕНЯЙТЕ ИХ СОДЕРЖИМОЕ.
		1) native ASAN_HOOK_GetPlayerName(name[]);
		2) stock ASAN_INCLUDE_GetPlayerName(playerid, name[], length);
		3) stock ASAN_INCLUDE_SetPlayerName(playerid, name[]);
		
	Инклуд добавляет NATIVEs для использования в Pawn (в Вашем моде):
		1) native ASAN_IsValidNickName(name[])
			- Проверяет валидность введенного никнейма, исходя из настроек в Вашем 'ASAN_Config.ini';
			- Возвращает 'true;' в случае коррекности введенного ника;
			- Возвращает 'false;' в случае не коррекности введенного ника;
			
		2) native ASAN_GetMinNickLength()
			- Возвращяет минимальную длину никнейма, исходя из настроек в Вашем 'ASAN_Config.ini';
			
		3) native ASAN_GetMaxNickLength()
			- Возвращяет максимальную длину никнейма, исходя из настроек в Вашем 'ASAN_Config.ini';
		
	Создатель:
		[KrYpToDeN]
	Благодарности:
		Большое спасибо [EC]Zero за помощь с нахождением адресов памяти и реализации автоматического нахождения адресов для плагина версии 1.0!
		Большое спасибо Enrique_Heimonen за помощь в тестировании!
		Большое спасибо ZiGGi за помощь в нахождении адреса памяти для повторных никнеймов!
	Официальные ссылки для обсуждения плагина
		Порталы на русском языке:
			http://lightcode.ru/showthread.php?t=113118
			http://pawno.su/showthread.php?t=114245
			http://forum.sa-mp.com/showthread.php?t=617993
		Порталы на английском языке:	
			http://forum.sa-mp.com/showthread.php?t=647528
	Актуальную версия плагина, инклуда, а также англоязычную версию Вы можете найти на официальной странице плагина:
		https://github.com/KrYpToDeN/Advanced-SA-NickName
		
	Свои предложения по дальнейшему развитию плагина, обнаружении каких-либо багов, сбоев Вы можете написать в Issue на GitHub:
		https://github.com/KrYpToDeN/Advanced-SA-NickName/issues
*/

#if !defined _samp_included
	#error Include 'ASAN_FS.inc' should be loaded after 'a_samp.inc'!
#endif

#if !defined _string_included
	#error Include 'ASAN_FS.inc' should be loaded after 'string.inc'!
#endif

#if defined _ASAN_FS_included
	#endinput
#endif

#define _ASAN_FS_included
#pragma library ASAN

#define INCLUDE_ASAN_MAX_PLAYER_NAME 0x18

// HOOKS. Только для плагина. Не используйте их в своем Pawn коде.
native ASAN_HOOK_GetPlayerName(name[]);

// Дополниельные функции для Вашего Pawn кода.
native ASAN_IsValidNickName(name[]);
native ASAN_GetMinNickLength();
native ASAN_GetMaxNickLength();

stock ASAN_INCLUDE_GetPlayerName(playerid, name[], length)
{
    new return_value = GetPlayerName(playerid, name, length);
    ASAN_HOOK_GetPlayerName(name);
	return return_value;
}

#if defined _ALS_GetPlayerName
    #undef GetPlayerName
#else
    #define _ALS_GetPlayerName
#endif
#define GetPlayerName ASAN_INCLUDE_GetPlayerName

stock ASAN_INCLUDE_SetPlayerName(playerid, name[])
{
	new PlayerName[INCLUDE_ASAN_MAX_PLAYER_NAME + 1];
	GetPlayerName(playerid, PlayerName, sizeof(PlayerName));
	new name_length = strlen(name);
	if(strcmp(PlayerName, name, true, ASAN_GetMaxNickLength()) == 0)
	{
		return 0;
	}
		
	if(!ASAN_IsValidNickName(name) ||  name_length < ASAN_GetMinNickLength() || name_length > ASAN_GetMaxNickLength())
	{
		return -1;
	}	
	return SetPlayerName(playerid, name);
}

#if defined _ALS_SetPlayerName
    #undef SetPlayerName
#else
    #define _ALS_SetPlayerName
#endif
#define SetPlayerName ASAN_INCLUDE_SetPlayerName

// Russian Version - Русская версия

/*
	Данный плагин поддерживается 2мя инклудами.
		1) ASAN.inc - основной инклуд для использования в GameMode.
			Не используйте его в Ваших FilterScripts!!!
		2) ASAN_FS.inc - дополнительный инклуд, содержащий в себе дополнительные функции, для использования Ваших FilterScripts.
			Не используйте его в Вашем GameMode!!!
*/

/*
	Дополниельный инклуд v1.0 для плагина 'Advanced-SA-NickName' v5.0!
	Требуется установка инклуда во все Ваши FilterScripts для корректной работы плагина!
	Не используйте его в Вашем GameMode!!!
	
	Для установки инклуда и корректной работы плагина:	
		1) Поместите данный файл в папку 'pawno/include';
		2) Во всех Ваших FilterScripts после строки
				#include <a_samp>
			обязательно пропишите данный инклуд
				#include "ASAN_FS"
				
	В инклуде присутствуют следующие хуки/natives для корректной работы плагина. НЕ ИЗМЕНЯЙТЕ ИХ СОДЕРЖИМОЕ.
		1) native ASAN_HOOK_GetPlayerName(name[]);
		2) stock ASAN_INCLUDE_GetPlayerName(playerid, name[], length);
		3) stock ASAN_INCLUDE_SetPlayerName(playerid, name[]);
		
	Инклуд добавляет NATIVEs для использования в Pawn (в Вашем моде):
		1) native ASAN_IsValidNickName(name[])
			- Проверяет валидность введенного никнейма, исходя из настроек в Вашем 'ASAN_Config.ini';
			- Возвращает 'true;' в случае коррекности введенного ника;
			- Возвращает 'false;' в случае не коррекности введенного ника;
			
		2) native ASAN_GetMinNickLength()
			- Возвращяет минимальную длину никнейма, исходя из настроек в Вашем 'ASAN_Config.ini';
			
		3) native ASAN_GetMaxNickLength()
			- Возвращяет максимальную длину никнейма, исходя из настроек в Вашем 'ASAN_Config.ini';
		
	Создатель:
		[KrYpToDeN]
	Благодарности:
		Большое спасибо [EC]Zero за помощь с нахождением адресов памяти и реализации автоматического нахождения адресов для плагина версии 1.0!
		Большое спасибо Enrique_Heimonen за помощь в тестировании!
		Большое спасибо ZiGGi за помощь в нахождении адреса памяти для повторных никнеймов!
	Официальные ссылки для обсуждения плагина
		Порталы на русском языке:
			http://lightcode.ru/showthread.php?t=113118
			http://pawno.su/showthread.php?t=114245
			http://forum.sa-mp.com/showthread.php?t=617993
		Порталы на английском языке:	
			http://forum.sa-mp.com/showthread.php?t=647528
	Актуальную версия плагина, инклуда, а также англоязычную версию Вы можете найти на официальной странице плагина:
		https://github.com/KrYpToDeN/Advanced-SA-NickName
		
	Свои предложения по дальнейшему развитию плагина, обнаружении каких-либо багов, сбоев Вы можете написать в Issue на GitHub:
		https://github.com/KrYpToDeN/Advanced-SA-NickName/issues
*/