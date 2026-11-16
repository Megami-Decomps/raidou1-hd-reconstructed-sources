#include "types.h"
#include "libsdf.h"
#include "sdftime.h"

typedef struct sdfTime_t sdfTime_t;

static sdfTime_t *sdfLastTime;
u8 GetDelay;

// 0x2281e00
SDF_TIME Get(sdfTime_t *aTime) {
  s32 v4;
  sdfTime_t *p_sdfLastTime;
  sdfTime_t *v6;
  u8 Second;
  sdfTime_t *v12;
  u8 Minute;
  sdfTime_t *v15;
  u8 Hour;
  sdfTime_t *v18;
  u8 Day;
  sdfTime_t *v21;
  u8 Month;
  sdfTime_t *v24;
  u16 v25;
  u64 dateData;

  dateData = 0;
  if (!GetDelay)
  {
    dateData = get_Now(0)._dateData;
    Second = get_Second((System_DateTime_o)&dateData, 0);
    sdfLastTime->sec = Second;
    v12 = sdfLastTime;
    Minute = get_Minute((System_DateTime_o)&dateData, 0);
    v12->min = Minute;
    v15 = sdfLastTime;
    Hour = get_Hour((System_DateTime_o)&dateData, 0);
    v15->hour = Hour;
    v18 = sdfLastTime;
    Day = get_Day((System_DateTime_o)&dateData, 0);
    v18->day = Day;
    v21 = sdfLastTime;
    Month = get_Month((System_DateTime_o)&dateData, 0);
    v21->month = Month;
    v24 = sdfLastTime;
    v25 = get_Month((System_DateTime_o)&dateData, 0) + 2000;
    v4 = 0;
    v24->year = v25;
    GetDelay = 20;
    goto LABEL_6;
  }
  v4 = 1;
LABEL_6:
  p_sdfLastTime = &sdfLastTime;
  v6 = p_sdfLastTime;
  aTime = p_sdfLastTime;
  return v4;
}
