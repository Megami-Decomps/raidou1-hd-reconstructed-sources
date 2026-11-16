#include "types.h"
#include "CMP_MENU_ID.h"
#include "ITM.h"
#include "PanelFocus.h"
#include "SKLID.h"
#include "SklItmRst.h"
#include "buttonguide.h"
#include "cmpfile.h"
#include "cmpitem.h"
#include "cmpkuda.h"
#include "cmpmain.h"
#include "cmpomoide.h"
#include "cmpstatus.h"
#include "cmpstatusitmsklset.h"
#include "dat.h"
#include "dds3_pad.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "ditectivebook.h"
#include "evtbit.h"
#include "fclmsg.h"
#include "fld.h"
#include "itf.h"
#include "localize.h"
#include "raijindlc.h"
#include "rstgrowth.h"
#include "sbattle.h"
#include "sbtl.h"
#include "sbtlitem.h"
#include "sbtlskill.h"
#include "sbtlweapon.h"
#include "scr.h"
#include "sdat.h"
#include "tips.h"

#define RST_JUMP_FRAME 40
#define KUDA_PARAM_MAX 8
#define ATRB_PARAM_MAX 11

typedef enum {
    UseUpdateStep_Selsct = 0,
    UseUpdateStep_Char = 1,
    UseUpdateStep_SelBack = 3,
    UseUpdateStep_EffEnd = 9,
    UseUpdateStep_Special = 10,
    UseUpdateStep_SklSet = 11,
    UseUpdateStep_CallRst = 12,
    UseUpdateStep_RstChk = 13,
    UseUpdateStep_RstEnd = 14,
    UseUpdateStep_TabChg = 15,
    UseUpdateStep_Tips = 16,
} UseUpdateStep;

typedef enum {
    ItemMenuBufType_Use = 0,
    ItemMenuBufType_Check = 1,
    ItemMenuBufType_Material = 2,
    ItemMenuBufType_Sword = 3,
    ItemMenuBufType_Max = 4,
} ItemMenuBufType;

typedef enum {
    CMP_USE_SCR_SYUMAMIZ = 0,
    CMP_USE_SCR_TAIMAMIZ = 1,
    CMP_USE_SCR_NEKOZYAR = 2,
    CMP_USE_SCR_TETYOU__ = 13,
    CMP_USE_SCR_ROIDOU = 14,
    CMP_USE_SCR_SEIKATU = 15,
} CMP_USE_SCR;

typedef struct CmpSklItem_t CmpSklItem_t;
typedef struct EvtItemCutInSpr EvtItemCutInSpr;
typedef struct ItemMenuData ItemMenuData;
typedef struct ItemUpdateManager ItemUpdateManager;
typedef struct SklItemCoefficient_t SklItemCoefficient_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct sdatPlayerUnitWork_t sdatPlayerUnitWork_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;
typedef struct sprHandle_t sprHandle_t;

typedef bool (*cmpItemFunc_t)(void);

struct CmpSklItem_t {
    char *name;
    SKLID sklID;
    s32 param[8];
};

struct SklItemCoefficient_t {
    char *name;
    s32 devilID;
    f32 coefficient[11];
};

EvtItemCutInSpr *cutInOnTbl[21];
static char *cmpAssetName;
dds3ProcessID_t *g_listPID;
dds3ProcessID_t *g_charPID;
dds3ProcessID_t *g_stockPID;
dds3ProcessID_t *g_activePID;
s8 g_step;
s8 g_count;
bool g_setSaveCsr;
s32 g_itemNo;
s32 g_charNo;
PanelFocus g_panel;
CMP_MENU_ID g_menuID;
u16 *g_arrItemID;
s32 g_itemNum;
s32 g_equipNo;
u8 *g_pDatScr;
s32 g_scrReq;
dds3ProcessID_t *g_scrPID;
bool g_bEnd;
sprHandle_t *g_hSpr;
sdatPlayerUnitWork_t *selDrawPlayer;
sdatUnitWork_t *selDrawDevil;
ItemUpdateManager *itmUpdateMg;
bool openInfo;
void *sklItemConvTbl;
void *sklItemCntTbl;
void *sklItmCoefficientTbl;
SklItmRst sklItmRst;
s32 g_oldSwordSelNo;
ItemMenuData *itmMenuData;
bool useNekozyar;
bool useSpItem;
static cmpItemFunc_t *cmpItemFunc;
static s32 *arrUseItemMessage;
s32 *s_arrSortItemID;

// 0x1e5b330
bool cmpDrawHelp(void) {
  s32 v7;
  char *v8;

  if (g_step != 1)
    goto LABEL_26;
  if (tbldata[g_itemNo]->type != 0x2000)
    goto LABEL_26;
  LODWORD(g_itemNo) = g_itemNo;
  if (get_Item(sklItemConvTbl, g_itemNo, 0))
  {
    get_Item(sklItemConvTbl, g_itemNo, 0);
  }
  v7 = g_itemNo;
  v8 = sdatItemName(v7);
  frSetVariableRequest(0, v8);
  ButtonLineHelpTextSet("CMP_HELP_L0028", 0, 1, 0xA09DC380, 1);
  return 1;
LABEL_26:
  g_step = (u8)g_step;
  if (g_step == 16)
    return 1;
  if (g_step == 11)
    return 1;
  if (g_step == 13)
    return 1;
  frSetVariableRequest(0, 0);
  return 0;
}

// 0x1e5b6a0
void cmpSetEquipSwordNo(s32 iSwordNo) {
  g_equipNo = iSwordNo;
  return;
}

// 0x1e5b730
s8 cmpGetStep(void) {
  return g_step;
}

// 0x1e5b7b0
s8 cmpGetCount(void) {
  return g_count;
}

// 0x1e5b830
s32 cmpGetEquipSwordNo(void) {
  return g_equipNo;
}

// 0x1e5b8b0
void cmpResetUseNekozyar(void) {
  useNekozyar = 0;
  return;
}

// 0x1e5b930
bool cmpChkUseNekozyar(void) {
  return useNekozyar;
}

// 0x1e5b9b0
u8 cmpChkUseTETYOU(void) {
  s32 nakamaMode;
  sdatUnitWork_t *stock_id;
  s32 v6;
  s32 v7;
  s32 v8;
  bool v9;

  nakamaMode = fldGb->nakamaMode;
  stock_id = GBWK->player->stock_id;
  v6 = (stock_id[8]->flag & 1) + (stock_id[7]->flag & 1);
  v7 = (stock_id[21]->flag & 1)
     + (stock_id[20]->flag & 1)
     + (stock_id[19]->flag & 1)
     + (stock_id[18]->flag & 1)
     + (stock_id[17]->flag & 1)
     + (stock_id[16]->flag & 1)
     + (stock_id[15]->flag & 1)
     + (stock_id[14]->flag & 1)
     + (stock_id[13]->flag & 1)
     + (stock_id[12]->flag & 1)
     + (stock_id[11]->flag & 1)
     + (stock_id[10]->flag & 1)
     + (stock_id[9]->flag & 1)
     + v6
     + (stock_id[6]->flag & 1)
     + (stock_id[5]->flag & 1)
     + (stock_id[4]->flag & 1)
     + (stock_id[3]->flag & 1)
     + (stock_id[2]->flag & 1)
     + (stock_id[1]->flag & 1)
     + (stock_id[0]->flag & 1);
  v8 = (stock_id[31]->flag & 1)
     + (stock_id[30]->flag & 1)
     + (stock_id[29]->flag & 1)
     + (stock_id[28]->flag & 1)
     + (stock_id[27]->flag & 1)
     + (stock_id[26]->flag & 1)
     + (stock_id[25]->flag & 1)
     + (stock_id[24]->flag & 1)
     + (stock_id[23]->flag & 1)
     + (stock_id[22]->flag & 1)
     + v7;
  if (v8)
    v9 = nakamaMode == 0;
  else
    v9 = 0;
  return !v9;
}

// 0x1e5bc90
u8 cmpCheckMegane(void) {
  return GBWK->player->megane;
}

// 0x1e5bd00
u8 cmpCheckSeikatu(void) {
  return GBWK->player->seikatu;
}

// 0x1e5bd70
char *cmpGetNoneItemText(void) {
  u32 LanguageID;

  LanguageID = GetLanguageID();
  if (LanguageID <= 4)
    return *(&off_4CD9F68)[LanguageID];
  return "？？？";
}

// 0x1e5be40
u64 cmpChkEnableUseUnit(sdatUnitWork_t *a_pUnit, s32 a_itemId) {
  u32 *v5;
  s32 *v6;
  u32 *v8;
  u64 result;
  s32 v10;
  s64 sklid;
  SBTLITEM_TBL *v12;
  s32 type;
  u32 usetype;
  s32 devilid;
  s32 badstatus;
  ItemUpdateManager *v19;
  sdatUnitWork_t *v20;
  u64 v21;
  s64 v22;
  u64 v24;
  s32 mag;
  s32 magMax;
  sdatPlayerUnitWork_t *player;
  s32 v31;
  s32 str;
  s32 tec;
  s32 vit;
  s32 luck;
  s32 v36;
  s64 v38;
  u32 v39;
  s32 v40;
  s32 Sword4Param;
  s64 v43;
  s32 v44;
  s32 v46;
  s64 v47;
  s32 v48;
  s32 v50;
  s64 v51;
  char *v52;
  char *NoneItemText;
  bool v56;
  CmpSklItemConversionTbl_Tbl *Item;
  sdatUnitWork_t *v59;
  s32 v60;
  s32 v61;
  u32 attr;
  sdatUnitWork_t *UpdateUnit;
  sdatUnitWork_t *v66;
  u32 flg;

  v5 = NewSpecific(uint, 4u);
  InitializeArray_55364416(v5, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__77709D56B05C914D187518E5F38731346FCCCDE306353FB4A30C4B2A91CDA01A, 0);
  v6 = NewSpecific(s32, 4u);
  if (!a_pUnit)
    return 0;
  v8 = v6;
  result = 0;
  if ((u32)a_itemId > 0x2FF || (a_pUnit->flag & 1) == 0)
    return result;
  v10 = 1;
  sklid = tbldata[a_itemId]->sklid;
  v10 = (u8)byte_5755FB0;
  flg = tbldata[sklid]->flg;
  v12 = tbldata[a_itemId];
  type = v12->type;
  usetype = v12->usetype;
  if ((v12->side & 0x1000) != 0)
  {
    if ((a_pUnit->flag & 2) == 0)
      return 0;
  }
  else if ((v12->side & 0x6000) == 0 || (v12->side & 0x800) != 0 && (a_pUnit->flag & 2) != 0)
  {
    return 0;
  }
  if (!fldGb->nakamaMode)
    goto LABEL_28;
  devilid = a_pUnit->devilid;
  result = 0;
  if (GBWK->mapSummonID == devilid && (usetype & 0x10) == 0)
  {
LABEL_28:
    badstatus = a_pUnit->badstatus;
    if ((badstatus & 0x100000) == 0 && ((badstatus & 0x10000) == 0 || !a_pUnit->devilid))
    {
      if ((badstatus & 0x20000) != 0)
      {
        if ((tbldata[sklid]->attr & 0x200) != 0)
        {
          if ((tbldata[sklid]->badst & 0x20000) != 0)
            return 0x10000;
        }
        return 0;
      }
      if ((flg & 0x40) == 0)
      {
        if ((a_itemId & 0xFFFFFFFE) == 0x8C)
          return 1;
        if ((flg & 0x1000) != 0)
          v21 = (u64)(a_pUnit->now->hp < a_pUnit->now->maxhp) << 12;
        else
          v21 = 0;
        if ((flg & 0x2000) != 0)
        {
          if (a_pUnit->now->hp < a_pUnit->now->maxhp)
            v21 |= 0x2000u;
          v22 = (u16)flg & 0xC000;
LABEL_57:
          v24 = v21 | v22;
          if (sbattleIsBattle())
          {
LABEL_58:
            mag = wk->mag;
            magMax = wk->magMax;
LABEL_68:
            if (mag < magMax)
              v21 = v24;
            if ((flg & 0x10000) != 0)
            {
              v31 = a_pUnit->badstatus;
              if ((tbldata[sklid]->badst & v31) != 0)
                v21 = (u32)v21 & 0xFFFECFFF | 0x10000;
              else
                v21 = (u32)v21 & 0xFFFFCFFF;
            }
            str = a_pUnit->backup->str;
            v8[8] = GETITEMPARA_LOW(a_pUnit->pitem->str) + str;
            tec = a_pUnit->backup->tec;
            v8[9] = GETITEMPARA_LOW(a_pUnit->pitem->tec) + tec;
            vit = a_pUnit->backup->vit;
            v8[10] = GETITEMPARA_LOW(a_pUnit->pitem->vit) + vit;
            luck = a_pUnit->backup->luck;
            v8[11] = GETITEMPARA_LOW(a_pUnit->pitem->luck) + luck;
            if ((a_pUnit->flag & 2) != 0)
            {
              v36 = v8[8];
              v8[8] = v36
                    - datGetSword4Param(GBWK->player->swordno, 0);
            }
            LODWORD(v38) = v5[0];
            v39 = flg;
            if (((u32)v38 & flg) != 0)
            {
              if ((s32)v8[8] >= 40)
                v38 = 0;
              else
                v38 = (u32)v38;
              v21 |= v38;
            }
            if ((a_pUnit->flag & 2) != 0)
            {
              v40 = v8[9];
              Sword4Param = datGetSword4Param(GBWK->player->swordno, 1);
              v39 = flg;
              v8[9] = v40 - Sword4Param;
            }
            LODWORD(v43) = v5[1];
            if (((u32)v43 & v39) != 0)
            {
              if ((s32)v8[9] >= 40)
                v43 = 0;
              else
                v43 = (u32)v43;
              v21 |= v43;
            }
            if ((a_pUnit->flag & 2) != 0)
            {
              v44 = v8[10];
              v46 = datGetSword4Param(GBWK->player->swordno, 2);
              v39 = flg;
              v8[10] = v44 - v46;
            }
            LODWORD(v47) = v5[2];
            if (((u32)v47 & v39) != 0)
            {
              if ((s32)v8[10] >= 40)
                v47 = 0;
              else
                v47 = (u32)v47;
              v21 |= v47;
            }
            if ((a_pUnit->flag & 2) != 0)
            {
              v48 = v8[11];
              v50 = datGetSword4Param(GBWK->player->swordno, 3);
              v39 = flg;
              v8[11] = v48 - v50;
            }
            LODWORD(v51) = v5[3];
            if (((u32)v51 & v39) != 0)
            {
              if ((s32)v8[11] >= 40)
                v51 = 0;
              else
                v51 = (u32)v51;
              v21 |= v51;
            }
            v52 = sdatItemName(a_itemId);
            NoneItemText = cmpGetNoneItemText();
            v56 = op_Equality(v52, NoneItemText, 0);
            result = 0;
            if (!v56)
            {
              if (type == 0x4000)
              {
                if (itmUpdateMg)
                {
                  UpdateUnit = GetUpdateUnit(itmUpdateMg, a_pUnit->devilid, a_pUnit->uniq_code);
                }
                else
                {
                  UpdateUnit = 0;
                }
                if (UpdateUnit)
                  v66 = UpdateUnit;
                else
                  v66 = a_pUnit;
                if (v66->level >= 99)
                  return 0;
                else
                  return v21 | 0x200000000LL;
              }
              else if (type == 0x2000)
              {
                Item = get_Item(sklItemConvTbl, a_itemId, 0);
                if ((CmpStatusChkUseSklItem(a_pUnit, Item->sklID) & 1) != 0)
                  return v21 | 0x100000000LL;
                else
                  return 0;
              }
              else
              {
                return v21;
              }
            }
            return result;
          }
LABEL_65:
          player = GBWK->player;
          mag = player->mag;
          magMax = player->maxmag;
          goto LABEL_68;
        }
        else
        {
          v22 = (u16)flg & 0xC000;
          goto LABEL_57;
        }
        v24 = v21 | v22;
        if (sbattleIsBattle())
          goto LABEL_58;
        goto LABEL_65;
      }
      if ((a_pUnit->flag & 6) != 4)
        return 0;
      v19 = itmUpdateMg;
      if (v19)
      {
        v19 = itmUpdateMg;
        v20 = GetUpdateUnit(v19, a_pUnit->devilid, a_pUnit->uniq_code);
      }
      else
      {
        v20 = 0;
      }
      v59 = v20 ? v20 : a_pUnit;
      if (v59->chuusei > 99)
        return 0;
      v60 = a_pUnit->devilid;
      v61 = sub_1B6D720(v60);
      attr = tbldata[sklid]->attr;
      if (attr <= 0x10)
      {
        result = 0;
        switch (attr)
        {
          case 0u:
            return 64;
          case 1u:
            if (v61 == 1)
              return 64;
            return 0;
          case 2u:
            if (v61 == 2)
              return 64;
            return 0;
          case 4u:
            if (v61 == 3)
              return 64;
            return 0;
          case 8u:
            if (v61 == 4)
              return 64;
            return 0;
          case 0x10u:
            if (v61 == 5)
              return 64;
            return 0;
          default:
            return result;
        }
        return result;
      }
      if (attr == 32)
      {
        if (v61 == 6)
          return 64;
      }
      else if (attr == 64 && v61 == 7)
      {
        return 64;
      }
    }
    return 0;
  }
  return result;
}

// 0x1e5c9b0
u64 cmpChkEnableUseChar(sdatUnitWork_t *a_pUnit, s32 a_itemId) {
  u64 v6;
  sdatPlayerUnitWork_t *player;

  if ((tbldata[a_itemId]->usetype & 4) == 0)
    return 0;
  v6 = cmpChkEnableUseUnit(a_pUnit, a_itemId);
  if ((v6 & 0xC000) == 0)
    return v6;
  player = GBWK->player;
  if (player->mag >= player->maxmag)
    return v6 & 0xFFFF3FFF;
  return v6;
}

// 0x1e5cb30
u32 cmpChkUseUnit(sdatUnitWork_t *unit, s32 a_itemID) {
  u32 *v5;
  s32 str;
  s32 tec;
  s32 vit;
  s32 luck;
  u32 v10;
  s64 v11;
  s32 v12;
  s64 sklid;
  u32 flg;
  s32 devilid;
  s32 badstatus;
  u32 attr;
  s32 v18;
  s32 v19;
  s32 v20;
  s32 v22;
  s32 v23;
  s32 v24;
  s32 v25;

  v5 = NewSpecific(s32, 4u);
  str = unit->backup->str;
  v5[8] = GETITEMPARA_LOW(unit->pitem->str) + str;
  tec = unit->backup->tec;
  v5[9] = GETITEMPARA_LOW(unit->pitem->tec) + tec;
  vit = unit->backup->vit;
  v5[10] = GETITEMPARA_LOW(unit->pitem->vit) + vit;
  luck = unit->backup->luck;
  v10 = 0;
  v5[11] = GETITEMPARA_LOW(unit->pitem->luck) + luck;
  if ((u32)a_itemID > 0x2FF || (unit->flag & 1) == 0)
    return v10;
  v11 = a_itemID;
  v12 = 1;
  sklid = tbldata[a_itemID]->sklid;
  v12 = (u8)byte_5755FB0;
  flg = tbldata[sklid]->flg;
  if ((tbldata[v11]->side & 0x1000) != 0)
  {
    if ((unit->flag & 4) != 0)
      return 0;
  }
  else if ((tbldata[v11]->side & 0x6000) == 0 || (tbldata[v11]->side & 0x800) != 0 && (unit->flag & 2) != 0)
  {
    return 0;
  }
  if (fldGb->nakamaMode)
  {
    devilid = unit->devilid;
    if (GBWK->mapSummonID != devilid)
      return 0;
  }
  badstatus = unit->badstatus;
  if ((badstatus & 0x20000) != 0)
  {
    if ((tbldata[sklid]->attr & 0x200) == 0)
      return 0;
    if ((tbldata[sklid]->badst & 0x20000) == 0)
      return 0;
    return 0x10000;
  }
  if ((flg & 0x40) != 0)
  {
    if ((unit->flag & 6) == 4 && unit->chuusei <= 98)
    {
      attr = tbldata[sklid]->attr;
      if (attr > 0x10)
      {
        if (attr == 32)
        {
          v20 = unit->devilid;
          if ((u32)sub_1B6D720(v20) != 6)
            return 0;
        }
        else
        {
          if (attr != 64)
            return 0;
          v19 = unit->devilid;
          if ((u32)sub_1B6D720(v19) != 7)
            return 0;
        }
        return 64;
      }
      else
      {
        v10 = 0;
        switch (attr)
        {
          case 0u:
            return 64;
          case 1u:
            v18 = unit->devilid;
            if ((u32)sub_1B6D720(v18) == 1)
              return 64;
            return 0;
          case 2u:
            v22 = unit->devilid;
            if ((u32)sub_1B6D720(v22) == 2)
              return 64;
            return 0;
          case 4u:
            v23 = unit->devilid;
            if ((u32)sub_1B6D720(v23) == 3)
              return 64;
            return 0;
          case 8u:
            v24 = unit->devilid;
            if ((u32)sub_1B6D720(v24) == 4)
              return 64;
            return 0;
          case 0x10u:
            v25 = unit->devilid;
            if ((u32)sub_1B6D720(v25) == 5)
              return 64;
            return 0;
          default:
            return v10;
        }
      }
    }
    return 0;
  }
  if ((flg & 0x1000) == 0)
  {
    v10 = 0;
    if ((flg & 0x2000) != 0)
      goto LABEL_31;
LABEL_81:
    if ((flg & 0x4000) != 0)
      goto LABEL_34;
LABEL_82:
    if ((flg & 0x8000) != 0)
      goto LABEL_37;
LABEL_83:
    if ((flg & 0x10000) != 0)
      goto LABEL_40;
LABEL_84:
    if ((flg & 0x20000) != 0)
      goto LABEL_48;
LABEL_85:
    if ((flg & 0x40000) != 0)
      goto LABEL_51;
LABEL_86:
    if ((flg & 0x80000) != 0)
      goto LABEL_54;
LABEL_87:
    if ((flg & 0x100000) == 0)
      return v10;
    goto LABEL_88;
  }
  v10 = (unit->now->hp < unit->now->maxhp) << 12;
  if ((flg & 0x2000) == 0)
    goto LABEL_81;
LABEL_31:
  if (unit->now->hp < unit->now->maxhp)
    v10 |= 0x2000u;
  if ((flg & 0x4000) == 0)
    goto LABEL_82;
LABEL_34:
  if (unit->now->mp < unit->now->maxmp)
    v10 |= 0x4000u;
  if ((flg & 0x8000) == 0)
    goto LABEL_83;
LABEL_37:
  if (unit->now->mp < unit->now->maxmp)
    v10 |= 0x8000u;
  if ((flg & 0x10000) == 0)
    goto LABEL_84;
LABEL_40:
  if ((tbldata[sklid]->badst & badstatus) != 0)
    v10 = v10 & 0xFFFECFFF | 0x10000;
  else
    v10 &= 0xFFFFCFFF;
  if ((flg & 0x20000) == 0)
    goto LABEL_85;
LABEL_48:
  if ((s32)v5[8] <= 39)
    v10 |= 0x20000u;
  if ((flg & 0x40000) == 0)
    goto LABEL_86;
LABEL_51:
  if ((s32)v5[10] <= 39)
    v10 |= 0x40000u;
  if ((flg & 0x80000) == 0)
    goto LABEL_87;
LABEL_54:
  if ((s32)v5[9] <= 39)
    v10 |= 0x80000u;
  if ((flg & 0x100000) != 0)
  {
LABEL_88:
    if ((s32)v5[11] < 40)
      v10 |= 0x100000u;
  }
  return v10;
}

// 0x1e5d1e0
bool cmpChkUse(s32 a_itemID) {
  bool v4;
  s32 v6;
  s32 v8;
  char *v10;
  char *NoneItemText;
  bool result;
  sdatUnitWork_t *v21;
  sdatUnitWork_t *para;
  s64 v24;
  s32 v26;
  sdatUnitWork_t *v28;

  if (tbldata[a_itemID]->type != 128)
  {
    if (tbldata[a_itemID]->type != 4096)
    {
      if ((tbldata[a_itemID]->usetype & 4) != 0)
      {
        v4 = evtBitCheck(42);
        if ((u32)(a_itemID - 752) < 0xFFFFFF10 || v4)
        {
          v6 = 0;
          while (1)
          {
            v8 = arrUseItemMessage[arrUseItemMessage->bounds[1].length
                                                             * v6];
            if (v8 < 0)
              break;
            v8 = arrUseItemMessage[arrUseItemMessage->bounds[1].length
                                                                                   * v6];
            ++v6;
            if (v8 == a_itemID)
            {
              switch (a_itemID)
              {
                case 9:
                  if (fldGb->nakamaMode)
                    goto LABEL_54;
                  v10 = sdatItemName(9);
                  goto LABEL_33;
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                case 25:
                case 26:
                case 27:
                case 28:
                case 29:
                case 30:
                case 31:
                case 32:
                case 33:
                  goto LABEL_54;
                case 34:
                  if ((GBWK->player->para->itemstatus & 0x20) != 0)
                    goto LABEL_54;
                  goto LABEL_46;
                case 35:
                  if ((GBWK->player->para->itemstatus & 0x40) != 0)
                    goto LABEL_54;
                  goto LABEL_46;
                case 36:
                  if (fldGb->nakamaMode)
                    goto LABEL_54;
                  goto LABEL_46;
                default:
                  if (a_itemID != 760)
                    goto LABEL_54;
                  if (fldGb->nakamaMode)
                    goto LABEL_54;
                  v10 = sdatItemName(760);
LABEL_33:
                  NoneItemText = cmpGetNoneItemText();
                  if (!op_Inequality(v10, NoneItemText, 0))
                    goto LABEL_54;
LABEL_46:
                  result = 1;
                  break;
              }
              return result;
            }
          }
LABEL_54:
          if (!fldGb->nakamaMode)
          {
            para = GBWK->player->para;
            v24 = 32;
            v26 = cmpChkEnableUseUnit(para, a_itemID) != 0;
            do
            {
              v28 = *(sdatUnitWork_t *)((char *)&GBWK->player->stock_id->obj.klass + v24);
              v24 += 8;
              if (cmpChkEnableUseUnit(v28, a_itemID))
                ++v26;
            }
            while (v24 != 288);
            return v26 > 0;
          }
          if ((tbldata[a_itemID]->type & 0x100) == 0)
          {
            v21 = GBWK->player->stock_id[datGetStockDevilIndex(GBWK->mapSummonID, GBWK->mapSummonUNIQ)];
            return cmpChkEnableUseUnit(v21, a_itemID) != 0;
          }
        }
      }
    }
  }
  return 0;
}

// 0x1e5d7a0
void cmpUpdateUseItemEnebleDecide(void) {
  s64 i;
  bool v6;
  dds3ProcessID_t *v8;
  s32 v9;

  if (g_menuID != 61442)
    return;
  if (g_itemNum < 1)
  {
    itfMenuSetFlagMenu(g_listPID, 0, 2, 0);
    return;
  }
  for (i = 16; ; ++i)
  {
    if (i - 16 >= g_itemNum)
      break;
    v6 = cmpChkUse(*((u16 *)&g_arrItemID->obj.klass + i));
    v8 = g_listPID;
    v9 = *((u16 *)&g_arrItemID->obj.klass + i);
    itfMenuSetFlagMenu(v8, v9, 2, v6);
  }
}

// 0x1e5d9a0
s32 cmpUpdateEnableUseCharUnitPC(void) {
  return cmpUpdateEnableUseCharUnit(g_itemNo);
}

// 0x1e5da20
s32 cmpUpdateEnableUseCharUnit(s32 a_useItemID) {
  s64 v3;
  Il2CppClass **v4;
  s32 v5;
  s64 namespaze_high;
  u32 flg;
  SBTLITEM_TBL *v8;
  s32 side;
  s32 type;
  s32 v12;
  sdatUnitWork_t *stock_id;
  s32 v16;
  sdatUnitWork_t *v17;
  u32 badst;
  s32 v20;
  u32 attr;
  s32 v23;
  u32 v24;
  int32x2_t v25;
  int8x8_t v26;
  int8x8_t v27;
  int8x8_t v28;
  int8x8_t v29;
  int8x8_t v30;
  int8x8_t v31;
  int32x2_t v32;
  int8x8_t v33;
  tagCMP_WORK *Work;
  sdatUnitWork_t *p_psUse;
  char v36;
  tagCMP_WORK *v40;
  u64 v42;
  u64 v43;
  u64 v44;
  u32 v45;

  if ((u32)a_useItemID > 0x2FF)
    return 0;
  v3 = a_useItemID;
  v4 = &tbldata->obj.klass + (u32)a_useItemID;
  v5 = 1;
  namespaze_high = SHIDWORD(v4[4]->_1.namespaze);
  v5 = (u8)byte_5755FB0;
  flg = tbldata[namespaze_high]->flg;
  v8 = tbldata[v3];
  side = v8->side;
  type = v8->type;
  if ((side & 0x1000) != 0)
    v12 = 3;
  else
    v12 = (side << 29 >> 31) & 6;
  v45 = v12;
  if (fldGb->nakamaMode)
  {
    stock_id = GBWK->player->stock_id;
    v16 = 0x200000;
    v17 = stock_id[datGetStockDevilIndex(GBWK->mapSummonID, GBWK->mapSummonUNIQ)];
  }
  else
  {
    v17 = 0;
    v16 = 0;
  }
  if ((tbldata[namespaze_high]->attr & 0x200) == 0)
    goto LABEL_27;
  if ((tbldata[namespaze_high]->badst & 0x20000) != 0)
  {
    v16 |= 0x1000u;
    badst = tbldata[namespaze_high]->badst;
    if ((flg & 0x40) == 0)
      goto LABEL_28;
  }
  else
  {
LABEL_27:
    badst = 0;
    if ((flg & 0x40) == 0)
    {
LABEL_28:
      v20 = v16;
      goto LABEL_53;
    }
  }
  v20 = v16 | 0x20801;
  attr = tbldata[namespaze_high]->attr;
  if (attr > 0x10)
  {
    if (attr == 32)
    {
      v23 = 133633;
    }
    else
    {
      if (attr != 64)
        goto LABEL_53;
      v23 = 134145;
    }
LABEL_52:
    v20 = v16 | v23;
    goto LABEL_53;
  }
  switch (attr)
  {
    case 1u:
      v23 = 133137;
      goto LABEL_52;
    case 2u:
      v23 = 133153;
      goto LABEL_52;
    case 4u:
      v23 = 133185;
      goto LABEL_52;
    case 8u:
      v23 = 133249;
      goto LABEL_52;
    case 0x10u:
      v23 = 133377;
      goto LABEL_52;
    default:
      break;
  }
LABEL_53:
  if ((flg & 0x3000) != 0 && (flg & 0xC000) != 0)
  {
    v20 |= ~(tbldata[namespaze_high]->badst >> 6) & 0x800
         | 0x2000000;
  }
  else if ((flg & 0x3000) == 0)
  {
    goto LABEL_64;
  }
  v20 |= ~(tbldata[namespaze_high]->badst >> 6) & 0x800 | 4;
LABEL_64:
  v24 = v20 | 8;
  if ((flg & 0xC000) == 0)
    v24 = v20;
  v25.n64_u64[0] = vdup_n_s32(v24).n64_u64[0];
  if ((flg & 0x10000) != 0)
  {
    v25.n64_u32[1] = v24 & 0x3FFE7FB;
    v42 = v25.n64_u64[0];
    v25.n64_u64[0] = v42;
    v25.n64_u64[0] = v42;
    v25.n64_u64[0] |= 0x100000001000uLL;
    badst = tbldata[namespaze_high]->badst;
  }
  v26.n64_u64[0] = vbsl_s8(vcltz_s32(vshl_n_s32(vdup_n_s32((flg & 0x20000) == 0), 0x1Fu)), v25, (int8x8_t)(v25.n64_u64[0] | 0x280000002800LL)).n64_u64[0];
  v27.n64_u64[0] = vbsl_s8(vcltz_s32(vshl_n_s32(vdup_n_s32((flg & 0x40000) == 0), 0x1Fu)), v26, (int8x8_t)(v26.n64_u64[0] | 0x880000008800LL)).n64_u64[0];
  v28.n64_u64[0] = vbsl_s8(vcltz_s32(vshl_n_s32(vdup_n_s32((flg & 0x80000) == 0), 0x1Fu)), v27, (int8x8_t)(v27.n64_u64[0] | 0x480000004800LL)).n64_u64[0];
  v29.n64_u64[0] = vbsl_s8(vcltz_s32(vshl_n_s32(vdup_n_s32((flg & 0x100000) == 0), 0x1Fu)), v28, vorr_s8(v28, vdup_n_s32(0x10800u))).n64_u64[0];
  v30.n64_u64[0] = vbsl_s8(vcltz_s32(vshl_n_s32(vdup_n_s32(type == 0x2000), 0x1Fu)), vorr_s8(v29, vdup_n_s32(0x800800u)), v29).n64_u64[0];
  v31.n64_u64[0] = vorr_s8(v30, vdup_n_s32(0x1000800u)).n64_u64[0];
  v32.n64_u64[0] = vcltz_s32(vshl_n_s32(vdup_n_s32(type == 0x4000), 0x1Fu)).n64_u64[0];
  v33.n64_u64[0] = vbsl_s8(v32, v31, v30).n64_u64[0];
  v43 = v33.n64_u64[0];
  v33.n64_u64[0] = v43;
  v44 = v33.n64_u64[0] | 0x4000000040000LL;
  Work = cmpGetWork();
  Work->psUse = v17;
  p_psUse = &Work->psUse;
  *((u32 *)p_psUse + 4) = v44;
  v36 = byte_575803D;
  *(sdatUnitWork_t *)((char *)p_psUse + 20) = (sdatUnitWork_t *)v44;
  p_psUse[1] = (sdatUnitWork_t *)v45;
  if ((v36 & 1) != 0)
  {
    goto LABEL_79;
  }
  else
  {
LABEL_79:
    cmpGetWork()->iBadStatus = badst;
    goto LABEL_80;
  }
  cmpGetWork()->iBadStatus = badst;
LABEL_80:
  v40 = cmpGetWork();
  return cmpMenuFilter(v40);
}

// 0x1e5e3b0
s32 cmpCheckUseCharEnableSelect(s32 a_useItemID) {
  sdatUnitWork_t *para;
  s64 v6;
  s32 v8;
  sdatUnitWork_t *v10;

  para = GBWK->player->para;
  v6 = 32;
  v8 = cmpChkEnableUseChar(para, a_useItemID) != 0;
  do
  {
    v10 = *(sdatUnitWork_t *)((char *)&GBWK->player->stock_id->obj.klass + v6);
    v6 += 8;
    if (cmpChkEnableUseChar(v10, a_useItemID))
      ++v8;
  }
  while (v6 != 288);
  return v8;
}

// 0x1e5e4d0
s32 cmpCallFuncUse2(void) {
  dds3ProcessID_t *StockPID;
  s32 SelectID;
  s16 v16;
  dds3ProcessID_t *v20;
  sdatUnitWork_t *para;
  sdatUnitWork_t *v32;
  sdatPlayerUnitWork_t *player;
  s64 v35;
  sdatUnitWork_t *v37;
  sdatUnitWork_t *v40;
  s32 v42;
  s32 v45;
  dds3ProcessID_t *v48;
  dds3ProcessID_t *v54;
  dds3ProcessID_t *v56;
  SBTLITEM_TBL *v58;
  sdatUnitWork_t *v60;
  s32 v63;
  sdatPlayerUnitWork_t *v64;
  SBTLITEM_TBL *v67;
  char v69;
  dds3ProcessID_t *v70;
  SBTLITEM_TBL *v72;
  s64 v73;
  bool v75;
  s32 v78;
  dds3ProcessID_t *v81;
  s32 v82;
  bool FlagMenu;
  u32 v86;
  sdatUnitWork_t *v91;
  sdatUnitWork_t *stock_id;
  sdatUnitWork_t *v108;
  s32 v110;
  sdatUnitWork_t *v111;

  cmpGetWork();
  if (g_step != 1)
    return 1;
  if (g_panel == 2)
  {
    StockPID = cmpGetStockPID();
LABEL_20:
    g_activePID = StockPID;
    SelectID = itfMenuGetSelectID(g_activePID);
    g_charNo = SelectID;
    if (g_panel != 1)
      goto LABEL_36;
    if (SelectID == 2)
    {
      v16 = GBWK->player->stack_p[1];
      goto LABEL_35;
    }
    else
    {
      if (SelectID != 1)
        goto LABEL_36;
      v16 = GBWK->player->stack_p[0];
LABEL_35:
      g_charNo = v16;
LABEL_36:
      v20 = g_activePID;
      if (itfMenuGetFlagMenu(v20, g_charNo, 4u))
      {
        para = GBWK->player->para;
        if (cmpChkEnableUseUnit(para, g_itemNo))
        {
          v32 = GBWK->player->para;
          sdatCalcItem(v32, g_itemNo);
          player = GBWK->player;
          datCalcNowParam(player->para, player->swordno, 0);
          datDvlParaUpdate(0);
        }
        v35 = 32;
        while (1)
        {
          v37 = *(sdatUnitWork_t *)((char *)&GBWK->player->stock_id->obj.klass + v35);
          if (!!cmpChkEnableUseUnit(v37, g_itemNo))
          {
            v40 = *(sdatUnitWork_t *)((char *)&GBWK->player->stock_id->obj.klass + v35);
            v42 = g_itemNo;
            sdatCalcItem(v40, v42);
            datCalcNowParam(*(sdatUnitWork_t *)((char *)&GBWK->player->stock_id->obj.klass + v35), 0, 0);
          }
          v35 += 8;
          if (v35 == 288)
          {
            v45 = 0;
            while (1)
            {
              v48 = g_activePID;
              if (!itfMenuGetFlagMenu(v48, v45, 2u))
              {
                goto LABEL_79;
              }
              v54 = g_activePID;
              itfMenuSetAnimFlashMenu(v54, v45);
LABEL_79:
              if (!!itfMenuGetFlagMenu(g_stockPID, v45, 2u))
              {
                v56 = g_stockPID;
                itfMenuSetAnimFlashMenu(v56, v45);
              }
              if (++v45 == 12)
                goto LABEL_131;
            }
          }
        }
      }
      if ((tbldata[g_itemNo]->type & 0x4000) != 0)
      {
LABEL_124:
        ItemUnitUpdate(SelectID);
        goto LABEL_128;
      }
      v58 = tbldata;
      if ((v58[g_itemNo]->type & 0x100) != 0)
        goto LABEL_124;
      if (!SelectID)
      {
        if (g_panel == 1)
        {
          v60 = GBWK->player->para;
          v63 = g_itemNo;
          sdatCalcItem(v60, v63);
          v64 = GBWK->player;
          datCalcNowParam(v64->para, v64->swordno, 0);
          datDvlParaUpdate(0);
LABEL_128:
          v70 = g_activePID;
          itfMenuSetAnimFlashMenu(v70, SelectID);
LABEL_131:
          v72 = tbldata;
          v73 = g_itemNo;
          if ((v72[v73]->flg & 2) != 0)
          {
            datAddItem(v73, -1);
            v75 = datCheckItem(g_itemNo, 1);
            if (!v75)
            {
              v78 = g_itemNo;
              itfMenuDelMenu(g_listPID, v78);
              itfMenuSetFlagMenu(g_listPID, g_itemNo, 2, 0);
            }
          }
          List = MakeList(61442);
          cmpUpdateUseItemEnebleDecide();
          v81 = g_listPID;
          v82 = g_itemNo;
          FlagMenu = itfMenuGetFlagMenu(v81, v82, 2u);
          if (FlagMenu)
          {
            if (v86)
            {
              if (g_charNo)
                goto LABEL_171;
            }
            else
            {
              if (g_charNo)
                goto LABEL_171;
            }
            if (g_panel == 1 && !SelectID)
            {
              v91 = GBWK->player->para;
              if (cmpChkEnableUseChar(v91, g_itemNo))
                goto LABEL_179;
LABEL_174:
              if (cmpUpdateEnableUseCharUnit(g_itemNo))
              {
                goto LABEL_176;
              }
              goto LABEL_9007;
              if (cmpUpdateEnableUseCharUnit(g_itemNo))
              {
LABEL_176:
                goto LABEL_177;
              }
LABEL_9007:
              cmpCheckUseCharEnableSelect(g_itemNo);
LABEL_177:
              cmpUpdateSelectPosCharPID();
              cmpUpdateSelectNextPosCharPID2();
              cmpUpdateSelectNextPosStockPID();
              g_panel = cmpSetFocusPanel(g_panel);
              goto LABEL_179;
            }
LABEL_171:
            stock_id = GBWK->player->stock_id;
            if (!cmpChkEnableUseChar(stock_id[g_charNo], g_itemNo))
              goto LABEL_174;
LABEL_179:
            v69 = 1;
LABEL_182:
            g_count = 0;
            g_step = v69;
            return 1;
          }
          if (v86)
          {
LABEL_157:
            itfMenuSetFlag(g_charPID, 256, 1);
            itfMenuSetFlag(g_stockPID, 256, 1);
            goto LABEL_179;
          }
          else
          {
            goto LABEL_157;
          }
          goto LABEL_157;
        }
      }
      v67 = tbldata;
      if (v67[g_itemNo]->type == 0x2000)
      {
        cmpSklItemSetStatusDraw();
        v69 = 11;
        goto LABEL_182;
      }
      v108 = GBWK->player->stock_id;
      v110 = g_itemNo;
      v111 = v108[g_charNo];
      sdatCalcItem(v111, v110);
      datCalcNowParam(GBWK->player->stock_id[g_charNo], 0, 0);
      goto LABEL_128;
    }
    goto LABEL_35;
  }
  StockPID = cmpGetCharPID();
  goto LABEL_20;
}

// 0x1e61170
bool cmpItmRnkUpCheck(sdatUnitWork_t *_unit) {
  il2cpp_array_size_t max_length;
  char v4;
  s64 v5;
  s64 v6;
  s32 v8;

  if (!evtBitCheck(43))
  {
    v4 = 0;
    return v4 & 1;
  }
  max_length = sdatLvUpPlayerRankUp->max_length;
  if ((s32)max_length >= 1)
  {
    v4 = 0;
    v5 = 4;
    v6 = -(s64)(u32)max_length;
    while (1)
    {
      v8 = *(u32 *)(*((u64 *)&sdatLvUpPlayerRankUp->obj.klass + v5) + 24);
      if (!v8)
      {
        goto LABEL_11;
      }
      v8 = *(u32 *)(*((u64 *)&sdatLvUpPlayerRankUp->obj.klass + v5) + 24);
      if (!evtBitCheck(v8))
        return v4 & 1;
LABEL_11:
      if (!evtBitCheck(*(u32 *)(*((u64 *)&sdatLvUpPlayerRankUp->obj.klass + v5) + 20)))
      {
        v4 |= datGetTotalCyuusei(unit) >= *(u32 *)(*((u64 *)&sdatLvUpPlayerRankUp->obj.klass + v5) + 16);
      }
      ++v5;
      if (v6 + v5 == 4)
        return v4 & 1;
    }
  }
  return 0;
}

// 0x1e5f450
void ItemUnitUpdate(s32 _id) {
  Il2CppClass *klass;
  sdatPlayerUnitWork_t *v4;
  sdatUnitWork_t *v6;
  s32 v7;
  s32 v8;
  sdatUnitWork_t *v9;
  s32 v10;
  ItemUpdateManager *v12;
  sdatPlayerUnitWork_t *v13;
  ItemUpdateManager *v14;
  sdatPlayerUnitWork_t *v15;
  sdatPlayerUnitWork_t *v16;
  s32 v18;
  sdatUnitWork_t *v19;
  void *castClass;
  sdatUnitWork_t *v22;
  s32 v25;
  s32 level;
  void *data;
  s32 v29;
  sdatUnitWork_t *stock_id;
  s32 StockDevilIndex;
  sdatPlayerUnitWork_t *v33;
  sdatPlayerUnitWork_t *updateDrawPlayer;
  ItemUpdateManager *p_fields;
  sdatUnitWork_t *v38;
  sdatUnitWork_t *para;
  sdatUnitWork_t *v43;
  ItemUpdateManager *itmUpdateMg_local;
  sdatPlayerUnitWork_t *v45;
  ItemUpdateManager *v46;
  sdatPlayerUnitWork_t *v47;
  sdatUnitWork_t *v55;
  sdatPlayerUnitWork_t *v58;

  klass = _get_Instance()[13].klass;
  if (!id)
  {
    if (g_panel == 1)
      goto LABEL_6;
  }
  v22 = Allocate(sdatUnitWork_t);
  _ctor(v22, 0);
  ClassCopy(v22, selDrawDevil, 0);
  v25 = sdatCalcItem(v22, g_itemNo);
  if ((tbldata[g_itemNo]->type & 0x100) == 0)
  {
    v22->exp += v25;
    datGetDevilLevelUpUnit(v22, v22);
    datCalcNowParam(v22, 0, 0);
    level = v22->level;
    if (level > selDrawDevil->level)
    {
      data = klass->_1.this_arg.data;
      v29 = v22->level;
      stock_id = GBWK->player->stock_id;
      StockDevilIndex = datGetStockDevilIndex(v22->devilid, v22->uniq_code);
      LvUpNumAnimTrig(data, v29 - stock_id[StockDevilIndex]->level, 0);
      goto LABEL_60;
    }
    v38 = GBWK->player->stock_id;
    v38[datGetStockDevilIndex(v22->devilid, v22->uniq_code)]->exp = v22->exp;
    goto LABEL_64;
  }
  v33 = Allocate(sdatPlayerUnitWork_t);
  _ctor(v33, 0);
  updateDrawPlayer = itmUpdateMg->updateDrawPlayer;
  if (updateDrawPlayer)
  {
    goto LABEL_52;
LABEL_51:
    updateDrawPlayer = p_fields->updateDrawPlayer;
LABEL_52:
    ClassCopy(v33, updateDrawPlayer, 0);
    para = v33->para;
    datAddTotalCyuusei(para, v25);
    v43 = v33->para;
    if (cmpItmRnkUpCheck(v33->para))
      goto LABEL_56;
    goto LABEL_9001;
    if (cmpItmRnkUpCheck(v43))
    {
LABEL_56:
      itmUpdateMg_local = itmUpdateMg;
      v47 = itmUpdateMg_local->updateDrawPlayer;
      v46 = &itmUpdateMg_local->fields;
      v45 = v47;
      if (!v47)
      {
        v58 = Allocate(sdatPlayerUnitWork_t);
        _ctor(v58, 0);
        v46->updateDrawPlayer = v58;
        v45 = v46->updateDrawPlayer;
      }
      ClassCopy(v45, v33, 0);
      itmUpdateMg->rstJump = 1;
      if (v22->chuusei >= 100)
        goto LABEL_60;
      goto LABEL_71;
    }
LABEL_9001:
    *(u32 *)&GBWK->player->para->chuusei_high = *(u32 *)&v33->para->chuusei_high;
    if (v22->chuusei >= 100)
    {
LABEL_60:
      itmUpdateMg->rstJump = 1;
LABEL_64:
      SetUpdateDvlUnit(itmUpdateMg, v22);
      goto LABEL_65;
    }
LABEL_71:
    v55 = GBWK->player->stock_id;
    v55[datGetStockDevilIndex(v22->devilid, v22->uniq_code)]->chuusei = v22->chuusei;
    goto LABEL_64;
  }
  p_fields = &GBWK->player;
  goto LABEL_51;
LABEL_6:
  v4 = Allocate(sdatPlayerUnitWork_t);
  _ctor(v4, 0);
  ClassCopy(v4, selDrawPlayer, 0);
  v6 = v4->para;
  v7 = g_itemNo;
  v8 = sdatCalcItem(v6, v7);
  v9 = v4->para;
  v10 = v9->exp + v8;
  v9->exp = v10;
  datGetPlayerLevelUpUnit(v4, v4);
  datCalcNowParam(v4->para, GBWK->player->swordno, 0);
  datDvlParaUpdate(0);
  v12 = itmUpdateMg;
  v15 = v12->updateDrawPlayer;
  v14 = &v12->fields;
  v13 = v15;
  if (!v15)
  {
    v16 = Allocate(sdatPlayerUnitWork_t);
    _ctor(v16, 0);
    v14->updateDrawPlayer = v16;
    v13 = v14->updateDrawPlayer;
  }
  ClassCopy(v13, v4, 0);
  v18 = itmUpdateMg->updateDrawPlayer->para->level;
  v19 = GBWK->player->para;
  if (v18 <= v19->level)
  {
    v19 = GBWK->player->para;
    v19->exp = v4->para->exp;
    cmpUpdateUseItemEnebleDecide();
    goto LABEL_66;
  }
  else
  {
    castClass = klass->_1.castClass;
    LOBYTE(v18) = itmUpdateMg->updateDrawPlayer->para->level;
    LvUpNumAnimTrig(castClass, (char)v18 - GBWK->player->para->level, 0);
    itmUpdateMg->rstJump = 1;
  }
LABEL_65:
  cmpUpdateUseItemEnebleDecide();
LABEL_66:
  cmpUpdateSelectPosCharPID();
  cmpUpdateSelectNextPosCharPID2();
  cmpUpdateSelectNextPosStockPID();
}

// 0x1e61620
s32 cmpCallFuncUse(void) {
    return 0;
}

// 0x1e623d0
s32 cmpCallFuncBullet(void) {
  s32 SelectID;
  sdatPlayerUnitWork_t *player;

  SelectID = itfMenuGetSelectID(g_listPID);
  player = GBWK->player;
  player->hgunnum = player->item[SelectID];
  player->bulletno = SelectID;
  g_step = g_step + 1;
  return 1;
}

// 0x1e624d0
s32 cmpCallFuncSword(void) {
  void *Instance;
  tagCMP_WORK *Work;

  Instance = get_Instance(0);
  ItfSortMenuActive(Instance, 0, 0);
  itfMenuGetSelectID(g_listPID);
  Work = cmpGetWork();
  cmpSklTypeSet(0, 1);
  itfMenuSetFlagMenu(Work->menuPID, 262146, 64, 0);
  cmpSetTabFlag(1);
  cmpSetHelpFlag(1);
  cmpSetHelpDispFlag(0);
  g_GoldNoDspFlg = 1;
  g_step = 1;
  return 1;
}

// 0x1e626c0
u32 cmpGetValueColor(s32 iNewVal, s32 iOldVal) {
  u32 v3;

  if (iOldVal >= iNewVal)
    v3 = -1600273536;
  else
    v3 = 1853947776;
  if (iOldVal <= iNewVal)
    return v3;
  else
    return 1849704703;
}

// 0x1e626f0
void cmpDrawSwordParam(s32 a_x, s32 a_y, s32 a_z, u8 a_alphaRate, s32 a_swordno, s32 a_swordno_chk, u32 a_swordnameColor) {
  s32 v13;
  s64 v14;
  void *monitor;
  void *v16;
  char *v17;
  u32 v18;
  u32 v19;
  s32 m_atk;
  s32 v21;
  s32 v22;
  Il2CppObject *v23;
  char *v24;
  char *v25;
  Il2CppObject *Instance;
  u32 v27;
  s32 hp;
  s32 v29;
  s32 v30;
  Il2CppObject *v31;
  char *v32;
  char *v33;
  Il2CppObject *v34;
  u32 v35;
  s32 str;
  s32 v37;
  s32 v38;
  Il2CppObject *v39;
  char *v40;
  char *v41;
  Il2CppObject *v42;
  u32 v43;
  s32 tec;
  s32 v45;
  s32 v46;
  Il2CppObject *v47;
  char *v48;
  char *v49;
  Il2CppObject *v50;
  u32 v51;
  s32 vit;
  s32 v53;
  s32 v54;
  Il2CppObject *v55;
  char *v56;
  char *v57;
  Il2CppObject *v58;
  s32 luck;
  s32 v60;
  s32 v61;
  Il2CppObject *v62;
  char *v63;
  Il2CppObject *v64;
  s32 m_hojo;
  s32 SkillIconSpriteNo;
  s32 v67;
  s32 data;

  v13 = GBWK->player->swordno != a_swordno;
  v14 = a_swordno;
  monitor = _get_Instance()[9].monitor;
  DetailsSwordTypeIconDraw(monitor, tbl[a_swordno]->m_type, v13, 0);
  v16 = _get_Instance()[9].monitor;
  v17 = sdatItemName(a_swordno + 144);
  WeaponDetailsTextDraw(v16, v17, 1, v13, "", 1, 0);
  v18 = -1600273536;
  v19 = -1600273536;
  m_atk = tbl[v14]->m_atk;
  if ((a_swordno_chk & 0x80000000) == 0)
  {
    v21 = tbl[a_swordno_chk]->m_atk;
    if (v21 >= m_atk)
      v22 = -1600273536;
    else
      v22 = 1853947776;
    if (v21 <= m_atk)
      v19 = v22;
    else
      v19 = 1849704703;
  }
  data = m_atk;
  v23 = Box(s32, &data);
  v24 = Format("{0,3:d}", v23, 0);
  v25 = Concat_54766928(0, v24, 0);
  Instance = _get_Instance();
  WeaponParaDraw(Instance[9].monitor, 5, 1, m_atk, v19, v13, 0);
  v27 = -1600273536;
  hp = tbl[v14]->m_paraBns->hp;
  if ((a_swordno_chk & 0x80000000) == 0)
  {
    v29 = tbl[a_swordno_chk]->m_paraBns->hp;
    if (v29 >= hp)
      v30 = -1600273536;
    else
      v30 = 1853947776;
    if (v29 <= hp)
      v27 = v30;
    else
      v27 = 1849704703;
  }
  data = hp;
  v31 = Box(s32, &data);
  v32 = Format("{0,2:d}", v31, 0);
  v33 = Concat_54766928(v25, v32, 0);
  v34 = _get_Instance();
  WeaponParaDraw(v34[9].monitor, 4, 0, hp, v27, v13, 0);
  v35 = -1600273536;
  str = tbl[v14]->m_paraBns->str;
  if ((a_swordno_chk & 0x80000000) == 0)
  {
    v37 = tbl[a_swordno_chk]->m_paraBns->str;
    if (v37 >= str)
      v38 = -1600273536;
    else
      v38 = 1853947776;
    if (v37 <= str)
      v35 = v38;
    else
      v35 = 1849704703;
  }
  data = str;
  v39 = Box(s32, &data);
  v40 = Format("{0,1:d}", v39, 0);
  v41 = Concat_54766928(v33, v40, 0);
  v42 = _get_Instance();
  WeaponParaDraw(v42[9].monitor, 0, 1, str, v35, v13, 0);
  v43 = -1600273536;
  tec = tbl[v14]->m_paraBns->tec;
  if ((a_swordno_chk & 0x80000000) == 0)
  {
    v45 = tbl[a_swordno_chk]->m_paraBns->tec;
    if (v45 >= tec)
      v46 = -1600273536;
    else
      v46 = 1853947776;
    if (v45 <= tec)
      v43 = v46;
    else
      v43 = 1849704703;
  }
  data = tec;
  v47 = Box(s32, &data);
  v48 = Format("{0,1:d}", v47, 0);
  v49 = Concat_54766928(v41, v48, 0);
  v50 = _get_Instance();
  WeaponParaDraw(v50[9].monitor, 1, 2, tec, v43, v13, 0);
  v51 = -1600273536;
  vit = tbl[v14]->m_paraBns->vit;
  if ((a_swordno_chk & 0x80000000) == 0)
  {
    v53 = tbl[a_swordno_chk]->m_paraBns->vit;
    if (v53 >= vit)
      v54 = -1600273536;
    else
      v54 = 1853947776;
    if (v53 <= vit)
      v51 = v54;
    else
      v51 = 1849704703;
  }
  data = vit;
  v55 = Box(s32, &data);
  v56 = Format("{0,1:d}", v55, 0);
  v57 = Concat_54766928(v49, v56, 0);
  v58 = _get_Instance();
  WeaponParaDraw(v58[9].monitor, 2, 3, vit, v51, v13, 0);
  luck = tbl[v14]->m_paraBns->luck;
  if ((a_swordno_chk & 0x80000000) == 0)
  {
    v60 = tbl[a_swordno_chk]->m_paraBns->luck;
    if (v60 >= luck)
      v61 = -1600273536;
    else
      v61 = 1853947776;
    if (v60 <= luck)
      v18 = v61;
    else
      v18 = 1849704703;
  }
  data = luck;
  v62 = Box(s32, &data);
  v63 = Format("{0,1:d}", v62, 0);
  Concat_54766928(v57, v63, 0);
  v64 = _get_Instance();
  WeaponParaDraw(v64[9].monitor, 3, 4, luck, v18, v13, 0);
  m_hojo = tbl[v14]->m_hojo;
  if ((m_hojo & 0x80000000) == 0)
  {
    SkillIconSpriteNo = cmpGetSkillIconSpriteNo(m_hojo);
    if ((SkillIconSpriteNo & 0x80000000) == 0)
    {
      v67 = SkillIconSpriteNo;
      itfIconDrawSprite(a_x + 2, a_y + 47, a_z, a_alphaRate, v67, 108);
    }
  }
}

// 0x1e63250
void DrawFunc(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate) {
  tagCMP_WORK *Work;
  CmpSubMenuPass *p_menuPass;
  CmpSubMenuPass *menuPass;
  s32 iconType;
  s32 v23;
  void *klass;
  Il2CppObject *ProcessData;
  Il2CppObject *v27;
  s32 v29;
  Il2CppClass *v30;
  s32 tab;
  s64 v32;
  s32 v33;
  s64 v34;
  CmpSubMenuPass *v35;
  s64 v36;
  CmpSubMenuPass *v37;
  char *v38;
  CmpSubMenuPass *v39;
  char *v40;
  CmpSubMenuPass *v41;
  CmpSubMenuPass *v43;
  s32 v48;
  Il2CppObject *Instance;
  Il2CppObject *v50;
  s64 v52;
  char *v53;
  void *v55;
  CmpSubMenuPass *v56;
  u32 v57;
  dds3ProcessID_t *v63;
  dds3ProcessID_t *v67;
  bool v70;
  s32 EvtItemSprNo;
  Il2CppObject *v74;
  void *gameObject;
  Il2CppObject *v76;
  Il2CppObject *v77;
  Il2CppObject *v78;
  s32 v80;
  Il2CppObject *v81;
  char *v82;
  dds3ProcessID_t *v87;
  u32 v88;
  s32 v91;
  s32 swordno;
  s32 v93;
  Il2CppObject *v94;
  u32 v95;
  s32 v98;
  s32 v99;
  s32 v100;
  s32 v101;
  u8 v102;
  void *v103;
  s32 data;

  Work = cmpGetWork();
  if (!g_setSaveCsr)
    return;
  menuPass = Work->menuPass;
  p_menuPass = &Work->menuPass;
  if (menuPass)
  {
    goto LABEL_17;
  }
  else
  {
    v35 = Allocate(CmpSubMenuPass);
    _ctor(v35, 0);
    p_menuPass = v35;
LABEL_17:
    exMenu = 1;
    goto LABEL_18;
  }
  exMenu = 1;
LABEL_18:
  v100 = a_y;
  v101 = a_z;
  v99 = a_x;
  iconType = tbldata[a_id]->iconType;
  if (g_menuID == 262146)
    v23 = 0;
  else
    v23 = iconType;
  klass = _get_Instance()[7].klass;
  v103 = _get_Instance()[11].klass;
  ProcessData = dds3GetProcessData(g_listPID);
  v27 = ProcessData;
  v29 = ProcessData[8].klass;
  ExtendMenuOn(klass, 8, 0);
  ExtendMenuClearCheck(klass, v29, 0);
  v30 = v27[5].klass;
  tab = -1;
  v102 = a_alphaRate;
  if ((s32)v30->_1.namespaze < 1)
  {
    v33 = -1;
  }
  else
  {
    v32 = 0;
    v33 = -1;
    while (1)
    {
      v34 = *(u64 *)(*((u64 *)&v30->_1.byval_arg.data + v32) + 24);
      if (v34)
      {
        if (*(u32 *)(v34 + 16) == a_id)
          break;
      }
      if ((u32)v30->_1.namespaze == ++v32)
        goto LABEL_42;
    }
    v33 = v32;
  }
LABEL_42:
  v36 = 8 * v33;
  v37 = p_menuPass;
  v38 = *(char **)((*(u64 **)((char *)&v30->_1.byval_arg.data + v36))[3] + 48);
  v37->str = v38;
  v37 = ((char *)v37 + 24);
  v37[-1].devilID = v33;
  v39 = p_menuPass;
  v40 = *(char **)((*(u64 **)((char *)&v27[5].klass->_1.byval_arg.data + v36))[3] + 56);
  v39->tag = v40;
  v41 = p_menuPass;
  p_menuPass->color = a_fontColor;
  v43 = v41;
  v43->sklSprNo = -1;
  v43->itmType = v23;
  v43->devilID = -1;
  v41->id = g_menuID;
  if (g_menuID != 262146)
  {
    tab = itmMenuData->tab;
  }
  DrawItemTab(klass, tab, 0);
  v48 = g_menuID;
  if (!a_id)
  {
    if (v48 != 262146)
    {
      ExtendMenuText(klass, p_menuPass, 0);
      ItemNum(klass, v33, -1, a_fontColor, 0);
      (klass->scrollBarSet->klass->vtable._4_ScrollBarDraw.methodPtr)(klass->scrollBarSet, HIDWORD(v27[8].klass), HIDWORD(v27[7].monitor), *((u32 *)v27[9].monitor + SBYTE4(v27[5].monitor) + 8), klass->scrollBarSet->klass->vtable._4_ScrollBarDraw.method);
      ExtendMenuCursorClear(klass, 0);
      Instance = _get_Instance();
      SetAnim(Instance[12].klass, 1, 0);
      return;
    }
  }
  if (v48 == 262146)
  {
    ExtendMenuClearCheck(v103, v29, 0);
    v50 = _get_Instance();
    DrawWeaponMenu(v50, 0);
    SwordIconChange(v103, v33, tbl[a_id - 144]->m_type, 0);
    (v103->scrollBarSet->klass->vtable._4_ScrollBarDraw.methodPtr)(v103->scrollBarSet, HIDWORD(v27[8].klass), HIDWORD(v27[7].monitor), *((u32 *)v27[9].monitor + SBYTE4(v27[5].monitor) + 8), v103->scrollBarSet->klass->vtable._4_ScrollBarDraw.method);
    v52 = *(u64 *)(*((u64 *)&v27[5].klass->_1.byval_arg.data + v33) + 24);
    v53 = *(char **)(v52 + 48);
    v52 = *(u64 *)(*((u64 *)&v27[5].klass->_1.byval_arg.data + v33) + 24);
    ExtendMenuText(v103, v33, v53, a_fontColor, g_menuID, *(char **)(v52 + 56), 0);
    goto LABEL_73;
  }
  if (itmUpdateMg)
  {
    if (!itmUpdateMg->rstJump)
    {
      v55 = *((void *)_get_Instance()[9].monitor + 3);
      if (get_activeSelf(v55, 0))
        SetActive(v55, 0, 0);
    }
  }
LABEL_73:
  v56 = p_menuPass;
  if ((*(u32 *)(*(u64 *)(*((u64 *)&v27[5].klass->_1.byval_arg.data + v33) + 24) + 112) & 8) != 0)
    v57 = 1;
  else
    v57 = a_fontColor;
  v56->color = v57;
  ExtendMenuText(klass, v56, 0);
  (klass->scrollBarSet->klass->vtable._4_ScrollBarDraw.methodPtr)(klass->scrollBarSet, HIDWORD(v27[8].klass), HIDWORD(v27[7].monitor), *((u32 *)v27[9].monitor + SBYTE4(v27[5].monitor) + 8), klass->scrollBarSet->klass->vtable._4_ScrollBarDraw.method);
  if (itfMenuGetSelectID(g_listPID) != a_id)
  {
    goto LABEL_81;
  }
  v67 = g_listPID;
  itfMenuImgGetAlpha(v67, 2);
  if (g_menuID == 262146)
    ExtendMenuCursor(v103, v33, 0);
  MainMenuCursorMove(klass, v33, ((s64)v27[13].klass & 8) == 0, 0);
  v70 = cmpDrawHelp();
  if (g_menuID != 262146 && !v70)
  {
    itfDrawMiscHelp(0xA09DC380, (f32)v102 / 255.0, 1, a_id, 0);
  }
  EvtItemSprNo = cmpGetEvtItemSprNo(a_id);
  if (itmMenuData->tab != 1 || EvtItemSprNo == -1)
    goto LABEL_119;
  if (g_itemNum < 1)
  {
LABEL_119:
    v78 = _get_Instance();
    SetAnim(v78[12].klass, 1, 0);
  }
  else
  {
    v74 = _get_Instance();
    gameObject = get_gameObject(v74[12].klass, 0);
    if (!get_activeSelf(gameObject, 0))
      SetActive(gameObject, 1, 0);
    v76 = _get_Instance();
    SetAnim(v76[12].klass, 0, 0);
    v77 = _get_Instance();
    ChangeSprite(v77[12].klass, EvtItemSprNo, 0);
  }
LABEL_81:
  v63 = g_listPID;
  itfMenuChkMenuTop(v63, a_id);
  if (g_menuID == 65538)
  {
    itfIconDrawBullet(v99 + 105, v100, v101, v102, a_id, 108);
  }
  if (g_menuID == 196610)
    goto LABEL_126;
  if (itmMenuData->tab == 1)
    goto LABEL_126;
  if (g_itemNum > 0)
    goto LABEL_128;
LABEL_126:
  if (g_menuID == 262146)
    goto LABEL_128;
  ItemNum(klass, v33, -1, v57, 0);
  return;
LABEL_128:
  v80 = GBWK->player->item[a_id];
  data = v80;
  v81 = Box(s32, &data);
  v82 = Format("{0,3:d}", v81, 0);
  Concat_54766928(0, v82, 0);
  ItemNum(v103, v33, v80, v57, 0);
  ItemNum(klass, v33, v80, v57, 0);
  if (g_menuID == 262146)
  {
    v87 = g_listPID;
    if (itfMenuGetSelectID(v87) != a_id)
      return;
    v91 = a_id - 144;
    swordno = GBWK->player->swordno;
    cmpDrawSwordParam(28, 264, v101, v102, swordno, -1, v88);
    v93 = GBWK->player->swordno;
    v94 = _get_Instance();
    if (v91 == v93)
    {
      RaidouAffterWeapon(v94, 0, 0);
    }
    else
    {
      RaidouAffterWeapon(v94, 1, 0);
      v98 = GBWK->player->swordno;
      cmpDrawSwordParam(28, 349, v101, v102, v91, v98, v95);
    }
    return;
  }
}

// 0x1e64110
s32 cmpGetEvtItemSprNo(ITM _itemNo) {
  void *v3;
  void *_9__76_1;
  void *v10;
  void *v11;
  Il2CppObject *object;
  Il2CppObject *v14;

  v3 = Allocate(Project_cmpItem___c__DisplayClass76_0);
  v3->_itemNo = itemNo;
  if (itemNo == 403 && evtBitCheck(97))
  {
    _9__76_1 = __9__76_1;
    if (!_9__76_1)
    {
      v14 = __9;
      _9__76_1 = Allocate(System_Predicate_cmpItem_EvtItemCutInSpr_);
      __ctor(_9__76_1, v14, Method_Project_cmpItem___c__GetEvtItemSprNo_b__76_1__, 0);
      __9__76_1 = _9__76_1;
    }
    object = Find_object_(cutInOnTbl, _9__76_1);
    return HIDWORD(object[1].klass);
  }
  v10 = cutInOnTbl;
  v11 = Allocate(System_Predicate_cmpItem_EvtItemCutInSpr_);
  __ctor(v11, v3, Method_Project_cmpItem___c__DisplayClass76_0__GetEvtItemSprNo_b__0__, 0);
  object = Find_object_(v10, v11);
  if (!object)
    return -1;
  return HIDWORD(object[1].klass);
}

// 0x1e64330
void cmpSortMenu(void) {
  void *v1;
  s64 i;
  s64 size;
  s64 v6;
  s32 *items;
  s32 v8;
  void *Instance;
  void *v10;
  void *v11;
  void *IndexList;
  s64 j;
  s64 v15;
  s64 k;
  s16 Item;
  char *v20;

  v1 = Allocate(System_Collections_Generic_List_int_);
  __ctor(v1);
  for (i = 0; ; ++i)
  {
    if (i >= g_itemNum)
      break;
    size = v1->_size;
    v6 = (s64)g_arrItemID + 2 * i;
    ++v1->_version;
    items = v1->_items;
    v8 = *(u16 *)(v6 + 32);
    if ((u32)size >= LODWORD(items->max_length))
    {
      _AddWithResize(v1, v8, *(const MethodInfo_2D8F530 **)(*(u64 *)(*((u64 *)Method_System_Collections_Generic_List_int__Add__ + 4) + 192) + 112));
    }
    else
    {
      v1->_size = size + 1;
      items[size] = v8;
    }
  }
  Instance = get_Instance(0);
  ListSet_object_(Instance, v1);
  v10 = get_Instance(0);
  ListSort(v10, 0);
  v11 = get_Instance(0);
  IndexList = GetIndexList(v11, 0);
  for (j = 0; ; ++j)
  {
    if (j >= g_itemNum)
      break;
    v15 = (s64)g_arrItemID + 2 * j;
    *(u16 *)(v15 + 32) = 0;
  }
  for (k = 0; ; ++k)
  {
    if (k >= g_itemNum)
      break;
    Item = _get_Item(IndexList, k);
    v20 = (char *)g_arrItemID + 2 * k;
    *((u16 *)v20 + 16) = Item;
  }
}

// 0x1e5ff00
s32 MakeList(CMP_MENU_ID a_id) {
  u16 v4;
  s64 v12;
  s32 tab;

  v4 = 0;
  g_itemNum = 0;
  while (1)
  {
    if (SLODWORD(s_arrSortItemID->max_length) <= v4)
      break;
    v12 = LOWORD(s_arrSortItemID[v4]);
    if (!datCheckItem(v12, 1))
      goto LABEL_9;
    if (a_id > 196609)
    {
      if (a_id == 196610)
      {
LABEL_42:
        if (!datCheckEventItem(v12))
          goto LABEL_9;
        goto LABEL_6;
      }
      if (a_id != 262146)
      {
        if (a_id != 393218)
          goto LABEL_9;
        goto LABEL_34;
      }
      if ((tbldata[(u32)v12]->type & 0x400) == 0)
        goto LABEL_9;
      goto LABEL_6;
    }
    if (a_id != 61442)
    {
      if (a_id == 65538)
      {
        if ((tbldata[(u32)v12]->type & 4) == 0)
          goto LABEL_9;
        goto LABEL_6;
      }
      if (a_id != 131074)
        goto LABEL_9;
      if (tbldata[(u32)v12]->type)
      {
        if ((tbldata[(u32)v12]->flg & 4) == 0)
          goto LABEL_6;
      }
      goto LABEL_9;
    }
    tab = itmMenuData->tab;
    if (tab)
    {
      if (tab == 1)
        goto LABEL_42;
      if (tab != 2)
        goto LABEL_9;
LABEL_34:
      if ((tbldata[(u32)v12]->type & 0x800) == 0)
        goto LABEL_9;
LABEL_6:
      g_arrItemID[g_itemNum] = v12;
      g_itemNum = g_itemNum + 1;
      goto LABEL_9;
    }
    if ((tbldata[v12]->usetype & 6) != 0)
      goto LABEL_6;
    if ((tbldata[v12]->type & 0x80) != 0)
      goto LABEL_6;
    if ((tbldata[v12]->type & 0x1000) != 0)
      goto LABEL_6;
LABEL_9:
    ++v4;
  }
  return g_itemNum;
}

// 0x1e645d0
void cmpSwordSelStatusDraw(void) {
  tagCMP_WORK *Work;
  dds3ProcessID_t *charPID;
  sdatUnitWork_t *para;

  Work = cmpGetWork();
  charPID = Work->charPID;
  itfMenuSetFlag(charPID, 2048, 1);
  itfMenuSetFlag(Work->stockPID, 2048, 1);
  g_equipNo = 1;
  para = GBWK->player->para;
  Start(para, 0);
  SetType(17039361, g_equipNo, 0);
  cmpSwordSelFlagOn();
  cmpSetTabFlag(1);
  cmpSetHelpFlag(1);
  g_GoldNoDspFlg = 1;
}

// 0x1e5fc70
void cmpSklItemSetStatusDraw(void) {
  sdatUnitWork_t *stock_id;
  sdatUnitWork_t *v5;
  CmpSklItemConversionTbl_Tbl *Item;
  s32 v7;
  s32 sklID;
  s32 v10;
  Il2CppClass *klass;

  cmpGetWork();
  stock_id = GBWK->player->stock_id;
  v5 = stock_id[datGetStockDevilIndex(selDrawDevil->devilid, selDrawDevil->uniq_code)];
  Start(v5, 0);
  SetType(0x80000000LL, 0, 0);
  Item = get_Item(sklItemConvTbl, g_itemNo, 0);
  v7 = CmpStatusChkUseSklItem(v5, Item->sklID);
  sklItmRst = v7;
  sklID = get_Item(sklItemConvTbl, g_itemNo, 0)->sklID;
  v10 = OmoideSklCheck(sklID);
  cmpStartSklSet(v5, v10);
  cmpSetTabFlag(1);
  cmpSetHelpFlag(1);
  g_GoldNoDspFlg = 1;
  klass = _get_Instance()[13].klass;
  openInfo = 0;
  MenuClose(klass, 0);
}

// 0x1e64810
void cmpSortActiveOnFunc(void) {
  cmpSetHelpFlag(0);
  itfMenuSetFlag(g_listPID, 256, 1);
}

// 0x1e648f0
void cmpSortActiveOffFunc(void) {
  cmpSetHelpFlag(1);
  itfMenuSetFlag(g_listPID, 256, 0);
  ButtonLineHelpTextSet(0, 0, 1, 0xA09DC380, 1);
}

// 0x1e64a00
void cmpSortFunc(void) {
  Setup(g_menuID, 0);
  itfMenuSetFlag(g_listPID, 256, 1);
}

// 0x1e65970
void cmpSortSetting(CMP_MENU_ID _id) {
  s32 v4;
  void *Instance;
  void *v6;
  void *v7;
  void *v8;
  void *v9;
  void *v10;
  s32 tab;

  if (id == 262146)
  {
    v4 = 8;
LABEL_6:
    Instance = get_Instance(0);
    SortSetting(Instance, v4, 0);
    goto LABEL_7;
  }
  tab = itmMenuData->tab;
  if (!tab)
  {
    v4 = 3;
    goto LABEL_6;
  }
  if (tab == 2)
  {
    v4 = 5;
    goto LABEL_6;
  }
  tab = itmMenuData->tab;
  if (tab == 1)
  {
    v4 = 4;
    goto LABEL_6;
  }
LABEL_7:
  v6 = get_Instance(0);
  v7 = Allocate(System_Action);
  _ctor(v7, 0, Method_Project_cmpItem_SortActiveOnFunc__, 0);
  v8 = Allocate(System_Action);
  _ctor(v8, 0, Method_Project_cmpItem_SortActiveOffFunc__, 0);
  SetActiveCallBack(v6, v7, v8, 0);
  v9 = get_Instance(0);
  v10 = Allocate(System_Action);
  _ctor(v10, 0, Method_Project_cmpItem_SortFunc__, 0);
  SetSortCallBack(v9, v10, 0);
}

// 0x1e64ab0
void Setup(CMP_MENU_ID a_id, bool _none) {
  dds3ProcessID_t *ListPID;
  dds3ProcessID_t *v12;
  itfMoverFunc_t v13;
  dds3ProcessID_t *v16;
  itfMoverFunc_t v17;
  dds3ProcessID_t *v18;
  s64 i;
  u32 v23;
  u32 v25;
  s32 v26;
  u32 v28;
  s32 tab;
  u32 v30;
  dds3ProcessID_t *v31;
  char *v33;
  s32 v34;
  s32 v35;
  bool v36;
  dds3ProcessID_t *v37;
  dds3ProcessID_t *v38;
  char *v40;
  itfMenuFunc_t v41;
  dds3ProcessID_t *v44;
  s32 swordno;
  dds3ProcessID_t *v46;
  char *v47;
  itfMenuFunc_t v48;
  dds3ProcessID_t *v50;
  itfMenuDrawFunc_t v51;
  dds3ProcessID_t *v52;
  dds3ProcessID_t *v57;
  dds3ProcessID_t *v60;
  dds3ProcessID_t *CharPID;
  dds3ProcessID_t *StockPID;
  s32 StockPanelActive;
  u32 v67;
  dds3ProcessID_t *v68;
  sprHandle_t *v78;
  char *v80;
  char *LocalizeText;
  dds3ProcessID_t *v83;
  dds3ProcessID_t *v84;
  itfMenuDrawFunc_t v85;
  dds3ProcessID_t *v88;

  g_menuID = a_id;
  g_count = 0;
  List = MakeList(a_id);
  cmpSortMenu();
  ListPID = cmpGetListPID();
  g_listPID = ListPID;
  itfMenuClearMenuAll(g_listPID);
  if (g_menuID == 262146)
  {
    v12 = g_listPID;
    v13 = Allocate(itfMoverFunc_t);
    _ctor(v13, 0, Method_Project_cmpMain_WeaponMenuAnimFunc__, 0);
    itfMoverSetMenu(v12, v13);
    cmpSwordSelStatusDraw();
    goto LABEL_22;
  }
  else
  {
    v16 = g_listPID;
    v17 = Allocate(itfMoverFunc_t);
    _ctor(v17, 0, Method_Project_cmpMain_ExSubMenuAnimFunc__, 0);
    itfMoverSetMenu(v16, v17);
    goto LABEL_22;
  }
LABEL_22:
  v18 = g_listPID;
  itfMenuSetFlag(v18, 8, 1);
  itfMenuSetFlag(g_listPID, 32, 0);
  itfMenuSetFlag(g_listPID, 256, 0);
  itfMenuSetFlag(g_listPID, 512, 0);
  itfMenuSetFlag(g_listPID, 2048, 0);
  itfMenuSetFlag(g_listPID, 4096, 0);
  itfMenuSetFlag(g_listPID, 0x2000, 0);
  itfMenuSetFlag(g_listPID, 1, 1);
  itfMenuSetSelectID(g_listPID, 0);
  for (i = 0; ; ++i)
  {
    if (i >= g_itemNum)
      break;
    v26 = g_arrItemID[i];
    if (g_menuID != 61442)
    {
      if (v25)
      {
        if (g_menuID != 262146)
          goto LABEL_74;
      }
      else
      {
        if (g_menuID != 262146)
          goto LABEL_74;
      }
      swordno = GBWK->player->swordno;
      v46 = g_listPID;
      v47 = sdatItemName(v26);
      v48 = Allocate(itfMenuFunc_t);
      _ctor(v48, 0, Method_Project_cmpItem_CallFuncSword__, 0);
      itfMenuSetRootMenu(v46, v26, v47, v48, 0);
      itfMenuSetFlagMenu(g_listPID, v26, 2, v26 - 144 != swordno);
      goto LABEL_74;
    }
    if (v25)
    {
      tab = itmMenuData->tab;
      if (!tab)
        goto LABEL_46;
    }
    else
    {
      tab = itmMenuData->tab;
      if (!tab)
      {
LABEL_46:
        if (v28)
        {
          v38 = g_listPID;
          goto LABEL_48;
        }
        else
        {
          v38 = g_listPID;
        }
LABEL_48:
        v40 = sdatItemName(v26);
        v41 = Allocate(itfMenuFunc_t);
        _ctor(v41, 0, Method_Project_cmpItem_CallFuncUse__, 0);
        itfMenuSetRootMenu(v38, v26, v40, v41, 0);
        itfMenuSetFlagMenu(g_listPID, v26, 128, 1);
        if (!cmpChkUse(v26))
        {
          v44 = g_listPID;
          v37 = v44;
          v34 = v26;
          v35 = 2;
          v36 = 0;
LABEL_54:
          itfMenuSetFlagMenu(v37, v34, v35, v36);
          goto LABEL_74;
        }
        goto LABEL_74;
      }
    }
    if (v28)
    {
      if (tab == 1)
        goto LABEL_37;
    }
    else
    {
      tab = itmMenuData->tab;
      if (tab == 1)
      {
LABEL_37:
        if (!v30)
          goto LABEL_67;
        goto LABEL_38;
      }
    }
    if (v30)
    {
      if (tab == 2)
        goto LABEL_66;
    }
    else
    {
      if (itmMenuData->tab == 2)
      {
LABEL_66:
LABEL_67:
        v31 = g_listPID;
LABEL_39:
        v33 = sdatItemName(v26);
        itfMenuSetRootMenu(v31, v26, v33, 0, 0);
        v34 = v26;
        v35 = 128;
        v36 = 1;
        v37 = g_listPID;
        goto LABEL_54;
LABEL_38:
        v31 = g_listPID;
        goto LABEL_39;
      }
    }
LABEL_74:
    v50 = g_listPID;
    v51 = Allocate(itfMenuDrawFunc_t);
    _ctor(v51, 0, Method_Project_cmpItem_DrawFunc__, 0);
    itfMenuSetDrawFunc(v50, v26, v51, 0);
    v52 = g_listPID;
    itfMenuLinkSprite(v52, g_hSpr[1]);
    {
      v57 = g_listPID;
      goto LABEL_85;
    }
    v57 = g_listPID;
LABEL_85:
    itfMenuSetFlag(v57, 2, 0);
    itfMenuSetDrawParam(g_listPID, 8, 1);
    itfMenuStart(g_listPID);
    if (itmMenuData->tab)
    {
      v60 = g_listPID;
      itfMenuSetDecideSE(v60, -1, -2);
    }
    CharPID = cmpGetCharPID();
    g_charPID = CharPID;
    StockPID = cmpGetStockPID();
    g_stockPID = StockPID;
    StockPanelActive = cmpGetStockPanelActive();
    if (StockPanelActive == 2)
    {
      if (!v67)
      v68 = cmpGetStockPID();
    }
    else
    {
      if (!v67)
      v68 = cmpGetCharPID();
    }
    g_activePID = v68;
    itfMenuSetFlag(g_charPID, 512, 0);
    itfMenuSetFlag(g_stockPID, 512, 0);
    itfMenuSetSelectID(g_charPID, 0);
    g_step = 0;
    *(u64 *)&g_itemNo = -1;
    g_oldSwordSelNo = -1;
    if (!g_hSpr)
    {
      cmpLoadSpriteHnd(2);
      goto LABEL_105;
LABEL_106:
      v78 = g_hSpr[2];
      goto LABEL_9002;
LABEL_105:
      goto LABEL_106;
LABEL_9002:
      g_hSpr = v78;
      continue;
    }
  }
  if (v23)
  {
    if ((s32)g_itemNum > 0)
      return;
LABEL_129:
    if (g_menuID == 262146)
      return;
    v80 = "CMP_STATUS_L0018";
    LocalizeText = GetLocalizeText(v80, 1);
    v83 = g_listPID;
    itfMenuSetRootMenu(v83, 0, LocalizeText, 0, 0);
    itfMenuSetFlagMenu(g_listPID, 0, 128, 1);
    itfMenuSetFlagMenu(g_listPID, 0, 2, 0);
    v84 = g_listPID;
    v85 = Allocate(itfMenuDrawFunc_t);
    _ctor(v85, 0, Method_Project_cmpItem_DrawFunc__, 0);
    itfMenuSetDrawFunc(v84, 0, v85, 0);
    itfMenuSetFlag(g_listPID, 2, 0);
    itfMenuSetDrawParam(g_listPID, 8, 1);
    itfMenuStart(g_listPID);
    if (itmMenuData->tab)
    {
      v88 = g_listPID;
      itfMenuSetDecideSE(v88, -1, -2);
    }
    ButtonLineHelpDispSet(0);
  }
  else
  {
    if (g_itemNum <= 0)
      goto LABEL_129;
  }
}

// 0x1e65bc0
void FreeSpriteHnd(void) {
  if (g_hSpr)
    goto LABEL_4;
  return;
  if (g_hSpr)
  {
LABEL_4:
    cmpFreeSpriteHnd(2);
    g_hSpr = 0;
    return;
  }
}

// 0x1e65cc0
void cmpOpenItemInfo(void) {
  Il2CppClass *klass;
  sdatUnitWork_t *v10;
  s32 devilid;
  s32 v13;
  SBTLITEM_TBL *v16;
  s64 v18;
  s32 v19;
  s32 v20;
  sdatUnitWork_t *para;
  s32 swordno;
  s32 sklID;
  s32 v29;
  s32 v31;
  bool v32;

  itemNumDraw = 1;
  klass = _get_Instance()[13].klass;
  cmpSearchiSelDevil();
  if (!selDrawDevil)
    return;
  if (!selDrawDevil->devilid)
  {
    if (!selDrawPlayer)
      return;
  }
  v10 = selDrawDevil;
  devilid = (u16)v10->devilid;
  if (v10->devilid)
  {
    datCalcNowParam(v10, 0, 0);
    v13 = 2;
    goto LABEL_25;
  }
  para = selDrawPlayer->para;
  swordno = selDrawPlayer->swordno;
  datCalcNowParam(para, swordno, 0);
  v13 = 1;
LABEL_25:
  SetDevilStatus(klass, selDrawDevil, 0, 0, selDrawPlayer, 0, 0);
  SetBtlSkill(klass, selDrawDevil, -1, 0);
  SetBtlSkillCsr(klass, -1, 0);
  SetOmoideSkill(klass, selDrawDevil, -1, 0, 2, 0);
  SetOmoideSkillCsr(klass, -1, 0);
  SetOmoideScrollBar(klass, selDrawDevil, 0, 2, 0);
  if (!openInfo)
  {
    if (tbldata[g_itemNo]->type == 0x2000)
    {
      LODWORD(g_itemNo) = g_itemNo;
      sklID = get_Item(sklItemConvTbl, g_itemNo, 0)->sklID;
      if (OmoideSklCheck(sklID))
        v29 = 3;
      else
        v29 = 2;
    }
    else
    {
      v29 = 1;
    }
    MenuOpne(klass, v13, v29, 0);
    openInfo = 1;
    goto LABEL_64;
  }
  if (!devilid)
  {
    v20 = 0;
    goto LABEL_62;
  }
  v16 = tbldata;
  v18 = g_itemNo;
  if (v16[v18]->type == 0x2000)
  {
    LODWORD(v18) = g_itemNo;
    v19 = get_Item(sklItemConvTbl, v18, 0)->sklID;
    if (OmoideSklCheck(v19))
      v20 = 3;
    else
      v20 = 2;
  }
  else
  {
    v20 = 1;
  }
LABEL_62:
  MenuChange(klass, v20, 0);
LABEL_64:
  v31 = selDrawDevil->devilid;
  v32 = DlcDevilSelCheck(v31);
  DrawOnOff(klass, v32, 0);
}

// 0x1e66980
void cmpCloseItemInfo(void) {
  Il2CppClass *klass;

  itemNumDraw = 0;
  klass = _get_Instance()[13].klass;
  itfMenuSetFlag(g_listPID, 2048, 0);
  itfMenuSetFlag(g_listPID, 4096, 1);
  openInfo = 0;
  MenuClose(klass, 0);
}

// 0x1e662c0
void cmpSearchiSelDevil(void) {
  Il2CppClass *klass;
  dds3ProcessID_t *g_stockPID_local;
  s32 SelectID;
  sdatUnitWork_t *v9;
  s64 v19;
  sdatUnitWork_t *UpdateUnit;
  sdatUnitWork_t *v22;
  void *castClass;
  void *data;
  s32 level;
  sdatPlayerUnitWork_t *v30;
  s32 v32;
  sdatPlayerUnitWork_t *v33;
  sdatPlayerUnitWork_t *player;
  sdatPlayerUnitWork_t *v38;

  cmpGetWork();
  klass = _get_Instance()[13].klass;
  if (g_panel == 2)
  {
    g_stockPID_local = g_stockPID;
    goto LABEL_12;
  }
  else
  {
    if (g_panel != 1)
      return;
    g_stockPID_local = g_charPID;
    goto LABEL_12;
  }
LABEL_12:
  SelectID = itfMenuGetSelectID(g_stockPID_local);
  v9 = Allocate(sdatUnitWork_t);
  _ctor(v9, 0);
  selDrawDevil = v9;
  selDrawPlayer = 0;
  if (SelectID)
  {
    if (SelectID == 1)
    {
      if (g_panel != 1)
        goto LABEL_32;
      player = GBWK->player;
      v19 = (s64)player->stock_id + 8 * player->stack_p[0];
      goto LABEL_37;
    }
    if (SelectID == 2)
    {
      if (g_panel == 1)
      {
        v30 = GBWK->player;
        v19 = (s64)v30->stock_id + 8 * v30->stack_p[1];
LABEL_37:
        ClassCopy(selDrawDevil, *(sdatUnitWork_t *)(v19 + 32), 0);
        UpdateUnit = GetUpdateUnit(itmUpdateMg, selDrawDevil->devilid, selDrawDevil->uniq_code);
        if (UpdateUnit)
        {
          v22 = UpdateUnit;
          if (selDrawDevil->level >= v22->level)
          {
LABEL_42:
            ClassCopy(selDrawDevil, v22, 0);
            return;
          }
          (*(*(u64 *)klass->_1.this_arg.data + 552))(klass->_1.this_arg.data, 1, *(u64 *)(*(u64 *)klass->_1.this_arg.data + 560));
          data = klass->_1.this_arg.data;
          level = v22->level;
          LvUpNumChenge(data, level - selDrawDevil->level, 0);
          goto LABEL_42;
        }
        castClass = klass->_1.this_arg.data;
        goto LABEL_45;
      }
    }
    else
    {
    }
LABEL_32:
    v19 = (s64)GBWK->player->stock_id + 8 * SelectID;
    goto LABEL_37;
  }
  if (g_panel != 1)
    goto LABEL_32;
  if (!itmUpdateMg->updateDrawPlayer)
  {
    v38 = Allocate(sdatPlayerUnitWork_t);
    _ctor(v38, 0);
    selDrawPlayer = v38;
    ClassCopy(selDrawPlayer, GBWK->player, 0);
    ClassCopy(selDrawDevil, GBWK->player->para, 0);
    castClass = klass->_1.castClass;
LABEL_45:
    (*(*(u64 *)castClass + 552))(castClass, 0, *(u64 *)(*(u64 *)castClass + 560));
    return;
  }
  v32 = GBWK->player->para->level;
  if (v32 < itmUpdateMg->updateDrawPlayer->para->level)
    (*(klass->_1.castClass->_1.image + 69))(klass->_1.castClass, 1, *((u64 *)klass->_1.castClass->_1.image + 70));
  v33 = Allocate(sdatPlayerUnitWork_t);
  _ctor(v33, 0);
  selDrawPlayer = v33;
  ClassCopy(selDrawPlayer, itmUpdateMg->updateDrawPlayer, 0);
  ClassCopy(selDrawDevil, itmUpdateMg->updateDrawPlayer->para, 0);
}

// 0x1e66b00
void cmpItmUseButtonGuideSet(void) {
  s32 devilid;
  bool v6;
  s32 v9;

  if (g_panel != 2)
    goto LABEL_14;
  if (!selDrawDevil)
    goto LABEL_14;
  devilid = selDrawDevil->devilid;
  v6 = DlcDevilSelCheck(devilid);
  if (v6)
    goto LABEL_14;
  if (itmUpdateMg->rstJump)
    v9 = 9;
  else
    v9 = 8;
  goto LABEL_21;
LABEL_14:
  if (itmUpdateMg->rstJump)
    v9 = 7;
  else
    v9 = 6;
LABEL_21:
  cmpCmpGuideSet(v9, 0, 90);
}

// 0x1e66ce0
void cmpTabChange(void) {
  u32 v7;
  ItemMenuData *v8;
  s32 v9;
  s32 v10;
  bool v11;
  s32 tab;
  Il2CppObject *Instance;
  dds3ProcessID_t *v20;
  dds3ProcessID_t *v21;
  s32 v22;
  dds3ProcessID_t *v23;

  if (itfMenuGetCtrlType(g_listPID) != 1)
    return;
  itmMenuData->oldTab = itmMenuData->tab;
  if (!CHECK_REP(4104, 1))
  {
    v11 = CHECK_REP(4107, 1);
    if (!v11)
    {
      v10 = 0;
      goto LABEL_32;
    }
    tab = itmMenuData->tab;
    if (tab == 2)
    {
      itmMenuData->tab = 0;
      v10 = 1;
      goto LABEL_32;
    }
    tab = itmMenuData->tab;
    itmMenuData->tab = tab + 1;
    v10 = 1;
    goto LABEL_32;
  }
  v8 = itmMenuData;
  v9 = v8->tab;
  if (!v9)
  {
    if (!v7)
    {
      v8 = itmMenuData;
    }
    v8->tab = 2;
    v10 = 1;
    goto LABEL_32;
  }
  if (!v7)
  {
    v8 = itmMenuData;
    v9 = v8->tab;
  }
  v8->tab = v9 - 1;
  v10 = 1;
LABEL_32:
  if (!v10)
    return;
  Instance = _get_Instance();
  AllMenuContentsClear(Instance[7].klass, 0);
  if (MakeList(61442) >= 1)
  {
    if (itmMenuData->tab)
    {
      v20 = g_listPID;
      v21 = v20;
      v22 = -2;
LABEL_49:
      itfMenuSetDecideSE(v21, -1, v22);
      goto LABEL_50;
    }
    v23 = g_listPID;
    v21 = v23;
    v22 = -1;
    goto LABEL_49;
  }
LABEL_50:
  SE(24);
  *((u8 *)*((const MethodInfo *)cmpItem + 2).virtualMethodPointer + 48) = 15;
  cmpCsrUseSave();
  g_setSaveCsr = 0;
}

// 0x1e67090
bool cmpTabChangeMouse(void) {
  return 0;
}

// 0x1e67260
void cmpMenuChange(void) {
  cmpSortSetting(61442);
  Setup(61442, 0);
}

// 0x1e670a0
void cmpCsrUseSave(void) {
  tagCMP_WORK *Work;
  MenuSelectData *SelectData;
  MenuSelectData *v5;
  s32 oldTab;
  CmpCsrSave *csrSave;
  s32 v9;
  MenuSelectData *v10;

  Work = cmpGetWork();
  SelectData = itfMenuCreateSelectData(g_listPID);
  if (SelectData)
    goto LABEL_8;
  return;
  if (SelectData)
  {
LABEL_8:
    v5 = SelectData;
    oldTab = itmMenuData->oldTab;
    if (oldTab == 1)
    {
      csrSave = Work->csrSave;
      v9 = 4;
      v10 = v5;
LABEL_11:
      SetCsrSave(csrSave, v9, v10, 0);
      return;
    }
    csrSave = Work->csrSave;
    if (oldTab == 2)
    {
      v9 = 5;
      v10 = v5;
      goto LABEL_11;
    }
    v9 = 3;
    v10 = v5;
    goto LABEL_11;
  }
}

// 0x1e672d0
void cmpCsrUseLoad(void) {
  tagCMP_WORK *Work;
  s32 tab;
  CmpCsrSave *csrSave;
  s32 v7;
  MenuSelectData *SaveSelectID;

  Work = cmpGetWork();
  if (g_setSaveCsr)
    return;
  if (g_step)
    return;
  tab = itmMenuData->tab;
  if (tab != 1)
  {
    tab = itmMenuData->tab;
    csrSave = Work->csrSave;
    if (tab == 2)
      v7 = 5;
    else
      v7 = 3;
    goto LABEL_22;
  }
  csrSave = Work->csrSave;
  v7 = 4;
LABEL_22:
  SaveSelectID = GetSaveSelectID(csrSave, v7, 0);
  if (SaveSelectID)
  {
    itfMenuSetSelectData(g_listPID, SaveSelectID);
  }
  g_setSaveCsr = 1;
}

// 0x1e674d0
void cmpTipsOffCallBack(void) {
  ButtonLineHelpDispSet(1);
}

// 0x1e67550
bool cmpUpdateUse(void) {
  tagCMP_WORK *Work;
  s32 v5;
  s32 StockPanelActive;
  void *v12;
  dds3ProcessID_t *v13;
  bool Flag;
  dds3ProcessID_t *v16;
  bool v17;
  u32 v20;
  dds3ProcessID_t *v22;
  bool v26;
  TipsCallBack v29;
  dds3ProcessID_t *v33;
  char v35;
  void *v37;
  s32 sklID;
  s32 v42;
  dds3ProcessID_t *charPID;
  dds3ProcessID_t *v44;
  dds3ProcessID_t *StockPID;
  dds3ProcessID_t *v56;
  s32 WaitType;
  void *Instance;
  tagCMP_STATUS_WORK *StatusWk;
  dds3ProcessID_t *v67;
  TipsCallBack v68;
  u32 v69;
  s32 v72;
  void *v73;
  dds3ProcessID_t *v75;
  dds3ProcessID_t *v76;
  dds3ProcessID_t *v78;
  dds3ProcessID_t *v79;
  dds3ProcessID_t *v87;
  s32 v88;
  s32 tab;
  s32 v92;
  void *v93;
  void *v95;
  dds3ProcessID_t *v97;
  dds3ProcessID_t *v102;
  struct cmpItem *v104;
  dds3ProcessID_t *v107;
  s32 v108;
  dds3ProcessID_t *v114;
  s32 v115;
  void *v117;
  dds3ProcessID_t *v119;
  _BOOL8 v120;

  Work = cmpGetWork();
  SelectID = itfMenuGetSelectID(g_listPID);
  v5 = SelectID;
  cmpCsrUseLoad();
  LOBYTE(g_scrPID) = 0;
  switch (g_step)
  {
    case 0:
      if (cmpTipsCalc(Work))
        return 0;
      v56 = g_listPID;
      WaitType = itfMenuGetWaitType(v56);
      if (WaitType == 4)
      {
        if (g_charPID)
        {
          itfMenuSetDecideSE(g_charPID, -1, -1);
        }
        if (g_stockPID)
        {
          itfMenuSetDecideSE(g_stockPID, -1, -1);
        }
        cmpCsrUseSave();
        g_setSaveCsr = 0;
        Instance = get_Instance(0);
        ItfSortMenuActive(Instance, 0, 0);
        StatusWk = cmpGetStatusWk();
        if (StatusWk)
          StatusWk->player_tec = -1;
        return 1;
      }
      tab = itmMenuData->tab;
      if (tab == 2)
      {
        v92 = 16;
        goto LABEL_219;
      }
      tab = itmMenuData->tab;
      if (tab == 1)
      {
        v92 = 17;
      }
      else
      {
        if (v5 != 9)
          goto LABEL_293;
        if (DlcItemGetCheck(9))
        {
          v92 = 10;
        }
        else
        {
LABEL_293:
          v92 = 5;
        }
      }
LABEL_219:
      cmpCmpGuideSet(v92, 0, 90);
      v93 = get_Instance(0);
      if (GetItfSortSysActive(v93, 0))
        goto LABEL_221;
      goto LABEL_9000;
      if (GetItfSortSysActive(v117, 0))
      {
LABEL_221:
LABEL_222:
        v95 = get_Instance(0);
        ItfSortMenuActive(v95, 1, 0);
        return 0;
      }
LABEL_9000:
      v119 = g_listPID;
      v120 = itfMenuSetFlagMenu(v119, -1, 8, 0);
      cmpTabChange();
      goto LABEL_222;
    case 1:
      StockPanelActive = cmpGetStockPanelActive();
      g_panel = StockPanelActive;
      v12 = get_Instance(0);
      ItfSortMenuActive(v12, 0, 0);
      v13 = g_charPID;
      Flag = itfMenuGetFlag(v13, 8u);
      if (!Flag)
      {
        v16 = g_stockPID;
        v17 = itfMenuGetFlag(v16, 8u);
        if (!v17)
        {
          g_step = 3;
        }
      }
      if (g_count < 0)
        goto LABEL_39;
      LOBYTE(g_count) = g_count;
      if ((char)g_count < 50)
      {
        if (!v20)
        {
          LOBYTE(g_count) = g_count;
        }
        g_count = g_count + 1;
LABEL_39:
        v22 = g_listPID;
        itfMenuSetFlagMenu(v22, g_itemNo, 2048, 1);
        itfMenuSetFlag(g_listPID, 2048, 1);
        itfMenuSetFlag(g_listPID, 4096, 0);
        cmpOpenItemInfo();
        cmpItmUseButtonGuideSet();
        v26 = CHECK_PRESS(4096, 1);
        LOBYTE(g_scrPID) = 0;
        if (!v26)
        {
          if (tbldata[g_itemNo]->type == 0x2000 && !evtBitCheck(10026))
          {
            v29 = Allocate(TipsCallBack);
            _ctor(v29, 0, Method_Project_cmpItem_TipsOffCallBack__, 0);
            add_OffEvent(v29, 0);
            tipsTIPSStart(42);
            ReceiptSet(9466);
            v33 = g_charPID;
            itfMenuSetFlag(v33, 256, 1);
            itfMenuSetFlag(g_stockPID, 256, 1);
            itfMenuSetFlag(g_listPID, 256, 1);
            v35 = 16;
            goto LABEL_201;
          }
          return 0;
        }
        return (char)g_scrPID;
      }
      if (!v20)
      {
        v87 = g_listPID;
        v88 = g_itemNo;
        goto LABEL_212;
      }
      v87 = g_listPID;
      v88 = g_itemNo;
LABEL_212:
      if (itfMenuGetFlagMenu(v87, v88, 2u))
      {
        goto LABEL_277;
      }
      cmpSetStockPanelActive(0, 0);
      g_step = 3;
LABEL_277:
      g_count = -1;
      return 0;
    case 3:
      if (itmUpdateMg->rstJump)
      {
        *(u16 *)&g_step = 12;
        dds3FadeOut(0, 0, 0, 0x14u);
      }
      else
      {
        if (useSpItem)
        {
          useSpItem = 0;
        }
        else
        {
          if (!v69)
          cmpCloseItemInfo();
        }
        v97 = g_charPID;
        itfMenuSetFlagMenu(v97, -1, 8, 0);
        itfMenuSetFlagMenu(g_charPID, -1, 16, 0);
        itfMenuSetFlagMenu(g_stockPID, -1, 8, 0);
        itfMenuSetFlagMenu(g_stockPID, -1, 16, 0);
        itfMenuSetFlagMenu(g_listPID, -1, 8, 0);
        itfMenuSetFlagMenu(g_listPID, -1, 2048, 0);
        itfMenuSetFlagMenu(g_charPID, -1, 2, 1);
        itfMenuSetFlagMenu(g_stockPID, -1, 2, 1);
        itfMenuSetFlag(g_charPID, 256, 0);
        itfMenuSetFlag(g_stockPID, 256, 0);
        cmpSetStockPanelActive(0, 0);
        itfMenuSetFlag(g_listPID, 8, 1);
        itfMenuSetSelectID(g_charPID, 0);
        itfMenuSetSelectID(g_stockPID, 0);
        cmpCharSelectSetDefault();
        g_step = 0;
        if (g_bEnd)
        {
          v102 = g_listPID;
          itfMenuCallEnd(v102);
        }
      }
      return 0;
    case 9:
      LogError("エフェクト終了待機::HD仕様では来ないはず", 0);
      return 0;
    case 0xA:
      v37 = get_Instance(0);
      ItfSortMenuActive(v37, 0, 0);
      useSpItem = 1;
      if (!g_scrPID)
        return (char)g_scrPID;
      if (dds3GetProcessStat(g_scrPID) != 3)
      {
        if (dds3GetProcessStat(g_scrPID))
        {
          return 0;
        }
      }
      g_scrPID = 0;
      v104 = ((char *)v104 + 104);
      LODWORD(v104[-1].s_arrSortItemID) = -1;
      g_step = 3;
      v107 = g_listPID;
      itfMenuSetFlagMenu(v107, -1, 2048, 0);
      v108 = g_itemNo;
      if (datCheckItem(v108, 1))
      {
LABEL_261:
        List = MakeList(61442);
        cmpUpdateUseItemEnebleDecide();
        return 0;
      }
      v114 = g_listPID;
      v115 = g_itemNo;
      itfMenuDelMenu(v114, v115);
      itfMenuSetFlagMenu(g_listPID, g_itemNo, 2, 0);
      goto LABEL_261;
    case 0xB:
      sklID = get_Item(sklItemConvTbl, g_itemNo, 0)->sklID;
      if (OmoideSklCheck(sklID))
        v42 = 12;
      else
        v42 = 11;
      cmpCmpGuideSet(v42, 0, 90);
      charPID = Work->charPID;
      itfMenuSetFlag(charPID, 2048, 1);
      itfMenuSetFlag(Work->stockPID, 2048, 1);
      if (!cmpChkEnd())
        return 0;
      v44 = cmpGetCharPID();
      StockPID = cmpGetStockPID();
      itfMenuSetFlag(v44, 2048, 0);
      itfMenuSetFlag(v44, 4096, 1);
      itfMenuSetFlag(StockPID, 2048, 0);
      itfMenuSetFlag(StockPID, 4096, 1);
      cmpSetTabFlag(0);
      cmpSetHelpFlag(0);
      g_GoldNoDspFlg = 0;
      *((u16 *)*((MethodInfo *)cmpItem + 2).virtualMethodPointer + 24) = 12801;
      cmpUpdateUseItemEnebleDecide();
      cmpUpdateSelectPosCharPID();
      cmpUpdateSelectNextPosCharPID2();
      cmpUpdateSelectNextPosStockPID();
      return 0;
    case 0xC:
      if (dds3FadeCheck())
        return 0;
      v72 = ++g_count;
      if (v72 < 20)
        return 0;
      v73 = get_Instance(0);
      ItfButtonGuideActive(v73, 0, 0);
      cmpCloseItemInfo();
      v75 = cmpGetCharPID();
      v76 = cmpGetStockPID();
      cmpSetTabFlag(1);
      cmpSetHelpFlag(1);
      (loc_1E7CC60)(1, 0);
      itfMenuSetFlag(v75, 2048, 1);
      itfMenuSetFlag(v75, 4096, 0);
      itfMenuSetFlag(v76, 2048, 1);
      itfMenuSetFlag(v76, 4096, 0);
      itfMenuSetFlag(g_listPID, 2048, 1);
      itfMenuSetFlag(g_listPID, 4096, 0);
      Delete(0);
      LOBYTE(g_scrPID) = 0;
      if (g_count < 40)
        return (char)g_scrPID;
      rstCmpItemGrowthStart();
      *(u16 *)&g_step = 13;
      return 0;
    case 0xD:
      if (rstProcessCheck())
        return 0;
      v78 = cmpGetCharPID();
      v79 = cmpGetStockPID();
      itfMenuSetFlag(v78, 2048, 0);
      itfMenuSetFlag(v78, 4096, 1);
      itfMenuSetFlag(v79, 2048, 0);
      itfMenuSetFlag(v79, 4096, 1);
      cmpSetTabFlag(0);
      cmpSetHelpFlag(0);
      g_GoldNoDspFlg = 0;
      cmpUpdateUseItemEnebleDecide();
      cmpCreateRankTextList();
      itfMenuSetDecideSE(g_charPID, -1, -1);
      itfMenuSetDecideSE(g_stockPID, -1, -1);
      ClassInit(itmUpdateMg);
      dds3FadeIn(0, 0, 0, 2u);
      v35 = 14;
LABEL_201:
LABEL_206:
      g_step = v35;
      return 0;
    case 0xE:
      if (dds3FadeCheck())
        return 0;
      v35 = 3;
      goto LABEL_206;
    case 0xF:
      cmpSortSetting(61442);
      Setup(61442, 0);
      LOBYTE(g_scrPID) = 0;
      g_step = 0;
      return (char)g_scrPID;
    case 0x10:
      cmpOpenItemInfo();
      if (tipsProcessCheck())
        return 0;
      v67 = g_charPID;
      itfMenuSetFlag(v67, 256, 0);
      itfMenuSetFlag(g_stockPID, 256, 0);
      itfMenuSetFlag(g_listPID, 256, 0);
      g_step = 1;
      v68 = Allocate(TipsCallBack);
      _ctor(v68, 0, Method_Project_cmpItem_TipsOffCallBack__, 0);
      remove_OffEvent(v68, 0);
      return 0;
    default:
      return (char)g_scrPID;
  }
}

// 0x1e68fb0
bool cmpUpdateBullet(void) {
  return 0;
}

// 0x1e68fc0
bool cmpUpdateThrow(void) {
  return 0;
}

// 0x1e68fd0
bool UpdateEvent(void) {
  return 0;
}

// 0x1e68fe0
bool cmpUpdateSword(void) {
  dds3ProcessID_t *CharPID;
  dds3ProcessID_t *StockPID;
  tagCMP_WORK *Work;
  Il2CppObject *ProcessData;
  Il2CppObject *v6;
  MenuSelectData *SaveSelectID;
  MenuSelectData *v12;
  void *v16;
  s32 v17;
  dds3ProcessID_t *v19;
  dds3ProcessID_t *v22;
  s32 v25;
  void *Instance;
  Il2CppObject *v28;
  void *v29;
  void *v31;
  MenuSelectData *SelectData;
  dds3ProcessID_t *v36;
  s32 SelectID;
  dds3ProcessID_t *v41;
  s32 v43;
  sdatUnitWork_t *para;
  void *v47;

  CharPID = cmpGetCharPID();
  StockPID = cmpGetStockPID();
  Work = cmpGetWork();
  ProcessData = dds3GetProcessData(g_mainPID);
  v6 = ProcessData;
  if (g_setSaveCsr)
    goto LABEL_12;
  SaveSelectID = GetSaveSelectID(Work->csrSave, 7, 0);
  if (SaveSelectID)
  {
    v12 = SaveSelectID;
    itfMenuSetSelectData(g_listPID, v12);
  }
  g_setSaveCsr = 1;
LABEL_13:
  g_step = (u8)g_step;
  if (g_step != 1)
    goto LABEL_14;
  goto LABEL_30;
LABEL_12:
  goto LABEL_13;
  if (g_step != 1)
  {
LABEL_14:
    if (g_step)
      return 0;
    if (g_count)
      return 0;
    Instance = get_Instance(0);
    ItfSortMenuActive(Instance, 1, 0);
    v28 = _get_Instance();
    DrawWeaponMenu(v28, 0);
    cmpSklTypeSet(0, 1);
    v29 = get_Instance(0);
    if (GetItfSortSysActive(v29, 0))
    {
      goto LABEL_70;
    }
    else
    {
      cmpCmpGuideSet(13, 0, 90);
LABEL_70:
      if (cmpChkEnd())
      {
LABEL_71:
        v31 = get_Instance(0);
        ItfSortMenuActive(v31, 0, 0);
        itfMenuSetFlag(CharPID, 2048, 0);
        itfMenuSetFlag(CharPID, 4096, 1);
        itfMenuSetFlag(StockPID, 2048, 0);
        itfMenuSetFlag(StockPID, 4096, 1);
        cmpSetTabFlag(0);
        cmpSetHelpFlag(0);
        g_GoldNoDspFlg = 0;
        SelectData = itfMenuCreateSelectData(Work->listPID);
        SetCsrSave(Work->csrSave, 7, SelectData, 0);
        *(u16 *)&g_count = 0;
        return 1;
      }
LABEL_91:
      v36 = g_listPID;
      SelectID = itfMenuGetSelectID(v36);
      if (g_oldSwordSelNo == SelectID)
      {
        goto LABEL_97;
      }
      v43 = SelectID - 144;
      g_equipNo = v43;
      para = GBWK->player->para;
      Start(para, 0);
      SetType(17039361, g_equipNo, 0);
      g_oldSwordSelNo = SelectID;
LABEL_97:
      v41 = g_listPID;
      if (itfMenuGetCtrlType(v41) == 4)
      {
        g_count = 1;
        v47 = get_Instance(0);
        ItfSortMenuActive(v47, 0, 0);
        cmpCmpGuideSet(14, 0, 90);
        itfMenuSetFlag(CharPID, 2048, 1);
        itfMenuSetFlag(StockPID, 2048, 1);
        cmpSetEvent(5);
      }
      return 0;
    }
    if (cmpChkEnd())
      goto LABEL_71;
    goto LABEL_91;
  }
LABEL_30:
  g_count = 0;
  v16 = get_Instance(0);
  ItfSortMenuActive(v16, 0, 0);
  if (cmpGetStatusStep() == 1)
    v17 = 15;
  else
    v17 = 14;
  cmpCmpGuideSet(v17, 0, 90);
  v19 = g_listPID;
  itfMenuSetFlag(v19, 256, 1);
  if (!CHECK_TRIG2(4096))
  {
    if (LOBYTE(v6[2].klass) != 10)
    {
      Work->stat &= ~0x20u;
      return 0;
    }
    v22 = g_listPID;
    itfMenuSetFlag(v22, 256, 0);
    g_step = 0;
    v25 = GBWK->player->swordno + 144;
    itfMenuSetFlagMenu(g_listPID, -1, 2, 1);
    itfMenuSetFlagMenu(g_listPID, v25, 2, 0);
    itfMenuStart(g_listPID);
    cmpSetTabFlag(1);
    cmpSetHelpFlag(1);
    cmpSetHelpDispFlag(0);
    g_GoldNoDspFlg = 1;
    cmpRaidouBackChange(6);
    TitleChange(5);
    SE(1);
    return 0;
  }
  cmpSetEvent(2);
  LODWORD(v6[8].monitor) = -1;
  return 0;
}

// 0x1e699c0
bool cmpUpdateJewel(void) {
  return 0;
}

// 0x1e699d0
bool cmpUpdateMaterial(void) {
  return 0;
}

// 0x1e699e0
bool Update(void) {
  cmpItemFunc_t v5;

  v5 = cmpItemFunc[CMP_MENU_ID_ROOT_MASK(g_menuID)];
  return (v5->invoke_impl)(v5->method_code, v5->method);
}

// 0x1e69ac0
void cmpLoadScript(void) {
  void *p_Dependent;
  void *Dependent_local;
  void *Asset;
  sdfBinary *v8;
  u8 *data;
  void *v12;
  s64 naturalAligment;
  void *v15;
  void *p_sklItemConvTbl;
  void *v19;
  void *v21;
  s64 v23;
  void *v24;
  void *p_sklItemCntTbl;
  void *v28;
  void *v30;
  s64 v32;
  void *v33;
  void *v34;
  void *p_sklItmCoefficientTbl;

  p_Dependent = &Dependent;
  Dependent_local = p_Dependent;
  Load(Dependent_local, cmpAssetName, cmpAssetName);
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  Asset = LoadAsset(_Ctrl_k__BackingField, cmpAssetName, "cmp_use_scr.bf", 0);
  v8 = Allocate(sdfBinary);
  _ctor(v8, Asset, 0);
  data = v8->data;
  g_pDatScr = data;
  v12 = LoadAsset(_Ctrl_k__BackingField, cmpAssetName, "CmpSklItemConversionTbl", 0);
  if (!v12)
  {
    sklItemConvTbl = 0;
    goto LABEL_38;
  }
  if (v12->klass->_2.naturalAligment >= (u32)naturalAligment)
  {
    if (v12->klass->_2.typeHierarchy[naturalAligment - 1] == Project_CmpSklItemConversionTbl)
      v15 = v12;
    else
      v15 = 0;
  }
  else
  {
    v15 = 0;
  }
  sklItemConvTbl = (void *)v15;
  p_sklItemConvTbl = &sklItemConvTbl;
  if (v12->klass->_2.naturalAligment < (u32)naturalAligment)
  {
    goto LABEL_38;
  }
  if (v12->klass->_2.typeHierarchy[naturalAligment - 1] == Project_CmpSklItemConversionTbl)
    v19 = v12;
  else
    v19 = 0;
LABEL_38:
  v21 = LoadAsset(_Ctrl_k__BackingField, cmpAssetName, "CmpSklItemTbl", 0);
  if (!v21)
  {
    sklItemCntTbl = 0;
    goto LABEL_56;
  }
  if (v21->klass->_2.naturalAligment >= (u32)v23)
  {
    if (v21->klass->_2.typeHierarchy[v23 - 1] == CmpSklItemCntTbl)
      v24 = v21;
    else
      v24 = 0;
  }
  else
  {
    v24 = 0;
  }
  sklItemCntTbl = (void *)v24;
  p_sklItemCntTbl = &sklItemCntTbl;
  if (v21->klass->_2.naturalAligment < (u32)v23)
  {
    goto LABEL_56;
  }
  if (v21->klass->_2.typeHierarchy[v23 - 1] == CmpSklItemCntTbl)
    v28 = v21;
  else
    v28 = 0;
LABEL_56:
  v30 = LoadAsset(_Ctrl_k__BackingField, cmpAssetName, "CmpSklItmCoefficientTbl", 0);
  if (v30)
  {
    if (v30->klass->_2.naturalAligment >= (u32)v32)
    {
      if (v30->klass->_2.typeHierarchy[v32 - 1] == CmpSklItmCoefficientTbl)
        v33 = v30;
      else
        v33 = 0;
    }
    else
    {
      v33 = 0;
    }
    sklItmCoefficientTbl = (void *)v33;
    p_sklItmCoefficientTbl = &sklItmCoefficientTbl;
    if (v30->klass->_2.naturalAligment >= (u32)v32)
    {
      if (v30->klass->_2.typeHierarchy[v32 - 1] == CmpSklItmCoefficientTbl)
        v34 = v30;
      else
        v34 = 0;
    }
    else
    {
      v34 = 0;
    }
  }
  else
  {
    v34 = 0;
    sklItmCoefficientTbl = 0;
    p_sklItmCoefficientTbl = &sklItmCoefficientTbl;
  }
  Unload(Dependent, cmpAssetName, 0);
}

// 0x1e6a030
void cmpFreeScript(void) {
  g_pDatScr = 0;
}

// 0x1e6a0c0
void cmpStart(void) {
  Il2CppObject *v1;
  ItemMenuData *itmMenuData_local;
  void *v6;
  Il2CppObject *v7;

  v1 = Allocate(ItemMenuData);
  _ctor(v1, 0);
  itmMenuData = (ItemMenuData *)v1;
  itmMenuData_local = itmMenuData;
  *(u64 *)&itmMenuData_local->oldTab = 0;
  v6 = Allocate(System_Collections_Generic_Dictionary_cmpItem_ItemMenuBufType__itf_Menu_t_);
  object____ctor(v6);
  itmMenuData_local->menuBuff = v6;
  v7 = Allocate(ItemUpdateManager);
  _ctor(v7, 0);
  ClassInit(v7);
  itmUpdateMg = (ItemUpdateManager *)v7;
}

// 0x1e6a2b0
void End(void) {
  FreeSpriteHnd();
  if (g_scrPID)
  {
    dds3KillProcess(g_scrPID, 0);
    g_scrPID = 0;
  }
  itmUpdateMg = 0;
}

// 0x1e6a3e0
s32 cmpChkMessageDraw(void) {
  scrHandle_t *v1;
  Il2CppObject *ProcessData;
  s32 monitor_high;

  v1 = Allocate(scrHandle_t);
  _ctor(v1, 0);
  if (!g_scrPID)
    return 0;
  if (!dds3ExistProcess(g_scrPID))
    return 0;
  ProcessData = dds3GetProcessData(g_scrPID);
  if (!ProcessData)
  monitor_high = HIDWORD(ProcessData[6].monitor);
  return itfMesMngGetStat(monitor_high) != 0;
}

// 0x1e6a5e0
s32 cmpGetItemIDFromSortNo(s32 a_sortNo) {
  if (a_sortNo < 0)
    return -1;
  if (SLODWORD(s_arrSortItemID->max_length) <= a_sortNo)
    return -1;
  return s_arrSortItemID[a_sortNo];
}

// 0x1e6a6b0
s32 cmpCommand_CHECK_USE_TETYOU(void) {
  u8 v2;

  v2 = cmpChkUseTETYOU();
  scrSetIntReturnValue(v2);
  return 1;
}

// 0x1e6a770
s32 cmpCommand_CHECK_MEGANE(void) {
  s32 megane;

  megane = GBWK->player->megane;
  scrSetIntReturnValue(megane);
  return 1;
}

// 0x1e6a880
s32 cmpCommand_CHECK_SEIKATU(void) {
  s32 seikatu;

  seikatu = GBWK->player->seikatu;
  scrSetIntReturnValue(seikatu);
  return 1;
}

// 0x1e6a990
s32 cmpCommand_SEIKATU_SET(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  GBWK->player->seikatu = IntPara == 1;
  return 1;
}

// 0x1e6aa40
s32 cmpCommand_MEGANE_SET(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  GBWK->player->megane = IntPara == 1;
  return 1;
}
