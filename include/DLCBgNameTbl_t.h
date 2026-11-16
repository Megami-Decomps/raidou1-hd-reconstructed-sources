#pragma once
#include "types.h"

typedef struct BgNameTbl_t BgNameTbl_t;
typedef struct DLCBgNameTbl_t DLCBgNameTbl_t;

struct BgNameTbl_t {
    s32 _floorID;
    char *_assetName;
    char *_bgName;
    s32 *_cutTbl;
    char *_cameraHit;
    char *_extraWall;
    char *_extraCamera;
    s32 _encountFlg;
    sdfVector3_t _bgAddVect;
};

struct DLCBgNameTbl_t {
    s32 _fieldID;
    BgNameTbl_t *_BgName;
};
