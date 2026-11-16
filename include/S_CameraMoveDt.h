#pragma once
#include "types.h"

typedef struct S_CameraMoveDt S_CameraMoveDt;
typedef struct S_FovMove S_FovMove;
typedef struct S_PosMove S_PosMove;
typedef struct S_UpVMove S_UpVMove;

struct S_CameraMoveDt {
    S_PosMove *m_pPosMoveCam;
    S_PosMove *m_pPosMoveTgt;
    S_FovMove *m_pFovMove;
    S_UpVMove *m_pUpVMove;
};
