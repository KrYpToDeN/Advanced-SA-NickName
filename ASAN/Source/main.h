#pragma once

#include "headers.h"
#include "constants.h"

#define HAVE_STDINT_H

#include "lib/SDK/amx/amx.h"
#include "lib/SDK/plugincommon.h"

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports();
PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData);
PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx);
PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx);
PLUGIN_EXPORT void PLUGIN_CALL Unload();



