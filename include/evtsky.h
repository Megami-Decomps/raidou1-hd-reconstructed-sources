#pragma once
#include "types.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;

extern bool fldbokasi;
extern bool skyanime;

void evtSetBokasi(bool sw);
void evtSetAlpha(s32 frame, s32 a);
bool evtCheckAlphaAnime(void);
void Exit(void);
dds3ProcessID_t *evtInit(void);
