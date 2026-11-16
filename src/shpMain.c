#include "types.h"
#include "buttonguide.h"
#include "cmphelp.h"
#include "cmpitem.h"
#include "cmpmisc.h"
#include "cmpstatus.h"
#include "dat.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "evtbit.h"
#include "evtpmv.h"
#include "fcldrawback.h"
#include "fclmenu.h"
#include "fclmsg.h"
#include "fld.h"
#include "gohinit.h"
#include "itf.h"
#include "kernel.h"
#include "localize.h"
#include "nwdmodeltables.h"
#include "nwdnews.h"
#include "sbtlitem.h"
#include "sbtlsub.h"
#include "scr.h"
#include "sdfmem.h"
#include "sdfsound.h"
#include "shpaction.h"
#include "shpdraw.h"
#include "shpmain.h"
#include "shpmessage.h"
#include "shpmisc.h"
#include "shpmodel.h"
#include "sndat3.h"

#define KnyMasterX 122
#define KnyMasterY 0
#define KnyMasterZ 222.9

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct fileLoadAsset_Request fileLoadAsset_Request;
typedef struct tagSHP_DBG_WK tagSHP_DBG_WK;
typedef struct tagSHP_WK tagSHP_WK;

tagSHP_WK *s_wk;
dds3ProcessID_t *g_mainPID;
bool g_bCallRelease;
bool g_NoRelese;
s32 g_endmode;
s32 g_shptype;
dds3ProcessID_t *g_rootPID;
tagSHP_DBG_WK *s_dbgwk;
dds3ProcessID_t *g_debugPID;
void *SMDP;
bool g_shpsave;
bool g_shop_campOpen;
bool g_shopEvent;
bool SE_NotKillFlag;
void *shpCameraPar;
char *strName;
char *strMenu;
s16 **arrConvModelID;
f32 *arrCharTargetY;
s32 *arrOrderModelID;
fileLoadAsset_Request *UIsceneLoadReq;
fileLoadAsset_Request *sceneLoadReq;
bool MenuActive;
f32 shpSetMenuMilkHall_x2;
f32 shpSetMenuMilkHall_y2;
u8 g_rootstep;
u8 g_rootcnt;

void UniSetMenuStat(void);
void UniSetText(void);

// 0x2184d30
void shpCallProcEnd(void) {
  dds3ProcessID_t *cntrPID;

  if (!ProcessCheck())
  {
    goto LABEL_5;
  }
  g_shop_campOpen = 1;
  ProcessEnd(0, 0);
LABEL_5:
  if (!g_shopEvent)
    nwdProcessEnd();
  Delete(0);
  cntrPID = s_wk->cntrPID;
  itfCountProcessEnd(cntrPID);
}

// 0x2184f00
u8 shpCheckProcEnd(void) {
  bool v2;
  bool v4;
  bool v5;
  char v7;
  bool v8;
  dds3ProcessID_t *cntrPID;
  u8 v10;
  tagSHP_WK *s_wk_local;

  if (g_shop_campOpen)
  {
    v2 = ProcessCheck();
    goto LABEL_8;
  }
  v2 = 0;
LABEL_8:
  v4 = nwdProcessCheck();
  v5 = fclCheck();
  v7 = v2 + v4;
  v8 = v5;
  cntrPID = s_wk->cntrPID;
  v10 = v7 + v8;
  if (itfCountProcessCheck(cntrPID))
    return v10 + 1;
  s_wk_local = s_wk;
  s_wk_local->cntrPID = 0;
  return v10;
}

// 0x21850d0
u8 ProcessEnd(void) {
  u32 stat;

  if (!g_mainPID)
    return 1;
  if (!dds3ExistProcess(g_mainPID))
    return 2;
  stat = s_wk->stat;
  if ((stat & 2) != 0)
    return 3;
  stat = s_wk->stat;
  s_wk->count = 0;
  s_wk->stat = stat | 2;
  g_endmode = 1;
  s_wk->step = 9;
  return 0;
}

// 0x2176350
s32 shpMakeIndexList(s32 a_listtype, s16 *a_pList, bool _bo) {
  bool v8;
  u32 v9;
  s32 v11;
  s32 ItemIDFromSortNo;
  s32 v14;
  s32 v16;
  _BOOL4 v18;
  char *v19;
  char *v20;
  char *v21;
  char *v22;
  char *v23;
  char *v24;
  char *v25;
  char *v26;
  char *v27;
  char *v28;
  char *v29;
  char *v30;
  char *v31;
  char *v32;
  char *v33;
  char *v34;
  char *v35;
  char *v36;
  char *v37;
  char *v38;
  char *v39;
  char *v40;
  char *v41;
  char *v42;
  char *v43;
  char *v44;
  char *v45;
  char *v46;
  char *v47;
  char *v48;
  char *v49;
  char *v50;
  s16 *a_pLista;

  a_pLista = a_pList;
  if (s_wk)
    v8 = a_pList == 0;
  else
    v8 = 1;
  if (v8)
    return -1;
  if ((u32)(a_listtype - 1) < 3)
  {
    return shpSetItemList(a_listtype, 768, &a_pLista, bo);
  }
  if (a_listtype == 5)
  {
    v9 = 0;
    if (cmpChkDevilStockExist(0))
    {
      v9 = 1;
      a_pList[0] = 0;
      if (!cmpChkDevilStockExist(1))
      {
LABEL_48:
        if (!cmpChkDevilStockExist(2))
          goto LABEL_49;
        goto LABEL_86;
      }
    }
    else if (!cmpChkDevilStockExist(1))
    {
      goto LABEL_48;
    }
    v20 = (char *)a_pList + 2 * v9++;
    *((u16 *)v20 + 16) = 1;
    if (!cmpChkDevilStockExist(2))
    {
LABEL_49:
      if (!cmpChkDevilStockExist(3))
        goto LABEL_50;
      goto LABEL_87;
    }
LABEL_86:
    v21 = (char *)a_pList + 2 * v9++;
    *((u16 *)v21 + 16) = 2;
    if (!cmpChkDevilStockExist(3))
    {
LABEL_50:
      if (!cmpChkDevilStockExist(4))
        goto LABEL_51;
      goto LABEL_88;
    }
LABEL_87:
    v22 = (char *)a_pList + 2 * v9++;
    *((u16 *)v22 + 16) = 3;
    if (!cmpChkDevilStockExist(4))
    {
LABEL_51:
      if (!cmpChkDevilStockExist(5))
        goto LABEL_52;
      goto LABEL_89;
    }
LABEL_88:
    v23 = (char *)a_pList + 2 * v9++;
    *((u16 *)v23 + 16) = 4;
    if (!cmpChkDevilStockExist(5))
    {
LABEL_52:
      if (!cmpChkDevilStockExist(6))
        goto LABEL_53;
      goto LABEL_90;
    }
LABEL_89:
    v24 = (char *)a_pList + 2 * v9++;
    *((u16 *)v24 + 16) = 5;
    if (!cmpChkDevilStockExist(6))
    {
LABEL_53:
      if (!cmpChkDevilStockExist(7))
        goto LABEL_54;
      goto LABEL_91;
    }
LABEL_90:
    v25 = (char *)a_pList + 2 * v9++;
    *((u16 *)v25 + 16) = 6;
    if (!cmpChkDevilStockExist(7))
    {
LABEL_54:
      if (!cmpChkDevilStockExist(8))
        goto LABEL_55;
      goto LABEL_92;
    }
LABEL_91:
    v26 = (char *)a_pList + 2 * v9++;
    *((u16 *)v26 + 16) = 7;
    if (!cmpChkDevilStockExist(8))
    {
LABEL_55:
      if (!cmpChkDevilStockExist(9))
        goto LABEL_56;
      goto LABEL_93;
    }
LABEL_92:
    v27 = (char *)a_pList + 2 * v9++;
    *((u16 *)v27 + 16) = 8;
    if (!cmpChkDevilStockExist(9))
    {
LABEL_56:
      if (!cmpChkDevilStockExist(10))
        goto LABEL_57;
      goto LABEL_94;
    }
LABEL_93:
    v28 = (char *)a_pList + 2 * v9++;
    *((u16 *)v28 + 16) = 9;
    if (!cmpChkDevilStockExist(10))
    {
LABEL_57:
      if (!cmpChkDevilStockExist(11))
        goto LABEL_58;
      goto LABEL_95;
    }
LABEL_94:
    v29 = (char *)a_pList + 2 * v9++;
    *((u16 *)v29 + 16) = 10;
    if (!cmpChkDevilStockExist(11))
    {
LABEL_58:
      if (!cmpChkDevilStockExist(12))
        goto LABEL_59;
      goto LABEL_96;
    }
LABEL_95:
    v30 = (char *)a_pList + 2 * v9++;
    *((u16 *)v30 + 16) = 11;
    if (!cmpChkDevilStockExist(12))
    {
LABEL_59:
      if (!cmpChkDevilStockExist(13))
        goto LABEL_60;
      goto LABEL_97;
    }
LABEL_96:
    v31 = (char *)a_pList + 2 * v9++;
    *((u16 *)v31 + 16) = 12;
    if (!cmpChkDevilStockExist(13))
    {
LABEL_60:
      if (!cmpChkDevilStockExist(14))
        goto LABEL_61;
      goto LABEL_98;
    }
LABEL_97:
    v32 = (char *)a_pList + 2 * v9++;
    *((u16 *)v32 + 16) = 13;
    if (!cmpChkDevilStockExist(14))
    {
LABEL_61:
      if (!cmpChkDevilStockExist(15))
        goto LABEL_62;
      goto LABEL_99;
    }
LABEL_98:
    v33 = (char *)a_pList + 2 * v9++;
    *((u16 *)v33 + 16) = 14;
    if (!cmpChkDevilStockExist(15))
    {
LABEL_62:
      if (!cmpChkDevilStockExist(16))
        goto LABEL_63;
      goto LABEL_100;
    }
LABEL_99:
    v34 = (char *)a_pList + 2 * v9++;
    *((u16 *)v34 + 16) = 15;
    if (!cmpChkDevilStockExist(16))
    {
LABEL_63:
      if (!cmpChkDevilStockExist(17))
        goto LABEL_64;
      goto LABEL_101;
    }
LABEL_100:
    v35 = (char *)a_pList + 2 * v9++;
    *((u16 *)v35 + 16) = 16;
    if (!cmpChkDevilStockExist(17))
    {
LABEL_64:
      if (!cmpChkDevilStockExist(18))
        goto LABEL_65;
      goto LABEL_102;
    }
LABEL_101:
    v36 = (char *)a_pList + 2 * v9++;
    *((u16 *)v36 + 16) = 17;
    if (!cmpChkDevilStockExist(18))
    {
LABEL_65:
      if (!cmpChkDevilStockExist(19))
        goto LABEL_66;
      goto LABEL_103;
    }
LABEL_102:
    v37 = (char *)a_pList + 2 * v9++;
    *((u16 *)v37 + 16) = 18;
    if (!cmpChkDevilStockExist(19))
    {
LABEL_66:
      if (!cmpChkDevilStockExist(20))
        goto LABEL_67;
      goto LABEL_104;
    }
LABEL_103:
    v38 = (char *)a_pList + 2 * v9++;
    *((u16 *)v38 + 16) = 19;
    if (!cmpChkDevilStockExist(20))
    {
LABEL_67:
      if (!cmpChkDevilStockExist(21))
        goto LABEL_68;
      goto LABEL_105;
    }
LABEL_104:
    v39 = (char *)a_pList + 2 * v9++;
    *((u16 *)v39 + 16) = 20;
    if (!cmpChkDevilStockExist(21))
    {
LABEL_68:
      if (!cmpChkDevilStockExist(22))
        goto LABEL_69;
      goto LABEL_106;
    }
LABEL_105:
    v40 = (char *)a_pList + 2 * v9++;
    *((u16 *)v40 + 16) = 21;
    if (!cmpChkDevilStockExist(22))
    {
LABEL_69:
      if (!cmpChkDevilStockExist(23))
        goto LABEL_70;
      goto LABEL_107;
    }
LABEL_106:
    v41 = (char *)a_pList + 2 * v9++;
    *((u16 *)v41 + 16) = 22;
    if (!cmpChkDevilStockExist(23))
    {
LABEL_70:
      if (!cmpChkDevilStockExist(24))
        goto LABEL_71;
      goto LABEL_108;
    }
LABEL_107:
    v42 = (char *)a_pList + 2 * v9++;
    *((u16 *)v42 + 16) = 23;
    if (!cmpChkDevilStockExist(24))
    {
LABEL_71:
      if (!cmpChkDevilStockExist(25))
        goto LABEL_72;
      goto LABEL_109;
    }
LABEL_108:
    v43 = (char *)a_pList + 2 * v9++;
    *((u16 *)v43 + 16) = 24;
    if (!cmpChkDevilStockExist(25))
    {
LABEL_72:
      if (!cmpChkDevilStockExist(26))
        goto LABEL_73;
      goto LABEL_110;
    }
LABEL_109:
    v44 = (char *)a_pList + 2 * v9++;
    *((u16 *)v44 + 16) = 25;
    if (!cmpChkDevilStockExist(26))
    {
LABEL_73:
      if (!cmpChkDevilStockExist(27))
        goto LABEL_74;
      goto LABEL_111;
    }
LABEL_110:
    v45 = (char *)a_pList + 2 * v9++;
    *((u16 *)v45 + 16) = 26;
    if (!cmpChkDevilStockExist(27))
    {
LABEL_74:
      if (!cmpChkDevilStockExist(28))
        goto LABEL_75;
      goto LABEL_112;
    }
LABEL_111:
    v46 = (char *)a_pList + 2 * v9++;
    *((u16 *)v46 + 16) = 27;
    if (!cmpChkDevilStockExist(28))
    {
LABEL_75:
      if (!cmpChkDevilStockExist(29))
        goto LABEL_76;
      goto LABEL_113;
    }
LABEL_112:
    v47 = (char *)a_pList + 2 * v9++;
    *((u16 *)v47 + 16) = 28;
    if (!cmpChkDevilStockExist(29))
    {
LABEL_76:
      if (!cmpChkDevilStockExist(30))
        goto LABEL_77;
      goto LABEL_114;
    }
LABEL_113:
    v48 = (char *)a_pList + 2 * v9++;
    *((u16 *)v48 + 16) = 29;
    if (!cmpChkDevilStockExist(30))
    {
LABEL_77:
      if (!cmpChkDevilStockExist(31))
        goto LABEL_116;
      goto LABEL_115;
    }
LABEL_114:
    v49 = (char *)a_pList + 2 * v9++;
    *((u16 *)v49 + 16) = 30;
    if (!cmpChkDevilStockExist(31))
      goto LABEL_116;
LABEL_115:
    v50 = (char *)a_pList + 2 * v9++;
    *((u16 *)v50 + 16) = 31;
    goto LABEL_116;
  }
  if (a_listtype != 4)
  {
    v9 = 0;
LABEL_116:
    sub_188E3B0(&a_pList[v9], 255, 2 * (767 - v9) + 2);
    return v9;
  }
  v11 = 0;
  v9 = 0;
  do
  {
    ItemIDFromSortNo = cmpGetItemIDFromSortNo(v11);
    if (ItemIDFromSortNo < 0)
      goto LABEL_21;
    v16 = ItemIDFromSortNo;
    if (ItemIDFromSortNo != 9 && ItemIDFromSortNo != 760)
    {
      if (datGetItemNumEquipMinus(v16))
      {
        if ((tbldata[v16]->flg & 4) != 0)
        {
          v18 = 0;
LABEL_42:
          if ((v18 | ((u8)(tbldata[v16]->flg & 8) >> 3)) == 1)
          {
            v19 = (char *)a_pList + 2 * (s32)v9++;
            *((u16 *)v19 + 16) = v16;
          }
          goto LABEL_21;
        }
        else
        {
          v18 = (tbldata[v16]->type & 0x2000) == 0;
          goto LABEL_42;
        }
        goto LABEL_42;
      }
    }
LABEL_21:
    ++v11;
  }
  while (v11 != 768);
  if (!bo)
    shpSortMenu(&a_pLista, v9, v14);
  if ((s32)v9 <= 767)
    goto LABEL_116;
  return v9;
}

// 0x21745d0
s32 datGetItemNumEquipMinus(s32 id) {
  s32 ItemNum;
  s32 v4;
  s32 swordno;

  if ((u32)id > 0x2FF)
    return 0;
  if (datCheckEventItem(id))
    return 0;
  ItemNum = datCalcGetItemNum(id);
  if ((ItemNum & 0x80000000) != 0)
    return 0;
  v4 = ItemNum;
  swordno = GBWK->player->swordno;
  if ((swordno & 0x80000000) == 0)
  {
    LOWORD(swordno) = GBWK->player->swordno;
    v4 -= (s16)swordno + 144 == id;
  }
  return v4 & ~(v4 >> 31);
}

// 0x2185260
s32 nwdCheckLoadModel(s32 ModelTableIndex) {
  s64 v4;
  s32 v5;
  s32 max_length;
  s32 v7;
  s64 v8;
  u32 *v10;
  s32 v11;
  s32 v12;
  s32 v13;
  bool v14;

  v4 = ModelTableIndex;
  v5 = 0;
  max_length = nwdModelTable[ModelTableIndex]->Flag->max_length;
  if (max_length - 1 >= 0)
  {
    v7 = nwdModelTable[ModelTableIndex]->Flag->max_length;
    v8 = 8 * (u32)(max_length - 1) + 32;
    do
    {
      v10 = *(Il2CppClass **)((char *)&nwdModelTable[v4]->Flag->obj.klass + v8);
      v11 = v10[6];
      v12 = v10[4];
      v13 = v10[5];
      if (v12)
        v14 = 0;
      else
        v14 = v13 == 0;
      if (v14 && v11 == 0)
      {
        ++v5;
      }
      else if ((!v12 || evtBitCheck(v12)) && (!v13 || evtBitCheck(v13)) && (!v11 || !evtBitCheck(v11)))
      {
        goto LABEL_26;
      }
      --v7;
      v8 -= 8;
    }
    while (v7 > 0);
  }
  if (v5 != max_length)
    return -1;
LABEL_26:
  return nwdModelTable[v4]->Minor;
}

// 0x21853f0
void nwdLoadModel(void) {
  s32 *charID;
  s64 i;
  s32 v6;
  s32 v8;
  s64 v11;
  s64 v12;
  s64 v14;
  f32 *v15;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 v19;

  charID = s_wk->charID;
  charID[0] = -1;
  charID[1] = -1;
  charID[2] = -1;
  charID[3] = -1;
  charID[4] = -1;
  charID[5] = -1;
  charID[6] = -1;
  charID[7] = -1;
  charID[8] = -1;
  for (i = 4; ; ++i)
  {
    if (i - 4 >= SLODWORD(nwdModelTable->max_length))
      break;
    v6 = nwdCheckLoadModel(i - 4);
    if (v6 < 0)
      continue;
    v8 = v6;
    v11 = *((u64 *)&arrConvModelID->obj.klass + i);
    v12 = *(s16 *)(v11 + 34);
    s_wk->charID[v12] = *(s16 *)(v11 + 32);
    if ((v12 & 0x8000000000000000LL) == 0)
    {
      if (shpGetExist(v12))
        continue;
      v14 = *((u64 *)&nwdModelTable->obj.klass + i);
      v15 = *(f32 **)(v14 + 24);
      v16 = *(f32 *)(v14 + 32);
      v17 = v15[10];
      v18 = v15[8];
      v19 = v15[9];
      shpSetParamInit(v12, 3u, v8, 0, v18, v19, v17, v16);
    }
  }
}

// 0x2185740
s32 *shpGets_wk_CharID(void) {
  s32 *charID;

  charID = s_wk->charID;
  if (!charID)
    return charID;
  return charID;
}

// 0x21857f0
void shpMenuChkSelect(void) {
  s32 shopType;
  s32 v6;
  s32 v9;
  s16 v10;
  bool v11;
  s32 IndexList;
  s32 v15;

  shopType = (u8)s_wk->shopType;
  if (!s_wk->shopType)
  {
    IndexList = shpMakeIndexList(2, s_wk->index, 1);
    fclSetFlagSelect(17, IndexList > 0);
    v15 = shpMakeIndexList(4, s_wk->index, 1);
    v10 = 32;
    v11 = v15 > 0;
    goto LABEL_15;
  }
  if (shopType != 1)
    return;
  goto LABEL_6;
  if (s_wk->shopType == 1)
  {
LABEL_6:
    v6 = shpMakeIndexList(5, s_wk->index, 0);
    fclSetFlagSelect(2048, v6 > 0);
    v9 = shpMakeIndexList(3, s_wk->index, 0);
    v10 = 256;
    v11 = v9 > 0;
LABEL_15:
    fclSetFlagSelect(v10, v11);
  }
}

// 0x2185a20
void shpSetMenuParam(s16 a_menuId, s16 a_actType, s16 a_charId, s16 a_objId) {
  s64 menuMax;
  tagSHP_MENU_WK *v12;

  if ((a_menuId & 0x8000) == 0)
  {
    menuMax = s_wk->menuMax;
    v12 = s_wk->Menu[menuMax];
    v12->menuId = a_menuId;
    v12->actType = a_actType;
    v12->charId = a_charId;
    v12->objId = a_objId;
    s_wk->menuMax = menuMax + 1;
  }
}

// 0x2185ad0
void shpSetMenuKonnouya(void) {
  char *v2;
  char *LocalizeText;
  s64 menuMax;
  char *v7;
  s64 v8;
  char *v9;
  s64 v12;
  char *v13;
  s64 v14;
  char *v15;
  s64 v18;
  char *v19;
  s64 v20;
  char *v21;
  s64 v24;
  char *v25;
  s64 v26;
  char *v27;
  s64 v30;
  char *v31;
  s64 v32;
  char *v33;
  s64 v36;
  s64 v37;

  v2 = strMenu[5];
  LocalizeText = GetLocalizeText(v2, 1);
  fclSetParam(18, 0xFFFF, 1, 1, LocalizeText);
  menuMax = s_wk->menuMax;
  v7 = strMenu[6];
  v8 = (s64)s_wk->Menu + 8 * menuMax;
  s_wk->menuMax = menuMax + 1;
  *(u64 *)(*(u64 *)(v8 + 32) + 16) = 0xFFFF0000008A0012LL;
  v9 = GetLocalizeText(v7, 1);
  fclSetParam(32, 0xFFFF, 1, 1, v9);
  v12 = s_wk->menuMax;
  v13 = strMenu[1];
  v14 = (s64)s_wk->Menu + 8 * v12;
  s_wk->menuMax = v12 + 1;
  *(u64 *)(*(u64 *)(v14 + 32) + 16) = 0xFFFF0000010A0020LL;
  v15 = GetLocalizeText(v13, 1);
  fclSetParam(4097, 0xFFFF, 1, 0, v15);
  v18 = s_wk->menuMax;
  v19 = strMenu[7];
  v20 = (s64)s_wk->Menu + 8 * v18;
  s_wk->menuMax = v18 + 1;
  *(u64 *)(*(u64 *)(v20 + 32) + 16) = 0x100441001LL;
  v21 = GetLocalizeText(v19, 1);
  fclSetParam(64, 0xFFFF, 1, 0, v21);
  v24 = s_wk->menuMax;
  v25 = strMenu[2];
  v26 = (s64)s_wk->Menu + 8 * v24;
  s_wk->menuMax = v24 + 1;
  *(u64 *)(*(u64 *)(v26 + 32) + 16) = 0xFFFF000020040040LL;
  v27 = GetLocalizeText(v25, 1);
  fclSetParam(0x2000, 0xFFFF, 1, 1, v27);
  v30 = s_wk->menuMax;
  v31 = strMenu[16];
  v32 = (s64)s_wk->Menu + 8 * v30;
  s_wk->menuMax = v30 + 1;
  *(u64 *)(*(u64 *)(v32 + 32) + 16) = 0xFFFF000000002000LL;
  v33 = GetLocalizeText(v31, 1);
  fclSetParam(144, 0xFFFF, 1, 1, v33);
  v36 = s_wk->menuMax;
  v37 = (s64)s_wk->Menu + 8 * v36;
  s_wk->menuMax = v36 + 1;
  *(u64 *)(*(u64 *)(v37 + 32) + 16) = 0xFFFF000040000090LL;
  fclSetFlagDecideEnd(0x2000);
}

// 0x2185ec0
void shpSetMenuMilkHall(void) {
  char *v2;
  char *LocalizeText;
  s64 menuMax;
  char *v8;
  tagSHP_WK *v11;
  s64 v12;
  char *v13;
  char *v14;
  tagSHP_WK *v17;
  s64 v18;
  char *v19;
  tagSHP_WK *v21;
  s64 v22;
  char *v23;
  tagSHP_WK *v25;
  s64 v26;
  s64 i;
  s32 v29;
  s32 v30;
  s64 v32;
  s16 *v33;
  s32 v34;
  s64 v35;
  char *v36;
  char *v37;
  s32 v38;
  tagSHP_WK *v40;
  s64 v41;
  tagSHP_MENU_WK *v42;
  f32 *Pos;
  f32 v45;
  f32 v46;
  f32 v47;
  f32 v48;
  unsigned __int128 v49;

  v49 = 0u;
  v2 = strMenu[10];
  LocalizeText = GetLocalizeText(v2, 1);
  fclSetParam(256, 0xFFFF, 1, 1, LocalizeText);
  menuMax = s_wk->menuMax;
  s_wk->Menu[menuMax]->fields = (tagSHP_MENU_WK)0xFFFF000004220100LL;
  s_wk->menuMax = menuMax + 1;
  v8 = GetLocalizeText(strMenu[1], 1);
  fclSetParam(4096, 0xFFFF, 1, 1, v8);
  v11 = s_wk;
  v12 = s_wk->menuMax;
  s_wk->Menu[v12]->fields = (tagSHP_MENU_WK)0xFFFF000000441000LL;
  v11->menuMax = v12 + 1;
  v13 = GetLocalizeText(strMenu[11], 1);
  fclSetParam(512, 512, 0, 1, v13);
  v14 = GetLocalizeText(strMenu[12], 1);
  fclSetParam(1024, 0xFFFF, 1, 1, v14);
  v17 = s_wk;
  v18 = s_wk->menuMax;
  s_wk->Menu[v18]->fields = (tagSHP_MENU_WK)0xFFFF000010040400LL;
  v17->menuMax = v18 + 1;
  v19 = GetLocalizeText(strMenu[2], 1);
  fclSetParam(0x2000, 0xFFFF, 1, 1, v19);
  v21 = s_wk;
  v22 = v21->menuMax;
  v21->Menu[v22]->fields = (tagSHP_MENU_WK)0xFFFF000000002000LL;
  v21->menuMax = v22 + 1;
  fclSetFlagDecideEnd(0x2000);
  v23 = GetLocalizeText(strMenu[16], 1);
  fclSetParam(144, 0xFFFF, 1, 1, v23);
  v25 = s_wk;
  v26 = v25->menuMax;
  v25->Menu[v26]->fields = (tagSHP_MENU_WK)0xFFFF000040000090LL;
  v25->menuMax = v26 + 1;
  fclSetFlagDecideEnd(0x2000);
  for (i = 32; i != 68; i += 4)
  {
    v32 = *(s32 *)((char *)&arrOrderModelID->obj.klass + i);
    v33 = arrConvModelID[v32];
    v34 = v33[0];
    v35 = v33[1];
    if (s_wk->charID[v35] == v34)
    {
      v36 = strName[v34];
      v37 = GetLocalizeText(v36, 1);
      v38 = (s16)(v34 + 4096);
      fclSetParam(v34 + 4096, 4096, 1, 0, v37);
      if ((v38 & 0x80000000) == 0)
      {
        v40 = s_wk;
        v41 = v40->menuMax;
        v42 = v40->Menu[v41];
        v42->actType = 68;
        v42->menuId = v38;
        v42->charId = v34;
        v42->objId = v35;
        v40->menuMax = v41 + 1;
      }
      Pos = nwdModelTable[v32]->Pos;
      v45 = arrCharTargetY[v34];
      v46 = Pos[0];
      v47 = Pos[1];
      v48 = Pos[2];
      sBtlChangeWorldtoScreenUnity3(v46, v47 - v45, v48, &v49);
      if (*(f32 *)&v49 == INFINITY)
        v29 = 0x80000000;
      else
        v29 = *(f32 *)&v49;
      if (*((f32 *)&v49 + 1) == INFINITY)
        v30 = 0x80000000;
      else
        v30 = *((f32 *)&v49 + 1);
      fclSetCursor(v38, v29, v30, v32);
    }
  }
}

// 0x2186510
void shpNpcGetCursorPos(s32 _num, s32 *_x, s32 *_y) {
  s64 v8;
  s64 v11;
  f32 v12;
  f32 *Pos;
  f32 v14;
  f32 v15;
  f32 v16;
  s64 v17;
  s32 v18;
  s32 v19;
  unsigned __int128 v20;

  v20 = 0u;
  v8 = num;
  v11 = arrConvModelID[num][0];
  v12 = arrCharTargetY[v11];
  Pos = nwdModelTable[v8]->Pos;
  v14 = Pos[0];
  v15 = Pos[1];
  v16 = Pos[2];
  sBtlChangeWorldtoScreenUnity3(v14, v15 - v12, v16, &v20);
  v17 = v20;
  v18 = *(f32 *)&v20;
  if (*(f32 *)&v20 == INFINITY)
    v18 = 0x80000000;
  *x = v18;
  v19 = *((f32 *)&v17 + 1);
  if (*((f32 *)&v17 + 1) == INFINITY)
    v19 = 0x80000000;
  *y = v19;
}

// 0x2186680
void shpSetMoveBack(f32 a_tgtx, f32 a_tgty, f32 a_tgtz, f32 a_ratio, s32 a_frame) {
  u32 v12;
  u32 v14;
  u64 v15;
  tagSHP_BACK_WK *back;
  u64 y2;

  y2 = 0;
  shpPoint3To2(a_tgtx, a_tgty, a_tgtz, (f32 *)&y2 + 1, &y2);
  *(f32 *)&v12 = (f32)(*((f32 *)&y2 + 1) + -2048.0) + 256.0;
  *(f32 *)&v14 = (f32)((f32)(*(f32 *)&y2 + -2048.0) + 112.0) + (f32)((f32)(*(f32 *)&y2 + -2048.0) + 112.0);
  *(f32 *)&y2 = *(f32 *)&v14;
  *((f32 *)&y2 + 1) = *(f32 *)&v12;
  v15 = __PAIR64__(v12, v14);
  v15 = y2;
  back = s_wk->back;
  back->fx = *((f32 *)&v15 + 1);
  LODWORD(back->fy) = v15;
  back->ratio = a_ratio;
  back->frame = a_frame;
  *(u64 *)&back->posx = 0x4360000043800000LL;
  *(u64 *)&back->w = 0x43E0000044000000LL;
  back->movx = (f32)(*((f32 *)&v15 + 1) + -256.0) / (f32)a_frame;
  back->movy = (f32)(*(f32 *)&v15 + -224.0) / (f32)a_frame;
  *(u64 *)&back->count = 0x100000000LL;
}

// 0x21867e0
void shpSetMoveBackDef(s32 a_frame) {
  int32x2_t v2;
  float32x2_t *back;
  float32x2_t v6;

  v2.n64_f32[0] = (f32)a_frame;
  back = s_wk->back;
  v6.n64_u64[0] = back[3].n64_u64[0];
  back[6].n64_u32[1] = a_frame;
  back[4].n64_u64[0] = vdiv_f32(vsub_f32((float32x2_t)0x4360000043800000LL, v6), vdup_lane_s32(v2, 0)).n64_u64[0];
  back[7].n64_u64[0] = 0x200000000LL;
}

// 0x2186880
void shpUpdateBack(void) {
  int32x2_t v1;
  float32x2_t *back;
  s32 v4;
  u32 v6;
  float32x2_t v7;
  float32x2_t v8;
  float32x2_t *v9;
  u64 v10;
  s32 v11;
  s32 v12;
  u64 v13;

  back = s_wk->back;
  if (back[7].n64_i32[1] < 1)
    return;
  v4 = back[6].n64_i32[1];
  back = s_wk->back;
  if ((back[7].n64_u32[0] & 0x80000000) == 0)
  {
    v1.n64_f32[0] = (f32)v4;
    v13 = v1.n64_u64[0];
    v1.n64_u64[0] = v13;
    back = s_wk->back;
    v6 = back[7].n64_u32[1];
    v7.n64_u64[0] = vdiv_f32(vmul_n_f32((float32x2_t)0x43E0000044000000LL, 1.0 - back[6].n64_f32[0]), vdup_lane_s32(v1, 0)).n64_u64[0];
    if (v6 == 1)
    {
      back = s_wk->back;
      v8.n64_u64[0] = vsub_f32(back[5], v7).n64_u64[0];
      goto LABEL_27;
    }
    if (v6 != 2)
      goto LABEL_18;
    goto LABEL_9001;
    if (back[7].n64_u32[1] != 2)
    {
LABEL_18:
LABEL_19:
      v9 = s_wk->back;
      v10 = vadd_f32(v9[3], v9[4]).n64_u64[0];
      v11 = v9[6].n64_i32[1];
      v12 = v9[7].n64_u32[0] + 1;
      v9[7].n64_u32[0] = v12;
      v9[3].n64_u64[0] = v10;
      if (v12 >= v11)
      {
        v9 = s_wk->back;
        v9[7].n64_u64[0] = 0xFFFFFFFFLL;
      }
      return;
    }
LABEL_9001:
    back = s_wk->back;
    v8.n64_u64[0] = vadd_f32(v7, back[5]).n64_u64[0];
LABEL_27:
    back[5].n64_u64[0] = v8.n64_u64[0];
    goto LABEL_19;
  }
}

// 0x2186aa0
void shpInitFunc(void) {
  fileLoadAsset_Request *Asset__AllSceneAsync;
  s32 shopType;
  void *v11;
  sdfBinary *v12;
  u8 *v14;
  u8 **v15;
  void *v17;
  sdfBinary *v18;
  u8 *v19;
  u8 **v20;
  void *v22;
  sdfBinary *v23;
  u8 *v24;
  u8 **v25;
  bool v26;
  void *Asset;
  sdfBinary *v31;
  u8 *v33;
  u8 **pDatScr;
  Il2CppObject *v35;
  char data[4];

  Init();
  shpSetCamera(s_wk->shopType);
  s_wk->stat |= 0x80u;
  Init();
  shpMsgInit();
  Init();
  cmpSetDraw(1);
  cmpSetType(1);
  cmpSetId(0);
  fclCreate(16);
  Create(0);
  Load(Dependent, "ui_konnouya", "ui_konnouya");
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  Asset__AllSceneAsync = AllSceneAsync("ui_konnouya", 0);
  UIsceneLoadReq = Asset__AllSceneAsync;
  shopType = (u8)s_wk->shopType;
  if (!s_wk->shopType)
  {
    fclLoadData("kny_sys.bmd", "shop_evt", 1);
    Asset = LoadAsset(_Ctrl_k__BackingField, "shop_evt", "kny_talk.bf", 0);
    v31 = Allocate(sdfBinary);
    _ctor(v31, Asset, 0);
    v33 = v31->data;
    pDatScr = s_wk->pDatScr;
    pDatScr[0] = v33;
    return;
  }
  if (shopType == 1)
  {
    fclLoadData("nwd_sys.bmd", "shop_evt", 1);
    v11 = LoadAsset(_Ctrl_k__BackingField, "shop_evt", "nwd_talk.bf", 0);
    v12 = Allocate(sdfBinary);
    _ctor(v12, v11, 0);
    v14 = v12->data;
    v15 = s_wk->pDatScr;
    v15[0] = v14;
    v17 = LoadAsset(_Ctrl_k__BackingField, "shop_evt", "nwd_drink.bf", 0);
    v18 = Allocate(sdfBinary);
    _ctor(v18, v17, 0);
    v19 = v18->data;
    v20 = s_wk->pDatScr;
    v20[1] = v19;
    v22 = LoadAsset(_Ctrl_k__BackingField, "shop_evt", "nwd_news.bf", 0);
    v23 = Allocate(sdfBinary);
    _ctor(v23, v22, 0);
    v24 = v23->data;
    v25 = s_wk->pDatScr;
    v25[2] = v24;
    g_shopEvent = 0;
    if (evtBitCheck(199))
    {
      v26 = evtBitCheck(200);
      if (v26)
      {
        goto LABEL_32;
      }
      g_shopEvent = 1;
    }
    else
    {
    }
LABEL_32:
    if (g_shopEvent)
      return;
    nwdProcessStart();
    nwdLoadSprite();
    return;
  }
  LOBYTE(shopType) = s_wk->shopType;
  data[0] = shopType;
  v35 = Box(sbyte, data);
  LogError(v35, 0);
}

// 0x2187250
void shpInitBack(void) {
  tagSHP_BACK_WK *back;

  back = s_wk->back;
  *(u64 *)&back->posx = 0x4360000043800000LL;
  back->count = -1;
  *(u64 *)&back->w = 0x43E0000044000000LL;
}

// 0x21872d0
void shpInit(void) {
  tagSHP_WK *v5;
  tagSHP_MENU_WK *v6;
  s64 i;
  tagSHP_MENU_WK *Menu;
  Il2CppObject *v10;
  s32 shopType;
  void *Asset;
  s64 naturalAligment;
  void *v20;
  char **v22;
  fileLoadAsset_Request *Asset__AllSceneAsync;
  void *v27;
  void *p_SMDP;
  void *v33;
  s64 v35;
  void *v36;
  void *v37;
  void *p_shpCameraPar;
  tagSHP_WK *v42;
  u32 stat;
  tagSHP_BACK_WK *back;
  tagSHP_DRAW_WK *v49;
  s32 *EventBit;
  s32 v53;

  if (!s_wk)
    goto LABEL_6;
  goto LABEL_5;
  if (s_wk)
  {
LABEL_5:
    wk = s_wk;
  }
LABEL_6:
  Load(Dependent, "shop_evt", "shop_evt");
  v5 = s_wk;
  v5->menuMax = 0;
  v5->selNo = 0;
  v5->selNum = 0;
  v6 = NewSpecific(tagSHP_MENU_WK, 0x10u);
  v5->Menu = v6;
  for (i = 32; i != 160; i += 8)
  {
    Menu = s_wk->Menu;
    v10 = Allocate(tagSHP_MENU_WK);
    _ctor(v10, 0);
    *(Il2CppClass **)((char *)&Menu->obj.klass + i) = v10;
  }
  shopType = (u8)s_wk->shopType;
  if (s_wk->shopType)
  {
    if (shopType != 1)
      goto LABEL_19;
    goto LABEL_9001;
    if (s_wk->shopType != 1)
    {
LABEL_19:
      goto LABEL_20;
    }
LABEL_9001:
    v22 = &"milkhall";
    Load(Dependent, "milkhall", "milkhall");
    goto LABEL_37;
  }
  v22 = &"konnouya";
  Load(Dependent, "konnouya", "konnouya");
LABEL_37:
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  Asset__AllSceneAsync = AllSceneAsync(*v22, 0);
  sceneLoadReq = Asset__AllSceneAsync;
LABEL_20:
  Load(Dependent, "shpmodeldatapar_key", "shpmodeldatapar_key");
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  Asset = LoadAsset(_Ctrl_k__BackingField, "shpmodeldatapar_key", "shpModelDataPar", 0);
  if (!Asset)
  {
    v27 = 0;
    SMDP = 0;
    p_SMDP = &SMDP;
    goto LABEL_57;
  }
  if (Asset->klass->_2.naturalAligment >= (u32)naturalAligment)
  {
    if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_shpModelDataPar)
      v20 = Asset;
    else
      v20 = 0;
  }
  else
  {
    v20 = 0;
  }
  SMDP = (void *)v20;
  p_SMDP = &SMDP;
  if (Asset->klass->_2.naturalAligment >= (u32)naturalAligment)
  {
    if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_shpModelDataPar)
      v27 = Asset;
    else
      v27 = 0;
  }
  else
  {
    v27 = 0;
  }
LABEL_57:
  Load(Dependent, "shop_scr", "shop_scr");
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  v33 = LoadAsset(_Ctrl_k__BackingField, "shop_scr", "ShpCameraPar", 0);
  if (v33)
  {
    if (v33->klass->_2.naturalAligment >= (u32)v35)
    {
      if (v33->klass->_2.typeHierarchy[v35 - 1] == Project_ShpCameraPar)
        v36 = v33;
      else
        v36 = 0;
    }
    else
    {
      v36 = 0;
    }
    shpCameraPar = (void *)v36;
    p_shpCameraPar = &shpCameraPar;
    if (v33->klass->_2.naturalAligment >= (u32)v35)
    {
      if (v33->klass->_2.typeHierarchy[v35 - 1] == Project_ShpCameraPar)
        v37 = v33;
      else
        v37 = 0;
    }
    else
    {
      v37 = 0;
    }
  }
  else
  {
    v37 = 0;
    shpCameraPar = 0;
    p_shpCameraPar = &shpCameraPar;
  }
  v42 = s_wk;
  stat = v42->stat;
  v42->count = 0;
  v42->curCount = 0;
  v42->ctrlType = 0;
  v42->stat = stat | 0x19;
  back = s_wk->back;
  *(u64 *)&back->posx = 0x4360000043800000LL;
  *(u64 *)&back->w = 0x43E0000044000000LL;
  back->count = -1;
  if (!wk)
    goto LABEL_85;
  wk->countRootCur = 0;
LABEL_86:
  goto LABEL_87;
LABEL_85:
  goto LABEL_86;
LABEL_87:
  v49 = wk;
  if (!v49)
  {
    if (s_wk->shopType)
      return;
LABEL_107:
    if (evtBitCheck(2321))
    {
      goto LABEL_114;
    }
    EventBit = GBWK->EventBit;
    EventBit[72] |= 0x4000u;
LABEL_114:
    if (GBWK->GameFileInfo->chapter == 9)
      v53 = 54;
    else
      v53 = 1;
    fldJmpBitOn(v53, 1);
    return;
  }
  v49 = wk;
  v49->bRootLineEnd = 0;
  *(u32 *)&v49->countRootCur2 = 0;
  if (!s_wk->shopType)
    goto LABEL_107;
}

// 0x2187cd0
void shpRelease(void) {
  char **v7;
  u8 **pDatScr;
  u8 **v13;
  u8 **v15;
  UnityEngine_SceneManagement_Scene_o v16;

  End();
  shpCameraPar = 0;
  shpEnd();
  shpMsgEnd();
  cmpEnd();
  fclDelete();
  Unload(Dependent, "shop_evt", 0);
  Unload(Dependent, "ui_konnouya", 0);
  Unload(Dependent, "shpmodeldatapar_key", 0);
  Unload(Dependent, "shop_scr", 0);
  if (!s_wk->shopType)
  {
    v7 = &"konnouya";
    Unload(Dependent, "konnouya", 0);
    goto LABEL_25;
  }
  if (s_wk->shopType != 1)
    goto LABEL_31;
  Unload(Dependent, "milkhall", 0);
  if (evtIsExec(613, 1))
    goto LABEL_31;
  v7 = &"milkhall";
LABEL_25:
  v16.m_Handle = GetSceneByName(*v7, 0).m_Handle;
  UnloadSceneAsync_61083440(v16, 0);
LABEL_31:
  pDatScr = s_wk->pDatScr;
  pDatScr[0] = 0;
  v13 = s_wk->pDatScr;
  v13[1] = 0;
  v15 = s_wk->pDatScr;
  v15[2] = 0;
}

// 0x2188100
void shpLoadLocalizeTextData(void) {
  ;
}

// 0x2188110
dds3ProcessFunc_t shpProcess(dds3ProcessID_t *proc) {
  u32 stat;
  s32 shopType;
  s32 v7;
  tagSHP_WK *v10;
  struct shpMain *v11;
  tagSHP_WK *v12;
  void *Instance;
  void *p_shpUIManager;
  void *v17;
  char v20;
  s32 v21;
  void *v22;
  tagSHP_WK *v24;
  s16 v26;
  s32 v28;
  tagSHP_WK *v29;
  s32 v30;
  s64 v32;
  s64 v33;
  u16 *v34;
  tagSHP_WK *v35;
  tagSHP_WK *v39;
  tagSHP_MENU_WK *pMenu;
  tagSHP_WK *v41;
  tagSHP_WK *v42;
  tagSHP_WK *v44;
  u32 actType;
  s8 updated;
  s32 v51;
  bool v55;
  u32 v56;
  s16 count;
  u32 v58;
  dds3ProcessFunc_t v59;
  s32 menuId;
  s32 v64;
  s32 v65;
  tagSHP_WK *v70;
  tagSHP_WK *v72;
  u32 v73;
  sdatPlayerUnitWork_t *player;
  s32 gold;
  s32 v77;
  s32 v78;
  tagSHP_WK *v81;
  u32 v82;
  s32 v83;
  s32 selMax;
  tagSHP_WK *v85;
  s32 v86;
  tagSHP_WK *v87;
  tagSHP_WK *v88;
  u32 v89;
  s32 v90;
  u32 v94;
  tagSHP_MENU_WK *v95;
  s32 v96;
  sdatPlayerUnitWork_t *v100;
  sdatPlayerUnitWork_t *v101;
  tagSHP_WK *v103;
  s32 monitor_high;
  tagSHP_WK *v108;
  s64 v110;
  s64 v111;
  s16 *v112;
  tagSHP_WK *v113;

  stat = s_wk->stat;
  if ((stat & 0x400) == 0)
  {
    shopType = (u8)s_wk->shopType;
    if (shopType)
      goto LABEL_8;
    goto LABEL_9000;
    if (s_wk->shopType)
    {
LABEL_8:
      if (shopType == 1)
        v7 = 18;
      else
        v7 = -1;
      goto LABEL_14;
    }
LABEL_9000:
    v7 = 17;
LABEL_14:
    sndBgmLoadId_XF(v7);
    s_wk->stat |= 0x400u;
LABEL_34:
    if (!sceneLoadReq->isDone)
      return 0;
    goto LABEL_35;
  }
  if ((stat & 0x800) != 0)
    goto LABEL_34;
  if (sndBgmStatus_XF() != 2)
    goto LABEL_34;
  sndBgmPlay(0, 0);
  s_wk->stat |= 0x800u;
  goto LABEL_34;
LABEL_35:
  v10 = s_wk;
  switch (v10->step)
  {
    case 0:
      if (p2sdLoadCheckMidi(4259840) != 1)
        goto LABEL_193;
      shpSetSwitchMotion(0, 1);
      shpSetSingleMotion(0, 0);
      shpSetMotionSpeed(0, 0.0);
      v12 = s_wk;
      LODWORD(v11) = UIsceneLoadReq->isDone;
      v12->count = 0;
      v12->stepAct = 0;
      if (!(u32)v11)
        return 0;
      Instance = get_Instance(0);
      ItfButtonGuideSet(Instance, 1, 0);
      p_shpUIManager = &shpUIManager;
      v17 = p_shpUIManager;
      InitMenuTitle(v17, s_wk->shopType, 0);
      v20 = 1;
      goto LABEL_191;
    case 1:
      v10 = s_wk;
      v21 = (u8)v10->shopType;
      if (v21 == 1)
      {
        shpSetMenuMilkHall();
        fldFacilityMistInit(1);
      }
      else if (!v21)
      {
        shpSetMenuKonnouya();
      }
      shpMenuChkSelect();
      fclSetLink();
      fclSetParamTitle("");
      v20 = 2;
      goto LABEL_191;
    case 2:
      if (shpUpdateEnter() != 1)
      {
        v22 = get_Instance(0);
        ItfButtonGuideSet(v22, 1, 0);
        v24 = s_wk;
        v24->pMenu = 0;
        v24 = ((char *)v24 + 104);
        BYTE1(v24[-1].mag) = 0;
        BYTE1(v24[-1].selNo) = 1;
        s_wk->step = 3;
        fclStartUpdate();
        s_wk->stat |= 4u;
      }
      goto LABEL_193;
    case 3:
      v26 = fclUpdate();
      v28 = v26;
      v29 = s_wk;
      v30 = v29->stat | 0x20;
      v29->stat = v30;
      if (v28 != -1)
      {
        if (v28 < 0)
          goto LABEL_193;
        v29 = s_wk;
        v29->pMenu = 0;
        v32 = 0;
        do
        {
          v35 = s_wk;
          if (v32 >= v35->menuMax)
            goto LABEL_245;
          v35 = s_wk;
          v33 = (s64)v35->Menu + 8 * v32++;
          v34 = *(u16 **)(v33 + 32);
        }
        while (v34[8] != (u16)v28);
        v35 = s_wk;
        v34 = *(&v35->Menu->max_length + v32);
        v35->pMenu = (tagSHP_MENU_WK *)v34;
LABEL_245:
        v85 = s_wk;
        v85->step = 4;
        v85->stat &= ~0x20u;
        goto LABEL_193;
      }
      v29 = s_wk;
      v30 = s_wk->stat;
      *(u32 *)&v29->step = 8;
      v29->stat = v30 & 0xFFFFFFDF;
      goto LABEL_193;
    case 4:
      fclUpdate();
      v39 = s_wk;
      pMenu = v39->pMenu;
      if ((pMenu->actType & 2) == 0)
      {
        goto LABEL_97;
      }
      v39 = s_wk;
      pMenu = v39->pMenu;
      menuId = pMenu->menuId;
      v64 = (u16)pMenu->menuId;
      if (menuId <= 18)
      {
        if (v64 == 18)
          v77 = 1;
        else
          v77 = -1;
        if (v64 == 17)
          v65 = 2;
        else
          v65 = v77;
      }
      else
      {
        switch (v64)
        {
          case 32:
            v65 = 4;
            break;
          case 256:
            v65 = 3;
            break;
          case 2048:
            v65 = 5;
            break;
          default:
            v65 = -1;
            break;
        }
      }
      v39 = s_wk;
      LOWORD(v64) = v39->pMenu->menuId;
      if ((v64 & 0x200) != 0)
        v65 = 3;
      if (v65 < 0)
      {
        v39 = s_wk;
        v39->step = 3;
LABEL_148:
        fclStartUpdate();
        goto LABEL_193;
      }
      v78 = v65;
      if (v65 == 1)
        goto LABEL_229;
      if (v65 == 4)
      {
        v78 = 2;
LABEL_229:
        shpSortSetting(v78);
      }
      v81 = s_wk;
      v81->selMax = shpMakeIndexList(v65, s_wk->index, 0);
      v10 = s_wk;
      if (v10->selMax > 0)
      {
        if (v82)
        {
          if (v10->pMenu->menuId == 2048)
            v83 = 8;
          else
            v83 = 6;
          selMax = v10->selMax;
          v10->drwMax = selMax;
          if (selMax >= v83)
          {
LABEL_238:
            v10 = s_wk;
            v10->drwMax = v83;
            goto LABEL_263;
          }
        }
        else
        {
          v10 = s_wk;
          if (v10->pMenu->menuId == 2048)
            v83 = 8;
          else
            v83 = 6;
          v86 = v10->selMax;
          v10->drwMax = v86;
          if (v86 >= v83)
            goto LABEL_238;
        }
LABEL_263:
        v87 = s_wk;
        v87->selNumMax = 0;
        if (v87->pMenu->menuId == 2048)
        {
          cmpSetDraw(0);
        }
        v88 = s_wk;
        v88->ctrlType = 4;
        v89 = v88->stat;
        v88->topNo = 0;
        *(u64 *)&v88->selNo = 0;
        v88->stat = v89 & 0xFFFF1FB7 | 0x4000;
LABEL_97:
        v41 = s_wk;
        if ((v41->pMenu->actType & 4) == 0)
        {
LABEL_99:
          v42 = s_wk;
          v44 = v42;
          player = GBWK->player;
          gold = player->gold;
          v44->mag = player->mag;
          v42->yen = gold;
          *(u32 *)&v44->step = 7;
          goto LABEL_193;
        }
        v41 = s_wk;
        v41->ctrlType = 3;
        goto LABEL_99;
      }
      if (!v82)
      {
        v10 = s_wk;
      }
      v20 = 5;
      goto LABEL_192;
    case 5:
      v10 = s_wk;
      if (v10->pMenu->menuId == 2048)
      {
        fclStart1(13, 0);
        v20 = 6;
        goto LABEL_191;
      }
LABEL_145:
      v10 = s_wk;
      v10->step = 3;
      goto LABEL_148;
    case 6:
      if (Update())
        goto LABEL_193;
      goto LABEL_145;
    case 7:
      fclUpdate();
      actType = (u16)s_wk->pMenu->actType;
      if (s_wk->pMenu->actType <= 530)
      {
        if ((s16)actType <= 138)
        {
          if (actType == 68)
          {
            updated = shpUpdateTalk();
          }
          else
          {
            if (actType != 138)
              goto LABEL_193;
            updated = shpUpdateBuy();
          }
        }
        else if (actType == 266)
        {
          updated = shpUpdateSell();
        }
        else
        {
          if (actType != 530)
            goto LABEL_193;
          updated = shpUpdateTrade();
        }
      }
      else if (actType <= 0x822)
      {
        if (actType != 1058 && actType != 2082)
          goto LABEL_193;
        updated = shpUpdateOrder();
      }
      else
      {
        switch (actType)
        {
          case 0x1004u:
            updated = shpUpdateNews();
            break;
          case 0x2004u:
            updated = shpUpdateGoma();
            break;
          case 0x4000u:
            updated = shpUpdateDBOOK();
            break;
          default:
            goto LABEL_193;
        }
      }
      if (updated == 1)
        goto LABEL_193;
      v90 = updated;
      if (updated == 5)
      {
        g_endmode = 2;
        v10 = s_wk;
        v20 = 9;
        v10->count = 0;
        goto LABEL_192;
      }
      if (!evtBitCheck(-1))
      {
        v100 = GBWK->player;
        v101 = GBWK->player;
        v103 = s_wk;
        v103->pMenu = 0;
        v103 = ((char *)v103 + 104);
        monitor_high = HIDWORD(v103->monitor);
        v101->mag = (s32)v103->drawPID;
        v100->gold = monitor_high;
        BYTE1(v103[-1].selNo) = 1;
        v103[-1].mag = 3;
        s_wk->stat = s_wk->stat
                                                                   & 0xFFFFFFB7
                                                                   | 8;
        cmpSetDraw(1);
        shpMenuChkSelect();
        fclStartUpdate();
        cmpUpdateBulletNum();
        goto LABEL_193;
      }
      v95 = s_wk->pMenu;
      v96 = (u16)v95->actType;
      if (v96 == 68)
      {
        if (!v94)
        {
          v95 = s_wk->pMenu;
        }
        v90 = v95->menuId - 3584;
        goto LABEL_301;
      }
      if (v94)
      {
        if (v96 == 2082)
        {
LABEL_298:
          v95 = s_wk->pMenu;
          v90 = v95->menuId + 3584;
LABEL_301:
          fclSetTargetId(v90);
          goto LABEL_315;
        }
      }
      else
      {
        v95 = s_wk->pMenu;
        if (v95->actType == 2082)
          goto LABEL_298;
      }
LABEL_315:
      v108 = s_wk;
      v108->pMenu = 0;
      v110 = 0;
      while (1)
      {
        v113 = s_wk;
        if (v110 >= v113->menuMax)
          break;
        v113 = s_wk;
        v111 = (s64)v113->Menu + 8 * v110++;
        v112 = *(s16 **)(v111 + 32);
        if (v90 == v112[8])
        {
          v113 = s_wk;
          v112 = *(&v113->Menu->max_length + v110);
          v113->pMenu = (tagSHP_MENU_WK *)v112;
          break;
        }
      }
      v20 = 4;
LABEL_191:
      v10 = s_wk;
LABEL_192:
      v10->step = v20;
      goto LABEL_193;
    case 8:
      v51 = (u8)shpUpdateLeave();
      if (v51 == 3)
      {
        v70 = s_wk;
        v70->pMenu = 0;
        v70 = ((char *)v70 + 104);
        BYTE1(v70[-1].mag) = 0;
        BYTE1(v70[-1].selNo) = 1;
        s_wk->step = 3;
        fclStartUpdate();
        v72 = s_wk;
        v73 = v72->stat;
        v72->stepAct = 0;
        v72->stat = v73 | 4;
        shpMenuChkSelect();
      }
      else if (v51 == 2)
      {
        g_endmode = 1;
        *(u32 *)&s_wk->step = 9;
      }
      goto LABEL_193;
    case 9:
      dds3FilterClear();
      if (s_wk->count)
      {
        goto LABEL_130;
LABEL_172:
        v20 = 10;
        v10 = s_wk;
        v10->count = 0;
        goto LABEL_192;
      }
      shpCallProcEnd();
LABEL_130:
      v55 = shpCheckProcEnd() == 0;
      if (v55)
        goto LABEL_172;
      if (v56)
LABEL_180:
      ++s_wk->count;
LABEL_193:
      if ((s_wk->stat & 0x80) == 0)
        return 0;
      shpUpdateCamera();
      shpUpdateBack();
      return 0;
    case 0xA:
      v10 = s_wk;
      count = v10->count;
      if (count)
      {
        if (!v58)
        {
          v10 = s_wk;
          count = v10->count;
        }
        if (count >= 2)
        {
          v10 = s_wk;
          v20 = 11;
          v10->count = 0;
          goto LABEL_192;
        }
      }
      else
      {
        if (!v58)
        shpSetStatDraw(0);
        s_wk->stat &= ~0x80u;
      }
      goto LABEL_180;
    case 0xB:
      v59 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
      _ctor(v59, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      return v59;
    default:
      goto LABEL_193;
  }
}

// 0x2189450
void shpSetColorModel(u32 a_abgr, s32 a_defObjId) {
  s32 i;

  for (i = 0; i != 16; ++i)
  {
    while (1)
    {
      if (a_defObjId != i)
        break;
      shpSetColor(a_defObjId, 0x80808080);
      if (++i == 16)
        return;
    }
    shpSetColor(i, a_abgr);
  }
}

// 0x2189520
void shpDrawBack(void) {
  u32 stat;
  u8 v5;
  s32 count;
  tagSHP_MENU_WK *pMenu;
  s32 v9;
  u32 v10;
  s32 objId;
  s32 i;
  u32 v13;

  stat = s_wk->stat;
  if ((stat & 0x100) == 0)
    goto LABEL_4;
  if ((stat & 0x20000) == 0)
    goto LABEL_12;
  goto LABEL_9000;
  if ((s_wk->stat & 0x20000) == 0)
  {
LABEL_12:
    v5 = 64;
    goto LABEL_24;
  }
LABEL_9000:
  count = 30 - s_wk->count;
LABEL_22:
  v5 = (s32)(f32)((f32)((f32)((f32)count * 64.0) / 30.0) + 64.0);
  goto LABEL_24;
LABEL_4:
  if ((stat & 0x20000) == 0)
    goto LABEL_6;
  goto LABEL_15;
  if ((s_wk->stat & 0x20000) != 0)
  {
LABEL_15:
    count = s_wk->count;
    goto LABEL_22;
  }
LABEL_6:
  v5 = 0x80;
LABEL_24:
  pMenu = s_wk->pMenu;
  if (!pMenu)
    return;
  v9 = (u16)(v5 << 8) | (v5 << 16) | v5;
  v10 = v9 | 0x80000000;
  objId = pMenu->objId;
  for (i = 0; i != 16; ++i)
  {
    while (1)
    {
      if (objId != i)
        break;
      if (!v13)
      shpSetColor(objId, 0x80808080);
      if (++i == 16)
        return;
    }
    if (!v13)
    shpSetColor(i, v10);
  }
}

// 0x21897e0
void shpDrawGoodPoint(void) {
  ;
}

// 0x21897f0
dds3ProcessFunc_t shpDrawProcess(dds3ProcessID_t *proc) {
  f32 v5;
  u32 stat;
  u32 v8;
  tagSHP_WK *v9;
  u32 v10;
  f32 v11;
  u32 v12;
  s32 v13;
  s32 count;
  f32 TitleAlphaRate;
  s32 shopType;
  tagSHP_WK *v20;
  f32 v21;
  tagSHP_WK *v31;
  u32 v32;
  tagSHP_WK *v33;
  s32 v34;
  s32 v35;
  s32 v36;
  s32 v37;
  s32 v38;
  s32 v39;
  s32 a_mag;
  s32 a_trade;
  s32 v42;
  s32 topNo;
  s32 drwNo;
  s32 selMax;
  s32 drwMax;
  s32 selNumMax;
  s32 yen;
  s32 mag;
  s32 trade;
  s32 actType;
  s32 v53;
  u32 v54;
  s32 Hierarchy;
  f32 v57;
  s32 v59;
  tagSHP_WK *v60;
  tagSHP_MENU_WK *pMenu;
  f32 v63;
  s32 v64;
  s32 v68;
  s32 v71;
  void *gameObject;
  s32 v74;
  u32 v76;
  s32 step;
  u8 PanelAlpha;
  u8 v81;
  s16 SelectId;
  s32 v84;
  s32 v85;
  s32 v86;
  s64 v88;
  s32 selNum;

  if ((s_wk->stat & 4) == 0)
    return 0;
  MilkHallBackObjActive(shpUIManager, 1, 0);
  v5 = 0.0;
  stat = s_wk->stat;
  if ((stat & 0x1000) == 0)
    goto LABEL_11;
  if ((stat & 0x4000) == 0)
  {
    v5 = 255.0;
    goto LABEL_12;
  }
  if ((stat & 0x10000) == 0)
  {
    count = s_wk->count;
    goto LABEL_71;
  }
  count = 20 - s_wk->count;
LABEL_71:
  v5 = (f32)((f32)count * 255.0) / 20.0;
LABEL_12:
  v9 = s_wk;
  v10 = v9->stat;
  if ((v10 & 0x8000) == 0)
    goto LABEL_13;
  if (v8)
  {
    if ((v10 & 0x10000) == 0)
    {
LABEL_27:
      if (!v12)
      {
        v9 = s_wk;
      }
      v13 = v9->count;
      goto LABEL_40;
    }
  }
  else
  {
    v9 = s_wk;
    if ((v9->stat & 0x10000) == 0)
      goto LABEL_27;
  }
  if (!v12)
  {
    v9 = s_wk;
  }
  v13 = 13 - v9->count;
LABEL_40:
  v11 = (f32)((f32)v13 * 255.0) / 13.0;
  goto LABEL_42;
LABEL_11:
  goto LABEL_12;
LABEL_13:
  if (!v8)
  {
    v10 = s_wk->stat;
  }
  if ((v10 & 0x10000) != 0)
    v11 = 0.0;
  else
    v11 = 255.0;
LABEL_42:
  shpDrawBack();
  TitleAlphaRate = fclGetTitleAlphaRate();
  shopType = s_wk->shopType;
  shpBackSpr(shopType, TitleAlphaRate, v5);
  v20 = s_wk;
  if (v20->step != 7)
  {
    if (!op_Inequality(shpUIManager, 0, 0))
    {
LABEL_86:
LABEL_87:
      if ((u32)(s_wk->step - 3) > 4)
        goto LABEL_117;
      fclDraw();
      goto LABEL_118;
    }
    if (CheckItemListActive(shpUIManager, 0))
    {
      goto LABEL_60;
    }
    goto LABEL_9002;
    if (CheckItemListActive(shpUIManager, 0))
    {
LABEL_60:
      ItemListActive(shpUIManager, 0, 0);
      if (!CheckSODAListActive(shpUIManager, 0))
        goto LABEL_64;
      goto LABEL_79;
LABEL_78:
      if (!CheckSODAListActive(shpUIManager, 0))
      {
LABEL_64:
        goto LABEL_65;
      }
LABEL_79:
      SODAListActive(shpUIManager, 0, 0);
LABEL_65:
      if (!CheckMAGListActive(shpUIManager, 0))
        goto LABEL_86;
      MAGListActive(shpUIManager, 0, 0);
      goto LABEL_86;
    }
LABEL_9002:
    goto LABEL_78;
  }
  v20 = s_wk;
  if ((v20->pMenu->actType & 2) == 0)
    goto LABEL_86;
  if ((v20->stat & 0x8000) != 0)
    v21 = v11 / 255.0;
  else
    v21 = 1.0;
  if (v20->ctrlType != 5)
  {
    selNum = -1;
    goto LABEL_104;
  }
  v20 = s_wk;
  selNum = v20->selNum;
LABEL_104:
  v33 = s_wk;
  if ((v33->stat & 0x2000) != 0)
  {
    if (!v32)
    {
      v33 = s_wk;
    }
    drwNo = v33->drwNo;
    topNo = v33->topNo;
    selMax = v33->selMax;
    drwMax = v33->drwMax;
    selNumMax = v33->selNumMax;
    yen = v33->yen;
    mag = v33->mag;
    trade = v33->trade;
    actType = v33->pMenu->actType;
    shpItemListTest(actType, topNo, drwNo, selMax, drwMax, selNum, selNumMax, yen, mag, trade, v21);
  }
  else
  {
    if (!v32)
    {
      v33 = s_wk;
    }
    v35 = v33->drwNo;
    v34 = v33->topNo;
    v36 = v33->selMax;
    v37 = v33->drwMax;
    v38 = v33->selNumMax;
    v39 = v33->yen;
    a_mag = v33->mag;
    a_trade = v33->trade;
    v42 = v33->pMenu->actType;
    shpItemListTest(v42, v34, v35, v36, v37, selNum, v38, v39, a_mag, a_trade, 0.0);
  }
  goto LABEL_87;
LABEL_117:
LABEL_118:
  v31 = s_wk;
  if ((v31->stat & 0x20) == 0)
    goto LABEL_149;
  v53 = (u8)v31->shopType;
  if (v53)
    goto LABEL_121;
  goto LABEL_9003;
  if (s_wk->shopType)
  {
LABEL_121:
    if (v54)
    {
      Hierarchy = fclGetHierarchy();
      if (Hierarchy)
        goto LABEL_123;
    }
    else
    {
      v86 = fclGetHierarchy();
      if (v86)
      {
LABEL_123:
        v59 = 1;
LABEL_125:
        v60 = s_wk;
        pMenu = v60->pMenu;
        if (pMenu)
        {
          v60 = s_wk;
          pMenu = v60->pMenu;
          if (pMenu->actType == 530)
          {
            v60 = s_wk;
            if ((v60->stat & 0x2000) != 0)
              v59 = 1;
          }
        }
        nwdDrawKeyHelp(v59, v57);
        goto LABEL_149;
      }
    }
    v59 = s_wk->step > 6;
    goto LABEL_125;
  }
LABEL_9003:
  if (!v54)
  if ((fclGetSelectId() & 0x8000) == 0)
    goto LABEL_143;
  if (fclGetHierarchy())
  {
LABEL_143:
    v64 = 1;
    goto LABEL_145;
  }
  v64 = 0;
LABEL_145:
  if ((s_wk->stat & 0x8000) == 0)
  {
    knyDrawKeyHelp(v64, v63);
  }
LABEL_149:
  if (s_wk->step != 3)
    goto LABEL_164;
  v68 = fclGetHierarchy();
  if (v68 < 0)
    goto LABEL_164;
  v71 = s_wk->shopType;
  shpRootMenuTitle(v71);
  gameObject = get_gameObject(**((void ***)Project_shp_UI_manager + 23), 0);
  SetActive(gameObject, 1, 0);
  UniSetMenuStat();
  UniSetText();
  v74 = fclGetHierarchy();
  if (v74)
  {
    if (v76)
LABEL_174:
    MenuTitleSet(shpUIManager, 0);
LABEL_184:
    if (s_wk->step != 3)
      return 0;
    goto LABEL_185;
  }
  ShopNameTitleSet(shpUIManager, 0);
  goto LABEL_184;
LABEL_164:
  step = (u8)s_wk->step;
  if (step == 8)
    goto LABEL_170;
  if (step == 7)
    goto LABEL_170;
  goto LABEL_184;
LABEL_170:
  if (s_wk->pMenu)
  {
    goto LABEL_174;
  }
  ButtonGuideDispOff();
  goto LABEL_184;
LABEL_185:
  PanelAlpha = fclGetPanelAlpha();
  if (PanelAlpha)
  {
    v81 = PanelAlpha;
    SelectId = fclGetSelectIdEx();
    v84 = SelectId;
    if (s_wk->shopType)
    {
      if (v84 > 1024)
      {
        if (v84 == 2048)
        {
          v85 = 7;
          goto LABEL_236;
        }
        if ((u16)v84 == 4096)
        {
          v85 = 9;
          goto LABEL_236;
        }
        if ((u16)v84 == 0x2000)
        {
          v85 = 11;
          goto LABEL_236;
        }
LABEL_221:
        if ((v84 & 0x1000) != 0)
          v85 = 12;
        else
          v85 = -1;
        goto LABEL_236;
      }
      if (v84 != 144)
      {
        if ((u16)v84 == 256)
        {
          v85 = 8;
          goto LABEL_236;
        }
        if ((u16)v84 == 1024)
        {
          v85 = 10;
          goto LABEL_236;
        }
        goto LABEL_221;
      }
LABEL_224:
      v85 = 39;
      goto LABEL_236;
    }
    if (v84 <= 32)
    {
      v88 = v84 - 16;
      if ((u32)v88 < 3)
      {
        v85 = dword_3E65AB0[v88];
        goto LABEL_236;
      }
      if (v84 == 32)
      {
        v85 = 1;
        goto LABEL_236;
      }
    }
    else
    {
      if (v84 == 64)
      {
        v85 = 3;
        goto LABEL_236;
      }
      if ((u16)v84 == 144)
        goto LABEL_224;
      if ((u16)v84 == 0x2000)
      {
        v85 = 4;
        goto LABEL_236;
      }
    }
    if ((v84 & 0x1000) != 0)
      v85 = 2;
    else
      v85 = -1;
LABEL_236:
    if (v85 < 0)
      return 0;
    fclCommandHelp(v85, v81);
    return 0;
  }
  return 0;
}

// 0x2173e40
s16 shpGetListItemNo(s32 a_listNo) {
  return s_wk->index[a_listNo];
}

// 0x218a630
s32 shpGetActType(void) {
  tagSHP_MENU_WK *pMenu;

  pMenu = s_wk->pMenu;
  if (!pMenu)
    return 0;
  pMenu = s_wk->pMenu;
  return pMenu->actType;
}

// 0x217a210
void shpSetZoom(s32 a_objId) {
  s64 v5;
  f32 v6;
  f32 v7;
  f32 v8;
  f32 v9;
  tagSHP_WK *v13;
  tagSHP_BACK_WK *back;
  u64 v20;

  if ((s_wk->stat & 0x100) == 0)
  {
    if ((u32)a_objId > 8)
      return;
    if (a_objId)
    {
      goto LABEL_8;
    }
    a_objId = s_wk->shopType == 1;
LABEL_8:
    v5 = (s64)shpCameraPar->zoomPar + 16 * (u32)a_objId;
    v6 = *(f32 *)(v5 + 32);
    v8 = *(f32 *)(v5 + 40);
    v7 = *(f32 *)(v5 + 44);
    v9 = *(f32 *)(v5 + 36) + -100.0;
    shpSetMove3D(v6, v9, v8, v7, 30);
    shpSetMoveBack(v6, v9, v8, v7, 30);
    s_wk->stat |= 0x100u;
    goto LABEL_20;
  }
  shpSetMove3DDef(30);
  v13 = s_wk;
  back = v13->back;
  __asm { FMOV            V1.2S, #30.0 }
  v20 = vdiv_f32(vsub_f32((float32x2_t)0x4360000043800000LL, *(float32x2_t *)&back->posx), _D1).n64_u64[0];
  back->type = 2;
  *(u64 *)&back->frame = 30;
  *(u64 *)&back->movx = v20;
  v13->stat &= ~0x100u;
LABEL_20:
  s_wk->stat |= 0x20000u;
}

// 0x218a6e0
void shpSetDrawNewspaper(bool a_bDraw) {
  if (a_bDraw)
  {
    s_wk->stat |= 0x200u;
    return;
  }
  s_wk->stat &= ~0x200u;
}

// 0x2177a10
void shpSetStatDraw(bool a_bDraw) {
  if (!s_wk)
    return;
  if (a_bDraw)
  {
    s_wk->stat |= 4u;
    shpSetDrwModelAll(a_bDraw);
    return;
  }
  else
  {
    s_wk->stat &= ~4u;
  }
  shpSetDrwModelAll(a_bDraw);
}

// 0x217b6d0
s32 shpGetSelectItemID(void) {
  s32 selNo;
  s32 v4;

  goto LABEL_3;
LABEL_7:
  selNo = s_wk->selNo;
  if (selNo < 0)
    goto LABEL_15;
  v4 = s_wk->index[selNo];
  goto LABEL_17;
LABEL_3:
  if (s_wk)
    goto LABEL_7;
LABEL_15:
  v4 = -1;
LABEL_17:
  scrSetIntReturnValue(v4);
  return 1;
}

// 0x217b8d0
s32 shpGetModelHandle(void) {
  u32 IntPara;
  u32 v3;
  u32 v5;
  dds3Basic_t *Basic;
  s32 serialID;

  IntPara = scrGetIntPara(0);
  if (IntPara >= 0xA)
    goto LABEL_15;
  v3 = IntPara;
  v5 = arrConvModelID[v3][1];
  if (v5 < 9)
  {
    Basic = shpGetBasic(v5);
    if (!Basic)
      goto LABEL_15;
    serialID = Basic->serialID;
    goto LABEL_17;
  }
LABEL_15:
  serialID = -1;
LABEL_17:
  scrSetIntReturnValue(serialID);
  return 1;
}

// 0x217bab0
s32 shpSetModelMotion(void) {
  u32 IntPara;
  s32 v2;
  s32 v3;
  u32 v5;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  if (IntPara > 9)
    return 1;
  v3 = v2;
  v5 = arrConvModelID[IntPara][1];
  if (v5 > 8)
    return 1;
  if (v3)
  {
    shpSetSmoothSingleMotion(v5, v3);
    return 1;
  }
  shpSetSmoothLoopMotion(v5, 0);
  return 1;
}

// 0x217bca0
s32 shpCallRelease(void) {
  g_bCallRelease = 1;
  return 1;
}

// 0x217bd80
s32 shpWaitRelease(void) {
  return 1;
}

// 0x217be10
s32 nwdGetSelectModelID(void) {
  s32 objId;
  s32 v6;

  objId = (u16)s_wk->pMenu->objId;
  if ((u16)arrConvModelID[0][1] != objId)
  {
    if ((u16)arrConvModelID[1][1] != objId)
    {
      if ((u16)arrConvModelID[2][1] != objId)
      {
        if ((u16)arrConvModelID[3][1] != objId)
        {
          if ((u16)arrConvModelID[4][1] != objId)
          {
            if ((u16)arrConvModelID[5][1] != objId)
            {
              if ((u16)arrConvModelID[6][1] != objId)
              {
                if ((u16)arrConvModelID[7][1] != objId)
                {
                  if ((u16)arrConvModelID[8][1] == objId)
                  {
                    v6 = 8;
                    goto LABEL_52;
                  }
                  goto LABEL_50;
                }
                v6 = 7;
                goto LABEL_52;
              }
              v6 = 6;
              goto LABEL_52;
            }
            v6 = 5;
            goto LABEL_52;
          }
          v6 = 4;
          goto LABEL_52;
        }
        v6 = 3;
        goto LABEL_52;
      }
      v6 = 2;
      goto LABEL_52;
    }
    v6 = 1;
    goto LABEL_52;
  }
  v6 = 0;
  goto LABEL_52;
LABEL_50:
  if ((u16)arrConvModelID[9][1] != objId)
    return 1;
  v6 = 9;
LABEL_52:
  scrSetIntReturnValue(v6);
  return 1;
}

// 0x217c2d0
s32 knyGetIntimateRank(void) {
  s32 GoodRank;

  GoodRank = knyGetGoodRank();
  scrSetIntReturnValue(GoodRank);
  return 1;
}

// 0x217c4b0
s32 nwdGetIntimateRank(void) {
  s32 GoodRank;

  GoodRank = nwdGetGoodRank();
  scrSetIntReturnValue(GoodRank);
  return 1;
}

// 0x218a7a0
void shpLoadModel(void) {
  s32 shopType;
  f32 v6;
  f32 v7;
  f32 v8;

  shopType = (u8)s_wk->shopType;
  if (shopType == 1)
  {
    nwdLoadModel();
    return;
  }
  if (shopType)
    return;
  v6 = SMDP[6];
  v7 = SMDP[7];
  v8 = SMDP[8];
  shpSetParamInit(0, 3u, 147, 0, v6, v7, v8, -90.0);
  s_wk->charID[0] = 1;
}

// 0x218a930
void shpShutdown(dds3ProcessID_t *proc) {
  char *v7;
  tagSHP_WK *p_fields;
  tagSHP_WK *s_wk_local;
  tagSHP_WK *v16;
  tagSHP_WK *v17;
  tagSHP_WK *v18;
  tagSHP_WK *v19;
  tagSHP_WK *v20;
  tagSHP_WK *v21;
  tagSHP_WK *v22;
  struct shpMain *v24;
  tagSHP_WK *v26;
  UnityEngine_SceneManagement_Scene_o v27;

  GBWK->EventBit[72] &= ~1u;
  UIDestroy(shpUIManager, 0);
  shpRelease();
  v7 = "";
  ButtonGuideName = "";
  GuideObjClr();
  if (SE_NotKillFlag)
  {
    goto LABEL_16;
  }
  p2sdUnLoadAllSMGFile();
LABEL_16:
  p_fields = &s_wk->fields;
  if (!!dds3ExistProcess(&p_fields->drawPID))
  {
    v26 = &s_wk->fields;
    dds3KillProcess(&v26->drawPID, 0);
  }
  v27.m_Handle = GetSceneByName("UI_konnouya", 0).m_Handle;
  UnloadSceneAsync_61083440(v27, 0);
  s_wk_local = s_wk;
  s_wk_local->drawPID = 0;
  v16 = s_wk;
  v16->cntrPID = 0;
  v17 = s_wk;
  v17->Menu = 0;
  v18 = s_wk;
  v18->pMenu = 0;
  v19 = s_wk;
  v19->back = 0;
  v20 = s_wk;
  v20->pDatScr = 0;
  v21 = s_wk;
  v21->charID = 0;
  v22 = s_wk;
  v22->index = 0;
  s_wk = 0;
  MenuActive = 0;
  g_shop_campOpen = 0;
  g_mainPID = 0;
  v24 = ((char *)v24 + 8);
  BYTE3(SMDP) = 0;
}

// 0x218ad50
dds3ProcessID_t *ProcessStart(s32 a_shoptype) {
  s8 v2;
  tagSHP_WK *v3;
  tagSHP_WK *s_wk_local;
  Il2CppObject *v7;
  tagSHP_WK *v8;
  tagSHP_MENU_WK *pMenu;
  s64 v11;
  tagSHP_WK *v15;
  s32 shopType;
  s32 v17;
  dds3ProcessFunc_t v20;
  shutdownfuncDelegate v21;
  Il2CppObject *v23;
  dds3ProcessID_t *started;
  tagSHP_WK *v26;
  dds3ProcessFunc_t v27;
  dds3ProcessID_t *v28;

  v2 = a_shoptype;
  v3 = Allocate(tagSHP_WK);
  _ctor(v3);
  s_wk = v3;
  s_wk_local = s_wk;
  v7 = Allocate(tagSHP_MENU_WK);
  _ctor(v7, 0);
  s_wk_local->pMenu = (tagSHP_MENU_WK *)v7;
  v8 = s_wk;
  v8->shopType = v2;
  pMenu = v8->pMenu;
  LODWORD(v8) = (u8)byte_5755E7A;
  pMenu->actType = 0;
  v11 = *(u64 *)(*((u64 *)*((const MethodInfo *)dat + 2).virtualMethodPointer + 60) + 56);
  *(u32 *)(v11 + 320) |= 4u;
  shpInit();
  shpInitFunc();
  shpLoadModel();
  sdfMemSetAllocated();
  v15 = s_wk;
  if ((v15->stat & 0x400) == 0)
  {
    shopType = (u8)v15->shopType;
    if (shopType)
      goto LABEL_14;
    goto LABEL_9000;
    if (s_wk->shopType)
    {
LABEL_14:
      shopType = (u8)s_wk->shopType;
      if (shopType == 1)
        v17 = 18;
      else
        v17 = -1;
LABEL_20:
      sndBgmLoadId_XF(v17);
      s_wk->stat |= 0x400u;
      goto LABEL_22;
    }
LABEL_9000:
    v17 = 17;
    goto LABEL_20;
  }
LABEL_22:
  if (!p2sdLoadCheckMidi(4259840))
  {
    p2sdLoadSMGFile(4259840);
  }
  v20 = Allocate(dds3ProcessFunc_t);
  _ctor(v20, 0, Method_Project_shpMain_Process__, 0);
  v21 = Allocate(shutdownfuncDelegate);
  _ctor(v21, 0, Method_Project_shpMain_shpShutdown__, 0);
  v23 = s_wk;
  started = dds3StartProcess("shop_main", 1026, 0, 0, v20, v21, v23);
  g_mainPID = started;
  v26 = s_wk;
  v27 = Allocate(dds3ProcessFunc_t);
  _ctor(v27, 0, Method_Project_shpMain_shpDrawProcess__, 0);
  v28 = dds3StartProcess("shop_draw", 11024, 0, 0, v27, 0, s_wk);
  v26->drawPID = v28;
  return g_mainPID;
}

// 0x218b1e0
s32 ProcessCheck(void) {
  if (!g_mainPID)
    return 0;
  if (dds3GetProcessStat(g_mainPID) != 3)
  {
    if (dds3GetProcessStat(g_mainPID))
    {
      return 1;
    }
  }
  g_mainPID = 0;
  return 0;
}

// 0x218b350
void shpRootCallProcEnd(void) {
  ProcessEnd();
  if (g_bCallRelease)
    return;
  gohStopSequence();
}

// 0x218b420
u8 shpRootCheckProcEnd(void) {
  u8 v2;

  v2 = ProcessCheck();
  if (g_bCallRelease)
    return v2;
  if (!gohCheckSequence())
    ++v2;
  return v2;
}

// 0x218b510
dds3ProcessFunc_t shpRootProcess(dds3ProcessID_t *PID) {
  s32 v5;
  bool v10;
  s32 v15;
  u32 v18;
  dds3ProcessFunc_t v23;
  u32 v25;
  s32 g_shptype_local;

  if (g_rootstep > 4)
    return 0;
  switch (g_rootstep)
  {
    case 0u:
      v5 = ProcessCheck();
      if (v5)
        goto LABEL_10;
      goto LABEL_9001;
      if (v15)
      {
LABEL_10:
        if (s_wk)
        {
          if (s_wk->shopType == 1)
          {
            fldFacilityMistDraw(1);
            return 0;
          }
        }
        return 0;
      }
LABEL_9001:
      if (g_endmode == 2)
      {
        v18 = 2 * g_shpsave;
        gohStartSequence(v18);
        g_NoRelese = 0;
        g_rootstep = 1;
        return 0;
      }
      goto LABEL_58;
    case 1u:
      if (gohCheckSequence() != 1)
        return 0;
LABEL_58:
      *(u16 *)&g_rootstep = 2;
      return 0;
    case 2u:
      if (!g_rootcnt)
        shpRootCallProcEnd();
      v10 = shpRootCheckProcEnd() == 0;
      if (!v10)
      {
        ++g_rootcnt;
        return 0;
      }
      *(u16 *)&g_rootstep = 3;
      return 0;
    case 3u:
      if (g_debugPID)
      {
        dds3FadeIn(0, 0, 0, 1u);
        sndBgmFadeOut2();
        goto LABEL_78;
      }
      if (g_bCallRelease)
        goto LABEL_95;
      if (g_NoRelese)
      {
LABEL_95:
        g_NoRelese = 0;
      }
      else
      {
        if (g_shpsave)
        {
          if (!v25)
          g_shptype_local = 6;
        }
        else
        {
          if (!v25)
          mapTitleAutoFade();
          g_shptype_local = g_shptype;
        }
        mapReturnFromShop(g_shptype_local);
      }
LABEL_78:
      v23 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
      _ctor(v23, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      return v23;
    case 4u:
      if (sdfMemCheckRelease())
        return 0;
      g_rootstep = 0;
      return 0;
    default:
      return 0;
  }
}

// 0x218ba80
void shpRootShutdown(dds3ProcessID_t *PID) {
  if (!!gohCheckSequence())
  {
    sdfMemRelease();
    fldFacilityMistDestroy(1);
  }
  g_rootPID = 0;
}

// 0x218bbd0
void shpProcessStart(s32 a_shoptype) {
  dds3ProcessFunc_t v3;
  shutdownfuncDelegate v4;
  dds3ProcessID_t *started;
  bool v8;

  v3 = Allocate(dds3ProcessFunc_t);
  _ctor(v3, 0, Method_Project_shpMain_shpRootProcess__, 0);
  v4 = Allocate(shutdownfuncDelegate);
  _ctor(v4, 0, Method_Project_shpMain_shpRootShutdown__, 0);
  started = dds3StartProcess("shop_root", 1026, 0, 0, v3, v4, 0);
  g_rootPID = started;
  v8 = a_shoptype == 2;
  if (a_shoptype == 2)
    a_shoptype = 0;
  g_shpsave = v8;
  g_shptype = a_shoptype;
  sdfMemRelease();
  ProcessStart(g_shptype);
  *(u16 *)&g_bCallRelease = 0;
  SE_NotKillFlag = 0;
  *(u16 *)&g_rootstep = 4;
}

// 0x218be00
void shpKonnouyaProcessStart(void) {
  shpProcessStart(0);
}

// 0x218be70
void shpMilkHallProcessStart(void) {
  shpProcessStart(1);
}

// 0x218bee0
void shpProcessEnd(void) {
  if (!dds3ExistProcess(g_rootPID))
    return;
  *(u16 *)&g_rootstep = 2;
}

// 0x217c6b0
bool shpProcessCheck(void) {
  if (!g_rootPID)
    return 0;
  if (dds3GetProcessStat(g_rootPID) != 3)
  {
    if (dds3GetProcessStat(g_rootPID))
    {
      return 1;
    }
  }
  g_rootPID = 0;
  return 0;
}

// 0x2180690
s32 shpGetShopType(void) {
  return s_wk->shopType;
}

// 0x218bff0
bool shpCheckLoadShopUI(void) {
  return UIsceneLoadReq->isDone;
}
