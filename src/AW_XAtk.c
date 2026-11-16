#include "types.h"
#include "SKLID.h"
#include "aw_xatk.h"
#include "aw_xatkpad.h"
#include "bsflow.h"
#include "sbtl.h"
#include "sbtldmg.h"

#define ID_E001_01 65553
#define ID_E001_02 65554
#define ID_E001_03 65555
#define ID_E001_04 65556
#define ID_E001_05 65557
#define ID_E001_06 65558
#define ID_E001_07 65559
#define ID_E001_08 65560
#define ID_E001_09 65561
#define ID_E001_10 65562
#define ID_E001_11 65563
#define ID_E001_12 65564
#define ID_E001_13 65565
#define ID_E001_14 65566
#define ID_E001_15 65567
#define ID_E016_01 65889
#define ID_E016_02 65890
#define ID_E016_03 65891
#define ID_E016_04 65892
#define ID_E018_01 65921
#define ID_E018_02 65922
#define ID_E018_03 65923
#define ID_E018_04 65924
#define ID_E01D_01 66001
#define ID_E01D_02 66002
#define ID_E01D_03 66003
#define ID_E01D_04 66004
#define ID_E028_01 66177
#define ID_E028_02 66178
#define ID_E028_03 66179
#define ID_E028_04 66180
#define ID_E028_05 66181
#define ID_E02D_01 66257
#define ID_E02D_02 66258
#define ID_E02D_03 66259
#define ID_E02D_04 66260
#define ID_E02E_01 66273
#define ID_E02E_02 66274
#define ID_E02E_03 66275
#define ID_E02E_04 66276
#define ID_E022_01 66081
#define ID_E022_02 66082
#define ID_E022_03 66083
#define ID_E022_04 66084
#define ID_E02F_01 66289
#define ID_E02F_02 66290
#define ID_E02F_03 66291
#define ID_E02F_04 66292
#define ID_E024_01 66113
#define ID_E024_02 66114
#define ID_E024_03 66115
#define ID_E024_04 66116
#define ID_E026_01 66145
#define ID_E026_02 66146
#define ID_E026_03 66147
#define ID_E026_04 66148
#define ID_E03C_01 66497
#define ID_E03C_02 66498
#define ID_E03C_03 66499
#define ID_E03C_04 66500
#define ID_E03C_05 66501
#define ID_E03C_06 66502
#define ID_E217_01 74097
#define ID_E217_02 74098
#define ID_E219_01 74129
#define ID_E219_02 74130
#define ID_E219_03 74131
#define ID_E20E_01 73953
#define ID_E20E_02 73954
#define ID_E20E_03 73955
#define ID_E20E_04 73956
#define ID_E03B_01 66481
#define ID_E03B_02 66482
#define ID_E03B_03 66483
#define ID_E03B_04 66484
#define ID_E01A_01 65953
#define ID_E01C_01 65985
#define ID_E01B_01 65969

typedef struct AW_XAtk_Arg_t AW_XAtk_Arg_t;
typedef struct AW_XAtk_t AW_XAtk_t;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

struct AW_XAtk_t {
    s32 ID;
    s32 V;
    f32 Ps2X;
    f32 Ps2Y;
    f32 Ps2Z;
    f32 Ps2Dir;
    s32 Delay;
    s32 Mark;
    SKLID SklID;
    u32 Flag;
};

AW_XAtk_Arg_t *ArgumentParam;
static AW_XAtk_t *gXAtkTable;

// 0x1e83770
void Init(void) {
  ;
}

// 0x1e83780
void Add(s32 _ID, SBTLUNIT_WORK *_wkEnemy) {
  AW_XAtk_Arg_t *ArgumentParam_local;

  ArgumentParam_local = ArgumentParam;
  ArgumentParam_local->wk = wkEnemy;
  ArgumentParam_local = ((char *)ArgumentParam_local + 24);
  LODWORD(ArgumentParam_local[-1].wk) = ID;
  Add_2();
}

// 0x1e83800
void Add_2(void) {
  s32 v2;
  u32 status;
  SBTLUNIT_WORK *wk_local;
  char v17;
  s64 i;
  AW_XAtkPad_Arg_t *v19;
  s64 v20;
  SBTLUNIT_WORK *v21;
  s64 v22;
  __int128 v23;
  s32 v24;
  SBTLUNIT_WORK *p_wk;
  AW_XAtk_t *v28;
  AW_XAtkPad_Arg_t *v30;
  void *Instance;

  v2 = 0;
  while (1)
  {
    if (v2 >= SLODWORD(gXAtkTable->max_length))
      break;
    if (gXAtkTable[v2]->ID == ArgumentParam->ID)
    {
      if (v2 == -1)
        return;
      if (!ArgumentParam->wk)
        return;
      status = wk->status;
      if ((status & 0x1000000) != 0)
        return;
      if ((status & 0x2000000) != 0)
        return;
      if (!sBtlCheckPlayerDead())
      {
        if (!wk->enemy_zenmetu)
        {
          if (!IsSceanStop())
            goto LABEL_37;
          if (wk->mode != 2)
          {
LABEL_37:
            if ((u32)(ArgumentParam->ID - 66497) > 4)
            {
              if (wk->encountno != 60)
              {
                wk_local = ArgumentParam->wk;
                if (wk_local)
                {
                  wk_local = ArgumentParam->wk;
                  AW_XAtkDelete_DuplicationNG(wk_local);
                }
              }
            }
            else
            {
              SetAction(18);
              AW_XAtkDelete_XATK_FLAG2_BsFlowClr();
            }
            v17 = 0;
            for (i = v2 + 4; ; ++i)
            {
              v28 = gXAtkTable;
              if (i - 4 >= SLODWORD(v28->max_length))
                break;
              v28 = gXAtkTable;
              if (*(u32 *)(*((u64 *)&v28->obj.klass + i) + 16) != ArgumentParam->ID)
                break;
              v30 = ArgumentParam;
              v19 = ArgumentParam;
              v20 = 8 * i;
              v21 = ArgumentParam->wk;
              v22 = *((u64 *)&gXAtkTable->obj.klass + i);
              v23 = *(_OWORD *)(v22 + 24);
              v24 = *(u32 *)(v22 + 40);
              v30->V = *(u32 *)(v22 + 20);
              v19->wk = v21;
              p_wk = &v19->wk;
              *((u32 *)p_wk - 3) = v24;
              *(_OWORD *)((char *)p_wk - 28) = v23;
              *(p_wk - 1) = *(SBTLUNIT_WORK *)(v22 + 48);
              Add();
              v17 |= *(&(*(Il2CppClass **)((char *)&gXAtkTable->obj.klass + v20))->_1.byval_arg.bits + 1) == 1;
            }
            if ((v17 & 1) != 0)
            {
              Instance = get_Instance(0);
              ReqCallMark(Instance, 300, 0);
            }
          }
        }
      }
      return;
    }
    ++v2;
  }
}

// 0x1e84790
void ClearBattleEnd(void) {
  SBTLUNIT_WORK *wk;
  AW_XAtk_Arg_t *ArgumentParam_local;

  wk = ArgumentParam->wk;
  if (!wk)
    return;
  wk = ArgumentParam->wk;
  ClassMemAlloc(wk, 0);
  ArgumentParam_local = ArgumentParam;
  ArgumentParam_local->wk = 0;
}
