#include "types.h"
#include "sdf3d.h"
#include "sdfmath.h"
#include "sdfmem.h"
#include "sdfpad.h"
#include "sdfrand.h"
#include "sdfsystem.h"
#include "sdfth.h"

#define FPS 60
#define FrameTime 0.016666668

static void *IOHandlerThread(void);

// 0x2268260
void sdfDummyFunc(void) {
  ;
}

// 0x2268270
static void *IOHandlerThread(void) {
  void *v1;

  v1 = Allocate(Project_libsdf_sdfSystem__IOHandlerThread_d__5);
  v1->__1__state = 0;
  return v1;
}

// 0x2268300
void sdfInit(void) {
  void *v6;

  sdfMemInit();
  sdfPadInitManager();
  sdfThInit();
  sdf3Init();
  sdfInitByTime(0);
  v6 = Allocate(Project_libsdf_sdfSystem__IOHandlerThread_d__5);
  v6->__1__state = 0;
  sdfThCreate(v6, 76);
}

// 0x2268640
void sdfInit_2(void *list) {
  Init();
  Init(list, 0);
}

// 0x22686e0
void sdfSetScene(void *obj) {
  UnityEngine_SceneManagement_Scene_o v4;

  v4.m_Handle = get_scene(hook, 0).m_Handle;
  MoveGameObjectToScene(obj, v4, 0);
}
