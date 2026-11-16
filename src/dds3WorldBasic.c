#include "types.h"
#include "dds3basic.h"
#include "dds3worldbasic.h"

typedef struct dds3BasicArrayHandle_t dds3BasicArrayHandle_t;
typedef struct dds3BasicFunction_t dds3BasicFunction_t;
typedef struct dds3Basic_t dds3Basic_t;

dds3BasicFunction_t *Function;
dds3Basic_t *dds3TheWorld;

static bool Constructor(dds3Basic_t *basic);
static void Destructor(dds3Basic_t *basic);
static bool MainProcuder(dds3Basic_t *basic);
static bool DrawProcuder(dds3Basic_t *basic);

// 0x2308940
static bool Constructor(dds3Basic_t *basic) {
  void *v3;

  v3 = Allocate(dds3WorldBasic_t);
  _ctor(v3, 0);
  if (!v3)
    return 0;
  v3[1].klass = 0;
  v3[1].monitor = 0;
  v3[2].klass = 0;
  v3[2].monitor = 0;
  v3[3].klass = 0;
  v3[4].klass = 0;
  v3[3].monitor = 0xFFFFFFFF0000LL;
  v3[4].monitor = 0;
  basic->workdata = v3;
  return 1;
}

// 0x2308a50
static void Destructor(dds3Basic_t *basic) {
  void *workdata;
  dds3BasicArrayHandle_t *v6;
  Project_Basic_dds3Basic_t_WORK_c *klass;

  workdata = basic->workdata;
  if (workdata)
  {
    while (workdata[1].klass)
    {
      dds3DeleteScene(&workdata[1]);
    }
    klass = workdata[4].klass;
    v6 = &workdata[4];
    if (klass)
    {
      do
      {
        dds3FreeBasicArrayHandle(v6);
      }
      while (v6);
    }
  }
}

// 0x2308d70
static bool MainProcuder(dds3Basic_t *basic) {
  void *workdata;
  dds3Basic_t *klass;

  workdata = basic->workdata;
  klass = workdata[2].klass;
  if (klass)
  {
    dds3CallMainProcuder(klass);
  }
  return 1;
}

// 0x2308e30
static bool DrawProcuder(dds3Basic_t *basic) {
  void *workdata;
  dds3Basic_t *klass;

  workdata = basic->workdata;
  klass = workdata[2].klass;
  if (klass)
  {
    dds3CallDrawProcuder(klass);
  }
  return 1;
}

// 0x2308ef0
dds3Basic_t *Add(s32 bufcnt) {
  dds3Basic_t *v4;
  void *workdata;
  dds3Basic_t *v7;
  Project_Basic_dds3Basic_t_WORK_c *v9;
  void *v10;
  s64 v11;
  s64 v12;
  Project_Basic_dds3Basic_t_WORK_c *klass;
  Il2CppObject *v14;
  Project_Basic_dds3Basic_t_WORK_c *v16;
  s64 v17;
  u16 *data;
  void *v19;
  s64 v20;
  s16 v21;
  s64 v22;
  Project_Basic_dds3Basic_t_WORK_c *v23;
  s64 v24;

  v4 = 0;
  if ((u32)(bufcnt - 32) >> 5 > 0x3FE)
    return v4;
  if (dds3TheWorld)
    return v4;
  v7 = dds3Add(0);
  workdata = v7->workdata;
  v4 = v7;
  if (!workdata)
  v9 = NewSpecific(dds3BasicArray_t, bufcnt);
  workdata[3].klass = v9;
  v10 = workdata + 3;
  v11 = 32;
  v12 = bufcnt;
  do
  {
    klass = v10->klass;
    v14 = Allocate(dds3BasicArray_t);
    _ctor(v14, 0);
    if (v14)
      QueryInterface(v14, *((void **)klass->_1.image + 8));
    *(void **)((char *)&klass->_1.image + v11) = v14;
    v11 += 8;
    --v12;
  }
  while (v12);
  v16 = workdata[3].klass;
  v17 = (u32)(bufcnt - 1);
  LOWORD(workdata[3].monitor) = bufcnt;
  data = v16->_1.byval_arg.data;
  v19 = data + 8;
  data[13] = -1;
  if (bufcnt == 1)
  {
    data[12] = -1;
    *((u64 *)data + 2) = 0;
  }
  else
  {
    *((u64 *)data + 2) = 0;
    data[12] = 1;
    v20 = 0;
    do
    {
      v23 = v10->klass;
      v24 = *((u64 *)&v10->klass->_1.byval_arg.bits + v20);
      *(u16 *)(v24 + 26) = v20;
      if (v17 - 1 == v20)
      {
        v22 = *((u64 *)&v23->_1.byval_arg.data + v17);
        v21 = -1;
      }
      else
      {
        v21 = v20 + 2;
        v22 = v24;
      }
      *(u64 *)(v24 + 16) = 0;
      *(u16 *)(v22 + 24) = v21;
      ++v20;
    }
    while ((u32)bufcnt - 1 != v20);
  }
  WORD1(workdata[3].monitor) = 0;
  WORD2(workdata[3].monitor) = bufcnt - 1;
  HIWORD(workdata[3].monitor) = bufcnt;
  dds3TheWorld = v4;
  return v4;
}

// 0x2309200
void Delete(void) {
  if (dds3TheWorld)
    goto LABEL_4;
  return;
  if (dds3TheWorld)
  {
LABEL_4:
    dds3Delete(dds3TheWorld);
    dds3TheWorld = 0;
    return;
  }
}

// 0x2309300
void dds3SetActiveScene(dds3Basic_t *scene) {
  void *workdata;
  Project_Basic_dds3Basic_t_WORK_c *klass;

  if (!dds3TheWorld)
    return;
  workdata = dds3TheWorld->workdata;
  klass = workdata->klass;
}

// 0x2304120
dds3Basic_t *dds3GetActiveScene(void) {
  dds3Basic_t *workdata;
  s64 naturalAligment;

  if (!dds3TheWorld)
    return 0;
  workdata = (dds3Basic_t *)dds3TheWorld->workdata;
  if (!workdata)
    return workdata[4];
  LOBYTE(workdata[2].next) < (u32)naturalAligment || *((dds3WorldBasic_t **)(workdata)[1].worknext + naturalAligment - 1) != dds3WorldBasic_t;
  return workdata[4];
}

// 0x2309420
void dds3SetControlScene(dds3Basic_t *scene) {
  void *workdata;
  Project_Basic_dds3Basic_t_WORK_c *klass;

  if (!dds3TheWorld)
    return;
  workdata = dds3TheWorld->workdata;
  klass = workdata->klass;
}

// 0x22fc8d0
dds3Basic_t *dds3GetControlScene(void) {
  dds3Basic_t *workdata;
  s64 naturalAligment;

  if (!dds3TheWorld)
    return 0;
  workdata = (dds3Basic_t *)dds3TheWorld->workdata;
  if (!workdata)
    return workdata[5];
  LOBYTE(workdata[2].next) < (u32)naturalAligment || *((dds3WorldBasic_t **)(workdata)[1].worknext + naturalAligment - 1) != dds3WorldBasic_t;
  return workdata[5];
}

// 0x2309540
dds3Basic_t *dds3AddScene(void) {
  void *workdata;
  dds3Basic_t *v4;
  u64 *monitor;
  void **p_monitor;
  void *v9;
  dds3Basic_t *p_prev;

  if (!dds3TheWorld)
    return 0;
  workdata = dds3TheWorld->workdata;
  if (!workdata)
  v4 = dds3Add(1);
  if (!v4)
    return v4;
  p_monitor = &workdata[1].monitor;
  monitor = workdata[1].monitor;
  if (monitor)
  {
    monitor[8] = v4;
    v9 = *p_monitor;
    v4->prev = (dds3Basic_t *)*p_monitor;
    p_prev = &v4->prev;
  }
  else
  {
    workdata[1].klass = (Project_Basic_dds3Basic_t_WORK_c *)v4;
    p_prev = &workdata[1];
    v9 = v4;
  }
  *p_monitor = v4;
  return v4;
}

// 0x2308b60
void dds3DeleteScene(dds3Basic_t *scene) {
  void *workdata;
  dds3Basic_t *v7;
  void *v8;
  dds3Basic_t *klass;
  void **p_monitor;
  void *v11;
  void **v12;
  dds3Basic_t *monitor;
  dds3Basic_t *next;
  dds3Basic_t *prev;
  dds3Basic_t *v17;

  if (scene)
  {
    if (dds3TheWorld)
    {
      workdata = dds3TheWorld->workdata;
      if (!workdata)
      v7 = scene;
      v8 = workdata + 1;
      klass = workdata[1].klass;
      if (klass == scene)
      {
        next = klass->next;
        v8->klass = (Project_Basic_dds3Basic_t_WORK_c *)next;
        v7 = scene;
        p_monitor = &workdata[1].monitor;
        if (workdata[1].monitor != scene)
        {
LABEL_16:
          v11 = workdata + 2;
          if (workdata[2].klass != v7)
            goto LABEL_17;
          goto LABEL_22;
        }
      }
      else
      {
        p_monitor = &workdata[1].monitor;
        if (workdata[1].monitor != v7)
          goto LABEL_16;
      }
      prev = v7->prev;
      *p_monitor = prev;
      v7 = scene;
      v11 = workdata + 2;
      if (workdata[2].klass != scene)
      {
LABEL_17:
        monitor = workdata[2].monitor;
        v12 = &workdata[2].monitor;
        if (monitor != v7)
          goto LABEL_18;
        goto LABEL_23;
      }
LABEL_22:
      v11->klass = 0;
      v7 = scene;
      v17 = workdata[2].monitor;
      v12 = &workdata[2].monitor;
      if (v17 != scene)
      {
LABEL_18:
LABEL_19:
        dds3Delete(v7);
        return;
      }
LABEL_23:
      *v12 = 0;
      v7 = scene;
      goto LABEL_19;
    }
  }
}

// 0x23012f0
dds3BasicArrayHandle_t *dds3GetBasicArrayHandle(s32 bufcnt) {
  void *workdata;
  Il2CppObject *v7;
  u64 *monitor;
  void **p_monitor;
  void *v10;
  Il2CppObject *v11;
  dds3BasicArrayHandle_t *hndl;

  if (!dds3TheWorld)
    return 0;
  workdata = dds3TheWorld->workdata;
  if (!workdata)
  if (HIWORD(workdata[3].monitor) < bufcnt)
    return 0;
  v7 = Allocate(dds3BasicArrayHandle_t);
  _ctor(v7, 0);
  hndl = v7;
  if (v7)
  {
    v7[1].monitor = 0;
    v7[1].klass = 0xFFFFFFFFFFFFLL;
    v7[2].klass = 0;
    p_monitor = &workdata[4].monitor;
    monitor = workdata[4].monitor;
    if (monitor)
    {
      monitor[3] = v7;
      v10 = *p_monitor;
      v11 = v7 + 2;
      v7[2].klass = *p_monitor;
    }
    else
    {
      workdata[4].klass = (Project_Basic_dds3Basic_t_WORK_c *)v7;
      v11 = &workdata[4];
      v10 = v7;
    }
    *p_monitor = v7;
    dds3AddBasicArray(hndl, bufcnt);
  }
  return (dds3BasicArrayHandle_t *)v7;
}

// 0x2301720
void dds3FreeBasicArrayHandle(dds3BasicArrayHandle_t *hndl) {
  void *workdata;
  dds3BasicArrayHandle_t *next;
  dds3BasicArrayHandle_t *prev;
  u64 *p_next;
  dds3BasicArrayHandle_t *v10;
  dds3BasicArrayHandle_t *v11;
  u64 *p_prev;

  if (hndl)
  {
    if (!dds3TheWorld)
      return;
    workdata = dds3TheWorld->workdata;
    if (!workdata)
      goto LABEL_14;
    goto LABEL_9000;
    if (!workdata)
    {
LABEL_14:
      dds3DeleteAllBasicArray(hndl);
      next = hndl->next;
      prev = hndl->prev;
      if (prev)
        p_next = &prev->next;
      else
        p_next = &workdata[4].klass;
      *p_next = next;
      v11 = hndl->next;
      v10 = hndl->prev;
      if (v11)
        p_prev = &v11->prev;
      else
        p_prev = &workdata[4].monitor;
      *p_prev = v10;
      return;
    }
LABEL_9000:
    goto LABEL_14;
  }
}

// 0x2309890
void dds3DeleteBasicArray(dds3BasicArrayHandle_t *hndl) {
  dds3BasicArrayHandle_t *v3;
  void *workdata;
  s64 v8;
  dds3BasicArrayHandle_t *v9;
  Project_Basic_dds3Basic_t_WORK_c *klass;
  s64 nowindex;
  s64 v12;
  s64 v13;
  s32 v14;
  s16 v15;
  s32 v16;
  s16 monitor_high;

  v3 = hndl;
  if (hndl && v3->count && (v3->nowindex & 0x80000000) == 0)
  {
    if (!dds3TheWorld)
      return;
    workdata = dds3TheWorld->workdata;
    if (!workdata)
    v8 = *((u64 *)&workdata[3].klass->_1.byval_arg.data + hndl->nowindex);
    *(u64 *)(v8 + 16) = 0;
    v9 = hndl;
    klass = workdata[3].klass;
    nowindex = hndl->nowindex;
    v12 = *((u64 *)&klass->_1.byval_arg.data + nowindex);
    v13 = *(u16 *)(v12 + 24);
    v14 = *(s16 *)(v12 + 26);
    v15 = *(u16 *)(v12 + 24);
    if (v14 < 0)
    {
      v9->firstindex = v13;
      if (((s16)v13 & 0x80000000) == 0)
      {
LABEL_18:
        *(u16 *)(*((u64 *)&klass->_1.byval_arg.data + v13) + 26) = v14;
        *(u32 *)(v12 + 24) = -1;
        v16 = SWORD2(workdata[3].monitor);
        if ((v16 & 0x80000000) == 0)
        {
LABEL_19:
          *(u16 *)(v12 + 26) = v16;
          *(u16 *)(*((u64 *)&klass->_1.byval_arg.data + (u16)v16) + 24) = nowindex;
LABEL_23:
          monitor_high = HIWORD(workdata[3].monitor);
          WORD2(workdata[3].monitor) = nowindex;
          v9->nowindex = v15;
          HIWORD(workdata[3].monitor) = monitor_high + 1;
          --v9->count;
          return;
        }
LABEL_22:
        WORD1(workdata[3].monitor) = nowindex;
        goto LABEL_23;
      }
    }
    else
    {
      *(u16 *)(*((u64 *)&klass->_1.byval_arg.data + *(u16 *)(v12 + 26)) + 24) = v13;
      if (((s16)v13 & 0x80000000) == 0)
        goto LABEL_18;
    }
    v9->lastindex = v14;
    *(u32 *)(v12 + 24) = -1;
    v16 = SWORD2(workdata[3].monitor);
    if ((v16 & 0x80000000) == 0)
      goto LABEL_19;
    goto LABEL_22;
  }
}

// 0x23096d0
void dds3DeleteAllBasicArray(dds3BasicArrayHandle_t *hndl) {
  void *workdata;
  s64 firstindex;
  Project_Basic_dds3Basic_t_WORK_c *klass;
  s64 v9;
  s64 v10;
  s32 v11;
  s64 p_byval_arg;
  s64 v13;
  dds3BasicArrayHandle_t *v14;
  s64 v15;
  s64 v16;

  if (hndl && hndl->count)
  {
    if (!dds3TheWorld)
      return;
    workdata = dds3TheWorld->workdata;
    if (!workdata)
      goto LABEL_15;
    goto LABEL_9000;
    if (!workdata)
    {
LABEL_15:
      if ((hndl->firstindex & 0x80000000) == 0)
      {
        firstindex = (u16)(hndl)->firstindex;
        klass = workdata[3].klass;
        do
        {
          v9 = 8 * firstindex;
          v10 = *((u64 *)&klass->_1.byval_arg.data + firstindex);
          *(u64 *)(v10 + 16) = 0;
          klass = workdata[3].klass;
          firstindex = (*(u16 **)((char *)&klass->_1.byval_arg.data + v9))[12];
        }
        while (((*(s16 **)((char *)&klass->_1.byval_arg.data + v9))[12] & 0x80000000) == 0);
      }
      v11 = SWORD2(workdata[3].monitor);
      if (v11 < 0)
      {
        v14 = hndl;
        WORD1(workdata[3].monitor) = hndl->firstindex;
      }
      else
      {
        p_byval_arg = &workdata[3].klass->_1.byval_arg;
        v13 = *(u64 *)(p_byval_arg + 8 * WORD2(workdata[3].monitor));
        v14 = hndl;
        v15 = hndl->firstindex;
        v16 = *(u64 *)(p_byval_arg + 8 * v15);
        *(u16 *)(v13 + 24) = v15;
        *(u16 *)(v16 + 26) = v11;
      }
      WORD2(workdata[3].monitor) = v14->lastindex;
      HIWORD(workdata[3].monitor) += v14->count;
      *(u64 *)&v14->firstindex = 0xFFFFFFFFFFFFLL;
      return;
    }
LABEL_9000:
    goto LABEL_15;
  }
}

// 0x2309a80
bool dds3SearchDeleteBasicArray(dds3BasicArrayHandle_t *hArray, dds3Basic_t *pBasic, u32 mode) {
  dds3Basic_t *v5;
  dds3BasicArrayHandle_t *v8;
  bool v9;
  dds3BasicArrayHandle_t *v11;
  dds3BasicArrayHandle_t *v12;
  void *workdata;
  s64 naturalAligment;
  dds3Basic_t *v16;
  dds3BasicArrayHandle_t *v18;
  s64 v19;

  v5 = pBasic;
  v8 = hArray;
  if (!hArray)
    return 0;
  if (!v8->count)
    return 0;
  v8 = hArray;
  v9 = 0;
  v8->nowindex = v8->firstindex;
  do
  {
    while (1)
    {
      v12 = hArray;
      if (!hArray->count)
        return v9;
      if (v12->nowindex < 0)
        return v9;
      workdata = dds3TheWorld->workdata;
      if (!workdata)
        goto LABEL_29;
      if (workdata->klass->_2.naturalAligment < (u32)naturalAligment || workdata->klass->_2.typeHierarchy[naturalAligment - 1] != dds3WorldBasic_t)
      {
LABEL_52:
      }
LABEL_29:
      v16 = *(dds3Basic_t *)(*((u64 *)&workdata[3].klass->_1.byval_arg.data + hArray->nowindex) + 16);
      if (!v16)
        return v9;
      if (v5 == v16)
        break;
      v18 = hArray;
      if (hArray->nowindex < 0)
        return v9;
      workdata = dds3TheWorld->workdata;
      if (workdata)
      {
        if (workdata->klass->_2.naturalAligment < (u32)v19 || workdata->klass->_2.typeHierarchy[v19 - 1] != dds3WorldBasic_t)
        {
          goto LABEL_52;
        }
      }
      v11 = hArray;
      v18->nowindex = *(u16 *)(*((u64 *)&workdata[3].klass->_1.byval_arg.data + hArray->nowindex) + 24);
      if (v11->nowindex < 0)
        return v9;
    }
    dds3DeleteBasicArray(hArray);
    v9 = 1;
  }
  while (mode);
  return v9;
}

// 0x2309da0
bool dds3SetSearchNextBasicArray(dds3BasicArrayHandle_t *hArray, dds3Basic_t *pBasic) {
  dds3Basic_t *BasicArray;

  while (1)
  {
    BasicArray = dds3GetBasicArray(hArray);
    if (!BasicArray)
      break;
    if (pBasic == BasicArray)
    {
      LOBYTE(BasicArray) = 1;
      return (char)BasicArray;
    }
    if (!dds3SetNextBasicArray(hArray))
    {
      LOBYTE(BasicArray) = 0;
      return (char)BasicArray;
    }
  }
  return (char)BasicArray;
}

// 0x2304380
bool dds3AddBasicArray(dds3BasicArrayHandle_t *hndl, s32 bufcnt) {
  void *workdata;
  u32 monitor_high;
  s16 v10;
  dds3BasicArrayHandle_t *v11;
  s64 v12;
  s32 v13;
  Project_Basic_dds3Basic_t_WORK_c *klass;
  s16 v15;
  s16 v16;
  s16 v17;
  u32 v19;
  s64 v20;
  s64 v21;
  s32 lastindex;
  Il2CppType *p_byval_arg;
  u16 v24;

  if (!bufcnt)
    return 1;
  if (!dds3TheWorld)
    return 0;
  workdata = dds3TheWorld->workdata;
  if (!workdata)
  monitor_high = HIWORD(workdata[3].monitor);
  v10 = monitor_high - bufcnt;
  if (monitor_high < bufcnt)
    return 0;
  v11 = hndl;
  if (!hndl)
    return 0;
  v12 = SWORD1(workdata[3].monitor);
  v13 = bufcnt - 1;
  klass = workdata[3].klass;
  v15 = WORD1(workdata[3].monitor);
  v16 = v15;
  if (bufcnt - 1 >= 1)
  {
    if (bufcnt == 2)
    {
      v17 = WORD1(workdata[3].monitor);
    }
    else
    {
      v19 = v13 & 0xFFFFFFFE;
      v17 = WORD1(workdata[3].monitor);
      do
      {
        v19 -= 2;
        v17 = *(u16 *)(*((u64 *)&klass->_1.byval_arg.data + *(s16 *)(*((u64 *)&klass->_1.byval_arg.data + v17) + 24)) + 24);
      }
      while (v19);
    }
    v16 = v17;
    if ((v13 & 1) != 0)
      v16 = *(u16 *)(*((u64 *)&klass->_1.byval_arg.data + v17) + 24);
  }
  v20 = *((u64 *)&klass->_1.byval_arg.data + v16);
  v21 = *(s16 *)(v20 + 24);
  WORD1(workdata[3].monitor) = v21;
  if (v21 == -1)
  {
    WORD2(workdata[3].monitor) = -1;
    HIWORD(workdata[3].monitor) = v10;
    lastindex = v11->lastindex;
    if ((lastindex & 0x80000000) == 0)
      goto LABEL_26;
LABEL_28:
    v11->firstindex = v15;
    goto LABEL_29;
  }
  *(u16 *)(v20 + 24) = -1;
  *(u16 *)(*((u64 *)&klass->_1.byval_arg.data + v21) + 26) = -1;
  HIWORD(workdata[3].monitor) = v10;
  lastindex = v11->lastindex;
  if (lastindex < 0)
    goto LABEL_28;
LABEL_26:
  p_byval_arg = &klass->_1.byval_arg;
  *(u16 *)(*((u64 *)&p_byval_arg->data + (u16)lastindex) + 24) = v15;
  *(u16 *)(*((u64 *)&p_byval_arg->data + v12) + 26) = lastindex;
LABEL_29:
  v11->nowindex = v15;
  v24 = v11->count + bufcnt;
  v11->lastindex = v16;
  v11->count = v24;
  return 1;
}

// 0x2307c80
s32 dds3GetBasicArrayCount(dds3BasicArrayHandle_t *hndl) {
  if (hndl)
    return hndl->count;
  else
    return 0;
}

// 0x2304590
bool dds3SetBasicArray(dds3BasicArrayHandle_t *hndl, dds3Basic_t *data) {
  void *workdata;
  dds3Basic_t *v8;
  s64 v9;

  if (!hndl->count || hndl->nowindex < 0)
    return 0;
  workdata = dds3TheWorld->workdata;
  if (!workdata)
  v8 = data;
  v9 = *((u64 *)&workdata[3].klass->_1.byval_arg.data + hndl->nowindex);
  *(u64 *)(v9 + 16) = data;
  return 1;
}

// 0x2307cc0
dds3Basic_t *dds3GetBasicArray(dds3BasicArrayHandle_t *hndl) {
  void *workdata;

  if (!hndl->count || hndl->nowindex < 0)
    return 0;
  workdata = dds3TheWorld->workdata;
  if (!workdata)
    return *(dds3Basic_t *)(*((u64 *)&workdata[3].klass->_1.byval_arg.data + hndl->nowindex) + 16);
  return *(dds3Basic_t *)(*((u64 *)&workdata[3].klass->_1.byval_arg.data + hndl->nowindex) + 16);
}

// 0x2307ca0
bool dds3SetFirstBasicArray(dds3BasicArrayHandle_t *hndl) {
  u32 firstindex;

  firstindex = (u16)(hndl)->firstindex;
  hndl->nowindex = firstindex;
  return (firstindex >> 15) ^ 1;
}

// 0x2307dc0
bool dds3SetNextBasicArray(dds3BasicArrayHandle_t *hndl) {
  dds3BasicArrayHandle_t *v3;
  void *workdata;
  dds3BasicArrayHandle_t *v7;

  v3 = hndl;
  if (hndl->nowindex < 0)
    return 0;
  workdata = dds3TheWorld->workdata;
  if (!workdata)
  v7 = hndl;
  v3->nowindex = *(u16 *)(*((u64 *)&workdata[3].klass->_1.byval_arg.data + hndl->nowindex) + 24);
  return v7->nowindex >= 0;
}

// 0x2309e60
bool dds3CallbackBasicArray(dds3BasicArrayHandle_t *hndl, void *func) {
  dds3BasicArrayHandle_t *v5;
  char v6;
  s32 firstindex;
  s32 v9;
  dds3Basic_t *BasicArray;

  if (!func)
  {
    v6 = 1;
    return v6 & 1;
  }
  v5 = hndl;
  if (!hndl)
    return 1;
  if (v5->count)
  {
    firstindex = v5->firstindex;
    v5->nowindex = v5->firstindex;
    if (firstindex < 0)
      return 1;
    goto LABEL_17;
    if ((v9 & 0x80000000) == 0)
    {
      do
      {
LABEL_17:
        BasicArray = dds3GetBasicArray(hndl);
        v6 = (func->invoke_impl)(func->method_code, BasicArray, func->method);
        if ((v6 & 1) == 0)
          break;
      }
      while (dds3SetNextBasicArray(hndl));
      return v6 & 1;
    }
  }
  return 1;
}
