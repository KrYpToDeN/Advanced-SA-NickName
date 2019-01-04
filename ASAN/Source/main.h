#pragma once

#include "headers.h"
#include "constants.h"

#include "SDK/plugin.h"

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports();
PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData);
PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx);
PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx);
PLUGIN_EXPORT void PLUGIN_CALL Unload();



