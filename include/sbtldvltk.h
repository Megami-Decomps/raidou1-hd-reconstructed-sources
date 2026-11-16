#pragma once
#include "types.h"
#include "SBTLDVLTK_MODE.h"
#include "kernel.h"

typedef struct SBTLDVLTK_LISTWORK SBTLDVLTK_LISTWORK;
typedef struct SBTLDVLTK_WORK SBTLDVLTK_WORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct sprHandle_t sprHandle_t;

extern char *sbtldvltk_filetbl;
extern char *devil_face_dummy;
extern char *devil_image_none;
extern char *devil_img_btl_none;
extern char *devil_img_goh_none;
extern s32 *sbtldvltk_index00;
extern dds3ProcessID_t *GlobalPID;
extern SBTLDVLTK_LISTWORK *pGlobalLWK;
extern SBTLUNIT_WORK *GlobalUnitWK;
extern u32 *GlobalStat;
extern s32 GlobalCurrentArray;
extern sprHandle_t *GlobalSpr;
extern u32 GlobalSprStat;
extern u8 **pGlobalMsg;
extern s32 g_strlen;
extern char *dvltkAseetName;
extern char *dvlFaceAssetName;
extern char *dvlIconAssetName;
extern char *dvlBtlIconAssetName;

char *sBtlGetFaceTexName(s32 id);
char *sBtlGetIconTexName(s32 id);
char *sBtlGetBtlIconTexName(s32 id);
char *sBtlGetGohIconTexName(s32 id);
bool sBtlGetShikimiEnemyIdNo(s32 id);
bool sBtlDrawText(SBTLDVLTK_WORK *dwk);
void sBtlAnimWaku(SBTLDVLTK_WORK *dwk);
bool sBtlCheckPriority_Battle(SBTLDVLTK_MODE mode1, SBTLDVLTK_MODE mode2);
u32 sBtlCheckDebugFlag(void);
sprHandle_t *sBtlGetSpriteHandle(void);
s32 sBtlGetKucyou(s32 DevilID);
SBTLDVLTK_LISTWORK *sBtlCreateDvltkList(void);
bool sBtlLoadDvltkData_Enemy(SBTLUNIT_WORK *wk);
SBTLDVLTK_MODE sBtlGetRandNo(SBTLDVLTK_MODE type1, SBTLDVLTK_MODE type2, SBTLDVLTK_MODE type3);
bool sBtlCreateWork(SBTLUNIT_WORK *wk);
SBTLDVLTK_WORK *sBtlCreateDvltk_Priority(SBTLDVLTK_LISTWORK *lwk, SBTLUNIT_WORK *wk, SBTLDVLTK_MODE mode);
SBTLDVLTK_WORK *sBtlCreateDvltk_Gouto(SBTLDVLTK_LISTWORK *lwk, SBTLUNIT_WORK *wk, SBTLDVLTK_MODE mode, s32 rndptn);
SBTLDVLTK_WORK *sBtlCreateDvltk_Kuda(SBTLDVLTK_LISTWORK *lwk, SBTLUNIT_WORK *wk, SBTLDVLTK_MODE mode);
SBTLDVLTK_WORK *sBtlCreateDvltk(SBTLDVLTK_LISTWORK *lwk, SBTLUNIT_WORK *wk, SBTLDVLTK_MODE mode, bool gouto, bool kuda);
bool Proc(SBTLDVLTK_LISTWORK *lwk);
bool sBtlSearchDvltk(SBTLDVLTK_LISTWORK *lwk, SBTLUNIT_WORK *wk);
bool Draw(SBTLDVLTK_LISTWORK *lwk);
bool sBtlReleaseDvltk_List(SBTLDVLTK_LISTWORK *lwk, u8 flg);
bool sBtlDeleteDvltkList(SBTLDVLTK_LISTWORK *lwk);
bool sBtlDrawTextFont(s32 x, s32 y, s32 z, u32 rgba, SBTLUNIT_WORK *wk, SBTLDVLTK_MODE mode, SBTLDVLTK_WORK *_dwk);
void sBtlCombDevilTalkSet(s32 _num);
void sBtlDeadDevilTalkSet(void);
void sBtlFirstSummonTextSet(SBTLUNIT_WORK *wk);
dds3ProcessFunc_t sBtlExt_CalcProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t sBtlExt_DrawProcess(dds3ProcessID_t *PID);
void sBtlExt_Free(s32 ArrayIndex);
void sBtlExt_ShutDown(dds3ProcessID_t *PID);
s32 sBtlExt_CreateBuffer(s32 DevilID, s32 ArrayIndex);
s32 sBtlExt_FreeBuffer(void);
s32 sBtlExt_MesReqEx(SBTLDVLTK_MODE Type, s32 ArrayIndex);
s32 sBtlExt_MesReq(s32 DevilID, SBTLDVLTK_MODE Type);
s32 sBtlExt_EndMes(void);
s32 sBtlExt_ChkMes(void);
s32 sBtlExtCommand_DVLTK_DSP(void);
s32 sBtlExtCommand_DVLTK_WAIT(void);
s32 sBtlLoadOnMemMsg(void);
s32 sBtlCheckMsgMemType(void);
