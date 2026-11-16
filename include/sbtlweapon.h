#pragma once
#include "types.h"
#include "ITM.h"
#include "SBWEAPON_TYPE.h"
#include "SKLID.h"

typedef struct SBTLWEAPON_MAT_TBL SBTLWEAPON_MAT_TBL;
typedef struct SBTLWEAPON_TBL SBTLWEAPON_TBL;
typedef struct sdatParaWork_t sdatParaWork_t;

struct SBTLWEAPON_MAT_TBL {
    ITM Item;
    s8 Num;
};

struct SBTLWEAPON_TBL {
    s32 m_atk;
    SBWEAPON_TYPE m_type;
    sdatParaWork_t *m_paraBns;
    SKLID m_hojo;
    ITM *BaseItem[7];
    SBTLWEAPON_MAT_TBL *Material[4];
    s32 gold;
    s16 effectcolor;
    s16 treeStage;
    s16 branchNo;
};

extern SBTLWEAPON_TBL *tbl;

SBWEAPON_TYPE sBtlDatType(s32 _WeaponId);
SBTLWEAPON_TBL *sBtlDat(void);
