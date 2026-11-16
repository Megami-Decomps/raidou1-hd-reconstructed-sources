#pragma once
#include "types.h"

#define BATK_UP 0
#define BATK_DOWN 1
#define MATK_UP 2
#define MATK_DOWN 3
#define ESC_UP 4
#define ESC_DOWN 5
#define DEF_UP 6
#define DEF_DOWN 7
#define HIT_UP 8
#define HIT_DOWN 9
#define BATKx2 10
#define DEKAJA 11
#define DEKUNDA 12
#define MATKx2 13

#define ALL 1
#define TENMA 2
#define SYAMA 4
#define RAMA 3
#define TOUMA 4
#define KIMA 5
#define YUMA 6
#define JUMA 7

#define UP 9557
#define DOWN 682
#define NON 0
#define BATK_UP 1
#define BATK_DOWN 2
#define MATK_UP 4
#define MATK_DOWN 8
#define ESC_UP 16
#define ESC_DOWN 32
#define DEF_UP 64
#define DEF_DOWN 128
#define HIT_UP 256
#define HIT_DOWN 512
#define BATKx2 1024
#define DEKAJA 2048
#define DEKUNDA 4096
#define MATKx2 8192

#define FIELD 1
#define BATTLE 2

#define EXCEPT_CHARGE 1
#define HANSYA_MISS 2
#define COSTMUSI 4
#define DEAD 8
#define ENEMYUSELESS 16
#define HUNT 32
#define GUN_ISSEI 64
#define GUN_MAGIC 128

typedef enum {
    TAR_CODE_AI = 0,
    TAR_CODE_LIFEMIN = 1,
    TAR_CODE_BAD = 2,
    TAR_CODE_ID = 3,
    TAR_CODE_LIGHT = 4,
    TAR_CODE_DARK = 5,
    TAR_CODE_PLAYER = 6,
    TAR_CODE_JOKEN = 7,
    TAR_CODE_RND = 8,
    TAR_CODE_BAARLV = 9,
    TAR_CODE_LVMIN = 10,
    TAR_CODE_MYAI = 11,
    TAR_CODE_MINE = 12,
    TAR_CODE_HUMAN = 13,
    TAR_CODE_NOTBAD = 14,
    TAR_CODE_DEVIL = 15,
    TAR_CODE_RAHU = 16,
    TAR_CODE_REFRACT = 17,
    TAR_CODE_MPMAX = 18,
    TAR_CODE_ATTR_N = 19,
    TAR_CODE_REV = 20,
    TAR_CODE_CNT_HPMIN = 21,
    TAR_CODE_NONE = 22,
    TAR_CODE_HPMINR = 23,
} TAR_CODE;

typedef enum {
    SU_COMM_NON = 0,
    SU_COMM_ATTACK = 1,
    SU_COMM_SKILL = 2,
    SU_COMM_LINKAGE = 3,
    SU_COMM_ITEM = 4,
    SU_COMM_DEVILIZE = 5,
    SU_COMM_ESCAPE = 6,
    SU_COMM_HUNT = 7,
    SU_COMM_COUNTER = 8,
    SU_COMM_PARTY = 9,
    SU_COMM_WAIT = 10,
    SU_COMM_RETURN = 11,
    SU_COMM_SUMMON = 12,
    SU_COMM_BADWAIT = 13,
    SU_COMM_BADLOSS = 14,
    SU_COMM_BADDAMAGE = 15,
    SU_COMM_PRESS = 16,
    SU_COMM_BOSS = 17,
} SU_COMM;

typedef enum {
    UV_MV_NON = 0,
    UV_MV_ROT = 1,
    UV_MV_DASH = 2,
    UV_MV_MAX = 3,
} UV_MV;

typedef enum {
    UV_AUTOWAIT_OFF = 0,
    UV_AUTOWAIT_ON = 1,
} UV_AUTOWAIT;

typedef enum {
    UV_MODEL_S = 0,
    UV_MODEL_M = 1,
    UV_MODEL_L = 2,
    UV_MODEL_LL = 3,
    UV_MODEL_MAX = 4,
} UV_MODEL;

typedef enum {
    UV_SHADOW_NON = 0,
    UV_SHADOW_S = 1,
    UV_SHADOW_M = 2,
    UV_SHADOW_L = 3,
    UV_SHADOW_LL = 4,
    UV_SHADOW_MAX = 5,
} UV_SHADOW;

typedef enum {
    UV_END_NORM = 0,
    UV_END_PAUSE = 1,
    UV_END_OUT = 2,
    UV_END_STOP = 3,
    UV_END_MAX = 4,
} UV_END;

typedef enum {
    BTL_SND_TYPE_NORMAL1 = 1,
    BTL_SND_TYPE_NORMAL2 = 2,
    BTL_SND_TYPE_NORMAL3 = 3,
    BTL_SND_TYPE_NORMAL4 = 4,
    BTL_SND_TYPE_NORMAL5 = 5,
    BTL_SND_TYPE_NORMAL6 = 6,
    BTL_SND_TYPE_NORMAL7 = 7,
    BTL_SND_TYPE_NORMAL8 = 8,
    BTL_SND_TYPE_NORMAL9 = 9,
    BTL_SND_TYPE_NORMAL10 = 5,
    BTL_SND_TYPE_BOSS1 = 5,
    BTL_SND_TYPE_BOSS2 = 5,
    BTL_SND_TYPE_BOSS3 = 5,
    BTL_SND_TYPE_BOSS4 = 5,
    BTL_SND_TYPE_BOSS5 = 5,
    BTL_SND_TYPE_DDS3 = 13,
    BTL_SND_TYPE_MAX = 14,
} BTL_SND_TYPE;

typedef enum {
    ENC_ESC_ON = 0,
    ENC_ESC_OFF = 1,
} ENC_ESC;

typedef enum {
    ENC_FORMATION_NORMAL = 0,
} ENC_FORMATION;

typedef enum {
    SK_TYPE_NON = -1,
    SK_TYPE_NORMAL = 0,
    SK_TYPE_LINKAGE = 1,
    SK_TYPE_HUNT = 2,
    SK_TYPE_COUNTER = 3,
    SK_TYPE_AUTO = 4,
    SK_TYPE_GUN = 5,
} SK_TYPE;

typedef enum {
    NSK_COST_NON = 0,
    NSK_COST_HP = 1,
    NSK_COST_MP = 2,
} NSK_COST;

typedef enum {
    NSK_TARGET_TYPE_SINGLE = 0,
    NSK_TARGET_TYPE_GROUP = 1,
    NSK_TARGET_TYPE_ALL = 2,
    NSK_TARGET_TYPE_NON = 3,
} NSK_TARGET_TYPE;

typedef enum {
    NSK_TARGET_RAND_OFF = 0,
    NSK_TARGET_RAND_ON = 1,
} NSK_TARGET_RAND;

typedef enum {
    NSK_BUTURI = 0,
    NSK_MAGIC = 1,
    NSK_HUNT = 2,
} NSK;

typedef enum {
    NSK_HANEI_TYPE_NON = 0,
    NSK_HANEI_TYPE_DMG = 1,
    NSK_HANEI_TYPE_REC = 2,
    NSK_HANEI_TYPE_SET = 3,
    NSK_HANEI_TYPE_DOWN = 4,
    NSK_HANEI_TYPE_UP = 5,
    NSK_HANEI_TYPE_MAXHPDMG = 6,
    NSK_HANEI_TYPE_MAXHPREC = 7,
    NSK_HANEI_TYPE_PERDMG = 8,
    NSK_HANEI_TYPE_PERREC = 9,
    NSK_HANEI_TYPE_MAXPERDMG = 10,
    NSK_HANEI_TYPE_MAXPERREC = 11,
    NSK_HANEI_TYPE_DRAIN = 12,
    NSK_HANEI_TYPE_DRAIN2 = 13,
    NSK_HANEI_TYPE_DMGDIV = 14,
    NSK_HANEI_TYPE_RNDUP = 15,
} NSK_HANEI_TYPE;

typedef enum {
    NSK_BAD_TYPE_NON = 0,
    NSK_BAD_TYPE_ON = 1,
    NSK_BAD_TYPE_OFF = 2,
    NSK_BAD_TYPE_RNDON = 3,
} NSK_BAD_TYPE;

typedef enum {
    NSK_PROG_NON = 0,
    NSK_PROG_ANALYZE = 1,
    NSK_PROG_SUMMON = 2,
    NSK_PROG_ESCAPE = 3,
    NSK_PROG_SLEEPONLY = 4,
    NSK_PROG_ESUTOMA = 5,
    NSK_PROG_RIBERAMA = 6,
    NSK_PROG_RIFUTOMA = 7,
    NSK_PROG_RAITOMA = 8,
    NSK_PROG_PRESS = 9,
    NSK_PROG_ITEM = 10,
    NSK_PROG_DECOY = 11,
    NSK_PROG_GUARD = 12,
    NSK_PROG_TOMOGUI = 13,
    NSK_PROG_SEPARATE = 14,
    NSK_PROG_COMBINE = 15,
} NSK_PROG;

typedef enum {
    NSK_ANIME_NORMAL = 0,
    NSK_ANIME_DELAY5 = 1,
    NSK_ANIME_DELAY8 = 2,
    NSK_ANIME_DELAY10 = 3,
    NSK_ANIME_LEFT1 = 4,
    NSK_ANIME_LEFT5 = 5,
    NSK_ANIME_LEFT8 = 6,
    NSK_ANIME_LEFT10 = 7,
    NSK_ANIME_RIGHT1 = 8,
    NSK_ANIME_RIGHT5 = 9,
    NSK_ANIME_RIGHT8 = 10,
    NSK_ANIME_RIGHT10 = 11,
    NSK_ANIME_RAND1 = 12,
    NSK_ANIME_RAND5 = 13,
    NSK_ANIME_RAND8 = 14,
    NSK_ANIME_RAND10 = 15,
} NSK_ANIME;

typedef enum {
    NSK_HATUDO_NON = 0,
    NSK_HATUDO_NORMAL = 1,
    NSK_HATUDO_HANYOU = 2,
    NSK_HATUDO_AGI = 3,
    NSK_HATUDO_BUFU = 4,
    NSK_HATUDO_JIO = 5,
    NSK_HATUDO_ZAN = 6,
    NSK_HATUDO_MAGNA = 7,
    NSK_HATUDO_MEGIDO = 8,
    NSK_HATUDO_HAMA = 9,
    NSK_HATUDO_MUDO = 10,
    NSK_HATUDO_BOSS1 = 11,
    NSK_HATUDO_BOSS2 = 12,
    NSK_HATUDO_BOSS3 = 13,
    NSK_HATUDO_BOSS4 = 14,
    NSK_HATUDO_BOSS5 = 15,
    NSK_HATUDO_BOSS6 = 16,
    NSK_HATUDO_BOSS7 = 17,
    NSK_HATUDO_BOSS8 = 18,
    NSK_HATUDO_BOSS9 = 19,
    NSK_HATUDO_BOSS10 = 20,
    NSK_HATUDO_BOSS11 = 21,
    NSK_HATUDO_BOSS12 = 22,
    NSK_HATUDO_BOSS13 = 23,
    NSK_HATUDO_BOSS14 = 24,
    NSK_HATUDO_BOSS15 = 25,
    NSK_HATUDO_MAX = 26,
} NSK_HATUDO;

typedef struct datEncountFld_Area_t datEncountFld_Area_t;
typedef struct datEncountFld_t datEncountFld_t;

struct datEncountFld_Area_t {
    s32 pack0;
    s16 flg1;
    s16 pack1;
    s16 flg2;
    s16 pack2;
};

struct datEncountFld_t {
    s32 field;
    datEncountFld_Area_t *Encount[64];
};
