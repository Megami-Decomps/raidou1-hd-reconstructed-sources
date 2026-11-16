#pragma once
#include "types.h"
#include "name.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct nmeWork_tag nmeMainWork_tag;
typedef struct nmeWork_tag nmeWork_tag;

struct nmeWork_tag {
    dds3ProcessID_t *proc_draw;
    NME_MODE mode;
    dds3ProcessID_t *menuPID;
};
