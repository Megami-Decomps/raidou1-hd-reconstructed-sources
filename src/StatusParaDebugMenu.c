#include "types.h"
#include "dat.h"
#include "dds3_pad2.h"
#include "kernel.h"
#include "sbtl.h"
#include "sbtlcalc.h"
#include "sbtldraw.h"
#include "sbtlsub.h"
#include "sdat.h"
#include "statusparadebugmenu.h"

typedef enum {
    StatusParaDebugMenu_MenuListID_ID = 0,
    StatusParaDebugMenu_MenuListID_str = 1,
    StatusParaDebugMenu_MenuListID_tec = 2,
    StatusParaDebugMenu_MenuListID_vit = 3,
    StatusParaDebugMenu_MenuListID_luck = 4,
    StatusParaDebugMenu_MenuListID_HP = 5,
} StatusParaDebugMenu_MenuListID;

typedef struct dds3ProcessID_t dds3ProcessID_t;

static s32 NowMenuListID;
static s32 ID;
static char *Name;

// 0x1a380d0
dds3ProcessFunc_t Process(dds3ProcessID_t *id) {
  sdatUnitWork_t *v2;
  sdatParaWork_t *v3;
  sdatParaWork_t *now;
  struct dat *static_fields;
  s32 v8;
  s32 devilid;
  char *v11;
  s32 tec;
  s32 vit;
  s32 luck;
  sdatPlayerUnitWork_t *player;
  s32 v17;
  sdatUnitWork_t *v18;
  sdatParaWork_t *v19;
  s32 v20;
  s32 v21;
  s32 v23;
  s32 v26;
  s32 v29;
  s32 max_length;
  char *PlayerName;
  sdatUnitWork_t *para;
  sdatParaWork_t *v36;
  u32 level;
  s32 str;
  s32 v40;
  sdatPlayerUnitWork_t *v42;
  sdatUnitWork_t *v43;
  s8 *p_level;
  s32 v45;
  s16 *p_str;
  s16 *p_tec;
  s16 v48;
  s32 v49;
  sdatPlayerUnitWork_t *v50;
  sdatUnitWork_t *v51;
  sdatParaWork_t *v52;
  s32 *p_maxhp;
  s32 *p_hp;
  s32 Bonus;
  s16 v56;
  s32 v58;
  u32 v59;
  sdatPlayerUnitWork_t *v60;
  sdatUnitWork_t *v61;
  s32 v62;
  sdatPlayerUnitWork_t *v63;
  sdatUnitWork_t *v64;
  sdatParaWork_t *v65;
  s32 v67;
  u32 v68;
  sdatPlayerUnitWork_t *v69;
  sdatUnitWork_t *v70;
  s32 v71;
  sdatPlayerUnitWork_t *v72;
  sdatUnitWork_t *v73;
  sdatParaWork_t *v74;
  s32 v76;
  u32 v77;
  sdatPlayerUnitWork_t *v78;
  sdatUnitWork_t *v79;
  s32 v80;
  sdatPlayerUnitWork_t *v81;
  sdatUnitWork_t *v82;
  sdatParaWork_t *v83;
  char *v85;
  char *v86;
  s32 v87;
  s32 v88;
  char *v89;
  char *v90;
  s32 v91;
  s32 v92;
  char *v93;
  char *v94;
  s32 v95;
  s32 v96;
  char *v97;
  char *v98;
  s32 v99;
  s32 v100;
  char *v101;
  char *v102;
  s32 v103;
  s32 v104;
  char *v105;
  char *v106;
  s32 v107;
  s32 v108;
  char *v109;
  char *v110;
  char *v111;
  char *v113;
  char *v114;
  char *v115;
  char *v116;
  char *v117;
  s32 v118;
  s32 v119;
  dds3ProcessFunc_t v120;
  s32 v123;
  u32 v124;
  sdatPlayerUnitWork_t *v125;
  sdatParaWork_t *v126;
  s32 maxhp;
  s32 v128;
  s32 v129;
  s32 v130;
  s32 v131;
  s32 v132;
  sdatUnitWork_t *v133;
  sdatUnitWork_t *v134;
  sdatUnitWork_t *v135;
  sdatUnitWork_t *v136;
  s32 hp;
  u64 v139;
  s64 v140;
  s32 v141;
  sdfColor_t v142;
  sdfColor_t v143;
  sdfColor_t v144;
  sdfColor_t v145;
  sdfColor_t v146;
  sdfColor_t v147;
  sdfColor_t v148;
  sdfColor_t v149;

  v141 = 0;
  v140 = 0;
  v139 = 0;
  hp = 0;
  v2 = Allocate(sdatUnitWork_t);
  _ctor(v2, 0);
  v3 = Allocate(sdatParaWork_t);
  _ctor(v3, 0);
  now = v2->now;
  now->tec = GBWK->player->para->now->tec;
  sBtlGetPlayerTec_ParaUp(v2, v3);
  v8 = ID;
  if (v8 <= 0)
  {
    PlayerName = sBtlGetPlayerName();
    Name = PlayerName;
    para = GBWK->player->para;
    v36 = para->now;
    level = para->level;
    str = v36->str;
    HIDWORD(v140) = v36->tec;
    v141 = str;
    LODWORD(v140) = v36->vit;
    v139 = __PAIR64__(v36->luck, level);
    hp = v36->hp;
    if (!CHECK_TRIG(4, 0))
      goto LABEL_16;
  }
  else
  {
    v8 = ID;
    devilid = GBWK->player->stock_id[GBWK->player->stack_p[v8 - 1]]->devilid;
    v11 = sdatDevilName(devilid, 0);
    Name = v11;
    tec = v3->tec;
    vit = v3->vit;
    luck = v3->luck;
    player = GBWK->player;
    v17 = v3->str;
    v18 = player->stock_id[player->stack_p[ID
                                                                         - 1]];
    v19 = v18->now;
    LODWORD(v139) = v18->level;
    LODWORD(v18) = v17 + v19->str;
    v20 = tec + v19->tec;
    v21 = v19->vit;
    HIDWORD(v140) = v20;
    v141 = v18;
    LODWORD(v18) = v3->hp + v19->hp;
    HIDWORD(v139) = luck + v19->luck;
    LODWORD(v140) = vit + v21;
    hp = v18;
    if (!CHECK_TRIG(4, 0))
      goto LABEL_16;
  }
  v23 = NowMenuListID - 1;
  if (!NowMenuListID)
    v23 = 0;
  NowMenuListID = v23;
LABEL_16:
  if (CHECK_TRIG(5, 0))
  {
    if (NowMenuListID + 1 < 5)
      v26 = NowMenuListID + 1;
    else
      v26 = 5;
    NowMenuListID = v26;
  }
  switch (NowMenuListID)
  {
    case 0:
      if (CHECK_REP(6, 0))
        ID = (ID - 1)
                                                                & ~((ID - 1) >> 31);
      if (CHECK_REP(7, 0))
      {
        v29 = ID + 1;
        ID = v29;
        max_length = GBWK->player->stack_p->max_length;
        if (v29 > max_length)
        {
          max_length = GBWK->player->stack_p->max_length;
          ID = max_length;
        }
      }
      goto LABEL_62;
    case 1:
      v40 = ID;
      if (v40 > 0)
      {
        v40 = ID;
        v42 = GBWK->player;
        v43 = v42->stock_id[v42->stack_p[v40 - 1]];
        p_level = &v43->level;
        v45 = v43->devilid;
        p_str = &v43->now->str;
        p_tec = &v43->backup->str;
        v48 = sBtlGetDevilData(v45, -1)->str;
        v49 = ID;
        v50 = GBWK->player;
        v51 = v50->stock_id[v50->stack_p[v49 - 1]];
        v52 = v51->now;
        p_maxhp = &v52->maxhp;
        p_hp = &v52->hp;
        Bonus = v3->str;
        v56 = v51->pitem->str;
        goto LABEL_61;
      }
      v40 = ID;
      v133 = GBWK->player->para;
      StatusPlayerParaDebug(&v133->now->str, &v133->backup->str, v40);
      goto LABEL_62;
    case 2:
      v58 = ID;
      if (v58 > 0)
      {
        if (!v59)
        {
          v58 = ID;
        }
        v60 = GBWK->player;
        v61 = v60->stock_id[v60->stack_p[v58 - 1]];
        p_level = &v61->level;
        v62 = v61->devilid;
        p_str = &v61->now->tec;
        p_tec = &v61->backup->tec;
        v48 = sBtlGetDevilData(v62, -1)->tec;
        v49 = ID;
        v63 = GBWK->player;
        v64 = v63->stock_id[v63->stack_p[v49 - 1]];
        v65 = v64->now;
        p_maxhp = &v65->maxhp;
        p_hp = &v65->hp;
        Bonus = v3->tec;
        v56 = v64->pitem->tec;
        goto LABEL_61;
      }
      if (!v59)
      {
        v58 = ID;
      }
      v134 = GBWK->player->para;
      StatusPlayerParaDebug(&v134->now->tec, &v134->backup->tec, v58);
      goto LABEL_62;
    case 3:
      v67 = ID;
      if (v67 > 0)
      {
        if (!v68)
        {
          v67 = ID;
        }
        v69 = GBWK->player;
        v70 = v69->stock_id[v69->stack_p[v67 - 1]];
        p_level = &v70->level;
        v71 = v70->devilid;
        p_str = &v70->now->vit;
        p_tec = &v70->backup->vit;
        v48 = sBtlGetDevilData(v71, -1)->vit;
        v49 = ID;
        v72 = GBWK->player;
        v73 = v72->stock_id[v72->stack_p[v49 - 1]];
        v74 = v73->now;
        p_maxhp = &v74->maxhp;
        p_hp = &v74->hp;
        Bonus = v3->vit;
        v56 = v73->pitem->vit;
        goto LABEL_61;
      }
      if (!v68)
      {
        v67 = ID;
      }
      v135 = GBWK->player->para;
      StatusPlayerParaDebug(&v135->now->vit, &v135->backup->vit, v67);
      goto LABEL_62;
    case 4:
      v76 = ID;
      if (v76 <= 0)
      {
        if (!v77)
        {
          v76 = ID;
        }
        v136 = GBWK->player->para;
        StatusPlayerParaDebug(&v136->now->luck, &v136->backup->luck, v76);
      }
      else
      {
        if (!v77)
        {
          v76 = ID;
        }
        v78 = GBWK->player;
        v79 = v78->stock_id[v78->stack_p[v76 - 1]];
        p_level = &v79->level;
        v80 = v79->devilid;
        p_str = &v79->now->luck;
        p_tec = &v79->backup->luck;
        v48 = sBtlGetDevilData(v80, -1)->luck;
        v49 = ID;
        v81 = GBWK->player;
        v82 = v81->stock_id[v81->stack_p[v49 - 1]];
        v83 = v82->now;
        p_maxhp = &v83->maxhp;
        p_hp = &v83->hp;
        Bonus = v3->luck;
        v56 = v82->pitem->luck;
LABEL_61:
        StatusNakamaParaDebug(p_level, p_str, p_tec, v48, p_maxhp, p_hp, v56, v49, Bonus);
      }
      goto LABEL_62;
    case 5:
      v123 = ID;
      if (v123 <= 0)
      {
        v126 = GBWK->player->para->now;
        maxhp = v126->maxhp;
        if (CHECK_REP(6, 0))
          goto LABEL_120;
      }
      else
      {
        if (!v124)
        {
          v123 = ID;
        }
        v125 = GBWK->player;
        v126 = v125->stock_id[v125->stack_p[v123 - 1]]->now;
        maxhp = v126->maxhp;
        if (CHECK_REP(6, 0))
        {
LABEL_120:
          v128 = v126->hp - 1;
          if (v128 <= 1)
            v128 = 1;
          v126->hp = v128;
        }
      }
      if (CHECK_REP(8, 0))
      {
        v129 = v126->hp - 10;
        if (v129 <= 1)
          v129 = 1;
        v126->hp = v129;
        if (!CHECK_REP(7, 0))
        {
LABEL_125:
          if (!CHECK_REP(11, 0))
            goto LABEL_62;
          goto LABEL_134;
        }
      }
      else if (!CHECK_REP(7, 0))
      {
        goto LABEL_125;
      }
      v130 = v126->hp;
      if (v130 + 1 < maxhp)
        v131 = v130 + 1;
      else
        v131 = maxhp;
      v126->hp = v131;
      if (!CHECK_REP(11, 0))
        goto LABEL_62;
LABEL_134:
      v132 = v126->hp + 10;
      if (v132 >= maxhp)
        v132 = maxhp;
      v126->hp = v132;
LABEL_62:
      v142.r = 1.0;
      v142.g = 1.0;
      v142.b = 1.0;
      v142.a = 1.0;
      SetTextPartsDataList(20.0, (f32)(32 * NowMenuListID + 52), 150.0, 32.0, v142, "＞", 0);
      v85 = ToString((u32)StatusParaDebugMenu->static_fields + 4, 0);
      v86 = Concat_54766928("キャラID = ", v85, 0);
      v87 = NowMenuListID;
      v143.r = 1.0;
      if (v87)
        v88 = 20;
      else
        v88 = 44;
      v143.g = 1.0;
      v143.b = 1.0;
      v143.a = 1.0;
      SetTextPartsDataList((f32)v88, 52.0, 270.0, 32.0, v143, v86, 0);
      v89 = ToString((s32)&v141, 0);
      v90 = Concat_54766928("力 = ", v89, 0);
      v91 = NowMenuListID;
      v144.r = 1.0;
      if (v91 == 1)
        v92 = 44;
      else
        v92 = 20;
      v144.g = 1.0;
      v144.b = 1.0;
      v144.a = 1.0;
      SetTextPartsDataList((f32)v92, 84.0, 270.0, 32.0, v144, v90, 0);
      v93 = ToString((s32)&v140 + 4, 0);
      v94 = Concat_54766928("魔 = ", v93, 0);
      v95 = NowMenuListID;
      v145.r = 1.0;
      if (v95 == 2)
        v96 = 44;
      else
        v96 = 20;
      v145.g = 1.0;
      v145.b = 1.0;
      v145.a = 1.0;
      SetTextPartsDataList((f32)v96, 116.0, 270.0, 32.0, v145, v94, 0);
      v97 = ToString((s32)&v140, 0);
      v98 = Concat_54766928("耐 = ", v97, 0);
      v99 = NowMenuListID;
      v146.r = 1.0;
      if (v99 == 3)
        v100 = 44;
      else
        v100 = 20;
      v146.g = 1.0;
      v146.b = 1.0;
      v146.a = 1.0;
      SetTextPartsDataList((f32)v100, 148.0, 270.0, 32.0, v146, v98, 0);
      v101 = ToString((s32)&v139 + 4, 0);
      v102 = Concat_54766928("運 = ", v101, 0);
      v103 = NowMenuListID;
      v147.r = 1.0;
      if (v103 == 4)
        v104 = 44;
      else
        v104 = 20;
      v147.g = 1.0;
      v147.b = 1.0;
      v147.a = 1.0;
      SetTextPartsDataList((f32)v104, 180.0, 270.0, 32.0, v147, v102, 0);
      v105 = ToString((s32)&hp, 0);
      v106 = Concat_54766928("体 = ", v105, 0);
      v107 = NowMenuListID;
      v148.r = 1.0;
      if (v107 == 5)
        v108 = 44;
      else
        v108 = 20;
      v148.g = 1.0;
      v148.b = 1.0;
      v148.a = 1.0;
      SetTextPartsDataList((f32)v108, 212.0, 270.0, 32.0, v148, v106, 0);
      v109 = NewSpecific(string, 6u);
      v110 = "キャラ名 = ";
      v111 = v109;
      v109[0] = "キャラ名 = ";
      v111[1] = Name;
      v113 = "\nレベル = ";
      v111[2] = "\nレベル = ";
      v114 = ToString((s32)&v139, 0);
      v111[3] = v114;
      v115 = "\n現在体力 = ";
      v111[4] = "\n現在体力 = ";
      v116 = ToString((s32)&hp, 0);
      v111[5] = v116;
      v117 = Concat_54832608(v111, 0);
      v118 = NowMenuListID;
      v149.r = 1.0;
      if (v118 == 6)
        v119 = 44;
      else
        v119 = 20;
      v149.g = 1.0;
      v149.b = 1.0;
      v149.a = 1.0;
      SetTextPartsDataList((f32)v119, 254.0, 510.0, 32.0, v149, v117, 0);
      v120 = 0;
      if (CHECK_TRIG(1, 0))
      {
        v120 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
        _ctor(v120, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      }
      return v120;
    default:
      goto LABEL_62;
  }
}

// 0x1a398f0
void TextDraw(s32 panelNo, s32 TextPosX, s32 TextPosY, s32 TextSizeW, s32 TextSizeH, const sdfColor_t *col, char *str) {
  f32 a;
  f32 b;
  f32 g;
  f32 r;
  s32 v20;
  sdfColor_t v21;

  a = col->a;
  b = col->b;
  g = col->g;
  r = col->r;
  v21.b = b;
  v21.a = a;
  if (NowMenuListID + 1 == panelNo)
    v20 = TextPosX + 24;
  else
    v20 = TextPosX;
  v21.r = r;
  v21.g = g;
  SetTextPartsDataList((f32)v20, (f32)(TextPosY + 32 * panelNo), (f32)TextSizeW, (f32)TextSizeH, v21, str, 0);
}

// 0x1a39550
void StatusNakamaParaDebug(s8 *level, s16 *status_now, s16 *status_Back, s16 BaseStatus, s32 *MaxHP, s32 *HP, s16 pItem, s32 ChrID, s32 Bonus) {
  bool v18;
  s64 v19;
  s16 v20;
  sdatPlayerUnitWork_t *player;
  s32 DevilMaxHP;
  s32 v24;
  s32 v25;
  s32 v27;
  sdatPlayerUnitWork_t *v28;
  s32 v29;
  s32 v30;
  sdatPlayerUnitWork_t *v32;
  s32 v33;
  sdatParaWork_t *backup;
  s32 v35;

  v18 = __OFSUB__(ChrID, 1);
  v19 = (u32)(ChrID - 1);
  if ((s32)v19 < 0 == v18)
  {
    if (!CHECK_REP(6, 0))
      goto LABEL_13;
    --*level;
    --*status_now;
    v20 = *status_Back - 1;
    *status_Back = v20;
    if (*status_now <= 1)
    {
      *status_now = 1;
      if (*status_Back > 1)
      {
LABEL_7:
        if (*level > 1)
          goto LABEL_8;
        goto LABEL_30;
      }
    }
    else if (v20 > 1)
    {
      goto LABEL_7;
    }
    *status_Back = 1;
    if (*level > 1)
    {
LABEL_8:
LABEL_9:
      player = GBWK->player;
      DevilMaxHP = datGetDevilMaxHP(player->stock_id[player->stack_p[(u32)v19]], 0);
      if (DevilMaxHP <= 1)
        v24 = 1;
      else
        v24 = DevilMaxHP;
      *MaxHP = v24;
      *HP = v24;
LABEL_13:
      if (CHECK_REP(7, 0))
      {
        ++*level;
        ++*status_now;
        ++*status_Back;
        v25 = GETITEMPARA_LOW(pItem);
        if (*level >= 100)
          *level = 99;
        v27 = v25 + BaseStatus;
        v28 = GBWK->player;
        v29 = datGetDevilMaxHP(v28->stock_id[v28->stack_p[(u32)v19]], 0);
        if (v29 >= 999)
          v30 = 999;
        else
          v30 = v29;
        *MaxHP = v30;
        *HP = v30;
        v32 = GBWK->player;
        v33 = *status_now;
        backup = v32->stock_id[v32->stack_p[v19]]->backup;
        backup->hp = v30;
        backup->maxhp = v30;
        v35 = Bonus + 2 * v27;
        if (v35 < v33)
          *status_now = v35;
        if (v35 < *status_Back)
          *status_Back = v35;
      }
      return;
    }
LABEL_30:
    *level = 1;
    goto LABEL_9;
  }
}

// 0x1a391c0
void StatusPlayerParaDebug(s16 *status_now, s16 *status_back, s32 ChrID) {
  sdatUnitWork_t *para;
  s8 v9;
  sdatUnitWork_t *v10;
  sdatParaWork_t *now;
  sdatParaWork_t *v13;
  sdatUnitWork_t *v14;
  sdatParaWork_t *backup;
  sdatParaWork_t *v16;
  s32 maxhp;
  sdatUnitWork_t *v19;
  s8 v20;
  sdatUnitWork_t *v21;
  sdatParaWork_t *v22;
  sdatParaWork_t *v24;
  sdatUnitWork_t *v25;
  sdatParaWork_t *v26;
  sdatParaWork_t *v27;
  s32 v28;

  if (ChrID <= 0)
  {
    if (!CHECK_REP(6, 0))
      goto LABEL_19;
    para = GBWK->player->para;
    v9 = para->level - 1;
    para->level = v9;
    --*status_now;
    --*status_back;
    if (v9 <= 0)
    {
      para = GBWK->player->para;
      para->level = 1;
      if (*status_now > 10)
      {
LABEL_10:
        if (*status_back > 10)
          goto LABEL_11;
        goto LABEL_43;
      }
    }
    else if (*status_now > 10)
    {
      goto LABEL_10;
    }
    *status_now = 10;
    if (*status_back > 10)
    {
LABEL_11:
LABEL_12:
      v10 = GBWK->player->para;
      now = v10->now;
      now->maxhp = datGetPlayerMaxHP(v10);
      v13 = GBWK->player->para->now;
      if (v13->maxhp >= 1000)
      {
        v13 = GBWK->player->para->now;
        v13->maxhp = 999;
      }
      v14 = GBWK->player->para;
      v16 = v14->now;
      backup = v14->backup;
      maxhp = v16->maxhp;
      v16->hp = maxhp;
      backup->hp = maxhp;
      backup->maxhp = maxhp;
LABEL_19:
      if (!CHECK_REP(7, 0))
        return;
      v19 = GBWK->player->para;
      v20 = v19->level + 1;
      v19->level = v20;
      ++*status_now;
      ++*status_back;
      if (v20 >= 100)
      {
        v19 = GBWK->player->para;
        v19->level = 99;
        if (*status_now < 41)
        {
LABEL_24:
          if (*status_back < 41)
            goto LABEL_25;
          goto LABEL_37;
        }
      }
      else if (*status_now < 41)
      {
        goto LABEL_24;
      }
      *status_now = 40;
      if (*status_back < 41)
      {
LABEL_25:
LABEL_26:
        v21 = GBWK->player->para;
        v22 = v21->now;
        v22->maxhp = datGetPlayerMaxHP(v21);
        v24 = GBWK->player->para->now;
        if (v24->maxhp >= 1000)
        {
          v24 = GBWK->player->para->now;
          v24->maxhp = 999;
        }
        v25 = GBWK->player->para;
        v27 = v25->now;
        v26 = v25->backup;
        v28 = v27->maxhp;
        v27->hp = v28;
        v26->hp = v28;
        v26->maxhp = v28;
        return;
      }
LABEL_37:
      *status_back = 40;
      goto LABEL_26;
    }
LABEL_43:
    *status_back = 10;
    goto LABEL_12;
  }
}

// 0x1a39800
void SetHP(s32 *HP, s32 maxHP) {
  s32 v5;
  s32 v6;
  s32 v7;
  s32 v8;

  if (CHECK_REP(6, 0))
  {
    v5 = *HP - 1;
    if (v5 <= 1)
      v5 = 1;
    *HP = v5;
    if (!CHECK_REP(8, 0))
    {
LABEL_3:
      if (!CHECK_REP(7, 0))
        goto LABEL_4;
      goto LABEL_12;
    }
  }
  else if (!CHECK_REP(8, 0))
  {
    goto LABEL_3;
  }
  v6 = *HP - 10;
  if (v6 <= 1)
    v6 = 1;
  *HP = v6;
  if (!CHECK_REP(7, 0))
  {
LABEL_4:
    if (!CHECK_REP(11, 0))
      return;
    goto LABEL_16;
  }
LABEL_12:
  if (*HP + 1 < maxHP)
    v7 = *HP + 1;
  else
    v7 = maxHP;
  *HP = v7;
  if (CHECK_REP(11, 0))
  {
LABEL_16:
    v8 = *HP + 10;
    if (v8 >= maxHP)
      v8 = maxHP;
    *HP = v8;
  }
}
