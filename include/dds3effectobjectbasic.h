#pragma once
#include "types.h"

typedef struct dds3BasicFunction_t dds3BasicFunction_t;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3EffectObjectBasicWorkData_t dds3EffectObjectBasicWorkData_t;
typedef struct dds3ObjectBaseControlWorkData_t dds3ObjectBaseControlWorkData_t;

extern dds3BasicFunction_t *Function;

bool dds3EffectObjectBasicConstructor(dds3Basic_t *aPtr);
void dds3EffectObjectBasicDestructor(dds3Basic_t *aPtr);
bool dds3EffectObjectBasicMainProcedure(dds3Basic_t *aPtr);
bool dds3EffectObjectBasicDrawProcedure(dds3Basic_t *aPtr);
dds3ObjectBaseControlWorkData_t *dds3EffectObjectBasicGetControlWorkData(dds3Basic_t *pBasic);
dds3Basic_t *dds3EffectObjectBasicAdd(u32 serialID, const sdfVector4_t *aPos, const sdfVector4_t *aRot);
dds3Basic_t *dds3EffectObjectBasicAddD3P2(void *effdata, const sdfVector4_t *pos, const sdfVector4_t *rot);
dds3Basic_t *dds3EffectObjectBasicAddEPL(void *effdata, const sdfVector4_t *pos, const sdfVector4_t *rot);
dds3Basic_t *dds3EffectObjectBasicAddESP(char *name, const sdfVector4_t *pos, const sdfVector4_t *rot, f32 r);
dds3EffectObjectBasicWorkData_t *CheckESP(dds3Basic_t *b);
bool GetESPPos(dds3Basic_t *b);
s32 GetESPR(dds3Basic_t *b);
void dds3EffectObjectBasicStatOn(dds3Basic_t *basic, u32 s);
void dds3EffectObjectBasicStatOff(dds3Basic_t *basic, u32 s);
bool dds3EffectObjectBasicLinkObject(dds3Basic_t *basic, dds3Basic_t *target);
void dds3EffectObjectBasicGetObjectIndex(dds3Basic_t *basic);
s32 dds3EffectObjectBasicLinkObjectIndex(dds3Basic_t *basic, dds3Basic_t *target, s32 index);
void dds3EffectObjectBasicUnlinkObject(dds3Basic_t *basic);
