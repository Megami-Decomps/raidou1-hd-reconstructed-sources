#pragma once
#include "types.h"
#include "event.h"

typedef struct dds3Basic_t dds3Basic_t;
typedef struct evtFrameInfo_t evtFrameInfo_t;
typedef struct evtViewerObject_t evtViewerObject_t;
typedef struct pmdDataInfo_t pmdDataInfo_t;
typedef struct pmdObjectTable_t pmdObjectTable_t;

struct evtViewerObject_t {
    PMD_OBJTYPE type;
    s32 myno;
    s32 nameindex;
    s32 fileindex;
    dds3Basic_t *basic;
    pmdDataInfo_t *data;
    pmdObjectTable_t *object_data;
    void *p;
    void *mesh;
    s32 nowedit;
    sdfVector4_t orgPos;
    sdfVector4_t orgRot;
    s32 posChangeFlag;
    s32 framecnt;
    evtFrameInfo_t *firstframeinfo;
    evtFrameInfo_t *lastframeinfo;
    evtFrameInfo_t *motionchange_apply_frame[8];
    evtViewerObject_t *next;
    evtViewerObject_t *prev;
};
