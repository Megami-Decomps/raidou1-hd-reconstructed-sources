#include "types.h"
#include "dat.h"
#include "dds3_pad2.h"
#include "itemdebugmenu.h"
#include "kernel.h"
#include "sdat.h"

typedef enum {
    ItemDebugMenu_MenuListID_No = 0,
    ItemDebugMenu_MenuListID_Num = 1,
    ItemDebugMenu_MenuListID_Get = 2,
} ItemDebugMenu_MenuListID;

typedef struct dds3ProcessID_t dds3ProcessID_t;

static s32 NowMenuListID;
static s32 ItemID;
static s32 ItemNum;
static bool ItemGet;
static char *ItemName;
static s32 ItemNumMax;

// 0x1a37250
dds3ProcessFunc_t Process(dds3ProcessID_t *id) {
  struct dat *static_fields;
  s16 *item;
  s32 v7;
  bool v11;
  s32 v14;
  bool v15;
  bool v17;
  s32 v20;
  bool v21;
  s32 v26;
  s32 v29;
  bool v30;
  s32 v32;
  bool v38;
  bool v39;
  s32 v41;
  s32 v43;
  char *v44;
  s32 v46;
  char *v47;
  char *v48;
  s32 v50;
  f32 v51;
  s32 v52;
  char *v53;
  char *v54;
  s32 v58;
  s32 v59;
  char *v60;
  s32 v62;
  s32 v63;
  char *v64;
  char *v65;
  char *v66;
  char *v68;
  s32 v69;
  char *v70;
  char *v71;
  char *v72;
  char *v73;
  char *v74;
  char *v75;
  s32 v79;
  s32 v80;
  dds3ProcessFunc_t v81;
  s32 NowMenuListID_local;
  s32 v84;
  sdfColor_t v85;
  sdfColor_t v86;
  sdfColor_t v87;
  sdfColor_t v88;
  sdfColor_t v89;

  NowMenuListID_local = 0;
  item = GBWK->player->item;
  v7 = item[ItemID];
  v84 = v7;
  ItemNumMax = datGetItemMaxNum(ItemID) - v7;
  if (CHECK_TRIG(4, 0))
  {
    if (NowMenuListID--)
      goto LABEL_10;
    NowMenuListID = 0;
    v17 = CHECK_TRIG(5, 0);
    if (!v17)
      goto LABEL_24;
    goto LABEL_11;
  }
LABEL_10:
  v11 = CHECK_TRIG(5, 0);
  if (!v11)
    goto LABEL_24;
LABEL_11:
  v14 = NowMenuListID + 1;
  v15 = NowMenuListID - 2 < 0;
  NowMenuListID = v14;
  if (v15 != __OFSUB__(v14, 3))
    goto LABEL_24;
  NowMenuListID = 2;
LABEL_24:
  NowMenuListID_local = NowMenuListID;
  v20 = NowMenuListID_local;
  if (NowMenuListID_local != 2)
  {
    if (v20 != 1)
    {
      if (v20)
        goto LABEL_106;
      if (CHECK_REP(6, 0))
      {
        --ItemID;
        if (!CHECK_REP(7, 0))
        {
LABEL_30:
          if (!CHECK_REP(8, 0))
            goto LABEL_31;
          goto LABEL_66;
        }
      }
      else if (!CHECK_REP(7, 0))
      {
        goto LABEL_30;
      }
      ++ItemID;
      if (!CHECK_REP(8, 0))
      {
LABEL_31:
        v21 = CHECK_REP(11, 0);
        if (!v21)
          goto LABEL_32;
        goto LABEL_69;
      }
LABEL_66:
      ItemID -= 10;
      v38 = CHECK_REP(11, 0);
      if (!v38)
      {
LABEL_32:
        goto LABEL_33;
      }
LABEL_69:
      ItemID += 10;
LABEL_33:
      if (ItemNum <= ItemNumMax)
      {
        goto LABEL_35;
      }
      ItemNum = ItemNumMax;
LABEL_35:
      if (ItemID > 0)
      {
        goto LABEL_37;
      }
      ItemID = 1;
LABEL_37:
      if (ItemID < 768)
        goto LABEL_106;
      ItemID = 767;
      goto LABEL_106;
    }
    if (CHECK_TRIG(6, 0))
    {
      v29 = ItemNum - 1;
      ItemNum = v29;
      if (v29 < 0)
      {
        ItemNum = 0;
      }
    }
    v30 = CHECK_TRIG(7, 0);
    if (v30)
    {
      ++ItemNum;
LABEL_54:
      v32 = ItemNumMax;
      if (ItemNum <= v32)
        goto LABEL_55;
      goto LABEL_88;
    }
    {
      goto LABEL_54;
    }
    v32 = ItemNumMax;
    if (ItemNum <= v32)
    {
LABEL_55:
      goto LABEL_56;
    }
LABEL_88:
    v32 = ItemNumMax;
    ItemNum = v32;
LABEL_56:
    if (ItemNum >= 1)
    {
      ItemGet = 1;
      goto LABEL_106;
    }
    ItemGet = 0;
    goto LABEL_106;
  }
  v26 = ItemNumMax;
  if (ItemNum <= v26)
  {
    goto LABEL_43;
  }
  v26 = ItemNumMax;
  ItemNum = v26;
LABEL_43:
  if (!ItemGet)
    goto LABEL_106;
  v39 = CHECK_TRIG(4096, 0);
  if (v39)
  {
    v41 = ItemID;
    datAddItem(v41, ItemNum);
  }
LABEL_106:
  v43 = ItemID;
  v44 = sdatItemName(v43);
  ItemName = v44;
  v46 = NowMenuListID;
  v85.r = 1.0;
  v85.g = 1.0;
  v85.b = 1.0;
  v85.a = 1.0;
  SetTextPartsDataList(20.0, (f32)(32 * v46 + 52), 150.0, 32.0, v85, "＞", 0);
  v47 = ToString((u32)ItemDebugMenu->static_fields + 4, 0);
  v48 = Concat_54766928("アイテムID = ", v47, 0);
  v50 = NowMenuListID;
  v51 = 1.0;
  if (v50)
    v52 = 20;
  else
    v52 = 44;
  v86.r = 1.0;
  v86.g = 1.0;
  v86.b = 1.0;
  v86.a = 1.0;
  SetTextPartsDataList((f32)v52, 52.0, 270.0, 32.0, v86, v48, 0);
  v53 = ToString((u32)ItemDebugMenu->static_fields + 8, 0);
  v54 = Concat_54766928("欲しい個数 = ", v53, 0);
  v58 = NowMenuListID;
  v87.r = 1.0;
  if (v58 == 1)
    v59 = 44;
  else
    v59 = 20;
  v87.g = 1.0;
  v87.b = 1.0;
  v87.a = 1.0;
  SetTextPartsDataList((f32)v59, 84.0, 270.0, 32.0, v87, v54, 0);
  if (!ItemNum)
    v51 = 0.5;
  v60 = "入手";
  v62 = NowMenuListID;
  v88.r = v51;
  if (v62 == 2)
    v63 = 44;
  else
    v63 = 20;
  v88.g = v51;
  v88.b = v51;
  v88.a = 1.0;
  SetTextPartsDataList((f32)v63, 116.0, 270.0, 32.0, v88, v60, 0);
  v64 = NewSpecific(string, 8u);
  v65 = "アイテム名 = ";
  v66 = v64;
  v64[0] = "アイテム名 = ";
  v66[1] = ItemName;
  v68 = "\n最大で持てる個数 = ";
  v66[2] = "\n最大で持てる個数 = ";
  v69 = ItemID;
  NowMenuListID_local = datGetItemMaxNum(v69);
  v70 = ToString((s32)&NowMenuListID_local, 0);
  v66[3] = v70;
  v71 = "\n今の所持数 = ";
  v66[4] = "\n今の所持数 = ";
  v72 = ToString((s32)&v84, 0);
  v66[5] = v72;
  v73 = "\n入手できる個数";
  v66[6] = "\n入手できる個数";
  v74 = ToString((u32)ItemDebugMenu->static_fields + 24, 0);
  v66[7] = v74;
  v75 = Concat_54832608(v66, 0);
  v79 = NowMenuListID;
  v89.r = 1.0;
  if (v79 == 3)
    v80 = 44;
  else
    v80 = 20;
  v89.g = 1.0;
  v89.b = 1.0;
  v89.a = 1.0;
  SetTextPartsDataList((f32)v80, 158.0, 510.0, 32.0, v89, v75, 0);
  v81 = 0;
  if (CHECK_TRIG(1, 0))
  {
    v81 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
    _ctor(v81, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
  }
  return v81;
}

// 0x1a37ef0
void TextDraw(s32 panelNo, s32 TextPosX, s32 TextPosY, s32 TextSizeW, s32 TextSizeH, const sdfColor_t *col, char *str) {
  f32 a;
  f32 b;
  f32 g;
  f32 r;
  s32 v23;
  sdfColor_t v24;

  a = col->a;
  b = col->b;
  g = col->g;
  r = col->r;
  v24.b = b;
  v24.a = a;
  if (NowMenuListID + 1 == panelNo)
    v23 = TextPosX + 24;
  else
    v23 = TextPosX;
  v24.r = r;
  v24.g = g;
  SetTextPartsDataList((f32)v23, (f32)(TextPosY + 32 * panelNo), (f32)TextSizeW, (f32)TextSizeH, v24, str, 0);
}
