#pragma once
#include "types.h"

// macros
// 0x1d69d30: void *CURRENT(void *_cmdlist)
#define CURRENT(_cmdlist) (cmdlist->pCurrent)

// 0x1d69d40: void *HEAD(void *_cmdlist)
#define HEAD(_cmdlist) (cmdlist->pHead)

// 0x1d69d50: void *TAIL(void *_cmdlist)
#define TAIL(_cmdlist) (cmdlist->pTail)

// 0x1d69d60: void *LISTTOP(void *_cmdlist)
#define LISTTOP(_cmdlist) (cmdlist->pListTop)

// 0x1d69d70: s32 ITEMCNT(void *_cmdlist)
#define ITEMCNT(_cmdlist) (cmdlist->ItemCnt)

// 0x1d69d80: s32 ITEMIDX(void *_cmdlist)
#define ITEMIDX(_cmdlist) (cmdlist->pCurrent->Index)

// 0x1d69d90: s32 STEPY(void *_cmdlist)
#define STEPY(_cmdlist) (cmdlist->StepY)

// 0x1d69da0: s32 LINEOFS(void *_cmdlist)
#define LINEOFS(_cmdlist) (cmdlist->ItemOfs)

// 0x1d69db0: s32 Y(void *_cmdlist, s32 _ofs)
#define Y(_cmdlist, _ofs) (cmdlist->StepY * (cmdlist->ItemOfs + ofs))

// 0x1d69dc0: s32 STAT(void *_cmdlist)
#define STAT(_cmdlist) (cmdlist->Stat)
