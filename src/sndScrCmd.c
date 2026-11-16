#include "types.h"
#include "cfg.h"
#include "configaudio.h"
#include "fld.h"
#include "itf.h"
#include "scr.h"
#include "sdfsound.h"
#include "sndat3.h"
#include "sndmanager.h"

static s32 LoadCheck(s32 ReqNo);
void BgmPlaySub(s32 id, f32 volume, s64 startTimeMs);

// macros
// 0x21ef0e0: s32 BGM_PLAY(void)
static inline s32 BGM_PLAY(void) {
  s32 IntPara;
  s32 v3;
  s32 v4;

  IntPara = scrGetIntPara(0);
  v3 = IntPara & 0xFFFF0000;
  v4 = p2sdLoadCheckMidi(IntPara & 0xFFFF0000);
  if (v4 == 2)
    return 0;
  if (v4)
  {
    p2sdPlayBGM(IntPara);
    return 1;
  }
  else
  {
    p2sdLoadSMGFile(v3);
    return 0;
  }
}

// 0x21ef230: s32 SE_STOP(void)
static inline s32 SE_STOP(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  p2sdSndStop(IntPara);
  return 1;
}

// 0x21ef2d0: s32 SE_PLAY(void)
static inline s32 SE_PLAY(void) {
  s32 IntPara;
  s32 v3;
  s32 v4;

  IntPara = scrGetIntPara(0);
  v3 = IntPara & 0xFFFF0000;
  v4 = p2sdLoadCheckMidi(IntPara & 0xFFFF0000);
  if (v4 == 2)
    return 0;
  if (v4)
  {
    SE(IntPara);
    return 1;
  }
  else
  {
    p2sdLoadSMGFile(v3);
    return 0;
  }
}

// 0x21ef410: s32 BGM_STOP(void)
static inline s32 BGM_STOP(void) {
  p2sdSndStopAll();
  return 1;
}

// 0x21ef490: s32 LOAD_SMG(void)
static inline s32 LOAD_SMG(void) {
  s32 IntPara;
  s32 v3;
  s32 v4;

  IntPara = scrGetIntPara(0);
  v3 = IntPara & 0xFFFF0000;
  v4 = p2sdLoadCheckMidi(v3);
  if (v4)
    return v4 != 2;
  p2sdLoadSMGFile(v3);
  return 0;
}

// 0x21ef5a0: s32 VOICE_PLAY(void)
#define VOICE_PLAY() (itfMesMngMessage())

// 0x21ef610: s32 VOICE_STOP(void)
#define VOICE_STOP() (1)

// 0x21ef620: s32 VOICE_STATUS(void)
#define VOICE_STATUS() (1)

// 0x21ef630: s32 VOICE_PAUSE(void)
#define VOICE_PAUSE() (1)

// 0x21ef640: s32 MSG_HOJO(void)
static inline s32 MSG_HOJO(void) {
  s32 ConfigGAME;

  ConfigGAME = cfgGetConfigGAME(8, 0);
  scrSetIntReturnValue(ConfigGAME);
  return 1;
}

// 0x21ef6e0: s32 VOICE_PLAY_LABEL(void)
static inline s32 VOICE_PLAY_LABEL(void) {
  char *StrPara;
  char *v5;

  StrPara = scrGetStrPara(0);
  if (!StrPara)
    return 1;
  v5 = StrPara;
  sndVoicePlayFile(v5, 0);
  return 1;
}

// 0x21ef7b0: s32 VOICE_WAIT_LABEL(void)
static inline s32 VOICE_WAIT_LABEL(void) {
  void *Instance;

  Instance = get_Instance(0);
  return !IsVoicePlay(Instance, 0, 0);
}

// 0x21ef820: s32 AT3_BGM_LOAD(void)
static inline s32 AT3_BGM_LOAD(void) {
  s32 IntPara;

  at3_bgm_request_flag = 1;
  IntPara = scrGetIntPara(0);
  if ((IntPara & 0x80000000) == 0)
  {
    goto LABEL_6;
  }
  IntPara = mapGetReturnBgmID();
LABEL_6:
  at3_bgm_nowloadid = IntPara;
  at3_bgm_skip = 0;
  return 1;
}

// 0x21ef9b0: s32 AT3_BGM_PLAY(void)
static inline s32 AT3_BGM_PLAY(void) {
  f32 Volume;

  at3_bgm_request_flag = 1;
  Volume = GetVolume(1.0, 1);
  BgmPlaySub(0, Volume, 0);
  return 1;
}

// 0x21efaa0: s32 AT3_BGM_STOP(void)
static inline s32 AT3_BGM_STOP(void) {
  s64 tbl_idx;
  s32 sucount;
  void *Instance;

  at3_bgm_request_flag = 1;
  at3_bgm_skip = 0;
  tbl_idx = at3_bgm_mng_param->tbl_idx;
  sucount = at3_bgm_mng_param->sucount;
  at3_bgm_mng_param->sucount = 0;
  at3_continue_buff[tbl_idx] = sucount;
  at3_bgm_mng_param->play_mode = 2;
  Instance = get_Instance(0);
  StopAT3BGM(Instance, 0);
  sndBgmFree();
  return 1;
}

// 0x21efbb0: s32 AT3_BGM_FADEIN(void)
static inline s32 AT3_BGM_FADEIN(void) {
  at3_bgm_request_flag = 1;
  sndBgmFadeIn(0, 0);
  return 1;
}

// 0x21efc20: s32 AT3_BGM_FADE(void)
static inline s32 AT3_BGM_FADE(void) {
  void *Instance;

  at3_bgm_request_flag = 1;
  Instance = get_Instance(0);
  FadeOutAT3BGM(Instance, 100, 0);
  return 1;
}

// 0x21efca0: s32 AT3_BGM_CONTINUE(void)
static inline s32 AT3_BGM_CONTINUE(void) {
  *((u32 *)*((const MethodInfo *)sndAt3 + 2).virtualMethodPointer + 42) = 1;
  sndBgmContinue();
  return 1;
}

// 0x21efd10: s32 AT3_BGM_END_WAIT(void)
#define AT3_BGM_END_WAIT() (sndBgmStatus() == 0)

// 0x21efd90: s32 AT3_SE_LOAD(void)
static inline s32 AT3_SE_LOAD(void) {
  s32 IntPara;
  s64 v7;

  IntPara = scrGetIntPara(0);
  if (IntPara <= 4095)
  {
    at3_se_id = IntPara;
    at3_se_mng_param->play_mode = 2;
    v7 = (s64)SeTbl + 8 * IntPara;
    goto LABEL_14;
  }
  at3_se_id = IntPara;
  at3_se_mng_param->play_mode = 2;
  v7 = (s64)SiboTbl + 8 * (u32)(IntPara - 4096);
LABEL_14:
  at3_se_mng_param->suloop = *(s16 *)(*(u64 *)(v7 + 32) + 22);
  return 1;
}

// 0x21eff20: s32 AT3_SE_PLAY(void)
static inline s32 AT3_SE_PLAY(void) {
  sndSePlay(0);
  return 1;
}

// 0x21effa0: s32 AT3_SE_STOP(void)
static inline s32 AT3_SE_STOP(void) {
  sndSeStop(-1, 0);
  return 1;
}

// 0x21f0000: s32 AT3_SE_FADE(void)
static inline s32 AT3_SE_FADE(void) {
  sndSeFadeOut();
  return 1;
}

// 0x21ef010
static s32 LoadCheck(s32 ReqNo) {
  s32 v4;
  s32 v5;

  v4 = ReqNo & 0xFFFF0000;
  v5 = p2sdLoadCheckMidi(v4);
  if (v5)
    return v5 != 2;
  p2sdLoadSMGFile(v4);
  return 0;
}
