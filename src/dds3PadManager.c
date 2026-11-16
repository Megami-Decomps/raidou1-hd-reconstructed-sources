#include "types.h"
#include "cfg.h"
#include "configgamepad.h"
#include "dds3_pad.h"
#include "dds3padmanager.h"
#include "libsdf.h"
#include "sdfpad.h"

SDF_PAD ***PrivatePadMap;
u8 ***PrivatePadAnalog;
SDF_PAD **PrivatePadAnalogMap;
SDF_PAD ***PadMap;
u8 ***PadAnalog;
SDF_PAD **PadAnalogMap;
u8 *PadActPow;
u8 *PadActPow_goal;
u32 *PadActFrame;
static bool init_flg;
static s32 **padmap_to_keyid;
s32 *keyid_to_padmap;
static s32 **keyid_to_sprno;

static bool IsAnalogKeyBoard(s32 config_id);
static void Act2Sub(void);
static void ActUpdate(void);

// 0x2295200
void dds3PadInitialize(void) {
  s64 i;
  SDF_PAD *v4;
  SDF_PAD *v5;
  s64 j;
  u8 *v10;
  s64 v13;
  SDF_PAD *v15;
  u8 *v16;
  SDF_PAD *v19;
  SDF_PAD *v20;
  s64 k;
  SDF_PAD **v24;
  u8 *v25;
  SDF_PAD **v29;
  u8 *v30;

  for (i = 32; i != 128; i += 4)
  {
    v4 = PrivatePadMap[0][0];
    v5 = PadMap[0][0];
    *(u32 *)((char *)&v4->obj.klass + i) = 0;
    *(u32 *)((char *)&v5->obj.klass + i) = 0;
  }
  for (j = 32; j != 128; j += 4)
  {
    *(u32 *)((char *)&PrivatePadMap[1][0]->obj.klass + j) = 0;
    *(u32 *)((char *)&PadMap[1][0]->obj.klass + j) = 0;
  }
  PrivatePadAnalog[0][0][0] = 0;
  PrivatePadAnalog[0][0][1] = 0;
  v10 = PadAnalog[0][0];
  PrivatePadAnalogMap[0][0] = 0;
  v10[0] = 0;
  PadAnalog[0][0][1] = 0;
  PadAnalogMap[0][0] = 0;
  v13 = 32;
  PrivatePadAnalog[0][1][0] = 0;
  PrivatePadAnalog[0][1][1] = 0;
  v15 = PrivatePadAnalogMap[0];
  v16 = PadAnalog[0][1];
  v15[1] = 0;
  v16[0] = 0;
  PadAnalog[0][1][1] = 0;
  PadAnalogMap[0][1] = 0;
  do
  {
    v19 = PrivatePadMap[0][1];
    v20 = PadMap[0][1];
    *(u32 *)((char *)&v19->obj.klass + v13) = 0;
    *(u32 *)((char *)&v20->obj.klass + v13) = 0;
    v13 += 4;
  }
  while (v13 != 128);
  for (k = 32; k != 128; k += 4)
  {
    *(u32 *)((char *)&PrivatePadMap[1][1]->obj.klass + k) = 0;
    *(u32 *)((char *)&PadMap[1][1]->obj.klass + k) = 0;
  }
  PrivatePadAnalog[1][0][0] = 0;
  PrivatePadAnalog[1][0][1] = 0;
  v24 = PrivatePadAnalogMap;
  v25 = PadAnalog[1][0];
  v24[1][0] = 0;
  v25[0] = 0;
  PadAnalog[1][0][1] = 0;
  PadAnalogMap[1][0] = 0;
  PrivatePadAnalog[1][1][0] = 0;
  PrivatePadAnalog[1][1][1] = 0;
  v29 = PrivatePadAnalogMap;
  v30 = PadAnalog[1][1];
  v29[1][1] = 0;
  v30[0] = 0;
  PadAnalog[1][1][1] = 0;
  PadAnalogMap[1][1] = 0;
  PadActPow[0] = 0;
  PadActPow_goal[0] = 0;
  PadActFrame[0] = 0;
  PadActPow[1] = 0;
  PadActPow_goal[1] = 0;
  PadActFrame[1] = 0;
  init_flg = 1;
}

// 0x2297290
bool dds3PadIsInit(void) {
  return init_flg;
}

// 0x2296880
void dds3PadUpdate(void) {
  s64 i;
  s32 v3;
  s64 v4;
  s32 ConfigGAMEPAD;
  void *v6;
  s64 v7;
  s64 v8;
  Il2CppObject *Item;
  f32 v10;
  Il2CppObject *v11;
  f32 Y;
  f32 v13;
  f32 v14;
  f32 v16;
  f32 v17;
  s64 v18;
  Il2CppObject *v19;
  f32 v20;
  Il2CppObject *v21;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 v26;
  f32 v27;
  u64 CurrentKey;
  u64 OneShotKey;
  u64 RepeatKey;
  s64 j;
  s32 v33;
  s64 v34;
  s32 v35;
  s32 v36;
  s64 k;
  u32 v38;
  s32 v39;
  s64 v40;
  u32 v42;
  _BOOL4 v43;
  bool v44;
  s16 v45;
  s16 v46;
  s32 v47;
  s32 v49;
  s32 v50;
  Il2CppObject *v51;
  s32 v52;
  s32 v53;

  for (i = 0; i != 2; ++i)
  {
    ConfigGAMEPAD = cfgGetConfigGAMEPAD(2, 0);
    v6 = NewSpecific(f32, 5u);
    InitializeArray_55364416(v6, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__EBE41DA550A492286CFCFF1D8F04FDF65AC452C16779AFA8D4973D4A343D9A4B, 0);
    SetAxisPushVal(i, *((f32 *)&v6[2].klass + ConfigGAMEPAD), 0);
    v7 = (_System_k__BackingField->klass->vtable._6_Current.methodPtr)(_System_k__BackingField, (u32)i, _System_k__BackingField->klass->vtable._6_Current.method);
    v8 = v7;
    if (v7)
    {
      Item = object___get_Item(*(void *)(v7 + 32), 1);
      v10 = get_X(Item, 0) * 128.0;
      v11 = object___get_Item(*(void *)(v8 + 32), 1);
      Y = get_Y(v11, 0);
    }
    else
    {
      v10 = 0.0;
      Y = 0.0;
    }
    v13 = v10 + 128.0;
    v14 = (f32)(Y * 128.0) + 128.0;
    if ((f32)(v10 + 128.0) >= 256.0)
      v13 = 255.0;
    if (v13 <= -256.0)
      v16 = -255.0;
    else
      v16 = v13;
    if (v14 >= 256.0)
      v14 = 255.0;
    if (v14 <= -256.0)
      v17 = -255.0;
    else
      v17 = v14;
    v18 = i;
    PrivatePadAnalog[v18][0][0] = (s32)v16;
    PrivatePadAnalog[v18][0][1] = (s32)v17;
    if (v8)
    {
      v19 = object___get_Item(*(void *)(v8 + 32), 0);
      v20 = get_X(v19, 0) * 128.0;
      v21 = object___get_Item(*(void *)(v8 + 32), 0);
      v22 = get_Y(v21, 0);
    }
    else
    {
      v20 = 0.0;
      v22 = 0.0;
    }
    v23 = v20 + 128.0;
    v24 = (f32)(v22 * 128.0) + 128.0;
    if ((f32)(v20 + 128.0) >= 256.0)
      v23 = 255.0;
    if (v23 <= -256.0)
      v26 = -255.0;
    else
      v26 = v23;
    if (v24 >= 256.0)
      v24 = 255.0;
    if (v24 <= -256.0)
      v27 = -255.0;
    else
      v27 = v24;
    PrivatePadAnalog[v18][1][0] = (s32)v26;
    PrivatePadAnalog[v18][1][1] = (s32)v27;
    CurrentKey = GetCurrentKey(i, 0);
    OneShotKey = GetOneShotKey(i, 0);
    RepeatKey = GetRepeatKey(1, i, 0);
    for (j = 32; j != 128; j += 4)
    {
      v33 = *(u32 *)((char *)&padmap_to_keyid[0]->obj.klass + j);
      if ((v33 & 0xFFC0) != 0)
        v34 = 0;
      else
        v34 = 1 << v33;
      v35 = (v34 & CurrentKey) != 0;
      if ((v34 & OneShotKey) != 0)
        v35 |= 0x80u;
      if ((v34 & RepeatKey) != 0)
        v36 = v35 | 2;
      else
        v36 = v35;
      *(u32 *)((char *)&PrivatePadMap[0][i]->obj.klass + j) = v36;
    }
    for (k = 32; k != 128; k += 4)
    {
      v38 = *(u32 *)((char *)&padmap_to_keyid[0]->obj.klass + k);
      v39 = 1;
      v40 = 1 << v38;
      if ((v38 & 0xFFC0) != 0)
        v40 = 0;
      if ((v40 & CurrentKey) == 0)
      {
        v42 = cfgGetConfigGAMEPAD(1, 0) & 0xFFFFFFFE;
        v43 = (v38 & 0xFFFFFFFC) == 12;
        v44 = v42 == 2;
        if (v42 == 2)
          v45 = -4;
        else
          v45 = 4;
        if (!v44)
          v43 = v38 < 4;
        v46 = v38 + v45;
        if (!v43)
          v46 = v38;
        v40 = 1 << v46;
        if ((v46 & 0xFFC0) != 0)
          v40 = 0;
        v39 = (v40 & CurrentKey) != 0;
      }
      if ((v40 & OneShotKey) != 0)
        v39 |= 0x80u;
      if ((v40 & RepeatKey) != 0)
        v47 = v39 | 2;
      else
        v47 = v39;
      *(u32 *)((char *)&PrivatePadMap[1][i]->obj.klass + k) = v47;
    }
    {
      PrivatePadAnalogMap[i][0] = 0;
      if (v8)
        goto LABEL_106;
LABEL_114:
      v53 = 0;
      v3 = 0;
      goto LABEL_5;
    }
    v49 = (CurrentKey & 0xF0) != 0;
    if ((OneShotKey & 0xF0) != 0)
      v49 |= 0x80u;
    if ((RepeatKey & 0xF0) != 0)
      v50 = v49 | 2;
    else
      v50 = v49;
    PrivatePadAnalogMap[i][0] = v50;
LABEL_106:
    v51 = object___get_Item(*(void *)(v8 + 32), 1);
    if (!v51)
      goto LABEL_114;
    v52 = (CurrentKey & 0xF00) != 0;
    if ((OneShotKey & 0xF00) != 0)
      v52 |= 0x80u;
    if ((RepeatKey & 0xF00) != 0)
      v53 = v52 | 2;
    else
      v53 = v52;
    v3 = v53;
    v3 = v53;
LABEL_5:
    v4 = (s64)PrivatePadAnalogMap + 8 * i;
    *(u32 *)(*(u64 *)(v4 + 32) + 36) = v3;
  }
  ActUpdate();
}

// 0x2297680
u8 ***dds3PadGetAnalog(void) {
  return PadAnalog;
}

// 0x2297700
u8 dds3PadGetAnalogLX(bool keyboard_input) {
  s32 ConfigGAMEPAD;

  ConfigGAMEPAD = cfgGetConfigGAMEPAD(1, 0);
  return PadAnalog[0][(ConfigGAMEPAD & 0xFFFFFFFE) != 2][0];
}

// 0x2297810
u8 dds3PadGetAnalogLY(bool keyboard_input) {
  s32 ConfigGAMEPAD;

  ConfigGAMEPAD = cfgGetConfigGAMEPAD(1, 0);
  return PadAnalog[0][(ConfigGAMEPAD & 0xFFFFFFFE) != 2][1];
}

// 0x2297920
u8 dds3PadGetAnalogRX(bool keyboard_input) {
  s32 ConfigGAMEPAD;

  ConfigGAMEPAD = cfgGetConfigGAMEPAD(1, 0);
  return PadAnalog[0][(ConfigGAMEPAD & 0xFFFFFFFE) == 2][0];
}

// 0x2297a30
u8 dds3PadGetAnalogRY(bool keyboard_input) {
  s32 ConfigGAMEPAD;

  ConfigGAMEPAD = cfgGetConfigGAMEPAD(1, 0);
  return PadAnalog[0][(ConfigGAMEPAD & 0xFFFFFFFE) == 2][1];
}

// 0x2297b40
static bool IsAnalogKeyBoard(s32 config_id) {
  return 0;
}

// 0x2297390
bool dds3PadIsTypeCD(void) {
  return (cfgGetConfigGAMEPAD(1, 0) & 0xFFFFFFFE) == 2;
}

// 0x2297b50
s32 dds3PadGetNewID(SDF_PADMAP id) {
  return ConfigGameGetConfigPadMap(id, 1) & 0xFFFF00FF;
}

// 0x2297bc0
s32 dds3PadGetButtonArrangement(void) {
  return 0;
}

// 0x2297310
s32 dds3PadGetPadMapToKeyID(SDF_PADMAP id) {
  u8 v2;

  v2 = id;
  return padmap_to_keyid[0][v2];
}

// 0x2297bd0
s32 dds3PadGetKeyIDToPadMap(s32 id) {
  u16 v2;

  v2 = id;
  return keyid_to_padmap[v2];
}

// 0x2297c50
void *dds3PadGetKeyIDPADMAP(void) {
  void *v3;

  v3 = Allocate(System_Collections_Generic_List_int_);
  __ctor_47770768(v3, keyid_to_padmap);
  return v3;
}

// 0x2297d00
s32 dds3PadGetKeyIDToSprNo(s32 id) {
  u16 v2;

  v2 = id;
  return keyid_to_sprno[0][v2];
}

// 0x2297d80
static void Act2Sub(void) {
  u32 v4;
  u32 v5;
  s32 v6;
  u32 v7;
  u32 v8;
  s32 v9;

  v4 = PadActPow_goal[1];
  v5 = PadActPow[1];
  if (v5 >= v4)
  {
    if (v5 > v4)
    {
      if (v8)
      {
        v9 = v5 - v4;
        if (v9 < 33)
          goto LABEL_21;
      }
      else
      {
        if ((s32)(PadActPow[1] - v4) < 33)
          goto LABEL_21;
      }
      if (v7)
      {
        PadActPow[1] -= 32;
      }
      else
      {
        PadActPow[1] -= 32;
      }
      return;
    }
    if (v8)
    {
LABEL_22:
      PadActPow[1] = v4;
      return;
    }
LABEL_19:
    PadActPow[1] = v4;
    return;
  }
  v6 = v4 - v5;
  if (v6 < 33)
  {
LABEL_21:
    if (v7)
      goto LABEL_22;
    goto LABEL_19;
  }
  if (v7)
  {
    PadActPow[1] += 32;
  }
  else
  {
    PadActPow[1] += 32;
  }
}

// 0x2297f50
void dds3PadAct(u32 mode, u8 pow, u32 frame) {
  s32 v8;
  s32 v10;
  s32 v14;

  if (!cfgGetConfigGAME(9, 0))
    return;
  v8 = pow;
  if ((pow & 0x80) != 0)
    v8 = 128;
  if (mode)
    v10 = v8;
  else
    v10 = v8 != 0;
  if (mode)
  {
    *(u8 *)(*((u64 *)*((const MethodInfo *)dds3PadManager + 2).virtualMethodPointer + 7) + 33) = v10;
    Act2Sub();
    goto LABEL_14;
  }
  else
  {
    *(u8 *)(*((u64 *)*((const MethodInfo *)dds3PadManager + 2).virtualMethodPointer + 7) + 32) = v10;
    PadActPow[0] = v10;
    goto LABEL_14;
  }
LABEL_14:
  PadActFrame[mode != 0] = frame;
  if (mode)
  {
    v14 = PadActPow[mode != 0];
    sdfPadSetAct1(0, v14);
  }
  else
  {
    sdfPadSetAct0(0, v10);
  }
}

// 0x2298150
void dds3PadActAllStop(void) {
  PadActPow[0] = 0;
  PadActFrame[0] = 0;
  PadActPow[1] = 0;
  PadActFrame[1] = 0;
  sdfPadSetAct(0, 0, 0);
}

// 0x2297400
static void ActUpdate(void) {
  s32 v4;
  u32 *v6;
  s32 v9;
  s32 v13;

  if (!PadActFrame[0])
  {
LABEL_9:
    goto LABEL_10;
  }
  v4 = PadActFrame[0] - 1;
  PadActFrame[0] = v4;
  if (v4)
    goto LABEL_9;
  PadActPow[0] = 0;
  sdfPadSetAct0(0, 0);
LABEL_10:
  v6 = PadActFrame;
  if (!v6[1])
    return;
  v9 = v6[1] - 1;
  v6[1] = v9;
  if (!v9)
  {
    v13 = 0;
    PadActPow[1] = 0;
    sdfPadSetAct1(0, 0);
    return;
  }
  if (PadActPow[1] == PadActPow_goal[1])
    return;
  goto LABEL_30;
  if (PadActPow[1] != PadActPow_goal[1])
  {
LABEL_30:
    Act2Sub();
    v13 = PadActPow[1];
    sdfPadSetAct1(0, v13);
    return;
  }
}

// 0x2298210
bool dds3PadIsAnyKey(void) {
  return CHECK_TRIG(4096, 0)
      || CHECK_TRIG(4097, 0)
      || CHECK_TRIG(4098, 0)
      || CHECK_TRIG(4099, 0)
      || CHECK_TRIG(4104, 0)
      || CHECK_TRIG(4107, 0)
      || CHECK_TRIG(4105, 0)
      || CHECK_TRIG(4108, 0)
      || CHECK_TRIG(4110, 0)
      || CHECK_TRIG(4106, 0)
      || CHECK_TRIG(4109, 0)
      || CHECK_TRIG(4111, 0);
}
