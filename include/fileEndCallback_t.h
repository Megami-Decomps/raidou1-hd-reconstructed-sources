#pragma once
#include "types.h"

typedef struct fileHandle_t fileHandle_t;

typedef void (*fileEndCallback_t)(fileHandle_t *cb, void *parm);
