#include "types.h"
#include "ITM.h"
#include "cmpdebug.h"

#define ITEM_MNUM 12
#define STEP_MAX 3
#define D_PARAM_CHANGE 13
#define P_PARAM_CHANGE 16

typedef enum {
    DBG_REPORT_GIFT = 0,
    DBG_REPORT_HIROEMON = 1,
    DBG_REPORT_ZENI = 2,
    DBG_REPORT_TAKUMI = 3,
} DBG_REPORT;

typedef enum {
    DBG_AWARD_ZAKURO = 0,
    DBG_AWARD_RAIDOU_SKL = 1,
    DBG_AWARD_SETSUMA = 2,
    DBG_AWARD_KILL_DEVIL = 3,
    DBG_AWARD_HUUMA = 4,
    DBG_AWARD_COMB = 5,
    DBG_AWARD_LATER = 6,
} DBG_AWARD;

typedef enum {
    Par_Level = 0,
    Par_Hp = 1,
    Par_MaxHp = 2,
    Par_Str = 3,
    Par_Vit = 4,
    Par_Tec = 5,
    Par_Luck = 6,
    Par_Vice = 7,
    Par_BadSt = 8,
    Par_Chuusei = 9,
    Par_Exp = 10,
    Par_Omoide = 11,
    Par_Gift = 12,
    Par_Mag = 13,
    Par_MaxMag = 14,
    Par_SmnrRank = 15,
    Par_Uniq = 16,
    Par_Max = 17,
} Par;

typedef struct cmpDebugDate cmpDebugDate;

static char *paramenu;
static char *paraType;
static char *itemAllType;
static char *dvlReportType;
static char *awdText;
char *debugMainMenu;
char *debugMenuOnOff;
char *CMP_DEBUG_ASSETNAME;
char *CMP_DEBUG_PROCESS_NAME;
DEBUG_FLG flag;
cmpDebugDate *debugData;
s32 *testAddDevil;
ITM *noUseItemList;
