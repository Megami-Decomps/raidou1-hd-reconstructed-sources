#include "types.h"
#include "aw.h"
#include "aw_enemyhitback.h"
#include "sbtl.h"
#include "sbtleff.h"
#include "sbtlsub.h"
#include "sbtlunit.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e35fe0
void Init(void) {
  ;
}

// 0x1e35ff0
s32 Add(s32 _TargetListID) {
  AW_Func v5;
  s32 v6;
  AW_WORK_t *AW;
  s32 *StepIntBuff;
  __int128 v9;
  char *v10;

  if (GetAW_Unit_ListID(405, TargetListID))
    return -1;
  v5 = Allocate(AW_Func);
  _ctor(v5, 0, Method_Project_AW_EnemyHitBack_Calc__, 0);
  v6 = Add(405, 0.0, 0.0, 0.0, 0, v5, 0, 1);
  AW = GetAW(v6);
  StepIntBuff = AW->StepIntBuff;
  *(u64 *)&v9 = -1;
  *((u64 *)&v9 + 1) = -1;
  AW->Unit_ListID = TargetListID;
  *(_OWORD *)StepIntBuff = v9;
  *(_OWORD *)&StepIntBuff[4] = v9;
  v10 = "AW_EnemyHitBack";
  AW->DbgStr = "AW_EnemyHitBack";
  return v6;
}

// 0x1e36160
void Delete(AW_WORK_t *aWork) {
  s32 Idx;

  Idx = aWork->Idx;
  DelAW(Idx, 0);
}

// 0x1e361d0
void Calc(AW_WORK_t *aWork) {
  s32 Step;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 Unit_ListID;
  SBTLUNIT_WORK *v7;
  s32 Idx;
  SBTLUNIT_WORK *v10;
  SBTLACTAI_WORK *actaiwk;
  f32 hitbk_cnt;
  f32 hit_area_r;
  f32 v17;
  SBATTLE_WORK *wk_local;
  SBTLUNIT_LISTWORK *TargetList_MASK;
  SBTLUNIT_LISTWORK *other_List2;
  s64 i;
  SBTLUNIT_LISTWORK *v23;
  SBTLUNIT_LISTWORK *v24;
  SBTLUNIT_WORK *pUnit;
  bool v27;
  s32 *StepIntBuff;
  s32 ListID;
  f32 x;
  f32 z;
  f32 v32;
  f32 v33;
  f32 LenXZ;
  f32 v35;
  long f64 v36;
  s64 v37;
  s64 v38;
  s32 *v39;
  s32 *m_Items;
  SBTLUNIT_LISTWORK *v42;
  SBTLUNIT_LISTWORK *p_other_List2;
  SBTLUNIT_LISTWORK *v45;
  sdfVector4_t v46;
  sdfVector4_t v47;

  Step = aWork->Step;
  if (Step == 1)
  {
    Idx = aWork->Idx;
LABEL_14:
    DelAW(Idx, 0);
    return;
  }
  if (Step)
    return;
  UnitMng = wk->UnitMng;
  Unit_ListID = aWork->Unit_ListID;
  v7 = sBtlSearchUnit_ID(UnitMng, Unit_ListID);
  if (!v7)
    goto LABEL_30;
  v10 = v7;
  if (!sBtlCheckLiveTarget_NotHitDmg(v7))
  {
LABEL_30:
    Idx = aWork->Idx;
    goto LABEL_14;
  }
  if (!sBtlCheckLiveTarget2(v10))
    goto LABEL_30;
  actaiwk = v10->actaiwk;
  hitbk_cnt = actaiwk->hitbk_cnt;
  if (hitbk_cnt >= 0.9 || hitbk_cnt <= 0.1)
  {
    if (hitbk_cnt >= 0.9)
      Delete(aWork);
  }
  else
  {
    hit_area_r = actaiwk->hit_area_r;
    *(u64 *)&v46.x = 0;
    *(u64 *)&v46.z = 0;
    if (hit_area_r >= 100.0)
      v17 = hit_area_r;
    else
      v17 = 100.0;
    wk_local = wk;
    TargetList_MASK = sBtlCreateTargetList_MASK(2, 0, 0x10000);
    wk_local->other_List2 = TargetList_MASK;
    other_List2 = wk->other_List2;
    if (other_List2->count)
    {
      for (i = 0; ; ++i)
      {
        v24 = wk->other_List2;
        if (i >= v24->count)
          break;
        v24 = wk->other_List2;
        pUnit = v24->pUnitL[i]->pUnit;
        if (pUnit)
          v27 = pUnit == v10;
        else
          v27 = 1;
        if (!v27)
        {
          if (sBtlCheckDamageTarget(pUnit))
          {
            StepIntBuff = aWork->StepIntBuff;
            ListID = pUnit->ListID;
            if (StepIntBuff[0] != ListID && StepIntBuff[1] != ListID && StepIntBuff[2] != ListID && StepIntBuff[3] != ListID && StepIntBuff[4] != ListID && StepIntBuff[5] != ListID && StepIntBuff[6] != ListID && StepIntBuff[7] != ListID)
            {
              x = v10->pos.x;
              z = v10->pos.z;
              v32 = pUnit->pos.x;
              v33 = pUnit->pos.z;
              LenXZ = sBtlGetLenXZ(x, z, v32, v33);
              v35 = pUnit->actaiwk->hit_area_r;
              if (v35 < 100.0)
                v35 = 100.0;
              if (LenXZ < (f32)(v17 + v35))
              {
                sBtlGetUnitHelperPos(pUnit, 21);
                sub_1B335A0(&v46, 0, v36);
                v47 = v46;
                v37 = *(u64 *)&v46.x;
                v38 = *(u64 *)&v46.z;
                *(u64 *)&v47.z = v38;
                *(u64 *)&v47.x = v37;
                SetDamageProc(pUnit, v10, 144, v47);
                v39 = aWork->StepIntBuff;
                m_Items = v39;
                if (v39[0] != -1)
                {
                  m_Items = &v39[1];
                  if (v39[1] != -1)
                  {
                    m_Items = &v39[2];
                    if (v39[2] != -1)
                    {
                      m_Items = &v39[3];
                      if (v39[3] != -1)
                      {
                        m_Items = &v39[4];
                        if (v39[4] != -1)
                        {
                          m_Items = &v39[5];
                          if (v39[5] != -1)
                          {
                            m_Items = &v39[6];
                            if (v39[6] != -1)
                            {
                              m_Items = &v39[7];
                              if (v39[7] != -1)
                                goto LABEL_89;
                            }
                          }
                        }
                      }
                    }
                  }
                }
                *m_Items = pUnit->ListID;
                if (v39[7] != -1)
                {
LABEL_89:
                  v42 = wk->other_List2;
                  sBtlDeleteUnitList(v42, 0);
                  p_other_List2 = &wk->other_List2;
                  p_other_List2 = 0;
                  Delete(aWork);
                  return;
                }
              }
            }
          }
        }
      }
      v24 = wk->other_List2;
      sBtlDeleteUnitList(v24, 0);
      v45 = &wk->other_List2;
      v45 = 0;
    }
    else
    {
      other_List2 = wk->other_List2;
      sBtlDeleteUnitList(other_List2, 0);
      v23 = &wk->other_List2;
      v23 = 0;
    }
  }
}
