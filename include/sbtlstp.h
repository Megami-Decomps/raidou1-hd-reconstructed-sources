#pragma once
#include "types.h"
#include "SBTLSTP_ID.h"

typedef struct SBTLSTP_LISTWORK SBTLSTP_LISTWORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

SBTLSTP_LISTWORK *sBtlCreateSTPList(void);
s32 sBtlCreateSTP_Unit(SBTLSTP_LISTWORK *lwk, SBTLUNIT_WORK *wk, SBTLSTP_ID id, s32 time, u32 bstf, u32 attr);
bool Proc(SBTLSTP_LISTWORK *lwk);
bool Draw(SBTLSTP_LISTWORK *lwk);
bool sBtlReleaseSTP_List(SBTLSTP_LISTWORK *lwk, u8 flg);
bool sBtlDeleteSTPList(SBTLSTP_LISTWORK *lwk);
