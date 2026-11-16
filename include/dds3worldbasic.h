#pragma once
#include "types.h"

typedef struct dds3BasicArrayHandle_t dds3BasicArrayHandle_t;
typedef struct dds3BasicFunction_t dds3BasicFunction_t;
typedef struct dds3Basic_t dds3Basic_t;

extern dds3BasicFunction_t *Function;
extern dds3Basic_t *dds3TheWorld;

dds3Basic_t *Add(s32 bufcnt);
void Delete(void);
void dds3SetActiveScene(dds3Basic_t *scene);
dds3Basic_t *dds3GetActiveScene(void);
void dds3SetControlScene(dds3Basic_t *scene);
dds3Basic_t *dds3GetControlScene(void);
dds3Basic_t *dds3AddScene(void);
void dds3DeleteScene(dds3Basic_t *scene);
dds3BasicArrayHandle_t *dds3GetBasicArrayHandle(s32 bufcnt);
void dds3FreeBasicArrayHandle(dds3BasicArrayHandle_t *hndl);
void dds3DeleteBasicArray(dds3BasicArrayHandle_t *hndl);
void dds3DeleteAllBasicArray(dds3BasicArrayHandle_t *hndl);
bool dds3SearchDeleteBasicArray(dds3BasicArrayHandle_t *hArray, dds3Basic_t *pBasic, u32 mode);
bool dds3SetSearchNextBasicArray(dds3BasicArrayHandle_t *hArray, dds3Basic_t *pBasic);
bool dds3AddBasicArray(dds3BasicArrayHandle_t *hndl, s32 bufcnt);
s32 dds3GetBasicArrayCount(dds3BasicArrayHandle_t *hndl);
bool dds3SetBasicArray(dds3BasicArrayHandle_t *hndl, dds3Basic_t *data);
dds3Basic_t *dds3GetBasicArray(dds3BasicArrayHandle_t *hndl);
bool dds3SetFirstBasicArray(dds3BasicArrayHandle_t *hndl);
bool dds3SetNextBasicArray(dds3BasicArrayHandle_t *hndl);
bool dds3CallbackBasicArray(dds3BasicArrayHandle_t *hndl, void *func);
