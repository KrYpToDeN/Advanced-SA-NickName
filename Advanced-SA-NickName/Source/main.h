#pragma once

typedef void(*logprintf_t)(char* format, ...);

logprintf_t logprintf;
void **ppPluginData;
extern void *pAMXFunctions;