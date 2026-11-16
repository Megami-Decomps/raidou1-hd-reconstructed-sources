#include "types.h"
#include "dds3basic.h"
#include "dds3objectbase.h"
#include "mdl.h"
#include "sbtl.h"
#include "sbtlcalc.h"
#include "sbtlcmbskl.h"
#include "sbtlmain.h"
#include "sbtlshadow.h"
#include "sdf_vu0.h"

// 0x205f530
void sBtlSetCmbBfrPos(void) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  struct sdfVector4_t pos;
  struct sdfVector4_t v8;

  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (pUnit)
    {
      pos = pUnit->pos;
      pUnit->bOldDispOff = (pUnit->vstatus & 0x1000) != 0;
      v8 = pos;
      goto LABEL_15;
LABEL_16:
      vct_A = v8;
      goto LABEL_17;
LABEL_15:
      goto LABEL_16;
LABEL_17:
      pUnit->vPosBfrCmb = vct_A;
      continue;
    }
  }
}

// 0x205f700
void sBtlSetPosCmbBfrPos(void) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  struct sdfVector4_t vPosBfrCmb;

  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (pUnit)
    {
      if (pUnit->bOldDispOff)
      {
        vPosBfrCmb = pUnit->vPosBfrCmb;
        goto LABEL_15;
LABEL_16:
        goto LABEL_17;
LABEL_18:
      }
      else
      {
        pUnit->vstatus &= ~0x1000u;
        vPosBfrCmb = pUnit->vPosBfrCmb;
LABEL_15:
        goto LABEL_16;
LABEL_17:
        vct_A = vPosBfrCmb;
        goto LABEL_18;
      }
      pUnit->pos = vct_A;
      continue;
    }
  }
}

// 0x205f8f0
void sBtlSetDrawChar(eCmbSklDraw flg) {
  SBTLUNIT_WORK *PChara;
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  dds3ModelHandle_t *hModel;
  s32 ListID;
  s32 *aTateHitID;
  dds3ModelHandle_t *v15;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  dds3ModelHandle_t *v21;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v23;
  sdatUnitWork_t *para;
  u32 BadStatus;
  dds3ModelHandle_t *v27;
  SBTLUNIT_WORK *v28;
  SBTLUNIT_WORK *v29;
  sdatUnitWork_t *v30;
  u32 v31;
  dds3ModelHandle_t *v33;
  sdfVector4_t v34;

  PChara = sBtlGetPChara();
  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if (pUnit->bOldDispOff)
      goto LABEL_18;
    hModel = pUnit->hModel;
    pUnit->vstatus &= ~0x1000u;
    mdlShow(hModel);
    if ((pUnit->actwk->status & 0xFFFFFFFE) == 0xA)
    {
      dds3ObjectBaseOffFlag(&pUnit->pBasic, 0x400u);
LABEL_18:
      if ((pUnit->side & 2) == 0)
        continue;
      goto LABEL_19;
    }
    sBtlDrawShadow(pUnit);
    if ((pUnit->side & 2) == 0)
      continue;
LABEL_19:
    ListID = pUnit->ListID;
    aTateHitID = wk->aTateHitID;
    if (aTateHitID[0] == ListID || aTateHitID[1] == ListID || aTateHitID[2] == ListID || aTateHitID[3] == ListID || aTateHitID[4] == ListID || aTateHitID[5] == ListID || aTateHitID[6] == ListID || aTateHitID[7] == ListID || aTateHitID[8] == ListID || aTateHitID[9] == ListID || aTateHitID[10] == ListID || aTateHitID[11] == ListID || aTateHitID[12] == ListID || aTateHitID[13] == ListID || aTateHitID[14] == ListID)
    {
      goto LABEL_90;
    }
    goto LABEL_9000;
    if (wk->aTateHitID[14] == ListID)
    {
LABEL_90:
      if ((flg & 0x40000000) == 0)
        goto LABEL_91;
      goto LABEL_94;
    }
    ListID = pUnit->ListID;
    aTateHitID = wk->aTateHitID;
LABEL_9000:
    if (aTateHitID[15] == ListID)
      goto LABEL_90;
    if ((flg & 0x20000000) == 0)
    {
LABEL_91:
      v15 = pUnit->hModel;
      pUnit->vstatus |= 0x1000u;
      mdlHide(v15);
      dds3ObjectBaseOffFlag(&pUnit->pBasic, 0x400u);
    }
LABEL_94:
    x = pUnit->pos.x;
    y = pUnit->pos.y;
    z = pUnit->pos.z;
    w = pUnit->pos.w;
    v34.x = x;
    v34.y = y;
    v34.z = z;
    v34.w = w;
    dds3SetPosPoseSet(&pUnit->pBasic, v34);
  }
  if ((flg & 0x80000000) == 0)
  {
    v21 = PChara->hModel;
    PChara->vstatus |= 0x1000u;
    mdlHide(v21);
    dds3ObjectBaseOffFlag(&PChara->pBasic, 0x400u);
  }
  Nakama = sBtlGetNakama(0);
  if (Nakama)
  {
    v23 = Nakama;
    para = Nakama->para;
    BadStatus = sBtlGetBadStatus(para);
    if ((flg & 0x10000000) != 0)
      goto LABEL_116;
    if ((flg & 0x4000000) == 0 || BadStatus == 12 || BadStatus == 6 || BadStatus == 8 || BadStatus == 7 || (v23->hstatus & 0x10) != 0)
    {
      v27 = v23->hModel;
      v23->vstatus |= 0x1000u;
      mdlHide(v27);
      dds3ObjectBaseOffFlag(&v23->pBasic, 0x400u);
    }
  }
LABEL_116:
  v28 = sBtlGetNakama(1);
  if (v28)
  {
    v29 = v28;
    v30 = v28->para;
    v31 = sBtlGetBadStatus(v30);
    if ((flg & 0x8000000) != 0)
      return;
    if ((flg & 0x2000000) == 0 || v31 == 12 || v31 == 6 || v31 == 8 || v31 == 7 || (v29->hstatus & 0x10) != 0)
    {
      v33 = v29->hModel;
      v29->vstatus |= 0x1000u;
      mdlHide(v33);
      dds3ObjectBaseOffFlag(&v29->pBasic, 0x400u);
    }
  }
}
