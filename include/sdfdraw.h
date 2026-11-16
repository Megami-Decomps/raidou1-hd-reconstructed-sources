#pragma once
#include "types.h"

typedef struct sdfDrawTag_t sdfDrawTag_t;
typedef struct sdfGrOt_t sdfGrOt_t;
typedef struct sdfGrPacketHeader_t sdfGrPacketHeader_t;

void sdfDrawTagLinkOt(sdfGrOt_t *ot, sdfDrawTag_t *tag);
void sdfDrawTagLinkOtHead(sdfGrOt_t *ot, sdfDrawTag_t *tag);
void sdfDrawTagInit(sdfDrawTag_t *aTag);
void sdfDrawTagLink(sdfDrawTag_t *aTag, sdfGrPacketHeader_t *aPacket);
