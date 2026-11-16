#include "types.h"
#include "dds3_pad.h"
#include "dds3_pad2.h"
#include "dds3kernelcore.h"
#include "dds3kernelmisc.h"
#include "dds3padmanager.h"
#include "kernel.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct sdfDrawTag_t sdfDrawTag_t;

// 0x22a17d0
void SelectSub(s32 *pbase, s32 *pm, s32 list, s32 win, s32 pad, s32 pluskey, s32 minuskey) {
  bool v13;
  bool v15;
  s32 v16;
  s32 v17;
  bool v18;
  s32 v19;
  bool v20;
  s32 v22;
  s32 v23;
  s32 v24;
  s32 v25;

  if (list < 2)
    return;
  if (pad)
  {
    v13 = CHECK_REP(minuskey, pm);
    v15 = CHECK_REP(pluskey);
    if (v13)
      goto LABEL_4;
LABEL_9:
    if (!v15)
      return;
LABEL_22:
    v23 = *pbase;
LABEL_23:
    v24 = *pm;
    v25 = win - 1;
    if (v23)
    {
      if (v24 >= v25)
      {
        if (v23 + win < list)
        {
          *pbase = v23 + 1;
          return;
        }
        *pbase = 0;
        goto LABEL_30;
      }
    }
    else if (v24 >= v25)
    {
LABEL_30:
      *pm = 0;
      return;
    }
    *pm = v24 + 1;
    return;
  }
  v20 = CHECK_REP2(minuskey);
  v15 = CHECK_REP2(pluskey);
  if (!v20)
    goto LABEL_9;
LABEL_4:
  v16 = *pbase;
  v17 = *pm;
  if (!*pbase)
  {
    v22 = v17 - 1;
    if (v17 >= 1)
      goto LABEL_21;
    if (list >= win)
      goto LABEL_19;
    goto LABEL_20;
  }
  v18 = __OFSUB__(v17, 1);
  v19 = v17 - 1;
  if (v19 < 0 == v18)
  {
    *pm = v19;
    if (!v15)
      return;
    goto LABEL_22;
  }
  v18 = __OFSUB__(v16, 1);
  v23 = v16 - 1;
  if (v23 < 0 != v18)
  {
    if (list > win)
    {
      *pbase = list - win;
LABEL_19:
      v22 = win - 1;
      goto LABEL_21;
    }
LABEL_20:
    v22 = list - 1;
LABEL_21:
    *pm = v22;
    if (!v15)
      return;
    goto LABEL_22;
  }
  *pbase = v23;
  if (v15)
    goto LABEL_23;
}

// 0x22a1900
s32 dds3SelectMenu(s32 pad, s32 listsx, s32 listsy, s32 winsx, s32 winsy, s32 *basex, s32 *basey, s32 *x, s32 *y) {
  SelectSub(basey, y, listsy, winsy, pad, 4101, 4100);
  SelectSub(basex, x, listsx, winsx, pad, 4103, 4102);
  if (pad)
  {
    if (CHECK_TRIG(4096))
      return 1;
    if (CHECK_TRIG(4097))
      return -1;
  }
  else
  {
    if (CHECK_TRIG2(4096))
      return 1;
    if (CHECK_TRIG2(4097))
      return -1;
  }
  return 0;
}

// 0x22a1a10
void dds3ConsPanelTagLink(sdfDrawTag_t *tag, s32 x, s32 y, s32 sx, s32 sy) {
  ;
}

// 0x22a1a20
void dds3ConsPanelTagLinkZ(sdfDrawTag_t *tag, s32 x, s32 y, s32 sx, s32 sy, s32 z) {
  ;
}

// 0x22a1a30
dds3ProcessFunc_t dds3VibrationTestProcess(dds3ProcessID_t *id) {
  u64 v3;
  dds3ProcessID_t *ida;

  ida = id;
  HIDWORD(v3) = -404681363 * dds3GetProcessRunTime(ida);
  LODWORD(v3) = HIDWORD(v3);
  if ((u32)(v3 >> 4) > 0x3A411)
    return 0;
  dds3PadAct(0, 1u, 0xBEu);
  dds3PadAct(1u, 0x78u, 0xBEu);
  return 0;
}

// 0x22a1b20
void *dds3GetCanvasTransform(void *canvas) {
  return get_transform(canvas, 0);
}
