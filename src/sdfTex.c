#include "types.h"
#include "sdftex.h"

#define baseScale 2

static f32 scale[4];
static f32 *mul;
static f32 *div;

static s32 GetScale(void *tex);

// 0x2268b60
void sdfTexFree(void *aHandle) {
  op_Equality(aHandle, 0, 0);
}

// 0x2268bd0
void sdfTexFreeDelayed(void *aHandle) {
  op_Equality(aHandle, 0, 0);
}

// 0x2268ca0
void *sdfTexSet(void *unit) {
  return ((void *(void *, const MethodInfo *))unit->klass->vtable._7_GetTexture.methodPtr)(unit, unit->klass->vtable._7_GetTexture.method);
}

// 0x2268cb0
static s32 GetScale(void *tex) {
  char *name;
  s32 stringLength;
  char *v4;
  u16 Chars;

  name = get_name(tex, 0);
  stringLength = name->_stringLength;
  v4 = name;
  if (get_Chars(name, stringLength - 2, 0) != 46)
    return 0;
  Chars = get_Chars(v4, stringLength - 1, 0);
  switch (Chars)
  {
    case '2':
      return 1;
    case '3':
      return 2;
    case '4':
      return 3;
  }
  return 0;
}

// 0x2268d60
f32 sdfTexScale(void *tex) {
  char *name;
  s32 stringLength;
  char *v7;
  u16 Chars;
  s64 v9;
  s32 v10;
  s64 v11;
  s64 v12;

  name = get_name(tex, 0);
  stringLength = name->_stringLength;
  v7 = name;
  Chars = get_Chars(name, stringLength - 2, 0);
  v9 = 0;
  if (Chars == 46)
  {
    v10 = get_Chars(v7, stringLength - 1, 0);
    v11 = 3;
    v12 = 2;
    if (v10 != 52)
      v11 = 0;
    if (v10 != 51)
      v12 = v11;
    if (v10 == 50)
      v9 = 1;
    else
      v9 = v12;
  }
  return scale[v9];
}

// 0x2268e40
f32 sdfTexScaleMulF4(void *tex) {
  char *name;
  s32 stringLength;
  char *v7;
  u16 Chars;
  s64 v9;
  s32 v10;
  s64 v11;
  s64 v12;

  name = get_name(tex, 0);
  stringLength = name->_stringLength;
  v7 = name;
  Chars = get_Chars(name, stringLength - 2, 0);
  v9 = 0;
  if (Chars == 46)
  {
    v10 = get_Chars(v7, stringLength - 1, 0);
    v11 = 3;
    v12 = 2;
    if (v10 != 52)
      v11 = 0;
    if (v10 != 51)
      v12 = v11;
    if (v10 == 50)
      v9 = 1;
    else
      v9 = v12;
  }
  return mul[v9];
}

// 0x2268f20
f32 sdfTexScaleDivF4(void *tex) {
  char *name;
  s32 stringLength;
  char *v7;
  u16 Chars;
  s64 v9;
  s32 v10;
  s64 v11;
  s64 v12;

  name = get_name(tex, 0);
  stringLength = name->_stringLength;
  v7 = name;
  Chars = get_Chars(name, stringLength - 2, 0);
  v9 = 0;
  if (Chars == 46)
  {
    v10 = get_Chars(v7, stringLength - 1, 0);
    v11 = 3;
    v12 = 2;
    if (v10 != 52)
      v11 = 0;
    if (v10 != 51)
      v12 = v11;
    if (v10 == 50)
      v9 = 1;
    else
      v9 = v12;
  }
  return div[v9];
}
