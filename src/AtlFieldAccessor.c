#include "types.h"
#include "atlfieldaccessor.h"
#include "atlfieldplayermotionconst.h"
#include "atlfieldtableresource.h"
#include "field.h"
#include "scr.h"

typedef struct MAP_OBJ_t MAP_OBJ_t;
typedef struct MapScriptEx MapScriptEx;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct mapNpc_t mapNpc_t;

static void *s_TmpScriptList;

// 0x1b4fd20
bool IsInitialized(void) {
  return IsInitialized();
}

// 0x1b4fd30
void Initialize(dds3ProcessID_t *planProsessID) {
  Initialize(planProsessID);
}

// 0x1b4fd40
void Terminate(void) {
  Terminate();
}

// 0x1b4fd50
void UnloadRequest(void) {
  ResetEnemySymbol(1);
  ClrUI(0);
}

// 0x1b4fda0
bool IsDoneUnload(void) {
  return 1;
}

// 0x1b4fdb0
void SetPause(bool isPause) {
  SetPause(isPause);
}

// 0x1b4fdc0
void SetVisible(bool isVisible) {
  SetVisible(isVisible);
}

// 0x1b4fdd0
MapScriptEx *CheckRunningScriptEx(void) {
  s32 v3;
  Il2CppObject *Item;
  MapScriptEx *v6;
  s32 size;
  void *v8;
  s32 v9;
  s32 v11;
  s32 v12;
  s32 v14;

  if (s_TmpScriptList)
  {
    goto LABEL_5;
  }
  v8 = Allocate(System_Collections_Generic_List_scrHandle_t_);
  __ctor_48217280(v8, 10);
  s_TmpScriptList = v8;
LABEL_5:
  scrGetRunningScripts(s_TmpScriptList);
  if (s_TmpScriptList->_size < 1)
  {
    v6 = 0;
LABEL_21:
    v14 = s_TmpScriptList->_version + 1;
    s_TmpScriptList->_size = 0;
    s_TmpScriptList->_version = v14;
    return v6;
  }
  else
  {
    v3 = 0;
    while (1)
    {
      Item = _get_Item(s_TmpScriptList, v3);
      v6 = Find(scriptEx, &Item[1], 0);
      if (v6)
        break;
      ++v3;
      size = s_TmpScriptList->_size;
      if (v3 >= size)
      {
        if (size < 1)
          goto LABEL_21;
        goto LABEL_16;
      }
    }
    if (s_TmpScriptList->_size < 1)
      goto LABEL_21;
LABEL_16:
    v9 = 0;
    do
    {
      _set_Item(s_TmpScriptList, v9++, 0);
      v11 = s_TmpScriptList->_size;
    }
    while (v9 < v11);
    v12 = s_TmpScriptList->_version + 1;
    s_TmpScriptList->_size = 0;
    s_TmpScriptList->_version = v12;
    if (v11 >= 1)
      Clear(s_TmpScriptList->_items, 0, v11, 0);
    return v6;
  }
}

// 0x1b50050
void CheckScriptClear(void) {
  MapScriptEx *v1;

  v1 = CheckRunningScriptEx();
  if (!v1 || v1->_delete_es_type == 1)
  {
    ResetEnemySymbol(0);
    ClrUI(0);
  }
}

// 0x1b4fd80
void Clear(bool isImmediateResetEnemy) {
  ResetEnemySymbol(isImmediateResetEnemy);
  ClrUI(0);
}

// 0x1b500b0
void OnReloadMapPoint(void) {
  OnReloadMapPoint();
}

// 0x1b500c0
void OnOpenTBox(s32 uniq) {
  s64 v3;
  s64 v4;

  if (IsInitialized())
  {
    v3 = *((u64 *)Method_AtlUtil_AtSingleton_AtlFieldManager__get_Instance__ + 4);
    if ((*(u16 *)(v3 + 309) & 1) == 0)
      v3 = sub_42269C(v3);
    v4 = *(u64 *)(*(u64 *)(v3 + 192) + 16);
    if ((*(u16 *)(v4 + 309) & 1) == 0)
      v4 = sub_42269C(v4);
    UseTBox_36365280(**(void ***)(v4 + 184), uniq, 0);
  }
}

// 0x1b50160
void LoadStart(s32 map, s32 floor) {
  LoadStart(map, floor);
}

// 0x1b50170
bool IsDoneLoad(void) {
  return IsDoneLoad();
}

// 0x1b50090
void ResetEnemySymbol(bool isImmediate) {
  ResetEnemySymbol(isImmediate);
}

// 0x1b50180
void AiRun(bool runmode) {
  AiRun(runmode);
}

// 0x1b50190
bool IsSurprise(bool isCheckMoveCoroutine) {
  return IsSurprise(isCheckMoveCoroutine);
}

// 0x1b501a0
bool IsPlayingSupriseMotion(void) {
  s64 v1;
  s64 v2;
  void *v3;
  dds3ModelHandle_t *m_hMdl_Model;
  AtlFieldPlayerMotionConst_Data *v5;
  bool v6;

  if (!IsInitialized())
    return 0;
  v1 = *((u64 *)Method_AtlUtil_AtSingleton_AtlFieldCharaManager__get_Instance__ + 4);
  if ((*(u16 *)(v1 + 309) & 1) != 0)
  {
    v2 = *(u64 *)(*(u64 *)(v1 + 192) + 16);
    if ((*(u16 *)(v2 + 309) & 1) != 0)
    {
LABEL_6:
      v3 = *(void *)(**(u64 **)(v2 + 184) + 32);
      if (!v3)
        return 0;
      goto LABEL_10;
    }
  }
  else
  {
    v2 = *(u64 *)(*(u64 *)(sub_42269C(v1) + 192) + 16);
    if ((*(u16 *)(v2 + 309) & 1) != 0)
      goto LABEL_6;
  }
  v3 = *(void *)(**(u64 **)(sub_42269C(v2) + 184) + 32);
  if (!v3)
    return 0;
LABEL_10:
  m_hMdl_Model = v3->m_hMdl_Model;
  if (!m_hMdl_Model)
    return 0;
  v5 = Find(0);
  v6 = 0;
  if (v5->m_RawID == m_hMdl_Model->motionMinorNum)
    return !IsEndMotion(v3, 0);
  return v6;
}

// 0x1b502d0
bool CheckSurpriseNakamaParam(sdfVector3_t *pos, f32 *dir) {
  return CheckSurpriseNakamaParam(pos, dir);
}

// 0x1b502e0
bool IsExistsEnemySymbol(void) {
  return IsExistsEnemySymbol();
}

// 0x1b502f0
bool IsScreenInEnemySymbolTarget(void) {
  return IsScreenInEnemySymbolTarget();
}

// 0x1b50300
void GetSymbolEncount_ZoomPos(f32 *_X, f32 *_Y, f32 *_Z) {
  GetSymbolEncount_ZoomPos(X, Y, Z);
}

// 0x1b50310
s32 CheckEncount(s32 *_EncountId, s32 *_EncountPackId, s32 *_Type2, s32 *_NakamaId, s32 *_EnemyId, s32 *_MapId, s32 *_FieldId) {
  return CheckEncount(EncountId, EncountPackId, Type2, NakamaId, EnemyId, MapId, FieldId);
}

// 0x1b50320
eFieldState GetBattleProdState(void) {
  return GetState();
}

// 0x1b50330
void PlayStartBattleProd(bool isSurprise, s32 surpriseNakamaID) {
  PlayStartBattleProd(isSurprise, surpriseNakamaID);
}

// 0x1b50340
void OnStartBattle(void) {
  OnStartBattle();
}

// 0x1b50350
void OnEndBattle(void) {
  OnEndBattle();
}

// 0x1b50360
void OnSpawnBattleUnit(SBTLUNIT_WORK *unit) {
  OnSpawnBattleUnit(unit);
}

// 0x1b500a0
void ClrUI(eFieldClearUIMode mode) {
  ClrUI(mode);
}

// 0x1b50370
void CancelPausePopup(void) {
  CancelPausePopup();
}

// 0x1b50380
bool IsThroughCameraCollision(const sdfVector3_t *camPos) {
  f32 z;
  f32 y;
  f32 x;
  s64 v5;
  s64 v6;
  void *v7;
  bool IsThroughCameraCollision;
  s16 v10;
  s16 v11;
  sdfVector3_t v12;

  z = camPos->z;
  y = camPos->y;
  x = camPos->x;
  v5 = *((u64 *)Method_AtlUtil_AtSingleton_AtlFieldCameraManager__get_Instance__ + 4);
  if ((*(u16 *)(v5 + 309) & 1) != 0)
  {
    v6 = *(u64 *)(*(u64 *)(v5 + 192) + 16);
    if ((*(u16 *)(v6 + 309) & 1) != 0)
      goto LABEL_4;
    goto LABEL_8;
  }
  v6 = *(u64 *)(*(u64 *)(sub_42269C(v5) + 192) + 16);
  if ((*(u16 *)(v6 + 309) & 1) != 0)
  {
LABEL_4:
    v7 = **(void ***)(v6 + 184);
    if (!v7)
      return (char)v7;
    goto LABEL_9;
  }
LABEL_8:
  v7 = **(void ***)(sub_42269C(v6) + 184);
  if (!v7)
    return (char)v7;
LABEL_9:
  v12.x = x;
  v12.y = y;
  v12.z = z;
  IsThroughCameraCollision = IsThroughCameraCollision(v7, v12, 0);
  v10 = 0;
  __ctor((System_Nullable_bool__o)&v10, IsThroughCameraCollision);
  v11 = v10;
  if ((u8)v10)
    LOBYTE(v7) = _get_Value((System_Nullable_bool__o)&v11);
  else
    LOBYTE(v7) = 0;
  return (char)v7;
}

// 0x1b50500
void ClearNPCs(void) {
  s64 v1;
  s64 v2;
  s64 v3;

  if (IsInitialized())
  {
    v1 = *((u64 *)Method_AtlUtil_AtSingleton_AtlFieldCharaManager__get_Instance__ + 4);
    if ((*(u16 *)(v1 + 309) & 1) != 0)
    {
      v2 = *(u64 *)(*(u64 *)(v1 + 192) + 16);
      if ((*(u16 *)(v2 + 309) & 1) != 0)
      {
LABEL_6:
        ClearNPCs(**(void ***)(v2 + 184), 0);
        return;
      }
    }
    else
    {
      v2 = *(u64 *)(*(u64 *)(sub_42269C(v1) + 192) + 16);
      if ((*(u16 *)(v2 + 309) & 1) != 0)
        goto LABEL_6;
    }
    v3 = sub_42269C(v2);
    ClearNPCs(**(void ***)(v3 + 184), 0);
  }
}

// 0x1b505c0
void AddNPC(mapNpc_t *npcData, dds3Basic_t *basic) {
  s64 v5;
  s64 v6;

  if (IsInitialized())
  {
    v5 = *((u64 *)Method_AtlUtil_AtSingleton_AtlFieldCharaManager__get_Instance__ + 4);
    if ((*(u16 *)(v5 + 309) & 1) == 0)
      v5 = sub_42269C(v5);
    v6 = *(u64 *)(*(u64 *)(v5 + 192) + 16);
    if ((*(u16 *)(v6 + 309) & 1) == 0)
      v6 = sub_42269C(v6);
    AddNPC(**(void ***)(v6 + 184), npcData, basic, 0);
  }
}

// 0x1b50670
MAP_OBJ_t *GetOverrideMapObj(void) {
  bool IsInitialized;
  MAP_OBJ_t *result;
  s64 v4;
  s64 v5;

  IsInitialized = IsInitialized();
  result = 0;
  if (!IsInitialized)
    return result;
  v4 = *((u64 *)Method_AtlUtil_AtSingleton_AtlFieldManager__get_Instance__ + 4);
  if ((*(u16 *)(v4 + 309) & 1) == 0)
    v4 = sub_42269C(v4);
  v5 = *(u64 *)(*(u64 *)(v4 + 192) + 16);
  if ((*(u16 *)(v5 + 309) & 1) == 0)
    v5 = sub_42269C(v5);
  return *(MAP_OBJ_t *)(**(u64 **)(v5 + 184) + 32);
}

// 0x1b50720
void ClearOverrideMapObj(void) {
  s64 v1;
  s64 v2;
  s64 v3;

  if (IsInitialized())
  {
    v1 = *((u64 *)Method_AtlUtil_AtSingleton_AtlFieldManager__get_Instance__ + 4);
    if ((*(u16 *)(v1 + 309) & 1) != 0)
    {
      v2 = *(u64 *)(*(u64 *)(v1 + 192) + 16);
      if ((*(u16 *)(v2 + 309) & 1) != 0)
      {
LABEL_6:
        ClearOverrideMapObj(**(void ***)(v2 + 184), 0);
        return;
      }
    }
    else
    {
      v2 = *(u64 *)(*(u64 *)(sub_42269C(v1) + 192) + 16);
      if ((*(u16 *)(v2 + 309) & 1) != 0)
        goto LABEL_6;
    }
    v3 = sub_42269C(v2);
    ClearOverrideMapObj(**(void ***)(v3 + 184), 0);
  }
}

// 0x1b507e0
void SetCameraCharaFadeEnable(bool isEnable) {
  s64 v3;
  s64 v4;

  if (!IsInitialized())
    return;
  v3 = *((u64 *)Method_AtlUtil_AtSingleton_AtlFieldCameraManager__get_Instance__ + 4);
  if ((*(u16 *)(v3 + 309) & 1) == 0)
    v3 = sub_42269C(v3);
  v4 = *(u64 *)(*(u64 *)(v3 + 192) + 16);
  if ((*(u16 *)(v4 + 309) & 1) == 0)
    v4 = sub_42269C(v4);
  *(u8 *)(**(u64 **)(v4 + 184) + 44) = isEnable;
}

// 0x1b50890
void RegisterAWParentTransform(void *tr) {
  s_AWParentTransform = tr;
}

// 0x1b508f0
bool IsNewMobSystem(void) {
  return 1;
}

// 0x1b50900
bool IsValidNewMobSystem(void) {
  s64 v1;
  s64 v2;
  s64 v3;

  if (!IsInitialized())
    return 0;
  v1 = *((u64 *)Method_AtlUtil_AtSingleton_AtlFieldMobManager__get_Instance__ + 4);
  if ((*(u16 *)(v1 + 309) & 1) == 0)
  {
    v2 = *(u64 *)(*(u64 *)(sub_42269C(v1) + 192) + 16);
    if ((*(u16 *)(v2 + 309) & 1) != 0)
      return IsValid(**(void ***)(v2 + 184), 0);
LABEL_10:
    v3 = sub_42269C(v2);
    return IsValid(**(void ***)(v3 + 184), 0);
  }
  v2 = *(u64 *)(*(u64 *)(v1 + 192) + 16);
  if ((*(u16 *)(v2 + 309) & 1) == 0)
    goto LABEL_10;
  return IsValid(**(void ***)(v2 + 184), 0);
}
