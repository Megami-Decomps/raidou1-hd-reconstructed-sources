#pragma once
#include "types.h"

typedef struct sprHandle_t sprHandle_t;

extern sprHandle_t *moon_spr;
extern s32 LoyaltyID;
extern s16 LoyaltyAdd;

void evtMoonTakaraCntReset(bool SummonDV);
void evtMoonZeniCntReset(bool SummonDV);
void evtMoonTakumiCntReset(void);
void evtMoonTeisatuCntReset(void);
void evtMoonLoyaltyDataClear(void);
void evtMoonLoyaltyCntClear(void);
void evtMoonLoyaltyCntReset(void);
void evtMoonLoyaltyCntUpdate(void);
bool evtMoonLoyaltyCntCheck(void);
void evtMoonLoyaltyWinSetup(void);
s32 evtMoonGetAge(void);
s32 evtMoonGetAge16(void);
void evtMoonSetAge(u32 age);
void evtMoonSetAgeBit(s32 age);
void evtMoonEnableCalc(void);
void evtMoonDisableCalc(void);
void evtMoonEnableDraw(void);
void evtMoonDisableDraw(bool fldobjout_reset);
void evtMoonEnableDraw2(void);
void evtMoonDisableDraw2(void);
bool evtMoonGetDraw(void);
void evtMoonFadeIn(s32 Frame);
void evtMoonFadeOut(s32 Frame);
s32 evtMoonFadeCheck(void);
void evtMoonAddMove(f32 leng);
void evtMoonInitProcess(void);
void evtMoonFreeProcess(void);
