// English Version - Англоязычная версия

/*
	This plugin is supported by 2 includes.
		1) ASAN.inc - the main include for useing into your GameMode.
			Don't use it into your FilterScripts!!!
		2) ASAN_FS.inc - extra include, containing extra functions, for using into your FilterScripts.
			Don't use it into your GameMode!!!
*/

/*		
	Main include v4.0 for plugin 'Advanced-SA-NickName' v5.0!
	It's necessary to install this include into your GameMode for correctly plugin work!
	Don't use it into your FilterScripts!!!
	
	Для установки инклуда и корректной работы плагина:	
		1) Input this file into folder 'pawno/include';
		2) Into your GameMode after line
				#include <a_samp>
			it's necessary to write the include
				#include "ASAN"
		
	Into include there are next hooks/natives for correctly plugin work. DO NOT CHANGE THEIR CONTENTS!
		1) native ASAN_HOOK_ConnectPlayer(playerid, name[]);
		2) native ASAN_HOOK_DisconnectPlayer(playerid, reason);
		3) public OnPlayerConnect(playerid);
		4) public OnPlayerDisconnect(playerid, reason);
				
	Credits:
		[KrYpToDeN]
	Thanks:
		Many thanks to [EC]Zero for help with finding memory addresses and implementing automatic address finding for the plugin version 1.0!
		Many thanks to Enrique_Heimonen for help in testing!
		Many thanks to ZiGGi for help in finding the memory address for repeated nicknames!	
	Official links to discuss the plugin
		Portals in Russian:
			http://lightcode.ru/showthread.php?t=113118
			http://pawno.su/showthread.php?t=114245
			http://forum.sa-mp.com/showthread.php?t=617993
		Portals in English:	
			http://forum.sa-mp.com/showthread.php?t=647528
	The current version of the plugin, incude, and also the Russian version you can find on the official page of the plugin:
		https://github.com/KrYpToDeN/Advanced-SA-NickName
		
	Your suggestions for further development of the plugin, detection of any bugs, crashes you can write in Issue on GitHub:	
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

// Extra include with extra functions.
#include "ASAN_FS"

// HOOKS. Only for plugin. Don't use it in your pawn code.
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

// English Version - Англоязычная версия

/*
	This plugin is supported by 2 includes.
		1) ASAN.inc - the main include for useing into your GameMode.
			Don't use it into your FilterScripts!!!
		2) ASAN_FS.inc - extra include, containing extra functions, for using into your FilterScripts.
			Don't use it into your GameMode!!!
*/

/*		
	Main include v4.0 for plugin 'Advanced-SA-NickName' v5.0!
	It's necessary to install this include into your GameMode for correctly plugin work!
	Don't use it into your FilterScripts!!!
	
	Для установки инклуда и корректной работы плагина:	
		1) Input this file into folder 'pawno/include';
		2) Into your GameMode after line
				#include <a_samp>
			it's necessary to write the include
				#include "ASAN"
		
	Into include there are next hooks/natives for correctly plugin work. DO NOT CHANGE THEIR CONTENTS!
		1) native ASAN_HOOK_ConnectPlayer(playerid, name[]);
		2) native ASAN_HOOK_DisconnectPlayer(playerid, reason);
		3) public OnPlayerConnect(playerid);
		4) public OnPlayerDisconnect(playerid, reason);
				
	Credits:
		[KrYpToDeN]
	Thanks:
		Many thanks to [EC]Zero for help with finding memory addresses and implementing automatic address finding for the plugin version 1.0!
		Many thanks to Enrique_Heimonen for help in testing!
		Many thanks to ZiGGi for help in finding the memory address for repeated nicknames!	
	Official links to discuss the plugin
		Portals in Russian:
			http://lightcode.ru/showthread.php?t=113118
			http://pawno.su/showthread.php?t=114245
			http://forum.sa-mp.com/showthread.php?t=617993
		Portals in English:	
			http://forum.sa-mp.com/showthread.php?t=647528
	The current version of the plugin, incude, and also the Russian version you can find on the official page of the plugin:
		https://github.com/KrYpToDeN/Advanced-SA-NickName
		
	Your suggestions for further development of the plugin, detection of any bugs, crashes you can write in Issue on GitHub:	
		https://github.com/KrYpToDeN/Advanced-SA-NickName/issues
*/