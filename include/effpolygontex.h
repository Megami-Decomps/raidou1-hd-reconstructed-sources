#pragma once
#include "types.h"

typedef enum {
    EFFPOLYGON_TEX_TYPE_NON = 0,
    EFFPOLYGON_TEX_TYPE_BOARD = 1,
    EFFPOLYGON_TEX_TYPE_BOARD_LOOP = 2,
    EFFPOLYGON_TEX_TYPE_MAX = 3,
} EFFPOLYGON_TEX_TYPE;

typedef struct MeshEditPCU MeshEditPCU;
typedef struct Standard Standard;
typedef struct ctexlHandle_t ctexlHandle_t;
typedef struct dds3Billboard_Basic_t dds3Billboard_Basic_t;
typedef struct dds3Billboard_Tex_t dds3Billboard_Tex_t;
typedef struct effBehavior_AlphaParams_t effBehavior_AlphaParams_t;
typedef struct effBehavior_RGBParams_t effBehavior_RGBParams_t;
typedef struct effBehavior_SR_Params_t effBehavior_SR_Params_t;
typedef struct effOption effOption;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct effPolygonTexMesh effPolygonTexMesh;
typedef struct effPolygonTexMesh_Job effPolygonTexMesh_Job;
typedef struct effPolygonTex_Params_t effPolygonTex_Params_t;
typedef struct ptexHandle_t ptexHandle_t;

struct effPolygonTex_Params_t {
    effBehavior_RGBParams_t *rgb;
    effBehavior_AlphaParams_t *alpha;
    effBehavior_SR_Params_t *scale;
    effBehavior_SR_Params_t *rotate;
    f32 area;
    bool zTest;
};

struct ptexHandle_t {
    effOption *option;
    sdfVector4_t pos;
    sdfVector4_t rot;
    f32 scale;
    sdfVector4_t abgr;
    EFFPOLYGON_TEX_TYPE type;
    s32 frame;
    effPolygonTex_Params_t *param;
    dds3Billboard_Basic_t *hBillboard;
    ctexlHandle_t *hCTexList;
    u32 flags;
    s32 frame_end;
    s32 frame_out;
    effPolygonTexMesh *pMesh;
};

struct effPolygonTexMesh_Job {
    void *vertex;
    void *index;
    void *table;
    dds3Billboard_Tex_t tex;
    f32 mulF4;
    s32 texWidth;
    s32 texHeight;
};

struct effPolygonTexMesh {
    void *jobHandle;
    bool isAlive;
    void *mesh;
    MeshEditPCU *edit;
    effPolygonTexMesh_Job job;
};

ptexHandle_t *PartsCreate(Standard *pParts);
void Delete(effPartsHandle_t *handle);
ptexHandle_t *Copy(effPartsHandle_t *handle);
void ResourceCopy(effPartsHandle_t *dst, effPartsHandle_t *src);
void Draw(effPartsHandle_t *handle);
void PositionSet(effPartsHandle_t *handle, const sdfVector4_t *pPos);
void RotateSet(effPartsHandle_t *handle, const sdfVector4_t *pRot);
void ColorSet(effPartsHandle_t *handle, const sdfVector4_t *abgr);
void ScaleSet(effPartsHandle_t *handle, f32 scale);
