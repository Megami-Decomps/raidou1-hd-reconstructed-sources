#pragma once
#include "types.h"

void LogTextSet(char *_str, s32 _fontSize, s32 _maxLine, s32 _fontCol);
void LogPrevSet(char *_str, s32 _fontSize, s32 _maxLine, s32 _fontCol);
void ClearText(void);
void TextPosChange(s32 _x, s32 _y);
void ActiveBackBorad(bool _active);
void DebugTextSet(char *_debugText);
