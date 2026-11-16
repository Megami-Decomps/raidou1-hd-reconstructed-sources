#pragma once
#include "types.h"
#include "E_CAMERA_FOV_TYPE.h"

typedef struct S_FovMove S_FovMove;

struct S_FovMove {
    f32 m_fFrm;
    E_CAMERA_FOV_TYPE m_eCtrl;
    f32 m_fovy;
};
