#pragma once
#include "types.h"
#include "field.h"
#include "fieldEnemySymbol.h"

typedef struct AtlEnemySymbol AtlEnemySymbol;
typedef struct AtlEnemySymbolChoiceData AtlEnemySymbolChoiceData;
typedef struct AtlEnemySymbolTableData AtlEnemySymbolTableData;
typedef struct ESEncountTbl_EncountPack_t ESEncountTbl_EncountPack_t;
typedef struct ESEncountTbl_t ESEncountTbl_t;
typedef struct datRndEncTbl_t datRndEncTbl_t;

bool IsEnableChapter(ESEncountTbl_t *data);
void mapDraw_KemuriReq_E(const sdfVector3_t *pos);
void mapDraw_KemuriReq_Big2(const sdfVector3_t *pos);
datRndEncTbl_t *GetEncountTableInRndPackData(ESEncountTbl_EncountPack_t *pack);
AtlEnemySymbolChoiceData ChoiceEncount(AtlEnemySymbolTableData *data, bool isAlreadyDestroy);
bool IsEnableEncountPack(ESEncountTbl_EncountPack_t *pack);
s32 ConvEncountIDToEnemyID(s32 dlcID, s32 encountID);
eEnemySymbolPopSkillStatus CalcCurrentPopSkillStatus(void);
sdfVector3_t CalcOtherEnemyClosestPoint(AtlEnemySymbol *checkSymbol, sdfVector3_t *pos);
eType CalcTargetRingType(AtlEnemySymbol *symbol);
bool IsInstantDeath(AtlEnemySymbol *symbol);
