#pragma once
#include "types.h"

typedef struct evtUnitHandle_t evtUnitHandle_t;

typedef bool (*ActionDelegate)(evtUnitHandle_t *h, void *data);
