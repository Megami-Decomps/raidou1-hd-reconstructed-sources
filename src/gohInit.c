#include "types.h"
#include "cmpomoide.h"
#include "cmpraidouskill.h"
#include "cmpstatus.h"
#include "dat.h"
#include "dds3adminiprocess.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "evtbit.h"
#include "evtmoon.h"
#include "evtpmv.h"
#include "evtviewer.h"
#include "fclmisc.h"
#include "fclmsg.h"
#include "fld.h"
#include "goh.h"
#include "gohaccident.h"
#include "gohaccidentfail.h"
#include "gohcalc.h"
#include "gohcombinetbl.h"
#include "gohcombunity.h"
#include "gohdevilres.h"
#include "gohdraw.h"
#include "gohinit.h"
#include "gohmain.h"
#include "gohmenu.h"
#include "gohnotdupliskill.h"
#include "gohrenken.h"
#include "gohswordhistory.h"
#include "jmscmdmenu.h"
#include "jmsmisc.h"
#include "kernel.h"
#include "mdl.h"
#include "mdl_check.h"
#include "raijindlc.h"
#include "sbtlweapon.h"
#include "scr.h"
#include "scrcommand.h"
#include "sdfmem.h"
#include "sdfsound.h"
#include "shpmain.h"
#include "sndat3.h"

#define GOH_KUCYO_MSG_UNIT 7
#define GOH_BIRTH_MSG_UNIT 3
#define BG_WAIT_UNITY 5
#define ST_WAIT_UNITY 16
#define GOH_CALC_PROCESS_NAME "gohmaden_calc"
#define GOH_DRAW_PROCESS_NAME "gohmaden_draw"
#define GOH_UPDT_PROCESS_NAME "gohmaden_updt"
#define GOH_ALWAYS_DRAW_PROCESS_NAME "gohmaden_always_draw"
#define GOH_MSG_FILENAME "goh_mes.bmd"
#define GOH_EVT_SCR_FILENAME "goh_evt.bf"
#define GOH_EVT2_SCR_FILENAME "goh_evt2.bf"
#define GOH_MODEL_MAJOR 3
#define GOH_TALK_SCR_FILENAME "goh_talk.bf"
#define GOH_SINAN_SCR_FILENAME "goh_sinan.bf"
#define GOH_SCR_FILENAME "gohmaden.bf"

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct gohData_t gohData_t;
typedef struct gohTable_t gohTable_t;
typedef struct sprHandle_t sprHandle_t;

void *debugSetting;
void *animChengeTbl;
char *gohAssetName;
char *gohDebugAssetName;
s32 *c_iDevilTbl;
dds3ProcessID_t *GlobalPID;
dds3ProcessID_t *GlobalDrawPID;
s32 gCallFromMenu;

// macros
// 0x1bb5bd0: s32 RENKEN_ERR_CHK(void)
static inline s32 RENKEN_ERR_CHK(void) {
  s16 *ProcessData;
  s32 v4;
  s32 v5;
  s32 v7;

  if (!GlobalPID)
  {
    v4 = 0;
    v5 = 0;
    goto LABEL_16;
  }
  ProcessData = dds3GetProcessData(GlobalPID);
  if (!ProcessData)
  v5 = ProcessData[179];
  v4 = ProcessData[180];
LABEL_16:
  v7 = gohCheckComposition(v4, v5);
  scrSetIntReturnValue(v7);
  return 1;
}

// 0x1bb1110
dds3ProcessID_t *gohDebugProcessStart(void) {
  dds3ProcessID_t *v1;
  void *Asset;
  s64 naturalAligment;
  void *v8;
  void *v10;
  s64 v12;
  s32 i;
  s64 v16;
  void *debugFlagSetting;
  s32 Item;
  s32 v21;
  s32 *v23;
  s32 v26;
  s32 v28;
  s32 *v29;
  s32 v30;
  s32 *v31;
  s32 v32;
  s32 *v33;
  s32 v34;
  s32 *v35;
  s32 v36;
  s32 *v37;
  s32 v38;
  s32 *v39;
  s32 v40;
  s32 *v41;
  s32 v42;
  s32 *v43;
  s32 v44;
  s32 *v45;
  s32 v46;
  s32 *v47;
  s32 v48;
  s32 *v49;
  s32 v50;
  s32 *v51;
  s32 v52;
  s32 *v53;
  s32 v54;
  s32 *v55;
  s32 v56;
  s32 *v57;
  s32 v58;
  s32 *v59;
  s32 v60;
  s32 *v61;
  s32 v62;
  s32 *v63;
  s32 v64;
  s32 *v65;
  s32 v66;
  s32 *v67;
  s32 v68;
  s32 *v69;
  s32 v70;
  s32 *v71;
  s32 v72;
  s32 *v73;
  s32 *v74;
  Il2CppObject *ProcessData;
  s32 size;
  sdatPlayerUnitWork_t *player;
  u32 v83;
  s32 v84;
  u32 v85;
  void *v87;
  s32 v88;
  s32 v92;
  s32 v93;
  void *v95;
  void *addDevil;
  s32 v97;
  s32 StockDevilIndex;
  s32 v99;
  sdatUnitWork_t *v103;
  void *v104;
  SKLID *aRsvSkl;
  s64 v106;
  s64 v107;
  s32 v108;
  il2cpp_array_size_t max_length;
  s64 v110;
  s64 v111;
  s32 v112;
  s32 v116;
  s32 iOmoideSkillCnt;
  s32 omoideCnt;
  Il2CppObject *v121;
  sdatPlayerUnitWork_t *v122;
  il2cpp_array_size_t v124;
  s64 v125;
  s64 v126;
  s32 v127;
  s32 v131;
  il2cpp_array_size_t v134;
  s64 v135;
  s64 v136;
  s32 v137;
  s32 v141;
  s32 spiritCnt;
  s32 spiritNum;
  s32 level;
  s32 raidouLvNum;
  s32 addMoneyNum;
  s32 m;
  u32 j;
  sdatUnitWork_t *v156;
  s32 k;
  s32 *EventBit;
  s32 *v160;
  Il2CppObject *v161;
  dds3ProcessID_t *id;

  v1 = Allocate(dds3ProcessID_t);
  _ctor(v1, 0);
  id = gohProcessStart(1);
  Load(Dependent, gohDebugAssetName, gohDebugAssetName);
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  Asset = LoadAsset(_Ctrl_k__BackingField, gohDebugAssetName, "GohDebugInitSetting", 0);
  if (Asset)
  {
    if (Asset->klass->_2.naturalAligment >= (u32)naturalAligment)
    {
      if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == GohDebugInitSetting)
        v8 = Asset;
      else
        v8 = 0;
    }
    else
    {
      v8 = 0;
    }
    debugSetting = v8;
    if (Asset->klass->_2.naturalAligment >= (u32)v12)
    {
      if (Asset->klass->_2.typeHierarchy[v12 - 1] == GohDebugInitSetting)
        v10 = Asset;
      else
        v10 = 0;
    }
    else
    {
      v10 = 0;
    }
  }
  else
  {
    v10 = 0;
    debugSetting = 0;
  }
  Unload(Dependent, gohDebugAssetName, 0);
  if (!debugSetting->gohAllDebugSetting)
    return id;
  for (i = 0; ; ++i)
  {
    debugFlagSetting = debugSetting->debugFlagSetting;
    if (i >= debugFlagSetting->_size)
      break;
    debugFlagSetting = debugSetting->debugFlagSetting;
    Item = _get_Item(debugFlagSetting, i);
    if (Item)
    {
      if ((u32)(Item - 2618) >= 0xFFFFFFC6)
        evtBitKityouItemAdd(Item);
      v16 = (s64)GBWK->EventBit + 4 * (Item / 32);
      *(u32 *)(v16 + 32) |= 1 << Item;
    }
  }
  v21 = (u8)byte_5755E7A;
  if (!debugSetting->renkenEvent)
    goto LABEL_55;
  if (v21)
  {
    goto LABEL_48;
  }
  else
  {
    goto LABEL_48;
  }
LABEL_48:
  v23 = &GBWK->EventBit[73];
  *v23 |= 0x8000u;
  goto LABEL_50;
LABEL_55:
  if (v21)
  {
    goto LABEL_57;
  }
  else
  {
LABEL_57:
    v28 = 1;
  }
  EventBit = GBWK->EventBit;
  EventBit[2] |= 2u;
  if (v28)
  {
    goto LABEL_373;
  }
  else
  {
  }
LABEL_373:
  v160 = &GBWK->EventBit[72];
  *v160 |= 0x10000u;
LABEL_50:
  if (debugSetting->allEvtDevil)
  {
    v26 = 1;
    v29 = GBWK->EventBit;
    v29[72] |= 0x100000u;
    if (v26)
    {
      goto LABEL_64;
    }
    else
    {
LABEL_64:
      v30 = 1;
    }
    v31 = GBWK->EventBit;
    v31[72] |= 0x200000u;
    if (v30)
    {
      goto LABEL_69;
    }
    else
    {
LABEL_69:
      v32 = 1;
    }
    v33 = GBWK->EventBit;
    v33[72] |= 0x400000u;
    if (v32)
    {
      goto LABEL_74;
    }
    else
    {
LABEL_74:
      v34 = 1;
    }
    v35 = GBWK->EventBit;
    v35[72] |= 0x800000u;
    if (v34)
    {
      goto LABEL_79;
    }
    else
    {
LABEL_79:
      v36 = 1;
    }
    v37 = GBWK->EventBit;
    v37[72] |= 0x1000000u;
    if (v36)
    {
      goto LABEL_84;
    }
    else
    {
LABEL_84:
      v38 = 1;
    }
    v39 = GBWK->EventBit;
    v39[72] |= 0x2000000u;
    if (v38)
    {
      goto LABEL_89;
    }
    else
    {
LABEL_89:
      v40 = 1;
    }
    v41 = GBWK->EventBit;
    v41[72] |= 0x4000000u;
    if (v40)
    {
      goto LABEL_94;
    }
    else
    {
LABEL_94:
      v42 = 1;
    }
    v43 = GBWK->EventBit;
    v43[72] |= 0x8000000u;
    if (v42)
    {
      goto LABEL_99;
    }
    else
    {
LABEL_99:
      v44 = 1;
    }
    v45 = GBWK->EventBit;
    v45[72] |= 0x10000000u;
    if (v44)
    {
      goto LABEL_104;
    }
    else
    {
LABEL_104:
      v46 = 1;
    }
    v47 = GBWK->EventBit;
    v47[72] |= 0x20000000u;
    if (v46)
    {
      goto LABEL_109;
    }
    else
    {
LABEL_109:
      v48 = 1;
    }
    v49 = GBWK->EventBit;
    v49[72] |= 0x40000000u;
    if (v48)
    {
      goto LABEL_114;
    }
    else
    {
LABEL_114:
      v50 = 1;
    }
    v51 = GBWK->EventBit;
    v51[72] |= 0x80000000;
    if (v50)
    {
      goto LABEL_119;
    }
    else
    {
LABEL_119:
      v52 = 1;
    }
    v53 = GBWK->EventBit;
    v53[73] |= 1u;
    if (v52)
    {
      goto LABEL_124;
    }
    else
    {
LABEL_124:
      v54 = 1;
    }
    v55 = GBWK->EventBit;
    v55[73] |= 2u;
    if (v54)
    {
      goto LABEL_129;
    }
    else
    {
LABEL_129:
      v56 = 1;
    }
    v57 = GBWK->EventBit;
    v57[73] |= 4u;
    if (v56)
    {
      goto LABEL_134;
    }
    else
    {
LABEL_134:
      v58 = 1;
    }
    v59 = GBWK->EventBit;
    v59[73] |= 8u;
    if (v58)
    {
      goto LABEL_139;
    }
    else
    {
LABEL_139:
      v60 = 1;
    }
    v61 = GBWK->EventBit;
    v61[73] |= 0x10u;
    if (v60)
    {
      goto LABEL_144;
    }
    else
    {
LABEL_144:
      v62 = 1;
    }
    v63 = GBWK->EventBit;
    v63[73] |= 0x20u;
    if (v62)
    {
      goto LABEL_149;
    }
    else
    {
LABEL_149:
      v64 = 1;
    }
    v65 = GBWK->EventBit;
    v65[73] |= 0x40u;
    if (v64)
    {
      goto LABEL_154;
    }
    else
    {
LABEL_154:
      v66 = 1;
    }
    v67 = GBWK->EventBit;
    v67[73] |= 0x80u;
    if (v66)
    {
      goto LABEL_159;
    }
    else
    {
LABEL_159:
      v68 = 1;
    }
    v69 = GBWK->EventBit;
    v69[84] |= 1u;
    if (v68)
    {
      goto LABEL_164;
    }
    else
    {
LABEL_164:
      v70 = 1;
    }
    v71 = GBWK->EventBit;
    v71[84] |= 2u;
    if (v70)
    {
      goto LABEL_169;
    }
    else
    {
LABEL_169:
      v72 = 1;
    }
    v73 = GBWK->EventBit;
    v73[84] |= 4u;
    if (v72)
    {
      goto LABEL_174;
    }
    else
    {
    }
LABEL_174:
    v74 = GBWK->EventBit;
    v74[84] |= 8u;
  }
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  size = debugSetting->addDevil->_size;
  player = GBWK->player;
  if (size > player->stock_max)
    goto LABEL_188;
LABEL_185:
  v83 = size - 1;
  v161 = ProcessData;
  if (size < 1)
    goto LABEL_220;
LABEL_191:
  if (v83 >= 0x1F)
    v83 = 31;
  v84 = 0;
  v85 = v83 + 1;
  while (1)
  {
    v87 = debugSetting;
    if (v87->sameDvl)
      goto LABEL_206;
    v87 = debugSetting;
    v88 = _get_Item(v87->addDevil, v84);
    if (datGetStockDevilIndex(v88, 0) == -1)
      goto LABEL_206;
    goto LABEL_9003;
    if (datGetStockDevilIndex(v88, 0) == -1)
    {
LABEL_206:
      if (Exists("new_devil"))
        goto LABEL_216;
      goto LABEL_9002;
      if (Exists("new_devil"))
      {
LABEL_216:
        v92 = _get_Item(debugSetting->addDevil, v84);
        datAddDevil(v92);
        goto LABEL_195;
      }
LABEL_9002:
      if (_get_Item(debugSetting->addDevil, v84) >= 496)
      {
        if (_get_Item(debugSetting->addDevil, v84) < 502)
          goto LABEL_195;
      }
      goto LABEL_216;
    }
LABEL_9003:
LABEL_195:
    if (v85 == ++v84)
      goto LABEL_220;
  }
  player = GBWK->player;
  if (size <= player->stock_max)
    goto LABEL_185;
LABEL_188:
  player = GBWK->player;
  player->stock_max = size + 5;
  v83 = size - 1;
  v161 = ProcessData;
  if (size >= 1)
    goto LABEL_191;
LABEL_220:
  v93 = 0;
  while (2)
  {
    v95 = debugSetting;
    if (v93 < v95->debugDvl->_size)
    {
      v95 = debugSetting;
      addDevil = v95->addDevil;
      if (v93 < addDevil->_size)
      {
        addDevil = debugSetting->addDevil;
        v97 = _get_Item(addDevil, v93);
        StockDevilIndex = datGetStockDevilIndex(v97, 0);
        if (StockDevilIndex == -1)
          goto LABEL_222;
        goto LABEL_9004;
        if (StockDevilIndex == -1)
        {
LABEL_222:
          ++v93;
          continue;
        }
LABEL_9004:
        v99 = StockDevilIndex;
        v103 = GBWK->player->stock_id[v99];
        v104 = debugSetting;
        if (v104->chuuseiMax)
          goto LABEL_239;
        goto LABEL_9005;
        if (v104->chuuseiMax)
LABEL_239:
          v103->chuusei = 100;
LABEL_9005:
        if (v104->rsvSkl)
        {
          aRsvSkl = v103->aRsvSkl;
          if (SLODWORD(aRsvSkl->max_length) >= 1)
          {
            v106 = 8;
            do
            {
              if (*((u32 *)&aRsvSkl->obj.klass + v106))
              {
                v108 = IndexOf_Int32Enum_(v103->haveskill, 0);
                aRsvSkl = v103->aRsvSkl;
                v103->haveskill[v108] = *((u32 *)&aRsvSkl->obj.klass + v106);
                *((u32 *)&aRsvSkl->obj.klass + v106) = 0;
              }
              v107 = v106 - 7;
              ++v106;
            }
            while (v107 < SLODWORD(aRsvSkl->max_length));
          }
        }
        if (v103 && debugSetting->allOmoide)
        {
          max_length = g_aOmoide->max_length;
          if ((s64)(max_length << 32) < 1)
            goto LABEL_270;
          v110 = 0;
          v111 = (s32)max_length;
          v112 = 1;
          do
          {
            v116 = g_aOmoide[v110];
            if (!_Contains(debugSetting->omoideRemove, v116))
            {
              datOmoideSkillSetMaster(v103, v116, 1);
            }
            v110 = v112++;
          }
          while (v111 > v110);
          goto LABEL_270;
        }
LABEL_270:
        iOmoideSkillCnt = v103->iOmoideSkillCnt;
        omoideCnt = debugSetting->omoideCnt;
        if (iOmoideSkillCnt < (s16)omoideCnt)
        {
          omoideCnt = debugSetting->omoideCnt;
          v103->iOmoideSkillCnt = omoideCnt;
        }
        goto LABEL_222;
      }
    }
    break;
  }
  v121 = v161;
  v122 = GBWK->player;
  if (v122)
  {
    if (debugSetting->allRaidou)
    {
      v124 = raidouSkillList->max_length;
      if ((s64)(v124 << 32) >= 1)
      {
        v125 = 0;
        v126 = (s32)v124;
        v127 = 1;
        do
        {
          v131 = raidouSkillList[v125];
          if (!_Contains(debugSetting->raidouRemove, v131))
          {
            datRaidouSkillSetMaster(v122, v131, 1);
          }
          v125 = v127++;
        }
        while (v126 > v125);
      }
    }
    if (debugSetting->allSpirit)
    {
      v134 = spiritList->max_length;
      if ((s64)(v134 << 32) >= 1)
      {
        v135 = 0;
        v136 = (s32)v134;
        v137 = 1;
        do
        {
          v141 = spiritList[v135];
          if (!_Contains(debugSetting->spiritRemove, v141))
          {
            SpiritSkillSetMaster(v122, v141, 1, 0);
          }
          v135 = v137++;
        }
        while (v136 > v135);
      }
    }
    spiritCnt = v122->spiritCnt;
    v121 = v161;
    spiritNum = debugSetting->spiritNum;
    if (spiritCnt >= spiritNum)
      goto LABEL_322;
    spiritNum = debugSetting->spiritNum;
    if (spiritNum <= 8)
    {
      spiritNum = debugSetting->spiritNum;
      v122->spiritCnt = spiritNum;
    }
  }
LABEL_322:
  if (debugSetting->majin)
    gohDebugMajinDead();
  level = GBWK->player->para->level;
  raidouLvNum = debugSetting->raidouLvNum;
  if (raidouLvNum <= level)
    goto LABEL_330;
  gohPlayerLevelSet(raidouLvNum);
LABEL_331:
  if (!debugSetting->allKarte)
    goto LABEL_332;
  for (j = 1; j != 544; ++j)
  {
    if (j < 0x50 || j - 337 < 0x40 || j - 496 <= 5)
    {
      v156 = Allocate(sdatUnitWork_t);
      _ctor(v156, 0);
      datCreateDevilUnit(j, v156);
      if (v156->level >= 1)
      {
        if (!_Contains(debugSetting->removeKarteDvl, j))
          (*(v121[34].klass->_1.image + 179))(v121[34].klass, v156, *((u64 *)v121[34].klass->_1.image + 180));
      }
    }
  }
LABEL_333:
  if (!debugSetting->masyoAllGet)
    goto LABEL_334;
  for (k = 272; k != 370; ++k)
  {
    datAddItem(k, 99);
  }
LABEL_335:
  addMoneyNum = debugSetting->addMoneyNum;
  goto LABEL_336;
LABEL_330:
  goto LABEL_331;
LABEL_332:
  goto LABEL_333;
LABEL_334:
  goto LABEL_335;
LABEL_336:
  datAddMoney(addMoneyNum);
  gohSetLetterCnt(debugSetting->letterCnt);
  if (debugSetting->swordAllGet)
  {
    for (m = 145; m != 244; ++m)
    {
      datAddItem(m, 1);
      gohOnSwordHave(m - 144);
      gohOnSword(m - 144);
    }
  }
  return id;
}

// 0x1bb2ec0
void gohPlayerLevelSet(s32 _lv) {
  sdatUnitWork_t *para;
  s32 PlayerExp;
  sdatPlayerUnitWork_t *player;
  sdatPlayerUnitWork_t *v8;
  sdatPlayerUnitWork_t *v9;

  para = GBWK->player->para;
  PlayerExp = datGetPlayerExp(lv);
  para->exp = PlayerExp;
  player = GBWK->player;
  datGetPlayerLevelUpUnit(player, player);
  v8 = GBWK->player;
  datCalcNowParam(v8->para, v8->swordno, 0);
  datDvlParaUpdate(0);
  datCalcMagMax();
  v9 = GBWK->player;
  v9->mag = v9->maxmag;
  v9->para->now->hp = v9->para->now->maxhp;
}

// 0x1bb2fc0
gohTable_t *gohGetTable(void) {
  gohTable_t *result;

  if (!GlobalPID)
    return 0;
  result = (gohTable_t *)dds3GetProcessData(GlobalPID);
  if (!result)
    return result;
  return *(gohTable_t *)&result[2].AccidentDevilSize;
}

// 0x1bb3110
sprHandle_t *gohGetSpriteHandle(void) {
  if (!GlobalPID)
    return 0;
  dds3GetProcessData(GlobalPID);
  return 0;
}

// 0x1bb3200
void *gohGetDvlFaceSprite(s32 _devilId) {
  Il2CppObject *Instance;

  Instance = _get_Instance();
  return GetFaceSprite(Instance, devilId, 0);
}

// 0x1bb3260
s32 gohCheckModelLoad(s32 ModelTableIndex) {
  s32 max_length;
  s64 v5;
  s32 v6;
  s64 i;
  u32 *v8;
  s32 v9;
  s32 v10;
  s32 v11;
  bool v12;

  max_length = ModelTable[ModelTableIndex]->Flag->max_length;
  if (max_length - 1 < 0)
    return -1;
  v5 = ModelTableIndex;
  v6 = -1;
  for (i = 8 * (u32)(max_length - 1) + 32; ; i -= 8)
  {
    v8 = *(Il2CppClass **)((char *)&ModelTable[v5]->Flag->obj.klass + i);
    v9 = v8[6];
    v10 = v8[4];
    v11 = v8[5];
    if (v10)
      v12 = 0;
    else
      v12 = v11 == 0;
    if (!(v12 && v9 == 0))
    {
      if (!v10 || evtBitCheck(v10))
        break;
    }
    if (--max_length <= 0)
      return v6;
  }
  if (v11 && !evtBitCheck(v11) || v9 && evtBitCheck(v9))
    return -1;
  return ModelTable[v5]->Minor;
}

// 0x1bb33d0
s32 ModelLoad(gohData_t *pData) {
  s32 Flag;
  s32 ModelTableIndex;
  s32 v5;
  s32 v6;
  s32 v8;
  s32 v9;
  s32 v10;
  dds3ModelResrc_t *v11;
  dds3ModelHandle_t *Model;
  s64 ModelLoadCnt;
  dds3ModelHandle_t *v14;
  dds3ModelHandle_t *v15;
  Il2CppClass **v16;
  f32 *Pos;
  s64 v19;
  f32 v20;

  Flag = pData->Flag;
  if ((Flag & 2) != 0)
  {
    if ((Flag & 8) != 0)
      return 0;
    if ((Flag & 4) != 0)
      v5 = 8;
    else
      v5 = 4;
    v6 = v5 | Flag;
    goto LABEL_38;
  }
  if ((Flag & 1) != 0)
  {
    ModelTableIndex = pData->ModelTableIndex;
  }
  else
  {
    ModelTableIndex = 0;
    *(u64 *)&pData->ModelTableIndex = 0;
  }
  pData->Flag = Flag | 1;
  if (ModelTableIndex >= SLODWORD(ModelTable->max_length))
    goto LABEL_37;
  goto LABEL_9000;
  if (ModelTableIndex >= SLODWORD(ModelTable->max_length))
  {
LABEL_37:
    v6 = pData->Flag | 2;
LABEL_38:
    pData->Flag = v6;
    return 1;
  }
LABEL_9000:
  if (pData->ModelLoadCnt >= SLODWORD(pData->Model->max_length))
    goto LABEL_37;
  v8 = pData->ModelTableIndex;
  v9 = gohCheckModelLoad(v8);
  if (v9 >= 0)
  {
    v10 = v9;
    v11 = mdlPrepare(3u, v10, 0);
    if (!READY(v11))
      return 1;
    Model = pData->Model;
    ModelLoadCnt = pData->ModelLoadCnt;
    v14 = mdlLoad(3u, v10);
    v15 = v14;
    v16 = &Model->obj.klass + ModelLoadCnt;
    v16[4] = v15;
    pData->ModelIndex[pData->ModelLoadCnt] = pData->ModelTableIndex;
    Pos = ModelTable[pData->ModelTableIndex]->Pos;
    v19 = *(u64 *)Pos;
    v20 = Pos[2];
    *(u64 *)&vct_A.x = v19;
    vct_A.z = v20;
    vct_A.w = 0.0;
    mdlSetPosition(pData->Model[pData->ModelLoadCnt]);
    mdlLoopMotion(pData->Model[pData->ModelLoadCnt], 0, 0);
    mdlSetMotionSpeedEx(pData->Model[pData->ModelLoadCnt], 0, 0.5);
    mdlSetMotionSpeedEx(pData->Model[pData->ModelLoadCnt], 1, 0.5);
    mdlSetMotionSpeedEx(pData->Model[pData->ModelLoadCnt], 2, 0.5);
    ++pData->ModelLoadCnt;
  }
  ++pData->ModelTableIndex;
  return 1;
}

// 0x1bb3780
void ModelFree(gohData_t *pData) {
  dds3ModelHandle_t *Model;
  s64 v4;
  s64 v5;
  u64 *v6;
  dds3ModelHandle_t *v7;
  s32 Flag;

  Model = pData->Model;
  if (SLODWORD(Model->max_length) >= 1)
  {
    v4 = 0;
    v5 = 32;
    do
    {
      v7 = *(dds3ModelHandle_t *)((char *)&Model->obj.klass + v5);
      if (v7)
      {
        Free(v7);
        v6 = ((char *)&pData->Model->obj.klass + v5);
        *v6 = 0;
        Model = pData->Model;
      }
      ++v4;
      v5 += 8;
    }
    while (v4 < SLODWORD(Model->max_length));
  }
  Flag = pData->Flag;
  pData->Flag = Flag & 0xFFFFFFFC;
  if (pData->dvlFaceSet)
    pData->Flag = Flag & 0xFFFFFFF0;
}

// 0x1bb3870
void gohTableLoad(gohTable_t *pTable) {
  u8 **p_gohCombine;
  u8 *v5;
  u16 **p_gohAccidentFailTbl;
  u16 *v8;
  SKLID **p_gohNotDupliSkillTbl;
  SKLID *v11;
  void *Ctrl_k__BackingField;
  void *Asset;
  s64 naturalAligment;
  void *p_pEventDevil;
  UnityEngine_Object_c *klass;
  void *v21;
  void *v22;
  void *v24;
  s64 v26;
  void *p_swordTree;
  UnityEngine_Object_c *v28;
  void *v29;
  void *v30;
  void *v32;
  s64 v34;
  void *p_nameSortTbl;
  UnityEngine_Object_c *v36;
  void *v37;
  void *v38;

  p_gohCombine = &gohCombine;
  v5 = *p_gohCombine;
  pTable->CombineTbl = *p_gohCombine;
  p_gohAccidentFailTbl = &gohAccidentFailTbl;
  v8 = *p_gohAccidentFailTbl;
  pTable->pAccidentFail = *p_gohAccidentFailTbl;
  p_gohNotDupliSkillTbl = &gohNotDupliSkillTbl;
  v11 = *p_gohNotDupliSkillTbl;
  pTable->pNotDupliSkill = *p_gohNotDupliSkillTbl;
  Ctrl_k__BackingField = _Ctrl_k__BackingField;
  Asset = LoadAsset(Ctrl_k__BackingField, gohAssetName, "gohEventDevilTbl", 0);
  if (!Asset)
  {
    pTable->pEventDevil = 0;
    goto LABEL_34;
  }
  if (Asset->klass->_2.naturalAligment < (u32)naturalAligment)
  {
    pTable->pEventDevil = 0;
    p_pEventDevil = &pTable->pEventDevil;
    klass = Asset->klass;
    if (Asset->klass->_2.naturalAligment >= (u32)naturalAligment)
      goto LABEL_18;
LABEL_32:
    goto LABEL_34;
  }
  if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_gohEventDevilTbl)
    v22 = Asset;
  else
    v22 = 0;
  pTable->pEventDevil = v22;
  p_pEventDevil = &pTable->pEventDevil;
  klass = Asset->klass;
  if (Asset->klass->_2.naturalAligment < (u32)naturalAligment)
    goto LABEL_32;
LABEL_18:
  if (klass->_2.typeHierarchy[naturalAligment - 1] == Project_gohEventDevilTbl)
    v21 = Asset;
  else
    v21 = 0;
LABEL_34:
  v24 = LoadAsset(_Ctrl_k__BackingField, gohAssetName, "GohSwordTreeTbl", 0);
  if (!v24)
  {
    pTable->swordTree = 0;
    goto LABEL_52;
  }
  if (v24->klass->_2.naturalAligment < (u32)v26)
  {
    pTable->swordTree = 0;
    p_swordTree = &pTable->swordTree;
    v28 = v24->klass;
    if (v24->klass->_2.naturalAligment >= (u32)v26)
      goto LABEL_39;
LABEL_50:
    goto LABEL_52;
  }
  if (v24->klass->_2.typeHierarchy[v26 - 1] == Project_GohSwordTreeTbl)
    v30 = v24;
  else
    v30 = 0;
  pTable->swordTree = v30;
  p_swordTree = &pTable->swordTree;
  v28 = v24->klass;
  if (v24->klass->_2.naturalAligment < (u32)v26)
    goto LABEL_50;
LABEL_39:
  if (v28->_2.typeHierarchy[v26 - 1] == Project_GohSwordTreeTbl)
    v29 = v24;
  else
    v29 = 0;
LABEL_52:
  v32 = LoadAsset(_Ctrl_k__BackingField, gohAssetName, "gohDevilNameSortTbl", 0);
  if (!v32)
  {
    v37 = 0;
    pTable->nameSortTbl = 0;
    p_nameSortTbl = &pTable->nameSortTbl;
    goto LABEL_66;
  }
  if (v32->klass->_2.naturalAligment >= (u32)v34)
  {
    if (v32->klass->_2.typeHierarchy[v34 - 1] == Project_GohDvlNameSortTbl)
      v38 = v32;
    else
      v38 = 0;
    pTable->nameSortTbl = v38;
    p_nameSortTbl = &pTable->nameSortTbl;
    v36 = v32->klass;
    if (v32->klass->_2.naturalAligment >= (u32)v34)
      goto LABEL_57;
LABEL_65:
    v37 = 0;
    goto LABEL_66;
  }
  pTable->nameSortTbl = 0;
  p_nameSortTbl = &pTable->nameSortTbl;
  v36 = v32->klass;
  if (v32->klass->_2.naturalAligment < (u32)v34)
    goto LABEL_65;
LABEL_57:
  if (v36->_2.typeHierarchy[v34 - 1] == Project_GohDvlNameSortTbl)
    v37 = v32;
  else
    v37 = 0;
LABEL_66:
  gohSetup();
  gohCreateSortedDevilList(pTable->DevilList, pTable);
  gohTablRegistEventDevil(pTable);
}

// 0x1bb3d70
void gohTableFree(gohTable_t *pTable) {
  pTable->pAccidentFail = 0;
  pTable->pEventDevil = 0;
  pTable->pNotDupliSkill = 0;
  pTable->nameSortTbl = 0;
  pTable->swordTree = 0;
  pTable->DevilList = 0;
}

// 0x1bb3df0
bool gohEvtFadeInCheck(void) {
  char v1;

  if (evtBitCheck(149))
  {
    v1 = evtBitCheck(150);
    if (!evtBitCheck(198))
      return v1 & 1;
    goto LABEL_5;
  }
  v1 = 1;
  if (evtBitCheck(198))
LABEL_5:
    v1 &= evtBitCheck(199);
  return v1 & 1;
}

// 0x1bb3e70
void gohStartEtcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *v5;
  bool v6;
  dds3ProcessFunc_t v7;
  dds3ProcessFunc_t v8;
  u8 *klass;
  dds3ProcessID_t *started;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = Allocate(dds3ProcessID_t);
  _ctor(v5, 0);
  if (evtBitCheck(149))
  {
    v6 = evtBitCheck(150);
    if (evtBitCheck(198) && !evtBitCheck(199))
      goto LABEL_21;
    goto LABEL_17;
  }
  if (evtBitCheck(198))
  {
    v6 = 1;
    if (!evtBitCheck(199))
      goto LABEL_21;
LABEL_17:
    if (!v6)
      goto LABEL_21;
  }
  dds3FadeIn(0, 0, 0, 0x1Eu);
LABEL_21:
  v7 = Allocate(dds3ProcessFunc_t);
  _ctor(v7, 0, Method_Project_gohMain_RootWaitDrawProcess__, 0);
  dds3StartProcess("gohmaden_draw", 11022, 0, 0, v7, 0, ProcessData);
  v8 = Allocate(dds3ProcessFunc_t);
  _ctor(v8, 0, Method_Project_gohMain_RootWaitUpdateProcess__, 0);
  dds3StartProcess("gohmaden_updt", 21003, 0, 0, v8, 0, ProcessData);
  klass = ProcessData[7].klass;
  started = scrStartScript2(1, klass, 0, 1);
  ProcessData[7].monitor = started;
}

// 0x1bb41a0
s32 gohLoadBgModel(dds3ProcessID_t *PID, gohData_t *pData) {
  dds3ProcessID_t *p_PmvPID;
  dds3ProcessID_t *v6;
  dds3ProcessID_t *v7;
  dds3ProcessID_t *parent;

  parent = PID;
  p_PmvPID = &pData->PmvPID;
  if (pData->PmvPID)
    return 0;
  v6 = evtStart2(0, 680, 1, 3);
  p_PmvPID = v6;
  dds3LinkProcess(parent, &pData->PmvPID);
  scrSetMovieCancel(0);
  v7 = p_PmvPID;
  evtIgnoreFade(v7);
  pData->Flag |= 0x10u;
  return 1;
}

// 0x1bb42f0
s32 gohCheckLoadBgModel(gohData_t *pData) {
  dds3ProcessID_t *PmvPID;

  PmvPID = pData->PmvPID;
  if (evtCheckRun(PmvPID))
  {
    pData->Flag |= 0x40020u;
    return 0;
  }
  return 1;
}

// 0x1bb43b0
void gohFreeBgModel(gohData_t *pData) {
  dds3ProcessID_t *PmvPID;

  PmvPID = pData->PmvPID;
  if (PmvPID)
  {
    evtEnd(PmvPID);
    pData->PmvPID = 0;
    pData->Flag &= 0xFFFFFFCF;
  }
}

// 0x1bb4440
s32 gohBgmLoad(gohData_t *pData) {
  if ((byte_57570C3 & 1) == 0)
  {
    if ((pData->Flag & 0x100) == 0)
      goto LABEL_3;
    return 1;
  }
  if ((pData->Flag & 0x100) != 0)
    return 1;
LABEL_3:
  sndBgmLoadId_XF(19);
  pData->Flag |= 0x100u;
  return 0;
}

// 0x1bb44d0
s32 gohBgmPlay(gohData_t *pData) {
  if ((pData->Flag & 0x200) != 0)
    return 1;
  if (sndBgmStatus_XF() == 2)
  {
    sndBgmFadeIn(0, 0);
    pData->Flag |= 0x200u;
    return 1;
  }
  return 0;
}

// 0x1bb4590
s32 gohBgmStop(gohData_t *pData) {
  sndBgmStop();
  sndBgmFree();
  pData->Flag &= 0xFFFFFCFF;
  return 0;
}

// 0x1bb4610
dds3ProcessFunc_t gohLoad2ndProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *v10;
  dds3ProcessID_t *monitor;
  dds3ProcessID_t *v16;
  dds3ProcessFunc_t v17;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if ((BYTE1(ProcessData[1].klass) & 2) == 0)
    goto LABEL_12;
LABEL_18:
  if (!ModelLoad(ProcessData))
    goto LABEL_25;
  return 0;
LABEL_12:
  if (sndBgmStatus_XF() != 2)
    return 0;
  sndBgmFadeIn(0, 0);
  LODWORD(ProcessData[1].klass) |= 0x200u;
  goto LABEL_18;
LABEL_25:
  v10 = id;
  if (!!gohLoadBgModel(v10, ProcessData))
    return 0;
  monitor = ProcessData[2].monitor;
  if (!evtCheckRun(monitor))
    return 0;
  LODWORD(ProcessData[1].klass) |= 0x40020u;
  if (!p2sdLoadCheckMidi(4259840))
  {
    p2sdLoadSMGFile(4259840);
    return 0;
  }
  if (!GohCreateAllUnitSortTbl(ProcessData))
    return 0;
  v16 = id;
  gohStartEtcProcess(v16);
  v17 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v17, 0, Method_Project_gohMain_RootWaitCalcProcess__, 0);
  return v17;
}

// 0x1bb4a20
dds3ProcessFunc_t gohEventScrProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *monitor;
  s32 v6;
  dds3ProcessFunc_t v8;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  monitor = ProcessData[6].monitor;
  if (gohCheckScrRun(ProcessData[6].monitor))
    goto LABEL_11;
  if ((BYTE1(ProcessData[1].klass) & 1) != 0)
    goto LABEL_34;
  goto LABEL_31;
  if ((BYTE1(ProcessData[1].klass) & 1) != 0)
  {
LABEL_34:
    v8 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
    _ctor(v8, 0, Method_Project_gohInit_Load2ndProcess__, 0);
    return v8;
  }
LABEL_31:
  sndBgmLoadId_XF(19);
  LODWORD(ProcessData[1].klass) |= 0x100u;
  goto LABEL_34;
LABEL_11:
  if (evtBitCheck(253) || !evtBitCheck(200))
  {
    if (BYTE5(ProcessData[26].klass))
    {
      fldFacilityMistInit(0);
      BYTE5(ProcessData[26].klass) = 0;
    }
    v6 = 0;
  }
  else
  {
    v6 = 1;
  }
  fldFacilityMistDraw(v6);
  return 0;
}

// 0x1bb4ce0
void gohProcessEnd(void) {
  dds3KillProcessName("gohmaden_calc", 0);
  dds3KillProcessName("gohmaden_draw", 0);
  dds3KillProcessName("gohmaden_updt", 0);
  dds3KillProcessName("gohmaden_always_draw", 0);
}

// 0x1bb4dd0
s32 gohProcessCheck(void) {
  return dds3SearchProcessName("gohmaden_calc") != 0;
}

// 0x1bb4e50
void gohDebugProcessEnd(void) {
  gohProcessEnd();
}

// 0x1bb4ec0
s32 gohDebugProcessCheck(void) {
  return dds3SearchProcessName("gohmaden_calc") != 0;
}

// 0x1bb4fb0
s32 gohScrCmd_GOH_EXIT(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  s32 IntPara;
  s32 v9;

  if (!GlobalPID)
    return 1;
  ProcessData = dds3GetProcessData(GlobalPID);
  v4 = ProcessData;
  IntPara = scrGetIntPara(0);
  if (IntPara != 1)
    goto LABEL_14;
  v9 = 2;
LABEL_25:
  HIDWORD(v4[10].klass) = v9;
  return 1;
LABEL_14:
  if (IntPara)
  {
    v9 = 3;
    goto LABEL_25;
  }
  HIDWORD(v4[10].klass) = 1;
  return !dds3SearchProcessName("gohmaden_calc");
}

// 0x1bb51f0
void gohStopSequence(void) {
  gohProcessEnd();
}

// 0x1bb5260
s32 gohCheckSequence(void) {
  return dds3SearchProcessName("gohmaden_calc") == 0;
}

// 0x1bb5350
s32 gohScrCmd_CALL_GOHMADEN(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  fldGbLocationSavePointStore();
  dds3AdminiCallSequence2(40, IntPara, 0, 0);
  scrAllReleaseScript();
  return 1;
}

// 0x1bb5400
s32 gohScrCmd_RequestItemNo(void) {
  s32 v1;

  v1 = gohRequestItemNo();
  scrSetIntReturnValue(v1);
  return 1;
}

// 0x1bb5470
s32 gohScrCmd_RequestItemCnt(void) {
  s32 v1;

  v1 = gohRequestItemCnt();
  scrSetIntReturnValue(v1);
  return 1;
}

// 0x1bb54e0
s32 gohScrCmd_PresentItem(void) {
  s32 v1;
  s32 IntPara;
  bool v3;
  bool v4;
  s32 v5;

  v1 = gohRequestItemNo();
  IntPara = scrGetIntPara(0);
  v3 = datCheckItem(v1, 1);
  v4 = gohPresentItem(IntPara != 0 && v3);
  if (!IntPara)
  {
    v5 = 0;
    goto LABEL_17;
  }
  if (v4)
  {
    datAddItem(v1, -1);
  }
  if (v3)
    v5 = 1;
  else
    v5 = -1;
LABEL_17:
  scrSetIntReturnValue(v5);
  return 1;
}

// 0x1bb5610
s32 gohScrCmd_AccidentType(void) {
  s32 TypeCnt;
  s32 v2;
  s32 i;
  s32 TypeNo;
  s32 v5;

  TypeCnt = gohGetTypeCnt();
  if (TypeCnt < 1)
  {
    v5 = 0;
    goto LABEL_8;
  }
  v2 = TypeCnt;
  for (i = 0; i != v2; ++i)
    TypeNo = gohGetTypeNo(i);
  v5 = TypeNo;
LABEL_8:
  scrSetIntReturnValue(v5);
  return 1;
}

// 0x1bb56c0
s32 gohScrCmd_AccidentKind(void) {
  s32 KindNo;

  KindNo = gohGetKindNo();
  scrSetIntReturnValue(KindNo);
  return 1;
}

// 0x1bb5730
s32 gohScrCmd_AccidentTypeVal(void) {
  s32 IntPara;
  s32 TypeVal;

  IntPara = scrGetIntPara(0);
  TypeVal = gohGetTypeVal(IntPara);
  scrSetIntReturnValue(TypeVal);
  return 1;
}

// 0x1bb57a0
s32 gohScrCmd_AccidentCancel(void) {
  gohClear();
  return 1;
}

// 0x1bb57c0
s32 gohScrCmd_AccidentMajinCnt(void) {
  return 1;
}

// 0x1bb57d0
s32 gohScrCmd_AccidentSelectMajin(void) {
  return 1;
}

// 0x1bb57e0
s32 gohScrCmd_GetCombiCount(void) {
  s32 CombiCount;

  CombiCount = gohGetCombiCount(2);
  scrSetIntReturnValue(CombiCount);
  return 1;
}

// 0x1bb5850
s32 gohScrCmd_RenkenAporion(void) {
  s16 *ProcessData;
  bool v4;
  s32 v6;

  if (!GlobalPID)
  {
    v4 = 1;
    goto LABEL_16;
  }
  ProcessData = dds3GetProcessData(GlobalPID);
  if (!ProcessData)
  v4 = gohCheckAporion(ProcessData[180], ProcessData[179]);
LABEL_16:
  v6 = ToInt32_54962832(v4, 0);
  scrSetIntReturnValue(v6);
  return 1;
}

// 0x1bb5a00
s32 gohScrCmd_RenkenComposition(void) {
  s16 *ProcessData;
  s16 *v4;
  s32 v6;
  s32 v7;
  s32 v8;

  if (!GlobalPID)
  {
    v4 = 0;
    v7 = 0;
    v6 = 0;
    goto LABEL_13;
  }
  ProcessData = dds3GetProcessData(GlobalPID);
  v4 = ProcessData;
  v6 = ProcessData[179];
  v7 = ProcessData[180];
LABEL_13:
  v8 = gohCheckComposition(v7, v6);
  scrSetIntReturnValue(v8);
  if (v8)
    return 1;
  gohComposition(v7, v6);
  *((u8 *)v4 + 357) = 1;
  return 1;
}

// 0x1bb5d50
s32 gohScrCmd_RenkenResultVal(void) {
  s32 IntPara;
  s16 *ProcessData;
  s16 *v6;
  s32 m_hojo;
  s32 SwordType;
  u32 v10;
  sdatPlayerUnitWork_t *v14;
  s32 v15;
  bool Master;
  sdatPlayerUnitWork_t *player;

  IntPara = scrGetIntPara(0);
  if (!GlobalPID)
    return 1;
  ProcessData = dds3GetProcessData(GlobalPID);
  if (!ProcessData)
    return 1;
  v6 = ProcessData;
  switch (IntPara)
  {
    case 0:
      m_hojo = ProcessData[180] + 144;
      break;
    case 1:
      SwordType = gohGetSwordType(ProcessData[180]);
      if ((u32)(SwordType - 1) >= 3)
        m_hojo = 0;
      else
        m_hojo = SwordType;
      break;
    case 2:
      v10 = gohGetSwordAuraNo(ProcessData[180]) - 2;
      if (v10 >= 9)
        m_hojo = 0;
      else
        m_hojo = v10;
      break;
    case 3:
      m_hojo = GBWK->player->swordno == v6[179];
      break;
    case 4:
      m_hojo = tbl[v6[180]]->m_hojo;
      break;
    case 5:
      if (!*((u8 *)v6 + 539))
      {
        player = GBWK->player;
        Master = datSpiritSkillGetMaster(player, tbl[v6[180]]->m_hojo);
        goto LABEL_58;
      }
      v14 = GBWK->player;
      if (datRaidouSkillGetMaster(v14, tbl[v6[180]]->m_hojo))
      {
        m_hojo = 2;
      }
      else
      {
        m_hojo = 0;
      }
      break;
    case 6:
      v15 = tbl[v6[180]]->m_hojo;
      Master = RaidouSklCheck(v15);
LABEL_58:
      m_hojo = Master;
      break;
    default:
      m_hojo = 0;
      break;
  }
  scrSetIntReturnValue(m_hojo);
  return 1;
}

// 0x1bb61d0
s32 gohScrCmd_RenkenSpirit(void) {
  s32 IntPara;
  Il2CppObject *ProcessData;

  IntPara = scrGetIntPara(0);
  if (!GlobalPID)
    return 1;
  ProcessData = dds3GetProcessData(GlobalPID);
  if (!ProcessData)
    return 1;
  BYTE2(ProcessData[31].klass) = IntPara == 0;
  return 1;
}

// 0x1bb6350
s32 gohScrCmd_RenkenEquip(void) {
  s16 *ProcessData;
  s32 v6;

  if (!GlobalPID)
    return 1;
  ProcessData = dds3GetProcessData(GlobalPID);
  if (!ProcessData)
    return 1;
  v6 = ProcessData[180];
  datSetPlayerSword(v6, 0);
  return 1;
}

// 0x1bb64d0
s32 gohScrCmd_RenkenEquipAnime(void) {
  s32 IntPara;
  bool v2;
  s32 v3;

  IntPara = scrGetIntPara(0);
  v2 = ToBoolean_54990112(IntPara, 0);
  if (v2)
    v3 = 2;
  else
    v3 = 3;
  cmpSetEvent(v3);
  return 1;
}

// 0x1bb65b0
s32 gohScrCmd_GiftInfo(void) {
  s32 IntPara;
  s16 *ProcessData;
  s32 v7;

  IntPara = scrGetIntPara(0);
  if (!GlobalPID)
    return 1;
  ProcessData = dds3GetProcessData(GlobalPID);
  if (!ProcessData)
    return 1;
  switch (IntPara)
  {
    case 0:
      v7 = ProcessData[94] - 1;
      break;
    case 1:
      v7 = ProcessData[95];
      break;
    case 2:
      v7 = ProcessData[96];
      break;
    case 3:
      v7 = ProcessData[97];
      break;
    case 4:
      v7 = ProcessData[289];
      break;
    default:
      v7 = 0;
      break;
  }
  scrSetIntReturnValue(v7);
  return 1;
}

// 0x1bb67d0
s32 gohScrCmd_BirthDevilNo(void) {
  Il2CppObject *ProcessData;
  s32 v6;

  if (!GlobalPID)
    return 1;
  ProcessData = dds3GetProcessData(GlobalPID);
  if (!ProcessData)
    return 1;
  v6 = *((s16 *)ProcessData[16].monitor + 11);
  scrSetIntReturnValue(v6);
  return 1;
}

// 0x1bb6950
s32 gohScrCmd_BirthOmoideSkillCnt(void) {
  Il2CppObject *ProcessData;
  s32 v6;

  if (!GlobalPID)
    return 1;
  ProcessData = dds3GetProcessData(GlobalPID);
  if (!ProcessData)
    return 1;
  v6 = *((s16 *)ProcessData[16].monitor + 108);
  scrSetIntReturnValue(v6);
  return 1;
}

// 0x1bb6ad0
s32 gohScrCmd_GetSinanMenuIndex(void) {
  Il2CppObject *ProcessData;
  s32 monitor;

  if (!GlobalPID)
    return 1;
  ProcessData = dds3GetProcessData(GlobalPID);
  if (!ProcessData)
  monitor = ProcessData[25].monitor;
  scrSetIntReturnValue(monitor);
  return 1;
}

// 0x1bb6c50
dds3ProcessFunc_t gohLoad1stProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  DvlFaceSet *v5;
  void *CombineResultAllAsync;
  void *Asset;
  sdfBinary *v16;
  u8 *data;
  void *v19;
  sdfBinary *v20;
  void *v22;
  sdfBinary *v23;
  void *v25;
  sdfBinary *v26;
  void *v28;
  sdfBinary *v29;
  void *v31;
  sdfBinary *v32;
  u8 *v33;
  u8 *v34;
  u8 *v35;
  u8 *v36;
  u8 *v37;
  s32 v38;
  u8 *pEvtScrData;
  dds3ProcessID_t *started;
  dds3ProcessFunc_t v42;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if (!ProcessData->dataLoad)
  {
    v5 = Allocate(DvlFaceSet);
    _ctor(v5, 0);
    ProcessData->dvlFaceSet = v5;
    Load(Dependent, gohAssetName, gohAssetName);
    LoadSyncAll(_Ctrl_k__BackingField, 0);
    gohTableLoad(ProcessData->Table);
    CtrlStart(0);
    CtrlStart(0);
    allUnitTblCreated = 0;
    ProcessData->Flag &= ~0x100000u;
    CombineResultAllAsync = gohCreateCombineResultAllAsync(ProcessData);
    ProcessData->result2Task = CombineResultAllAsync;
    Asset = LoadAsset(_Ctrl_k__BackingField, gohAssetName, "goh_mes.bmd", 0);
    v16 = Allocate(sdfBinary);
    _ctor(v16, Asset, 0);
    data = v16->data;
    ProcessData->pMsgData = data;
    Create(0);
    fclLinkData(ProcessData->pMsgData);
    fclSelMesSpeedMax(g_mainPID, 1);
    v19 = LoadAsset(_Ctrl_k__BackingField, gohAssetName, "goh_evt.bf", 0);
    v20 = Allocate(sdfBinary);
    _ctor(v20, v19, 0);
    v22 = LoadAsset(_Ctrl_k__BackingField, gohAssetName, "goh_evt2.bf", 0);
    v23 = Allocate(sdfBinary);
    _ctor(v23, v22, 0);
    v25 = LoadAsset(_Ctrl_k__BackingField, gohAssetName, "goh_talk.bf", 0);
    v26 = Allocate(sdfBinary);
    _ctor(v26, v25, 0);
    v28 = LoadAsset(_Ctrl_k__BackingField, gohAssetName, "gohmaden.bf", 0);
    v29 = Allocate(sdfBinary);
    _ctor(v29, v28, 0);
    v31 = LoadAsset(_Ctrl_k__BackingField, gohAssetName, "goh_sinan.bf", 0);
    v32 = Allocate(sdfBinary);
    _ctor(v32, v31, 0);
    v33 = v20->data;
    ProcessData->pEvtScrData = v33;
    v34 = v23->data;
    ProcessData->pEvt2ScrData = v34;
    v35 = v26->data;
    ProcessData->m_pTalkScrData = v35;
    v36 = v29->data;
    ProcessData->m_pScrData = v36;
    v37 = v32->data;
    ProcessData->pSinanScrData = v37;
    Unload(Dependent, gohAssetName, 0);
    if (evtBitCheck(253) || !evtBitCheck(200))
    {
      v38 = 0;
    }
    else
    {
      v38 = 1;
    }
    fldFacilityMistInit(v38);
    ProcessData->milkMist = v38;
    ProcessData->dataLoad = 1;
  }
  pEvtScrData = ProcessData->pEvtScrData;
  started = scrStartScript2(1, pEvtScrData, 0, 1);
  ProcessData->EvtScrPID = started;
  v42 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v42, 0, Method_Project_gohInit_EventScrProcess__, 0);
  return v42;
}

// 0x1bb7470
gohData_t *Init(void) {
  gohData_t *v1;
  DvlFaceSet *v3;
  jmsSeqHandle_t *v5;
  Il2CppObject *v8;
  Il2CppObject *v9;

  v1 = Allocate(gohData_t);
  _ctor(v1);
  v3 = Allocate(DvlFaceSet);
  _ctor(v3, 0);
  v1->dvlFaceSet = v3;
  v1->MenuFade = 1;
  v5 = v1->SeqHandle;
  jmsInitSeqHandle(v5);
  gohSetupDevilList();
  v1->m_bCompsitionFlag = 0;
  *(u32 *)&v1->m_iSelectBaseSwordNo = 0;
  v1->haveSword = 0;
  v1->menu_move = 1;
  v1->combStSeq = 0;
  v1->cmbBackStatus = 0;
  gohCreateInstance();
  v1->dataLoad = 0;
  nativeSkillStep = 0;
  gohMenuActive = 0;
  v8 = Allocate(GohKarteSeq);
  _ctor(v8, 0);
  (v8->klass->vtable[4].methodPtr)(v8, v8->klass->vtable[4].method);
  v1->gohKarteSeq = v8;
  v9 = Allocate(GohKarte2Seq);
  _ctor(v9, 0);
  (v9->klass->vtable[4].methodPtr)(v9, v9->klass->vtable[4].method);
  v1->gohKarte2Seq = v9;
  return v1;
}

// 0x1bb7b60
void Destroy(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  gohData_t *v4;
  s32 ExitFlag;
  dds3ProcessID_t *p_PmvPID;
  dds3ProcessID_t *PmvPID;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v13;
  void *m_pDevSelList1;
  void *m_pDevSelList2;
  void *m_pSelList;
  gohTable_t *Table;
  SequenceParameter *v21;
  s32 *EventBit;
  s32 v25;
  s32 v27;
  s32 *v30;
  dds3ProcessID_t *id;

  id = PID;
  goto LABEL_3;
LABEL_14:
  gohDestroyInstance();
  ExitFlag = 0;
  goto LABEL_43;
LABEL_3:
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_14;
  v4 = ProcessData;
  gohDestroyInstance();
  ExitFlag = v4->ExitFlag;
  dds3KillProcessName("gohmaden_draw", 0);
  dds3KillProcessName("gohmaden_updt", 0);
  p_PmvPID = &v4->PmvPID;
  PmvPID = v4->PmvPID;
  if (PmvPID)
  {
    evtEnd(PmvPID);
    v4->PmvPID = 0;
    v4->Flag &= 0xFFFFFFCF;
  }
  ModelFree(v4);
  Delete(0);
  fclDestroyMessage();
  v4->pMsgData = 0;
  v4->m_pScrData = 0;
  v4->m_pTalkScrData = 0;
  v4->pEvtScrData = 0;
  v4->pEvt2ScrData = 0;
  v4->pSinanScrData = 0;
  ProcessEnd(gCallFromMenu == 0, 0);
  SeqHandle = v4->SeqHandle;
  v13 = id;
  jmsSeqDestroyAll(SeqHandle, v13);
  ProcessEnd();
  m_pDevSelList1 = v4->m_pDevSelList1;
  if (m_pDevSelList1)
    jmsDestroyCmdMenu(m_pDevSelList1);
  m_pDevSelList2 = v4->m_pDevSelList2;
  if (m_pDevSelList2)
    jmsDestroyCmdMenu(m_pDevSelList2);
  m_pSelList = v4->m_pSelList;
  if (m_pSelList)
    jmsDestroyCmdMenu(m_pSelList);
  Table = v4->Table;
  Table->pAccidentFail = 0;
  Table->pEventDevil = 0;
  Table->pNotDupliSkill = 0;
  Table->nameSortTbl = 0;
  Table->swordTree = 0;
  Table->DevilList = 0;
  sndBgmFadeOut2();
  gohHDParClear(v4);
  p2sdUnLoadSMGFile(4259840, 1);
LABEL_43:
  GlobalPID = 0;
  GlobalDrawPID = 0;
  if (ExitFlag == 3)
  {
    EventBit = GBWK->EventBit;
    EventBit[72] &= ~1u;
    return;
  }
  if (ExitFlag == 2)
  {
    v21 = Allocate(SequenceParameter);
    _ctor(v21, 0);
    v21->CallData2 = 0;
    dds3AdminiCallSequence(40, v21, 0);
    return;
  }
  v25 = gCallFromMenu;
  if (v25 == 3)
    goto LABEL_57;
  if (v25 == 4)
    goto LABEL_57;
  v25 = gCallFromMenu;
  if (v25 == 1)
    goto LABEL_79;
  v25 = gCallFromMenu;
  if (v25)
  {
    v25 = gCallFromMenu;
    if (v25 == 2)
      v27 = 6;
    else
      v27 = 0;
    goto LABEL_78;
  }
  else
  {
    mapTitleAutoFade();
    v27 = 0;
    goto LABEL_78;
  }
LABEL_78:
  mapReturnFromShop(v27);
  goto LABEL_79;
LABEL_57:
  if (ProcessCheck())
    goto LABEL_79;
  gohReturnToShop();
LABEL_79:
  v30 = GBWK->EventBit;
  v30[72] &= ~1u;
  nativeSkillStep = 0;
}

// 0x1bb8310
void gohHDParClear(gohData_t *_data) {
  data->dvlFaceSet = 0;
  data->combiDevil1 = 0;
  data->combiDevil2 = 0;
  data->combiBarthDevil = 0;
  data->gohKarteSeq = 0;
  data->gohKarte2Seq = 0;
  data->writeUnit = 0;
  data->m_ReprtDevil1 = 0;
  data->m_ReprtDevil2 = 0;
  data->gouScene = 0;
}

// 0x1bb83d0
void gohReturnToShop(void) {
  _BOOL4 v2;

  v2 = gCallFromMenu == 4;
  g_NoRelese = 1;
  if (ProcessCheck())
    return;
  dds3AdminiCallSequence2(11, 2 * v2, 0, 0);
  return;
}

// 0x1bb2b20
dds3ProcessID_t *gohProcessStart(s32 iMode) {
  Il2CppObject *inited;
  s32 v5;
  dds3ProcessFunc_t v6;
  shutdownfuncDelegate v7;
  dds3ProcessID_t *started;
  dds3ProcessFunc_t v9;
  shutdownfuncDelegate v10;
  dds3ProcessID_t *v11;

  sdfMemRelease();
  dds3FadeOut(0, 0, 0, 0);
  inited = Init();
  if (GBWK->GameFileInfo->chapter == 9)
    v5 = 65;
  else
    v5 = 41;
  fldJmpBitOn(v5, 1);
  evtMoonDisableDraw(1);
  ProcessStart(0);
  v6 = Allocate(dds3ProcessFunc_t);
  _ctor(v6, 0, Method_Project_gohInit_Load1stProcess__, 0);
  v7 = Allocate(shutdownfuncDelegate);
  _ctor(v7, 0, Method_Project_gohInit_Destroy__, 0);
  started = dds3StartProcess("gohmaden_calc", 1024, 0, 1, v6, v7, inited);
  v9 = Allocate(dds3ProcessFunc_t);
  _ctor(v9, 0, Method_Project_gohInit_AlwaysDrawProcess__, 0);
  v10 = Allocate(shutdownfuncDelegate);
  _ctor(v10, 0, Method_Project_gohInit_AlwaysDrawDestroy__, 0);
  v11 = dds3StartProcess("gohmaden_always_draw", 1024, 0, 0, v9, v10, 0);
  GlobalPID = started;
  GlobalDrawPID = v11;
  gCallFromMenu = iMode;
  return started;
}

// 0x1bb84b0
dds3ProcessFunc_t gohAlwaysDrawProcess(dds3ProcessID_t *PID) {
  gohAllDrawCalc();
  return 0;
}

// 0x1bb8530
void gohAlwaysDrawDestroy(dds3ProcessID_t *PID) {
  fldFacilityMistDestroy(0);
}

// 0x1bb85b0
void gohStartSequence(u32 Mode) {
  if (!Mode || Mode == 2)
  {
    gohProcessStart(Mode);
  }
  else if (Mode == 1)
  {
    gohDebugProcessStart();
  }
}
