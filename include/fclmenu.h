#pragma once
#include "types.h"

void fclAnimFunc(s32 mode);
void fclSetApperTitle(void);
void fclSetDisapperTitle(void);
void fclSetParamTitle(char *a_str);
bool fclSetParamFull(s16 a_id, s16 a_type, s16 a_parentId, bool a_bSelect, bool a_bDrawTitle, s32 a_posx, s32 a_posy, char *a_str);
bool fclSetParam(s16 a_id, s16 a_parentId, bool a_bSelect, bool a_bDrawTitle, char *a_str);
bool fclSetFlagSelect(s16 a_id, bool a_bSelect);
bool fclSetFlagDecideEnd(s16 a_id);
bool fclSetCursor(s16 a_id, s32 a_x, s32 a_y, s32 a_model);
s32 getTarget(void);
void fclSetLink(void);
void fclStartUpdate(void);
s16 fclGetSelectId(void);
s16 fclGetSelectIdEx(void);
s32 fclGetHierarchy(void);
void fclSetTargetId(s16 a_id);
u8 fclGetTitleAlphaRate(void);
s16 fclUpdate(void);
u8 fclGetPanelAlpha(void);
u8 fclGetTitleAlpha(void);
void fclDraw(void);
void fclCreate(s32 a_nMenu);
void fclDelete(void);
