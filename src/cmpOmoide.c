#include "types.h"
#include "SKLID.h"
#include "cmpomoide.h"

SKLID *kuisibariTbl[5];
SKLID *g_aOmoide;
SKLID *spiritList;

// 0x218cae0
void *cmpSortUseSpritList(void) {
  void *v3;
  s64 i;
  SKLID *v6;
  s64 size;
  s32 v8;
  u64 *v9;
  s32 *items;

  v3 = Allocate(System_Collections_Generic_List_int_);
  __ctor_47770496(v3, spiritList->max_length);
  for (i = 0; ; ++i)
  {
    v6 = spiritList;
    if (i >= SLODWORD(v6->max_length))
      break;
    v6 = spiritList;
    size = v3->_size;
    v8 = v6[i];
    v9 = Method_System_Collections_Generic_List_int__Add__;
    ++v3->_version;
    items = v3->_items;
    if ((u32)size >= LODWORD(items->max_length))
    {
      _AddWithResize(v3, v8, *(const MethodInfo_2D8F530 **)(*(u64 *)(v9[4] + 192) + 112));
    }
    else
    {
      v3->_size = size + 1;
      items[size] = v8;
    }
  }
  return v3;
}

// 0x218cc50
bool OmoideSklCheck(SKLID _sklID) {
  return IndexOf_Int32Enum_(g_aOmoide, sklID) != -1;
}

// 0x218cce0
bool cmpSpiritSklCheck(SKLID _sklID) {
  return IndexOf_Int32Enum_(spiritList, sklID) != -1;
}
