#pragma once
#include "types.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct nmeInput0Work_tag nmeInput0Work_tag;

struct nmeInput0Work_tag {
    dds3ProcessID_t *proc_draw;
    s32 mode;
    dds3ProcessID_t *menuPID;
    u32 type;
};
