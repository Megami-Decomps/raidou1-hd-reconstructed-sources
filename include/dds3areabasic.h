#pragma once
#include "types.h"
#include "basic.h"

typedef struct dds3BasicArrayHandle_t dds3BasicArrayHandle_t;
typedef struct dds3BasicFunction_t dds3BasicFunction_t;
typedef struct dds3Basic_t dds3Basic_t;

extern dds3BasicFunction_t *Function;

bool CB_BasicDrawProcuder(dds3Basic_t *pBasic);
bool CB_ReleaseObjectBasic(dds3Basic_t *pBasic);
DDS3_AREABASIC_ITEMTYPE BasicTypeToItemType(BASIC_TYPE type);
dds3Basic_t *dds3AreaBasicAdd(u32 serialID, char *pName);
void dds3AreaBasicRegistItem(dds3Basic_t *pAreaBasic, dds3Basic_t *pItemBasic);
void dds3AreaBasicReleaseItem(dds3Basic_t *pAreaBasic, dds3Basic_t *pItemBasic);
dds3BasicArrayHandle_t *dds3AreaBasicGetItemArray(dds3Basic_t *pAreaBasic, DDS3_AREABASIC_ITEMTYPE itemType);
dds3BasicArrayHandle_t *dds3AreaBasicArrangeGetItemArray(dds3Basic_t *pAreaBasic, DDS3_AREABASIC_ITEMTYPE itemType, void *checkFunc, dds3Basic_t *pBasic);
dds3Basic_t *dds3AreaBasicGetFastArea(void);
