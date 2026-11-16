#include "types.h"
#include "sbtl.h"
#include "sbtlsub.h"
#include "sbtltalk.h"

typedef struct SBTLTALK_WORK SBTLTALK_WORK;

// 0x1fbe070
SBTLTALK_WORK *sBtlCreateTalk(void) {
  SBTLTALK_WORK *v1;

  v1 = (SBTLTALK_WORK *)Allocate(SBTLTALK_WORK);
  _ctor(v1, 0);
  v1->mode = 0;
  return v1;
}

// 0x1fbe0d0
bool Proc(SBTLTALK_WORK *twk) {
  if (wk->talkwk)
    return twk->mode > 0;
  return 0;
}

// 0x1fbe180
bool sBtlDeleteTalk(SBTLTALK_WORK *twk) {
  return 1;
}

// 0x1fbe190
bool sBtlSetDevilSkillID(s32 devilid, s32 flg) {
  SBTLTALK_WORK *talkwk;
  SBTLTALK_WORK *v8;
  DEVILDATA_WORK *v9;
  SKLID *v10;
  DEVILDATA_WORK *v11;
  s32 v13;
  SBTLTALK_WORK *v14;
  DEVILDATA_WORK *DevilData;
  SKLID *haveskill;
  DEVILDATA_WORK *v17;
  s32 v19;
  DEVILDATA_WORK *v20;
  s64 v23;
  _BOOL4 v24;
  s64 v26;
  s64 v28;
  s64 v30;
  bool v31;
  s64 v33;
  _BOOL4 v34;
  s64 v36;
  s64 v38;
  s64 v40;

  talkwk = wk->talkwk;
  if (!talkwk)
    return talkwk != 0;
  if (flg == 2)
  {
    v14 = talkwk;
    v14 = wk->talkwk;
    v14->sklid[0] = 149;
    DevilData = sBtlGetDevilData(devilid, -1);
    haveskill = DevilData->haveskill;
    v17 = DevilData;
    if (haveskill[0])
    {
      haveskill = v17->haveskill;
      v19 = 2;
      wk->talkwk->sklid[1] = haveskill[0];
      if (!haveskill[1])
        goto LABEL_61;
    }
    else
    {
      v19 = 1;
      if (!haveskill[1])
      {
LABEL_61:
        v34 = v19 < 4;
        if (v19 <= 3)
        {
          if (haveskill[2])
          {
            haveskill = v17->haveskill;
            v36 = (s64)wk->talkwk->sklid + 4 * (u32)v19++;
            *(u32 *)(v36 + 32) = haveskill[2];
          }
          v34 = v19 < 4;
          if (v19 <= 3)
          {
            if (haveskill[3])
            {
              haveskill = v17->haveskill;
              v38 = (s64)wk->talkwk->sklid + 4 * (u32)v19++;
              *(u32 *)(v38 + 32) = haveskill[3];
            }
            v34 = v19 < 4;
          }
        }
        if (v34)
        {
          v40 = (u32)v19 + 8;
          do
          {
            v31 = (u32)v40 == 11;
            *((u32 *)&wk->talkwk->sklid->obj.klass + v40++) = 0;
          }
          while (!v31);
        }
        return talkwk != 0;
      }
    }
    haveskill = v17->haveskill;
    v33 = (s64)wk->talkwk->sklid + 4 * (u32)v19++;
    *(u32 *)(v33 + 32) = haveskill[1];
    goto LABEL_61;
  }
  if (flg != 1)
  {
    if (flg)
      return talkwk != 0;
    v8 = talkwk;
    v8 = wk->talkwk;
    v8->sklid[0] = 149;
    v9 = sBtlGetDevilData(devilid, -1);
    v10 = v9->haveskill;
    v11 = v9;
    if (v10[0])
    {
      v10 = v11->haveskill;
      v13 = 2;
      wk->talkwk->sklid[1] = v10[0];
      if (!v10[1])
        goto LABEL_41;
    }
    else
    {
      v13 = 1;
      if (!v10[1])
      {
LABEL_41:
        v24 = v13 < 4;
        if (v13 <= 3)
        {
          if (v10[2])
          {
            v10 = v11->haveskill;
            v26 = (s64)wk->talkwk->sklid + 4 * (u32)v13++;
            *(u32 *)(v26 + 32) = v10[2];
          }
          v24 = v13 < 4;
          if (v13 <= 3)
          {
            if (v10[3])
            {
              v10 = v11->haveskill;
              v28 = (s64)wk->talkwk->sklid + 4 * (u32)v13++;
              *(u32 *)(v28 + 32) = v10[3];
            }
            v24 = v13 < 4;
          }
        }
        if (v24)
        {
          v30 = (u32)v13 + 8;
          do
          {
            v31 = (u32)v30 == 11;
            *((u32 *)&wk->talkwk->sklid->obj.klass + v30++) = 0;
          }
          while (!v31);
        }
        return talkwk != 0;
      }
    }
    v10 = v11->haveskill;
    v23 = (s64)wk->talkwk->sklid + 4 * (u32)v13++;
    *(u32 *)(v23 + 32) = v10[1];
    goto LABEL_41;
  }
  v20 = sBtlGetDevilData(devilid, -1);
  wk->talkwk->sklid[1] = v20->haveskill[1];
  wk->talkwk->sklid[2] = v20->haveskill[2];
  wk->talkwk->sklid[3] = v20->haveskill[3];
  return 1;
}
