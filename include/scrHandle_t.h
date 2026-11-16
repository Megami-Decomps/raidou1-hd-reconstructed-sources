#pragma once
#include "types.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct scrCode_t scrCode_t;
typedef struct scrHandle_t scrHandle_t;
typedef struct scrHeader_t scrHeader_t;
typedef struct scrLabelTable_t scrLabelTable_t;
typedef struct scrProcTable_t scrProcTable_t;
typedef struct scrStackData_t scrStackData_t;
typedef struct scrTypeTable_t scrTypeTable_t;

struct scrStackData_t {
    s32 im;
    f32 fm;
    s16 s0;
    s16 s1;
    s8 c0;
    s8 c1;
    s8 c2;
    s8 c3;
    dds3ProcessID_t *id;
    sdfVector4_t vec;
};

struct scrHandle_t {
    char *Name;
    s32 CP;
    s32 SP;
    s8 StackType[28];
    scrStackData_t *StackData[28];
    scrHeader_t *Header;
    scrTypeTable_t *TypeTable;
    scrProcTable_t *ProcTable;
    scrLabelTable_t *LabelTable;
    scrCode_t *Code;
    u8 *MessageData;
    u8 *StringData;
    s32 StartProc;
    s32 MesHandle;
    s32 ScriptTimer;
    s32 CommandTimer;
    s32 *LocalInt;
    f32 *LocalFloat;
    dds3ProcessID_t *ProcessID;
    scrHandle_t *prev;
    scrHandle_t *next;
    void *data;
};
