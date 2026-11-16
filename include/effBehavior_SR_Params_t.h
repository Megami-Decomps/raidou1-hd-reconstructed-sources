#pragma once
#include "types.h"

typedef enum {
    EFFBEHAVIOR_SR_POINT_NON = 0,
    EFFBEHAVIOR_SR_POINT_1 = 1,
    EFFBEHAVIOR_SR_POINT_2 = 2,
    EFFBEHAVIOR_SR_POINT_MAX = 3,
} EFFBEHAVIOR_SR_POINT;

typedef enum {
    EFFBEHAVIOR_SR_DIR_FIX = 0,
    EFFBEHAVIOR_SR_DIR_RANDOM = 1,
    EFFBEHAVIOR_SR_DIR_ALIGN = 2,
    EFFBEHAVIOR_SR_DIR_MAX = 3,
} EFFBEHAVIOR_SR_DIR;

typedef struct Float Float;
typedef struct effBehavior_SR_Params_t effBehavior_SR_Params_t;

struct Float {
    f32 rate;
    f32 sr;
};

struct effBehavior_SR_Params_t {
    EFFBEHAVIOR_SR_POINT type;
    f32 start;
    f32 end;
    f32 random;
    EFFBEHAVIOR_SR_DIR dir;
    Float *point[3];
};
