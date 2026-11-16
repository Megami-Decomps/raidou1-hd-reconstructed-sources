#pragma once
#include "types.h"

typedef struct effQuakeRequest_t effQuakeRequest_t;

void effStopStat(void);
void effRestoreStat(void);
void effInit(void);
void effUpdate(void);
effQuakeRequest_t *effRegist(void);
void effStart(effQuakeRequest_t *req, u32 amp);
void effStartDamp(effQuakeRequest_t *req, u32 amp, u32 frame);
void effStartSignal(effQuakeRequest_t *req);
void effStop(effQuakeRequest_t *req);
void effRemove(effQuakeRequest_t *req);
