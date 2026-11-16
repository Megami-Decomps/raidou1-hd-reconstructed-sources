#include "types.h"
#include "SKLID.h"
#include "SklItmRst.h"
#include "buttonguide.h"
#include "cmpitem.h"
#include "cmpmodel.h"
#include "cmpomoide.h"
#include "cmpstatus.h"
#include "cmpstatusitmsklset.h"
#include "dat.h"
#include "dds3_pad.h"
#include "fclmisc.h"
#include "fclmsg.h"
#include "itf.h"
#include "localize.h"
#include "sbtlitem.h"
#include "sbtlskill.h"
#include "sbtlsub.h"
#include "sdat.h"

#define NEW_SKL_CSR_NUM 12
#define SKLCHANGECHK_FRAME 30
#define CANCEL_WAIT 4

typedef struct sdatUnitWork_t sdatUnitWork_t;
typedef struct tagCMP_STATUS_WORK tagCMP_STATUS_WORK;

s32 sklType;
s32 oldSklCsr;
s32 setIndex;
SKLID setSkill;
SKLID oldSkill;
bool gaugeUp;
bool autoCsr;
ResultMesType rstMesType;

// 0x218d190
SklItmRst CmpStatusChkUseSklItem(sdatUnitWork_t *_unit, SKLID _skl) {
  if (!unit->devilid)
    return 0;
  if (IndexOf_Int32Enum_(g_aOmoide, skl) == -1)
    return CmpStatusChkNmlUseSklItem(unit, skl);
  else
    return CmpStatusChkOmoideUseSklItem(unit, skl);
}

// 0x218d2c0
SklItmRst CmpStatusChkOmoideUseSklItem(sdatUnitWork_t *_unit, SKLID _skl) {
  void *v5;
  bool Master;
  SKLID *aOmoideSkill;
  s32 v9;
  void *sklItemGuages;
  s32 v11;
  void *v12;
  void *v13;

  v5 = Allocate(Project_CmpStatusItmSklSet___c__DisplayClass13_0);
  v5->_skl = skl;
  Master = datOmoideSkillGetMaster(unit, skl);
  aOmoideSkill = unit->aOmoideSkill;
  if (Master)
  {
    v9 = IndexOf_Int32Enum_(aOmoideSkill, v5->_skl);
    sklItemGuages = unit->sklItemGuages;
    if (v9 == -1)
      v11 = 69;
    else
      v11 = 37;
    v12 = Allocate(System_Collections_Generic_List_SklItemGuage_);
    __ctor_48217552(v12, sklItemGuages);
    v13 = Allocate(System_Predicate_SklItemGuage_);
    __ctor(v13, v5, Method_Project_CmpStatusItmSklSet___c__DisplayClass13_0__ChkOmoideUseSklItem_b__0__, 0);
    if (_Find(v12, v13))
    {
      return v11;
    }
    else
    {
      return 0;
    }
  }
  else if (IndexOf_Int32Enum__39255936(aOmoideSkill, 0, 0, unit->iOmoideSkillCnt) == -1)
  {
    return 11;
  }
  else
  {
    return 3;
  }
}

// 0x218d4a0
SklItmRst CmpStatusChkNmlUseSklItem(sdatUnitWork_t *_unit, SKLID _skl) {
  void *v5;
  s32 devilid;
  void *sklItemGuages;
  void *v9;
  void *v10;

  v5 = Allocate(Project_CmpStatusItmSklSet___c__DisplayClass14_0);
  v5->_skl = skl;
  devilid = unit->devilid;
  if (!datChkKeisyouSkl(devilid, skl))
    return 0;
  if (IndexOf_Int32Enum_(unit->haveskill, v5->_skl) == -1 && IndexOf_Int32Enum_(unit->aRsvSkl, v5->_skl) == -1)
  {
    if (datSklItmDrawMaxCnt(unit) >= 8)
      return 11;
    else
      return 131;
  }
  else
  {
    sklItemGuages = unit->sklItemGuages;
    v9 = Allocate(System_Collections_Generic_List_SklItemGuage_);
    __ctor_48217552(v9, sklItemGuages);
    v10 = Allocate(System_Predicate_SklItemGuage_);
    __ctor(v10, v5, Method_Project_CmpStatusItmSklSet___c__DisplayClass14_0__ChkNmlUseSklItem_b__0__, 0);
    if (_Find(v9, v10))
    {
      return 5;
    }
    else if (IndexOf_Int32Enum_(unit->aRsvSkl, v5->_skl) == -1)
    {
      return 0;
    }
    else
    {
      return 19;
    }
  }
}

// 0x218d700
void CmpStatusAutoNmlSklSet(tagCMP_STATUS_WORK *wk) {
  SKLID *haveskill;
  il2cpp_array_size_t max_length;
  s64 v7;
  s32 v8;
  s32 *m_Items;
  s32 v10;
  sdatUnitWork_t *unit;
  u32 skillMax;
  Il2CppClass *klass;
  char *LocalizeText;
  Il2CppObject *Instance;
  s32 v16;
  s32 v17;
  SKLID *aRsvSkl;
  s64 v20;
  s64 v21;
  s32 *v22;
  s32 v23;

  setIndex = -1;
  if ((sklItmRst & 4) == 0)
    goto LABEL_5;
  haveskill = wk->unit->haveskill;
  max_length = haveskill->max_length;
  if ((s32)max_length >= 1)
  {
    v7 = 0;
    v8 = 0;
    m_Items = haveskill;
    while (1)
    {
      v10 = m_Items[v7];
      if (v10)
      {
        if (v10 == setSkill)
        {
          LODWORD(max_length) = v7;
          goto LABEL_27;
        }
      }
      else
      {
        ++v8;
      }
      if ((u32)max_length == ++v7)
        goto LABEL_26;
    }
  }
  LODWORD(max_length) = 0;
  v8 = 0;
LABEL_26:
  LODWORD(v7) = 0;
LABEL_27:
  setIndex = v7;
  cmpSetSklCsr(max_length - v8);
  return;
LABEL_5:
  if ((sklItmRst & 2) == 0)
    return;
  if ((sklItmRst & 0x10) == 0)
  {
    cmpSetSklCsrMax();
    unit = wk->unit;
    skillMax = wk->skillMax;
    unit->newSklCnt = 1;
    klass = _get_Instance()[10].klass;
    LocalizeText = GetLocalizeText("CMP_STATUS_L0018", 1);
    (*(klass->_1.image + 55))(klass, skillMax, LocalizeText, 2694693760LL, 0, *((u64 *)klass->_1.image + 56));
    Instance = _get_Instance();
    v16 = -1;
    (*(Instance[10].klass->_1.image + 59))(Instance[10].klass, 0xFFFFFFFFLL, skillMax, *((u64 *)Instance[10].klass->_1.image + 60));
    v17 = 0;
    goto LABEL_41;
  }
  aRsvSkl = wk->unit->aRsvSkl;
  if ((s32)aRsvSkl->max_length >= 1)
  {
    v20 = 0;
    v17 = 0;
    v21 = (u32)aRsvSkl->max_length;
    v22 = aRsvSkl;
    v16 = -1;
    while (1)
    {
      v23 = v22[v20];
      if (v23)
      {
        if (v23 == setSkill)
        {
          v16 = v20;
          goto LABEL_39;
        }
      }
      else
      {
        ++v17;
      }
      if (v21 == ++v20)
        goto LABEL_39;
    }
  }
  v17 = 0;
  v16 = -1;
LABEL_39:
  skillMax = v16 + 1;
  setIndex = v16 + 1;
LABEL_41:
  cmpSetSklCsr(skillMax);
  cmpSetRsvCsr(v16 - v17);
  return;
}

// 0x218da50
void CmpStatusAutoOmoideSklSet(tagCMP_STATUS_WORK *wk) {
  SKLID *aOmoideSkill;
  s32 setSkill_local;
  s32 v8;
  s32 v9;

  if ((sklItmRst & 4) != 0)
  {
    if ((sklItmRst & 0x40) == 0)
    {
      aOmoideSkill = wk->unit->aOmoideSkill;
      setSkill_local = setSkill;
      goto LABEL_14;
    }
    v9 = 0;
    while (1)
    {
      if (cmpCurGetSelectMemSklID() == setSkill)
        return;
      cmpMemSklCurNext(1);
      if (++v9 > SLODWORD(g_aOmoide->max_length))
        return;
    }
  }
  if ((sklItmRst & 2) == 0)
    return;
  setSkill_local = 0;
  aOmoideSkill = wk->unit->aOmoideSkill;
LABEL_14:
  v8 = IndexOf_Int32Enum_(aOmoideSkill, setSkill_local);
  cmpSetSklCsr(v8);
}

// 0x218dca0
void CmpStatusAutoSklSet(tagCMP_STATUS_WORK *wk) {
  if (IndexOf_Int32Enum_(g_aOmoide, setSkill) == -1)
    CmpStatusAutoNmlSklSet(wk);
  else
    CmpStatusAutoOmoideSklSet(wk);
}

// 0x218dde0
void CmpStatusSklSet(tagCMP_STATUS_WORK *wk) {
  sdatUnitWork_t *unit;
  s32 sklType;
  s32 SklCsrMax;
  s32 v6;
  _BOOL4 v7;
  s32 SklCsr;
  sdatUnitWork_t *v9;
  s32 v11;
  char *v13;

  unit = wk->unit;
  sklType = wk->sklType;
  SklCsrMax = cmpGetSklCsrMax(unit, sklType);
  cmpSklCsrMouse(1);
  if (!CHECK_TRIG(4100, 1) && !CHECK_REP(4100, 1))
  {
    if (CHECK_TRIG(4101, 1) || CHECK_REP(4101, 1))
    {
      if (cmpGetSklCsr() != 12)
      {
        cmpSklCsrD();
      }
      goto LABEL_85;
    }
    if (CHECK_TRIG(4102, 1) || CHECK_REP(4102, 1))
    {
      if (cmpGetSklCsr() != 2)
      {
        if (!wk->sklType)
          goto LABEL_65;
        if (cmpGetSklCsr() == 12)
        {
          v7 = SklCsrMax != 1;
          v6 = v7;
          goto LABEL_83;
        }
        if (!wk->sklType)
        {
LABEL_65:
          if (wk->rsvCsr)
          {
            if (cmpGetSklCsr() == 12)
            {
              v9 = wk->unit;
              if (datCheckRsvSkillCnt(v9) >= 1)
                wk->rsvCsr = 0;
              v6 = 1;
              goto LABEL_83;
            }
          }
        }
        cmpSklCsrL();
        goto LABEL_85;
      }
LABEL_27:
      v6 = 12;
LABEL_83:
      cmpSetSklCsr(v6);
      v11 = 3;
      goto LABEL_84;
    }
    if (!CHECK_TRIG(4103, 1) && !CHECK_REP(4103, 1))
    {
      if (CHECK_TRIG(4099, 1) && !wk->sklType)
      {
        wk->noSklHelp = !wk->noSklHelp;
        goto LABEL_85;
      }
      if (!CHECK_TRIG(4096, 1) || !CmpStatusCheckSklSet(wk))
        goto LABEL_85;
      v11 = 0;
      wk->step = 5;
LABEL_84:
      SE(v11);
      goto LABEL_85;
    }
    if (wk->sklType)
    {
      if (cmpGetSklCsr() == 1)
        goto LABEL_27;
    }
    if (SklCsrMax == 1)
    {
      if (!cmpGetSklCsr())
        goto LABEL_27;
    }
    if (wk->sklType)
      goto LABEL_111;
    if (cmpGetSklCsr() != 1)
    {
LABEL_111:
      if (cmpGetSklCsr() == 12 && SklCsrMax >= 3)
      {
        wk->rsvCsr = -1;
        v6 = 2;
        goto LABEL_83;
      }
    }
    else
    {
      if (!cmpGetRsvCsr())
        goto LABEL_60;
      if (cmpGetRsvCsr() == -1)
      {
        SklCsr = cmpGetSklCsr();
        if (cmpRNextRsvCsr(wk, SklCsr) == -1)
        {
LABEL_60:
          wk->rsvCsr = -1;
          goto LABEL_27;
        }
      }
    }
    cmpSklCsrR();
    goto LABEL_85;
  }
  if (cmpGetSklCsr() == 12)
    goto LABEL_85;
  cmpSklCsrU();
LABEL_85:
  if (cmpGetSklCsr() != 12)
    return;
  if (!wk->noSklHelp)
  {
    _get_Instance();
    v13 = sdatSkillHelp(setSkill, 1);
    ButtonLineHelpDispSet(1);
    ButtonLineHelpTextSet(v13, 0, 1, 0xA09DC380, 1);
  }
}

// 0x218e3a0
bool CmpStatusCheckSklSet(tagCMP_STATUS_WORK *wk) {
  s32 SklCsr;
  s32 v5;
  SKLID *haveskill;
  s32 *p_selSkl;
  s32 v10;
  void *sklItemGuages;
  void *v12;
  bool result;

  SklCsr = cmpGetSklCsr();
  if (SklCsr > 11)
    return 0;
  v5 = SklCsr;
  if (IndexOf_Int32Enum_(g_aOmoide, setSkill) == -1)
  {
    if (wk->rsvCsr != -1)
      return 0;
    haveskill = wk->unit->haveskill;
    p_selSkl = &wk->selSkl;
  }
  else
  {
    haveskill = wk->unit->aOmoideSkill;
    p_selSkl = &haveskill[v5];
  }
  v10 = *p_selSkl;
  IndexOf_Int32Enum_(haveskill, setSkill);
  sklItemGuages = wk->unit->sklItemGuages;
  v12 = Allocate(System_Collections_Generic_List_SklItemGuage_);
  __ctor_48217552(v12, sklItemGuages);
  result = 0;
  gaugeUp = 0;
  if ((u32)(v10 + 1) >= 2 && v10 != 149)
  {
    if (sklItmRst)
    {
      result = 1;
      oldSkill = v10;
      return result;
    }
    return 0;
  }
  return result;
}

// 0x218e6b0
void CmpStatusChangeSkill(tagCMP_STATUS_WORK *wk) {
  s32 SklCsr;
  sdatUnitWork_t *stock_id;
  sdatUnitWork_t *v6;
  Il2CppClass *klass;
  s32 v11;
  s64 v13;
  s32 *v15;
  s32 v16;
  s32 v17;
  s32 v19;
  s32 devilid;
  s32 v21;
  s32 v23;
  s32 selSkl;
  s32 v26;
  const MethodInfo_256B490 *v27;
  s64 v29;
  void *battleskill;
  s32 v31;
  s32 v32;
  const MethodInfo_256B490 *v33;
  s64 v34;
  void *v35;
  s32 v36;
  s32 v43;

  SklCsr = cmpGetSklCsr();
  stock_id = GBWK->player->stock_id;
  v6 = stock_id[datGetStockDevilIndex(wk->unit->devilid, wk->unit->uniq_code)];
  klass = _get_Instance()[13].klass;
  CmpStatusTempLicenseUpdate(v6);
  v11 = IndexOf_Int32Enum_(g_aOmoide, setSkill);
  if (v11 == -1)
  {
    if ((sklItmRst & 0x10) != 0)
    {
      if (IndexOf_Int32Enum_(v6->aRsvSkl, setSkill) != -1)
      {
        devilid = v6->devilid;
        sBtlGetDevilData(devilid, -1);
        v21 = IndexOf_Int32Enum_(v6->aRsvSkl, setSkill);
        if (v21 != -1)
          v6->aRsvSkl[v21] = 0;
        v6->haveskill[v21 + 1] = setSkill;
        v23 = setSkill;
        cmpAutoBattleSkl(v6, v23);
        goto LABEL_43;
      }
    }
    selSkl = wk->selSkl;
    if (selSkl)
    {
      if (selSkl == setSkill)
        goto LABEL_43;
      v26 = IndexOf_Int32Enum_(v6->haveskill, selSkl);
      v27 = Method_System_Array_IndexOf_SKLID___;
      v29 = (s64)v6->haveskill + 4 * v26;
      battleskill = v6->battleskill;
      *(u32 *)(v29 + 32) = setSkill;
      v31 = IndexOf_Int32Enum_(battleskill, oldSkill, v27);
      if (v31 == -1)
        goto LABEL_43;
    }
    else
    {
      v32 = datSklItmDrawMaxCnt(v6);
      v33 = Method_System_Array_IndexOf_SKLID___;
      v34 = (s64)v6->haveskill + 4 * v32;
      v35 = v6->battleskill;
      *(u32 *)(v34 + 32) = setSkill;
      v31 = IndexOf_Int32Enum_(v35, 0, v33);
      if (v31 == -1)
        goto LABEL_43;
    }
    v6->battleskill[v31] = setSkill;
LABEL_43:
    v36 = setSkill;
    datCombiSkilAutoSet(v6, v36);
    goto LABEL_46;
  }
  if ((sklItmRst & 0x40) != 0)
    goto LABEL_46;
  v13 = (s64)v6->aOmoideSkill + 4 * SklCsr;
  v16 = *(u32 *)(v13 + 32);
  v15 = (v13 + 32);
  v17 = setSkill;
  if (v16 != v17)
  {
    *v15 = v17;
    v19 = setSkill;
    datOmoideSkillSetMaster(v6, v19, 1);
    datCalcNowParam(v6, 0, 0);
  }
LABEL_46:
  ClassCopy(wk->unit, v6, 0);
  ClassCopy(selDrawDevil, v6, 0);
  SetBtlSkill(klass, selDrawDevil, -1, 0);
  SetOmoideSkill(klass, selDrawDevil, -1, 0, 2, 0);
  SetOmoideScrollBar(klass, selDrawDevil, 0, 2, 0);
  if ((tbldata[g_itemNo]->flg & 2) == 0)
    return;
  datAddItem(g_itemNo, -1);
  if (!datCheckItem(g_itemNo, 1))
  {
    v43 = g_itemNo;
    itfMenuDelMenu(g_listPID, v43);
    itfMenuSetFlagMenu(g_listPID, g_itemNo, 2, 0);
  }
}

// 0x218ed20
bool CmpStatusTempLicenseUpdate(sdatUnitWork_t *_unit) {
  CmpStatusItmSklSet **v2;
  void *sklItemGuages;
  void *v5;
  sdatUnitWork_t *v8;
  s32 i;
  CmpStatusItmSklSet **v10;
  s32 v11;
  s32 v13;
  s32 klass;
  s32 v15;
  s32 v17;
  Il2CppObject *Item;
  const MethodInfo_2DFC320 *v20;
  struct Project_CmpStatusItmSklSet___c_StaticFields *static_fields;
  void *_9__21_1;
  void *_9__21_0;
  Il2CppObject *v27;
  Il2CppObject *v30;
  struct CmpStatusItmSklSet *v31;
  s32 v32;
  Il2CppObject *v33;
  Il2CppObject *v35;
  bool v36;
  void *v37;
  void *array;

  v2 = &CmpStatusItmSklSet;
  sklItemGuages = unit->sklItemGuages;
  v5 = Allocate(System_Collections_Generic_List_SklItemGuage_);
  __ctor_48217552(v5, sklItemGuages);
  if (IndexOf_Int32Enum_(g_aOmoide, setSkill) == -1)
  {
    v8 = unit;
    array = unit->haveskill;
    if (v5->_size < 1)
      goto LABEL_43;
    goto LABEL_13;
  }
  v8 = unit;
  array = 0;
  if (v5->_size >= 1)
  {
LABEL_13:
    for (i = 0; i < v5->_size; ++i)
    {
      v10 = v2;
      v11 = (*v2)->static_fields->setSkill;
      v13 = IndexOf_Int32Enum_(g_aOmoide, v11);
      klass = _get_Item(v5, i)[1].klass;
      if (v13 == -1)
      {
        if (IndexOf_Int32Enum_(array, klass) != -1)
          goto LABEL_15;
        v17 = _get_Item(v5, i)[1].klass;
        if (IndexOf_Int32Enum_(g_aOmoide, v17) == -1)
          goto LABEL_36;
        goto LABEL_15;
      }
      if (!datOmoideSkillGetMaster(v8, klass))
      {
        v15 = _get_Item(v5, i)[1].klass;
        if (IndexOf_Int32Enum_(g_aOmoide, v15) == -1)
          goto LABEL_15;
LABEL_36:
        Item = _get_Item(v5, i);
        v20 = Method_System_Collections_Generic_List_SklItemGuage__get_Item__;
        LODWORD(Item[1].klass) = 0;
        HIDWORD(_get_Item(v5, i, v20)[1].klass) = 0;
      }
LABEL_15:
      v2 = v10;
    }
  }
LABEL_43:
  if ((sklItmRst & 4) == 0)
  {
    _9__21_1 = __9__21_1;
    if (!_9__21_1)
    {
      v27 = __9;
      _9__21_1 = Allocate(System_Predicate_SklItemGuage_);
      __ctor(_9__21_1, v27, Method_Project_CmpStatusItmSklSet___c__TempLicenseUpdate_b__21_1__, 0);
      __9__21_1 = _9__21_1;
    }
    v30 = _Find(v5, _9__21_1);
    if (!v30)
    {
      LogError("枠がない", 0);
    }
    v31 = (*v2)->static_fields;
    v32 = v31->setSkill;
    v31->rstMesType = 0;
    LODWORD(v30[1].klass) = v32;
    HIDWORD(v30[1].klass) = 1;
    goto LABEL_70;
  }
  _9__21_0 = __9__21_0;
  if (!_9__21_0)
  {
    v33 = __9;
    _9__21_0 = Allocate(System_Predicate_SklItemGuage_);
    __ctor(_9__21_0, v33, Method_Project_CmpStatusItmSklSet___c__TempLicenseUpdate_b__21_0__, 0);
    __9__21_0 = _9__21_0;
  }
  v35 = _Find(v5, _9__21_0);
  if (v35)
  {
    ++HIDWORD(v35[1].klass);
    (*v2)->static_fields->rstMesType = 1;
  }
  else
  {
    LogError("CheckSklSetで判定済みのためこないはず", 0);
  }
LABEL_70:
  v36 = CmpStatusOfficielLicenseCheck(v5, v8);
  if (v36)
    (*v2)->static_fields->rstMesType = 2;
  v37 = _ToArray(v5);
  v8->sklItemGuages = (SklItemGuage *)v37;
  return v36;
}

// 0x218f440
bool CmpStatusOfficielLicenseCheck(void *_list, sdatUnitWork_t *_unit) {
  s32 BookCnt;
  void *_9__22_0;
  Il2CppObject *v9;
  Il2CppObject *v12;
  void *v13;

  BookCnt = CmpStatusGetBookCnt(unit, setSkill);
  _9__22_0 = __9__22_0;
  if (_9__22_0)
  {
    v9 = _Find(list, _9__22_0);
    if (v9)
      goto LABEL_6;
LABEL_12:
    LogError("スキルが登録されていない", 0);
    return 0;
  }
  v12 = __9;
  v13 = Allocate(System_Predicate_SklItemGuage_);
  __ctor(v13, v12, Method_Project_CmpStatusItmSklSet___c__OfficielLicenseCheck_b__22_0__, 0);
  __9__22_0 = v13;
  v9 = _Find(list, v13);
  if (!v9)
    goto LABEL_12;
LABEL_6:
  if (SHIDWORD(v9[1].klass) >= BookCnt)
  {
    CmpStatusSetOfficialSkl(unit, setSkill);
    return 1;
  }
  return 0;
}

// 0x218fb20
bool CmpStatusSetOfficialSkl(sdatUnitWork_t *_unit, SKLID _sklID) {
  SklItemGuage **p_sklItemGuages;
  void *sklItemGuages;
  void *v7;
  char v8;
  s32 v9;
  Il2CppObject *Item;
  const MethodInfo_2DFC320 *v11;
  void *v12;

  p_sklItemGuages = &unit->sklItemGuages;
  sklItemGuages = unit->sklItemGuages;
  v7 = Allocate(System_Collections_Generic_List_SklItemGuage_);
  __ctor_48217552(v7, sklItemGuages);
  if (v7->_size < 1)
  {
    v8 = 0;
  }
  else
  {
    v8 = 0;
    v9 = 0;
    do
    {
      if (LODWORD(_get_Item(v7, v9)[1].klass) == sklID)
      {
        Item = _get_Item(v7, v9);
        v11 = Method_System_Collections_Generic_List_SklItemGuage__get_Item__;
        LODWORD(Item[1].klass) = 0;
        v8 = 1;
        HIDWORD(_get_Item(v7, v9, v11)[1].klass) = 0;
      }
      ++v9;
    }
    while (v9 < v7->_size);
  }
  v12 = _ToArray(v7);
  *p_sklItemGuages = (SklItemGuage *)v12;
  return v8 & 1;
}

// 0x218f630
s32 CmpStatusGetBookCnt(sdatUnitWork_t *_unit, SKLID _sklID) {
  s32 devilid;
  s32 kuda_id;
  SklItemCoefficient_t *TblDateDvl;
  s32 v10;
  SklItemCoefficient_t *v11;
  CmpSklItem_t *TblDateSkillId;
  u32 v15;
  signed s32 v16;
  s64 v17;
  s64 v18;
  s64 v19;
  u32 attr;
  s32 v22;
  DEVILDATA_WORK *DevilFormat;
  s64 v24;
  bool v25;
  f32 v26;
  s32 v27;

  devilid = unit->devilid;
  kuda_id = sBtlGetDevilData(devilid, -1)->kuda_id;
  TblDateDvl = GetTblDateDvl(sklItmCoefficientTbl, unit->devilid, 0);
  if ((u32)(sklID + 1) < 2)
    return 0;
  v11 = TblDateDvl;
  if (IndexOf_Int32Enum_(g_aOmoide, sklID) != -1)
  {
LABEL_19:
    TblDateSkillId = GetTblDateSkillId(sklItemCntTbl, sklID, 0);
    goto LABEL_22;
  }
  if (datCheckSkillType(sklID) == 2)
    goto LABEL_19;
  attr = tbldata[sklID]->attr;
  TblDateSkillId = GetTblDateAttrb(sklItemCntTbl, attr, sklID, 0);
  v22 = unit->devilid;
  DevilFormat = datGetDevilFormat(v22);
  v10 = 1;
  if (IndexOf_Int32Enum__39237408(DevilFormat->haveskill, sklID, 1) == -1)
  {
LABEL_22:
    if (TblDateSkillId)
    {
      v15 = kuda_id - 1;
      if ((u32)(kuda_id - 1) >= 7)
        v15 = 7;
      v10 = TblDateSkillId->param[v15];
      if (!v11)
        return v10;
    }
    else
    {
      v10 = 0;
      if (!v11)
        return v10;
    }
LABEL_33:
    v16 = tbldata[sklID]->attr;
    if (v16 <= 16)
    {
      v18 = 10;
      if (v16 == 16)
        v18 = 2;
      v19 = 10;
      if (v16 == 8)
        v18 = 1;
      if (v16 == 4)
        v19 = 0;
      if (v16 == 1)
        v19 = 4;
      if (v16 <= 4)
        v17 = v19;
      else
        v17 = v18;
    }
    else if ((u32)v16 <= 0x40)
    {
      v24 = 10;
      if (v16 == 64)
        v24 = 5;
      v25 = v16 == 32;
      v17 = 3;
      if (!v25)
        v17 = v24;
    }
    else
    {
      switch (v16)
      {
        case 128:
          v17 = 6;
          break;
        case 256:
          v17 = 7;
          break;
        case 512:
          v17 = 8;
          if ((tbldata[sklID]->flg & 4) == 0)
            v17 = 9;
          break;
        default:
          v17 = 10;
          break;
      }
    }
    v26 = v11->coefficient[v17] * (f32)v10;
    v27 = (s32)v26;
    if ((s32)v26 <= 1)
      v27 = 1;
    if (v26 == INFINITY)
      return 1;
    else
      return v27;
    goto LABEL_33;
  }
  return v10;
}

// 0x218fc90
bool CmpStatusChkUseAutoCsr(void) {
  s32 v4;
  s32 v7;

  v4 = IndexOf_Int32Enum_(g_aOmoide, setSkill);
  if (v4 == -1)
  {
    if ((sklItmRst & 0x10) != 0)
      return 1;
    if ((sklItmRst & 4) != 0)
      return 1;
    if ((sklItmRst & 0x80) != 0)
      return 1;
    return 0;
  }
  v7 = sklItmRst;
  if ((v7 & 8) == 0)
    return 1;
  if ((v7 & 4) != 0)
    return 1;
  return (v7 & 0x40) != 0;
}

// 0x218fec0
s32 CmpStatusGetNowBookCnt(sdatUnitWork_t *_unit, SKLID _sklID) {
  void *v5;
  void *sklItemGuages;
  void *v8;
  void *v9;
  Il2CppObject *v10;

  v5 = Allocate(Project_CmpStatusItmSklSet___c__DisplayClass26_0);
  v5->_sklID = sklID;
  sklItemGuages = unit->sklItemGuages;
  v8 = Allocate(System_Collections_Generic_List_SklItemGuage_);
  __ctor_48217552(v8, sklItemGuages);
  v9 = Allocate(System_Predicate_SklItemGuage_);
  __ctor(v9, v5, Method_Project_CmpStatusItmSklSet___c__DisplayClass26_0__GetNowBookCnt_b__0__, 0);
  v10 = _Find(v8, v9);
  if (v10)
    return HIDWORD(v10[1].klass);
  else
    return -1;
}

// 0x2190010
void CmpStatusSklItemSequence(tagCMP_STATUS_WORK *wk) {
  CmpSklItemConversionTbl_Tbl *Item;
  s32 v9;
  s8 v13;
  s32 SklCsr;
  _BOOL8 v16;
  s64 flags;
  s32 v19;
  s32 v25;
  s32 v27;
  char *v29;
  char *v30;
  s32 v32;
  s32 v33;
  s32 v34;
  s32 v36;
  s32 sklID;
  char *v39;
  char *v40;
  s32 v42;
  s32 v43;
  s16 v44;
  s32 v47;
  char *v48;
  char *v51;
  s32 v53;
  s32 count;

  switch (wk->step)
  {
    case 0:
      if ((wk->flags & 0x400000) == 0)
        return;
      setSkill = 0;
      if (get_Item(sklItemConvTbl, g_itemNo, 0))
      {
        Item = get_Item(sklItemConvTbl, g_itemNo, 0);
        setSkill = Item->sklID;
        oldSklCsr = 0;
        goto LABEL_12;
      }
      else
      {
        oldSklCsr = 0;
        goto LABEL_12;
      }
LABEL_12:
      cmpCallStart(wk);
      cmpClearDat();
      v9 = CmpStatusChkUseSklItem(wk->unit, setSkill);
      *((u32 *)*((const MethodInfo *)cmpItem + 2).virtualMethodPointer + 46) = v9;
      if (!CmpStatusChkUseAutoCsr())
      {
        if (OmoideSklCheck(setSkill))
        {
          v13 = 2;
          goto LABEL_122;
        }
      }
      wk->noSklHelp = 1;
      goto LABEL_96;
    case 2:
      fclStart1(17, 0);
      wk->step = 3;
      return;
    case 3:
      if (Update())
        return;
LABEL_96:
      v13 = 4;
      wk->count = 0;
      goto LABEL_122;
    case 4:
      SklCsr = cmpGetSklCsr();
      oldSklCsr = SklCsr;
      autoCsr = 0;
      v16 = CHECK_TRIG(4097, 1);
      if (v16)
      {
        if (wk->count < 4)
          return;
        flags = wk->flags;
        if ((flags & 0x4000000) == 0)
        {
          wk->flags = flags | 0x4000000;
          SE(1);
        }
      }
      if ((wk->flags & 0x4000000) != 0)
      {
        wk->count = 0;
        cmpCallEnd(wk);
        goto LABEL_119;
      }
      if (CmpStatusChkUseAutoCsr())
      {
        CmpStatusAutoSklSet(wk);
        autoCsr = 1;
        wk->step = 5;
      }
      else
      {
        CmpStatusSklSet(wk);
        autoCsr = 0;
      }
      count = wk->count;
      if (count >= 4)
        v44 = 4;
      else
        v44 = count + 1;
LABEL_83:
      wk->count = v44;
      return;
    case 5:
      v19 = setSkill;
      if (IndexOf_Int32Enum_(g_aOmoide, v19) != -1)
        wk->noSklHelp = 1;
      Reset(0);
      if ((sklItmRst & 4) == 0)
      {
        if ((sklItmRst & 8) == 0)
        {
          v25 = setSkill;
          if (IndexOf_Int32Enum_(g_aOmoide, v25) != -1)
            goto LABEL_89;
        }
        v27 = sklItmRst;
        if ((v27 & 0x10) == 0)
        {
          v27 = sklItmRst;
          if ((v27 & 0x80) == 0)
          {
            v29 = sdatSkillName(oldSkill);
            fclSetMessageVar(0, v29);
            v30 = sdatSkillName(setSkill);
            fclSetMessageVar(1, v30);
            fclSetMessageInvalid(1);
            SetMessagePos(1u);
            v32 = setSkill;
            if (OmoideSklCheck(v32))
              v33 = 19;
            else
              v33 = 18;
            fclStart2(v33, 0, 0);
LABEL_94:
            fclSetSelCancelPos(1);
            goto LABEL_111;
          }
        }
LABEL_89:
        v47 = setSkill;
        v48 = sdatSkillName(v47);
        fclSetMessageVar(0, v48);
        fclSetMessageVar(1, 0);
        fclSetMessageInvalid(1);
        SetMessagePos(1u);
        fclStart2(21, 0, 0);
        goto LABEL_94;
      }
      v51 = sdatItemName(g_itemNo);
      fclSetMessageVar(0, v51);
      fclSetMessageVar(1, 0);
      fclSetMessageInvalid(1);
      SetMessagePos(1u);
      fclStart2(20, 0, 0);
      fclSetSelCancelPos(1);
      SetMessagePos(1u);
LABEL_111:
      v13 = 6;
LABEL_122:
      wk->step = v13;
      return;
    case 6:
      v34 = Update();
      if (v34 != 1)
      {
        if (!v34)
        {
          CmpStatusChangeSkill(wk);
          wk->count = 30;
          wk->step = 7;
          if (rstMesType == 2)
            v36 = 47;
          else
            v36 = 46;
          SE(v36);
        }
        return;
      }
      autoCsr = 0;
      v53 = sklItmRst;
      if ((v53 & 8) == 0)
        goto LABEL_119;
      v53 = sklItmRst;
      if ((v53 & 0x10) != 0)
      {
LABEL_119:
        v13 = 10;
      }
      else
      {
        v13 = 4;
        wk->count = 0;
        wk->noSklHelp = 0;
      }
      goto LABEL_122;
    case 7:
      wk->modeSq = 0;
      sklID = get_Item(sklItemConvTbl, g_itemNo, 0)->sklID;
      v39 = sdatSkillName(sklID);
      fclSetMessageVar(0, v39);
      v40 = sdatDevilName(wk->unit->devilid, 0);
      fclSetMessageVar(1, v40);
      fclSetMessageInvalid(1);
      if (rstMesType)
      {
        if (rstMesType != 2)
        {
LABEL_79:
          v13 = 9;
          goto LABEL_122;
        }
        v42 = 23;
      }
      else
      {
        v42 = 22;
      }
      fclStart1(v42, 0);
      v13 = 8;
      goto LABEL_122;
    case 8:
      if (!Update())
        goto LABEL_79;
      return;
    case 9:
      autoCsr = 0;
      v43 = wk->count;
      if (v43 <= 0)
      {
        LOWORD(v43) = 0;
        wk->step = 10;
      }
      v44 = v43 - 1;
      goto LABEL_83;
    case 0xA:
      cmpUpdateEnableUseCharUnit(g_itemNo);
      wk->count = 0;
      wk->noSklHelp = 0;
      wk->seqtype = 0;
      wk->step = 0;
      wk->mode = 8;
      cmpFuncEnd(wk);
      Reset(0);
      return;
    default:
      return;
  }
}

// 0x2190a90
void CmpStatusDraw(tagCMP_STATUS_WORK *_wk) {
  Il2CppObject *Instance;
  s32 step;
  Il2CppClass *klass;
  bool v6;
  s32 v7;
  u32 v8;
  u32 v9;
  s32 v12;
  Il2CppObject *v14;

  Instance = _get_Instance();
  step = wk->step;
  klass = Instance[10].klass;
  if (step == 10)
  {
    (*(klass->_1.image + 79))(Instance[10].klass, 0, *((u64 *)klass->_1.image + 80));
    (*(klass->_1.image + 69))(klass, 0, *((u64 *)klass->_1.image + 70));
    goto LABEL_15;
  }
  if (step == 6)
  {
    (*(klass->_1.image + 69))(Instance[10].klass, 0, *((u64 *)klass->_1.image + 70));
    (*(klass->_1.image + 79))(klass, 0, *((u64 *)klass->_1.image + 80));
LABEL_15:
    if (!wk->noSklHelp)
      goto LABEL_34;
LABEL_16:
    v12 = IndexOf_Int32Enum_(g_aOmoide, setSkill);
    if (v12 == -1)
    {
      ButtonLineHelpTextSet("CMP_HELP_L0027", 0, 1, 0xA09DC380, 1);
    }
    else
    {
      ButtonLineHelpDispSet(0);
    }
    goto LABEL_34;
  }
  if (step != 4)
    goto LABEL_15;
  (*(klass->_1.image + 69))(Instance[10].klass, 1, *((u64 *)klass->_1.image + 70));
  (*(klass->_1.image + 79))(klass, 1, *((u64 *)klass->_1.image + 80));
  v6 = cmpGetSklCsr() == 12;
  v7 = setSkill;
  if (v6)
  {
    if (!v8)
    v9 = 1692838528;
  }
  else
  {
    if (!v8)
    v9 = -1600273536;
  }
  cmpDrawSkillNameExUnity(v7, 12, v9, 0, 0, 0);
  if (wk->noSklHelp)
    goto LABEL_16;
LABEL_34:
  v14 = _get_Instance();
  StatusUiDraw(v14, 2);
}
