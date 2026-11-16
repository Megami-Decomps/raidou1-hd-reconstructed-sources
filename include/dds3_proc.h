#pragma once
#include "types.h"
#include "kernel.h"

#define NAME_LENGTH 64
#define STAT_MASK 15
#define STAT_INVALID 0
#define STAT_START 1
#define STAT_RUNNING 2
#define STAT_END 3
#define FLAG_MASK 268435440
#define FLAG_PADDISABLE 16
#define FLAG_SUSPEND 32
#define FLAG_SET_ONLY 0
#define FLAG_SET_NOT 1
#define FLAG_SET_CHILD 2
#define FLAG_SET_ALL 3
#define MAX 1000

typedef struct dds3ProcessID_t dds3ProcessID_t;

// macros
// 0x22876c0: dds3ProcessFunc_t END(dds3ProcessID_t *id)
#define END(id) (0)
