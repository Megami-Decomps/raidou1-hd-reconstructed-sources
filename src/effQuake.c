#include "types.h"
#include "dds3kerneldraw.h"
#include "effquake.h"

#define EFFSTAT_QUAKEMAX 32
#define EFFSTAT_QUAKEFLAG_STOP 1

typedef struct effQuakeRequest_t effQuakeRequest_t;

static effQuakeRequest_t *quake_list[32];
static s32 flags_quake;

// 0x1960c90
void effStopStat(void) {
  s64 v2;

  v2 = 32;
  flags_quake |= 1u;
  do
  {
    if ((~LOWORD((*(Il2CppClass **)((char *)&quake_list->obj.klass + v2))->_1.namespaze) & 0xD) == 0)
      dds3StopQuake();
    v2 += 8;
  }
  while (v2 != 288);
}

// 0x1960da0
void effRestoreStat(void) {
  s64 v2;
  s32 v3;
  u32 v4;
  s32 v5;
  s32 v6;
  u32 v7;
  s64 v8;
  u32 v9;

  v2 = 32;
  flags_quake &= ~1u;
  do
  {
    v8 = *(s64 *)((char *)&quake_list->obj.klass + v2);
    if ((~*(u16 *)(v8 + 24) & 0xD) != 0)
      goto LABEL_10;
    if (*(u16 *)(v8 + 26) == 1)
    {
      v3 = *(u16 *)(v8 + 28);
      v4 = *(u32 *)(v8 + 16);
      v5 = *(u32 *)(v8 + 20);
      v6 = v4 - v3;
      v7 = (v4 - v3) * v5 / v4;
      goto LABEL_9;
    }
    if (!*(u16 *)(v8 + 26))
    {
      v9 = *(u32 *)(v8 + 20);
      v6 = 0;
      v7 = v9;
LABEL_9:
      dds3SetQuake(v6, v7);
    }
LABEL_10:
    v2 += 8;
  }
  while (v2 != 288);
}

// 0x1960ef0
void effInit(void) {
  s64 v1;
  s64 v4;
  effQuakeRequest_t *quake_list_local;
  Il2CppObject *v6;

  v1 = 32;
  do
  {
    quake_list_local = quake_list;
    if (!*(Il2CppClass **)((char *)&quake_list_local->obj.klass + v1))
    {
      v6 = Allocate(effQuakeRequest_t);
      _ctor(v6, 0);
      if (!v6)
      *(Il2CppClass **)((char *)&quake_list_local->obj.klass + v1) = v6;
    }
    v4 = *(s64 *)((char *)&quake_list->obj.klass + v1);
    v1 += 8;
    *(u16 *)(v4 + 24) = 0;
  }
  while (v1 != 288);
  flags_quake = 0;
}

// 0x1961090
void effUpdate(void) {
  s64 i;
  effQuakeRequest_t *v5;
  s16 flags;
  u16 v8;

  for (i = 32; i != 288; i += 8)
  {
    v5 = *(effQuakeRequest_t *)((char *)&quake_list->obj.klass + i);
    if ((~v5->flags & 5) != 0)
      continue;
    if ((flags_quake & 1) != 0)
      continue;
    if (v5->type == 1 && v5->frame == ++v5->count)
    {
      flags = v5->flags;
      if ((flags & 8) == 0)
        goto LABEL_28;
      v8 = v5->flags;
      if ((v8 & 8) == 0)
        goto LABEL_27;
      goto LABEL_24;
      if ((v8 & 8) == 0)
      {
LABEL_27:
        flags = v8 & 0xFFF3;
LABEL_28:
        v5->flags = flags & 0xFFF3;
        if ((flags & 2) != 0)
        {
          effRemove(v5);
        }
        continue;
      }
LABEL_24:
      dds3StopQuake();
      v8 = v5->flags;
      goto LABEL_27;
    }
  }
}

// 0x19613e0
effQuakeRequest_t *effRegist(void) {
  s64 v2;
  s64 v3;
  u32 v4;
  effQuakeRequest_t *quake_list_local;
  s64 v7;
  Il2CppObject *v8;
  effQuakeRequest_t *result;

  v2 = -32;
  v3 = 4;
  v4 = 32;
  while (1)
  {
    quake_list_local = quake_list;
    v7 = *((u64 *)&quake_list_local->obj.klass + v3);
    if (!v7)
    {
      quake_list_local = quake_list;
      v8 = Allocate(effQuakeRequest_t);
      _ctor(v8, 0);
      v4 = v3 - 4;
      *((u64 *)&quake_list_local->obj.klass + v3) = v8;
LABEL_17:
      goto LABEL_19;
    }
    v7 = *((u64 *)&quake_list->obj.klass + v3);
    if ((*(u16 *)(v7 + 24) & 1) == 0)
      break;
    ++v3;
    v2 -= 8;
    if (v3 == 36)
      goto LABEL_17;
  }
  v4 = v3 - 4;
LABEL_19:
  result = quake_list[v4];
  result->flags = 1;
  return result;
}

// 0x1961550
void effStart(effQuakeRequest_t *req, u32 amp) {
  effQuakeRequest_t *v6;

  req->type = 0;
  req->amp = amp;
  v6 = req;
  effStartSignal(v6);
}

// 0x1961780
void effStartDamp(effQuakeRequest_t *req, u32 amp, u32 frame) {
  effQuakeRequest_t *v8;

  req->frame = frame;
  req->amp = amp;
  req->type = 1;
  v8 = req;
  effStartSignal(v8);
}

// 0x19615f0
void effStartSignal(effQuakeRequest_t *req) {
  s64 v4;
  u16 v5;
  effQuakeRequest_t *m_Items;
  effQuakeRequest_t *v7;
  s32 flags;
  u32 priority;
  s64 v10;
  s64 v11;
  s32 v12;
  u32 v13;
  u16 v14;
  u32 amp;
  u32 frame;

  v5 = 0;
  v10 = 32;
  while (1)
  {
    v11 = *(s64 *)((char *)&quake_list->obj.klass + v10);
    if (v11)
    {
      v12 = *(u16 *)(v11 + 24);
      if ((~v12 & 5) == 0)
      {
        v13 = *(u16 *)(v11 + 30);
        *(u16 *)(v11 + 24) = v12 & 0xFFF7;
        if (v5 <= v13)
          v5 = v13;
      }
    }
    v10 += 8;
    if (v10 == 288)
      goto LABEL_19;
  }
  v4 = 0;
  v5 = 0;
  m_Items = quake_list;
  do
  {
    v7 = m_Items[v4];
    if (v7)
    {
      flags = v7->flags;
      if ((~flags & 5) == 0)
      {
        priority = v7->priority;
        v7->flags = flags & 0xFFF7;
        if (v5 <= priority)
          v5 = priority;
      }
    }
    ++v4;
  }
  while (v4 != 32);
LABEL_19:
  v14 = req->flags;
  req->count = 0;
  req->priority = v5;
  req->flags = v14 | 0xC;
  frame = req->frame;
  amp = req->amp;
  dds3SetQuake(frame, amp);
}

// 0x1961240
void effStop(effQuakeRequest_t *req) {
  u16 flags;

  flags = req->flags;
  if ((flags & 8) == 0)
  {
    req->flags = flags & 0xFFF3;
    return;
  }
  dds3StopQuake();
  req->flags &= 0xFFF3u;
}

// 0x19612d0
void effRemove(effQuakeRequest_t *req) {
  s32 flags;
  u16 v4;

  flags = req->flags;
  if ((~flags & 0xC) != 0)
  {
    req->flags = flags & 0xFFFE;
    return;
  }
  v4 = req->flags;
  if ((v4 & 8) == 0)
  {
    req->flags = v4 & 0xFFF2;
    return;
  }
  dds3StopQuake();
  req->flags &= 0xFFF2u;
}
