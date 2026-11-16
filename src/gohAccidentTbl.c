#include "types.h"
#include "EMParam.h"
#include "SKLID.h"
#include "gohaccidenttbl.h"

typedef struct gohAccidentDevilTbl gohAccidentDevilTbl;
typedef struct gohAccidentFactorTbl gohAccidentFactorTbl;

gohAccidentDevilTbl *s_BlankTbl;
gohAccidentFactorTbl *s_RequestItemTbl1;
gohAccidentFactorTbl *s_RequestItemTbl2;
gohAccidentFactorTbl *s_RequestItemTbl3;
s16 *s_LuckRateMajinTbl;
s16 *s_LuckRateToshidensetsuTbl;
gohAccidentDevilTbl *s_MajinTbl;
gohAccidentDevilTbl *s_ToshidenTbl;
gohAccidentDevilTbl *s_SlimeTbl;
SKLID *s_aiOmoideSkillTbl;
s16 *gohAccidentDevil;
EMParam *eParamTblAge8;
EMParam *eParamTblAge;
f32 *cntParaTbl;
f32 **parCntTbl;
f32 **hpCntTbl;
