#pragma once
#include "types.h"
#include "E_CAMERA_MODE.h"

typedef struct SBTLCAMERA_WORK SBTLCAMERA_WORK;
typedef struct S_CameraMove S_CameraMove;
typedef struct S_DofCtrl S_DofCtrl;
typedef struct S_FovCtrl S_FovCtrl;
typedef struct S_PosCtrl S_PosCtrl;
typedef struct S_UpVCtrl S_UpVCtrl;
typedef struct dds3Basic_t dds3Basic_t;

struct S_CameraMove {
    S_PosCtrl *m_PosCtrlCam;
    S_PosCtrl *m_PosCtrlTgt;
    S_FovCtrl *m_FovCtrl;
    S_UpVCtrl *m_UpVCtrl;
    S_DofCtrl *m_DofCtrl;
};

struct SBTLCAMERA_WORK {
    sdfVector2_t followUpAngle;
    sdfVector2_t followUpAngleGoal;
    sdfVector4_t targetpos;
    sdfVector4_t direction;
    sdfVector4_t camerapos;
    sdfVector4_t targetpos_bk;
    sdfVector4_t direction_bk;
    sdfVector4_t camerapos_bk;
    S_CameraMove *m_CamMov;
    dds3Basic_t *cm;
    f32 distance;
    f32 fovy;
    sdfVector4_t vertical;
    E_CAMERA_MODE mode;
    E_CAMERA_MODE modeOld;
    sdfVector3_t CameraLockOnTargetPos;
    bool CameraLockOnNone;
    bool CameraHighTargetUse;
    s32 CameraHighTargetID;
    f32 GazeOff_GunMode_RY;
};
