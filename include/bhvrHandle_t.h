#pragma once
#include "types.h"
#include "EFFBEHAVIOR_TYPE.h"

typedef enum {
    OFFSET = 1,
} EFFBEHAVIOR_FLAG;

typedef struct bhvrHandle_t bhvrHandle_t;
typedef struct effBehavior_Params_Basic_t effBehavior_Params_Basic_t;
typedef struct effBehavior_Physics_t effBehavior_Physics_t;
typedef struct effPosture_t effPosture_t;

struct bhvrHandle_t {
    EFFBEHAVIOR_TYPE type;
    u32 number;
    u32 numall;
    EFFBEHAVIOR_FLAG flag;
    s32 frame;
    f32 count;
    effPosture_t *pPosture;
    effBehavior_Physics_t *pPhysics;
    effBehavior_Params_Basic_t *pParams;
    effBehavior_Params_Basic_t *pParamsBase;
};

struct effBehavior_Physics_t {
    f32 b_scale_r;
    f32 b_rotate;
    f32 b_rotate_r;
};
