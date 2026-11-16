#include "types.h"
#include "aw.h"
#include "aw_disco.h"
#include "aw_fatkbtn.h"
#include "aw_hitlight.h"
#include "aw_hits.h"
#include "cmpmain.h"
#include "dat.h"
#include "dds3_pad.h"
#include "dds3adminiprocess.h"
#include "dds3basic.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "dds3objectbase.h"
#include "dds3scenebasic.h"
#include "dds3unitobjectbasic.h"
#include "dds3worldbasic.h"
#include "evtbit.h"
#include "expdraw.h"
#include "file.h"
#include "fld.h"
#include "kernel.h"
#include "mapenemy.h"
#include "mdl.h"
#include "sbattle.h"
#include "sbtlencount.h"
#include "sbtlsound.h"
#include "sbtlsub.h"
#include "sbtlvisual.h"
#include "sdat.h"
#include "sdf_vu0.h"
#include "sdfmodel.h"
#include "sdfquat.h"
#include "sdfsound.h"

#define MAP_ENEMY_OBJ_MAX 40
#define MAP_ENEMY_MDL_MAX 4
#define MAP_ENEMY_RES_AVATAR_MAX 21
#define MAP_ENEMY_RES_DEVIL_MAX 16
#define MAP_ENEMY_RES_LOAD_MAX 16
#define MAP_ENEMY_GUNZEI_NUM 3
#define MAP_ENEMY_TRAP_VAL_NUM 16
#define MAP_ENEMY_TRAP1_VAL_NUM 16
#define EP00 1
#define EP01 2
#define EP02 4
#define EP03 8
#define EP04 16
#define EP05 32
#define EP06 64
#define EP07 128
#define EP08 256
#define EP09 512
#define EP10 1024
#define EP11 2048
#define EP12 4096
#define EP_ALL 8191
#define EP00_03 15
#define EP04_12 8176
#define EP07NOT 8063
#define EP09NOT 7679
#define EP00_09 1023
#define EP10_12 7168

typedef enum {
    ENUM_ENEMY_RES_NULL = 0,
    ENUM_ENEMY_RES_HITO = 1,
    ENUM_ENEMY_RES_ONNA = 2,
    ENUM_ENEMY_RES_RYUU = 3,
    ENUM_ENEMY_RES_JYUUJIN = 4,
    ENUM_ENEMY_RES_JYAC = 5,
    ENUM_ENEMY_RES_KEMONO = 6,
    ENUM_ENEMY_RES_SURAIMU = 7,
    ENUM_ENEMY_RES_TORI = 8,
    ENUM_ENEMY_RES_REIKON = 9,
    ENUM_ENEMY_RES_TENSI = 10,
    ENUM_ENEMY_RES_BOSS_HITO = 11,
    ENUM_ENEMY_RES_BOSS_ONNA = 12,
    ENUM_ENEMY_RES_BOSS_RYUU = 13,
    ENUM_ENEMY_RES_BOSS_JYUUJIN = 14,
    ENUM_ENEMY_RES_BOSS_JYAC = 15,
    ENUM_ENEMY_RES_BOSS_KEMONO = 16,
    ENUM_ENEMY_RES_BOSS_SURAIMU = 17,
    ENUM_ENEMY_RES_BOSS_TORI = 18,
    ENUM_ENEMY_RES_BOSS_REIKON = 19,
    ENUM_ENEMY_RES_BOSS_TENSI = 20,
} ENUM_ENEMY_RES;

typedef enum {
    ENUM_ENEMY_STEP_NULL = 0,
    ENUM_ENEMY_STEP_LOAD = 1,
    ENUM_ENEMY_STEP_LOADDONE = 2,
    ENUM_ENEMY_STEP_RESET = 3,
    ENUM_ENEMY_STEP_RESET2 = 4,
    ENUM_ENEMY_STEP_RESET2_2 = 5,
    ENUM_ENEMY_STEP_RESET2_3 = 6,
    ENUM_ENEMY_STEP_RUN_PAUSE = 7,
    ENUM_ENEMY_STEP_RUN = 8,
    ENUM_ENEMY_STEP_FREE_S = 9,
    ENUM_ENEMY_STEP_FREE_M = 10,
} ENUM_ENEMY_STEP;

typedef enum {
    ENUM_ENEMY_MOT_SUMMON = 0,
    ENUM_ENEMY_MOT_STANDBY = 1,
    ENUM_ENEMY_MOT_WALK = 2,
    ENUM_ENEMY_MOT_DISCO = 3,
    ENUM_ENEMY_MOT_RUN = 4,
    ENUM_ENEMY_MOT_DAMAGE = 5,
    ENUM_ENEMY_MOT_DEAD = 6,
    ENUM_ENEMY_MOT_RETURN = 7,
} ENUM_ENEMY_MOT;

typedef enum {
    ENUM_ENEMY_OBJ_AISTEP_STANDBY = 0,
    ENUM_ENEMY_OBJ_AISTEP_DOOR = 1,
    ENUM_ENEMY_OBJ_AISTEP_SUMMON_WAIT = 2,
    ENUM_ENEMY_OBJ_AISTEP_SUMMON_WAIT_2 = 3,
    ENUM_ENEMY_OBJ_AISTEP_SUMMON = 4,
    ENUM_ENEMY_OBJ_AISTEP_STANDBY_UROURO_1 = 5,
    ENUM_ENEMY_OBJ_AISTEP_STANDBY_UROURO_2 = 6,
    ENUM_ENEMY_OBJ_AISTEP_DISCO = 7,
    ENUM_ENEMY_OBJ_AISTEP_RUN = 8,
    ENUM_ENEMY_OBJ_AISTEP_RUN_ASSIST = 9,
    ENUM_ENEMY_OBJ_AISTEP_GIVEUP_1 = 10,
    ENUM_ENEMY_OBJ_AISTEP_GIVEUP_2 = 11,
    ENUM_ENEMY_OBJ_AISTEP_GIVEUP_2B = 12,
    ENUM_ENEMY_OBJ_AISTEP_GIVEUP_3 = 13,
    ENUM_ENEMY_OBJ_AISTEP_RUN_INTERCEPT = 14,
    ENUM_ENEMY_OBJ_AISTEP_RUN_INTERCEPT_ASSIST = 15,
    ENUM_ENEMY_OBJ_AISTEP_RUN_RUSH = 16,
    ENUM_ENEMY_OBJ_AISTEP_DAMAGE = 17,
    ENUM_ENEMY_OBJ_AISTEP_BOSS = 18,
    ENUM_ENEMY_OBJ_AISTEP_BOSS_WARPOUT = 19,
    ENUM_ENEMY_OBJ_AISTEP_BOSS_AREAOUT = 20,
    ENUM_ENEMY_OBJ_AISTEP_TRAP1 = 21,
    ENUM_ENEMY_OBJ_AISTEP_TRAP1_WARP = 22,
    ENUM_ENEMY_OBJ_AISTEP_TRAP1_SUMMON = 23,
    ENUM_ENEMY_OBJ_AISTEP_TRAP1_SUMMON_WAIT = 24,
    ENUM_ENEMY_OBJ_AISTEP_TRAP2 = 25,
    ENUM_ENEMY_OBJ_AISTEP_TRAP2_WAIT = 26,
    ENUM_ENEMY_OBJ_AISTEP_TRAP3 = 27,
    ENUM_ENEMY_OBJ_AISTEP_TRAP3_WAIT = 28,
    ENUM_ENEMY_OBJ_AISTEP_TRAP4 = 29,
    ENUM_ENEMY_OBJ_AISTEP_TRAP4_WAIT = 30,
} ENUM_ENEMY_OBJ_AISTEP;

typedef struct TYPE_ENEMYDIFFTBL TYPE_ENEMYDIFFTBL;
typedef struct TYPE_ENEMYOBJ TYPE_ENEMYOBJ;
typedef struct TYPE_ENEMYOFFSET TYPE_ENEMYOFFSET;
typedef struct TYPE_ENEMYRES TYPE_ENEMYRES;
typedef struct TYPE_ENEMYSIZE TYPE_ENEMYSIZE;
typedef struct TYPE_ENEMYSYMBOLTABLE TYPE_ENEMYSYMBOLTABLE;
typedef struct TYPE_ENEMYWORK TYPE_ENEMYWORK;
typedef struct TYPE_KINSI_AREA_TABLE TYPE_KINSI_AREA_TABLE;
typedef struct TYPE_KINSI_POP_TABLE TYPE_KINSI_POP_TABLE;
typedef struct TYPE_POP_TABLE TYPE_POP_TABLE;
typedef struct TYPE_TRAP TYPE_TRAP;
typedef struct TYPE_TRAP1 TYPE_TRAP1;
typedef struct TYPE_TRAP1_TABLE TYPE_TRAP1_TABLE;
typedef struct TYPE_TRAP2_TABLE TYPE_TRAP2_TABLE;
typedef struct TYPE_TRAP3_TABLE TYPE_TRAP3_TABLE;
typedef struct TYPE_TRAP4_TABLE TYPE_TRAP4_TABLE;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;

struct TYPE_TRAP {
    s32 m_Index;
    s32 m_EncId;
    s32 m_EnemyId;
    s32 m_SymbolId;
};

struct TYPE_TRAP1 {
    s32 m_Index;
    s32 m_EncId[16];
    s32 m_EnemyId[16];
    s32 m_SymbolId[16];
};

struct TYPE_ENEMYOBJ {
    bool m_Use;
    s32 m_ObjIdx;
    sdfVector3_t m_PopPos;
    sdfVector3_t m_PopPos_Bk;
    sdfVector3_t m_Pos;
    f32 m_Dir;
    s32 m_Mot;
    s32 m_MotOld;
    f32 m_MotSpd;
    f32 m_MotHokan;
    f32 m_Len;
    f32 m_DitherAlpha;
    sdfVector3_t m_QuakePos;
    s32 m_QuakePow;
    s32 m_PopTableIdx;
    s32 m_EncountIdx;
    s32 m_EncountPackIdx;
    s32 m_EncountMap;
    s32 m_EncountFloor;
    s32 m_EnemyId;
    s32 m_MoveType;
    bool m_ScreenIn;
    f32 m_ScreenSabun;
    s32 m_AiStep;
    s32 m_AiCnt;
    s32 m_AiParam;
    s32 m_NoDiscoTime;
    sdfVector3_t m_UroUroPos;
    bool m_FAtk;
    s32 m_KabeCnt;
    s32 m_Summon_WaitTime;
    sdfVector3_t m_AssisttPos;
    f32 m_Run_Spd;
    f32 m_Run_MaxSpd;
    s32 m_Run_AiCnt;
    sdfVector3_t m_Run_ContactPos;
    s32 m_Run_Stamina;
    f32 m_Rush_Dir;
    f32 m_Intercept_Spd;
    f32 m_Intercept_MaxSpd;
    f32 m_Intercept_Velocity;
    f32 m_Intercept_Range;
    f32 m_Intercept_Time;
    sdfVector3_t m_Intercept_ContactPos;
    f32 m_Intercept_Dir;
    f32 m_Intercept_PtoEDir;
    s32 m_Intercept_AiCnt;
    s32 m_Intercept_Stamina;
    sdfVector3_t m_ETrap3_SPos;
    f32 m_ETrap3_SDir;
    sdfVector3_t m_ETrap3_GPos;
    f32 m_ETrap3_GDir;
    f32 m_ETrap3_MoveTime;
    sdfVector3_t m_ETrap3_MoveVec;
    f32 m_ETrap3_MoveHigh;
    s32 m_Kemuri_Cnt;
    bool m_AkirameSwitchOn;
    bool m_Trap1;
    bool m_Trap2;
    bool m_Trap3;
    bool m_Trap4;
    bool m_Icon_On;
    s32 m_Icon_Anim;
    bool m_Icon_ScreenOut;
    f32 m_Icon_Len;
    bool m_Icon3D;
    sdfVector3_t m_Icon3D_XYZ;
    bool m_Icon2D;
    f32 m_Icon2D_X;
    f32 m_Icon2D_Y;
    s32 m_Move3dSE_Acter;
    s32 m_UroUroSE_Cnt;
    s32 m_Lv;
    s32 m_Exp;
    s32 m_Item;
    s32 m_EncHitTime;
    bool m_Dead;
    s32 m_EncPackId;
    bool m_QuestEnemyFlag;
    s32 m_EnemySize;
    f32 m_EnemyScale;
    s32 m_Res_Type;
    s32 m_Res_Avatar_Idx;
    s32 m_Res_Devil_Idx;
    dds3Basic_t *m_hMdl_Basic;
    dds3ModelHandle_t *m_hMdl_Model;
    bool m_SceenAdd;
    bool m_CopyMdl;
};

struct TYPE_ENEMYRES {
    s32 m_hEnemy_Res;
    s32 m_NowLink;
    s32 m_EnemyId;
    char *m_AssetKey;
    bool m_SmgLoad;
};

struct TYPE_ENEMYWORK {
    dds3ProcessID_t *m_ProcID;
    s32 m_Step;
    s32 m_Cnt;
    s32 m_Map;
    s32 m_Area;
    s32 m_Area2;
    sdfVector3_t m_PlayerPos;
    f32 m_PlayerSpd;
    f32 m_PlayerDir;
    sdfVector3_t m_PlayerVec;
    TYPE_ENEMYOBJ *m_Obj[40];
    s32 m_EnemyNum;
    s32 m_SummonNum;
    s32 m_OikakeNum;
    s32 m_OikakeSwitchCnt;
    s32 m_Trap1WarpCnt;
    s32 m_StopSummonWaitCnt;
    s32 m_StopNoDiscoCnt;
    bool m_KEnemyOn;
    bool m_HunterSummonOn;
    s32 m_FAtkStep;
    s32 m_FAtkStepCnt;
    bool m_FAtkIcon;
    s32 m_FAtkObjIdx;
    sdfVector3_t m_FAtkNakamaPos;
    sdfVector3_t m_FAtkGoalPos;
    f32 m_FAtkNakamaDir;
    bool m_FAtkRaidoMotion;
    TYPE_ENEMYRES *m_Res_Avatar[21];
    TYPE_ENEMYRES *m_Res_Devil[16];
    TYPE_TRAP1 *m_Trap1[16];
    s32 m_Trap1Num;
    TYPE_TRAP *m_Trap3[16];
    s32 m_Trap3Num;
    TYPE_TRAP *m_Trap2[16];
    s32 m_Trap2Num;
    TYPE_TRAP *m_Trap4[16];
    s32 m_Trap4Num;
};

struct TYPE_ENEMYDIFFTBL {
    s32 m_DiscoInt;
    s32 m_DiscoPar;
    f32 m_RunSpd;
    f32 m_RunAccel;
    f32 m_InterceptSpd;
    f32 m_InterceptAccel;
    s32 m_EncHitTime;
};

struct TYPE_ENEMYSIZE {
    f32 m_N;
    f32 m_B;
    f32 m_S;
};

struct TYPE_ENEMYOFFSET {
    f32 m_N;
    f32 m_B;
    f32 m_S;
};

struct TYPE_ENEMYSYMBOLTABLE {
    s32 m_ModelId;
    s32 m_Range_Disco;
    s32 m_Par_Run;
    s32 m_Spd_Run;
    s32 m_Par_Intercept;
    s32 m_Spd_Intercept;
    s32 m_Par_Rush;
    s32 m_Spd_Rush;
};

struct TYPE_POP_TABLE {
    s32 MId;
    s32 FId;
    s32 E;
    s32 X;
    s32 Y;
    s32 Z;
    s32 P1Dev;
    s32 P1Enc;
    s32 FlgS;
    s32 FlgE;
};

struct TYPE_KINSI_AREA_TABLE {
    s32 m_MapId;
    s32 m_FloorId;
    s32 m_OnFlag;
    s32 m_OffFlag;
};

struct TYPE_KINSI_POP_TABLE {
    s32 m_MapId;
    s32 m_FloorId;
    s32 m_PopId;
    s32 m_OnFlag;
    s32 m_OffFlag;
};

struct TYPE_TRAP1_TABLE {
    s32 m_MapId;
    s32 m_FloorId;
    s32 m_CX;
    s32 m_CY;
    s32 m_CZ;
    s32 m_SizeX;
    s32 m_SizeZ;
    s32 m_Rot;
    s32 m_Katamuki;
    s32 m_GenLenType;
    s32 m_EncPackId;
    s32 m_OnFlag;
    s32 m_OffFlag;
    s32 m_1stFlag;
    s32 m_1stPar;
    s32 m_2ndPar;
};

struct TYPE_TRAP2_TABLE {
    s32 m_MapId;
    s32 m_FloorId;
    s32 m_CX;
    s32 m_CY;
    s32 m_CZ;
    s32 m_SizeX;
    s32 m_Rot;
    s32 m_EncPackId;
    s32 m_OnFlag;
    s32 m_OffFlag;
    s32 m_1stFlag;
    s32 m_1stPar;
    s32 m_2ndPar;
    s32 m_SX;
    s32 m_SY;
    s32 m_SZ;
    s32 m_SD;
};

struct TYPE_TRAP3_TABLE {
    s32 m_MapId;
    s32 m_FloorId;
    s32 m_CX;
    s32 m_CY;
    s32 m_CZ;
    s32 m_SizeX;
    s32 m_SizeZ;
    s32 m_Rot;
    s32 m_Katamuki;
    s32 m_EncPackId;
    s32 m_OnFlag;
    s32 m_OffFlag;
    s32 m_1stFlag;
    s32 m_1stPar;
    s32 m_2ndPar;
    s32 m_SX;
    s32 m_SY;
    s32 m_SZ;
    s32 m_SD;
    s32 m_GX;
    s32 m_GY;
    s32 m_GZ;
    s32 m_GD;
    s32 m_Time;
    s32 m_High;
};

struct TYPE_TRAP4_TABLE {
    s32 m_MapId;
    s32 m_FloorId;
    s32 m_CX;
    s32 m_CY;
    s32 m_CZ;
    s32 m_Rot;
    s32 m_EncPackId;
    s32 m_HakaiId;
};

static TYPE_ENEMYWORK *gEnemyWork;
static TYPE_ENEMYDIFFTBL *gMapEnemyDiffTbl;
static TYPE_ENEMYSIZE *gMapEnemySizeTbl;
static TYPE_ENEMYOFFSET *gMapEnemyoffset;
static TYPE_ENEMYSYMBOLTABLE *gMapEnemySymbolTable;
static s32 g_EnemySymbol_Fast_Par;
static f32 g_EnemySymbol_Fast_ClipLen;
static f32 g_EnemySymbol_Far_ClipLen;
static f32 g_EnemySymbol_High_ClipLen;
static f32 g_EnemySymbol_Near_ClipLen;
static f32 g_EnemySymbol_Mid_CountLen;
static s32 g_EnemySymbol_Mid_CountPar;
static s32 g_EnemySymbol_Max;
static s32 g_EnemySymbol_Min;
static s32 g_EnemySymbol_ResMax;
static s32 g_EnemySymbol_Diff;
static s32 g_EnemySummonMax;
static bool g_AttackUse;
static sdfVector3_t g_AttackPos;
static f32 g_AttackDir;
static s32 g_AttackAnmCnt;
static s32 g_AttackHitEnable;
static s32 g_AttackEncCnt;
static s32 g_AttackEnemyObj;
static bool g_AttackEncGo;
static bool g_AttackEstma;
static bool g_AttackDamageUse;
static s32 g_AttackDamageCnt;
static sdfVector3_t g_AttackDamagePos;
static f32 g_AttackDamageDir;
static bool g_BackAttackEncount;
static s32 g_NoEnemyDiscoTime;
static s32 g_GenLenType;
static s32 g_ETrap1TableIndex;
static s32 g_ETrap3TableIndex;
static s32 g_ETrap4TableIndex;
static bool *gPop1St_Done;
static s32 gPop1St_MapId;
static s32 *sMapEnemyIdx_buff;
static s32 sMapEnemyIdx_max;
static TYPE_POP_TABLE *gPopTable;

static f32 GetSizeTable(s32 sizeid, s32 residx);
static void slMapEnemy_CalcDest(dds3ProcessID_t *argsId);
static bool LoadBlock_EX(s32 _ResType, s32 *_ResIdx, s32 _EnemyID);
static bool LoadBlock(s32 _ResType, s32 *_ResIdx, s32 _EnemyID);
static s32 Add1(const sdfVector3_t *aEPos, f32 aEDir);
static void TrapChangeEncId_Trap1(TYPE_ENEMYOBJ *pObj, s32 idx, s32 num);
static void TrapChangeEncId(TYPE_ENEMYOBJ *pObj, s32 idx, s32 type);
static s32 Add_trap(const sdfVector3_t *aEPos, s32 idx, s32 packid, s32 type);
static void Choice1(TYPE_ENEMYOBJ *pObj);
static void ReSet_SummonWait(TYPE_ENEMYOBJ *pObj);
static void Reset_Calc(void);
static void SceneDel_Calc(void);
static void MemFree_Calc(void);
static void SceneDel_1(TYPE_ENEMYOBJ *pObj);
static void MemFree_NotFreeBase_1(TYPE_ENEMYOBJ *pObj);
static bool Damage_Check(TYPE_ENEMYOBJ *pObj);
static s32 Get_RexIdx(s32 _EnemyID);
static bool Load_MotionSe(TYPE_ENEMYOBJ *pObj);
static bool Free_MotionSe(TYPE_ENEMYOBJ *pObj);
static void EnemySe(TYPE_ENEMYOBJ *pObj, s32 seid);
static TYPE_ENEMYOBJ *Get_OikakeEnemy(void);
static bool Set_NearPoint_2(TYPE_ENEMYOBJ *pObj);
static bool Set_NearPoint(TYPE_ENEMYOBJ *pObj);
static void AI_Update(void);
static void InOutUpdate(void);
static void mapEnemy_Update(void);
static void mapEnemy_FAtkUpdate(void);
static void mapEnemy_SetFAtk_PlayerDir(void);
static dds3ProcessFunc_t slMapEnemy_Calc(dds3ProcessID_t *argsId);
static bool IsEnemyMatch(TYPE_ENEMYOBJ *pObj);
static s32 AsdMdlSyncLoad(s32 _DevilID, char **_AssetKey);
static void AsdMdlFree(TYPE_ENEMYOBJ *pObj);
static void Free_AllAsset(void);
static dds3Basic_t *AsdMdlCopy(s32 _ResId);
static void AsdMdlSceneAddModel(TYPE_ENEMYOBJ *pObj, s32 _ResId);
static void AsdMdlSceneDelModel(TYPE_ENEMYOBJ *pObj);
static void AsdMdlShow(TYPE_ENEMYOBJ *pObj);
static void AsdMdlHide(TYPE_ENEMYOBJ *pObj);
static bool AsdMdlCheckHide(TYPE_ENEMYOBJ *pObj);
static void AsdMdlSetPosition(TYPE_ENEMYOBJ *pObj, const sdfVector3_t *_Pos);
static void AsdMdlSetRotationXYZ(TYPE_ENEMYOBJ *pObj, f32 _DirX, f32 _DirY, f32 _DirZ);
static void AsdMdlSetScaleXYZ(TYPE_ENEMYOBJ *pObj, f32 _SclX, f32 _SclY, f32 _SclZ);
static void AsdModelSetChrAnmNo(TYPE_ENEMYOBJ *pObj, s32 _MotId, f32 _Hokan);
static void AsdMdlSetChrAnmSpeed(TYPE_ENEMYOBJ *pObj, f32 _MotSpd);
static bool AsdMdlChkChrAnmEnd(TYPE_ENEMYOBJ *pObj);
static void AsdMdlSetDitherAlpha(TYPE_ENEMYOBJ *pObj, f32 _DitherAlpha);
u32 GetDevilSE(s32 devilID, s32 motionID);

// 0x1b6d7a0
void mapEnemyTP(void) {
  ;
}

// 0x1b6d7b0
static f32 GetSizeTable(s32 sizeid, s32 residx) {
  s64 v5;

  if ((u32)(residx - 2) > 0x12)
  {
    v5 = 1;
    if (sizeid != 2)
    {
LABEL_5:
      if (sizeid == 3)
      {
        return gMapEnemySizeTbl[v5]->m_S;
      }
      else
      {
        return gMapEnemySizeTbl[v5]->m_N;
      }
    }
  }
  else
  {
    v5 = qword_3E62158[residx - 2];
    if (sizeid != 2)
      goto LABEL_5;
  }
  return gMapEnemySizeTbl[v5]->m_B;
}

// 0x1b6d8e0
void mapInit(dds3ProcessID_t *planProsessID) {
  TYPE_ENEMYWORK *v3;
  TYPE_ENEMYWORK *gEnemyWork_local;
  dds3ProcessFunc_t v6;
  shutdownfuncDelegate v7;
  dds3ProcessID_t *started;
  s32 v9;
  s64 v10;
  s64 v11;
  s32 v12;
  TYPE_ENEMYOBJ *m_Obj;
  TYPE_ENEMYOBJ *v14;
  TYPE_ENEMYRES *m_Res_Avatar;
  s64 i;
  s64 v17;
  TYPE_ENEMYRES *v18;
  s64 j;
  char *v20;
  s64 v21;
  TYPE_ENEMYRES *m_Res_Devil;
  TYPE_ENEMYRES *v23;
  s64 v24;
  s64 v25;
  u32 *v26;
  u32 *v27;
  u32 *v28;
  TYPE_TRAP1 *m_Trap1;
  TYPE_TRAP1 *v30;
  TYPE_TRAP *m_Trap3;
  s64 k;
  s64 v33;
  TYPE_TRAP *v34;
  TYPE_TRAP *m_Trap2;
  s64 v36;
  s64 v37;
  TYPE_TRAP *v38;
  TYPE_TRAP *m_Trap4;
  s64 v40;
  s64 v41;
  TYPE_TRAP *v42;
  dds3ProcessID_t *parent;

  parent = planProsessID;
  if (!gEnemyWork)
  {
    v3 = Allocate(TYPE_ENEMYWORK);
    _ctor(v3, 0);
    gEnemyWork = v3;
  }
  gEnemyWork_local = gEnemyWork;
  v6 = Allocate(dds3ProcessFunc_t);
  _ctor(v6, 0, Method_Project_mapEnemy_slMapEnemy_Calc__, 0);
  v7 = Allocate(shutdownfuncDelegate);
  _ctor(v7, 0, Method_Project_mapEnemy_slMapEnemy_CalcDest__, 0);
  started = dds3StartProcess("mapEnemy", 1012, 0, 0, v6, v7, 0);
  gEnemyWork_local->m_ProcID = started;
  dds3LinkProcess(parent, &gEnemyWork_local->m_ProcID);
  v9 = 0;
  v10 = 32;
  gEnemyWork_local->m_Area2 = -1;
  *(u64 *)&gEnemyWork_local->m_Step = 0;
  *(u64 *)&gEnemyWork_local->m_Map = 0;
  *(u64 *)&gEnemyWork_local->m_EnemyNum = 0;
  *(u64 *)&gEnemyWork_local->m_OikakeNum = 0;
  *(u64 *)&gEnemyWork_local->m_StopSummonWaitCnt = 0;
  *(u16 *)&gEnemyWork_local->m_KEnemyOn = 0;
  *(u64 *)&gEnemyWork_local->m_FAtkStep = 0;
  gEnemyWork_local->m_FAtkIcon = 0;
  gEnemyWork_local->m_FAtkObjIdx = -1;
  gEnemyWork_local->m_FAtkRaidoMotion = 0;
  *(u64 *)&gEnemyWork_local->m_FAtkNakamaPos.x = 0;
  *(u64 *)&gEnemyWork_local->m_FAtkNakamaPos.z = 0;
  *(u64 *)&gEnemyWork_local->m_FAtkGoalPos.y = 0;
  do
  {
    m_Obj = gEnemyWork_local->m_Obj;
    v14 = Allocate(TYPE_ENEMYOBJ);
    _ctor(v14, 0);
    *(Il2CppClass **)((char *)&m_Obj->obj.klass + v10) = v14;
    v11 = *(s64 *)((char *)&gEnemyWork_local->m_Obj->obj.klass + v10);
    *(u64 *)(v11 + 24) = 0;
    *(u8 *)(v11 + 16) = 0;
    *(u32 *)(v11 + 20) = v9;
    *(u32 *)(v11 + 32) = 0;
    *(u32 *)(v11 + 44) = 0;
    *(u32 *)(v11 + 64) = 0;
    *(u32 *)(v11 + 68) = -1;
    *(u64 *)(v11 + 48) = 0;
    *(u64 *)(v11 + 56) = 0;
    *(u64 *)(v11 + 104) = 0xFFFFFFFFLL;
    *(u32 *)(v11 + 112) = 0;
    *(u64 *)(v11 + 124) = 0x100000000LL;
    *(u8 *)(v11 + 132) = 0;
    *(u32 *)(v11 + 140) = 0;
    *(u32 *)(v11 + 144) = 0;
    *(u64 *)(v11 + 36) = 0;
    *(_OWORD *)(v11 + 72) = xmmword_3D01650;
    v12 = sub_1905740(200, 0);
    *(u32 *)(v11 + 336) = 0;
    *(u64 *)(v11 + 380) = 0x3E700000000LL;
    *(u32 *)(v11 + 148) = v12 + 60;
    *(u32 *)(v11 + 152) = 0;
    *(u64 *)(v11 + 324) = 0;
    *(u8 *)(v11 + 340) = 0;
    *(u32 *)(v11 + 344) = 0;
    *(u16 *)(v11 + 332) = 0;
    *(u32 *)(v11 + 396) = 0;
    *(u8 *)(v11 + 168) = 0;
    *(u8 *)(v11 + 400) = 0;
    *(u64 *)(v11 + 428) = 0;
    *(u64 *)(v11 + 420) = 0;
    *(u32 *)(v11 + 436) = 0;
    *(u64 *)(v11 + 440) = 0;
    v10 += 8;
    *(u16 *)(v11 + 448) = 0;
    ++v9;
    *(u8 *)(v11 + 408) = 0;
    *(u64 *)(v11 + 412) = 0x3F80000000000001LL;
  }
  while (v10 != 352);
  m_Res_Avatar = gEnemyWork_local->m_Res_Avatar;
  for (i = 32; i != 200; i += 8)
  {
    v18 = Allocate(TYPE_ENEMYRES);
    _ctor(v18, 0);
    *(Il2CppClass **)((char *)&m_Res_Avatar->obj.klass + i) = v18;
    m_Res_Avatar = gEnemyWork_local->m_Res_Avatar;
    v17 = *(s64 *)((char *)&m_Res_Avatar->obj.klass + i);
    *(u64 *)(v17 + 16) = 0xFFFFFFFFLL;
    *(u8 *)(v17 + 40) = 0;
  }
  for (j = 32; j != 160; j += 8)
  {
    m_Res_Devil = gEnemyWork_local->m_Res_Devil;
    v23 = Allocate(TYPE_ENEMYRES);
    _ctor(v23, 0);
    *(Il2CppClass **)((char *)&m_Res_Devil->obj.klass + j) = v23;
    v20 = "";
    v21 = *(s64 *)((char *)&gEnemyWork_local->m_Res_Devil->obj.klass + j);
    *(u64 *)(v21 + 32) = "";
    v21 += 32;
    *(u64 *)(v21 - 16) = 0xFFFFFFFFLL;
    *(u32 *)(v21 - 8) = -1;
    *(u8 *)(v21 + 8) = 0;
  }
  v24 = 32;
  do
  {
    m_Trap1 = gEnemyWork_local->m_Trap1;
    v30 = Allocate(TYPE_TRAP1);
    _ctor(v30, 0);
    *(Il2CppClass **)((char *)&m_Trap1->obj.klass + v24) = v30;
    v25 = *(s64 *)((char *)&gEnemyWork_local->m_Trap1->obj.klass + v24);
    v24 += 8;
    *(u32 *)(v25 + 16) = -1;
    v26 = *(u32 **)(v25 + 24);
    v27 = *(u32 **)(v25 + 32);
    v28 = *(u32 **)(v25 + 40);
    v26[8] = 0;
    v27[8] = 0;
    v28[8] = 0;
    v26[9] = 0;
    v27[9] = 0;
    v28[9] = 0;
    v26[10] = 0;
    v27[10] = 0;
    v28[10] = 0;
    v26[11] = 0;
    v27[11] = 0;
    v28[11] = 0;
    v26[12] = 0;
    v27[12] = 0;
    v28[12] = 0;
    v26[13] = 0;
    v27[13] = 0;
    v28[13] = 0;
    v26[14] = 0;
    v27[14] = 0;
    v28[14] = 0;
    v26[15] = 0;
    v27[15] = 0;
    v28[15] = 0;
    v26[16] = 0;
    v27[16] = 0;
    v28[16] = 0;
    v26[17] = 0;
    v27[17] = 0;
    v28[17] = 0;
    v26[18] = 0;
    v27[18] = 0;
    v28[18] = 0;
    v26[19] = 0;
    v27[19] = 0;
    v28[19] = 0;
    v26[20] = 0;
    v27[20] = 0;
    v28[20] = 0;
    v26[21] = 0;
    v27[21] = 0;
    v28[21] = 0;
    v26[22] = 0;
    v27[22] = 0;
    v28[22] = 0;
    v26[23] = 0;
    v27[23] = 0;
    v28[23] = 0;
  }
  while (v24 != 160);
  gEnemyWork_local->m_Trap1Num = 0;
  m_Trap3 = gEnemyWork_local->m_Trap3;
  for (k = 32; k != 160; k += 8)
  {
    v34 = Allocate(TYPE_TRAP);
    _ctor(v34, 0);
    *(Il2CppClass **)((char *)&m_Trap3->obj.klass + k) = v34;
    m_Trap3 = gEnemyWork_local->m_Trap3;
    v33 = *(s64 *)((char *)&m_Trap3->obj.klass + k);
    *(_OWORD *)(v33 + 16) = xmmword_3D00DF0;
  }
  m_Trap2 = gEnemyWork_local->m_Trap2;
  v36 = 32;
  gEnemyWork_local->m_Trap3Num = 0;
  do
  {
    v38 = Allocate(TYPE_TRAP);
    _ctor(v38, 0);
    *(Il2CppClass **)((char *)&m_Trap2->obj.klass + v36) = v38;
    m_Trap2 = gEnemyWork_local->m_Trap2;
    v37 = *(s64 *)((char *)&m_Trap2->obj.klass + v36);
    v36 += 8;
    *(_OWORD *)(v37 + 16) = xmmword_3D00DF0;
  }
  while (v36 != 160);
  m_Trap4 = gEnemyWork_local->m_Trap4;
  v40 = 32;
  gEnemyWork_local->m_Trap2Num = 0;
  do
  {
    v42 = Allocate(TYPE_TRAP);
    _ctor(v42, 0);
    *(Il2CppClass **)((char *)&m_Trap4->obj.klass + v40) = v42;
    m_Trap4 = gEnemyWork_local->m_Trap4;
    v41 = *(s64 *)((char *)&m_Trap4->obj.klass + v40);
    v40 += 8;
    *(_OWORD *)(v41 + 16) = xmmword_3D00DF0;
  }
  while (v40 != 160);
  gEnemyWork_local->m_Trap4Num = 0;
}

// 0x1b6e070
void mapKill(void) {
  TYPE_ENEMYWORK *gEnemyWork_local;

  gEnemyWork_local = gEnemyWork;
  dds3KillProcess(&gEnemyWork_local->m_ProcID, 0);
}

// 0x1b6e140
static void slMapEnemy_CalcDest(dds3ProcessID_t *argsId) {
  _BOOL8 v2;

  DelAW_ListType(1, 1);
  v2 = mapFree_MotionSe_All();
  Free_AllAsset();
  if (!gEnemyWork)
    return;
  gEnemyWork = 0;
}

// 0x1b6e4e0
void mapFirstInit1St(void) {
  s64 v2;
  bool *gPop1St_Done_local;

  v2 = 32;
  gPop1St_MapId = -1;
  while (1)
  {
    gPop1St_Done_local = gPop1St_Done;
    if (v2 - 32 >= SLODWORD(gPop1St_Done_local->max_length))
      break;
    gPop1St_Done_local = gPop1St_Done;
    *((u8 *)&gPop1St_Done_local->obj.klass + v2++) = 0;
  }
}

// 0x1b6e5a0
void mapInit1St(s32 _MapId) {
  s64 i;
  bool *gPop1St_Done_local;

  if (gPop1St_MapId == MapId)
    return;
  gPop1St_MapId = MapId;
  for (i = 32; ; ++i)
  {
    gPop1St_Done_local = gPop1St_Done;
    if (i - 32 >= SLODWORD(gPop1St_Done_local->max_length))
      break;
    gPop1St_Done_local = gPop1St_Done;
    *((u8 *)&gPop1St_Done_local->obj.klass + i) = 0;
  }
}

// 0x1b6e6a0
bool mapChk1St(s32 _PopTableIdx, s32 *_DevilID, s32 *_EncountID) {
  s64 v6;
  TYPE_POP_TABLE *v11;

  LODWORD(v6) = PopTableIdx;
  *DevilID = 0;
  *EncountID = 0;
  if ((u32)v6 == -1)
    return 0;
  if (SLODWORD(gPop1St_Done->max_length) <= (s32)v6)
    return 0;
  v6 = (s32)v6;
  if (gPop1St_Done[(s32)v6])
    return 0;
  v11 = gPopTable[v6];
  *DevilID = v11->P1Dev;
  *EncountID = v11->P1Enc;
  return 1;
}

// 0x1b6e7e0
void mapSet1StDone(s32 _PopTableIdx) {
  if ((PopTableIdx & 0x80000000) == 0)
  {
    if (SLODWORD(gPop1St_Done->max_length) <= PopTableIdx)
      return;
    gPop1St_Done[PopTableIdx] = 1;
  }
}

// 0x1b6e8b0
bool mapChkPopEpsode(s32 _PopTableIdx) {
  u8 chapter;

  chapter = GBWK->GameFileInfo->chapter;
  return ((u32)gPopTable[PopTableIdx]->E >> chapter) & 1;
}

// 0x1b6e970
bool mapChkPopJKFlg(s32 _PopTableIdx) {
  TYPE_POP_TABLE *v4;
  TYPE_POP_TABLE *v5;
  TYPE_POP_TABLE *v7;
  s32 FlgE;

  if (PopTableIdx == -1)
    return 0;
  v4 = gPopTable[PopTableIdx];
  if (v4->FlgS)
  {
    if (v4->FlgE)
    {
      if (!evtBitCheck(v4->FlgS))
        return 0;
      if (evtBitCheck(gPopTable[PopTableIdx]->FlgE))
        return 0;
      goto LABEL_14;
    }
  }
  v5 = gPopTable[PopTableIdx];
  if (!v5->FlgS)
    goto LABEL_24;
  goto LABEL_22;
LABEL_14:
  v5 = gPopTable[PopTableIdx];
  if (!v5->FlgS)
    goto LABEL_24;
LABEL_22:
  v5 = gPopTable[PopTableIdx];
  if (!v5->FlgE)
    goto LABEL_28;
LABEL_24:
  goto LABEL_25;
LABEL_28:
  if (evtBitCheck(gPopTable[PopTableIdx]->FlgS))
  {
    goto LABEL_32;
  }
  return 0;
LABEL_32:
LABEL_25:
  v7 = gPopTable[PopTableIdx];
  if (v7->FlgS)
    return 1;
  FlgE = v7->FlgE;
  if (!FlgE)
    return 1;
  if (evtBitCheck(FlgE))
    return 0;
  return 1;
}

// 0x1b6ec40
void mapLoadStart(s32 map, s32 area) {
  bool v6;
  s32 v7;
  TYPE_ENEMYWORK *gEnemyWork_local;

  if (area)
    v6 = 0;
  else
    v6 = map == 22;
  if (v6)
    v7 = 2;
  else
    v7 = -1;
  gEnemyWork_local = gEnemyWork;
  *(u64 *)&gEnemyWork_local->m_Step = 1;
  gEnemyWork_local->m_Area2 = v7;
  gEnemyWork_local->m_Map = map;
  gEnemyWork_local->m_Area = area;
  mapInit1St(map);
}

// 0x1b6ed00
bool mapLoadCheckDone(void) {
  return gEnemyWork->m_Step == 2;
}

// 0x1b6ede0
void mapReset2(void) {
  g_AttackEstma = 0;
  *(u64 *)&gEnemyWork->m_Step = 4;
  g_AttackEncCnt = 0;
}

// 0x1b6ee50
void mapReset3(void) {
  s64 v3;
  TYPE_ENEMYWORK *gEnemyWork_local;
  TYPE_ENEMYOBJ *m_Obj;
  s64 v6;

  v3 = 32;
  *(u16 *)&g_AttackEncGo = 0;
  gEnemyWork_local = gEnemyWork;
  *(u64 *)&g_AttackPos.z = 0;
  *(u64 *)&g_AttackPos.x = 0;
  g_AttackUse = 0;
  *(u64 *)&g_AttackDamageCnt = 0;
  *(u64 *)&g_AttackDamagePos.y = 0;
  *(u64 *)((char *)&g_AttackDamagePos.z + 1) = 0;
  g_AttackEncCnt = 0;
  g_AttackDamageUse = 0;
  m_Obj = gEnemyWork_local->m_Obj;
  do
  {
    v6 = *(s64 *)((char *)&m_Obj->obj.klass + v3);
    if (*(u8 *)(v6 + 16) && (*(u32 *)(v6 + 420) || *(s32 *)(v6 + 424) <= 0) && *(u32 *)(v6 + 140) == 17)
    {
      --gEnemyWork_local->m_OikakeNum;
      *(u64 *)(v6 + 140) = 12;
    }
    v3 += 8;
  }
  while (v3 != 352);
}

// 0x1b6ef30
void mapAiRun(bool runmode) {
  s32 v5;

  if (!gEnemyWork->m_Step)
    return;
  if (runmode)
    v5 = 8;
  else
    v5 = 7;
  gEnemyWork->m_Step = v5;
  gEnemyWork->m_Cnt = 0;
}

// 0x1b6efd0
void mapModelFree(void) {
  TYPE_ENEMYWORK *gEnemyWork_local;

  gEnemyWork_local = gEnemyWork;
  if (!gEnemyWork_local->m_Step)
    return;
  *(u64 *)&gEnemyWork_local->m_Step = 9;
}

// 0x1b6f060
bool mapModelFreeDoneCheck(void) {
  if (gEnemyWork)
    return gEnemyWork->m_Step == 0;
  return 1;
}

// 0x1b6f100
static bool LoadBlock_EX(s32 _ResType, s32 *_ResIdx, s32 _EnemyID) {
  TYPE_ENEMYRES *m_Res_Devil;
  TYPE_ENEMYRES *v10;
  s32 v11;
  s64 v12;
  TYPE_ENEMYRES *v14;
  s64 v15;
  char *v16;
  TYPE_ENEMYRES *v17;
  char *AssetKey;

  AssetKey = "";
  if (!ResType)
    return 1;
  m_Res_Devil = gEnemyWork->m_Res_Devil;
  v10 = m_Res_Devil[0];
  if (v10->m_hEnemy_Res == -1)
  {
    v12 = 0;
LABEL_72:
    AsdMdlSyncLoad(EnemyID, &AssetKey);
    v14 = gEnemyWork->m_Res_Devil;
    v15 = v12;
    v10->m_hEnemy_Res = EnemyID;
    v16 = AssetKey;
    v17 = v14[v15];
    v17->m_AssetKey = AssetKey;
    v17 = ((char *)v17 + 32);
    *(u32 *)&v17[-1].m_SmgLoad = EnemyID;
    gEnemyWork->m_Res_Devil[v15]->m_NowLink = 0;
    return 1;
  }
  if (v10->m_EnemyId == EnemyID)
  {
    v11 = 0;
LABEL_70:
    *ResIdx = v11;
    return 1;
  }
  v10 = m_Res_Devil[1];
  if (v10->m_hEnemy_Res == -1)
  {
    v12 = 1;
    goto LABEL_72;
  }
  if (v10->m_EnemyId == EnemyID)
  {
    v11 = 1;
    goto LABEL_70;
  }
  v10 = m_Res_Devil[2];
  if (v10->m_hEnemy_Res == -1)
  {
    v12 = 2;
    goto LABEL_72;
  }
  if (v10->m_EnemyId == EnemyID)
  {
    v11 = 2;
    goto LABEL_70;
  }
  v10 = m_Res_Devil[3];
  if (v10->m_hEnemy_Res == -1)
  {
    v12 = 3;
    goto LABEL_72;
  }
  if (v10->m_EnemyId == EnemyID)
  {
    v11 = 3;
    goto LABEL_70;
  }
  v10 = m_Res_Devil[4];
  if (v10->m_hEnemy_Res == -1)
  {
    v12 = 4;
    goto LABEL_72;
  }
  if (v10->m_EnemyId == EnemyID)
  {
    v11 = 4;
    goto LABEL_70;
  }
  v10 = m_Res_Devil[5];
  if (v10->m_hEnemy_Res == -1)
  {
    v12 = 5;
    goto LABEL_72;
  }
  if (v10->m_EnemyId == EnemyID)
  {
    v11 = 5;
    goto LABEL_70;
  }
  v10 = m_Res_Devil[6];
  if (v10->m_hEnemy_Res == -1)
  {
    v12 = 6;
    goto LABEL_72;
  }
  if (v10->m_EnemyId == EnemyID)
  {
    v11 = 6;
    goto LABEL_70;
  }
  v10 = m_Res_Devil[7];
  if (v10->m_hEnemy_Res == -1)
  {
    v12 = 7;
    goto LABEL_72;
  }
  if (v10->m_EnemyId == EnemyID)
  {
    v11 = 7;
    goto LABEL_70;
  }
  v10 = m_Res_Devil[8];
  if (v10->m_hEnemy_Res == -1)
  {
    v12 = 8;
    goto LABEL_72;
  }
  if (v10->m_EnemyId == EnemyID)
  {
    v11 = 8;
    goto LABEL_70;
  }
  v10 = m_Res_Devil[9];
  if (v10->m_hEnemy_Res == -1)
  {
    v12 = 9;
    goto LABEL_72;
  }
  if (v10->m_EnemyId == EnemyID)
  {
    v11 = 9;
    goto LABEL_70;
  }
  v10 = m_Res_Devil[10];
  if (v10->m_hEnemy_Res == -1)
  {
    v12 = 10;
    goto LABEL_72;
  }
  if (v10->m_EnemyId == EnemyID)
  {
    v11 = 10;
    goto LABEL_70;
  }
  v10 = m_Res_Devil[11];
  if (v10->m_hEnemy_Res == -1)
  {
    v12 = 11;
    goto LABEL_72;
  }
  if (v10->m_EnemyId == EnemyID)
  {
    v11 = 11;
    goto LABEL_70;
  }
  v10 = m_Res_Devil[12];
  if (v10->m_hEnemy_Res == -1)
  {
    v12 = 12;
    goto LABEL_72;
  }
  if (v10->m_EnemyId == EnemyID)
  {
    v11 = 12;
    goto LABEL_70;
  }
  v10 = m_Res_Devil[13];
  if (v10->m_hEnemy_Res == -1)
  {
    v12 = 13;
    goto LABEL_72;
  }
  if (v10->m_EnemyId == EnemyID)
  {
    v11 = 13;
    goto LABEL_70;
  }
  v10 = m_Res_Devil[14];
  if (v10->m_hEnemy_Res == -1)
  {
    v12 = 14;
    goto LABEL_72;
  }
  if (v10->m_EnemyId == EnemyID)
  {
    v11 = 14;
    goto LABEL_70;
  }
  v10 = m_Res_Devil[15];
  if (v10->m_hEnemy_Res == -1)
  {
    v12 = 15;
    goto LABEL_72;
  }
  if (v10->m_EnemyId == EnemyID)
  {
    v11 = 15;
    goto LABEL_70;
  }
  return 0;
}

// 0x1b6f6a0
static bool LoadBlock(s32 _ResType, s32 *_ResIdx, s32 _EnemyID) {
  TYPE_ENEMYRES *m_Res_Avatar;
  TYPE_ENEMYRES *m_Res_Devil;
  u32 v11;
  u32 v12;
  TYPE_ENEMYRES *v13;
  s32 m_hEnemy_Res;
  s32 v15;
  u32 v16;
  bool v17;
  TYPE_ENEMYRES *v18;
  TYPE_ENEMYRES *v19;
  s32 v20;
  TYPE_ENEMYRES *v21;
  TYPE_ENEMYRES *v22;
  s32 v23;
  s32 v24;
  char *v26;
  s64 m_Items;
  s64 v28;
  char *AssetKey;

  AssetKey = "";
  m_Res_Avatar = gEnemyWork->m_Res_Avatar;
  m_Res_Devil = gEnemyWork->m_Res_Devil;
  v11 = m_Res_Avatar[1]->m_hEnemy_Res != -1;
  if (m_Res_Avatar[0]->m_hEnemy_Res != -1)
    ++v11;
  if (m_Res_Avatar[2]->m_hEnemy_Res == -1)
    v12 = v11;
  else
    v12 = v11 + 1;
  if (m_Res_Avatar[3]->m_hEnemy_Res != -1)
    ++v12;
  if (m_Res_Avatar[4]->m_hEnemy_Res != -1)
    ++v12;
  if (m_Res_Avatar[5]->m_hEnemy_Res != -1)
    ++v12;
  if (m_Res_Avatar[6]->m_hEnemy_Res != -1)
    ++v12;
  if (m_Res_Avatar[7]->m_hEnemy_Res != -1)
    ++v12;
  if (m_Res_Avatar[8]->m_hEnemy_Res != -1)
    ++v12;
  if (m_Res_Avatar[9]->m_hEnemy_Res != -1)
    ++v12;
  if (m_Res_Avatar[10]->m_hEnemy_Res != -1)
    ++v12;
  if (m_Res_Avatar[11]->m_hEnemy_Res != -1)
    ++v12;
  if (m_Res_Avatar[12]->m_hEnemy_Res != -1)
    ++v12;
  if (m_Res_Avatar[13]->m_hEnemy_Res != -1)
    ++v12;
  if (m_Res_Avatar[14]->m_hEnemy_Res != -1)
    ++v12;
  if (m_Res_Avatar[15]->m_hEnemy_Res != -1)
    ++v12;
  if (m_Res_Avatar[16]->m_hEnemy_Res != -1)
    ++v12;
  if (m_Res_Avatar[17]->m_hEnemy_Res != -1)
    ++v12;
  v13 = m_Res_Avatar[19];
  m_hEnemy_Res = m_Res_Avatar[18]->m_hEnemy_Res;
  v15 = m_Res_Avatar[20]->m_hEnemy_Res;
  if (m_hEnemy_Res != -1)
    ++v12;
  if (v13->m_hEnemy_Res != -1)
    ++v12;
  if (v15 == -1)
    v16 = v12;
  else
    v16 = v12 + 1;
  if (m_Res_Devil[0]->m_hEnemy_Res != -1)
    ++v16;
  if (m_Res_Devil[1]->m_hEnemy_Res != -1)
    ++v16;
  if (m_Res_Devil[2]->m_hEnemy_Res != -1)
    ++v16;
  if (m_Res_Devil[3]->m_hEnemy_Res != -1)
    ++v16;
  if (m_Res_Devil[4]->m_hEnemy_Res != -1)
    ++v16;
  if (m_Res_Devil[5]->m_hEnemy_Res != -1)
    ++v16;
  if (m_Res_Devil[6]->m_hEnemy_Res != -1)
    ++v16;
  if (m_Res_Devil[7]->m_hEnemy_Res != -1)
    ++v16;
  if (m_Res_Devil[8]->m_hEnemy_Res != -1)
    ++v16;
  if (m_Res_Devil[9]->m_hEnemy_Res != -1)
    ++v16;
  if (m_Res_Devil[10]->m_hEnemy_Res != -1)
    ++v16;
  if (m_Res_Devil[11]->m_hEnemy_Res != -1)
    ++v16;
  if (m_Res_Devil[12]->m_hEnemy_Res != -1)
    ++v16;
  v17 = m_Res_Devil[13]->m_hEnemy_Res == -1;
  v19 = m_Res_Devil[14];
  v18 = m_Res_Devil[15];
  if (!v17)
    ++v16;
  v20 = v18->m_hEnemy_Res;
  if (v19->m_hEnemy_Res != -1)
    ++v16;
  if (v20 != -1)
    ++v16;
  if (v16 > 0xF)
    return 0;
  if (ResType)
  {
    v21 = gEnemyWork->m_Res_Devil;
    v22 = v21[0];
    if (v22->m_hEnemy_Res == -1)
    {
      v24 = 0;
    }
    else
    {
      if (v22->m_EnemyId == EnemyID)
      {
        v23 = 0;
LABEL_144:
        *ResIdx = v23;
        return 1;
      }
      v22 = v21[1];
      if (v22->m_hEnemy_Res == -1)
      {
        v24 = 1;
      }
      else
      {
        if (v22->m_EnemyId == EnemyID)
        {
          v23 = 1;
          goto LABEL_144;
        }
        v22 = v21[2];
        if (v22->m_hEnemy_Res == -1)
        {
          v24 = 2;
        }
        else
        {
          if (v22->m_EnemyId == EnemyID)
          {
            v23 = 2;
            goto LABEL_144;
          }
          v22 = v21[3];
          if (v22->m_hEnemy_Res == -1)
          {
            v24 = 3;
          }
          else
          {
            if (v22->m_EnemyId == EnemyID)
            {
              v23 = 3;
              goto LABEL_144;
            }
            v22 = v21[4];
            if (v22->m_hEnemy_Res == -1)
            {
              v24 = 4;
            }
            else
            {
              if (v22->m_EnemyId == EnemyID)
              {
                v23 = 4;
                goto LABEL_144;
              }
              v22 = v21[5];
              if (v22->m_hEnemy_Res == -1)
              {
                v24 = 5;
              }
              else
              {
                if (v22->m_EnemyId == EnemyID)
                {
                  v23 = 5;
                  goto LABEL_144;
                }
                v22 = v21[6];
                if (v22->m_hEnemy_Res == -1)
                {
                  v24 = 6;
                }
                else
                {
                  if (v22->m_EnemyId == EnemyID)
                  {
                    v23 = 6;
                    goto LABEL_144;
                  }
                  v22 = v21[7];
                  if (v22->m_hEnemy_Res == -1)
                  {
                    v24 = 7;
                  }
                  else
                  {
                    if (v22->m_EnemyId == EnemyID)
                    {
                      v23 = 7;
                      goto LABEL_144;
                    }
                    v22 = v21[8];
                    if (v22->m_hEnemy_Res == -1)
                    {
                      v24 = 8;
                    }
                    else
                    {
                      if (v22->m_EnemyId == EnemyID)
                      {
                        v23 = 8;
                        goto LABEL_144;
                      }
                      v22 = v21[9];
                      if (v22->m_hEnemy_Res == -1)
                      {
                        v24 = 9;
                      }
                      else
                      {
                        if (v22->m_EnemyId == EnemyID)
                        {
                          v23 = 9;
                          goto LABEL_144;
                        }
                        v22 = v21[10];
                        if (v22->m_hEnemy_Res == -1)
                        {
                          v24 = 10;
                        }
                        else
                        {
                          if (v22->m_EnemyId == EnemyID)
                          {
                            v23 = 10;
                            goto LABEL_144;
                          }
                          v22 = v21[11];
                          if (v22->m_hEnemy_Res == -1)
                          {
                            v24 = 11;
                          }
                          else
                          {
                            if (v22->m_EnemyId == EnemyID)
                            {
                              v23 = 11;
                              goto LABEL_144;
                            }
                            v22 = v21[12];
                            if (v22->m_hEnemy_Res == -1)
                            {
                              v24 = 12;
                            }
                            else
                            {
                              if (v22->m_EnemyId == EnemyID)
                              {
                                v23 = 12;
                                goto LABEL_144;
                              }
                              v22 = v21[13];
                              if (v22->m_hEnemy_Res == -1)
                              {
                                v24 = 13;
                              }
                              else
                              {
                                if (v22->m_EnemyId == EnemyID)
                                {
                                  v23 = 13;
                                  goto LABEL_144;
                                }
                                v22 = v21[14];
                                if (v22->m_hEnemy_Res == -1)
                                {
                                  v24 = 14;
                                }
                                else
                                {
                                  if (v22->m_EnemyId == EnemyID)
                                  {
                                    v23 = 14;
                                    goto LABEL_144;
                                  }
                                  v22 = v21[15];
                                  if (v22->m_hEnemy_Res != -1)
                                  {
                                    if (v22->m_EnemyId == EnemyID)
                                    {
                                      v23 = 15;
                                      goto LABEL_144;
                                    }
                                    return 0;
                                  }
                                  v24 = 15;
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
    *ResIdx = v24;
    AsdMdlSyncLoad(EnemyID, &AssetKey);
    v22->m_hEnemy_Res = EnemyID;
    v26 = AssetKey;
    m_Items = gEnemyWork->m_Res_Devil;
    *(u32 *)(*(u64 *)(m_Items + 8 * *ResIdx) + 24) = EnemyID;
    v28 = *(u64 *)(m_Items + 8 * *ResIdx);
    *(u64 *)(v28 + 32) = v26;
    gEnemyWork->m_Res_Devil[*ResIdx]->m_NowLink = 0;
  }
  return 1;
}

// 0x1b6fca0
static s32 Add1(const sdfVector3_t *aEPos, f32 aEDir) {
  f32 z;
  f32 y;
  f32 x;
  TYPE_ENEMYOBJ *m_Obj;
  TYPE_ENEMYOBJ *v10;
  s32 v11;
  s64 v12;
  s32 v13;
  s32 v14;
  s32 v15;

  z = aEPos->z;
  y = aEPos->y;
  x = aEPos->x;
  m_Obj = gEnemyWork->m_Obj;
  v10 = m_Obj[0];
  if (v10->m_Use)
    goto LABEL_4;
  v11 = 0;
LABEL_86:
  v10->m_PopPos.x = x;
  v10->m_PopPos.y = y;
  v12 = *(u64 *)&v10->m_PopPos.x;
  v10->m_PopPos.z = z;
  v10->m_Use = 1;
  v10->m_Pos.x = x;
  v10->m_Pos.y = y;
  v10->m_Pos.z = z;
  v10->m_Dir = aEDir;
  v10->m_Len = 0.0;
  v10->m_MoveType = 1;
  v10->m_EncHitTime = 0;
  *(u64 *)&v10->m_PopPos_Bk.x = v12;
  *(f32 *)&v12 = v10->m_PopPos.z;
  v10->m_FAtk = 0;
  v10->m_Dead = 0;
  LODWORD(v10->m_PopPos_Bk.z) = v12;
  *(u64 *)&v10->m_MotSpd = 0x404000003F000000LL;
  *(u64 *)&v10->m_Mot = 0xFFFFFFFF00000000LL;
  *(u64 *)&v10->m_AiStep = 2;
  v13 = sub_1905740(200, 0);
  v10->m_UroUroSE_Cnt = 0;
  *(u64 *)&v10->m_AiParam = (u32)(v13 + 60);
  v14 = sub_1905740(300, 0);
  *(u16 *)&v10->m_AkirameSwitchOn = 0;
  v10->m_Trap3 = 0;
  v10->m_Summon_WaitTime = v14 + 1;
  v15 = gEnemyWork->m_EnemyNum + 1;
  v10->m_Res_Type = 1;
  gEnemyWork->m_EnemyNum = v15;
  return v11;
LABEL_4:
  v10 = m_Obj[1];
  if (!v10->m_Use)
  {
    v11 = 1;
    goto LABEL_86;
  }
  v10 = m_Obj[2];
  if (!v10->m_Use)
  {
    v11 = 2;
    goto LABEL_86;
  }
  v10 = m_Obj[3];
  if (!v10->m_Use)
  {
    v11 = 3;
    goto LABEL_86;
  }
  v10 = m_Obj[4];
  if (!v10->m_Use)
  {
    v11 = 4;
    goto LABEL_86;
  }
  v10 = m_Obj[5];
  if (!v10->m_Use)
  {
    v11 = 5;
    goto LABEL_86;
  }
  v10 = m_Obj[6];
  if (!v10->m_Use)
  {
    v11 = 6;
    goto LABEL_86;
  }
  v10 = m_Obj[7];
  if (!v10->m_Use)
  {
    v11 = 7;
    goto LABEL_86;
  }
  v10 = m_Obj[8];
  if (!v10->m_Use)
  {
    v11 = 8;
    goto LABEL_86;
  }
  v10 = m_Obj[9];
  if (!v10->m_Use)
  {
    v11 = 9;
    goto LABEL_86;
  }
  v10 = m_Obj[10];
  if (!v10->m_Use)
  {
    v11 = 10;
    goto LABEL_86;
  }
  v10 = m_Obj[11];
  if (!v10->m_Use)
  {
    v11 = 11;
    goto LABEL_86;
  }
  v10 = m_Obj[12];
  if (!v10->m_Use)
  {
    v11 = 12;
    goto LABEL_86;
  }
  v10 = m_Obj[13];
  if (!v10->m_Use)
  {
    v11 = 13;
    goto LABEL_86;
  }
  v10 = m_Obj[14];
  if (!v10->m_Use)
  {
    v11 = 14;
    goto LABEL_86;
  }
  v10 = m_Obj[15];
  if (!v10->m_Use)
  {
    v11 = 15;
    goto LABEL_86;
  }
  v10 = m_Obj[16];
  if (!v10->m_Use)
  {
    v11 = 16;
    goto LABEL_86;
  }
  v10 = m_Obj[17];
  if (!v10->m_Use)
  {
    v11 = 17;
    goto LABEL_86;
  }
  v10 = m_Obj[18];
  if (!v10->m_Use)
  {
    v11 = 18;
    goto LABEL_86;
  }
  v10 = m_Obj[19];
  if (!v10->m_Use)
  {
    v11 = 19;
    goto LABEL_86;
  }
  v10 = m_Obj[20];
  if (!v10->m_Use)
  {
    v11 = 20;
    goto LABEL_86;
  }
  v10 = m_Obj[21];
  if (!v10->m_Use)
  {
    v11 = 21;
    goto LABEL_86;
  }
  v10 = m_Obj[22];
  if (!v10->m_Use)
  {
    v11 = 22;
    goto LABEL_86;
  }
  v10 = m_Obj[23];
  if (!v10->m_Use)
  {
    v11 = 23;
    goto LABEL_86;
  }
  v10 = m_Obj[24];
  if (!v10->m_Use)
  {
    v11 = 24;
    goto LABEL_86;
  }
  v10 = m_Obj[25];
  if (!v10->m_Use)
  {
    v11 = 25;
    goto LABEL_86;
  }
  v10 = m_Obj[26];
  if (!v10->m_Use)
  {
    v11 = 26;
    goto LABEL_86;
  }
  v10 = m_Obj[27];
  if (!v10->m_Use)
  {
    v11 = 27;
    goto LABEL_86;
  }
  v10 = m_Obj[28];
  if (!v10->m_Use)
  {
    v11 = 28;
    goto LABEL_86;
  }
  v10 = m_Obj[29];
  if (!v10->m_Use)
  {
    v11 = 29;
    goto LABEL_86;
  }
  v10 = m_Obj[30];
  if (!v10->m_Use)
  {
    v11 = 30;
    goto LABEL_86;
  }
  v10 = m_Obj[31];
  if (!v10->m_Use)
  {
    v11 = 31;
    goto LABEL_86;
  }
  v10 = m_Obj[32];
  if (!v10->m_Use)
  {
    v11 = 32;
    goto LABEL_86;
  }
  v10 = m_Obj[33];
  if (!v10->m_Use)
  {
    v11 = 33;
    goto LABEL_86;
  }
  v10 = m_Obj[34];
  if (!v10->m_Use)
  {
    v11 = 34;
    goto LABEL_86;
  }
  v10 = m_Obj[35];
  if (!v10->m_Use)
  {
    v11 = 35;
    goto LABEL_86;
  }
  v10 = m_Obj[36];
  if (!v10->m_Use)
  {
    v11 = 36;
    goto LABEL_86;
  }
  v10 = m_Obj[37];
  if (!v10->m_Use)
  {
    v11 = 37;
    goto LABEL_86;
  }
  v10 = m_Obj[38];
  if (!v10->m_Use)
  {
    v11 = 38;
    goto LABEL_86;
  }
  v10 = m_Obj[39];
  if (!v10->m_Use)
  {
    v11 = 39;
    goto LABEL_86;
  }
  return -1;
}

// 0x1b70120
static void TrapChangeEncId_Trap1(TYPE_ENEMYOBJ *pObj, s32 idx, s32 num) {
  TYPE_TRAP1 *m_Trap1;
  TYPE_TRAP1 *v9;
  s32 *m_EncId;
  s32 *m_EnemyId;
  s64 v13;
  s32 v15;
  s64 v16;
  DEVILDATA_WORK *DevilData;
  SBTLITEM_WORK *item;
  SBTLITEM_WORK *v19;
  s32 getexp;
  s32 v22;
  VISUALDATA_WORK *VisualData;
  s32 *m_SymbolId;

  m_Trap1 = gEnemyWork->m_Trap1;
  v9 = m_Trap1[0];
  if (v9->m_Index == idx)
    goto LABEL_30;
  v9 = m_Trap1[1];
  if (v9->m_Index == idx)
    goto LABEL_30;
  v9 = m_Trap1[2];
  if (v9->m_Index == idx)
    goto LABEL_30;
  v9 = m_Trap1[3];
  if (v9->m_Index == idx)
    goto LABEL_30;
  v9 = m_Trap1[4];
  if (v9->m_Index == idx)
    goto LABEL_30;
  v9 = m_Trap1[5];
  if (v9->m_Index == idx)
    goto LABEL_30;
  v9 = m_Trap1[6];
  if (v9->m_Index == idx)
    goto LABEL_30;
  v9 = m_Trap1[7];
  if (v9->m_Index == idx)
    goto LABEL_30;
  v9 = m_Trap1[8];
  if (v9->m_Index == idx || (v9 = m_Trap1[9], v9->m_Index == idx) || (v9 = m_Trap1[10], v9->m_Index == idx) || (v9 = m_Trap1[11], v9->m_Index == idx) || (v9 = m_Trap1[12], v9->m_Index == idx) || (v9 = m_Trap1[13], v9->m_Index == idx) || (v9 = m_Trap1[14], v9->m_Index == idx) || (v9 = m_Trap1[15], v9->m_Index == idx))
  {
LABEL_30:
    SceneDel_1(pObj);
    MemFree_NotFreeBase_1(pObj);
    m_EncId = v9->m_EncId;
    m_EnemyId = v9->m_EnemyId;
    v13 = 4 * num;
    pObj->m_EncountPackIdx = 0;
    pObj->m_EncountIdx = *(s32 *)((char *)m_EncId + v13);
    v15 = *(s32 *)((char *)m_EnemyId + v13);
    pObj->m_EnemyId = v15;
    if (!(u32)v13)
    v16 = num;
    DevilData = sBtlGetDevilData(v15, -1);
    item = DevilData->item;
    pObj->m_EnemySize = 100;
    pObj->m_Lv = DevilData->level;
    v19 = item[0];
    getexp = DevilData->getexp;
    pObj->m_Exp = getexp;
    v22 = pObj->m_EnemyId;
    pObj->m_Item = v19->itemid;
    VisualData = sBtlGetVisualData(1u, v22);
    m_SymbolId = v9->m_SymbolId;
    pObj->m_Res_Type = 1;
    pObj->m_EnemyScale = VisualData->scale;
    pObj->m_Res_Devil_Idx = m_SymbolId[v16];
  }
}

// 0x1b706a0
static void TrapChangeEncId(TYPE_ENEMYOBJ *pObj, s32 idx, s32 type) {
  s32 v8;
  TYPE_TRAP *m_Trap3;
  TYPE_TRAP *v11;
  s32 m_EnemyId;
  DEVILDATA_WORK *DevilData;
  SBTLITEM_WORK *item;
  SBTLITEM_WORK *v18;
  s32 getexp;
  s32 v21;
  f32 scale;

  v8 = type - 1;
  if ((u32)(type - 1) > 3)
    return;
  switch (v8)
  {
    case 0:
    case 2:
      m_Trap3 = gEnemyWork->m_Trap3;
      v11 = m_Trap3[0];
      if (v11)
        goto LABEL_13;
      goto LABEL_14;
    case 1:
      m_Trap3 = gEnemyWork->m_Trap2;
      v11 = m_Trap3[0];
      if (!v11)
        goto LABEL_14;
      goto LABEL_13;
    case 3:
      m_Trap3 = gEnemyWork->m_Trap4;
      v11 = m_Trap3[0];
      if (!v11)
        goto LABEL_14;
LABEL_13:
      if (v11->m_Index == idx)
        goto LABEL_44;
LABEL_14:
      v11 = m_Trap3[1];
      if (v11 && v11->m_Index == idx)
        goto LABEL_44;
      v11 = m_Trap3[2];
      if (v11)
      {
        if (v11->m_Index == idx)
          goto LABEL_44;
      }
      v11 = m_Trap3[3];
      if (v11)
      {
        if (v11->m_Index == idx)
          goto LABEL_44;
      }
      v11 = m_Trap3[4];
      if (v11)
      {
        if (v11->m_Index == idx)
          goto LABEL_44;
      }
      v11 = m_Trap3[5];
      if (v11)
      {
        if (v11->m_Index == idx)
          goto LABEL_44;
      }
      v11 = m_Trap3[6];
      if (v11)
      {
        if (v11->m_Index == idx)
          goto LABEL_44;
      }
      v11 = m_Trap3[7];
      if (v11)
      {
        if (v11->m_Index == idx)
          goto LABEL_44;
      }
      v11 = m_Trap3[8];
      if (v11)
      {
        if (v11->m_Index == idx)
          goto LABEL_44;
      }
      if ((v11 = m_Trap3[9]) != 0 && v11->m_Index == idx || (v11 = m_Trap3[10]) != 0 && v11->m_Index == idx || (v11 = m_Trap3[11]) != 0 && v11->m_Index == idx || (v11 = m_Trap3[12]) != 0 && v11->m_Index == idx || (v11 = m_Trap3[13]) != 0 && v11->m_Index == idx || (v11 = m_Trap3[14]) != 0 && v11->m_Index == idx || (v11 = m_Trap3[15]) != 0 && v11->m_Index == idx)
      {
LABEL_44:
        SceneDel_1(pObj);
        MemFree_NotFreeBase_1(pObj);
        m_EnemyId = v11->m_EnemyId;
        pObj->m_EncountIdx = v11->m_EncId;
        pObj->m_EncountPackIdx = 0;
        pObj->m_EnemyId = m_EnemyId;
        DevilData = sBtlGetDevilData(m_EnemyId, -1);
        item = DevilData->item;
        pObj->m_EnemySize = 100;
        pObj->m_Lv = DevilData->level;
        v18 = item[0];
        getexp = DevilData->getexp;
        pObj->m_Exp = getexp;
        v21 = pObj->m_EnemyId;
        pObj->m_Item = v18->itemid;
        scale = sBtlGetVisualData(1u, v21)->scale;
        pObj->m_Res_Type = 1;
        pObj->m_EnemyScale = scale;
        pObj->m_Res_Devil_Idx = v11->m_SymbolId;
      }
      break;
    default:
      return;
  }
}

// 0x1b709a0
static s32 Add_trap(const sdfVector3_t *aEPos, s32 idx, s32 packid, s32 type) {
  s32 v8;
  TYPE_TRAP1 *m_Trap1;
  TYPE_TRAP1 *v11;
  s64 v12;
  s32 *v13;
  s32 v14;
  s32 *m_EnemyId;
  s32 *m_SymbolId;
  s32 v18;
  s32 result;
  TYPE_TRAP *m_Trap2;
  TYPE_TRAP *v21;
  s32 *p_m_SymbolId;

  v8 = type - 1;
  switch (v8)
  {
    case 0:
      m_Trap1 = gEnemyWork->m_Trap1;
      v11 = m_Trap1[0];
      if (v11->m_Index != -1)
      {
        v11 = m_Trap1[1];
        if (v11->m_Index != -1)
        {
          v11 = m_Trap1[2];
          if (v11->m_Index != -1)
          {
            v11 = m_Trap1[3];
            if (v11->m_Index != -1)
            {
              v11 = m_Trap1[4];
              if (v11->m_Index != -1)
              {
                v11 = m_Trap1[5];
                if (v11->m_Index != -1)
                {
                  v11 = m_Trap1[6];
                  if (v11->m_Index != -1)
                  {
                    v11 = m_Trap1[7];
                    if (v11->m_Index != -1)
                    {
                      v11 = m_Trap1[8];
                      if (v11->m_Index != -1)
                      {
                        v11 = m_Trap1[9];
                        if (v11->m_Index != -1)
                        {
                          v11 = m_Trap1[10];
                          if (v11->m_Index != -1)
                          {
                            v11 = m_Trap1[11];
                            if (v11->m_Index != -1)
                            {
                              v11 = m_Trap1[12];
                              if (v11->m_Index != -1)
                              {
                                v11 = m_Trap1[13];
                                if (v11->m_Index != -1)
                                {
                                  v11 = m_Trap1[14];
                                  if (v11->m_Index != -1)
                                  {
                                    v11 = m_Trap1[15];
                                    if (v11->m_Index != -1)
                                      goto LABEL_49;
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
      v12 = 32;
      v11->m_Index = idx;
      do
      {
        m_EnemyId = v11->m_EnemyId;
        m_SymbolId = v11->m_SymbolId;
        *(u32 *)((char *)&v11->m_EncId->obj.klass + v12) = 0;
        *(u32 *)((char *)&m_EnemyId->obj.klass + v12) = 146;
        *(u32 *)((char *)&m_SymbolId->obj.klass + v12) = 0;
        v18 = *(u32 *)((char *)&m_EnemyId->obj.klass + v12);
        v13 = ((char *)m_SymbolId + v12);
        v14 = 1;
        LoadBlock_EX(1, v13, v18);
        v12 += 4;
      }
      while (v12 != 96);
      return v14;
    case 1:
      m_Trap2 = gEnemyWork->m_Trap2;
      v21 = m_Trap2[0];
      if (v21->m_Index == -1)
        goto LABEL_50;
      goto LABEL_34;
    case 2:
      m_Trap2 = gEnemyWork->m_Trap3;
      v21 = m_Trap2[0];
      if (v21->m_Index == -1)
        goto LABEL_50;
      goto LABEL_34;
    case 3:
      m_Trap2 = gEnemyWork->m_Trap4;
      v21 = m_Trap2[0];
      if (v21->m_Index == -1)
        goto LABEL_50;
LABEL_34:
      v21 = m_Trap2[1];
      if (v21->m_Index == -1)
        goto LABEL_50;
      v21 = m_Trap2[2];
      if (v21->m_Index == -1)
        goto LABEL_50;
      v21 = m_Trap2[3];
      if (v21->m_Index == -1)
        goto LABEL_50;
      v21 = m_Trap2[4];
      if (v21->m_Index == -1)
        goto LABEL_50;
      v21 = m_Trap2[5];
      if (v21->m_Index == -1)
        goto LABEL_50;
      v21 = m_Trap2[6];
      if (v21->m_Index == -1)
        goto LABEL_50;
      v21 = m_Trap2[7];
      if (v21->m_Index == -1)
        goto LABEL_50;
      v21 = m_Trap2[8];
      if (v21->m_Index == -1 || (v21 = m_Trap2[9], v21->m_Index == -1) || (v21 = m_Trap2[10], v21->m_Index == -1) || (v21 = m_Trap2[11], v21->m_Index == -1) || (v21 = m_Trap2[12], v21->m_Index == -1) || (v21 = m_Trap2[13], v21->m_Index == -1) || (v21 = m_Trap2[14], v21->m_Index == -1) || (v21 = m_Trap2[15], v21->m_Index == -1))
      {
LABEL_50:
        v21->m_SymbolId = 0;
        p_m_SymbolId = &v21->m_SymbolId;
        *(p_m_SymbolId - 3) = idx;
        *((u64 *)p_m_SymbolId - 1) = 0x9200000000LL;
        LoadBlock_EX(1, p_m_SymbolId, 146);
        result = 1;
      }
      else
      {
LABEL_49:
        result = -1;
      }
      break;
    default:
      return -1;
  }
  return result;
}

// 0x1b70d60
static void Choice1(TYPE_ENEMYOBJ *pObj) {
  s32 m_PopTableIdx;
  bool v5;
  f32 x;
  f32 z;
  s32 v9;
  s32 v10;
  s32 EncountDevil1_Lv;
  DEVILDATA_WORK *DevilData;
  SBTLITEM_WORK *item;
  SBTLITEM_WORK *v15;
  s32 getexp;
  s32 m_EnemyId;
  s32 RndEnc;
  s32 v20;
  s32 v21;
  s32 EncountID[2];

  *(u64 *)EncountID = 0;
  m_PopTableIdx = pObj->m_PopTableIdx;
  pObj->m_QuestEnemyFlag = 0;
  v5 = mapChk1St(m_PopTableIdx, &EncountID[1], EncountID);
  x = pObj->m_PopPos.x;
  z = pObj->m_PopPos.z;
  if (!v5)
  {
    RndEnc = mapGetRndEnc(x, z);
    pObj->m_EncountPackIdx = RndEnc;
    v20 = RndEnc;
    v10 = sBtlRndEncCalc_Symbol(v20, &pObj->m_EncountMap, &pObj->m_EncountFloor);
    pObj->m_EncountIdx = v10;
LABEL_20:
    EncountDevil1_Lv = sBtlGetEncountDevil1_Lv(v10);
    pObj->m_EnemyId = EncountDevil1_Lv;
    goto LABEL_11;
  }
  v9 = mapGetRndEnc(x, z);
  v10 = EncountID[0];
  pObj->m_EncountPackIdx = v9;
  if (v10)
  {
    EncountDevil1_Lv = EncountID[1];
    pObj->m_EncountIdx = v10;
    if (EncountDevil1_Lv)
      goto LABEL_10;
    goto LABEL_27;
  }
  v21 = v9;
  v10 = sBtlRndEncCalc_Symbol(v21, &pObj->m_EncountMap, &pObj->m_EncountFloor);
  EncountDevil1_Lv = EncountID[1];
  pObj->m_EncountIdx = v10;
  if (!EncountDevil1_Lv)
  {
LABEL_27:
    goto LABEL_20;
  }
LABEL_10:
  pObj->m_EnemyId = EncountDevil1_Lv;
LABEL_11:
  DevilData = sBtlGetDevilData(EncountDevil1_Lv, -1);
  item = DevilData->item;
  pObj->m_EnemySize = 100;
  pObj->m_Lv = DevilData->level;
  v15 = item[0];
  getexp = DevilData->getexp;
  pObj->m_Exp = getexp;
  m_EnemyId = pObj->m_EnemyId;
  pObj->m_Item = v15->itemid;
  pObj->m_EnemyScale = sBtlGetVisualData(1u, m_EnemyId)->scale;
  if (pObj->m_Res_Type)
    pObj->m_Res_Devil_Idx = 0;
  else
    pObj->m_Res_Avatar_Idx = pObj->m_EnemyId > 1200;
}

// 0x1b71030
static void ReSet_SummonWait(TYPE_ENEMYOBJ *pObj) {
  f32 z;
  f32 v7;
  f32 v8;
  f32 v9;
  s64 v10;
  u32 v11;
  s32 v12;
  s32 v13;
  f32 v15;
  f32 x;
  f32 y;
  f32 LenXYZ;
  s32 v19;

  z = pObj->m_PopPos_Bk.z;
  v7 = fldGb[45];
  v8 = fldGb[43];
  v9 = fldGb[44];
  v10 = *(u64 *)&pObj->m_PopPos_Bk.x;
  pObj->m_PopPos.z = z;
  pObj->m_Pos.z = z;
  *(u64 *)&pObj->m_PopPos.x = v10;
  *(u64 *)&pObj->m_Pos.x = v10;
  v11 = sub_1905740(360, 0);
  pObj->m_Len = 0.0;
  pObj->m_Icon_ScreenOut = 0;
  pObj->m_Mot = 1;
  pObj->m_EncHitTime = 0;
  pObj->m_FAtk = 0;
  pObj->m_Dead = 0;
  *(u64 *)&pObj->m_MotSpd = 0x404000003F000000LL;
  pObj->m_Dir = (f32)v11;
  *(u64 *)&pObj->m_AiStep = 2;
  v12 = sub_1905740(200, 0);
  pObj->m_UroUroSE_Cnt = 0;
  *(u64 *)&pObj->m_AiParam = (u32)(v12 + 60);
  v13 = sub_1905740(240, 0) + 60;
  *(u16 *)&pObj->m_AkirameSwitchOn = 0;
  pObj->m_Summon_WaitTime = v13;
  v15 = pObj->m_PopPos.z;
  *(u16 *)&pObj->m_Trap3 = 0;
  x = pObj->m_PopPos.x;
  y = pObj->m_PopPos.y;
  LenXYZ = sBtlGetLenXYZ(v8, v9, v7, x, y, v15);
  if (LenXYZ < 500.0)
  {
    v19 = 600;
LABEL_13:
    pObj->m_Summon_WaitTime += v19;
    return;
  }
  if (LenXYZ < 800.0)
  {
    v19 = 420;
    goto LABEL_13;
  }
  v19 = 300;
  if (LenXYZ < 1000.0 || LenXYZ < 1200.0)
    goto LABEL_13;
}

// 0x1b71250
static void Reset_Calc(void) {
  TYPE_ENEMYWORK *gEnemyWork_local;
  f32 playerX;
  f32 playerY;
  f32 playerZ;
  s64 v10;
  TYPE_ENEMYOBJ *m_Obj;
  s64 v12;
  s64 v13;
  s64 m_Items;
  s64 v15;
  u32 *v16;
  u32 *v17;
  u32 *v18;
  TYPE_TRAP *m_Trap3;
  TYPE_TRAP *m_Trap2;
  TYPE_TRAP *m_Trap4;
  s32 m_Map;
  s32 m_Area;
  s32 m_Area2;
  s32 v25;
  s64 v26;
  s64 v27;
  s32 v28;
  s64 v29;
  u32 *v30;
  u8 chapter;
  s32 v33;
  s32 v34;
  s32 v35;
  f32 v36;
  f32 v37;
  f32 v38;
  f32 LenXYZ;
  TYPE_ENEMYOBJ *v40;
  f32 v41;
  TYPE_ENEMYOBJ *v42;
  s64 v43;
  f32 z;
  f32 v46;
  bool v48;
  f32 x;
  f32 v50;
  s32 v52;
  s32 v53;
  s32 EncountDevil1_Lv;
  DEVILDATA_WORK *DevilData;
  s32 m_EnemyId;
  s32 v58;
  _BOOL4 m_KEnemyOn;
  s64 v60;
  s32 v61;
  s32 v62;
  s32 RndEnc;
  s32 v64;
  s32 v65;
  s32 m_SummonNum;
  f32 y;
  s32 v70;
  f32 FromX;
  s32 EncountID[2];
  s32 Num[2];

  *(u64 *)EncountID = 0;
  *(u64 *)Num = 0;
  gEnemyWork_local = gEnemyWork;
  playerX = fldGb->playerX;
  playerY = fldGb->playerY;
  playerZ = fldGb->playerZ;
  g_NoEnemyDiscoTime = 60;
  g_EnemySymbol_Diff = 0;
  FromX = playerX;
  g_EnemySymbol_Fast_Par = 30;
  g_EnemySymbol_Mid_CountLen = 1000.0;
  *(_OWORD *)&g_EnemySymbol_Fast_ClipLen = xmmword_3D01DF0;
  *(_OWORD *)&g_EnemySymbol_Mid_CountPar = xmmword_3CFA000;
  v10 = 32;
  *(u64 *)&gEnemyWork_local->m_EnemyNum = 0;
  gEnemyWork_local->m_OikakeNum = 0;
  m_Obj = gEnemyWork_local->m_Obj;
  do
  {
    v12 = *(s64 *)((char *)&m_Obj->obj.klass + v10);
    v10 += 8;
    *(u8 *)(v12 + 16) = 0;
    *(u64 *)(v12 + 64) = 0xFFFFFFFF00000000LL;
    *(u64 *)(v12 + 72) = 0x404000003F000000LL;
    *(u16 *)(v12 + 328) = 0;
    *(u8 *)(v12 + 408) = 0;
    *(u32 *)(v12 + 412) = 1;
    *(u16 *)(v12 + 331) = 0;
  }
  while (v10 != 352);
  v13 = 0;
  m_Items = gEnemyWork_local->m_Trap1;
  do
  {
    v15 = *(u64 *)(m_Items + v13);
    v13 += 8;
    *(u32 *)(v15 + 16) = -1;
    v16 = *(u32 **)(v15 + 24);
    v17 = *(u32 **)(v15 + 32);
    v18 = *(u32 **)(v15 + 40);
    v16[8] = 0;
    v17[8] = 0;
    v18[8] = 0;
    v16[9] = 0;
    v17[9] = 0;
    v18[9] = 0;
    v16[10] = 0;
    v17[10] = 0;
    v18[10] = 0;
    v16[11] = 0;
    v17[11] = 0;
    v18[11] = 0;
    v16[12] = 0;
    v17[12] = 0;
    v18[12] = 0;
    v16[13] = 0;
    v17[13] = 0;
    v18[13] = 0;
    v16[14] = 0;
    v17[14] = 0;
    v18[14] = 0;
    v16[15] = 0;
    v17[15] = 0;
    v18[15] = 0;
    v16[16] = 0;
    v17[16] = 0;
    v18[16] = 0;
    v16[17] = 0;
    v17[17] = 0;
    v18[17] = 0;
    v16[18] = 0;
    v17[18] = 0;
    v18[18] = 0;
    v16[19] = 0;
    v17[19] = 0;
    v18[19] = 0;
    v16[20] = 0;
    v17[20] = 0;
    v18[20] = 0;
    v16[21] = 0;
    v17[21] = 0;
    v18[21] = 0;
    v16[22] = 0;
    v17[22] = 0;
    v18[22] = 0;
    v16[23] = 0;
    v17[23] = 0;
    v18[23] = 0;
  }
  while (v13 != 128);
  m_Trap3 = gEnemyWork_local->m_Trap3;
  gEnemyWork_local->m_Trap1Num = 0;
  *(u64 *)Num = 0;
  m_Trap3[0]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap3[1]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap3[2]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap3[3]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap3[4]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap3[5]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap3[6]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap3[7]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap3[8]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap3[9]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap3[10]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap3[11]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap3[12]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap3[13]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap3[14]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap3[15]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  gEnemyWork_local->m_Trap3Num = 0;
  m_Trap2 = gEnemyWork_local->m_Trap2;
  m_Trap2[0]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap2[1]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap2[2]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap2[3]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap2[4]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap2[5]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap2[6]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap2[7]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap2[8]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap2[9]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap2[10]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap2[11]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap2[12]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap2[13]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap2[14]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap2[15]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  gEnemyWork_local->m_Trap2Num = 0;
  m_Trap4 = gEnemyWork_local->m_Trap4;
  m_Trap4[0]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap4[1]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap4[2]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap4[3]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap4[4]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap4[5]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap4[6]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap4[7]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap4[8]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap4[9]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap4[10]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap4[11]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap4[12]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap4[13]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap4[14]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  m_Trap4[15]->fields = (TYPE_TRAP)xmmword_3D00DF0;
  gEnemyWork_local->m_Trap4Num = 0;
  m_Map = gEnemyWork_local->m_Map;
  m_Area = gEnemyWork_local->m_Area;
  m_Area2 = gEnemyWork_local->m_Area2;
  mapFindPopTable(m_Map, m_Area, m_Area2, &Num[1], Num);
  v25 = Num[1];
  if (Num[1] < Num[0] + Num[1])
  {
    v26 = Num[0] + Num[1];
    v27 = Num[1] + 4;
    do
    {
      v30 = *((u32 **)&gPopTable->obj.klass + v27);
      chapter = GBWK->GameFileInfo->chapter;
      if (((*(u32 *)(*((u64 *)&gPopTable->obj.klass + v27) + 24) >> chapter) & 1) == 0)
        goto LABEL_15;
      v33 = v30[7];
      v34 = v30[8];
      v35 = v30[9];
      v36 = v33;
      v37 = v34;
      v38 = v35;
      LenXYZ = sBtlGetLenXYZ(FromX, playerY, playerZ, (f32)v33, v37, v38);
      v40 = gEnemyWork_local->m_Obj;
      v41 = LenXYZ;
      v42 = v40[0];
      if (v42->m_Use)
      {
        v42 = v40[1];
        if (v42->m_Use)
        {
          v42 = v40[2];
          if (v42->m_Use)
          {
            v42 = v40[3];
            if (v42->m_Use)
            {
              v42 = v40[4];
              if (v42->m_Use)
              {
                v42 = v40[5];
                if (v42->m_Use)
                {
                  v42 = v40[6];
                  if (v42->m_Use)
                  {
                    v42 = v40[7];
                    if (v42->m_Use)
                    {
                      v42 = v40[8];
                      if (v42->m_Use)
                      {
                        v42 = v40[9];
                        if (v42->m_Use)
                        {
                          v42 = v40[10];
                          if (v42->m_Use)
                          {
                            v42 = v40[11];
                            if (v42->m_Use)
                            {
                              v42 = v40[12];
                              if (v42->m_Use)
                              {
                                v42 = v40[13];
                                if (v42->m_Use)
                                {
                                  v42 = v40[14];
                                  if (v42->m_Use)
                                  {
                                    v42 = v40[15];
                                    if (v42->m_Use)
                                    {
                                      v42 = v40[16];
                                      if (v42->m_Use)
                                      {
                                        v42 = v40[17];
                                        if (v42->m_Use)
                                        {
                                          v42 = v40[18];
                                          if (v42->m_Use)
                                          {
                                            v42 = v40[19];
                                            if (v42->m_Use)
                                            {
                                              v42 = v40[20];
                                              if (v42->m_Use)
                                              {
                                                v42 = v40[21];
                                                if (v42->m_Use)
                                                {
                                                  v42 = v40[22];
                                                  if (v42->m_Use)
                                                  {
                                                    v42 = v40[23];
                                                    if (v42->m_Use)
                                                    {
                                                      v42 = v40[24];
                                                      if (v42->m_Use)
                                                      {
                                                        v42 = v40[25];
                                                        if (v42->m_Use)
                                                        {
                                                          v42 = v40[26];
                                                          if (v42->m_Use)
                                                          {
                                                            v42 = v40[27];
                                                            if (v42->m_Use)
                                                            {
                                                              v42 = v40[28];
                                                              if (v42->m_Use)
                                                              {
                                                                v42 = v40[29];
                                                                if (v42->m_Use)
                                                                {
                                                                  v42 = v40[30];
                                                                  if (v42->m_Use)
                                                                  {
                                                                    v42 = v40[31];
                                                                    if (v42->m_Use)
                                                                    {
                                                                      v42 = v40[32];
                                                                      if (v42->m_Use)
                                                                      {
                                                                        v42 = v40[33];
                                                                        if (v42->m_Use)
                                                                        {
                                                                          v42 = v40[34];
                                                                          if (v42->m_Use)
                                                                          {
                                                                            v42 = v40[35];
                                                                            if (v42->m_Use)
                                                                            {
                                                                              v42 = v40[36];
                                                                              if (v42->m_Use)
                                                                              {
                                                                                v42 = v40[37];
                                                                                if (v42->m_Use)
                                                                                {
                                                                                  v42 = v40[38];
                                                                                  if (v42->m_Use)
                                                                                  {
                                                                                    v42 = v40[39];
                                                                                    if (v42->m_Use)
                                                                                      goto LABEL_15;
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
      v42->m_PopPos.x = v36;
      v42->m_PopPos.y = v37;
      v42->m_PopPos.z = v38;
      v43 = *(u64 *)&v42->m_PopPos.x;
      z = v42->m_PopPos.z;
      v42->m_Use = 1;
      v42->m_Pos.x = v36;
      v42->m_Pos.y = v37;
      v42->m_Pos.z = v38;
      *(u64 *)&v42->m_PopPos_Bk.x = v43;
      v42->m_PopPos_Bk.z = z;
      v46 = (u32)sub_1905740(360, 0);
      v42->m_Mot = 1;
      *(u64 *)&v42->m_MotSpd = 0x404000003F000000LL;
      v42->m_Len = 0.0;
      v42->m_Icon_ScreenOut = 0;
      v42->m_MoveType = 1;
      v42->m_EncHitTime = 0;
      v42->m_FAtk = 0;
      v42->m_Dead = 0;
      v42->m_Res_Type = 1;
      v42->m_PopTableIdx = v25;
      v42->m_QuestEnemyFlag = 0;
      v42->m_Dir = v46;
      v48 = mapChk1St(v25, &EncountID[1], EncountID);
      x = v42->m_PopPos.x;
      v50 = v42->m_PopPos.z;
      if (!v48)
      {
        RndEnc = mapGetRndEnc(x, v50);
        v42->m_EncountPackIdx = RndEnc;
        v64 = RndEnc;
        v53 = sBtlRndEncCalc_Symbol(v64, &v42->m_EncountMap, &v42->m_EncountFloor);
        v42->m_EncountIdx = v53;
LABEL_93:
        EncountDevil1_Lv = sBtlGetEncountDevil1_Lv(v53);
        v42->m_EnemyId = EncountDevil1_Lv;
        goto LABEL_76;
      }
      v52 = mapGetRndEnc(x, v50);
      v53 = EncountID[0];
      v42->m_EncountPackIdx = v52;
      if (v53)
      {
        EncountDevil1_Lv = EncountID[1];
        v42->m_EncountIdx = v53;
        if (!EncountDevil1_Lv)
          goto LABEL_101;
      }
      else
      {
        v65 = v52;
        v53 = sBtlRndEncCalc_Symbol(v65, &v42->m_EncountMap, &v42->m_EncountFloor);
        EncountDevil1_Lv = EncountID[1];
        v42->m_EncountIdx = v53;
        if (!EncountDevil1_Lv)
        {
LABEL_101:
          goto LABEL_93;
        }
      }
      v42->m_EnemyId = EncountDevil1_Lv;
LABEL_76:
      DevilData = sBtlGetDevilData(EncountDevil1_Lv, -1);
      v42->m_Lv = DevilData->level;
      m_EnemyId = v42->m_EnemyId;
      v42->m_Exp = DevilData->getexp;
      v42->m_Item = DevilData->item[0]->itemid;
      v42->m_EnemySize = 100;
      v42->m_EnemyScale = sBtlGetVisualData(1u, m_EnemyId)->scale;
      if (v42->m_Res_Type)
        v42->m_Res_Avatar_Idx = 0;
      *(u64 *)&v42->m_AiStep = 2;
      v58 = sub_1905740(200, 0);
      v42->m_UroUroSE_Cnt = 0;
      v42->m_AiParam = v58 + 60;
      v42->m_NoDiscoTime = 0;
      *(u16 *)&v42->m_AkirameSwitchOn = 0;
      *(u16 *)&v42->m_Trap3 = 0;
      v42->m_EncHitTime = 0;
      v42->m_FAtk = 0;
      v42->m_Dead = 0;
      m_KEnemyOn = gEnemyWork_local->m_KEnemyOn;
      if (gEnemyWork_local->m_KEnemyOn)
        v60 = 240;
      else
        v60 = 300;
      v61 = sub_1905740(v60, 0);
      v62 = v61 + 60;
      if (!m_KEnemyOn)
        v62 = v61 + 1;
      v42->m_Summon_WaitTime = v62;
      if (v41 < 500.0)
      {
        v28 = v62 + 600;
LABEL_13:
        v42->m_Summon_WaitTime = v28;
        goto LABEL_14;
      }
      if (v41 < 800.0)
      {
        v28 = v62 + 420;
        goto LABEL_13;
      }
      if (v41 < 1000.0 || v41 < 1200.0)
      {
        v28 = v62 + 300;
        goto LABEL_13;
      }
      if (v41 < g_EnemySymbol_Fast_ClipLen)
      {
        m_SummonNum = gEnemyWork_local->m_SummonNum;
        if (m_SummonNum < g_EnemySummonMax - 5 && !gEnemyWork_local->m_KEnemyOn)
        {
          y = v42->m_Pos.y;
          if (sBtlGetABS(playerY - y) < 30.0)
          {
            v70 = sub_1905740(100, 0);
            if (v70 < g_EnemySymbol_Fast_Par)
            {
              v42->m_Summon_WaitTime = 0;
              ++gEnemyWork_local->m_SummonNum;
            }
          }
        }
      }
LABEL_14:
      ++gEnemyWork_local->m_EnemyNum;
LABEL_15:
      v29 = v27 - 3;
      ++v27;
      ++v25;
    }
    while (v29 < v26);
  }
}

// 0x1b71ff0
static void SceneDel_Calc(void) {
  s64 v2;
  TYPE_ENEMYWORK *gEnemyWork_local;
  s64 v4;
  void *v6;
  dds3Basic_t *v7;
  s32 v8;

  v2 = 32;
  gEnemyWork_local = gEnemyWork;
  do
  {
    v4 = *(s64 *)((char *)&gEnemyWork_local->m_Obj->obj.klass + v2);
    if (*(u64 *)(v4 + 432) && *(u8 *)(v4 + 448))
    {
      v6 = (v4 + 432);
      v7 = *(dds3Basic_t *)(v4 + 432);
      dds3SceneBasicDelete(v7);
      *(u64 *)(v4 + 432) = 0;
      *(u64 *)(v4 + 440) = 0;
      v8 = *(u8 *)(v4 + 408);
      *(u8 *)(v4 + 448) = 0;
      *(u8 *)(v4 + 16) = 0;
      if (v8)
        *(u8 *)(v4 + 408) = 0;
      goto LABEL_6;
    }
LABEL_6:
    v2 += 8;
  }
  while (v2 != 352);
}

// 0x1b721f0
static void MemFree_Calc(void) {
  s64 v2;
  TYPE_ENEMYWORK *gEnemyWork_local;
  s64 v4;
  void *v5;
  dds3Basic_t *v6;
  s64 v7;
  char **v8;
  char *v9;
  char *v10;
  s64 v11;
  s64 i;
  char **v14;
  char *v15;
  char *v16;
  s64 v17;

  v2 = 32;
  gEnemyWork_local = gEnemyWork;
  do
  {
    v4 = *(s64 *)((char *)&gEnemyWork_local->m_Obj->obj.klass + v2);
    if (*(u64 *)(v4 + 432))
    {
      if (*(u8 *)(v4 + 449))
      {
        v5 = (v4 + 432);
        v6 = *(dds3Basic_t *)(v4 + 432);
        if (!v6)
          goto LABEL_7;
        dds3SceneBasicDelete(v6);
        *(u64 *)(v4 + 432) = 0;
        *(u64 *)(v4 + 440) = 0;
        goto LABEL_7;
      }
LABEL_7:
      *(u8 *)(v4 + 449) = 0;
    }
    v2 += 8;
  }
  while (v2 != 352);
  v7 = 32;
  gEnemyWork_local->m_SummonNum = 0;
  do
  {
    v11 = *(s64 *)((char *)&gEnemyWork_local->m_Res_Avatar->obj.klass + v7);
    if (*(u32 *)(v11 + 16) != -1)
    {
      v9 = *(char **)(v11 + 32);
      v8 = (v11 + 32);
      Unload(Dependent, v9, 0);
      v10 = "";
      *(v8 - 2) = 0xFFFFFFFFLL;
      *((u32 *)v8 - 2) = -1;
      *v8 = v10;
    }
    v7 += 8;
  }
  while (v7 != 200);
  for (i = 32; i != 160; i += 8)
  {
    v17 = *(s64 *)((char *)&gEnemyWork_local->m_Res_Devil->obj.klass + i);
    if (*(u32 *)(v17 + 16) != -1)
    {
      v15 = *(char **)(v17 + 32);
      v14 = (v17 + 32);
      Unload(Dependent, v15, 0);
      v16 = "";
      *(v14 - 2) = 0xFFFFFFFFLL;
      *((u32 *)v14 - 2) = -1;
      *v14 = v16;
    }
  }
}

// 0x1b703a0
static void SceneDel_1(TYPE_ENEMYOBJ *pObj) {
  TYPE_ENEMYWORK *gEnemyWork_local;
  dds3Basic_t *p_m_hMdl_Basic;
  dds3Basic_t *v7;
  s32 m_Res_Type;
  s64 v9;
  bool v10;
  s64 v11;
  s64 v12;

  if (!pObj->m_hMdl_Basic)
    return;
  if (!pObj->m_SceenAdd)
    return;
  gEnemyWork_local = gEnemyWork;
  p_m_hMdl_Basic = &pObj->m_hMdl_Basic;
  v7 = p_m_hMdl_Basic;
  dds3SceneBasicDelete(v7);
  pObj->m_hMdl_Basic = 0;
  pObj->m_hMdl_Model = 0;
  m_Res_Type = pObj->m_Res_Type;
  v9 = 176;
  pObj->m_SceenAdd = 0;
  v10 = m_Res_Type == 0;
  v11 = 428;
  if (v10)
  {
    v9 = 168;
    v11 = 424;
  }
  v12 = *((u64 *)&(*(TYPE_ENEMYWORK **)((char *)&gEnemyWork_local->klass + v9))->_1.byval_arg.data + *(s32 *)((char *)&pObj->klass + v11));
  --*(u32 *)(v12 + 20);
}

// 0x1b70530
static void MemFree_NotFreeBase_1(TYPE_ENEMYOBJ *pObj) {
  TYPE_ENEMYWORK *gEnemyWork_local;
  dds3Basic_t *m_hMdl_Basic;

  gEnemyWork_local = gEnemyWork;
  if (!pObj->m_CopyMdl)
    goto LABEL_16;
  m_hMdl_Basic = pObj->m_hMdl_Basic;
  if (!m_hMdl_Basic)
    goto LABEL_16;
  dds3SceneBasicDelete(m_hMdl_Basic);
  pObj->m_hMdl_Basic = 0;
  pObj->m_hMdl_Model = 0;
LABEL_16:
  pObj->m_hMdl_Basic = 0;
  pObj->m_hMdl_Model = 0;
  *(u16 *)&pObj->m_AkirameSwitchOn = 0;
  pObj->m_Use = 0;
  *(u16 *)&pObj->m_Trap3 = 0;
  *(u64 *)&pObj->m_Mot = 0xFFFFFFFF00000000LL;
  *(u64 *)&pObj->m_MotSpd = 0x404000003F000000LL;
  --gEnemyWork_local->m_SummonNum;
}

// 0x1b72500
static bool Damage_Check(TYPE_ENEMYOBJ *pObj) {
  return pObj->m_FAtk;
}

// 0x1b72510
static s32 Get_RexIdx(s32 _EnemyID) {
  TYPE_ENEMYRES *m_Res_Devil;
  TYPE_ENEMYRES *v5;
  TYPE_ENEMYRES *v7;
  TYPE_ENEMYRES *v8;
  TYPE_ENEMYRES *v9;
  TYPE_ENEMYRES *v10;
  TYPE_ENEMYRES *v11;
  TYPE_ENEMYRES *v12;
  TYPE_ENEMYRES *v13;
  TYPE_ENEMYRES *v14;
  TYPE_ENEMYRES *v15;
  TYPE_ENEMYRES *v16;
  TYPE_ENEMYRES *v17;
  TYPE_ENEMYRES *v18;
  TYPE_ENEMYRES *v19;
  TYPE_ENEMYRES *v20;
  TYPE_ENEMYRES *v21;

  m_Res_Devil = gEnemyWork->m_Res_Devil;
  v5 = m_Res_Devil[0];
  if (v5->m_hEnemy_Res != -1 && v5->m_EnemyId == EnemyID)
    return 0;
  v7 = m_Res_Devil[1];
  if (v7->m_hEnemy_Res != -1 && v7->m_EnemyId == EnemyID)
    return 1;
  v8 = m_Res_Devil[2];
  if (v8->m_hEnemy_Res != -1 && v8->m_EnemyId == EnemyID)
    return 2;
  v9 = m_Res_Devil[3];
  if (v9->m_hEnemy_Res != -1 && v9->m_EnemyId == EnemyID)
    return 3;
  v10 = m_Res_Devil[4];
  if (v10->m_hEnemy_Res != -1 && v10->m_EnemyId == EnemyID)
    return 4;
  v11 = m_Res_Devil[5];
  if (v11->m_hEnemy_Res != -1 && v11->m_EnemyId == EnemyID)
    return 5;
  v12 = m_Res_Devil[6];
  if (v12->m_hEnemy_Res != -1 && v12->m_EnemyId == EnemyID)
    return 6;
  v13 = m_Res_Devil[7];
  if (v13->m_hEnemy_Res != -1 && v13->m_EnemyId == EnemyID)
    return 7;
  v14 = m_Res_Devil[8];
  if (v14->m_hEnemy_Res != -1 && v14->m_EnemyId == EnemyID)
    return 8;
  v15 = m_Res_Devil[9];
  if (v15->m_hEnemy_Res != -1 && v15->m_EnemyId == EnemyID)
    return 9;
  v16 = m_Res_Devil[10];
  if (v16->m_hEnemy_Res != -1 && v16->m_EnemyId == EnemyID)
    return 10;
  v17 = m_Res_Devil[11];
  if (v17->m_hEnemy_Res != -1 && v17->m_EnemyId == EnemyID)
    return 11;
  v18 = m_Res_Devil[12];
  if (v18->m_hEnemy_Res != -1 && v18->m_EnemyId == EnemyID)
    return 12;
  v19 = m_Res_Devil[13];
  if (v19->m_hEnemy_Res != -1 && v19->m_EnemyId == EnemyID)
    return 13;
  v20 = m_Res_Devil[14];
  if (v20->m_hEnemy_Res != -1 && v20->m_EnemyId == EnemyID)
    return 14;
  v21 = m_Res_Devil[15];
  if (v21->m_hEnemy_Res == -1 || v21->m_EnemyId != EnemyID)
    return -1;
  else
    return 15;
}

// 0x1b72880
static bool Load_MotionSe(TYPE_ENEMYOBJ *pObj) {
  s32 m_EnemyId;
  u32 DevilSE;
  s32 RexIdx;
  TYPE_ENEMYRES *v9;
  s32 v10;

  if (!pObj->m_Res_Type)
    return 1;
  m_EnemyId = pObj->m_EnemyId;
  DevilSE = GetDevilSE(m_EnemyId, -1);
  RexIdx = Get_RexIdx(m_EnemyId);
  if (RexIdx == -1)
    return 1;
  v9 = gEnemyWork->m_Res_Devil[RexIdx];
  v10 = p2sdLoadCheckMidi(DevilSE);
  if (v10 == 2)
    return 0;
  if (v10 == 1)
  {
    if (!sBtlLoadDevilSE_English(DevilSE + 0x10000000))
      return 0;
    return 1;
  }
  if (v10)
    return 0;
  v9->m_SmgLoad = 1;
  p2sdLoadSMGFile(DevilSE);
  return 0;
}

// 0x1b72a50
static bool Free_MotionSe(TYPE_ENEMYOBJ *pObj) {
  s32 m_EnemyId;
  u32 DevilSE;
  s32 RexIdx;
  TYPE_ENEMYRES *v9;
  s32 v10;

  if (!pObj->m_Res_Type)
    return 1;
  m_EnemyId = pObj->m_EnemyId;
  DevilSE = GetDevilSE(m_EnemyId, -1);
  RexIdx = Get_RexIdx(m_EnemyId);
  if (RexIdx == -1)
    return 1;
  v9 = gEnemyWork->m_Res_Devil[RexIdx];
  if (!v9->m_SmgLoad)
    return 1;
  v10 = p2sdLoadCheckMidi(DevilSE);
  if (v10 != 1)
    return !v10;
  p2sdUnLoadSMGFile(DevilSE, 1);
  p2sdUnLoadSMGFile(DevilSE + 0x10000000, 1);
  v9->m_SmgLoad = 0;
  return 1;
}

// 0x1b6e230
bool mapFree_MotionSe_All(void) {
  TYPE_ENEMYWORK *gEnemyWork_local;
  s64 v4;
  TYPE_ENEMYOBJ *v5;

  gEnemyWork_local = gEnemyWork;
  if (!gEnemyWork_local)
    return 1;
  gEnemyWork_local = gEnemyWork;
  v4 = 32;
  while (1)
  {
    v5 = *(TYPE_ENEMYOBJ *)((char *)&gEnemyWork_local->m_Obj->obj.klass + v4);
    if (v5->m_Use)
    {
      if (!Free_MotionSe(v5))
        break;
    }
    v4 += 8;
    if (v4 == 352)
      return 1;
  }
  return 0;
}

// 0x1b72c00
static void EnemySe(TYPE_ENEMYOBJ *pObj, s32 seid) {
  s32 m_EnemyId;
  f32 x;
  f32 y;
  f32 z;
  s32 v9;
  u32 DevilSE;
  s32 v11;
  u32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  sdfVector4_t v16;
  sdfVector4_t v17;

  m_EnemyId = pObj->m_EnemyId;
  switch (seid)
  {
    case 0:
      x = pObj->m_Pos.x;
      y = pObj->m_Pos.y;
      z = pObj->m_Pos.z;
      v9 = 65561;
      goto LABEL_24;
    case 1:
      DevilSE = GetDevilSE(m_EnemyId, 13);
      p2sdLoadCheckMidi(DevilSE);
      x = pObj->m_Pos.x;
      y = pObj->m_Pos.y;
      z = pObj->m_Pos.z;
      v16.w = 0.0;
      v9 = DevilSE;
      v11 = 48;
      goto LABEL_26;
    case 2:
      v12 = GetDevilSE(m_EnemyId, 6);
      p2sdLoadCheckMidi(v12);
      x = pObj->m_Pos.x;
      y = pObj->m_Pos.y;
      z = pObj->m_Pos.z;
      v16.w = 0.0;
      v9 = v12;
      goto LABEL_25;
    case 3:
      x = pObj->m_Pos.x;
      y = pObj->m_Pos.y;
      z = pObj->m_Pos.z;
      v9 = 65564;
LABEL_24:
      v16.w = 0.0;
LABEL_25:
      v11 = 64;
LABEL_26:
      v16.x = x;
      v16.y = y;
      v16.z = z;
      fldSePlay3DSE_BaseVol(v9, v11, v16);
      break;
    case 8:
      v13 = pObj->m_Pos.x;
      v14 = pObj->m_Pos.y;
      v15 = pObj->m_Pos.z;
      v17.x = v13;
      v17.y = v14;
      v17.w = 0.0;
      v17.z = v15;
      fldSePlay3DSE_DeadVoice(m_EnemyId, 80, v17);
      break;
    default:
      return;
  }
}

// 0x1b72e70
static TYPE_ENEMYOBJ *Get_OikakeEnemy(void) {
  s64 v2;
  TYPE_ENEMYOBJ *m_Obj;
  TYPE_ENEMYOBJ *result;
  u32 m_AiStep;
  bool v6;
  s32 v7;

  v2 = 32;
  m_Obj = gEnemyWork->m_Obj;
  while (1)
  {
    result = *(TYPE_ENEMYOBJ *)((char *)&m_Obj->obj.klass + v2);
    if (result->m_Use)
    {
      m_AiStep = result->m_AiStep;
      v6 = m_AiStep > 0x10;
      v7 = (1 << m_AiStep) & 0x1C300;
      if (!v6 && v7 != 0)
        break;
    }
    v2 += 8;
    if (v2 == 352)
      return 0;
  }
  return result;
}

// 0x1b72f30
static bool Set_NearPoint_2(TYPE_ENEMYOBJ *pObj) {
  TYPE_ENEMYWORK *gEnemyWork_local;
  f32 v7;
  f32 playerX;
  f32 playerY;
  f32 playerZ;
  s32 m_Trap1WarpCnt;
  s32 v13;
  f32 v14;
  f32 v15;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  s32 v22;
  f32 PosToDir;
  sdfVector3_t *p_m_Pos;
  f32 x;
  f32 v27;
  f32 v28;
  f32 v29;
  f32 v31;
  f32 y;
  f32 z;
  sdfVector3_t retpos;
  f32 ToX;
  f32 v38;
  f32 v39;
  sdfVector3_t v40;
  sdfVector3_t v41;
  sdfVector3_t v42;
  sdfVector3_t v43;

  *(u64 *)&retpos.x = 0;
  retpos.z = 0.0;
  gEnemyWork_local = gEnemyWork;
  v7 = 0.0;
  playerX = fldGb->playerX;
  playerY = fldGb->playerY;
  playerZ = fldGb->playerZ;
  m_Trap1WarpCnt = gEnemyWork_local->m_Trap1WarpCnt;
  ToX = playerX;
  v38 = playerY;
  v39 = playerZ;
  if (m_Trap1WarpCnt < 1)
    goto LABEL_14;
  if ((m_Trap1WarpCnt & 1) != 0)
  {
    if (m_Trap1WarpCnt + 1 >= 0)
      v13 = m_Trap1WarpCnt + 1;
    else
      v13 = m_Trap1WarpCnt + 2;
    v7 = (f32)((f32)(v13 >> 1) * 35.0) + 0.0;
  }
  if ((u32)m_Trap1WarpCnt > 0xC)
    v14 = 250.0;
  else
LABEL_14:
    v14 = 560.0;
  v15 = v14 + (f32)(u32)sub_1905740(50, 0);
  sBtlGetMoveXZ(playerX, playerZ, v7, v15, &ToX, &v39);
  v18 = ToX;
  v17 = v38;
  v19 = v39;
  ++gEnemyWork_local->m_Trap1WarpCnt;
  v20 = v17 + 35.0;
  v21 = playerY + 35.0;
  v40.x = playerX;
  v40.y = v21;
  v40.z = playerZ;
  v42.x = v18;
  v42.y = v20;
  v42.z = v19;
  v22 = mapCollision_PosToPosHitChk(v40, v42);
  if (v22 == -1)
  {
    PosToDir = sBtlGetPosToDir(v18, v19, playerX, playerZ);
    x = pObj->m_Pos.x;
    p_m_Pos = &pObj->m_Pos;
    v27 = x;
    v28 = ToX;
    v29 = v38 + -5.0;
    v31 = v39;
    p_m_Pos[1].x = PosToDir;
    y = p_m_Pos->y;
    z = p_m_Pos->z;
    v38 = v29;
    v41.x = v27;
    v41.y = y;
    v41.z = z;
    v43.x = v28;
    v43.y = v29;
    v43.z = v31;
    mapCollisionHitChk2(v41, v43, &retpos, 0);
    *p_m_Pos = retpos;
  }
  return v22 == -1;
}

// 0x1b735b0
static bool Set_NearPoint(TYPE_ENEMYOBJ *pObj) {
  TYPE_ENEMYWORK *gEnemyWork_local;
  u32 v7;
  bool v8;
  f32 playerX;
  f32 playerY;
  f32 playerZ;
  s32 m_Trap1WarpCnt;
  bool v14;
  s32 v15;
  s32 v16;
  f32 v17;
  f32 v18;
  s32 v19;
  s32 v20;
  f32 v21;
  f32 v22;
  u32 v23;
  f32 v24;
  f32 v25;
  f32 v27;
  f32 v28;
  f32 v29;
  f32 v32;
  f32 v33;
  f32 v34;
  f32 ToX;
  f32 v38;
  f32 v39;
  sdfVector3_t v40;
  sdfVector3_t v41;

  gEnemyWork_local = gEnemyWork;
  v7 = 0;
  v8 = 1;
  playerX = fldGb->playerX;
  playerY = fldGb->playerY;
  playerZ = fldGb->playerZ;
  while (1)
  {
    ToX = playerX;
    v38 = playerY;
    v39 = playerZ;
    m_Trap1WarpCnt = gEnemyWork_local->m_Trap1WarpCnt;
    v14 = m_Trap1WarpCnt < 1;
    if (g_GenLenType)
    {
      if (v14)
      {
        v18 = 0.0;
LABEL_29:
        v22 = 900.0;
        goto LABEL_33;
      }
      if (m_Trap1WarpCnt + 1 >= 0)
        v15 = m_Trap1WarpCnt + 1;
      else
        v15 = m_Trap1WarpCnt + 2;
      v16 = v15 >> 1;
      v17 = -(f32)((f32)v16 * 25.0);
      if ((m_Trap1WarpCnt & 1) == 0)
        v17 = (f32)v16 * 25.0;
      v18 = v17 + 0.0;
      if ((u32)m_Trap1WarpCnt <= 0xC)
        goto LABEL_29;
      *(f32 *)&v19 = 500.0;
      goto LABEL_32;
    }
    if (v14)
    {
      v18 = 0.0;
LABEL_31:
      *(f32 *)&v19 = 560.0;
      goto LABEL_32;
    }
    if (m_Trap1WarpCnt + 1 >= 0)
      v20 = m_Trap1WarpCnt + 1;
    else
      v20 = m_Trap1WarpCnt + 2;
    if ((m_Trap1WarpCnt & 1) != 0)
      v21 = -(f32)((f32)(v20 >> 1) * 35.0);
    else
      v21 = (f32)(v20 >> 1) * 35.0;
    v18 = v21 + 0.0;
    if ((u32)m_Trap1WarpCnt <= 0xC)
      goto LABEL_31;
    *(f32 *)&v19 = 250.0;
LABEL_32:
    v22 = *(f32 *)&v19;
LABEL_33:
    v23 = sub_1905740(50, 0);
    v24 = ToX;
    v25 = v39;
    sBtlGetMoveXZ(v24, v25, v18, v22 + (f32)v23, &ToX, &v39);
    v27 = ToX;
    v28 = v38;
    v29 = v39;
    ++gEnemyWork_local->m_Trap1WarpCnt;
    v40.y = playerY + 35.0;
    v40.z = playerZ;
    v41.x = v27;
    v41.z = v29;
    v41.y = v28 + 35.0;
    v40.x = playerX;
    if (mapCollision_PosToPosHitChk(v40, v41) == -1)
      break;
    v8 = v7++ < 3;
    if (v7 == 4)
      return v8;
  }
  v38 = v38 + -5.0;
  v32 = ToX;
  v33 = v39;
  v34 = mapGetY(v32, v33);
  v38 = v34;
  pObj->m_Pos.x = ToX;
  pObj->m_Pos.y = v34;
  pObj->m_Pos.z = v39;
  pObj->m_Dir = sBtlGetPosToDir(v27, v29, playerX, playerZ);
  return v8;
}

// 0x1b739e0
static void AI_Update(void) {
  fld **v3;
  TYPE_ENEMYWORK *gEnemyWork_local;
  f32 playerY;
  f32 playerX;
  f32 playerZ;
  s32 g_EnemySummonMax_local;
  s32 v18;
  s32 m_StopSummonWaitCnt;
  s32 v20;
  f32 v21;
  s32 m_StopNoDiscoCnt;
  s32 v23;
  s32 v24;
  s64 v25;
  TYPE_ENEMYRES **p_m_Res_Devil;
  s64 v27;
  TYPE_ENEMYOBJ *v28;
  u64 v30;
  s32 v31;
  f32 v32;
  f32 v33;
  f32 v34;
  fld *v36;
  s32 m_PopTableIdx;
  sdfVector3_t *v42;
  u64 v43;
  f32 v44;
  s32 v45;
  f32 v46;
  f32 v47;
  f32 v48;
  u64 v49;
  f32 v50;
  s32 m_Run_Stamina;
  s32 v56;
  s32 v63;
  s32 v64;
  _BOOL4 m_Dead;
  s32 v66;
  u64 v68;
  s32 v69;
  s32 m_QuakePow;
  f32 v71;
  f32 v72;
  s32 v73;
  u64 v74;
  f32 v75;
  dds3Basic_t *m_hMdl_Basic;
  f32 m_EnemyScale;
  f32 v78;
  f32 v79;
  f32 v80;
  f32 v81;
  f32 v82;
  f32 v83;
  s32 v87;
  u32 v88;
  s32 *p_m_Res_Devil_Idx;
  TYPE_ENEMYRES **p_m_Res_Avatar;
  TYPE_ENEMYRES *v91;
  f32 v92;
  s32 v93;
  u32 v95;
  s32 *v96;
  TYPE_ENEMYRES **v97;
  TYPE_ENEMYRES *v99;
  fld *v100;
  f32 v101;
  f32 v102;
  f32 v103;
  u64 v104;
  s32 v105;
  s32 v106;
  u32 v108;
  s32 *v109;
  TYPE_ENEMYRES **v110;
  TYPE_ENEMYRES *v111;
  u64 v112;
  float32x2_t *v113;
  s32 v114;
  f32 m_ETrap3_MoveTime;
  s32 v116;
  s32 v117;
  s32 v118;
  u32 v120;
  s32 *v121;
  TYPE_ENEMYRES **v122;
  TYPE_ENEMYRES *v124;
  fld *v125;
  f32 v126;
  f32 v127;
  f32 v128;
  u64 v129;
  s32 v130;
  f32 v131;
  f32 v132;
  f32 v133;
  f32 m_ETrap3_MoveHigh;
  f32 v135;
  f32 v136;
  s32 v137;
  f32 v138;
  f32 m_ETrap3_GDir;
  f32 v140;
  f32 v141;
  f32 v142;
  u64 v143;
  f32 v144;
  f32 v145;
  f32 v146;
  s32 v147;
  s32 v148;
  s32 v149;
  f32 v150;
  f32 v151;
  f32 v152;
  fld *v153;
  f32 v155;
  s32 v156;
  float32x2_t v157;
  u64 v159;
  f32 v160;
  f32 v161;
  u64 v162;
  f32 v163;
  f32 LenXYZ_33399936;
  f32 v165;
  s32 m_AiParam;
  f32 m_Range_Disco;
  u64 v169;
  f32 v170;
  s64 v172;
  f32 v173;
  u64 v174;
  f32 v175;
  f32 v177;
  f32 v178;
  f32 v179;
  f32 v180;
  f32 v181;
  f32 v182;
  f32 v184;
  f32 v186;
  u64 v187;
  f32 v188;
  sdfVector3_t *p_m_UroUroPos;
  f32 v190;
  f32 v191;
  u64 v193;
  f32 v194;
  f32 v195;
  u32 v196;
  s64 v197;
  f32 v198;
  f32 v200;
  f32 v201;
  f32 v202;
  f32 v203;
  f32 v204;
  u64 v206;
  f32 v207;
  f32 v208;
  u32 v209;
  s64 v210;
  f32 v211;
  f32 v212;
  f32 v213;
  f32 v214;
  f32 v215;
  f32 v216;
  u64 v218;
  f32 v219;
  f32 v220;
  u32 v221;
  s64 v222;
  f32 v223;
  fld *v224;
  u64 *p_m_Pos;
  u64 v227;
  f32 v228;
  f32 v229;
  f32 v230;
  f32 v231;
  f32 AtoB_LR;
  s32 v233;
  f32 v234;
  s32 v236;
  TYPE_ENEMYRES **v237;
  s32 m_Res_Avatar_Idx;
  s32 v240;
  fld **v241;
  u64 v242;
  f32 v243;
  u64 v244;
  f32 v245;
  s32 v246;
  f32 v248;
  f32 v249;
  f32 v250;
  f32 v251;
  f32 v252;
  _BOOL4 m_Icon3D;
  s32 v254;
  s32 v255;
  fld *v256;
  f32 v257;
  f32 v258;
  f32 v259;
  f32 v260;
  u64 v261;
  f32 v262;
  _BOOL4 v263;
  f32 v264;
  f32 v265;
  f32 v266;
  s32 v267;
  f32 v268;
  f32 v269;
  f32 v270;
  f32 v271;
  u64 v272;
  s32 m_Intercept_Stamina;
  u64 v274;
  _BOOL4 v275;
  f32 v276;
  f32 v277;
  f32 v278;
  s32 v279;
  f32 v280;
  f32 v281;
  f32 v282;
  u64 v283;
  f32 v284;
  s64 v285;
  u64 v286;
  f32 v287;
  s32 m_Run_AiCnt;
  f32 v289;
  s32 v290;
  s32 v291;
  f32 v292;
  u32 v293;
  u64 v294;
  f32 v295;
  s64 v297;
  f32 v298;
  u64 v299;
  f32 v300;
  f32 v301;
  f32 v302;
  f32 v303;
  u32 v304;
  s64 v305;
  f32 v306;
  f32 v307;
  f32 m_DitherAlpha;
  f32 v309;
  u64 v310;
  s32 v311;
  s64 v312;
  fld *v313;
  f32 v314;
  f32 v315;
  f32 v316;
  dds3ModelHandle_t *m_hMdl_Model;
  s32 v319;
  s32 v320;
  u64 v321;
  u64 v323;
  f32 v324;
  f32 v325;
  s64 v326;
  s32 v329;
  s64 v330;
  f32 m_Run_Spd;
  f32 m_Run_MaxSpd;
  u64 v333;
  f32 v334;
  f32 v335;
  s32 m_ObjIdx;
  f32 v338;
  f32 v339;
  f32 v340;
  u64 v341;
  f32 v342;
  int32x2_t v343;
  f32 v344;
  f32 v345;
  float32x2_t v346;
  float32x2_t v347;
  f32 v348;
  f32 VecToDir;
  f32 Dir_Hokan;
  u64 v352;
  f32 v353;
  f32 ABS;
  f32 v356;
  f32 v357;
  f32 v358;
  f32 v359;
  f32 v360;
  f32 v361;
  f32 v362;
  f32 v363;
  f32 v364;
  u64 v365;
  f32 v366;
  f32 v367;
  f32 v368;
  s32 v369;
  s32 v370;
  f32 v371;
  s32 v372;
  fld **v373;
  f32 v374;
  f32 v375;
  f32 v376;
  u64 v377;
  f32 v378;
  f32 v379;
  f32 v380;
  f32 v381;
  s64 v382;
  int32x2_t v383;
  float32x2_t *v384;
  f32 v385;
  f32 v386;
  f32 v387;
  s32 v388;
  s32 v389;
  fld **v390;
  f32 m_Intercept_Spd;
  f32 m_Intercept_MaxSpd;
  f32 v393;
  f32 v394;
  f32 v395;
  f32 v396;
  f32 v397;
  u64 v398;
  f32 v399;
  s32 v400;
  s32 v401;
  f32 v402;
  f32 v403;
  f32 v404;
  f32 v405;
  u64 v406;
  f32 v407;
  f32 v408;
  f32 v409;
  f32 v410;
  f32 v411;
  f32 v412;
  f32 v413;
  f32 v414;
  f32 v415;
  f32 m_Intercept_Dir;
  f32 v417;
  f32 v418;
  f32 v419;
  f32 v420;
  f32 v421;
  f32 v422;
  u64 v423;
  f32 v424;
  f32 v425;
  f32 v426;
  f32 v427;
  f32 v428;
  f32 v429;
  f32 v430;
  s64 v431;
  f32 v432;
  f32 v433;
  f32 v434;
  s32 v437;
  u32 v438;
  s32 *p_m_Res_Avatar_Idx;
  TYPE_ENEMYRES **v440;
  TYPE_ENEMYRES *v441;
  f32 v442;
  f32 m_Rush_Dir;
  f32 v444;
  u64 v445;
  f32 v446;
  f32 v447;
  f32 v449;
  f32 v450;
  u32 v451;
  f32 v452;
  f32 v453;
  f32 v454;
  f32 v455;
  f32 v457;
  f32 v458;
  f32 v459;
  f32 v460;
  f32 v461;
  f32 v462;
  s32 v463;
  f32 v465;
  f32 v466;
  f32 v467;
  s32 v468;
  s64 v469;
  TYPE_ENEMYSYMBOLTABLE *v470;
  s32 v471;
  TYPE_ENEMYSYMBOLTABLE *v474;
  s32 m_Par_Run;
  _BOOL4 v476;
  f32 m_Spd_Run;
  f32 v478;
  _BOOL4 v479;
  s32 m_Spd_Intercept;
  f32 v481;
  f32 m_Dir;
  f32 v483;
  f32 v484;
  f32 v485;
  u64 v486;
  f32 v487;
  f32 v488;
  f32 v489;
  f32 v490;
  s64 v491;
  int32x2_t v492;
  float32x2_t *v493;
  f32 v494;
  f32 v495;
  f32 v496;
  u64 v497;
  f32 v498;
  f32 v499;
  f32 v500;
  f32 v501;
  f32 v502;
  u64 v503;
  f32 v504;
  f32 v505;
  f32 v506;
  f32 v507;
  f32 v508;
  f32 v509;
  f32 v510;
  f32 v511;
  f32 v512;
  f32 v513;
  f32 v514;
  f32 v515;
  f32 v516;
  f32 v517;
  f32 AtoB_LR_ABS;
  f32 v519;
  f32 v520;
  f32 v521;
  f32 v522;
  f32 v523;
  u64 v524;
  f32 v525;
  f32 v526;
  f32 v527;
  f32 v528;
  f32 v529;
  f32 v530;
  s64 v531;
  f32 v532;
  f32 v533;
  f32 v534;
  u64 v535;
  f32 v536;
  f32 v537;
  f32 v538;
  float32x2_t v540;
  f32 v541;
  f32 v542;
  f32 v543;
  f32 v544;
  u32 v545;
  s32 v546;
  f32 v547;
  f32 v548;
  f32 v549;
  fld *v550;
  _BOOL4 m_Trap1;
  s32 m_Spd_Rush;
  f32 v553;
  s32 v555;
  TYPE_ENEMYRES **v557;
  s32 v558;
  fld **v559;
  s32 m_AiCnt;
  s32 v561;
  s32 v562;
  fld *v563;
  s32 v564;
  s32 v565;
  u64 v567;
  f32 v568;
  f32 v570;
  s64 v571;
  f32 v572;
  u64 v573;
  s32 v574;
  s32 v575;
  TYPE_ENEMYOBJ *v577;
  f32 v579;
  f32 v580;
  f32 v581;
  u64 v582;
  f32 v583;
  f32 v584;
  f32 v585;
  f32 v586;
  f32 v587;
  f32 v588;
  f32 v589;
  f32 v591;
  u64 v592;
  u32 v593;
  f32 v594;
  f32 v595;
  s32 m_KabeCnt;
  f32 v598;
  f32 m_RunAccel;
  f32 v600;
  u64 v601;
  f32 v602;
  f32 v603;
  f32 v604;
  f32 v605;
  f32 v606;
  f32 v608;
  u64 v609;
  u32 v610;
  f32 v611;
  f32 v612;
  s32 v613;
  s32 v614;
  f32 v615;
  s32 v616;
  s32 m_Res_Type;
  s32 m_EnemyId;
  TYPE_ENEMYRES *v619;
  float32x2_t v621;
  f32 v622;
  f32 v623;
  f32 v624;
  f32 v625;
  u32 v626;
  s32 v627;
  f32 v628;
  f32 v629;
  f32 v630;
  fld *v631;
  f32 v633;
  f32 m_InterceptAccel;
  f32 v635;
  f32 v636;
  f32 v637;
  f32 m_PlayerDir;
  f32 v639;
  f32 v640;
  f32 v642;
  f32 v643;
  f32 v644;
  f32 v645;
  f32 v646;
  f32 v647;
  f32 v648;
  f32 v650;
  f32 v651;
  u64 v653;
  f32 v654;
  sdfVector3_t *p_m_Intercept_ContactPos;
  TYPE_ENEMYWORK *v656;
  f32 v657;
  s64 v658;
  u64 v659;
  u32 v660;
  f32 v661;
  f32 v662;
  f32 v663;
  f32 v664;
  f32 m_Intercept_Range;
  TYPE_ENEMYWORK *v666;
  f32 v667;
  f32 v668;
  s64 v670;
  u64 v671;
  u32 v672;
  f32 v673;
  f32 v674;
  f32 v675;
  f32 v676;
  s32 v677;
  f32 v679;
  f32 v680;
  f32 v681;
  f32 v682;
  f32 PosToDir;
  f32 v684;
  f32 v685;
  f32 v686;
  f32 v688;
  f32 v689;
  f32 v690;
  u32 v691;
  f32 v693;
  f32 v694;
  f32 v695;
  f32 v696;
  f32 v697;
  f32 v698;
  f32 v699;
  f32 v700;
  f32 v701;
  f32 v703;
  f32 v704;
  f32 v705;
  f32 v706;
  f32 v707;
  f32 v708;
  f32 v709;
  f32 v710;
  f32 v711;
  f32 v713;
  u64 v714;
  u32 v715;
  s64 v716;
  f32 v717;
  f32 v718;
  f32 v719;
  f32 v720;
  s32 v721;
  TYPE_ENEMYOBJ *OikakeEnemy;
  f32 x;
  f32 y;
  f32 z;
  f32 v727;
  f32 v728;
  f32 v729;
  f32 v730;
  f32 v731;
  f32 v732;
  f32 v733;
  u64 v734;
  u64 v735;
  f32 v736;
  f32 v737;
  f32 v738;
  f32 v739;
  f32 v740;
  f32 v741;
  f32 v742;
  f32 v743;
  f32 v744;
  f32 v745;
  f32 v746;
  s32 v747;
  f32 v748;
  f32 v750;
  f32 v751;
  f32 v752;
  f32 v753;
  s64 v755;
  f32 v756;
  u64 v758;
  f32 v759;
  s64 v761;
  f32 v762;
  u32 v763;
  f32 v764;
  f32 v765;
  f32 v766;
  f32 v768;
  f32 v769;
  f32 v770;
  f32 v771;
  s64 v773;
  f32 v774;
  u64 v776;
  f32 v777;
  s64 v779;
  f32 v780;
  s64 i;
  float32x2_t *v782;
  u64 v783;
  f32 v784;
  s64 v785;
  s32 v786;
  s32 v787;
  f32 ToXYZ;
  f32 ToXYZa;
  s32 ToXYZc;
  TYPE_ENEMYRES **v792;
  TYPE_ENEMYRES **v793;
  f32 v794;
  f32 v795;
  f32 frompos;
  s32 v797;
  f32 v798;
  sdfVector3_t *p_m_PlayerPos;
  float32x2_t FromXYZ;
  float32x2_t FromXYZa;
  u64 FromXYZd;
  float32x2_t FromXYZe;
  s64 FromXYZb;
  s32 FromXYZf;
  s32 FromXYZc;
  s32 FromXYZg;
  s32 FromXYZh;
  f32 v813;
  f32 v814;
  f32 v815;
  sdfVector3_t retpos;
  sdfVector3_t v817;
  sdfVector3_t v818;
  u64 v819;
  f32 v820;
  float32x2_t ToX;
  f32 v822[4];
  sdfVector3_t v823;
  sdfVector3_t v824;
  sdfVector3_t v825;
  sdfVector3_t v826;
  sdfVector3_t v827;
  sdfVector3_t v828;
  sdfVector3_t v829;
  sdfVector3_t v830;
  sdfVector3_t v831;
  sdfVector3_t v832;
  sdfVector3_t v833;
  sdfVector3_t v834;
  sdfVector3_t v835;
  sdfVector3_t v836;
  sdfVector3_t v837;
  sdfVector3_t v838;
  sdfVector3_t v839;
  sdfVector3_t v840;
  sdfVector3_t v841;
  sdfVector3_t v842;
  sdfVector3_t v843;
  sdfVector3_t v844;
  sdfVector3_t v845;
  sdfVector3_t v846;
  sdfVector3_t v847;
  sdfVector3_t v848;
  sdfVector3_t v849;
  sdfVector3_t v850;
  sdfVector3_t v851;
  sdfVector3_t v852;
  sdfVector3_t v853;
  sdfVector3_t v854;
  sdfVector3_t v855;
  sdfVector3_t v856;
  sdfVector3_t v857;
  sdfVector3_t v858;
  sdfVector3_t v859;
  sdfVector3_t v860;
  sdfVector3_t v861;
  sdfVector3_t v862;
  sdfVector3_t v863;
  sdfVector3_t v864;
  sdfVector3_t v865;
  sdfVector3_t v866;
  sdfVector3_t v867;
  sdfVector3_t v868;
  sdfVector3_t v869;
  sdfVector3_t v870;
  sdfVector3_t v871;
  sdfVector3_t v872;
  sdfVector3_t v873;
  sdfVector3_t v874;
  sdfVector3_t v875;
  sdfVector3_t v876;
  sdfVector3_t v877;
  sdfVector3_t v878;
  sdfVector3_t v879;
  sdfVector3_t v880;
  sdfVector3_t v881;
  sdfVector3_t v882;
  sdfVector3_t v883;
  sdfVector3_t v884;
  sdfVector3_t v885;
  sdfVector3_t v886;
  sdfVector3_t v887;
  sdfVector3_t v888;
  sdfVector3_t v889;
  sdfVector3_t v890;
  sdfVector3_t v891;
  sdfVector3_t v892;
  sdfVector3_t v893;
  sdfVector3_t v894;
  sdfVector3_t v895;
  sdfVector3_t v896;
  sdfVector3_t v897;
  sdfVector3_t v898;
  sdfVector3_t v899;
  sdfVector3_t v900;
  sdfVector3_t v901;
  sdfVector3_t v902;
  sdfVector3_t v903;
  sdfVector3_t v904;
  sdfVector3_t v905;
  sdfVector3_t v906;
  sdfVector3_t v907;
  sdfVector3_t v908;
  sdfVector3_t v909;
  sdfVector3_t v910;
  sdfVector3_t v911;
  sdfVector3_t v912;
  sdfVector3_t v913;
  sdfVector3_t v914;
  sdfVector3_t v915;
  sdfVector3_t v916;
  sdfVector3_t v917;
  sdfVector3_t v918;
  sdfVector3_t v919;
  sdfVector3_t v920;
  sdfVector3_t v921;
  sdfVector3_t v922;
  sdfVector3_t v923;
  sdfVector3_t v924;
  sdfVector3_t v925;
  sdfVector3_t v926;
  sdfVector3_t v927;
  sdfVector3_t v928;
  sdfVector3_t v929;
  sdfVector3_t v930;
  sdfVector3_t v931;
  sdfVector3_t v932;
  sdfVector3_t v933;
  sdfVector3_t v934;
  sdfVector3_t v935;
  sdfVector3_t v936;
  sdfVector3_t v937;
  sdfVector3_t v938;
  sdfVector3_t v939;
  sdfVector3_t v940;
  sdfVector3_t v941;
  sdfVector3_t v942;
  sdfVector3_t v943;
  sdfVector3_t v944;
  sdfVector3_t v945;
  sdfVector3_t v946;
  sdfVector3_t v947;
  sdfVector3_t v948;
  sdfVector3_t v949;
  sdfVector3_t v950;
  sdfVector3_t v951;
  sdfVector3_t v952;
  sdfVector3_t v953;
  sdfVector3_t v954;
  sdfVector3_t v955;
  sdfVector3_t v956;
  sdfVector3_t v957;
  sdfVector3_t v958;
  sdfVector3_t v959;
  sdfVector3_t v960;
  sdfVector3_t v961;
  sdfVector3_t v962;
  sdfVector3_t v963;
  sdfVector4_t v964;
  sdfVector4_t v965;
  sdfVector4_t v966;
  sdfVector4_t v967;
  sdfVector4_t v968;
  sdfVector4_t v969;

  v3 = &fld;
  v822[0] = 0.0;
  ToX.n64_u64[0] = 0;
  v820 = 0.0;
  v819 = 0;
  v818.z = 0.0;
  *(u64 *)&v818.x = 0;
  v817.z = 0.0;
  retpos.z = 0.0;
  *(u64 *)&v817.x = 0;
  *(u64 *)&retpos.x = 0;
  gEnemyWork_local = gEnemyWork;
  ToX.n64_u64[0] = 0;
  v822[0] = 0.0;
  v819 = 0;
  v820 = 0.0;
  *(u64 *)&v818.x = 0;
  v818.z = 0.0;
  playerX = fldGb->playerX;
  playerY = fldGb->playerY;
  playerZ = fldGb->playerZ;
  g_EnemySummonMax_local = g_EnemySummonMax;
  LODWORD(fldGb) = gEnemyWork_local->m_OikakeSwitchCnt;
  _VF = __OFSUB__((u32)fldGb, 1);
  v18 = (u32)fldGb - 1;
  if (v18 < 0 == _VF)
    gEnemyWork_local->m_OikakeSwitchCnt = v18;
  m_StopSummonWaitCnt = gEnemyWork_local->m_StopSummonWaitCnt;
  _VF = __OFSUB__(m_StopSummonWaitCnt, 1);
  v20 = m_StopSummonWaitCnt - 1;
  if (v20 < 0 == _VF)
    gEnemyWork_local->m_StopSummonWaitCnt = v20;
  v21 = g_EnemySymbol_Mid_CountPar;
  m_StopNoDiscoCnt = gEnemyWork_local->m_StopNoDiscoCnt;
  _VF = __OFSUB__(m_StopNoDiscoCnt, 1);
  v23 = m_StopNoDiscoCnt - 1;
  if (v23 < 0 == _VF)
    gEnemyWork_local->m_StopNoDiscoCnt = v23;
  p_m_PlayerPos = &gEnemyWork_local->m_PlayerPos;
  if (g_EnemySummonMax_local >= 0)
    v24 = g_EnemySummonMax_local;
  else
    v24 = g_EnemySummonMax_local + 1;
  v25 = 0;
  v797 = v24 >> 1;
  p_m_Res_Devil = &gEnemyWork_local->m_Res_Devil;
  v815 = playerY;
  v795 = g_EnemySymbol_High_ClipLen;
  frompos = playerY + 25.0;
  v794 = 100.0 - v21;
  v798 = -g_EnemySymbol_High_ClipLen;
  v813 = playerX;
  v814 = playerY + 35.0;
  while (1)
  {
    v28 = gEnemyWork_local->m_Obj[v25];
    if (v28->m_Use)
      break;
LABEL_21:
    if (++v25 == 40)
    {
      for (i = 32; i != 352; i += 8)
      {
        v782 = *(float32x2_t **)((char *)&gEnemyWork_local->m_Obj->obj.klass + i);
        if (v782[2].n64_u8[0])
        {
          ToX.n64_u64[0] = v782[6].n64_u64[0];
          v783 = ToX.n64_u64[0];
          v822[0] = v782[7].n64_f32[0];
          v784 = v822[0];
          v898.x = playerX;
          v898.y = playerY;
          v898.z = playerZ;
          *(u64 *)&v963.x = v783;
          v963.z = v784;
          v782[10].n64_f32[0] = GetLenXYZ(v898, v963);
        }
      }
      return;
    }
  }
  switch (v28->m_AiStep)
  {
    case 0:
      ++v28->m_AiCnt;
      if (!gEnemyWork_local->m_StopNoDiscoCnt)
        ++v28->m_NoDiscoTime;
      ++v28->m_UroUroSE_Cnt;
      ToX.n64_u64[0] = *(u64 *)&v28->m_Pos.x;
      v822[0] = v28->m_Pos.z;
      v28->m_Mot = 1;
      v28->m_DitherAlpha = 1.0;
      *(u64 *)&v28->m_MotSpd = 0x404000003F000000LL;
      if (v28->m_FAtk)
        goto LABEL_19;
      v162 = ToX.n64_u64[0];
      v163 = v822[0];
      v831.x = playerX;
      v831.y = playerY;
      v831.z = playerZ;
      *(u64 *)&v903.x = v162;
      v903.z = v163;
      LenXYZ_33399936 = GetLenXYZ(v831, v903);
      if (v28->m_NoDiscoTime >= 1801 && LenXYZ_33399936 > 800.0)
        goto LABEL_480;
      *(u64 *)&v818.x = __PAIR64__(LODWORD(v814), LODWORD(playerX));
      v165 = ToX.n64_f32[1];
      v819 = ToX.n64_u64[0];
      v818.z = playerZ;
      v820 = v822[0];
      m_AiParam = v28->m_AiParam;
      *((f32 *)&v819 + 1) = ToX.n64_f32[1] + 35.0;
      if (m_AiParam <= 9998)
      {
        if (v28->m_Res_Type)
        {
          m_Range_Disco = 1000.0;
          if (v28->m_Trap1)
            goto LABEL_652;
        }
        else
        {
          m_Range_Disco = gMapEnemySymbolTable[v28->m_Res_Avatar_Idx]->m_Range_Disco;
          if (v28->m_Trap1)
          {
LABEL_652:
            if (gEnemyWork_local->m_OikakeNum > 0)
              goto LABEL_824;
LABEL_653:
            v555 = 0;
            if (!v28->m_ScreenIn)
              goto LABEL_824;
            goto LABEL_654;
          }
        }
      }
      else
      {
        m_Range_Disco = 600.0;
        if (v28->m_Trap1)
          goto LABEL_652;
      }
      if (gEnemyWork_local->m_OikakeSwitchCnt)
        goto LABEL_652;
      if (gEnemyWork_local->m_OikakeNum < 1)
        goto LABEL_653;
      OikakeEnemy = Get_OikakeEnemy();
      if (!OikakeEnemy || OikakeEnemy->m_Trap1)
        goto LABEL_652;
      x = OikakeEnemy->m_Pos.x;
      y = OikakeEnemy->m_Pos.y;
      z = OikakeEnemy->m_Pos.z;
      v885.x = playerX;
      v885.y = playerY;
      v885.z = playerZ;
      v950.x = x;
      v950.y = y;
      v950.z = z;
      v727 = GetLenXYZ(v885, v950);
      *(float32x2_t *)&v951.x = ToX;
      v728 = v727;
      v951.z = v822[0];
      v886.x = playerX;
      v886.y = playerY;
      v886.z = playerZ;
      v729 = GetLenXYZ(v886, v951);
      if ((f32)(v728 - v729) >= 500.0 && (v729 >= 300.0 || v728 <= 400.0))
        goto LABEL_652;
      v555 = 1;
      if (!v28->m_ScreenIn)
        goto LABEL_824;
LABEL_654:
      v557 = p_m_Res_Devil;
      v558 = g_EnemySummonMax_local;
      v559 = v3;
      m_AiCnt = v28->m_AiCnt;
      v561 = v555;
      v555 = v561;
      v562 = m_AiCnt % gMapEnemyDiffTbl[g_EnemySymbol_Diff]->m_DiscoInt;
      v3 = v559;
      g_EnemySummonMax_local = v558;
      p_m_Res_Devil = v557;
      if (!v562)
      {
        v563 = *v3;
        v564 = v555;
        v563 = *v3;
        v555 = v564;
        if (!fldGb->nakamaMode)
        {
          FromXYZc = v555;
          if (sBtlGetABS(playerY - v165) < 120.0)
          {
            v565 = sub_1905740(100, 0);
            ToXYZc = v565;
            v565 = ToXYZc;
            if (v565 < gMapEnemyDiffTbl[g_EnemySymbol_Diff]->m_DiscoPar)
            {
              v567 = ToX.n64_u64[0];
              v568 = v822[0];
              v869.x = playerX;
              v869.y = playerY;
              v869.z = playerZ;
              *(u64 *)&v936.x = v567;
              v936.z = v568;
              if (GetLenXYZ(v869, v936) < m_Range_Disco)
              {
                v570 = v818.z;
                v571 = *(u64 *)&v818.x;
                v572 = v820;
                v573 = v819;
                *(u64 *)&v870.x = v571;
                v870.z = v570;
                *(u64 *)&v937.x = v573;
                v937.z = v572;
                v574 = mapCollision_PosToPosHitChk(v870, v937);
                playerX = v813;
                playerY = v815;
                v575 = FromXYZc;
                if (v574 == -1)
                {
                  v575 = FromXYZc;
                  if (v575)
                  {
                    v577 = Get_OikakeEnemy();
                    if (v577)
                      v577->m_AkirameSwitchOn = 1;
                    gEnemyWork_local->m_OikakeSwitchCnt = 180;
                  }
                  goto LABEL_424;
                }
              }
            }
          }
        }
      }
LABEL_824:
      if (v28->m_AiParam > 9998)
        goto LABEL_837;
      if (!gEnemyWork_local->m_StopNoDiscoCnt)
      {
        v730 = v28->m_PopPos.z;
        v731 = v28->m_PopPos.x;
        v732 = v28->m_PopPos.y;
        v733 = v822[0];
        v734 = ToX.n64_u64[0];
        v887.x = v731;
        v887.y = v732;
        v887.z = v730;
        *(u64 *)&v952.x = v734;
        v952.z = v733;
        playerX = v813;
        playerY = v815;
        if (GetLenXYZ(v887, v952) > (f32)(m_Range_Disco + 900.0))
        {
          v735 = ToX.n64_u64[0];
          v736 = v822[0];
          v888.x = v813;
          v888.y = v815;
          v888.z = playerZ;
          *(u64 *)&v953.x = v735;
          v953.z = v736;
          if (GetLenXYZ(v888, v953) > 800.0)
          {
LABEL_480:
            v27 = 10;
            goto LABEL_20;
          }
        }
      }
      v737 = v28->m_Pos.x;
      v738 = v28->m_Pos.y;
      v739 = v28->m_Pos.z;
      if (sBtlChkWorldtoScreenIn(v737, v738, v739) && v28->m_AiCnt > 3 * v28->m_AiParam)
      {
        v27 = 5;
        goto LABEL_20;
      }
LABEL_837:
      if (v28->m_UroUroSE_Cnt != 180)
        goto LABEL_21;
LABEL_838:
      sub_1905740(100, 0);
      v28->m_UroUroSE_Cnt = 0;
      goto LABEL_21;
    case 1:
      v30 = *(u64 *)&v28->m_Pos.x;
      v28->m_Mot = 1;
      v818.x = playerX;
      v819 = v30;
      ToX.n64_u64[0] = v30;
      *(f32 *)&v30 = v28->m_Pos.z;
      v31 = v28->m_AiCnt + 1;
      v32 = *((f32 *)&v819 + 1);
      v33 = ToX.n64_f32[1];
      *(u64 *)&v28->m_MotSpd = 0x404000003F000000LL;
      v28->m_AiCnt = v31;
      LODWORD(v822[0]) = v30;
      v820 = *(f32 *)&v30;
      LODWORD(v30) = v28->m_Res_Type;
      *((f32 *)&v819 + 1) = v32 + 35.0;
      v818.y = v814;
      v818.z = playerZ;
      if ((u32)v30)
      {
        v34 = 1000.0;
        goto LABEL_31;
      }
      else
      {
        v34 = gMapEnemySymbolTable[v28->m_Res_Avatar_Idx]->m_Range_Disco;
LABEL_31:
        v36 = *v3;
        goto LABEL_32;
      }
      v36 = *v3;
LABEL_32:
      if (fldGb->nakamaMode)
        goto LABEL_447;
      if ((s32)sub_1905740(100, 0) <= 19)
      {
        if (sBtlGetABS(playerY - v33) < 120.0)
        {
          v169 = ToX.n64_u64[0];
          v170 = v822[0];
          v832.x = playerX;
          v832.y = playerY;
          v832.z = playerZ;
          *(u64 *)&v904.x = v169;
          v904.z = v170;
          if (GetLenXYZ(v832, v904) < v34)
          {
            v172 = *(u64 *)&v818.x;
            v173 = v818.z;
            v174 = v819;
            v175 = v820;
            *(u64 *)&v833.x = v172;
            v833.z = v173;
            *(u64 *)&v905.x = v174;
            v905.z = v175;
            playerX = v813;
            playerY = v815;
            if (mapCollision_PosToPosHitChk(v833, v905) == -1)
              goto LABEL_397;
          }
        }
      }
      goto LABEL_447;
    case 2:
      m_PopTableIdx = v28->m_PopTableIdx;
      if (!mapChkPopJKFlg(m_PopTableIdx))
        goto LABEL_21;
      if (gEnemyWork_local->m_SummonNum >= g_EnemySummonMax_local || gEnemyWork_local->m_StopSummonWaitCnt > 0)
        goto LABEL_21;
      v177 = gEnemyWork_local->m_PlayerPos.x;
      v178 = gEnemyWork_local->m_PlayerPos.y;
      v179 = gEnemyWork_local->m_PlayerPos.z;
      v180 = v28->m_Pos.x;
      v181 = v28->m_Pos.y;
      v182 = v28->m_Pos.z;
      v834.x = v177;
      v834.y = v178;
      v834.z = v179;
      v906.x = v180;
      v906.y = v181;
      v906.z = v182;
      v184 = GetLenXYZ(v834, v906);
      playerX = v813;
      playerY = v815;
      if (v184 > g_EnemySymbol_Far_ClipLen)
      {
        if (v28->m_ScreenIn && gEnemyWork_local->m_SummonNum < v797)
        {
          if ((s32)sub_1905740(100, 0) <= 29)
            goto LABEL_21;
        }
        else if ((s32)sub_1905740(100, 0) < 80)
        {
          goto LABEL_21;
        }
      }
      if (v184 > g_EnemySymbol_Mid_CountLen && !v28->m_ScreenIn && v794 > (f32)(s32)sub_1905740(99, 0))
        goto LABEL_21;
      if (v184 < g_EnemySymbol_Near_ClipLen)
        goto LABEL_21;
      v615 = gEnemyWork_local->m_PlayerPos.y - v28->m_Pos.y;
      if (v615 < v798)
        goto LABEL_21;
      if (v615 > v795)
        goto LABEL_21;
      v616 = v28->m_Summon_WaitTime - 1;
      _ZF = v28->m_Summon_WaitTime == 1;
      v28->m_Summon_WaitTime = v616;
      if (v616 >= 0 && !_ZF)
        goto LABEL_21;
      gEnemyWork_local->m_StopSummonWaitCnt = 120;
      ++gEnemyWork_local->m_SummonNum;
      *(u64 *)&v28->m_AiStep = 3;
      v28->m_Mot = 0;
      v28->m_DitherAlpha = 0.0;
      m_Res_Type = v28->m_Res_Type;
      *(u64 *)&v28->m_Pos.x = *(u64 *)&v28->m_PopPos.x;
      v28->m_Pos.z = v28->m_PopPos.z;
      *(u64 *)&v28->m_MotSpd = 1056964608;
      if (m_Res_Type)
      {
        m_EnemyId = v28->m_EnemyId;
        FromXYZg = v28->m_EnemyId;
        m_EnemyId = FromXYZg;
        if (LoadBlock(m_Res_Type, &v28->m_Res_Devil_Idx, m_EnemyId))
        {
          AsdMdlSceneAddModel(v28, (s32)v1);
          v619 = (*p_m_Res_Devil)[v28->m_Res_Devil_Idx];
          ++v619->m_NowLink;
          v28->m_CopyMdl = 0;
        }
      }
      goto LABEL_537;
    case 3:
      if (!Load_MotionSe(gEnemyWork_local->m_Obj[v25]))
        goto LABEL_21;
      v27 = 4;
      goto LABEL_20;
    case 4:
      if (v28->m_AiCnt >= 21)
      {
        if (v28->m_FAtk)
          goto LABEL_19;
      }
      m_DitherAlpha = v28->m_DitherAlpha;
      v28->m_Mot = 0;
      v822[0] = v28->m_Pos.z;
      v309 = m_DitherAlpha + 0.008333334;
      v310 = *(u64 *)&v28->m_Pos.x;
      v28->m_Pos.z = v28->m_PopPos.z;
      v311 = v28->m_AiCnt;
      ToX.n64_u64[0] = v310;
      v312 = *(u64 *)&v28->m_PopPos.x;
      *(u64 *)&v28->m_MotSpd = 1056964608;
      *(u64 *)&v28->m_Pos.x = v312;
      v28->m_AiCnt = v311 + 1;
      if (v309 > 1.0)
        v309 = 1.0;
      v28->m_DitherAlpha = v309;
      if (v311)
      {
        if (v311 + 1 < 11)
          goto LABEL_21;
        goto LABEL_353;
      }
      v313 = *v3;
      v314 = v28->m_Pos.x;
      v315 = v28->m_Pos.y;
      v316 = v28->m_Pos.z;
      v968.w = 0.0;
      v968.x = v314;
      v968.y = v315;
      v968.z = v316;
      fldSePlay3DSE_BaseVol(65561, 64, v968);
      playerY = v815;
      if (v28->m_AiCnt < 11)
        goto LABEL_21;
LABEL_353:
      m_hMdl_Model = v28->m_hMdl_Model;
      if (!mdlChkMotionEnd(m_hMdl_Model))
        goto LABEL_21;
      if (v28->m_MoveType)
      {
LABEL_447:
        v28->m_AiStep = 0;
        v28->m_AiCnt = 0;
        v369 = sub_1905740(200, 0);
        v28->m_UroUroSE_Cnt = 0;
        *(u64 *)&v28->m_AiParam = (u32)(v369 + 60);
      }
      else
      {
        v28->m_UroUroSE_Cnt = 0;
        *(_OWORD *)&v28->m_AiStep = xmmword_3D00530;
      }
      goto LABEL_21;
    case 5:
      ++v28->m_AiCnt;
      ++v28->m_NoDiscoTime;
      ++v28->m_UroUroSE_Cnt;
      if (v28->m_FAtk)
        goto LABEL_19;
      v186 = v28->m_Pos.z;
      v187 = *(u64 *)&v28->m_Pos.x;
      v28->m_Mot = 2;
      v188 = v28->m_PopPos.x;
      v822[0] = v186;
      ToX.n64_u64[0] = v187;
      *(u64 *)&v28->m_MotSpd = 0x40A000003F000000LL;
      v28->m_DitherAlpha = 1.0;
      v28->m_UroUroPos.x = v188 + (f32)(u32)sub_1905740(500, 0);
      p_m_UroUroPos = &v28->m_UroUroPos;
      v190 = v28->m_PopPos.z;
      v28->m_UroUroPos.y = v28->m_PopPos.y;
      v191 = v190 + (f32)(u32)sub_1905740(500, 0);
      v819 = ToX.n64_u64[0];
      v820 = v822[0];
      v193 = ToX.n64_u64[0];
      v194 = v822[0];
      *(u64 *)&v818.x = *(u64 *)&v28->m_UroUroPos.x;
      v28->m_UroUroPos.z = v191;
      v818.z = v28->m_UroUroPos.z;
      v195 = v818.z;
      v197 = *(u64 *)&v818.x;
      v198 = v818.y + 35.0;
      *((f32 *)&v819 + 1) = *((f32 *)&v193 + 1) + 35.0;
      v818.y = v818.y + 35.0;
      if (!v196)
      LODWORD(v835.x) = v197;
      v835.y = v198;
      v835.z = v195;
      LODWORD(v907.x) = v193;
      v907.y = *((f32 *)&v193 + 1) + 35.0;
      v907.z = v194;
      if (mapCollision_PosToPosHitChk(v835, v907) == -1)
        goto LABEL_336;
      v200 = v28->m_PopPos.x;
      v201 = v200 + (f32)(u32)sub_1905740(500, 0);
      v202 = v28->m_PopPos.y;
      v203 = v28->m_PopPos.z;
      v28->m_UroUroPos.x = v201;
      v28->m_UroUroPos.y = v202;
      v204 = v203 + (f32)(u32)sub_1905740(500, 0);
      v819 = ToX.n64_u64[0];
      v820 = v822[0];
      v206 = ToX.n64_u64[0];
      v207 = v822[0];
      *(u64 *)&v818.x = *(u64 *)&p_m_UroUroPos->x;
      v28->m_UroUroPos.z = v204;
      v818.z = v28->m_UroUroPos.z;
      v208 = v818.z;
      v210 = *(u64 *)&v818.x;
      v211 = v818.y + 35.0;
      *((f32 *)&v819 + 1) = *((f32 *)&v206 + 1) + 35.0;
      v818.y = v818.y + 35.0;
      if (!v209)
      LODWORD(v836.x) = v210;
      v836.y = v211;
      v836.z = v208;
      LODWORD(v908.x) = v206;
      v908.y = *((f32 *)&v206 + 1) + 35.0;
      v908.z = v207;
      if (mapCollision_PosToPosHitChk(v836, v908) == -1)
        goto LABEL_336;
      v212 = v28->m_PopPos.x;
      v213 = v212 + (f32)(u32)sub_1905740(500, 0);
      v214 = v28->m_PopPos.y;
      v215 = v28->m_PopPos.z;
      v28->m_UroUroPos.x = v213;
      v28->m_UroUroPos.y = v214;
      v216 = v215 + (f32)(u32)sub_1905740(500, 0);
      v819 = ToX.n64_u64[0];
      v820 = v822[0];
      v218 = ToX.n64_u64[0];
      v219 = v822[0];
      *(u64 *)&v818.x = *(u64 *)&p_m_UroUroPos->x;
      v28->m_UroUroPos.z = v216;
      v818.z = v28->m_UroUroPos.z;
      v220 = v818.z;
      v222 = *(u64 *)&v818.x;
      v223 = v818.y + 35.0;
      *((f32 *)&v819 + 1) = *((f32 *)&v218 + 1) + 35.0;
      v818.y = v818.y + 35.0;
      if (!v221)
      LODWORD(v837.x) = v222;
      v837.y = v223;
      v837.z = v220;
      LODWORD(v909.x) = v218;
      v909.y = *((f32 *)&v218 + 1) + 35.0;
      v909.z = v219;
      if (mapCollision_PosToPosHitChk(v837, v909) == -1)
      {
LABEL_336:
        *(u64 *)&v818.x = *(u64 *)&p_m_UroUroPos->x;
        v818.z = v28->m_UroUroPos.z;
        v301 = v28->m_Pos.x;
        v302 = v28->m_Pos.y;
        v303 = v28->m_Pos.z;
        retpos = v818;
        v305 = *(u64 *)&v818.x;
        v306 = v818.y + 1.0;
        v307 = v818.z;
        v818.y = v818.y + 1.0;
        if (!v304)
        v846.x = v301;
        v846.y = v302;
        v846.z = v303;
        LODWORD(v917.x) = v305;
        v917.y = v306;
        v917.z = v307;
        mapCollisionHitChk2(v846, v917, &retpos, 0);
        *(u64 *)&p_m_UroUroPos->x = *(u64 *)&retpos.x;
        v28->m_UroUroPos.z = retpos.z;
        *(u64 *)&v28->m_AiStep = 6;
      }
      else
      {
        v28->m_AiStep = 0;
        v28->m_AiCnt = 0;
        v28->m_AiParam = sub_1905740(100, 0) + 60;
      }
      playerX = v813;
      playerY = v815;
      goto LABEL_21;
    case 6:
      ++v28->m_AiCnt;
      ++v28->m_NoDiscoTime;
      ++v28->m_UroUroSE_Cnt;
      if (v28->m_FAtk)
        goto LABEL_19;
      v224 = *v3;
      p_m_Pos = &v28->m_Pos;
      ToX.n64_u64[0] = *(u64 *)&v28->m_Pos.x;
      v822[0] = v28->m_Pos.z;
      if (fldGb->nakamaMode)
        goto LABEL_425;
      if (v28->m_AiCnt >= 31 && (s32)sub_1905740(100, 0) <= 4)
      {
        *(u64 *)&v818.x = __PAIR64__(LODWORD(playerY), LODWORD(playerX));
        v818.z = playerZ;
        v333 = ToX.n64_u64[0];
        v819 = ToX.n64_u64[0];
        v334 = v822[0];
        v820 = v822[0];
        v848.x = playerX;
        v848.y = playerY;
        v848.z = playerZ;
        *(u64 *)&v919.x = v333;
        v919.z = v334;
        v335 = GetLenXYZ(v848, v919);
        if (sBtlGetABS(playerY - ToX.n64_f32[1]) < 120.0 && v335 < 800.0)
        {
LABEL_424:
          ++gEnemyWork_local->m_OikakeNum;
          v28->m_KabeCnt = 0;
          v28->m_NoDiscoTime = 0;
          v28->m_UroUroSE_Cnt = 0;
          v28->m_Icon_Anim = 0;
          v849.z = v28->m_Pos.z;
          m_ObjIdx = v28->m_ObjIdx;
          *(u64 *)&v28->m_AiStep = 7;
          v849.x = v28->m_Pos.x;
          v849.y = v28->m_Pos.y + -200.0;
          Add(m_ObjIdx, v849, 0);
          v28->m_Icon3D = 1;
          goto LABEL_21;
        }
      }
LABEL_425:
      ToX.n64_u64[0] = *p_m_Pos;
      v338 = v28->m_UroUroPos.x;
      v339 = v28->m_UroUroPos.y;
      v340 = v28->m_UroUroPos.z;
      v822[0] = v28->m_Pos.z;
      v341 = ToX.n64_u64[0];
      v28->m_Mot = 2;
      v342 = v822[0];
      v28->m_DitherAlpha = 1.0;
      *(u64 *)&v28->m_MotSpd = 0x40A000003F000000LL;
      v850.x = v338;
      v850.y = v339;
      v850.z = v340;
      *(u64 *)&v920.x = v341;
      v920.z = v342;
      v343.n64_f32[0] = GetLenXYZ(v850, v920);
      if (v343.n64_f32[0] < 30.0)
        goto LABEL_438;
      v344 = v28->m_UroUroPos.z;
      v345 = v822[0];
      v346.n64_u64[0] = *(u64 *)&v28->m_UroUroPos.x;
      v347.n64_u64[0] = ToX.n64_u64[0];
      FromXYZd = v343.n64_u64[0];
      v343.n64_u64[0] = FromXYZd;
      v348 = (f32)(v344 - v345) / v343.n64_f32[0];
      FromXYZe.n64_u64[0] = vdiv_f32(vsub_f32(v346, v347), vdup_lane_s32(v343, 0)).n64_u64[0];
      VecToDir = sBtlGetVecToDir(FromXYZe.n64_f32[0], v348);
      Dir_Hokan = sBtlGetDir_Hokan(v28->m_Dir, VecToDir, 8.0);
      __asm { FMOV            V1.2S, #1.25 }
      v28->m_Dir = Dir_Hokan;
      v352 = vadd_f32(vmul_f32(FromXYZe, _D1), *(float32x2_t *)&v28->m_Pos.x).n64_u64[0];
      v822[0] = (f32)(v348 * 1.25) + v28->m_Pos.z;
      v353 = v28->m_UroUroPos.y;
      ToX.n64_u64[0] = v352;
      ABS = sBtlGetABS(v353 - *((f32 *)&v352 + 1));
      if ((v28->m_AiCnt & 7) == 0 || ABS > 5.0)
      {
        v356 = ToX.n64_f32[0];
        v357 = ToX.n64_f32[1] + -2.5;
        v358 = v28->m_Pos.z;
        v359 = v28->m_Pos.x;
        v360 = v28->m_Pos.y;
        v361 = v822[0];
        ToX.n64_f32[1] = ToX.n64_f32[1] + -2.5;
        v851.x = v359;
        v851.y = v360;
        v851.z = v358;
        v921.x = v356;
        v921.y = v357;
        v921.z = v361;
        mapCollisionHitChk2(v851, v921, &retpos, 0);
        ToX.n64_u64[0] = *(u64 *)&retpos.x;
        v822[0] = retpos.z;
      }
      v362 = v28->m_Pos.x;
      v363 = v28->m_Pos.y;
      v364 = v28->m_Pos.z;
      v365 = ToX.n64_u64[0];
      v366 = v822[0];
      v852.x = v362;
      v852.y = v363;
      v852.z = v364;
      *(u64 *)&v922.x = v365;
      v922.z = v366;
      if (GetLenXYZ(v852, v922) < 1.0)
      {
LABEL_438:
        v28->m_AiStep = 0;
        v28->m_AiCnt = 0;
        v28->m_AiParam = sub_1905740(200, 0) + 60;
        goto LABEL_812;
      }
      *p_m_Pos = ToX.n64_u64[0];
      playerX = v813;
      playerY = v815;
      v28->m_Pos.z = v822[0];
      if (v28->m_UroUroSE_Cnt == 180)
        goto LABEL_838;
      goto LABEL_21;
    case 7:
      ++v28->m_AiCnt;
      if (v28->m_FAtk)
        goto LABEL_19;
      ToX.n64_u64[0] = *(u64 *)&v28->m_Pos.x;
      v227 = ToX.n64_u64[0];
      v822[0] = v28->m_Pos.z;
      v28->m_Mot = 2;
      v228 = v822[0];
      v28->m_DitherAlpha = 1.0;
      *(u64 *)&v28->m_MotSpd = 0x40A000003F000000LL;
      v838.x = playerX;
      v838.y = playerY;
      v838.z = playerZ;
      *(u64 *)&v910.x = v227;
      v910.z = v228;
      v229 = GetLenXYZ(v838, v910);
      v230 = sBtlGetVecToDir((f32)(playerX - ToX.n64_f32[0]) / v229, (f32)(playerZ - v822[0]) / v229);
      v231 = sBtlGetDir_Hokan(v28->m_Dir, v230, 15.0);
      v28->m_Dir = v231;
      AtoB_LR = sBtlGetAtoB_LR(v231, v230);
      v233 = v28->m_AiCnt;
      if (AtoB_LR >= 0.0)
        v234 = AtoB_LR;
      else
        v234 = -AtoB_LR;
      if (v233 == 1)
      {
        EnemySe(v28, 1);
        v233 = v28->m_AiCnt;
      }
      if (v234 >= 25.0 || v233 < 6)
        goto LABEL_21;
      v236 = v28->m_Res_Type;
      *(u64 *)&v28->m_Mot = 0xFFFFFFFF00000004LL;
      *(u64 *)&v28->m_MotSpd = 0x40A000003F800000LL;
      if (v236)
      {
        v237 = p_m_Res_Devil;
        m_Res_Avatar_Idx = 1;
        v240 = g_EnemySummonMax_local;
        goto LABEL_269;
      }
      else
      {
        m_Res_Avatar_Idx = v28->m_Res_Avatar_Idx;
        v237 = p_m_Res_Devil;
        v240 = g_EnemySummonMax_local;
LABEL_269:
        v241 = v3;
        goto LABEL_556;
      }
      v241 = v3;
LABEL_556:
      v469 = m_Res_Avatar_Idx;
      FromXYZb = m_Res_Avatar_Idx;
      v470 = gMapEnemySymbolTable[v469];
      v471 = sub_1905740((u32)(v470->m_Par_Run + v470->m_Par_Intercept + v470->m_Par_Rush - 1), 0);
      v474 = gMapEnemySymbolTable[v469];
      m_Par_Run = v474->m_Par_Run;
      if (v471 >= m_Par_Run)
      {
        v3 = v241;
        v474 = gMapEnemySymbolTable[FromXYZb];
        m_Par_Run = v474->m_Par_Run;
        g_EnemySummonMax_local = v240;
        p_m_Res_Devil = v237;
        if (v471 >= v474->m_Par_Intercept + m_Par_Run)
        {
          m_Trap1 = v28->m_Trap1;
          *(u64 *)&v28->m_AiStep = 16;
          if (m_Trap1 || v28->m_Trap3 || v28->m_Trap4)
          {
            v474 = gMapEnemySymbolTable[FromXYZb];
            m_Spd_Rush = v474->m_Spd_Rush;
            v553 = (f32)((f32)m_Spd_Rush + 1.0) + (f32)(u32)sub_1905740(3, 0);
          }
          else
          {
            v474 = gMapEnemySymbolTable[FromXYZb];
            v553 = v474->m_Spd_Rush;
          }
          v28->m_Run_Spd = v553;
          v28->m_Run_MaxSpd = v553;
          v28->m_Run_AiCnt = 0;
          v28->m_Run_Stamina = 130;
          v28->m_Kemuri_Cnt = 0;
        }
        else
        {
          v479 = v28->m_Trap1;
          *(u64 *)&v28->m_AiStep = 14;
          if (v479 || v28->m_Trap3 || v28->m_Trap4)
          {
            v474 = gMapEnemySymbolTable[FromXYZb];
            v28->m_Run_Spd = (f32)v474->m_Spd_Run;
            m_Spd_Intercept = v474->m_Spd_Intercept;
            v481 = (f32)((f32)m_Spd_Intercept + 1.0) + (f32)(u32)sub_1905740(3, 0);
          }
          else
          {
            v474 = gMapEnemySymbolTable[FromXYZb];
            v28->m_Run_Spd = gMapEnemyDiffTbl[g_EnemySymbol_Diff]->m_InterceptSpd;
            v481 = v474->m_Spd_Intercept;
          }
          v28->m_Intercept_MaxSpd = v481;
          m_Dir = v28->m_Dir;
          v28->m_Kemuri_Cnt = 0;
          v28->m_Intercept_Dir = m_Dir;
          *(u64 *)&v28->m_Intercept_AiCnt = 0x12C00000000LL;
        }
      }
      else
      {
        v3 = v241;
        v476 = v28->m_Trap1;
        *(u64 *)&v28->m_AiStep = 8;
        if (v476 || v28->m_Trap3 || v28->m_Trap4)
        {
          g_EnemySummonMax_local = v240;
          v474 = gMapEnemySymbolTable[FromXYZb];
          m_Spd_Run = v474->m_Spd_Run;
          v28->m_Run_Spd = m_Spd_Run;
          v478 = (f32)(m_Spd_Run + 1.0) + (f32)(u32)sub_1905740(3, 0);
        }
        else
        {
          g_EnemySummonMax_local = v240;
          v474 = gMapEnemySymbolTable[FromXYZb];
          v28->m_Run_Spd = gMapEnemyDiffTbl[g_EnemySymbol_Diff]->m_RunSpd;
          v478 = v474->m_Spd_Run;
        }
        p_m_Res_Devil = v237;
        v28->m_Run_MaxSpd = v478;
        v28->m_Run_AiCnt = 0;
        v28->m_Run_Stamina = 300;
        v28->m_Kemuri_Cnt = 0;
      }
      goto LABEL_21;
    case 8:
      ++v28->m_AiCnt;
      if (v28->m_FAtk)
        goto LABEL_18;
      v42 = &v28->m_Pos;
      ToX.n64_u64[0] = *(u64 *)&v28->m_Pos.x;
      v43 = ToX.n64_u64[0];
      v822[0] = v28->m_Pos.z;
      v28->m_Mot = 4;
      v44 = v822[0];
      FromXYZ.n64_u64[0] = v43;
      v28->m_DitherAlpha = 1.0;
      v45 = v28->m_Run_AiCnt - 1;
      *(u64 *)&v28->m_MotSpd = 0x40A000003F800000LL;
      v28->m_Run_AiCnt = v45;
      if (v45 > 0)
        goto LABEL_56;
      if (v28->m_Run_Stamina < 0 || v28->m_AkirameSwitchOn)
      {
        m_Run_Spd = v28->m_Run_Spd;
        if (m_Run_Spd <= 5.0)
          goto LABEL_479;
        m_Run_MaxSpd = m_Run_Spd + -1.0;
LABEL_683:
        v28->m_Run_Spd = m_Run_MaxSpd;
        goto LABEL_684;
      }
      v579 = v44;
      v580 = v28->m_Run_Spd;
      v581 = v580 + gMapEnemyDiffTbl[g_EnemySymbol_Diff]->m_RunAccel;
      m_Run_MaxSpd = v28->m_Run_MaxSpd;
      v44 = v579;
      v28->m_Run_Spd = v581;
      if (v581 > m_Run_MaxSpd)
        goto LABEL_683;
LABEL_684:
      v582 = ToX.n64_u64[0];
      v583 = v822[0];
      if (!v28->m_Trap1)
      {
        v584 = v28->m_PopPos.x;
        v585 = v28->m_PopPos.y;
        v586 = v28->m_PopPos.z;
        v871.x = v584;
        v871.y = v585;
        v871.z = v586;
        *(u64 *)&v938.x = v582;
        v938.z = v583;
        v587 = GetLenXYZ(v871, v938);
        playerY = v815;
        if (sBtlGetABS(v815 - ToX.n64_f32[1]) > 120.0 || v587 > 2500.0)
          goto LABEL_723;
        v583 = v822[0];
        v582 = ToX.n64_u64[0];
      }
      v588 = v44;
      v872.x = v813;
      v872.z = playerZ;
      *(u64 *)&v939.x = v582;
      v872.y = v815;
      v939.z = v583;
      playerY = v815;
      if (GetLenXYZ(v872, v939) > 3000.0)
        goto LABEL_723;
      v589 = ToX.n64_f32[1];
      if (sBtlGetABS(v815 - v589) > 120.0 || v28->m_KabeCnt >= 181)
        goto LABEL_723;
      v819 = ToX.n64_u64[0];
      v591 = frompos;
      *(u64 *)&v818.x = __PAIR64__(LODWORD(frompos), LODWORD(v813));
      v818.z = playerZ;
      v592 = ToX.n64_u64[0];
      v820 = v822[0];
      v594 = ToX.n64_f32[1] + 25.0;
      v595 = v822[0];
      *((f32 *)&v819 + 1) = ToX.n64_f32[1] + 25.0;
      if (!v593)
      {
        v591 = frompos;
      }
      v873.x = v813;
      v873.y = v591;
      v873.z = playerZ;
      LODWORD(v940.x) = v592;
      v940.y = v594;
      v940.z = v595;
      if (mapCollision_PosToPosHitChk(v873, v940) == -1)
      {
        v28->m_KabeCnt = 0;
        v747 = sub_1905740(4, 0);
        v28->m_Run_ContactPos.z = playerZ;
        v28->m_Run_AiCnt = v747 + 4;
        v28->m_Run_ContactPos.x = v813;
        v28->m_Run_ContactPos.y = v815;
        v44 = v588;
      }
      else
      {
        v44 = v588;
        if (!v28->m_Trap1)
        {
          v748 = *((f32 *)&v819 + 1);
          if ((f32)(*((f32 *)&v819 + 1) - v818.y) > -10.0 && (f32)(*((f32 *)&v819 + 1) - v818.y) < 10.0)
          {
            v750 = v822[0];
            v751 = ToX.n64_f32[0];
            v752 = *(f32 *)&v819;
            v753 = v820;
            v890.x = v813;
            v890.z = v750;
            v955.x = v752;
            v890.y = frompos;
            v955.y = v748;
            v955.z = v753;
            if (mapCollision_PosToPosHitChk(v890, v955) == -1)
            {
              v755 = *(u64 *)&v818.x;
              v756 = v818.z;
              v891.x = v813;
              v891.z = v750;
              *(u64 *)&v956.x = v755;
              v891.y = frompos;
              v956.z = v756;
              if (mapCollision_PosToPosHitChk(v891, v956) == -1)
              {
                v28->m_AssisttPos.z = v750;
                v28->m_AssisttPos.x = v813;
                playerY = v815;
                v28->m_AssisttPos.y = v815;
                playerX = v813;
                goto LABEL_897;
              }
            }
            v758 = v819;
            v759 = v820;
            v892.y = frompos;
            v892.x = v751;
            v892.z = playerZ;
            *(u64 *)&v957.x = v758;
            v957.z = v759;
            playerX = v813;
            if (mapCollision_PosToPosHitChk(v892, v957) == -1)
            {
              v761 = *(u64 *)&v818.x;
              v762 = v818.z;
              v893.y = frompos;
              v893.x = v751;
              v893.z = playerZ;
              *(u64 *)&v958.x = v761;
              v958.z = v762;
              if (mapCollision_PosToPosHitChk(v893, v958) == -1)
              {
                v28->m_AssisttPos.x = v751;
                playerY = v815;
                v28->m_AssisttPos.y = v815;
                v28->m_AssisttPos.z = playerZ;
LABEL_897:
                v27 = 9;
                goto LABEL_20;
              }
            }
          }
        }
        m_KabeCnt = v28->m_KabeCnt;
        v28->m_Run_AiCnt = 0;
        v28->m_KabeCnt = m_KabeCnt + 1;
      }
LABEL_56:
      v46 = v28->m_PopPos.x;
      v47 = v28->m_PopPos.y;
      v48 = v28->m_PopPos.z;
      v49 = ToX.n64_u64[0];
      v50 = v822[0];
      v826.x = v46;
      v826.y = v47;
      v826.z = v48;
      *(u64 *)&v899.x = v49;
      v899.z = v50;
      if (GetLenXYZ(v826, v899) >= 600.0)
      {
        m_Run_Stamina = v28->m_Run_Stamina;
      }
      else
      {
        m_Run_Stamina = v28->m_Run_Stamina;
        if ((v28->m_AiCnt & 3) != 0)
        {
          if ((m_Run_Stamina & 0x80000000) == 0)
            goto LABEL_452;
          goto LABEL_450;
        }
      }
      v370 = m_Run_Stamina - 1;
      v28->m_Run_Stamina = v370;
      if ((v370 & 0x80000000) == 0)
        goto LABEL_452;
LABEL_450:
      v371 = v28->m_Run_Spd;
      if (v371 > 5.0)
        v28->m_Run_Spd = v371 + -1.0;
LABEL_452:
      v792 = p_m_Res_Devil;
      v372 = g_EnemySummonMax_local;
      if (v28->m_KabeCnt <= 29)
      {
        v374 = v28->m_Run_ContactPos.x;
        v375 = v28->m_Run_ContactPos.y;
        v376 = v28->m_Run_ContactPos.z;
        v377 = ToX.n64_u64[0];
        v378 = v822[0];
        v853.x = v374;
        v853.y = v375;
        v853.z = v376;
        *(u64 *)&v923.x = v377;
        v373 = v3;
        v923.z = v378;
        v379 = GetLenXYZ(v853, v923);
        v380 = sBtlGetVecToDir((f32)(v28->m_Run_ContactPos.x - ToX.n64_f32[0]) / v379, (f32)(v28->m_Run_ContactPos.z - v822[0]) / v379);
        v381 = sBtlGetDir_Hokan(v28->m_Dir, v380, 10.0);
        v28->m_Dir = v381;
        sBtlGetMoveXZ(ToX.n64_f32[0], v822[0], v381, v28->m_Run_Spd, &ToX, v822);
      }
      else
      {
        v373 = v3;
        v28->m_Mot = 1;
        *(u64 *)&v28->m_MotSpd = 0x40C000003F000000LL;
      }
      v382 = 0;
      while (1)
      {
        if (v25 != v382)
        {
          v384 = gEnemyWork_local->m_Obj[v382];
          if (v384[2].n64_u8[0])
          {
            v385 = v384[6].n64_f32[0];
            v386 = v384[6].n64_f32[1];
            v387 = v384[7].n64_f32[0];
            *(float32x2_t *)&v854.x = FromXYZ;
            v854.z = v44;
            v924.x = v385;
            v924.y = v386;
            v924.z = v387;
            v383.n64_f32[0] = GetLenXYZ(v854, v924);
            if (v383.n64_f32[0] < 1.0)
              v383.n64_f32[0] = 1.0;
            if (v383.n64_f32[0] < 50.0)
              break;
          }
        }
        if (++v382 == 40)
          goto LABEL_623;
      }
LABEL_624:
      v537 = -5.0;
      v538 = v384[7].n64_f32[0] - v44;
      goto LABEL_626;
    case 9:
      ++v28->m_AiCnt;
      if (v28->m_FAtk)
        goto LABEL_18;
      ToX.n64_u64[0] = *(u64 *)&v28->m_Pos.x;
      v242 = ToX.n64_u64[0];
      v822[0] = v28->m_Pos.z;
      v243 = v822[0];
      v28->m_Mot = 4;
      v244 = v242;
      v28->m_DitherAlpha = 1.0;
      v245 = v243;
      v246 = v28->m_Run_AiCnt - 1;
      *(u64 *)&v28->m_MotSpd = 0x404000003F800000LL;
      v28->m_Run_AiCnt = v246;
      FromXYZa.n64_u64[0] = v242;
      if (v246 > 0)
      {
        v248 = v28->m_AssisttPos.x;
        v249 = v28->m_AssisttPos.y;
        v250 = v28->m_AssisttPos.z;
        goto LABEL_274;
      }
      if (v28->m_Run_Stamina < 0 || v28->m_AkirameSwitchOn)
      {
        v367 = v28->m_Run_Spd;
        if (v367 <= 5.0)
          goto LABEL_479;
        v368 = v367 + -1.0;
LABEL_705:
        v28->m_Run_Spd = v368;
        goto LABEL_706;
      }
      v598 = v28->m_Run_Spd;
      m_RunAccel = gMapEnemyDiffTbl[g_EnemySymbol_Diff]->m_RunAccel;
      v600 = v598 + (f32)(m_RunAccel + (f32)((f32)(u32)sub_1905740(200, 0) / 100.0));
      v368 = v28->m_Run_MaxSpd;
      v28->m_Run_Spd = v600;
      if (v600 > v368)
        goto LABEL_705;
LABEL_706:
      v601 = ToX.n64_u64[0];
      v602 = v822[0];
      if (!v28->m_Trap1)
      {
        v603 = v28->m_PopPos.x;
        v604 = v28->m_PopPos.y;
        v605 = v28->m_PopPos.z;
        v874.x = v603;
        v874.y = v604;
        v874.z = v605;
        *(u64 *)&v941.x = v601;
        v941.z = v602;
        if (GetLenXYZ(v874, v941) > 2500.0)
        {
LABEL_810:
          --gEnemyWork_local->m_OikakeNum;
          v285 = 10;
LABEL_811:
          *(u64 *)&v28->m_AiStep = v285;
LABEL_812:
          playerX = v813;
          playerY = v815;
          goto LABEL_21;
        }
        v602 = v822[0];
        v601 = ToX.n64_u64[0];
      }
      v875.x = v813;
      v875.z = playerZ;
      *(u64 *)&v942.x = v601;
      v875.y = v815;
      v942.z = v602;
      playerY = v815;
      if (GetLenXYZ(v875, v942) > 3000.0)
        goto LABEL_723;
      v606 = ToX.n64_f32[1];
      if (sBtlGetABS(v815 - v606) > 120.0 || v28->m_KabeCnt >= 181)
      {
LABEL_723:
        playerX = v813;
        --gEnemyWork_local->m_OikakeNum;
        v27 = 10;
        goto LABEL_20;
      }
      v819 = ToX.n64_u64[0];
      playerX = v813;
      v608 = frompos;
      *(u64 *)&v818.x = __PAIR64__(LODWORD(frompos), LODWORD(v813));
      v818.z = playerZ;
      v609 = ToX.n64_u64[0];
      v820 = v822[0];
      v611 = ToX.n64_f32[1] + 25.0;
      v612 = v822[0];
      *((f32 *)&v819 + 1) = ToX.n64_f32[1] + 25.0;
      if (!v610)
      {
        v608 = frompos;
      }
      v876.x = v813;
      v876.y = v608;
      v876.z = playerZ;
      LODWORD(v943.x) = v609;
      v943.y = v611;
      v943.z = v612;
      v613 = mapCollision_PosToPosHitChk(v876, v943);
      v28->m_KabeCnt = 0;
      if (v613 == -1)
      {
        v28->m_Run_AiCnt = 0;
        v27 = 8;
        goto LABEL_20;
      }
      v614 = sub_1905740(4, 0);
      v244 = ToX.n64_u64[0];
      v28->m_Run_AiCnt = v614 + 4;
      v245 = v822[0];
      *(u64 *)&v28->m_Run_ContactPos.x = *(u64 *)&v28->m_AssisttPos.x;
      v28->m_Run_ContactPos.z = v28->m_AssisttPos.z;
      v248 = v28->m_AssisttPos.x;
      v249 = v28->m_AssisttPos.y;
      v250 = v28->m_AssisttPos.z;
LABEL_274:
      v839.x = v248;
      v839.y = v249;
      v839.z = v250;
      *(u64 *)&v823.x = v244;
      v823.z = v245;
      v251 = GetLenXYZ(v839, v823);
      v252 = v28->m_Run_Spd;
      if (v251 < v252)
      {
        v28->m_KabeCnt = 0;
        v27 = 8;
        v28->m_Run_AiCnt = 0;
        goto LABEL_322;
      }
      v388 = v28->m_Run_Stamina - 1;
      v28->m_Run_Stamina = v388;
      if (v252 > 5.0 && v388 < 0)
        v28->m_Run_Spd = v252 + -1.0;
      v793 = p_m_Res_Devil;
      v389 = g_EnemySummonMax_local;
      if (v28->m_KabeCnt <= 29)
      {
        v483 = v28->m_Run_ContactPos.x;
        v484 = v28->m_Run_ContactPos.y;
        v485 = v28->m_Run_ContactPos.z;
        v486 = ToX.n64_u64[0];
        v487 = v822[0];
        v862.x = v483;
        v862.y = v484;
        v862.z = v485;
        *(u64 *)&v931.x = v486;
        v390 = v3;
        v931.z = v487;
        v488 = GetLenXYZ(v862, v931);
        v489 = sBtlGetVecToDir((f32)(v28->m_Run_ContactPos.x - ToX.n64_f32[0]) / v488, (f32)(v28->m_Run_ContactPos.z - v822[0]) / v488);
        v490 = sBtlGetDir_Hokan(v28->m_Dir, v489, 10.0);
        v28->m_Dir = v490;
        sBtlGetMoveXZ(ToX.n64_f32[0], v822[0], v490, v28->m_Run_Spd, &ToX, v822);
      }
      else
      {
        v390 = v3;
        v28->m_Mot = 1;
        *(u64 *)&v28->m_MotSpd = 0x40C000003F000000LL;
      }
      v491 = 0;
      while (1)
      {
        if (v25 != v491)
        {
          v493 = gEnemyWork_local->m_Obj[v491];
          if (v493[2].n64_u8[0])
          {
            v494 = v493[6].n64_f32[0];
            v495 = v493[6].n64_f32[1];
            v496 = v493[7].n64_f32[0];
            *(float32x2_t *)&v863.x = FromXYZa;
            v863.z = v243;
            v932.x = v494;
            v932.y = v495;
            v932.z = v496;
            v492.n64_f32[0] = GetLenXYZ(v863, v932);
            if (v492.n64_f32[0] < 1.0)
              v492.n64_f32[0] = 1.0;
            if (v492.n64_f32[0] < 50.0)
              break;
          }
        }
        if (++v491 == 40)
        {
          v497 = ToX.n64_u64[0];
          v498 = v822[0];
          goto LABEL_741;
        }
      }
      __asm { FMOV            V4.2S, #-5.0 }
      v498 = v822[0] + (f32)((f32)((f32)(v493[7].n64_f32[0] - v243) / v492.n64_f32[0]) * -5.0);
      v621.n64_u64[0] = vdiv_f32(vsub_f32(v493[6], FromXYZa), vdup_lane_s32(v492, 0)).n64_u64[0];
      v822[0] = v498;
      v497 = vadd_f32(ToX, vmul_f32(v621, _D4)).n64_u64[0];
      ToX.n64_u32[0] = v497;
LABEL_741:
      v3 = v390;
      v622 = v28->m_Pos.x;
      v623 = v28->m_Pos.y;
      v624 = v28->m_Pos.z;
      v625 = *((f32 *)&v497 + 1) + -5.0;
      ToX.n64_f32[1] = *((f32 *)&v497 + 1) + -5.0;
      if (!v626)
      {
        FromXYZh = v497;
        LODWORD(v497) = FromXYZh;
      }
      v877.x = v622;
      v877.y = v623;
      v877.z = v624;
      LODWORD(v824.x) = v497;
      v824.y = v625;
      v824.z = v498;
      mapCollisionHitChk2(v877, v824, &retpos, 0);
      g_EnemySummonMax_local = v389;
      v28->m_Pos = retpos;
      playerX = v813;
      playerY = v815;
      p_m_Res_Devil = v793;
      v627 = v28->m_Kemuri_Cnt - 1;
      _ZF = v28->m_Kemuri_Cnt == 1;
      v28->m_Kemuri_Cnt = v627;
      if (v627 < 0 || _ZF)
      {
        v628 = v28->m_Pos.x;
        v629 = v28->m_Pos.y;
        v630 = v28->m_Pos.z;
        v631 = *v3;
        v878.y = (f32)(v629 / -100.0) + 0.1;
        v878.z = v630 / -100.0;
        v878.x = v628 / -100.0;
        addPlayerFootEffect_Pos(v878, 1.5);
        v468 = sub_1905740(4, 0) + 18;
        goto LABEL_635;
      }
      goto LABEL_744;
    case 0xA:
      ++v28->m_AiCnt;
      gEnemyWork_local->m_StopNoDiscoCnt = 120;
      if (v28->m_FAtk)
        goto LABEL_19;
      ToX.n64_u64[0] = *(u64 *)&v28->m_Pos.x;
      v822[0] = v28->m_Pos.z;
      v28->m_Mot = 1;
      m_Icon3D = v28->m_Icon3D;
      *(u64 *)&v28->m_MotSpd = 0x40C000003F000000LL;
      if (m_Icon3D)
      {
        v254 = v28->m_ObjIdx;
        v28->m_Icon3D = 0;
        Delete(v254);
      }
      if (v28->m_AiCnt < 61)
        goto LABEL_21;
      v27 = 11;
      goto LABEL_20;
    case 0xB:
      ++v28->m_AiCnt;
      if (v28->m_FAtk)
        goto LABEL_19;
      v255 = v28->m_AiCnt;
      if (v255 == 1)
      {
        v256 = *v3;
        v257 = v28->m_Pos.x;
        v258 = v28->m_Pos.y;
        v259 = v28->m_Pos.z;
        v967.w = 0.0;
        v967.x = v257;
        v967.y = v258;
        v967.z = v259;
        fldSePlay3DSE_BaseVol(65564, 64, v967);
        playerY = v815;
        v255 = v28->m_AiCnt;
      }
      v28->m_Mot = 7;
      *(u64 *)&v28->m_MotSpd = 0x404000003F000000LL;
      v260 = v28->m_DitherAlpha + -0.008333334;
      if (v260 < 0.0)
        v260 = 0.0;
      v28->m_DitherAlpha = v260;
      if (v255 < 151)
        goto LABEL_21;
LABEL_72:
      SceneDel_1(v28);
      v27 = 13;
      goto LABEL_20;
    case 0xC:
      ++v28->m_AiCnt;
      goto LABEL_72;
    case 0xD:
      v56 = v28->m_AiCnt + 1;
      _NF = v28->m_AiCnt - 2 < 0;
      v28->m_AiCnt = v56;
      if (_NF == __OFSUB__(v56, 3))
      {
        MemFree_NotFreeBase_1(v28);
        v28->m_AiStep = 0;
        v28->m_AiCnt = 0;
        *(u16 *)&v28->m_Trap3 = 0;
        *(u16 *)&v28->m_AkirameSwitchOn = 0;
        v28->m_Use = 1;
        Choice1(v28);
        ReSet_SummonWait(v28);
      }
      goto LABEL_21;
    case 0xE:
      ++v28->m_AiCnt;
      if (v28->m_FAtk)
        goto LABEL_18;
      v42 = &v28->m_Pos;
      ToX.n64_u64[0] = *(u64 *)&v28->m_Pos.x;
      v261 = ToX.n64_u64[0];
      v822[0] = v28->m_Pos.z;
      v28->m_Mot = 4;
      v262 = v822[0];
      FromXYZ.n64_u64[0] = v261;
      v263 = v28->m_Trap1;
      *(u64 *)&v28->m_MotSpd = 0x404000003F800000LL;
      if (!v263)
      {
        v264 = v28->m_PopPos.x;
        v265 = v28->m_PopPos.y;
        v266 = v28->m_PopPos.z;
        *(float32x2_t *)&v911.x = FromXYZ;
        v840.x = v264;
        v840.y = v265;
        v840.z = v266;
        v911.z = v262;
        if (GetLenXYZ(v840, v911) > 1800.0)
          goto LABEL_479;
      }
      v267 = v28->m_Intercept_AiCnt - 1;
      _ZF = v28->m_Intercept_AiCnt == 1;
      v28->m_Intercept_AiCnt = v267;
      if (v267 >= 0 && !_ZF)
        goto LABEL_297;
      if (v28->m_Run_Stamina < 0 || v28->m_AkirameSwitchOn)
      {
        m_Intercept_Spd = v28->m_Intercept_Spd;
        if (m_Intercept_Spd <= 5.0)
          goto LABEL_479;
        ToXYZa = v262;
        m_Intercept_MaxSpd = m_Intercept_Spd + -1.0;
LABEL_754:
        v28->m_Intercept_Spd = m_Intercept_MaxSpd;
        goto LABEL_755;
      }
      v633 = v28->m_Intercept_Spd;
      ToXYZa = v262;
      m_InterceptAccel = gMapEnemyDiffTbl[g_EnemySymbol_Diff]->m_InterceptAccel;
      v635 = v633 + (f32)(m_InterceptAccel + (f32)((f32)(u32)sub_1905740(200, 0) / 100.0));
      m_Intercept_MaxSpd = v28->m_Intercept_MaxSpd;
      v28->m_Intercept_Spd = v635;
      if (v635 > m_Intercept_MaxSpd)
        goto LABEL_754;
LABEL_755:
      v636 = gEnemyWork_local->m_PlayerPos.x;
      v637 = gEnemyWork_local->m_PlayerPos.z;
      m_PlayerDir = gEnemyWork_local->m_PlayerDir;
      v639 = v28->m_Pos.x;
      v640 = v28->m_Pos.z;
      v28->m_Intercept_PtoEDir = sBtlGetDir_PosDirToPos(v636, v637, m_PlayerDir, v639, v640);
      v642 = gEnemyWork_local->m_PlayerSpd - v28->m_Intercept_Spd;
      v643 = v28->m_Pos.z;
      v644 = v28->m_Pos.x;
      v645 = v28->m_Pos.y;
      if (v642 < 0.0)
        v642 = -v642;
      if (v642 < 1.0)
        v642 = 1.0;
      v28->m_Intercept_Velocity = v642;
      v646 = gEnemyWork_local->m_PlayerPos.x;
      v647 = gEnemyWork_local->m_PlayerPos.y;
      v648 = gEnemyWork_local->m_PlayerPos.z;
      v879.x = v646;
      v879.y = v647;
      v879.z = v648;
      v944.x = v644;
      v944.y = v645;
      v944.z = v643;
      v650 = GetLenXYZ(v879, v944);
      v651 = v650 / v28->m_Intercept_Velocity;
      if (v651 > 40.0)
        v651 = 40.0;
      v28->m_Intercept_Range = v650;
      v28->m_Intercept_Time = v651;
      v653 = vadd_f32(*(float32x2_t *)&gEnemyWork_local->m_PlayerPos.x, vmul_n_f32(*(float32x2_t *)&gEnemyWork_local->m_PlayerVec.x, v651)).n64_u64[0];
      v654 = gEnemyWork_local->m_PlayerPos.z + (f32)(gEnemyWork_local->m_PlayerVec.z * v651);
      *(u64 *)&v28->m_Intercept_ContactPos.x = v653;
      p_m_Intercept_ContactPos = &v28->m_Intercept_ContactPos;
      v28->m_Intercept_ContactPos.z = v654;
      v656 = *(TYPE_ENEMYWORK **)&p_m_PlayerPos->x;
      *(u64 *)&v818.x = *(u64 *)&v28->m_Intercept_ContactPos.x;
      v657 = gEnemyWork_local->m_PlayerPos.z;
      v819 = v656;
      *(f32 *)&v656 = v28->m_Intercept_ContactPos.z;
      v658 = *(u64 *)&v818.x;
      v659 = v819;
      v820 = v657;
      LODWORD(v818.z) = (u32)v656;
      v661 = v818.y + 25.0;
      v662 = v820;
      v663 = *(f32 *)&v656;
      v664 = *((f32 *)&v819 + 1) + 25.0;
      v818.y = v818.y + 25.0;
      *((f32 *)&v819 + 1) = *((f32 *)&v819 + 1) + 25.0;
      if (!v660)
      LODWORD(v880.x) = v658;
      v880.y = v661;
      v880.z = v663;
      LODWORD(v945.x) = v659;
      v945.y = v664;
      v945.z = v662;
      if (Collision_PosToPosHitChk(v880, v945, &v817) != -1)
      {
        *(u64 *)&p_m_Intercept_ContactPos->x = *(u64 *)&v817.x;
        v28->m_Intercept_ContactPos.z = v817.z;
      }
      m_Intercept_Range = v28->m_Intercept_Range;
      playerX = v813;
      playerY = v815;
      if (m_Intercept_Range > 1200.0)
        goto LABEL_770;
      if (m_Intercept_Range >= 600.0)
      {
        if (v28->m_Intercept_Spd > 15.0)
        {
          v740 = v28->m_Intercept_ContactPos.x;
          v741 = v28->m_Intercept_ContactPos.y;
          v742 = v28->m_Intercept_ContactPos.z;
          v743 = v28->m_Pos.x;
          v744 = v28->m_Pos.y;
          v745 = v28->m_Pos.z;
          v889.x = v740;
          v889.y = v741;
          v889.z = v742;
          v954.x = v743;
          v954.y = v744;
          v954.z = v745;
          v746 = GetLenXYZ(v889, v954);
          m_Intercept_Range = v28->m_Intercept_Range;
          playerX = v813;
          playerY = v815;
          if (m_Intercept_Range > v746)
          {
LABEL_770:
            v666 = *(TYPE_ENEMYWORK **)&p_m_PlayerPos->x;
            v28->m_Intercept_ContactPos.z = gEnemyWork_local->m_PlayerPos.z;
            *(u64 *)&p_m_Intercept_ContactPos->x = v666;
          }
        }
      }
      else if (v28->m_Intercept_PtoEDir < 80.0)
      {
        goto LABEL_770;
      }
      if (m_Intercept_Range > 3000.0)
        goto LABEL_786;
      v667 = ToX.n64_f32[1];
      if (sBtlGetABS(playerY - v667) > 120.0 || v28->m_KabeCnt >= 181)
      {
LABEL_786:
        --gEnemyWork_local->m_OikakeNum;
        v27 = 10;
        goto LABEL_20;
      }
      v819 = ToX.n64_u64[0];
      *(u64 *)&v818.x = *(u64 *)&p_m_Intercept_ContactPos->x;
      v668 = v28->m_Intercept_ContactPos.z;
      v820 = v822[0];
      v670 = *(u64 *)&v818.x;
      v818.z = v668;
      v671 = ToX.n64_u64[0];
      v673 = v668;
      v674 = ToX.n64_f32[1] + 25.0;
      v675 = v818.y + 25.0;
      v676 = v822[0];
      *((f32 *)&v819 + 1) = ToX.n64_f32[1] + 25.0;
      v818.y = v818.y + 25.0;
      if (!v672)
      LODWORD(v881.x) = v670;
      v881.y = v675;
      v881.z = v673;
      LODWORD(v946.x) = v671;
      v946.y = v674;
      v946.z = v676;
      if (mapCollision_PosToPosHitChk(v881, v946) == -1)
      {
        v28->m_KabeCnt = 0;
        v28->m_Intercept_AiCnt = sub_1905740(4, 0) + 4;
LABEL_880:
        v262 = ToXYZa;
LABEL_297:
        ToXYZ = v262;
        v268 = v28->m_PopPos.z;
        v269 = v28->m_PopPos.x;
        v270 = v28->m_PopPos.y;
        v271 = v822[0];
        v272 = ToX.n64_u64[0];
        v841.x = v269;
        v841.y = v270;
        v841.z = v268;
        *(u64 *)&v912.x = v272;
        v912.z = v271;
        if (GetLenXYZ(v841, v912) >= 600.0)
        {
          m_Intercept_Stamina = v28->m_Intercept_Stamina;
        }
        else
        {
          m_Intercept_Stamina = v28->m_Intercept_Stamina;
          if ((v28->m_AiCnt & 3) != 0)
          {
            if (m_Intercept_Stamina < 0)
              goto LABEL_488;
            goto LABEL_490;
          }
        }
        v401 = m_Intercept_Stamina - 1;
        v28->m_Intercept_Stamina = v401;
        if (v401 < 0)
        {
LABEL_488:
          v402 = v28->m_Intercept_Spd;
          if (v402 > 5.0)
            v28->m_Intercept_Spd = v402 + -1.0;
        }
LABEL_490:
        v403 = v28->m_Intercept_ContactPos.x;
        v404 = v28->m_Intercept_ContactPos.y;
        v405 = v28->m_Intercept_ContactPos.z;
        v406 = ToX.n64_u64[0];
        v407 = v822[0];
        v856.x = v403;
        v856.y = v404;
        v856.z = v405;
        *(u64 *)&v926.x = v406;
        v926.z = v407;
        v408 = GetLenXYZ(v856, v926);
        if (v408 > 1.0)
        {
          v409 = v408;
          v410 = v28->m_Intercept_ContactPos.x;
          v411 = v28->m_Intercept_ContactPos.z;
          v412 = ToX.n64_f32[0];
          v413 = v822[0];
          v414 = sBtlGetVecToDir((f32)(v410 - v412) / v409, (f32)(v411 - v413) / v409);
          v28->m_Intercept_Dir = sBtlGetDir_Hokan(v28->m_Intercept_Dir, v414, 10.0);
        }
        v792 = p_m_Res_Devil;
        if (v28->m_Intercept_Range < 400.0 || v28->m_KabeCnt >= 31)
        {
          v420 = gEnemyWork_local->m_PlayerPos.x;
          v421 = gEnemyWork_local->m_PlayerPos.y;
          v422 = gEnemyWork_local->m_PlayerPos.z;
          v423 = ToX.n64_u64[0];
          v424 = v822[0];
          v857.x = v420;
          v857.y = v421;
          v857.z = v422;
          *(u64 *)&v927.x = v423;
          v372 = g_EnemySummonMax_local;
          v927.z = v424;
          v425 = GetLenXYZ(v857, v927);
          v426 = sBtlGetVecToDir((f32)(gEnemyWork_local->m_PlayerPos.x - ToX.n64_f32[0]) / v425, (f32)(gEnemyWork_local->m_PlayerPos.z - v822[0]) / v425);
          v28->m_Dir = sBtlGetDir_Hokan(v28->m_Dir, v426, 5.0);
        }
        else
        {
          v415 = v28->m_Dir;
          m_Intercept_Dir = v28->m_Intercept_Dir;
          v372 = g_EnemySummonMax_local;
          v417 = sBtlGetDir_Hokan(v415, m_Intercept_Dir, 5.0);
          v418 = v28->m_Intercept_Dir;
          v28->m_Dir = v417;
          if (sBtlGetAtoB_LR_ABS(v417, v418) > 10.0)
          {
            v419 = v28->m_Intercept_Spd;
            if (v419 > 5.0)
              v28->m_Intercept_Spd = v419 + -1.0;
          }
        }
        v373 = v3;
        v427 = ToX.n64_f32[0];
        v428 = v822[0];
        v429 = v28->m_Intercept_Dir;
        v430 = v28->m_Intercept_Spd;
        sBtlGetMoveXZ(v427, v428, v429, v430, &ToX, v822);
        v431 = 0;
        while (1)
        {
          if (v25 != v431)
          {
            v384 = gEnemyWork_local->m_Obj[v431];
            if (v384[2].n64_u8[0])
            {
              v432 = v384[6].n64_f32[0];
              v433 = v384[6].n64_f32[1];
              v434 = v384[7].n64_f32[0];
              *(float32x2_t *)&v858.x = FromXYZ;
              v858.z = ToXYZ;
              v928.x = v432;
              v928.y = v433;
              v928.z = v434;
              v383.n64_f32[0] = GetLenXYZ(v858, v928);
              if (v383.n64_f32[0] < 1.0)
                v383.n64_f32[0] = 1.0;
              if (v383.n64_f32[0] < 50.0)
                break;
            }
          }
          if (++v431 == 40)
            goto LABEL_623;
        }
        v537 = -5.0;
        v538 = v384[7].n64_f32[0] - ToXYZ;
LABEL_626:
        __asm { FMOV            V4.2S, #-5.0 }
        v536 = v822[0] + (f32)((f32)(v538 / v383.n64_f32[0]) * v537);
        v540.n64_u64[0] = vdiv_f32(vsub_f32(v384[6], FromXYZ), vdup_lane_s32(v383, 0)).n64_u64[0];
        v822[0] = v536;
        v535 = vadd_f32(ToX, vmul_f32(v540, _D4)).n64_u64[0];
        ToX.n64_u32[0] = v535;
LABEL_627:
        v3 = v373;
        v541 = v28->m_Pos.x;
        v542 = v28->m_Pos.y;
        v543 = v28->m_Pos.z;
        v544 = *((f32 *)&v535 + 1) + -5.0;
        ToX.n64_f32[1] = *((f32 *)&v535 + 1) + -5.0;
        if (!v545)
        {
          FromXYZf = v535;
          LODWORD(v535) = FromXYZf;
        }
        v867.x = v541;
        v867.y = v542;
        v867.z = v543;
        LODWORD(v825.x) = v535;
        v825.y = v544;
        v825.z = v536;
        mapCollisionHitChk2(v867, v825, &retpos, 0);
        g_EnemySummonMax_local = v372;
        *v42 = retpos;
        playerX = v813;
        playerY = v815;
        p_m_Res_Devil = v792;
        v546 = v28->m_Kemuri_Cnt - 1;
        _ZF = v28->m_Kemuri_Cnt == 1;
        v28->m_Kemuri_Cnt = v546;
        if (v546 >= 0 && !_ZF)
        {
LABEL_744:
          goto LABEL_21;
        }
        v547 = v28->m_Pos.x;
        v548 = v28->m_Pos.y;
        v549 = v28->m_Pos.z;
        v550 = *v3;
        v868.y = (f32)(v548 / -100.0) + 0.1;
        v868.z = v549 / -100.0;
        v868.x = v547 / -100.0;
        addPlayerFootEffect_Pos(v868, 1.5);
        v468 = 20;
LABEL_635:
        v28->m_Kemuri_Cnt = v468;
        goto LABEL_744;
      }
      v677 = v28->m_KabeCnt;
      v28->m_Intercept_AiCnt = 0;
      v679 = ToX.n64_f32[0];
      v680 = v822[0];
      v28->m_KabeCnt = v677 + 1;
      v681 = gEnemyWork_local->m_PlayerPos.x;
      v682 = gEnemyWork_local->m_PlayerPos.z;
      PosToDir = sBtlGetPosToDir(v679, v680, v681, v682);
      v819 = ToX.n64_u64[0];
      *(float32x2_t *)&v818.x = ToX;
      v818.z = v822[0];
      v820 = v822[0];
      sBtlGetMoveXZ(ToX.n64_f32[0], v822[0], PosToDir, 100.0, &v818.x, &v818.z);
      v684 = v818.x;
      v685 = *(f32 *)&v819;
      v686 = *((f32 *)&v819 + 1) + 25.0;
      v688 = v818.z;
      v689 = v818.y + 25.0;
      v690 = v820;
      *((f32 *)&v819 + 1) = *((f32 *)&v819 + 1) + 25.0;
      v818.y = v818.y + 25.0;
      if (!v691)
      v882.x = v684;
      v882.y = v689;
      v882.z = v688;
      v947.x = v685;
      v947.y = v686;
      v947.z = v690;
      if (mapCollision_PosToPosHitChk(v882, v947) == -1)
      {
        *(u64 *)&p_m_Intercept_ContactPos->x = *(u64 *)&v818.x;
        v763 = ToX.n64_u32[1];
        v28->m_Intercept_ContactPos.z = v818.z;
        LODWORD(v28->m_Intercept_ContactPos.y) = v763;
        goto LABEL_880;
      }
      playerX = v813;
      playerY = v815;
      if (!v28->m_Trap1)
      {
        v819 = ToX.n64_u64[0];
        v820 = v822[0];
        v764 = ToX.n64_f32[1] + 25.0;
        *(u64 *)&v818.x = *(u64 *)&p_m_PlayerPos->x;
        v765 = gEnemyWork_local->m_PlayerPos.z;
        *((f32 *)&v819 + 1) = ToX.n64_f32[1] + 25.0;
        v818.z = v765;
        v818.y = v818.y + 25.0;
        v766 = (f32)(ToX.n64_f32[1] + 25.0) - v818.y;
        if (v766 > -10.0 && v766 < 10.0)
        {
          v768 = v822[0];
          v769 = ToX.n64_f32[0];
          v770 = *(f32 *)&v819;
          v771 = v820;
          v894.y = frompos;
          v894.y = frompos;
          v894.x = v813;
          v894.z = v768;
          v959.x = v770;
          v959.y = v764;
          v959.z = v771;
          if (mapCollision_PosToPosHitChk(v894, v959) == -1)
          {
            v773 = *(u64 *)&v818.x;
            v774 = v818.z;
            v895.y = frompos;
            v895.x = v813;
            v895.z = v768;
            *(u64 *)&v960.x = v773;
            v960.z = v774;
            if (mapCollision_PosToPosHitChk(v895, v960) == -1)
            {
              v28->m_AssisttPos.z = v768;
              v28->m_AssisttPos.x = v813;
              v28->m_AssisttPos.y = v815;
              playerY = v815;
              goto LABEL_899;
            }
          }
          v776 = v819;
          v777 = v820;
          v896.y = frompos;
          v896.x = v769;
          v896.z = playerZ;
          *(u64 *)&v961.x = v776;
          v961.z = v777;
          playerY = v815;
          if (mapCollision_PosToPosHitChk(v896, v961) == -1)
          {
            v779 = *(u64 *)&v818.x;
            v780 = v818.z;
            v897.y = frompos;
            v897.x = v769;
            v897.z = playerZ;
            *(u64 *)&v962.x = v779;
            v962.z = v780;
            if (mapCollision_PosToPosHitChk(v897, v962) == -1)
            {
              v28->m_AssisttPos.x = v769;
              v28->m_AssisttPos.y = v815;
              v28->m_AssisttPos.z = playerZ;
LABEL_899:
              v27 = 15;
              goto LABEL_20;
            }
          }
        }
      }
      v28->m_Mot = 1;
LABEL_379:
      v326 = 0x40C000003F000000LL;
LABEL_385:
      *(u64 *)&v28->m_MotSpd = v326;
      goto LABEL_21;
    case 0xF:
      ++v28->m_AiCnt;
      if (v28->m_FAtk)
        goto LABEL_18;
      v42 = &v28->m_Pos;
      ToX.n64_u64[0] = *(u64 *)&v28->m_Pos.x;
      v274 = ToX.n64_u64[0];
      v822[0] = v28->m_Pos.z;
      v28->m_Mot = 4;
      v44 = v822[0];
      FromXYZ.n64_u64[0] = v274;
      v275 = v28->m_Trap1;
      *(u64 *)&v28->m_MotSpd = 0x404000003F800000LL;
      if (!v275)
      {
        v276 = v28->m_PopPos.x;
        v277 = v28->m_PopPos.y;
        v278 = v28->m_PopPos.z;
        *(float32x2_t *)&v913.x = FromXYZ;
        v842.x = v276;
        v842.y = v277;
        v842.z = v278;
        v913.z = v44;
        if (GetLenXYZ(v842, v913) > 1800.0)
          goto LABEL_479;
      }
      v279 = v28->m_Intercept_AiCnt - 1;
      _ZF = v28->m_Intercept_AiCnt == 1;
      v28->m_Intercept_AiCnt = v279;
      if (v279 >= 0 && !_ZF)
        goto LABEL_309;
      if (v28->m_Run_Stamina < 0 || v28->m_AkirameSwitchOn)
      {
        v393 = v28->m_Intercept_Spd;
        if (v393 <= 5.0)
        {
LABEL_479:
          --gEnemyWork_local->m_OikakeNum;
          goto LABEL_480;
        }
        v394 = v393 + -1.0;
LABEL_793:
        v28->m_Intercept_Spd = v394;
        goto LABEL_794;
      }
      v693 = v44;
      v694 = v28->m_Intercept_Spd;
      v695 = gMapEnemyDiffTbl[g_EnemySymbol_Diff]->m_InterceptAccel;
      v696 = v694 + (f32)(v695 + (f32)((f32)(u32)sub_1905740(200, 0) / 100.0));
      v394 = v28->m_Intercept_MaxSpd;
      v44 = v693;
      v28->m_Intercept_Spd = v696;
      if (v696 > v394)
        goto LABEL_793;
LABEL_794:
      v697 = gEnemyWork_local->m_PlayerPos.x;
      v698 = gEnemyWork_local->m_PlayerPos.z;
      v699 = gEnemyWork_local->m_PlayerDir;
      v700 = v28->m_Pos.x;
      v701 = v28->m_Pos.z;
      v28->m_Intercept_PtoEDir = sBtlGetDir_PosDirToPos(v697, v698, v699, v700, v701);
      v703 = gEnemyWork_local->m_PlayerSpd - v28->m_Intercept_Spd;
      v704 = v28->m_Pos.z;
      v705 = v28->m_Pos.x;
      v706 = v28->m_Pos.y;
      if (v703 < 0.0)
        v703 = -v703;
      if (v703 < 1.0)
        v703 = 1.0;
      v28->m_Intercept_Velocity = v703;
      v707 = gEnemyWork_local->m_PlayerPos.x;
      v708 = gEnemyWork_local->m_PlayerPos.y;
      v709 = gEnemyWork_local->m_PlayerPos.z;
      v883.x = v707;
      v883.y = v708;
      v883.z = v709;
      v948.x = v705;
      v948.y = v706;
      v948.z = v704;
      v710 = GetLenXYZ(v883, v948);
      v711 = v710 / v28->m_Intercept_Velocity;
      *(u64 *)&v28->m_Intercept_ContactPos.x = *(u64 *)&v28->m_AssisttPos.x;
      v28->m_Intercept_ContactPos.z = v28->m_AssisttPos.z;
      if (v711 > 40.0)
        v711 = 40.0;
      v28->m_Intercept_Range = v710;
      v28->m_Intercept_Time = v711;
      if (v710 > 3000.0 || v28->m_KabeCnt >= 181)
        goto LABEL_810;
      v819 = ToX.n64_u64[0];
      *(u64 *)&v818.x = *(u64 *)&p_m_PlayerPos->x;
      v713 = gEnemyWork_local->m_PlayerPos.z;
      v714 = ToX.n64_u64[0];
      v820 = v822[0];
      v716 = *(u64 *)&v818.x;
      v717 = ToX.n64_f32[1] + 25.0;
      v718 = v822[0];
      v818.z = v713;
      v719 = v713;
      v720 = v818.y + 25.0;
      *((f32 *)&v819 + 1) = ToX.n64_f32[1] + 25.0;
      v818.y = v818.y + 25.0;
      if (!v715)
      LODWORD(v884.x) = v716;
      v884.y = v720;
      v884.z = v719;
      LODWORD(v949.x) = v714;
      v949.y = v717;
      v949.z = v718;
      v721 = mapCollision_PosToPosHitChk(v884, v949);
      v28->m_KabeCnt = 0;
      if (v721 == -1)
        goto LABEL_313;
      v28->m_Run_AiCnt = sub_1905740(4, 0) + 4;
LABEL_309:
      v280 = v28->m_AssisttPos.x;
      v281 = v28->m_AssisttPos.y;
      v282 = v28->m_AssisttPos.z;
      v283 = ToX.n64_u64[0];
      v284 = v822[0];
      v843.x = v280;
      v843.y = v281;
      v843.z = v282;
      *(u64 *)&v914.x = v283;
      v914.z = v284;
      if (GetLenXYZ(v843, v914) < v28->m_Intercept_Spd)
      {
        v28->m_KabeCnt = 0;
LABEL_313:
        v28->m_Run_AiCnt = 0;
        v285 = 14;
        goto LABEL_811;
      }
      v395 = v28->m_PopPos.x;
      v396 = v28->m_PopPos.y;
      v397 = v28->m_PopPos.z;
      v398 = ToX.n64_u64[0];
      v399 = v822[0];
      v855.x = v395;
      v855.y = v396;
      v855.z = v397;
      *(u64 *)&v925.x = v398;
      v925.z = v399;
      if (GetLenXYZ(v855, v925) >= 600.0)
      {
        v400 = v28->m_Intercept_Stamina;
      }
      else
      {
        v400 = v28->m_Intercept_Stamina;
        if ((v28->m_AiCnt & 3) != 0)
          goto LABEL_593;
      }
      v28->m_Intercept_Stamina = --v400;
LABEL_593:
      if (v400 < 0)
      {
        v499 = v28->m_Intercept_Spd;
        if (v499 > 5.0)
          v28->m_Intercept_Spd = v499 + -1.0;
      }
      v500 = v28->m_Intercept_ContactPos.x;
      v501 = v28->m_Intercept_ContactPos.y;
      v502 = v28->m_Intercept_ContactPos.z;
      v503 = ToX.n64_u64[0];
      v504 = v822[0];
      v864.x = v500;
      v864.y = v501;
      v864.z = v502;
      *(u64 *)&v933.x = v503;
      v933.z = v504;
      v505 = GetLenXYZ(v864, v933);
      v506 = 1.0;
      if (v505 > 1.0)
      {
        v507 = v44;
        v508 = v505;
        v509 = v28->m_Intercept_ContactPos.x;
        v510 = v28->m_Intercept_ContactPos.z;
        v511 = ToX.n64_f32[0];
        v512 = v822[0];
        v513 = sBtlGetVecToDir((f32)(v509 - v511) / v508, (f32)(v510 - v512) / v508);
        v44 = v507;
        v28->m_Intercept_Dir = sBtlGetDir_Hokan(v28->m_Intercept_Dir, v513, 10.0);
      }
      v792 = p_m_Res_Devil;
      if (v28->m_Intercept_Range < 400.0 || v28->m_KabeCnt >= 31)
      {
        v372 = g_EnemySummonMax_local;
        v520 = gEnemyWork_local->m_PlayerPos.z;
        v521 = gEnemyWork_local->m_PlayerPos.x;
        v522 = gEnemyWork_local->m_PlayerPos.y;
        v523 = v822[0];
        v524 = ToX.n64_u64[0];
        v865.x = v521;
        v865.y = v522;
        v865.z = v520;
        *(u64 *)&v934.x = v524;
        v934.z = v523;
        v525 = GetLenXYZ(v865, v934);
        v526 = sBtlGetVecToDir((f32)(gEnemyWork_local->m_PlayerPos.x - ToX.n64_f32[0]) / v525, (f32)(gEnemyWork_local->m_PlayerPos.z - v822[0]) / v525);
        v527 = sBtlGetDir_Hokan(v28->m_Dir, v526, 5.0);
        v519 = v28->m_Intercept_Spd;
        v28->m_Dir = v527;
        v506 = 1.0;
      }
      else
      {
        v514 = v28->m_Dir;
        v515 = v28->m_Intercept_Dir;
        v516 = sBtlGetDir_Hokan(v514, v515, 5.0);
        v517 = v28->m_Intercept_Dir;
        v28->m_Dir = v516;
        AtoB_LR_ABS = sBtlGetAtoB_LR_ABS(v516, v517);
        v519 = v28->m_Intercept_Spd;
        v372 = g_EnemySummonMax_local;
        if (AtoB_LR_ABS > 10.0 && v519 > 5.0)
        {
          v519 = v519 + -1.0;
          v28->m_Intercept_Spd = v519;
        }
      }
      v373 = v3;
      v528 = ToX.n64_f32[0];
      v529 = v822[0];
      v530 = v28->m_Intercept_Dir;
      sBtlGetMoveXZ(v528, v529, v530, v519, &ToX, v822);
      v531 = 0;
      while (1)
      {
        if (v25 != v531)
        {
          v384 = gEnemyWork_local->m_Obj[v531];
          if (v384[2].n64_u8[0])
          {
            v532 = v384[6].n64_f32[0];
            v533 = v384[6].n64_f32[1];
            v534 = v384[7].n64_f32[0];
            *(float32x2_t *)&v866.x = FromXYZ;
            v866.z = v44;
            v935.x = v532;
            v935.y = v533;
            v935.z = v534;
            v383.n64_f32[0] = GetLenXYZ(v866, v935);
            if (v383.n64_f32[0] < v506)
              v383.n64_f32[0] = v506;
            if (v383.n64_f32[0] < 50.0)
              goto LABEL_624;
          }
        }
        if (++v531 == 40)
        {
LABEL_623:
          v535 = ToX.n64_u64[0];
          v536 = v822[0];
          goto LABEL_627;
        }
      }
    case 0x10:
      ++v28->m_AiCnt;
      if (v28->m_FAtk)
        goto LABEL_18;
      goto LABEL_9005;
      if (v28->m_FAtk)
      {
LABEL_18:
        --gEnemyWork_local->m_OikakeNum;
        goto LABEL_19;
      }
LABEL_9005:
      ToX.n64_u64[0] = *(u64 *)&v28->m_Pos.x;
      v822[0] = v28->m_Pos.z;
      v286 = ToX.n64_u64[0];
      v28->m_Mot = 4;
      v287 = v822[0];
      m_Run_AiCnt = v28->m_Run_AiCnt;
      *(u64 *)&v28->m_MotSpd = 0x404000003F800000LL;
      if (m_Run_AiCnt <= 15)
      {
        v28->m_Run_ContactPos.z = playerZ;
        v28->m_Run_ContactPos.x = playerX;
        v28->m_Run_ContactPos.y = v815;
        v289 = sBtlGetPosToDir(*(f32 *)&v286, v287, playerX, playerZ);
        v290 = v28->m_Run_AiCnt;
        v28->m_Rush_Dir = v289;
        v28->m_Run_AiCnt = v290 + 1;
      }
      v291 = v28->m_Run_Stamina - 1;
      v28->m_Run_Stamina = v291;
      if (v291 < 0 || v28->m_AkirameSwitchOn)
      {
        --gEnemyWork_local->m_OikakeNum;
        v27 = 10;
LABEL_322:
        playerY = v815;
        goto LABEL_20;
      }
      v442 = v28->m_Dir;
      m_Rush_Dir = v28->m_Rush_Dir;
      v444 = sBtlGetDir_Hokan(v442, m_Rush_Dir, 15.0);
      v445 = ToX.n64_u64[0];
      v28->m_Dir = v444;
      v446 = v28->m_Rush_Dir;
      v819 = v445;
      v820 = v822[0];
      sBtlGetMoveXZ(*(f32 *)&v445, v822[0], v446, 100.0, &v819, &v820);
      v447 = *(f32 *)&v819;
      LODWORD(v818.x) = v286;
      v449 = v820;
      v450 = *((f32 *)&v819 + 1) + 25.0;
      v818.y = *((f32 *)&v286 + 1) + 25.0;
      v818.z = v287;
      *((f32 *)&v819 + 1) = *((f32 *)&v819 + 1) + 25.0;
      if (!v451)
      LODWORD(v859.x) = v286;
      v859.y = *((f32 *)&v286 + 1) + 25.0;
      v859.z = v287;
      v929.x = v447;
      v929.y = v450;
      v929.z = v449;
      if (mapCollision_PosToPosHitChk(v859, v929) != -1)
        goto LABEL_810;
      v452 = ToX.n64_f32[0];
      v453 = v822[0];
      v454 = v28->m_Dir;
      v455 = v28->m_Run_Spd;
      sBtlGetMoveXZ(v452, v453, v454, v455, &ToX, v822);
      v457 = ToX.n64_f32[0];
      v458 = ToX.n64_f32[1] + -5.0;
      v459 = v28->m_Pos.z;
      v460 = v28->m_Pos.x;
      v461 = v28->m_Pos.y;
      v462 = v822[0];
      ToX.n64_f32[1] = ToX.n64_f32[1] + -5.0;
      v860.x = v460;
      v860.y = v461;
      v860.z = v459;
      v930.x = v457;
      v930.y = v458;
      v930.z = v462;
      mapCollisionHitChk2(v860, v930, &retpos, 0);
      v28->m_Pos = retpos;
      playerX = v813;
      playerY = v815;
      v463 = v28->m_Kemuri_Cnt - 1;
      _ZF = v28->m_Kemuri_Cnt == 1;
      v28->m_Kemuri_Cnt = v463;
      if (v463 < 0 || _ZF)
      {
        v465 = v28->m_Pos.x;
        v466 = v28->m_Pos.y;
        v467 = v28->m_Pos.z;
        v861.x = v465;
        v861.y = v466;
        v861.z = v467;
        mapDraw_KemuriReq_E(v861);
        v468 = sub_1905740(4, 0) + 10;
        goto LABEL_635;
      }
      goto LABEL_744;
    case 0x11:
      if (v28->m_Icon3D)
      {
        v63 = v28->m_ObjIdx;
        v28->m_Icon3D = 0;
        Delete(v63);
      }
      v64 = v28->m_AiCnt;
      if (!v64)
      {
        *(u64 *)&v28->m_QuakePos.x = *(u64 *)&v28->m_Pos.x;
        v28->m_QuakePos.z = v28->m_Pos.z;
        v28->m_QuakePow = 10;
      }
      m_Dead = v28->m_Dead;
      v66 = v64 + 1;
      v28->m_AiCnt = v66;
      _ZF = !m_Dead;
      v68 = *(u64 *)&v28->m_QuakePos.x;
      *(u64 *)&v28->m_MotSpd = 0x3F8000003F000000LL;
      ToX.n64_u64[0] = v68;
      if (_ZF)
        v69 = 5;
      else
        v69 = 6;
      v28->m_Mot = v69;
      m_QuakePow = v28->m_QuakePow;
      v822[0] = v28->m_QuakePos.z;
      if (m_QuakePow >= 1)
      {
        v71 = m_QuakePow;
        v72 = ToX.n64_f32[0];
        v28->m_QuakePow = m_QuakePow - 1;
        if ((v66 & 1) == 0)
          v71 = -(f32)m_QuakePow;
        ToX.n64_f32[0] = v72 + v71;
        v822[0] = v822[0] + v71;
      }
      *(float32x2_t *)&v28->m_Pos.x = ToX;
      v28->m_Pos.z = v822[0];
      if (v66 < 91)
        goto LABEL_21;
      v27 = 12;
      goto LABEL_20;
    case 0x15:
      v73 = v28->m_AiCnt;
      v28->m_Mot = 1;
      v74 = *(u64 *)&v28->m_Pos.x;
      v28->m_Trap1 = 1;
      v75 = v28->m_Pos.z;
      ToX.n64_u64[0] = v74;
      v822[0] = v75;
      v28->m_AiCnt = v73 + 1;
      m_hMdl_Basic = v28->m_hMdl_Basic;
      *(u64 *)&v28->m_MotSpd = 0x404000003F000000LL;
      if (!m_hMdl_Basic)
        goto LABEL_906;
      dds3ObjectBaseOffFlag(&v28->m_hMdl_Basic, 1u);
      m_EnemyScale = v28->m_EnemyScale;
      v964.w = 1.0;
      v964.x = m_EnemyScale;
      v964.y = m_EnemyScale;
      v964.z = m_EnemyScale;
      dds3SetSclPoseSet(&v28->m_hMdl_Basic, v964);
      if (v28->m_FAtk)
        goto LABEL_19;
      v818.z = playerZ;
      *(u64 *)&v818.x = __PAIR64__(LODWORD(v814), LODWORD(playerX));
      v819 = ToX.n64_u64[0];
      v292 = ToX.n64_f32[1];
      v820 = v822[0];
      *((f32 *)&v819 + 1) = ToX.n64_f32[1] + 35.0;
      if (!v293)
      if (sBtlGetABS(playerY - v292) < 120.0)
      {
        v294 = ToX.n64_u64[0];
        v295 = v822[0];
        v844.x = playerX;
        v844.y = playerY;
        v844.z = playerZ;
        *(u64 *)&v915.x = v294;
        v915.z = v295;
        if (GetLenXYZ(v844, v915) < 1500.0)
        {
          v297 = *(u64 *)&v818.x;
          v298 = v818.z;
          v299 = v819;
          v300 = v820;
          *(u64 *)&v845.x = v297;
          v845.z = v298;
          *(u64 *)&v916.x = v299;
          v916.z = v300;
          playerX = v813;
          playerY = v815;
          if (mapCollision_PosToPosHitChk(v845, v916) == -1)
            goto LABEL_397;
        }
      }
      v27 = 22;
      goto LABEL_20;
    case 0x16:
      if (v28->m_AiCnt < 21)
        goto LABEL_359;
      if (v28->m_FAtk)
        goto LABEL_19;
      goto LABEL_9006;
      if (v28->m_FAtk)
      {
LABEL_19:
        v27 = 17;
LABEL_20:
        *(u64 *)&v28->m_AiStep = v27;
        goto LABEL_21;
      }
LABEL_9006:
LABEL_359:
      if (!v28->m_hMdl_Basic)
      {
LABEL_906:
        v785 = 30;
        v786 = 10;
        v787 = 30;
        goto LABEL_907;
      }
      v28->m_Mot = 0;
      v319 = v28->m_AiCnt;
      *(u64 *)&v28->m_MotSpd = 1056964608;
      if (v319)
      {
        if (v319 != 1)
          goto LABEL_371;
        goto LABEL_367;
      }
      if (Set_NearPoint(v28))
      {
        v28->m_Trap1 = 1;
        if (v28->m_AiCnt != 1)
LABEL_367:
LABEL_371:
        v320 = v28->m_AiCnt + 1;
        v28->m_AiCnt = v320;
        if (4 * v25 + 40 < v320)
        {
          v321 = *(u64 *)&v28->m_Pos.x;
          *(u64 *)&v818.x = __PAIR64__(LODWORD(v814), LODWORD(playerX));
          v819 = v321;
          *(f32 *)&v321 = v28->m_Pos.z;
          v818.z = playerZ;
          v323 = v819;
          v820 = *(f32 *)&v321;
          v324 = *((f32 *)&v819 + 1) + 35.0;
          v325 = v820;
          *((f32 *)&v819 + 1) = *((f32 *)&v819 + 1) + 35.0;
          if (!(u32)v321)
          v847.x = playerX;
          v847.y = v814;
          v847.z = playerZ;
          LODWORD(v918.x) = v323;
          v918.y = v324;
          v918.z = v325;
          if (mapCollision_PosToPosHitChk(v847, v918) == -1)
          {
LABEL_397:
            v329 = gEnemyWork_local->m_OikakeNum + 1;
            v330 = 7;
LABEL_400:
            gEnemyWork_local->m_OikakeNum = v329;
            v28->m_KabeCnt = 0;
            *(u64 *)&v28->m_AiStep = v330;
            v28->m_NoDiscoTime = 0;
            v28->m_UroUroSE_Cnt = 0;
            v28->m_Icon_Anim = 0;
          }
          else
          {
            v28->m_AiStep = 0;
            v28->m_AiCnt = 0;
            v28->m_AiParam = sub_1905740(200, 0) + 60;
          }
        }
        goto LABEL_21;
      }
      v786 = 0;
      v787 = 60;
      v785 = 200;
LABEL_907:
      v28->m_AiStep = v786;
      v28->m_AiCnt = 0;
      v28->m_AiParam = sub_1905740(v785, 0) + v787;
      return;
    case 0x17:
      if (gEnemyWork_local->m_SummonNum >= g_EnemySummonMax_local)
        goto LABEL_480;
      v78 = gEnemyWork_local->m_PlayerPos.x;
      v79 = gEnemyWork_local->m_PlayerPos.y;
      v80 = gEnemyWork_local->m_PlayerPos.z;
      v81 = v28->m_Pos.x;
      v82 = v28->m_Pos.y;
      v83 = v28->m_Pos.z;
      v827.x = v78;
      v827.y = v79;
      v827.z = v80;
      v900.x = v81;
      v900.y = v82;
      v900.z = v83;
      if (GetLenXYZ(v827, v900) < 1500.0)
      {
        v28->m_Summon_WaitTime = 0;
        playerX = v813;
        playerY = v815;
        ++gEnemyWork_local->m_SummonNum;
        v28->m_Mot = 0;
        v87 = v28->m_Res_Type;
        *(u64 *)&v28->m_AiStep = 0x100000016LL;
        *(u64 *)&v28->m_Pos.x = *(u64 *)&v28->m_PopPos.x;
        v28->m_Pos.z = v28->m_PopPos.z;
        v28->m_Trap1 = 1;
        *(u64 *)&v28->m_MotSpd = 1056964608;
        if (v87)
        {
          p_m_Res_Devil_Idx = &v28->m_Res_Devil_Idx;
          p_m_Res_Avatar = p_m_Res_Devil;
          if (!v88)
            goto LABEL_120;
        }
        else
        {
          p_m_Res_Avatar = &gEnemyWork_local->m_Res_Avatar;
          p_m_Res_Devil_Idx = &v28->m_Res_Avatar_Idx;
          if (!v88)
LABEL_120:
        }
        AsdMdlSceneAddModel(v28, (s32)v84);
        v91 = (*p_m_Res_Avatar)[*p_m_Res_Devil_Idx];
        ++v91->m_NowLink;
        v28->m_CopyMdl = 0;
        if (!v28->m_hMdl_Basic)
          goto LABEL_537;
        dds3ObjectBaseOffFlag(&v28->m_hMdl_Basic, 1u);
        v92 = v28->m_EnemyScale;
        goto LABEL_536;
      }
      playerX = v813;
      playerY = v815;
      if (!Set_NearPoint(v28))
        goto LABEL_480;
      v28->m_Summon_WaitTime = 0;
      ++gEnemyWork_local->m_SummonNum;
      v28->m_Mot = 0;
      v437 = v28->m_Res_Type;
      *(u64 *)&v28->m_AiStep = 0x100000016LL;
      v28->m_Trap1 = 1;
      *(u64 *)&v28->m_MotSpd = 1056964608;
      if (v437)
      {
        p_m_Res_Avatar_Idx = &v28->m_Res_Devil_Idx;
        v440 = p_m_Res_Devil;
        if (v438)
          goto LABEL_529;
LABEL_528:
        goto LABEL_529;
      }
      v440 = &gEnemyWork_local->m_Res_Avatar;
      p_m_Res_Avatar_Idx = &v28->m_Res_Avatar_Idx;
      if (!v438)
        goto LABEL_528;
LABEL_529:
      AsdMdlSceneAddModel(v28, (s32)v1);
      v441 = (*v440)[*p_m_Res_Avatar_Idx];
      ++v441->m_NowLink;
      v28->m_CopyMdl = 0;
      if (!v28->m_hMdl_Basic)
        goto LABEL_537;
      dds3ObjectBaseOffFlag(&v28->m_hMdl_Basic, 1u);
      v92 = v28->m_EnemyScale;
LABEL_536:
      v969.w = 1.0;
      v969.x = v92;
      v969.y = v92;
      v969.z = v92;
      dds3SetSclPoseSet(&v28->m_hMdl_Basic, v969);
LABEL_537:
      v28->m_SceenAdd = 1;
      goto LABEL_21;
    case 0x19:
      v93 = v28->m_AiCnt;
      if (v93)
        goto LABEL_137;
      ++gEnemyWork_local->m_SummonNum;
      if (v28->m_Res_Type)
      {
        v96 = &v28->m_Res_Devil_Idx;
        v97 = p_m_Res_Devil;
        if (v95)
          goto LABEL_133;
LABEL_132:
        goto LABEL_133;
      }
      v97 = &gEnemyWork_local->m_Res_Avatar;
      v96 = &v28->m_Res_Avatar_Idx;
      if (!v95)
        goto LABEL_132;
LABEL_133:
      AsdMdlSceneAddModel(v28, (s32)v1);
      v99 = (*v97)[*v96];
      ++v99->m_NowLink;
      v28->m_Mot = 0;
      *(u16 *)&v28->m_SceenAdd = 1;
      *(u64 *)&v28->m_MotSpd = 1056964608;
      v100 = *v3;
      v101 = v28->m_Pos.x;
      v102 = v28->m_Pos.y;
      v103 = v28->m_Pos.z;
      v965.w = 0.0;
      v965.x = v101;
      v965.y = v102;
      v965.z = v103;
      fldSePlay3DSE_BaseVol(65561, 64, v965);
      v93 = v28->m_AiCnt;
LABEL_137:
      v104 = *(u64 *)&v28->m_Pos.x;
      v105 = v93 + 1;
      v28->m_AiCnt = v105;
      ToX.n64_u64[0] = v104;
      v822[0] = v28->m_Pos.z;
      if (v105 < 21)
        goto LABEL_21;
      if (v28->m_FAtk)
        goto LABEL_19;
      if (v28->m_AiCnt < 41)
        goto LABEL_21;
      v28->m_UroUroSE_Cnt = 0;
      *(_OWORD *)&v28->m_AiStep = xmmword_3CFE730;
      goto LABEL_379;
    case 0x1B:
      v106 = v28->m_AiCnt;
      if (v106)
        goto LABEL_146;
      ++gEnemyWork_local->m_SummonNum;
      if (v28->m_Res_Type)
      {
        v109 = &v28->m_Res_Devil_Idx;
        v110 = p_m_Res_Devil;
        if (v108)
          goto LABEL_145;
LABEL_144:
        goto LABEL_145;
      }
      v110 = &gEnemyWork_local->m_Res_Avatar;
      v109 = &v28->m_Res_Avatar_Idx;
      if (!v108)
        goto LABEL_144;
LABEL_145:
      AsdMdlSceneAddModel(v28, (s32)v1);
      v111 = (*v110)[*v109];
      ++v111->m_NowLink;
      *(u16 *)&v28->m_SceenAdd = 1;
      v106 = v28->m_AiCnt;
LABEL_146:
      v113 = &v28->m_Pos;
      v112 = *(u64 *)&v28->m_Pos.x;
      v114 = v106 + 1;
      v28->m_AiCnt = v114;
      ToX.n64_u64[0] = v112;
      v822[0] = v28->m_Pos.z;
      v28->m_Mot = 3;
      v28->m_Trap3 = 1;
      *(u64 *)&v28->m_MotSpd = 0x404000003F000000LL;
      m_ETrap3_MoveTime = v28->m_ETrap3_MoveTime;
      v116 = m_ETrap3_MoveTime;
      if (m_ETrap3_MoveTime == INFINITY)
        v117 = 0x80000000;
      else
        v117 = m_ETrap3_MoveTime;
      if (v114 <= v117)
      {
        v132 = v28->m_ETrap3_SPos.z;
        v133 = v28->m_ETrap3_MoveVec.z * (f32)v114;
        m_ETrap3_MoveHigh = v28->m_ETrap3_MoveHigh;
        v135 = v28->m_ETrap3_SPos.y + (f32)(v28->m_ETrap3_MoveVec.y * (f32)v114);
        ToX.n64_f32[0] = v28->m_ETrap3_SPos.x
                       + (f32)(v28->m_ETrap3_MoveVec.x * (f32)v114);
        v822[0] = v132 + v133;
        v136 = sub_188E3D0((f32)((f32)(180.0 / m_ETrap3_MoveTime) * (f32)v114) * 0.017453292);
        v28->m_Pos.z = v822[0];
        v114 = v28->m_AiCnt;
        ToX.n64_f32[1] = v135 + (f32)(m_ETrap3_MoveHigh * v136);
        m_ETrap3_MoveTime = v28->m_ETrap3_MoveTime;
        v113->n64_u64[0] = ToX.n64_u64[0];
        v116 = m_ETrap3_MoveTime;
      }
      else
      {
        v113->n64_u64[0] = *(u64 *)&v28->m_ETrap3_GPos.x;
        v28->m_Pos.z = v28->m_ETrap3_GPos.z;
      }
      v137 = v116 - 4;
      if (m_ETrap3_MoveTime == INFINITY)
        v137 = 2147483644;
      if (v114 >= v137)
      {
        ToX.n64_u64[0] = v113->n64_u64[0];
        v143 = ToX.n64_u64[0];
        v822[0] = v28->m_Pos.z;
        v144 = v822[0];
        v828.x = playerX;
        v828.y = playerY;
        v828.z = playerZ;
        *(u64 *)&v901.x = v143;
        v901.z = v144;
        v145 = GetLenXYZ(v828, v901);
        v142 = sBtlGetVecToDir((f32)(playerX - ToX.n64_f32[0]) / v145, (f32)(playerZ - v822[0]) / v145);
        v141 = v28->m_Dir;
        v140 = 10.0;
      }
      else
      {
        v138 = v28->m_Dir;
        m_ETrap3_GDir = v28->m_ETrap3_GDir;
        v140 = 2.0;
        v141 = v138;
        v142 = m_ETrap3_GDir;
      }
      v28->m_Dir = sBtlGetDir_Hokan(v141, v142, v140);
      v146 = v28->m_ETrap3_MoveTime;
      v147 = v146;
      v148 = v28->m_AiCnt;
      v149 = (s32)v146 - 4;
      if (v146 == INFINITY)
        v149 = 2147483644;
      if (v148 == v149)
      {
        v150 = v28->m_ETrap3_GPos.x;
        v151 = v28->m_ETrap3_GPos.y;
        v152 = v28->m_ETrap3_GPos.z;
        v153 = *v3;
        v829.y = (f32)(v151 / -100.0) + 0.1;
        v829.z = v152 / -100.0;
        v829.x = v150 / -100.0;
        addPlayerFootEffect_Pos(v829, 1.5);
        v146 = v28->m_ETrap3_MoveTime;
        v148 = v28->m_AiCnt;
        v147 = v146;
      }
      if (v146 == INFINITY)
        v147 = 0x80000000;
      if (v148 == v147)
      {
        dds3SetQuake(30, 0x28u);
        v148 = v28->m_AiCnt;
      }
      if (v148 != 8)
      v155 = v28->m_ETrap3_MoveTime;
      v156 = v155;
      if (v155 == INFINITY)
        v156 = 0x80000000;
      if (v28->m_AiCnt <= v156)
        goto LABEL_21;
      v157.n64_u64[0] = v113->n64_u64[0];
      *(u64 *)&v818.x = __PAIR64__(LODWORD(v814), LODWORD(playerX));
      v819 = v157.n64_u64[0];
      v157.n64_u32[0] = LODWORD(v28->m_Pos.z);
      v818.z = playerZ;
      v159 = v819;
      v820 = v157.n64_f32[0];
      v160 = *((f32 *)&v819 + 1) + 35.0;
      v161 = v820;
      *((f32 *)&v819 + 1) = *((f32 *)&v819 + 1) + 35.0;
      if (!v157.n64_u32[0])
      v830.x = playerX;
      v830.y = v814;
      v830.z = playerZ;
      LODWORD(v902.x) = v159;
      v902.y = v160;
      v902.z = v161;
      if (mapCollision_PosToPosHitChk(v830, v902) != -1)
      {
        v28->m_AiStep = 0;
        v28->m_AiCnt = 0;
        v28->m_AiParam = 10;
        goto LABEL_21;
      }
      v329 = gEnemyWork_local->m_OikakeNum + 1;
      v330 = 0x600000007LL;
      goto LABEL_400;
    case 0x1D:
      v118 = v28->m_AiCnt;
      if (v118)
        goto LABEL_159;
      ++gEnemyWork_local->m_SummonNum;
      if (v28->m_Res_Type)
      {
        v121 = &v28->m_Res_Devil_Idx;
        v122 = p_m_Res_Devil;
        if (v120)
          goto LABEL_155;
LABEL_154:
        goto LABEL_155;
      }
      v122 = &gEnemyWork_local->m_Res_Avatar;
      v121 = &v28->m_Res_Avatar_Idx;
      if (!v120)
        goto LABEL_154;
LABEL_155:
      AsdMdlSceneAddModel(v28, (s32)v1);
      v124 = (*v122)[*v121];
      ++v124->m_NowLink;
      v28->m_Mot = 0;
      *(u16 *)&v28->m_SceenAdd = 1;
      *(u64 *)&v28->m_MotSpd = 1056964608;
      v125 = *v3;
      v126 = v28->m_Pos.x;
      v127 = v28->m_Pos.y;
      v128 = v28->m_Pos.z;
      v966.w = 0.0;
      v966.x = v126;
      v966.y = v127;
      v966.z = v128;
      fldSePlay3DSE_BaseVol(65561, 64, v966);
      v118 = v28->m_AiCnt;
LABEL_159:
      v129 = *(u64 *)&v28->m_Pos.x;
      v130 = v118 + 1;
      v28->m_Trap4 = 1;
      v131 = v28->m_Pos.z;
      v28->m_AiCnt = v130;
      ToX.n64_u64[0] = v129;
      v822[0] = v131;
      if (v130 == 8)
      {
        EnemySe(v28, 1);
        v130 = v28->m_AiCnt;
      }
      if (v130 < 21)
        goto LABEL_21;
      if (v28->m_FAtk)
        goto LABEL_19;
      if (v28->m_AiCnt < 81)
        goto LABEL_21;
      __asm { FMOV            V0.2S, #30.0 }
      v28->m_Run_Stamina = 300;
      v28->m_Run_AiCnt = 0;
      v28->m_UroUroSE_Cnt = 0;
      *(u64 *)&v28->m_Run_Spd = _D0;
      v326 = 0x404000003F000000LL;
      *(_OWORD *)&v28->m_AiStep = xmmword_3D04D40;
      goto LABEL_385;
    default:
      goto LABEL_21;
  }
}

// 0x1b79280
static void InOutUpdate(void) {
  s64 v2;
  TYPE_ENEMYWORK *gEnemyWork_local;
  s64 v4;
  f32 v5;
  f32 v6;
  f32 v7;
  unsigned __int128 v8;

  v2 = 32;
  gEnemyWork_local = gEnemyWork;
  v8 = 0u;
  do
  {
    v4 = *(s64 *)((char *)&gEnemyWork_local->m_Obj->obj.klass + v2);
    if (*(u8 *)(v4 + 16))
    {
      v5 = *(f32 *)(v4 + 48);
      v6 = *(f32 *)(v4 + 52);
      v7 = *(f32 *)(v4 + 56);
      *(u8 *)(v4 + 132) = sBtlChangeWorldtoScreenUnity3(v5, v6, v7, &v8);
    }
    v2 += 8;
  }
  while (v2 != 352);
}

// 0x1b79380
static void mapEnemy_Update(void) {
  TYPE_ENEMYWORK *gEnemyWork_local;
  GlobalWork_t *fldGb_local;
  s64 v5;
  f32 PlayerKakudo;
  s64 v12;
  TYPE_ENEMYOBJ *v13;
  u32 m_AiStep;
  bool v15;
  s32 v16;
  f32 x;
  f32 y;
  f32 m_Dir;
  f32 z;
  f32 m_EnemyScale;
  f32 v25;
  f32 v26;
  f32 m_DitherAlpha;
  dds3ModelHandle_t *m_hMdl_Model;
  s32 m_EnemySize;
  s32 m_Res_Avatar_Idx;
  s32 v32;
  s32 m_Mot;
  f32 m_MotHokan;
  f32 m_MotSpd;
  dds3ModelHandle_t *v37;
  u32 v38;
  s32 v39;
  sdfVector3_t v41;
  sdfVector3_t v42;
  sdfVector4_t v43;
  sdfVector4_t v44;

  gEnemyWork_local = gEnemyWork;
  if (dds3AdminiGetNextSequence() != -1)
    return;
  if (!cmpProcessCheck())
  {
    fldGb_local = fldGb;
    v5 = *(u64 *)&fldGb_local->playerX;
    gEnemyWork_local->m_PlayerSpd = 0.0;
    gEnemyWork_local->m_PlayerVec.y = 0.0;
    *(u64 *)&gEnemyWork_local->m_PlayerPos.x = v5;
    *(f32 *)&v5 = fldGb_local->playerZ;
    PlayerKakudo = fldGb_local->PlayerKakudo;
    LODWORD(gEnemyWork_local->m_PlayerPos.z) = v5;
    gEnemyWork_local->m_PlayerDir = PlayerKakudo;
    if (!(u32)fldGb_local)
    sBtlGetMoveXZ(0.0, 0.0, PlayerKakudo, 0.0, &gEnemyWork_local->m_PlayerVec.x, &gEnemyWork_local->m_PlayerVec.z);
    if (!fldDbg->MenuOn)
    {
      if (fldProcCheckFlag(0x40u))
      {
        if (g_NoEnemyDiscoTime >= 1)
        {
          g_NoEnemyDiscoTime = g_NoEnemyDiscoTime - 1;
        }
        AI_Update();
      }
    }
    InOutUpdate();
    v12 = 32;
    while (1)
    {
      v13 = *(TYPE_ENEMYOBJ *)((char *)&gEnemyWork_local->m_Obj->obj.klass + v12);
      if (!v13->m_Use)
        goto LABEL_32;
      m_AiStep = v13->m_AiStep;
      v15 = m_AiStep > 0x10;
      v16 = (1 << m_AiStep) & 0x1C3F3;
      if (!v15 && v16 != 0 && v13->m_Icon3D)
      {
        v41.z = v13->m_Pos.z;
        v41.x = v13->m_Pos.x;
        v41.y = v13->m_Pos.y + -200.0;
        OnVisible(v13->m_ObjIdx, v41, 0);
        if (!v13->m_Use)
          goto LABEL_32;
      }
      if (!v13->m_SceenAdd)
        goto LABEL_32;
      if (v13->m_hMdl_Basic)
        break;
LABEL_86:
      v38 = v13->m_AiStep;
      v15 = v38 > 0x10;
      v39 = (1 << v38) & 0x1C3F3;
      if (!v15 && v39 != 0 && v13->m_Icon3D)
      {
        v42.z = v13->m_Pos.z;
        v42.x = v13->m_Pos.x;
        v42.y = v13->m_Pos.y + -200.0;
        OnVisible(v13->m_ObjIdx, v42, 0);
      }
LABEL_32:
      v12 += 8;
      if (v12 == 352)
        return;
    }
    x = v13->m_Pos.x;
    y = v13->m_Pos.y;
    z = v13->m_Pos.z;
    m_Dir = v13->m_Dir;
    if (!v13->m_hMdl_Basic && dds3ObjectBaseCheckFlag(&v13->m_hMdl_Basic, 1))
    {
      dds3ObjectBaseOffFlag(&v13->m_hMdl_Basic, 1u);
      m_EnemyScale = v13->m_EnemyScale;
      v43.x = m_EnemyScale;
      v43.y = m_EnemyScale;
      v43.z = m_EnemyScale;
      v43.w = 1.0;
      dds3SetSclPoseSet(&v13->m_hMdl_Basic, v43);
    }
    v44.y = y + 0.0;
    v44.w = 0.0;
    v44.x = x;
    v44.z = z;
    dds3SetPosPoseSet(&v13->m_hMdl_Basic, v44);
    AsdMdlSetRotationXYZ(v13, v25, m_Dir, v26);
    m_DitherAlpha = v13->m_DitherAlpha;
    m_hMdl_Model = v13->m_hMdl_Model;
    mdlSetDitherAlpha(m_hMdl_Model, m_DitherAlpha);
    m_EnemySize = v13->m_EnemySize;
    if (m_EnemySize == 1)
      goto LABEL_77;
    if (v13->m_Res_Type)
    {
      goto LABEL_77;
    }
    if (m_EnemySize == 3)
    {
      m_Res_Avatar_Idx = v13->m_Res_Avatar_Idx;
      v32 = 3;
    }
    else
    {
      if (m_EnemySize != 2)
        goto LABEL_77;
      m_Res_Avatar_Idx = v13->m_Res_Avatar_Idx;
      v32 = 2;
    }
    GetSizeTable(v32, m_Res_Avatar_Idx);
LABEL_77:
    m_Mot = v13->m_Mot;
    if (m_Mot != v13->m_MotOld)
    {
      v13->m_MotOld = m_Mot;
      m_MotHokan = v13->m_MotHokan;
      AsdModelSetChrAnmNo(v13, m_Mot, m_MotHokan);
      m_MotSpd = v13->m_MotSpd;
      v37 = v13->m_hMdl_Model;
      if (v37)
      {
        mdlSetMotionSpeed(v37, m_MotSpd);
      }
    }
    goto LABEL_86;
  }
}

// 0x1b79ee0
static void mapEnemy_FAtkUpdate(void) {
  TYPE_ENEMYWORK *gEnemyWork_local;
  u32 v4;
  _BOOL4 v6;
  bool v8;
  bool v9;
  f32 v10;
  s64 v11;
  u8 v12;
  f32 v13;
  s32 v14;
  TYPE_ENEMYOBJ *v15;
  u32 m_AiStep;
  s32 v17;
  f32 x;
  f32 y;
  f32 z;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 LenXYZ_33399936;
  f32 ABS;
  bool v27;
  s64 m_FAtkObjIdx;
  char v29;
  s32 v31;
  char v32;
  u32 v33;
  s32 m_FAtkStep;
  s32 v37;
  s32 v39;
  TYPE_ENEMYOBJ *v44;
  char *v46;
  char *v47;
  s32 m_Item;
  char *v49;
  char *v50;
  s64 v51;
  TYPE_ENEMYOBJ *v52;
  f32 v53;
  f32 v54;
  f32 v55;
  long f64 v56;
  TYPE_ENEMYOBJ *m_Obj;
  TYPE_ENEMYOBJ *v60;
  f32 v61;
  f32 v62;
  f32 v63;
  f32 v64;
  f32 PosToDir;
  s32 m_Lv;
  TYPE_ENEMYOBJ *v71;
  f32 v72;
  f32 v73;
  f32 v74;
  f32 v75;
  f32 v76;
  f32 v77;
  s64 v78;
  f32 v79;
  f32 v80;
  f32 v81;
  TYPE_ENEMYOBJ *v84;
  s32 v87;
  s64 v90;
  TYPE_ENEMYOBJ *v91;
  f32 v92;
  f32 v93;
  f32 v94;
  long f64 v95;
  f32 v96;
  f32 v97;
  f32 v98;
  f32 v99;
  f32 v100;
  f32 v101;
  f32 v102;
  s32 m_ObjIdx;
  bool v104;
  s64 v105;
  s64 v106;
  s64 v107;
  s64 v108;
  sdfVector3_t v109;
  sdfVector3_t v110;
  sdfVector3_t v111;
  sdfVector3_t v112;
  sdfVector3_t v113;
  sdfVector3_t v114;
  sdfVector4_t v115;
  sdfVector4_t v116;
  sdfVector4_t v117;
  sdfVector4_t v118;

  v107 = 0;
  v108 = 0;
  v105 = 0;
  v106 = 0;
  goto LABEL_3;
  if (v4)
  {
LABEL_3:
    gEnemyWork_local = gEnemyWork;
    if (dds3AdminiGetNextSequence() != -1)
      return;
    goto LABEL_7;
  }
  gEnemyWork_local = gEnemyWork;
  if (dds3AdminiGetNextSequence() != -1)
    return;
LABEL_7:
  if (cmpProcessCheck())
    return;
  if (fldGb->nakamaMode)
  {
    if (gEnemyWork_local->m_FAtkObjIdx != -1)
    {
      DeleteAll();
      gEnemyWork_local->m_FAtkStep = 0;
      gEnemyWork_local->m_FAtkIcon = 0;
      gEnemyWork_local->m_FAtkObjIdx = -1;
    }
    return;
  }
  v6 = !fldProcCheckFlag(0x40u);
  v8 = fldGb->NoInpPlCnt != 0 || v6;
  v104 = v8;
  if (summonDvModel)
    v9 = CHECK_TRIG(8203, 1) && !v8;
  else
    v9 = 0;
  v10 = 99999.0;
  v11 = 0;
  v12 = 0;
  v13 = 99999.0;
  v14 = -1;
  do
  {
    v15 = gEnemyWork_local->m_Obj[v11];
    if (v15->m_Use)
    {
      m_AiStep = v15->m_AiStep;
      v32 = m_AiStep > 0xF;
      v17 = (1 << m_AiStep) & 0xC361;
      if (!v32 && v17 != 0)
      {
        x = gEnemyWork_local->m_PlayerPos.x;
        y = gEnemyWork_local->m_PlayerPos.y;
        z = gEnemyWork_local->m_PlayerPos.z;
        v22 = v15->m_Pos.x;
        v23 = v15->m_Pos.y;
        v24 = v15->m_Pos.z;
        v109.x = x;
        v109.y = y;
        v109.z = z;
        v113.x = v22;
        v113.y = v23;
        v113.z = v24;
        LenXYZ_33399936 = GetLenXYZ(v109, v113);
        ABS = sBtlGetABS(gEnemyWork_local->m_PlayerPos.y - v15->m_Pos.y);
        v27 = LenXYZ_33399936 < 800.0 && ABS < 150.0;
        if (v27)
        {
          m_FAtkObjIdx = (u32)gEnemyWork_local->m_FAtkObjIdx;
          if ((u32)m_FAtkObjIdx != -1 && (v11 != m_FAtkObjIdx ? (v29 = 0) : (v13 = LenXYZ_33399936, v29 = 1), v12 |= v29, v9))
          {
            if (v11 != m_FAtkObjIdx && LenXYZ_33399936 < v10)
            {
              v10 = LenXYZ_33399936;
              v14 = v11;
            }
          }
          else if (LenXYZ_33399936 < v10)
          {
            v10 = LenXYZ_33399936;
            v14 = v11;
          }
        }
      }
    }
    ++v11;
  }
  while (v11 != 40);
  if (summonDvModel)
  {
    if (v9)
    {
      v31 = gEnemyWork_local->m_FAtkObjIdx;
      if ((v12 & (v14 == -1)) == 0)
      {
        v32 = (v31 != -1) & __CFADD__(v31, 1);
        if (v31 == -1 || (v33 = gEnemyWork_local->m_FAtkStep, v32 = v33 > 1, v33 != 1))
        {
          v31 = v14;
          m_FAtkStep = gEnemyWork_local->m_FAtkStep;
        }
        else
        {
          Cng(gEnemyWork_local->m_Obj[v31]->m_ObjIdx, 0);
          sBtlPlaySE(0x10061u);
          v31 = v14;
          m_FAtkStep = gEnemyWork_local->m_FAtkStep;
          v32 = (u32)m_FAtkStep > 0xA;
          if (m_FAtkStep > 10)
            goto LABEL_70;
        }
        goto LABEL_102;
      }
    }
    else if ((v12 & 1) != 0)
    {
      v31 = gEnemyWork_local->m_FAtkObjIdx;
      if ((f32)(v13 - v10) > 600.0 || v14 == v31)
        v31 = v14;
    }
    else
    {
      v31 = v14;
    }
  }
  else
  {
    v31 = -1;
  }
  m_FAtkStep = gEnemyWork_local->m_FAtkStep;
  v32 = (u32)m_FAtkStep > 0xA;
  if (m_FAtkStep > 10)
  {
LABEL_70:
    switch (m_FAtkStep)
    {
      case 11:
        mapEnemy_SetFAtk_PlayerDir();
        v39 = gEnemyWork_local->m_FAtkStepCnt + 1;
        v27 = gEnemyWork_local->m_FAtkStepCnt - 59 < 0;
        gEnemyWork_local->m_FAtkStepCnt = v39;
        if (v27 == __OFSUB__(v39, 60))
        {
          if (!fldDbg->EncountOn)
          {
            if (!fldDbg->EncountBtnOn)
            {
              *(u64 *)&gEnemyWork_local->m_FAtkStep = 0;
              g_AttackEncCnt = 0;
            }
          }
        }
        break;
      case 20:
        mapEnemy_SetFAtk_PlayerDir();
        v44 = gEnemyWork_local->m_Obj[gEnemyWork_local->m_FAtkObjIdx];
        mapSet1StDone(v44->m_PopTableIdx);
        v46 = ToString((s32)v44 + 388, 0);
        v47 = Concat_54766928("EXP ", v46, 0);
        expReqDrawExpUpText(v47, 90);
        m_Item = v44->m_Item;
        if (m_Item)
        {
          v49 = sdatItemName(m_Item);
          v50 = Concat_54766928("ITEM ", v49, 0);
          expReqDrawExpUpText(v50, 90);
        }
        v51 = 21;
LABEL_100:
        *(u64 *)&gEnemyWork_local->m_FAtkStep = v51;
        break;
      case 21:
        mapEnemy_SetFAtk_PlayerDir();
        v37 = gEnemyWork_local->m_FAtkStepCnt + 1;
        v27 = gEnemyWork_local->m_FAtkStepCnt - 59 < 0;
        gEnemyWork_local->m_FAtkStepCnt = v37;
        if (v27 == __OFSUB__(v37, 60))
        {
          *(u64 *)&gEnemyWork_local->m_FAtkStep = 0;
          gEnemyWork_local->m_FAtkObjIdx = -1;
        }
        break;
    }
    return;
  }
LABEL_102:
  if (!v32)
  {
    switch (m_FAtkStep)
    {
      case 0:
        if (v31 != -1 && !v104)
        {
          gEnemyWork_local->m_FAtkObjIdx = v31;
          gEnemyWork_local->m_FAtkStep = 1;
          gEnemyWork_local->m_FAtkIcon = 1;
          v52 = gEnemyWork_local->m_Obj[v31];
          v53 = v52->m_Pos.x;
          v54 = v52->m_Pos.y;
          v55 = v52->m_Pos.z;
          if (sdfModelGetMarkPos(v52->m_hMdl_Model->modelRoot, 0))
          {
            v107 = 0;
            v108 = 0;
            sub_1B335A0(&v107, 0, v56);
            v110.y = *((f32 *)&v107 + 1);
            v53 = *(f32 *)&v107;
            v55 = *(f32 *)&v108;
          }
          else
          {
            v110.y = v54 + -100.0;
          }
          v110.x = v53;
          v110.z = v55;
          Add(v52->m_ObjIdx, v110, 0);
        }
        return;
      case 1:
        if (v31 == -1)
        {
          DeleteAll();
          gEnemyWork_local->m_FAtkStep = 0;
          gEnemyWork_local->m_FAtkIcon = 0;
          gEnemyWork_local->m_FAtkObjIdx = -1;
        }
        else if (v31 == gEnemyWork_local->m_FAtkObjIdx)
        {
          if (summonDvModel && !(v104 | !CHECK_TRIG(8195, 1)))
          {
            DeleteAll();
            m_Obj = gEnemyWork_local->m_Obj;
            gEnemyWork_local->m_FAtkIcon = 0;
            v60 = m_Obj[gEnemyWork_local->m_FAtkObjIdx];
            *(u64 *)&gEnemyWork_local->m_FAtkGoalPos.x = *(u64 *)&v60->m_Pos.x;
            gEnemyWork_local->m_FAtkGoalPos.z = v60->m_Pos.z;
            fldGetSummonDvPos(&gEnemyWork_local->m_FAtkNakamaPos.x, &gEnemyWork_local->m_FAtkNakamaPos.y, &gEnemyWork_local->m_FAtkNakamaPos.z);
            v61 = gEnemyWork_local->m_FAtkNakamaPos.x;
            v62 = gEnemyWork_local->m_FAtkNakamaPos.z;
            v63 = v60->m_Pos.x;
            v64 = v60->m_Pos.z;
            PosToDir = sBtlGetPosToDir(v61, v62, v63, v64);
            gEnemyWork_local->m_FAtkNakamaDir = PosToDir;
            gEnemyWork_local->m_FAtkNakamaDir = sBtlGetDirZ180(PosToDir);
            v115.w = 0.0;
            v60->m_FAtk = 1;
            v115.x = gEnemyWork_local->m_FAtkNakamaPos.x;
            v115.y = gEnemyWork_local->m_FAtkNakamaPos.y;
            v115.z = gEnemyWork_local->m_FAtkNakamaPos.z;
            fldSePlay3DSE_BaseVol(65579, 127, v115);
            v116.x = gEnemyWork_local->m_FAtkNakamaPos.x;
            v116.y = gEnemyWork_local->m_FAtkNakamaPos.y;
            v116.w = 0.0;
            v116.z = gEnemyWork_local->m_FAtkNakamaPos.z;
            mapSeNakamaPlay3DSE(6, 127, v116);
            v117.x = gEnemyWork_local->m_PlayerPos.x;
            v117.y = gEnemyWork_local->m_PlayerPos.y;
            v117.w = 0.0;
            v117.z = gEnemyWork_local->m_PlayerPos.z;
            fldSePlay3DSE_BaseVol(65627, 127, v117);
            m_Lv = v60->m_Lv;
            if (m_Lv <= GBWK->player->para->level - 5)
              v60->m_Dead = 1;
            gEnemyWork_local->m_FAtkStep = 2;
            mdlSetMotionSpeed(playerModel, 0.5);
            mdlSmoothSingleMotion(playerModel, 0, 48, 2.0, 2.0, 0.0);
            gEnemyWork_local->m_FAtkRaidoMotion = 1;
          }
        }
        else
        {
          gEnemyWork_local->m_FAtkObjIdx = v31;
        }
        if (gEnemyWork_local->m_FAtkIcon)
        {
          v90 = gEnemyWork_local->m_FAtkObjIdx;
          if ((u32)v90 != -1)
          {
            v91 = gEnemyWork_local->m_Obj[v90];
            v92 = v91->m_Pos.x;
            v93 = v91->m_Pos.y;
            v94 = v91->m_Pos.z;
            if (sdfModelGetMarkPos(v91->m_hMdl_Model->modelRoot, 0))
            {
              v105 = 0;
              v106 = 0;
              sub_1B335A0(&v105, 0, v95);
              v112.y = *((f32 *)&v105 + 1);
              v92 = *(f32 *)&v105;
              v94 = *(f32 *)&v106;
            }
            else
            {
              v112.y = v93 + -100.0;
            }
            m_ObjIdx = v91->m_ObjIdx;
            if (v104)
            {
              OffVisible(m_ObjIdx, 0);
            }
            else
            {
              v112.x = v92;
              v112.z = v94;
              OnVisible(m_ObjIdx, v112, 0);
            }
          }
        }
        return;
      case 2:
        mapEnemy_SetFAtk_PlayerDir();
        v71 = gEnemyWork_local->m_Obj[gEnemyWork_local->m_FAtkObjIdx];
        if (v71->m_Use)
        {
          v72 = v71->m_Pos.x;
          v73 = gEnemyWork_local->m_FAtkNakamaPos.x;
          gEnemyWork_local->m_FAtkGoalPos.x = v72;
          v74 = v71->m_Pos.y;
          v75 = gEnemyWork_local->m_FAtkNakamaPos.y;
          gEnemyWork_local->m_FAtkGoalPos.y = v74;
          v76 = gEnemyWork_local->m_FAtkNakamaPos.z;
          v77 = v71->m_Pos.z;
          gEnemyWork_local->m_FAtkGoalPos.z = v77;
          v111.x = v73;
          v111.y = v75;
          v111.z = v76;
          v114.x = v72;
          v114.y = v74;
          v114.z = v77;
          if (GetLenXYZ(v111, v114) >= 100.0)
          {
            v96 = gEnemyWork_local->m_FAtkNakamaPos.x;
            v97 = gEnemyWork_local->m_FAtkNakamaPos.y;
            v98 = gEnemyWork_local->m_FAtkNakamaPos.z;
            v99 = gEnemyWork_local->m_FAtkGoalPos.x;
            v100 = gEnemyWork_local->m_FAtkGoalPos.y;
            v101 = gEnemyWork_local->m_FAtkGoalPos.z;
            GetMovePosToPos(v96, v97, v98, v99, v100, v101, 100.0, &gEnemyWork_local->m_FAtkNakamaPos.x, &gEnemyWork_local->m_FAtkNakamaPos.y, &gEnemyWork_local->m_FAtkNakamaPos.z);
            v102 = sBtlGetPosToDir(gEnemyWork_local->m_FAtkNakamaPos.x, gEnemyWork_local->m_FAtkNakamaPos.z, v71->m_Pos.x, v71->m_Pos.z);
            gEnemyWork_local->m_FAtkNakamaDir = v102;
            gEnemyWork_local->m_FAtkNakamaDir = sBtlGetDirZ180(v102);
          }
          else
          {
            v78 = *(u64 *)&gEnemyWork_local->m_FAtkGoalPos.x;
            gEnemyWork_local->m_FAtkStep = 3;
            *(u64 *)&gEnemyWork_local->m_FAtkNakamaPos.x = v78;
            gEnemyWork_local->m_FAtkNakamaPos.z = gEnemyWork_local->m_FAtkGoalPos.z;
            Add_Fld(v71->m_Pos.x, v71->m_Pos.y + -150.0, v71->m_Pos.z, v71->m_Dir, 1.0, 0);
            Add_Fld(v71->m_Pos.x, v71->m_Pos.y + -150.0, v71->m_Pos.z);
            v79 = v71->m_Pos.x;
            v80 = v71->m_Pos.y;
            v81 = v71->m_Pos.z;
            v118.w = 0.0;
            v118.x = v79;
            v118.y = v80;
            v118.z = v81;
            fldSePlay3DSE_BaseVol(0x10000, 127, v118);
            dds3SetQuake(20, 0x3Cu);
          }
        }
        else
        {
          gEnemyWork_local->m_FAtkStep = 0;
          gEnemyWork_local->m_FAtkIcon = 0;
          gEnemyWork_local->m_FAtkObjIdx = -1;
        }
        return;
      case 3:
        mapEnemy_SetFAtk_PlayerDir();
        v84 = gEnemyWork_local->m_Obj[gEnemyWork_local->m_FAtkObjIdx];
        if (!v84->m_Use)
        {
          *(u64 *)&gEnemyWork_local->m_FAtkStep = 0;
          return;
        }
        if (!v84->m_Dead)
        {
          v51 = 10;
          goto LABEL_100;
        }
        *(u64 *)&gEnemyWork_local->m_FAtkStep = 20;
        EnemySe(v84, 8);
        break;
      case 4:
      case 5:
      case 6:
      case 7:
      case 8:
      case 9:
        return;
      case 10:
        mapEnemy_SetFAtk_PlayerDir();
        v87 = gEnemyWork_local->m_FAtkStepCnt + 1;
        v27 = gEnemyWork_local->m_FAtkStepCnt - 19 < 0;
        gEnemyWork_local->m_FAtkStepCnt = v87;
        if (v27 == __OFSUB__(v87, 20))
        {
          *(u64 *)&gEnemyWork_local->m_FAtkStep = 11;
          g_AttackEncCnt = 2;
          g_AttackEnemyObj = gEnemyWork_local->m_FAtkObjIdx;
        }
        return;
      default:
        goto LABEL_70;
    }
  }
}

// 0x1b7ac60
static void mapEnemy_SetFAtk_PlayerDir(void) {
  TYPE_ENEMYOBJ *v3;
  f32 m_PlayerDir;
  f32 x;
  f32 z;
  f32 v7;
  f32 v8;
  f32 PosToDir;
  f32 DirZ180;
  f32 AtoB_LR_ABS;
  f32 v12;
  f32 Dir_Hokan;
  f32 v16;
  f32 v21;
  f32 *p_x;
  f32 v25;
  f32 y;
  f32 v27;
  f32 w;
  sdfVector4_t v30;

  v3 = gEnemyWork->m_Obj[gEnemyWork->m_FAtkObjIdx];
  if (v3->m_Use)
  {
    m_PlayerDir = gEnemyWork->m_PlayerDir;
    x = gEnemyWork->m_PlayerPos.x;
    z = gEnemyWork->m_PlayerPos.z;
    v7 = v3->m_Pos.x;
    v8 = v3->m_Pos.z;
    PosToDir = sBtlGetPosToDir(x, z, v7, v8);
    DirZ180 = sBtlGetDirZ180(PosToDir);
    AtoB_LR_ABS = sBtlGetAtoB_LR_ABS(m_PlayerDir, DirZ180);
    if (AtoB_LR_ABS >= 120.0)
    {
      v12 = 15.0;
      goto LABEL_15;
    }
    else if (AtoB_LR_ABS >= 90.0)
    {
      v12 = 10.0;
LABEL_15:
      Dir_Hokan = sBtlGetDir_Hokan(m_PlayerDir, DirZ180, v12);
      v16 = Dir_Hokan;
      gEnemyWork->m_PlayerDir = v16;
      fldGb->PlayerKakudo = v16;
      fldGb->PlayerKakudoGoal = v16;
      vct_A = (struct sdfVector4_t)xmmword_3D015F0;
      v21 = RAD(fldGb->PlayerKakudo);
      FromRotation(v21);
      p_x = &vf00.x;
      v25 = p_x[4];
      y = p_x[5];
      v27 = p_x[6];
      w = p_x[7];
      v30.x = v25;
      v30.y = y;
      v30.z = v27;
      v30.w = w;
      dds3SetRotPoseSet(playerBasic, v30);
      return;
    }
    else
    {
      v12 = 5.0;
      goto LABEL_15;
    }
    goto LABEL_15;
  }
}

// 0x1b7af90
bool mapEnemy_GetFAtk(f32 *_X, f32 *_Y, f32 *_Z, f32 *_Dir) {
  u32 m_FAtkStep;
  bool v12;
  s32 v13;

  m_FAtkStep = gEnemyWork->m_FAtkStep;
  if ((m_FAtkStep & 0xFFFFFFFE) == 2)
    goto LABEL_11;
  goto LABEL_7;
  if ((m_FAtkStep & 0xFFFFFFFE) == 2)
  {
LABEL_11:
    *X = gEnemyWork->m_FAtkNakamaPos.x;
    *Y = gEnemyWork->m_FAtkNakamaPos.y;
    *Z = gEnemyWork->m_FAtkNakamaPos.z;
    *Dir = gEnemyWork->m_FAtkNakamaDir;
    return 1;
  }
LABEL_7:
  v12 = m_FAtkStep > 0x15;
  v13 = (1 << m_FAtkStep) & 0x300C00;
  if (!v12 && v13 != 0)
    goto LABEL_11;
  return 0;
}

// 0x1b7b0a0
bool mapEnemy_GetFAtkMotion(void) {
  dds3ModelHandle_t *v7;

  if (!gEnemyWork->m_FAtkRaidoMotion)
    return 0;
  if (!mdlChkMotionEnd(playerModel))
  {
    v7 = playerModel;
    if (v7->motionMinorNum == 48)
      return 1;
  }
  gEnemyWork->m_FAtkRaidoMotion = 0;
  return 0;
}

// 0x1b7b240
static dds3ProcessFunc_t slMapEnemy_Calc(dds3ProcessID_t *argsId) {
  TYPE_ENEMYWORK *gEnemyWork_local;
  u32 v6;
  dds3ProcessFunc_t result;

  gEnemyWork_local = gEnemyWork;
  if (fldDbg->InfoOn)
  {
    mapDebug_AiDraw();
    v6 = gEnemyWork_local->m_Step - 1;
    goto LABEL_13;
  }
  v6 = gEnemyWork_local->m_Step - 1;
  if (v6 > 9)
    return 0;
LABEL_13:
  switch (v6)
  {
    case 0u:
      *(u64 *)&gEnemyWork_local->m_Step = 2;
      return 0;
    case 2u:
      Reset_Calc();
      *(u64 *)&gEnemyWork_local->m_Step = 7;
      return 0;
    case 3u:
      SceneDel_Calc();
      goto LABEL_24;
    case 4u:
      MemFree_Calc();
LABEL_24:
      *(u64 *)&gEnemyWork_local->m_Step = (u32)(gEnemyWork_local->m_Step + 1);
      result = 0;
      break;
    case 5u:
      Reset_Calc();
      *(u64 *)&gEnemyWork_local->m_Step = 8;
      result = 0;
      break;
    case 7u:
      mapEnemy_Update();
      mapEnemy_FAtkUpdate();
      result = 0;
      break;
    case 8u:
      SceneDel_Calc();
      *(u64 *)&gEnemyWork_local->m_Step = 10;
      result = 0;
      break;
    case 9u:
      MemFree_Calc();
      *(u64 *)&gEnemyWork_local->m_Step = 0;
      result = 0;
      break;
    default:
      return 0;
  }
  return result;
}

// 0x1b7c0d0
bool mapChkSymbolEncount(void) {
  return gEnemyWork->m_EnemyNum > 0;
}

// 0x1b7c140
bool mapChkSymbolEncount_ScreenIn(void) {
  s64 m_FAtkObjIdx;
  TYPE_ENEMYOBJ *v4;
  f32 x;
  f32 y;
  f32 z;

  if (gEnemyWork->m_EnemyNum < 1)
    return 0;
  m_FAtkObjIdx = gEnemyWork->m_FAtkObjIdx;
  if ((u32)m_FAtkObjIdx != -1)
  {
    v4 = gEnemyWork->m_Obj[m_FAtkObjIdx];
    x = v4->m_Pos.x;
    y = v4->m_Pos.y;
    z = v4->m_Pos.z;
    if (sBtlChkWorldtoScreenIn(x, y + -100.0, z))
      return 1;
  }
  return 0;
}

// 0x1b7c260
void mapGetSymbolEncount_ZoomPos(f32 *_X, f32 *_Y, f32 *_Z) {
  s64 m_FAtkObjIdx;
  f32 v10;
  TYPE_ENEMYOBJ *v11;
  f32 playerY;
  f32 *p_z;
  GlobalWork_t *fldGb_local;

  if (gEnemyWork->m_EnemyNum >= 1)
  {
    m_FAtkObjIdx = gEnemyWork->m_FAtkObjIdx;
    if ((u32)m_FAtkObjIdx != -1)
    {
      v10 = -100.0;
      v11 = gEnemyWork->m_Obj[m_FAtkObjIdx];
      *X = v11->m_Pos.x;
      playerY = v11->m_Pos.y;
      p_z = &v11->m_Pos.z;
      goto LABEL_12;
    }
  }
  v10 = -80.0;
  fldGb_local = fldGb;
  *X = fldGb_local->playerX;
  playerY = fldGb_local->playerY;
  p_z = &fldGb_local->playerZ;
LABEL_12:
  *Y = playerY + v10;
  *Z = *p_z;
}

// 0x1b7c3a0
s32 mapEncountCheck(s32 *_EncountId, s32 *_EncountPackId, s32 *_Type2, s32 *_NakamaId, s32 *_EnemyId, s32 *_Map, s32 *_Field) {
  struct mapEnemy *static_fields;
  TYPE_ENEMYWORK *gEnemyWork_local;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;
  s32 v27;
  s32 v31;
  TYPE_ENEMYOBJ *m_Obj;
  TYPE_ENEMYOBJ *v33;
  s32 *p_m_EncountIdx;
  s64 m_PopTableIdx;
  s64 v40;
  s64 v41;
  s64 *v42;
  f32 LenXZ;
  s32 v45;
  f32 v50;
  f32 v51;
  f32 PosToDir;
  u32 v53;
  f32 v54;
  f32 v56;
  f32 v57;
  f32 v58;
  s32 v64;
  f32 v66;
  f32 v67;
  f32 v68;
  f32 v69;
  s32 *v70;
  s32 *v71;
  s32 *v72;
  s32 *v73;
  s32 *v74;
  s64 ToX;
  f32 v76;

  v76 = 0.0;
  gEnemyWork_local = gEnemyWork;
  ToX = 0;
  if (!!(u32)static_fields)
  {
    if (gEnemyWork_local->m_Step)
      goto LABEL_5;
    return -1;
  }
  if (!gEnemyWork_local->m_Step)
    return -1;
LABEL_5:
  v21 = fldGb[45];
  v22 = fldGb[43];
  v23 = fldGb[44];
  v24 = fldGb[52];
  if (fldDbg->EncountOn)
    goto LABEL_15;
  if (fldDbg->EncountBtnOn)
    goto LABEL_15;
  return 0;
LABEL_15:
  if (g_AttackEncCnt >= 1)
  {
    v31 = g_AttackEncCnt - 1;
    g_AttackEncCnt = v31;
    if (v31 == 1)
    {
      m_Obj = gEnemyWork_local->m_Obj;
      v33 = m_Obj[g_AttackEnemyObj];
      g_AttackEncGo = 1;
      p_m_EncountIdx = &v33->m_EncountIdx;
      *EncountId = v33->m_EncountIdx;
      *EncountPackId = v33->m_EncountPackIdx;
      *Type2 = 2;
      *NakamaId = GBWK->mapSummonID;
      *EnemyId = v33->m_EnemyId;
      *Map = v33->m_EncountMap;
      *Field = v33->m_EncountFloor;
      m_PopTableIdx = (u32)v33->m_PopTableIdx;
      if ((m_PopTableIdx & 0x80000000) == 0)
      {
        if ((s32)m_PopTableIdx < SLODWORD(gPop1St_Done->max_length))
        {
          gPop1St_Done[m_PopTableIdx] = 1;
        }
      }
      return *p_m_EncountIdx;
    }
  }
  v70 = EncountId;
  v71 = EncountPackId;
  v27 = -1;
  v72 = Type2;
  v73 = NakamaId;
  v74 = Field;
  v40 = 32;
  while (1)
  {
    v41 = *(s64 *)((char *)&gEnemyWork_local->m_Obj->obj.klass + v40);
    if (!*(u8 *)(v41 + 16) || !*(u8 *)(v41 + 448) || *(u32 *)(v41 + 140) == 4 && *(s32 *)(v41 + 144) < 20 || *(u32 *)(v41 + 64) == 7)
    {
      goto LABEL_36;
    }
    v42 = (v41 + 48);
    ToX = *(u64 *)(v41 + 48);
    v76 = *(f32 *)(v41 + 56);
    LenXZ = sBtlGetLenXZ(v22, v21, *(f32 *)&ToX, v76);
    if (sBtlGetABS(v23 - *(f32 *)(v41 + 52)) < 100.0 && LenXZ < 60.0)
      break;
    *(u32 *)(v41 + 396) = 0;
LABEL_36:
    v40 += 8;
    if (v40 == 352)
      return v27;
  }
  v45 = *(u32 *)(v41 + 396) + 1;
  *(u32 *)(v41 + 396) = v45;
  if (v45 < gMapEnemyDiffTbl[g_EnemySymbol_Diff]->m_EncHitTime)
    goto LABEL_36;
  g_AttackEstma = 0;
  v50 = *(f32 *)(v41 + 48);
  v51 = *(f32 *)(v41 + 56);
  PosToDir = sBtlGetPosToDir(v50, v51, v22, v21);
  v53 = *(u32 *)(v41 + 412);
  v54 = PosToDir;
  if (v53 > 1)
  {
    if (v53 != 2)
      goto LABEL_58;
LABEL_76:
    ToX = *v42;
    v66 = *(f32 *)&ToX;
    v76 = *(f32 *)(v41 + 56);
    v67 = v76;
    sBtlGetMoveXZ(v66, v67, v54 + 180.0, 50.0, &ToX, &v76);
    if (*(u32 *)(v41 + 412) == 3)
      goto LABEL_79;
LABEL_59:
    v56 = *(f32 *)&ToX;
    v57 = v76;
    goto LABEL_60;
  }
  ToX = *v42;
  v76 = *(f32 *)(v41 + 56);
  sBtlGetMoveXZ(*(f32 *)&ToX, v76, v54 + 180.0, 50.0, &ToX, &v76);
  v53 = *(u32 *)(v41 + 412);
  if (v53 == 2)
    goto LABEL_76;
LABEL_58:
  if (v53 != 3)
    goto LABEL_59;
LABEL_79:
  ToX = *v42;
  v68 = *(f32 *)&ToX;
  v76 = *(f32 *)(v41 + 56);
  v69 = v76;
  sBtlGetMoveXZ(v68, v69, v54 + 180.0, 100.0, &ToX, &v76);
  v56 = *(f32 *)&ToX;
  v57 = v76;
LABEL_60:
  v58 = sBtlGetPosToDir(v22, v21, v56, v57);
  if (sBtlGetAtoB_LR_ABS(v24, v58) > 120.0)
  {
    g_BackAttackEncount = 1;
  }
  p_m_EncountIdx = (v41 + 108);
  *v70 = *(u32 *)(v41 + 108);
  *v71 = *(u32 *)(v41 + 112);
  *v72 = 1;
  *v73 = GBWK->mapSummonID;
  *EnemyId = *(u32 *)(v41 + 124);
  *Map = *(u32 *)(v41 + 116);
  *v74 = *(u32 *)(v41 + 120);
  v64 = *(u32 *)(v41 + 104);
  mapSet1StDone(v64);
  return *p_m_EncountIdx;
}

// 0x1b7caa0
s32 mapGetSymbolNum(void) {
  return gEnemyWork->m_EnemyNum;
}

// 0x1b7cb30
void mapKEnemy_WorkClear(void) {
  ;
}

// 0x1b7cb40
s32 mapGetOikakeNum(void) {
  return gEnemyWork->m_OikakeNum;
}

// 0x1b7cbd0
void mapAI_All_GiveUp(void) {
  s64 v2;
  TYPE_ENEMYWORK *gEnemyWork_local;
  TYPE_ENEMYOBJ *m_Obj;
  s64 v5;
  u32 v6;
  bool v7;
  s32 v8;

  v2 = 32;
  gEnemyWork_local = gEnemyWork;
  m_Obj = gEnemyWork_local->m_Obj;
  do
  {
    v5 = *(s64 *)((char *)&m_Obj->obj.klass + v2);
    if (*(u8 *)(v5 + 16) && (*(u32 *)(v5 + 420) || *(s32 *)(v5 + 424) <= 10))
    {
      v6 = *(u32 *)(v5 + 140);
      v7 = v6 > 0x10;
      v8 = (1 << v6) & 0x1C300;
      if (!v7 && v8 != 0)
      {
        --gEnemyWork_local->m_OikakeNum;
        *(u64 *)(v5 + 140) = 10;
      }
    }
    v2 += 8;
  }
  while (v2 != 352);
}

// 0x1b7ccb0
void mapAI_All_Door(void) {
  s64 v2;
  TYPE_ENEMYOBJ *m_Obj;
  s64 v4;
  u32 v5;
  bool v6;
  s32 v7;

  v2 = 32;
  m_Obj = gEnemyWork->m_Obj;
  do
  {
    v4 = *(s64 *)((char *)&m_Obj->obj.klass + v2);
    if (*(u8 *)(v4 + 16) && (*(u32 *)(v4 + 420) || *(s32 *)(v4 + 424) <= 10))
    {
      v5 = *(u32 *)(v4 + 140);
      v6 = v5 > 6;
      v7 = (1 << v5) & 0x61;
      if (!v6 && v7 != 0)
        *(u64 *)(v4 + 140) = 1;
    }
    v2 += 8;
  }
  while (v2 != 352);
}

// 0x1b7cd80
void mapAI_All_Trap1(void) {
  s64 v3;
  TYPE_ENEMYWORK *gEnemyWork_local;
  TYPE_ENEMYOBJ *v5;
  s32 m_Trap1Num;
  s32 m_AiStep;

  v3 = 32;
  gEnemyWork_local = gEnemyWork;
  gEnemyWork_local->m_Trap1WarpCnt = 0;
  do
  {
    v5 = *(TYPE_ENEMYOBJ *)((char *)&gEnemyWork_local->m_Obj->obj.klass + v3);
    if (v5->m_Use && (v5->m_Res_Type || v5->m_Res_Avatar_Idx <= 10))
    {
      m_Trap1Num = gEnemyWork_local->m_Trap1Num;
      if (m_Trap1Num <= 15)
      {
        m_AiStep = v5->m_AiStep;
        if ((u32)(m_AiStep - 5) < 2)
          goto LABEL_15;
        if (m_AiStep == 2)
        {
          *(u64 *)&v5->m_AiStep = 23;
          goto LABEL_6;
        }
        if (!m_AiStep)
        {
LABEL_15:
          *(u64 *)&v5->m_AiStep = 21;
          m_Trap1Num = gEnemyWork_local->m_Trap1Num;
LABEL_6:
          TrapChangeEncId_Trap1(v5, g_ETrap1TableIndex, m_Trap1Num);
          ++gEnemyWork_local->m_Trap1Num;
        }
      }
    }
    v3 += 8;
  }
  while (v3 != 352);
}

// 0x1b7ceb0
void mapAI_All_Trap2(s32 aTableIndex) {
  s64 v5;
  s64 v6;

  v5 = 32;
  while (1)
  {
    v6 = *(s64 *)((char *)&gEnemyWork->m_Obj->obj.klass + v5);
    if (*(u8 *)(v6 + 16) && (*(u32 *)(v6 + 420) || *(s32 *)(v6 + 424) <= 10) && *(u32 *)(v6 + 140) == 2)
      break;
    v5 += 8;
    if (v5 == 352)
      return;
  }
  *(u64 *)(v6 + 24) = 0;
  *(u32 *)(v6 + 32) = 0;
  *(u64 *)(v6 + 48) = 0;
  *(u64 *)(v6 + 56) = 0;
  *(u64 *)(v6 + 140) = 25;
  TrapChangeEncId(v6, aTableIndex, 2);
}

// 0x1b7cfb0
void mapAI_All_Trap3(void) {
  s64 v3;
  s64 v4;
  s64 v5;

  v3 = 32;
  while (1)
  {
    v4 = *(s64 *)((char *)&gEnemyWork->m_Obj->obj.klass + v3);
    if (*(u8 *)(v4 + 16) && (*(u32 *)(v4 + 420) || *(s32 *)(v4 + 424) <= 10) && *(u32 *)(v4 + 140) == 2)
      break;
    v3 += 8;
    if (v3 == 352)
      return;
  }
  *(u32 *)(v4 + 300) = 0;
  *(u64 *)(v4 + 292) = 0;
  *(u64 *)(v4 + 284) = 0;
  *(u32 *)(v4 + 320) = 1065353216;
  *(u32 *)(v4 + 280) = 1119092736;
  *(u32 *)(v4 + 32) = 1119092736;
  *(int32x2_t *)(v4 + 272) = vdup_n_s32(0x42B40000u);
  v5 = *(u64 *)(v4 + 272);
  *(u64 *)(v4 + 48) = v5;
  *(u64 *)(v4 + 56) = 1119092736;
  *(u64 *)(v4 + 24) = v5;
  *(_OWORD *)(v4 + 304) = xmmword_3CFAFB0;
  *(u64 *)(v4 + 140) = 27;
  TrapChangeEncId(v4, g_ETrap3TableIndex, 3);
}

// 0x1b7d0e0
void mapAI_All_Trap4(void) {
  s64 v4;
  TYPE_ENEMYOBJ *m_Obj;
  s64 v6;

  if (!g_ETrap4TableIndex)
    return;
  v4 = 32;
  m_Obj = gEnemyWork->m_Obj;
  while (1)
  {
    v6 = *(s64 *)((char *)&m_Obj->obj.klass + v4);
    if (*(u8 *)(v6 + 16) && (*(u32 *)(v6 + 420) || *(s32 *)(v6 + 424) <= 10) && *(u32 *)(v6 + 140) == 2)
      break;
    v4 += 8;
    if (v4 == 352)
      return;
  }
  *(u64 *)(v6 + 24) = 0;
  *(u32 *)(v6 + 32) = 0;
  *(u64 *)(v6 + 48) = 0;
  *(u64 *)(v6 + 56) = 0;
  *(u64 *)(v6 + 140) = 29;
  TrapChangeEncId(v6, g_ETrap4TableIndex, 4);
}

// 0x1b7d1f0
void mapAI_Trap3_Direct(const sdfVector3_t *s_pos, f32 s_dir, const sdfVector3_t *e_pos, f32 e_dir, f32 movetime, f32 movehigh) {
  f32 z;
  f32 y;
  f32 x;
  f32 v12;
  f32 v13;
  f32 v14;
  s64 v16;
  s64 v17;
  s64 v18;
  s32 v19;

  z = e_pos->z;
  y = e_pos->y;
  x = e_pos->x;
  v12 = s_pos->z;
  v13 = s_pos->y;
  v14 = s_pos->x;
  v16 = 32;
  while (1)
  {
    v17 = *(s64 *)((char *)&gEnemyWork->m_Obj->obj.klass + v16);
    if (*(u8 *)(v17 + 16) && (*(u32 *)(v17 + 420) || *(s32 *)(v17 + 424) <= 10) && *(u32 *)(v17 + 140) == 2)
      break;
    v16 += 8;
    if (v16 == 352)
      return;
  }
  *(f32 *)(v17 + 304) = movetime;
  *(f32 *)(v17 + 272) = v14;
  *(f32 *)(v17 + 276) = v13;
  v18 = *(u64 *)(v17 + 272);
  *(u64 *)(v17 + 24) = v18;
  *(u64 *)(v17 + 48) = v18;
  *(f32 *)(v17 + 280) = v12;
  *(f32 *)(v17 + 320) = movehigh;
  v19 = *(u32 *)(v17 + 280);
  *(f32 *)(v17 + 284) = s_dir;
  *(f32 *)(v17 + 288) = x;
  *(f32 *)(v17 + 292) = y;
  *(f32 *)(v17 + 296) = z;
  *(f32 *)(v17 + 300) = e_dir;
  *(u32 *)(v17 + 32) = v19;
  *(u32 *)(v17 + 56) = v19;
  *(f32 *)(v17 + 60) = s_dir;
  *(u64 *)(v17 + 140) = 27;
  *(f32 *)(v17 + 308) = (f32)(x - v14) / movetime;
  *(f32 *)(v17 + 312) = (f32)(y - v13) / movetime;
  *(f32 *)(v17 + 316) = (f32)(z - v12) / movetime;
}

// 0x1b7b4d0
void mapDebug_AiDraw(void) {
  char *v3;
  char *v4;
  u64 *v5;
  char *v6;
  char *v7;
  char *v8;
  char *v9;
  char *v10;
  TYPE_ENEMYWORK *v11;
  char *v12;
  char *v13;
  char *v14;
  char *v15;
  char *v16;
  char *v17;
  char *v18;
  char *v19;
  char *v20;
  char *v21;
  char *v22;
  char *v23;
  char *v24;
  char *v25;
  char *v26;
  char *v27;
  char *v28;
  char *v29;
  char *v30;
  char *v31;
  char *v32;
  char *v33;
  char *v34;
  char *v35;
  char *v36;
  s32 i;
  s32 v39;
  s32 v40;
  s32 v41;
  s32 v42;
  s32 v43;
  s32 v44;
  s32 v45;
  s32 v46;
  s32 v47;
  s32 v48;
  s32 v49;
  s32 v50;
  TYPE_ENEMYOBJ *v51;
  char *v52;
  char *v53;
  char *v54;
  char *v55;
  char *v56;
  f32 x;
  s32 v58;
  char *v59;
  char *v60;
  f32 z;
  s32 v62;
  char *v63;
  char *v64;
  TYPE_ENEMYWORK *v65;
  char *v66;
  char **v67;
  s32 m_EnemyId;
  char *v69;
  char *v70;
  char *v71;
  char *v72;
  s32 j;
  s32 v74;
  s32 v75;
  s32 v76;
  s32 v77;
  s32 v78;
  s32 v79;
  TYPE_ENEMYRES *v80;
  char *v81;
  char *v82;
  char *v83;
  char *v84;
  s32 v85;
  char *v86;
  char *v87;
  s32 m_Map;
  s32 m_Area;
  s32 m_Area2;
  s32 v91;
  s32 v92;
  s32 v93;
  u32 *v95;
  s32 v96;
  s32 v97;
  s32 v98;
  u64 *v99;
  s32 Num[2];
  s32 StIdx[2];

  *(u64 *)StIdx = 0;
  *(u64 *)Num = 0;
  v3 = NewSpecific(string, 0x1Fu);
  v4 = "STANDBY";
  v5 = v3;
  v3[0] = "STANDBY";
  v6 = "DOOR";
  v5[5] = "DOOR";
  v7 = "SUMMON_W";
  v5[6] = "SUMMON_W";
  v8 = "SUMMON_W2";
  v5[7] = "SUMMON_W2";
  v9 = "SUMMON";
  v5[8] = "SUMMON";
  v10 = "UROURO_1";
  v11 = gEnemyWork;
  v5[9] = "UROURO_1";
  v12 = "UROURO_2";
  v5[10] = "UROURO_2";
  v13 = "DISCO";
  v5[11] = "DISCO";
  v14 = "RUN";
  v5[12] = "RUN";
  v15 = "RUN_A";
  v5[13] = "RUN_A";
  v16 = "GIVEUP_1";
  v5[14] = "GIVEUP_1";
  v17 = "GIVEUP_2";
  v5[15] = "GIVEUP_2";
  v18 = "GIVEUP_D";
  v5[16] = "GIVEUP_D";
  v19 = "GIVEUP_3";
  v5[17] = "GIVEUP_3";
  v20 = "INTERCEPT";
  v5[18] = "INTERCEPT";
  v21 = "INTERCEPT_A";
  v5[19] = "INTERCEPT_A";
  v22 = "RUSH";
  v5[20] = "RUSH";
  v23 = "DAMAGE";
  v5[21] = "DAMAGE";
  v24 = "BOSS";
  v5[22] = "BOSS";
  v25 = "BOSS_WO";
  v5[23] = "BOSS_WO";
  v26 = "BOSS_AO";
  v5[24] = "BOSS_AO";
  v27 = "TRAP1";
  v5[25] = "TRAP1";
  v28 = "TRAP1_WARP";
  v5[26] = "TRAP1_WARP";
  v29 = "TRAP1_SUMMON";
  v5[27] = "TRAP1_SUMMON";
  v30 = "TRAP1_SUMMON_WAIT";
  v5[28] = "TRAP1_SUMMON_WAIT";
  v31 = "TRAP2";
  v5[29] = "TRAP2";
  v32 = "TRAP2_W";
  v5[30] = "TRAP2_W";
  v33 = "TRAP3";
  v5[31] = "TRAP3";
  v34 = "TRAP3_W";
  v5[32] = "TRAP3_W";
  v35 = "TRAP4";
  v5[33] = "TRAP4";
  v99 = v5;
  v36 = "TRAP4_W";
  v5[34] = "TRAP4_W";
  StIdx[1] = 0;
  for (i = 0; i < 40; StIdx[1] = i)
  {
    v51 = v11->m_Obj[i];
    if (v51->m_Use)
    {
      v52 = ToString((s32)&StIdx[1], 0);
      v53 = Concat_54832128(" ", v52, " ", v99[v51->m_AiStep + 4], 0);
      v54 = ToString((s32)v51 + 176, 0);
      v55 = NewSpecific(string, 5u);
      v56 = "[";
      v55[0] = "[";
      x = v51->m_Pos.x;
      v58 = x;
      if (x == INFINITY)
        v58 = 0x80000000;
      Num[0] = v58;
      v59 = ToString(Num, 0);
      v55[1] = v59;
      v60 = " ";
      v55[2] = " ";
      z = v51->m_Pos.z;
      v62 = z;
      if (z == INFINITY)
        v62 = 0x80000000;
      Num[0] = v62;
      v63 = ToString(Num, 0);
      v55[3] = v63;
      v64 = "]";
      v55[4] = "]";
      v65 = v11;
      v66 = Concat_54832608(v55, 0);
      v67 = &"B";
      m_EnemyId = v51->m_EnemyId;
      if (v11->m_FAtkObjIdx != StIdx[1])
        v67 = &"";
      v69 = *v67;
      v70 = sdatDevilName(m_EnemyId, 0);
      v71 = ToString_55996800((s32)v51 + 108, "X", 0);
      v72 = Concat_54766928("0x", v71, 0);
      v39 = SPR_X(8);
      v40 = SPR_Y((16 * StIdx[1]) | 8);
      sprDbgPrintStr(v39, v40, 0, 0, v53, 109, 24);
      v41 = SPR_X(112);
      v42 = SPR_Y((16 * StIdx[1]) | 8);
      sprDbgPrintStr(v41, v42, 0, 0, v54, 109, 24);
      v43 = SPR_X(142);
      v44 = SPR_Y((16 * StIdx[1]) | 8);
      sprDbgPrintStr(v43, v44, 0, 0, v66, 109, 24);
      v45 = SPR_X(240);
      v46 = SPR_Y((16 * StIdx[1]) | 8);
      sprDbgPrintStr(v45, v46, 0, 0, v69, 109, 24);
      v47 = SPR_X(256);
      v48 = SPR_Y((16 * StIdx[1]) | 8);
      sprDbgPrintStr(v47, v48, 0, 0, v72, 109, 24);
      v49 = SPR_X(288);
      v50 = SPR_Y((16 * StIdx[1]) | 8);
      sprDbgPrintStr(v49, v50, 0, 0, v70, 109, 24);
      i = StIdx[1];
      v11 = v65;
    }
    ++i;
  }
  StIdx[1] = 0;
  for (j = 0; j < 16; StIdx[1] = j)
  {
    v80 = v11->m_Res_Devil[j];
    if (v80->m_hEnemy_Res != -1)
    {
      v81 = ToString((s32)&StIdx[1], 0);
      v82 = Concat_54766928(" ", v81, 0);
      v83 = ToString((s32)v80 + 20, 0);
      v84 = Concat_54831728("(", v83, ")", 0);
      v85 = v80->m_EnemyId;
      v86 = v84;
      v87 = sdatDevilName(v85, 0);
      v74 = SPR_X(8);
      v75 = SPR_Y(16 * StIdx[1] + 400);
      sprDbgPrintStr(v74, v75, 0, 0, v82, 109, 24);
      v76 = SPR_X(32);
      v77 = SPR_Y(16 * StIdx[1] + 400);
      sprDbgPrintStr(v76, v77, 0, 0, v86, 109, 24);
      v78 = SPR_X(64);
      v79 = SPR_Y(16 * StIdx[1] + 400);
      sprDbgPrintStr(v78, v79, 0, 0, v87, 109, 24);
      j = StIdx[1];
    }
    ++j;
  }
  StIdx[0] = 0;
  Num[1] = 0;
  m_Map = v11->m_Map;
  m_Area = v11->m_Area;
  m_Area2 = v11->m_Area2;
  mapFindPopTable(m_Map, m_Area, m_Area2, StIdx, &Num[1]);
  v91 = Num[1];
  StIdx[1] = 0;
  if (Num[1] >= 1)
  {
    v92 = StIdx[0];
    v93 = 0;
    do
    {
      v93 = StIdx[1];
      v95 = *((u32 **)&gPopTable[v93] + v92);
      v96 = v95[7];
      v97 = v95[8];
      v98 = v95[9];
      sBtlDrawLineX_PS2((f32)v96, (f32)v97 + -5.0, (f32)v98, 100.0, 0xFFFFFFu);
      v93 = ++StIdx[1];
    }
    while (StIdx[1] < v91);
  }
}

// 0x1b788c0
static bool IsEnemyMatch(TYPE_ENEMYOBJ *pObj) {
  return 0;
}

// 0x1b6f510
static s32 AsdMdlSyncLoad(s32 _DevilID, char **_AssetKey) {
  char *DevilModelName;
  pacFileHandle_t *_28877184;
  sdfPacDecodeResrcHandle_t *v7;
  sdfPacDecodeResrcHandle_t *Resrc;
  sdfPacDecodeResrcHandle_t *next;
  sdfPacDecodeResrcHandle_t *v10;

  DevilModelName = mdlGetDevilModelName(DevilID);
  _28877184 = pacLoad_2(DevilModelName);
  pacSync(_28877184);
  *AssetKey = DevilModelName;
  v7 = Allocate(sdfPacDecodeResrcHandle_t);
  _ctor(v7, 0);
  Resrc = pacGetResrc(_28877184);
  if (Resrc)
  {
    next = Resrc;
    do
    {
      if (!next->header->userId)
      {
        v10 = pacGetResrc(_28877184);
        PackDecode(1u, DevilID, 257, v10);
      }
      next = next->next;
    }
    while (next);
  }
  pacHandleFree(_28877184);
  return DevilID;
}

// 0x1b72460
static void AsdMdlFree(TYPE_ENEMYOBJ *pObj) {
  dds3Basic_t *m_hMdl_Basic;

  m_hMdl_Basic = pObj->m_hMdl_Basic;
  if (m_hMdl_Basic)
  {
    dds3SceneBasicDelete(m_hMdl_Basic);
    pObj->m_hMdl_Basic = 0;
    pObj->m_hMdl_Model = 0;
  }
}

// 0x1b6e330
static void Free_AllAsset(void) {
  s64 v2;
  TYPE_ENEMYWORK *gEnemyWork_local;
  char *v4;
  u64 *v5;
  s64 v6;
  s64 i;
  char *v9;
  u64 *v10;
  s64 v11;

  v2 = 32;
  gEnemyWork_local = gEnemyWork;
  do
  {
    v6 = *(s64 *)((char *)&gEnemyWork_local->m_Res_Avatar->obj.klass + v2);
    if (*(u32 *)(v6 + 16) != -1)
    {
      v6 = *(s64 *)((char *)&gEnemyWork_local->m_Res_Avatar->obj.klass + v2);
      Unload(Dependent, *(char **)(v6 + 32), 0);
      v4 = "";
      v5 = *(Il2CppClass **)((char *)&gEnemyWork_local->m_Res_Avatar->obj.klass + v2);
      v5[4] = "";
      v5 += 4;
      *(v5 - 2) = 0xFFFFFFFFLL;
      *((u32 *)v5 - 2) = -1;
    }
    v2 += 8;
  }
  while (v2 != 200);
  for (i = 32; i != 160; i += 8)
  {
    v11 = *(s64 *)((char *)&gEnemyWork_local->m_Res_Devil->obj.klass + i);
    if (*(u32 *)(v11 + 16) != -1)
    {
      v11 = *(s64 *)((char *)&gEnemyWork_local->m_Res_Devil->obj.klass + i);
      Unload(Dependent, *(char **)(v11 + 32), 0);
      v9 = "";
      v10 = *(Il2CppClass **)((char *)&gEnemyWork_local->m_Res_Devil->obj.klass + i);
      v10[4] = "";
      v10 += 4;
      *(v10 - 2) = 0xFFFFFFFFLL;
      *((u32 *)v10 - 2) = -1;
    }
  }
  DeleteAll();
  DeleteAll();
}

// 0x1b7d350
static dds3Basic_t *AsdMdlCopy(s32 _ResId) {
  return 0;
}

// 0x1b788d0
static void AsdMdlSceneAddModel(TYPE_ENEMYOBJ *pObj, s32 _ResId) {
  dds3Basic_t *p_m_hMdl_Basic;
  f32 m_EnemyScale;
  f32 *p_x;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 v13;
  u32 v14;
  dds3Basic_t *v15;
  dds3Basic_t *ControlScene;
  dds3Basic_t *v17;
  s32 m_EnemyId;
  dds3ModelHandle_t *ModelHandle;
  dds3ModelHandle_t *p_m_hMdl_Model;
  sdfVector4_t v23;
  sdfVector4_t v24;
  sdfVector4_t v25;
  sdfVector4_t v26;
  sdfVector4_t v27;

  if (pObj)
  {
    p_m_hMdl_Basic = &pObj->m_hMdl_Basic;
    m_EnemyScale = pObj->m_EnemyScale;
    pObj->m_hMdl_Basic = 0;
    vct_A = (struct sdfVector4_t)xmmword_3D015F0;
    FromRotation(3.1415927);
    vct_B = (struct sdfVector4_t)xmmword_3CFD5C0;
    Mult();
    p_x = &vf00.x;
    v10 = p_x[4];
    v11 = p_x[5];
    v12 = p_x[6];
    v13 = p_x[7];
    v14 = dds3SerializeID();
    v23.w = 1.0;
    v23.x = 0.0;
    v23.y = 0.0;
    v23.z = 0.0;
    v27.x = v10;
    v27.y = v11;
    v27.z = v12;
    v27.w = v13;
    v15 = dds3UnitObjectBasicAdd(v14, v23, v27);
    p_m_hMdl_Basic = v15;
    dds3SetBasicName(p_m_hMdl_Basic, "ENEMYSYMBOL_UNIT");
    ControlScene = dds3GetControlScene();
    v17 = p_m_hMdl_Basic;
    dds3SceneBasicSetActiveUnit(ControlScene, v17);
    m_EnemyId = pObj->m_EnemyId;
    mdlSearchResrc(1u, m_EnemyId);
    dds3ObjectBaseMakeUnit(pObj->m_hMdl_Basic, 1u, pObj->m_EnemyId);
    v24.x = 0.0;
    v24.y = 0.0;
    v24.z = 0.0;
    v24.w = 1.0;
    dds3SetPosPoseSet(&pObj->m_hMdl_Basic, v24);
    v25.x = v10;
    v25.y = v11;
    v25.z = v12;
    v25.w = v13;
    dds3SetRotPoseSet(&pObj->m_hMdl_Basic, v25);
    v26.x = m_EnemyScale;
    v26.y = m_EnemyScale;
    v26.z = m_EnemyScale;
    v26.w = 1.0;
    dds3SetSclPoseSet(&pObj->m_hMdl_Basic, v26);
    ModelHandle = dds3ObjectBaseGetModelHandle(&pObj->m_hMdl_Basic);
    if (ModelHandle)
    {
      p_m_hMdl_Model = &pObj->m_hMdl_Model;
    }
    else
    {
      p_m_hMdl_Model = &pObj->m_hMdl_Model;
      pObj->m_hMdl_Model = 0;
    }
    dds3SetRadiusPoseSet(&pObj->m_hMdl_Basic, 20.0);
    mdlLoopMotion(p_m_hMdl_Model, 0, 2);
    dds3ObjectBaseOnFlag(&pObj->m_hMdl_Basic, 0x400u);
    dds3ObjectBaseOnFlag(&pObj->m_hMdl_Basic, 0x40000u);
    return;
  }
}

// 0x1b72150
static void AsdMdlSceneDelModel(TYPE_ENEMYOBJ *pObj) {
  dds3Basic_t *m_hMdl_Basic;

  if (pObj)
  {
    m_hMdl_Basic = pObj->m_hMdl_Basic;
    dds3SceneBasicDelete(m_hMdl_Basic);
    pObj->m_hMdl_Basic = 0;
    pObj->m_hMdl_Model = 0;
  }
}

// 0x1b790c0
static void AsdMdlShow(TYPE_ENEMYOBJ *pObj) {
  f32 m_EnemyScale;
  sdfVector4_t v4;

  dds3ObjectBaseOffFlag(&pObj->m_hMdl_Basic, 1u);
  m_EnemyScale = pObj->m_EnemyScale;
  v4.w = 1.0;
  v4.x = m_EnemyScale;
  v4.y = m_EnemyScale;
  v4.z = m_EnemyScale;
  dds3SetSclPoseSet(&pObj->m_hMdl_Basic, v4);
}

// 0x1b7d360
static void AsdMdlHide(TYPE_ENEMYOBJ *pObj) {
  dds3ObjectBaseOnFlag(&pObj->m_hMdl_Basic, 1u);
}

// 0x1b79920
static bool AsdMdlCheckHide(TYPE_ENEMYOBJ *pObj) {
  return !pObj->m_hMdl_Basic && dds3ObjectBaseCheckFlag(&pObj->m_hMdl_Basic, 1);
}

// 0x1b79940
static void AsdMdlSetPosition(TYPE_ENEMYOBJ *pObj, const sdfVector3_t *_Pos) {
  f32 z;
  f32 y;
  f32 x;
  sdfVector4_t v7;

  z = Pos->z;
  y = Pos->y;
  x = Pos->x;
  v7.z = z;
  v7.w = 0.0;
  v7.y = y + 0.0;
  v7.x = x;
  dds3SetPosPoseSet(&pObj->m_hMdl_Basic, v7);
}

// 0x1b799e0
static void AsdMdlSetRotationXYZ(TYPE_ENEMYOBJ *pObj, f32 _DirX, f32 _DirY, f32 _DirZ) {
  f32 v7;
  f32 v9;
  dds3Basic_t *p_m_hMdl_Basic;
  f32 *p_x;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  sdfVector4_t v19;

  if (pObj->m_hMdl_Basic)
  {
    v7 = sBtlGet360((f32)(360.0 - DirY) + 180.0);
    vct_A = (struct sdfVector4_t)xmmword_3D015F0;
    v9 = RAD(v7);
    FromRotation(v9);
    p_m_hMdl_Basic = &pObj->m_hMdl_Basic;
    p_x = &vf00.x;
    x = p_x[4];
    y = p_x[5];
    z = p_x[6];
    w = p_x[7];
    v19.x = x;
    v19.y = y;
    v19.z = z;
    v19.w = w;
    dds3SetRotPoseSet(p_m_hMdl_Basic, v19);
    return;
  }
}

// 0x1b79c60
static void AsdMdlSetScaleXYZ(TYPE_ENEMYOBJ *pObj, f32 _SclX, f32 _SclY, f32 _SclZ) {
  ;
}

// 0x1b79c70
static void AsdModelSetChrAnmNo(TYPE_ENEMYOBJ *pObj, s32 _MotId, f32 _Hokan) {
  s32 v7;
  s32 v8;
  dds3ModelHandle_t *m_hMdl_Model;
  dds3ModelHandle_t *v11;

  v7 = 0;
  v8 = 13;
  switch (MotId)
  {
    case 0:
      goto LABEL_13;
    case 1:
      v8 = 0;
      v7 = 1;
      m_hMdl_Model = pObj->m_hMdl_Model;
      goto LABEL_14;
    case 2:
    case 4:
      v7 = 1;
      v8 = 1;
      m_hMdl_Model = pObj->m_hMdl_Model;
      goto LABEL_14;
    case 3:
      v7 = 0;
      v8 = 6;
      m_hMdl_Model = pObj->m_hMdl_Model;
      goto LABEL_14;
    case 5:
      v7 = 0;
      v8 = 4;
      m_hMdl_Model = pObj->m_hMdl_Model;
      goto LABEL_14;
    case 6:
      v7 = 0;
      v8 = 12;
LABEL_13:
      m_hMdl_Model = pObj->m_hMdl_Model;
      goto LABEL_14;
    case 7:
      v7 = 0;
      v8 = 14;
      m_hMdl_Model = pObj->m_hMdl_Model;
LABEL_14:
      if (v8 == m_hMdl_Model->motionMinorNum)
        return;
      v11 = pObj->m_hMdl_Model;
      if (v7)
      {
        mdlSmoothLoopMotion(v11, 0, v8, Hokan, Hokan, 0.0);
      }
      else
      {
        mdlSmoothSingleMotion(v11, 0, v8, Hokan, Hokan, 0.0);
      }
      return;
    default:
      return;
  }
}

// 0x1b79e50
static void AsdMdlSetChrAnmSpeed(TYPE_ENEMYOBJ *pObj, f32 _MotSpd) {
  dds3ModelHandle_t *m_hMdl_Model;

  m_hMdl_Model = pObj->m_hMdl_Model;
  if (m_hMdl_Model)
  {
    mdlSetMotionSpeed(m_hMdl_Model, MotSpd);
  }
}

// 0x1b78d50
static bool AsdMdlChkChrAnmEnd(TYPE_ENEMYOBJ *pObj) {
  dds3ModelHandle_t *m_hMdl_Model;

  m_hMdl_Model = pObj->m_hMdl_Model;
  return mdlChkMotionEnd(m_hMdl_Model);
}

// 0x1b79be0
static void AsdMdlSetDitherAlpha(TYPE_ENEMYOBJ *pObj, f32 _DitherAlpha) {
  dds3ModelHandle_t *m_hMdl_Model;

  m_hMdl_Model = pObj->m_hMdl_Model;
  mdlSetDitherAlpha(m_hMdl_Model, DitherAlpha);
}

// 0x1b731b0
s32 mapCollision_PosToPosHitChk(const sdfVector3_t *frompos, const sdfVector3_t *topos) {
  f32 z;
  f32 x;
  f32 v5;
  f32 v6;
  f32 LenXZ;
  s32 CeilToInt;
  s32 v9;
  s32 v10;
  s32 i;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  s32 v16;
  f32 GetZ;
  f32 GetX;
  s64 getz;

  z = topos->z;
  x = topos->x;
  v5 = frompos->z;
  v6 = frompos->x;
  getz = 0;
  LenXZ = sBtlGetLenXZ(v6, v5, x, z);
  CeilToInt = sBtlGetCeilToInt(LenXZ, 38.0);
  v9 = CeilToInt - 1;
  GetZ = v5;
  GetX = v6;
  if (CeilToInt < 1)
    return -1;
  v10 = CeilToInt;
  for (i = 0; i != v10; ++i)
  {
    if (i >= v9)
    {
      v16 = 1;
      if (mapHitCalc(1, x, z, 40.0, (f32 *)&getz + 1, &getz, -1, 0))
        return v16;
    }
    else
    {
      v13 = GetZ;
      v12 = GetX;
      sBtlGetMovePosToPos(v12, v13, x, z, 38.0, &GetX, &GetZ);
      v15 = GetZ;
      v14 = GetX;
      v16 = 1;
      if (mapHitCalc(1, v14, v15, 40.0, (f32 *)&getz + 1, &getz, -1, 0))
        return v16;
    }
  }
  return -1;
}

// 0x1b78e90
s32 Collision_PosToPosHitChk(const sdfVector3_t *frompos, const sdfVector3_t *topos, sdfVector3_t *retpos) {
  f32 z;
  f32 y;
  f32 x;
  f32 v7;
  f32 v8;
  f32 LenXZ;
  s32 CeilToInt;
  s32 v14;
  s32 v15;
  s32 v16;
  s32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v24;
  f32 GetX;
  s64 getz;

  z = topos->z;
  y = topos->y;
  x = topos->x;
  v7 = frompos->z;
  v8 = frompos->x;
  retpos->x = x;
  retpos->y = y;
  retpos->z = z;
  getz = 0;
  LenXZ = sBtlGetLenXZ(v8, v7, x, z);
  CeilToInt = sBtlGetCeilToInt(LenXZ, 38.0);
  v14 = CeilToInt - 1;
  v24 = v7;
  GetX = v8;
  if (CeilToInt < 1)
    return -1;
  v15 = CeilToInt;
  v16 = 0;
  v17 = -1;
  while (v16 < v14)
  {
    v19 = v24;
    v18 = GetX;
    sBtlGetMovePosToPos(v18, v19, x, z, 38.0, &GetX, &v24);
    v21 = v24;
    v20 = GetX;
    if (mapHitCalc(1, v20, v21, 40.0, (f32 *)&getz + 1, &getz, -1, 0))
      goto LABEL_20;
LABEL_17:
    if (v15 == ++v16)
      return v17;
  }
  if (!mapHitCalc(1, x, z, 40.0, (f32 *)&getz + 1, &getz, -1, 0))
    goto LABEL_17;
LABEL_20:
  retpos->x = *((f32 *)&getz + 1);
  LODWORD(retpos->z) = getz;
  retpos->y = mapGetY(x, z);
  return 1;
}

// 0x1b733a0
bool mapCollisionHitChk2(const sdfVector3_t *oldpos, const sdfVector3_t *frompos, sdfVector3_t *retpos, bool aGroundMode) {
  f32 z;
  f32 y;
  f32 x;
  f32 v8;
  f32 v9;
  s32 v13;
  s32 m_Area;
  f32 FloorY;
  f32 v18;
  f32 ABS;
  f32 v20;
  f32 getz;
  f32 getx;

  z = frompos->z;
  y = frompos->y;
  x = frompos->x;
  v8 = oldpos->z;
  v9 = oldpos->x;
  retpos->x = x;
  retpos->y = y;
  retpos->z = z;
  getz = z;
  getx = x;
  v13 = mapHitCalc(0, x, z, 40.0, &getx, &getz, -1, 0);
  if (v13 == -1)
  {
    z = v8;
    x = v9;
  }
  else
  {
    if (!v13)
    {
      goto LABEL_8;
    }
    z = getz;
    x = getx;
  }
LABEL_8:
  if (gEnemyWork->m_Area2 != -1)
  {
    m_Area = gEnemyWork->m_Area;
    FloorY = mapGetFloorY(m_Area, x, z);
    v18 = mapGetFloorY(gEnemyWork->m_Area2, x, z);
    ABS = sBtlGetABS(y - FloorY);
    if (ABS >= sBtlGetABS(y - v18))
      v20 = v18;
    else
      v20 = FloorY;
    goto LABEL_23;
  }
  v20 = mapGetY(x, z);
LABEL_23:
  retpos->y = v20;
  return 1;
}

// 0x1b73940
bool mapCollisionHitChk(sdfVector3_t *phys_pos, sdfVector3_t *phys_oldpos) {
  f32 x;
  f32 z;
  s64 v8;

  x = phys_pos->x;
  z = phys_pos->z;
  phys_pos->y = mapGetY(x, z);
  v8 = *(u64 *)&phys_pos->x;
  phys_oldpos->z = phys_pos->z;
  *(u64 *)&phys_oldpos->x = v8;
  return 1;
}

// 0x1b78e80
void se3dPosSet(s32 Move3dSE_Acter, const sdfVector3_t *pos) {
  ;
}

// 0x1b78de0
void mapDraw_KemuriReq_E(const sdfVector3_t *pos) {
  f32 z;
  f32 y;
  f32 x;
  sdfVector3_t v5;

  z = pos->z;
  y = pos->y;
  x = pos->x;
  v5.y = (f32)(y / -100.0) + 0.1;
  v5.z = z / -100.0;
  v5.x = x / -100.0;
  addPlayerFootEffect_Pos(v5, 1.5);
}

// 0x1b79160
void mapDraw_KemuriReq_Big2(const sdfVector3_t *pos) {
  f32 z;
  f32 y;
  f32 x;
  sdfVector3_t v5;

  z = pos->z;
  y = pos->y;
  x = pos->x;
  v5.y = (f32)(y / -100.0) + 0.1;
  v5.z = z / -100.0;
  v5.x = x / -100.0;
  addPlayerFootEffect_Pos(v5, 1.5);
}

// 0x1b79200
void mapCamera_SetQuake(s32 a, s32 b, s32 c) {
  dds3SetQuake(30, 0x28u);
}

// 0x1b7d370
void mapClrUI(void) {
  expAllCancelExpUpText(1);
  AllClearGetRewardText(instance, 0);
}

// 0x1b71e40
void mapFindPopTable(s32 _MapId, s32 _FloorId, s32 _Floor2Id, s32 *_StIdx, s32 *_Num) {
  char v12;
  s64 i;
  TYPE_POP_TABLE *gPopTable_local;

  *Num = 0;
  v12 = 1;
  for (i = 4; ; ++i)
  {
    gPopTable_local = gPopTable;
    if (i - 4 >= SLODWORD(gPopTable_local->max_length))
      break;
    if (*(u32 *)(*((u64 *)&gPopTable_local->obj.klass + i) + 16) != MapId)
      goto LABEL_22;
    if (*(u32 *)(*((u64 *)&gPopTable->obj.klass + i) + 20) == FloorId)
      goto LABEL_19;
    if (*(u32 *)(*((u64 *)&gPopTable->obj.klass + i) + 20) == Floor2Id)
      goto LABEL_19;
    goto LABEL_9000;
    if (*(u32 *)(*((u64 *)&gPopTable->obj.klass + i) + 20) == Floor2Id)
    {
LABEL_19:
      if ((v12 & 1) != 0)
        *StIdx = i - 4;
      v12 = 0;
      ++*Num;
      continue;
    }
LABEL_9000:
LABEL_22:
    if ((v12 & 1) == 0)
      return;
    v12 = 1;
  }
}
