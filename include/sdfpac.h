#pragma once
#include "types.h"
#include "libsdf.h"

typedef struct sdfPacDecodeCb_t sdfPacDecodeCb_t;
typedef struct sdfPacDecodeResrcHandle_t sdfPacDecodeResrcHandle_t;

sdfPacDecodeResrcHandle_t *sdfPacGetResrc(sdfPacDecodeCb_t *cb);
void sdfPacInit(sdfPacDecodeCb_t *cb, sdfPacCallback_t callback);
void sdfPacSetStay(sdfPacDecodeCb_t *cb);
void sdfPacFree(sdfPacDecodeCb_t *cb);
SDF_PAC_STAT sdfPacDecode(sdfPacDecodeCb_t *cb, void *data, s32 length);
sdfPacDecodeResrcHandle_t *sdfPacFreeResrc(sdfPacDecodeResrcHandle_t *resrc);
