#pragma once
#include "types.h"

typedef struct AW_XAtk_Arg_t AW_XAtk_Arg_t;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

struct AW_XAtk_Arg_t {
    s32 ID;
    SBTLUNIT_WORK *wk;
};

extern AW_XAtk_Arg_t *ArgumentParam;

void Init(void);
void Add(s32 _ID, SBTLUNIT_WORK *_wkEnemy);
void Add_2(void);
void ClearBattleEnd(void);
