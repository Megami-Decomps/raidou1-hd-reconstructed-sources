#include "types.h"
#include "SBTLDVLTK_MODE.h"
#include "dat.h"
#include "dds3kernelcore.h"
#include "evtbit.h"
#include "itf.h"
#include "kernel.h"
#include "localize.h"
#include "mdl.h"
#include "raijindlc.h"
#include "sbattle.h"
#include "sbtl.h"
#include "sbtlbossevent.h"
#include "sbtlcalc.h"
#include "sbtldvltk.h"
#include "sbtlmain.h"
#include "sbtlplayer.h"
#include "sbtlsound.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "scr.h"
#include "smnr.h"
#include "sndmanager.h"
#include "wordwrap.h"

#define SBTLDVLTK_OFFSETX 386
#define SBTLDVLTK_OFFSETY 322
#define DVLTK_STAT_NONE 0
#define DVLTK_STAT_SETPARAM 1
#define DVLTK_STAT_ENDREQ 2
#define DVLTK_STAT_END 4
#define DVLTK_STAT_LOADEND 8
#define DVLTK_SPRSTAT_SPR_LOAD 1
#define DVLTK_CONV_NARUMI 208
#define DVLTK_CONV_AIBOU 209
#define DVLTK_ARRAY_MAX 5
#define SBTL_DVLTK_CALC_PROC_NAME "dvltkCalc"
#define SBTL_DVLTK_DRAW_PROC_NAME "dvltkDraw"
#define GUN_TIME 60
#define GUN_RAND 3

typedef struct SBTLDVLTK_LISTWORK SBTLDVLTK_LISTWORK;
typedef struct SBTLDVLTK_WORK SBTLDVLTK_WORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct sprHandle_t sprHandle_t;

char *sbtldvltk_filetbl;
char *devil_face_dummy;
char *devil_image_none;
char *devil_img_btl_none;
char *devil_img_goh_none;
s32 *sbtldvltk_index00;
dds3ProcessID_t *GlobalPID;
SBTLDVLTK_LISTWORK *pGlobalLWK;
SBTLUNIT_WORK *GlobalUnitWK;
u32 *GlobalStat;
s32 GlobalCurrentArray;
sprHandle_t *GlobalSpr;
u32 GlobalSprStat;
u8 **pGlobalMsg;
static s32 *GlobalMsgSize;
s32 g_strlen;
char *dvltkAseetName;
char *dvlFaceAssetName;
char *dvlIconAssetName;
char *dvlBtlIconAssetName;
static s32 gun_talk_time;
static s32 zouen_talk_time;
static char *playing_voice;
static char **gouto_hitokoto;

static void LoadLocalizeText(void);
static bool SpecifiedGoutoMessage(SBTLDVLTK_MODE mode);
static bool IsStartNakamaCutIn(void);
static void CloseWin(void);
static char *GetDrawText(u32 rgba, SBTLUNIT_WORK *wk, SBTLDVLTK_MODE mode, SBTLDVLTK_WORK *_dwk);
static s32 DeadTextLogGet(s32 _num);

// 0x1f38cb0
char *sBtlGetFaceTexName(s32 id) {
  u32 v3;
  _BOOL4 v4;
  s32 v6;
  Il2CppObject *v7;
  s32 data;

  v3 = id & 0xFFFFFFFE;
  if (id)
  {
    if (id < 80)
      goto LABEL_11;
    if ((u32)(id - 401) > 0xFFFFFFBF)
      goto LABEL_11;
    v4 = (u32)(id - 496) < 6;
    if (v3 == 208)
      goto LABEL_11;
  }
  else
  {
    v4 = 0;
  }
  if (!v4)
    return 0;
LABEL_11:
  if (v3 != 208)
  {
    id = mdlGetDevilModelNo(id);
  }
  if ((id & 0xF000) == 0x2000)
    v6 = id - 0x2000;
  else
    v6 = id;
  data = v6;
  v7 = Box(s32, &data);
  return Format("devil_face_{0:X3}", v7, 0);
}

// 0x1f38de0
char *sBtlGetIconTexName(s32 id) {
  Il2CppObject *v3;
  s32 *v6;
  DEVILDATA_WORK *DevilFormat;
  s32 DevilModelNo;
  Il2CppObject *v9;
  s32 v10;
  s32 v11;
  s32 data;

  if (id == 2748)
  {
    data = 2748;
    v3 = Box(s32, &data);
    return Format("devil_image_{0:x3}", v3, 0);
  }
  if (id > 207)
  {
    if ((u32)(id - 208) >= 2)
    {
      if (id == 256)
      {
        v6 = &v11;
        v11 = 256;
LABEL_31:
        v9 = Box(s32, v6);
        return Format("devil_image_{0:X3}", v9, 0);
      }
      goto LABEL_11;
    }
LABEL_30:
    v6 = &v10;
    v10 = id;
    goto LABEL_31;
  }
  if (id == -1)
    goto LABEL_32;
  if (!id)
    goto LABEL_30;
LABEL_11:
  if (id >= 80 && (u32)(id - 337) >= 0x40 && (u32)(id - 496) > 5)
  {
    DevilFormat = datGetDevilFormat(id);
    if (DevilFormat && DevilFormat->huumaID)
      id = DevilFormat->huumaID;
    id = mdlGetDevilModelNo(id);
    goto LABEL_30;
  }
  if (DlcDevilSelCheck(id))
  {
    DevilModelNo = mdlGetDevilModelNo(id);
    if ((DevilModelNo & 0xF000) == 0x2000)
      id = DevilModelNo - 0x2000;
    else
      id = DevilModelNo;
    goto LABEL_30;
  }
LABEL_32:
  return devil_image_none;
}

// 0x1f39050
char *sBtlGetBtlIconTexName(s32 id) {
  s32 v5;
  Il2CppObject *v6;
  s32 data;

  if ((u32)(id - 208) >= 2 && id)
  {
    if (id == -1)
    {
      return devil_img_btl_none;
    }
    if (id >= 80 && (u32)(id - 337) >= 0x40 && (u32)(id - 496) > 5)
      return 0;
    id = mdlGetDevilModelNo(id);
  }
  if ((id & 0xF000) == 0x2000)
    v5 = id - 0x2000;
  else
    v5 = id;
  data = v5;
  v6 = Box(s32, &data);
  return Format("devil_img_btl_{0:X3}", v6, 0);
}

// 0x1f391a0
char *sBtlGetGohIconTexName(s32 id) {
  s32 DevilModelNo;
  s32 v5;
  Il2CppObject *v6;
  s32 data;

  if (!id)
    return 0;
  if (id == -1)
  {
    return devil_img_goh_none;
  }
  if (id >= 80 && (u32)(id - 337) >= 0x40 && (u32)(id - 496) > 5)
    return 0;
  DevilModelNo = mdlGetDevilModelNo(id);
  if ((DevilModelNo & 0xF000) == 0x2000)
    v5 = DevilModelNo - 0x2000;
  else
    v5 = DevilModelNo;
  data = v5;
  v6 = Box(s32, &data);
  return Format("devil_img_goh_{0:X3}", v6, 0);
}

// 0x1f39300
bool sBtlGetShikimiEnemyIdNo(s32 id) {
  return (u32)(id - 188) < 0x19;
}

// 0x1f39310
static void LoadLocalizeText(void) {
  ;
}

// 0x1f39320
bool sBtlDrawText(SBTLDVLTK_WORK *dwk) {
  void *v3;
  s32 v4;
  s32 v5;
  SBTLUNIT_WORK *tube_wk;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 listID;
  s32 mode;
  s32 v15;
  u32 v16;

  v3 = NewSpecific(uint, 4u);
  InitializeArray_55364416(v3, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__59C6CF8C5CF90DA19897E3877124C72F74BE4F590F7A08F87B6B5E7E6B03AF62, 0);
  if (GlobalPID)
  {
    tube_wk = GlobalUnitWK[GlobalCurrentArray];
    if (!tube_wk)
      return 0;
    goto LABEL_20;
  }
  if (dwk->tube_support)
  {
    tube_wk = dwk->tube_wk;
    if (!tube_wk)
      return 0;
  }
  else
  {
    UnitMng = wk->UnitMng;
    listID = dwk->listID;
    tube_wk = sBtlSearchUnit_ID(UnitMng, listID);
    if (!tube_wk)
      return 0;
  }
LABEL_20:
  if (!GlobalPID)
  {
    if (dwk->devilid != tube_wk->para->devilid)
      return 0;
  }
  mode = dwk->mode;
  if (mode)
    v15 = -2139062272;
  else
    v15 = -1061109760;
  v16 = dwk->alpha | v15;
  if (!sBtlDrawTextFont((s32)sBtlDvltk, v4, v5, v16, tube_wk, mode, dwk))
    return 1;
  sBtlGetSpriteHandle();
  NewSpecific(uint, 4u);
  return 1;
}

// 0x1f399a0
void sBtlAnimWaku(SBTLDVLTK_WORK *dwk) {
  SBTLDVLTK_WAKUWORK *wk;
  SBTLDVLTK_WAKUWORK *v3;
  s32 st;
  s32 v5;
  bool v6;
  s32 v7;
  s32 v8;
  SBTLDVLTK_WAKUWORK *v9;
  s32 v10;
  s32 v11;
  s32 v12;
  s32 v13;
  SBTLDVLTK_WAKUWORK *v14;
  s32 v15;
  s32 v16;
  s32 v17;
  s32 v18;
  SBTLDVLTK_WAKUWORK *v19;
  s32 v20;
  s32 v21;
  s32 v22;
  s32 v23;
  SBTLDVLTK_WAKUWORK *v24;
  s32 v25;
  s32 v26;
  s32 v27;
  s32 v28;
  SBTLDVLTK_WAKUWORK *v29;
  s32 v30;
  s32 v31;
  s32 v32;
  s32 v33;
  SBTLDVLTK_WAKUWORK *v34;
  s32 v35;
  s32 v36;
  s32 v37;
  s32 v38;

  wk = dwk->wk;
  v3 = wk[0];
  st = v3->st;
  if (st == 1)
  {
    v8 = v3->alpha + 1;
    v6 = v3->alpha - 127 < 0;
    v3->alpha = v8;
    if (v6 != __OFSUB__(v8, 128))
      goto LABEL_9;
    v7 = 0;
    v3->alpha = 128;
    goto LABEL_8;
  }
  if (!st)
  {
    v5 = v3->alpha - 1;
    v6 = v3->alpha - 2 < 0;
    v3->alpha = v5;
    if (v6 ^ __OFSUB__(v5, 1) | (v5 == 1))
    {
      v7 = 1;
      v3->alpha = 1;
LABEL_8:
      v3->st = v7;
    }
  }
LABEL_9:
  v9 = wk[1];
  v10 = v9->st;
  if (v10)
  {
    if (v10 == 1)
    {
      v11 = v9->alpha + 1;
      v6 = v9->alpha - 127 < 0;
      v9->alpha = v11;
      if (v6 == __OFSUB__(v11, 128))
      {
        v12 = 0;
        v9->alpha = 128;
LABEL_16:
        v9->st = v12;
      }
    }
  }
  else
  {
    v13 = v9->alpha - 1;
    v6 = v9->alpha - 2 < 0;
    v9->alpha = v13;
    if (v6 ^ __OFSUB__(v13, 1) | (v13 == 1))
    {
      v12 = 1;
      v9->alpha = 1;
      goto LABEL_16;
    }
  }
  v14 = wk[2];
  v15 = v14->st;
  if (v15)
  {
    if (v15 == 1)
    {
      v16 = v14->alpha + 1;
      v6 = v14->alpha - 127 < 0;
      v14->alpha = v16;
      if (v6 == __OFSUB__(v16, 128))
      {
        v17 = 0;
        v14->alpha = 128;
LABEL_24:
        v14->st = v17;
      }
    }
  }
  else
  {
    v18 = v14->alpha - 1;
    v6 = v14->alpha - 2 < 0;
    v14->alpha = v18;
    if (v6 ^ __OFSUB__(v18, 1) | (v18 == 1))
    {
      v17 = 1;
      v14->alpha = 1;
      goto LABEL_24;
    }
  }
  v19 = wk[3];
  v20 = v19->st;
  if (v20)
  {
    if (v20 == 1)
    {
      v21 = v19->alpha + 1;
      v6 = v19->alpha - 127 < 0;
      v19->alpha = v21;
      if (v6 == __OFSUB__(v21, 128))
      {
        v22 = 0;
        v19->alpha = 128;
LABEL_32:
        v19->st = v22;
      }
    }
  }
  else
  {
    v23 = v19->alpha - 1;
    v6 = v19->alpha - 2 < 0;
    v19->alpha = v23;
    if (v6 ^ __OFSUB__(v23, 1) | (v23 == 1))
    {
      v22 = 1;
      v19->alpha = 1;
      goto LABEL_32;
    }
  }
  v24 = wk[4];
  v25 = v24->st;
  if (v25)
  {
    if (v25 == 1)
    {
      v26 = v24->alpha + 1;
      v6 = v24->alpha - 127 < 0;
      v24->alpha = v26;
      if (v6 == __OFSUB__(v26, 128))
      {
        v27 = 0;
        v24->alpha = 128;
LABEL_40:
        v24->st = v27;
      }
    }
  }
  else
  {
    v28 = v24->alpha - 1;
    v6 = v24->alpha - 2 < 0;
    v24->alpha = v28;
    if (v6 ^ __OFSUB__(v28, 1) | (v28 == 1))
    {
      v27 = 1;
      v24->alpha = 1;
      goto LABEL_40;
    }
  }
  v29 = wk[5];
  v30 = v29->st;
  if (v30)
  {
    if (v30 == 1)
    {
      v31 = v29->alpha + 1;
      v6 = v29->alpha - 127 < 0;
      v29->alpha = v31;
      if (v6 == __OFSUB__(v31, 128))
      {
        v32 = 0;
        v29->alpha = 128;
LABEL_48:
        v29->st = v32;
      }
    }
  }
  else
  {
    v33 = v29->alpha - 1;
    v6 = v29->alpha - 2 < 0;
    v29->alpha = v33;
    if (v6 ^ __OFSUB__(v33, 1) | (v33 == 1))
    {
      v32 = 1;
      v29->alpha = 1;
      goto LABEL_48;
    }
  }
  v34 = wk[6];
  v35 = v34->st;
  if (v35)
  {
    if (v35 == 1)
    {
      v36 = v34->alpha + 1;
      v6 = v34->alpha - 127 < 0;
      v34->alpha = v36;
      if (v6 == __OFSUB__(v36, 128))
      {
        v37 = 0;
        v34->alpha = 128;
LABEL_56:
        v34->st = v37;
      }
    }
  }
  else
  {
    v38 = v34->alpha - 1;
    v6 = v34->alpha - 2 < 0;
    v34->alpha = v38;
    if (v6 ^ __OFSUB__(v38, 1) | (v38 == 1))
    {
      v37 = 1;
      v34->alpha = 1;
      goto LABEL_56;
    }
  }
}

// 0x1f39c10
bool sBtlCheckPriority_Battle(SBTLDVLTK_MODE mode1, SBTLDVLTK_MODE mode2) {
  s32 *v5;
  s32 v7;

  v5 = NewSpecific(s32, 0x20u);
  InitializeArray_55364416(v5, Field__PrivateImplementationDetails__395D6A64262833ADA97172A4A24CDC5778F97C1A004D72AC0A23DE7727C78BFC, 0);
  if (mode1 == 22 && mode2 == 18)
    return 1;
  if ((u32)mode2 <= 0x27 && ((1 << mode2) & 0xA800000000LL) != 0)
    return 1;
  v7 = *(u32 *)((char *)v5 + 24) - 1;
  return v7 > mode1 && v7 > mode2 && *(u32 *)((s64)&v5[0] + 4 * mode1) <= *(u32 *)((s64)&v5[0] + 4 * mode2);
}

// 0x1f39930
u32 sBtlCheckDebugFlag(void) {
  return 1;
}

// 0x1f397c0
sprHandle_t *sBtlGetSpriteHandle(void) {
  SBTLPANEL_WORK *panelwk;

  if (GlobalPID)
  {
    return GlobalSpr;
  }
  panelwk = wk->panelwk;
  if (!panelwk)
    return 0;
  panelwk = wk->panelwk;
  return panelwk->hPanelSpr5;
}

// 0x1f39d40
s32 sBtlGetKucyou(s32 DevilID) {
  if (DevilID == 208)
    return 15;
  if (DevilID == 209)
    return 16;
  return sBtlGetDevilData(DevilID, -1)->kucyo;
}

// 0x1f39de0
SBTLDVLTK_LISTWORK *sBtlCreateDvltkList(void) {
  SBTLDVLTK_LISTWORK *v1;

  v1 = (SBTLDVLTK_LISTWORK *)Allocate(SBTLDVLTK_LISTWORK);
  _ctor(v1, 0);
  v1->num = 0;
  v1->dwk = 0;
  return v1;
}

// 0x1f39e50
bool sBtlLoadDvltkData_Enemy(SBTLUNIT_WORK *wk) {
  return 1;
}

// 0x1f39e60
SBTLDVLTK_MODE sBtlGetRandNo(SBTLDVLTK_MODE type1, SBTLDVLTK_MODE type2, SBTLDVLTK_MODE type3) {
  s32 v7;
  s32 v8;

  v7 = sub_1905740(3, 0);
  if (v7 == 2)
    v8 = type3;
  else
    v8 = type1;
  if (v7 == 1)
    return type2;
  else
    return v8;
}

// 0x1f39eb0
bool sBtlCreateWork(SBTLUNIT_WORK *wk) {
  u16 *v3;
  s32 side;
  s32 devilid;
  s16 huumaID;
  s32 v10;
  s16 dvltk_gstat;
  s32 v12;
  s32 hstatus;
  bool result;
  sbtldvltk_unitworktag *dvltkwk;
  s32 v17;
  s64 kucyo;
  sbtldvltk_unitworktag *v20;
  char *FaceTexName;
  sbtldvltk_unitworktag *v22;
  s16 v23;
  u8 *v24;
  u8 **v25;
  s32 v26;
  char v27;
  s64 v28;
  void *v29;
  void *pData;
  u8 **v31;
  s32 v32;
  s64 v33;
  sbtldvltk_unitworktag *v34;
  u8 **v35;
  s32 Kucyou;
  u8 *v37;
  u8 **v38;
  void *v40;
  void *v41;
  u8 **v42;
  s32 v44;

  v3 = NewSpecific(char, 0x28u);
  CreateString_54864672(0, v3, 0);
  side = wk->side;
  if ((side & 0x80) != 0)
    return 1;
  devilid = wk->para->devilid;
  if ((side & 2) != 0)
  {
    huumaID = sBtlGetDevilData(devilid, -1)->huumaID;
    if (!huumaID)
      return 1;
  }
  else
  {
    huumaID = wk->para->devilid;
  }
  v10 = wk->para->devilid;
  if (v10 == 208)
  {
    if (!sbtldvltk_filetbl[15])
      return 1;
  }
  else if (v10 == 209)
  {
    if (!sbtldvltk_filetbl[16])
      return 1;
  }
  else
  {
    if (!sbtldvltk_filetbl[sBtlGetDevilData(v10, -1)->kucyo])
      return 1;
  }
  if ((wk->hstatus & 1) != 0)
    return 1;
  dvltk_gstat = wk->dvltk_gstat;
  if (dvltk_gstat)
  {
    v12 = dvltk_gstat;
    goto LABEL_27;
  }
  dvltkwk = wk->dvltkwk;
  v17 = wk->para->devilid;
  if (v17 == 208)
  {
    kucyo = 15;
    goto LABEL_55;
  }
  if (v17 == 209)
  {
    kucyo = 16;
  }
  else
  {
    kucyo = sBtlGetDevilData(v17, -1)->kucyo;
  }
LABEL_55:
  v24 = NewSpecific(byte, pGlobalMsg[kucyo]->max_length);
  dvltkwk->pData = v24;
  v25 = pGlobalMsg;
  v26 = wk->para->devilid;
  if (v26 == 208)
  {
    v27 = 1;
    v28 = 15;
  }
  else if (v26 == 209)
  {
    v27 = 1;
    v28 = 16;
  }
  else
  {
    v28 = sBtlGetDevilData(v26, -1)->kucyo;
    v27 = byte_575839D;
  }
  v29 = v25[v28];
  pData = wk->dvltkwk->pData;
  v31 = pGlobalMsg;
  v32 = wk->para->devilid;
  if (v32 == 208)
  {
    v33 = 15;
  }
  else if (v32 == 209)
  {
    v33 = 16;
  }
  else
  {
    v33 = sBtlGetDevilData(v32, -1)->kucyo;
  }
  Copy_56180528(v29, pData, v31[v33]->max_length, 0);
  v34 = wk->dvltkwk;
  wk->dvltk_gstat = 2;
  v34->hFile = 0;
  dvltk_gstat = wk->dvltk_gstat;
  v12 = dvltk_gstat;
  if ((u32)dvltk_gstat > 5)
    return 0;
LABEL_27:
  switch (v12)
  {
    case 0:
      goto LABEL_79;
    case 1:
      v20 = wk->dvltkwk;
      v35 = pGlobalMsg;
      Kucyou = sBtlGetKucyou(wk->para->devilid);
      v37 = NewSpecific(byte, v35[Kucyou]->max_length);
      v20->pData = v37;
      v38 = pGlobalMsg;
      v40 = v38[sBtlGetKucyou(wk->para->devilid)];
      v41 = wk->dvltkwk->pData;
      v42 = pGlobalMsg;
      v44 = sBtlGetKucyou(wk->para->devilid);
      Copy_56180528(v40, v41, v42[v44]->max_length, 0);
      goto LABEL_78;
    case 2:
      FaceTexName = sBtlGetFaceTexName(huumaID);
      v22 = wk->dvltkwk;
      if (FaceTexName)
      {
        if (v22->LB_Load)
        {
          v23 = 4;
          result = 0;
        }
        else
        {
LABEL_78:
          dvltk_gstat = wk->dvltk_gstat;
LABEL_79:
          result = 0;
          v23 = dvltk_gstat + 1;
        }
        wk->dvltk_gstat = v23;
      }
      else
      {
        v22->CacheTex = 0;
LABEL_82:
        hstatus = wk->hstatus;
        result = 1;
LABEL_83:
        wk->hstatus = hstatus | 1;
      }
      break;
    case 3:
      if (!dds3SearchProcessName("sbattle"))
        goto LABEL_82;
      goto LABEL_78;
    case 4:
    case 5:
      hstatus = wk->hstatus;
      result = 0;
      goto LABEL_83;
    default:
      return 0;
  }
  return result;
}

// 0x1f3a500
SBTLDVLTK_WORK *sBtlCreateDvltk_Priority(SBTLDVLTK_LISTWORK *lwk, SBTLUNIT_WORK *wk, SBTLDVLTK_MODE mode) {
  SBATTLE_WORK *v9;
  s32 side;
  sdatUnitWork_t *para;
  s32 v12;
  SBTLUNIT_WORK *v13;
  u32 status;
  SBTLUNIT_WORK *Nakama;
  sdatUnitWork_t *v16;
  u32 BadStatus;

  if (!wk)
    return 0;
  v9 = wk;
  if ((v9->status4 & 0x100) != 0)
    return 0;
  side = wk->side;
  if ((side & 1) == 0)
    return 0;
  if ((u32)mode > 0x11)
    goto LABEL_36;
  if (((1 << mode) & 0x1E00) == 0)
  {
    if (((1 << mode) & 0x20018) != 0)
    {
      para = wk->para;
      if (sBtlGetBadStatus(para) - 7 >= 2)
        v12 = mode;
      else
        v12 = 13;
      goto LABEL_17;
    }
    if (mode == 14)
    {
      v16 = wk->para;
      BadStatus = sBtlGetBadStatus(v16);
      if (BadStatus - 9 >= 5)
      {
        if (BadStatus - 7 >= 2)
          v12 = 14;
        else
          v12 = 13;
      }
      else
      {
        v12 = 17;
      }
LABEL_17:
      v13 = wk;
      status = wk->actwk->status;
      if (status == 40)
        goto LABEL_38;
      goto LABEL_37;
    }
LABEL_36:
    v13 = wk;
    v12 = mode;
    status = wk->actwk->status;
    if (status == 40)
      goto LABEL_38;
    goto LABEL_37;
  }
  if ((side & 0x80) == 0)
    goto LABEL_36;
  v9 = wk;
  if (v9->member_num < 1)
    goto LABEL_36;
  Nakama = sBtlGetNakama(0);
  if (!Nakama)
    goto LABEL_36;
  v13 = Nakama;
  v12 = mode;
  if (!CheckLiveTarget(Nakama))
    goto LABEL_36;
  status = v13->actwk->status;
  if (status == 40)
  {
LABEL_38:
    if (mode == 15)
      goto LABEL_39;
    return 0;
  }
LABEL_37:
  if (status == 10)
    goto LABEL_38;
LABEL_39:
  return sBtlCreateDvltk(lwk, v13, v12, 0, 0);
}

// 0x1f3af00
SBTLDVLTK_WORK *sBtlCreateDvltk_Gouto(SBTLDVLTK_LISTWORK *lwk, SBTLUNIT_WORK *wk, SBTLDVLTK_MODE mode, s32 rndptn) {
  SBATTLE_WORK *v10;
  s32 v18;

  v10 = wk;
  if ((v10->status & 0x40000000) != 0)
    return 0;
  if ((u32)(mode - 281) < 3)
  {
    if (!zouen_talk_time)
    {
      zouen_talk_time = 1200;
      goto LABEL_26;
    }
    return 0;
  }
  if (mode == 262)
  {
    v10 = wk;
    if (v10->hitokoto_gunuse)
      return 0;
    if (gun_talk_time || (s32)sub_1905740(10, 0) > 3)
      return 0;
    gun_talk_time = 3600;
  }
LABEL_26:
  if ((u32)(mode - 289) >= 2 && wk->encountno == 31)
    return 0;
  v18 = sub_1905740(rndptn, 0) + mode;
  return sBtlCreateDvltk(lwk, wk, v18, 1, 0);
}

// 0x1f3b120
SBTLDVLTK_WORK *sBtlCreateDvltk_Kuda(SBTLDVLTK_LISTWORK *lwk, SBTLUNIT_WORK *wk, SBTLDVLTK_MODE mode) {
  return sBtlCreateDvltk(lwk, wk, mode, 0, 1);
}

// 0x1f3a990
SBTLDVLTK_WORK *sBtlCreateDvltk(SBTLDVLTK_LISTWORK *lwk, SBTLUNIT_WORK *wk, SBTLDVLTK_MODE mode, bool gouto, bool kuda) {
  _BOOL4 v6;
  _BOOL4 IsBattle;
  s64 v12;
  SBTLDVLTK_WORK *p_dwk;
  s32 v17;
  sdatUnitWork_t *para;
  s32 ListID;
  s32 devilid;
  s64 v21;
  s64 v22;
  s64 v23;
  bool v25;
  _BOOL4 v27;
  _BOOL4 v29;
  void *Instance;
  s32 v31;
  s32 v32;
  void *v33;

  v6 = kuda;
  if ((u32)mode <= 0x27 && ((1 << mode) & 0xA800000000LL) != 0 || evtBitCheck(42))
  {
    if (!wk)
      return 0;
    goto LABEL_6;
  }
  IsBattle = sbattleIsBattle();
  v12 = 0;
  if (wk && (!IsBattle || v6))
  {
LABEL_6:
    if ((u32)mode <= 0x31 && ((1 << mode) & 0x3000100000000LL) != 0)
    {
      if (!IsStartNakamaCutIn())
        return 0;
    }
    if (gouto || (wk->side & 0x80) == 0)
    {
      p_dwk = &lwk->dwk;
      if (!lwk->dwk)
      {
        v12 = Allocate(SBTLDVLTK_WORK);
        _ctor(v12, 0);
        *(u64 *)(v12 + 144) = 0;
        *(u64 *)(v12 + 152) = 0;
        lwk->dwk = (SBTLDVLTK_WORK *)v12;
        lwk->num = 1;
LABEL_46:
        para = wk->para;
        *(u32 *)(v12 + 40) = mode;
        *(u32 *)(v12 + 44) = 0;
        ListID = wk->ListID;
        *(u32 *)(v12 + 68) = 322;
        devilid = para->devilid;
        LODWORD(para) = para->seikaku;
        *(u32 *)(v12 + 16) = ListID;
        *(u32 *)(v12 + 20) = devilid;
        *(u32 *)(v12 + 28) = (u32)para;
        v21 = *(u64 *)(v12 + 112);
        *(u64 *)(v12 + 60) = 0x20200000000LL;
        v23 = *(u64 *)(v21 + 56);
        v22 = *(u64 *)(v21 + 64);
        *(u32 *)(v23 + 16) = 1;
        *(u32 *)(v22 + 16) = 1;
        *(u64 *)(v12 + 132) = 0x100000000LL;
        v25 = v6;
        sBtlPlaySE(0x10023u);
        *(u64 *)(v12 + 88) = 0;
        *(u8 *)(v12 + 80) = gouto;
        *(u32 *)(v12 + 76) = 0;
        if (!sbattleIsBattle())
          goto LABEL_66;
        if ((u32)mode > 0x31)
          goto LABEL_81;
        if (((1 << mode) & 0x3000100040006LL) != 0)
        {
          v27 = wk->hitokoto1st != 0;
LABEL_58:
          if (wk->hitokoto_spirit)
            v29 = 0;
          else
            v29 = v27;
          if (v29)
          {
            Instance = get_Instance(0);
            HitikotoStock(Instance, 0);
            *(u32 *)(v12 + 76) = 1;
            *(u32 *)(v12 + 36) = 180;
            *(u8 *)(v12 + 96) = v25;
            if (!v6)
              return (SBTLDVLTK_WORK *)v12;
LABEL_80:
            *(u64 *)(v12 + 104) = wk;
            return (SBTLDVLTK_WORK *)v12;
          }
LABEL_66:
          if (*(u32 *)(v12 + 76))
          {
            *(u32 *)(v12 + 36) = 180;
            *(u8 *)(v12 + 96) = v25;
            if (!v6)
              return (SBTLDVLTK_WORK *)v12;
            goto LABEL_80;
          }
          v31 = *(u32 *)(v12 + 20);
          *(u32 *)(v12 + 36) = 300;
          if (v31 == 208)
          {
            v32 = 240;
          }
          else
          {
            if (v31 != 209)
              goto LABEL_77;
            v32 = 241;
          }
          *(u32 *)(v12 + 20) = v32;
LABEL_77:
          v33 = get_Instance(0);
          NCutInReq(v33, *(u32 *)(v12 + 20), 0);
          *(u32 *)(v12 + 20) = v31;
          *(u8 *)(v12 + 96) = v25;
          if (!v6)
            return (SBTLDVLTK_WORK *)v12;
          goto LABEL_80;
        }
        if (((1 << mode) & 0xA800000000LL) != 0)
        {
          v27 = 0;
          goto LABEL_58;
        }
        else
        {
LABEL_81:
          v27 = 1;
          goto LABEL_58;
        }
        goto LABEL_58;
      }
      v12 = p_dwk;
      if (GlobalPID)
      {
        if (!*(u32 *)(v12 + 32) && *(u32 *)(v12 + 40) > mode)
          return (SBTLDVLTK_WORK *)v12;
        goto LABEL_46;
      }
      v17 = *(u32 *)(v12 + 40);
      if (v17 == mode)
      {
        if (*(u32 *)(v12 + 44) == 1)
          *(u32 *)(v12 + 32) = 0;
        if ((u32)(mode - 275) > 3)
          return (SBTLDVLTK_WORK *)v12;
      }
      if (*(u8 *)(v12 + 80))
      {
        if ((u32)(v17 - 263) <= 0x1B && ((1 << (v17 - 7)) & 0xFE307FF) != 0)
        {
          sBtlDrawText(v12);
        }
      }
      if (mode == 291 || mode == 258)
        *(u8 *)(v12 + 141) = 1;
      ClassClear(v12, 0);
      *(u64 *)(v12 + 144) = 0;
      *(u64 *)(v12 + 152) = 0;
      goto LABEL_46;
    }
    return 0;
  }
  return (SBTLDVLTK_WORK *)v12;
}

// 0x1f3b460
static bool SpecifiedGoutoMessage(SBTLDVLTK_MODE mode) {
  return ((u32)(mode - 263) < 0x1C) & (0xFE307FFu >> (mode - 7));
}

// 0x1f3b1a0
static bool IsStartNakamaCutIn(void) {
  s32 encountno;

  if (sBtlCheck_StartLoad() != -1)
    return 0;
  encountno = wk->encountno;
  if (encountno == 22)
    return 0;
  if (encountno == 23)
    return 0;
  if (encountno == 24)
    return 0;
  encountno = wk->encountno;
  if (encountno == 26)
    return 0;
  encountno = wk->encountno;
  if (encountno == 27)
    return 0;
  encountno = wk->encountno;
  if (encountno == 28)
    return 0;
  encountno = wk->encountno;
  if (encountno == 29)
    return 0;
  encountno = wk->encountno;
  if (encountno == 30)
    return 0;
  encountno = wk->encountno;
  if (encountno == 48)
    return 0;
  encountno = wk->encountno;
  return encountno != 517;
}

// 0x1f3b480
bool Proc(SBTLDVLTK_LISTWORK *lwk) {
  SBTLDVLTK_WORK *dwk;
  f32 v14;
  s32 v15;
  s32 status;
  s32 sincount;
  s32 v18;
  s32 alpha;
  s32 v20;
  SBATTLE_WORK *v22;
  u32 v23;
  void *Instance;
  void *v26;
  void *v27;
  s32 cmpcounter;
  void *v30;

  if (!lwk)
    return 0;
  dwk = lwk->dwk;
  if (wk)
  {
    if (IsSceanStop())
      goto LABEL_27;
    if (wk->cmbSkl->bRun)
      goto LABEL_27;
    if (gun_talk_time)
    {
      gun_talk_time = gun_talk_time - 1;
    }
    if (zouen_talk_time)
    {
      zouen_talk_time = zouen_talk_time - 1;
    }
  }
LABEL_27:
  if (!dwk || !lwk->num)
    return 0;
  if (wk->bosseventflg)
    return 0;
  if (!GlobalPID)
  {
    if (!wk->kaiwaflg)
    {
      if ((wk->status & 0x8000000) != 0)
        return 0;
      if ((wk->status2 & 0x12) != 0)
        return 0;
    }
  }
  do
  {
    status = dwk->status;
    if (status == 1)
    {
      dwk->alpha += 5;
      LimitRange(&dwk->alpha, 0, 128);
      ++dwk->counter;
      if (dwk->mesType)
      {
        if (dwk->overwrite_f)
        {
          Instance = get_Instance(0);
          if (IsNCutInOut(Instance, 0))
            goto LABEL_64;
        }
        cmpcounter = dwk->cmpcounter;
        goto LABEL_9000;
LABEL_64:
        v26 = get_Instance(0);
        if (op_Inequality(v26, 0, 0))
        {
          v27 = get_Instance(0);
          CloseDevilMes(v27, 0);
        }
        dwk->overwrite_f = 0;
        cmpcounter = dwk->cmpcounter;
LABEL_9000:
        LimitRange(&dwk->counter, 0, cmpcounter);
        if (dwk->counter < dwk->cmpcounter)
          goto LABEL_46;
LABEL_81:
        dwk->overwrite_f = 0;
        dwk->status = 2;
        goto LABEL_46;
      }
      v30 = get_Instance(0);
      if (!IsNCutInOut(v30, 0))
        goto LABEL_46;
      goto LABEL_81;
    }
    else
    {
      if (status)
        goto LABEL_46;
      sincount = dwk->sincount;
      v18 = COUNT_UP_360(sincount, 12);
      alpha = dwk->alpha;
      dwk->sincount = v18;
      dwk->alpha = alpha + 5;
      LimitRange(&dwk->alpha, 0, 128);
      v20 = dwk->sincount;
      if ((u32)v20 > 0xB3)
      {
        dwk->status = 1;
        dwk->ofs_x = 386;
        if (dwk->mode != 15)
          goto LABEL_46;
        StopBattle();
        v22 = wk;
        *(u32 *)&v22->eventno = 6;
        v23 = v22->status;
        v22->eventgstat = 0;
        v22->status = v23 | 0x400;
        sBtlSetNSTOP();
        goto LABEL_46;
      }
      v14 = GET_360toSIN((f32)v20, 386.0, 514.0);
      v15 = v14;
      if (v14 == INFINITY)
        v15 = 0x80000000;
      dwk->ofs_x = v15;
    }
LABEL_46:
    dwk = dwk->next;
  }
  while (dwk);
  return 1;
}

// 0x1f3ba60
bool sBtlSearchDvltk(SBTLDVLTK_LISTWORK *lwk, SBTLUNIT_WORK *wk) {
  sprHandle_t *SpriteHandle;
  bool result;
  SBTLDVLTK_WORK *dwk;

  SpriteHandle = sBtlGetSpriteHandle();
  result = 0;
  if (!lwk)
    return result;
  if (SpriteHandle)
  {
    dwk = lwk->dwk;
    if (!dwk || !lwk->num)
      return 0;
    if (GlobalPID)
      goto LABEL_20;
    goto LABEL_14;
    if (!GlobalPID)
    {
LABEL_14:
      if ((wk->status & 0x8000000) == 0)
        goto LABEL_20;
      return 0;
    }
LABEL_20:
    while (dwk->status > 1u || dwk->listID != wk->ListID)
    {
      dwk = dwk->next;
      if (!dwk)
        return 0;
    }
    return 1;
  }
  return result;
}

// 0x1f3bbd0
static void CloseWin(void) {
  void *v3;
  void *v5;
  void *Instance;

  if (!sbattleIsBattle())
  {
    goto LABEL_5;
  }
  Instance = get_Instance(0);
  HitokotoChange(Instance, 0, 0);
LABEL_5:
  v3 = get_Instance(0);
  if (!op_Inequality(v3, 0, 0))
    return;
  v5 = get_Instance(0);
  CloseDevilMes(v5, 0);
}

// 0x1f3bd60
bool Draw(SBTLDVLTK_LISTWORK *lwk) {
  SBTLDVLTK_WORK *dwk;
  s32 bosseventflg;
  SBATTLE_WORK *v11;
  u32 status2;
  s32 mode;
  void *Instance;
  void *v16;
  void *v17;
  void *v18;

  if (!lwk || (dwk = lwk->dwk) == 0 || !lwk->num)
  {
LABEL_13:
    CloseWin();
    return 0;
  }
  bosseventflg = (u8)wk->bosseventflg;
  if (bosseventflg)
  {
    goto LABEL_13;
  }
  if (GlobalPID)
    goto LABEL_31;
  v11 = wk;
  if (!v11->kaiwaflg)
  {
    v11 = wk;
    status2 = v11->status2;
    if ((status2 & 0x12) != 0)
      goto LABEL_27;
    status2 = wk->status2;
    if ((status2 & 0x80) != 0)
    {
LABEL_27:
      goto LABEL_13;
    }
  }
  do
  {
LABEL_31:
    if (!dwk)
      break;
    mode = dwk->mode;
    if ((!mode || !dwk->next) && dwk->status <= 1u)
    {
      if (dwk->mesType)
      {
        Instance = get_Instance(0);
        HitokotoChange(Instance, 1, 0);
      }
      else
      {
        v16 = get_Instance(0);
        if (op_Inequality(v16, 0, 0))
        {
          v17 = get_Instance(0);
          if (IsNCutInIn(v17, 0))
          {
            v18 = get_Instance(0);
            OpenDevilMes(v18, 0);
          }
        }
      }
      sBtlDrawText(dwk);
    }
    dwk = dwk->next;
  }
  while (mode);
  return 1;
}

// 0x1f3c040
bool sBtlReleaseDvltk_List(SBTLDVLTK_LISTWORK *lwk, u8 flg) {
  SBTLDVLTK_LISTWORK *v3;
  SBTLDVLTK_WORK *p_dwk;
  SBTLDVLTK_WORK *dwk;
  SBTLDVLTK_WORK *prev;
  SBTLDVLTK_WORK *v7;
  SBTLDVLTK_WORK *next;
  SBTLDVLTK_WORK *v9;
  SBTLDVLTK_WORK *v10;
  SBTLDVLTK_WORK *v11;
  SBTLDVLTK_WORK *v12;
  SBTLDVLTK_WORK *v13;
  SBTLDVLTK_WORK *v14;
  SBTLDVLTK_WORK *v15;
  SBTLDVLTK_WORK *v16;
  SBTLDVLTK_WORK *v17;

  if (lwk)
  {
    v3 = lwk;
    p_dwk = &lwk->dwk;
    dwk = lwk->dwk;
    if (dwk && lwk->num)
    {
      if (flg)
      {
        while (1)
        {
          prev = dwk->prev;
          dwk->status = 2;
          if (prev)
            break;
          v9 = 0;
          next = dwk->next;
          if (next)
            goto LABEL_9;
LABEL_10:
          if (!v9)
          {
            v10 = dwk->next;
            p_dwk = v10;
            v11 = p_dwk;
            if (p_dwk)
            {
              v11->prev = 0;
            }
          }
          dwk = dwk->next;
          --v3->num;
          if (!dwk)
            goto LABEL_28;
        }
        v7 = dwk->next;
        prev->next = v7;
        v9 = dwk->prev;
        next = dwk->next;
        if (!next)
          goto LABEL_10;
LABEL_9:
        next->prev = v9;
        v9 = dwk->prev;
        goto LABEL_10;
      }
      while (1)
      {
        while (dwk->status != 2)
        {
          dwk = dwk->next;
          if (!dwk)
            goto LABEL_28;
        }
        v12 = dwk->prev;
        if (v12)
          break;
        v15 = 0;
        v14 = dwk->next;
        if (v14)
          goto LABEL_19;
LABEL_20:
        if (!v15)
        {
          v16 = dwk->next;
          p_dwk = v16;
          v17 = p_dwk;
          if (p_dwk)
          {
            v17->prev = 0;
          }
        }
        dwk = dwk->next;
        --v3->num;
        if (!dwk)
        {
LABEL_28:
          LOBYTE(lwk) = 1;
          return (char)lwk;
        }
      }
      v13 = dwk->next;
      v12->next = v13;
      v15 = dwk->prev;
      v14 = dwk->next;
      if (!v14)
        goto LABEL_20;
LABEL_19:
      v14->prev = v15;
      v15 = dwk->prev;
      goto LABEL_20;
    }
    LOBYTE(lwk) = 0;
  }
  return (char)lwk;
}

// 0x1f3c1b0
bool sBtlDeleteDvltkList(SBTLDVLTK_LISTWORK *lwk) {
  sBtlReleaseDvltk_List(lwk, 1u);
  return 1;
}

// 0x1f39650
bool sBtlDrawTextFont(s32 x, s32 y, s32 z, u32 rgba, SBTLUNIT_WORK *wk, SBTLDVLTK_MODE mode, SBTLDVLTK_WORK *_dwk) {
  char *DrawText;
  char *v13;
  s32 devilid;
  void *Instance;
  void *v17;
  sdfColor_t v18;

  DrawText = GetDrawText(rgba, wk, mode, dwk);
  v13 = DrawText;
  if (dwk->mesType)
  {
    if (dwk->gouto)
      devilid = 209;
    else
      devilid = wk->para->devilid;
    Instance = get_Instance(0);
    HitokotoDraw(Instance, v13, devilid, wk->ListID, 0);
    return 0;
  }
  else if (DrawText)
  {
    v17 = get_Instance(0);
    v18.r = 1.0;
    v18.g = 1.0;
    v18.b = 1.0;
    v18.a = 1.0;
    DevilMesText(v17, v13, v18, 0);
    return 1;
  }
  else
  {
    return 0;
  }
}

// 0x1f3c220
static char *GetDrawText(u32 rgba, SBTLUNIT_WORK *wk, SBTLDVLTK_MODE mode, SBTLDVLTK_WORK *_dwk) {
  void *Instance;
  _BOOL4 IsGoutoVoicePlay;
  char *result;
  char **p_gouto_text;
  u8 *pData;
  u8 *v16;
  FontReq_t *v17;
  s32 devilid;
  char *v19;
  s64 v20;
  char *v22;
  char *LocalizeText;
  char *v24;
  char *v25;
  char *v27;
  char *v29;
  s32 v30;
  char **v32;
  s32 v34;
  char *v35;
  char *v36;
  char *PartVoice;

  if (!playing_voice)
  {
    IsGoutoVoicePlay = 0;
    if (dwk->gouto)
      goto LABEL_7;
    goto LABEL_12;
  }
  Instance = get_Instance(0);
  IsGoutoVoicePlay = IsGoutoVoicePlay(Instance, playing_voice, 0);
  if (dwk->gouto)
  {
LABEL_7:
    p_gouto_text = &dwk->gouto_text;
    result = dwk->gouto_text;
    if (result)
      return result;
    LODWORD(v20) = dwk->mode - 256;
    v22 = gouto_hitokoto[(s32)v20][0];
    LocalizeText = GetLocalizeText(v22, 1);
    *p_gouto_text = LocalizeText;
    v24 = *p_gouto_text;
    v25 = ConvertNBSP(v24);
    *p_gouto_text = v25;
    if ((IsGoutoVoicePlay & sndVoiceStatus(0) & 1) == 0)
    {
      v20 = (s32)v20;
LABEL_33:
      v27 = gouto_hitokoto[v20][1];
      sndVoicePlayFile(v27, 0);
      v29 = gouto_hitokoto[v20][1];
      playing_voice = v29;
      return *p_gouto_text;
    }
    sndVoiceStop(0);
    v20 = (s32)v20;
    goto LABEL_33;
  }
LABEL_12:
  pData = wk->dvltkwk->pData;
  if (!pData)
    return 0;
  result = MessageNumSearch(mode, pData, 0);
  if (result)
  {
    v16 = result;
    v17 = MessageRequestNS(0, 0, 0, 0, 0, 0, 0, v16, 0);
    if (dwk->call_voice)
    {
LABEL_48:
LABEL_50:
      frSetFontColor(v17, rgba);
      frDrawFontEx2(v17, 1, 0x6Eu);
      frDestroyFontRequestAfter(v17);
      return sub_1C88420(v17, 0);
    }
    devilid = (u16)wk->para->devilid;
    if (devilid != 209)
    {
      if (devilid != 208)
      {
        v34 = sub_1F4D6E0(0);
        itfPartVoiceDevilSet(wk->para->devilid);
        v35 = Replace_54838864(v17->tag_id, "<", "", 0);
        v36 = Replace_54838864(v35, ">", "", 0);
        PartVoice = itfGetPartVoice(v36);
        if (!IsNullOrEmpty(PartVoice, 0))
        {
          sndVoicePlayFile(PartVoice, 0);
        }
        itfPartVoiceDevilSet(v34);
        goto LABEL_50;
      }
      v19 = "PVA03_55_002";
      goto LABEL_47;
    }
    v30 = sub_1905740(3, 0);
    if (v30 == 1)
    {
      v32 = &"PVA02A_00_008";
      goto LABEL_46;
    }
    else if (v30)
    {
      v32 = &"PVA02A_00_009";
      goto LABEL_46;
    }
    else
    {
      v32 = &"PVA02A_00_003";
LABEL_46:
      v19 = *v32;
LABEL_47:
      sndVoicePlayFile(v19, 0);
      dwk->call_voice = 1;
      goto LABEL_48;
    }
    goto LABEL_46;
  }
  return result;
}

// 0x1f3c7d0
void sBtlCombDevilTalkSet(s32 _num) {
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v5;
  SBTLUNIT_WORK *v7;
  s32 hitCombDevilTalk_1;
  bool v12;
  u32 v14;
  SBATTLE_WORK *v15;
  s32 hitCombDevilTalk_2;
  SBTLDVLTK_LISTWORK *dvltkList;
  s32 v18;
  SBTLDVLTK_LISTWORK *v19;
  SBTLUNIT_WORK *v20;
  SBTLDVLTK_LISTWORK *v21;

  Nakama = sBtlGetNakama(0);
  v5 = sBtlGetNakama(1);
  v7 = v5;
  if (Nakama && v5)
  {
    if (num != 1)
    {
      if (num)
        return;
      hitCombDevilTalk_1 = wk->hitCombDevilTalk_1;
      if (hitCombDevilTalk_1)
      {
        if (hitCombDevilTalk_1 != 1)
          return;
        wk->hitCombDevilTalk_1 = 0;
        Nakama = v7;
LABEL_33:
        dvltkList = wk->dvltkList;
        v18 = 9;
        v19 = dvltkList;
        v20 = Nakama;
LABEL_36:
        sBtlCreateDvltk_Priority(v19, v20, v18);
        return;
      }
      wk->hitCombDevilTalk_1 = 1;
      goto LABEL_33;
    }
    v15 = wk;
    hitCombDevilTalk_2 = v15->hitCombDevilTalk_2;
    if (hitCombDevilTalk_2)
    {
      if (v14)
      {
        if (hitCombDevilTalk_2 != 1)
          return;
      }
      else
      {
        v15 = wk;
        if (v15->hitCombDevilTalk_2 != 1)
          return;
      }
      v15 = wk;
      v15->hitCombDevilTalk_2 = 0;
      Nakama = v7;
      goto LABEL_42;
    }
    if (!v14)
    {
      v15 = wk;
    }
    v15->hitCombDevilTalk_2 = 1;
    goto LABEL_42;
  }
  v12 = Nakama != 0;
  if (Nakama && !v5)
    goto LABEL_17;
  Nakama = v5;
  if (!v5)
    v12 = 1;
  if (!v12)
  {
LABEL_17:
    if (num != 1)
    {
      if (num)
        return;
      goto LABEL_33;
    }
LABEL_42:
    v21 = wk->dvltkList;
    v18 = 10;
    v19 = v21;
    v20 = Nakama;
    goto LABEL_36;
  }
}

// 0x1f3cad0
void sBtlDeadDevilTalkSet(void) {
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v4;
  SBTLUNIT_WORK *v6;
  s32 deadDevilTalk;
  bool v11;
  s32 v12;
  s32 v15;
  SBTLDVLTK_LISTWORK *v18;
  s32 v19;
  SBTLDVLTK_LISTWORK *v20;
  SBTLUNIT_WORK *v21;
  s32 v22;
  SBTLDVLTK_LISTWORK *dvltkList;

  Nakama = sBtlGetNakama(0);
  v4 = sBtlGetNakama(1);
  v6 = v4;
  if (Nakama && v4)
  {
    deadDevilTalk = wk->deadDevilTalk;
    if (deadDevilTalk)
    {
      if (deadDevilTalk != 1)
        return;
      wk->deadDevilTalk = 0;
      v12 = 1;
      goto LABEL_18;
    }
    v12 = 0;
    wk->deadDevilTalk = 1;
LABEL_36:
    v6 = Nakama;
    v22 = DeadTextLogGet(v12);
    if (!v22)
      goto LABEL_37;
    goto LABEL_19;
LABEL_35:
    goto LABEL_36;
  }
  v11 = Nakama != 0;
  if (Nakama && !v4)
  {
    v12 = 0;
    goto LABEL_36;
  }
  if (!v4)
    v11 = 1;
  if (!v11)
  {
    v12 = 1;
    Nakama = v6;
    goto LABEL_35;
LABEL_18:
    v15 = DeadTextLogGet(1);
    if (!v15)
    {
LABEL_37:
      dvltkList = wk->dvltkList;
      v19 = 21;
      v20 = dvltkList;
      v21 = v6;
LABEL_24:
      sBtlCreateDvltk_Priority(v20, v21, v19);
      return;
    }
LABEL_19:
    v18 = wk->dvltkList;
    v19 = 23;
    v20 = v18;
    v21 = v6;
    goto LABEL_24;
  }
}

// 0x1f3cd40
static s32 DeadTextLogGet(s32 _num) {
  u32 v4;
  SBATTLE_WORK *v5;
  s32 deadDevilTalk_log1;
  s32 deadDevilTalk_log2;

  if (num == 1)
  {
    deadDevilTalk_log2 = wk->deadDevilTalk_log2;
    if (deadDevilTalk_log2)
    {
      if (deadDevilTalk_log2 != 1)
        return -1;
      wk->deadDevilTalk_log2 = 0;
      return 1;
    }
    wk->deadDevilTalk_log2 = 1;
    return 0;
  }
  if (num)
    return -1;
  v5 = wk;
  deadDevilTalk_log1 = v5->deadDevilTalk_log1;
  if (deadDevilTalk_log1)
  {
    if (v4)
    {
      if (deadDevilTalk_log1 == 1)
        goto LABEL_24;
    }
    else
    {
      v5 = wk;
      if (v5->deadDevilTalk_log1 == 1)
      {
LABEL_24:
        v5->deadDevilTalk_log1 = 0;
        return 1;
      }
    }
    return -1;
  }
  if (v4)
  {
    v5->deadDevilTalk_log1 = 1;
  }
  else
  {
    wk->deadDevilTalk_log1 = 1;
  }
  return 0;
}

// 0x1f3cf80
void sBtlFirstSummonTextSet(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v4;
  s16 *summonindex;
  s32 v6;
  s32 v7;
  s32 Rand;
  s32 v12;
  SBTLDVLTK_LISTWORK *v14;
  SBTLDVLTK_LISTWORK *v15;
  SBTLUNIT_WORK *v16;
  s32 v17;
  SBTLDVLTK_LISTWORK *dvltkList;
  SBTLDVLTK_LISTWORK *v21;
  SBTLDVLTK_LISTWORK *v23;
  SBTLDVLTK_LISTWORK *v26;
  s32 v27;
  void *Instance;

  v4 = wk;
  summonindex = v4->summonindex;
  v6 = summonindex[0];
  v7 = (u16)summonindex[1];
  if (v6 != -1 && v7 != 0xFFFF)
  {
    if (v4->firstDevilTalk)
      goto LABEL_18;
    Rand = GetRand(2u);
    if (Rand == 1)
    {
      wk->firstDevilTalk = 1;
      return;
    }
  }
LABEL_18:
  if (wk->hitokoto1st)
    return;
  if (main_data->type2 == 2)
    goto LABEL_24;
LABEL_32:
  switch (GetRand(4u))
  {
    case 0u:
      dvltkList = wk->dvltkList;
      v15 = dvltkList;
      v16 = wk;
      v17 = 48;
      goto LABEL_59;
    case 1u:
      v23 = wk->dvltkList;
      v17 = 49;
      goto LABEL_53;
    case 2u:
      v23 = wk->dvltkList;
      v17 = 18;
LABEL_53:
      v15 = v23;
      v16 = wk;
      goto LABEL_59;
    case 3u:
      v26 = wk->dvltkList;
      v15 = v26;
      v16 = wk;
      v17 = 32;
      goto LABEL_59;
    default:
      goto LABEL_60;
  }
  if (main_data->type2 != 2)
    goto LABEL_32;
LABEL_24:
  v12 = GetRand(2u);
  if (v12 == 1)
  {
    v21 = wk->dvltkList;
    v15 = v21;
    v16 = wk;
    v17 = 2;
    goto LABEL_59;
  }
  if (!v12)
  {
    v14 = wk->dvltkList;
    v15 = v14;
    v16 = wk;
    v17 = 1;
LABEL_59:
    sBtlCreateDvltk_Priority(v15, v16, v17);
  }
LABEL_60:
  v27 = get_Instance(0)->frameWait - 60;
  Instance = get_Instance(0);
  SetFrameWait(Instance, v27, 0);
  wk->hitokoto1st = 1;
}

// 0x1f3d360
dds3ProcessFunc_t sBtlExt_CalcProcess(dds3ProcessID_t *PID) {
  dds3ProcessFunc_t v10;
  s64 v13;

  if (!sBtlCreateWork(GlobalUnitWK[GlobalCurrentArray]))
    return 0;
  Proc(pGlobalLWK[GlobalCurrentArray]);
  if ((GlobalStat[GlobalCurrentArray] & 2) != 0)
  {
    if (!sBtlReleaseDvltk_List(pGlobalLWK[GlobalCurrentArray], 1u))
      goto LABEL_14;
  }
  else
  {
    if (!sBtlReleaseDvltk_List(pGlobalLWK[GlobalCurrentArray], 0))
    {
LABEL_14:
      v10 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
      _ctor(v10, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      return v10;
    }
  }
  v13 = (s64)GlobalStat + 4 * GlobalCurrentArray;
  *(u32 *)(v13 + 32) |= 8u;
  return 0;
}

// 0x1f3d530
dds3ProcessFunc_t sBtlExt_DrawProcess(dds3ProcessID_t *PID) {
  dds3ProcessFunc_t v5;

  if (!GlobalPID)
  {
    v5 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
    _ctor(v5, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
    return v5;
  }
  if ((GlobalStat[GlobalCurrentArray] & 8) == 0)
    return 0;
  Draw(pGlobalLWK[GlobalCurrentArray]);
  return 0;
}

// 0x1f3d670
void sBtlExt_Free(s32 ArrayIndex) {
  s64 v6;
  SBTLDVLTK_LISTWORK *v7;
  SBTLUNIT_WORK *v9;
  Il2CppClass **v10;

  if ((GlobalStat[ArrayIndex] & 8) == 0)
    return;
  v6 = ArrayIndex;
  v7 = pGlobalLWK[ArrayIndex];
  sBtlReleaseDvltk_List(v7, 1u);
  v9 = GlobalUnitWK[v6];
  if (v9)
  {
    v9 = GlobalUnitWK[v6];
    ClassMemAlloc(v9, 0);
    v10 = &GlobalUnitWK->obj.klass + v6;
    v10[4] = 0;
  }
  GlobalStat[v6] = 0;
  GlobalCurrentArray = 0;
}

// 0x1f3d820
void sBtlExt_ShutDown(dds3ProcessID_t *PID) {
  if (GlobalCurrentArray)
    goto LABEL_14;
  sBtlExt_Free(0);
  if (!GlobalSpr)
    goto LABEL_14;
  GlobalSpr = 0;
  GlobalSprStat = 0;
LABEL_14:
  GlobalPID = 0;
}

// 0x1f3d950
s32 sBtlExt_CreateBuffer(s32 DevilID, s32 ArrayIndex) {
  s64 v7;
  SBTLDVLTK_LISTWORK *pGlobalLWK_local;
  SBTLDVLTK_LISTWORK *v14;
  SBTLUNIT_WORK *GlobalUnitWK_local;
  SBTLUNIT_WORK *v17;
  Il2CppClass **v18;
  u32 v20;
  SBTLUNIT_WORK *v22;
  s64 v23;
  sdatUnitWork_t *para;
  s32 mapSummonID;
  u32 v27;

  v7 = ArrayIndex;
  if ((GlobalStat[ArrayIndex] & 1) != 0)
  {
    goto LABEL_5;
  }
  pGlobalLWK_local = pGlobalLWK;
  GlobalStat[v7] = 0;
  v14 = Allocate(SBTLDVLTK_LISTWORK);
  _ctor(v14, 0);
  v14->num = 0;
  v14->dwk = 0;
  v18 = &GlobalUnitWK_local->obj.klass + v7;
  v18[4] = v17;
  if (DevilID)
  {
    GlobalUnitWK[v7]->para->devilid = DevilID;
    if (!v20)
    {
LABEL_24:
    }
  }
  else
  {
    para = GlobalUnitWK[v7]->para;
    mapSummonID = GBWK->mapSummonID;
    para->devilid = mapSummonID;
    if (!v27)
      goto LABEL_24;
  }
  v22 = GlobalUnitWK;
  v23 = (s64)GlobalStat + 4 * v7;
  v22[v7]->side |= 1u;
  *(u32 *)(v23 + 32) |= 1u;
LABEL_5:
  if ((GlobalSprStat & 1) != 0)
  {
    goto LABEL_7;
  }
  GlobalSprStat = GlobalSprStat | 1;
LABEL_7:
  if (!GlobalSpr)
    return 0;
  return sBtlCreateWork(GlobalUnitWK[v7]);
}

// 0x1f3dcb0
s32 sBtlExt_FreeBuffer(void) {
  sBtlExt_Free(1);
  sBtlExt_Free(2);
  sBtlExt_Free(3);
  sBtlExt_Free(4);
  if (!GlobalSpr)
    return 1;
  GlobalSpr = 0;
  GlobalSprStat = 0;
  return 1;
}

// 0x1f3de20
s32 sBtlExt_MesReqEx(SBTLDVLTK_MODE Type, s32 ArrayIndex) {
  dds3ProcessFunc_t v8;
  shutdownfuncDelegate v9;
  dds3ProcessID_t *started;
  dds3ProcessFunc_t v13;

  if (!GlobalPID)
  {
    v8 = Allocate(dds3ProcessFunc_t);
    _ctor(v8, 0, Method_Project_sBtlDvltk_Ext_CalcProcess__, 0);
    v9 = Allocate(shutdownfuncDelegate);
    _ctor(v9, 0, Method_Project_sBtlDvltk_Ext_ShutDown__, 0);
    started = dds3StartProcess("dvltkCalc", 1016, 0, 0, v8, v9, 0);
    GlobalPID = started;
    v13 = Allocate(dds3ProcessFunc_t);
    _ctor(v13, 0, Method_Project_sBtlDvltk_Ext_DrawProcess__, 0);
    dds3StartProcess("dvltkDraw", 11020, 0, 0, v13, 0, 0);
  }
  sBtlCreateDvltk(pGlobalLWK[ArrayIndex], GlobalUnitWK[ArrayIndex], Type, 0, 0);
  GlobalCurrentArray = ArrayIndex;
  return 1;
}

// 0x1f3e080
s32 sBtlExt_MesReq(s32 DevilID, SBTLDVLTK_MODE Type) {
  if (!GlobalPID)
    sBtlExt_CreateBuffer(DevilID, 0);
  sBtlExt_MesReqEx(Type, 0);
  return 1;
}

// 0x1f3e150
s32 sBtlExt_EndMes(void) {
  s64 v4;

  if (!GlobalPID)
    return 0;
  v4 = (s64)GlobalStat + 4 * GlobalCurrentArray;
  *(u32 *)(v4 + 32) |= 2u;
  return 1;
}

// 0x1f3e210
s32 sBtlExt_ChkMes(void) {
  return GlobalPID != 0;
}

// 0x1f3e280
s32 sBtlExtCommand_DVLTK_DSP(void) {
  s32 IntPara;
  s32 v3;

  IntPara = scrGetIntPara(0);
  v3 = scrGetIntPara(1);
  if (GlobalPID)
    return 1;
  sBtlExt_MesReq(IntPara, v3);
  return 1;
}

// 0x1f3e370
s32 sBtlExtCommand_DVLTK_WAIT(void) {
  return GlobalPID == 0;
}

// 0x1f3e430
s32 sBtlLoadOnMemMsg(void) {
  s64 v4;
  s64 i;
  void *Asset;
  sdfBinary *v7;
  u8 *data;
  u8 **v9;
  void *Ctrl_k__BackingField;

  Load(Dependent, dvltkAseetName, dvltkAseetName);
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  v4 = 0;
  for (i = 32; ; i += 8)
  {
    if (v4 >= SLODWORD(sbtldvltk_filetbl->max_length))
      break;
    Ctrl_k__BackingField = _Ctrl_k__BackingField;
    Asset = LoadAsset(Ctrl_k__BackingField, dvltkAseetName, *(char **)((char *)&sbtldvltk_filetbl->obj.klass + i), 0);
    v7 = Allocate(sdfBinary);
    _ctor(v7, Asset, 0);
    data = v7->data;
    v9 = ((char *)pGlobalMsg + i);
    *v9 = data;
    ++v4;
  }
  Unload(Dependent, dvltkAseetName, 0);
  return 1;
}

// 0x1f3a4f0
s32 sBtlCheckMsgMemType(void) {
  return 1;
}
