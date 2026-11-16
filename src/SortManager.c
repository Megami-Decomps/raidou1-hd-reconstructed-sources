#include "types.h"
#include "buttonguide.h"
#include "sortmanager.h"
#include "tips.h"

void *sortText;
void *sortHelpText;
void *sortGuide;
void *reversePermit;

// 0x21e16c0
void SortGuideSet(SORT_GUIDE _id, bool _timer, s32 _waitTimer) {
  Il2CppObject *Item;
  Il2CppObject *v15;

  if (tipsProcessCheck())
    return;
  if (object___ContainsKey(sortGuide, id))
  {
    Item = object___get_Item(sortGuide, id);
    if (op_Inequality(GuideName, Item, 0))
    {
      v15 = object___get_Item(sortGuide, id);
      ButtonGuideDispSet(v15, timer, waitTimer);
    }
    return;
  }
  LogWarning("不明なボタンガイドID", 0);
}
