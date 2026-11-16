#pragma once
#include "types.h"
#include "MODELTYPE.h"

typedef enum {
    PIB_CHUNK_TYPE_P2A = 1,
    PIB_CHUNK_TYPE_D3P = 2,
    PIB_CHUNK_TYPE_TRACK = 3,
    PIB_CHUNK_TYPE_BLUR = 4,
    PIB_CHUNK_TYPE_IPU = 5,
    PIB_CHUNK_TYPE_END = 65535,
} PIB_CHUNK_TYPE;

typedef enum {
    MDLSTAT_HIDE = 1,
    MDLSTAT_EFFECT_HIDE = 2,
    MDLSTAT_EFFECT_CLIP = 4,
    MDLSTAT_EFF_ONLY = 8,
    MDLSTAT_BG_HIDE = 16,
    MDLSTAT_HIDE_UPDATEPOS = 32,
} MDLSTAT;

typedef enum {
    INITCREATE = 1,
    AUTOSTART = 2,
} MOTION_FLAG;

typedef enum {
    dds3ModelEffectType_P2A = 0,
    dds3ModelEffectType_D3P = 1,
    dds3ModelEffectType_TRACK = 2,
    dds3ModelEffectType_IPU = 3,
} dds3ModelEffectType;

typedef struct dds3ModelEffectCtrlr_t dds3ModelEffectCtrlr_t;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct dds3ModelResrcPlayBook_t dds3ModelResrcPlayBook_t;
typedef struct dds3ModelResrc_t dds3ModelResrc_t;
typedef struct mdlEffectResrcItem_t mdlEffectResrcItem_t;
typedef struct mdlEffectResrcList_t mdlEffectResrcList_t;
typedef struct mdlLoadingTag_t mdlLoadingTag_t;
typedef struct mdlSetDef_t mdlSetDef_t;
typedef struct pibChunkItem_BLUR_t pibChunkItem_BLUR_t;
typedef struct pibChunkItem_IPU_t pibChunkItem_IPU_t;
typedef struct pibChunkItem_P2A_D3P_t pibChunkItem_P2A_D3P_t;
typedef struct pibChunkItem_TRACK_t pibChunkItem_TRACK_t;
typedef struct pibChunkItem_t pibChunkItem_t;
typedef struct pibChunk_t pibChunk_t;
typedef struct pibHeaderChunk_t pibHeaderChunk_t;
typedef struct sdfModelDef_t sdfModelDef_t;
typedef struct sdfModelRootNode_t sdfModelRootNode_t;
typedef struct sdfMotionCtrlr_t sdfMotionCtrlr_t;
typedef struct sdfMotionPlayBook_t sdfMotionPlayBook_t;

struct pibHeaderChunk_t {
    u32 version;
    u16 effectCount;
    u16 motionCount;
    pibChunk_t *chunk;
};

struct pibChunk_t {
    s32 group;
    pibChunkItem_t *item;
};

struct pibChunkItem_t {
    PIB_CHUNK_TYPE type;
};

struct pibChunkItem_P2A_D3P_t {
    u32 type;
    u32 markId;
    u16 count;
    u16 effectIndex;
    f32 zOffset;
};

struct pibChunkItem_TRACK_t {
    u32 type;
    u32 mark[2];
    u16 startFrame;
    u16 endFrame;
    u16 interval;
    u8 face;
    u8 blendAlgo;
    u32 colors[4];
};

struct pibChunkItem_BLUR_t {
    u32 type;
    u16 interval;
    u16 count;
    u32 startColor;
    u32 endColor;
};

struct pibChunkItem_IPU_t {
    u32 type;
    u32 texId;
    u32 startFrame;
    u8 fps;
    u8 loop;
    u16 effectIndex;
};

struct mdlEffectResrcItem_t {
    dds3ModelEffectType type;
    s32 count;
    void *handle;
};

struct mdlEffectResrcList_t {
    s32 count;
    s32 growStep;
    mdlEffectResrcItem_t *items;
};

struct dds3ModelResrcPlayBook_t {
    MOTION_FLAG flags;
    s16 playGroup;
    s16 firstMotion;
    sdfMotionPlayBook_t *ptr;
};

struct dds3ModelResrc_t {
    dds3ModelResrc_t *next;
    dds3ModelResrc_t *prev;
    MODELTYPE major;
    u16 minor;
    bool autoFreeFlag;
    dds3ModelHandle_t *models;
    sdfModelDef_t *modelDefPtr;
    dds3ModelResrcPlayBook_t *playbooks;
    pibHeaderChunk_t *effectData;
    mdlEffectResrcList_t *effectResrcList;
    f32 scale;
    f32 radius;
};

struct dds3ModelEffectCtrlr_t {
    dds3ModelEffectCtrlr_t *next;
    dds3ModelEffectType type;
    s16 playGroup;
    void *handle;
    void *work;
};

struct dds3ModelHandle_t {
    MDLSTAT stat;
    dds3ModelHandle_t *next;
    dds3ModelHandle_t *prev;
    dds3ModelResrc_t *resrc;
    s16 motionMajorNum;
    s16 motionMinorNum;
    dds3ModelEffectCtrlr_t *effects;
    sdfModelRootNode_t *modelRoot;
    sdfMotionCtrlr_t *motionCtrlr;
    sdfMotionCtrlr_t *motions[4];
    f32 radius;
    bool IsBustUp;
    bool IsMdlEffect_NonStop;
};

struct mdlSetDef_t {
    sdfModelDef_t *modelDefPtr;
    sdfMotionPlayBook_t *playbookPtr;
    pibHeaderChunk_t *effectData;
    mdlEffectResrcList_t *effectResrcList;
};

struct mdlLoadingTag_t {
    mdlLoadingTag_t *next;
    s32 minor;
};
