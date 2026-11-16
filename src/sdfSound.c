#include "types.h"
#include "configaudio.h"
#include "sdfsound.h"
#include "sndmanager.h"
#include "sndsmghd.h"

typedef void (*sdfSoundMovieCallback_t)(s32 size);

static void *p2sdStreamCallback;
static s32 MoviePlaying;
static void *_acbwork;

// 0x2249240
void p2sdPlayBGM(s32 MidiNo) {
  s32 v5;
  Il2CppObject *Item;
  void *v7;
  void *Instance;
  f32 Volume;

  p2sdLoadSMGFile(MidiNo);
  v5 = MidiNo & 0xFFFF0000;
  if (!object___ContainsKey(_acbwork, MidiNo & 0xFFFF0000))
    return;
  Item = object___get_Item(_acbwork, v5);
  if (!Item)
    return;
  v7 = Item;
  Instance = get_Instance(Item);
  Volume = GetVolume(1.0, 2);
  PlaySE(Instance, MidiNo, v7, 1.0, Volume);
}

// 0x2249850
void p2sdPause(s32 MidiNo) {
  ;
}

// 0x2249860
void p2sdContinue(s32 MidiNo) {
  ;
}

// 0x2249870
void p2sdSndStop(s32 MidiNo) {
  void *Instance;

  Instance = get_Instance(*(const MethodInfo **)&MidiNo);
  StopSE(Instance, MidiNo);
}

// 0x22499c0
void p2sdBGMStopAll(void) {
  void *Instance;

  Instance = get_Instance();
  StopAT3BGM(Instance);
}

// 0x2249ac0
void p2sdSEStopAll(void) {
  void *Instance;
  void *v4;
  CriPlayInfo *playerSE;
  void *v6;
  s64 v7;
  s64 v8;
  s64 v9;
  s64 maxSE;
  s64 v11;

  Instance = get_Instance();
  StopAllAT3SE(Instance);
  v4 = get_Instance();
  if (v4->maxSE >= 1)
  {
    playerSE = v4->playerSE;
    v6 = v4;
    v7 = 4;
    do
    {
      v8 = 8 * v7;
      Loop(*(void *)(*((u64 *)&playerSE->obj.klass + v7) + 16), 0, 0);
      Stop_37506912(*(void *)(*((u64 *)&v6->playerSE->obj.klass + v7) + 16), 0);
      playerSE = v6->playerSE;
      v9 = v7 - 3;
      ++v7;
      maxSE = v6->maxSE;
      v11 = *(s64 *)((char *)&playerSE->obj.klass + v8);
      *(u32 *)(v11 + 28) = -1;
      *(u32 *)(v11 + 48) = 0;
    }
    while (v9 < maxSE);
  }
}

// 0x2249cc0
void p2sdSndStopAll(void) {
  void *Instance;
  void *v4;
  void *v7;
  CriPlayInfo *playerSE;
  void *v9;
  s64 v10;
  s64 v11;
  s64 v12;
  s64 maxSE;
  s64 v14;

  Instance = get_Instance();
  StopAT3BGM(Instance);
  v4 = get_Instance();
  StopAllAT3SE(v4);
  v7 = get_Instance();
  if (v7->maxSE >= 1)
  {
    playerSE = v7->playerSE;
    v9 = v7;
    v10 = 4;
    do
    {
      v11 = 8 * v10;
      Loop(*(void *)(*((u64 *)&playerSE->obj.klass + v10) + 16), 0, 0);
      Stop_37506912(*(void *)(*((u64 *)&v9->playerSE->obj.klass + v10) + 16), 0);
      playerSE = v9->playerSE;
      v12 = v10 - 3;
      ++v10;
      maxSE = v9->maxSE;
      v14 = *(s64 *)((char *)&playerSE->obj.klass + v11);
      *(u32 *)(v14 + 28) = -1;
      *(u32 *)(v14 + 48) = 0;
    }
    while (v12 < maxSE);
  }
}

// 0x2248860
void p2sdPlaySeEx(s32 MidiNo, s32 aVolume, s32 pan) {
  s32 v8;
  Il2CppObject *Item;
  void *v10;
  f32 v11;
  void *Instance;
  f32 Volume;

  v8 = MidiNo & 0xFFFF0000;
  if (!object___ContainsKey(_acbwork, MidiNo & 0xFFFF0000))
    return;
  Item = object___get_Item(_acbwork, v8);
  if (!Item)
    return;
  v10 = Item;
  v11 = (f32)aVolume / 127.0;
  Instance = get_Instance(Item);
  Volume = GetVolume(v11, 2);
  PlaySE(Instance, MidiNo, v10, v11, Volume);
}

// 0x2248be0
void p2sdPlaySeExLoop(s32 MidiNo, s32 aVolume, s32 pan, bool loop) {
  s32 v9;
  Il2CppObject *Item;
  void *v11;
  f32 v12;
  void *Instance;
  f32 Volume;

  v9 = MidiNo & 0xFFFF0000;
  if (!object___ContainsKey(_acbwork, MidiNo & 0xFFFF0000))
    return;
  Item = object___get_Item(_acbwork, v9);
  if (!Item)
    return;
  v11 = Item;
  v12 = (f32)aVolume / 127.0;
  Instance = get_Instance(Item);
  Volume = GetVolume(v12, 2);
  PlaySELoop(Instance, MidiNo, v11, v12, Volume, 0);
}

// 0x2248fe0
void p2sdPlaySeEx_VolAngle(s32 MidiNo, s32 aVolume, f32 Angle) {
  s32 v9;
  Il2CppObject *Item;
  void *v11;
  f32 v12;
  void *Instance;
  f32 Volume;

  v9 = MidiNo & 0xFFFF0000;
  if (!object___ContainsKey(_acbwork, MidiNo & 0xFFFF0000))
    return;
  Item = object___get_Item(_acbwork, v9);
  if (!Item)
    return;
  v11 = Item;
  v12 = (f32)aVolume / 127.0;
  Instance = get_Instance(Item);
  Volume = GetVolume(v12, 2);
  PlaySE_VolAngle(Instance, MidiNo, v11, v12, Volume, Angle);
}

// 0x2249f40
void p2sdPlaySeDeg(s32 MidiNo, f32 deg, f32 dis, f32 hight) {
  s32 v5;
  u32 v10;
  s32 v11;
  f32 v12;
  s32 v13;
  f32 v14;
  s32 v16;
  bool v17;
  s32 v18;

  v10 = (s32)deg % 360;
  if (deg == INFINITY)
    v11 = -128;
  else
    v11 = (s32)deg % 360;
  if (v11 >= 181)
  {
    v11 -= 360;
    goto LABEL_17;
  }
  if (v11 <= -181)
  {
    v10 = v11 + 360;
    v12 = 1.0;
    v13 = v11 + 315;
    v14 = 1.0;
    if (v10 >= 0x2D)
      goto LABEL_20;
    goto LABEL_10;
  }
  if (v11 < 0)
  {
LABEL_17:
    v10 = -v11;
    v12 = 1.0;
    v13 = -v11 - 45;
    v14 = 1.0;
    if (v10 >= 0x2D)
      goto LABEL_20;
LABEL_10:
    if (dis <= v12)
      goto LABEL_11;
LABEL_25:
    v14 = v14 / (f32)((f32)(dis * 0.333) + 1.0);
    goto LABEL_12;
  }
  v12 = 1.0;
  v13 = v10 - 45;
  v14 = 1.0;
  if (v10 < 0x2D)
    goto LABEL_10;
LABEL_20:
  v17 = v10 >= 0x5A;
  v18 = v10 - 90;
  if (v18 != 0 && v17)
  {
    v14 = (f32)((f32)v18 * -0.005556) + 0.75;
    if (dis > v12)
      goto LABEL_25;
  }
  else
  {
    v14 = (f32)((f32)v13 * -0.004444) + 1.0;
    if (dis > v12)
      goto LABEL_25;
  }
LABEL_11:
LABEL_12:
  if ((f32)(v14 * 127.0) == INFINITY)
    v16 = 0x80000000;
  else
    v16 = (f32)(v14 * 127.0);
  p2sdPlaySeEx(MidiNo, v16, v5);
}

// 0x2249220
void p2sdPlaySe3DEx(s32 MidiNo, f32 posx, f32 posy, f32 posz, s32 limit) {
  ;
}

// 0x2248ec0
bool p2sdIsPlaySE(s32 id) {
  void *Instance;
  s32 maxSE;
  void *v5;
  s64 v6;
  CriPlayInfo *v7;

  Instance = get_Instance(*(const MethodInfo **)&id);
  maxSE = Instance->maxSE;
  if (maxSE < 1)
    return 0;
  v5 = Instance;
  v6 = 0;
  while (1)
  {
    v7 = v5->playerSE[v6];
    if (v7->id == id)
      break;
LABEL_3:
    if (++v6 >= maxSE)
      return 0;
  }
  if (GetStatus(v7->p, 0) != 2)
  {
    maxSE = v5->maxSE;
    goto LABEL_3;
  }
  return 1;
}

// 0x224a1a0
bool p2sdIsBeforePlayback(s32 id) {
  void *Instance;
  s32 maxSE;
  void *v5;
  s64 v6;
  CriPlayInfo *v7;

  Instance = get_Instance(*(const MethodInfo **)&id);
  maxSE = Instance->maxSE;
  if (maxSE < 1)
    return 0;
  v5 = Instance;
  v6 = 0;
  while (1)
  {
    v7 = v5->playerSE[v6];
    if (v7->id == id)
      break;
LABEL_3:
    if (++v6 >= maxSE)
      return 0;
  }
  if ((u32)(GetStatus(v7->p, 0) - 1) >= 2)
  {
    maxSE = v5->maxSE;
    goto LABEL_3;
  }
  return 1;
}

// 0x224a2f0
void p2sdSetStandPos(f32 Cposx, f32 Cposy, f32 Cposz, f32 Pposx, f32 Pposy, f32 Pposz) {
  ;
}

// 0x224a300
void p2sdOutputMode(s32 output_mode) {
  ;
}

// 0x224a310
void p2sdMasterVolume(u16 vol) {
  ;
}

// 0x224a320
void p2sdBGMVolume(u16 vol) {
  ;
}

// 0x224a330
void p2sdFadeIn(s32 MidiNo) {
  ;
}

// 0x224a340
void p2sdFadeOut(s32 MidiNo) {
  ;
}

// 0x224a350
void p2sdBGMVolHalfDown(void) {
  ;
}

// 0x224a360
void p2sdBGMVolHalfUp(void) {
  ;
}

// 0x224a370
void p2sdMelodyTrans(s32 midiNo) {
  ;
}

// 0x224a380
void p2sdVolume2(s32 MidiNo, u16 vol) {
  s32 v7;
  Il2CppObject *Item;
  void *v9;
  f32 v10;
  void *Instance;
  f32 Volume;

  v7 = MidiNo & 0xFFFF0000;
  if (!object___ContainsKey(_acbwork, MidiNo & 0xFFFF0000))
    return;
  Item = object___get_Item(_acbwork, v7);
  if (!Item)
    return;
  v9 = Item;
  v10 = (f32)vol / 127.0;
  Instance = get_Instance(Item);
  Volume = GetVolume(v10, 2);
  PlaySE_Volume2(Instance, MidiNo, v9, v10, Volume);
}

// 0x224a650
void p2sdOverlap(s32 MidiNo, u16 vol, s64 overlapTime) {
  s32 v9;
  Il2CppObject *Item;
  void *v11;
  f32 v12;
  void *Instance;
  f32 Volume;

  v9 = MidiNo & 0xFFFF0000;
  if (!object___ContainsKey(_acbwork, MidiNo & 0xFFFF0000))
    return;
  Item = object___get_Item(_acbwork, v9);
  if (!Item)
    return;
  v11 = Item;
  v12 = (f32)vol / 127.0;
  Instance = get_Instance(Item);
  Volume = GetVolume(v12, 2);
  PlaySE_Overlap(Instance, MidiNo, v11, v12, Volume, overlapTime);
}

// 0x224a940
s32 p2sdAdpcmStreamPlay(char *fname, u8 vol) {
  return 0;
}

// 0x224a950
s32 p2sdAdpcmStreamStatus(void) {
  return 0;
}

// 0x224a960
void p2sdAdpcmStreamStop(void) {
  ;
}

// 0x224a970
void p2sdAdpcmStreamSetVolume(u16 vol) {
  ;
}

// 0x224a980
void p2sdAdpcmStreamFadeout(u32 fade) {
  ;
}

// 0x224a990
void *p2sdSetMovieCallback(void *func) {
  if (MoviePlaying)
    return 0;
  p2sdStreamCallback = func;
  return func;
}

// 0x224aa60
s32 p2sdMovieStreamPlay(u8 vol) {
  return MoviePlaying != 0;
}

// 0x224aad0
s32 p2sdMovieStreamStatus(void) {
  return MoviePlaying;
}

// 0x224ab50
void p2sdMovieStreamStop(void) {
  ;
}

// 0x224ab60
void p2sdMovieStreamSetVolume(u16 vol) {
  ;
}

// 0x224ab70
void p2sdDbgVolSet(s32 area, u8 *buff) {
  ;
}

// 0x224ab80
void p2sdDbgVolGet(s32 area, u8 *buff) {
  ;
}

// 0x224ab90
void p2sdSMGLock(s32 MidiNo) {
  ;
}

// 0x224aba0
void p2sdSMGUnLock(s32 MidiNo) {
  ;
}

// 0x224abb0
void p2sdSMGClearLock(void) {
  ;
}

// 0x22495d0
s32 p2sdLoadCheckMidi(s32 MidiNo) {
  return object___ContainsKey(_acbwork, MidiNo & 0xFFFF0000);
}

// 0x2249410
void p2sdLoadSMGFile(s32 MidiNo) {
  s32 v4;
  char *SmgName;
  _BOOL8 IsNullOrEmpty;
  Il2CppObject *AcbFile;
  void *Instance;

  v4 = MidiNo & 0xFFFF0000;
  if (object___ContainsKey(_acbwork, v4))
  {
    return;
  }
  SmgName = sndGetSmgName(v4);
  IsNullOrEmpty = IsNullOrEmpty(SmgName, 0);
  if (IsNullOrEmpty)
  {
    AcbFile = 0;
  }
  else
  {
    Instance = get_Instance(IsNullOrEmpty);
    AcbFile = LoadAcbFile(Instance, SmgName, 0);
  }
  object___Add(_acbwork, v4, AcbFile);
  return;
}

// 0x224ad10
void p2sdUnLoadSMGFile(s32 MidiNo, bool remove) {
  s32 v6;
  Il2CppObject *Item;

  v6 = MidiNo & 0xFFFF0000;
  if (!object___ContainsKey(_acbwork, v6))
    return;
  Item = object___get_Item(_acbwork, v6);
  if (Item)
    (Item->klass->vtable[5].methodPtr)(Item, Item->klass->vtable[5].method);
  if (remove)
  {
    object___Remove(_acbwork, v6);
  }
}

// 0x224aec0
void p2sdUnLoadAllSMGFile(void) {
  void *acbwork;
  void *v4;
  s32 v5;
  __int128 v7;
  __int128 smg_no;

  v7 = 0u;
  smg_no = 0u;
  acbwork = _acbwork;
  v4 = Allocate(System_Collections_Generic_List_KeyValuePair_int__CriAtomExAcb);
  object_____ctor_47177280(v4, acbwork);
  object____GetEnumerator(&v7, v4);
  while (object____MoveNext(&v7))
  {
    v5 = smg_no;
    if (!sndIsCommonSMG(v5))
    {
      p2sdUnLoadSMGFile(v5, 0);
      object___Remove(_acbwork, v5);
    }
  }
  object____Dispose(&v7);
}

// 0x224b100
void p2sdLoadSMGFileOnMem(u8 *po, s32 size) {
  ;
}

// 0x224b110
bool p2sdMidiRegister(s32 MidiNo) {
  s32 v5;
  Il2CppObject *Item;
  void *v7;
  CriWare_CriAtomEx_CueInfo_o v9;

  v5 = MidiNo & 0xFFFF0000;
  if (!object___ContainsKey(_acbwork, MidiNo & 0xFFFF0000))
    goto LABEL_16;
  Item = object___get_Item(_acbwork, v5);
  if (!Item)
    return (char)Item;
  v7 = Item;
  get_Instance(Item);
  memset(&v9, 0, sizeof(v9));
  if (MidiNo == -1)
LABEL_16:
    LOBYTE(Item) = 0;
  else
    LOBYTE(Item) = GetCueInfo_37449696(v7, (u16)MidiNo, &v9, 0);
  return (char)Item;
}
