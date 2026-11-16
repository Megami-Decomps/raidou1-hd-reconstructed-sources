#include "types.h"
#include "sbtl.h"
#include "sbtleffbo.h"
#include "sbtlunit.h"

typedef struct SBTLUNIT_LISTWORK SBTLUNIT_LISTWORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

SBTLUNIT_WORK *sbtleffbo_acter;
SBTLUNIT_WORK *sbtleffbo_target;

// 0x1999560
bool sBtlEffSetActer(s32 id) {
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v5;

  UnitMng = wk->UnitMng;
  v5 = sBtlSearchUnit_ID(UnitMng, id);
  sbtleffbo_acter = v5;
  return 1;
}

// 0x1999640
bool sBtlEffSetTarget(s32 id) {
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v5;

  UnitMng = wk->UnitMng;
  v5 = sBtlSearchUnit_ID(UnitMng, id);
  sbtleffbo_target = v5;
  return 1;
}

// 0x1999710
SBTLUNIT_LISTWORK *sBtlEffCreateUnitList(u8 area) {
  SBTLUNIT_LISTWORK *UnitList;
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  SBTLUNIT_WORK *sbtleffbo_acter_local;
  SBTLUNIT_WORK *sbtleffbo_target_local;

  if (!wk)
    return 0;
  if (wk->UnitMng)
  {
    UnitList = sBtlCreateUnitList(48);
    for (i = 0; ; ++i)
    {
      UnitMng = wk->UnitMng;
      if (i >= UnitMng->number)
        return UnitList;
      pUnit = UnitMng->pUnitL[i]->pUnit;
      if (!pUnit)
        continue;
      switch (area)
      {
        case 0u:
          if ((pUnit->side & 7) != 0)
            goto LABEL_13;
          continue;
        case 1u:
          sbtleffbo_acter_local = sbtleffbo_acter;
          if (sbtleffbo_acter_local)
            goto LABEL_36;
          continue;
        case 2u:
          goto LABEL_35;
        case 3u:
        case 6u:
        case 7u:
          continue;
        case 4u:
          sbtleffbo_target_local = sbtleffbo_acter;
          if (!sbtleffbo_target_local)
            continue;
          goto LABEL_31;
        case 5u:
          sbtleffbo_target_local = sbtleffbo_target;
          if (!sbtleffbo_target_local)
            continue;
LABEL_31:
          if (((pUnit->side ^ sbtleffbo_target_local->side) & 0x3F) == 0)
            goto LABEL_13;
          continue;
        case 8u:
          if (sbtleffbo_acter && sbtleffbo_acter->ListID == pUnit->ListID)
            goto LABEL_13;
LABEL_35:
          sbtleffbo_acter_local = sbtleffbo_target;
          if (!sbtleffbo_acter_local)
            continue;
LABEL_36:
          if (sbtleffbo_acter_local->ListID == pUnit->ListID)
          {
LABEL_13:
            sBtlEntryUnitList(UnitList, pUnit);
          }
          break;
        default:
          goto LABEL_13;
      }
    }
  }
  return 0;
}

// 0x19999a0
void sBtlEffDeleteUnitList(SBTLUNIT_LISTWORK *lwk) {
  sBtlDeleteUnitList(lwk, 0);
}
