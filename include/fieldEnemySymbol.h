#pragma once
#include "types.h"
#include "field.h"

typedef enum {
    AtlEnemySymbol_eState_None = 0,
    AtlEnemySymbol_eState_Summon = 1,
    AtlEnemySymbol_eState_Standby = 2,
    AtlEnemySymbol_eState_Move = 3,
    AtlEnemySymbol_eState_Discovery = 4,
    AtlEnemySymbol_eState_Chase = 5,
    AtlEnemySymbol_eState_StandStill = 6,
    AtlEnemySymbol_eState_Giveup = 7,
    AtlEnemySymbol_eState_Damage = 8,
    AtlEnemySymbol_eState_Return = 9,
    AtlEnemySymbol_eState_Dead = 10,
    AtlEnemySymbol_eState_MAX = 11,
} AtlEnemySymbol_eState;

typedef enum {
    eEnemyMotion_SUMMON = 0,
    eEnemyMotion_STANDBY = 1,
    eEnemyMotion_WALK = 2,
    eEnemyMotion_DISCO = 3,
    eEnemyMotion_RUN = 4,
    eEnemyMotion_DAMAGE = 5,
    eEnemyMotion_DEAD = 6,
    eEnemyMotion_RETURN = 7,
} eEnemyMotion;

typedef enum {
    eEnemySE_Summon = 0,
    eEnemySE_Discovery = 1,
    eEnemySE_Encount = 2,
    eEnemySE_Return = 3,
    eEnemySE_Wandering = 4,
    eEnemySE_TrapSummon = 5,
    eEnemySE_TrapJumpOut = 6,
    eEnemySE_Contact = 7,
    eEnemySE_Dead = 8,
    eEnemySE_Missing = 9,
} eEnemySE;

typedef enum {
    eEnemyGiveupType_Respawn = 0,
    eEnemyGiveupType_Delete = 1,
} eEnemyGiveupType;

typedef enum {
    eEnemySymbolPopSkillStatus_Normal = 0,
    eEnemySymbolPopSkillStatus_Riberama = 1,
    eEnemySymbolPopSkillStatus_Estoma = 2,
} eEnemySymbolPopSkillStatus;

typedef enum {
    eEnemySymbolRepopTiming_AreaChange = 0,
    eEnemySymbolRepopTiming_Encount_This = 1,
    eEnemySymbolRepopTiming_Encount_Other = 2,
    eEnemySymbolRepopTiming_Giveup_Chase = 3,
    eEnemySymbolRepopTiming_Clear = 4,
} eEnemySymbolRepopTiming;

typedef enum {
    eEnemySymbolOuterScreenNotice_None = 0,
    eEnemySymbolOuterScreenNotice_Left = 1,
    eEnemySymbolOuterScreenNotice_Right = 2,
    eEnemySymbolOuterScreenNotice_Center = 3,
} eEnemySymbolOuterScreenNotice;

typedef enum {
    eEnemySymbolDebug_BtlSkipMode_None = 0,
    eEnemySymbolDebug_BtlSkipMode_AllSuccess = 1,
    eEnemySymbolDebug_BtlSkipMode_AllFailed = 2,
    eEnemySymbolDebug_BtlSkipMode_MAX = 3,
} eEnemySymbolDebug_BtlSkipMode;

typedef enum {
    eEnemyTestMode_None = 0,
    eEnemyTestMode_NormalMove = 1,
    eEnemyTestMode_Chase = 2,
} eEnemyTestMode;

typedef enum {
    AtlEnemySymbolManager_eState_Null = 0,
    AtlEnemySymbolManager_eState_Load = 1,
    AtlEnemySymbolManager_eState_LoadDone = 2,
    AtlEnemySymbolManager_eState_Reset = 3,
    AtlEnemySymbolManager_eState_ResetEnd = 4,
    AtlEnemySymbolManager_eState_Pause = 5,
    AtlEnemySymbolManager_eState_Idle = 6,
    AtlEnemySymbolManager_eState_Unload = 7,
    AtlEnemySymbolManager_eState_UnloadDone = 8,
    AtlEnemySymbolManager_eState_Reload = 9,
    AtlEnemySymbolManager_eState_BattleStartProd_Playing = 10,
    AtlEnemySymbolManager_eState_BattleStartProd_End = 11,
    AtlEnemySymbolManager_eState_Battling = 12,
    AtlEnemySymbolManager_eState_MAX = 13,
} AtlEnemySymbolManager_eState;

typedef enum {
    eSurpriseStep_Init = 0,
    eSurpriseStep_Idle = 1,
    eSurpriseStep_AttackStartWait = 2,
    eSurpriseStep_Attack = 3,
    eSurpriseStep_EncountBeforeWait = 4,
    eSurpriseStep_Encount = 5,
    eSurpriseStep_BattleStartWait = 6,
    eSurpriseStep_BattleStart = 7,
    eSurpriseStep_Skip = 8,
    eSurpriseStep_OpenTBox = 9,
    eSurpriseStep_AttackAfterWait = 10,
} eSurpriseStep;

typedef enum {
    eStep_None = 0,
    eStep_Load = 1,
    eStep_Done = 2,
    eStep_Unload = 3,
    eStep_MAX = 4,
} eStep;

typedef enum {
    eStatus_HP = 0,
    eStatus_Atk = 1,
    eStatus_Def = 2,
    eStatus_Vice = 3,
    eStatus_Mag = 4,
    eStatus_Spirit = 5,
} eStatus;

typedef struct AtlEnemyMotionConst_Data AtlEnemyMotionConst_Data;
typedef struct AtlEnemySymbol AtlEnemySymbol;
typedef struct AtlEnemySymbolChara AtlEnemySymbolChara;
typedef struct AtlEnemySymbolChoiceData AtlEnemySymbolChoiceData;
typedef struct AtlEnemySymbolResource_Data AtlEnemySymbolResource_Data;
typedef struct AtlEnemySymbolSpawnerBase AtlEnemySymbolSpawnerBase;
typedef struct AtlEnemySymbolSurpriseTarget AtlEnemySymbolSurpriseTarget;
typedef struct AtlEnemySymbolTableData AtlEnemySymbolTableData;
typedef struct AtlFieldHUD_EnemyTarget AtlFieldHUD_EnemyTarget;
typedef struct AtlFieldHUD_Simple3D AtlFieldHUD_Simple3D;
typedef struct AtlFieldHUD_TargetRing AtlFieldHUD_TargetRing;
typedef struct BattleData BattleData;
typedef struct DEVILDATA_WORK DEVILDATA_WORK;
typedef struct ESDevilTbl_t ESDevilTbl_t;
typedef struct ESEncountTbl_EncountPack_t ESEncountTbl_EncountPack_t;
typedef struct ESEncountTbl_t ESEncountTbl_t;
typedef struct EncountPack EncountPack;
typedef struct FadeData FadeData;
typedef struct MAP_OBJ_t MAP_OBJ_t;
typedef struct Record Record;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;

struct ESDevilTbl_t {
    s32 _id;
    f32 normal_mv_spd;
    f32 normal_rot_spd;
    f32 normal_m_speed;
    f32 disc_mv_spd;
    f32 disc_rot_spd;
    f32 disc_m_speed;
    f32 col_radius;
    f32 scale;
    f32 target_cursor_x;
    f32 target_cursor_y;
    f32 target_cursor_z;
    f32 target_cursor_scale;
    f32 target_ring_x;
    f32 target_ring_y;
    f32 target_ring_z;
    f32 target_ring_scale;
    f32 bounds_x;
    f32 bounds_y;
    f32 bounds_z;
    f32 bounds_ofs_x;
    f32 bounds_ofs_y;
    f32 bounds_ofs_z;
    char *bounds_bone_name;
    f32 dist_icon_x;
    f32 dist_icon_y;
    f32 dist_icon_z;
};

struct AtlEnemySymbolChoiceData {
    AtlEnemySymbolTableData *m_Table;
    s32 m_ChoisePackIndex;
    s32 m_EncountID;
    s32 m_DLCIndex;
    s32 m_VisibleDevilID;
    s32 m_EncountOldPackIndex;
    s32 m_BattleMapID;
    s32 m_BattleAreaID;
    bool m_IsIgnoreInstantDeath;
    s32 m_MaxLv;
};

struct AtlEnemySymbol {
    f32 m_CheckDiscoveryPlayerTime;
    AtlEnemySymbolSpawnerBase *m_ParentSpawner;
    s32 m_TableID;
    s32 m_UniqueID;
    AtlEnemySymbolChoiceData m_TableParam;
    DEVILDATA_WORK *m_DevilParam;
    ESDevilTbl_t *m_VisualParam;
    AtlEnemySymbolChara *m_Chara;
    void *m_State;
    sdfVector3_t m_PlayerPos;
    f32 m_CurrentPlayerToDistance;
    f32 m_CurrentPlayerToDistanceY;
    f32 m_CurrentPlayerToAngle;
    bool m_IsInScreen;
    void *m_RangeMoveCollision;
    void *m_EyeCollision;
    void *m_MovePath;
    f32 m_Dt;
    bool m_IsPlaySpawnProd;
    eEnemyGiveupType m_GiveupType;
    sdfVector3_t m_Bounds;
    sdfVector3_t m_BoundsOfs;
    char *m_BoundsBoneName;
    sdfVector3_t m_TargetIconOfs;
    f32 m_TargetIconSize;
    sdfVector3_t m_TargetRingOfs;
    f32 m_TargetRingSize;
    sdfVector3_t m_DistIconOfs;
    bool m_IsDebugVisibleAllIcon;
    f32 m_NormalMoveSpeed;
    f32 m_NormalRotSpeed;
    f32 m_NormalMotionSpeed;
    f32 m_ChaseMoveSpeed;
    f32 m_ChaseRotSpeed;
    f32 m_ChaseMotionSpeed;
    AtlEnemySymbolSurpriseTarget *m_SurpriseTarget;
    AtlFieldHUD_Simple3D *m_HUD_DiscoveryIcon;
    AtlFieldHUD_Simple3D *m_HUD_QuestionIcon;
    eEnemyTestMode m_TestMode;
    bool m_IsChaseDamage;
};

struct AtlEnemySymbolChara {
    sdfVector3_t m_Pos;
    bool m_IsDirtyPos;
    sdfVector3_t m_Rotate;
    bool m_IsDirtyRotate;
    sdfQuaternion_t _RotateQuat_k__BackingField;
    f32 m_Scale;
    bool m_IsDirtyScale;
    f32 m_MotionSpeed;
    bool m_IsDirtyMotSpeed;
    f32 m_Alpha;
    bool m_IsDirtyAlpha;
    f32 m_Radius;
    void *m_BaseCollision;
    dds3Basic_t *m_hMdl_Basic;
    dds3ModelHandle_t *m_hMdl_Model;
    bool m_IsCreateModel;
    f32 m_DeltaTime;
    sdfVector3_t m_BoundsSize;
    sdfVector3_t m_BoundsOffset;
    char *m_BoundsBoneName;
    void *m_Bounds;
    bool m_IsCopyPos2;
    bool m_IsFadeEffEnable;
    void *m_Effs;
    s32 m_LastReqFadeType;
    FadeData *m_Fades;
    ESDevilTbl_t *m_DevilData;
};

struct AtlEnemyMotionConst_Data {
    eEnemyMotion m_MotID;
    s32 m_RawID;
    bool m_IsLoop;
};

struct EncountPack {
    ESEncountTbl_EncountPack_t *m_Pack;
    bool m_IsEnable;
    s32 *m_PackDevilIDs;
    void *m_RndEncOuterEncountBattleMapIDs;
    void *m_RndEncInnerEncountBattleMapIDs;
    void *m_RndEncBattleMapID;
    void *m_EncountBattleMapID;
    s32 m_EncountDevilIDIndex;
};

struct AtlEnemySymbolTableData {
    s32 m_UniqueID;
    ESEncountTbl_t *m_Body;
    EncountPack *m_EncountPacks;
};

struct BattleData {
    bool m_IsSurprise;
    s32 m_LastFaastAttackDevilID;
};

struct Record {
    sdfVector3_t m_Pos;
    f32 m_Dir;
};

struct AtlEnemySymbolResource_Data {
    s32 m_DevilID;
    s32 m_ResourceID;
    s32 m_MotionSEID;
    void *m_TmpLoadMotionSECoroutine;
    void *m_TmpUnloadCoroutine;
    char *m_AssetKey;
};

struct AtlEnemySymbolSpawnerBase {
    AtlEnemySymbolTableData *m_SymbolData;
    bool m_IsEnable;
    bool m_IsPlaySpawnProd;
    f32 m_RepopGuardTimer;
    bool m_IsAlreadyDestroy;
    bool m_IsAlreadyIn;
    bool m_IsPlayingTimer;
};

struct AtlEnemySymbolSurpriseTarget {
    AtlEnemySymbol *_Symbol_k__BackingField;
    MAP_OBJ_t *_TBox_k__BackingField;
    sdfVector3_t m_PlayerPos;
    AtlFieldHUD_TargetRing *m_TargetRing;
    eType m_ForceTargetRingType;
    AtlFieldHUD_EnemyTarget *m_TargetIcon;
    bool m_IsDamage;
    bool m_IsVisibleTargetIcon;
    bool m_IsVisibleTargetRing;
    eFieldSurpriseTargetStatus m_Status;
};
