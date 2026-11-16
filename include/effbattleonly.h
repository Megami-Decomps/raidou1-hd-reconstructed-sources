#pragma once
#include "types.h"

typedef enum {
    EFFBATTLEONLY_TYPE_NON = 0,
    EFFBATTLEONLY_TYPE_XxPOINTLIGHT = 1,
    EFFBATTLEONLY_TYPE_XxMODELCOLOR = 2,
    EFFBATTLEONLY_TYPE_XxEFFECTLIGHT = 3,
    EFFBATTLEONLY_TYPE_XxCAMERA_F2 = 4,
    EFFBATTLEONLY_TYPE_XxMOTION = 5,
    EFFBATTLEONLY_TYPE_XxSE = 6,
    EFFBATTLEONLY_TYPE_XxFIELDLIGHT = 7,
    EFFBATTLEONLY_TYPE_XxPADVIBE = 8,
    EFFBATTLEONLY_TYPE_XxFILTER_FLD = 9,
    EFFBATTLEONLY_TYPE_XxFOVY = 10,
    EFFBATTLEONLY_TYPE_S_UNITDISP = 11,
    EFFBATTLEONLY_TYPE_S_POINTLIGHT = 12,
    EFFBATTLEONLY_TYPE_S_MODELCOLOR = 13,
    EFFBATTLEONLY_TYPE_MAX = 14,
} EFFBATTLEONLY_TYPE;

typedef struct Standard Standard;
typedef struct bonlyHandle_t bonlyHandle_t;
typedef struct effOption effOption;
typedef struct effPartsHandle_t effPartsHandle_t;

struct bonlyHandle_t {
    effOption *option;
    sdfVector4_t pos;
    sdfVector4_t rot;
    f32 scale;
    sdfVector4_t abgr;
    s32 frame;
    EFFBATTLEONLY_TYPE type;
    void *pHandle;
    void *pParams;
};

bonlyHandle_t *effPartsCreate(Standard *pParts);
void effDelete(effPartsHandle_t *handle);
bonlyHandle_t *Copy(effPartsHandle_t *handle);
void effCalcAndDraw(effPartsHandle_t *handle);
void effPositionSet(effPartsHandle_t *handle, const sdfVector4_t *pPos);
void effRotateSet(effPartsHandle_t *handle, const sdfVector4_t *pRot);
void effColorSet(effPartsHandle_t *handle, const sdfVector4_t *abgr);
void effScaleSet(effPartsHandle_t *handle, f32 scale);
