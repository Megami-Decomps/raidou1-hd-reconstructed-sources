#pragma once
#include "types.h"

#define RADIUS 0.5
#define GRID_CROSSROAD 1
#define GRID_ADJUST 2
#define FOLLOW_LEFTBEHIND -2
#define FOLLOW_LEFT -1
#define FOLLOW_RIGHT 1
#define FOLLOW_RIGHTBEHIND 2
#define TRUE 1
#define FALSE 0
#define LOOP_NUM 60
#define SMALL 0.0001
#define HEADON_DIST 11
#define EVADEPLAYER_MULT 1.2
#define EVADEPLAYER_STILL_DIST 0.5
#define EVADEPLAYER_DIST 5
#define EVADEOBJECT_DIST 7
#define FRIEND_DIST 0.3
#define ROTATE_NORMAL 0.12
#define CTN_VIEW_MAX 40
#define DEBUG 0
#define CITIZEN_MAX 256
#define FRIEND_MAX 4
#define TIME_SLICE 6
#define TIME_SLICE_F 6
#define BLOCK_CITIZEN_MAX 64
#define EXIT_MAX 16
#define OBJECT_MAX 64
#define BLOCK_TYPE_CORNER 0
#define BLOCK_TYPE_EDGE 1
#define MOVE_MOVED 1
#define MOVE_TURNING 2
#define MOVE_SLIDEIN 4
#define MOVE_EVADEPLAYER 8
#define MOVE_LEADER 16
#define MOVE_WAIT 32
#define MOVE_EXIT 64
#define MOVE_EXIT2 536870912
#define MOVE_BIRTH 128
#define MOVE_EVADEOBJECT 256
#define SPDTYPE_SLOW 0
#define SPDTYPE_FAST 1
#define DEFSPD_SLOW 1
#define DEFSPD_FAST 1.45

typedef enum {
    CTN_EVADE_NONE = 0,
    CTN_EVADE_LEFT = 1,
    CTN_EVADE_CENTER = 2,
    CTN_EVADE_RIGHT = 3,
} CTN_EVADE;

typedef struct ctnBlock_t ctnBlock_t;
typedef struct ctnCitizen_t ctnCitizen_t;
typedef struct ctnExit_t ctnExit_t;
typedef struct ctnGrid_t ctnGrid_t;
typedef struct ctnInput_t ctnInput_t;
typedef struct ctnObject_t ctnObject_t;
typedef struct ctnTargetInfo_t ctnTargetInfo_t;
typedef struct ctnWork_t ctnWork_t;

struct ctnInput_t {
    s32 fPlayer;
    f32 playerX;
    f32 playerY;
    s32 waitFlag;
};

struct ctnTargetInfo_t {
    f32 moveDir[2];
    f32 moveNormal[2];
    s32 blockIndex;
    s32 leftWallIndex;
    s32 rightWallIndex;
    s32 resv;
};

struct ctnCitizen_t {
    sdfVector4_t rotateQuat;
    s32 fExist;
    f32 x;
    f32 y;
    f32 vx;
    f32 vy;
    f32 targetVx;
    f32 targetVy;
    f32 vleng;
    f32 dirX;
    f32 dirY;
    f32 normalX;
    f32 normalY;
    f32 offCenter;
    f32 leftWallDist;
    f32 rightWallDist;
    s32 index;
    s32 sliceIndex;
    s32 attr;
    u8 exitIndex;
    s8 pathPref;
    u8 classType;
    s8 followType;
    u8 friendNum;
    u8 blockIndex;
    u8 belongIndex;
    CTN_EVADE evadeType;
    ctnTargetInfo_t *pTargetInfo;
    ctnCitizen_t *pAhead;
    ctnCitizen_t *pBehind;
    ctnCitizen_t *pHeadOn;
    ctnCitizen_t *pFriends[4];
    s32 playerEvadeArray[7];
    s32 resv0;
    s32 objectEvadeArray[7];
    s32 objectDir;
    s32 aheadEvadeArray[7];
    s32 spdType;
    s32 dir;
    f32 angle;
    f32 oldX;
    f32 oldY;
    s32 newModelID;
    s32 NgCount;
};

struct ctnBlock_t {
    s32 index;
    f32 crowd;
    f32 area;
    s32 citizenNum;
    ctnCitizen_t *pCitizen[64];
    f32 *vertex[4];
    f32 *normal[4];
    ctnTargetInfo_t *targetInfo[4];
    s32 fExit[16];
    f32 dist[16];
    s32 type;
    s32 connectNum;
    s32 resv[2];
};

struct ctnExit_t {
    f32 *vertex[2];
    f32 dir[2];
    s32 leng;
    s32 curCnt;
    s32 index;
    s32 originalInterval;
    s32 interval;
    s32 blockIndex;
    s32 group;
    s32 popularity;
};

struct ctnGrid_t {
    ctnBlock_t *pBlock;
    s32 x;
    s32 y;
    u8 dummy;
    u8 signalIndex[5];
    u8 attr;
    u8 citizenNum;
    s32 resv[3];
};

struct ctnObject_t {
    f32 center[2];
    f32 radius;
    s32 resv;
};

struct ctnWork_t {
    ctnGrid_t *pGrid;
    ctnGrid_t *gridData;
    ctnBlock_t *blockArray;
    s32 gridNum;
    ctnExit_t *exitArray[16];
    ctnCitizen_t *citizenArray[256];
    ctnObject_t *objectArray[64];
    s32 objectNum;
    s32 timeSliceNum[6];
    s32 xMax;
    s32 yMax;
    s32 blockNum;
    s32 exitNum;
    s32 citizenNum;
    s32 sliceIndex;
    s32 fPlayer;
    f32 playerX;
    f32 playerY;
    f32 playerOldX;
    f32 playerOldY;
    f32 playerVx;
    f32 playerVy;
    s32 waitFlag;
    s32 mapID;
    s32 floorID;
    s32 debugIndex;
};

extern ctnWork_t *Work;
extern s32 gMap03_CntN;
extern s32 gMap03_CntS;

void ctnLoadDataIDFloor(s32 id, s32 floor);
ctnGrid_t *ctnGetGrid(s32 x, s32 y);
void ctnMemFree(void);
void ctnUpdate(ctnInput_t *pInput);
void ctnAdjustShoot(f32 ratio);
void ctnNormalizeVec(f32 *vx, f32 *vy);
bool ctnCheckClose(s32 map, s32 id, ctnCitizen_t *ctn);
f32 ctnCameraRelativeDistance(f32 camX, f32 camZ, f32 ctnX, f32 ctnZ);
