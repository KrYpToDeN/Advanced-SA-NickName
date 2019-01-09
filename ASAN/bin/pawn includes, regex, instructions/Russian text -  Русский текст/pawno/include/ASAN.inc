// Russian Version - Русская версия

/*
	Данный плагин поддерживается 2мя инклудами.
		1) ASAN.inc - основной инклуд для использования в GameMode.
			Не используйте его в Ваших FilterScripts!!!
		2) ASAN_FS.inc - дополнительный инклуд, содержащий в себе дополнительные функции, для использования Ваших FilterScripts.
			Не используйте его в Вашем GameMode!!!
*/

/*		
	Основной инклуд v4.0 для плагина 'Advanced-SA-NickName' v5.0!
	Требуется обязательная установка инклуда в GameMode для корректной работы плагина!
	Не используйте его в Ваших FilterScripts!!!
	
	Для установки инклуда и корректной работы плагина:	
		1) Поместите данный файл в папку 'pawno/include';
		2) В Вашем GameMode после строки
				#include <a_samp>
			обязательно пропишите данный инклуд
				#include "ASAN"
		
	В инклуде присутствуют следующие хуки/natives для корректной работы плагина. НЕ ИЗМЕНЯЙТЕ ИХ СОДЕРЖИМОЕ.
		1) native ASAN_HOOK_ConnectPlayer(playerid, name[]);
		2) native ASAN_HOOK_DisconnectPlayer(playerid, reason);
		3) public OnPlayerConnect(playerid);
		4) public OnPlayerDisconnect(playerid, reason);
				
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
	#error Include 'ASAN.inc' should be loaded after 'a_samp.inc'!
#endif

#if !defined _string_included
	#error Include 'ASAN.inc' should be loaded after 'string.inc'!
#endif

#if defined _ASAN_FS_included
	#error Include 'ASAN.inc' should be loaded before 'ASAN_FS.inc'!
#endif

#if defined _ASAN_included
	#endinput
#endif

#define _ASAN_included
#pragma library ASAN

// Дополнительный инклуд с дополнительными функциями.
#include "ASAN_FS"

// HOOKS. Только для плагина. Не используйте их в своем Pawn коде.
native ASAN_HOOK_ConnectPlayer(playerid, name[]);
native ASAN_HOOK_DisconnectPlayer(playerid, reason);

public OnPlayerConnect(playerid)
{
	new name[INCLUDE_ASAN_MAX_PLAYER_NAME + 1];
	GetPlayerName(playerid, name, sizeof(name));
	ASAN_HOOK_ConnectPlayer(playerid, name);
	
	if(funcidx("TEST_OnPlayerConnect") != -1)
	{
		return CallLocalFunction("TEST_OnPlayerConnect", "d", playerid);
	}
	return 1;
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect TEST_OnPlayerConnect

forward TEST_OnPlayerConnect(playerid);


public OnPlayerDisconnect(playerid, reason)
{
	ASAN_HOOK_DisconnectPlayer(playerid, reason);
	
	if(funcidx("TEST_OnPlayerDisconnect") != -1)
	{
		return CallLocalFunction("TEST_OnPlayerDisconnect", "dd", playerid, reason);
	}
	return 1;
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect TEST_OnPlayerDisconnect

forward TEST_OnPlayerDisconnect(playerid, reason);

// Russian Version - Русская версия

/*
	Данный плагин поддерживается 2мя инклудами.
		1) ASAN.inc - основной инклуд для использования в GameMode.
			Не используйте его в Ваших FilterScripts!!!
		2) ASAN_FS.inc - дополнительный инклуд, содержащий в себе дополнительные функции, для использования Ваших FilterScripts.
			Не используйте его в Вашем GameMode!!!
*/

/*		
	Основной инклуд v4.0 для плагина 'Advanced-SA-NickName' v5.0!
	Требуется обязательная установка инклуда в GameMode для корректной работы плагина!
	Не используйте его в Ваших FilterScripts!!!
	
	Для установки инклуда и корректной работы плагина:	
		1) Поместите данный файл в папку 'pawno/include';
		2) В Вашем GameMode после строки
				#include <a_samp>
			обязательно пропишите данный инклуд
				#include "ASAN"
		
	В инклуде присутствуют следующие хуки/natives для корректной работы плагина. НЕ ИЗМЕНЯЙТЕ ИХ СОДЕРЖИМОЕ.
		1) native ASAN_HOOK_ConnectPlayer(playerid, name[]);
		2) native ASAN_HOOK_DisconnectPlayer(playerid, reason);
		3) public OnPlayerConnect(playerid);
		4) public OnPlayerDisconnect(playerid, reason);
				
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