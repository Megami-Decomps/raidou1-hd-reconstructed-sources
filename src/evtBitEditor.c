#include "types.h"
#include "dat.h"
#include "dds3_pad2.h"
#include "dds3kernelmisc.h"
#include "evtbit.h"
#include "evtbiteditor.h"
#include "kernel.h"

#define snum "0123456789ABCDEF"

typedef struct dds3ProcessID_t dds3ProcessID_t;

static char *list;
static s32 s_iBase;
static s32 s_iX;
static s32 s_iY;
static void *strbuf;

// 0x19e7060
char *evtBitToZenkaku(char *text) {
  s32 stringLength;
  void *v4;
  s32 i;
  char *v6;
  char *v8;
  u16 Chars;
  s32 v10;
  s32 v11;
  u16 v14;

  v14 = 0;
  stringLength = text->_stringLength;
  v4 = Allocate(System_Text_StringBuilder);
  _ctor_56602720(v4, stringLength, 0);
  if (stringLength >= 1)
  {
    for (i = 0; i != stringLength; ++i)
    {
      v8 = list[0];
      Chars = get_Chars(text, i, 0);
      v10 = IndexOf(v8, Chars, 0);
      if (v10 == -1)
      {
        v14 = get_Chars(text, i, 0);
        v6 = ToString((u16)&v14, 0);
      }
      else
      {
        v11 = v10;
        v6 = Substring_54838176(list[1], v11, 1, 0);
      }
      Append_56602800(v4, v6, 0);
    }
  }
  return ((char *(void *, const MethodInfo *))v4->klass->vtable._3_ToString.methodPtr)(v4, v4->klass->vtable._3_ToString.method);
}

// 0x19e7200
char *evtBitToHankaku(char *text) {
  s32 stringLength;
  void *v4;
  s32 i;
  char *v6;
  char *v8;
  u16 Chars;
  s32 v10;
  s32 v11;
  u16 v14;

  v14 = 0;
  stringLength = text->_stringLength;
  v4 = Allocate(System_Text_StringBuilder);
  _ctor_56602720(v4, stringLength, 0);
  if (stringLength >= 1)
  {
    for (i = 0; i != stringLength; ++i)
    {
      v8 = list[1];
      Chars = get_Chars(text, i, 0);
      v10 = IndexOf(v8, Chars, 0);
      if (v10 == -1)
      {
        v14 = get_Chars(text, i, 0);
        v6 = ToString((u16)&v14, 0);
      }
      else
      {
        v11 = v10;
        v6 = Substring_54838176(list[0], v11, 1, 0);
      }
      Append_56602800(v4, v6, 0);
    }
  }
  return ((char *(void *, const MethodInfo *))v4->klass->vtable._3_ToString.methodPtr)(v4, v4->klass->vtable._3_ToString.method);
}

// 0x19e73a0
dds3ProcessFunc_t dds3Process(dds3ProcessID_t *id) {
  bool v3;
  char *v6;
  char **v7;
  char *v8;
  s32 i;
  void *v11;
  u16 Chars;
  void *v15;
  bool v16;
  char **v17;
  s32 v20;
  void *v24;
  char **v25;
  void *v27;
  Il2CppObject *v28;
  char *v29;
  char *v30;
  s32 j;
  bool v32;
  char *v35;
  char *v37;
  f32 y;
  f32 x;
  char *v44;
  s32 v48;
  bool v49;
  s32 v52;
  s32 v53;
  bool v55;
  s32 v57;
  dds3ProcessFunc_t v58;
  bool v60;
  s32 v61;
  s64 v63;
  s64 v65;
  s32 data;
  s32 basex;
  s32 v69;

  basex = 0;
  Clear(strbuf);
  v69 = s_iX
      + 16
      * (s_iY + s_iBase);
  v3 = evtBitCheck(v69);
  v6 = ToString((s32)&v69, 0);
  if (v3)
    v7 = &" = ON";
  else
    v7 = &" = OFF";
  v8 = Concat_54766928(v6, *v7, 0);
  Append_56602800(strbuf, v8, 0);
  Append_56602800(strbuf, "\n", 0);
  Append_56602800(strbuf, "　　　　", 0);
  for (i = 0; i != 16; ++i)
  {
    v15 = strbuf;
    v16 = i == s_iX;
    v17 = &"<color=#FFFFFF>";
    if (v16)
      v17 = &"<color=#FF7300>";
    Append_56602800(v15, *v17, 0);
    v11 = strbuf;
    Chars = get_Chars("0123456789ABCDEF", i, 0);
    Append_56602736(v11, Chars, 0);
    Append_56602800(strbuf, "</color>", 0);
  }
  Append_56602800(strbuf, "\n", 0);
  v20 = 0;
  while (2)
  {
    v24 = strbuf;
    v16 = s_iY == v20;
    v69 = 16 * (s_iBase + v20);
    v25 = &"<color=#FFFFFF>";
    if (v16)
      v25 = &"<color=#FF7300>";
    Append_56602800(v24, *v25, 0);
    v27 = strbuf;
    data = v69;
    v28 = Box(s32, &data);
    v29 = Format("{0:X4}", v28, 0);
    v30 = Concat_54766928(v29, ":", 0);
    Append_56602800(v27, v30, 0);
    Append_56602800(strbuf, "</color>", 0);
    for (j = 0; j != 16; ++j)
    {
      v32 = evtBitCheck(j + v69);
      if (v32)
      {
        v35 = "1";
        if (j == s_iX)
          goto LABEL_49;
      }
      else
      {
        v35 = "0";
        if (j == s_iX)
          goto LABEL_49;
        if (s_iY == v20)
          goto LABEL_49;
        goto LABEL_57;
      }
      if (s_iY == v20)
      {
LABEL_49:
        v37 = "<color=#FF7300>";
        goto LABEL_51;
      }
LABEL_57:
      v37 = "<color=#FFFFFF>";
LABEL_51:
      if (j != s_iX)
      {
        goto LABEL_34;
      }
      if (s_iY == v20)
        v37 = "<color=#0073FF>";
LABEL_34:
      Append_56602800(strbuf, v37, 0);
      Append_56602800(strbuf, v35, 0);
      Append_56602800(strbuf, "</color>", 0);
    }
    Append_56602800(strbuf, "\n", 0);
    if (++v20 != 16)
      continue;
    break;
  }
  x = BitEditor.x;
  y = BitEditor.y;
  v44 = (strbuf->klass->vtable._3_ToString.methodPtr)(strbuf, strbuf->klass->vtable._3_ToString.method);
  SetTextPartsDataList_BITEDIT(10.0, (f32)(y * -0.5) + -50.0, x, y, 18, v44, 0);
  if (CHECK_REP(8, 0))
  {
    if (s_iBase < 1)
      goto LABEL_76;
    v48 = s_iBase - 16;
    s_iBase = v48;
    if (v48 >= 0)
      goto LABEL_76;
    s_iBase = 0;
    v55 = CHECK_REP(11, 0);
    if (!v55)
      goto LABEL_91;
  }
  else
  {
LABEL_76:
    v49 = CHECK_REP(11, 0);
    if (!v49)
      goto LABEL_91;
  }
  v52 = s_iBase;
  v53 = v52 + 16;
  if (v52 + 16 > 1023)
    goto LABEL_91;
  v52 = s_iBase;
  v53 = v52 + 16;
  s_iBase = v53;
  if (v52 + 32 >= 1025)
  {
    s_iBase = 1008;
  }
LABEL_91:
  basex = 0;
  v57 = dds3SelectMenu(1, 16, 1024, 16, 16, &basex, &s_iBase, &s_iX, &s_iY);
  if (v57 == -1)
  {
    v58 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
    _ctor(v58, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
    return v58;
  }
  v58 = 0;
  if (v57 == 1)
  {
    v69 = s_iX + 16 * (s_iY + s_iBase);
    v60 = evtBitCheck(v69);
    v61 = v69;
    if (v60)
    {
      v58 = 0;
      v63 = (s64)GBWK->EventBit + 4 * (v61 / 32);
      *(u32 *)(v63 + 32) &= ~(1 << v61);
      return v58;
    }
    if (v69)
    {
      if ((u32)(v61 - 2618) >= 0xFFFFFFC6)
        evtBitKityouItemAdd(v61);
      v58 = 0;
      v65 = (s64)GBWK->EventBit + 4 * (v61 / 32);
      *(u32 *)(v65 + 32) |= 1 << v61;
      return v58;
    }
    return 0;
  }
  return v58;
}
