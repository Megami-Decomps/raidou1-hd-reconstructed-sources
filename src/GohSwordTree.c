#include "types.h"
#include "ITM.h"
#include "dat.h"
#include "dds3kernelcore.h"
#include "evtbit.h"
#include "gohinit.h"
#include "gohrenken.h"
#include "gohswordtree.h"
#include "jmsmisc.h"
#include "spweapon.h"

#define SPIRIT_LIST_MAX 4

typedef struct gohData_t gohData_t;

// 0x1c0c750
void GohCsrUpdate(gohData_t *_pData) {
  s32 gohTreeMenuType;

  if (!pData->spritCheck)
  {
    gohTreeMenuType = pData->gohTreeMenuType;
    if (gohTreeMenuType == 2)
    {
      (pData->treeSpiritCsr->klass->vtable._10_CsrUpdate.methodPtr)(pData->treeSpiritCsr, pData->treeSpiritCsr->klass->vtable._10_CsrUpdate.method);
    }
    else if (gohTreeMenuType == 1)
    {
      (pData->treeBattleCsr->klass->vtable._10_CsrUpdate.methodPtr)(pData->treeBattleCsr, pData->treeBattleCsr->klass->vtable._10_CsrUpdate.method);
    }
    else
    {
      SwordTreeCsrUpdate(pData);
    }
  }
}

// 0x1c0c940
void GohLrChangeUpdate(gohData_t *_pData) {
  ;
}

// 0x1c0c950
void GohTreeMenuTypeAdd(gohData_t *_pData) {
  s32 gohTreeMenuType;
  const MethodInfo_32670E0 *v4;
  s32 v5;
  Il2CppObject *Instance;

  gohTreeMenuType = pData->gohTreeMenuType;
  v4 = Method_Project_SingletonMonoBehaviour_GohCanvasManager__get_Instance__;
  if (gohTreeMenuType == 2)
    v5 = 0;
  else
    v5 = gohTreeMenuType + 1;
  pData->gohTreeMenuType = v5;
  pData->drawTreeUpdate = 1;
  Instance = _get_Instance(v4);
  (*(*(u64 *)Instance[16].klass->_1.methods + 408))(Instance[16].klass->_1.methods, *(u64 *)(*(u64 *)Instance[16].klass->_1.methods + 416));
  SE(0);
}

// 0x1c0c9e0
void GohTreeMenuTypeSub(gohData_t *_pData) {
  s32 gohTreeMenuType;
  const MethodInfo_32670E0 *v4;
  s32 v5;
  Il2CppObject *Instance;

  gohTreeMenuType = pData->gohTreeMenuType;
  v4 = Method_Project_SingletonMonoBehaviour_GohCanvasManager__get_Instance__;
  if (gohTreeMenuType)
    v5 = gohTreeMenuType - 1;
  else
    v5 = 2;
  pData->gohTreeMenuType = v5;
  pData->drawTreeUpdate = 1;
  Instance = _get_Instance(v4);
  (*(*(u64 *)Instance[16].klass->_1.methods + 408))(Instance[16].klass->_1.methods, *(u64 *)(*(u64 *)Instance[16].klass->_1.methods + 416));
  SE(0);
}

// 0x1c0ca70
void GohMouseCsrUpdate(gohData_t *pData) {
  ;
}

// 0x1c0ca80
void GohSetScrollCsrSet(gohData_t *pData) {
  Il2CppObject *Instance;
  TreeCsr *treeCsr;
  s32 v5;
  s32 v6;
  s32 v7;

  Instance = _get_Instance();
  treeCsr = pData->treeCsr;
  v5 = *((u32 *)Instance[16].klass->_1.implementedInterfaces + 6);
  if (treeCsr->type != v5)
  {
    pData->drawTreeUpdate = 1;
    if (v5 == 3)
      v6 = 2;
    else
      v6 = 1;
    treeCsr->type = v5;
    if (v5)
      v7 = v6;
    else
      v7 = 0;
    treeCsr->stage = v7;
    treeCsr->branch = 0;
    SE(3);
  }
}

// 0x1c0c7a0
void SwordTreeCsrUpdate(gohData_t *pData) {
  TreeCsr *treeCsr;
  void *swordTree;
  char v7;
  s32 v8;
  s32 v9;
  void *TypeList;
  s32 branch;
  Il2CppClass **implementedInterfaces;

  treeCsr = pData->treeCsr;
  swordTree = pData->Table->swordTree;
  v7 = jmsChkCommonInput(0xF1u);
  if ((v7 & 0x10) != 0)
  {
    GohTreeCsrNext(pData, 0);
    v8 = 1;
    if (v7 < 0)
      goto LABEL_6;
    goto LABEL_12;
  }
  if ((v7 & 0x20) != 0)
  {
    GohTreeCsrNext(pData, 1);
    v8 = 1;
    if (v7 < 0)
      goto LABEL_6;
  }
  else
  {
    v8 = 0;
    if (v7 < 0)
    {
LABEL_6:
      v9 = 3;
LABEL_14:
      GohTreeCsrNext(pData, v9);
      v8 = 1;
      goto LABEL_15;
    }
  }
LABEL_12:
  if ((v7 & 0x40) != 0)
  {
    v9 = 2;
    goto LABEL_14;
  }
LABEL_15:
  TypeList = GetTypeList(swordTree, treeCsr->stage, treeCsr->type, 0);
  branch = treeCsr->branch;
  if (branch < TypeList->_size)
  {
    treeCsr->item = (s32)_get_Item(TypeList, branch)[1].klass;
    if (v8)
    {
      implementedInterfaces = _get_Instance()[16].klass->_1.implementedInterfaces;
      if (implementedInterfaces)
        ScrollStepSet(implementedInterfaces, pData->treeCsr->type, 0);
      pData->drawTreeUpdate = 1;
    }
  }
}

// 0x1c0cb30
s32 GohTreeCsrNext(gohData_t *_pData, TreeCsrMove _csrMove) {
  TreeCsr *treeCsr;
  void *swordTree;
  void *TypeList;
  s32 type;
  s32 stage;
  s32 branch;
  s32 v11;
  s32 v12;
  s32 v13;
  s32 v14;
  void *v15;
  void *v16;
  char v17;
  s32 v18;
  Il2CppObject *Item;
  bool v20;
  s32 v21;
  s32 size;
  s32 v24;

  treeCsr = pData->treeCsr;
  swordTree = pData->Table->swordTree;
  TypeList = GetTypeList(swordTree, treeCsr->stage, treeCsr->type, 0);
  type = treeCsr->type;
  stage = treeCsr->stage;
  branch = treeCsr->branch;
  switch (csrMove)
  {
    case 0:
      if (--branch >= 0)
        goto LABEL_40;
      v11 = type - 1;
      if (type >= 1)
      {
        branch = GetTypeList(swordTree, stage, v11, 0)->_size - 1;
        goto LABEL_33;
      }
      branch = 0;
      goto LABEL_40;
    case 1:
      if (branch + 1 < TypeList->_size)
      {
        ++branch;
        goto LABEL_41;
      }
      if (type > 2)
        goto LABEL_40;
      v11 = type + 1;
      if (GetTypeList(swordTree, stage, type + 1, 0)->_size < 1)
        goto LABEL_40;
      if (type == 2 && !evtBitCheck(2960))
      {
        type = 2;
        if (treeCsr->stage == stage)
          goto LABEL_41;
      }
      else
      {
        branch = 0;
LABEL_33:
        type = v11;
        if (treeCsr->stage == stage)
          goto LABEL_41;
      }
      goto LABEL_43;
    case 2:
      v12 = 1;
      while (stage - v12 >= 0)
      {
        v13 = -v12;
        while (1)
        {
          v14 = stage + v13;
          v15 = GetTypeList(swordTree, stage + v13, type, 0);
          if (v15->_size >= 1)
            break;
          --v13;
          if (stage + v13 == -1)
          {
            v12 = stage + 1;
            goto LABEL_25;
          }
        }
        v16 = v15;
        v24 = type;
        v17 = 0;
        v18 = 0;
        do
        {
          Item = _get_Item(v16, v18);
          v20 = _Contains(Item[2].klass, treeCsr->item);
          v17 |= v20;
          if (v20)
            branch = v18;
          ++v18;
        }
        while (v18 < v16->_size);
        type = v24;
        v12 = -v13;
        stage += v13;
        if ((v17 & 1) != 0)
        {
          v12 = -v13;
          stage = v14;
          break;
        }
      }
LABEL_25:
      if (stage - v12 >= 0)
        goto LABEL_40;
      branch = 0;
      type = 0;
      stage = 0;
      if (treeCsr->stage)
        goto LABEL_43;
      goto LABEL_41;
    case 3:
      v21 = stage + 1;
      if (stage + 1 >= swordTree->treeList->_size)
        goto LABEL_40;
      break;
    default:
      goto LABEL_40;
  }
  while (1)
  {
    size = GetTypeList(swordTree, v21, type, 0)->_size;
    if (size >= 1)
      break;
    if (++v21 >= swordTree->treeList->_size)
    {
LABEL_40:
      if (treeCsr->stage == stage)
        goto LABEL_41;
      goto LABEL_43;
    }
  }
  if (size > branch)
    stage = v21;
  if (treeCsr->stage != stage)
    goto LABEL_43;
LABEL_41:
  if (treeCsr->type != type || treeCsr->branch != branch)
LABEL_43:
    SE(3);
  treeCsr->type = type;
  treeCsr->stage = stage;
  treeCsr->branch = branch;
  CsrDebugLog(treeCsr, 0);
  return 0;
}

// 0x1c0ce80
void GohCreateCheckSword(gohData_t *_pData) {
  s32 NowSelBaseSword;
  char spSword;

  NowSelBaseSword = GohGetNowSelBaseSword();
  if (IndexOf_Int32Enum_(tbl, pData->treeCsr->item) != -1)
  {
    spSword = pData->spSword;
    if (!spSword)
      goto LABEL_15;
  }
  if (NowSelBaseSword)
  {
    if ((u32)(NowSelBaseSword - 144) <= 0x63)
    {
      if (((GBWK->SwordHistory->m_haveBits[(u32)(NowSelBaseSword - 144) >> 3] >> (NowSelBaseSword & 7)) & 1) != 0)
      {
        spSword = 1;
LABEL_15:
        pData->swordDetails = spSword;
        return;
      }
    }
    pData->swordDetails = 0;
  }
  else
  {
    pData->swordDetails = 1;
  }
}

// 0x1c0d1b0
bool GohCreateCheckSelSword(gohData_t *_pData, ITM _baseSd, ITM _sd) {
  bool result;
  s32 ItmSwordNo;
  u32 v7;
  s32 v9;
  s32 v10;

  if (sd == 145)
    return 0;
  ItmSwordNo = GetItmSwordNo(sd, 0);
  v7 = GetItmSwordNo(baseSd, 0);
  v9 = gohCheckComposition(ItmSwordNo, v7);
  if (v7 > 0x63)
    return 0;
  v10 = v9;
  if (v10)
    return 0;
  result = 1;
  if (((1 << (v7 & 7)) & GBWK->SwordHistory->m_haveBits[v7 >> 3]) != 0)
    return result;
  return 0;
}

// 0x1c0cfe0
ITM GohGetNowSelBaseSword(void) {
  Il2CppObject *ProcessData;
  s32 *monitor;
  void *TypeList;
  Il2CppObject *Item;

  ProcessData = dds3GetProcessData(GlobalPID);
  if (!ProcessData)
    return 0;
  monitor = ProcessData[31].monitor;
  TypeList = GetTypeList(ProcessData[17].klass->_1.parent, monitor[4], monitor[7], 0);
  if (_get_Item(TypeList, monitor[5])[1].monitor && *((s32 *)_get_Item(TypeList, monitor[5])[1].monitor + 6) >= 1)
  {
    Item = _get_Item(TypeList, monitor[5]);
    return _get_Item(Item[1].monitor, 0);
  }
  return 0;
}
