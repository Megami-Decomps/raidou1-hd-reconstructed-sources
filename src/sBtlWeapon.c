#include "types.h"
#include "SBWEAPON_TYPE.h"
#include "sbtl.h"
#include "sbtlweapon.h"

typedef struct SBTLWEAPON_TBL SBTLWEAPON_TBL;

SBTLWEAPON_TBL *tbl;

// 0x2133430
SBWEAPON_TYPE sBtlDatType(s32 _WeaponId) {
  return tbl[WeaponId]->m_type;
}

// 0x21334a0
SBTLWEAPON_TBL *sBtlDat(void) {
  return tbl[wk->weaponId];
}
