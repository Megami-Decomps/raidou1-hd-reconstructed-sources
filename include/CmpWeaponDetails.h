#pragma once
#include "types.h"

typedef struct CmpCheckSwordSet_CmpWeaponPara CmpCheckSwordSet_CmpWeaponPara;
typedef struct CmpWeaponDetails CmpWeaponDetails;

struct CmpWeaponDetails {
    void *weaponName;
    CmpCheckSwordSet_CmpWeaponPara *para;
};

struct CmpCheckSwordSet_CmpWeaponPara {
    void *para;
    void *paraNum;
};
