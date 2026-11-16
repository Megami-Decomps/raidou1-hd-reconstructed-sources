#include "types.h"
#include "cmpmain.h"
#include "cmpmodel.h"
#include "dat.h"
#include "dds3_pad.h"
#include "dds3basic.h"
#include "dds3kernelcore.h"
#include "dds3objectbase.h"
#include "dds3scenebasic.h"
#include "dds3worldbasic.h"
#include "evt.h"
#include "evtbit.h"
#include "evtmoon.h"
#include "fclmisc.h"
#include "fclmsg.h"
#include "fld.h"
#include "fldcommand.h"
#include "gohinit.h"
#include "itf.h"
#include "localize.h"
#include "quest.h"
#include "rstgrowth.h"
#include "sbtlencount.h"
#include "sbtlitem.h"
#include "sbtlsub.h"
#include "scr.h"
#include "sdat.h"
#include "sdf_vu0.h"
#include "sdfmem.h"
#include "slmain.h"
#include "sndat3.h"

#define REPORT_NORMAL_CHECK 0
#define REPORT_NORMAL_INIT 1
#define REPORT_NORMAL_EFFECT 2
#define REPORT_NORMAL_MSG_SET 3
#define REPORT_SPECIAL_CHECK 4
#define REPORT_SPECIAL_INIT 5
#define REPORT_SPECIAL_EFFECT 6
#define REPORT_SPECIAL_MSG_SET 7
#define REPORT_MSG_WAIT 8
#define REPORT_MSG_CLS 9
#define REPORT_ZENIGET_CHK 10
#define REPORT_ZENIGET_MSG 11
#define REPORT_HIROEMON_CHK 12
#define REPORT_HIROEMON_MSG 13
#define REPORT_GIFT_CHK 14
#define REPORT_GIFT_MSG 15
#define REPORT_TAKUMI_CHK 16
#define REPORT_TAKUMI_MSG 17
#define REPORT_LIMITOVER_CHK 18
#define REPORT_LIMITOVER_MSG 19
#define REPORT_END 20
#define REPORT_SUB_TAKUMI_MOT 21
#define REPORT_GOH_DVLSET1 22
#define REPORT_GOH_DVLSET2 23
#define REPORT_GOH_MSG_SET 24
#define REPORT_GOH_GET_MSG_SET 25
#define REPORT_GOH_SET_REP 26
#define msg_report_talk 60
#define msg_report_zeniget1 61
#define msg_report_zeniget2 62
#define msg_report_hiroemon1 63
#define msg_report_hiroemon2 64
#define msg_report_gift1 65
#define msg_report_gift2 66
#define msg_report_limitover 67
#define msg_report_takumi 68
#define devil_report_Goh 69
#define devil_report_GohGet 70
#define SKIP_WAIT 1

typedef struct SB_RNDENC_DEVILINFO SB_RNDENC_DEVILINFO;
typedef struct sdatUnitWork_t sdatUnitWork_t;
typedef struct tagRST_GROWTH_WORK tagRST_GROWTH_WORK;

s32 jimusyo_return_yen[50];
static s32 devilbox_item_num;
static s32 MAP_EX_kaifuku_yen;
static s32 *MAP_EX_buff;
static SB_RNDENC_DEVILINFO *MAP_EX_devilInfo;
sdfVector4_t map_cut_over2_cpos;
sdfVector4_t map_cut_over2_tpos;
static s32 save_stat;
static void *DevilReportStok_Zeniget;
static void *DevilReportStok_Hiroemon;
static void *DevilReportStok_Gift;
static void *DevilReportStok_Takumi;
static void *DevilReportStok_Erase;
bool Report_LimitOver;
tagRST_GROWTH_WORK *talk_wk;
static sdatUnitWork_t *reportWork;
bool repeat;
static s32 scrStep;
static s32 skipWait;
static s32 actWinPhase;

bool SetPadEnable(bool a_bFlag);

// macros
// 0x1b63a70: s32 ACT_WIN_DSP(void)
static inline s32 ACT_WIN_DSP(void) {
  scrSetIntReturnValue(0);
  return 1;
}

// 0x1b63ad0: s32 DIR_HIT_CNTR(void)
static inline s32 DIR_HIT_CNTR(void) {
  scrSetIntReturnValue(0);
  return 1;
}

// 0x1b63b30: s32 PAD_DISABLE(void)
static inline s32 PAD_DISABLE(void) {
  dds3Basic_t *ActiveScene;

  fldReleaseUnitPad();
  ActiveScene = dds3GetActiveScene();
  if (!dds3SceneBasicGetActiveUnit(ActiveScene))
    return 1;
  SetPadEnable(0);
  return 1;
}

// 0x1b63c70: s32 PAD_ENABLE(void)
static inline s32 PAD_ENABLE(void) {
  dds3Basic_t *ActiveScene;
  dds3Basic_t *basic;

  ActiveScene = dds3GetActiveScene();
  basic = dds3SceneBasicGetActiveUnit(ActiveScene);
  if (!basic)
    return 1;
  dds3ObjectBaseSetPrimaryControl(basic, 0);
  fldPlayerMotReset();
  fldRegistUnitPad();
  SetPadEnable(1);
  mapEffEplAllEnd();
  evtGetUnitHandle2(playerBasic)->Stat = 0;
  return 1;
}

// 0x1b63e20: s32 SET_ALLPANEL(void)
static inline s32 SET_ALLPANEL(void) {
  s32 IntPara;
  GlobalWork_t *v8;

  IntPara = scrGetIntPara(0);
  if (IntPara != 1)
  {
    if (!IntPara)
    {
      fldGb->IfDrawOn = 0;
      evtMoonDisableDraw(1);
    }
    return 1;
  }
  v8 = fldGb;
  v8->IfDrawOn = 1;
  evtMoonEnableDraw();
  return 1;
}

// 0x1b63f90: s32 SET_PROGRESS_MES(void)
static inline s32 SET_PROGRESS_MES(void) {
  s32 IntPara;
  s32 v4;

  IntPara = scrGetIntPara(0);
  if ((u32)(IntPara - 1) > 4)
    return 1;
  v4 = IntPara;
  if (IntPara == 5)
  {
    LOBYTE(mapKudaMskIdx) = 1;
    return 1;
  }
  else if (IntPara == 4)
  {
    LOBYTE(mapKudaMskIdx) = 0;
    return 1;
  }
  else
  {
    mapUI_DispChange(v4);
    return 1;
  }
}

// 0x1b640f0: s32 SEARCH_ID(char **pName)
static inline s32 SEARCH_ID(char **pName) {
  char *v3;
  dds3Basic_t *v4;
  dds3Basic_t *scene;

  scene = dds3GetControlScene();
  v3 = *pName;
  v4 = dds3SceneBasicSearchName(scene, v3);
  if (v4)
    return v4->serialID;
  return -1;
}

// 0x1b645e0: s32 MAP_GET_TAKARA_TBL(void)
static inline s32 MAP_GET_TAKARA_TBL(void) {
  TakaraTbl_t *v2;
  s32 Type;
  s32 mapSummonID;
  s32 kucyo;
  TakaraDevil2Tbl_t *v9;
  TakaraDevil1Tbl_t *v10;
  s32 v11;
  TakaraDevil1Param_t *param;
  TakaraDevil1Param_t *v13;
  s32 Par;
  s64 v15;
  s32 ItemNum;
  TakaraDevil1Param_t *v18;
  TakaraDevil1Param_t *v21;
  s32 v22;
  s32 v23;
  s32 v24;
  s32 v25;
  s32 v26;

  v2 = GetfldItemBox(fldItemBoxTbl, fldGb->nowTakaraTblIdx, 0);
  switch (scrGetIntPara(0))
  {
    case 0:
      Type = v2->_Type;
      goto LABEL_31;
    case 1:
      if (v2->_Type == 1)
      {
        mapSummonID = GBWK->mapSummonID;
        kucyo = sBtlGetDevilData(mapSummonID, -1)->kucyo;
        v9 = GetfldTakaraDevil2(fldTakaraDevil2Tbl, kucyo, 0);
        v10 = GetfldTakaraDevil1(fldTakaraDevil1Tbl, v9->_param, 0);
        v11 = sub_1905740(100, 0);
        param = v10->_param;
        v13 = param[0];
        Par = v13->_Par;
        if (v11 < Par)
        {
          v15 = 0;
          ItemNum = v13->_ItemNum;
          goto LABEL_20;
        }
        v21 = param[1];
        v22 = Par + v21->_Par;
        if (v22 > v11)
        {
          v15 = 1;
          goto LABEL_47;
        }
        v21 = param[2];
        v23 = v22 + v21->_Par;
        if (v23 > v11)
        {
          v15 = 2;
          goto LABEL_47;
        }
        v21 = param[3];
        v24 = v23 + v21->_Par;
        if (v24 > v11)
        {
          v15 = 3;
          goto LABEL_47;
        }
        v21 = param[4];
        v25 = v24 + v21->_Par;
        if (v25 > v11)
        {
          v15 = 4;
          goto LABEL_47;
        }
        v21 = param[5];
        if (v25 + v21->_Par > v11)
        {
          v15 = 5;
LABEL_47:
          ItemNum = v21->_ItemNum;
LABEL_20:
          v18 = param[v15];
          devilbox_item_num = ItemNum;
          Type = v18->_ItemID;
          goto LABEL_31;
        }
        v26 = v13->_ItemNum;
        v13 = v10->_param[0];
        devilbox_item_num = v26;
        Type = v13->_ItemID;
        goto LABEL_31;
      }
      else
      {
        Type = v2->_ItemID;
        goto LABEL_31;
      }
LABEL_30:
LABEL_31:
      scrSetIntReturnValue(Type);
      return 1;
    case 2:
      if (v2->_Type == 1)
      {
        Type = devilbox_item_num;
        goto LABEL_31;
      }
      else
      {
        Type = v2->_ItemNum;
        goto LABEL_31;
      }
      goto LABEL_30;
    case 3:
      Type = v2->_Trap;
      goto LABEL_31;
    case 4:
      Type = v2->_Param;
      goto LABEL_31;
    default:
      return 1;
  }
}

// 0x1b64990: s32 MAP_SET_TAKARA_OPEN(void)
static inline s32 MAP_SET_TAKARA_OPEN(void) {
  mapTakaraOpen(fldGb->nowTakaraTblIdx);
  return 1;
}

// 0x1b64a00: s32 MAP_CHK_TAKARA_OPEN(void)
static inline s32 MAP_CHK_TAKARA_OPEN(void) {
  s32 v2;

  v2 = mapTakaraChkOpen(fldGb->nowTakaraTblIdx, -1);
  scrSetIntReturnValue(v2 != 0);
  return 1;
}

// 0x1b64ab0: s32 GET_MAP_FIELD_NO(void)
static inline s32 GET_MAP_FIELD_NO(void) {
  s32 fieldID;

  fieldID = fldGb->fieldID;
  scrSetIntReturnValue(fieldID);
  return 1;
}

// 0x1b64b80: s32 GET_MAP_FLOOR_NO(void)
static inline s32 GET_MAP_FLOOR_NO(void) {
  s32 floorID;

  floorID = fldGb->floorID;
  scrSetIntReturnValue(floorID);
  return 1;
}

// 0x1b64c50: s32 MAP_TITLE_START(void)
static inline s32 MAP_TITLE_START(void) {
  s32 IntPara;
  s32 v2;
  s32 v3;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  v3 = scrGetIntPara(2);
  mapTitleStart(IntPara, v2, v3, 1);
  return 1;
}

// 0x1b64d20: s32 MAP_EX(void)
static inline s32 MAP_EX(void) {
  u32 IntPara;
  u32 v5;
  u32 v6;
  u32 ReturnPrice;
  s32 v9;
  GlobalWork_t *v17;
  s32 flag;
  u32 v19;
  s32 floorID;
  s32 v24;
  s32 StockDevilIndex;
  s32 v28;
  u32 v30;
  sdatUnitWork_t *v31;
  _BOOL4 v32;
  s32 v35;
  s32 result;
  sdatUnitWork_t *para;
  s32 BadStatus;
  sdatUnitWork_t *v43;
  s32 v44;
  bool v47;
  u32 v48;
  s32 v49;
  s32 v50;
  s32 SelectID;
  s32 v52;
  bool v53;
  s32 yen;
  f32 v60;
  f32 v61;
  s32 v63;
  s32 v65;
  s32 v67;
  s32 v69;
  u32 v71;
  s32 RndEncMap;
  s32 v91;
  u32 v93;
  void *FldBgNameList;
  s32 v96;
  SB_RNDENC_DEVILINFO *v99;
  s32 v100;
  s32 *devil_id;
  s32 v105;
  s32 v106;
  sdatUnitWork_t *v108;
  s32 v109;
  s32 v110;
  s32 v112;
  s32 v113;
  sdatUnitWork_t *v115;
  s32 v116;
  s32 v117;
  f32 v119;
  s32 v120;
  char v121;
  s32 v124;
  s32 v125;
  bool v130;
  bool v132;
  u32 v133;
  char *label;

  label = 0;
  IntPara = scrGetIntPara(0);
  if (!talk_wk)
    goto LABEL_11;
LABEL_13:
  v5 = IntPara - 1;
  goto LABEL_14;
LABEL_11:
  if (IntPara <= 0x13 && ((1 << IntPara) & 0xC1080) != 0)
    goto LABEL_13;
  scrEventSkipEnd(0, 0);
  v5 = IntPara - 1;
  if (IntPara - 1 > 0x49)
  {
LABEL_21:
    switch (IntPara)
    {
      case 0x85u:
        mapEffEplLoad_LB_HIRO();
        ReturnPrice = 0;
        break;
      case 0x86u:
        ReturnPrice = mapEffEplLoad_LB_HIRO_EndCheck();
        break;
      case 0x87u:
        mapEffEplStart(20, 0.0, -220.0, 2500.0, -100.0, -16.0, 0, -1);
        ReturnPrice = 0;
        break;
      case 0x88u:
        mapEffEplEnd(20);
        ReturnPrice = 0;
        break;
      case 0x89u:
        ReturnPrice = fldGb->ReturnPrice;
        break;
      default:
        goto LABEL_357;
    }
    goto LABEL_358;
  }
LABEL_14:
  v6 = IntPara;
  ReturnPrice = 0;
  switch (v5)
  {
    case 0u:
      awdMenuStart();
      ReturnPrice = 0;
      break;
    case 1u:
      if (!awdMenuCheckWait())
        goto LABEL_357;
      ReturnPrice = 2;
      switch (awdMenuGetSelectID())
      {
        case -1:
          goto LABEL_358;
        case 0:
          ReturnPrice = 1;
          fldGb->PlayerSutaCnt = 120;
          fldJmpBitOn(24, 1);
          v9 = 21;
          goto LABEL_474;
        case 1:
          ReturnPrice = 1;
          fldGb->PlayerSutaCnt = 120;
          fldJmpBitOn(26, 1);
          v9 = 23;
          v124 = 9;
          v125 = 1;
          goto LABEL_481;
        case 2:
          ReturnPrice = 1;
          fldGb->PlayerSutaCnt = 120;
          fldJmpBitOn(28, 1);
          v9 = 22;
          v125 = 0;
          v124 = 6;
          goto LABEL_481;
        case 3:
          ReturnPrice = 1;
          fldGb->PlayerSutaCnt = 120;
          fldJmpBitOn(30, 1);
          v9 = 24;
          goto LABEL_474;
        case 4:
          if (GBWK->GameFileInfo->chapter == 5)
          {
            fldDestBitOn(5, 12);
            goto LABEL_480;
          }
LABEL_480:
          ReturnPrice = 1;
          fldGb->PlayerSutaCnt = 120;
          fldJmpBitOn(32, 1);
          v9 = 27;
          v124 = 10;
          v125 = 0;
LABEL_481:
          mapCallMapNext(v9, v125, v124, &label);
          break;
        case 5:
          fldGb->PlayerSutaCnt = 120;
          v130 = evtBitCheck(195);
          if (v130)
          {
            if (!fldJmpBitChk(69))
            {
              fldJmpBitOff(34);
              fldJmpBitOn(69, 0);
            }
          }
          else
          {
            if (!fldJmpBitChk(34))
            {
              fldJmpBitOn(34, 0);
              fldJmpBitOff(69);
            }
          }
          v132 = evtBitCheck(192);
          if (v132)
          {
            if (!v133)
            v9 = 25;
            ReturnPrice = 1;
            v125 = 2;
          }
          else
          {
            if (!v133)
            v9 = 25;
            ReturnPrice = 1;
LABEL_474:
            v125 = 0;
          }
          v124 = 1;
          goto LABEL_481;
        default:
          goto LABEL_357;
      }
      break;
    case 2u:
    case 3u:
    case 4u:
    case 5u:
    case 8u:
    case 0x19u:
    case 0x1Au:
    case 0x1Bu:
    case 0x1Cu:
    case 0x1Fu:
    case 0x20u:
    case 0x21u:
    case 0x22u:
    case 0x23u:
    case 0x24u:
    case 0x25u:
    case 0x26u:
    case 0x30u:
    case 0x3Bu:
    case 0x3Cu:
    case 0x3Du:
    case 0x3Eu:
    case 0x3Fu:
    case 0x40u:
    case 0x41u:
      break;
    case 6u:
      yen = GetfldHeal(fldHealTbl, fldGb->nowHealTblIdx, 0)->_yen;
      if (evtBitCheck(206))
      {
        v60 = yen;
        v61 = 12.0;
        goto LABEL_378;
      }
      if (evtBitCheck(195))
      {
        v60 = yen;
        v61 = 11.0;
        goto LABEL_378;
      }
      if (evtBitCheck(185))
      {
        v60 = yen;
        v61 = 10.0;
        goto LABEL_378;
      }
      if (evtBitCheck(176))
      {
        v60 = yen;
        v61 = 9.0;
        goto LABEL_378;
      }
      if (evtBitCheck(166))
      {
        v120 = vcvts_n_s32_f32((f32)yen, 3u);
        v119 = (f32)yen * 8.0;
      }
      else
      {
        if (evtBitCheck(160))
        {
          v60 = yen;
          v61 = 7.0;
          goto LABEL_378;
        }
        if (evtBitCheck(145))
        {
          v60 = yen;
          v61 = 6.0;
          goto LABEL_378;
        }
        if (evtBitCheck(131))
        {
          v60 = yen;
          v61 = 5.0;
          goto LABEL_378;
        }
        if (!evtBitCheck(111))
        {
          if (!evtBitCheck(96))
          {
            if (!evtBitCheck(65))
              goto LABEL_383;
            v119 = (f32)yen + (f32)yen;
            goto LABEL_379;
          }
          v60 = yen;
          v61 = 3.0;
LABEL_378:
          v119 = v60 * v61;
LABEL_379:
          v120 = v119;
          goto LABEL_380;
        }
        v120 = vcvts_n_s32_f32((f32)yen, 2u);
        v119 = (f32)yen * 4.0;
      }
LABEL_380:
      if (v119 == INFINITY)
        yen = 0x80000000;
      else
        yen = v120;
LABEL_383:
      v121 = evtBitCheck(3016);
      ReturnPrice = yen << v121;
      MAP_EX_kaifuku_yen = ReturnPrice;
      itfMoneySetDrawOn();
      break;
    case 7u:
      ReturnPrice = fldGb->ReturnPrice;
      fldGb->ReturnMapID = 0;
      fldGb->ReturnPrice = 0;
      break;
    case 9u:
      fldSetExtraCutID(-1, -1);
      if (mapWarpChk_Idx(fldGb->warpExIdx))
      {
        SequenceControl->phase = 37;
        Process_WarpWait = 1;
        Process_WarpIdx = fldGb->warpExIdx;
        mapZoomClear();
        ReturnPrice = 0;
        break;
      }
      return mapWarpGo_Idx(fldGb->warpExIdx);
    case 0xAu:
      itfMoneySetAddMoney(-MAP_EX_kaifuku_yen);
      ReturnPrice = 0;
      break;
    case 0xBu:
      itfMoneySetDrawOff();
      ReturnPrice = 0;
      break;
    case 0xCu:
      v17 = fldGb;
      flag = v17->flag;
      if ((flag & 4) == 0)
        goto LABEL_357;
      v17 = fldGb;
      flag = v17->flag;
      v19 = flag & 0xFFFFFFFB;
      goto LABEL_198;
    case 0xDu:
      v17 = fldGb;
      v63 = v17->flag;
      if ((v63 & 8) == 0)
        goto LABEL_357;
      v17 = fldGb;
      v63 = v17->flag;
      v19 = v63 & 0xFFFFFFF7;
      goto LABEL_198;
    case 0xEu:
      v17 = fldGb;
      v65 = v17->flag;
      if ((v65 & 0x10) == 0)
        goto LABEL_357;
      v17 = fldGb;
      v65 = v17->flag;
      v19 = v65 & 0xFFFFFFEF;
      goto LABEL_198;
    case 0xFu:
      v17 = fldGb;
      v67 = v17->flag;
      if ((v67 & 0x20) == 0)
        goto LABEL_357;
      v17 = fldGb;
      v67 = v17->flag;
      v19 = v67 & 0xFFFFFFDF;
      goto LABEL_198;
    case 0x10u:
      v17 = fldGb;
      v69 = v17->flag;
      if ((v69 & 0x40) == 0)
        goto LABEL_357;
      v17 = fldGb;
      v69 = v17->flag;
      v19 = v69 & 0xFFFFFFBF;
      goto LABEL_198;
    case 0x11u:
      datPartyDevilRecovery(GBWK->mapSummonID);
      ReturnPrice = 0;
      break;
    case 0x12u:
      fldPlayerMotReset();
      if (fldGb->nakamaMode)
      {
        if (!v71)
        mapBadEffFree(1);
        ReturnPrice = 0;
      }
      else
      {
        if (!v71)
        mapBadEffFreeAll();
        ReturnPrice = 0;
      }
      break;
    case 0x13u:
      floorID = fldGb->floorID;
      elvMenuStart(floorID);
      ReturnPrice = 0;
      fldGb->IfDrawOn = 1;
      break;
    case 0x14u:
      if (elvMenuCheckWait())
      {
        ReturnPrice = elvMenuGetSelectID();
        if (ReturnPrice <= 0x62)
        {
          fldGb->ElvSeStopFlag = 1;
          break;
        }
      }
      else
      {
        ReturnPrice = 99;
      }
      fldGb->ElvSeStopFlag = 0;
      break;
    case 0x15u:
      v17 = fldGb;
      v24 = v17->flag;
      if ((v24 & 0x80) == 0)
        goto LABEL_357;
      v17 = fldGb;
      v24 = v17->flag;
      v19 = v24 & 0xFFFFFF7F;
LABEL_198:
      v17->flag = v19;
      ReturnPrice = 1;
      break;
    case 0x16u:
      ReturnPrice = fldGb->GetSkil_Item;
      break;
    case 0x17u:
      ReturnPrice = fldGb->GetSkil_Zeni;
      break;
    case 0x18u:
      StockDevilIndex = datGetStockDevilIndex(GBWK->mapSummonID, GBWK->mapSummonUNIQ);
      if (StockDevilIndex == -1)
        goto LABEL_357;
      v28 = StockDevilIndex;
      v31 = GBWK->player->stock_id[v28];
      v32 = v31->chuusei > 99;
      if (!v30)
      {
        v31 = GBWK->player->stock_id[v28];
      }
      if (100 * v31->now->hp / v31->now->maxhp <= 40)
        ReturnPrice = 2;
      else
        ReturnPrice = v32;
      break;
    case 0x1Du:
      mapEffEplAllEnd();
      ReturnPrice = 0;
      break;
    case 0x1Eu:
      ReturnPrice = 0;
      fldGb->bgm_fadeout_flag = 0;
      break;
    case 0x27u:
      RndEncMap = mapGetRndEncMap(MAP_EX_buff);
      if (!RndEncMap)
        goto LABEL_303;
      goto LABEL_293;
      if (!RndEncMap)
      {
LABEL_303:
        ReturnPrice = 0;
        MAP_EX_devilInfo->num = 0;
        devil_id = MAP_EX_devilInfo->devil_id;
        *(u64 *)devil_id = 0;
        devil_id[2] = 0;
        break;
      }
LABEL_293:
      v93 = RndEncMap;
      FldBgNameList = fldGetFldBgNameList(fldGb->fieldID, fldGb->floorID);
      if (!FldBgNameList || FldBgNameList->_size < 1 || !LODWORD(_get_Item(FldBgNameList, 0)[4].monitor))
      {
        goto LABEL_303;
      }
      v96 = sub_1905740(v93, 0);
      v99 = MAP_EX_devilInfo;
      v100 = MAP_EX_buff[v96];
      sBtlGetDevilInfo(v100, v99);
      ReturnPrice = 0;
      break;
    case 0x28u:
      ReturnPrice = MAP_EX_devilInfo->num;
      break;
    case 0x29u:
      v35 = MAP_EX_devilInfo->devil_id[0];
      goto LABEL_224;
    case 0x2Au:
      ReturnPrice = MAP_EX_devilInfo->devil_id[0];
      break;
    case 0x2Bu:
      v35 = MAP_EX_devilInfo->devil_id[1];
      goto LABEL_224;
    case 0x2Cu:
      ReturnPrice = MAP_EX_devilInfo->devil_id[1];
      break;
    case 0x2Du:
      v35 = MAP_EX_devilInfo->devil_id[2];
LABEL_224:
      ReturnPrice = sub_1B6D720(v35);
      break;
    case 0x2Eu:
      ReturnPrice = MAP_EX_devilInfo->devil_id[2];
      break;
    case 0x2Fu:
      ReturnPrice = mapGetTakaraNum();
      break;
    case 0x31u:
      mapNakamaTakumi_Mot1();
      ReturnPrice = 0;
      break;
    case 0x32u:
      mapNakamaTakumi_Mot2();
      ReturnPrice = 0;
      break;
    case 0x33u:
      mapNakamaTakumi_Mot3();
      ReturnPrice = 0;
      break;
    case 0x34u:
      mapNakamaTakumi_Mot4();
      ReturnPrice = 0;
      break;
    case 0x35u:
      mapNakamaTakumi_FLUSH();
      ReturnPrice = 0;
      break;
    case 0x36u:
      mapNakamaTakumi_VDSE();
      ReturnPrice = 0;
      break;
    case 0x37u:
      if (mapNakamaTakumi_CheckEffStart())
        goto LABEL_357;
      scrSetIntReturnValue(0);
      return 0;
    case 0x38u:
      mapNakamaTakumi_VUSE();
      ReturnPrice = 0;
      break;
    case 0x39u:
      para = GBWK->player->para;
      BadStatus = sdatCalc_GetBadStatus(para);
      if (BadStatus == 10)
      {
        BadStatus = 10;
        goto LABEL_320;
      }
      else
      {
        if (BadStatus != 11)
          goto LABEL_321;
        BadStatus = 11;
        goto LABEL_320;
      }
LABEL_320:
      mapBadEffOffCng(0, BadStatus);
LABEL_321:
      v105 = datGetStockDevilIndex(GBWK->mapSummonID, GBWK->mapSummonUNIQ);
      if (v105 == -1)
        goto LABEL_357;
      v106 = v105;
      v108 = GBWK->player->stock_id[v106];
      v109 = sdatCalc_GetBadStatus(v108);
      if (v109 == 10)
      {
        v110 = 10;
      }
      else
      {
        if (v109 != 11)
          goto LABEL_357;
        v110 = 11;
      }
      mapBadEffOffCng(1, v110);
      ReturnPrice = 0;
      break;
    case 0x3Au:
      v43 = GBWK->player->para;
      v44 = sdatCalc_GetBadStatus(v43);
      if (v44 == 10)
      {
        v44 = 10;
        goto LABEL_334;
      }
      else
      {
        if (v44 != 11)
          goto LABEL_335;
        v44 = 11;
        goto LABEL_334;
      }
LABEL_334:
      mapBadEffLoad(0, v44);
LABEL_335:
      v112 = datGetStockDevilIndex(GBWK->mapSummonID, GBWK->mapSummonUNIQ);
      if (v112 == -1)
        goto LABEL_357;
      v113 = v112;
      v115 = GBWK->player->stock_id[v113];
      v116 = sdatCalc_GetBadStatus(v115);
      if (v116 == 10)
      {
        v117 = 10;
      }
      else
      {
        if (v116 != 11)
          goto LABEL_357;
        v117 = 11;
      }
      mapBadEffLoad(1, v117);
LABEL_357:
      ReturnPrice = 0;
      break;
    case 0x42u:
      savePointMenuProcessStart();
      savePointMenuStart();
      ReturnPrice = 0;
      switch (GBWK->fldSave->tmnlid)
      {
        case 1:
          v49 = 25;
          goto LABEL_459;
        case 3:
          v49 = 37;
          goto LABEL_459;
        case 4:
          v49 = 44;
          goto LABEL_459;
        case 7:
          v49 = 29;
          goto LABEL_459;
        case 0xA:
          v49 = 43;
          goto LABEL_459;
        case 0xB:
          v49 = 27;
          goto LABEL_459;
        case 0xC:
          v49 = 71;
          goto LABEL_459;
        case 0xD:
          v49 = 72;
          goto LABEL_459;
        case 0xE:
          v49 = 73;
          goto LABEL_459;
        case 0xF:
          v49 = 74;
          goto LABEL_459;
        case 0x14:
        case 0x15:
        case 0x16:
          v47 = evtBitCheck(195);
          if (v47)
          {
            if (!v48)
            v49 = 69;
            v50 = 0;
          }
          else
          {
            if (!v48)
            v49 = 35;
LABEL_459:
            v50 = 1;
          }
          fldJmpBitOn(v49, v50);
          ReturnPrice = 0;
          break;
        case 0x17:
          v49 = 31;
          goto LABEL_459;
        case 0x18:
          v49 = 33;
          goto LABEL_459;
        case 0x19:
          v49 = 75;
          goto LABEL_459;
        case 0x1C:
          v49 = 42;
          goto LABEL_459;
        default:
          goto LABEL_358;
      }
      break;
    case 0x43u:
      if (savePointMenuCheckWait())
      {
        SelectID = savePointMenuGetSelectID();
        if (SelectID <= 0x10000)
        {
          if (SelectID == 0x10000)
            ReturnPrice = 0;
          else
            ReturnPrice = 3;
        }
        else
        {
          if (SelectID == 196608)
            v52 = 10;
          else
            v52 = 3;
          if (SelectID == 0x20000)
            ReturnPrice = 1;
          else
            ReturnPrice = v52;
        }
        if (savePointMenuProcessCheck())
        {
          savePointMenuProcessEnd();
        }
      }
      else
      {
        ReturnPrice = 99;
      }
      break;
    case 0x44u:
      *(u16 *)&Story11Extra = 257;
      Story11Cancel = 0;
      Story11Number = -1;
      goto LABEL_245;
    case 0x45u:
      v53 = mapIfMenuTask() == 2;
      if (v53)
      {
        ReturnPrice = Story11Number;
        break;
      }
      if (Story11Cancel)
        goto LABEL_282;
      return 0;
    case 0x46u:
      ReturnPrice = 0;
      *(u16 *)&Story11Extra = 0;
      Story11Cancel = 0;
      Story11Number = -1;
      break;
    case 0x47u:
      QuestDevilNumber = -1;
      *(u32 *)&QuestDevilExtra = 257;
LABEL_245:
      fldProcOnFlag(0x40u);
      result = mapIfMenuTask();
      if (!result)
        return result;
      ReturnPrice = result;
      fldReleaseUnitPad();
      break;
    case 0x48u:
      v53 = mapIfMenuTask() == 2;
      if (v53)
      {
        scrSetIntReturnValue(QuestDevilNumber);
        QuestDevilNumber = -1;
        fldReleaseUnitPad();
        return 1;
      }
      if (!QuestDevilCancel)
        return 0;
LABEL_282:
      v91 = -1;
      goto LABEL_361;
    case 0x49u:
      ReturnPrice = 0;
      *(u64 *)&QuestDevilExtra = 0xFFFFFFFF00000000LL;
      break;
    default:
      IntPara = v6;
      goto LABEL_21;
  }
LABEL_358:
  v91 = ReturnPrice;
LABEL_361:
  scrSetIntReturnValue(v91);
  return 1;
}

// 0x1b66740: s32 FLD_NEKO(void)
#define FLD_NEKO() (1)

// 0x1b66750: s32 MAP_ZOOM(void)
static inline s32 MAP_ZOOM(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  fldBgZoomTest(IntPara);
  return 1;
}

// 0x1b667f0: s32 MAP_ZOOM2(void)
static inline s32 MAP_ZOOM2(void) {
  s32 IntPara;
  s32 v2;
  s32 v3;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  v3 = scrGetIntPara(2);
  fldBgZoomTest2(IntPara, v2, v3);
  return 1;
}

// 0x1b668c0: s32 MAP_NPC_GET_HANDLE(void)
static inline s32 MAP_NPC_GET_HANDLE(void) {
  s32 IntPara;
  u32 serialID;

  IntPara = scrGetIntPara(0);
  if (IntPara)
  {
    serialID = mapObjGetBasic(IntPara)->serialID;
  }
  else
  {
    serialID = fldGb->nowTalkModelID;
  }
  scrSetIntReturnValue(serialID);
  return 1;
}

// 0x1b669b0: s32 MAP_NPC_REFRESH(void)
static inline s32 MAP_NPC_REFRESH(void) {
  mapObjAdd_Cash_Free();
  if (mapNpcTblRefresh_Wait() != -1)
  {
    goto LABEL_5;
  }
  mapNpcTblRefresh();
LABEL_5:
  if (mapNpcTblRefresh_Wait() == 1)
    return 0;
  mapMapObjectRefresh2();
  if (MiniMapUpdateFlag)
    minMapRefresh();
  mapObjOnOff();
  return 1;
}

// 0x1b66cd0: s32 MAP_CUT_OVERSET_COMMON(s32 cutidx, f32 cx, f32 cz, f32 cy, f32 tx, f32 tz, f32 ty)
static inline s32 MAP_CUT_OVERSET_COMMON(s32 cutidx, f32 cx, f32 cz, f32 cy, f32 tx, f32 tz, f32 ty) {
  s32 cut_idx_overlap_CngNow;
  s32 cut_idx_overlap;
  f32 *static_fields;
  s32 v22;
  s32 v23;
  s32 v24;
  s32 v25;

  cut_idx_overlap_CngNow = fldGb->cut_idx_overlap_CngNow;
  if (cut_idx_overlap_CngNow)
    goto LABEL_4;
  cut_idx_overlap = fldGb->cut_idx_overlap;
  fldGb->cut_idx_overlap = cutidx;
  cutidx = fldGb->cut_idx_overlap;
  fldGb->cut_idx_old = 0;
  static_fields[9] = cy;
  static_fields[10] = cz;
  static_fields[8] = cx;
  static_fields[13] = ty;
  static_fields[14] = tz;
  static_fields[12] = tx;
  if (cutidx)
  {
    if (fldGb->cut_idx != cutidx)
      goto LABEL_25;
  }
  else if (cut_idx_overlap)
  {
    if (fldGb->cut_idx != cut_idx_overlap)
      goto LABEL_25;
    goto LABEL_9000;
    if (fldGb->cut_idx != cut_idx_overlap)
    {
LABEL_25:
      v24 = 0;
      v25 = 0;
      v22 = 1;
      v24 = v25;
      v23 = v22;
      goto LABEL_28;
    }
LABEL_9000:
  }
  return 1;
LABEL_4:
  if (cut_idx_overlap_CngNow == 1)
    return 0;
  if (cut_idx_overlap_CngNow != 2)
    return 0;
  v22 = 0;
  v23 = 0;
  v24 = 1;
LABEL_28:
  fldGb->cut_idx_overlap_CngNow = v23;
  return v24;
}

// 0x1b66f30: s32 MAP_CUT_OVERSET(void)
static inline s32 MAP_CUT_OVERSET(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  return MAP_CUT_OVERSET_COMMON(IntPara, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
}

// 0x1b66fd0: s32 MAP_CUT_OVERSET2(void)
static inline s32 MAP_CUT_OVERSET2(void) {
  s32 IntPara;
  s32 v2;
  s32 v3;
  s32 v4;
  s32 v5;
  s32 v6;
  s32 v8;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  v3 = scrGetIntPara(2);
  v4 = scrGetIntPara(3);
  v5 = scrGetIntPara(4);
  v6 = scrGetIntPara(5);
  v8 = scrGetIntPara(6);
  return MAP_CUT_OVERSET_COMMON(IntPara, (f32)v2, (f32)v3, (f32)v4, (f32)v5, (f32)v6, (f32)v8);
}

// 0x1b670f0: s32 MAP_POINT_GET_HANDLE(void)
static inline s32 MAP_POINT_GET_HANDLE(void) {
  s16 IntPara;
  s32 SerializeID;

  IntPara = scrGetIntPara(0);
  SerializeID = mapObjPointGetSerializeID(IntPara);
  scrSetIntReturnValue(SerializeID);
  return 1;
}

// 0x1b67190: s32 MAP_SUMMON_GET_ID(void)
static inline s32 MAP_SUMMON_GET_ID(void) {
  s32 mapSummonID;

  mapSummonID = GBWK->mapSummonID;
  scrSetIntReturnValue(mapSummonID);
  return 1;
}

// 0x1b67260: s32 MAP_NAKAMA_MODE(void)
static inline s32 MAP_NAKAMA_MODE(void) {
  s32 IntPara;
  GlobalWork_t *fldGb_local;
  GlobalWork_t *v10;
  f32 playerZ;
  GlobalWork_t *v18;

  IntPara = scrGetIntPara(0);
  if (IntPara)
  {
    fldGb_local = fldGb;
    if (fldGb_local->nakamaMode)
    {
LABEL_9:
      mapNakamaWakeUp(0);
      return 1;
    }
    fldGb_local = fldGb;
    *(u64 *)&fldGb_local->nakamaX = *(u64 *)&fldGb_local->playerX;
    playerZ = fldGb_local->playerZ;
    fldGb_local->nakamaMap = fldGb_local->fieldID;
    fldGb_local->nakamaFloor = fldGb_local->floorID;
    fldGb_local->nakamaZ = playerZ;
    fldGb_local->nakamaKakudo = fldGb_local->PlayerKakudoGoal;
    fldGb_local->nakamaMode = 1;
    v18 = fldGb_local;
    fldGb_local->nakamaID = GBWK->mapSummonID;
    *(u64 *)&v18->nakamaRunSpeed = 0x500000005LL;
    GBWK->EventBit[93] |= 0x20000u;
    fldPlayerToNakama(2);
    HIDWORD(QuestIconNowList) = 5;
    SequenceControl->phase = 20;
    goto LABEL_9;
  }
  v10 = fldGb;
  if (!v10->nakamaMode)
    return 1;
  v10->nakamaMode = 0;
  GBWK->EventBit[93] &= ~0x20000u;
  fldNakamaToSummon();
  HIDWORD(QuestIconNowList) = 1;
  if (!summonDvBasic)
  {
    SequenceControl->phase = 19;
    goto LABEL_24;
  }
  mapSummonDvFoceSet(summonDvBasic->poseset->pos.x, summonDvBasic->poseset->pos.y, summonDvBasic->poseset->pos.z);
  SequenceControl->phase = 19;
LABEL_24:
  if (!aiboBasic)
    return 1;
  dds3ObjectBaseOffFlag(aiboBasic, 1u);
  return 1;
}

// 0x1b676b0: s32 MAP_MODEL_LIGHT(void)
static inline s32 MAP_MODEL_LIGHT(void) {
  evtUnitHandle_t *v1;
  s32 IntPara;

  v1 = Allocate(evtUnitHandle_t);
  _ctor(v1, 0);
  IntPara = scrGetIntPara(0);
  evtGetUnitHandle(IntPara)->MapLightUse = 1;
  return 1;
}

// 0x1b67780: s32 MAP_SCROLL(void)
static inline s32 MAP_SCROLL(void) {
  s32 IntPara;
  s32 v2;
  s32 v3;
  s32 CamType;
  f32 v7;
  f32 v8;
  f32 v9;
  s64 r;
  f32 y;
  f32 x;

  x = 0.0;
  y = 0.0;
  r = 0;
  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  v3 = scrGetIntPara(2);
  if (IntPara)
  {
    if (mapObjPointGet(IntPara, &x, &y, (f32 *)&r + 1, &r))
    {
      CamType = fldGetCamType();
      if (CamType)
      {
        ExtraCameraType = 0;
      }
      v7 = x;
      v8 = y;
      v9 = *((f32 *)&r + 1);
      mapBgFScrollOn(v7, v8 - (f32)v2, v9, v3);
    }
  }
  else
  {
    mapBgFScrollOff(v3);
  }
  return 1;
}

// 0x1b67900: s32 MAP_SCROLL_EX(void)
static inline s32 MAP_SCROLL_EX(void) {
  s32 IntPara;
  s32 v2;
  s32 v3;
  s32 CamType;
  f32 v7;
  f32 v8;
  f32 v9;
  s64 r;
  f32 y;
  f32 x;

  x = 0.0;
  y = 0.0;
  r = 0;
  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  v3 = scrGetIntPara(2);
  if (IntPara)
  {
    if (mapObjPointGet(IntPara, &x, &y, (f32 *)&r + 1, &r))
    {
      CamType = fldGetCamType();
      if (CamType)
      {
        ExtraCameraFlag = 0;
      }
      v7 = x;
      v8 = y;
      v9 = *((f32 *)&r + 1);
      mapBgFScrollOn(v7, v8 - (f32)v2, v9, v3);
    }
  }
  else
  {
    mapBgFScrollOff(v3);
    *(u64 *)&ExtraCameraFlag = -1;
  }
  return 1;
}

// 0x1b67a90: s32 FREE_CAMERA_RESET(void)
static inline s32 FREE_CAMERA_RESET(void) {
  ExtraCameraType = -1;
  fldBgTexLogClear();
  return 1;
}

// 0x1b67b00: s32 FIXED_CAMERA_MODE(void)
static inline s32 FIXED_CAMERA_MODE(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  ExtraCameraType = IntPara;
  return 1;
}

// 0x1b67bb0: s32 AUTOMAP_SET(void)
static inline s32 AUTOMAP_SET(void) {
  s32 IntPara;
  s32 v2;
  s32 v3;
  s32 v4;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  v3 = scrGetIntPara(2);
  v4 = scrGetIntPara(3);
  mapAM_MaskSetCurrent(IntPara, v2);
  if (v4 == 1)
  {
    mapAM_MaskOpen_ID(IntPara, v2, v3);
    return 1;
  }
  else
  {
    mapAM_MaskClose_ID(IntPara, v2, v3);
    return 1;
  }
}

// 0x1b67cf0: s32 CTNNPC_SET(void)
static inline s32 CTNNPC_SET(void) {
  s32 IntPara;
  s32 v2;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  if (IntPara)
  {
    if (v2)
    {
      mapCtnColorFadeIn(1);
      return 1;
    }
    else
    {
      mapCtnColorFadeIn(0);
      return 1;
    }
  }
  else if (v2)
  {
    mapCtnColorFadeOut(1);
    return 1;
  }
  else
  {
    mapCtnColorFadeOut(0);
    return 1;
  }
}

// 0x1b67e10: s32 KANKYOSE_SET(void)
static inline s32 KANKYOSE_SET(void) {
  s32 IntPara;
  s32 v2;
  u32 v3;
  s32 v4;
  s32 v7;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  if (!IntPara)
  {
    fldGb->StartKanKyoOff = 1;
    if (v2)
    {
      v7 = 1;
LABEL_23:
      mapSeKankyoFadeOut(v7);
      return 1;
    }
    v7 = 0;
    goto LABEL_23;
  }
  if (v2)
  {
    if (!v3)
    v4 = 1;
  }
  else
  {
    if (!v3)
    v4 = 0;
  }
  mapSeKankyoFadeIn(v4);
  return 1;
}

// 0x1b67f50: s32 FRELDBGM_SET(void)
static inline s32 FRELDBGM_SET(void) {
  s32 IntPara;
  s32 v2;
  s32 BgmId;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  BgmId = mapSoundGetBgmId(IntPara, v2);
  sndBgmLoadId_XF(BgmId);
  sndBgmPlay(BgmId, 0);
  return 1;
}

// 0x1b68050: s32 CALLDEVIL_CLR(void)
static inline s32 CALLDEVIL_CLR(void) {
  *(u64 *)&GBWK->mapSummonID = 0;
  return 1;
}

// 0x1b680c0: s32 SET_TORAIDOU_SEL(void)
static inline s32 SET_TORAIDOU_SEL(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  HIDWORD(mapKudaScript) = IntPara;
  return 1;
}

// 0x1b681b0: s32 CHK_LEVEL_DIFF(void)
static inline s32 CHK_LEVEL_DIFF(void) {
  s32 IntPara;
  s32 level;

  IntPara = scrGetIntPara(0);
  level = GBWK->player->para->level;
  scrSetIntReturnValue(IntPara >= level + 10);
  return 1;
}

// 0x1b68310: s32 SET_DEST_FLAG(void)
static inline s32 SET_DEST_FLAG(void) {
  s32 IntPara;
  s32 v2;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  fldDestBitOn(IntPara, v2);
  mapIfSetDestCheck();
  mapIfDrawDestText();
  minMapRefresh();
  return 1;
}

// 0x1b683e0: s32 SET_DEST_FLAG_NOREFRESH(void)
static inline s32 SET_DEST_FLAG_NOREFRESH(void) {
  s32 IntPara;
  s32 v2;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  fldDestBitOn(IntPara, v2);
  mapIfSetDestCheck();
  mapIfDrawDestText();
  return 1;
}

// 0x1b684a0: s32 CLR_DEST_FLAG(void)
static inline s32 CLR_DEST_FLAG(void) {
  s32 IntPara;
  s32 v2;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  fldDestBitOff(IntPara, v2);
  mapIfSetDestCheck();
  mapIfDrawDestText();
  return 1;
}

// 0x1b68560: s32 SET_JMP_FLAG(void)
static inline s32 SET_JMP_FLAG(void) {
  s32 IntPara;
  s32 v2;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  fldJmpBitOn(IntPara, v2);
  return 1;
}

// 0x1b68610: s32 CLR_JMP_FLAG(void)
static inline s32 CLR_JMP_FLAG(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  fldJmpBitOff(IntPara);
  return 1;
}

// 0x1b686b0: s32 SET_MINIMAP_DISP(void)
static inline s32 SET_MINIMAP_DISP(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  miniMapDispSet(IntPara != 0);
  return 1;
}

// 0x1b68750: s32 SET_STORY_NUMBER(void)
static inline s32 SET_STORY_NUMBER(void) {
  u8 IntPara;
  GameFileInfo_t *GameFileInfo;

  IntPara = scrGetIntPara(0);
  GameFileInfo = GBWK->GameFileInfo;
  GameFileInfo->chapter = IntPara;
  GameFileInfo->TmnlMode = 0;
  return 1;
}

// 0x1b687f0: s32 GET_ENCOUNTTBL(void)
static inline s32 GET_ENCOUNTTBL(void) {
  s32 v4;
  f32 *p_x;
  f32 z;
  f32 x;
  f32 y;
  s32 nowKiretsuIdx;
  s32 v14;
  s32 *p_encID;
  f32 v16;
  dds3Basic_t *pBasic;

  pBasic = playerBasic;
  dds3GetPosPoseSet(pBasic);
  v4 = (u8)byte_5755EF6;
  vct_B = (struct sdfVector4_t)xmmword_3CFD5C0;
  if (v4)
  {
    goto LABEL_11;
  }
  else
  {
LABEL_11:
    goto LABEL_12;
  }
LABEL_12:
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  p_x = &vf00.x;
  z = p_x[6];
  x = p_x[4];
  y = p_x[5];
  nowKiretsuIdx = fldGb->nowKiretsuIdx;
  if ((u32)(nowKiretsuIdx - 50) < 4)
  {
    v14 = dword_3D01640[nowKiretsuIdx - 50];
    goto LABEL_24;
  }
  nowKiretsuIdx = fldGb->nowKiretsuIdx;
  p_encID = &GetSakemeTable(sakemeTbl, nowKiretsuIdx, 0)->_encID;
  v14 = *p_encID;
LABEL_24:
  if (v14 != GetQuestEncountID(6, 1))
  {
    v16 = sqrtf((f32)((f32)(x * x) + (f32)(y * y)) + (f32)(z * z));
    v14 = sBtlRndEncCalcKirestu(v14, v16 + v16);
  }
  scrSetIntReturnValue(v14);
  return 1;
}

// 0x1b68bb0: s32 CALL_ENCOUNTBATTLE(void)
static inline s32 CALL_ENCOUNTBATTLE(void) {
  s32 IntPara;
  s32 RndEnc;

  IntPara = scrGetIntPara(0);
  RndEnc = mapGetRndEnc(fldGb->playerX, fldGb->playerZ);
  fldEncountBattleSet(IntPara, RndEnc, 0, 0, 0, 0);
  fldEncountBattleStart();
  scrAllReleaseScript();
  return 1;
}

// 0x1b68c90: s32 GET_ENCOUNT_LV_AVE(void)
static inline s32 GET_ENCOUNT_LV_AVE(void) {
  s32 IntPara;
  s32 LevelAverage;

  IntPara = scrGetIntPara(0);
  LevelAverage = sBtlGetLevelAverage(IntPara);
  scrSetIntReturnValue(LevelAverage);
  return 1;
}

// 0x1b68d30: s32 AUTOSAVE(void)
static inline s32 AUTOSAVE(void) {
  dds3ProcessFunc_t *p_AutoSaveFunc;
  s32 v5;
  s32 v6;

  if (save_stat != 1)
  {
    if (!save_stat)
    {
      if (chackAutoSave())
      {
        p_AutoSaveFunc = &AutoSaveFunc;
        *p_AutoSaveFunc = 0;
        v5 = 0;
        v6 = 1;
        AutoSaveProc = 0;
        goto LABEL_23;
      }
      return 1;
    }
    return 0;
  }
  if (!slUpdateAutoSave())
    return 0;
  v6 = 0;
  v5 = save_stat;
LABEL_23:
  save_stat = v6;
  return v5;
}

// 0x1b68f30: s32 SUSPENDSAVE(void)
static inline s32 SUSPENDSAVE(void) {
  dds3ProcessFunc_t *p_SuspendFunc;
  s32 result;
  s32 v8;

  if (save_stat != 1)
  {
    if (save_stat)
      return 0;
    p_SuspendFunc = &SuspendFunc;
    *p_SuspendFunc = 0;
    SuspendProc = 0;
    result = 0;
    save_stat = 1;
    return result;
  }
  result = slUpdateSuspend();
  if (result)
  {
    v8 = result;
    save_stat = 0;
    scrSetIntReturnValue(v8);
    SE(26);
    return 1;
  }
  return result;
}

// 0x1b69120: s32 SET_BGMLOAD_MODE(void)
static inline s32 SET_BGMLOAD_MODE(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  fldGb->BgmLoadMode = IntPara;
  return 1;
}

// 0x1b691c0: s32 GET_ZAKURO_NOW(void)
static inline s32 GET_ZAKURO_NOW(void) {
  s32 v2;

  v2 = fldZakuroNowGet();
  scrSetIntReturnValue(v2);
  return 1;
}

// 0x1b69280: s32 SET_ZAKURO_NOW(void)
static inline s32 SET_ZAKURO_NOW(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  fldZakuroNowSet(IntPara);
  return 1;
}

// 0x1b69320: s32 GET_ZAKURO_LOOP(void)
static inline s32 GET_ZAKURO_LOOP(void) {
  s32 v2;

  v2 = fldZakuroCntGet();
  scrSetIntReturnValue(v2);
  return 1;
}

// 0x1b693e0: s32 SET_ZAKURO_LOOP(void)
static inline s32 SET_ZAKURO_LOOP(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  fldZakuroCntSet(IntPara);
  return 1;
}

// 0x1b69480: s32 CHK_ZAKURO_COMP(void)
static inline s32 CHK_ZAKURO_COMP(void) {
  s32 v2;

  v2 = fldZakuroChkComp();
  scrSetIntReturnValue(v2);
  return 1;
}

// 0x1b69540: s32 CLR_ZAKURO_BIT(void)
static inline s32 CLR_ZAKURO_BIT(void) {
  fldZakuroBitClr();
  fldCleKiretsuFlg();
  return 1;
}

// 0x1b695b0: s32 CHK_ZAKURO_REWARD(void)
static inline s32 CHK_ZAKURO_REWARD(void) {
  s32 v2;

  v2 = fldZakuroChkReward();
  scrSetIntReturnValue(v2);
  return 1;
}

// 0x1b69670: s32 GET_ZAKURO_REWARD(void)
static inline s32 GET_ZAKURO_REWARD(void) {
  s32 IntPara;
  s32 v2;
  s32 ZakuroReward;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  ZakuroReward = fldGetZakuroReward(IntPara, v2);
  scrSetIntReturnValue(ZakuroReward);
  return 1;
}

// 0x1b69730: s32 CHK_ZAKURO_REWARD_EVE(void)
static inline s32 CHK_ZAKURO_REWARD_EVE(void) {
  scrSetIntReturnValue(ZakuroRewordEve);
  return 1;
}

// 0x1b697f0: s32 CHK_ZAKURO_REWARD_NOW(void)
static inline s32 CHK_ZAKURO_REWARD_NOW(void) {
  s32 v2;

  v2 = fldZakuroChkRewardNow();
  scrSetIntReturnValue(v2);
  return 1;
}

// 0x1b698b0: s32 HUKIDASHIEND_ON(void)
static inline s32 HUKIDASHIEND_ON(void) {
  s32 IntPara;
  s32 v2;
  s32 v3;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  v3 = scrGetIntPara(2);
  mapHukidashiEndCheck(IntPara, v3, v2);
  return 1;
}

// 0x1b69980: s32 HUKIDASHIEND_OFF(void)
static inline s32 HUKIDASHIEND_OFF(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  mapHukidashiEndOff(IntPara);
  return 1;
}

// 0x1b69a20: s32 SET_DATABUFFER(void)
static inline s32 SET_DATABUFFER(void) {
  s32 IntPara;
  s32 v2;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  fldSetDataBuffer(IntPara, v2);
  return 1;
}

// 0x1b69ad0: s32 DEVIL_REPORT(void)
static inline s32 DEVIL_REPORT(void) {
  u32 IntPara;
  bool v2;
  s32 v4;
  s32 v9;
  Il2CppObject *ProcessData;
  long f64 v12;
  s64 v13;
  sdatUnitWork_t *v16;
  s32 v18;
  void *ReportStok;
  void *v24;
  void *v26;
  s32 size;
  s32 v30;
  s32 result;
  s32 devilid;
  s32 v34;
  s32 v36;
  char *v37;
  void *v39;
  s32 v42;
  s32 v44;
  s32 v45;
  s32 v47;
  char *v48;
  s32 v50;
  bool IsEventSkip;
  s32 v55;
  void *DevilReportStok_Zeniget_local;
  char *v60;
  s32 v62;
  s32 v66;
  Il2CppObject *v67;
  char *v68;
  char *v69;
  char *v70;
  s32 v73;
  Il2CppObject *v74;
  char *v75;
  char *v76;
  char *v77;
  s32 v82;
  char *v83;
  u32 v86;
  s32 v90;
  char *v91;
  Il2CppObject *v94;
  long f64 v95;
  s64 v96;
  s64 v97;
  s64 v98;
  bool v100;
  sdatUnitWork_t *v101;
  Il2CppClass **v104;
  sdatUnitWork_t *v106;
  Il2CppClass **v109;
  sdatUnitWork_t *v111;
  u32 v115;
  tagRST_GROWTH_WORK *v116;
  char *v118;
  char *v120;
  bool v124;
  s32 v125;
  char *v126;
  char *v128;
  s32 v129;
  tagRST_GROWTH_WORK *v132;
  tagCMP_WORK *Work;
  s32 v139;
  char v140;
  s32 data;
  s32 count;
  s32 gold;

  IntPara = scrGetIntPara(0);
  gold = 0;
  count = 0;
  v2 = cmpProcessCheck();
  v4 = gohProcessCheck();
  if (IntPara > 0x1A)
  {
LABEL_196:
    v18 = 0;
    goto LABEL_290;
  }
  v9 = v4;
  switch (IntPara)
  {
    case 0u:
      if (reportWork)
      {
        goto LABEL_27;
      }
      v104 = &GBWK->player->stock_id->obj.klass
           + datGetStockDevilIndex(GBWK->mapSummonID, GBWK->mapSummonUNIQ);
      v106 = v104[4];
      reportWork = v106;
LABEL_27:
      Report_LimitOver = 0;
      ReportStok = GetReportStok(reportWork, 1, 0);
      DevilReportStok_Zeniget = ReportStok;
      v24 = GetReportStok(reportWork, 2, 0);
      DevilReportStok_Hiroemon = v24;
      v26 = GetReportStok(reportWork, 4, 0);
      DevilReportStok_Gift = v26;
      size = DevilReportStok_Hiroemon->_size
           + DevilReportStok_Zeniget->_size
           + DevilReportStok_Gift->_size;
      goto LABEL_55;
    case 1u:
      fldReportMsgInit();
      mapNakamaHiroStart();
      v18 = 0;
      goto LABEL_290;
    case 2u:
      v30 = mapNakamaHiroTask();
      result = 0;
      if (!v30)
        goto LABEL_196;
      return result;
    case 3u:
      devilid = reportWork->devilid;
      v34 = 4 * sBtlGetDevilData(devilid, -1)->kucyo;
      gold = v34;
      if ((u32)sub_1905740(100, 0) <= 0x31)
      {
        v34 |= 1u;
        gold = v34;
      }
      fclResetEx(talk_wk->giftPID);
      v36 = reportWork->devilid;
      v37 = sdatDevilName(v36, 0);
      fclSetMessageVar(0, v37);
      fclStart(talk_wk->giftPID, 1, v34, 1);
      goto LABEL_253;
    case 4u:
      if (reportWork)
      {
        goto LABEL_54;
      }
      v109 = &GBWK->player->stock_id->obj.klass
           + datGetStockDevilIndex(GBWK->mapSummonID, GBWK->mapSummonUNIQ);
      v111 = v109[4];
      reportWork = v111;
LABEL_54:
      v39 = GetReportStok(reportWork, 3, 0);
      DevilReportStok_Takumi = v39;
      size = DevilReportStok_Takumi->_size;
LABEL_55:
      v18 = size > 0;
LABEL_290:
      scrSetIntReturnValue(v18);
      return 1;
    case 5u:
      fldReportMsgInit();
      mapNakamaTakumiStart();
      v18 = 0;
      goto LABEL_290;
    case 6u:
      v42 = mapNakamaTakumiTask();
      result = 0;
      if (!v42)
        goto LABEL_196;
      return result;
    case 7u:
      v44 = reportWork->devilid;
      v45 = 4 * sBtlGetDevilData(v44, -1)->kucyo;
      gold = v45;
      if ((u32)sub_1905740(100, 0) <= 0x31)
        gold = v45 | 1;
      fclResetEx(talk_wk->giftPID);
      v47 = reportWork->devilid;
      v48 = sdatDevilName(v47, 0);
      fclSetMessageVar(0, v48);
      v50 = 68;
      goto LABEL_176;
    case 8u:
      IsEventSkip = scrIsEventSkip(0);
      if (IsEventSkip)
      {
        v55 = skipWait;
        skipWait = v55 - 1;
        v100 = skipWait > 0;
      }
      else
      {
        v100 = 0;
      }
      v139 = fclUpdateEx(talk_wk->giftPID);
      v18 = 0;
      result = 0;
      if (v139)
        v140 = 1;
      else
        v140 = v100;
      if ((v140 & 1) == 0)
        goto LABEL_290;
      return result;
    case 9u:
      v18 = 1;
      fclEndMessageEx(1);
      goto LABEL_290;
    case 0xAu:
      DevilReportStok_Zeniget_local = DevilReportStok_Zeniget;
      goto LABEL_136;
    case 0xBu:
      fldReportZeniget(reportWork, DevilReportStok_Zeniget, DevilReportStok_Erase, &gold);
      if (gold < 1)
        goto LABEL_196;
      fclResetEx(talk_wk->giftPID);
      v60 = ToString_55996800((s32)&gold, "d", 0);
      fclSetMessageVar(0, v60);
      if (DevilReportStok_Erase->_size <= 1)
        v62 = 61;
      else
        v62 = 62;
      fclStart(talk_wk->giftPID, 1, v62, 1);
      SE(65);
LABEL_255:
      v18 = 1;
      skipWait = 1;
      goto LABEL_290;
    case 0xCu:
      DevilReportStok_Zeniget_local = DevilReportStok_Hiroemon;
      goto LABEL_136;
    case 0xDu:
      fldReportHiroemon(reportWork, DevilReportStok_Hiroemon, DevilReportStok_Erase, &gold, &count);
      if (count < 1)
        goto LABEL_196;
      v66 = gold;
      if (tbldata[gold]->iconType)
      {
        data = tbldata[gold]->iconType;
        v67 = Box(s32, &data);
        v68 = Format("<ITM_{0:D2}>", v67, 0);
        v69 = sdatItemName(v66);
        v70 = Concat_54766928(v68, v69, 0);
      }
      else
      {
        v70 = sdatItemName(v66);
      }
      v118 = v70;
      fclResetEx(talk_wk->giftPID);
      fclSetMessageVar(0, v118);
      v120 = ToString_55996800((s32)&count, "d", 0);
      fclSetMessageVar(1, v120);
      v124 = DevilReportStok_Erase->_size <= 1;
      v125 = 63;
      goto LABEL_244;
    case 0xEu:
      DevilReportStok_Zeniget_local = DevilReportStok_Gift;
      goto LABEL_136;
    case 0xFu:
      fldReportGift(reportWork, DevilReportStok_Gift, DevilReportStok_Erase, &gold, &count);
      if (count < 1)
        goto LABEL_196;
      v73 = gold;
      if (tbldata[gold]->iconType)
      {
        data = tbldata[gold]->iconType;
        v74 = Box(s32, &data);
        v75 = Format("<ITM_{0:D2}>", v74, 0);
        v76 = sdatItemName(v73);
        v77 = Concat_54766928(v75, v76, 0);
      }
      else
      {
        v77 = sdatItemName(v73);
      }
      v126 = v77;
      fclResetEx(talk_wk->giftPID);
      fclSetMessageVar(0, v126);
      v128 = ToString_55996800((s32)&count, "d", 0);
      fclSetMessageVar(1, v128);
      v124 = DevilReportStok_Erase->_size <= 1;
      v125 = 65;
LABEL_244:
      if (v124)
        v129 = v125;
      else
        v129 = v125 + 1;
      fclStart(talk_wk->giftPID, 1, v129, 1);
      SE(65);
LABEL_253:
      goto LABEL_255;
    case 0x10u:
      DevilReportStok_Zeniget_local = DevilReportStok_Takumi;
LABEL_136:
      v18 = DevilReportStok_Zeniget_local->_size < 1;
      goto LABEL_290;
    case 0x11u:
      fldReportTakumi(reportWork, DevilReportStok_Takumi, DevilReportStok_Erase);
      goto LABEL_289;
    case 0x12u:
      v18 = !Report_LimitOver;
      goto LABEL_290;
    case 0x13u:
      fclResetEx(talk_wk->giftPID);
      v82 = reportWork->devilid;
      v83 = sdatDevilName(v82, 0);
      fclSetMessageVar(0, v83);
      v50 = 67;
      goto LABEL_176;
    case 0x14u:
      if (scrStep)
      {
        if (scrStep != 1)
          goto LABEL_284;
        if (fclProcessCheck(talk_wk->giftPID))
          return 0;
        rstRelease(talk_wk);
        v132 = talk_wk;
        v132->giftPID = 0;
        talk_wk = 0;
        if (!v2)
          goto LABEL_284;
LABEL_281:
        Work = cmpGetWork();
        EndScript(Work->dvlReportMachine->script, 0);
LABEL_284:
        reportWork = 0;
        scrStep = 0;
        repeat = 0;
        mapNakamaWachFree();
LABEL_289:
        v18 = 1;
        goto LABEL_290;
      }
      if (v86)
      {
        if (repeat)
          goto LABEL_217;
      }
      else
      {
        if (repeat)
        {
LABEL_217:
          goto LABEL_218;
        }
      }
      scrEventSkipEnd(0, 0);
      scrLogEnd(talk_wk->giftPID);
      fclDirectCallMesClear();
LABEL_218:
      fldReportMsgEnd(reportWork);
      if (v2 || v9 != 0)
      {
        goto LABEL_220;
      }
      else
      {
        mapBgFScrollOff(25);
        fldBgZoomTest(0);
LABEL_220:
        if (repeat)
          goto LABEL_221;
        goto LABEL_263;
      }
      if (repeat)
      {
LABEL_221:
        if (v115)
        {
          v116 = talk_wk;
          goto LABEL_223;
        }
        else
        {
          v116 = talk_wk;
LABEL_223:
          rstRelease(v116);
          if (!v2)
            goto LABEL_284;
          goto LABEL_281;
        }
        rstRelease(v116);
        if (!v2)
          goto LABEL_284;
        goto LABEL_281;
      }
LABEL_263:
      fclProcessEnd(talk_wk->giftPID);
      ++scrStep;
      return 0;
    case 0x15u:
      ModelLoadInitAction();
      goto LABEL_289;
    case 0x16u:
    case 0x17u:
      if (!v4)
        goto LABEL_196;
      if (!GlobalPID)
        goto LABEL_196;
      ProcessData = dds3GetProcessData(GlobalPID);
      v13 = sub_83F0(ProcessData, gohData_t, v12);
      if (IntPara == 22)
      {
        v16 = *(sdatUnitWork_t *)(v13 + 584);
        reportWork = v16;
        v18 = 0;
      }
      else
      {
        v101 = *(sdatUnitWork_t *)(v13 + 592);
        reportWork = v101;
        v18 = 0;
        repeat = 0;
      }
      goto LABEL_290;
    case 0x18u:
      fclResetEx(talk_wk->giftPID);
      fclStart(talk_wk->giftPID, 1, 69, 1);
      goto LABEL_255;
    case 0x19u:
      fclResetEx(talk_wk->giftPID);
      v90 = reportWork->devilid;
      v91 = sdatDevilName(v90, 0);
      fclSetMessageVar(0, v91);
      v50 = 70;
LABEL_176:
      v18 = 1;
      fclStart(talk_wk->giftPID, 1, v50, 1);
      skipWait = 1;
      goto LABEL_290;
    case 0x1Au:
      if (!v4)
        goto LABEL_196;
      if (!GlobalPID)
        goto LABEL_196;
      v94 = dds3GetProcessData(GlobalPID);
      v96 = sub_83F0(v94, gohData_t, v95);
      v97 = *(u64 *)(v96 + 584);
      if (!v97)
        goto LABEL_196;
      v98 = *(u64 *)(v96 + 592);
      if (!v98 || *(s32 *)(*(u64 *)(v97 + 320) + 24) < 1 || *(s32 *)(*(u64 *)(v98 + 320) + 24) < 1)
        goto LABEL_196;
      v18 = 0;
      repeat = 1;
      goto LABEL_290;
    default:
      goto LABEL_196;
  }
}

// 0x1b6c370: s32 ACT_WIN_SEL(void)
static inline s32 ACT_WIN_SEL(void) {
  s32 IntPara;
  s32 v4;
  char *v5;
  char *ActionName;
  char *v7;
  s32 v8;
  s32 v11;
  s32 v13;
  f32 v14;
  s32 v15;
  GlobalWork_t *fldGb_local;
  s32 nakamaMode;
  s32 v18;
  s32 v19;
  s32 v20;
  s32 v21;
  s32 v22;
  s32 v23;
  s32 v24;
  s32 y;
  s32 x;
  s64 y2;

  x = 0;
  y = 0;
  y2 = 0;
  IntPara = scrGetIntPara(0);
  if (isActionWndDisp)
    goto LABEL_9;
  v5 = "";
  if (IntPara == 3)
  {
    ActionName = mapIfGetActionName(90);
    v11 = 92;
  }
  else
  {
    if (IntPara != 2)
    {
      if (IntPara == 1)
      {
        ActionName = mapIfGetActionName(91);
        v7 = mapIfGetActionName(90);
        v5 = mapIfGetActionName(92);
        v8 = 3;
        goto LABEL_43;
      }
      else
      {
        v8 = 0;
        v7 = "";
        ActionName = "";
        goto LABEL_43;
      }
      goto LABEL_42;
    }
    ActionName = mapIfGetActionName(91);
    v11 = 90;
  }
  v7 = mapIfGetActionName(v11);
  v8 = 2;
LABEL_43:
  fldPoint3To2(fldGb->playerX, fldGb->playerY + -100.0, fldGb->playerZ, (f32 *)&y2 + 1, &y2);
  if ((f32)(*((f32 *)&y2 + 1) + -1792.0) == INFINITY)
    v13 = 0x80000000;
  else
    v13 = (f32)(*((f32 *)&y2 + 1) + -1792.0);
  v14 = (f32)(*(f32 *)&y2 + -1936.0) + (f32)(*(f32 *)&y2 + -1936.0);
  if (v14 == INFINITY)
    v15 = 2147483636;
  else
    v15 = (s32)v14 - 12;
  y = v15;
  fldGb_local = fldGb;
  nakamaMode = fldGb_local->nakamaMode;
  fldGb_local->scriptStartWinX = v13;
  fldGb_local->scriptStartWinY = v15;
  *(u64 *)&fldGb_local->scriptStartWinCur = 0;
  fldGb_local->scriptStartWinMode = nakamaMode;
  fldGb_local->scriptStartWinType = IntPara + 90;
  itfSetActionWndLines(v8);
  v18 = frPreCalcStrWidth(ActionName, 1, 0);
  v19 = frPreCalcStrWidth(v7, 1, 0);
  v20 = frPreCalcStrWidth(v5, 1, 0);
  if (v18 <= v19)
    v21 = v19;
  else
    v21 = v18;
  if (v21 <= v20)
    v22 = v20;
  else
    v22 = v21;
  if (v22 >= 0)
    v23 = v22;
  else
    v23 = v22 + 1;
  v24 = v13 - (v23 >> 1);
  x = v24;
  mapIfDrawActionWin2(v24, v15, v22, 0, 0);
  mapIfActionWinPosClip(&x, &y, v22);
  itfSetActWndTextCoror(ActionName, 1, 0xFFFFFFFF);
  itfSetActWndTextCoror(v7, 2, 0xFFFFFFFF);
  itfSetActWndTextCoror(v5, 3, 0xFFFFFFFF);
  return 0;
LABEL_42:
  goto LABEL_43;
LABEL_9:
  switch (IntPara)
  {
    case 3:
      if (CHECK_TRIG(4097, 1))
        goto LABEL_72;
      if (!CHECK_TRIG(4101, 1))
        return 0;
      break;
    case 2:
      if (!CHECK_TRIG(4100, 1))
      {
        if (CHECK_TRIG(4097, 1))
          goto LABEL_72;
        return 0;
      }
      break;
    case 1:
      if (!CHECK_TRIG(4100, 1))
      {
        if (CHECK_TRIG(4097, 1))
        {
          v4 = 2;
          goto LABEL_32;
        }
        if (CHECK_TRIG(4101, 1))
        {
LABEL_72:
          v4 = 1;
          goto LABEL_32;
        }
        return 0;
      }
      break;
    default:
      return 0;
  }
  v4 = 0;
LABEL_32:
  scrSetIntReturnValue(v4);
  itfPreDrawActionWndDisp(0);
  SE(0);
  return 1;
}

// 0x1b6c8c0: s32 CHK_DRLANG(void)
static inline s32 CHK_DRLANG(void) {
  s32 dream_code_language;
  s32 Language;

  dream_code_language = GBWK->dream_code_language;
  Language = GetLanguage();
  scrSetIntReturnValue(dream_code_language == Language);
  return 1;
}

// 0x1b6c9b0: s32 CUT_CAMERA_MOVE(void)
static inline s32 CUT_CAMERA_MOVE(void) {
  s32 IntPara;
  s32 v2;
  s32 v3;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  v3 = scrGetIntPara(2);
  if (IntPara)
  {
    fldCameraCutMoveSet(IntPara, v2, v3);
    return 1;
  }
  else
  {
    fldCameraCutMoveClr();
    return 1;
  }
}

// 0x1b6caa0: s32 SET_SOLOMODE_POINT(void)
static inline s32 SET_SOLOMODE_POINT(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  LODWORD(mapNakamaTakumiTask_r) = IntPara;
  return 1;
}

// 0x1b6cb90: s32 GET_SOLOMODE_POINT(void)
static inline s32 GET_SOLOMODE_POINT(void) {
  scrSetIntReturnValue(SLODWORD(mapNakamaTakumiTask_r));
  return 1;
}

// 0x1b6cca0: s32 AUTO_NAKAMATORAIDOU(void)
static inline s32 AUTO_NAKAMATORAIDOU(void) {
  autoNakamaToRaidou();
  return 1;
}

// 0x1b6cd20: s32 QUEST_EX(void)
static inline s32 QUEST_EX(void) {
  s32 IntPara;
  s32 *v3;
  s32 *v5;
  s32 *EventBit;
  s32 *v9;
  s32 *v11;
  u32 v12;

  IntPara = scrGetIntPara(0);
  scrGetIntPara(1);
  if (IntPara == 1)
  {
    if (evtBitCheck(185) && evtBitCheck(12498) && !evtBitCheck(12554))
    {
      EventBit = GBWK->EventBit;
      EventBit[392] |= 0x800u;
      if (!evtBitCheck(195))
        goto LABEL_28;
      goto LABEL_12;
    }
    v3 = GBWK->EventBit;
    v3[392] &= ~0x800u;
    if (!evtBitCheck(195))
      goto LABEL_28;
LABEL_12:
    if (evtBitCheck(12498) && evtBitCheck(12554) && !evtBitCheck(12594))
    {
      v5 = GBWK->EventBit;
      v5[393] |= 0x80000u;
      if (!evtBitCheck(206))
        goto LABEL_39;
      goto LABEL_31;
    }
LABEL_28:
    v9 = GBWK->EventBit;
    v9[393] &= ~0x80000u;
    if (!evtBitCheck(206))
      goto LABEL_39;
LABEL_31:
    if (evtBitCheck(12498) && evtBitCheck(12554) && evtBitCheck(12594))
    {
      v11 = GBWK->EventBit;
      v12 = v11[394] | 0x80000;
      goto LABEL_42;
    }
LABEL_39:
    v11 = GBWK->EventBit;
    v12 = v11[394] & 0xFFF7FFFF;
LABEL_42:
    v11[394] = v12;
    return 1;
  }
  return 1;
}

// 0x1b6d070: s32 SET_EXTRA_CUTID(void)
static inline s32 SET_EXTRA_CUTID(void) {
  s32 IntPara;
  s32 v2;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(0);
  fldSetExtraCutID(IntPara, v2);
  return 1;
}

// 0x1b6d120: s32 SET_MINIMAPUPDATE(void)
static inline s32 SET_MINIMAPUPDATE(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  MiniMapUpdateFlag = IntPara == 1;
  return 1;
}

// 0x1b6d210: s32 SETUP_MINIMAPUPDATE(void)
static inline s32 SETUP_MINIMAPUPDATE(void) {
  mapIfSetDestList();
  minMapRefresh();
  return 1;
}

// 0x1b6d280: s32 SET_MINIMAP_PLAYER(void)
static inline s32 SET_MINIMAP_PLAYER(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  fldSetMinimapPlayer(IntPara);
  return 1;
}

// 0x1b6d320: s32 MAPWALLDEL(void)
static inline s32 MAPWALLDEL(void) {
  s16 IntPara;

  IntPara = scrGetIntPara(0);
  mapWallObjDel(IntPara);
  return 1;
}

// 0x1b6d3c0: s32 MAPWALLSET(void)
static inline s32 MAPWALLSET(void) {
  s16 IntPara;

  IntPara = scrGetIntPara(0);
  mapWallObjSet(IntPara);
  return 1;
}

// 0x1b6d460: s32 POPUP_PAUSE_END(void)
static inline s32 POPUP_PAUSE_END(void) {
  if (!instance)
    return 1;
  goto LABEL_3;
  if (instance)
LABEL_3:
    SetPauseAndInvisible(instance, 0, 0);
  return 1;
}

// 0x1b6d4e0: s32 RESOURCES_RELEASE(void)
static inline s32 RESOURCES_RELEASE(void) {
  sdfMemResourcesRelease();
  return 1;
}

// 0x1b641c0
s32 fldGetHojiID(char **pName) {
  s32 v3;
  u16 Chars;

  if (!Equals_54828784(*pName, "hoji", 0))
    return 0;
  if (!get_Chars(*pName, 0, 0))
    return 0;
  if (!get_Chars(*pName, 1, 0))
    return 0;
  if (!get_Chars(*pName, 2, 0))
    return 0;
  if (!get_Chars(*pName, 3, 0))
    return 0;
  v3 = 4;
  if (get_Chars(*pName, 4, 0))
  {
    v3 = 5;
    if (get_Chars(*pName, 5, 0))
    {
      v3 = 6;
      if (get_Chars(*pName, 6, 0))
      {
        v3 = 7;
        if (get_Chars(*pName, 7, 0))
        {
          v3 = 8;
          if (get_Chars(*pName, 8, 0))
          {
            v3 = 9;
            if (get_Chars(*pName, 9, 0))
            {
              v3 = 10;
              if (get_Chars(*pName, 10, 0))
              {
                v3 = 11;
                if (get_Chars(*pName, 11, 0))
                {
                  v3 = 12;
                  if (get_Chars(*pName, 12, 0))
                  {
                    v3 = 13;
                    if (get_Chars(*pName, 13, 0))
                    {
                      v3 = 14;
                      if (get_Chars(*pName, 14, 0))
                      {
                        v3 = 15;
                        if (get_Chars(*pName, 15, 0))
                        {
                          v3 = 16;
                          if (get_Chars(*pName, 16, 0))
                          {
                            v3 = 17;
                            if (get_Chars(*pName, 17, 0))
                            {
                              v3 = 18;
                              if (get_Chars(*pName, 18, 0))
                              {
                                v3 = 19;
                                if (get_Chars(*pName, 19, 0))
                                {
                                  v3 = 20;
                                  if (get_Chars(*pName, 20, 0))
                                  {
                                    v3 = 21;
                                    if (get_Chars(*pName, 21, 0))
                                    {
                                      v3 = 22;
                                      if (get_Chars(*pName, 22, 0))
                                      {
                                        v3 = 23;
                                        if (get_Chars(*pName, 23, 0))
                                        {
                                          v3 = 24;
                                          if (get_Chars(*pName, 24, 0))
                                          {
                                            v3 = 25;
                                            if (get_Chars(*pName, 25, 0))
                                            {
                                              v3 = 26;
                                              if (get_Chars(*pName, 26, 0))
                                              {
                                                v3 = 27;
                                                if (get_Chars(*pName, 27, 0))
                                                {
                                                  v3 = 28;
                                                  if (get_Chars(*pName, 28, 0))
                                                  {
                                                    v3 = 29;
                                                    if (get_Chars(*pName, 29, 0))
                                                    {
                                                      v3 = 30;
                                                      if (get_Chars(*pName, 30, 0))
                                                      {
                                                        v3 = 31;
                                                        if (get_Chars(*pName, 31, 0))
                                                          return 0;
                                                      }
                                                    }
                                                  }
                                                }
                                              }
                                            }
                                          }
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  Chars = get_Chars(*pName, v3 - 2, 0);
  return 10 * Chars + get_Chars(*pName, v3 - 1, 0) - 528;
}

// 0x1b66bb0
sdfVector4_t fldGetMAP_CUT_OVERSET_Cam(void) {
  f32 *static_fields;
  sdfVector4_t result;

  result.x = static_fields[8];
  result.y = static_fields[9];
  result.z = static_fields[10];
  result.w = static_fields[11];
  return result;
}

// 0x1b66c40
sdfVector4_t fldGetMAP_CUT_OVERSET_Tgt(void) {
  f32 *static_fields;
  sdfVector4_t result;

  result.x = static_fields[12];
  result.y = static_fields[13];
  result.z = static_fields[14];
  result.w = static_fields[15];
  return result;
}

// 0x1b68280
s32 fldGetFastTravelPrice(s32 mapID, u32 gotoIdx) {
  if (gotoIdx)
    return 0;
  return jimusyo_return_yen[mapID];
}

// 0x1b6b2c0
void fldWaitSet(void) {
  skipWait = 1;
  return;
}

// 0x1b6c2e0
void fldRepeatSet(void) {
  repeat = 1;
  return;
}

// 0x1b6b180
void fldReportMsgInit(void) {
  tagRST_GROWTH_WORK *v5;

  if (talk_wk)
  {
    goto LABEL_5;
  }
  v5 = Allocate(tagRST_GROWTH_WORK);
  _ctor(v5, 0);
  talk_wk = v5;
LABEL_5:
  rstInit(talk_wk, 1);
}

// 0x1b6c260
void fldReportMsgEnd(sdatUnitWork_t *pWork) {
  if (pWork)
    SortReportStok(pWork, 0);
  summonDvDispHukidashi = fldDevilReportSummonDevilCheck();
}

// 0x1b6b350
void fldReportZeniget(sdatUnitWork_t *pWork, void *ZenigetList, void *EraseList, s32 *gold) {
  void *v8;
  s32 size;
  s32 v10;
  s32 i;
  s32 v13;
  Il2CppObject *v14;
  s64 v15;
  u64 *v16;
  Il2CppObject *v17;
  void *v18;
  Il2CppClass **v19;
  sdatPlayerUnitWork_t *player;
  s32 v23;
  Il2CppObject *Item;
  const MethodInfo_2DFC320 *v25;
  Il2CppObject *v26;
  const MethodInfo_2DFC320 *v27;
  Il2CppObject *v28;
  s64 v29;
  u64 *v30;
  DevilReportStok_t *items;
  Il2CppClass **v32;
  sdatPlayerUnitWork_t *v34;
  s32 v35;
  s32 v36;
  const MethodInfo_2DFC320 *v37;
  Il2CppObject *v38;
  const MethodInfo_2DFC320 *v39;
  Il2CppObject *v40;
  s32 v41;
  Il2CppObject *v42;
  s32 v43;
  Il2CppObject *v44;

  v8 = Allocate(System_Collections_Generic_List_DevilReportStok_t_);
  __ctor(v8);
  *gold = 0;
  size = EraseList->_size;
  v10 = EraseList->_version + 1;
  EraseList->_size = 0;
  EraseList->_version = v10;
  if (size >= 1)
    Clear(EraseList->_items, 0, size, 0);
  if (ZenigetList->_size >= 1)
  {
    for (i = 0; i < ZenigetList->_size; ++i)
    {
      v13 = GBWK->player->gold;
      if (HIDWORD(_get_Item(ZenigetList, i)[1].monitor) + v13 <= 9999999)
      {
        player = GBWK->player;
        v23 = player->gold;
        Item = _get_Item(ZenigetList, i);
        v25 = Method_System_Collections_Generic_List_DevilReportStok_t__get_Item__;
        player->gold = HIDWORD(Item[1].monitor) + v23;
        LODWORD(player) = *gold;
        v26 = _get_Item(ZenigetList, i, v25);
        v27 = Method_System_Collections_Generic_List_DevilReportStok_t__get_Item__;
        *gold = HIDWORD(v26[1].monitor) + (u32)player;
        v28 = _get_Item(ZenigetList, i, v27);
        v29 = EraseList->_size;
        v30 = Method_System_Collections_Generic_List_DevilReportStok_t__Add__;
        ++EraseList->_version;
        items = EraseList->_items;
        if ((u32)v29 >= LODWORD(items->max_length))
        {
          _AddWithResize(EraseList, v28, *(const MethodInfo_2DFC660 **)(*(u64 *)(v30[4] + 192) + 112));
        }
        else
        {
          v32 = &items->obj.klass + v29;
          EraseList->_size = v29 + 1;
          v32[4] = v28;
        }
        continue;
      }
      v14 = _get_Item(ZenigetList, i);
      v15 = v8->_size;
      v16 = Method_System_Collections_Generic_List_DevilReportStok_t__Add__;
      v17 = v14;
      ++v8->_version;
      v18 = v8->_items;
      if ((u32)v15 >= LODWORD(v18->max_length))
      {
        _AddWithResize(v8, v14, *(const MethodInfo_2DFC660 **)(*(u64 *)(v16[4] + 192) + 112));
      }
      else
      {
        v19 = &v18->obj.klass + v15;
        v8->_size = v15 + 1;
        v19[4] = v17;
      }
      Report_LimitOver = 1;
      v34 = GBWK->player;
      v35 = v34->gold;
      v36 = 9999999 - v35;
      if (9999999 - v35 >= 1)
      {
        v34 = GBWK->player;
        v35 = v34->gold;
        v37 = Method_System_Collections_Generic_List_DevilReportStok_t__get_Item__;
        v34->gold = v35 + v36;
        *gold += v36;
        v38 = _get_Item(ZenigetList, i, v37);
        v39 = Method_System_Collections_Generic_List_DevilReportStok_t__get_Item__;
        HIDWORD(v38[1].monitor) -= v36;
        v40 = _get_Item(ZenigetList, i, v39);
        SwapReportStok(pWork, v40, 0);
      }
    }
  }
  if (EraseList->_size >= 1)
  {
    v41 = 0;
    do
    {
      v42 = _get_Item(EraseList, v41);
      _Remove(ZenigetList, v42);
      ++v41;
    }
    while (v41 < EraseList->_size);
  }
  if (v8->_size >= 1)
  {
    v43 = 0;
    do
    {
      v44 = _get_Item(v8, v43);
      _Remove(ZenigetList, v44);
      ++v43;
    }
    while (v43 < v8->_size);
  }
  DelReportStok(pWork, EraseList, 0);
}

// 0x1b6b7b0
void fldReportHiroemon(sdatUnitWork_t *pWork, void *HiroemonList, void *EraseList, s32 *ItemID, s32 *count) {
  void *v10;
  s32 size;
  s32 v12;
  s32 i;
  s32 monitor;
  s32 v15;
  s32 ItemMaxNum;
  s32 v17;
  Il2CppObject *v18;
  s64 v19;
  u64 *v20;
  void *v21;
  Il2CppClass **v22;
  s32 v24;
  s32 monitor_high;
  s32 v26;
  Il2CppObject *Item;
  const MethodInfo_2DFC320 *v28;
  Il2CppObject *v29;
  s64 v30;
  u64 *v31;
  DevilReportStok_t *items;
  Il2CppClass **v33;
  s64 v35;
  s32 v36;
  const MethodInfo_2DFC320 *v37;
  Il2CppObject *v38;
  const MethodInfo_2DFC320 *v39;
  Il2CppObject *v40;
  s32 v41;
  Il2CppObject *v42;
  s32 v43;
  Il2CppObject *v44;

  v10 = Allocate(System_Collections_Generic_List_DevilReportStok_t_);
  __ctor(v10);
  *ItemID = 0;
  *count = 0;
  size = EraseList->_size;
  v12 = EraseList->_version + 1;
  EraseList->_size = 0;
  EraseList->_version = v12;
  if (size >= 1)
    Clear(EraseList->_items, 0, size, 0);
  if (HiroemonList->_size >= 1)
  {
    for (i = 0; i < HiroemonList->_size; ++i)
    {
      monitor = *ItemID;
      if (!*ItemID)
      {
        monitor = _get_Item(HiroemonList, i)[1].monitor;
        *ItemID = monitor;
      }
      if (monitor != LODWORD(_get_Item(HiroemonList, i)[1].monitor))
        continue;
      v15 = *ItemID;
      ItemMaxNum = datGetItemMaxNum(v15);
      v17 = GBWK->player->item[*ItemID];
      if (HIDWORD(_get_Item(HiroemonList, i)[1].monitor) + v17 <= ItemMaxNum)
      {
        v24 = *ItemID;
        monitor_high = HIDWORD(_get_Item(HiroemonList, i)[1].monitor);
        datAddItem(v24, monitor_high);
        v26 = *count;
        Item = _get_Item(HiroemonList, i);
        v28 = Method_System_Collections_Generic_List_DevilReportStok_t__get_Item__;
        *count = HIDWORD(Item[1].monitor) + v26;
        v29 = _get_Item(HiroemonList, i, v28);
        v30 = EraseList->_size;
        v31 = Method_System_Collections_Generic_List_DevilReportStok_t__Add__;
        ++EraseList->_version;
        items = EraseList->_items;
        if ((u32)v30 >= LODWORD(items->max_length))
        {
          _AddWithResize(EraseList, v29, *(const MethodInfo_2DFC660 **)(*(u64 *)(v31[4] + 192) + 112));
        }
        else
        {
          v33 = &items->obj.klass + v30;
          EraseList->_size = v30 + 1;
          v33[4] = v29;
        }
        continue;
      }
      v18 = _get_Item(HiroemonList, i);
      v19 = v10->_size;
      v20 = Method_System_Collections_Generic_List_DevilReportStok_t__Add__;
      ++v10->_version;
      v21 = v10->_items;
      if ((u32)v19 >= LODWORD(v21->max_length))
      {
        _AddWithResize(v10, v18, *(const MethodInfo_2DFC660 **)(*(u64 *)(v20[4] + 192) + 112));
      }
      else
      {
        v22 = &v21->obj.klass + v19;
        v10->_size = v19 + 1;
        v22[4] = v18;
      }
      Report_LimitOver = 1;
      v35 = *ItemID;
      v36 = ItemMaxNum - GBWK->player->item[v35];
      if (v36 >= 1)
      {
        datAddItem(v35, v36);
        v37 = Method_System_Collections_Generic_List_DevilReportStok_t__get_Item__;
        *count += v36;
        v38 = _get_Item(HiroemonList, i, v37);
        v39 = Method_System_Collections_Generic_List_DevilReportStok_t__get_Item__;
        HIDWORD(v38[1].monitor) -= v36;
        v40 = _get_Item(HiroemonList, i, v39);
        SwapReportStok(pWork, v40, 0);
      }
    }
  }
  if (EraseList->_size >= 1)
  {
    v41 = 0;
    do
    {
      v42 = _get_Item(EraseList, v41);
      _Remove(HiroemonList, v42);
      ++v41;
    }
    while (v41 < EraseList->_size);
  }
  if (v10->_size >= 1)
  {
    v43 = 0;
    do
    {
      v44 = _get_Item(v10, v43);
      _Remove(HiroemonList, v44);
      ++v43;
    }
    while (v43 < v10->_size);
  }
  DelReportStok(pWork, EraseList, 0);
}

// 0x1b6bc60
void fldReportGift(sdatUnitWork_t *pWork, void *GiftList, void *EraseList, s32 *ItemID, s32 *count) {
  void *v10;
  s32 size;
  s32 v12;
  s32 i;
  s32 monitor;
  s32 v15;
  s32 ItemMaxNum;
  s32 v17;
  Il2CppObject *v18;
  s64 v19;
  u64 *v20;
  void *v21;
  Il2CppClass **v22;
  s32 v24;
  s32 monitor_high;
  s32 v26;
  Il2CppObject *Item;
  const MethodInfo_2DFC320 *v28;
  Il2CppObject *v29;
  s64 v30;
  u64 *v31;
  DevilReportStok_t *items;
  Il2CppClass **v33;
  s64 v35;
  s32 v36;
  const MethodInfo_2DFC320 *v37;
  Il2CppObject *v38;
  const MethodInfo_2DFC320 *v39;
  Il2CppObject *v40;
  s32 v41;
  Il2CppObject *v42;
  s32 v43;
  Il2CppObject *v44;

  v10 = Allocate(System_Collections_Generic_List_DevilReportStok_t_);
  __ctor(v10);
  *ItemID = 0;
  *count = 0;
  size = EraseList->_size;
  v12 = EraseList->_version + 1;
  EraseList->_size = 0;
  EraseList->_version = v12;
  if (size >= 1)
    Clear(EraseList->_items, 0, size, 0);
  if (GiftList->_size >= 1)
  {
    for (i = 0; i < GiftList->_size; ++i)
    {
      monitor = *ItemID;
      if (!*ItemID)
      {
        monitor = _get_Item(GiftList, i)[1].monitor;
        *ItemID = monitor;
      }
      if (monitor != LODWORD(_get_Item(GiftList, i)[1].monitor))
        continue;
      v15 = *ItemID;
      ItemMaxNum = datGetItemMaxNum(v15);
      v17 = GBWK->player->item[*ItemID];
      if (HIDWORD(_get_Item(GiftList, i)[1].monitor) + v17 <= ItemMaxNum)
      {
        v24 = *ItemID;
        monitor_high = HIDWORD(_get_Item(GiftList, i)[1].monitor);
        datAddItem(v24, monitor_high);
        v26 = *count;
        Item = _get_Item(GiftList, i);
        v28 = Method_System_Collections_Generic_List_DevilReportStok_t__get_Item__;
        *count = HIDWORD(Item[1].monitor) + v26;
        v29 = _get_Item(GiftList, i, v28);
        v30 = EraseList->_size;
        v31 = Method_System_Collections_Generic_List_DevilReportStok_t__Add__;
        ++EraseList->_version;
        items = EraseList->_items;
        if ((u32)v30 >= LODWORD(items->max_length))
        {
          _AddWithResize(EraseList, v29, *(const MethodInfo_2DFC660 **)(*(u64 *)(v31[4] + 192) + 112));
        }
        else
        {
          v33 = &items->obj.klass + v30;
          EraseList->_size = v30 + 1;
          v33[4] = v29;
        }
        continue;
      }
      v18 = _get_Item(GiftList, i);
      v19 = v10->_size;
      v20 = Method_System_Collections_Generic_List_DevilReportStok_t__Add__;
      ++v10->_version;
      v21 = v10->_items;
      if ((u32)v19 >= LODWORD(v21->max_length))
      {
        _AddWithResize(v10, v18, *(const MethodInfo_2DFC660 **)(*(u64 *)(v20[4] + 192) + 112));
      }
      else
      {
        v22 = &v21->obj.klass + v19;
        v10->_size = v19 + 1;
        v22[4] = v18;
      }
      Report_LimitOver = 1;
      v35 = *ItemID;
      v36 = ItemMaxNum - GBWK->player->item[v35];
      if (v36 >= 1)
      {
        datAddItem(v35, v36);
        v37 = Method_System_Collections_Generic_List_DevilReportStok_t__get_Item__;
        *count += v36;
        v38 = _get_Item(GiftList, i, v37);
        v39 = Method_System_Collections_Generic_List_DevilReportStok_t__get_Item__;
        HIDWORD(v38[1].monitor) -= v36;
        v40 = _get_Item(GiftList, i, v39);
        SwapReportStok(pWork, v40, 0);
      }
    }
  }
  if (EraseList->_size >= 1)
  {
    v41 = 0;
    do
    {
      v42 = _get_Item(EraseList, v41);
      _Remove(GiftList, v42);
      ++v41;
    }
    while (v41 < EraseList->_size);
  }
  if (v10->_size >= 1)
  {
    v43 = 0;
    do
    {
      v44 = _get_Item(v10, v43);
      _Remove(GiftList, v44);
      ++v43;
    }
    while (v43 < v10->_size);
  }
  DelReportStok(pWork, EraseList, 0);
}

// 0x1b6c110
void fldReportTakumi(sdatUnitWork_t *pWork, void *TakumiList, void *EraseList) {
  s32 size;
  s32 v8;
  Il2CppObject *Item;
  s64 v10;
  u64 *v11;
  Il2CppObject *v12;
  DevilReportStok_t *items;
  Il2CppClass **v14;
  Il2CppObject *v15;

  size = EraseList->_size;
  v8 = EraseList->_version + 1;
  EraseList->_size = 0;
  EraseList->_version = v8;
  if (size >= 1)
    Clear(EraseList->_items, 0, size, 0);
  Item = _get_Item(TakumiList, 0);
  v10 = EraseList->_size;
  v11 = Method_System_Collections_Generic_List_DevilReportStok_t__Add__;
  v12 = Item;
  ++EraseList->_version;
  items = EraseList->_items;
  if ((u32)v10 >= LODWORD(items->max_length))
  {
    _AddWithResize(EraseList, Item, *(const MethodInfo_2DFC660 **)(*(u64 *)(v11[4] + 192) + 112));
  }
  else
  {
    v14 = &items->obj.klass + v10;
    EraseList->_size = v10 + 1;
    v14[4] = v12;
  }
  v15 = _get_Item(TakumiList, 0);
  _Remove(TakumiList, v15);
  DelReportStok(pWork, EraseList, 0);
}
