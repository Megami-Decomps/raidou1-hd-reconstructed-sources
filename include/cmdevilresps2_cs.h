#pragma once
#include "types.h"
#include "SKLID.h"

typedef struct CMDevil CMDevil;
typedef struct CMDevilRaceAssociate CMDevilRaceAssociate;
typedef struct CMDevilResPs2 CMDevilResPs2;
typedef struct CMRaceSort CMRaceSort;
typedef struct SMHitokotoMsgTbl SMHitokotoMsgTbl;
typedef struct SMRaidouSkillEx SMRaidouSkillEx;
typedef struct SMSkillEx SMSkillEx;
typedef struct SMSpiritSkillEx SMSpiritSkillEx;
typedef struct SMWeaponEx SMWeaponEx;

struct SMHitokotoMsgTbl {
    u8 m_uStanceBit;
    u16 m_uKucyouBit;
};

struct CMDevil {
    s32 m_iDevilNo;
    s32 m_spDevilNo;
    SMHitokotoMsgTbl *s_sHitokotoMsgTbl[28];
};

struct CMDevilRaceAssociate {
    CMDevil *m_cDevil;
};

struct SMWeaponEx {
    u8 m_iKindNo;
    u8 m_iBaseSwordCnt;
    u8 m_uNewSwordCnt;
    u8 m_auNewSwordNo[4];
};

struct SMSkillEx {
    u8 m_iOmoideSkillNo;
};

struct SMSpiritSkillEx {
    u8 m_iSpritSkillNo;
};

struct SMRaidouSkillEx {
    u8 m_iRaidouSkillNo;
};

struct CMDevilResPs2 {
    bool InstanceFieldsInitialized;
    char *m_szNull;
    CMRaceSort *m_cRaceSort;
    SMWeaponEx *m_asWeapon;
    u16 m_uOmoideSkillCnt;
    SKLID *m_aOmoideSkill;
    SMSkillEx *m_aSkill;
    SMSpiritSkillEx *sMSpiritSkillExList;
    SKLID *m_aSpiritSkill;
    u16 m_uSpiritSkillCnt;
    SMRaidouSkillEx *sMRaidouSkillExList;
    SKLID *m_aRaidouSkill;
    u16 m_uRaidouSkillCnt;
};

struct CMRaceSort {
    s32 m_iListCnt;
    CMDevilRaceAssociate *m_pcList;
    void *m_cSort;
};

extern CMDevilResPs2 *s_pcInst;
