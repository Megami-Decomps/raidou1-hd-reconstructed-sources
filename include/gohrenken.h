#pragma once
#include "types.h"
#include "ITM.h"

typedef struct gohData_t gohData_t;
typedef struct gohRenkenNewSwordList_t gohRenkenNewSwordList_t;
typedef struct gohRenkenSelMaterial_t gohRenkenSelMaterial_t;
typedef struct gohRenkenSelSwordList_t gohRenkenSelSwordList_t;
typedef struct sdatPlayerUnitWork_t sdatPlayerUnitWork_t;

void gohSelSwordList(gohRenkenSelSwordList_t *psSelf);
void gohNewSwordList(gohRenkenNewSwordList_t *psSelf, s32 iSwordNo);
void gohSelMaterial(gohRenkenSelMaterial_t *psSelf, s32 iSwordNo);
bool gohCheckAporion(s32 iNewSwordNo, s32 iBaseSwordNo);
s32 gohCheckComposition(s32 iNewSwordNo, s32 iBaseSwordNo);
void gohComposition(s32 iNewSwordNo, s32 iBaseSwordNo);
char *gohGetSwordName(s32 iSwordNo);
s32 gohGetSwordType(s32 iSwordNo);
s32 gohGetSwordAuraNo(s32 iSwordNo);
bool gohCheckSwordFlag(s32 iSwordNo);
void gohCreateMaterialDate(gohRenkenSelMaterial_t *_mat, ITM _swordNo);
void gohGetSwordSkl(gohData_t *_pData, sdatPlayerUnitWork_t *_player);
void gohAchievementUnlock(sdatPlayerUnitWork_t *_player);
