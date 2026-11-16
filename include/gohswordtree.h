#pragma once
#include "types.h"
#include "ITM.h"

typedef enum {
    TreeCsrMove_Up = 0,
    TreeCsrMove_Down = 1,
    TreeCsrMove_Left = 2,
    TreeCsrMove_Right = 3,
    TreeCsrMove_Max = 4,
} TreeCsrMove;

typedef struct gohData_t gohData_t;

void GohCsrUpdate(gohData_t *_pData);
void GohLrChangeUpdate(gohData_t *_pData);
void GohTreeMenuTypeAdd(gohData_t *_pData);
void GohTreeMenuTypeSub(gohData_t *_pData);
void GohMouseCsrUpdate(gohData_t *pData);
void GohSetScrollCsrSet(gohData_t *pData);
void SwordTreeCsrUpdate(gohData_t *pData);
s32 GohTreeCsrNext(gohData_t *_pData, TreeCsrMove _csrMove);
void GohCreateCheckSword(gohData_t *_pData);
bool GohCreateCheckSelSword(gohData_t *_pData, ITM _baseSd, ITM _sd);
ITM GohGetNowSelBaseSword(void);
