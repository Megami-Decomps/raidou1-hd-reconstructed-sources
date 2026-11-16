#pragma once
#include "types.h"

typedef struct sdfDrawTag_t sdfDrawTag_t;
typedef struct sdfPrimTransPacket_t sdfPrimTransPacket_t;

sdfDrawTag_t *sdfPrimAllocDrawTag(void);
void sdfPrimSetOpaquePacket(sdfPrimTransPacket_t *aPkt);
void sdfPrimSetSemiTransPacket(sdfPrimTransPacket_t *aPkt);
void sdfPrimSetAddTransPacket(sdfPrimTransPacket_t *aPkt);
void sdfPrimSetSubTransPacket(sdfPrimTransPacket_t *aPkt);
