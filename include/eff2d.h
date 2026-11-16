#pragma once
#include "types.h"

typedef enum {
    EFF2D_TYPE_NON = 0,
    EFF2D_TYPE_NORMAL = 1,
    EFF2D_TYPE_MAX = 2,
} EFF2D_TYPE;

typedef struct MeshEditPCU MeshEditPCU;
typedef struct Standard Standard;
typedef struct ctexlHandle_t ctexlHandle_t;
typedef struct dds3Billboard_Basic_t dds3Billboard_Basic_t;
typedef struct dds3Billboard_Tex_t dds3Billboard_Tex_t;
typedef struct eff2D_Params_t eff2D_Params_t;
typedef struct eff2dHandle_t eff2dHandle_t;
typedef struct eff2dMesh eff2dMesh;
typedef struct eff2dMesh_Job eff2dMesh_Job;
typedef struct effBehavior_AlphaParams_t effBehavior_AlphaParams_t;
typedef struct effBehavior_RGBParams_t effBehavior_RGBParams_t;
typedef struct effBehavior_SR_Params_t effBehavior_SR_Params_t;
typedef struct effOption effOption;
typedef struct effPartsHandle_t effPartsHandle_t;

struct eff2D_Params_t {
    effBehavior_RGBParams_t *rgb;
    effBehavior_AlphaParams_t *alpha;
    effBehavior_SR_Params_t *scale;
    effBehavior_SR_Params_t *rotate;
    u32 life;
    s32 x;
    s32 y;
};

struct eff2dHandle_t {
    effOption *option;
    sdfVector4_t abgr;
    EFF2D_TYPE type;
    s32 frame;
    eff2D_Params_t *param;
    dds3Billboard_Basic_t *hBillboard;
    ctexlHandle_t *hCTexList;
    eff2dMesh *pMesh;
};

struct eff2dMesh_Job {
    void *vertex;
    void *index;
    void *position;
    void *table;
    sdfVector4_t color;
    sdfVector4_t abgr;
};

struct eff2dMesh {
    void *jobHandle;
    bool isAlive;
    void *mesh;
    MeshEditPCU *edit;
    eff2dMesh_Job job;
    void *position;
    dds3Billboard_Tex_t TexInfo;
};

eff2dHandle_t *eff2PartsCreate(Standard *pParts);
void eff2Delete(effPartsHandle_t *handle);
eff2dHandle_t *Copy(effPartsHandle_t *handle);
void eff2ResourceCopy(effPartsHandle_t *dst, effPartsHandle_t *src);
void eff2Draw(effPartsHandle_t *handle);
void eff2ColorSet(effPartsHandle_t *handle, const sdfVector4_t *abgr);
