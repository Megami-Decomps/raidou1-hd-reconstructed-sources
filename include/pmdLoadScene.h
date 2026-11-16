#pragma once
#include "types.h"

typedef enum {
    pmdLoadScene_MODE_OFF = 0,
    pmdLoadScene_MODE_ON = 1,
    pmdLoadScene_MODE_DEL = 2,
} pmdLoadScene_MODE;

typedef struct pmdLoadScene pmdLoadScene;

struct pmdLoadScene {
    char *sceneName;
    char *assetBundleName;
    pmdLoadScene_MODE startMode;
    pmdLoadScene_MODE endMode;
    sdfVector3_t pos;
    s32 unitNo;
    s32 disableParts;
    void *bg;
    void *bgCtrl;
    void *model;
    s32 step;
};
