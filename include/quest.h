#pragma once
#include "types.h"

typedef struct QUEST_CLASS QUEST_CLASS;

struct QUEST_CLASS {
    s32 ID;
    s32 type;
    s32 stFlag[4];
    s32 edFlag[4];
    s32 nItemID[5];
    s32 nItemNum[5];
    s32 nDevilID[3];
    s32 nKatana[6];
    s32 encountID[3];
    s32 rItemID[5];
    s32 rItemNum[5];
    s32 rDevilFlag[2];
    s32 rMoney;
    s32 rKatana;
    s32 category;
};

extern QUEST_CLASS *QUESTDATA[46];
extern char *QuestDataAssetKey;
extern bool isResultRun;

void Init(void);
void Delete(void);
QUEST_CLASS *GetQuestData(s32 ID);
void QuestClearReward(s32 _id);
s32 GetQuestType(s32 _id);
s32 GetQuestCategory(s32 _id);
s32 GetQuestNeedItemID(s32 _id, s32 _no);
s32 GetQuestNeedItemNum(s32 _id, s32 _no);
s32 GetQuestNeedDevilID(s32 _id, s32 _no);
s32 GetQuestNeedKatanaID(s32 _id, s32 _no);
s32 GetQuestEncountID(s32 _id, s32 _no);
s32 GetQuestRewardItemID(s32 _id, s32 _no);
s32 GetQuestRewardItemNum(s32 _id, s32 _no);
s32 GetQuestRewardDevilFlag(s32 _id, s32 _no);
s32 GetQuestRewardMoney(s32 _id);
s32 GetQuestRewardKatana(s32 _id);
bool ChackRewardReceive(s32 _id);
s32 CheckClearFlag(void);
void DrawCherryBlossomEff(void);
void LoadCherryBlossomEff(const sdfVector4_t *effPos);
void DeleteCherryBlossomEff(void);
bool CheckResultRun(void);
void StartQuestResult(s32 quest_id);
void SetPopUp(void *txt, f32 time, void *spr);
void SetPopUpOver(char *txt, f32 time, void *spr);
void StartPopup(void);
void SetReturnMapBgm(s32 map, s32 floor, bool flag);
void MainProcess(void);
