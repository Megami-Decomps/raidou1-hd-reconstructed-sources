#pragma once
#include "types.h"

typedef enum {
    E_CAMERA_DOF_TYPE_Non = 0,
    E_CAMERA_DOF_TYPE_Set = 1,
    E_CAMERA_DOF_TYPE_End = 16,
} E_CAMERA_DOF_TYPE;

typedef struct DepthOfFieldSetting DepthOfFieldSetting;
typedef struct S_DofCtrl S_DofCtrl;
typedef struct S_DofMove S_DofMove;

struct S_DofMove {
    f32 m_fFrm;
    E_CAMERA_DOF_TYPE m_eCtrl;
    DepthOfFieldSetting *m_dof;
};

struct S_DofCtrl {
    S_DofMove *m_dofMove;
    s32 m_cnt;
    s32 m_stp;
    s32 m_run;
    DepthOfFieldSetting *m_dofLast;
};
