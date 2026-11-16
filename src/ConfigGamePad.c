#include "types.h"
#include "cfg.h"
#include "cmpmain.h"
#include "configgamepad.h"
#include "configunity.h"
#include "dat.h"
#include "dds3_pad.h"
#include "dds3padmanager.h"
#include "libsdf.h"
#include "sbtl.h"

#define DRAW_LIST_MAX 7
#define EX_MAX 3

typedef struct ConfigCursor ConfigCursor;

u16 version;
char *menuText;
char *helpText;
char *prisetText;
s32 **minMaxPar;
s32 *yokoCur;
s32 *skipCnt;
static ConfigCursor *curwk;
static s32 curListMax;
static s32 curDrawMax;
s32 *curSkipCnt;
static s32 *selKeyId;
static bool change_enable;
static s32 *selTbl_a;
static s32 *selTbl_b;
static s32 *tmp_priset;
static s32 **priSet;
bool same_time_flag;
static s32 GP_A1;
static s32 GP_A2;
static s32 GP_C;
static s32 GP_C1;
static s32 GP_C2;
static s32 GP_C3;
static s32 GP_C4;
static s32 GP_C5;
static s32 GP_D;
static s32 GP_F;
static s32 GP_G;
static s32 GP_H;
static s32 GP_H1;
static s32 *group_tbl;
static s32 **duplicatesp_tbl;
static s32 mposidx;
static s32 *mSamePos;

static void ChangeInit(GamePadSet setno);
static bool chkDir(GamePadSet setno, s32 keyid);
static bool chkRevDir(s32 dstkey, s32 keyid);
static void ChangePriSet(s32 priset_no);
static bool IsSameTime(s32 i);
static void ActButtonChange(void);
static SDF_PADMAP GetConfigPadMapBtl(GamePadSet r_id, GamePadSet n_id, bool nakama_f);
static s32 ChangeKeyDuplicateChkNew(s32 _setPos, s32 _yokoPos, s32 _chgKey);
static bool mSamePosSet(s32 src_key, s32 chgkey, s32 index);
static void mSamePosInit(void);
static void ReSetDuplication(s32 _setPos, s32 old_key);
static void SetActionBtn(GamePadSet padset, s32 keyid);

// macros
// 0x18cd760: s32 ABTN(s32 id)
#define ABTN(id) (id << 16)

// 0x18ca1b0
char *ConfigGameGetSelectText(s32 _setPar, s32 _value) {
  char **v7;

  if (!setPar)
    return "CONFIG_MAIN_L0011";
  if (setPar == 1)
  {
    return prisetText[value];
  }
  else
  {
    v7 = &"CONFIG_MAIN_L0009";
    if (!value)
      v7 = &"CONFIG_MAIN_L0010";
    return *v7;
  }
}

// 0x18ca2a0
void ConfigGameInitSelectCnt(void) {
  s32 *v3;
  s32 **v4;
  s32 *v5;
  s32 **v6;
  s32 *v7;
  s32 **v8;
  s32 *v9;
  s32 **v10;
  s32 *v11;

  v3 = NewSpecific(s32, 2u);
  minMaxPar[0] = v3;
  v4 = minMaxPar;
  v5 = NewSpecific(s32, 2u);
  v5[1] = 1;
  v4[1] = v5;
  v6 = minMaxPar;
  v7 = NewSpecific(s32, 2u);
  v7[1] = 4;
  v6[2] = v7;
  v8 = minMaxPar;
  v9 = NewSpecific(s32, 2u);
  v8[10] = v9;
  v9[1] = 1;
  v10 = minMaxPar;
  v11 = NewSpecific(s32, 2u);
  v10[11] = v11;
  v11[1] = 1;
}

// 0x18ca3f0
void ConfigGameInit(void) {
  ConfigCursor *NowCsr;
  ConfigCursor *v5;

  NowCsr = GetNowCsr();
  v4 = (NowCsr->klass->vtable._5_SetMaxPar.methodPtr)(NowCsr, (u32)(LODWORD(skipCnt->max_length) + 36), 7, NowCsr->klass->vtable._5_SetMaxPar.method);
  v5 = GetNowCsr();
  v5->skipCnt = skipCnt;
}

// 0x18ca4e0
void ConfigGameUpdate(void) {
  ConfigCursor *NowCsr;
  s32 setNo;
  s32 v6;
  s32 ConfigData;
  s32 v9;
  s32 v15;
  s64 v17;
  s32 *v19;
  s32 v20;
  s32 v21;
  s32 v23;
  s32 *v25;
  s32 v26;
  s32 v27;

  NowCsr = GetNowCsr();
  setNo = NowCsr->setNo;
  v6 = setNo - 5;
  if ((u32)(setNo - 5) > 0x1E)
    goto LABEL_6;
  goto LABEL_5;
  if ((u32)(setNo - 5) <= 0x1E)
LABEL_5:
    setNo = dword_3E5FDCC[v6];
LABEL_6:
  ConfigData = GetConfigData(NowCsr->setNo);
  v9 = GetConfigData(NowCsr->setNo);
  if (!setNo)
  {
    if (!CHECK_TRIG(4096, 1))
      goto LABEL_18;
    SE(0);
    InitSaveToMessage(0);
    goto LABEL_18;
  }
  if (CsrTopReturn(NowCsr, 0))
    return;
  switch (setNo)
  {
    case 1:
      v19 = minMaxPar[1];
      v20 = v19[0];
      v21 = v19[1];
      if (CHECK_TRIG(4103, 1))
      {
        SE(3);
        if (v9 + 1 <= v21)
          v23 = v9 + 1;
        else
          v23 = v20;
      }
      else
      {
        v23 = v9;
        if (CHECK_TRIG(4102, 1))
        {
          SE(3);
          if (v9 - 1 >= v20)
            v23 = v9 - 1;
          else
            v23 = v21;
        }
      }
      v9 = ConfigData;
      if (v23 != ConfigData)
      {
        if (NowCsr->setNo == 1)
        {
          ChangePriSet(v23);
          v9 = v23;
        }
        else
        {
          v9 = v23;
        }
      }
      break;
    case 2:
      v25 = minMaxPar[2];
      v26 = v25[0];
      v27 = v25[1];
      if (CHECK_REP(4103, 1))
      {
        if (v9 < v27)
        {
          SE(3);
          ++v9;
        }
      }
      else if (CHECK_REP(4102, 1) && v9 > v26)
      {
        SE(3);
        --v9;
      }
      break;
    case 10:
    case 11:
      if (!IsSpecifiedState(1))
      {
        if (!CHECK_TRIG(4103, 1) && !CHECK_TRIG(4102, 1))
        {
          goto LABEL_45;
        }
        SE(3);
        v17 = (s64)yokoCur + 4 * NowCsr->setNo;
        *(u32 *)(v17 + 32) ^= 1u;
      }
      break;
    case 13:
    case 14:
    case 15:
    case 16:
    case 29:
    case 30:
    case 31:
    case 32:
    case 33:
    case 34:
    case 35:
    case 36:
    case 37:
    case 38:
    case 39:
    case 40:
    case 41:
    case 42:
    case 43:
    case 44:
      break;
    default:
      if (!IsSpecifiedState(1))
      {
LABEL_45:
        if (CHECK_TRIG(47875, 1))
        {
          SE(0);
          ChangeInit(setNo);
          ChangeState(2);
        }
      }
      break;
  }
LABEL_18:
  v15 = NowCsr->setNo;
  SetConfigData(v15, v9);
}

// 0x18cafe0
void ConfigGameDraw(void) {
  ConfigCursor *NowCsr;
  u32 setNo;
  u32 v5;
  s32 v11;
  bool v14;

  NowCsr = GetNowCsr();
  setNo = NowCsr->setNo;
  v5 = setNo - 5;
  if (setNo - 5 > 0x1E)
  {
    goto LABEL_6;
  }
  setNo = dword_3E5FDCC[v5];
LABEL_6:
  MenuHelpDraw(instance, NowCsr->setNo, helpText, 0);
  if (setNo - 29 >= 0x10 && (setNo > 0x10 || ((1 << setNo) & 0x1E007) == 0))
  {
    v14 = !IsSpecifiedState(2);
    if (v14)
      v11 = 43;
    else
      v11 = 44;
LABEL_25:
    cmpCmpGuideSet(v11, 0, 90);
    if ((u32)(NowCsr->setNo - 1) < 2)
      return;
    goto LABEL_26;
  }
  if (!IsSpecifiedState(2))
  {
    v11 = 42;
    goto LABEL_25;
  }
  if ((u32)(NowCsr->setNo - 1) < 2)
    return;
LABEL_26:
  ConfigGameChangeDraw();
}

// 0x18ca8f0
GamePadSet ConfigGameGetSetNo_To_GamePadSet(s32 SetNo) {
  if ((u32)(SetNo - 5) <= 0x1E)
    return dword_3E5FDCC[SetNo - 5];
  return SetNo;
}

// 0x18cb470
s32 ConfigGameGamePadSet_To_GetSetNo(GamePadSet padset) {
  s32 v2;

  if (padset <= 97)
  {
    if ((u32)(padset - 5) >= 0x1C)
    {
      if (padset == 97)
        return 12;
    }
    else
    {
      return dword_3E5FE48[padset - 5];
    }
  }
  else
  {
    if (padset == 106)
      v2 = 30;
    else
      v2 = padset;
    if (padset == 103)
      return 20;
    else
      return v2;
  }
  return padset;
}

// 0x18cabc0
static void ChangeInit(GamePadSet setno) {
  s32 **p_selTbl_b;
  s32 *v7;
  il2cpp_array_size_t max_length;
  s32 *v9;
  s64 v12;
  s32 v13;
  s32 *m_Items;
  s64 v16;
  s32 v17;

  curDrawMax = 12;
  if ((u32)(setno - 3) > 1)
  {
    p_selTbl_b = &selTbl_b;
  }
  else
  {
    p_selTbl_b = &selTbl_a;
  }
  v7 = *p_selTbl_b;
  max_length = (*p_selTbl_b)->max_length;
  curListMax = max_length;
  max_length = v7->max_length;
  curListMax = 0;
  v9 = NewSpecific(s32, max_length);
  selKeyId = v9;
  if (SLODWORD(v7->max_length) >= 1)
  {
    v12 = 0;
    v13 = 0;
    m_Items = v7;
    do
    {
      v17 = m_Items[v12];
      if (chkDir(setno, v17))
      {
        v16 = (s64)selKeyId + 4 * v13++;
        *(u32 *)(v16 + 32) = m_Items[v12];
        ++curListMax;
      }
      ++v12;
    }
    while (v12 < SLODWORD(v7->max_length));
  }
  (curwk->klass->vtable._4_CsrClear.methodPtr)(curwk, curwk->klass->vtable._4_CsrClear.method);
  (curwk->klass->vtable._5_SetMaxPar.methodPtr)(curwk, (u32)curListMax, (u32)curDrawMax, curwk->klass->vtable._5_SetMaxPar.method);
  change_enable = 1;
  ButtonSeleDisp(instance, 1, 0);
  ConfigGameChangeDraw();
  ButtonSeleCur(instance, 0, 0);
}

// 0x18cb4c0
static bool chkDir(GamePadSet setno, s32 keyid) {
  bool result;
  s32 v7;
  s32 ConfigData;
  s32 v12;
  u16 v19;
  s32 v20;
  s32 v21;
  u16 v24;
  u16 v30;
  s32 v31;
  s32 v32;
  u16 v35;
  u16 v39;
  s32 v40;
  s32 v41;
  u16 v44;
  s32 ConfigDataLw;
  s32 v54;
  s32 v59;
  s32 v65;

  result = 1;
  switch (setno)
  {
    case 10:
    case 11:
      if (yokoCur[setno])
      {
        ConfigData = GetConfigData(setno) >> 16;
        goto LABEL_17;
      }
      ConfigData = (u16)GetConfigData(setno);
      goto LABEL_17;
    case 12:
      v19 = GetConfigData(13);
      if (keyid)
        v20 = -1;
      else
        v20 = 1;
      if (keyid == 1)
        v20 = 0;
      if (keyid == 2)
        v20 = 3;
      if (keyid == 3)
        v20 = 2;
      if (keyid == 4)
        v20 = 5;
      if (keyid == 5)
        v20 = 4;
      if (keyid == 6)
        v20 = 7;
      if (keyid == 7)
        v20 = 6;
      if (keyid == 8)
        v20 = 9;
      if (keyid == 9)
        v20 = 8;
      if (keyid == 10)
        v20 = 11;
      if (keyid == 11)
        v21 = 10;
      else
        v21 = v20;
      if (v21 != -1)
      {
        result = 0;
        if (v21 == v19)
          return result;
      }
      v24 = GetConfigData(14);
      if (v21 != -1)
      {
        if (v21 == v24)
          return 0;
      }
      ConfigDataLw = GetConfigDataLw(15);
      if (!chkRevDir(ConfigDataLw, keyid))
        return 0;
      v65 = GetConfigDataLw(16);
      return chkRevDir(v65, keyid);
    case 13:
    case 14:
    case 15:
    case 16:
      v7 = 12;
      goto LABEL_16;
    case 17:
      v7 = 18;
      goto LABEL_16;
    case 18:
      v7 = 17;
      goto LABEL_16;
    case 19:
      v30 = GetConfigData(20);
      if (keyid)
        v31 = -1;
      else
        v31 = 1;
      if (keyid == 1)
        v31 = 0;
      if (keyid == 2)
        v31 = 3;
      if (keyid == 3)
        v31 = 2;
      if (keyid == 4)
        v31 = 5;
      if (keyid == 5)
        v31 = 4;
      if (keyid == 6)
        v31 = 7;
      if (keyid == 7)
        v31 = 6;
      if (keyid == 8)
        v31 = 9;
      if (keyid == 9)
        v31 = 8;
      if (keyid == 10)
        v31 = 11;
      if (keyid == 11)
        v32 = 10;
      else
        v32 = v31;
      if (v32 != -1)
      {
        result = 0;
        if (v32 == v30)
          return result;
      }
      v35 = GetConfigData(21);
      if (v32 != -1)
      {
        if (v32 == v35)
          return 0;
      }
      v59 = GetConfigDataLw(22);
      if (!chkRevDir(v59, keyid))
        return 0;
      v65 = GetConfigDataLw(23);
      return chkRevDir(v65, keyid);
    case 20:
    case 21:
    case 22:
    case 23:
      v7 = 19;
      goto LABEL_16;
    case 28:
      v39 = GetConfigData(29);
      if (keyid)
        v40 = -1;
      else
        v40 = 1;
      if (keyid == 1)
        v40 = 0;
      if (keyid == 2)
        v40 = 3;
      if (keyid == 3)
        v40 = 2;
      if (keyid == 4)
        v40 = 5;
      if (keyid == 5)
        v40 = 4;
      if (keyid == 6)
        v40 = 7;
      if (keyid == 7)
        v40 = 6;
      if (keyid == 8)
        v40 = 9;
      if (keyid == 9)
        v40 = 8;
      if (keyid == 10)
        v40 = 11;
      if (keyid == 11)
        v41 = 10;
      else
        v41 = v40;
      if (v41 != -1)
      {
        result = 0;
        if (v41 == v39)
          return result;
      }
      v44 = GetConfigData(30);
      if (v41 != -1)
      {
        if (v41 == v44)
          return 0;
      }
      v54 = GetConfigDataLw(31);
      if (!chkRevDir(v54, keyid))
        return 0;
      v65 = GetConfigDataLw(32);
      return chkRevDir(v65, keyid);
    case 29:
    case 30:
    case 31:
    case 32:
      v7 = 28;
LABEL_16:
      ConfigData = (u16)GetConfigData(v7);
LABEL_17:
      if (keyid)
        v12 = -1;
      else
        v12 = 1;
      if (keyid == 1)
        v12 = 0;
      if (keyid == 2)
        v12 = 3;
      if (keyid == 3)
        v12 = 2;
      if (keyid == 4)
        v12 = 5;
      if (keyid == 5)
        v12 = 4;
      if (keyid == 6)
        v12 = 7;
      if (keyid == 7)
        v12 = 6;
      if (keyid == 8)
        v12 = 9;
      if (keyid == 9)
        v12 = 8;
      if (keyid == 10)
        v12 = 11;
      if (keyid == 11)
        v12 = 10;
      return v12 == -1 || v12 != ConfigData;
    default:
      return result;
  }
}

// 0x18cc1e0
static bool chkRevDir(s32 dstkey, s32 keyid) {
  s32 v3;

  if (keyid)
    v3 = -1;
  else
    v3 = 1;
  if (keyid == 1)
    v3 = 0;
  if (keyid == 2)
    v3 = 3;
  if (keyid == 3)
    v3 = 2;
  if (keyid == 4)
    v3 = 5;
  if (keyid == 5)
    v3 = 4;
  if (keyid == 6)
    v3 = 7;
  if (keyid == 7)
    v3 = 6;
  if (keyid == 8)
    v3 = 9;
  if (keyid == 9)
    v3 = 8;
  if (keyid == 10)
    v3 = 11;
  if (keyid == 11)
    v3 = 10;
  return v3 == -1 || v3 != dstkey;
}

// 0x18cc280
bool ConfigGameChange(void) {
  ConfigCursor *NowCsr;
  s64 i;
  char *v7;
  _BOOL4 v9;
  s32 setNo;
  s32 v14;
  s32 v15;
  s32 ConfigData;
  s32 v19;
  s32 v20;
  s32 v21;
  s32 v24;
  s64 v26;
  s32 v28;
  u16 v29;
  s32 v31;
  s32 v32;
  bool v33;
  bool v34;
  bool v36;
  bool v37;
  s32 v38;
  s32 v39;
  s32 v40;
  s32 v45;
  s32 v46;
  s32 v47;
  s32 v49;
  s32 v50;
  u16 v52;
  u16 v56;
  u32 v61;
  void *v67;

  if (CHECK_TRIG(4096, 1))
  {
    NowCsr = GetNowCsr();
    for (i = 0; ; ++i)
    {
      if (i >= SLODWORD(mSamePos->max_length))
        break;
      v7 = (char *)mSamePos + 4 * i;
      *((u32 *)v7 + 8) = 0;
    }
    setNo = NowCsr->setNo;
    if ((setNo & 0xFFFFFFFE) == 0xA)
    {
      v14 = NowCsr->setNo;
      v15 = selKeyId[curwk->csrNo];
      ConfigData = GetConfigData(v14);
      v19 = NowCsr->setNo;
      v20 = ConfigData;
      v21 = v20 >> 16;
      v24 = (u16)GetConfigData(v19);
      v26 = NowCsr->setNo;
      if (yokoCur[v26])
      {
        if (v15 == v21)
        {
          SetConfigDataLw(v26, v15);
          v28 = NowCsr->setNo;
          v29 = GetConfigData(v28);
          v31 = v28;
          v32 = v29 | ((u16)v24 << 16);
LABEL_83:
          SetConfigData(v31, v32);
          v9 = 1;
          goto LABEL_85;
        }
LABEL_46:
        v38 = v26;
        ChangeKeyDuplicateChkNew(v26, yokoCur[v38], selKeyId[curwk->csrNo]);
        v39 = NowCsr->setNo;
        v40 = mSamePos[0];
        SE(0);
        if (v40 == v39)
        {
          v45 = NowCsr->setNo;
          v46 = selKeyId[curwk->csrNo];
          if ((v45 & 0xFFFFFFFE) == 0xA)
          {
            v45 = NowCsr->setNo;
            v47 = yokoCur[v45];
            if (v47)
            {
              v49 = v45;
              v50 = v46;
LABEL_71:
              SetConfigDataLw(v49, v50);
              v9 = 1;
              goto LABEL_85;
            }
            v56 = GetConfigData(v45);
            v31 = v45;
            v32 = v56 | ((u16)v46 << 16);
            goto LABEL_83;
          }
          SetConfigDataLw(v45, v46);
          ActButtonChange();
          v9 = 1;
        }
        else
        {
          v9 = 1;
          InitMessage(3, 1);
        }
        goto LABEL_85;
      }
      if (v15 != v24)
        goto LABEL_46;
      v52 = GetConfigData(v26);
      SetConfigData(v26, v52 | ((u16)v15 << 16));
      v49 = NowCsr->setNo;
      v50 = v21;
      goto LABEL_71;
    }
    LODWORD(v26) = NowCsr->setNo;
    goto LABEL_46;
  }
  if (CHECK_TRIG(4097, 1))
  {
    v9 = 1;
    SE(1);
    goto LABEL_85;
  }
  v33 = CHECK_TRIG(4100, 1);
  v34 = CHECK_REP(4100, 1);
  (curwk->klass->vtable._7_CsrUp.methodPtr)(curwk, v33, v34, curwk->klass->vtable._7_CsrUp.method);
  v36 = CHECK_TRIG(4101, 1);
  v37 = CHECK_REP(4101, 1);
  (curwk->klass->vtable._8_CsrDown.methodPtr)(&curwk->klass, curwk, v36, v37, curwk->klass->vtable._8_CsrDown.method);
  v9 = 0;
LABEL_85:
  ButtonSeleCur(instance, curwk->csrNo, 0);
  if (!v9)
  {
    if (v61)
    {
      goto LABEL_97;
    }
    else
    {
LABEL_97:
      goto LABEL_98;
    }
LABEL_98:
    v67 = instance;
    ButtonSeleMenuScloll(v67, curListMax, curDrawMax, curwk->listTop, 0);
    return v9;
  }
  if (v61)
  {
    goto LABEL_91;
  }
LABEL_91:
  ButtonSeleDisp(instance, 0, 0);
  change_enable = 0;
  return v9;
}

// 0x18cb290
void ConfigGameChangeDraw(void) {
  s64 i;
  void *Instance;
  void *ButtonImage;

  if (change_enable)
  {
    for (i = 0; ; ++i)
    {
      if (i >= curListMax)
        return;
      Instance = get_Instance(0);
      ButtonImage = GetButtonImage(Instance, 0, selKeyId[i], 0);
      ButtonSelePadButtonSet(instance, i, ButtonImage, 0);
    }
  }
}

// 0x18c3930
s32 *ConfigGameGetPriSet(s32 priset_no) {
  s32 ButtonArrangement;
  s64 i;
  s64 v6;
  s32 *v8;
  s32 *v10;
  s32 v11;
  s32 *v13;

  ButtonArrangement = dds3PadGetButtonArrangement();
  for (i = 8; ; ++i)
  {
    v8 = priSet[priset_no];
    if (i - 8 >= v8[6])
      break;
    v8 = priSet[priset_no];
    v6 = i;
    *(u32 *)((char *)&tmp_priset->obj.klass + v6 * 4) = v8[v6];
  }
  if (ButtonArrangement)
  {
    if ((u32)(ButtonArrangement - 3) >= 0xFFFFFFFE)
    {
      v8 = priSet[priset_no];
      tmp_priset[3] = v8[12];
      tmp_priset[4] = v8[11];
    }
    v10 = tmp_priset;
    v11 = v10[3];
    v10[84] = v11;
    v10[121] = v11;
    v10[124] = v11;
    v10[132] = v11;
    return tmp_priset;
  }
  else
  {
    v8 = priSet[priset_no];
    v13 = tmp_priset;
    v13[3] = v8[11];
    v13[4] = v8[12];
    return tmp_priset;
  }
  return tmp_priset;
}

// 0x18ca920
static void ChangePriSet(s32 priset_no) {
  s32 *PriSet;
  s32 *v7;
  u32 *v8;
  u32 v9;
  s32 v10;
  signed s32 v11;
  s32 v12;
  u32 v13;

  PriSet = ConfigGameGetPriSet(priset_no);
  if (SLODWORD(PriSet->max_length) >= 4)
  {
    v7 = PriSet;
    v8 = &dword_3E5FDA0[9];
    v9 = -2;
    do
    {
      v12 = v9 + 5;
      v13 = v9 + 5;
      if (v9 <= 0x1E)
        goto LABEL_15;
      goto LABEL_9000;
      if (v9 <= 0x1E)
LABEL_15:
        v13 = *v8;
LABEL_9000:
      v10 = v7[v13];
      SetConfigData(v12, v10);
      v11 = v9 + 6;
      ++v8;
      ++v9;
    }
    while (v11 < SLODWORD(v7->max_length));
  }
}

// 0x18cca90
static bool IsSameTime(s32 i) {
  if (i == 10)
    return 1;
  return i == 11;
}

// 0x18cd770
bool ConfigGameIsCtrl(s32 i) {
  s32 v2;
  bool result;

  v2 = i - 33;
  result = 1;
  switch (v2)
  {
    case 0:
    case 1:
    case 2:
    case 3:
    case 14:
    case 15:
    case 36:
    case 37:
    case 52:
    case 53:
    case 54:
    case 55:
    case 81:
    case 82:
      return result;
    default:
      result = 0;
      break;
  }
  return result;
}

// 0x18cd460
static void ActButtonChange(void) {
  u16 ConfigData;
  u16 v9;
  s32 v11;
  s32 v13;
  s32 v14;
  s32 v29;

  ConfigData = GetConfigData(13);
  v9 = GetConfigData(21);
  v11 = ConfigData;
  v13 = (u16)GetConfigData(31);
  v14 = (u16)GetConfigData(18);
  SetActionBtn(13, v11);
  SetActionBtn(14, v11);
  SetActionBtn(15, v11);
  SetActionBtn(16, v11);
  SetActionBtn(20, v9);
  SetActionBtn(21, v9);
  SetActionBtn(22, v9);
  SetActionBtn(23, v9);
  SetActionBtn(29, v13);
  SetActionBtn(30, v13);
  SetActionBtn(31, v13);
  SetActionBtn(32, v13);
  SetActionBtn(18, v14);
  v29 = (u16)GetConfigData(3);
  SetConfigDataLw(84, v29);
  SetConfigDataLw(121, v29);
  SetConfigDataLw(124, v29);
  SetConfigDataLw(132, v29);
}

// 0x18ca910
bool ConfigGameNotSetChk(void) {
  return 1;
}

// 0x18cda30
void ConfigGameSetSameTimeKey(bool _active) {
  same_time_flag = active;
}

// 0x18cdaa0
SDF_PADMAP ConfigGameGetCmnTypeCD(SDF_PADMAP id) {
  if (!GBWK)
    return id;
  if ((GBWK->config_data[3][1] & 0xFFFFFFFE) != 2)
    return id;
  if (id == 4099)
    return 4102;
  if (id == 4098)
    return 4100;
  return id;
}

// 0x18c1880
SDF_PADMAP ConfigGameGetConfigPadMap(SDF_PADMAP id, bool nakama_f) {
  s32 v11;
  dds3GlobalWork_t *v13;
  bool v14;
  s32 v15;
  s32 v16;
  s32 result;
  dds3GlobalWork_t *v19;
  dds3GlobalWork_t *v21;
  s32 ConfigGAMEPAD;
  u16 v25;
  s32 v28;
  s32 v30;
  s32 v31;
  dds3GlobalWork_t *v33;
  dds3GlobalWork_t *v35;
  dds3GlobalWork_t *v37;
  dds3GlobalWork_t *v39;
  dds3GlobalWork_t *v41;
  dds3GlobalWork_t *v43;
  dds3GlobalWork_t *v45;
  dds3GlobalWork_t *v47;
  dds3GlobalWork_t *v49;
  dds3GlobalWork_t *v51;
  dds3GlobalWork_t *v53;
  dds3GlobalWork_t *v55;
  dds3GlobalWork_t *v57;
  dds3GlobalWork_t *v59;
  s32 v60;

  if (!GBWK)
  {
LABEL_17:
    if (id > 24579)
    {
      switch (id)
      {
        case 24580:
          goto LABEL_37;
        case 24581:
          goto LABEL_43;
        case 24582:
          goto LABEL_59;
        case 24583:
          goto LABEL_62;
        case 24584:
        case 24585:
        case 24586:
        case 24588:
          goto LABEL_115;
        case 24587:
          goto LABEL_65;
        case 24589:
          goto LABEL_68;
        default:
          switch (id)
          {
            case 28672:
              goto LABEL_20;
            case 28673:
              goto LABEL_81;
            case 28674:
              goto LABEL_92;
            case 28675:
              goto LABEL_101;
            case 28676:
            case 28677:
            case 28678:
            case 28679:
            case 28680:
            case 28681:
            case 28682:
            case 28683:
              goto LABEL_115;
            case 28684:
              goto LABEL_112;
            default:
              if (id == 42510)
                goto LABEL_72;
              goto LABEL_115;
          }
      }
    }
    switch (id)
    {
      case 20480:
        goto LABEL_48;
      case 20481:
        goto LABEL_136;
      case 20482:
        goto LABEL_141;
      case 20483:
        goto LABEL_144;
      case 20484:
        goto LABEL_147;
      case 20485:
        goto LABEL_150;
      case 20486:
        goto LABEL_153;
      case 20487:
        goto LABEL_158;
      case 20488:
        goto LABEL_161;
      case 20489:
        goto LABEL_164;
      case 20490:
        goto LABEL_169;
      case 20491:
      case 20493:
LABEL_115:
        switch (id)
        {
          case 32768:
            goto LABEL_116;
          case 32770:
            goto LABEL_242;
          case 32771:
            goto LABEL_245;
          case 32772:
            goto LABEL_248;
          case 32773:
            goto LABEL_251;
          case 32774:
            goto LABEL_254;
          case 32775:
            goto LABEL_257;
          case 32776:
            goto LABEL_260;
          case 32779:
            goto LABEL_263;
          case 32781:
            goto LABEL_266;
          default:
            goto LABEL_273;
        }
      case 20492:
        goto LABEL_172;
      case 20494:
        goto LABEL_72;
      case 20495:
        goto LABEL_177;
      default:
        switch (id)
        {
          case 8194:
            goto LABEL_31;
          case 8195:
            goto LABEL_180;
          case 8196:
          case 8197:
          case 8198:
          case 8199:
            goto LABEL_115;
          case 8200:
            goto LABEL_185;
          case 8201:
            goto LABEL_190;
          case 8202:
            goto LABEL_195;
          case 8203:
            goto LABEL_200;
          case 8204:
            goto LABEL_205;
          case 8205:
            goto LABEL_210;
          case 8206:
            goto LABEL_215;
          case 8207:
            goto LABEL_220;
          default:
            switch (id)
            {
              case 4096:
                goto LABEL_54;
              case 4097:
                goto LABEL_225;
              case 4100:
                goto LABEL_230;
              case 4101:
                goto LABEL_233;
              case 4102:
                goto LABEL_236;
              case 4103:
                goto LABEL_239;
              default:
                goto LABEL_115;
            }
        }
    }
  }
  if ((GBWK->config_data[3][1] & 0xFFFFFFFE) != 2)
    goto LABEL_17;
  if (id <= 24579)
  {
    switch (id)
    {
      case 20480:
LABEL_48:
        v14 = nakama_f;
        v16 = 26;
        v15 = 8;
        goto LABEL_40;
      case 20481:
LABEL_136:
        v33 = GBWK;
        if (!v33)
          goto LABEL_384;
        v33 = GBWK;
        ConfigGAMEPAD = v33->config_data[3][7];
        goto LABEL_385;
      case 20482:
LABEL_141:
        v14 = nakama_f;
        v16 = 25;
        v15 = 6;
        goto LABEL_40;
      case 20483:
LABEL_144:
        v14 = nakama_f;
        v15 = 5;
        v16 = 24;
        goto LABEL_40;
      case 20484:
LABEL_147:
        v31 = 98;
        goto LABEL_269;
      case 20485:
LABEL_150:
        v31 = 100;
        goto LABEL_269;
      case 20486:
LABEL_153:
        v35 = GBWK;
        if (!v35)
          goto LABEL_384;
        v35 = GBWK;
        ConfigGAMEPAD = v35->config_data[3][101];
        goto LABEL_385;
      case 20487:
LABEL_158:
        v31 = 102;
        goto LABEL_269;
      case 20488:
LABEL_161:
        v14 = nakama_f;
        v15 = 9;
        v16 = 27;
        goto LABEL_40;
      case 20489:
LABEL_164:
        v37 = GBWK;
        if (!v37)
          goto LABEL_384;
        v37 = GBWK;
        ConfigGAMEPAD = v37->config_data[3][17];
        goto LABEL_385;
      case 20490:
LABEL_169:
        v31 = 103;
        goto LABEL_269;
      case 20491:
      case 20493:
        goto LABEL_273;
      case 20492:
LABEL_172:
        v39 = GBWK;
        if (!v39)
          goto LABEL_384;
        goto LABEL_309;
        if (!v39)
        {
LABEL_384:
          ConfigGAMEPAD = 0;
          goto LABEL_385;
        }
LABEL_309:
        v39 = GBWK;
        ConfigGAMEPAD = v39->config_data[3][18];
        goto LABEL_385;
      case 20494:
        goto LABEL_72;
      case 20495:
LABEL_177:
        v14 = nakama_f;
        v15 = 99;
        v16 = 107;
        goto LABEL_40;
      default:
        switch (id)
        {
          case 8194:
LABEL_31:
            v13 = GBWK;
            if (!v13)
              goto LABEL_384;
            v13 = GBWK;
            ConfigGAMEPAD = v13->config_data[3][51];
            goto LABEL_385;
          case 8195:
LABEL_180:
            v41 = GBWK;
            if (!v41)
              goto LABEL_384;
            v41 = GBWK;
            ConfigGAMEPAD = v41->config_data[3][57];
            goto LABEL_385;
          case 8196:
          case 8197:
          case 8198:
          case 8199:
            goto LABEL_273;
          case 8200:
LABEL_185:
            v43 = GBWK;
            if (!v43)
              goto LABEL_384;
            v43 = GBWK;
            ConfigGAMEPAD = v43->config_data[3][53];
            goto LABEL_385;
          case 8201:
LABEL_190:
            v45 = GBWK;
            if (!v45)
              goto LABEL_384;
            v45 = GBWK;
            ConfigGAMEPAD = v45->config_data[3][56];
            goto LABEL_385;
          case 8202:
LABEL_195:
            v47 = GBWK;
            if (!v47)
              goto LABEL_384;
            v47 = GBWK;
            ConfigGAMEPAD = v47->config_data[3][55];
            goto LABEL_385;
          case 8203:
LABEL_200:
            v49 = GBWK;
            if (!v49)
              goto LABEL_384;
            v49 = GBWK;
            ConfigGAMEPAD = v49->config_data[3][58];
            goto LABEL_385;
          case 8204:
LABEL_205:
            v51 = GBWK;
            if (!v51)
              goto LABEL_384;
            v51 = GBWK;
            ConfigGAMEPAD = v51->config_data[3][54];
            goto LABEL_385;
          case 8205:
LABEL_210:
            v53 = GBWK;
            if (!v53)
              goto LABEL_384;
            v53 = GBWK;
            ConfigGAMEPAD = v53->config_data[3][59];
            goto LABEL_385;
          case 8206:
LABEL_215:
            v55 = GBWK;
            if (!v55)
              goto LABEL_384;
            v55 = GBWK;
            ConfigGAMEPAD = v55->config_data[3][50];
            goto LABEL_385;
          case 8207:
LABEL_220:
            v57 = GBWK;
            if (!v57)
              goto LABEL_384;
            v57 = GBWK;
            ConfigGAMEPAD = v57->config_data[3][52];
            goto LABEL_385;
          default:
            switch (id)
            {
              case 4096:
LABEL_54:
                v19 = GBWK;
                if (!v19)
                  goto LABEL_384;
                v19 = GBWK;
                ConfigGAMEPAD = v19->config_data[3][3];
                goto LABEL_385;
              case 4097:
LABEL_225:
                v59 = GBWK;
                if (!v59)
                  goto LABEL_384;
                v59 = GBWK;
                ConfigGAMEPAD = v59->config_data[3][4];
LABEL_385:
                return dds3PadGetKeyIDToPadMap(ConfigGAMEPAD);
              case 4098:
                v60 = 4098;
                return ConfigGameGetCmnTypeCD(v60);
              case 4099:
                v60 = 4099;
                return ConfigGameGetCmnTypeCD(v60);
              case 4100:
LABEL_230:
                v31 = 33;
                goto LABEL_269;
              case 4101:
LABEL_233:
                v31 = 34;
                goto LABEL_269;
              case 4102:
LABEL_236:
                v31 = 35;
                goto LABEL_269;
              case 4103:
LABEL_239:
                v31 = 36;
                goto LABEL_269;
              default:
                goto LABEL_273;
            }
        }
    }
  }
  if (id >= 0x8000)
  {
    switch (id)
    {
      case 32768:
LABEL_116:
        v31 = 26;
        goto LABEL_269;
      case 32769:
      case 32777:
      case 32778:
      case 32780:
        goto LABEL_273;
      case 32770:
LABEL_242:
        v31 = 25;
        goto LABEL_269;
      case 32771:
LABEL_245:
        v31 = 24;
        goto LABEL_269;
      case 32772:
LABEL_248:
        v31 = 104;
        goto LABEL_269;
      case 32773:
LABEL_251:
        v31 = 105;
        goto LABEL_269;
      case 32774:
LABEL_254:
        v31 = 29;
        goto LABEL_269;
      case 32775:
LABEL_257:
        v31 = 30;
        goto LABEL_269;
      case 32776:
LABEL_260:
        v31 = 27;
        goto LABEL_269;
      case 32779:
LABEL_263:
        v31 = 28;
        goto LABEL_269;
      case 32781:
LABEL_266:
        v31 = 106;
        goto LABEL_269;
      default:
        if (id != 42510)
        {
LABEL_273:
          if (id > 42497)
          {
            if (id > 45570)
            {
              if (id <= 46594)
              {
                if (id <= 46082)
                {
                  switch (id)
                  {
                    case 45571:
                      v31 = 74;
                      break;
                    case 45826:
                      v31 = 76;
                      break;
                    case 46082:
                      v31 = 118;
                      break;
                    default:
                      goto LABEL_570;
                  }
                }
                else if (id > 46338)
                {
                  if (id == 46339)
                  {
                    v31 = 120;
                  }
                  else
                  {
                    if (id != 46594)
                      goto LABEL_570;
                    v31 = 122;
                  }
                }
                else if (id == 46083)
                {
                  v31 = 117;
                }
                else
                {
                  if (id != 46338)
                    goto LABEL_570;
                  v31 = 119;
                }
              }
              else if (id > 47106)
              {
                if (id > 47618)
                {
                  if (id == 47619)
                  {
                    v31 = 65;
                  }
                  else
                  {
                    if (id != 47875)
                      goto LABEL_570;
                    v31 = 67;
                  }
                }
                else if (id == 47107)
                {
                  v31 = 129;
                }
                else
                {
                  if (id != 47362)
                    goto LABEL_570;
                  v31 = 128;
                }
              }
              else if (id > 46850)
              {
                if (id == 46851)
                {
                  v31 = 126;
                }
                else
                {
                  if (id != 47106)
                    goto LABEL_570;
                  v31 = 127;
                }
              }
              else if (id == 46595)
              {
                v31 = 123;
              }
              else
              {
                if (id != 46850)
                  goto LABEL_570;
                v31 = 125;
              }
            }
            else if (id <= 43533)
            {
              if (id > 43525)
              {
                if (id == 43526)
                {
                  v31 = 47;
                }
                else
                {
                  if (id != 43527)
                    goto LABEL_570;
                  v31 = 48;
                }
              }
              else
              {
                switch (id)
                {
                  case 42752:
                    v31 = 121;
                    break;
                  case 42753:
                  case 42754:
                  case 42755:
                  case 42758:
                  case 42759:
                  case 42760:
                  case 42761:
                  case 42762:
                  case 42763:
                  case 42764:
                  case 42765:
                    goto LABEL_570;
                  case 42756:
                    v31 = 114;
                    break;
                  case 42757:
                    v31 = 115;
                    break;
                  case 42766:
                    v31 = 116;
                    break;
                  default:
                    if (id != 42498)
                      goto LABEL_570;
                    v31 = 109;
                    break;
                }
              }
            }
            else if (id > 45313)
            {
              switch (id)
              {
                case 45314:
                  v31 = 73;
                  break;
                case 45315:
                  v31 = 75;
                  break;
                case 45327:
                  v31 = 66;
                  break;
                default:
                  goto LABEL_570;
              }
            }
            else
            {
              switch (id)
              {
                case 45056:
                  v31 = 124;
                  break;
                case 45057:
                case 45060:
                case 45061:
                case 45062:
                case 45063:
                case 45064:
                case 45065:
                case 45066:
                case 45067:
                case 45068:
                case 45069:
                case 45070:
                  goto LABEL_570;
                case 45058:
                  v31 = 71;
                  break;
                case 45059:
                  v31 = 72;
                  break;
                case 45071:
                  v31 = 64;
                  break;
                default:
                  if (id != 43534)
                    goto LABEL_570;
                  v31 = 49;
                  break;
              }
            }
          }
          else
          {
            if (id > 41729)
            {
              switch (id)
              {
                case 42242:
                  v31 = 95;
                  goto LABEL_269;
                case 42243:
                  v31 = 96;
                  goto LABEL_269;
                case 42244:
                  v31 = 85;
                  goto LABEL_269;
                case 42245:
                  v31 = 86;
                  goto LABEL_269;
                case 42246:
                  v31 = 87;
                  goto LABEL_269;
                case 42247:
                  v31 = 88;
                  goto LABEL_269;
                case 42248:
                  v31 = 94;
                  goto LABEL_269;
                case 42249:
                  v31 = 92;
                  goto LABEL_269;
                case 42250:
                case 42251:
                case 42254:
                case 42255:
                case 42256:
                case 42257:
                case 42258:
                case 42259:
                  goto LABEL_570;
                case 42252:
                  v31 = 93;
                  goto LABEL_269;
                case 42253:
                  v31 = 91;
                  goto LABEL_269;
                case 42260:
                  v31 = 89;
                  goto LABEL_269;
                case 42261:
                  v31 = 90;
                  goto LABEL_269;
                default:
                  switch (id)
                  {
                    case 41730:
                      v31 = 80;
                      goto LABEL_269;
                    case 41731:
                    case 41732:
                    case 41733:
                    case 41734:
                    case 41735:
                    case 41736:
                    case 41737:
                    case 41738:
                    case 41739:
                    case 41740:
                    case 41742:
                    case 41743:
                    case 41744:
                    case 41745:
                    case 41746:
                    case 41747:
                    case 41748:
                    case 41749:
                      goto LABEL_570;
                    case 41741:
                      v31 = 77;
                      goto LABEL_269;
                    case 41750:
                      v31 = 78;
                      goto LABEL_269;
                    case 41751:
                      v31 = 79;
                      goto LABEL_269;
                    default:
                      switch (id)
                      {
                        case 41984:
                          v31 = 84;
                          goto LABEL_269;
                        case 41999:
                          v31 = 83;
                          goto LABEL_269;
                        case 42004:
                          v31 = 81;
                          goto LABEL_269;
                        case 42005:
                          v31 = 82;
                          goto LABEL_269;
                        default:
                          goto LABEL_570;
                      }
                  }
              }
            }
            if (id > 40961)
            {
              if (id > 41475)
              {
                if (id == 41476)
                {
                  v31 = 69;
                }
                else
                {
                  if (id != 41477)
                    goto LABEL_570;
                  v31 = 70;
                }
              }
              else
              {
                switch (id)
                {
                  case 41218:
                    v31 = 63;
                    break;
                  case 41219:
                  case 41220:
                  case 41221:
                  case 41222:
                  case 41223:
                  case 41224:
                  case 41225:
                  case 41226:
                  case 41227:
                  case 41228:
                  case 41229:
                  case 41231:
                  case 41232:
                  case 41233:
                  case 41234:
                  case 41235:
                    goto LABEL_570;
                  case 41230:
                    v31 = 68;
                    break;
                  case 41236:
                    v31 = 61;
                    break;
                  case 41237:
                    v31 = 62;
                    break;
                  default:
                    if (id != 40962)
                      goto LABEL_570;
                    v31 = 60;
                    break;
                }
              }
            }
            else
            {
              if (id > 36865)
              {
                switch (id)
                {
                  case 36866:
                    v31 = 110;
                    goto LABEL_269;
                  case 36867:
                    v31 = 111;
                    goto LABEL_269;
                  case 36877:
                    v31 = 113;
                    goto LABEL_269;
                  case 36878:
                    v31 = 112;
                    goto LABEL_269;
                  default:
                    goto LABEL_570;
                }
              }
              switch (id)
              {
                case 4104:
                  v31 = 45;
                  break;
                case 4107:
                  v31 = 46;
                  break;
                case 32783:
                  v31 = 107;
                  break;
                default:
LABEL_570:
                  if (id <= 45311)
                  {
                    switch (id)
                    {
                      case 43266:
                        v31 = 134;
                        goto LABEL_269;
                      case 43267:
                        v31 = 133;
                        goto LABEL_269;
                      case 43268:
                      case 43269:
                      case 43270:
                      case 43271:
                      case 43272:
                      case 43273:
                      case 43274:
                      case 43276:
                      case 43277:
                      case 43278:
                      case 43279:
                      case 43280:
                      case 43281:
                      case 43282:
                      case 43283:
                        goto LABEL_639;
                      case 43275:
                        v31 = 135;
                        goto LABEL_269;
                      case 43284:
                        v31 = 136;
                        goto LABEL_269;
                      case 43285:
                        v31 = 137;
                        goto LABEL_269;
                      default:
                        if (id != 43021)
                          goto LABEL_639;
                        v31 = 131;
                        break;
                    }
                    break;
                  }
                  if (id > 47374)
                  {
                    if (id == 47375)
                      return 4111;
                    if (id == 48130)
                      return 4098;
                  }
                  else
                  {
                    if (id == 45312)
                    {
                      v31 = 132;
                      break;
                    }
                    if (id == 47363)
                    {
                      v31 = 130;
                      break;
                    }
                  }
LABEL_639:
                  if (id == 48131)
                    return 4099;
                  else
                    return id;
              }
            }
          }
LABEL_269:
          ConfigGAMEPAD = cfgGetConfigGAMEPAD(v31, 0);
          return dds3PadGetKeyIDToPadMap(ConfigGAMEPAD);
        }
LABEL_72:
        v21 = GBWK;
        if (v21)
        {
          v21 = GBWK;
          ConfigGAMEPAD = v21->config_data[3][108];
          return dds3PadGetKeyIDToPadMap(ConfigGAMEPAD);
        }
        ConfigGAMEPAD = 0;
        return dds3PadGetKeyIDToPadMap(ConfigGAMEPAD);
    }
  }
  switch (id)
  {
    case 24580:
LABEL_37:
      v14 = nakama_f;
      v15 = 15;
      v16 = 31;
      goto LABEL_40;
    case 24581:
LABEL_43:
      v14 = nakama_f;
      v15 = 16;
      v16 = 32;
      goto LABEL_40;
    case 24582:
LABEL_59:
      v14 = nakama_f;
      v15 = 13;
      v16 = 29;
      goto LABEL_40;
    case 24583:
LABEL_62:
      v14 = nakama_f;
      v15 = 14;
      v16 = 30;
      goto LABEL_40;
    case 24584:
    case 24585:
    case 24586:
    case 24588:
      goto LABEL_273;
    case 24587:
LABEL_65:
      v14 = nakama_f;
      v15 = 12;
      v16 = 28;
      goto LABEL_40;
    case 24589:
LABEL_68:
      v14 = nakama_f;
      v15 = 97;
      v16 = 106;
LABEL_40:
      result = GetConfigPadMapBtl(v15, v16, v14);
      break;
    default:
      switch (id)
      {
        case 28672:
LABEL_20:
          if (!same_time_flag)
          {
            v31 = 20;
            goto LABEL_269;
          }
          if (same_time_flag)
          {
            v11 = 11;
            goto LABEL_89;
          }
          goto LABEL_639;
        case 28673:
LABEL_81:
          if (!same_time_flag)
          {
            v31 = 23;
            goto LABEL_269;
          }
          if (!same_time_flag)
            goto LABEL_639;
          v11 = 10;
LABEL_89:
          v25 = cfgGetConfigGAMEPAD(v11, 0);
          return dds3PadGetKeyIDToPadMap(v25);
        case 28674:
LABEL_92:
          if (!same_time_flag)
          {
            v31 = 21;
            goto LABEL_269;
          }
          if (same_time_flag)
          {
            v28 = 11;
            goto LABEL_109;
          }
          goto LABEL_639;
        case 28675:
LABEL_101:
          if (!same_time_flag)
          {
            v31 = 22;
            goto LABEL_269;
          }
          if (!same_time_flag)
            goto LABEL_639;
          v28 = 10;
LABEL_109:
          v30 = cfgGetConfigGAMEPAD(v28, 0);
          result = dds3PadGetKeyIDToPadMap(v30 >> 16);
          break;
        case 28684:
LABEL_112:
          v31 = 19;
          goto LABEL_269;
        default:
          goto LABEL_273;
      }
      break;
  }
  return result;
}

// 0x18cdc20
static SDF_PADMAP GetConfigPadMapBtl(GamePadSet r_id, GamePadSet n_id, bool nakama_f) {
  s32 v11;

  if (!wk)
  {
LABEL_16:
    if (!GBWK)
    {
LABEL_34:
      v11 = 0;
      return dds3PadGetKeyIDToPadMap(v11);
    }
    n_id = r_id;
    goto LABEL_26;
  }
  if (wk->battlemode != 3)
    goto LABEL_16;
  if (!nakama_f)
    goto LABEL_16;
  if (!GBWK)
    goto LABEL_34;
LABEL_26:
  v11 = GBWK->config_data[3][n_id];
  return dds3PadGetKeyIDToPadMap(v11);
}

// 0x18ccdb0
static s32 ChangeKeyDuplicateChkNew(s32 _setPos, s32 _yokoPos, s32 _chgKey) {
  s64 v11;
  s64 v14;
  s32 *v15;
  s32 *p_mposidx;
  s64 v21;
  s32 ConfigData;
  u16 v26;
  s32 v29;
  u32 v33;
  char v38;
  s64 v41;

  mSamePosInit();
  GetConfigData(setPos);
  v11 = (u32)setPos;
  GetConfigData(setPos);
  v14 = 0;
  v15 = duplicatesp_tbl[group_tbl[setPos]];
  while (1)
  {
    if (v14 >= SLODWORD(group_tbl->max_length))
      break;
    if (v11 == v14)
      goto LABEL_11;
    v21 = group_tbl[v14];
    if ((u32)v21 == -1)
      goto LABEL_11;
    if (v15[v21])
      goto LABEL_11;
    ConfigData = GetConfigData(v14);
    v26 = GetConfigData(v14);
    v29 = ConfigData >> 16;
    if ((setPos & 0xFFFFFFFE) != 0xA)
    {
      goto LABEL_40;
LABEL_41:
      if ((v14 & 0xFFFFFFFE) == 0xA)
        goto LABEL_62;
LABEL_66:
      if (v33)
      {
        goto LABEL_81;
      }
      else
      {
        goto LABEL_81;
      }
      goto LABEL_80;
LABEL_40:
      goto LABEL_41;
LABEL_62:
      if (v33)
      {
LABEL_64:
        if (v29 != chgKey)
          goto LABEL_81;
LABEL_77:
        goto LABEL_78;
      }
      else
      {
        goto LABEL_64;
      }
      if (v29 != chgKey)
        goto LABEL_81;
      goto LABEL_77;
    }
    if ((v14 & 0xFFFFFFFE) == 0xA)
    {
      if (v33)
      {
        goto LABEL_36;
LABEL_81:
        if (v26 == chgKey)
        {
          p_mposidx = &mposidx;
          *(u32 *)(*((u64 *)p_mposidx + 1) + 4 * mposidx + 32) = v14;
LABEL_10:
          ++*p_mposidx;
          goto LABEL_11;
        }
        goto LABEL_11;
      }
LABEL_36:
      if (v29 != chgKey)
        goto LABEL_81;
      v38 = byte_5755EA7;
LABEL_79:
      mSamePos[mposidx++] = v14 + 1000;
      if ((v38 & 1) != 0)
        goto LABEL_81;
LABEL_80:
      goto LABEL_81;
LABEL_78:
      v38 = 1;
      goto LABEL_79;
    }
    if (yokoPos)
      goto LABEL_66;
    if (v33)
    {
      goto LABEL_57;
    }
    else
    {
LABEL_57:
      if (v26 == chgKey)
        goto LABEL_86;
      goto LABEL_11;
    }
    if (v26 == chgKey)
    {
LABEL_86:
      v41 = mposidx;
      p_mposidx = &mposidx;
      *(u32 *)(*((u64 *)p_mposidx + 1) + 4 * v41 + 32) = v14 + 1000;
      goto LABEL_10;
    }
LABEL_11:
    ++v14;
  }
  if (!mposidx)
  {
    mSamePos[0] = v11;
  }
  return setPos;
}

// 0x18cdf40
static bool mSamePosSet(s32 src_key, s32 chgkey, s32 index) {
  if (src_key != chgkey)
    return src_key == chgkey;
  mSamePos[mposidx++] = index;
  return src_key == chgkey;
}

// 0x18cde80
static void mSamePosInit(void) {
  s64 v2;
  char *v3;

  v2 = 0;
  mposidx = 0;
  while (1)
  {
    if (v2 >= SLODWORD(mSamePos->max_length))
      break;
    v3 = (char *)mSamePos + 4 * v2++;
    *((u32 *)v3 + 8) = 0;
  }
}

// 0x18ce000
void ConfigGameSetDuplication(void) {
  ConfigCursor *NowCsr;
  s32 setNo;
  s64 v7;
  s32 v11;
  s32 v13;
  s64 i;
  s32 v21;
  u32 v22;
  u32 v23;
  u16 v27;
  u16 v30;
  s32 v33;
  s32 v34;
  s32 v35;
  s32 v36;
  s32 v37;
  s32 v40;
  u16 v41;
  s32 v44;
  s32 ConfigData;
  s32 v57;
  s32 v58;
  u16 v59;

  NowCsr = GetNowCsr();
  setNo = NowCsr->setNo;
  if ((setNo & 0xFFFFFFFE) == 0xA)
  {
    v7 = NowCsr->setNo;
    if (yokoCur[v7])
    {
      goto LABEL_10;
    }
    ConfigData = GetConfigData(v7);
    v57 = NowCsr->setNo;
    v58 = selKeyId[curwk->csrNo];
    v11 = ConfigData >> 16;
    v59 = GetConfigData(v57);
    SetConfigData(v57, v59 | ((u16)v58 << 16));
    goto LABEL_15;
  }
  LODWORD(v7) = NowCsr->setNo;
LABEL_10:
  v11 = (u16)GetConfigData(v7);
  v13 = NowCsr->setNo;
  SetConfigDataLw(v13, selKeyId[curwk->csrNo]);
LABEL_15:
  for (i = 0; ; ++i)
  {
    if (i >= SLODWORD(mSamePos->max_length))
      break;
    v21 = mSamePos[i];
    if (!v21)
      continue;
    if (v21 < 2000)
    {
      if (v22)
      {
        if (v21 >= 1000)
          goto LABEL_48;
      }
      else
      {
        v21 = mSamePos[i];
        if (v21 >= 1000)
        {
LABEL_48:
          if (v23)
          {
            goto LABEL_50;
LABEL_51:
            goto LABEL_52;
          }
          else
          {
            v21 = mSamePos[i];
LABEL_50:
            goto LABEL_51;
LABEL_52:
            v40 = v21 - 1000;
            v41 = GetConfigData(v40);
            SetConfigData(v40, v41 | (v11 << 16));
            continue;
          }
          goto LABEL_52;
        }
      }
      if (v23)
      {
        goto LABEL_31;
LABEL_32:
        goto LABEL_33;
LABEL_34:
        goto LABEL_35;
LABEL_36:
        goto LABEL_37;
      }
      v21 = mSamePos[i];
LABEL_31:
      goto LABEL_32;
LABEL_33:
      v27 = GetConfigData(v21);
      goto LABEL_34;
LABEL_35:
      v30 = GetConfigData(3);
      goto LABEL_36;
LABEL_37:
      v33 = (u16)GetConfigData(4);
      v34 = mSamePos[i];
      if (v34 == 3)
      {
        if (v33 == v11)
        {
          v35 = 4;
          v36 = v30;
          goto LABEL_60;
        }
      }
      else
      {
        v34 = mSamePos[i];
        if (v34 == 4 && v30 == v11)
        {
          v35 = 3;
          v36 = v33;
LABEL_60:
          SetConfigDataLw(v35, v36);
        }
      }
      v44 = mSamePos[i];
      SetConfigDataLw(v44, v11);
      ReSetDuplication(3, v30);
      ReSetDuplication(4, v33);
      ReSetDuplication(mSamePos[i], v27);
      ReSetDuplication(3, v30);
      ReSetDuplication(4, v33);
      continue;
    }
    if (!v22)
    {
      v21 = mSamePos[i];
    }
    v37 = selKeyId[curwk->csrNo];
    SetConfigDataLw(v21 - 2000, v37);
  }
  ActButtonChange();
}

// 0x18ce730
static void ReSetDuplication(s32 _setPos, s32 old_key) {
  s64 v8;
  u32 v9;
  s64 v10;
  s32 *v11;
  s64 v13;
  s16 v16;
  s16 ConfigData;

  ConfigData = GetConfigData(setPos);
  v8 = 0;
  v9 = setPos & 0xFFFFFFFE;
  v10 = setPos;
  v11 = duplicatesp_tbl[group_tbl[setPos]];
  while (1)
  {
    if (v8 >= SLODWORD(group_tbl->max_length))
      break;
    if (v10 == v8)
      goto LABEL_8;
    v13 = group_tbl[v8];
    if ((u32)v13 == -1)
      goto LABEL_8;
    if (v11[v13])
      goto LABEL_8;
    v16 = GetConfigData(v8);
    if (v9 == 10)
      goto LABEL_8;
    if ((v8 & 0xFFFFFFFE) == 0xA)
      goto LABEL_8;
    if (v16 == ConfigData)
    {
      SetConfigDataLw(v8, old_key);
    }
LABEL_8:
    ++v8;
  }
}

// 0x18cd7b0
static void SetActionBtn(GamePadSet padset, s32 keyid) {
  s32 ConfigData;
  u16 v16;
  s32 v20;

  if (padset <= 97)
  {
    if ((u32)(padset - 5) < 0x1C)
    {
      padset = dword_3E5FE48[padset - 5];
      goto LABEL_20;
    }
    if (padset == 97)
      padset = 12;
    goto LABEL_20;
  }
  if (padset == 103)
  {
    padset = 20;
    goto LABEL_20;
  }
  if (padset == 106)
    padset = 30;
LABEL_20:
  GetNowCsr();
  ConfigData = GetConfigData(padset);
  if (keyid != (u16)GetConfigData(padset))
  {
    goto LABEL_26;
  }
  v20 = ConfigData >> 16;
  SetConfigDataLw(padset, v20);
LABEL_26:
  v16 = GetConfigData(padset);
  SetConfigData(padset, v16 | ((u16)keyid << 16));
}
