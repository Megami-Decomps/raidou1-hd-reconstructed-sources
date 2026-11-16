#include "types.h"
#include "configaudio.h"
#include "file.h"
#include "sbtlsound.h"
#include "sndat3.h"

typedef struct fileHandle_t fileHandle_t;

void *BgmTbl;
void *SeTbl;
void *SiboTbl;
s16 *at3_bgm_out;
static void *at3_bgm_mng_param;
static void *at3_bgm_info;
s16 *at3_se_out;
static void *at3_se_mng_param;
static void *at3_se_info;
s16 *at3_swapbgm_out;
static void *at3_swapbgm_mng_param;
static void *at3_swapbgm_info;
s16 *at3_outbuf;
s16 *at3_zerobuf;
static u16 *at3_swapbuf;
static s32 swap_next_bgm_id;
static s32 swap_step;
static u16 *at3_continue_buff;
static s32 at3_flag;
static s32 at3_dma_flag;
static s32 at3_bgm_fadein_speed;
static s32 at3_bgm_fade_speed;
static s32 at3_se_fade_speed;
s32 at3_bgm_nowloadid;
static s32 at3_bgm_nowplayid;
static s32 at3_bgm_skip;
s32 at3_bgm_request_flag;
static s32 at3_bgm_voldown_flag;
static s32 at3_se_id;
static fileHandle_t *fh_at3_bgm_load;
static fileHandle_t *fh_at3_se_load;
static s32 sndAt3Calc_cnt;
static s32 sndAt3Calc_cnt2;
static s32 sndAt3Calc_cnt3;
static s32 sndAt3Calc_cnt4;

static s32 BgmStatus_NoSema(void);
static void BgmFree_NoSema(void);
static void SeStop_NoSema(void);
static void SeFree_NoSema(void);
static void Calc(void);
static void File_Init(char **fname, void *param);
static void File_BgmLoadStart(char **fname);
static s32 File_BgmLoadChk(void *param);
static void BgmPlaySub(s32 id, f32 volume, s64 startTimeMs);
static void File_SeLoadStart(char **fname);
static s32 File_SeLoadChk(void *param);
static s32 SeStatus_NoSema(void);
static void SwapCopy(void);
static s32 SwapStatus(void);

// 0x21e4fa0
s32 sndNameToID_AT3SE(char *name) {
  s64 v3;
  s32 v4;

  v3 = 0;
  v4 = -1;
  while (1)
  {
    if (v3 >= SLODWORD(SeTbl->max_length))
      return v4;
    if (Equals_54828784(name, SeTbl[v3]->fname, 0))
      return v3;
    ++v3;
  }
}

// 0x21e5070
static s32 BgmStatus_NoSema(void) {
  s32 status;
  u32 v6;

  if (at3_bgm_mng_param->status != 1)
  {
    goto LABEL_5;
  }
  at3_bgm_mng_param->sucount = 0;
  if (v6)
  at3_bgm_mng_param->status = 2;
LABEL_5:
  if (at3_bgm_skip == 1)
    return 2;
  status = at3_bgm_mng_param->status;
  if ((status & 0xFFFFFFFC) == 4)
    return 3;
  return status;
}

// 0x21e52c0
static void BgmFree_NoSema(void) {
  void *at3_bgm_mng_param_local;
  void *v6;

  at3_bgm_mng_param_local = at3_bgm_mng_param;
  at3_bgm_mng_param_local->p_pcmout = at3_zerobuf;
  at3_bgm_mng_param_local = ((char *)at3_bgm_mng_param_local + 40);
  *((u8 *)&at3_bgm_mng_param_local[-1].tbl_idx + 4) = 0;
  v6 = at3_bgm_mng_param;
  at3_bgm_skip = 0;
  v6->status = 0;
  *(u64 *)&at3_bgm_nowloadid = -1;
}

// 0x21e5350
static void SeStop_NoSema(void) {
  at3_se_mng_param->sucount = 0;
  at3_se_mng_param->play_mode = 2;
}

// 0x21e53c0
static void SeFree_NoSema(void) {
  ;
}

// 0x21e53d0
static void Calc(void) {
  int32x2_t *static_fields;
  u64 v3;
  u64 v4;
  u64 v5;
  u64 v7;
  u64 v10;
  void *v13;
  void *v14;
  void *v16;
  void *v19;
  void *v24;
  void *v25;
  void *v30;
  void *v31;
  void *v33;
  void *v37;
  u32 v38;
  void *v40;
  s16 *v41;
  void *v43;
  s32 sunum;
  s32 v45;
  s32 suloop;
  u32 v47;
  void *v49;
  void *v53;
  s32 v54;
  s32 v55;
  void *v57;
  void *v63;
  s32 v64;
  s32 v65;
  s16 *v68;

  v3 = vadd_s32(static_fields[25], (int32x2_t)0x100000001LL).n64_u64[0];
  ++static_fields[26].n64_u32[0];
  v4 = static_fields[4].n64_u64[0];
  static_fields[25].n64_u64[0] = v3;
  if (*(u32 *)(v4 + 32) != 1)
  {
LABEL_18:
    goto LABEL_19;
  }
  if (*(u32 *)(v4 + 56) != 5)
    goto LABEL_18;
  v5 = static_fields[5].n64_u64[0];
  if (*(u32 *)(v5 + 48))
  {
    if ((signed s32)static_fields[25].n64_u32[1] >= (signed s32)static_fields[18].n64_u32[0])
    {
      v7 = static_fields[5].n64_u64[0];
      static_fields[25].n64_u32[1] = 0;
      --*(u32 *)(v7 + 48);
    }
    goto LABEL_18;
  }
  v5 = static_fields[5].n64_u64[0];
  v10 = static_fields[4].n64_u64[0];
  *(u32 *)(v5 + 48) = 0;
  *(u32 *)(v10 + 56) = 3;
LABEL_19:
  if (at3_bgm_mng_param->play_mode != 1)
    goto LABEL_46;
  if (at3_bgm_mng_param->status != 4)
    goto LABEL_46;
  if (at3_bgm_info->minusvol <= 0x1E)
  {
    if (sndAt3Calc_cnt >= at3_bgm_fade_speed)
    {
      v13 = at3_bgm_info;
      sndAt3Calc_cnt = 0;
      ++v13->minusvol;
    }
    goto LABEL_46;
  }
  v14 = at3_bgm_mng_param;
  at3_bgm_info->minusvol = 0;
  v14->play_mode = 2;
  v14->sucount = 0;
  v16 = at3_bgm_mng_param;
  v16->p_pcmout = at3_zerobuf;
  v16 = ((char *)v16 + 40);
  *((u8 *)&v16[-1].tbl_idx + 4) = 0;
  v19 = at3_bgm_mng_param;
  at3_bgm_skip = 0;
  v19->status = 0;
  *(u64 *)&at3_bgm_nowloadid = -1;
LABEL_46:
  if (at3_swapbgm_mng_param->play_mode != 1)
    goto LABEL_66;
  if (at3_swapbgm_mng_param->status != 6)
    goto LABEL_66;
  if (at3_swapbgm_info->minusvol <= 0x1E)
  {
    if (sndAt3Calc_cnt >= at3_bgm_fade_speed)
    {
      v24 = at3_swapbgm_info;
      sndAt3Calc_cnt = 0;
      ++v24->minusvol;
    }
    goto LABEL_66;
  }
  v25 = at3_swapbgm_mng_param;
  at3_swapbgm_info->minusvol = 0;
  v25->play_mode = 2;
  v25->sucount = 0;
LABEL_66:
  if (at3_se_mng_param->play_mode != 1)
    goto LABEL_86;
  if (at3_se_mng_param->status != 4)
    goto LABEL_86;
  if (at3_se_info->minusvol <= 0x1E)
  {
    if (sndAt3Calc_cnt3 >= at3_se_fade_speed)
    {
      v30 = at3_se_info;
      sndAt3Calc_cnt3 = 0;
      ++v30->minusvol;
    }
    goto LABEL_86;
  }
  v31 = at3_se_mng_param;
  at3_se_info->minusvol = 0;
  v31->play_mode = 2;
  v31->sucount = 0;
LABEL_86:
  v33 = at3_bgm_mng_param;
  if (v33->play_mode)
  {
    goto LABEL_89;
  }
  at3_flag = 1;
  v33->play_mode = 1;
LABEL_89:
  if (!at3_flag)
    goto LABEL_120;
  v37 = at3_bgm_mng_param;
  if (v37->play_mode != 1)
    goto LABEL_120;
  if (v37->status == 7)
  {
    if (v38)
    {
LABEL_105:
      v37->sucount = 0;
      v37->play_mode = 2;
      v40 = at3_bgm_mng_param;
      v41 = at3_zerobuf;
      v40->p_pcmout = v41;
      v40 = ((char *)v40 + 40);
      *((u8 *)&v40[-1].tbl_idx + 4) = 0;
      v43 = at3_bgm_mng_param;
      at3_bgm_skip = 0;
      v43->status = 0;
      *(u64 *)&at3_bgm_nowloadid = -1;
      goto LABEL_120;
    }
LABEL_104:
    v37 = at3_bgm_mng_param;
    goto LABEL_105;
  }
  if (!v38)
  {
    v37 = at3_bgm_mng_param;
  }
  sunum = v37->sunum;
  v45 = v37->sucount + 1;
  v37->sucount = v45;
  if (v45 >= sunum)
  {
    v37 = at3_bgm_mng_param;
    suloop = v37->suloop;
    if (suloop == -1)
    {
      if (v47)
        goto LABEL_105;
      goto LABEL_104;
    }
    if (!v47)
    {
      v37 = at3_bgm_mng_param;
      suloop = v37->suloop;
    }
    v37->sucount = suloop;
  }
LABEL_120:
  v49 = at3_se_mng_param;
  if (v49->play_mode)
  {
    goto LABEL_123;
  }
  at3_flag = 1;
  v49->play_mode = 1;
LABEL_123:
  if (!at3_flag)
    goto LABEL_137;
  v53 = at3_se_mng_param;
  if (v53->play_mode != 1)
  {
LABEL_137:
    goto LABEL_138;
  }
  v54 = v53->sunum;
  v55 = v53->sucount + 1;
  v53->sucount = v55;
  if (v55 < v54)
    goto LABEL_137;
  v53 = at3_se_mng_param;
  v53->sucount = 0;
  v53->play_mode = 2;
LABEL_138:
  v57 = at3_swapbgm_mng_param;
  if (v57->play_mode)
    goto LABEL_139;
  at3_flag = 1;
  v57->play_mode = 1;
LABEL_140:
  if (!at3_flag)
    return;
  goto LABEL_152;
LABEL_139:
  goto LABEL_140;
LABEL_152:
  v63 = at3_swapbgm_mng_param;
  if (v63->play_mode != 1)
    return;
  v64 = v63->sunum;
  v65 = v63->sucount + 1;
  v63->sucount = v65;
  if (v65 < v64)
    return;
  v63 = at3_swapbgm_mng_param;
  v68 = at3_zerobuf;
  v63->p_pcmout = v68;
  v63->sucount = 0;
  v63->play_mode = 2;
  at3_swapbgm_mng_param->status = 0;
}

// 0x21e5db0
void Init(void) {
  void *at3_bgm_mng_param_local;
  void *v6;
  void *at3_se_mng_param_local;
  void *v11;
  void *v13;
  s16 *v14;
  void *v16;
  void *at3_swapbgm_mng_param_local;
  void *v20;
  s16 *v21;
  void *v23;
  void *v24;
  void *p_at3info;
  void *v26;
  void *v27;

  at3_bgm_mng_param_local = at3_bgm_mng_param;
  at3_bgm_mng_param_local->p_at3info = at3_bgm_info;
  v6 = at3_bgm_mng_param;
  v6->p_pcmout = at3_zerobuf;
  v6 = ((char *)v6 + 40);
  *((u8 *)&v6[-1].tbl_idx + 4) = 0;
  at3_se_mng_param_local = at3_se_mng_param;
  v11 = at3_bgm_mng_param;
  *(u64 *)&v11->suloop = 0x200000000LL;
  v11->status = 0;
  at3_se_mng_param_local->p_at3info = at3_se_info;
  v11->tbl_idx = 0;
  v13 = at3_se_mng_param;
  v14 = at3_zerobuf;
  v13->p_pcmout = v14;
  v13 = ((char *)v13 + 40);
  *((u8 *)&v13[-1].tbl_idx + 4) = 0;
  v16 = at3_se_mng_param;
  at3_swapbgm_mng_param_local = at3_swapbgm_mng_param;
  *(u64 *)&v16->suloop = 0x200000000LL;
  at3_swapbgm_mng_param_local->p_at3info = at3_swapbgm_info;
  v16->status = 0;
  v16->tbl_idx = 0;
  v20 = at3_swapbgm_mng_param;
  v21 = at3_zerobuf;
  v20->p_pcmout = v21;
  v23 = at3_swapbgm_mng_param;
  v24 = at3_swapbgm_info;
  p_at3info = v23->p_at3info;
  v23->status = 0;
  v23->tbl_idx = 0;
  p_at3info->at3decparam = 2;
  *(_OWORD *)&v23->sucount = xmmword_3D02790;
  v26 = at3_bgm_info;
  v27 = at3_se_info;
  v26->minusvol = 0;
  v27->minusvol = 2;
  v24->minusvol = 0;
}

// 0x21e5f00
void sndBgmGetInfo(void *info) {
  void *at3_bgm_mng_param_local;

  at3_bgm_mng_param_local = at3_bgm_mng_param;
  *(u64 *)&info->sunum = *(u64 *)&at3_bgm_mng_param_local->sunum;
  info->suloop = at3_bgm_mng_param_local->suloop;
}

// 0x21e5f80
void sndBgmSetInfo(void *info) {
  void *at3_bgm_mng_param_local;

  at3_bgm_mng_param_local = at3_bgm_mng_param;
  *(u64 *)&at3_bgm_mng_param_local->sunum = *(u64 *)&info->sunum;
  at3_bgm_mng_param_local->suloop = info->suloop;
}

// 0x21e6000
static void File_Init(char **fname, void *param) {
  ;
}

// 0x21e6010
static void File_BgmLoadStart(char **fname) {
  char *v3;
  fileHandle_t *_28877872;

  v3 = *fname;
  _28877872 = Load(v3, 0);
  fh_at3_bgm_load = _28877872;
  at3_bgm_mng_param->status = 1;
}

// 0x21e5240
static s32 File_BgmLoadChk(void *param) {
  param->sucount = 0;
  at3_bgm_mng_param->status = 2;
  return 1;
}

// 0x21e60d0
void sndBgmLoadFile(char **fname) {
  void *at3_bgm_mng_param_local;
  void *v7;
  void *v9;
  void *p_at3info;
  char *fnamea;

  fnamea = "/soundat3/b_bgm2-2.at3";
  at3_bgm_mng_param_local = at3_bgm_mng_param;
  at3_bgm_mng_param_local->p_at3info = at3_bgm_info;
  v7 = at3_bgm_mng_param;
  v7->p_pcmout = at3_zerobuf;
  v9 = at3_bgm_mng_param;
  p_at3info = v9->p_at3info;
  v9->play_mode = 2;
  p_at3info->at3decparam = 2;
  *(u64 *)&v9->sizeofunit = sub_C0;
  File_BgmLoadStart(&fnamea);
}

// 0x21e61a0
void sndBgmLoadId(s32 id) {
  u16 *v3;
  void *v10;
  void *v13;
  void *at3_swapbgm_mng_param_local;
  s16 *v15;
  void *v17;
  void *v20;
  s16 *v21;
  void *v24;
  void *v25;
  char *v26;
  char *fname;

  fname = 0;
  v3 = NewSpecific(char, 0x20u);
  CreateString_54864672(0, v3, 0);
  at3_bgm_skip = 0;
  at3_bgm_nowloadid = id;
  if (at3_bgm_nowplayid == id)
  {
    at3_bgm_skip = 1;
    return;
  }
  if (at3_bgm_mng_param->status)
  {
    at3_bgm_mng_param->sucount = 0;
    at3_bgm_mng_param->play_mode = 2;
    v10 = at3_bgm_mng_param;
    v10->p_pcmout = at3_zerobuf;
    v10 = ((char *)v10 + 40);
    *((u8 *)&v10[-1].tbl_idx + 4) = 0;
    v13 = at3_bgm_mng_param;
    at3_swapbgm_mng_param_local = at3_swapbgm_mng_param;
    v15 = at3_zerobuf;
    at3_bgm_skip = 0;
    v13->status = 0;
    *(u64 *)&at3_bgm_nowloadid = -1;
    at3_swapbgm_mng_param_local->p_pcmout = v15;
    at3_swapbgm_mng_param_local = ((char *)at3_swapbgm_mng_param_local + 40);
    HIDWORD(at3_swapbgm_mng_param_local[-1].p_at3info) = 0;
    at3_swapbgm_mng_param_local[-1].tbl_idx = 2;
    at3_swapbgm_mng_param->status = 0;
    goto LABEL_16;
  }
LABEL_16:
  v17 = at3_bgm_mng_param;
  v17->p_at3info = at3_bgm_info;
  v20 = at3_bgm_mng_param;
  v21 = at3_zerobuf;
  v20->p_pcmout = v21;
  v24 = at3_bgm_mng_param;
  at3_bgm_nowplayid = id;
  v24->tbl_idx = id;
  v25 = BgmTbl[id];
  v26 = v25->fname;
  v24->suloop = v25->suloop;
  v24->play_mode = 2;
  fname = v26;
  File_BgmLoadStart(&fname);
}

// 0x21e63f0
s32 sndBgmStatus(void) {
  s32 status;
  u32 v6;

  if (at3_bgm_mng_param->status != 1)
  {
    goto LABEL_5;
  }
  at3_bgm_mng_param->sucount = 0;
  if (v6)
  at3_bgm_mng_param->status = 2;
LABEL_5:
  if (at3_bgm_skip == 1)
    return 2;
  status = at3_bgm_mng_param->status;
  if ((status & 0xFFFFFFFC) == 4)
    return 3;
  return status;
}

// 0x21e65c0
static void BgmPlaySub(s32 id, f32 volume, s64 startTimeMs) {
  s16 suloop;
  void *Instance;

  if (id)
  {
    goto LABEL_5;
  }
  id = at3_bgm_nowloadid;
LABEL_5:
  suloop = BgmTbl[id]->suloop;
  Instance = get_Instance(0);
  PlayAT3BGM(Instance, id, BgmTbl[id]->fname, 1.0, volume, (suloop & 0x8000) == 0, startTimeMs, 0);
}

// 0x21e66f0
void sndBgmPlay(s32 id, s64 startTimeMs) {
  f32 Volume;

  Volume = GetVolume(1.0, 1);
  BgmPlaySub(id, Volume, startTimeMs);
}

// 0x21e67a0
void sndVoiceBgmPlay(s32 id, s64 startTimeMs) {
  f32 Volume;

  Volume = GetVolume(1.0, 3);
  BgmPlaySub(id, Volume, startTimeMs);
}

// 0x21e6850
void sndBgmPlayLoop(s32 id) {
  s32 at3_bgm_nowloadid_local;
  f32 Volume;
  void *Instance;

  at3_bgm_nowloadid_local = id;
  if (id)
    goto LABEL_3;
  goto LABEL_9000;
  if (at3_bgm_nowloadid_local)
  {
LABEL_3:
    goto LABEL_5;
  }
LABEL_9000:
  at3_bgm_nowloadid_local = at3_bgm_nowloadid;
LABEL_5:
  Volume = GetVolume(1.0, 1);
  Instance = get_Instance(0);
  PlayAT3BGM(Instance, at3_bgm_nowloadid_local, BgmTbl[at3_bgm_nowloadid_local]->fname, 1.0, Volume, 1, 0, 0);
}

// 0x21e6990
void sndBgmFadeIn(s32 id, s64 startTimeMs) {
  s32 v8;
  u32 v11;
  void *v12;
  f32 Volume;
  s32 v17;
  u32 v19;

  if (at3_bgm_skip == 1)
  {
    at3_bgm_skip = 0;
    return;
  }
  v8 = BgmStatus_NoSema();
  if (v8 != 1)
    goto LABEL_11;
  goto LABEL_9000;
  if (v17 != 1)
  {
LABEL_11:
    goto LABEL_12;
  }
LABEL_9000:
  at3_bgm_mng_param->sucount = 0;
  if (v19)
  at3_bgm_mng_param->status = 2;
LABEL_12:
  v12 = at3_bgm_mng_param;
  if (v12->play_mode == 1)
    goto LABEL_13;
  if (!v11)
  {
    v12 = at3_bgm_mng_param;
  }
  v12->play_mode = 0;
  v12->sucount = 0;
  v12->status = 5;
  at3_bgm_info->minusvol = 20;
  at3_bgm_fadein_speed = 6;
LABEL_16:
  goto LABEL_17;
LABEL_13:
  if (v11)
  {
    if (v12->status != 4)
      goto LABEL_15;
    goto LABEL_32;
  }
  v12 = at3_bgm_mng_param;
  if (v12->status == 4)
  {
LABEL_32:
    v12 = at3_bgm_mng_param;
    v12->status = 5;
    at3_bgm_fadein_speed = 6;
    goto LABEL_16;
  }
LABEL_15:
  goto LABEL_16;
LABEL_17:
  Volume = GetVolume(1.0, 1);
  BgmPlaySub(id, Volume, startTimeMs);
}

// 0x21e6ca0
void sndBgmContinue(void) {
  s32 v4;
  u32 v7;
  void *v8;
  f32 Volume;
  s32 v13;
  u32 v15;
  char *v17;

  if (at3_bgm_skip == 1)
  {
    at3_bgm_skip = 0;
    return;
  }
  v4 = BgmStatus_NoSema();
  if (v4 != 1)
    goto LABEL_10;
  goto LABEL_9001;
  if (v13 != 1)
  {
LABEL_10:
    goto LABEL_11;
  }
LABEL_9001:
  at3_bgm_mng_param->sucount = 0;
  if (v15)
  at3_bgm_mng_param->status = 2;
LABEL_11:
  v8 = at3_bgm_mng_param;
  if (v8->play_mode == 1)
    goto LABEL_12;
  if (!v7)
  {
    v8 = at3_bgm_mng_param;
  }
  v8->play_mode = 0;
  v17 = (char *)at3_continue_buff + 2 * v8->tbl_idx;
  v8->status = 5;
  v8->sucount = *((u16 *)v17 + 16);
  at3_bgm_info->minusvol = 20;
  at3_bgm_fadein_speed = 6;
LABEL_15:
  goto LABEL_16;
LABEL_12:
  if (v7)
  {
    if (v8->status != 4)
      goto LABEL_14;
    goto LABEL_32;
  }
  v8 = at3_bgm_mng_param;
  if (v8->status == 4)
  {
LABEL_32:
    v8 = at3_bgm_mng_param;
    v8->status = 5;
    at3_bgm_fadein_speed = 6;
    goto LABEL_15;
  }
LABEL_14:
  goto LABEL_15;
LABEL_16:
  Volume = GetVolume(1.0, 1);
  BgmPlaySub(0, Volume, 0);
}

// 0x21e6fd0
void sndBgmStop(void) {
  s64 tbl_idx;
  s32 sucount;
  void *Instance;

  at3_bgm_skip = 0;
  tbl_idx = at3_bgm_mng_param->tbl_idx;
  sucount = at3_bgm_mng_param->sucount;
  at3_bgm_mng_param->sucount = 0;
  at3_continue_buff[tbl_idx] = sucount;
  at3_bgm_mng_param->play_mode = 2;
  Instance = get_Instance(0);
  StopAT3BGM(Instance, 0);
}

// 0x21e7060
void sndImmediateBgmStop(void) {
  s64 tbl_idx;
  s32 sucount;
  void *Instance;

  at3_bgm_skip = 0;
  tbl_idx = at3_bgm_mng_param->tbl_idx;
  sucount = at3_bgm_mng_param->sucount;
  at3_bgm_mng_param->sucount = 0;
  at3_continue_buff[tbl_idx] = sucount;
  at3_bgm_mng_param->play_mode = 2;
  Instance = get_Instance(0);
  ImmediateStopAT3BGM(Instance, 0);
}

// 0x21e70f0
void sndBgmTop(void) {
  at3_bgm_mng_param->sucount = 0;
  return;
}

// 0x21e7180
void sndBgmFadeOut(void) {
  void *Instance;

  Instance = get_Instance(0);
  FadeOutAT3BGM(Instance, 100, 0);
}

// 0x21e71a0
void sndBgmFadeOut2(void) {
  s64 tbl_idx;
  u16 sucount;

  if (at3_bgm_mng_param->play_mode != 1)
    return;
  if (at3_bgm_mng_param->status != 3)
    return;
  at3_bgm_skip = 0;
  tbl_idx = at3_bgm_mng_param->tbl_idx;
  at3_bgm_mng_param->status = 4;
  sucount = at3_bgm_mng_param->sucount;
  at3_bgm_info->minusvol = 0;
  at3_continue_buff[tbl_idx] = sucount;
  at3_bgm_fade_speed = 3;
}

// 0x21e72b0
void sndBgmFree(void) {
  void *at3_bgm_mng_param_local;
  void *v7;

  at3_bgm_mng_param_local = at3_bgm_mng_param;
  at3_bgm_mng_param_local->p_pcmout = at3_zerobuf;
  at3_bgm_mng_param_local = ((char *)at3_bgm_mng_param_local + 40);
  *((u8 *)&at3_bgm_mng_param_local[-1].tbl_idx + 4) = 0;
  v7 = at3_bgm_mng_param;
  at3_bgm_skip = 0;
  v7->status = 0;
  *(u64 *)&at3_bgm_nowloadid = -1;
}

// 0x21e7390
static void File_SeLoadStart(char **fname) {
  char *v3;
  fileHandle_t *_28877872;

  v3 = *fname;
  _28877872 = Load(v3, 0);
  fh_at3_se_load = _28877872;
  at3_se_mng_param->status = 1;
}

// 0x21e7450
static s32 File_SeLoadChk(void *param) {
  param->sucount = 0;
  at3_se_mng_param->status = 2;
  return 1;
}

// 0x21e74d0
void sndSeLoadFile(char **fname) {
  at3_se_mng_param->play_mode = 2;
}

// 0x21e7540
void sndSeLoadId(s32 id) {
  at3_se_id = id;
  at3_se_mng_param->suloop = SeTbl[id]->suloop;
  at3_se_mng_param->play_mode = 2;
}

// 0x21e75d0
void sndSe2LoadId(s32 id) {
  at3_se_id = id;
  at3_se_mng_param->suloop = SiboTbl[id - 4096]->suloop;
  at3_se_mng_param->play_mode = 2;
}

// 0x21e7660
void sndSeLoadFromMem(void *data, s32 size, s32 mode) {
  ;
}

// 0x21e7670
static s32 SeStatus_NoSema(void) {
  u32 v4;

  if (at3_se_mng_param->status == 1)
  {
    at3_se_mng_param->sucount = 0;
    if (v4)
    {
LABEL_7:
      at3_se_mng_param->status = 2;
      return 1;
    }
    goto LABEL_7;
  }
  if (at3_se_mng_param->play_mode == 2)
    return 2;
  else
    return 3;
}

// 0x21e77c0
s32 sndSeStatus(void) {
  if (at3_se_mng_param->play_mode == 2)
    return 2;
  else
    return 3;
}

// 0x21e7830
void sndSePlay(s32 type) {
  s32 v9;
  u32 suloop;
  char *Fname;
  f32 Volume;
  void *Instance;
  void *v18;

  if (at3_se_id == -1)
    return;
  if (at3_se_mng_param->play_mode == 1)
    return;
  at3_se_mng_param->play_mode = 0;
  at3_se_mng_param->status = 3;
  at3_se_info->minusvol = 2;
  if (at3_se_id > 4095)
  {
    v9 = at3_se_id - 4096;
    suloop = (u16)SiboTbl[v9]->suloop;
    v9 = at3_se_id - 4096;
    Fname = GetFname(SiboTbl[v9], 0);
    goto LABEL_23;
  }
  v18 = SeTbl[at3_se_id];
  suloop = (u16)v18->suloop;
  v18 = SeTbl[at3_se_id];
  Fname = v18->fname;
LABEL_23:
  Volume = GetVolume(1.0, 2);
  Instance = get_Instance(0);
  PlayAT3SE(Instance, Fname, type, 1.0, Volume, (u8)(suloop >> 15) != 1, 0);
  at3_se_id = -1;
}

// 0x21e7ae0
void sndDeadSePlay_VolAngle(s32 devilid, s32 aVolume, f32 Angle) {
  s32 SpDevilID;
  s32 v8;
  void *v9;
  s16 suloop;
  char *Fname;
  void *Instance;
  f32 Volume;
  void *v14;

  SpDevilID = sBtlGetSpDevilID(devilid);
  if (SpDevilID >= 2560)
    v8 = SpDevilID - 2560;
  else
    v8 = SpDevilID;
  v9 = SiboTbl[v8];
  suloop = v9->suloop;
  Fname = GetFname(v9, 0);
  Instance = get_Instance(0);
  if (!IsPlayAT3SE(Instance, Fname, 0))
  {
    Volume = GetVolume((f32)aVolume / 127.0, 2);
    v14 = get_Instance(0);
    PlayAT3SE_VolAngle(v14, Fname, 1, (f32)aVolume / 127.0, Volume, Angle, (suloop & 0x8000) == 0, 0);
  }
}

// 0x21e7ca0
void sndSeStop(s32 id, s32 type) {
  void *Instance;

  at3_se_mng_param->sucount = 0;
  at3_se_mng_param->play_mode = 2;
  Instance = get_Instance(0);
  StopAT3SE_35974096(Instance, id, type, 0);
}

// 0x21e7d90
void sndSeStop_name(char *name, s32 type) {
  void *Instance;

  at3_se_mng_param->sucount = 0;
  at3_se_mng_param->play_mode = 2;
  Instance = get_Instance(0);
  StopAT3SE(Instance, name, type, 0);
}

// 0x21e7e80
void sndSeFree(void) {

}

// 0x21e7ee0
void sndSeFadeOut(void) {
  void *Instance;
  void *v7;

  if (at3_se_mng_param->play_mode)
    goto LABEL_17;
  if (at3_se_mng_param->status != 3)
    goto LABEL_17;
  if (at3_se_mng_param->sucount < at3_se_mng_param->sunum - 4)
  {
    at3_se_mng_param->status = 4;
    at3_se_fade_speed = 4;
    at3_se_info->minusvol = 2;
  }
LABEL_17:
  Instance = get_Instance(0);
  ChangeSeFadeOutTime(Instance, at3_se_id, 120, 0);
  v7 = get_Instance(0);
  StopAT3SE_35974096(v7, at3_se_id, 0, 0);
}

// 0x21e8050
static void SwapCopy(void) {
  ;
}

// 0x21e8060
static s32 SwapStatus(void) {
  return 1;
}

// 0x21e8070
void sndBgmLoadId_XF(s32 id) {
  at3_bgm_nowloadid = id;
  at3_bgm_skip = 0;
}

// 0x21e80e0
s32 sndBgmStatus_XF(void) {
  return 2;
}

// 0x21e80f0
void sndBgmReqestClear(void) {
  at3_bgm_request_flag = 0;
  return;
}

// 0x21e8170
s32 sndBgmReqestCheck(void) {
  return at3_bgm_request_flag;
}

// 0x21e81f0
s32 sndBgmGetNowPlayID(void) {
  return at3_bgm_nowplayid;
}

// 0x21e8270
s32 sndDebugPrint(void) {
  return at3_bgm_info->minusvol;
}

// 0x21e8300
s32 sndSeDebugPrint(void) {
  return at3_se_info->minusvol;
}
