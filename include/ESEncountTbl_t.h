#pragma once
#include "types.h"

typedef enum {
    eMoveType_None = 0,
    eMoveType_Path = 1,
    eMoveType_Range_Sphere = 2,
    eMoveType_Range_OBB = 3,
} eMoveType;

typedef enum {
    On = 0,
    Off = 1,
    Immediate = 2,
} eDiscoveryType;

typedef enum {
    eSpawnerType_Normal = 0,
    eSpawnerType_TrapOne = 1,
    eSpawnerType_TrapWrapAround = 2,
} eSpawnerType;

typedef struct ESEncountTbl_EncountPack_t ESEncountTbl_EncountPack_t;
typedef struct ESEncountTbl_t ESEncountTbl_t;

struct ESEncountTbl_t {
    s32 _uniqueID;
    s32 _line;
    s16 _id;
    s16 _map;
    s16 _floor;
    bool _is_ignoreInstantDeath;
    bool _chapters[13];
    s16 _pos[2];
    s16 _dir;
    eDiscoveryType _discoveryType;
    bool _is_nakamaModeEncount;
    eMoveType _moveType;
    s16 _routes[8];
    bool _isPathLoop;
    eSpawnerType _spawnerType;
    s16 _popPos[2];
    s16 _popRadius;
    ESEncountTbl_EncountPack_t *_packs[3];
    sdfVector3_t Pos;
    f32 Dir;
    sdfVector3_t PopPos;
    f32 PopRadius;
    sdfVector3_t Routes[4];
    s32 PathRouteCount;
};
