#pragma once
#include "types.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;

void mapEnemyTP(void);
void mapInit(dds3ProcessID_t *planProsessID);
void mapKill(void);
void mapFirstInit1St(void);
void mapInit1St(s32 _MapId);
bool mapChk1St(s32 _PopTableIdx, s32 *_DevilID, s32 *_EncountID);
void mapSet1StDone(s32 _PopTableIdx);
bool mapChkPopEpsode(s32 _PopTableIdx);
bool mapChkPopJKFlg(s32 _PopTableIdx);
void mapLoadStart(s32 map, s32 area);
bool mapLoadCheckDone(void);
void mapReset2(void);
void mapReset3(void);
void mapAiRun(bool runmode);
void mapModelFree(void);
bool mapModelFreeDoneCheck(void);
bool mapFree_MotionSe_All(void);
bool mapEnemy_GetFAtk(f32 *_X, f32 *_Y, f32 *_Z, f32 *_Dir);
bool mapEnemy_GetFAtkMotion(void);
bool mapChkSymbolEncount(void);
bool mapChkSymbolEncount_ScreenIn(void);
void mapGetSymbolEncount_ZoomPos(f32 *_X, f32 *_Y, f32 *_Z);
s32 mapEncountCheck(s32 *_EncountId, s32 *_EncountPackId, s32 *_Type2, s32 *_NakamaId, s32 *_EnemyId, s32 *_Map, s32 *_Field);
s32 mapGetSymbolNum(void);
void mapKEnemy_WorkClear(void);
s32 mapGetOikakeNum(void);
void mapAI_All_GiveUp(void);
void mapAI_All_Door(void);
void mapAI_All_Trap1(void);
void mapAI_All_Trap2(s32 aTableIndex);
void mapAI_All_Trap3(void);
void mapAI_All_Trap4(void);
void mapAI_Trap3_Direct(const sdfVector3_t *s_pos, f32 s_dir, const sdfVector3_t *e_pos, f32 e_dir, f32 movetime, f32 movehigh);
void mapDebug_AiDraw(void);
s32 mapCollision_PosToPosHitChk(const sdfVector3_t *frompos, const sdfVector3_t *topos);
s32 Collision_PosToPosHitChk(const sdfVector3_t *frompos, const sdfVector3_t *topos, sdfVector3_t *retpos);
bool mapCollisionHitChk2(const sdfVector3_t *oldpos, const sdfVector3_t *frompos, sdfVector3_t *retpos, bool aGroundMode);
bool mapCollisionHitChk(sdfVector3_t *phys_pos, sdfVector3_t *phys_oldpos);
void se3dPosSet(s32 Move3dSE_Acter, const sdfVector3_t *pos);
void mapDraw_KemuriReq_E(const sdfVector3_t *pos);
void mapDraw_KemuriReq_Big2(const sdfVector3_t *pos);
void mapCamera_SetQuake(s32 a, s32 b, s32 c);
void mapClrUI(void);
void mapFindPopTable(s32 _MapId, s32 _FloorId, s32 _Floor2Id, s32 *_StIdx, s32 *_Num);
