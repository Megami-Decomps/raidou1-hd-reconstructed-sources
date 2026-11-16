#include "types.h"
#include "dds3kernelcore.h"
#include "dds3padmanager.h"
#include "kernel.h"
#include "sdfmem.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;

static dds3ProcessID_t *startinglistf;
static dds3ProcessID_t *startinglistl;
static s32 startinglistcnt;
static dds3ProcessID_t *endinglistf;
static dds3ProcessID_t *endinglistl;
static s32 endinglistcnt;
static dds3ProcessID_t *runninglistf;
static dds3ProcessID_t *runninglistl;
static s32 runninglistcnt;
static dds3ProcessID_t *runprocess;
static s32 uua_count;
static s32 un_scene_max;

static void _EndProcess(dds3ProcessID_t *setp);
static void DeleteProcessList(dds3ProcessID_t *setp);
static void AddProcessList(dds3ProcessID_t *setp);
static void _StartProcess(dds3ProcessID_t *setp);
static void StartingProcess(void);
static bool RunProcess(dds3ProcessID_t *pro);
static void RunningProcess(void);
static void _KillProcess(dds3ProcessID_t *setp);
static void EndingProcess(void);
static void ChangeProcessFlagChild(bool change, dds3ProcessID_t *parent, u32 flag);
static void ChangeProcessFlag(bool change, dds3ProcessID_t *target, u32 flag, s32 type);
static void SetShutdownTimer(dds3ProcessID_t *id, s32 newtimer);
static u32 GetProcessStartTime(dds3ProcessID_t *id);
static void UnlinkProcess(dds3ProcessID_t *target);
static void UnloadExec(void);

// 0x22847a0
void Init(void) {
  struct dds3KernelCore *v3;
  struct dds3KernelCore *v5;
  struct dds3KernelCore *v7;

  startinglistf = 0;
  startinglistl = 0;
  endinglistf = 0;
  v3 = ((char *)v3 + 24);
  LODWORD(v3[-1].unSceneOp) = 0;
  endinglistl = 0;
  runninglistf = 0;
  v5 = ((char *)v5 + 48);
  LODWORD(v5[-1].unSceneOp) = 0;
  runninglistl = 0;
  runprocess = 0;
  v7 = ((char *)v7 + 72);
  LODWORD(v7[-1].unSceneOp) = 0;
}

// 0x2284890
static void _EndProcess(dds3ProcessID_t *setp) {
  if ((setp->flag & 0xF) - 1 <= 1)
  {
    DeleteProcessList(setp);
    setp->flag = setp->flag & 0xFFFFFFF0 | 3;
    AddProcessList(setp);
    if (!setp->shutdowntimer)
    {
      _KillProcess(setp);
    }
  }
}

// 0x2284950
static void DeleteProcessList(dds3ProcessID_t *setp) {
  u32 v3;
  dds3ProcessID_t *prev;
  dds3ProcessID_t *p_prev;
  dds3ProcessID_t *next;
  struct dds3KernelCore *p_next;
  dds3ProcessID_t *v8;
  dds3ProcessID_t *v14;
  dds3ProcessID_t *v15;
  dds3ProcessID_t *p_endinglistl;
  u32 v17;
  dds3ProcessID_t *v18;
  u32 v25;
  s32 *p_endinglistcnt;

  v3 = setp->flag & 0xF;
  if (v3 - 1 > 2)
    return;
  p_prev = &setp->prev;
  prev = setp->prev;
  if (prev)
  {
    next = setp->next;
    prev->next = next;
    p_next = &prev->next;
  }
  else
  {
    switch (v3)
    {
      case 3u:
        v8 = setp->next;
        endinglistf = v8;
        p_next = &endinglistf;
        break;
      case 2u:
        v8 = setp->next;
        runninglistf = v8;
        p_next = &runninglistf;
        break;
      case 1u:
        v8 = setp->next;
        startinglistf = v8;
        break;
      default:
        goto LABEL_20;
    }
    next = v8;
  }
LABEL_20:
  v14 = setp->next;
  if (v14)
  {
    v15 = p_prev;
    v14->prev = p_prev;
    p_endinglistl = &v14->prev;
LABEL_35:
    goto LABEL_36;
  }
  v17 = setp->flag & 0xF;
  switch (v17)
  {
    case 3u:
      v18 = p_prev;
      endinglistl = v18;
      p_endinglistl = &endinglistl;
      goto LABEL_34;
    case 2u:
      v18 = p_prev;
      runninglistl = v18;
      p_endinglistl = &runninglistl;
      goto LABEL_34;
    case 1u:
      v18 = p_prev;
      startinglistl = v18;
      p_endinglistl = &startinglistl;
LABEL_34:
      v15 = v18;
      goto LABEL_35;
  }
LABEL_36:
  setp->next = 0;
  setp->prev = 0;
  v25 = setp->flag & 0xF;
  switch (v25)
  {
    case 3u:
      p_endinglistcnt = &endinglistcnt;
      break;
    case 2u:
      p_endinglistcnt = &runninglistcnt;
      break;
    case 1u:
      p_endinglistcnt = &startinglistcnt;
      break;
    default:
      return;
  }
  --*p_endinglistcnt;
}

// 0x2284bf0
static void AddProcessList(dds3ProcessID_t *setp) {
  u32 v3;
  dds3ProcessID_t *endinglistf_local;
  u32 v6;
  dds3ProcessID_t *startinglistl_local;
  dds3ProcessID_t *v8;
  dds3ProcessID_t *p_endinglistl;
  u32 v10;
  dds3ProcessID_t *p_runninglistl;
  dds3ProcessID_t *prev;
  dds3ProcessID_t *v13;
  dds3ProcessID_t *p_prev;
  u32 v15;
  struct dds3KernelCore *p_endinglistf;
  dds3ProcessID_t *v19;
  dds3ProcessID_t *endinglistl_local;
  dds3ProcessID_t *v21;
  dds3ProcessID_t *runninglistl_local;
  dds3ProcessID_t *v23;
  u32 v24;
  s32 *p_endinglistcnt;

  v3 = setp->flag & 0xF;
  switch (v3)
  {
    case 3u:
      endinglistf_local = endinglistf;
      if (!endinglistf_local)
        break;
LABEL_13:
      while (endinglistf_local->priority <= setp->priority)
      {
        endinglistf_local = endinglistf_local->next;
        if (!endinglistf_local)
        {
          v6 = setp->flag & 0xF;
          switch (v6)
          {
            case 3u:
              endinglistl_local = endinglistl;
              endinglistl_local->next = setp;
              v21 = endinglistl;
              setp->prev = v21;
              p_endinglistl = &endinglistl;
              break;
            case 2u:
              runninglistl_local = runninglistl;
              runninglistl_local->next = setp;
              v23 = runninglistl;
              setp->prev = v23;
              p_endinglistl = &runninglistl;
              break;
            case 1u:
              startinglistl_local = startinglistl;
              startinglistl_local->next = setp;
              v8 = startinglistl;
              setp->prev = v8;
              p_endinglistl = &startinglistl;
              break;
            default:
              goto LABEL_55;
          }
          v19 = setp;
          p_endinglistl = setp;
          goto LABEL_54;
        }
      }
      prev = endinglistf_local->prev;
      if (prev)
      {
        prev->next = setp;
        v13 = endinglistf_local->prev;
        setp->prev = v13;
        p_prev = &setp->prev;
        goto LABEL_72;
      }
      v15 = setp->flag & 0xF;
      switch (v15)
      {
        case 3u:
          endinglistf = setp;
          p_endinglistf = &endinglistf;
          break;
        case 2u:
          runninglistf = setp;
          p_endinglistf = &runninglistf;
          break;
        case 1u:
          startinglistf = setp;
          break;
        default:
LABEL_71:
          v13 = 0;
          setp->prev = 0;
          p_prev = &setp->prev;
LABEL_72:
          setp->next = endinglistf_local;
          endinglistf_local->prev = setp;
          v24 = setp->flag & 0xF;
          if (v24 != 3)
            goto LABEL_56;
LABEL_73:
          p_endinglistcnt = &endinglistcnt;
          goto LABEL_76;
      }
      goto LABEL_71;
    case 2u:
      endinglistf_local = runninglistf;
      if (endinglistf_local)
        goto LABEL_13;
      break;
    case 1u:
      endinglistf_local = startinglistf;
      if (endinglistf_local)
        goto LABEL_13;
      break;
    default:
      return;
  }
  v10 = setp->flag & 0xF;
  switch (v10)
  {
    case 3u:
      endinglistf = setp;
      p_runninglistl = &endinglistl;
      goto LABEL_45;
    case 2u:
      runninglistf = setp;
      p_runninglistl = &runninglistl;
      goto LABEL_45;
    case 1u:
      startinglistf = setp;
      p_runninglistl = &startinglistl;
LABEL_45:
      p_runninglistl = setp;
      break;
  }
  v19 = 0;
  setp->prev = 0;
  p_endinglistl = &setp->prev;
LABEL_54:
LABEL_55:
  setp->next = 0;
  v24 = setp->flag & 0xF;
  if (v24 == 3)
    goto LABEL_73;
LABEL_56:
  if (v24 == 2)
  {
    p_endinglistcnt = &runninglistcnt;
  }
  else
  {
    if (v24 != 1)
      return;
    p_endinglistcnt = &startinglistcnt;
  }
LABEL_76:
  ++*p_endinglistcnt;
}

// 0x2285260
static void _StartProcess(dds3ProcessID_t *setp) {
  DeleteProcessList(setp);
  setp->flag = setp->flag & 0xFFFFFFF0 | 2;
  AddProcessList(setp);
  setp->starttime = 0;
  setp->runtime = 0;
}

// 0x22852e0
static void StartingProcess(void) {
  dds3ProcessID_t *startinglistf_local;
  s32 starttimer;
  s32 v6;
  dds3ProcessID_t *next;

  goto LABEL_3;
  while (1)
  {
LABEL_12:
    starttimer = startinglistf_local->starttimer;
    v6 = starttimer - 1;
    if (starttimer >= 1)
    {
      --starttimer;
      startinglistf_local->starttimer = v6;
    }
    next = startinglistf_local->next;
    if (!starttimer)
    {
      DeleteProcessList(startinglistf_local);
      startinglistf_local->flag = startinglistf_local->flag & 0xFFFFFFF0 | 2;
      AddProcessList(startinglistf_local);
      startinglistf_local->starttime = 0;
      startinglistf_local->runtime = 0;
    }
    startinglistf_local = next;
    if (!next)
      return;
  }
LABEL_3:
  startinglistf_local = startinglistf;
  if (startinglistf_local)
    goto LABEL_12;
}

// 0x2285410
void PadEi(void) {
  s64 v3;
  SDF_PAD **v7;
  SDF_PAD **v8;
  SDF_PAD *v9;
  u8 *v10;
  u8 *v13;
  s64 v14;
  SDF_PAD ***v17;
  SDF_PAD **v18;
  SDF_PAD **v19;
  SDF_PAD *v20;
  u8 *v21;
  u8 *v24;

  v3 = 32;
  do
  {
    v8 = PadMap[0];
    v7 = PadMap[1];
    v9 = PrivatePadMap[1][0];
    *(u32 *)((char *)&v8[0]->obj.klass + v3) = *(u32 *)((char *)&PrivatePadMap[0][0]->obj.klass + v3);
    *(u32 *)((char *)&v7[0]->obj.klass + v3) = *(u32 *)((char *)&v9->obj.klass + v3);
    v3 += 4;
  }
  while (v3 != 128);
  v10 = PadAnalog[0][0];
  v10[0] = PrivatePadAnalog[0][0][0];
  PadAnalog[0][0][1] = PrivatePadAnalog[0][0][1];
  PadAnalogMap[0][0] = PrivatePadAnalogMap[0][0];
  v13 = PadAnalog[0][1];
  v13[0] = PrivatePadAnalog[0][1][0];
  v14 = 32;
  PadAnalog[0][1][1] = PrivatePadAnalog[0][1][1];
  PadAnalogMap[0][1] = PrivatePadAnalogMap[0][1];
  do
  {
    v17 = PadMap;
    v19 = v17[0];
    v18 = v17[1];
    v20 = PrivatePadMap[1][1];
    *(u32 *)((char *)&v19[1]->obj.klass + v14) = *(u32 *)((char *)&PrivatePadMap[0][1]->obj.klass + v14);
    *(u32 *)((char *)&v18[1]->obj.klass + v14) = *(u32 *)((char *)&v20->obj.klass + v14);
    v14 += 4;
  }
  while (v14 != 128);
  v21 = PadAnalog[1][0];
  v21[0] = PrivatePadAnalog[1][0][0];
  PadAnalog[1][0][1] = PrivatePadAnalog[1][0][1];
  PadAnalogMap[1][0] = PrivatePadAnalogMap[1][0];
  v24 = PadAnalog[1][1];
  v24[0] = PrivatePadAnalog[1][1][0];
  PadAnalog[1][1][1] = PrivatePadAnalog[1][1][1];
  PadAnalogMap[1][1] = PrivatePadAnalogMap[1][1];
}

// 0x2285760
static bool RunProcess(dds3ProcessID_t *pro) {
  dds3ProcessFunc_t *p_processfunc;
  void *processfunc;
  bool v9;
  s64 v10;
  SDF_PAD *v13;
  SDF_PAD *v14;
  s64 v17;
  SDF_PAD ***v18;
  SDF_PAD *v19;
  SDF_PAD *v20;
  dds3ProcessFunc_t v23;
  void *v25;
  dds3ProcessFunc_t v26;

  if ((pro->flag & 0x20) == 0)
  {
    runprocess = pro;
    if ((pro->flag & 0x10) == 0)
    {
      PadEi();
      p_processfunc = &pro->processfunc;
      processfunc = pro->processfunc;
      if (!processfunc)
        goto LABEL_43;
      goto LABEL_35;
    }
    v10 = 32;
    do
    {
      v13 = PadMap[0][0];
      v14 = PadMap[1][0];
      *(u32 *)((char *)&v13->obj.klass + v10) = 0;
      *(u32 *)((char *)&v14->obj.klass + v10) = 0;
      v10 += 4;
    }
    while (v10 != 128);
    PadAnalog[0][0][0] = 0;
    PadAnalog[0][0][1] = 0;
    PadAnalogMap[0][0] = 0;
    PadAnalog[0][1][0] = 0;
    PadAnalog[0][1][1] = 0;
    v17 = 32;
    PadAnalogMap[0][1] = 0;
    do
    {
      v18 = PadMap;
      v19 = v18[0][1];
      v20 = v18[1][1];
      *(u32 *)((char *)&v19->obj.klass + v17) = 0;
      *(u32 *)((char *)&v20->obj.klass + v17) = 0;
      v17 += 4;
    }
    while (v17 != 128);
    PadAnalog[1][0][0] = 0;
    PadAnalog[1][0][1] = 0;
    PadAnalogMap[1][0] = 0;
    PadAnalog[1][1][0] = 0;
    PadAnalog[1][1][1] = 0;
    PadAnalogMap[1][1] = 0;
    p_processfunc = &pro->processfunc;
    processfunc = pro->processfunc;
    if (!processfunc)
      goto LABEL_43;
LABEL_35:
    v23 = Allocate(dds3ProcessFunc_t);
    _ctor(v23, 0);
    if (op_Inequality(processfunc, v23, 0))
    {
      v25 = (pro->processfunc->invoke_impl)(pro->processfunc->method_code, pro, pro->processfunc->method);
      if (v25)
      {
        *p_processfunc = (dds3ProcessFunc_t)v25;
      }
      v26 = Allocate(dds3ProcessFunc_t);
      _ctor(v26, 0);
      if (op_Equality(v25, v26, 0) && (pro->flag & 0xF) == 2)
      {
        _EndProcess(pro);
        v9 = 0;
        goto LABEL_46;
      }
    }
LABEL_43:
    ++pro->runtime;
    v9 = 1;
LABEL_46:
    runprocess = 0;
    return v9;
  }
  return 1;
}

// 0x2285b40
static void RunningProcess(void) {
  dds3ProcessID_t *runninglistf_local;
  dds3ProcessID_t *endinglistf_local;
  dds3ProcessID_t *p_next;
  dds3ProcessID_t *prev;
  dds3ProcessID_t *v11;
  dds3ProcessID_t *p_runninglistf;
  dds3ProcessID_t *v14;
  dds3ProcessID_t *p_endinglistf;
  dds3ProcessID_t *v19;

  runninglistf_local = runninglistf;
  endinglistf_local = endinglistf;
  if (runninglistf_local)
  {
    if (!endinglistf_local)
      goto LABEL_33;
    while (1)
    {
      while (1)
      {
        if (runninglistf_local->priority > endinglistf_local->priority)
          break;
        prev = runninglistf_local->prev;
        if (!RunProcess(runninglistf_local))
        {
          if (prev)
          {
            p_next = &prev->next;
          }
          else
          {
            p_next = &runninglistf;
          }
          goto LABEL_7;
        }
        p_next = &runninglistf_local->next;
LABEL_7:
        runninglistf_local = p_next;
        if (!p_next)
          goto LABEL_48;
      }
      v11 = endinglistf_local->prev;
      if (RunProcess(endinglistf_local))
      {
LABEL_20:
        endinglistf_local = endinglistf_local->next;
        if (!endinglistf_local)
          goto LABEL_33;
      }
      else
      {
LABEL_23:
        if (v11)
        {
          endinglistf_local = v11->next;
          if (!endinglistf_local)
            goto LABEL_33;
        }
        {
          endinglistf_local = endinglistf;
          if (!endinglistf_local)
            goto LABEL_33;
        }
        else
        {
          endinglistf_local = endinglistf;
          if (!endinglistf_local)
          {
            while (1)
            {
LABEL_33:
              v14 = runninglistf_local->prev;
              if (!RunProcess(runninglistf_local))
              {
                if (v14)
                {
                  p_runninglistf = &v14->next;
                }
                else
                {
                  p_runninglistf = &runninglistf;
                }
                goto LABEL_32;
              }
              p_runninglistf = &runninglistf_local->next;
LABEL_32:
              runninglistf_local = p_runninglistf;
              if (!p_runninglistf)
                return;
            }
          }
        }
      }
    }
    if (RunProcess(endinglistf_local))
      goto LABEL_20;
    goto LABEL_23;
  }
  if (endinglistf_local)
  {
    do
    {
LABEL_48:
      v19 = endinglistf_local->prev;
      if (!RunProcess(endinglistf_local))
      {
        if (v19)
        {
          p_endinglistf = &v19->next;
        }
        else
        {
          p_endinglistf = &endinglistf;
        }
        goto LABEL_47;
      }
      p_endinglistf = &endinglistf_local->next;
LABEL_47:
      endinglistf_local = p_endinglistf;
    }
    while (p_endinglistf);
  }
}

// 0x2285100
static void _KillProcess(dds3ProcessID_t *setp) {
  dds3ProcessID_t *child;
  shutdownfuncDelegate shutdownfunc;
  dds3ProcessID_t *parent;
  dds3ProcessID_t *p_parent;
  dds3ProcessID_t *v9;
  dds3ProcessID_t *p_child;
  dds3ProcessID_t *v11;
  dds3ProcessID_t *v12;
  dds3ProcessID_t *sibling;
  dds3ProcessID_t *p_sibling;
  dds3ProcessID_t *id;

  child = setp->child;
  while (1)
  {
    id = child;
    if (!child)
      break;
    child = child->sibling;
    dds3KillProcess(id, 0);
  }
  DeleteProcessList(setp);
  shutdownfunc = setp->shutdownfunc;
  if (shutdownfunc)
    (shutdownfunc->invoke_impl)(shutdownfunc->method_code, setp, shutdownfunc->method);
  setp->flag &= 0xFFFFFFF0;
  p_parent = &setp->parent;
  parent = setp->parent;
  if (parent)
  {
    v11 = parent->child;
    p_child = &parent->child;
    v9 = v11;
    if (v11 == setp)
    {
      sibling = setp->sibling;
      p_sibling = p_child;
      p_child = sibling;
    }
    else
    {
      if (!v9)
      {
LABEL_24:
        setp->parent = 0;
        setp->sibling = 0;
        return;
      }
      while (1)
      {
        v12 = v9->sibling;
        if (v12 == setp)
          break;
        v9 = v9->sibling;
        if (!v12)
          goto LABEL_24;
      }
      sibling = setp->sibling;
      v9->sibling = sibling;
      p_sibling = &v9->sibling;
    }
    goto LABEL_24;
  }
}

// 0x2285f60
static void EndingProcess(void) {
  dds3ProcessID_t *endinglistf_local;
  s32 shutdowntimer;
  s32 v5;
  dds3ProcessID_t *next;

  endinglistf_local = endinglistf;
  if (!endinglistf_local)
    return;
  do
  {
    shutdowntimer = endinglistf_local->shutdowntimer;
    v5 = shutdowntimer - 1;
    if (shutdowntimer >= 1)
    {
      --shutdowntimer;
      endinglistf_local->shutdowntimer = v5;
    }
    next = endinglistf_local->next;
    if (!shutdowntimer)
    {
      _KillProcess(endinglistf_local);
    }
    endinglistf_local = next;
  }
  while (next);
}

// 0x2286030
static void ChangeProcessFlagChild(bool change, dds3ProcessID_t *parent, u32 flag) {
  dds3ProcessID_t *v7;
  u32 v8;
  dds3ProcessID_t *child;
  u32 v10;
  u32 v11;
  dds3ProcessID_t *parenta;

  v7 = parent;
  v8 = parent->flag;
  child = parent->child;
  v10 = v8 | flag & 0xFFFFFF0;
  v11 = v8 & ~(flag & 0xFFFFFF0);
  parenta = child;
  if (change)
    v11 = v10;
  for (v7->flag = v11; child; parenta = child)
  {
    ChangeProcessFlagChild(change, parenta, flag);
    child = child->sibling;
  }
}

// 0x2286100
static void ChangeProcessFlag(bool change, dds3ProcessID_t *target, u32 flag, s32 type) {
  u32 v9;
  dds3ProcessID_t *startinglistf_local;
  dds3ProcessID_t *v13;
  u32 v14;
  u32 v15;
  s32 v16;
  dds3ProcessID_t *i;
  dds3ProcessID_t *j;
  dds3ProcessID_t *k;
  dds3ProcessID_t *next;
  dds3ProcessID_t *v23;
  dds3ProcessID_t *v24;
  dds3ProcessID_t *runninglistf_local;
  dds3ProcessID_t *v27;
  dds3ProcessID_t *endinglistf_local;
  dds3ProcessID_t *v30;
  dds3ProcessID_t *m;
  dds3ProcessID_t *n;
  dds3ProcessID_t *ii;
  dds3ProcessID_t *v37;
  dds3ProcessID_t *v38;
  dds3ProcessID_t *v40;
  dds3ProcessID_t *v41;

  switch (type)
  {
    case 0:
      v13 = target;
      v14 = flag & 0xFFFFFF0;
      v15 = target->flag;
      if (change)
        v13->flag = v15 | v14;
      else
        v13->flag = v15 & ~v14;
      break;
    case 1:
    case 3:
      v9 = flag & 0xFFFFFF0;
      if (change)
      {
        startinglistf_local = startinglistf;
        if (startinglistf_local)
        {
          if (type == 3)
          {
            do
            {
              startinglistf_local->flag |= v9;
              startinglistf_local = startinglistf_local->next;
            }
            while (startinglistf_local);
          }
          else if (type == 1)
          {
            v24 = target;
            do
            {
              if (startinglistf_local != v24)
                startinglistf_local->flag |= v9;
              startinglistf_local = startinglistf_local->next;
            }
            while (startinglistf_local);
          }
          else
          {
            do
              startinglistf_local = startinglistf_local->next;
            while (startinglistf_local);
          }
        }
        runninglistf_local = runninglistf;
        if (runninglistf_local)
        {
          if (type == 3)
          {
            do
            {
              runninglistf_local->flag |= v9;
              runninglistf_local = runninglistf_local->next;
            }
            while (runninglistf_local);
          }
          else if (type == 1)
          {
            v27 = target;
            do
            {
              if (runninglistf_local != v27)
                runninglistf_local->flag |= v9;
              runninglistf_local = runninglistf_local->next;
            }
            while (runninglistf_local);
          }
          else
          {
            do
              runninglistf_local = runninglistf_local->next;
            while (runninglistf_local);
          }
        }
        endinglistf_local = endinglistf;
        if (endinglistf_local)
        {
          if (type == 3)
          {
            do
            {
              endinglistf_local->flag |= v9;
              endinglistf_local = endinglistf_local->next;
            }
            while (endinglistf_local);
          }
          else if (type == 1)
          {
            v30 = target;
            do
            {
              if (endinglistf_local != v30)
                endinglistf_local->flag |= v9;
              endinglistf_local = endinglistf_local->next;
            }
            while (endinglistf_local);
          }
          else
          {
            do
              endinglistf_local = endinglistf_local->next;
            while (endinglistf_local);
          }
        }
      }
      else
      {
        v16 = ~v9;
        if (type == 3)
        {
          for (i = startinglistf; i; i = i->next)
            i->flag &= v16;
          for (j = runninglistf; j; j = j->next)
            j->flag &= v16;
          for (k = endinglistf; k; k = k->next)
            k->flag &= v16;
        }
        else if (type == 1)
        {
          next = startinglistf;
          if (next)
          {
            v23 = target;
            do
            {
              if (next != v23)
                next->flag &= v16;
              next = next->next;
            }
            while (next);
          }
          v37 = runninglistf;
          if (v37)
          {
            v38 = target;
            do
            {
              if (v37 != v38)
                v37->flag &= v16;
              v37 = v37->next;
            }
            while (v37);
          }
          v40 = endinglistf;
          if (v40)
          {
            v41 = target;
            do
            {
              if (v40 != v41)
                v40->flag &= v16;
              v40 = v40->next;
            }
            while (v40);
          }
        }
        else
        {
          for (m = startinglistf; m; m = m->next)
            ;
          for (n = runninglistf; n; n = n->next)
            ;
          for (ii = endinglistf; ii; ii = ii->next)
            ;
        }
      }
      break;
    case 2:
      ChangeProcessFlagChild(change, target, flag);
      break;
    default:
      return;
  }
}

// 0x2286590
s32 dds3GetProcessCount(u32 type) {
  char v2;
  s32 v3;

  v2 = type;
  v3 = v2 & 0xF;
  switch (v3)
  {
    case 3:
      return endinglistcnt;
    case 2:
      return runninglistcnt;
    case 1:
      return startinglistcnt;
    default:
      return 0;
  }
}

// 0x2286680
dds3ProcessID_t *dds3SearchProcessNumber(u32 type, s32 n) {
  char v4;
  s32 v5;
  dds3ProcessID_t *result;
  s32 v10;

  v4 = type;
  v5 = v4 & 0xF;
  if (v5 == 3)
  {
    result = endinglistf;
    if (n < 1)
      return result;
LABEL_17:
    if (result)
    {
      v10 = 1;
      do
      {
        result = result->next;
        if (v10 >= n)
          break;
        ++v10;
      }
      while (result);
    }
    return result;
  }
  if (v5 == 2)
  {
    result = runninglistf;
    if (n < 1)
      return result;
    goto LABEL_17;
  }
  if (v5 != 1)
    return 0;
  result = startinglistf;
  if (n >= 1)
    goto LABEL_17;
  return result;
}

// 0x22867a0
bool dds3ProcessMain(void) {
  dds3ProcessID_t *endinglistf_local;
  s32 shutdowntimer;
  s32 v10;
  dds3ProcessID_t *next;

  StartingProcess();
  RunningProcess();
  endinglistf_local = *((dds3ProcessID_t *)*((MethodInfo *)dds3KernelCore + 2).virtualMethodPointer + 3);
  if (!endinglistf_local)
    goto LABEL_11;
  do
  {
    shutdowntimer = endinglistf_local->shutdowntimer;
    v10 = shutdowntimer - 1;
    if (shutdowntimer >= 1)
    {
      --shutdowntimer;
      endinglistf_local->shutdowntimer = v10;
    }
    next = endinglistf_local->next;
    if (!shutdowntimer)
    {
      _KillProcess(endinglistf_local);
    }
    endinglistf_local = next;
  }
  while (next);
LABEL_11:
  UnloadExec();
  return 1;
}

// 0x2284290
dds3ProcessID_t *dds3StartProcess(char *namestr, DDS3_PRIORITY priority, s32 starttimer, s32 shutdowntimer, dds3ProcessFunc_t processfunc, shutdownfuncDelegate shutdownfunc, void *data) {
  dds3ProcessID_t *v15;
  s32 v16;

  v15 = Allocate(dds3ProcessID_t);
  if (v15)
  {
    v15->name = namestr;
    v16 = (namestr->klass->vtable._2_GetHashCode.methodPtr)(namestr, namestr->klass->vtable._2_GetHashCode.method);
    v15->starttime = 0;
    v15->runtime = 0;
    v15->priority = priority;
    v15->nameHash = v16;
    v15->flag = 1;
    v15->id = (*(*(u64 *)v15 + 344))(v15, *(u64 *)(*(u64 *)v15 + 352));
    v15->starttimer = starttimer;
    v15->processfunc = processfunc;
    v15->shutdowntimer = shutdowntimer;
    v15->shutdownfunc = shutdownfunc;
    v15->workdata = data;
    v15->next = 0;
    v15->prev = 0;
    v15->parent = 0;
    v15->child = 0;
    v15->sibling = 0;
    AddProcessList(v15);
    if (!v15->starttimer)
    {
      DeleteProcessList(v15);
      v15->flag = v15->flag & 0xFFFFFFF0 | 2;
      AddProcessList(v15);
      v15->starttime = 0;
      v15->runtime = 0;
      return v15;
    }
  }
  return v15;
}

// 0x2286ae0
bool dds3KillProcessName(char *name, s32 shutdowntimer) {
  dds3ProcessID_t *v6;
  dds3ProcessID_t *id;

  v6 = dds3SearchProcessName(name);
  id = v6;
  if (!v6)
    return (char)v6;
  LOBYTE(v6) = dds3KillProcess(id, shutdowntimer);
  return (char)v6;
}

// 0x2285dc0
bool dds3KillProcess(dds3ProcessID_t *id, s32 shutdowntimer) {
  dds3ProcessID_t *v5;

  v5 = id;
  if (!v5)
    return 0;
  if ((v5->flag & 0xF) - 1 < 2)
  {
    v5->shutdowntimer = shutdowntimer;
    _EndProcess(v5);
    return 1;
  }
  if ((v5->flag & 0xF) != 3)
    return 0;
  v5->shutdowntimer = shutdowntimer;
  if (shutdowntimer)
    return 1;
  _KillProcess(v5);
  return 1;
}

// 0x2286bb0
void dds3EndProcess(dds3ProcessID_t *id) {
  if ((id->flag & 0xF) != 2)
    return;
  DeleteProcessList(id);
  id->flag = id->flag & 0xFFFFFFF0 | 3;
  AddProcessList(id);
}

// 0x2286c50
static void SetShutdownTimer(dds3ProcessID_t *id, s32 newtimer) {
  if ((id->flag & 0xF) - 1 <= 2)
    id->shutdowntimer = (s16)newtimer;
}

// 0x2286c80
u32 dds3GetProcessStat(dds3ProcessID_t *id) {
  if (!dds3ExistProcess(id))
    return 0;
  if ((id->flag & 0xC) != 0)
    return 0;
  else
    return id->flag & 0xF;
}

// 0x2282de0
dds3ProcessID_t *dds3SearchProcessName(char *namestr) {
  s32 v3;
  dds3ProcessID_t *startinglistf_local;

  v3 = (namestr->klass->vtable._2_GetHashCode.methodPtr)(namestr, namestr->klass->vtable._2_GetHashCode.method);
  startinglistf_local = startinglistf;
  if (startinglistf_local)
  {
    while (startinglistf_local->nameHash != v3 || !Equals_54828784(startinglistf_local->name, namestr, 0))
    {
      startinglistf_local = startinglistf_local->next;
      if (!startinglistf_local)
        goto LABEL_7;
    }
    return startinglistf_local;
  }
LABEL_7:
  startinglistf_local = runninglistf;
  if (startinglistf_local)
  {
    while (startinglistf_local->nameHash != v3 || !Equals_54828784(startinglistf_local->name, namestr, 0))
    {
      startinglistf_local = startinglistf_local->next;
      if (!startinglistf_local)
        goto LABEL_15;
    }
    return startinglistf_local;
  }
LABEL_15:
  startinglistf_local = endinglistf;
  if (!startinglistf_local)
    return startinglistf_local;
  do
  {
    if (startinglistf_local->nameHash == v3 && Equals_54828784(startinglistf_local->name, namestr, 0))
    {
      break;
    }
    startinglistf_local = startinglistf_local->next;
  }
  while (startinglistf_local);
  return startinglistf_local;
}

// 0x2286ea0
dds3ProcessID_t *dds3SearchProcessPriority(DDS3_PRIORITY priority) {
  dds3ProcessID_t *result;

  result = startinglistf;
  if (result)
  {
    while (result->priority != priority)
    {
      result = result->next;
      if (!result)
        goto LABEL_6;
    }
    return result;
  }
LABEL_6:
  result = runninglistf;
  if (result)
  {
    while (result->priority != priority)
    {
      result = result->next;
      if (!result)
        goto LABEL_10;
    }
    return result;
  }
LABEL_10:
  result = endinglistf;
  if (!result)
    return result;
  do
  {
    if (result->priority == priority)
      break;
    result = result->next;
  }
  while (result);
  return result;
}

// 0x2286d30
bool dds3ExistProcess(dds3ProcessID_t *id) {
  dds3ProcessID_t *startinglistf_local;
  dds3ProcessID_t *runninglistf_local;
  bool result;
  dds3ProcessID_t *endinglistf_local;
  dds3ProcessID_t *v8;

  startinglistf_local = startinglistf;
  if (startinglistf_local)
  {
    while (startinglistf_local != id)
    {
      startinglistf_local = startinglistf_local->next;
      if (!startinglistf_local)
        goto LABEL_9;
    }
    return 1;
  }
LABEL_9:
  runninglistf_local = runninglistf;
  if (runninglistf_local)
    goto LABEL_15;
LABEL_17:
  endinglistf_local = endinglistf;
  if (endinglistf_local)
  {
    v8 = id;
    do
    {
      result = endinglistf_local == v8;
      if (endinglistf_local == v8)
        break;
      endinglistf_local = endinglistf_local->next;
    }
    while (endinglistf_local);
    return result;
  }
  return 0;
LABEL_15:
  while (runninglistf_local != id)
  {
    runninglistf_local = runninglistf_local->next;
    if (!runninglistf_local)
      goto LABEL_17;
  }
  return 1;
}

// 0x2286fd0
static u32 GetProcessStartTime(dds3ProcessID_t *id) {
  return id->starttime;
}

// 0x2286fe0
u32 dds3GetProcessRunTime(dds3ProcessID_t *id) {
  return id->runtime;
}

// 0x2286ff0
void dds3SetProcessData(dds3ProcessID_t *id, void *data) {
  dds3ProcessID_t *v3;

  v3 = id;
  v3->workdata = data;
}

// 0x2282f60
void *dds3GetProcessData(dds3ProcessID_t *id) {
  return id->workdata;
}

// 0x2287000
void dds3LinkProcess(dds3ProcessID_t *parent, dds3ProcessID_t *target) {
  dds3ProcessID_t *v5;
  dds3ProcessID_t *v6;
  dds3ProcessID_t *p_parent;
  dds3ProcessID_t *p_child;
  dds3ProcessID_t *v9;
  dds3ProcessID_t *child;
  dds3ProcessID_t *v11;
  dds3ProcessID_t *sibling;
  dds3ProcessID_t *p_sibling;
  dds3ProcessID_t *v14;
  dds3ProcessID_t *v15;
  dds3ProcessID_t *v16;
  dds3ProcessID_t *v17;
  dds3ProcessID_t *v18;

  v5 = target;
  p_parent = &target->parent;
  v6 = p_parent;
  if (p_parent)
  {
    {
      child = v6->child;
      p_child = &v6->child;
      v9 = child;
      if (child == v5)
      {
        sibling = v5->sibling;
        p_child = sibling;
      }
      else
      {
        if (!v9)
        {
LABEL_14:
          v5->parent = 0;
          v5->sibling = 0;
          goto LABEL_15;
        }
        while (1)
        {
          v11 = v9->sibling;
          if (v11 == v5)
            break;
          v9 = v9->sibling;
          if (!v11)
            goto LABEL_14;
        }
        sibling = v5->sibling;
        v9->sibling = sibling;
        p_child = &v9->sibling;
      }
      goto LABEL_14;
    }
  }
LABEL_15:
  p_sibling = &parent->child;
  v14 = p_sibling;
  if (p_sibling)
  {
    do
    {
      v15 = v14;
      v14 = v14->sibling;
    }
    while (v14);
    v16 = target;
    v15->sibling = target;
    p_sibling = &v15->sibling;
  }
  else
  {
    v16 = target;
    p_sibling = target;
  }
  v17 = target;
  v18 = parent;
  v17->parent = parent;
}

// 0x2285ec0
static void UnlinkProcess(dds3ProcessID_t *target) {
  dds3ProcessID_t *parent;
  dds3ProcessID_t *p_parent;
  dds3ProcessID_t *v5;
  dds3ProcessID_t *p_child;
  dds3ProcessID_t *child;
  dds3ProcessID_t *v8;
  dds3ProcessID_t *sibling;
  dds3ProcessID_t *p_sibling;

  if (target)
  {
    p_parent = &target->parent;
    parent = target->parent;
    if (parent)
    {
      child = parent->child;
      p_child = &parent->child;
      v5 = child;
      if (child == target)
      {
        sibling = target->sibling;
        p_sibling = p_child;
        p_child = sibling;
      }
      else
      {
        if (!v5)
        {
LABEL_12:
          target->parent = 0;
          target->sibling = 0;
          return;
        }
        while (1)
        {
          v8 = v5->sibling;
          if (v8 == target)
            break;
          v5 = v5->sibling;
          if (!v8)
            goto LABEL_12;
        }
        sibling = target->sibling;
        v5->sibling = sibling;
        p_sibling = &v5->sibling;
      }
      goto LABEL_12;
    }
  }
}

// 0x2287120
void dds3SetProcessFlag(dds3ProcessID_t *target, u32 flag, s32 type) {
  ChangeProcessFlag(1, target, flag, type);
}

// 0x22871a0
void dds3ResetProcessFlag(dds3ProcessID_t *target, u32 flag, s32 type) {
  ChangeProcessFlag(0, target, flag, type);
}

// 0x2287220
dds3ProcessID_t *dds3SearchProcessID(s32 id) {
  dds3ProcessID_t *result;

  result = startinglistf;
  if (result)
  {
    while (result->id != id)
    {
      result = result->next;
      if (!result)
        goto LABEL_6;
    }
    return result;
  }
LABEL_6:
  result = runninglistf;
  if (result)
  {
    while (result->id != id)
    {
      result = result->next;
      if (!result)
        goto LABEL_10;
    }
    return result;
  }
LABEL_10:
  result = endinglistf;
  if (!result)
    return result;
  do
  {
    if (result->id == id)
      break;
    result = result->next;
  }
  while (result);
  return result;
}

// 0x22868d0
static void UnloadExec(void) {
  bool v4;
  s64 v6;
  s64 i;
  u64 *v8;
  void *unSceneOp_local;
  void *v10;
  bool isDone;

  v4 = uua_count != 0;
  if (uua_count)
    uua_count = 0;
  v6 = 0;
  for (i = 32; ; i += 8)
  {
    unSceneOp_local = unSceneOp;
    if (v6 >= SLODWORD(unSceneOp_local->max_length))
      break;
    v10 = *(void *)((char *)&unSceneOp_local->obj.klass + i);
    if (!v10)
      goto LABEL_12;
    isDone = get_isDone(v10, 0);
    if (!isDone)
      goto LABEL_12;
    v8 = ((char *)&unSceneOp->obj.klass + i);
    *v8 = 0;
    v4 = 1;
LABEL_12:
    ++v6;
  }
  if (v4)
  {
    sdfMemRelease();
  }
}

// 0x2287350
void dds3UnloadSceneAsync(void *mv) {
  s64 v4;
  s64 v5;
  s64 v6;
  s32 *unSceneOp_local;
  void *v9;

  v4 = 3;
  v5 = 8;
  while (1)
  {
    unSceneOp_local = unSceneOp;
    if (v4 - 3 >= unSceneOp_local[6])
      break;
    unSceneOp_local = unSceneOp;
    v6 = *(u64 *)&unSceneOp_local[v5];
    ++v4;
    v5 += 2;
    if (!v6)
    {
      v9 = UnloadSceneAsync_61083440(mv, 0);
      if (v9)
      {
        QueryInterface(v9, *(void **)(*(u64 *)unSceneOp_local + 64));
      }
      *(u64 *)&unSceneOp_local[2 * v4] = v9;
      return;
    }
  }
}

// 0x22874d0
void dds3UnloadUnusedAssets(bool req) {
  if (req)
  {
    ++uua_count;
    return;
  }
  sdfMemResourcesRelease();
}
