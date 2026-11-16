#pragma once
#include "types.h"

typedef enum {
    LanguageID_EN = 0,
    LanguageID_FR = 1,
    LanguageID_IT = 2,
    LanguageID_DE = 3,
    LanguageID_ES = 4,
    LanguageID_None = 5,
} LanguageID;

typedef enum {
    EFIGS = 0,
    AS = 1,
    JA = 2,
} LanguageTYPE;

typedef struct UIfontSize UIfontSize;

struct UIfontSize {
    s32 id;
    s32 lang;
    f32 font_size;
    s32 character;
    s32 line;
};

extern void *fileList;

LanguageID GetLanguageID(void);
LanguageTYPE GetLanguageTYPE(void);
char *GetLanguageTag(void);
char *GetAppendix(void);
s32 GetLanguage(void);
void LoadDefault(void *list);
void LoadLocalizeText(void *data);
void LoadLocalizeText_2(char *key, char *filename);
void LoadLocalizeText_3(char *key);
void Remove_2(char *filename);
void RemoveKey(char *key);
char *GetLocalizeText(char *ID, bool label);
bool ContainsLabel(char *ID);
s32 ContainsFileName(char *name);
s32 ContainsKeyName(char *key);
void *GetList(void);
void LoadPM1LocalizeText(s32 eventno);
void RemovePM1LocalizeText(s32 eventno);
void UIFontSizeInit(void);
UIfontSize *GetUIfontSize(s32 id, s32 all_lang, s32 type_lang);
