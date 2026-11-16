#pragma once
#include "types.h"

bool ActiveOnOff(void *_object, bool _active);
bool EnabledOnOff(void *_object, bool _active);
bool AnimChangeCheck(void *_anim);
bool AnimEndCheck(void *_anim, s32 _layer);
void GraphicRayOnOff(void *_canvasObj, bool _active);
