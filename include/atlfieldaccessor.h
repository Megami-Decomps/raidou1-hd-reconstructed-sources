#pragma once
#include "types.h"
#include "field.h"

typedef enum {
    eDeleteESType_OFF = 0,
    eDeleteESType_ON = 1,
} eDeleteESType;

typedef struct MAP_OBJ_t MAP_OBJ_t;
typedef struct MapScriptEx MapScriptEx;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct mapNpc_t mapNpc_t;

struct MapScriptEx {
    char *_script_name;
    s32 ScriptNameHash;
    eDeleteESType _delete_es_type;
};

bool IsInitialized(void);
void Initialize(dds3ProcessID_t *planProsessID);
void Terminate(void);
void UnloadRequest(void);
bool IsDoneUnload(void);
void SetPause(bool isPause);
void SetVisible(bool isVisible);
MapScriptEx *CheckRunningScriptEx(void);
void CheckScriptClear(void);
void Clear(bool isImmediateResetEnemy);
void OnReloadMapPoint(void);
void OnOpenTBox(s32 uniq);
void LoadStart(s32 map, s32 floor);
bool IsDoneLoad(void);
void ResetEnemySymbol(bool isImmediate);
void AiRun(bool runmode);
bool IsSurprise(bool isCheckMoveCoroutine);
bool IsPlayingSupriseMotion(void);
bool CheckSurpriseNakamaParam(sdfVector3_t *pos, f32 *dir);
bool IsExistsEnemySymbol(void);
bool IsScreenInEnemySymbolTarget(void);
void GetSymbolEncount_ZoomPos(f32 *_X, f32 *_Y, f32 *_Z);
s32 CheckEncount(s32 *_EncountId, s32 *_EncountPackId, s32 *_Type2, s32 *_NakamaId, s32 *_EnemyId, s32 *_MapId, s32 *_FieldId);
eFieldState GetBattleProdState(void);
void PlayStartBattleProd(bool isSurprise, s32 surpriseNakamaID);
void OnStartBattle(void);
void OnEndBattle(void);
void OnSpawnBattleUnit(SBTLUNIT_WORK *unit);
void ClrUI(eFieldClearUIMode mode);
void CancelPausePopup(void);
bool IsThroughCameraCollision(const sdfVector3_t *camPos);
void ClearNPCs(void);
void AddNPC(mapNpc_t *npcData, dds3Basic_t *basic);
MAP_OBJ_t *GetOverrideMapObj(void);
void ClearOverrideMapObj(void);
void SetCameraCharaFadeEnable(bool isEnable);
void RegisterAWParentTransform(void *tr);
bool IsNewMobSystem(void);
bool IsValidNewMobSystem(void);
