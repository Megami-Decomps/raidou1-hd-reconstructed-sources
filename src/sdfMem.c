#include "types.h"
#include "sdfmem.h"
#include "sdfth.h"

#define ReleaseSize 20971520

static s64 allocated;
static void *funcList;

static void *Thread(void);

// 0x225f1e0
void sdfMemInit(void) {
  void *v1;

  v1 = Allocate(Project_libsdf_sdfMem__Thread_d__6);
  v1->__1__state = 0;
  sdfThCreate(v1, 78);
}

// 0x225f2c0
static void *Thread(void) {
  void *v1;

  v1 = Allocate(Project_libsdf_sdfMem__Thread_d__6);
  v1->__1__state = 0;
  return v1;
}

// 0x225f590
bool sdfMemCheckRelease(void) {
  if (!releaseOp)
    return 0;
  if (get_isDone(releaseOp, 0))
  {
    releaseOp = 0;
    return 0;
  }
  return 1;
}

// 0x225f680
void sdfMemResourcesRelease(void) {
  void *v1;
  s64 TotalAllocatedMemoryLong;

  v1 = UnloadUnusedAssets(0);
  releaseOp = v1;
  TotalAllocatedMemoryLong = GetTotalAllocatedMemoryLong(0);
  allocated = TotalAllocatedMemoryLong;
  return;
}

// 0x225f810
void sdfMemRelease(void) {
  Collect_56271200(0);
  sdfMemResourcesRelease();
}

// 0x225f8c0
void Release(s32 generation) {
  Collect(generation, 0);
  sdfMemResourcesRelease();
}

// 0x225f770
void sdfMemSetAllocated(void) {
  s64 TotalAllocatedMemoryLong;

  TotalAllocatedMemoryLong = GetTotalAllocatedMemoryLong(0);
  allocated = TotalAllocatedMemoryLong;
  return;
}

// 0x225f990
s64 sdfMemGetDifference(void) {
  s64 TotalAllocatedMemoryLong;

  TotalAllocatedMemoryLong = GetTotalAllocatedMemoryLong(0);
  return TotalAllocatedMemoryLong - allocated;
}

// 0x225fa30
void sdfMemSetFunc(void *func) {
  void *funcList_local;
  u64 *v5;
  s64 size;
  void *items;
  Il2CppClass **v8;

  funcList_local = funcList;
  v5 = Method_System_Collections_Generic_List_Func_bool___Add__;
  size = funcList_local->_size;
  ++funcList_local->_version;
  items = funcList_local->_items;
  if ((u32)size >= LODWORD(items->max_length))
  {
    _AddWithResize(funcList_local, func, *(const MethodInfo_2DFC660 **)(*(u64 *)(v5[4] + 192) + 112));
  }
  else
  {
    v8 = &items->obj.klass + size;
    funcList_local->_size = size + 1;
    v8[4] = func;
  }
}
