#include "types.h"
#include "battletips.h"
#include "bsflow.h"
#include "dat.h"
#include "dds3kernelcore.h"
#include "dvl.h"
#include "evtbit.h"
#include "fld.h"
#include "sbtl.h"
#include "sbtlactai.h"
#include "sbtlaction.h"
#include "sbtlai.h"
#include "sbtlcalc.h"
#include "sbtlcamera.h"
#include "sbtldmg.h"
#include "sbtldvltk.h"
#include "sbtleff.h"
#include "sbtlencount.h"
#include "sbtlmain.h"
#include "sbtlscript.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sbtlvisual.h"
#include "sdf_vu0.h"
#include "sdfquat.h"
#include "smnr.h"

#define Ex18_D_WAIT 600

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct SB_ENCOUNTPAC SB_ENCOUNTPAC;
typedef struct SB_GENERATOR_WORK SB_GENERATOR_WORK;
typedef struct SB_RNDENCPAC SB_RNDENCPAC;
typedef struct SB_RNDENC_DEVILINFO SB_RNDENC_DEVILINFO;
typedef struct datRndEncRitu_t datRndEncRitu_t;
typedef struct datRndEncTbl_t datRndEncTbl_t;

static SB_ENCOUNTPAC *sb_encountpac[16];
static SB_RNDENCPAC **sb_rndencpac;
s32 g_pac_id;
s32 g_rndenc1_map;
s32 g_rndenc1_floor;
u32 encountcnt;
s32 datRndEncBase;
s32 encmax;
static sdfVector4_t sb_enc_ex_pos;
static sdfVector4_t sb_enc_ex_rot;
static s32 zouen_mes;
SB_GENERATOR_WORK *sb_gen_work;
s32 sb_gen_d_flag;
bool sb_gen_e_zenmetu;

static SBTLUNIT_WORK *SetEncountData_Sub(s32 devil, s32 posid, s32 groupID, s32 EffMode, s32 exflg);
static void UnloadChk(void);
static void UnloadExec(void);
static s32 JudgGoutoZouen(SBTLUNIT_WORK *wk);
static s32 GetRandomNumMax(datRndEncTbl_t *prndenc);

// 0x20bde90
void sBtlInitEncountPac(void *tbl, s32 dlc_no) {
  u32 v5;
  SB_ENCOUNTPAC **sb_encountpac_local;
  Il2CppClass *v8;
  Il2CppClass *v9;
  Il2CppClass **v10;
  s64 v11;
  s64 v13;
  s32 *v14;
  SB_ENCOUNTPAC *v15;
  s32 *v16;
  s64 v17;
  s64 i;
  s32 *enc1;
  SB_ENCOUNT1 *v20;
  s32 Length;
  s64 v23;
  s64 v24;
  s64 j;
  SB_ENCOUNTPAC *v27;
  SB_ENCOUNTPAC *ENCOUNTPAC;
  SB_ENCOUNTPAC *v29;
  SB_ENCOUNTPAC **v30;

  if (dlc_no)
    v5 = 64;
  else
    v5 = 1024;
  if (dlc_no)
  {
    goto LABEL_8;
  }
  else
  {
    v30 = NewSpecific(Project_SB_ENCOUNTPAC__, 0x10u);
    sb_encountpac = v30;
    goto LABEL_8;
  }
LABEL_8:
  sb_encountpac_local = sb_encountpac;
  v8 = NewSpecific(SB_ENCOUNTPAC, v5);
  v9 = v8;
  v10 = &sb_encountpac_local->obj.klass + dlc_no;
  v10[4] = v9;
  v11 = dlc_no;
  v13 = 0;
LABEL_12:
  v14 = sb_encountpac[v11];
  if (v13 < v14[6])
  {
    v15 = Allocate(SB_ENCOUNTPAC);
    _ctor(v15, 0);
    if (!v15)
      goto LABEL_20;
    goto LABEL_9000;
    if (!v15)
    {
LABEL_20:
      v16 = &v14[2 * v13];
      *((u64 *)v16 + 4) = v15;
      v17 = 0;
      for (i = 8; ; i += 2)
      {
        enc1 = sb_encountpac[v11][v13]->enc1;
        if (v17 >= enc1[6])
        {
          ++v13;
          goto LABEL_12;
        }
        v20 = Allocate(SB_ENCOUNT1);
        _ctor(v20, 0);
        if (v20)
        {
          if (!QueryInterface(v20, *(void **)(*(u64 *)enc1 + 64)))
            goto LABEL_30;
        }
        *(u64 *)&enc1[i] = v20;
        ++v17;
      }
    }
LABEL_9000:
    if (!QueryInterface(v15, *(void **)(*(u64 *)v14 + 64)))
      goto LABEL_30;
    goto LABEL_20;
  }
  Length = GetLength(tbl, 0);
  if (Length >= 1)
  {
    v23 = 0;
    v24 = Length;
    for (j = 32; ; j += 8)
    {
      v27 = sb_encountpac[v11];
      ENCOUNTPAC = GetENCOUNTPAC(tbl, v23, 0);
      v29 = ENCOUNTPAC;
      if (ENCOUNTPAC)
      {
          break;
      }
      *(Il2CppClass **)((char *)&v27->obj.klass + j) = v29;
      if (v24 == ++v23)
        return;
    }
LABEL_30:
  }
}

// 0x20be250
void sBtlInitEncountPacDlc(s32 dlc_no) {
  char *v4;
  char *v5;
  char *v6;
  char *v7;
  void *Asset;
  s64 naturalAligment;
  void *v11;
  s32 v14;
  s32 v15;

  v15 = dlc_no;
  if (!fldCheckDlcData(dlc_no))
    return;
  v4 = ToString((s32)&v15, 0);
  v5 = Concat_54766928("battle_dlc", v4, 0);
  v6 = ToString((s32)&v15, 0);
  v7 = Concat_54766928("sb_encountpac_DLC", v6, 0);
  Asset = LoadAsset(_Ctrl_k__BackingField, v5, v7, 0);
  {
    v11 = 0;
    goto LABEL_13;
  }
  if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_BattleEncountPac)
    v11 = Asset;
  else
    v11 = 0;
LABEL_13:
  if (!op_Inequality(v11, 0, 0))
    return;
  v14 = v15;
  sBtlInitEncountPac(v11, v14);
}

// 0x20be4d0
SB_ENCOUNTPAC *sBtlGetEncountPac(s32 dlc_no) {
  s32 DlcMapNo;

  DlcMapNo = dlc_no;
  if (dlc_no == -1)
  {
    DlcMapNo = sBtlGetDlcMapNo();
    return sb_encountpac[DlcMapNo];
  }
  return sb_encountpac[DlcMapNo];
}

// 0x20be590
s32 sBtlGetDlcMapNo(void) {
  s32 v4;
  GlobalWork_t *v5;
  GlobalWork_t *v6;
  s32 nowKiretsuIdx;
  _BOOL4 v8;
  s32 v10;

  if (!fldGb)
    return 0;
  if (fldGb->fieldID == 26)
  {
LABEL_13:
    v4 = 1;
    goto LABEL_14;
  }
  if (fldGb->RndEncFieldID == 26)
    goto LABEL_13;
  v4 = 0;
LABEL_14:
  v5 = fldGb;
  if (v5->fieldID == 29)
  {
LABEL_21:
    v4 = 2;
    goto LABEL_26;
  }
  if (v5->RndEncFieldID == 29)
    goto LABEL_21;
  v6 = fldGb;
  if (v6->fieldID == 30)
    goto LABEL_29;
  goto LABEL_27;
LABEL_26:
  v6 = fldGb;
  if (v6->fieldID == 30)
    goto LABEL_29;
LABEL_27:
  if (v6->RndEncFieldID == 30)
    goto LABEL_29;
  goto LABEL_9001;
  if (fldGb->RndEncFieldID == 30)
  {
LABEL_29:
    v4 = 3;
LABEL_41:
    nowKiretsuIdx = fldGb->nowKiretsuIdx;
    v8 = nowKiretsuIdx == 50;
    goto LABEL_42;
  }
LABEL_9001:
  goto LABEL_41;
LABEL_42:
  if (nowKiretsuIdx == 51)
    v8 = 1;
  if (v8)
    v4 = 4;
  goto LABEL_46;
  {
LABEL_46:
    v10 = nowKiretsuIdx;
    goto LABEL_47;
  }
  v10 = fldGb->nowKiretsuIdx;
LABEL_47:
  if (nowKiretsuIdx == 52 || v10 == 53)
    return 5;
  else
    return v4;
}

// 0x20be860
void sBtlInitRndEncPac(void *tbl, s32 dlc_no) {
  SB_RNDENCPAC **sb_rndencpac_local;
  s32 Length;
  Il2CppClass *v8;
  Il2CppClass *v9;
  Il2CppClass **v10;
  s64 v11;
  s64 v12;
  s64 i;
  SB_RNDENCPAC *v15;
  SB_RNDENCPAC *RNDENCPAC;
  SB_RNDENCPAC *v17;
  SB_RNDENCPAC **v19;

  if (dlc_no)
  {
    goto LABEL_4;
  }
  v19 = NewSpecific(Project_SB_RNDENCPAC__, 0x10u);
  sb_rndencpac = v19;
LABEL_4:
  sb_rndencpac_local = sb_rndencpac;
  Length = GetLength(tbl, 0);
  v8 = NewSpecific(SB_RNDENCPAC, Length);
  v9 = v8;
  v10 = &sb_rndencpac_local->obj.klass + dlc_no;
  v10[4] = v9;
  if (GetLength(tbl, 0) >= 1)
  {
    v11 = 0;
    v12 = dlc_no;
    for (i = 32; ; i += 8)
    {
      v15 = sb_rndencpac[v12];
      RNDENCPAC = GetRNDENCPAC(tbl, v11, 0);
      v17 = RNDENCPAC;
      if (RNDENCPAC)
      {
          break;
      }
      *(Il2CppClass **)((char *)&v15->obj.klass + i) = v17;
      if (++v11 >= GetLength(tbl, 0))
        return;
    }
  }
}

// 0x20bea60
void sBtlInitRndEncPacDlc(s32 dlc_no) {
  char *v4;
  char *v5;
  char *v6;
  char *v7;
  void *Asset;
  s32 v11;
  s64 naturalAligment;
  void *v13;
  s32 v14;

  v14 = dlc_no;
  if (fldCheckDlcData(dlc_no))
    goto LABEL_4;
  return;
  if (fldCheckDlcData(dlc_no))
  {
LABEL_4:
    v4 = ToString((s32)&v14, 0);
    v5 = Concat_54766928("battle_dlc", v4, 0);
    v6 = ToString((s32)&v14, 0);
    v7 = Concat_54766928("sb_rndencpac_DLC", v6, 0);
    Asset = LoadAsset(_Ctrl_k__BackingField, v5, v7, 0);
    v11 = v14;
    if (Asset)
    {
      if (Asset->klass->_2.naturalAligment >= (u32)naturalAligment)
      {
        if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_BattleRndEncPac)
          v13 = Asset;
        else
          v13 = 0;
        goto LABEL_23;
      }
    }
    v13 = 0;
LABEL_23:
    sBtlInitRndEncPac(v13, v11);
    return;
  }
}

// 0x20bec90
SB_RNDENCPAC *sBtlGetRndEncPac(s32 dlc_no) {
  s32 DlcMapNo;

  DlcMapNo = dlc_no;
  if (dlc_no == -1)
  {
    DlcMapNo = sBtlGetDlcMapNo();
    return sb_rndencpac[DlcMapNo];
  }
  return sb_rndencpac[DlcMapNo];
}

// 0x20bed50
datRndEncTbl_t *sBtlGetRndEncTbl_t(s32 id, s32 tbl) {
  s32 nowKiretsuIdx;
  s32 v6;
  s32 v7;
  s32 v8;
  s32 DlcMapNo;
  s32 v13;
  bool v16;
  s64 v17;

  nowKiretsuIdx = fldGb->nowKiretsuIdx;
  v6 = nowKiretsuIdx;
  v7 = nowKiretsuIdx;
  v8 = nowKiretsuIdx;
  DlcMapNo = sBtlGetDlcMapNo();
  if (v6 == 50)
    v13 = 1;
  else
    v13 = tbl;
  v16 = v6 == 50 || v7 == 51 || nowKiretsuIdx == 52 || v8 == 53;
  v17 = id;
  if (v16)
    v17 = 0;
  if (v7 == 51)
    v13 = 2;
  if (nowKiretsuIdx == 52)
    v13 = 1;
  if (v8 == 53)
    v13 = 2;
  return sb_rndencpac[DlcMapNo][v17]->rndenctbl[v13];
}

// 0x20bef90
bool sBtlSetGeneratorData(s32 encountno) {
  s32 DlcMapNo;
  il2cpp_array_size_t max_length;
  s64 v8;
  s64 v9;
  s64 v10;
  SB_GENERATOR_WORK *v11;
  s32 v13;
  SB_ENCOUNT1 *v15;
  u32 type;
  bool v17;
  s32 v18;
  s64 v21;
  s16 zan_num;
  SB_GENERATOR_WORK *v25;
  s32 v29;
  s32 IntervalRand;
  SB_GENERATOR_WORK *v32;

  sBtlClearGeneratorWork();
  DlcMapNo = sBtlGetDlcMapNo();
  max_length = sb_encountpac[DlcMapNo][encountno]->enc1->max_length;
  if ((s32)max_length >= 1)
  {
    v8 = 0;
    v9 = encountno;
    v10 = (u32)max_length;
    do
    {
      v13 = sBtlGetDlcMapNo();
      v15 = sb_encountpac[v13][v9]->enc1[v8];
      type = v15->type;
      v17 = type > 9;
      v18 = (1 << type) & 0x33C;
      if (v17 || v18 == 0)
        goto LABEL_9;
      if (sb_gen_work[0]->use)
      {
        if (sb_gen_work[1]->use)
        {
          if (sb_gen_work[2]->use)
          {
            if (sb_gen_work[3]->use)
            {
              if (sb_gen_work[4]->use)
              {
                if (sb_gen_work[5]->use)
                {
                  if (sb_gen_work[6]->use)
                  {
                    if (sb_gen_work[7]->use)
                    {
                      if (sb_gen_work[8]->use)
                      {
                        if (sb_gen_work[9]->use)
                        {
                          if (sb_gen_work[10]->use)
                          {
                            if (sb_gen_work[11]->use)
                            {
                              if (sb_gen_work[12]->use)
                              {
                                if (sb_gen_work[13]->use)
                                {
                                  if (sb_gen_work[14]->use)
                                  {
                                    if (sb_gen_work[15]->use)
                                    {
                                      if (sb_gen_work[16]->use)
                                      {
                                        if (sb_gen_work[17]->use)
                                        {
                                          if (sb_gen_work[18]->use)
                                          {
                                            if (sb_gen_work[19]->use)
                                            {
                                              if (sb_gen_work[20]->use)
                                              {
                                                if (sb_gen_work[21]->use)
                                                {
                                                  if (sb_gen_work[22]->use)
                                                  {
                                                    if (sb_gen_work[23]->use)
                                                      goto LABEL_9;
                                                    v21 = 23;
                                                  }
                                                  else
                                                  {
                                                    v21 = 22;
                                                  }
                                                }
                                                else
                                                {
                                                  v21 = 21;
                                                }
                                              }
                                              else
                                              {
                                                v21 = 20;
                                              }
                                            }
                                            else
                                            {
                                              v21 = 19;
                                            }
                                          }
                                          else
                                          {
                                            v21 = 18;
                                          }
                                        }
                                        else
                                        {
                                          v21 = 17;
                                        }
                                      }
                                      else
                                      {
                                        v21 = 16;
                                      }
                                    }
                                    else
                                    {
                                      v21 = 15;
                                    }
                                  }
                                  else
                                  {
                                    v21 = 14;
                                  }
                                }
                                else
                                {
                                  v21 = 13;
                                }
                              }
                              else
                              {
                                v21 = 12;
                              }
                            }
                            else
                            {
                              v21 = 11;
                            }
                          }
                          else
                          {
                            v21 = 10;
                          }
                        }
                        else
                        {
                          v21 = 9;
                        }
                      }
                      else
                      {
                        v21 = 8;
                      }
                    }
                    else
                    {
                      v21 = 7;
                    }
                  }
                  else
                  {
                    v21 = 6;
                  }
                }
                else
                {
                  v21 = 5;
                }
              }
              else
              {
                v21 = 4;
              }
            }
            else
            {
              v21 = 3;
            }
          }
          else
          {
            v21 = 2;
          }
        }
        else
        {
          v21 = 1;
        }
      }
      else
      {
        v21 = 0;
      }
      zan_num = v15->zan_num;
      v25 = sb_gen_work[v21];
      v25->use = 1;
      v25->zan_cnt = zan_num;
      LOBYTE(zan_num) = v15->zan_num;
      v25 = sb_gen_work[v21];
      v25->type_d_sommon_flg = 0;
      wk->all_encount_max += (char)zan_num;
      if (g_pac_id == 524 && v15->type == 5)
      {
        v29 = v15->type;
        v25->wait = v21;
        if (v29 != 8)
          goto LABEL_92;
LABEL_89:
        v32 = sb_gen_work[v21];
        v32->wait = GetIntervalRand(0, 30) + 100;
        v29 = v15->type;
        goto LABEL_92;
      }
      v25 = sb_gen_work[v21];
      IntervalRand = GetIntervalRand(0, 30);
      v29 = v15->type;
      v25->wait = IntervalRand;
      if (v29 == 8)
        goto LABEL_89;
LABEL_92:
      if (v29 == 4)
      {
        if (wk->encountno == 24)
        {
          sb_gen_work[v21]->wait = 600;
          goto LABEL_8;
        }
      }
      else
      {
      }
LABEL_8:
      v11 = sb_gen_work[v21];
      v11->penc = v15;
LABEL_9:
      ++v8;
    }
    while (v8 != v10);
  }
  return 1;
}

// 0x20bf740
bool sBtlGetPointData(s32 pointID, sdfVector4_t *pos, sdfVector4_t *rot) {
  f32 *static_fields;
  f32 v10;
  s64 z;
  f32 y;
  f32 x;

  x = 0.0;
  y = 0.0;
  z = 0;
  *(u64 *)&pos->x = 0;
  *(u64 *)&pos->z = 0;
  if (pointID != 100)
  {
    mapEncPointGet(pointID, &x, &y, (f32 *)&z + 1, &z);
    v10 = x;
    pos->w = 1.0;
    pos->x = v10;
    pos->y = y;
    pos->z = *((f32 *)&z + 1);
    FromEuler(0.0, *(f32 *)&z * 0.017453292, 0.0);
    *rot = vct_A;
    return 1;
  }
  pos->x = static_fields[10];
  pos->y = static_fields[11];
  pos->z = static_fields[12];
  pos->w = static_fields[13];
  *(u64 *)&rot->x = 0;
  *(u64 *)&rot->z = 0;
  *rot = sb_enc_ex_rot;
  return 1;
}

// 0x20bf950
void sBtlSetExPos(const sdfVector4_t *pos, const sdfVector4_t *rot) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v7;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 *static_fields;

  w = rot->w;
  z = rot->z;
  y = rot->y;
  x = rot->x;
  v7 = pos->w;
  v8 = pos->z;
  v9 = pos->y;
  v10 = pos->x;
  static_fields[12] = v8;
  static_fields[13] = v7;
  static_fields[14] = x;
  static_fields[15] = y;
  static_fields[16] = z;
  static_fields[17] = w;
  static_fields[10] = v10;
  static_fields[11] = v9;
}

// 0x20bfa10
bool sBtlSetEncountPacData(s32 encountpac_no) {
  s32 DlcMapNo;
  SB_ENCOUNTPAC *v8;
  SBATTLE_WORK *wk_local;
  s32 v10;
  SBATTLE_WORK *v12;
  s32 v13;
  s64 i;
  s64 v16;
  s32 v21;
  s64 v23;
  s32 v25;
  u64 v27;
  s64 v28;
  s32 v29;
  s32 v30;
  s32 v31;
  s32 v32;
  s32 v34;
  SB_ENCOUNT1 *v36;
  s32 devil;
  s32 pos;
  s32 groupID;
  s32 exflg;
  s32 v42;
  s32 v43;
  s32 v44;
  s32 v46;
  s32 v47;
  s32 v48;
  s32 encountno;

  g_pac_id = encountpac_no;
  DlcMapNo = sBtlGetDlcMapNo();
  v8 = sb_encountpac[DlcMapNo][encountpac_no];
  wk_local = wk;
  *(u16 *)&wk_local->maigoEnc = 0;
  v10 = wk_local->encountno;
  if (v10 >= 752)
  {
    if (v10 < 768)
      goto LABEL_20;
  }
  if ((v8->flag & 6) != 0)
    goto LABEL_66;
LABEL_20:
  v12 = wk;
  v13 = v12->encountno;
  if (v13 == 471)
    goto LABEL_66;
  if (v13 == 487)
    goto LABEL_66;
  if (v13 == 528)
    goto LABEL_66;
  v12 = wk;
  v13 = v12->encountno;
  if (v13 != 560)
  {
    v12 = wk;
    v13 = v12->encountno;
    if (v13 != 482)
    {
      v12 = wk;
      v13 = v12->encountno;
      if (v13 != 483)
      {
        v12 = wk;
        v13 = v12->encountno;
        if (v13 != 484)
        {
          v12 = wk;
          if ((v12->status2 & 0x400000) == 0)
          {
            for (i = 4; ; ++i)
            {
              if (i - 4 >= wk->stock_num)
                goto LABEL_66;
              v16 = *((u64 *)&GBWK->player->stock_id->obj.klass + i);
              if (*(u16 *)(v16 + 22))
              {
                v16 = *((u64 *)&GBWK->player->stock_id->obj.klass + i);
                if ((*(u8 *)(v16 + 146) & 0x10) != 0 && GetIntervalRand(0, 100) <= 34)
                  break;
              }
            }
            wk->maigoEnc = 1;
            v21 = EIDtoNID(*(s16 *)(*((u64 *)&GBWK->player->stock_id->obj.klass + i) + 22));
            sBtlSetEncountData(v21, 9, 0, 0);
            return 1;
          }
        }
      }
    }
  }
LABEL_66:
  v23 = encountpac_no;
  v25 = sBtlGetDlcMapNo();
  encountno = encountpac_no;
  if ((s32)sb_encountpac[v25][encountpac_no]->enc1->max_length >= 1)
  {
    v27 = 0;
    v28 = 8
        * (u32)sb_encountpac[v25][encountpac_no]->enc1->max_length;
    while (2)
    {
      v34 = sBtlGetDlcMapNo();
LABEL_82:
      v36 = sb_encountpac[v34][v23]->enc1[v27 / 8];
      switch (v36->type)
      {
        case 1:
        case 8:
          devil = v36->devil;
          pos = v36->pos;
          groupID = v36->groupID;
          exflg = v36->exflg;
          v29 = devil;
          v30 = pos;
          v31 = groupID;
          v32 = 0;
          goto LABEL_76;
        case 6:
          v42 = v36->devil;
          v43 = v36->pos;
          v44 = v36->groupID;
          exflg = v36->exflg;
          v29 = v42;
          v30 = v43;
          v31 = v44;
          v32 = 1;
          goto LABEL_76;
        case 7:
          v46 = v36->devil;
          v47 = v36->pos;
          v48 = v36->groupID;
          exflg = v36->exflg;
          v29 = v46;
          v30 = v47;
          v31 = v48;
          v32 = 2;
LABEL_76:
          SetEncountData_Sub(v29, v30, v31, v32, exflg);
LABEL_77:
          v27 += 8;
          if (v28 != v27)
            continue;
          goto LABEL_106;
        default:
          goto LABEL_77;
      }
      goto LABEL_82;
    }
    v34 = sBtlGetDlcMapNo();
    goto LABEL_82;
  }
LABEL_106:
  wk->gouto_zouen = 0;
  sBtlSetGeneratorData(encountno);
  return 1;
}

// 0x20c0360
static SBTLUNIT_WORK *SetEncountData_Sub(s32 devil, s32 posid, s32 groupID, s32 EffMode, s32 exflg) {
  s64 v12;
  s64 v14;
  sdatPlayerUnitWork_t *player;
  DEVILDATA_WORK *DevilData;
  VISUALDATA_WORK *VisualData;
  SBTLUNIT_WORK *v18;
  sdatUnitWork_t *para;
  SBTLUNIT_WORK *v20;
  s32 aishou;
  SBTLAISYO_DATAWORK *Aisyotbl;
  sdatUnitWork_t *v23;
  sdatParaWork_t *now;
  s32 hp;
  sdatParaWork_t *backup;
  s32 maxhp;
  s64 v28;
  SKLID *haveskill;
  SKLID *v30;
  sdatUnitWork_t *v31;
  sdatUnitWork_t *v33;
  f32 x;
  f32 v38;
  f32 z;
  f32 w;
  struct sdfVector4_t v42;
  sdfVector4_t *v43;
  f32 v46;
  sdfVector4_t *p_rot;
  s32 v49;
  sdfVector4_t *p_rot_p;
  sdfVector4_t *p_koteipos;
  s32 devilid;
  u16 setmotionno;
  s32 ListID;
  SBTLACTAI_WORK *actaiwk;
  sdfVector4_t *p_searchpos;
  sdfVector4_t *p_movepos;
  SBTLACTAI_WORK *v65;
  sdatParaWork_t *v66;
  void *v68;
  s32 v69;
  f32 v70;
  s32 hithelpercnt;
  s32 hithelperno;
  f32 v74;
  f32 v75;
  SBTLEFF_LISTWORK *effList;
  f32 v77;
  f32 v78;
  f32 v79;
  SBTLEFF_LISTWORK *v80;
  SBTLUNIT_WORK *v81;
  s32 v82;
  SBTLEFF_LISTWORK *v85;
  s32 v86;
  f32 v93;
  f32 v94;
  f32 v95;
  f32 v96;
  struct sdfVector4_t pos;
  MOTIONDATA_WORK *MotionVisualData;
  s64 r;
  s64 y;
  sdfVector4_t v101;

  r = 0;
  y = 0;
  if (devil != 125)
    goto LABEL_16;
  if (!wk->maigoEnc)
  {
    v12 = 0;
    devil = 83;
    while (1)
    {
      player = GBWK->player;
      if (v12 >= player->stock_max)
        break;
      player = GBWK->player;
      v14 = (s64)player->stock_id + 8 * v12++;
      if (*(u16 *)(*(u64 *)(v14 + 32) + 22) == 45)
        goto LABEL_16;
    }
    devil = 125;
  }
LABEL_16:
  DevilData = sBtlGetDevilData(devil, -1);
  VisualData = sBtlGetVisualData(2u, devil);
  MotionVisualData = sBtlGetMotionVisualData(2u, devil, 0);
  v18 = sBtlSetSummon_E(1u, devil, groupID, 0);
  para = v18->para;
  v20 = v18;
  para->level = DevilData->level;
  para->devilid = devil;
  para->raceid = DevilData->kuda_id;
  v18->bunriid = DevilData->bunriid;
  aishou = DevilData->aishou;
  v18->exflg = exflg;
  v18->enc_posid = posid;
  v18->aisyoid = aishou;
  Aisyotbl = sBtlGetAisyotbl(aishou);
  ClassCopy(v20->para->aisyo, Aisyotbl, 0);
  ClassCopy(v20->aisyo_bkup, v20->para->aisyo, 0);
  sBtlKudanAisyo(v20);
  v23 = v20->para;
  *(int8x8_t *)&v20->status = vorr_s8(*(int8x8_t *)&DevilData->stflg, *(int8x8_t *)&v20->status);
  if (v23->devilid == 294)
    v20->vstatus |= 8u;
  now = v23->now;
  hp = DevilData->hp;
  now->hp = hp;
  backup = v23->backup;
  backup->hp = hp;
  maxhp = DevilData->maxhp;
  now->maxhp = maxhp;
  backup->maxhp = maxhp;
  v28 = *(u64 *)&DevilData->mp;
  now->mp = v28;
  *(u64 *)&backup->mp = v28;
  *(u64 *)&backup->str = *(u64 *)&DevilData->str;
  haveskill = DevilData->haveskill;
  v30 = v20->haveskill;
  v30[2] = haveskill[0];
  v30[3] = haveskill[1];
  v30[4] = haveskill[2];
  v30[5] = haveskill[3];
  v30[6] = haveskill[4];
  v30[7] = haveskill[5];
  v30[8] = haveskill[6];
  v30[9] = haveskill[7];
  v30[10] = haveskill[8];
  v30[11] = haveskill[9];
  v30[12] = haveskill[10];
  v30[13] = haveskill[11];
  v30[14] = haveskill[12];
  v30[15] = haveskill[13];
  v30[16] = haveskill[14];
  v30[17] = haveskill[15];
  sBtlCheckAutoSkill_Enemy(v20);
  sBtlCheckBattlePara(v20);
  v31 = v20->para;
  v33 = v20->para;
  v31->vice = wk->spirit_enemy;
  v33->seikaku = DevilData->seikaku;
  if (posid != 100)
  {
    mapEncPointGet(posid, (f32 *)&y + 1, &y, (f32 *)&r + 1, &r);
    v46 = *(f32 *)&y;
    v20->pos.x = *((f32 *)&y + 1);
    v20->pos.y = v46;
    v20->pos.z = *((f32 *)&r + 1);
    FromEuler(0.0, *(f32 *)&r * 0.017453292, 0.0);
    p_rot = &v20->rot;
    v49 = (u8)byte_5755EF5;
    *p_rot = vct_A;
    if (v49)
      goto LABEL_47;
    goto LABEL_112;
    if (v86)
    {
LABEL_47:
      goto LABEL_48;
    }
LABEL_112:
LABEL_48:
    vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
    p_rot_p = &v20->rot_p;
    *p_rot_p = vct_A;
    LODWORD(v20->mv_rotbk) = r;
    if ((v20->status & 0x80000) == 0)
      goto LABEL_57;
LABEL_51:
    pos = v20->pos;
    vct_A = pos;
    p_koteipos = &v20->koteipos;
    *p_koteipos = vct_A;
    goto LABEL_57;
  }
  v20->pos.x = sb_enc_ex_pos.x;
  v20->pos.y = sb_enc_ex_pos.y;
  v20->pos.z = sb_enc_ex_pos.z;
  x = sb_enc_ex_rot.x;
  v20->rot.x = x;
  v38 = sb_enc_ex_rot.y;
  v20->rot.y = v38;
  z = sb_enc_ex_rot.z;
  v20->rot.z = z;
  v93 = v38;
  v94 = z;
  w = sb_enc_ex_rot.w;
  v20->rot.w = w;
  v95 = w;
  v96 = x;
  *(u64 *)&v42.x = __PAIR64__(LODWORD(v93), LODWORD(v96));
  *(u64 *)&v42.z = __PAIR64__(LODWORD(v95), LODWORD(v94));
  vct_A = v42;
  v43 = &v20->rot_p;
  *v43 = vct_A;
  sBtlSetRotateDeg(v20);
  if ((v20->status & 0x80000) != 0)
    goto LABEL_51;
LABEL_57:
  v20->actaiwk->status |= 0x1000u;
  devilid = v20->para->devilid;
  if (!!sBtlCheckScriptData(devilid, v20))
  {
    v20->actaiwk->status &= ~0x1000u;
    if ((v20->status & 0x8000000) == 0)
      goto LABEL_60;
    goto LABEL_63;
  }
  if ((v20->status & 0x8000000) == 0)
  {
LABEL_60:
    setmotionno = 0;
    goto LABEL_64;
  }
LABEL_63:
  setmotionno = DevilData->setmotionno;
LABEL_64:
  v20->motion_setno = setmotionno;
  v20->side = 2;
  v20->actaiwk->LeaderID = 0;
  ListID = v20->ListID;
  sBtlSetLockID(v20, ListID);
  v20->mv_spd.z = 0.0;
  actaiwk = v20->actaiwk;
  v20->mv_rot = 0.0;
  v20->max_mvspd.z = VisualData->mv_spd;
  v20->max_mvrot = VisualData->rot_spd;
  actaiwk->status = actaiwk->status & 0xFFFFFE1F | 0x160;
  p_searchpos = &actaiwk->searchpos;
  *p_searchpos = vct_A;
  p_movepos = &v20->actaiwk->movepos;
  *p_movepos = vct_A;
  v65 = v20->actaiwk;
  *(int32x2_t *)&v65->search_area_r = vrev64_s32(*(int32x2_t *)&DevilData->frid_area_r);
  v66 = v20->para->now;
  if (!v66->hp)
    *(u64 *)&v66->hp = 0x3200000032LL;
  v20->scale.x = VisualData->scale;
  v20->scale.y = VisualData->scale;
  v20->scale.z = VisualData->scale;
  v20->scale.w = VisualData->scale;
  v20->size = VisualData->size;
  v20->disp_offy = VisualData->disp_offy;
  v65->hit_area_r = VisualData->hit_area_r;
  v65->priv_area_r = MotionVisualData->m_mv_area_r;
  *(u64 *)&v65->frid_area_r = *(u64 *)&DevilData->frid_area_r;
  v20->actcounter_max = DevilData->actcounter;
  v68 = NewSpecific(f32, 5u);
  InitializeArray_55364416(v68, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__385F200FF22F7AFC1F516A8DBD9004A8F865B3087B932ECB956A889D91483A7A, 0);
  LOWORD(v69) = v20->actcounter_max;
  if ((v20->side & 1) != 0)
  {
    v70 = *((f32 *)&v68[2].klass + v20->para->seikaku) * (f32)(s16)v69;
    v69 = v70;
    if (v70 == INFINITY)
      LOWORD(v69) = 0;
    v20->actcounter_max = v69;
  }
  v20->actcounter = GetIntervalRand(0, (s16)v69);
  hithelpercnt = VisualData->hithelpercnt;
  if (VisualData->hithelpercnt)
  {
    hithelperno = VisualData->hithelperno;
    sBtlCreateHitHelper(v20, hithelperno, hithelpercnt);
    v20->status |= 0x1000u;
  }
  sBtlEncountInit(v20, EffMode);
  if (EffMode != 2)
  {
    if (EffMode == 1)
    {
      v74 = v20->pos.x;
      v75 = v20->pos.y;
      effList = wk->effList;
      v78 = v20->pos.z;
      v77 = v20->pos.w;
      v79 = 1.0;
      v80 = effList;
      v81 = v20;
      v82 = 14;
    }
    else
    {
      if ((v20->status & 0x100000) != 0)
      {
        v74 = v20->pos.x;
        v75 = v20->pos.y;
        v85 = wk->effList;
        v78 = v20->pos.z;
        v77 = v20->pos.w;
        v82 = 5;
      }
      else
      {
        v74 = v20->pos.x;
        v75 = v20->pos.y;
        v85 = wk->effList;
        v78 = v20->pos.z;
        v77 = v20->pos.w;
        v82 = 51;
      }
      v79 = 1.0;
      v80 = v85;
      v81 = v20;
    }
    v101.x = v74;
    v101.y = v75;
    v101.z = v78;
    v101.w = v77;
    sBtlCreateEff(v80, v81, v82, 0, v101, 0x80808080, 0, v79, 0);
    ++wk->gouto_zouen;
    v91 = JudgGoutoZouen(v20);
    zouen_mes = (s32)v91;
    UnloadChk();
    return v20;
  }
  return v20;
}

// 0x20c1210
static void UnloadChk(void) {
  s32 all_encount_max;
  s32 v3;
  s32 v5;
  s32 v7;
  s32 v8;

  all_encount_max = wk->all_encount_max;
  if (all_encount_max < 31)
  {
    v3 = 30;
    goto LABEL_11;
  }
  v3 = all_encount_max + 2;
LABEL_11:
  if (v3 >= 102)
    v5 = 102;
  else
    v5 = v3;
  if (wk->encountno == 515)
    v7 = 30;
  else
    v7 = v5;
  v8 = wk->all_encount_cnt + 1;
  wk->all_encount_cnt = v8;
  if (v8 <= v7)
    return;
  wk->all_encount_cnt = 0;
  wk->all_encount_tim = 40;
}

// 0x20c13a0
static void UnloadExec(void) {
  s32 all_encount_tim;
  s32 v4;

  if (!wk)
    return;
  all_encount_tim = wk->all_encount_tim;
  if (!all_encount_tim)
    return;
  v4 = all_encount_tim - 1;
  wk->all_encount_tim = v4;
  if (v4 > 0)
    return;
  dds3UnloadUnusedAssets(1);
}

// 0x20c11b0
static s32 JudgGoutoZouen(SBTLUNIT_WORK *wk) {
  s32 v2;
  s32 result;

  v2 = (u16)wk->para->devilid - 258;
  result = 2;
  switch (v2)
  {
    case 0:
    case 1:
    case 2:
    case 53:
      return result;
    case 27:
    case 28:
    case 30:
    case 49:
    case 50:
    case 51:
      result = 1;
      break;
    default:
      if (IsAction(4))
        result = 3;
      else
        result = 0;
      break;
  }
  return result;
}

// 0x20c01b0
SBTLUNIT_WORK *sBtlSetEncountData(s32 devil, s32 posid, s32 groupID, s32 exflg) {
  return SetEncountData_Sub(devil, posid, groupID, 0, exflg);
}

// 0x20c0240
SBTLUNIT_WORK *sBtlSetEncountData2(s32 devil, s32 posid, s32 groupID, s32 exflg) {
  return SetEncountData_Sub(devil, posid, groupID, 1, exflg);
}

// 0x20c02d0
SBTLUNIT_WORK *sBtlSetEncountData3(s32 devil, s32 posid, s32 groupID, s32 exflg) {
  return SetEncountData_Sub(devil, posid, groupID, 2, exflg);
}

// 0x20c14d0
SBTLUNIT_WORK *sBtlSetEncountData4(s32 devil, s32 posid, s32 groupID, s32 exflg) {
  SBTLUNIT_WORK *result;

  result = SetEncountData_Sub(devil, posid, groupID, 1, exflg);
  result->aiwk->scrflag |= 0x800000u;
  return result;
}

// 0x20c10f0
void sBtlSetactcounter(SBTLUNIT_WORK *wk) {
  void *v3;
  f32 v4;
  s32 v5;

  v3 = NewSpecific(f32, 5u);
  InitializeArray_55364416(v3, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__385F200FF22F7AFC1F516A8DBD9004A8F865B3087B932ECB956A889D91483A7A, 0);
  if ((wk->side & 1) != 0)
  {
    v4 = *((f32 *)&v3[2].klass + wk->para->seikaku) * (f32)wk->actcounter_max;
    v5 = v4;
    if (v4 == INFINITY)
      LOWORD(v5) = 0;
    wk->actcounter_max = v5;
  }
}

// 0x20bf610
bool sBtlClearGeneratorWork(void) {
  s64 i;
  u64 *v2;
  SB_GENERATOR_WORK *sb_gen_work_local;
  Il2CppObject *v5;

  for (i = 32; i != 224; i += 8)
  {
    sb_gen_work_local = sb_gen_work;
    v5 = Allocate(SB_GENERATOR_WORK);
    _ctor(v5, 0);
    *(Il2CppClass **)((char *)&sb_gen_work_local->obj.klass + i) = v5;
    v2 = *(Il2CppClass **)((char *)&sb_gen_work->obj.klass + i);
    v2[4] = 0;
    v2 += 4;
    *(v2 - 2) = 0;
    *((u32 *)v2 - 2) = 0;
  }
  sb_gen_d_flag = 0;
  return 1;
}

// 0x20c1570
void sBtlGeneratorD_On(s32 group) {
  sb_gen_d_flag = 1;
  return;
}

// 0x20c1600
bool sBtlCheckGeneratorGroupID(s32 group) {
  bool v4;
  s64 v5;
  u64 v6;
  s64 v7;

  v4 = 1;
  v5 = 4;
  {
    if (*(u32 *)(*((u64 *)&sb_gen_work->obj.klass + v5) + 16))
      goto LABEL_10;
LABEL_5:
    v6 = v5 - 4;
    ++v5;
    v4 = v6 < 0x17;
    if (v5 == 28)
      return v4;
  }
  if (!*(u32 *)(*((u64 *)&sb_gen_work->obj.klass + v5) + 16))
    goto LABEL_5;
LABEL_10:
  v7 = *((u64 *)&sb_gen_work->obj.klass + v5);
  if (*(char *)(*(u64 *)(v7 + 32) + 24) != group)
    goto LABEL_5;
  v7 = *((u64 *)&sb_gen_work->obj.klass + v5);
  if (*(s16 *)(v7 + 20) <= 0)
  {
    if (*(s16 *)(*((u64 *)&sb_gen_work->obj.klass + v5) + 20) != -1)
      goto LABEL_5;
  }
  return v4;
}

// 0x20c1740
bool sBtlCheckGeneratorGroupID2(s32 group) {
  bool v4;
  s64 v5;
  u64 v6;
  s64 v7;

  v4 = 1;
  v5 = 4;
  {
    if (*(u32 *)(*((u64 *)&sb_gen_work->obj.klass + v5) + 16))
      goto LABEL_10;
LABEL_5:
    v6 = v5 - 4;
    ++v5;
    v4 = v6 < 0x17;
    if (v5 == 28)
      return v4;
  }
  if (!*(u32 *)(*((u64 *)&sb_gen_work->obj.klass + v5) + 16))
    goto LABEL_5;
LABEL_10:
  v7 = *(u64 *)(*((u64 *)&sb_gen_work->obj.klass + v5) + 32);
  if (*(u32 *)(v7 + 16) == 9 || *(char *)(v7 + 24) != group)
    goto LABEL_5;
  if (*(s16 *)(*((u64 *)&sb_gen_work->obj.klass + v5) + 20) <= 0)
    goto LABEL_5;
  return v4;
}

// 0x20c1860
bool sBtlCheckGenerator_ND(void) {
  bool v3;
  s64 v4;
  u64 v5;
  s64 v6;
  s32 v7;

  v3 = 1;
  v4 = 4;
  {
    if (*(u32 *)(*((u64 *)&sb_gen_work->obj.klass + v4) + 16))
      goto LABEL_9;
LABEL_4:
    v5 = v4 - 4;
    ++v4;
    v3 = v5 < 0x17;
    if (v4 == 28)
      return v3;
  }
  if (!*(u32 *)(*((u64 *)&sb_gen_work->obj.klass + v4) + 16))
    goto LABEL_4;
LABEL_9:
  v6 = *(u64 *)(*((u64 *)&sb_gen_work->obj.klass + v4) + 32);
  if ((u32)(*(u32 *)(v6 + 16) - 2) > 2)
    goto LABEL_4;
  v7 = *(char *)(v6 + 24);
  if (!sBtlCheckGeneratorGroupID(v7))
  {
    goto LABEL_4;
  }
  return v3;
}

// 0x20c1980
bool sBtlCheckGenerator_D(void) {
  bool v2;
  s64 v3;
  u64 v4;
  s64 v6;
  s64 v7;
  s32 v8;

  v2 = 1;
  v3 = 4;
  while (1)
  {
    v6 = *((u64 *)&sb_gen_work->obj.klass + v3);
    if (!*(u32 *)(v6 + 16))
      goto LABEL_5;
    v7 = *(u64 *)(v6 + 32);
    if (*(u32 *)(v7 + 16) != 5)
      goto LABEL_5;
    v8 = *(char *)(v7 + 24);
    if (!sBtlCheckGeneratorGroupID(v8))
      goto LABEL_5;
    if (wk->enemy_num < *(char *)(v7 + 25))
      goto LABEL_22;
LABEL_5:
    v4 = v3 - 4;
    ++v3;
    v2 = v4 < 0x17;
    if (v3 == 28)
      return v2;
  }
  if (wk->enemy_num >= *(char *)(v7 + 25))
    goto LABEL_5;
LABEL_22:
  if (g_pac_id == 524)
  {
    if (*(u16 *)(*((u64 *)&sb_gen_work->obj.klass + v3) + 22))
      goto LABEL_5;
  }
  return v2;
}

// 0x20c1b60
bool sBtlCheckGeneratorAll(void) {
  bool v2;
  s64 v3;
  u64 v4;
  s64 v5;

  v2 = 1;
  v3 = 4;
  {
    v5 = *((u64 *)&sb_gen_work->obj.klass + v3);
    if (*(u32 *)(v5 + 16))
      goto LABEL_10;
LABEL_5:
    v4 = v3 - 4;
    ++v3;
    v2 = v4 < 0x17;
    if (v3 == 28)
      return v2;
  }
  v5 = *((u64 *)&sb_gen_work->obj.klass + v3);
  if (!*(u32 *)(v5 + 16))
    goto LABEL_5;
LABEL_10:
  v5 = *((u64 *)&sb_gen_work->obj.klass + v3);
  if (*(s16 *)(v5 + 20) <= 0)
  {
    if (*(s16 *)(*((u64 *)&sb_gen_work->obj.klass + v3) + 20) != -1)
      goto LABEL_5;
  }
  return v2;
}

// 0x20c1c70
void sBtlSetGeneCam(s16 posID) {
  SBATTLE_WORK *wk_local;
  sdfVector4_t *p_vAddEnemy;
  sdfVector4_t v8;

  if (wk->addEnemyCamCnt)
    return;
  if (sBtlGetMode() != 2)
    return;
  wk_local = wk;
  wk_local->addEnemyCamCnt = 120;
  p_vAddEnemy = &wk_local->vAddEnemy;
  sBtlGetPointData(posID, p_vAddEnemy, &v8);
}

// 0x20c1dc0
bool sBtlGeneratorProc(void) {
  bool v2;
  char v7;
  s32 v8;
  s64 i;
  s64 v10;
  s64 v12;
  char *data;
  s32 encountno;
  u32 v16;
  bool v17;
  s32 v18;
  char v20;
  s32 v23;
  s32 v25;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 v28;
  s32 v32;
  SBTLUNIT_LISTWORK *v33;
  s64 v36;
  s32 v37;
  s32 v38;
  s32 v40;
  SBTLUNIT_LISTWORK *v41;
  s32 v43;
  SBTLUNIT_WORK *v45;
  s32 v46;
  SBTLUNIT_LISTWORK *v47;
  s64 v50;
  s32 v51;
  s32 v52;
  s32 v53;
  s32 v54;
  s32 v55;
  s64 v57;
  s32 v58;
  s32 v63;
  SBTLUNIT_LISTWORK *v64;
  s32 NumUnit_GroupID;
  s32 v67;
  s64 v69;
  s32 v70;
  bool v72;
  s32 v73;
  s32 v74;
  s32 v75;
  s32 v76;
  SBATTLE_WORK *v79;
  char v82;
  s32 v83;
  s32 v84;
  s32 v85;
  s32 v86;
  s32 v87;
  s64 v89;
  s64 v90;
  s32 v91;
  s64 v93;
  s32 v94;
  s16 v95;
  s32 v97;
  s32 v99;
  SBTLUNIT_LISTWORK *v100;
  s32 v102;
  char v105;
  s64 v107;
  s32 v108;
  s32 v110;
  SBTLUNIT_LISTWORK *v111;
  s32 v113;
  s32 v114;
  s32 v118;
  s32 v119;
  s32 v120;
  s32 v121;
  s64 v123;
  s32 v124;
  s32 v126;
  s32 v127;
  s32 v128;
  s32 v129;
  s32 v130;
  SBTLUNIT_WORK *v131;
  s64 v133;
  s32 v134;
  s64 v136;
  s32 v137;
  s16 v138;
  SBATTLE_WORK *v140;
  SBATTLE_WORK *v141;
  SBTLDVLTK_LISTWORK *dvltkList;
  SBTLUNIT_WORK *PChara;
  s32 v147;
  SBTLDVLTK_LISTWORK *v148;
  SBTLUNIT_WORK *v149;
  s32 v150;
  SBTLUNIT_LISTWORK *v152;
  s32 v153;
  s32 v154;
  sdatPlayerUnitWork_t *player;
  s16 *stack_p;
  SBATTLE_WORK *v160;
  s32 v161;
  s16 *summonindex;
  s32 *summonindex_menu;
  SBTLDVLTK_LISTWORK *v165;
  SBTLUNIT_WORK *v166;

  if (wk->endcnt > 0)
    return 1;
  if (IsSceanStop())
    return 1;
  if ((wk->status2 & 0x80000) != 0)
    return 0;
  if (wk->cmbSkl->bRun)
    return 0;
  if (wk->sklProc->bRun)
    return 0;
  if (wk->kaiwaflg)
    return 0;
  if (sBtlCheckPlayerDead())
    return 0;
  UnloadExec();
  v7 = 0;
  v8 = -1;
  for (i = 32; i != 224; i += 8)
  {
    v12 = *(s64 *)((char *)&sb_gen_work->obj.klass + i);
    if (!*(u32 *)(v12 + 16))
      continue;
    data = *(char **)(v12 + 32);
    encountno = wk->encountno;
    if (encountno > 395)
    {
      if ((u32)encountno <= 0x1A3)
      {
        if (encountno == 413 || encountno == 419)
          goto LABEL_60;
      }
      else
      {
        if (encountno == 486)
          goto LABEL_60;
        if ((u32)(encountno - 491) > 0xFFFFFFFC)
          goto LABEL_72;
        v16 = encountno - 528;
        v17 = v16 > 6;
        v18 = (1 << v16) & 0x4D;
        if (!v17 && v18 != 0)
          goto LABEL_72;
      }
      goto LABEL_75;
    }
    if (encountno > 2)
    {
      if (encountno == 66)
      {
LABEL_60:
        if (data[25] < 5)
          goto LABEL_75;
        v20 = 4;
      }
      else if (encountno == 127)
      {
        if (data[25] < 4)
          goto LABEL_75;
        v20 = 3;
      }
      else
      {
        if ((encountno & 0xFFFFFFFE) != 0x18A)
          goto LABEL_75;
LABEL_72:
        if (data[25] < 6)
          goto LABEL_75;
        v20 = 5;
      }
      data[25] = v20;
      goto LABEL_75;
    }
    if (encountno == 1 || encountno == 2)
    {
      if (sBtlGetDlcMapNo() == 4)
        goto LABEL_72;
      if (sBtlGetDlcMapNo() == 5)
        goto LABEL_72;
    }
LABEL_75:
    v23 = *((u32 *)data + 4);
    if (v23 == 3)
    {
      v25 = data[27];
      UnitMng = wk->UnitMng;
      if (sBtlGetNumUnit_GroupID(UnitMng, v25) > 0)
        continue;
      v28 = data[27];
      if (sBtlCheckGeneratorGroupID(v28))
        continue;
      if (wk->InfiniteSpringStop_flag)
      {
        v10 = *(s64 *)((char *)&sb_gen_work->obj.klass + i);
        *(u16 *)(v10 + 20) = 0;
LABEL_34:
        *(u32 *)(v10 + 16) = 0;
        continue;
      }
      v23 = *((u32 *)data + 4);
    }
    if ((v23 & 0xFFFFFFFE) == 2)
    {
      v32 = data[24];
      v33 = wk->UnitMng;
      if (sBtlGetNumUnit_GroupID(v33, v32) < data[25])
      {
        v36 = *(s64 *)((char *)&sb_gen_work->obj.klass + i);
        v37 = *(u32 *)(v36 + 24);
        if (v37 >= 1)
        {
          v36 = *(s64 *)((char *)&sb_gen_work->obj.klass + i);
          v37 = *(u32 *)(v36 + 24);
          *(u32 *)(v36 + 24) = v37 - 1;
        }
        v8 = data[24];
        if (LODWORD((*(Il2CppClass **)((char *)&sb_gen_work->obj.klass + i))->_1.namespaze))
          goto LABEL_105;
        v73 = *((s16 *)data + 11);
        v74 = data[20];
        v75 = data[24];
        v76 = *((u32 *)data + 7);
        sBtlSetEncountData(v73, v74, v75, v76);
        sBtlSetGeneCam(data[20]);
        v79 = wk;
        if (v79->encountno == 515)
        {
          v79 = wk;
          v79->tuto_r2_di = 1;
          goto LABEL_193;
        }
LABEL_193:
        v90 = *(s64 *)((char *)&sb_gen_work->obj.klass + i);
        v91 = GetIntervalRand(0, 30) + 100;
        *(u32 *)(v90 + 24) = v91;
        v93 = *(s64 *)((char *)&sb_gen_work->obj.klass + i);
        v94 = *(u16 *)(v93 + 20);
        if (v94 != 0xFFFF)
        {
          v93 = *(s64 *)((char *)&sb_gen_work->obj.klass + i);
          LOWORD(v94) = *(u16 *)(v93 + 20);
          v95 = v94 - 1;
          *(u16 *)(v93 + 20) = v95;
          if (v95 <= 0)
          {
            v93 = *(s64 *)((char *)&sb_gen_work->obj.klass + i);
            *(u32 *)(v93 + 16) = 0;
          }
        }
LABEL_105:
        v7 = 1;
        goto LABEL_106;
      }
    }
LABEL_106:
    v38 = *((u32 *)data + 4);
    if (v38 == 4)
    {
      v40 = data[27];
      v41 = wk->UnitMng;
      if (sBtlGetNumUnit_GroupID(v41, v40) <= 0)
      {
        v43 = data[27];
        if (!sBtlCheckGeneratorGroupID(v43))
        {
          v10 = *(s64 *)((char *)&sb_gen_work->obj.klass + i);
          goto LABEL_34;
        }
      }
      if (wk->encountno == 24)
      {
        v45 = sBtlSearchDeivl(165);
        if (!v45 || v45->para->now->hp < 1)
          continue;
      }
      v46 = data[24];
      v47 = wk->UnitMng;
      if (sBtlGetNumUnit_GroupID(v47, v46) < data[25])
      {
        v50 = *(s64 *)((char *)&sb_gen_work->obj.klass + i);
        v51 = *(u32 *)(v50 + 24);
        if (v51 >= 1)
        {
          v50 = *(s64 *)((char *)&sb_gen_work->obj.klass + i);
          v51 = *(u32 *)(v50 + 24);
          *(u32 *)(v50 + 24) = v51 - 1;
        }
        v8 = data[24];
        if (!LODWORD((*(Il2CppClass **)((char *)&sb_gen_work->obj.klass + i))->_1.namespaze))
        {
          v52 = *((s16 *)data + 11);
          v53 = data[20];
          v54 = data[24];
          v55 = *((u32 *)data + 7);
          sBtlSetEncountData(v52, v53, v54, v55);
          sBtlSetGeneCam(data[20]);
          v57 = *(s64 *)((char *)&sb_gen_work->obj.klass + i);
          v58 = GetIntervalRand(0, 30) + 100;
          *(u32 *)(v57 + 24) = v58;
          if (wk->encountno == 24)
          {
            LODWORD((*(Il2CppClass **)((char *)&sb_gen_work->obj.klass + i))->_1.namespaze) = 600;
          }
        }
        v7 = 1;
      }
      v38 = *((u32 *)data + 4);
    }
    if (v38 == 5)
    {
      if (sb_gen_d_flag)
      {
        v63 = data[24];
        v64 = wk->UnitMng;
        NumUnit_GroupID = sBtlGetNumUnit_GroupID(v64, v63);
        if (NumUnit_GroupID < data[25])
        {
          v67 = NumUnit_GroupID;
          v69 = *(s64 *)((char *)&sb_gen_work->obj.klass + i);
          v70 = *(u32 *)(v69 + 24);
          if (v70 >= 1)
          {
            v69 = *(s64 *)((char *)&sb_gen_work->obj.klass + i);
            v70 = *(u32 *)(v69 + 24);
            *(u32 *)(v69 + 24) = v70 - 1;
          }
          v8 = data[24];
          if (g_pac_id == 524)
          {
            v72 = HIWORD((*(Il2CppClass **)((char *)&sb_gen_work->obj.klass + i))->_1.name) == 1;
          }
          else
          {
            v72 = 0;
          }
          if (LODWORD((*(Il2CppClass **)((char *)&sb_gen_work->obj.klass + i))->_1.namespaze))
            v82 = 1;
          else
            v82 = v72;
          if ((v82 & 1) != 0)
          {
            v7 = 1;
          }
          else
          {
            v83 = v8;
            v84 = *((s16 *)data + 11);
            v85 = data[20];
            v86 = data[24];
            v87 = *((u32 *)data + 7);
            sBtlSetEncountData(v84, v85, v86, v87);
            sBtlSetGeneCam(data[20]);
            v7 = 1;
            v89 = *(s64 *)((char *)&sb_gen_work->obj.klass + i);
            *(u16 *)(v89 + 22) = 1;
            *(u32 *)(v89 + 24) = GetIntervalRand(0, 30) + 30;
            if (v67 + 1 >= data[25])
            {
              v8 = v83;
              sb_gen_d_flag = 0;
            }
            else
            {
              v8 = v83;
            }
          }
        }
      }
    }
    v97 = *((u32 *)data + 4);
    if (v97 != 8)
      goto LABEL_230;
    v99 = data[24];
    v100 = wk->UnitMng;
    v102 = sBtlGetNumUnit_GroupID(v100, v99);
    if (!sb_gen_e_zenmetu)
    {
      if (v102)
        goto LABEL_216;
      v105 = 1;
LABEL_214:
      sb_gen_e_zenmetu = v105;
      goto LABEL_216;
    }
    if (v102 == data[25])
    {
      v105 = 0;
      goto LABEL_214;
    }
LABEL_216:
    if (sb_gen_e_zenmetu)
    {
      v107 = *(s64 *)((char *)&sb_gen_work->obj.klass + i);
      v108 = *(u32 *)(v107 + 24);
      if (v108 >= 1)
      {
        v107 = *(s64 *)((char *)&sb_gen_work->obj.klass + i);
        v108 = *(u32 *)(v107 + 24);
        *(u32 *)(v107 + 24) = v108 - 1;
      }
      v8 = data[24];
      if (!LODWORD((*(Il2CppClass **)((char *)&sb_gen_work->obj.klass + i))->_1.namespaze))
      {
        v127 = *((s16 *)data + 11);
        v128 = data[20];
        v129 = data[24];
        v130 = *((u32 *)data + 7);
        v131 = sBtlSetEncountData(v127, v128, v129, v130);
        v131->hstatus |= 0xCu;
        sBtlSetGeneCam(data[20]);
        v133 = *(s64 *)((char *)&sb_gen_work->obj.klass + i);
        v134 = GetIntervalRand(0, 30) + 100;
        *(u32 *)(v133 + 24) = v134;
        v136 = *(s64 *)((char *)&sb_gen_work->obj.klass + i);
        v137 = *(u16 *)(v136 + 20);
        if (v137 != 0xFFFF)
        {
          v136 = *(s64 *)((char *)&sb_gen_work->obj.klass + i);
          LOWORD(v137) = *(u16 *)(v136 + 20);
          v138 = v137 - 1;
          *(u16 *)(v136 + 20) = v138;
          if (v138 <= 0)
          {
            v136 = *(s64 *)((char *)&sb_gen_work->obj.klass + i);
            *(u32 *)(v136 + 16) = 0;
          }
        }
      }
      v7 = 1;
    }
    v97 = *((u32 *)data + 4);
LABEL_230:
    if (v97 == 9)
    {
      v110 = data[24];
      v111 = wk->UnitMng;
      v113 = sBtlGetNumUnit_GroupID(v111, v110);
      v114 = data[24];
      if (!sBtlCheckGeneratorGroupID2(v114) && v113 < data[25])
      {
        v8 = data[24];
        LODWORD((*(Il2CppClass **)((char *)&sb_gen_work->obj.klass + i))->_1.namespaze) = 0;
        {
          v118 = *((s16 *)data + 11);
          v119 = data[20];
          v120 = data[24];
          v121 = *((u32 *)data + 7);
          sBtlSetEncountData(v118, v119, v120, v121);
          sBtlSetGeneCam(data[20]);
          v123 = *(s64 *)((char *)&sb_gen_work->obj.klass + i);
          v124 = GetIntervalRand(0, 30) + 100;
          *(u32 *)(v123 + 24) = v124;
          v10 = *(s64 *)((char *)&sb_gen_work->obj.klass + i);
          v126 = (s16)--*(u16 *)(v10 + 20);
          if (v126 <= 0)
          {
            v10 = *(s64 *)((char *)&sb_gen_work->obj.klass + i);
            v7 = 1;
            goto LABEL_34;
          }
        }
        v7 = 1;
      }
    }
  }
  v140 = wk;
  if ((v140->gouto_zouen == 0) | v7 & 1)
  {
    if ((v7 & 1) != 0)
      goto LABEL_265;
LABEL_293:
    goto LABEL_294;
  }
  v140 = wk;
  if ((v140->status & 0x10000) != 0)
  {
    if (zouen_mes == 1)
    {
      dvltkList = wk->dvltkList;
      PChara = sBtlGetPChara();
      v147 = 282;
      v148 = dvltkList;
      v149 = PChara;
      v150 = 2;
      goto LABEL_281;
    }
    if (zouen_mes != 2)
    {
      if (zouen_mes != 3)
      {
        v165 = wk->dvltkList;
        v166 = sBtlGetPChara();
        v147 = 281;
        v148 = v165;
        v149 = v166;
        v150 = 3;
LABEL_281:
        sBtlCreateDvltk_Gouto(v148, v149, v147, v150);
      }
    }
  }
  zouen_mes = 0;
  wk->gouto_zouen = 0;
  if ((v7 & 1) == 0)
    goto LABEL_293;
LABEL_265:
  SummonTipsCall(v8);
LABEL_294:
  v141 = wk;
  if (v141->t1_3_nakama)
    return 1;
  v141 = wk;
  if (v141->encountno != 23)
    return 1;
  v141 = wk;
  v152 = v141->UnitMng;
  v153 = sBtlGetNumUnit_GroupID(v152, 2);
  v154 = sBtlGetNumUnit_GroupID(wk->UnitMng, 3);
  if (v154 + v153 + sBtlGetNumUnit_GroupID(wk->UnitMng, 4) != 3)
    return 1;
  player = GBWK->player;
  stack_p = player->stack_p;
  v160 = wk;
  v161 = stack_p[0];
  summonindex = v160->summonindex;
  summonindex_menu = v160->summonindex_menu;
  summonindex[0] = stack_p[0];
  LODWORD(stack_p) = stack_p[1];
  summonindex[1] = (s16)stack_p;
  summonindex_menu[0] = v161;
  summonindex_menu[1] = (s32)stack_p;
  sBtlNakamaSetUp(0);
  v2 = 1;
  sBtlNakamaSetUp(1);
  wk->t1_3_nakama = 1;
  return v2;
}

// 0x20c3060
s32 sBtlGetRndEncJoken(s32 id) {
  datRndEncTbl_t *RndEncTbl_t;
  s32 flag0;
  s32 flag0j;
  bool v9;
  s32 result;
  s32 flag1j;
  bool v13;
  datRndEncTbl_t *v14;
  s32 v15;
  s32 v17;
  bool v18;
  s32 v20;
  s32 v21;
  bool v22;
  datRndEncTbl_t *v23;
  s32 v24;
  s32 v26;
  bool v27;
  s32 flag1;
  s32 v29;
  bool v30;

  RndEncTbl_t = sBtlGetRndEncTbl_t(id, 0);
  flag0 = RndEncTbl_t->flag0;
  if (RndEncTbl_t->flag0)
  {
    flag0j = RndEncTbl_t->flag0j;
    v9 = evtBitCheck(flag0);
    if (flag0j)
    {
      if (!v9)
        goto LABEL_16;
    }
    else if (v9)
    {
      goto LABEL_16;
    }
  }
  result = RndEncTbl_t->flag1;
  if (!RndEncTbl_t->flag1)
    return result;
  flag1j = RndEncTbl_t->flag1j;
  v13 = evtBitCheck(result);
  if (flag1j)
  {
    if (v13)
      return 0;
  }
  else if (!v13)
  {
    return 0;
  }
LABEL_16:
  v14 = sBtlGetRndEncTbl_t(id, 1);
  v15 = v14->flag0;
  if (!v14->flag0)
    goto LABEL_24;
  v17 = v14->flag0j;
  v18 = evtBitCheck(v15);
  if (v17)
  {
    if (!v18)
    {
LABEL_30:
      v23 = sBtlGetRndEncTbl_t(id, 2);
      v24 = v23->flag0;
      if (!v23->flag0)
        goto LABEL_39;
      goto LABEL_9001;
      if (!v23->flag0)
      {
LABEL_39:
        flag1 = v23->flag1;
        if (!v23->flag1)
          return 2;
        v29 = v23->flag1j;
        v30 = evtBitCheck(flag1);
        if (v29)
        {
          if (v30)
            return 2;
        }
        else if (!v30)
        {
          return 2;
        }
        return 0;
      }
LABEL_9001:
      v26 = v23->flag0j;
      v27 = evtBitCheck(v24);
      if (v26)
      {
        if (!v27)
          return 0;
      }
      else if (v27)
      {
        return 0;
      }
      goto LABEL_39;
    }
  }
  else if (v18)
  {
    goto LABEL_30;
  }
LABEL_24:
  v20 = v14->flag1;
  if (!v14->flag1)
    return 1;
  v21 = v14->flag1j;
  v22 = evtBitCheck(v20);
  if (!v21)
  {
    if (v22)
      goto LABEL_30;
    return 1;
  }
  if (!v22)
    goto LABEL_30;
  return 1;
}

// 0x20c3280
s32 sBtlGetRndEncType(s32 id, s32 nakama) {
  s32 RndEncJoken;
  datRndEncTbl_t *RndEncTbl_t;
  s32 result;
  u32 v12;
  dds3GlobalWork_t *v14;
  u32 encountcnt_local;
  dds3GlobalWork_t *v17;
  u32 v19;
  datRndEncRitu_t *ritu;
  datRndEncRitu_t *v21;
  s64 v22;
  datRndEncRitu_t *v23;
  datRndEncRitu_t *v24;
  datRndEncRitu_t *v25;
  datRndEncRitu_t *v26;
  datRndEncRitu_t *v27;
  datRndEncRitu_t *v28;
  datRndEncRitu_t *v29;
  s32 v30;
  s32 v32;
  datRndEncRitu_t *v33;
  datRndEncRitu_t *v34;
  s32 encountid;

  if (!id)
    return 0;
  RndEncJoken = sBtlGetRndEncJoken(id);
  RndEncTbl_t = sBtlGetRndEncTbl_t(id, RndEncJoken);
  result = sBtlGetRndEncMax(id);
  if (result)
  {
    if (GBWK->fix_encountflg == 3)
    {
      result = 0;
      GBWK->fix_encountflg = 0;
      return result;
    }
    if (nakama)
      goto LABEL_35;
    if (GBWK->encountcnt)
    {
      goto LABEL_18;
    }
    encountcnt_local = 0;
    encountcnt = encountcnt_local;
LABEL_18:
    v12 = GBWK->encountcnt;
    if (v12 == encountcnt)
    {
      v14 = GBWK;
      if (v14->fix_encountflg)
      {
        v14 = GBWK;
        return v14->fix_encounttype;
      }
      return 0;
    }
LABEL_35:
    v17 = GBWK;
    v19 = v17->encountcnt;
    encountcnt = v19;
    if (v17->fix_encountflg)
    {
      return v17->fix_encounttype;
    }
    ritu = RndEncTbl_t->ritu;
    v21 = ritu[0];
    if (v21->encountid)
    {
      v22 = v21->ritu;
      v23 = ritu[1];
      if (!v23->encountid)
        goto LABEL_47;
    }
    else
    {
      v22 = 0;
      v23 = ritu[1];
      if (!v23->encountid)
      {
LABEL_47:
        v24 = ritu[2];
        if (v24->encountid)
          v22 = (u32)v22 + v24->ritu;
        v25 = ritu[3];
        if (v25->encountid)
          v22 = (u32)v22 + v25->ritu;
        v26 = ritu[4];
        if (v26->encountid)
          v22 = (u32)v22 + v26->ritu;
        v27 = ritu[5];
        if (v27->encountid)
          v22 = (u32)v22 + v27->ritu;
        v28 = ritu[6];
        if (v28->encountid)
          v22 = (u32)v22 + v28->ritu;
        v29 = ritu[7];
        if (v29->encountid)
          v22 = (u32)v22 + v29->ritu;
        v30 = sub_1905740(v22, 0);
        v32 = v30;
        result = 0;
        GBWK->fix_encountflg = 0;
        if (!nakama)
        {
          v33 = RndEncTbl_t->ritu;
          v34 = v33[0];
          encountid = v34->encountid;
          if (v34->encountid)
          {
            encountid = v34->ritu;
            if (v32 < encountid)
              return v34->type;
          }
          v34 = v33[1];
          if (v34->encountid)
          {
            encountid += v34->ritu;
            if (encountid > v32)
              return v34->type;
          }
          v34 = v33[2];
          if (v34->encountid)
          {
            encountid += v34->ritu;
            if (encountid > v32)
              return v34->type;
          }
          v34 = v33[3];
          if (v34->encountid)
          {
            encountid += v34->ritu;
            if (encountid > v32)
              return v34->type;
          }
          v34 = v33[4];
          if (v34->encountid)
          {
            encountid += v34->ritu;
            if (encountid > v32)
              return v34->type;
          }
          v34 = v33[5];
          if (v34->encountid)
          {
            encountid += v34->ritu;
            if (encountid > v32)
              return v34->type;
          }
          v34 = v33[6];
          if (v34->encountid)
          {
            encountid += v34->ritu;
            if (encountid > v32)
              return v34->type;
          }
          v34 = v33[7];
          if (v34->encountid)
          {
            if (encountid + v34->ritu > v32)
              return v34->type;
          }
          return 0;
        }
        return result;
      }
    }
    v22 = (u32)v22 + v23->ritu;
    goto LABEL_47;
  }
  return result;
}

// 0x20c3a90
void sBtlResetRndEncType(void) {
  if (GBWK->fix_encountflg != 2)
    return;
  GBWK->fix_encountflg = 0;
}

// 0x20c3790
s32 sBtlGetRndEncMax(s32 id) {
  s32 RndEncJoken;
  datRndEncTbl_t *RndEncTbl_t;
  datRndEncRitu_t *ritu;
  datRndEncTbl_t *v9;
  u64 v14;
  s32 v15;
  s32 v16;
  s32 v17;

  if (!id)
    return 0;
  RndEncJoken = sBtlGetRndEncJoken(id);
  RndEncTbl_t = sBtlGetRndEncTbl_t(id, RndEncJoken);
  ritu = RndEncTbl_t->ritu;
  if (!(ritu[0]->ritu + ritu[1]->ritu + ritu[2]->ritu + ritu[3]->ritu + ritu[4]->ritu + ritu[5]->ritu + ritu[6]->ritu + ritu[7]->ritu))
    return 0;
  v9 = RndEncTbl_t;
  if (encmax >= 1)
  {
    return encmax;
  }
  v14 = 0xFFFFFFF0A3D70A30LL * v9->normalritu;
  v15 = (v14 >> 63) + (SHIDWORD(v14) >> 5) + datRndEncBase;
  if (v15 <= 50)
    v15 = 50;
  v16 = sub_1905740((u32)(2 * v15 - 96), 0);
  encmax = v16 + 48;
  if (v9->normalritu == 100)
  {
    v17 = sub_1905740(500, 0);
    encmax = v17 + 1000;
    return encmax;
  }
  return encmax;
}

// 0x20c3b50
s32 sBtlGetRndEncCnt(void) {
  return GBWK->encountcnt;
}

// 0x20c3be0
s32 sBtlRndEncCalc(s32 id, f32 length) {
  s32 fix_encountno;
  s32 RndEncJoken;
  datRndEncTbl_t *RndEncTbl_t;
  s32 RndEncMax;
  s32 v12;
  f32 encountkyori;
  s32 v16;
  dds3GlobalWork_t *v17;
  dds3GlobalWork_t *v18;
  dds3GlobalWork_t *v19;
  u32 encountcnt;
  s64 RandomNumMax;
  s32 v24;
  datRndEncRitu_t *ritu;
  s32 v26;
  datRndEncRitu_t *v27;
  s32 encountid;
  s32 v29;
  s32 v31;
  s32 v32;
  s32 v33;
  s32 v34;
  s32 v35;
  s32 v36;
  s32 v37;
  s32 v38;
  s32 v39;
  s32 v40;
  s32 v41;
  s32 v42;
  s32 v43;
  s32 floor;

  fix_encountno = 0;
  if (id && length != 0.0)
  {
    RndEncJoken = sBtlGetRndEncJoken(id);
    RndEncTbl_t = sBtlGetRndEncTbl_t(id, RndEncJoken);
    RndEncMax = sBtlGetRndEncMax(id);
    if (!RndEncMax)
      return 0;
    v12 = RndEncMax;
    encountkyori = GBWK->encountkyori + length;
    GBWK->encountkyori = encountkyori;
    if (encountkyori < 100.0)
      return 0;
    encountkyori = GBWK->encountkyori;
    if ((f32)(encountkyori / 100.0) == INFINITY)
      v16 = 0x80000000;
    else
      v16 = (f32)(encountkyori / 100.0);
    GBWK->encountkyori = encountkyori - (f32)((f32)v16 * 100.0);
    if (v16 >= 1)
    {
      do
      {
        v19 = GBWK;
        encountcnt = v19->encountcnt;
        --v16;
        v19->encountcnt = encountcnt + sub_1905740(3, 0) + 2;
      }
      while (v16);
LABEL_18:
      v17 = GBWK;
      if (v17->encountcnt < 0xFDE9)
        goto LABEL_19;
      goto LABEL_27;
    }
    {
      goto LABEL_18;
    }
    v17 = GBWK;
    if (v17->encountcnt < 0xFDE9)
    {
LABEL_19:
      goto LABEL_20;
    }
LABEL_27:
    v17 = GBWK;
    v17->encountcnt = 65000;
LABEL_20:
    v18 = GBWK;
    if (v18->encountcnt < (s64)v12)
      return 0;
    v18 = GBWK;
    if (v18->fix_encountflg == 1)
    {
      v18 = GBWK;
      fix_encountno = v18->fix_encountno;
      v18->fix_encountflg = 3;
      return fix_encountno;
    }
    RandomNumMax = GetRandomNumMax(RndEncTbl_t);
    v24 = sub_1905740(RandomNumMax, 0);
    ritu = RndEncTbl_t->ritu;
    v26 = v24;
    v27 = ritu[0];
    encountid = v27->encountid;
    if (v27->encountid)
    {
      v29 = v27->ritu;
      if (v24 < v29)
      {
        if (v29 == 1000)
          goto LABEL_103;
        if (fldGb->lastTimeEncountID != encountid)
          goto LABEL_103;
        v29 = v27->ritu;
        ritu = RndEncTbl_t->ritu;
      }
    }
    else
    {
      v29 = 0;
    }
    v27 = ritu[1];
    v31 = v27->encountid;
    if (v27->encountid)
    {
      v32 = v29 + v27->ritu;
      if (v32 > v26)
      {
        if (v32 == 1000)
          goto LABEL_103;
        if (fldGb->lastTimeEncountID != v31)
          goto LABEL_103;
        v32 = v29 + v27->ritu;
        ritu = RndEncTbl_t->ritu;
      }
    }
    else
    {
      v32 = v29;
    }
    v27 = ritu[2];
    v33 = v27->encountid;
    if (v27->encountid)
    {
      v34 = v32 + v27->ritu;
      if (v34 > v26)
      {
        if (v34 == 1000)
          goto LABEL_103;
        if (fldGb->lastTimeEncountID != v33)
          goto LABEL_103;
        v34 = v32 + v27->ritu;
        ritu = RndEncTbl_t->ritu;
      }
    }
    else
    {
      v34 = v32;
    }
    v27 = ritu[3];
    v35 = v27->encountid;
    if (v27->encountid)
    {
      v36 = v34 + v27->ritu;
      if (v36 > v26)
      {
        if (v36 == 1000)
          goto LABEL_103;
        if (fldGb->lastTimeEncountID != v35)
          goto LABEL_103;
        v36 = v34 + v27->ritu;
        ritu = RndEncTbl_t->ritu;
      }
    }
    else
    {
      v36 = v34;
    }
    v27 = ritu[4];
    v37 = v27->encountid;
    if (v27->encountid)
    {
      v38 = v36 + v27->ritu;
      if (v38 > v26)
      {
        if (v38 == 1000)
          goto LABEL_103;
        if (fldGb->lastTimeEncountID != v37)
          goto LABEL_103;
        v38 = v36 + v27->ritu;
        ritu = RndEncTbl_t->ritu;
      }
    }
    else
    {
      v38 = v36;
    }
    v27 = ritu[5];
    v39 = v27->encountid;
    if (v27->encountid)
    {
      v40 = v38 + v27->ritu;
      if (v40 > v26)
      {
        if (v40 == 1000)
          goto LABEL_103;
        if (fldGb->lastTimeEncountID != v39)
          goto LABEL_103;
        v40 = v38 + v27->ritu;
        ritu = RndEncTbl_t->ritu;
      }
    }
    else
    {
      v40 = v38;
    }
    v27 = ritu[6];
    v41 = v27->encountid;
    if (!v27->encountid)
    {
      v42 = v40;
LABEL_97:
      v27 = ritu[7];
      fix_encountno = v27->encountid;
      if (!v27->encountid)
        return fix_encountno;
      v43 = v42 + v27->ritu;
      if (v43 > v26)
      {
        if (v43 == 1000)
          goto LABEL_103;
        if (fldGb->lastTimeEncountID != fix_encountno)
          goto LABEL_103;
      }
      return 0;
    }
    v42 = v40 + v27->ritu;
    if (v42 <= v26)
      goto LABEL_97;
    if (v42 != 1000)
    {
      if (fldGb->lastTimeEncountID == v41)
      {
        v42 = v40 + v27->ritu;
        ritu = RndEncTbl_t->ritu;
        goto LABEL_97;
      }
    }
LABEL_103:
    fix_encountno = v27->encountid;
    fldGb->lastTimeEncountID = fix_encountno;
    encmax = 0;
    floor = v27->floor;
    g_rndenc1_map = v27->map;
    g_rndenc1_floor = floor;
    GBWK->fix_encountflg = 3;
    return fix_encountno;
  }
  return fix_encountno;
}

// 0x20c4260
s32 sBtlRndEncCalc_Symbol(s32 id, s32 *_map, s32 *_floor) {
  s32 RndEncJoken;
  datRndEncTbl_t *RndEncTbl_t;
  datRndEncRitu_t *ritu;
  datRndEncRitu_t *v12;
  s64 v13;
  datRndEncRitu_t *v14;
  datRndEncRitu_t *v15;
  datRndEncRitu_t *v16;
  datRndEncRitu_t *v17;
  datRndEncRitu_t *v18;
  datRndEncRitu_t *v19;
  datRndEncRitu_t *v20;
  s32 v21;
  datRndEncRitu_t *v22;
  datRndEncRitu_t *v23;
  s32 encountid;
  s32 v25;

  if (!id)
    goto LABEL_45;
  RndEncJoken = sBtlGetRndEncJoken(id);
  RndEncTbl_t = sBtlGetRndEncTbl_t(id, RndEncJoken);
  if (!sBtlGetRndEncMax(id))
    goto LABEL_45;
  ritu = RndEncTbl_t->ritu;
  v12 = ritu[0];
  if (v12->encountid)
  {
    v13 = v12->ritu;
    v14 = ritu[1];
    if (!v14->encountid)
      goto LABEL_11;
    goto LABEL_10;
  }
  v13 = 0;
  v14 = ritu[1];
  if (v14->encountid)
LABEL_10:
    v13 = (u32)v13 + v14->ritu;
LABEL_11:
  v15 = ritu[2];
  if (v15->encountid)
    v13 = (u32)v13 + v15->ritu;
  v16 = ritu[3];
  if (v16->encountid)
    v13 = (u32)v13 + v16->ritu;
  v17 = ritu[4];
  if (v17->encountid)
    v13 = (u32)v13 + v17->ritu;
  v18 = ritu[5];
  if (v18->encountid)
    v13 = (u32)v13 + v18->ritu;
  v19 = ritu[6];
  if (v19->encountid)
    v13 = (u32)v13 + v19->ritu;
  v20 = ritu[7];
  if (v20->encountid)
    v13 = (u32)v13 + v20->ritu;
  v21 = sub_1905740(v13, 0);
  v22 = RndEncTbl_t->ritu;
  v23 = v22[0];
  encountid = v23->encountid;
  if (!v23->encountid)
  {
    v25 = 0;
    v23 = v22[1];
    encountid = v23->encountid;
    if (!v23->encountid)
      goto LABEL_32;
    goto LABEL_31;
  }
  v25 = v23->ritu;
  if (v21 < v25)
    goto LABEL_44;
  v23 = v22[1];
  encountid = v23->encountid;
  if (v23->encountid)
  {
LABEL_31:
    v25 += v23->ritu;
    if (v25 <= v21)
      goto LABEL_32;
LABEL_44:
    *map = v23->map;
    *floor = v23->floor;
    return encountid;
  }
LABEL_32:
  v23 = v22[2];
  encountid = v23->encountid;
  if (v23->encountid)
  {
    v25 += v23->ritu;
    if (v25 > v21)
      goto LABEL_44;
  }
  v23 = v22[3];
  encountid = v23->encountid;
  if (v23->encountid)
  {
    v25 += v23->ritu;
    if (v25 > v21)
      goto LABEL_44;
  }
  v23 = v22[4];
  encountid = v23->encountid;
  if (v23->encountid)
  {
    v25 += v23->ritu;
    if (v25 > v21)
      goto LABEL_44;
  }
  v23 = v22[5];
  encountid = v23->encountid;
  if (v23->encountid)
  {
    v25 += v23->ritu;
    if (v25 > v21)
      goto LABEL_44;
  }
  v23 = v22[6];
  encountid = v23->encountid;
  if (v23->encountid)
  {
    v25 += v23->ritu;
    if (v25 > v21)
      goto LABEL_44;
  }
  v23 = v22[7];
  encountid = v23->encountid;
  if (v23->encountid)
  {
    if (v25 + v23->ritu > v21)
      goto LABEL_44;
  }
LABEL_45:
  *map = 0;
  *floor = 0;
  return 0;
}

// 0x20c4500
datRndEncRitu_t *sBtlRndEncCalc_Symbol2(s32 dlcIndex, s32 packIndex, s32 tableIndex, s32 *encountIndex) {
  SB_RNDENCPAC *v10;
  datRndEncTbl_t *rndenctbl;
  datRndEncTbl_t *v12;
  datRndEncRitu_t *ritu;
  datRndEncRitu_t *v14;
  s64 v15;
  datRndEncRitu_t *v16;
  datRndEncRitu_t *v17;
  datRndEncRitu_t *v18;
  datRndEncRitu_t *v19;
  datRndEncRitu_t *v20;
  datRndEncRitu_t *v21;
  datRndEncRitu_t *v22;
  s32 v23;
  datRndEncRitu_t *v24;
  s32 v25;
  datRndEncRitu_t *result;
  s32 encountid;

  if ((dlcIndex | packIndex) < 0)
    return 0;
  if (dlcIndex == -1)
    dlcIndex = sBtlGetDlcMapNo();
  v10 = sb_rndencpac[dlcIndex];
  if (SLODWORD(v10->max_length) <= packIndex)
    return 0;
  rndenctbl = v10[packIndex]->rndenctbl;
  if (SLODWORD(rndenctbl->max_length) <= tableIndex)
    return 0;
  v12 = rndenctbl[tableIndex];
  ritu = v12->ritu;
  v14 = ritu[0];
  if (!v14->encountid)
  {
    v15 = 0;
    v16 = ritu[1];
    if (!v16->encountid)
      goto LABEL_14;
    goto LABEL_13;
  }
  v15 = v14->ritu;
  v16 = ritu[1];
  if (v16->encountid)
LABEL_13:
    v15 = (u32)v15 + v16->ritu;
LABEL_14:
  v17 = ritu[2];
  if (v17->encountid)
    v15 = (u32)v15 + v17->ritu;
  v18 = ritu[3];
  if (v18->encountid)
    v15 = (u32)v15 + v18->ritu;
  v19 = ritu[4];
  if (v19->encountid)
    v15 = (u32)v15 + v19->ritu;
  v20 = ritu[5];
  if (v20->encountid)
    v15 = (u32)v15 + v20->ritu;
  v21 = ritu[6];
  if (v21->encountid)
    v15 = (u32)v15 + v21->ritu;
  v22 = ritu[7];
  if (v22->encountid)
    v15 = (u32)v15 + v22->ritu;
  if ((u32)v15)
  {
    v23 = sub_1905740(v15, 0);
    v24 = v12->ritu;
    v25 = v23;
    result = v24[0];
    encountid = result->encountid;
    if (result->encountid)
    {
      encountid = result->ritu;
      if (v25 < encountid)
      {
        *encountIndex = 0;
        return result;
      }
    }
    result = v24[1];
    if (result->encountid)
    {
      encountid += result->ritu;
      if (encountid > v25)
      {
        *encountIndex = 1;
        return result;
      }
    }
    result = v24[2];
    if (result->encountid)
    {
      encountid += result->ritu;
      if (encountid > v25)
      {
        *encountIndex = 2;
        return result;
      }
    }
    result = v24[3];
    if (result->encountid)
    {
      encountid += result->ritu;
      if (encountid > v25)
      {
        *encountIndex = 3;
        return result;
      }
    }
    result = v24[4];
    if (result->encountid)
    {
      encountid += result->ritu;
      if (encountid > v25)
      {
        *encountIndex = 4;
        return result;
      }
    }
    result = v24[5];
    if (result->encountid)
    {
      encountid += result->ritu;
      if (encountid > v25)
      {
        *encountIndex = 5;
        return result;
      }
    }
    result = v24[6];
    if (result->encountid)
    {
      encountid += result->ritu;
      if (encountid > v25)
      {
        *encountIndex = 6;
        return result;
      }
    }
    result = v24[7];
    if (result->encountid)
    {
      if (encountid + result->ritu > v25)
      {
        *encountIndex = 7;
        return result;
      }
    }
  }
  return 0;
}

// 0x20c48f0
s32 sBtlCheckRndEncLevel(s32 tbl) {
  s32 v3;
  s32 v4;
  s64 v5;
  s32 DlcMapNo;
  s64 v9;
  s32 v10;
  s32 v12;
  s32 level;

  if (!tbl)
    return 0;
  v3 = 0;
  v4 = 0;
  v5 = 32;
  do
  {
    DlcMapNo = sBtlGetDlcMapNo();
    v9 = *(s64 *)((char *)&sb_encountpac[DlcMapNo][tbl]->enc1->obj.klass + v5);
    v10 = *(u32 *)(v9 + 16);
    if (v10 == 6 || v10 == 1)
    {
      v12 = *(s16 *)(v9 + 22);
      if (*(u16 *)(v9 + 22))
      {
        ++v4;
        v3 += sBtlGetDevilData(v12, -1)->level;
      }
    }
    v5 += 8;
  }
  while (v5 != 224);
  if (!v4)
    return 0;
  level = GBWK->player->para->level;
  return v3 / v4 + ((char)(level + (((u32)level >> 13) & 3)) >> 2) >= level;
}

// 0x20c4af0
s32 sBtlGetLevelAverage(s32 encountno) {
  s32 DlcMapNo;
  s32 v7;
  s32 v8;
  s64 v9;
  SB_ENCOUNTPAC *v10;
  s64 v11;
  s32 v12;
  s32 v14;

  DlcMapNo = sBtlGetDlcMapNo();
  v7 = 0;
  v8 = 0;
  v9 = 32;
  v10 = sb_encountpac[DlcMapNo][encountno];
  do
  {
    v11 = *(s64 *)((char *)&v10->enc1->obj.klass + v9);
    v12 = *(u32 *)(v11 + 16);
    if (v12 == 6 || v12 == 1)
    {
      v14 = *(s16 *)(v11 + 22);
      if (*(u16 *)(v11 + 22))
      {
        ++v8;
        v7 += sBtlGetDevilData(v14, -1)->level;
      }
    }
    v9 += 8;
  }
  while (v9 != 224);
  if (v8)
    return v7 / v8;
  else
    return 0;
}

// 0x20c4cb0
void sBtlResetRndEncCount(void) {
  *(u64 *)&GBWK->encountkyori = 0;
  encmax = 0;
  return;
}

// 0x20c4d80
void sBtlSetRndEncTopPriorityMap_Symbol(s32 map, s32 floor) {
  g_rndenc1_map = map;
  g_rndenc1_floor = floor;
  return;
}

// 0x20c4e10
void sBtlRndEncTopPriorityMap(s32 *map, s32 *floor) {
  *map = g_rndenc1_map;
  *floor = g_rndenc1_floor;
}

// 0x20c4e90
void sBtlGetDevilInfo(s32 id, SB_RNDENC_DEVILINFO *pDevilInfo) {
  u64 *v5;
  s64 v6;
  u64 *v7;
  void *v8;
  s32 *devil_id;
  s32 RndEncJoken;
  datRndEncTbl_t *RndEncTbl_t;
  s64 v14;
  u32 v15;
  s64 v16;
  s64 v17;
  s64 v18;
  s64 v19;
  s64 v20;
  s64 v21;
  s64 v22;
  s64 v23;
  s64 v24;
  s64 v25;
  s64 v26;
  s64 v27;
  s64 v28;
  s64 v29;
  s64 v30;
  s64 v31;
  s64 v32;
  s64 v33;
  s64 v34;
  s64 v35;
  s64 v36;
  s64 v37;
  s64 v38;
  s64 v39;
  s64 v40;
  s64 v41;
  s64 v42;
  s64 v43;
  s64 v44;
  s64 v45;
  s64 v46;
  s64 v47;
  datRndEncRitu_t *v48;
  s32 DlcMapNo;
  s64 v52;
  SB_ENCOUNT1 *enc1;
  u64 *v54;
  s32 ritu;
  s64 v56;
  SB_ENCOUNT1 *v57;
  s32 devil;
  s64 v59;
  char v60;
  s64 v61;
  bool v62;
  s64 v64;
  s32 *v65;
  s64 v66;
  s64 v67;
  s32 v68;
  s32 v69;
  s32 v70;
  s32 v71;
  s64 *v72;
  s64 v73;
  s64 v74;
  s64 v75;
  s64 v76;
  s64 v77;
  s64 v78;
  s64 v79;
  u64 *v80;
  s64 v81;
  s64 *v82;
  s64 v83;
  s64 v84;
  s32 v85;
  s32 v86;
  u64 *v87;
  s64 v88;
  s64 v89;
  s64 v90;
  s32 v91;
  s32 v92;
  s32 v93;
  s32 v94;
  s64 *v95;
  s64 v96;
  s64 v97;
  s64 v98;
  s64 v99;
  s64 v100;
  s64 v101;
  s64 v102;
  u64 *v103;
  s64 v104;
  s64 *v105;
  s64 v106;
  s64 v107;
  s32 v108;
  s32 v109;
  u64 *v110;
  s64 v111;
  s64 v112;
  s64 v113;
  s32 v114;
  s32 v115;
  s32 v116;
  s32 v117;
  s64 *v118;
  s64 v119;
  s64 v120;
  s64 v121;
  s64 v122;
  s64 v123;
  s64 v124;
  s64 v125;
  u64 *v126;
  s64 v127;
  s64 *v128;
  s64 v129;
  s64 v130;
  s32 v131;
  s32 v132;
  u64 *i;
  s64 v134;
  SB_RNDENC_DEVILINFO *v135;

  v5 = NewSpecific(int__, 0x40u);
  v6 = 0;
  v7 = v5 + 4;
  do
  {
    v8 = NewSpecific(s32, 2u);
    v7[v6] = v8;
  }
  while (v6 != 64);
  devil_id = pDevilInfo->devil_id;
  *(u64 *)devil_id = 0;
  devil_id[2] = 0;
  pDevilInfo->num = 0;
  if (!id)
    return;
  v135 = pDevilInfo;
  RndEncJoken = sBtlGetRndEncJoken(id);
  RndEncTbl_t = sBtlGetRndEncTbl_t(id, RndEncJoken);
  v14 = 0;
  v15 = 0;
  *(u64 *)(v5[4] + 32) = 0;
  v16 = v5[6];
  *(u64 *)(v5[5] + 32) = 0;
  *(u64 *)(v16 + 32) = 0;
  v17 = v5[8];
  *(u64 *)(v5[7] + 32) = 0;
  *(u64 *)(v17 + 32) = 0;
  v18 = v5[10];
  *(u64 *)(v5[9] + 32) = 0;
  *(u64 *)(v18 + 32) = 0;
  v19 = v5[12];
  *(u64 *)(v5[11] + 32) = 0;
  *(u64 *)(v19 + 32) = 0;
  v20 = v5[14];
  *(u64 *)(v5[13] + 32) = 0;
  *(u64 *)(v20 + 32) = 0;
  v21 = v5[16];
  *(u64 *)(v5[15] + 32) = 0;
  *(u64 *)(v21 + 32) = 0;
  v22 = v5[18];
  *(u64 *)(v5[17] + 32) = 0;
  *(u64 *)(v22 + 32) = 0;
  v23 = v5[20];
  *(u64 *)(v5[19] + 32) = 0;
  *(u64 *)(v23 + 32) = 0;
  v24 = v5[22];
  *(u64 *)(v5[21] + 32) = 0;
  *(u64 *)(v24 + 32) = 0;
  v25 = v5[24];
  *(u64 *)(v5[23] + 32) = 0;
  *(u64 *)(v25 + 32) = 0;
  v26 = v5[26];
  *(u64 *)(v5[25] + 32) = 0;
  *(u64 *)(v26 + 32) = 0;
  v27 = v5[28];
  *(u64 *)(v5[27] + 32) = 0;
  *(u64 *)(v27 + 32) = 0;
  v28 = v5[30];
  *(u64 *)(v5[29] + 32) = 0;
  *(u64 *)(v28 + 32) = 0;
  v29 = v5[32];
  *(u64 *)(v5[31] + 32) = 0;
  *(u64 *)(v29 + 32) = 0;
  v30 = v5[34];
  *(u64 *)(v5[33] + 32) = 0;
  *(u64 *)(v30 + 32) = 0;
  v31 = v5[36];
  *(u64 *)(v5[35] + 32) = 0;
  *(u64 *)(v31 + 32) = 0;
  v32 = v5[38];
  *(u64 *)(v5[37] + 32) = 0;
  *(u64 *)(v32 + 32) = 0;
  v33 = v5[40];
  *(u64 *)(v5[39] + 32) = 0;
  *(u64 *)(v33 + 32) = 0;
  v34 = v5[42];
  *(u64 *)(v5[41] + 32) = 0;
  *(u64 *)(v34 + 32) = 0;
  v35 = v5[44];
  *(u64 *)(v5[43] + 32) = 0;
  *(u64 *)(v35 + 32) = 0;
  v36 = v5[46];
  *(u64 *)(v5[45] + 32) = 0;
  *(u64 *)(v36 + 32) = 0;
  v37 = v5[48];
  *(u64 *)(v5[47] + 32) = 0;
  *(u64 *)(v37 + 32) = 0;
  v38 = v5[50];
  *(u64 *)(v5[49] + 32) = 0;
  *(u64 *)(v38 + 32) = 0;
  v39 = v5[52];
  *(u64 *)(v5[51] + 32) = 0;
  *(u64 *)(v39 + 32) = 0;
  v40 = v5[54];
  *(u64 *)(v5[53] + 32) = 0;
  *(u64 *)(v40 + 32) = 0;
  v41 = v5[56];
  *(u64 *)(v5[55] + 32) = 0;
  *(u64 *)(v41 + 32) = 0;
  v42 = v5[58];
  *(u64 *)(v5[57] + 32) = 0;
  *(u64 *)(v42 + 32) = 0;
  v43 = v5[60];
  *(u64 *)(v5[59] + 32) = 0;
  *(u64 *)(v43 + 32) = 0;
  v44 = v5[62];
  *(u64 *)(v5[61] + 32) = 0;
  *(u64 *)(v44 + 32) = 0;
  v45 = v5[64];
  *(u64 *)(v5[63] + 32) = 0;
  *(u64 *)(v45 + 32) = 0;
  v46 = v5[66];
  *(u64 *)(v5[65] + 32) = 0;
  v47 = v5[67];
  *(u64 *)(v46 + 32) = 0;
  *(u64 *)(v47 + 32) = 0;
  while (2)
  {
    while (1)
    {
      v48 = RndEncTbl_t->ritu[v14];
      if (!v48->encountid || !v48->ritu)
        break;
      DlcMapNo = sBtlGetDlcMapNo();
      v52 = 0;
      enc1 = sb_encountpac[DlcMapNo][v48->encountid]->enc1;
      while (1)
      {
        v57 = enc1[v52];
        if (!v57->type)
          goto LABEL_18;
        devil = (u16)v57->devil;
        if (devil == 214)
        {
          devil = 126;
          if ((s32)v15 < 1)
            goto LABEL_17;
        }
        else if (devil == 218)
        {
          devil = 217;
          if ((s32)v15 < 1)
            goto LABEL_17;
        }
        else
        {
          devil = (s16)devil;
          if ((u32)((s16)devil - 285) >= 0xFFFFFFFE)
            devil = 282;
          if ((s32)v15 < 1)
            goto LABEL_17;
        }
        v59 = 0;
        v60 = 0;
        do
        {
          while (1)
          {
            v61 = v5[v59 + 4];
            if (*(u32 *)(v61 + 32) != devil)
              break;
            v62 = v15 - 1 == v59++;
            *(u32 *)(v61 + 36) += v48->ritu;
            v60 = 1;
            if (v62)
              goto LABEL_18;
          }
          ++v59;
        }
        while (v15 != v59);
        if ((v60 & 1) != 0)
          goto LABEL_18;
LABEL_17:
        v54 = &v5[v15];
        ritu = v48->ritu;
        ++v15;
        v56 = v54[4];
        *(u32 *)(v56 + 32) = devil;
        *(u32 *)(v56 + 36) = ritu;
        if (v15 == 64)
          break;
LABEL_18:
        if (++v52 == 24)
          goto LABEL_9;
      }
      if (++v14 == 8)
      {
LABEL_45:
        v64 = v15;
        v135->num = 3;
        v67 = v15 & 0x7FFFFFFC;
        v68 = 0;
        v69 = 0;
        v70 = 0;
        v71 = 0;
        v72 = v5 + 7;
        v73 = v15 & 0xFFFFFFFC;
        do
        {
          v74 = *(v72 - 3);
          v75 = *(v72 - 2);
          v73 -= 4;
          v76 = *(v72 - 1);
          v77 = *v72;
          v72 += 4;
          v68 += *(u32 *)(v74 + 36);
          v69 += *(u32 *)(v75 + 36);
          v70 += *(u32 *)(v76 + 36);
          v71 += *(u32 *)(v77 + 36);
        }
        while (v73);
        v78 = (u32)(v71 + v70 + v69 + v68);
        if (v67 != v15)
        {
          v79 = ~v67;
          if ((v15 & 1) != 0)
          {
            v80 = &v5[v67];
            v67 |= 1u;
            v78 = (u32)(*(u32 *)(v80[4] + 36) + v78);
          }
          if (v79 + v15)
          {
            v81 = v15 - v67;
            v82 = &v5[v67 + 5];
            do
            {
              v83 = *(v82 - 1);
              v84 = *v82;
              v81 -= 2;
              v82 += 2;
              v78 = (u32)(*(u32 *)(v84 + 36) + *(u32 *)(v83 + 36) + v78);
            }
            while (v81);
          }
        }
        v85 = sub_1905740(v78, 0);
        v86 = 0;
        v87 = v5 + 4;
        v88 = v15;
        while (1)
        {
          v89 = *v87;
          v86 += *(u32 *)(*v87 + 36);
          if (v86 > v85)
            break;
          ++v87;
          if (!--v88)
            goto LABEL_59;
        }
        v135->devil_id[0] = *(u32 *)(v89 + 32);
        *(u32 *)(v89 + 36) = 0;
LABEL_59:
        v90 = v15 & 0x7FFFFFFC;
        v91 = 0;
        v92 = 0;
        v93 = 0;
        v94 = 0;
        v95 = v5 + 7;
        v96 = v15 & 0xFFFFFFFC;
        do
        {
          v97 = *(v95 - 3);
          v98 = *(v95 - 2);
          v96 -= 4;
          v99 = *(v95 - 1);
          v100 = *v95;
          v95 += 4;
          v91 += *(u32 *)(v97 + 36);
          v92 += *(u32 *)(v98 + 36);
          v93 += *(u32 *)(v99 + 36);
          v94 += *(u32 *)(v100 + 36);
        }
        while (v96);
        v101 = (u32)(v94 + v93 + v92 + v91);
        if (v90 != v15)
        {
          v102 = ~v90;
          if ((v15 & 1) != 0)
          {
            v103 = &v5[v90];
            v90 |= 1u;
            v101 = (u32)(*(u32 *)(v103[4] + 36) + v101);
          }
          if (v102 + v15)
          {
            v104 = v15 - v90;
            v105 = &v5[v90 + 5];
            do
            {
              v106 = *(v105 - 1);
              v107 = *v105;
              v104 -= 2;
              v105 += 2;
              v101 = (u32)(*(u32 *)(v107 + 36) + *(u32 *)(v106 + 36) + v101);
            }
            while (v104);
          }
        }
        v108 = sub_1905740(v101, 0);
        v109 = 0;
        v110 = v5 + 4;
        v111 = v15;
        while (1)
        {
          v112 = *v110;
          v109 += *(u32 *)(*v110 + 36);
          if (v109 > v108)
            break;
          --v111;
          ++v110;
          if (!v111)
            goto LABEL_72;
        }
        v135->devil_id[1] = *(u32 *)(v112 + 32);
        *(u32 *)(v112 + 36) = 0;
LABEL_72:
        v113 = v15 & 0x7FFFFFFC;
        v114 = 0;
        v115 = 0;
        v116 = 0;
        v117 = 0;
        v118 = v5 + 7;
        v119 = v15 & 0xFFFFFFFC;
        do
        {
          v120 = *(v118 - 3);
          v121 = *(v118 - 2);
          v119 -= 4;
          v122 = *(v118 - 1);
          v123 = *v118;
          v118 += 4;
          v114 += *(u32 *)(v120 + 36);
          v115 += *(u32 *)(v121 + 36);
          v116 += *(u32 *)(v122 + 36);
          v117 += *(u32 *)(v123 + 36);
        }
        while (v119);
        v124 = (u32)(v117 + v116 + v115 + v114);
        if (v113 != v15)
        {
          v125 = ~v113;
          if ((v15 & 1) != 0)
          {
            v126 = &v5[v113];
            v113 |= 1u;
            v124 = (u32)(*(u32 *)(v126[4] + 36) + v124);
          }
          if (v125 + v15)
          {
            v127 = v15 - v113;
            v128 = &v5[v113 + 5];
            do
            {
              v129 = *(v128 - 1);
              v130 = *v128;
              v127 -= 2;
              v128 += 2;
              v124 = (u32)(*(u32 *)(v130 + 36) + *(u32 *)(v129 + 36) + v124);
            }
            while (v127);
          }
        }
        v131 = sub_1905740(v124, 0);
        v132 = 0;
        for (i = v5 + 4; ; ++i)
        {
          v134 = *i;
          v132 += *(u32 *)(*i + 36);
          if (v132 > v131)
            break;
          if (!--v64)
            return;
        }
        v135->devil_id[2] = *(u32 *)(v134 + 32);
        *(u32 *)(v134 + 36) = 0;
        return;
      }
    }
LABEL_9:
    if (++v14 != 8)
      continue;
    break;
  }
  if ((s32)v15 > 3)
    goto LABEL_45;
  v135->num = v15;
  v65 = v135->devil_id;
  v66 = v5[5];
  v65[0] = *(u32 *)(v5[4] + 32);
  v65[1] = *(u32 *)(v66 + 32);
  v65[2] = *(u32 *)(v5[6] + 32);
}

// 0x20c56e0
s32 sBtlGetEncountDevil1_Lv(s32 encountno) {
  s32 DlcMapNo;
  s32 v7;
  s64 v8;
  s64 v9;
  s32 v10;
  s64 v11;
  s32 level;
  s64 v13;
  s32 v14;
  s32 v16;

  DlcMapNo = sBtlGetDlcMapNo();
  v7 = 0;
  v8 = 32;
  v9 = (s64)sb_encountpac[DlcMapNo] + 8 * encountno;
  v10 = -1;
  v11 = *(u64 *)(v9 + 32);
  do
  {
    v13 = *(u64 *)(*(u64 *)(v11 + 104) + v8);
    v14 = *(u32 *)(v13 + 16);
    if (v14 == 6 || v14 == 1)
    {
      v16 = *(s16 *)(v13 + 22);
      if (*(u16 *)(v13 + 22))
      {
        level = sBtlGetDevilData(v16, -1)->level;
        if (v7 < level)
          v10 = v16;
        if (v7 <= level)
          v7 = level;
      }
    }
    v8 += 8;
  }
  while (v8 != 224);
  return v10;
}

// 0x20c5880
s32 sBtlGetEncountDevilMaxLv(s32 encountno, s32 dlcID) {
  s32 v7;
  s64 v8;
  SB_ENCOUNTPAC *v9;
  s32 level;
  s64 v11;
  s32 v12;

  if (dlcID == -1)
    dlcID = sBtlGetDlcMapNo();
  v7 = 0;
  v8 = 32;
  v9 = sb_encountpac[dlcID][encountno];
  do
  {
    v11 = *(s64 *)((char *)&v9->enc1->obj.klass + v8);
    v12 = *(s16 *)(v11 + 22);
    if (*(u16 *)(v11 + 22))
    {
      level = sBtlGetDevilData(v12, encountno)->level;
      if (v7 <= level)
        v7 = level;
    }
    v8 += 8;
  }
  while (v8 != 224);
  return v7;
}

// 0x20c5a10
s32 sBtlGetDevilNum(s32 id, s32 devilid) {
  s32 RndEncJoken;
  datRndEncTbl_t *RndEncTbl_t;
  s64 v8;
  s64 v9;
  s32 DlcMapNo;
  SB_ENCOUNT1 *enc1;
  SB_ENCOUNT1 *v14;
  SB_ENCOUNT1 *v15;
  SB_ENCOUNT1 *v16;
  SB_ENCOUNT1 *v17;
  SB_ENCOUNT1 *v18;
  SB_ENCOUNT1 *v19;
  SB_ENCOUNT1 *v20;
  SB_ENCOUNT1 *v21;
  SB_ENCOUNT1 *v22;
  SB_ENCOUNT1 *v23;
  SB_ENCOUNT1 *v24;
  SB_ENCOUNT1 *v25;
  SB_ENCOUNT1 *v26;
  SB_ENCOUNT1 *v27;
  SB_ENCOUNT1 *v28;
  SB_ENCOUNT1 *v29;
  SB_ENCOUNT1 *v30;
  SB_ENCOUNT1 *v31;
  SB_ENCOUNT1 *v32;
  SB_ENCOUNT1 *v33;
  SB_ENCOUNT1 *v34;
  SB_ENCOUNT1 *v35;
  SB_ENCOUNT1 *v36;
  SB_ENCOUNT1 *v37;

  if (id)
  {
    RndEncJoken = sBtlGetRndEncJoken(id);
    RndEncTbl_t = sBtlGetRndEncTbl_t(id, RndEncJoken);
    id = 0;
    v8 = 32;
    while (1)
    {
      v9 = *(s64 *)((char *)&RndEncTbl_t->ritu->obj.klass + v8);
      if (*(u16 *)(v9 + 16))
      {
        if (*(u16 *)(v9 + 18))
          break;
      }
LABEL_7:
      v8 += 8;
      if (v8 == 96)
        return id;
    }
    DlcMapNo = sBtlGetDlcMapNo();
    enc1 = sb_encountpac[DlcMapNo][*(u16 *)(v9 + 16)]->enc1;
    v14 = enc1[0];
    if (v14->type && v14->devil == devilid)
      ++id;
    v15 = enc1[1];
    if (v15->type && v15->devil == devilid)
      ++id;
    v16 = enc1[2];
    if (v16->type && v16->devil == devilid)
      ++id;
    v17 = enc1[3];
    if (v17->type && v17->devil == devilid)
      ++id;
    v18 = enc1[4];
    if (v18->type && v18->devil == devilid)
      ++id;
    v19 = enc1[5];
    if (v19->type && v19->devil == devilid)
      ++id;
    v20 = enc1[6];
    if (v20->type && v20->devil == devilid)
      ++id;
    v21 = enc1[7];
    if (v21->type && v21->devil == devilid)
      ++id;
    v22 = enc1[8];
    if (v22->type && v22->devil == devilid)
      ++id;
    v23 = enc1[9];
    if (v23->type && v23->devil == devilid)
      ++id;
    v24 = enc1[10];
    if (v24->type && v24->devil == devilid)
      ++id;
    v25 = enc1[11];
    if (v25->type && v25->devil == devilid)
      ++id;
    v26 = enc1[12];
    if (v26->type && v26->devil == devilid)
      ++id;
    v27 = enc1[13];
    if (v27->type && v27->devil == devilid)
      ++id;
    v28 = enc1[14];
    if (v28->type && v28->devil == devilid)
      ++id;
    v29 = enc1[15];
    if (v29->type && v29->devil == devilid)
      ++id;
    v30 = enc1[16];
    if (v30->type && v30->devil == devilid)
      ++id;
    v31 = enc1[17];
    if (v31->type && v31->devil == devilid)
      ++id;
    v32 = enc1[18];
    if (v32->type && v32->devil == devilid)
      ++id;
    v33 = enc1[19];
    if (v33->type && v33->devil == devilid)
      ++id;
    v34 = enc1[20];
    if (v34->type && v34->devil == devilid)
      ++id;
    v35 = enc1[21];
    if (v35->type && v35->devil == devilid)
      ++id;
    v36 = enc1[22];
    if (v36->type && v36->devil == devilid)
      ++id;
    v37 = enc1[23];
    if (v37->type && v37->devil == devilid)
      ++id;
    goto LABEL_7;
  }
  return id;
}

// 0x20c5dd0
s32 sBtlChkUnkui(s32 id) {
  return 0;
}

// 0x20c5de0
s32 sBtlGetMusiEncountID(s32 rnd_encid) {
  s16 *v3;
  s64 v5;
  s32 RndEncJoken;
  datRndEncTbl_t *RndEncTbl_t;
  s64 i;
  s64 v10;

  v3 = NewSpecific(s16, 0x10u);
  if (rnd_encid)
  {
    v5 = v3;
    RndEncJoken = sBtlGetRndEncJoken(rnd_encid);
    RndEncTbl_t = sBtlGetRndEncTbl_t(rnd_encid, RndEncJoken);
    *(_OWORD *)(v5 + 32) = 0u;
    *(_OWORD *)(v5 + 48) = 0u;
    for (i = 32; i != 96; i += 8)
    {
      v10 = *(s64 *)((char *)&RndEncTbl_t->ritu->obj.klass + i);
      if (!*(u16 *)(v10 + 16) || !*(u16 *)(v10 + 18))
        continue;
      sBtlGetDlcMapNo();
      continue;
    }
  }
  return 0;
}

// 0x20c5f40
s32 sBtlRndEncCalcKirestu(s32 id, f32 length) {
  s32 RndEncJoken;
  datRndEncTbl_t *RndEncTbl_t;
  f32 encountkyori;
  f32 v10;
  datRndEncRitu_t *ritu;
  datRndEncRitu_t *v12;
  s64 v13;
  datRndEncRitu_t *v14;
  datRndEncRitu_t *v15;
  datRndEncRitu_t *v16;
  datRndEncRitu_t *v17;
  datRndEncRitu_t *v18;
  datRndEncRitu_t *v19;
  datRndEncRitu_t *v20;
  s32 v21;
  datRndEncRitu_t *v22;
  datRndEncRitu_t *v23;
  s32 encountid;
  s32 v25;
  s32 map;
  s32 floor;

  RndEncJoken = sBtlGetRndEncJoken(id);
  RndEncTbl_t = sBtlGetRndEncTbl_t(id, RndEncJoken);
  encountkyori = GBWK->encountkyori;
  v10 = (f32)(s32)(f32)(encountkyori / 100.0) * 100.0;
  if ((f32)(encountkyori / 100.0) == INFINITY)
    v10 = -214748360000.0;
  GBWK->encountkyori = encountkyori - v10;
  ritu = RndEncTbl_t->ritu;
  v12 = ritu[0];
  if (v12->encountid)
  {
    v13 = v12->ritu;
    v14 = ritu[1];
    if (!v14->encountid)
      goto LABEL_12;
    goto LABEL_11;
  }
  v13 = 0;
  v14 = ritu[1];
  if (v14->encountid)
LABEL_11:
    v13 = (u32)v13 + v14->ritu;
LABEL_12:
  v15 = ritu[2];
  if (v15->encountid)
    v13 = (u32)v13 + v15->ritu;
  v16 = ritu[3];
  if (v16->encountid)
    v13 = (u32)v13 + v16->ritu;
  v17 = ritu[4];
  if (v17->encountid)
    v13 = (u32)v13 + v17->ritu;
  v18 = ritu[5];
  if (v18->encountid)
    v13 = (u32)v13 + v18->ritu;
  v19 = ritu[6];
  if (v19->encountid)
    v13 = (u32)v13 + v19->ritu;
  v20 = ritu[7];
  if (v20->encountid)
    v13 = (u32)v13 + v20->ritu;
  v21 = sub_1905740(v13, 0);
  v22 = RndEncTbl_t->ritu;
  v23 = v22[0];
  encountid = v23->encountid;
  if (v23->encountid)
  {
    v25 = v23->ritu;
    if (v21 < v25)
      goto LABEL_44;
    v23 = v22[1];
    encountid = v23->encountid;
    if (!v23->encountid)
      goto LABEL_32;
  }
  else
  {
    v25 = 0;
    v23 = v22[1];
    encountid = v23->encountid;
    if (!v23->encountid)
      goto LABEL_32;
  }
  v25 += v23->ritu;
  if (v25 > v21)
    goto LABEL_44;
LABEL_32:
  v23 = v22[2];
  encountid = v23->encountid;
  if (v23->encountid)
  {
    v25 += v23->ritu;
    if (v25 > v21)
      goto LABEL_44;
  }
  v23 = v22[3];
  encountid = v23->encountid;
  if (v23->encountid)
  {
    v25 += v23->ritu;
    if (v25 > v21)
      goto LABEL_44;
  }
  v23 = v22[4];
  encountid = v23->encountid;
  if (v23->encountid)
  {
    v25 += v23->ritu;
    if (v25 > v21)
      goto LABEL_44;
  }
  v23 = v22[5];
  encountid = v23->encountid;
  if (v23->encountid)
  {
    v25 += v23->ritu;
    if (v25 > v21)
      goto LABEL_44;
  }
  v23 = v22[6];
  encountid = v23->encountid;
  if (v23->encountid)
  {
    v25 += v23->ritu;
    if (v25 > v21)
      goto LABEL_44;
  }
  v23 = v22[7];
  encountid = v23->encountid;
  if (!v23->encountid)
    return encountid;
  if (v25 + v23->ritu > v21)
  {
LABEL_44:
    map = v23->map;
    floor = v23->floor;
    g_rndenc1_map = map;
    g_rndenc1_floor = floor;
    GBWK->fix_encountflg = 3;
    return encountid;
  }
  return 0;
}

// 0x20c39d0
static s32 GetRandomNumMax(datRndEncTbl_t *prndenc) {
  datRndEncRitu_t *ritu;
  datRndEncRitu_t *v3;
  s32 result;
  datRndEncRitu_t *v5;
  datRndEncRitu_t *v6;
  datRndEncRitu_t *v7;
  datRndEncRitu_t *v8;
  datRndEncRitu_t *v9;
  datRndEncRitu_t *v10;
  datRndEncRitu_t *v11;

  ritu = prndenc->ritu;
  v3 = ritu[0];
  if (v3->encountid)
  {
    result = v3->ritu;
    v5 = ritu[1];
    if (!v5->encountid)
      goto LABEL_4;
    goto LABEL_3;
  }
  result = 0;
  v5 = ritu[1];
  if (v5->encountid)
LABEL_3:
    result += v5->ritu;
LABEL_4:
  v6 = ritu[2];
  if (v6->encountid)
    result += v6->ritu;
  v7 = ritu[3];
  if (v7->encountid)
    result += v7->ritu;
  v8 = ritu[4];
  if (v8->encountid)
    result += v8->ritu;
  v9 = ritu[5];
  if (v9->encountid)
    result += v9->ritu;
  v10 = ritu[6];
  if (v10->encountid)
    result += v10->ritu;
  v11 = ritu[7];
  if (v11->encountid)
    result += v11->ritu;
  return result;
}
