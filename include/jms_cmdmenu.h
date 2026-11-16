#pragma once
#include "types.h"

// macros
// 0x1c9b760: void *HEAD(void *_cmdmenu)
#define HEAD(_cmdmenu) (cmdmenu->pCmdList->pHead)

// 0x1c9b770: void *TAIL(void *_cmdmenu)
#define TAIL(_cmdmenu) (cmdmenu->pCmdList->pTail)

// 0x1c9b780: void *CURRENT(void *_cmdmenu)
#define CURRENT(_cmdmenu) (cmdmenu->pCmdList->pCurrent)

// 0x1c9b790: void *LISTTOP(void *_cmdmenu)
#define LISTTOP(_cmdmenu) (cmdmenu->pCmdList->pListTop)

// 0x1c9b7a0: void *LIST(void *_cmdlist)
#define LIST(_cmdlist) (cmdlist->pCmdList)

// 0x1c9a210: s32 STEPY(void *_cmdlist)
#define STEPY(_cmdlist) (cmdlist->pCmdList->StepY)

// 0x1c9a2b0: s32 LINEOFS(void *_cmdlist)
#define LINEOFS(_cmdlist) (cmdlist->pCmdList->ItemOfs)

// 0x1c9a2c0: s32 Y(void *_cmdlist, s32 _ofs)
#define Y(_cmdlist, _ofs) (cmdlist->pCmdList->StepY * (cmdlist->pCmdList->ItemOfs + ofs))

// 0x1c9a500: s32 ITEMCNT(void *_cmdlist)
#define ITEMCNT(_cmdlist) (cmdlist->pCmdList->ItemCnt)

// 0x1c9b7b0: s32 ITEMIDX(void *_cmdmenu)
#define ITEMIDX(_cmdmenu) (cmdmenu->pCmdList->pCurrent->Index)
