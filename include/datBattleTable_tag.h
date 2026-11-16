#pragma once
#include "types.h"

typedef struct BattleTableData_tag BattleTableData_tag;
typedef struct datBattleTable_tag datBattleTable_tag;

struct BattleTableData_tag {
    void *pp;
    s32 size;
};

struct datBattleTable_tag {
    char *pFileName;
    BattleTableData_tag *data[20];
};
