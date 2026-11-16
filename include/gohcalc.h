#pragma once
#include "types.h"
#include "GOH_KARTE_SORTMODE.h"
#include "SKLID.h"

typedef struct gohGeneralList_t gohGeneralList_t;
typedef struct gohKarteList_t gohKarteList_t;
typedef struct gohKarteUnit_t gohKarteUnit_t;
typedef struct gohSortedDevilList_t gohSortedDevilList_t;
typedef struct gohTable_t gohTable_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;

extern gohKarteList_t *gBackupKarteList;

void gohStrongSwordFlag(s32 DevilID, s32 Mode);
s32 gohTablCheckEventDevil(gohTable_t *pTable, s32 DevilID);
void gohTablRegistEventDevil(gohTable_t *pTable);
bool gohCheckEventDevil(s32 DevilID);
s32 gohAccidentFailDevilNo(s32 idx);
u32 gohAccidentFailDevilCnt(void);
s32 gohSortedSkillPrioHigherCallback(void *op1, void *op2);
s32 gohSortedSkillPrioLowerCallback(void *op1, void *op2);
s32 gohSortedDevilListCallback(void *op1, void *op2);
void gohCreateSortedDevilList(gohSortedDevilList_t *pList, gohTable_t *pTable);
s32 gohLevelSortedUnitListCallback(void *op1, void *op2);
s32 gohRaceSortedUnitListCallback(void *op1, void *op2);
s32 gohFavSortedUnitListCallback(void *op1, void *op2);
void gohCreateSortedUnitList(s32 UnitNums, sdatUnitWork_t *pUnitList, GOH_KARTE_SORTMODE Mode, bool _pro);
s32 gohUnitListIndex(s32 _unitNum, sdatUnitWork_t *_searchiUnit, sdatUnitWork_t *pUnitList, bool _pro);
s32 gohCheckHaveSkill(sdatUnitWork_t *pUnit, SKLID SkillID);
s32 gohDelDevilFromGeneralList(gohGeneralList_t *pGeneralList, s32 Index);
bool gohKarteIsInvalidateSkillNo(SKLID iSkillNo);
SKLID gohKarteUnitGetSkill(gohKarteUnit_t *psKarteUnit, s64 iIdx);
void gohKarteUnitSetSkill(gohKarteUnit_t *psKarteUnit, s64 iIdx, SKLID uSkillNo);
bool gohKarteUnitGetReserveSkillFlag(gohKarteUnit_t *psKarteUnit, s64 iIdx);
void gohKarteUnitSetReserveSkillFlag(gohKarteUnit_t *psKarteUnit, s64 iIdx, bool bFlag);
bool gohKarteAllRegCheck(s32 _devilId);
s32 gohKarteSearchFromKarteList(s32 DevilID, gohKarteList_t *pKarteList, bool _pro);
s32 gohKarteSearchUcFromKarteList(s32 DevilID, u32 _uniqCode, gohKarteList_t *pKarteList, bool _pro);
s32 gohKarteCreateUnitFromKarteList(s32 DevilID, sdatUnitWork_t *pUnit, gohKarteList_t *pKarteList);
s32 gohKarteCreateUnitUcFromKarteList(s32 DevilID, u32 _uniqCode, sdatUnitWork_t *pUnit, gohKarteList_t *pKarteList, bool _pro);
void *gohCreateAllKarteUnitList(void);
void *gohCreateAllKarteDevilList(s32 _devilId);
void *gohKarteProCreateUnitList(s32 _devilId);
s32 gohKarteCreateUnit(s32 DevilID, sdatUnitWork_t *pUnit);
s32 gohKarteCreateUnitUc(s32 DevilID, u32 _uniqCode, sdatUnitWork_t *pUnit, bool _pro);
s32 gohKarteCheckRegist(sdatUnitWork_t *pUnit, gohKarteList_t *pKarteList, bool _pro, bool _uniqChk);
s32 gohKarteRestoreDevil(sdatUnitWork_t *pUnit);
s32 gohKarteRegistDevilBtl(sdatUnitWork_t *pUnit, gohKarteList_t *pKarteList, s32 Mode, s32 type);
void gohKarteBackupAll(void);
void gohInitGlobalWorkKarte(void);
void gohDlcKarteReg(void);
s32 gohKarteRestoreAll(void);
s32 gohGetCombiCount(s32 iMode);
void gohSetCombiCount(s32 iValue);
void gohAddCombiCount(s32 iVal);
void gohSetLetterCnt(s32 iVal);
s32 gohGetRank(void);
void gohKarteCreateKarteUnitFromUnit(gohKarteUnit_t *pKarteUnit, sdatUnitWork_t *pUnit, s8 mode);
void gohKarteCreateUnitFromKarteUnit(sdatUnitWork_t *pUnit, gohKarteUnit_t *pKarteUnit);
s32 gohKarteRegistDevil(sdatUnitWork_t *pUnit, gohKarteList_t *pKarteList, s32 Mode, s32 type, bool _pro, sdatUnitWork_t *_overwrite);
s32 gohGetKarteProUnitCnt(gohKarteList_t *pKarteList);
s32 gohKarteProRegistDelDevil(sdatUnitWork_t *pUnit, gohKarteList_t *pKarteList);
s32 gohKarteGetRestoreCost(sdatUnitWork_t *pUnit);
s32 gohCreateRecoverUnit(gohGeneralList_t *pGeneralList);
s32 gohGetKarteProRegistNum(void);
s32 gohChkKarteState(s32 devilid, s32 _uniqCode, bool _pro);
gohKarteUnit_t *gohGetKarteUnit(sdatUnitWork_t *_unit, bool _pro);
void gohSetKarteLock(sdatUnitWork_t *_unit, bool _set, bool _pro);
bool gohGetKarteLock(sdatUnitWork_t *_unit, bool _pro);
void gohSetKarteFavSet(sdatUnitWork_t *_unit, bool _set, bool _pro);
bool gohGetKarteFav(sdatUnitWork_t *_unit, bool _pro);
