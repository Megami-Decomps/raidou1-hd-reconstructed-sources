#pragma once
#include "types.h"

#define UPDATEFOVY 1

#define DRAW 1
#define EXIT 2
#define LINK 4
#define INDEX 8
#define FLDEX 16

typedef enum {
    DDS3_AREABASIC_ITEMTYPE_OBJECT = 0,
    DDS3_AREABASIC_ITEMTYPE_EVENT = 1,
    DDS3_AREABASIC_ITEMTYPE_MAX = 2,
} DDS3_AREABASIC_ITEMTYPE;

typedef enum {
    BASIC_TYPE_WORLD = 0,
    BASIC_TYPE_SCENE = 1,
    BASIC_TYPE_AREA = 2,
    BASIC_TYPE_MOVER = 3,
    BASIC_TYPE_CAMERAOBJECT = 4,
    BASIC_TYPE_UNITOBJECT = 5,
    BASIC_TYPE_MATTEROBJECT = 6,
    BASIC_TYPE_EFFECTOBJECT = 7,
    BASIC_TYPE_EVENTOBJECT = 8,
    BASIC_TYPE_LIGHTOBJECT = 9,
    BASIC_TYPE_STATICMODEL = 10,
    BASIC_TYPE_EFFECT = 11,
    BASIC_TYPE_EVENT = 12,
    BASIC_TYPE_FOG = 13,
    BASIC_TYPE_LIGHT = 14,
    BASIC_TYPE_PATH = 15,
    BASIC_TYPE_POINT = 16,
    BASIC_TYPE_MAX = 17,
} BASIC_TYPE;

typedef enum {
    UPDATEPOSE = 1,
    UPDATETM = 2,
    ONGROUND = 4,
    POS2 = 8,
    SIN = 16,
} POSESET_FLAG;

typedef enum {
    DDS3_CAMERAOBJECT_MODE_LOOKAT = 0,
    DDS3_CAMERAOBJECT_MODE_FREE = 1,
    DDS3_CAMERAOBJECT_MODE_MAX = 2,
} DDS3_CAMERAOBJECT_MODE;

typedef enum {
    DDS3_EFFECTOBJECT_TYPE_D3P = 1,
    DDS3_EFFECTOBJECT_TYPE_P2A = 2,
    DDS3_EFFECTOBJECT_TYPE_TMX = 3,
    DDS3_EFFECTOBJECT_TYPE_BILLBOARD = 4,
    DDS3_EFFECTOBJECT_TYPE_BED = 5,
    DDS3_EFFECTOBJECT_TYPE_ESP = 6,
    DDS3_EFFECTOBJECT_TYPE_MG1 = 7,
    DDS3_EFFECTOBJECT_TYPE_MG2 = 8,
} DDS3_EFFECTOBJECT_TYPE;

typedef enum {
    SCENEON = 1,
    SCENEANIME = 2,
    AUTOLINKOFF = 4,
    SCENEPROXY = 8,
} DDS3_LIGHTOBJ_FLAG;

typedef enum {
    IGNORE_DRAW_MODEL = 1,
    IGNORE_DRAW_RANGE = 2,
    IGNORE_COLLISION = 32,
    IGNORE_EVENT = 64,
    IGNORE_AREA = 128,
    IGNORE_ELAUTO = 256,
    SVKAGE = 512,
    MARUKAGE = 1024,
    USE_CLIP = 2048,
    IGNORE_DRAW_SHADOW = 4096,
    KUBI = 8192,
    EVT_SHADOW_ALPHA = 16384,
    EVT_SHADOW_YZAHYO = 32768,
    SPECULAR_ON = 65536,
    MARUKAGE_Y_ON = 131072,
    MARUKAGE_NO_HELPER = 262144,
    MARUKAGE_NPC = 524288,
    MOTION_ONLY = 1048576,
    BUSTUP = 2097152,
    USE_STEALTH = 4194304,
    MAXBIT = 19,
} DDS3_OBJECTBASE_FLAG;

typedef enum {
    DDS3_OBJECTBASE_ITEMTYPE_OWN = 0,
    DDS3_OBJECTBASE_ITEMTYPE_MOVER = 1,
    DDS3_OBJECTBASE_ITEMTYPE_DECIDER = 2,
    DDS3_OBJECTBASE_ITEMTYPE_MODEL = 3,
    DDS3_OBJECTBASE_ITEMTYPE_AREA = 4,
    DDS3_OBJECTBASE_ITEMTYPE_PADD01 = 5,
    DDS3_OBJECTBASE_ITEMTYPE_PADD02 = 6,
    DDS3_OBJECTBASE_ITEMTYPE_MAX = 7,
} DDS3_OBJECTBASE_ITEMTYPE;

typedef enum {
    DDS3_OBJECTBASE_MODELTYPE_UNIT = 0,
    DDS3_OBJECTBASE_MODELTYPE_MATTER = 1,
    DDS3_OBJECTBASE_MODELTYPE_EFFECT = 2,
    DDS3_OBJECTBASE_MODELTYPE_MAX = 3,
} DDS3_OBJECTBASE_MODELTYPE;

typedef enum {
    DDS3_PATHBASIC_CONTROL_FORWARD = 0,
    DDS3_PATHBASIC_CONTROL_BACK = 1,
    DDS3_PATHBASIC_CONTROL_MAX = 2,
} DDS3_PATHBASIC_CONTROL;

typedef enum {
    DDS3_PATHBASIC_FLAG_POS = 1,
    DDS3_PATHBASIC_FLAG_ROT = 2,
    DDS3_PATHBASIC_FLAG_FOVY = 4,
    DDS3_PATHBASIC_FLAG_STOP = 8,
    DDS3_PATHBASIC_FLAG_LIGHT = 16,
    DDS3_PATHBASIC_FLAG_LOOP = 32,
} DDS3_PATHBASIC_FLAG;

typedef enum {
    DDS3_BASICARRAY_SERACHDELETE_MODE_FIRST = 0,
    DDS3_BASICARRAY_SERACHDELETE_MODE_ALL = 1,
    DDS3_BASICARRAY_SERACHDELETE_MODE_MAX = 2,
} DDS3_BASICARRAY_SERACHDELETE_MODE;

typedef struct CamOffset CamOffset;
typedef struct Camera Camera;
typedef struct Light Light;
typedef struct Rot Rot;
typedef struct Trans Trans;
typedef struct dds3AreaBasicWorkData_t dds3AreaBasicWorkData_t;
typedef struct dds3BasicArrayHandle_t dds3BasicArrayHandle_t;
typedef struct dds3BasicArray_t dds3BasicArray_t;
typedef struct dds3BasicFunction_t dds3BasicFunction_t;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3CameraObjectBasicWorkData_t dds3CameraObjectBasicWorkData_t;
typedef struct dds3EffectObjectBasicWorkData_t dds3EffectObjectBasicWorkData_t;
typedef struct dds3EventObjectBasicWorkData_t dds3EventObjectBasicWorkData_t;
typedef struct dds3LightObjectBasicWorkData_t dds3LightObjectBasicWorkData_t;
typedef struct dds3ObjectBaseControlWorkData_t dds3ObjectBaseControlWorkData_t;
typedef struct dds3PathBasicControl_t dds3PathBasicControl_t;
typedef struct dds3PointBasicWorkData_t dds3PointBasicWorkData_t;
typedef struct dds3PoseSet_t dds3PoseSet_t;
typedef struct dds3SceneBasicTable_t dds3SceneBasicTable_t;
typedef struct dds3SceneBasic_t dds3SceneBasic_t;
typedef struct dds3WorldBasic_t dds3WorldBasic_t;
typedef struct dummy_fldResourceEffect_t dummy_fldResourceEffect_t;
typedef struct fldResourceLightPath_t fldResourceLightPath_t;
typedef struct sdf3DLightParallelPacket_t sdf3DLightParallelPacket_t;
typedef struct sdf3DLight_t sdf3DLight_t;
typedef struct sdfMotionCtrlr_t sdfMotionCtrlr_t;

typedef s32 (*checkFuncDelegate)(dds3Basic_t *pBasic);
typedef s32 (*dds3MoverBasicPadControl_t)(dds3PoseSet_t *pValue, const sdfMatrix4_t *mtx);
typedef bool (*dds3MoverBasicObjFunc_t)(dds3PoseSet_t *pValue, dds3Basic_t *pBasic);

struct dummy_fldResourceEffect_t {
    u32 flag;
    u32 type;
    u32 noEffect;
    f32 size[3];
    u32 offsetZ;
    u32 groupID;
    u32 param0;
    u32 param1;
};

struct Camera {
    u32 *pKey;
    f32 *pItem;
};

struct Trans {
    u32 *pKey;
    sdfVector3_t *pItem;
};

struct Rot {
    u32 *pKey;
    sdfVector4_t *pItem;
};

struct Light {
    u32 *pKey;
    fldResourceLightPath_t *pItem;
};

struct dds3AreaBasicWorkData_t {
    dds3BasicArrayHandle_t *hBasicArray;
};

struct dds3BasicFunction_t {
    void *constructor;
    void *destructor;
    void *mainprocuder;
    void *drawprocuder;
};

struct dds3PoseSet_t {
    sdfMatrix4_t workTM;
    sdfVector4_t pos;
    sdfVector4_t rot;
    sdfVector4_t scl;
    sdfVector4_t pos2;
    sdfVector4_t workpos;
    sdfVector4_t workrot;
    sdfVector4_t workscl;
    sdfVector4_t plane;
    u32 flag;
    f32 r;
    f32 frameFall;
    u32 pad;
};

struct dds3Basic_t {
    u32 flag;
    u32 serialID;
    char *name;
    u32 type;
    dds3BasicFunction_t *basicfunction;
    void *workdata;
    dds3PoseSet_t *poseset;
    dds3Basic_t *next;
    dds3Basic_t *prev;
    dds3Basic_t *worknext;
    dds3Basic_t *workprev;
    dds3Basic_t *workpointer;
    u32 color;
    u32 pad[3];
};

struct dds3CameraObjectBasicWorkData_t {
    sdfMatrix4_t cameraTM;
    sdfVector4_t eyeVector;
    sdfVector4_t vertical;
    sdfVector4_t targetPos;
    sdfVector4_t upVector;
    dds3ObjectBaseControlWorkData_t *pObjectBaseControlWorkData;
    u32 mode;
    u32 flag;
    f32 fovy;
};

struct CamOffset {
    sdfVector4_t cpos;
    sdfVector4_t tpos;
};

struct dds3EffectObjectBasicWorkData_t {
    dds3ObjectBaseControlWorkData_t *pObjectBaseControlWorkData;
    u32 stat;
    DDS3_EFFECTOBJECT_TYPE type;
    void *handle;
    sdfVector4_t linkpos;
    dds3Basic_t *linkbasic;
    u16 linkindex;
    BASIC_TYPE linkbasictype;
    void *para;
    void *cuth;
    s32 reserve1;
    s32 reserve2;
    s32 reserve3;
    dummy_fldResourceEffect_t *pFldEx;
    sdfVector4_t FldExBasePos;
};

struct dds3EventObjectBasicWorkData_t {
    dds3ObjectBaseControlWorkData_t *pObjectBaseControlWorkData;
    u32 padd[3];
};

struct dds3LightObjectBasicWorkData_t {
    sdf3DLight_t *Light;
    sdfVector4_t Ambient;
    f32 InsideR;
    f32 OutsideR;
    f32 Soften;
    f32 Bias;
    u32 AnimeType;
    DDS3_LIGHTOBJ_FLAG Flag;
    u32 BaseLightRGB;
    u32 BaseAmbientRGB;
    u16 SwitchFrame;
    u16 Reserve1;
    dds3ObjectBaseControlWorkData_t *ObjectBaseControlWorkData;
    sdf3DLightParallelPacket_t *LightPacket;
};

struct dds3ObjectBaseControlWorkData_t {
    DDS3_OBJECTBASE_FLAG flag;
    dds3BasicArrayHandle_t *hEventBasicArray;
    DDS3_OBJECTBASE_MODELTYPE modelType;
    void *pModel;
    dds3Basic_t *pBasic[7];
    void *pUserValue;
    sdfMotionCtrlr_t *pMot;
    s32 MotMode;
    f32 MotSpeed;
    f32 cam_len;
    s32 sdwchrid;
    s32 sdwnodeidx[24];
    u32 sdwid;
    s32 kubinodeidx;
};

struct dds3PathBasicControl_t {
    DDS3_PATHBASIC_CONTROL mode;
    u32 flag;
    f32 frameMax;
    f32 frame;
    Trans *pTransrate;
    Rot *pRotation;
    Camera *pFovy;
    Light *pLight;
};

struct dds3PointBasicWorkData_t {
    sdfVector4_t pos;
    sdfVector4_t rot;
    sdfVector4_t scl;
};

struct dds3SceneBasicTable_t {
    s32 linkcount;
    dds3Basic_t *firstbasic;
    dds3Basic_t *lastbasic;
};

struct dds3SceneBasic_t {
    s32 mapno;
    dds3SceneBasicTable_t *basictable;
    dds3Basic_t *activecamera;
    dds3Basic_t *activeunit;
    u8 *pScrFileData;
    bool visible;
    s32 pad[7];
};

struct dds3BasicArray_t {
    dds3Basic_t *target;
    s16 next;
    s16 prev;
};

struct dds3BasicArrayHandle_t {
    s16 firstindex;
    s16 lastindex;
    s16 nowindex;
    u16 count;
    dds3BasicArrayHandle_t *next;
    dds3BasicArrayHandle_t *prev;
};

struct dds3WorldBasic_t {
    dds3Basic_t *firstscene;
    dds3Basic_t *lastscene;
    dds3Basic_t *activescene;
    dds3Basic_t *controlscene;
    dds3BasicArray_t *basicarray;
    u16 basicarraycnt;
    s16 firstempty;
    s16 lastempty;
    u16 emptycount;
    dds3BasicArrayHandle_t *firstheader;
    dds3BasicArrayHandle_t *lastheader;
};
