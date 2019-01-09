// English Version - Англоязычная версия

/*
	This plugin is supported by 2 includes.
		1) ASAN.inc - the main include for useing into your GameMode.
			Don't use it into your FilterScripts!!!
		2) ASAN_FS.inc - extra include, containing extra functions, for using into your FilterScripts.
			Don't use it into your GameMode!!!
*/

/*
	Extra include v1.0 for plugin 'Advanced-SA-NickName' v5.0!
	It's necessary to install this include into all of your FilterScripts for correctly plugin work!
	Don't use it into your GameMode!!!
	
	To install include and to work plugin correctly:
		1) Input this file into folder 'pawno/include';
		2) Into all of your FilterScripts after line
				#include <a_samp>
			it's necessary to write the include
				#include "ASAN_FS"
				
	Into include there are next hooks/natives for correctly plugin work. DO NOT CHANGE THEIR CONTENTS!
		1) native ASAN_HOOK_GetPlayerName(name[]);
		2) stock ASAN_INCLUDE_GetPlayerName(playerid, name[], length);
		3) stock ASAN_INCLUDE_SetPlayerName(playerid, name[]);
		
	Include adds NATIVEs for using into Pawn (в Вашем моде):
		1) native ASAN_IsValidNickName(name[])
			- Verifies the validity of the entered nickname, based on the settings in your 'ASAN_Config.ini';
			- Returns 'true;' in case of correctness of the entered nickname;
			- Returns 'false;' in case of not correctness of the entered nickname;
			
		2) native ASAN_GetMinNickLength()
			- Returns the minimum length of the nickname, based on the settings in your 'ASAN_Config.ini';
			
		3) native ASAN_GetMaxNickLength()
			- Returns the maximum length of the nickname, based on the settings in your 'ASAN_Config.ini';
		
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

// HOOKS. Only for plugin. Don't use it in your pawn code.
native ASAN_HOOK_GetPlayerName(name[]);

// Extra functions for your Pawn code.
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

// English Version - Англоязычная версия

/*
	This plugin is supported by 2 includes.
		1) ASAN.inc - the main include for useing into your GameMode.
			Don't use it into your FilterScripts!!!
		2) ASAN_FS.inc - extra include, containing extra functions, for using into your FilterScripts.
			Don't use it into your GameMode!!!
*/

/*
	Extra include v1.0 for plugin 'Advanced-SA-NickName' v5.0!
	It's necessary to install this include into all of your FilterScripts for correctly plugin work!
	Don't use it into your GameMode!!!
	
	To install include and to work plugin correctly:
		1) Input this file into folder 'pawno/include';
		2) Into all of your FilterScripts after line
				#include <a_samp>
			it's necessary to write the include
				#include "ASAN_FS"
				
	Into include there are next hooks/natives for correctly plugin work. DO NOT CHANGE THEIR CONTENTS!
		1) native ASAN_HOOK_GetPlayerName(name[]);
		2) stock ASAN_INCLUDE_GetPlayerName(playerid, name[], length);
		3) stock ASAN_INCLUDE_SetPlayerName(playerid, name[]);
		
	Include adds NATIVEs for using into Pawn (в Вашем моде):
		1) native ASAN_IsValidNickName(name[])
			- Verifies the validity of the entered nickname, based on the settings in your 'ASAN_Config.ini';
			- Returns 'true;' in case of correctness of the entered nickname;
			- Returns 'false;' in case of not correctness of the entered nickname;
			
		2) native ASAN_GetMinNickLength()
			- Returns the minimum length of the nickname, based on the settings in your 'ASAN_Config.ini';
			
		3) native ASAN_GetMaxNickLength()
			- Returns the maximum length of the nickname, based on the settings in your 'ASAN_Config.ini';
		
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