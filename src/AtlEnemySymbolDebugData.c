#include "types.h"

typedef struct AtlEnemySymbolDebugData AtlEnemySymbolDebugData;

struct AtlEnemySymbolDebugData {
    sdfColor_t Color_EnemyEyeRange;
    sdfColor_t Color_EnemyMoveRange;
    sdfColor_t Color_SpawnerNormal;
    sdfColor_t Color_SpawnerTrap;
};

static AtlEnemySymbolDebugData *s_Inst;
