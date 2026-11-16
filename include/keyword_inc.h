#pragma once
#include "types.h"

typedef struct keywordCategoryData keywordCategoryData;

struct keywordCategoryData {
    s32 listno[10];
};

extern keywordCategoryData *s_sKeywordcd[32];
extern s16 *s_iKeywordflglist;
extern s16 *s_iKeywordreadflglist;
