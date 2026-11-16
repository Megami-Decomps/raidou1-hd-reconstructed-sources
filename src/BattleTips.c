#include "types.h"
#include "battletips.h"
#include "evtbit.h"
#include "sbtl.h"
#include "tips.h"

Step step;
void *encountNoTbl;

// 0x2022820
bool ChkTipsStart(void) {
  return Update();
}

// 0x2022a40
bool CallCheck(void) {
  void *v6;
  s32 Item;

  if (!int___ContainsKey(encountNoTbl, wk->encountno))
    return 0;
  v6 = encountNoTbl;
  Item = int___get_Item(v6, wk->encountno);
  if (evtBitCheck(Item))
    return 0;
  tipsTIPSStart(Item - 9984);
  StopKey();
  StopBattle();
  return 1;
}

// 0x2022890
bool Update(void) {
  if (step != 2)
  {
    if (step != 1)
    {
      if (!step)
      {
        if (!CallCheck())
          return 1;
        goto LABEL_23;
      }
      return 0;
    }
    if (tipsProcessCheck())
      return 0;
LABEL_23:
    ++step;
    return 0;
  }
  step = 0;
  RestartBattle();
  return 1;
}

// 0x2022c00
bool SummonTipsCall(s32 _groupID) {
  SBATTLE_WORK *wk_local;

  if (!evtBitCheck(10006))
  {
    if (groupID == 2 && wk->encountno == 448)
    {
      GBWK->EventBit[21] |= 0x400u;
      wk_local = wk;
      wk_local->callTips = 22;
      wk_local->eventgstat = 0;
      *(u32 *)&wk_local->eventno = 14;
      wk_local->status |= 0x400u;
      return 0;
    }
  }
  return 0;
}
