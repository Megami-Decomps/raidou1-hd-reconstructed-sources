#include "types.h"
#include "BST.h"
#include "BSTF.h"
#include "cmpfile.h"
#include "cmpkuda.h"
#include "cmpmain.h"
#include "cmpmisc.h"
#include "dat.h"
#include "dds3kernelcore.h"
#include "itf.h"
#include "localize.h"
#include "raijindlc.h"
#include "sbtlsub.h"
#include "sdat.h"

#define CAMPFLDSUM_MARK -15
#define CAMPLISTGAUGESPRNO 13
#define BLANK_STOCK 999
#define EMPTY_STOCK 9999

typedef enum {
    CMP_PARTY_PANEL_X = 219,
    CMP_PARTY_PANEL_Y = 27,
    CMP_PARTY_PANEL_W = 293,
    CMP_PARTY_PANEL_H = 25,
    CMP_PARTY_PANEL_FX = 14,
    CMP_PARTY_PANEL_FY = 2,
} CMP_PARTY_PANEL;

typedef enum {
    CMPPLAYERLIST_X = 219,
    CMPPLAYERLIST_Y = 27,
} CMPPLAYERLIST;

typedef enum {
    MARK1 = -15,
    MARK2 = -15,
} CAMPBTLSUM;

typedef enum {
    GAUGE_X = 238,
    GAUGE_Y = 16,
    NUM_X = 246,
    NUM_Y = 1,
} CAMPRAIDOMAG;

typedef enum {
    CAMPLVNUM_X = 171,
    CAMPLVNUM_Y = 4,
} CAMPLVNUM;

typedef enum {
    CAMPBSTICON_X = 127,
    CAMPBSTICON_Y = 1,
} CAMPBSTICON;

typedef enum {
    CAMPHPGAUGE_X = 195,
    CAMPHPGAUGE_Y = 16,
} CAMPHPGAUGE;

typedef enum {
    CAMPHPNUM_X = 203,
    CAMPHPNUM_Y = 1,
} CAMPHPNUM;

typedef struct Menu_t Menu_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct sprHandle_t sprHandle_t;

// 0x1f5fec0
bool cmpChkDevilStockExist(s32 a_stockID) {
  sdatUnitWork_t *v4;

  if ((u32)a_stockID > 0x1F)
    return 0;
  v4 = GBWK->player->stock_id[a_stockID];
  return (v4->flag & 1) != 0 && v4->devilid != 0;
}

// 0x1f5ff80
bool cmpDelDevilStock(s32 a_stockID) {
  sdatUnitWork_t *v5;
  u32 flag;

  if ((u32)a_stockID > 0x1F)
    return 0;
  v5 = GBWK->player->stock_id[a_stockID];
  flag = v5->flag;
  v5->devilid = 0;
  v5->flag = flag & 0xFFFFFFFE;
  return 1;
}

// 0x1f60030
s32 cmpGetDevilStockDevilID(s32 a_stockID) {
  sdatUnitWork_t *v4;
  s32 devilid;

  if ((u32)a_stockID > 0x1F)
    return -1;
  v4 = GBWK->player->stock_id[a_stockID];
  if ((v4->flag & 1) == 0)
    return -1;
  devilid = (u16)v4->devilid;
  if (!devilid)
    return -1;
  return (s16)devilid;
}

// 0x1f60150
BST cmpGetBstNo(BSTF a_bst) {
  s32 v2;
  s32 v3;
  u32 v4;

  if ((a_bst & 0x10000) != 0)
    v2 = 16;
  else
    v2 = 22;
  if ((a_bst & 0x800) != 0)
    v3 = 11;
  else
    v3 = v2;
  if ((a_bst & 0x400) != 0)
    v4 = 10;
  else
    v4 = v3;
  if ((a_bst & 0x20000) != 0)
    return 17;
  else
    return v4;
}

// 0x1f551d0
void cmpUpdateBulletNum(void) {
  sdatPlayerUnitWork_t *player;
  s64 bulletno;

  player = GBWK->player;
  bulletno = (u32)player->bulletno;
  if ((s32)bulletno < 1)
  {
    player->hgunnum = 0;
  }
  else
  {
    player = GBWK->player;
    player->hgunnum = player->item[bulletno];
  }
}

// 0x1f60190
void cmpPartyDrawFunc(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate) {
  tagCMP_WORK *Work;
  dds3ProcessID_t *p_charPID;
  Menu_t *ProcessData;
  MenuMover_t *mv;
  s64 v19;
  s64 max_length;
  MenuMover_t *m_Items;
  s32 v22;
  MenuCB_tag *cb;
  Il2CppObject *Instance;
  s16 *stack_p;
  s64 v30;
  u32 v31;
  Il2CppObject *v32;
  MenuCB_tag *v33;
  Il2CppObject *v34;
  sdatPlayerUnitWork_t *player;
  s32 v37;
  char v38;
  sdatUnitWork_t *p_para;
  sdatPlayerUnitWork_t *v41;
  s32 v42;
  Il2CppObject *v43;
  Il2CppObject *v44;
  sdatUnitWork_t *v46;
  dds3ProcessID_t *charPID;
  sdatPlayerUnitWork_t *v56;
  sdatUnitWork_t *stock_id;
  s64 v58;
  sdatUnitWork_t *v62;
  sdatPlayerUnitWork_t *v64;
  sdatUnitWork_t *v65;
  bool v66;
  char v67;
  sdatParaWork_t *now;
  s32 maxhp;
  s32 hp;
  Il2CppObject *v71;
  Il2CppObject *v72;
  char *v73;
  u32 v74;
  Il2CppObject *v75;
  u8 v76;
  s32 v77;
  sdatPlayerUnitWork_t *v79;
  sdatUnitWork_t *v80;
  s64 v81;
  sdatPlayerUnitWork_t *v83;
  s32 mag;
  s32 maxmag;
  sdatPlayerUnitWork_t *updateDrawPlayer;
  sdatPlayerUnitWork_t *playerUnit;
  sdatPlayerUnitWork_t *v88;
  s32 v89;
  s32 v90;
  Il2CppObject *v91;
  Il2CppObject *v92;
  sdatPlayerUnitWork_t *v94;
  Il2CppObject *v95;
  Il2CppObject *v96;
  char *v97;
  Il2CppObject *v98;
  Il2CppObject *v100;
  char *v101;
  Il2CppObject *v102;
  sdatPlayerUnitWork_t *v104;
  sdatUnitWork_t *v105;
  s64 v106;
  s32 v108;
  s32 badstatus;
  s32 v110;
  u32 v111;
  sdatPlayerUnitWork_t *v114;
  void *monitor;
  sdatUnitWork_t *v116;
  u32 v117;
  Il2CppObject *v118;
  void *v119;
  s32 devilid;
  DEVILDATA_WORK *DevilData;
  bool v123;
  Il2CppObject *v124;
  s32 v125;
  sdatUnitWork_t *pUnit;
  char *str0;
  sdatUnitWork_t *UpdateUnit;
  s32 a_za;
  u8 v130;
  s32 v131;
  sprHandle_t *SpriteHnd;
  s32 v134;
  s32 v135;
  s32 data;

  SpriteHnd = cmpGetSpriteHnd(0);
  Work = cmpGetWork();
  p_charPID = &Work->charPID;
  ProcessData = dds3GetProcessData(p_charPID);
  if (!ProcessData)
    goto LABEL_13;
  goto LABEL_11;
  if (!ProcessData)
LABEL_11:
LABEL_13:
  dds3GetProcessData(&Work->stockPID);
  mv = ProcessData->mv;
  v131 = a_x;
  if ((s32)mv->max_length < 1)
  {
    v22 = -1;
    v130 = a_alphaRate;
    goto LABEL_20;
  }
  else
  {
    v19 = 0;
    max_length = (u32)mv->max_length;
    m_Items = mv;
    v22 = -1;
    while (1)
    {
      cb = m_Items[v19]->cb;
      if (cb)
      {
        if (cb->id == a_id)
          break;
      }
      if (max_length == ++v19)
        goto LABEL_19;
    }
    v22 = v19;
LABEL_19:
    v130 = a_alphaRate;
LABEL_20:
    goto LABEL_21;
  }
LABEL_21:
  if (!cmpGetWork())
    return;
  if (!cmpGetWork()->charPID)
    return;
  if (Work->stockPanelActive == Work->changeActivePanel)
  {
    a_za = a_z;
    datGetStockDevilNums(0);
    Instance = _get_Instance();
    stack_p = GBWK->player->stack_p;
    PartyInfoDraw(Instance[6].monitor, stack_p[0], stack_p[1], 0);
    v30 = v22;
    if ((ProcessData->mv[v30]->cb->attrUnity & 8) != 0)
      v31 = 1;
    else
      v31 = a_fontColor;
    v32 = _get_Instance();
    v33 = ProcessData->mv[v30]->cb;
    PartyListTextDraw(v32[6].monitor, v22, v33->str, v31, v33->tag, 0);
    v34 = _get_Instance();
    PartyListCursorDraw(v34[6].monitor, v22, ProcessData->mv[v30]->cb->attrUnity, 0);
    switch (a_id)
    {
      case 1:
        player = GBWK->player;
        v37 = (u16)player->stack_p[0];
        if (v37 != 0xFFFF)
        {
          player = GBWK->player;
          LOWORD(v37) = player->stack_p[0];
          v38 = 1;
          v125 = 0;
          p_para = &player->stock_id[(s16)v37];
          break;
        }
LABEL_53:
        v43 = _get_Instance();
        TopAttrIconDraw(v43[6].monitor, v22, 0, 0);
        v44 = _get_Instance();
        TopHukidasiIconDraw(v44[6].monitor, v22, 0, 0, 0);
        return;
      case 3:
        return;
      case 2:
        v41 = GBWK->player;
        v42 = (u16)v41->stack_p[1];
        if (v42 == 0xFFFF)
          goto LABEL_53;
        v41 = GBWK->player;
        LOWORD(v42) = v41->stack_p[1];
        v38 = 1;
        v125 = 1;
        p_para = &v41->stock_id[(s16)v42];
        break;
      default:
        if (a_id > 2)
          return;
        v38 = 0;
        v125 = 0;
        p_para = &GBWK->player->para;
        break;
    }
    v46 = p_para;
    if (itmUpdateMg)
    {
      UpdateUnit = GetUpdateUnit(itmUpdateMg, v46->devilid, v46->uniq_code, 0);
      goto LABEL_63;
    }
    else
    {
      UpdateUnit = 0;
LABEL_63:
      if (cmpGetWork())
      {
        charPID = cmpGetWork()->charPID;
        goto LABEL_70;
      }
      charPID = 0;
LABEL_70:
      itfMenuGetFlashCount(charPID, a_id);
      cmpGetMarkID();
      if ((v38 & 1) != 0)
      {
        if (a_id == 1)
        {
          v56 = GBWK->player;
          stock_id = v56->stock_id;
          v58 = v56->stack_p[0];
        }
        else
        {
          if (!v125)
          {
            v65 = 0;
LABEL_92:
            pUnit = v65;
            if (itmUpdateMg)
              v66 = UpdateUnit == 0;
            else
              v66 = 1;
            if (v66)
            {
              v67 = 1;
            }
            else
            {
              v65 = UpdateUnit;
              v67 = 0;
            }
            now = v65->now;
            hp = now->hp;
            maxhp = now->maxhp;
            itfCalcSpriteWidth(SpriteHnd, 157, hp, maxhp);
            v71 = _get_Instance();
            HpGaugeDraw(v71[6].monitor, a_id, v22, hp, maxhp, 0, 0);
            data = hp;
            v72 = Box(s32, &data);
            v73 = Format("{0,3:d}", v72, 0);
            str0 = Concat_54766928(0, v73, 0);
            v74 = a_fontColor;
            if (a_fontColor == -1600273536)
            {
              v74 = 1967865216;
              if (maxhp >= 1)
              {
                if (!datCheckDying(pUnit))
                {
                  if (100 * hp / maxhp <= 49)
                    v74 = -1264556928;
                  else
                    v74 = -1600273536;
                }
              }
            }
            v75 = _get_Instance();
            PartyHpDraw(v75[6].monitor, a_id, hp, v74, ProcessData, 0);
            if (a_id)
            {
              v76 = v130;
              if (a_id == 1)
              {
                v77 = a_y;
                v79 = GBWK->player;
                v80 = v79->stock_id;
                v81 = v79->stack_p[0];
                goto LABEL_124;
              }
              v77 = a_y;
              if (v125)
              {
                v94 = GBWK->player;
                v80 = v94->stock_id;
                v81 = v94->stack_p[1];
LABEL_124:
                hp = v80[v81]->level;
                if ((v67 & 1) != 0)
                  goto LABEL_133;
LABEL_132:
                hp = UpdateUnit->level;
                goto LABEL_133;
              }
              if ((v67 & 1) == 0)
                goto LABEL_132;
            }
            else
            {
              v76 = v130;
              v83 = GBWK->player;
              mag = v83->mag;
              maxmag = v83->maxmag;
              if (itmUpdateMg && (updateDrawPlayer = itmUpdateMg->updateDrawPlayer) != 0)
              {
                ClassCopy(Work->playerUnit, updateDrawPlayer, 0);
                playerUnit = Work->playerUnit;
                datCalcMagMaxPlayerUnit(playerUnit);
                v88 = Work->playerUnit;
                v89 = v88->mag;
                v90 = v88->maxmag;
                v91 = _get_Instance();
                MagGaugeDraw(v91[6].monitor, v89, v90, 1, 0);
                v92 = _get_Instance();
                MagDraw(v92[6].monitor, v89, a_fontColor, 0);
                v77 = a_y;
              }
              else
              {
                itfCalcSpriteWidth(SpriteHnd, 166, mag, maxmag);
                v95 = _get_Instance();
                MagGaugeDraw(v95[6].monitor, mag, maxmag, 1, 0);
                v135 = mag;
                v96 = Box(s32, &v135);
                v97 = Format("{0,4:d}", v96, 0);
                str0 = Concat_54766928(str0, v97, 0);
                v98 = _get_Instance();
                MagDraw(v98[6].monitor, mag, a_fontColor, 0);
                v77 = a_y;
              }
              hp = GBWK->player->para->level;
              if ((v67 & 1) == 0)
                goto LABEL_132;
            }
LABEL_133:
            v134 = hp;
            v100 = Box(s32, &v134);
            v101 = Format("{0,2:d}", v100, 0);
            Concat_54766928(str0, v101, 0);
            v102 = _get_Instance();
            PartyLvDraw(v102[6].monitor, a_id, hp, a_fontColor, ProcessData, 0);
            if (a_id)
            {
              if (a_id == 1)
              {
                v104 = GBWK->player;
                v105 = v104->stock_id;
                v106 = v104->stack_p[0];
              }
              else
              {
                if ((v125 & 1) == 0)
                {
                  badstatus = 0;
                  v108 = v77 + 1;
                  goto LABEL_155;
                }
                v114 = GBWK->player;
                v105 = v114->stock_id;
                v106 = v114->stack_p[1];
              }
              v108 = v77 + 1;
              badstatus = v105[v106]->badstatus;
              if ((badstatus & 0x20000) == 0)
              {
LABEL_148:
                if ((badstatus & 0x400) != 0)
                {
                  v111 = 10;
                  goto LABEL_158;
                }
                if ((badstatus & 0x800) != 0)
                {
                  v111 = 11;
                  goto LABEL_158;
                }
LABEL_155:
                if ((badstatus & 0x10000) != 0)
                  v111 = 16;
                else
                  v111 = 22;
LABEL_158:
                v110 = 1;
                goto LABEL_160;
              }
            }
            else
            {
              v108 = v77 + 1;
              badstatus = GBWK->player->para->badstatus;
              if ((badstatus & 0x20000) == 0)
                goto LABEL_148;
            }
            v110 = 0;
            v111 = 17;
LABEL_160:
            itfIconDrawBadStatus(v131 + 127, v108, a_za, v76, v111, 108);
            monitor = _get_Instance()[6].monitor;
            if (v110)
            {
              v116 = pUnit;
              if ((badstatus & 0x400) != 0)
              {
                v117 = 10;
              }
              else if ((badstatus & 0x800) != 0)
              {
                v117 = 11;
              }
              else if ((badstatus & 0x10000) != 0)
              {
                v117 = 16;
              }
              else
              {
                v117 = 22;
              }
            }
            else
            {
              v117 = 17;
              v116 = pUnit;
            }
            TopBstIconDraw(monitor, a_id, v22, v117, v116, 0);
            v118 = _get_Instance();
            TopFaceIconDraw(v118[6].monitor, a_id, v22, v116->devilid, 0);
            v119 = _get_Instance()[6].monitor;
            devilid = v116->devilid;
            DevilData = sBtlGetDevilData(devilid, -1);
            TopAttrIconDraw(v119, v22, DevilData->kuda_id, 0);
            v123 = v116->DevilReportStok->_size > 0;
            v124 = _get_Instance();
            TopHukidasiIconDraw(v124[6].monitor, v22, v123, 0, 0);
            return;
          }
          v64 = GBWK->player;
          stock_id = v64->stock_id;
          v58 = v64->stack_p[1];
        }
        v62 = &stock_id[v58];
LABEL_91:
        v65 = v62;
        goto LABEL_92;
      }
      v62 = &GBWK->player->para;
      goto LABEL_91;
    }
    goto LABEL_63;
  }
}

// 0x1f61000
void cmpStockDrawFunc(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate) {
  sprHandle_t *SpriteHnd;
  tagCMP_WORK *Work;
  dds3ProcessID_t *p_stockPID;
  Menu_t *ProcessData;
  MenuMover_t *mv;
  s64 v19;
  s64 max_length;
  MenuMover_t *m_Items;
  s32 v22;
  MenuCB_tag *cb;
  u8 v25;
  s32 drwMax;
  Il2CppObject *Instance;
  Il2CppObject *v31;
  Il2CppObject *v32;
  s32 StockDevilNums;
  Il2CppObject *v34;
  Il2CppObject *v35;
  Il2CppObject *v36;
  s64 v37;
  u32 v38;
  Il2CppObject *v39;
  MenuCB_tag *v40;
  Il2CppObject *v41;
  Il2CppObject *v42;
  Il2CppObject *v43;
  Il2CppObject *v44;
  sdatUnitWork_t *stock_id;
  sdatUnitWork_t *v48;
  sdatUnitWork_t *v52;
  s32 devilid;
  bool v54;
  Il2CppObject *v55;
  bool v56;
  s32 v57;
  sdatUnitWork_t *v58;
  sdatParaWork_t *now;
  s32 hp;
  s32 maxhp;
  Il2CppObject *v62;
  Il2CppObject *v63;
  char *v64;
  u32 v65;
  Il2CppObject *v66;
  sdatUnitWork_t *v68;
  s32 level;
  Il2CppObject *v70;
  s32 badstatus;
  u32 v73;
  Il2CppObject *v74;
  void *monitor;
  u32 v76;
  Il2CppObject *v77;
  void *v78;
  s32 v79;
  Il2CppObject *v80;
  s32 v81;
  sdatUnitWork_t *pUnit;
  sdatUnitWork_t *UpdateUnit;
  s32 v84;
  s32 data;

  SpriteHnd = cmpGetSpriteHnd(0);
  Work = cmpGetWork();
  p_stockPID = &Work->stockPID;
  ProcessData = dds3GetProcessData(p_stockPID);
  if (!ProcessData)
    goto LABEL_13;
  goto LABEL_11;
  if (!ProcessData)
LABEL_11:
LABEL_13:
  mv = ProcessData->mv;
  v84 = a_x;
  if ((s32)mv->max_length < 1)
  {
    v22 = -1;
    v25 = a_alphaRate;
    drwMax = ProcessData->drwMax;
    goto LABEL_20;
  }
  else
  {
    v19 = 0;
    max_length = (u32)mv->max_length;
    m_Items = mv;
    v22 = -1;
    while (1)
    {
      cb = m_Items[v19]->cb;
      if (cb)
      {
        if (cb->id == a_id)
          break;
      }
      if (max_length == ++v19)
        goto LABEL_19;
    }
    v22 = v19;
LABEL_19:
    v25 = a_alphaRate;
    drwMax = ProcessData->drwMax;
LABEL_20:
    goto LABEL_21;
  }
LABEL_21:
  if (!cmpGetWork())
    return;
  if (!cmpGetWork()->charPID)
    return;
  if (Work->stockPanelActive == Work->changeActivePanel && !Work->dvlReportMachine)
  {
    if (a_id == 999)
    {
      Instance = _get_Instance();
      (*(**((u64 **)Instance[6].monitor + 12) + 376))(*((u64 *)Instance[6].monitor + 12), 0, 0, 0, *(u64 *)(**((u64 **)Instance[6].monitor + 12) + 384));
      v31 = _get_Instance();
      StockAllClear(v31[6].monitor, 0, 0);
      v32 = _get_Instance();
      StockLvHpTextDraw(v32[6].monitor, 0, 0);
    }
    else
    {
      StockDevilNums = datGetStockDevilNums(0);
      if (StockDevilNums <= a_id)
      {
        v34 = _get_Instance();
        StockEmptyDraw(v34[6].monitor, v22, 0);
        if (!v22)
        {
          v35 = _get_Instance();
          StockLvHpTextDraw(v35[6].monitor, 0, 0);
        }
      }
      v36 = _get_Instance();
      StockAllClear(v36[6].monitor, drwMax, 0);
      v37 = v22;
      if ((ProcessData->mv[v37]->cb->attrUnity & 8) != 0)
        v38 = 1;
      else
        v38 = a_fontColor;
      v39 = _get_Instance();
      v40 = ProcessData->mv[v37]->cb;
      StockListTextDraw(v39[6].monitor, v22, v40->str, v38, v40->tag, 0);
      v41 = _get_Instance();
      StockListCursorDraw(v41[6].monitor, v22, ProcessData->mv[v37]->cb->attrUnity, 0);
      if (StockDevilNums > a_id)
      {
        v42 = _get_Instance();
        StockInfoDraw(v42[6].monitor, v22, 0);
      }
      v43 = _get_Instance();
      StockFaceDraw(v43[6].monitor, v22, 0);
      v44 = _get_Instance();
      (*(**((u64 **)v44[6].monitor + 12) + 376))(*((u64 *)v44[6].monitor + 12), (u32)ProcessData->drwDefNum, (u32)ProcessData->selMax, (u32)ProcessData->topNo[ProcessData->nowHierarchy], *(u64 *)(**((u64 **)v44[6].monitor + 12) + 384));
      if (StockDevilNums > a_id)
      {
        stock_id = GBWK->player->stock_id;
        v48 = stock_id[a_id];
        if (itmUpdateMg)
          UpdateUnit = GetUpdateUnit(itmUpdateMg, v48->devilid, v48->uniq_code, 0);
        else
          UpdateUnit = 0;
        v52 = GBWK->player->stock_id[a_id];
        devilid = v52->devilid;
        v54 = DlcDevilSelCheck(devilid);
        if (!v22 && (v52->flag & 1) != 0)
        {
          v55 = _get_Instance();
          StockLvHpTextDraw(v55[6].monitor, 1, 0);
        }
        if (v54)
        {
          pUnit = v52;
          if (itmUpdateMg)
            v56 = UpdateUnit == 0;
          else
            v56 = 1;
          v57 = v56;
          if (v56)
            v58 = v52;
          else
            v58 = UpdateUnit;
          v81 = v57;
          now = v58->now;
          hp = now->hp;
          maxhp = now->maxhp;
          itfCalcSpriteWidth(SpriteHnd, 157, hp, maxhp);
          v62 = _get_Instance();
          HpGaugeDraw(v62[6].monitor, a_id, v22, hp, maxhp, 1, 0);
          data = hp;
          v63 = Box(s32, &data);
          v64 = Format("{0,3:d}", v63, 0);
          Concat_54766928(0, v64, 0);
          v65 = a_fontColor;
          if (a_fontColor == -1600273536)
          {
            v65 = 1967865216;
            if (maxhp >= 1)
            {
              if (!datCheckDying(v52))
              {
                if (100 * hp / maxhp <= 49)
                  v65 = -1264556928;
                else
                  v65 = -1600273536;
              }
            }
          }
          v66 = _get_Instance();
          StockHpDraw(v66[6].monitor, a_id, v22, hp, v65, ProcessData, 0);
          v68 = GBWK->player->stock_id[a_id];
          if (!v81)
            v68 = UpdateUnit;
          level = v68->level;
          v70 = _get_Instance();
          StockLvDraw(v70[6].monitor, a_id, v22, level, a_fontColor, ProcessData, 0);
          badstatus = GBWK->player->stock_id[a_id]->badstatus;
          if ((badstatus & 0x20000) != 0)
          {
            v73 = 17;
          }
          else if ((badstatus & 0x400) != 0)
          {
            v73 = 10;
          }
          else if ((badstatus & 0x800) != 0)
          {
            v73 = 11;
          }
          else if ((badstatus & 0x10000) != 0)
          {
            v73 = 16;
          }
          else
          {
            v73 = 22;
          }
          itfIconDrawBadStatus(v84 + 127, a_y + 1, a_z, v25, v73, 108);
          monitor = _get_Instance()[6].monitor;
          if ((badstatus & 0x20000) != 0)
          {
            v76 = 17;
          }
          else if ((badstatus & 0x400) != 0)
          {
            v76 = 10;
          }
          else if ((badstatus & 0x800) != 0)
          {
            v76 = 11;
          }
          else if ((badstatus & 0x10000) != 0)
          {
            v76 = 16;
          }
          else
          {
            v76 = 22;
          }
          StockTopBstIconDraw(monitor, a_id, v22, v76, pUnit, 0);
          v77 = _get_Instance();
          StockTopFaceIconDraw(v77[6].monitor, a_id, v22, pUnit->devilid, 0);
          v78 = _get_Instance()[6].monitor;
          v79 = sub_1B6D720(pUnit->devilid);
          StockTopAttrIconDraw(v78, v22, v79, 0);
          LOBYTE(v78) = pUnit->DevilReportStok->_size > 0;
          v80 = _get_Instance();
          TopHukidasiIconDraw(v80[6].monitor, v22, (bool)v78, 1, 0);
        }
        else
        {
          v74 = _get_Instance();
          StockNoDlcDraw(v74[6].monitor, v22, 0);
        }
      }
    }
  }
}

// 0x1f619b0
s32 cmpCharMoveFunc(Menu_t *wk, MENU_KEY_TYPE _key, bool _loop) {
  tagCMP_WORK *Work;
  tagCMP_WORK *v10;
  tagCMP_WORK *v12;
  bool v14;
  tagCMP_WORK *v16;
  tagCMP_WORK *v18;

  if (key == 3)
  {
    Work = cmpGetWork();
    if (!Work)
      return (s32)Work;
    v16 = Work;
    LODWORD(Work) = 0;
    if (v16->stockPanelActive != 1 || !loop)
      return (s32)Work;
    if (cmpGetSelectStockPIDSelMaxCnt(0, 0) < 0)
      goto LABEL_47;
    v18 = cmpGetWork();
    if (!v18)
      goto LABEL_44;
    goto LABEL_43;
    if (!v18)
    {
LABEL_44:
      v14 = 0;
      goto LABEL_30;
    }
LABEL_43:
    v18->changeActivePanel = 2;
    SE(3);
    goto LABEL_44;
  }
  if (key != 1)
    goto LABEL_47;
  Work = cmpGetWork();
  if (!Work)
    return (s32)Work;
  v10 = Work;
  LODWORD(Work) = 0;
  if (v10->stockPanelActive == 1 && loop)
  {
    if ((cmpGetSelectStockPIDSelMaxCnt(1, 0) & 0x80000000) == 0)
    {
      v12 = cmpGetWork();
      if (!v12)
        goto LABEL_28;
      goto LABEL_27;
      if (!v12)
      {
LABEL_28:
        v14 = 1;
LABEL_30:
        cmpUpdateSelectPosStockPIDSelMax(v14);
        LODWORD(Work) = 1;
        return (s32)Work;
      }
LABEL_27:
      v12->changeActivePanel = 2;
      SE(3);
      goto LABEL_28;
    }
LABEL_47:
    LODWORD(Work) = 0;
  }
  return (s32)Work;
}

// 0x1f5c990
dds3ProcessID_t *cmpPartyListProcessStart(void) {
  dds3ProcessID_t *v1;
  dds3ProcessID_t *v2;
  itfMenuMoveFunc v4;

  v1 = Allocate(dds3ProcessID_t);
  _ctor(v1, 0);
  v2 = itfMenuProcessStart();
  cmpPartyListMake(v2);
  v4 = Allocate(itfMenuMoveFunc);
  _ctor(v4, 0, Method_Project_cmpMisc_CharMoveFunc__, 0);
  itfMenuSetMoveFunc(v2, v4);
  return v2;
}

// 0x1f622b0
s32 cmpStockMoveFunc(Menu_t *wk, MENU_KEY_TYPE _key, bool _loop) {
  tagCMP_WORK *v7;
  tagCMP_WORK *Work;
  s32 v11;
  tagCMP_WORK *v14;
  tagCMP_WORK *v18;

  if (key == 3)
  {
    Work = cmpGetWork();
    if (!Work)
      return 0;
    v11 = 0;
    if (Work->stockPanelActive != 2 || !loop)
      return v11;
    if (cmpGetSelectCharPIDSelMaxCnt(0) < 0)
      return 0;
    v18 = cmpGetWork();
    if (!v18)
    {
LABEL_42:
      cmpUpdateSelectPosCharPIDSelMax(0);
      cmpUpdateSelectPosStockPIDSelMax(0);
      return 0;
    }
    v18->changeActivePanel = 1;
    goto LABEL_42;
  }
  if (key != 1)
    return 0;
  v7 = cmpGetWork();
  if (!v7)
    return 0;
  v11 = 0;
  if (v7->stockPanelActive != 2 || !loop)
    return v11;
  if (cmpGetSelectCharPIDSelMaxCnt(1) < 0)
    return 0;
  cmpUpdateSelectPosCharPIDSelMax(1);
  v14 = cmpGetWork();
  v11 = 1;
  if (!v14)
    return v11;
  v14->changeActivePanel = 1;
  SE(3);
  return 1;
}

// 0x1f5cb10
dds3ProcessID_t *cmpStockListProcessStart(void) {
  dds3ProcessID_t *v1;
  dds3ProcessID_t *v2;
  itfMenuMoveFunc v4;

  v1 = Allocate(dds3ProcessID_t);
  _ctor(v1, 0);
  v2 = itfMenuProcessStart();
  cmpStockListMake(v2, 1);
  v4 = Allocate(itfMenuMoveFunc);
  _ctor(v4, 0, Method_Project_cmpMisc_StockMoveFunc__, 0);
  itfMenuSetMoveFunc(v2, v4);
  return v2;
}

// 0x1f62e00
s32 cmpPartyAnimFunc(s32 mode) {
  Il2CppObject *Instance;

  if ((u32)mode > 1)
    return 1;
  Instance = _get_Instance();
  AnimSet(Instance[6].monitor, mode, 1, 1, 0);
  return 1;
}

// 0x1f62e90
s32 cmpStockAnimFunc(s32 mode) {
  return 1;
}

// 0x1f61ce0
void cmpPartyListMake(dds3ProcessID_t *PID) {
  itfMoverFunc_t v4;
  char *v5;
  char *v6;
  itfMenuDrawFunc_t v7;
  u32 v10;
  sdatUnitWork_t *v12;
  s32 DevilStockDevilID;
  char *v14;
  char *v15;
  dds3ProcessID_t *v16;
  char *v17;
  char *v18;
  char *LocalizeText;
  itfMenuDrawFunc_t v20;
  u32 v22;
  sdatUnitWork_t *v24;
  s32 v25;
  char *v26;
  char *v27;
  dds3ProcessID_t *v28;
  char *v29;
  char *v30;
  char *v31;
  itfMenuDrawFunc_t v32;

  cmpGetWork();
  v4 = Allocate(itfMoverFunc_t);
  _ctor(v4, 0, Method_Project_cmpMisc_PartyAnimFunc__, 0);
  itfMoverSetMenu(PID, v4);
  v5 = sdatDevilName(241, 0);
  v6 = sdatDevilName(241, 1);
  itfMenuSetRootMenu(PID, 0, v5, 0, v6);
  v7 = Allocate(itfMenuDrawFunc_t);
  _ctor(v7, 0, Method_Project_cmpMisc_PartyDrawFunc__, 0);
  itfMenuSetDrawFunc(PID, 0, v7, 0);
  v10 = GBWK->player->stack_p[0];
  if (v10 == -1)
  {
    LocalizeText = GetLocalizeText("CMP_MENU_L0045", 1);
    v16 = PID;
    v17 = LocalizeText;
    v18 = "";
    goto LABEL_29;
  }
  if (v10 <= 0x1F)
  {
    v12 = GBWK->player->stock_id[v10];
    if ((v12->flag & 1) != 0)
    {
      if (v12->devilid)
      {
        DevilStockDevilID = cmpGetDevilStockDevilID(v10);
        v14 = sdatDevilName(DevilStockDevilID, 0);
        v15 = sdatDevilName(DevilStockDevilID, 1);
        v16 = PID;
        v17 = v14;
        v18 = v15;
LABEL_29:
        itfMenuSetRootMenu(v16, 1, v17, 0, v18);
        v20 = Allocate(itfMenuDrawFunc_t);
        _ctor(v20, 0, Method_Project_cmpMisc_PartyDrawFunc__, 0);
        itfMenuSetDrawFunc(PID, 1, v20, 0);
        itfMenuSetFlagMenu(PID, 1, 1, v10 != -1);
      }
    }
  }
  v22 = GBWK->player->stack_p[1];
  if (v22 == -1)
  {
    v31 = GetLocalizeText("CMP_MENU_L0045", 1);
    v28 = PID;
    v29 = v31;
    v30 = "";
    goto LABEL_50;
  }
  if (v22 <= 0x1F)
  {
    v24 = GBWK->player->stock_id[v22];
    if ((v24->flag & 1) != 0)
    {
      if (v24->devilid)
      {
        v25 = cmpGetDevilStockDevilID(v22);
        v26 = sdatDevilName(v25, 0);
        v27 = sdatDevilName(v25, 1);
        v28 = PID;
        v29 = v26;
        v30 = v27;
LABEL_50:
        itfMenuSetRootMenu(v28, 2, v29, 0, v30);
        v32 = Allocate(itfMenuDrawFunc_t);
        _ctor(v32, 0, Method_Project_cmpMisc_PartyDrawFunc__, 0);
        itfMenuSetDrawFunc(PID, 2, v32, 0);
        itfMenuSetFlagMenu(PID, 2, 1, v22 != -1);
      }
    }
  }
  itfMenuSetFlag(PID, 2, 0);
  itfMenuSetFlag(PID, 8, 0);
  itfMenuSetFlag(PID, 16, 0);
  itfMenuSetFlag(PID, 32, 1);
  itfMenuUpdateLink(PID);
}

// 0x1f62600
void cmpStockListMake(dds3ProcessID_t *PID, bool _sort) {
  itfMoverFunc_t v6;
  void *Instance;
  void *v8;
  void *stock_id;
  void *v11;
  void *v12;
  void *v13;
  void *DvlList;
  void *v15;
  sdatUnitWork_t *v17;
  sdatUnitWork_t *v19;
  sdatPlayerUnitWork_t *player;
  void *v22;
  s16 *stack_p;
  s16 *v27;
  u64 v28;
  s32 v29;
  itfMenuDrawFunc_t v30;
  sdatPlayerUnitWork_t *v33;
  s16 *v34;
  sdatUnitWork_t *v36;
  s32 DevilStockDevilID;
  char *v38;
  char *v39;
  itfMenuDrawFunc_t v40;
  s8 stock_max;
  s32 v43;
  itfMenuDrawFunc_t v44;

  cmpGetWork();
  v6 = Allocate(itfMoverFunc_t);
  _ctor(v6, 0, Method_Project_cmpMisc_StockAnimFunc__, 0);
  itfMoverSetMenu(PID, v6);
  if (sort)
  {
    Instance = get_Instance(0);
    SortSetting(Instance, 1, 0);
    v8 = get_Instance(0);
    stock_id = GBWK->player->stock_id;
    v11 = Allocate(System_Collections_Generic_List_sdatUnitWork_t_);
    __ctor_48217552(v11, stock_id);
    ListSet_object_(v8, v11);
    v12 = get_Instance(0);
    ListSort(v12, 0);
  }
  v13 = get_Instance(0);
  DvlList = GetDvlList(v13, 1, 0);
  v15 = Allocate(System_Collections_Generic_List_sdatUnitWork_t_);
  __ctor_48217552(v15, DvlList);
  if (GBWK->player->stack_p[0] == -1)
  {
    v17 = 0;
  }
  else
  {
    v17 = Allocate(sdatUnitWork_t);
    _ctor(v17, 0);
    ClassCopy(v17, GBWK->player->stock_id[GBWK->player->stack_p[0]], 0);
  }
  if (GBWK->player->stack_p[1] == -1)
  {
    v19 = 0;
    goto LABEL_27;
  }
  else
  {
    v19 = Allocate(sdatUnitWork_t);
    _ctor(v19, 0);
    ClassCopy(v19, GBWK->player->stock_id[GBWK->player->stack_p[1]], 0);
    goto LABEL_27;
  }
LABEL_27:
  player = GBWK->player;
  v22 = _ToArray(v15);
  player->stock_id = (sdatUnitWork_t *)v22;
  datAdjustStock(0);
  if (v17)
  {
    stack_p = GBWK->player->stack_p;
    stack_p[0] = datGetStockDevilIndex(v17->devilid, v17->uniq_code);
  }
  if (v19)
  {
    v27 = GBWK->player->stack_p;
    v27[1] = datGetStockDevilIndex(v19->devilid, v19->uniq_code);
  }
  v28 = 0;
  v29 = 0;
  while (1)
  {
    v33 = GBWK->player;
    if ((s64)v28 >= v33->stock_max)
      break;
    v34 = v33->stack_p;
    if (v28 == v34[0])
      goto LABEL_39;
    if (v28 == v34[1])
      goto LABEL_39;
    if (v28 > 0x1F)
      goto LABEL_82;
    v36 = GBWK->player->stock_id[v28];
    if ((v36->flag & 1) != 0 && v36->devilid)
    {
      DevilStockDevilID = cmpGetDevilStockDevilID(v28);
      v38 = sdatDevilName(DevilStockDevilID, 0);
      v39 = sdatDevilName(DevilStockDevilID, 1);
      ++v29;
      itfMenuSetRootMenu(PID, v28, v38, 0, v39);
      v40 = Allocate(itfMenuDrawFunc_t);
      _ctor(v40, 0, Method_Project_cmpMisc_StockDrawFunc__, 0);
      itfMenuSetDrawFunc(PID, v28, v40, 0);
    }
    else
    {
LABEL_82:
      ++v29;
      itfMenuSetRootMenu(PID, v28, "", 0, "");
      v30 = Allocate(itfMenuDrawFunc_t);
      _ctor(v30, 0, Method_Project_cmpMisc_StockDrawFunc__, 0);
      itfMenuSetDrawFunc(PID, v28, v30, 0);
    }
LABEL_39:
    ++v28;
  }
  stock_max = v33->stock_max;
  if (!v29)
  {
    itfMenuSetRootMenu(PID, 999, "", 0, "");
    v44 = Allocate(itfMenuDrawFunc_t);
    _ctor(v44, 0, Method_Project_cmpMisc_StockDrawFunc__, 0);
    itfMenuSetDrawFunc(PID, 999, v44, 0);
  }
  if (stock_max >= 8)
    v43 = 8;
  else
    v43 = stock_max;
  itfMenuSetDrawParam(PID, v43, 1);
  itfMenuSetFlag(PID, 2, 0);
  itfMenuSetFlag(PID, 8, 0);
  itfMenuSetFlag(PID, 16, 0);
  itfMenuSetFlag(PID, 32, 1);
  itfMenuUpdateLink(PID);
}

// 0x1f62ea0
void cmpStockListRecreate(bool _sort) {
  dds3ProcessID_t *stockPID;
  dds3ProcessID_t *v8;
  dds3ProcessID_t *v10;
  itfMenuFunc_t v11;
  dds3ProcessID_t *v12;
  itfMenuMoveFunc v13;
  dds3ProcessID_t *id;

  if (cmpGetWork())
  {
    stockPID = cmpGetWork()->stockPID;
    id = stockPID;
    goto LABEL_10;
  }
  id = 0;
LABEL_10:
  dds3GetProcessData(id);
  v8 = id;
  itfMenuClearMenuAll(v8);
  cmpStockListMake(id, sort);
  v10 = id;
  v11 = Allocate(itfMenuFunc_t);
  _ctor(v11, 0, Method_Project_cmpKuda_CallFuncOraganize__, 0);
  itfMenuSetFunc(v10, -1, v11);
  itfMenuSetFlagMenu(id, -1, 64, 1);
  itfMenuSetFlagMenu(id, -1, 128, 1);
  v12 = id;
  v13 = Allocate(itfMenuMoveFunc);
  _ctor(v13, 0, Method_Project_cmpMisc_StockMoveFunc__, 0);
  itfMenuSetMoveFunc(v12, v13);
  itfMenuStart(id);
  cmpSetFilterOrganize();
  cmpUpdateEnable();
  cmpUpdateFontCharPID();
}

// 0x1f5ca80
void cmpPartyListSetImage(dds3ProcessID_t *PID, sprHandle_t *a_phSpr) {
  itfMenuLinkSprite(PID, a_phSpr);
  itfMenuSetMoveAppear(PID, 3);
  itfMenuSetMoveDisappear(PID, 3);
}
