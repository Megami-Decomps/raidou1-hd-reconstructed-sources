#pragma once
#include "types.h"
#include "libsdf.h"

typedef struct sdfDrawTag_t sdfDrawTag_t;
typedef struct sdfGrOt_t sdfGrOt_t;

void sdfGrOtFuncLinkToHead(sdfGrOt_t *aOt, sdfDrawTag_t *aTag);
void sdfGrOtNormalReg(sdfGrOt_t *aOt, sdfDrawTag_t *aTag);
void sdfGrOtNormalCallback(sdfGrOt_t *aOt, SDF_OT_FUNC aFunc, sdfDrawTag_t *aData);
void sdfGrOtInit(sdfGrOt_t *aOt, s32 aNumOt);
sdfDrawTag_t *sdfGrOtClose(sdfGrOt_t *aOt);
