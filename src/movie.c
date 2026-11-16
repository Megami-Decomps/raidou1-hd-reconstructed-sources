#include "types.h"
#include "cfg.h"
#include "configaudio.h"
#include "dds3adminiprocess.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "itf.h"
#include "kernel.h"
#include "movie.h"
#include "sdfdraw.h"
#include "sdfmat.h"
#include "sdfmem.h"
#include "sdfprim.h"
#include "sdfsystem.h"

#define DDS3_MOVIEDRAW_PROCNAME "movieDraw"

typedef struct dds3MovieTable_t dds3MovieTable_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct sdfPrimTransPacket_t sdfPrimTransPacket_t;

MvSTAT procStat;
s32 drawStart;
s32 drawEnd;
static char *path;
static char *wave;
static bool isLoop;
static bool isPlayBGM;
static bool memoryAlloc;
static void *mesh;
s32 PlayingNo;
static dds3ProcessID_t *dds3MovieDrawProcId;
static sdfColor32_t vertexWhite;
static sdfPrimTransPacket_t *transPacket;
static f32 lvol;
static void *decoder;
static dds3MovieTable_t *dds3MovieTable;

static dds3ProcessFunc_t DrawProc(dds3ProcessID_t *aProcId);
static bool PlayFile(dds3MovieTable_t tbl, bool isPlay);
static void InitMesh(void *mat);
static void DrawMesh(void);
static f32 CalcVolume(f32 f);

// 0x1d81e10
static dds3ProcessFunc_t DrawProc(dds3ProcessID_t *aProcId) {
  struct movie *static_fields;
  u32 v4;
  s32 v7;
  bool IsNullOrEmpty;
  f32 Volume;
  void *Instance;
  dds3ProcessFunc_t v19;

  v4 = procStat - 1;
  switch (v4)
  {
    case 0u:
      itfSetIsmesWndBaseDisp(0);
      v7 = 2;
      goto LABEL_56;
    case 1u:
      if (((decoder->klass[1]._1.image)(decoder, decoder->klass[1]._1.gc_desc) & 1) != 0)
      {
        IsNullOrEmpty = IsNullOrEmpty(wave, 0);
        if (!IsNullOrEmpty)
        {
          if (isPlayBGM)
          {
            Volume = GetVolume(1.0, 3);
            Instance = get_Instance(0);
            PlayMOVIE(Instance, 1000, wave, 1.0, Volume, 0, 0, 0);
          }
        }
        *(u64 *)movie->static_fields = 0x200000003LL;
        return 0;
      }
      return 0;
    case 2u:
      if (((decoder->klass[1]._1.byval_arg.data)(decoder, *(u64 *)&decoder->klass[1]._1.byval_arg.bits) & 1) != 0)
        return 0;
      drawEnd = 1;
      procStat = 4;
      return 0;
    case 3u:
      DrawMesh();
      return 0;
    case 4u:
      if (((decoder->klass[1]._1.this_arg.data)(decoder, *(u64 *)&decoder->klass[1]._1.this_arg.bits) & 1) != 0)
        return 0;
      v7 = 6;
LABEL_56:
      procStat = v7;
      return 0;
    case 5u:
      (decoder->klass[1]._1.name)(decoder, decoder->klass[1]._1.namespaze);
      PlayingNo = -1;
      procStat = 0;
      if (memoryAlloc)
      {
        sdfMemRelease();
      }
      else
      {
        memoryAlloc = 1;
      }
      itfSetIsmesWndBaseDisp(1);
      itfMessageClrAll();
      v19 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
      _ctor(v19, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      return v19;
    default:
      return 0;
  }
}

// 0x1d823c0
void movieNoMemoryAlloc(void) {
  memoryAlloc = 0;
  return;
}

// 0x1d82440
static bool PlayFile(dds3MovieTable_t tbl, bool isPlay) {
  char *wave_local;
  char *path_local;
  bool v9;
  char *v10;
  dds3ProcessFunc_t v13;
  dds3ProcessID_t *started;

  wave_local = tbl.wave;
  path_local = tbl.path;
  if (dds3MovieDrawProcId)
    return dds3MovieDrawProcId == 0;
  v9 = isPlay;
  path = path_local;
  v10 = wave_local[cfgGetConfigAUDIO(6, 0)];
  wave = v10;
  *(u64 *)&procStat = 1;
  drawEnd = 0;
  isPlayBGM = v9;
  v13 = Allocate(dds3ProcessFunc_t);
  _ctor(v13, 0, Method_Project_movie_DrawProc__, 0);
  started = dds3StartProcess("movieDraw", 11003, 1, 1, v13, 0, 0);
  dds3MovieDrawProcId = started;
  return dds3MovieDrawProcId == 0;
}

// 0x1d82630
void moviePlay(s32 aNum, bool loop, bool isPlay) {
  bool v9;

  if (aNum == 26)
  {
    dds3AdminiCallSequence(14, 0, 0);
  }
  else
  {
    if (PlayFile(dds3MovieTable[aNum], isPlay))
    {
      v9 = loop;
      PlayingNo = aNum;
      isLoop = v9;
    }
  }
}

// 0x1d82700
void movieStop(s32 bgmStop) {
  void *Instance;

  if (!dds3MovieDrawProcId)
    return;
  procStat = 5;
  dds3MovieDrawProcId = 0;
  drawEnd = 1;
  movieDisp(0);
  if (!bgmStop)
  {
    if (isPlayBGM)
    {
      Instance = get_Instance(0);
      ImmediateStopAT3BGM(Instance, 0);
    }
  }
  isPlayBGM = 1;
}

// 0x1d82a30
s32 movieCheckEnd(void) {
  return drawEnd;
}

// 0x1d82ab0
s32 movieCheckDrawStat(void) {
  return drawStart;
}

// 0x1d82b30
void movieInitManager(void) {
  procStat = 0;
  movieStop(0);
  memoryAlloc = 1;
}

// 0x1d82bb0
void moviePause(bool sw) {
  if (!dds3MovieDrawProcId)
    return;
  (decoder->klass[1]._1.element_class)(decoder, sw, decoder->klass[1]._1.castClass);
}

// 0x1d82830
void movieDisp(bool sw) {
  void *v7;
  struct sdfVector4_t *p_oneVector;
  f32 *p_y;
  f32 *p_z;
  f32 *p_w;
  f32 v13;
  f32 v14;
  f32 v15;

  if (!dds3MovieDrawProcId)
    return;
  if (!op_Inequality(mesh, 0, 0))
    return;
  v7 = mesh;
  if (!sw)
  {
    p_y = &zeroVector.y;
    p_z = &zeroVector.z;
    p_w = &zeroVector.w;
    goto LABEL_22;
  }
  p_oneVector = &oneVector;
  p_y = &oneVector.y;
  p_z = &oneVector.z;
  p_w = &oneVector.w;
LABEL_22:
  v13 = *p_w;
  v14 = *p_z;
  v15 = *p_y;
  v7->object_color.x = zeroVector.x;
  v7->object_color.y = v15;
  v7->object_color.z = v14;
  v7->object_color.w = v13;
  (decoder->klass[1]._1.element_class)(decoder, !sw, decoder->klass[1]._1.castClass);
}

// 0x1d82c70
void movieCue(void) {
  if (!dds3MovieDrawProcId)
    return;
  (decoder->klass[1]._1.declaringType)(decoder, decoder->klass[1]._1.parent);
  if (procStat == 4)
  {
    drawEnd = 0;
    procStat = 3;
  }
}

// 0x1d82d70
s32 movieGetFrame(void) {
  return (decoder->klass[1]._1.generic_class)(decoder, decoder->klass[1]._1.typeMetadataHandle);
}

// 0x1d82de0
s32 movieGetFrameCount(void) {
  return (decoder->klass[1]._1.interopData)(decoder, decoder->klass[1]._1.klass);
}

// 0x1d82e50
bool movieCheckStandby(void) {
  return procStat == 0;
}

// 0x1d82ec0
MvSTAT movieGetProcStat(void) {
  return procStat;
}

// 0x1d82f40
static void InitMesh(void *mat) {
  void *_36165888;
  void *transform;
  void *v8;
  MeshEdit *edit;
  MeshEdit *v11;
  void *Material;
  void *v14;

  _36165888 = Make_36165888(mat, 0);
  mesh = _36165888;
  transform = get_transform(mesh, 0);
  v8 = get_transform(hook, 0);
  SetParent_61042560(transform, v8, 0, 0);
  mesh->type = 0;
  InitSquare(mesh, 1, 0);
  edit = mesh->edit;
  (edit->klass->vtable._4_unknown.methodPtr)(edit, edit->klass->vtable._4_unknown.method);
  SetSquarePos(mesh, 0, -1.0, 1.0, 1.0, -1.0, 0);
  SetSquareCol(mesh, 0, (sdfColor32_t)(u32)vertexWhite.rgba, 0);
  SetSquareUV_36173248(mesh, 0, 0);
  SetSquareIndex_36173424(mesh, 0);
  SetMarker(mesh, 0);
  v11 = mesh->edit;
  (v11->klass->vtable._5_unknown.methodPtr)(v11, v11->klass->vtable._5_unknown.method);
  Material = get_Material(mesh, 0);
  SetVector_60817376(Material, ID_OBJECT_COLOR, zeroVector, 0);
  v14 = mesh;
  v14->object_color = oneVector;
}

// 0x1d822e0
static void DrawMesh(void) {
  sdfDrawTag_t *v1;

  v1 = sdfPrimAllocDrawTag();
  sdfDrawTagLink(v1, transPacket);
  sdfDrawTagLink(v1, mesh->packet);
  sdfDrawTagLinkOt(Ot[103], v1);
}

// 0x1d83210
static f32 CalcVolume(f32 f) {
  return GetVolume(lvol + f, 3);
}

// 0x1d81750
char *movieGetSofdec2Path(char *path) {
  return Concat_54831728("movie/", path, ".usm", 0);
}
