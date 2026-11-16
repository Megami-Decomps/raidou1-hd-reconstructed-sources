#pragma once
#include "types.h"

#define DEBUG 0
#define DATA_FILENAME "neko.NEK"
#define MAX 5
#define CONNECT_MAX 16

typedef struct nekoHome_t nekoHome_t;
typedef struct nekoNeko_t nekoNeko_t;
typedef struct nekoPoint_t nekoPoint_t;
typedef struct nekoWork_t nekoWork_t;

struct nekoHome_t {
    f32 x;
    f32 y;
    f32 angle;
    f32 rotateQuat[4];
    s32 connectNum;
    s32 connectedPointIndexArray[16];
};

struct nekoPoint_t {
    f32 x;
    f32 y;
    s32 type;
    f32 dirX;
    f32 dirY;
    f32 angle;
    f32 rotateQuat[4];
    s32 connectNum;
    s32 connectedPointIndexArray[16];
    s32 resv;
};

struct nekoNeko_t {
    sdfVector4_t rotateQuat;
    s32 fExist;
    s32 index;
    f32 x;
    f32 y;
    f32 vx;
    f32 vy;
    f32 targetVx;
    f32 targetVy;
    f32 vleng;
    f32 angle;
    s32 state;
    s32 homeIndex;
    s32 nextPointIndex;
    s32 prevPointIndex;
    s32 hideCnt;
    s32 existCnt;
};

struct nekoWork_t {
    nekoNeko_t *nekoArray[5];
    nekoHome_t *homeArray;
    nekoPoint_t *pointArray;
    s32 nekoNum;
    s32 homeNum;
    s32 pointNum;
    f32 playerX;
    f32 playerY;
};

extern s32 gNekoFlag;
extern nekoWork_t *Work;

void nekoStart(void);
void nekoMemFree(void);
void nekoUpdate(f32 playerX, f32 playerY);
