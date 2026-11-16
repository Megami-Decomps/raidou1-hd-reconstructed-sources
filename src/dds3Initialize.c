#include "types.h"
#include "dds3initialize.h"
#include "dds3kerneldraw.h"

#define KEY_loadmes "loadmes"
#define KEY_common_shader "common_shader"

static bool firstCall;
static char *loadFixed;
static char *loadFirstOnly;
static char *loadScene;
static char **loadAlways;

// 0x229f380
bool dds3AlwaysAssetCheck(char *_assetName) {
  s64 v5;
  bool v6;

  if (SLODWORD(loadAlways->max_length) < 1)
    return 0;
  v5 = 0;
  do
  {
    v6 = op_Equality(loadAlways[v5][1], assetName, 0);
    if (v6)
      break;
    ++v5;
  }
  while (v5 < SLODWORD(loadAlways->max_length));
  return v6;
}

// 0x2296820
void *dds3Async(void) {
  void *v1;

  v1 = Allocate(Project_Kernel_dds3Initialize__Async_d__8);
  v1->__1__state = 0;
  return v1;
}

// 0x229f490
char *dds3GetFixedKey(char *key) {
  return Concat_54766928("_", key, 0);
}

// 0x229f4f0
void dds3KernelInit(void *list) {
  Initialize(list);
  Initialize(list);
  dds3FilterDefaultLoad(list);
  dds3FinishInit(list);
}
