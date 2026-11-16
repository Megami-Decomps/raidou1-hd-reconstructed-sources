#include "types.h"
#include "dat.h"
#include "frname.h"
#include "localize.h"

static bool CheckLanguage(void);

// 0x1c94ee0
char *frGetString(void) {
  char *v1;
  s32 v3;
  char *v4;
  char *v5;

  v1 = frGet1NString();
  LanguageTYPE = GetLanguageTYPE();
  v3 = LanguageTYPE;
  v4 = frGet2NString();
  v5 = v4;
  if (v3)
    v4 = v1;
  else
    v5 = v1;
  return Concat_54831728(v4, " ", v5, 0);
}

// 0x1c94fa0
char *frGet1NString(void) {
  s32 name_language;

  name_language = GBWK->name_language;
  if (name_language == GetLanguage())
  {
    return GBWK->player_family;
  }
  return GetLocalizeText("SYSTEM_L0002", 1);
}

// 0x1c95120
char *frGet2NString(void) {
  s32 name_language;

  name_language = GBWK->name_language;
  if (name_language == GetLanguage())
  {
    return GBWK->player_first;
  }
  return GetLocalizeText("SYSTEM_L0003", 1);
}

// 0x1c952a0
static bool CheckLanguage(void) {
  s32 name_language;

  name_language = GBWK->name_language;
  return name_language == GetLanguage();
}
