#include "types.h"
#include "SKLID.h"
#include "achievement.h"
#include "cfg.h"
#include "cmpmenuopen.h"
#include "cmpmodel.h"
#include "cmpomoide.h"
#include "cmpraidouskill.h"
#include "cmpstatus.h"
#include "dat.h"
#include "dds3kernelcore.h"
#include "dds3kernelmain.h"
#include "dvl.h"
#include "evtbit.h"
#include "fld.h"
#include "gohcalc.h"
#include "gohdevilres.h"
#include "gohinit.h"
#include "gohswordhistory.h"
#include "kernel.h"
#include "raijindlc.h"
#include "sbattle.h"
#include "sbtl.h"
#include "sbtlbossevent.h"
#include "sbtlcalc.h"
#include "sbtldvltk.h"
#include "sbtlitem.h"
#include "sbtlmain.h"
#include "sbtlskill.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sbtlweapon.h"
#include "scr.h"
#include "sdat.h"
#include "sdfvsync.h"
#include "titlemain.h"

#define DDS3_GLOBALWORK_PROCESS_NAME "GBWK"
#define assetKey "datatbl"
#define assetKeyDlc "datatbl"
#define filterAssetName "FclFilterTbl"
#define PARAM_VAL_MAX 40
#define PARAM_CALC_MAX 255
#define MAX_HP 999
#define MAX_MP 999
#define DEFAULT_SWORD_NO 1
#define DEFAULT_SWORD_ATK 10
#define STRONG_SWORD_ATK 50
#define MAX_MAG 300
#define DEFAULT_SPRIT_CNT 6
#define GOLD_MAX 9999999
#define openNumTop 8192

typedef struct DEVILDATA_WORK DEVILDATA_WORK;
typedef struct NewGame2_t NewGame2_t;
typedef struct datCalcBase_t datCalcBase_t;
typedef struct datDevilAI_t datDevilAI_t;
typedef struct datEncountBG_t datEncountBG_t;
typedef struct datEncountFld_t datEncountFld_t;
typedef struct datEncountPack_t datEncountPack_t;
typedef struct datEncountRare_t datEncountRare_t;
typedef struct datEncount_t datEncount_t;
typedef struct datFldHuntTbl_t datFldHuntTbl_t;
typedef struct datItem_t datItem_t;
typedef struct datLinkageSkillList_t datLinkageSkillList_t;
typedef struct datLinkageSkillVisual_t datLinkageSkillVisual_t;
typedef struct datLinkageSkill_t datLinkageSkill_t;
typedef struct datNormalSkillVisual_t datNormalSkillVisual_t;
typedef struct datNormalSkill_t datNormalSkill_t;
typedef struct datPlayerAttackGun_t datPlayerAttackGun_t;
typedef struct datSkill_t datSkill_t;
typedef struct datSpecialSkill_t datSpecialSkill_t;
typedef struct datTakaraSagasi_t datTakaraSagasi_t;
typedef struct datUnitCamera_t datUnitCamera_t;
typedef struct datUnitMotionSE_t datUnitMotionSE_t;
typedef struct datUnitVisual_t datUnitVisual_t;
typedef struct datUnitWork_t datUnitWork_t;
typedef struct dds3GlobalWork_t dds3GlobalWork_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct gohSwordHistory_t gohSwordHistory_t;
typedef struct sdatLvUpPlayerParamUp_t sdatLvUpPlayerParamUp_t;
typedef struct sdatLvUpPlayerRankUp_t sdatLvUpPlayerRankUp_t;
typedef struct sdatPlayerUnitWork_t sdatPlayerUnitWork_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;
typedef struct shpSave_t shpSave_t;

struct NewGame2_t {
    bool SYS_ENDING0;
    u16 endcnt;
    u32 playtime;
    bool SYS_SYS_HARD_ON;
    bool SYS_RANK[15];
    bool SYS_RANK2[14];
    bool SYS_GOU_ITIMOK_ON[18];
    bool SYS_GOU_HAYATARO_ON[4];
    bool SYS_ZIM_MAHJON_ON;
    bool SYS_KON_HANAFU_ON;
    shpSave_t *shpSave;
    s32 total_cyuusei;
    s32 stock_max;
    s32 maxmag;
    s32 syougou;
    bool setSyougou;
    bool RankTips[2];
    bool *dbook_readFlag;
    s32 *dbook_updateFlag;
    bool dbook_OpenFlag[1750];
    f64 totalPlayTime;
    bool *quest_clearSave;
    gohSwordHistory_t *SwordHistory;
    sdatPlayerUnitWork_t *player;
    s32 gold;
    s32 maxgold;
};

datUnitWork_t *PlayerUnitWork;
u32 *AtmaAisyo;
u32 *HumanAisyo;
datUnitVisual_t *PlayerVisual;
datUnitMotionSE_t *PlayerMotSE;
datPlayerAttackGun_t *PlayerAttackGun;
datUnitVisual_t *DevilVisual;
datDevilAI_t *DevilAI;
datUnitMotionSE_t *DevilMotSE;
u32 *datDevilAisyo;
datUnitCamera_t *datDevilCamera;
datEncount_t *Encount;
datEncountFld_t *EncountFld;
datEncountPack_t *EncountPack;
datEncountRare_t *EncountRare;
datEncountBG_t *EncountBG;
datFldHuntTbl_t *FldHuntTbl;
datSkill_t *Skill;
datNormalSkill_t *NormalSkill;
datLinkageSkill_t *LinkageSkill;
datLinkageSkillList_t *LinkageSkillList;
datSpecialSkill_t *SpecialSkill;
datNormalSkillVisual_t *NormalSkillVisual;
datLinkageSkillVisual_t *LinkageSkillVisual;
datItem_t *Item;
datCalcBase_t *CalcBase;
u8 *PlayerName;
u8 *DevilName;
u8 *AtmaName;
u8 *AtmaAisyoName;
u8 *DevilAisyoName;
u8 *ItemName;
u8 *RaceName;
u8 *SkillName;
u8 *MahenName;
u8 *MashoName;
u8 *SkillHelp;
u8 *ItemHelp;
u8 *ActionMiscHelp;
u8 *JyokyoHelp;
char *ai_scr;
char *calc_scr;
s32 datEncountBase;
datTakaraSagasi_t *TakaraSagasi;
u8 *HeartsHelp;
u8 *PlayerRaceName;
u8 *HeartsName;
void *sdatLvUpDevilGiftTbl;
void *sdatLvUpDevilGiftTbl_DLC;
s32 sdatLvUpDevilGiftSize;
s32 sdatLvUpDevilParamUpSize;
sdatLvUpPlayerParamUp_t *sdatLvUpPlayerParamUp;
s32 sdatLvUpPlayerParamUpSize;
sdatLvUpPlayerRankUp_t *sdatLvUpPlayerRankUp;
s32 sdatLvUpPlayerRankUpSize;
s32 gohDevilParamSize;
u16 *gohSameDevils;
s32 gohSameDevilsSize;
void *gohKarteWakuSetting;
static sdatPlayerUnitWork_t *levelUpPlayerUnit;
s16 *s_aSummonerRankTbl;
static s32 select_dvl_uniq;
dds3GlobalWork_t *GBWK;
s32 gb_btltime;
s32 gb_btlaitime;

static s32 CheckJidouSkillPrio(sdatUnitWork_t *pUnit, SKLID SkillID);
static void SetPlayerStanceNum(s32 num);
static dds3ProcessFunc_t dds3GlobalWorkMainProc(dds3ProcessID_t *procID);
static void UserInit(void);
static void UserDestroy(void);
static void GlobalWorkNewGame(void);
static NewGame2_t *NewGame2Push(void);
static void NewGame2Pop(NewGame2_t *NewGame2);

// 0x18f5db0
void datInitPlayer(void) {
  dds3GlobalWork_t *GBWK_local;
  sdatPlayerUnitWork_t *v3;
  s64 v7;
  sdatPlayerUnitWork_t *player;
  sdatUnitWork_t *para;
  char *v10;
  s16 *item;
  sdatUnitWork_t *v13;

  GBWK_local = GBWK;
  v3 = Allocate(sdatPlayerUnitWork_t);
  _ctor(v3);
  GBWK_local->player = v3;
  v7 = 0;
  player = GBWK->player;
  para = player->para;
  para->level = 1;
  para->flag |= 3u;
  player->gold = 2000;
  player->swordatk = 10;
  *(u64 *)&player->mag = 0x12C00000000LL;
  while (1)
  {
    item = GBWK->player->item;
    if (v7 >= SLODWORD(item->max_length))
      break;
    item = GBWK->player->item;
    v10 = (char *)item + 2 * v7++;
    *((u16 *)v10 + 16) = 0;
  }
  datAddItem(145, 1);
  gohOnSwordHave(1);
  PlayerInit(GBWK->sortSave, 0);
  *(u32 *)GBWK->player->stack_p = -1;
  sBtlInitPlayerData();
  datSetPlayerUnitSword(GBWK->player, 1, v13);
  *(u64 *)&GBWK->player->spiritCnt = 0x100000006LL;
}

// 0x18f6450
s32 datGetPlayerParam(s32 id) {
  s32 result;

  switch (id)
  {
    case 0:
      result = GBWK->player->para->now->hp;
      break;
    case 1:
      result = GBWK->player->para->now->maxhp;
      break;
    case 2:
      result = GBWK->player->para->now->mp;
      break;
    case 3:
      result = GBWK->player->para->now->maxmp;
      break;
    case 4:
      result = GBWK->player->para->now->str;
      break;
    case 5:
      result = GBWK->player->para->now->vit;
      break;
    case 6:
      result = GBWK->player->para->now->tec;
      break;
    case 7:
      result = GBWK->player->para->now->luck;
      break;
    case 8:
      result = GBWK->player->stock_max;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}

// 0x18f66f0
void datSetPlayerParam(s32 id, s32 nums) {
  switch (id)
  {
    case 0:
      GBWK->player->para->now->hp = nums;
      break;
    case 4:
      GBWK->player->para->now->str = nums;
      break;
    case 5:
      GBWK->player->para->now->vit = nums;
      break;
    case 6:
      GBWK->player->para->now->tec = nums;
      break;
    case 7:
      GBWK->player->para->now->luck = nums;
      break;
    case 8:
      GBWK->player->mag = nums;
      break;
    default:
      return;
  }
}

// 0x18f68e0
s32 datGetStockDevilID(s32 Index) {
  sdatUnitWork_t *v4;

  v4 = GBWK->player->stock_id[Index];
  if ((v4->flag & 1) != 0)
    return v4->devilid;
  else
    return 0;
}

// 0x18f6980
u32 datGetStockUniqCode(s32 Index) {
  sdatUnitWork_t *v4;

  v4 = GBWK->player->stock_id[Index];
  if ((v4->flag & 1) != 0)
    return v4->uniq_code;
  else
    return 0;
}

// 0x18f6a20
void datDlcNoneCheck(void) {
  s64 v1;
  sdatPlayerUnitWork_t *player;
  s16 *stack_p;
  s64 v5;
  s32 devilid;
  bool v7;

  v1 = 16;
  while (1)
  {
    player = GBWK->player;
    stack_p = player->stack_p;
    if (v1 - 16 >= SLODWORD(stack_p->max_length))
      break;
    v5 = *((s16 *)&stack_p->obj.klass + v1);
    if (v5 == -1)
      goto LABEL_5;
    player = GBWK->player;
    devilid = player->stock_id[v5]->devilid;
    v7 = DlcDevilSelCheck(devilid);
    if (v7)
      goto LABEL_5;
    *((u16 *)&GBWK->player->stack_p->obj.klass + v1) = -1;
LABEL_5:
    ++v1;
  }
}

// 0x18f6bb0
s32 datAdjustStock(bool _stack) {
  sdatUnitWork_t *v5;
  sdatUnitWork_t *v9;
  u64 v13;
  s32 v14;
  sdatUnitWork_t *v15;
  u64 i;
  s64 v17;
  s32 devilid;
  u32 uniq_code;
  s16 StockDevilIndex;
  s32 v22;
  u32 v23;

  if (stack)
  {
    if (GBWK->player->stack_p[0] == -1)
    {
      v5 = 0;
LABEL_11:
      if (GBWK->player->stack_p[1] == -1)
      {
        v9 = 0;
      }
      else
      {
        v9 = Allocate(sdatUnitWork_t);
        _ctor(v9);
        ClassCopy(v9, GBWK->player->stock_id[GBWK->player->stack_p[1]]);
      }
      goto LABEL_19;
    }
    else
    {
      v5 = Allocate(sdatUnitWork_t);
      _ctor(v5);
      ClassCopy(v5, GBWK->player->stock_id[GBWK->player->stack_p[0]]);
      goto LABEL_11;
    }
    goto LABEL_11;
  }
  v9 = 0;
  v5 = 0;
LABEL_19:
  v13 = 0;
  v14 = 0;
  do
  {
    v15 = GBWK->player->stock_id[v13];
    if ((v15->flag & 1) == 0 || !v15->devilid)
    {
      if (v13 <= 0x1E)
      {
        for (i = v13; i != 31; ++i)
        {
          v17 = (s64)GBWK->player->stock_id + 8 * i;
          ClassCopy(*(sdatUnitWork_t *)(v17 + 32), *(sdatUnitWork_t *)(v17 + 40));
        }
      }
      ClassClear(GBWK->player->stock_id[31]);
      v14 = 1;
    }
    ++v13;
  }
  while (v13 != 32);
  if (v5)
  {
    devilid = v5->devilid;
    uniq_code = v5->uniq_code;
    StockDevilIndex = datGetStockDevilIndex(devilid, uniq_code);
    GBWK->player->stack_p[0] = StockDevilIndex;
  }
  if (v9)
  {
    v22 = v9->devilid;
    v23 = v9->uniq_code;
    GBWK->player->stack_p[1] = datGetStockDevilIndex(v22, v23);
  }
  return v14;
}

// 0x18f72c0
s32 datGetEmptyStockCnt(void) {
  s64 v2;
  s32 v3;
  sdatUnitWork_t *v4;

  v2 = 0;
  v3 = 0;
  while (1)
  {
    if (v2 >= GBWK->player->stock_max)
      return v3;
    v4 = GBWK->player->stock_id[v2];
    if ((v4->flag & 1) == 0 || !v4->devilid)
      ++v3;
    ++v2;
  }
}

// 0x18f73e0
s32 datGetEmptyStock(void) {
  s64 v2;
  s32 v3;
  sdatUnitWork_t *v4;

  v2 = 0;
  v3 = -1;
  while (v2 < GBWK->player->stock_max)
  {
    v4 = GBWK->player->stock_id[v2];
    if ((v4->flag & 1) == 0 || !v4->devilid)
      return v2;
    ++v2;
  }
  return v3;
}

// 0x18f7500
s32 datCheckSameDevil(s32 DevilID) {
  s64 v4;
  s32 v5;

  v4 = 0;
  v5 = -1;
  while (1)
  {
    if (v4 >= gohSameDevilsSize / 2)
      return v5;
    if (gohSameDevils[v4] == DevilID)
      return v4;
    ++v4;
  }
}

// 0x18f75d0
void *datGetSameStockIndexList(s32 _devilID) {
  void *v3;
  s64 v4;
  s32 v5;
  sdatUnitWork_t *stock_id;
  s64 size;
  u64 *v9;
  s32 *items;

  v3 = Allocate(System_Collections_Generic_List_int_);
  __ctor(v3);
  v4 = 0;
  v5 = v3->_version + 1;
  v3->_size = 0;
  v3->_version = v5;
  while (1)
  {
    stock_id = GBWK->player->stock_id;
    if (v4 >= SLODWORD(stock_id->max_length))
      return v3;
    if (stock_id[v4]->devilid == devilID)
    {
      size = v3->_size;
      v9 = Method_System_Collections_Generic_List_int__Add__;
      ++v3->_version;
      items = v3->_items;
      if ((u32)size >= LODWORD(items->max_length))
      {
        _AddWithResize(v3, v4, *(const MethodInfo_2D8F530 **)(*(u64 *)(v9[4] + 192) + 112));
      }
      else
      {
        v3->_size = size + 1;
        items[size] = v4;
      }
    }
    ++v4;
  }
}

// 0x18f6f00
s32 datGetStockDevilIndex(s32 DevilID, u32 UniqCode) {
  s64 v5;
  sdatUnitWork_t *v8;
  sdatUnitWork_t *v9;
  s64 v11;
  s64 v13;
  s64 v14;
  sdatUnitWork_t *v16;

  if (DevilID)
  {
    v5 = 0;
    while (1)
    {
      if (v5 >= GBWK->player->stock_max)
        break;
      v8 = GBWK->player->stock_id[v5];
      if (!((v8->flag & 1) == 0 || v8->devilid != DevilID))
      {
        if (!UniqCode)
          return v5;
        v9 = GBWK->player->stock_id[v5];
        if ((v9->flag & 1) != 0 && v9->uniq_code == UniqCode)
          return v5;
      }
      ++v5;
    }
    v11 = 0;
    LODWORD(v5) = -1;
    goto LABEL_37;
    while (1)
    {
LABEL_37:
      if (v11 >= gohSameDevilsSize / 2)
        return v5;
      if (gohSameDevils[v11] == DevilID)
        break;
      ++v11;
    }
    if ((v11 & 0x80000000) == 0)
    {
      v13 = 0;
      LODWORD(v5) = -1;
      while (1)
      {
        if (v13 >= gohSameDevilsSize / 2)
          return v5;
        v14 = 0;
        while (v14 < GBWK->player->stock_max)
        {
          v16 = GBWK->player->stock_id[v14];
          if ((v16->flag & 1) != 0)
          {
            if (v16->devilid == gohSameDevils[v13])
            {
LABEL_64:
              LODWORD(v5) = v14;
              return v5;
            }
          }
          else if (!gohSameDevils[v13])
          {
            goto LABEL_64;
          }
          ++v14;
        }
        ++v13;
        continue;
      }
    }
  }
  LODWORD(v5) = -1;
  return v5;
}

// 0x18f7770
s32 datGetStockAliveDevilNum(void) {
  s32 v2;
  s64 i;
  s64 stock_max;
  s64 v6;

  v2 = 0;
  for (i = 4; ; ++i)
  {
    stock_max = GBWK->player->stock_max;
    if (i - 4 >= stock_max)
      break;
    v6 = *((u64 *)&GBWK->player->stock_id->obj.klass + i);
    if ((*(u8 *)(v6 + 16) & 1) != 0 && *(u16 *)(v6 + 22))
    {
      v6 = *((u64 *)&GBWK->player->stock_id->obj.klass + i);
      if (*(s32 *)(*(u64 *)(v6 + 40) + 16) > 0)
        ++v2;
    }
  }
  LODWORD(stock_max) = GBWK->player->stock_max;
  if (v2 <= (s32)stock_max)
    return v2;
  v2 = stock_max;
  return v2;
}

// 0x18f7930
s32 datGetStockDevilNums(bool dlc) {
  s32 v3;
  s64 i;
  s64 stock_max;
  s64 v8;
  s64 v10;
  s32 v11;
  bool v13;
  bool v14;

  v3 = 0;
  for (i = 4; ; ++i)
  {
    stock_max = GBWK->player->stock_max;
    if (i - 4 >= stock_max)
      break;
    v8 = *((u64 *)&GBWK->player->stock_id->obj.klass + i);
    if ((*(u8 *)(v8 + 16) & 1) == 0 || !*(u16 *)(v8 + 22))
      continue;
    if (!dlc)
      goto LABEL_4;
    v10 = *((u64 *)&GBWK->player->stock_id->obj.klass + i);
    if ((*(u8 *)(v10 + 16) & 1) != 0)
    {
      v11 = *(s16 *)(v10 + 22);
LABEL_25:
      v13 = DlcDevilSelCheck(v11);
      if (v13)
        goto LABEL_4;
      continue;
    }
    else
    {
      v11 = 0;
      goto LABEL_25;
    }
    v14 = DlcDevilSelCheck(v11);
    if (v14)
    {
LABEL_4:
      ++v3;
      continue;
    }
  }
  LODWORD(stock_max) = (char)stock_max;
  if (v3 <= (char)stock_max)
    return v3;
  v3 = stock_max;
  return GBWK->player->stock_max;
}

// 0x18f7b90
s32 datGetStockReprtStok(void) {
  sdatUnitWork_t *stock_id;
  s64 v3;
  s32 v4;
  sdatUnitWork_t *v5;
  s32 devilid;

  stock_id = GBWK->player->stock_id;
  if (SLODWORD(stock_id->max_length) >= 1)
  {
    v3 = 0;
    v4 = 0;
    while (1)
    {
      v5 = stock_id[v3];
      devilid = v5->devilid;
      if (DlcDevilSelCheck(devilid))
        goto LABEL_12;
      goto LABEL_9000;
      if (DlcDevilSelCheck(devilid))
LABEL_12:
        v4 += v5->DevilReportStok->_size;
LABEL_9000:
      if (++v3 >= SLODWORD(stock_id->max_length))
        return v4;
    }
  }
  return 0;
}

// 0x18f7cc0
DEVILDATA_WORK *datGetDevilFormat(s32 iDevilID) {
  return sBtlGetDevilData(iDevilID, -1);
}

// 0x18f7d30
s32 datGetKudaRace(s32 DevilID) {
  return sBtlGetDevilData(DevilID, -1)->kuda_id;
}

// 0x18f7da0
s32 datCheckSkillType(SKLID SkillID) {
  if ((tbldata[SkillID]->type & 0x1000) != 0)
    return 2;
  else
    return (u32)(SkillID - 240) < 0x30;
}

// 0x18f7e70
bool datCheckSkillPhysicDamage(SKLID SkillID) {
  SBTLSKILLP_TBL *Skilltbl;
  u16 type;

  Skilltbl = sBtlGetSkilltbl(SkillID);
  if (Skilltbl)
  {
    if ((Skilltbl->flg & 1) != 0)
    {
      if ((Skilltbl->attr & 0x401) != 0)
      {
        LOBYTE(Skilltbl) = 1;
      }
      else
      {
        type = Skilltbl->type;
        LOBYTE(Skilltbl) = 1;
        if ((type & 0xFFF) != 1 && (type & 0xFFF) != 7)
          LOBYTE(Skilltbl) = (type & 0xFFE) == 12;
      }
    }
    else
    {
      LOBYTE(Skilltbl) = 0;
    }
  }
  return (char)Skilltbl;
}

// 0x18f7ef0
bool datCheckSkillMagicDamage(SKLID SkillID) {
  SBTLSKILLP_TBL *Skilltbl;

  Skilltbl = sBtlGetSkilltbl(SkillID);
  if (Skilltbl)
  {
    if ((Skilltbl->flg & 1) != 0 && (Skilltbl->type & 0xFFFu) <= 0xF)
      LODWORD(Skilltbl) = (0x8028u >> LOBYTE(Skilltbl->type)) & 1;
    else
      LOBYTE(Skilltbl) = 0;
  }
  return (char)Skilltbl;
}

// 0x18f7f40
bool datCheckSkillGunDamage(SKLID SkillID) {
  SBTLSKILLP_TBL *Skilltbl;
  s32 v3;

  Skilltbl = sBtlGetSkilltbl(SkillID);
  if (Skilltbl)
  {
    if ((Skilltbl->flg & 1) != 0)
    {
      if ((Skilltbl->attr & 2) != 0)
      {
        LOBYTE(Skilltbl) = 1;
      }
      else
      {
        v3 = Skilltbl->type & 0xFFF;
        LOBYTE(Skilltbl) = v3 == 2 || v3 == 14;
      }
    }
    else
    {
      LOBYTE(Skilltbl) = 0;
    }
  }
  return (char)Skilltbl;
}

// 0x18f7fa0
SKLID datGetDefaultSkill(s32 DevilID, s32 SkillType) {
  s32 v5;
  s64 v7;
  s32 v8;
  s64 v10;
  s32 v11;
  s64 v13;
  s32 v14;
  s64 v15;
  s32 v17;

  v5 = sBtlGetDevilData(DevilID, -1)->haveskill[0];
  v7 = v5;
  if ((tbldata[v7]->type & 0x1000) != 0)
    v8 = 2;
  else
    v8 = (u32)(v5 - 240) < 0x30;
  if (v8 == SkillType)
    return v5;
  v5 = sBtlGetDevilData(DevilID, -1)->haveskill[1];
  v10 = v5;
  if ((tbldata[v10]->type & 0x1000) != 0)
    v11 = 2;
  else
    v11 = (u32)(v5 - 240) < 0x30;
  if (v11 == SkillType)
    return v5;
  v5 = sBtlGetDevilData(DevilID, -1)->haveskill[2];
  v13 = v5;
  if ((tbldata[v13]->type & 0x1000) != 0)
    v14 = 2;
  else
    v14 = (u32)(v5 - 240) < 0x30;
  if (v14 != SkillType)
  {
    v15 = sBtlGetDevilData(DevilID, -1)->haveskill[3];
LABEL_39:
    if ((tbldata[v15]->type & 0x1000) != 0)
      v17 = 2;
    else
      v17 = (u32)(v15 - 240) < 0x30;
    if (v17 == SkillType)
      return v15;
    else
      return 0;
    goto LABEL_39;
  }
  return v5;
}

// 0x18f83c0
s32 datCheckHaveSkill(sdatUnitWork_t *pUnit, SKLID SkillID) {
  SKLID *haveskill;

  haveskill = pUnit->haveskill;
  if (haveskill[0] == SkillID)
    return 1;
  if (haveskill[1] == SkillID)
    return 1;
  if (haveskill[2] == SkillID)
    return 1;
  if (haveskill[3] == SkillID)
    return 1;
  if (haveskill[4] == SkillID)
    return 1;
  if (haveskill[5] == SkillID)
    return 1;
  if (haveskill[6] == SkillID)
    return 1;
  if (haveskill[7] == SkillID)
    return 1;
  if (haveskill[8] == SkillID)
    return 1;
  if (haveskill[9] == SkillID)
    return 1;
  if (haveskill[10] == SkillID)
    return 1;
  if (haveskill[11] == SkillID)
    return 1;
  if (haveskill[12] == SkillID)
    return 1;
  if (haveskill[13] == SkillID)
    return 1;
  if (haveskill[14] == SkillID)
    return 1;
  if (haveskill[15] == SkillID)
    return 1;
  return haveskill[16] == SkillID;
}

// 0x18f8520
s32 datCheckHaveSkillCnt(sdatUnitWork_t *pUnit) {
  int32x4_t *haveskill;
  int8x8_t v3;
  int8x8_t v4;
  uint8x8_t v5;

  haveskill = pUnit->haveskill;
  v3.n64_u64[0] = vand_s8(vmovn_s16(vmvnq_s8(vuzp1q_s16(vceqzq_s32(haveskill[4]), vceqzq_s32(haveskill[5])))), (int8x8_t)0x8040201008040201LL).n64_u64[0];
  v4.n64_u64[0] = vand_s8(vmovn_s16(vmvnq_s8(vuzp1q_s16(vceqzq_s32(haveskill[2]), vceqzq_s32(haveskill[3])))), (int8x8_t)0x8040201008040201LL).n64_u64[0];
  v3.n64_u8[0] = vaddv_s8(v3);
  v4.n64_u8[0] = vaddv_s8(v4);
  v4.n64_u32[0] = (u16)(v4.n64_u16[0] | (v3.n64_u16[0] << 8));
  v5.n64_u64[0] = vcnt_s8(v4).n64_u64[0];
  v5.n64_u16[0] = vaddlv_u8(v5);
  if (haveskill[6].n128_u32[0])
    return v5.n64_u32[0] + 1;
  else
    return v5.n64_u32[0];
}

// 0x18f85b0
s32 datCheckRsvSkillCnt(sdatUnitWork_t *pUnit) {
  SKLID *aRsvSkl;
  s32 v3;
  s32 v4;
  s32 v5;
  _BOOL4 v6;
  s32 v7;

  aRsvSkl = pUnit->aRsvSkl;
  v3 = aRsvSkl[0];
  v4 = aRsvSkl[1];
  v5 = aRsvSkl[2];
  v6 = v4 != 0;
  if (v3)
    v7 = v6 + 1;
  else
    v7 = v6;
  if (v5)
    return v7 + 1;
  else
    return v7;
}

// 0x18f85e0
static s32 CheckJidouSkillPrio(sdatUnitWork_t *pUnit, SKLID SkillID) {
  s32 v7;
  s64 v8;
  s64 v9;

  v7 = 0;
  if ((u32)(SkillID - 240) > 0x2F)
    return v7;
  if ((tbldata[SkillID]->type & 0x1000) == 0)
  {
    v7 = 0;
    v8 = 32;
    while (1)
    {
      v9 = *(s32 *)((char *)&pUnit->haveskill->obj.klass + v8);
      if ((tbldata[v9]->type & 0x1000) == 0 && (u32)(v9 - 240) <= 0x2F)
      {
        ++v7;
        if ((u32)v9 == SkillID)
          return v7;
      }
      v8 += 4;
      if (v8 == 100)
        return 0;
    }
  }
  return v7;
}

// 0x18f8820
s32 datCheckSkillEnable(sdatUnitWork_t *pUnit, SKLID SkillID) {
  s32 v6;
  sdatUnitWork_t *p_fields;
  s32 level;
  s32 devilid;
  s32 v11;
  s32 v13;
  s32 v14;

  if (!SkillID)
    return 0;
  if ((u32)(SkillID - 240) > 0x2F || (tbldata[SkillID]->type & 0x1000) != 0)
  {
    if ((tbldata[SkillID]->type & 0x1000) == 0)
      return 1;
    p_fields = &pUnit->fields;
    if ((pUnit->flag & 8) != 0)
      return 1;
    level = pUnit->level;
    devilid = pUnit->devilid;
    if (sBtlGetDevilData(devilid, -1)->level >= level)
      return 0;
    v11 = 8;
    goto LABEL_32;
  }
  v6 = CheckJidouSkillPrio(pUnit, SkillID);
  if (v6 == 2)
  {
    if ((pUnit->flag & 0x20) != 0)
      return 1;
    goto LABEL_27;
  }
  if (v6 == 1 && (pUnit->flag & 0x10) != 0)
    return 1;
LABEL_27:
  v13 = pUnit->level;
  v14 = pUnit->devilid;
  if (sBtlGetDevilData(v14, -1)->level + 2 > v13)
    return 0;
  p_fields = &pUnit->fields;
  v11 = 48;
LABEL_32:
  p_fields->flag |= v11;
  return 1;
}

// 0x18f8a80
s32 datGetSkillCopyIndex(s32 SkillType) {
  if (SkillType == 2)
    return 4;
  else
    return 2 * (SkillType == 1);
}

// 0x18f8aa0
void datReplaceHaveSkill(sdatUnitWork_t *pUnit) {
  sdatUnitWork_t *v3;
  s32 v5;
  s64 i;
  s32 v7;
  s64 v9;
  s32 v10;
  s64 v11;
  s32 v12;
  s32 v14;
  s32 v15;
  s64 v16;
  s32 v17;
  s32 v19;
  SKLID *haveskill;
  SKLID *v21;

  v3 = Allocate(sdatUnitWork_t);
  _ctor(v3);
  v5 = 0;
  for (i = 32; i != 100; i += 4)
  {
    v7 = *(u32 *)((char *)&pUnit->haveskill->obj.klass + i);
    if (!v7)
      continue;
    if ((tbldata[v7]->type & 0x1000) == 0 && (u32)(v7 - 288) <= 0xFFFFFFCF)
    {
      v9 = (s64)v3->haveskill + 4 * v5++;
      *(u32 *)(v9 + 32) = v7;
    }
  }
  v10 = 0;
  v11 = 32;
  while (2)
  {
    v12 = *(u32 *)((char *)&pUnit->haveskill->obj.klass + v11);
    if (v12)
    {
      goto LABEL_26;
LABEL_27:
      goto LABEL_28;
LABEL_26:
      goto LABEL_27;
LABEL_28:
      if ((tbldata[v12]->type & 0x1000) == 0 && (u32)(v12 - 240) <= 0x2F)
      {
        v14 = v10 + 2;
        ++v10;
        v3->haveskill[v14] = v12;
      }
    }
    v11 += 4;
    if (v11 != 100)
      continue;
    break;
  }
  v15 = 0;
  v16 = 32;
  while (2)
  {
    v17 = *(u32 *)((char *)&pUnit->haveskill->obj.klass + v16);
    if (v17)
    {
      goto LABEL_42;
LABEL_43:
      goto LABEL_44;
LABEL_42:
      goto LABEL_43;
LABEL_44:
      if ((tbldata[v17]->type & 0x1000) != 0)
      {
        v19 = v15 + 4;
        ++v15;
        v3->haveskill[v19] = v17;
      }
    }
    v16 += 4;
    if (v16 != 100)
      continue;
    break;
  }
  haveskill = v3->haveskill;
  v21 = pUnit->haveskill;
  v21[0] = haveskill[0];
  v21[1] = haveskill[1];
  v21[2] = haveskill[2];
  v21[3] = haveskill[3];
  v21[4] = haveskill[4];
  v21[5] = haveskill[5];
  v21[6] = haveskill[6];
  v21[7] = haveskill[7];
  v21[8] = haveskill[8];
  v21[9] = haveskill[9];
  v21[10] = haveskill[10];
  v21[11] = haveskill[11];
  v21[12] = haveskill[12];
  v21[13] = haveskill[13];
  v21[14] = haveskill[14];
  v21[15] = haveskill[15];
  v21[16] = haveskill[16];
}

// 0x18f8e90
s32 datAddSkill(sdatUnitWork_t *pUnit, SKLID SkillID) {
  SKLID *haveskill;
  s32 *m_Items;
  s32 *v7;
  s32 v8;

  haveskill = pUnit->haveskill;
  m_Items = haveskill;
  if (haveskill[0])
  {
    m_Items = &haveskill[1];
    if (haveskill[1])
    {
      m_Items = &haveskill[2];
      if (haveskill[2])
      {
        m_Items = &haveskill[3];
        if (haveskill[3])
        {
          m_Items = &haveskill[4];
          if (haveskill[4])
          {
            m_Items = &haveskill[5];
            if (haveskill[5])
            {
              m_Items = &haveskill[6];
              if (haveskill[6])
              {
                m_Items = &haveskill[7];
                if (haveskill[7])
                {
                  m_Items = &haveskill[8];
                  if (haveskill[8])
                  {
                    m_Items = &haveskill[9];
                    if (haveskill[9])
                    {
                      m_Items = &haveskill[10];
                      if (haveskill[10])
                      {
                        m_Items = &haveskill[11];
                        if (haveskill[11])
                        {
                          m_Items = &haveskill[12];
                          if (haveskill[12])
                          {
                            m_Items = &haveskill[13];
                            if (haveskill[13])
                            {
                              m_Items = &haveskill[14];
                              if (haveskill[14])
                              {
                                m_Items = &haveskill[15];
                                if (haveskill[15])
                                {
                                  v8 = haveskill[16];
                                  v7 = &haveskill[16];
                                  if (v8)
                                    return 0;
                                  m_Items = v7;
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
  *m_Items = SkillID;
  datReplaceHaveSkill(pUnit);
  return 1;
}

// 0x18f8ff0
void datCreateDevilUnitEx(s32 DevilID, s32 SkillMode, sdatUnitWork_t *pUnit, s32 uniqCode) {
  u32 flag;
  DEVILDATA_WORK *DevilData;
  sdatParaWork_t *backup;
  sdatParaWork_t *v14;
  sdatParaWork_t *v15;
  sdatParaWork_t *v16;
  SBTLAISYO_DATAWORK *aisyo;
  DEVILDATA_WORK *v20;
  sdatParaWork_t *now;
  s32 maxmp;
  SKLID *sousaSkill;
  SKLID *v26;
  s64 v27;
  s32 v28;
  s32 v29;
  u32 v31;
  s64 v32;
  s64 v33;
  char *v34;
  s32 v35;
  SKLID *battleskill;
  u32 v37;
  s32 v39;
  s32 v41;
  s32 v43;
  char *v44;
  SKLID *v45;
  u32 v46;
  s64 v47;
  s64 v48;
  char *v49;
  s32 v50;
  s64 v53;
  char *v54;
  char *v55;
  sdatUnitWork_t *v56;
  s32 skill2[2];

  *(u64 *)skill2 = 0;
  ClassClear(pUnit, *(const MethodInfo **)&SkillMode);
  flag = pUnit->flag;
  pUnit->devilid = DevilID;
  pUnit->flag = flag | 5;
  pUnit->raceid = sBtlGetDevilData(DevilID, -1)->kuda_id;
  pUnit->level = sBtlGetDevilData(DevilID, -1)->level;
  DevilData = sBtlGetDevilData(DevilID, -1);
  backup = pUnit->backup;
  pUnit->seikaku = DevilData->seikaku;
  backup->str = sBtlGetDevilData(DevilID, -1)->str;
  v14 = pUnit->backup;
  v14->tec = sBtlGetDevilData(DevilID, -1)->tec;
  v15 = pUnit->backup;
  v15->vit = sBtlGetDevilData(DevilID, -1)->vit;
  v16 = pUnit->backup;
  v16->luck = sBtlGetDevilData(DevilID, -1)->luck;
  aisyo = pUnit->aisyo;
  v20 = sBtlGetDevilData(DevilID, -1);
  ClassCopy(aisyo, aisyo_tbldata[v20->aishou], 0);
  datCalcNowParam(pUnit, 0, 0);
  now = pUnit->now;
  skill2[0] = 255;
  skill2[1] = 255;
  maxmp = now->maxmp;
  now->hp = now->maxhp;
  now->mp = maxmp;
  mskGetNo(DevilID, &skill2[1], skill2);
  sousaSkill = pUnit->sousaSkill;
  sousaSkill[0] = fldChangeFromMskGetNoToSKLID(skill2[1]);
  v26 = pUnit->sousaSkill;
  v26[1] = fldChangeFromMskGetNoToSKLID(skill2[0]);
  v56 = pUnit;
  if (SkillMode == 1)
  {
    v27 = 0;
    v28 = 0;
    while (1)
    {
      v29 = sBtlGetDevilData(DevilID, -1)->haveskill[v27];
      if (!v29)
      {
        ++v28;
        goto LABEL_17;
      }
      if ((u32)(v29 - 288) > 0xFFFFFFCF)
        goto LABEL_17;
      if ((tbldata[v29]->type & 0x1000) == 0)
      {
        v31 = v27 - v28;
        if ((s32)v27 - v28 <= 0)
        {
          v33 = 4 * (s32)v31;
          v34 = (char *)v56->haveskill + v33;
          v32 = (s64)v56->battleskill + v33;
          *((u32 *)v34 + 8) = v29;
          goto LABEL_36;
        }
        if (v31 <= 3)
        {
          v32 = (s64)v56->aRsvSkl + 4 * (u32)(~v28 + v27);
LABEL_36:
          *(u32 *)(v32 + 32) = v29;
        }
      }
LABEL_17:
      if (++v27 == 4)
        goto LABEL_68;
    }
  }
  v35 = sBtlGetDevilData(DevilID, -1)->haveskill[0];
  if (v35)
  {
    battleskill = pUnit->battleskill;
    v37 = 0;
    pUnit->haveskill[0] = v35;
    battleskill[0] = v35;
    goto LABEL_42;
  }
  v37 = 1;
LABEL_42:
  v39 = sBtlGetDevilData(DevilID, -1)->haveskill[1];
  if (v39)
  {
    if (!v37)
    {
      pUnit->aRsvSkl[0] = v39;
      goto LABEL_46;
    }
    v53 = 4 * (v37 ^ 1);
    v54 = (char *)pUnit->haveskill + v53;
    v55 = (char *)pUnit->battleskill + v53;
    *((u32 *)v54 + 8) = v39;
    *((u32 *)v55 + 8) = v39;
  }
  else
  {
    ++v37;
  }
LABEL_46:
  v41 = sBtlGetDevilData(DevilID, -1)->haveskill[2];
  if (!v41)
  {
    ++v37;
    goto LABEL_61;
  }
  if (v37 < 2)
  {
    pUnit->aRsvSkl[1 - v37] = v41;
    goto LABEL_61;
  }
  v45 = pUnit->battleskill;
  v46 = 2 - v37;
  v37 = 2;
  v47 = v46;
  pUnit->haveskill[v47] = v41;
  v45[v47] = v41;
LABEL_61:
  v43 = sBtlGetDevilData(DevilID, -1)->haveskill[3];
  if (v43)
  {
    if (v37 >= 3)
    {
      v48 = 4 * (3 - v37);
      v49 = (char *)pUnit->haveskill + v48;
      v44 = (char *)pUnit->battleskill + v48;
      *((u32 *)v49 + 8) = v43;
    }
    else
    {
      v44 = (char *)pUnit->aRsvSkl + 4 * (2 - v37);
    }
    *((u32 *)v44 + 8) = v43;
  }
LABEL_68:
  v56->iOmoideSkillCnt = 1;
  v50 = uniqCode;
  v56->vice = 0;
  if (uniqCode < 0)
  {
    v50 = GBWK->nakama_uniq_cnt + 1;
    GBWK->nakama_uniq_cnt = v50;
  }
  v56->uniq_code = v50;
}

// 0x18f9d80
void datCreateDevilUnit(s32 DevilID, sdatUnitWork_t *pUnit) {
  datCreateDevilUnitEx(DevilID, 0, pUnit, -1);
}

// 0x18f9df0
s32 datAddCheckDevilUnit(sdatUnitWork_t *pUnit) {
  s32 devilid;
  u32 uniq_code;
  s32 result;

  devilid = pUnit->devilid;
  uniq_code = pUnit->uniq_code;
  if ((datGetStockDevilIndex(devilid, uniq_code) & 0x80000000) == 0)
    return -1;
  result = datGetEmptyStock();
  if (result < 0)
    return -2;
  return result;
}

// 0x18f9ec0
s32 datAddDevilUnit(sdatUnitWork_t *pUnit) {
  s32 devilid;
  u32 uniq_code;
  s32 v8;
  s32 EmptyStock;
  s8 v13;
  s32 v17;
  s32 kuda_id;
  s32 v21;
  s32 *EventBit;

  devilid = pUnit->devilid;
  uniq_code = pUnit->uniq_code;
  if ((datGetStockDevilIndex(devilid, uniq_code) & 0x80000000) == 0)
    return -1;
  EmptyStock = datGetEmptyStock();
  if ((EmptyStock & 0x80000000) == 0)
  {
    v8 = EmptyStock;
    pUnit->flag |= 5u;
    pUnit->TakaraCnt = sub_1905740(5, 0) + 6;
    pUnit->ZeniCnt = sub_1905740(5, 0) + 6;
    v13 = sub_1905740(5, 0) + 16;
    pUnit->TakumiCnt = v13;
    datCalcNowParam(pUnit, 0, 0);
    datNewCombiSkilAutoSet(pUnit);
    ClassCopy(GBWK->player->stock_id[v8], pUnit);
    AddGetDevilList(GBWK->sortSave, pUnit->devilid, pUnit->uniq_code, 0, 0);
    v17 = pUnit->devilid;
    kuda_id = (u8)sBtlGetDevilData(v17, -1)->kuda_id;
    if (kuda_id == 8)
    {
      v21 = 0x4000;
      goto LABEL_24;
    }
    else
    {
      if (kuda_id != 9)
        return v8;
      v21 = 0x8000;
      goto LABEL_24;
    }
LABEL_24:
    EventBit = GBWK->EventBit;
    EventBit[65] |= v21;
    return v8;
  }
  return -2;
}

// 0x18fa370
s32 datAddDevilEx(s32 DevilID, s32 SkillMode) {
  sdatUnitWork_t *v5;

  v5 = Allocate(sdatUnitWork_t);
  _ctor(v5);
  datCreateDevilUnitEx(DevilID, SkillMode, v5, -1);
  return datAddDevilUnit(v5);
}

// 0x18fa420
s32 datAddDevil(s32 DevilID) {
  s32 v5;

  v5 = DevilID;
  return datAddDevilEx(v5, 0);
}

// 0x18fa4b0
s32 datDelDevil(s32 DevilID, u32 UniqCode) {
  s32 StockDevilIndex;
  u32 v7;
  dds3GlobalWork_t *GBWK_local;
  s16 *stack_p;
  s32 v13;
  u32 v14;
  s32 v15;
  s16 *v16;
  sdatPlayerUnitWork_t *v17;
  sdatUnitWork_t *v18;
  s32 v19;
  s64 v20;
  s32 v21;
  sdatPlayerUnitWork_t *v22;
  sdatUnitWork_t *v23;
  s32 v24;
  s64 v25;
  sdatUnitWork_t *v26;
  u32 v27;
  u32 uniq_code;
  s16 *v29;
  sdatPlayerUnitWork_t *player;
  sdatUnitWork_t *v31;
  s64 v32;
  sdatUnitWork_t *v33;
  sdatUnitWork_t *v34;
  s32 v35;
  sdatPlayerUnitWork_t *v36;
  sdatUnitWork_t *v37;
  s64 v38;
  s64 v39;
  dds3GlobalWork_t *v40;
  SortSave *sortSave;
  sdatUnitWork_t *v42;

  StockDevilIndex = datGetStockDevilIndex(DevilID, UniqCode);
  if ((StockDevilIndex & 0x80000000) != 0)
    return -1;
  v7 = StockDevilIndex;
  GBWK_local = GBWK;
  if (GBWK_local->mapSummonID != DevilID)
  {
LABEL_13:
    goto LABEL_15;
  }
  if (GBWK_local->mapSummonUNIQ != UniqCode)
    goto LABEL_13;
  *(u64 *)&GBWK_local->mapSummonID = 0;
LABEL_15:
  stack_p = GBWK->player->stack_p;
  if (v7 != stack_p[0])
  {
    if (v7 == stack_p[1])
    {
      if (v14)
      {
        v15 = (u16)stack_p[0];
        stack_p[1] = -1;
        if (v15 == 0xFFFF)
          goto LABEL_61;
      }
      else
      {
        v29 = GBWK->player->stack_p;
        v15 = (u16)v29[0];
        v29[1] = -1;
        if (v15 == 0xFFFF)
          goto LABEL_61;
      }
      player = GBWK->player;
      v31 = player->stock_id[(s16)v15];
      if ((v31->flag & 1) != 0)
      {
        v24 = v31->devilid;
        v32 = player->stack_p[0];
LABEL_76:
        v34 = GBWK->player->stock_id[v32];
        if ((v34->flag & 1) != 0)
        {
          uniq_code = v34->uniq_code;
          v27 = 0;
        }
        else
        {
          v27 = 0;
          uniq_code = 0;
        }
        v19 = 0;
        goto LABEL_99;
      }
      else
      {
        v24 = 0;
        v32 = player->stack_p[0];
        goto LABEL_76;
      }
      goto LABEL_76;
    }
    if (v14)
    {
      v21 = (u16)stack_p[0];
      if (v21 != 0xFFFF)
        goto LABEL_38;
    }
    else
    {
      v21 = (u16)GBWK->player->stack_p[0];
      if (v21 != 0xFFFF)
      {
LABEL_38:
        v22 = GBWK->player;
        v23 = v22->stock_id[(s16)v21];
        if ((v23->flag & 1) != 0)
        {
          v24 = v23->devilid;
          v25 = v22->stack_p[0];
          goto LABEL_69;
        }
        else
        {
          v24 = 0;
          v25 = v22->stack_p[0];
LABEL_69:
          v33 = GBWK->player->stock_id[v25];
          if ((v33->flag & 1) != 0)
          {
            uniq_code = v33->uniq_code;
            goto LABEL_83;
          }
          else
          {
            uniq_code = 0;
            goto LABEL_83;
          }
LABEL_83:
          v35 = (u16)GBWK->player->stack_p[1];
          if (v35 == 0xFFFF)
          {
            v27 = 0;
            v19 = 0;
            goto LABEL_99;
          }
          v36 = GBWK->player;
          v37 = v36->stock_id[(s16)v35];
          if ((v37->flag & 1) != 0)
          {
            v19 = v37->devilid;
            v38 = v36->stack_p[1];
            goto LABEL_94;
          }
          else
          {
            v19 = 0;
            v38 = v36->stack_p[1];
LABEL_94:
            v26 = GBWK->player->stock_id[v38];
            if ((v26->flag & 1) == 0)
            {
              v27 = 0;
              goto LABEL_99;
            }
LABEL_98:
            v27 = v26->uniq_code;
            goto LABEL_99;
          }
          goto LABEL_94;
        }
        goto LABEL_69;
      }
    }
    uniq_code = 0;
    v24 = 0;
    goto LABEL_83;
  }
  v16 = GBWK->player->stack_p;
  v13 = (u16)v16[1];
  v16[0] = -1;
  if (v13 != 0xFFFF)
    goto LABEL_29;
LABEL_61:
  v27 = 0;
  uniq_code = 0;
  v19 = 0;
  v24 = 0;
  goto LABEL_99;
LABEL_29:
  v17 = GBWK->player;
  v18 = v17->stock_id[(s16)v13];
  if ((v18->flag & 1) != 0)
  {
    v19 = v18->devilid;
    v20 = v17->stack_p[1];
    goto LABEL_46;
  }
  v19 = 0;
  v20 = v17->stack_p[1];
LABEL_46:
  v26 = GBWK->player->stock_id[v20];
  if ((v26->flag & 1) != 0)
  {
    uniq_code = 0;
    v24 = 0;
    goto LABEL_98;
  }
  v27 = 0;
  uniq_code = 0;
  v24 = 0;
LABEL_99:
  v39 = v7;
  v40 = GBWK;
  sortSave = v40->sortSave;
  v42 = v40->player->stock_id[v39];
  AddGetDevilList(sortSave, v42->devilid, v42->uniq_code, 1, 0);
  ClassClear(GBWK->player->stock_id[v39]);
  datAdjustStock(0);
  if (v24)
  {
    v7 = datGetStockDevilIndex(v24, uniq_code);
    if ((v7 & 0x80000000) == 0)
    {
      GBWK->player->stack_p[0] = v7;
    }
  }
  if (v19)
  {
    v7 = datGetStockDevilIndex(v19, v27);
    if ((v7 & 0x80000000) == 0)
    {
      GBWK->player->stack_p[1] = v7;
    }
  }
  return v7;
}

// 0x18fa1d0
void datNewCombiSkilAutoSet(sdatUnitWork_t *_unit) {
  SKLID *haveskill;
  s64 i;
  s32 v5;
  s32 v7;

  haveskill = unit->haveskill;
  if (SLODWORD(haveskill->max_length) >= 1)
  {
    for (i = 0; i < SLODWORD(haveskill->max_length); ++i)
    {
      v5 = haveskill[i];
      if ((tbldata[v5]->type & 0x1000) != 0 && IndexOf_Int32Enum_(unit->combSkill, v5) == -1)
      {
        v7 = IndexOf_Int32Enum_(unit->combSkill, 0);
        if (v7 == -1)
          return;
        unit->combSkill[v7] = v5;
      }
      haveskill = unit->haveskill;
    }
  }
}

// 0x18fad10
void datCombiSkilAutoSet(sdatUnitWork_t *_unit, SKLID _skl) {
  s32 v7;

  if ((tbldata[skl]->type & 0x1000) != 0 && IndexOf_Int32Enum_(unit->combSkill, skl) == -1)
  {
    v7 = IndexOf_Int32Enum_(unit->combSkill, 0);
    if (v7 != -1)
      unit->combSkill[v7] = skl;
  }
}

// 0x18fae90
SKLID datGetCombiSkillSetting(CombiSetting _setting) {
  s32 v5;
  s32 v7;
  s64 v9;
  u32 v10;
  s32 v11;
  s64 v12;
  sdatUnitWork_t *v13;
  sdatUnitWork_t *v14;

  v5 = setting - 1;
  if ((u32)setting > 1)
  {
    v7 = GBWK->player->stack_p[1];
    if (v7 < 0)
      return 0;
    goto LABEL_11;
  }
  v7 = GBWK->player->stack_p[0];
  if (v7 < 0)
    return 0;
LABEL_11:
  v9 = (u16)v7;
  v11 = (v5 & 0xFFFFFFFD) == 0;
  v12 = (s64)GBWK->player->stock_id + 8 * v9;
  v13 = *(sdatUnitWork_t *)(v12 + 32);
  if (v10)
  {
    v14 = *(sdatUnitWork_t *)(v12 + 32);
  }
  else
  {
    v14 = v13;
  }
  return datGetDvlCombiSetting(v14, v11);
}

// 0x18fafc0
SKLID datGetDvlCombiSetting(sdatUnitWork_t *_unit, s32 _index) {
  s32 v5;
  SKLID *haveskill;
  s64 v7;
  s32 v8;
  s32 v9;
  s64 v12;

  v5 = 0;
  if (unit)
  {
    if (index <= 1)
    {
      v5 = unit->combSkill[index];
      if (!v5)
      {
        haveskill = unit->haveskill;
        if (SLODWORD(haveskill->max_length) >= 1)
        {
          if (index)
          {
            v7 = 0;
            v8 = 0;
            while (1)
            {
              v9 = haveskill[v7];
              if ((tbldata[v9]->type & 0x1000) != 0)
              {
                if (v8)
                  return v9;
                v8 = 1;
              }
              haveskill = unit->haveskill;
              if (++v7 >= SLODWORD(haveskill->max_length))
                return 0;
            }
          }
          v12 = 0;
          while (1)
          {
            v5 = haveskill[v12];
            if ((tbldata[v5]->type & 0x1000) == 0)
            {
              haveskill = unit->haveskill;
              ++v12;
              v5 = 0;
              if (v12 < SLODWORD(haveskill->max_length))
                continue;
            }
            return v5;
          }
        }
        return 0;
      }
    }
  }
  return v5;
}

// 0x18fb230
void datLoadLevelUpTable(void) {
  void *Asset;
  s64 naturalAligment;
  void *v7;
  void *p_sdatLvUpDevilGiftTbl;
  void *v10;
  void *v11;
  void *v13;
  s64 v15;
  void *v16;
  void *v17;
  void *p_sdatLvUpDevilGiftTbl_DLC;
  sdatLvUpPlayerParamUp_t **p_sdatLvUpPlayerParamUp;
  sdatLvUpPlayerRankUp_t **p_sdatLvUpPlayerRankUp;

  Load(Dependent, "datatbl", "datatbl");
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  Asset = LoadAsset(_Ctrl_k__BackingField, "datatbl", "RstLvUpDevilGiftTbl", 0);
  if (!Asset)
  {
    p_sdatLvUpDevilGiftTbl = &sdatLvUpDevilGiftTbl;
    p_sdatLvUpDevilGiftTbl = 0;
    goto LABEL_32;
  }
  if (Asset->klass->_2.naturalAligment >= (u32)naturalAligment)
  {
    if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == RstLvUpDevilGiftTbl)
      v7 = Asset;
    else
      v7 = 0;
  }
  else
  {
    v7 = 0;
  }
  sdatLvUpDevilGiftTbl = (void *)v7;
  v10 = &sdatLvUpDevilGiftTbl;
  if (Asset->klass->_2.naturalAligment < (u32)naturalAligment)
  {
    goto LABEL_32;
  }
  if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == RstLvUpDevilGiftTbl)
    v11 = Asset;
  else
    v11 = 0;
LABEL_32:
  v13 = LoadAsset(_Ctrl_k__BackingField, "datatbl", "RstLvUpDevilGiftTbl_DLC", 0);
  if (v13)
  {
    if (v13->klass->_2.naturalAligment >= (u32)v15)
    {
      if (v13->klass->_2.typeHierarchy[v15 - 1] == RstLvUpDevilGiftTbl)
        v16 = v13;
      else
        v16 = 0;
    }
    else
    {
      v16 = 0;
    }
    sdatLvUpDevilGiftTbl_DLC = (void *)v16;
    p_sdatLvUpDevilGiftTbl_DLC = &sdatLvUpDevilGiftTbl_DLC;
    if (v13->klass->_2.naturalAligment >= (u32)v15)
    {
      if (v13->klass->_2.typeHierarchy[v15 - 1] == RstLvUpDevilGiftTbl)
        v17 = v13;
      else
        v17 = 0;
    }
    else
    {
      v17 = 0;
    }
  }
  else
  {
    v17 = 0;
    p_sdatLvUpDevilGiftTbl_DLC = &sdatLvUpDevilGiftTbl_DLC;
    p_sdatLvUpDevilGiftTbl_DLC = 0;
  }
  Unload(Dependent, "datatbl", 0);
  p_sdatLvUpPlayerParamUp = &sdatLvUpPlayerParamUp;
  *p_sdatLvUpPlayerParamUp = sdatLvUpPlayerParamUp;
  p_sdatLvUpPlayerRankUp = &sdatLvUpPlayerRankUp;
  *p_sdatLvUpPlayerRankUp = sdatLvUpPlayerRankUp;
}

// 0x18fb5e0
void datLoadGohmadenTable(void) {
  void *p_Dependent;
  void *Dependent_local;
  void *Asset;
  s64 naturalAligment;
  void *v10;
  void *v11;
  void *p_gohKarteWakuSetting;

  p_Dependent = &Dependent;
  Dependent_local = p_Dependent;
  Load(Dependent_local, gohAssetName, gohAssetName);
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  Asset = LoadAsset(_Ctrl_k__BackingField, gohAssetName, "GohKarteWakuSetting", 0);
  if (!Asset)
  {
    v11 = 0;
    p_gohKarteWakuSetting = &gohKarteWakuSetting;
    p_gohKarteWakuSetting = 0;
    goto LABEL_31;
  }
  if (Asset->klass->_2.naturalAligment >= (u32)naturalAligment)
  {
    if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == GohKarteWakuSetting)
      v10 = Asset;
    else
      v10 = 0;
  }
  else
  {
    v10 = 0;
  }
  gohKarteWakuSetting = (void *)v10;
  p_gohKarteWakuSetting = &gohKarteWakuSetting;
  if (Asset->klass->_2.naturalAligment >= (u32)naturalAligment)
  {
    if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == GohKarteWakuSetting)
      v11 = Asset;
    else
      v11 = 0;
  }
  else
  {
    v11 = 0;
  }
LABEL_31:
  Unload(Dependent, gohAssetName, 0);
}

// 0x18fb870
s32 datGetPlayerExp(s32 Level) {
  if (Level == 1)
    return 0;
  if (Level >= 99)
    Level = 99;
  return PLAYER_EXP(Level);
}

// 0x18fb8a0
s32 datGetPlayerLevelUpNums(sdatPlayerUnitWork_t *pUnit) {
  s32 v3;
  sdatUnitWork_t *para;
  s8 level;
  s32 exp;
  s32 v8;
  s32 v9;
  sdatUnitWork_t *v10;

  v3 = 1;
  para = pUnit->para;
  level = para->level;
  exp = para->exp;
LABEL_4:
  v8 = v3 + level;
  if (v8 == 1)
  {
    if (exp >= 0)
      goto LABEL_12;
  }
  else
  {
    while (1)
    {
      v9 = v8 >= 99 ? 99 : v8;
      if (exp < PLAYER_EXP(v9))
        break;
LABEL_12:
      v10 = pUnit->para;
      if (v3 + v10->level > 99)
        return v3 - 1;
      level = v10->level;
      ++v3;
      exp = v10->exp;
      goto LABEL_4;
    }
  }
  return v3 - 1;
}

// 0x18fb990
s32 datGetPlayerMaxHP(sdatUnitWork_t *pParam) {
  s32 vit;
  f32 v3;

  vit = pParam->now->vit;
  if (vit >= 40)
    vit = 40;
  v3 = (f32)((f32)((f32)((f32)((f32)pParam->level * 6.5) * (f32)(90.0 - (f32)pParam->level)) / 100.0) + (f32)((f32)((f32)pParam->level * 6.8) + (f32)((f32)vit * 8.0)))
     + 15.0;
  if (v3 > 999.0)
    v3 = 999.0;
  if (v3 == INFINITY)
    return 0x80000000;
  else
    return (s32)v3;
}

// 0x18fba30
void datGetPlayerOnceLevelUpParam(sdatPlayerUnitWork_t *pUnit, s32 Level) {
  sdatUnitWork_t *para;
  s32 swordno;

  if (Level == 99)
    return;
  para = pUnit->para;
  swordno = pUnit->swordno;
  datCalcNowParam(para, swordno, 0);
}

// 0x18fbad0
s32 datGetPlayerLevelUpParam(sdatPlayerUnitWork_t *pDstUnit, sdatPlayerUnitWork_t *pSrcUnit) {
  sdatUnitWork_t *para;
  s32 v7;
  s8 level;
  s32 exp;
  s32 v11;
  s32 v12;
  s32 v13;
  sdatUnitWork_t *v14;
  s32 v17;
  sdatUnitWork_t *v19;
  s32 swordno;

  para = pSrcUnit->para;
  v7 = 0;
  level = para->level;
  exp = para->exp;
LABEL_6:
  v11 = v7 + level;
  if (v11)
  {
    v12 = v11 + 1;
    if (v12 >= 99)
      v13 = 99;
    else
      v13 = v12;
    if (exp >= PLAYER_EXP(v13))
      goto LABEL_14;
  }
  else
  {
    while (exp >= 0)
    {
LABEL_14:
      v14 = pSrcUnit->para;
      if (v7 + v14->level + 1 > 99)
        break;
      level = v14->level;
      ++v7;
      exp = v14->exp;
      goto LABEL_6;
    }
  }
  ClassCopy(levelUpPlayerUnit, pSrcUnit);
  v17 = pSrcUnit->para->level;
  if (v17 + v7 > v17)
  {
    do
    {
      if (v17 != 99)
      {
        v19 = levelUpPlayerUnit->para;
        swordno = levelUpPlayerUnit->swordno;
        datCalcNowParam(v19, swordno, 0);
      }
      ++v17;
    }
    while (v17 < v7 + pSrcUnit->para->level);
  }
  ClassCopy(pDstUnit, levelUpPlayerUnit);
  return v7;
}

// 0x18fbd10
void datGetPlayerLevelUpUnit(sdatPlayerUnitWork_t *pDstUnit, sdatPlayerUnitWork_t *pSrcUnit) {
  char PlayerLevelUpParam;
  sdatUnitWork_t *para;
  s32 v7;

  PlayerLevelUpParam = datGetPlayerLevelUpParam(pDstUnit, pSrcUnit);
  para = pDstUnit->para;
  v7 = (u8)(para->level + PlayerLevelUpParam);
  para->level += PlayerLevelUpParam;
  if (v7 == 99)
  {
    para->exp = PLAYER_EXP(99);
  }
}

// 0x18fbdc0
s32 datGetDevilExp(s32 DevilID, s32 Level) {
  if (Level >= 99)
    Level = 99;
  if (Level <= sBtlGetDevilData(DevilID, -1)->level)
    return 0;
  else
    return DEVIL_EXP(DevilID, Level);
}

// 0x18fbe70
s32 datGetDevilLevelUpNums(sdatUnitWork_t *pUnit) {
  s8 level;
  s32 v4;
  s32 exp;
  s32 devilid;
  s32 v9;

  level = pUnit->level;
  v4 = 1;
  exp = pUnit->exp;
  devilid = pUnit->devilid;
LABEL_4:
  if (v4 + level >= 99)
    v9 = 99;
  else
    v9 = v4 + level;
  goto LABEL_9;
  while (1)
  {
    if (v4 + level >= 99)
      v9 = 99;
    else
      v9 = v4 + level;
LABEL_9:
    if (v9 <= sBtlGetDevilData(devilid, -1)->level)
    {
      if (exp < 0)
        return v4 - 1;
    }
    else if (exp < DEVIL_EXP(devilid, v9))
    {
      return v4 - 1;
    }
    if (v4 + pUnit->level > 99)
      return v4 - 1;
    level = pUnit->level;
    ++v4;
    exp = pUnit->exp;
    devilid = pUnit->devilid;
    goto LABEL_4;
  }
}

// 0x18fbff0
s32 datGetDevilMaxHP(sdatUnitWork_t *pUnit, sdatPlayerUnitWork_t *_player) {
  s8 level;
  s16 vit;
  sdatParaWork_t *v7;
  sdatUnitWork_t *para;
  f32 v10;

  level = pUnit->level;
  vit = pUnit->now->vit;
  v7 = Allocate(sdatParaWork_t);
  if (player)
  {
    para = player->para;
    goto LABEL_6;
  }
  para = GBWK->player->para;
LABEL_6:
  sBtlGetPlayerTec_ParaUp(para, v7);
  v10 = (f32)((f32)((f32)((f32)((f32)level * 6.5) * (f32)(90.0 - (f32)level)) / 100.0) + (f32)((f32)((f32)level * 6.8) + (f32)((f32)((f32)vit + (f32)v7->vit) * 8.0)))
      + 15.0;
  if (v10 > 999.0)
    v10 = 999.0;
  if (v10 == INFINITY)
    return 0x80000000;
  else
    return (s32)v10;
}

// 0x18fc180
s32 datGetDevilMaxMP(sdatUnitWork_t *pUnit) {
  f32 v2;

  v2 = (f32)((f32)pUnit->level * 3.0) + (f32)((f32)pUnit->now->tec * 12.0);
  if (v2 > 999.0)
    v2 = 999.0;
  if (v2 == INFINITY)
    return 0x80000000;
  else
    return (s32)v2;
}

// 0x18fc1e0
void datGetDevilOnceLevelUpParam(sdatUnitWork_t *pUnit) {
  s64 v3;
  u32 *v4;
  int32x2_t *v5;
  s32 *v6;
  s32 *v7;
  sdatParaWork_t *pitem;
  u32 *v9;
  uint16x4_t v10;
  int8x16_t v11;
  s32 devilid;
  s32 v13;
  s32 v14;
  s32 v15;
  s32 str;
  u32 v17;
  u32 v18;
  s32 v20;
  s32 v21;
  s32 v22;
  s32 v23;
  s32 tec;
  DEVILDATA_WORK *DevilData;
  s64 v26;
  s32 v27;
  s32 v28;
  s32 v29;
  s32 v30;
  s32 vit;
  DEVILDATA_WORK *v32;
  u32 v33;
  s64 v34;
  s32 v35;
  s32 v37;
  s32 v38;
  s32 v39;
  s32 luck;
  DEVILDATA_WORK *v41;
  u32 v42;
  s64 v43;
  s64 v44;
  s64 v45;
  int32x2_t v46;
  int32x2_t v47;
  int32x2_t v48;
  int32x2_t v49;
  int32x2_t v50;
  int32x2_t v51;
  int32x2_t v52;
  s64 v53;
  int32x2_t *v54;
  sdatLvUpDevilParamUp_t *LvUpDevilParamUp;
  s64 v56;
  char *v57;
  signed s32 v58;
  s32 v59;
  s32 v60;
  s32 v61;
  u32 *v62;
  s32 *v63;
  s32 v64;
  u32 *v65;
  s64 v66;
  s32 v67;
  u32 v68;
  u32 v69;
  s64 v71;
  s32 v72;
  s64 v73;
  s64 v74;
  u32 *v75;
  s64 v76;
  s32 v77;
  sdatParaWork_t *backup;
  s32 v79;
  char *v80;
  s64 v81;
  u32 *v82;
  sdatParaWork_t *v83;
  s32 v84;
  sdatParaWork_t *v85;
  s32 v86;
  sdatParaWork_t *v87;
  s32 v88;
  float32x2x2_t v89;

  v3 = NewSpecific(s32, 4u);
  v4 = NewSpecific(s32, 4u);
  v5 = NewSpecific(s32, 4u);
  v6 = NewSpecific(s32, 4u);
  if (pUnit->level != 99)
  {
    v7 = &v6[0];
    pitem = pUnit->pitem;
    v9 = v6;
    v10.n64_u16[0] = (u8)*(u64 *)&pitem->str;
    v10.n64_u16[1] = (u8)BYTE2(*(u64 *)&pitem->str);
    v10.n64_u16[2] = (u8)BYTE4(*(u64 *)&pitem->str);
    v10.n64_u16[3] = (u8)BYTE6(*(u64 *)&pitem->str);
    v11 = vshrq_n_s32(vshlq_n_s32(vaddw_u16(vaddw_u16(vaddl_u16(v10, *(uint16x4_t *)&pUnit->backup->str), *(uint16x4_t *)&pUnit->huuma->str), *(uint16x4_t *)&pUnit->surpriseParam->str), 0x10u), 0x10u);
    v89.val[0].n64_u64[0] = v11.n128_u64[0];
    v89.val[1].n64_u64[0] = vextq_s8(v11, v11, 8u).n128_u64[0];
    vst2_f32(&v6[0], v89);
    devilid = pUnit->devilid;
    v13 = LOBYTE(pUnit->pitem->str) + sBtlGetDevilData(devilid, -1)->str;
    if (v13 >= 21)
      v14 = 40;
    else
      v14 = 2 * v13;
    if (*v7 >= v14)
    {
      v18 = 0;
      v20 = pUnit->devilid;
      goto LABEL_17;
    }
    else
    {
      v15 = pUnit->devilid;
      str = pUnit->backup->str;
      v17 = str - sBtlGetDevilData(v15, -1)->str;
      v18 = 1;
      v5[4].n64_u32[0] = v17;
      *(u32 *)(v3 + 32) = 0;
      v20 = pUnit->devilid;
LABEL_17:
      v21 = LOBYTE(pUnit->pitem->tec) + sBtlGetDevilData(v20, -1)->tec;
      if (v21 >= 21)
        v22 = 40;
      else
        v22 = 2 * v21;
      if (v9[9] < v22)
      {
        v23 = pUnit->devilid;
        tec = pUnit->backup->tec;
        DevilData = sBtlGetDevilData(v23, -1);
        v26 = v18++;
        v5[4].n64_u32[v26] = tec - DevilData->tec;
        *(u32 *)(v3 + v26 * 4 + 32) = 1;
      }
      v27 = pUnit->devilid;
      v28 = LOBYTE(pUnit->pitem->vit) + sBtlGetDevilData(v27, -1)->vit;
      if (v28 >= 21)
        v29 = 40;
      else
        v29 = 2 * v28;
      if (v9[10] < v29)
      {
        v30 = pUnit->devilid;
        vit = pUnit->backup->vit;
        v32 = sBtlGetDevilData(v30, -1);
        v33 = v18++;
        v34 = v33;
        v5[4].n64_u32[v34] = vit - v32->vit;
        *(u32 *)(v3 + v34 * 4 + 32) = 2;
      }
      v35 = pUnit->devilid;
      v37 = LOBYTE(pUnit->pitem->luck) + sBtlGetDevilData(v35, -1)->luck;
      if (v37 >= 21)
        v38 = 40;
      else
        v38 = 2 * v37;
      if (v9[11] >= v38)
      {
        if (!v18)
          return;
      }
      else
      {
        v39 = pUnit->devilid;
        luck = pUnit->backup->luck;
        v41 = sBtlGetDevilData(v39, -1);
        v42 = v18++;
        v43 = v42;
        v5[4].n64_u32[v43] = luck - v41->luck;
        *(u32 *)(v3 + v43 * 4 + 32) = 3;
      }
      v44 = v18;
      if (v18 < 8)
      {
        v45 = 0;
        goto LABEL_88;
      }
      v46.n64_u64[0] = vcltz_s32(v5[4]).n64_u64[0];
      if ((v46.n64_u8[0] & 1) != 0)
      {
        v5[4].n64_u32[0] = 0;
        v47.n64_u64[0] = v5[5].n64_u64[0];
        if ((v46.n64_u8[4] & 1) == 0)
        {
LABEL_47:
          v48.n64_u64[0] = vcltz_s32(v47).n64_u64[0];
          if ((v48.n64_u8[0] & 1) == 0)
            goto LABEL_48;
          goto LABEL_57;
        }
      }
      else
      {
        v47.n64_u64[0] = v5[5].n64_u64[0];
        if ((v46.n64_u8[4] & 1) == 0)
          goto LABEL_47;
      }
      v5[4].n64_u32[1] = 0;
      v48.n64_u64[0] = vcltz_s32(v47).n64_u64[0];
      if ((v48.n64_u8[0] & 1) == 0)
      {
LABEL_48:
        v49.n64_u64[0] = v5[6].n64_u64[0];
        if ((v48.n64_u8[4] & 1) == 0)
          goto LABEL_49;
        goto LABEL_58;
      }
LABEL_57:
      v5[5].n64_u32[0] = 0;
      v49.n64_u64[0] = v5[6].n64_u64[0];
      if ((v48.n64_u8[4] & 1) == 0)
      {
LABEL_49:
        v50.n64_u64[0] = vcltz_s32(v49).n64_u64[0];
        if ((v50.n64_u8[0] & 1) == 0)
          goto LABEL_50;
        goto LABEL_59;
      }
LABEL_58:
      v5[5].n64_u32[1] = 0;
      v50.n64_u64[0] = vcltz_s32(v49).n64_u64[0];
      if ((v50.n64_u8[0] & 1) == 0)
      {
LABEL_50:
        v51.n64_u64[0] = v5[7].n64_u64[0];
        if ((v50.n64_u8[4] & 1) == 0)
          goto LABEL_51;
        goto LABEL_60;
      }
LABEL_59:
      v5[6].n64_u32[0] = 0;
      v51.n64_u64[0] = v5[7].n64_u64[0];
      if ((v50.n64_u8[4] & 1) == 0)
      {
LABEL_51:
        v52.n64_u64[0] = vcltz_s32(v51).n64_u64[0];
        if ((v52.n64_u8[0] & 1) == 0)
          goto LABEL_52;
        goto LABEL_61;
      }
LABEL_60:
      v5[6].n64_u32[1] = 0;
      v52.n64_u64[0] = vcltz_s32(v51).n64_u64[0];
      if ((v52.n64_u8[0] & 1) == 0)
      {
LABEL_52:
        v45 = v18 & 8;
        if ((v52.n64_u8[4] & 1) == 0)
          goto LABEL_53;
        goto LABEL_62;
      }
LABEL_61:
      v5[7].n64_u32[0] = 0;
      v45 = v18 & 8;
      if ((v52.n64_u8[4] & 1) == 0)
      {
LABEL_53:
        if (v45 != v18)
        {
LABEL_88:
          v80 = (char *)v5 + 4 * v45;
          v81 = v18 - v45;
          v82 = v80 + 32;
          do
          {
            if ((*v82 & 0x80000000) != 0)
              *v82 = 0;
            ++v82;
            --v81;
          }
          while (v81);
        }
LABEL_63:
        v53 = 0;
        v54 = v5 + 4;
        do
        {
          v59 = pUnit->devilid;
          LvUpDevilParamUp = sdatGetLvUpDevilParamUp(v59);
          v56 = v53;
          v57 = (char *)LvUpDevilParamUp->Param + v53;
          v58 = v54->n64_i32[v53++];
          v4[v56 + 8] = v58 / (u8)v57[32];
        }
        while (v44 != v53);
        v60 = v4[8];
        if ((s32)v44 >= 2)
        {
          if (v4[9] < v60)
            v60 = v4[9];
          if ((u32)v44 != 2)
          {
            if (v4[10] < v60)
              v60 = v4[10];
            if ((u32)v44 != 3 && v4[11] < v60)
              v60 = v4[11];
          }
        }
        v61 = 0;
        v62 = (v3 + 32);
        v63 = v4 + 8;
        do
        {
          v64 = *v63++;
          if (v64 == v60)
          {
            v65 = &v4[v61++];
            v65[8] = *v62;
          }
          ++v62;
          --v44;
        }
        while (v44);
        v66 = v61;
        v67 = 16;
        do
        {
          v68 = RAND(0);
          v69 = RAND(0);
          v71 = v68 % v66;
          v72 = v4[6];
          if ((s32)v71 < v72)
          {
            v73 = v69 % v66;
            if ((s32)v73 < v72)
            {
              v74 = v71;
              v75 = v4 + 8;
              v76 = v73;
              v77 = v4[v74 + 8];
              v75[v74] = v4[v76 + 8];
              v75[v76] = v77;
            }
          }
          --v67;
        }
        while (v67);
        switch (v4[8])
        {
          case 0:
            backup = pUnit->backup;
            v79 = backup->str;
            if (pUnit->pbtl->str + 40 > v79)
              backup->str = v79 + 1;
            break;
          case 1:
            v83 = pUnit->backup;
            v84 = v83->tec;
            if (pUnit->pbtl->tec + 40 > v84)
              v83->tec = v84 + 1;
            break;
          case 2:
            v85 = pUnit->backup;
            v86 = v85->vit;
            if (pUnit->pbtl->vit + 40 > v86)
              v85->vit = v86 + 1;
            break;
          case 3:
            v87 = pUnit->backup;
            v88 = v87->luck;
            if (pUnit->pbtl->luck + 40 > v88)
              v87->luck = v88 + 1;
            break;
          default:
            break;
        }
        datCalcNowParam(pUnit, 0, 0);
        return;
      }
LABEL_62:
      v5[7].n64_u32[1] = 0;
      if (v45 != v18)
        goto LABEL_88;
      goto LABEL_63;
    }
    goto LABEL_17;
  }
}

// 0x18fc930
s32 datGetDevilLevelUpParam(sdatUnitWork_t *pDstUnit, sdatUnitWork_t *pSrcUnit) {
  s32 DevilLevelUpNums;
  sdatUnitWork_t *v6;
  s32 v11;

  DevilLevelUpNums = datGetDevilLevelUpNums(pSrcUnit);
  v6 = Allocate(sdatUnitWork_t);
  _ctor(v6);
  ClassCopy(v6, pSrcUnit);
  if (DevilLevelUpNums >= 1)
  {
    v11 = DevilLevelUpNums;
    do
    {
      datGetDevilOnceLevelUpParam(v6);
      --v11;
    }
    while (v11);
  }
  ClassCopy(pDstUnit, v6);
  return DevilLevelUpNums;
}

// 0x18fca20
void datGetDevilLevelUpUnit(sdatUnitWork_t *pDstUnit, sdatUnitWork_t *pSrcUnit) {
  s8 v5;
  s32 devilid;
  s32 v8;

  v5 = pDstUnit->level + datGetDevilLevelUpParam(pDstUnit, pSrcUnit);
  pDstUnit->level = v5;
  if (v5 == 99)
  {
    devilid = pDstUnit->devilid;
    if (sBtlGetDevilData(devilid, -1)->level > 0x62u)
      v8 = 0;
    else
      v8 = DEVIL_EXP(devilid, 99);
    pDstUnit->exp = v8;
    return;
  }
}

// 0x18fcb50
void datCalcDevilMaxParCheck(sdatUnitWork_t *pUnit) {
  s32 devilid;
  DEVILDATA_WORK *DevilData;
  int16x4_t *now;
  sdatParaWork_t *pitem;
  int16x4_t v9;
  int16x4_t v10;
  s32 v11;
  u16 v12;
  s32 v13;
  u16 v14;
  s32 v15;
  u16 v16;
  u32 luck;
  s32 v18;
  u16 v19;
  u16 v21;

  devilid = pUnit->devilid;
  DevilData = sBtlGetDevilData(devilid, -1);
  now = pUnit->now;
  pitem = pUnit->pitem;
  v9.n64_u16[0] = (u8)*(u64 *)&pitem->str;
  v9.n64_u16[1] = (u8)BYTE2(*(u64 *)&pitem->str);
  v9.n64_u16[2] = (u8)BYTE4(*(u64 *)&pitem->str);
  v9.n64_u16[3] = (u8)BYTE6(*(u64 *)&pitem->str);
  v10.n64_u64[0] = vadd_s16(vadd_s16(v9, vadd_s16(*(int16x4_t *)&pUnit->backup->str, *(int16x4_t *)&pUnit->pbtl->str)), vadd_s16(*(int16x4_t *)&pUnit->huuma->str, *(int16x4_t *)&pUnit->surpriseParam->str)).n64_u64[0];
  now[4].n64_u64[0] = v10.n64_u64[0];
  v11 = 2 * (LOBYTE(pitem->str) + DevilData->str);
  v12 = v10.n64_u16[0];
  if (v11 < v10.n64_i16[0])
  {
    v12 = 2 * (LOBYTE(pitem->str) + DevilData->str);
    now[4].n64_u16[0] = v11;
  }
  v13 = 2 * (LOBYTE(pitem->vit) + DevilData->vit);
  v14 = v10.n64_u16[1];
  if (v13 < v10.n64_i16[1])
  {
    v14 = 2 * (LOBYTE(pitem->vit) + DevilData->vit);
    now[4].n64_u16[1] = v13;
  }
  v15 = 2 * (LOBYTE(pitem->tec) + DevilData->tec);
  v16 = v10.n64_u16[2];
  if (v15 < v10.n64_i16[2])
  {
    v16 = 2 * (LOBYTE(pitem->tec) + DevilData->tec);
    now[4].n64_u16[2] = v15;
  }
  luck = (u16)pitem->luck;
  v18 = 2 * (DevilData->luck + (u8)luck);
  v19 = v10.n64_u16[3];
  if (v18 < v10.n64_i16[3])
  {
    now[4].n64_u16[3] = v18;
    v19 = v18;
    luck = (u16)pitem->luck;
  }
  now[4].n64_u16[0] = HIBYTE(pitem->str) + v12;
  v21 = HIBYTE(pitem->vit) + v14;
  now[4].n64_u16[2] = HIBYTE(pitem->tec) + v16;
  now[4].n64_u16[1] = v21;
  now[4].n64_u16[3] = v19 + (luck >> 8);
  LimitRange((s32 *)&now[2] + 1, 0, 999);
  LimitRange(&pUnit->now->maxmp, 0, 999);
  LimitRange_2(&pUnit->now->str, 0, 40);
  LimitRange_2(&pUnit->now->vit, 0, 40);
  LimitRange_2(&pUnit->now->tec, 0, 40);
  LimitRange_2(&pUnit->now->luck, 0, 40);
}

// 0x18fcde0
void datDvlParaUpdate(sdatPlayerUnitWork_t *player) {
  sdatUnitWork_t *stock_id;
  il2cpp_array_size_t max_length;
  s64 v7;
  sdatUnitWork_t *v8;

  stock_id = GBWK->player->stock_id;
  max_length = stock_id->max_length;
  if ((s32)max_length >= 1)
  {
    v7 = 0;
    do
    {
      v8 = stock_id[v7];
      if ((v8->flag & 1) != 0)
      {
        datCalcNowParam(v8, 0, player);
        max_length = stock_id->max_length;
      }
      ++v7;
    }
    while (v7 < (s32)max_length);
  }
}

// 0x18f9690
void datCalcNowParam(sdatUnitWork_t *pUnit, s32 SwordID, sdatPlayerUnitWork_t *_player) {
  sdatParaWork_t *backup;
  s32 str;
  s32 tec;
  s32 vit;
  s32 luck;
  u32 flag;
  sdatParaWork_t *v15;
  sdatParaWork_t *v16;
  sdatParaWork_t *v17;
  sdatParaWork_t *v18;
  sdatParaWork_t *v19;
  s16 v20;
  s16 v22;
  s32 v23;
  s16 v24;
  u32 v25;
  s16 v26;
  s16 v27;
  s16 v28;
  sdatParaWork_t *pitem;
  sdatParaWork_t *pbtl;
  sdatParaWork_t *huuma;
  sdatParaWork_t *surpriseParam;
  sdatParaWork_t *now;
  u32 v34;
  s16 v35;
  s16 v36;
  u32 v37;
  s16 v38;
  s32 v39;
  s32 v40;
  s32 v41;
  sdatParaWork_t *v42;
  s32 v43;
  sdatParaWork_t *v45;
  sdatParaWork_t *v46;
  s32 level;
  f32 v48;
  s32 v49;
  f32 v50;
  s32 v51;
  s32 maxhp;
  sdatParaWork_t *v53;
  s32 DevilMaxHP;
  sdatParaWork_t *v55;
  f32 v57;
  s32 v58;
  sdatParaWork_t *v59;
  sdatParaWork_t *v60;
  sdatParaWork_t *v61;
  sdatParaWork_t *v62;
  sdatParaWork_t *v63;
  s32 v64;
  sdatParaWork_t *v65;
  s32 v66;
  s32 v67;

  sBtlCheckAutoSkill(pUnit, 0);
  sBtlSetAutoSkill_GB(pUnit);
  backup = pUnit->backup;
  str = backup->str;
  if (str >= 256)
  {
    LOWORD(str) = 255;
    backup->str = 255;
    tec = backup->tec;
    if (tec < 256)
    {
LABEL_7:
      vit = backup->vit;
      if (vit < 256)
        goto LABEL_8;
      goto LABEL_15;
    }
  }
  else
  {
    tec = backup->tec;
    if (tec < 256)
      goto LABEL_7;
  }
  LOWORD(tec) = 255;
  backup->tec = 255;
  vit = backup->vit;
  if (vit < 256)
  {
LABEL_8:
    luck = backup->luck;
    if (luck < 256)
      goto LABEL_9;
    goto LABEL_16;
  }
LABEL_15:
  LOWORD(vit) = 255;
  backup->vit = 255;
  luck = backup->luck;
  if (luck < 256)
  {
LABEL_9:
    flag = pUnit->flag;
    if ((flag & 2) == 0)
      goto LABEL_10;
LABEL_17:
    pitem = pUnit->pitem;
    pbtl = pUnit->pbtl;
    huuma = pUnit->huuma;
    surpriseParam = pUnit->surpriseParam;
    now = pUnit->now;
    v34 = (u16)pitem->vit;
    v35 = huuma->vit;
    v36 = huuma->tec;
    now->str = pbtl->str
                    + str
                    + huuma->str
                    + surpriseParam->str
                    + HIBYTE(pitem->str)
                    + (u8)pitem->str;
    v37 = (u16)pitem->tec;
    v38 = pbtl->vit + vit + v35 + surpriseParam->vit + (v34 >> 8) + (u8)v34;
    LOWORD(v34) = surpriseParam->tec;
    now->vit = v38;
    v39 = (u16)huuma->luck;
    now->tec = pbtl->tec + tec + v36 + v34 + (v37 >> 8) + (u8)v37;
    v40 = (u16)pbtl->luck + luck + v39 + (u16)surpriseParam->luck;
    v41 = v40 + HIBYTE(pitem->luck) + (u8)pitem->luck;
    now->luck = v40 + HIBYTE(pitem->luck) + (u8)pitem->luck;
    now->luck = sBtlGetCorrectionParamLuck() + v41;
    if ((pUnit->flag & 4) != 0)
      goto LABEL_36;
    goto LABEL_20;
  }
LABEL_16:
  luck = 255;
  backup->luck = 255;
  flag = pUnit->flag;
  if ((flag & 2) != 0)
    goto LABEL_17;
LABEL_10:
  if ((flag & 4) == 0)
  {
    v15 = pUnit->pitem;
    v16 = pUnit->pbtl;
    v17 = pUnit->huuma;
    v18 = pUnit->surpriseParam;
    v19 = pUnit->now;
    v20 = v16->vit + vit;
    v21 = (u16)v18->str;
    v22 = v18->vit;
    v23 = HIBYTE(v15->vit) + (u8)v15->vit;
    v24 = v17->vit;
    v19->str = v16->str
                    + str
                    + v17->str
                    + (u16)v21
                    + HIBYTE(v15->str)
                    + (u8)v15->str;
    v25 = (u16)v15->tec;
    v26 = v20 + v24 + v22;
    v27 = v18->tec;
    v19->vit = v26 + v23;
    v28 = v18->luck;
    v19->tec = v16->tec + tec + v17->tec + v27 + (v25 >> 8) + (u8)v25;
    v19->luck = v16->luck
                     + luck
                     + v17->luck
                     + v28
                     + HIBYTE(v15->luck)
                     + (u8)v15->luck;
    if ((pUnit->flag & 4) != 0)
      goto LABEL_36;
LABEL_20:
    v42 = pUnit->now;
    if (v42->str >= 41)
    {
      v42->str = 40;
      if (v42->tec < 41)
      {
LABEL_22:
        v43 = v42->vit;
        if (v43 < 41)
          goto LABEL_23;
        goto LABEL_62;
      }
    }
    else if (v42->tec < 41)
    {
      goto LABEL_22;
    }
    v42->tec = 40;
    v43 = v42->vit;
    if (v43 < 41)
    {
LABEL_23:
      if (v42->luck < 41)
        goto LABEL_24;
      goto LABEL_63;
    }
LABEL_62:
    LOWORD(v43) = 40;
    v42->vit = 40;
    if (v42->luck < 41)
    {
LABEL_24:
      v45 = pUnit->backup;
      v46 = v45;
LABEL_25:
      level = pUnit->level;
      v46->maxmp = 0;
      v48 = level;
      v49 = (s16)v43;
      if ((s16)v43 >= 40)
        v49 = 40;
      v50 = (f32)((f32)((f32)((f32)(v48 * 6.5) * (f32)(90.0 - v48)) / 100.0) + (f32)((f32)(v48 * 6.8) + (f32)((f32)v49 * 8.0)))
          + 15.0;
      if (v50 > 999.0)
        v50 = 999.0;
      v51 = v50;
      if (v50 == INFINITY)
        v51 = 0x80000000;
      v45->maxhp = v51;
      maxhp = v46->maxhp;
      v46->maxhp = tbl[SwordID]->m_paraBns->hp
                        + maxhp;
      goto LABEL_45;
    }
LABEL_63:
    v42->luck = 40;
    v45 = pUnit->backup;
    v46 = v45;
    goto LABEL_25;
  }
  datCalcDevilMaxParCheck(pUnit);
  if ((pUnit->flag & 4) != 0)
    goto LABEL_36;
  goto LABEL_20;
LABEL_36:
  v53 = pUnit->backup;
  DevilMaxHP = datGetDevilMaxHP(pUnit, player);
  v55 = pUnit->now;
  v53->maxhp = DevilMaxHP;
  v57 = (f32)((f32)pUnit->level * 3.0) + (f32)((f32)v55->tec * 12.0);
  if (v57 > 999.0)
    v57 = 999.0;
  v58 = v57;
  if (v57 == INFINITY)
    v58 = 0x80000000;
  pUnit->backup->maxmp = v58;
  sBtlCheckAutoSkill(pUnit, 0);
  sBtlSetAutoSkill_GB(pUnit);
LABEL_45:
  v59 = pUnit->now;
  v60 = pUnit->backup;
  v61 = pUnit->surpriseParam;
  v62 = pUnit->pitem;
  v63 = pUnit->pbtl;
  v64 = v62->maxhp + v60->maxhp;
  v65 = pUnit->huuma;
  LODWORD(v60) = v62->maxmp + v60->maxmp + v63->maxmp + v65->maxmp;
  v66 = v64 + v63->maxhp + v65->maxhp + pUnit->accident->maxhp + v61->maxhp;
  v59->maxhp = v66;
  v67 = (u32)v60 + v61->maxmp;
  v59->maxmp = v67;
  if (v66 >= 1000)
  {
    v66 = 999;
    v59->maxhp = 999;
    if (v67 < 1000)
    {
LABEL_47:
      if (v59->hp <= v66)
        goto LABEL_48;
      goto LABEL_55;
    }
  }
  else if (v67 < 1000)
  {
    goto LABEL_47;
  }
  v67 = 999;
  v59->maxmp = 999;
  if (v59->hp <= v66)
  {
LABEL_48:
    if (v59->mp <= v67)
      goto LABEL_49;
    goto LABEL_56;
  }
LABEL_55:
  v59->hp = v66;
  if (v59->mp <= v67)
  {
LABEL_49:
    goto LABEL_50;
  }
LABEL_56:
  v59->mp = v67;
LABEL_50:
  datCalcMagMaxPlayerUnit(GBWK->player);
}

// 0x18fcf50
s32 datGetSword4Param(s32 SwordID, s32 Type) {
  switch (Type)
  {
    case 2:
      return tbl[SwordID]->m_paraBns->vit;
    case 1:
      return tbl[SwordID]->m_paraBns->tec;
    case 0:
      return tbl[SwordID]->m_paraBns->str;
  }
  return tbl[SwordID]->m_paraBns->luck;
}

// 0x18fd190
s32 datGetSwordParamHP(s32 SwordID) {
  return tbl[SwordID]->m_paraBns->hp;
}

// 0x18fd250
s32 datGetSwordAisyoEx(s32 SwordID) {
  return 0;
}

// 0x18fd260
s32 datGetSwordAisyo(void) {
  return 0;
}

// 0x18fd2d0
u32 datCheckStrongSwordDevil(s32 DevilID) {
  u32 result;

  result = 2344;
  if (DevilID > 33)
  {
    switch (DevilID)
    {
      case '"':
        return result;
      case '?':
        return 2346;
      case 'D':
        return 2345;
    }
    return 0;
  }
  if (DevilID != 7)
  {
    if (DevilID == 25)
      return 2348;
    return 0;
  }
  return result;
}

// 0x18fd330
s32 datCheckStrongSwordAttack(s32 SwordID) {
  s32 *v3;
  s64 v4;
  s64 v5;
  s32 v6;
  s32 v7;
  s32 v8;

  v3 = NewSpecific(s32, 5u);
  InitializeArray_55364416(v3, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__3861726F356D5E4D65EDE32BB2E76E8389FBC9650DDB93F6F671B3B94023ADDA, 0);
  if (*(s32 *)((char *)v3 + 24) < 1)
    return 50;
  v4 = 0;
  v5 = &v3[0];
  v6 = 50;
  while (1)
  {
    v8 = *(u32 *)(v5 + 4 * v4);
    if (v8 <= 33)
      goto LABEL_15;
LABEL_10:
    v7 = 2344;
    if (v8 != 34)
    {
      if (v8 == 63)
      {
        v7 = 2346;
      }
      else
      {
        if (v8 != 68)
          goto LABEL_18;
        v7 = 2345;
      }
    }
LABEL_6:
    if (!evtBitCheck(v7))
      return 0;
LABEL_7:
    if (*(s32 *)((char *)v3 + 24) <= ++v4)
      return v6;
  }
  if (v8 > 33)
    goto LABEL_10;
LABEL_15:
  v7 = 2344;
  if (v8 == 7)
    goto LABEL_6;
  if (v8 == 25)
  {
    v7 = 2348;
    goto LABEL_6;
  }
LABEL_18:
  if (*(u32 *)(v5 + 4 * v4) == SwordID)
    goto LABEL_7;
  return 0;
}

// 0x18fd4b0
s32 datSetPlayerUnitSword(sdatPlayerUnitWork_t *pUnit, s32 SwordID, sdatUnitWork_t *pDevil) {
  s64 swordno;
  sdatParaWork_t *backup;
  s16 str;
  sdatParaWork_t *v11;
  s16 tec;
  sdatParaWork_t *v14;
  s16 vit;
  sdatParaWork_t *v17;
  s16 luck;
  sdatParaWork_t *v20;
  s16 v21;
  sdatParaWork_t *v23;
  s16 v24;
  s64 v26;
  sdatParaWork_t *v27;
  s16 v28;
  sdatParaWork_t *v30;
  s16 v31;
  sdatUnitWork_t *para;
  s32 m_atk;

  swordno = pUnit->swordno;
  if (pUnit->swordno)
  {
    backup = pUnit->para->backup;
    str = backup->str;
    backup->str = str
                       - tbl[swordno]->m_paraBns->str;
    v11 = pUnit->para->backup;
    tec = v11->tec;
    v11->tec = tec
                    - tbl[swordno]->m_paraBns->tec;
    v14 = pUnit->para->backup;
    vit = v14->vit;
    v14->vit = vit
                    - tbl[swordno]->m_paraBns->vit;
    v17 = pUnit->para->backup;
    luck = v17->luck;
    v17->luck = luck
                     - tbl[swordno]->m_paraBns->luck;
    goto LABEL_18;
  }
LABEL_18:
  v20 = pUnit->para->backup;
  v21 = v20->str;
  v20->str = tbl[SwordID]->m_paraBns->str
                  + v21;
  v23 = pUnit->para->backup;
  v24 = v23->tec;
  v26 = SwordID;
  v23->tec = tbl[v26]->m_paraBns->tec + v24;
  v27 = pUnit->para->backup;
  v28 = v27->vit;
  v27->vit = tbl[v26]->m_paraBns->vit + v28;
  v30 = pUnit->para->backup;
  v31 = v30->luck;
  para = pUnit->para;
  v30->luck = tbl[v26]->m_paraBns->luck + v31;
  datCalcNowParam(para, SwordID, 0);
  datDvlParaUpdate(0);
  if (!SwordID)
  {
    pUnit->swordatk = 10;
    pUnit->swordno = 0;
    goto LABEL_38;
  }
  m_atk = tbl[v26]->m_atk;
  pUnit->swordatk = m_atk;
  pUnit->swordatk = datCheckStrongSwordAttack(SwordID) + m_atk;
  pUnit->swordno = SwordID;
LABEL_38:
  datCalcMagMaxPlayerUnit(pUnit);
  return swordno;
}

// 0x18f63e0
s32 datSetPlayerSword(s32 SwordID, sdatUnitWork_t *pDevil) {
  return datSetPlayerUnitSword(GBWK->player, SwordID);
}

// 0x18fde90
bool datCheckDying(sdatUnitWork_t *pUnit) {
  return 100 * pUnit->now->hp / pUnit->now->maxhp < 26;
}

// 0x18fdeb0
void datAddMoney(s32 add) {
  sdatPlayerUnitWork_t *player;
  s32 gold;
  u32 v5;

  player = GBWK->player;
  gold = player->gold;
  v5 = (gold + add) & ~((gold + add) >> 31);
  if (v5 >= 0x98967F)
    v5 = 9999999;
  player->gold = v5;
}

// 0x18fdf70
bool datCheckMoney(s32 money) {
  return GBWK->player->gold >= money;
}

// 0x18fdff0
bool datCheckEventItem(s32 id) {
  if ((byte_5755FED & 1) != 0)
  {
    if ((u32)(id - 768) < 0xFFFFFE90)
      return 0;
  }
  else
  {
    if ((u32)(id - 768) < 0xFFFFFE90)
      return 0;
  }
  return (tbldata[id]->type & 0x40) != 0;
}

// 0x18fe0d0
s32 datCalcGetItemNum(s32 id) {
  if ((u32)(id - 768) < 0xFFFFFE90)
  {
    if (id > 767)
      return -1;
    goto LABEL_13;
  }
  if ((tbldata[id]->type & 0x40) != 0)
    return evtBitCheck(id + 2160);
LABEL_13:
  return GBWK->player->item[id];
}

// 0x18f5fb0
void datAddItem(s32 id, s32 num) {
  s32 v8;
  s32 v9;
  s64 v12;
  u32 v14;
  s64 v15;
  s64 v17;

  if ((u32)(id - 768) < 0xFFFFFE90)
    goto LABEL_5;
  if ((tbldata[id]->type & 0x40) == 0)
  {
LABEL_13:
    v8 = GBWK->player->item[id] + num;
    v9 = v8 & ~(v8 >> 31);
    if (v9 <= datGetItemMaxNum(id))
    {
      v12 = id;
      goto LABEL_18;
    }
    LOWORD(v9) = datGetItemMaxNum(id);
    v12 = id;
LABEL_18:
    GBWK->player->item[v12] = v9;
    if (id == 39)
    {
      if (GBWK->player->item[39] >= 8)
      {
        fldDestBitOn(9, 13);
        goto LABEL_36;
      }
      goto LABEL_34;
    }
LABEL_34:
LABEL_36:
    UpdateGetList(GBWK->sortSave, id, num, 0);
    return;
  }
  v14 = id + 2160;
  if (num < 0)
  {
    v17 = (s64)GBWK->EventBit + 4 * (v14 >> 5);
    *(u32 *)(v17 + 32) &= ~(1 << v14);
    goto LABEL_36;
  }
  if ((u32)(id - 458) < 0xFFFFFFC6)
  {
LABEL_33:
    v15 = (s64)GBWK->EventBit + 4 * (v14 >> 5);
    *(u32 *)(v15 + 32) |= 1 << v14;
    goto LABEL_34;
  }
  evtBitKityouItemAdd(v14);
  goto LABEL_33;
LABEL_5:
  if (id <= 767)
    goto LABEL_13;
}

// 0x18fe390
bool datCheckItem(s32 id, s32 num) {
  if ((u32)(id - 768) < 0xFFFFFE90)
  {
    if (id > 767)
      return 0;
    goto LABEL_13;
  }
  if ((tbldata[id]->type & 0x40) != 0)
    return evtBitCheck(id + 2160);
LABEL_13:
  return GBWK->player->item[id] >= num;
}

// 0x18fe520
s32 datGetItemNum(s32 id) {
  s32 ItemNum;

  ItemNum = datCalcGetItemNum(id);
  return ItemNum & ~(ItemNum >> 31);
}

// 0x18fe250
s32 datGetItemMaxNum(s32 id) {
  SBTLITEM_TBL *v4;
  s32 v6;

  v4 = tbldata[id];
  if ((v4->type & 4) == 0)
    return v4->max_num;
  v6 = id + 16;
  if (v6 < 0)
    return 0;
  if (GBWK->player->item[v6] >= 1)
    return 99;
  else
    return 24;
}

// 0x18fe590
void datAddMag(s32 add) {
  sdatPlayerUnitWork_t *player;
  s32 v6;
  s32 maxmag;

  player = GBWK->player;
  v6 = (player->mag + add) & ~((player->mag + add) >> 31);
  maxmag = player->maxmag;
  if (v6 > maxmag)
    v6 = maxmag;
  GBWK->player->mag = v6;
}

// 0x18fe6a0
bool datCheckMag(s32 num) {
  return GBWK->player->mag >= num;
}

// 0x18fe720
void datPartyRecovery(void) {
  s64 v3;
  sdatPlayerUnitWork_t *player;
  sdatUnitWork_t *para;
  sdatParaWork_t *now;
  s64 v7;
  s64 v8;
  u32 *v9;
  s32 v10;

  v3 = 0;
  player = GBWK->player;
  para = player->para;
  now = para->now;
  para->badstatus = 0;
  now->hp = now->maxhp;
  while (v3 < datGetStockDevilNums(0))
  {
    v7 = (s64)player->stock_id + 8 * v3;
    ++v3;
    v8 = *(u64 *)(v7 + 32);
    v9 = *(u32 **)(v8 + 40);
    *(u32 *)(v8 + 144) = 0;
    v10 = v9[7];
    v9[4] = v9[5];
    v9[6] = v10;
  }
}

// 0x18fe800
void datPartyDevilRecovery(s32 devilid) {
  s64 v4;
  sdatPlayerUnitWork_t *player;
  sdatUnitWork_t *v6;
  sdatParaWork_t *now;

  v4 = 0;
  player = GBWK->player;
  while (1)
  {
    if (v4 >= datGetStockDevilNums(0))
      break;
    v6 = player->stock_id[v4];
    if (v6->devilid == devilid)
    {
      now = v6->now;
      v6->badstatus = 0;
      now->hp = now->maxhp;
      now->mp = now->maxmp;
    }
    ++v4;
  }
}

// 0x18fe8d0
s32 datGetTotalCyuusei(sdatUnitWork_t *pUnit) {
  return (u16)pUnit->chuusei | ((u16)pUnit->chuusei_high << 16);
}

// 0x18fe8e0
void datAddTotalCyuusei(sdatUnitWork_t *pUnit, s32 Val) {
  s32 v5;
  u64 v6;
  void *achievementTbl_k__BackingField;
  Project_DefineAchievementID_string__c *klass;
  s64 v11;
  Project_DefineAchievementID_string__c **p_offset;
  s64 v13;
  char *v14;

  v5 = (u16)pUnit->chuusei + Val + ((u16)pUnit->chuusei_high << 16);
  if (v5 >= 99999)
    v5 = 99999;
  HIDWORD(v6) = v5;
  LODWORD(v6) = v5;
  *(u32 *)&pUnit->chuusei_high = v6 >> 16;
  if (evtBitCheck(2493))
  {
    achievementTbl_k__BackingField = _achievementTbl_k__BackingField;
    klass = achievementTbl_k__BackingField->klass;
    v11 = *(u16 *)&achievementTbl_k__BackingField->klass->_2.rank;
    if (!*(u16 *)&achievementTbl_k__BackingField->klass->_2.rank)
      goto LABEL_18;
    goto LABEL_15;
    if (!*(u16 *)&achievementTbl_k__BackingField->klass->_2.rank)
    {
LABEL_18:
      v13 = sub_4227F4(achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 0x27u);
LABEL_20:
      v14 = (*v13)(achievementTbl_k__BackingField, *(u64 *)(v13 + 8));
      Unlock_2(v14);
      return;
    }
LABEL_15:
    p_offset = &klass->_1.interfaceOffsets->offset;
    while (*(p_offset - 1) != Project_DefineAchievementID_string_)
    {
      p_offset += 2;
      if (!--v11)
        goto LABEL_18;
    }
    v13 = (&klass[1]._1.interopData + 2 * *(u32 *)p_offset);
    goto LABEL_20;
  }
}

// 0x18fea80
void datPartyDamageMap(s32 mode) {
  sdatUnitWork_t *para;
  u32 BadStatus;
  sdatParaWork_t *now;
  s32 hp;
  s32 v11;
  s32 v12;
  s32 v13;
  s32 v14;
  s64 v15;
  s32 v16;
  s32 v17;
  sdatPlayerUnitWork_t *player;
  sdatUnitWork_t *v20;
  u32 v24;
  s32 v25;
  u32 v26;
  s32 v27;
  s32 v28;
  s64 v29;
  u32 v30;
  sdatParaWork_t *v31;
  s32 v32;
  s32 v33;
  s32 v34;
  s32 v35;
  s32 v36;

  switch (mode)
  {
    case 1:
      para = GBWK->player->para;
      BadStatus = sBtlGetBadStatus(para);
      if (BadStatus != 11)
        goto LABEL_30;
      now = GBWK->player->para->now;
      hp = now->hp;
      v11 = 3 * now->maxhp;
      if ((u32)(v11 + 99) >= 0xC7)
      {
        v14 = v11 / -100 + hp;
        if (v14 <= 1)
          v13 = 1;
        else
          v13 = v14;
        goto LABEL_29;
      }
      else
      {
        v12 = hp - 1;
        if (v12 <= 1)
          v13 = 1;
        else
          v13 = v12;
        goto LABEL_29;
      }
      now = GBWK->player->para->now;
LABEL_29:
      now->hp = v13;
      goto LABEL_30;
    case 2:
      goto LABEL_64;
    case 3:
      goto LABEL_72;
    case 4:
LABEL_30:
      v15 = 4;
      while (2)
      {
        player = GBWK->player;
        if (v15 - 4 < player->stock_max)
        {
          v20 = *((sdatUnitWork_t *)&player->stock_id->obj.klass + v15);
          if (GBWK->mapSummonID == v20->devilid)
          {
            v24 = sBtlGetBadStatus(v20);
            if (v24 != 11)
              goto LABEL_37;
            v29 = *(u64 *)(*((u64 *)&GBWK->player->stock_id->obj.klass + v15) + 40);
            v25 = *(u32 *)(v29 + 16);
            if (v25 < 1)
              goto LABEL_37;
            if (v26)
            {
              v27 = 3 * *(u32 *)(v29 + 20);
              v28 = -1;
              if ((u32)(v27 + 99) >= 0xC7)
                goto LABEL_61;
            }
            else
            {
              v29 = *(u64 *)(*((u64 *)&GBWK->player->stock_id->obj.klass + v15) + 40);
              v25 = *(u32 *)(v29 + 16);
              v27 = 3 * *(u32 *)(v29 + 20);
              v28 = -1;
              if ((u32)(v27 + 99) >= 0xC7)
LABEL_61:
                v28 = v27 / -100;
            }
            v16 = v28 + v25;
            if (v16 <= 1)
              v17 = 1;
            else
              v17 = v16;
            if (!v26)
            {
              v29 = *(u64 *)(*((u64 *)&GBWK->player->stock_id->obj.klass + v15) + 40);
            }
            *(u32 *)(v29 + 16) = v17;
            goto LABEL_37;
          }
LABEL_37:
          ++v15;
          continue;
        }
        break;
      }
      if (mode == 3)
      {
LABEL_72:
        v31 = GBWK->player->para->now;
        v32 = v31->hp;
        v33 = 50 * v32;
        if ((u32)(50 * v32 + 99) < 0xC7)
          goto LABEL_67;
LABEL_75:
        v36 = v33 / -100 + v32;
        if (v36 <= 1)
          v35 = 1;
        else
          v35 = v36;
        if (!v30)
          goto LABEL_79;
        goto LABEL_80;
      }
      if (mode != 2)
        return;
LABEL_64:
      v31 = GBWK->player->para->now;
      v32 = v31->hp;
      v33 = 10 * v31->maxhp;
      if ((u32)(v33 + 99) >= 0xC7)
        goto LABEL_75;
LABEL_67:
      v34 = v32 - 1;
      if (v34 <= 1)
        v35 = 1;
      else
        v35 = v34;
      if (!v30)
      {
LABEL_79:
        v31 = GBWK->player->para->now;
      }
LABEL_80:
      v31->hp = v35;
      return;
    default:
      return;
  }
}

// 0x18fefd0
bool datCheckBadPartyMap(s32 bad) {
  sdatUnitWork_t *para;
  s32 StockDevilIndex;
  s32 v10;
  sdatUnitWork_t *v12;

  para = GBWK->player->para;
  if (sBtlGetBadStatus(para) == bad)
    return 1;
  StockDevilIndex = datGetStockDevilIndex(GBWK->mapSummonID, GBWK->mapSummonUNIQ);
  if (StockDevilIndex == -1)
    return 0;
  v10 = StockDevilIndex;
  v12 = GBWK->player->stock_id[v10];
  return sBtlGetBadStatus(v12) == bad;
}

// 0x18ff210
void datResetBadStat(sdatUnitWork_t *pWork, u32 badstat) {
  pWork->badstatus &= ~(1 << badstat);
}

// 0x18ff230
s32 datDebtFromGouto(s32 money) {
  void *achievementTbl_k__BackingField;
  Project_DefineAchievementID_string__c *klass;
  s64 v10;
  Project_DefineAchievementID_string__c **p_offset;
  s64 v13;
  char *v14;
  s32 v18;
  dds3GlobalWork_t *v19;
  sdatPlayerUnitWork_t *player;
  s32 gold;

  if (money >= 1)
  {
    GBWK->debt_from_gouto += money;
    achievementTbl_k__BackingField = _achievementTbl_k__BackingField;
    klass = achievementTbl_k__BackingField->klass;
    v10 = *(u16 *)&achievementTbl_k__BackingField->klass->_2.rank;
    if (!*(u16 *)&achievementTbl_k__BackingField->klass->_2.rank)
      goto LABEL_19;
    goto LABEL_16;
    if (!*(u16 *)&achievementTbl_k__BackingField->klass->_2.rank)
    {
LABEL_19:
      v13 = sub_4227F4(achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 0xFu);
LABEL_21:
      v14 = (*v13)(achievementTbl_k__BackingField, *(u64 *)(v13 + 8));
      Unlock_2(v14);
      if (GBWK->debt_from_gouto >= 10000000)
      {
        GBWK->debt_from_gouto = 9999999;
      }
      goto LABEL_25;
    }
LABEL_16:
    p_offset = &klass->_1.interfaceOffsets->offset;
    while (*(p_offset - 1) != Project_DefineAchievementID_string_)
    {
      p_offset += 2;
      if (!--v10)
        goto LABEL_19;
    }
    v13 = &klass->vtable[*(u32 *)p_offset + 15];
    goto LABEL_21;
  }
  if ((money & 0x80000000) == 0)
  {
LABEL_25:
    return GBWK->debt_from_gouto;
  }
  v18 = -money;
  v19 = GBWK;
  player = v19->player;
  gold = player->gold;
  if (gold < v18)
    return 0;
  v19 = GBWK;
  player = v19->player;
  gold = player->gold;
  player->gold = gold + money;
  v19->debt_from_gouto += money;
  return 1;
}

// 0x18ff4d0
u32 datGetSummonerRank(void) {
  return cmpGetNowSummonerRank() + 1;
}

// 0x18ff550
bool datChkCard(s16 devilid) {
  return (GBWK->player->devilCard[(s16)(devilid + (((u32)devilid >> 28) & 7)) >> 3] & (0x1000000 << (devilid - ((devilid + (((u32)devilid >> 28) & 7)) & 0x18)) >> 24)) != 0;
}

// 0x18ff5f0
void datSetCard(s16 devilid) {
  s32 v2;
  s32 v4;
  char *v5;

  v2 = devilid;
  v4 = v2 + (((u32)(s16)v2 >> 28) & 7);
  v5 = (char *)GBWK->player->devilCard + ((s16)v4 >> 3);
  v5[32] |= 1 << (v2 - (v4 & 0x18));
}

// 0x18ff690
void datAddStock(s32 nums) {
  char v2;
  sdatPlayerUnitWork_t *player;
  s32 v5;

  v2 = nums;
  player = GBWK->player;
  v5 = (char)(player->stock_max + v2);
  player->stock_max += v2;
  if (v5 >= 33)
  {
    player = GBWK->player;
    player->stock_max = 32;
  }
}

// 0x18ff740
void datSetSummonerRank(u32 uRank) {
  il2cpp_array_size_t max_length;
  s64 v5;
  s64 v6;
  s64 v7;
  s32 v8;
  s64 v9;
  u32 v10;
  s64 v11;
  s32 v12;
  s32 v13;
  s32 v14;
  s64 v15;
  s32 v16;

  max_length = s_aSummonerRankTbl->max_length;
  v5 = (u32)max_length;
  if (uRank - 1 >= (u32)max_length)
    v6 = (u32)max_length;
  else
    v6 = uRank - 1;
  if ((u32)v6)
  {
    v7 = 0;
    v8 = 0;
    while (1)
    {
      if (evtBitCheck(s_aSummonerRankTbl[v7]))
      {
        goto LABEL_18;
      }
      else
      {
        cmpRankNewOn(v8);
LABEL_18:
        v10 = s_aSummonerRankTbl[v7];
        goto LABEL_19;
      }
      v10 = s_aSummonerRankTbl[v7];
LABEL_19:
      if (v10)
      {
        if (v10 - 2618 >= 0xFFFFFFC6)
        {
          evtBitKityouItemAdd(v10);
        }
        v9 = (s64)GBWK->EventBit + 4 * ((s32)((v10 + ((v10 >> 26) & 0x1F)) << 16) >> 21);
        *(u32 *)(v9 + 32) |= 1 << v10;
      }
      v7 = ++v8;
      if (v8 >= v6)
        goto LABEL_29;
    }
  }
  v8 = 0;
LABEL_29:
  v11 = v8;
  if (v5 > v8)
  {
    v12 = v8 + 1;
    do
    {
      v16 = (u16)s_aSummonerRankTbl[v11];
      v13 = 1 << v16;
      v14 = v16 + (((u32)(s16)v16 >> 26) & 0x1F);
      v11 = v12++;
      v15 = (s64)GBWK->EventBit + 4 * ((s16)v14 >> 5);
      *(u32 *)(v15 + 32) &= ~v13;
    }
    while (v5 > v11);
  }
}

// 0x18ffa00
s32 datGetSummonerRankNum(void) {
  s16 *v2;
  s64 max_length_low;
  s32 max_length;
  s64 v7;

  v2 = s_aSummonerRankTbl;
  max_length_low = LODWORD(v2->max_length);
  if (!LODWORD(v2->max_length))
  {
LABEL_5:
    max_length = s_aSummonerRankTbl->max_length;
    return max_length + 1;
  }
  v7 = 0;
  max_length = 0;
  while (1)
  {
    if (!evtBitCheck(s_aSummonerRankTbl[v7]))
      return max_length + 1;
    v7 = ++max_length;
    if (max_length_low <= max_length)
    {
      goto LABEL_5;
    }
  }
}

// 0x18ffb10
void datCalcLuckParam(void) {
  sdatUnitWork_t *para;
  sdatParaWork_t *now;
  s16 luck;
  u32 v5;
  s16 v6;
  s32 v7;
  s16 v8;
  s16 v9;
  s16 v10;
  sdatParaWork_t *v12;

  para = GBWK->player->para;
  now = para->now;
  luck = para->backup->luck;
  v5 = (u16)para->pitem->luck;
  v6 = para->pbtl->luck;
  v7 = (v5 >> 8) + (u8)v5;
  v8 = para->huuma->luck;
  v9 = para->surpriseParam->luck;
  v10 = v9 + sBtlGetCorrectionParamLuck();
  now->luck = v6 + luck + v8 + v7 + v10;
  v12 = GBWK->player->para->now;
  if (v12->luck <= 0)
  {
    v12 = GBWK->player->para->now;
    v12->luck = 1;
  }
}

// 0x18ffc70
s32 datSklDrawMaxCnt(sdatUnitWork_t *pWork) {
  SKLID *haveskill;
  s64 max_length;
  s64 v4;
  s64 v5;
  s32 result;
  s64 v7;
  char *v8;
  u32 v9;
  u32 v10;
  s32 v11;

  haveskill = pWork->haveskill;
  if ((s32)haveskill->max_length < 1)
    return 0;
  max_length = (u32)haveskill->max_length;
  v4 = haveskill->max_length & 1;
  if (max_length == 1)
  {
    v5 = 0;
    result = 0;
  }
  else
  {
    v5 = 0;
    result = 0;
    v7 = max_length - v4;
    do
    {
      v8 = (char *)haveskill + 4 * v5;
      v5 += 2;
      v9 = *((u32 *)v8 + 8) + 1;
      v10 = *((u32 *)v8 + 9) + 1;
      if (v9 < 2)
        v11 = result;
      else
        v11 = result + 1;
      if (v10 < 2)
        result = v11;
      else
        result = v11 + 1;
    }
    while (v7 != v5);
  }
  if (v4)
  {
    if ((u32)(haveskill[v5] + 1) >= 2)
      ++result;
  }
  return result;
}

// 0x18ffd00
s32 datSklItmDrawMaxCnt(sdatUnitWork_t *pWork) {
  SKLID *haveskill;
  s64 v4;
  s64 v5;
  s64 v6;
  s32 result;
  SKLID *aRsvSkl;
  il2cpp_array_size_t max_length;
  s64 v10;
  char *v11;
  u32 v12;
  u32 v13;
  s32 v14;
  s64 v15;
  il2cpp_array_size_t v16;
  s64 v17;
  s64 v18;
  char *v19;
  u32 v20;
  u32 v21;
  s32 v22;

  haveskill = pWork->haveskill;
  if ((s32)haveskill->max_length < 1)
  {
    result = 0;
    aRsvSkl = pWork->aRsvSkl;
    max_length = aRsvSkl->max_length;
    if ((s32)max_length < 1)
      return result;
  }
  else
  {
    v4 = (u32)haveskill->max_length;
    v5 = haveskill->max_length & 1;
    if (v4 == 1)
    {
      v6 = 0;
      result = 0;
    }
    else
    {
      v6 = 0;
      result = 0;
      v10 = v4 - v5;
      do
      {
        v11 = (char *)haveskill + 4 * v6;
        v6 += 2;
        v12 = *((u32 *)v11 + 8) + 1;
        v13 = *((u32 *)v11 + 9) + 1;
        if (v12 < 2)
          v14 = result;
        else
          v14 = result + 1;
        if (v13 < 2)
          result = v14;
        else
          result = v14 + 1;
      }
      while (v10 != v6);
    }
    if (v5 && (u32)(haveskill[v6] + 1) >= 2)
    {
      ++result;
      aRsvSkl = pWork->aRsvSkl;
      max_length = aRsvSkl->max_length;
      if ((s32)max_length < 1)
        return result;
    }
    else
    {
      aRsvSkl = pWork->aRsvSkl;
      max_length = aRsvSkl->max_length;
      if ((s32)max_length < 1)
        return result;
    }
  }
  v15 = (u32)max_length;
  v16 = max_length & 1;
  if (v15 == 1)
  {
    v17 = 0;
  }
  else
  {
    v17 = 0;
    v18 = v15 - v16;
    do
    {
      v19 = (char *)aRsvSkl + 4 * v17;
      v17 += 2;
      v20 = *((u32 *)v19 + 8) + 1;
      v21 = *((u32 *)v19 + 9) + 1;
      if (v20 < 2)
        v22 = result;
      else
        v22 = result + 1;
      if (v21 < 2)
        result = v22;
      else
        result = v22 + 1;
    }
    while (v18 != v17);
  }
  if (v16)
  {
    if ((u32)(aRsvSkl[v17] + 1) >= 2)
      ++result;
  }
  return result;
}

// 0x18ffe40
bool datOmoideSkillGetMaster(sdatUnitWork_t *pWork, SKLID uSkillNo) {
  s32 Skill2OmoideSkillNo;
  s8 *aOmoideSkillMaster;
  s64 v6;
  u32 v7;
  s32 v8;
  _BOOL4 v9;

  Skill2OmoideSkillNo = gohGetSkill2OmoideSkillNo(uSkillNo);
  aOmoideSkillMaster = pWork->aOmoideSkillMaster;
  v6 = (u32)Skill2OmoideSkillNo >> 3;
  if (SLODWORD(aOmoideSkillMaster->max_length) <= v6)
  {
    LOBYTE(v9) = 0;
  }
  else
  {
    v7 = aOmoideSkillMaster[v6];
    if (Skill2OmoideSkillNo <= 0)
      v8 = -(-Skill2OmoideSkillNo & 7);
    else
      LOBYTE(v8) = Skill2OmoideSkillNo & 7;
    return (v7 >> v8) & 1;
  }
  return v9;
}

// 0x18ffeb0
bool datSwordSklGetMaster(sdatPlayerUnitWork_t *pWork, SKLID uSkillNo) {
  bool v5;
  s32 RaidouSkillNo;
  s8 *raidouSkillMaster;
  s64 v9;
  u32 v10;
  s32 v11;
  _BOOL4 v12;

  v5 = RaidouSklCheck(uSkillNo);
  if (v5)
  {
    RaidouSkillNo = gohGetRaidouSkillNo(uSkillNo);
    raidouSkillMaster = pWork->raidouSkillMaster;
    v9 = (u32)RaidouSkillNo >> 3;
    if (SLODWORD(raidouSkillMaster->max_length) > v9)
      goto LABEL_9;
LABEL_18:
    LOBYTE(v12) = 0;
    return v12;
  }
  if (uSkillNo == 1024)
  {
    LOBYTE(v12) = 1;
    return v12;
  }
  RaidouSkillNo = gohGetSkillSpiritSkillNo(uSkillNo);
  raidouSkillMaster = pWork->spiritMaster;
  v9 = (u32)RaidouSkillNo >> 3;
  if (SLODWORD(raidouSkillMaster->max_length) <= v9)
    goto LABEL_18;
LABEL_9:
  v10 = raidouSkillMaster[v9];
  if (RaidouSkillNo <= 0)
    v11 = -(-RaidouSkillNo & 7);
  else
    LOBYTE(v11) = RaidouSkillNo & 7;
  return (v10 >> v11) & 1;
}

// 0x1900060
bool datSpiritSkillGetMaster(sdatPlayerUnitWork_t *pWork, SKLID uSkillNo) {
  _BOOL4 v3;
  s32 SkillSpiritSkillNo;
  s8 *spiritMaster;
  s64 v7;
  u32 v8;
  s32 v9;

  if (uSkillNo == 1024)
  {
    LOBYTE(v3) = 1;
  }
  else
  {
    SkillSpiritSkillNo = gohGetSkillSpiritSkillNo(uSkillNo);
    spiritMaster = pWork->spiritMaster;
    v7 = (u32)SkillSpiritSkillNo >> 3;
    if (SLODWORD(spiritMaster->max_length) <= v7)
    {
      LOBYTE(v3) = 0;
    }
    else
    {
      v8 = spiritMaster[v7];
      if (SkillSpiritSkillNo <= 0)
        v9 = -(-SkillSpiritSkillNo & 7);
      else
        LOBYTE(v9) = SkillSpiritSkillNo & 7;
      return (v8 >> v9) & 1;
    }
  }
  return v3;
}

// 0x18ffff0
bool datRaidouSkillGetMaster(sdatPlayerUnitWork_t *pWork, SKLID uSkillNo) {
  s32 RaidouSkillNo;
  s8 *raidouSkillMaster;
  s64 v6;
  u32 v7;
  s32 v8;
  _BOOL4 v9;

  RaidouSkillNo = gohGetRaidouSkillNo(uSkillNo);
  raidouSkillMaster = pWork->raidouSkillMaster;
  v6 = (u32)RaidouSkillNo >> 3;
  if (SLODWORD(raidouSkillMaster->max_length) <= v6)
  {
    LOBYTE(v9) = 0;
  }
  else
  {
    v7 = raidouSkillMaster[v6];
    if (RaidouSkillNo <= 0)
      v8 = -(-RaidouSkillNo & 7);
    else
      LOBYTE(v8) = RaidouSkillNo & 7;
    return (v7 >> v8) & 1;
  }
  return v9;
}

// 0x19000e0
bool datOmoideSkillHaveSkill(sdatUnitWork_t *pWork, SKLID uSkillNo) {
  SKLID *aOmoideSkill;
  u64 max_length_low;
  s64 v6;
  s32 *v7;
  s64 v8;
  s32 v9;

  aOmoideSkill = pWork->aOmoideSkill;
  max_length_low = LODWORD(aOmoideSkill->max_length);
  if (!LODWORD(aOmoideSkill->max_length))
    return 0;
  if (aOmoideSkill[0] == uSkillNo)
    return 1;
  v6 = 0;
  v7 = &aOmoideSkill[1];
  do
  {
    v8 = v6;
    if (max_length_low - 1 == v6)
      break;
    v9 = v7[v6++];
  }
  while (v9 != uSkillNo);
  return v8 + 1 < max_length_low;
}

// 0x1900140
bool datSpiritSkillHaveSkill(sdatPlayerUnitWork_t *pWork, SKLID uSkillNo) {
  SKLID *spiritSkill;
  u64 max_length_low;
  s64 v6;
  s32 *v7;
  s64 v8;
  s32 v9;

  spiritSkill = pWork->spiritSkill;
  max_length_low = LODWORD(spiritSkill->max_length);
  if (!LODWORD(spiritSkill->max_length))
    return 0;
  if (spiritSkill[0] == uSkillNo)
    return 1;
  v6 = 0;
  v7 = &spiritSkill[1];
  do
  {
    v8 = v6;
    if (max_length_low - 1 == v6)
      break;
    v9 = v7[v6++];
  }
  while (v9 != uSkillNo);
  return v8 + 1 < max_length_low;
}

// 0x19001a0
void datOmoideSkillSetMaster(sdatUnitWork_t *pWork, SKLID uSkillNo, bool bFlag) {
  s32 Skill2OmoideSkillNo;
  s8 *aOmoideSkillMaster;
  signed s64 v8;
  char *v9;
  char v10;
  s32 v11;
  s32 v12;
  char v13;
  char v14;

  if ((u32)(uSkillNo + 1) >= 2)
  {
    Skill2OmoideSkillNo = gohGetSkill2OmoideSkillNo(uSkillNo);
    aOmoideSkillMaster = pWork->aOmoideSkillMaster;
    v8 = (u64)(u32)Skill2OmoideSkillNo >> 3;
    if (SLODWORD(aOmoideSkillMaster->max_length) > v8)
    {
      v9 = (char *)aOmoideSkillMaster + v8;
      v10 = v9[32];
      if (Skill2OmoideSkillNo <= 0)
        v11 = -(-Skill2OmoideSkillNo & 7);
      else
        LOBYTE(v11) = Skill2OmoideSkillNo & 7;
      v12 = 1 << v11;
      v13 = v10 & ~(u8)v12;
      v14 = v10 | v12;
      if (!bFlag)
        v14 = v13;
      v9[32] = v14;
    }
  }
}

// 0x1900230
s8 *datOmoideSkillDelOfcSkl(sdatUnitWork_t *_unit) {
  void *sklItemGuages;
  void *v4;
  s8 *v5;
  s32 v6;
  s32 Skill2OmoideSkillNo;
  s8 *aOmoideSkillMaster;
  s64 v9;
  u32 v10;
  s32 v11;
  s32 v12;
  signed s64 v13;
  s32 v14;
  System_Collections_Generic_List_Enumerator_T__o v16;

  memset(&v16, 0, sizeof(v16));
  sklItemGuages = unit->sklItemGuages;
  v4 = Allocate(System_Collections_Generic_List_SklItemGuage_);
  __ctor_48217552(v4, sklItemGuages);
  v5 = NewSpecific(sbyte, 0x10u);
  Copy_56180528(unit->aOmoideSkillMaster, v5, *(u32 *)((char *)v5 + 24), 0);
  _GetEnumerator(&v16, v4);
  while (_MoveNext(&v16))
  {
    v6 = *(u32 *)((char *)&v16._current->klass + (u64)sub_10);
    if (v6)
    {
      Skill2OmoideSkillNo = gohGetSkill2OmoideSkillNo(v6);
      aOmoideSkillMaster = unit->aOmoideSkillMaster;
      v9 = (u32)Skill2OmoideSkillNo >> 3;
      if (SLODWORD(aOmoideSkillMaster->max_length) > v9)
      {
        v10 = aOmoideSkillMaster[v9];
        if (Skill2OmoideSkillNo <= 0)
          v11 = -(-Skill2OmoideSkillNo & 7);
        else
          LOBYTE(v11) = Skill2OmoideSkillNo & 7;
        if (((v10 >> v11) & 1) != 0)
        {
          v12 = gohGetSkill2OmoideSkillNo(v6);
          v13 = (u64)(u32)v12 >> 3;
          if (SLODWORD(unit->aOmoideSkillMaster->max_length) > v13)
          {
            if (v12 <= 0)
              v14 = -(-v12 & 7);
            else
              LOBYTE(v14) = v12 & 7;
            *(u8 *)((s64)&v5[0] + v13) &= ~(1 << v14);
          }
        }
      }
    }
  }
  _Dispose(&v16);
  return v5;
}

// 0x19004b0
void datSpiritSkillSetMaster(sdatPlayerUnitWork_t *pWork, SKLID uSkillNo, bool bFlag) {
}

// 0x1900630
void datRaidouSkillSetMaster(sdatPlayerUnitWork_t *pWork, SKLID uSkillNo, bool bFlag) {
  s32 RaidouSkillNo;
  s8 *raidouSkillMaster;
  signed s64 v9;
  s8 *m_Items;
  s32 v11;
  s32 v12;
  s8 v13;
  s32 IsRegCnt;
  void *achievementTbl_k__BackingField;
  Project_DefineAchievementID_string__c *klass;
  s64 v20;
  Project_DefineAchievementID_string__c **p_offset;
  s64 v22;
  char *v24;

  RaidouSkillNo = gohGetRaidouSkillNo(uSkillNo);
  raidouSkillMaster = pWork->raidouSkillMaster;
  v9 = (u64)(u32)RaidouSkillNo >> 3;
  if (SLODWORD(raidouSkillMaster->max_length) <= v9)
    return;
  m_Items = raidouSkillMaster;
  if (RaidouSkillNo <= 0)
    v11 = -(-RaidouSkillNo & 7);
  else
    LOBYTE(v11) = RaidouSkillNo & 7;
  v12 = 1 << v11;
  v13 = m_Items[v9];
  if (!bFlag)
  {
    m_Items[v9] = v13 & ~(u8)v12;
    RaidouSklGetListSet(GBWK->sortSave, uSkillNo, 1, 0);
    return;
  }
  m_Items[v9] = v13 | v12;
  RaidouSklGetListSet(GBWK->sortSave, uSkillNo, 0, 0);
  IsRegCnt = datRaidouSkillIsRegCnt(pWork);
  achievementTbl_k__BackingField = _achievementTbl_k__BackingField;
  klass = achievementTbl_k__BackingField->klass;
  v20 = *(u16 *)&achievementTbl_k__BackingField->klass->_2.rank;
  if (*(u16 *)&achievementTbl_k__BackingField->klass->_2.rank)
  {
    p_offset = &klass->_1.interfaceOffsets->offset;
    while (*(p_offset - 1) != Project_DefineAchievementID_string_)
    {
      p_offset += 2;
      if (!--v20)
        goto LABEL_18;
    }
    v22 = (&klass[1]._1.element_class + 2 * *(u32 *)p_offset);
  }
  else
  {
LABEL_18:
    v22 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 0x24u);
  }
  v24 = (*v22)(achievementTbl_k__BackingField, *(u64 *)(v22 + 8));
  ProgressUnlock_3(v24, IsRegCnt, 16);
}

// 0x19009d0
s32 datSpiritSkillGetCount(sdatPlayerUnitWork_t *pWork) {
  il2cpp_array_size_t max_length;
  u64 v5;
  s32 v6;
  s64 v7;
  s32 v9;
  s32 SkillSpiritSkillNo;
  s8 *spiritMaster;
  s64 v12;
  u32 v13;
  s32 v14;

  max_length = spiritList->max_length;
  if ((s32)max_length >= 1)
  {
    v5 = 0;
    v6 = 0;
    v7 = 4 * (u32)max_length;
    while (1)
    {
      v9 = spiritList[v5 / 4];
      if (v9 != 1024)
      {
        SkillSpiritSkillNo = gohGetSkillSpiritSkillNo(v9);
        spiritMaster = pWork->spiritMaster;
        v12 = (u32)SkillSpiritSkillNo >> 3;
        if (SLODWORD(spiritMaster->max_length) <= v12)
          goto LABEL_6;
        v13 = spiritMaster[v12];
        if (SkillSpiritSkillNo <= 0)
          v14 = -(-SkillSpiritSkillNo & 7);
        else
          LOBYTE(v14) = SkillSpiritSkillNo & 7;
        if (((v13 >> v14) & 1) == 0)
          goto LABEL_6;
      }
      ++v6;
LABEL_6:
      v5 += 4;
      if (v7 == v5)
        return v6;
    }
  }
  return 0;
}

// 0x1900b50
s32 datRaidouSkillGetCount(sdatPlayerUnitWork_t *pWork) {
  il2cpp_array_size_t max_length;
  u64 v5;
  s32 v6;
  s64 v7;
  s32 v9;
  s32 RaidouSkillNo;
  s8 *raidouSkillMaster;
  s64 v12;
  u32 v13;
  s32 v14;

  max_length = raidouSkillList->max_length;
  if ((s32)max_length < 1)
    return 0;
  v5 = 0;
  v6 = 0;
  v7 = 4 * (u32)max_length;
  do
  {
    v9 = raidouSkillList[v5 / 4];
    RaidouSkillNo = gohGetRaidouSkillNo(v9);
    raidouSkillMaster = pWork->raidouSkillMaster;
    v12 = (u32)RaidouSkillNo >> 3;
    if (SLODWORD(raidouSkillMaster->max_length) > v12)
    {
      v13 = raidouSkillMaster[v12];
      if (RaidouSkillNo <= 0)
        v14 = -(-RaidouSkillNo & 7);
      else
        LOBYTE(v14) = RaidouSkillNo & 7;
      v6 += (v13 >> v14) & 1;
    }
    v5 += 4;
  }
  while (v7 != v5);
  return v6;
}

// 0x1900cb0
s32 datOmoideSkillSetCnt(sdatUnitWork_t *pWork) {
  SKLID *aOmoideSkill;
  u64 max_length;
  s64 v4;
  s32 result;
  int32x4_t v6;
  int32x4_t *v7;
  s64 v8;
  int32x4_t v9;
  int32x4_t v10;
  int32x4_t v11;
  int32x4_t v12;
  int32x4_t v13;
  int32x4_t v14;
  int32x4_t v15;
  u64 v16;
  s32 *v17;

  aOmoideSkill = pWork->aOmoideSkill;
  if ((s32)aOmoideSkill->max_length < 1)
    return 0;
  max_length = (u32)aOmoideSkill->max_length;
  if (max_length >= 0x10)
  {
    v6 = 0u;
    v4 = aOmoideSkill->max_length & 0xFFFFFFF0;
    v7 = &aOmoideSkill[12];
    v8 = v4;
    v9 = 0u;
    v10 = 0u;
    v11 = 0u;
    do
    {
      v8 -= 16;
      v12 = vtstq_s32(v7[-2], v7[-2]);
      v13 = vtstq_s32(v7[-3], v7[-3]);
      v14 = vtstq_s32(v7[-1], v7[-1]);
      v15 = vtstq_s32(*v7, *v7);
      v7 += 4;
      v9 = vsubq_s32(v9, v12);
      v11 = vsubq_s32(v11, v15);
      v6 = vsubq_s32(v6, v13);
      v10 = vsubq_s32(v10, v14);
    }
    while (v8);
    result = vaddvq_s32(vaddq_s32(vaddq_s32(v11, v10), vaddq_s32(v9, v6)));
    if ((aOmoideSkill->max_length & 0xF) == 0)
      return result;
  }
  else
  {
    v4 = 0;
    result = 0;
  }
  v16 = max_length - v4;
  v17 = &aOmoideSkill[v4];
  do
  {
    if (*v17++)
      ++result;
    --v16;
  }
  while (v16);
  return result;
}

// 0x1900d80
s32 datOmoideSkillGetCount(sdatUnitWork_t *pWork) {
  il2cpp_array_size_t max_length;
  u64 v5;
  s32 v6;
  s64 v7;
  s32 v9;
  s32 Skill2OmoideSkillNo;
  s8 *aOmoideSkillMaster;
  s64 v12;
  u32 v13;
  s32 v14;

  max_length = g_aOmoide->max_length;
  if ((s32)max_length < 1)
    return 0;
  v5 = 0;
  v6 = 0;
  v7 = 4 * (u32)max_length;
  do
  {
    v9 = g_aOmoide[v5 / 4];
    Skill2OmoideSkillNo = gohGetSkill2OmoideSkillNo(v9);
    aOmoideSkillMaster = pWork->aOmoideSkillMaster;
    v12 = (u32)Skill2OmoideSkillNo >> 3;
    if (SLODWORD(aOmoideSkillMaster->max_length) > v12)
    {
      v13 = aOmoideSkillMaster[v12];
      if (Skill2OmoideSkillNo <= 0)
        v14 = -(-Skill2OmoideSkillNo & 7);
      else
        LOBYTE(v14) = Skill2OmoideSkillNo & 7;
      v6 += (v13 >> v14) & 1;
    }
    v5 += 4;
  }
  while (v7 != v5);
  return v6;
}

// 0x1900ee0
bool datOmoideSkillIsComplete(sdatUnitWork_t *pWork) {
  il2cpp_array_size_t max_length;
  bool v5;
  s64 v6;
  s64 v7;
  s64 v8;
  s64 v9;
  s32 v10;
  s32 Skill2OmoideSkillNo;
  s8 *aOmoideSkillMaster;
  s64 v14;
  u32 v15;
  s32 v16;

  max_length = g_aOmoide->max_length;
  if ((s32)max_length >= 1)
  {
    v5 = 0;
    v6 = (s32)max_length;
    v7 = -(s64)(u32)max_length;
    v8 = 8;
    while (1)
    {
      v10 = *((u32 *)&g_aOmoide->obj.klass + v8);
      if ((u32)(v10 - 257) < 2)
        goto LABEL_5;
      if (v10 == 861 || v10 == 969)
        goto LABEL_5;
      Skill2OmoideSkillNo = gohGetSkill2OmoideSkillNo(v10);
      aOmoideSkillMaster = pWork->aOmoideSkillMaster;
      v14 = (u32)Skill2OmoideSkillNo >> 3;
      if (SLODWORD(aOmoideSkillMaster->max_length) <= v14)
        return v5;
      v15 = aOmoideSkillMaster[v14];
      if (Skill2OmoideSkillNo <= 0)
        v16 = -(-Skill2OmoideSkillNo & 7);
      else
        LOBYTE(v16) = Skill2OmoideSkillNo & 7;
      if (((v15 >> v16) & 1) == 0)
        return v5;
LABEL_5:
      v9 = v8 - 7;
      ++v8;
      v5 = v9 >= v6;
      if (v7 + v8 == 8)
        return v5;
    }
  }
  return 1;
}

// 0x19010b0
bool datSpiritSkillIsComplete(sdatPlayerUnitWork_t *pWork) {
  il2cpp_array_size_t max_length;
  s64 v5;
  s64 v6;
  bool v7;
  s64 v8;
  s32 v10;
  s32 SkillSpiritSkillNo;
  s8 *spiritMaster;
  s64 v13;
  u32 v14;
  s32 v15;

  max_length = spiritList->max_length;
  if ((s32)max_length >= 1)
  {
    v5 = (u32)max_length;
    v6 = 0;
    v7 = 0;
    v8 = (s32)max_length;
    while (1)
    {
      v10 = spiritList[v6];
      if (v10 != 1024)
      {
        SkillSpiritSkillNo = gohGetSkillSpiritSkillNo(v10);
        spiritMaster = pWork->spiritMaster;
        v13 = (u32)SkillSpiritSkillNo >> 3;
        if (SLODWORD(spiritMaster->max_length) <= v13)
          return v7;
        v14 = spiritMaster[v13];
        if (SkillSpiritSkillNo <= 0)
          v15 = -(-SkillSpiritSkillNo & 7);
        else
          LOBYTE(v15) = SkillSpiritSkillNo & 7;
        if (((v14 >> v15) & 1) == 0)
          return v7;
      }
      v7 = ++v6 >= v8;
      if (v5 == v6)
        return v7;
    }
  }
  return 1;
}

// 0x1901230
bool datRaidouSkillIsComplete(sdatPlayerUnitWork_t *pWork) {
  il2cpp_array_size_t max_length;
  s64 v5;
  s64 v6;
  bool v7;
  s64 v8;
  s32 v10;
  s32 RaidouSkillNo;
  s8 *raidouSkillMaster;
  s64 v13;
  u32 v14;
  s32 v15;

  max_length = raidouSkillList->max_length;
  if ((s32)max_length < 1)
    return 1;
  v5 = (u32)max_length;
  v6 = 0;
  v7 = 0;
  v8 = (s32)max_length;
  do
  {
    v10 = raidouSkillList[v6];
    RaidouSkillNo = gohGetRaidouSkillNo(v10);
    raidouSkillMaster = pWork->raidouSkillMaster;
    v13 = (u32)RaidouSkillNo >> 3;
    if (SLODWORD(raidouSkillMaster->max_length) <= v13)
      break;
    v14 = raidouSkillMaster[v13];
    if (RaidouSkillNo <= 0)
      v15 = -(-RaidouSkillNo & 7);
    else
      LOBYTE(v15) = RaidouSkillNo & 7;
    if (((v14 >> v15) & 1) == 0)
      break;
    v7 = ++v6 >= v8;
  }
  while (v5 != v6);
  return v7;
}

// 0x1900870
s32 datRaidouSkillIsRegCnt(sdatPlayerUnitWork_t *pWork) {
  il2cpp_array_size_t max_length;
  u64 v5;
  s32 v6;
  s64 v7;
  s32 v9;
  s32 RaidouSkillNo;
  s8 *raidouSkillMaster;
  s64 v12;
  u32 v13;
  s32 v14;

  max_length = raidouSkillList->max_length;
  if ((s32)max_length < 1)
    return 0;
  v5 = 0;
  v6 = 0;
  v7 = 4 * (u32)max_length;
  do
  {
    v9 = raidouSkillList[v5 / 4];
    RaidouSkillNo = gohGetRaidouSkillNo(v9);
    raidouSkillMaster = pWork->raidouSkillMaster;
    v12 = (u32)RaidouSkillNo >> 3;
    if (SLODWORD(raidouSkillMaster->max_length) > v12)
    {
      v13 = raidouSkillMaster[v12];
      if (RaidouSkillNo <= 0)
        v14 = -(-RaidouSkillNo & 7);
      else
        LOBYTE(v14) = RaidouSkillNo & 7;
      v6 += (v13 >> v14) & 1;
    }
    v5 += 4;
  }
  while (v7 != v5);
  return v6;
}

// 0x19013a0
bool datChkSpiritSkl(SKLID _sklID) {
  return sklID == 696 || (u32)(sklID - 690) < 3 || sklID == 701;
}

// 0x19013c0
bool datChkKeisyouSkl(s32 _devilID, SKLID _skl) {
  signed s16 transfer;
  signed s16 keisyo_form;
  char v10;

  transfer = sBtlGetSkilltbl(skl)->transfer;
  keisyo_form = sBtlGetDevilData(devilID, -1)->keisyo_form;
  if ((transfer & 1) != 0 && (keisyo_form & 1) == 0 || (transfer & 2) != 0 && (keisyo_form & 2) == 0 || (transfer & 4) != 0 && (keisyo_form & 4) == 0 || (transfer & 8) != 0 && (keisyo_form & 8) == 0 || (transfer & 0x10) != 0 && (keisyo_form & 0x10) == 0 || (transfer & 0x20) != 0 && (keisyo_form & 0x20) == 0 || (transfer & 0x40) != 0 && (keisyo_form & 0x40) == 0 || (transfer & 0x80) != 0 && (keisyo_form & 0x80) == 0 || (transfer & 0x100) != 0 && (keisyo_form & 0x100) == 0 || (transfer & 0x200) != 0 && (keisyo_form & 0x200) == 0 || (transfer & 0x400) != 0 && (keisyo_form & 0x400) == 0 || (transfer & 0x800) != 0 && (keisyo_form & 0x800) == 0 || (transfer & 0x1000) != 0 && (keisyo_form & 0x1000) == 0 || (transfer & 0x2000) != 0 && (keisyo_form & 0x2000) == 0 || (transfer & 0x4000) != 0 && (keisyo_form & 0x4000) == 0)
  {
    return 0;
  }
  if (transfer >= 0 || keisyo_form < 0)
    v10 = -1;
  else
    v10 = 0;
  return v10 & 1;
}

// 0x1901550
SKLID *datRemoveOfcSkl(SKLID **_sklList, void *_itemList) {
  void *v5;
  SKLID *v6;
  il2cpp_array_size_t max_length;
  s64 v8;
  s32 v9;
  SKLID *v10;
  s32 v11;
  char *v12;
  void *v13;
  char *v14;
  void *v15;
  s32 skl;
  s64 size;
  u64 *v18;
  void *items;

  v5 = Allocate(System_Collections_Generic_List_SKLID_);
  __ctor(v5);
  v6 = *sklList;
  LODWORD(max_length) = (*sklList)->max_length;
  if ((s32)max_length >= 1)
  {
    v8 = 0;
    v9 = 0;
    while (1)
    {
      v13 = Allocate(Project_dat___c__DisplayClass190_0);
      _c__DisplayClass190_0___ctor(v13, 0);
      v10 = *sklList;
      v14 = (char *)*sklList + 4 * v8;
      v11 = *((u32 *)v14 + 8);
      v13->skl = v11;
      if (*((u32 *)v14 + 8))
      {
        v15 = Allocate(System_Predicate_SklItemGuage_);
        __ctor(v15, v13, Method_Project_dat___c__DisplayClass190_0__RemoveOfcSkl_b__0__, 0);
        if (_Find(itemList, v15))
        {
          skl = v13->skl;
          size = v5->_size;
          v18 = Method_System_Collections_Generic_List_SKLID__Add__;
          ++v5->_version;
          items = v5->_items;
          if ((u32)size >= LODWORD(items->max_length))
          {
            _AddWithResize(v5, skl, *(const MethodInfo_2D92A30 **)(*(u64 *)(v18[4] + 192) + 112));
          }
          else
          {
            v5->_size = size + 1;
            *((u32 *)items + size) = skl;
          }
          goto LABEL_7;
        }
        v10 = *sklList;
        v11 = v13->skl;
      }
      v12 = (char *)v10 + 4 * v9++;
      *((u32 *)v12 + 8) = v11;
LABEL_7:
      v6 = *sklList;
      ++v8;
      max_length = (*sklList)->max_length;
      if (v8 >= (s32)max_length)
        goto LABEL_14;
    }
  }
  v9 = 0;
LABEL_14:
  if (v9 < (s32)max_length)
    sub_188E3B0(&v6[v9], 0, 4 * (u32)(max_length + ~v9) + 4);
  return (SKLID *)_ToArray(v5);
}

// 0x1901780
void datRemoveNoneSkl(SKLID **_sklList) {
  SKLID *v2;
  il2cpp_array_size_t max_length;
  s32 v4;
  s64 v5;
  s32 *m_Items;
  s32 v7;
  s32 v8;
  char *v9;

  v2 = *sklList;
  max_length = (*sklList)->max_length;
  if ((s32)max_length < 1)
  {
    v4 = 0;
  }
  else
  {
    v4 = 0;
    v5 = (u32)(*sklList)->max_length;
    m_Items = v2;
    do
    {
      v8 = *m_Items++;
      v7 = v8;
      if (v8)
      {
        v9 = (char *)v2 + 4 * v4++;
        *((u32 *)v9 + 8) = v7;
      }
      --v5;
    }
    while (v5);
  }
  if (v4 < (s32)max_length)
    sub_188E3B0(&v2[v4], 0, 4 * (u32)(~v4 + max_length) + 4);
}

// 0x19017f0
void *datRcvSklNoneIndex(sdatUnitWork_t *_unit) {
  void *haveskill;
  void *v4;
  void *_9__192_0;
  Il2CppObject *v8;
  s32 LastIndex;
  void *v11;
  s64 size;
  u64 *v14;
  s32 *items;

  haveskill = unit->haveskill;
  v4 = Allocate(System_Collections_Generic_List_SKLID_);
  __ctor_47784336(v4, haveskill);
  _9__192_0 = __9__192_0;
  if (!_9__192_0)
  {
    v8 = __9;
    _9__192_0 = Allocate(System_Predicate_SKLID_);
    __ctor(_9__192_0, v8, Method_Project_dat___c__RcvSklNoneIndex_b__192_0__, 0);
    __9__192_0 = _9__192_0;
  }
  LastIndex = _FindLastIndex(v4, _9__192_0);
  v11 = Allocate(System_Collections_Generic_List_int_);
  __ctor(v11);
  if ((LastIndex & 0x80000000) == 0)
  {
    do
    {
      if (!_get_Item(v4, LastIndex))
      {
        size = v11->_size;
        v14 = Method_System_Collections_Generic_List_int__Add__;
        ++v11->_version;
        items = v11->_items;
        if ((u32)size >= LODWORD(items->max_length))
        {
          _AddWithResize(v11, LastIndex, *(const MethodInfo_2D8F530 **)(*(u64 *)(v14[4] + 192) + 112));
        }
        else
        {
          v11->_size = size + 1;
          items[size] = LastIndex;
        }
      }
    }
    while (LastIndex-- > 0);
  }
  return v11;
}

// 0x1901a30
void datGetTmpSklDelHaveSkl(sdatUnitWork_t *_pUnit) {
  void *sklItemGuages;
  void *v4;
  SKLID **p_haveskill;
  void *haveskill;
  void *v8;
  void *v10;
  void *v12;
  void *monitor;
  s32 v14;
  s64 v15;
  void *v16;
  s32 v17;
  s32 klass;
  char *v19;
  void *v20;
  SKLID *v22;
  s64 v23;
  s32 Item;
  char *v25;
  s32 devilid;
  sdatUnitWork_t *pUnita;
  System_Collections_Generic_List_Enumerator_T__o v29;

  memset(&v29, 0, sizeof(v29));
  sklItemGuages = pUnit->sklItemGuages;
  v4 = Allocate(System_Collections_Generic_List_SklItemGuage_);
  __ctor_48217552(v4, sklItemGuages);
  pUnita = Allocate(sdatUnitWork_t);
  _ctor(pUnita);
  p_haveskill = &pUnit->haveskill;
  haveskill = pUnit->haveskill;
  v8 = Allocate(System_Collections_Generic_List_SKLID_);
  __ctor_47784336(v8, haveskill);
  v10 = datRcvSklNoneIndex(pUnit);
  datRemoveOfcSkl(&pUnit->haveskill, v4);
  v12 = pUnit->haveskill;
  monitor = v12[1].monitor;
  if ((s32)monitor < 1)
  {
    v14 = 0;
  }
  else
  {
    v14 = 0;
    v15 = (u32)v12[1].monitor;
    v16 = v12 + 2;
    do
    {
      klass = v16->klass;
      v16 = ((char *)v16 + 4);
      v17 = klass;
      if (klass)
      {
        v19 = (char *)v12 + 4 * v14++;
        *((u32 *)v19 + 8) = v17;
      }
      --v15;
    }
    while (v15);
  }
  if (v14 < (s32)monitor)
    sub_188E3B0((char *)&v12[2] + 4 * v14, 0, 4 * (u32)(~v14 + (u32)monitor) + 4);
  v20 = Allocate(System_Collections_Generic_List_SKLID_);
  __ctor_47784336(v20, v12);
  _Sort(v10);
  _GetEnumerator(&v29, v10);
  while (_MoveNext(&v29))
    _Insert(v20, (s32)v29._current, 0);
  _Dispose(&v29);
  v22 = *p_haveskill;
  if (SLODWORD((*p_haveskill)->max_length) >= 1)
  {
    v23 = 0;
    do
    {
      Item = _get_Item(v20, v23);
      v25 = (char *)v22 + 4 * v23++;
      *((u32 *)v25 + 8) = Item;
      v22 = *p_haveskill;
    }
    while (v23 < SLODWORD((*p_haveskill)->max_length));
  }
  if (!v22[0])
  {
    devilid = pUnit->devilid;
    datCreateDevilUnitEx(devilid, 0, pUnita, -1);
    (*p_haveskill)[0] = pUnita->haveskill[0];
    return;
  }
}

// 0x1901e30
void datGetTmpDelOmoideSkl(sdatUnitWork_t *_pUnit) {
  void *sklItemGuages;
  void *v4;

  sklItemGuages = pUnit->sklItemGuages;
  v4 = Allocate(System_Collections_Generic_List_SklItemGuage_);
  __ctor_48217552(v4, sklItemGuages);
  datRemoveOfcSkl(&pUnit->aOmoideSkill, v4);
}

// 0x1901ee0
s32 datCalcEnemyToNakamaID(s32 enemyID) {
  s32 result;

  result = sBtlGetDevilData(enemyID, -1)->huumaID;
  if (result)
    return result;
  if (enemyID < 0)
    return EIDtoNID(enemyID);
  result = 0;
  if ((u32)enemyID >= 0x151 && (u32)(enemyID - 476) <= 0xFFFFFFF3)
    return EIDtoNID(enemyID);
  return result;
}

// 0x1901fb0
s32 datFieldGetAutoSkillNum(s32 skillid) {
  sdatPlayerUnitWork_t *player;
  s32 v7;
  s32 StockDevilNums;
  int32x4_t v10;
  s64 v11;
  s64 v12;
  s32 mapSummonID;
  s64 v14;
  int32x4_t *v15;
  int16x8_t v16;
  int32x4_t v18;

  player = GBWK->player;
  v7 = tbl[GBWK->player->swordno]->m_hojo == skillid;
  StockDevilNums = datGetStockDevilNums(0);
  if (GBWK->mapSummonID >= 1 && StockDevilNums >= 1)
  {
    v10 = vdupq_n_s32(skillid);
    v11 = -(s64)(u32)StockDevilNums;
    v12 = 4;
    v18 = v10;
    do
    {
      mapSummonID = GBWK->mapSummonID;
      v14 = *((u64 *)&GBWK->player->stock_id->obj.klass + v12);
      if ((*(u8 *)(v14 + 16) & 1) != 0)
      {
        if (mapSummonID == *(s16 *)(v14 + 22))
        {
LABEL_18:
          v15 = *(int32x4_t **)(*((u64 *)&player->stock_id->obj.klass + v12) + 192);
          v16 = vandq_s8(vuzp1q_s16(vceqq_s32(v15[2], v18), vceqq_s32(v15[3], v18)), (int8x16_t)xmmword_3D045F0);
          v16.n128_u32[0] = (u8)vaddvq_s16(v16);
          v16.n128_u64[0] = vcnt_s8((int8x8_t)v16.n128_u64[0]).n64_u64[0];
          v16.n128_u16[0] = vaddlv_u8((uint8x8_t)v16.n128_u64[0]);
          v7 += v16.n128_u32[0];
        }
      }
      else if (!mapSummonID)
      {
        goto LABEL_18;
      }
      ++v12;
    }
    while (v11 + v12 != 4);
  }
  return v7;
}

// 0x1902260
bool datFieldChkDevilAutoSkill(s32 devilid, s32 skillid) {
  sdatPlayerUnitWork_t *player;
  s32 StockDevilNums;
  u64 v8;
  s64 v10;
  char v11;
  u64 v12;
  s64 v13;
  u32 *v14;

  player = GBWK->player;
  StockDevilNums = datGetStockDevilNums(0);
  if (StockDevilNums >= 1)
  {
    v8 = StockDevilNums;
    v10 = 4;
    v11 = 1;
    while (1)
    {
      v13 = *((u64 *)&GBWK->player->stock_id->obj.klass + v10);
      if ((*(u8 *)(v13 + 16) & 1) != 0)
      {
        if (*(s16 *)(v13 + 22) != devilid)
          goto LABEL_7;
      }
      else if (devilid)
      {
        goto LABEL_7;
      }
      v14 = *(u32 **)(*((u64 *)&player->stock_id->obj.klass + v10) + 192);
      if (v14[8] == skillid || v14[9] == skillid || v14[10] == skillid || v14[11] == skillid || v14[12] == skillid || v14[13] == skillid || v14[14] == skillid || v14[15] == skillid)
      {
        return v11;
      }
LABEL_7:
      v12 = v10 - 3;
      ++v10;
      v11 = v12 < v8;
      if (v10 - v8 == 4)
        return v11;
    }
  }
  return 0;
}

// 0x1902440
s32 datGetPlayerStance(void) {
  s32 stance;

  stance = GBWK->player->stance;
  if (stance <= -6)
    return 2;
  else
    return stance > 5;
}

// 0x19024c0
s32 datGetPlayerStanceNum(void) {
  return GBWK->player->stance;
}

// 0x1902530
static void SetPlayerStanceNum(s32 num) {
  ;
}

// 0x1902540
void datAddPlayerStance(s32 num) {
  ;
}

// 0x1902550
bool datCheckItemFull(s32 id) {
  return GBWK->player->item[id] > 98;
}

// 0x18fdae0
void datCalcMagMaxPlayerUnit(sdatPlayerUnitWork_t *pUnit) {
  sdatLvUpPlayerParamUp_t *sdatLvUpPlayerParamUp_local;
  sdatUnitWork_t *para;
  s32 level;
  s64 v7;
  s64 v8;
  s32 v9;
  s32 mag;
  s32 v14;
  s32 v15;
  s32 v16;
  s32 v17;
  sdatLvUpPlayerParamUp_t *v18;
  s64 v19;
  s64 v20;
  s64 v21;
  s64 v22;
  sdatLvUpPlayerParamUp_t *v23;
  s64 v24;
  Il2CppClass **v25;
  s64 v26;
  sdatLvUpPlayerParamUp_t *v27;
  s64 v28;
  sdatLvUpPlayerParamUp_t *v29;
  SKLID *spiritSkill;
  s64 v31;
  s32 v32;
  s32 m_hojo;
  s32 v34;
  s32 v35;
  s16 para2[2];
  s16 para1[2];

  para1[0] = 0;
  para2[0] = 0;
  sdatLvUpPlayerParamUp_local = sdatLvUpPlayerParamUp;
  if (!sdatLvUpPlayerParamUp_local)
  {
    v9 = 0;
    mag = pUnit->mag;
    pUnit->maxmag = 0;
    if (mag <= 0)
      return;
    goto LABEL_45;
  }
  para = pUnit->para;
  level = para->level;
  if (level < 0)
  {
    v9 = 0;
    goto LABEL_26;
  }
  v7 = (u8)para->level + 1;
  if ((u8)level >= 3u)
  {
    v8 = (u8)v7 & 0xFC;
    v14 = 0;
    v15 = 0;
    v16 = 0;
    v17 = 0;
    v18 = &sdatLvUpPlayerParamUp_local[3];
    v19 = v8;
    do
    {
      v20 = *(v18 - 3);
      v21 = *(v18 - 2);
      v19 -= 4;
      v22 = *(v18 - 1);
      v23 = v18;
      v18 += 4;
      v14 += *(s16 *)(v20 + 16);
      v15 += *(s16 *)(v21 + 16);
      v16 += *(s16 *)(v22 + 16);
      v17 += v23->UpValMag;
    }
    while (v19);
    v9 = v17 + v16 + v15 + v14;
    if (v8 == v7)
      goto LABEL_26;
  }
  else
  {
    v8 = 0;
    v9 = 0;
  }
  v24 = ~v8;
  if ((v7 & 1) != 0)
  {
    v25 = &sdatLvUpPlayerParamUp_local->obj.klass + v8;
    v8 |= 1u;
    v9 += SLOWORD(v25[4]->_1.name);
  }
  if (v24 + v7)
  {
    v26 = v7 - v8;
    v27 = &sdatLvUpPlayerParamUp_local[v8 + 1];
    do
    {
      v28 = *(v27 - 1);
      v29 = v27;
      v26 -= 2;
      v27 += 2;
      v9 += *(s16 *)(v28 + 16) + v29->UpValMag;
    }
    while (v26);
  }
LABEL_26:
  spiritSkill = pUnit->spiritSkill;
  if (SLODWORD(spiritSkill->max_length) >= 1)
  {
    v31 = 0;
    do
    {
      v32 = spiritSkill[v31];
      if (sBtlGetAutoSkillPara(v32, para1, para2) == 64)
        v9 = v9 * para2[0] / 100;
      spiritSkill = pUnit->spiritSkill;
      ++v31;
    }
    while (v31 < SLODWORD(spiritSkill->max_length));
  }
  m_hojo = tbl[pUnit->swordno]->m_hojo;
  if (sBtlGetAutoSkillPara(m_hojo, para1, para2) == 67)
  {
    v9 = 110 * v9 / 100;
    if (v9 <= 300)
    {
LABEL_41:
      v34 = pUnit->mag;
      pUnit->maxmag = v9;
      if (v34 <= v9)
        return;
LABEL_45:
      pUnit->mag = v9;
      return;
    }
  }
  else if (v9 <= 300)
  {
    goto LABEL_41;
  }
  v9 = 300;
  v35 = pUnit->mag;
  pUnit->maxmag = 300;
  if (v35 > 300)
    goto LABEL_45;
}

// 0x18fcec0
void datCalcMagMax(void) {
  sdatPlayerUnitWork_t *player;

  player = GBWK->player;
  datCalcMagMaxPlayerUnit(player);
}

// 0x19025d0
s32 datCommand_GET_DEVIL_NUMS(void) {
  s32 StockDevilNums;

  StockDevilNums = datGetStockDevilNums(0);
  scrSetIntReturnValue(StockDevilNums);
  return 1;
}

// 0x1902690
s32 datCommand_GET_DEVIL_ID(void) {
  s32 IntPara;
  sdatUnitWork_t *v3;
  sdatUnitWork_t *v6;

  IntPara = scrGetIntPara(0);
  v3 = GBWK->player->stock_id[IntPara];
  if ((v3->flag & 1) != 0)
  {
    scrSetIntReturnValue(v3->devilid);
    goto LABEL_13;
  }
  scrSetIntReturnValue(0);
LABEL_13:
  v6 = GBWK->player->stock_id[IntPara];
  if ((v6->flag & 1) != 0)
    select_dvl_uniq = v6->uniq_code;
  else
    select_dvl_uniq = 0;
  return 1;
}

// 0x1902830
s32 datCommand_GET_LIVE_DEVIL_NUMS(void) {
  s64 v3;
  s32 v4;
  s64 v5;

  v3 = 0;
  v4 = 0;
  while (1)
  {
    if (v3 >= datGetStockDevilNums(0))
      break;
    v5 = (s64)GBWK->player->stock_id + 8 * v3++;
    if (*(s32 *)(*(u64 *)(*(u64 *)(v5 + 32) + 40) + 16) > 0)
      ++v4;
  }
  scrSetIntReturnValue(v4);
  return 1;
}

// 0x1902920
s32 datCommand_GET_LIVE_DEVIL_ID(void) {
  s32 IntPara;
  s32 v4;
  s32 v5;
  s64 i;
  s32 v7;
  s64 v8;
  s64 v10;
  s32 v11;

  IntPara = scrGetIntPara(0);
  v4 = 0;
  v5 = 0;
  for (i = 4; ; ++i)
  {
    if (i - 4 >= datGetStockDevilNums(0))
      break;
    if (*(s32 *)(*(u64 *)(*((u64 *)&GBWK->player->stock_id->obj.klass + i) + 40) + 16) < 1)
    {
      v7 = v5;
      goto LABEL_7;
    }
    v7 = v5 + 1;
    if (v5 == IntPara)
    {
      v8 = *((u64 *)&GBWK->player->stock_id->obj.klass + i);
      if ((*(u8 *)(v8 + 16) & 1) != 0)
      {
        v4 = *(s16 *)(v8 + 22);
      }
      else
      {
        v4 = 0;
        goto LABEL_23;
      }
LABEL_23:
      v10 = *((u64 *)&GBWK->player->stock_id->obj.klass + i);
      if ((*(u8 *)(v10 + 16) & 1) != 0)
        v11 = *(u32 *)(v10 + 280);
      else
        v11 = 0;
      select_dvl_uniq = v11;
    }
LABEL_7:
    v5 = v7;
  }
  scrSetIntReturnValue(v4);
  return 1;
}

// 0x1902b40
s32 datCommand_CHK_DEVIL_SKILL(void) {
  s64 v1;
  s32 v2;
  s32 IntPara;
  sdatUnitWork_t *v6;
  s32 v7;
  SKLID *haveskill;

  v1 = 0;
  v2 = 0;
  IntPara = scrGetIntPara(0);
  while (1)
  {
    if (v1 >= datGetStockDevilNums(0))
      break;
    if (IntPara == (u32)v1)
    {
      v6 = GBWK->player->stock_id[v1];
      v2 = 1;
      v7 = scrGetIntPara(1);
      haveskill = v6->haveskill;
      if (haveskill[0] != v7 && haveskill[1] != v7 && haveskill[2] != v7 && haveskill[3] != v7 && haveskill[4] != v7 && haveskill[5] != v7 && haveskill[6] != v7 && haveskill[7] != v7 && haveskill[8] != v7 && haveskill[9] != v7 && haveskill[10] != v7 && haveskill[11] != v7 && haveskill[12] != v7 && haveskill[13] != v7 && haveskill[14] != v7 && haveskill[15] != v7)
      {
        v2 = haveskill[16] == v7;
      }
    }
    ++v1;
  }
  scrSetIntReturnValue(v2);
  return 1;
}

// 0x1902d40
s32 datCommand_DEVIL_IN(void) {
  s32 IntPara;
  u32 v4;

  IntPara = scrGetIntPara(0);
  v4 = datAddDevilEx(IntPara, 0);
  if (sbattleIsBattle())
  {
    sBtlEntryStockData(IntPara);
    goto LABEL_21;
  }
  if ((v4 & 0x80000000) == 0)
  {
    gohKarteRegistDevil(GBWK->player->stock_id[v4], GBWK->karte_list, 1, 1, 0, 0);
  }
LABEL_21:
  scrSetIntReturnValue(v4);
  return 1;
}

// 0x1902f20
s32 datCommand_DEVIL_OUT(void) {
  s32 IntPara;
  s32 v3;

  IntPara = scrGetIntPara(0);
  v3 = datDelDevil(IntPara, 0);
  scrSetIntReturnValue(v3 >= 0);
  return 1;
}

// 0x1902fe0
s32 datCommand_STOCK_DEVIL_OUT(void) {
  s32 IntPara;
  s32 v3;
  sdatUnitWork_t *v6;
  u32 uniq_code;
  s32 v8;

  IntPara = scrGetIntPara(0);
  v3 = scrGetIntPara(1);
  v6 = GBWK->player->stock_id[v3];
  if ((v6->flag & 1) != 0)
    uniq_code = v6->uniq_code;
  else
    uniq_code = 0;
  select_dvl_uniq = uniq_code;
  v8 = datDelDevil(IntPara, uniq_code);
  scrSetIntReturnValue(v8 >= 0);
  return 1;
}

// 0x1903140
s32 datCommand_DEVIL_OUT_AFTER(void) {
  s32 IntPara;
  struct dat *v5;
  s32 AfterOutDevilID;
  s32 v11;
  s32 v15;

  IntPara = scrGetIntPara(0);
  if (!IntPara)
  {
    AfterOutDevilID = GBWK->AfterOutDevilID;
    if (AfterOutDevilID)
    {
      v11 = datDelDevil(AfterOutDevilID, select_dvl_uniq);
LABEL_16:
      GBWK->AfterOutDevilID = 0;
      mapEiseiTaiituClear();
      if ((v11 & 0x80000000) == 0)
        goto LABEL_18;
      v15 = 0;
      goto LABEL_20;
    }
    v11 = -1;
    goto LABEL_16;
  }
  GBWK->AfterOutDevilID = IntPara;
  if (!(u32)v5)
  mapEiseiTaiituSet(IntPara, select_dvl_uniq);
LABEL_18:
  v15 = 1;
LABEL_20:
  scrSetIntReturnValue(v15);
  return 1;
}

// 0x1903310
s32 datCommand_GET_STOCK_MAX(void) {
  s32 stock_max;

  stock_max = GBWK->player->stock_max;
  scrSetIntReturnValue(stock_max);
  return 1;
}

// 0x19033b0
s32 datCommand_GET_INC_STOCK(void) {
  return 1;
}

// 0x19033c0
s32 datCommand_INC_STOCK(void) {
  char IntPara;
  sdatPlayerUnitWork_t *player;
  s32 v4;

  IntPara = scrGetIntPara(0);
  player = GBWK->player;
  v4 = (char)(player->stock_max + IntPara);
  player->stock_max += IntPara;
  if (v4 >= 33)
  {
    player = GBWK->player;
    player->stock_max = 32;
  }
  return 1;
}

// 0x19034f0
s32 datCommand_DEBT_FROM_GOUTO(void) {
  s32 IntPara;
  s32 v3;

  IntPara = scrGetIntPara(0);
  v3 = datDebtFromGouto(IntPara);
  scrSetIntReturnValue(v3);
  return 1;
}

// 0x1903590
s32 datCommand_GET_SUMMONERRANK_NUM(void) {
  s32 SummonerRankNum;

  SummonerRankNum = datGetSummonerRankNum();
  scrSetIntReturnValue(SummonerRankNum);
  return 1;
}

// 0x1903650
static dds3ProcessFunc_t dds3GlobalWorkMainProc(dds3ProcessID_t *procID) {
  f64 totalPlayTime;

  *(int32x2_t *)&GBWK->runtime = vadd_s32(*(int32x2_t *)&GBWK->runtime, (int32x2_t)0x100000001LL);
  if (PauseSign)
    return 0;
  if (!firstFrame)
    return 0;
  totalPlayTime = GBWK->totalPlayTime;
  GBWK->totalPlayTime = totalPlayTime + _ElapsedTime_k__BackingField;
  return 0;
}

// 0x19038b0
static void UserInit(void) {
  cfgInitGlobalWork();
  scrInitGlobalWork();
  evtInitGlobalWork();
  datInitPlayer();
  fldGbInit_System(0);
  datLoadLevelUpTable();
  datLoadGohmadenTable();
  gohInitGlobalWorkKarte();
  sBtlLoadOnMemMsg();
  datLoadCampStausTable();
  datLoadTable();
  Clear(0);
  CmpClear();
}

// 0x1903a70
static void UserDestroy(void) {
  ;
}

// 0x1903a80
void datGlobalWorkInit(void) {
  dds3ProcessFunc_t v2;
  dds3ProcessID_t *started;

  GlobalWorkNewGame();
  v2 = Allocate(dds3ProcessFunc_t);
  _ctor(v2, 0, Method_Project_dat_dds3GlobalWorkMainProc__, 0);
  started = dds3StartProcess("GBWK", 1, 0, 0, v2, 0, GBWK);
  UserInit();
}

// 0x1903b90
static void GlobalWorkNewGame(void) {
  dds3GlobalWork_t *v1;
  dds3GlobalWork_t *p_GBWK;
  dds3GlobalWork_t *GBWK_local;

  v1 = Allocate(dds3GlobalWork_t);
  _ctor(v1);
  p_GBWK = &GBWK;
  p_GBWK = v1;
  GBWK_local = GBWK;
  *(u64 *)&GBWK_local->runtime = 0;
  GBWK_local->totalPlayTime = 0.0;
}

// 0x1903c40
void datGlobalWorkDestroy(void) {
  dds3GlobalWork_t *p_GBWK;

  dds3KillProcessName("GBWK", 0);
  p_GBWK = &GBWK;
  p_GBWK = 0;
}

// 0x1903d00
static NewGame2_t *NewGame2Push(void) {
  NewGame2_t *v1;
  bool v2;
  s64 v3;
  s64 v4;
  bool v5;
  s64 v6;
  s64 v7;
  s64 v8;
  bool v9;
  s64 v10;
  s64 v11;
  s64 v12;
  bool v13;
  s64 v14;
  s64 v15;
  s64 v16;
  bool v17;
  s64 v18;
  shpSave_t *shpSave;
  u32 playtime;
  sdatPlayerUnitWork_t *player;
  s32 stock_max;
  s32 syougou;
  s64 v26;
  s64 v27;
  bool *dbook_readFlag;
  s32 *dbook_updateFlag;
  s64 v30;
  s64 v31;
  bool v32;
  s64 v33;
  dds3GlobalWork_t *v35;
  bool *quest_clearSave;
  gohSwordHistory_t *v37;

  v1 = Allocate(NewGame2_t);
  _ctor(v1, 0);
  v1->SYS_ENDING0 = evtBitCheck(2960);
  v1->SYS_SYS_HARD_ON = evtBitCheck(2961);
  v1->SYS_ZIM_MAHJON_ON = evtBitCheck(2352);
  v2 = evtBitCheck(2353);
  v3 = v1->SYS_RANK;
  v1->SYS_KON_HANAFU_ON = v2;
  if (*(s32 *)(v3 + 24) >= 1)
  {
    v4 = 32;
    do
    {
      v5 = evtBitCheck(v4 + 2032);
      v6 = v4 - 31;
      *(u8 *)(v3 + v4) = v5;
      v3 = v1->SYS_RANK;
      ++v4;
    }
    while (v6 < *(s32 *)(v3 + 24));
  }
  v7 = v1->SYS_RANK2;
  if (*(s32 *)(v7 + 24) >= 1)
  {
    v8 = 32;
    do
    {
      v9 = evtBitCheck(v8 + 2448);
      v10 = v8 - 31;
      *(u8 *)(v7 + v8) = v9;
      v7 = v1->SYS_RANK2;
      ++v8;
    }
    while (v10 < *(s32 *)(v7 + 24));
  }
  v11 = v1->SYS_GOU_ITIMOK_ON;
  if (*(s32 *)(v11 + 24) >= 1)
  {
    v12 = 32;
    do
    {
      v13 = evtBitCheck(v12 + 2294);
      v14 = v12 - 31;
      *(u8 *)(v11 + v12) = v13;
      v11 = v1->SYS_GOU_ITIMOK_ON;
      ++v12;
    }
    while (v14 < *(s32 *)(v11 + 24));
  }
  v15 = v1->SYS_GOU_HAYATARO_ON;
  if (*(s32 *)(v15 + 24) >= 1)
  {
    v16 = 32;
    do
    {
      v17 = evtBitCheck(v16 + 2656);
      v18 = v16 - 31;
      *(u8 *)(v15 + v16) = v17;
      v15 = v1->SYS_GOU_HAYATARO_ON;
      ++v16;
    }
    while (v18 < *(s32 *)(v15 + 24));
  }
  shpSave = GBWK->shpSave;
  playtime = GBWK->playtime;
  LOWORD(GBWK) = GBWK->GameFileInfo->endcnt;
  v1->playtime = playtime;
  v1->endcnt = (u16)GBWK;
  v1->shpSave = shpSave;
  player = GBWK->player;
  stock_max = player->stock_max;
  v1->total_cyuusei = (u16)player->para->chuusei
                       | ((u16)player->para->chuusei_high << 16);
  v1->stock_max = stock_max;
  syougou = player->syougou;
  LOBYTE(player) = player->setSyougou;
  v1->maxmag = 100;
  v1->syougou = syougou;
  v1->setSyougou = (u8)player;
  gohKarteBackupAll();
  v26 = v1->RankTips;
  *(u8 *)(v26 + 32) = evtBitCheck(10022);
  v27 = v1->RankTips;
  *(u8 *)(v27 + 33) = evtBitCheck(10008);
  dbook_readFlag = GBWK->dbook_readFlag;
  v1->dbook_readFlag = dbook_readFlag;
  dbook_updateFlag = GBWK->dbook_updateFlag;
  v1->dbook_updateFlag = dbook_updateFlag;
  v30 = v1->dbook_OpenFlag;
  if (*(s32 *)(v30 + 24) >= 1)
  {
    v31 = 0;
    do
    {
      v32 = evtBitCheck(v31 + 0x2000);
      v33 = v30 + v31;
      v30 = v1->dbook_OpenFlag;
      *(u8 *)(v33 + 32) = v32;
      ++v31;
    }
    while (v31 < *(s32 *)(v30 + 24));
  }
  v35 = GBWK;
  quest_clearSave = v35->quest_clearSave;
  v1->totalPlayTime = v35->totalPlayTime;
  v1->quest_clearSave = quest_clearSave;
  v37 = Allocate(gohSwordHistory_t);
  _ctor(v37, 0);
  v1->SwordHistory = v37;
  Transfer(v1->SwordHistory, GBWK->SwordHistory, 0);
  ClassCopy(v1->player, GBWK->player);
  return v1;
}

// 0x19040b0
static void NewGame2Pop(NewGame2_t *NewGame2) {
  s32 *EventBit;
  s32 *v6;
  s32 *v8;
  s32 *v10;
  bool *SYS_RANK;
  s64 v12;
  s32 v14;
  s64 v15;
  bool *SYS_RANK2;
  s64 v17;
  s32 v19;
  s64 v20;
  bool *SYS_GOU_ITIMOK_ON;
  s64 v22;
  s32 v24;
  s64 v25;
  bool *SYS_GOU_HAYATARO_ON;
  s64 v27;
  s32 v28;
  s64 v29;
  shpSave_t *shpSave;
  u16 endcnt;
  dds3GlobalWork_t *GBWK_local;
  s32 maxmag;
  s32 syougou;
  sdatPlayerUnitWork_t *player;
  bool setSyougou;
  bool *RankTips;
  s32 *v42;
  s32 *v44;
  bool *dbook_readFlag;
  bool **p_dbook_readFlag;
  s32 *dbook_updateFlag;
  s32 **p_dbook_updateFlag;
  bool *dbook_OpenFlag;
  s64 v50;
  s32 v51;
  s64 v52;
  f64 totalPlayTime;
  dds3GlobalWork_t *v56;
  bool *quest_clearSave;
  GameFileInfo_t *GameFileInfo;
  s32 v59;
  sdatUnitWork_t *para;
  sdatParaWork_t *now;
  sdatParaWork_t *pitem;
  s64 v69;
  sdatUnitWork_t *v71;
  sdatUnitWork_t *v72;
  dds3GlobalWork_t *v76;
  s64 v80;
  s32 v84;
  sdatPlayerUnitWork_t *v85;
  s32 SkillSpiritSkillNo;
  s8 *spiritMaster;
  s64 v88;
  u32 v89;
  s32 v90;
  s64 i;
  u32 v92;
  sdatPlayerUnitWork_t *v96;
  s32 RaidouSkillNo;
  s8 *raidouSkillMaster;
  s64 v100;
  u32 v101;
  s32 v102;
  s64 v105;
  s64 v106;
  s32 *v110;

  if (NewGame2->SYS_ENDING0)
  {
    EventBit = GBWK->EventBit;
    EventBit[92] |= 0x10000u;
    goto LABEL_7;
  }
LABEL_7:
  if (NewGame2->SYS_SYS_HARD_ON)
  {
    v6 = GBWK->EventBit;
    v6[92] |= 0x20000u;
  }
  if (NewGame2->SYS_ZIM_MAHJON_ON)
  {
    v8 = GBWK->EventBit;
    v8[73] |= 0x10000u;
  }
  if (NewGame2->SYS_KON_HANAFU_ON)
  {
    v10 = GBWK->EventBit;
    v10[73] |= 0x20000u;
  }
  SYS_RANK = NewGame2->SYS_RANK;
  if (SLODWORD(SYS_RANK->max_length) >= 1)
  {
    v12 = 0;
    while (!SYS_RANK[v12])
    {
LABEL_26:
      SYS_RANK = NewGame2->SYS_RANK;
      if (++v12 >= SLODWORD(SYS_RANK->max_length))
        goto LABEL_33;
    }
    if ((u32)(v12 - 554) >= 0xFFFFFFC6)
      goto LABEL_32;
    goto LABEL_9000;
    if ((u32)(v12 - 554) >= 0xFFFFFFC6)
LABEL_32:
      evtBitKityouItemAdd(v12 + 2064);
LABEL_9000:
    v14 = v12 + 2095;
    if ((s32)v12 + 2064 >= 0)
      v14 = v12 + 2064;
    v15 = (s64)GBWK->EventBit + 4 * (v14 >> 5);
    *(u32 *)(v15 + 32) |= 1 << (v12 + 16);
    goto LABEL_26;
  }
LABEL_33:
  SYS_RANK2 = NewGame2->SYS_RANK2;
  if (SLODWORD(SYS_RANK2->max_length) >= 1)
  {
    v17 = 0;
    while (!SYS_RANK2[v17])
    {
LABEL_40:
      SYS_RANK2 = NewGame2->SYS_RANK2;
      if (++v17 >= SLODWORD(SYS_RANK2->max_length))
        goto LABEL_47;
    }
    if ((u32)(v17 - 138) >= 0xFFFFFFC6)
      goto LABEL_46;
    goto LABEL_9001;
    if ((u32)(v17 - 138) >= 0xFFFFFFC6)
LABEL_46:
      evtBitKityouItemAdd(v17 + 2480);
LABEL_9001:
    v19 = v17 + 2511;
    if ((s32)v17 + 2480 >= 0)
      v19 = v17 + 2480;
    v20 = (s64)GBWK->EventBit + 4 * (v19 >> 5);
    *(u32 *)(v20 + 32) |= 1 << (v17 - 80);
    goto LABEL_40;
  }
LABEL_47:
  SYS_GOU_ITIMOK_ON = NewGame2->SYS_GOU_ITIMOK_ON;
  if (SLODWORD(SYS_GOU_ITIMOK_ON->max_length) >= 1)
  {
    v22 = 0;
    while (!SYS_GOU_ITIMOK_ON[v22])
    {
LABEL_54:
      SYS_GOU_ITIMOK_ON = NewGame2->SYS_GOU_ITIMOK_ON;
      if (++v22 >= SLODWORD(SYS_GOU_ITIMOK_ON->max_length))
        goto LABEL_61;
    }
    if ((u32)(v22 - 292) >= 0xFFFFFFC6)
      goto LABEL_60;
    goto LABEL_9002;
    if ((u32)(v22 - 292) >= 0xFFFFFFC6)
LABEL_60:
      evtBitKityouItemAdd(v22 + 2326);
LABEL_9002:
    v24 = v22 + 2357;
    if ((s32)v22 + 2326 >= 0)
      v24 = v22 + 2326;
    v25 = (s64)GBWK->EventBit + 4 * (v24 >> 5);
    *(u32 *)(v25 + 32) |= 1 << (v22 + 22);
    goto LABEL_54;
  }
LABEL_61:
  SYS_GOU_HAYATARO_ON = NewGame2->SYS_GOU_HAYATARO_ON;
  if (SLODWORD(SYS_GOU_HAYATARO_ON->max_length) >= 1)
  {
    v27 = 0;
    while (!SYS_GOU_HAYATARO_ON[v27])
    {
LABEL_66:
      SYS_GOU_HAYATARO_ON = NewGame2->SYS_GOU_HAYATARO_ON;
      if (++v27 >= SLODWORD(SYS_GOU_HAYATARO_ON->max_length))
        goto LABEL_73;
    }
    v28 = v27 + 2688;
    if ((s32)v27 + 2688 < 0)
      v28 = v27 + 2719;
    v29 = (s64)GBWK->EventBit + 4 * (v28 >> 5);
    *(u32 *)(v29 + 32) |= 1 << v27;
    goto LABEL_66;
  }
LABEL_73:
  shpSave = NewGame2->shpSave;
  endcnt = NewGame2->endcnt;
  GBWK_local = GBWK;
  GBWK_local->shpSave = shpSave;
  GBWK_local = ((char *)GBWK_local + 144);
  *(u16 *)(*(u64 *)&GBWK_local[-1].CamKakudo + 36) = endcnt;
  HIDWORD(GBWK_local[-1].saveCutID) = NewGame2->playtime;
  datAddTotalCyuusei(GBWK->player->para, NewGame2->total_cyuusei);
  maxmag = NewGame2->maxmag;
  syougou = NewGame2->syougou;
  player = GBWK->player;
  player->stock_max = LOBYTE(NewGame2->stock_max) - 2;
  setSyougou = NewGame2->setSyougou;
  player->maxmag = maxmag;
  player->syougou = syougou;
  player->setSyougou = setSyougou;
  gohKarteRestoreAll();
  RankTips = NewGame2->RankTips;
  if (RankTips[0])
  {
    v42 = GBWK->EventBit;
    v42[313] |= 0x40u;
    RankTips = NewGame2->RankTips;
    goto LABEL_79;
  }
LABEL_79:
  if (RankTips[1])
  {
    v44 = GBWK->EventBit;
    v44[312] |= 0x1000000u;
    goto LABEL_84;
  }
LABEL_84:
  dbook_readFlag = NewGame2->dbook_readFlag;
  p_dbook_readFlag = &GBWK->dbook_readFlag;
  *p_dbook_readFlag = dbook_readFlag;
  dbook_updateFlag = NewGame2->dbook_updateFlag;
  p_dbook_updateFlag = &GBWK->dbook_updateFlag;
  *p_dbook_updateFlag = dbook_updateFlag;
  dbook_OpenFlag = NewGame2->dbook_OpenFlag;
  if (SLODWORD(dbook_OpenFlag->max_length) >= 1)
  {
    v50 = 0;
    while (!dbook_OpenFlag[v50])
    {
LABEL_89:
      dbook_OpenFlag = NewGame2->dbook_OpenFlag;
      if (++v50 >= SLODWORD(dbook_OpenFlag->max_length))
        goto LABEL_96;
    }
    v51 = v50 + 0x2000;
    if ((s32)v50 + 0x2000 < 0)
      v51 = v50 + 8223;
    v52 = (s64)GBWK->EventBit + 4 * (v51 >> 5);
    *(u32 *)(v52 + 32) |= 1 << v50;
    goto LABEL_89;
  }
LABEL_96:
  totalPlayTime = NewGame2->totalPlayTime;
  v56 = GBWK;
  quest_clearSave = NewGame2->quest_clearSave;
  GameFileInfo = v56->GameFileInfo;
  v56->totalPlayTime = totalPlayTime;
  v56->quest_clearSave = quest_clearSave;
  v59 = (totalPlayTime * 60.0);
  if (totalPlayTime * 60.0 >= 0.0)
    v59 = (u32)(totalPlayTime * 60.0);
  GameFileInfo->PlayTime = v59;
  Transfer(GBWK->SwordHistory, NewGame2->SwordHistory, 0);
  if (handover_type)
  {
    goto LABEL_105;
  }
  ClassCopy(GBWK->player->para, NewGame2->player->para);
  para = GBWK->player->para;
  now = para->now;
  pitem = para->pitem;
  v69 = *(u64 *)&pitem->str;
  now->hp = now->maxhp;
  *(u64 *)&pitem->hp = 0;
  *(u64 *)&pitem->mp = 0;
  *(u64 *)&pitem->str = v69 & 0xFF00FF00FF00FFLL;
  v71 = GBWK->player->para;
  sBtlCheckItemCount(v71);
  GBWK->player->swordno = NewGame2->player->swordno;
  datSetPlayerUnitSword(GBWK->player, 1, v72);
  v76 = GBWK;
  v76->stat &= 0xFFFFFFCC;
  v76->player->para->itemstatus &= 0xFFFFFF9F;
  GBWK->EventBit[65] |= 0x1000000u;
LABEL_105:
  if (handover_type)
  {
    if (handover_type != 1)
      return;
  }
  v80 = 0;
  *(u64 *)&GBWK->player->gold = *(u64 *)&NewGame2->player->gold;
  while (1)
  {
    if (v80 >= SLODWORD(spiritList->max_length))
      break;
    v84 = spiritList[v80];
    if (v84 == 1452)
      goto LABEL_155;
    v85 = NewGame2->player;
    if (v84 == 1024)
      goto LABEL_152;
    SkillSpiritSkillNo = gohGetSkillSpiritSkillNo(v84);
    spiritMaster = v85->spiritMaster;
    v88 = (u32)SkillSpiritSkillNo >> 3;
    if (SLODWORD(spiritMaster->max_length) > v88)
    {
      v89 = spiritMaster[v88];
      if (SkillSpiritSkillNo <= 0)
        v90 = -(-SkillSpiritSkillNo & 7);
      else
        LOBYTE(v90) = SkillSpiritSkillNo & 7;
      if (((v89 >> v90) & 1) != 0)
      {
LABEL_152:
        SpiritSkillSetMaster(GBWK->player, v84, 1);
      }
    }
LABEL_155:
    ++v80;
  }
  for (i = 0; ; ++i)
  {
    if (i >= SLODWORD(raidouSkillList->max_length))
      break;
    v92 = raidouSkillList[i];
    if (v92 > 0x37 || ((1 << v92) & 0x80008000800100LL) == 0)
    {
      v96 = NewGame2->player;
      RaidouSkillNo = gohGetRaidouSkillNo(v92);
      raidouSkillMaster = v96->raidouSkillMaster;
      v100 = (u32)RaidouSkillNo >> 3;
      if (SLODWORD(raidouSkillMaster->max_length) > v100)
      {
        v101 = raidouSkillMaster[v100];
        if (RaidouSkillNo <= 0)
          v102 = -(-RaidouSkillNo & 7);
        else
          LOBYTE(v102) = RaidouSkillNo & 7;
        if (((v101 >> v102) & 1) != 0)
        {
          datRaidouSkillSetMaster(GBWK->player, v92, 1);
        }
      }
    }
  }
  if ((s32)GBWK->player->item->max_length >= 2)
  {
    v105 = 0;
    v106 = (u32)GBWK->player->item->max_length - 1;
    do
    {
      if ((tbldata[v105 + 1]->type & 0x40) == 0 && ((u32)(v105 + 1) > 0x27 || ((1 << ((u8)v105 + 1)) & 0x9000000200LL) == 0))
      {
        if ((tbldata[v105 + 1]->type & 0x400) != 0)
        {
          if (v105 != 195)
          {
            GBWK->player->item[v105 + 1] = NewGame2->player->item[v105 + 1];
            if (v105 == 144)
            {
              datAddItem(145, 1);
            }
          }
        }
        else
        {
          GBWK->player->item[v105 + 1] = NewGame2->player->item[v105 + 1];
        }
      }
      ++v105;
    }
    while (v106 != v105);
  }
  v110 = GBWK->EventBit;
  v110[65] |= 0x800000u;
}

// 0x1905020
void datGlobalWorkUserInit2(s32 mode) {
  NewGame2_t *v4;

  if (!mode)
  {
    v4 = 0;
    goto LABEL_7;
  }
  v4 = NewGame2Push();
LABEL_7:
  GlobalWorkNewGame();
  cfgInitSbtlShortCut();
  scrInitGlobalWork();
  evtInitGlobalWork();
  datInitPlayer();
  fldGbInit_System(0);
  gohInitGlobalWorkKarte();
  Clear(0);
  CmpClear();
  gohDlcKarteReg();
  if (mode)
  {
    NewGame2Pop(v4);
  }
}
