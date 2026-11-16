#include "types.h"

static char *ChangeCharacter(char *sourceString, s32 charIndex, u16 newChar);

// 0x21f7a80
static char *ChangeCharacter(char *sourceString, s32 charIndex, u16 newChar) {
  char *v6;
  char *v8;
  char *v9;
  u16 v11;

  v11 = newChar;
  if (charIndex > 0)
  {
    v6 = Substring_54838176(sourceString, 0, charIndex, 0);
    goto LABEL_6;
  }
  v6 = "";
LABEL_6:
  v8 = ToString((u16)&v11, 0);
  if (sourceString->_stringLength - 1 <= charIndex)
    v9 = "";
  else
    v9 = Substring(sourceString, charIndex + 1, 0);
  return Concat_54831728(v6, v8, v9, 0);
}
