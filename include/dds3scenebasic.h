#pragma once
#include "types.h"
#include "basic.h"

typedef struct dds3BasicArrayHandle_t dds3BasicArrayHandle_t;
typedef struct dds3BasicFunction_t dds3BasicFunction_t;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct sdfBinary sdfBinary;

extern dds3BasicFunction_t *Function;

void dds3SceneBasicFreeScene(dds3Basic_t *pBasic);
void dds3SceneBasicVisible(dds3Basic_t *basic, bool visible);
dds3Basic_t *dds3SceneBasicAdd(BASIC_TYPE type);
void dds3SceneBasicDelete(dds3Basic_t *basic);
dds3Basic_t *SetActiveCamera(dds3Basic_t *pSceneBasic, dds3Basic_t *pCameraBasic);
dds3Basic_t *dds3SceneBasicGetActiveCamera(dds3Basic_t *pBasic);
dds3Basic_t *dds3SceneBasicSetActiveUnit(dds3Basic_t *pSceneBasic, dds3Basic_t *pUnitBasic);
dds3Basic_t *dds3SceneBasicGetActiveUnit(dds3Basic_t *pSceneBasic);
u32 dds3SceneBasicSearchSerialID_Used(u32 serialID);
dds3Basic_t *dds3SceneBasicSearch(dds3Basic_t *pBasic, u32 serialID, u32 type);
dds3BasicArrayHandle_t *dds3SceneBasicGetList(dds3Basic_t *pBasic, u32 type);
void dds3SceneBasicMakeScene(dds3Basic_t *pBasic, char *akey);
void dds3SceneBasicMakeScene_FromMemory(dds3Basic_t *pBasic, s32 field, s32 area, void *pF1, void *pF2, sdfBinary *pTB, sdfBinary *pBF);
bool dds3SceneBasicLoadScriptFile(dds3Basic_t *scene, char *scrfile, char *akey);
bool dds3SceneBasicLoadScriptFile_FromMem(dds3Basic_t *scene, void *mem);
void dds3SceneBasicReleaseScriptFile(dds3Basic_t *scene);
dds3ProcessID_t *dds3SceneBasicStartScript(dds3Basic_t *scene, char *procname);
void dds3SceneBasicEndScript(dds3Basic_t *scene, char *procname);
bool dds3SceneBasicExistBasicFromType(dds3Basic_t *scene, BASIC_TYPE type, dds3Basic_t *target);
bool dds3SceneBasicExistBasic(dds3Basic_t *scene, dds3Basic_t *target);
void dds3SetMapNo(dds3Basic_t *scene, s32 mapno);
s32 dds3GetMapNo(dds3Basic_t *scene);
dds3Basic_t *dds3SceneBasicSearchNameAndType(dds3Basic_t *scene, u32 type, char *name);
dds3Basic_t *dds3SceneBasicSearchName(dds3Basic_t *scene, char *name);
