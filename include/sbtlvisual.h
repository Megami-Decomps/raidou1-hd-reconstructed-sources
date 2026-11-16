#pragma once
#include "types.h"
#include "MODELTYPE.h"

typedef struct MOTIONDATA_WORK MOTIONDATA_WORK;
typedef struct MOTIONMOVE_WORK MOTIONMOVE_WORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct SBTLVISUAL_DATA SBTLVISUAL_DATA;
typedef struct VISUALDATA_WORK VISUALDATA_WORK;
typedef struct V_POSITION_WORK V_POSITION_WORK;

extern V_POSITION_WORK *sbtleff_cylindertbl;
extern MOTIONMOVE_WORK *sbtlmotionmv_tbldata;
extern V_POSITION_WORK *sbtleff_cylindertbl_p;

MOTIONMOVE_WORK *sBtlGetMotionMoveData(MODELTYPE major, s32 minor);
f32 sBtlGetMotionMove(SBTLUNIT_WORK *wk, f32 now_frame);
V_POSITION_WORK *sBtlGetEffCylinderData(MODELTYPE major, s32 id);
VISUALDATA_WORK *sBtlGetVisualData(MODELTYPE major, s32 id);
VISUALDATA_WORK *sBtlGetVisualDataZ(s32 id);
void sBtlSetVisualDataZInit(s32 index, void *tbl);
VISUALDATA_WORK *sBtlGetVisualData_P(MODELTYPE major, s32 id);
MOTIONDATA_WORK *sBtlGetMotionVisualData(MODELTYPE major, s32 id1, s32 id2);
bool sBtlCheckMotionTiming(SBTLUNIT_WORK *wk);
f32 sBtlGetActionTime(SBTLUNIT_WORK *wk, s32 flg);
f32 sBtlGetSETime(SBTLUNIT_WORK *wk, s32 motionID);
void sBtlGetBouncePow(SBTLUNIT_WORK *wk, f32 *_Pow, s32 *_Rebound);
bool sBtlGetCylinderData_ID(MODELTYPE major, s32 minor, SBTLVISUAL_DATA *data);
bool sBtlGetCylinderData(SBTLUNIT_WORK *wk, SBTLVISUAL_DATA *data);
