#include "types.h"
#include "MODELTYPE.h"
#include "SKLID.h"
#include "atlfieldaccessor.h"
#include "battletips.h"
#include "dat.h"
#include "gohcalc.h"
#include "sbtl.h"
#include "sbtlbossevent.h"
#include "sbtlcalc.h"
#include "sbtlcmndmenunew.h"
#include "sbtldmg.h"
#include "sbtldvltk.h"
#include "sbtleff.h"
#include "sbtlencount.h"
#include "sbtlmain.h"
#include "sbtlmenu.h"
#include "sbtlscene.h"
#include "sbtlscript.h"
#include "sbtlskill.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sdf_vu0.h"

typedef struct RED_GUAGE RED_GUAGE;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct sdatPlayerUnitWork_t sdatPlayerUnitWork_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;

static f32 cnf;

static void GetPartyLevelDfference(void);
static bool IsHiMitama(s32 iDevilID);
static void BattleSkillSort(SBTLUNIT_WORK *wk, sdatUnitWork_t *unit);
static bool IsBtlSkl(SBTLUNIT_WORK *wk, SKLID skl);
static bool GetPacData(MODELTYPE major, s32 minor, s32 devilid);

// 0x1f438b0
bool sBtlCheckStartBattle(void) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  SBTLUNIT_WORK *Nakama_FastLoad;
  sdatPlayerUnitWork_t *player;
  SBTLUNIT_LISTWORK *v8;
  s32 playerID;
  SBTLUNIT_WORK *v10;
  SBATTLE_WORK *v12;
  u32 status;
  s32 mode;
  s32 battlemode;
  sdatUnitWork_t *para;
  u32 BadStatus;
  u32 v18;
  SBTLUNIT_LISTWORK *v21;
  s32 v22;
  SBATTLE_WORK *v24;
  SBATTLE_WORK *v26;
  SBATTLE_WORK *v27;
  SBTLUNIT_LISTWORK *v28;
  s32 v29;
  SBTLUNIT_WORK *v30;
  s32 v31;
  sdatUnitWork_t *stock_id;
  sdatUnitWork_t *v33;
  s32 v34;
  sdatUnitWork_t *v35;
  sdatUnitWork_t *v36;
  s32 v37;
  sdatUnitWork_t *v38;
  sdatUnitWork_t *v39;
  s32 v40;
  sdatUnitWork_t *v41;
  sdatUnitWork_t *v42;
  sdatUnitWork_t *v46;
  u32 v47;
  RED_GUAGE *v49;
  SBTLUNIT_WORK *PChara;
  sdatUnitWork_t *v51;
  SBATTLE_WORK *v54;
  SB_ENCOUNTPAC *EncountPac;
  SB_ENCOUNTPAC *v57;
  _BOOL8 IsInitialized;
  s32 v59;
  SBTLUNIT_WORK *v60;
  u32 v62;
  SBTLUNIT_WORK *v63;
  SBTLUNIT_WORK *v64;
  SBTLUNIT_WORK *v65;
  sbtl *v66;
  SBATTLE_WORK *v69;
  u32 v71;
  SB_ENCOUNTPAC *v72;
  bool v73;

  if (wk->enemy_num < 1)
    goto LABEL_18;
  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 2) != 0 && (u32)(pUnit->mode - 1) < 2)
      goto LABEL_18;
  }
  player = GBWK->player;
  if ((wk->status & 0x80000000) != 0)
  {
    LOBYTE(Nakama_FastLoad) = 1;
    return (char)Nakama_FastLoad;
  }
  v8 = wk->UnitMng;
  playerID = wk->playerID;
  Nakama_FastLoad = sBtlSearchUnit_ID(v8, playerID);
  if (!Nakama_FastLoad)
    return (char)Nakama_FastLoad;
  v10 = Nakama_FastLoad;
  v12 = wk;
  status = v12->status;
  if ((status & 0x8000) != 0)
    goto LABEL_46;
  mode = v10->mode;
  if (!mode)
  {
    v10->mode = 2;
    v12 = wk;
    if (v12->battlemode == 3)
    {
      sBtlSetSummonEffect_Nakama(v10, 0);
    }
    goto LABEL_18;
  }
  if (mode < 3)
    goto LABEL_18;
  v12 = wk;
  status = v12->status;
  v12->status = status | 0x8000;
  battlemode = (u16)v12->battlemode;
  if (battlemode == 1)
  {
    v10->color = 0;
    v10->mode = 5;
    v10->vstatus |= 0x200000u;
    para = v10->para;
    BadStatus = sBtlGetBadStatus(para);
    if (BadStatus != 22)
    {
      v18 = BadStatus;
      sBtlSetBadStatus_No(v10, 0, v18, 1, -1);
    }
    goto LABEL_123;
  }
  if (battlemode == 3)
    goto LABEL_76;
  goto LABEL_9001;
  if (wk->battlemode == 3)
  {
LABEL_76:
    goto LABEL_77;
  }
LABEL_9001:
  v10->motion_UseWait2 = 1;
  sBtlSetMotion(v10, 130, 0, 0, 0);
LABEL_77:
  if (wk->battlemode == 3)
    goto LABEL_18;
  v10->color = 0;
  v10->mode = 5;
  v10->vstatus |= 0x200000u;
  v46 = v10->para;
  v47 = sBtlGetBadStatus(v10->para);
  if (v47 == 22)
  {
    goto LABEL_120;
  }
  v62 = v47;
  sBtlSetBadStatus_No(v10, 0, v62, 1, -1);
LABEL_120:
  v49 = wk->aRedGuage[0];
  PChara = sBtlGetPChara();
  if (!v49)
  {
LABEL_122:
LABEL_123:
    sBtlCheckBattlePara(v10);
    goto LABEL_18;
  }
  v51 = PChara->para;
  v49->cnt = 0;
  v49->bgn = v51->now->hp;
  goto LABEL_122;
LABEL_46:
  v24 = wk;
  v21 = v24->UnitMng;
  v22 = v24->playerID;
  Nakama_FastLoad = sBtlSearchUnit_ID(v21, v22);
  if (!Nakama_FastLoad)
    return (char)Nakama_FastLoad;
  if (Nakama_FastLoad->mode < 4)
    goto LABEL_18;
  v26 = wk;
  if (v26->member_num < 1)
    goto LABEL_230;
  v26 = wk;
  if (v26->encountno == 23)
  {
LABEL_230:
    v27 = wk;
    v28 = v27->UnitMng;
    v29 = v27->playerID;
    Nakama_FastLoad = sBtlSearchUnit_ID(v28, v29);
    if (!Nakama_FastLoad)
      return (char)Nakama_FastLoad;
    goto LABEL_70;
  }
  v26 = wk;
  v31 = v26->summonindex[0];
  if (v31 < 0)
    goto LABEL_231;
  stock_id = player->stock_id;
  LOWORD(v31) = wk->summonindex[0];
  v33 = stock_id[(s16)v31];
  if ((v33->flag & 1) == 0 || (v33->badstatus & 0x130000) != 0)
  {
LABEL_231:
  }
  else
  {
    Nakama_FastLoad = sBtlGetNakama_FastLoad(0);
    if (!Nakama_FastLoad)
      return (char)Nakama_FastLoad;
    v63 = Nakama_FastLoad;
    if (!sBtlCheckDamageTarget_FastLoadNakama(v63))
      goto LABEL_18;
    if (!sBtlLoadEffectData_Decode_FastLoad_Nakama(v63))
      goto LABEL_18;
  }
  v34 = wk->summonindex[1];
  if (v34 < 0)
    goto LABEL_232;
  v35 = player->stock_id;
  LOWORD(v34) = wk->summonindex[1];
  v36 = v35[(s16)v34];
  if ((v36->flag & 1) == 0 || (v36->badstatus & 0x130000) != 0)
  {
LABEL_232:
  }
  else
  {
    Nakama_FastLoad = sBtlGetNakama_FastLoad(1);
    if (!Nakama_FastLoad)
      return (char)Nakama_FastLoad;
    v64 = Nakama_FastLoad;
    if (!sBtlCheckDamageTarget_FastLoadNakama(v64))
      goto LABEL_18;
    if (!sBtlLoadEffectData_Decode_FastLoad_Nakama(v64))
      goto LABEL_18;
  }
  v37 = wk->summonindex[0];
  if (v37 < 0)
    goto LABEL_233;
  v38 = player->stock_id;
  LOWORD(v37) = wk->summonindex[0];
  v39 = v38[(s16)v37];
  if ((v39->flag & 1) == 0 || (v39->badstatus & 0x130000) != 0)
  {
LABEL_233:
    goto LABEL_102;
  }
  else
  {
    Nakama_FastLoad = sBtlGetNakama(0);
    if (!Nakama_FastLoad)
      return (char)Nakama_FastLoad;
    v65 = Nakama_FastLoad;
    if (!sBtlCheckDamageTarget(v65))
      goto LABEL_18;
    goto LABEL_102;
  }
LABEL_102:
  v40 = wk->summonindex[1];
  if (v40 < 0)
    goto LABEL_107;
  v41 = player->stock_id;
  LOWORD(v40) = wk->summonindex[1];
  v42 = v41[(s16)v40];
  if ((v42->flag & 1) == 0 || (v42->badstatus & 0x130000) != 0)
    goto LABEL_107;
  Nakama_FastLoad = sBtlGetNakama(1);
  if (!Nakama_FastLoad)
    return (char)Nakama_FastLoad;
LABEL_70:
  v30 = Nakama_FastLoad;
  if (!sBtlCheckDamageTarget(v30))
    goto LABEL_18;
LABEL_107:
  if (wk->gouto_startlvl)
  {
    goto LABEL_110;
  }
  GetPartyLevelDfference();
  wk->gouto_startlvl = 1;
LABEL_110:
  if (sBtlLoadEffectData_Decode(0))
  {
    if (!sBtlLoadAttackHitData_Decode(0))
      goto LABEL_18;
    v54 = wk;
    if (v54->smnCtrl->bNoOk)
      goto LABEL_18;
    v54 = wk;
    if (v54->step < 1)
      goto LABEL_18;
    v54 = wk;
    if ((v54->status2 & 0x2000000) != 0)
      goto LABEL_18;
    v54 = wk;
    if ((v54->status4 & 4) == 0)
      goto LABEL_18;
    EncountPac = sBtlGetEncountPac(-1);
    v57 = EncountPac[wk->encountno];
    if (!ChkTipsStart())
      goto LABEL_18;
    IsInitialized = IsInitialized();
    if (IsInitialized)
    {
      Nakama_FastLoad = GetBattleProdState();
      v59 = Nakama_FastLoad;
      v60 = Nakama_FastLoad;
      LOBYTE(Nakama_FastLoad) = 0;
      switch (v59)
      {
        case 0:
        case 3:
          PlayStartBattleProd(main_data->type2 == 2, main_data->NakamaID);
          goto LABEL_18;
        case 5:
          return (char)Nakama_FastLoad;
        case 6:
          OnStartBattle();
          goto LABEL_191;
        default:
          IsInitialized = (_BOOL8)v60;
          goto LABEL_191;
      }
      return (char)Nakama_FastLoad;
    }
LABEL_191:
    v66 = sBtlChkBossEventStart();
    if (((u8)v66 & 1) != 0)
      goto LABEL_206;
    if ((v57->flag & 0x36) == 0)
    {
      v69 = wk;
      if (v69->maigoEnc)
      {
        if (!v71)
        {
          v69 = wk;
        }
        v69->status |= 0x80000000;
        v69->huuma_targetID = 1;
        goto LABEL_206;
      }
      if (!v71)
      {
        v69 = wk;
      }
      if ((v69->status2 & 0x400000) != 0)
      {
        goto LABEL_197;
LABEL_196:
        v69 = wk;
LABEL_197:
        v69->bNoEnemyName = 1;
        v69->status |= 0x80000000;
        sBtlSetStartEx(1);
LABEL_206:
        if (sBtlChkBossEventStart_EnemySummonWait())
        {
          v72 = v57;
          v73 = 1;
        }
        else
        {
          v72 = v57;
          v73 = 0;
        }
        sBtlBattleStart(v72, v73);
        goto LABEL_18;
      }
      v66 = ChkSensei();
      if (((u8)v66 & 1) != 0)
        goto LABEL_206;
      v66 = ChkSenseiDamage();
      if (((u8)v66 & 1) != 0)
        goto LABEL_206;
      v66 = ChkMyth();
      if (((u8)v66 & 1) != 0)
        goto LABEL_206;
    }
    goto LABEL_196;
  }
LABEL_18:
  LOBYTE(Nakama_FastLoad) = 0;
  return (char)Nakama_FastLoad;
}

// 0x1f447f0
static void GetPartyLevelDfference(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  s32 level;
  SB_ENCOUNTPAC *EncountPac;
  s64 v8;
  char v9;
  char v10;
  s32 v11;
  SB_ENCOUNTPAC *v12;
  SBATTLE_WORK *v13;
  SBTLUNIT_LISTWORK *v14;
  SBTLUNIT_WORK *pUnit;
  s32 devilid;
  s32 v17;
  bool v18;
  SBTLDVLTK_LISTWORK *dvltkList;
  SBATTLE_WORK *v20;
  SBTLUNIT_LISTWORK *v21;
  s32 v22;
  SBTLUNIT_WORK *v24;
  s32 v25;
  SBATTLE_WORK *v26;
  SBTLUNIT_LISTWORK *v27;
  s32 v28;

  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  level = sBtlSearchUnit_ID(UnitMng, playerID)->para->level;
  EncountPac = sBtlGetEncountPac(-1);
  v8 = 0;
  v9 = 0;
  v10 = 0;
  v11 = -1;
  v12 = EncountPac[wk->encountno];
  while (1)
  {
    v13 = wk;
    v14 = v13->UnitMng;
    if (v8 >= v14->number)
      break;
    pUnit = v14->pUnitL[v8]->pUnit;
    if (pUnit)
    {
      if ((pUnit->side & 2) != 0)
      {
        if ((v12->flag & 0x36) != 0)
        {
          v10 = 0;
          v9 = 1;
        }
        else
        {
          devilid = pUnit->para->devilid;
          if ((u32)(devilid - 413) >= 4)
          {
            v17 = datCalcEnemyToNakamaID(devilid);
            v18 = gohKarteAllRegCheck(v17);
            if (!v18)
              v10 |= (pUnit->status & 0x10000) == 0;
          }
        }
        if (v11 <= pUnit->para->level)
          v11 = pUnit->para->level;
      }
    }
    ++v8;
  }
  if (level - v11 <= -5)
  {
    if ((v9 & 1) != 0)
      return;
    dvltkList = v13->dvltkList;
    v26 = wk;
    v27 = v26->UnitMng;
    v28 = v26->playerID;
    v24 = sBtlSearchUnit_ID(v27, v28);
    v25 = 258;
    goto LABEL_52;
  }
  if ((v10 & 1) != 0)
  {
    dvltkList = v13->dvltkList;
    v20 = wk;
    v21 = v20->UnitMng;
    v22 = v20->playerID;
    v24 = sBtlSearchUnit_ID(v21, v22);
    v25 = 291;
LABEL_52:
    sBtlCreateDvltk_Gouto(dvltkList, v24, v25, 1);
  }
}

// 0x1f44f30
static bool IsHiMitama(s32 iDevilID) {
  return (u32)(iDevilID - 413) < 4;
}

// 0x1f44c70
bool sBtlChkBossEventStart(void) {
  s64 v1;
  s32 v3;
  SBTLUNIT_LISTWORK *UnitMng;
  s64 number;
  SBTLUNIT_WORK *pUnit;

  v1 = 0;
  while (1)
  {
    UnitMng = wk->UnitMng;
    number = UnitMng->number;
    if (v1 >= number)
      return v1 < number;
    pUnit = UnitMng->pUnitL[v1]->pUnit;
    if (pUnit)
    {
      if ((pUnit->side & 0x3F) == 2)
      {
        v3 = sBtlCheck(pUnit, 0, 0);
        if ((v3 & 0x80000000) == 0)
        {
          wk->boss_eventID = pUnit->ListID;
          wk->status |= 0x80000000;
          sBtlProcessStart(0, v3);
          pUnit->aiwk->bWait2 = 1;
          return v1 < number;
        }
      }
    }
    ++v1;
  }
}

// 0x1f44e00
bool sBtlChkBossEventStart_EnemySummonWait(void) {
  s64 v1;
  SBTLUNIT_LISTWORK *UnitMng;
  s64 number;
  SBTLUNIT_WORK *pUnit;

  v1 = 0;
  while (1)
  {
    UnitMng = wk->UnitMng;
    number = UnitMng->number;
    if (v1 >= number)
      return v1 < number;
    pUnit = UnitMng->pUnitL[v1]->pUnit;
    if (pUnit)
    {
      if ((pUnit->side & 0x3F) == 2)
      {
        if (sBtlCheck_Start_EnemySummonWait(pUnit))
          return v1 < number;
      }
    }
    ++v1;
  }
}

// 0x1f44f40
bool sBtlCheckSummon(s32 idx) {
  sdatPlayerUnitWork_t *player;
  sdatUnitWork_t *stock_id;
  s64 v9;
  sdatUnitWork_t *v10;
  sdatUnitWork_t *v12;
  sdatUnitWork_t *v13;
  s64 v14;
  sdatUnitWork_t *v15;
  s32 devilid;

  player = GBWK->player;
  if (wk->battlemode)
    return 0;
  if (wk->summonindex[0] < 0)
    return 0;
  if (wk->stock_num < 1)
    return 0;
  stock_id = player->stock_id;
  v9 = wk->summonindex[idx];
  v10 = stock_id[v9];
  if ((v10->flag & 1) == 0 || (v10->badstatus & 0x130000) != 0)
    return 0;
  v12 = player->stock_id;
  v13 = player->stock_id;
  v14 = v9;
  v15 = v12[v14];
  devilid = v13[v14]->devilid;
  return sBtlCheckMagCost(v15, devilid, 0);
}

// 0x1f45230
void sBtlInitEffect(void) {
  SBTLEFF_DATAWORK *v1;
  s64 v4;
  s64 i;
  s64 v6;
  plistHandle_t_Resource *v7;
  const char *name;
  effPartsListPose_t *v9;
  s32 *wkeffOnMem_local;
  SBTLEFF_DATAWORK *v12;

  v1 = NewSpecific(SBTLEFF_DATAWORK, 0x2Eu);
  wkeffOnMem = v1;
  v4 = 0;
  for (i = 8; ; i += 2)
  {
    wkeffOnMem_local = wkeffOnMem;
    if (v4 >= wkeffOnMem_local[6])
      break;
    v12 = Allocate(SBTLEFF_DATAWORK);
    _ctor(v12, 0);
    if (v12)
      QueryInterface(v12, *(void **)(*(u64 *)wkeffOnMem_local + 64));
    *(u64 *)&wkeffOnMem_local[i] = v12;
    v6 = *(s64 *)((char *)&wkeffOnMem->obj.klass + i * 4);
    v7 = Allocate(plistHandle_t_Resource);
    _ctor(v7, 0);
    *(u64 *)(v6 + 16) = v7;
    name = (*(Il2CppClass **)((char *)&wkeffOnMem->obj.klass + i * 4))->_1.name;
    v9 = Allocate(effPartsListPose_t);
    _ctor(v9, 0);
    *((u64 *)name + 2) = v9;
    ++v4;
  }
}

// 0x1f45430
bool sBtlInitPlayerData(void) {
  sdatParaWork_t *v1;
  SBTLAISYO_DATAWORK *v3;
  void *v4;
  sdatPlayerUnitWork_t *player;
  s32 v10;
  sdfVector4_t *p_pos;
  s32 v12;
  sdfVector4_t *p_rot;
  sdatUnitWork_t *para;
  sdatParaWork_t *v16;
  sdatUnitWork_t *v17;
  sdatParaWork_t *v18;
  sdatUnitWork_t *stock_id;
  sdatUnitWork_t *v21;
  sdatUnitWork_t *v22;
  sdatUnitWork_t *v23;
  sdatUnitWork_t *v24;
  sdatUnitWork_t *v25;
  sdatUnitWork_t *v26;
  sdatUnitWork_t *v27;
  sdatUnitWork_t *v28;
  sdatUnitWork_t *v29;
  sdatUnitWork_t *v30;
  sdatUnitWork_t *v31;
  sdatUnitWork_t *v32;
  sdatUnitWork_t *v33;
  sdatUnitWork_t *v34;
  sdatUnitWork_t *v35;
  sdatUnitWork_t *v36;
  sdatUnitWork_t *v37;
  s32 v39;

  v1 = Allocate(sdatParaWork_t);
  *(_OWORD *)&v1->hp = xmmword_3D02E40;
  *(u64 *)&v1->str = 0x5000600030006LL;
  v3 = Allocate(SBTLAISYO_DATAWORK);
  _ctor(v3, 0);
  v4 = NewSpecific(s32, 0x10u);
  InitializeArray_55364416(v4, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__3090ED5EE8E290FCC420860442F61473DE73BEC8C5A1E7FF354B2CF52E1F962D, 0);
  v3->para = v4;
  player = GBWK->player;
  v10 = (u8)byte_5755EF6;
  vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
  if (v10)
  {
    p_pos = &player->pos;
    goto LABEL_10;
  }
  else
  {
    p_pos = &player->pos;
LABEL_10:
    v12 = (u8)byte_5755EF5;
    *p_pos = vct_A;
    if (v12)
      goto LABEL_11;
    goto LABEL_24;
  }
  v39 = (u8)byte_5755EF5;
  *p_pos = vct_A;
  if (v39)
  {
LABEL_11:
    goto LABEL_12;
  }
LABEL_24:
LABEL_12:
  vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
  p_rot = &player->rot;
  para = player->para;
  player->stock_max = 8;
  *p_rot = vct_A;
  para->flag = 3;
  v16 = Clone(v1, 0);
  para->now = v16;
  v17 = player->para;
  v18 = Clone(v1, 0);
  v17->backup = v18;
  ClassCopy(player->para->aisyo, v3, 0);
  player->swordno = 0;
  player->bulletno = 80;
  *(u64 *)&player->gunno = 0x600000000LL;
  stock_id = GBWK->player->stock_id;
  v21 = stock_id[1];
  stock_id[0]->bChuuseiDrink = 0;
  v21->bChuuseiDrink = 0;
  v22 = stock_id[3];
  stock_id[2]->bChuuseiDrink = 0;
  v22->bChuuseiDrink = 0;
  v23 = stock_id[5];
  stock_id[4]->bChuuseiDrink = 0;
  v23->bChuuseiDrink = 0;
  v24 = stock_id[7];
  stock_id[6]->bChuuseiDrink = 0;
  v24->bChuuseiDrink = 0;
  v25 = stock_id[9];
  stock_id[8]->bChuuseiDrink = 0;
  v25->bChuuseiDrink = 0;
  v26 = stock_id[11];
  stock_id[10]->bChuuseiDrink = 0;
  v26->bChuuseiDrink = 0;
  v27 = stock_id[13];
  stock_id[12]->bChuuseiDrink = 0;
  v27->bChuuseiDrink = 0;
  v28 = stock_id[15];
  stock_id[14]->bChuuseiDrink = 0;
  v28->bChuuseiDrink = 0;
  v29 = stock_id[17];
  stock_id[16]->bChuuseiDrink = 0;
  v29->bChuuseiDrink = 0;
  v30 = stock_id[19];
  stock_id[18]->bChuuseiDrink = 0;
  v30->bChuuseiDrink = 0;
  v31 = stock_id[21];
  stock_id[20]->bChuuseiDrink = 0;
  v31->bChuuseiDrink = 0;
  v32 = stock_id[23];
  stock_id[22]->bChuuseiDrink = 0;
  v32->bChuuseiDrink = 0;
  v33 = stock_id[25];
  stock_id[24]->bChuuseiDrink = 0;
  v33->bChuuseiDrink = 0;
  v34 = stock_id[27];
  stock_id[26]->bChuuseiDrink = 0;
  v34->bChuuseiDrink = 0;
  v35 = stock_id[29];
  stock_id[28]->bChuuseiDrink = 0;
  v37 = stock_id[30];
  v36 = stock_id[31];
  v35->bChuuseiDrink = 0;
  v37->bChuuseiDrink = 0;
  v36->bChuuseiDrink = 0;
  return 1;
}

// 0x1f451a0
sdatPlayerUnitWork_t *sBtlGetPlayerData(void) {
  return GBWK->player;
}

// 0x1f458e0
sdatUnitWork_t *sBtlGetStockUnitData(s32 id) {
  sdatUnitWork_t *v4;

  if ((u32)id > 0x1F)
    return 0;
  v4 = GBWK->player->stock_id[id];
  if (!v4->devilid)
    return 0;
  if ((v4->flag & 1) != 0)
    return GBWK->player->stock_id[id];
  else
    return 0;
}

// 0x1f45990
bool sBtlSetData_Unit_Stock(SBTLUNIT_WORK *wk, s32 stock) {
  SKLID *haveskill;
  sdatUnitWork_t *v7;
  sdatUnitWork_t *v8;
  sdatUnitWork_t *stock_id;
  Il2CppClass **v10;

  haveskill = GBWK->player->stock_id[stock]->haveskill;
  v7 = Clone(wk->para, 0);
  v8 = v7;
  stock_id = GBWK->player->stock_id;
  v10 = &stock_id->obj.klass + stock;
  v10[4] = v8;
  v8->haveskill = haveskill;
  return 1;
}

// 0x1f45a80
bool sBtlGetData_Stock_Unit(SBTLUNIT_WORK *wk, s32 stock) {
  SKLID *v6;
  sdatUnitWork_t *v8;
  sdatUnitWork_t *para;
  SKLID *haveskill;
  s32 v12;
  s32 v13;
  s32 v14;
  s32 v15;
  s32 v16;
  s32 v17;
  s32 v18;
  s32 v19;
  s32 v20;
  s32 v21;
  s32 v22;
  s32 v23;
  s32 v24;
  s32 v25;
  s32 v26;
  s32 v27;
  s32 v28;
  s64 v29;
  sdatUnitWork_t *v30;
  SKLID *battleskill;
  s32 v32;
  s32 v33;
  sdatUnitWork_t *v34;
  SBTLAI_WORK *aiwk;

  v6 = NewSpecific(SKLID, 0x11u);
  v8 = GBWK->player->stock_id[stock];
  sBtlCheckStockPara(v8);
  ClassCopy(wk->para, v8, 0);
  BattleSkillSort(wk, v8);
  wk->uniq_code = v8->uniq_code;
  ClassCopy(wk->aisyo_bkup, wk->para->aisyo, 0);
  para = wk->para;
  *(u64 *)&v6[0] = 0x12000000095LL;
  haveskill = para->haveskill;
  v12 = haveskill[0];
  if (v12 && v12 != 149 && v12 != 288)
    v6[2] = v12;
  v13 = haveskill[1];
  if (v13 && v13 != 149 && v13 != 288)
    v6[3] = v13;
  v14 = haveskill[2];
  if (v14 && v14 != 149 && v14 != 288)
    v6[4] = v14;
  v15 = haveskill[3];
  if (v15 && v15 != 149 && v15 != 288)
    v6[5] = v15;
  v16 = haveskill[4];
  if (v16 && v16 != 149 && v16 != 288)
    v6[6] = v16;
  v17 = haveskill[5];
  if (v17 && v17 != 149 && v17 != 288)
    v6[7] = v17;
  v18 = haveskill[6];
  if (v18 && v18 != 149 && v18 != 288)
    v6[8] = v18;
  v19 = haveskill[7];
  if (v19 && v19 != 149 && v19 != 288)
    v6[9] = v19;
  v20 = haveskill[8];
  if (v20 && v20 != 149 && v20 != 288)
    v6[10] = v20;
  v21 = haveskill[9];
  if (v21 && v21 != 149 && v21 != 288)
    v6[11] = v21;
  v22 = haveskill[10];
  if (v22 && v22 != 149 && v22 != 288)
    v6[12] = v22;
  v23 = haveskill[11];
  if (v23 && v23 != 149 && v23 != 288)
    v6[13] = v23;
  v24 = haveskill[12];
  if (v24 && v24 != 149 && v24 != 288)
    v6[14] = v24;
  v25 = haveskill[13];
  if (v25 && v25 != 149 && v25 != 288)
    v6[15] = v25;
  v26 = haveskill[14];
  if (v26 && v26 != 149 && v26 != 288)
    v6[16] = v26;
  v27 = haveskill[15];
  if (v27 && v27 != 149 && v27 != 288)
    v6[17] = v27;
  v28 = haveskill[16];
  if (v28 && v28 != 149 && v28 != 288)
    v6[18] = v28;
  haveskill[0] = 149;
  v29 = 0;
  haveskill[1] = v6[1];
  haveskill[2] = v6[2];
  haveskill[3] = v6[3];
  haveskill[4] = v6[4];
  haveskill[5] = v6[5];
  haveskill[6] = v6[6];
  haveskill[7] = v6[7];
  haveskill[8] = v6[8];
  haveskill[9] = v6[9];
  haveskill[10] = v6[10];
  haveskill[11] = v6[11];
  haveskill[12] = v6[12];
  haveskill[13] = v6[13];
  haveskill[14] = v6[14];
  haveskill[15] = v6[15];
  haveskill[16] = v6[16];
  do
  {
    v30 = wk->para;
    if (!v30->autoskill[v29])
      goto LABEL_75;
    battleskill = v30->battleskill;
    v32 = battleskill[0];
    v33 = v30->haveskill[v29];
    if (v32 == v33)
    {
      if (sBtlChkRepeat(v32))
      {
LABEL_116:
        v34 = wk->para;
        aiwk = wk->aiwk;
        aiwk->RepeatOdrSkl = v34->haveskill[v29];
        goto LABEL_118;
      }
      battleskill = wk->para->battleskill;
      v33 = wk->para->haveskill[v29];
    }
    if (battleskill[1] == v33)
    {
      if (sBtlChkRepeat(v33))
        goto LABEL_116;
      battleskill = wk->para->battleskill;
      v33 = wk->para->haveskill[v29];
    }
    if (battleskill[2] == v33)
    {
      if (sBtlChkRepeat(v33))
        goto LABEL_116;
      battleskill = wk->para->battleskill;
      v33 = wk->para->haveskill[v29];
    }
    if (battleskill[3] == v33)
    {
      if (sBtlChkRepeat(v33))
        goto LABEL_116;
      battleskill = wk->para->battleskill;
      v33 = wk->para->haveskill[v29];
      if (battleskill[4] != v33)
      {
LABEL_94:
        if (battleskill[5] != v33)
          goto LABEL_95;
        goto LABEL_106;
      }
    }
    else if (battleskill[4] != v33)
    {
      goto LABEL_94;
    }
    if (sBtlChkRepeat(v33))
      goto LABEL_116;
    battleskill = wk->para->battleskill;
    v33 = wk->para->haveskill[v29];
    if (battleskill[5] != v33)
    {
LABEL_95:
      if (battleskill[6] != v33)
        goto LABEL_96;
      goto LABEL_110;
    }
LABEL_106:
    if (sBtlChkRepeat(v33))
      goto LABEL_116;
    battleskill = wk->para->battleskill;
    v33 = wk->para->haveskill[v29];
    if (battleskill[6] != v33)
    {
LABEL_96:
      if (battleskill[7] != v33)
        goto LABEL_75;
LABEL_114:
      if (sBtlChkRepeat(v33))
        goto LABEL_116;
      goto LABEL_75;
    }
LABEL_110:
    if (sBtlChkRepeat(v33))
      goto LABEL_116;
    v33 = wk->para->haveskill[v29];
    if (wk->para->battleskill[7] == v33)
      goto LABEL_114;
LABEL_75:
    ++v29;
  }
  while (v29 != 17);
  v8->autoskill[0] = 0;
  wk->para->autoskill[0] = 0;
  v8->autoskill[1] = 0;
  wk->para->autoskill[1] = 0;
  v8->autoskill[2] = 0;
  wk->para->autoskill[2] = 0;
  v8->autoskill[3] = 0;
  wk->para->autoskill[3] = 0;
  v8->autoskill[4] = 0;
  wk->para->autoskill[4] = 0;
  v8->autoskill[5] = 0;
  wk->para->autoskill[5] = 0;
  v8->autoskill[6] = 0;
  wk->para->autoskill[6] = 0;
  v8->autoskill[7] = 0;
  wk->para->autoskill[7] = 0;
  v8->autoskill[8] = 0;
  wk->para->autoskill[8] = 0;
  v8->autoskill[9] = 0;
  wk->para->autoskill[9] = 0;
  v8->autoskill[10] = 0;
  wk->para->autoskill[10] = 0;
  v8->autoskill[11] = 0;
  wk->para->autoskill[11] = 0;
  v8->autoskill[12] = 0;
  wk->para->autoskill[12] = 0;
  v8->autoskill[13] = 0;
  wk->para->autoskill[13] = 0;
  v8->autoskill[14] = 0;
  wk->para->autoskill[14] = 0;
  v8->autoskill[15] = 0;
  wk->para->autoskill[15] = 0;
  v8->autoskill[16] = 0;
  wk->para->autoskill[16] = 0;
  v8->autoskill[0] = 1;
  wk->para->autoskill[0] = 1;
  aiwk = wk->aiwk;
  v34 = wk->para;
  aiwk->RepeatOdrSkl = 149;
LABEL_118:
  aiwk->dfltOdrStk = -1;
  *(u64 *)&aiwk->RepeatOdrTgt = -1;
  *(u64 *)&aiwk->dfltOdrSkl = -4294967147LL;
  v34->geturei_vice_flag = v8->geturei_vice_flag;
  return 1;
}

// 0x1f465b0
static void BattleSkillSort(SBTLUNIT_WORK *wk, sdatUnitWork_t *unit) {
  SKLID *battleskill;
  SKLID *haveskill;
  s64 v7;
  s32 v8;
  s32 v9;
  char *v10;

  battleskill = wk->para->battleskill;
  if ((s32)battleskill->max_length >= 1)
    sub_188E3B0(battleskill, 0, 4 * (u32)battleskill->max_length);
  haveskill = unit->haveskill;
  if (SLODWORD(haveskill->max_length) >= 1)
  {
    v7 = 0;
    v8 = 0;
    while (1)
    {
      v9 = haveskill[v7];
      if (v9)
        break;
LABEL_7:
      haveskill = unit->haveskill;
      if (++v7 >= SLODWORD(haveskill->max_length))
        return;
    }
    if ((tbldata[v9]->useflg & 1) != 0)
    {
      v10 = (char *)wk->para->battleskill + 4 * v8++;
      *((u32 *)v10 + 8) = v9;
    }
    goto LABEL_7;
  }
}

// 0x1f46700
static bool IsBtlSkl(SBTLUNIT_WORK *wk, SKLID skl) {
  SKLID *battleskill;
  s32 v4;
  bool v5;
  s32 v6;
  s32 v8;
  s32 v10;
  s32 v12;
  s32 v14;
  s32 v15;
  s32 v17;

  battleskill = wk->para->battleskill;
  v4 = battleskill[0];
  if (v4)
    v5 = v4 == skl;
  else
    v5 = 0;
  if (v5)
    return 1;
  v6 = battleskill[1];
  if (v6 && v6 == skl)
    return 1;
  v8 = battleskill[2];
  if (v8 && v8 == skl)
    return 1;
  v10 = battleskill[3];
  if (v10 && v10 == skl)
    return 1;
  v12 = battleskill[4];
  if (v12 && v12 == skl)
    return 1;
  v14 = battleskill[5];
  if (v14)
  {
    if (v14 == skl)
      return 1;
  }
  v15 = battleskill[6];
  if (v15)
  {
    if (v15 == skl)
      return 1;
  }
  v17 = battleskill[7];
  return v17 && v17 == skl;
}

// 0x1f467a0
bool sBtlCheckLive(sdatUnitWork_t *unit) {
  return (unit->badstatus & 0x20000) == 0;
}

// 0x1f44610
bool sBtlCheckSelect(sdatUnitWork_t *unit) {
  return (unit->flag & 1) != 0 && (unit->badstatus & 0x130000) == 0;
}

// 0x1f46200
bool sBtlCheckStockPara(sdatUnitWork_t *unit) {
  sdatParaWork_t *huuma;
  int16x4_t *backup;
  sdatParaWork_t *now;
  int16x4_t *surpriseParam;
  sdatParaWork_t *pitem;
  sdatParaWork_t *pbtl;
  s32 v9;
  s32 maxmp;
  u32 flag;
  u16 v12;
  s16 v13;
  s32 vit;
  sdatParaWork_t *v15;
  s16 v16;
  s16 v17;
  s32 tec;
  sdatParaWork_t *v19;
  s16 v20;
  s16 v21;
  s32 luck;
  sdatParaWork_t *v23;
  s16 v24;
  sdatParaWork_t *v25;
  s16 v26;
  s16 v27;
  s32 v28;
  s32 maxhp;

  sBtlSetAutoSkill_GB(unit);
  huuma = unit->huuma;
  now = unit->now;
  backup = unit->backup;
  surpriseParam = unit->surpriseParam;
  pitem = unit->pitem;
  pbtl = unit->pbtl;
  v9 = pitem->maxhp + backup[2].n64_u32[1] + pbtl->maxhp + huuma->maxhp;
  LODWORD(pbtl) = pbtl->maxmp + huuma->maxmp;
  maxmp = pitem->maxmp;
  now->maxhp = v9 + unit->accident->maxhp + surpriseParam[2].n64_u32[1];
  now->maxmp = maxmp + backup[3].n64_u32[1] + (u32)pbtl + surpriseParam[3].n64_u32[1];
  flag = unit->flag;
  if ((flag & 2) != 0)
  {
    v12 = backup[4].n64_u16[0];
    v13 = v12 + unit->pbtl->str + GETITEMPARA(pitem->str);
    vit = unit->pitem->vit;
    now->str = v13 + unit->huuma->str + unit->surpriseParam->str;
    v15 = unit->now;
    v16 = unit->backup->vit;
    v17 = v16 + unit->pbtl->vit + GETITEMPARA(vit);
    tec = unit->pitem->tec;
    v15->vit = v17 + unit->huuma->vit + unit->surpriseParam->vit;
    v19 = unit->now;
    v20 = unit->backup->tec;
    v21 = v20 + unit->pbtl->tec + GETITEMPARA(tec);
    luck = unit->pitem->luck;
    v19->tec = v21 + unit->huuma->tec + unit->surpriseParam->tec;
    v23 = unit->now;
    v24 = unit->backup->luck;
    v23->luck = v24
                     + unit->pbtl->luck
                     + GETITEMPARA(luck)
                     + unit->huuma->luck
                     + unit->surpriseParam->luck;
    v25 = unit->now;
    v26 = v25->luck;
    v27 = sBtlGetCorrectionParamLuck() + v26;
    now = unit->now;
    v25->luck = v27;
    v28 = now->luck;
    if (v28 <= 1)
      LOWORD(v28) = 1;
    now->luck = v28;
    if (unit->devilid)
      goto LABEL_14;
LABEL_19:
    LimitRange(&now->maxhp, 0, 999);
    LimitRange(&unit->now->maxmp, 0, 999);
    LimitRange_2(&unit->now->str, 0, 40);
    LimitRange_2(&unit->now->vit, 0, 40);
    LimitRange_2(&unit->now->tec, 0, 40);
    LimitRange_2(&unit->now->luck, 0, 40);
    now = unit->now;
    maxhp = now->maxhp;
    goto LABEL_15;
  }
  if ((flag & 4) != 0)
  {
    datCalcDevilMaxParCheck(unit);
    now = unit->now;
    if (unit->devilid)
      goto LABEL_14;
    goto LABEL_19;
  }
  *(int16x4_t *)&now->str = vadd_s16(surpriseParam[4], backup[4]);
  if (!unit->devilid)
    goto LABEL_19;
LABEL_14:
  maxhp = now->maxhp;
LABEL_15:
  LimitRange(&now->hp, 0, maxhp);
  LimitRange(&unit->now->mp, 0, unit->now->maxmp);
  return 1;
}

// 0x1f467b0
bool sBtlSetMapFade(s32 frame, u32 abgr, s16 mode) {
  u32 *v7;
  u32 *v8;
  u16 *v9;
  SBTLSCENE_WORK *scene;
  s32 status;
  bool v14;
  SBATTLE_WORK *v15;
  s32 mf_abgr_low;
  s32 mf_abgr_s_low;
  s32 v18;
  s32 v20;
  s32 v21;
  s32 v22;
  s32 v23;
  s32 v25;
  s32 v26;
  s32 v28;
  s32 v29;
  s32 v31;
  s32 v32;
  s32 v33;
  s32 v35;
  s32 v38;
  s32 v39;
  s32 v41;
  s32 v42;
  s32 v43;
  SBATTLE_WORK *v44;

  v7 = NewSpecific(s32, 3u);
  v8 = NewSpecific(s32, 3u);
  v9 = NewSpecific(s16, 3u);
  if (wk)
  {
    scene = wk->scene;
    wk->mf_mode = mode;
    wk->mf_counter = 0;
    status = scene->status;
    wk->mf_cmpcounter = frame;
    scene->status = status | 8;
    if (frame)
    {
      goto LABEL_10;
    }
    {
      wk->mf_cmpcounter = 1;
      goto LABEL_10;
    }
    else
    {
      wk->mf_cmpcounter = 1;
LABEL_10:
      v14 = mode == 0;
      v15 = wk;
      mf_abgr_low = LOBYTE(v15->mf_abgr);
      v15->mf_abgr_s = abgr;
      v7[8] = mf_abgr_low;
      v7[9] = BYTE1(v15->mf_abgr);
      v7[10] = BYTE2(v15->mf_abgr);
      mf_abgr_s_low = LOBYTE(v15->mf_abgr_s);
      v8[8] = mf_abgr_s_low;
      v8[9] = BYTE1(v15->mf_abgr_s);
      v8[10] = BYTE2(v15->mf_abgr_s);
      v18 = v7[8];
      if (v14)
      {
        if (v18 <= mf_abgr_s_low)
        {
          v15 = wk;
          v22 = (s16)((mf_abgr_s_low - v18) / v15->mf_cmpcounter);
          if (v22 <= 1)
            LOWORD(v22) = 1;
        }
        else
        {
          v15 = wk;
          v21 = (s16)((v18 - mf_abgr_s_low) / v15->mf_cmpcounter);
          if (v21 <= 1)
            v21 = 1;
          v22 = -v21;
        }
        v9[16] = v22;
        v38 = v7[9];
        v39 = v8[9];
        if (v38 <= v39)
        {
          v42 = (s16)((v39 - v38) / wk->mf_cmpcounter);
          if (v42 <= 1)
            LOWORD(v42) = 1;
        }
        else
        {
          v41 = (s16)((v38 - v39) / wk->mf_cmpcounter);
          if (v41 <= 1)
            v41 = 1;
          v42 = -v41;
        }
        v9[17] = v42;
        v31 = v7[10];
        v32 = v8[10];
        v33 = v31 - v32;
        if (v31 <= v32)
        {
LABEL_41:
          v35 = (s16)((v32 - v31) / wk->mf_cmpcounter);
          if (v35 <= 1)
            LOWORD(v35) = 1;
          v9[18] = v35;
          goto LABEL_68;
        }
      }
      else
      {
        if (v18 >= mf_abgr_s_low)
        {
          v15 = wk;
          v23 = (s16)((v18 - mf_abgr_s_low) / v15->mf_cmpcounter);
          if (v23 <= 1)
            v23 = 1;
          v20 = -v23;
        }
        else
        {
          v15 = wk;
          v20 = (s16)((mf_abgr_s_low - v18) / v15->mf_cmpcounter);
          if (v20 <= 1)
            LOWORD(v20) = 1;
        }
        v9[16] = v20;
        v25 = v7[9];
        v26 = v8[9];
        if (v25 >= v26)
        {
          v29 = (s16)((v25 - v26) / wk->mf_cmpcounter);
          if (v29 <= 1)
            v29 = 1;
          v28 = -v29;
        }
        else
        {
          v28 = (s16)((v26 - v25) / wk->mf_cmpcounter);
          if (v28 <= 1)
            LOWORD(v28) = 1;
        }
        v9[17] = v28;
        v31 = v7[10];
        v32 = v8[10];
        v33 = v31 - v32;
        if (v31 < v32)
          goto LABEL_41;
      }
      v43 = (s16)(v33 / wk->mf_cmpcounter);
      if (v43 <= 1)
        LOWORD(v43) = 1;
      v9[18] = -(s16)v43;
LABEL_68:
      v44 = wk;
      v44->mf_r = v9[16];
      v44->mf_g = v9[17];
      v44->mf_b = v9[18];
      return 1;
    }
    goto LABEL_10;
  }
  return 1;
}

// 0x1f46c00
bool sBtlMapFadeProc(void) {
  SBATTLE_WORK *wk_local;
  s32 mf_counter;
  s32 mf_cmpcounter;
  s16 *p_mf_counter;
  s32 mf_abgr_low;
  SBATTLE_WORK *v10;
  s32 mf_r;
  u32 mf_abgr;
  SBATTLE_WORK *v14;
  s32 mf_g;
  u32 v16;
  s32 v17;
  SBATTLE_WORK *v18;
  s32 mf_b;
  u32 v20;

  wk_local = wk;
  if (!wk_local)
    return 1;
  if ((wk_local->scene->status & 8) == 0)
    return 0;
  if ((wk_local->status & 0x8000000) == 0)
  {
    mf_counter = wk_local->mf_counter;
    mf_cmpcounter = wk_local->mf_cmpcounter;
    if (mf_counter < mf_cmpcounter)
    {
      wk_local = wk;
      LOWORD(mf_counter) = wk_local->mf_counter;
      LOWORD(mf_cmpcounter) = wk_local->mf_cmpcounter;
      p_mf_counter = &wk_local->mf_counter;
      wk_local->mf_counter = mf_counter + 1;
      LimitRange_2(p_mf_counter, 0, mf_cmpcounter);
      mf_abgr_low = LOBYTE(wk->mf_abgr);
      v10 = wk;
      mf_r = v10->mf_r;
      goto LABEL_9000;
LABEL_22:
      v14 = wk;
      mf_g = v14->mf_g;
      v16 = v14->mf_abgr;
      v17 = mf_abgr_low + mf_r;
      v18 = wk;
      mf_b = (u16)v18->mf_b;
      v18 = wk;
      v18->mf_abgr = ((mf_abgr & 0xFF00) + (mf_g << 8))
                          | v17
                          | ((v16 & 0xFF0000) + (mf_b << 16))
                          | (HIBYTE(v18->mf_abgr_s) << 24);
      goto LABEL_35;
LABEL_9000:
      mf_abgr = v10->mf_abgr;
      goto LABEL_22;
    }
    wk_local->mf_abgr = wk_local->mf_abgr_s;
    if (wk_local->mf_mode != 1)
    {
LABEL_35:
      v20 = wk->mf_abgr;
      sBtlMapColorSet(v20);
      return 1;
    }
    wk_local = wk;
    wk_local->scene->status &= ~8u;
    goto LABEL_35;
  }
  return 0;
}

// 0x1f46fb0
bool sBtlSetMapFade_H(s32 frame, u32 abgr, s16 mode) {
  u32 *v7;
  u32 *v8;
  u32 *v9;
  SBTLSCENE_WORK *scene;
  s32 status;
  bool v14;
  SBATTLE_WORK *v15;
  s32 mfh_abgr_low;
  s32 mfh_abgr_s_low;
  s32 v18;
  s32 v20;
  s32 v21;
  s32 v22;
  s32 v23;
  s32 v25;
  s32 v26;
  s32 v28;
  s32 v29;
  s32 v31;
  s32 v32;
  s32 v33;
  s32 v35;
  s32 v38;
  s32 v39;
  s32 v41;
  s32 v42;
  s32 v43;
  s32 v44;
  SBATTLE_WORK *v45;

  v7 = NewSpecific(s32, 3u);
  v8 = NewSpecific(s32, 3u);
  v9 = NewSpecific(s32, 3u);
  if (wk)
  {
    scene = wk->scene;
    wk->mfh_mode = mode;
    wk->mfh_counter = 0;
    status = scene->status;
    wk->mfh_cmpcounter = frame;
    scene->status = status | 0x10;
    if (frame)
    {
      goto LABEL_10;
    }
    {
      wk->mfh_cmpcounter = 1;
      goto LABEL_10;
    }
    else
    {
      wk->mfh_cmpcounter = 1;
LABEL_10:
      v14 = mode == 0;
      v15 = wk;
      mfh_abgr_low = LOBYTE(v15->mfh_abgr);
      v15->mfh_abgr_s = abgr;
      v7[8] = mfh_abgr_low;
      v7[9] = BYTE1(v15->mfh_abgr);
      v7[10] = BYTE2(v15->mfh_abgr);
      mfh_abgr_s_low = LOBYTE(v15->mfh_abgr_s);
      v8[8] = mfh_abgr_s_low;
      v8[9] = BYTE1(v15->mfh_abgr_s);
      v8[10] = BYTE2(v15->mfh_abgr_s);
      v18 = v7[8];
      if (v14)
      {
        if (v18 <= mfh_abgr_s_low)
        {
          v15 = wk;
          v22 = (mfh_abgr_s_low - v18) / v15->mfh_cmpcounter;
          if (v22 <= 1)
            v22 = 1;
        }
        else
        {
          v15 = wk;
          v21 = (v18 - mfh_abgr_s_low) / v15->mfh_cmpcounter;
          if (v21 <= 1)
            v21 = 1;
          v22 = -v21;
        }
        v9[8] = v22;
        v38 = v7[9];
        v39 = v8[9];
        if (v38 <= v39)
        {
          v42 = (v39 - v38) / wk->mfh_cmpcounter;
          if (v42 <= 1)
            v42 = 1;
        }
        else
        {
          v41 = (v38 - v39) / wk->mfh_cmpcounter;
          if (v41 <= 1)
            v41 = 1;
          v42 = -v41;
        }
        v9[9] = v42;
        v31 = v7[10];
        v32 = v8[10];
        v33 = v31 - v32;
        if (v31 <= v32)
        {
LABEL_41:
          v35 = (v32 - v31) / wk->mfh_cmpcounter;
          if (v35 <= 1)
            v35 = 1;
          v9[10] = v35;
          goto LABEL_68;
        }
      }
      else
      {
        if (v18 >= mfh_abgr_s_low)
        {
          v15 = wk;
          v23 = (v18 - mfh_abgr_s_low) / v15->mfh_cmpcounter;
          if (v23 <= 1)
            v23 = 1;
          v20 = -v23;
        }
        else
        {
          v15 = wk;
          v20 = (mfh_abgr_s_low - v18) / v15->mfh_cmpcounter;
          if (v20 <= 1)
            v20 = 1;
        }
        v9[8] = v20;
        v25 = v7[9];
        v26 = v8[9];
        if (v25 >= v26)
        {
          v29 = (v25 - v26) / wk->mfh_cmpcounter;
          if (v29 <= 1)
            v29 = 1;
          v28 = -v29;
        }
        else
        {
          v28 = (v26 - v25) / wk->mfh_cmpcounter;
          if (v28 <= 1)
            v28 = 1;
        }
        v9[9] = v28;
        v31 = v7[10];
        v32 = v8[10];
        v33 = v31 - v32;
        if (v31 < v32)
          goto LABEL_41;
      }
      v43 = v33 / wk->mfh_cmpcounter;
      if (v43 <= 1)
        v43 = 1;
      v35 = -v43;
      v9[10] = v35;
LABEL_68:
      v44 = v9[9];
      v45 = wk;
      v45->mfh_r = v9[8];
      v45->mfh_g = v44;
      v45->mfh_b = v35;
      return 1;
    }
    goto LABEL_10;
  }
  return 1;
}

// 0x1f473c0
bool sBtlMapFadeProc_H(void) {
  SBATTLE_WORK *wk_local;
  s32 mfh_counter;
  s32 mfh_cmpcounter;
  s16 *p_mfh_counter;
  s32 mfh_abgr_low;
  SBATTLE_WORK *v10;
  s32 mfh_r;
  u32 mfh_abgr;
  SBATTLE_WORK *v14;
  s32 mfh_g;
  u32 v16;
  s32 v17;
  SBATTLE_WORK *v18;
  s32 mfh_b;
  u32 v20;

  wk_local = wk;
  if (!wk_local)
    return 1;
  if ((wk_local->scene->status & 0x10) == 0)
    return 0;
  mfh_counter = wk_local->mfh_counter;
  mfh_cmpcounter = wk_local->mfh_cmpcounter;
  if (mfh_counter < mfh_cmpcounter)
  {
    wk_local = wk;
    LOWORD(mfh_counter) = wk_local->mfh_counter;
    LOWORD(mfh_cmpcounter) = wk_local->mfh_cmpcounter;
    p_mfh_counter = &wk_local->mfh_counter;
    wk_local->mfh_counter = mfh_counter + 1;
    LimitRange_2(p_mfh_counter, 0, mfh_cmpcounter);
    mfh_abgr_low = LOBYTE(wk->mfh_abgr);
    v10 = wk;
    mfh_r = v10->mfh_r;
    goto LABEL_9000;
LABEL_20:
    v14 = wk;
    mfh_g = v14->mfh_g;
    v16 = v14->mfh_abgr;
    v17 = mfh_abgr_low + mfh_r;
    v18 = wk;
    mfh_b = (u16)v18->mfh_b;
    v18 = wk;
    v18->mfh_abgr = ((mfh_abgr & 0xFF00) + (mfh_g << 8))
                         | v17
                         | ((v16 & 0xFF0000) + (mfh_b << 16))
                         | (HIBYTE(v18->mfh_abgr_s) << 24);
    goto LABEL_31;
LABEL_9000:
    mfh_abgr = v10->mfh_abgr;
    goto LABEL_20;
  }
  wk_local = wk;
  wk_local->mfh_abgr = wk_local->mfh_abgr_s;
  wk_local->scene->status &= ~0x10u;
LABEL_31:
  v20 = wk->mfh_abgr;
  sBtlMapColorSet(v20);
  return 1;
}

// 0x1f476f0
bool sBtlSetSetsumaPadStop(s32 sttime, s32 cmpcnt, f32 _SlowMotionSpeed) {
  SBATTLE_WORK *wk_local;
  u32 status4;
  s32 playerID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v14;

  wk_local = wk;
  status4 = wk_local->status4;
  if ((status4 & 0x100000) != 0)
    return 1;
  wk_local = wk;
  status4 = wk_local->status4;
  wk_local->status4 = status4 | 0x100000;
  wk_local->setsuma_pad_stop_sttime = sttime;
  playerID = wk_local->playerID;
  wk_local->setsuma_pad_stop_cmpcnt = cmpcnt;
  UnitMng = wk_local->UnitMng;
  *(u64 *)&wk_local->setsuma_pad_stop_stcnt = 0;
  v14 = sBtlSearchUnit_ID(UnitMng, playerID);
  sBtlStartSlowMotion(v14, SlowMotionSpeed);
  return 1;
}

// 0x1f47830
bool sBtlProcSetsumaPadStop(void) {
  SBATTLE_WORK *v4;
  SBATTLE_WORK *v5;
  s32 setsuma_pad_stop_sttime;
  s32 *p_setsuma_pad_stop_stcnt;
  u32 v11;
  SBATTLE_WORK *v12;
  s32 setsuma_pad_stop_cnt;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v16;

  if (!wk)
    return wk != 0;
  v4 = wk;
  if ((wk->status4 & 0x100000) == 0)
    return wk != 0;
  if (v4->setsuma_pad_stop_stcnt < v4->setsuma_pad_stop_sttime)
  {
    goto LABEL_14;
  }
  v4 = wk;
  v4->setsuma_pad_Stop = 1;
LABEL_14:
  v5 = wk;
  setsuma_pad_stop_sttime = v5->setsuma_pad_stop_sttime;
  p_setsuma_pad_stop_stcnt = &v5->setsuma_pad_stop_stcnt;
  ++v5->setsuma_pad_stop_stcnt;
  LimitRange(p_setsuma_pad_stop_stcnt, 0, setsuma_pad_stop_sttime);
  if (!IsSceanStop())
    return wk != 0;
  v12 = wk;
  setsuma_pad_stop_cnt = v12->setsuma_pad_stop_cnt;
  if (setsuma_pad_stop_cnt >= v12->setsuma_pad_stop_cmpcnt)
  {
    if (!v11)
    {
      v12 = wk;
    }
    v12->setsuma_pad_Stop = 0;
    UnitMng = v12->UnitMng;
    *(u64 *)&v12->setsuma_pad_stop_cnt = 0;
    v12->status4 &= ~0x100000u;
    playerID = v12->playerID;
    v16 = sBtlSearchUnit_ID(UnitMng, playerID);
    sBtlEndSlowMotion(v16);
    return 1;
  }
  else
  {
    if (!v11)
    {
      v12 = wk;
      setsuma_pad_stop_cnt = v12->setsuma_pad_stop_cnt;
    }
    v12->setsuma_pad_stop_cnt = setsuma_pad_stop_cnt + 1;
    return 1;
  }
}

// 0x1f47ab0
bool sBtlIsSetsumaPadStop(void) {
  return (BYTE2(wk->status4) >> 4) & 1;
}

// 0x1f47b20
void sBtlEndSetsumaPadStop(void) {
  SBATTLE_WORK *wk_local;
  u32 status4;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v7;

  wk_local = wk;
  status4 = wk_local->status4;
  if ((status4 & 0x100000) == 0)
    return;
  wk_local = wk;
  status4 = wk_local->status4;
  wk_local->status4 = status4 & 0xFFEFFFFF;
  wk_local->setsuma_pad_Stop = 0;
  UnitMng = wk_local->UnitMng;
  playerID = wk_local->playerID;
  *(_OWORD *)&wk_local->setsuma_pad_stop_sttime = 0u;
  v7 = sBtlSearchUnit_ID(UnitMng, playerID);
  sBtlEndSlowMotion(v7);
}

// 0x1f47c30
bool sBtlSetEnemyLastDeadStop(s32 sttime, s32 cmpcnt, f32 _SlowMotionSpeedPlayer, f32 _SlowMotionSpeedEnemy) {
  SBATTLE_WORK *wk_local;
  u32 status4;
  s32 playerID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v16;
  s64 i;
  SBTLUNIT_LISTWORK *v19;
  SBTLUNIT_WORK *pUnit;

  wk_local = wk;
  status4 = wk_local->status4;
  if ((status4 & 0x200000) != 0)
    return 1;
  goto LABEL_7;
  if ((status4 & 0x200000) == 0)
  {
LABEL_7:
    wk_local = wk;
    status4 = wk_local->status4;
    wk_local->status4 = status4 | 0x200000;
    wk_local->enemylastdead_stop_sttime = sttime;
    playerID = wk_local->playerID;
    wk_local->enemylastdead_stop_cmpcnt = cmpcnt;
    UnitMng = wk_local->UnitMng;
    wk_local->enemylastdead_stop_spd_player = SlowMotionSpeedPlayer;
    *(u64 *)&wk_local->enemylastdead_stop_stcnt = 0;
    wk_local->enemylastdead_stop_spd_enemy = SlowMotionSpeedEnemy;
    v16 = sBtlSearchUnit_ID(UnitMng, playerID);
    sBtlStartSlowMotion(v16, wk->enemylastdead_stop_spd_player);
    for (i = 0; ; ++i)
    {
      v19 = wk->UnitMng;
      if (i >= v19->number)
        return 1;
      pUnit = v19->pUnitL[i]->pUnit;
      if (!pUnit)
        continue;
      if ((pUnit->side & 2) != 0)
        pUnit->vstatus |= 0x2000000u;
    }
  }
  return 1;
}

// 0x1f47e10
bool sBtlProcEnemyLastDeadStop(void) {
  SBATTLE_WORK *v3;
  SBATTLE_WORK *v4;
  s32 enemylastdead_stop_sttime;
  s32 *p_enemylastdead_stop_stcnt;
  u32 v10;
  SBATTLE_WORK *v11;
  s32 enemylastdead_stop_cnt;
  SBTLUNIT_LISTWORK *v14;
  s32 playerID;
  SBTLUNIT_WORK *v16;
  s64 j;
  SBTLUNIT_LISTWORK *v19;
  SBTLUNIT_WORK *v20;
  s64 i;
  SBATTLE_WORK *v22;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  f32 enemylastdead_stop_spd_enemy;

  if (!wk)
    return wk != 0;
  v3 = wk;
  if ((wk->status4 & 0x200000) == 0)
    return wk != 0;
  if (v3->enemylastdead_stop_stcnt < v3->enemylastdead_stop_sttime)
  {
    goto LABEL_14;
  }
  if (!v3->enemylastdead_Stop)
    goto LABEL_50;
  goto LABEL_9002;
  if (!wk->enemylastdead_Stop)
  {
LABEL_50:
    for (i = 0; ; ++i)
    {
      v22 = wk;
      UnitMng = v22->UnitMng;
      if (i >= UnitMng->number)
        break;
      pUnit = UnitMng->pUnitL[i]->pUnit;
      if (!pUnit)
        continue;
      if ((pUnit->side & 2) != 0)
      {
        enemylastdead_stop_spd_enemy = v22->enemylastdead_stop_spd_enemy;
        sBtlStartSlowMotion(pUnit, enemylastdead_stop_spd_enemy);
        continue;
      }
    }
  }
LABEL_9002:
  wk->enemylastdead_Stop = 1;
LABEL_14:
  v4 = wk;
  enemylastdead_stop_sttime = v4->enemylastdead_stop_sttime;
  p_enemylastdead_stop_stcnt = &v4->enemylastdead_stop_stcnt;
  ++v4->enemylastdead_stop_stcnt;
  LimitRange(p_enemylastdead_stop_stcnt, 0, enemylastdead_stop_sttime);
  if (IsSceanStop())
  {
    v11 = wk;
    enemylastdead_stop_cnt = v11->enemylastdead_stop_cnt;
    if (enemylastdead_stop_cnt < v11->enemylastdead_stop_cmpcnt)
    {
      if (!v10)
      {
        v11 = wk;
        enemylastdead_stop_cnt = v11->enemylastdead_stop_cnt;
      }
      v11->enemylastdead_stop_cnt = enemylastdead_stop_cnt + 1;
      return wk != 0;
    }
    if (!v10)
    {
      v11 = wk;
    }
    v11->enemylastdead_Stop = 0;
    *(u64 *)&v11->enemylastdead_stop_cnt = 0;
    v14 = v11->UnitMng;
    v11->status4 &= ~0x200000u;
    playerID = v11->playerID;
    v16 = sBtlSearchUnit_ID(v14, playerID);
    sBtlEndSlowMotion(v16);
    for (j = 0; ; ++j)
    {
      v19 = wk->UnitMng;
      if (j >= v19->number)
        return wk != 0;
      v20 = v19->pUnitL[j]->pUnit;
      if (!v20)
        continue;
      if ((v20->side & 2) != 0)
      {
        sBtlEndSlowMotion(v20);
        v20->vstatus &= ~0x2000000u;
      }
    }
  }
  return wk != 0;
}

// 0x1f48250
bool sBtlIsEnemyLastDeadStop(void) {
  return (BYTE2(wk->status4) >> 5) & 1;
}

// 0x1f482c0
bool sBtlSetHitStop(s32 sttime, s32 cmpcnt) {
  SBATTLE_WORK *wk_local;
  u32 status2;

  wk_local = wk;
  status2 = wk_local->status2;
  if ((status2 & 0x400) != 0)
    return 1;
  wk_local = wk;
  status2 = wk_local->status2;
  wk_local->hitst_sttime = sttime;
  wk_local->status2 = status2 | 0x400;
  wk_local->hitst_cmpcnt = cmpcnt;
  *(u64 *)&wk_local->hitst_stcnt = 0;
  return 1;
}

// 0x1f483a0
bool sBtlProcHitStop(void) {
  SBATTLE_WORK *v4;
  SBATTLE_WORK *v5;
  s32 hitst_sttime;
  s32 *p_hitst_stcnt;
  u32 v11;
  SBATTLE_WORK *v12;
  s32 hitst_cnt;

  if (!wk)
    return wk != 0;
  v4 = wk;
  if ((wk->status2 & 0x400) == 0)
    return wk != 0;
  if (v4->hitst_stcnt < v4->hitst_sttime)
  {
    goto LABEL_14;
  }
  v4 = wk;
  v4->hitStop = 1;
LABEL_14:
  v5 = wk;
  hitst_sttime = v5->hitst_sttime;
  p_hitst_stcnt = &v5->hitst_stcnt;
  ++v5->hitst_stcnt;
  LimitRange(p_hitst_stcnt, 0, hitst_sttime);
  if (!IsSceanStop())
    return wk != 0;
  v12 = wk;
  hitst_cnt = v12->hitst_cnt;
  if (hitst_cnt >= v12->hitst_cmpcnt)
  {
    if (!v11)
    {
      v12 = wk;
    }
    v12->hitStop = 0;
    *(u64 *)&v12->hitst_cnt = 0;
    v12->status2 &= ~0x400u;
    return 1;
  }
  else
  {
    if (!v11)
    {
      v12 = wk;
      hitst_cnt = v12->hitst_cnt;
    }
    v12->hitst_cnt = hitst_cnt + 1;
    return 1;
  }
}

// 0x1f485e0
s32 sBtlSearchPacData(MODELTYPE major, s32 minor, s32 devilid) {
  s32 v8;
  s64 i;
  s64 v10;

  v8 = major;
  for (i = 4; i != 20; ++i)
  {
    if (*(u16 *)(*((u64 *)&wk3->pacdata->obj.klass + i) + 40) == v8)
    {
      if (*(u32 *)(*((u64 *)&wk3->pacdata->obj.klass + i) + 44) == minor)
      {
        if (*(u32 *)(*((u64 *)&wk3->pacdata->obj.klass + i) + 48) == devilid)
          return i - 4;
      }
    }
  }
  v10 = 4;
  while (1)
  {
    if (*(u16 *)(*((u64 *)&wk3->pacdata->obj.klass + v10) + 40))
      goto LABEL_16;
    if (!*(u32 *)(*((u64 *)&wk3->pacdata->obj.klass + v10) + 44))
      goto LABEL_25;
LABEL_16:
    if (++v10 == 20)
      return -2;
  }
  if (*(u32 *)(*((u64 *)&wk3->pacdata->obj.klass + v10) + 44))
    goto LABEL_16;
LABEL_25:
  if (*(u32 *)(*((u64 *)&wk3->pacdata->obj.klass + v10) + 48))
    goto LABEL_16;
  return v10 - 4;
}

// 0x1f487f0
s32 sBtlSearchPacData2(MODELTYPE major, s32 minor, s32 devilid) {
  s32 v8;
  s64 v9;

  v8 = major;
  v9 = 4;
  while (1)
  {
    if (*(u16 *)(*((u64 *)&wk3->pacdata->obj.klass + v9) + 40) == v8)
    {
      if (*(u32 *)(*((u64 *)&wk3->pacdata->obj.klass + v9) + 44) == minor)
      {
        if (*(u32 *)(*((u64 *)&wk3->pacdata->obj.klass + v9) + 48) == devilid)
          break;
      }
    }
    if (++v9 == 20)
      return -2;
  }
  return v9 - 4;
}

// 0x1f48920
static bool GetPacData(MODELTYPE major, s32 minor, s32 devilid) {
  s32 v7;
  s32 v8;
  SBTLPACDATA_WORK *v10;

  v7 = sBtlSearchPacData(major, minor, devilid);
  if (v7 != -1)
  {
    v8 = v7;
    v10 = wk3->pacdata[v8];
    v10->major = major;
    v10->minor = minor;
    v10->devilid = devilid;
  }
  return 1;
}

// 0x1f489d0
bool sBtlSetPacData_MHT(MODELTYPE major, s32 minor, s32 devilid, void *pData, s32 size) {
  s32 v10;
  s32 v12;
  s32 v13;
  SBTLPACDATA_WORK *v15;
  s32 max_length;
  s64 v17;
  s64 v18;
  void *v19;
  SBTLSKLHIT_PACDATAWORK *pwk;
  SBTLSKLHIT_PACDATAWORK *v22;
  s64 v23;
  u64 *v24;
  SBTLSKLHIT_PACLIST *hitwk;

  v10 = sBtlSearchPacData(major, minor, devilid);
  if (v10 != -1)
  {
    v12 = v10;
    v13 = sBtlSearchPacData(major, minor, devilid);
    if (v13 != -1)
    {
      v15 = wk3->pacdata[v13];
      v15->major = major;
      v15->minor = minor;
      v15->devilid = devilid;
    }
    max_length = pData->max_length;
    wk3->pacdata[v12]->hitwk->num = max_length;
    if (max_length >= 1)
    {
      v17 = 0;
      v18 = 32;
      do
      {
        pwk = wk3->pacdata[v12]->hitwk->pwk;
        v22 = Allocate(SBTLSKLHIT_PACDATAWORK);
        _ctor(v22, 0);
        *(Il2CppClass **)((char *)&pwk->obj.klass + v18) = v22;
        v23 = *(s64 *)((char *)&wk3->pacdata[v12]->hitwk->pwk->obj.klass + v18);
        v24 = *(Il2CppClass **)((char *)&pData->obj.klass + v18);
        v19 = v24[2];
        *(u64 *)(v23 + 40) = v19;
        ++v17;
        v18 += 8;
      }
      while (v17 < SLODWORD(pData->max_length));
    }
    hitwk = wk3->pacdata[v12]->hitwk;
    hitwk->status |= 1u;
  }
  return 1;
}

// 0x1f48c70
bool sBtlSetPacData_AT3(MODELTYPE major, s32 minor, s32 devilid, void *pData, s32 size) {
  s32 v10;
  s32 v11;
  SBTLPACDATA_WORK *v13;

  if (sBtlSearchPacData(major, minor, devilid) != -1)
  {
    v10 = sBtlSearchPacData(major, minor, devilid);
    if (v10 != -1)
    {
      v11 = v10;
      v13 = wk3->pacdata[v11];
      v13->major = major;
      v13->minor = minor;
      v13->devilid = devilid;
    }
  }
  return 1;
}

// 0x1f48d30
bool sBtlSetPacData_motionSE(MODELTYPE major, s32 minor, s32 devilid, void *pData, s32 size) {
  s32 v10;
  s32 v11;
  SBTLPACDATA_WORK *v13;

  if (sBtlSearchPacData(major, minor, devilid) != -1)
  {
    v10 = sBtlSearchPacData(major, minor, devilid);
    if (v10 != -1)
    {
      v11 = v10;
      v13 = wk3->pacdata[v11];
      v13->major = major;
      v13->minor = minor;
      v13->devilid = devilid;
    }
  }
  return 1;
}

// 0x1f48df0
void sBtlPacData_Init(void) {
  s64 i;
  const char *name;
  const char *namespaze;
  SBTLPACDATA_WORK *pacdata;
  SBTLPACDATA_WORK *v6;

  for (i = 32; i != 160; i += 8)
  {
    pacdata = wk3->pacdata;
    v6 = Allocate(SBTLPACDATA_WORK);
    _ctor(v6, 0);
    *(Il2CppClass **)((char *)&pacdata->obj.klass + i) = v6;
    name = (*(Il2CppClass **)((char *)&wk3->pacdata->obj.klass + i))->_1.name;
    *((u64 *)name + 2) = 0;
    namespaze = (*(Il2CppClass **)((char *)&wk3->pacdata->obj.klass + i))->_1.namespaze;
    *((u64 *)namespaze + 2) = 0;
  }
}

// 0x1f48f20
void sBtlPacData_Free(void) {
  s64 i;
  SBTLPACDATA_WORK *v3;
  s64 v4;
  s64 j;
  s64 v6;
  s64 v7;
  s64 v8;
  SBTLSKLHIT_PACLIST *hitwk;
  SBTLPACDATA_AT3 *at3;
  SBTL_PACDATA_MOTIONSE *motionSE;

  for (i = 0; i != 16; ++i)
  {
    while (1)
    {
      v3 = wk3->pacdata[i];
      if (v3->major)
        goto LABEL_16;
      if (v3->minor)
        goto LABEL_16;
      if (v3->devilid)
        goto LABEL_16;
LABEL_13:
      if (++i == 16)
        return;
    }
    if (!wk3->pacdata[i]->devilid)
      goto LABEL_13;
LABEL_16:
    v4 = i;
    if ((wk3->pacdata[i]->hitwk->status & 1) != 0)
    {
      for (j = 4; ; ++j)
      {
        hitwk = wk3->pacdata[i]->hitwk;
        if (j - 4 >= hitwk->num)
          break;
        hitwk = wk3->pacdata[i]->hitwk;
        v6 = *((u64 *)&hitwk->pwk->obj.klass + j);
        *(u64 *)(v6 + 16) = 0;
        v7 = *((u64 *)&wk3->pacdata[v4]->hitwk->pwk->obj.klass + j);
        *(u64 *)(v7 + 32) = 0;
        v8 = *((u64 *)&wk3->pacdata[v4]->hitwk->pwk->obj.klass + j);
        *(u64 *)(v8 + 40) = 0;
      }
      hitwk = wk3->pacdata[i]->hitwk;
      hitwk->status = 0;
    }
    at3 = wk3->pacdata[v4]->at3;
    at3->pData = 0;
    motionSE = wk3->pacdata[v4]->motionSE;
    motionSE->pData = 0;
  }
}

// 0x1f491e0
void sBtlPacData_FreeIndex(MODELTYPE major, s32 minor, s32 devilid) {
  s64 i;
  SBTLPACDATA_AT3 *at3;
  SBTLPACDATA_WORK *v10;
  SBTL_PACDATA_MOTIONSE *motionSE;
  SBTLPACDATA_AT3 *v12;
  SBTLPACDATA_WORK *v13;
  SBTLPACDATA_WORK *v14;
  SBTLPACDATA_WORK *v15;
  s64 v16;
  s64 j;
  s64 v18;
  s64 v19;
  s64 v20;
  SBTLSKLHIT_PACLIST *hitwk;

  for (i = 0; i != 16; ++i)
  {
    v14 = wk3->pacdata[i];
    if (!v14->major)
    {
      if (v14->minor)
        goto LABEL_17;
      if (!v14->devilid)
        continue;
    }
LABEL_17:
    if (wk3->pacdata[i]->major == major)
    {
      if (wk3->pacdata[i]->minor == minor)
      {
        v15 = wk3->pacdata[i];
        if (v15->devilid == devilid)
        {
          v16 = i;
          if ((v15->hitwk->status & 1) != 0)
          {
            for (j = 4; ; ++j)
            {
              hitwk = wk3->pacdata[i]->hitwk;
              if (j - 4 >= hitwk->num)
                break;
              hitwk = wk3->pacdata[i]->hitwk;
              v18 = *((u64 *)&hitwk->pwk->obj.klass + j);
              *(u64 *)(v18 + 16) = 0;
              v19 = *((u64 *)&wk3->pacdata[v16]->hitwk->pwk->obj.klass + j);
              *(u64 *)(v19 + 32) = 0;
              v20 = *((u64 *)&wk3->pacdata[v16]->hitwk->pwk->obj.klass + j);
              *(u64 *)(v20 + 40) = 0;
            }
            hitwk->status = 0;
          }
          at3 = wk3->pacdata[v16]->at3;
          at3->pData = 0;
          v10 = wk3->pacdata[v16];
          v12 = v10->at3;
          motionSE = v10->motionSE;
          motionSE->pData = 0;
          v12->size = 0;
          v13 = wk3->pacdata[v16];
          v13->major = 0;
          v13->minor = 0;
          v13->devilid = 0;
          continue;
        }
      }
    }
  }
}

// 0x1f495a0
s32 sBtlCheckEndEscape(void) {
  return escape_checkflg;
}

// 0x1f49620
s32 sBtlCheckEndTimeUp(void) {
  if (!wk)
    return 0;
  if (wk->mode == 16)
    return 1;
  return 0;
}

// 0x1f3a7a0
SBTLUNIT_WORK *sBtlGetNakama(s8 idx) {
  u32 v5;
  s64 v6;
  s32 v7;
  SBATTLE_WORK *v8;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 v10;
  SBTLUNIT_WORK *result;
  sdatUnitWork_t *para;

  if ((u8)idx > 1u)
    return 0;
  v5 = wk->summonindex[(u8)idx];
  if (v5 > 0x1F)
    return 0;
  v6 = idx;
  if (wk->summonindex_menu[(u8)idx] != v5)
    return 0;
  v7 = wk->summonflg[wk->summonindex[(u8)idx]];
  if (v7 != 3)
  {
    v7 = wk->summonflg[wk->summonindex[(u8)idx]];
    if (v7 != 2)
    {
      if (wk->battlemode != 3)
        return 0;
    }
  }
  v8 = wk;
  UnitMng = v8->UnitMng;
  v10 = v8->summonID[v8->summonindex[v6]];
  result = sBtlSearchUnit_ID(UnitMng, v10);
  if (!result)
    return 0;
  para = result->para;
  if (!para || !para->devilid)
    return 0;
  return result;
}

// 0x1f44640
SBTLUNIT_WORK *sBtlGetNakama_FastLoad(s8 idx) {
  u32 v5;
  s64 v6;
  SBATTLE_WORK *v7;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 v9;
  SBTLUNIT_WORK *result;
  sdatUnitWork_t *para;

  if ((u8)idx > 1u)
    return 0;
  v5 = wk->summonindex[(u8)idx];
  if (v5 > 0x1F)
    return 0;
  v6 = idx;
  if (wk->summonindex_menu[(u8)idx] != v5)
    return 0;
  if (!wk->summonflg[wk->summonindex[(u8)idx]])
  {
    if (wk->battlemode != 3)
      return 0;
  }
  v7 = wk;
  UnitMng = v7->UnitMng;
  v9 = v7->summonID[v7->summonindex[v6]];
  result = sBtlSearchUnit_ID(UnitMng, v9);
  if (!result)
    return 0;
  para = result->para;
  if (!para || !para->devilid)
    return 0;
  return result;
}

// 0x1f496e0
SBTLUNIT_WORK *sBtlGetNakama2(s8 idx) {
  u32 v5;
  s64 v6;
  SBATTLE_WORK *v7;
  SBATTLE_WORK *v8;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 v10;
  SBTLUNIT_WORK *result;

  if ((u8)idx > 1u)
    return 0;
  v5 = wk->summonindex[(u8)idx];
  if (v5 > 0x1F)
    return 0;
  v6 = idx;
  if (wk->summonindex_menu[(u8)idx] != v5)
    return 0;
  if (idx == 1)
  {
    if (wk->battlemode == 3)
      return 0;
  }
  v7 = wk;
  if (!v7->summonflg[v7->summonindex[(u8)idx]])
  {
    v7 = wk;
    if (v7->battlemode != 3)
      return 0;
  }
  v8 = wk;
  UnitMng = v8->UnitMng;
  v10 = v8->summonID[v8->summonindex[v6]];
  result = sBtlSearchUnit_ID(UnitMng, v10);
  if (!result || !result->para->devilid)
    return 0;
  return result;
}

// 0x1f3fed0
SBTLUNIT_WORK *sBtlGetPChara(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;

  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  return sBtlSearchUnit_ID(UnitMng, playerID);
}

// 0x1f498c0
s32 sBtlGetSmnNo(SBTLUNIT_WORK *pUnit) {
  s32 v5;
  s32 ListID;
  SBATTLE_WORK *v8;
  s32 v9;
  s32 v10;

  goto LABEL_3;
LABEL_7:
  ListID = pUnit->ListID;
  if (ListID != wk->summonID[(s16)v5])
    goto LABEL_11;
  return 0;
LABEL_3:
  v5 = wk->summonindex[0];
  if ((v5 & 0x80000000) == 0)
    goto LABEL_7;
LABEL_11:
  v8 = wk;
  v9 = v8->summonindex[1];
  if (v9 < 0)
    return -1;
  v10 = pUnit->ListID;
  if (v10 == v8->summonID[(s16)v9])
    return 1;
  return -1;
}

// 0x1f44600
void sBtlInitRedGg(RED_GUAGE *pRedGg, s32 hp) {
  if (pRedGg)
  {
    pRedGg->bgn = hp;
    pRedGg->cnt = 0;
  }
}

// 0x1f49a60
void sBtlDrawRedGg(s32 x, s32 y, RED_GUAGE *pRedGg, s32 hp, s32 maxhp) {
  s32 bgn;
  s32 len;
  s32 v8;
  s32 cnt;
  s32 v10;

  bgn = pRedGg->bgn;
  if (bgn >= hp)
  {
    if (bgn <= hp)
      goto LABEL_7;
    v8 = 400;
    pRedGg->bgn = hp;
    pRedGg->len = bgn;
  }
  else
  {
    len = pRedGg->len;
    pRedGg->bgn = hp;
    if (len >= hp)
      goto LABEL_7;
    v8 = 0;
  }
  pRedGg->cnt = v8;
LABEL_7:
  cnt = pRedGg->cnt;
  if (cnt >= 256)
  {
    v10 = cnt - 1;
  }
  else
  {
    if (cnt < 2)
      return;
    if (cnt <= 10)
      cnt = 10;
    v10 = cnt - 10;
  }
  pRedGg->cnt = v10;
}

// 0x1f49ad0
void sBtlMain_Now_Omikuji_Draw(s32 alpha) {
  if (!wk->RouletteAns)
    return;
  wk->status4 |= 0x2000u;
  cnf = cnf + 0.08;
}

// 0x1f49bc0
bool sBtlCheckLastEnemyDead(SBTLUNIT_WORK *wk) {
  s64 i;
  SBATTLE_WORK *v7;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  bool v10;
  s32 playerID;
  SBTLUNIT_WORK *v13;
  SBATTLE_WORK *v15;
  u32 status;
  s32 mode;

  if ((wk->side & 2) == 0)
    return 0;
  for (i = 0; ; ++i)
  {
    v7 = wk;
    UnitMng = v7->UnitMng;
    if (i >= UnitMng->number)
      break;
    UnitMng = wk->UnitMng;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (pUnit)
      v10 = pUnit == wk;
    else
      v10 = 1;
    if (!v10 && (pUnit->side & 2) != 0)
    {
      if (pUnit->para->now->hp > 0)
        return 0;
      if (!sBtlCheckLiveTarget2(pUnit))
        continue;
      if (sBtlCheckDamageTarget(pUnit))
        return 0;
    }
  }
  playerID = v7->playerID;
  v13 = sBtlSearchUnit_ID(UnitMng, playerID);
  v15 = wk;
  if (v15->kaiwaflg)
    goto LABEL_49;
  if (v15->bNoEndCam)
    goto LABEL_49;
  if (v13->actwk->status == 34)
    goto LABEL_49;
  v15 = wk;
  if ((v15->status & 0x1000000) != 0)
    goto LABEL_49;
  status = v13->actwk->status;
  if (status == 10 || status == 40)
    goto LABEL_49;
  v15 = wk;
  mode = v15->mode;
  if (mode == 5)
    goto LABEL_49;
  mode = wk->mode;
  if (mode == 6)
    goto LABEL_49;
  mode = wk->mode;
  if (mode == 13)
  {
LABEL_49:
    return BYTE2(wk->status2) & 1;
  }
  if (!sBtlCheckGeneratorAll())
    return 1;
  if (!sBtlCheckGenerator_ND())
    return 1;
  return BYTE2(wk->status2) & 1;
}
