#include "types.h"
#include "achievement.h"
#include "atlfieldaccessor.h"
#include "atlfieldtableresource.h"
#include "aw.h"
#include "aw_sbattle.h"
#include "bsflow.h"
#include "buttonguide.h"
#include "cfg.h"
#include "cmpmisc.h"
#include "configgame.h"
#include "dat.h"
#include "dds3_pad.h"
#include "dds3adminiprocess.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "dds3kernelmain.h"
#include "fclmisc.h"
#include "fld.h"
#include "g_aposmove.h"
#include "itf.h"
#include "kernel.h"
#include "lmap.h"
#include "rstinit.h"
#include "sb_auto.h"
#include "sbtl.h"
#include "sbtlactai.h"
#include "sbtlaction.h"
#include "sbtlainew.h"
#include "sbtlcalc.h"
#include "sbtlcamera.h"
#include "sbtlcmndmenunew.h"
#include "sbtlcontinue.h"
#include "sbtldmg.h"
#include "sbtldraw.h"
#include "sbtldvltk.h"
#include "sbtleff.h"
#include "sbtleffbo.h"
#include "sbtlencount.h"
#include "sbtlevent.h"
#include "sbtlexp.h"
#include "sbtlitem.h"
#include "sbtlmain.h"
#include "sbtlmenu.h"
#include "sbtlpanel.h"
#include "sbtlplayer.h"
#include "sbtlplayerfoot.h"
#include "sbtlscene.h"
#include "sbtlscript.h"
#include "sbtlskill.h"
#include "sbtlsm.h"
#include "sbtlsound.h"
#include "sbtlstp.h"
#include "sbtlsub.h"
#include "sbtltime.h"
#include "sbtltubesupport.h"
#include "sbtlunit.h"
#include "sbtlvisual.h"
#include "sbtlweapon.h"
#include "scr.h"
#include "sdf_vu0.h"
#include "sdfquat.h"
#include "sdfsound.h"
#include "sdfsystem.h"
#include "smnr.h"
#include "sndat3.h"
#include "tips.h"

#define SBTLFIRSTATTACK_R 15
#define SBTLFIRSTATTACK_R2 25
#define SBTLFIRSTATTACK_R2L 18
#define SBTLFIRSTATTACK_R2U 38
#define ROULETTE_TOP 195

typedef struct SBATTLE_WORK SBATTLE_WORK;
typedef struct SBATTLE_WORK2 SBATTLE_WORK2;
typedef struct SBATTLE_WORK3 SBATTLE_WORK3;
typedef struct SBTLEFF_DATAWORK SBTLEFF_DATAWORK;
typedef struct SBTLMAIN_DATA SBTLMAIN_DATA;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct sdatPlayerUnitWork_t sdatPlayerUnitWork_t;

static s32 dbg_encount_bk;
static void *battleMap;
char *ret_field_scene;
bool battle_map_loadend;
static s16 *stack_p_backup;
static s32 exit2_flag;
static s32 exit3_flag;

SBATTLE_WORK *wk;
SBATTLE_WORK2 *wk2;
SBATTLE_WORK3 *wk3;
SBTLMAIN_DATA *main_data;
SBTLEFF_DATAWORK *wkeffOnMem;
sdatPlayerUnitWork_t *tutorial_bk;
bool escape_checkflg;
bool kaiwa_btlendflg;
bool epl_otchkflg;
u32 frame_cnt;
u32 runtime_cnt;
u8 *ai_scr;
u8 *huuma_success_scr;

static void Exit2Set(s32 i);

// macros
// 0x1ec1700: f32 DEG_RAD(f32 x)
#define DEG_RAD(x) ((f32)(x / 180.0) * 3.14159)

// 0x1ec1720: f32 RAD_DEG(f32 x)
#define RAD_DEG(x) ((f32)(x * 180.0) / 3.14159)

// 0x1ec1740: f32 GET_PER_SRCtoDES(f32 src, f32 des, f32 per)
#define GET_PER_SRCtoDES(src, des, per) ((f32)((f32)(des - src) * per) + src)

// 0x1ec1750: f32 GET_360toSIN(f32 cnt, f32 lower, f32 upper)
static inline f32 GET_360toSIN(f32 cnt, f32 lower, f32 upper) {
  f32 v7;
  f32 v8;
  f32 v9;
  f32 v10;

  v7 = (f32)((f32)(sub_188E3E0(cnt + 90.0) / 180.0) * 3.14159) * 0.15915494;
  v8 = (s32)v7;
  if (v7 == INFINITY)
    v8 = -2147500000.0;
  v9 = v7 - v8;
  if ((f32)(v7 - v8) <= 0.5)
  {
    if (v9 < -0.5)
      v9 = v9 + 1.0;
  }
  else
  {
    v9 = v9 + -1.0;
  }
  if (v9 <= 0.25)
  {
    if (v9 < -0.25)
      v9 = -0.5 - v9;
  }
  else
  {
    v9 = 0.5 - v9;
  }
  v10 = v9 * 4.0;
  return (f32)((f32)(upper - lower) * (f32)((f32)((f32)((f32)((f32)((f32)((f32)(v10 * 1.5707963) + (f32)((f32)(v10 * (f32)(v10 * v10)) * -0.6459637)) + (f32)((f32)((f32)(v10 * v10) * (f32)(v10 * (f32)(v10 * v10))) * 0.07968968)) + (f32)((f32)((f32)(v10 * v10) * (f32)((f32)(v10 * v10) * (f32)(v10 * (f32)(v10 * v10)))) * -0.0046737655)) + (f32)((f32)((f32)(v10 * v10) * (f32)((f32)(v10 * v10) * (f32)((f32)(v10 * v10) * (f32)(v10 * (f32)(v10 * v10))))) * 0.00015148419)) + 1.0) * 0.5))
       + lower;
}

// 0x1ec1910: s32 COUNT_UP_360(s32 cnt, s32 add)
#define COUNT_UP_360(cnt, add) ((add + cnt) % 360)

// 0x1ec1940
void LimitRange(s32 *x, s32 l, s32 h) {
  s32 v4;
  s32 v5;

  if (*x >= h)
    v4 = h;
  else
    v4 = *x;
  if (*x <= l)
    v5 = l;
  else
    v5 = v4;
  *x = v5;
}

// 0x1ec1960
void LimitRange_2(s16 *x, s16 l, s16 h) {
  s32 v4;
  s16 v5;

  v4 = *x;
  v5 = h;
  if (v4 < h)
    v5 = *x;
  if (v4 <= l)
    v5 = l;
  *x = v5;
}

// 0x1ec1980
void LimitRange_3(u32 *x, u32 l, u32 h) {
  u32 v4;
  u32 v5;

  if (*x >= h)
    v4 = h;
  else
    v4 = *x;
  if (*x <= l)
    v5 = l;
  else
    v5 = v4;
  *x = v5;
}

// 0x1ec19a0
void LimitRange_4(s8 *x, s8 l, s8 h) {
  s32 v4;
  s8 v5;

  v4 = *x;
  v5 = h;
  if (v4 < h)
    v5 = *x;
  if (v4 <= l)
    v5 = l;
  *x = v5;
}

// 0x1ec19c0
void LimitRange_5(f32 *x, s32 l, s32 h) {
  f32 v4;

  v4 = l;
  if (*x > (f32)l)
  {
    v4 = h;
    if (*x < (f32)h)
      v4 = *x;
  }
  *x = v4;
}

// 0x1ec1a00
void EncountAiPackLoad(void) {
  void *Asset;
  s64 naturalAligment;
  void *v6;
  s64 v7;
  void *v9;
  sdfBinary *v10;
  s32 v11;
  char *v12;
  char *v13;
  s32 v16;
  s32 v17;
  void *v18;
  s32 dlc_no;

  dlc_no = 0;
  Asset = LoadAsset(_Ctrl_k__BackingField, "battle", "sb_encountpac", 0);
  if (!Asset)
  {
LABEL_15:
    sBtlInitEncountPac(0, 0);
    goto LABEL_17;
  }
  if (Asset->klass->_2.naturalAligment < (u32)naturalAligment)
    goto LABEL_15;
  if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_BattleEncountPac)
    v18 = Asset;
  else
    v18 = 0;
  sBtlInitEncountPac(v18, 0);
LABEL_17:
  v6 = LoadAsset(_Ctrl_k__BackingField, "battle", "sb_rndencpac", 0);
  if (v6)
  {
    if (v6->klass->_2.naturalAligment >= (u32)v7)
    {
      if (v6->klass->_2.typeHierarchy[v7 - 1] != Project_BattleRndEncPac)
        v6 = 0;
      sBtlInitRndEncPac(v6, 0);
      goto LABEL_24;
    }
    v6 = 0;
  }
  sBtlInitRndEncPac(v6, 0);
LABEL_24:
  v9 = LoadAsset(_Ctrl_k__BackingField, "battle", "sb_devilai_R1.TBL", 0);
  v10 = Allocate(sdfBinary);
  _ctor(v10, v9, 0);
  sBtlInitAIdata(v10, 0);
  v11 = 1;
  for (dlc_no = 1; dlc_no < 6; v11 = dlc_no)
  {
    if (!!fldCheckDlcData(v11))
    {
      v12 = ToString((s32)&dlc_no, 0);
      v13 = Concat_54766928("battle_dlc", v12, 0);
      Load(Dependent, v13, v13);
      LoadSyncAll(_Ctrl_k__BackingField, 0);
      v16 = dlc_no;
      sBtlInitEncountPacDlc(v16);
      sBtlInitRndEncPacDlc(dlc_no);
      v17 = dlc_no;
      sBtlInitAIdataDLC(v17);
      Unload(Dependent, v13, 0);
    }
    ++dlc_no;
  }
}

// 0x1ec1ec0
void LoadTableData(void) {
  s64 v4;
  SBTLITEM_TBL *v5;
  s64 v6;
  SBTLITEM_TBL *tbldata_local;
  SBTLITEM_TBL *v8;
  void *Asset;
  s64 naturalAligment;
  void *v12;
  s32 Length;
  s64 v14;
  s64 v15;
  s64 v16;
  SBTLITEM_TBL *v17;
  SBTLITEM_TBL *ITEMTBL;
  Il2CppClass *v19;
  void *v21;
  s64 v22;
  void *v23;
  s32 v24;
  SBTLWEAPON_TBL *v25;
  s64 v26;
  s64 v27;
  s64 v28;
  SBTLWEAPON_TBL *tbl_local;
  SBTLWEAPON_TBL *WEAPONTBL;
  Il2CppClass *v31;
  s64 v32;
  SBTLSKILLP_TBL *v33;
  s64 v34;
  SBTLSKILLP_TBL *v35;
  s64 v36;
  SBTLSKILLP_TBL *v37;
  void *v39;
  s64 v40;
  void *v41;
  s32 v42;
  s64 v43;
  s64 v44;
  s64 v45;
  SBTLSKILLP_TBL *v46;
  SBTLSKILLP_TBL *SKILLTBL;
  Il2CppClass *v48;
  void *v50;
  s64 v51;
  void *v52;
  s32 v53;
  SBTLSKLVISUAL_TBL *v54;
  s32 v56;
  s64 v57;
  s64 v58;
  s64 v59;
  SBTLSKLVISUAL_TBL *visualtbldata_local;
  SBTLSKLVISUAL_TBL *SKILLVISUALTBL;
  Il2CppClass *v62;
  void *v64;
  s64 v65;
  void *v66;
  s32 v67;
  V_POSITION_WORK *v68;
  s32 v71;
  s64 v72;
  s64 v73;
  s64 v74;
  V_POSITION_WORK *sbtleff_cylindertbl_local;
  V_POSITION_WORK *EFFCYLINDER;
  V_POSITION_WORK *v78;
  void *v80;
  s64 v81;
  void *v82;
  s32 v83;
  V_POSITION_WORK *v84;
  s32 v87;
  s64 v88;
  s64 v89;
  s64 v90;
  V_POSITION_WORK *sbtleff_cylindertbl_p_local;
  V_POSITION_WORK *v93;
  V_POSITION_WORK *v94;
  void *v96;
  s64 v97;
  void *v98;
  void *v101;
  s64 v102;
  void *v104;
  s64 v105;
  void *v106;
  void *v107;
  s32 v108;
  SBTLEFFDMG_TBL *v109;
  s32 v112;
  s64 v113;
  s64 v114;
  s64 v115;
  SBTLEFFDMG_TBL *dmg_tbldata_local;
  SBTLEFFDMG_TBL *EFFDMG_TBL;
  SBTLEFFDMG_TBL *v119;
  void *v121;
  s64 v122;
  void *v123;
  s32 v124;
  SBTLEFFDMG_TBL *v125;
  s32 v127;
  s64 v128;
  s64 v129;
  s64 v130;
  SBTLEFFDMG_TBL *dmg_tbldata_p_local;
  SBTLEFFDMG_TBL *v133;
  SBTLEFFDMG_TBL *v134;
  void *v136;
  s64 v137;
  void *v138;
  MOTIONMOVE_WORK *v139;
  s64 v142;
  s64 v143;
  MOTIONMOVE_WORK *sbtlmotionmv_tbldata_local;
  MOTIONMOVE_WORK *DEVILMOTIONMOVE;
  MOTIONMOVE_WORK *v147;
  void *v149;
  s64 v150;
  void *v151;
  void *v154;
  s64 v155;
  void *v157;
  s64 v158;
  void *v160;
  s64 v161;
  void *v162;
  void *v163;
  void *v164;
  SBTLAISYO_DATAWORK *v165;
  void *v168;
  s64 v169;
  void *v170;
  s64 v171;
  s64 v172;
  SBTLAISYO_DATAWORK *aisyo_tbldata_local;
  SBTLAISYO_DATAWORK *AISYOTBL;
  SBTLAISYO_DATAWORK *v176;
  void *v179;
  sdfBinary *v180;
  u8 *data;
  void *v185;
  sdfBinary *v186;
  u8 *v187;
  SBTLAUTO_TBL *v190;
  void *v193;
  s64 v195;
  void *v196;
  void *v197;
  void *p_g_aCamMoveDtHd;

  Load(Dependent, "battle", "battle");
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  EncountAiPackLoad();
  v4 = 768;
  v5 = NewSpecific(SBTLITEM_TBL, 0x300u);
  tbldata = v5;
  v6 = 32;
  do
  {
    tbldata_local = tbldata;
    v8 = Allocate(SBTLITEM_TBL);
    _ctor(v8, 0);
    *(Il2CppClass **)((char *)&tbldata_local->obj.klass + v6) = v8;
    v6 += 8;
    --v4;
  }
  while (v4);
  Asset = LoadAsset(_Ctrl_k__BackingField, "battle", "sb_itemtbl", 0);
  {
    v12 = 0;
    Length = GetLength(0, 0);
    if (Length < 1)
      goto LABEL_35;
LABEL_30:
    v14 = 0;
    v15 = Length;
    v16 = 32;
    while (1)
    {
      v17 = tbldata;
      ITEMTBL = GetITEMTBL(v12, v14, 0);
      v19 = ITEMTBL;
      if (ITEMTBL)
      {
          break;
      }
      *(Il2CppClass **)((char *)&v17->obj.klass + v16) = v19;
      ++v14;
      v16 += 8;
      if (v15 == v14)
        goto LABEL_35;
    }
  }
  if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_BattleItemTbl)
    v12 = Asset;
  else
    v12 = 0;
  Length = GetLength(v12, 0);
  if (Length >= 1)
    goto LABEL_30;
LABEL_35:
  v21 = LoadAsset(_Ctrl_k__BackingField, "battle", "sb_weapontbl", 0);
  {
    if (v21->klass->_2.typeHierarchy[v22 - 1] == Project_BattleWeaponTbl)
      v23 = v21;
    else
      v23 = 0;
  }
  else
  {
    v23 = 0;
  }
  v24 = GetLength(v23, 0);
  v25 = NewSpecific(SBTLWEAPON_TBL, v24);
  tbl = v25;
  if (v24 >= 1)
  {
    v26 = 0;
    v27 = v24;
    v28 = 32;
    do
    {
      tbl_local = tbl;
      WEAPONTBL = GetWEAPONTBL(v23, v26, 0);
      v31 = WEAPONTBL;
      *(Il2CppClass **)((char *)&tbl_local->obj.klass + v28) = v31;
      ++v26;
      v28 += 8;
    }
    while (v27 != v26);
  }
  v32 = 1600;
  v33 = NewSpecific(SBTLSKILLP_TBL, 0x640u);
  tbldata = v33;
  v34 = 32;
  v35 = tbldata;
  do
  {
    v37 = Allocate(SBTLSKILLP_TBL);
    _ctor(v37, 0);
    *(Il2CppClass **)((char *)&v35->obj.klass + v34) = v37;
    --v32;
    v35 = tbldata;
    v36 = *(s64 *)((char *)&v35->obj.klass + v34);
    v34 += 8;
    *(u16 *)(v36 + 28) = 0;
  }
  while (v32);
  v39 = LoadAsset(_Ctrl_k__BackingField, "battle", "sb_skilltbl", 0);
  {
    v41 = 0;
    v42 = GetLength(0, 0);
    if (v42 < 1)
      goto LABEL_77;
LABEL_72:
    v43 = 0;
    v44 = v42;
    v45 = 32;
    while (1)
    {
      v46 = tbldata;
      SKILLTBL = GetSKILLTBL(v41, v43, 0);
      v48 = SKILLTBL;
      *(Il2CppClass **)((char *)&v46->obj.klass + v45) = v48;
      ++v43;
      v45 += 8;
      if (v44 == v43)
        goto LABEL_77;
    }
  }
  if (v39->klass->_2.typeHierarchy[v40 - 1] == Project_BattleSkillTbl)
    v41 = v39;
  else
    v41 = 0;
  v42 = GetLength(v41, 0);
  if (v42 >= 1)
    goto LABEL_72;
LABEL_77:
  v50 = LoadAsset(_Ctrl_k__BackingField, "battle", "sb_skillvisual", 0);
  {
    if (v50->klass->_2.typeHierarchy[v51 - 1] == Project_BattleSkillVisualTbl)
      v52 = v50;
    else
      v52 = 0;
  }
  else
  {
    v52 = 0;
  }
  v53 = GetLength(v52, 0);
  v54 = NewSpecific(SBTLSKLVISUAL_TBL, v53);
  visualtbldata = v54;
  v56 = GetLength(v52, 0);
  if (v56 >= 1)
  {
    v57 = 0;
    v58 = v56;
    v59 = 32;
    do
    {
      visualtbldata_local = visualtbldata;
      SKILLVISUALTBL = GetSKILLVISUALTBL(v52, v57, 0);
      v62 = SKILLVISUALTBL;
      *(Il2CppClass **)((char *)&visualtbldata_local->obj.klass + v59) = v62;
      ++v57;
      v59 += 8;
    }
    while (v58 != v57);
  }
  v64 = LoadAsset(_Ctrl_k__BackingField, "battle", "sb_effcylinder", 0);
  {
    if (v64->klass->_2.typeHierarchy[v65 - 1] == Project_BattleEffCylinder)
      v66 = v64;
    else
      v66 = 0;
  }
  else
  {
    v66 = 0;
  }
  v67 = GetLength(v66, 0);
  v68 = NewSpecific(V_POSITION_WORK, v67);
  sbtleff_cylindertbl = v68;
  v71 = GetLength(v66, 0);
  if (v71 >= 1)
  {
    v72 = 0;
    v73 = v71;
    v74 = 32;
    do
    {
      sbtleff_cylindertbl_local = sbtleff_cylindertbl;
      EFFCYLINDER = GetEFFCYLINDER(v66, v72, 0);
      v78 = EFFCYLINDER;
      *(Il2CppClass **)((char *)&sbtleff_cylindertbl_local->obj.klass + v74) = v78;
      ++v72;
      v74 += 8;
    }
    while (v73 != v72);
  }
  v80 = LoadAsset(_Ctrl_k__BackingField, "battle", "sb_effcylinder_p", 0);
  {
    if (v80->klass->_2.typeHierarchy[v81 - 1] == Project_BattleEffCylinder)
      v82 = v80;
    else
      v82 = 0;
  }
  else
  {
    v82 = 0;
  }
  v83 = GetLength(v82, 0);
  v84 = NewSpecific(V_POSITION_WORK, v83);
  sbtleff_cylindertbl_p = v84;
  v87 = GetLength(v82, 0);
  if (v87 >= 1)
  {
    v88 = 0;
    v89 = v87;
    v90 = 32;
    do
    {
      sbtleff_cylindertbl_p_local = sbtleff_cylindertbl_p;
      v93 = GetEFFCYLINDER(v82, v88, 0);
      v94 = v93;
      *(Il2CppClass **)((char *)&sbtleff_cylindertbl_p_local->obj.klass + v90) = v94;
      ++v88;
      v90 += 8;
    }
    while (v89 != v88);
  }
  v96 = LoadAsset(_Ctrl_k__BackingField, "battle", "sb_devilvisualtbl", 0);
  {
    if (v96->klass->_2.typeHierarchy[v97 - 1] == Project_BattleDevilVisualTbl)
      v98 = v96;
    else
      v98 = 0;
LABEL_145:
    sBtlSetVisualDataZInit(0, v98);
    goto LABEL_146;
  }
  else
  {
    v98 = 0;
    goto LABEL_145;
  }
  sBtlSetVisualDataZInit(0, v98);
LABEL_146:
  v101 = LoadAsset(_Ctrl_k__BackingField, "battle", "sb_devilvisualtbl_hyakki", 0);
  {
    sBtlSetVisualDataZInit(1, 0);
    goto LABEL_150;
  }
  if (v101->klass->_2.typeHierarchy[v102 - 1] == Project_BattleDevilVisualTbl)
    v107 = v101;
  else
    v107 = 0;
  sBtlSetVisualDataZInit(1, v107);
LABEL_150:
  v104 = LoadAsset(_Ctrl_k__BackingField, "battle", "sb_effdamagetbl", 0);
  {
    if (v104->klass->_2.typeHierarchy[v105 - 1] == Project_BattleEffDamageTbl)
      v106 = v104;
    else
      v106 = 0;
  }
  else
  {
    v106 = 0;
  }
  v108 = GetLength(v106, 0);
  v109 = NewSpecific(SBTLEFFDMG_TBL, v108);
  dmg_tbldata = v109;
  v112 = GetLength(v106, 0);
  if (v112 >= 1)
  {
    v113 = 0;
    v114 = v112;
    v115 = 32;
    do
    {
      dmg_tbldata_local = dmg_tbldata;
      EFFDMG_TBL = GetEFFDMG_TBL(v106, v113, 0);
      v119 = EFFDMG_TBL;
      *(Il2CppClass **)((char *)&dmg_tbldata_local->obj.klass + v115) = v119;
      ++v113;
      v115 += 8;
    }
    while (v114 != v113);
  }
  v121 = LoadAsset(_Ctrl_k__BackingField, "battle", "sb_effdamagetbl_p", 0);
  {
    if (v121->klass->_2.typeHierarchy[v122 - 1] == Project_BattleEffDamageTbl)
      v123 = v121;
    else
      v123 = 0;
  }
  else
  {
    v123 = 0;
  }
  v124 = GetLength(v123, 0);
  v125 = NewSpecific(SBTLEFFDMG_TBL, v124);
  dmg_tbldata_p = v125;
  v127 = GetLength(v123, 0);
  if (v127 >= 1)
  {
    v128 = 0;
    v129 = v127;
    v130 = 32;
    do
    {
      dmg_tbldata_p_local = dmg_tbldata_p;
      v133 = GetEFFDMG_TBL(v123, v128, 0);
      v134 = v133;
      *(Il2CppClass **)((char *)&dmg_tbldata_p_local->obj.klass + v130) = v134;
      ++v128;
      v130 += 8;
    }
    while (v129 != v128);
  }
  v136 = LoadAsset(_Ctrl_k__BackingField, "battle", "sb_motionmv", 0);
  {
    if (v136->klass->_2.typeHierarchy[v137 - 1] == Project_BattleDevilMotionMove)
      v138 = v136;
    else
      v138 = 0;
  }
  else
  {
    v138 = 0;
  }
  v139 = NewSpecific(MOTIONMOVE_WORK, 0x220u);
  sbtlmotionmv_tbldata = v139;
  v142 = 0;
  v143 = 32;
  do
  {
    sbtlmotionmv_tbldata_local = sbtlmotionmv_tbldata;
    DEVILMOTIONMOVE = GetDEVILMOTIONMOVE(v138, v142, 0);
    v147 = DEVILMOTIONMOVE;
    *(Il2CppClass **)((char *)&sbtlmotionmv_tbldata_local->obj.klass + v143) = v147;
    ++v142;
    v143 += 8;
  }
  while (v142 != 544);
  v149 = LoadAsset(_Ctrl_k__BackingField, "battle", "sb_devilformat", 0);
  {
    if (v149->klass->_2.typeHierarchy[v150 - 1] == Project_BattleDevilFormat)
      v151 = v149;
    else
      v151 = 0;
LABEL_233:
    sBtlSetDevilDataInit(0, v151);
    goto LABEL_234;
  }
  else
  {
    v151 = 0;
    goto LABEL_233;
  }
  sBtlSetDevilDataInit(0, v151);
LABEL_234:
  v154 = LoadAsset(_Ctrl_k__BackingField, "battle", "sb_devilformat_hyakki", 0);
  {
    sBtlSetDevilDataInit(1, 0);
    goto LABEL_238;
  }
  if (v154->klass->_2.typeHierarchy[v155 - 1] == Project_BattleDevilFormat)
    v163 = v154;
  else
    v163 = 0;
  sBtlSetDevilDataInit(1, v163);
LABEL_238:
  v157 = LoadAsset(_Ctrl_k__BackingField, "battle", "sb_devilhuumaitem", 0);
  {
    sBtlSetDevilHuumaItemInit(0, 0);
    goto LABEL_242;
  }
  if (v157->klass->_2.typeHierarchy[v158 - 1] == Project_BattleDevilHuumaItem)
    v164 = v157;
  else
    v164 = 0;
  sBtlSetDevilHuumaItemInit(0, v164);
LABEL_242:
  v160 = LoadAsset(_Ctrl_k__BackingField, "battle", "sb_devilhuumaitem_DLC", 0);
  {
    if (v160->klass->_2.typeHierarchy[v161 - 1] == Project_BattleDevilHuumaItem)
      v162 = v160;
    else
      v162 = 0;
  }
  else
  {
    v162 = 0;
  }
  sBtlSetDevilHuumaItemInit(1, v162);
  v165 = NewSpecific(SBTLAISYO_DATAWORK, 0x220u);
  aisyo_tbldata = v165;
  v168 = LoadAsset(_Ctrl_k__BackingField, "battle", "sb_aisyotbl", 0);
  {
    if (v168->klass->_2.typeHierarchy[v169 - 1] == Project_BattleAisyoTbl)
      v170 = v168;
    else
      v170 = 0;
  }
  else
  {
    v170 = 0;
  }
  v171 = 0;
  v172 = 32;
  do
  {
    aisyo_tbldata_local = aisyo_tbldata;
    AISYOTBL = GetAISYOTBL(v170, v171, 0);
    v176 = AISYOTBL;
    *(Il2CppClass **)((char *)&aisyo_tbldata_local->obj.klass + v172) = v176;
    ++v171;
    v172 += 8;
  }
  while (v171 != 544);
  v179 = LoadAsset(_Ctrl_k__BackingField, "battle", "ai_scr.bf", 0);
  v180 = Allocate(sdfBinary);
  _ctor(v180, v179, 0);
  data = v180->data;
  ai_scr = data;
  v185 = LoadAsset(_Ctrl_k__BackingField, "battle", "huuma_success_scr.bf", 0);
  v186 = Allocate(sdfBinary);
  _ctor(v186, v185, 0);
  v187 = v186->data;
  huuma_success_scr = v187;
  v190 = tbldata;
  autotbldata = v190;
  LevelDataLoad();
  v193 = LoadAsset(_Ctrl_k__BackingField, "battle", "CamMoveDtHDTbl", 0);
  if (!v193)
  {
    v197 = 0;
    p_g_aCamMoveDtHd = &g_aCamMoveDtHd;
    p_g_aCamMoveDtHd = 0;
    goto LABEL_323;
  }
  if (v193->klass->_2.naturalAligment >= (u32)v195)
  {
    if (v193->klass->_2.typeHierarchy[v195 - 1] == Project_CamMoveDtHDTbl)
      v196 = v193;
    else
      v196 = 0;
  }
  else
  {
    v196 = 0;
  }
  g_aCamMoveDtHd = (void *)v196;
  p_g_aCamMoveDtHd = &g_aCamMoveDtHd;
  if (v193->klass->_2.naturalAligment >= (u32)v195)
  {
    if (v193->klass->_2.typeHierarchy[v195 - 1] == Project_CamMoveDtHDTbl)
      v197 = v193;
    else
      v197 = 0;
  }
  else
  {
    v197 = 0;
  }
LABEL_323:
  Load(0);
}

// 0x1ec3ad0
void ReloadDLCTableData(void) {
  void *Asset;
  s64 naturalAligment;
  void *v6;

  EncountAiPackLoad();
  Asset = LoadAsset(_Ctrl_k__BackingField, "battle", "sb_devilhuumaitem_DLC", 0);
  {
    if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_BattleDevilHuumaItem)
      v6 = Asset;
    else
      v6 = 0;
  }
  else
  {
    v6 = 0;
  }
  sBtlSetDevilHuumaItemInit(1, v6);
  Unload(Dependent, "battle", 0);
}

// 0x1ec3ca0
void Printf(char *str, void *LegacyParamArray) {
  ;
}

// 0x1ec3cb0
void Init(s32 mode, s32 encountno) {
  SBATTLE_WORK *v4;
  SBATTLE_WORK *wk_local;
  SBATTLE_WORK *v12;
  SBATTLE_WORK *v16;
  SBATTLE_WORK *v18;
  s32 v19;
  s32 v20;
  s32 v22;
  u32 v23;
  s64 v24;
  SBATTLE_WORK *v27;
  u32 v28;
  SBATTLE_WORK *v29;
  SBTLDMG_LISTWORK *AnimList;
  SBATTLE_WORK *v31;
  SBTLDMG_HITLISTWORK *HitList;
  SBATTLE_WORK *v33;
  SBTLEFF_LISTWORK *EffList;
  SBATTLE_WORK *v35;
  SBTLDVLTK_LISTWORK *DvltkList;
  SBATTLE_WORK *v37;
  SBTLEXP_LISTWORK *EXPList;
  SBATTLE_WORK *v39;
  SBTLSTP_LISTWORK *STPList;
  SBTLUNIT_LISTWORK *p_tgtList;
  SBTLUNIT_LISTWORK *p_friend_List;
  SBTLUNIT_LISTWORK *p_other_List;
  SBTLUNIT_LISTWORK *p_other_List2;
  s64 v45;
  s64 v46;
  SBATTLE_WORK *v48;
  u32 v49;
  s32 *vibe;
  Il2CppObject *v51;
  SBTLUNIT_LISTWORK *UnitList;
  SBATTLE_WORK *v54;
  SBTLUNIT_LISTWORK *v55;
  SBATTLE_WORK *v56;
  SBTLITEM_LISTWORK *ItemList;
  SBATTLE_WORK *v58;
  SBTLITEM_LISTWORK *v59;
  SBATTLE_WORK *v60;
  SBTLITEM_LISTWORK *v61;
  SBATTLE_WORK *v62;
  SBTLSM_LISTWORK *SMList;
  SBATTLE_WORK *v64;
  SBTLEFF_DELLISTWORK *DelList;
  s64 v67;
  s64 v68;
  s64 v69;
  SBATTLE_WORK *v70;
  u32 v71;
  s32 *aMagEff;
  Il2CppObject *v73;
  s32 v75;
  u32 v76;
  SBATTLE_WORK *v83;
  SBATTLE_WORK *v84;
  SBATTLE_WORK *v85;
  u32 v86;
  s32 start_debug_menu_on;
  sdatPlayerUnitWork_t *player;
  sdatPlayerUnitWork_t *v89;
  Il2CppObject *v92;
  SBATTLE_WORK *v94;
  SBTLUNIT_WORK *PChara;

  v4 = Allocate(SBATTLE_WORK);
  _ctor(v4, 0);
  wk = v4;
  *(u32 *)stack_p_backup = -1;
  *(u64 *)&exit2_flag = 0;
  *(u16 *)&escape_checkflg = 0;
  wk_local = wk;
  *(u32 *)wk_local->returnindex = -1;
  wk_local->sukacnt = 0;
  wk_local->gStartBossCamCnt = 0;
  *(u64 *)&wk_local->RouletteAfterTime = 0x100000000LL;
  sBtlSetStaticInit();
  sBtlSetFollowUpCameraPar();
  v12 = wk;
  v12->camera_mode = -1;
  *(u64 *)&v12->all_encount_max = 0;
  *(u16 *)&v12->TipsDone_WEAK_SHIELD = 0;
  v12->fast_dying = 0;
  v12->NakamaShugouOn = 0;
  v12->enemy_zenmetu = 0;
  v12->all_encount_cnt = 0;
  *(u32 *)&v12->TipsDone_KATANA_S = 0;
  v12->sprit_waza = GBWK->player->sprit_waza;
  sBtlRaidouWazaCoolTimeInit();
  v16 = wk;
  *(u16 *)&v16->BtlEnd_Boss_Sprit = 0;
  *(_OWORD *)&v16->hitCombDevilTalk_1 = 0u;
  *(u64 *)((char *)&v16->deadDevilTalk_log1 + 1) = 0;
  if (mode >= 4)
  {
    goto LABEL_22;
  }
  if (mode < 0)
  {
    wk->battlemode = 0;
    goto LABEL_17;
LABEL_22:
    v16->battlemode = 0;
    goto LABEL_17;
  }
  wk->battlemode = mode;
LABEL_17:
  v18 = wk;
  if (v18->battlemode == 2)
  {
    v94 = wk;
    v94->battlemode = 0;
    v94->is_jyuso = 1;
  }
  v19 = 0;
  wk->r2ng = 0;
  v20 = (u8)byte_5755E7B;
  do
  {
    if (v20)
    {
      goto LABEL_27;
    }
    else
    {
      v20 = 1;
      goto LABEL_27;
    }
    v20 = (u8)byte_5755E7B;
LABEL_27:
    v22 = 1 << v19;
    v23 = (u32)(v19 + 3040) >> 5;
    ++v19;
    v24 = (s64)GBWK->EventBit + 4 * v23;
    *(u32 *)(v24 + 32) &= ~v22;
  }
  while (v19 != 16);
  if (encountno)
  {
    v27 = wk;
    v27->start_debug_menu_on = 0;
    v27->encountno = encountno;
    if (!v28)
    {
LABEL_35:
    }
  }
  else
  {
    v85 = wk;
    v85->start_debug_menu_on = 1;
    v85->encountno = dbg_encount_bk;
    if (!v86)
      goto LABEL_35;
  }
  v29 = wk;
  v29->mf_abgr = -2139062144;
  v29->mfh_abgr = -2139062144;
  *(int8x8_t *)&v29->status = vand_s8(*(int8x8_t *)&v29->status, (int8x8_t)0xEFFFFFFFFFFFFFF7LL);
  v29->mode = 1;
  AnimList = sBtlCreateAnimList();
  v29->dmgList = AnimList;
  v31 = wk;
  HitList = sBtlCreateHitList();
  v31->hitList = HitList;
  v33 = wk;
  EffList = sBtlCreateEffList();
  v33->effList = EffList;
  v35 = wk;
  DvltkList = sBtlCreateDvltkList();
  v35->dvltkList = DvltkList;
  v37 = wk;
  EXPList = sBtlCreateEXPList();
  v37->expList = EXPList;
  sbtlInit();
  v39 = wk;
  STPList = sBtlCreateSTPList();
  v39->stpList = STPList;
  p_tgtList = &wk->tgtList;
  p_tgtList = 0;
  p_friend_List = &wk->friend_List;
  p_friend_List = 0;
  p_other_List = &wk->other_List;
  p_other_List = 0;
  p_other_List2 = &wk->other_List2;
  p_other_List2 = 0;
  v45 = 0;
  v46 = 8;
  while (2)
  {
    v48 = wk;
    vibe = v48->vibe;
    if (v45 < vibe[6])
    {
      if (v49)
      {
        v51 = Allocate(SBTLVIBE_WORK);
        _ctor(v51, 0);
        if (!v51)
          goto LABEL_47;
      }
      else
      {
        vibe = wk->vibe;
        v51 = Allocate(SBTLVIBE_WORK);
        _ctor(v51, 0);
        if (!v51)
        {
LABEL_47:
          *(u64 *)&vibe[v46] = v51;
          ++v45;
          v46 += 2;
          continue;
        }
      }
      if (!QueryInterface(v51, *(void **)(*(u64 *)vibe + 64)))
      {
LABEL_89:
      }
      goto LABEL_47;
    }
    break;
  }
  if (v49)
  {
    goto LABEL_59;
  }
  else
  {
    v48 = wk;
  }
LABEL_59:
  UnitList = sBtlCreateUnitList(48);
  v48->targetList = UnitList;
  v54 = wk;
  v55 = sBtlCreateUnitList(48);
  v54->enemyList = v55;
  v56 = wk;
  ItemList = sBtlCreateItemList();
  v56->itemList = ItemList;
  v58 = wk;
  v59 = sBtlCreateItemList();
  v58->bulletList = v59;
  v60 = wk;
  v61 = sBtlCreateItemList();
  v60->katanaList = v61;
  v62 = wk;
  SMList = sBtlCreateSMList();
  v62->sysmsgList = SMList;
  v64 = wk;
  DelList = sBtlCreateDelList();
  v64->effdelList = DelList;
  sBtlEntryItemList(wk->itemList);
  sBtlEntryItemList_Type(wk->bulletList, 4u);
  sBtlEntryKatanaList(wk->katanaList);
  sBtlInitTutorial();
  Init();
  sBtlClearGeneratorWork();
  Init();
  sBtlAllInit();
  ProcessStart(0);
  sBtlInit();
  GuideDispStop(0);
  Init();
  sBtlPacData_Init();
  sBtlEisyoWaitTask();
  sBtlInitAddMag();
  v67 = 0;
  v68 = 8;
  while (2)
  {
    v70 = wk;
    aMagEff = v70->aMagEff;
    if (v67 < aMagEff[6])
    {
      if (v71)
      {
        v73 = Allocate(SBTL_MAGEFF);
        _ctor(v73, 0);
        if (!v73)
          goto LABEL_80;
      }
      else
      {
        aMagEff = wk->aMagEff;
        v73 = Allocate(SBTL_MAGEFF);
        _ctor(v73, 0);
        if (!v73)
        {
LABEL_80:
          *(u64 *)&aMagEff[v68] = v73;
          v69 = *(s64 *)((char *)&wk->aMagEff->obj.klass + v68 * 4);
          v68 += 2;
          *(u32 *)(v69 + 140) = v67++;
          continue;
        }
      }
      if (!QueryInterface(v73, *(void **)(*(u64 *)aMagEff + 64)))
        goto LABEL_89;
      goto LABEL_80;
    }
    break;
  }
  if (!v71)
  {
    v70 = wk;
    start_debug_menu_on = v70->start_debug_menu_on;
    v70->pMagEffNextSearch = 0;
    if (!start_debug_menu_on)
      goto LABEL_121;
LABEL_92:
    if (!v76)
      goto LABEL_93;
    goto LABEL_94;
  }
  v75 = v70->start_debug_menu_on;
  v70->pMagEffNextSearch = 0;
  if (v75)
    goto LABEL_92;
LABEL_121:
  if (!v76)
  {
    v70 = wk;
    if (!v70->weaponId)
      goto LABEL_143;
LABEL_123:
    player = GBWK->player;
    v89 = player;
    player->swordno = wk->weaponId;
    datSetPlayerSword(v89->swordno, 0);
    PChara = sBtlGetPChara();
    datCalcNowParam(PChara->para, GBWK->player->swordno, 0);
    datDvlParaUpdate(0);
    goto LABEL_96;
  }
  if (v70->weaponId)
    goto LABEL_123;
LABEL_143:
LABEL_93:
  v70 = wk;
LABEL_94:
  v70->weaponId = sBtlGetPlayerData()->swordno;
LABEL_96:
  sBtlInitLoadPlayerOnMemData();
  do
  {
  }
  while (!sBtlLoadEndCheck_PlayerOnMemData());
  do
  {
  }
  while (!sBtlLoadPlayerOnMemData());
  wk->encount_fieldmap_load_done = 0;
  battle_map_loadend = 1;
  if (!IsLoaded())
  {
    battle_map_loadend = 0;
    v92 = AddComponent_object_(hook);
    battleMap = (void *)v92;
  }
  Init();
  sBtlSetGunNum(6);
  v83 = wk;
  v83->timecount = 18000;
  v83->hitokoto_spirit = 0;
  itfBattleEvtKeyWaitInit();
  v84 = wk;
  v84->tuto_r2_di = 0;
  v84->bAssistAttackBtn = 0;
}

// 0x1ec4be0
dds3ProcessFunc_t Proc(dds3ProcessID_t *id) {
  bool v4;
  char v6;
  u32 status;
  SBATTLE_WORK *v10;
  void *bsc;
  SBTLDVLTK_LISTWORK *dvltkList;
  SBTLEXP_LISTWORK *expList;
  SBTLSM_LISTWORK *sysmsgList;
  bool IsSceanStop;
  bool v33;
  SBATTLE_WORK *v34;
  bool v35;
  SBATTLE_WORK *v36;
  u32 NotCmbSkl_Cnt;
  SBATTLE_WORK *v38;
  u32 NotCmbSkl_Cnt2;
  SBATTLE_WORK *v40;
  u32 NotSinaba_Cnt;
  bool v42;
  SBATTLE_WORK *v44;
  s32 *scrCnt;
  s32 *enshutuCnt;
  SBATTLE_WORK *v50;
  u32 v55;
  s64 v56;

  v4 = cfgGetConfigGAME(10, 0) == 0;
  v6 = !v4;
  wk->bAssistAttackBtn = v6;
  if (!dds3SearchProcessName("sbattle"))
    return 0;
  sBtlGetMemoryStatus();
  if ((wk->status & 8) == 0)
    goto LABEL_16;
  goto LABEL_28;
  if ((wk->status & 8) != 0)
  {
LABEL_28:
    MokutekiOFF();
    Exit();
    return 0;
  }
LABEL_16:
  GetRand(0x5Fu);
  status = wk->status;
  if ((status & 0x10000) == 0)
  {
    status = wk->status;
    if ((status & 0x80000000) == 0)
    {
      sBtlCheckStartBattle();
    }
  }
  v10 = wk;
  if ((v10->status & 0x80000000) != 0)
  {
    v10 = wk;
    if (v10->bBfrBtlEnd)
    {
      v10 = wk;
      v10->status = v10->status & 0x7FFEFFFF | 0x10000;
      v10->status2 &= ~0x80000u;
    }
  }
  sBtlClearStartTime_Damage();
  ProcStart();
  SmnCtrlRun();
  sBtlRunSklProc();
  sBtlEisyoWaitTask();
  sBtlAttackwaitWaitTask();
  sBtlCheckPad();
  sBtlProcHitStop();
  sBtlProcSetsumaPadStop();
  sBtlProcEnemyLastDeadStop();
  sBtlMapFadeProc();
  sBtlMapFadeProc_H();
  bsc = wk->bsc;
  if (!op_Inequality(bsc, 0, 0))
  {
    goto LABEL_52;
  }
  sBtlSetCameraLockOnTgtUpdate();
LABEL_52:
  Proc(0);
  dvltkList = wk->dvltkList;
  Proc(dvltkList);
  sBtlReleaseDvltk_List(wk->dvltkList, 0);
  expList = wk->expList;
  Proc(expList);
  sBtlReleaseEXP_List(wk->expList, 0);
  sysmsgList = wk->sysmsgList;
  Proc(sysmsgList);
  sBtlReleaseSM_List(wk->sysmsgList, 0);
  sbtlProc();
  Proc(wk->stpList);
  sBtlReleaseSTP_List(wk->stpList, 0);
  sBtlGeneratorProc();
  itfBattleEvtKeyWaitProc();
  sBtlMainProc();
  Proc(0);
  sBtlCalcVibe();
  sBtlUpdateVibe();
  ++wk->syscnt;
  IsSceanStop = IsSceanStop();
  if (!IsSceanStop)
    goto LABEL_138;
  if ((wk->scrFlag & 1) != 0)
    goto LABEL_138;
LABEL_84:
  if (!IsSceanStop())
    goto LABEL_153;
  GetRand(0x20u);
  goto LABEL_87;
LABEL_138:
  v44 = wk;
  scrCnt = v44->scrCnt;
  ++scrCnt[0];
  ++scrCnt[1];
  ++scrCnt[2];
  ++scrCnt[3];
  enshutuCnt = v44->enshutuCnt;
  ++enshutuCnt[0];
  ++enshutuCnt[1];
  ++enshutuCnt[2];
  ++enshutuCnt[3];
  ++enshutuCnt[4];
  ++enshutuCnt[5];
  ++enshutuCnt[6];
  ++enshutuCnt[7];
  goto LABEL_84;
LABEL_153:
  v50 = wk;
  if ((v50->status2 & 0x80000) != 0)
  {
    v50 = wk;
    v50->RouletteAfterTime = 0;
    GetRand(0x20u);
    goto LABEL_87;
  }
  v50 = wk;
  ++v50->RouletteAfterTime;
  GetRand(0x20u);
LABEL_87:
  CheckEnd();
  sBtlMainDraw2();
  CalcUpdate();
  sBtlRaidouWazaCoolTimeUpdate();
  if (wk->bBfrBtlEnd)
  {
    v33 = IsSceanStop();
    if (!v33)
    {
      v34 = wk;
      if (!v34->cmbSkl->bRun)
      {
        v34 = wk;
        if (!v34->sklProc->bRun)
        {
          v34 = wk;
          if (!v34->kaiwaflg)
          {
            v35 = sBtlCheckPlayerDead();
            if (!v35)
            {
              v36 = wk;
              NotCmbSkl_Cnt = v36->NotCmbSkl_Cnt;
              if (NotCmbSkl_Cnt)
              {
                v36 = wk;
                NotCmbSkl_Cnt = v36->NotCmbSkl_Cnt;
                v36->NotCmbSkl_Cnt = NotCmbSkl_Cnt - 1;
              }
              v38 = wk;
              NotCmbSkl_Cnt2 = v38->NotCmbSkl_Cnt2;
              if (NotCmbSkl_Cnt2)
              {
                v38 = wk;
                NotCmbSkl_Cnt2 = v38->NotCmbSkl_Cnt2;
                v38->NotCmbSkl_Cnt2 = NotCmbSkl_Cnt2 - 1;
              }
              v40 = wk;
              NotSinaba_Cnt = v40->NotSinaba_Cnt;
              if (NotSinaba_Cnt)
              {
                v40 = wk;
                NotSinaba_Cnt = v40->NotSinaba_Cnt;
                v40->NotSinaba_Cnt = NotSinaba_Cnt - 1;
              }
              if (wk->timeflg)
              {
                v42 = sBtlCheckEnemyAllDead();
                if (!v42)
                {
                  ++gb_btltime;
                }
              }
              else
              {
              }
              ++gb_btlaitime;
              Check(0);
            }
          }
        }
      }
    }
  }
  if (wk->mode == 5)
    goto LABEL_191;
  if (tipsProcessCheck())
    goto LABEL_191;
  if (sBtlIsSetsumaPadStop() || sBtlIsEnemyLastDeadStop())
  {
LABEL_191:
    gShaderUVScroll = 0;
    return 0;
  }
  if ((wk->status4 & 0x400000) != 0)
  {
    if (!v55)
    v56 = 0;
  }
  else
  {
    if (!v55)
    v56 = 1;
  }
  (loc_1ED51F0)(v56, 0);
  return 0;
}

// 0x1ec97c0
void Shutdown(dds3ProcessID_t *id) {
  if (!mefMistTexOnDataCheck())
  {
LABEL_5:
    get_Instance(0);
    JUMPOUT(0x18B2D40);
    goto LABEL_5;
  }
  mefMistTexDestroy();
  goto LABEL_5;
}

// 0x1ec98b0
dds3ProcessFunc_t DrawProc(dds3ProcessID_t *id) {
  void *bsc;
  SBTLDVLTK_LISTWORK *dvltkList;
  SBATTLE_WORK *v11;

  if (!dds3SearchProcessName("sbattle"))
    return 0;
  if (!wk)
    goto LABEL_31;
  if ((wk->status & 8) == 0)
  {
    bsc = wk->bsc;
    if (!op_Inequality(bsc, 0, 0))
    {
LABEL_17:
      Draw();
      Draw();
      sBtlMainDraw();
      sBtlDrawEscapeGauge(32, 384);
      dvltkList = wk->dvltkList;
      Draw(dvltkList, 0);
      Draw(wk->stpList, 0);
      EventProc();
      DrawUpdate();
      return 0;
    }
    SpriteClear(wk->bsc, 0);
    goto LABEL_17;
  }
LABEL_31:
  v11 = wk;
  if (!v11)
    return 0;
  v11 = wk;
    return 0;
}

// 0x1ec9c50
dds3ProcessFunc_t DrawProc2(dds3ProcessID_t *id) {
  void *bsc;
  SBTLDMG_HITLISTWORK *hitList;
  SBTLEFF_LISTWORK *effList;
  SBTLSM_LISTWORK *sysmsgList;

  if (!dds3SearchProcessName("sbattle"))
    return 0;
  if (!wk)
    return 0;
  if ((wk->status & 8) != 0)
    return 0;
  bsc = wk->bsc;
  if (!!op_Inequality(bsc, 0, 0))
    SpriteClear2(wk->bsc, 0);
  hitList = wk->hitList;
  sBtlHitCProc_Idou(hitList);
  effList = wk->effList;
  sBtlListProc(effList);
  sBtlReleaseEff(wk->effList, 0);
  sBtlAnimListProc();
  sBtlHitCProc(wk->hitList);
  sBtlReleaseHitC_List(wk->hitList, 0);
  sBtlDelProc(wk->effdelList);
  sBtlReleaseDelList(wk->effdelList, 0);
  Draw();
  sBtlDrawAnimList();
  sysmsgList = wk->sysmsgList;
  Draw(sysmsgList, 0);
  DrawTime();
  return 0;
}

// 0x1ec8370
bool CheckEnd(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v5;
  SBATTLE_WORK *v7;
  s32 mode;
  bool v10;
  u32 *p_status;
  s64 v14;
  SBATTLE_WORK *v18;
  u32 status;
  s32 v20;
  SBATTLE_WORK *v22;
  SBATTLE_WORK *v23;
  SBATTLE_WORK *v26;
  u32 v27;
  s32 endcnt;
  s32 v29;
  s32 v30;
  SBATTLE_WORK *v31;
  SBTLUNIT_LISTWORK *v34;
  s32 v35;
  SBTLUNIT_WORK *v36;
  SBATTLE_WORK *v39;
  SBTLUNIT_LISTWORK *v40;
  s32 v41;
  sdatUnitWork_t *para;
  s32 battlemode;
  SBTLEFF_LISTWORK *effList;
  void *Instance;
  void *v49;
  void *v51;
  void *v52;
  void *v53;
  void *v54;
  void *v55;
  SBATTLE_WORK *v57;
  void *v58;
  SBTLUNIT_WORK *PChara;
  f32 v60;
  f32 v61;
  f32 v62;
  SBTLUNIT_WORK *Nakama;
  s32 vstatus;
  SBTLUNIT_WORK *v66;
  s64 v67;
  SBTLUNIT_WORK *v68;
  SBTLACTAI_WORK *actaiwk;
  SBTLUNIT_WORK *v70;
  s32 v71;
  SBTLUNIT_WORK *v72;
  s64 v73;
  SBTLUNIT_WORK *v74;
  SBTLACTAI_WORK *v75;
  s32 v77;
  SBATTLE_WORK *v79;
  SBATTLE_WORK *v81;
  s32 BtlEnd_BossFedeOut;
  SBATTLE_WORK *v83;
  s32 v84;
  s32 v85;
  SBATTLE_WORK *v86;
  bool v87;
  void *achievementTbl_k__BackingField;
  Project_DefineAchievementID_string__c *klass;
  s64 v91;
  Project_DefineAchievementID_string__c **p_offset;
  s64 v93;
  s32 v96;
  SBATTLE_WORK *v98;
  SBATTLE_WORK *v100;
  s32 v102;
  char *v103;
  bool v104;
  f32 ZeroZ;
  s64 ZeroY;

  ZeroY = 0;
  ZeroZ = 0.0;
  if (!sBtlCheckLoadFlg())
    return 1;
  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v5 = sBtlSearchUnit_ID(UnitMng, playerID);
  if (v5->actwk->status == 34)
  {
    v7 = wk;
    if ((v7->status & 0x1000000) != 0)
      goto LABEL_38;
    mode = v7->mode;
    if (mode == 5)
      goto LABEL_38;
    v7 = wk;
    mode = v7->mode;
    if (mode != 6)
    {
      v7 = wk;
      mode = v7->mode;
      if (mode != 13)
      {
        v7 = wk;
        v7->status |= 0x40000000u;
        End();
        if ((v5->para->badstatus & 0x20000) == 0)
        {
          if (sBtlCheckUnit_Exec())
          {
            v10 = sBtlCheckTutorialBattle();
            if (v10)
              goto LABEL_33;
            goto LABEL_9000;
            if (v104)
            {
LABEL_33:
              v5->para->badstatus |= 0x20000u;
              goto LABEL_34;
            }
LABEL_9000:
            wk->status |= 0x20u;
            v5->para->badstatus |= 0x20000u;
LABEL_34:
            p_status = &wk->status;
            LODWORD(v14) = *(u64 *)p_status | 8;
            HIDWORD(v14) = HIDWORD(*(u64 *)p_status) & 0xEFFFFFFF;
            *(u64 *)p_status = v14;
            sBtlInitDropWork();
            sBtlSetEndData();
            sBtlCheckBattleLose();
            return 1;
          }
        }
      }
    }
  }
LABEL_38:
  v18 = wk;
  if (v18->kaiwaflg)
    goto LABEL_82;
  if (!v18->bNoEndCam)
  {
    v18 = wk;
    if (!v18->cmbSkl->bRun && v5->actwk->status != 34)
    {
      v18 = wk;
      if ((v18->status & 0x1000000) == 0)
      {
        status = v5->actwk->status;
        if (status != 10 && status != 40)
        {
          v18 = wk;
          v20 = v18->mode;
          if (v20 != 5)
          {
            v18 = wk;
            v20 = v18->mode;
            if (v20 != 6)
            {
              v18 = wk;
              v20 = v18->mode;
              if (v20 != 13)
              {
                v18 = wk;
                if (!v18->enemy_num)
                {
                  if (!sBtlCheckSetsuma())
                  {
                    if (!sBtlChkNakama_SkillUse_SHINEBA())
                    {
                      if (!sBtlCheckGeneratorAll())
                        goto LABEL_81;
                      if (!sBtlCheckGenerator_ND())
                      {
LABEL_81:
                        if ((wk->status5 & 0x40) == 0)
                          goto LABEL_88;
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
LABEL_82:
  v22 = wk;
  if ((v22->status2 & 0x10000) == 0)
  {
    v22 = wk;
    v22->endcnt = 0;
    return 1;
  }
LABEL_88:
  v23 = wk;
  v23->bNoUseSkl = 1;
  End();
  v26 = wk;
  v27 = v26->status;
  endcnt = v26->endcnt;
  v26->r2ng = 1;
  v26->mode = 0;
  v29 = v27 | 0x40000000;
  v30 = endcnt + 1;
  v31 = v26;
  v26->status = v29;
  v26->endcnt = v30;
  v30 = v26->endcnt;
  v31 = wk;
  v34 = v31->UnitMng;
  if (v30 >= 0x7FFF)
    v30 = 0x7FFF;
  v26->endcnt = v30 & ~(v30 >> 31);
  v35 = v31->playerID;
  v36 = sBtlSearchUnit_ID(v34, v35);
  if (wk->endcnt != 1)
    goto LABEL_172;
  sBtlShugouKaijyo();
  sBtlResetGunMode_Eve();
  v39 = wk;
  v40 = v39->UnitMng;
  v41 = v39->playerID;
  v36 = sBtlSearchUnit_ID(v40, v41);
  para = v36->para;
  sBtlGetBadStatus(para);
  if (v36->actwk->status != 42)
  {
    v36->vstatus |= 0x8000000u;
    sBtlResetBadStatus(v36, 98303);
    battlemode = (u16)wk->battlemode;
    if (battlemode == 1)
    {
      goto LABEL_113;
    }
    v36->next_motion_not_hokan = 1;
    battlemode = (u16)wk->battlemode;
    if (battlemode == 3)
      v102 = 4;
    else
      v102 = 12;
    sBtlSetMotion(v36, v102, 0, 0, 0);
LABEL_113:
    effList = wk->effList;
    sBtlForceDelete_ID_Acter(effList, v36, 55);
    sBtlResetCharge(v36, 0);
    sBtlResetJump(v36);
    sBtlReleaseSTP_List(wk->stpList, 1u);
    Instance = get_Instance(0);
    ButtleEndUIClr(Instance, 0);
    v49 = get_Instance(0);
    BtlEnd(v49, 0);
    sBtlBattleVictoryStart();
    MokutekiOFF();
    v51 = get_Instance(0);
    CharaIconActive(v51, 0, 0);
    v52 = get_Instance(0);
    AllInOut(v52, 0, 1, 1, 1, 0);
    v53 = get_Instance(0);
    SetumaButton(v53, 0, 0);
    v54 = get_Instance(0);
    DevilHPactive(v54, 0, 0);
    v55 = get_Instance(0);
    if (GetTimeLimitAnim(v55, 0) == 1)
    {
      v58 = get_Instance(0);
      TimeLimitChangeAnim(v58, 2, 0);
LABEL_125:
      v57 = wk;
      if (v57->bNoEndCam)
        goto LABEL_159;
LABEL_131:
      v57 = wk;
      if (v57->camera_mode != 1)
      {
        sBtlGetZeroPos((f32 *)&ZeroY + 1, &ZeroY, &ZeroZ);
        PChara = sBtlGetPChara();
        if (PChara)
        {
          v60 = *(f32 *)&ZeroY;
          v61 = ZeroZ;
          v62 = *((f32 *)&ZeroY + 1) + 0.0;
          PChara->L2_muteki = 1;
          PChara->rot = (struct sdfVector4_t)xmmword_3CFD5C0;
          PChara->pos.x = v62;
          PChara->pos.y = v60 + 0.0;
          PChara->pos.z = v61 + 0.0;
        }
        if (wk->battlemode != 3)
        {
          Nakama = sBtlGetNakama(0);
          if (Nakama)
          {
            vstatus = Nakama->vstatus;
            v66 = Nakama;
            Nakama->JumpOfsPos.y = 0.0;
            Nakama->vstatus = vstatus & 0xFFFFEFFF;
            sBtlUpdateUnitJumpOfsPos(v66);
            sBtlBgnWait(v66);
            v67 = ZeroY;
            v66->next_motion_not_hokan = 1;
            v66->pos.x = *((f32 *)&v67 + 1) + -197.645;
            v66->pos.y = *(f32 *)&v67 + 0.0;
            v66->rot = (struct sdfVector4_t)xmmword_3CFD5C0;
            v66->pos.z = ZeroZ + 151.63;
            sBtlSetMotion(v66, 0, 0, 0, 0);
            v68 = sBtlGetNakama(0);
            v68->status &= 0xFFFFFFF9;
            v66->L2_muteki = 1;
            sBtlSetAction(v66, 1, 0);
            v66->actwk->use_skillid = 0;
            actaiwk = v66->actaiwk;
            v66->aiwk->mode = 12;
            actaiwk->stat = 1;
          }
          v70 = sBtlGetNakama(1);
          if (v70)
          {
            v71 = v70->vstatus;
            v72 = v70;
            v70->JumpOfsPos.y = 0.0;
            v70->vstatus = v71 & 0xFFFFEFFF;
            sBtlUpdateUnitJumpOfsPos(v72);
            sBtlBgnWait(v72);
            v73 = ZeroY;
            v72->next_motion_not_hokan = 1;
            v72->pos.x = *((f32 *)&v73 + 1) + 197.645;
            v72->pos.y = *(f32 *)&v73 + 0.0;
            v72->rot = (struct sdfVector4_t)xmmword_3CFD5C0;
            v72->pos.z = ZeroZ + 151.63;
            sBtlSetMotion(v72, 0, 0, 0, 0);
            v74 = sBtlGetNakama(1);
            v74->status &= 0xFFFFFFF9;
            v72->L2_muteki = 1;
            sBtlSetAction(v72, 1, 0);
            v72->actwk->use_skillid = 0;
            v75 = v72->actaiwk;
            v72->aiwk->mode = 12;
            v75->stat = 1;
          }
        }
        if (wk->battlemode == 3)
        {
          v77 = sub_1905740(3, 0);
          sBtlSetMove(g_aCamMovEnd[v77], 1);
          sBtlSetDof2Bokah(1.0, 2.5, 90.0, 12.0, 2.5, 90.0, 12.0);
          sBtlSetMode(1);
          Proc(0);
        }
      }
      goto LABEL_159;
    }
    else
    {
      goto LABEL_125;
    }
    v57 = wk;
    if (v57->bNoEndCam)
      goto LABEL_159;
    goto LABEL_131;
  }
LABEL_159:
  sBtlResetATKEffect();
  sBtlForceDeleteAll(0);
  sBtlForceDeleteAll_TimeStopSkill(0, 0);
  sBtlPlayerDeleteFootEff();
  dds3StopQuake();
  sBtlSetAction(v36, 42, 0);
  sBtlSetEndBadStatus();
  goto LABEL_171;
LABEL_172:
  goto LABEL_174;
LABEL_171:
  if (wk->encountno != 66)
    goto LABEL_172;
  achievementTbl_k__BackingField = _achievementTbl_k__BackingField;
  klass = achievementTbl_k__BackingField->klass;
  v91 = *(u16 *)&achievementTbl_k__BackingField->klass->_2.rank;
  if (*(u16 *)&achievementTbl_k__BackingField->klass->_2.rank)
  {
    p_offset = &klass->_1.interfaceOffsets->offset;
    while (*(p_offset - 1) != Project_DefineAchievementID_string_)
    {
      p_offset += 2;
      if (!--v91)
        goto LABEL_214;
    }
    v93 = &klass->vtable[*(u32 *)p_offset + 17];
  }
  else
  {
LABEL_214:
    v93 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 0x11u);
  }
  v103 = (*v93)(achievementTbl_k__BackingField, *(u64 *)(v93 + 8));
  Unlock_2(v103);
LABEL_174:
  v79 = wk;
  if (v79->battlemode != 3)
  {
    v79 = wk;
    if (!v79->BtlEnd_BossFedeOut)
    {
      v79 = wk;
      if (v79->encountno != 58)
      {
        HdBtlEndCam();
      }
    }
  }
  v81 = wk;
  if (v81->endcnt < 10)
  {
    BtlEnd_BossFedeOut = 0;
    goto LABEL_193;
  }
  v81 = wk;
  BtlEnd_BossFedeOut = v81->BtlEnd_BossFedeOut;
LABEL_193:
  if (wk->endcnt >= 10)
  {
    BtlEnd_BossFedeOut |= CHECK_TRIG(4097, 1);
LABEL_195:
    v83 = wk;
    v84 = (v83->endcnt > 239) | BtlEnd_BossFedeOut;
    v85 = (u16)v83->battlemode;
    if (v85 == 1)
      goto LABEL_200;
    goto LABEL_216;
  }
  {
    goto LABEL_195;
  }
  v86 = wk;
  v84 = (v86->endcnt > 239) | BtlEnd_BossFedeOut;
  v85 = (u16)v86->battlemode;
  if (v85 == 1)
    goto LABEL_200;
LABEL_216:
  if (v85 == 3)
    goto LABEL_218;
  goto LABEL_9004;
  if (wk->battlemode == 3)
  {
LABEL_218:
    if (sBtlCheckNextAction(v36) && v36->motionst >= 1)
    {
      v87 = wk->endcnt <= 149;
      goto LABEL_233;
    }
    goto LABEL_225;
  }
LABEL_9004:
  if (!sBtlGetNakama(0) && !sBtlGetNakama(1))
  {
LABEL_200:
    if (!sBtlCheckNextAction(v36))
    {
LABEL_225:
      if ((v84 & 1) != 0)
        goto LABEL_237;
      return 1;
    }
    v87 = v36->motionst <= 0;
    goto LABEL_233;
  }
  v87 = wk->endcnt <= 219;
LABEL_233:
  v96 = !v87;
  if (((v96 | v84) & 1) == 0)
    return 1;
LABEL_237:
  v98 = wk;
  if ((v98->status2 & 1) == 0)
    goto LABEL_244;
  goto LABEL_9005;
  if ((v98->status2 & 1) == 0)
  {
LABEL_244:
    if (sBtlCheckUnit_Exec())
    {
      v100 = wk;
      *(int8x8_t *)&v100->status = vorr_s8(*(int8x8_t *)&v100->status, (int8x8_t)0x1000000000000008LL);
      v100->endcnt = 0;
      sBtlCheckBattleWin();
      sBtlGetAutoSkillPoint();
      sBtlGetChuuseiPoint();
      sBtlSetEndData();
    }
    return 1;
  }
LABEL_9005:
  v98 = wk;
  if (v98->endcnt >= 180)
    goto LABEL_244;
  return 0;
}

// 0x1ec9fd0
void HdBtlEndCam(void) {
  s32 endcnt;
  s32 v3;
  S_CameraMoveDt *CamMovePtn;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v6;
  f32 v7;
  f32 v8;
  s32 devilid;
  f32 v10;
  sdfVector4_t *p_rot;
  s32 v13;
  S_CameraMoveDt *v14;
  SBTLUNIT_WORK *v15;
  SBTLUNIT_WORK *v16;
  f32 v17;
  f32 v18;
  s32 v19;
  f32 v20;
  sdfVector4_t *v22;
  u32 v23;
  S_CameraMoveDt *v24;
  SBTLUNIT_WORK *v25;
  SBTLUNIT_WORK *v26;
  f32 v27;
  f32 v28;
  s32 v29;
  f32 v30;
  long f64 v31;
  long f64 v32;
  SBTLUNIT_WORK *v33;
  SBTLUNIT_WORK *v34;
  f32 v35;
  f32 v36;
  s32 v37;
  f32 v38;
  long f64 v39;
  long f64 v40;
  SBTLUNIT_WORK *v41;
  f32 v42;
  SBTLUNIT_WORK *v43;
  f32 v44;
  f32 v45;
  sdatUnitWork_t *v46;
  sdfVector4_t *v48;
  SBTLUNIT_WORK *v49;
  SBTLUNIT_WORK *v50;
  f32 v51;
  f32 v52;
  s32 v53;
  f32 v54;
  f32 v55;
  SBTLUNIT_WORK *v56;
  SBTLUNIT_WORK *v57;
  f32 v58;
  f32 v59;
  s32 v60;
  f32 v61;
  sdfVector4_t *v63;
  SBTLUNIT_WORK *v64;
  f32 v65;
  f32 v66;
  s32 v67;
  f32 v68;
  sdfVector4_t *v70;
  SBTLUNIT_WORK *v71;
  SBTLUNIT_WORK *v72;
  f32 v73;
  f32 v74;
  s32 v75;
  f32 v76;
  sdfVector4_t *v78;
  sdfVector4_t *v80;
  SBTLUNIT_WORK *v81;
  SBTLUNIT_WORK *v82;
  f32 v83;
  f32 v84;
  s32 v85;
  f32 v86;
  f32 v87;
  sdfVector4_t *p_rotbk;
  SBTLUNIT_WORK *v90;
  f32 v91;
  f32 v92;
  s32 v93;
  f32 v94;
  s32 v95;
  sdfVector4_t *v97;
  SBTLUNIT_WORK *v98;
  f32 v99;
  f32 v100;
  f32 v101;
  sdatUnitWork_t *para;
  sdfVector4_t *v104;
  SBTLUNIT_WORK *v105;
  f32 v106;
  f32 v107;
  s32 v108;
  f32 v109;
  f32 v110;
  sdfVector4_t *v112;
  SBTLUNIT_WORK *v113;
  f32 v114;
  f32 v115;
  sdatUnitWork_t *v116;
  sdfVector4_t *v118;
  sdfVector4_t *v120;
  sdfVector4_t *v122;
  SBTLUNIT_WORK *v123;
  SBTLUNIT_WORK *v124;
  f32 v125;
  f32 v126;
  s32 v127;
  f32 v128;
  sdfVector4_t *v130;
  sdfVector4_t *v132;
  SB_ENCOUNTPAC *EncountPac;
  SB_ENCOUNTPAC *v135;
  SBTLUNIT_WORK *v136;
  SBTLUNIT_WORK *v137;
  SBTLUNIT_WORK *v138;
  SBTLUNIT_WORK *v139;
  f32 ZeroZ;
  s64 ZeroY;

  ZeroY = 0;
  ZeroZ = 0.0;
  sBtlGetZeroPos((f32 *)&ZeroY + 1, &ZeroY, &ZeroZ);
  endcnt = wk->endcnt;
  if (endcnt == 1)
  {
    v3 = sub_1905740(3, 0);
    CamMovePtn = sBtlGetCamMovePtn(v3 + 311);
    sBtlSetMove(CamMovePtn, 1);
    sBtlSetDof2Bokah(1.0, 0.5, 50.0, 20.0, 0.5, 50.0, 20.0);
    sBtlSetMode(1);
    Proc(0);
    if (v3 != 2)
    {
      if (v3 != 1)
      {
        if (v3)
          return;
        Nakama = sBtlGetNakama(0);
        if (Nakama)
        {
          v6 = Nakama;
          v7 = *((f32 *)&ZeroY + 1) + -197.645;
          v8 = *(f32 *)&ZeroY + 0.0;
          devilid = (u16)Nakama->para->devilid;
          v10 = ZeroZ + 151.63;
          Nakama->pos.x = *((f32 *)&ZeroY + 1) + -197.645;
          Nakama->pos.y = v8;
          Nakama->pos.z = v10;
          if (devilid == 22)
            Nakama->pos.x = v7 + -100.0;
          Nakama->mv_rotbk = 0.0;
          FromEuler(0.0, 0.0, 0.0);
          p_rot = &v6->rot;
          *p_rot = vct_A;
          p_rotbk = &v6->rotbk;
          *p_rotbk = vct_A;
        }
        v90 = sBtlGetNakama(1);
        if (!v90)
          return;
        v82 = v90;
        v91 = *((f32 *)&ZeroY + 1) + 197.645;
        v92 = *(f32 *)&ZeroY + 0.0;
        v93 = (u16)v90->para->devilid;
        v94 = ZeroZ + 151.63;
        v90->pos.x = *((f32 *)&ZeroY + 1) + 197.645;
        v90->pos.y = v92;
        v90->pos.z = v94;
        if (v93 == 22)
          v90->pos.x = v91 + 100.0;
        v90->mv_rotbk = 30.0;
        v95 = 1057360530;
        goto LABEL_142;
      }
      v49 = sBtlGetNakama(0);
      if (v49)
      {
        v50 = v49;
        v51 = *((f32 *)&ZeroY + 1) + -197.645;
        v52 = *(f32 *)&ZeroY + 0.0;
        v53 = (u16)v49->para->devilid;
        v54 = ZeroZ + 151.63;
        v49->pos.x = *((f32 *)&ZeroY + 1) + -197.645;
        v49->pos.y = v52;
        v49->pos.z = v54;
        if (v53 == 22)
          v49->pos.x = v51 + -100.0;
        v49->mv_rotbk = 320.0;
        v55 = 5.5850534;
        goto LABEL_76;
      }
      goto LABEL_94;
    }
    v41 = sBtlGetNakama(0);
    if (!v41)
    {
LABEL_116:
      v98 = sBtlGetNakama(1);
      if (!v98)
        return;
      v99 = ZeroZ;
      v82 = v98;
      v100 = *((f32 *)&ZeroY + 1) + 197.645;
      v101 = *(f32 *)&ZeroY + 0.0;
      para = v98->para;
      v98->pos.x = *((f32 *)&ZeroY + 1) + 197.645;
      LODWORD(para) = (u16)para->devilid;
      v98->pos.y = v101;
      v98->pos.z = v99 + 101.630005;
      if ((u32)para == 22)
        v98->pos.x = v100 + 100.0;
      v98->mv_rotbk = 40.0;
      v95 = 1060288706;
      goto LABEL_142;
    }
    v42 = ZeroZ;
    v43 = v41;
    v44 = *((f32 *)&ZeroY + 1) + -197.645;
    v45 = *(f32 *)&ZeroY + 0.0;
    v46 = v41->para;
    v41->pos.x = *((f32 *)&ZeroY + 1) + -197.645;
    LODWORD(v46) = (u16)v46->devilid;
    v41->pos.y = v45;
    v41->pos.z = v42 + 151.63;
    if ((u32)v46 == 22)
      v41->pos.x = v44 + -100.0;
    v41->mv_rotbk = 0.0;
    FromEuler(0.0, 0.0, 0.0);
    v48 = &v43->rot;
    *v48 = vct_A;
    v97 = &v43->rotbk;
    *v97 = vct_A;
    goto LABEL_116;
  }
  if (endcnt == 30)
  {
    v13 = sub_1905740(3, 0);
    v14 = sBtlGetCamMovePtn(v13 + 314);
    sBtlSetMove(v14, 1);
    sBtlSetDof2Bokah(1.0, 1.4, 70.0, 12.0, 1.4, 70.0, 12.0);
    sBtlSetMode(1);
    Proc(0);
    if (v13 != 2)
    {
      if (v13 == 1)
      {
        v64 = sBtlGetNakama(0);
        if (v64)
        {
          v50 = v64;
          v65 = *((f32 *)&ZeroY + 1) + -197.645;
          v66 = *(f32 *)&ZeroY + 0.0;
          v67 = (u16)v64->para->devilid;
          v68 = ZeroZ + 251.63;
          v64->pos.x = *((f32 *)&ZeroY + 1) + -197.645;
          v64->pos.y = v66;
          v64->pos.z = v68;
          if (v67 == 22)
            v64->pos.x = v65 + -100.0;
          v64->mv_rotbk = 330.0;
          v55 = 5.7595863;
LABEL_76:
          FromEuler(0.0, v55, 0.0);
          v70 = &v50->rot;
          *v70 = vct_A;
          v80 = &v50->rotbk;
          *v80 = vct_A;
          goto LABEL_94;
        }
LABEL_94:
        v81 = sBtlGetNakama(1);
        if (!v81)
          return;
        v82 = v81;
        v83 = *((f32 *)&ZeroY + 1) + 197.645;
        v84 = *(f32 *)&ZeroY + 0.0;
        v85 = (u16)v81->para->devilid;
        v86 = ZeroZ + 151.63;
        v81->pos.x = *((f32 *)&ZeroY + 1) + 197.645;
        v81->pos.y = v84;
        v81->pos.z = v86;
        if (v85 == 22)
          v81->pos.x = v83 + 100.0;
        v81->mv_rotbk = 0.0;
        v87 = 0.0;
LABEL_143:
        FromEuler(0.0, v87, 0.0);
        v118 = &v82->rot;
        *v118 = vct_A;
        v120 = &v82->rotbk;
        *v120 = vct_A;
        return;
      }
      if (v13)
        return;
      v15 = sBtlGetNakama(0);
      if (v15)
      {
        v16 = v15;
        v17 = *((f32 *)&ZeroY + 1) + -147.645;
        v18 = *(f32 *)&ZeroY + 0.0;
        v19 = (u16)v15->para->devilid;
        v20 = ZeroZ + -151.63;
        v15->pos.x = *((f32 *)&ZeroY + 1) + -147.645;
        v15->pos.y = v18;
        v15->pos.z = v20;
        if (v19 == 22)
          v15->pos.x = v17 + -100.0;
        v15->mv_rotbk = 240.0;
        FromEuler(0.0, 4.1887903, 0.0);
        v22 = &v16->rot;
        *v22 = vct_A;
        v104 = &v16->rotbk;
        *v104 = vct_A;
      }
      v105 = sBtlGetNakama(1);
      if (!v105)
        return;
      v82 = v105;
      v106 = *((f32 *)&ZeroY + 1) + 197.645;
      v107 = *(f32 *)&ZeroY + 0.0;
      v108 = (u16)v105->para->devilid;
      v109 = ZeroZ + -151.63;
      v105->pos.x = *((f32 *)&ZeroY + 1) + 197.645;
      v105->pos.y = v107;
      v105->pos.z = v109;
      if (v108 != 22)
        goto LABEL_141;
      v110 = 100.0;
LABEL_140:
      v82->pos.x = v106 + v110;
LABEL_141:
      v82->mv_rotbk = 180.0;
      v95 = 1078530011;
LABEL_142:
      v87 = *(f32 *)&v95;
      goto LABEL_143;
    }
    v56 = sBtlGetNakama(0);
    if (!v56)
    {
LABEL_137:
      v113 = sBtlGetNakama(1);
      if (!v113)
        return;
      v114 = ZeroZ;
      v82 = v113;
      v106 = *((f32 *)&ZeroY + 1) + -197.645;
      v115 = *(f32 *)&ZeroY + 0.0;
      v116 = v113->para;
      v113->pos.x = *((f32 *)&ZeroY + 1) + -197.645;
      LODWORD(v116) = (u16)v116->devilid;
      v113->pos.y = v115;
      v113->pos.z = v114 + -151.63;
      if ((u32)v116 != 22)
        goto LABEL_141;
      v110 = -100.0;
      goto LABEL_140;
    }
    v57 = v56;
    v58 = *((f32 *)&ZeroY + 1) + 197.645;
    v59 = *(f32 *)&ZeroY + 0.0;
    v60 = (u16)v56->para->devilid;
    v61 = ZeroZ + -151.63;
    v56->pos.x = *((f32 *)&ZeroY + 1) + 197.645;
    v56->pos.y = v59;
    v56->pos.z = v61;
    if (v60 == 22)
      v56->pos.x = v58 + 100.0;
    v56->mv_rotbk = 160.0;
    FromEuler(0.0, 2.7925267, 0.0);
    v63 = &v57->rot;
    *v63 = vct_A;
    v112 = &v57->rotbk;
    *v112 = vct_A;
    goto LABEL_137;
  }
  endcnt = wk->endcnt;
  if (endcnt == 90)
  {
    v23 = sub_1905740(3, 0);
    v24 = sBtlGetCamMovePtn(v23 + 317);
    sBtlSetMove(v24, 1);
    sBtlSetDof2Bokah(1.0, 2.7, 85.0, 12.0, 2.7, 85.0, 12.0);
    sBtlSetMode(1);
    Proc(0);
    if (v23 >= 2)
    {
      if (v23 == 2)
      {
        v25 = sBtlGetNakama(0);
        if (v25)
        {
          v26 = v25;
          v27 = *((f32 *)&ZeroY + 1) + 197.645;
          v28 = *(f32 *)&ZeroY + 0.0;
          v29 = (u16)v25->para->devilid;
          v30 = ZeroZ + -151.63;
          v25->pos.x = *((f32 *)&ZeroY + 1) + 197.645;
          v25->pos.y = v28;
          v25->pos.z = v30;
          if (v29 == 22)
            v25->pos.x = v27 + 100.0;
          v25->mv_rotbk = 180.0;
          FromEuler(0.0, 3.1415927, 0.0);
          *(__n128 *)&v32 = sub_1B335A0(&v26->rot, 0, v31);
          sub_1B335A0(&v26->rotbk, 0, v32);
        }
        v33 = sBtlGetNakama(1);
        if (v33)
        {
          v34 = v33;
          v35 = *((f32 *)&ZeroY + 1) + -197.645;
          v36 = *(f32 *)&ZeroY + 0.0;
          v37 = (u16)v33->para->devilid;
          v38 = ZeroZ + -151.63;
          v33->pos.x = *((f32 *)&ZeroY + 1) + -197.645;
          v33->pos.y = v36;
          v33->pos.z = v38;
          if (v37 == 22)
            v33->pos.x = v35 + -100.0;
          v33->mv_rotbk = 180.0;
          FromEuler(0.0, 3.1415927, 0.0);
          *(__n128 *)&v40 = sub_1B335A0(&v34->rot, 0, v39);
          sub_1B335A0(&v34->rotbk, 0, v40);
        }
      }
      goto LABEL_176;
    }
    v71 = sBtlGetNakama(0);
    if (!v71)
    {
LABEL_162:
      v123 = sBtlGetNakama(1);
      if (!v123)
      {
LABEL_176:
        EncountPac = sBtlGetEncountPac(-1);
        v135 = EncountPac[wk->encountno];
        v136 = sBtlGetNakama(0);
        if (v136 && (v135->flag & 0x2000000) == 0)
        {
          v137 = v136;
          v136->next_motion_not_hokan = 1;
          sBtlSetMotion(v137, 4, 0, 0, 0);
        }
        v138 = sBtlGetNakama(1);
        if (v138 && (v135->flag & 0x2000000) == 0)
        {
          v139 = v138;
          v138->next_motion_not_hokan = 1;
          sBtlSetMotion(v139, 4, 0, 0, 0);
        }
        return;
      }
      v124 = v123;
      v125 = *((f32 *)&ZeroY + 1) + 197.645;
      v126 = *(f32 *)&ZeroY + 0.0;
      v127 = (u16)v123->para->devilid;
      v128 = ZeroZ + 151.63;
      v123->pos.x = *((f32 *)&ZeroY + 1) + 197.645;
      v123->pos.y = v126;
      v123->pos.z = v128;
      if (v127 == 22)
        v123->pos.x = v125 + 100.0;
      v123->mv_rotbk = 0.0;
      FromEuler(0.0, 0.0, 0.0);
      v130 = &v124->rot;
      *v130 = vct_A;
      v132 = &v124->rotbk;
      *v132 = vct_A;
      goto LABEL_176;
    }
    v72 = v71;
    v73 = *((f32 *)&ZeroY + 1) + -197.645;
    v74 = *(f32 *)&ZeroY + 0.0;
    v75 = (u16)v71->para->devilid;
    v76 = ZeroZ + 151.63;
    v71->pos.x = *((f32 *)&ZeroY + 1) + -197.645;
    v71->pos.y = v74;
    v71->pos.z = v76;
    if (v75 == 22)
      v71->pos.x = v73 + -100.0;
    v71->mv_rotbk = 0.0;
    FromEuler(0.0, 0.0, 0.0);
    v78 = &v72->rot;
    *v78 = vct_A;
    v122 = &v72->rotbk;
    *v122 = vct_A;
    goto LABEL_162;
  }
}

// 0x1ec8230
void ChkInochigoi(void) {
  ;
}

// 0x1ecb230
bool ChkSensei(void) {
  return 0;
}

// 0x1ecb240
bool ChkSenseiDamage(void) {
  return 0;
}

// 0x1ecb250
bool ChkMyth(void) {
  return 0;
}

// 0x1ecb260
bool Start(SBTLMAIN_DATA *data, s32 flg) {
  u32 *p_FrameCount;
  u32 FrameCount_local;
  Il2CppObject *v11;
  u32 v12;
  s32 mode;
  s32 encountno;
  dds3ProcessFunc_t v20;
  shutdownfuncDelegate v21;
  dds3ProcessID_t *v22;
  dds3ProcessID_t *p_MProc_ID;
  dds3ProcessFunc_t v25;
  dds3ProcessFunc_t v26;
  dds3ProcessID_t *started;
  dds3ProcessID_t *target;
  dds3ProcessID_t *parent;

  parent = 0;
  started = 0;
  target = 0;
  goto LABEL_3;
  if (v12)
  {
LABEL_3:
    goto LABEL_4;
  }
LABEL_4:
  p_FrameCount = &FrameCount;
  FrameCount_local = *p_FrameCount;
  frame_cnt = FrameCount_local;
  v11 = MemberwiseClone(data, 0);
  if (!v11)
    goto LABEL_17;
  goto LABEL_15;
  if (!v11)
LABEL_15:
LABEL_17:
  main_data = (SBTLMAIN_DATA *)v11;
  main_data->flg = flg;
  if (flg)
  {
    goto LABEL_19;
  }
  sBtlLoadOnMemMsg();
  sBtlInitLoadAttackHitData_pData();
  rstSetFlag(0x20000);
LABEL_19:
  sBtlForceDelete_EffectWork(2);
  sBtlForceDelete_AttackHitData();
  sBtlInitEffectWork();
  sBtlInitLoadAttackHitData_pData();
  mode = data->mode;
  encountno = data->encountno;
  Init(mode, encountno);
  v20 = Allocate(dds3ProcessFunc_t);
  _ctor(v20, 0, Method_Project_sBtl_Proc__, 0);
  v21 = Allocate(shutdownfuncDelegate);
  _ctor(v21, 0, Method_Project_sBtl_Shutdown__, 0);
  parent = dds3StartProcess("sbattle", 1016, 0, 0, v20, v21, 0);
  v22 = parent;
  p_MProc_ID = &wk->MProc_ID;
  p_MProc_ID = parent;
  v25 = Allocate(dds3ProcessFunc_t);
  _ctor(v25, 0, Method_Project_sBtl_DrawProc__, 0);
  target = dds3StartProcess("sbattle_draw", 1016, 0, 0, v25, 0, 0);
  dds3LinkProcess(parent, target);
  v26 = Allocate(dds3ProcessFunc_t);
  _ctor(v26, 0, Method_Project_sBtl_DrawProc2__, 0);
  started = dds3StartProcess("sbattle_draw2", 11021, 0, 0, v26, 0, 0);
  dds3LinkProcess(parent, started);
  Init();
  Init(flg, 0);
  sBtlCreateAIScript();
  sBtlInitDropWork();
  Init();
  RestartBattle();
  sBtlStopVibe();
  return 1;
}

// 0x1ec5f20
bool Exit(s32 type) {
  SB_ENCOUNTPAC *EncountPac;
  SB_ENCOUNTPAC *v8;
  SBATTLE_WORK *v9;
  s32 v10;
  sdatUnitWork_t *para;
  sdatUnitWork_t *StockUnitData;
  sdatUnitWork_t *v17;
  sdatUnitWork_t *v19;
  sdatUnitWork_t *v20;
  s32 i;
  sdatUnitWork_t *v22;
  sdatUnitWork_t *v23;
  SBATTLE_WORK *v25;
  SBTLUNIT_LISTWORK *targetList;
  SBTLUNIT_LISTWORK *p_targetList;
  SBTLUNIT_LISTWORK *tgtList;
  SBTLUNIT_LISTWORK *p_tgtList;
  SBTLUNIT_LISTWORK *enemyList;
  SBTLUNIT_LISTWORK *p_enemyList;
  SBTLUNIT_LISTWORK *friend_List;
  SBTLUNIT_LISTWORK *p_friend_List;
  SBTLUNIT_LISTWORK *other_List;
  SBTLUNIT_LISTWORK *p_other_List;
  SBTLUNIT_LISTWORK *other_List2;
  SBTLUNIT_LISTWORK *p_other_List2;
  SBTLEFF_LISTWORK *effList;
  SBTLEFF_LISTWORK *v46;
  SBATTLE_WORK *v49;
  SBTLDMG_LISTWORK *p_dmgList;
  SBTLDMG_LISTWORK *v51;
  SBTLDMG_HITLISTWORK *hitList;
  SBTLDMG_HITLISTWORK *p_hitList;
  SBTLDVLTK_LISTWORK *dvltkList;
  SBTLDVLTK_LISTWORK *p_dvltkList;
  SBTLEXP_LISTWORK *expList;
  SBTLEXP_LISTWORK *p_expList;
  SBTLSTP_LISTWORK *stpList;
  SBTLSTP_LISTWORK *p_stpList;
  SBTLITEM_LISTWORK *itemList;
  SBTLITEM_LISTWORK *p_itemList;
  SBTLITEM_LISTWORK *bulletList;
  SBTLITEM_LISTWORK *p_bulletList;
  SBATTLE_WORK *v64;
  SBTLEFF_DELLISTWORK *effdelList;
  SBTLEFF_DELLISTWORK *p_effdelList;
  SBTLEFF_LISTWORK *p_effList;
  s32 encountno;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v77;
  sdatUnitWork_t *v79;
  s32 devilid;
  u32 uniq_code;
  s16 StockDevilIndex;
  _BOOL4 v85;
  _BOOL4 v86;
  _BOOL4 v87;
  _BOOL4 v88;
  SBATTLE_WORK *v90;
  u32 status5;
  SBTLUNIT_WORK *v95;
  s64 v97;
  SBTLUNIT_WORK *v98;
  sdatUnitWork_t *v100;
  s32 v101;
  u32 v102;
  s16 v103;
  long f64 v105;
  f32 v107;
  sdatPlayerUnitWork_t *player;
  s64 v114;
  s64 v115;
  long f64 v117;
  long f64 v120;
  f32 v122;
  long f64 v123;
  f32 v124;
  s32 v126;
  u32 v128;
  SBATTLE_WORK *v129;
  dds3ProcessID_t *p_MProc_ID;
  SBATTLE_WORK *v138;
  u32 status;
  u32 v141;
  SBATTLE_WORK *v145;
  SBTLUNIT_WORK *scrunit;
  SBTLUNIT_WORK *p_scrunit;
  SBTLUNIT_WORK *scrEventUnit;
  SBTLUNIT_WORK *p_scrEventUnit;
  s64 v150;
  s64 j;
  u64 *v152;
  SBTLUNIT_WORK *scrUnitList;
  SBTLUNIT_WORK *v154;
  SBTLUNIT_WORK *v156;
  SBTLUNIT_WORK *pLoadingUnit;
  SBTLUNIT_WORK *p_pLoadingUnit;
  SB_ENCOUNTPAC *v164;

  gShaderUVScroll = 1;
  if (!wk)
    return 1;
  if (!dds3SearchProcessName("sbattle"))
    return 1;
  EncountPac = sBtlGetEncountPac(-1);
  v8 = EncountPac[wk->encountno];
  if (exit2_flag)
  {
    goto LABEL_24;
  }
  if (!wk->UnitMng)
    goto LABEL_342;
  if (wk->battlemode == 3)
    goto LABEL_342;
  para = sBtlGetPlayerData()->para;
  sBtlResetBadStatus_GB(para, 32);
  if ((wk->summonindex[0] & 0x80000000) == 0)
  {
    StockUnitData = sBtlGetStockUnitData((u16)wk->summonindex[0]);
    if (StockUnitData)
    {
      v17 = StockUnitData;
      sBtlResetBadStatus_GB(v17, 32);
    }
  }
  if ((wk->summonindex[1] & 0x80000000) == 0)
  {
    v19 = sBtlGetStockUnitData((u16)wk->summonindex[1]);
    if (v19)
    {
      v20 = v19;
      sBtlResetBadStatus_GB(v20, 32);
    }
  }
  for (i = 0; i != 32; ++i)
  {
    v22 = sBtlGetStockUnitData(i);
    if (v22)
    {
      v23 = v22;
      sBtlResetBadStatus_GB(v23, 32);
    }
  }
  Nakama = sBtlGetNakama(0);
  if (Nakama)
  {
    v77 = Nakama;
    v79 = v77->para;
    if (!escape_checkflg || v79->now->hp)
    {
      devilid = v79->devilid;
      uniq_code = v77->uniq_code;
      StockDevilIndex = datGetStockDevilIndex(devilid, uniq_code);
      goto LABEL_316;
    }
  }
  else
  {
    Exit2Set(0);
  }
  StockDevilIndex = -1;
LABEL_316:
  GBWK->player->stack_p[0] = StockDevilIndex;
  v95 = sBtlGetNakama(1);
  if (v95)
  {
    v98 = v95;
    v100 = v98->para;
    if (!escape_checkflg || v100->now->hp)
    {
      v101 = v100->devilid;
      v102 = v98->uniq_code;
      v103 = datGetStockDevilIndex(v101, v102);
      goto LABEL_335;
    }
  }
  else
  {
    Exit2Set(1);
  }
  v103 = -1;
LABEL_335:
  GBWK->player->stack_p[1] = v103;
  if (wk->encountno == 513)
  {
    sub_1A21FE0(9986, 0, v97);
    goto LABEL_352;
  }
  if (wk->encountno != 514)
    goto LABEL_339;
LABEL_353:
  sub_1A21FE0(9989, 0, v97);
  sub_1A21FE0(9990, 0, v114);
  sub_1A21FE0(9991, 0, v115);
LABEL_340:
  if (wk->encountno != 517)
    goto LABEL_342;
  goto LABEL_341;
LABEL_352:
  if (wk->encountno == 514)
    goto LABEL_353;
LABEL_339:
  goto LABEL_340;
  if (wk->encountno == 517)
LABEL_341:
    sub_1A21FE0(10003, 0, v97);
LABEL_342:
  player = GBWK->player;
  player->sprit_waza = wk->sprit_waza;
  exit2_flag = 1;
LABEL_24:
  v9 = wk;
  v10 = v9->status | 8;
  v9->status = v10;
  if ((v9->status2 & 0x80000000) != 0)
    goto LABEL_75;
  if ((v10 & 0x20) == 0)
    goto LABEL_27;
  goto LABEL_9006;
  if ((wk->status & 0x20) == 0)
  {
LABEL_27:
    sBtlClear();
    if (ProcessCheck())
    {
      if (!rstCheckFlag(64))
        return 1;
      wk->status2 |= 0x80000000;
LABEL_39:
      sBtlInitSceneRndEnc_IDFlag();
      goto LABEL_75;
    }
    encountno = wk->encountno;
    gGlobalEncNo = encountno;
    if (wk->battlemode == 3)
    {
      rstSetFlag(0x80000);
      sBtlTutorialEndNakamaChack();
      goto LABEL_243;
    }
    else
    {
    }
    sBtlTutorialEndNakamaChack();
    if ((wk->status5 & 0x10) != 0)
    {
LABEL_230:
      rstSetFlag(1);
      goto LABEL_247;
    }
LABEL_244:
    sBtlCheckDrop();
LABEL_247:
    sBtlStopSEAll(0);
    p2sdSndStop(2);
    if (type)
    {
      dds3AdminiCallSequence(12, 0, 0);
      rstResultStart();
      sndBgmFadeOut();
      goto LABEL_39;
    }
    if ((v8->flag & 0x1000000) == 0)
    {
LABEL_367:
      if ((wk->status5 & 0x10) == 0)
        goto LABEL_379;
      rstSetFlag(0x10000);
      sub_1B34770(0, v120);
      if (v122 != 1.0)
        goto LABEL_376;
      goto LABEL_379;
      if (v124 != 1.0)
      {
LABEL_376:
        dds3FadeOut(0, 0, 0, 0xAu);
      }
LABEL_379:
      p2sdUnLoadAllSMGFile();
      ProcessStart(0);
      rstResultStart();
      return 1;
    }
    rstSetFlag(0x10000);
    sub_1B34770(0, v105);
    if (v107 == 1.0)
      goto LABEL_367;
    dds3FadeOut(0, 0, 0, 0xAu);
    goto LABEL_367;
LABEL_243:
    if ((wk->status5 & 0x10) != 0)
      goto LABEL_230;
    goto LABEL_244;
  }
LABEL_9006:
  {
    if (!rstCheckFlag(0x40000))
    {
      ClearFlgOnGameOver();
      rstSetFlag(0x40000);
      sBtlStopSEAll(0);
      return 1;
    }
  }
LABEL_75:
  v25 = wk;
  v25->status2 |= 4u;
  sBtlStopVibe();
  sBtlDrawON();
  if (!sBtlCheckUnit_Exec())
    return 0;
  targetList = wk->targetList;
  if (targetList)
  {
    targetList = wk->targetList;
    sBtlDeleteUnitList(targetList, 1);
    p_targetList = &wk->targetList;
    p_targetList = 0;
  }
  tgtList = wk->tgtList;
  if (tgtList)
  {
    tgtList = wk->tgtList;
    sBtlDeleteUnitList(tgtList, 1);
    p_tgtList = &wk->tgtList;
    p_tgtList = 0;
  }
  enemyList = wk->enemyList;
  if (enemyList)
  {
    enemyList = wk->enemyList;
    sBtlDeleteUnitList(enemyList, 1);
    p_enemyList = &wk->enemyList;
    p_enemyList = 0;
  }
  friend_List = wk->friend_List;
  if (friend_List)
  {
    friend_List = wk->friend_List;
    sBtlDeleteUnitList(friend_List, 1);
    p_friend_List = &wk->friend_List;
    p_friend_List = 0;
  }
  other_List = wk->other_List;
  if (other_List)
  {
    other_List = wk->other_List;
    sBtlDeleteUnitList(other_List, 1);
    p_other_List = &wk->other_List;
    p_other_List = 0;
  }
  other_List2 = wk->other_List2;
  if (other_List2)
  {
    other_List2 = wk->other_List2;
    sBtlDeleteUnitList(other_List2, 1);
    p_other_List2 = &wk->other_List2;
    p_other_List2 = 0;
  }
  if (sbtleffbo_acter)
  {
    ClassMemAlloc(sbtleffbo_acter);
    sbtleffbo_acter = 0;
  }
  if (sbtleffbo_target)
  {
    ClassMemAlloc(sbtleffbo_target);
    sbtleffbo_target = 0;
  }
  sBtlDestroyTarget();
  if (!sBtlCheckLoadEnd_EffectWork())
    return 0;
  effList = wk->effList;
  if (effList)
  {
    v46 = wk->effList;
    if (sBtlDeleteEffList(v46))
    {
      v49 = wk;
      if (v49->dmgList)
      {
        v49 = wk;
        p_dmgList = &v49->dmgList;
        sBtlDeleteAnimList(p_dmgList);
        v51 = &wk->dmgList;
        v51 = 0;
      }
      hitList = wk->hitList;
      if (hitList)
      {
        hitList = wk->hitList;
        sBtlDeleteHitList(hitList);
        p_hitList = &wk->hitList;
        p_hitList = 0;
      }
      dvltkList = wk->dvltkList;
      if (dvltkList)
      {
        dvltkList = wk->dvltkList;
        sBtlDeleteDvltkList(dvltkList);
        p_dvltkList = &wk->dvltkList;
        p_dvltkList = 0;
      }
      expList = wk->expList;
      if (expList)
      {
        expList = wk->expList;
        sBtlDeleteEXPList(expList);
        p_expList = &wk->expList;
        p_expList = 0;
      }
      stpList = wk->stpList;
      if (stpList)
      {
        stpList = wk->stpList;
        sBtlDeleteSTPList(stpList);
        p_stpList = &wk->stpList;
        p_stpList = 0;
      }
      itemList = wk->itemList;
      if (itemList)
      {
        itemList = wk->itemList;
        sBtlDeleteItemList(itemList);
        p_itemList = &wk->itemList;
        p_itemList = 0;
      }
      bulletList = wk->bulletList;
      if (bulletList)
      {
        bulletList = wk->bulletList;
        sBtlDeleteItemList(bulletList);
        p_bulletList = &wk->bulletList;
        p_bulletList = 0;
      }
      v64 = wk;
      if (v64->sysmsgList)
      {
        v64 = wk;
        v64->sysmsgList = 0;
      }
      effdelList = wk->effdelList;
      if (effdelList)
      {
        effdelList = wk->effdelList;
        sBtlDeleteDelList(effdelList);
        p_effdelList = &wk->effdelList;
        p_effdelList = 0;
      }
      sBtlProcessEnd();
      Delete(0);
      p_effList = &wk->effList;
      p_effList = 0;
      return 0;
    }
  }
  v164 = v8;
  v85 = effList == 0;
  v86 = ProcessCheck();
  v87 = sBtlDeleteOnData(0);
  v88 = sBtlForceDelete_EffectWork(1);
  sBtlForceDelete_EffectWork(2);
  sBtlForceDelete_AttackHitData();
  sBtlInitEffectWork();
  sBtlInitLoadAttackHitData_pData();
  sbtlEnd();
  sBtlBattleEnd();
  v90 = wk;
  if ((v90->status & 0x800000) == 0)
  {
    v90 = wk;
    if (v90->effList)
      goto LABEL_294;
    if (!Exit())
      goto LABEL_294;
    if (sBtlFree())
    {
      wk->status |= 0x800000u;
      return 0;
    }
    else
    {
LABEL_294:
      OnEndBattle();
      return 0;
    }
  }
  OnEndBattle();
  if (!v88 || !v87 || !v85 || v86 || !sBtlDeleteMainPanel())
    return 0;
  status5 = wk->status5;
  if ((status5 & 1) == 0)
  {
    sBtlFreeBgScene();
    return 0;
  }
  status5 = wk->status5;
  if ((status5 & 4) != 0)
  {
    sBtlFreeUISceneEnd();
    if ((wk->status & 0x80) == 0)
    {
      goto LABEL_396;
    }
    fclDestroyMessage();
    fclEndMessage();
LABEL_396:
    v126 = wk->encountno;
    dbg_encount_bk = v126;
    sBtlPacData_Free();
    scrAllReleaseScript();
    v129 = wk;
    if ((v129->status & 0x20) == 0)
    {
      if (v128)
      {
        goto LABEL_403;
LABEL_404:
        sBtlSMGClearLock();
        if (!!dds3SearchProcessPriority(1016))
        {
          p_MProc_ID = &wk->MProc_ID;
          dds3KillProcess(p_MProc_ID, 1);
        }
        v138 = wk;
        status = v138->status;
        v138->enemy_num = 0;
        v138->enemy_zenmetu = 0;
        v138->endcnt = 0;
        v138->status = status & 0xFB7FFFEC;
        if ((v164->flag & 0x1000000) != 0)
        {
          goto LABEL_440;
        }
        else
        {
          v138 = wk;
          if ((v138->status5 & 0x10) == 0)
          {
            if (!v141)
            dds3FadeIn2(1u);
            goto LABEL_442;
          }
          if (v141)
          {
LABEL_440:
            if (!dds3FadeCheck())
            {
              dds3FadeOut(0, 0, 0, 5u);
              dds3UnloadUnusedAssets(1);
              goto LABEL_443;
            }
LABEL_442:
            dds3UnloadUnusedAssets(1);
LABEL_443:
            v145 = wk;
            v145->status5 |= 0x80u;
            v145 = wk;
            scrunit = v145->scrunit;
            if (scrunit)
            {
              scrunit = wk->scrunit;
              ClassMemAlloc(scrunit);
              p_scrunit = &wk->scrunit;
              p_scrunit = 0;
            }
            scrEventUnit = wk->scrEventUnit;
            if (scrEventUnit)
            {
              scrEventUnit = wk->scrEventUnit;
              ClassMemAlloc(scrEventUnit);
              p_scrEventUnit = &wk->scrEventUnit;
              p_scrEventUnit = 0;
            }
            if (wk->scrUnitList)
            {
              v150 = 0;
              for (j = 32; ; j += 8)
              {
                scrUnitList = wk->scrUnitList;
                if (v150 >= SLODWORD(scrUnitList->max_length))
                  break;
                scrUnitList = wk->scrUnitList;
                v154 = *(SBTLUNIT_WORK *)((char *)&scrUnitList->obj.klass + j);
                if (v154)
                {
                  v154 = *(SBTLUNIT_WORK *)((char *)&wk->scrUnitList->obj.klass + j);
                  ClassMemAlloc(v154);
                  v152 = ((char *)&wk->scrUnitList->obj.klass + j);
                  *v152 = 0;
                }
                ++v150;
              }
            }
            if (sbtleffbo_acter)
            {
              ClassMemAlloc(sbtleffbo_acter);
              sbtleffbo_acter = 0;
            }
            v156 = sbtleffbo_target;
            if (v156)
            {
              ClassMemAlloc(v156);
              sbtleffbo_target = 0;
            }
            if (bs_akama2_wk)
            {
              ClassMemAlloc(bs_akama2_wk);
              bs_akama2_wk = 0;
            }
            pLoadingUnit = wk->pLoadingUnit;
            if (pLoadingUnit)
            {
              pLoadingUnit = wk->pLoadingUnit;
              ClassMemAlloc(pLoadingUnit);
              p_pLoadingUnit = &wk->pLoadingUnit;
              p_pLoadingUnit = 0;
            }
            sBtlClearStaticPar();
            return 1;
          }
        }
        goto LABEL_440;
      }
LABEL_403:
      RestartBattle();
      goto LABEL_404;
    }
    if (v128)
    {
      if (v129->battlemode == 3)
        goto LABEL_409;
    }
    else
    {
      if (wk->battlemode == 3)
      {
LABEL_409:
        rstSetFlag(0x80000);
        sBtlInitSceneRndEnc_IDFlag();
        goto LABEL_419;
      }
    }
LABEL_419:
    ProcessStart(0);
    goto LABEL_403;
  }
  sBtlFreeUIScene();
  return 0;
}

// 0x1ec5b70
void MokutekiOFF(void) {
  if (!lmapSetBattleDestFlagCheck(9))
  {
LABEL_9:
    goto LABEL_10;
  }
  if (lmapSetBattleDestFlagCheck(10))
    goto LABEL_9;
  lmapSetBattleDestFlag(10);
LABEL_10:
  if (!lmapSetBattleDestFlagCheck(11))
  {
LABEL_19:
    goto LABEL_20;
  }
  if (lmapSetBattleDestFlagCheck(12))
    goto LABEL_19;
  lmapSetBattleDestFlag(12);
LABEL_20:
  if (!lmapSetBattleDestFlagCheck(13))
  {
LABEL_29:
    goto LABEL_30;
  }
  if (lmapSetBattleDestFlagCheck(14))
    goto LABEL_29;
  lmapSetBattleDestFlag(14);
LABEL_30:
  if (!lmapSetBattleDestFlagCheck(19))
  {
    if (!lmapSetBattleDestFlagCheck(15))
      goto LABEL_43;
  }
  if (!lmapSetBattleDestFlagCheck(16))
    goto LABEL_47;
LABEL_43:
  goto LABEL_44;
LABEL_47:
  lmapSetBattleDestFlag(16);
LABEL_44:
  if (!lmapSetBattleDestFlagCheck(17))
  {
LABEL_53:
    goto LABEL_54;
  }
  if (lmapSetBattleDestFlagCheck(18))
    goto LABEL_53;
  lmapSetBattleDestFlag(18);
LABEL_54:
  tipsReDestEnd();
  lmapSetBattleDestRelease();
}

// 0x1ecbd40
void ClearFlgOnGameOver(void) {
  _BOOL4 v3;
  s32 v5;
  s32 *v6;
  s32 *EventBit;
  s32 v10;
  s32 *v11;
  _BOOL4 v18;
  s32 *v19;

  if (wk->encountno == 512)
  {
    lmapClrBattleDestFlag(9);
    lmapClrBattleDestFlag(10);
LABEL_7:
    if (wk->encountno != 513)
      goto LABEL_8;
    goto LABEL_25;
  }
  {
    goto LABEL_7;
  }
  if (wk->encountno != 513)
  {
LABEL_8:
    goto LABEL_9;
  }
LABEL_25:
  lmapClrBattleDestFlag(11);
  lmapClrBattleDestFlag(12);
LABEL_9:
  if (wk->encountno != 514)
  {
    goto LABEL_11;
  }
  v5 = 1;
  EventBit = GBWK->EventBit;
  EventBit[21] &= ~0x200u;
  if (v5)
  {
LABEL_45:
    v10 = 1;
    goto LABEL_48;
  }
  else
  {
    goto LABEL_45;
  }
  v10 = (u8)byte_5755E7B;
LABEL_48:
  v11 = GBWK->EventBit;
  v11[21] &= ~0x10000u;
  if (v10)
  {
    goto LABEL_50;
  }
  else
  {
    goto LABEL_50;
  }
LABEL_50:
  GBWK->EventBit[21] &= ~0x20000u;
  lmapClrBattleDestFlag(1);
  lmapClrBattleDestFlag(2);
  lmapClrBattleDestFlag(13);
  lmapClrBattleDestFlag(14);
LABEL_11:
  if (wk->encountno != 515)
  {
    goto LABEL_13;
  }
  lmapClrBattleDestFlag(15);
  lmapClrBattleDestFlag(19);
  lmapClrBattleDestFlag(16);
LABEL_13:
  if (wk->encountno != 517)
  {
    goto LABEL_15;
  }
  GBWK->EventBit[312] &= ~0x40000u;
  lmapClrBattleDestFlag(17);
  lmapClrBattleDestFlag(18);
LABEL_15:
  if (wk->encountno != 23)
  {
    goto LABEL_17;
  }
  v18 = 0;
  v19 = GBWK->EventBit;
  v19[21] &= ~0x1000u;
  GBWK->EventBit[21] &= ~0x2000u;
  lmapClrBattleDestFlag(3);
  lmapClrBattleDestFlag(4);
LABEL_17:
  if (wk->encountno != 22)
    return;
  v3 = 0;
  v6 = GBWK->EventBit;
  v6[21] &= ~0x4000u;
  GBWK->EventBit[21] &= ~0x8000u;
  lmapClrBattleDestFlag(5);
  lmapClrBattleDestFlag(6);
}

// 0x1ecbb20
static void Exit2Set(s32 i) {
  s32 encountno;
  s16 *v8;
  s64 v9;
  sdatPlayerUnitWork_t *player;
  s64 v11;
  sdatUnitWork_t *stock_id;
  sdatUnitWork_t *v13;
  s32 badstatus;

  encountno = wk->encountno;
  if (encountno)
  {
    if (encountno != 31)
      return;
  }
  v8 = stack_p_backup;
  v9 = i;
  player = GBWK->player;
  stack_p_backup[v9] = player->stack_p[v9];
  if (v8[v9] < 0)
    return;
  v11 = i;
  stock_id = player->stock_id;
  v13 = stock_id[stack_p_backup[v11]];
  if (cmpGetBstNo(v13->badstatus) == 17)
  {
    badstatus = v13->badstatus;
    v13->badst_cnt = 0;
    v13->badstatus = badstatus & 0xFFFDFFFF;
    v13->now->hp = v13->now->maxhp;
  }
}

// 0x1ecc350
void Exit2(void) {
  s16 *stack_p;
  s16 *v4;

  if (exit2_flag != 1)
    return;
  if ((stack_p_backup[0] & 0x80000000) == 0)
  {
    stack_p = GBWK->player->stack_p;
    stack_p[0] = stack_p_backup[0];
    goto LABEL_13;
  }
LABEL_13:
  if (stack_p_backup[1] >= 0)
  {
    v4 = GBWK->player->stack_p;
    v4[1] = stack_p_backup[1];
  }
  exit2_flag = 2;
}

// 0x1ecc540
void Exit3Set(void) {
  s16 *v4;

  stack_p_backup[0] = GBWK->player->stack_p[0];
  v4 = stack_p_backup;
  v4[1] = GBWK->player->stack_p[1];
  exit3_flag = 1;
}

// 0x1ecc6a0
void Exit3(void) {
  s16 *stack_p;
  s16 *v4;

  if (exit3_flag != 1)
    return;
  if ((stack_p_backup[0] & 0x80000000) == 0)
  {
    stack_p = GBWK->player->stack_p;
    stack_p[0] = stack_p_backup[0];
    goto LABEL_13;
  }
LABEL_13:
  if (stack_p_backup[1] < 0)
    return;
  v4 = GBWK->player->stack_p;
  v4[1] = stack_p_backup[1];
  return;
}

// 0x1ecc870
void StopKey(void) {
  if (!dds3SearchProcessName("sbattle"))
    return;
  if (!wk)
    return;
  wk->status4 |= 0x80000u;
}

// 0x1ecc9a0
bool StopBattle(void) {
  dds3ProcessID_t *v2;
  void *Instance;

  v2 = dds3SearchProcessName("sbattle");
  if (!v2)
    return (char)v2;
  if (!wk)
  {
    LOBYTE(v2) = 0;
    return (char)v2;
  }
  wk->status |= 0x40u;
  Instance = get_Instance(0);
  BattleDispUIOn(Instance, 0);
  LOBYTE(v2) = 1;
  return (char)v2;
}

// 0x1ec8240
bool IsSceanStop(void) {
  s32 v3;
  u32 status;

  if (!wk)
    return 0;
  v3 = (wk->status >> 6) & 1;
  if (wk->hitStop)
    return 1;
  if (!sBtlIsSetsumaPadStop())
    return (sBtlIsEnemyLastDeadStop() | v3) != 0;
  return 1;
}

// 0x1eccaf0
bool CheckStopBattle(void) {
  dds3ProcessID_t *v2;

  v2 = dds3SearchProcessName("sbattle");
  if (!v2)
    return (char)v2;
  if (!wk)
    goto LABEL_19;
  if (!IsSceanStop())
    goto LABEL_19;
  if ((wk->status & 0x100000) == 0)
    goto LABEL_17;
LABEL_19:
  LOBYTE(v2) = 0;
  return (char)v2;
LABEL_17:
  LOBYTE(v2) = 1;
  return (char)v2;
}

// 0x1ecb9f0
bool RestartBattle(void) {
  dds3ProcessID_t *v2;
  u32 status4;

  v2 = dds3SearchProcessName("sbattle");
  if (!v2)
    return (char)v2;
  if (!wk)
  {
    LOBYTE(v2) = 0;
    return (char)v2;
  }
  status4 = wk->status4;
  wk->status &= ~0x40u;
  wk->status4 = status4 & 0xFEB7FFFF;
  LOBYTE(v2) = 1;
  return (char)v2;
}

// 0x1eccc60
bool StopBattle_StopUV(void) {
  wk->status4 |= 0x400000u;
  return 1;
}

// 0x1ecb920
bool ReloadTableData(void) {
  sBtlLoadOnMemMsg();
  sBtlInitLoadAttackHitData_pData();
  return 1;
}

// 0x1ecccd0
bool LoadOnMemoryData(void) {
  SBATTLE_WORK *v2;
  SBATTLE_WORK3 *v5;
  SBATTLE_WORK2 *v7;

  LoadTableData();
  sBtlInitEffect();
  sBtlOnDataLoadInit_Pac1();
  v2 = Allocate(SBATTLE_WORK);
  _ctor(v2, 0);
  wk = v2;
  wk->mode = 1;
  v5 = Allocate(SBATTLE_WORK3);
  _ctor(v5, 0);
  wk3 = v5;
  v7 = Allocate(SBATTLE_WORK2);
  _ctor(v7, 0);
  wk2 = v7;
  sBtlInitEffectWork();
  sBtlInitLoadAttackHitData_pData();
  sBtlMap_Init();
  return 1;
}

// 0x1ec7f40
void SmnCtrlRun(void) {
  SUMMON_CTRL *smnCtrl;
  s64 v5;
  s32 v6;
  s64 v7;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 v9;
  s64 v11;

  if (!wk)
    return;
  smnCtrl = wk->smnCtrl;
  if (!smnCtrl->bNoOk)
    return;
  if (smnCtrl->io)
    goto LABEL_12;
  goto LABEL_27;
  if (!smnCtrl->io)
  {
LABEL_27:
    smnCtrl = wk->smnCtrl;
    v6 = wk->summonindex[smnCtrl->aprId];
    if (v6 < 0)
      return;
    v7 = (u16)v6;
    UnitMng = wk->UnitMng;
    v9 = wk->summonID[v7];
    if (sBtlSearchUnit_ID(UnitMng, v9))
      return;
    v11 = 0;
    wk->smnCtrl->bNoOk = 0;
    while (1)
    {
      if (!wk->summonflg[v11])
      {
        wk->summonID[v11] = 0;
      }
      if (++v11 == 32)
        return;
    }
  }
LABEL_12:
  smnCtrl = wk->smnCtrl;
  if (wk->summonflg[smnCtrl->stkId] == 2)
  {
    smnCtrl = wk->smnCtrl;
    v5 = 0;
    smnCtrl->bNoOk = 0;
    do
    {
      if (!wk->summonflg[v5])
      {
        wk->summonID[v5] = 0;
      }
      ++v5;
    }
    while (v5 != 32);
  }
}

// 0x1eccee0
bool CheckRun(void) {
  if (!wk)
    return 0;
  return dds3SearchProcessName("sbattle") != 0;
}
