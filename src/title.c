#include "types.h"
#include "dds3_pad.h"
#include "dds3adminiprocess.h"
#include "dds3basic.h"
#include "dds3cameraobjectbasic.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "dds3objectbase.h"
#include "dds3padmanager.h"
#include "dds3scenebasic.h"
#include "dds3unitobjectbasic.h"
#include "dds3worldbasic.h"
#include "kernel.h"
#include "mdl.h"
#include "sdf_vu0.h"
#include "sndat3.h"
#include "title.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;

sdfVector4_t DrawTex_pos;
sdfVector4_t DrawTex_uv;
sdfVector4_t DrawTex_color;
s32 Draw_old;
s32 Draw_new;
s32 Draw_move;
s32 Draw_trig;
dds3ProcessID_t *proc_debug;
s32 TestPad_count;

// 0x2232170
void titleRelease(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;
  s32 v5;
  dds3ProcessID_t *v9;

  workdata = proc->workdata;
  if ((SBYTE1(workdata[2].klass) & 0x80000000) == 0)
  {
    v5 = sndBgmStatus();
    if (v5 == 3)
    {
      sndBgmFadeOut2();
    }
    else
    {
      if (sndBgmStatus())
      {
        sndBgmStop();
        sndBgmFree();
      }
    }
    titleReleaseDraw(proc);
    v9 = &workdata[1];
    if (!dds3ExistProcess(v9))
    {
LABEL_23:
      titleTestRelease(proc);
      BYTE1(workdata[2].klass) |= 0x80u;
      return;
    }
    dds3KillProcess(v9, 1);
    goto LABEL_23;
  }
}

// 0x2232460
void titleTestRelease(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;
  Il2CppClass *klass;
  s32 v6;

  workdata = proc->workdata;
  klass = workdata[3].klass;
  v6 = SBYTE1(klass->_1.name);
  if ((v6 & 0x80000000) == 0)
  {
    if ((v6 & 3) == 1)
    {
      titleTestDeleteWorld(proc);
      LOBYTE(v6) = BYTE1(klass->_1.name) | 2;
    }
    BYTE1(klass->_1.name) = v6 | 0x80;
  }
}

// 0x2232650
s32 titleTestMain(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;
  Il2CppClass *klass;
  s32 result;
  s32 v8;
  s32 v9;

  workdata = proc->workdata;
  klass = workdata[3].klass;
  switch (LOBYTE(klass->_1.name))
  {
    case 0:
      BYTE1(klass->_1.name) = 0;
      LOBYTE(klass->_1.nestedTypes) = 0;
      titleTestCreateWorld(proc);
      BYTE1(klass->_1.name) |= 1u;
      titleTestCreateModel(proc);
      dds3FadeIn(0, 0, 0, 0x1Eu);
      result = 0;
      WORD1(klass->_1.name) = 0;
      goto LABEL_12;
    case 1:
      v8 = SWORD1(klass->_1.name);
      if (!WORD1(klass->_1.name))
      {
        dds3FadeOut(0, 0, 0, 0x1Eu);
        LOWORD(v8) = WORD1(klass->_1.name);
        goto LABEL_31;
      }
      if (v8 < 30)
      {
LABEL_31:
        WORD1(klass->_1.name) = v8 + 1;
        LOBYTE(klass->_1.nestedTypes) |= 2u;
        titleTestUpdateModel(proc);
        titleTestDraw(proc);
        return 0;
      }
      WORD1(klass->_1.name) = 0;
      result = titleTestPad(proc);
      if (result)
      {
        result = 0;
LABEL_12:
        ++LOBYTE(klass->_1.name);
      }
      return result;
    case 2:
      v9 = WORD1(klass->_1.name);
      if (v9 == 3)
      {
        LOBYTE(klass->_1.name) = 3;
        WORD1(klass->_1.name) = 4;
        return 0;
      }
      else
      {
        if (!WORD1(klass->_1.name))
        {
          titleTestRelease(proc);
          LOWORD(v9) = WORD1(klass->_1.name);
        }
        WORD1(klass->_1.name) = v9 + 1;
        return 0;
      }
    case 3:
      WORD1(klass->_1.name) = 0;
      LOBYTE(klass->_1.name) = 0;
      return 1;
    default:
      return 0;
  }
}

// 0x2233b40
void titleDeleteDraw(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;

  workdata = proc->workdata;
  if ((BYTE1(workdata[2].klass) & 0x40) == 0)
    BYTE1(workdata[2].klass) |= 0x40u;
}

// 0x2233bd0
void titleInit(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;

  workdata = proc->workdata;
  BYTE4(workdata[2].klass) = 0;
  LODWORD(workdata[2].klass) = 0;
}

// 0x2233c60
void titleCallNameEntry(void) {
  SequenceParameter *v1;

  v1 = Allocate(SequenceParameter);
  _ctor(v1, 0);
  v1->CallData2 = 1;
  dds3AdminiCallSequence(18, v1, 0);
}

// 0x2233cd0
bool titleGetPressAnyButton(void) {
  return CHECK_TRIG(4096, 1)
      || CHECK_TRIG(4097, 1)
      || CHECK_TRIG(4098, 1)
      || CHECK_TRIG(4099, 1)
      || CHECK_TRIG(4107, 1)
      || CHECK_TRIG(4108, 1)
      || CHECK_TRIG(4104, 1)
      || CHECK_TRIG(4105, 1)
      || CHECK_TRIG(4111, 1)
      || CHECK_TRIG(4110, 1);
}

// 0x2233db0
dds3ProcessFunc_t titleMain(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;
  s32 klass_low;
  u32 v6;
  s32 v7;
  char v9;
  char v10;
  SequenceParameter *v11;
  dds3ProcessFunc_t v12;
  char v14;
  char v15;
  u8 v16;
  s32 v17;

  workdata = proc->workdata;
  klass_low = LOBYTE(workdata[2].klass);
  if ((u32)(klass_low - 6) < 3)
  {
    BYTE4(workdata[2].klass) = 2;
LABEL_24:
    switch (klass_low)
    {
      case 0:
        dds3FadeOut(0, 0, 0, 1u);
        LOBYTE(workdata[2].klass) = 1;
        return 0;
      case 1:
        if (sndBgmStatus())
          return 0;
        sndBgmLoadId(29);
        v9 = 2;
        goto LABEL_38;
      case 2:
        if (sndBgmStatus() != 2)
          return 0;
        v9 = 3;
LABEL_38:
        LOBYTE(workdata[2].klass) = v9;
        return 0;
      case 5:
        if (titleTestMain(proc) == 1)
          goto LABEL_54;
        return 0;
      case 6:
        if (!WORD1(workdata[2].klass))
        {
          dds3FadeIn(0, 0, 0, 0x1Eu);
          sndBgmPlay(0, 0);
          goto LABEL_21;
        }
        if (SWORD1(workdata[2].klass) < 30)
          goto LABEL_21;
        if (CHECK_TRIG(4096, 1) || CHECK_TRIG(4110, 1))
        {
          if (SWORD1(workdata[2].klass) >= 900)
          {
            dds3FadeIn(0, 0, 0, 5u);
          }
          v10 = 7;
          goto LABEL_85;
        }
        v17 = SWORD1(workdata[2].klass);
        if (v17 == 900)
        {
          dds3FadeOut(0, 0, 0, 0x3Cu);
          sndBgmFadeOut();
          goto LABEL_21;
        }
        if (v17 < 960)
          goto LABEL_21;
        v10 = 1;
        goto LABEL_85;
      case 7:
        if (CHECK_TRIG(4097, 1))
        {
          WORD1(workdata[2].klass) = 30;
LABEL_54:
          LOBYTE(workdata[2].klass) = 6;
          return 0;
        }
        if (CHECK_TRIG(4096, 1))
        {
          WORD1(workdata[2].klass) = 0;
          LOBYTE(workdata[2].klass) = 8;
          return 0;
        }
        if (LOWORD(workdata[2].monitor))
          return 0;
        BYTE6(workdata[2].klass) = BYTE5(workdata[2].klass);
        if (CHECK_REP(4100, 1) || CHECK_REP(4102, 1))
        {
          v14 = BYTE5(workdata[2].klass);
          LOWORD(workdata[2].monitor) = 1;
          BYTE5(workdata[2].klass) = v14 - 1;
        }
        if (CHECK_REP(4101, 1) || CHECK_REP(4103, 1))
        {
          v15 = BYTE5(workdata[2].klass);
          LOWORD(workdata[2].monitor) = 1;
          v16 = v15 + 1;
          BYTE5(workdata[2].klass) = v16;
          if ((v16 & 0x80) == 0)
            goto LABEL_106;
        }
        else
        {
          if (LOWORD(workdata[2].monitor) != 1)
            return 0;
          v16 = BYTE5(workdata[2].klass);
          if ((v16 & 0x80) == 0)
          {
LABEL_106:
            if (v16 >= 3u)
            {
              BYTE5(workdata[2].klass) = 0;
              return 0;
            }
            return 0;
          }
        }
        BYTE5(workdata[2].klass) = 2;
        return 0;
      case 8:
        v7 = WORD1(workdata[2].klass);
        if (v7 == 60)
        {
          dds3FadeIn(0, 0, 0, 5u);
          WORD1(workdata[2].klass) = 0;
LABEL_97:
          LOBYTE(workdata[2].klass) = 10;
          return 0;
        }
        if (WORD1(workdata[2].klass))
          goto LABEL_22;
        dds3FadeOut(0, 0, 0, 0x3Cu);
        sndBgmFadeOut2();
        goto LABEL_21;
      case 9:
        if (dds3ExistProcess(&workdata[1].monitor))
        {
          return 0;
        }
        goto LABEL_97;
      case 10:
        v7 = SWORD1(workdata[2].klass);
        if (WORD1(workdata[2].klass))
        {
          if (v7 >= 3)
            LOBYTE(workdata[2].klass) = 11;
          goto LABEL_22;
        }
        titleRelease(proc);
        goto LABEL_21;
      case 11:
        if (BYTE5(workdata[2].klass) <= 2u)
        {
          v11 = Allocate(SequenceParameter);
          _ctor(v11, 0);
          v11->CallData2 = 1;
          dds3AdminiCallSequence(18, v11, 0);
        }
        v12 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
        _ctor(v12, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
        return v12;
      default:
        return 0;
    }
  }
  if (klass_low == 3)
  {
    BYTE4(workdata[2].klass) = 0;
    v6 = WORD1(workdata[2].klass);
    if (WORD1(workdata[2].klass))
      goto LABEL_11;
LABEL_18:
    dds3FadeIn(0, 0, 0, 0x1Eu);
    goto LABEL_21;
  }
  if (klass_low != 4)
  {
    BYTE4(workdata[2].klass) = -1;
    goto LABEL_24;
  }
  BYTE4(workdata[2].klass) = 1;
  v6 = WORD1(workdata[2].klass);
  if (!WORD1(workdata[2].klass))
    goto LABEL_18;
LABEL_11:
  if ((s16)v6 >= 30)
  {
    if (v6 <= 0x95)
    {
      if (titleGetPressAnyButton())
      {
        WORD1(workdata[2].klass) = 150;
        return 0;
      }
    }
    else if (v6 == 150)
    {
      dds3FadeOut(0, 0, 0, 0x1Eu);
    }
    else if (v6 >= 0xB4)
    {
      v10 = klass_low + 1;
LABEL_85:
      LOBYTE(workdata[2].klass) = v10;
      WORD1(workdata[2].klass) = 0;
      return 0;
    }
  }
LABEL_21:
  LOWORD(v7) = WORD1(workdata[2].klass);
LABEL_22:
  WORD1(workdata[2].klass) = v7 + 1;
  return 0;
}

// 0x22345e0
dds3ProcessFunc_t titleDraw(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;
  s32 klass_low;
  void *v6;
  void *v7;
  bool v8;
  bool v9;
  void *monitor;
  s32 monitor_low;
  s32 v14;
  u32 *p_x;
  s32 v17;
  s32 v18;
  s16 v19;
  s32 v21;

  workdata = proc->workdata;
  klass_low = LOBYTE(workdata[2].klass);
  if (klass_low == 6)
  {
    v6 = NewSpecific(s32, 6u);
    InitializeArray_55364416(v6, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__302C610156D1219BE093AB447823562AE3F4BA18B2ED33552C19031FFC7D8C92, 0);
    v7 = NewSpecific(s32, 6u);
    InitializeArray_55364416(v7, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__C88845A4A041D36D16C0B2BDD5DDEF521052DF5CE155B85456D6B41D233A2FA0, 0);
    v8 = CHECK_TRIG(4099, 1);
    if (v8)
    {
      v9 = v8;
      monitor = v6[1].monitor;
      Draw_trig ^= 1u;
      if ((s32)monitor >= 1 && v9)
      {
        v21 = 0;
        do
        {
          monitor = v6[1].monitor;
          ++v21;
        }
        while (v21 < (s32)monitor);
      }
    }
    klass_low = LOBYTE(workdata[2].klass);
  }
  if ((u32)(klass_low - 7) <= 1)
  {
    monitor_low = SLOWORD(workdata[2].monitor);
    if (monitor_low >= 1)
    {
      if (monitor_low == 1)
      {
        v14 = SBYTE6(workdata[2].klass);
        LOWORD(monitor_low) = 1;
        p_x = &DrawTex_pos.x;
        v17 = 192 * v14 + 2496;
        v18 = 192 * SBYTE5(workdata[2].klass) + 2496;
        p_x[12] = v17;
        p_x[13] = v18;
        p_x[14] = (v18 - v17) / 3;
      }
      if (((u16)monitor_low + 1) << 16 < 0x40000)
        v19 = monitor_low + 1;
      else
        v19 = 0;
      LOWORD(workdata[2].monitor) = v19;
    }
  }
  return 0;
}

// 0x2234830
dds3ProcessFunc_t titleProcess(dds3ProcessID_t *proc) {
  dds3ProcessID_t *v4;

  v4 = proc;
  return titleMain(v4);
}

// 0x22348b0
void titleShutdown(dds3ProcessID_t *proc) {
  dds3ProcessID_t *v4;

  v4 = proc;
  titleRelease(v4);
}

// 0x2234940
void titleInitialize(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;
  s64 naturalAligment;
  dds3ProcessFunc_t v5;
  dds3ProcessID_t *started;
  Il2CppObject *v7;
  s64 v8;

  workdata = proc->workdata;
  if (workdata)
  {
    if (workdata->klass->_2.naturalAligment < (u32)naturalAligment || workdata->klass->_2.typeHierarchy[naturalAligment - 1] != tagTITLE_WORK)
    {
      v7 = proc->workdata;
      goto LABEL_18;
    }
  }
  v5 = Allocate(dds3ProcessFunc_t);
  _ctor(v5, 0, Method_Project_title_DrawProcess__, 0);
  started = dds3StartProcess("titleDrawProc", 11015, 0, 0, v5, 0, workdata);
  workdata[1].klass = started;
  v7 = proc->workdata;
  if (!v7)
    goto LABEL_16;
  if (v7->klass->_2.naturalAligment < (u32)v8 || v7->klass->_2.typeHierarchy[v8 - 1] != tagTITLE_WORK)
  {
LABEL_18:
  }
LABEL_16:
  BYTE4(v7[2].klass) = 0;
  LODWORD(v7[2].klass) = 0;
}

// 0x2234b20
dds3ProcessFunc_t titleDrawProcess(dds3ProcessID_t *proc) {
  titleDraw(proc);
  return 0;
}

// 0x2232370
void titleReleaseDraw(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;

  workdata = proc->workdata;
  if (!workdata)
    goto LABEL_11;
  goto LABEL_9;
  if (!workdata)
LABEL_9:
LABEL_11:
  if ((BYTE1(workdata[2].klass) & 0x40) == 0)
    BYTE1(workdata[2].klass) |= 0x40u;
}

// 0x2234b90
dds3ProcessID_t *titleStart(void) {
  tagTITLE_WORK *v1;
  dds3ProcessID_t *v3;
  dds3ProcessFunc_t v4;
  shutdownfuncDelegate v5;
  dds3ProcessID_t *started;

  v1 = Allocate(tagTITLE_WORK);
  _ctor(v1);
  v3 = Allocate(dds3ProcessID_t);
  _ctor(v3, 0);
  v4 = Allocate(dds3ProcessFunc_t);
  _ctor(v4, 0, Method_Project_title_Process__, 0);
  v5 = Allocate(shutdownfuncDelegate);
  _ctor(v5, 0, Method_Project_title_Shutdown__, 0);
  started = dds3StartProcess("titleProc", 1024, 0, 0, v4, v5, v1);
  titleInitialize(started);
  return started;
}

// 0x2234d40
void titleFinish(dds3ProcessID_t *proc) {
  dds3ProcessID_t *v4;
  dds3ProcessID_t *id;

  id = proc;
  if (!dds3ExistProcess(id))
    return;
  v4 = id;
  titleRelease(id);
  dds3KillProcess(id, 1);
  return;
}

// 0x2234e40
void titleStartDebug(void) {
  dds3ProcessID_t *v2;

  v2 = titleStart();
  proc_debug = v2;
}

// 0x2234eb0
void titleFinishDebug(void) {
  if (proc_debug)
    titleFinish(proc_debug);
  proc_debug = 0;
}

// 0x2234fa0
bool CheckDebug(void) {
  if (!proc_debug)
    return 1;
  if (dds3ExistProcess(proc_debug))
    return 0;
  proc_debug = 0;
  return 1;
}

// 0x22328e0
void titleTestCreateWorld(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;
  Il2CppClass *klass;
  dds3Basic_t *v6;
  u32 v7;
  u32 v9;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  dds3Basic_t *v18;
  dds3Basic_t *p_byval_arg;
  dds3Basic_t *v20;
  dds3Basic_t *v21;
  sdfVector4_t v22;
  sdfVector4_t v23;
  sdfVector4_t v24;

  workdata = proc->workdata;
  klass = workdata[3].klass;
  v6 = Add(0, 0);
  klass->_1.namespaze = v6;
  dds3SetControlScene(&klass->_1.namespaze);
  dds3SetActiveScene(klass->_1.namespaze);
  v7 = dds3SerializeID();
  Add(v7, 0);
  *(_OWORD *)&klass->_1.byval_arg.bits = xmmword_3CFE080;
  *(_OWORD *)&klass->_1.this_arg.bits = xmmword_3CFD5C0;
  v9 = dds3SerializeID();
  v10 = *(f32 *)&klass->_1.byval_arg.bits;
  v11 = *((f32 *)&klass->_1.byval_arg.bits + 1);
  v12 = *(f32 *)&klass->_1.this_arg.data;
  v13 = *((f32 *)&klass->_1.this_arg.data + 1);
  v14 = *(f32 *)&klass->_1.this_arg.bits;
  v15 = *((f32 *)&klass->_1.this_arg.bits + 1);
  v16 = *(f32 *)&klass->_1.element_class;
  v17 = *((f32 *)&klass->_1.element_class + 1);
  v23.x = v10;
  v23.y = v11;
  v23.z = v12;
  v23.w = v13;
  v24.x = v14;
  v24.y = v15;
  *(u64 *)&v22.x = 0;
  v24.z = v16;
  v24.w = v17;
  v18 = dds3CameraObjectBasicAddTypeLookAt(v9, v23, v24, v22);
  klass->_1.byval_arg.data = v18;
  p_byval_arg = &klass->_1.byval_arg;
  dds3SetBasicName(p_byval_arg, "TitleTestCamera");
  dds3SetRadiusPoseSet(p_byval_arg, 10.0);
  v21 = *(p_byval_arg - 1);
  v20 = p_byval_arg;
  SetActiveCamera(v21, v20, 0);
}

// 0x2232540
void titleTestDeleteWorld(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;
  Il2CppClass *klass;
  dds3Basic_t *data;
  dds3Basic_t *p_namespaze;
  const char *namespaze;

  workdata = proc->workdata;
  klass = workdata[3].klass;
  data = klass->_1.byval_arg.data;
  if (data)
  {
    dds3CameraObjectBasicDelete(data);
  }
  namespaze = klass->_1.namespaze;
  p_namespaze = &klass->_1.namespaze;
  if (namespaze)
  {
    dds3DeleteScene(p_namespaze);
  }
}

// 0x2232b30
void titleTestCreateModel(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;
  s64 naturalAligment;
  Il2CppClass *klass;
  u32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  dds3Basic_t *v22;
  Il2CppObject *ModelHandle;
  Il2CppObject *v24;
  s64 v26;
  Il2CppClass ***p_implementedInterfaces;
  dds3ModelHandle_t *v28;
  u32 v29;
  dds3Basic_t *v30;
  Il2CppObject *v31;
  s64 v33;
  Il2CppRuntimeInterfaceOffsetPair **p_interfaceOffsets;
  dds3Basic_t *pObjectBasic;
  sdfVector4_t v36;
  sdfVector4_t v37;

  workdata = proc->workdata;
  __asm { FMOV            V1.4S, #1.0 }
  klass = workdata[3].klass;
  pObjectBasic = 0;
  HIDWORD(klass->_1.parent) = 0;
  *(_OWORD *)&klass->_1.interopData = xmmword_3CFD5C0;
  *(_OWORD *)&klass->_1.fields = _Q1;
  *(_OWORD *)&klass->_1.properties = xmmword_3CFD5C0;
  v13 = dds3SerializeID();
  v14 = *(f32 *)&klass->_1.properties;
  v15 = *((f32 *)&klass->_1.properties + 1);
  v16 = *(f32 *)&klass->_1.methods;
  v17 = *((f32 *)&klass->_1.methods + 1);
  v18 = *(f32 *)&klass->_1.interopData;
  v19 = *((f32 *)&klass->_1.interopData + 1);
  v20 = *(f32 *)&klass->_1.klass;
  v21 = *((f32 *)&klass->_1.klass + 1);
  v36.x = v14;
  v36.y = v15;
  v36.z = v16;
  v36.w = v17;
  v37.x = v18;
  v37.y = v19;
  v37.z = v20;
  v37.w = v21;
  v22 = dds3UnitObjectBasicAdd(v13, v36, v37);
  pObjectBasic = v22;
  klass->_1.typeMetadataHandle = v22;
  dds3ObjectBaseMakeUnit(v22, 1u, 16);
  ModelHandle = dds3ObjectBaseGetModelHandle(pObjectBasic);
  v24 = ModelHandle;
  if (ModelHandle)
  {
    if (ModelHandle->klass->_2.naturalAligment < (u32)v26 || ModelHandle->klass->_2.typeHierarchy[v26 - 1] != dds3ModelHandle_t || (klass->_1.implementedInterfaces = &ModelHandle->klass, p_implementedInterfaces = &klass->_1.implementedInterfaces, ModelHandle->klass->_2.naturalAligment < (u32)v26) || ModelHandle->klass->_2.typeHierarchy[v26 - 1] != dds3ModelHandle_t)
    {
LABEL_24:
    }
  }
  else
  {
    klass->_1.implementedInterfaces = 0;
    p_implementedInterfaces = &klass->_1.implementedInterfaces;
  }
  v28 = *p_implementedInterfaces;
  mdlLoopMotion(v28, 0, 0);
  dds3SetPosPoseSet(pObjectBasic, *(sdfVector4_t *)&klass->_1.properties);
  dds3SetRotPoseSet(pObjectBasic, *(sdfVector4_t *)&klass->_1.interopData);
  dds3SetSclPoseSet(pObjectBasic, *(sdfVector4_t *)&klass->_1.fields);
  v29 = dds3SerializeID();
  v30 = dds3UnitObjectBasicAdd(v29, *(sdfVector4_t *)&klass->_1.properties, *(sdfVector4_t *)&klass->_1.interopData);
  klass->_1.generic_class = v30;
  dds3ObjectBaseMakeUnit(klass->_1.generic_class, 1u, 16);
  v31 = dds3ObjectBaseGetModelHandle(&klass->_1.generic_class);
  v24 = v31;
  if (v31)
  {
    if (v31->klass->_2.naturalAligment < (u32)v33)
      goto LABEL_24;
    if (v31->klass->_2.typeHierarchy[v33 - 1] != dds3ModelHandle_t)
      goto LABEL_24;
    klass->_1.interfaceOffsets = (Il2CppRuntimeInterfaceOffsetPair *)v31;
    p_interfaceOffsets = &klass->_1.interfaceOffsets;
    if (v24->klass->_2.naturalAligment < (u32)v33 || v24->klass->_2.typeHierarchy[v33 - 1] != dds3ModelHandle_t)
    {
      goto LABEL_24;
    }
  }
  else
  {
    klass->_1.interfaceOffsets = 0;
    p_interfaceOffsets = &klass->_1.interfaceOffsets;
  }
  mdlLoopMotion(klass->_1.interfaceOffsets, 0, 0);
  dds3SetPosPoseSet(&klass->_1.generic_class, *(sdfVector4_t *)&klass->_1.properties);
  dds3SetRotPoseSet(&klass->_1.generic_class, *(sdfVector4_t *)&klass->_1.interopData);
  dds3SetSclPoseSet(&klass->_1.generic_class, *(sdfVector4_t *)&klass->_1.fields);
  LOWORD(klass->_1.nestedTypes) = 257;
}

// 0x22350c0
void titleTestUpdateModelShadow(dds3ProcessID_t *proc) {
  u64 *v3;
  s64 v4;
  u64 *v5;
  u64 *v6;
  s64 v7;
  Il2CppObject *workdata;
  Il2CppClass *klass;
  f32 *v12;
  f32 v13;
  f32 v14;
  f32 v15;
  u32 *v16;
  s64 v17;
  f32 *v18;
  u32 *v19;
  u32 *v20;
  s64 p_parent;
  Il2CppClass *interfaceType;
  Il2CppClass **v24;
  _OWORD *p_x;
  __int128 v26;
  __int128 v27;
  __int128 v28;
  struct sdfVector4_t v29;
  dds3ModelHandle_t *interfaceOffsets;
  __int128 v35;

  v35 = xmmword_3D057A0;
  v3 = sub_3BD9D0(float_, &v35);
  v4 = v3[2];
  v3[5] = 0;
  v3[4] = 0;
  v5 = v3 + 4;
  v6 = v3;
  v7 = *(u64 *)(v4 + 16);
  *(_OWORD *)((char *)v5 + 4 * v7) = 0u;
  *(_OWORD *)&v5[v7] = 0u;
  *(_OWORD *)((char *)v5 + 12 * v7) = 0u;
  workdata = proc->workdata;
  klass = workdata[3].klass;
  v12 = DirLights[0];
  v14 = v12[8];
  v13 = v12[9];
  v15 = v12[10];
  *((u32 *)v6 + 8) = 1065353216;
  v16 = v6 + 4;
  v17 = *(u64 *)(*((u64 *)v16 - 2) + 16);
  v18 = &v16[v17];
  v19 = &v16[2 * v17];
  v20 = &v16[3 * v17];
  *v18 = (f32)-v14 / v13;
  *v19 = 0;
  *v20 = 0;
  v16[1] = 0;
  v18[1] = 0.0;
  v19[1] = 0;
  v20[1] = 0;
  v16[2] = 0;
  v18[2] = (f32)-v15 / v13;
  v19[2] = 1065353216;
  v20[2] = 0;
  v16[3] = 0;
  v18[3] = 0.0;
  v19[3] = 0;
  v20[3] = 1065353216;
  p_parent = &klass->_1.interfaceOffsets[4].interfaceType->_1.parent;
  (loc_2245570)(p_parent, 0);
  interfaceType = klass->_1.interfaceOffsets[4].interfaceType;
  v24 = &interfaceType->_1.parent;
  p_x = &vf00.x;
  v26 = p_x[5];
  v27 = p_x[6];
  v28 = p_x[7];
  *(_OWORD *)v24 = p_x[4];
  *((_OWORD *)v24 + 1) = v26;
  *((_OWORD *)v24 + 2) = v27;
  *((_OWORD *)v24 + 3) = v28;
  v29 = *(sdfVector4_t *)&klass->_1.properties;
  vct_A = v29;
  interfaceOffsets = klass->_1.interfaceOffsets;
  mdlSetPosition(interfaceOffsets);
}

// 0x2233560
void titleTestUpdateModel(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;
  Il2CppClass *klass;
  dds3Basic_t *p_typeMetadataHandle;
  void **p_generic_class;
  dds3Basic_t *v8;
  dds3Basic_t *v10;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  sdfVector4_t v20;
  sdfVector4_t v21;

  workdata = proc->workdata;
  klass = workdata[3].klass;
  p_typeMetadataHandle = &klass->_1.typeMetadataHandle;
  p_generic_class = &klass->_1.generic_class;
  if (((s64)klass->_1.nestedTypes & 2) != 0)
  {
    dds3ObjectBaseOffFlag(p_typeMetadataHandle, 1u);
    if (*p_generic_class)
      dds3ObjectBaseOffFlag(&klass->_1.generic_class, 1u);
  }
  else
  {
    dds3ObjectBaseOnFlag(p_typeMetadataHandle, 1u);
    if (*p_generic_class)
      dds3ObjectBaseOnFlag(&klass->_1.generic_class, 1u);
  }
  v8 = &klass->_1.typeMetadataHandle;
  if (((s64)klass->_1.nestedTypes & 4) != 0)
  {
    dds3ObjectBaseOnFlag(v8, 0x400u);
    v10 = &klass->_1.typeMetadataHandle;
    v11 = *(f32 *)&klass->_1.properties;
    v12 = *((f32 *)&klass->_1.properties + 1);
    v13 = *(f32 *)&klass->_1.methods;
    v14 = *((f32 *)&klass->_1.methods + 1);
    goto LABEL_16;
  }
  else
  {
    dds3ObjectBaseOffFlag(v8, 0x400u);
    v10 = &klass->_1.typeMetadataHandle;
    v11 = *(f32 *)&klass->_1.properties;
    v12 = *((f32 *)&klass->_1.properties + 1);
    v13 = *(f32 *)&klass->_1.methods;
    v14 = *((f32 *)&klass->_1.methods + 1);
    goto LABEL_16;
  }
LABEL_16:
  v20.x = v11;
  v20.y = v12;
  v20.z = v13;
  v20.w = v14;
  dds3SetPosPoseSet(v10, v20);
  dds3SetRotPoseSet(v10, *(sdfVector4_t *)&klass->_1.interopData);
  dds3SetSclPoseSet(v10, *(sdfVector4_t *)&klass->_1.fields);
  if (klass->_1.generic_class)
  {
    v15 = *(f32 *)&klass->_1.properties;
    v16 = *((f32 *)&klass->_1.properties + 1);
    v17 = *(f32 *)&klass->_1.methods;
    v18 = *((f32 *)&klass->_1.methods + 1);
    v21.x = v15;
    v21.y = v16;
    v21.z = v17;
    v21.w = v18;
    dds3SetPosPoseSet(&klass->_1.generic_class, v21);
    dds3SetRotPoseSet(&klass->_1.generic_class, *(sdfVector4_t *)&klass->_1.interopData);
    dds3SetSclPoseSet(&klass->_1.generic_class, *(sdfVector4_t *)&klass->_1.fields);
    titleTestUpdateModelShadow(proc);
  }
}

// 0x22353f0
void titleTestInitEffectLineBall(dds3ProcessID_t *proc, const sdfVector4_t *pos) {
  Il2CppObject *workdata;
  void *static_fields;
  s64 v7;
  s64 v8;
  s64 v9;
  f32 v10;
  s64 v11;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;

  workdata = proc->workdata;
  static_fields = workdata[3].klass->static_fields;
  v7 = 4;
  *((u64 *)static_fields + 3) = 0;
  *((u64 *)static_fields + 4) = 0;
  do
  {
    v10 = (f32)(u32)sub_1905740(128, 0) + 1.0;
    v11 = *(u64 *)(*(u64 *)(*((u64 *)static_fields + 2) + 8 * v7) + 16);
    v12 = (f32)(v10 * 1.0) + *((f32 *)static_fields + 6);
    *(f32 *)(v11 + 32) = v12;
    v13 = (f32)(v10 * 0.0) + *((f32 *)static_fields + 8);
    *(f32 *)(v11 + 40) = v13;
    v14 = *((f32 *)static_fields + 7);
    *(u32 *)(v11 + 44) = 1065353216;
    if ((((u8)v7 - 4) & 1) != 0)
      v15 = v14;
    else
      v15 = v14 + 0.0;
    *(f32 *)(v11 + 36) = v15;
    *(f32 *)(v11 + 48) = v12;
    *(f32 *)(v11 + 52) = v15;
    *(f32 *)(v11 + 56) = v13;
    *(u32 *)(v11 + 60) = 1065353216;
    v8 = 8 * v7;
    v9 = *(u64 *)(*((u64 *)static_fields + 2) + 8 * v7);
    *(u32 *)(v9 + 28) = 0;
    ++v7;
    *(u32 *)(v9 + 32) = sub_1905740(30, 0) + 30;
    *(u32 *)(*(u64 *)(*((u64 *)static_fields + 2) + v8) + 24) = 1;
  }
  while (v7 != 1028);
  *((u32 *)static_fields + 10) = 1;
}

// 0x22355c0
void titleTestUpdateEffectLineBall(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;
  char *static_fields;
  s32 v7;
  s64 v8;
  s64 v9;
  struct sdfVector4_t v10;
  s64 v11;
  s32 v12;
  s32 v13;
  struct sdfVector4_t v14;
  sdfVector4_t *v15;
  s64 v16;
  s32 v17;
  s32 v18;
  struct sdfVector4_t v19;

  workdata = proc->workdata;
  static_fields = workdata[3].klass->static_fields;
  if ((static_fields[40] & 1) != 0)
  {
    v19 = *(sdfVector4_t *)(static_fields + 24);
    v7 = 0;
    v8 = -8192;
    vct_C = v19;
    v9 = *((u64 *)static_fields + 2);
    while ((*(u8 *)(*(u64 *)(v9 + v8 + 8224) + 24) & 1) == 0)
    {
      ++v7;
LABEL_11:
      v8 += 8;
      if (!v8)
      {
        if (v7 == 1024)
          *((u32 *)static_fields + 10) = 0;
        return;
      }
    }
    vct_A = vct_C;
    v10 = *(sdfVector4_t *)(*(u64 *)(*(u64 *)(*((u64 *)static_fields + 2) + v8 + 8224) + 16) + 32);
    vct_B = v10;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v11 = *(u64 *)(*((u64 *)static_fields + 2) + v8 + 8224);
    v13 = *(u32 *)(v11 + 28);
    v12 = *(u32 *)(v11 + 32);
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, 1.2 / (f32)(v12 - v13));
    v14 = *(sdfVector4_t *)(*(u64 *)(*(u64 *)(*((u64 *)static_fields + 2) + v8 + 8224) + 16) + 32);
    vct_B = v14;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v15 = *(sdfVector4_t *)(*(u64 *)(*((u64 *)static_fields + 2) + v8 + 8224) + 16);
    v15[2] = vct_A;
    v9 = *((u64 *)static_fields + 2);
    v16 = *(u64 *)(v9 + v8 + 8224);
    v17 = *(u32 *)(v16 + 32);
    v18 = *(u32 *)(v16 + 28) + 1;
    *(u32 *)(v16 + 28) = v18;
    if (v18 == v17)
      *(u64 *)(v16 + 24) = 0;
    goto LABEL_11;
  }
}

// 0x2235a10
void titleTestDrawEffectLineBall(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;

  workdata = proc->workdata;
}

// 0x2235a90
void titleTestInitEffectParticle(dds3ProcessID_t *proc, const sdfVector4_t *pos, const sdfVector4_t *vec) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v8;
  f32 v9;
  f32 v11;
  f32 v12;
  Il2CppObject *workdata;
  Il2CppRGCTXData *rgctx_data;
  f32 *p_x;
  f32 *v18;
  f32 *v19;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 v25;
  f32 v26;
  sdfVector4_t *v27;
  f32 v28;
  f32 v29;
  s32 v30;
  f32 v31;
  sdfVector4_t *v32;
  f32 v33;
  s64 v34;
  Il2CppRGCTXData v35;
  s64 v36;
  s64 v37;
  struct sdfVector4_t v38;
  sdfVector4_t *v39;
  f32 v40;
  s64 v41;
  f32 v42;
  u32 v44;
  sdfVector4_t *v47;
  struct sdfVector4_t v51;

  w = vec->w;
  z = vec->z;
  y = vec->y;
  x = vec->x;
  v8 = pos->w;
  v9 = pos->z;
  v11 = pos->y;
  v12 = pos->x;
  workdata = proc->workdata;
  rgctx_data = workdata[3].klass->rgctx_data;
  p_x = &vf00.x;
  p_x[8] = v12;
  p_x[9] = v11;
  p_x[10] = v9;
  p_x[11] = v8;
  v18 = &vf00.x;
  v18[4] = x;
  v18[5] = y;
  v18[6] = z;
  v18[7] = w;
  v19 = &vf00.x;
  v20 = v19[6];
  v21 = v19[4];
  v22 = v19[5];
  sub_1949110(0);
  v25 = v21 * v21;
  v26 = v22 * v22;
  v27 = &rgctx_data[3];
  v28 = v25 + v26;
  v29 = v20 * v20;
  v30 = (u8)byte_5755EF6;
  *v27 = vct_B;
  if (!v30)
  {
    v31 = v28 + v29;
    v32 = &rgctx_data[5];
    goto LABEL_21;
  }
  v31 = v28 + v29;
  v32 = &rgctx_data[5];
LABEL_21:
  v33 = sqrtf(v31);
  v34 = -8192;
  v35.rgctxDataDummy = rgctx_data[2].rgctxDataDummy;
  *v32 = vct_A;
  do
  {
    v38 = *v27;
    v39 = *(sdfVector4_t *)((char *)v35.rgctxDataDummy + v34 + 8224);
    v51 = *v27;
    v38 = v51;
    v39[1] = v38;
    *(_OWORD *)(*(u64 *)((char *)rgctx_data[2].rgctxDataDummy + v34 + 8224) + 32) = *(_OWORD *)&rgctx_data[5].rgctxDataDummy;
    v40 = (f32)((f32)(u32)sub_1905740(64, 0) + 1.0) + 64.0;
    sub_1905740(360, 0);
    v41 = *(u64 *)((char *)rgctx_data[2].rgctxDataDummy + v34 + 8224);
    v42 = *(f32 *)(v41 + 24);
    *(f32 *)(v41 + 16) = *(f32 *)(v41 + 16) + (f32)(v40 * 1.0);
    *(f32 *)(v41 + 24) = (f32)(v40 * 0.0) + v42;
    vct_A = (struct sdfVector4_t)xmmword_3CFFF90;
    sub_1949110(0);
    v44 = sub_1905740(100, 0);
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, (f32)v44 / 100.0);
    vct_B = vct_A;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    sub_1949110(0);
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v33 * (f32)((f32)(64.0 - (f32)(v40 + -64.0)) * 0.015625));
    v47 = *(sdfVector4_t *)((char *)rgctx_data[2].rgctxDataDummy + v34 + 8224);
    v47[2] = vct_A;
    v36 = *(u64 *)((char *)rgctx_data[2].rgctxDataDummy + v34 + 8224);
    *(u32 *)(v36 + 52) = 0;
    *(u32 *)(v36 + 56) = sub_1905740(60, 0) + 60;
    v35.rgctxDataDummy = rgctx_data[2].rgctxDataDummy;
    v37 = (s64)v35.rgctxDataDummy + v34;
    v34 += 8;
    *(u32 *)(*(u64 *)(v37 + 8224) + 48) = 1;
  }
  while (v34);
  LODWORD(rgctx_data[7].rgctxDataDummy) = 1;
}

// 0x2236200
void titleTestUpdateEffectParticle(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;
  Il2CppRGCTXData *rgctx_data;
  s64 v6;
  s64 v7;
  f32 v9;
  f32 v10;
  struct sdfVector4_t v13;
  sdfVector4_t *v14;
  sdfVector4_t *v15;
  s64 v16;
  s32 v17;
  s32 v18;

  workdata = proc->workdata;
  rgctx_data = workdata[3].klass->rgctx_data;
  if (((s64)rgctx_data[7].rgctxDataDummy & 1) != 0)
  {
    v6 = *((u64 *)rgctx_data[2].rgctxDataDummy + 1028);
    v7 = *(u64 *)(v6 + 40);
    v9 = *(f32 *)(v6 + 32);
    v10 = *(f32 *)(v6 + 36) + (f32)((f32)*(s32 *)(v6 + 52) * 0.02);
    *(f32 *)(v6 + 36) = v10;
    vct_A.x = v9;
    vct_A.y = v10;
    *(u64 *)&vct_A.z = v7;
    v13 = *(sdfVector4_t *)(*((u64 *)rgctx_data[2].rgctxDataDummy + 1028) + 16);
    vct_B = v13;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v14 = *((sdfVector4_t *)rgctx_data[2].rgctxDataDummy + 1028);
    v15 = v14 + 1;
    *v15 = vct_A;
    v16 = *((u64 *)rgctx_data[2].rgctxDataDummy + 1028);
    v17 = *(u32 *)(v16 + 56);
    v18 = *(u32 *)(v16 + 52) + 1;
    *(u32 *)(v16 + 52) = v18;
    if (v18 > v17)
      *(u64 *)(v16 + 48) = 0;
    if (*(f32 *)(v16 + 20) > *((f32 *)&rgctx_data[3].klass + 1))
      *(u64 *)(v16 + 48) = 0;
    return;
  }
}

// 0x22364b0
void titleTestPoint3To2(f32 x3, f32 y3, f32 z3, f32 x2, f32 y2) {
  _OWORD *p_x;
  __int128 v12;
  __int128 v13;
  __int128 v14;
  sdfMatrix4_t v19;
  sdfMatrix4_t v20;
  sdfVector4_t v21;

  p_x = &vf00.x;
  v12 = p_x[5];
  v13 = p_x[6];
  v14 = p_x[7];
  p_x[8] = p_x[4];
  p_x[9] = v12;
  p_x[10] = v13;
  p_x[11] = v14;
  vct_A.x = x3;
  vct_A.y = y3;
  vct_A.z = z3;
  vct_A.w = 1.0;
  vct_A.w = 1.0;
  get_transpose(&v20, &mtx_A, 0);
  v19 = v20;
  v21 = op_Multiply_60923920(&v19, vct_A, 0);
  vct_A.x = v21.x * (f32)(1.0 / v21.w);
  vct_A.y = v21.y * (f32)(1.0 / v21.w);
  vct_A.z = v21.z * (f32)(1.0 / v21.w);
  vct_A.w = 1.0 / v21.w;
  vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  return;
}

// 0x2236770
void titleTestDrawEffectParticle(dds3ProcessID_t *proc) {
  f32 v2;
  f32 v3;
  Il2CppObject *workdata;
  Il2CppRGCTXData *rgctx_data;
  s64 i;
  s64 v9;
  f32 v11;
  f32 v12;
  f32 v13;

  workdata = proc->workdata;
  rgctx_data = workdata[3].klass->rgctx_data;
  if (((s64)rgctx_data[7].rgctxDataDummy & 1) != 0)
  {
    for (i = 4; i != 1028; ++i)
    {
      v9 = *((u64 *)rgctx_data[2].rgctxDataDummy + i);
      if ((*(u8 *)(v9 + 48) & 1) != 0)
      {
        v11 = *(f32 *)(v9 + 16);
        v12 = *(f32 *)(v9 + 20);
        v13 = *(f32 *)(v9 + 24);
        titleTestPoint3To2(v11, v12, v13, v2, v3);
      }
    }
  }
}

// 0x2236880
void titleTestDrawStageLine(void) {
  ;
}

// 0x2236890
void titleTestDrawStage(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;

  workdata = proc->workdata;
}

// 0x22337c0
void titleTestDraw(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;
  s64 naturalAligment;
  Il2CppClass *klass;
  s64 v6;
  f32 v8;
  struct sdfVector4_t v9;
  s64 v12;
  struct sdfVector4_t v14;

  workdata = proc->workdata;
  if (workdata)
  {
    if (workdata->klass->_2.naturalAligment < (u32)naturalAligment || workdata->klass->_2.typeHierarchy[naturalAligment - 1] != tagTITLE_WORK)
    {
LABEL_43:
    }
  }
  klass = workdata[3].klass;
  workdata = proc->workdata;
  if (workdata)
  {
    if (workdata->klass->_2.naturalAligment < (u32)v6 || workdata->klass->_2.typeHierarchy[v6 - 1] != tagTITLE_WORK)
    {
      goto LABEL_43;
    }
  }
  v14 = *(sdfVector4_t *)&klass->_1.castClass;
  vct_A = v14;
  v8 = *(f32 *)&klass->_1.parent;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v8);
  v9 = *(sdfVector4_t *)&klass->_1.properties;
  vct_B = v9;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  titleTestUpdateEffectLineBall(proc);
  workdata = proc->workdata;
  if (workdata)
  {
    if (workdata->klass->_2.naturalAligment < (u32)v12 || workdata->klass->_2.typeHierarchy[v12 - 1] != tagTITLE_WORK)
    {
      goto LABEL_43;
    }
  }
  titleTestUpdateEffectParticle(proc);
  titleTestDrawEffectParticle(proc);
}

// 0x2236910
bool titleTestGetPadAnalog(const sdfVector4_t *pPad, f32 pLength, f32 min) {
  u32 AnalogLX;
  f32 AnalogLY;
  f32 v7;
  f32 v8;
  f32 v10;
  f32 v11;
  f32 *p_x;
  f32 z;
  f32 x;
  f32 y;
  f32 v18;
  f32 v19;

  AnalogLX = dds3PadGetAnalogLX(1);
  AnalogLY = dds3PadGetAnalogLY(1);
  v7 = AnalogLX;
  v8 = AnalogLY + -128.0;
  v10 = v7 + -128.0;
  v11 = -v8;
  vct_A.x = v10;
  vct_A.y = 0.0;
  vct_A.z = v11;
  vct_A.w = 0.0;
  p_x = &vf00.x;
  z = p_x[6];
  x = p_x[4];
  y = p_x[5];
  v18 = (f32)((f32)(x * x) + (f32)(y * y)) + (f32)(z * z);
  sub_1949110(0);
  v19 = sqrtf(v18);
  if (v19 < min)
  {
    CHECK_PRESS2(4100);
    CHECK_PRESS2(4101);
    CHECK_PRESS2(4103);
    CHECK_PRESS2(4102);
    return v19 >= min;
  }
  return v19 >= min;
}

// 0x2232ef0
s32 titleTestPad(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;
  Il2CppClass *klass;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 v14;
  bool v15;
  f32 v16;
  dds3Basic_t *data;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 v27;
  f32 v28;
  f32 v29;
  f32 v30;
  f32 v31;
  s32 v32;
  sdfVector4_t *p_interopData;
  f32 v36;
  f32 v37;
  sdfVector4_t *p_properties;
  struct sdfVector4_t v39;
  struct sdfVector4_t v40;
  struct sdfVector4_t v42;
  struct sdfVector4_t v43;
  sdfVector4_t v46;
  sdfVector4_t v47;
  sdfVector4_t v48;
  sdfVector4_t v49;
  sdfVector4_t v50;
  sdfVector4_t v51;
  sdfVector4_t v52;

  workdata = proc->workdata;
  klass = workdata[3].klass;
  if (!CHECK_TRIG(4099, 1))
  {
    if (!CHECK_TRIG(4098, 1))
      goto LABEL_10;
LABEL_15:
    v10 = *(f32 *)&klass->_1.properties;
    v11 = *((f32 *)&klass->_1.properties + 1);
    v13 = *(f32 *)&klass->_1.methods;
    v12 = *((f32 *)&klass->_1.methods + 1);
    v51.y = -6.0;
    v51.x = 0.0;
    v51.z = 0.0;
    v51.w = 0.0;
    v47.x = v10;
    v47.y = v11;
    v47.z = v13;
    v47.w = v12;
    titleTestInitEffectParticle(proc, v47, v51);
    if (CHECK_TRIG(4096, 1))
      goto LABEL_11;
LABEL_18:
    if (CHECK_PRESS2(4107) || CHECK_PRESS2(4108))
    {
      if (CHECK_PRESS2(4107))
        *((f32 *)&klass->_1.byval_arg.bits + 1) = *((f32 *)&klass->_1.byval_arg.bits + 1) + -16.0;
      v15 = CHECK_PRESS2(4108);
      v16 = *((f32 *)&klass->_1.byval_arg.bits + 1);
      if (v15)
      {
        v16 = v16 + 16.0;
        *((f32 *)&klass->_1.byval_arg.bits + 1) = v16;
      }
      data = klass->_1.byval_arg.data;
      v18 = *(f32 *)&klass->_1.byval_arg.bits;
      v19 = *(f32 *)&klass->_1.this_arg.bits;
      v20 = *((f32 *)&klass->_1.this_arg.bits + 1);
      v21 = *(f32 *)&klass->_1.element_class;
      v22 = *((f32 *)&klass->_1.element_class + 1);
      v24 = *(f32 *)&klass->_1.this_arg.data;
      v23 = *((f32 *)&klass->_1.this_arg.data + 1);
      v49.x = v19;
      v49.y = v20;
      v49.z = v21;
      v49.w = v22;
      v52.x = v18;
      v52.y = v16;
      v52.z = v24;
      v52.w = v23;
      dds3CameraObjectBasicSetTgtCam(data, v49, v52);
      if (!titleTestGetPadAnalog(v50, v27, 48.0))
        goto LABEL_69;
      goto LABEL_31;
    }
    else
    {
    }
    if (!titleTestGetPadAnalog(v48, v14, 48.0))
      goto LABEL_69;
LABEL_31:
    v28 = *((f32 *)&klass->_1.parent + 1);
    if (v28 > 180.0)
      v28 = v28 + -360.0;
    if (v28 < -180.0)
      v28 = v28 + 360.0;
    v29 = (f32)(0.0 - v28) + -360.0;
    if ((f32)(0.0 - v28) <= 180.0)
      v29 = 0.0 - v28;
    v30 = v29 + 360.0;
    if (v29 >= -180.0)
      v30 = v29;
    v31 = -16.0;
    if (v30 >= -16.0 && (v31 = 16.0, v30 <= 16.0))
    {
      v31 = v30;
      v32 = 1;
    }
    else
    {
      v32 = 0;
    }
    p_interopData = &klass->_1.interopData;
    v42 = *(sdfVector4_t *)&klass->_1.interopData;
    *((f32 *)&klass->_1.parent + 1) = v28 + v31;
    vct_A = v42;
    *p_interopData = vct_A;
    if (v32)
    {
      v43 = *(sdfVector4_t *)&klass->_1.castClass;
      vct_A = v43;
      v36 = *(f32 *)&klass->_1.parent;
      v37 = v36 / 48.0;
      v37 = v36 / 48.0;
      vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v37);
      v39 = *(sdfVector4_t *)&klass->_1.properties;
      p_properties = &klass->_1.properties;
      v40 = v39;
      vct_B = v40;
      vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      *p_properties = vct_A;
      goto LABEL_71;
    }
LABEL_69:
LABEL_71:
    ++TestPad_count;
    return 0;
  }
  titleTestInitEffectLineBall(proc, v46);
  if (CHECK_TRIG(4098, 1))
    goto LABEL_15;
LABEL_10:
  if (!CHECK_TRIG(4096, 1))
    goto LABEL_18;
LABEL_11:
  TestPad_count = 0;
  return 1;
}
