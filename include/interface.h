#pragma once
#include "types.h"

typedef enum {
    FR_COL_DEF = 0,
    FR_COL_RED = 1,
    FR_COL_BLUE = 2,
    FR_COL_YELLOW = 3,
    FR_COL_GREEN = 4,
    FR_COL_GLAY = 5,
    FR_COL_MAX = 6,
} FR_COL;

typedef enum {
    TMC00 = 0,
    TMC01 = 1,
    TMC02 = 2,
    TMC03 = 3,
    TMC04 = 4,
    TMC05 = 5,
    TMC06 = 6,
    TMC07 = 7,
    TMC08 = 8,
    TMC09 = 9,
    TMC10 = 10,
    TMC11 = 11,
    TMC12 = 12,
    TMC13 = 13,
    TMC14 = 14,
    TMC15 = 15,
    TMC16 = 16,
    TMC17 = 17,
    TMC18 = 18,
    TMC19 = 19,
    TMC20 = 20,
    TMC21 = 21,
    TMC22 = 22,
    TMC23 = 23,
    TMC24 = 24,
    TMC25 = 25,
} UI_COL;

typedef enum {
    FR_STYLE_MIN = 0,
    FR_STYLE_HELP = 1,
    FR_STYLE_SNUM = 2,
    FR_STYLE_LNUM = 3,
    FR_STYLE_MAX = 4,
} FR_STYLE;

typedef enum {
    FRW_HELP_SKILL = 0,
    FRW_HELP_ITEM = 1,
    FRW_HELP_SOUSA = 2,
    FRW_HELP_PARA = 3,
} FRW_HELP;

typedef enum {
    ITF_MESBINTYPE_MES = 0,
    ITF_MESBINTYPE_SEL = 1,
} ITF_MESBINTYPE;

typedef enum {
    VERSION = 2,
    MAGICCODE0 = 809980749,
    MAGICCODE1 = 826757965,
    MAXLABEL = 24,
} ITF_MESBIN;

typedef enum {
    ITF_MESMNG_STAT_NULL = 0,
    ITF_MESMNG_STAT_MES = 7,
    ITF_MESMNG_STAT_MES_NONE = 0,
    ITF_MESMNG_STAT_MES_READY = 1,
    ITF_MESMNG_STAT_MES_WAITWIN = 2,
    ITF_MESMNG_STAT_MES_BUSY = 3,
    ITF_MESMNG_STAT_MES_END = 4,
    ITF_MESMNG_STAT_SEL = 56,
    ITF_MESMNG_STAT_SEL_NONE = 0,
    ITF_MESMNG_STAT_SEL_READY = 8,
    ITF_MESMNG_STAT_SEL_WAITWIN = 16,
    ITF_MESMNG_STAT_SEL_BUSY = 24,
    ITF_MESMNG_STAT_SEL_SELECT = 32,
    ITF_MESMNG_STAT_SEL_END = 40,
    ITF_MESMNG_STAT_MESWIN = 768,
    ITF_MESMNG_STAT_MESWIN_CLOSED = 0,
    ITF_MESMNG_STAT_MESWIN_OPENING = 256,
    ITF_MESMNG_STAT_MESWIN_OPENED = 512,
    ITF_MESMNG_STAT_MESWIN_CLOSING = 768,
    ITF_MESMNG_STAT_SELWIN = 3072,
    ITF_MESMNG_STAT_SELWIN_CLOSED = 0,
    ITF_MESMNG_STAT_SELWIN_OPENING = 1024,
    ITF_MESMNG_STAT_SELWIN_OPENED = 2048,
    ITF_MESMNG_STAT_SELWIN_CLOSING = 3072,
    ITF_MESMNG_STAT_SPKWIN = 12288,
    ITF_MESMNG_STAT_SPKWIN_CLOSED = 0,
    ITF_MESMNG_STAT_SPKWIN_OPENING = 4096,
    ITF_MESMNG_STAT_SPKWIN_OPENED = 8192,
    ITF_MESMNG_STAT_SPKWIN_CLOSING = 12288,
    ITF_MESMNG_STAT_READONLY = 65535,
    ITF_MESMNG_STAT_NODISP_SPK = 65536,
    ITF_MESMNG_STAT_NODISP_MES = 131072,
    ITF_MESMNG_STAT_NODISP_SEL = 262144,
    ITF_MESMNG_STAT_NODISP_WIN = 524288,
    ITF_MESMNG_STAT_NODISP_LEAF = 1048576,
    ITF_MESMNG_STAT_REQ_WIN = 2097152,
    ITF_MESMNG_STAT_IGNORE_SPDUP = 4194304,
    ITF_MESMNG_STAT_IGNORE_NEXTPAGE = 8388608,
    ITF_MESMNG_STAT_KEYWAIT = 16777216,
} ITF_MESMNG_STAT;

typedef enum {
    ITF_MESMNG_VAR_INT = 0,
    ITF_MESMNG_VAR_DEVIL = 1,
    ITF_MESMNG_VAR_HUMAN = 2,
    ITF_MESMNG_VAR_ITEM = 3,
    ITF_MESMNG_VAR_FLOOR = 4,
    ITF_MESMNG_VAR_SKILL = 5,
    ITF_MESMNG_VAR_NTERM = 6,
    ITF_MESMNG_VAR_STERM = 7,
    ITF_MESMNG_VAR_RACE = 8,
    ITF_MESMNG_VAR_INPUT = 9,
    ITF_MESMNG_VAR_DH = 10,
    ITF_MESMNG_VAR_CODENAME = 11,
    ITF_MESMNG_VAR_DRLANG = 12,
} ITF_MESMNG_VAR;

typedef enum {
    CONFIG_HIGHSPEED = 1,
    DISPWIN = 2,
    VOID_SPEAKER = 65535,
} ITF_MESMNG;

typedef enum {
    ITF_PANEL_TYPE_NORMAL = 0,
    ITF_PANEL_TYPE_MESWIN = 1,
    ITF_PANEL_TYPE_SELWIN = 2,
    ITF_PANEL_TYPE_PLAIN = 3,
    ITF_PANEL_TYPE_PERA1 = 4,
    ITF_PANEL_TYPE_LEFTFADE = 5,
    ITF_PANEL_TYPE_MESWIN2 = 6,
    ITF_PANEL_TYPE_SPKWIN2 = 7,
    ITF_PANEL_TYPE_FACILITY = 8,
    ITF_PANEL_TYPE_NUM = 9,
} ITF_PANEL_TYPE;

typedef struct itfMesBinFileHeader_t itfMesBinFileHeader_t;
typedef struct itfMesBinMesHeader_t itfMesBinMesHeader_t;
typedef struct itfMesBinSelHeader_t itfMesBinSelHeader_t;
typedef struct itfMesBinTypeHeader2_t itfMesBinTypeHeader2_t;
typedef struct itfMesBinTypeHeader_t itfMesBinTypeHeader_t;
typedef struct itfPanelTypeWork_t itfPanelTypeWork_t;
typedef struct itfpanel_t itfpanel_t;
typedef struct sdfIVector4_t sdfIVector4_t;

struct itfMesBinFileHeader_t {
    u8 filetype;
    u8 format;
    s16 user_id;
    u32 filesize;
    u32 mgc;
    u32 extsize;
    u32 ofs_addrinfo;
    u32 size_addrinfo;
    u32 numtypeheader;
    u8 resolveaddress;
    u8 reserved0;
    u16 version;
};

struct itfMesBinTypeHeader_t {
    u32 type;
    s32 ptr;
};

struct itfMesBinTypeHeader2_t {
    s32 ppspkhead;
    s32 spknum;
    s32 pextdata;
    u32 reserved;
};

struct itfMesBinMesHeader_t {
    u8 *label;
    s16 page;
    u16 speaker;
    u32 *addr;
    s32 *len;
};

struct itfMesBinSelHeader_t {
    u8 *label;
    s16 ext;
    s16 item;
    s16 pattern;
    u16 reserved;
    u32 *ptr;
    s32 *len;
};

struct itfpanel_t {
    itfPanelTypeWork_t *pwork;
    s32 type;
    u32 z;
    sdfIVector4_t pos;
    sdfIVector4_t color;
};
