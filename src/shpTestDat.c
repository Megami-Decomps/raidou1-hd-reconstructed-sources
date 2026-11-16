#include "types.h"
#include "cmpmisc.h"
#include "sbtlitem.h"
#include "shpmain.h"
#include "shptestdat.h"

typedef struct tagSHPTDAT_WK tagSHPTDAT_WK;
typedef struct tagSHP_GUEST_WK tagSHP_GUEST_WK;

tagSHPTDAT_WK *wk;
static u32 *shpTestDatItemStatType;

// 0x21aea50
tagSHPTDAT_WK *shpGetWork(void) {
  return wk;
}

// 0x21aead0
s32 MakeIndexList(s32 a_listtype, s32 *a_pList) {
  u32 v6;
  s64 v7;
  char *v8;
  s64 v9;
  char *v10;
  s64 v11;
  char *v12;
  char *v13;
  char *v15;
  char *v16;
  char *v17;
  char *v18;
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

  v6 = -1;
  if (!a_pList)
    return v6;
  if (!wk)
    return v6;
  v6 = 0;
  switch (a_listtype)
  {
    case 1:
      v7 = 0;
      v6 = 0;
      while (1)
      {
        if (tbldata[v7]->type == 1)
        {
          v8 = (char *)a_pList + 4 * (s32)v6++;
          *((u32 *)v8 + 8) = v7;
        }
        if (++v7 == 768)
          goto LABEL_37;
      }
    case 3:
      v9 = 0;
      v6 = 0;
      while (1)
      {
        if (tbldata[v9]->type == 32)
        {
          v10 = (char *)a_pList + 4 * (s32)v6++;
          *((u32 *)v10 + 8) = v9;
        }
        if (++v9 == 768)
          goto LABEL_37;
      }
    case 4:
      v11 = 0;
      v6 = 0;
      do
      {
        if (datGetItemNumEquipMinus(v11) >= 1)
        {
          if ((tbldata[v11]->flg & 4) == 0)
          {
            v12 = (char *)a_pList + 4 * (s32)v6++;
            *((u32 *)v12 + 8) = v11;
          }
        }
        ++v11;
      }
      while (v11 != 768);
LABEL_37:
      if ((s32)v6 > 767)
        return v6;
LABEL_72:
      sub_188E3B0(&a_pList[v6], 255, 4 * (767 - v6) + 4);
      return v6;
    case 5:
      v6 = 0;
      if (cmpChkDevilStockExist(0))
      {
        v6 = 1;
        a_pList[0] = 0;
        if (!cmpChkDevilStockExist(1))
        {
LABEL_41:
          if (!cmpChkDevilStockExist(2))
            goto LABEL_42;
          goto LABEL_76;
        }
      }
      else if (!cmpChkDevilStockExist(1))
      {
        goto LABEL_41;
      }
      v15 = (char *)a_pList + 4 * v6++;
      *((u32 *)v15 + 8) = 1;
      if (!cmpChkDevilStockExist(2))
      {
LABEL_42:
        if (!cmpChkDevilStockExist(3))
          goto LABEL_43;
        goto LABEL_77;
      }
LABEL_76:
      v16 = (char *)a_pList + 4 * v6++;
      *((u32 *)v16 + 8) = 2;
      if (!cmpChkDevilStockExist(3))
      {
LABEL_43:
        if (!cmpChkDevilStockExist(4))
          goto LABEL_44;
        goto LABEL_78;
      }
LABEL_77:
      v17 = (char *)a_pList + 4 * v6++;
      *((u32 *)v17 + 8) = 3;
      if (!cmpChkDevilStockExist(4))
      {
LABEL_44:
        if (!cmpChkDevilStockExist(5))
          goto LABEL_45;
        goto LABEL_79;
      }
LABEL_78:
      v18 = (char *)a_pList + 4 * v6++;
      *((u32 *)v18 + 8) = 4;
      if (!cmpChkDevilStockExist(5))
      {
LABEL_45:
        if (!cmpChkDevilStockExist(6))
          goto LABEL_46;
        goto LABEL_80;
      }
LABEL_79:
      v19 = (char *)a_pList + 4 * v6++;
      *((u32 *)v19 + 8) = 5;
      if (!cmpChkDevilStockExist(6))
      {
LABEL_46:
        if (!cmpChkDevilStockExist(7))
          goto LABEL_47;
        goto LABEL_81;
      }
LABEL_80:
      v20 = (char *)a_pList + 4 * v6++;
      *((u32 *)v20 + 8) = 6;
      if (!cmpChkDevilStockExist(7))
      {
LABEL_47:
        if (!cmpChkDevilStockExist(8))
          goto LABEL_48;
        goto LABEL_82;
      }
LABEL_81:
      v21 = (char *)a_pList + 4 * v6++;
      *((u32 *)v21 + 8) = 7;
      if (!cmpChkDevilStockExist(8))
      {
LABEL_48:
        if (!cmpChkDevilStockExist(9))
          goto LABEL_49;
        goto LABEL_83;
      }
LABEL_82:
      v22 = (char *)a_pList + 4 * v6++;
      *((u32 *)v22 + 8) = 8;
      if (!cmpChkDevilStockExist(9))
      {
LABEL_49:
        if (!cmpChkDevilStockExist(10))
          goto LABEL_50;
        goto LABEL_84;
      }
LABEL_83:
      v23 = (char *)a_pList + 4 * v6++;
      *((u32 *)v23 + 8) = 9;
      if (!cmpChkDevilStockExist(10))
      {
LABEL_50:
        if (!cmpChkDevilStockExist(11))
          goto LABEL_51;
        goto LABEL_85;
      }
LABEL_84:
      v24 = (char *)a_pList + 4 * v6++;
      *((u32 *)v24 + 8) = 10;
      if (!cmpChkDevilStockExist(11))
      {
LABEL_51:
        if (!cmpChkDevilStockExist(12))
          goto LABEL_52;
        goto LABEL_86;
      }
LABEL_85:
      v25 = (char *)a_pList + 4 * v6++;
      *((u32 *)v25 + 8) = 11;
      if (!cmpChkDevilStockExist(12))
      {
LABEL_52:
        if (!cmpChkDevilStockExist(13))
          goto LABEL_53;
        goto LABEL_87;
      }
LABEL_86:
      v26 = (char *)a_pList + 4 * v6++;
      *((u32 *)v26 + 8) = 12;
      if (!cmpChkDevilStockExist(13))
      {
LABEL_53:
        if (!cmpChkDevilStockExist(14))
          goto LABEL_54;
        goto LABEL_88;
      }
LABEL_87:
      v27 = (char *)a_pList + 4 * v6++;
      *((u32 *)v27 + 8) = 13;
      if (!cmpChkDevilStockExist(14))
      {
LABEL_54:
        if (!cmpChkDevilStockExist(15))
          goto LABEL_55;
        goto LABEL_89;
      }
LABEL_88:
      v28 = (char *)a_pList + 4 * v6++;
      *((u32 *)v28 + 8) = 14;
      if (!cmpChkDevilStockExist(15))
      {
LABEL_55:
        if (!cmpChkDevilStockExist(16))
          goto LABEL_56;
        goto LABEL_90;
      }
LABEL_89:
      v29 = (char *)a_pList + 4 * v6++;
      *((u32 *)v29 + 8) = 15;
      if (!cmpChkDevilStockExist(16))
      {
LABEL_56:
        if (!cmpChkDevilStockExist(17))
          goto LABEL_57;
        goto LABEL_91;
      }
LABEL_90:
      v30 = (char *)a_pList + 4 * v6++;
      *((u32 *)v30 + 8) = 16;
      if (!cmpChkDevilStockExist(17))
      {
LABEL_57:
        if (!cmpChkDevilStockExist(18))
          goto LABEL_58;
        goto LABEL_92;
      }
LABEL_91:
      v31 = (char *)a_pList + 4 * v6++;
      *((u32 *)v31 + 8) = 17;
      if (!cmpChkDevilStockExist(18))
      {
LABEL_58:
        if (!cmpChkDevilStockExist(19))
          goto LABEL_59;
        goto LABEL_93;
      }
LABEL_92:
      v32 = (char *)a_pList + 4 * v6++;
      *((u32 *)v32 + 8) = 18;
      if (!cmpChkDevilStockExist(19))
      {
LABEL_59:
        if (!cmpChkDevilStockExist(20))
          goto LABEL_60;
        goto LABEL_94;
      }
LABEL_93:
      v33 = (char *)a_pList + 4 * v6++;
      *((u32 *)v33 + 8) = 19;
      if (!cmpChkDevilStockExist(20))
      {
LABEL_60:
        if (!cmpChkDevilStockExist(21))
          goto LABEL_61;
        goto LABEL_95;
      }
LABEL_94:
      v34 = (char *)a_pList + 4 * v6++;
      *((u32 *)v34 + 8) = 20;
      if (!cmpChkDevilStockExist(21))
      {
LABEL_61:
        if (!cmpChkDevilStockExist(22))
          goto LABEL_62;
        goto LABEL_96;
      }
LABEL_95:
      v35 = (char *)a_pList + 4 * v6++;
      *((u32 *)v35 + 8) = 21;
      if (!cmpChkDevilStockExist(22))
      {
LABEL_62:
        if (!cmpChkDevilStockExist(23))
          goto LABEL_63;
        goto LABEL_97;
      }
LABEL_96:
      v36 = (char *)a_pList + 4 * v6++;
      *((u32 *)v36 + 8) = 22;
      if (!cmpChkDevilStockExist(23))
      {
LABEL_63:
        if (!cmpChkDevilStockExist(24))
          goto LABEL_64;
        goto LABEL_98;
      }
LABEL_97:
      v37 = (char *)a_pList + 4 * v6++;
      *((u32 *)v37 + 8) = 23;
      if (!cmpChkDevilStockExist(24))
      {
LABEL_64:
        if (!cmpChkDevilStockExist(25))
          goto LABEL_65;
        goto LABEL_99;
      }
LABEL_98:
      v38 = (char *)a_pList + 4 * v6++;
      *((u32 *)v38 + 8) = 24;
      if (!cmpChkDevilStockExist(25))
      {
LABEL_65:
        if (!cmpChkDevilStockExist(26))
          goto LABEL_66;
        goto LABEL_100;
      }
LABEL_99:
      v39 = (char *)a_pList + 4 * v6++;
      *((u32 *)v39 + 8) = 25;
      if (!cmpChkDevilStockExist(26))
      {
LABEL_66:
        if (!cmpChkDevilStockExist(27))
          goto LABEL_67;
        goto LABEL_101;
      }
LABEL_100:
      v40 = (char *)a_pList + 4 * v6++;
      *((u32 *)v40 + 8) = 26;
      if (!cmpChkDevilStockExist(27))
      {
LABEL_67:
        if (!cmpChkDevilStockExist(28))
          goto LABEL_68;
        goto LABEL_102;
      }
LABEL_101:
      v41 = (char *)a_pList + 4 * v6++;
      *((u32 *)v41 + 8) = 27;
      if (!cmpChkDevilStockExist(28))
      {
LABEL_68:
        if (!cmpChkDevilStockExist(29))
          goto LABEL_69;
        goto LABEL_103;
      }
LABEL_102:
      v42 = (char *)a_pList + 4 * v6++;
      *((u32 *)v42 + 8) = 28;
      if (!cmpChkDevilStockExist(29))
      {
LABEL_69:
        if (!cmpChkDevilStockExist(30))
          goto LABEL_70;
        goto LABEL_104;
      }
LABEL_103:
      v43 = (char *)a_pList + 4 * v6++;
      *((u32 *)v43 + 8) = 29;
      if (!cmpChkDevilStockExist(30))
      {
LABEL_70:
        if (!cmpChkDevilStockExist(31))
          goto LABEL_72;
        goto LABEL_71;
      }
LABEL_104:
      v44 = (char *)a_pList + 4 * v6++;
      *((u32 *)v44 + 8) = 30;
      if (!cmpChkDevilStockExist(31))
        goto LABEL_72;
LABEL_71:
      v13 = (char *)a_pList + 4 * v6++;
      *((u32 *)v13 + 8) = 31;
      goto LABEL_72;
    default:
      goto LABEL_72;
  }
}

// 0x21af450
void shpSetWorkRandParam(void) {
  s64 v2;
  u64 v3;
  s64 v5;
  tagSHPTDAT_ITEM_WK *v6;
  tagSHPTDAT_ITEM_WK *v8;
  tagSHPTDAT_PLYITEM_WK *v11;
  tagSHPTDAT_SHPITEM_WK *v12;
  u32 v13;
  u32 v14;
  char v15;
  tagSHPTDAT_PLYITEM_WK *v16;
  s8 v17;
  tagSHPTDAT_SHPITEM_WK *v19;
  tagSHPTDAT_SHPITEM_WK *v20;
  u32 v21;
  tagSHPTDAT_SHPITEM_WK *v22;
  s32 v23;
  tagSHPTDAT_SHPITEM_WK *v24;

  v2 = 0;
  v3 = 1;
  do
  {
    v5 = v2;
    v6 = wk->item[v2 + 1];
    v6->stat = *(u32 *)((char *)&shpTestDatItemStatType->obj.klass + 4 * v2 + 36 - 24 * (v3 / 6));
    v6->price = sub_1905740(2000, 0);
    v8 = wk->item[v2 + 1];
    if (v8->price)
    {
      goto LABEL_12;
    }
    v8->price = 1;
LABEL_12:
    if (wk->item[v2 + 1]->stat == 256)
    {
      v11 = wk->player[v5 + 1];
      v12 = wk->shop[v5 + 1];
      v11->posse = -1;
      v12->stock = -1;
      v13 = sub_1905740(6, 0);
      if (!v13)
        goto LABEL_22;
    }
    else
    {
      v16 = wk->player[v5 + 1];
      v17 = sub_1905740(10, 0);
      v16->posse = v17;
      v19 = wk->shop[v5 + 1];
      v19->stock = sub_1905740(10, 0);
      v13 = sub_1905740(6, 0);
      if (!v13)
      {
LABEL_22:
        v15 = 2;
        goto LABEL_24;
      }
    }
    v14 = v13;
    if (v14 > 4)
      goto LABEL_25;
    v15 = 1;
LABEL_24:
    v20 = wk->shop[v2 + 1];
    v20->stat |= v15;
LABEL_25:
    v22 = wk->shop[v2 + 1];
    if ((v22->stat & 2) != 0)
    {
      if (!v21)
      {
        v22 = wk->shop[v2 + 1];
      }
      v22->stock = 0;
    }
    else
    {
      if (v21)
      {
        if (v22->stock)
          goto LABEL_7;
      }
      else
      {
        if (wk->shop[v2 + 1]->stock)
          goto LABEL_7;
      }
      v23 = sub_1905740(3, 0);
      if (!v23)
      {
        v24 = wk->shop[v2 + 1];
        v24->stat |= 8u;
      }
    }
LABEL_7:
    ++v2;
    ++v3;
  }
  while (v2 != 767);
  wk->reserveId = -1;
}

// 0x21af7e0
tagSHP_GUEST_WK *GetAddrGuestWork(s32 a_guestId) {
  if ((u32)a_guestId > 4)
    return 0;
  if (!wk)
    return 0;
  return wk->guest[a_guestId];
}

// 0x21af8b0
void Init(void) {
  tagSHPTDAT_WK *v1;

  v1 = Allocate(tagSHPTDAT_WK);
  _ctor(v1);
  wk = v1;
}

// 0x21af950
void End(void) {
  if (!wk)
    return;
  wk = 0;
}
