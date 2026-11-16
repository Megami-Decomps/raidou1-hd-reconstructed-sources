#include "types.h"
#include "libsdf.h"
#include "sdfassert.h"

static sdfAssertFunc_t sdfAssertFunc;

static void CallFunc(char *condition, char *stackTrace, s32 type);

// 0x225c540
static void CallFunc(char *condition, char *stackTrace, s32 type) {
  if (type == 4)
  {
    if (sdfAssertFunc)
      (sdfAssertFunc->invoke_impl)(sdfAssertFunc->method_code, condition, stackTrace, sdfAssertFunc->method);
  }
}

// 0x225c5d0
sdfAssertFunc_t sdfSetFunc(sdfAssertFunc_t func) {
  void *v5;

  if (!sdfAssertFunc)
  {
    v5 = Allocate(UnityEngine_Application_LogCallback);
    _ctor(v5, 0, Method_Project_libsdf_sdfAssert_CallFunc__, 0);
    add_logMessageReceived(v5, 0);
  }
  sdfAssertFunc = func;
  return sdfAssertFunc;
}
