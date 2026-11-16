#include "types.h"
#include "atlfieldtableresource.h"

#define c_AssetBundleName "battle"
#define c_AssetName_ESEncount "ESEncountTbl"
#define c_AssetName_ESConst "ESConstTbl"
#define c_AssetName_ESDevil "ESDevilTbl"
#define c_AssetName_MobChara "MapMobCharaTbl"
#define c_AssetName_MobPlace "MapMobPlaceTbl"
#define c_AssetName_ScriptEx "MapScriptExTbl"

void *fldESEncountTbl;
void *fldESConstTbl;
void *fldESDevilTbl;
void *mobCharaTbl;
void *mobPlaceTbl;
void *scriptEx;

// 0x22aac90
void Load(void) {
  void *Asset;
  s64 naturalAligment;
  void *v4;
  void *v5;
  s64 v7;
  void *v10;
  s64 v12;
  void *v13;
  void *v14;
  void *p_fldESConstTbl;
  void *v20;
  s64 v22;
  void *v23;
  void *v24;
  void *p_fldESDevilTbl;
  void *v30;
  s64 v32;
  void *v33;
  void *v34;
  void *p_mobCharaTbl;
  void *v40;
  s64 v42;
  void *v43;
  void *v44;
  void *p_mobPlaceTbl;
  void *v50;
  s64 v52;
  void *v53;
  void *v54;
  void *p_scriptEx;

  fldESEncountTbl = 0;
  Asset = LoadAsset(_Ctrl_k__BackingField, "battle", "ESEncountTbl", 0);
  if (Asset)
  {
    if (Asset->klass->_2.naturalAligment >= (u32)naturalAligment)
    {
      if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_ESEncountTbl)
        v4 = Asset;
      else
        v4 = 0;
    }
    else
    {
      v4 = 0;
    }
    fldESEncountTbl = v4;
    if (Asset->klass->_2.naturalAligment >= (u32)v7)
    {
      if (Asset->klass->_2.typeHierarchy[v7 - 1] == Project_ESEncountTbl)
        v5 = Asset;
      else
        v5 = 0;
    }
    else
    {
      v5 = 0;
    }
  }
  else
  {
    v5 = 0;
    fldESEncountTbl = 0;
  }
  Initialize(fldESEncountTbl);
  fldESConstTbl = 0;
  v10 = LoadAsset(_Ctrl_k__BackingField, "battle", "ESConstTbl", 0);
  if (v10)
  {
    if (v10->klass->_2.naturalAligment >= (u32)v12)
    {
      if (v10->klass->_2.typeHierarchy[v12 - 1] == Project_ESConstTbl)
        v13 = v10;
      else
        v13 = 0;
    }
    else
    {
      v13 = 0;
    }
    fldESConstTbl = (void *)v13;
    p_fldESConstTbl = &fldESConstTbl;
    if (v10->klass->_2.naturalAligment >= (u32)v12)
    {
      if (v10->klass->_2.typeHierarchy[v12 - 1] == Project_ESConstTbl)
        v14 = v10;
      else
        v14 = 0;
    }
    else
    {
      v14 = 0;
    }
  }
  else
  {
    v14 = 0;
    fldESConstTbl = 0;
    p_fldESConstTbl = &fldESConstTbl;
  }
  Initialize(fldESConstTbl);
  fldESDevilTbl = 0;
  v20 = LoadAsset(_Ctrl_k__BackingField, "battle", "ESDevilTbl", 0);
  if (v20)
  {
    if (v20->klass->_2.naturalAligment >= (u32)v22)
    {
      if (v20->klass->_2.typeHierarchy[v22 - 1] == Project_ESDevilTbl)
        v23 = v20;
      else
        v23 = 0;
    }
    else
    {
      v23 = 0;
    }
    fldESDevilTbl = (void *)v23;
    p_fldESDevilTbl = &fldESDevilTbl;
    if (v20->klass->_2.naturalAligment >= (u32)v22)
    {
      if (v20->klass->_2.typeHierarchy[v22 - 1] == Project_ESDevilTbl)
        v24 = v20;
      else
        v24 = 0;
    }
    else
    {
      v24 = 0;
    }
  }
  else
  {
    v24 = 0;
    fldESDevilTbl = 0;
    p_fldESDevilTbl = &fldESDevilTbl;
  }
  Initialize(fldESDevilTbl);
  mobCharaTbl = 0;
  v30 = LoadAsset(_Ctrl_k__BackingField, "battle", "MapMobCharaTbl", 0);
  if (v30)
  {
    if (v30->klass->_2.naturalAligment >= (u32)v32)
    {
      if (v30->klass->_2.typeHierarchy[v32 - 1] == Project_MapMobCharaTbl)
        v33 = v30;
      else
        v33 = 0;
    }
    else
    {
      v33 = 0;
    }
    mobCharaTbl = (void *)v33;
    p_mobCharaTbl = &mobCharaTbl;
    if (v30->klass->_2.naturalAligment >= (u32)v32)
    {
      if (v30->klass->_2.typeHierarchy[v32 - 1] == Project_MapMobCharaTbl)
        v34 = v30;
      else
        v34 = 0;
    }
    else
    {
      v34 = 0;
    }
  }
  else
  {
    v34 = 0;
    mobCharaTbl = 0;
    p_mobCharaTbl = &mobCharaTbl;
  }
  Initialize(mobCharaTbl);
  mobPlaceTbl = 0;
  v40 = LoadAsset(_Ctrl_k__BackingField, "battle", "MapMobPlaceTbl", 0);
  if (v40)
  {
    if (v40->klass->_2.naturalAligment >= (u32)v42)
    {
      if (v40->klass->_2.typeHierarchy[v42 - 1] == Project_MapMobPlaceTbl)
        v43 = v40;
      else
        v43 = 0;
    }
    else
    {
      v43 = 0;
    }
    mobPlaceTbl = (void *)v43;
    p_mobPlaceTbl = &mobPlaceTbl;
    if (v40->klass->_2.naturalAligment >= (u32)v42)
    {
      if (v40->klass->_2.typeHierarchy[v42 - 1] == Project_MapMobPlaceTbl)
        v44 = v40;
      else
        v44 = 0;
    }
    else
    {
      v44 = 0;
    }
  }
  else
  {
    v44 = 0;
    mobPlaceTbl = 0;
    p_mobPlaceTbl = &mobPlaceTbl;
  }
  Initialize(mobPlaceTbl);
  scriptEx = 0;
  v50 = LoadAsset(_Ctrl_k__BackingField, "battle", "MapScriptExTbl", 0);
  if (v50)
  {
    if (v50->klass->_2.naturalAligment >= (u32)v52)
    {
      if (v50->klass->_2.typeHierarchy[v52 - 1] == Project_MapScriptExTbl)
        v53 = v50;
      else
        v53 = 0;
    }
    else
    {
      v53 = 0;
    }
    scriptEx = (void *)v53;
    p_scriptEx = &scriptEx;
    if (v50->klass->_2.naturalAligment >= (u32)v52)
    {
      if (v50->klass->_2.typeHierarchy[v52 - 1] == Project_MapScriptExTbl)
        v54 = v50;
      else
        v54 = 0;
    }
    else
    {
      v54 = 0;
    }
  }
  else
  {
    v54 = 0;
    scriptEx = 0;
    p_scriptEx = &scriptEx;
  }
  Initialize(scriptEx);
}
