#include "types.h"
#include "commonui.h"

// 0x223f640
bool ActiveOnOff(void *_object, bool _active) {
  bool activeSelf;

  activeSelf = get_activeSelf(object, 0);
  if (active)
  {
    if (activeSelf)
      return 0;
  }
  else if (!activeSelf)
  {
    return 0;
  }
  SetActive(object, active, 0);
  return 1;
}

// 0x223f6a0
bool EnabledOnOff(void *_object, bool _active) {
  bool enabled;

  enabled = get_enabled(object, 0);
  if (active)
  {
    if (enabled)
      return 0;
  }
  else if (!enabled)
  {
    return 0;
  }
  set_enabled(object, active, 0);
  return 1;
}

// 0x223f700
bool AnimChangeCheck(void *_anim) {
  void *gameObject;
  void *runtimeAnimatorController;

  if (op_Equality(anim, 0, 0))
    return 0;
  gameObject = get_gameObject(anim, 0);
  if (!get_activeInHierarchy(gameObject, 0))
    return 0;
  runtimeAnimatorController = get_runtimeAnimatorController(anim, 0);
  return !op_Equality(runtimeAnimatorController, 0, 0);
}

// 0x223f800
bool AnimEndCheck(void *_anim, s32 _layer) {
  UnityEngine_AnimatorStateInfo_o v4;
  UnityEngine_AnimatorStateInfo_o v5;

  GetCurrentAnimatorStateInfo(&v4, anim, layer, 0);
  v5 = v4;
  return get_normalizedTime(&v5, 0) >= 1.0;
}

// 0x223f850
void GraphicRayOnOff(void *_canvasObj, bool _active) {
  Il2CppObject *Component_object;

  goto LABEL_3;
LABEL_7:
  Component_object = GetComponent_object_(canvasObj);
  if (!op_Inequality(Component_object, 0, 0))
    return;
  set_enabled(Component_object, active, 0);
  return;
LABEL_3:
  if (op_Inequality(canvasObj, 0, 0))
    goto LABEL_7;
}
