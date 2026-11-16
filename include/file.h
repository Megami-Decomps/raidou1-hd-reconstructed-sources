#pragma once
#include "types.h"
#include "fileEndCallback_t.h"
#include "libsdf.h"

typedef enum {
    STATE_INIT = 0,
    STATE_WAIT = 1,
    STATE_LOADED = 2,
    STATE_GO = 3,
} STATE;

typedef struct AssetBundleCtrl_Data AssetBundleCtrl_Data;
typedef struct DlcFiles_Data DlcFiles_Data;
typedef struct Load Load;
typedef struct STOCK STOCK;
typedef struct fileHandle_t fileHandle_t;
typedef struct pacFileHandle_t pacFileHandle_t;
typedef struct sdfPacDecodeResrcHandle_t sdfPacDecodeResrcHandle_t;

struct Load {
    s32 count;
    char *aName;
    s32 dlcId;
};

struct AssetBundleCtrl_Data {
    s32 count;
    Load *ld;
};

struct STOCK {
    char *key;
    char *filename;
};

struct DlcFiles_Data {
    s32 id;
    char *name;
    char *assetBundles;
    bool exists;
    char *aNames;
    s32 count;
    char *mount;
    u8 *buf;
};

bool pacHandleFree(pacFileHandle_t *pacHandle);
bool fileHandleFree(fileHandle_t *fileHandle);
pacFileHandle_t *pacLoadEx(char *abKey, char *assetName, sdfPacCallback_t callback, fileEndCallback_t endCallback, void *callbackParm);
pacFileHandle_t *pacLoad(char *abKey, char *assetName);
pacFileHandle_t *pacLoad_2(char *filename);
fileHandle_t *fileLoadEx(char *abKey, char *assetName, fileEndCallback_t endCallback, void *callbackParm);
fileHandle_t *fileLoad(char *abKey, char *assetName);
fileHandle_t *Load(char *filename);
void *fileGetMemHandle(fileHandle_t *fileHandle);
void *fileGetLoadPtr(fileHandle_t *fileHandle);
bool fileCheckEnd(fileHandle_t *fileHandle);
bool pacCheckEnd(pacFileHandle_t *pacHandle);
void fileSync(fileHandle_t *fileHandle);
void pacSync(pacFileHandle_t *pacFileHandle);
void fileSyncAll(void);
bool fileManager(bool sync);
bool Manager(void);
void fileSysInit(void);
sdfPacDecodeResrcHandle_t *pacGetResrc(pacFileHandle_t *cb);
