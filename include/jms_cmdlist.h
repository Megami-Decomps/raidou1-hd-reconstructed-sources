#pragma once
#include "types.h"

// macros
// 0x1c9b6c0: void *CURRENT(void *_cmdlist)
#define CURRENT(_cmdlist) (cmdlist->pCurrent)

// 0x1c9b6d0: void *HEAD(void *_cmdlist)
#define HEAD(_cmdlist) (cmdlist->pHead)

// 0x1c9b6e0: void *TAIL(void *_cmdlist)
#define TAIL(_cmdlist) (cmdlist->pTail)

// 0x1c9b6f0: void *LISTTOP(void *_cmdlist)
#define LISTTOP(_cmdlist) (cmdlist->pListTop)

// 0x1c9b700: s32 ITEMCNT(void *_cmdlist)
#define ITEMCNT(_cmdlist) (cmdlist->ItemCnt)

// 0x1c996e0: s32 ITEMIDX(void *_cmdlist)
#define ITEMIDX(_cmdlist) (cmdlist->pCurrent->Index)

// 0x1c9b710: s32 STEPY(void *_cmdlist)
#define STEPY(_cmdlist) (cmdlist->StepY)

// 0x1c9b720: s32 LINEOFS(void *_cmdlist)
#define LINEOFS(_cmdlist) (cmdlist->ItemOfs)

// 0x1c9b730: s32 Y(void *_cmdlist, s32 _ofs)
#define Y(_cmdlist, _ofs) (cmdlist->StepY * (cmdlist->ItemOfs + ofs))

// 0x1c9b740: s32 STAT(void *_cmdlist)
#define STAT(_cmdlist) (cmdlist->Stat)
