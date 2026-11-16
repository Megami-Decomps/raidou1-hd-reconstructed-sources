#include "types.h"
#include "aw_prediction.h"
#include "aw_sbattle.h"
#include "aw_summonng.h"
#include "aw_xatkpad.h"
#include "bsflow.h"
#include "dat.h"
#include "dds3basic.h"
#include "dds3kerneldraw.h"
#include "effstat.h"
#include "evtbit.h"
#include "fld.h"
#include "itf.h"
#include "mdl.h"
#include "sbtl.h"
#include "sbtlactai.h"
#include "sbtlaction.h"
#include "sbtlcalc.h"
#include "sbtlcamera.h"
#include "sbtlcmbskl.h"
#include "sbtlcommand.h"
#include "sbtlcontinue.h"
#include "sbtldmg.h"
#include "sbtleff.h"
#include "sbtlencount.h"
#include "sbtlmain.h"
#include "sbtlplayer.h"
#include "sbtlplayer_spirit.h"
#include "sbtlscene.h"
#include "sbtlscript.h"
#include "sbtlskill.h"
#include "sbtlsm.h"
#include "sbtlsound.h"
#include "sbtlsub.h"
#include "sbtlsupport.h"
#include "sbtlunit.h"
#include "sbtlvisual.h"
#include "scr.h"
#include "sdf_vu0.h"
#include "sdfmodel.h"
#include "sdfquat.h"
#include "tips.h"
#include "tutorialscript.h"

#define MATORY_POS_DISTANCE 150
#define MATORY_ANGLE 45

typedef struct SBTLAISYO_DATAWORK SBTLAISYO_DATAWORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct S_CameraMoveDt S_CameraMoveDt;
typedef struct S_FovMove S_FovMove;
typedef struct S_PosMove S_PosMove;
typedef struct S_UpVMove S_UpVMove;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct sdfModelNode_t sdfModelNode_t;

static u32 script_eff_colortbl[8];
SBTLAISYO_DATAWORK *script_aisyo_tbl;
static s32 hk_seltype;
static f32 BLOCKER_MOVE_SPEED;
static f32 BS14_CSHO_R_SIZE;
static S_PosMove *g_aTgtMove_KayaDead0;
static S_PosMove *g_aCamMove_KayaDead0;
static S_PosMove *g_aTgtMove_KayaDead1;
static S_PosMove *g_aCamMove_KayaDead1;
static S_CameraMoveDt *g_CamMov_KayaDead0;
static S_CameraMoveDt *g_CamMov_KayaDead1;
static S_PosMove *g_aTgtMove_BS_LASTB3_0;
static S_PosMove *g_aCamMove_BS_LASTB3_0;
static S_CameraMoveDt *g_CamMov_BS_LASTB3_0;
static S_PosMove *g_aTgtMove_BS_LASTB3_1;
static S_PosMove *g_aCamMove_BS_LASTB3_1;
static S_CameraMoveDt *g_CamMov_BS_LASTB3_1;
static S_PosMove *g_aTgtMove_BS_LASTB3_1B;
static S_PosMove *g_aCamMove_BS_LASTB3_1B;
static S_FovMove *g_aFovMove_BS_LASTB3_1B;
static S_UpVMove *g_aUpVMove_BS_LASTB3_1B;
static S_CameraMoveDt *g_CamMov_BS_LASTB3_1B;
static S_PosMove *g_aTgtMove_BS_LASTB3_2;
static S_PosMove *g_aCamMove_BS_LASTB3_2;
static S_FovMove *g_aFovMove_BS_LASTB3_2;
static S_UpVMove *g_aUpVMove_BS_LASTB3_2;
static S_CameraMoveDt *g_CamMov_BS_LASTB3_2;
static S_PosMove *g_aTgtMove_BS_LASTB3_3;
static S_PosMove *g_aCamMove_BS_LASTB3_3;
static S_FovMove *g_aFovMove_BS_LASTB3_3;
static S_UpVMove *g_aUpVMove_BS_LASTB3_3;
static S_CameraMoveDt *g_CamMov_BS_LASTB3_3;
static s32 gBossTalk_GetReady_Step;
static bool gBossTalk_GetReady_TheWorld_Bk;
static s32 gBossTalk_Target_ListID;
static s32 gBossTalk_GetReady_TimeOutCnt;
static s32 gBossTalk_GetReady_TimeOutMax;
static s32 taiitu_power_time;
s32 BS_LASTB2_pos_type;
s32 sklid_BS14_target;
static s32 *BS14_CHOUSIN_pos;

static s32 SBTL_SET_SCRIPT_Sub(s32 evtload_evtno, s32 eventno, s32 theworld, s32 scenestop);
static void sBtlScriptSub_ResetBadStatus(SBTLUNIT_WORK *wk);
static void Support_SetPosInit(void);
static void Support_SetPos(SBTLUNIT_WORK *wk, s32 pointID);
static s32 sBtlIncNodeColor(sdfModelNode_t *pNode, u32 DstColor, u32 IncColor, u32 Mode);
static s32 sBtlIncNodeColorFromName(dds3ModelHandle_t *hModel, char *pNodeName, u32 DstColor, u32 IncColor, u32 Mode);
static s32 BS14_TargetSet(SBTLUNIT_WORK *wk, const sdfVector4_t *pos, f32 _SizeR, f32 _Life, s32 _Wait);
static void BS14_CHOUSIN_TargetSet(SBTLUNIT_WORK *wk);
SBTLUNIT_WORK *GetData(void);
SBTLUNIT_WORK *Support_GetUserData(void);
SBTLUNIT_WORK *Support_GetNakamaData(s32 idx);
void Support_RunZoomProcess(void);
s32 Support_RunWarpProcess(void);
s32 Support_RunWaitProcess(void);
s32 Support_RunDownProcess(void);
s32 RunReactProcess(void);
void Support_SetAisyo(s32 listID, s32 aisyoID);
void Support_MovePos(SBTLUNIT_WORK *wk, const sdfVector4_t *pos);
void Support_MovePos2(SBTLUNIT_WORK *wk, const sdfVector4_t *pos, f32 frame, s32 motion_no);
s32 CheckLoadData(void);

// macros
// 0x20fbed0: s32 SBTL_CHK_EVENT(void)
static inline s32 SBTL_CHK_EVENT(void) {
  s32 *v1;
  SBTLUNIT_WORK *Data;
  s32 devilid;
  AITBLDATA_WORK *AITBL;
  AICHK_WORK *act;
  u32 *code;
  u64 v7;
  u64 v8;
  u64 v9;
  s32 v10;
  s32 v11;
  u32 v12;
  u64 v14;
  u32 v15;
  CheckFuncTblDelegate v16;
  s32 v17;
  AICHK_WORK *v18;
  u64 v20;
  u32 v21;
  CheckFuncTblDelegate v22;
  s32 v23;
  AICHK_WORK *v24;
  u64 v26;
  u32 v27;
  CheckFuncTblDelegate v28;
  s32 v29;
  SBTLAI_WORK *aiwk;
  s32 scrStep;
  s32 v32;

  v1 = NewSpecific(s32, 3u);
  Data = GetData();
  devilid = Data->para->devilid;
  AITBL = sBtlGetAITBL(devilid, Data);
  v1[2] = -1;
  act = AITBL->act;
  *(u64 *)&v1[0] = -1;
  code = act[0]->code;
  v7 = code[8];
  if ((u32)v7 >= 0x100000)
  {
    v14 = v7 >> 20;
    v15 = v7 & 0xFFFFF;
    v16 = CheckFuncTbl[v14];
    v17 = (v16->invoke_impl)(v16->method_code, Data, v15, 0, v16->method);
    v18 = AITBL->act;
    v1[0] = v17;
    code = v18[0]->code;
    v8 = code[9];
    if ((u32)v8 < 0x100000)
    {
LABEL_7:
      v9 = code[10];
      if ((u32)v9 < 0x100000)
        goto LABEL_8;
LABEL_17:
      v26 = v9 >> 20;
      v27 = v9 & 0xFFFFF;
      v28 = CheckFuncTbl[v26];
      v29 = (v28->invoke_impl)(v28->method_code, Data, v27, 2, v28->method);
      v1[2] = v29;
      v10 = v1[1];
      v11 = v29;
      if (v1[0] == 1)
        goto LABEL_9;
      goto LABEL_20;
    }
  }
  else
  {
    v8 = code[9];
    if ((u32)v8 < 0x100000)
      goto LABEL_7;
  }
  v20 = v8 >> 20;
  v21 = v8 & 0xFFFFF;
  v22 = CheckFuncTbl[v20];
  v23 = (v22->invoke_impl)(v22->method_code, Data, v21, 1, v22->method);
  v24 = AITBL->act;
  v1[1] = v23;
  v9 = v24[0]->code[2];
  if ((u32)v9 >= 0x100000)
    goto LABEL_17;
LABEL_8:
  v10 = v1[1];
  v11 = v1[2];
  if (v1[0] == 1)
  {
LABEL_9:
    if (v10 == 1)
    {
      v12 = v11 != 1;
    }
    else if (v11 == 1)
    {
      v12 = 2;
    }
    else
    {
      v12 = 4;
    }
    goto LABEL_30;
  }
LABEL_20:
  if (v10 == 1)
  {
    if (v11 == 1)
      v12 = 3;
    else
      v12 = 5;
  }
  else if (v11 == 1)
  {
    v12 = 6;
  }
  else
  {
    v12 = 7;
  }
LABEL_30:
  aiwk = Data->aiwk;
  scrStep = aiwk->scrStep;
  if ((scrStep & (1 << v12)) == 0)
  {
    v32 = AITBL->act[0]->jmptbl[v12];
    aiwk->scrStep = scrStep | (1 << v12);
    goto LABEL_33;
  }
  v32 = -1;
LABEL_33:
  scrSetIntReturnValue(v32);
  return 1;
}

// 0x20fc1c0: s32 SBTL_SET_BATTLE_STOP(void)
static inline s32 SBTL_SET_BATTLE_STOP(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v5;
  SBTLUNIT_WORK *v6;
  s32 IntPara;
  s32 v9;
  s32 v10;
  void *Instance;
  void *v14;

  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v5 = sBtlSearchUnit_ID(UnitMng, playerID);
  if (v5)
  {
    v6 = v5;
    if (sBtlChkNowJump(v6))
      goto LABEL_20;
  }
  goto LABEL_12;
LABEL_20:
  StopKey();
LABEL_12:
  IntPara = scrGetIntPara(0);
  v9 = scrGetIntPara(1);
  v10 = scrGetIntPara(2);
  sBtlSupport_BattleStop(IntPara, v9, v10);
  wk->status4 |= 0x1000000u;
  Instance = get_Instance(0);
  if (!op_Inequality(Instance, 0, 0))
    return 1;
  v14 = get_Instance(0);
  ClrShortCutPause(v14, 0);
  return 1;
}

// 0x20fc410: s32 SBTL_SET_BATTLE_RESTART(void)
static inline s32 SBTL_SET_BATTLE_RESTART(void) {
  SBTLUNIT_WORK *UserData;
  s64 i;
  SBATTLE_WORK *v6;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s32 ListID;

  UserData = Support_GetUserData();
  RestartBattle();
  wk->scrFlag &= ~1u;
  if (UserData->actwk->status != 34)
  {
    wk->status &= 0xBDFFFFFF;
  }
  for (i = 0; ; ++i)
  {
    v6 = wk;
    UnitMng = v6->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 0x18) != 0 || (pUnit->status & 0x10) != 0)
    {
      sBtlStatusBitOff(pUnit, 0xFFFFFFEF);
    }
    else
    {
      ListID = pUnit->ListID;
      pUnit->vstatus &= ~0x2000000u;
      if (ListID != wk->playerID)
        continue;
      if ((wk->scrFlag & 0x40000) == 0)
        continue;
      pUnit->actwk->status = 2;
    }
  }
  if ((wk->scrFlag & 0x40000) == 0)
    sBtlResetNSTOP();
  wk->scrFlag &= ~0x40000u;
  return 1;
}

// 0x20fc720: s32 SBTL_SET_EFFSTOPCANCEL_FLAG(void)
static inline s32 SBTL_SET_EFFSTOPCANCEL_FLAG(void) {
  wk->scrFlag |= 0x80000u;
  return 1;
}

// 0x20fc790: s32 SBTL_FOLD_EFFSTOPCANCEL_FLAG(void)
static inline s32 SBTL_FOLD_EFFSTOPCANCEL_FLAG(void) {
  wk->scrFlag &= ~0x80000u;
  return 1;
}

// 0x20fc800: s32 SBTL_CHK_EVENT_RUN(void)
static inline s32 SBTL_CHK_EVENT_RUN(void) {
  u32 status;

  status = wk->status;
  scrSetIntReturnValue(((status >> 10) & 1) == 0);
  return 1;
}

// 0x20fc9a0: s32 SBTL_SET_SCRIPT(void)
static inline s32 SBTL_SET_SCRIPT(void) {
  s32 IntPara;
  SBTLUNIT_WORK *Data;
  SBATTLE_WORK *wk_local;
  SBTLACTION_WORK *actwk;
  s32 ListID;

  IntPara = scrGetIntPara(0);
  Data = GetData();
  wk_local = wk;
  wk_local->eventno = 10;
  wk_local->evtload_evtno = IntPara;
  wk_local->eventgstat = 0;
  *(u64 *)&wk_local->eventTheworld = 0;
  actwk = Data->actwk;
  wk_local->status |= 0x400u;
  ListID = Data->ListID;
  actwk->total_homing = 0.0;
  actwk->no_homing = 0;
  wk_local->eventListID = ListID;
  actwk->framecnt = 0;
  actwk->framecntB = 0;
  return 1;
}

// 0x20fcaf0: s32 SBTL_SET_SCRIPT2(void)
static inline s32 SBTL_SET_SCRIPT2(void) {
  s32 IntPara;
  s16 v2;
  s32 v3;
  s32 v4;
  SBTLUNIT_WORK *Data;
  s32 ListID;
  SBTLACTION_WORK *actwk;
  u32 status;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  v3 = scrGetIntPara(2);
  v4 = scrGetIntPara(3);
  Data = GetData();
  ListID = Data->ListID;
  actwk = Data->actwk;
  actwk->total_homing = 0.0;
  actwk->no_homing = 0;
  wk->evtload_evtno = IntPara;
  status = wk->status;
  wk->eventno = v2;
  wk->eventTheworld = v3;
  wk->eventSceneStop = v4;
  wk->eventgstat = 0;
  wk->eventListID = ListID;
  wk->status = status | 0x400;
  actwk->framecnt = 0;
  actwk->framecntB = 0;
  return 1;
}

// 0x20fcc70: s32 SBTL_SET_EXIT(void)
static inline s32 SBTL_SET_EXIT(void) {
  u32 *p_status;
  s64 v5;

  p_status = &wk->status;
  LODWORD(v5) = *(u64 *)p_status | 8;
  HIDWORD(v5) = HIDWORD(*(u64 *)p_status) & 0xEFFFFFFF;
  *(u64 *)p_status = v5;
  sBtlSetEndData();
  return 1;
}

// 0x20fcd30: s32 SBTL_DELETE_UNIT(void)
static inline s32 SBTL_DELETE_UNIT(void) {
  SBTLUNIT_WORK *Data;

  Data = GetData();
  Data->color = 0;
  Data->mode = 9;
  sBtlDeath(Data);
  return 1;
}

// 0x20fcd60: s32 SBTL_DELETE_UNIT_GROUPID(void)
static inline s32 SBTL_DELETE_UNIT_GROUPID(void) {
  s32 IntPara;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v4;

  IntPara = scrGetIntPara(0);
  UnitMng = wk->UnitMng;
  v4 = sBtlSearchUnit_GroupID(UnitMng, IntPara);
  if (v4)
    v4->mode = 9;
  return 1;
}

// 0x20fce70: s32 SBTL_DELETE_ALL(void)
static inline s32 SBTL_DELETE_ALL(void) {
  s64 v1;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  bool v5;

  v1 = 0;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v1 >= UnitMng->number)
      return 1;
    pUnit = UnitMng->pUnitL[v1]->pUnit;
    if (!pUnit)
      goto LABEL_4;
    v5 = sBtlCheckDamageTarget(pUnit);
    if (!v5)
      goto LABEL_4;
    if ((pUnit->side & 2) != 0)
      pUnit->mode = 9;
LABEL_4:
    ++v1;
  }
}

// 0x20fcfc0: s32 SBTL_SET_SEVENT(void)
static inline s32 SBTL_SET_SEVENT(void) {
  SBTLUNIT_WORK *Data;
  s32 IntPara;
  SBATTLE_WORK *v7;
  s32 ListID;
  SBTLACTION_WORK *actwk;

  Data = GetData();
  IntPara = scrGetIntPara(0);
  wk->evtload_evtno = IntPara;
  v7 = wk;
  v7->eventno = 9;
  ListID = Data->ListID;
  v7->eventgstat = 0;
  v7->eventListID = ListID;
  v7->status |= 0x400u;
  actwk = Data->actwk;
  actwk->framecnt = 0;
  actwk->framecntB = 0;
  actwk->total_homing = 0.0;
  actwk->no_homing = 0;
  return 1;
}

// 0x20fd0c0: s32 SBTL_SET_EVENT_UNIT(void)
static inline s32 SBTL_SET_EVENT_UNIT(void) {
  s32 IntPara;
  s32 v2;
  SBTLUNIT_WORK *NakamaData;
  SBTLUNIT_WORK *p_scrEventUnit;

  IntPara = scrGetIntPara(0);
  if (IntPara == -3)
  {
    NakamaData = Support_GetNakamaData(0);
    if (NakamaData)
      goto LABEL_12;
  }
  else
  {
    v2 = IntPara;
    if (IntPara != -2)
    {
      if (IntPara == -1)
      {
        NakamaData = GetData();
      }
      else
      {
        NakamaData = wk->scrUnitList[v2];
      }
      goto LABEL_14;
    }
  }
  NakamaData = Support_GetUserData();
LABEL_12:
LABEL_14:
  p_scrEventUnit = &wk->scrEventUnit;
  p_scrEventUnit = NakamaData;
  return 1;
}

// 0x20fd200: s32 SBTL_SET_GENERAL_CUTIN(void)
static inline s32 SBTL_SET_GENERAL_CUTIN(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  wk->scrCutinID = IntPara;
  return 1;
}

// 0x20fd2a0: s32 SBTL_SET_GENERAL_MESSAGE(void)
static inline s32 SBTL_SET_GENERAL_MESSAGE(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  wk->scrMsgID = IntPara;
  return 1;
}

// 0x20fd340: s32 SBTL_GET_GENERAL_CUTIN(void)
static inline s32 SBTL_GET_GENERAL_CUTIN(void) {
  s32 scrCutinID;

  scrCutinID = wk->scrCutinID;
  scrSetIntReturnValue(scrCutinID);
  return 1;
}

// 0x20fd410: s32 SBTL_GET_GENERAL_MESSAGE(void)
static inline s32 SBTL_GET_GENERAL_MESSAGE(void) {
  s32 scrMsgID;

  scrMsgID = wk->scrMsgID;
  scrSetIntReturnValue(scrMsgID);
  return 1;
}

// 0x20fd4e0: s32 SBTL_SET_ZOOM_UNIT(void)
static inline s32 SBTL_SET_ZOOM_UNIT(void) {
  SBTLUNIT_WORK *scrEventUnit;
  f32 FloatPara;
  s32 IntPara;
  SBTLVISUAL_DATA *v5;
  sdatUnitWork_t *para;
  s32 devilid;
  SBATTLE_WORK *v9;
  SBTLUNIT_WORK *v10;
  struct sdfVector4_t v12;
  sdfVector4_t v14;
  float32x4_t v15;
  s32 scrFlag;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;
  long f64 v25;
  f32 y;
  f32 v27;
  s64 v28;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 v33;
  SBTLUNIT_WORK *v36;
  sdfVector4_t vct_A_local;
  f32 v39;
  f32 v41;
  s64 v43;
  s64 v44;
  SBTLUNIT_WORK *v47;
  struct sdfVector4_t v52;
  struct sdfVector4_t v53;
  struct sdfVector4_t v56;
  struct sdfVector4_t v57;
  struct sdfVector4_t v58;
  struct sdfVector4_t v59;
  unsigned __int128 v60;
  sdfVector4_t v62;
  sdfVector4_t v63;

  scrEventUnit = wk->scrEventUnit;
  FloatPara = scrGetFloatPara(0);
  IntPara = scrGetIntPara(1);
  v5 = Allocate(SBTLVISUAL_DATA);
  para = scrEventUnit->para;
  v60 = 0u;
  devilid = (u16)para->devilid;
  if (devilid != 305 && devilid != 268)
  {
LABEL_39:
    if (devilid != 305 && devilid != 268)
      goto LABEL_44;
    scrFlag = wk->scrFlag;
    if ((scrFlag & 0x40) == 0)
    {
      devilid = (u16)scrEventUnit->para->devilid;
LABEL_44:
      if ((u32)(devilid - 268) > 0x25 || ((1 << ((u8)devilid - 12)) & 0x3000000003LL) == 0)
      {
LABEL_51:
        if (devilid != 257)
          goto LABEL_55;
        if (wk->scrStep)
        {
          devilid = (u16)scrEventUnit->para->devilid;
LABEL_55:
          if (devilid <= 311)
          {
            if (devilid != 259)
            {
              if (devilid == 293)
              {
                sBtlGetCylinderData(scrEventUnit, v5);
                v21 = v5->center.x;
                v22 = v5->center.y;
                v24 = v5->center.z;
                v23 = v5->center.w;
                *(__n128 *)&v25 = sub_1B332C0(0, v21, v22, v24, v23);
                sub_1B335A0(&v60, 0, v25);
                y = scrEventUnit->pos.y;
                *((f32 *)&v60 + 1) = y;
                v27 = *(f32 *)&v60;
                v28 = *((u64 *)&v60 + 1);
                v62.x = v27;
                v62.y = y;
                *(u64 *)&v62.z = v28;
                goto LABEL_142;
              }
LABEL_71:
              sBtlGetCylinderData(scrEventUnit, v5);
              v30 = v5->center.x;
              v31 = v5->center.y;
              v33 = v5->center.z;
              v32 = v5->center.w;
              v63.x = v30;
              v63.y = v31;
              v63.z = v33;
              v63.w = v32;
              sBtlSetZoom2(v63, FloatPara, IntPara);
              goto LABEL_78;
            }
            sBtlGetCylinderData(scrEventUnit, v5);
            v58 = v5->center;
            vct_A = v58;
            vct_A_local = vct_A;
            v39 = 200.0;
            goto LABEL_139;
          }
          if (devilid != 312)
          {
            if (devilid != 313)
              goto LABEL_71;
            v36 = wk->scrUnitList[0];
            sBtlGetCylinderData(v36, v5);
            v56 = v5->center;
            vct_A = v56;
            vct_A_local = vct_A;
            v39 = 420.0;
            goto LABEL_139;
          }
          v47 = wk->scrUnitList[0];
          sBtlGetCylinderData(v47, v5);
          v59 = v5->center;
          vct_A = v59;
          vct_A_local = vct_A;
          v39 = 75.0;
LABEL_139:
          v60 = vct_A_local;
          v44 = *(u64 *)&vct_A_local.x;
          v41 = vct_A_local.x + v39;
          v43 = *(u64 *)&vct_A_local.z;
LABEL_141:
          v62.x = v41;
          v62.y = *((f32 *)&v44 + 1);
          *(u64 *)&v62.z = v43;
LABEL_142:
          sBtlSetZoom2(v62, FloatPara, IntPara);
          return 1;
        }
        sBtlGetCylinderData(scrEventUnit, v5);
        v57 = v5->center;
        vct_A = v57;
        v60 = vct_A;
        v41 = *(f32 *)&v60;
        v43 = *((u64 *)&v60 + 1);
        *((f32 *)&v44 + 1) = *((f32 *)&v60 + 1) + 40.0;
        goto LABEL_141;
      }
      if ((wk->scrFlag & 0x80) == 0)
      {
        devilid = (u16)scrEventUnit->para->devilid;
        goto LABEL_51;
      }
      SetAction(11);
      goto LABEL_71;
    }
    scrFlag = wk->scrFlag;
    scrEventUnit = wk->scrUnitList[2];
    wk->scrFlag = scrFlag & 0xFFFFFFBF;
    goto LABEL_71;
  }
  v9 = wk;
  if (v9->scrStep == 3)
    goto LABEL_11;
  goto LABEL_38;
  if (v9->scrStep != 3)
  {
LABEL_38:
    devilid = (u16)scrEventUnit->para->devilid;
    goto LABEL_39;
  }
LABEL_11:
  v9 = wk;
  v10 = v9->scrUnitList[2];
  sBtlGetCylinderData(scrEventUnit, v5);
  v52 = v5->center;
  vct_A = v52;
  v60 = vct_A;
  sBtlGetCylinderData(v10, v5);
  v12 = v5->center;
  vct_A = v12;
  v53 = vct_A;
  v14 = (sdfVector4_t)v60;
  vct_A = v14;
  vct_B = v53;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v15.n128_u64[0] = 0x3F0000003F000000LL;
  v15.n128_u64[1] = 0x3F0000003F000000LL;
  vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, v15);
  v60 = vct_A;
  sBtlSetZoom2((sdfVector4_t)v60, FloatPara, IntPara);
LABEL_78:
  wk->scrFlag |= 4u;
  return 1;
}

// 0x20fe1a0: s32 SBTL_SET_ZOOM_DEFAULT(void)
static inline s32 SBTL_SET_ZOOM_DEFAULT(void) {
  s32 IntPara;
  s32 scrFlag;

  IntPara = scrGetIntPara(0);
  scrFlag = wk->scrFlag;
  if ((scrFlag & 8) == 0)
  {
    sBtlDefaultZoom2(IntPara);
    return 1;
  }
  wk->scrFlag = scrFlag & 0xFFFFFFFB;
  return 1;
}

// 0x20fe2d0: s32 SBTL_SET_ZOOM_RATIO(void)
static inline s32 SBTL_SET_ZOOM_RATIO(void) {
  wk->scrZoomRatio = scrGetFloatPara(0);
  return 1;
}

// 0x20fe390: s32 SBTL_GET_ZOOM_RATIO(void)
static inline s32 SBTL_GET_ZOOM_RATIO(void) {
  f32 scrZoomRatio;

  scrZoomRatio = wk->scrZoomRatio;
  scrSetFloatReturnValue(scrZoomRatio);
  return 1;
}

// 0x20fe460: s32 SBTL_SET_ZOOM_FRAME(void)
static inline s32 SBTL_SET_ZOOM_FRAME(void) {
  wk->scrZoomFrame = scrGetIntPara(0);
  return 1;
}

// 0x20fe520: s32 SBTL_GET_ZOOM_FRAME(void)
static inline s32 SBTL_GET_ZOOM_FRAME(void) {
  s32 scrZoomFrame;

  scrZoomFrame = wk->scrZoomFrame;
  scrSetIntReturnValue(scrZoomFrame);
  return 1;
}

// 0x20fe5f0: s32 SBTL_SET_ZOOMOUT_FRAME(void)
static inline s32 SBTL_SET_ZOOMOUT_FRAME(void) {
  wk->scrZoomOutFrame = scrGetIntPara(0);
  return 1;
}

// 0x20fe6b0: s32 SBTL_GET_ZOOMOUT_FRAME(void)
static inline s32 SBTL_GET_ZOOMOUT_FRAME(void) {
  s32 scrZoomOutFrame;

  scrZoomOutFrame = wk->scrZoomOutFrame;
  scrSetIntReturnValue(scrZoomOutFrame);
  return 1;
}

// 0x20fe780: s32 SBTL_SET_CUTSCROLL_UNIT(void)
static inline s32 SBTL_SET_CUTSCROLL_UNIT(void) {
  SBTLUNIT_WORK *Data;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  sdfVector4_t v7;

  Data = GetData();
  x = Data->pos.x;
  y = Data->pos.y;
  z = Data->pos.z;
  w = Data->pos.w;
  v7.x = x;
  v7.y = y;
  v7.z = z;
  v7.w = w;
  sBtlSetCutScroll(v7);
  return 1;
}

// 0x20fe810: s32 SBTL_SET_CUTSCROLL_DEFAULT(void)
static inline s32 SBTL_SET_CUTSCROLL_DEFAULT(void) {
  sBtlDefaultCutScroll();
  return 1;
}

// 0x20fe890: s32 SBTL_RESTART_EFFECT(void)
static inline s32 SBTL_RESTART_EFFECT(void) {
  if ((wk->status & 0x8000000) == 0)
    return 1;
  effStopEffectStop();
  wk->status &= ~0x8000000u;
  return 1;
}

// 0x20fe960: s32 AI_RUN_AUTOPROCESS(void)
static inline s32 AI_RUN_AUTOPROCESS(void) {
  SBTLUNIT_WORK *Data;
  SBTLACTAI_WORK *actaiwk;
  u32 status;

  Data = GetData();
  Support_RunZoomProcess();
  Data->aiwk->scr_actcheckflg = 1;
  if (!!IsSceanStop())
  {
    if ((Data->status & 0x10) == 0)
      goto LABEL_10;
  }
  ++Data->aiwk->scrAutoCnt;
  if (Support_RunWarpProcess() || Support_RunWaitProcess())
  {
LABEL_10:
LABEL_12:
    scrSetIntReturnValue(1);
    return 1;
  }
  if (Data->actwk->status == 10 && (Data->aiwk->scrflag & 0x40000) == 0)
    goto LABEL_29;
  if (Support_RunDownProcess() == 1)
    goto LABEL_10;
  actaiwk = Data->actaiwk;
  if (actaiwk->dataflg == 1)
  {
    if (Data->aiwk->stat == 1 && actaiwk->stat == 2)
    {
      sBtlUseTableDataProc(Data);
    }
LABEL_29:
    scrSetIntReturnValue(1);
    Data->aiwk->scr_actcheckflg = 1;
    return 1;
  }
  if (RunReactProcess() == 1)
  {
    Data->aiwk->scr_actcheckflg = 1;
    goto LABEL_12;
  }
  if ((Data->actaiwk->mode & 0xFFFFFFFE) != 0xC)
    goto LABEL_29;
  if (Data->mode == 9)
    goto LABEL_29;
  status = Data->actwk->status;
  if (status <= 0x21 && ((1 << status) & 0x200800380LL) != 0)
    goto LABEL_29;
  Data->aiwk->scr_actcheckflg = 1;
  scrSetIntReturnValue(0);
  return 1;
}

// 0x20febe0: s32 AI_SET_LIST_UNIT(void)
static inline s32 AI_SET_LIST_UNIT(void) {
  SBTLUNIT_WORK *Data;
  s32 IntPara;
  SBTLUNIT_WORK *scrUnitList;
  SBTLUNIT_WORK *v5;
  SBTLUNIT_WORK *v6;
  Il2CppClass **v7;

  Data = GetData();
  IntPara = scrGetIntPara(0);
  scrUnitList = wk->scrUnitList;
  v5 = GetData();
  v6 = v5;
  v7 = &scrUnitList->obj.klass + IntPara;
  v7[4] = v6;
  ++wk->scrUnitNum;
  Data->aiwk->scrListID = IntPara;
  return 1;
}

// 0x20fed00: s32 AI_CHK_LIST_UNIT(void)
static inline s32 AI_CHK_LIST_UNIT(void) {
  s32 IntPara;
  s32 v3;
  SBTLUNIT_WORK *Data;
  s32 v7;

  IntPara = scrGetIntPara(0);
  if (IntPara == -1)
  {
    Data = GetData();
    if (Data)
      goto LABEL_7;
    goto LABEL_13;
  }
  v3 = IntPara;
  Data = wk->scrUnitList[v3];
  if (Data)
  {
LABEL_7:
    if (Data->actwk->status == 10)
    {
      v7 = -2;
      goto LABEL_15;
    }
    if (sBtlCheckDamageTarget(Data))
    {
      if (Data->actwk->status == 7)
        v7 = 2;
      else
        v7 = 1;
      goto LABEL_15;
    }
    v7 = -1;
    goto LABEL_15;
  }
LABEL_13:
  v7 = -3;
LABEL_15:
  scrSetIntReturnValue(v7);
  return 1;
}

// 0x20feeb0: s32 AI_CHK_LIST_COUNT(void)
static inline s32 AI_CHK_LIST_COUNT(void) {
  s64 v2;
  s32 max_length;
  SBTLUNIT_WORK *scrUnitList;
  SBTLUNIT_WORK *v5;

  v2 = 0;
  max_length = wk->scrUnitList->max_length;
  while (1)
  {
    scrUnitList = wk->scrUnitList;
    if (v2 >= SLODWORD(scrUnitList->max_length))
      break;
    v5 = scrUnitList[v2];
    if (!v5)
      goto LABEL_6;
    if (v5->actwk->status == 10)
LABEL_6:
      --max_length;
    ++v2;
  }
  scrSetIntReturnValue(max_length);
  return 1;
}

// 0x20feff0: s32 AI_GET_LIST_STEP(void)
static inline s32 AI_GET_LIST_STEP(void) {
  s32 IntPara;
  s32 v2;
  SBTLUNIT_WORK *v4;
  s32 scrStep3;

  IntPara = scrGetIntPara(1);
  v2 = scrGetIntPara(0);
  v4 = wk->scrUnitList[v2];
  switch (IntPara)
  {
    case 3:
      scrStep3 = v4->aiwk->scrStep3;
      goto LABEL_16;
    case 2:
      scrStep3 = v4->aiwk->scrStep2;
LABEL_16:
      scrSetIntReturnValue(scrStep3);
      return 1;
    case 1:
      scrStep3 = v4->aiwk->scrStep;
      goto LABEL_16;
  }
  return 1;
}

// 0x20ff120: s32 AI_SET_LIST_STEP(void)
static inline s32 AI_SET_LIST_STEP(void) {
  s32 IntPara;
  s32 v2;
  s32 v3;
  SBTLUNIT_WORK *v5;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  v3 = scrGetIntPara(2);
  v5 = wk->scrUnitList[IntPara];
  if (!v5)
    return 1;
  if (v3 == 3)
  {
    v5->aiwk->scrStep3 = v2;
    return 1;
  }
  else
  {
    if (v3 != 2)
    {
      if (v3 == 1)
        v5->aiwk->scrStep = v2;
      return 1;
    }
    v5->aiwk->scrStep2 = v2;
    return 1;
  }
}

// 0x20ff250: s32 AI_GET_COUNTER(void)
static inline s32 AI_GET_COUNTER(void) {
  s32 scrAutoCnt;

  scrAutoCnt = GetData()->aiwk->scrAutoCnt;
  scrSetIntReturnValue(scrAutoCnt);
  return 1;
}

// 0x20ff2c0: s32 AI_SET_COUNTER(void)
static inline s32 AI_SET_COUNTER(void) {
  SBTLAI_WORK *aiwk;

  aiwk = GetData()->aiwk;
  aiwk->scrAutoCnt = scrGetIntPara(0);
  return 1;
}

// 0x20ff330: s32 AI_GET_CMPCOUNTER(void)
static inline s32 AI_GET_CMPCOUNTER(void) {
  s32 scrCmpCnt;

  scrCmpCnt = GetData()->aiwk->scrCmpCnt;
  scrSetIntReturnValue(scrCmpCnt);
  return 1;
}

// 0x20ff3a0: s32 AI_SET_CMPCOUNTER(void)
static inline s32 AI_SET_CMPCOUNTER(void) {
  SBTLAI_WORK *aiwk;

  aiwk = GetData()->aiwk;
  aiwk->scrCmpCnt = scrGetIntPara(0);
  return 1;
}

// 0x20ff410: s32 AI_SET_CMPCOUNTER_ALL(void)
static inline s32 AI_SET_CMPCOUNTER_ALL(void) {
  wk->scrCmpCnt = scrGetIntPara(0);
  return 1;
}

// 0x20ff4d0: s32 AI_GET_CMPCOUNTER_ALL(void)
static inline s32 AI_GET_CMPCOUNTER_ALL(void) {
  s32 scrCmpCnt;

  scrCmpCnt = wk->scrCmpCnt;
  scrSetIntReturnValue(scrCmpCnt);
  return 1;
}

// 0x20ff5a0: s32 AI_SET_COUNTER_ALL(void)
static inline s32 AI_SET_COUNTER_ALL(void) {
  s32 IntPara;
  s32 *scrCnt;

  IntPara = scrGetIntPara(1);
  scrCnt = wk->scrCnt;
  scrCnt[IntPara] = scrGetIntPara(0);
  return 1;
}

// 0x20ff650: s32 AI_GET_COUNTER_ALL(void)
static inline s32 AI_GET_COUNTER_ALL(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  scrSetIntReturnValue(wk->scrCnt[IntPara]);
  return 1;
}

// 0x20ff700: s32 AI_SET_ENSHUTU_COUNTER(void)
static inline s32 AI_SET_ENSHUTU_COUNTER(void) {
  s32 IntPara;
  s32 v2;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  wk->enshutuCnt[v2] = IntPara;
  return 1;
}

// 0x20ff7c0: s32 AI_GET_ENSHUTU_COUNTER(void)
static inline s32 AI_GET_ENSHUTU_COUNTER(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  scrSetIntReturnValue(wk->enshutuCnt[IntPara]);
  return 1;
}

// 0x20ff870: s32 AI_SET_ENSHUTU_CMPCOUNTER(void)
static inline s32 AI_SET_ENSHUTU_CMPCOUNTER(void) {
  s32 IntPara;
  s32 v2;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  wk->enshutuCmpCnt[v2] = IntPara;
  return 1;
}

// 0x20ff930: s32 AI_GET_ENSHUTU_CMPCOUNTER(void)
static inline s32 AI_GET_ENSHUTU_CMPCOUNTER(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  scrSetIntReturnValue(wk->enshutuCmpCnt[IntPara]);
  return 1;
}

// 0x20ff9e0: s32 AI_GET_ENCOUNTNO(void)
static inline s32 AI_GET_ENCOUNTNO(void) {
  s32 scrEncountNo;

  scrEncountNo = wk->scrEncountNo;
  scrSetIntReturnValue(scrEncountNo);
  return 1;
}

// 0x20ffab0: s32 AI_GET_GROUPID(void)
static inline s32 AI_GET_GROUPID(void) {
  s32 GroupID;

  GroupID = GetData()->GroupID;
  scrSetIntReturnValue(GroupID);
  return 1;
}

// 0x20ffb20: s32 SBTLE_SET_ENDEVT(void)
static inline s32 SBTLE_SET_ENDEVT(void) {
  GetData();
  return 1;
}

// 0x20ffb40: s32 AI_CHK_MYHP(void)
static inline s32 AI_CHK_MYHP(void) {
  SBTLUNIT_WORK *Data;
  s32 IntPara;
  sdatParaWork_t *now;
  s32 hp;
  s64 v5;
  s32 v6;

  Data = GetData();
  IntPara = scrGetIntPara(0);
  now = Data->para->now;
  hp = now->hp;
  if (!IntPara)
  {
    v6 = hp == 0;
    goto LABEL_8;
  }
  v5 = 1374389535 * now->maxhp * IntPara;
  v6 = hp <= (s32)((v5 >> 37) + ((u64)v5 >> 63));
LABEL_8:
  scrSetIntReturnValue(v6);
  return 1;
}

// 0x20ffc20: s32 AI_CHK_MYHP_LESS(void)
static inline s32 AI_CHK_MYHP_LESS(void) {
  SBTLUNIT_WORK *Data;
  s32 IntPara;
  sdatParaWork_t *now;
  s32 hp;
  s32 maxhp;

  Data = GetData();
  IntPara = scrGetIntPara(0);
  now = Data->para->now;
  hp = now->hp;
  maxhp = now->maxhp;
  scrSetIntReturnValue(100 * hp < maxhp * IntPara);
  return 1;
}

// 0x20ffcd0: s32 AI_CHK_USER_HP(void)
static inline s32 AI_CHK_USER_HP(void) {
  SBTLUNIT_WORK *UserData;
  s32 IntPara;
  sdatParaWork_t *now;
  s32 hp;
  s32 maxhp;

  UserData = Support_GetUserData();
  IntPara = scrGetIntPara(0);
  now = UserData->para->now;
  hp = now->hp;
  maxhp = now->maxhp;
  scrSetIntReturnValue(100 * hp / maxhp <= IntPara);
  return 1;
}

// 0x20ffd80: s32 AI_CHK_USER_MAG_GOE(void)
static inline s32 AI_CHK_USER_MAG_GOE(void) {
  s32 IntPara;
  s32 mag;
  s32 magMax;

  IntPara = scrGetIntPara(0);
  if (wk->mag)
  {
    goto LABEL_9;
  }
  scrSetIntReturnValue(0);
LABEL_9:
  mag = wk->mag;
  magMax = wk->magMax;
  scrSetIntReturnValue(100 * mag / magMax >= IntPara);
  return 1;
}

// 0x20ffeb0: s32 AI_CHK_HP_TARGET(void)
static inline s32 AI_CHK_HP_TARGET(void) {
  s32 IntPara;
  s32 v3;
  SBTLUNIT_WORK *NakamaData;
  s32 v7;

  IntPara = scrGetIntPara(1);
  if (IntPara == -3)
  {
    NakamaData = Support_GetNakamaData(0);
    goto LABEL_18;
  }
  v3 = IntPara;
  if (IntPara == -2)
  {
    NakamaData = Support_GetUserData();
    goto LABEL_18;
  }
  if (IntPara == -1)
  {
    NakamaData = GetData();
    goto LABEL_18;
  }
  NakamaData = wk->scrUnitList[v3];
LABEL_18:
  v7 = scrGetIntPara(0);
  if (NakamaData)
    LODWORD(NakamaData) = 100
                        * NakamaData->para->now->hp
                        / NakamaData->para->now->maxhp <= v7;
  scrSetIntReturnValue((s32)NakamaData);
  return 1;
}

// 0x2100050: s32 AI_CHK_NAKAMA(void)
static inline s32 AI_CHK_NAKAMA(void) {
  s32 IntPara;
  SBTLUNIT_WORK *NakamaData;

  IntPara = scrGetIntPara(0);
  NakamaData = Support_GetNakamaData(IntPara);
  scrSetIntReturnValue(NakamaData != 0);
  return 1;
}

// 0x21000e0: s32 AI_CHK_MV(void)
static inline s32 AI_CHK_MV(void) {
  SBTLUNIT_WORK *Data;
  s32 mode;

  Data = GetData();
  mode = Data->actaiwk->mode;
  scrSetIntReturnValue((mode & 0xFFFFFFFE) == 12);
  Data->aiwk->scr_actcheckflg = 1;
  return 1;
}

// 0x2100170: s32 AI_SET_THEWORLD(void)
static inline s32 AI_SET_THEWORLD(void) {
  s32 IntPara;
  s32 v3;
  SBTLUNIT_WORK *Data;

  IntPara = scrGetIntPara(0);
  if (IntPara != -3)
  {
    v3 = IntPara;
    if (IntPara != -1)
    {
      Data = wk->scrUnitList[v3];
      goto LABEL_12;
    }
    Data = GetData();
LABEL_12:
    sBtlStatusBitOn(Data, 0x10u);
    return 1;
  }
  Data = Support_GetNakamaData(0);
  if (Data)
  {
    goto LABEL_12;
  }
  return 1;
}

// 0x21002d0: s32 AI_UNSET_THEWORLD(void)
static inline s32 AI_UNSET_THEWORLD(void) {
  s32 IntPara;
  s32 v3;
  SBTLUNIT_WORK *Data;

  IntPara = scrGetIntPara(0);
  if (IntPara == -1)
  {
    Data = GetData();
    goto LABEL_7;
  }
  v3 = IntPara;
  Data = wk->scrUnitList[v3];
  if (!Data)
    return 1;
LABEL_7:
  sBtlStatusBitOff(Data, 0xFFFFFFEF);
  return 1;
}

// 0x2100410: s32 AI_SET_AISYO(void)
static inline s32 AI_SET_AISYO(void) {
  s32 IntPara;
  s32 v2;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  Support_SetAisyo(IntPara, v2);
  return 1;
}

// 0x2100600: s32 AI_SET_PARA(void)
static inline s32 AI_SET_PARA(void) {
  s32 IntPara;
  s32 v2;
  signed s32 v3;
  s32 v4;
  SBTLUNIT_WORK *NakamaData;
  sdatParaWork_t *now;
  signed s32 maxhp;
  sdatUnitWork_t *para;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  v3 = scrGetIntPara(2);
  switch (IntPara)
  {
    case -4:
      v4 = 1;
      goto LABEL_12;
    case -3:
      v4 = 0;
LABEL_12:
      NakamaData = Support_GetNakamaData(v4);
      if (!NakamaData)
        return 1;
      goto LABEL_17;
    case -2:
      NakamaData = Support_GetUserData();
      if (!NakamaData)
        return 1;
      goto LABEL_17;
    case -1:
      NakamaData = GetData();
      if (NakamaData)
        goto LABEL_17;
      return 1;
    default:
      NakamaData = wk->scrUnitList[IntPara];
      if (!NakamaData)
        return 1;
LABEL_17:
      if (v2 != 1)
      {
        if (!v2)
        {
          now = NakamaData->para->now;
          maxhp = now->maxhp;
          if (v3 == -1)
          {
            now->hp = maxhp;
            return 1;
          }
          else
          {
            if (v3 < maxhp)
              maxhp = v3;
            now->hp = maxhp;
            return 1;
          }
        }
        return 1;
      }
      para = NakamaData->para;
      if (sBtlGetBadStatus(para) == 17)
        return 1;
      if (v3 == 9 || v3 == 5)
      {
        sBtlScriptSub_ResetBadStatus(NakamaData);
      }
      else if (v3 == -1)
      {
        sBtlScriptSub_ResetBadStatus(NakamaData);
        return 1;
      }
      sBtlSetBadStatus_No(NakamaData, 0, v3, 0, -1);
      return 1;
  }
}

// 0x2100880: s32 AI_GET_PARA(void)
static inline s32 AI_GET_PARA(void) {
  s32 IntPara;
  s32 v2;
  s32 v3;
  SBTLUNIT_WORK *NakamaData;
  s32 v6;
  s32 hp;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  v3 = scrGetIntPara(2);
  switch (IntPara)
  {
    case -4:
      NakamaData = Support_GetNakamaData(1);
      if (!NakamaData)
        goto LABEL_13;
      goto LABEL_16;
    case -3:
      NakamaData = Support_GetNakamaData(0);
      if (NakamaData)
        goto LABEL_16;
LABEL_13:
      hp = 0;
LABEL_30:
      scrSetIntReturnValue(hp);
      return 1;
    case -2:
      NakamaData = Support_GetUserData();
LABEL_16:
      v6 = v2 - 1;
      goto LABEL_17;
    case -1:
      NakamaData = GetData();
      v6 = v2 - 1;
      if ((u32)(v2 - 1) > 3)
        return 1;
      goto LABEL_17;
    default:
      NakamaData = wk->scrUnitList[IntPara];
      v6 = v2 - 1;
      if ((u32)(v2 - 1) <= 3)
      {
LABEL_17:
        switch (v6)
        {
          case 0:
            hp = (NakamaData->para->badstatus & v3) != 0;
            goto LABEL_30;
          case 1:
            hp = NakamaData->actwk->status == 8;
            goto LABEL_30;
          case 2:
            hp = NakamaData->para->now->hp;
            goto LABEL_30;
          case 3:
            hp = sBtlCheckEnableUseKaja(NakamaData, v3) > 0;
            goto LABEL_30;
          default:
            return 1;
        }
      }
      return 1;
  }
}

// 0x2100ae0: s32 AI_SET_ADDCNT(void)
static inline s32 AI_SET_ADDCNT(void) {
  SBTLAI_WORK *aiwk;

  aiwk = GetData()->aiwk;
  aiwk->act_p = scrGetIntPara(0);
  return 1;
}

// 0x2100b50: s32 AI_GET_ADDCNT(void)
static inline s32 AI_GET_ADDCNT(void) {
  s32 act_p;

  act_p = GetData()->aiwk->act_p;
  scrSetIntReturnValue(act_p);
  return 1;
}

// 0x2100bc0: s32 AI_SET_STEP(void)
static inline s32 AI_SET_STEP(void) {
  SBTLAI_WORK *aiwk;

  aiwk = GetData()->aiwk;
  aiwk->scrStep = scrGetIntPara(0);
  return 1;
}

// 0x2100c30: s32 AI_ADD_STEP(void)
static inline s32 AI_ADD_STEP(void) {
  SBTLAI_WORK *aiwk;
  s32 scrStep;

  aiwk = GetData()->aiwk;
  scrStep = aiwk->scrStep;
  aiwk->scrStep = scrGetIntPara(0) + scrStep;
  return 1;
}

// 0x2100cb0: s32 AI_GET_STEP(void)
static inline s32 AI_GET_STEP(void) {
  s32 scrStep;

  scrStep = GetData()->aiwk->scrStep;
  scrSetIntReturnValue(scrStep);
  return 1;
}

// 0x2100d20: s32 AI_SET_STEP2(void)
static inline s32 AI_SET_STEP2(void) {
  SBTLAI_WORK *aiwk;

  aiwk = GetData()->aiwk;
  aiwk->scrStep2 = scrGetIntPara(0);
  return 1;
}

// 0x2100d90: s32 AI_ADD_STEP2(void)
static inline s32 AI_ADD_STEP2(void) {
  SBTLAI_WORK *aiwk;
  s32 scrStep2;

  aiwk = GetData()->aiwk;
  scrStep2 = aiwk->scrStep2;
  aiwk->scrStep2 = scrGetIntPara(0) + scrStep2;
  return 1;
}

// 0x2100e10: s32 AI_GET_STEP2(void)
static inline s32 AI_GET_STEP2(void) {
  s32 scrStep2;

  scrStep2 = GetData()->aiwk->scrStep2;
  scrSetIntReturnValue(scrStep2);
  return 1;
}

// 0x2100e80: s32 AI_SET_STEP3(void)
static inline s32 AI_SET_STEP3(void) {
  SBTLAI_WORK *aiwk;

  aiwk = GetData()->aiwk;
  aiwk->scrStep3 = scrGetIntPara(0);
  return 1;
}

// 0x2100ef0: s32 AI_ADD_STEP3(void)
static inline s32 AI_ADD_STEP3(void) {
  SBTLAI_WORK *aiwk;
  s32 scrStep3;

  aiwk = GetData()->aiwk;
  scrStep3 = aiwk->scrStep3;
  aiwk->scrStep3 = scrGetIntPara(0) + scrStep3;
  return 1;
}

// 0x2100f70: s32 AI_GET_STEP3(void)
static inline s32 AI_GET_STEP3(void) {
  s32 scrStep3;

  scrStep3 = GetData()->aiwk->scrStep3;
  scrSetIntReturnValue(scrStep3);
  return 1;
}

// 0x2100fe0: s32 AI_SET_STEPn(void)
static inline s32 AI_SET_STEPn(void) {
  s32 *scrStepN;
  s32 IntPara;

  scrStepN = GetData()->aiwk->scrStepN;
  IntPara = scrGetIntPara(0);
  scrStepN[IntPara] = scrGetIntPara(1);
  return 1;
}

// 0x2101070: s32 AI_ADD_STEPn(void)
static inline s32 AI_ADD_STEPn(void) {
  s32 *scrStepN;
  char *v2;
  s32 v3;

  scrStepN = GetData()->aiwk->scrStepN;
  v2 = (char *)scrStepN + 4 * scrGetIntPara(0);
  v3 = *((u32 *)v2 + 8);
  *((u32 *)v2 + 8) = scrGetIntPara(1) + v3;
  return 1;
}

// 0x2101100: s32 AI_GET_STEPn(void)
static inline s32 AI_GET_STEPn(void) {
  s32 *scrStepN;
  s32 IntPara;

  scrStepN = GetData()->aiwk->scrStepN;
  IntPara = scrGetIntPara(0);
  scrSetIntReturnValue(scrStepN[IntPara]);
  return 1;
}

// 0x2101180: s32 AI_SET_STEP_ALL(void)
static inline s32 AI_SET_STEP_ALL(void) {
  wk->scrStep = scrGetIntPara(0);
  return 1;
}

// 0x2101240: s32 AI_GET_STEP_ALL(void)
static inline s32 AI_GET_STEP_ALL(void) {
  s32 scrStep;

  scrStep = wk->scrStep;
  scrSetIntReturnValue(scrStep);
  return 1;
}

// 0x2101310: s32 AI_SET_FLAG_ALL(void)
static inline s32 AI_SET_FLAG_ALL(void) {
  s32 IntPara;
  s32 v2;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  if (v2)
  {
    wk->scrFlag |= IntPara;
    return 1;
  }
  else
  {
    wk->scrFlag &= ~IntPara;
    return 1;
  }
}

// 0x2101400: s32 AI_CHK_FLAG_ALL(void)
static inline s32 AI_CHK_FLAG_ALL(void) {
  s32 IntPara;
  s32 scrFlag;

  IntPara = scrGetIntPara(0);
  scrFlag = wk->scrFlag;
  scrSetIntReturnValue((scrFlag & IntPara) != 0);
  return 1;
}

// 0x21014e0: s32 AI_SET_FLAG(void)
static inline s32 AI_SET_FLAG(void) {
  s32 IntPara;
  s32 v2;
  s32 v3;
  s32 v4;
  SBTLUNIT_WORK *Data;
  SBTLAI_WORK *aiwk;
  s32 result;
  u32 scrflag;
  s32 v10;
  s32 v11;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  v3 = scrGetIntPara(2);
  if (v3 == -1)
  {
    Data = GetData();
  }
  else
  {
    v4 = v3;
    Data = wk->scrUnitList[v4];
  }
  aiwk = Data->aiwk;
  result = 1;
  scrflag = aiwk->scrflag;
  v10 = scrflag | IntPara;
  v11 = scrflag & ~IntPara;
  if (v2)
    v11 = v10;
  aiwk->scrflag = v11;
  return result;
}

// 0x21015e0: s32 AI_CHK_FLAG(void)
static inline s32 AI_CHK_FLAG(void) {
  s32 IntPara;
  s32 v2;
  s32 v3;
  SBTLAI_WORK *v5;
  u32 scrflag;
  SBTLAI_WORK *aiwk;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  if (v2 == -1)
  {
    aiwk = GetData()->aiwk;
    scrflag = aiwk->scrflag;
    goto LABEL_10;
  }
  v3 = v2;
  v5 = wk->scrUnitList[v3]->aiwk;
  scrflag = v5->scrflag;
LABEL_10:
  scrSetIntReturnValue((scrflag & IntPara) != 0);
  return 1;
}

// 0x21016f0: s32 AI_SET_MAINFLAG(void)
static inline s32 AI_SET_MAINFLAG(void) {
  s32 IntPara;
  s32 v2;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  if (v2)
  {
    wk->status |= IntPara;
    return 1;
  }
  else
  {
    wk->status &= ~IntPara;
    return 1;
  }
}

// 0x21017e0: s32 AI_SET_ACTCHECK(void)
static inline s32 AI_SET_ACTCHECK(void) {
  s32 IntPara;
  s32 v3;
  SBTLUNIT_WORK *Data;

  IntPara = scrGetIntPara(0);
  if (IntPara == -1)
  {
    Data = GetData();
    if (!Data)
      return 1;
    goto LABEL_7;
  }
  v3 = IntPara;
  Data = wk->scrUnitList[v3];
  if (Data)
LABEL_7:
    Data->aiwk->scr_actcheckflg = 1;
  return 1;
}

// 0x21018d0: s32 AI_GET_TARGET(void)
static inline s32 AI_GET_TARGET(void) {
  s32 scrTargetCode;

  scrTargetCode = GetData()->aiwk->scrTargetCode;
  scrSetIntReturnValue(scrTargetCode);
  return 1;
}

// 0x2101940: s32 AI_SET_TARGET(void)
static inline s32 AI_SET_TARGET(void) {
  SBTLUNIT_WORK *Data;
  s32 IntPara;
  SBTLACTAI_WORK *actaiwk;
  s32 UseTable_Target;
  SBTLACTAI_WORK *v5;

  Data = GetData();
  IntPara = scrGetIntPara(0);
  Data->aiwk->scrTargetCode = IntPara;
  actaiwk = Data->actaiwk;
  UseTable_Target = sBtlGetUseTable_Target(Data, IntPara >> 16, (u16)IntPara);
  v5 = Data->actaiwk;
  actaiwk->ai_targetID = UseTable_Target;
  v5->ai_targetID = sBtlCheckEnemyTarget(Data, v5->ai_targetID);
  return 1;
}

// 0x2101a20: s32 AI_SET_SKILL(void)
static inline s32 AI_SET_SKILL(void) {
  SBTLUNIT_WORK *Data;
  s32 IntPara;

  Data = GetData();
  IntPara = scrGetIntPara(0);
  sBtlSetSkillTarget(Data, IntPara, Data->aiwk->scrTargetCode);
  return 1;
}

// 0x2101ab0: s32 AI_SET_SKILL_TARGET(void)
static inline s32 AI_SET_SKILL_TARGET(void) {
  SBTLUNIT_WORK *Data;
  s32 IntPara;
  u32 v3;

  Data = GetData();
  IntPara = scrGetIntPara(0);
  v3 = scrGetIntPara(1);
  if (IntPara == 506)
  {
    wk->SUMMONSKILL_Start = 180;
  }
  sBtlSetSkillTarget(Data, IntPara, v3);
  return 1;
}

// 0x2101b90: s32 AI_SET_SKILL_TARGET_GEN(void)
static inline s32 AI_SET_SKILL_TARGET_GEN(void) {
  SBTLUNIT_WORK *Data;
  s32 IntPara;
  u32 v3;
  s32 *genArg;
  s32 v5;
  SBTLACTION_WORK *actwk;
  s32 *v7;
  s32 v8;
  SBTLACTION_WORK *v9;
  s32 *v10;
  s32 v11;
  SBTLACTION_WORK *v12;
  s32 *v13;

  Data = GetData();
  IntPara = scrGetIntPara(0);
  v3 = scrGetIntPara(1);
  sBtlSetSkillTarget(Data, IntPara, v3);
  genArg = Data->actwk->genArg;
  v5 = scrGetIntPara(2);
  actwk = Data->actwk;
  genArg[0] = v5;
  v7 = actwk->genArg;
  v8 = scrGetIntPara(3);
  v9 = Data->actwk;
  v7[1] = v8;
  v10 = v9->genArg;
  v11 = scrGetIntPara(4);
  v12 = Data->actwk;
  v10[2] = v11;
  v13 = v12->genArg;
  v13[3] = scrGetIntPara(5);
  return 1;
}

// 0x2101c80: s32 AI_CHK_ACTIONCNT(void)
static inline s32 AI_CHK_ACTIONCNT(void) {
  SBTLUNIT_WORK *Data;
  s32 v2;
  SBTLACTION_WORK *actwk;

  Data = GetData();
  v2 = 1;
  sBtlGetActionTime(Data, 1);
  actwk = Data->actwk;
  if (actwk->framecnt >= 110)
  {
    actwk->action_flg = 1;
  }
  else
  {
    v2 = 0;
  }
  scrSetIntReturnValue(v2);
  return 1;
}

// 0x2101d60: s32 AI_LOAD_EFFECT(void)
static inline s32 AI_LOAD_EFFECT(void) {
  s32 IntPara;
  bool EffectData_ID;

  IntPara = scrGetIntPara(0);
  EffectData_ID = sBtlLoadEffectData_ID(IntPara);
  scrSetIntReturnValue(EffectData_ID);
  return 1;
}

// 0x2101e20: s32 AI_SET_EFFECT(void)
static inline s32 AI_SET_EFFECT(void) {
  SBTLUNIT_WORK *Data;
  s32 IntPara;
  u8 v3;
  s32 side;
  SBTLACTION_WORK *actwk;

  Data = GetData();
  IntPara = scrGetIntPara(0);
  v3 = scrGetIntPara(1);
  side = Data->side;
  sBtlCheckEffectData(Data, IntPara, v3, 0, side, -1, 0);
  actwk = Data->actwk;
  actwk->framecnt = 0;
  actwk->framecntB = 0;
  actwk->total_homing = 0.0;
  actwk->no_homing = 0;
  return 1;
}

// 0x2101f10: s32 AI_SET_STOPMOTION(void)
static inline s32 AI_SET_STOPMOTION(void) {
  GetData()->m_rate = 0.0;
  return 1;
}

// 0x2101f30: s32 AI_SET_UNITFADE(void)
static inline s32 AI_SET_UNITFADE(void) {
  SBTLUNIT_WORK *Data;
  s32 IntPara;
  s32 v3;

  Data = GetData();
  IntPara = scrGetIntPara(0);
  v3 = scrGetIntPara(1);
  if (IntPara)
  {
    sBtlSetFade(Data, 2, 0, 0, v3);
    sBtlSetMotion(Data, 10, 8, 8, 0);
    Data->status |= 0x4001u;
    return 1;
  }
  else
  {
    sBtlSetFade(Data, 1, 0, 0, v3);
    sBtlSetMotion(Data, 11, 0, 0, 0);
    Data->aiwk->scrflag |= 4u;
    return 1;
  }
}

// 0x2102090: s32 AI_SET_REACT(void)
static inline s32 AI_SET_REACT(void) {
  SBTLUNIT_WORK *Data;
  SBTLAI_WORK *aiwk;
  SBTLAI_WORK *v3;
  f32 FloatPara;
  SBTLAI_WORK *v5;

  Data = GetData();
  aiwk = Data->aiwk;
  aiwk->scrReactSkillID = scrGetIntPara(0);
  v3 = Data->aiwk;
  FloatPara = scrGetFloatPara(1);
  v5 = Data->aiwk;
  v3->scrReactDist = FloatPara;
  v5->scrflag |= 0x80u;
  return 1;
}

// 0x2102130: s32 AI_SET_WAIT_MOTIONID(void)
static inline s32 AI_SET_WAIT_MOTIONID(void) {
  s32 IntPara;
  u32 v2;
  s32 v3;
  s32 v4;
  SBTLUNIT_WORK *UserData;
  SBTLAI_WORK *aiwk;
  u32 scrflag;
  s8 v8;
  SBTLAI_WORK *v9;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  v3 = scrGetIntPara(2);
  if (v3 == -2)
  {
    UserData = Support_GetUserData();
    aiwk = UserData->aiwk;
    if (!IntPara)
    {
LABEL_20:
      aiwk->scrflag &= 0xFFFEFEFF;
      return 1;
    }
  }
  else
  {
    v4 = v3;
    if (v3 == -1)
    {
      UserData = GetData();
      aiwk = UserData->aiwk;
      if (!IntPara)
        goto LABEL_20;
    }
    else
    {
      UserData = wk->scrUnitList[v4];
      aiwk = UserData->aiwk;
      if (!IntPara)
        goto LABEL_20;
    }
  }
  scrflag = aiwk->scrflag;
  aiwk->scrcnt = 0;
  aiwk->cmpscrcnt = IntPara;
  aiwk->scrflag = scrflag | 0x100;
  if (UserData->next_motionno != v2)
  {
    UserData->actaiwk->dataflg = 0;
    v8 = UserData->para->devilid != 257;
    sBtlSetMotion_ID(UserData, v2, 0, 0, v8);
  }
  if (v2 >= 3)
  {
    v9 = UserData->aiwk;
  }
  else
  {
    v9 = UserData->aiwk;
    if (UserData->para->devilid != 291)
      goto LABEL_23;
  }
  v9->scrflag |= 0x10000u;
LABEL_23:
  v9->scr_actcheckflg = 1;
  return 1;
}

// 0x2102f30: s32 AI_SET_POS(void)
static inline s32 AI_SET_POS(void) {
  s32 IntPara;
  s32 v2;
  SBTLUNIT_WORK *NakamaData;
  s32 v4;
  SBTLUNIT_WORK *UserData;
  dds3ModelHandle_t *hModel;
  struct sdfVector4_t rot;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  struct sdfVector4_t pos;
  sdfVector4_t v21;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  switch (v2)
  {
    case -4:
      NakamaData = Support_GetNakamaData(1);
      if (NakamaData)
        goto LABEL_16;
      return 1;
    case -3:
      NakamaData = Support_GetNakamaData(0);
      if (NakamaData)
        goto LABEL_16;
      return 1;
    case -2:
      UserData = Support_GetUserData();
      goto LABEL_15;
    case -1:
      UserData = GetData();
LABEL_15:
      NakamaData = UserData;
      goto LABEL_16;
    default:
      v4 = v2;
      NakamaData = wk->scrUnitList[v4];
LABEL_16:
      sBtlGetPointData(IntPara, &NakamaData->pos, &NakamaData->rot);
      pos = NakamaData->pos;
      vct_A = pos;
      hModel = NakamaData->hModel;
      mdlSetPosition(NakamaData->hModel);
      rot = NakamaData->rot;
      vct_A = rot;
      mdlSetRotate(NakamaData->hModel);
      x = NakamaData->pos.x;
      y = NakamaData->pos.y;
      z = NakamaData->pos.z;
      w = NakamaData->pos.w;
      v21.x = x;
      v21.y = y;
      v21.z = z;
      v21.w = w;
      dds3SetPosPoseSet(&NakamaData->pBasic, v21);
      dds3SetRotPoseSet(&NakamaData->pBasic, NakamaData->rot);
      return 1;
  }
}

// 0x2103270: s32 AI_SET_WARP_POINT(void)
static inline s32 AI_SET_WARP_POINT(void) {
  s32 IntPara;
  s32 v2;
  s32 v4;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  v4 = scrGetIntPara(2);
  return AI_SET_WARP_POINT_SUB(IntPara, v2, v4, -1);
}

// 0x21037a0: s32 AI_SET_WARP_POINT_DIR(void)
static inline s32 AI_SET_WARP_POINT_DIR(void) {
  s32 IntPara;
  s32 v2;
  s32 v3;
  s32 v5;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  v3 = scrGetIntPara(2);
  v5 = scrGetIntPara(3);
  return AI_SET_WARP_POINT_SUB(IntPara, v2, v3, v5);
}

// 0x2103330: s32 AI_SET_WARP_POINT_SUB(s32 posID, s32 skill1, s32 skill2, s32 angle)
static inline s32 AI_SET_WARP_POINT_SUB(s32 posID, s32 skill1, s32 skill2, s32 angle) {
  SBTLUNIT_WORK *Data;
  SBTLSKLVISUAL_TBL *SklVisualTbl;
  s32 motionno;
  SBTLAI_WORK *aiwk;
  SBTLACTAI_WORK *actaiwk;
  sdfVector4_t *p_scrPos;
  sdfVector4_t *p_scrRot;
  SBTLACTAI_WORK *v19;
  sdfVector4_t *p_scrPos2;
  s32 devilid;
  _BOOL4 v23;
  s32 flg;
  SBTLACTAI_WORK *v27;
  sdfVector4_t *v28;
  sdfVector4_t *v29;
  struct sdfVector4_t pos;

  if (skill1 != -1)
  {
    if (sBtlHDloadChk(skill1))
      goto LABEL_6;
    return 0;
  }
LABEL_6:
  Data = GetData();
  SklVisualTbl = sBtlGetSklVisualTbl(skill1);
  Data->aiwk->wrap_after_dir = angle;
  sBtlSetFade(Data, 2, 0, 0, 4);
  if (skill1 != -1)
  {
    sBtlSetSkill_EffectData(Data, skill1, 0);
    motionno = SklVisualTbl->motionno;
    goto LABEL_11;
  }
  motionno = 10;
LABEL_11:
  sBtlSetMotion(Data, motionno, 4, 0, 0);
  aiwk = Data->aiwk;
  aiwk->scrSkillID = skill2;
  actaiwk = Data->actaiwk;
  p_scrPos = &actaiwk->scrPos;
  p_scrRot = &actaiwk->scrRot;
  aiwk->scrflag |= 9u;
  sBtlGetPointData(posID, p_scrPos, p_scrRot);
  pos = Data->pos;
  vct_A = pos;
  v19 = Data->actaiwk;
  p_scrPos2 = &v19->scrPos2;
  *p_scrPos2 = vct_A;
  devilid = Data->para->devilid;
  if (devilid > 269)
  {
    if ((devilid & 0xFFFFFFFE) != 0x130)
    {
      if (devilid != 310)
        goto LABEL_40;
      goto LABEL_39;
    }
    goto LABEL_24;
  }
  if (devilid == 267)
    goto LABEL_39;
  if ((devilid & 0xFFFFFFFE) == 0x10C)
  {
LABEL_24:
    if (wk->scrStep == 3)
    {
      v23 = 1;
      if (posID != 2)
        goto LABEL_40;
      if (v23)
      {
        v27 = Data->actaiwk;
        v28 = &v27->scrPos;
        v29 = &v27->scrRot;
        sBtlGetPointData(3, v28, v29);
        Data->actaiwk->scrPos.x = Data->actaiwk->scrPos.x + -280.0;
      }
      goto LABEL_40;
    }
LABEL_39:
    Data->aiwk->scrflag |= 0x200000u;
  }
LABEL_40:
  Data->aiwk->scrcnt = 0;
  Data->status |= 1u;
  sBtlStatusBitOn(Data, 0x4000u);
  flg = Data->flg;
  Data->aisyoid = 0;
  Data->damagecnt = 0;
  Data->flg = flg | 2;
  sBtlResetModelColor(Data);
  sBtlLockOnFree(Data);
  Data->aiwk->scr_actcheckflg = 1;
  *(u64 *)&Data->hangeki_nokezoranai = 0x3C00000078LL;
  return 1;
}

// 0x2103880: s32 AI_SET_SUMMON_POINT(void)
static inline s32 AI_SET_SUMMON_POINT(void) {
  SBTLUNIT_WORK *Data;
  s32 IntPara;
  s32 v3;
  s32 v4;
  s32 v6;

  Data = GetData();
  IntPara = scrGetIntPara(0);
  v3 = scrGetIntPara(1);
  v4 = scrGetIntPara(2);
  v6 = scrGetIntPara(3);
  AI_SET_SUMMON_POINT_SUB(Data, IntPara, v3, v4, v6, 0);
  return 1;
}

// 0x2103970: s32 AI_SET_SUMMON_POINT_SUB(SBTLUNIT_WORK *wk, s32 devil, s32 posID, s32 groupID, s32 flag, s32 nameflag)
static inline s32 AI_SET_SUMMON_POINT_SUB(SBTLUNIT_WORK *wk, s32 devil, s32 posID, s32 groupID, s32 flag, s32 nameflag) {
  s64 v13;
  SBTLUNIT_WORK *v14;
  struct sdfVector4_t CameraEyePos_local;
  long f64 v18;
  f32 *p_x;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 y;
  f32 x;
  f32 w;
  f32 z;
  float32x2_t v35;
  f32 v38;
  f32 v39;
  f32 v40;
  f32 v41;
  f32 v42;
  f32 v43;
  f32 v44;
  f32 v45;
  f32 v46;
  f32 v47;
  f32 v48;
  f32 v49;
  f32 v50;
  f32 v51;
  SBTLEFF_LISTWORK *effList;
  f32 v56;
  f32 v57;
  f32 v58;
  f32 v59;
  f32 v60;
  SBTLUNIT_WORK *v61;
  SBTLAI_WORK *aiwk;
  SBTLSM_LISTWORK *sysmsgList;
  f32 *v66;
  f32 v67;
  f32 v68;
  f32 v69;
  f32 v70;
  f32 *v72;
  f32 v73;
  f32 v74;
  f32 v75;
  f32 v76;
  SBTLUNIT_WORK *v77;
  struct sdfVector4_t v79;
  struct sdfVector4_t v80;
  struct sdfVector4_t pos;
  sdfVector3_t v84;
  sdfVector3_t v85;
  sdfVector4_t v86;
  sdfVector4_t v87;
  sdfVector4_t v88;
  sdfVector4_t v89;
  sdfQuaternion_t v90;
  sdfVector4_t v91;
  sdfVector4_t v92;
  sdfVector4_t v93;

  v13 = (u32)(devil - 260);
  v14 = 0;
  if ((u32)v13 > 0x33)
  {
LABEL_22:
    if (posID != -300)
    {
      if (posID != -2)
      {
        if (posID == -1)
        {
          x = wk->pos.x;
          y = wk->pos.y;
          z = wk->pos.z;
          w = wk->pos.w;
LABEL_90:
          v57 = wk->rot.x;
          v58 = wk->rot.y;
          v60 = wk->rot.z;
          v59 = wk->rot.w;
          v88.x = x;
          v88.y = y;
          v88.z = z;
          v88.w = w;
          v92.x = v57;
          v92.y = v58;
          v92.z = v60;
          v92.w = v59;
          sBtlSetExPos(v88, v92);
          posID = 100;
        }
LABEL_93:
        switch (flag)
        {
          case 0:
            v61 = sBtlSetEncountData(devil, posID, groupID, 0);
            aiwk = v61->aiwk;
            v14 = v61;
            goto LABEL_102;
          case 1:
            v14 = sBtlSetEncountData3(devil, posID, groupID, 0);
            sBtlStatusBitOn(v14, 0x10u);
            v14->status |= 1u;
            aiwk = v14->aiwk;
LABEL_102:
            aiwk->scrflag |= 0x800000u;
            break;
          case 2:
            v14 = sBtlSetEncountData4(devil, posID, groupID, 0);
            break;
          case 3:
            v14 = sBtlSetEncountData4(devil, posID, groupID, 0);
            sBtlStatusBitOn(v14, 0x10u);
            v14->status |= 1u;
            break;
          default:
            goto LABEL_111;
        }
        goto LABEL_111;
      }
      if (devil != 302 && devil != 263)
      {
        posID = -2;
        if ((u32)flag > 3)
        {
LABEL_111:
          if (devil == 182)
          {
            if (nameflag == 1)
            {
              sysmsgList = wk->sysmsgList;
              sBtlCreateSM(sysmsgList, v14, 51, 0, 0, 120);
            }
          }
          else if (devil == 475)
          {
            v14->pos.x = 0.0;
            v14->pos.y = 0.0;
            v14->pos.z = 0.0;
            wk->boss_eventID = v14->ListID;
          }
          return 1;
        }
        goto LABEL_93;
      }
      pos = wk->pos;
      vct_A = pos;
      x = vct_A.x;
      y = vct_A.y;
      w = vct_A.w;
      z = vct_A.z + 200.0;
      goto LABEL_90;
    }
    v80 = wk->pos;
    vct_A = v80;
    v38 = vct_A.x;
    y = vct_A.y;
    v39 = vct_A.z;
    w = vct_A.w;
    v90 = V2Q(wk->rot);
    v84 = Internal_ToEulerRad(v90, 0);
    v85.x = v84.x * 57.29578;
    v85.y = v84.y * 57.29578;
    v85.z = v84.z * 57.29578;
    v40 = Internal_MakePositive(v85, 0).y + -45.0;
    v41 = (f32)(v40 * 0.017453292) * 0.15915494;
    v42 = (s32)v41;
    if (v41 == INFINITY)
      v42 = -2147500000.0;
    v43 = v41 - v42;
    v44 = v43 + 1.0;
    if (v43 >= -0.5)
      v44 = v43;
    if (v43 > 0.5)
      v45 = v43 + -1.0;
    else
      v45 = v44;
    v46 = -0.5 - v45;
    if (v45 >= -0.25)
      v46 = v45;
    if (v45 > 0.25)
      v46 = 0.5 - v45;
    v47 = v46 * 4.0;
    v49 = (f32)((f32)(v40 * 0.017453292) + 1.5708) * 0.15915494;
    v50 = (s32)v49;
    if (v49 == INFINITY)
      v50 = -2147500000.0;
    v51 = v49 - v50;
    if (v51 <= 0.5)
    {
      if (v51 < -0.5)
        v51 = v51 + 1.0;
    }
    else
    {
      v51 = v51 + -1.0;
    }
    if (v51 <= 0.25)
    {
      if (v51 < -0.25)
        v51 = -0.5 - v51;
    }
    else
    {
      v51 = 0.5 - v51;
    }
    v56 = v51 * 4.0;
    v48 = v47 * v47;
    x = v38
      + (f32)((f32)((f32)((f32)((f32)((f32)(v47 * 1.5708) + (f32)((f32)(v47 * (f32)(v47 * v47)) * -0.6459637)) + (f32)((f32)(v48 * (f32)(v47 * (f32)(v47 * v47))) * 0.07968968)) + (f32)((f32)(v48 * (f32)(v48 * (f32)(v47 * (f32)(v47 * v47)))) * -0.0046737655)) + (f32)((f32)(v48 * (f32)(v48 * (f32)(v48 * (f32)(v47 * (f32)(v47 * v47))))) * 0.00015148419)) * 208.30952);
    z = v39
      + (f32)((f32)((f32)((f32)((f32)((f32)(v56 * 1.5708) + (f32)((f32)(v56 * (f32)(v56 * v56)) * -0.6459637)) + (f32)((f32)((f32)(v56 * v56) * (f32)(v56 * (f32)(v56 * v56))) * 0.07968968)) + (f32)((f32)((f32)(v56 * v56) * (f32)((f32)(v56 * v56) * (f32)(v56 * (f32)(v56 * v56)))) * -0.0046737655)) + (f32)((f32)((f32)(v56 * v56) * (f32)((f32)(v56 * v56) * (f32)((f32)(v56 * v56) * (f32)(v56 * (f32)(v56 * v56))))) * 0.00015148419)) * -208.30952);
    goto LABEL_90;
  }
  if (((1 << ((u8)devil - 4)) & 0x3800016000000LL) != 0)
  {
    if (flag == 1)
    {
      v14 = 0;
      goto LABEL_22;
    }
    v79 = wk->pos;
    vct_A = v79;
    CameraEyePos_local = CameraEyePos;
    vct_B = CameraEyePos_local;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v18 = sub_18E6660(0, *(u64 *)&devil);
    FromEuler(0.0, *(f32 *)&v18, 0.0);
    p_x = &vf00.x;
    v21 = wk->pos.x;
    v22 = wk->pos.y;
    v23 = p_x[4];
    v24 = p_x[5];
    v25 = p_x[6];
    v26 = p_x[7];
    v28 = wk->pos.z;
    v27 = wk->pos.w;
    v86.x = v21;
    v86.y = v22;
    v86.z = v28;
    v86.w = v27;
    v91.x = v23;
    v91.y = v24;
    v91.z = v25;
    v91.w = v26;
    sBtlSetExPos(v86, v91);
    v14 = sBtlSetEncountData4(devil, 100, groupID, 0);
    v14->para->now->hp = wk->para->now->hp;
    goto LABEL_22;
  }
  if (devil != 260)
  {
    if (v13 != 51)
      goto LABEL_22;
    if (groupID == 1)
    {
      sBtlGetUnitHelperPos(wk, 201);
      v35.n64_u64[0] = 0x430C0000C3020000LL;
LABEL_135:
      v66 = &vf00.x;
      v67 = v66[4];
      v68 = v66[5];
      v69 = v66[6];
      v70 = v66[7];
      *(float32x2_t *)&wk->pos.x = vadd_f32(*(float32x2_t *)&wk->pos.x, v35);
      FromEuler(0.0, 0.0, 0.0);
      v72 = &vf00.x;
      v73 = v72[4];
      v74 = v72[5];
      v76 = v72[6];
      v75 = v72[7];
      v89.x = v67;
      v89.y = v68;
      v89.z = v69;
      v89.w = v70;
      v93.x = v73;
      v93.y = v74;
      v93.z = v76;
      v93.w = v75;
      sBtlSetExPos(v89, v93);
      v77 = sBtlSetEncountData2(311, 100, groupID, 0);
      v77->vstatus |= 0x800000u;
      return 1;
    }
    sBtlGetUnitHelperPos(wk, 202);
    v35.n64_u64[0] = vdup_n_s32(0x42C80000u).n64_u64[0];
    goto LABEL_135;
  }
  effList = wk->effList;
  v87.y = 600.0;
  v87.z = 2000.0;
  v87.x = 0.0;
  v87.w = 0.0;
  sBtlCreateEff(effList, 0, 14, 0, v87, 0x80808080, 0, 1.0, 0);
  return 1;
}

// 0x21046e0: s32 AI_SET_RESUMMON_POINT(void)
static inline s32 AI_SET_RESUMMON_POINT(void) {
  s32 IntPara;
  s32 v2;
  SBTLUNIT_WORK *v4;
  SBTLUNIT_WORK *Data;
  SBTLAI_WORK *aiwk;
  SBTLUNIT_WORK *v9;
  sdfVector4_t *p_pos;
  s32 v12;
  struct sdfVector4_t rot;
  sdfVector4_t *p_rot;
  s32 v15;
  struct sdfVector4_t pos;
  struct sdfVector4_t v17;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  v4 = wk->scrUnitList[IntPara];
  Data = GetData();
  if (v2 == -1)
  {
    v9 = Data;
    pos = Data->pos;
    vct_A = pos;
    p_pos = &v4->pos;
    v12 = (u8)byte_5755EF5;
    *p_pos = vct_A;
    rot = v9->rot;
    if (v12)
      goto LABEL_19;
    goto LABEL_29;
    if (v15)
    {
LABEL_19:
      goto LABEL_20;
    }
LABEL_29:
    v17 = rot;
    rot = v17;
LABEL_20:
    vct_A = rot;
    p_rot = &v4->rot;
    *p_rot = vct_A;
    v9->status |= 1u;
    goto LABEL_12;
  }
  sBtlGetPointData(v2, &v4->pos, &v4->rot);
LABEL_12:
  sBtlSetFade(v4, 1, 0, 0, 8);
  sBtlSetMotion(v4, 0, 0, 0, 0);
  aiwk = v4->aiwk;
  *(u64 *)&aiwk->scrcnt = 0x1000000000LL;
  aiwk->scrflag |= 0x1100u;
  return 1;
}

// 0x2104a50: s32 AI_GET_NUM_GROUPID(void)
static inline s32 AI_GET_NUM_GROUPID(void) {
  s32 IntPara;
  s32 v2;
  s32 v3;
  SBTLUNIT_LISTWORK *v5;
  s32 NumUnit_GroupID2;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_LISTWORK *v9;
  s32 v10;
  s32 v11;
  SBTLUNIT_LISTWORK *v13;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  if (v2 == 2)
  {
    UnitMng = wk->UnitMng;
    v9 = UnitMng;
    v10 = IntPara;
    v11 = 1;
    goto LABEL_23;
  }
  if (v2 == 1)
  {
    v13 = wk->UnitMng;
    v9 = v13;
    v10 = IntPara;
    v11 = 0;
LABEL_23:
    NumUnit_GroupID2 = sBtlGetNumUnit_GroupID2(v9, v10, v11);
    goto LABEL_24;
  }
  v3 = 0;
  if (v2)
    goto LABEL_25;
  v5 = wk->UnitMng;
  NumUnit_GroupID2 = sBtlGetNumUnit_GroupID(v5, IntPara);
LABEL_24:
  v3 = NumUnit_GroupID2;
LABEL_25:
  scrSetIntReturnValue(v3);
  return 1;
}

// 0x2104c10: s32 AI_CHK_UNITFADE(void)
static inline s32 AI_CHK_UNITFADE(void) {
  GetData();
  scrSetIntReturnValue(1);
  return 1;
}

// 0x2104c80: s32 AI_GET_RAND_INT(void)
static inline s32 AI_GET_RAND_INT(void) {
  s64 IntPara;
  s32 v2;

  IntPara = scrGetIntPara(0);
  v2 = sub_1905740(IntPara, 0);
  scrSetIntReturnValue(v2);
  return 1;
}

// 0x2104cf0: s32 AI_SET_TABLE(void)
static inline s32 AI_SET_TABLE(void) {
  SBTLUNIT_WORK *Data;
  s32 IntPara;
  SBTLACTAI_WORK *actaiwk;
  s32 *data_p;

  Data = GetData();
  IntPara = scrGetIntPara(0);
  actaiwk = Data->actaiwk;
  actaiwk->dataflg = 1;
  data_p = actaiwk->data_p;
  data_p[0] = IntPara;
  data_p[1] = 0;
  Data->aiwk->scr_actcheckflg = 1;
  sBtlUseTableDataProc(Data);
  return 1;
}

// 0x2104db0: s32 AI_CONTINUE_TABLE(void)
static inline s32 AI_CONTINUE_TABLE(void) {
  SBTLUNIT_WORK *Data;
  SBTLAI_WORK *aiwk;
  SBTLUNIT_WORK *v3;

  Data = GetData();
  aiwk = Data->aiwk;
  aiwk->scr_actcheckflg = 1;
  if (aiwk->stat == 1)
  {
    v3 = Data;
    if (Data->actaiwk->stat == 2)
    {
      sBtlUseTableDataProc(v3);
    }
  }
  return 1;
}

// 0x2104e50: s32 AI_CHK_USE_TABLE(void)
static inline s32 AI_CHK_USE_TABLE(void) {
  s32 dataflg;

  dataflg = (u8)GetData()->actaiwk->dataflg;
  scrSetIntReturnValue(dataflg != 0);
  return 1;
}

// 0x2104ed0: s32 AI_SET_STOP_TABLE(void)
static inline s32 AI_SET_STOP_TABLE(void) {
  SBTLACTAI_WORK *actaiwk;

  actaiwk = GetData()->actaiwk;
  actaiwk->dataflg = 0;
  return 1;
}

// 0x2104f00: s32 AI_SET_STOP_ACTION(void)
static inline s32 AI_SET_STOP_ACTION(void) {
  s32 IntPara;
  s32 v3;
  SBTLUNIT_WORK *Data;
  SBTLUNIT_WORK *NakamaData;

  IntPara = scrGetIntPara(0);
  if (IntPara == -3)
  {
    NakamaData = Support_GetNakamaData(0);
    if (!NakamaData)
      return 1;
    goto LABEL_12;
  }
  v3 = IntPara;
  if (IntPara == -2)
  {
    NakamaData = Support_GetUserData();
LABEL_12:
    sBtlSupport_StopAction(NakamaData);
    return 1;
  }
  if (IntPara == -1)
  {
    Data = GetData();
    sBtlSupport_StopAction(Data);
    return 1;
  }
  else
  {
    sBtlSupport_StopAction(wk->scrUnitList[v3]);
    return 1;
  }
}

// 0x2105040: s32 AI_SET_MOVE_POINT(void)
static inline s32 AI_SET_MOVE_POINT(void) {
  SBTLUNIT_WORK *Data;
  s32 IntPara;
  unsigned __int128 v4;
  sdfVector4_t pos;

  *(u64 *)&pos.x = 0;
  *(u64 *)&pos.z = 0;
  v4 = 0u;
  Data = GetData();
  IntPara = scrGetIntPara(0);
  sBtlGetPointData(IntPara, &pos, &v4);
  Support_MovePos(Data, pos);
  return 1;
}

// 0x2105120: s32 AI_SET_MOVE_POINT2(void)
static inline s32 AI_SET_MOVE_POINT2(void) {
  SBTLUNIT_WORK *Data;
  s32 IntPara;
  f32 FloatPara;
  s32 v4;
  unsigned __int128 v6;
  sdfVector4_t pos;

  *(u64 *)&pos.x = 0;
  *(u64 *)&pos.z = 0;
  v6 = 0u;
  Data = GetData();
  IntPara = scrGetIntPara(0);
  FloatPara = scrGetFloatPara(1);
  v4 = scrGetIntPara(2);
  sBtlGetPointData(IntPara, &pos, &v6);
  Support_MovePos2(Data, pos, FloatPara, v4);
  return 1;
}

// 0x2105230: s32 AI_SET_DOWN(void)
static inline s32 AI_SET_DOWN(void) {
  s32 IntPara;
  SBTLUNIT_WORK *Data;
  SBTLDMG_HITLISTWORK *hitList;
  SBTLEFF_LISTWORK *effList;
  SBTLAI_WORK *aiwk;

  IntPara = scrGetIntPara(0);
  Data = GetData();
  GetData()->actaiwk->dataflg = 0;
  sBtlSetMotion(Data, 14, 4, 400, 0);
  sBtlSetAction(Data, 23, 400);
  hitList = wk->hitList;
  sBtlClearHitC(hitList, Data);
  effList = wk->effList;
  sBtlForceReset(effList, Data);
  aiwk = Data->aiwk;
  aiwk->cmpscrcnt = IntPara;
  *(u64 *)&aiwk->scrflag = aiwk->scrflag | 0x10;
  return 1;
}

// 0x2105420: s32 AI_GET_DISTANCE_DATA(void)
static inline s32 AI_GET_DISTANCE_DATA(void) {
  s32 devilid;
  f32 enmy_area_r;

  GetData();
  devilid = GetData()->para->devilid;
  enmy_area_r = sBtlGetDevilData(devilid, -1)->enmy_area_r;
  scrSetFloatReturnValue(enmy_area_r);
  return 1;
}

// 0x21054e0: s32 AI_GET_DISTANCE(void)
static inline s32 AI_GET_DISTANCE(void) {
  s32 IntPara;
  s32 v2;
  SBTLUNIT_WORK *Data;
  SBTLUNIT_WORK *NakamaData;
  sdfVector4_t v8;
  f32 *p_x;
  f32 z;
  f32 x;
  f32 y;
  f32 v14;
  f32 v15;
  struct sdfVector4_t v18;
  struct sdfVector4_t v19;
  sdfVector4_t rot;
  sdfVector4_t pos;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  *(u64 *)&pos.x = 0;
  *(u64 *)&pos.z = 0;
  *(u64 *)&rot.x = 0;
  *(u64 *)&rot.z = 0;
  if (IntPara == -1)
  {
    Data = GetData();
    if (v2 != -4)
      goto LABEL_9;
LABEL_13:
    NakamaData = Support_GetNakamaData(1);
    if (!NakamaData)
    {
LABEL_43:
      v15 = 9000000.0;
      goto LABEL_46;
    }
LABEL_14:
    v18 = NakamaData->pos;
    vct_A = v18;
    pos = vct_A;
    v19 = Data->pos;
    goto LABEL_21;
  }
  Data = wk->scrUnitList[IntPara];
  if (v2 == -4)
    goto LABEL_13;
LABEL_9:
  if (v2 == -3)
  {
    NakamaData = Support_GetNakamaData(0);
    if (!NakamaData)
      goto LABEL_43;
    goto LABEL_14;
  }
  if (v2 == -2)
  {
    NakamaData = Support_GetUserData();
    goto LABEL_14;
  }
  if (v2 < 0)
    return 1;
  sBtlGetPointData(v2, &pos, &rot);
  v19 = Data->pos;
LABEL_21:
  vct_A = v19;
  v8 = pos;
  vct_B = v8;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  p_x = &vf00.x;
  z = p_x[6];
  x = p_x[4];
  y = p_x[5];
  v14 = sqrtf((f32)((f32)(x * x) + (f32)(y * y)) + (f32)(z * z));
  v15 = v14;
LABEL_46:
  scrSetFloatReturnValue(v15);
  return 1;
}

// 0x2105980: s32 AI_CHK_DISTANCE_TARGET(void)
static inline s32 AI_CHK_DISTANCE_TARGET(void) {
  f32 FloatPara;
  s32 IntPara;
  u32 NumDistance;
  s32 v5;

  FloatPara = scrGetFloatPara(0);
  IntPara = scrGetIntPara(1);
  NumDistance = sBtlGetNumDistance(FloatPara);
  if (NumDistance > 5)
    goto LABEL_16;
  if (((1 << NumDistance) & 0x2A) == 0)
  {
    if (((1 << NumDistance) & 0x14) != 0 && (IntPara & 0xFFFF0000) == 0x10000)
      goto LABEL_13;
LABEL_16:
    v5 = 0;
    goto LABEL_15;
  }
  if ((IntPara & 0xFFFF0000) != 0x20000 && ((IntPara & 0xFFFF0000) != 0x10000 || NumDistance - 2 >= 4))
    goto LABEL_16;
LABEL_13:
  v5 = 1;
LABEL_15:
  scrSetIntReturnValue(v5);
  return 1;
}

// 0x2105ab0: s32 AI_GET_NUM_DISTANCE(void)
static inline s32 AI_GET_NUM_DISTANCE(void) {
  f32 FloatPara;
  s32 NumDistance;

  FloatPara = scrGetFloatPara(0);
  NumDistance = sBtlGetNumDistance(FloatPara);
  scrSetIntReturnValue(NumDistance);
  return 1;
}

// 0x2105b20: s32 AI_BS_CHKITI_MV(void)
static inline s32 AI_BS_CHKITI_MV(void) {
  SBTLUNIT_WORK *Data;
  SBTLUNIT_WORK *v2;

  Data = GetData();
  if (Data->aiwk->act_p > 4 || (v2 = Data, (Data->actaiwk->mode & 0xFFFFFFFE) == 0xC))
  {
    scrSetIntReturnValue(1);
    return 1;
  }
  else
  {
    scrSetIntReturnValue(0);
    v2->aiwk->scr_actcheckflg = 1;
    return 1;
  }
}

// 0x2105bf0: s32 AI_BS_ITI_OPENEYE(void)
static inline s32 AI_BS_ITI_OPENEYE(void) {
  SBTLUNIT_WORK *Data;
  sdatUnitWork_t *para;
  SBTLUNIT_WORK *v3;
  s32 devilid;
  s16 v5;
  s32 aishou;
  SBTLAISYO_DATAWORK *Aisyotbl;
  SBTLAI_WORK *aiwk;

  Data = GetData();
  para = Data->para;
  v3 = Data;
  devilid = para->devilid;
  v5 = para->devilid;
  aishou = sBtlGetDevilData(devilid, -1)->aishou;
  v3->aisyoid = v5;
  v3->motion_setno = 4;
  Aisyotbl = sBtlGetAisyotbl(aishou);
  ClassCopy(v3->para->aisyo, Aisyotbl, 0);
  aiwk = v3->aiwk;
  v3->Itimoku_CloseEye = 0;
  aiwk->scr_actcheckflg = 1;
  ++v3->Itimoku_CloseCnt;
  return 1;
}

// 0x2105cf0: s32 AI_BS_ITI_CLOSEEYE(void)
static inline s32 AI_BS_ITI_CLOSEEYE(void) {
  SBTLUNIT_WORK *Data;
  sdatUnitWork_t *para;
  SBTLUNIT_WORK *v3;
  __int128 v4;
  s32 *v6;
  SBTLAI_WORK *aiwk;

  Data = GetData();
  para = Data->para;
  v3 = Data;
  *(u64 *)&v4 = 0x100000001000LL;
  *((u64 *)&v4 + 1) = 0x100000001000LL;
  Data->motion_setno = 5;
  v6 = para->aisyo->para;
  *(_OWORD *)v6 = v4;
  *(_OWORD *)&v6[4] = v4;
  *(_OWORD *)&v6[8] = v4;
  *(_OWORD *)&v6[12] = v4;
  sBtlSetMotion(v3, 0, 4, 0, 0);
  scrSetIntReturnValue(1);
  aiwk = v3->aiwk;
  v3->Itimoku_CloseEye = 1;
  aiwk->scr_actcheckflg = 1;
  wk->SUMMONSKILL_Start = 0;
  return 1;
}

// 0x2105e10: s32 AI_MOD(void)
static inline s32 AI_MOD(void) {
  s32 IntPara;
  s32 v2;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  scrSetIntReturnValue(IntPara % v2);
  return 1;
}

// 0x2105e90: s32 AI_PRINTINT(void)
static inline s32 AI_PRINTINT(void) {
  s64 v2;
  sbtl *v3;
  sbtl *v4;
  s64 v5;

  GetData();
  scrGetIntPara(0);
  v2 = 32;
  do
  {
    v5 = *(s64 *)((char *)&wk2->effpac->obj.klass + v2);
    if ((*(u16 *)(v5 + 38) & 1) != 0)
      goto LABEL_6;
    v4 = v3;
    if (!*(u16 *)(v5 + 36))
LABEL_6:
    v2 += 8;
    v3 = v4;
  }
  while (v2 != 1232);
  return 1;
}

// 0x2105fe0: s32 AI_BS_YOMIK_CHOOSE_POINT(void)
static inline s32 AI_BS_YOMIK_CHOOSE_POINT(void) {
  SBTLUNIT_WORK *Data;
  s32 devilid;
  s32 v3;
  s32 v4;
  s32 v5;
  f32 v6;
  s32 v7;
  s32 v8;
  f32 v9;
  s64 v10;
  f32 z;
  struct sdfVector4_t v14;
  f32 *p_x;
  f32 x;
  f32 y;
  f32 v18;
  s32 v21;
  f32 v22;
  s32 v23;
  s32 v24;
  f32 v25;
  s32 v26;
  s32 v27;
  s64 v28;
  f32 v29;
  struct sdfVector4_t v32;
  f32 *v33;
  f32 v34;
  f32 v35;
  f32 v36;
  f32 v38;
  struct sdfVector4_t v40;
  f32 *v41;
  f32 v42;
  f32 v43;
  f32 v44;
  SBTLUNIT_WORK *UserData;
  s32 v50;
  sdfVector4_t v53;
  SBTLUNIT_WORK *NakamaData;
  sdfVector4_t rot;
  sdfVector4_t pos;

  *(u64 *)&pos.x = 0;
  *(u64 *)&pos.z = 0;
  *(u64 *)&rot.x = 0;
  *(u64 *)&rot.z = 0;
  Data = GetData();
  UserData = Support_GetUserData();
  NakamaData = Support_GetNakamaData(0);
  devilid = Data->para->devilid;
  if (devilid == 276)
  {
    v3 = 4;
    v4 = 7;
  }
  else if (devilid == 277)
  {
    v3 = 8;
    v4 = 11;
  }
  else
  {
    v3 = 3;
    v4 = 6;
  }
  v5 = v4 + 1;
  v50 = v4;
  v6 = 100000.0;
  v7 = v3;
  v8 = v3;
  do
  {
    sBtlGetPointData(v7, &pos, &rot);
    pos.w = 0.0;
    v10 = *(u64 *)&pos.x;
    z = pos.z;
    *(u64 *)&vct_A.x = v10;
    vct_A.z = z;
    vct_A.w = 0.0;
    v14 = Data->pos;
    vct_B = v14;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    p_x = &vf00.x;
    x = p_x[4];
    y = p_x[5];
    v18 = p_x[6];
    v9 = sqrtf((f32)((f32)(x * x) + (f32)(y * y)) + (f32)(v18 * v18));
    if (v9 <= v6)
    {
      v6 = v9;
      v8 = v7;
    }
    ++v7;
  }
  while (v5 != v7);
  v21 = v50;
  v22 = -1.0;
  v23 = 3;
  v24 = v3;
  do
  {
    v26 = v8 - 1;
    if (v50 + 2 == v8)
      v26 = v3;
    if (v3 == v8)
      v27 = v21;
    else
      v27 = v26;
    sBtlGetPointData(v27, &pos, &rot);
    pos.w = 0.0;
    v28 = *(u64 *)&pos.x;
    v29 = pos.z;
    *(u64 *)&vct_A.x = v28;
    vct_A.z = v29;
    vct_A.w = 0.0;
    v32 = UserData->pos;
    vct_B = v32;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v33 = &vf00.x;
    v34 = v33[4];
    v35 = v33[5];
    v36 = v33[6];
    v38 = sqrtf((f32)((f32)(v34 * v34) + (f32)(v35 * v35)) + (f32)(v36 * v36));
    if (NakamaData)
    {
      v53 = pos;
      vct_A = v53;
      v40 = NakamaData->pos;
      vct_B = v40;
      vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      v41 = &vf00.x;
      v42 = v41[4];
      v43 = v41[5];
      v44 = v41[6];
      v25 = sqrtf((f32)((f32)(v42 * v42) + (f32)(v43 * v43)) + (f32)(v44 * v44));
      goto LABEL_39;
    }
    v25 = v38 + 10.0;
LABEL_39:
    v21 = v50;
    ++v8;
    if (v38 < v25)
      v25 = v38;
    if (v25 >= v22)
    {
      v22 = v25;
      v24 = v27;
    }
    --v23;
  }
  while (v23);
  scrSetIntReturnValue(v24);
  return 1;
}

// 0x21067f0: s32 AI_BS_AKAMA_CHOOSE_WARP(void)
static inline s32 AI_BS_AKAMA_CHOOSE_WARP(void) {
  f32 v1;
  SBTLUNIT_WORK *NakamaData;
  s32 v3;
  s32 i;
  f32 v5;
  s64 v6;
  f32 z;
  struct sdfVector4_t v10;
  f32 *p_x;
  f32 x;
  f32 y;
  f32 v14;
  f32 v16;
  struct sdfVector4_t v18;
  f32 *v19;
  f32 v20;
  f32 v21;
  f32 v22;
  SBTLUNIT_WORK *UserData;
  struct sdfVector4_t v28;
  sdfVector4_t rot;
  sdfVector4_t pos;

  *(u64 *)&pos.x = 0;
  *(u64 *)&pos.z = 0;
  *(u64 *)&rot.x = 0;
  *(u64 *)&rot.z = 0;
  UserData = Support_GetUserData();
  v1 = -1.0;
  NakamaData = Support_GetNakamaData(0);
  v3 = 3;
  for (i = 2; i != 6; ++i)
  {
    sBtlGetPointData(i, &pos, &rot);
    pos.w = 0.0;
    v6 = *(u64 *)&pos.x;
    z = pos.z;
    *(u64 *)&vct_A.x = v6;
    vct_A.z = z;
    vct_A.w = 0.0;
    v10 = UserData->pos;
    vct_B = v10;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    p_x = &vf00.x;
    x = p_x[4];
    y = p_x[5];
    v14 = p_x[6];
    v16 = sqrtf((f32)((f32)(x * x) + (f32)(y * y)) + (f32)(v14 * v14));
    if (NakamaData)
    {
      v28 = pos;
      vct_A = v28;
      v18 = NakamaData->pos;
      vct_B = v18;
      vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      v19 = &vf00.x;
      v20 = v19[4];
      v21 = v19[5];
      v22 = v19[6];
      v5 = sqrtf((f32)((f32)(v20 * v20) + (f32)(v21 * v21)) + (f32)(v22 * v22));
      goto LABEL_5;
    }
    v5 = v16 + 10.0;
LABEL_5:
    if (v16 < v5)
      v5 = v16;
    if (v5 >= v1)
    {
      v1 = v5;
      v3 = i;
    }
  }
  scrSetIntReturnValue(v3);
  return 1;
}

// 0x2106d20: s32 AI_BS_CHOOSE_POINT(void)
static inline s32 AI_BS_CHOOSE_POINT(void) {
  s32 v2;

  v2 = AI_BS_CHOOSE_POINT_SUB();
  scrSetIntReturnValue(v2);
  return 1;
}

// 0x2106de0: s32 AI_BS_CHOOSE_POINT_SUB(void)
static inline s32 AI_BS_CHOOSE_POINT_SUB(void) {
  SBTLUNIT_WORK *UserData;
  SBTLUNIT_WORK *NakamaData;
  SBTLUNIT_WORK *Data;
  s32 *v4;
  s64 v5;
  s32 devilid;
  s32 v8;
  f32 v9;
  s32 v10;
  s32 v11;
  f32 v13;
  struct sdfVector4_t v15;
  f32 *v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v23;
  s32 v24;
  s32 v25;
  s64 v26;
  f32 v27;
  f32 v29;
  s64 v30;
  f32 v31;
  f32 *v35;
  f32 v36;
  f32 v37;
  f32 v38;
  s32 scrStep;
  u32 v44;
  f32 v45;
  s32 v46;
  s32 v47;
  f32 v49;
  struct sdfVector4_t v51;
  f32 *v52;
  f32 v53;
  f32 v54;
  f32 v55;
  f32 v57;
  s32 v58;
  f32 v60;
  struct sdfVector4_t v62;
  f32 *v63;
  f32 v64;
  f32 v65;
  f32 v66;
  u32 *v68;
  s64 v69;
  s32 v70;
  s32 v71;
  s64 v72;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s32 v77;
  struct sdfVector4_t v79;
  f32 *v80;
  f32 v81;
  f32 v82;
  f32 v83;
  f32 v85;
  s32 v86;
  f32 v88;
  struct sdfVector4_t v90;
  f32 *p_x;
  f32 x;
  f32 y;
  f32 z;
  s32 v96;
  u32 v97;
  f32 v99;
  s32 v100;
  u32 v101;
  struct sdfVector4_t v103;
  f32 *v104;
  f32 v105;
  f32 v106;
  f32 v107;
  f32 v109;
  bool v112;
  bool v113;
  s32 v114;
  s64 v115;
  s64 v116;
  s64 v117;
  u32 v118;
  f32 v119;
  s64 v120;
  s32 *v121;
  s32 v122;
  s64 v123;
  f32 v124;
  struct sdfVector4_t v127;
  f32 *v128;
  f32 v129;
  f32 v130;
  f32 v131;
  f32 v133;
  struct sdfVector4_t v135;
  f32 *v136;
  f32 v137;
  f32 v138;
  f32 v139;
  f32 v141;
  s64 i;
  SBTLUNIT_LISTWORK *v146;
  SBTLUNIT_WORK *v147;
  s32 v148;
  f32 v149;
  f32 v150;
  f32 v151;
  f32 w;
  u32 *v153;
  sdfVector4_t v154;
  sdfVector4_t v157;
  sdfVector4_t v160;
  sdfVector4_t v163;
  SBTLUNIT_WORK *v168;
  struct sdfVector4_t v169;
  struct sdfVector4_t v170;
  struct sdfVector4_t v173;
  sdfVector4_t v176;
  sdfVector4_t rot;
  sdfVector4_t pos;

  *(u64 *)&pos.x = 0;
  *(u64 *)&pos.z = 0;
  *(u64 *)&rot.x = 0;
  *(u64 *)&rot.z = 0;
  UserData = Support_GetUserData();
  NakamaData = Support_GetNakamaData(0);
  Data = GetData();
  v4 = NewSpecific(s32, 8u);
  v168 = UserData;
  if (!UserData)
    return 1;
  v5 = v4;
  devilid = Data->para->devilid;
  if (devilid <= 291)
  {
    if (devilid <= 267)
    {
      if (devilid != 262)
      {
        if (Data->para->devilid == 267)
          goto LABEL_47;
        return 1;
      }
LABEL_81:
      scrStep = wk->scrStep;
      if (scrStep == 2)
        goto LABEL_194;
      goto LABEL_9001;
      if (scrStep == 2)
      {
LABEL_194:
        v85 = 1000000.0;
        v44 = -1;
        v86 = 2;
        while (v86 == Data->aiwk->scrCmpCnt)
        {
LABEL_198:
          if (++v86 == 10)
            return v44;
        }
        sBtlGetPointData(v86, &pos, &rot);
        v173 = pos;
        vct_A = v173;
        v90 = Data->pos;
        vct_B = v90;
        vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
        p_x = &vf00.x;
        x = p_x[4];
        y = p_x[5];
        z = p_x[6];
        v88 = sqrtf((f32)((f32)(x * x) + (f32)(y * y)) + (f32)(z * z));
        if (v88 < v85 && v88 > 200.0)
        {
          v85 = v88;
          v44 = v86;
        }
        goto LABEL_198;
      }
LABEL_9001:
      scrStep = wk->scrStep;
      if (scrStep == 3)
        goto LABEL_194;
      v99 = 1000000.0;
      v100 = -1;
      v101 = 1;
      while (v101 <= 8 && ((1 << v101) & 0x148) != 0)
      {
LABEL_235:
        if (++v101 == 10)
        {
          do
          {
            do
              v44 = sub_1905740(10, 0);
            while (v44 <= 8 && ((1 << v44) & 0x149) != 0);
            v112 = v100 == 4 && v44 == 2;
            v113 = v44 == 4 && v100 == 2;
          }
          while (v113 || v112);
          return v44;
        }
      }
      sBtlGetPointData(v101, &pos, &rot);
      v176 = pos;
      vct_A = v176;
      v103 = Data->pos;
      vct_B = v103;
      vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      v104 = &vf00.x;
      v105 = v104[4];
      v106 = v104[5];
      v107 = v104[6];
      v109 = sqrtf((f32)((f32)(v105 * v105) + (f32)(v106 * v106)) + (f32)(v107 * v107));
      if (v109 < v99)
      {
        v99 = v109;
        v100 = v101;
      }
      goto LABEL_235;
    }
    if ((devilid & 0xFFFFFFFE) == 0x10C)
    {
LABEL_11:
      v8 = wk->scrStep;
      if (!v8)
        goto LABEL_120;
      goto LABEL_9006;
      if (!v8)
      {
LABEL_120:
        v57 = 1000000.0;
        v58 = 0;
        v44 = -1;
        while (1)
        {
          sBtlGetPointData(v58, &pos, &rot);
          v160 = pos;
          vct_A = v160;
          v62 = v168->pos;
          vct_B = v62;
          vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
          v63 = &vf00.x;
          v64 = v63[4];
          v65 = v63[5];
          v66 = v63[6];
          v60 = sqrtf((f32)((f32)(v64 * v64) + (f32)(v65 * v65)) + (f32)(v66 * v66));
          if (v60 < v57 && v60 > 100.0)
          {
            v57 = v60;
            v44 = v58;
          }
          if (++v58 == 25)
            return v44;
        }
      }
LABEL_9006:
      if (v8 == 2)
        goto LABEL_120;
      return 1;
    }
    v44 = 1;
    if (devilid != 291)
      return v44;
    v45 = 1000000.0;
    v46 = -1;
    v47 = 3;
    while (1)
    {
      sBtlGetPointData(v47, &pos, &rot);
      v157 = pos;
      vct_A = v157;
      v51 = Data->pos;
      vct_B = v51;
      vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      v52 = &vf00.x;
      v53 = v52[4];
      v54 = v52[5];
      v55 = v52[6];
      v49 = sqrtf((f32)((f32)(v53 * v53) + (f32)(v54 * v54)) + (f32)(v55 * v55));
      if (v49 < v45)
      {
        v45 = v49;
        v46 = v47;
      }
      if (++v47 == 28)
      {
        v96 = v46 - 3;
        if (v46 - 3 >= 10)
        {
          *(u32 *)(v5 + 32) = v46 - 10;
          v97 = 1;
        }
        else
        {
          v97 = 0;
        }
        v114 = v96 % 5;
        if (v96 % 5 > 2)
        {
          if (v96 <= 14)
            goto LABEL_286;
LABEL_281:
          if (v114 < 2)
            goto LABEL_282;
LABEL_287:
          v117 = v5 + 4 * v97++;
          *(u32 *)(v117 + 32) = v46 - 2;
          if (v96 >= 10)
            goto LABEL_288;
LABEL_283:
          if (v114 > 2)
            goto LABEL_293;
LABEL_290:
          v118 = v97 + 1;
          *(u32 *)(v5 + 4 * v97++ + 32) = v46 + 12;
          if (v114 >= 2)
            goto LABEL_293;
        }
        else
        {
          v115 = v5 + 4 * v97++;
          *(u32 *)(v115 + 32) = v46 + 2;
          if (v96 > 14)
            goto LABEL_281;
LABEL_286:
          v116 = v5 + 4 * v97++;
          *(u32 *)(v116 + 32) = v46 + 10;
          if (v114 >= 2)
            goto LABEL_287;
LABEL_282:
          if (v96 < 10)
            goto LABEL_283;
LABEL_288:
          if (v114 <= 2)
          {
            v118 = v97 + 1;
            *(u32 *)(v5 + 4 * v97++ + 32) = v46 - 8;
            if (v96 < 15)
              goto LABEL_290;
LABEL_295:
            v97 = v118;
            if (v114 >= 2)
            {
LABEL_296:
              v118 = v97 + 1;
              *(u32 *)(v5 + 4 * v97 + 32) = v46 - 12;
            }
LABEL_297:
            v119 = -1.0;
            v120 = v118;
            v121 = (v5 + 32);
            v44 = 3;
            while (2)
            {
              v122 = *v121;
              sBtlGetPointData(v122, &pos, &rot);
              pos.w = 0.0;
              v123 = *(u64 *)&pos.x;
              v124 = pos.z;
              *(u64 *)&vct_A.x = v123;
              vct_A.z = v124;
              vct_A.w = 0.0;
              v127 = v168->pos;
              goto LABEL_307;
LABEL_308:
              goto LABEL_309;
LABEL_307:
              vct_B = v127;
              goto LABEL_308;
LABEL_309:
              vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
              goto LABEL_311;
LABEL_312:
              goto LABEL_313;
LABEL_311:
              v128 = &vf00.x;
              v129 = v128[4];
              v130 = v128[5];
              v131 = v128[6];
              goto LABEL_312;
LABEL_313:
              v133 = sqrtf((f32)((f32)(v129 * v129) + (f32)(v130 * v130)) + (f32)(v131 * v131));
              if (NakamaData)
              {
                v163 = pos;
                vct_A = v163;
                v135 = NakamaData->pos;
                goto LABEL_319;
LABEL_320:
                goto LABEL_321;
LABEL_319:
                vct_B = v135;
                goto LABEL_320;
LABEL_321:
                vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
                goto LABEL_323;
LABEL_324:
                goto LABEL_325;
LABEL_323:
                v136 = &vf00.x;
                v137 = v136[4];
                v138 = v136[5];
                v139 = v136[6];
                goto LABEL_324;
LABEL_325:
                v141 = sqrtf((f32)((f32)(v137 * v137) + (f32)(v138 * v138)) + (f32)(v139 * v139));
                if (v133 < v141)
                  v141 = v133;
                if (v141 >= v119)
                {
LABEL_298:
                  v44 = *v121;
                  v119 = v141;
                }
              }
              else
              {
                v141 = v133 + 10.0;
                if (v133 < (f32)(v133 + 10.0))
                  v141 = v133;
                if (v141 >= v119)
                  goto LABEL_298;
              }
              ++v121;
              if (!--v120)
                return v44;
              continue;
            }
          }
          if (v96 >= 15)
            goto LABEL_296;
LABEL_293:
          v118 = v97 + 1;
          *(u32 *)(v5 + 4 * v97 + 32) = v46 + 8;
        }
        if (v96 >= 10)
          goto LABEL_295;
        goto LABEL_297;
      }
    }
  }
  if ((u32)devilid > 0x12C)
  {
    if ((devilid & 0xFFFFFFFE) != 0x130)
    {
      if (devilid != 310)
        return 1;
LABEL_47:
      v169 = UserData->pos;
      vct_A = v169;
LABEL_52:
      v23 = -1.0;
      v24 = -1;
      v25 = 2;
      v26 = *(u64 *)&vct_A.x;
      v27 = vct_A.z;
      while (1)
      {
        sBtlGetPointData(v25, &pos, &rot);
        pos.w = 0.0;
        v30 = *(u64 *)&pos.x;
        v31 = pos.z;
        *(u64 *)&vct_A.x = v30;
        vct_A.z = v31;
        vct_A.w = 0.0;
        *(u64 *)&vct_B.x = v26;
        vct_B.z = v27;
        vct_B.w = 0.0;
        vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
        v35 = &vf00.x;
        v36 = v35[4];
        v37 = v35[5];
        v38 = v35[6];
        v29 = sqrtf((f32)((f32)(v36 * v36) + (f32)(v37 * v37)) + (f32)(v38 * v38));
        if (v29 >= v23)
        {
          v23 = v29;
          v24 = v25;
        }
        if (++v25 == 8)
        {
          if (v24 == -1)
            return 1;
          else
            return v24;
        }
      }
      goto LABEL_52;
    }
    goto LABEL_11;
  }
  if (devilid == 300)
    goto LABEL_81;
  if (Data->para->devilid != 292)
    return 1;
  v153 = v4;
  v9 = 1000000.0;
  v10 = 5;
  v11 = 5;
  do
  {
    sBtlGetPointData(v10, &pos, &rot);
    v154 = pos;
    vct_A = v154;
    v15 = UserData->pos;
    vct_B = v15;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v16 = &vf00.x;
    v17 = v16[4];
    v18 = v16[5];
    v19 = v16[6];
    v13 = sqrtf((f32)((f32)(v17 * v17) + (f32)(v18 * v18)) + (f32)(v19 * v19));
    if (v13 < v9 && v13 > 100.0)
    {
      v9 = v13;
      v11 = v10;
    }
    ++v10;
  }
  while (v10 != 14);
  v68 = v153;
  if ((u32)(v11 - 5) <= 8)
  {
    v69 = 4 * (v11 - 5);
    v70 = *(u32 *)((char *)&unk_3E65688 + v69);
    v71 = *(u32 *)((char *)&unk_3E656AC + v69);
    LODWORD(v69) = *(u32 *)((char *)&unk_3E656D0 + v69);
    v153[8] = v70;
    v153[9] = v71;
    v153[10] = v69;
  }
  v72 = 0;
  while (2)
  {
    UnitMng = wk->UnitMng;
    if (v72 >= UnitMng->number)
      return v68[8];
    pUnit = wk->UnitMng->pUnitL[v72]->pUnit;
    if (!pUnit)
      goto LABEL_154;
    if (pUnit->actwk->status == 10 || pUnit->para->devilid != 182 || pUnit->GroupID == 3)
    {
      goto LABEL_154;
    }
    v77 = v68[8];
    sBtlGetPointData(v77, &pos, &rot);
    v170 = pos;
    v68 = v153;
    goto LABEL_169;
LABEL_170:
    vct_A = v170;
    v79 = pUnit->pos;
    goto LABEL_171;
LABEL_172:
    vct_B = v79;
    goto LABEL_173;
LABEL_174:
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    goto LABEL_175;
LABEL_176:
    v80 = &vf00.x;
    v81 = v80[4];
    v82 = v80[5];
    v83 = v80[6];
    goto LABEL_9016;
LABEL_169:
    goto LABEL_170;
LABEL_171:
    goto LABEL_172;
LABEL_173:
    goto LABEL_174;
LABEL_175:
    goto LABEL_176;
LABEL_9016:
    if (sqrtf((f32)((f32)(v81 * v81) + (f32)(v82 * v82)) + (f32)(v83 * v83)) >= 100.0)
    {
LABEL_154:
      ++v72;
      continue;
    }
    break;
  }
  for (i = 0; ; ++i)
  {
    v146 = wk->UnitMng;
    if (i >= v146->number)
      break;
    v146 = wk->UnitMng;
    v147 = v146->pUnitL[i]->pUnit;
    if (v147 && v147->actwk->status != 10 && v147->para->devilid == 182 && v147->GroupID != 3)
    {
      v148 = v68[9];
      sBtlGetPointData(v148, &pos, &rot);
      v149 = pos.x;
      v150 = pos.y;
      v151 = pos.z;
      w = pos.w;
      sub_1B332C0(0, v149, v150, v151, w);
      sub_1B33360(0, v147->pos.x, v147->pos.y, v147->pos.z, v147->pos.w);
      sub_1B33400(0);
      v68 = v153;
      if ((loc_1CDE880)(0) < 100.0)
        return v153[10];
    }
  }
  return v68[9];
}

// 0x2108c90: s32 SBTL_NAKAMAICON_ON(void)
#define SBTL_NAKAMAICON_ON() (1)

// 0x2108ca0: s32 SBTL_NAKAMAICON_OFF(void)
#define SBTL_NAKAMAICON_OFF() (1)

// 0x2108cb0: s32 SBTL_LOADBLOCK(void)
static inline s32 SBTL_LOADBLOCK(void) {
  if (CheckLoadData(0))
    return 0;
  wk->status2 |= 0x200u;
  return 1;
}

// 0x2108d40: s32 SBTL_ENDBLOCK(void)
static inline s32 SBTL_ENDBLOCK(void) {
  wk->status2 &= ~0x200u;
  return 1;
}

// 0x2108db0: s32 SBTL_BUSTUP_ON(void)
static inline s32 SBTL_BUSTUP_ON(void) {
  wk->status2 |= 0xE0u;
  return 1;
}

// 0x2108e20: s32 SBTL_BUSTUP_OFF(void)
static inline s32 SBTL_BUSTUP_OFF(void) {
  s32 IntPara;
  u32 status2;

  IntPara = scrGetIntPara(0);
  status2 = wk->status2 & 0xFFFFFF7F;
  wk->status2 = status2;
  if (IntPara != 1)
  {
    status2 = wk->status2;
    wk->status2 = status2 & 0xFFFFFF9F;
  }
  return 1;
}

// 0x2108ef0: s32 SBTL_CHECK_PLAYERDEAD(void)
static inline s32 SBTL_CHECK_PLAYERDEAD(void) {
  bool v2;

  v2 = sBtlCheckPlayerDead();
  scrSetIntReturnValue(v2);
  return 1;
}

// 0x2108fb0: s32 SBTL_SET_DVLTK(void)
static inline s32 SBTL_SET_DVLTK(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  if (IntPara == 1)
  {
    wk->status2 &= ~0x80u;
    return 1;
  }
  else
  {
    wk->status2 |= 0x80u;
    return 1;
  }
}

// 0x2109090: s32 SBTL_LOADPROC(void)
static inline s32 SBTL_LOADPROC(void) {
  s32 scrLoadStat;
  s32 v4;
  SBATTLE_WORK *v5;
  bool EffectData_ID;
  SBATTLE_WORK *wk_local;
  s32 v9;

  if (scrGetIntPara(0) != 1)
    return 1;
  scrLoadStat = wk->scrLoadStat;
  if (scrLoadStat == 2)
  {
    EffectData_ID = sBtlLoadEffectData_ID(231);
    if (EffectData_ID)
    {
      wk_local = wk;
      ++wk_local->scrLoadStat;
      wk_local->status2 &= ~0x200u;
      goto LABEL_33;
    }
    goto LABEL_31;
  }
  if (scrLoadStat == 1)
  {
    if (sBtlLoadEffectData_ID(232))
    {
      sBtlLoadEffectData_ID(231);
      v5 = wk;
      goto LABEL_30;
    }
    goto LABEL_33;
  }
  if (!scrLoadStat)
  {
    v4 = CheckLoadData(0);
    if (!v4)
    {
      v5 = wk;
      v5->status2 |= 0x200u;
LABEL_30:
      ++v5->scrLoadStat;
    }
  }
LABEL_31:
LABEL_33:
  v9 = wk->scrLoadStat == 3;
  scrSetIntReturnValue(v9);
  return v9;
}

// 0x2109320: s32 AI_CHK_CHKSKL_R(void)
static inline s32 AI_CHK_CHKSKL_R(void) {
  SBTLUNIT_WORK *Data;
  s32 IntPara;
  s32 v4;

  Data = GetData();
  IntPara = scrGetIntPara(0);
  v4 = sBtlSupport_AI_CHK_CHKSKL_R(Data, IntPara);
  scrSetIntReturnValue(v4);
  return 1;
}

// 0x21093d0: s32 SBTL_SETCAMMOD(void)
static inline s32 SBTL_SETCAMMOD(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  sBtlSetMode(IntPara);
  return 1;
}

// 0x2109470: s32 SBTL_GETUNITPOS(void)
static inline s32 SBTL_GETUNITPOS(void) {
  s32 IntPara;
  s32 v2;
  s32 v3;
  SBATTLE_WORK *wk_local;
  sdfVector4_t *p_scrVector;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  switch (IntPara)
  {
    case -4:
      v3 = 1;
      goto LABEL_12;
    case -3:
      v3 = 0;
LABEL_12:
      if (!Support_GetNakamaData(v3))
        goto LABEL_25;
      goto LABEL_15;
    case -2:
      if (Support_GetUserData())
        goto LABEL_15;
      goto LABEL_25;
    case -1:
      if (!GetData())
        goto LABEL_25;
      goto LABEL_15;
    default:
      if (wk->scrUnitList[IntPara])
      {
LABEL_15:
        if (v2 < 0)
          return 1;
        wk_local = wk;
        p_scrVector = &wk_local->scrVector;
        *p_scrVector = vct_A;
        return 1;
      }
LABEL_25:
      scrSetIntReturnValue(0);
      return 1;
  }
}

// 0x2109670: s32 SBTL_SETDISP_FLG(void)
static inline s32 SBTL_SETDISP_FLG(void) {
  s32 IntPara;
  s32 v2;
  s32 v3;
  SBTLUNIT_WORK *NakamaData;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  switch (IntPara)
  {
    case -4:
      v3 = 1;
      goto LABEL_12;
    case -3:
      v3 = 0;
LABEL_12:
      NakamaData = Support_GetNakamaData(v3);
      if (!NakamaData)
        return 1;
      goto LABEL_17;
    case -2:
      NakamaData = Support_GetUserData();
      if (!NakamaData)
        return 1;
      goto LABEL_17;
    case -1:
      NakamaData = GetData();
      if (NakamaData)
        goto LABEL_17;
      return 1;
    default:
      NakamaData = wk->scrUnitList[IntPara];
      if (!NakamaData)
        return 1;
LABEL_17:
      NakamaData->vstatus = NakamaData->vstatus & 0xFFFFEFFF | ((v2 == 0) << 12);
      return 1;
  }
}

// 0x21097a0: s32 SBTL_SET_UNITFLG(void)
static inline s32 SBTL_SET_UNITFLG(void) {
  s32 IntPara;
  s32 v2;
  s32 v3;
  s32 v4;
  SBTLUNIT_WORK *NakamaData;
  s32 flg;
  s32 v8;
  s32 v9;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  v3 = scrGetIntPara(2);
  switch (IntPara)
  {
    case -4:
      v4 = 1;
      goto LABEL_11;
    case -3:
      v4 = 0;
LABEL_11:
      NakamaData = Support_GetNakamaData(v4);
      break;
    case -2:
      NakamaData = Support_GetUserData();
      break;
    case -1:
      NakamaData = GetData();
      break;
    default:
      NakamaData = wk->scrUnitList[IntPara];
      break;
  }
  flg = NakamaData->flg;
  v8 = flg & ~v3;
  v9 = flg | v3;
  if (!v2)
    v9 = v8;
  NakamaData->flg = v9;
  return 1;
}

// 0x21098e0: s32 SBTL_SET_CAMPOS(void)
static inline s32 SBTL_SET_CAMPOS(void) {
  sdfVector4_t v2;

  v2.x = 0.0;
  v2.y = 0.0;
  v2.z = 0.0;
  v2.w = 0.0;
  sBtlSetPos(v2);
  return 1;
}

// 0x2109950: s32 SBTL_SET_CAMPOSSLP(void)
static inline s32 SBTL_SET_CAMPOSSLP(void) {
  sdfVector4_t v2;

  v2.x = 0.0;
  v2.y = 0.0;
  v2.z = 0.0;
  v2.w = 0.0;
  sBtlSetPosSlp(v2);
  return 1;
}

// 0x21099c0: s32 SBTL_SET_CAMBGNPOSSLP(void)
static inline s32 SBTL_SET_CAMBGNPOSSLP(void) {
  sBtlBgnPosSlp();
  return 1;
}

// 0x2109a40: s32 SBTL_GET_CAMPOSSLP(void)
static inline s32 SBTL_GET_CAMPOSSLP(void) {
  s32 PosSlp;

  PosSlp = sBtlGetPosSlp();
  scrSetIntReturnValue(PosSlp);
  return 1;
}

// 0x2109b00: s32 SBTL_SET_CAMTGT(void)
static inline s32 SBTL_SET_CAMTGT(void) {
  sdfVector4_t v2;

  v2.x = 0.0;
  v2.y = 0.0;
  v2.z = 0.0;
  v2.w = 0.0;
  sBtlSetTgt(v2);
  return 1;
}

// 0x2109b70: s32 SBTL_SET_CAMTGTSLP(void)
static inline s32 SBTL_SET_CAMTGTSLP(void) {
  sdfVector4_t v2;

  v2.x = 0.0;
  v2.y = 0.0;
  v2.z = 0.0;
  v2.w = 0.0;
  sBtlSetTgtSlp(v2);
  return 1;
}

// 0x2109be0: s32 SBTL_SET_CAMBGNTGTSLP(void)
static inline s32 SBTL_SET_CAMBGNTGTSLP(void) {
  sBtlBgnTgtSlp();
  return 1;
}

// 0x2109c60: s32 SBTL_GET_CAMTGTSLP(void)
static inline s32 SBTL_GET_CAMTGTSLP(void) {
  s32 TgtSlp;

  TgtSlp = sBtlGetTgtSlp();
  scrSetIntReturnValue(TgtSlp);
  return 1;
}

// 0x2109d20: s32 AI_GET_LIST_UNIT(void)
static inline s32 AI_GET_LIST_UNIT(void) {
  s32 IntPara;
  s32 v3;
  SBTLAI_WORK *v5;
  s32 scrListID;
  SBTLAI_WORK *aiwk;

  IntPara = scrGetIntPara(0);
  if (IntPara == -1)
  {
    aiwk = GetData()->aiwk;
    scrListID = aiwk->scrListID;
    goto LABEL_8;
  }
  v3 = IntPara;
  v5 = wk->scrUnitList[v3]->aiwk;
  scrListID = v5->scrListID;
LABEL_8:
  scrSetIntReturnValue(scrListID);
  return 1;
}

// 0x2109e40: s32 AI_SET_LIST_UNIT_SP(void)
static inline s32 AI_SET_LIST_UNIT_SP(void) {
  SBTLUNIT_WORK *Data;
  s32 IntPara;
  SBTLUNIT_WORK *scrUnitList;
  SBTLUNIT_WORK *v5;
  SBTLUNIT_WORK *v6;
  SBTLUNIT_WORK *v7;
  Il2CppClass **v8;

  Data = GetData();
  IntPara = scrGetIntPara(0);
  scrUnitList = wk->scrUnitList;
  if (scrUnitList[IntPara])
  {
    scrUnitList = wk->scrUnitList;
    if (scrUnitList[IntPara + 1])
      IntPara += 2;
    else
      ++IntPara;
  }
  v5 = wk->scrUnitList;
  v6 = GetData();
  v7 = v6;
  v8 = &v5->obj.klass + IntPara;
  v8[4] = v7;
  ++wk->scrUnitNum;
  Data->aiwk->scrListID = IntPara;
  return 1;
}

// 0x2109fb0: s32 SBTL_SET_CAMERA_MODE(void)
static inline s32 SBTL_SET_CAMERA_MODE(void) {
  SBTLUNIT_WORK *v1;
  u32 IntPara;
  s32 v3;
  s32 v4;
  f32 v5;
  f32 v6;
  s64 v8;
  f32 *p_x;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  s64 v18;
  s32 v19;
  f32 *v22;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 v29;
  s32 v34;
  s32 v37;
  sdfVector4_t *v38;
  sdfVector4_t *v39;
  SBTLUNIT_WORK *NakamaData;
  s32 v42;
  SBTLUNIT_WORK *UserData;
  f32 *v46;
  f32 *v49;
  f32 v50;
  f32 v51;
  f32 v52;
  f32 v53;
  f32 *v56;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  s32 v61;
  s32 v63;
  f32 *v64;
  sdfVector4_t v68;
  sdfMatrix4_t v69;
  sdfMatrix4_t v70;
  sdfVector4_t v71;
  sdfVector4_t v72;
  sdfVector4_t v73;

  v1 = Allocate(SBTLUNIT_WORK);
  _ctor(v1, 0);
  IntPara = scrGetIntPara(0);
  v3 = scrGetIntPara(1);
  v4 = scrGetIntPara(2);
  if (IntPara == 4)
  {
    sBtlSetMode(12);
    sBtlGetPointData(v3, &v1->pos, &v1->rot);
    v5 = v1->pos.x;
    v6 = v1->pos.y + -200.0;
    v8 = *(u64 *)&v1->pos.z;
    v1->pos.y = v6;
    vct_A.x = v5;
    vct_A.y = v6;
    *(u64 *)&vct_A.z = v8;
    p_x = &vf00.x;
    v12 = p_x[4];
    v13 = p_x[5];
    v14 = p_x[6];
    v15 = p_x[7];
    sBtlGetPointData(v4, &v1->pos, &v1->rot);
    v16 = v1->pos.x;
    v17 = v1->pos.y + -100.0;
    v18 = *(u64 *)&v1->pos.z;
    v19 = (u8)byte_5755EF5;
    v1->pos.y = v17;
    if (v19)
    {
      goto LABEL_17;
    }
    else
    {
LABEL_17:
      vct_A.x = v16;
      vct_A.y = v17;
      *(u64 *)&vct_A.z = v18;
      goto LABEL_18;
    }
    vct_A.x = v16;
    vct_A.y = v17;
    *(u64 *)&vct_A.z = v18;
LABEL_18:
LABEL_19:
    v22 = &vf00.x;
    v72.x = v12;
    v72.y = v13;
    v72.z = v14;
    v72.w = v15;
LABEL_20:
    v26 = v22[4];
    v27 = v22[5];
    v28 = v22[6];
    v29 = v22[7];
    sBtlSetPosSlp(v72);
    v73.x = v26;
    v73.y = v27;
    v73.z = v28;
    v73.w = v29;
LABEL_21:
    sBtlSetTgtSlp(v73);
    sBtlBgnPosSlp();
    sBtlBgnTgtSlp();
    return 1;
LABEL_71:
    goto LABEL_19;
  }
  switch (v3)
  {
    case -4:
      v34 = 1;
      goto LABEL_42;
    case -3:
      v34 = 0;
LABEL_42:
      NakamaData = Support_GetNakamaData(v34);
      v42 = v4 + 4;
      goto LABEL_43;
    case -2:
      NakamaData = Support_GetUserData();
      v42 = v4 + 4;
      if ((u32)(v4 + 4) > 3)
        goto LABEL_47;
      goto LABEL_43;
    case -1:
      NakamaData = GetData();
      v42 = v4 + 4;
      if ((u32)(v4 + 4) > 3)
        goto LABEL_47;
      goto LABEL_43;
    default:
      if (v3 > 99)
      {
        v37 = v3 - 100;
        v38 = &v1->pos;
        v39 = &v1->rot;
        sBtlGetPointData(v37, v38, v39);
        v68 = *v38;
LABEL_39:
        NakamaData = 0;
        vct_A = v68;
        v42 = v4 + 4;
        if ((u32)(v4 + 4) > 3)
          goto LABEL_47;
LABEL_43:
        switch (v42)
        {
          case 0:
            UserData = Support_GetNakamaData(1);
            if (IntPara > 3)
              return 1;
            goto LABEL_58;
          case 1:
            UserData = Support_GetNakamaData(0);
            if (IntPara > 3)
              return 1;
            goto LABEL_58;
          case 2:
            UserData = Support_GetUserData();
            if (IntPara > 3)
              return 1;
            goto LABEL_58;
          case 3:
            UserData = GetData();
            goto LABEL_58;
          default:
            goto LABEL_47;
        }
        goto LABEL_39;
      }
      NakamaData = wk->scrUnitList[v3];
      v42 = v4 + 4;
      if ((u32)(v4 + 4) <= 3)
        goto LABEL_43;
LABEL_47:
      UserData = wk->scrUnitList[v4];
      if (IntPara <= 3)
      {
LABEL_58:
        switch (IntPara)
        {
          case 0u:
            sBtlSetMode(2);
            return 1;
          case 1u:
            sBtlSetMode(12);
            sBtlGetUnitHelperPos(NakamaData, 0);
            v46 = &vf00.x;
            v12 = v46[4];
            v13 = v46[5];
            v14 = v46[6];
            v15 = v46[7];
            sBtlGetUnitHelperPos(UserData, 0);
            goto LABEL_71;
          case 2u:
            sBtlSetMode(12);
            v49 = &vf00.x;
            v50 = v49[4];
            v51 = v49[5];
            v53 = v49[6];
            v52 = v49[7];
            sBtlGetUnitHelperPos(UserData, 0);
            v22 = &vf00.x;
            v72.x = v50;
            v72.y = v51;
            v72.z = v53;
            v72.w = v52;
            goto LABEL_20;
          case 3u:
            sBtlSetMode(12);
            sBtlGetUnitHelperPos(UserData, 0);
            v56 = &vf00.x;
            x = v56[4];
            y = v56[5];
            z = v56[6];
            w = v56[7];
            v61 = (u8)byte_5756085;
            vct_A = (struct sdfVector4_t)xmmword_3CFD620;
            get_transpose(&v70, &mtx_A, 0);
            v69 = v70;
            v71 = op_Multiply_60923920(&v69, vct_A, 0);
            vct_A = v71;
            v63 = (u8)byte_5756177;
            vct_B = (struct sdfVector4_t)xmmword_3CFB1C0;
            if (v63)
            {
              goto LABEL_100;
            }
            else
            {
LABEL_100:
              vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
              goto LABEL_101;
            }
            vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
LABEL_101:
            v64 = &vf00.x;
            v64[8] = x;
            v64[9] = y;
            v64[10] = z;
            v64[11] = w;
            vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
            sBtlSetPosSlp(vct_A);
            v73.x = x;
            v73.y = y;
            v73.z = z;
            v73.w = w;
            goto LABEL_21;
          default:
            return 1;
        }
      }
      return 1;
  }
}

// 0x210ab10: s32 FRC_WAIT(void)
static inline s32 FRC_WAIT(void) {
  sBtlBgnWaitALL(0);
  return 1;
}

// 0x210ab70: s32 FRC_WAIT_OUT(void)
static inline s32 FRC_WAIT_OUT(void) {
  s32 IntPara;
  SBTLUNIT_WORK *v3;

  IntPara = scrGetIntPara(0);
  v3 = wk->scrUnitList[IntPara];
  if (!v3)
    return 1;
  v3 = wk->scrUnitList[IntPara];
  sBtlEndWait(v3);
  return 1;
}

// 0x210acb0: s32 FRC_WAIT_OUT_ALL(void)
static inline s32 FRC_WAIT_OUT_ALL(void) {
  sBtlEndWaitALL(0, 0);
  return 1;
}

// 0x210ad20: s32 SBTL_GET_CUTNO(void)
static inline s32 SBTL_GET_CUTNO(void) {
  s32 event_icon;

  event_icon = wk->event_icon;
  scrSetIntReturnValue(event_icon);
  return 1;
}

// 0x210af10: s32 AI_SET_TIME(void)
static inline s32 AI_SET_TIME(void) {
  s32 IntPara;
  s8 v2;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  if (IntPara)
  {
    wk->aitimecount = IntPara;
  }
  wk->aitimeflg = v2;
  gb_btlaitime = 0;
  return 1;
}

// 0x210b030: s32 AI_CHK_TIME(void)
static inline s32 AI_CHK_TIME(void) {
  s32 aitimecount;
  s32 v5;
  s32 gb_btlaitime_local;

  if (!wk->aitimeflg)
  {
    gb_btlaitime_local = 1;
    goto LABEL_11;
  }
  aitimecount = wk->aitimecount;
  if (!aitimecount)
  {
    gb_btlaitime_local = gb_btlaitime;
    goto LABEL_11;
  }
  v5 = aitimecount - gb_btlaitime;
  gb_btlaitime_local = v5 & ~(v5 >> 31);
LABEL_11:
  scrSetIntReturnValue(gb_btlaitime_local);
  return 1;
}

// 0x210b1f0: s32 AI_SET_AISHOU(void)
static inline s32 AI_SET_AISHOU(void) {
  GetData();
  return 1;
}

// 0x210b240: s32 AI_SET_EFFCLR(void)
static inline s32 AI_SET_EFFCLR(void) {
  s32 IntPara;
  s32 v2;
  s32 v3;
  SBTLUNIT_WORK *NakamaData;
  s32 mdlEffClr;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  switch (IntPara)
  {
    case -4:
      v3 = 1;
      goto LABEL_12;
    case -3:
      v3 = 0;
LABEL_12:
      NakamaData = Support_GetNakamaData(v3);
      if (!NakamaData->bMdlEffClr)
        goto LABEL_17;
      goto LABEL_15;
    case -2:
      NakamaData = Support_GetUserData();
      if (NakamaData->bMdlEffClr)
        goto LABEL_15;
      goto LABEL_17;
    case -1:
      NakamaData = GetData();
      if (!NakamaData->bMdlEffClr)
        goto LABEL_17;
      goto LABEL_15;
    default:
      NakamaData = wk->scrUnitList[IntPara];
      if (NakamaData->bMdlEffClr)
      {
LABEL_15:
        mdlEffClr = NakamaData->mdlEffClr;
      }
      else
      {
LABEL_17:
        NakamaData->bMdlEffClr = 1;
        mdlEffClr = -2139062144;
        NakamaData->mdlEffClr = -2139062144;
      }
      NakamaData->mdlEffClrTgt = v2;
      NakamaData->mdlEffClrBgn = mdlEffClr;
      NakamaData->mdlEffClrFrm = 180;
      return 1;
  }
}

// 0x210b390: s32 AI_SET_MAGHP(void)
#define AI_SET_MAGHP() (1)

// 0x210b3a0: s32 AI_SET_MAGOUT(void)
#define AI_SET_MAGOUT() (1)

// 0x210b3b0: s32 AI_CHK_MAGOUT(void)
static inline s32 AI_CHK_MAGOUT(void) {
  scrSetIntReturnValue(0);
  return 1;
}

// 0x210b410: s32 AI_MAGOUT_START(void)
#define AI_MAGOUT_START() (1)

// 0x210b420: s32 AI_MAGOUT_START_NUM(void)
static inline s32 AI_MAGOUT_START_NUM(void) {
  s32 IntPara;
  s32 v2;
  SBTLUNIT_WORK *Data;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  Data = GetData();
  sBtlAddMag(IntPara);
  if (!v2)
    return 1;
  sBtlGetUnitHelperPos(Data, 1);
  if (sdfModelGetMarkPos(Data->hEveUnit->Model->modelRoot, 1))
  {
    goto LABEL_16;
  }
  else
  {
    sdfModelGetMarkPos(Data->hEveUnit->Model->modelRoot, 0);
LABEL_16:
    goto LABEL_17;
  }
LABEL_17:
  return 1;
}

// 0x210b640: s32 AI_SET_EFFCLR_SP(void)
static inline s32 AI_SET_EFFCLR_SP(void) {
  s32 IntPara;
  SBTLUNIT_WORK *Data;
  SBTLUNIT_WORK *v3;
  u32 v6;

  IntPara = scrGetIntPara(0);
  Data = GetData();
  v3 = Data;
  if (!Data->bMdlEffClr)
  {
    Data->bMdlEffClr = 1;
    Data->mdlEffClr = -2139062144;
    goto LABEL_7;
  }
LABEL_7:
  v6 = script_eff_colortbl[IntPara];
  v3->mdlEffClrBgn = v3->mdlEffClr;
  v3->mdlEffClrTgt = v6;
  v3->mdlEffClrFrm = 180;
  return 1;
}

// 0x210b730: s32 AI_SET_AISHOU_SP(void)
static inline s32 AI_SET_AISHOU_SP(void) {
  SBTLUNIT_WORK *Data;
  s32 IntPara;

  Data = GetData();
  IntPara = scrGetIntPara(0);
  ClassCopy(Data->para->aisyo, script_aisyo_tbl[IntPara], 0);
  return 1;
}

// 0x210b7f0: s32 SBTL_SET_CAMERA_MOVE(void)
static inline s32 SBTL_SET_CAMERA_MOVE(void) {
  s32 IntPara;
  S_CameraMoveDt *CamMovePtn;

  IntPara = scrGetIntPara(0);
  sBtlSetMode(13);
  sBtlSetCmbBfrPos();
  CamMovePtn = sBtlGetCamMovePtn(IntPara);
  sBtlSetMove(CamMovePtn, 1);
  return 1;
}

// 0x210b8b0: s32 SBTL_IS_CAMERA_MOVE_END(void)
static inline s32 SBTL_IS_CAMERA_MOVE_END(void) {
  bool IsMoveEnd;

  IsMoveEnd = sBtlIsMoveEnd();
  scrSetIntReturnValue(IsMoveEnd);
  return 1;
}

// 0x210b970: s32 AI_CHK_BOSSEVENT(void)
static inline s32 AI_CHK_BOSSEVENT(void) {
  s32 bosseventflg;

  bosseventflg = wk->bosseventflg;
  scrSetIntReturnValue(bosseventflg);
  return 1;
}

// 0x210ba40: s32 AI_SET_MAGOUT_TYPE(void)
static inline s32 AI_SET_MAGOUT_TYPE(void) {
  s32 IntPara;
  s32 v2;
  SBTLUNIT_WORK *Data;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  Data = GetData();
  if (IntPara == 2)
  {
    Data->mag_on3 = v2;
    return 1;
  }
  else if (IntPara == 1)
  {
    Data->mag_on2 = v2;
    return 1;
  }
  else
  {
    if (!IntPara)
      Data->mag_on1 = v2;
    return 1;
  }
}

// 0x210bb00: s32 AI_SET_DEADEVENT_TYPE(void)
static inline s32 AI_SET_DEADEVENT_TYPE(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  GetData()->dead_on = IntPara;
  return 1;
}

// 0x210bb70: s32 AI_MOTION_SE(void)
static inline s32 AI_MOTION_SE(void) {
  SBTLUNIT_WORK *Data;
  s32 IntPara;
  s32 devilid;
  u32 DevilSESub;

  Data = GetData();
  IntPara = scrGetIntPara(0);
  devilid = Data->para->devilid;
  DevilSESub = sBtlGetDevilSESub(devilid, IntPara);
  sBtlPlaySE(DevilSESub);
  return 1;
}

// 0x210bc30: s32 AI_CHK_LUCKY(void)
static inline s32 AI_CHK_LUCKY(void) {
  u32 status3;

  status3 = wk->status3;
  scrSetIntReturnValue((status3 & 0x10FF) != 0);
  return 1;
}

// 0x210bd00: s32 AI_CHK_BOSSRLT_TIME(void)
static inline s32 AI_CHK_BOSSRLT_TIME(void) {
  s32 RouletteAfterTime;
  s32 IntPara;

  RouletteAfterTime = wk->RouletteAfterTime;
  IntPara = scrGetIntPara(0);
  scrSetIntReturnValue(RouletteAfterTime >= IntPara);
  return 1;
}

// 0x210bdf0: s32 AI_CHK_BOSSRLT_NUM(void)
static inline s32 AI_CHK_BOSSRLT_NUM(void) {
  s32 RouletteUseCnt;
  s32 IntPara;

  RouletteUseCnt = wk->RouletteUseCnt;
  IntPara = scrGetIntPara(0);
  scrSetIntReturnValue(RouletteUseCnt >= IntPara);
  return 1;
}

// 0x210bee0: s32 SBTL_EVENT_TIMING(void)
#define SBTL_EVENT_TIMING() (1)

// 0x210bef0: s32 AI_CONTINUE_WAIT(void)
static inline s32 AI_CONTINUE_WAIT(void) {
  SBTLUNIT_WORK *Data;
  s32 IntPara;
  s32 devilid;
  s32 v4;
  s32 continue_timer;
  signed s32 v6;
  s32 result;
  s32 v8;

  Data = GetData();
  IntPara = scrGetIntPara(0);
  scrGetIntPara(1);
  scrGetIntPara(2);
  scrGetIntPara(3);
  devilid = Data->para->devilid;
  v4 = sBtlGetContinueRaito(devilid) * IntPara;
  if (v4 < 100)
    return 1;
  continue_timer = Data->continue_timer;
  v6 = v4 / 0x64u;
  result = continue_timer + 1 >= v6;
  if (continue_timer + 1 < v6)
    v8 = continue_timer + 1;
  else
    v8 = 0;
  Data->continue_timer = v8;
  return result;
}

// 0x210c020: s32 AI_ACTION_STOP_CHK(void)
static inline s32 AI_ACTION_STOP_CHK(void) {
  u32 status;
  s32 mode;
  s32 v6;

  status = wk->status;
  mode = wk->mode;
  if (mode == 5)
    v6 = 1;
  else
    v6 = HIWORD(status) & 1;
  scrSetIntReturnValue(v6);
  return 1;
}

// 0x210c120: s32 HUUMA_KAIWA_SELSET(void)
static inline s32 HUUMA_KAIWA_SELSET(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  hk_seltype = IntPara;
  return 1;
}

// 0x210c1d0: s32 HUUMA_KAIWA_SELGET(void)
static inline s32 HUUMA_KAIWA_SELGET(void) {
  scrSetIntReturnValue(hk_seltype);
  return 1;
}

// 0x210c290: s32 HUUMA_KAIWA_RESULT(void)
static inline s32 HUUMA_KAIWA_RESULT(void) {
  s32 IntPara;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 huuma_targetID;
  SBTLUNIT_WORK *v8;
  s32 MessageHandle;
  s32 devilid;
  s32 v11;
  u64 *v12;
  SBTLUNIT_WORK *NakamaData;
  SBTLUNIT_WORK *v14;
  SBTLUNIT_WORK *v16;
  SBATTLE_WORK *v18;
  s32 v20;
  s32 v21;
  SBATTLE_WORK *v23;
  sdatParaWork_t *now;
  s16 v25;
  s16 *p_str;
  s16 str;
  SBATTLE_WORK *v30;
  s32 magMax;
  SBATTLE_WORK *v34;
  sdatParaWork_t *v35;
  s16 tec;
  SBATTLE_WORK *v38;
  sdatParaWork_t *v39;
  s16 vit;
  SBATTLE_WORK *v42;
  sdatParaWork_t *v43;
  s16 luck;

  IntPara = scrGetIntPara(0);
  wk->scrMsgID = 0;
  UnitMng = wk->UnitMng;
  huuma_targetID = wk->huuma_targetID;
  v8 = sBtlSearchUnit_ID(UnitMng, huuma_targetID);
  MessageHandle = scrGetMessageHandle();
  if ((MessageHandle & 0x80000000) == 0)
  {
    devilid = v8->para->devilid;
    itfMesMngSetVar(MessageHandle, 0, devilid, 1);
  }
  if (IntPara == 1)
  {
    v20 = sub_1905740(4, 0);
    if ((s32)sub_1905740(100, 0) >= 10)
      v21 = 1;
    else
      v21 = 2;
    if ((MessageHandle & 0x80000000) == 0)
    {
      itfMesMngSetVar(MessageHandle, 1, v21, 0);
    }
    switch (v20)
    {
      case 0:
        v23 = wk;
        v23->scrMsgID = 2;
        v23->huuma_status_up[0] = v21;
        now = v8->para->now;
        str = now->str;
        p_str = &now->str;
        v25 = str;
        break;
      case 1:
        v34 = wk;
        v34->scrMsgID = 3;
        v34->huuma_status_up[1] = v21;
        v35 = v8->para->now;
        tec = v35->tec;
        p_str = &v35->tec;
        v25 = tec;
        break;
      case 2:
        v38 = wk;
        v38->scrMsgID = 4;
        v38->huuma_status_up[2] = v21;
        v39 = v8->para->now;
        vit = v39->vit;
        p_str = &v39->vit;
        v25 = vit;
        break;
      case 3:
        v42 = wk;
        v42->scrMsgID = 5;
        v42->huuma_status_up[3] = v21;
        v43 = v8->para->now;
        luck = v43->luck;
        p_str = &v43->luck;
        v25 = luck;
        break;
      default:
        goto LABEL_45;
    }
    *p_str = v25 + v21;
    LimitRange_2(p_str, 0, 40);
  }
  else if (IntPara)
  {
    wk->scrMsgID = 8;
  }
  else
  {
    v11 = sub_1905740(100, 0);
    v12 = NewSpecific(SBTLUNIT_WORK, 2u);
    NakamaData = Support_GetNakamaData(0);
    v14 = NakamaData;
    v12[5] = v16;
    if (v11 >= 50 && evtBitCheck(9998))
    {
      v18 = wk;
      v18->scrMsgID = 6;
      v18->sprit_waza = 4000;
    }
    else
    {
      v30 = wk;
      v30->scrMsgID = 7;
      magMax = v30->magMax;
      sBtlAddMag(magMax);
LABEL_45:
    }
  }
  scrSetIntReturnValue(IntPara);
  return 1;
}

// 0x210c740: s32 BATTLE_STOP_EFF(void)
static inline s32 BATTLE_STOP_EFF(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  wk->battlStopEff = IntPara != 0;
  return 1;
}

// 0x210c7e0: s32 AI_SET_SKILL_MOTION(void)
static inline s32 AI_SET_SKILL_MOTION(void) {
  SBTLUNIT_WORK *Data;

  Data = GetData();
  Data->req_skill_motion = scrGetIntPara(0);
  return 1;
}

// 0x210c850: s32 AI_SET_NKM_MARK(void)
static inline s32 AI_SET_NKM_MARK(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  if (IntPara)
  {
    wk->status5 |= 0x20u;
    return 1;
  }
  else
  {
    wk->status5 &= ~0x20u;
    return 1;
  }
}

// 0x210c930: s32 AI_BS_SPECIAL(void)
static inline s32 AI_BS_SPECIAL(void) {
  s32 IntPara;
  s32 v2;
  s32 v3;
  SBTLUNIT_WORK *v4;
  SBTLUNIT_WORK *UserData;
  SBTLUNIT_WORK *NakamaData;
  s32 *v7;
  SBTLUNIT_WORK *v10;
  SBTLACTION_WORK *v11;
  int32x4_t *v12;
  SBTLUNIT_WORK *v13;
  SBTLACTION_WORK *v14;
  f32 v18;
  f32 v19;
  f32 v20;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v25;
  s32 ListID;
  s32 v32;
  s64 v34;
  s32 *stock_id;
  SBATTLE_WORK *v36;
  f32 v38;
  f32 v40;
  f32 v41;
  long f64 v42;
  s32 v44;
  SBATTLE_WORK *v45;
  u32 *v46;
  s32 v47;
  SBTLAI_WORK *v48;
  u32 v49;
  s32 v50;
  s32 v51;
  s32 scrStep2;
  u32 color;
  s32 v57;
  SBTLAI_WORK *v58;
  S_CameraMoveDt *g_CamMov_BS_LASTB3_1_local;
  SBATTLE_WORK *v64;
  SBTLUNIT_LISTWORK *v65;
  s32 v66;
  SBTLUNIT_WORK *v67;
  SBATTLE_WORK *v69;
  SBTLUNIT_LISTWORK *v70;
  s32 v71;
  SBTLUNIT_WORK *v72;
  SBATTLE_WORK *v76;
  SBTLUNIT_LISTWORK *v77;
  s32 v78;
  SBTLUNIT_WORK *v79;
  SBATTLE_WORK *v83;
  SBTLUNIT_LISTWORK *v84;
  s32 v85;
  SBTLUNIT_WORK *v86;
  long f64 v87;
  long f64 v88;
  long f64 v89;
  f32 v90;
  f32 v91;
  f32 v92;
  f32 v93;
  long f64 v94;
  long f64 v95;
  long f64 v96;
  f32 v97;
  f32 v98;
  f32 v99;
  f32 v100;
  SBATTLE_WORK *v102;
  SBATTLE_WORK *v108;
  SBTLUNIT_LISTWORK *v109;
  s32 v110;
  sdatUnitWork_t *v111;
  SBATTLE_WORK *v114;
  SBTLUNIT_LISTWORK *v115;
  s32 v116;
  SBATTLE_WORK *v120;
  SBTLUNIT_LISTWORK *v121;
  s32 v122;
  SBTLUNIT_WORK *v123;
  SBTLDMG_HITLISTWORK *hitList;
  SBTLEFF_LISTWORK *effList;
  SBTLACTION_WORK *actwk;
  SBATTLE_WORK *v129;
  SBTLUNIT_LISTWORK *v130;
  s32 v131;
  Il2CppClass *klass;
  void (*methodPtr)(void);
  u32 v137;
  void *Instance;
  bool v139;
  Il2CppObject *v140;
  u32 v144;
  SBATTLE_WORK *v145;
  SBTLUNIT_LISTWORK *v146;
  s32 v147;
  SBTLUNIT_WORK *v148;
  SBTLUNIT_LISTWORK *v157;
  SBTLUNIT_WORK *v161;
  f32 x;
  f32 z;
  f32 v164;
  f32 v165;
  f32 PosToDir;
  f32 Dir180;
  f32 RotToDir;
  f32 v169;
  f32 Dir_Hokan;
  long f64 v171;
  long f64 v172;
  bool IsAction;
  f32 v180;
  f32 v182;
  long f64 v183;
  long f64 v184;
  __n128 v185;
  sdfVector4_t *p_ppos;
  SBTLEFF_LISTWORK *v188;
  SBTLEFF_LISTWORK *v190;
  SBTLUNIT_WORK *scrUnitList;
  SBTLUNIT_WORK *v193;
  SBTLUNIT_WORK *v194;
  long f64 v195;
  long f64 v196;
  long f64 v197;
  f32 v198;
  f32 v199;
  f32 v200;
  f32 v201;
  long f64 v202;
  long f64 v203;
  f32 v204;
  f32 v205;
  SBTLAI_WORK *v206;
  f32 v207;
  s64 v208;
  f32 v209;
  f32 v210;
  SBTLAI_WORK *v211;
  u32 v212;
  s64 v213;
  u32 v214;
  s64 v215;
  SBTLUNIT_WORK *v217;
  SBTLUNIT_WORK *v218;
  SBTLUNIT_WORK *v219;
  f32 v220;
  f32 v221;
  f32 v222;
  f32 v223;
  long f64 v224;
  long f64 v225;
  SBTLACTAI_WORK *v226;
  sdfVector4_t *p_scrPos2;
  sdfVector4_t *p_scrRot2;
  SBTLACTAI_WORK *v229;
  f32 v230;
  s64 v231;
  SBTLACTAI_WORK *v232;
  f32 v233;
  s64 v234;
  s64 v235;
  SBTLUNIT_LISTWORK *v237;
  SBTLUNIT_WORK *pUnit;
  bool v239;
  s32 hstatus;
  s64 v241;
  SBTLUNIT_LISTWORK *v243;
  SBTLUNIT_WORK *v244;
  s32 devilid;
  SBTLUNIT_WORK *v247;
  s32 v248;
  u32 v249;
  s32 v250;
  f32 v252;
  f32 v253;
  f32 *v254;
  f32 v255;
  f32 v256;
  long f64 v257;
  f32 v258;
  f32 v259;
  f32 v260;
  f32 v261;
  long f64 v262;
  long f64 v263;
  f32 v264;
  long f64 v265;
  f32 m_rate;
  s64 v267;
  s32 v268;
  u32 v269;
  struct sdfVector4_t v271;
  f32 *v272;
  f32 v273;
  f32 v274;
  f32 v275;
  f32 v277;
  s64 v279;
  __int128 v281;
  s32 *para;
  s64 i;
  SBTLUNIT_LISTWORK *v285;
  SBTLUNIT_WORK *v286;
  u32 v287;
  s64 v288;
  bool v289;
  SBATTLE_WORK *v291;
  SBTLEFF_LISTWORK *v292;
  f32 v294;
  f32 v295;
  f32 v296;
  f32 v297;
  long f64 v298;
  s64 v299;
  long f64 v300;
  f32 v301;
  long f64 v302;
  s64 v303;
  SBTLUNIT_LISTWORK *v305;
  SBTLUNIT_WORK *v306;
  f32 v307;
  f32 v308;
  f32 v309;
  f32 v310;
  f32 v311;
  f32 v312;
  u32 v314;
  SBTLACTAI_WORK *v316;
  SBTLUNIT_WORK *v318;
  u32 v319;
  SBATTLE_WORK *v322;
  s32 v323;
  SBTLEFF_LISTWORK *v324;
  bool v325;
  SBTLEFF_LISTWORK *v326;
  bool v327;
  SBTLEFF_LISTWORK *v329;
  SBATTLE_WORK *v331;
  SBTLUNIT_LISTWORK *v332;
  s32 boss_eventID;
  int32x4_t *v334;
  int32x2_t v335;
  long f64 v336;
  dds3ModelHandle_t *v337;
  SBATTLE_WORK *v339;
  SBTLUNIT_LISTWORK *v340;
  s32 v341;
  SBTLUNIT_WORK *v342;
  S_CameraMoveDt *CamMovePtn;
  u32 v344;
  s32 v346;
  s32 v347;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v349;
  SBTLUNIT_WORK *v350;
  SBATTLE_WORK *v353;
  SBATTLE_WORK *v355;
  u32 *p_stock_mask;
  s32 v357;
  sdatUnitWork_t *v359;
  SBATTLE_WORK *v361;
  SBTLUNIT_LISTWORK *v362;
  s32 v363;
  SBTLUNIT_WORK *v364;
  SBTLUNIT_WORK *v365;
  SBTLUNIT_WORK *v366;
  SBTLUNIT_WORK *v368;
  s32 v369;
  u32 v374;
  s32 v376;
  SBTLUNIT_WORK *v377;
  s32 v378;
  s32 v380;
  s32 v382;
  s32 v383;
  s64 k;
  SBTLUNIT_LISTWORK *v386;
  SBTLUNIT_WORK *v387;
  SBATTLE_WORK *v389;
  SBTLUNIT_LISTWORK *v390;
  s32 v391;
  SBTLUNIT_WORK *v392;
  s32 v394;
  f32 v396;
  f32 v397;
  f32 v398;
  f32 v399;
  f32 v400;
  f32 v401;
  f32 v402;
  f32 v403;
  f32 v404;
  long f64 v405;
  long f64 v406;
  SBATTLE_WORK *v410;
  SBTLUNIT_LISTWORK *v411;
  s32 v412;
  SBTLUNIT_WORK *v413;
  SBATTLE_WORK *v415;
  SBTLUNIT_LISTWORK *v416;
  s32 v417;
  SBTLUNIT_WORK *v418;
  s32 v420;
  SBATTLE_WORK *v422;
  s32 v423;
  SBTLUNIT_WORK *UnitFromDevilID;
  f32 v425;
  f32 v426;
  f32 v427;
  f32 v428;
  f32 v429;
  f32 v430;
  f32 v431;
  f32 v432;
  f32 v433;
  long f64 v434;
  long f64 v435;
  SBATTLE_WORK *v439;
  SBTLUNIT_LISTWORK *v440;
  s32 v441;
  s32 v442;
  SBATTLE_WORK *v444;
  SBTLUNIT_LISTWORK *v445;
  s32 v446;
  s32 v447;
  SBATTLE_WORK *v449;
  s32 v450;
  SBTLUNIT_WORK *v451;
  f32 v452;
  f32 v453;
  f32 v454;
  f32 v455;
  f32 v456;
  f32 v457;
  f32 v458;
  f32 v459;
  f32 v460;
  long f64 v461;
  long f64 v462;
  SBATTLE_WORK *v464;
  SBTLUNIT_LISTWORK *v465;
  s32 v466;
  SBTLUNIT_WORK *v467;
  s32 scrCmpCnt;
  SBTLAI_WORK *aiwk;
  u32 scrflag;
  f32 v472;
  f32 y;
  f32 w;
  f32 v475;
  long f64 v476;
  s32 scrListID;
  f32 v478;
  dds3ModelHandle_t *hModel;
  s64 j;
  SBTLUNIT_LISTWORK *v481;
  SBTLUNIT_WORK *v482;
  u32 v483;
  s64 v484;
  bool v485;
  s32 v492;
  s64 v493;
  SBTLUNIT_LISTWORK *v495;
  SBTLUNIT_WORK *v496;
  u32 status;
  f32 v498;
  f32 v500;
  struct sdfVector4_t v502;
  f32 *v503;
  f32 v504;
  f32 v505;
  f32 v506;
  s32 v508;
  s16 v509;
  DEVILDATA_WORK *DevilData;
  s32 aishou;
  SBTLAISYO_DATAWORK *Aisyotbl;
  long f64 v515;
  f32 v516;
  f32 v517;
  f32 v518;
  s32 v519;
  SBTLUNIT_WORK *v522;
  SBTLUNIT_WORK *v525;
  f32 v526;
  f32 v527;
  f32 v528;
  f32 v529;
  long f64 v530;
  s64 v531;
  long f64 v532;
  f32 v533;
  long f64 v534;
  SBATTLE_WORK *v536;
  SBTLEFF_LISTWORK *v537;
  f32 *v539;
  f32 v540;
  f32 v541;
  f32 v542;
  f32 v543;
  long f64 v545;
  SBATTLE_WORK *v546;
  s32 *scrCnt;
  SBTLACTAI_WORK *v548;
  f32 v549;
  f32 v551;
  f32 v552;
  u32 v553;
  f32 v554;
  s64 v555;
  long f64 v556;
  f32 v557;
  u32 v558;
  SBATTLE_WORK *v562;
  s32 scrLoadStat;
  SBTLEFF_LISTWORK *v564;
  SBTLEFF_LISTWORK *v567;
  SBATTLE_WORK *v568;
  s32 v569;
  u64 v570;
  s32 v571;
  s32 v572;
  s32 v573;
  s32 v575;
  f32 v576;
  f32 v577;
  f32 v578;
  f32 v579;
  f32 v580;
  f32 v581;
  f32 v582;
  f32 v583;
  f32 v584;
  long f64 v585;
  long f64 v586;
  s32 v590;
  SBTLUNIT_WORK *v591;
  f32 v592;
  f32 v593;
  f32 v594;
  f32 v595;
  f32 v596;
  f32 v597;
  f32 v598;
  long f64 v599;
  long f64 v600;
  SBTLUNIT_WORK *v605;
  SBATTLE_WORK *v607;
  u32 v608;
  SBTLEFF_LISTWORK *v609;
  f32 v611;
  f32 v612;
  SBATTLE_WORK *v613;
  SBTLEFF_LISTWORK *v614;
  bool v615;
  SBTLEFF_LISTWORK *v616;
  bool v617;
  SBTLEFF_LISTWORK *v619;
  SBATTLE_WORK *v621;
  SBTLEFF_LISTWORK *v622;
  s32 motionno;
  SBTLUNIT_LISTWORK *v625;
  s32 v628;
  f32 v629;
  f32 v630;
  f32 v631;
  f32 v632;
  f32 v633;
  f32 v634;
  f32 v635;
  f32 v636;
  f32 v637;
  long f64 v638;
  long f64 v639;
  f32 AtoB_LR_ABS;
  f32 v642;
  f32 v643;
  f32 v644;
  f32 v645;
  f32 v646;
  long f64 v647;
  SBTLACTAI_WORK *v648;
  f32 v649;
  f32 v650;
  f32 v651;
  f32 v652;
  long f64 v653;
  SBTLACTAI_WORK *v654;
  SBTLACTAI_WORK *v656;
  f32 *v657;
  f32 v658;
  f32 v659;
  f32 v660;
  f32 v661;
  s32 v662;
  f32 v663;
  f32 v664;
  f32 v665;
  f32 v666;
  SBTLUNIT_WORK *v672;
  s32 v673;
  f32 BS14_CSHO_R_SIZE_local;
  f32 v675;
  f32 v676;
  f32 v677;
  f32 v678;
  f32 v679;
  s32 v680;
  f32 v681;
  f32 v682;
  f32 v683;
  f32 v684;
  f32 v685;
  SBTLUNIT_WORK *v686;
  f32 priv_area_r;
  f32 v688;
  f32 v689;
  f32 v690;
  f32 v691;
  long f64 v692;
  long f64 v693;
  f32 v694;
  f32 v695;
  f32 v696;
  f32 v697;
  long f64 v698;
  s64 v699;
  long f64 v700;
  long f64 v701;
  long f64 v702;
  long f64 v703;
  SBTLUNIT_WORK *v704;
  SBTLUNIT_WORK *v705;
  s32 v706;
  struct sdfVector4_t v708;
  f32 *v709;
  f32 v710;
  f32 v711;
  f32 v712;
  f32 v714;
  u32 v716;
  f32 v717;
  f32 v718;
  f32 v719;
  f32 v720;
  f32 v721;
  bool v722;
  f32 v724;
  f32 v725;
  SBTLUNIT_WORK *v726;
  f32 v727;
  s32 v728;
  s32 v729;
  _BOOL4 v730;
  bool v731;
  struct sdfVector4_t v733;
  f32 *p_x;
  f32 v735;
  f32 v736;
  f32 v737;
  f32 v739;
  u32 v741;
  f32 v742;
  f32 v743;
  f32 v744;
  f32 v745;
  f32 v746;
  bool v747;
  f32 v749;
  f32 v750;
  f32 v751;
  f32 v752;
  f32 v753;
  f32 scrAngle;
  f32 v755;
  long f64 v756;
  long f64 v757;
  long f64 v758;
  long f64 v759;
  f32 v760;
  f32 v761;
  f32 v762;
  f32 v763;
  long f64 v764;
  s64 v765;
  long f64 v766;
  long f64 v767;
  long f64 v768;
  f32 v769;
  f32 v771;
  s32 v772;
  f32 v774;
  u32 v775;
  f32 v776;
  s64 v777;
  long f64 v778;
  f32 v779;
  SBTLEFF_LISTWORK *v781;
  long f64 v783;
  long f64 v784;
  long f64 v785;
  long f64 v786;
  long f64 v787;
  f32 *actaiwk;
  f32 v789;
  f32 v790;
  f32 v791;
  f32 v792;
  long f64 v794;
  long f64 v795;
  sdfVector4_t *p_rot;
  long f64 v797;
  f32 v798;
  f32 v799;
  f32 v800;
  SBATTLE_WORK *v802;
  SBATTLE_WORK *v804;
  bool v805;
  SBTLEFF_LISTWORK *v806;
  f32 v808;
  f32 v809;
  f32 v810;
  f32 v811;
  f32 v812;
  f32 v813;
  f32 v814;
  f32 v815;
  f32 v816;
  long f64 v817;
  long f64 v818;
  f32 v819;
  f32 v820;
  s64 v821;
  long f64 v822;
  f32 v823;
  f32 v824;
  s64 v825;
  long f64 v826;
  long f64 v827;
  long f64 v828;
  SBTLEFF_LISTWORK *v830;
  s32 v831;
  SBATTLE_WORK *v834;
  s32 v835;
  SBATTLE_WORK *v838;
  f32 v839;
  f32 v840;
  f32 v841;
  f32 v842;
  long f64 v843;
  s32 v844;
  f32 v845;
  s32 v847;
  f32 v848;
  f32 v849;
  f32 v850;
  f32 v851;
  f32 v852;
  f32 v853;
  f32 v854;
  f32 v855;
  f32 v856;
  long f64 v857;
  long f64 v858;
  SBTLEFF_LISTWORK *v860;
  SBTLEFF_LISTWORK *v862;
  SBTLEFF_LISTWORK *v864;
  SBTLEFF_LISTWORK *v866;
  s32 v868;
  SBATTLE_WORK *v872;
  u32 status2;
  u32 v874;
  SBTLEFF_LISTWORK *v875;
  u32 v877;
  SBTLEFF_LISTWORK *v878;
  SBTLEFF_LISTWORK *v880;
  f32 v882;
  f32 v883;
  f32 v884;
  f32 v885;
  long f64 v886;
  f32 v887;
  f32 v888;
  f32 v889;
  f32 v890;
  f32 v891;
  f32 v892;
  f32 v893;
  f32 v894;
  s64 v895;
  SBTLUNIT_LISTWORK *v896;
  SBTLUNIT_WORK *v897;
  u32 v898;
  SBTLEFF_LISTWORK *v899;
  SBTLEFF_LISTWORK *v902;
  SBTLEFF_LISTWORK *v904;
  SBTLEFF_LISTWORK *v906;
  SBTLEFF_LISTWORK *v908;
  SBTLEFF_LISTWORK *v910;
  SBTLEFF_LISTWORK *v912;
  SBTLEFF_LISTWORK *v914;
  SBTLEFF_LISTWORK *v916;
  SBTLEFF_LISTWORK *v919;
  SBTLEFF_LISTWORK *v921;
  SBTLEFF_LISTWORK *v923;
  SBTLEFF_LISTWORK *v925;
  SBTLEFF_LISTWORK *v927;
  s32 v928;
  s32 v932;
  u32 v933;
  SBTLEFF_LISTWORK *v935;
  SBTLEFF_LISTWORK *v938;
  long f64 v941;
  long f64 v942;
  f32 *v943;
  f32 v944;
  f32 v945;
  f32 v946;
  f32 v947;
  SBTLEFF_LISTWORK *v950;
  SBTLEFF_LISTWORK *v952;
  SBTLEFF_LISTWORK *v954;
  SBTLEFF_LISTWORK *v956;
  SBTLEFF_LISTWORK *v958;
  s32 v959;
  SBTLEFF_LISTWORK *v961;
  SBTLEFF_LISTWORK *v963;
  SBTLEFF_LISTWORK *v965;
  SBTLEFF_LISTWORK *v967;
  SBTLEFF_LISTWORK *v969;
  SBTLEFF_LISTWORK *v971;
  SBTLEFF_LISTWORK *v973;
  SBTLEFF_LISTWORK *v975;
  SBATTLE_WORK *v976;
  SBTLEFF_LISTWORK *v977;
  bool v978;
  SBTLEFF_LISTWORK *v979;
  bool v980;
  SBTLEFF_LISTWORK *v982;
  SBATTLE_WORK *v983;
  SBTLEFF_LISTWORK *v984;
  bool v985;
  SBTLEFF_LISTWORK *v986;
  bool v987;
  SBTLEFF_LISTWORK *v989;
  SBATTLE_WORK *v990;
  SBTLEFF_LISTWORK *v991;
  bool v992;
  SBTLEFF_LISTWORK *v993;
  bool v994;
  SBTLEFF_LISTWORK *v996;
  SBATTLE_WORK *v997;
  SBTLEFF_LISTWORK *v998;
  bool v999;
  SBTLEFF_LISTWORK *v1000;
  bool v1001;
  SBTLEFF_LISTWORK *v1003;
  SBATTLE_WORK *v1004;
  SBTLEFF_LISTWORK *v1005;
  bool v1006;
  SBTLEFF_LISTWORK *v1007;
  bool v1008;
  SBTLEFF_LISTWORK *v1010;
  SBATTLE_WORK *v1011;
  SBTLEFF_LISTWORK *v1012;
  bool v1013;
  SBTLEFF_LISTWORK *v1014;
  bool v1015;
  SBTLEFF_LISTWORK *v1017;
  SBATTLE_WORK *v1018;
  SBTLEFF_LISTWORK *v1019;
  bool v1020;
  SBTLEFF_LISTWORK *v1021;
  bool v1022;
  SBTLEFF_LISTWORK *v1024;
  SBATTLE_WORK *v1025;
  SBTLEFF_LISTWORK *v1026;
  bool v1027;
  SBTLEFF_LISTWORK *v1028;
  bool v1029;
  s32 v1031;
  SBTLEFF_LISTWORK *v1033;
  SBTLEFF_LISTWORK *v1035;
  SBTLEFF_LISTWORK *v1037;
  SBTLEFF_LISTWORK *v1039;
  sdfVector4_t v1041;
  u32 v1044;
  sdfVector4_t v1045;
  sdfVector4_t v1048;
  sdfVector4_t v1051;
  s32 data;
  s64 v1055;
  s64 v1056;
  s64 v1057;
  s64 v1058;
  sdfVector4_t v1059;
  s64 v1060;
  s64 v1061;
  s64 v1062;
  s64 v1063;
  sdfVector4_t rot;
  sdfVector4_t v1065;
  sdfVector4_t pos;
  sdfVector4_t v1067;
  sdfVector4_t v1068;
  sdfVector4_t v1069;
  sdfVector4_t v1070;
  sdfVector4_t v1071;
  sdfVector4_t v1072;
  sdfVector4_t v1073;
  sdfVector4_t v1074;
  sdfVector4_t v1075;

  v1055 = 0;
  v1056 = 0;
  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  v3 = scrGetIntPara(2);
  v4 = GetData();
  UserData = Support_GetUserData();
  NakamaData = Support_GetNakamaData(0);
  *(u64 *)&pos.x = 0;
  *(u64 *)&pos.z = 0;
  *(u64 *)&v1065.x = 0;
  *(u64 *)&v1065.z = 0;
  *(u64 *)&rot.x = 0;
  *(u64 *)&rot.z = 0;
  v1062 = 0;
  v1063 = 0;
  v1060 = 0;
  v1061 = 0;
  *(u64 *)&v1059.x = 0;
  *(u64 *)&v1059.z = 0;
  v1057 = 0;
  v1058 = 0;
  v7 = NewSpecific(s32, 0x20u);
  if (IntPara <= 40000)
  {
    if (IntPara > 10030)
    {
      if ((u32)IntPara <= 0x7530)
      {
        if (IntPara == 10040)
        {
          wk->BtlEnd_BossFedeOut = 1;
          goto LABEL_323;
        }
        if (IntPara != 20000)
        {
          if (IntPara == 30000)
          {
            wk->sprit_waza = 4000;
            goto LABEL_323;
          }
          goto LABEL_320;
        }
LABEL_323:
        LODWORD(v12) = 1;
        return (s32)v12;
      }
      switch (IntPara)
      {
        case 32000:
          if (v2)
            goto LABEL_1225;
          SetAction(3);
          wk->enemy_zenmetu = 0;
          goto LABEL_323;
        case 32001:
          T_OkikumuMotion(v2);
          goto LABEL_323;
        case 32002:
          UnitOnOff(v2, v3);
          goto LABEL_323;
        case 32003:
          RaidouMotion(v2);
          goto LABEL_323;
        case 32004:
          if (!NakamaRot(v2, v3))
            goto LABEL_293;
          goto LABEL_323;
        case 32005:
          klass = _get_Instance()->klass;
          if (v3 == 1)
            methodPtr = klass->vtable[6].methodPtr;
          else
            methodPtr = klass->vtable[7].methodPtr;
          methodPtr();
          goto LABEL_323;
        case 32006:
          LoadEff();
          goto LABEL_323;
        case 32007:
          InstanceEff();
          goto LABEL_323;
        case 32008:
          DestroyEff();
          goto LABEL_323;
        case 32009:
          dds3FadeIn2(0x1Eu);
          goto LABEL_323;
        default:
          if (IntPara == 31000)
          {
            v4->actwk->action_flg = 0;
            goto LABEL_323;
          }
          if (IntPara != 40000)
            goto LABEL_320;
          scrStep2 = sBtlBS_LASTB1_Action_DangCheck(v4);
          break;
      }
LABEL_128:
LABEL_130:
      v51 = scrStep2;
      goto LABEL_131;
    }
    if (IntPara > 2000)
    {
      switch (IntPara)
      {
        case 10000:
          if (v2 != 1)
          {
            if (v2)
            {
              if (v2 == -1)
              {
                UnitMng = wk->UnitMng;
                playerID = wk->playerID;
                v25 = sBtlSearchUnit_ID(UnitMng, playerID);
                sBtlSearchUnit_ID(wk->UnitMng, v25->actaiwk->targetID);
                ListID = v4->ListID;
                gBossTalk_Target_ListID = ListID;
                sBtlSetBossTalkTarget(v4);
                wk->AttackBtn_NgTime = 3;
                gBossTalk_GetReady_TimeOutCnt = 0;
              }
            }
            else
            {
              gBossTalk_GetReady_TimeOutCnt = 0;
              if (wk->battlemode == 1)
              {
                gBossTalk_GetReady_Step = 0;
                sBtlSetMotion(v4, 0, 0, 0, 0);
              }
              else
              {
                gBossTalk_GetReady_Step = 0;
                gBossTalk_GetReady_TheWorld_Bk = 0;
                v464 = wk;
                v465 = v464->UnitMng;
                v466 = v464->playerID;
                v467 = sBtlSearchUnit_ID(v465, v466);
                wk->status4 |= 0x800000u;
                if ((v467->status & 0x10) != 0)
                {
                  gBossTalk_GetReady_TheWorld_Bk = 1;
                }
                else
                {
                  sBtlStatusBitOn(v467, 0x10u);
                }
                if ((u32)(wk->encountno - 61) <= 0xFFFFFFFD && !v3)
                  SetAction(21);
                sBtlResetCharge(v467, 0);
LABEL_1020:
                wk->AttackBtn_NgTime = 3;
              }
            }
            goto LABEL_323;
          }
          if (wk->battlemode == 1)
            goto LABEL_323;
          ++gBossTalk_GetReady_TimeOutCnt;
          v145 = wk;
          if ((u32)(v145->encountno - 59) < 2)
            v3 = 1;
          if (!v144)
          {
            v145 = wk;
          }
          v146 = v145->UnitMng;
          v147 = v145->playerID;
          v148 = sBtlSearchUnit_ID(v146, v147);
          if (gBossTalk_GetReady_Step != 2)
          {
            if (gBossTalk_GetReady_Step != 1)
            {
              if (gBossTalk_GetReady_Step)
                goto LABEL_323;
              sBtlStatusBitOn(v148, 0x10u);
              if (sBtlJumpProc_Eve())
              {
                if (gBossTalk_GetReady_TimeOutCnt < gBossTalk_GetReady_TimeOutMax)
                  goto LABEL_293;
              }
              if (wk->mode != 1)
              {
                if (gBossTalk_GetReady_TimeOutCnt < gBossTalk_GetReady_TimeOutMax)
                  goto LABEL_293;
              }
              if (gBossTalk_Target_ListID == -1)
              {
LABEL_366:
                if (wk->mode == 1 && (v148->side & 0x80) != 0 && v148->motionno == 104)
                {
                  sBtlSetMotion(v148, 0, 0, 0, 0);
                }
                x = v148->pos.x;
                z = v148->pos.z;
                v164 = v4->pos.x;
                v165 = v4->pos.z;
                PosToDir = sBtlGetPosToDir(x, z, v164, v165);
                Dir180 = sBtlGetDir180(PosToDir);
                RotToDir = sBtlGetRotToDir(v148->rot);
                v169 = sBtlGetDir180(RotToDir);
                Dir_Hokan = sBtlGetDir_Hokan(v169, Dir180, 15.0);
                v148->mv_rotbk = Dir_Hokan;
                FromEuler(0.0, Dir_Hokan * 0.017453292, 0.0);
                *(__n128 *)&v172 = sub_1B335A0(&v148->rot, 0, v171);
                sub_1B335A0(&v148->rotbk, 0, v172);
                v148->front_deg = sBtlGetDir180(Dir_Hokan);
                if (v3)
                {
                  goto LABEL_380;
                }
                else
                {
                  v848 = v4->pos.x;
                  v849 = v4->pos.z;
                  v850 = v148->pos.x;
                  v851 = v148->pos.z;
                  v852 = sBtlGetPosToDir(v848, v849, v850, v851);
                  v853 = sBtlGetDir180(v852);
                  v854 = sBtlGetRotToDir(v4->rot);
                  v855 = sBtlGetDir180(v854);
                  v856 = sBtlGetDir_Hokan(v855, v853, 5.0);
                  v4->mv_rotbk = v856;
                  FromEuler(0.0, v856 * 0.017453292, 0.0);
                  *(__n128 *)&v858 = sub_1B335A0(&v4->rot, 0, v857);
                  sub_1B335A0(&v4->rotbk, 0, v858);
LABEL_380:
                  if ((u32)(wk->encountno - 61) < 0xFFFFFFFE)
                  {
LABEL_381:
                    IsAction = IsAction(21);
                    if (IsAction)
                    {
                      if (gBossTalk_GetReady_TimeOutCnt < gBossTalk_GetReady_TimeOutMax)
                        goto LABEL_293;
                    }
LABEL_1573:
LABEL_1575:
                    LODWORD(v12) = 0;
                    gBossTalk_GetReady_Step = 1;
                    return (s32)v12;
                  }
LABEL_1572:
                  goto LABEL_1573;
                }
                if ((u32)(wk->encountno - 61) < 0xFFFFFFFE)
                  goto LABEL_381;
                goto LABEL_1572;
              }
              v157 = wk->UnitMng;
              v161 = sBtlSearchUnit_ID(v157, gBossTalk_Target_ListID);
              v4 = v161;
              goto LABEL_366;
            }
            if (gBossTalk_Target_ListID == -1)
            {
LABEL_1209:
              v629 = v148->pos.x;
              v630 = v148->pos.z;
              v631 = v4->pos.x;
              v632 = v4->pos.z;
              v633 = sBtlGetPosToDir(v629, v630, v631, v632);
              v634 = sBtlGetDir180(v633);
              v635 = sBtlGetRotToDir(v148->rot);
              v636 = sBtlGetDir180(v635);
              v637 = sBtlGetDir_Hokan(v636, v634, 15.0);
              v148->mv_rotbk = v637;
              FromEuler(0.0, v637 * 0.017453292, 0.0);
              *(__n128 *)&v639 = sub_1B335A0(&v148->rot, 0, v638);
              sub_1B335A0(&v148->rotbk, 0, v639);
              v148->front_deg = sBtlGetDir180(v637);
              if (v3)
              {
                AtoB_LR_ABS = sBtlGetAtoB_LR_ABS(v637, v634);
                v642 = 1.0;
              }
              else
              {
                v808 = v4->pos.x;
                v809 = v4->pos.z;
                v810 = v148->pos.x;
                v811 = v148->pos.z;
                v812 = sBtlGetPosToDir(v808, v809, v810, v811);
                v813 = sBtlGetDir180(v812);
                v814 = sBtlGetRotToDir(v4->rot);
                v815 = sBtlGetDir180(v814);
                v816 = sBtlGetDir_Hokan(v815, v813, 5.0);
                v4->mv_rotbk = v816;
                FromEuler(0.0, v816 * 0.017453292, 0.0);
                *(__n128 *)&v818 = sub_1B335A0(&v4->rot, 0, v817);
                sub_1B335A0(&v4->rotbk, 0, v818);
                v819 = sBtlGetAtoB_LR_ABS(v637, v634);
                AtoB_LR_ABS = sBtlGetAtoB_LR_ABS(v816, v813);
                v642 = 1.0;
                if (v819 >= 1.0)
                  goto LABEL_1492;
              }
              if (AtoB_LR_ABS < v642)
              {
                gBossTalk_GetReady_Step = 2;
              }
LABEL_1492:
              if (gBossTalk_GetReady_TimeOutCnt < gBossTalk_GetReady_TimeOutMax)
                goto LABEL_293;
LABEL_1139:
              LODWORD(v12) = 0;
              gBossTalk_GetReady_Step = 2;
              return (s32)v12;
            }
            v625 = wk->UnitMng;
            v628 = gBossTalk_Target_ListID;
            v4 = sBtlSearchUnit_ID(v625, v628);
            goto LABEL_1209;
          }
          motionno = v148->motionno;
          if (motionno <= 112)
          {
            if (motionno != 57 && motionno != 112)
              goto LABEL_1465;
          }
          else if (motionno != 118 && motionno != 115)
          {
            goto LABEL_1465;
          }
          v805 = sBtlCheckMotionEnd(v148);
          if (!v805)
          {
            if (gBossTalk_GetReady_TimeOutCnt < gBossTalk_GetReady_TimeOutMax)
              goto LABEL_293;
          }
LABEL_1465:
          if (gBossTalk_GetReady_TheWorld_Bk)
          {
            goto LABEL_1468;
          }
          sBtlStatusBitOff(v148, 0xFFFFFFEF);
LABEL_1468:
          gBossTalk_Target_ListID = -1;
LABEL_1469:
          wk->status4 &= ~0x800000u;
          goto LABEL_323;
        case 10001:
          switch (v2)
          {
            case 0:
              gBossTalk_GetReady_Step = 0;
              gBossTalk_GetReady_TheWorld_Bk = 0;
              v120 = wk;
              v121 = v120->UnitMng;
              v122 = v120->playerID;
              v123 = sBtlSearchUnit_ID(v121, v122);
              wk->status4 |= 0x800000u;
              if ((v123->status & 0x10) != 0)
              {
                gBossTalk_GetReady_TheWorld_Bk = 1;
              }
              else
              {
                sBtlStatusBitOn(v123, 0x10u);
              }
              sBtlSetBossTalkTarget(v4);
              SetAction(7);
              sBtlResetCharge(v123, 0);
              goto LABEL_1020;
            case 1:
              v389 = wk;
              v390 = v389->UnitMng;
              v391 = v389->playerID;
              v392 = sBtlSearchUnit_ID(v390, v391);
              v394 = gBossTalk_GetReady_Step;
              if (v394 != 2)
              {
                if (v394 == 1)
                {
                  v576 = v392->pos.x;
                  v577 = v392->pos.z;
                  v578 = v4->pos.x;
                  v579 = v4->pos.z;
                  v580 = sBtlGetPosToDir(v576, v577, v578, v579);
                  v581 = sBtlGetDir180(v580);
                  v582 = sBtlGetRotToDir(v392->rot);
                  v583 = sBtlGetDir180(v582);
                  v584 = sBtlGetDir_Hokan(v583, v581, 15.0);
                  v392->mv_rotbk = v584;
                  FromEuler(0.0, v584 * 0.017453292, 0.0);
                  *(__n128 *)&v586 = sub_1B335A0(&v392->rot, 0, v585);
                  sub_1B335A0(&v392->rotbk, 0, v586);
                  v392->front_deg = sBtlGetDir180(v584);
                  goto LABEL_1135;
                }
                if (v394)
                  goto LABEL_323;
                sBtlStatusBitOn(v392, 0x10u);
                if (sBtlJumpProc_Eve())
                  goto LABEL_293;
                if (wk->mode != 1)
                  goto LABEL_293;
                v396 = v392->pos.x;
                v397 = v392->pos.z;
                v398 = v4->pos.x;
                v399 = v4->pos.z;
                v400 = sBtlGetPosToDir(v396, v397, v398, v399);
                v401 = sBtlGetDir180(v400);
                v402 = sBtlGetRotToDir(v392->rot);
                v403 = sBtlGetDir180(v402);
                v404 = sBtlGetDir_Hokan(v403, v401, 15.0);
                v392->mv_rotbk = v404;
                FromEuler(0.0, v404 * 0.017453292, 0.0);
                *(__n128 *)&v406 = sub_1B335A0(&v392->rot, 0, v405);
                sub_1B335A0(&v392->rotbk, 0, v406);
                v392->front_deg = sBtlGetDir180(v404);
                if (!IsCamDone())
                  goto LABEL_293;
                goto LABEL_879;
              }
              v575 = v392->motionno;
              if (v575 <= 112)
              {
                if (v575 != 57 && v575 != 112)
                {
LABEL_1404:
                  if (!gBossTalk_GetReady_TheWorld_Bk)
                  {
                    v605 = v392;
                    goto LABEL_1410;
                  }
                  goto LABEL_1411;
                }
              }
              else if (v575 != 118 && v575 != 115)
              {
                goto LABEL_1404;
              }
              if (!sBtlCheckMotionEnd(v392))
                goto LABEL_293;
              goto LABEL_1404;
            case 2:
              gBossTalk_GetReady_Step = 0;
              gBossTalk_GetReady_TheWorld_Bk = 0;
              v410 = wk;
              v411 = v410->UnitMng;
              v412 = v410->playerID;
              v413 = sBtlSearchUnit_ID(v411, v412);
              wk->status4 |= 0x800000u;
              if ((v413->status & 0x10) != 0)
              {
                gBossTalk_GetReady_TheWorld_Bk = 1;
              }
              else
              {
                sBtlStatusBitOn(v413, 0x10u);
              }
              v442 = 9;
              goto LABEL_954;
            case 3:
              v415 = wk;
              v416 = v415->UnitMng;
              v417 = v415->playerID;
              v418 = sBtlSearchUnit_ID(v416, v417);
              v420 = gBossTalk_GetReady_Step;
              if (v420 == 2)
                goto LABEL_957;
              if (v420 == 1)
              {
                if (wk->encountno == 46)
                  v590 = 268;
                else
                  v590 = 305;
                goto LABEL_1129;
              }
              if (v420)
                goto LABEL_323;
              sBtlStatusBitOn(v418, 0x10u);
              if (sBtlJumpProc_Eve())
                goto LABEL_293;
              v422 = wk;
              if (v422->mode != 1)
                goto LABEL_293;
              v422 = wk;
              if (v422->encountno == 46)
                v423 = 268;
              else
                v423 = 305;
              UnitFromDevilID = sBtlGetUnitFromDevilID(v423);
              if (UnitFromDevilID)
              {
                v425 = v418->pos.x;
                v426 = v418->pos.z;
                v427 = UnitFromDevilID->pos.x;
                v428 = UnitFromDevilID->pos.z;
                v429 = sBtlGetPosToDir(v425, v426, v427, v428);
                v430 = sBtlGetDir180(v429);
                v431 = sBtlGetRotToDir(v418->rot);
                v432 = sBtlGetDir180(v431);
                v433 = sBtlGetDir_Hokan(v432, v430, 15.0);
                v418->mv_rotbk = v433;
                FromEuler(0.0, v433 * 0.017453292, 0.0);
                *(__n128 *)&v435 = sub_1B335A0(&v418->rot, 0, v434);
                sub_1B335A0(&v418->rotbk, 0, v435);
                v418->front_deg = sBtlGetDir180(v433);
              }
              if (IsAction(9))
                goto LABEL_293;
              goto LABEL_879;
            case 4:
              gBossTalk_GetReady_Step = 0;
              gBossTalk_GetReady_TheWorld_Bk = 0;
              v439 = wk;
              v440 = v439->UnitMng;
              v441 = v439->playerID;
              v413 = sBtlSearchUnit_ID(v440, v441);
              wk->status4 |= 0x800000u;
              if ((v413->status & 0x10) != 0)
              {
                v442 = 8;
                gBossTalk_GetReady_TheWorld_Bk = 1;
              }
              else
              {
                sBtlStatusBitOn(v413, 0x10u);
                v442 = 8;
              }
LABEL_954:
              SetAction(v442);
              sBtlResetCharge(v413, 0);
              goto LABEL_323;
            case 5:
              v444 = wk;
              v445 = v444->UnitMng;
              v446 = v444->playerID;
              v418 = sBtlSearchUnit_ID(v445, v446);
              v447 = gBossTalk_GetReady_Step;
              if (v447 != 2)
              {
                if (v447 == 1)
                {
                  if (wk->encountno == 46)
                    v590 = 269;
                  else
                    v590 = 304;
LABEL_1129:
                  v591 = sBtlGetUnitFromDevilID(v590);
                  if (!v591)
                    goto LABEL_1136;
                  v592 = v418->pos.x;
                  v593 = v418->pos.z;
                  v594 = v591->pos.x;
                  v595 = v591->pos.z;
                  v596 = sBtlGetPosToDir(v592, v593, v594, v595);
                  v581 = sBtlGetDir180(v596);
                  v597 = sBtlGetRotToDir(v418->rot);
                  v598 = sBtlGetDir180(v597);
                  v584 = sBtlGetDir_Hokan(v598, v581, 15.0);
                  v418->mv_rotbk = v584;
                  FromEuler(0.0, v584 * 0.017453292, 0.0);
                  *(__n128 *)&v600 = sub_1B335A0(&v418->rot, 0, v599);
                  sub_1B335A0(&v418->rotbk, 0, v600);
                  v418->front_deg = sBtlGetDir180(v584);
LABEL_1135:
                  if (sBtlGetAtoB_LR_ABS(v584, v581) < 1.0)
                  {
LABEL_1136:
                    goto LABEL_1139;
                  }
                  goto LABEL_293;
                }
                if (v447)
                  goto LABEL_323;
                sBtlStatusBitOn(v418, 0x10u);
                if (sBtlJumpProc_Eve())
                  goto LABEL_293;
                v449 = wk;
                if (v449->mode != 1)
                  goto LABEL_293;
                v449 = wk;
                if (v449->encountno == 46)
                  v450 = 269;
                else
                  v450 = 304;
                v451 = sBtlGetUnitFromDevilID(v450);
                if (v451)
                {
                  v452 = v418->pos.x;
                  v453 = v418->pos.z;
                  v454 = v451->pos.x;
                  v455 = v451->pos.z;
                  v456 = sBtlGetPosToDir(v452, v453, v454, v455);
                  v457 = sBtlGetDir180(v456);
                  v458 = sBtlGetRotToDir(v418->rot);
                  v459 = sBtlGetDir180(v458);
                  v460 = sBtlGetDir_Hokan(v459, v457, 15.0);
                  v418->mv_rotbk = v460;
                  FromEuler(0.0, v460 * 0.017453292, 0.0);
                  *(__n128 *)&v462 = sub_1B335A0(&v418->rot, 0, v461);
                  sub_1B335A0(&v418->rotbk, 0, v462);
                  v418->front_deg = sBtlGetDir180(v460);
                }
                if (IsAction(8))
                  goto LABEL_293;
LABEL_879:
                goto LABEL_1575;
              }
LABEL_957:
              v492 = v418->motionno;
              if (v492 <= 112)
              {
                if (v492 != 57 && v492 != 112)
                  goto LABEL_1153;
              }
              else if (v492 != 118 && v492 != 115)
              {
                goto LABEL_1153;
              }
              if (!sBtlCheckMotionEnd(v418))
                goto LABEL_293;
LABEL_1153:
              if (!gBossTalk_GetReady_TheWorld_Bk)
              {
                v605 = v418;
LABEL_1410:
                sBtlStatusBitOff(v605, 0xFFFFFFEF);
              }
LABEL_1411:
              goto LABEL_1469;
            default:
              goto LABEL_323;
          }
        case 10002:
          goto LABEL_323;
        case 10003:
          hitList = wk->hitList;
          sBtlClearHitC(hitList, v4);
          effList = wk->effList;
          sBtlForceReset(effList, v4);
          goto LABEL_323;
        case 10004:
          DeleteAll_BossDead();
          goto LABEL_323;
        case 10010:
          v4->aiwk->scrflag &= ~0x20000u;
          actwk = v4->actwk;
          if (actwk->status == 10 && actwk->action_flg == 1)
            actwk->action_flg = 0;
          goto LABEL_323;
        case 10011:
          dds3PostHitFlashStart(0x28u);
          sBtlEndSetsumaPadStop();
          sBtlSetEnemyLastDeadStop(1, 80, 0.05, 0.05);
          goto LABEL_323;
        case 10020:
          v129 = wk;
          v130 = v129->UnitMng;
          v131 = v129->playerID;
          sBtlSearchUnit_ID(v130, v131)->actaiwk->targetID = v4->ListID;
          goto LABEL_323;
        case 10030:
          wk->enemy_zenmetu = 1;
          goto LABEL_323;
        default:
          goto LABEL_320;
      }
    }
    switch (IntPara)
    {
      case 1:
        if (v2 == 1)
        {
          sBtlPlayBossAtrac3(v4);
          goto LABEL_323;
        }
        sBtlGetPointData(1, &pos, &rot);
        scrCmpCnt = wk->scrCmpCnt;
        aiwk = v4->aiwk;
        scrflag = aiwk->scrflag;
        if ((scrflag & 0x200) == 0)
        {
          aiwk->scrStep3 = 0;
          aiwk->scrflag = scrflag | 0x200;
          v472 = v4->pos.x;
          y = v4->pos.y;
          v475 = v4->pos.z;
          w = v4->pos.w;
          *(__n128 *)&v476 = sub_1B332C0(0, v472, y, v475, w);
          sub_1B335A0(&v4->actaiwk->scrPos, 0, v476);
          scrListID = v4->aiwk->scrListID;
          switch (scrListID)
          {
            case 1:
              v478 = 0.0;
              break;
            case 2:
              v478 = 4.1887903;
              break;
            case 3:
              v478 = 2.0943952;
              break;
            default:
              v478 = 0.0;
              break;
          }
          v4->actaiwk->scrAngle = v478;
          FromEuler(0.0, v478, 0.0);
          ToMatrix();
          sub_1B332C0(0, 0.0, 0.0, 1.0, 0.0);
          *(__n128 *)&v784 = sub_1B33480(0, 100.0);
          (loc_1EA2510)(0, v784);
          sub_1B33360(0, pos.x, pos.y, pos.z, pos.w);
          *(__n128 *)&v785 = sub_1B33520(0);
          sub_1B335A0(&v4->actaiwk->scrPos2, 0, v785);
          FromEuler(0.0, v478, 0.0);
          sub_1B335A0(&v4->actaiwk->scrRot2, 0, v786);
          *(__n128 *)&v787 = sub_1B332C0(0, v4->rot.x, v4->rot.y, v4->rot.z, v4->rot.w);
          sub_1B335A0(&v4->actaiwk->scrRot, 0, v787);
          v568 = wk;
          v569 = v568->scrCnt[0];
          if (v569 <= 150)
            goto LABEL_1428;
          goto LABEL_1097;
LABEL_1096:
          v568 = wk;
          v569 = v568->scrCnt[0];
          if (v569 <= 150)
          {
LABEL_1428:
            actaiwk = v4->actaiwk;
            v789 = actaiwk[33];
            v790 = actaiwk[34];
            v792 = actaiwk[35];
            v791 = actaiwk[36];
            sub_1B332C0(0, v789, v790, v792, v791);
            sub_1B33360(0, v4->actaiwk->scrPos.x, v4->actaiwk->scrPos.y, v4->actaiwk->scrPos.z, v4->actaiwk->scrPos.w);
            sub_1B33400(0);
            sub_1B33480(0, (f32)wk->scrCnt[0] / 150.0);
            sub_1B33360(0, v4->actaiwk->scrPos.x, v4->actaiwk->scrPos.y, v4->actaiwk->scrPos.z, v4->actaiwk->scrPos.w);
            *(__n128 *)&v794 = sub_1B33520(0);
            sub_1B335A0(&v4->pos, 0, v794);
            sub_1B332C0(0, v4->actaiwk->scrRot.x, v4->actaiwk->scrRot.y, v4->actaiwk->scrRot.z, v4->actaiwk->scrRot.w);
            sub_1B33360(0, v4->actaiwk->scrRot2.x, v4->actaiwk->scrRot2.y, v4->actaiwk->scrRot2.z, v4->actaiwk->scrRot2.w);
            Slerp((f32)wk->scrCnt[0] / 150.0, 0);
            p_rot = &v4->rot;
LABEL_1433:
            sub_1B335A0(p_rot, 0, v795);
            goto LABEL_1434;
          }
LABEL_1097:
          v568 = wk;
          v569 = v568->scrCnt[0];
          if (v569 < 151)
            goto LABEL_1102;
          v568 = wk;
          v569 = v568->scrCnt[0];
          v570 = 21474836490LL * v568->scrCmpCnt;
          if (v569 > (s32)(HIDWORD(v570) + (v570 >> 63) + 150))
          {
LABEL_1102:
            v571 = 15 * scrCmpCnt / 3;
            v572 = v571 + 150;
            v573 = wk->scrCnt[0];
            if (v573 <= v572)
              goto LABEL_1108;
            v573 = wk->scrCnt[0];
            if (v573 > v571 + 160)
            {
LABEL_1108:
              ClrAction();
              v4->aiwk->scrflag &= ~0x200u;
              scrSetIntReturnValue(0);
              sBtlSetRotateDeg(v4);
              goto LABEL_323;
            }
            if (v4->aiwk->scrStep3)
              goto LABEL_1814;
            v839 = v4->pos.x;
            v840 = v4->pos.y;
            v842 = v4->pos.z;
            v841 = v4->pos.w;
            *(__n128 *)&v843 = sub_1B332C0(0, v839, v840, v842, v841);
            sub_1B335A0(&v4->actaiwk->scrPos, 0, v843);
            v844 = v4->aiwk->scrListID;
            if (v844 == 3)
            {
              v847 = wk->scrCmpCnt % 3 + 1;
            }
            else if (v844 == 2)
            {
              v847 = wk->scrCmpCnt % 3 + 2;
            }
            else
            {
              v845 = 0.0;
              if (v844 != 1)
              {
LABEL_1811:
                v4->actaiwk->scrAngle = v845;
                FromEuler(0.0, v845, 0.0);
                ToMatrix();
                sub_1B332C0(0, 0.0, 0.0, 1.0, 0.0);
                *(__n128 *)&v941 = sub_1B33480(0, 300.0);
                (loc_1EA2510)(0, v941);
                sub_1B33360(0, pos.x, pos.y, pos.z, pos.w);
                *(__n128 *)&v942 = sub_1B33520(0);
                sub_1B335A0(&v4->actaiwk->scrPos2, 0, v942);
                v4->aiwk->scrStep3 = 1;
LABEL_1814:
                v943 = v4->actaiwk;
                v944 = v943[33];
                v945 = v943[34];
                v947 = v943[35];
                v946 = v943[36];
                sub_1B332C0(0, v944, v945, v947, v946);
                sub_1B33360(0, v4->actaiwk->scrPos.x, v4->actaiwk->scrPos.y, v4->actaiwk->scrPos.z, v4->actaiwk->scrPos.w);
                sub_1B33400(0);
                sub_1B33480(0, (f32)(wk->scrCnt[0] - v572) / 10.0);
                sub_1B33360(0, v4->actaiwk->scrPos.x, v4->actaiwk->scrPos.y, v4->actaiwk->scrPos.z, v4->actaiwk->scrPos.w);
                *(__n128 *)&v795 = sub_1B33520(0);
                p_rot = &v4->pos;
                goto LABEL_1433;
              }
              v847 = wk->scrCmpCnt % 3;
            }
            v845 = (f32)v847 * 2.0943952;
            goto LABEL_1811;
          }
          scrAngle = v4->actaiwk->scrAngle;
          v569 = wk->scrCnt[0];
          v755 = scrAngle + (f32)((f32)((f32)(v569 % 15) * 6.2831855) / 15.0);
          FromEuler(0.0, v755, 0.0);
          ToMatrix();
          sub_1B332C0(0, 0.0, 0.0, 1.0, 0.0);
          *(__n128 *)&v756 = sub_1B33480(0, 100.0);
          (loc_1EA2510)(0, v756);
          sub_1B33360(0, pos.x, pos.y, pos.z, pos.w);
          *(__n128 *)&v757 = sub_1B33520(0);
          sub_1B335A0(&v4->pos, 0, v757);
          FromEuler(0.0, v755, 0.0);
          sub_1B335A0(&v4->rot, 0, v758);
          sBtlSetRotateDeg(v4);
LABEL_1434:
LABEL_1436:
          v51 = 1;
          goto LABEL_131;
LABEL_1435:
          goto LABEL_1436;
        }
        goto LABEL_1096;
      case 2:
        sBtlGetPointData(1, &pos, &rot);
        v180 = v4->actaiwk->scrAngle;
        v182 = v180
             + (f32)((f32)((f32)(wk->scrCnt[0] % 900) * 6.2831855) / 900.0);
        FromEuler(0.0, v182, 0.0);
        ToMatrix();
        sub_1B332C0(0, 0.0, 0.0, 1.0, 0.0);
        *(__n128 *)&v183 = sub_1B33480(0, 300.0);
        (loc_1EA2510)(0, v183);
        sub_1B33360(0, pos.x, pos.y, pos.z, pos.w);
        *(__n128 *)&v184 = sub_1B33520(0);
        sub_1B335A0(&v4->pos, 0, v184);
        FromEuler(0.0, v182, 0.0);
        p_ppos = &v4->rot;
        goto LABEL_403;
      case 3:
        v188 = wk->effList;
        if (sBtlSearchEffect_SAB(v188, 435, 1u))
          goto LABEL_1714;
        v190 = wk->effList;
        if (sBtlSearchEffect_SAB(v190, 435, 2u))
          goto LABEL_1714;
        v567 = wk->effList;
        if (sBtlSearchEffect_SAB(v567, 435, 5u))
          goto LABEL_1714;
        v781 = wk->effList;
        if (sBtlSearchEffect_SAB(v781, 434, 1u))
          goto LABEL_1714;
        v830 = wk->effList;
        if (sBtlSearchEffect_SAB(v830, 434, 2u))
          goto LABEL_1714;
        v864 = wk->effList;
        if (!sBtlSearchEffect_SAB(v864, 434, 5u))
          goto LABEL_1434;
LABEL_1714:
LABEL_1715:
LABEL_1716:
        v51 = 0;
        goto LABEL_131;
      case 4:
        scrUnitList = wk->scrUnitList;
        v193 = scrUnitList[1];
        v194 = scrUnitList[2];
        switch (v2)
        {
          case 0:
            FromEuler(0.0, 0.0, 0.0);
            *(__n128 *)&v196 = sub_1B335A0(&v193->rot, 0, v195);
            sub_1B335A0(&v194->rot, 0, v196);
            sBtlSetRotateDeg(v193);
            sBtlSetRotateDeg(v194);
            *(__n128 *)&v197 = sub_1B332C0(0, v193->pos.x, v193->pos.y, v193->pos.z, v193->pos.w);
            sub_1B335A0(&v194->pos, 0, v197);
            v194->pos.x = v193->pos.x + -280.0;
            v193->status |= 0x4000u;
            v194->status |= 0x4000u;
            goto LABEL_323;
          case 1:
            v643 = v193->pos.x;
            v644 = v193->pos.y;
            v646 = v193->pos.z;
            v645 = v193->pos.w;
            *(__n128 *)&v647 = sub_1B332C0(0, v643, v644, v646, v645);
            sub_1B335A0(&v193->actaiwk->scrPos, 0, v647);
            v648 = v193->actaiwk;
            v649 = v648->scrPos.y;
            v650 = v648->scrPos.x + -140.0;
            v651 = v648->scrPos.z;
            v652 = v648->scrPos.w;
            v648->scrPos.x = v650;
            *(__n128 *)&v653 = sub_1B332C0(0, v650, v649, v651, v652);
            sub_1B335A0(&v193->actaiwk->movepos, 0, v653);
            v654 = v193->actaiwk;
            v654->scrPos2.x = 0.0;
            v654->scrPos2.y = 0.0;
            v656 = v654;
            v654->scrPos2.z = BLOCKER_MOVE_SPEED;
            v656->scrPos2.w = 0.0;
            sBtlSetSkillTarget(v193, 441, 0x60000u);
            sBtlSetSkillTarget(v194, 441, 0x60000u);
            v193->status |= 0x4001u;
            v194->status |= 0x4001u;
            v193->status &= ~0x80000u;
            v194->status &= ~0x80000u;
            goto LABEL_323;
          case 2:
            v657 = v193->actaiwk;
            v658 = v657[25];
            v659 = v657[26];
            v661 = v657[27];
            v660 = v657[28];
            v185 = sub_1B332C0(0, v658, v659, v661, v660);
            p_ppos = &v193->actaiwk->ppos;
            goto LABEL_403;
          case 3:
            v193->status &= 0xFFFFBFFE;
            v194->status &= 0xFFFFBFFE;
            v193->flg &= ~2u;
            v194->flg &= ~2u;
LABEL_1225:
            ClrAction();
            goto LABEL_323;
          case 4:
            v662 = 5;
            goto LABEL_1228;
          case 5:
            v662 = 6;
LABEL_1228:
            SetAction(v662);
            break;
          default:
            goto LABEL_323;
        }
        goto LABEL_323;
      case 5:
        sBtlGetPointData(2, &pos, &rot);
        v198 = pos.x;
        v199 = pos.y;
        v201 = pos.z;
        v200 = pos.w;
        *(__n128 *)&v202 = sub_1B332C0(0, v198, v199, v201, v200);
        *(__n128 *)&v203 = sub_1B335A0(&v1062, 0, v202);
        sub_1B335A0(&v1060, 0, v203);
        v204 = *(f32 *)&v1062 + -200.0;
        v205 = *(f32 *)&v1060 + 200.0;
        v206 = v4->aiwk;
        v206->scr_actcheckflg = 1;
        *(f32 *)&v1062 = v204;
        *(f32 *)&v1060 = v205;
        switch (v2)
        {
          case 0:
            v207 = *((f32 *)&v1062 + 1);
            v208 = v1063;
            sub_1B332C0(0, v204, v207, *(f32 *)&v208, *((f32 *)&v208 + 1));
            sub_1B33360(0, v4->pos.x, v4->pos.y, v4->pos.z, v4->pos.w);
            sub_1B33400(0);
            v209 = (loc_1CDE880)(0);
            sub_1B332C0(0, *(f32 *)&v1060, *((f32 *)&v1060 + 1), *(f32 *)&v1061, *((f32 *)&v1061 + 1));
            sub_1B33360(0, v4->pos.x, v4->pos.y, v4->pos.z, v4->pos.w);
            sub_1B33400(0);
            v210 = (loc_1CDE880)(0);
            v211 = v4->aiwk;
            v212 = v211->scrflag;
            if (v209 >= v210)
            {
              v214 = v212 | 0x800;
              v213 = v1060;
              v215 = v1061;
            }
            else
            {
              v213 = v1062;
              v214 = v212 & 0xFFFFF7FF;
              v215 = v1063;
            }
            v211->scrflag = v214;
            *(__n128 *)&v759 = sub_1B33360(0, *(f32 *)&v213, *((f32 *)&v213 + 1), *(f32 *)&v215, *((f32 *)&v215 + 1));
            (loc_21189D0)(&v4->actaiwk->movepos, 0, v759);
            v760 = v4->pos.x;
            v761 = v4->pos.y;
            v762 = v4->pos.z;
            v763 = v4->pos.w;
            sub_1B332C0(0, v760, v761, v762, v763);
            sub_1B33400(0);
            sub_1949110(0);
            sub_1B335A0(&v1059, 0, v764);
            v766 = sub_18E6660(0, v765);
            v4->actaiwk->scrAngle = *(f32 *)&v766;
            sub_1B332C0(0, v1059.x, v1059.y, v1059.z, v1059.w);
            sub_1B33480(0, 200.0);
            sub_1B33360(0, v4->actaiwk->movepos.x, v4->actaiwk->movepos.y, v4->actaiwk->movepos.z, v4->actaiwk->movepos.w);
            *(__n128 *)&v767 = sub_1B33520(0);
            sub_1B335A0(&v4->actaiwk->scrPos, 0, v767);
            *(__n128 *)&v768 = sub_1B332C0(0, v4->pos.x, v4->pos.y, v4->pos.z, v4->pos.w);
            sub_1B335A0(&v4->actaiwk->scrPos2, 0, v768);
            sub_1B332C0(0, v4->actaiwk->scrPos.x, v4->actaiwk->scrPos.y, v4->actaiwk->scrPos.z, v4->actaiwk->scrPos.w);
            sub_1B33360(0, v4->actaiwk->scrPos2.x, v4->actaiwk->scrPos2.y, v4->actaiwk->scrPos2.z, v4->actaiwk->scrPos2.w);
            sub_1B33400(0);
            v769 = (loc_1CDE880)(0);
            v771 = (f32)(v769 / v4->max_mvspd.z) + 1.0;
            v772 = v771;
            if (v771 == INFINITY)
              v772 = 0x80000000;
            wk->scrCmpCnt = v772;
            v4->status |= 0x200u;
            goto LABEL_323;
          case 1:
            v539 = v4->actaiwk;
            v540 = v539[25];
            v541 = v539[26];
            v542 = v539[27];
            v543 = v539[28];
            sub_1B332C0(0, v540, v541, v542, v543);
            sub_1B33360(0, v4->actaiwk->scrPos2.x, v4->actaiwk->scrPos2.y, v4->actaiwk->scrPos2.z, v4->actaiwk->scrPos2.w);
            sub_1B33400(0);
            sub_1B33480(0, (f32)wk->scrCnt[1] / (f32)wk->scrCmpCnt);
            sub_1B33360(0, v4->actaiwk->scrPos2.x, v4->actaiwk->scrPos2.y, v4->actaiwk->scrPos2.z, v4->actaiwk->scrPos2.w);
            *(__n128 *)&v545 = sub_1B33520(0);
            sub_1B335A0(&v4->pos, 0, v545);
            v546 = wk;
            scrCnt = v546->scrCnt;
            if (scrCnt[1] >= v546->scrCmpCnt)
            {
              scrCnt = wk->scrCnt;
              scrCnt[1] = 0;
              v4->aiwk->scrStep = 2;
            }
            goto LABEL_323;
          case 2:
            v548 = v4->actaiwk;
            v549 = v548->scrAngle;
            if ((v206->scrflag & 0x800) != 0)
            {
              v774 = v549 + -0.05235988;
              if (v774 >= -7.853982)
                v552 = v774;
              else
                v552 = v774 + 12.566371;
              v548->scrAngle = v552;
              if (v552 >= -1.5707964)
              {
                v824 = *((f32 *)&v1060 + 1);
                v825 = v1061;
                if (!v775)
                *(__n128 *)&v826 = sub_1B332C0(0, v205, v824, *(f32 *)&v825, *((f32 *)&v825 + 1));
                sub_1B335A0(&pos, 0, v826);
                v557 = 1.5707964;
                goto LABEL_1511;
              }
              v776 = *((f32 *)&v1062 + 1);
              v777 = v1063;
              if (!v775)
              *(__n128 *)&v778 = sub_1B332C0(0, v204, v776, *(f32 *)&v777, *((f32 *)&v777 + 1));
              sub_1B335A0(&pos, 0, v778);
              v779 = 4.712389;
            }
            else
            {
              v551 = v549 + 0.05235988;
              if (v551 <= 7.853982)
                v552 = v551;
              else
                v552 = v551 + -12.566371;
              v548->scrAngle = v552;
              if (v552 > 1.5707964)
              {
                v554 = *((f32 *)&v1062 + 1);
                v555 = v1063;
                if (!v553)
                *(__n128 *)&v556 = sub_1B332C0(0, v204, v554, *(f32 *)&v555, *((f32 *)&v555 + 1));
                sub_1B335A0(&pos, 0, v556);
                v557 = 4.712389;
LABEL_1511:
                v823 = v552 + v557;
                goto LABEL_1512;
              }
              v820 = *((f32 *)&v1060 + 1);
              v821 = v1061;
              if (!v553)
              *(__n128 *)&v822 = sub_1B332C0(0, v205, v820, *(f32 *)&v821, *((f32 *)&v821 + 1));
              sub_1B335A0(&pos, 0, v822);
              v779 = 1.5707964;
            }
            v823 = v779 - v552;
            v552 = -v552;
LABEL_1512:
            FromEuler(0.0, v823, 0.0);
            sub_1B335A0(&v4->rot, 0, v827);
            FromEuler(0.0, v552, 0.0);
            ToMatrix();
            sub_1B332C0(0, 0.0, 0.0, 1.0, 0.0);
            *(__n128 *)&v828 = sub_1B33480(0, 200.0);
            (loc_1EA2510)(0, v828);
            sub_1B33360(0, pos.x, pos.y, pos.z, pos.w);
            v185 = sub_1B33520(0);
            p_ppos = &v4->pos;
            goto LABEL_403;
          case 3:
            v4->status &= ~0x200u;
            goto LABEL_323;
          default:
            goto LABEL_323;
        }
      case 6:
        v217 = wk->scrUnitList;
        v219 = v217[1];
        v218 = v217[2];
        switch (v2)
        {
          case 3:
            v219->mode = 9;
            v218->mode = 9;
            break;
          case 2:
            v344 = 0;
LABEL_1026:
            dds3FadeOut(0xFFu, 0xFFu, v344, 0x3Cu);
            break;
          case 0:
            v219->status |= 0x80u;
            v218->status |= 0x80u;
            if (NakamaData)
              NakamaData->status |= 1u;
            v220 = v219->pos.x;
            v221 = v219->pos.y;
            v223 = v219->pos.z;
            v222 = v219->pos.w;
            *(__n128 *)&v224 = sub_1B332C0(0, v220, v221, v223, v222);
            sub_1B335A0(&v1059, 0, v224);
            v1059.z = v1059.z + -3000.0;
            Support_MovePos(v219, v1059);
            *(__n128 *)&v225 = sub_1B332C0(0, v218->pos.x, v218->pos.y, v218->pos.z, v218->pos.w);
            sub_1B335A0(&v1059, 0, v225);
            v1059.z = v1059.z + -3000.0;
            Support_MovePos(v218, v1059);
            break;
        }
        goto LABEL_323;
      case 7:
        if (!v2)
        {
          if (v3 == -1)
          {
            v686 = Support_GetUserData();
            priv_area_r = v686->actaiwk->priv_area_r;
            v688 = v4->pos.x;
            v689 = v4->pos.y;
            v691 = v4->pos.z;
            v690 = v4->pos.w;
            sub_1B332C0(0, v688, v689, v691, v690);
            sub_1B33360(0, v686->pos.x, v686->pos.y, v686->pos.z, v686->pos.w);
            sub_1B33400(0);
            sub_1B335A0(&v1059, 0, v692);
            sub_1949110(0);
            sub_1B33480(0, priv_area_r);
            sub_1B33360(0, v686->pos.x, v686->pos.y, v686->pos.z, v686->pos.w);
            *(__n128 *)&v693 = sub_1B33520(0);
            sub_1B335A0(&v4->actaiwk->scrPos2, 0, v693);
          }
          else
          {
            v226 = v4->actaiwk;
            p_scrPos2 = &v226->scrPos2;
            p_scrRot2 = &v226->scrRot2;
            sBtlGetPointData(v3, p_scrPos2, p_scrRot2);
            v229 = v4->actaiwk;
            v230 = v229->scrPos2.x;
            v229->scrPos2.x = v230 + (f32)((f32)(sub_1B34D00(0, v231) * 200.0) + -100.0);
            v232 = v4->actaiwk;
            v233 = v232->scrPos2.z;
            v232->scrPos2.z = v233 + (f32)((f32)(sub_1B34D00(0, v234) * 200.0) + -100.0);
          }
          v694 = v4->pos.x;
          v695 = v4->pos.y;
          v697 = v4->pos.z;
          v696 = v4->pos.w;
          sub_1B332C0(0, v694, v695, v697, v696);
          sub_1B33360(0, v4->actaiwk->scrPos2.x, v4->actaiwk->scrPos2.y, v4->actaiwk->scrPos2.z, v4->actaiwk->scrPos2.w);
          sub_1B33400(0);
          sub_1B335A0(&v1059, 0, v698);
          v700 = sub_18E6660(0, v699);
          FromEuler(0.0, *(f32 *)&v700, 0.0);
          sub_1B335A0(&v4->actaiwk->scrRot2, 0, v701);
          *(__n128 *)&v702 = sub_1B332C0(0, v4->pos.x, v4->pos.y, v4->pos.z, v4->pos.w);
          sub_1B335A0(&v4->actaiwk->scrPos, 0, v702);
          *(__n128 *)&v703 = sub_1B332C0(0, v4->rot.x, v4->rot.y, v4->rot.z, v4->rot.w);
          sub_1B335A0(&v4->actaiwk->scrRot, 0, v703);
          v519 = 452;
          v704 = v4;
LABEL_1503:
          sBtlSetSkillTarget(v704, v519, 0x60000u);
        }
        goto LABEL_323;
      case 8:
      case 9:
      case 13:
        goto LABEL_320;
      case 10:
      case 29:
        goto LABEL_323;
      case 11:
        v235 = 0;
        while (1)
        {
          v237 = wk->UnitMng;
          if (v235 >= v237->number)
            break;
          v237 = wk->UnitMng;
          pUnit = v237->pUnitL[v235]->pUnit;
          if (pUnit)
          {
            v239 = sBtlCheckDamageTarget(pUnit);
            if (v239 && (pUnit->side & 2) != 0)
            {
              hstatus = pUnit->hstatus;
              pUnit->mode = 9;
              pUnit->hstatus = hstatus | 8;
            }
          }
          ++v235;
        }
        goto LABEL_323;
      case 12:
        if (v2 == 1)
        {
          v241 = 0;
          while (1)
          {
            v243 = wk->UnitMng;
            if (v241 >= v243->number)
              break;
            v243 = wk->UnitMng;
            v244 = v243->pUnitL[v241]->pUnit;
            if (v244)
            {
              if (v244->actwk->status != 10)
              {
                devilid = (u16)v244->para->devilid;
                if ((devilid == 298 || devilid == 166) && v244->mode >= 5)
                {
                  v244->aiwk->scrflag |= 0x200u;
                  v244->sewk->flag |= 1u;
                  sBtlSetSkillTarget(v244, 469, 0x60000u);
                }
              }
            }
            ++v241;
          }
        }
        goto LABEL_323;
      case 14:
        v247 = wk->scrUnitList[0];
        if (v2 != 2)
        {
          if (v2 == 1)
          {
            switch (v3)
            {
              case 1:
                v519 = 498;
                goto LABEL_1502;
              case 2:
                v519 = 499;
                goto LABEL_1502;
              case 3:
                v519 = 236;
                goto LABEL_1502;
              case 4:
                v519 = 237;
LABEL_1502:
                v704 = wk->scrUnitList[0];
                goto LABEL_1503;
              default:
                goto LABEL_323;
            }
          }
          if (v2)
            goto LABEL_323;
          if (v3 == 2)
          {
            v248 = 102;
          }
          else
          {
            if (v3 != 1)
            {
LABEL_1419:
              v4->vstatus |= 0x800000u;
              goto LABEL_323;
            }
            v248 = 101;
          }
          sBtlGetUnitHelperPos(v247, v248);
          sub_1B335A0(&v4->pos, 0, v783);
          goto LABEL_1419;
        }
        if (v3 == 1)
        {
          sBtlGetUnitHelperPos(v247, 201);
          sub_1B335A0(&v4->pos, 0, v797);
          v516 = v4->pos.y;
          v518 = v4->pos.x + -130.0;
          v517 = 140.0;
        }
        else
        {
          if (v3 != 2)
          {
            v518 = v4->pos.x;
            v798 = v4->pos.y;
            goto LABEL_1444;
          }
          sBtlGetUnitHelperPos(v247, 202);
          sub_1B335A0(&v4->pos, 0, v515);
          v516 = v4->pos.y;
          v517 = 100.0;
          v518 = v4->pos.x + 100.0;
        }
        v798 = v516 + v517;
        v4->pos.x = v518;
        v4->pos.y = v516 + v517;
LABEL_1444:
        v4->vstatus |= 0x800000u;
        v800 = v4->pos.z;
        v799 = v4->pos.w;
        v1073.x = v518;
        v1073.y = v798;
        v1073.z = v800;
        v1073.w = v799;
        dds3SetPosPoseSet(&v4->pBasic, v1073);
        goto LABEL_323;
      case 15:
        if (v2 == 2)
        {
          v493 = 0;
          v4->status &= 0xFFFFBFFE;
          while (1)
          {
            v495 = wk->UnitMng;
            if (v493 >= v495->number)
              break;
            v495 = wk->UnitMng;
            v496 = v495->pUnitL[v493]->pUnit;
            if (v496)
            {
              if ((v496->side & 2) != 0)
              {
                status = v496->status;
                if ((status & 0x4000) != 0)
                  v496->status = status & 0xFFFFBFFE;
              }
            }
            ++v493;
          }
        }
        else if (!v2)
        {
          v249 = v4->status;
          v250 = -16386;
LABEL_603:
          v4->status = v249 & v250;
        }
        goto LABEL_323;
      case 16:
        if (v2 != 2)
        {
          if (v2 != 1)
          {
            if (v2)
              goto LABEL_323;
            v252 = UserData->pos.x;
            v253 = UserData->pos.y;
            v254 = wk->scrUnitList[2];
            v256 = UserData->pos.z;
            v255 = UserData->pos.w;
            sub_1B332C0(0, v252, v253, v256, v255);
            sub_1B33360(0, v254[41], v254[42], v254[43], v254[44]);
            sub_1B33400(0);
            sub_1949110(0);
            sub_1B335A0(&v1059, 0, v257);
            scrStep2 = 0;
            while (1)
            {
              sBtlGetPointData(scrStep2, &v1065, &rot);
              v258 = v1065.x;
              v259 = v1065.y;
              v260 = v1065.z;
              v261 = v1065.w;
              sub_1B332C0(0, v258, v259, v260, v261);
              sub_1B33360(0, v254[41], v254[42], v254[43], v254[44]);
              sub_1B33400(0);
              *(__n128 *)&v263 = sub_1B335A0(&v1057, 0, v262);
              v264 = (loc_1CDE880)(0, v263);
              sub_1B332C0(0, *(f32 *)&v1057, *((f32 *)&v1057 + 1), *(f32 *)&v1058, *((f32 *)&v1058 + 1));
              sub_1949110(0);
              sub_1B335A0(&v1057, 0, v265);
              if (v264 > 200.0 && (f32)((f32)(v1059.x * *(f32 *)&v1057) + (f32)(v1059.z * *(f32 *)&v1058)) < 0.0)
              {
                goto LABEL_128;
              }
              if (++scrStep2 == 25)
              {
                scrStep2 = 8;
                goto LABEL_128;
              }
            }
          }
          if (v4->aiwk->scrListID == 1)
          {
            v525 = &wk->scrUnitList[2];
          }
          else
          {
            v525 = &wk->scrUnitList[1];
          }
          v726 = v525;
          v727 = 1000000.0;
          v728 = 0;
          v729 = 8;
          while (1)
          {
            sBtlGetPointData(v728, &v1065, &rot);
            v1051 = v1065;
            vct_A = v1051;
            v733 = UserData->pos;
            vct_B = v733;
            vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
            p_x = &vf00.x;
            v735 = p_x[4];
            v736 = p_x[5];
            v737 = p_x[6];
            v739 = sqrtf((f32)((f32)(v735 * v735) + (f32)(v736 * v736)) + (f32)(v737 * v737));
            if (!v726)
              goto LABEL_1314;
            if (wk->scrStep == 2)
            {
LABEL_1314:
              v730 = v739 < v727;
              v731 = v739 <= 100.0;
            }
            else
            {
              v743 = v1065.x;
              v742 = v1065.y;
              v745 = v1065.z;
              v744 = v1065.w;
              if ((v726->aiwk->scrflag & 8) != 0)
              {
                if (!v741)
                sub_1B332C0(0, v743, v742, v745, v744);
                sub_1B33360(0, v726->pos.x, v726->pos.y, v726->pos.z, v726->pos.w);
                sub_1B33400(0);
                v749 = (loc_1CDE880)(0);
                sub_1B332C0(0, v1065.x, v1065.y, v1065.z, v1065.w);
                sub_1B33360(0, v726->actaiwk->scrPos.x, v726->actaiwk->scrPos.y, v726->actaiwk->scrPos.z, v726->actaiwk->scrPos.w);
                sub_1B33400(0);
                (loc_1CDE880)(0);
                v730 = v739 < v727;
                if (v739 <= 100.0)
                  v730 = 0;
                v747 = v749 <= 200.0;
              }
              else
              {
                if (!v741)
                sub_1B332C0(0, v743, v742, v745, v744);
                sub_1B33360(0, v726->pos.x, v726->pos.y, v726->pos.z, v726->pos.w);
                sub_1B33400(0);
                (loc_1CDE880)(0);
                v730 = v739 < v727;
                v747 = v739 <= 100.0;
              }
              if (v747)
                v730 = 0;
              v731 = v746 <= 200.0;
            }
            if (v731)
              v730 = 0;
            if (v730)
            {
              v727 = v739;
              v729 = v728;
            }
            if (++v728 == 25)
            {
              sBtlGetPointData(v729, &v1065, &rot);
              v750 = v1065.x;
              v751 = v1065.y;
              v752 = v1065.z;
              v753 = v1065.w;
              sub_1B332C0(0, v750, v751, v752, v753);
              sub_1B33360(0, v4->pos.x, v4->pos.y, v4->pos.z, v4->pos.w);
              sub_1B33400(0);
              if ((loc_1CDE880)(0) < 300.0)
                scrStep2 = -1;
              else
                scrStep2 = v729;
              goto LABEL_128;
            }
          }
        }
        if (v4->aiwk->scrListID == 1)
        {
          v522 = &wk->scrUnitList[2];
        }
        else
        {
          v522 = &wk->scrUnitList[1];
        }
        v705 = v522;
        while (1)
        {
          v706 = sub_1905740(10, 0);
          sBtlGetPointData(v706, &v1065, &rot);
          v1048 = v1065;
          vct_A = v1048;
          v708 = UserData->pos;
          vct_B = v708;
          vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
          v709 = &vf00.x;
          v710 = v709[4];
          v711 = v709[5];
          v712 = v709[6];
          v714 = sqrtf((f32)((f32)(v710 * v710) + (f32)(v711 * v711)) + (f32)(v712 * v712));
          if (!v705)
            goto LABEL_1265;
          if (wk->scrStep == 2)
          {
LABEL_1265:
            if (v714 > 100.0)
              goto LABEL_1307;
          }
          else
          {
            v718 = v1065.x;
            v717 = v1065.y;
            v720 = v1065.z;
            v719 = v1065.w;
            if ((v705->aiwk->scrflag & 8) != 0)
            {
              if (!v716)
              sub_1B332C0(0, v718, v717, v720, v719);
              sub_1B33360(0, v705->pos.x, v705->pos.y, v705->pos.z, v705->pos.w);
              sub_1B33400(0);
              v724 = (loc_1CDE880)(0);
              sub_1B332C0(0, v1065.x, v1065.y, v1065.z, v1065.w);
              sub_1B33360(0, v705->actaiwk->scrPos.x, v705->actaiwk->scrPos.y, v705->actaiwk->scrPos.z, v705->actaiwk->scrPos.w);
              sub_1B33400(0);
              (loc_1CDE880)(0);
              if (v714 > 100.0 && v724 > 200.0 && v725 > 200.0)
              {
LABEL_1307:
                v51 = v706;
                goto LABEL_131;
              }
            }
            else
            {
              if (!v716)
              sub_1B332C0(0, v718, v717, v720, v719);
              sub_1B33360(0, v705->pos.x, v705->pos.y, v705->pos.z, v705->pos.w);
              sub_1B33400(0);
              (loc_1CDE880)(0);
              v722 = v714 <= 100.0 || v721 <= 200.0;
              if (!v722)
                goto LABEL_1307;
            }
          }
        }
      case 17:
        if (v2)
        {
          sBtlRestartMotion(v4);
          m_rate = v4->m_rate;
        }
        else
        {
          v4->m_rate = 0.0;
          m_rate = 0.0;
        }
        hModel = v4->hModel;
        mdlSetMotionSpeed(hModel, m_rate);
        goto LABEL_323;
      case 18:
        if (v2)
        {
          if (v2 != 1)
            goto LABEL_323;
          v267 = v7;
          v268 = 0;
          v269 = 0;
          while (1)
          {
            sBtlGetPointData(v268, &v1065, &rot);
            v1041 = v1065;
            vct_A = v1041;
            v271 = UserData->pos;
            vct_B = v271;
            vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
            v272 = &vf00.x;
            v273 = v272[4];
            v274 = v272[5];
            v275 = v272[6];
            v277 = sqrtf((f32)((f32)(v273 * v273) + (f32)(v274 * v274)) + (f32)(v275 * v275));
            if (v277 > 550.0 && v277 < 800.0)
            {
              v279 = v267 + 4 * (s32)v269++;
              *(u32 *)(v279 + 32) = v268;
            }
            if (++v268 == 29)
            {
              if (v269)
                scrStep2 = *(u32 *)(v267 + 4 * (u32)sub_1905740(v269, 0) + 32);
              else
                scrStep2 = 23;
              goto LABEL_128;
            }
          }
        }
        v498 = 1000000.0;
        scrStep2 = 23;
        while (1)
        {
          sBtlGetPointData(v2, &v1065, &rot);
          v1045 = v1065;
          vct_A = v1045;
          v502 = UserData->pos;
          vct_B = v502;
          vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
          v503 = &vf00.x;
          v504 = v503[4];
          v505 = v503[5];
          v506 = v503[6];
          v500 = sqrtf((f32)((f32)(v504 * v504) + (f32)(v505 * v505)) + (f32)(v506 * v506));
          if (v500 < v498 && v500 > 100.0)
          {
            v498 = v500;
            scrStep2 = v2;
          }
          if (++v2 == 29)
            goto LABEL_128;
        }
      case 19:
        if (v2 == 1)
        {
          v508 = v4->para->devilid;
          v509 = v4->para->devilid;
          DevilData = sBtlGetDevilData(v508, -1);
          v4->aisyoid = v509;
          v4->motion_setno = 20;
          aishou = DevilData->aishou;
          Aisyotbl = sBtlGetAisyotbl(aishou);
          ClassCopy(v4->para->aisyo, Aisyotbl, 0);
        }
        else if (!v2)
        {
          *(u64 *)&v281 = 0x100000001000LL;
          *((u64 *)&v281 + 1) = 0x100000001000LL;
          para = v4->para->aisyo->para;
          *(_OWORD *)para = v281;
          *(_OWORD *)&para[4] = v281;
          *(_OWORD *)&para[8] = v281;
          *(_OWORD *)&para[12] = v281;
        }
        goto LABEL_323;
      case 20:
        if (v2)
        {
          for (i = 0; ; ++i)
          {
            v285 = wk->UnitMng;
            if (i >= v285->number)
              break;
            v285 = wk->UnitMng;
            v286 = v285->pUnitL[i]->pUnit;
            if (v286)
            {
              v287 = (u16)v286->para->devilid - 261;
              v722 = v287 > 0x3E;
              v288 = (1 << v287) & 0x4000030000000005LL;
              v289 = v722 || v288 == 0;
              if (!v289 && v286->mode >= 4)
                v286->mode = 9;
            }
          }
          sBtlBS_RASUPU_Dead_EffStop();
        }
        else
        {
          for (j = 0; ; ++j)
          {
            v481 = wk->UnitMng;
            if (j >= v481->number)
              break;
            v481 = wk->UnitMng;
            v482 = v481->pUnitL[j]->pUnit;
            if (v482)
            {
              v483 = (u16)v482->para->devilid - 261;
              v722 = v483 > 0x3E;
              v484 = (1 << v483) & 0x4000030000000005LL;
              v485 = v722 || v484 == 0;
              if (!v485 && v482->mode >= 5)
              {
                v482->status |= 0x4011u;
                sBtlSetFade(v482, 2, 0, 0, 2);
              }
            }
          }
          sBtlBS_RASUPU_Dead_EffStop0();
        }
        goto LABEL_323;
      case 21:
        if (v2 == 3)
        {
          v526 = v4->pos.x;
          v527 = v4->pos.y;
          v529 = v4->pos.z;
          v528 = v4->pos.w;
          sub_1B332C0(0, v526, v527, v529, v528);
          sub_1B33360(0, UserData->pos.x, UserData->pos.y, UserData->pos.z, UserData->pos.w);
          sub_1B33400(0);
          sub_1B335A0(&v1059, 0, v530);
          v532 = sub_18E6660(0, v531);
          v533 = *(f32 *)&v532;
          FromEuler(0.0, *(f32 *)&v532, 0.0);
          sub_1B335A0(&v4->rot, 0, v534);
          v4->mv_rotbk = v533;
          scrStep2 = 1;
          goto LABEL_128;
        }
        if (v2 != 2)
        {
          if (v2 != 1)
            goto LABEL_1750;
          v291 = wk;
          scrStep2 = 1;
          switch (v291->scrLoadStat)
          {
            case 0:
              v292 = v291->effList;
              if (sBtlSearchEffect_SAB(v292, 436, 1u))
                goto LABEL_1750;
              v902 = wk->effList;
              if (sBtlSearchEffect_SAB(v902, 436, 2u))
                goto LABEL_1750;
              v921 = wk->effList;
              if (!sBtlSearchEffect_SAB(v921, 436, 5u))
                goto LABEL_1792;
LABEL_1750:
              scrStep2 = 0;
              goto LABEL_128;
LABEL_1792:
              scrStep2 = 0;
              wk->scrLoadStat = 1;
              goto LABEL_128;
            case 1:
              v831 = 436;
              goto LABEL_1533;
            case 2:
              goto LABEL_1447;
            case 3:
              goto LABEL_1451;
            case 4:
              goto LABEL_128;
            default:
              goto LABEL_1750;
          }
        }
        v536 = wk;
        scrStep2 = 1;
        switch (v536->scrLoadStat)
        {
          case 0:
            v537 = v536->effList;
            if (sBtlSearchEffect_SAB(v537, 437, 1u))
              goto LABEL_1750;
            v904 = wk->effList;
            if (sBtlSearchEffect_SAB(v904, 437, 2u))
              goto LABEL_1750;
            v923 = wk->effList;
            if (sBtlSearchEffect_SAB(v923, 437, 5u))
              goto LABEL_1750;
            goto LABEL_1792;
          case 1:
            v831 = 437;
LABEL_1533:
            sBtlForceDelete_EffectWork_ID(v831, 1);
            scrStep2 = 0;
            wk->scrLoadStat = 2;
            goto LABEL_128;
          case 2:
LABEL_1447:
            if (CheckLoadData(0))
              goto LABEL_1750;
            scrStep2 = 0;
            v802 = wk;
            v802->status2 |= 0x200u;
            v802->scrLoadStat = 3;
            goto LABEL_128;
          case 3:
LABEL_1451:
            if (!sBtlLoadEffectData_ID(414))
              goto LABEL_1750;
            scrStep2 = 0;
            v804 = wk;
            v804->scrLoadStat = 4;
            v804->status2 &= ~0x200u;
            goto LABEL_128;
          case 4:
            goto LABEL_128;
          default:
            goto LABEL_1750;
        }
      case 22:
        v294 = v4->pos.x;
        v295 = v4->pos.y;
        v297 = v4->pos.z;
        v296 = v4->pos.w;
        sub_1B332C0(0, v294, v295, v297, v296);
        sub_1B33360(0, UserData->pos.x, UserData->pos.y, UserData->pos.z, UserData->pos.w);
        sub_1B33400(0);
        sub_1B335A0(&v1059, 0, v298);
        v300 = sub_18E6660(0, v299);
        v301 = *(f32 *)&v300;
        FromEuler(0.0, *(f32 *)&v300, 0.0);
        sub_1B335A0(&v4->rot, 0, v302);
        v4->mv_rotbk = v301;
        goto LABEL_323;
      case 23:
        UserData->status |= 0x10u;
        v319 = UserData->actwk->status;
        if (v319 > 0x28 || ((1 << v319) & 0x10400000400LL) == 0)
        {
          if (!v2)
          {
            sBtlSetMotion(UserData, 12, 0, 0, 0);
          }
          sBtlSetAction(UserData, 42, 0);
        }
        wk->status |= 0x42000000u;
        goto LABEL_323;
      case 24:
        v4->status |= 0x80000000;
        goto LABEL_323;
      case 25:
        switch (v2)
        {
          case 0:
            v303 = 0;
            while (1)
            {
              v305 = wk->UnitMng;
              if (v303 >= v305->number)
                break;
              v305 = wk->UnitMng;
              v306 = v305->pUnitL[v303]->pUnit;
              if (v306 && v306->para->devilid == 311)
                v306->mode = 9;
              ++v303;
            }
            goto LABEL_323;
          case 1:
            if (v3)
            {
              if (!v558)
              sBtlSetHelperHit(v4);
            }
            else
            {
              if (!v558)
              sBtlResetHelperHit(v4);
            }
            goto LABEL_323;
          case 2:
            LODWORD(v12) = 1;
            BS_LASTB2_pos_type = 1;
            return (s32)v12;
          case 3:
            BS_LASTB2_pos_type = 0;
            v562 = wk;
            scrLoadStat = v562->scrLoadStat;
            if (scrLoadStat != 1)
            {
              if (scrLoadStat)
                goto LABEL_1776;
              v564 = v562->effList;
              if (sBtlSearchEffect_SAB(v564, 232, 1u))
                goto LABEL_1776;
              v860 = wk->effList;
              if (sBtlSearchEffect_SAB(v860, 232, 2u))
                goto LABEL_1776;
              v906 = wk->effList;
              if (sBtlSearchEffect_SAB(v906, 232, 5u))
                goto LABEL_1776;
              v928 = 1;
              sBtlForceDelete_EffectWork_ID(232, 1);
LABEL_1775:
              wk->scrLoadStat = v928;
LABEL_1776:
              v932 = wk->scrLoadStat;
              if (v932 == 2)
              {
                if (!v933)
                LODWORD(v12) = 1;
                scrSetIntReturnValue(1);
                return (s32)v12;
              }
              if (!v933)
                goto LABEL_1715;
              goto LABEL_1716;
            }
            v806 = v562->effList;
            if (sBtlSearchEffect_SAB(v806, 231, 1u))
              goto LABEL_1776;
            v862 = wk->effList;
            if (sBtlSearchEffect_SAB(v862, 231, 2u))
              goto LABEL_1776;
            v908 = wk->effList;
            if (sBtlSearchEffect_SAB(v908, 231, 5u))
              goto LABEL_1776;
            sBtlForceDelete_EffectWork_ID(231, 1);
            v928 = 2;
            goto LABEL_1775;
          default:
            goto LABEL_323;
        }
      case 26:
        if (v2 > 99)
        {
          switch (v2)
          {
            case 'f':
              v1055 = 0;
              v1056 = 0;
              sBtlGetUnitHelperPos(v4, 20);
              p_ppos = &v1055;
LABEL_403:
              sub_1B335A0(p_ppos, 0, *(long f64 *)&v185);
              break;
            case 'e':
              v681 = UserData->pos.x;
              v682 = UserData->pos.y;
              v684 = UserData->pos.z;
              v683 = UserData->pos.w;
              if ((u32)(v3 - 1) >= 4)
                v685 = 500.0;
              else
                v685 = 400.0;
              v1072.x = v681;
              v1072.y = v682;
              v1072.z = v684;
              v1072.w = v683;
              BS14_TargetSet(v4, v1072, v685, 120.0, 0);
              break;
            case 'd':
              BS14_CHOUSIN_TargetSet(v4);
              break;
          }
          goto LABEL_323;
        }
        if (v2)
        {
          if (v2 != 1)
          {
            if (v2 != 2)
              goto LABEL_323;
            sBtlGetPointData(10, &v1065, &rot);
            v307 = v1065.x;
            v308 = v1065.y;
            v310 = v1065.z;
            v309 = v1065.w;
            sub_1B332C0(0, v307, v308, v310, v309);
            sub_1B33360(0, UserData->pos.x, UserData->pos.y, UserData->pos.z, UserData->pos.w);
            sub_1B33400(0);
            v311 = (loc_1CDE880)(0);
            sBtlGetPointData(17, &v1065, &rot);
            sub_1B332C0(0, v1065.x, v1065.y, v1065.z, v1065.w);
            sub_1B33360(0, UserData->pos.x, UserData->pos.y, UserData->pos.z, UserData->pos.w);
            sub_1B33400(0);
            v312 = (loc_1CDE880)(0);
            if (v311 >= v312)
            {
              if (!v314)
              v51 = 2;
              goto LABEL_131;
            }
            if (v314)
              goto LABEL_1436;
            goto LABEL_1435;
          }
          v676 = UserData->pos.x;
          v677 = UserData->pos.y;
          v679 = UserData->pos.z;
          v678 = UserData->pos.w;
          v1071.x = v676;
          BS14_CSHO_R_SIZE_local = 400.0;
          v675 = 240.0;
          v1071.y = v677;
          v1071.z = v679;
          v1071.w = v678;
          v672 = v4;
          v673 = 60;
        }
        else
        {
          v663 = UserData->pos.x;
          v664 = UserData->pos.y;
          v666 = UserData->pos.z;
          v665 = UserData->pos.w;
          v1071.x = v663;
          v1071.y = v664;
          v1071.z = v666;
          v1071.w = v665;
          v672 = v4;
          v673 = 0;
          BS14_CSHO_R_SIZE_local = BS14_CSHO_R_SIZE;
          v675 = 352.0;
        }
        v680 = BS14_TargetSet(v672, v1071, BS14_CSHO_R_SIZE_local, v675, v673);
        sBtlGetPointData(v680, &v1065, &rot);
        if (UserData->pos.x > v1065.x)
        {
          scrStep2 = -1;
          goto LABEL_128;
        }
        sBtlGetPointData(v680, &v1065, &rot);
        if (UserData->pos.x < v1065.x)
        {
          scrStep2 = 1;
          goto LABEL_128;
        }
        goto LABEL_1750;
      case 27:
        switch (v2)
        {
          case 1:
            v322 = wk;
            v323 = 1;
            switch (v322->scrLoadStat)
            {
              case 0:
                v322 = wk;
                if ((v322->scrFlag & 0x800) != 0)
                  goto LABEL_1920;
                v322 = wk;
                v324 = v322->effList;
                v325 = sBtlSearchEffect_SAB(v324, 464, 1u);
                if (v325)
                  goto LABEL_1920;
                v326 = wk->effList;
                v327 = sBtlSearchEffect_SAB(v326, 464, 2u);
                if (v327)
                  goto LABEL_1920;
                v329 = wk->effList;
                if (sBtlSearchEffect_SAB(v329, 464, 5u))
                {
                  goto LABEL_1920;
                }
                sBtlForceDelete_EffectWork_ID(464, 1);
                wk->scrFlag |= 0x800u;
LABEL_1920:
                v976 = wk;
                if ((v976->scrFlag & 0x1000) != 0)
                  goto LABEL_1968;
                v976 = wk;
                v977 = v976->effList;
                v978 = sBtlSearchEffect_SAB(v977, 235, 1u);
                if (v978)
                  goto LABEL_1968;
                v979 = wk->effList;
                v980 = sBtlSearchEffect_SAB(v979, 235, 2u);
                if (v980)
                {
LABEL_1968:
                  v990 = wk;
                  if ((v990->scrFlag & 0x2000) != 0)
                    goto LABEL_2016;
                  v990 = wk;
                  v991 = v990->effList;
                  v992 = sBtlSearchEffect_SAB(v991, 228, 1u);
                  if (v992)
                    goto LABEL_2016;
                  v993 = wk->effList;
                  v994 = sBtlSearchEffect_SAB(v993, 228, 2u);
                  if (v994)
                  {
LABEL_2016:
                    v1004 = wk;
                    if ((v1004->scrFlag & 0x4000) != 0)
                      goto LABEL_2064;
                    v1004 = wk;
                    v1005 = v1004->effList;
                    v1006 = sBtlSearchEffect_SAB(v1005, 499, 1u);
                    if (v1006)
                      goto LABEL_2064;
                    v1007 = wk->effList;
                    v1008 = sBtlSearchEffect_SAB(v1007, 499, 2u);
                    if (v1008)
                    {
LABEL_2064:
                      v1018 = wk;
                      if ((v1018->scrFlag & 0x8000) == 0)
                      {
                        v1018 = wk;
                        v1019 = v1018->effList;
                        v1020 = sBtlSearchEffect_SAB(v1019, 466, 1u);
                        if (!v1020)
                        {
                          v1021 = wk->effList;
                          v1022 = sBtlSearchEffect_SAB(v1021, 466, 2u);
                          if (!v1022)
                          {
                            goto LABEL_2106;
                          }
                        }
                      }
                      goto LABEL_2109;
                    }
                    v1010 = wk->effList;
                    if (sBtlSearchEffect_SAB(v1010, 499, 5u))
                    {
                      goto LABEL_2064;
                    }
                    sBtlForceDelete_EffectWork_ID(499, 1);
                    wk->scrFlag |= 0x4000u;
                    goto LABEL_2064;
                  }
                  v996 = wk->effList;
                  if (sBtlSearchEffect_SAB(v996, 228, 5u))
                  {
                    goto LABEL_2016;
                  }
                  sBtlForceDelete_EffectWork_ID(228, 1);
                  wk->scrFlag |= 0x2000u;
                  goto LABEL_2016;
                }
                v982 = wk->effList;
                if (sBtlSearchEffect_SAB(v982, 235, 5u))
                {
                  goto LABEL_1968;
                }
                sBtlForceDelete_EffectWork_ID(235, 1);
                wk->scrFlag |= 0x1000u;
                goto LABEL_1968;
              case 1:
                goto LABEL_1536;
              case 2:
                if (!sBtlLoadEffectData_ID(498))
                  goto LABEL_2188;
                v868 = 237;
                goto LABEL_1628;
              case 3:
                if (!sBtlLoadEffectData_ID(237))
                  goto LABEL_2188;
                goto LABEL_1601;
              case 4:
                goto LABEL_1540;
              case 5:
                goto LABEL_1548;
              case 6:
                goto LABEL_2198;
              default:
                goto LABEL_2188;
            }
          case 2:
            v613 = wk;
            v323 = 1;
            switch (v613->scrLoadStat)
            {
              case 0:
                v613 = wk;
                if ((v613->scrFlag & 0x800) != 0)
                  goto LABEL_1944;
                v613 = wk;
                v614 = v613->effList;
                v615 = sBtlSearchEffect_SAB(v614, 464, 1u);
                if (v615)
                  goto LABEL_1944;
                v616 = wk->effList;
                v617 = sBtlSearchEffect_SAB(v616, 464, 2u);
                if (v617)
                  goto LABEL_1944;
                v619 = wk->effList;
                if (sBtlSearchEffect_SAB(v619, 464, 5u))
                {
                  goto LABEL_1944;
                }
                sBtlForceDelete_EffectWork_ID(464, 1);
                wk->scrFlag |= 0x800u;
LABEL_1944:
                v983 = wk;
                if ((v983->scrFlag & 0x1000) != 0)
                  goto LABEL_1992;
                v983 = wk;
                v984 = v983->effList;
                v985 = sBtlSearchEffect_SAB(v984, 474, 1u);
                if (v985)
                  goto LABEL_1992;
                v986 = wk->effList;
                v987 = sBtlSearchEffect_SAB(v986, 474, 2u);
                if (v987)
                {
LABEL_1992:
                  v997 = wk;
                  if ((v997->scrFlag & 0x2000) != 0)
                    goto LABEL_2040;
                  v997 = wk;
                  v998 = v997->effList;
                  v999 = sBtlSearchEffect_SAB(v998, 229, 1u);
                  if (v999)
                    goto LABEL_2040;
                  v1000 = wk->effList;
                  v1001 = sBtlSearchEffect_SAB(v1000, 229, 2u);
                  if (v1001)
                  {
LABEL_2040:
                    v1011 = wk;
                    if ((v1011->scrFlag & 0x4000) != 0)
                      goto LABEL_2092;
                    v1011 = wk;
                    v1012 = v1011->effList;
                    v1013 = sBtlSearchEffect_SAB(v1012, 498, 1u);
                    if (v1013)
                      goto LABEL_2092;
                    v1014 = wk->effList;
                    v1015 = sBtlSearchEffect_SAB(v1014, 498, 2u);
                    if (v1015)
                    {
LABEL_2092:
                      v1025 = wk;
                      if ((v1025->scrFlag & 0x8000) == 0)
                      {
                        v1025 = wk;
                        v1026 = v1025->effList;
                        v1027 = sBtlSearchEffect_SAB(v1026, 466, 1u);
                        if (!v1027)
                        {
                          v1028 = wk->effList;
                          v1029 = sBtlSearchEffect_SAB(v1028, 466, 2u);
                          if (!v1029)
                          {
                            v1024 = wk->effList;
                            goto LABEL_2107;
LABEL_2106:
                            v1024 = wk->effList;
                            if (!sBtlSearchEffect_SAB(v1024, 466, 5u))
                            {
LABEL_2080:
                              sBtlForceDelete_EffectWork_ID(466, 1);
                              wk->scrFlag |= 0x8000u;
                              goto LABEL_2109;
                            }
LABEL_2108:
                            goto LABEL_2109;
LABEL_2107:
                            if (!sBtlSearchEffect_SAB(v1024, 466, 5u))
                              goto LABEL_2080;
                            goto LABEL_2108;
                          }
                        }
                      }
LABEL_2109:
                      v834 = wk;
                      v1031 = v834->scrFlag;
                      if ((v1031 & 0x800) != 0)
                      {
                        v834 = wk;
                        v1031 = v834->scrFlag;
                        if ((v1031 & 0x1000) != 0)
                        {
                          v834 = wk;
                          v1031 = v834->scrFlag;
                          if ((v1031 & 0x2000) != 0)
                          {
                            v834 = wk;
                            v1031 = v834->scrFlag;
                            if ((v1031 & 0x4000) != 0)
                            {
                              v834 = wk;
                              v1031 = v834->scrFlag;
                              if ((v1031 & 0x8000) != 0)
                              {
                                v834 = wk;
                                v835 = 1;
                                v323 = 0;
LABEL_2197:
                                v834->scrLoadStat = v835;
LABEL_2198:
                                v51 = v323;
LABEL_131:
                                scrSetIntReturnValue(v51);
                                goto LABEL_323;
                              }
                            }
                          }
                        }
                      }
LABEL_2188:
                      v323 = 0;
                      goto LABEL_2198;
                    }
                    v1017 = wk->effList;
                    if (sBtlSearchEffect_SAB(v1017, 498, 5u))
                    {
                      goto LABEL_2092;
                    }
                    sBtlForceDelete_EffectWork_ID(498, 1);
                    wk->scrFlag |= 0x4000u;
                    goto LABEL_2092;
                  }
                  v1003 = wk->effList;
                  if (sBtlSearchEffect_SAB(v1003, 229, 5u))
                  {
                    goto LABEL_2040;
                  }
                  sBtlForceDelete_EffectWork_ID(229, 1);
                  wk->scrFlag |= 0x2000u;
                  goto LABEL_2040;
                }
                v989 = wk->effList;
                if (sBtlSearchEffect_SAB(v989, 474, 5u))
                {
                  goto LABEL_1992;
                }
                sBtlForceDelete_EffectWork_ID(474, 1);
                wk->scrFlag |= 0x1000u;
                goto LABEL_1992;
              case 1:
LABEL_1536:
                if (CheckLoadData(0))
                  goto LABEL_2188;
                v323 = 0;
                v834 = wk;
                v834->status2 |= 0x200u;
                v835 = 2;
                goto LABEL_2197;
              case 2:
                if (!sBtlLoadEffectData_ID(499))
                  goto LABEL_2188;
                v868 = 236;
LABEL_1628:
                sBtlLoadEffectData_ID(v868);
                v835 = 3;
                v323 = 0;
                v834 = wk;
                goto LABEL_2197;
              case 3:
                if (!sBtlLoadEffectData_ID(236))
                  goto LABEL_2188;
LABEL_1601:
                sBtlLoadEffectData_ID(238);
                goto LABEL_1605;
              case 4:
LABEL_1540:
                if (!sBtlLoadEffectData_ID(238))
                  goto LABEL_2188;
                sBtlLoadEffectData_ID(239);
                v835 = 5;
                v323 = 0;
                v834 = wk;
                goto LABEL_2197;
              case 5:
LABEL_1548:
                if (!sBtlLoadEffectData_ID(239))
                  goto LABEL_2188;
                v838 = wk;
                v838->scrLoadStat = 6;
                v838->status2 &= ~0x200u;
                goto LABEL_2198;
              case 6:
                goto LABEL_2198;
              default:
                goto LABEL_2188;
            }
          case 3:
            v607 = wk;
            v323 = 1;
            switch (v607->scrLoadStat)
            {
              case 0:
                v608 = v4->aiwk->scrflag;
                if ((v608 & 0x200) == 0)
                {
                  if ((v608 & 0x400) == 0)
                    goto LABEL_2188;
                  v609 = v607->effList;
                  if (sBtlSearchEffect_SAB(v609, 499, 1u))
                    goto LABEL_2188;
                  v973 = wk->effList;
                  if (sBtlSearchEffect_SAB(v973, 499, 2u))
                    goto LABEL_2188;
                  v1039 = wk->effList;
                  if (sBtlSearchEffect_SAB(v1039, 499, 5u))
                    goto LABEL_2188;
                  v959 = 499;
                  goto LABEL_2192;
                }
                v910 = v607->effList;
                if (sBtlSearchEffect_SAB(v910, 498, 1u))
                  goto LABEL_2188;
                v958 = wk->effList;
                if (sBtlSearchEffect_SAB(v958, 498, 2u))
                  goto LABEL_2188;
                v975 = wk->effList;
                if (sBtlSearchEffect_SAB(v975, 498, 5u))
                  goto LABEL_2188;
                v959 = 498;
                goto LABEL_2192;
              case 1:
                v874 = v4->aiwk->scrflag;
                if ((v874 & 0x200) == 0)
                {
                  if ((v874 & 0x400) == 0)
                    goto LABEL_2188;
                  v875 = v607->effList;
                  if (sBtlSearchEffect_SAB(v875, 235, 1u))
                    goto LABEL_2188;
                  v961 = wk->effList;
                  if (sBtlSearchEffect_SAB(v961, 235, 2u))
                    goto LABEL_2188;
                  v1033 = wk->effList;
                  if (sBtlSearchEffect_SAB(v1033, 235, 5u))
                    goto LABEL_2188;
                  v959 = 235;
                  goto LABEL_2192;
                }
                v912 = v607->effList;
                if (sBtlSearchEffect_SAB(v912, 474, 1u))
                  goto LABEL_2188;
                v950 = wk->effList;
                if (sBtlSearchEffect_SAB(v950, 474, 2u))
                  goto LABEL_2188;
                v967 = wk->effList;
                if (sBtlSearchEffect_SAB(v967, 474, 5u))
                  goto LABEL_2188;
                v959 = 474;
                goto LABEL_2192;
              case 2:
                v877 = v4->aiwk->scrflag;
                if ((v877 & 0x200) == 0)
                {
                  if ((v877 & 0x400) == 0)
                    goto LABEL_2188;
                  v878 = v607->effList;
                  if (sBtlSearchEffect_SAB(v878, 228, 1u))
                    goto LABEL_2188;
                  v963 = wk->effList;
                  if (sBtlSearchEffect_SAB(v963, 228, 2u))
                    goto LABEL_2188;
                  v1035 = wk->effList;
                  if (sBtlSearchEffect_SAB(v1035, 228, 5u))
                    goto LABEL_2188;
                  v959 = 228;
                  goto LABEL_2192;
                }
                v914 = v607->effList;
                if (sBtlSearchEffect_SAB(v914, 229, 1u))
                  goto LABEL_2188;
                v952 = wk->effList;
                if (sBtlSearchEffect_SAB(v952, 229, 2u))
                  goto LABEL_2188;
                v969 = wk->effList;
                if (sBtlSearchEffect_SAB(v969, 229, 5u))
                  goto LABEL_2188;
                v959 = 229;
                goto LABEL_2192;
              case 3:
                v880 = v607->effList;
                if (sBtlSearchEffect_SAB(v880, 465, 1u))
                  goto LABEL_2188;
                v927 = wk->effList;
                if (sBtlSearchEffect_SAB(v927, 465, 2u))
                  goto LABEL_2188;
                v956 = wk->effList;
                if (sBtlSearchEffect_SAB(v956, 465, 5u))
                  goto LABEL_2188;
                sBtlForceDelete_EffectWork_ID(465, 1);
LABEL_1605:
                v835 = 4;
                v323 = 0;
                v834 = wk;
                goto LABEL_2197;
              case 4:
                v882 = v4->rot.x;
                v883 = v4->rot.y;
                v1065.z = 2000.0;
                *(u64 *)&v1065.x = 0x4416000000000000LL;
                v885 = v4->rot.z;
                v884 = v4->rot.w;
                *(__n128 *)&v886 = sub_1B332C0(0, v882, v883, v885, v884);
                sub_1B335A0(&rot, 0, v886);
                v887 = v1065.x;
                v888 = v1065.y;
                v889 = v1065.z;
                v890 = v1065.w;
                v891 = rot.x;
                v892 = rot.y;
                v894 = rot.z;
                v893 = rot.w;
                v1074.x = v887;
                v1074.y = v888;
                v1074.z = v889;
                v1074.w = v890;
                v1075.x = v891;
                v1075.y = v892;
                v1075.z = v894;
                v1075.w = v893;
                sBtlSetExPos(v1074, v1075);
                sBtlSetEncountData3(260, 100, 0, 0);
                goto LABEL_2193;
              case 5:
                v895 = 0;
                while (2)
                {
                  v834 = wk;
                  v896 = v834->UnitMng;
                  if (v895 >= v896->number)
                    goto LABEL_2188;
                  v834 = wk;
                  v896 = v834->UnitMng;
                  v897 = v896->pUnitL[v895]->pUnit;
                  if (!v897 || v897->para->devilid != 260)
                  {
                    ++v895;
                    continue;
                  }
                  break;
                }
                if (v897->mode != 4)
                  goto LABEL_2188;
                v834 = wk;
                v323 = 0;
                goto LABEL_2196;
              case 6:
                v898 = v4->aiwk->scrflag;
                if ((v898 & 0x200) == 0)
                {
                  if ((v898 & 0x400) == 0)
                    goto LABEL_2188;
                  v899 = v607->effList;
                  if (sBtlSearchEffect_SAB(v899, 236, 1u))
                    goto LABEL_2188;
                  v965 = wk->effList;
                  if (sBtlSearchEffect_SAB(v965, 236, 2u))
                    goto LABEL_2188;
                  v1037 = wk->effList;
                  if (sBtlSearchEffect_SAB(v1037, 236, 5u))
                    goto LABEL_2188;
                  v959 = 236;
                  goto LABEL_2192;
                }
                v916 = v607->effList;
                if (sBtlSearchEffect_SAB(v916, 237, 1u))
                  goto LABEL_2188;
                v954 = wk->effList;
                if (sBtlSearchEffect_SAB(v954, 237, 2u))
                  goto LABEL_2188;
                v971 = wk->effList;
                if (sBtlSearchEffect_SAB(v971, 237, 5u))
                  goto LABEL_2188;
                v959 = 237;
                goto LABEL_2192;
              case 7:
                goto LABEL_2198;
              default:
                goto LABEL_2188;
            }
          case 4:
            break;
          case 5:
            sBtlStatusBitOff(v4, 0xFFFFBFFF);
            v323 = 1;
            v4->rot.x = (loc_1FBC910)(0);
            v4->rot.y = v611;
            v4->rot.z = v612;
            v4->rot.w = 1.0;
            goto LABEL_2198;
          default:
            goto LABEL_2188;
        }
        break;
      case 28:
        wk->scrLoadStat = 0;
        goto LABEL_323;
      case 30:
        sBtlStopMotionSE(260, 16);
        sBtlPlayDeadVoice(v4);
        goto LABEL_323;
      case 31:
        v316 = v4->actaiwk;
        v4->vstatus &= ~0x800u;
        v316->status = v316->status & 0xFFFFDD80 | 0x44;
        *(u64 *)&v4->mv_spdbk.x = 0;
        v4->mv_spdbk.z = 0.0;
        v4->mv_rot = 0.0;
        goto LABEL_323;
      case 32:
        v4->sewk->flag |= 1u;
        goto LABEL_323;
      case 33:
        if (v2 == -1)
        {
          v318 = GetData();
        }
        else
        {
          v318 = wk->scrUnitList[v2];
        }
        v318->actwk->status = 1;
        goto LABEL_323;
      case 34:
        v249 = v4->status;
        v250 = -67125250;
        goto LABEL_603;
      default:
        switch (IntPara)
        {
          case 1000:
            wk->status5 &= ~8u;
            if (v2)
              v32 = 52;
            else
              v32 = 13;
            sBtlGetPChara();
            v34 = 0;
            break;
          case 1001:
            v331 = wk;
            v332 = v331->UnitMng;
            boss_eventID = v331->boss_eventID;
            v334 = sBtlSearchUnit_ID(v332, boss_eventID);
            v12 = v334;
            if (!v334)
              return (s32)v12;
            if (!v334[48].n128_u64[1])
              goto LABEL_293;
            v335.n64_u32[0] = 3.0;
            if (!v2)
              v335.n64_f32[0] = 1.7;
            v334[6] = vdupq_lane_s32(v335, 0);
            v1044 = v335.n64_u32[0];
            v335.n64_u32[0] = v1044;
            *(__n128 *)&v336 = sub_1B332C0(0, v335.n64_f32[0], v335.n64_f32[0], v335.n64_f32[0], v335.n64_f32[0]);
            sub_1B335A0(*(u64 *)(v12[47].n128_u64[1] + 56) + 112, 0, v336);
            v337 = v12[48].n128_u64[1];
            mdlSetScale(v337);
            goto LABEL_323;
          case 1002:
            goto LABEL_323;
          case 1003:
            PosReset(v2, v3);
            goto LABEL_323;
          case 1004:
            WajutsuPosSet();
            goto LABEL_323;
          case 1005:
            v339 = wk;
            v340 = v339->UnitMng;
            v341 = v339->boss_eventID;
            v342 = sBtlSearchUnit_ID(v340, v341);
            v342->vstatus |= 0x2000000u;
            sBtlSetMotion(v342, 4, 0, 0, 2);
            v342->actaiwk->scrMotion = 0;
            sBtlGetActionTime(v342, 0);
            sBtlSetMode(13);
            sBtlSetCmbBfrPos();
            CamMovePtn = sBtlGetCamMovePtn(305);
            sBtlSetMove(CamMovePtn, 1);
            goto LABEL_323;
          case 1006:
            v344 = 255;
            goto LABEL_1026;
          case 1007:
            v346 = IndexOf_int_(wk->stock_id, 13);
            v347 = IndexOf_short_(wk->summonindex, v346);
            Nakama = sBtlGetNakama(0);
            v349 = sBtlGetNakama(1);
            v350 = v349;
            if (Nakama && Nakama->para->devilid == 13)
              goto LABEL_323;
            if (!v349)
              goto LABEL_681;
            if (v347 == 1 || v349->para->devilid == 13)
            {
              sBtlDeleteUnit(v350);
LABEL_681:
              *(u32 *)GBWK->player->stack_p = -65536;
              v353 = wk;
              v353->summonindex[0] = v346;
              v353->summonindex_menu[0] = v346;
              *(int8x8_t *)&v353->status4 = vorr_s8(*(int8x8_t *)&v353->status4, (int8x8_t)0x800000200LL);
              v1070.x = 0.0;
              v1070.y = 0.0;
              v1070.z = 0.0;
              v1070.w = 0.0;
              sBtlSetSummon_Unit(UserData, (s16)v346, 0, 1, v1070, 3, 0);
              v355 = wk;
              p_stock_mask = &v355->stock_mask;
              v357 = v355->summonindex[v346];
              sBtlSetBit(p_stock_mask, v357);
              wk->status4 &= ~0x200u;
            }
            goto LABEL_323;
          case 1008:
            v359 = GBWK->player->stock_id[0];
            if (v359)
            {
              v359 = GBWK->player->stock_id[0];
              v359->now->hp = v359->now->maxhp;
              v359->badstatus = 0;
            }
            goto LABEL_323;
          case 1009:
            PosReset(0, 0);
            v361 = wk;
            v362 = v361->UnitMng;
            v363 = v361->boss_eventID;
            v364 = sBtlSearchUnit_ID(v362, v363);
            sBtlStatusBitOff(v364, 0xFFBFFFFF);
            sBtlStatusBitOff(v364, 0xFFFFFFFE);
            v364->vstatus &= 0xF5FFEFFF;
            v365 = sBtlGetNakama(0);
            sBtlStatusBitOff(v365, 0xFFBFFFFF);
            sBtlStatusBitOff(v365, 0xFFFFFFEF);
            *(int8x8_t *)&v365->vstatus = vand_s8(*(int8x8_t *)&v365->vstatus, (int8x8_t)0xFFBFFFFFF5FFEFFFLL);
            v366 = sBtlGetNakama(1);
            sBtlStatusBitOff(v366, 0xFFBFFFFF);
            sBtlStatusBitOff(v366, 0xFFFFFFEF);
            *(int8x8_t *)&v366->vstatus = vand_s8(*(int8x8_t *)&v366->vstatus, (int8x8_t)0xFFBFFFFFF5FFEFFFLL);
            UserData->vstatus &= 0xF5FFEFFF;
            sBtlEventFovOff();
            goto LABEL_323;
          case 1010:
            CameraNormalPosSet();
            dds3BistaIn(0x1Eu);
            goto LABEL_323;
          case 1011:
            v368 = sBtlGetNakama(v2);
            if (v368)
            {
              v369 = v368->hstatus;
              if (v3 == 1)
                v368->hstatus = v369 | 0x400000;
              else
                v368->hstatus = v369 & 0xFFBFFFFF;
            }
            goto LABEL_323;
          case 1012:
            taiitu_power_time = 0;
            goto LABEL_323;
          case 1013:
            if (wk->cmbSkl->bRun)
              goto LABEL_323;
            if (sBtlCheckSetsuma())
              goto LABEL_323;
            if (IsSceanStop())
              goto LABEL_323;
            if (!taiitu_power_time)
              goto LABEL_1476;
            v376 = taiitu_power_time - 1;
            taiitu_power_time = v376;
            if (v376 > 0)
              goto LABEL_323;
            taiitu_power_time = 0;
            v377 = GetData();
            v378 = AI_BS_CHOOSE_POINT_SUB();
            v380 = 182;
            goto LABEL_752;
          case 1014:
            if (wk->cmbSkl->bRun)
              goto LABEL_323;
            if (sBtlCheckSetsuma())
              goto LABEL_323;
            if (IsSceanStop())
              goto LABEL_323;
            v382 = taiitu_power_time;
            if (v382)
            {
              if (!v374)
              {
                v382 = taiitu_power_time;
              }
              v383 = v382 - 1;
              taiitu_power_time = v383;
              if (v383 <= 0)
              {
                taiitu_power_time = 0;
                v377 = GetData();
                v378 = AI_BS_CHOOSE_POINT_SUB();
                v380 = 219;
LABEL_752:
                AI_SET_SUMMON_POINT_SUB(v377, v380, v378, 2, 2, 1);
              }
            }
            else
            {
LABEL_1476:
              taiitu_power_time = v2;
            }
            goto LABEL_323;
          case 1015:
            for (k = 0; ; ++k)
            {
              v386 = wk->UnitMng;
              if (k >= v386->number)
                break;
              v386 = wk->UnitMng;
              v387 = v386->pUnitL[k]->pUnit;
              if (v387)
              {
                if (sBtlCheckDamageTarget(v387) && (v387->side & 2) != 0 && v387->para->devilid == 152)
                {
                  goto LABEL_754;
                }
                if (sBtlCheckDamageTarget(v387) && (v387->side & 2) != 0 && v387->para->devilid == 219)
                {
LABEL_754:
                  v387->mode = 9;
                }
              }
            }
            goto LABEL_323;
          default:
            if (IntPara != 2000)
              goto LABEL_320;
            if (v3)
            {
              if (!v137)
              Instance = get_Instance(0);
              v139 = 0;
            }
            else
            {
              if (!v137)
              Instance = get_Instance(0);
              v139 = 1;
            }
            SpriteGageDisp(Instance, v139, 0);
            goto LABEL_323;
        }
        while (2)
        {
          stock_id = wk->stock_id;
          if (v34 < SLODWORD(stock_id->max_length))
          {
            stock_id = wk->stock_id;
            if (stock_id[v34] != v32)
            {
              ++v34;
              continue;
            }
          }
          else
          {
            LODWORD(v34) = 0;
          }
          break;
        }
        v36 = wk;
        v36->summonindex[v2] = v34;
        v36->summonindex_menu[v2] = v34;
        if (v2)
          v38 = -200.0;
        else
          v38 = 200.0;
        v40 = 0.7853982;
        nakama_pos.x = v38;
        nakama_pos.y = 0.0;
        nakama_pos.z = 0.0;
        nakama_pos.w = 1.0;
        if (v2)
        {
          v40 = -0.87266463;
          v41 = -50.0;
        }
        else
        {
          v41 = 45.0;
        }
        FromEuler(0.0, v40, 0.0);
        sub_1B335A0(&nakama_rot, 0, v42);
        nakama_mv_rotbk = v41;
        v44 = wk->summonindex[v2];
        v1067.y = 0.0;
        v1067.z = 0.0;
        v1067.w = 0.0;
        v1067.x = v38;
        sBtlSetSummon_Unit(UserData, v44, 0x400000u, 1, v1067, 3, 0);
        v45 = wk;
        v46 = &v45->stock_mask;
        v47 = v45->summonindex[v2];
        sBtlSetBit(v46, v47);
        goto LABEL_323;
    }
    v621 = wk;
    v323 = 1;
    switch (v621->scrLoadStat)
    {
      case 0:
        v622 = v621->effList;
        if (sBtlSearchEffect_SAB(v622, 238, 1u))
          goto LABEL_2188;
        v925 = wk->effList;
        if (sBtlSearchEffect_SAB(v925, 238, 2u))
          goto LABEL_2188;
        v938 = wk->effList;
        if (sBtlSearchEffect_SAB(v938, 238, 5u))
          goto LABEL_2188;
        v959 = 238;
        goto LABEL_2192;
      case 1:
        v866 = v621->effList;
        if (sBtlSearchEffect_SAB(v866, 239, 1u))
          goto LABEL_2188;
        v919 = wk->effList;
        if (sBtlSearchEffect_SAB(v919, 239, 2u))
          goto LABEL_2188;
        v935 = wk->effList;
        if (sBtlSearchEffect_SAB(v935, 239, 5u))
          goto LABEL_2188;
        v959 = 239;
LABEL_2192:
        sBtlForceDelete_EffectWork_ID(v959, 1);
LABEL_2193:
        v323 = 0;
        v834 = wk;
LABEL_2196:
        v835 = v834->scrLoadStat + 1;
        goto LABEL_2197;
      case 2:
        if (CheckLoadData(0))
          goto LABEL_2188;
        v323 = 0;
        v834 = wk;
        v834->status2 |= 0x200u;
        goto LABEL_2196;
      case 3:
        if (!sBtlLoadEffectData_ID(75))
          goto LABEL_2188;
        sBtlLoadEffectData_ID(76);
        goto LABEL_2193;
      case 4:
        if (sBtlLoadEffectData_ID(76))
          goto LABEL_2193;
        goto LABEL_2188;
      case 5:
        if (!sBtlLoadEffectData_ID(77))
          goto LABEL_2188;
        v872 = wk;
        status2 = v872->status2;
        ++v872->scrLoadStat;
        v872->status2 = status2 & 0xFFFFFDFF;
        goto LABEL_2198;
      case 6:
        goto LABEL_2198;
      default:
        goto LABEL_2188;
    }
  }
  if ((u32)IntPara <= 0xC418)
  {
    if ((u32)IntPara > 0xC364)
    {
      switch (IntPara)
      {
        case 50030:
          sBtlPlayerResetPlayerPosRot_Start_Boss(1);
          sBtlSetMove(g_CamMov_BS_LASTB3_0, 1);
          v18 = 10.0;
          v19 = 1.0;
          v20 = 30.0;
          goto LABEL_217;
        case 50031:
          g_CamMov_BS_LASTB3_1_local = g_CamMov_BS_LASTB3_1;
          goto LABEL_186;
        case 50032:
          sBtlSetMove(g_CamMov_BS_LASTB3_1B, 0);
          sBtlSetMode(13);
          Proc(0);
          v64 = wk;
          v65 = v64->UnitMng;
          v66 = v64->playerID;
          v67 = sBtlSearchUnit_ID(v65, v66);
          sBtlStatusBitOn(v67, 0x10u);
          goto LABEL_323;
        case 50033:
          sBtlEventFovOff();
          sBtlEventUpVOff();
          sBtlClearTgt();
          v69 = wk;
          v70 = v69->UnitMng;
          v71 = v69->playerID;
          v72 = sBtlSearchUnit_ID(v70, v71);
          sBtlStatusBitOff(v72, 0xFFFFFFEF);
          goto LABEL_323;
        case 50034:
        case 50035:
        case 50036:
        case 50037:
        case 50038:
        case 50039:
        case 50043:
        case 50044:
        case 50045:
        case 50046:
        case 50047:
        case 50048:
        case 50049:
        case 50050:
        case 50051:
        case 50052:
        case 50053:
        case 50054:
        case 50055:
        case 50056:
        case 50057:
        case 50058:
        case 50059:
        case 50060:
        case 50061:
        case 50062:
        case 50063:
        case 50064:
        case 50065:
        case 50066:
        case 50067:
        case 50068:
        case 50069:
        case 50070:
        case 50071:
        case 50072:
        case 50073:
        case 50074:
        case 50075:
        case 50076:
        case 50077:
        case 50078:
        case 50079:
        case 50080:
        case 50081:
        case 50082:
        case 50083:
        case 50084:
        case 50085:
        case 50086:
        case 50087:
        case 50088:
        case 50089:
        case 50090:
        case 50091:
        case 50092:
        case 50093:
        case 50094:
        case 50095:
        case 50096:
        case 50097:
        case 50098:
        case 50099:
          goto LABEL_320;
        case 50040:
          SetAction(19);
          sBtlPlayerResetPlayerPosRot_Start_Boss(2);
          sBtlSetMove(g_CamMov_BS_LASTB3_2, 1);
          sBtlSetMode(13);
          Proc(0);
          v76 = wk;
          v77 = v76->UnitMng;
          v78 = v76->playerID;
          v79 = sBtlSearchUnit_ID(v77, v78);
          sBtlStatusBitOn(v79, 0x4010u);
          v79->status |= 1u;
          MOON_OUT();
          goto LABEL_323;
        case 50041:
          g_CamMov_BS_LASTB3_1_local = g_CamMov_BS_LASTB3_3;
LABEL_186:
          sBtlSetMove(g_CamMov_BS_LASTB3_1_local, 0);
          goto LABEL_218;
        case 50042:
          goto LABEL_323;
        case 50100:
          if (v2 < 1)
            goto LABEL_323;
          LODWORD(v12) = scrGetCommandTimer() >= v2;
          return (s32)v12;
        default:
          if (IntPara != 50200)
            goto LABEL_320;
          if (v4 && (v4->side & 2) != 0 && (v4->status & 0x4000000) == 0 && (v4->vstatus & 0x10000) == 0)
          {
            if (sBtlCheckDamageTarget(v4))
            {
              color = v4->color;
              v4->ditherAlpha = 1;
              v4->dissolveAlpha = 1.0;
              v4->color = color | 0xFF000000;
              v4->vstatus &= 0xFFFFFFFC;
            }
          }
          goto LABEL_323;
      }
    }
    switch (IntPara)
    {
      case 50000:
        v4->actaiwk->mahaskl_waitframe = 100;
        goto LABEL_323;
      case 50001:
        v4->actaiwk->mahaskl_waitframe = 0;
        goto LABEL_323;
      case 50002:
        v83 = wk;
        v84 = v83->UnitMng;
        v85 = v83->playerID;
        v86 = sBtlSearchUnit_ID(v84, v85);
        sBtlResetAction(v86);
        v86->vstatus &= ~0x1000u;
        v86->next_motion_not_hokan = 1;
        *(__n128 *)&v87 = sub_1B332C0(0, 0.0, 0.0, 565.0, 0.0);
        sub_1B335A0(&v86->pos, 0, v87);
        FromEuler(0.0, 3.1415927, 0.0);
        *(__n128 *)&v89 = sub_1B335A0(&v86->rot, 0, v88);
        sub_1B335A0(&v86->rotbk, 0, v89);
        v90 = v86->pos.x;
        v91 = v86->pos.y;
        v93 = v86->pos.z;
        v92 = v86->pos.w;
        v1068.x = v90;
        v1068.y = v91;
        v1068.z = v93;
        v1068.w = v92;
        dds3SetPosPoseSet(&v86->pBasic, v1068);
        dds3SetRotPoseSet(&v86->pBasic, v86->rot);
        sBtlSetMotion(v86, 0, 0, 0, 0);
        sBtlStatusBitOn(v86, 0x10u);
        if (v4)
        {
          *(__n128 *)&v94 = sub_1B332C0(0, 0.0, 0.0, 800.0, 0.0);
          sub_1B335A0(&v4->pos, 0, v94);
          FromEuler(0.0, 0.0, 0.0);
          *(__n128 *)&v96 = sub_1B335A0(&v4->rot, 0, v95);
          sub_1B335A0(&v4->rotbk, 0, v96);
          v97 = v4->pos.x;
          v98 = v4->pos.y;
          v99 = v4->pos.z;
          v100 = v4->pos.w;
          v1069.x = v97;
          v1069.y = v98;
          v1069.z = v99;
          v1069.w = v100;
          dds3SetPosPoseSet(&v4->pBasic, v1069);
          dds3SetRotPoseSet(&v4->pBasic, v4->rot);
        }
        v102 = wk;
        v102->boss_eventID = v4->ListID;
        sBtlSetMove(g_CamMov_KayaDead0, 1);
        v18 = 1.0;
        v19 = 0.5;
        v20 = 42.0;
LABEL_217:
        sBtlSetDof2Bokah(v18, v19, v20, 4.0, v19, v20, 4.0);
LABEL_218:
        sBtlSetMode(13);
        Proc(0);
        goto LABEL_323;
      case 50003:
        sBtlSetMove(g_CamMov_KayaDead1, 1);
        sBtlSetDof2Bokah(120.0, 0.5, 42.0, 4.0, 2.0, 42.0, 4.0);
        sBtlSetMode(13);
        Proc(0);
        goto LABEL_323;
      case 50004:
        Add_Pur();
        sBtlPlaySE(0x7740000u);
        v108 = wk;
        v109 = v108->UnitMng;
        v110 = v108->playerID;
        v111 = sBtlSearchUnit_ID(v109, v110)->para;
        v111->badstatus &= ~0x10000u;
        sBtlKudaHuuin_AllOff();
        goto LABEL_323;
      case 50005:
        sBtlClearDof2Bokah();
        sBtlNoHokan();
        sBtlSetMode(2);
        v114 = wk;
        v115 = v114->UnitMng;
        v116 = v114->playerID;
        sBtlSearchUnit_ID(v115, v116);
        goto LABEL_323;
      case 50006:
      case 50007:
      case 50008:
      case 50009:
      case 50011:
      case 50012:
      case 50013:
      case 50014:
      case 50015:
      case 50016:
      case 50017:
      case 50018:
      case 50019:
        goto LABEL_320;
      case 50010:
        (loc_2118A60)((u32)v2, 0);
        goto LABEL_323;
      case 50020:
        goto LABEL_1225;
      default:
        if (IntPara != 41000)
          goto LABEL_320;
        if (wk->encountno == 43)
          v57 = 262;
        else
          v57 = 300;
        v58 = sBtlSearchDeivl(v57)->aiwk;
        scrStep2 = v58->scrStep2;
        goto LABEL_130;
    }
  }
  if ((u32)IntPara <= 0x11170)
  {
    if (IntPara != 60000)
    {
      if (IntPara == 60001)
      {
        v50 = sub_1905740(v2, 0);
        v51 = v50 + 1;
        goto LABEL_131;
      }
      if (IntPara == 70000)
      {
        if (v2)
        {
          wk->effNoStop2 = 1;
        }
        else
        {
          wk->effNoStop2 = 0;
        }
        goto LABEL_323;
      }
      goto LABEL_320;
    }
    goto LABEL_323;
  }
  if (IntPara == 80000)
  {
    if (v4->actwk->use_skillid != v2)
    {
      v48 = v4->aiwk;
      v49 = v48->scrflag;
      if ((v49 & 0x400) != 0)
        v48->scrflag = v49 & 0xFFFFFBFF;
    }
    goto LABEL_323;
  }
  if (IntPara == 90000)
  {
    switch (v2)
    {
      case 2:
        tutorialFlag = 0;
        break;
      case 1:
        wk->tuto_r2_di = 0;
        break;
      case 0:
        if (IsSceanStop())
          goto LABEL_293;
        break;
    }
    goto LABEL_323;
  }
  if (IntPara != 95000)
  {
LABEL_320:
    data = IntPara;
    v140 = Box(s32, &data);
    LogError(v140, 0);
    goto LABEL_323;
  }
  v10 = sBtlGetNakama(0);
  if (v10)
  {
    v11 = v10->actwk;
    if (v11 && v11->status == 40 && v11->use_skillid == 240)
      goto LABEL_293;
    v10->hstatus &= ~0x800u;
  }
  LODWORD(v12) = 1;
  v13 = sBtlGetNakama(1);
  if (v13)
  {
    v14 = v13->actwk;
    if (!v14 || v14->status != 40 || v14->use_skillid != 240)
    {
      v13->hstatus &= ~0x800u;
      return (s32)v12;
    }
LABEL_293:
    LODWORD(v12) = 0;
  }
  return (s32)v12;
}

// 0x20fbd20
s32 sBtlSupport_AI_CHK_CHKSKL_R(SBTLUNIT_WORK *wk, s32 arg) {
  s32 v5;
  s32 v6;

  v5 = arg & 0xF000;
  if ((arg & 0xF000) != 0)
  {
    if (v5 == 0x4000)
    {
      v6 = 0;
      while (1)
      {
        if ((sBtlGetSkilltbl(v6)->flg & arg) != 0)
        {
          if (sBtlCheckChkskl(wk, v6))
            break;
        }
        if (++v6 == 1600)
          return 0;
      }
      goto LABEL_22;
    }
    if (v5 == 0x8000)
    {
      v6 = 0;
      while (1)
      {
        if ((sBtlGetSkilltbl(v6)->attr & arg) != 0)
        {
          if (sBtlCheckChkskl(wk, v6))
            break;
        }
        if (++v6 == 1600)
          return 0;
      }
      goto LABEL_22;
    }
    return 0;
  }
  v6 = arg & 0xFFF;
  if (!sBtlCheckChkskl(wk, v6))
    return 0;
LABEL_22:
  sBtlResetChkskl(wk, v6);
  return 1;
}

// 0x20fc8d0
static s32 SBTL_SET_SCRIPT_Sub(s32 evtload_evtno, s32 eventno, s32 theworld, s32 scenestop) {
  s16 v7;
  SBTLUNIT_WORK *Data;
  s32 ListID;
  SBTLACTION_WORK *actwk;
  u32 status;

  v7 = eventno;
  Data = GetData();
  ListID = Data->ListID;
  actwk = Data->actwk;
  actwk->total_homing = 0.0;
  actwk->no_homing = 0;
  wk->evtload_evtno = evtload_evtno;
  status = wk->status;
  wk->eventno = v7;
  wk->eventTheworld = theworld;
  wk->eventSceneStop = scenestop;
  wk->eventgstat = 0;
  wk->eventListID = ListID;
  wk->status = status | 0x400;
  actwk->framecnt = 0;
  actwk->framecntB = 0;
  return 1;
}

// 0x2100490
static void sBtlScriptSub_ResetBadStatus(SBTLUNIT_WORK *wk) {
  sdatUnitWork_t *para;
  u32 BadStatus;
  char v6;
  u32 status;

  para = wk->para;
  BadStatus = sBtlGetBadStatus(para);
  if (BadStatus == 22)
    return;
  v6 = BadStatus;
  sBtlResetBadStatus(wk, 1 << v6);
  sBtlRestartMotion(wk);
  status = wk->status;
  wk->getMag = 0;
  wk->status = status & 0xFFFFFFDF;
  wk->hstatus &= ~0x10u;
  if (wk->actwk->status == 9)
  {
    sBtlSetAction(wk, 1, 0);
  }
}

// 0x2102310
static void Support_SetPosInit(void) {
  SBTLUNIT_WORK *UserData;
  SBTLUNIT_WORK *v2;
  SB_ENCOUNTPAC *EncountPac;
  s16 start_playerpos;
  f32 v6;
  sdfVector4_t *p_rot;
  s32 v9;
  sdfVector4_t *p_rot_p;
  s32 v12;
  struct sdfVector4_t pos;
  dds3ModelHandle_t *hModel;
  struct sdfVector4_t v17;
  SBTLUNIT_WORK *NakamaData;
  f32 v21;
  f32 v22;
  SBTLUNIT_WORK *v23;
  s64 v24;
  f32 v25;
  f32 v26;
  s32 v27;
  sdfVector4_t *v29;
  s32 v30;
  sdfVector4_t *v31;
  struct sdfVector4_t v32;
  s32 v33;
  struct sdfVector4_t v34;
  dds3ModelHandle_t *v37;
  struct sdfVector4_t v38;
  SBTLUNIT_WORK *v40;
  f32 v41;
  f32 v42;
  SBTLUNIT_WORK *v43;
  s64 v44;
  f32 v45;
  f32 v46;
  s32 v47;
  sdfVector4_t *v49;
  s32 v50;
  sdfVector4_t *v51;
  struct sdfVector4_t v52;
  s32 v53;
  struct sdfVector4_t v54;
  dds3ModelHandle_t *v57;
  struct sdfVector4_t v58;
  s32 v60;
  struct sdfVector4_t v61;
  struct sdfVector4_t v62;
  struct sdfVector4_t v65;
  struct sdfVector4_t v66;
  struct sdfVector4_t v69;
  struct sdfVector4_t v70;
  s64 r;
  f32 y;
  f32 x;

  x = 0.0;
  y = 0.0;
  r = 0;
  UserData = Support_GetUserData();
  if (UserData)
  {
    v2 = UserData;
    EncountPac = sBtlGetEncountPac(-1);
    start_playerpos = EncountPac[wk->encountno]->start_playerpos;
    mapEncPointGet(start_playerpos, &x, &y, (f32 *)&r + 1, &r);
    v6 = y;
    v2->pos.x = x;
    v2->pos.y = v6;
    v2->pos.z = *((f32 *)&r + 1);
    FromEuler(0.0, *(f32 *)&r * 0.017453292, 0.0);
    p_rot = &v2->rot;
    v9 = (u8)byte_5755EF5;
    *p_rot = vct_A;
    if (v9)
      goto LABEL_14;
    goto LABEL_35;
    if (v27)
    {
LABEL_14:
      goto LABEL_15;
    }
LABEL_35:
LABEL_15:
    vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
    p_rot_p = &v2->rot_p;
    v12 = (u8)byte_5755EF5;
    LODWORD(v2->mv_rotbk) = r;
    pos = v2->pos;
    *p_rot_p = vct_A;
    if (v12)
    {
      goto LABEL_19;
    }
    else
    {
      v61 = pos;
      pos = v61;
LABEL_19:
      vct_A = pos;
      hModel = v2->hModel;
      goto LABEL_20;
    }
    v62 = pos;
    vct_A = v62;
    hModel = v2->hModel;
LABEL_20:
    mdlSetPosition(hModel);
    v17 = *p_rot;
    vct_A = v17;
    mdlSetRotate(v2->hModel);
    sBtlResetAction(v2);
    sBtlSetAction(v2, 1, 0);
    goto LABEL_25;
  }
LABEL_25:
  NakamaData = Support_GetNakamaData(1);
  if (!NakamaData)
    goto LABEL_65;
  v21 = y;
  v22 = x;
  v23 = NakamaData;
  NakamaData->pos.x = x;
  NakamaData->pos.y = v21;
  v24 = r;
  NakamaData->pos.z = *((f32 *)&r + 1);
  if (*(f32 *)&v24 <= -45.0 || *(f32 *)&v24 >= 45.0)
  {
    if (*(f32 *)&v24 >= -45.0 || *(f32 *)&v24 <= -135.0)
    {
      if (*(f32 *)&v24 <= 45.0 || *(f32 *)&v24 >= 135.0)
      {
        v25 = 200.0;
        goto LABEL_51;
      }
      v26 = 200.0;
    }
    else
    {
      v26 = -200.0;
    }
    NakamaData->pos.z = *((f32 *)&v24 + 1) + v26;
    goto LABEL_52;
  }
  v25 = -200.0;
LABEL_51:
  NakamaData->pos.x = v22 + v25;
LABEL_52:
  FromEuler(0.0, *(f32 *)&v24 * 0.017453292, 0.0);
  v29 = &v23->rot;
  v30 = (u8)byte_5755EF5;
  *v29 = vct_A;
  if (v30)
    goto LABEL_56;
  goto LABEL_75;
  if (v47)
  {
LABEL_56:
    goto LABEL_57;
  }
LABEL_75:
LABEL_57:
  vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
  v31 = &v23->rot_p;
  v32 = vct_A;
  v33 = (u8)byte_5755EF5;
  LODWORD(v23->mv_rotbk) = r;
  v34 = v23->pos;
  *v31 = v32;
  if (v33)
  {
    goto LABEL_61;
  }
  else
  {
    v65 = v34;
    v34 = v65;
LABEL_61:
    vct_A = v34;
    v37 = v23->hModel;
    goto LABEL_62;
  }
  v66 = v34;
  vct_A = v66;
  v37 = v23->hModel;
LABEL_62:
  mdlSetPosition(v37);
  v38 = *v29;
  vct_A = v38;
  mdlSetRotate(v23->hModel);
LABEL_65:
  v40 = Support_GetNakamaData(0);
  if (!v40)
    return;
  v41 = y;
  v42 = x;
  v43 = v40;
  v40->pos.x = x;
  v40->pos.y = v41;
  v44 = r;
  v40->pos.z = *((f32 *)&r + 1);
  if (*(f32 *)&v44 <= -45.0 || *(f32 *)&v44 >= 45.0)
  {
    if (*(f32 *)&v44 >= -45.0 || *(f32 *)&v44 <= -135.0)
    {
      if (*(f32 *)&v44 <= 45.0 || *(f32 *)&v44 >= 135.0)
      {
        v45 = -200.0;
        goto LABEL_89;
      }
      v46 = -200.0;
    }
    else
    {
      v46 = 200.0;
    }
    v40->pos.z = *((f32 *)&v44 + 1) + v46;
    goto LABEL_90;
  }
  v45 = 200.0;
LABEL_89:
  v40->pos.x = v42 + v45;
LABEL_90:
  FromEuler(0.0, *(f32 *)&v44 * 0.017453292, 0.0);
  v49 = &v43->rot;
  v50 = (u8)byte_5755EF5;
  *v49 = vct_A;
  if (v50)
    goto LABEL_94;
  goto LABEL_107;
  if (v60)
  {
LABEL_94:
    goto LABEL_95;
  }
LABEL_107:
LABEL_95:
  vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
  v51 = &v43->rot_p;
  v52 = vct_A;
  v53 = (u8)byte_5755EF5;
  LODWORD(v43->mv_rotbk) = r;
  v54 = v43->pos;
  *v51 = v52;
  if (v53)
  {
    goto LABEL_99;
  }
  else
  {
    v69 = v54;
    v54 = v69;
LABEL_99:
    vct_A = v54;
    v57 = v43->hModel;
    goto LABEL_100;
  }
  v70 = v54;
  vct_A = v70;
  v57 = v43->hModel;
LABEL_100:
  mdlSetPosition(v57);
  v58 = *v49;
  vct_A = v58;
  mdlSetRotate(v43->hModel);
}

// 0x2102d60
static void Support_SetPos(SBTLUNIT_WORK *wk, s32 pointID) {
  sdfVector4_t *p_rot;
  dds3ModelHandle_t *hModel;
  struct sdfVector4_t v10;
  struct sdfVector4_t pos;

  p_rot = &wk->rot;
  sBtlGetPointData(pointID, &wk->pos, &wk->rot);
  pos = wk->pos;
  vct_A = pos;
  hModel = wk->hModel;
  mdlSetPosition(wk->hModel);
  v10 = *p_rot;
  vct_A = v10;
  mdlSetRotate(wk->hModel);
}

// 0x2108980
static s32 sBtlIncNodeColor(sdfModelNode_t *pNode, u32 DstColor, u32 IncColor, u32 Mode) {
  Il2CppObject *Component_object;
  int8x8_t v10;
  int8x8_t v11;
  f32 v12;
  f32 v13;
  f32 v14;
  uint32x2_t v15;
  f32 v16;
  f32 v17;
  int8x8_t v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  float32x2_t v23;
  float32x2_t v24;
  int8x8_t v25;
  int8x8_t v26;
  int32x2_t v27;
  int32x2_t v28;
  int8x8_t v29;
  int8x8_t v30;
  s32 v31;
  u32 v32;
  _BOOL4 v33;
  u32 v34;
  s32 v35;
  bool v36;
  u32 v37;
  s32 v38;
  u32 v39;

  Component_object = GetComponent_object_(pNode);
  if (!op_Inequality(Component_object, 0, 0))
    return 0;
  v10.n64_u32[0] = DstColor;
  v11.n64_u32[0] = IncColor;
  v10.n64_u32[1] = DstColor >> 8;
  v12 = (f32)BYTE2(DstColor) * 0.0078125;
  v13 = (f32)HIBYTE(DstColor) * 0.0078125;
  v14 = (f32)BYTE2(IncColor) * 0.0078125;
  v11.n64_u32[1] = IncColor >> 8;
  v15.n64_u64[0] = vand_s8(v11, (int8x8_t)0xFF000000FFLL).n64_u64[0];
  v16 = (f32)HIBYTE(IncColor) * 0.0078125;
  v11.n64_u32[0] = HIDWORD(Component_object[4].klass);
  v17 = *(f32 *)&Component_object[4].monitor;
  v18.n64_u64[0] = vmul_f32(vcvt_f32_u32(vand_s8(v10, (int8x8_t)0xFF000000FFLL)), (float32x2_t)0x3C0000003C000000LL).n64_u64[0];
  v19 = v11.n64_f32[0] - v14;
  v20 = v14 + v11.n64_f32[0];
  v21 = v17 - v16;
  v22 = v16 + v17;
  v23.n64_u64[0] = vmul_f32(vcvt_f32_u32(v15), (float32x2_t)0x3C0000003C000000LL).n64_u64[0];
  v24.n64_u64[0] = *(u64 *)((char *)&Component_object[3].monitor + 4);
  v25.n64_u64[0] = vsub_f32(v24, v23).n64_u64[0];
  v26.n64_u64[0] = vadd_f32(v23, v24).n64_u64[0];
  v27.n64_u64[0] = vcgt_f32(v18, v25).n64_u64[0];
  v28.n64_u64[0] = vcgt_f32(v26, v18).n64_u64[0];
  v29.n64_u64[0] = vbsl_s8(v27, v18, v25).n64_u64[0];
  v30.n64_u64[0] = vbsl_s8(v28, v18, v26).n64_u64[0];
  if ((v27.n64_u8[0] & 1) != 0)
    v31 = 3;
  else
    v31 = 4;
  v32 = v31 + v27.n64_u32[1];
  v33 = v19 < v12;
  if (v19 < v12)
    v19 = (f32)BYTE2(DstColor) * 0.0078125;
  v34 = v32 - v33;
  if (v21 < v13)
  {
    --v34;
    v21 = (f32)HIBYTE(DstColor) * 0.0078125;
  }
  if ((v28.n64_u8[0] & 1) != 0)
    v35 = 3;
  else
    v35 = 4;
  v36 = v20 <= v12;
  if (v20 > v12)
    v20 = (f32)BYTE2(DstColor) * 0.0078125;
  v37 = v35 + v28.n64_u32[1];
  v38 = !v36;
  v39 = v37 - v38;
  if (v22 > v13)
    --v39;
  else
    v13 = v22;
  if (Mode)
  {
    v30.n64_u64[0] = v29.n64_u64[0];
    v20 = v19;
  }
  else
  {
    v34 = v39;
  }
  LOBYTE(Component_object[3].monitor) = 1;
  if (Mode)
    v13 = v21;
  *(f64 *)((char *)&Component_object[3].monitor + 4) = v30.n64_f64[0];
  *((f32 *)&Component_object[4].klass + 1) = v20;
  *(f32 *)&Component_object[4].monitor = v13;
  return v34 == 0;
}

// 0x2108bc0
static s32 sBtlIncNodeColorFromName(dds3ModelHandle_t *hModel, char *pNodeName, u32 DstColor, u32 IncColor, u32 Mode) {
  sdfModelRootNode_t *modelRoot;
  s32 NodeIndexByName;
  sdfModelNode_t *v14;

  modelRoot = hModel->modelRoot;
  NodeIndexByName = sdfModelGetNodeIndexByName(modelRoot, pNodeName);
  if (NodeIndexByName == -1)
    return 1;
  v14 = modelRoot->nodeList->items[NodeIndexByName];
  return sBtlIncNodeColor(v14, DstColor, IncColor, Mode);
}

// 0x210adf0
s32 sBtlSBTL_SET_MoveSpdMul(void) {
  s32 IntPara;
  s32 v2;
  s32 v3;
  SBTLUNIT_WORK *NakamaData;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  switch (IntPara)
  {
    case -4:
      v3 = 1;
      goto LABEL_11;
    case -3:
      v3 = 0;
LABEL_11:
      NakamaData = Support_GetNakamaData(v3);
      break;
    case -2:
      NakamaData = Support_GetUserData();
      break;
    case -1:
      NakamaData = GetData();
      break;
    default:
      NakamaData = wk->scrUnitList[IntPara];
      break;
  }
  NakamaData->moveSpdMul = (f32)v2;
  return 1;
}

// 0x2117060
static s32 BS14_TargetSet(SBTLUNIT_WORK *wk, const sdfVector4_t *pos, f32 _SizeR, f32 _Life, s32 _Wait) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  s32 v14;
  f32 v17;
  f32 v18;
  f32 v19;
  unsigned __int128 v21;
  sdfVector4_t posa;
  sdfVector4_t v23;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  v23.x = x;
  v23.y = y;
  v23.z = z;
  v23.w = w;
  v14 = sBtlGetNearPosHD(wk, v23);
  *(u64 *)&posa.x = 0;
  *(u64 *)&posa.z = 0;
  sklid_BS14_target = v14;
  v21 = 0u;
  sBtlGetPointData(v14, &posa, &v21);
  Add(posa, SizeR, Life, Wait, 0);
  v17 = posa.x;
  v18 = posa.y;
  v19 = posa.z;
  AW_XAtkSetHomingPos(v17, v18, v19);
  return v14;
}

// 0x21171d0
s32 sBtlBS14_TargetGet(void) {
  return sklid_BS14_target;
}

// 0x2116d00
static void BS14_CHOUSIN_TargetSet(SBTLUNIT_WORK *wk) {
  SBTLUNIT_WORK *UserData;
  SBTLUNIT_WORK *NakamaData;
  SBTLUNIT_WORK *v5;
  u32 PointNums;
  s32 *v11;
  s32 *v14;
  s32 *v16;
  s32 *v17;
  s64 v18;
  s32 *v20;
  u32 v21;
  s32 v23;
  f32 x;
  f32 y;
  f32 z;
  s32 *v27;
  s32 *v28;
  unsigned __int128 v29;
  sdfVector4_t pos;

  *(u64 *)&pos.x = 0;
  *(u64 *)&pos.z = 0;
  v29 = 0u;
  UserData = Support_GetUserData();
  NakamaData = Support_GetNakamaData(0);
  v5 = Support_GetNakamaData(1);
  PointNums = mapEncGetPointNums();
  BS14_CHOUSIN_pos[0] = sBtlGetNearPosHD(wk, UserData->pos);
  if (NakamaData)
  {
    v11 = BS14_CHOUSIN_pos;
    v11[1] = sBtlGetNearPosHD(wk, NakamaData->pos);
    if (v5)
      goto LABEL_10;
  }
  else
  {
    v27 = BS14_CHOUSIN_pos;
    v27[1] = sub_1905740(PointNums, 0);
    if (v5)
    {
LABEL_10:
      v14 = BS14_CHOUSIN_pos;
      v14[2] = sBtlGetNearPosHD(wk, v5->pos);
      goto LABEL_14;
    }
  }
  v28 = BS14_CHOUSIN_pos;
  v28[2] = sub_1905740(PointNums, 0);
LABEL_14:
  v16 = BS14_CHOUSIN_pos;
  v16[3] = sub_1905740(PointNums, 0);
  v17 = BS14_CHOUSIN_pos;
  v18 = 0;
  v17[4] = sub_1905740(PointNums, 0);
  while (1)
  {
    v20 = BS14_CHOUSIN_pos;
    if (v18 >= SLODWORD(v20->max_length))
      break;
    *(u64 *)&pos.x = 0;
    *(u64 *)&pos.z = 0;
    v29 = 0u;
    if (v21)
    {
      v23 = v20[v18];
      goto LABEL_21;
    }
    else
    {
      v23 = BS14_CHOUSIN_pos[v18];
      goto LABEL_21;
    }
LABEL_21:
    sBtlGetPointData(v23, &pos, &v29);
    Add(pos, 150.0, 240.0, 0, 0);
    x = pos.x;
    y = pos.y;
    z = pos.z;
    AW_XAtkSetHomingPos(x, y, z);
    ++v18;
  }
}

// 0x2117250
s32 sBtlBS14_CHOUSIN_TargetGet(s32 step3) {
  return BS14_CHOUSIN_pos[step3];
}
