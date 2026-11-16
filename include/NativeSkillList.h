#pragma once
#include "types.h"
#include "SKLID.h"

typedef enum {
    NoRegist = 0,
    Registrable = 1,
    Registered = 2,
} NativeSkillListType;

typedef struct NativeSkillList NativeSkillList;

struct NativeSkillList {
    SKLID skillID;
    NativeSkillListType registType;
};
