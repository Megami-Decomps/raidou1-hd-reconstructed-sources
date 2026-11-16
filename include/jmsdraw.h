#pragma once
#include "types.h"

typedef struct jmsCyousaPanel_t jmsCyousaPanel_t;
typedef struct jmsData_t jmsData_t;
typedef struct sprHandle_t sprHandle_t;

extern f32 offsetCharaIcon[7];

void DrawCyousaPanel(jmsCyousaPanel_t *pPanel, sprHandle_t *pSpr);
void DrawBtnIcon(s32 Type, s32 AlphaRate, sprHandle_t *pSpr);
void DrawModel(jmsData_t *pData, s32 CursorIndex);
void DrawModel_M(jmsData_t *pData, s32 CursorIndex);
