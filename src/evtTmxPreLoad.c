#include "types.h"
#include "dds3kernelcore.h"
#include "evttmxpreload.h"
#include "file.h"
#include "kernel.h"
#include "sdftex.h"

typedef enum {
    EVT_TMXPRELOAD_STAT_NONE = 0,
    EVT_TMXPRELOAD_STAT_LOAD_NOW = 1,
    EVT_TMXPRELOAD_STAT_LOAD_END = 2,
} EVT_TMXPRELOAD_STAT;

typedef enum {
    EVT_TMXPRELOAD_FLAG_NONE = 0,
    EVT_TMXPRELOAD_FLAG_END = 1,
} EVT_TMXPRELOAD_FLAG;

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct evtTmxPreLoadQue_t evtTmxPreLoadQue_t;
typedef struct evtTmxPreLoad_t evtTmxPreLoad_t;
typedef struct fileHandle_t fileHandle_t;
typedef struct sdfIVector2_t sdfIVector2_t;

struct evtTmxPreLoadQue_t {
    u32 UID[2];
    s32 ReqFrame[2];
    bool Flag[2];
    s32 Cnt;
};

struct evtTmxPreLoad_t {
    EVT_TMXPRELOAD_STAT Stat;
    EVT_TMXPRELOAD_FLAG Flag;
    s32 LoadCnt;
    sdfIVector2_t *MaskOfs[2];
    u32 UID[2];
    u32 ReqFrame[2];
    evtTmxPreLoadQue_t *Que;
};

void *pBgTbl;
static dds3ProcessID_t *TmxPreLoadPID;

static evtTmxPreLoad_t *Init(void);
static void Destroy(dds3ProcessID_t *PID);
static s32 GetIndexFromUID(evtTmxPreLoad_t *pData, u32 UID);
static void EndCallback(fileHandle_t *FH, void *pParam);
static s32 GetTblIndex(s32 EventNo);
static void UpdateQue(evtTmxPreLoadQue_t *pQue);
static s32 SelectFreeTex(evtTmxPreLoad_t *pData);
static void Start(evtTmxPreLoad_t *pData);
static dds3ProcessFunc_t Process(dds3ProcessID_t *PID);

// 0x19e22e0
static evtTmxPreLoad_t *Init(void) {
  evtTmxPreLoad_t *v1;

  v1 = (evtTmxPreLoad_t *)Allocate(evtTmxPreLoad_t);
  _ctor(v1);
  return v1;
}

// 0x19e2490
static void Destroy(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  void *data;
  void *v7;
  void *v9;
  void *v11;
  void *v12;
  void *v14;
  void *v15;
  void *v16;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  data = ProcessData[2].klass->_1.byval_arg.data;
  if (!op_Inequality(ProcessData[2].klass->_1.byval_arg.data, 0, 0))
    goto LABEL_11;
  goto LABEL_9001;
  if (!op_Inequality(data, 0, 0))
  {
LABEL_11:
    v7 = *((void *)ProcessData[2].monitor + 4);
    goto LABEL_12;
  }
LABEL_9001:
  v14 = ProcessData[2].klass->_1.byval_arg.data;
  sdfTexFree(v14);
  v7 = *((void *)ProcessData[2].monitor + 4);
LABEL_12:
  if (!op_Inequality(v7, 0, 0))
  {
    v9 = *(void *)&ProcessData[2].klass->_1.byval_arg.bits;
    goto LABEL_14;
  }
  v15 = *((void *)ProcessData[2].monitor + 4);
  sdfTexFree(v15);
  v9 = *(void *)&ProcessData[2].klass->_1.byval_arg.bits;
LABEL_14:
  if (!op_Inequality(v9, 0, 0))
  {
    v11 = *((void *)ProcessData[2].monitor + 5);
    goto LABEL_16;
  }
  v16 = *(void *)&ProcessData[2].klass->_1.byval_arg.bits;
  sdfTexFree(v16);
  v11 = *((void *)ProcessData[2].monitor + 5);
LABEL_16:
  if (op_Inequality(v11, 0, 0))
  {
    v12 = *((void *)ProcessData[2].monitor + 5);
    sdfTexFree(v12);
  }
  TmxPreLoadPID = 0;
}

// 0x19e2790
static s32 GetIndexFromUID(evtTmxPreLoad_t *pData, u32 UID) {
  u32 *v3;

  v3 = pData->UID;
  if (v3[0] == UID)
    return 0;
  if (v3[1] == UID)
    return 1;
  return -1;
}

// 0x19e27c0
static void EndCallback(fileHandle_t *FH, void *pParam) {
  void *topPtr;
  Project_fileHandle_t_Parm_c *klass;
  s32 monitor;
  char *v11;

  topPtr = FH->topPtr;
  if (!topPtr)
  {
    klass = pParam[2].klass;
    monitor = pParam[1].monitor;
    goto LABEL_14;
  }
  klass = pParam[2].klass;
  monitor = pParam[1].monitor;
  QueryInterface(topPtr, *((void **)klass->_1.image + 8));
LABEL_14:
  v11 = (char *)klass + 8 * monitor - 8;
  *((u64 *)v11 + 4) = topPtr;
  fileHandleFree(FH);
  LODWORD(pParam[1].klass) = (s64)pParam[1].klass & 0xFFFFFFFC | 2;
}

// 0x19e2930
static s32 GetTblIndex(s32 EventNo) {
  void *Tbl;
  s32 v4;

  Tbl = pBgTbl->Tbl;
  if (Tbl->_size < 1)
    return -1;
  v4 = 0;
  while (LODWORD(_get_Item(Tbl, v4)[1].klass) != EventNo)
  {
    ++v4;
    Tbl = pBgTbl->Tbl;
    if (v4 >= Tbl->_size)
      return -1;
  }
  return v4;
}

// 0x19e2a30
s32 evtGetFileNums(s32 EventNo) {
  void *Tbl;
  s32 v4;

  Tbl = pBgTbl->Tbl;
  if (Tbl->_size < 1)
    return 1;
  v4 = 0;
  while (LODWORD(_get_Item(Tbl, v4)[1].klass) != EventNo)
  {
    ++v4;
    Tbl = pBgTbl->Tbl;
    if (v4 >= Tbl->_size)
      return 1;
  }
  return *((u32 *)_get_Item(pBgTbl->Tbl, v4)[1].monitor + 6);
}

// 0x19e2b60
static void UpdateQue(evtTmxPreLoadQue_t *pQue) {
  bool *Flag;
  s32 Cnt;
  s32 *ReqFrame;

  Flag = pQue->Flag;
  if (Flag[1])
  {
    Cnt = pQue->Cnt;
    Flag[1] = 0;
    pQue->Cnt = Cnt - 1;
  }
  if (Flag[0])
  {
    ReqFrame = pQue->ReqFrame;
    pQue->UID[0] = pQue->UID[1];
    ReqFrame[0] = ReqFrame[1];
    *(u16 *)Flag = 0;
    --pQue->Cnt;
  }
}

// 0x19e2bb0
static s32 SelectFreeTex(evtTmxPreLoad_t *pData) {
  s64 LoadCnt;
  evtTmxPreLoadQue_t *Que;
  s64 Cnt;
  u32 *UID;
  u32 *v6;
  s64 v7;
  int32x4_t *v8;
  u32 *m_Items;
  u32 v10;
  s64 v11;
  u32 v12;
  int32x4_t v13;
  s64 v14;
  int8x16_t v15;
  int8x16_t v16;
  s64 v17;
  int8x16_t v18;
  int8x16_t v19;
  int32x4_t *v20;
  int8x16_t v21;
  int32x4_t v22;
  int32x4_t v23;
  int8x8_t v24;
  int32x4_t *v25;
  s64 v26;
  int32x4_t v27;
  int32x4_t v28;
  u32 *v29;
  s64 v30;
  s32 v31;

  LoadCnt = (u32)pData->LoadCnt;
  if ((s32)LoadCnt >= 1)
  {
    Que = pData->Que;
    Cnt = (u32)Que->Cnt;
    if ((s32)Cnt >= 1)
    {
      UID = Que->UID;
      v6 = pData->UID;
      v7 = 0;
      v8 = &UID[32];
      m_Items = UID;
      do
      {
        v10 = v6[v7];
        if ((u32)Cnt >= 8)
        {
          v13 = vdupq_n_s32(v10);
          if ((u32)Cnt < 0x40)
          {
            v12 = 0;
            v14 = 0;
LABEL_12:
            v24.n64_u64[0] = vdup_n_s8(v12).n64_u64[0];
            v25 = &m_Items[v14];
            v26 = v14 - ((u32)Cnt & 0xFFFFFFF8);
            do
            {
              v27 = *v25;
              v28 = v25[1];
              v25 += 2;
              v26 += 8;
              v24.n64_u64[0] = vorr_s8(vmovn_s16(vuzp1q_s16(vceqq_s32(v27, v13), vceqq_s32(v28, v13))), v24).n64_u64[0];
            }
            while (v26);
            v11 = Cnt & 0x7FFFFFF8;
            LOBYTE(v12) = vmaxv_u8(vcltz_s8(vshl_n_s8(v24, 7u))) & 1;
            if ((Cnt & 0xFFFFFFF8) == Cnt)
              goto LABEL_17;
            goto LABEL_15;
          }
          v15 = 0u;
          v16 = 0u;
          v17 = (u32)Cnt & 0xFFFFFFC0;
          v18 = 0u;
          v19 = 0u;
          v20 = v8;
          do
          {
            v17 -= 64;
            v15 = vorrq_s8(vuzp1q_s8(vuzp1q_s16(vceqq_s32(v20[-8], v13), vceqq_s32(v20[-7], v13)), vuzp1q_s16(vceqq_s32(v20[-6], v13), vceqq_s32(v20[-5], v13))), v15);
            v16 = vorrq_s8(vuzp1q_s8(vuzp1q_s16(vceqq_s32(v20[-4], v13), vceqq_s32(v20[-3], v13)), vuzp1q_s16(vceqq_s32(v20[-2], v13), vceqq_s32(v20[-1], v13))), v16);
            v18 = vorrq_s8(vuzp1q_s8(vuzp1q_s16(vceqq_s32(*v20, v13), vceqq_s32(v20[1], v13)), vuzp1q_s16(vceqq_s32(v20[2], v13), vceqq_s32(v20[3], v13))), v18);
            v21 = vuzp1q_s16(vceqq_s32(v20[4], v13), vceqq_s32(v20[5], v13));
            v23 = v20[6];
            v22 = v20[7];
            v20 += 16;
            v19 = vorrq_s8(vuzp1q_s8(v21, vuzp1q_s16(vceqq_s32(v23, v13), vceqq_s32(v22, v13))), v19);
          }
          while (v17);
          v12 = vmaxvq_u8(vcltzq_s8(vshlq_n_s8(vorrq_s8(vorrq_s8(v15, v16), vorrq_s8(v18, v19)), 7u))) & 1;
          if ((Cnt & 0xFFFFFFC0) == Cnt)
            goto LABEL_17;
          v14 = Cnt & 0x7FFFFFC0;
          v11 = (u32)Cnt & 0xFFFFFFC0;
          if ((Cnt & 0x38) != 0)
            goto LABEL_12;
        }
        else
        {
          v11 = 0;
          LOBYTE(v12) = 0;
        }
LABEL_15:
        v29 = &m_Items[v11];
        v30 = Cnt - v11;
        do
        {
          v31 = *v29++;
          --v30;
          LOBYTE(v12) = (v31 == v10) | v12;
        }
        while (v30);
LABEL_17:
        if ((v12 & 1) == 0)
          return v7;
        ++v7;
      }
      while (v7 != LoadCnt);
    }
  }
  LODWORD(v7) = 0;
  return v7;
}

// 0x19e2dd0
static void Start(evtTmxPreLoad_t *pData) {
  evtTmxPreLoadQue_t *Que;
  s64 v4;
  s64 i;
  s64 v6;
  u32 v7;
  void *Tbl;
  s32 v9;
  u32 *UID;
  Il2CppObject *v11;
  char *v12;
  Il2CppObject *Item;
  char *v14;
  s32 LoadCnt;
  evtTmxPreLoadQue_t *v16;
  s64 Cnt;
  u32 *v18;
  u32 *v19;
  u32 v20;
  s64 v21;
  u32 v22;
  int32x4_t v23;
  int8x16_t v24;
  int32x4_t *v25;
  s64 v26;
  int8x16_t v27;
  int8x16_t v28;
  int8x16_t v29;
  int8x16_t v30;
  int32x4_t v31;
  int32x4_t v32;
  int8x8_t v33;
  s64 v34;
  int32x4_t *v35;
  s64 v36;
  int32x4_t *v37;
  int32x4_t v38;
  int32x4_t v39;
  s64 v40;
  u32 *v41;
  s32 v42;
  u32 v43;
  s64 v44;
  s64 v45;
  int32x4_t v46;
  int8x16_t v47;
  int32x4_t *v48;
  s64 v49;
  int8x16_t v50;
  int8x16_t v51;
  int8x16_t v52;
  int8x16_t v53;
  int32x4_t v54;
  int32x4_t v55;
  int8x8_t v56;
  s64 v57;
  s64 v58;
  int32x4_t *v59;
  int32x4_t v60;
  int32x4_t v61;
  s64 v62;
  u32 *v63;
  s32 v64;
  s64 v65;
  void *v66;
  void *v67;
  void *v68;
  void *v69;
  s64 v70;
  sdfIVector2_t v71;
  s32 v72;
  sdfIVector2_t v73;
  s32 v74;
  s64 v75;
  char *v76;
  char *v77;
  void *Tex;
  void *v79;
  void *MaskTex;
  void *v81;
  Il2CppClass **v82;
  Il2CppClass **v83;
  u32 *ReqFrame;
  fileEndCallback_t v85;
  bool *Flag;
  s32 *v87;
  char *v89;
  char *v90;
  u32 v91;
  s32 data;

  Que = pData->Que;
  LODWORD(v4) = Que->Cnt;
  if ((u32)v4)
  {
    if ((s32)v4 >= 1)
    {
      for (i = 0; i < v4; ++i)
      {
        v7 = Que->UID[i];
        v91 = Que->ReqFrame[i];
        Tbl = pBgTbl->Tbl;
        if (Tbl->_size < 1)
          goto LABEL_9;
        v9 = 0;
        while (LODWORD(_get_Item(Tbl, v9)[1].klass) != HIWORD(v7))
        {
          ++v9;
          Tbl = pBgTbl->Tbl;
          if (v9 >= Tbl->_size)
            goto LABEL_9;
        }
        UID = pData->UID;
        if (UID[0] == v7)
        {
          v6 = 0;
        }
        else
        {
          if (UID[1] != v7)
          {
            if ((pData->Stat & 1) != 0)
              goto LABEL_9;
            data = HIWORD(v7);
            v11 = Box(s32, &data);
            v12 = Format("e{0}", v11, 0);
            Item = _get_Item(pBgTbl->Tbl, v9);
            v14 = *((char **)Item[1].monitor + (u16)v7 + 4);
            LoadCnt = pData->LoadCnt;
            if (LoadCnt == 2)
            {
              v16 = pData->Que;
              v90 = *((char **)Item[1].monitor + (u16)v7 + 4);
              Cnt = (u32)v16->Cnt;
              if ((s32)Cnt < 1)
                goto LABEL_51;
              v18 = pData->UID;
              v19 = v16->UID;
              v20 = v18[0];
              if ((u32)Cnt < 8)
              {
                v21 = 0;
                LOBYTE(v22) = 0;
                goto LABEL_34;
              }
              v23 = vdupq_n_s32(v20);
              if ((u32)Cnt >= 0x40)
              {
                v24 = 0u;
                v21 = (u32)Cnt & 0xFFFFFFC0;
                v25 = &v19[32];
                v26 = v21;
                v27 = 0u;
                v28 = 0u;
                v29 = 0u;
                do
                {
                  v26 -= 64;
                  v27 = vorrq_s8(vuzp1q_s8(vuzp1q_s16(vceqq_s32(v25[-8], v23), vceqq_s32(v25[-7], v23)), vuzp1q_s16(vceqq_s32(v25[-6], v23), vceqq_s32(v25[-5], v23))), v27);
                  v28 = vorrq_s8(vuzp1q_s8(vuzp1q_s16(vceqq_s32(v25[-4], v23), vceqq_s32(v25[-3], v23)), vuzp1q_s16(vceqq_s32(v25[-2], v23), vceqq_s32(v25[-1], v23))), v28);
                  v29 = vorrq_s8(vuzp1q_s8(vuzp1q_s16(vceqq_s32(*v25, v23), vceqq_s32(v25[1], v23)), vuzp1q_s16(vceqq_s32(v25[2], v23), vceqq_s32(v25[3], v23))), v29);
                  v30 = vuzp1q_s16(vceqq_s32(v25[4], v23), vceqq_s32(v25[5], v23));
                  v32 = v25[6];
                  v31 = v25[7];
                  v25 += 16;
                  v24 = vorrq_s8(vuzp1q_s8(v30, vuzp1q_s16(vceqq_s32(v32, v23), vceqq_s32(v31, v23))), v24);
                }
                while (v26);
                v22 = vmaxvq_u8(vcltzq_s8(vshlq_n_s8(vorrq_s8(vorrq_s8(v27, v28), vorrq_s8(v29, v24)), 7u))) & 1;
                if (v21 != Cnt)
                {
                  if ((Cnt & 0x38) == 0)
                    goto LABEL_34;
                  goto LABEL_31;
                }
              }
              else
              {
                v22 = 0;
                v21 = 0;
LABEL_31:
                v33.n64_u64[0] = vdup_n_s8(v22).n64_u64[0];
                v34 = v21;
                v35 = ((char *)v19 + 4 * v21);
                v21 = (u32)Cnt & 0xFFFFFFF8;
                v36 = v34 - v21;
                v37 = v35 + 2;
                do
                {
                  v38 = *v37;
                  v39 = v37[1];
                  v37 += 2;
                  v36 += 8;
                  v33.n64_u64[0] = vorr_s8(vmovn_s16(vuzp1q_s16(vceqq_s32(v38, v23), vceqq_s32(v39, v23))), v33).n64_u64[0];
                }
                while (v36);
                LOBYTE(v22) = vmaxv_u8(vcltz_s8(vshl_n_s8(v33, 7u))) & 1;
                if (v21 != Cnt)
                {
LABEL_34:
                  v40 = Cnt - v21;
                  v41 = &v19[v21];
                  do
                  {
                    v42 = *v41++;
                    --v40;
                    LOBYTE(v22) = (v42 == v20) | v22;
                  }
                  while (v40);
                }
              }
              if ((v22 & 1) == 0)
                goto LABEL_51;
              v43 = v18[1];
              if ((u32)Cnt < 8)
              {
                v44 = 0;
                LOBYTE(v45) = 0;
                goto LABEL_48;
              }
              v46 = vdupq_n_s32(v43);
              if ((u32)Cnt >= 0x40)
              {
                v47 = 0u;
                v44 = (u32)Cnt & 0xFFFFFFC0;
                v48 = &v19[32];
                v49 = v44;
                v50 = 0u;
                v51 = 0u;
                v52 = 0u;
                do
                {
                  v49 -= 64;
                  v50 = vorrq_s8(vuzp1q_s8(vuzp1q_s16(vceqq_s32(v48[-8], v46), vceqq_s32(v48[-7], v46)), vuzp1q_s16(vceqq_s32(v48[-6], v46), vceqq_s32(v48[-5], v46))), v50);
                  v51 = vorrq_s8(vuzp1q_s8(vuzp1q_s16(vceqq_s32(v48[-4], v46), vceqq_s32(v48[-3], v46)), vuzp1q_s16(vceqq_s32(v48[-2], v46), vceqq_s32(v48[-1], v46))), v51);
                  v52 = vorrq_s8(vuzp1q_s8(vuzp1q_s16(vceqq_s32(*v48, v46), vceqq_s32(v48[1], v46)), vuzp1q_s16(vceqq_s32(v48[2], v46), vceqq_s32(v48[3], v46))), v52);
                  v53 = vuzp1q_s16(vceqq_s32(v48[4], v46), vceqq_s32(v48[5], v46));
                  v55 = v48[6];
                  v54 = v48[7];
                  v48 += 16;
                  v47 = vorrq_s8(vuzp1q_s8(v53, vuzp1q_s16(vceqq_s32(v55, v46), vceqq_s32(v54, v46))), v47);
                }
                while (v49);
                LODWORD(v45) = vmaxvq_u8(vcltzq_s8(vshlq_n_s8(vorrq_s8(vorrq_s8(v50, v51), vorrq_s8(v52, v47)), 7u)))
                             & 1;
                if (v44 != Cnt)
                {
                  if ((Cnt & 0x38) == 0)
                    goto LABEL_48;
                  goto LABEL_45;
                }
              }
              else
              {
                LODWORD(v45) = 0;
                v44 = 0;
LABEL_45:
                v56.n64_u64[0] = vdup_n_s8(v45).n64_u64[0];
                v57 = v44;
                v44 = (u32)Cnt & 0xFFFFFFF8;
                v58 = v57 - v44;
                v59 = &v19[v57];
                do
                {
                  v60 = *v59;
                  v61 = v59[1];
                  v59 += 2;
                  v58 += 8;
                  v56.n64_u64[0] = vorr_s8(vmovn_s16(vuzp1q_s16(vceqq_s32(v60, v46), vceqq_s32(v61, v46))), v56).n64_u64[0];
                }
                while (v58);
                v45 = vmaxv_u8(vcltz_s8(vshl_n_s8(v56, 7u))) & 1;
                if (v44 != Cnt)
                {
LABEL_48:
                  v62 = Cnt - v44;
                  v63 = &v19[v44];
                  do
                  {
                    v64 = *v63++;
                    --v62;
                    LOBYTE(v45) = (v64 == v43) | v45;
                  }
                  while (v62);
                }
              }
              if ((v45 & 1) == 0)
                LODWORD(v65) = 1;
              else
LABEL_51:
                LODWORD(v65) = 0;
              v66 = pData->Tex[(u32)v65];
              v65 = (u32)v65;
              if (op_Inequality(v66, 0, 0))
              {
                v67 = pData->Tex[(u32)v65];
                sdfTexFree(v67);
              }
              v68 = pData->MaskTex[(u32)v65];
              if (!!op_Inequality(pData->MaskTex[(u32)v65], 0, 0))
              {
                v69 = pData->MaskTex[(u32)v65];
                sdfTexFree(v69);
                LoadCnt = pData->LoadCnt - 1;
                if ((s32)v65 < LoadCnt)
                  goto LABEL_66;
                goto LABEL_9000;
              }
              LoadCnt = pData->LoadCnt - 1;
              if ((s32)v65 < LoadCnt)
              {
LABEL_66:
                v89 = v12;
                v70 = (8 * (u32)v65) | 0x20;
                do
                {
                  Tex = pData->Tex;
                  v79 = Tex[v65 + 1];
                  MaskTex[v65] = v81;
                  v71 = (sdfIVector2_t)((char *)pData->MaskOfs + v70);
                  v72 = get_Item(v71, 0, 0);
                  set_Item(v71, 0, v72, 0);
                  v73 = (sdfIVector2_t)((char *)pData->MaskOfs + v70);
                  v74 = get_Item(v73, 1, 0);
                  set_Item(v73, 1, v74, 0);
                  v75 = 4 * v65;
                  v70 += 8;
                  ++v65;
                  v76 = (char *)pData->UID + v75;
                  v77 = (char *)pData->ReqFrame + v75;
                  *((u32 *)v76 + 8) = *((u32 *)v76 + 9);
                  *((u32 *)v77 + 8) = *((u32 *)v77 + 9);
                  LoadCnt = pData->LoadCnt - 1;
                }
                while (v65 < LoadCnt);
                v12 = v89;
              }
LABEL_9000:
              v14 = v90;
              pData->LoadCnt = LoadCnt;
            }
            v82 = &pData->Tex->obj.klass + LoadCnt;
            v82[4] = 0;
            v83 = &pData->MaskTex->obj.klass + pData->LoadCnt;
            v83[4] = 0;
            set_Item((sdfIVector2_t)&pData->MaskOfs[pData->LoadCnt], 0, 0, 0);
            set_Item((sdfIVector2_t)&pData->MaskOfs[pData->LoadCnt], 1, 0, 0);
            ReqFrame = pData->ReqFrame;
            pData->UID[pData->LoadCnt] = v7;
            ReqFrame[pData->LoadCnt++] = v91;
            if (!Contains(v14, ".tmx", 0))
            {
              v85 = Allocate(fileEndCallback_t);
              _ctor(v85, 0, Method_Project_evtTmxPreLoad_EndCallback__, 0);
              fileLoadEx(v12, v14, v85, pData);
              pData->Stat |= 1u;
            }
            goto LABEL_8;
          }
          v6 = 1;
        }
        pData->ReqFrame[v6] = v91;
LABEL_8:
        pData->Que->Flag[i] = 1;
LABEL_9:
        Que = pData->Que;
        v4 = Que->Cnt;
      }
    }
    Flag = Que->Flag;
    if (Flag[1])
    {
      Flag[1] = 0;
      Que->Cnt = v4 - 1;
    }
    if (Flag[0])
    {
      v87 = Que->ReqFrame;
      Que->UID[0] = Que->UID[1];
      v87[0] = v87[1];
      *(u16 *)Flag = 0;
      --Que->Cnt;
    }
  }
}

// 0x19e3790
bool evtChkLoad(bool Mode) {
  Il2CppObject *ProcessData;

  if (!TmxPreLoadPID)
    return 0;
  ProcessData = dds3GetProcessData(TmxPreLoadPID);
  if (!ProcessData)
  if (Mode && *((s32 *)ProcessData[4].monitor + 10) > 0)
    return 1;
  else
    return (s64)ProcessData[1].klass & 1;
}

// 0x19e38d0
bool evtRequest(u32 UID, s32 ReqFrame) {
  Il2CppObject *ProcessData;
  u32 *monitor;
  s32 v9;
  s64 v10;
  s32 *v11;
  s32 v12;
  s64 v13;

  if (!TmxPreLoadPID)
    return 0;
  ProcessData = dds3GetProcessData(TmxPreLoadPID);
  if (!ProcessData)
  if (!(u16)UID)
    return 0;
  monitor = ProcessData[4].monitor;
  v9 = monitor[10];
  if (v9 >= 1)
  {
    v10 = monitor[10];
    v11 = (*((u64 *)monitor + 2) + 32);
    while (1)
    {
      v12 = *v11++;
      if (v12 == UID)
        return 0;
      if (!--v10)
      {
        if (v9 > 1)
          goto LABEL_17;
        break;
      }
    }
  }
  monitor[10] = ++v9;
LABEL_17:
  v13 = *((u64 *)monitor + 3);
  *(u32 *)(*((u64 *)monitor + 2) + 4 * v9 + 28) = UID;
  *(u32 *)(v13 + 4 * (s32)(monitor[10] - 1) + 32) = ReqFrame;
  return 1;
}

// 0x19e3a40
void *evtGetTex(u32 UID) {
  Il2CppObject *ProcessData;
  u32 *monitor;
  s64 v7;

  if (!TmxPreLoadPID)
    return 0;
  ProcessData = dds3GetProcessData(TmxPreLoadPID);
  if (!ProcessData)
  monitor = ProcessData[3].monitor;
  if (monitor[8] == UID)
  {
    v7 = 0;
    return *((void *)&ProcessData[2].klass->_1.byval_arg.data + v7);
  }
  if (monitor[9] == UID)
  {
    v7 = 1;
    return *((void *)&ProcessData[2].klass->_1.byval_arg.data + v7);
  }
  return 0;
}

// 0x19e3b80
void *evtGetMaskTex(u32 UID) {
  Il2CppObject *ProcessData;
  u32 *monitor;
  s64 v7;

  if (!TmxPreLoadPID)
    return 0;
  ProcessData = dds3GetProcessData(TmxPreLoadPID);
  if (!ProcessData)
  monitor = ProcessData[3].monitor;
  if (monitor[8] == UID)
  {
    v7 = 0;
    return *((void *)ProcessData[2].monitor + v7 + 4);
  }
  if (monitor[9] == UID)
  {
    v7 = 1;
    return *((void *)ProcessData[2].monitor + v7 + 4);
  }
  return 0;
}

// 0x19e3cc0
bool evtGetMaskOfs(u32 UID, sdfIVector2_t *pOfs) {
  Il2CppObject *ProcessData;
  u32 *monitor;
  s64 v9;
  s64 v10;
  s32 Item;
  s32 v12;

  if (!TmxPreLoadPID)
    return 0;
  ProcessData = dds3GetProcessData(TmxPreLoadPID);
  if (!ProcessData)
  monitor = ProcessData[3].monitor;
  if (monitor[8] == UID)
  {
    v9 = 0;
LABEL_14:
    v10 = 8 * v9;
    Item = get_Item((sdfIVector2_t)((char *)&ProcessData[3].klass->_1.byval_arg + 8 * v9), 0, 0);
    set_Item((sdfIVector2_t)pOfs, 0, Item, 0);
    v12 = get_Item((sdfIVector2_t)((char *)&ProcessData[3].klass->_1.byval_arg + v10), 1, 0);
    set_Item((sdfIVector2_t)pOfs, 1, v12, 0);
    return 1;
  }
  if (monitor[9] == UID)
  {
    v9 = 1;
    goto LABEL_14;
  }
  return 0;
}

// 0x19e3e70
static dds3ProcessFunc_t Process(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessFunc_t v8;

  if (!TmxPreLoadPID)
    return 0;
  ProcessData = dds3GetProcessData(TmxPreLoadPID);
  if (!ProcessData)
  if (evtChkLoad(0))
    return 0;
  if ((BYTE4(ProcessData[1].klass) & 1) == 0)
  {
    Start();
    return 0;
  }
  v8 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v8, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
  return v8;
}

// 0x19e3fe0
bool evtProcessStart(dds3ProcessID_t *ParentPID, DDS3_PRIORITY Priority) {
  evtTmxPreLoad_t *v6;
  dds3ProcessFunc_t v8;
  shutdownfuncDelegate v9;
  dds3ProcessID_t *started;
  dds3ProcessID_t *parent;

  parent = ParentPID;
  if (!TmxPreLoadPID)
  {
    v6 = Allocate(evtTmxPreLoad_t);
    _ctor(v6);
    v8 = Allocate(dds3ProcessFunc_t);
    _ctor(v8, 0, Method_Project_evtTmxPreLoad_Process__, 0);
    v9 = Allocate(shutdownfuncDelegate);
    _ctor(v9, 0, Method_Project_evtTmxPreLoad_Destroy__, 0);
    started = dds3StartProcess("TmxPreLoad", Priority, 0, 0, v8, v9, v6);
    TmxPreLoadPID = started;
    if (ParentPID)
    {
      dds3LinkProcess(parent, TmxPreLoadPID);
    }
  }
  return TmxPreLoadPID != 0;
}

// 0x19e41c0
void evtProcessEnd(void) {
  Il2CppObject *ProcessData;

  if (TmxPreLoadPID)
  {
    ProcessData = dds3GetProcessData(TmxPreLoadPID);
    if (!ProcessData)
      goto LABEL_10;
    goto LABEL_9000;
    if (!ProcessData)
    {
LABEL_10:
      HIDWORD(ProcessData[1].klass) |= 1u;
      return;
    }
LABEL_9000:
    goto LABEL_10;
  }
}

// 0x19e42b0
void evtTexFree(void) {
  Il2CppObject *ProcessData;
  void *data;
  void *v6;
  void *v7;
  Il2CppClass *klass;
  void *v9;
  u64 *monitor;
  void *v11;
  void *v13;
  void *v14;
  Il2CppClass *v15;
  void *v16;
  u64 *v17;

  if (TmxPreLoadPID)
  {
    ProcessData = dds3GetProcessData(TmxPreLoadPID);
    if (!ProcessData)
    data = ProcessData[2].klass->_1.byval_arg.data;
    if (!op_Inequality(ProcessData[2].klass->_1.byval_arg.data, 0, 0))
      goto LABEL_12;
    goto LABEL_9000;
    if (!op_Inequality(data, 0, 0))
    {
LABEL_12:
      v6 = *((void *)ProcessData[2].monitor + 4);
      goto LABEL_13;
    }
LABEL_9000:
    v7 = ProcessData[2].klass->_1.byval_arg.data;
    sdfTexFree(v7);
    klass = ProcessData[2].klass;
    klass->_1.byval_arg.data = 0;
    v6 = *((void *)ProcessData[2].monitor + 4);
LABEL_13:
    if (!!op_Inequality(v6, 0, 0))
    {
      v9 = *((void *)ProcessData[2].monitor + 4);
      sdfTexFree(v9);
      monitor = ProcessData[2].monitor;
      monitor[4] = 0;
    }
    *((u32 *)ProcessData[3].monitor + 8) = 0;
    v11 = *(void *)&ProcessData[2].klass->_1.byval_arg.bits;
    if (!op_Inequality(*(void *)&ProcessData[2].klass->_1.byval_arg.bits, 0, 0))
      goto LABEL_25;
    goto LABEL_9001;
    if (!op_Inequality(v11, 0, 0))
    {
LABEL_25:
      v13 = *((void *)ProcessData[2].monitor + 5);
      goto LABEL_26;
    }
LABEL_9001:
    v14 = *(void *)&ProcessData[2].klass->_1.byval_arg.bits;
    sdfTexFree(v14);
    v15 = ProcessData[2].klass;
    *(u64 *)&v15->_1.byval_arg.bits = 0;
    v13 = *((void *)ProcessData[2].monitor + 5);
LABEL_26:
    if (!op_Inequality(v13, 0, 0))
      goto LABEL_36;
    goto LABEL_33;
    if (!op_Inequality(v13, 0, 0))
    {
LABEL_36:
      *((u32 *)ProcessData[3].monitor + 9) = 0;
      return;
    }
LABEL_33:
    v16 = *((void *)ProcessData[2].monitor + 5);
    sdfTexFree(v16);
    v17 = ProcessData[2].monitor;
    v17[5] = 0;
    goto LABEL_36;
  }
}
