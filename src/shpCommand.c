#include "types.h"
#include "dds3adminiprocess.h"
#include "fld.h"
#include "scr.h"
#include "shpmain.h"
#include "shpmisc.h"

// macros
// 0x217b650: s32 SHP_GET_SELECT_ID(void)
static inline s32 SHP_GET_SELECT_ID(void) {
  shpGetSelectItemID();
  return 1;
}

// 0x217b850: s32 SHP_MDL_GET_HANDLE(void)
static inline s32 SHP_MDL_GET_HANDLE(void) {
  shpGetModelHandle();
  return 1;
}

// 0x217ba30: s32 SHP_MOTION(void)
static inline s32 SHP_MOTION(void) {
  shpSetModelMotion();
  return 1;
}

// 0x217bbe0: s32 SHP_CALL_RELEASE(void)
static inline s32 SHP_CALL_RELEASE(void) {
  g_bCallRelease = 1;
  return 1;
}

// 0x217bd10: s32 SHP_WAIT_RELEASE(void)
#define SHP_WAIT_RELEASE() (1)

// 0x217bd90: s32 SHP_GET_INDEX(void)
static inline s32 SHP_GET_INDEX(void) {
  nwdGetSelectModelID();
  return 1;
}

// 0x217c1b0: s32 KNY_GET_INTIMATE_RANK(void)
static inline s32 KNY_GET_INTIMATE_RANK(void) {
  s32 GoodRank;

  GoodRank = knyGetGoodRank();
  scrSetIntReturnValue(GoodRank);
  return 1;
}

// 0x217c390: s32 NWD_GET_INTIMATE_RANK(void)
static inline s32 NWD_GET_INTIMATE_RANK(void) {
  s32 GoodRank;

  GoodRank = nwdGetGoodRank();
  scrSetIntReturnValue(GoodRank);
  return 1;
}

// 0x217c570: s32 SHP_KONNOUYA(void)
static inline s32 SHP_KONNOUYA(void) {
  fldGbLocationSavePointStore();
  fldGbLocationSavePointStore();
  dds3AdminiCallSequence2(11, 2, 0, 0);
  scrAllReleaseScript();
  return 1;
}

// 0x217c630: s32 SHP_KONNOUYA_WAIT(void)
#define SHP_KONNOUYA_WAIT() (!shpProcessCheck())
