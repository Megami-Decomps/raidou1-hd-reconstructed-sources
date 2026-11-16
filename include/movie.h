#pragma once
#include "types.h"

typedef enum {
    MvSTAT_NONE = 0,
    MvSTAT_LOAD = 1,
    MvSTAT_LOADWAIT = 2,
    MvSTAT_DRAWING = 3,
    MvSTAT_STOP = 4,
    MvSTAT_END = 5,
    MvSTAT_ERASE = 6,
} MvSTAT;

typedef enum {
    MOVIE_NONE = 0,
    MOVIE_PLAY_FIRST = 1,
    MOVIE_PLAY = 2,
    MOVIE_STOP = 3,
} MOVIE;

extern s32 PlayingNo;
extern MvSTAT procStat;
extern s32 drawEnd;
extern s32 drawStart;

void movieNoMemoryAlloc(void);
void moviePlay(s32 aNum, bool loop, bool isPlay);
void movieStop(s32 bgmStop);
s32 movieCheckEnd(void);
s32 movieCheckDrawStat(void);
void movieInitManager(void);
void moviePause(bool sw);
void movieDisp(bool sw);
void movieCue(void);
s32 movieGetFrame(void);
s32 movieGetFrameCount(void);
bool movieCheckStandby(void);
MvSTAT movieGetProcStat(void);
char *movieGetSofdec2Path(char *path);
