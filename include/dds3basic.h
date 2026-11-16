#pragma once
#include "types.h"
#include "basic.h"

typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3PoseSet_t dds3PoseSet_t;

extern u32 dds3SerializeID_serialCounter;

void dds3GetSclPoseSetMCR(dds3Basic_t *_pBasic);
void dds3GetPos2PoseSetMCR(dds3Basic_t *_pBasic);
void dds3GetPosPoseSetMCR(dds3Basic_t *_pBasic);
void dds3GetRotPoseSetMCR(dds3Basic_t *_pBasic);
dds3Basic_t *dds3Add(BASIC_TYPE type);
void dds3Delete(dds3Basic_t *basic);
bool dds3InitPoseSet(dds3Basic_t *basic);
void dds3FreePoseSet(dds3Basic_t *basic);
void dds3OnPoseSetFlag(dds3PoseSet_t *pPoseSet, u32 flag);
void dds3OffPoseSetFlag(dds3PoseSet_t *pPoseSet, u32 flag);
bool dds3CheckPoseSetFlag(dds3PoseSet_t *pPoseSet, u32 flag);
void dds3InitPoseSetValue(dds3PoseSet_t *pPoseSet);
void dds3BackupPoseSet(dds3PoseSet_t *pPoseSet);
void dds3SetRadiusPoseSet(dds3Basic_t *pBasic, f32 radius);
f32 dds3GetRadiusPoseSet(dds3Basic_t *pBasic);
void dds3SetPosPoseSet(dds3Basic_t *pBasic, const sdfVector4_t *pos);
void dds3SetRotPoseSet(dds3Basic_t *pBasic, const sdfVector4_t *rot);
void dds3SetSclPoseSet(dds3Basic_t *pBasic, const sdfVector4_t *scl);
void dds3GetPosPoseSet(dds3Basic_t *pBasic);
void dds3GetRotPoseSet(dds3Basic_t *pBasic);
void dds3GetSclPoseSet(dds3Basic_t *pBasic);
void dds3AddPosPoseSet(dds3Basic_t *pBasic, const sdfVector4_t *pos);
void dds3AddRotPoseSet(dds3Basic_t *pBasic, const sdfVector4_t *rot);
void dds3AddSclPoseSet(dds3Basic_t *pBasic, const sdfVector4_t *scl);
void dds3MakeMatrix(const sdfVector4_t *scale, const sdfVector4_t *quaternion, const sdfVector4_t *transrate);
void dds3GetTMPoseSet(dds3Basic_t *pBasic);
bool dds3RadiusCheckPoseSet(dds3PoseSet_t *p1, dds3PoseSet_t *p2);
bool dds3RadiusCheckPoseSet2(dds3PoseSet_t *p1, dds3PoseSet_t *p2);
bool dds3CallMainProcuder(dds3Basic_t *basic);
bool dds3CallDrawProcuder(dds3Basic_t *basic);
u32 dds3SerializeID(void);
void dds3SetBasicName(dds3Basic_t *basic, char *name);
char *dds3GetBasicName(dds3Basic_t *basic);
