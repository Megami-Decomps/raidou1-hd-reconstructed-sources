#pragma once
#include "types.h"
#include "AUTO.h"
#include "MODELTYPE.h"
#include "SBTLUNIT_MODE.h"
#include "SBTLUNIT_MOTION.h"
#include "SBTLUNIT_SIDE.h"
#include "SBTLUNIT_ST.h"
#include "SBTLUNIT_VST.h"
#include "SBTL_MODE.h"
#include "SBWEAPON_TYPE.h"
#include "SKLID.h"
#include "kernel.h"

#define BSIM_WAITO 0
#define BSIM_WALKO 0
#define BSIM_TBUTU 15
#define BSIM_MAGICO 7
#define BSIM_MAGICC 7
#define BSIM_WAITC 11
#define BSIM_WALKC 11
#define BSIM_DEAD 12
#define BSIM_FADEIN 13
#define BSIM_KIKAN 14
#define BSIM_DAMAGE 4
#define BSIM_DOWN 5
#define BSIM_BSTWO 2
#define BSIM_BSTWC 2
#define BSIM_SPECIAL 32
#define BSIM_YOKO_ST 33
#define BSIM_YOKO_LP 34
#define BSIM_YOKO_END 35
#define BSIM_TATE_ST 36
#define BSIM_TATE_LP 37
#define BSIM_TATE_END 38
#define BSIM_YOKO2TATE_LP 39
#define BSIM_TATE2YOKO_LP 40
#define BSAM_SKYW 32
#define BSAM_THROW 33
#define BSAM_SAKEBI 34
#define BSRP_SUMMON 32
#define BSRP_LASER 33
#define BSRP_VODKA 34
#define BSRP_BOMB 35
#define BSMR_SUMMON 32
#define BSMR_OC_LP 33
#define BSMR_OC_ED 34
#define BSMR_BOMB 35
#define BSMS_HIRU_ST 32
#define BSMS_HIRU_LP 33
#define BSMS_HIRU_ED 34
#define BSMS_BOU_ST 35
#define BSMS_BOU_WT 36
#define BSMS_TATK 37
#define BSMS_BOU_O_ST 38
#define BSMS_BOU_O_LP 39
#define BSMS_BOU_O_ED 40
#define BSMS_BOU_DOWN 41
#define BSSH_KIN_ST 32
#define BSSH_KIN_LP 33
#define BSSH_KIN_ED 34
#define BSSH_KATK 35
#define BSKY_GUARD 32
#define BSKY_SETU_ST 33
#define BSKY_SETU_LP 34
#define BSKY_SETU_ED 35
#define BSKY_SETU_RT 36
#define BSKY_SETU_D_IN 37
#define BSKY_SETU_D_OUT 38
#define BSKY_SMN_DIS 39
#define BSKY_BACKSTEO 40
#define BSKY_QUICK_MOVE 41
#define BSKY_QUICK_STOP 42
#define BSKY_QUICK_ATK 43
#define BS_T_OKI_UZU 32
#define BS_T_OKI_OKI_ST 33
#define BS_T_OKI_OKI_LP 34
#define BS_T_OKI_BIG 35
#define BS_T_OKI_MIORO 36
#define BS_T_OKI_KOUKO_ST 37
#define BS_T_OKI_KOUKO_LP 38
#define BS_T_OKI_LR 39
#define BSGN_WAIT 0
#define BSGN_WALK 1
#define BSGN_BST_W 2
#define BSGN_DAMAGE 4
#define BSGN_DOWN 5
#define BSGN_ATTACK 6
#define BSGN_TBUTU 15
#define BSGN_MASIC 7
#define BSGN_BRESS 8
#define BSGN_I 9
#define BSGN_BATTACK 10
#define BSGN_GUARD 11
#define BSGN_DEAD 12
#define BSGN_FADEIN 13
#define BSGN_KIKAN 14
#define BSGN_WPIN 13
#define BSGN_WPOUT 14
#define BSGN_SATTACK1 17
#define BSGN_SATTACK2 18
#define BSGN_SATTACK3 19
#define BSGN_SATTACK4 20
#define BSGN_SATTACK5 21
#define BSGN_SATTACK6 22
#define BSGN_SATTACK7 23
#define BSGN_SATTACK8 24
#define BSGN_SATTACK9 25
#define BSGN_SATTACKA 26
#define BSGN_SATTACKB 27
#define BSGN_REV1 16
#define BSYM_SATTACK 15
#define BSYM_TBUTU 6
#define BSMS_WPOUT 17
#define BSMS_WPIN 18
#define BSAK_MAGIC 24
#define BSAK_WPOUT 20
#define BSAK_WPIN 21
#define BSMT1_WAIT 0
#define BSMT1_DAMAGE 12
#define BSMT1_MAGIC 7
#define BSMT1_FADEIN 13
#define BSMT1_DESTROY 17
#define BSMT2_WAIT 18
#define BSMT2_DAMAGE 20
#define BSMT2_MAGIC 22
#define BSMT2_DESTROY 21
#define BSMT3_WAIT 23
#define BSMT3_MAGIC 26
#define BSMT3_DESTROY 25
#define BSRS_DEAD1 12
#define BSRS_MATO 17
#define BSRS_KAISOU 18
#define BSRS_HIDE 19
#define BSRS_TOHINSHI 20
#define BSRS_HINSHIWAIT 21
#define BSRS_DEAD2 22
#define BSRS_DEADWAIT 23
#define BSTT_BARRIER 0
#define BSTT_BAROFF 1
#define BSCS_WAIT_FAR 0
#define BSCS_WAIT_CLOSE 22
#define BSCR_WAIT 0
#define BSCR_PLASMA_R2 12
#define BSCR_PLASMA_L2 13
#define BSCK_DEAD 16
#define MODELLMAX 48
#define MAJORNO_PLAYER 0
#define MAJORNO_DEVIL 1
#define MAJORNO_ITEM 1
#define NULL 65535
#define MNO_WAIT 0
#define MNO_DAMAGE 1
#define MNO_BST_W 2
#define MNO_ATTACK 3
#define MNO_MASIC 4
#define MNO_WALK 9
#define MNO_FADEIN 10
#define MNO_BATTACK 11
#define MNO_DOWN 12
#define MNO_DOWNM 13
#define MNO_YOBIA 14
#define MNO_KAITEN 15
#define MNO_WPOUT 16
#define MNO_WPIN 17
#define MNO_BOBJ 1
#define NMNO_WAIT 0
#define NMNO_WALK 1
#define NMNO_BST_W 2
#define NMNO_REV0 3
#define NMNO_DAMAGE 4
#define NMNO_DOWN 5
#define NMNO_ATTACK 6
#define NMNO_MASIC 7
#define NMNO_BRESS 8
#define NMNO_BATTACK 9
#define NMNO_ZAN 10
#define NMNO_GDC 11
#define NMNO_DEAD 12
#define NMNO_FADEIN 13
#define NMNO_KIKAN 14
#define NMNO_TBUTU 15
#define NMNO_REV1 16
#define NMNO_REV2 17
#define NMNO_REV3 18
#define NMNO_REV4 19
#define NMNO_REV5 20
#define NMNO_REV6 21
#define NMNO_REV7 22
#define NMNO_REV8 23
#define NMNO_REV9 24
#define NMNO_REV10 25
#define NMNO_REV11 26
#define NMNO_REV12 27
#define NMNO_REV13 28
#define NMNO_REV14 29
#define NMNO_REV15 30
#define NMNO_REV16 31
#define BMNO_A020 32
#define BMNO_A021 33
#define BMNO_A022 34
#define BMNO_A023 35
#define BMNO_A024 36
#define BMNO_A025 37
#define BMNO_A026 38
#define BMNO_A027 39
#define BMNO_A028 40
#define BMNO_A029 41
#define BMNO_A02a 42
#define BMNO_A02b 43
#define BMNO_A02c 44
#define BMNO_A02d 45
#define BMNO_A02e 46
#define BMNO_A02f 47
#define PMNO_WAIT 0
#define PMNO_WALK 1
#define PMNO_BST_W 2
#define PMNO_BWALK 3
#define PMNO_DAMAGE 4
#define PMNO_DOWN 5
#define PMNO_HUUMAOK 6
#define PMNO_HUUMA 7
#define PMNO_HINS_W 8
#define PMNO_HINS_M 9
#define PMNO_0A 10
#define PMNO_SD_GUARD 11
#define PMNO_DEAD 12
#define PMNO_SORDR 13
#define PMNO_ANIM0E 14
#define PMNO_ITEMU 15
#define PMNO_SUMMON 16
#define PMNO_RETURN 17
#define PMNO_MEIREI 18
#define PMNO_YOBIYO 19
#define PMNO_OIUCHI 20
#define PMNO_RELOAD 21
#define PMNO_HGUNN 22
#define PMNO_GUN 23
#define PMNO_SD_COMBO4 24
#define PMNO_GUN_C 25
#define PMNO_HGUNR 26
#define PMNO_NSORD1 27
#define PMNO_NSORD2 28
#define PMNO_NSORD3 29
#define PMNO_MAGTUKI 30
#define PMNO_CHG_S_S 31
#define PMNO_CHG_M_S 32
#define PMNO_IAITATE 33
#define PMNO_RENKEI 34
#define PMNO_CHG_S_G 35
#define PMNO_CHG_M_G 36
#define PMNO_RAINPIKE 37
#define PMNO_RENDUKI 38
#define PMNO_TADANOTUKI 39
#define PMNO_MAWASIKERI 40
#define PMNO_BAKUTEN 41
#define PMNO_ZENTEN 42
#define PMNO_LC_GUARD 43
#define PMNO_AX_GUARD 44
#define PMNO_LOOKUP_IN 45
#define PMNO_LOOKUP_LOOP 46
#define PMNO_RESV_2F 47
#define PMNO_RESV_30 48
#define PMNO_SD_COMBI1 49
#define PMNO_LC_COMBI1 50
#define PMNO_AX_COMBI1 51
#define PMNO_COMBI_KAI 52
#define PMNO_RESV_35 53
#define PMNO_CHG_WALK 54
#define PMNO_CHG_WAIT 55
#define PMNO_CHG_ST 56
#define PMNO_CHG_ED 57
#define PMNO_SD_COMBI2 58
#define PMNO_LC_COMBI2 59
#define PMNO_AX_COMBI2 60
#define PMNO_RESV_3D 61
#define PMNO_RESV_3E 62
#define PMNO_RESV_3F 63
#define PMNO_RESV_40 64
#define PMNO_RESV_41 65
#define PMNO_RESV_42 66
#define PMNO_RESV_43 67
#define PMNO_RESV_44 68
#define PMNO_RESV_45 69
#define PMNO_RESV_46 70
#define PMNO_RESV_47 71
#define PMNO_RESV_48 72
#define PMNO_RESV_49 73
#define PMNO_GUN_TYUSHYOT 74
#define PMNO_GUN_DAISHYOT 75
#define PMNO_GUN_CHG 76
#define PMNO_GUN_CHG_ST 77
#define PMNO_GUN_CHG_ED 78
#define PMNO_GUN_CHG_MF 79
#define PMNO_GUN_CHG_MR 80
#define PMNO_GUN_CHG_MB 81
#define PMNO_GUN_CHG_ML 82
#define PMNO_SETSUMA1 83
#define PMNO_SETSUMA2 84
#define PMNO_SETSUMA3 85
#define PMNO_SETSUMA4 86
#define PMNO_JUMPATK1L 87
#define PMNO_JUMPATK2A 88
#define PMNO_JUMPATK1 89
#define PMNO_JUMPATK2 90
#define PMNO_JUMP_U 91
#define PMNO_JUMP_D 92
#define PMNO_JUMP_L 93
#define PMNO_APPROACH 94
#define PMNO_APPROACHATK 95
#define PMNO_APPROACH_ED 96
#define PMNO_SCOMBO1 97
#define PMNO_SCOMBO2 98
#define PMNO_SCOMBO3 99
#define PMNO_SCOMBO4 100
#define PMNO_SCOMBO5 101
#define PMNO_SCOMBO1A 102
#define PMNO_N_RUN 103
#define PMNO_RUN_TO_IDLE 104
#define PMNO_RUN_R 105
#define PMNO_RUN_L 106
#define PMNO_TURN_R 107
#define PMNO_TURN_B 108
#define PMNO_TURN_L 109
#define PMNO_TURN_ED 110
#define PMNO_SD_GUARD_ST 111
#define PMNO_SD_GUARD_ED 112
#define PMNO_SD_GUARD_H 113
#define PMNO_LC_GUARD_ST 114
#define PMNO_LC_GUARD_ED 115
#define PMNO_LC_GUARD_H 116
#define PMNO_AX_GUARD_ST 117
#define PMNO_AX_GUARD_ED 118
#define PMNO_AX_GUARD_H 119
#define PMNO_CAMLOCKON_MF 120
#define PMNO_CAMLOCKON_MR 121
#define PMNO_CAMLOCKON_MB 122
#define PMNO_CAMLOCKON_ML 123
#define PMNO_JUMPHATK1 124
#define PMNO_JUMPHATK1L 125
#define PMNO_SETSUMA1_D 126
#define PMNO_SETSUMA1_R 127
#define PMNO_BAD_ST 128
#define PMNO_BAD_ED 129
#define PMNO_WAIT_CLOAK 130
#define PMNO_DOWN_S 131
#define PMNO_HUUMA_KUDA 132
#define PMNO_RUN_R2 133
#define PMNO_RUN_L2 134
#define PMNO_ZEN_TO_RUN 135
#define PMNO_HUUMA_ED 136
#define PMNO_HUUMA_ST 137
#define PMNO_BAD2_ST 138
#define PMNO_BAD2_LOOP 139
#define PMNO_BAD2_ED 140
#define PMNO_RESV_8D 141
#define PMNO_RESV_8E 142
#define PMNO_RESV_8F 143
#define PMNO_SD_HCOMBO_S1 144
#define PMNO_SD_HCOMBO_S2 145
#define PMNO_SD_HCOMBO_S3 146
#define PMNO_SD_HCOMBO_S4 147
#define PMNO_SD_HCOMBO_S5 148
#define PMNO_SD_HCOMBO_L1 149
#define PMNO_SD_HCOMBO_L2 150
#define PMNO_SD_HCOMBO_L3 151
#define PMNO_SD_HCOMBO_L4 152
#define PMNO_SD_HCOMBO_L5 153
#define PMNO_LC_HCOMBO_1 154
#define PMNO_LC_HCOMBO_2 155
#define PMNO_LC_HCOMBO_3 156
#define PMNO_LC_HCOMBO_4 157
#define PMNO_LC_HCOMBO_5 158
#define PMNO_LC_HCOMBO_6 159
#define PMNO_AX_HCOMBO_S1 160
#define PMNO_AX_HCOMBO_S2 161
#define PMNO_AX_HCOMBO_S3 162
#define PMNO_AX_HCOMBO_S4 163
#define PMNO_AX_HCOMBO_L1 164
#define PMNO_AX_HCOMBO_L2 165
#define PMNO_AX_HCOMBO_L3 166
#define PMNO_AX_HCOMBO_L4 167
#define PMNO_R_SD_SHOT 168
#define PMNO_R_GUN_SHOT 169
#define PMNO_R_MAGIC 170
#define PMNO_R_JIGENKIRI 171
#define PMNO_R_GROUND_S 172
#define PMNO_R_GROUND_L 173
#define PMNO_R_GROUND_E 174
#define PMNO_R_SDDASH_S 175
#define PMNO_R_SDDASH_L 176
#define PMNO_R_SDDASH_E 177
#define PMNO_R_SDDASH_T 178
#define PMNO_R_MAGIC2 179
#define PMNO_R_MAGIC3 180
#define PMNO_R_MAGIC4 181
#define PMNO_R_MAGIC5 182
#define PMNO_R_MAGIC6 183
#define PMNO_RESV_B8 184
#define PMNO_RESV_B9 185
#define PMNO_LOOK_R_IN 186
#define PMNO_LOOK_R_LOOP 187
#define PMNO_LOOK_L_IN 188
#define PMNO_LOOK_L_LOOP 189
#define MAPHIT 33.3

typedef enum {
    SBTLSKL_KAJA_TARUKAJA = 0,
    SBTLSKL_KAJA_MAKAKAJA = 1,
    SBTLSKL_KAJA_RAKUKAJA = 2,
    SBTLSKL_KAJA_MAX = 3,
} SBTLSKL_KAJA;

typedef struct DEVILDATA_WORK DEVILDATA_WORK;
typedef struct SBTLITEM_WORK SBTLITEM_WORK;
typedef struct SBTLUNIT_LISTWORK SBTLUNIT_LISTWORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;

extern s32 *sbtlmotion_tbl[32];
extern s32 g_DbgCnt;
extern s32 step;
extern s32 stepcnt;
extern s32 player_theworld_cng;
extern s32 nakama0_theworld_cng;
extern s32 nakama1_theworld_cng;
extern f32 distance_r;

bool sBtlDeleteEnemy(SBTLUNIT_WORK *wk);
bool sBtlDeletePlayer(SBTLUNIT_WORK *wk);
bool sBtlSetSummon_Unit(SBTLUNIT_WORK *wklock, s32 point, u32 addst, s8 flg, const sdfVector4_t *pos, s8 stflg, bool theworld_on);
void sBtlStatusBitOn(SBTLUNIT_WORK *wk, SBTLUNIT_ST st);
void sBtlStatusBitOff(SBTLUNIT_WORK *wk, SBTLUNIT_ST st);
bool sBtlCheckModelDataLoadEnd(SBTLUNIT_WORK *wk);
bool Init(s8 flg);
void sBtlSetEndBadStatus(void);
bool sBtlSetEndData(void);
bool Exit(void);
void sBtlResetBadStatus_Stock(void);
void sBtlResetGetureiViceFlag_Stock(void);
void sBtlResetMenuCursor_Stock(void);
bool sBtlSetDisp(SBTLUNIT_WORK *wk, s8 flg);
bool Draw(void);
SBTLUNIT_LISTWORK *sBtlCreateUnitList(s32 number);
SBTLUNIT_WORK *sBtlSearchUnit_ID(SBTLUNIT_LISTWORK *lwk, s32 ID);
SBTLUNIT_WORK *sBtlSearchUnit_GroupID(SBTLUNIT_LISTWORK *lwk, s32 serialID);
bool sBtlSearchUnit_Nakama(SBTLUNIT_WORK *wk);
s32 sBtlGetNumUnit_GroupID(SBTLUNIT_LISTWORK *lwk, s32 serialID);
s32 sBtlGetNumUnit_GroupID2(SBTLUNIT_LISTWORK *lwk, s32 serialID, s32 flg);
bool sBtlClearUnitList(SBTLUNIT_LISTWORK *wk);
bool sBtlDeleteUnitList(SBTLUNIT_LISTWORK *wk, bool _destroy);
s32 sBtlEntryUnitList(SBTLUNIT_LISTWORK *lwk, SBTLUNIT_WORK *wk);
s32 sBtlReleaseUnitList(SBTLUNIT_LISTWORK *lwk, SBTLUNIT_WORK *wk);
SBTLUNIT_WORK *sBtlCreateUnit(MODELTYPE major, s32 minor, SBTLUNIT_MODE mode);
bool sBtlDeleteUnit_UnWork(SBTLUNIT_WORK *wk);
bool sBtlCheckReturn_Unit(SBTLUNIT_WORK *wk);
bool sBtlSearchReturn_Unit(SBTLUNIT_WORK *wklock);
bool sBtlDeleteUnit(SBTLUNIT_WORK *wk);
bool sBtlCheckSearchUnit_MMD(SBTLUNIT_WORK *wk);
bool sBtlMutekiProc(SBTLUNIT_WORK *wk);
void sBtlResetMutekiColor(SBTLUNIT_WORK *wk);
bool sBtlResetColor_Select(void);
bool sBtlSetColor_Select(SBTLUNIT_WORK *wk, u32 abgr);
bool sBtlSetColor_PNL(u32 abgr);
bool sBtlResetColor_PNL(u32 abgr);
void sBtlResetModelColor(SBTLUNIT_WORK *wk);
void sBtlSetChangeModelColor(SBTLUNIT_WORK *wk, u32 rgba);
void sBtlSetChangeModelColor_DST(SBTLUNIT_WORK *wk, u32 src, u32 dst, f32 ratio);
bool sBtlChangeModelColor(SBTLUNIT_WORK *wk);
bool sBtlChangeModelColor_DST(SBTLUNIT_WORK *wk);
void sBtlResetModelColor_DST(SBTLUNIT_WORK *wk);
void sBtlSetModelColorChroma(SBTLUNIT_WORK *wk, u32 rgba);
bool sBtlChangeModelData(SBTLUNIT_WORK *wk);
bool CheckMapHit(SBTLUNIT_WORK *wk, const sdfVector4_t *oldpos);
s32 sBtlCheckMapHit_Data(f32 _OldX, f32 _OldZ, f32 posx, f32 posz, f32 *px, f32 *pz);
void sBtlSetMapDistacne(f32 x, f32 z);
void sBtlSetMapDistacneR(f32 r);
bool sBtlCheckMapHit_Cross(const sdfVector4_t *pos0, const sdfVector4_t *ppos, f32 dis);
bool sBtlGetHitPos(const sdfVector4_t *pos0, const sdfVector4_t *ppos, f32 *posX, f32 *posZ);
void sBtlGetRotate(SBTLUNIT_WORK *wk, const sdfVector4_t *pos);
void sBtlGetRotate_Kaihi(SBTLUNIT_WORK *wk, const sdfVector4_t *pos);
void sBtlCheckRotSpd(SBTLUNIT_WORK *wk, const sdfVector4_t *pos);
bool sBtlCheckNoDmgYure(SBTLUNIT_WORK *wk);
bool UnitMV(SBTLUNIT_WORK *wk);
void UnitMV_To_Basic(SBTLUNIT_WORK *wk);
void sBtlUpdateUnitJumpOfsPos(SBTLUNIT_WORK *wk);
bool sBtlCheckMotionNo(SBTLUNIT_WORK *wk, SBTLUNIT_MOTION no);
bool sBtlCheckMotionEnd(SBTLUNIT_WORK *wk);
bool sBtlCheckMotionEnd_AnimatorNormal(SBTLUNIT_WORK *wk);
void sBtlCheckGuardMotion(SBTLUNIT_WORK *wk);
bool sBtlRestartMotion(SBTLUNIT_WORK *wk);
bool sBtlCheckMotionID(SBTLUNIT_WORK *wk, SBTLUNIT_MOTION motionno);
bool sBtlSetMotion_ID(SBTLUNIT_WORK *wk, s32 id, s32 bframe, s32 aframe, s8 flg);
s32 sBtlGetMotionNo(SBTLUNIT_WORK *wk, SBTLUNIT_SIDE side, SBTLUNIT_MOTION motionno);
void sBtlResetAtkSklEff(SBTLUNIT_WORK *wk);
bool sBtlSetMotion(SBTLUNIT_WORK *wk, SBTLUNIT_MOTION setmotionno, s32 bframe, s32 aframe, s8 flg);
bool sBtlIsDying(SBTLUNIT_WORK *wk);
bool sBtlCutMotion(SBTLUNIT_WORK *wk, f32 m_rate);
bool sBtlSetFade(SBTLUNIT_WORK *wk, SBTLUNIT_VST flg, s32 start, s32 count, s32 para);
bool sBtlFadeProc(SBTLUNIT_WORK *wk);
SBTLUNIT_LISTWORK *sBtlCreateTargetList_MASK(SBTLUNIT_SIDE side, SBTLUNIT_ST mask, SBTLUNIT_VST mask_v);
SBTLUNIT_LISTWORK *sBtlCreateTargetList_AI(SBTLUNIT_SIDE side);
SBTLUNIT_LISTWORK *sBtlCreateTargetList(SBTLUNIT_SIDE side);
SBTLUNIT_LISTWORK *sBtlCreateTargetList_DeadOn(SBTLUNIT_SIDE side);
s32 sBtlCreateTargetList_ALLHIT(void);
SBTLUNIT_LISTWORK *sBtlCreateTargetList_Talk(SBTLUNIT_SIDE side);
SBTLUNIT_LISTWORK *sBtlCreateTargetList_Analyze(SBTLUNIT_SIDE side);
SBTLUNIT_LISTWORK *sBtlCreateTargetList_Group(SBTLUNIT_SIDE side, s32 GroupID);
SBTLUNIT_LISTWORK *sBtlCreateTargetList_PForward(SBTLUNIT_SIDE side);
void sBtlUpdateMiusinai(SBTLUNIT_WORK *wk);
bool sBtlCheckDamageTargetTemp(SBTLUNIT_WORK *wk);
bool sBtlCheckDamageTarget(SBTLUNIT_WORK *wk);
bool sBtlCheckDamageTarget_FastLoadNakama(SBTLUNIT_WORK *wk);
bool sBtlCheckDamageTargetUseItem(SBTLUNIT_WORK *wk);
bool CheckLiveTarget(SBTLUNIT_WORK *wk);
bool sBtlCheckLiveTarget_NotHitDmg(SBTLUNIT_WORK *wk);
bool sBtlCheckLiveTarget_NotHitDmg_Kakusi(SBTLUNIT_WORK *wk);
bool sBtlCheckLiveTarget2(SBTLUNIT_WORK *wk);
bool sBtlCheckTalkSelectTarget(SBTLUNIT_WORK *wk);
bool sBtlCheckTateSkillSelectTarget(SBTLUNIT_WORK *wk);
bool sBtlCheckExist(SBTLUNIT_WORK *wk);
bool sBtlCheckExist2(SBTLUNIT_WORK *wk);
SBTLUNIT_WORK *sBtlSearchHitHelper_ID(SBTLUNIT_WORK *wk, s32 id, s32 max);
bool sBtlCreateHitHelper(SBTLUNIT_WORK *wk, s32 devilid, s32 count);
void sBtlResetHelperHit(SBTLUNIT_WORK *wk);
void sBtlSetHelperHit(SBTLUNIT_WORK *wk);
bool sBtlGetHelperPos(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, s32 devilid);
bool sBtlDeleteHitHelper(SBTLUNIT_WORK *wk);
bool sBtlSetItem(SBTLUNIT_WORK *wk);
bool sBtlItem_CheckSetItem(SBTLITEM_WORK *item, const sdfVector4_t *pos);
void sBtlDlcBtl_SetItemu(s32 _dlcNum, DEVILDATA_WORK *_data);
bool sBtlDlcZakuroBtl_SetItem(void);
s32 sBtlCheckSummonUnit_Exist2(s32 idx);
s32 sBtlCheckSummonUnit_Dead_or_ALive(s32 idx);
s32 sBtlCheckSummonUnit_Exist(s32 idx);
s32 sBtlCheckSummonUnit(void);
s32 sBtlGetStockPoint(void);
bool sBtlEntryStockData_Huuma(void);
s32 sBtlEntryStockData(s32 devilid);
SBTLUNIT_WORK *sBtlSetSummon_E(MODELTYPE major, s32 minor, s32 groupid, s32 id);
SBTLUNIT_WORK *sBtlResetSummon(s32 index, s32 flg);
SBTLUNIT_WORK *sBtlSetSummon(MODELTYPE major, s32 minor, s32 index, s32 flg);
bool SetReturn(s32 index, s32 flg);
bool sBtlResetSummon_E(SBTLUNIT_WORK *wk);
void sBtlResetAction_Flag(SBTLUNIT_WORK *wk);
bool ResetAction(SBTLUNIT_WORK *wk, s8 flg);
bool sBtlCreateEnemyList(void);
SBTLUNIT_LISTWORK *sBtlCreateSideList_AI(SBTLUNIT_SIDE side, s32 flg);
SBTLUNIT_LISTWORK *sBtlCreateSideList(SBTLUNIT_SIDE side, s32 flg);
bool sBtlCheckLoopMotion(SBTLUNIT_WORK *wk, SBTLUNIT_MOTION no);
void sBtlStartSlowMotion(SBTLUNIT_WORK *wk, f32 _Spd);
void sBtlEndSlowMotion(SBTLUNIT_WORK *wk);
bool sBtlChkSlowMotion(SBTLUNIT_WORK *wk, f32 *_MSlow_Speed);
void sBtlSetMotionHitStop(SBTLUNIT_WORK *wk, f32 _Spd, f32 _Time, f32 _StFrame);
void sBtlSetEffectHitStop(SBTLUNIT_WORK *wk, f32 _Spd, f32 _Time, f32 _StTime);
void sBtlClrCtrl(s32 pRes, s32 tgt, s32 bgn, s32 frm);
dds3ProcessFunc_t Proc(dds3ProcessID_t *id);
bool sBtlCheckUnit_Exec_R(void);
bool sBtlCheckUnit_Exec(void);
bool sBtlModelDataLoad(SBTLUNIT_WORK *wk);
void sBtlCheckBossSE(SBTLUNIT_WORK *wk);
bool sBtlSetModelDataLoadEnd(SBTLUNIT_WORK *wk);
s32 sBtlGetLight_SetPos(SBTLUNIT_WORK *wk, s8 lightno);
s32 sBtlSetLight_SetPos(SBTLUNIT_WORK *wk, s8 lightno);
bool sBtlSetUnitLight_Dir(SBTLUNIT_WORK *wk, const sdfVector4_t *dir, s32 flg);
bool sBtlSetUnitLight(SBTLUNIT_WORK *wk, s32 time, u32 diffuse, u32 ambient, s32 flg, s32 flg2);
bool sBtlSetLight_Map(SBTLUNIT_WORK *wk, s32 time, s32 flg);
bool sBtlCheckMotionMove(SBTLUNIT_WORK *wk);
s32 sBtlReleaseUnitList_ID(SBTLUNIT_LISTWORK *lwk, s32 id);
s32 UnitRegist(MODELTYPE major, s32 minor);
s32 sBtlGetPlayerMinor(SBTL_MODE btlMode, SBWEAPON_TYPE weaponType);
bool sBtlSetPlayerData(s8 flg);
void UnitSetPlayerSprit(SBTLUNIT_WORK *_playerUnit);
SBTLUNIT_WORK *sBtlGetPlayer_HitTarget(void);
bool sBtlIsDeadBgn(SBTLUNIT_WORK *wk);
bool sBtlIsDeadBgn_2(SBTLUNIT_WORK *wk);
void sBtlSetRunAway(SBTLUNIT_WORK *wk);
bool sBtlSetReturnStock_Enemy(SBTLUNIT_WORK *wk);
void sBtlBgnWait(SBTLUNIT_WORK *wk);
void sBtlEndWait(SBTLUNIT_WORK *wk);
void sBtlBgnWaitALL(SBTLUNIT_WORK *wk);
void sBtlBgnWait_TimeStopSkill(SBTLUNIT_WORK *wk, s32 flg);
void sBtlBgnWaitALL_TimeStopSkill(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wk2);
void sBtlEndWaitALL(SBTLUNIT_WORK *wk, s32 after_waza);
SKLID sBtlChkHaveMemSkl(sdatUnitWork_t *pUnit, AUTO arg);
s32 sBtlChkHaveMemSklParty(s32 arg);
f32 sBtlGetKajaParamEx(SBTLUNIT_WORK *wk, SBTLSKL_KAJA kajatype, s32 *pCount);
f32 sBtlGetKajaParam(SBTLUNIT_WORK *wk, SBTLSKL_KAJA kajatype);
u32 sBtlCheckKajaAnyEx(SBTLUNIT_WORK *wk, s32 *pCount);
u32 sBtlCheckKajaAny(SBTLUNIT_WORK *wk);
s32 sBtlCheckEnableUseKaja(SBTLUNIT_WORK *wk, SKLID skillid);
s32 sBtlCheckEnableUseKajaNewAI(SBTLUNIT_WORK *wk, SKLID skillid);
s32 sBtlCheckEnableUseKarn(SBTLUNIT_WORK *wk, SKLID skillid);
s32 sBtlCheckEnableUseAura(SBTLUNIT_WORK *wk, SKLID skillid);
s32 sBtlGetAuraIdx(SKLID skillid);
s32 sBtlCheckEnableUseSkill(SBTLUNIT_WORK *wk, SKLID skillid);
void sBtlResetBtlMagicStatus(SBTLUNIT_WORK *wk);
SBTLUNIT_SIDE sBtlGetBothSide(SBTLUNIT_WORK *wk, SBTLUNIT_SIDE side);
bool sBtlUnit_CheckSummon_LoadExecOk_sub(void);
bool sBtlCheckSummon_LoadExecOk(s32 mode);
SBTLUNIT_WORK *sBtlGetNakamaUnit(sdatUnitWork_t *a_pUnit);
void GetUnitHelperPos(SBTLUNIT_WORK *wk, sdfVector4_t *_HelperPos);
void sBtlGetUnitHelperPosSub(SBTLUNIT_WORK *wk, sdfVector4_t *_HelperPos, s32 markpos_no);
void sBtlGetUnitTargetPos(SBTLUNIT_WORK *wk, sdfVector4_t *_HelperPos);
void sBtlGetUnitDamagePos(SBTLUNIT_WORK *wk, sdfVector4_t *_HelperPos);
bool sBtlChkEnemyID(s32 _DevilID);
SBTLUNIT_WORK *sBtlGetUnitFromDevilID(s32 _DevilID);
SBTLUNIT_WORK *sBtlGetUnitEnemy1_Live(void);
SBTLUNIT_WORK *sBtlGetUnitEnemy1(void);
void sBtlResetJump_FO_Eve(SBTLUNIT_WORK *wk);
bool sBtlChkBounceUnit(SBTLUNIT_WORK *wk);
void sBtlSetBounce(SBTLUNIT_WORK *wk, f32 _Pow, f32 _AddRndNml, s32 _ReBound);
void sBtlSetBounceHitStop(SBTLUNIT_WORK *wk, s32 _WaitFrame, s32 _StopFrame);
bool sBtlChkSceneEnemyLive(void);
bool sBtlChkNakama_SkillUse_SHINEBA(void);
