#pragma once
#include "types.h"
#include "FILE_TYPE.h"
#include "fileEndCallback_t.h"

typedef enum {
    FILE_LOAD_PHASE_BUNDLE_READ = 0,
    FILE_LOAD_PHASE_ASSET_READING = 1,
    FILE_LOAD_PHASE_ASSET_READ = 2,
    FILE_LOAD_PHASE_DONE = 3,
} FILE_LOAD_PHASE;

typedef struct AssetBundleCtrl_Request AssetBundleCtrl_Request;
typedef struct fileHandle_t fileHandle_t;

struct fileHandle_t {
    FILE_TYPE type;
    FILE_LOAD_PHASE phase;
    fileHandle_t *next;
    char *abKey;
    char *assetName;
    bool abLoad;
    AssetBundleCtrl_Request *request;
    fileEndCallback_t endCallback;
    void *endCallbackParm;
};
