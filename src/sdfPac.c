#include "types.h"
#include "libsdf.h"
#include "sdfdecomp.h"
#include "sdfpac.h"

#define PAC_BLOCK_ALIGN 64

typedef struct sdfPacDecodeCb_t sdfPacDecodeCb_t;
typedef struct sdfPacDecodeResrcHandle_t sdfPacDecodeResrcHandle_t;
typedef struct sdfPacStdBlockHeader_t sdfPacStdBlockHeader_t;

static void UseSrc(sdfPacDecodeCb_t *cb, s32 size);
static void NewBlock(sdfPacDecodeCb_t *cb);
static void EndBlock(sdfPacDecodeCb_t *cb);
static sdfPacDecodeResrcHandle_t *NewResrc(sdfPacDecodeCb_t *cb, sdfPacStdBlockHeader_t *hdr);
static SDF_PAC_CB_ACT StdCallback(sdfPacDecodeCb_t *cb, SDF_PAC_CB_CAUSE cause, sdfPacStdBlockHeader_t *hdr);
static void MemDecoderFunc(sdfPacDecodeCb_t *cb);
static void MemDecompDecoderFunc(sdfPacDecodeCb_t *cb);
static void MemStayDecoderFunc(sdfPacDecodeCb_t *cb);
static void MemDecoderFuncInit(sdfPacDecodeCb_t *cb, sdfPacStdBlockHeader_t *hdr);
static void MemDecoderInit(sdfPacDecodeCb_t *cb, sdfPacStdBlockHeader_t *hdr);
static void ModelDecoderEndFunc(sdfPacDecodeCb_t *cb);
static void ModelDecoderInit(sdfPacDecodeCb_t *cb, sdfPacStdBlockHeader_t *hdr);
static void MotionDecoderEndFunc(sdfPacDecodeCb_t *cb);
static void MotionDecoderInit(sdfPacDecodeCb_t *cb, sdfPacStdBlockHeader_t *hdr);

// 0x22636d0
sdfPacDecodeResrcHandle_t *sdfPacGetResrc(sdfPacDecodeCb_t *cb) {
  return cb->resrcHead;
}

// 0x22636e0
void sdfPacInit(sdfPacDecodeCb_t *cb, sdfPacCallback_t callback) {
  cb->currBlockNum = -1;
  if (!callback)
  {
    callback = Allocate(sdfPacCallback_t);
    _ctor(callback, 0);
  }
  cb->callback = callback;
}

// 0x22638b0
void sdfPacSetStay(sdfPacDecodeCb_t *cb) {
  cb->flag |= 1u;
}

// 0x22638c0
void sdfPacFree(sdfPacDecodeCb_t *cb) {
  ;
}

// 0x22638d0
static void UseSrc(sdfPacDecodeCb_t *cb, s32 size) {
  cb->srcData->point += size;
}

// 0x22638f0
static void NewBlock(sdfPacDecodeCb_t *cb) {
  sdfBinary *srcData;
  s32 v4;
  sdfPacStdBlockHeader_t *v5;
  char *String;
  char *v7;
  u32 U32;
  s16 currBlockNum;
  s32 v10;
  s32 rest;

  srcData = cb->srcData;
  v4 = srcData->point & 0x3F;
  if (v4)
  {
    cb->stat = 1;
    cb->rest = 64 - v4;
  }
  else
  {
    v5 = Allocate(sdfPacStdBlockHeader_t);
    v5->fileType = ReadU8(srcData, 0);
    v5->compression = ReadU8(srcData, 0);
    v5->userId = ReadU16(srcData, 0);
    v5->size = ReadU32(srcData, 0);
    String = ReadString(srcData, 4, 0);
    v7 = CutCode00(srcData, String, 0);
    v5->magicCode = v7;
    U32 = ReadU32(srcData, 0);
    currBlockNum = cb->currBlockNum;
    v5->realSize = U32;
    cb->currBlockNum = currBlockNum + 1;
    cb->rest = v5->size - 16;
    v10 = (cb->callback->invoke_impl)(cb->callback->method_code, cb, 0, v5, cb->callback->method);
    if (v10 == 2)
    {
      rest = cb->rest;
      cb->stat = 1;
      cb->rest = ((cb->srcData->point + rest + 63) & 0xFFFFFFC0) - cb->srcData->point;
    }
    else if (v10 == 1)
    {
      cb->stat = -1;
    }
    else
    {
      cb->stat = 2;
    }
  }
}

// 0x2263b80
static void EndBlock(sdfPacDecodeCb_t *cb) {
  sdfPacDecodeResrcHandle_t *p_resrcTail;
  s32 v4;
  sdfPacDecodeResrcHandle_t *p_resrcHead;
  sdfPacDecodeResrcHandle_t *resrcTail;
  sdfPacDecodeResrcHandle_t *resrcHead;
  sdfPacDecodeResrcHandle_t *v8;

  p_resrcTail = &cb->resrcTail;
  v4 = (cb->callback->invoke_impl)(cb->callback->method_code, cb, 1, cb->resrcTail->header, cb->callback->method);
  if (v4 == 1)
  {
    cb->stat = -1;
  }
  else
  {
    if (v4 == 4)
    {
      resrcHead = cb->resrcHead;
      resrcTail = cb->resrcTail;
      p_resrcHead = &cb->resrcHead;
      if (resrcHead == resrcTail)
      {
        p_resrcHead = 0;
      }
      else
      {
        do
        {
          v8 = resrcHead;
          resrcHead = resrcHead->next;
        }
        while (resrcHead != resrcTail);
        p_resrcTail = &v8->next;
      }
      p_resrcTail = 0;
    }
    cb->stat = 0;
  }
}

// 0x2263c40
SDF_PAC_STAT sdfPacDecode(sdfPacDecodeCb_t *cb, void *data, s32 length) {
  s64 naturalAligment;
  void *p_primalData;
  Project_libsdf_sdfResource_c *klass;
  void *v11;
  void *primalData;
  s64 v14;
  void *v15;
  UnityEngine_Object_c *v17;
  s64 v18;
  sdfPacStdBlockHeader_t *v19;
  sdfPacStdBlockHeader_t *v20;
  s64 v21;
  u8 *v22;
  sdfPacDecodeResrcHandle_t *resrcTail;
  sdfPacDecodeResrcHandle_t *v25;
  sdfBinary *v26;
  sdfBinary *New;
  sdfBinary *p_srcData;
  s32 v30;
  sdfBinary *srcData;
  s32 v32;
  s32 rest;
  s32 v34;
  sdfBinary *v35;
  s32 point;
  s32 v37;
  s32 v38;
  void *v40;

  if (!data)
  {
    cb->primalData = 0;
    primalData = cb->primalData;
    goto LABEL_10;
  }
  if (data->klass->_2.naturalAligment < (u32)naturalAligment)
  {
    cb->primalData = 0;
    p_primalData = &cb->primalData;
    klass = data->klass;
    if (data->klass->_2.naturalAligment >= (u32)naturalAligment)
      goto LABEL_6;
    goto LABEL_43;
  }
  if (data->klass->_2.typeHierarchy[naturalAligment - 1] == Project_libsdf_sdfResourcePrimal)
    v40 = data;
  else
    v40 = 0;
  cb->primalData = (void *)v40;
  p_primalData = &cb->primalData;
  klass = data->klass;
  if (data->klass->_2.naturalAligment < (u32)naturalAligment)
  {
LABEL_43:
    primalData = p_primalData;
    goto LABEL_10;
  }
LABEL_6:
  if (klass->_2.typeHierarchy[naturalAligment - 1] == Project_libsdf_sdfResourcePrimal)
    v11 = data;
  else
    v11 = 0;
  primalData = p_primalData;
LABEL_10:
  if (op_Equality(primalData, 0, 0))
  {
    {
      if (data->klass->_2.typeHierarchy[v14 - 1] == Project_libsdf_sdfResourcePack)
        v15 = data;
      else
        v15 = 0;
      goto LABEL_15;
    }
    else
    {
      v15 = 0;
      goto LABEL_15;
    }
LABEL_15:
    if (op_Inequality(v15, 0, 0))
    {
      v17 = v15[1].klass;
      if (SLODWORD(v17->_1.namespaze) >= 1)
      {
        v18 = 0;
        do
        {
          v19 = *((sdfPacStdBlockHeader_t ***)&v17->_1.byval_arg.data + v18);
          if (v19)
          {
            v20 = v19;
            if (LOBYTE(v19[7].magicCode) >= (u32)v21 && *((pbResourceUnit **)v20[5].klass + v21 - 1) == pbResourceUnit)
            {
              v22 = (v20[10].monitor)(*((u64 *)&v17->_1.byval_arg.data + v18), *(u64 *)&v20[10].fileType);
              NewResrc(cb, v19[2]);
              resrcTail = cb->resrcTail;
              resrcTail->unit = (pbResourceUnit *)v19;
              if (v22)
              {
                v25 = cb->resrcTail;
                v26 = Allocate(sdfBinary);
                _ctor_36176832(v26, v22, 0);
                v25->ptr = v26;
              }
            }
          }
          ++v18;
        }
        while (v18 < SLODWORD(v17->_1.namespaze));
      }
    }
    return -1;
  }
  New = GetNew(cb->primalData->_bin, 1, 0, 0);
  cb->srcData = New;
  p_srcData = &cb->srcData;
  set_Length(cb->srcData, length, 0);
  v30 = get_Length(cb->srcData, 0);
  srcData = cb->srcData;
  if (v30 - srcData->point >= 1)
  {
    do
    {
      switch (cb->stat)
      {
        case 0xFF:
          return -1;
        case 0:
          NewBlock(cb);
          break;
        case 1:
          rest = cb->rest;
          v34 = get_Length(srcData, 0);
          v35 = cb->srcData;
          point = v35->point;
          if (rest > v34 - point)
          {
            v37 = get_Length(v35, 0);
            v35 = p_srcData;
            point = p_srcData->point;
            rest = v37 - point;
          }
          v35->point = point + rest;
          v38 = cb->rest - rest;
          cb->rest = v38;
          if (!v38)
            cb->stat = 0;
          break;
        case 2:
          (cb->decoder->invoke_impl)(cb->decoder->method_code, cb, cb->decoder->method);
          break;
        default:
          break;
      }
      v32 = get_Length(p_srcData, 0);
      srcData = p_srcData;
    }
    while (v32 - p_srcData->point > 0);
  }
  return cb->stat;
}

// 0x2264080
static sdfPacDecodeResrcHandle_t *NewResrc(sdfPacDecodeCb_t *cb, sdfPacStdBlockHeader_t *hdr) {
  Il2CppObject *v5;
  sdfPacDecodeResrcHandle_t *p_resrcTail;
  sdfPacDecodeResrcHandle_t *resrcTail;
  sdfPacDecodeResrcHandle_t *p_fields;
  Il2CppObject **v9;

  v5 = Allocate(sdfPacDecodeResrcHandle_t);
  _ctor(v5, 0);
  v5[1].monitor = cb;
  v5[2].monitor = hdr;
  resrcTail = cb->resrcTail;
  p_resrcTail = &cb->resrcTail;
  p_fields = &resrcTail->fields;
  if (resrcTail)
    v9 = p_fields;
  else
    v9 = (p_resrcTail - 1);
  *v9 = v5;
  p_resrcTail = (sdfPacDecodeResrcHandle_t *)v5;
  return (sdfPacDecodeResrcHandle_t *)v5;
}

// 0x2264190
sdfPacDecodeResrcHandle_t *sdfPacFreeResrc(sdfPacDecodeResrcHandle_t *resrc) {
  return resrc->next;
}

// 0x22641a0
static SDF_PAC_CB_ACT StdCallback(sdfPacDecodeCb_t *cb, SDF_PAC_CB_CAUSE cause, sdfPacStdBlockHeader_t *hdr) {
  s32 result;
  intptr_t *v8;
  sdfBinary *srcData;
  void *v10;
  u32 pixelFormat;
  s32 v13;
  s32 v14;
  sdfPacDecodeFunc_t v15;
  s32 v17;
  s32 CLUTFormat;
  s32 v19;
  s32 v20;
  s32 v21;
  s32 v22;
  s32 v23;

  if (cause)
    return 0;
  switch (hdr->fileType)
  {
    case 1u:
      v8 = &Method_Project_libsdf_sdfPac_EndBlock__;
      goto LABEL_19;
    case 2u:
      srcData = cb->srcData;
      v10 = Allocate(Project_libsdf_sdfPacTmxHeader_t);
      _ctor_36062576(v10, srcData);
      pixelFormat = v10->pixelFormat;
      if (pixelFormat > 0xA)
      {
        if (pixelFormat == 19)
        {
          CLUTFormat = v10->CLUTFormat;
          if (CLUTFormat == 10 || CLUTFormat == 2)
          {
            v14 = 8;
            v13 = 512;
          }
          else if (v10->CLUTFormat)
          {
            v13 = 0;
            v14 = 8;
          }
          else
          {
            v14 = 8;
            v13 = 1024;
          }
        }
        else
        {
          if (pixelFormat != 20)
          {
            v13 = 0;
            goto LABEL_39;
          }
          v17 = v10->CLUTFormat;
          if (v17 == 10 || v17 == 2)
          {
            v14 = 4;
            v13 = 32;
          }
          else if (v10->CLUTFormat)
          {
            v13 = 0;
            v14 = 4;
          }
          else
          {
            v14 = 4;
            v13 = 64;
          }
        }
LABEL_37:
        v19 = v10->numOfMipmap + 1;
        LOWORD(v20) = v10->width;
        LOWORD(v21) = v10->height;
        do
        {
          v22 = (s16)v21;
          v23 = v14 * (s16)v20;
          v20 = (s16)v20 >> 1;
          v21 = (s16)v21 >> 1;
          --v19;
          v13 += (v23 * v22) >> 3;
        }
        while (v19);
      }
      else
      {
        v13 = 0;
        v14 = 24;
        switch (v10->pixelFormat)
        {
          case 0u:
            v13 = 0;
            v14 = 32;
            goto LABEL_37;
          case 1u:
            goto LABEL_37;
          case 2u:
          case 0xAu:
            v13 = 0;
            v14 = 16;
            goto LABEL_37;
          default:
            break;
        }
      }
LABEL_39:
      cb->rest = v13;
      result = 2;
      break;
    case 3u:
    case 4u:
    case 5u:
    case 7u:
      return 3;
    case 6u:
      v8 = &Method_Project_libsdf_sdfPac_ModelDecoderEndFunc__;
      goto LABEL_19;
    case 8u:
      v8 = &Method_Project_libsdf_sdfPac_MotionDecoderEndFunc__;
LABEL_19:
      MemDecoderFuncInit(cb, hdr);
      v15 = Allocate(sdfPacDecodeFunc_t);
      _ctor(v15, 0, *v8);
      cb->onEnd = v15;
      return 0;
    case 9u:
      v13 = 4 * ReadS32(cb->srcData, 0);
      goto LABEL_39;
    default:
      if (hdr->fileType == 255)
        return 1;
      else
        return 3;
  }
  return result;
}

// 0x22648c0
static void MemDecoderFunc(sdfPacDecodeCb_t *cb) {
  s32 rest;
  s32 Length;
  sdfBinary *srcData;
  s32 v6;
  sdfPacDecodeResrcHandle_t *resrcTail;
  u8 *Array;
  sdfBinary *v9;
  s32 v10;

  rest = cb->rest;
  Length = get_Length(cb->srcData, 0);
  srcData = cb->srcData;
  if (rest > Length - srcData->point)
  {
    v6 = get_Length(srcData, 0);
    srcData = cb->srcData;
    rest = v6 - srcData->point;
  }
  if (rest)
  {
    resrcTail = cb->resrcTail;
    Array = ReadArray(srcData, rest, 0);
    v9 = Allocate(sdfBinary);
    _ctor_36176832(v9, Array, 0);
    resrcTail->ptr = v9;
    v10 = cb->rest - rest;
    cb->rest = v10;
    if (!v10)
      (cb->onEnd->invoke_impl)(cb->onEnd->method_code, cb, cb->onEnd->method);
  }
}

// 0x22649d0
static void MemDecompDecoderFunc(sdfPacDecodeCb_t *cb) {
  if (sdfExec(cb->resrcTail->ptr->data, cb->srcData))
    (cb->onEnd->invoke_impl)(cb->onEnd->method_code, cb, cb->onEnd->method);
}

// 0x2264a30
static void MemStayDecoderFunc(sdfPacDecodeCb_t *cb) {
  s32 rest;
  s32 Length;
  sdfBinary *srcData;
  s32 point;
  s32 v7;
  s32 v8;

  rest = cb->rest;
  Length = get_Length(cb->srcData, 0);
  srcData = cb->srcData;
  point = srcData->point;
  if (rest > Length - point)
  {
    v7 = get_Length(srcData, 0);
    srcData = cb->srcData;
    point = srcData->point;
    rest = v7 - point;
  }
  if (rest)
  {
    srcData->point = point + rest;
    v8 = cb->rest - rest;
    cb->rest = v8;
    if (!v8)
      (cb->onEnd->invoke_impl)(cb->onEnd->method_code, cb, cb->onEnd->method);
  }
}

// 0x2264ad0
static void MemDecoderFuncInit(sdfPacDecodeCb_t *cb, sdfPacStdBlockHeader_t *hdr) {
  sdfPacDecodeResrcHandle_t *v5;
  u32 realSize;
  sdfPacDecodeResrcHandle_t *v7;
  sdfPacDecodeFunc_t v8;
  sdfPacDecodeFunc_t v10;
  intptr_t *v11;
  sdfBinary *New;
  intptr_t v15;
  u8 *v16;
  sdfBinary *v17;

  v5 = NewResrc(cb, hdr);
  realSize = hdr->realSize;
  v7 = v5;
  if (realSize)
    goto LABEL_3;
  realSize = hdr->size - 16;
  if ((cb->flag & 1) == 0)
    goto LABEL_4;
LABEL_9:
  New = GetNew(cb->srcData, 1, 0, 0);
  v7->ptr = New;
  v8 = Allocate(sdfPacDecodeFunc_t);
  v15 = Method_Project_libsdf_sdfPac_MemStayDecoderFunc__;
  v10 = v8;
  goto LABEL_12;
LABEL_3:
  if ((cb->flag & 1) != 0)
    goto LABEL_9;
LABEL_4:
  if ((hdr->compression & 0xF) == 1)
  {
    v16 = NewSpecific(byte, realSize);
    v17 = Allocate(sdfBinary);
    _ctor_36176832(v17, v16, 0);
    v7->ptr = v17;
    v8 = Allocate(sdfPacDecodeFunc_t);
    v10 = v8;
    v11 = &Method_Project_libsdf_sdfPac_MemDecompDecoderFunc__;
  }
  else
  {
    if ((hdr->compression & 0xF) != 0)
      return;
    v8 = Allocate(sdfPacDecodeFunc_t);
    v10 = v8;
    v11 = &Method_Project_libsdf_sdfPac_MemDecoderFunc__;
  }
  v15 = *v11;
LABEL_12:
  _ctor(v8, 0, v15);
  cb->decoder = v10;
}

// 0x22644d0
static void MemDecoderInit(sdfPacDecodeCb_t *cb, sdfPacStdBlockHeader_t *hdr) {
  sdfPacDecodeFunc_t v5;

  MemDecoderFuncInit(cb, hdr);
  v5 = Allocate(sdfPacDecodeFunc_t);
  _ctor(v5, 0);
  cb->onEnd = v5;
}

// 0x2264de0
static void ModelDecoderEndFunc(sdfPacDecodeCb_t *cb) {
  sdfPacDecodeResrcHandle_t *p_resrcTail;
  s32 v4;
  sdfPacDecodeResrcHandle_t *p_resrcHead;
  sdfPacDecodeResrcHandle_t *resrcTail;
  sdfPacDecodeResrcHandle_t *resrcHead;
  sdfPacDecodeResrcHandle_t *v8;

  p_resrcTail = &cb->resrcTail;
  ResetStart(cb->resrcTail->ptr, 0, 16, 0);
  v4 = (cb->callback->invoke_impl)(cb->callback->method_code, cb, 1, p_resrcTail->header, cb->callback->method);
  if (v4 == 1)
  {
    cb->stat = -1;
  }
  else
  {
    if (v4 == 4)
    {
      resrcHead = cb->resrcHead;
      resrcTail = cb->resrcTail;
      p_resrcHead = &cb->resrcHead;
      if (resrcHead == resrcTail)
      {
        p_resrcHead = 0;
      }
      else
      {
        do
        {
          v8 = resrcHead;
          resrcHead = resrcHead->next;
        }
        while (resrcHead != resrcTail);
        p_resrcTail = &v8->next;
      }
      p_resrcTail = 0;
    }
    cb->stat = 0;
  }
}

// 0x2264780
static void ModelDecoderInit(sdfPacDecodeCb_t *cb, sdfPacStdBlockHeader_t *hdr) {
  sdfPacDecodeFunc_t v5;

  MemDecoderFuncInit(cb, hdr);
  v5 = Allocate(sdfPacDecodeFunc_t);
  _ctor(v5, 0);
  cb->onEnd = v5;
}

// 0x2264eb0
static void MotionDecoderEndFunc(sdfPacDecodeCb_t *cb) {
  sdfPacDecodeResrcHandle_t *p_resrcTail;
  sdfPacDecodeResrcHandle_t *resrcTail;
  sdfBinary *ptr;
  sdfPacMotionHeader_t *v6;
  s32 v7;
  sdfPacDecodeResrcHandle_t *p_resrcHead;
  sdfPacDecodeResrcHandle_t *v9;
  sdfPacDecodeResrcHandle_t *resrcHead;
  sdfPacDecodeResrcHandle_t *v11;

  p_resrcTail = &cb->resrcTail;
  resrcTail = cb->resrcTail;
  ptr = resrcTail->ptr;
  v6 = Allocate(sdfPacMotionHeader_t);
  ptr->point += 8;
  v6->group = ReadU16(ptr, 0);
  v6->playGroup = ReadU16(ptr, 0);
  v6->firstMotion = ReadS16(ptr, 0);
  v6->flags = ReadU16(ptr, 0);
  resrcTail->extHeader = (void *)v6;
  ResetStart(resrcTail->ptr, 1, 0, 0);
  v7 = (cb->callback->invoke_impl)(cb->callback->method_code, cb, 1, cb->resrcTail->header, cb->callback->method);
  if (v7 == 1)
  {
    cb->stat = -1;
  }
  else
  {
    if (v7 == 4)
    {
      resrcHead = cb->resrcHead;
      v9 = cb->resrcTail;
      p_resrcHead = &cb->resrcHead;
      if (resrcHead == v9)
      {
        p_resrcHead = 0;
      }
      else
      {
        do
        {
          v11 = resrcHead;
          resrcHead = resrcHead->next;
        }
        while (resrcHead != v9);
        p_resrcTail = &v11->next;
      }
      p_resrcTail = 0;
    }
    cb->stat = 0;
  }
}

// 0x2264820
static void MotionDecoderInit(sdfPacDecodeCb_t *cb, sdfPacStdBlockHeader_t *hdr) {
  sdfPacDecodeFunc_t v5;

  MemDecoderFuncInit(cb, hdr);
  v5 = Allocate(sdfPacDecodeFunc_t);
  _ctor(v5, 0);
  cb->onEnd = v5;
}
