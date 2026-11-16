#pragma once
#include "types.h"
#include "TNEFFECT_BLEND.h"
#include "bilManager.h"
#include "dds3EffectHandle_t_DrawFunc.h"
#include "effect.h"

typedef enum {
    DDS3BILLBOARD_NORMAL = 0,
    DDS3BILLBOARD_P2A = 1,
    DDS3BILLBOARD_MULTI = 2,
    DDS3BILLBOARD_GENERAL = 3,
    DDS3BILLBOARD_SNORMAL = 4,
    DDS3BILLBOARD_ANIM = 5,
} DDS3BILLBOARD;

typedef enum {
    DDS3BILLANIM_STATE_END = 0,
    DDS3BILLANIM_STATE_RUN = 1,
} DDS3BILLANIM_STATE;

typedef enum {
    BILLANIM_MODE_NORMAL = 0,
    BILLANIM_MODE_ALPHA = 1,
    BILLANIM_MODE_AUTOEND = 16,
    BILLANIM_MODE_PLURAL = 268435456,
    BILLANIM_MODE_ADD = 2,
    BILLANIM_MODE_SUB = 4,
    BILLANIM_MODE_MTEX = 64,
    BILLANIM_MODE_AMTEX = 128,
    BILLANIM_MODE_P2APOLYGON = 256,
} BILLANIM_MODE;

typedef enum {
    BILLANIM_ATTR_MTEX = 64,
    BILLANIM_ATTR_AMTEX = 128,
    BILLANIM_ATTR_P2APOLYGON = 256,
} BILLANIM_ATTR;

typedef struct BillTable_t BillTable_t;
typedef struct Draw Draw;
typedef struct Frame Frame;
typedef struct MeshEditD MeshEditD;
typedef struct MeshJobD MeshJobD;
typedef struct P2A_ANIMATION_t P2A_ANIMATION_t;
typedef struct P2A_TEXANIM_t P2A_TEXANIM_t;
typedef struct Sub Sub;
typedef struct dds3BillAnimResource_t dds3BillAnimResource_t;
typedef struct dds3BillAnim_t dds3BillAnim_t;
typedef struct dds3BillResource_t dds3BillResource_t;
typedef struct dds3BillboardDirect_Param_t dds3BillboardDirect_Param_t;
typedef struct dds3Billboard_Basic_t dds3Billboard_Basic_t;
typedef struct dds3Billboard_MeshJob dds3Billboard_MeshJob;
typedef struct dds3Billboard_Normal_t dds3Billboard_Normal_t;
typedef struct dds3Billboard_P2A_t dds3Billboard_P2A_t;
typedef struct dds3Billboard_Tex_t dds3Billboard_Tex_t;
typedef struct effOption effOption;
typedef struct sdfDrawTag_t sdfDrawTag_t;
typedef struct sdfGrOt_t sdfGrOt_t;
typedef struct sdfMesh_IndexJob sdfMesh_IndexJob;

struct dds3Billboard_MeshJob {
    void *jobHandle;
    bool isAlive;
    void *mesh;
};

struct Frame {
    bool setTexture;
    f32 width;
    f32 height;
    s32 count;
    s32 *buf;
};

struct MeshEditD {
    void *body;
    void *dataArray;
    void *data;
    void *index;
    Sub *sub;
    void *bounds;
    s32 vertexCount;
    s32 indexCount;
    void *work;
    void *vertex;
    void *boundsJob;
    bool isWorking;
    s32 count;
    s32 camID;
    void *source;
    void *job;
    void *jobList;
    sdfMesh_IndexJob indexJob;
    Frame *frames;
};

struct MeshJobD {
    void *jobHandle;
    bool isAlive;
    void *mesh;
    MeshEditD *edit;
};

struct dds3BillboardDirect_Param_t {
    sdfVector4_t pos;
    sdfVector2_t scale;
    f32 rot;
    sdfVector4_t abgr;
    s32 frame;
    MeshJobD *mesh;
    s32 count;
};

struct dds3Billboard_Normal_t {
    sdfVector4_t pos;
    sdfVector4_t scale;
    f32 rot;
    sdfVector4_t abgr;
    dds3EffectHandle_t_DrawFunc Draw;
    u16 type;
    u16 mode;
    s32 camID;
    effOption *option;
    dds3BillResource_t *hResource;
    bool useDraw;
};

struct Draw {
    s32 count;
    sdfDrawTag_t *pBillTag;
    dds3Billboard_MeshJob *pMesh;
};

struct dds3BillResource_t {
    BILL_DRAW type;
    u32 count;
    sdfVector2_t uv[2];
    f32 cx;
    f32 cy;
    f32 width;
    f32 height;
    Draw *draw[5];
    dds3BillResource_t *next;
};

struct P2A_ANIMATION_t {
    P2A_TEXANIM_t *spranm;
    u32 *alpha;
    BILLANIM_ATTR attr;
    BILLANIM_MODE mode;
};

struct P2A_TEXANIM_t {
    s16 sx;
    s16 sy;
    s16 cx;
    s16 cy;
    s16 u1;
    s16 v1;
    s16 u2;
    s16 v2;
    s16 texid;
    s16 attr;
    f32 angle;
};

struct dds3BillAnimResource_t {
    P2A_ANIMATION_t *pAnimTable;
    u32 AnimNum;
    s32 count;
    dds3BillResource_t *pResList;
};

struct dds3BillAnim_t {
    s32 key;
    s32 wait;
    P2A_ANIMATION_t *pAnim;
    BILL_MODE mode;
    bool *useDraw;
};

struct dds3Billboard_P2A_t {
    sdfVector4_t pos;
    sdfVector4_t scale;
    f32 rot;
    sdfVector4_t abgr;
    dds3EffectHandle_t_DrawFunc Draw;
    u16 type;
    u16 mode;
    s32 camID;
    effOption *option;
    dds3BillAnimResource_t *hResource;
    DDS3BILLANIM_STATE state;
    BILLANIM_MODE animMode;
    u32 number;
    u32 Anim_n;
    dds3BillAnim_t *pAnim;
    BILL_DRAW drawType;
};

extern BillTable_t *BillboardTable;
extern dds3Billboard_Basic_t *hGeneralBillboard;

dds3Billboard_Basic_t *dds3BillboardGeneralCreate(u32 index);
void dds3BillboardSetBlend(dds3Billboard_Basic_t *handle, TNEFFECT_BLEND blend);
void *dds3BillboardTexHandleAndUVGet(dds3Billboard_Basic_t *handle, dds3Billboard_Tex_t *pTex);
void dds3BillboardManagerInit(void);
void dds3BillboardManagerExit(void);
void dds3BillboardLinkOt(void);
dds3Billboard_Normal_t *dds3BillboardNormalCreate(void *pData);
dds3Billboard_P2A_t *dds3BillboardP2ACreate(void *pData);
void *dds3BillboardGetAnimTex(dds3Billboard_Basic_t *hBillboard, dds3Billboard_Tex_t *pTex);
dds3Billboard_Basic_t *dds3BillboardCreate(DDS3BILLBOARD type, void *pData);
dds3Billboard_Basic_t *dds3BillboardCopy(void *handle);
void dds3BillboardDelete(void *handle);
void dds3BillboardDraw(void *handle);
dds3Billboard_Basic_t *dds3BillboardGeneral(s32 number);
void *dds3BillboardGetGeneralTex(s32 number);
void dds3BillboardSetPosition(void *handle, const sdfVector4_t *pPos);
void dds3BillboardSetRotate(void *handle, f32 rot);
void dds3BillboardSetScale(void *handle, f32 x, f32 y);
void dds3BillboardSetRGBA(void *handle, u32 abgr);
void SetRGBA(void *handle, const sdfVector4_t *abgr);
void dds3BillboardSetMode(dds3Billboard_Basic_t *hBillboard, BILL_MODE mode);
void dds3BillboardSetAnimKey(dds3Billboard_Basic_t *hBillboard, s32 frame, s32 wait);
void SetAnimKey(dds3Billboard_Basic_t *hBillboard, s32 frame);
void dds3BillboardSetAnimKey2(dds3Billboard_Basic_t *hBillboard, s32 frame);
s32 dds3BillboardGetAnimFrame(dds3Billboard_Basic_t *hBillboard);
f32 dds3BillboardGetDirectionRotate(const sdfVector4_t *pPos, const sdfVector4_t *pVec);
f32 dds3BillboardGetDirectionScale(const sdfVector4_t *pVec);
MeshJobD *dds3BillboardDirectInit(s32 billCount, s32 frameCount);
void dds3BillboardDirectDraw(sdfGrOt_t *pOt, dds3BillboardDirect_Param_t *pBillboard);
