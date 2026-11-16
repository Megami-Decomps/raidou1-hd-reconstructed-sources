#include "types.h"
#include "SKLID.h"
#include "aw.h"
#include "aw_hits.h"
#include "aw_hitsscore.h"
#include "sbtl.h"
#include "sbtlsub.h"
#include "sbtlunit.h"

#define gDRAW_MAX 5
#define gSCORE_MAX 16

typedef struct AW_WORK_t AW_WORK_t;

static s32 gAW_Idx[16];
static s32 *gScore;
static f32 *gCamLen;
static bool *gScreenIn;
static f32 *gScreenX;
static f32 *gScreenX_Nml;
static s32 gNum;
static s32 *gScreen10_I;
static f32 *gScreen10_Len;
static s32 *gRankSort;
static s32 *gRankSortScore;
static bool gRankSortCalcDone;

// 0x1e3dea0
void AW_HitsInit(void) {
  ;
}

// 0x1e3deb0
s32 AW_HitsAdd(s32 _ListID, SKLID _SkillID, f32 _X, f32 _Y, f32 _Z, f32 _Dir, f32 _Scale) {
  s32 v16;
  AW_Func v17;
  AW_WORK_t *AW;
  SBTLCAMERA_WORK *camera;
  s64 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 v29;
  s64 v31;
  f32 v33;
  f32 v34;
  f32 v35;
  bool v36;
  s32 width;
  f32 v38;
  f32 v39;
  f32 v40;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 Unit_ListID;
  f32 v48;
  u64 v50;
  f32 v51;
  s64 v52;
  char *v54;
  unsigned __int128 v56;

  v16 = -1;
  if (gNum > 15)
    return v16;
  v17 = Allocate(AW_Func);
  _ctor(v17, 0, Method_Project_AW_HitsScore_Calc__, 0);
  v16 = Add(241, 0.0, 0.0, 0.0, 0, v17, 0, 1);
  AW = GetAW(v16);
  AW->Unit_ListID = ListID;
  AW->HDEff_SkillID = SkillID;
  AW->X = X;
  AW->Y = Y;
  AW->Z = Z;
  AW->Dir = Dir;
  AW->Scale = Scale;
  AW->StepIntA = -1;
  AW->StepBoolA = 0;
  camera = wk->scene->camera;
  AW->StepIntA = gNum;
  v25 = gNum;
  gAW_Idx[v25] = v16;
  gScore[v25] = 0;
  v26 = AW->X;
  v27 = AW->Z;
  v28 = camera->camerapos.x;
  v29 = camera->camerapos.z;
  v31 = gNum;
  gCamLen[v31] = sBtlGetLenXZ(v26, v27, v28, v29);
  gScreenIn[gNum] = 0;
  gScreenX[v31] = 0.0;
  gScreenX_Nml[v31] = -9999.0;
  get_width(0);
  get_width(0);
  get_width(0);
  get_width(0);
  v33 = AW->X;
  v34 = AW->Y;
  v35 = AW->Z;
  v56 = 0u;
  v36 = sBtlChangeWorldtoScreenUnity3(v33, v34, v35, &v56);
  width = get_width(0);
  v38 = *(f32 *)&v56;
  v39 = -1.0;
  v40 = (f32)(*(f32 *)&v56 * (f32)(2.0 / (f32)width)) + -1.0;
  if (v40 >= -1.0)
  {
    if (v40 <= 1.0)
      v39 = (f32)(*(f32 *)&v56 * (f32)(2.0 / (f32)width)) + -1.0;
    else
      v39 = 1.0;
    if (!v36)
      goto LABEL_37;
  }
  else if (!v36)
  {
LABEL_37:
    gScreenIn[gNum] = 0;
    v51 = *(f32 *)&v56;
    v52 = (s64)gScreenX + 4 * gNum;
    goto LABEL_40;
  }
  if (*(f32 *)&v56 <= 0.0 || v38 >= (f32)get_width(0))
    goto LABEL_37;
  gScreenIn[gNum] = 1;
  LODWORD(gScreenX[v31]) = v56;
  gScreenX_Nml[v31] = (f32)(v39 + 1.0) * 0.5;
  UnitMng = wk->UnitMng;
  Unit_ListID = AW->Unit_ListID;
  sBtlSearchUnit_ID(UnitMng, Unit_ListID);
  v48 = gScreenX_Nml[v31] * 10.0;
  if (v48 == INFINITY)
    v50 = 0xFFFFFFFF80000000LL;
  else
    v50 = (s32)v48;
  v51 = gCamLen[v31];
  if (gScreen10_Len[v50] <= v51)
    goto LABEL_41;
  v51 = gCamLen[gNum];
  gScreen10_I[v50] = gNum;
  v52 = (s64)gScreen10_Len + 4 * v50;
LABEL_40:
  *(f32 *)(v52 + 32) = v51;
LABEL_41:
  v54 = "AW_HitsScore";
  ++gNum;
  AW->DbgStr = v54;
  return v16;
}

// 0x1e3e3c0
void AW_HitsClrScoreWork(void) {
  s64 v2;
  s64 v4;
  s64 v5;
  s64 v6;
  char *v7;
  char *v8;
  char *v9;
  u32 v13;
  u32 v14;
  u32 v15;
  u32 v16;
  u32 v17;
  u32 v18;
  u32 v19;
  u32 v20;
  u32 v21;
  u32 v26;
  u32 v27;
  u32 v28;
  u32 v29;
  u32 v30;
  u32 v31;
  u32 v32;
  f32 *v33;
  u32 v34;

  v2 = 0;
  do
  {
    v4 = 4 * v2;
    v5 = (s64)gScore + 4 * v2;
    gAW_Idx[v2] = -1;
    *(u32 *)(v5 + 32) = 0;
    v6 = (s64)gCamLen + 4 * v2;
    v7 = (char *)gScreenIn + v2++;
    *(u32 *)(v6 + 32) = 1203982208;
    v7[32] = 0;
    v8 = (char *)gScreenX + v4;
    v9 = (char *)gScreenX_Nml + v4;
    *((u32 *)v8 + 8) = 0;
    *((u32 *)v9 + 8) = -971228160;
  }
  while (v2 != 16);
  gNum = 0;
  gScreen10_I[0] = -1;
  gScreen10_Len[0] = 99999.0;
  gScreen10_I[1] = -1;
  gScreen10_Len[1] = 99999.0;
  if (!v13)
    goto LABEL_57;
  gScreen10_I[2] = -1;
  gScreen10_Len[2] = 99999.0;
  if (!v14)
    goto LABEL_58;
LABEL_14:
  gScreen10_I[3] = -1;
  gScreen10_Len[3] = 99999.0;
  if (!v15)
    goto LABEL_59;
LABEL_15:
  gScreen10_I[4] = -1;
  gScreen10_Len[4] = 99999.0;
  if (!v16)
    goto LABEL_60;
LABEL_16:
  gScreen10_I[5] = -1;
  gScreen10_Len[5] = 99999.0;
  if (!v17)
    goto LABEL_61;
LABEL_17:
  gScreen10_I[6] = -1;
  gScreen10_Len[6] = 99999.0;
  if (!v18)
    goto LABEL_62;
LABEL_18:
  gScreen10_I[7] = -1;
  gScreen10_Len[7] = 99999.0;
  if (!v19)
    goto LABEL_63;
LABEL_19:
  gScreen10_I[8] = -1;
  gScreen10_Len[8] = 99999.0;
  if (!v20)
    goto LABEL_64;
LABEL_20:
  gScreen10_I[9] = -1;
  gScreen10_Len[9] = 99999.0;
  if (v21)
    goto LABEL_22;
  goto LABEL_21;
LABEL_57:
  gScreen10_I[2] = -1;
  gScreen10_Len[2] = 99999.0;
  if (v26)
    goto LABEL_14;
LABEL_58:
  gScreen10_I[3] = -1;
  gScreen10_Len[3] = 99999.0;
  if (v27)
    goto LABEL_15;
LABEL_59:
  gScreen10_I[4] = -1;
  gScreen10_Len[4] = 99999.0;
  if (v28)
    goto LABEL_16;
LABEL_60:
  gScreen10_I[5] = -1;
  gScreen10_Len[5] = 99999.0;
  if (v29)
    goto LABEL_17;
LABEL_61:
  gScreen10_I[6] = -1;
  gScreen10_Len[6] = 99999.0;
  if (v30)
    goto LABEL_18;
LABEL_62:
  gScreen10_I[7] = -1;
  gScreen10_Len[7] = 99999.0;
  if (v31)
    goto LABEL_19;
LABEL_63:
  gScreen10_I[8] = -1;
  gScreen10_Len[8] = 99999.0;
  if (v32)
    goto LABEL_20;
LABEL_64:
  v33 = gScreen10_Len;
  gScreen10_I[9] = -1;
  v33[9] = 99999.0;
  if (!v34)
  {
LABEL_21:
  }
LABEL_22:
  gRankSort[0] = -1;
  gRankSortScore[0] = -99999;
  gRankSort[1] = -1;
  gRankSortScore[1] = -99999;
  gRankSort[2] = -1;
  gRankSortScore[2] = -99999;
  gRankSort[3] = -1;
  gRankSortScore[3] = -99999;
  gRankSort[4] = -1;
  gRankSortScore[4] = -99999;
  gRankSort[5] = -1;
  gRankSortScore[5] = -99999;
  gRankSort[6] = -1;
  gRankSortScore[6] = -99999;
  gRankSort[7] = -1;
  gRankSortScore[7] = -99999;
  gRankSort[8] = -1;
  gRankSortScore[8] = -99999;
  gRankSort[9] = -1;
  gRankSortScore[9] = -99999;
  gRankSort[10] = -1;
  gRankSortScore[10] = -99999;
  gRankSort[11] = -1;
  gRankSortScore[11] = -99999;
  gRankSort[12] = -1;
  gRankSortScore[12] = -99999;
  gRankSort[13] = -1;
  gRankSortScore[13] = -99999;
  gRankSort[14] = -1;
  gRankSortScore[14] = -99999;
  gRankSort[15] = -1;
  gRankSortScore[15] = -99999;
  gRankSortCalcDone = 0;
  return;
}

// 0x1e3e9e0
void AW_HitsAdd_Spirit(s32 _ListID, SKLID _SkillID, f32 _PS2X, f32 _PS2Y, f32 _PS2Z) {
  AW_HitsAdd(ListID, SkillID, PS2X, PS2Y, PS2Z, 0.0, 1.0);
}

// 0x1e3c8d0
void AW_HitsAdd_Go(s32 _ListID, SKLID _SkillID, f32 _X, f32 _Y, f32 _Z, f32 _Dir, f32 _Scale) {
  s64 v14;
  s32 v17;
  AW_WORK_t *AW;

  v14 = 8;
  while (1)
  {
    if (v14 - 8 >= gNum)
      break;
    v17 = *((u32 *)&gAW_Idx->obj.klass + v14);
    if (v17 == -1)
      goto LABEL_4;
    AW = GetAW(v17);
    if (!AW)
      goto LABEL_4;
    if (AW->Unit_ListID == ListID)
    {
      AW->X = X;
      AW->Y = Y;
      AW->Z = Z;
      AW->Dir = Dir;
      AW->Scale = Scale;
      AW->StepBoolA = 1;
      return;
    }
LABEL_4:
    ++v14;
  }
}

// 0x1e3ea80
void AW_HitsCalc(AW_WORK_t *aWork) {
  s32 Step;
  s64 StepIntA;
  SBTLUNIT_LISTWORK *v7;
  s32 playerID;
  SBTLUNIT_WORK *v9;
  SBTLUNIT_WORK *v10;
  s64 v13;
  s32 targetID;
  s64 v15;
  s32 Idx;
  s32 *v20;
  s64 v21;
  f32 v23;
  s32 v25;
  s64 m;
  s64 v27;
  s32 v29;
  AW_WORK_t *v31;
  f32 X;
  f32 Z;
  f32 v34;
  f32 v35;
  f32 LenXZ;
  s32 v37;
  SBTLUNIT_LISTWORK *v39;
  s32 v40;
  f32 v42;
  s32 v43;
  bool v44;
  s64 v45;
  s32 *gRankSort_local;
  s32 *gRankSortScore_local;
  s64 v48;
  s32 *gScore_local;
  s32 v50;
  s64 v52;
  s64 i;
  s64 j;
  s64 v56;
  s32 *v57;
  s32 *v58;
  s64 v59;
  s64 v60;
  s32 v61;
  s32 v62;
  s64 k;
  s32 v65;
  AW_WORK_t *AW;
  s32 Unit_ListID;
  SBTLUNIT_LISTWORK *UnitMng;
  u32 v70;

  Step = aWork->Step;
  switch (Step)
  {
    case 2:
      Idx = aWork->Idx;
      DelAW(Idx, 0);
      return;
    case 1:
      if (!gRankSortCalcDone)
      {
        v45 = 8;
        gRankSortCalcDone = 1;
        while (1)
        {
          if (v45 - 8 >= gNum)
            break;
          gRankSort_local = gRankSort;
          gRankSortScore_local = gRankSortScore;
          v48 = 4 * v45;
          gScore_local = gScore;
          v50 = v45++ - 8;
          *(u32 *)((char *)&gRankSort_local->obj.klass + v48) = v50;
          *(u32 *)((char *)&gRankSortScore_local->obj.klass + v48) = *(u32 *)((char *)&gScore_local->obj.klass + v48);
        }
        v52 = 0;
        for (i = 9; ; ++i)
        {
          if (v52 >= gNum - 1)
            break;
          for (j = i; ; ++j)
          {
            if (gNum <= (s32)j - 8)
              break;
            if (gRankSortScore[v52] < *((u32 *)&gRankSortScore->obj.klass + j))
            {
              v56 = 4 * j;
              v58 = gRankSort;
              v57 = gRankSortScore;
              v59 = (s64)v58 + 4 * v52;
              v60 = (s64)v57 + 4 * v52;
              v61 = *(u32 *)(v59 + 32);
              v62 = *(u32 *)(v60 + 32);
              *(u32 *)(v59 + 32) = *((u32 *)&v58->obj.klass + j);
              *(u32 *)(v60 + 32) = *((u32 *)&v57->obj.klass + j);
              *(u32 *)((char *)&v58->obj.klass + v56) = v61;
              *(u32 *)((char *)&v57->obj.klass + v56) = v62;
            }
          }
          ++v52;
        }
        for (k = 0; ; ++k)
        {
          if (k >= gNum)
            break;
          v65 = gAW_Idx[gRankSort[k]];
          AW = GetAW(v65);
          AW->StepIntA = k;
          Unit_ListID = AW->Unit_ListID;
          UnitMng = wk->UnitMng;
          sBtlSearchUnit_ID(UnitMng, Unit_ListID);
        }
      }
      if (aWork->StepBoolA)
      {
        if (aWork->StepIntA <= 4)
        {
          v39 = wk->UnitMng;
          v40 = aWork->Unit_ListID;
          sBtlSearchUnit_ID(v39, v40);
          Add_Score(aWork->Unit_ListID, aWork->HDEff_SkillID, aWork->X, v42, aWork->Z, aWork->Dir, aWork->Scale);
        }
        aWork->Step = 2;
      }
      v43 = aWork->StepCnt + 1;
      v44 = aWork->StepCnt - 120 < 0;
      aWork->StepCnt = v43;
      if (v44 == __OFSUB__(v43, 121))
      {
        v37 = 2;
LABEL_115:
        aWork->Step = v37;
      }
      return;
    case 0:
      StepIntA = aWork->StepIntA;
      v7 = wk->UnitMng;
      playerID = wk->playerID;
      v9 = sBtlSearchUnit_ID(v7, playerID);
      v10 = sBtlSearchUnit_ID(wk->UnitMng, aWork->Unit_ListID);
      if (gScreenIn[StepIntA])
      {
        gScore[StepIntA] += 5;
      }
      if (v10)
      {
        if ((v10->status & 0x4000000) != 0)
        {
          v13 = (s64)gScore + 4 * StepIntA;
          *(u32 *)(v13 + 32) -= 100;
        }
        targetID = v9->actaiwk->targetID;
        if (targetID != -1 && v10->ListID == targetID)
        {
          v15 = (s64)gScore + 4 * StepIntA;
          *(u32 *)(v15 + 32) += 6;
        }
      }
      if (gScreen10_I[0] != (u32)StepIntA && gScreen10_I[1] != (u32)StepIntA && gScreen10_I[2] != (u32)StepIntA && gScreen10_I[3] != (u32)StepIntA && gScreen10_I[4] != (u32)StepIntA && gScreen10_I[5] != (u32)StepIntA && gScreen10_I[6] != (u32)StepIntA && gScreen10_I[7] != (u32)StepIntA && gScreen10_I[8] != (u32)StepIntA && gScreen10_I[9] != (u32)StepIntA)
      {
        goto LABEL_75;
      }
      goto LABEL_9001;
      if (v20[0] != (u32)StepIntA)
      {
        v20 = gScreen10_I;
        if (v20[1] != (u32)StepIntA)
        {
          v20 = gScreen10_I;
          if (v20[2] != (u32)StepIntA)
          {
            v20 = gScreen10_I;
            if (v20[3] != (u32)StepIntA)
            {
              v20 = gScreen10_I;
              if (v20[4] != (u32)StepIntA)
              {
                v20 = gScreen10_I;
                if (v20[5] != (u32)StepIntA)
                {
                  v20 = gScreen10_I;
                  if (v20[6] != (u32)StepIntA)
                  {
                    v20 = gScreen10_I;
                    if (v20[7] != (u32)StepIntA)
                    {
                      v20 = gScreen10_I;
                      if (v20[8] != (u32)StepIntA)
                      {
                        v20 = gScreen10_I;
                        if (v20[9] != (u32)StepIntA)
                        {
LABEL_75:
                          if (!gScreenIn[StepIntA])
                            goto LABEL_84;
                          v23 = gCamLen[StepIntA];
                          if (v23 >= 800.0)
                          {
                            v23 = gCamLen[StepIntA];
                            if (v23 < 1100.0)
                            {
                              v25 = 3;
                              if (v70)
                                goto LABEL_83;
                              goto LABEL_82;
                            }
                            if (!v70)
                            {
                              v23 = gCamLen[StepIntA];
                            }
                            if (v23 >= 1400.0)
                              goto LABEL_84;
                            v25 = 2;
LABEL_82:
                          }
                          else
                          {
                            v25 = 4;
                          }
LABEL_83:
                          gScore[StepIntA] += v25;
LABEL_84:
                          for (m = 8; ; ++m)
                          {
                            if (m - 8 >= gNum)
                            {
                              v37 = 1;
                              aWork->StepCnt = 0;
                              goto LABEL_115;
                            }
                            v29 = *((u32 *)&gAW_Idx->obj.klass + m);
                            if (v29 == -1)
                              continue;
                            v31 = GetAW(v29);
                            X = v31->X;
                            Z = v31->Z;
                            v34 = aWork->X;
                            v35 = aWork->Z;
                            LenXZ = sBtlGetLenXZ(v34, v35, X, Z);
                            if (LenXZ < 500.0)
                            {
                              v27 = (s64)gScore + 4 * StepIntA;
                              *(u32 *)(v27 + 32) -= 2;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
LABEL_9001:
      v21 = (s64)gScore + 4 * StepIntA;
      *(u32 *)(v21 + 32) += 5;
      goto LABEL_75;
  }
}
