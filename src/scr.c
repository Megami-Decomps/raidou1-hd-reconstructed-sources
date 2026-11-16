#include "types.h"
#include "dat.h"
#include "dds3kernelcore.h"
#include "fclmsg.h"
#include "fld.h"
#include "fldcommand.h"
#include "itf.h"
#include "kernel.h"
#include "localize.h"
#include "meslogmain.h"
#include "sbtldraw.h"
#include "scr.h"
#include "scrcommand.h"

#define SCRLOG_MAX 8
#define MESLOG_NUMBER_MAX 30
#define MESLOG_NUMBER_CH 8
#define MESLOG_LBLCHR_MAX 64
#define MESLOG_LBLCHR_MAX2 128
#define MESLOG_FR_VAR_MAX 8
#define MESLOG_PARAM_MAX 8
#define MESLOG_BYTE_ARRY1 64
#define MESLOG_BYTE_SIZE1 1920
#define MESLOG_BYTE_ARRY2 512
#define MESLOG_BYTE_SIZE2 15360
#define MESLOG_BYTE_ARRY3 1024
#define MESLOG_BYTE_SIZE3 30720
#define MESLOG_PARAM_SIZE 240

typedef struct LOGDISP_PARAM LOGDISP_PARAM;
typedef struct SCRLOG SCRLOG;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct instanceMes_tag instanceMes_tag;
typedef struct scrCode_t scrCode_t;
typedef struct scrHandle_t scrHandle_t;
typedef struct scrHeader_t scrHeader_t;
typedef struct scrLabelTable_t scrLabelTable_t;
typedef struct scrProcTable_t scrProcTable_t;
typedef struct scrTypeTable_t scrTypeTable_t;

typedef s32 (*CodeFunc_t)(scrHandle_t *pwork);

static SCRLOG *log_work[8];
static SCRLOG *fldlog_wk;
static void *ml_fileList;
static void *aloadList;
static void *MxxTbl;
static s32 HandleCount;
static scrHandle_t *HandleFirst;
static scrHandle_t *HandleLast;
static CodeFunc_t *codefunc;
scrHandle_t *s_hNowpWork;
static s32 s_i1;
static s32 s_i2;
static s32 s_ri;
static f32 s_f1;
static f32 s_f2;
static f32 s_rf;
static s32 s_t1;
static s32 s_t2;

static SCRLOG *GerLogWork(dds3ProcessID_t *pid);
static void NewLogSaveNext(void);
static char *TagGet(char *tag);
static char *TagGetStr(char *str);
static void InitNewMsgLogList(SCRLOG *lwk);
static void NewLogSave(char *mesTag, char *spkTag, char *voiceTag);
static bool IsSameFL(s32 wtop, char *key, char *filename);
static void Fload(char *key, char *filename, bool add);
static bool map16chk(char *key);
static void *ExxLog(char *mestag);
static void MxxLog(char *mestag);
static void LinkScriptHandleList(scrHandle_t *h);
static void UnlinkScriptHandleList(scrHandle_t *h);
static scrHandle_t *AddScript(scrHeader_t *header, scrTypeTable_t *typetable, scrProcTable_t *proctable, scrLabelTable_t *labeltable, scrCode_t *code, u8 *mesdata, u8 *stringdata, s32 startproc);
static scrHandle_t *AddScript2(u8 *scrdata, s32 startproc);
static scrHandle_t *AddScript3(char *asset_name, char *filename, s32 startproc);
static dds3ProcessID_t *StartScriptProcess(s32 priority, scrHandle_t *h, bool skip_enable);
static void Shutdown(dds3ProcessID_t *id);
static void PushInt(scrHandle_t *pwork, s32 data);
static void PushFloat(scrHandle_t *pwork, f32 data);
static void PushStr(scrHandle_t *pwork, s32 data);
static void PushRet(scrHandle_t *pwork, s32 cp);
static s32 PopInt(scrHandle_t *pwork);
static f32 PopFloat(scrHandle_t *pwork);
static s32 CodeFunc_PushI(scrHandle_t *pwork);
static s32 CodeFunc_PushIS(scrHandle_t *pwork);
static s32 CodeFunc_PushF(scrHandle_t *pwork);
static s32 CodeFunc_PushIX(scrHandle_t *pwork);
static s32 CodeFunc_PushFX(scrHandle_t *pwork);
static s32 CodeFunc_PushLIX(scrHandle_t *pwork);
static s32 CodeFunc_PushLFX(scrHandle_t *pwork);
static s32 CodeFunc_PushSTR(scrHandle_t *pwork);
static s32 CodeFunc_PushReg(scrHandle_t *pwork);
static s32 CodeFunc_PopIX(scrHandle_t *pwork);
static s32 CodeFunc_PopFX(scrHandle_t *pwork);
static s32 CodeFunc_PopLIX(scrHandle_t *pwork);
static s32 CodeFunc_PopLFX(scrHandle_t *pwork);
static s32 CodeFunc_Proc(scrHandle_t *pwork);
static s32 CodeFunc_Comm(scrHandle_t *pwork);
static s32 CodeFunc_End(scrHandle_t *pwork);
static s32 CodeFunc_Jump(scrHandle_t *pwork);
static s32 CodeFunc_Call(scrHandle_t *pwork);
static s32 CodeFunc_Run(scrHandle_t *pwork);
static s32 CodeFunc_Goto(scrHandle_t *pwork);
static void CodeFunc_2Operation(scrHandle_t *pwork, s32 type);
static s32 CodeFunc_Add(scrHandle_t *pwork);
static s32 CodeFunc_Sub(scrHandle_t *pwork);
static s32 CodeFunc_Mul(scrHandle_t *pwork);
static s32 CodeFunc_Div(scrHandle_t *pwork);
static s32 CodeFunc_Minus(scrHandle_t *pwork);
static s32 CodeFunc_Not(scrHandle_t *pwork);
static s32 CodeFunc_Or(scrHandle_t *pwork);
static s32 CodeFunc_And(scrHandle_t *pwork);
static s32 CodeFunc_EQ(scrHandle_t *pwork);
static s32 CodeFunc_NEQ(scrHandle_t *pwork);
static s32 CodeFunc_S(scrHandle_t *pwork);
static s32 CodeFunc_L(scrHandle_t *pwork);
static s32 CodeFunc_SE(scrHandle_t *pwork);
static s32 CodeFunc_LE(scrHandle_t *pwork);
static s32 CodeFunc_IF(scrHandle_t *pwork);

// 0x2142330
void scrLogInit(void) {
  SCRLOG *v3;
  SCRLOG *v5;
  SCRLOG *v6;
  SCRLOG *v8;
  SCRLOG *v9;
  SCRLOG *v11;
  SCRLOG *v12;
  SCRLOG *v14;
  SCRLOG *v15;
  SCRLOG *v17;
  SCRLOG *v18;
  SCRLOG *v20;
  SCRLOG *v21;
  SCRLOG *v23;
  SCRLOG *v24;

  v3 = Allocate(SCRLOG);
  _ctor(v3, 0);
  log_work[0] = v3;
  v5 = log_work;
  v6 = Allocate(SCRLOG);
  _ctor(v6, 0);
  v5[1] = v6;
  v8 = log_work;
  v9 = Allocate(SCRLOG);
  _ctor(v9, 0);
  v8[2] = v9;
  v11 = log_work;
  v12 = Allocate(SCRLOG);
  _ctor(v12, 0);
  v11[3] = v12;
  v14 = log_work;
  v15 = Allocate(SCRLOG);
  _ctor(v15, 0);
  v14[4] = v15;
  v17 = log_work;
  v18 = Allocate(SCRLOG);
  _ctor(v18, 0);
  v17[5] = v18;
  v20 = log_work;
  v21 = Allocate(SCRLOG);
  _ctor(v21, 0);
  v20[6] = v21;
  v23 = log_work;
  v24 = Allocate(SCRLOG);
  _ctor(v24, 0);
  v23[7] = v24;
}

// 0x2142660
static SCRLOG *GerLogWork(dds3ProcessID_t *pid) {
  SCRLOG *v5;
  SCRLOG *result;
  SCRLOG *v7;
  SCRLOG *v8;
  s64 v9;
  SCRLOG *v10;
  SCRLOG *v11;
  SCRLOG *v12;
  SCRLOG *v13;
  SCRLOG *v14;

  if (pid)
  {
    v5 = log_work[0];
    if (!v5->start)
    {
LABEL_13:
      v7 = log_work[1];
      if (!v7->start)
      {
LABEL_19:
        v8 = log_work[2];
        if (!v8->start)
        {
LABEL_27:
          v10 = log_work[3];
          if (!v10->start)
          {
LABEL_35:
            v11 = log_work[4];
            if (!v11->start)
              goto LABEL_43;
            goto LABEL_9000;
            if (!v11->start)
            {
LABEL_43:
              v12 = log_work[5];
              if (!v12->start)
                goto LABEL_52;
              v12 = log_work[5];
              if (v12->pid != pid)
              {
LABEL_52:
                v13 = log_work[6];
                if (!v13->start)
                  goto LABEL_75;
                v13 = log_work[6];
                if (v13->pid == pid)
                {
                  v9 = 6;
                }
                else
                {
LABEL_75:
                  v14 = log_work[7];
                  if (!v14->start)
                    return 0;
                  v14 = log_work[7];
                  if (v14->pid != pid)
                    return 0;
                  v9 = 7;
                }
                goto LABEL_70;
              }
              v9 = 5;
LABEL_70:
              return log_work[v9];
            }
LABEL_9000:
            if (v11->pid != pid)
              goto LABEL_43;
            v9 = 4;
            goto LABEL_70;
          }
          if (v10->pid != pid)
            goto LABEL_35;
          v9 = 3;
          goto LABEL_70;
        }
        if (v8->pid != pid)
          goto LABEL_27;
        v9 = 2;
        goto LABEL_70;
      }
      if (v7->pid != pid)
        goto LABEL_19;
      v9 = 1;
      goto LABEL_70;
    }
    if (v5->pid != pid)
      goto LABEL_13;
    v9 = 0;
    goto LABEL_70;
  }
  result = fldlog_wk;
  result->is_field = 1;
  return result;
}

// 0x2142a80
void scrLogStart(dds3ProcessID_t *pid) {
  SCRLOG *v3;

  v3 = Allocate(SCRLOG);
  _ctor(v3, 0);
  SetLog(v3);
  LogStart(pid);
}

// 0x2142b20
void scrLogSetId(dds3ProcessID_t *pid) {
  ;
}

// 0x2142b30
void scrLogSave(char *msg_text, char *spk_text, char *voice_text, void *tag_list, instanceMes_tag *pinst, void *sel_list, char *sel_text, char *mes_save, bool *add_flag) {
  message_tag *message;
  FontReq_t *pfont;
  char *tag_id;
  Speaker_tag *speaker;
  FontReq_t *v20;
  s32 num;
  char *v22;
  bool v24;
  void *v25;
  u64 *v26;
  s64 size;
  void *items;
  Il2CppClass **v29;
  char *v30;
  char *v31;
  char *v32;
  char *v33;
  char *v34;
  void *v35;
  u64 *v36;
  s64 v37;
  void *v38;
  Il2CppClass **v39;
  char *v40;
  s32 v43;

  message = pinst->message;
  v43 = 0;
  if (message && (pfont = message->pfont) != 0)
  {
    tag_id = pfont->tag_id;
    speaker = pinst->speaker;
    if (!speaker)
    {
LABEL_12:
      v22 = 0;
      goto LABEL_14;
    }
  }
  else
  {
    tag_id = 0;
    speaker = pinst->speaker;
    if (!speaker)
      goto LABEL_12;
  }
  v20 = speaker->pfont;
  if (!v20)
    goto LABEL_12;
  num = (s16)speaker->num;
  if ((num & 0x80000000) == 0)
  {
    v22 = v20->tag_id;
    goto LABEL_14;
  }
  v43 = num & 0x7FFF;
  v40 = ToString_55996800((s32)&v43, "d2", 0);
  v22 = Concat_54766928("msglog_spk", v40, 0);
LABEL_14:
  NewLogSave(tag_id, v22, voice_text);
  v24 = _Contains(tag_list, tag_id);
  if (v24)
    goto LABEL_17;
  v25 = tag_list;
  v26 = Method_System_Collections_Generic_List_string__Add__;
  size = tag_list->_size;
  v25->_version = tag_list->_version + 1;
  items = v25->_items;
  if ((u32)size < LODWORD(items->max_length))
  {
    v25->_size = size + 1;
    v29 = &items->obj.klass + size;
    v29[4] = tag_id;
LABEL_17:
    if (!op_Inequality(sel_text, "", 0))
      goto LABEL_18;
    goto LABEL_29;
  }
  _AddWithResize(v25, tag_id, *(const MethodInfo_2DFC660 **)(*(u64 *)(v26[4] + 192) + 112));
  if (!op_Inequality(sel_text, "", 0))
  {
LABEL_18:
    if (!v24)
    {
LABEL_19:
      v30 = Copy(msg_text);
      if (spk_text)
        v31 = spk_text;
      else
        v31 = "";
      v32 = Copy(v31);
      if (voice_text)
        v33 = voice_text;
      else
        v33 = "";
      v34 = Copy(v33);
      AddLog(v30, v32, v34);
      return;
    }
    goto LABEL_36;
  }
LABEL_29:
  if (!_Contains(sel_list, tag_id))
  {
    v35 = sel_list;
    v36 = Method_System_Collections_Generic_List_string__Add__;
    v37 = sel_list->_size;
    v35->_version = sel_list->_version + 1;
    v38 = v35->_items;
    if ((u32)v37 >= LODWORD(v38->max_length))
    {
      _AddWithResize(v35, tag_id, *(const MethodInfo_2DFC660 **)(*(u64 *)(v36[4] + 192) + 112));
      if (!v24)
        goto LABEL_19;
    }
    else
    {
      v35->_size = v37 + 1;
      v39 = &v38->obj.klass + v37;
      v39[4] = tag_id;
      if (!v24)
        goto LABEL_19;
    }
  }
LABEL_36:
  if (op_Equality(mes_save[0], msg_text, 0))
    *add_flag = 1;
}

// 0x2143600
void scrLogSaveSel(char *sel_text, bool flag, void *sel_list, char **mes_save, bool *add_flag) {
  s32 v11;
  s32 v12;
  Il2CppObject *Item;
  char *v14;
  char *v15;
  char *v16;
  char *v17;
  char **v18;
  char *v19;
  char *v21;
  char **v22;
  char *v23;

  if (sel_list->_size < 1)
    goto LABEL_12;
  v11 = 0;
  v12 = 1;
  do
  {
    Item = _get_Item(sel_list, v11++);
    v12 &= !op_Equality(Item, sel_text, 0);
  }
  while (v11 < sel_list->_size);
  if ((v12 & 1) != 0)
  {
LABEL_12:
    if (flag && op_Inequality(sel_text, "", 0))
    {
      if (GetListCount() >= 1)
      {
        v14 = Copy(sel_text);
        v15 = (*mes_save)[1];
        if (v15)
        {
          v16 = Copy(v15);
          v18 = &(*mes_save)[2];
          v17 = *v18;
          if (*v18)
            goto LABEL_15;
        }
        else
        {
          v21 = "";
          v22 = &(*mes_save)[1];
          *v22 = "";
          v16 = Copy((*mes_save)[1]);
          v18 = &(*mes_save)[2];
          v17 = *v18;
          if (*v18)
          {
LABEL_15:
            v19 = Copy(v17);
LABEL_16:
            AddLog(v14, v16, v19);
            *add_flag = 0;
            return;
          }
        }
        v23 = "";
        *v18 = "";
        v19 = Copy((*mes_save)[2]);
        goto LABEL_16;
      }
    }
  }
}

// 0x2143820
void scrLogSelIDSave(LOGDISP_PARAM *logwk) {
  s32 v5;
  s32 *selidx;
  s32 **p_selidx;
  s64 max_length_low;
  s32 *v9;
  s32 **p_selidxsave;
  s64 v11;
  s64 v12;
  s32 *v13;
  u64 v14;
  u64 v15;
  s32 *v16;
  __int128 *v17;
  u64 v18;
  __int128 v19;
  __int128 v20;
  __int128 v21;
  __int128 v22;
  u64 v23;
  u64 v24;
  s64 v25;
  u32 *v26;
  s32 *v27;
  s32 v28;
  s32 *v29;
  il2cpp_array_size_t max_length;
  u64 v31;
  s64 m_Items;
  s64 v33;
  s64 v34;
  s32 v35;

  v5 = GetListCount() - 1;
  p_selidx = &logwk->selidx;
  selidx = logwk->selidx;
  max_length_low = LODWORD(selidx->max_length);
  if (max_length_low == 1 && !selidx[0])
  {
    selidx[0] = v5;
  }
  else
  {
    v9 = NewSpecific(s32, max_length_low);
    logwk->selidxsave = v9;
    p_selidxsave = &logwk->selidxsave;
    v11 = *(p_selidxsave - 1);
    v12 = *(u64 *)(v11 + 24);
    if ((s32)v12 >= 1)
    {
      v13 = *p_selidxsave;
      v14 = (u32)*(u64 *)(v11 + 24);
      v15 = 0;
      if (v14 < 0x10)
        goto LABEL_13;
      if ((u64)v13 - v11 < 0x40)
        goto LABEL_13;
      v16 = &v13[12];
      v17 = (v11 + 48);
      v15 = v14 - (*(u64 *)(v11 + 24) & 0xF);
      v18 = v15;
      do
      {
        v19 = *(v17 - 1);
        v20 = *v17;
        v18 -= 16;
        v21 = v17[1];
        v22 = v17[2];
        v17 += 4;
        *((_OWORD *)v16 - 3) = v19;
        *((_OWORD *)v16 - 2) = v20;
        *((_OWORD *)v16 - 1) = v21;
        *(_OWORD *)v16 = v22;
        v16 += 16;
      }
      while (v18);
      if ((v12 & 0xF) != 0)
      {
LABEL_13:
        v23 = v15 + 1;
        if ((((u32)v12 - (u32)v15) & 1) != 0)
        {
          v13[v15] = *(u32 *)(v11 + 4 * v15 + 32);
          ++v15;
        }
        if (v14 != v23)
        {
          v24 = v14 - v15;
          v25 = 4 * v15 + 36;
          v26 = ((char *)v13 + v25);
          v27 = (v11 + v25);
          do
          {
            v24 -= 2;
            *(v26 - 1) = *(v27 - 1);
            v28 = *v27;
            v27 += 2;
            *v26 = v28;
            v26 += 2;
          }
          while (v24);
        }
      }
    }
    v29 = NewSpecific(s32, (s32)v12 + 1);
    *p_selidx = v29;
    max_length = (*p_selidx)->max_length;
    if ((s32)max_length >= 1)
    {
      v31 = 0;
      m_Items = (*p_selidx);
      v33 = 4 * (u32)(max_length - 1);
      v34 = 4 * (u32)(*p_selidx)->max_length;
      do
      {
        v35 = v5;
        if (v33 != v31)
          v35 = (*p_selidxsave)[v31 / 4];
        *(u32 *)(m_Items + v31) = v35;
        v31 += 4;
      }
      while (v34 != v31);
    }
  }
}

// 0x2143ae0
bool scrIsLogSave(void) {
  MesLogData_t *Wk;

  Wk = GetWk();
  if (Wk)
    LOBYTE(Wk) = ChkLog(Wk->mesLog, 0);
  return (char)Wk;
}

// 0x2143b70
void *scrGetMsgLogList(void) {
  return GetLog(0);
}

// 0x2143bf0
void *scrGetSpeakerLogList(void) {
  return GetLog(1);
}

// 0x2143c70
void *scrGetVoiceLogList(void) {
  return GetLog(2);
}

// 0x2143a70
s32 scrGetLogListCount(void) {
  return GetListCount();
}

// 0x2143cf0
SCRLOG *scrLogCheck(dds3ProcessID_t *pid) {
  return 0;
}

// 0x2143d00
void scrLogEnd(dds3ProcessID_t *pid) {
  MesLogData_t *Wk;

  goto LABEL_3;
LABEL_7:
  Wk = GetWk();
  if (!Wk)
    return;
  LogEnable(Wk->mesLog, 0, pid, 0);
  return;
LABEL_3:
  if (ProcessCheck())
    goto LABEL_7;
}

// 0x2143dd0
void scrLogEndAll(void) {
  MesLogData_t *Wk;

  goto LABEL_3;
LABEL_7:
  Wk = GetWk();
  if (!Wk)
    return;
  LogEnableReset(Wk->mesLog, 0);
  return;
LABEL_3:
  if (ProcessCheck())
    goto LABEL_7;
}

// 0x2143e90
void scrLogFlgReset(void) {
  MesLogData_t *Wk;

  goto LABEL_3;
LABEL_7:
  Wk = GetWk();
  if (!Wk)
    return;
  LogEnableReset(Wk->mesLog, 0);
  return;
LABEL_3:
  if (ProcessCheck())
    goto LABEL_7;
}

// 0x2143f50
bool scrEventSkipChk(void) {
  return 0;
}

// 0x2143f60
bool scrIsEventSkip(dds3ProcessID_t *pid) {
  MesLogData_t *Wk;

  goto LABEL_3;
LABEL_9:
  LOBYTE(Wk) = 0;
  return (char)Wk;
LABEL_3:
  if (!ProcessCheck())
    goto LABEL_9;
  Wk = GetWk();
  if (!Wk)
    return (char)Wk;
  LOBYTE(Wk) = Wk->mesSkip->enable;
  return (char)Wk;
}

// 0x2144030
void scrEventSkipMsg1st(void) {
  MesLogData_t *Wk;

  if (!ProcessCheck())
    return;
  Wk = GetWk();
  if (!Wk)
    return;
  Wk->mesSkip->msg1st = 1;
  return;
}

// 0x21440f0
void scrEndEventSkipMsg1st(void) {
  MesLogData_t *Wk;

  if (!ProcessCheck())
    return;
  Wk = GetWk();
  if (!Wk)
    return;
  Wk->mesSkip->msg1st = 0;
  return;
}

// 0x21441b0
void scrEventSkipEnd(bool _restart, dds3ProcessID_t *pid) {
  MesLogData_t *Wk;
  MesSkip *mesSkip;

  if (!ProcessCheck())
    return;
  Wk = GetWk();
  if (!Wk)
    return;
  mesSkip = Wk->mesSkip;
  if (restart)
    Stop(mesSkip, 0);
  else
    End(mesSkip, 0);
}

// 0x2144290
void scrEventSkipRestart(void) {
  MesLogData_t *Wk;

  goto LABEL_3;
LABEL_7:
  Wk = GetWk();
  if (!Wk)
    return;
  ReStart(Wk->mesSkip, 0);
  return;
LABEL_3:
  if (ProcessCheck())
    goto LABEL_7;
}

// 0x2144350
void scrEventSkipRestartFlagChange(void) {
  MesSkip *ProcessData;

  if (ProcessCheck())
    goto LABEL_4;
  return;
  if (ProcessCheck())
  {
LABEL_4:
    ProcessData = dds3GetProcessData(GlobalPID);
    if (!ProcessData)
      goto LABEL_15;
    goto LABEL_13;
    if (!ProcessData)
    {
LABEL_15:
      EventSkipRestartFlagChange(ProcessData[2], 0);
      return;
    }
LABEL_13:
    goto LABEL_15;
  }
}

// 0x2144490
static void NewLogSaveNext(void) {
  NEW_MSGLOG *new_msglog;
  s32 msglog_read_top;
  s32 v4;
  NEW_MSGLOG *v5;
  bool v6;

  new_msglog = GBWK->new_msglog;
  msglog_read_top = new_msglog->msglog_read_top;
  v4 = new_msglog->msglog_write_top + 1;
  if (v4 >= 30)
  {
    v4 = 0;
    new_msglog->msglog_write_page = 1;
LABEL_7:
    v5 = GBWK->new_msglog;
    if (!v5->msglog_write_page)
      goto LABEL_23;
    goto LABEL_14;
  }
  goto LABEL_7;
LABEL_14:
  if (v4 > msglog_read_top || (!v4 ? (v6 = msglog_read_top == 29) : (v6 = 0), v6))
  {
    if (msglog_read_top < 29)
      ++msglog_read_top;
    else
      msglog_read_top = 0;
  }
LABEL_23:
  v5 = GBWK->new_msglog;
  v5->msglog_write_top = v4;
  v5->msglog_read_top = msglog_read_top;
}

// 0x21445f0
static char *TagGet(char *tag) {
  void *ASCII;

  if (IsNullOrEmpty(tag, 0))
    return "";
  ASCII = get_ASCII(0);
  (ASCII->klass->vtable._16_GetBytes.methodPtr)(ASCII, tag, ASCII->klass->vtable._16_GetBytes.method);
  if (get_Chars(tag, 0, 0))
    return tag;
  else
    return "";
}

// 0x2144690
static char *TagGetStr(char *str) {
  if (IsNullOrEmpty(str, 0))
    return "";
  else
    return str;
}

// 0x2144700
static void InitNewMsgLogList(SCRLOG *lwk) {
  void *msglog;
  s32 size;
  s32 v5;
  void *spklog;
  s32 v7;
  s32 v8;
  void *voicelog;
  s32 v10;
  s32 v11;
  s32 v13;
  s32 msglog_read_top;
  char *v16;
  char *v17;
  void *ASCII;
  char *v19;
  char *v20;
  void *v21;
  char *v22;
  char *v23;
  void *v24;
  u16 Chars;
  char *v26;
  void *v27;
  Il2CppObject *v29;
  char *v30;
  char *v32;
  char *v34;
  char *v36;
  char *v38;
  char *v40;
  char *v42;
  char *v44;
  char *v46;
  Il2CppObject *v48;
  void *v49;
  void *v50;
  s64 v51;
  u64 *v52;
  void *v53;
  Il2CppClass **v54;
  u32 v56;
  char *LocalizeText;
  char *v58;
  s64 v59;
  char *v60;
  char *v62;
  char *v63;
  void *v64;
  char *v66;
  u32 v67;
  char *v68;
  SCRLOG *v69;
  Il2CppObject *v70;
  s32 mapSummonID;
  Il2CppObject *Item1;
  void *v74;
  u64 *v75;
  s64 v76;
  void *items;
  Il2CppClass **v78;
  Il2CppObject *v80;
  void *v81;
  s64 v82;
  u64 *v83;
  void *v84;
  Il2CppClass **v85;
  void *v86;
  s64 v87;
  u64 *v88;
  void *v89;
  Il2CppClass **v90;
  Il2CppObject *v91;
  u8 ColNo;
  SCRLOG *v93;
  char *v94;
  System_ValueTuple_string__byte__o LabelToString;

  msglog = lwk->msglog;
  size = msglog->_size;
  v5 = msglog->_version + 1;
  msglog->_size = 0;
  msglog->_version = v5;
  if (size >= 1)
    Clear(msglog->_items, 0, size, 0);
  spklog = lwk->spklog;
  v7 = spklog->_size;
  v8 = spklog->_version + 1;
  spklog->_size = 0;
  spklog->_version = v8;
  if (v7 >= 1)
    Clear(spklog->_items, 0, v7, 0);
  voicelog = lwk->voicelog;
  v10 = voicelog->_size;
  v11 = voicelog->_version + 1;
  voicelog->_size = 0;
  voicelog->_version = v11;
  if (v10 >= 1)
    Clear(voicelog->_items, 0, v10, 0);
  ColNo = 0;
  v13 = 0;
  v93 = lwk;
  msglog_read_top = GBWK->new_msglog->msglog_read_top;
  do
  {
    v16 = GBWK->new_msglog->meslog_mesTag[msglog_read_top][0];
    if (IsNullOrEmpty(v16, 0))
    {
      v17 = "";
      goto LABEL_28;
    }
    ASCII = get_ASCII(0);
    (ASCII->klass->vtable._16_GetBytes.methodPtr)(ASCII, v16, ASCII->klass->vtable._16_GetBytes.method);
    if (get_Chars(v16, 0, 0))
      v17 = v16;
    else
      v17 = "";
LABEL_28:
    v19 = GBWK->new_msglog->meslog_mesTag[msglog_read_top][1];
    if (IsNullOrEmpty(GBWK->new_msglog->meslog_mesTag[msglog_read_top][1], 0))
    {
      goto LABEL_30;
    }
    goto LABEL_9001;
    if (IsNullOrEmpty(v19, 0))
    {
LABEL_30:
      v20 = "";
      goto LABEL_35;
    }
LABEL_9001:
    v21 = get_ASCII(0);
    (v21->klass->vtable._16_GetBytes.methodPtr)(v21, v19, v21->klass->vtable._16_GetBytes.method);
    if (get_Chars(v19, 0, 0))
      v20 = v19;
    else
      v20 = "";
LABEL_35:
    v22 = GBWK->new_msglog->meslog_spkTag[msglog_read_top];
    if (IsNullOrEmpty(GBWK->new_msglog->meslog_spkTag[msglog_read_top], 0))
    {
      goto LABEL_37;
    }
    goto LABEL_9002;
    if (IsNullOrEmpty(v22, 0))
    {
LABEL_37:
      v23 = "";
      goto LABEL_41;
    }
LABEL_9002:
    v24 = get_ASCII(0);
    (v24->klass->vtable._16_GetBytes.methodPtr)(v24, v22, v24->klass->vtable._16_GetBytes.method);
    Chars = get_Chars(v22, 0, 0);
    v23 = "";
    if (Chars)
      v23 = v22;
LABEL_41:
    v94 = v23;
    v26 = GBWK->new_msglog->meslog_voiceTag[msglog_read_top];
    if (!IsNullOrEmpty(v26, 0))
      goto LABEL_46;
    v26 = "";
    if (!op_Inequality(v17, "", 0))
      goto LABEL_13;
LABEL_49:
    if (!op_Inequality(v20, "", 0))
    {
      v32 = GBWK->new_msglog->gVarStr[msglog_read_top][0];
      frSetVariableRequest(0, v32);
      v34 = GBWK->new_msglog->gVarStr[msglog_read_top][1];
      frSetVariableRequest(1, v34);
      v36 = GBWK->new_msglog->gVarStr[msglog_read_top][2];
      frSetVariableRequest(2, v36);
      v38 = GBWK->new_msglog->gVarStr[msglog_read_top][3];
      frSetVariableRequest(3, v38);
      v40 = GBWK->new_msglog->gVarStr[msglog_read_top][4];
      frSetVariableRequest(4, v40);
      v42 = GBWK->new_msglog->gVarStr[msglog_read_top][5];
      frSetVariableRequest(5, v42);
      v44 = GBWK->new_msglog->gVarStr[msglog_read_top][6];
      frSetVariableRequest(6, v44);
      v46 = GBWK->new_msglog->gVarStr[msglog_read_top][7];
      frSetVariableRequest(7, v46);
      v48 = v26;
      mapSummonID = GBWK->mapSummonID;
      GBWK->mapSummonID = GBWK->new_msglog->gParam[msglog_read_top][0];
      LabelToString = itfGetLabelToString(v17, 0, ColNo);
      v69 = v93;
      Item1 = LabelToString.Item1;
      ColNo = LabelToString.Item2;
      v74 = v93->msglog;
      v75 = Method_System_Collections_Generic_List_string__Add__;
      v76 = v74->_size;
      ++v74->_version;
      items = v74->_items;
      if ((u32)v76 >= LODWORD(items->max_length))
      {
        _AddWithResize(v74, Item1, *(const MethodInfo_2DFC660 **)(*(u64 *)(v75[4] + 192) + 112));
      }
      else
      {
        v74->_size = v76 + 1;
        v78 = &items->obj.klass + v76;
        v78[4] = Item1;
      }
      GBWK->mapSummonID = mapSummonID;
      v70 = v48;
      goto LABEL_140;
    }
    v29 = "";
    v30 = GBWK->new_msglog->meslog_mesTag[msglog_read_top][0];
    if (IsNullOrEmpty(v30, 0))
      goto LABEL_55;
LABEL_93:
    v49 = get_ASCII(0);
    (v49->klass->vtable._16_GetBytes.methodPtr)(v49, v30, v49->klass->vtable._16_GetBytes.method);
    if (!get_Chars(v30, 0, 0))
      v30 = "";
    v91 = v26;
    if (op_Equality(v30, "", 0))
    {
LABEL_96:
      v50 = v93->msglog;
      v51 = v50->_size;
      v52 = Method_System_Collections_Generic_List_string__Add__;
      ++v50->_version;
      v53 = v50->_items;
      if ((u32)v51 >= LODWORD(v53->max_length))
      {
        _AddWithResize(v50, v29, *(const MethodInfo_2DFC660 **)(*(u64 *)(v52[4] + 192) + 112));
      }
      else
      {
        v50->_size = v51 + 1;
        v54 = &v53->obj.klass + v51;
        v54[4] = v29;
      }
      v69 = v93;
      v70 = v91;
LABEL_140:
      if (Equals_54828784(v94, "msglog_spk00", 0))
      {
        v80 = GBWK->new_msglog->gVarStr[msglog_read_top][0];
      }
      else
      {
        v80 = itfGetLabelToString(v94, 1, 0).Item1;
      }
      v81 = v69->spklog;
      v82 = v81->_size;
      v83 = Method_System_Collections_Generic_List_string__Add__;
      ++v81->_version;
      v84 = v81->_items;
      if ((u32)v82 >= LODWORD(v84->max_length))
      {
        _AddWithResize(v81, v80, *(const MethodInfo_2DFC660 **)(*(u64 *)(v83[4] + 192) + 112));
      }
      else
      {
        v81->_size = v82 + 1;
        v85 = &v84->obj.klass + v82;
        v85[4] = v80;
      }
      v86 = v69->voicelog;
      v87 = v86->_size;
      v88 = Method_System_Collections_Generic_List_string__Add__;
      ++v86->_version;
      v89 = v86->_items;
      if ((u32)v87 >= LODWORD(v89->max_length))
      {
        _AddWithResize(v86, v70, *(const MethodInfo_2DFC660 **)(*(u64 *)(v88[4] + 192) + 112));
      }
      else
      {
        v86->_size = v87 + 1;
        v90 = &v89->obj.klass + v87;
        v90[4] = v70;
      }
      goto LABEL_13;
    }
LABEL_98:
    if (GBWK->new_msglog->msglog_sel_result[msglog_read_top])
      v56 = -1448498689;
    else
      v56 = -1;
    LocalizeText = GetLocalizeText(v30, 1);
    v58 = itfRepColTag(LocalizeText, v56);
    v29 = Concat_54831728(v29, v29, v58, 0);
    v59 = 5;
    while (1)
    {
      v62 = *((char **)&GBWK->new_msglog->meslog_mesTag[msglog_read_top]->obj.klass + v59);
      if (!IsNullOrEmpty(v62, 0))
      {
        v64 = get_ASCII(0);
        (v64->klass->vtable._16_GetBytes.methodPtr)(v64, v62, v64->klass->vtable._16_GetBytes.method);
        if (get_Chars(v62, 0, 0))
          v63 = v62;
        else
          v63 = "";
        if (op_Equality(v63, "", 0))
          goto LABEL_96;
        goto LABEL_122;
      }
      v63 = "";
      if (op_Equality("", "", 0))
        goto LABEL_96;
LABEL_122:
      v66 = "\n";
      if (v59 - 4 == GBWK->new_msglog->msglog_sel_result[msglog_read_top])
        v67 = -1;
      else
        v67 = -1448498689;
      v68 = GetLocalizeText(v63, 1);
      v60 = itfRepColTag(v68, v67);
      ++v59;
      v29 = Concat_54831728(v29, v66, v60, 0);
      if (v59 == 12)
        goto LABEL_96;
    }
    if (IsNullOrEmpty(v30, 0))
    {
LABEL_55:
      v30 = "";
      v91 = v26;
      if (!op_Equality("", "", 0))
        goto LABEL_98;
      goto LABEL_96;
    }
    goto LABEL_93;
LABEL_46:
    v27 = get_ASCII(0);
    (v27->klass->vtable._16_GetBytes.methodPtr)(v27, v26, v27->klass->vtable._16_GetBytes.method);
    if (!get_Chars(v26, 0, 0))
      v26 = "";
    if (op_Inequality(v17, "", 0))
      goto LABEL_49;
LABEL_13:
    ++v13;
    if (msglog_read_top + 1 < 30)
      ++msglog_read_top;
    else
      msglog_read_top = 0;
  }
  while (v13 != 30);
}

// 0x2142ea0
static void NewLogSave(char *mesTag, char *spkTag, char *voiceTag) {
  s64 msglog_write_top;
  char *v10;
  char *v12;
  char *v14;
  char *v16;
  char *v18;
  char *v20;
  char *v22;
  char *v24;
  char *v26;
  char *v27;
  void *ASCII;
  char *meslog_spkTag;
  char *v31;
  void *v32;
  Il2CppClass **v33;
  char *meslog_voiceTag;
  char *v35;
  Il2CppClass **v36;
  void *v38;
  char *v39;
  Il2CppClass **v40;
  char *VariableRequest;
  char *v42;
  char *PlayerName;
  char *v45;
  s64 v46;
  s32 v47;
  char *v48;
  char *v49;
  char **v51;
  char *v52;

  msglog_write_top = GBWK->new_msglog->msglog_write_top;
  scrLoadLocalizeTextSave(msglog_write_top);
  v10 = GBWK->new_msglog->meslog_mesTag[msglog_write_top];
  v10[0] = 0;
  v12 = GBWK->new_msglog->meslog_mesTag[msglog_write_top];
  v12[1] = 0;
  v14 = GBWK->new_msglog->meslog_mesTag[msglog_write_top];
  v14[2] = 0;
  v16 = GBWK->new_msglog->meslog_mesTag[msglog_write_top];
  v16[3] = 0;
  v18 = GBWK->new_msglog->meslog_mesTag[msglog_write_top];
  v18[4] = 0;
  v20 = GBWK->new_msglog->meslog_mesTag[msglog_write_top];
  v20[5] = 0;
  v22 = GBWK->new_msglog->meslog_mesTag[msglog_write_top];
  v22[6] = 0;
  v24 = GBWK->new_msglog->meslog_mesTag[msglog_write_top];
  v24[7] = 0;
  v26 = GBWK->new_msglog->meslog_mesTag[msglog_write_top];
  if (IsNullOrEmpty(mesTag, 0))
  {
    v27 = "";
    goto LABEL_34;
  }
  ASCII = get_ASCII(0);
  (ASCII->klass->vtable._16_GetBytes.methodPtr)(ASCII, mesTag, ASCII->klass->vtable._16_GetBytes.method);
  if (get_Chars(mesTag, 0, 0))
    v27 = mesTag;
  else
    v27 = "";
LABEL_34:
  v26[0] = v27;
  meslog_spkTag = GBWK->new_msglog->meslog_spkTag;
  if (IsNullOrEmpty(spkTag, 0))
  {
    v31 = "";
  }
  else
  {
    v32 = get_ASCII(0);
    (v32->klass->vtable._16_GetBytes.methodPtr)(v32, spkTag, v32->klass->vtable._16_GetBytes.method);
    if (get_Chars(spkTag, 0, 0))
      v31 = spkTag;
    else
      v31 = "";
  }
  v33 = &meslog_spkTag->obj.klass + msglog_write_top;
  v33[4] = v31;
  meslog_voiceTag = GBWK->new_msglog->meslog_voiceTag;
  if (IsNullOrEmpty(voiceTag, 0))
  {
    v35 = "";
    v36 = &meslog_voiceTag->obj.klass + msglog_write_top;
    v36[4] = "";
    goto LABEL_51;
  }
  v38 = get_ASCII(0);
  (v38->klass->vtable._16_GetBytes.methodPtr)(v38, voiceTag, v38->klass->vtable._16_GetBytes.method);
  if (get_Chars(voiceTag, 0, 0))
    v39 = voiceTag;
  else
    v39 = "";
  v40 = &meslog_voiceTag->obj.klass + msglog_write_top;
  v40[4] = v39;
LABEL_51:
  VariableRequest = frGetVariableRequest(0);
  if (IsNullOrEmpty(VariableRequest, 0))
    v42 = "";
  else
    v42 = VariableRequest;
  PlayerName = Copy(v42);
  if (IsNullOrEmpty(PlayerName, 0) && !IsNullOrEmpty(mesTag, 0) && (Equals_54828784(mesTag, "<CMP_USE_MSG_L0016>", 0) || Equals_54828784(mesTag, "<CMP_USE_MSG_L0017>", 0) || Equals_54828784(mesTag, "<CMP_USE_MSG_L0018>", 0)))
  {
    PlayerName = sBtlGetPlayerName();
  }
  v45 = GBWK->new_msglog->gVarStr[msglog_write_top];
  v45[0] = PlayerName;
  v46 = 40;
  v47 = 1;
  do
  {
    v52 = frGetVariableRequest(v47);
    if (IsNullOrEmpty(v52, 0))
      v48 = "";
    else
      v48 = v52;
    v49 = Copy(v48);
    v51 = ((char *)GBWK->new_msglog->gVarStr[msglog_write_top] + v46);
    *v51 = v49;
    v46 += 8;
    ++v47;
  }
  while (v46 != 96);
  GBWK->new_msglog->gParam[msglog_write_top][0] = GBWK->mapSummonID;
  NewLogSaveNext();
}

// 0x2145a70
void scrNewLogSaveSelLabel(void *sel_label) {
  s64 msglog_write_top;
  char *v6;
  char *v8;
  char *v10;
  char *v12;
  char *v14;
  char *v16;
  char *v18;
  char *v20;
  s64 v21;
  s64 v22;
  void *v23;
  char *v24;
  Il2CppClass **v25;
  char *v27;
  Il2CppObject *Item;
  char *meslog_spkTag;
  char *v30;
  char *v31;
  void *ASCII;
  Il2CppClass **v33;
  char *v34;
  char *meslog_voiceTag;

  msglog_write_top = GBWK->new_msglog->msglog_write_top;
  scrLoadLocalizeTextSave(msglog_write_top);
  v6 = GBWK->new_msglog->meslog_mesTag[msglog_write_top];
  v6[0] = 0;
  v8 = GBWK->new_msglog->meslog_mesTag[msglog_write_top];
  v8[1] = 0;
  v10 = GBWK->new_msglog->meslog_mesTag[msglog_write_top];
  v10[2] = 0;
  v12 = GBWK->new_msglog->meslog_mesTag[msglog_write_top];
  v12[3] = 0;
  v14 = GBWK->new_msglog->meslog_mesTag[msglog_write_top];
  v14[4] = 0;
  v16 = GBWK->new_msglog->meslog_mesTag[msglog_write_top];
  v16[5] = 0;
  v18 = GBWK->new_msglog->meslog_mesTag[msglog_write_top];
  v18[6] = 0;
  v20 = GBWK->new_msglog->meslog_mesTag[msglog_write_top];
  v20[7] = 0;
  if (sel_label->_size >= 1)
  {
    v21 = 0;
    v22 = 32;
    do
    {
      v27 = GBWK->new_msglog->meslog_mesTag[msglog_write_top];
      Item = _get_Item(sel_label, v21);
      *(Il2CppClass **)((char *)&v27->obj.klass + v22) = Item;
      meslog_spkTag = GBWK->new_msglog->meslog_spkTag;
      v30 = "";
      if (!IsNullOrEmpty(v30, 0))
      {
        ASCII = get_ASCII(0);
        (ASCII->klass->vtable._16_GetBytes.methodPtr)(ASCII, v30, ASCII->klass->vtable._16_GetBytes.method);
        if (get_Chars(v30, 0, 0))
          v31 = v30;
        else
          v31 = "";
        goto LABEL_38;
      }
      v31 = "";
LABEL_38:
      v33 = &meslog_spkTag->obj.klass + msglog_write_top;
      v33[4] = v31;
      v34 = "";
      meslog_voiceTag = GBWK->new_msglog->meslog_voiceTag;
      if (IsNullOrEmpty(v34, 0))
      {
        v24 = "";
      }
      else
      {
        v23 = get_ASCII(0);
        (v23->klass->vtable._16_GetBytes.methodPtr)(v23, v34, v23->klass->vtable._16_GetBytes.method);
        if (get_Chars(v34, 0, 0))
          v24 = v34;
        else
          v24 = "";
      }
      v25 = &meslog_voiceTag->obj.klass + msglog_write_top;
      v25[4] = v24;
      ++v21;
      v22 += 8;
    }
    while (v21 < sel_label->_size);
  }
}

// 0x2145f10
void scrNewLogSaveSel(s32 sel_result) {
  GBWK->new_msglog->msglog_sel_result[GBWK->new_msglog->msglog_write_top] = sel_result;
  NewLogSaveNext();
}

// 0x2145430
void scrLoadLocalizeTextSave(s32 wtop) {
  void *p_fileList;
  s64 v6;
  void *fileList_local;
  s64 v9;
  char *v10;
  char *v11;
  char *v13;
  char *v14;
  char *v16;
  char *v17;
  char *v19;
  char *v20;
  char *v22;
  char *v23;
  char *v25;
  char *v26;
  char *v28;
  char *v29;
  char *v31;
  char *v32;
  __int128 v33;
  s64 v34;
  __int128 v35;
  _BOOL4 v36;
  bool v37;
  s64 v39;
  Il2CppClass **v40;
  _OWORD v41[2];
  s64 v42;
  __int128 v43;
  __int128 v44;
  s64 v45;

  v45 = 0;
  v43 = 0u;
  v44 = 0u;
  p_fileList = &fileList;
  v6 = wtop;
  fileList_local = p_fileList;
  v9 = v6;
  v10 = GBWK->new_msglog->meslog_key[v6];
  v10[0] = 0;
  v11 = GBWK->new_msglog->meslog_filename[v6];
  v11[0] = 0;
  v13 = GBWK->new_msglog->meslog_key[v9];
  v13[1] = 0;
  v14 = GBWK->new_msglog->meslog_filename[v9];
  v14[1] = 0;
  v16 = GBWK->new_msglog->meslog_key[v9];
  v16[2] = 0;
  v17 = GBWK->new_msglog->meslog_filename[v9];
  v17[2] = 0;
  v19 = GBWK->new_msglog->meslog_key[v9];
  v19[3] = 0;
  v20 = GBWK->new_msglog->meslog_filename[v9];
  v20[3] = 0;
  v22 = GBWK->new_msglog->meslog_key[v9];
  v22[4] = 0;
  v23 = GBWK->new_msglog->meslog_filename[v9];
  v23[4] = 0;
  v25 = GBWK->new_msglog->meslog_key[v9];
  v25[5] = 0;
  v26 = GBWK->new_msglog->meslog_filename[v9];
  v26[5] = 0;
  v28 = GBWK->new_msglog->meslog_key[v9];
  v28[6] = 0;
  v29 = GBWK->new_msglog->meslog_filename[v9];
  v29[6] = 0;
  v31 = GBWK->new_msglog->meslog_key[v9];
  v31[7] = 0;
  v32 = GBWK->new_msglog->meslog_filename[v9];
  v32[7] = 0;
  _GetEnumerator(v41, fileList_local);
  v33 = v41[0];
  v34 = 0;
  *(u64 *)&v41[0] = 0;
  *((u64 *)&v41[0] + 1) = &v43;
  v45 = v42;
  v43 = v33;
  v44 = v41[1];
  while (_MoveNext(&v43))
  {
    v35 = v44;
    v36 = IsNullOrEmpty(*((char **)&v44 + 1), 0)
       || IndexOf_54852384(*((char **)&v35 + 1), "DBOOK_DLC", 0) != 0;
    if (IsNullOrEmpty(*((char **)&v35 + 1), 0))
    {
      if (v36)
        goto LABEL_31;
    }
    else
    {
      if (IndexOf_54852384(*((char **)&v35 + 1), "MAP06", 0))
        v37 = v36;
      else
        v37 = 0;
      if (v37)
      {
LABEL_31:
        v39 = (s64)GBWK->new_msglog->meslog_key[v6] + 8 * v34;
        *(u64 *)(v39 + 32) = v35;
        v40 = &GBWK->new_msglog->meslog_filename[v6]->obj.klass
            + v34;
        v40[4] = *((Il2CppClass **)&v35 + 1);
        if (++v34 == 8)
          break;
      }
    }
  }
  _Dispose(&v43);
}

// 0x2145fc0
static bool IsSameFL(s32 wtop, char *key, char *filename) {
  u64 v7;
  s64 v8;
  char v9;
  bool v10;
  s64 v12;
  NEW_MSGLOG *new_msglog;
  char *v14;
  NEW_MSGLOG *v16;
  char *v17;
  NEW_MSGLOG *v19;
  char *v20;
  NEW_MSGLOG *v22;
  char *v23;
  NEW_MSGLOG *v25;
  char *v26;
  NEW_MSGLOG *v28;
  char *v29;
  NEW_MSGLOG *v31;
  char *v32;
  NEW_MSGLOG *v34;
  char *v35;

  v7 = 0;
  v8 = wtop;
  v9 = 1;
  do
  {
    if (v8 != v7)
    {
      v12 = v7;
      new_msglog = GBWK->new_msglog;
      v14 = new_msglog->meslog_filename[v7][0];
      if (Equals_54828784(key, new_msglog->meslog_key[v7][0], 0) && Equals_54828784(filename, v14, 0))
      {
        break;
      }
      v16 = GBWK->new_msglog;
      v17 = v16->meslog_filename[v12][1];
      if (Equals_54828784(key, v16->meslog_key[v12][1], 0) && Equals_54828784(filename, v17, 0))
      {
        break;
      }
      v19 = GBWK->new_msglog;
      v20 = v19->meslog_filename[v12][2];
      if (Equals_54828784(key, v19->meslog_key[v12][2], 0) && Equals_54828784(filename, v20, 0))
      {
        break;
      }
      v22 = GBWK->new_msglog;
      v23 = v22->meslog_filename[v12][3];
      if (Equals_54828784(key, v22->meslog_key[v12][3], 0) && Equals_54828784(filename, v23, 0))
      {
        break;
      }
      v25 = GBWK->new_msglog;
      v26 = v25->meslog_filename[v12][4];
      if (Equals_54828784(key, v25->meslog_key[v12][4], 0) && Equals_54828784(filename, v26, 0))
      {
        break;
      }
      v28 = GBWK->new_msglog;
      v29 = v28->meslog_filename[v12][5];
      if (Equals_54828784(key, v28->meslog_key[v12][5], 0) && Equals_54828784(filename, v29, 0))
      {
        break;
      }
      v31 = GBWK->new_msglog;
      v32 = v31->meslog_filename[v12][6];
      if (Equals_54828784(key, v31->meslog_key[v12][6], 0) && Equals_54828784(filename, v32, 0))
      {
        break;
      }
      v34 = GBWK->new_msglog;
      v35 = v34->meslog_filename[v12][7];
      if (Equals_54828784(key, v34->meslog_key[v12][7], 0) && Equals_54828784(filename, v35, 0))
      {
        break;
      }
    }
    v10 = v7++ >= 0x1D;
    v9 = !v10;
  }
  while (v7 != 30);
  return v9;
}

// 0x2146360
void scrLoadLocalizeMsgLog(void) {
  s32 size;
  s32 v5;
  s32 v7;
  s32 v8;
  s64 v9;
  s64 i;
  s64 v11;
  const MethodInfo_2EEBD00 *v12;
  char *v14;
  void *ASCII;
  char *Item1;
  char *Item2;
  void *v21;
  s32 v22;
  s32 v23;
  void *v28;
  u64 *v29;
  s32 v30;
  EvtMsgDat *v31;
  char *v32;
  void *v33;
  void *v38;
  s64 v39;
  u64 *v40;
  void *v41;
  Il2CppClass **v42;
  void *v46;
  s64 v47;
  u64 *v48;
  void *items;
  Il2CppClass **v50;
  u64 *v52;
  s32 v53;
  EvtMsgDat *v54;
  __int128 v55;
  s32 v56;
  Il2CppObject *Item;
  void *v59;
  s32 v60;
  s32 v62;
  SCRLOG *v63;
  EvtMsgDat v66;
  EvtMsgDat v67;
  System_ValueTuple_string__string__o v68;

  size = ml_fileList->_size;
  v5 = ml_fileList->_version + 1;
  ml_fileList->_size = 0;
  ml_fileList->_version = v5;
  if (size >= 1)
  {
    Clear(ml_fileList->_items, 0, size, 0);
  }
  v7 = aloadList->_size;
  v8 = aloadList->_version + 1;
  aloadList->_size = 0;
  aloadList->_version = v8;
  if (v7 >= 1)
    Clear(aloadList->_items, 0, v7, 0);
  v9 = 0;
  while (2)
  {
    for (i = 32; i != 96; i += 8)
    {
      v14 = *(char **)((char *)&GBWK->new_msglog->meslog_mesTag[v9]->obj.klass + i);
      if (IsNullOrEmpty(v14, 0))
      {
        v14 = "";
        goto LABEL_25;
      }
      ASCII = get_ASCII(0);
      (ASCII->klass->vtable._16_GetBytes.methodPtr)(ASCII, v14, ASCII->klass->vtable._16_GetBytes.method);
      if (!get_Chars(v14, 0, 0))
        v14 = "";
LABEL_25:
      MxxLog(v14);
      v68 = ExxLog(v14);
      Item1 = v68.Item1;
      Item2 = v68.Item2;
      if (!IsNullOrEmpty(v68.Item2, 0))
        goto LABEL_39;
      Item1 = *(char **)((char *)&GBWK->new_msglog->meslog_key[v9]->obj.klass + i);
      if (!IsNullOrEmpty(Item1, 0))
      {
        v21 = get_ASCII(0);
        (v21->klass->vtable._16_GetBytes.methodPtr)(v21, Item1, v21->klass->vtable._16_GetBytes.method);
        if (!get_Chars(Item1, 0, 0))
          Item1 = "";
        goto LABEL_36;
      }
      Item1 = "";
LABEL_36:
      Item2 = *(char **)((char *)&GBWK->new_msglog->meslog_filename[v9]->obj.klass + i);
      if (!IsNullOrEmpty(*(char **)((char *)&GBWK->new_msglog->meslog_filename[v9]->obj.klass + i), 0))
        goto LABEL_56;
      goto LABEL_9002;
      if (!IsNullOrEmpty(Item2, 0))
      {
LABEL_56:
        v33 = get_ASCII(0);
        (v33->klass->vtable._16_GetBytes.methodPtr)(v33, Item2, v33->klass->vtable._16_GetBytes.method);
        if (!get_Chars(Item2, 0, 0))
          Item2 = "";
        if (IsNullOrEmpty(Item2, 0))
          continue;
        goto LABEL_40;
      }
LABEL_9002:
      Item2 = "";
LABEL_39:
      if (IsNullOrEmpty(Item2, 0))
        continue;
LABEL_40:
      v22 = ContainsKeyName(Item1);
      v23 = ContainsFileName(Item2);
      if (v22 < 0 || v23 < 0)
      {
        if ((v22 & 0x80000000) == 0 && v23 < 0)
        {
          if (IsLoad(Dependent, Item1, 0))
          {
            goto LABEL_48;
          }
          Load(Dependent, Item1, Item1);
          LoadSyncAll(_Ctrl_k__BackingField, 0);
          v46 = aloadList;
          v47 = v46->_size;
          v48 = Method_System_Collections_Generic_List_string__Add__;
          ++v46->_version;
          items = v46->_items;
          if ((u32)v47 >= LODWORD(items->max_length))
          {
            _AddWithResize(v46, Item1, *(const MethodInfo_2DFC660 **)(*(u64 *)(v48[4] + 192) + 112));
          }
          else
          {
            v46->_size = v47 + 1;
            v50 = &items->obj.klass + v47;
            v50[4] = Item1;
          }
LABEL_49:
          goto LABEL_50;
LABEL_48:
          goto LABEL_49;
LABEL_50:
          LoadLocalizeText_2(Item1, Item2);
          v28 = ml_fileList;
          memset(&v66, 0, sizeof(v66));
          _ctor(&v66, Item1, Item2, 0, 0);
          v29 = Method_System_Collections_Generic_List_Localize_EvtMsgDat__Add__;
          v30 = v28->_size;
          ++v28->_version;
          v31 = v28->_items;
          if ((u32)v30 >= LODWORD(v31->max_length))
          {
            v11 = v29[4];
LABEL_13:
            v12 = *(const MethodInfo_2EEBD00 **)(*(u64 *)(v11 + 192) + 112);
            v67 = v66;
            _AddWithResize(v28, &v67, v12);
            continue;
          }
          v28->_size = v30 + 1;
          v32 = (char *)v31 + 24 * v30;
LABEL_91:
          v55 = *(_OWORD *)&v66.key;
          *((u64 *)v32 + 6) = v66.data;
          *((_OWORD *)v32 + 2) = v55;
          continue;
        }
        if (!map16chk(Item1))
          continue;
        Load(Dependent, Item1, Item1);
        LoadSyncAll(_Ctrl_k__BackingField, 0);
        v38 = aloadList;
        v39 = v38->_size;
        v40 = Method_System_Collections_Generic_List_string__Add__;
        ++v38->_version;
        v41 = v38->_items;
        if ((u32)v39 >= LODWORD(v41->max_length))
        {
          _AddWithResize(v38, Item1, *(const MethodInfo_2DFC660 **)(*(u64 *)(v40[4] + 192) + 112));
        }
        else
        {
          v38->_size = v39 + 1;
          v42 = &v41->obj.klass + v39;
          v42[4] = Item1;
          goto LABEL_85;
        }
LABEL_85:
        LoadLocalizeText_2(Item1, Item2);
        v28 = ml_fileList;
        memset(&v66, 0, sizeof(v66));
        _ctor(&v66, Item1, Item2, 0, 0);
        v52 = Method_System_Collections_Generic_List_Localize_EvtMsgDat__Add__;
        v53 = v28->_size;
        ++v28->_version;
        v54 = v28->_items;
        if ((u32)v53 >= LODWORD(v54->max_length))
        {
          v11 = v52[4];
          goto LABEL_13;
        }
        v28->_size = v53 + 1;
        v32 = (char *)v54 + 24 * v53;
        goto LABEL_91;
      }
    }
    if (++v9 != 30)
      continue;
    break;
  }
  v56 = 0;
  while (2)
  {
    v59 = aloadList;
    v60 = v59->_size;
    if (v56 < v60)
    {
      Item = _get_Item(aloadList, v56);
      Unload(Dependent, Item, 0);
      ++v56;
      continue;
    }
    break;
  }
  v62 = v59->_version + 1;
  v59->_size = 0;
  v59->_version = v62;
  if (v60 >= 1)
    goto LABEL_113;
  goto LABEL_9004;
  if (v60 >= 1)
LABEL_113:
    Clear(v59->_items, 0, v60, 0);
LABEL_9004:
  v63 = Allocate(SCRLOG);
  _ctor(v63, 0);
  InitNewMsgLogList(v63);
  SetLog(v63);
}

// 0x21475b0
static void Fload(char *key, char *filename, bool add) {
  void *ml_fileList_local;
  s32 size;
  u64 *v11;
  EvtMsgDat *items;
  __int128 v13;
  char *v14;
  const MethodInfo_2EEBD00 *v15;
  EvtMsgDat v16;
  EvtMsgDat v17;

  LoadLocalizeText_2(key, filename);
  if (!add)
    return;
  ml_fileList_local = ml_fileList;
  memset(&v16, 0, sizeof(v16));
  _ctor(&v16, key, filename, 0, 0);
  size = ml_fileList_local->_size;
  v11 = Method_System_Collections_Generic_List_Localize_EvtMsgDat__Add__;
  ++ml_fileList_local->_version;
  items = ml_fileList_local->_items;
  if ((u32)size >= LODWORD(items->max_length))
  {
    v15 = *(const MethodInfo_2EEBD00 **)(*(u64 *)(v11[4] + 192) + 112);
    v17 = v16;
    _AddWithResize(ml_fileList_local, &v17, v15);
  }
  else
  {
    v13 = *(_OWORD *)&v16.key;
    ml_fileList_local->_size = size + 1;
    v14 = (char *)items + 24 * size;
    *((u64 *)v14 + 6) = v16.data;
    *((_OWORD *)v14 + 2) = v13;
  }
}

// 0x2147770
static bool map16chk(char *key) {
  if (Equals_54828784(key, "map16_dea_msg.", 0))
  {
    if ((ContainsKeyName("map26_dea_msg.") & 0x80000000) == 0)
      return 0;
    if ((ContainsKeyName("map29_dea_msg.") & 0x80000000) == 0)
      return 0;
    if ((ContainsKeyName("map30_dea_msg.") & 0x80000000) == 0)
      return 0;
  }
  if (Equals_54828784(key, "map16_de1_msg.", 0))
  {
    if ((ContainsKeyName("map26_de1_msg.") & 0x80000000) == 0)
      return 0;
    if ((ContainsKeyName("map29_de1_msg.") & 0x80000000) == 0)
      return 0;
    if ((ContainsKeyName("map30_de1_msg.") & 0x80000000) == 0)
      return 0;
  }
  if (Equals_54828784(key, "map16_de2_msg.", 0))
  {
    if ((ContainsKeyName("map26_de2_msg.") & 0x80000000) == 0)
      return 0;
    if ((ContainsKeyName("map29_de2_msg.") & 0x80000000) == 0)
      return 0;
    if ((ContainsKeyName("map30_de2_msg.") & 0x80000000) == 0)
      return 0;
  }
  if (!Equals_54828784(key, "map16_de3_msg.", 0))
    goto LABEL_166;
  if (ContainsKeyName("map26_de3_msg.") < 0)
  {
    if (ContainsKeyName("map29_de3_msg.") < 0)
    {
      if (ContainsKeyName("map30_de3_msg.") < 0)
      {
LABEL_166:
        if (!Equals_54828784(key, "map26_dea_msg.", 0))
          goto LABEL_172;
        if (ContainsKeyName("map16_dea_msg.") < 0)
        {
          if (ContainsKeyName("map29_dea_msg.") < 0)
          {
            if (ContainsKeyName("map30_dea_msg.") < 0)
            {
LABEL_172:
              if (!Equals_54828784(key, "map26_de1_msg.", 0))
                goto LABEL_173;
              if (ContainsKeyName("map16_de1_msg.") < 0)
              {
                if (ContainsKeyName("map29_de1_msg.") < 0)
                {
                  if (ContainsKeyName("map30_de1_msg.") < 0)
                  {
LABEL_173:
                    if (!Equals_54828784(key, "map26_de2_msg.", 0))
                      goto LABEL_174;
                    if (ContainsKeyName("map16_de2_msg.") < 0)
                    {
                      if (ContainsKeyName("map29_de2_msg.") < 0)
                      {
                        if (ContainsKeyName("map30_de2_msg.") < 0)
                        {
LABEL_174:
                          if (!Equals_54828784(key, "map26_de3_msg.", 0))
                            goto LABEL_175;
                          if (ContainsKeyName("map16_de3_msg.") < 0)
                          {
                            if (ContainsKeyName("map29_de3_msg.") < 0)
                            {
                              if (ContainsKeyName("map30_de3_msg.") < 0)
                              {
LABEL_175:
                                if (!Equals_54828784(key, "map29_dea_msg.", 0))
                                  goto LABEL_176;
                                if (ContainsKeyName("map16_dea_msg.") < 0)
                                {
                                  if (ContainsKeyName("map26_dea_msg.") < 0)
                                  {
                                    if (ContainsKeyName("map30_dea_msg.") < 0)
                                    {
LABEL_176:
                                      if (!Equals_54828784(key, "map29_de1_msg.", 0))
                                        goto LABEL_177;
                                      if (ContainsKeyName("map16_de1_msg.") < 0)
                                      {
                                        if (ContainsKeyName("map26_de1_msg.") < 0)
                                        {
                                          if (ContainsKeyName("map30_de1_msg.") < 0)
                                          {
LABEL_177:
                                            if (!Equals_54828784(key, "map29_de2_msg.", 0))
                                              goto LABEL_178;
                                            if (ContainsKeyName("map16_de2_msg.") < 0)
                                            {
                                              if (ContainsKeyName("map26_de2_msg.") < 0)
                                              {
                                                if (ContainsKeyName("map30_de2_msg.") < 0)
                                                {
LABEL_178:
                                                  if (!Equals_54828784(key, "map29_de3_msg.", 0))
                                                    goto LABEL_179;
                                                  if (ContainsKeyName("map16_de3_msg.") < 0)
                                                  {
                                                    if (ContainsKeyName("map26_de3_msg.") < 0)
                                                    {
                                                      if (ContainsKeyName("map30_de3_msg.") < 0)
                                                      {
LABEL_179:
                                                        if (!Equals_54828784(key, "map30_dea_msg.", 0))
                                                          goto LABEL_180;
                                                        if (ContainsKeyName("map16_dea_msg.") < 0)
                                                        {
                                                          if (ContainsKeyName("map26_dea_msg.") < 0)
                                                          {
                                                            if (ContainsKeyName("map29_dea_msg.") < 0)
                                                            {
LABEL_180:
                                                              if (!Equals_54828784(key, "map30_de1_msg.", 0))
                                                                goto LABEL_181;
                                                              if (ContainsKeyName("map16_de1_msg.") < 0)
                                                              {
                                                                if (ContainsKeyName("map26_de1_msg.") < 0)
                                                                {
                                                                  if (ContainsKeyName("map29_de1_msg.") < 0)
                                                                  {
LABEL_181:
                                                                    if (!Equals_54828784(key, "map30_de2_msg.", 0))
                                                                      goto LABEL_182;
                                                                    if (ContainsKeyName("map16_de2_msg.") < 0)
                                                                    {
                                                                      if (ContainsKeyName("map26_de2_msg.") < 0)
                                                                      {
                                                                        if (ContainsKeyName("map29_de2_msg.") < 0)
                                                                        {
LABEL_182:
                                                                          if (!Equals_54828784(key, "map30_de3_msg.", 0))
                                                                            return 1;
                                                                          if (ContainsKeyName("map16_de3_msg.") < 0)
                                                                          {
                                                                            if (ContainsKeyName("map26_de3_msg.") < 0)
                                                                            {
                                                                              if (ContainsKeyName("map29_de3_msg.") < 0)
                                                                                return 1;
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
    }
  }
  return 0;
}

// 0x2147270
static void *ExxLog(char *mestag) {
  Il2CppObject *v3;
  bool IsNullOrEmpty;
  const MethodInfo_3353F10 *v5;
  Il2CppObject *v6;
  char **v7;
  char *v10;
  char *v11;
  System_ValueTuple_object__object__o v12;
  System_ValueTuple_string__string__o result;

  v3 = "";
  IsNullOrEmpty = IsNullOrEmpty(mestag, 0);
  v6 = "event_msg.";
  if (!IsNullOrEmpty)
  {
    if (IndexOf_54852384(mestag, "<E50", 0))
    {
      if (IndexOf_54852384(mestag, "<E60", 0))
      {
        if (IndexOf_54852384(mestag, "<E61", 0))
        {
          if (IndexOf_54852384(mestag, "<E62", 0))
          {
            if (IndexOf_54852384(mestag, "<E65", 0))
            {
              if (IndexOf_54852384(mestag, "<E66", 0))
              {
                if (IndexOf_54852384(mestag, "<E68", 0))
                {
                  if (IndexOf_54852384(mestag, "<E69", 0))
                  {
                    if (IndexOf_54852384(mestag, "<E80", 0))
                    {
                      if (!IndexOf_54852384(mestag, "<E81", 0))
                        v3 = "E81X";
                      goto LABEL_26;
                    }
                    v7 = &"E80X";
                  }
                  else
                  {
                    v7 = &"E69X";
                  }
                }
                else
                {
                  v7 = &"E68X";
                }
              }
              else
              {
                v7 = &"E66X";
              }
            }
            else
            {
              v7 = &"E65X";
            }
          }
          else
          {
            v7 = &"E62X";
          }
        }
        else
        {
          v7 = &"E61X";
        }
      }
      else
      {
        v7 = &"E60X";
      }
    }
    else
    {
      v7 = &"E50X";
    }
    v3 = *v7;
  }
LABEL_26:
  v12.Item1 = &v10;
  v12.Item2 = v6;
  v10 = 0;
  v11 = 0;
  object____ctor(v12, v3, Method_System_ValueTuple_string__string___ctor__, v5);
  result.Item1 = v10;
  result.Item2 = v11;
  return result;
}

// 0x2146dd0
static void MxxLog(char *mestag) {
  __int128 v4;
  Il2CppObject *key;
  Il2CppObject *value;
  s32 v8;
  s32 v9;
  void *v16;
  u64 *v17;
  s64 v18;
  void *v19;
  Il2CppClass **v20;
  void *aloadList_local;
  u64 *v23;
  s64 size;
  void *items;
  Il2CppClass **v26;
  System_Collections_Generic_Dictionary_Enumerator_TKey__TValue__o v27;
  System_Collections_Generic_Dictionary_Enumerator_TKey__TValue__o v28;

  if (!IndexOf_54852384(mestag, "<MAP06", 0))
  {
    object___GetEnumerator(&v27, MxxTbl);
    v4 = *(_OWORD *)&v27._dictionary;
    v27._dictionary = 0;
    *(u64 *)&v27._version = &v28;
    *(u64 *)&v28._getEnumeratorRetType = *(u64 *)&v27._getEnumeratorRetType;
    *(_OWORD *)&v28._dictionary = v4;
    v28._current = v27._current;
    while (1)
    {
      do
      {
        if (!object___MoveNext(&v28))
        {
          object___Dispose(&v28);
          return;
        }
        key = v28._current.key;
        value = v28._current.value;
        v8 = ContainsKeyName(value);
        v9 = ContainsFileName(key);
      }
      while ((v8 & 0x80000000) == 0 && (v9 & 0x80000000) == 0);
      if ((v8 & 0x80000000) == 0 && v9 < 0)
      {
        if (!IsLoad(Dependent, value, 0))
        {
          Load(Dependent, value, value);
          LoadSyncAll(_Ctrl_k__BackingField, 0);
          aloadList_local = aloadList;
          v23 = Method_System_Collections_Generic_List_string__Add__;
          size = aloadList_local->_size;
          ++aloadList_local->_version;
          items = aloadList_local->_items;
          if ((u32)size >= LODWORD(items->max_length))
          {
            _AddWithResize(aloadList_local, value, *(const MethodInfo_2DFC660 **)(*(u64 *)(v23[4] + 192) + 112));
          }
          else
          {
            aloadList_local->_size = size + 1;
            v26 = &items->obj.klass + size;
            v26[4] = value;
          }
        }
        goto LABEL_10;
      }
      Load(Dependent, value, value);
      LoadSyncAll(_Ctrl_k__BackingField, 0);
      v16 = aloadList;
      v17 = Method_System_Collections_Generic_List_string__Add__;
      v18 = v16->_size;
      ++v16->_version;
      v19 = v16->_items;
      if ((u32)v18 >= LODWORD(v19->max_length))
      {
        _AddWithResize(v16, value, *(const MethodInfo_2DFC660 **)(*(u64 *)(v17[4] + 192) + 112));
      }
      else
      {
        v16->_size = v18 + 1;
        v20 = &v19->obj.klass + v18;
        v20[4] = value;
      }
LABEL_10:
      Fload(value, key, 1);
    }
  }
}

// 0x21481a0
void scrRemoveLocalizeMsgLog(void) {
  char *v3;
  s32 size;
  s32 v7;
  __int128 v8;
  __int128 v9;
  s64 v10;

  v10 = 0;
  v8 = 0u;
  v9 = 0u;
  _GetEnumerator(&v8, ml_fileList);
  while (_MoveNext(&v8))
  {
    v3 = *((char **)&v9 + 1);
    Remove_30362592(v3, 0);
  }
  _Dispose(&v8);
  size = ml_fileList->_size;
  v7 = ml_fileList->_version + 1;
  ml_fileList->_size = 0;
  ml_fileList->_version = v7;
  if (size >= 1)
    Clear(ml_fileList->_items, 0, size, 0);
}

// 0x2148380
static void LinkScriptHandleList(scrHandle_t *h) {
  scrHandle_t *v7;

  if (!HandleLast)
  {
    HandleFirst = h;
    HandleLast = h;
    h->prev = 0;
    h->next = 0;
    goto LABEL_8;
  }
  h->prev = HandleLast;
  v7 = HandleLast;
  v7->next = h;
  h->next = 0;
  HandleLast = h;
LABEL_8:
  ++HandleCount;
}

// 0x21484f0
static void UnlinkScriptHandleList(scrHandle_t *h) {
  scrHandle_t *prev;
  scrHandle_t *next;
  scrHandle_t *v9;
  scrHandle_t *v10;
  scrHandle_t *p_prev;
  scrHandle_t *v12;
  scrHandle_t *v13;

  if (HandleFirst != h)
  {
    prev = h->prev;
    next = h->next;
    prev->next = next;
    goto LABEL_5;
  }
  v12 = h->next;
  HandleFirst = v12;
LABEL_5:
  if (HandleLast != h)
  {
    v10 = h->prev;
    v9 = h->next;
    v9->prev = v10;
    p_prev = &v9->prev;
    goto LABEL_16;
  }
  v13 = h->prev;
  HandleLast = v13;
  p_prev = &HandleLast;
  v10 = v13;
LABEL_16:
  h->prev = 0;
  h->next = 0;
  --HandleCount;
}

// 0x2148670
static scrHandle_t *AddScript(scrHeader_t *header, scrTypeTable_t *typetable, scrProcTable_t *proctable, scrLabelTable_t *labeltable, scrCode_t *code, u8 *mesdata, u8 *stringdata, s32 startproc) {
  scrHandle_t *v16;
  scrHandle_t *v18;
  Il2CppClass **v19;
  char *name;
  scrHandle_t *p_fields;
  Il2CppClass *v22;
  s64 v23;
  scrStackData_t *StackData;
  s64 v25;
  s64 v26;
  Il2CppObject *v27;
  void *p_LocalInt;
  void *p_LocalFloat;
  void *v31;
  s32 LocalFloatCount;
  void *v33;
  u8 *v36;
  scrHeader_t *object;
  u8 *v38;

  v16 = Allocate(scrHandle_t);
  _ctor(v16);
  v18 = 0;
  if ((startproc & 0x80000000) == 0 && header && typetable && proctable && code)
  {
    if (typetable[0]->ItemCount > startproc)
    {
      v19 = &proctable->obj.klass + (u32)startproc;
      v18 = v16;
      v38 = mesdata;
      v36 = stringdata;
      object = header;
      name = v19[4]->_1.name;
      v16->Name = name;
      p_fields = &v16->fields;
      v22 = v19[4];
      v23 = 32;
      StackData = p_fields->StackData;
      v25 = 32;
      *(u64 *)&p_fields->CP = LODWORD(v22->_1.namespaze);
      do
      {
        v27 = Allocate(scrStackData_t);
        _ctor(v27, 0);
        *(Il2CppClass **)((char *)&StackData->obj.klass + v25) = v27;
        *((u8 *)&v18->StackType->obj.klass + v23++) = 0;
        StackData = v18->StackData;
        v26 = *(s64 *)((char *)&StackData->obj.klass + v25);
        v25 += 8;
        *(u32 *)(v26 + 16) = 0;
      }
      while (v23 != 60);
      v18->Header = header;
      v18->TypeTable = typetable;
      v18->ProcTable = proctable;
      v18->LabelTable = labeltable;
      v18->Code = code;
      v18->MessageData = v38;
      v18->StringData = v36;
      *(u64 *)&v18->ScriptTimer = 0;
      v18->LocalInt = 0;
      p_LocalInt = &v18->LocalInt;
      v18->StartProc = startproc;
      v18->MesHandle = -1;
      v18->LocalFloat = 0;
      p_LocalFloat = &v18->LocalFloat;
      v18->ProcessID = 0;
      v18->prev = 0;
      v18->next = 0;
      if (object->LocalIntCount < 1)
      {
        p_LocalInt = 0;
        LocalFloatCount = object->LocalFloatCount;
        if (LocalFloatCount >= 1)
        {
LABEL_17:
          v33 = NewSpecific(f32, (u16)LocalFloatCount);
          p_LocalFloat = v33;
          Clear(p_LocalFloat, 0, object->LocalFloatCount, 0);
          if (!v38)
            goto LABEL_18;
          goto LABEL_23;
        }
      }
      else
      {
        v31 = NewSpecific(s32, (u16)object->LocalIntCount);
        p_LocalInt = v31;
        Clear(p_LocalInt, 0, object->LocalIntCount, 0);
        LocalFloatCount = object->LocalFloatCount;
        if (LocalFloatCount >= 1)
          goto LABEL_17;
      }
      p_LocalFloat = 0;
      if (!v38)
      {
LABEL_18:
LABEL_19:
        sub_214E900(v18, 0);
        return v18;
      }
LABEL_23:
      v18->MesHandle = itfMesMngInitialize(&v38->obj, 0, 0);
      goto LABEL_19;
    }
    return 0;
  }
  return v18;
}

// 0x2148a30
static scrHandle_t *AddScript2(u8 *scrdata, s32 startproc) {
  scrHeader_t *v5;
  s64 TypeTableCount;
  scrTypeTable_t *v8;
  s32 v9;
  u64 v10;
  s64 v11;
  scrTypeTable_t *v12;
  s64 *v13;
  s64 v14;
  s64 v15;
  scrProcTable_t *v16;
  scrLabelTable_t *v17;
  scrCode_t *v18;
  Il2CppClass **v19;
  Il2CppClass *v20;
  char *v21;
  Il2CppClass *v22;
  s64 v23;
  s32 v24;
  scrLabelTable_t *v25;
  s64 v26;
  scrProcTable_t *v27;
  scrProcTable_t *v28;
  s64 v30;
  s32 v31;
  s64 v32;
  scrLabelTable_t *v33;
  scrLabelTable_t *v34;
  s64 v36;
  s32 v37;
  s64 v38;
  s64 *v39;
  scrCode_t *v40;
  s64 v42;
  s64 v43;
  s64 v44;
  s64 v45;
  u8 *v46;
  s32 v47;
  u32 namespaze;
  s64 v49;
  s64 v50;
  void *v51;
  s32 v52;
  void *v53;
  s32 namespaze_high;
  s32 max_length;
  s32 v56;
  s64 v57;
  s32 startproca;
  scrLabelTable_t *v62;
  u8 *mesdata;
  u8 *v64;
  scrHeader_t *v65;
  scrTypeTable_t *v66;
  s64 v67;
  s32 v68;
  s32 index;
  s32 totalsize[2];

  *(u64 *)totalsize = 0;
  index = 0;
  v5 = Allocate(scrHeader_t);
  _ctor(v5, scrdata, totalsize, &totalsize[1]);
  if (v5->MagicCode != 811027526)
    return 0;
  v65 = v5;
  TypeTableCount = (u32)v5->TypeTableCount;
  v8 = NewSpecific(scrTypeTable_t, TypeTableCount);
  startproca = startproc;
  if ((s32)TypeTableCount < 1)
  {
    mesdata = 0;
    v64 = 0;
    v18 = 0;
    v17 = 0;
    v16 = 0;
  }
  else
  {
    v67 = TypeTableCount;
    v9 = totalsize[0];
    v10 = 0;
    v11 = 8 * TypeTableCount;
    do
    {
      v12 = Allocate(scrTypeTable_t);
      v12->Type = ToInt32(scrdata, v9, 0);
      v12->ItemSize = ToInt32(scrdata, v9 + 4, 0);
      v12->ItemCount = ToInt32(scrdata, v9 + 8, 0);
      v12->ItemAddress = ToInt32(scrdata, v9 + 12, 0);
      v13 = &v8[v10 / 8];
      *v13 = v12;
      v10 += 8;
      v9 += 16;
    }
    while (v11 != v10);
    v14 = v67;
    v15 = 0;
    v16 = 0;
    v66 = v8;
    v17 = 0;
    v18 = 0;
    mesdata = 0;
    v64 = 0;
    do
    {
      v19 = &v8->obj.klass + v15;
      v22 = v19[4];
      v21 = (v19 + 4);
      v20 = v22;
      switch (LODWORD(v22->_1.name))
      {
        case 0:
          v23 = NewSpecific(scrProcTable_t, (u32)v20->_1.namespaze);
          v16 = v23;
          v24 = *(u32 *)(*(u64 *)v21 + 24);
          index = *(u32 *)(*(u64 *)v21 + 28);
          if (v24 < 1)
            goto LABEL_10;
          v25 = v17;
          v26 = 0;
          v27 = (v23 + 32);
          while (1)
          {
            v28 = Allocate(scrProcTable_t);
            _ctor(v28, scrdata, &index, &totalsize[1]);
            v27 = v28;
            ++v26;
            ++v27;
            if (v26 >= *(s32 *)(*(u64 *)v21 + 24))
              goto LABEL_9;
          }
        case 1:
          v30 = NewSpecific(scrLabelTable_t, (u32)v20->_1.namespaze);
          v17 = v30;
          v31 = *(u32 *)(*(u64 *)v21 + 24);
          v68 = *(u32 *)(*(u64 *)v21 + 28);
          if (v31 < 1)
            goto LABEL_10;
          v32 = 0;
          v25 = v30;
          v33 = (v30 + 32);
          do
          {
            v34 = Allocate(scrLabelTable_t);
            _ctor(v34, scrdata, &v68, &totalsize[1]);
            v33 = v34;
            ++v32;
            ++v33;
          }
          while (v32 < *(s32 *)(*(u64 *)v21 + 24));
LABEL_9:
          v8 = v66;
          v14 = v67;
          v17 = v25;
          goto LABEL_10;
        case 2:
          v36 = NewSpecific(scrCode_t, (u32)v20->_1.namespaze);
          v18 = v36;
          if (*(s32 *)(*(u64 *)v21 + 24) < 1)
            goto LABEL_10;
          v62 = v17;
          v37 = *(u32 *)(*(u64 *)v21 + 28);
          v38 = 0;
          v39 = (v36 + 32);
          break;
        case 3:
          namespaze = v20->_1.namespaze;
          if (!namespaze)
            goto LABEL_10;
          v49 = NewSpecific(byte, namespaze);
          v50 = *(u64 *)v21;
          v51 = v49;
          v52 = *(u32 *)(v49 + 24);
          v53 = scrdata;
          mesdata = v51;
LABEL_37:
          Copy_56175392(v53, *(u32 *)(v50 + 28), v51, 0, v52, 0);
          goto LABEL_10;
        case 4:
          namespaze_high = HIDWORD(v20->_1.namespaze);
          if (v15 + 1 == v65->TypeTableCount)
            max_length = scrdata->max_length;
          else
            max_length = v8[v15 + 1]->ItemAddress;
          v56 = max_length - namespaze_high;
          v57 = NewSpecific(byte, max_length - namespaze_high);
          v50 = *(u64 *)v21;
          v51 = v57;
          v53 = scrdata;
          v52 = v56;
          v64 = v51;
          goto LABEL_37;
        default:
          return 0;
      }
      do
      {
        v40 = Allocate(scrCode_t);
        *(u64 *)&v40->c0 = 0;
        *(u64 *)&v40->fm = 0;
        *(u32 *)((char *)v40 + 36) = 0;
        v40->im = 0;
        v40->vec = zeroVector;
        *v39 = v40;
        v42 = *v39;
        *(u32 *)(v42 + 16) = ToInt32(scrdata, v37, 0);
        v43 = *v39;
        *(f32 *)(v43 + 20) = ToSingle(scrdata, v37, 0);
        v44 = *v39;
        *(u16 *)(v44 + 24) = ToInt16(scrdata, v37, 0);
        v45 = *v39;
        *(u16 *)(v45 + 26) = ToInt16(scrdata, v37 + 2, 0);
        ++v38;
        v46 = (u8 *)*v39++;
        v46[28] = scrdata[v37];
        v46[29] = scrdata[v37 + 1];
        v46[30] = scrdata[v37 + 2];
        v47 = v37 + 3;
        v37 += 4;
        v46[31] = scrdata[v47];
      }
      while (v38 < *(s32 *)(*(u64 *)v21 + 24));
      v8 = v66;
      v14 = v67;
      v17 = v62;
LABEL_10:
      ++v15;
    }
    while (v15 != v14);
  }
  return AddScript(v65, v8, v16, v17, v18, mesdata, v64, startproca);
}

// 0x2149090
static scrHandle_t *AddScript3(char *asset_name, char *filename, s32 startproc) {
  void *Asset;
  sdfBinary *v11;
  u8 *data;
  scrHandle_t *v14;

  Load(Dependent, asset_name, asset_name);
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  Asset = LoadAsset(_Ctrl_k__BackingField, asset_name, filename, 0);
  v11 = Allocate(sdfBinary);
  _ctor(v11, Asset, 0);
  data = v11->data;
  v14 = AddScript2(data, startproc);
  Unload(Dependent, asset_name, 0);
  return v14;
}

// 0x2149250
static dds3ProcessID_t *StartScriptProcess(s32 priority, scrHandle_t *h, bool skip_enable) {
  char *Name;
  dds3ProcessFunc_t v8;
  shutdownfuncDelegate v9;
  dds3ProcessID_t *started;

  Name = h->ProcTable[h->StartProc]->Name;
  v8 = Allocate(dds3ProcessFunc_t);
  _ctor(v8, 0, Method_Project_scr_Process__, 0);
  v9 = Allocate(shutdownfuncDelegate);
  _ctor(v9, 0, Method_Project_scr_Shutdown__, 0);
  started = dds3StartProcess(Name, priority, 1, 1, v8, v9, h);
  h->ProcessID = started;
  if (skip_enable)
  {
    scrLogStart(started);
    fclDirectCallMesClear();
  }
  return started;
}

// 0x21493e0
void scrInitGlobalWork(void) {
  Clear(GBWK->IntVariable, 0, 256, 0);
  Clear(GBWK->FloatVariable, 0, 256, 0);
}

// 0x2149470
dds3ProcessID_t *scrStartScript3(s32 priority, char *asset_name, char *filename, s32 startproc, bool skip_enable) {
  scrHeader_t *v11;
  scrLabelTable_t *v12;
  scrCode_t *v13;
  u8 *v14;
  u8 *v15;
  s32 v17;

  v11 = AddScript3(asset_name, filename, startproc);
  return sub_214EA70(priority, v11, skip_enable, 0, v12, v13, v14, v15, v17);
}

// 0x2149510
scrHandle_t *scrRegistScript3(char *asset_name, char *filename) {
  return AddScript3(asset_name, filename, 0);
}

// 0x2149580
dds3ProcessID_t *scrStartScript2(s32 priority, u8 *scrdata, s32 startproc, bool skip_enable) {
  scrHeader_t *v9;
  scrLabelTable_t *v10;
  scrCode_t *v11;
  u8 *v12;
  u8 *v13;
  s32 v15;

  v9 = AddScript2(scrdata, startproc);
  return sub_214EA70(priority, v9, skip_enable, 0, v10, v11, v12, v13, v15);
}

// 0x2149610
scrHandle_t *scrRegistScript2(u8 *scrdata) {
  u8 *v5;

  v5 = scrdata;
  return AddScript2(v5, 0);
}

// 0x21496a0
dds3ProcessID_t *scrStartScript1(s32 priority, scrHeader_t *header, scrTypeTable_t *typetable, scrProcTable_t *proctable, scrLabelTable_t *labeltable, scrCode_t *code, u8 *mesdata, u8 *stringdata, s32 startproc) {
  scrHeader_t *v18;
  scrLabelTable_t *v19;
  scrCode_t *v20;
  u8 *v21;
  u8 *v22;

  v18 = AddScript(header, typetable, proctable, labeltable, code, mesdata, stringdata, startproc);
  return sub_214EA70(priority, v18, 0, 0, v19, v20, v21, v22, startproc);
}

// 0x2149780
scrHandle_t *scrRegistScript1(scrHeader_t *header, scrTypeTable_t *typetable, scrProcTable_t *proctable, scrLabelTable_t *labeltable, scrCode_t *code, u8 *mesdata, u8 *stringdata) {
  return AddScript(header, typetable, proctable, labeltable, code, mesdata, stringdata, 0);
}

// 0x2149840
void scrReleaseScript(scrHandle_t *h) {
  s32 MesHandle;

  MesHandle = h->MesHandle;
  if ((MesHandle & 0x80000000) == 0)
  {
    itfMesMngRelease(MesHandle);
  }
  sub_214EBF0(h, 0);
}

// 0x2149900
void scrAllReleaseScript(void) {
  scrHandle_t *HandleFirst_local;
  scrHandle_t *next;

  HandleFirst_local = HandleFirst;
  if (HandleFirst_local)
    goto LABEL_9;
  return;
  if (HandleFirst_local)
  {
    do
    {
LABEL_9:
      while (1)
      {
        next = HandleFirst_local->next;
        if (HandleFirst_local->ProcessID)
          break;
        scrReleaseScript(HandleFirst_local);
        HandleFirst_local = next;
        if (!next)
          return;
      }
      dds3KillProcess(&HandleFirst_local->ProcessID, 0);
      HandleFirst_local = next;
    }
    while (next);
  }
}

// 0x2149a20
s32 scrSetStartProc(scrHandle_t *h, s32 startproc) {
  s64 v5;
  char *Name;
  s8 *StackType;
  s8 *v9;
  s8 *v10;
  s8 *v11;
  s8 *v12;
  s8 *v13;
  s8 *v14;
  s8 *v15;
  s8 *v16;
  s8 *v17;
  s8 *v18;
  s8 *v19;
  s8 *v20;
  s8 *v21;
  s8 *v22;
  s8 *v23;
  s8 *v24;
  s8 *v25;
  s8 *v26;
  s8 *v27;
  s8 *v28;
  s8 *v29;
  s8 *v30;
  s8 *v31;
  s8 *v32;
  s8 *v33;
  s8 *v34;
  s8 *v35;

  if (startproc < 0)
    return 0;
  if (h->TypeTable[0]->ItemCount <= startproc)
    return 0;
  v5 = startproc;
  Name = h->ProcTable[v5]->Name;
  h->Name = Name;
  StackType = h->StackType;
  h->CP = h->ProcTable[v5]->CodeAddress;
  h->SP = 0;
  StackType[0] = 0;
  v9 = h->StackType;
  h->StackData[0]->im = 0;
  v9[1] = 0;
  v10 = h->StackType;
  h->StackData[1]->im = 0;
  v10[2] = 0;
  v11 = h->StackType;
  h->StackData[2]->im = 0;
  v11[3] = 0;
  v12 = h->StackType;
  h->StackData[3]->im = 0;
  v12[4] = 0;
  v13 = h->StackType;
  h->StackData[4]->im = 0;
  v13[5] = 0;
  v14 = h->StackType;
  h->StackData[5]->im = 0;
  v14[6] = 0;
  v15 = h->StackType;
  h->StackData[6]->im = 0;
  v15[7] = 0;
  v16 = h->StackType;
  h->StackData[7]->im = 0;
  v16[8] = 0;
  v17 = h->StackType;
  h->StackData[8]->im = 0;
  v17[9] = 0;
  v18 = h->StackType;
  h->StackData[9]->im = 0;
  v18[10] = 0;
  v19 = h->StackType;
  h->StackData[10]->im = 0;
  v19[11] = 0;
  v20 = h->StackType;
  h->StackData[11]->im = 0;
  v20[12] = 0;
  v21 = h->StackType;
  h->StackData[12]->im = 0;
  v21[13] = 0;
  v22 = h->StackType;
  h->StackData[13]->im = 0;
  v22[14] = 0;
  v23 = h->StackType;
  h->StackData[14]->im = 0;
  v23[15] = 0;
  v24 = h->StackType;
  h->StackData[15]->im = 0;
  v24[16] = 0;
  v25 = h->StackType;
  h->StackData[16]->im = 0;
  v25[17] = 0;
  v26 = h->StackType;
  h->StackData[17]->im = 0;
  v26[18] = 0;
  v27 = h->StackType;
  h->StackData[18]->im = 0;
  v27[19] = 0;
  v28 = h->StackType;
  h->StackData[19]->im = 0;
  v28[20] = 0;
  v29 = h->StackType;
  h->StackData[20]->im = 0;
  v29[21] = 0;
  v30 = h->StackType;
  h->StackData[21]->im = 0;
  v30[22] = 0;
  v31 = h->StackType;
  h->StackData[22]->im = 0;
  v31[23] = 0;
  v32 = h->StackType;
  h->StackData[23]->im = 0;
  v32[24] = 0;
  v33 = h->StackType;
  h->StackData[24]->im = 0;
  v33[25] = 0;
  v34 = h->StackType;
  h->StackData[25]->im = 0;
  v34[26] = 0;
  v35 = h->StackType;
  h->StackData[26]->im = 0;
  v35[27] = 0;
  h->StartProc = startproc;
  h->StackData[27]->im = 0;
  *(u64 *)&h->ScriptTimer = 0;
  return 1;
}

// 0x2149c90
scrHandle_t *scrSearchScriptName(char *scriptname) {
  scrHandle_t *HandleFirst_local;

  HandleFirst_local = HandleFirst;
  if (!HandleFirst_local)
    return HandleFirst_local;
  do
  {
    if (Equals_54828848(scriptname, HandleFirst_local->Name, 4, 0))
      break;
    HandleFirst_local = HandleFirst_local->next;
  }
  while (HandleFirst_local);
  return HandleFirst_local;
}

// 0x2149d50
s32 scrSearchProcedureName(u8 *scrdata, char *procname) {
  scrHeader_t *v5;
  s64 TypeTableCount;
  s64 v8;
  s32 v9;
  s64 v10;
  s64 v11;
  s64 v12;
  scrTypeTable_t *v13;
  s32 v14;
  s32 v15;
  s64 v16;
  s32 v17;
  s64 v18;
  s32 *v19;
  s32 v20;
  s64 v21;
  scrProcTable_t *v22;
  scrProcTable_t *v23;
  s64 v26;
  s32 v28;
  s32 totalsize;
  s32 index;

  index = 0;
  if (!scrdata)
    return -1;
  v5 = Allocate(scrHeader_t);
  _ctor(v5, scrdata, &index, &totalsize);
  TypeTableCount = (u32)v5->TypeTableCount;
  v8 = NewSpecific(scrTypeTable_t, TypeTableCount);
  if ((s32)TypeTableCount < 1)
    return -1;
  v9 = index;
  v10 = v8;
  v11 = 0;
  v12 = v8 + 32;
  do
  {
    v13 = Allocate(scrTypeTable_t);
    v13->Type = ToInt32(scrdata, v9, 0);
    v13->ItemSize = ToInt32(scrdata, v9 + 4, 0);
    v14 = ToInt32(scrdata, v9 + 8, 0);
    v15 = v9 + 12;
    v13->ItemCount = v14;
    v13->ItemAddress = ToInt32(scrdata, v15, 0);
    if (!QueryInterface(v13, *(void **)(*(u64 *)v10 + 64)))
      goto LABEL_17;
    *(u64 *)(v12 + v11) = v13;
    v11 += 8;
    v9 = v15 + 4;
  }
  while (8 * TypeTableCount != v11);
  v16 = v10 + 32;
  v17 = -1;
  while (*(u32 *)(*(u64 *)v16 + 16))
  {
    v16 += 8;
    if (!--TypeTableCount)
      return v17;
  }
  v18 = NewSpecific(scrProcTable_t, *(u32 *)(*(u64 *)v16 + 24));
  v19 = v18;
  v20 = *(u32 *)(*(u64 *)v16 + 24);
  v28 = *(u32 *)(*(u64 *)v16 + 28);
  if (v20 >= 1)
  {
    v21 = 0;
    v22 = (v18 + 32);
    while (1)
    {
      v23 = Allocate(scrProcTable_t);
      _ctor(v23, scrdata, &v28, &totalsize);
      if (v23)
      {
        if (!QueryInterface(v23, *(void **)(*(u64 *)v19 + 64)))
          break;
      }
      v22 = v23;
      ++v21;
      ++v22;
      if (v21 >= *(s32 *)(*(u64 *)v16 + 24))
        goto LABEL_19;
    }
LABEL_17:
  }
  if (!v18)
    return -1;
LABEL_19:
  if (v19[6] < 1)
    return -1;
  v26 = 0;
  v17 = -1;
  while (!Equals_54828784(procname, *(char **)(*(u64 *)&v19[2 * v26 + 8] + 16), 0))
  {
    if (++v26 >= v19[6])
      return v17;
  }
  return v26;
}

// 0x214a030
void scrSetUserData(dds3ProcessID_t *id, void *p) {
  Il2CppObject *ProcessData;
  Il2CppClass *klass;
  dds3ProcessID_t *ida;

  ida = id;
  ProcessData = dds3GetProcessData(ida);
  klass = ProcessData->klass;
}

// 0x214a110
void *scrGetUserData(dds3ProcessID_t *id) {
  Il2CppObject **ProcessData;
  s64 naturalAligment;
  dds3ProcessID_t *ida;

  ida = id;
  ProcessData = dds3GetProcessData(ida);
  if (!ProcessData)
    return ProcessData[20];
  LOBYTE((*ProcessData)[19].klass) < (u32)naturalAligment || *((scrHandle_t **)(*ProcessData)[12].monitor + naturalAligment - 1) != scrHandle_t;
  return ProcessData[20];
}

// 0x214a1f0
static void Shutdown(dds3ProcessID_t *id) {
  Il2CppObject *ProcessData;
  scrHandle_t *v5;
  void *Instance;
  dds3ProcessID_t *ida;

  ida = id;
  ProcessData = dds3GetProcessData(ida);
  if (!ProcessData)
  {
    goto LABEL_5;
  }
  v5 = ProcessData;
  scrReleaseScript(v5);
LABEL_5:
  dds3SetProcessData(ida, 0);
  if (repeat)
    goto LABEL_19;
  if (GetNoSkipEnd())
    goto LABEL_19;
  goto LABEL_9001;
  if (GetNoSkipEnd())
  {
LABEL_19:
    goto LABEL_21;
  }
LABEL_9001:
  Instance = get_Instance(0);
  fastForwardDisp(Instance, 0, 0);
LABEL_21:
  if (!dds3SearchProcessName("fldProcSequence"))
    return;
  if (dds3SearchProcessName("camp_main"))
    return;
  fldSetFieldGuide(1);
}

// 0x214a4b0
s32 scrRunScript(scrHandle_t *h) {
  s64 s0;
  CodeFunc_t v6;
  s32 v7;

  goto LABEL_9;
  while (1)
  {
    while (1)
    {
LABEL_9:
      s0 = h->Code[h->CP]->s0;
      v6 = codefunc[s0];
      v7 = (v6->invoke_impl)(v6->method_code, h, v6->method);
      if (v7 != 1)
        break;
      h->CommandTimer = 0;
    }
    if (v7 == 2)
      break;
    if (!v7)
    {
      h->CommandTimer = 0;
      return 2;
    }
  }
  *(int32x2_t *)&h->ScriptTimer = vadd_s32(*(int32x2_t *)&h->ScriptTimer, (int32x2_t)0x100000001LL);
  return 1;
}

// 0x214a6c0
dds3ProcessFunc_t scrProcess(dds3ProcessID_t *id) {
  int32x2_t *ProcessData;
  s64 v5;
  CodeFunc_t v6;
  s32 v7;
  dds3ProcessID_t *v10;
  MesLogData_t *Wk;
  dds3ProcessFunc_t v15;
  dds3ProcessID_t *ida;

  ida = id;
  ProcessData = dds3GetProcessData(ida);
  if (!ProcessData)
  while (1)
  {
    while (1)
    {
      v5 = *(s16 *)(*(u64 *)(ProcessData[10].n64_u64[0] + 8 * ProcessData[3].n64_i32[0] + 32) + 24);
      v6 = codefunc[v5];
      v7 = (v6->invoke_impl)(v6->method_code, ProcessData, v6->method);
      if (v7 != 1)
        break;
      ProcessData[14].n64_u32[1] = 0;
    }
    if (!v7)
      break;
    if (v7 == 2)
    {
      ProcessData[14].n64_u64[0] = vadd_s32(ProcessData[14], (int32x2_t)0x100000001LL).n64_u64[0];
      return 0;
    }
  }
  ProcessData[14].n64_u32[1] = 0;
  if (GetNoSkipEnd())
    goto LABEL_36;
  v10 = ida;
  scrLogEnd(ida);
  if (!ProcessCheck())
    goto LABEL_36;
  Wk = GetWk();
  if (Wk)
    End(Wk->mesSkip, 0);
LABEL_36:
  if (MiniMapUpdateFlag)
  {
    mapIfSetDestList();
    minMapRefresh();
  }
  v15 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v15, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
  return v15;
}

// 0x214aa40
s32 scrGetScriptHandleCount(void) {
  return HandleCount;
}

// 0x214aac0
void scrGetRunningScripts(void *scripts) {
  Il2CppObject *HandleFirst_local;
  void *v5;
  s64 v6;
  s64 size;
  void *items;
  Il2CppClass **v9;

  HandleFirst_local = HandleFirst;
  if (HandleFirst_local)
    goto LABEL_9;
  return;
  for (HandleFirst_local = HandleFirst; HandleFirst_local; HandleFirst_local = (Il2CppObject *)HandleFirst_local[9].monitor)
  {
LABEL_9:
    while (1)
    {
      v5 = scripts;
      v6 = Method_System_Collections_Generic_List_scrHandle_t__Add__;
      size = scripts->_size;
      v5->_version = scripts->_version + 1;
      items = v5->_items;
      if ((u32)size < LODWORD(items->max_length))
        break;
      _AddWithResize(v5, HandleFirst_local, *(const MethodInfo_2DFC660 **)(*(u64 *)(*(u64 *)(v6 + 32) + 192) + 112));
      HandleFirst_local = HandleFirst_local[9].monitor;
      if (!HandleFirst_local)
        return;
    }
    v5->_size = size + 1;
    v9 = &items->obj.klass + size;
    v9[4] = HandleFirst_local;
  }
}

// 0x214abd0
bool scrCheckScriptPlaying(void) {
  return HandleFirst != 0;
}

// 0x214ac40
static void PushInt(scrHandle_t *pwork, s32 data) {
  s64 SP;

  pwork->StackType[pwork->SP] = 0;
  SP = pwork->SP;
  pwork->StackData[SP]->im = data;
  pwork->SP = SP + 1;
}

// 0x214ac70
static void PushFloat(scrHandle_t *pwork, f32 data) {
  s64 SP;

  pwork->StackType[pwork->SP] = 1;
  SP = pwork->SP;
  pwork->StackData[SP]->fm = data;
  pwork->SP = SP + 1;
}

// 0x214acb0
static void PushStr(scrHandle_t *pwork, s32 data) {
  s64 SP;

  pwork->StackType[pwork->SP] = 5;
  SP = pwork->SP;
  pwork->StackData[SP]->im = data;
  pwork->SP = SP + 1;
}

// 0x214acf0
static void PushRet(scrHandle_t *pwork, s32 cp) {
  s64 SP;

  pwork->StackType[pwork->SP] = 4;
  SP = pwork->SP;
  pwork->StackData[SP]->im = cp;
  pwork->SP = SP + 1;
}

// 0x214ad30
static s32 PopInt(scrHandle_t *pwork) {
  s8 *StackType;
  s64 SP;
  s32 result;
  f32 fm;

  LODWORD(SP) = pwork->SP - 1;
  StackType = pwork->StackType;
  pwork->SP = SP;
  SP = (s32)SP;
  switch (StackType[(s32)SP])
  {
    case 0:
    case 4:
      result = pwork->StackData[(s32)SP]->im;
      break;
    case 1:
      fm = pwork->StackData[(s32)SP]->fm;
      goto LABEL_13;
    case 2:
      SP = pwork->SP;
      result = GBWK->IntVariable[pwork->StackData[SP]->im];
      break;
    case 3:
      SP = pwork->SP;
      fm = GBWK->FloatVariable[pwork->StackData[SP]->im];
LABEL_13:
      if (fm == INFINITY)
        result = 0x80000000;
      else
        result = (s32)fm;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}

// 0x214aea0
static f32 PopFloat(scrHandle_t *pwork) {
  s8 *StackType;
  s64 SP;
  f32 result;

  LODWORD(SP) = pwork->SP - 1;
  StackType = pwork->StackType;
  pwork->SP = SP;
  SP = (s32)SP;
  switch (StackType[(s32)SP])
  {
    case 0:
      result = (f32)pwork->StackData[(s32)SP]->im;
      break;
    case 1:
      result = pwork->StackData[(s32)SP]->fm;
      break;
    case 2:
      SP = pwork->SP;
      result = (f32)GBWK->IntVariable[pwork->StackData[SP]->im];
      break;
    case 3:
      SP = pwork->SP;
      result = GBWK->FloatVariable[pwork->StackData[SP]->im];
      break;
    default:
      result = 0.0;
      break;
  }
  return result;
}

// 0x214b000
static s32 CodeFunc_PushI(scrHandle_t *pwork) {
  s32 v3;
  scrCode_t *Code;
  s32 im;
  s32 CP;
  s64 SP;

  v3 = pwork->CP + 1;
  Code = pwork->Code;
  pwork->CP = v3;
  im = Code[v3]->im;
  pwork->StackType[pwork->SP] = 0;
  CP = pwork->CP;
  SP = pwork->SP;
  pwork->StackData[SP]->im = im;
  pwork->CP = CP + 1;
  pwork->SP = SP + 1;
  return 1;
}

// 0x214b0b0
static s32 CodeFunc_PushIS(scrHandle_t *pwork) {
  s32 s1;
  s32 CP;
  s64 SP;

  s1 = pwork->Code[pwork->CP]->s1;
  pwork->StackType[pwork->SP] = 0;
  CP = pwork->CP;
  SP = pwork->SP;
  pwork->StackData[SP]->im = s1;
  pwork->CP = CP + 1;
  pwork->SP = SP + 1;
  return 1;
}

// 0x214b160
static s32 CodeFunc_PushF(scrHandle_t *pwork) {
  s32 v3;
  scrCode_t *Code;
  f32 fm;
  s32 CP;
  s64 SP;

  v3 = pwork->CP + 1;
  Code = pwork->Code;
  pwork->CP = v3;
  fm = Code[v3]->fm;
  pwork->StackType[pwork->SP] = 1;
  CP = pwork->CP;
  SP = pwork->SP;
  pwork->StackData[SP]->fm = fm;
  pwork->CP = CP + 1;
  pwork->SP = SP + 1;
  return 1;
}

// 0x214b220
static s32 CodeFunc_PushIX(scrHandle_t *pwork) {
  s32 v4;
  s32 CP;
  s64 SP;

  v4 = GBWK->IntVariable[pwork->Code[pwork->CP]->s1];
  pwork->StackType[pwork->SP] = 0;
  CP = pwork->CP;
  SP = pwork->SP;
  pwork->StackData[SP]->im = v4;
  pwork->CP = CP + 1;
  pwork->SP = SP + 1;
  return 1;
}

// 0x214b310
static s32 CodeFunc_PushFX(scrHandle_t *pwork) {
  f32 v4;
  s32 CP;
  s64 SP;

  v4 = GBWK->FloatVariable[pwork->Code[pwork->CP]->s1];
  pwork->StackType[pwork->SP] = 1;
  CP = pwork->CP;
  SP = pwork->SP;
  pwork->StackData[SP]->fm = v4;
  pwork->CP = CP + 1;
  pwork->SP = SP + 1;
  return 1;
}

// 0x214b400
static s32 CodeFunc_PushLIX(scrHandle_t *pwork) {
  s32 v3;
  s32 CP;
  s64 SP;

  v3 = pwork->LocalInt[pwork->Code[pwork->CP]->s1];
  pwork->StackType[pwork->SP] = 0;
  CP = pwork->CP;
  SP = pwork->SP;
  pwork->StackData[SP]->im = v3;
  pwork->CP = CP + 1;
  pwork->SP = SP + 1;
  return 1;
}

// 0x214b4c0
static s32 CodeFunc_PushLFX(scrHandle_t *pwork) {
  f32 v3;
  s32 CP;
  s64 SP;

  v3 = pwork->LocalFloat[pwork->Code[pwork->CP]->s1];
  pwork->StackType[pwork->SP] = 1;
  CP = pwork->CP;
  SP = pwork->SP;
  pwork->StackData[SP]->fm = v3;
  pwork->CP = CP + 1;
  pwork->SP = SP + 1;
  return 1;
}

// 0x214b580
static s32 CodeFunc_PushSTR(scrHandle_t *pwork) {
  s32 s1;
  s32 CP;
  s64 SP;

  s1 = pwork->Code[pwork->CP]->s1;
  pwork->StackType[pwork->SP] = 5;
  CP = pwork->CP;
  SP = pwork->SP;
  pwork->StackData[SP]->im = s1;
  pwork->CP = CP + 1;
  pwork->SP = SP + 1;
  return 1;
}

// 0x214b630
static s32 CodeFunc_PushReg(scrHandle_t *pwork) {
  scrStackData_t *StackData;
  scrStackData_t *v4;
  scrStackData_t *v5;
  f32 fm;
  dds3ProcessID_t *id;

  pwork->StackType[pwork->SP] = pwork->StackType[27];
  StackData = pwork->StackData;
  v4 = StackData[27];
  v5 = StackData[pwork->SP];
  fm = v4->fm;
  v5->im = v4->im;
  v5->fm = fm;
  *(u32 *)&v5->s0 = *(u32 *)&v4->s0;
  *(u32 *)&v5->c0 = *(u32 *)&v4->c0;
  id = v4->id;
  v5->id = id;
  v5 = ((char *)v5 + 32);
  *(sdfVector4_t *)&v5->monitor = v4->vec;
  *(int32x2_t *)&pwork->CP = vadd_s32(*(int32x2_t *)&pwork->CP, (int32x2_t)0x100000001LL);
  return 1;
}

// 0x214b6d0
static s32 CodeFunc_PopIX(scrHandle_t *pwork) {
  s32 *IntVariable;
  s64 s1;

  IntVariable = GBWK->IntVariable;
  s1 = pwork->Code[pwork->CP]->s1;
  IntVariable[s1] = PopInt(pwork);
  ++pwork->CP;
  return 1;
}

// 0x214b7a0
static s32 CodeFunc_PopFX(scrHandle_t *pwork) {
  f32 *FloatVariable;
  s64 s1;

  FloatVariable = GBWK->FloatVariable;
  s1 = pwork->Code[pwork->CP]->s1;
  FloatVariable[s1] = PopFloat(pwork);
  ++pwork->CP;
  return 1;
}

// 0x214b870
static s32 CodeFunc_PopLIX(scrHandle_t *pwork) {
  s32 *LocalInt;
  s64 s1;

  LocalInt = pwork->LocalInt;
  s1 = pwork->Code[pwork->CP]->s1;
  LocalInt[s1] = PopInt(pwork);
  ++pwork->CP;
  return 1;
}

// 0x214b910
static s32 CodeFunc_PopLFX(scrHandle_t *pwork) {
  f32 *LocalFloat;
  s64 s1;

  LocalFloat = pwork->LocalFloat;
  s1 = pwork->Code[pwork->CP]->s1;
  LocalFloat[s1] = PopFloat(pwork);
  ++pwork->CP;
  return 1;
}

// 0x214b9b0
static s32 CodeFunc_Proc(scrHandle_t *pwork) {
  ++pwork->CP;
  return 1;
}

// 0x214b9d0
static s32 CodeFunc_Comm(scrHandle_t *pwork) {
  s64 CP;
  s64 s1;
  commDelegate comm;
  s32 SP;

  CP = pwork->CP;
  s1 = pwork->Code[CP]->s1;
  s_hNowpWork = pwork;
  comm = tbl[s1]->comm;
  if (!(comm->invoke_impl)(comm->method_code, comm->method))
    return 2;
  SP = pwork->SP;
  pwork->SP = SP - tbl[s1]->paranum;
  if ((u32)CP == pwork->CP)
    pwork->CP = CP + 1;
  return 1;
}

// 0x214bb10
static s32 CodeFunc_End(scrHandle_t *pwork) {
  if (!pwork->SP)
    return 0;
  pwork->CP = PopInt(pwork) + 1;
  return 1;
}

// 0x214bb90
static s32 CodeFunc_Jump(scrHandle_t *pwork) {
  pwork->CP = pwork->ProcTable[pwork->Code[pwork->CP]->s1]->CodeAddress;
  return 1;
}

// 0x214bbc0
static s32 CodeFunc_Call(scrHandle_t *pwork) {
  s32 CP;
  s64 SP;
  s64 v6;

  CP = pwork->CP;
  pwork->StackType[pwork->SP] = 4;
  v6 = pwork->CP;
  SP = pwork->SP;
  pwork->StackData[SP]->im = CP;
  pwork->CP = pwork->ProcTable[pwork->Code[v6]->s1]->CodeAddress;
  pwork->SP = SP + 1;
  return 1;
}

// 0x214bc80
static s32 CodeFunc_Run(scrHandle_t *pwork) {
  ++pwork->CP;
  return 1;
}

// 0x214bca0
static s32 CodeFunc_Goto(scrHandle_t *pwork) {
  pwork->CP = pwork->LabelTable[pwork->Code[pwork->CP]->s1]->CodeAddress;
  return 1;
}

// 0x214bcd0
static void CodeFunc_2Operation(scrHandle_t *pwork, s32 type) {
  s32 SP;
  s8 *StackType;
  s32 v8;
  s32 s_i2_local;
  s32 v15;
  f32 s_f2_local;
  f32 v20;
  f32 v21;
  s64 v23;
  bool v25;
  f32 v26;
  f32 v27;
  s64 v29;

  SP = pwork->SP;
  StackType = pwork->StackType;
  v8 = StackType[SP - 1];
  StackType = pwork->StackType;
  SP = pwork->SP;
  s_t1 = v8;
  s_t2 = StackType[SP - 2];
  if (v8)
  {
    if (v8 != 2)
      goto LABEL_23;
  }
  if (!s_t2)
    goto LABEL_16;
  if (s_t2 == 2)
    goto LABEL_16;
LABEL_23:
  s_f1 = PopFloat(pwork);
  s_f2_local = PopFloat(pwork);
  s_f2 = s_f2_local;
  switch (type)
  {
    case 0:
      s_f2_local = s_f2;
      v20 = s_f1 + s_f2_local;
      goto LABEL_148;
    case 1:
      s_f2_local = s_f2;
      v20 = s_f1 - s_f2_local;
      goto LABEL_148;
    case 2:
      s_f2_local = s_f2;
      v20 = s_f1 * s_f2_local;
      goto LABEL_148;
    case 3:
      s_f2_local = s_f2;
      v20 = s_f1 / s_f2_local;
      goto LABEL_148;
    case 4:
      if (s_f1 != 0.0)
        goto LABEL_51;
      v21 = s_f2;
      v20 = 0.0;
      goto LABEL_50;
    case 5:
      v20 = 0.0;
      if (s_f1 == 0.0)
        goto LABEL_52;
      v21 = s_f2;
LABEL_50:
      if (v21 != 0.0)
LABEL_51:
        v20 = 1.0;
LABEL_52:
      goto LABEL_147;
    case 6:
      v25 = s_f1 == s_f2;
      v26 = 0.0;
      v27 = 1.0;
      goto LABEL_122;
    case 7:
      if (s_f1 == s_f2_local)
        v20 = 0.0;
      else
        v20 = 1.0;
      goto LABEL_148;
LABEL_122:
      if (v25)
        v20 = v27;
      else
        v20 = v26;
      goto LABEL_148;
    case 8:
      if (s_f1 >= s_f2_local)
        v20 = 0.0;
      else
        v20 = 1.0;
      goto LABEL_148;
    case 9:
      if (s_f1 <= s_f2_local)
        v20 = 0.0;
      else
        v20 = 1.0;
      goto LABEL_148;
    case 10:
      if (s_f1 <= s_f2_local)
        v20 = 1.0;
      else
        v20 = 0.0;
      goto LABEL_148;
    case 11:
      if (s_f1 >= s_f2_local)
        v20 = 1.0;
      else
        v20 = 0.0;
LABEL_147:
LABEL_148:
      s_rf = v20;
LABEL_149:
      pwork->StackType[pwork->SP] = 1;
      v29 = pwork->SP;
      pwork->StackData[v29]->fm = s_rf;
      LODWORD(v23) = v29;
      break;
    default:
      goto LABEL_149;
  }
  goto LABEL_152;
LABEL_16:
  s_i1 = PopInt(pwork);
  s_i2_local = PopInt(pwork);
  s_i2 = s_i2_local;
  switch (type)
  {
    case 0:
      s_i2_local = s_i2;
      v15 = s_i2_local + s_i1;
      goto LABEL_116;
    case 1:
      s_i2_local = s_i2;
      v15 = s_i1 - s_i2_local;
      goto LABEL_116;
    case 2:
      s_i2_local = s_i2;
      v15 = s_i2_local * s_i1;
      goto LABEL_116;
    case 3:
      s_i2_local = s_i2;
      v15 = s_i1 / s_i2_local;
      goto LABEL_116;
    case 4:
      if (!s_i1)
      {
        if (!s_i2)
          goto LABEL_112;
      }
      v15 = 1;
      goto LABEL_113;
    case 5:
      if (s_i1)
      {
        v15 = s_i2 != 0;
      }
      else
      {
LABEL_112:
        v15 = 0;
      }
LABEL_113:
      goto LABEL_115;
    case 6:
      v15 = s_i1 == s_i2_local;
      goto LABEL_116;
    case 7:
      v15 = s_i1 != s_i2_local;
      goto LABEL_116;
    case 8:
      v15 = s_i1 < s_i2_local;
      goto LABEL_116;
    case 9:
      v15 = s_i1 > s_i2_local;
      goto LABEL_116;
    case 10:
      v15 = s_i1 <= s_i2_local;
      goto LABEL_116;
    case 11:
      v15 = s_i1 >= s_i2_local;
LABEL_115:
LABEL_116:
      s_ri = v15;
LABEL_117:
      pwork->StackType[pwork->SP] = 0;
      v23 = pwork->SP;
      pwork->StackData[v23]->im = s_ri;
      break;
    default:
      goto LABEL_117;
  }
LABEL_152:
  pwork->SP = v23 + 1;
}

// 0x214c4c0
static s32 CodeFunc_Add(scrHandle_t *pwork) {
  CodeFunc_2Operation(pwork, 0);
  ++pwork->CP;
  return 1;
}

// 0x214c540
static s32 CodeFunc_Sub(scrHandle_t *pwork) {
  CodeFunc_2Operation(pwork, 1);
  ++pwork->CP;
  return 1;
}

// 0x214c5c0
static s32 CodeFunc_Mul(scrHandle_t *pwork) {
  CodeFunc_2Operation(pwork, 2);
  ++pwork->CP;
  return 1;
}

// 0x214c640
static s32 CodeFunc_Div(scrHandle_t *pwork) {
  CodeFunc_2Operation(pwork, 3);
  ++pwork->CP;
  return 1;
}

// 0x214c6c0
static s32 CodeFunc_Minus(scrHandle_t *pwork) {
  s64 v3;
  scrStackData_t *v4;
  scrStackData_t *v5;
  s64 v7;
  s64 v9;

  v3 = pwork->SP - 1;
  switch (pwork->StackType[v3])
  {
    case 0:
      v4 = pwork->StackData[v3];
      v4->im = -v4->im;
      break;
    case 1:
      v5 = pwork->StackData[v3];
      v5->fm = -v5->fm;
      break;
    case 2:
      v3 = pwork->SP - 1;
      v7 = (s64)GBWK->IntVariable + 4 * pwork->StackData[v3]->im;
      *(u32 *)(v7 + 32) = -*(u32 *)(v7 + 32);
      break;
    case 3:
      v3 = pwork->SP - 1;
      v9 = (s64)GBWK->FloatVariable + 4 * pwork->StackData[v3]->im;
      *(f32 *)(v9 + 32) = -*(f32 *)(v9 + 32);
      break;
    default:
      break;
  }
  ++pwork->CP;
  return 1;
}

// 0x214c830
static s32 CodeFunc_Not(scrHandle_t *pwork) {
  bool v3;
  s32 v5;
  f32 v6;
  s64 SP;

  switch (pwork->StackType[pwork->SP - 1])
  {
    case 0:
    case 2:
      v3 = PopInt(pwork) == 0;
      v5 = v3;
      goto LABEL_15;
    case 1:
    case 3:
      v6 = PopFloat(pwork);
      v5 = v6 == 0.0;
LABEL_15:
      pwork->StackType[pwork->SP] = 0;
      SP = pwork->SP;
      pwork->StackData[SP]->im = v5;
      pwork->SP = SP + 1;
      break;
    default:
      break;
  }
  ++pwork->CP;
  return 1;
}

// 0x214c960
static s32 CodeFunc_Or(scrHandle_t *pwork) {
  CodeFunc_2Operation(pwork, 4);
  ++pwork->CP;
  return 1;
}

// 0x214c9e0
static s32 CodeFunc_And(scrHandle_t *pwork) {
  CodeFunc_2Operation(pwork, 5);
  ++pwork->CP;
  return 1;
}

// 0x214ca60
static s32 CodeFunc_EQ(scrHandle_t *pwork) {
  CodeFunc_2Operation(pwork, 6);
  ++pwork->CP;
  return 1;
}

// 0x214cae0
static s32 CodeFunc_NEQ(scrHandle_t *pwork) {
  CodeFunc_2Operation(pwork, 7);
  ++pwork->CP;
  return 1;
}

// 0x214cb60
static s32 CodeFunc_S(scrHandle_t *pwork) {
  CodeFunc_2Operation(pwork, 8);
  ++pwork->CP;
  return 1;
}

// 0x214cbe0
static s32 CodeFunc_L(scrHandle_t *pwork) {
  CodeFunc_2Operation(pwork, 9);
  ++pwork->CP;
  return 1;
}

// 0x214cc60
static s32 CodeFunc_SE(scrHandle_t *pwork) {
  CodeFunc_2Operation(pwork, 10);
  ++pwork->CP;
  return 1;
}

// 0x214cce0
static s32 CodeFunc_LE(scrHandle_t *pwork) {
  CodeFunc_2Operation(pwork, 11);
  ++pwork->CP;
  return 1;
}

// 0x214cd60
static s32 CodeFunc_IF(scrHandle_t *pwork) {
  s32 result;

  switch (pwork->StackType[pwork->SP - 1])
  {
    case 0:
    case 2:
      if (!PopInt(pwork))
        goto LABEL_10;
      goto LABEL_6;
    case 1:
    case 3:
      if (PopFloat(pwork) == 0.0)
        goto LABEL_10;
LABEL_6:
      ++pwork->CP;
      result = 1;
      break;
    default:
LABEL_10:
      pwork->CP = pwork->LabelTable[pwork->Code[pwork->CP]->s1]->CodeAddress;
      result = 1;
      break;
  }
  return result;
}

// 0x214a5e0
s32 scrTraceCode(scrHandle_t *pwork) {
  s64 s0;
  CodeFunc_t v5;
  s32 v6;

  while (1)
  {
    while (1)
    {
      s0 = pwork->Code[pwork->CP]->s0;
      v5 = codefunc[s0];
      v6 = (v5->invoke_impl)(v5->method_code, pwork, v5->method);
      if (v6 != 1)
        break;
      pwork->CommandTimer = 0;
    }
    if (v6 == 2)
      break;
    if (!v6)
    {
      pwork->CommandTimer = 0;
      return 2;
    }
  }
  *(int32x2_t *)&pwork->ScriptTimer = vadd_s32(*(int32x2_t *)&pwork->ScriptTimer, (int32x2_t)0x100000001LL);
  return 1;
}

// 0x214ce70
s32 scrGetIntPara(s32 n) {
  s64 v6;
  f32 fm;
  s32 *IntVariable;
  f32 *FloatVariable;

  v6 = (s_hNowpWork->SP + ~n) & (u32)~((s_hNowpWork->SP + ~n) >> 31);
  switch (s_hNowpWork->StackType[v6])
  {
    case 0:
    case 4:
      return s_hNowpWork->StackData[v6]->im;
    case 1:
      fm = s_hNowpWork->StackData[v6]->fm;
      goto LABEL_21;
    case 2:
      IntVariable = GBWK->IntVariable;
      return IntVariable[s_hNowpWork->StackData[v6]->im];
    case 3:
      FloatVariable = GBWK->FloatVariable;
      fm = FloatVariable[s_hNowpWork->StackData[v6]->im];
LABEL_21:
      if (fm == INFINITY)
        return 0x80000000;
      else
        return (s32)fm;
    default:
      return 0;
  }
}

// 0x214d0d0
f32 scrGetFloatPara(s32 n) {
  s64 v5;
  s32 *IntVariable;
  f32 *FloatVariable;

  v5 = s_hNowpWork->SP + ~n;
  switch (s_hNowpWork->StackType[v5])
  {
    case 0:
    case 4:
      return (f32)s_hNowpWork->StackData[v5]->im;
    case 1:
      return s_hNowpWork->StackData[v5]->fm;
    case 2:
      IntVariable = GBWK->IntVariable;
      return (f32)IntVariable[s_hNowpWork->StackData[v5]->im];
    case 3:
      FloatVariable = GBWK->FloatVariable;
      return FloatVariable[s_hNowpWork->StackData[v5]->im];
    default:
      return 0.0;
  }
}

// 0x214d310
char *scrGetStrPara(s32 n) {
  void *v3;
  scrHandle_t *s_hNowpWork_local;
  s64 v6;
  s64 v7;
  u8 *StringData;
  s64 v9;
  s32 v10;

  v3 = Allocate(System_Text_StringBuilder);
  _ctor(v3, 0);
  s_hNowpWork_local = s_hNowpWork;
  v6 = s_hNowpWork_local->SP + ~n;
  if (s_hNowpWork_local->StackType[v6] != 5)
    return 0;
  s_hNowpWork_local = s_hNowpWork;
  v7 = (s64)s_hNowpWork_local->StackData + 8 * v6;
  StringData = s_hNowpWork_local->StringData;
  v9 = *(s32 *)(*(u64 *)(v7 + 32) + 16);
  LOBYTE(s_hNowpWork_local) = StringData[v9];
  if ((u8)s_hNowpWork_local)
  {
    v10 = v9 + 1;
    do
    {
      Append_56602736(v3, (u8)s_hNowpWork_local, 0);
      s_hNowpWork_local = ((char *)StringData + v10++);
      LODWORD(s_hNowpWork_local) = LOBYTE(s_hNowpWork_local->StackType);
    }
    while ((u32)s_hNowpWork_local);
  }
  return ((char *(void *, const MethodInfo *))v3->klass->vtable._3_ToString.methodPtr)(v3, v3->klass->vtable._3_ToString.method);
}

// 0x214d440
dds3ProcessID_t *scrGetdds3ProcessIDPara(s32 n) {
  s64 v5;

  v5 = s_hNowpWork->SP + ~n;
  if (s_hNowpWork->StackType[v5] != 6)
    return 0;
  return s_hNowpWork->StackData[v5]->id;
}

// 0x214d510
sdfVector4_t scrGetVector4Para(s32 n) {
  s64 v5;
  scrStackData_t *v6;
  struct sdfVector4_t *p_vec;
  f32 *p_y;
  f32 *p_z;
  f32 *p_w;
  sdfVector4_t result;

  v5 = s_hNowpWork->SP + ~n;
  if (s_hNowpWork->StackType[v5] == 7)
  {
    v6 = s_hNowpWork->StackData[v5];
    p_vec = &v6->vec;
    p_y = &v6->vec.y;
    p_z = &v6->vec.z;
    p_w = &v6->vec.w;
  }
  else
  {
    p_y = &zeroVector.y;
    p_z = &zeroVector.z;
    p_w = &zeroVector.w;
  }
  result.w = *p_w;
  result.z = *p_z;
  result.y = *p_y;
  result.x = zeroVector.x;
  return result;
}

// 0x214d620
void scrSetIntReturnValue(s32 i) {
  s_hNowpWork->StackType[27] = 0;
  s_hNowpWork->StackData[27]->im = i;
}

// 0x214d6b0
void scrSetFloatReturnValue(f32 f) {
  s_hNowpWork->StackType[27] = 1;
  s_hNowpWork->StackData[27]->fm = f;
}

// 0x214d740
void scrSetdds3ProcessIDReturnValue(dds3ProcessID_t *id) {
  scrStackData_t *v4;

  s_hNowpWork->StackType[27] = 6;
  v4 = s_hNowpWork->StackData[27];
  v4->id = id;
}

// 0x214d7d0
void SetFloatReturnValue(const sdfVector4_t *v) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  scrStackData_t *v7;

  w = v->w;
  z = v->z;
  y = v->y;
  x = v->x;
  s_hNowpWork->StackType[27] = 1;
  v7 = s_hNowpWork->StackData[27];
  v7->vec.z = z;
  v7->vec.w = w;
  v7->vec.x = x;
  v7->vec.y = y;
}

// 0x214d880
s32 scrGetLabelCodeAddress(s32 labelindex) {
  return s_hNowpWork->LabelTable[labelindex]->CodeAddress;
}

// 0x214d900
void scrSetCodePointer(s32 cp) {
  s_hNowpWork->CP = cp;
}

// 0x214d970
s32 scrGetCommandTimer(void) {
  return s_hNowpWork->CommandTimer;
}

// 0x214da00
s32 scrGetMessageHandle(void) {
  return s_hNowpWork->MesHandle;
}

// 0x214da90
scrHandle_t *scrGetScriptHandle(void) {
  return s_hNowpWork;
}

// 0x214db10
void *scrGetData(void) {
  return s_hNowpWork->data;
}
