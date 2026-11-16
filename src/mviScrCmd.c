#include "types.h"
#include "dds3kerneldraw.h"
#include "evtviewer.h"
#include "itf.h"
#include "movie.h"
#include "mviscrcmd.h"
#include "scr.h"
#include "sdfsound.h"

#define SCRMOVIE_SKIPCOUNT 30

static s32 s_ScriptMovieSkipFlag;
s32 skpStopEnable;

// macros
// 0x1d85130: s32 MOVIE_PLAY(void)
static inline s32 MOVIE_PLAY(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  scrEventSkipEnd(0, 0);
  p2sdBGMStopAll();
  moviePlay(IntPara, 0, 1);
  s_ScriptMovieSkipFlag = 0;
  gAns = 0;
  return 1;
}

// 0x1d85260: s32 MOVIE_STOP(void)
static inline s32 MOVIE_STOP(void) {
  movieStop(0);
  s_ScriptMovieSkipFlag = 0;
  _Off(Filter2, 0);
  itfPmvButtonGuideCtrl(0);
  return 1;
}

// 0x1d85370: s32 MOVIE_CHK(void)
static inline s32 MOVIE_CHK(void) {
  void *Instance;
  s32 v9;

  if (gAns == 2)
  {
    skpStopEnable = 0;
    movieStop(0);
    scrSetIntReturnValue(0);
    itfSetGuidePMV("", 0);
    Instance = get_Instance(0);
    uiOffGaugeOff(Instance, 1, 0);
    return 1;
  }
  v9 = drawEnd == 0;
  skpStopEnable = v9;
  scrSetIntReturnValue(v9);
  return 1;
}

// 0x1d85590: s32 MOVIE_CHKDRAW(void)
#define MOVIE_CHKDRAW() (drawStart == 2)
