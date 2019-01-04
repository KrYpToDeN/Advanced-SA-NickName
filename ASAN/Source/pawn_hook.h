#pragma once

#include "headers.h"

#define MAX_PLUGIN_NATIVES (6 + 1)

cell AMX_NATIVE_CALL ASAN_HOOK_ConnectPlayer(AMX* amx, cell* params);
cell AMX_NATIVE_CALL ASAN_HOOK_DisconnectPlayer(AMX* amx, cell* params);
cell AMX_NATIVE_CALL ASAN_HOOK_GetPlayerName(AMX *amx, cell *params);
cell AMX_NATIVE_CALL ASAN_IsValidNickName(AMX *amx, cell *params);
cell AMX_NATIVE_CALL ASAN_GetMinNickLength(AMX *amx, cell *params);
cell AMX_NATIVE_CALL ASAN_GetMaxNickLength(AMX *amx, cell *params);
