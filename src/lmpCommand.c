#include "types.h"

s32 NpcDelete(void);

// macros
// 0x1cf3960: s32 LMP_NPC_DELETE(void)
#define LMP_NPC_DELETE() (NpcDelete())
