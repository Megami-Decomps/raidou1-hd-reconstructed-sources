#include "types.h"
#include "SKLID.h"
#include "cmpraidouskill.h"
#include "dat.h"
#include "evtbit.h"
#include "libsdf.h"
#include "mdl.h"
#include "sbtl.h"
#include "sbtlcalc.h"
#include "sbtldmg.h"
#include "sbtlplayertbl.h"
#include "sbtlskill.h"

typedef struct HITSTOP_TABLE_t HITSTOP_TABLE_t;
typedef struct MOTIONMOVE_WORK MOTIONMOVE_WORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct VISUALDATA_WORK VISUALDATA_WORK;
typedef struct sbtlplayertbl_HDEFF_TABLE_t sbtlplayertbl_HDEFF_TABLE_t;

VISUALDATA_WORK *sbtlvisual_tbldata_player[5];
MOTIONMOVE_WORK *sbtlmotionmove_tbldata_player;
sbtlplayertbl_HDEFF_TABLE_t *gHDEffTable;
HITSTOP_TABLE_t *gHitStopTable;

// 0x20d0cc0
s32 sbtlplayertblGetHDEffTable_SKLID(SKLID _SkillId, s32 _SkillNum) {
  s64 v6;
  s32 v7;
  sbtlplayertbl_HDEFF_TABLE_t *v9;

  v6 = 0;
  v7 = -1;
  while (1)
  {
    if (v6 >= SLODWORD(gHDEffTable->max_length))
      return v7;
    v9 = gHDEffTable[v6];
    if (v9->SkillId == SkillId)
    {
      if (v9->SkillNum == SkillNum)
        return v6;
    }
    ++v6;
  }
}

// 0x20d0db0
sbtlplayertbl_HDEFF_TABLE_t *sbtlplayertblGetHDEffTable_Idx(s32 _TblIdx) {
  return gHDEffTable[TblIdx];
}

// 0x20d0e20
s32 sbtlplayertblGetHitStopTableIdx_SKLID(SKLID _SkillId) {
  s64 v4;
  s32 v5;

  v4 = 0;
  v5 = -1;
  while (1)
  {
    if (v4 >= SLODWORD(gHitStopTable->max_length))
      return v5;
    if (gHitStopTable[v4]->SkillId == SkillId)
      return v4;
    ++v4;
  }
}

// 0x20d0ee0
HITSTOP_TABLE_t *sbtlplayertblGetHitStopTable_Idx(s32 _TblIdx) {
  return gHitStopTable[TblIdx];
}

// 0x20d0f50
HITSTOP_TABLE_t *sbtlplayertblGetHitStopTable_SKLID(SKLID _SkillId) {
  s64 v4;
  Il2CppClass **v5;
  HITSTOP_TABLE_t *v6;
  HITSTOP_TABLE_t *gHitStopTable_local;

  v4 = 0;
  while (1)
  {
    gHitStopTable_local = gHitStopTable;
    if (v4 >= SLODWORD(gHitStopTable_local->max_length))
      break;
    gHitStopTable_local = gHitStopTable;
    v5 = &gHitStopTable_local->obj.klass + v4++;
    v6 = (HITSTOP_TABLE_t *)v5[4];
    if (v6->SkillId == SkillId)
      return v6;
  }
  return 0;
}

// 0x20d1010
void sbtlplayertblSetPlayerMotionData_Hokan(SBTLUNIT_WORK *wk) {
  u64 v3;
  s32 next_motionno;
  s16 v6;
  bool v7;
  s32 v8;
  SBATTLE_WORK *v10;
  s32 motionno;
  s32 v12;
  u32 v13;
  bool v14;
  s16 v15;
  s32 v16;
  s32 v17;
  s16 v18;
  s32 v19;
  s16 v20;
  s32 v21;
  s32 v22;
  bool v23;
  bool v24;
  s32 v25;
  s32 v26;
  s32 v27;
  s32 v29;
  s32 v30;
  u32 v31;
  u32 v32;
  dds3ModelHandle_t *hModel;
  f32 MotionFrameF;
  u32 v35;
  char v36;
  u64 v37;
  s32 v38;
  s32 v39;
  bool v40;
  s32 v41;
  s16 v43;
  s32 v44;
  u32 v45;
  s32 v46;
  u32 v48;
  u32 v49;

  if (wk->next_motion_not_hokan)
    goto LABEL_4;
  next_motionno = wk->next_motionno;
  wk->beforeframe = 4;
  LOWORD(v3) = 0;
  switch (next_motionno)
  {
    case 0:
    case 130:
      v10 = wk;
      if (v10->battlemode == 1)
        goto LABEL_224;
      motionno = wk->motionno;
      if (motionno > 85)
      {
        if ((u32)motionno <= 0x84)
        {
          LOWORD(v3) = 8;
          switch (motionno)
          {
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
              LOWORD(v3) = 4;
              goto LABEL_6;
            case 'f':
            case 'h':
            case 'k':
            case 'l':
            case 'm':
              return;
            case 'g':
            case 'i':
            case 'j':
              goto LABEL_6;
            case 'n':
              goto LABEL_4;
            default:
              if ((motionno & 0xFFFFFFFE) == 0x7E)
                goto LABEL_4;
              if (motionno == 132)
                goto LABEL_182;
              return;
          }
        }
        LOWORD(v3) = 8;
        switch (motionno)
        {
          case 135:
            goto LABEL_4;
          case 162:
          case 164:
            goto LABEL_6;
          case 168:
          case 169:
          case 170:
          case 171:
          case 177:
            goto LABEL_222;
          case 174:
            goto LABEL_237;
          default:
            return;
        }
        return;
      }
      if (motionno > 15)
      {
        LOWORD(v3) = 4;
        switch (motionno)
        {
          case 16:
            v10 = wk;
            if (v10->cmbSkl->bRun)
              goto LABEL_4;
            break;
          case 39:
          case 41:
          case 42:
          case 49:
          case 50:
          case 51:
            goto LABEL_4;
          case 40:
          case 45:
          case 46:
          case 47:
          case 48:
            return;
          case 43:
            goto LABEL_6;
          case 44:
            goto LABEL_224;
          default:
            if ((u32)(motionno - 83) < 3)
              goto LABEL_4;
            break;
        }
        return;
      }
      if (motionno == 1)
        goto LABEL_182;
      if (motionno == 11)
        goto LABEL_222;
      if (motionno != 15)
        return;
      goto LABEL_217;
    case 1:
      if (wk->battlemode == 1)
        goto LABEL_222;
      LODWORD(v3) = wk->motionno;
      if ((s32)v3 <= 16)
        goto LABEL_180;
      if ((u32)v3 <= 0x6D)
      {
        if ((u32)(v3 - 45) > 0xFFFFFFFD)
          goto LABEL_182;
        if ((u32)(v3 - 107) < 3)
          goto LABEL_4;
      }
      else
      {
        if ((u32)(v3 - 131) > 0xFFFFFFFC)
          goto LABEL_182;
        if ((u32)v3 == 135)
          goto LABEL_4;
      }
      return;
    case 2:
      LODWORD(v3) = wk->motionno;
      if ((s32)v3 > 15)
      {
        v29 = v3 - 39;
        LOWORD(v3) = 0;
        switch (v29)
        {
          case 0:
          case 2:
          case 3:
          case 71:
            goto LABEL_6;
          case 58:
          case 59:
          case 60:
          case 61:
          case 62:
            return;
          case 64:
          case 66:
          case 67:
            goto LABEL_182;
          default:
            goto LABEL_4;
        }
        return;
      }
      if ((u32)v3 == 1)
        goto LABEL_182;
      if ((u32)v3 == 11)
        goto LABEL_222;
      if ((u32)v3 != 15)
        goto LABEL_4;
LABEL_217:
      LOWORD(v3) = 10;
      goto LABEL_6;
    case 4:
    case 5:
    case 13:
    case 16:
    case 25:
    case 34:
    case 39:
    case 40:
    case 41:
    case 42:
    case 46:
    case 49:
    case 50:
    case 51:
    case 52:
    case 57:
    case 58:
    case 59:
    case 60:
    case 74:
    case 75:
    case 76:
    case 77:
    case 83:
    case 84:
    case 85:
    case 87:
    case 88:
    case 89:
    case 90:
    case 91:
    case 92:
    case 93:
    case 96:
    case 112:
    case 115:
    case 118:
    case 124:
    case 125:
    case 126:
    case 127:
    case 131:
    case 132:
    case 135:
    case 136:
    case 137:
    case 139:
    case 140:
    case 145:
    case 146:
    case 147:
    case 150:
    case 151:
    case 152:
    case 155:
    case 156:
    case 157:
    case 158:
    case 161:
    case 162:
    case 164:
    case 165:
    case 166:
    case 168:
    case 169:
    case 170:
    case 171:
    case 172:
    case 173:
    case 174:
    case 175:
    case 176:
    case 177:
    case 178:
    case 179:
    case 180:
    case 181:
    case 182:
    case 183:
      goto LABEL_6;
    case 7:
    case 17:
    case 38:
      if (wk->cmbSkl->bRun)
        goto LABEL_4;
      return;
    case 11:
      v16 = wk->motionno;
      if (v16 <= 7)
        goto LABEL_114;
      if ((u32)v16 > 0x6F)
        goto LABEL_109;
      if ((u32)(v16 - 17) > 0xFFFFFFFD)
        goto LABEL_224;
      if (v16 != 111)
        goto LABEL_222;
      goto LABEL_4;
    case 20:
      v14 = wk->motionno == 41;
      goto LABEL_42;
    case 21:
    case 153:
      goto LABEL_222;
    case 23:
      v30 = wk->motionno;
      if (v30 > 24)
      {
        v31 = v30 - 103;
        if (v31 > 0x1B || ((1 << v31) & 0x800000D) == 0)
        {
          LOWORD(v3) = 5;
          goto LABEL_6;
        }
        goto LABEL_224;
      }
      if ((u32)v30 < 3)
        goto LABEL_224;
      if (v30 == 24)
        v43 = 8;
      else
        v43 = 5;
      if (v30 == 23)
        LOWORD(v3) = 0;
      else
        LOWORD(v3) = v43;
      goto LABEL_6;
    case 43:
      v16 = wk->motionno;
      if (v16 <= 7)
        goto LABEL_114;
      if ((u32)v16 > 0x72)
        goto LABEL_109;
      if ((u32)(v16 - 17) > 0xFFFFFFFD)
        goto LABEL_224;
      if (v16 != 114)
        goto LABEL_222;
      goto LABEL_4;
    case 44:
      v16 = wk->motionno;
      if (v16 <= 7)
      {
LABEL_114:
        LOWORD(v3) = 1;
        if (!v16 || v16 == 2)
          goto LABEL_6;
        if (v16 == 7)
          goto LABEL_224;
        goto LABEL_222;
      }
      if ((u32)v16 > 0x75)
      {
LABEL_109:
        if (v16 == 132)
          LOWORD(v3) = 3;
        else
          LOWORD(v3) = 2;
        if (v16 == 130)
          LOWORD(v3) = 1;
        goto LABEL_6;
      }
      if ((u32)(v16 - 17) > 0xFFFFFFFD)
        goto LABEL_224;
      if (v16 != 117)
        goto LABEL_222;
      goto LABEL_4;
    case 45:
    case 56:
    case 98:
    case 99:
    case 100:
    case 101:
    case 102:
      goto LABEL_237;
    case 54:
      if (wk->motionno == 55)
        goto LABEL_4;
      return;
    case 55:
      LOWORD(v3) = wk->motionno == 54;
      goto LABEL_6;
    case 94:
      v17 = wk->motionno;
      if (v17 <= 94)
      {
        if ((u32)v17 < 3)
        {
          v36 = 16 * v17;
          v37 = 0x100000001LL;
          goto LABEL_234;
        }
        if ((u32)(v17 - 43) <= 0xFFFFFFFD)
        {
          v14 = v17 == 94;
          goto LABEL_42;
        }
        goto LABEL_4;
      }
      if ((u32)v17 > 0x6A)
      {
        if (v17 == 130)
          v18 = 1;
        else
          v18 = 2;
        if (v17 == 128)
          LOWORD(v3) = 0;
        else
          LOWORD(v3) = v18;
        goto LABEL_6;
      }
      v45 = v17 - 103;
      if (v45 >= 4)
        goto LABEL_222;
      v36 = 16 * v45;
      v37 = 0x20000;
      goto LABEL_234;
    case 95:
      v19 = wk->motionno;
      if (v19 <= 94)
      {
        v7 = v19 == 0;
        v6 = 2 * (v19 != 94);
        goto LABEL_170;
      }
      if (v19 == 130)
        v20 = 3;
      else
        v20 = 2;
      if (v19 == 96)
        LOWORD(v3) = 0;
      else
        LOWORD(v3) = v20;
      goto LABEL_6;
    case 97:
      LOWORD(v3) = wk->motionno != 42;
      goto LABEL_6;
    case 103:
      LODWORD(v3) = wk->motionno;
      if ((s32)v3 > 109)
      {
        if ((u32)v3 > 0x96)
          goto LABEL_10;
        v21 = v3 - 128;
        LOWORD(v3) = 8;
        switch (v21)
        {
          case 0:
          case 1:
          case 2:
          case 3:
            goto LABEL_6;
          case 5:
          case 6:
          case 7:
            goto LABEL_4;
          case 18:
            goto LABEL_222;
          case 22:
            goto LABEL_237;
          default:
            return;
        }
        return;
      }
      if ((s32)v3 <= 16)
        goto LABEL_180;
      if ((u32)v3 == 39)
        goto LABEL_4;
      if ((u32)(v3 - 45) > 0xFFFFFFFD)
        goto LABEL_182;
      if ((u32)(v3 - 107) < 3 || (u32)(v3 - 105) < 2)
        goto LABEL_4;
      if ((u32)v3 != 88)
        return;
      goto LABEL_224;
    case 104:
      LOWORD(v3) = 2;
      v32 = wk->motionno - 103;
      if (v32 > 0x20 || ((1 << v32) & 0x1C000000DLL) == 0)
        goto LABEL_6;
      wk->beforeframe = 0;
      hModel = wk->hModel;
      MotionFrameF = mdlGetMotionFrameF(hModel);
      LODWORD(v3) = (s32)MotionFrameF;
      if (MotionFrameF == INFINITY)
        LODWORD(v3) = 0x80000000;
      if ((u32)v3 >= 0x25)
        return;
      LOWORD(v3) = word_3E650B8[(s32)v3];
      goto LABEL_6;
    case 105:
    case 106:
    case 133:
    case 134:
      LODWORD(v3) = wk->motionno;
      if ((s32)v3 <= 109)
      {
        if ((s32)v3 <= 16)
        {
LABEL_180:
          if ((u32)v3 <= 0xB)
          {
            if (((1 << v3) & 0x835) != 0)
              goto LABEL_182;
            if (((1 << v3) & 0xA) != 0)
              return;
          }
          if ((u32)(v3 - 15) >= 2)
            return;
        }
        else
        {
          if ((u32)v3 == 39)
            goto LABEL_4;
          if ((u32)(v3 - 45) <= 0xFFFFFFFD)
          {
            v13 = v3 - 88;
            if (v13 > 0x15)
              return;
            if (((1 << v13) & 0x68000) == 0 && ((1 << v13) & 0x380000) == 0)
            {
              if (v13)
                return;
LABEL_224:
              LOWORD(v3) = 3;
              goto LABEL_6;
            }
LABEL_4:
            LOWORD(v3) = 0;
LABEL_6:
            wk->beforeframe = v3;
            return;
          }
        }
LABEL_182:
        LOWORD(v3) = 8;
        goto LABEL_6;
      }
      if ((u32)v3 <= 0x96)
      {
        v26 = v3 - 120;
        LOWORD(v3) = 8;
        switch (v26)
        {
          case 0:
          case 2:
          case 30:
            goto LABEL_237;
          case 8:
          case 9:
          case 10:
          case 11:
            goto LABEL_6;
          case 13:
          case 14:
          case 15:
            goto LABEL_4;
          case 26:
            goto LABEL_222;
          default:
            return;
        }
      }
      else
      {
LABEL_10:
        LODWORD(v3) = v3 - 161;
        if ((u32)v3 < 0x11 && ((0x12791u >> v3) & 1) != 0)
        {
          LOWORD(v3) = word_3E65094[(s32)v3];
          goto LABEL_6;
        }
      }
      return;
    case 107:
    case 109:
      LODWORD(v3) = wk->motionno;
      if ((s32)v3 > 106)
      {
        if ((u32)v3 > 0x96)
          goto LABEL_135;
        v12 = v3 - 128;
        LOWORD(v3) = 3;
        switch (v12)
        {
          case 0:
          case 1:
          case 18:
            goto LABEL_222;
          case 5:
          case 6:
            goto LABEL_6;
          case 8:
            return;
          case 22:
            goto LABEL_237;
          default:
            goto LABEL_4;
        }
        return;
      }
      if ((s32)v3 > 5)
      {
        v27 = v3 - 15;
        LOWORD(v3) = 3;
        switch (v27)
        {
          case 0:
          case 73:
          case 82:
          case 83:
          case 84:
          case 85:
          case 86:
          case 87:
          case 89:
            goto LABEL_222;
          case 25:
            return;
          case 90:
          case 91:
            goto LABEL_6;
          default:
            goto LABEL_4;
        }
        return;
      }
      if ((u32)v3 != 2 && (v3 & 0xFFFFFFFE) != 4)
        goto LABEL_4;
      goto LABEL_222;
    case 108:
      LODWORD(v3) = wk->motionno;
      if ((s32)v3 <= 106)
      {
        if ((s32)v3 <= 5)
        {
          v48 = v3 - 2;
          if (v48 >= 4)
            goto LABEL_4;
          v36 = 16 * v48;
          v37 = 0x2000200000002LL;
LABEL_234:
          v3 = v37 >> v36;
        }
        else
        {
          v44 = v3 - 15;
          LOWORD(v3) = 2;
          switch (v44)
          {
            case 0:
            case 73:
            case 82:
            case 83:
            case 84:
            case 85:
            case 86:
            case 87:
            case 88:
            case 89:
              goto LABEL_6;
            case 25:
              LOWORD(v3) = 6;
              break;
            case 90:
            case 91:
              goto LABEL_224;
            default:
              goto LABEL_4;
          }
        }
      }
      else
      {
        if ((u32)v3 <= 0x96)
        {
          v46 = v3 - 128;
          LOWORD(v3) = 2;
          switch (v46)
          {
            case 0:
            case 1:
            case 18:
              goto LABEL_6;
            case 5:
            case 6:
              goto LABEL_224;
            case 8:
              return;
            case 22:
              goto LABEL_237;
            default:
              goto LABEL_4;
          }
          return;
        }
LABEL_135:
        LODWORD(v3) = v3 - 161;
        if ((u32)v3 >= 0x11)
          goto LABEL_4;
        LOWORD(v3) = word_3E65104[(s32)v3];
      }
      goto LABEL_6;
    case 110:
      v35 = wk->motionno - 107;
      if (v35 >= 3)
        return;
      v36 = 16 * v35;
      v37 = 1;
      goto LABEL_234;
    case 111:
    case 114:
    case 117:
      LODWORD(v3) = wk->motionno;
      if ((s32)v3 <= 5)
      {
        LOWORD(v3) = (v3 & 0xFFFFFFFE) == 4;
      }
      else
      {
        v6 = (u32)v3 == 131;
        v7 = (u32)v3 == 96;
LABEL_170:
        if (v7)
          LOWORD(v3) = 3;
        else
          LOWORD(v3) = v6;
      }
      goto LABEL_6;
    case 120:
      v8 = wk->motionno;
      if (v8 <= 16)
        goto LABEL_78;
      if ((u32)v8 <= 0x2C)
        goto LABEL_94;
      LOWORD(v3) = 1;
      switch (v8)
      {
        case 88:
          goto LABEL_222;
        case 103:
        case 105:
        case 106:
        case 120:
        case 121:
        case 122:
        case 123:
        case 133:
        case 134:
        case 135:
          goto LABEL_4;
        case 107:
        case 108:
        case 109:
        case 128:
        case 129:
        case 130:
        case 131:
          goto LABEL_6;
        default:
          return;
      }
      return;
    case 121:
    case 122:
    case 123:
      v8 = wk->motionno;
      if (v8 <= 16)
      {
LABEL_78:
        if ((u32)v8 <= 0xB)
        {
          LOWORD(v3) = 1;
          if (((1 << v8) & 0x835) != 0)
            goto LABEL_6;
          if (((1 << v8) & 0xA) != 0)
            return;
        }
        if ((u32)(v8 - 15) >= 2)
          return;
      }
      else
      {
        if ((u32)v8 > 0x2C)
        {
          LOWORD(v3) = 1;
          switch (v8)
          {
            case 88:
              goto LABEL_222;
            case 103:
            case 105:
            case 106:
            case 107:
            case 108:
            case 109:
            case 128:
            case 129:
            case 130:
            case 131:
            case 133:
            case 134:
              goto LABEL_6;
            case 120:
            case 121:
            case 122:
            case 123:
            case 135:
              goto LABEL_4;
            default:
              return;
          }
          return;
        }
LABEL_94:
        if (v8 == 39)
          goto LABEL_4;
        if ((u32)(v8 - 43) >= 2)
          return;
      }
      goto LABEL_237;
    case 128:
      v38 = wk->motionno;
      v23 = v38 == 130 || v38 == 0;
      goto LABEL_142;
    case 144:
      v39 = wk->motionno;
      if (v39 <= 94)
      {
        if (v39 <= 42)
        {
          v49 = v39 - 39;
          if (v49 >= 4)
            goto LABEL_237;
          v3 = 0x10000u >> (16 * (u8)v49);
          goto LABEL_6;
        }
        v40 = v39 == 54;
        v41 = 94;
      }
      else if ((u32)v39 <= 0x87)
      {
        v40 = v39 == 96;
        v41 = 135;
      }
      else
      {
        v40 = v39 == 144;
        v41 = 149;
      }
      LOWORD(v3) = !v40 && v39 != v41;
      goto LABEL_6;
    case 148:
      LOWORD(v3) = 2 * ((u32)(wk->motionno - 54) > 3);
      goto LABEL_6;
    case 149:
      LODWORD(v3) = wk->motionno;
      if ((s32)v3 <= 54)
        goto LABEL_158;
      if ((u32)v3 <= 0x60)
        goto LABEL_189;
      v24 = (u32)v3 == 135;
      v25 = 149;
      goto LABEL_152;
    case 154:
      v22 = wk->motionno;
      if (v22 > 54)
      {
        if ((u32)v22 <= 0x60)
        {
          v14 = ((v22 - 94) & 0xFFFFFFFD) == 0;
LABEL_42:
          v15 = !v14;
          LOWORD(v3) = 2 * v15;
        }
        else
        {
          v23 = v22 == 154 || v22 == 135;
LABEL_142:
          if (v23)
            LOWORD(v3) = 0;
          else
            LOWORD(v3) = 2;
        }
        goto LABEL_6;
      }
      if ((u32)v22 > 0x36 || ((1 << v22) & 0x40068000000000LL) == 0)
      {
LABEL_222:
        LOWORD(v3) = 2;
        goto LABEL_6;
      }
      goto LABEL_4;
    case 160:
      LODWORD(v3) = wk->motionno;
      if ((s32)v3 > 54)
      {
        if ((u32)v3 <= 0x60)
        {
LABEL_189:
          LOWORD(v3) = (((u32)v3 - 94) & 0xFFFFFFFD) != 0;
        }
        else
        {
          v24 = (u32)v3 == 135;
          v25 = 160;
LABEL_152:
          LOWORD(v3) = !v24 && (u32)v3 != v25;
        }
        goto LABEL_6;
      }
LABEL_158:
      if ((u32)v3 > 0x36 || ((1 << v3) & 0x40068000000000LL) == 0)
      {
LABEL_237:
        LOWORD(v3) = 1;
        goto LABEL_6;
      }
      goto LABEL_4;
    case 163:
    case 167:
      LOWORD(v3) = (u32)(wk->motionno - 54) < 4;
      goto LABEL_6;
    default:
      return;
  }
}

// 0x20d1ab0
s32 sbtlplayertblGetSkillATRB(SKLID skillid) {
  SBTLSKILLP_TBL *Skilltbl;
  u32 attr;
  s32 v6;

  Skilltbl = sBtlGetSkilltbl(skillid);
  if ((u32)(skillid - 1472) < 7)
    return 8;
  attr = Skilltbl->attr;
  if ((attr & 1) != 0)
    return 0;
  if ((attr & 0x400) != 0)
  {
    v6 = skillid - 1316;
    if ((u32)(skillid - 1316) < 0x1F)
      return dword_3E65128[v6];
    return 1;
  }
  if ((attr & 2) != 0)
    return 3;
  if ((attr & 4) != 0)
    return 4;
  if ((attr & 8) != 0)
    return 5;
  if ((attr & 0x10) != 0)
    return 6;
  if ((attr & 0x20) != 0)
    return 7;
  return 8;
}

// 0x20d1bf0
bool sbtlplayertblChkPlayerMagSkill(SKLID skillid) {
  return ((u32)(skillid - 1316) < 0x1F) & (0x7FBFFFF3u >> (skillid - 36));
}

// 0x20d1c10
bool sbtlplayertblChkPlayerSordSkill(SKLID skillid) {
  bool result;

  result = 1;
  if (skillid != 144 && skillid != 156)
  {
    switch (skillid)
    {
      case 1280:
      case 1281:
      case 1282:
      case 1299:
      case 1300:
      case 1301:
      case 1302:
      case 1303:
      case 1304:
      case 1305:
      case 1306:
      case 1307:
      case 1308:
      case 1309:
      case 1310:
      case 1311:
      case 1312:
      case 1313:
      case 1314:
      case 1316:
      case 1317:
      case 1318:
      case 1319:
      case 1320:
      case 1321:
      case 1322:
      case 1323:
      case 1324:
      case 1325:
      case 1326:
      case 1327:
      case 1328:
      case 1329:
      case 1330:
      case 1331:
      case 1332:
      case 1333:
      case 1334:
      case 1335:
      case 1336:
      case 1337:
      case 1339:
      case 1340:
      case 1341:
      case 1342:
      case 1343:
      case 1344:
      case 1345:
      case 1346:
        return result;
      default:
        result = 0;
        break;
    }
  }
  return result;
}

// 0x20d1c60
s32 sbtlplayertblPlayerSkill_GetMag(SBTLUNIT_WORK *wkPlayer, SKLID skillid, SBTLUNIT_WORK *wkEnemy) {
  sdatUnitWork_t *para;
  SBTLSKILLP_TBL *Skilltbl;
  s32 v8;

  para = wkEnemy->para;
  sBtlGetBadStatus(para);
  Skilltbl = sBtlGetSkilltbl(skillid);
  v8 = 1;
  if ((u32)(skillid - 1316) <= 0x1E && ((1 << (skillid - 36)) & 0x7FBFFFF3) != 0)
  {
    if (!wk->raido_magwaza_costnot)
    {
      sBtlDeleteShild(wkEnemy, skillid, 100);
    }
    v8 = 0;
  }
  if (((sBtlGetSpiritSkillChk(1445) | v8) & 1) != 0)
    return Skilltbl->light_attack_mag;
  return 0;
}

// 0x20d1de0
void sbtlplayertblPlayerSkill_GetMag2(SBTLUNIT_WORK *wkPlayer, SBTLUNIT_WORK *wkEnemy, s32 _Damage) {
  s32 v8;

  if (30 * Damage >= 100)
    v8 = 30 * Damage / 0x64u;
  else
    v8 = 1;
  wkEnemy->getMag += v8;
  sBtlSetAddMagWeakAttack(wkPlayer, wkEnemy, v8, 0);
}

// 0x20d1e90
void sbtlplayertblPlayerSkill_GetMag3(SBTLUNIT_WORK *wkPlayer, SBTLUNIT_WORK *wkEnemy, s32 _Damage) {
  f32 v8;
  s32 v9;
  s32 v10;

  v8 = (f32)((f32)Damage * 0.2) + 0.99;
  v9 = v8;
  if ((s32)v8 <= 1)
    v9 = 1;
  if (v8 == INFINITY)
    v10 = 1;
  else
    v10 = v9;
  wkEnemy->getMag += v10;
  sBtlSetAddMagWeakAttack(wkPlayer, wkEnemy, v10, 0);
}

// 0x20d1f60
bool sbtlplayertblChkSklNG_MAHUU(SBTLUNIT_WORK *wk, SKLID sklid) {
  bool result;

  if (RaidouSklCheck(sklid))
    return 1;
  if (!!datChkSpiritSkl(sklid))
    return 1;
  if (sklid <= 167)
  {
    result = 0;
    if (sklid != 144 && sklid != 149)
      return (sklid & 0xFFFFFFFC) != 0xA4;
  }
  else
  {
    if ((u32)(sklid - 1296) < 0x2A)
      return 0;
    result = 0;
    if ((u32)(sklid - 1339) >= 8 && sklid != 674)
      return 1;
  }
  return result;
}

// 0x20d20b0
bool sbtlplayertblChkNG_TutoEtc(s32 _Mode, SKLID sklid, SDF_PADMAP key) {
  bool result;
  u32 v7;

  if (wk->ChkNG_TutoEtc_AllOk)
    return 0;
  v7 = key & 0xFFFFFFFE;
  if (key <= 4151)
  {
    if (v7 == 4122)
    {
      return !evtBitCheck(9987);
    }
    else
    {
      if (key != 4151)
        return 0;
      return !evtBitCheck(1934);
    }
  }
  else
  {
    if (v7 == 4152)
      return !evtBitCheck(10002);
    switch (key)
    {
      case 4166:
        if (evtBitCheck(9992))
          return 0;
        result = 1;
        break;
      case 4172:
        return !evtBitCheck(1934);
      case 4173:
        return !evtBitCheck(10002);
      case 4174:
        if (evtBitCheck(682))
          return 0;
        result = 1;
        break;
      case 4175:
        if (evtBitCheck(9991))
          return 0;
        result = 1;
        break;
      case 4176:
        if (evtBitCheck(2606))
          return 0;
        result = 1;
        break;
      case 4177:
        if (sbtlplayertblChk_R2_Up())
          return 0;
        result = 1;
        break;
      case 4178:
        if (evtBitCheck(9988))
          return 0;
        result = 1;
        break;
      case 4179:
        if (sbtlplayertblChk_R2_Dn())
          return 0;
        result = 1;
        break;
      case 4180:
        if (evtBitCheck(9998))
          return 0;
        result = 1;
        break;
      case 4181:
        if (evtBitCheck(9996))
          return 0;
        result = 1;
        break;
      default:
        return 0;
    }
  }
  return result;
}

// 0x20d2380
bool sbtlplayertblChk_R2_Up(void) {
  s32 v1;

  if (evtBitCheck(2103))
    v1 = 241;
  else
    v1 = 9996;
  return evtBitCheck(v1);
}

// 0x20d23b0
bool sbtlplayertblChk_R2_Dn(void) {
  s32 v1;

  if (evtBitCheck(2103))
    v1 = 241;
  else
    v1 = 10005;
  return evtBitCheck(v1);
}

// 0x20d23e0
bool sbtlplayertblCompulsion_TutoEtc(SDF_PADMAP key) {
  bool result;

  if (wk->encountno == 514)
  {
    if (evtBitCheck(688) && !evtBitCheck(689))
    {
      result = 1;
      if ((u32)(key - 4145) > 0x21 || ((1 << ((u8)key - 49)) & 0x200008001LL) == 0)
        return result;
    }
  }
  if (wk->encountno == 23)
  {
    if (evtBitCheck(684) && !evtBitCheck(685))
    {
      result = 1;
      if ((u32)(key - 4120) > 0x3D || ((1 << ((u8)key - 24)) & 0x2000000002000003LL) == 0)
        return result;
    }
  }
  if (wk->encountno != 22)
    return 0;
  if (!evtBitCheck(686))
    return 0;
  if (evtBitCheck(687))
    return 0;
  return key != 4180 && key != 4145;
}
