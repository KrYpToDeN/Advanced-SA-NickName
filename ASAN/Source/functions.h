#pragma once

#include "headers.h"

size_t CalcDisp(void* lpFirst, void* lpSecond);
bool UnblockMemory(void *address, int len);
int GetPlayerNameINT_Length(int name[]);

bool IsNonCaseSymbolsMatch(int player_name[], char *connected_name);
bool IsCaseSymbolsMatch(int player_name[], char *connected_name);
bool IsAllowdedToReplaceUnderscoreSymbols();
bool IsValidReplaceSpacesRules(char name[]); // Cheking first and last symbols in NickName. It can't = space!
int HOOK_ValidNickName(char *name); // Thanks to [EC]Zero for helping with this hook
bool IsMaxRepeatedNicksError(char *name);
bool IsIgnoreRepeatedNicksCaseError(char *name);

#if (defined(WIN32) || defined(_WIN32)) && defined(_MSC_VER)
int __stdcall HOOK_RepeatedNicks(char *name);
#else
int __cdecl HOOK_RepeatedNicks(int, char *name);
#endif

int GetFileSize();
bool GetNickLengthAddresses(char *address, char *&MinimumNickLength, char *&MaximumNickLength);
bool CheckMemmory(char*check, char*mas, int mas_length, bool include_null); // If 'include_null = false' - Don't check NULL number
void ShowErrorMessage(char hook_name[], int error_code);
void ShowCopiratesInfo();