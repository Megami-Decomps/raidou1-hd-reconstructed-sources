#include "types.h"
#include "EVT_PICTURE_TYPE.h"
#include "dds3kernelcore.h"
#include "evtcutin.h"
#include "evtpicture.h"
#include "evttmxpreload.h"
#include "kernel.h"
#include "scr.h"

#define UID_MAX 16

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct evtCutInData_t evtCutInData_t;

struct evtCutInData_t {
    u32 cutin_uid[16];
    dds3ProcessID_t *cutin_pid[16];
};

void *pFile;
static evtCutInData_t *Data;

static s32 GetIndexFromUID(evtCutInData_t *pData, u32 UID);
static void AddUID(u32 UID, dds3ProcessID_t *PID);
static void DelUID(u32 UID);
static s32 GetRegistNums(void);
static void DelProcessAll(void);
static void Callback(u32 UID);
static dds3ProcessFunc_t DestructProcess(dds3ProcessID_t *PID);
static void DestructDestroy(dds3ProcessID_t *PID);

// 0x19dffd0
void evtFirstInit(void) {
  void *Asset;
  s64 naturalAligment;
  void *v5;
  s64 v7;
  void *v8;
  void *v10;
  s64 v11;
  void *v12;
  void *v13;
  s64 v15;

  Asset = LoadAsset(_Ctrl_k__BackingField, "fld_common", "evtEventCutInFile", 0);
  if (!Asset)
  {
    pFile = 0;
    goto LABEL_28;
  }
  if (Asset->klass->_2.naturalAligment >= (u32)naturalAligment)
  {
    if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_evtCutInFile)
      v5 = Asset;
    else
      v5 = 0;
  }
  else
  {
    v5 = 0;
  }
  pFile = v5;
  if (Asset->klass->_2.naturalAligment < (u32)v7)
  {
    goto LABEL_28;
  }
  if (Asset->klass->_2.typeHierarchy[v7 - 1] == Project_evtCutInFile)
    v8 = Asset;
  else
    v8 = 0;
LABEL_28:
  v10 = LoadAsset(_Ctrl_k__BackingField, "fld_common", "evtEventCutInBgTbl", 0);
  if (!v10)
  {
    v13 = 0;
    pBgTbl = 0;
LABEL_34:
    return;
  }
  if (v10->klass->_2.naturalAligment >= (u32)v11)
  {
    if (v10->klass->_2.typeHierarchy[v11 - 1] == evtCutInBgTbl)
      v12 = v10;
    else
      v12 = 0;
  }
  else
  {
    v12 = 0;
  }
  pBgTbl = v12;
  if (v10->klass->_2.naturalAligment >= (u32)v15)
  {
    if (v10->klass->_2.typeHierarchy[v15 - 1] == evtCutInBgTbl)
      v13 = v10;
    else
      v13 = 0;
    goto LABEL_34;
  }
}

// 0x19e0310
static s32 GetIndexFromUID(evtCutInData_t *pData, u32 UID) {
  u32 *cutin_uid;

  if (!UID)
    return -1;
  cutin_uid = pData->cutin_uid;
  if (cutin_uid[0] == UID)
    return 0;
  if (cutin_uid[1] == UID)
    return 1;
  if (cutin_uid[2] == UID)
    return 2;
  if (cutin_uid[3] == UID)
    return 3;
  if (cutin_uid[4] == UID)
    return 4;
  if (cutin_uid[5] == UID)
    return 5;
  if (cutin_uid[6] == UID)
    return 6;
  if (cutin_uid[7] == UID)
    return 7;
  if (cutin_uid[8] == UID)
    return 8;
  if (cutin_uid[9] == UID)
    return 9;
  if (cutin_uid[10] == UID)
    return 10;
  if (cutin_uid[11] == UID)
    return 11;
  if (cutin_uid[12] == UID)
    return 12;
  if (cutin_uid[13] == UID)
    return 13;
  if (cutin_uid[14] == UID)
    return 14;
  if (cutin_uid[15] == UID)
    return 15;
  return -1;
}

// 0x19e0460
static void AddUID(u32 UID, dds3ProcessID_t *PID) {
  s64 v6;
  dds3ProcessID_t *cutin_pid;
  u32 *cutin_uid;
  Il2CppClass **v27;

  if (!UID)
    return;
  cutin_uid = Data->cutin_uid;
  if (!cutin_uid[0])
  {
    v6 = 0;
    goto LABEL_116;
  }
  if (cutin_uid[1])
  {
    cutin_uid = Data->cutin_uid;
    if (cutin_uid[2])
    {
      cutin_uid = Data->cutin_uid;
      if (cutin_uid[3])
      {
        cutin_uid = Data->cutin_uid;
        if (cutin_uid[4])
        {
          cutin_uid = Data->cutin_uid;
          if (cutin_uid[5])
          {
            cutin_uid = Data->cutin_uid;
            if (cutin_uid[6])
            {
              cutin_uid = Data->cutin_uid;
              if (cutin_uid[7])
              {
                cutin_uid = Data->cutin_uid;
                if (cutin_uid[8])
                {
                  cutin_uid = Data->cutin_uid;
                  if (cutin_uid[9])
                  {
                    cutin_uid = Data->cutin_uid;
                    if (cutin_uid[10])
                    {
                      cutin_uid = Data->cutin_uid;
                      if (cutin_uid[11])
                      {
                        cutin_uid = Data->cutin_uid;
                        if (cutin_uid[12])
                        {
                          cutin_uid = Data->cutin_uid;
                          if (cutin_uid[13])
                          {
                            cutin_uid = Data->cutin_uid;
                            if (cutin_uid[14])
                            {
                              cutin_uid = Data->cutin_uid;
                              if (cutin_uid[15])
                                return;
                              v6 = 15;
                            }
                            else
                            {
                              v6 = 14;
                            }
                          }
                          else
                          {
                            v6 = 13;
                          }
                        }
                        else
                        {
                          v6 = 12;
                        }
                      }
                      else
                      {
                        v6 = 11;
                      }
                    }
                    else
                    {
                      v6 = 10;
                    }
                  }
                  else
                  {
                    v6 = 9;
                  }
                }
                else
                {
                  v6 = 8;
                }
              }
              else
              {
                v6 = 7;
              }
            }
            else
            {
              v6 = 6;
            }
          }
          else
          {
            v6 = 5;
          }
        }
        else
        {
          v6 = 4;
        }
      }
      else
      {
        v6 = 3;
      }
    }
    else
    {
      v6 = 2;
    }
LABEL_116:
    cutin_pid = Data->cutin_pid;
    Data->cutin_uid[v6] = UID;
    if (!PID)
    {
LABEL_119:
      v27 = &cutin_pid->obj.klass + v6;
      v27[4] = PID;
      return;
    }
    goto LABEL_119;
  }
  v6 = 1;
  goto LABEL_116;
}

// 0x19e0a90
static void DelUID(u32 UID) {
  u32 *cutin_uid;
  s64 v6;
  dds3ProcessID_t *cutin_pid;
  Il2CppClass **v8;

  if (!UID)
    return;
  cutin_uid = Data->cutin_uid;
  if (cutin_uid[0] == UID)
  {
    v6 = 0;
  }
  else if (cutin_uid[1] == UID)
  {
    v6 = 1;
  }
  else if (cutin_uid[2] == UID)
  {
    v6 = 2;
  }
  else if (cutin_uid[3] == UID)
  {
    v6 = 3;
  }
  else if (cutin_uid[4] == UID)
  {
    v6 = 4;
  }
  else if (cutin_uid[5] == UID)
  {
    v6 = 5;
  }
  else if (cutin_uid[6] == UID)
  {
    v6 = 6;
  }
  else if (cutin_uid[7] == UID)
  {
    v6 = 7;
  }
  else if (cutin_uid[8] == UID)
  {
    v6 = 8;
  }
  else if (cutin_uid[9] == UID)
  {
    v6 = 9;
  }
  else if (cutin_uid[10] == UID)
  {
    v6 = 10;
  }
  else if (cutin_uid[11] == UID)
  {
    v6 = 11;
  }
  else if (cutin_uid[12] == UID)
  {
    v6 = 12;
  }
  else if (cutin_uid[13] == UID)
  {
    v6 = 13;
  }
  else if (cutin_uid[14] == UID)
  {
    v6 = 14;
  }
  else
  {
    if (cutin_uid[15] != UID)
      return;
    v6 = 15;
  }
  cutin_uid = Data->cutin_uid;
  cutin_pid = Data->cutin_pid;
  cutin_uid[v6] = 0;
  v8 = &cutin_pid->obj.klass + v6;
  v8[4] = 0;
}

// 0x19e0ca0
static s32 GetRegistNums(void) {
  int32x4_t *cutin_uid;
  int32x4_t v2;
  char v3;
  u32 v4;
  u32 v5;
  s32 v6;
  s32 v7;

  cutin_uid = Data->cutin_uid;
  v2 = vbicq_s8((int8x16_t)xmmword_3CFFD40, vceqzq_s32(cutin_uid[4]));
  v3 = vaddvq_s32(v2);
  v2.n128_u32[0] = (u8)vaddvq_s16(vbicq_s8((int8x16_t)xmmword_3D045F0, vuzp1q_s16(vceqzq_s32(cutin_uid[2]), vceqzq_s32(cutin_uid[3]))));
  v2.n128_u64[0] = vcnt_s8((int8x8_t)v2.n128_u64[0]).n64_u64[0];
  v2.n128_u16[0] = vaddlv_u8((uint8x8_t)v2.n128_u64[0]);
  v4 = v2.n128_u32[0];
  v2.n128_u32[0] = v3 & 0xF;
  v2.n128_u64[0] = vcnt_s8((int8x8_t)v2.n128_u64[0]).n64_u64[0];
  v2.n128_u16[0] = vaddlv_u8((uint8x8_t)v2.n128_u64[0]);
  v5 = v4 + v2.n128_u32[0];
  if (cutin_uid[5].n128_u32[0])
    ++v5;
  if (cutin_uid[5].n128_u32[1])
    v6 = (cutin_uid[5].n128_u32[2] != 0) + 1;
  else
    v6 = cutin_uid[5].n128_u32[2] != 0;
  v7 = v5 + v6;
  if (cutin_uid[5].n128_u32[3])
    return v7 + 1;
  else
    return v7;
}

// 0x19e10c0
bool evtChkUID(u32 UID) {
  u32 *cutin_uid;

  if (!UID)
    return 0;
  cutin_uid = Data->cutin_uid;
  if (cutin_uid[0] == UID)
    return 1;
  if (cutin_uid[1] == UID)
    return 1;
  if (cutin_uid[2] == UID)
    return 1;
  if (cutin_uid[3] == UID)
    return 1;
  if (cutin_uid[4] == UID)
    return 1;
  if (cutin_uid[5] == UID)
    return 1;
  if (cutin_uid[6] == UID)
    return 1;
  if (cutin_uid[7] == UID)
    return 1;
  if (cutin_uid[8] == UID)
    return 1;
  if (cutin_uid[9] == UID)
    return 1;
  if (cutin_uid[10] == UID)
    return 1;
  if (cutin_uid[11] == UID)
    return 1;
  if (cutin_uid[12] == UID)
    return 1;
  if (cutin_uid[13] == UID)
    return 1;
  return cutin_uid[14] == UID || cutin_uid[15] == UID;
}

// 0x19e1340
dds3ProcessID_t *evtGetPIDfromUID(u32 UID) {
  u32 *cutin_uid;
  s64 v6;

  if (!UID)
    return 0;
  cutin_uid = Data->cutin_uid;
  if (cutin_uid[0] != UID)
  {
    if (cutin_uid[1] == UID)
    {
      v6 = 1;
      goto LABEL_39;
    }
    if (cutin_uid[2] == UID)
    {
      v6 = 2;
      goto LABEL_39;
    }
    if (cutin_uid[3] == UID)
    {
      v6 = 3;
      goto LABEL_39;
    }
    if (cutin_uid[4] == UID)
    {
      v6 = 4;
      goto LABEL_39;
    }
    if (cutin_uid[5] == UID)
    {
      v6 = 5;
      goto LABEL_39;
    }
    if (cutin_uid[6] == UID)
    {
      v6 = 6;
      goto LABEL_39;
    }
    if (cutin_uid[7] == UID)
    {
      v6 = 7;
      goto LABEL_39;
    }
    if (cutin_uid[8] == UID)
    {
      v6 = 8;
      goto LABEL_39;
    }
    if (cutin_uid[9] == UID)
    {
      v6 = 9;
      goto LABEL_39;
    }
    if (cutin_uid[10] == UID)
    {
      v6 = 10;
      goto LABEL_39;
    }
    if (cutin_uid[11] == UID)
    {
      v6 = 11;
      goto LABEL_39;
    }
    if (cutin_uid[12] == UID)
    {
      v6 = 12;
      goto LABEL_39;
    }
    if (cutin_uid[13] == UID)
    {
      v6 = 13;
      goto LABEL_39;
    }
    if (cutin_uid[14] == UID)
    {
      v6 = 14;
      goto LABEL_39;
    }
    if (cutin_uid[15] == UID)
    {
      v6 = 15;
      goto LABEL_39;
    }
    return 0;
  }
  v6 = 0;
LABEL_39:
  return Data->cutin_pid[v6];
}

// 0x19e1540
void evtDelProcess(u32 UID) {
  dds3ProcessID_t *PIDfromUID;

  if (!evtChkUID(UID))
    return;
  PIDfromUID = evtGetPIDfromUID(UID);
  if (!PIDfromUID)
    return;
  evtPictureSetEndProcess(PIDfromUID);
  DelUID(UID);
}

// 0x19e1630
static void DelProcessAll(void) {
  s64 i;
  u32 v5;

  for (i = 0; i != 16; ++i)
  {
    v5 = Data->cutin_uid[i];
    if (!v5)
      continue;
    evtPictureSetEndProcess(Data->cutin_pid[i]);
    DelUID(v5);
  }
}

// 0x19e1710
static void Callback(u32 UID) {
  u32 v4;

  v4 = UID;
  DelUID(v4);
}

// 0x19e1790
static dds3ProcessFunc_t DestructProcess(dds3ProcessID_t *PID) {
  return 0;
}

// 0x19e17a0
static void DestructDestroy(dds3ProcessID_t *PID) {
  DelProcessAll();
}

// 0x19e1810
dds3ProcessID_t *evtStart(s32 *pNowFrame, dds3ProcessID_t *ParentPID, s32 X, s32 Y, DDS3_PRIORITY Pri, s32 Start, s32 End, EVT_PICTURE_TYPE Type, u32 UID) {
  s32 v18;
  char *monitor;
  s32 ui_mode;
  Il2CppObject *Item;
  s32 cutInType;
  dds3ProcessFunc_t v24;
  shutdownfuncDelegate v25;
  s32 v26;
  callbackDelegate v27;
  u8 *v28;
  callbackDelegate callback;
  intptr_t v30;
  s32 v31;
  s64 (__fastcall *method_ptr)();
  dds3ProcessID_t *started;
  void *v34;
  char *texpath;
  s32 v36;
  s32 *v37;
  s32 v38;
  s32 v39;
  dds3ProcessID_t *target;
  dds3ProcessID_t *parent;

  parent = ParentPID;
  target = 0;
  if (!UID)
    return 0;
  if (UID == 88)
  {
    scrEventSkipEnd(0, 0);
  }
  v37 = pNowFrame;
  v38 = Pri;
  v39 = Start;
  v36 = End;
  v18 = X;
  texpath = _get_Item(pFile->Tbl, UID)[1].klass;
  monitor = _get_Item(pFile->Tbl, UID)[1].monitor;
  ui_mode = _get_Item(pFile->Tbl, UID)[2].klass;
  Item = _get_Item(pFile->Tbl, UID);
  cutInType = HIDWORD(Item[2].klass);
  if (!GetRegistNums())
  {
    if (!dds3SearchProcessName("CutInDestructor"))
    {
      v24 = Allocate(dds3ProcessFunc_t);
      _ctor(v24, 0, Method_Project_evtCutIn_DestructProcess__, 0);
      v25 = Allocate(shutdownfuncDelegate);
      _ctor(v25, 0, Method_Project_evtCutIn_DestructDestroy__, 0);
      target = dds3StartProcess("CutInDestructor", 0, 0, 0, v24, v25, 0);
      dds3LinkProcess(parent, target);
    }
  }
  v26 = Y;
  v27 = Allocate(callbackDelegate);
  v28 = Method_Project_evtCutIn_Callback__;
  callback = v27;
  v30 = *((u64 *)Method_Project_evtCutIn_Callback__ + 1);
  v27->method = Method_Project_evtCutIn_Callback__;
  v27->method_ptr = v30;
  v27->m_target = 0;
  v31 = v28[82];
  callback->method_code = callback;
  if (!sub_3BDA00())
  {
    v34 = sub_3BDC90(0, "Delegate to an instance method cannot have null 'this'.");
  }
  if (v31 == 1)
  {
    method_ptr = sub_7AB0;
  }
  else
  {
    method_ptr = callback->method_ptr;
    callback->method_code = callback->m_target;
  }
  callback->invoke_impl = method_ptr;
  callback->extra_arg = sub_7A50;
  started = evtPictureStartProcess4(v18, v26, v38, v39, v36, v37, Type, UID, callback, texpath, monitor, ui_mode, cutInType);
  target = started;
  (loc_19E7EF0)(UID, started, 0);
  return target;
}

// 0x19e1cc0
dds3ProcessID_t *evtStartNakamaCutInBG(s32 x, s32 y) {
  Il2CppClass *texpath;
  char *monitor;
  s32 ui_mode;
  s32 cutInType;
  callbackDelegate v10;
  u8 *v11;
  callbackDelegate callback;
  intptr_t v13;
  s32 v14;
  s64 (__fastcall *method_ptr)();
  dds3ProcessID_t *started;
  void *v18;

  texpath = _get_Item(pFile->Tbl, 123)[1].klass;
  monitor = _get_Item(pFile->Tbl, 123)[1].monitor;
  ui_mode = _get_Item(pFile->Tbl, 123)[2].klass;
  cutInType = HIDWORD(_get_Item(pFile->Tbl, 123)[2].klass);
  v10 = Allocate(callbackDelegate);
  v11 = Method_Project_evtCutIn_Callback__;
  callback = v10;
  v13 = *((u64 *)Method_Project_evtCutIn_Callback__ + 1);
  v10->method = Method_Project_evtCutIn_Callback__;
  v10->method_ptr = v13;
  v10->m_target = 0;
  v14 = v11[82];
  callback->method_code = callback;
  if (!sub_3BDA00())
  {
    v18 = sub_3BDC90(0, "Delegate to an instance method cannot have null 'this'.");
  }
  if (v14 == 1)
  {
    method_ptr = sub_7AB0;
  }
  else
  {
    method_ptr = callback->method_ptr;
    callback->method_code = callback->m_target;
  }
  callback->invoke_impl = method_ptr;
  callback->extra_arg = sub_7A50;
  started = evtPictureStartProcess4(x, y, 11004, 0, 0, 0, 0, 0x7Bu, callback, texpath, monitor, ui_mode, cutInType);
  (loc_19E7EF0)(123, started, 0);
  gPictureOtEx = 93;
  return started;
}

// 0x19e1f10
dds3ProcessID_t *evtStartCommand(dds3ProcessID_t *ParentPID, s32 X, s32 Y, s32 Type, u32 UID) {
  s32 v11;
  s32 v12;
  u32 v13;
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  v11 = Type % 1000;
  if ((u32)(Type % 1000) >= 4)
  {
    if (v11 == 100)
      v12 = 100;
    else
      v12 = 196610;
  }
  else
  {
    v12 = dword_3CFBF30[v11];
  }
  if ((u32)(Type - 1000) >= 0x3E8)
    v13 = v12;
  else
    v13 = v12 | 0x1000000;
  id = evtStart(0, ParentPID, 16 * X, 8 * Y, 11004, 0, 0, v13, UID);
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  LODWORD(ProcessData[1].klass) |= 2u;
  return id;
}

// 0x19e20b0
void evtEndCommand(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  if (PID)
  {
    ProcessData = dds3GetProcessData(id);
    if (!ProcessData)
      goto LABEL_10;
    goto LABEL_9000;
    if (!ProcessData)
    {
LABEL_10:
      LODWORD(ProcessData[1].klass) |= 4u;
      return;
    }
LABEL_9000:
    goto LABEL_10;
  }
}
