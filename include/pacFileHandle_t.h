#pragma once
#include "types.h"
#include "fileEndCallback_t.h"

typedef struct AssetBundleCtrl_Request AssetBundleCtrl_Request;
typedef struct fileHandle_t fileHandle_t;
typedef struct pacFileHandle_t pacFileHandle_t;
typedef struct sdfPacDecodeCb_t sdfPacDecodeCb_t;

struct pacFileHandle_t {
    u8 type;
    u8 phase;
    fileHandle_t *next;
    char *abKey;
    char *assetName;
    bool abLoad;
    AssetBundleCtrl_Request *request;
    fileEndCallback_t endCallback;
    void *endCallbackParm;
    sdfPacDecodeCb_t *decodeCb;
    bool decodeEnd;
};
