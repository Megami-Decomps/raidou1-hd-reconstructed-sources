#pragma once
#include "types.h"
#include "MODELTYPE.h"

typedef struct dds3Basic_t dds3Basic_t;
typedef struct tagSHP_MODEL_CB tagSHP_MODEL_CB;

struct tagSHP_MODEL_CB {
    dds3Basic_t *unit;
    u32 stat;
    s32 ot;
    s32 switchMotionNo;
};

void shpCreateScene(void);
void shpDeleteScene(void);
void shpMakeLightPacket(void);
void shpResetCamera(void);
void shpSetCamera(s32 a_type);
void shpUpdataCameraPar(void);
void shpShpUpdateModelPos(void);
void shpGetCameraPos(s32 a_type, f32 *a_px, f32 *a_py, f32 *a_pz);
void shpAddCameraPos(s32 a_type, f32 a_x, f32 a_y, f32 a_z);
void shpSetMove3D(f32 a_tgtx, f32 a_tgty, f32 a_tgtz, f32 a_ratio, s32 a_frame);
void shpSetMove3DDef(s32 a_frame);
void shpUpdateCamera(void);
void shpDeleteModel(tagSHP_MODEL_CB *cb);
void shpSetModel(s32 a_objId, MODELTYPE a_majorNo, s32 a_minorNo);
void shpSetMotion(s32 a_no, s32 a_motNo);
void shpSetMotionSpeed(s32 a_no, f32 a_motSpeed);
void shpSetSingleMotion(s32 a_no, s32 a_motNo);
void shpSetSmoothLoopMotion(s32 a_no, s32 a_motNo);
void shpSetSmoothSingleMotion(s32 a_no, s32 a_motNo);
void shpSetSwitchMotion(s32 a_no, s32 a_motNo);
void shpSetMotionPause(s32 a_no, bool a_bPause);
void shpSetPosModel(s32 a_no, f32 a_x, f32 a_y, f32 a_z);
void shpSetRotModel(s32 a_no, f32 a_x, f32 a_y, f32 a_z);
void shpSetRotYModel(s32 a_no, f32 a_y);
void shpSetSclModel(s32 a_no, f32 a_x, f32 a_y, f32 a_z);
void shpSetSclModelEx(s32 a_no, f32 a_scale);
void shpSetDrwModel(s32 a_no, bool a_draw);
void shpSetDrwModelAll(bool a_bDraw);
void shpSetColor(s32 a_no, u32 a_col);
void shpSetParamInit(s32 a_objId, MODELTYPE a_majorNo, s32 a_minorNo, s32 a_motionNo, f32 a_posx, f32 a_posy, f32 a_posz, f32 a_roty);
void shpSetTrans(bool a_bTrans);
void shpSetDebugPrint(bool a_bPrint);
void shpDrawFieldLine(void);
dds3Basic_t *shpGetBasic(s32 a_objId);
bool shpGetExist(s32 a_objId);
void Init(void);
void End(void);
