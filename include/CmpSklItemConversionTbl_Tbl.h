#pragma once
#include "types.h"
#include "ITM.h"
#include "SKLID.h"

typedef struct CmpSklItemConversionTbl_Tbl CmpSklItemConversionTbl_Tbl;

struct CmpSklItemConversionTbl_Tbl {
    ITM itmId;
    SKLID sklID;
};
