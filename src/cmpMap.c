#include "types.h"
#include "cmpfile.h"
#include "cmpmain.h"
#include "cmpmap.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "ditectivebook.h"
#include "fld.h"
#include "itf.h"
#include "jmsinit.h"
#include "kernel.h"
#include "lmap.h"
#include "localize.h"
#include "sdfmem.h"

#define CMP_MAP_MAINPROC_NAME "camp_automap_main"
#define CMP_MAP_DRAWPROC_NAME "camp_automap_draw"
#define AUTOMAP_DATA_NAME "automapData"
#define AUTOMAP_TEXT_NAME "text_automapData."

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct tagCMP_MAP_WORK tagCMP_MAP_WORK;

dds3ProcessID_t *g_mainPID;

void mapAutoMapGuideCheckFloor(void);

// 0x1f5f1a0
dds3ProcessFunc_t Process(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 klass_high;
  s32 v9;
  dds3ProcessFunc_t v10;
  s32 v12;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  switch (HIDWORD(ProcessData[1].monitor))
  {
    case 0:
      if (!IsLoad(Dependent, "automapData", 0))
        return 0;
      HIDWORD(ProcessData[1].monitor) = 1;
      return 0;
    case 1:
      mapAutoMapCalc3();
      mapAutoMapGuideCheckFloor();
      LODWORD(ProcessData[1].monitor) |= 8u;
      HIDWORD(ProcessData[1].monitor) = 2;
      dds3FadeOut(0, 0, 0, 1u);
      return 0;
    case 2:
      klass_high = HIDWORD(ProcessData[2].klass);
      if (!klass_high)
      {
        dds3FadeIn(0, 0, 0, 0xAu);
        klass_high = HIDWORD(ProcessData[2].klass);
        goto LABEL_52;
      }
      if (klass_high < 10)
        goto LABEL_52;
      HIDWORD(ProcessData[2].klass) = 0;
      HIDWORD(ProcessData[1].monitor) = 3;
      return 0;
    case 3:
      if (mapAutoMapCalc3())
        return 0;
      HIDWORD(ProcessData[1].monitor) = 4;
      return 0;
    case 4:
      v9 = HIDWORD(ProcessData[2].klass);
      if (v9)
      {
        if (v9 >= 10)
        {
          HIDWORD(ProcessData[2].klass) = 0;
          HIDWORD(ProcessData[1].monitor) = 5;
          sdfMemResourcesRelease();
          return 0;
        }
      }
      else
      {
        dds3FadeOut(0, 0, 0, 0xAu);
        if (cmpProcessCheck())
          v12 = 1;
        else
          v12 = 18;
        SE(v12);
      }
      klass_high = HIDWORD(ProcessData[2].klass);
      goto LABEL_52;
    case 5:
      klass_high = HIDWORD(ProcessData[2].klass);
      if (!klass_high)
      {
        LODWORD(ProcessData[1].monitor) &= ~8u;
        goto LABEL_52;
      }
      if (klass_high < 2)
      {
LABEL_52:
        HIDWORD(ProcessData[2].klass) = klass_high + 1;
        return 0;
      }
      HIDWORD(ProcessData[2].klass) = 0;
      HIDWORD(ProcessData[1].monitor) = 6;
      mapAutomapClose();
      return 0;
    case 6:
      v10 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
      _ctor(v10, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      return v10;
    default:
      return 0;
  }
}

// 0x1f5f640
void DrawBackGradation(s32 a_x, s32 a_y, s32 count) {
  *(_OWORD *)(NewSpecific(uint, 4u) + 32) = xmmword_3CFB0D0;
}

// 0x1f5f6a0
void cmpDrawBack(tagCMP_MAP_WORK *wk) {
  if (!cmpGetSpriteHnd(3))
    return;
  *(_OWORD *)(NewSpecific(uint, 4u) + 32) = xmmword_3CFB0D0;
  *(_OWORD *)(NewSpecific(uint, 4u) + 32) = xmmword_3CFB0D0;
  *(_OWORD *)(NewSpecific(uint, 4u) + 32) = xmmword_3CFB0D0;
}

// 0x1f5f7e0
void cmpDrawBackPattern(tagCMP_MAP_WORK *wk) {
  u64 *v2;
  u64 *v3;
  u64 *v4;
  u64 *v5;
  u64 *v6;
  u64 *v7;
  u64 *v8;
  u64 *v9;
  u64 *v10;
  u64 *v11;

  v2 = NewSpecific(int__, 9u);
  v3 = NewSpecific(s32, 2u);
  v3[4] = 0x7100000011LL;
  v2[4] = v3;
  v4 = NewSpecific(s32, 2u);
  v4[4] = 0xFFFFFFFA0000003FLL;
  v2[5] = v4;
  v5 = NewSpecific(s32, 2u);
  v5[4] = 0x2D00000114LL;
  v2[6] = v5;
  v6 = NewSpecific(s32, 2u);
  v6[4] = 0xD1FFFFFFBBLL;
  v2[7] = v6;
  v7 = NewSpecific(s32, 2u);
  v7[4] = 0x10C00000048LL;
  v2[8] = v7;
  v8 = NewSpecific(s32, 2u);
  v8[4] = 0x14C000000A1LL;
  v2[9] = v8;
  v9 = NewSpecific(s32, 2u);
  v9[4] = 0xED0000011CLL;
  v2[10] = v9;
  v10 = NewSpecific(s32, 2u);
  v10[4] = 0x5200000185LL;
  v2[11] = v10;
  v11 = NewSpecific(s32, 2u);
  v2[12] = v11;
  v11[4] = 0x14100000186LL;
  cmpGetSpriteHnd(3);
}

// 0x1f5fa00
void DrawTop(tagCMP_MAP_WORK *wk) {
  if (!cmpGetSpriteHnd(3))
    return;
  itfIconDrawSprite(438, 419, 0, 0xFFu, 13, 109);
}

// 0x1f5fad0
dds3ProcessFunc_t DrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  tagCMP_MAP_WORK *v6;
  tagCMP_MAP_WORK *v8;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if (((s64)ProcessData[1].monitor & 8) != 0)
  {
    cmpDrawBack(ProcessData);
    cmpDrawBackPattern(v6);
    mapAutoMapDraw3();
    DrawTop(v8);
  }
  return 0;
}

// 0x1f5fbf0
void Release(tagCMP_MAP_WORK *wk) {
  s32 flag;

  flag = wk->flag;
  if ((flag & 2) == 0)
  {
    if ((flag & 4) == 0)
      return;
    goto LABEL_8;
  }
  wk->flag = flag & 0xFFFFFFFD;
  cmpFreeSpriteMem(3);
  flag = wk->flag;
  if ((flag & 4) == 0)
    return;
LABEL_8:
  wk->flag = flag & 0xFFFFFFFB;
  cmpFreeSpriteHnd(3);
}

// 0x1f5fce0
void Shutdown(dds3ProcessID_t *PID) {
  tagCMP_MAP_WORK *ProcessData;
  dds3ProcessID_t *p_drawPID;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  Release(ProcessData);
  p_drawPID = &ProcessData->drawPID;
  if (dds3ExistProcess(p_drawPID))
  {
    dds3KillProcess(p_drawPID, 0);
  }
  id = 0;
  g_mainPID = 0;
}

// 0x1f56180
void ProcessStart(bool _camp, s32 _mapNo, s32 _floorNo, s32 _x, s32 _z, bool _quest) {
  tagCMP_MAP_WORK *v15;
  dds3ProcessID_t *v16;
  dds3ProcessFunc_t v17;
  shutdownfuncDelegate v18;
  dds3ProcessID_t *started;
  dds3ProcessFunc_t v20;
  dds3ProcessID_t *v21;
  s32 v25;
  s32 floorNoa;
  s32 v27;

  if (!quest)
  {
    v25 = mapNo;
    goto LABEL_4;
  }
  if (jmsProcessCheck())
    goto LABEL_30;
  if (lmapProcessCheck())
    goto LABEL_30;
  QuestLoadMap = 1;
  fldJmsQuestMapLoad(mapNo, -1);
  v25 = mapNo;
  goto LABEL_4;
LABEL_30:
  fldJmsQuestMapLoad(mapNo, -1);
  mapAutoMapSetFloor(0, 0, 0.0, 0.0, 0, 0.0, 0.0);
  v25 = mapNo;
LABEL_4:
  GetAppendix();
  Load(Dependent, "automapData", "automapData");
  Load(Dependent, "text_automapData.", "text_automapData.");
  v27 = x;
  floorNoa = floorNo;
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  LoadLocalizeText_2("text_automapData.", "ICON_HELP");
  LoadLocalizeText_2("text_automapData.", "AM_LIST");
  v15 = Allocate(tagCMP_MAP_WORK);
  v16 = Allocate(dds3ProcessID_t);
  _ctor(v16, 0);
  v15->drawPID = v16;
  _ctor(v15, 0);
  v17 = Allocate(dds3ProcessFunc_t);
  _ctor(v17, 0, Method_Project_cmpMap_Process__, 0);
  v18 = Allocate(shutdownfuncDelegate);
  _ctor(v18, 0, Method_Project_cmpMap_Shutdown__, 0);
  started = dds3StartProcess("camp_automap_main", 1007, 0, 0, v17, v18, v15);
  g_mainPID = started;
  v20 = Allocate(dds3ProcessFunc_t);
  _ctor(v20, 0, Method_Project_cmpMap_DrawProcess__, 0);
  v21 = dds3StartProcess("camp_automap_draw", 11012, 0, 0, v20, 0, v15);
  v15->drawPID = v21;
  if (cmpGetSpriteHnd(3))
  {
    goto LABEL_18;
  }
  cmpLoadSpriteHnd(3);
  v15->flag |= 4u;
LABEL_18:
  mapAutoMapStart3(camp, v25, floorNoa, v27, z);
}

// 0x1f4fa00
void ProcessEnd(void) {
  Il2CppObject *ProcessData;
  s32 monitor;

  if (g_mainPID)
  {
    if (!dds3ExistProcess(g_mainPID))
      return;
    ProcessData = dds3GetProcessData(g_mainPID);
    if (!ProcessData)
    {
LABEL_14:
      monitor = ProcessData[1].monitor;
      if ((monitor & 1) == 0)
      {
        HIDWORD(ProcessData[2].klass) = 0;
        LODWORD(ProcessData[1].monitor) = monitor | 1;
        HIDWORD(ProcessData[1].monitor) = 5;
      }
      return;
    }
    goto LABEL_14;
  }
}

// 0x1f4fe20
bool ProcessCheck(void) {
  if (!g_mainPID)
    return 1;
  if (dds3GetProcessStat(g_mainPID) != 3)
  {
    if (dds3GetProcessStat(g_mainPID))
      return 0;
  }
  g_mainPID = 0;
  return 1;
}
