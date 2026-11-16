#include "types.h"
#include "sdfpad.h"

typedef struct Cb_t Cb_t;

static Cb_t *cbData[2];

// 0x2265270
void sdfPadControl(void) {
  Cb_t *v2;
  s32 *actDataBack;
  s32 *actData;
  s32 v5;
  s32 v6;
  f32 v7;
  f32 v8;
  Cb_t *v9;
  s32 *v10;
  s32 *v11;
  s32 v12;
  s32 v13;
  f32 v14;
  f32 v15;

  Update();
  v2 = cbData[0];
  actData = v2->actData;
  actDataBack = v2->actDataBack;
  v6 = actData[0];
  v5 = actData[1];
  if (v6 != actDataBack[0] || v5 != actDataBack[1])
  {
    actDataBack[0] = v6;
    actDataBack[1] = v5;
    v7 = (f32)v5 / 255.0;
    v8 = v6;
    (_System_k__BackingField->klass->vtable._13_UpdateVibration.methodPtr)(_System_k__BackingField, 0, _System_k__BackingField->klass->vtable._13_UpdateVibration.v7, v8);
  }
  v9 = cbData[1];
  v11 = v9->actData;
  v10 = v9->actDataBack;
  v13 = v11[0];
  v12 = v11[1];
  if (v13 != v10[0] || v12 != v10[1])
  {
    v10[0] = v13;
    v10[1] = v12;
    v14 = (f32)v12 / 255.0;
    v15 = v13;
    (_System_k__BackingField->klass->vtable._13_UpdateVibration.methodPtr)(_System_k__BackingField, 1, _System_k__BackingField->klass->vtable._13_UpdateVibration.v14, v15);
  }
}

// 0x2265420
void sdfPadSetAct0(s32 pad, s32 value) {
  cbData[pad]->actData[0] = value;
}

// 0x22654a0
void sdfPadSetAct1(s32 pad, s32 value) {
  u8 v3;

  v3 = value;
  cbData[pad]->actData[1] = v3;
}

// 0x2265520
void sdfPadSetAct(s32 pad, s32 value0, s32 value1) {
  u8 v4;
  u8 v5;
  s32 *actData;

  v4 = value1;
  v5 = value0;
  actData = cbData[pad]->actData;
  actData[0] = v5;
  actData[1] = v4;
}

// 0x22655b0
void sdfPadInitManager(void) {
  Il2CppObject *v1;
  Il2CppClass *v2;
  void *v3;
  Il2CppClass *klass;
  u32 *monitor;
  Il2CppObject *v9;
  Il2CppClass *v10;
  void *v11;
  Il2CppClass *v12;
  u32 *v13;
  Cb_t *v16;

  Init(2, 0);
  v1 = Allocate(Cb_t);
  v2 = NewSpecific(s32, 2u);
  v1[1].klass = v2;
  v3 = NewSpecific(s32, 2u);
  v1[1].monitor = v3;
  _ctor(v1, 0);
  klass = v1[1].klass;
  LODWORD(klass->_1.byval_arg.data) = 0;
  monitor = v1[1].monitor;
  monitor[8] = 0;
  HIDWORD(klass->_1.byval_arg.data) = 0;
  monitor[9] = 0;
  cbData[0] = (Cb_t *)v1;
  v9 = Allocate(Cb_t);
  v10 = NewSpecific(s32, 2u);
  v9[1].klass = v10;
  v11 = NewSpecific(s32, 2u);
  v9[1].monitor = v11;
  _ctor(v9, 0);
  v12 = v9[1].klass;
  LODWORD(v12->_1.byval_arg.data) = 0;
  v13 = v9[1].monitor;
  v13[8] = 0;
  HIDWORD(v12->_1.byval_arg.data) = 0;
  v13[9] = 0;
  v16 = cbData;
  v16[1] = (Cb_t *)v9;
}
