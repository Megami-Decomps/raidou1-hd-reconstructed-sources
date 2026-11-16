#include "types.h"
#include "sdf_gs_alpha.h"

typedef struct SDF_GS_ALPHA SDF_GS_ALPHA;

struct SDF_GS_ALPHA {
    s32 src;
    s32 dst;
    s32 op;
};

SDF_GS_ALPHA *SET_01010;
SDF_GS_ALPHA *SET_02010;
SDF_GS_ALPHA *SET_20010;
SDF_GS_ALPHA *SET_21000;
