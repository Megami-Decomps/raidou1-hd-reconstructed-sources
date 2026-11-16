#pragma once
#include "types.h"

typedef struct StaffSet StaffSet;

struct StaffSet {
    void *CutObjList;
    void *CutImageList;
    void *movie;
    void *captionTMProUGUI;
    void *nameTMProUGUI;
    void *staffNameTM1;
    void *staffNameTM2;
    void *captionTM1;
    void *copywriter;
};
