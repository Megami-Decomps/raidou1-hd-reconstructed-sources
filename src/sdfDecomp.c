#include "types.h"
#include "sdfdecomp.h"

#define SDF_DECOMP_DIRECTIVE_NORMAL 0
#define SDF_DECOMP_DIRECTIVE_ZERO 32
#define SDF_DECOMP_DIRECTIVE_RLE 64
#define SDF_DECOMP_DIRECTIVE_SD 96
#define SDF_DECOMP_DIRECTIVE_SD2 128
#define SDF_DECOMP_DIRECTIVE_WORD 160
#define SDF_DECOMP_DIRECTIVE_CMD 224
#define SDF_DECOMP_DIRECTIVE_MASK 224
#define SDF_DECOMP_DIRECTIVE_LENG_MASK 31
#define SDF_DECOMP_CMD_END 255

typedef struct sdfBinary sdfBinary;

// 0x225cc10
bool sdfExec(u8 *dst_p, sdfBinary *src_p) {
  s32 v6;
  u32 U8;
  u32 U16;
  u32 v9;
  s32 v10;
  s32 v11;
  s32 v12;
  s32 v13;
  s32 v14;
  s32 v15;
  u8 v16;
  s32 v17;
  s32 v18;
  s32 v19;
  u16 v20;
  s32 v21;
  s32 v22;
  s32 v23;
  s32 v24;
  u8 v25;
  char *v26;
  u32 v27;
  s32 v28;
  s32 v29;
  s32 v30;
  s32 v31;
  s32 v32;
  s32 v33;
  u8 v34;
  s32 v35;
  s32 v36;
  u8 v37;
  u8 v38;
  s32 v39;
  s32 v40;
  u8 v41;
  s32 v42;
  s32 v43;
  s32 v44;
  s32 v45;
  s32 v46;
  s32 v47;
  s32 v48;
  _OWORD *v49;
  u32 v50;
  s32 v51;
  char *v52;
  int8x16_t v53;
  s32 v54;
  s32 v55;
  int8x16_t *v56;
  int8x8_t v57;
  u32 v58;
  s32 v59;
  int8x8_t *v60;
  s32 v61;
  s32 v62;
  u8 *v63;
  u8 *v64;
  __int128 v65;
  __int128 v66;
  __int128 v67;
  u32 v68;
  s32 v69;
  s32 v70;
  s32 v71;
  u8 *v72;
  u8 *v73;
  __int128 v74;
  __int128 v75;
  __int128 v76;
  u32 v77;
  s32 v78;

  if (IsOver_36177024(src_p, 0))
    return 0;
  v6 = 0;
  while (1)
  {
    U8 = ReadU8(src_p, 0);
    if (U8 >= 0xE0)
      break;
    U16 = U8 & 0x1F;
    if ((U8 & 0x1F) != 0)
    {
      v9 = U8 & 0xE0;
      if (v9 <= 0x40)
        goto LABEL_16;
    }
    else
    {
      U16 = ReadU16(src_p, 0);
      v9 = U8 & 0xE0;
      if (v9 <= 0x40)
      {
LABEL_16:
        if (!v9)
        {
          if (U16)
          {
            v24 = v6 + U16;
            do
            {
              v25 = ReadU8(src_p, 0);
              v26 = (char *)dst_p + v6;
              --U16;
              ++v6;
              v26[32] = v25;
            }
            while (U16);
            v6 = v24;
          }
          goto LABEL_5;
        }
        if (v9 != 64)
        {
          if (v9 != 32 || !U16)
            goto LABEL_5;
          v11 = v6 + U16;
          if (U16 < 8 || (s32)(U16 + v6 - 1) < v6)
          {
            v12 = v6;
            goto LABEL_23;
          }
          if (U16 >= 0x40)
          {
            v45 = U16 & 0xFFC0;
            v47 = v6;
            v48 = v45;
            do
            {
              v49 = ((char *)dst_p + v47);
              v48 -= 64;
              v47 += 64;
              v49[2] = 0u;
              v49[3] = 0u;
              v49[4] = 0u;
              v49[5] = 0u;
            }
            while (v48);
            if (U16 == v45)
              goto LABEL_72;
            if ((U16 & 0x38) != 0)
              goto LABEL_81;
            v12 = v6 + v45;
          }
          else
          {
            v45 = 0;
LABEL_81:
            v12 = v6 + (U16 & 0xFFF8);
            v50 = v45 - (U16 & 0xFFF8);
            v51 = v6 + v45;
            do
            {
              v52 = (char *)dst_p + v51;
              v50 += 8;
              v51 += 8;
              *((u64 *)v52 + 4) = 0;
            }
            while (v50);
            if (U16 == (U16 & 0xFFF8))
              goto LABEL_72;
          }
LABEL_23:
          v13 = v11 - v12;
          v14 = (v11 - v12) & 3;
          if (v14)
          {
            do
            {
              v15 = v12 + 1;
              --v14;
              dst_p[v12++] = 0;
            }
            while (v14);
            if ((u32)(v13 - 1) < 3)
              goto LABEL_72;
          }
          else
          {
            v15 = v12;
            if ((u32)(v13 - 1) < 3)
              goto LABEL_72;
          }
          do
          {
            dst_p[v15] = 0;
            *(u16 *)&dst_p[v15 + 1] = 0;
            v44 = v15 + 3;
            v15 += 4;
            dst_p[v44] = 0;
          }
          while (v11 != v15);
          goto LABEL_72;
        }
        v27 = ReadU8(src_p, 0);
        if (U16)
        {
          v11 = v6 + U16;
          if (U16 < 8 || (s32)(U16 + v6 - 1) < v6)
          {
            v28 = v6;
            goto LABEL_47;
          }
          if (U16 >= 0x40)
          {
            v53 = vdupq_n_s8(v27);
            v46 = U16 & 0xFFC0;
            v54 = v6;
            v55 = v46;
            do
            {
              v56 = ((char *)dst_p + v54);
              v55 -= 64;
              v54 += 64;
              v56[2] = v53;
              v56[3] = v53;
              v56[4] = v53;
              v56[5] = v53;
            }
            while (v55);
            if (U16 == v46)
              goto LABEL_72;
            if ((U16 & 0x38) != 0)
              goto LABEL_89;
            v28 = v6 + v46;
          }
          else
          {
            v46 = 0;
LABEL_89:
            v57.n64_u64[0] = vdup_n_s8(v27).n64_u64[0];
            v28 = v6 + (U16 & 0xFFF8);
            v58 = v46 - (U16 & 0xFFF8);
            v59 = v6 + v46;
            do
            {
              v60 = ((char *)dst_p + v59);
              v58 += 8;
              v59 += 8;
              v60[4].n64_u64[0] = v57.n64_u64[0];
            }
            while (v58);
            if (U16 == (U16 & 0xFFF8))
              goto LABEL_72;
          }
LABEL_47:
          v29 = v11 - v28;
          v30 = (v11 - v28) & 3;
          if (v30)
          {
            do
            {
              v31 = v28 + 1;
              --v30;
              dst_p[v28++] = v27;
            }
            while (v30);
            if ((u32)(v29 - 1) < 3)
              goto LABEL_72;
          }
          else
          {
            v31 = v28;
            if ((u32)(v29 - 1) < 3)
              goto LABEL_72;
          }
          do
          {
            v42 = v31 + 2;
            dst_p[v31] = v27;
            dst_p[v31 + 1] = v27;
            v43 = v31 + 3;
            v31 += 4;
            dst_p[v42] = v27;
            dst_p[v43] = v27;
          }
          while (v11 != v31);
          goto LABEL_72;
        }
        goto LABEL_5;
      }
    }
    if (v9 == 96)
    {
      v16 = ReadU8(src_p, 0);
      if (U16)
      {
        v11 = v6 + U16;
        v17 = v6 - v16;
        if (U16 < 8 || (s32)(v6 + U16 - 1) < v6 || (s32)(v17 + U16 - 1) < v17 || (u64)(v6 - (s64)v17) < 0x40)
        {
          v18 = v6;
        }
        else if (U16 >= 0x40)
        {
          v32 = U16 & 0xFFC0;
          v61 = v6;
          v62 = v32;
          do
          {
            v63 = &dst_p[v61 - v16];
            v64 = &dst_p[v61];
            v62 -= 64;
            v61 += 64;
            v65 = *((_OWORD *)v63 + 1);
            v66 = *((_OWORD *)v63 + 2);
            v67 = *((_OWORD *)v63 + 3);
            *(_OWORD *)v64 = *(_OWORD *)v63;
            *((_OWORD *)v64 + 1) = v65;
            *((_OWORD *)v64 + 2) = v66;
            *((_OWORD *)v64 + 3) = v67;
          }
          while (v62);
          if (U16 == v32)
            goto LABEL_72;
          if ((U16 & 0x38) != 0)
            goto LABEL_97;
          v17 += v32;
          v18 = v6 + v32;
        }
        else
        {
          v32 = 0;
LABEL_97:
          v18 = v6 + (U16 & 0xFFF8);
          v17 += U16 & 0xFFF8;
          v68 = v32 - (U16 & 0xFFF8);
          v69 = v6 + v32;
          do
          {
            v68 += 8;
            *(u64 *)&dst_p[v69] = *(u64 *)&dst_p[v69 - v16];
            v69 += 8;
          }
          while (v68);
          if (U16 == (U16 & 0xFFF8))
            goto LABEL_72;
        }
        if (((v11 - v18) & 1) != 0)
        {
          v19 = v18 + 1;
          v34 = dst_p[v17++];
          dst_p[v18] = v34;
          if (v11 - 1 == v18)
            goto LABEL_72;
        }
        else
        {
          v19 = v18;
          if (v11 - 1 == v18)
            goto LABEL_72;
        }
        do
        {
          v35 = v17 + 1;
          v36 = v19 + 1;
          v37 = dst_p[v17];
          v17 += 2;
          dst_p[v19] = v37;
          v19 += 2;
          dst_p[v36] = dst_p[v35];
        }
        while (v11 != v19);
        goto LABEL_72;
      }
    }
    else
    {
      if (v9 != 128)
      {
        if (v9 == 160 && U16)
        {
          do
          {
            v10 = v6 + 1;
            --U16;
            dst_p[v6] = ReadU8(src_p, 0);
            v6 += 2;
            dst_p[v10] = 0;
          }
          while (U16);
        }
        goto LABEL_5;
      }
      v20 = ReadU16(src_p, 0);
      if (U16)
      {
        v11 = v6 + U16;
        v21 = v6 - v20;
        if (U16 < 8 || (s32)(v6 + U16 - 1) < v6 || (s32)(v21 + U16 - 1) < v21 || (u64)(v6 - (s64)v21) < 0x40)
        {
          v22 = v6;
        }
        else if (U16 >= 0x40)
        {
          v33 = U16 & 0xFFC0;
          v70 = v6;
          v71 = v33;
          do
          {
            v72 = &dst_p[v70 - v20];
            v73 = &dst_p[v70];
            v71 -= 64;
            v70 += 64;
            v74 = *((_OWORD *)v72 + 1);
            v75 = *((_OWORD *)v72 + 2);
            v76 = *((_OWORD *)v72 + 3);
            *(_OWORD *)v73 = *(_OWORD *)v72;
            *((_OWORD *)v73 + 1) = v74;
            *((_OWORD *)v73 + 2) = v75;
            *((_OWORD *)v73 + 3) = v76;
          }
          while (v71);
          if (U16 == v33)
            goto LABEL_72;
          if ((U16 & 0x38) != 0)
            goto LABEL_105;
          v21 += v33;
          v22 = v6 + v33;
        }
        else
        {
          v33 = 0;
LABEL_105:
          v22 = v6 + (U16 & 0xFFF8);
          v21 += U16 & 0xFFF8;
          v77 = v33 - (U16 & 0xFFF8);
          v78 = v6 + v33;
          do
          {
            v77 += 8;
            *(u64 *)&dst_p[v78] = *(u64 *)&dst_p[v78 - v20];
            v78 += 8;
          }
          while (v77);
          if (U16 == (U16 & 0xFFF8))
          {
LABEL_72:
            v6 = v11;
            goto LABEL_5;
          }
        }
        if (((v11 - v22) & 1) != 0)
        {
          v23 = v22 + 1;
          v38 = dst_p[v21++];
          dst_p[v22] = v38;
          if (v11 - 1 == v22)
            goto LABEL_72;
        }
        else
        {
          v23 = v22;
          if (v11 - 1 == v22)
            goto LABEL_72;
        }
        do
        {
          v39 = v21 + 1;
          v40 = v23 + 1;
          v41 = dst_p[v21];
          v21 += 2;
          dst_p[v23] = v41;
          v23 += 2;
          dst_p[v40] = dst_p[v39];
        }
        while (v11 != v23);
        goto LABEL_72;
      }
    }
LABEL_5:
    if (IsOver_36177024(src_p, 0))
      return 0;
  }
  if (U8 != 255)
    goto LABEL_5;
  return 1;
}
