#include "types.h"
#include "expdraw.h"

typedef enum {
    expDrawStep_Init = 0,
    expDrawStep_Wait = 1,
    expDrawStep_OpenWindow = 2,
    expDrawStep_Draw = 3,
    expDrawStep_CloseWindow = 4,
    expDrawStep_Close = 5,
} expDrawStep;

typedef struct drawExpTextFormat drawExpTextFormat;

struct drawExpTextFormat {
    char *mText;
    s32 mDispTimer;
};

static expDrawStep mExpDrawStep;
static s32 mExpWait;
static s32 mWindowWait;
static bool mIsOpenWindow;
static char *mExpDrawText;
static s32 gOpenWaitTime;
static s32 gCloseWaitTime;
static void *mDrawTextList;
static void *mDrawTextDataList;

// 0x1b85860
void DrawExpUpText(void) {
  Il2CppObject *Item;
  Il2CppClass *klass;
  void *Instance;
  void *v12;
  s32 v13;
  bool v14;
  s32 v15;
  void *v16;
  Il2CppObject *v18;
  Il2CppClass *v19;
  void *v22;
  s32 v23;
  void *v24;
  sdfColor_t v26;
  sdfColor_t v27;

  if (mExpDrawStep > 5u)
    return;
  switch (mExpDrawStep)
  {
    case 0:
      mExpDrawText = 0;
      mExpWait = 0;
      goto LABEL_11;
    case 1:
      if (mDrawTextDataList->_size)
      {
        Item = _get_Item(mDrawTextDataList, 0);
        klass = Item[1].klass;
        mExpDrawText = klass;
        mExpWait = (s32)Item[1].monitor;
        _RemoveAt(mDrawTextDataList, 0);
        mWindowWait = gOpenWaitTime;
        Instance = get_Instance(0);
        v26.r = 1.0;
        v26.g = 1.0;
        v26.b = 1.0;
        v26.a = 1.0;
        DevilMesText(Instance, mExpDrawText, v26, 0);
        if (!mIsOpenWindow)
        {
          v12 = get_Instance(0);
          OpenExpMes(v12, 0);
          mIsOpenWindow = 1;
        }
        mExpDrawStep = 2;
      }
      break;
    case 2:
      v13 = mWindowWait - 1;
      v14 = mWindowWait == 1;
      mWindowWait = v13;
      if (v13 < 0 || v14)
      {
        mWindowWait = 0;
        mExpDrawStep = 3;
      }
      break;
    case 3:
      v15 = mExpWait - 1;
      v14 = mExpWait == 1;
      mExpWait = v15;
      if (v15 < 0 || v14)
      {
        v16 = mDrawTextDataList;
        if (v16->_size)
        {
          v16 = mDrawTextDataList;
          v18 = _get_Item(v16, 0);
          v19 = v18[1].klass;
          mExpDrawText = v19;
          mExpWait = (s32)v18[1].monitor;
          _RemoveAt(mDrawTextDataList, 0);
          v22 = get_Instance(0);
          v27.r = 1.0;
          v27.g = 1.0;
          v27.b = 1.0;
          v27.a = 1.0;
          DevilMesText(v22, mExpDrawText, v27, 0);
        }
        else
        {
          *(u64 *)&mExpDrawStep = 5;
        }
      }
      break;
    case 4:
      v23 = mWindowWait - 1;
      v14 = mWindowWait == 1;
      mWindowWait = v23;
      if (v23 < 0 || v14)
      {
LABEL_11:
        mExpDrawStep = 1;
      }
      break;
    case 5:
      if (mIsOpenWindow)
      {
        v24 = get_Instance(0);
        CloseExpMes(v24, 0, 0);
        mIsOpenWindow = 0;
      }
      mWindowWait = gCloseWaitTime;
      mExpDrawStep = 4;
      break;
    default:
      return;
  }
}

// 0x1b85d30
void expReqDrawExpUpText(char *text, s32 timer) {
  drawExpTextFormat *v5;
  void *mDrawTextDataList_local;
  u64 *v8;
  s64 size;
  void *items;
  Il2CppClass **v11;

  v5 = Allocate(drawExpTextFormat);
  v5->mText = text;
  v5->mDispTimer = timer;
  mDrawTextDataList_local = mDrawTextDataList;
  v8 = Method_System_Collections_Generic_List_expDraw_drawExpTextFormat__Add__;
  size = mDrawTextDataList_local->_size;
  ++mDrawTextDataList_local->_version;
  items = mDrawTextDataList_local->_items;
  if ((u32)size >= LODWORD(items->max_length))
  {
    _AddWithResize(mDrawTextDataList_local, v5, *(const MethodInfo_2DFC660 **)(*(u64 *)(v8[4] + 192) + 112));
  }
  else
  {
    v11 = &items->obj.klass + size;
    v11[4] = v5;
    mDrawTextDataList_local->_size = size + 1;
  }
}

// 0x1b85e70
void expAllCancelExpUpText(bool _NotAnime) {
  s32 size;
  s32 v7;
  void *Instance;

  if (!mIsOpenWindow)
  {
    goto LABEL_5;
  }
  Instance = get_Instance(0);
  CloseExpMes(Instance, NotAnime, 0);
  mIsOpenWindow = 0;
LABEL_5:
  mExpDrawStep = 1;
  size = mDrawTextDataList->_size;
  v7 = mDrawTextDataList->_version + 1;
  mDrawTextDataList->_size = 0;
  mDrawTextDataList->_version = v7;
  if (size >= 1)
    Clear(mDrawTextDataList->_items, 0, size, 0);
}
