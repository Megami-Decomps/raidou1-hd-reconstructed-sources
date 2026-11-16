#include "types.h"
#include "dat.h"
#include "dds3kernelcore.h"
#include "itf.h"
#include "scr.h"
#include "sdat.h"
#include "shpmessage.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct tagSHP_MSG_WK tagSHP_MSG_WK;

struct tagSHP_MSG_WK {
    u8 *pDatScr;
    dds3ProcessID_t *ScrPID;
};

static tagSHP_MSG_WK *wk;
static char *szShpScrEnterFile;

static void Delete(void);
static void LoadFile(char **filename);
static void EnterLoadFile(s32 a_shopType);

// 0x21a4a00
static void Delete(void) {
  tagSHP_MSG_WK *wk_local;

  wk_local = wk;
  wk_local->pDatScr = 0;
}

// 0x21a4a70
static void LoadFile(char **filename) {
  tagSHP_MSG_WK *wk_local;
  char *v6;
  void *Asset;
  sdfBinary *v9;
  u8 *data;
  tagSHP_MSG_WK *v11;

  wk_local = wk;
  wk_local->pDatScr = 0;
  v6 = "shop_evt";
  Asset = LoadAsset(_Ctrl_k__BackingField, v6, *filename, 0);
  v9 = Allocate(sdfBinary);
  _ctor(v9, Asset, 0);
  data = v9->data;
  v11 = wk;
  v11->pDatScr = data;
}

// 0x21a4c30
s32 shpLinkData(u8 *a_pDatScr) {
  tagSHP_MSG_WK *wk_local;

  if (!a_pDatScr)
    return 0;
  wk_local = wk;
  wk_local->pDatScr = a_pDatScr;
  return 1;
}

// 0x21a4cc0
static void EnterLoadFile(s32 a_shopType) {
  LoadFile(&szShpScrEnterFile[a_shopType]);
}

// 0x21a4d30
void shpStartScript(s32 a_procedureNo) {
  tagSHP_MSG_WK *wk_local;
  u8 *pDatScr;
  dds3ProcessID_t *started;

  wk_local = wk;
  pDatScr = wk->pDatScr;
  started = scrStartScript2(1, pDatScr, a_procedureNo, 1);
  wk_local->ScrPID = started;
}

// 0x21a4e20
void shpNewsStartScript(void) {
  if (!wk)
    return;
  shpStartScript(0);
}

// 0x21a4ed0
void shpOrderStartScript(s32 a_stockID, s32 a_itemID) {
  scrHandle_t *v5;
  dds3ProcessID_t *p_ScrPID;
  Il2CppObject *ProcessData;
  s32 monitor_high;
  char *v11;

  v5 = Allocate(scrHandle_t);
  _ctor(v5, 0);
  if ((u32)a_stockID <= 0x1F)
  {
    datGetStockDevilID(a_stockID);
  }
  shpStartScript(0);
  p_ScrPID = &wk->ScrPID;
  ProcessData = dds3GetProcessData(&wk->ScrPID);
  if (!ProcessData)
  monitor_high = HIDWORD(ProcessData[6].monitor);
  v11 = sdatItemName(a_itemID);
  itfMesMngSetVarImmediate(monitor_high, 1, v11);
}

// 0x21a5090
void shpEnterStartScript(s32 a_shopType) {
  LoadFile(&szShpScrEnterFile[a_shopType]);
  shpStartScript(0);
}

// 0x21a5160
bool shpCheckScript(void) {
  tagSHP_MSG_WK *wk_local;
  dds3ProcessID_t *p_ScrPID;
  dds3ProcessID_t *v7;
  tagSHP_MSG_WK *v9;
  tagSHP_MSG_WK *v11;

  wk_local = wk;
  if (!wk_local->ScrPID)
    return 0;
  p_ScrPID = &wk_local->ScrPID;
  if (dds3GetProcessStat(p_ScrPID) != 3)
  {
    v7 = &wk->ScrPID;
    if (dds3GetProcessStat(v7))
      return 0;
  }
  v9 = wk;
  v9->ScrPID = 0;
  v11 = wk;
  v11->pDatScr = 0;
  return 1;
}

// 0x21a5370
void shpMsgInit(void) {
  Il2CppObject *v1;
  dds3ProcessID_t *v2;

  v1 = Allocate(tagSHP_MSG_WK);
  v2 = Allocate(dds3ProcessID_t);
  _ctor(v2, 0);
  v1[1].monitor = v2;
  _ctor(v1, 0);
  wk = (tagSHP_MSG_WK *)v1;
}

// 0x21a54e0
void shpMsgEnd(void) {
  tagSHP_MSG_WK *wk_local;
  dds3ProcessID_t *p_ScrPID;
  tagSHP_MSG_WK *v7;
  dds3ProcessID_t *v9;
  tagSHP_MSG_WK *v10;

  wk_local = wk;
  if (wk_local)
    goto LABEL_4;
  return;
  if (wk_local)
  {
LABEL_4:
    p_ScrPID = &wk_local->ScrPID;
    if (!dds3ExistProcess(p_ScrPID))
    {
      goto LABEL_8;
    }
    v9 = &wk->ScrPID;
    dds3KillProcess(v9, 0);
    v10 = wk;
    v10->ScrPID = 0;
LABEL_8:
    v7 = wk;
    v7->pDatScr = 0;
    wk = 0;
    return;
  }
}
