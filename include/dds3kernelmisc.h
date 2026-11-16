#pragma once
#include "types.h"
#include "kernel.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct sdfDrawTag_t sdfDrawTag_t;

void SelectSub(s32 *pbase, s32 *pm, s32 list, s32 win, s32 pad, s32 pluskey, s32 minuskey);
s32 dds3SelectMenu(s32 pad, s32 listsx, s32 listsy, s32 winsx, s32 winsy, s32 *basex, s32 *basey, s32 *x, s32 *y);
void dds3ConsPanelTagLink(sdfDrawTag_t *tag, s32 x, s32 y, s32 sx, s32 sy);
void dds3ConsPanelTagLinkZ(sdfDrawTag_t *tag, s32 x, s32 y, s32 sx, s32 sy, s32 z);
dds3ProcessFunc_t dds3VibrationTestProcess(dds3ProcessID_t *id);
void *dds3GetCanvasTransform(void *canvas);
