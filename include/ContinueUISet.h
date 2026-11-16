#pragma once
#include "types.h"

typedef struct ContinueUISet ContinueUISet;
typedef struct ContinueUITextSet ContinueUITextSet;

struct ContinueUITextSet {
    void *TextUGUI;
};

struct ContinueUISet {
    ContinueUITextSet *sousa_continueText;
    void *continueList;
    void *continueCursorList;
    void *continueTextList;
    void *continueFramaList;
    ContinueUITextSet *continueCountText[3];
};
