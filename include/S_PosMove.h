#pragma once
#include "types.h"

typedef enum {
    E_CAMERA_MOVE_TYPE_Non = 0,
    E_CAMERA_MOVE_TYPE_Set = 1,
    E_CAMERA_MOVE_TYPE_LineAS = 2,
    E_CAMERA_MOVE_TYPE_LineS = 3,
    E_CAMERA_MOVE_TYPE_Line = 4,
    E_CAMERA_MOVE_TYPE_Msk = 255,
    E_CAMERA_MOVE_TYPE_Arg = 4294901760,
    E_CAMERA_MOVE_TYPE_End = 256,
} E_CAMERA_MOVE_TYPE;

typedef enum {
    E_CAMERA_MOVE_TYPE_ASSET_Non = 0,
    E_CAMERA_MOVE_TYPE_ASSET_Set = 1,
    E_CAMERA_MOVE_TYPE_ASSET_LineAS = 2,
    E_CAMERA_MOVE_TYPE_ASSET_LineS = 4,
    E_CAMERA_MOVE_TYPE_ASSET_Line = 8,
    E_CAMERA_MOVE_TYPE_ASSET_End = 16,
} E_CAMERA_MOVE_TYPE_ASSET;

typedef enum {
    E_CAMERA_POSTYPE_Non = 0,
    E_CAMERA_POSTYPE_World = 1,
    E_CAMERA_POSTYPE_Char = 2,
    E_CAMERA_POSTYPE_CharLcl = 3,
    E_CAMERA_POSTYPE_CharLclNR = 4,
    E_CAMERA_POSTYPE_Char2 = 5,
    E_CAMERA_POSTYPE_Char3 = 6,
    E_CAMERA_POSTYPE_EventBoss = 7,
} E_CAMERA_POSTYPE;

typedef enum {
    E_CAMERA_POSBASE_Non = 0,
    E_CAMERA_POSBASE_SklUser = 1,
    E_CAMERA_POSBASE_Raidou = 2,
    E_CAMERA_POSBASE_CmbNkm = 3,
    E_CAMERA_POSBASE_EventBoss = 4,
} E_CAMERA_POSBASE;

typedef struct S_PosMove S_PosMove;

struct S_PosMove {
    sdfVector4_t m_vPos;
    E_CAMERA_POSTYPE m_ePosType;
    E_CAMERA_POSBASE m_eChar;
    f32 m_fFrm;
    E_CAMERA_MOVE_TYPE m_eCtrl;
    E_CAMERA_MOVE_TYPE_ASSET m_eCtrlAsset;
};
