#include "types.h"
#include "evtbit.h"
#include "shpdatdrink.h"
#include "shptestdat.h"

typedef struct tagSHP_GUEST_WK tagSHP_GUEST_WK;

static u8 **shpDatDrinkPoint[5];
static u8 **shpDatDrinkRank;
static s32 **shpDatDrinkSituation;

// 0x21b1110
s32 shpCnvIdChar2Guest(s32 a_charId) {
  if ((u32)(a_charId - 5) > 5)
    return -1;
  else
    return dword_3E65C0C[a_charId - 5];
}

// 0x21b1140
tagSHP_GUEST_WK *shpGetAddrGuestWork(s32 a_guestId) {
  if ((u32)a_guestId > 4)
    return 0;
  if (!wk)
    return 0;
  return wk->guest[a_guestId];
}

// 0x21b1240
s32 shpDrinkGetGiveProcedure(s32 a_charId, s32 a_drinkId) {
  s32 *v5;
  s64 v7;
  s32 v8;
  s64 v9;
  tagSHP_GUEST_WK *AddrGuestWork;
  tagSHP_GUEST_WK *v11;
  u8 *v13;
  s16 *intimacyPoint;
  s32 v15;
  s16 v16;
  s32 v17;
  s32 v18;
  s32 i;
  s32 v21;
  bool v22;
  s32 *v25;
  u32 bitDrinkRank;
  s32 v27;
  u32 v28;
  s32 v31;
  s32 v32;
  s32 v33;
  s32 v34;
  s32 v35;
  s32 v36;
  s32 v37;
  s32 v38;
  s32 v39;

  v5 = NewSpecific(s32, 2u);
  *(u64 *)&v5[0] = 0;
  v7 = v5;
  v8 = a_charId - 5;
  if ((u32)(a_charId - 5) > 5)
    return -1;
  if (((0x27u >> v8) & 1) == 0)
    return -1;
  v9 = dword_3E65C24[v8];
  AddrGuestWork = shpGetAddrGuestWork(v9);
  if (!AddrGuestWork)
    return -1;
  v11 = AddrGuestWork;
  v13 = shpDatDrinkPoint[v9][a_drinkId];
  intimacyPoint = v11->intimacyPoint;
  v15 = v13[0];
  v16 = intimacyPoint[0];
  *(u32 *)(v7 + 32) = v15;
  v17 = (s16)(v16 + v15);
  if (v17 >= 255)
    LOWORD(v17) = 255;
  intimacyPoint[0] = v17;
  v13 = shpDatDrinkPoint[v9][a_drinkId];
  intimacyPoint = v11->intimacyPoint;
  v18 = v13[1];
  *(u32 *)(v7 + 36) = v18;
  LOWORD(v18) = intimacyPoint[1] + v18;
  intimacyPoint[1] = v18;
  if ((s16)v18 >= 256)
    intimacyPoint[1] = 255;
  for (i = 0; ; ++i)
  {
    v21 = shpDatDrinkSituation[i][0];
    if (v21 < 0)
      break;
    v22 = evtBitCheck(v21);
    if (!v22)
      continue;
    v25 = shpDatDrinkSituation[i];
    if (v25[2] == -1)
    {
      if (v25[1] == a_charId)
        goto LABEL_42;
    }
    else
    {
      if (v25[1] != a_charId)
        continue;
      if (v25[2] == a_drinkId)
        goto LABEL_42;
      goto LABEL_9000;
      if (v25[2] == a_drinkId)
      {
LABEL_42:
        v25 = shpDatDrinkSituation[i];
        return v25[3];
      }
LABEL_9000:
    }
  }
  bitDrinkRank = v11->bitDrinkRank;
  if ((bitDrinkRank & 0x200) == 0 && v11->intimacyPoint[1] >= 255)
  {
    a_drinkId = 19;
    v11->bitDrinkRank = bitDrinkRank | 0x200;
    return a_drinkId;
  }
  if ((bitDrinkRank & 1) != 0)
  {
    v28 = v11->bitDrinkRank;
    if ((bitDrinkRank & 2) != 0)
      goto LABEL_61;
LABEL_57:
    v31 = v11->intimacyPoint[0];
    bitDrinkRank = v11->bitDrinkRank;
    if (v31 < shpDatDrinkRank[v9][1])
    {
      LOWORD(v28) = bitDrinkRank;
      goto LABEL_61;
    }
    v39 = 2;
    a_drinkId = 11;
    goto LABEL_105;
  }
  v27 = v11->intimacyPoint[0];
  bitDrinkRank = v11->bitDrinkRank;
  if (v27 >= shpDatDrinkRank[v9][0])
  {
    v39 = 1;
    a_drinkId = 10;
    goto LABEL_105;
  }
  LOWORD(v28) = bitDrinkRank;
  if ((bitDrinkRank & 2) == 0)
    goto LABEL_57;
LABEL_61:
  if ((v28 & 4) == 0)
  {
    v32 = v11->intimacyPoint[0];
    bitDrinkRank = v11->bitDrinkRank;
    if (v32 >= shpDatDrinkRank[v9][2])
    {
      v39 = 4;
      a_drinkId = 12;
      goto LABEL_105;
    }
    LOWORD(v28) = bitDrinkRank;
  }
  if ((v28 & 8) == 0)
  {
    v33 = v11->intimacyPoint[0];
    bitDrinkRank = v11->bitDrinkRank;
    if (v33 < shpDatDrinkRank[v9][3])
    {
      LOWORD(v28) = bitDrinkRank;
      goto LABEL_71;
    }
    v39 = 8;
    a_drinkId = 13;
LABEL_105:
    v11->bitDrinkRank = bitDrinkRank | v39;
    return a_drinkId;
  }
LABEL_71:
  if ((v28 & 0x10) == 0)
  {
    v34 = v11->intimacyPoint[0];
    bitDrinkRank = v11->bitDrinkRank;
    if (v34 >= shpDatDrinkRank[v9][4])
    {
      v39 = 16;
      a_drinkId = 14;
      goto LABEL_105;
    }
    LOWORD(v28) = bitDrinkRank;
  }
  if ((v28 & 0x20) == 0)
  {
    v35 = v11->intimacyPoint[0];
    bitDrinkRank = v11->bitDrinkRank;
    if (v35 >= shpDatDrinkRank[v9][5])
    {
      v39 = 32;
      a_drinkId = 15;
      goto LABEL_105;
    }
    LOWORD(v28) = bitDrinkRank;
  }
  if ((v28 & 0x40) == 0)
  {
    v36 = v11->intimacyPoint[0];
    bitDrinkRank = v11->bitDrinkRank;
    if (v36 >= shpDatDrinkRank[v9][6])
    {
      v39 = 64;
      a_drinkId = 16;
      goto LABEL_105;
    }
    LOWORD(v28) = bitDrinkRank;
  }
  if ((v28 & 0x80) == 0)
  {
    v37 = v11->intimacyPoint[0];
    bitDrinkRank = v11->bitDrinkRank;
    if (v37 >= shpDatDrinkRank[v9][7])
    {
      v39 = 128;
      a_drinkId = 17;
      goto LABEL_105;
    }
    LOWORD(v28) = bitDrinkRank;
  }
  if ((v28 & 0x100) == 0)
  {
    v38 = v11->intimacyPoint[0];
    if (v38 >= shpDatDrinkRank[v9][8])
    {
      bitDrinkRank = v11->bitDrinkRank;
      v39 = 256;
      a_drinkId = 18;
      goto LABEL_105;
    }
  }
  return a_drinkId;
}

// 0x21b1870
s32 shpDrinkGive(s32 a_charId, s32 a_drinkId) {
  s32 *v5;
  s64 v7;
  s32 v8;
  s32 result;
  s64 v10;
  tagSHP_GUEST_WK *AddrGuestWork;
  tagSHP_GUEST_WK *v12;
  s16 *intimacyPoint;
  s16 v16;
  u8 *v17;
  s32 v18;
  s32 v19;
  s32 v20;
  s32 v21;
  u32 bitDrinkRank;
  s32 *p_bitDrinkRank;
  s16 v25;
  s32 v26;
  s32 v27;
  s32 v28;
  s32 v29;
  s32 v30;
  s32 v31;
  s32 v32;
  s32 v33;
  s32 v34;
  s32 v35;

  v5 = NewSpecific(s32, 2u);
  *(u64 *)&v5[0] = 0;
  v7 = v5;
  v8 = a_charId - 5;
  if ((u32)(a_charId - 5) > 5)
    return -2;
  if (((0x27u >> v8) & 1) == 0)
    return -2;
  v10 = dword_3E65C24[v8];
  AddrGuestWork = shpGetAddrGuestWork(v10);
  if (!AddrGuestWork)
    return -2;
  v12 = AddrGuestWork;
  intimacyPoint = v12->intimacyPoint;
  v16 = intimacyPoint[0];
  v17 = shpDatDrinkPoint[v10][a_drinkId];
  v18 = v17[0];
  *(u32 *)(v7 + 32) = v18;
  v19 = (s16)(v16 + v18);
  if (v19 >= 255)
    LOWORD(v19) = 255;
  intimacyPoint[0] = v19;
  intimacyPoint = v12->intimacyPoint;
  v17 = shpDatDrinkPoint[v10][a_drinkId];
  v20 = v17[1];
  *(u32 *)(v7 + 36) = v20;
  LOWORD(v20) = intimacyPoint[1] + v20;
  v21 = (s16)v20;
  intimacyPoint[1] = v20;
  if ((s16)v20 > 255)
  {
    intimacyPoint[1] = 255;
    p_bitDrinkRank = &v12->bitDrinkRank;
    bitDrinkRank = v12->bitDrinkRank;
    if ((bitDrinkRank & 0x200) == 0)
    {
LABEL_20:
      *p_bitDrinkRank = bitDrinkRank | 0x200;
      return 9;
    }
  }
  else
  {
    p_bitDrinkRank = &v12->bitDrinkRank;
    bitDrinkRank = v12->bitDrinkRank;
    if ((bitDrinkRank & 0x200) == 0 && v21 == 255)
      goto LABEL_20;
  }
  v25 = bitDrinkRank;
  if ((bitDrinkRank & 1) == 0)
  {
    v26 = intimacyPoint[0];
    bitDrinkRank = *p_bitDrinkRank;
    if (v26 >= shpDatDrinkRank[v10][0])
    {
      result = 0;
      v35 = 1;
      goto LABEL_78;
    }
    v25 = bitDrinkRank;
  }
  if ((v25 & 2) == 0)
  {
    v27 = v12->intimacyPoint[0];
    bitDrinkRank = *p_bitDrinkRank;
    if (v27 >= shpDatDrinkRank[v10][1])
    {
      v35 = 2;
      result = 1;
      goto LABEL_78;
    }
    v25 = bitDrinkRank;
  }
  if ((v25 & 4) == 0)
  {
    v28 = v12->intimacyPoint[0];
    bitDrinkRank = *p_bitDrinkRank;
    if (v28 >= shpDatDrinkRank[v10][2])
    {
      v35 = 4;
      result = 2;
      goto LABEL_78;
    }
    v25 = bitDrinkRank;
  }
  if ((v25 & 8) == 0)
  {
    v29 = v12->intimacyPoint[0];
    bitDrinkRank = *p_bitDrinkRank;
    if (v29 >= shpDatDrinkRank[v10][3])
    {
      v35 = 8;
      result = 3;
      goto LABEL_78;
    }
    v25 = bitDrinkRank;
  }
  if ((v25 & 0x10) == 0)
  {
    v30 = v12->intimacyPoint[0];
    bitDrinkRank = *p_bitDrinkRank;
    if (v30 >= shpDatDrinkRank[v10][4])
    {
      v35 = 16;
      result = 4;
      goto LABEL_78;
    }
    v25 = bitDrinkRank;
  }
  if ((v25 & 0x20) == 0)
  {
    v31 = v12->intimacyPoint[0];
    bitDrinkRank = *p_bitDrinkRank;
    if (v31 >= shpDatDrinkRank[v10][5])
    {
      v35 = 32;
      result = 5;
      goto LABEL_78;
    }
    v25 = bitDrinkRank;
  }
  if ((v25 & 0x40) == 0)
  {
    v32 = v12->intimacyPoint[0];
    bitDrinkRank = *p_bitDrinkRank;
    if (v32 >= shpDatDrinkRank[v10][6])
    {
      v35 = 64;
      result = 6;
      goto LABEL_78;
    }
    v25 = bitDrinkRank;
  }
  if ((v25 & 0x80) == 0)
  {
    v33 = v12->intimacyPoint[0];
    bitDrinkRank = *p_bitDrinkRank;
    if (v33 >= shpDatDrinkRank[v10][7])
    {
      v35 = 128;
      result = 7;
      goto LABEL_78;
    }
    v25 = bitDrinkRank;
  }
  if ((v25 & 0x100) != 0)
    return -1;
  v34 = v12->intimacyPoint[0];
  if (v34 < shpDatDrinkRank[v10][8])
    return -1;
  bitDrinkRank = *p_bitDrinkRank;
  v35 = 256;
  result = 8;
LABEL_78:
  *p_bitDrinkRank = bitDrinkRank | v35;
  return result;
}
