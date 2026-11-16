#include "types.h"
#include "sdfdraw.h"

typedef struct sdfDrawTag_t sdfDrawTag_t;
typedef struct sdfGrOt_t sdfGrOt_t;
typedef struct sdfGrPacketHeader_t sdfGrPacketHeader_t;

// 0x225d2e0
void sdfDrawTagLinkOt(sdfGrOt_t *ot, sdfDrawTag_t *tag) {
  sdfDrawTag_t *tagTail;
  sdfDrawTag_t *p_tagTail;
  sdfDrawTag_t *p_next;

  if (tag->head)
  {
    p_tagTail = &ot->tagTail;
    tagTail = ot->tagTail;
    if (tagTail)
      p_next = &tagTail->next;
    else
      p_next = &ot->tagHead;
    p_next = tag;
    p_tagTail = tag;
  }
}

// 0x225d3a0
void sdfDrawTagLinkOtHead(sdfGrOt_t *ot, sdfDrawTag_t *tag) {
  sdfDrawTag_t *p_tagHead;
  sdfDrawTag_t *tagHead;

  if (tag->tail)
  {
    p_tagHead = &ot->tagHead;
    tagHead = ot->tagHead;
    if (!tagHead)
    {
      ot->tagTail = tag;
    }
    tag->next = tagHead;
    p_tagHead = tag;
  }
}

// 0x225d490
void sdfDrawTagInit(sdfDrawTag_t *aTag) {
  aTag->next = 0;
  aTag->head = 0;
  aTag->tail = 0;
}

// 0x225d4e0
void sdfDrawTagLink(sdfDrawTag_t *aTag, sdfGrPacketHeader_t *aPacket) {
  sdfGrPacketHeader_t *tail;
  sdfGrPacketHeader_t *p_tail;
  sdfGrPacketHeader_t *p_next;

  p_tail = &aTag->tail;
  tail = aTag->tail;
  if (tail)
    p_next = &tail->next;
  else
    p_next = &aTag->head;
  p_next = aPacket;
  p_tail = aPacket;
}
