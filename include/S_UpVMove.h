#pragma once
#include "types.h"
#include "E_CAMERA_FOV_TYPE.h"

typedef struct S_UpVMove S_UpVMove;

struct S_UpVMove {
    f32 m_fFrm;
    E_CAMERA_FOV_TYPE m_eCtrl;
    f32 m_UpV;
};
