#include "types.h"
#include "buttonguide.h"
#include "dat.h"
#include "dds3adminiprocess.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "evtbit.h"
#include "evtpmv.h"
#include "evtviewer.h"
#include "fclmisc.h"
#include "fclmsg.h"
#include "fld.h"
#include "jmsinit.h"
#include "jmsmain.h"
#include "jmsmenu.h"
#include "jmsmisc.h"
#include "kernel.h"
#include "localize.h"
#include "mdl.h"
#include "mdl_check.h"
#include "mjn.h"
#include "raijindlc.h"
#include "sbtlsub.h"
#include "scr.h"
#include "scrcommand.h"
#include "sdf3d.h"
#include "sdf_vu0.h"
#include "sdfquat.h"
#include "sdfsound.h"
#include "sndat3.h"

typedef struct SequenceParameter SequenceParameter;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct fileLoadAsset_Request fileLoadAsset_Request;
typedef struct jmsData_t jmsData_t;
typedef struct sdf3DLightParallelPacket_t sdf3DLightParallelPacket_t;
typedef struct sprHandle_t sprHandle_t;

dds3ProcessID_t *GlobalPID;
char *s_szModelName;
static s32 gCallFromMenu;
s32 gCallFromSubMenu;
fileLoadAsset_Request *uiReq;
static void *bgObj;
sdf3DLightParallelPacket_t *g_pLightPacket;
char *jms_asset_name;
static void *uiCtrl;

static s32 CheckModelLoad(s32 ModelTableIndex, jmsData_t *pData);
s32 ShutDown(void);

// macros
// 0x1ca0c50: void UIDISP(bool disp)
static inline void UIDISP(bool disp) {
  if (!op_Inequality(uiCtrl, 0, 0))
    return;
  UIDISP(uiCtrl, disp, 0);
}

// 0x1c9bad0
sprHandle_t *jmsGetSpriteHandle(void) {
  sprHandle_t *ProcessData;
  s64 naturalAligment;

  if (!GlobalPID)
    return 0;
  ProcessData = (sprHandle_t *)dds3GetProcessData(GlobalPID);
  if (!ProcessData)
    return ProcessData[24];
  LOBYTE(ProcessData[6].Type) < (u32)naturalAligment || *((jmsData_t **)(ProcessData)[4].monitor + naturalAligment - 1) != jmsData_t;
  return ProcessData[24];
}

// 0x1c9bc10
static s32 CheckModelLoad(s32 ModelTableIndex, jmsData_t *pData) {
  s32 max_length;
  s32 v6;
  s64 v7;
  s32 name;
  s32 name_high;
  jmsModelTable_t *Tbl;
  bool v11;
  s32 namespaze;
  bool v13;

  max_length = GetTbl(pData->jmsModel, ModelTableIndex, 0)->Flag->max_length;
  if (max_length - 1 < 0)
    return -1;
  v6 = -1;
  v7 = 8 * (u32)(max_length - 1) + 32;
  do
  {
    name = (*(Il2CppClass **)((char *)&GetTbl(pData->jmsModel, ModelTableIndex, 0)->Flag->obj.klass + v7))->_1.name;
    name_high = HIDWORD((*(Il2CppClass **)((char *)&GetTbl(pData->jmsModel, ModelTableIndex, 0)->Flag->obj.klass + v7))->_1.name);
    Tbl = GetTbl(pData->jmsModel, ModelTableIndex, 0);
    v11 = !name && name_high == 0;
    namespaze = (*(Il2CppClass **)((char *)&Tbl->Flag->obj.klass + v7))->_1.namespaze;
    v13 = v11 && namespaze == 0;
    if (!v13 && (!name || evtBitCheck(name)))
      break;
    --max_length;
    v7 -= 8;
  }
  while (max_length > 0);
  if (name_high && !evtBitCheck(name_high) || namespaze && evtBitCheck(namespaze))
    return -1;
  else
    return GetTbl(pData->jmsModel, ModelTableIndex, 0)->Minor;
}

// 0x1c9bd50
s32 jmsGetModelDefaultMotion(s32 Index, jmsData_t *pData) {
  return GetTbl(pData->jmsModel, pData->ModelIndex[Index], 0)->DefMotion;
}

// 0x1c9bd80
s32 jmsModelLoad(jmsData_t *pData) {
  jmsData_t *v3;
  s32 Flag;
  s32 ModelTableIndex;
  s32 v6;
  void *jmsModel;
  s32 TblCnt;
  jmsData_t *v10;
  s32 v11;
  s32 v12;
  s32 v13;
  dds3ModelResrc_t *v14;
  dds3ModelHandle_t *Model;
  s64 v16;
  dds3ModelHandle_t *v17;
  dds3ModelHandle_t *v18;
  Il2CppClass **v19;
  jmsData_t *v20;
  jmsModelTable_t *Tbl;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 *p_x;
  jmsData_t *v27;
  s64 v28;
  dds3ModelHandle_t *v29;
  jmsModelTable_t *v30;
  void *v31;
  s32 v32;
  f32 v33;
  f32 v34;
  f32 v35;
  s32 v36;
  s32 v37;
  sdf3DLightParallelPacket_t *v38;
  s32 ModelLoadCnt;
  unsigned __int128 v44;

  v3 = pData;
  Flag = pData->Flag;
  if ((Flag & 2) != 0)
  {
    if ((Flag & 8) != 0)
      return 0;
    if ((Flag & 4) != 0)
      v6 = Flag | 8;
    else
      v6 = Flag | 4;
    v3->Flag = v6;
    return 1;
  }
  if ((Flag & 1) != 0)
  {
    ModelTableIndex = v3->ModelTableIndex;
  }
  else
  {
    ModelTableIndex = 0;
    *(u64 *)&v3->ModelTableIndex = 0;
  }
  jmsModel = v3->jmsModel;
  v3->Flag = Flag | 1;
  TblCnt = GetTblCnt(jmsModel, 0);
  v10 = pData;
  if (ModelTableIndex >= TblCnt || v10->ModelLoadCnt >= SLODWORD(v10->Model->max_length))
    goto LABEL_43;
  v11 = v10->ModelTableIndex;
  v12 = CheckModelLoad(v11, v10);
  if (v12 < 0)
  {
    v10 = pData;
    ModelLoadCnt = pData->ModelLoadCnt;
    goto LABEL_42;
  }
  v13 = v12;
  v14 = mdlPrepare(3u, v13, 0);
  if (!READY(v14))
    return 1;
  Model = pData->Model;
  v16 = pData->ModelLoadCnt;
  v17 = mdlLoad(3u, v13);
  v18 = v17;
  v19 = &Model->obj.klass + v16;
  v19[4] = v18;
  v20 = pData;
  pData->ModelIndex[pData->ModelLoadCnt] = pData->ModelTableIndex;
  Tbl = GetTbl(v20->jmsModel, v20->ModelTableIndex, 0);
  FromEuler(0.0, Tbl->Angle * 0.017453292, 0.0);
  mdlSetRotate(pData->Model[pData->ModelLoadCnt]);
  v22 = GetTbl(pData->jmsModel, pData->ModelTableIndex, 0)->Pos[0];
  v23 = GetTbl(pData->jmsModel, pData->ModelTableIndex, 0)->Pos[1];
  v24 = GetTbl(pData->jmsModel, pData->ModelTableIndex, 0)->Pos[2];
  p_x = &vf00.x;
  p_x[4] = v22;
  p_x[5] = v23;
  p_x[6] = v24;
  p_x[7] = 0.0;
  mdlSetPosition(pData->Model[pData->ModelLoadCnt]);
  v27 = pData;
  v28 = pData->ModelLoadCnt;
  v29 = pData->Model[v28];
  v30 = GetTbl(v27->jmsModel, v27->ModelIndex[v28], 0);
  mdlLoopMotion(v29, 0, v30->DefMotion);
  mdlSetMotionSpeedEx(pData->Model[pData->ModelLoadCnt], 0, 0.5);
  mdlSetMotionSpeedEx(pData->Model[pData->ModelLoadCnt], 1, 0.5);
  mdlSetMotionSpeedEx(pData->Model[pData->ModelLoadCnt], 2, 0.5);
  v31 = pData->jmsModel;
  v32 = pData->ModelTableIndex;
  v44 = 0u;
  v33 = GetTbl(v31, v32, 0)->Pos[0];
  v34 = GetTbl(pData->jmsModel, pData->ModelTableIndex, 0)->Pos[1];
  v35 = GetTbl(pData->jmsModel, pData->ModelTableIndex, 0)->Pos[2];
  sBtlChangeWorldtoScreenUnity3(v33, v34 + -90.0, v35, &v44);
  if (*(f32 *)&v44 == INFINITY)
    v36 = 0x80000000;
  else
    v36 = *(f32 *)&v44;
  set_Item((sdfIVector2_t)&pData->ModelCursorPos[pData->ModelLoadCnt], 0, v36, 0);
  if (*((f32 *)&v44 + 1) == INFINITY)
    v37 = 0x80000000;
  else
    v37 = *((f32 *)&v44 + 1);
  set_Item((sdfIVector2_t)&pData->ModelCursorPos[pData->ModelLoadCnt], 1, v37, 0);
  v38 = Allocate(sdf3DLightParallelPacket_t);
  _ctor(v38, 0);
  g_pLightPacket = v38;
  jmsModelMakeLightPacket(pData->ModelTableIndex);
  mdlSetLight(pData->Model[pData->ModelLoadCnt], g_pLightPacket);
  v10 = pData;
  ModelLoadCnt = pData->ModelLoadCnt + 1;
  pData->ModelLoadCnt = ModelLoadCnt;
LABEL_42:
  ++v10->ModelTableIndex;
  if (ModelLoadCnt >= 2)
LABEL_43:
    v10->Flag |= 2u;
  return 1;
}

// 0x1c9d0d0
void jmsModelFree(jmsData_t *pData) {
  jmsData_t *v3;
  dds3ModelHandle_t *Model;
  s64 v5;
  s64 v6;
  u64 *v7;
  dds3ModelHandle_t *v8;

  v3 = pData;
  Model = pData->Model;
  if (SLODWORD(Model->max_length) >= 1)
  {
    v5 = 0;
    v6 = 32;
    do
    {
      v8 = *(dds3ModelHandle_t *)((char *)&Model->obj.klass + v6);
      if (v8)
      {
        Free(v8);
        v7 = ((char *)&pData->Model->obj.klass + v6);
        *v7 = 0;
        v3 = pData;
      }
      Model = v3->Model;
      ++v5;
      v6 += 8;
    }
    while (v5 < SLODWORD(Model->max_length));
  }
  v3->Flag &= 0xFFFFFFF0;
}

// 0x1c9c340
void jmsModelMakeLightPacket(s32 setModel) {
  Il2CppObject *ProcessData;
  sdfVector4_t *v7;
  _OWORD *v8;
  sdfVector4_t *v9;
  _OWORD *v10;
  sdf3DLight_t *v11;
  sdf3DLight_t *v12;
  sdf3DLight_t *v13;
  sdf3DLight_t *v14;
  sdf3DLight_t *m_Items;
  sdf3DLight_t *v16;
  sdf3DLight_t *v17;
  s32 klass;
  LightPacketClass *p_nightLight;
  sdf3DLight_t *v21;
  sdfVector4_t *v22;
  s32 v23;
  struct sdfVector4_t v24;
  sdf3DLight_t *v25;
  sdfVector4_t *v26;
  sdf3DLight_t *v28;
  sdfVector4_t *v29;
  s32 v30;
  struct sdfVector4_t v31;
  sdf3DLight_t *v32;
  sdfVector4_t *v33;
  sdf3DLight_t *v35;
  sdfVector4_t *v36;
  s32 v37;
  struct sdfVector4_t v38;
  sdf3DLight_t *v39;
  sdfVector4_t *v40;
  f32 w;
  f32 x;
  f32 y;
  f32 z;
  LightPacketClass *v46;
  sdf3DLight_t *v48;
  sdfVector4_t *p_color;
  struct sdfVector4_t v50;
  sdf3DLight_t *v51;
  sdfVector4_t *p_v;
  sdf3DLight_t *v54;
  sdfVector4_t *v55;
  struct sdfVector4_t v56;
  sdf3DLight_t *v57;
  sdfVector4_t *v58;
  sdf3DLight_t *v60;
  sdfVector4_t *v61;
  struct sdfVector4_t v62;
  sdf3DLight_t *v63;
  sdfVector4_t *v64;
  s32 v66;
  s32 v67;
  s32 v68;
  struct sdfVector4_t v70;
  struct sdfVector4_t v71;
  struct sdfVector4_t v72;
  struct sdfVector4_t v73;
  struct sdfVector4_t v74;
  struct sdfVector4_t v75;
  struct sdfVector4_t v82;
  struct sdfVector4_t v84;
  struct sdfVector4_t v86;
  sdfVector4_t v88;

  ProcessData = dds3GetProcessData(GlobalPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  v7 = NewSpecific(sdfVector4_t, 3u);
  *(u64 *)&v7[2].y = 0;
  v8 = v7;
  *(u64 *)&v7[1].w = 0;
  *(u32 *)&v7[2].w = 0;
  *(_OWORD *)&v7[0] = xmmword_3D01E40;
  *(u32 *)&v7[1].z = 1065353216;
  *(u64 *)&v7[1] = 0x3F8CCCCD3F99999ALL;
  v9 = NewSpecific(sdfVector4_t, 3u);
  *(u64 *)&v9[2].y = 0;
  v10 = v9;
  *(u64 *)&v9[1].w = 0;
  *(u32 *)&v9[2].w = 0;
  *(_OWORD *)&v9[0] = xmmword_3D06C00;
  *(u32 *)&v9[1].z = -1089344635;
  *(u64 *)&v9[1] = 0x3F4CCCCD3E4CCCCDLL;
  v11 = Allocate(sdf3DLight_t);
  _ctor(v11, 0);
  v12 = Allocate(sdf3DLight_t);
  _ctor(v12, 0);
  v13 = Allocate(sdf3DLight_t);
  _ctor(v13, 0);
  v14 = NewSpecific(sdf3DLight_t, 3u);
  v14[2] = v13;
  v17 = &v14[2];
  if (g_pLightPacket)
  {
    if (setModel != -1)
    {
      klass = ProcessData[16].klass;
      if (klass == 3)
      {
        p_nightLight = &GetTbl(ProcessData[15].klass, setModel, 0)->nightLight;
      }
      else if (klass == 2)
      {
        p_nightLight = &GetTbl(ProcessData[15].klass, setModel, 0)->eveningLight;
      }
      else
      {
        p_nightLight = &GetTbl(ProcessData[15].klass, setModel, 0)->lunchLight;
      }
      v46 = p_nightLight;
      v73 = p_nightLight->Col[0];
      vct_A = v73;
      v48 = m_Items;
      p_color = &v48->color;
      *p_color = vct_A;
      v50 = v46->Dir[0];
      vct_A = v50;
      v51 = m_Items;
      p_v = &v51->v;
      *p_v = vct_A;
      v74 = v46->Col[1];
      vct_A = v74;
      v54 = v16;
      v55 = &v54->color;
      *v55 = vct_A;
      v56 = v46->Dir[1];
      vct_A = v56;
      v57 = v16;
      v58 = &v57->v;
      *v58 = vct_A;
      v75 = v46->Col[2];
      vct_A = v75;
      v60 = v17;
      v61 = &v60->color;
      *v61 = vct_A;
      v62 = v46->Dir[2];
      vct_A = v62;
      v63 = v17;
      v64 = &v63->v;
      *v64 = vct_A;
      x = v46->Ambient.x;
      y = v46->Ambient.y;
      z = v46->Ambient.z;
      w = v46->Ambient.w;
LABEL_83:
      v88.x = x;
      v88.y = y;
      v88.z = z;
      v88.w = w;
      sdf3MakeLightParallelPacket(g_pLightPacket, v14, v88, 1);
      return;
    }
    v70 = (struct sdfVector4_t)v8[2];
    vct_A = v70;
    v21 = m_Items;
    v22 = &v21->color;
    v23 = (u8)byte_5755EF5;
    *v22 = vct_A;
    v24 = (struct sdfVector4_t)v10[2];
    if (v23)
      goto LABEL_29;
    goto LABEL_118;
    if (v66)
    {
LABEL_29:
      goto LABEL_30;
    }
LABEL_118:
    v82 = v24;
    v24 = v82;
LABEL_30:
    vct_A = v24;
    v25 = m_Items;
    v26 = &v25->v;
    *v26 = vct_A;
    v71 = (struct sdfVector4_t)v8[3];
    vct_A = v71;
    v28 = v16;
    v29 = &v28->color;
    v30 = (u8)byte_5755EF5;
    *v29 = vct_A;
    v31 = (struct sdfVector4_t)v10[3];
    if (v30)
      goto LABEL_38;
    goto LABEL_127;
    if (v67)
    {
LABEL_38:
      goto LABEL_39;
    }
LABEL_127:
    v84 = v31;
    v31 = v84;
LABEL_39:
    vct_A = v31;
    v32 = v16;
    v33 = &v32->v;
    *v33 = vct_A;
    v72 = (struct sdfVector4_t)v8[4];
    vct_A = v72;
    v35 = v17;
    v36 = &v35->color;
    v37 = (u8)byte_5755EF5;
    *v36 = vct_A;
    v38 = (struct sdfVector4_t)v10[4];
    if (v37)
      goto LABEL_47;
    goto LABEL_136;
    if (v68)
    {
LABEL_47:
LABEL_48:
      vct_A = v38;
      v39 = v17;
      v40 = &v39->v;
      w = 1.0;
      x = 0.3;
      y = 0.2;
      *v40 = vct_A;
      z = 0.2;
      goto LABEL_83;
    }
LABEL_136:
    v86 = v38;
    v38 = v86;
    goto LABEL_48;
  }
}

// 0x1c9d1b0
void jmsLoadBgModel(dds3ProcessID_t *ParentPID, jmsData_t *pData) {
  s32 v4;
  jmsData_t *v5;
  dds3ProcessID_t *v6;
  dds3ProcessID_t *p_PmvPID;
  dds3ProcessID_t *PmvPID;
  dds3ProcessID_t *parent;

  parent = ParentPID;
  if ((pData->Flag & 0x30) != 0)
    return;
  if (evtBitCheck(42))
    v4 = 1;
  else
    v4 = 2;
  if (evtBitCheck(144) && !evtBitCheck(146))
    v4 = 2;
  if (evtBitCheck(205))
    v4 = 2;
  if (evtBitCheck(147) && !evtBitCheck(350))
    v4 = 3;
  v5 = pData;
  pData->cutNo = v4;
  v6 = evtStart2(0, 685, v4, 1);
  v5->PmvPID = v6;
  p_PmvPID = &pData->PmvPID;
  dds3LinkProcess(parent, p_PmvPID);
  scrSetMovieCancel(0);
  PmvPID = pData->PmvPID;
  evtIgnoreFade(PmvPID);
  evtIgnoreAtracPlay(pData->PmvPID);
  pData->Flag |= 0x10u;
}

// 0x1c9d3c0
s32 jmsCheckBgModel(jmsData_t *pData) {
  dds3ProcessID_t *PmvPID;
  void *Instance;
  _BOOL4 v7;
  void *v9;

  PmvPID = pData->PmvPID;
  if (!evtCheckRun(PmvPID))
    return 0;
  pData->Flag |= 0x20u;
  if (evtBitCheck(146) && !evtBitCheck(145))
  {
    GBWK->IntVariable[200] = 0;
  }
  Instance = get_Instance(0);
  v7 = evtBitCheck(110) && !evtBitCheck(225)
    || !evtBitCheck(42)
    || evtBitCheck(81) && !evtBitCheck(83);
  SetParts(Instance, Instance->disableParts | v7, 0);
  v9 = get_Instance(0);
  bgObj = v9;
  return 1;
}

// 0x1c9d5f0
void jmsFreeBgModel(jmsData_t *pData) {
  jmsData_t *v5;
  dds3ProcessID_t *PmvPID;

  bgObj = 0;
  v5 = pData;
  PmvPID = pData->PmvPID;
  if (PmvPID)
  {
    evtEnd(PmvPID);
    v5 = pData;
  }
  v5->PmvPID = 0;
  pData->Flag &= 0xFFFFFFCF;
}

// 0x1c9d6c0
void jmsSetBgDisp(bool bo) {
  if (!op_Inequality(bgObj, 0, 0))
    return;
  SetActive(bgObj, bo, 0);
}

// 0x1c9d7d0
void jmsStartEtcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *v5;
  dds3ProcessFunc_t v6;
  dds3ProcessFunc_t v7;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = Allocate(dds3ProcessID_t);
  _ctor(v5, 0);
  mapTitleSkip();
  dds3FadeIn(0, 0, 0, 0x1Eu);
  v6 = Allocate(dds3ProcessFunc_t);
  _ctor(v6, 0, Method_Project_jmsMain_RootWaitDrawProcess__, 0);
  dds3StartProcess("jimusyo_draw", 11028, 0, 0, v6, 0, ProcessData);
  v7 = Allocate(dds3ProcessFunc_t);
  _ctor(v7, 0, Method_Project_jmsMain_RootWaitUpdateProcess__, 0);
  dds3StartProcess("jimusyo_updt", 21009, 0, 0, v7, 0, ProcessData);
}

// 0x1c9da30
void jmsAddTalkMenu(jmsData_t *pData) {
  s64 v3;
  s64 v5;
  char *v6;
  char *LocalizeText;

  if (pData->ModelLoadCnt >= 2)
  {
    v3 = 0;
    do
    {
      v5 = pData->ModelIndex[v3];
      v6 = s_szModelName[v5];
      LocalizeText = GetLocalizeText(v6, 1);
      jmsAddTalkTarget(v3++, LocalizeText);
    }
    while (v3 < pData->ModelLoadCnt);
  }
}

// 0x1c9db50
s32 jmsBgmLoad(jmsData_t *pData) {
  jmsData_t *v3;
  s32 BgmNo;

  v3 = pData;
  if ((pData->Flag & 0x100) != 0)
    return 1;
  BgmNo = v3->BgmNo;
  sndBgmLoadId_XF(BgmNo);
  pData->Flag |= 0x100u;
  return 0;
}

// 0x1c9dbf0
s32 jmsBgmPlay(jmsData_t *pData) {
  if ((pData->Flag & 0x200) != 0)
    return 1;
  if (sndBgmStatus_XF() == 2)
  {
    sndBgmFadeIn(0, 0);
    pData->Flag |= 0x200u;
    sndBgmPlay(0, 0);
    return 1;
  }
  return 0;
}

// 0x1c9dcd0
void jmsLoadLocalizeText(void) {
  ;
}

// 0x1c9dce0
dds3ProcessFunc_t jmsLoad2ndProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *klass;
  s32 v10;
  s32 v12;
  dds3ProcessID_t *v14;
  dds3ProcessID_t *v17;
  s32 v19;
  dds3ProcessFunc_t v20;
  Il2CppObject *v24;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  klass = ProcessData[8].klass;
  v24 = ProcessData;
  if (jmsCheckScrRun(klass))
  {
    goto LABEL_12;
  }
  ProcessData[8].klass = 0;
LABEL_12:
  if (jmsModelLoad(v24))
    return 0;
  if ((BYTE1(ProcessData[1].klass) & 4) != 0)
    goto LABEL_28;
  if ((BYTE1(ProcessData[1].klass) & 1) == 0)
  {
    v10 = ProcessData[13].klass;
    sndBgmLoadId_XF(v10);
    LODWORD(ProcessData[1].klass) |= 0x100u;
    if (!jmsBgmPlay(v24))
      return 0;
    goto LABEL_28;
  }
  if (!jmsBgmPlay(v24))
    return 0;
LABEL_28:
  v12 = p2sdLoadCheckMidi(4259840);
  if (v12 == 2)
    return 0;
  if (!v12)
  {
    p2sdLoadSMGFile(4259840);
  }
  v14 = id;
  jmsLoadBgModel(v14, v24);
  if (!jmsCheckBgModel(v24))
    return 0;
  v17 = id;
  jmsStartEtcProcess(v17);
  ProcessStart(0);
  jmsSetFocus(0);
  jmsAddTalkMenu(ProcessData);
  v19 = ProcessData[1].klass;
  if ((v19 & 0x800) != 0)
    LODWORD(ProcessData[1].klass) = v19 | 0x400;
  v20 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v20, 0, Method_Project_jmsMain_RootWaitCalcProcess__, 0);
  return v20;
}

// 0x1c9e0a0
bool jmsCheckUIReq(void) {
  if (!uiReq)
    return 0;
  return uiReq->isDone;
}

// 0x1c9e150
dds3ProcessFunc_t jmsEventScrProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *klass;
  s32 v6;
  dds3ProcessFunc_t v8;
  dds3ProcessFunc_t v9;
  intptr_t *v10;
  u8 *monitor;
  dds3ProcessID_t *started;
  char *v14;
  fileLoadAsset_Request *Asset__AllSceneAsync;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  klass = ProcessData[7].klass;
  if (jmsCheckScrRun(ProcessData[7].klass))
  {
    v6 = ProcessData[1].klass;
    if ((v6 & 0x2000) == 0)
    {
      LODWORD(ProcessData[1].klass) = v6 | 0x2000;
      mapTitleSkip();
    }
    return 0;
  }
  if (HIDWORD(ProcessData[8].monitor))
  {
    v8 = Allocate(dds3ProcessFunc_t);
    v9 = v8;
    v10 = &Method_Project_jmsMain_EndProcess__;
  }
  else
  {
    monitor = ProcessData[7].monitor;
    started = scrStartScript2(1, monitor, 0, 1);
    ProcessData[8].klass = started;
    v14 = "ui_office";
    Load(Dependent, v14, v14);
    LoadSyncAll(_Ctrl_k__BackingField, 0);
    Asset__AllSceneAsync = AllSceneAsync(v14, 0);
    uiReq = Asset__AllSceneAsync;
    Unload(Dependent, v14, 0);
    v8 = Allocate(dds3ProcessFunc_t);
    v9 = v8;
    v10 = &Method_Project_jmsInit_Load2ndProcess__;
  }
  _ctor(v8, 0, *v10, 0);
  return v9;
}

// 0x1c9e4a0
dds3ProcessFunc_t jmsLoad0Process(dds3ProcessID_t *PID) {
  void *p_Dependent;
  void *v5;
  dds3ProcessFunc_t v6;

  p_Dependent = &Dependent;
  v5 = p_Dependent;
  Load(v5, jms_asset_name, jms_asset_name);
  v6 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v6, 0, Method_Project_jmsInit_Load1stProcess__, 0);
  return v6;
}

// 0x1c9e590
dds3ProcessFunc_t jmsLoad1stProcess(dds3ProcessID_t *PID) {
  void *p_Dependent;
  void *Dependent_local;
  bool IsLoad;
  dds3ProcessFunc_t v7;
  Il2CppObject *ProcessData;
  void *Ctrl_k__BackingField;
  void *Asset;
  sdfBinary *v15;
  u8 *data;
  Il2CppObject *monitor;
  void *v19;
  sdfBinary *v20;
  Il2CppClass *v21;
  REPORT_READ_FLAG_CLASS *v22;
  REPORT_READ_FLAG_CLASS *v23;
  REPORT_READ_FLAG_CLASS *v24;
  REPORT_READ_FLAG_CLASS *v25;
  REPORT_READ_FLAG_CLASS *v26;
  REPORT_READ_FLAG_CLASS *v27;
  REPORT_READ_FLAG_CLASS *v28;
  REPORT_READ_FLAG_CLASS *v29;
  REPORT_READ_FLAG_CLASS *v30;
  REPORT_READ_FLAG_CLASS *v31;
  REPORT_READ_FLAG_CLASS *v32;
  REPORT_READ_FLAG_CLASS *v33;
  REPORT_READ_FLAG_CLASS *v34;
  il2cpp_array_size_t max_length;
  s64 v37;
  REPORT_READ_FLAG_CLASS *m_Items;
  REPORT_READ_FLAG_CLASS *v39;
  bool *report_readFlag;
  s64 v42;
  s64 v43;
  REPORT_READ_FLAG_CLASS *v44;
  REPORT_READ_FLAG_CLASS *v45;
  void *v52;
  void *v53;
  sdfBinary *v54;
  void *v56;
  sdfBinary *v57;
  void *v59;
  sdfBinary *v60;
  u8 *v61;
  u8 *v62;
  Il2CppClass *v63;
  void *v65;
  sdfBinary *v66;
  u8 *v67;
  void *v69;
  void *v70;
  Il2CppObject *v73;
  u8 *v74;
  dds3ProcessID_t *started;
  s32 *klass;
  s64 v77;
  s64 v78;
  Il2CppObject *v79;
  s64 i;
  s32 PackItemNo;
  Il2CppClass *v82;
  s64 v83;
  s32 PackItemCnt;
  s64 v85;
  s32 *v86;
  s64 v87;
  s64 v88;
  Il2CppObject *v89;
  s64 j;
  s32 v91;
  u64 *v92;
  s64 v93;
  s32 v94;
  s64 v95;
  s32 *v96;
  s64 v97;
  s64 v98;
  Il2CppObject *v99;
  s64 k;
  s32 v102;
  Il2CppClass *v103;
  s64 v104;
  s32 v105;
  s64 v106;
  void *v108;
  dds3ProcessID_t *id;

  id = PID;
  p_Dependent = &Dependent;
  Dependent_local = p_Dependent;
  IsLoad = IsLoad(Dependent_local, jms_asset_name, 0);
  v7 = 0;
  if (IsLoad)
  {
    Create(0);
    ProcessData = dds3GetProcessData(id);
    if (!ProcessData)
    Ctrl_k__BackingField = _Ctrl_k__BackingField;
    Asset = LoadAsset(Ctrl_k__BackingField, jms_asset_name, "jms_mes.bmd", 0);
    v15 = Allocate(sdfBinary);
    _ctor(v15, Asset, 0);
    data = v15->data;
    ProcessData[11].monitor = data;
    monitor = ProcessData[11].monitor;
    fclInitMessage(ProcessData[11].monitor);
    v19 = LoadAsset(_Ctrl_k__BackingField, jms_asset_name, "jms_file.bmd", 0);
    v20 = Allocate(sdfBinary);
    _ctor(v20, v19, 0);
    v21 = v20->data;
    ProcessData[10].klass = v21;
    v22 = NewSpecific(REPORT_READ_FLAG_CLASS, 0xCu);
    v23 = Allocate(REPORT_READ_FLAG_CLASS);
    _ctor(v23, 0);
    v22[0] = v23;
    v24 = Allocate(REPORT_READ_FLAG_CLASS);
    _ctor(v24, 0);
    v22[1] = v24;
    v25 = Allocate(REPORT_READ_FLAG_CLASS);
    _ctor(v25, 0);
    v22[2] = v25;
    v26 = Allocate(REPORT_READ_FLAG_CLASS);
    _ctor(v26, 0);
    v22[3] = v26;
    v27 = Allocate(REPORT_READ_FLAG_CLASS);
    _ctor(v27, 0);
    v22[4] = v27;
    v28 = Allocate(REPORT_READ_FLAG_CLASS);
    _ctor(v28, 0);
    v22[5] = v28;
    v29 = Allocate(REPORT_READ_FLAG_CLASS);
    _ctor(v29, 0);
    v22[6] = v29;
    v30 = Allocate(REPORT_READ_FLAG_CLASS);
    _ctor(v30, 0);
    v22[7] = v30;
    v31 = Allocate(REPORT_READ_FLAG_CLASS);
    _ctor(v31, 0);
    v22[8] = v31;
    v32 = Allocate(REPORT_READ_FLAG_CLASS);
    _ctor(v32, 0);
    v22[9] = v32;
    v33 = Allocate(REPORT_READ_FLAG_CLASS);
    _ctor(v33, 0);
    v22[10] = v33;
    v34 = Allocate(REPORT_READ_FLAG_CLASS);
    _ctor(v34, 0);
    v22[11] = v34;
    max_length = v22->max_length;
    if ((s32)max_length >= 1)
    {
      v37 = 0;
      m_Items = v22;
      do
      {
        v44 = m_Items[v37];
        v39 = m_Items[v37];
        report_readFlag = GBWK->report_readFlag;
        v42 = (s64)GBWK->report_updateFlag + 4 * v37;
        v43 = (s64)report_readFlag + v37++;
        LODWORD(v42) = *(u32 *)(v42 + 32);
        v44->READ_FLAG = *(u8 *)(v43 + 32);
        v39->UPDATE_FLAG = v42;
      }
      while (v37 < (s32)max_length);
    }
    v45 = NewSpecific(REPORT_READ_FLAG_CLASS, max_length);
    REPORT_READ_FLAG = v45;
    REPORT_READ_FLAG = v22;
    v52 = _Ctrl_k__BackingField;
LABEL_57:
    v53 = LoadAsset(v52, jms_asset_name, "jms_evt.bf", 0);
    v54 = Allocate(sdfBinary);
    _ctor(v54, v53, 0);
    v56 = LoadAsset(_Ctrl_k__BackingField, jms_asset_name, "jms_evt2.bf", 0);
    v57 = Allocate(sdfBinary);
    _ctor(v57, v56, 0);
    v59 = LoadAsset(_Ctrl_k__BackingField, jms_asset_name, "jms_talk.bf", 0);
    v60 = Allocate(sdfBinary);
    _ctor(v60, v59, 0);
    v61 = v54->data;
    ProcessData[6].monitor = v61;
    v62 = v57->data;
    ProcessData[7].monitor = v62;
    v63 = v60->data;
    ProcessData[5].klass = v63;
    v65 = LoadAsset(_Ctrl_k__BackingField, jms_asset_name, "jmsQuest.bf", 0);
    v66 = Allocate(sdfBinary);
    _ctor(v66, v65, 0);
    v67 = v66->data;
    ProcessData[13].monitor = v67;
    v69 = LoadAsset(_Ctrl_k__BackingField, jms_asset_name, "JmsModelTbl", 0);
    v70 = v69;
    if (!v69)
    {
      ProcessData[15].klass = 0;
      v73 = ProcessData + 15;
    }
    v74 = ProcessData[6].monitor;
    started = scrStartScript2(1, v74, 0, 1);
    ProcessData[7].klass = started;
    DLC_ItemInit();
    if (!IsBuyItem())
      goto LABEL_136;
    klass = ProcessData[17].klass;
    if (klass[6] < 1)
    {
LABEL_103:
      for (i = 4; ; ++i)
      {
        if (i - 4 >= GetPackItemMax(0))
          break;
        v85 = *((u64 *)&ProcessData[17].klass->_1.image + i);
        PackItemNo = GetPackItemNo(0, i - 4);
        v82 = ProcessData[17].klass;
        *(u32 *)(v85 + 16) = PackItemNo;
        v83 = *((u64 *)&v82->_1.image + i);
        PackItemCnt = GetPackItemCnt(0, i - 4);
        *(u32 *)(v83 + 20) = PackItemCnt;
      }
      v86 = ProcessData[17].monitor;
      if (v86[6] < 1)
      {
LABEL_116:
        for (j = 4; ; ++j)
        {
          if (j - 4 >= GetPackItemMax(1))
            break;
          v95 = *((u64 *)ProcessData[17].monitor + j);
          v91 = GetPackItemNo(1, j - 4);
          v92 = ProcessData[17].monitor;
          *(u32 *)(v95 + 16) = v91;
          v93 = v92[j];
          v94 = GetPackItemCnt(1, j - 4);
          *(u32 *)(v93 + 20) = v94;
        }
        v96 = ProcessData[18].klass;
        if (v96[6] < 1)
        {
LABEL_129:
          for (k = 4; ; ++k)
          {
            if (k - 4 >= GetPackItemMax(2))
              break;
            v106 = *((u64 *)&ProcessData[18].klass->_1.image + k);
            v102 = GetPackItemNo(2, k - 4);
            v103 = ProcessData[18].klass;
            *(u32 *)(v106 + 16) = v102;
            v104 = *((u64 *)&v103->_1.image + k);
            v105 = GetPackItemCnt(2, k - 4);
            *(u32 *)(v104 + 20) = v105;
          }
LABEL_136:
          v108 = Dependent;
          Unload(v108, jms_asset_name, 0);
          v7 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
          _ctor(v7, 0, Method_Project_jmsInit_EventScrProcess__, 0);
          return v7;
        }
        v97 = 0;
        v98 = 8;
        while (1)
        {
          v99 = Allocate(DlcItem_t);
          _ctor(v99, 0);
          if (v99)
          {
            if (!QueryInterface(v99, *(void **)(*(u64 *)v96 + 64)))
              break;
          }
          *(u64 *)&v96[v98] = v99;
          v96 = ProcessData[18].klass;
          ++v97;
          v98 += 2;
          if (v97 >= v96[6])
            goto LABEL_129;
        }
      }
      else
      {
        v87 = 0;
        v88 = 8;
        while (1)
        {
          v89 = Allocate(DlcItem_t);
          _ctor(v89, 0);
          if (v89)
          {
            if (!QueryInterface(v89, *(void **)(*(u64 *)v86 + 64)))
              break;
          }
          *(u64 *)&v86[v88] = v89;
          v86 = ProcessData[17].monitor;
          ++v87;
          v88 += 2;
          if (v87 >= v86[6])
            goto LABEL_116;
        }
      }
    }
    else
    {
      v77 = 0;
      v78 = 8;
      while (1)
      {
        v79 = Allocate(DlcItem_t);
        _ctor(v79, 0);
        if (v79)
        {
          if (!QueryInterface(v79, *(void **)(*(u64 *)klass + 64)))
            break;
        }
        *(u64 *)&klass[v78] = v79;
        klass = ProcessData[17].klass;
        ++v77;
        v78 += 2;
        if (v77 >= klass[6])
          goto LABEL_103;
      }
    }
    v52 = _Ctrl_k__BackingField;
    goto LABEL_57;
  }
  return v7;
}

// 0x1c9f540
jmsData_t *Init(void) {
  jmsData_t *v1;
  jmsSeqHandle_t *SeqHandle;

  v1 = (jmsData_t *)Allocate(jmsData_t);
  _ctor(v1);
  v1->MenuFade = 1;
  SeqHandle = v1->SeqHandle;
  v1->BgmNo = 16;
  jmsInitSeqHandle(SeqHandle);
  if (!evtBitCheck(42))
    v1->cutNo = 2;
  if (evtBitCheck(144) && !evtBitCheck(146))
    v1->cutNo = 2;
  if (evtBitCheck(205))
    v1->cutNo = 2;
  if (evtBitCheck(147) && !evtBitCheck(350))
    v1->cutNo = 3;
  return v1;
}

// 0x1c9f660
void jmsDestroy(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsData_t *v4;
  s32 ExitFlag;
  void *Instance;
  u8 **p_pEvt2ScrData;
  jmsSeqHandle_t *v15;
  dds3ProcessID_t *v16;
  s32 *EventBit;
  jmsData_t *v21;
  dds3ProcessID_t *id;

  id = PID;
  goto LABEL_3;
LABEL_26:
  ExitFlag = 0;
  goto LABEL_32;
LABEL_3:
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_26;
  v4 = ProcessData;
  v21 = v4;
  ExitFlag = v4->ExitFlag;
  g_pLightPacket = 0;
  MenuActive = 0;
  jmsUiCampCheck = 0;
  dds3KillProcessName("jimusyo_draw", 0);
  dds3KillProcessName("jimusyo_updt", 0);
  jmsFreeBgModel(v21);
  jmsModelFree(v21);
  Instance = get_Instance(0);
  ItfButtonGuideActive(Instance, 0, 0);
  fclDestroyMessage();
  Delete(0);
  v4->pScrData = 0;
  v4->pEvtScrData = 0;
  v4->pEvt2ScrData = 0;
  p_pEvt2ScrData = &v4->pEvt2ScrData;
  v15 = *(p_pEvt2ScrData - 12);
  v16 = id;
  jmsSeqDestroyAll(v15, v16);
  ProcessEnd();
  sndBgmFadeOut2();
  p2sdSndStop(3);
  if (!gMjnRun)
    goto LABEL_32;
  ShutDown();
LABEL_32:
  GlobalPID = 0;
  if (ExitFlag != 3)
  {
    if (ExitFlag == 2)
    {
      dds3AdminiCallSequence4(17, 0, 0, 0);
      return;
    }
    if (!gCallFromSubMenu)
      goto LABEL_44;
  }
  goto LABEL_40;
LABEL_44:
  mapReturnFromShop(3);
LABEL_40:
  EventBit = GBWK->EventBit;
  EventBit[72] &= ~1u;
}

// 0x1c9fb30
dds3ProcessID_t *jmsProcessStart(SequenceParameter *param) {
  dds3ProcessID_t *v2;
  Il2CppObject *inited;
  dds3ProcessFunc_t v5;
  shutdownfuncDelegate v6;
  dds3ProcessID_t *started;

  v2 = Allocate(dds3ProcessID_t);
  _ctor(v2, 0);
  dds3FadeOut(0, 0, 0, 0);
  inited = Init();
  v5 = Allocate(dds3ProcessFunc_t);
  _ctor(v5, 0, Method_Project_jmsInit_Load0Process__, 0);
  v6 = Allocate(shutdownfuncDelegate);
  _ctor(v6, 0, Method_Project_jmsInit_Destroy__, 0);
  started = dds3StartProcess("jimusyo_calc", 1030, 0, 1, v5, v6, inited);
  GlobalPID = started;
  *(u64 *)&gCallFromMenu = 0;
  return started;
}

// 0x1c9fd20
void jmsProcessEnd(void) {
  jmsReturnReadFlagData();
  REPORT_READ_FLAG = 0;
  dds3KillProcessName("jimusyo_calc", 0);
  dds3KillProcessName("jimusyo_draw", 0);
  dds3KillProcessName("jimusyo_updt", 0);
  GuideObjClr();
  uiCtrl = 0;
  if (uiReq)
  {
    AllSceneUnload(uiReq, 0);
    uiReq = 0;
  }
  p2sdUnLoadAllSMGFile();
}

// 0x1c9ffa0
void jmsReturnReadFlagData(void) {
  s64 v1;
  char *v3;
  s64 v4;
  s64 v5;
  s64 v6;
  char v7;
  bool *report_readFlag;

  v1 = 0;
  while (1)
  {
    if (v1 >= SLODWORD(REPORT_READ_FLAG->max_length))
      break;
    report_readFlag = GBWK->report_readFlag;
    v3 = (char *)report_readFlag + v1;
    v4 = (s64)GBWK->report_updateFlag + 4 * v1;
    v5 = (s64)REPORT_READ_FLAG + 8 * v1++;
    v6 = *(u64 *)(v5 + 32);
    v7 = *(u8 *)(v6 + 16);
    LODWORD(v6) = *(u32 *)(v6 + 20);
    v3[32] = v7;
    *(u32 *)(v4 + 32) = v6;
  }
}

// 0x1ca00d0
s32 jmsProcessCheck(void) {
  return dds3SearchProcessName("jimusyo_calc") != 0;
}

// 0x1ca0150
dds3ProcessID_t *jmsDebugProcessStart(SequenceParameter *param) {
  dds3ProcessID_t *result;

  result = jmsProcessStart(jmsInit);
  gCallFromMenu = 1;
  return result;
}

// 0x1ca01c0
void jmsDebugProcessEnd(void) {
  jmsProcessEnd();
}

// 0x1ca0230
s32 jmsDebugProcessCheck(void) {
  return dds3SearchProcessName("jimusyo_calc") != 0;
}

// 0x1ca0320
s32 jmsScrCmd_CALL_JIMUSYO(void) {
  scrGetIntPara(0);
  dds3AdminiCallSequence4(17, 0, 0, 0);
  scrAllReleaseScript();
  return 1;
}

// 0x1ca03a0
s32 jmsScrCmd_JMS_MOTION(void) {
  Il2CppObject *ProcessData;
  s32 IntPara;
  s32 v7;
  s64 klass_high;
  s32 v9;
  s64 v10;
  dds3ModelHandle_t *v11;

  if (!GlobalPID)
    return 1;
  ProcessData = dds3GetProcessData(GlobalPID);
  if (!ProcessData)
    goto LABEL_15;
  goto LABEL_13;
  if (!ProcessData)
LABEL_13:
LABEL_15:
  IntPara = scrGetIntPara(0);
  v7 = scrGetIntPara(1);
  klass_high = HIDWORD(ProcessData[9].klass);
  if ((s32)klass_high < 1)
    return 1;
  v9 = v7;
  v10 = 0;
  while (*((u32 *)ProcessData[3].monitor + v10 + 8) != IntPara)
  {
    if (klass_high == ++v10)
      return 1;
  }
  v11 = *((dds3ModelHandle_t *)&ProcessData[3].klass->_1.byval_arg.data + v10);
  if (v7)
  {
    mdlSmoothSingleMotion(v11, 0, v9, 15.0, 15.0, 0.0);
    return 1;
  }
  else
  {
    mdlSmoothLoopMotion(v11, 0, 0, 15.0, 15.0, 0.0);
    return 1;
  }
}

// 0x1ca0600
s32 jmsScrCmd_JMS_GET_INDEX(void) {
  Il2CppObject *ProcessData;
  s32 v6;

  if (!GlobalPID)
    return 1;
  ProcessData = dds3GetProcessData(GlobalPID);
  if (!ProcessData)
  v6 = *((u32 *)ProcessData[3].monitor + SLODWORD(ProcessData[9].monitor) + 8);
  scrSetIntReturnValue(v6);
  return 1;
}

// 0x1ca0780
s32 jmsScrCmd_JMS_EXIT(void) {
  Il2CppObject *ProcessData;
  s32 IntPara;
  s32 v8;

  if (!GlobalPID)
    return 1;
  ProcessData = dds3GetProcessData(GlobalPID);
  if (!ProcessData)
    goto LABEL_15;
  goto LABEL_13;
  if (!ProcessData)
LABEL_13:
LABEL_15:
  IntPara = scrGetIntPara(0);
  if (IntPara != 1)
    goto LABEL_17;
  v8 = 2;
LABEL_26:
  HIDWORD(ProcessData[8].monitor) = v8;
  return 1;
LABEL_17:
  if (IntPara)
  {
    v8 = 3;
    goto LABEL_26;
  }
  HIDWORD(ProcessData[8].monitor) = 1;
  return !dds3SearchProcessName("jimusyo_calc");
}

// 0x1ca09e0
s32 jmsScrCmd_JMS_SET_MODE(void) {
  Il2CppObject *ProcessData;
  s32 IntPara;
  u32 v7;
  u32 v8;
  u32 klass;

  if (!GlobalPID)
    return 1;
  ProcessData = dds3GetProcessData(GlobalPID);
  if (!ProcessData)
  scrGetIntPara(0);
  IntPara = scrGetIntPara(1);
  switch (IntPara)
  {
    case -3:
      v7 = LODWORD(ProcessData[1].klass) | 0x1400;
      LODWORD(ProcessData[1].klass) = v7;
      return (v7 >> 5) & 1;
    case -2:
      v8 = LODWORD(ProcessData[1].klass) | 0x400;
      LODWORD(ProcessData[1].klass) = v8;
      return (v8 >> 5) & 1;
    case -1:
      return (LODWORD(ProcessData[1].klass) >> 5) & 1;
    default:
      klass = ProcessData[1].klass;
      LODWORD(ProcessData[13].klass) = IntPara;
      klass |= 0x800u;
      LODWORD(ProcessData[1].klass) = klass;
      return (klass >> 5) & 1;
  }
}

// 0x1ca0be0
void jmsSetUI(void *ui) {
  uiCtrl = ui;
}

// 0x1ca0d60
bool jmsGetUI(void) {
  return op_Inequality(uiCtrl, 0, 0);
}

// 0x1ca0e30
bool jmsCeckUIDISP(void) {
  return uiCtrl->CheckBackFlag;
}
