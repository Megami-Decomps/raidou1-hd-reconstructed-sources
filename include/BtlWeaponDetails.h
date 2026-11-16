#pragma once
#include "types.h"

typedef struct BattleUICheckSwordSet_CmpWeaponPara BattleUICheckSwordSet_CmpWeaponPara;
typedef struct BtlWeaponDetails BtlWeaponDetails;

struct BtlWeaponDetails {
    void *weaponName;
    BattleUICheckSwordSet_CmpWeaponPara *para;
};

struct BattleUICheckSwordSet_CmpWeaponPara {
    void *para;
    void *paraNum;
};
