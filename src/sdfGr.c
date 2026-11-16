#include "types.h"
#include "libsdf.h"
#include "sdfgr.h"

#define rqOfsAdd 2

typedef struct sdfDrawTag_t sdfDrawTag_t;
typedef struct sdfGrOt_t sdfGrOt_t;

// 0x225d750
void sdfGrOtFuncLinkToHead(sdfGrOt_t *aOt, sdfDrawTag_t *aTag) {
  sdfDrawTag_t *p_tagHead;
  sdfDrawTag_t *tagHead;

  if (aTag->tail)
  {
    p_tagHead = &aOt->tagHead;
    tagHead = aOt->tagHead;
    if (!tagHead)
    {
      aOt->tagTail = aTag;
    }
    aTag->next = tagHead;
    p_tagHead = aTag;
  }
}

// 0x225d340
void sdfGrOtNormalReg(sdfGrOt_t *aOt, sdfDrawTag_t *aTag) {
  sdfDrawTag_t *tagTail;
  sdfDrawTag_t *p_tagTail;
  sdfDrawTag_t *p_next;

  if (aTag->head)
  {
    p_tagTail = &aOt->tagTail;
    tagTail = aOt->tagTail;
    if (tagTail)
      p_next = &tagTail->next;
    else
      p_next = &aOt->tagHead;
    p_next = aTag;
    p_tagTail = aTag;
  }
}

// 0x225d410
void sdfGrOtNormalCallback(sdfGrOt_t *aOt, SDF_OT_FUNC aFunc, sdfDrawTag_t *aData) {
  sdfDrawTag_t *p_tagHead;
  sdfDrawTag_t *tagHead;

  if (aFunc == 1 && aData->tail)
  {
    p_tagHead = &aOt->tagHead;
    tagHead = aOt->tagHead;
    if (!tagHead)
    {
      aOt->tagTail = aData;
    }
    aData->next = tagHead;
    p_tagHead = aData;
  }
}

// 0x225d7c0
void sdfGrOtInit(sdfGrOt_t *aOt, s32 aNumOt) {
  s64 v4;
  sdfGrOt_t *v5;
  sdfGrOt_t *m_Items;
  s32 v7;
  sdfGrOt_t *v8;

  if (SLODWORD(aOt->max_length) >= 1)
  {
    v4 = 0;
    v5 = 0;
    m_Items = aOt;
    v7 = aNumOt - 1;
    while (1)
    {
      v8 = m_Items[v4];
      v8->tagHead = 0;
      v8->tagTail = 0;
      if (v5)
      {
        v5->next = v8;
      }
      if (v7 == (u32)v4)
        break;
      ++v4;
      v5 = v8;
      if (v4 >= SLODWORD(aOt->max_length))
        return;
    }
    v8->next = 0;
  }
}

// 0x225d880
sdfDrawTag_t *sdfGrOtClose(sdfGrOt_t *aOt) {
  void *v3;
  sdfGrOt_t *v5;
  s32 v6;
  sdfDrawTag_t *v7;
  sdfDrawTag_t *tagHead;
  sdfDrawTag_t *next;
  sdfGrPacketHeader_t *head;

  v3 = Allocate(Project_libsdf_sdfGrPacketHeader_t_Param);
  _ctor(v3);
  v5 = aOt[0];
  v3->rqOfs = 0;
  if (!v5)
    return 0;
  v6 = 0;
  v7 = 0;
  do
  {
    tagHead = v5->tagHead;
    if (tagHead)
    {
      next = v5->tagHead;
      *(u64 *)&v3->rq = (u32)(v6 + v5->renderQueue);
      head = tagHead->head;
      if (!head)
        goto LABEL_12;
LABEL_10:
      while (1)
      {
        (head->klass->vtable._4_OtClose.methodPtr)(head, v3, head->klass->vtable._4_OtClose.method);
        if (head == next->tail)
          break;
        head = head->next;
      }
LABEL_12:
      while (next != v5->tagTail)
      {
        next = next->next;
        head = next->head;
        if (head)
          goto LABEL_10;
      }
      v6 = v3->rqOfs;
      if (!v7)
        v7 = tagHead;
    }
    v5 = v5->next;
    v6 += 2;
    v3->rqOfs = v6;
  }
  while (v5);
  return v7;
}
