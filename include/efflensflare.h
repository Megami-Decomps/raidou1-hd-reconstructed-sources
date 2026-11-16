#pragma once
#include "types.h"

typedef enum {
    TYPE_0 = 0,
    TYPE_1 = 1,
    TYPE_MAX = 2,
} EFFLENSFLARE;

typedef struct MarkerJob MarkerJob;
typedef struct MeshEditPCU MeshEditPCU;
typedef struct Standard Standard;
typedef struct effBehavior_AlphaParams_t effBehavior_AlphaParams_t;
typedef struct effBehavior_RGBParams_t effBehavior_RGBParams_t;
typedef struct effLensFlare_MeshJob effLensFlare_MeshJob;
typedef struct effLensFlare_MeshJob_VertexJob effLensFlare_MeshJob_VertexJob;
typedef struct effLensFlare_Params_t effLensFlare_Params_t;
typedef struct effOption effOption;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct flareHandle_t flareHandle_t;
typedef struct sdfMesh_IndexJob sdfMesh_IndexJob;

struct effLensFlare_MeshJob_VertexJob {
    void *vertex;
    void *partsList;
    void *subTable;
    f32 fx;
    f32 fy;
    f32 scale;
    sdfVector4_t abgr_base;
};

struct effLensFlare_MeshJob {
    void *jobHandle;
    bool isAlive;
    void *mesh;
    MeshEditPCU *edit;
    effLensFlare_MeshJob_VertexJob vertexJob;
    sdfMesh_IndexJob indexJob;
    MarkerJob markerJob;
};

struct effLensFlare_Params_t {
    effBehavior_RGBParams_t *rgb;
    effBehavior_AlphaParams_t *alpha;
    f32 scale;
    s32 life;
    EFFLENSFLARE type;
};

struct flareHandle_t {
    effOption *option;
    sdfVector4_t pos;
    s32 frame;
    sdfVector4_t abgr;
    effLensFlare_Params_t *param;
    effLensFlare_MeshJob *pMesh;
};

flareHandle_t *PartsCreate(Standard *pParts);
void Delete(effPartsHandle_t *handle);
flareHandle_t *Copy(effPartsHandle_t *handle);
void Draw(effPartsHandle_t *handle);
void PositionSet(effPartsHandle_t *handle, const sdfVector4_t *pPos);
void ColorSet(effPartsHandle_t *handle, const sdfVector4_t *abgr);
