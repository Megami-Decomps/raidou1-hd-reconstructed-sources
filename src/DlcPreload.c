#include "types.h"
#include "dlcpreload.h"

static char *names;
static bool *loaded;
static bool isLoading;

static bool Check(s32 index);

// 0x194d500
void *Exec(bool _again) {
  bool v3;
  void *v4;

  v3 = again;
  v4 = Allocate(Project_DlcPreload__Exec_d__3);
  v4->__1__state = 0;
  v4->_again = v3;
  return v4;
}

// 0x194d5a0
void *Again(bool again) {
  bool v3;
  void *v4;

  v3 = again;
  v4 = Allocate(Project_DlcPreload__Again_d__4);
  v4->__1__state = 0;
  v4->again = v3;
  return v4;
}

// 0x194d640
bool IsLoaded(void) {
  return !isLoading;
}

// 0x194d6b0
static bool Check(s32 index) {
  s64 v4;
  void *Dlc_k__BackingField;

  v4 = index;
  if (loaded[index])
    return 0;
  Dlc_k__BackingField = _Dlc_k__BackingField;
  return IsLoadable(Dlc_k__BackingField, names[v4], 0);
}
