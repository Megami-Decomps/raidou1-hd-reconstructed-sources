#pragma once
#include "types.h"
#include "BST.h"

typedef struct SBTLPNL_PARADATA SBTLPNL_PARADATA;

struct SBTLPNL_PARADATA {
    s32 p_hp;
    s32 p_maxhp;
    s32 mag;
    s32 maxmag;
    s32 playerID;
    BST p_badstauts;
    s32 l_target_devilid;
    s8 vice_level;
    s32 bullet;
    s32 bullet_num;
    s32 n_devilid;
    s32 nakamaid;
    s32 n_hp;
    s32 n_maxhp;
    s32 n_mp;
    s32 n_maxmp;
    BST n_badstatus;
    s32 haveskill[19];
    s32 n_devilid2;
    s32 nakamaid2;
    s32 n_hp2;
    s32 n_maxhp2;
    s32 n_mp2;
    s32 n_maxmp2;
    BST n_badstatus2;
    s32 haveskill2[19];
};
