#include "types.h"
#include "dat.h"
#include "dvl.h"
#include "gohkilldevil.h"

typedef struct gohKillDevil_t gohKillDevil_t;

// 0x1c05510
bool datCheckKillDevil(s32 iDevilID) {
  u8 *m_aBits;
  void *v5;

  m_aBits = GBWK->m_sKillDevil->m_aBits;
  v5 = Allocate(Project_CMFlag);
  _ctor(v5, m_aBits, SLODWORD(m_aBits->max_length), 0);
  if (IsENEMYOFFSET(iDevilID))
  {
    iDevilID = datCalcEnemyToNakamaID(iDevilID);
  }
  return TestBits(v5, iDevilID, 0);
}

// 0x1c05780
void datSetKillDevil(s32 iDevilID) {
  u8 *m_aBits;
  void *v5;

  m_aBits = GBWK->m_sKillDevil->m_aBits;
  v5 = Allocate(Project_CMFlag);
  _ctor(v5, m_aBits, SLODWORD(m_aBits->max_length), 0);
  if (IsENEMYOFFSET(iDevilID))
  {
    iDevilID = datCalcEnemyToNakamaID(iDevilID);
  }
  SetBits(v5, iDevilID, 1, 0);
}

// 0x1c05650
gohKillDevil_t *gohGetSelf(void) {
  return GBWK->m_sKillDevil;
}

// 0x1c056e0
s32 datGetDevilNo2BitIndex(s32 iDevilID) {
  if ((byte_5757279 & 1) == 0)
  {
    if (IsENEMYOFFSET(iDevilID))
      goto LABEL_3;
    return iDevilID;
  }
  if (!IsENEMYOFFSET(iDevilID))
    return iDevilID;
LABEL_3:
  return datCalcEnemyToNakamaID(iDevilID);
}
