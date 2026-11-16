#include "types.h"
#include "dds3_pad.h"
#include "fclmenu.h"
#include "itf.h"
#include "shpaction.h"
#include "shpmain.h"

typedef struct itfMover_t itfMover_t;
typedef struct itfSprList_t itfSprList_t;

static void *wk;
static itfSprList_t *fclMenuSprListPanel;
static itfSprList_t *fclMenuSprListPanelSelect;
static itfSprList_t *fclMenuSprListTitle;
static itfSprList_t *fclMenuSprListCursor;
static f32 fclMoverSetDisapper_fx;
static f32 fclMoverSetDisapper_fy;
static f32 fclMenuDraw_fx;
static f32 fclMenuDraw_fy;

static u8 CalcAlpha(itfMover_t *mv);
static bool MoverUpdate(void);
static void MoverSetApper(void);
static void MoverSetDisapper(void);
static bool _SetParam(void *cb, s16 a_id, s16 a_type, s16 a_parentId, bool a_bSelect, bool a_bDrawTitle, s32 a_posx, s32 a_posy, char *a_str);
static void *GetMenu(s32 a_hierarchy, s32 a_no);
static void *GetSelectMenu(void);
static void UpdateTargetMenu(void);
static void UniSetMenuStat(void);
static void UniSetText(void);
static void UpdateNextLink(void);
static void UpdatePrevLink(void);
static void Init(void);
static void LoadFile(void);
static void Select(void);
static void DrawSpriteAlpha(s32 a_x, s32 a_y, s32 a_z, s32 a_alpha, s32 a_sprNo);
static void DrawSpriteList(s32 a_x, s32 a_y, s32 a_z, s32 a_alpha, itfSprList_t *a_list);
static void DrawFontAlpha(s32 a_x, s32 a_y, u8 a_alpha, s8 a_attr, char *a_str);
static void DrawPanel(s32 a_x, s32 a_y, u8 a_alpha, s8 a_attr, char *a_str);
static void DrawTitle(s32 a_x, s32 a_y, u8 a_alpha, char *a_str);
static void DrawCursor(s32 a_x, s32 a_y, u8 a_alpha);
static void DrawCursorSelect(s32 a_x, s32 a_y, u8 a_alpha);

// 0x1b34ec0
void fclAnimFunc(s32 mode) {
  if (mode == 1)
  {
    KnyMainMenuAnimSet(shpUIManager, 2, 0);
  }
  else if (!mode)
  {
    if (MenuActive)
    {
      KnyMainMenuAnimSet(shpUIManager, 3, 0);
    }
    else
    {
      KnyMainMenuAnimSet(shpUIManager, 0, 0);
      MenuActive = 1;
    }
  }
}

// 0x1b34ff0
static u8 CalcAlpha(itfMover_t *mv) {
  s32 flags;

  flags = wk->flags;
  if ((flags & 0x10000) == 0)
    return (s32)255.0;
  if ((flags & 8) == 0)
  {
    return (s32)(f32)(255.0 - (f32)(itfMoverGetRatio(mv) * 255.0));
  }
  return (s32)(f32)(itfMoverGetRatio(mv) * 255.0);
}

// 0x1b35130
static bool MoverUpdate(void) {
  u64 v1;
  char i;
  itfMover_t *mover;
  itfMover_t *v8;

  v1 = 0;
  for (i = 0; ; i |= itfMoverUpdate(mover) == 1)
  {
    if (v1 >= wk->nMenuSet)
      break;
    mover = wk->menu[v1]->mover;
    ++v1;
  }
  v8 = wk->title->mover;
  itfMoverUpdate(v8);
  return i & 1;
}

// 0x1b35280
void fclSetApperTitle(void) {
  itfMover_t *mover;
  s32 ShopType;

  mover = wk->title->mover;
  itfMoverSetParam(mover, 93, 27, 93, 27, 10);
  ShopType = shpGetShopType();
  TitleAnimSet(shpUIManager, ShopType, 1, 0);
  wk->flags |= 0x30008u;
}

// 0x1b353e0
static void MoverSetApper(void) {
  s64 i;
  void *wk_local;
  s64 v6;
  void *v7;
  itfMover_t *v9;
  s32 v10;
  itfMover_t *mover;
  void *v14;
  s32 flags;

  fclAnimFunc(0);
  for (i = 4; ; ++i)
  {
    wk_local = wk;
    if (i - 4 >= (u64)wk_local->nMenuSet)
      break;
    v6 = *((u64 *)&wk_local->menu->obj.klass + i);
    if (*(u8 *)(v6 + 21) == (u8)wk_local->nowHierarchy)
      goto LABEL_15;
    goto LABEL_9000;
    if (*(u8 *)(v6 + 21) == (u8)v7->nowHierarchy)
    {
LABEL_15:
      v9 = *(itfMover_t *)(v6 + 64);
      v10 = *(char *)(v6 + 20);
      itfMoverSetParam(v9, 47, 88, 47, 26 * v10 + 88, 10);
      continue;
    }
LABEL_9000:
  }
  mover = wk->title->mover;
  itfMoverSetParam(mover, 93, 27, 93, 27, 10);
  v14 = wk;
  flags = v14->flags;
  v14->cntCursor = 0;
  v14->flags = flags | 0x10008;
}

// 0x1b35610
void fclSetDisapperTitle(void) {
  itfMover_t *mover;
  void *shpUIManager_local;
  s32 ShopType;

  mover = wk->title->mover;
  itfMoverSetParam(mover, 93, 27, 93, 27, 10);
  wk->flags = wk->flags
                                                            & 0xFFFCFFF7
                                                            | 0x30000;
  shpUIManager_local = shpUIManager;
  ShopType = shpGetShopType();
  TitleAnimSet(shpUIManager_local, ShopType, 2, 0);
}

// 0x1b35760
static void MoverSetDisapper(void) {
  s64 i;
  s32 v8;
  s32 v9;
  void *wk_local;
  s64 v13;
  itfMover_t *v15;
  itfMover_t *mover;
  f32 v19;
  f32 v20;
  s32 v21;
  s32 v22;

  KnyMainMenuAnimSet(shpUIManager, 2, 0);
  for (i = 4; ; ++i)
  {
    wk_local = wk;
    if (i - 4 >= (u64)wk->nMenuSet)
      break;
    v13 = *((u64 *)&wk_local->menu->obj.klass + i);
    if (*(u8 *)(v13 + 21) != (u8)wk_local->nowHierarchy)
      continue;
    v15 = *(itfMover_t *)(v13 + 64);
    itfMoverGetPosition(v15, &fclMoverSetDisapper_fx, &fclMoverSetDisapper_fy);
    if (fclMoverSetDisapper_fx == INFINITY)
      v8 = 0x80000000;
    else
      v8 = fclMoverSetDisapper_fx;
    if (fclMoverSetDisapper_fy == INFINITY)
      v9 = 0x80000000;
    else
      v9 = fclMoverSetDisapper_fy;
    itfMoverSetParam(v15, v8, v9, v8, 88, 10);
  }
  mover = wk_local->title->mover;
  itfMoverGetPosition(mover, &fclMoverSetDisapper_fx, &fclMoverSetDisapper_fy);
  v19 = fclMoverSetDisapper_fx;
  v20 = fclMoverSetDisapper_fy;
  if (v19 == INFINITY)
    v21 = 0x80000000;
  else
    v21 = v19;
  if (v20 == INFINITY)
    v22 = 0x80000000;
  else
    v22 = v20;
  itfMoverSetParam(mover, v21, v22, 93, 27, 10);
  wk->flags = wk->flags
                                                            & 0xFFFEFFF7
                                                            | 0x10000;
}

// 0x1b35a80
static bool _SetParam(void *cb, s16 a_id, s16 a_type, s16 a_parentId, bool a_bSelect, bool a_bDrawTitle, s32 a_posx, s32 a_posy, char *a_str) {
  if (cb)
  {
    cb->str = a_str;
    cb->id = a_id;
    cb->type = a_type;
    *(u16 *)&cb->no = -1;
    cb->parentId = a_parentId;
    cb->flags = 0;
    cb->posx = a_posx;
    cb->posy = a_posy;
    if (a_bDrawTitle)
      cb->flags |= 0x10u;
    if (a_bSelect)
      cb->flags |= 1u;
  }
  return cb != 0;
}

// 0x1b35b10
void fclSetParamTitle(char *a_str) {
  void *title;
  char **p_str;

  goto LABEL_3;
LABEL_7:
  title = wk->title;
  if (!title)
    return;
  title->str = a_str;
  p_str = &title->str;
  *(p_str - 4) = 0xFFFFFFFF0000FFFFLL;
  *((u32 *)p_str - 6) = 0;
  *(p_str - 1) = 0;
  return;
LABEL_3:
  if (wk)
    goto LABEL_7;
}

// 0x1b35bf0
bool fclSetParamFull(s16 a_id, s16 a_type, s16 a_parentId, bool a_bSelect, bool a_bDrawTitle, s32 a_posx, s32 a_posy, char *a_str) {
  u32 nMenuSet;
  _BOOL4 v20;
  void *v21;

  nMenuSet = wk->nMenuSet;
  v20 = a_id >= 0 && nMenuSet < wk->nMenuMax;
  if (v20)
  {
    nMenuSet = wk->nMenuSet;
    v21 = wk->menu[nMenuSet];
    if (v21)
    {
      v21->str = a_str;
      v21->id = a_id;
      v21->type = a_type;
      *(u16 *)&v21->no = -1;
      v21->parentId = a_parentId;
      v21->flags = 0;
      v21->posx = a_posx;
      v21->posy = a_posy;
      if (a_bDrawTitle)
        v21->flags |= 0x10u;
      if (a_bSelect)
        v21->flags |= 1u;
    }
    ++wk->nMenuSet;
  }
  return v20;
}

// 0x1b35d50
bool fclSetParam(s16 a_id, s16 a_parentId, bool a_bSelect, bool a_bDrawTitle, char *a_str) {
  return fclSetParamFull(a_id, 1, a_parentId, a_bSelect, a_bDrawTitle, 0, 0, a_str);
}

// 0x1b35e00
bool fclSetFlagSelect(s16 a_id, bool a_bSelect) {
  u64 v6;
  s32 v7;
  void *v8;
  u64 v9;
  u64 nMenuSet;
  u32 v13;

  v6 = 0;
  v7 = a_id;
  while (1)
  {
    v9 = v6;
    nMenuSet = wk->nMenuSet;
    if (v6 >= nMenuSet)
      break;
    ++v6;
    v8 = wk->menu[v9];
    if ((u16)v8->id == v7)
    {
      if (a_bSelect)
      {
        v8 = *(&wk->menu->max_length + v6);
        v13 = v8->flags | 1;
      }
      else
      {
        v8 = *(&wk->menu->max_length + v6);
        v13 = v8->flags & 0xFFFFFFFE;
      }
      v8->flags = v13;
      return v9 < nMenuSet;
    }
  }
  return v9 < nMenuSet;
}

// 0x1b35f30
bool fclSetFlagDecideEnd(s16 a_id) {
  u64 v4;
  s32 v5;
  void *v6;
  u64 v7;
  u64 nMenuSet;

  v4 = 0;
  v5 = a_id;
  while (1)
  {
    v7 = v4;
    nMenuSet = wk->nMenuSet;
    if (v4 >= nMenuSet)
      break;
    ++v4;
    v6 = wk->menu[v7];
    if ((u16)v6->id == v5)
    {
      v6 = *(&wk->menu->max_length + v4);
      v6->flags |= 0x20u;
      return v7 < nMenuSet;
    }
  }
  return v7 < nMenuSet;
}

// 0x1b36030
bool fclSetCursor(s16 a_id, s32 a_x, s32 a_y, s32 a_model) {
  u64 v10;
  s32 v11;
  void *v12;
  u64 v13;
  u64 nMenuSet;
  s32 flags;

  v10 = 0;
  v11 = a_id;
  while (1)
  {
    v13 = v10;
    nMenuSet = wk->nMenuSet;
    if (v10 >= nMenuSet)
      break;
    ++v10;
    v12 = wk->menu[v13];
    if ((u16)v12->id == v11)
    {
      v12 = *(&wk->menu->max_length + v10);
      flags = v12->flags;
      v12->posx = a_x;
      v12->posy = a_y;
      v12->modelID = a_model;
      v12->flags = flags | 4;
      return v13 < nMenuSet;
    }
  }
  return v13 < nMenuSet;
}

// 0x1b36150
static void *GetMenu(s32 a_hierarchy, s32 a_no) {
  s32 v6;
  s64 i;
  void *wk_local;
  void *v9;

  v6 = 0;
  for (i = 4; ; ++i)
  {
    wk_local = wk;
    if (i - 4 >= (u64)wk_local->nMenuSet)
      return 0;
    v9 = *((void *)&wk_local->menu->obj.klass + i);
    if (v9->hierarchy == a_hierarchy)
      goto LABEL_13;
LABEL_5:
    ;
  }
  v9 = *((void *)&wk->menu->obj.klass + i);
  if (v9->hierarchy != a_hierarchy)
    goto LABEL_5;
LABEL_13:
  if (v6 != a_no)
  {
    ++v6;
    goto LABEL_5;
  }
  return v9;
}

// 0x1b36290
static void *GetSelectMenu(void) {
  return GetMenu(wk->nowHierarchy, wk->selNo[wk->nowHierarchy]);
}

// 0x1b36300
static void UpdateTargetMenu(void) {
  void *wk_local;
  s64 i;
  void *v5;
  u8 *v6;
  void *v7;

  wk_local = wk;
  wk_local->target = 0;
  for (i = 4; ; ++i)
  {
    v7 = wk;
    if (i - 4 >= (u64)v7->nMenuSet)
      break;
    if (*(u8 *)(*((u64 *)&v7->menu->obj.klass + i) + 21) != (u8)v7->nowHierarchy)
      continue;
    v5 = wk;
    v6 = *((u8 **)&v5->menu->obj.klass + i);
    if (v6[20] == (u8)v5->selNo[v5->nowHierarchy])
    {
      v5 = wk;
      v6 = *((u8 **)&v5->menu->obj.klass + i);
      v5->target = (void *)v6;
      return;
    }
  }
}

// 0x1b36480
s32 getTarget(void) {
  return wk->target->parentId;
}

// 0x1b364f0
static void UniSetMenuStat(void) {
  s32 i;
  s8 selMax;
  s32 j;

  for (i = 0; ; ++i)
  {
    if (i >= wk->selMax)
      break;
    MenuListSetState(shpUIManager, i, 1, 0);
  }
  selMax = wk->selMax;
  if (MenuListCount(shpUIManager, 0) > selMax)
  {
    for (j = wk->selMax; ; ++j)
    {
      if (j >= MenuListCount(shpUIManager, 0))
        break;
      MenuListSetState(shpUIManager, j, 0, 0);
    }
  }
}

// 0x1b366a0
static void UniSetText(void) {
  s64 v3;
  s32 v4;
  s64 i;
  s32 v11;

  if (wk->nowHierarchy == 1)
  {
    v3 = wk->nMenuSet - (s64)wk->selMax;
    goto LABEL_10;
  }
  v3 = 0;
LABEL_10:
  v4 = 0;
  for (i = v3 + 4; ; ++i)
  {
    if (i - 4 >= wk->nMenuSet)
      break;
    if (v4 >= MenuListCount(shpUIManager, 0))
      break;
    if (*(u8 *)(*((u64 *)&wk->menu->obj.klass + i) + 20) != 255)
    {
      TextSetStr(shpUIManager, v4, *(char **)(*((u64 *)&wk->menu->obj.klass + i) + 48), 0);
      if (v4 != wk->selNo[wk->nowHierarchy])
      {
        CursorSetState(shpUIManager, v4, 0, 0);
        v11 = 0;
        goto LABEL_42;
      }
      CursorSetState(shpUIManager, v4, 1, 0);
      if ((*(u8 *)(*((u64 *)&wk->menu->obj.klass + i) + 24) & 1) == 0)
        goto LABEL_30;
      v11 = 1;
LABEL_42:
      TextMode(shpUIManager, v4, v11, 0);
      if ((*(u8 *)(*((u64 *)&wk->menu->obj.klass + i) + 24) & 1) == 0)
        goto LABEL_44;
      goto LABEL_12;
LABEL_30:
      if ((*(u8 *)(*((u64 *)&wk->menu->obj.klass + i) + 24) & 1) == 0)
      {
LABEL_44:
        TextMode(shpUIManager, v4, 2, 0);
      }
LABEL_12:
      ++v4;
      continue;
    }
  }
}

// 0x1b36a00
static void UpdateNextLink(void) {
  s32 id;
  s64 v5;
  void *v7;
  s8 selMax;
  void *wk_local;
  s64 v11;

  id = (u16)GetMenu(wk->nowHierarchy, wk->selNo[wk->nowHierarchy])->id;
  v5 = 4;
  wk->selMax = 0;
  while (1)
  {
    wk_local = wk;
    if (v5 - 4 >= (u64)wk_local->nMenuSet)
      break;
    v11 = *((u64 *)&wk_local->menu->obj.klass + v5);
    *(u8 *)(v11 + 20) = -1;
    if (*(u16 *)(v11 + 22) == id)
    {
      v7 = wk;
      selMax = v7->selMax;
      *(u8 *)(*((u64 *)&v7->menu->obj.klass + v5) + 20) = selMax;
      v7->selMax = selMax + 1;
    }
    ++v5;
  }
  wk_local = wk;
  ++wk_local->nowHierarchy;
  UpdateTargetMenu();
}

// 0x1b36bc0
static void UpdatePrevLink(void) {
  s32 parentId;
  u64 v5;
  s32 v6;
  s64 v8;
  s64 v9;
  s64 v11;
  void *v12;
  s8 selMax;
  void *v15;
  s64 v16;

  parentId = (u16)GetMenu(wk->nowHierarchy, wk->selNo[wk->nowHierarchy])->parentId;
  v5 = 0;
  v6 = -1;
  while (1)
  {
    if (v5 >= wk->nMenuSet)
      break;
    v8 = (s64)wk->menu + 8 * v5++;
    v9 = *(u64 *)(v8 + 32);
    if (*(u16 *)(v9 + 16) == parentId)
    {
      v9 = *(&wk->menu->max_length + v5);
      v6 = *(s16 *)(v9 + 22);
      break;
    }
  }
  v11 = 4;
  wk->selMax = 0;
  while (1)
  {
    v15 = wk;
    if (v11 - 4 >= (u64)v15->nMenuSet)
      break;
    v16 = *((u64 *)&v15->menu->obj.klass + v11);
    *(u8 *)(v16 + 20) = -1;
    if (v6 == *(s16 *)(v16 + 22))
    {
      v12 = wk;
      selMax = v12->selMax;
      *(u8 *)(*((u64 *)&v12->menu->obj.klass + v11) + 20) = selMax;
      v12->selMax = selMax + 1;
    }
    ++v11;
  }
  v15 = wk;
  v15->selNo[v15->nowHierarchy] = 0;
  --wk->nowHierarchy;
  UpdateTargetMenu();
}

// 0x1b36e50
void fclSetLink(void) {
  s64 v2;
  void *wk_local;
  u64 *v4;
  void *v6;
  s64 v7;
  s32 v8;
  s32 selMax;
  u64 i;
  void *v12;
  s64 j;
  void *v14;
  void *menu;
  s64 v16;
  u16 *v17;
  void *v18;
  u64 k;
  void *v20;
  s64 m;
  void *v22;
  void *v23;
  s64 v24;
  u16 *v25;
  void *v26;
  u64 n;
  u32 v28;
  void *v29;
  s64 ii;
  void *v31;
  void *v32;
  s64 v33;
  u16 *v34;
  void *v35;

  v2 = 4;
  wk->selMax = 0;
  while (1)
  {
    wk_local = wk;
    if (v2 - 4 >= (u64)wk_local->nMenuSet)
      break;
    wk_local = wk;
    v4 = *((u64 **)&wk_local->menu->obj.klass + v2);
    v4[4] = 0;
    v4 += 4;
    *((u16 *)v4 - 6) = -1;
    v6 = wk;
    v7 = *((u64 *)&v6->menu->obj.klass + v2);
    *(u32 *)(v7 + 24) &= ~2u;
    v8 = *(u16 *)(v7 + 22);
    if (v8 == 0xFFFF)
    {
      selMax = (u8)v6->selMax;
      *(u16 *)(v7 + 20) = (u8)selMax;
      if (!selMax)
      {
        v6 = wk;
        v7 = *((u64 *)&v6->menu->obj.klass + v2);
        v6->target = (void *)v7;
      }
      ++wk->selMax;
      goto LABEL_7;
    }
    if (*(u16 *)(v7 + 16) != v8)
      goto LABEL_7;
    v7 = *((u64 *)&wk->menu->obj.klass + v2);
    *(u16 *)(v7 + 20) = 255;
LABEL_7:
    ++v2;
  }
  for (i = 0; ; ++i)
  {
    v12 = wk;
    if (i >= v12->nMenuSet)
      break;
    if (v12->menu[i]->hierarchy)
      continue;
    for (j = 4; ; ++j)
    {
      if (j - 4 >= (u64)wk->nMenuSet)
        break;
      menu = wk->menu;
      v16 = *((u64 *)&menu->obj.klass + j);
      v17 = menu[i];
      if (*(u16 *)(v16 + 22) == v17[8])
      {
        v18 = wk->menu;
        v16 = *((u64 *)&v18->obj.klass + j);
        v17 = v18[i];
        *(u64 *)(v16 + 32) = v17;
        *(u8 *)(v16 + 21) = 1;
        v14 = wk->menu[i];
        v14->flags |= 2u;
      }
    }
  }
  for (k = 0; ; ++k)
  {
    v20 = wk;
    if (k >= v20->nMenuSet)
      break;
    if (v20->menu[k]->hierarchy != 1)
      continue;
    for (m = 4; ; ++m)
    {
      if (m - 4 >= (u64)wk->nMenuSet)
        break;
      v23 = wk->menu;
      v24 = *((u64 *)&v23->obj.klass + m);
      v25 = v23[k];
      if (*(u16 *)(v24 + 22) == v25[8])
      {
        v26 = wk->menu;
        v24 = *((u64 *)&v26->obj.klass + m);
        v25 = v26[k];
        *(u64 *)(v24 + 32) = v25;
        *(u8 *)(v24 + 21) = 2;
        v22 = wk->menu[k];
        v22->flags |= 2u;
      }
    }
  }
  for (n = 0; ; ++n)
  {
    v29 = wk;
    if (n >= v29->nMenuSet)
      break;
    if (v28)
    {
      if (v29->menu[n]->hierarchy != 2)
        continue;
    }
    else
    {
      if (wk->menu[n]->hierarchy != 2)
        continue;
    }
    for (ii = 4; ; ++ii)
    {
      if (ii - 4 >= (u64)wk->nMenuSet)
        break;
      v32 = wk->menu;
      v33 = *((u64 *)&v32->obj.klass + ii);
      v34 = v32[n];
      if (*(u16 *)(v33 + 22) == v34[8])
      {
        v35 = wk->menu;
        v33 = *((u64 *)&v35->obj.klass + ii);
        v34 = v35[n];
        *(u64 *)(v33 + 32) = v34;
        *(u8 *)(v33 + 21) = 3;
        v31 = wk->menu[n];
        v31->flags |= 2u;
      }
    }
  }
  if (!v28)
  {
    v29 = wk;
  }
  v29->flags |= 2u;
}

// 0x1b37480
void fclStartUpdate(void) {
  s32 ShopType;
  void *v6;
  s32 v7;
  s32 v11;

  ShopType = shpGetShopType();
  if (ShopType == 1)
  {
    MilkTitleAnim(shpUIManager, 1, 0);
    v11 = shpGetShopType();
    SetBackSetActive(shpUIManager, v11, 0, 0);
    MilkBackAnim(shpUIManager, 1, 0);
    goto LABEL_14;
  }
  if (!ShopType)
  {
    wk->nowHierarchy = 0;
    KnyTitleAnim(shpUIManager, 1, 0);
    v6 = shpUIManager;
    v7 = shpGetShopType();
    SetBackSetActive(v6, v7, 0, 0);
    KnyBackAnim(shpUIManager, 1, 0);
    MilkMenuObjActiveCtrl(shpUIManager, 0, 0);
  }
LABEL_14:
  wk->flags |= 4u;
}

// 0x1b376a0
s16 fclGetSelectId(void) {
  if (wk->step != 5)
    return -2;
  if ((wk->nowHierarchy & 0x80000000) != 0)
    return -1;
  return wk->target->id;
}

// 0x1b37790
s16 fclGetSelectIdEx(void) {
  if (wk->nowHierarchy < 0)
    return -1;
  return wk->target->id;
}

// 0x1b37840
s32 fclGetHierarchy(void) {
  if (!wk)
    return -1;
  return wk->nowHierarchy;
}

// 0x1b378f0
void fclSetTargetId(s16 a_id) {
  u64 v4;
  s64 v5;
  s64 v6;
  void *wk_local;
  s32 v8;
  s64 v9;
  void *v10;
  s8 selMax;
  void *v13;
  s64 v14;
  s64 v16;
  s64 v17;

  v4 = 0;
  while (1)
  {
    wk_local = wk;
    if (v4 >= wk_local->nMenuSet)
      break;
    wk_local = wk;
    v5 = (s64)wk_local->menu + 8 * v4++;
    v6 = *(u64 *)(v5 + 32);
    if (*(u16 *)(v6 + 16) == (u16)a_id)
    {
      wk_local = wk;
      v6 = *(&wk_local->menu->max_length + v4);
      v8 = *(u16 *)(v6 + 22);
      wk_local->selMax = 0;
      v9 = 4;
      while (2)
      {
        v13 = wk;
        if (v9 - 4 >= (u64)v13->nMenuSet)
        {
          v13 = wk;
          v16 = *(&v13->menu->max_length + v4);
          v17 = *(char *)(v16 + 21);
          LOBYTE(v16) = *(u8 *)(v16 + 20);
          v13->nowHierarchy = v17;
          v13->selNo[v17] = v16;
          UpdateTargetMenu();
          wk->flags |= 0x20000u;
          return;
        }
        v14 = *((u64 *)&v13->menu->obj.klass + v9);
        *(u8 *)(v14 + 20) = -1;
        if (*(u16 *)(v14 + 22) == v8)
        {
          v10 = wk;
          selMax = v10->selMax;
          *(u8 *)(*((u64 *)&v10->menu->obj.klass + v9) + 20) = selMax;
          v10->selMax = selMax + 1;
        }
        ++v9;
        continue;
      }
    }
  }
}

// 0x1b37af0
u8 fclGetTitleAlphaRate(void) {
  itfMover_t *mover;
  s32 flags;

  mover = wk->title->mover;
  if (!mover)
    return 0;
  flags = wk->flags;
  if ((flags & 0x200) == 0)
    return 0;
  if ((flags & 0x20000) == 0)
    return -1;
  return CalcAlpha(mover);
}

// 0x1b37c10
static void Init(void) {
  void *wk_local;
  void *v4;

  wk_local = wk;
  wk_local->target = 0;
  v4 = wk;
  *(u64 *)&v4->frame = 0;
  v4->flags = 0;
  v4->nowHierarchy = 0;
  v4->nMenuSet = 0;
  v4->selNo[0] = 0;
  wk->selNo[1] = 0;
  wk->selNo[2] = 0;
  wk->selNo[3] = 0;
}

// 0x1b37d40
static void LoadFile(void) {
  void *wk_local;
  sprHandle_t *v3;

  wk_local = wk;
  v3 = Allocate(sprHandle_t);
  _ctor(v3, 0);
  wk_local->phSpr = v3;
}

// 0x1b37dd0
static void Select(void) {
  s32 v2;
  _BOOL4 v4;
  s8 v8;
  char v9;
  s32 selMax;

  v2 = (u8)wk->selNo[wk->nowHierarchy];
  if (CHECK_TRIG(4100, 1))
  {
    LOBYTE(v2) = v2 - 1;
    if ((v2 & 0x80) != 0)
    {
      LOBYTE(v2) = wk->selMax - 1;
    }
    v4 = 1;
    goto LABEL_12;
  }
  if (CHECK_REP(4100, 1))
  {
    v9 = v2 - 1;
    if (((v2 - 1) & 0x80) != 0)
      LOBYTE(v2) = 0;
    else
      LOBYTE(v2) = v2 - 1;
    v4 = (v9 & 0x80) == 0;
LABEL_12:
    wk->selNo[wk->nowHierarchy] = v2;
    if (CHECK_TRIG(4101, 1))
      goto LABEL_13;
LABEL_27:
    if (!CHECK_REP(4101, 1))
    {
LABEL_29:
      UpdateTargetMenu();
      if (!v4)
        return;
      goto LABEL_30;
    }
    v8 = v2 + 1;
    selMax = wk->selMax;
    if (selMax > v8)
    {
      v4 = 1;
LABEL_40:
      goto LABEL_41;
    }
    LOBYTE(selMax) = wk->selMax;
    v8 = selMax - 1;
    goto LABEL_40;
  }
  v4 = 0;
  if (!CHECK_TRIG(4101, 1))
    goto LABEL_27;
LABEL_13:
  if (wk->selMax <= (char)(v2 + 1))
    v8 = 0;
  else
    v8 = v2 + 1;
  v4 = 1;
LABEL_41:
  wk->selNo[wk->nowHierarchy] = v8;
  goto LABEL_29;
  if (v4)
LABEL_30:
    SE(3);
}

// 0x1b38050
s16 fclUpdate(void) {
  s32 flags;
  void *v7;
  s32 v8;
  s32 v9;
  s32 ShopType;
  s32 v13;
  char v15;
  u32 v17;
  void *v18;
  s32 ctrlType;
  u32 v20;
  void *v22;
  s32 v23;
  void *target;
  s32 v25;
  u32 v26;
  u32 v27;
  bool v28;
  u32 v29;
  s32 v30;
  void *v31;
  u32 v33;
  s32 v34;
  u32 v35;
  void *v36;
  s32 v37;
  s32 v39;

  if (!wk)
    return -3;
  switch (wk->step)
  {
    case 0:
    case 1:
    case 2:
      flags = wk->flags;
      if ((flags & 2) != 0)
      {
        flags = wk->flags;
        if ((flags & 4) != 0)
        {
          wk->step = 3;
          MoverSetApper();
          wk->flags |= 0x20700u;
        }
      }
      goto LABEL_76;
    case 3:
      if (MoverUpdate())
        goto LABEL_76;
      if (CHECK_TRIG(4097, 1))
      {
        v7 = wk;
        if (v7->nowHierarchy >= 1)
          goto LABEL_26;
        goto LABEL_95;
      }
      v28 = CHECK_TRIG(4096, 1);
      if (v28)
      {
        v7 = wk;
        v30 = v7->target->flags;
        if ((v30 & 0x20) != 0)
        {
          if (!v29)
          {
            v7 = wk;
          }
          if (v7->nowHierarchy >= 1)
          {
LABEL_26:
            v7 = wk;
            v8 = 1;
            v9 = v7->flags;
            v7->ctrlType = 1;
            v7->flags = v9 & 0xFFFDFFFF;
            goto LABEL_30;
          }
LABEL_95:
          v7 = wk;
          v8 = 2;
          v7->ctrlType = 3;
          v7->flags |= 0x20000u;
LABEL_30:
          ShopType = shpGetShopType();
          shpTalkTitleSet(v8, ShopType);
          MoverSetDisapper();
          v13 = 1;
LABEL_33:
          SE(v13);
          v15 = 4;
          goto LABEL_74;
        }
        if (!v29)
        {
          v7 = wk;
          v30 = v7->target->flags;
        }
        if ((v30 & 1) != 0)
        {
          LOBYTE(v34) = ~(u8)v30 & 2;
          goto LABEL_9001;
LABEL_102:
          v36 = wk;
          if ((v36->target->flags & 0x10) == 0)
          {
            if (!v35)
            {
              v36 = wk;
            }
            v37 = 2;
            v36->flags |= 0x20000u;
            goto LABEL_119;
          }
          if (!v35)
          {
            v36 = wk;
          }
          v37 = 1;
          v36->flags &= ~0x20000u;
LABEL_119:
          v39 = shpGetShopType();
          shpTalkTitleSet(v37, v39);
          MoverSetDisapper();
          v13 = 0;
          goto LABEL_33;
LABEL_9001:
          v7->ctrlType = v34;
          goto LABEL_102;
        }
      }
      Select();
LABEL_76:
      return fclGetSelectId();
    case 4:
      if (MoverUpdate())
        goto LABEL_76;
      v18 = wk;
      ctrlType = (u8)v18->ctrlType;
      if (!v18->ctrlType)
      {
        if (!v17)
        UpdateNextLink();
LABEL_73:
        MoverSetApper();
        v15 = 3;
LABEL_74:
        v31 = wk;
        goto LABEL_75;
      }
      if (!v17)
      {
        v18 = wk;
        ctrlType = (u8)v18->ctrlType;
      }
      if (ctrlType == 1)
      {
        if (!v20)
        UpdatePrevLink();
        goto LABEL_73;
      }
      if (!v20)
      {
        v18 = wk;
        ctrlType = (u8)v18->ctrlType;
      }
      if (ctrlType != 2)
      {
        if (!v33)
        {
          v18 = wk;
          ctrlType = (u8)v18->ctrlType;
        }
        if (ctrlType == 3)
        {
          v18 = wk;
          v18->flags = v18->flags & 0xFFFDF9FB | 0x20000;
          *(u16 *)&v18->step = -251;
        }
        goto LABEL_76;
      }
      if (v33)
      {
        if ((v18->target->flags & 0x10) == 0)
          goto LABEL_84;
      }
      else
      {
        v18 = wk;
        if ((v18->target->flags & 0x10) == 0)
        {
LABEL_84:
LABEL_85:
          v31 = wk;
          v31->flags = v31->flags & 0xFFFDF9FB | 0x20200;
          v15 = 5;
LABEL_75:
          v31->step = v15;
          goto LABEL_76;
        }
      }
      v18 = wk;
      v18->flags |= 8u;
      goto LABEL_85;
    case 5:
      MoverUpdate();
      v22 = wk;
      v23 = v22->flags;
      if ((v23 & 4) == 0)
        goto LABEL_76;
      v22 = wk;
      v23 = v22->flags;
      target = v22->target;
      v25 = v23 | 0x600;
      v22->flags = v25;
      if ((target->flags & 0x10) != 0)
      {
        if (!v26)
        {
          v22 = wk;
          v25 = v22->flags;
        }
        v27 = v25 & 0xFFFDFFFF;
      }
      else
      {
        if (!v26)
        {
          v22 = wk;
          v25 = v22->flags;
        }
        v27 = v25 | 0x20000;
      }
      v22->flags = v27;
      goto LABEL_73;
    default:
      goto LABEL_76;
  }
}

// 0x1b38730
static void DrawSpriteAlpha(s32 a_x, s32 a_y, s32 a_z, s32 a_alpha, s32 a_sprNo) {
  sprHandle_t *phSpr;

  phSpr = wk->phSpr;
  itfDrawMiscSpriteAlpha(a_x, a_y, a_z, a_alpha, phSpr, a_sprNo, 109);
}

// 0x1b38830
static void DrawSpriteList(s32 a_x, s32 a_y, s32 a_z, s32 a_alpha, itfSprList_t *a_list) {
  sprHandle_t *phSpr;

  phSpr = wk->phSpr;
  itfDrawMiscSpriteList(a_x, a_y, a_z, a_alpha, phSpr, 109, a_list);
}

// 0x1b38930
static void DrawFontAlpha(s32 a_x, s32 a_y, u8 a_alpha, s8 a_attr, char *a_str) {
  s64 v11;
  u32 v12;

  v11 = a_attr - 1;
  if ((u32)v11 > 2)
  {
    v12 = -1600273536;
  }
  else
  {
    v12 = dword_3E61E08[v11];
  }
  itfDrawMiscFontAlpha(a_x, a_y, 0x100000, v12, a_alpha, a_str);
}

// 0x1b38a00
static void DrawPanel(s32 a_x, s32 a_y, u8 a_alpha, s8 a_attr, char *a_str) {
  u32 v12;
  sprHandle_t *phSpr;
  s64 v17;
  u32 v18;
  sprHandle_t *v24;

  v12 = a_alpha;
  phSpr = wk->phSpr;
  itfDrawMiscSpriteList(a_x, a_y, 256, v12, phSpr, 109, fclMenuSprListPanel);
  if ((a_attr & 2) == 0)
  {
    goto LABEL_8;
  }
  v24 = wk->phSpr;
  itfDrawMiscSpriteList(a_x, a_y, 256, v12, v24, 109, fclMenuSprListPanelSelect);
LABEL_8:
  v17 = a_attr - 1;
  if ((u32)v17 <= 2)
  {
    v18 = dword_3E61E08[v17];
    goto LABEL_26;
  }
  v18 = -1600273536;
LABEL_26:
  itfDrawMiscFontAlpha(a_x + 10, a_y + 4, 0x100000, v18, a_alpha, a_str);
}

// 0x1b38d00
static void DrawTitle(s32 a_x, s32 a_y, u8 a_alpha, char *a_str) {
  u32 v12;
  sprHandle_t *phSpr;

  if ((wk->flags & 0x20000) == 0)
    a_alpha = -1;
  v12 = a_alpha;
  phSpr = wk->phSpr;
  itfDrawMiscSpriteList(a_x, a_y, 256, v12, phSpr, 109, fclMenuSprListTitle);
  itfDrawMiscFontAlpha(a_x - 64, a_y + 16, 0x100000, 0xA09DC380, a_alpha, a_str);
}

// 0x1b38ef0
static void DrawCursor(s32 a_x, s32 a_y, u8 a_alpha) {
  TalkModelCursorSetActive(shpUIManager, 1, 0);
  SetTalkModelCursor(shpUIManager, a_x, a_y, 0);
}

// 0x1b38f80
static void DrawCursorSelect(s32 a_x, s32 a_y, u8 a_alpha) {
  s32 cntCursor;
  u32 v9;
  s32 v11;
  bool v12;
  sprHandle_t *phSpr;

  cntCursor = wk->cntCursor;
  if (cntCursor < 1)
  {
LABEL_9:
    v9 = 0;
    goto LABEL_11;
  }
  if (cntCursor > 60)
    goto LABEL_9;
  cntCursor = wk->cntCursor;
  v9 = (u8)(s32)(f32)((f32)((f32)((f32)((f32)(60 - cntCursor) * 160.0) / 60.0) * (f32)a_alpha) / 255.0);
LABEL_11:
  v11 = wk->cntCursor + 1;
  v12 = wk->cntCursor - 60 < 0;
  wk->cntCursor = v11;
  if (v12 != __OFSUB__(v11, 61))
  {
    goto LABEL_14;
  }
  wk->cntCursor = 0;
LABEL_14:
  phSpr = wk->phSpr;
  itfDrawMiscSpriteAlpha(a_x - 11, a_y - 14, 256, v9, phSpr, 70, 109);
}

// 0x1b39200
u8 fclGetPanelAlpha(void) {
  s64 i;
  s64 v5;
  void *wk_local;
  itfMover_t *v7;

  if ((wk->flags & 0x400) != 0)
  {
    for (i = 4; ; ++i)
    {
      wk_local = wk;
      if (i - 4 >= (u64)wk_local->nMenuSet)
        return 0;
      if (*(u8 *)(*((u64 *)&wk_local->menu->obj.klass + i) + 21) != (u8)wk_local->nowHierarchy)
        continue;
      v5 = *((u64 *)&wk->menu->obj.klass + i);
      if (!*(u8 *)(v5 + 20))
      {
        v7 = *(itfMover_t *)(v5 + 64);
        return CalcAlpha(v7);
      }
    }
  }
  return 0;
}

// 0x1b39380
u8 fclGetTitleAlpha(void) {
  void *v6;
  itfMover_t *mover;

  if ((wk->flags & 0x200) == 0)
    return 0;
  if (wk->step == 5)
  {
    if ((wk->target->flags & 0x10) != 0)
      goto LABEL_17;
    return 0;
  }
LABEL_17:
  v6 = wk;
  if ((v6->flags & 0x20000) == 0)
    return -1;
  mover = v6->title->mover;
  return CalcAlpha(mover);
}

// 0x1b39500
void fclDraw(void) {
  u64 v3;
  s32 v4;
  void *v5;
  void *v7;
  itfMover_t *mover;
  s32 v14;
  itfMover_t *v15;
  s32 v16;
  u8 v18;
  void *v19;
  void *v20;
  s32 v21;
  s32 no;
  char flags;
  s32 v24;
  s32 v25;
  void *v26;
  s32 modelID;
  s32 v29;
  s32 v30;
  void *v34;
  void *pParent;
  void *p_title;
  u32 v38;
  char *str;
  itfMover_t *v41;
  f32 v44;
  f32 v45;
  s32 v46;
  itfMover_t *v47;
  s32 v48;
  u8 v49;
  s32 a_y;
  s32 x;

  x = 0;
  a_y = 0;
  if ((wk->flags & 0x100) == 0)
    return;
  if (wk->step < 3)
    return;
  if ((wk->flags & 0x400) != 0)
  {
    v3 = 0;
    v4 = 0;
    while (1)
    {
      v5 = wk;
      if (v3 >= v5->nMenuSet)
      {
        if (!v4)
        {
          TalkModelCursorSetActive(shpUIManager, 0, 0);
        }
        break;
      }
      v5 = wk;
      if (v5->menu[v3]->hierarchy != v5->nowHierarchy)
        goto LABEL_15;
      v7 = wk->menu[v3];
      if (v7->no < 0)
        goto LABEL_15;
      mover = v7->mover;
      itfMoverGetPosition(mover, &fclMenuDraw_fx, &fclMenuDraw_fy);
      v14 = fclMenuDraw_fx;
      v15 = wk->menu[v3]->mover;
      if (fclMenuDraw_fx == INFINITY)
        v14 = 0x80000000;
      x = v14;
      v16 = fclMenuDraw_fy;
      if (fclMenuDraw_fy == INFINITY)
        v16 = 0x80000000;
      a_y = v16;
      v18 = CalcAlpha(v15);
      v19 = wk;
      v20 = v19->menu[v3];
      v21 = (u8)v19->selNo[v19->nowHierarchy];
      no = (u8)v20->no;
      flags = v20->flags;
      v24 = x;
      v25 = a_y;
      DrawPanel(v24, v25, v18, (flags & 1 | (2 * (no == v21))) ^ 1, v20->str);
      v26 = wk->menu[v3];
      if ((v26->flags & 4) != 0 && no == v21)
      {
        modelID = v26->modelID;
        shpNpcGetCursorPos(modelID, &x, &a_y);
        v29 = x;
        v30 = a_y;
        TalkModelCursorSetActive(shpUIManager, 1, 0);
        SetTalkModelCursor(shpUIManager, v29, v30, 0);
        ++v4;
        DrawCursorSelect(x, a_y, v18);
        goto LABEL_15;
      }
LABEL_15:
      ++v3;
    }
  }
  v34 = wk;
  if ((v34->flags & 0x200) == 0)
    return;
  if (v34->step == 5)
    goto LABEL_57;
  v34 = wk;
  pParent = v34->target->pParent;
  if (!pParent)
  {
    if (!v38)
    {
      v34 = wk;
    }
    p_title = &v34->title;
    goto LABEL_71;
  }
  if (!v38)
  {
    p_title = &wk->target->pParent;
    goto LABEL_71;
  }
LABEL_72:
  str = pParent->str;
  v41 = wk->title->mover;
  itfMoverGetPosition(v41, &fclMenuDraw_fx, &fclMenuDraw_fy);
  v44 = fclMenuDraw_fx;
  v45 = fclMenuDraw_fy;
  v46 = v44;
  v47 = wk->title->mover;
  if (v44 == INFINITY)
    v46 = 0x80000000;
  x = v46;
  v48 = v45;
  if (v45 == INFINITY)
    v48 = 0x80000000;
  a_y = v48;
  v49 = CalcAlpha(v47);
  DrawTitle(x, a_y, v49, str);
  return;
LABEL_57:
  v34 = wk;
  pParent = v34->target;
  if ((pParent->flags & 0x10) != 0)
  {
    p_title = &wk->target;
LABEL_71:
    pParent = p_title;
    goto LABEL_72;
  }
}

// 0x1b39b70
void fclCreate(s32 a_nMenu) {
  void *v3;
  void *wk_local;
  void *v6;
  s64 v7;
  s64 v8;
  void *menu;
  void *v11;
  void *v15;
  sprHandle_t *v16;

  if (a_nMenu >= 1)
  {
    v3 = Allocate(tagFCL_MENU_WK);
    _ctor(v3, 0);
    wk = v3;
    wk_local = wk;
    v6 = NewSpecific(tagFCL_MENU_CB, a_nMenu);
    wk_local->menu = v6;
    v7 = a_nMenu;
    v8 = 32;
    do
    {
      menu = wk->menu;
      v11 = Allocate(tagFCL_MENU_CB);
      _ctor(v11, 0);
      *(Il2CppClass **)((char *)&menu->obj.klass + v8) = v11;
      v8 += 8;
      --v7;
    }
    while (v7);
    wk->nMenuMax = a_nMenu;
    Init();
    v15 = wk;
    v16 = Allocate(sprHandle_t);
    _ctor(v16, 0);
    v15->phSpr = v16;
  }
}

// 0x1b39db0
void fclDelete(void) {
  void *wk_local;
  void *v3;

  wk_local = wk;
  if (!wk_local->phSpr)
  {
    goto LABEL_5;
  }
  wk_local = wk;
  wk_local->phSpr = 0;
LABEL_5:
  v3 = wk;
  if (!v3->menu)
  {
    goto LABEL_7;
  }
  v3 = wk;
  v3->menu = 0;
LABEL_7:
  if (!wk)
    return;
  wk = 0;
}
