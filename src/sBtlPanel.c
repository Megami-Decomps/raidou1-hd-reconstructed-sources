#include "types.h"
#include "SBTLPLAYER_MENUTYPE.h"
#include "SBTLPNL_MENU.h"
#include "SKLID.h"
#include "ditectivebook.h"
#include "kernel.h"
#include "rspecialskill.h"
#include "sbtl.h"
#include "sbtldraw.h"
#include "sbtlmain.h"
#include "sbtlpanel.h"
#include "sbtlplayer.h"
#include "sbtlsub.h"
#include "sbtltalk.h"
#include "sbtlunit.h"

typedef struct SBTLPANEL_WORK SBTLPANEL_WORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct sprHandle_t sprHandle_t;

static bool Midashi(void);
static bool ProcMidashi(void);
static bool Select(void);
static bool SelectKey(void);
static bool DrawSummonTarget_Csr(void);
static SBTLPANEL_WORK *CreatePanel(void);
static bool DeletePanel(SBTLPANEL_WORK *wk);
static bool Proc(SBTLPANEL_WORK *wk);

// 0x1f4af70
static bool Midashi(void) {
  return 1;
}

// 0x1f4afe0
static bool ProcMidashi(void) {
  return wk->mode == 2;
}

// 0x1f4b050
static bool Select(void) {
  SelectKey();
  return 1;
}

// 0x1f4b070
static bool SelectKey(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v5;

  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v5 = sBtlSearchUnit_ID(UnitMng, playerID);
  sBtlSummonMenuProc(v5);
  return 1;
}

// 0x1f4b150
static bool DrawSummonTarget_Csr(void) {
  return 1;
}

// 0x1f4b160
bool sBtlCheckLiveTarget(SBTLUNIT_WORK *wk) {
  u32 status;
  bool v3;

  status = wk->actwk->status;
  v3 = status == 11 || status == 14;
  return !v3 && wk->actaiwk->mode != 9 && wk->mode > 4;
}

// 0x1f4b1a0
void Init(void) {
  SBTLPANEL_WORK *Panel;
  SBTLPANEL_WORK *p_panelwk;
  SBATTLE_WORK *wk_local;
  SBTLPANEL_WORK *panelwk;
  SBTLPNL_WORK *mds_waku0;
  SBTLPNL_WORK *mds_waku1;
  SBTLPNL_WORK *mds_light;
  SBTLTALK_WORK *Talk;

  Panel = CreatePanel();
  Panel->hPanelSpr = 0;
  Panel->hPanelSpr2 = 0;
  Panel->hPanelSpr3 = 0;
  Panel->hPanelSpr4 = 0;
  Panel->hPanelSpr5 = 0;
  p_panelwk = &wk->panelwk;
  p_panelwk = Panel;
  wk_local = wk;
  panelwk = wk_local->panelwk;
  mds_waku0 = panelwk->mds_waku0;
  mds_waku1 = panelwk->mds_waku1;
  mds_light = panelwk->mds_light;
  *(u64 *)&mds_waku0->x = 0x20000013ALL;
  *(u64 *)&mds_waku1->x = 0x20000013ALL;
  *(u64 *)&mds_light->x = 297;
  Talk = sBtlCreateTalk();
  wk_local->talkwk = Talk;
}

// 0x1f4b4c0
bool sBtlDeleteMainPanel(void) {
  SBTLPANEL_WORK *panelwk;
  s32 status;
  SBATTLE_WORK *v6;
  u32 v7;
  SBTLTALK_WORK *p_talkwk;

  if ((wk->status & 0x800) == 0)
    return 1;
  panelwk = wk->panelwk;
  status = panelwk->status;
  if ((status & 1) == 0)
  {
LABEL_12:
    v6 = wk;
    v7 = v6->status;
    v6->panelwk = 0;
    v6->status = v7 & 0xFFFFF7FF;
    return 1;
  }
  if ((status & 2) != 0)
  {
    sBtlDeleteTalk(wk->talkwk);
    p_talkwk = &wk->talkwk;
    p_talkwk = 0;
    goto LABEL_12;
  }
  return 0;
}

// 0x1f4b2b0
static SBTLPANEL_WORK *CreatePanel(void) {
  SBTLPANEL_WORK *v1;
  s64 i;
  SBTLPNL_WORK *menu0;
  SBTLPNL_WORK *v4;
  SBTLPNL_WORK *menu1;
  SBTLPNL_WORK *v6;
  SBTLPNL_SETDATA *data;
  SBTLPNL_SETDATA *v8;
  SBTLPNL_SETDATA *v9;
  SBTLPNL_SETDATA *v10;

  v1 = (SBTLPANEL_WORK *)Allocate(SBTLPANEL_WORK);
  _ctor(v1, 0);
  for (i = 32; i != 128; i += 8)
  {
    menu0 = v1->menu0;
    v4 = Allocate(SBTLPNL_WORK);
    _ctor(v4, 0);
    *(Il2CppClass **)((char *)&menu0->obj.klass + i) = v4;
    menu1 = v1->menu1;
    v6 = Allocate(SBTLPNL_WORK);
    _ctor(v6, 0);
    *(Il2CppClass **)((char *)&menu1->obj.klass + i) = v6;
  }
  data = v1->data;
  v8 = Allocate(SBTLPNL_SETDATA);
  _ctor(v8, 0);
  v9[1] = v10;
  v1->hPanelSpr = 0;
  v1->hPanelSpr2 = 0;
  v1->hPanelSpr3 = 0;
  v1->hPanelSpr4 = 0;
  v1->hPanelSpr5 = 0;
  v1->alpha = 0;
  v1->mode = 0;
  return v1;
}

// 0x1f4b650
static bool DeletePanel(SBTLPANEL_WORK *wk) {
  s32 status;
  SBTLTALK_WORK *p_talkwk;

  status = wk->status;
  if ((status & 1) != 0)
  {
    if ((status & 2) == 0)
      return 0;
    sBtlDeleteTalk(wk->talkwk);
    p_talkwk = &wk->talkwk;
    p_talkwk = 0;
  }
  return 1;
}

// 0x1f4b700
bool sBtlMainProc(void) {
  SBTLPANEL_WORK *panelwk;

  if (!wk)
    return 0;
  panelwk = wk->panelwk;
  if (!panelwk)
    return 0;
  if ((panelwk->status & 2) == 0)
    return 0;
  Proc(panelwk);
  SelectKey();
  return 1;
}

// 0x1f4b9c0
void sBtlResetMidashiAnim(s8 flg) {
  SBTLPANEL_WORK *panelwk;
  SBTLPNL_WORK *mds_waku0;
  SBTLPNL_WORK *mds_waku1;
  SBTLPNL_WORK *mds_light;

  if (flg)
    return;
  panelwk = wk->panelwk;
  mds_waku0 = panelwk->mds_waku0;
  mds_waku1 = panelwk->mds_waku1;
  *(_OWORD *)&mds_waku0->x = xmmword_3CFB0C0;
  mds_waku0->alpha = 0;
  mds_waku1->alpha = 0;
  mds_waku0->mode = 0;
  *(_OWORD *)&mds_waku1->x = xmmword_3CFB0C0;
  mds_light = panelwk->mds_light;
  mds_waku1->mode = 0;
  mds_light->alpha = 0;
  mds_light->mode = 0;
  *(_OWORD *)&mds_light->x = xmmword_3CFCE90;
  panelwk->astat0 = 0;
  *(int32x2_t *)&mds_light->scaleX = vdup_n_s32(0x42C80000u);
}

// 0x1f4ba90
bool sBtlCheckSelectAnim(void) {
  return wk->panelwk->astat1 == 5;
}

// 0x1f4bb00
void sBtlSetSelectAnim(s8 flg) {
  s32 v3;
  s64 v4;
  SBTLPANEL_WORK *panelwk;
  s64 v7;
  s64 v8;
  SBTLPNL_WORK *menu0;
  SBTLPNL_WORK *v12;
  SBTLPNL_WORK *v13;
  s32 v14;
  s64 v15;
  SBTLPANEL_WORK *v17;
  s64 v18;
  s64 v19;
  s64 v20;
  SBTLUNIT_WORK *Nakama;
  s32 v24;
  s64 v25;
  SBTLPANEL_WORK *v27;
  s64 v28;
  s64 v29;
  s64 v30;
  u32 v31;
  SBATTLE_WORK *v32;
  s64 v34;
  SBTLPANEL_WORK *v35;
  s64 v36;
  s64 v37;
  s64 v38;
  SBATTLE_WORK *v39;
  s64 v41;
  SBTLPANEL_WORK *v42;
  s64 v43;
  s64 v44;
  s64 v45;
  SBATTLE_WORK *v46;
  u32 v47;
  SBTLPANEL_WORK *v48;
  s32 v49;
  SBTLPNL_WORK *kettei;
  s16 *summonindex;
  SBTLPANEL_WORK *v52;
  s32 *stock_useskillp;
  s64 v54;
  SBTLPNL_WORK *v55;
  SBTLPANEL_WORK *v56;
  SBTLPNL_WORK *v57;
  u32 v59;
  SBTLPNL_WORK *v61;
  SBTLPNL_WORK *v62;
  SBTLPNL_WORK *v63;
  SBTLPNL_WORK *v64;
  SBTLPNL_WORK *v65;
  SBTLPNL_WORK *v66;
  SBTLPNL_WORK *v67;
  SBTLPNL_WORK *v68;
  SBTLPNL_WORK *v69;
  SBTLPNL_WORK *v70;
  u32 v72;
  SBTLPNL_WORK *v73;
  u32 v75;
  SBTLPNL_WORK *v76;
  u32 v78;
  SBTLPNL_WORK *v79;
  u32 v81;
  SBTLPNL_WORK *v82;
  u32 v84;
  SBTLPNL_WORK *v85;
  u32 v87;
  SBTLPNL_WORK *v88;
  u32 v90;
  SBTLPNL_WORK *v91;
  u32 v93;
  SBTLPNL_WORK *v94;
  u32 v96;
  SBTLPNL_WORK *v97;

  switch (flg)
  {
    case 0:
      v3 = 46;
      v4 = 32;
      do
      {
        panelwk = wk->panelwk;
        v7 = *(s64 *)((char *)&panelwk->menu0->obj.klass + v4);
        *(u64 *)(v7 + 16) = 0;
        *(u32 *)(v7 + 36) = v3;
        *(u64 *)(v7 + 40) = 0;
        *(u64 *)(v7 + 28) = 0x1A900000000LL;
        v8 = *(s64 *)((char *)&panelwk->menu1->obj.klass + v4);
        v4 += 8;
        *(u32 *)(v8 + 36) = v3;
        v3 += 36;
        *(u64 *)(v8 + 40) = 0;
        *(u64 *)(v8 + 28) = 0x1A900000000LL;
        *(u64 *)(v8 + 16) = 0;
      }
      while (v4 != 128);
      panelwk = wk->panelwk;
      panelwk->acnt1 = 0;
      panelwk->astat1 = 2;
      return;
    case 1:
      menu0 = wk->panelwk->menu0;
      v12 = menu0[0];
      *(u64 *)&v12->x = 0x2E000001A9LL;
      v12->alpha = 0;
      v12->mode = 0;
      v13 = menu0[1];
      v13->alpha = 0;
      v13->mode = 0;
      *(u64 *)&v13->x = 0x52000001A9LL;
      goto LABEL_9000;
      if (!v59)
      {
        menu0 = wk->panelwk->menu0;
        v73 = menu0[2];
        *(u64 *)&v73->x = 0x76000001A9LL;
        v73->alpha = 0;
        v73->mode = 0;
        if (!v72)
        {
          menu0 = wk->panelwk->menu0;
          v76 = menu0[3];
          *(u64 *)&v76->x = 0x9A000001A9LL;
          v76->alpha = 0;
          v76->mode = 0;
          if (!v75)
          {
            menu0 = wk->panelwk->menu0;
            v79 = menu0[4];
            *(u64 *)&v79->x = 0xBE000001A9LL;
            v79->alpha = 0;
            v79->mode = 0;
            if (!v78)
            {
              menu0 = wk->panelwk->menu0;
              v82 = menu0[5];
              *(u64 *)&v82->x = 0xE2000001A9LL;
              v82->alpha = 0;
              v82->mode = 0;
              if (!v81)
              {
                menu0 = wk->panelwk->menu0;
                v85 = menu0[6];
                *(u64 *)&v85->x = 0x106000001A9LL;
                v85->alpha = 0;
                v85->mode = 0;
                if (!v84)
                {
                  menu0 = wk->panelwk->menu0;
                  v88 = menu0[7];
                  *(u64 *)&v88->x = 0x12A000001A9LL;
                  v88->alpha = 0;
                  v88->mode = 0;
                  if (!v87)
                  {
                    menu0 = wk->panelwk->menu0;
                    v91 = menu0[8];
                    *(u64 *)&v91->x = 0x14E000001A9LL;
                    v91->alpha = 0;
                    v91->mode = 0;
                    if (!v90)
                    {
                      menu0 = wk->panelwk->menu0;
                      v94 = menu0[9];
                      *(u64 *)&v94->x = 0x172000001A9LL;
                      v94->alpha = 0;
                      v94->mode = 0;
                      if (!v93)
                      {
                        menu0 = wk->panelwk->menu0;
                        v97 = menu0[10];
                        *(u64 *)&v97->x = 0x196000001A9LL;
                        v97->alpha = 0;
                        v97->mode = 0;
                        if (!v96)
                        {
                          menu0 = wk->panelwk->menu0;
                        }
                        goto LABEL_68;
                      }
LABEL_67:
                      v69 = menu0[10];
                      v69->alpha = 0;
                      v69->mode = 0;
                      *(u64 *)&v69->x = 0x196000001A9LL;
LABEL_68:
                      v70 = menu0[11];
                      v70->alpha = 0;
                      v70->mode = 0;
                      *(u64 *)&v70->x = 0x1BA000001A9LL;
                      return;
                    }
LABEL_66:
                    v68 = menu0[9];
                    v68->alpha = 0;
                    v68->mode = 0;
                    *(u64 *)&v68->x = 0x172000001A9LL;
                    goto LABEL_67;
                  }
LABEL_65:
                  v67 = menu0[8];
                  v67->alpha = 0;
                  v67->mode = 0;
                  *(u64 *)&v67->x = 0x14E000001A9LL;
                  goto LABEL_66;
                }
LABEL_64:
                v66 = menu0[7];
                v66->alpha = 0;
                v66->mode = 0;
                *(u64 *)&v66->x = 0x12A000001A9LL;
                goto LABEL_65;
              }
LABEL_63:
              v65 = menu0[6];
              v65->alpha = 0;
              v65->mode = 0;
              *(u64 *)&v65->x = 0x106000001A9LL;
              goto LABEL_64;
            }
LABEL_62:
            v64 = menu0[5];
            v64->alpha = 0;
            v64->mode = 0;
            *(u64 *)&v64->x = 0xE2000001A9LL;
            goto LABEL_63;
          }
LABEL_61:
          v63 = menu0[4];
          v63->alpha = 0;
          v63->mode = 0;
          *(u64 *)&v63->x = 0xBE000001A9LL;
          goto LABEL_62;
        }
LABEL_60:
        v62 = menu0[3];
        v62->alpha = 0;
        v62->mode = 0;
        *(u64 *)&v62->x = 0x9A000001A9LL;
        goto LABEL_61;
      }
LABEL_9000:
      v61 = menu0[2];
      v61->alpha = 0;
      v61->mode = 0;
      *(u64 *)&v61->x = 0x76000001A9LL;
      goto LABEL_60;
    case 2:
      v14 = 46;
      v15 = 4;
      while (1)
      {
        if (v15 - 4 >= wk->stock_num)
          break;
        v17 = wk->panelwk;
        v18 = 8 * v15++;
        v19 = *(s64 *)((char *)&v17->menu0->obj.klass + v18);
        *(u64 *)(v19 + 40) = 0;
        *(u64 *)(v19 + 16) = 0x8000000000LL;
        *(u32 *)(v19 + 36) = v14;
        v14 += 36;
        *(u64 *)(v19 + 28) = 0x13600000000LL;
        v20 = *(s64 *)((char *)&v17->menu1->obj.klass + v18);
        *(u32 *)(v20 + 20) = 96;
        *(u16 *)(v20 + 16) = 0;
      }
      v48 = wk->panelwk;
      v49 = 36 * wk->macter_csr + 54;
      v48->acnt1 = 0;
      v48->astat1 = 4;
      kettei = v48->kettei;
      kettei->y = v49;
      *(u64 *)&kettei->ofs_x = 0;
      *(u64 *)&kettei->mode = 0x8000000000LL;
      *(u64 *)&kettei->counter = 0x11600000000LL;
      *(int32x2_t *)&kettei->scaleX = vdup_n_s32(0x42C80000u);
      return;
    case 3:
      Nakama = sBtlGetNakama(0);
      sBtlGetSkillMenu(Nakama, 0x1000u);
      v24 = 46;
      v25 = 4;
      while (1)
      {
        v32 = wk;
        if (v25 - 4 >= v32->stock_skillnum)
          break;
        if (!v31)
        {
          v32 = wk;
        }
        v27 = v32->panelwk;
        v28 = 8 * v25++;
        v29 = *(s64 *)((char *)&v27->menu0->obj.klass + v28);
        *(u64 *)(v29 + 40) = 0;
        *(u64 *)(v29 + 16) = 0x8000000000LL;
        *(u32 *)(v29 + 36) = v24;
        v24 += 36;
        *(u64 *)(v29 + 28) = 0x13600000000LL;
        v30 = *(s64 *)((char *)&v27->menu1->obj.klass + v28);
        *(u32 *)(v30 + 20) = 96;
        *(u16 *)(v30 + 16) = 0;
      }
      if (!v31)
      {
        v32 = wk;
      }
      summonindex = v32->summonindex;
      v52 = v32->panelwk;
      v52->astat1 = 4;
      stock_useskillp = v32->stock_useskillp;
      v54 = summonindex[0];
      v55 = v52->kettei;
      v52->acnt1 = 0;
      v55->x = 278;
      LODWORD(stock_useskillp) = stock_useskillp[v54];
      *(u64 *)&v55->ofs_x = 0;
      v55->counter = 0;
      *(u64 *)&v55->mode = 0x8000000000LL;
      v55->y = 36 * (u32)stock_useskillp + 54;
      *(int32x2_t *)&v55->scaleX = vdup_n_s32(0x42C80000u);
      return;
    case 4:
      v34 = wk->macter_csr + 4;
      while (1)
      {
        v39 = wk;
        if (v34 - 4 >= v39->macter_csr + 1)
          break;
        v39 = wk;
        v35 = v39->panelwk;
        v36 = 8 * v34++;
        v37 = *(s64 *)((char *)&v35->menu0->obj.klass + v36);
        *(u64 *)(v37 + 16) = 0x8000000000LL;
        *(u32 *)(v37 + 44) = 0;
        *(_OWORD *)(v37 + 28) = xmmword_3CFB8F0;
        v38 = *(s64 *)((char *)&v35->menu1->obj.klass + v36);
        *(u32 *)(v38 + 20) = 0;
        *(u16 *)(v38 + 16) = 0;
      }
      return;
    case 5:
      v41 = wk->macter_csr + 4;
      while (1)
      {
        v46 = wk;
        if (v41 - 4 >= v46->macter_csr + 1)
          break;
        if (!v47)
        {
          v46 = wk;
        }
        v42 = v46->panelwk;
        v43 = 8 * v41++;
        v44 = *(s64 *)((char *)&v42->menu0->obj.klass + v43);
        *(u64 *)(v44 + 16) = 0x8000000000LL;
        *(u32 *)(v44 + 44) = 0;
        *(_OWORD *)(v44 + 28) = xmmword_3CFB8F0;
        v45 = *(s64 *)((char *)&v42->menu1->obj.klass + v43);
        *(u64 *)(v45 + 32) = 0x2E00000136LL;
        *(u32 *)(v45 + 20) = 96;
        *(u16 *)(v45 + 16) = 0;
      }
      if (!v47)
      {
        v46 = wk;
      }
      v56 = v46->panelwk;
      v56->astat1 = 6;
      v56->acnt1 = 0;
      v57 = v56->kettei;
      *(_OWORD *)&v57->counter = xmmword_3D00690;
      v57->ofs_y = 0;
      *(u64 *)&v57->mode = 0x8000000000LL;
      *(int32x2_t *)&v57->scaleX = vdup_n_s32(0x42C80000u);
      return;
    default:
      return;
  }
}

// 0x1f4c430
void sBtlResetSelectAnim(s8 flg) {
  s32 v3;
  s64 v4;
  SBTLPANEL_WORK *panelwk;
  s64 v7;
  s64 v8;
  SBTLPNL_WORK *v9;
  SBTLPNL_WORK *v10;
  SBTLPNL_WORK *menu0;
  SBTLPNL_WORK *v13;
  SBTLPNL_WORK *v14;
  SBTLPNL_WORK *v15;
  SBTLPNL_WORK *v16;
  SBTLPNL_WORK *v17;
  SBTLPNL_WORK *v18;
  SBTLPNL_WORK *v19;
  SBTLPNL_WORK *v20;
  SBTLPNL_WORK *v21;
  SBTLPNL_WORK *v22;
  SBTLPNL_WORK *v23;
  SBTLPNL_WORK *v24;
  SBTLPNL_WORK *v27;
  u32 v31;
  SBTLPNL_WORK *v33;
  SBTLPNL_WORK *v34;
  SBTLPNL_WORK *v35;
  SBTLPNL_WORK *v36;
  SBTLPNL_WORK *v37;
  SBTLPNL_WORK *v38;
  SBTLPNL_WORK *v39;
  SBTLPNL_WORK *v40;
  SBTLPNL_WORK *v41;
  u32 v43;
  SBTLPNL_WORK *v44;
  u32 v46;
  SBTLPNL_WORK *v47;
  u32 v49;
  SBTLPNL_WORK *v50;
  u32 v52;
  SBTLPNL_WORK *v53;
  u32 v55;
  SBTLPNL_WORK *v56;
  u32 v58;
  SBTLPNL_WORK *v59;
  u32 v61;
  SBTLPNL_WORK *v62;
  u32 v64;
  SBTLPNL_WORK *v65;
  u32 v67;
  SBTLPNL_WORK *v68;

  if (flg == 1)
  {
    menu0 = wk->panelwk->menu0;
    v13 = menu0[0];
    v14 = menu0[1];
    *(u64 *)&v13->x = 0x2E000001A9LL;
    v13->alpha = 0;
    v13->mode = 0;
    v14->alpha = 0;
    v14->mode = 0;
    *(u64 *)&v14->x = 0x52000001A9LL;
    v15 = menu0[2];
    v16 = menu0[3];
    v15->alpha = 0;
    v15->mode = 0;
    v16->mode = 0;
    *(u64 *)&v15->x = 0x76000001A9LL;
    v16->alpha = 0;
    *(u64 *)&v16->x = 0x9A000001A9LL;
    v17 = menu0[4];
    v18 = menu0[5];
    v17->alpha = 0;
    v17->mode = 0;
    v18->mode = 0;
    *(u64 *)&v17->x = 0xBE000001A9LL;
    v18->alpha = 0;
    *(u64 *)&v18->x = 0xE2000001A9LL;
    v19 = menu0[6];
    v20 = menu0[7];
    v19->alpha = 0;
    v19->mode = 0;
    v20->mode = 0;
    *(u64 *)&v19->x = 0x106000001A9LL;
    v20->alpha = 0;
    *(u64 *)&v20->x = 0x12A000001A9LL;
    v21 = menu0[8];
    v22 = menu0[9];
    v21->alpha = 0;
    v21->mode = 0;
    v22->mode = 0;
    *(u64 *)&v21->x = 0x14E000001A9LL;
    v22->alpha = 0;
    *(u64 *)&v22->x = 0x172000001A9LL;
    v24 = menu0[10];
    v23 = menu0[11];
    v24->alpha = 0;
    v24->mode = 0;
    *(u64 *)&v24->x = 0x196000001A9LL;
LABEL_31:
    v23->alpha = 0;
    v23->mode = 0;
    *(u64 *)&v23->x = 0x1BA000001A9LL;
    return;
    if (!v31)
    {
      v27 = wk->panelwk->menu0;
      v44 = v27[2];
      *(u64 *)&v44->x = 0x76000001A9LL;
      v44->alpha = 0;
      v44->mode = 0;
      if (!v43)
      {
        v27 = wk->panelwk->menu0;
        v47 = v27[3];
        *(u64 *)&v47->x = 0x9A000001A9LL;
        v47->alpha = 0;
        v47->mode = 0;
        if (!v46)
        {
          v27 = wk->panelwk->menu0;
          v50 = v27[4];
          *(u64 *)&v50->x = 0xBE000001A9LL;
          v50->alpha = 0;
          v50->mode = 0;
          if (!v49)
          {
            v27 = wk->panelwk->menu0;
            v53 = v27[5];
            *(u64 *)&v53->x = 0xE2000001A9LL;
            v53->alpha = 0;
            v53->mode = 0;
            if (!v52)
            {
              v27 = wk->panelwk->menu0;
              v56 = v27[6];
              *(u64 *)&v56->x = 0x106000001A9LL;
              v56->alpha = 0;
              v56->mode = 0;
              if (!v55)
              {
                v27 = wk->panelwk->menu0;
                v59 = v27[7];
                *(u64 *)&v59->x = 0x12A000001A9LL;
                v59->alpha = 0;
                v59->mode = 0;
                if (!v58)
                {
                  v27 = wk->panelwk->menu0;
                  v62 = v27[8];
                  *(u64 *)&v62->x = 0x14E000001A9LL;
                  v62->alpha = 0;
                  v62->mode = 0;
                  if (!v61)
                  {
                    v27 = wk->panelwk->menu0;
                    v65 = v27[9];
                    *(u64 *)&v65->x = 0x172000001A9LL;
                    v65->alpha = 0;
                    v65->mode = 0;
                    if (!v64)
                    {
                      v27 = wk->panelwk->menu0;
                      v68 = v27[10];
                      *(u64 *)&v68->x = 0x196000001A9LL;
                      v68->alpha = 0;
                      v68->mode = 0;
                      if (!v67)
                      {
                        v27 = wk->panelwk->menu0;
                      }
                      goto LABEL_30;
                    }
LABEL_29:
                    v41 = v27[10];
                    v41->alpha = 0;
                    v41->mode = 0;
                    *(u64 *)&v41->x = 0x196000001A9LL;
LABEL_30:
                    v23 = v27[11];
                    goto LABEL_31;
                  }
LABEL_28:
                  v40 = v27[9];
                  v40->alpha = 0;
                  v40->mode = 0;
                  *(u64 *)&v40->x = 0x172000001A9LL;
                  goto LABEL_29;
                }
LABEL_27:
                v39 = v27[8];
                v39->alpha = 0;
                v39->mode = 0;
                *(u64 *)&v39->x = 0x14E000001A9LL;
                goto LABEL_28;
              }
LABEL_26:
              v38 = v27[7];
              v38->alpha = 0;
              v38->mode = 0;
              *(u64 *)&v38->x = 0x12A000001A9LL;
              goto LABEL_27;
            }
LABEL_25:
            v37 = v27[6];
            v37->alpha = 0;
            v37->mode = 0;
            *(u64 *)&v37->x = 0x106000001A9LL;
            goto LABEL_26;
          }
LABEL_24:
          v36 = v27[5];
          v36->alpha = 0;
          v36->mode = 0;
          *(u64 *)&v36->x = 0xE2000001A9LL;
          goto LABEL_25;
        }
LABEL_23:
        v35 = v27[4];
        v35->alpha = 0;
        v35->mode = 0;
        *(u64 *)&v35->x = 0xBE000001A9LL;
        goto LABEL_24;
      }
LABEL_22:
      v34 = v27[3];
      v34->alpha = 0;
      v34->mode = 0;
      *(u64 *)&v34->x = 0x9A000001A9LL;
      goto LABEL_23;
    }
    v33 = v27[2];
    v33->alpha = 0;
    v33->mode = 0;
    *(u64 *)&v33->x = 0x76000001A9LL;
    goto LABEL_22;
  }
  if (!flg)
  {
    v3 = 46;
    v4 = 32;
    do
    {
      v9 = wk->panelwk->menu0;
      v10 = Allocate(SBTLPNL_WORK);
      _ctor(v10, 0);
      *(Il2CppClass **)((char *)&v9->obj.klass + v4) = v10;
      panelwk = wk->panelwk;
      v7 = *(s64 *)((char *)&panelwk->menu0->obj.klass + v4);
      *(u64 *)(v7 + 40) = 0;
      *(u64 *)(v7 + 16) = 0;
      *(u32 *)(v7 + 36) = v3;
      *(u64 *)(v7 + 28) = 0x1A900000000LL;
      v8 = *(s64 *)((char *)&panelwk->menu1->obj.klass + v4);
      v4 += 8;
      *(u32 *)(v8 + 36) = v3;
      v3 += 36;
      *(u64 *)(v8 + 28) = 0x1A900000000LL;
      *(u64 *)(v8 + 16) = 0;
    }
    while (v4 != 128);
    panelwk = wk->panelwk;
    panelwk->astat1 = 0;
    panelwk->acnt1 = 0;
  }
}

// 0x1f4ca70
bool sBtlMainDraw(void) {
  SBTLPANEL_WORK *panelwk;
  s32 kaiwaflg;

  panelwk = wk->panelwk;
  if (!panelwk)
    return 0;
  if ((panelwk->status & 2) == 0)
    return 0;
  if (panelwk->mode == 3)
    return 0;
  if ((wk->status4 & 0x10) != 0)
    return 0;
  if (ProcessCheck())
    return 0;
  if (ProcessCheck())
    return 0;
  sBtlEnemyData();
  kaiwaflg = (u8)wk->kaiwaflg;
  if (kaiwaflg != 1)
  {
    kaiwaflg = (u8)wk->kaiwaflg;
    if (kaiwaflg != 2)
    {
      sBtlPlayerData();
      goto LABEL_50;
    }
  }
  if (wk->kaiwapaneldisp0)
  {
    sBtlPlayerData();
  }
  if (!wk->kaiwapaneldisp1)
    return 1;
LABEL_50:
  sBtlSummonDevilData();
  return 1;
}

// 0x1f4cd70
bool sBtlMainDraw2(void) {
  SBTLUNIT_WORK *Nakama;
  void *Instance;
  void *v9;
  SBTLUNIT_WORK *v12;
  void *v14;
  void *v15;

  if (sBtlGetNakama(0) && (sBtlGetNakama(0)->vstatus & 0x1000) == 0)
  {
    Nakama = sBtlGetNakama(0);
    sBtlSummonDevilAshimoto(Nakama, 0);
    if (!sBtlGetNakama(1))
      goto LABEL_20;
    goto LABEL_15;
  }
  Instance = get_Instance(0);
  if (!op_Inequality(Instance, 0, 0))
  {
    if (!sBtlGetNakama(1))
      goto LABEL_20;
    goto LABEL_15;
  }
  v9 = get_Instance(0);
  NakamaMarkDispOff(v9, 0, 0);
  if (!sBtlGetNakama(1))
    goto LABEL_20;
LABEL_15:
  if ((sBtlGetNakama(1)->vstatus & 0x1000) == 0)
  {
    v12 = sBtlGetNakama(1);
    sBtlSummonDevilAshimoto(v12, 1);
    return 1;
  }
LABEL_20:
  v14 = get_Instance(0);
  if (!op_Inequality(v14, 0, 0))
    return 1;
  v15 = get_Instance(0);
  NakamaMarkDispOff(v15, 1, 0);
  return 1;
}

// 0x1f4cf50
bool sBtlSetLoadPanelData(void) {
  SBATTLE_WORK *wk_local;
  SBTLPANEL_WORK *panelwk;
  u32 status;

  wk_local = wk;
  if (!wk_local)
    return 0;
  panelwk = wk_local->panelwk;
  if (!panelwk)
    return 0;
  wk_local = wk;
  panelwk = wk_local->panelwk;
  if ((panelwk->status & 1) != 0)
    return 1;
  status = wk_local->status;
  if ((status & 1) == 0)
    return 1;
  wk_local = wk;
  status = wk_local->status;
  *(u64 *)&wk_local->effOnRsc->setflg = 0;
  wk_local->status = status | 0x800;
  panelwk->status |= 1u;
  return 0;
}

// 0x1f4d0c0
bool sBtlCheckLoadFlg(void) {
  SBTLPANEL_WORK *panelwk;
  _BOOL4 v4;

  if (!wk)
  {
    LOBYTE(v4) = 0;
    return v4;
  }
  panelwk = wk->panelwk;
  if (!panelwk)
  {
    LOBYTE(v4) = 0;
    return v4;
  }
  panelwk = wk->panelwk;
  return (LOBYTE(panelwk->status) >> 1) & 1;
}

// 0x1f4d1b0
bool sBtlCheckLoadData(void) {
  SBTLPANEL_WORK *panelwk;
  s32 setflg;

  if (!wk)
    return 0;
  panelwk = wk->panelwk;
  if (!panelwk)
    return 0;
  if ((panelwk->status & 2) != 0)
    return 1;
  setflg = wk->effOnRsc->setflg;
  if (setflg)
  {
    setflg = wk->effOnRsc->setflg;
  }
  panelwk->status |= 2u;
  return 1;
}

// 0x1f4b890
static bool Proc(SBTLPANEL_WORK *wk) {
  s32 mode;
  s32 v5;

  if (!wk || (~wk->status & 3) != 0)
  {
    LOBYTE(v5) = 0;
    return v5;
  }
  mode = wk->mode;
  if (mode == 2)
  {
    wk->alpha -= 16;
    LimitRange(&wk->alpha, 0, 128);
    if (wk->alpha <= 0)
    {
      v5 = 3;
LABEL_17:
      wk->mode = v5;
      LOBYTE(v5) = 1;
      return v5;
    }
LABEL_15:
    LOBYTE(v5) = 1;
    return v5;
  }
  if (mode)
    goto LABEL_15;
  wk->alpha += 16;
  LimitRange(&wk->alpha, 0, 128);
  v5 = 1;
  if (wk->alpha > 127)
    goto LABEL_17;
  return v5;
}

// 0x1f398e0
void sBtlDrawSprite(s32 x, s32 y, s32 alpha, sprHandle_t *handle, s32 sprno) {
  NewSpecific(uint, 4u);
}

// 0x1f4d310
void sBtlDrawSprite_RGBA2(s32 x, s32 y, u32 *rgba, sprHandle_t *handle, s32 sprno, DDS3_OT ot) {
  ;
}

// 0x1f4d320
bool sBtlResetSummonPanel(SBTLPLAYER_MENUTYPE menutype) {
  *(u32 *)wk->sgstat = 0;
  wk->menutype = menutype;
  return 1;
}

// 0x1f4d3a0
s32 sBtlGetMenuStatus(void) {
  return wk->panelwk->data[0]->flg;
}

// 0x1f4d410
void sBtlResetMenuPara(void) {
  wk->panelwk->data[0]->flg = 0;
}

// 0x1f4d480
void sBtlCancelMenuPara(void) {
  wk->panelwk->data[0]->flg = 2;
}

// 0x1f4d4f0
bool sBtlSetMenuPara(SBTLPNL_MENU mode, s32 stock_id, SKLID skillid, s32 itemid, s32 targetid, s32 smnid) {
  s16 v11;
  SBTLPNL_SETDATA *data;
  SBTLPNL_SETDATA *v16;
  SBTLPNL_SETDATA *v18;

  v11 = stock_id;
  data = wk->panelwk->data;
  v16 = data[0];
  v16->flg = 1;
  v16->select_no = mode;
  switch (mode)
  {
    case 1:
    case 8:
      v16 = wk->panelwk->data[0];
      goto LABEL_11;
    case 2:
      data = wk->panelwk->data;
      wk->ctrlSmnIdx = smnid;
      v18 = data[smnid];
      v18->meirei_no = 2;
      v18->target_p = v11;
      v18->skillid = skillid;
      v18->targetid = targetid;
      break;
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
      data = wk->panelwk->data;
      v16 = data[0];
      data[smnid]->meirei_no = mode;
LABEL_11:
      v16->target_p = v11;
      wk->ctrlSmnIdx = smnid;
      break;
    case 9:
      v16 = wk->panelwk->data[0];
      v16->target_p = v11;
      v16->itemid = itemid;
      v16->targetid = targetid;
      break;
    case 10:
      v16 = wk->panelwk->data[0];
      v16->itemid = itemid;
      break;
    default:
      break;
  }
  wk->menutype = 0;
  return 1;
}
