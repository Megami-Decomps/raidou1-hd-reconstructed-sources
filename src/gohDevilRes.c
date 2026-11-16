#include "types.h"
#include "SKLID.h"
#include "cmdevilresps2_cs.h"
#include "gohdevilres.h"

typedef struct DEVILDATA_WORK DEVILDATA_WORK;

// 0x1b9c5f0
bool CreateInstance(void) {
  return CreateInstance("", "", 0);
}

// 0x1b9c640
void DestroyInstance(void) {
  DestroyInstance();
}

// 0x1b9c650
bool gohIsInstance(void) {
  return IsInstance(0);
}

// 0x1b9c660
void gohSetup(void) {
  (s_pcInst->klass->vtable._6_Setup.methodPtr)(s_pcInst, s_pcInst->klass->vtable._6_Setup.method);
}

// 0x1b9c6c0
s32 gohGetDevilMax(void) {
  return (s_pcInst->klass->vtable._7_GetDevilMax.methodPtr)(s_pcInst, s_pcInst->klass->vtable._7_GetDevilMax.method);
}

// 0x1b9c720
s32 gohGetNakamaTop(void) {
  return (s_pcInst->klass->vtable._8_GetNakamaTop.methodPtr)(s_pcInst, s_pcInst->klass->vtable._8_GetNakamaTop.method);
}

// 0x1b9c780
s32 gohGetNakamaMax(void) {
  return (s_pcInst->klass->vtable._9_GetNakamaMax.methodPtr)(s_pcInst, s_pcInst->klass->vtable._9_GetNakamaMax.method);
}

// 0x1b9c7e0
DEVILDATA_WORK *gohGetDevilDataTable(s32 iNo) {
  return ((DEVILDATA_WORK *(CMDevilResPs2 *, u64, const MethodInfo *))s_pcInst->klass->vtable._11_GetDevilDataTable.methodPtr)(s_pcInst, iNo, s_pcInst->klass->vtable._11_GetDevilDataTable.method);
}

// 0x1b9c840
char *gohGetRaceName(s32 iNo) {
  return ((char *(CMDevilResPs2 *, u64, const MethodInfo *))s_pcInst->klass->vtable._13_GetRaceName.methodPtr)(s_pcInst, iNo, s_pcInst->klass->vtable._13_GetRaceName.method);
}

// 0x1b9c8a0
char *gohGetSeireiName(s32 iNo) {
  return ((char *(CMDevilResPs2 *, u64, const MethodInfo *))s_pcInst->klass->vtable._14_GetSeireiName.methodPtr)(s_pcInst, iNo, s_pcInst->klass->vtable._14_GetSeireiName.method);
}

// 0x1b9c900
char *gohGetMitamaName(s32 iNo) {
  return ((char *(CMDevilResPs2 *, u64, const MethodInfo *))s_pcInst->klass->vtable._15_GetMitamaName.methodPtr)(s_pcInst, iNo, s_pcInst->klass->vtable._15_GetMitamaName.method);
}

// 0x1b9c960
char *gohGetDevilName(s32 iNo) {
  return ((char *(CMDevilResPs2 *, u64, const MethodInfo *))s_pcInst->klass->vtable._16_GetDevilName.methodPtr)(s_pcInst, iNo, s_pcInst->klass->vtable._16_GetDevilName.method);
}

// 0x1b9c9c0
char *gohGetSkillName(s32 iNo) {
  return ((char *(CMDevilResPs2 *, u64, const MethodInfo *))s_pcInst->klass->vtable._17_GetSkillName.methodPtr)(s_pcInst, iNo, s_pcInst->klass->vtable._17_GetSkillName.method);
}

// 0x1b9ca20
char *gohGetSousaSkillName(s32 iNo) {
  return ((char *(CMDevilResPs2 *, u64, const MethodInfo *))s_pcInst->klass->vtable._18_GetSousaSkillName.methodPtr)(s_pcInst, iNo, s_pcInst->klass->vtable._18_GetSousaSkillName.method);
}

// 0x1b9ca80
bool gohIsSkillForm(s32 iDevilNo, SKLID iSkillNo) {
  return (s_pcInst->klass->vtable._26_IsSkillForm.methodPtr)(s_pcInst, iDevilNo, iSkillNo, s_pcInst->klass->vtable._26_IsSkillForm.method);
}

// 0x1b9caf0
u32 gohGetOmoideSkillCnt(void) {
  return s_pcInst->m_uOmoideSkillCnt;
}

// 0x1b9cb40
SKLID gohGetOmoideSkill2SkillNo(s32 iOmoideSkillNo) {
  return GetOmoideSkill2SkillNo(s_pcInst, iOmoideSkillNo, 0);
}

// 0x1b9cba0
s32 gohGetSkill2OmoideSkillNo(s32 iSkillNo) {
  return GetSkill2OmoideSkillNo(s_pcInst, iSkillNo, 0);
}

// 0x1b9cc00
s32 gohGetSkillSpiritSkillNo(s32 iSkillNo) {
  return GetSkillSpiritSkillNo(s_pcInst, iSkillNo, 0);
}

// 0x1b9cc60
s32 gohGetRaidouSkillNo(s32 iSkillNo) {
  return GetRaidouSkillNo(s_pcInst, iSkillNo, 0);
}

// 0x1b9ccc0
void gohSetupDevilList(void) {
  Init(s_pcInst->m_cRaceSort, 0);
}
