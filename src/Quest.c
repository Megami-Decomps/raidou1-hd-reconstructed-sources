#include "types.h"
#include "achievement.h"
#include "buttonguide.h"
#include "dat.h"
#include "dds3effect.h"
#include "dds3kerneldraw.h"
#include "dds3vrf.h"
#include "evtbit.h"
#include "evtmoon.h"
#include "file.h"
#include "fld.h"
#include "itf.h"
#include "localize.h"
#include "quest.h"
#include "sbtlitem.h"
#include "sbtlsound.h"
#include "scr.h"
#include "sndat3.h"
#include "sndmanager.h"
#include "tneffect_model.h"

#define QUEST_CLEAER "QUEST_INFO_L0001"
#define QUEST_GET_ITEM "QUEST_INFO_L0002"
#define QUEST_GET_MONEY "QUEST_INFO_L0003"
#define QUEST_GET_EXP "QUEST_INFO_L0003"
#define QUEST_GET_LOYALTY "QUEST_INFO_L0005"
#define QUEST_GET_LIMIT "QUEST_INFO_L0006"
#define QUEST_GO_TARA "QUEST_INFO_L0009"
#define QUEST_CAPACITY7 "QUEST_INFO_L0019"
#define QUEST_CAPACITY8 "QUEST_INFO_L0020"

#define QUEST_LENGTH 46

typedef enum {
    QuestResultStep_None = 0,
    QuestResultStep_Init = 1,
    QuestResultStep_EffIn = 2,
    QuestResultStep_Draw = 3,
    QuestResultStep_Effout = 4,
    QuestResultStep_End = 5,
} QuestResultStep;

typedef struct QUEST_CLASS QUEST_CLASS;
typedef struct effHandle_t effHandle_t;

QUEST_CLASS *QUESTDATA[46];
char *QuestDataAssetKey;
static QuestResultStep step;
static effHandle_t *hEff;
static f32 lifeTime;
static f32 inTime;
static f32 outTime;
static f32 totalTime;
static f32 timer;
static f32 ratio;
static sdfVector4_t effPos;
static sdfVector3_t gapCamPos;
static sdfVector3_t slidePos;
static bool sePlay;
static bool voicePlay;
static bool fieldUiDisable;
static s32 popType;
static f32 dispTime;
static void *text;
static void *icon;
static char *textSingle;
static bool returnMapBgm;
static s32 mapNo;
static s32 floorNo;
bool isResultRun;
static s32 mQuest_id;

static char *GetDevilOpenText(s32 ID);
static void *GetDevilKudaSpr(s32 ID);
static s32 GetFldCamera(void);
static void SetCameraStack(void *setCam);
static void DeleteCameraStack(void *deleteCam);
static void SetResultCameraPos(const sdfVector4_t *camPos);
static void SetFieldUiActive(bool active);
static void QuestResultInit(void);
static void EffectIn(void);
static void QuestResultDraw(void);
static void EffectOut(void);
static void QuestResultEnd(void);

// macros
// 0x1df2800: s32 QUEST_CLEAR_REWARD(void)
static inline s32 QUEST_CLEAR_REWARD(void) {
  void *v1;
  void *v2;
  s32 IntPara;
  QUEST_CLASS *QuestData;
  s32 v7;
  s64 v9;
  s32 *rItemID;
  s64 v11;
  s32 v12;
  il2cpp_array_size_t max_length;
  s64 v14;
  s32 v15;
  s32 v16;
  s64 v18;
  s64 v19;
  s32 v20;
  s32 v21;
  s32 v22;
  Il2CppObject *v23;
  s64 v24;
  u64 *v25;
  void *v26;
  Il2CppClass **v27;
  s32 v29;
  void *v30;
  Il2CppObject *v31;
  s64 v32;
  u64 *v33;
  void *v34;
  Il2CppClass **v35;
  s32 *v36;
  s64 v37;
  s64 v38;
  s32 v39;
  s32 v41;
  Il2CppObject *v43;
  s64 v44;
  u64 *v45;
  void *v46;
  Il2CppClass **v47;
  Il2CppObject *v49;
  s64 v50;
  u64 *v51;
  void *v52;
  Il2CppClass **v53;
  s64 v55;
  s32 rMoney;
  s32 v57;
  Il2CppObject *v58;
  s64 v59;
  u64 *v60;
  void *v61;
  Il2CppClass **v62;
  u64 *v63;
  s64 v64;
  void *v65;
  Il2CppClass **v66;
  s32 rKatana;
  s32 v68;
  Il2CppObject *v69;
  s64 v70;
  u64 *v71;
  void *v72;
  Il2CppClass **v73;
  s32 v75;
  void *v76;
  Il2CppObject *v77;
  s64 v78;
  u64 *v79;
  void *v80;
  Il2CppClass **v81;
  s32 spiritCnt;
  char **v84;
  Il2CppObject *v85;
  s64 v86;
  u64 *v87;
  void *v88;
  Il2CppClass **v89;
  Il2CppObject *v90;
  s64 v91;
  u64 *v92;
  void *v93;
  Il2CppClass **v94;
  u64 *v95;
  s64 v96;
  void *v97;
  Il2CppClass **v98;
  sdatPlayerUnitWork_t *player;
  s32 v101;
  u64 *v105;
  s64 v106;
  void *v107;
  Il2CppClass **v108;
  bool *quest_rewardFlag;
  struct Quest *v112;
  s64 v115;
  s64 v122;
  s64 v123;
  void *v124;
  s32 v129;
  Il2CppObject *Text;
  s32 iconType;
  void *Instance;
  Il2CppObject *ItmIconSpr;
  s64 size;
  u64 *v135;
  void *items;
  Il2CppClass **v137;
  u64 *v138;
  s64 v139;
  void *v140;
  Il2CppClass **v141;
  s32 *rDevilFlag;
  s64 v143;
  s64 v144;
  s32 v145;
  s32 v147;
  s64 v149;
  Il2CppObject *DevilOpenText;
  s64 v151;
  u64 *v152;
  void *v153;
  Il2CppClass **v154;
  Il2CppObject *DevilKudaSpr;
  s64 v157;
  u64 *v158;
  void *v159;
  Il2CppClass **v160;
  struct Quest *v162;

  v1 = Allocate(System_Collections_Generic_List_string_);
  __ctor(v1);
  v2 = Allocate(System_Collections_Generic_List_Sprite_);
  __ctor(v2);
  IntPara = scrGetIntPara(0);
  Init();
  QuestData = GetQuestData(IntPara);
  v7 = QuestData->edFlag[0];
  if (v7)
  {
    if ((u32)(v7 - 2618) >= 0xFFFFFFC6)
      evtBitKityouItemAdd(v7);
    v9 = (s64)GBWK->EventBit + 4 * (v7 / 32);
    *(u32 *)(v9 + 32) |= 1 << v7;
  }
  rItemID = QuestData->rItemID;
  if (SLODWORD(rItemID->max_length) < 1)
    goto LABEL_45;
  v11 = 8;
  do
  {
    v15 = *((u32 *)&rItemID->obj.klass + v11);
    if (v15)
    {
      v16 = *((u32 *)&QuestData->rItemNum->obj.klass + v11);
      if (v16)
      {
        v15 = *((u32 *)&QuestData->rItemID->obj.klass + v11);
        v16 = *((u32 *)&QuestData->rItemNum->obj.klass + v11);
        v12 = GBWK->player->item[v15];
        if (v16 + v12 <= datGetItemMaxNum(v15))
        {
          rItemID = QuestData->rItemID;
          goto LABEL_19;
        }
        switch (IntPara)
        {
          case ' ':
          case '%':
            returnMapBgm = 1;
            *(u64 *)&mapNo = 9;
            goto LABEL_186;
          case '!':
          case '&':
            returnMapBgm = 1;
            *(u64 *)&mapNo = 0x100000003LL;
            goto LABEL_186;
          default:
LABEL_186:
            isResultRun = 1;
            step = 1;
            mQuest_id = IntPara;
            v129 = *((u32 *)&QuestData->rItemID->obj.klass + v11);
            GBWK->quest_clearSave[IntPara] = 1;
            itfSetTextValue(0, 3, v129, 0);
            Text = itfGetText("QUEST_INFO_L0006");
            iconType = tbldata[*((s32 *)&QuestData->rItemID->obj.klass + v11)]->iconType;
            Instance = get_Instance(0);
            ItmIconSpr = GetItmIconSpr(Instance, iconType, 0);
            size = v1->_size;
            v135 = Method_System_Collections_Generic_List_string__Add__;
            ++v1->_version;
            items = v1->_items;
            if ((u32)size >= LODWORD(items->max_length))
            {
              _AddWithResize(v1, Text, *(const MethodInfo_2DFC660 **)(*(u64 *)(v135[4] + 192) + 112));
            }
            else
            {
              v137 = &items->obj.klass + size;
              v1->_size = size + 1;
              v137[4] = Text;
            }
            v138 = Method_System_Collections_Generic_List_Sprite__Add__;
            v139 = v2->_size;
            ++v2->_version;
            v140 = v2->_items;
            if ((u32)v139 >= LODWORD(v140->max_length))
            {
              _AddWithResize(v2, ItmIconSpr, *(const MethodInfo_2DFC660 **)(*(u64 *)(v138[4] + 192) + 112));
              rDevilFlag = QuestData->rDevilFlag;
              if (SLODWORD(rDevilFlag->max_length) < 1)
                goto LABEL_225;
            }
            else
            {
              v141 = &v140->obj.klass + v139;
              v2->_size = v139 + 1;
              v141[4] = ItmIconSpr;
              rDevilFlag = QuestData->rDevilFlag;
              if (SLODWORD(rDevilFlag->max_length) < 1)
                goto LABEL_225;
            }
            v143 = 8;
            do
            {
              v145 = *((u32 *)&rDevilFlag->obj.klass + v143);
              if (v145 && !evtBitCheck(v145))
              {
                v147 = *((u32 *)&QuestData->rDevilFlag->obj.klass + v143);
                if (v147)
                {
                  if ((u32)(v147 - 2618) >= 0xFFFFFFC6)
                    evtBitKityouItemAdd(v147);
                  v149 = (s64)GBWK->EventBit + 4 * (v147 / 32);
                  *(u32 *)(v149 + 32) |= 1 << v147;
                }
                DevilOpenText = GetDevilOpenText(IntPara);
                v151 = v1->_size;
                v152 = Method_System_Collections_Generic_List_string__Add__;
                ++v1->_version;
                v153 = v1->_items;
                if ((u32)v151 >= LODWORD(v153->max_length))
                {
                  _AddWithResize(v1, DevilOpenText, *(const MethodInfo_2DFC660 **)(*(u64 *)(v152[4] + 192) + 112));
                }
                else
                {
                  v154 = &v153->obj.klass + v151;
                  v1->_size = v151 + 1;
                  v154[4] = DevilOpenText;
                }
                DevilKudaSpr = GetDevilKudaSpr(IntPara);
                v157 = v2->_size;
                v158 = Method_System_Collections_Generic_List_Sprite__Add__;
                ++v2->_version;
                v159 = v2->_items;
                if ((u32)v157 >= LODWORD(v159->max_length))
                {
                  _AddWithResize(v2, DevilKudaSpr, *(const MethodInfo_2DFC660 **)(*(u64 *)(v158[4] + 192) + 112));
                }
                else
                {
                  v160 = &v159->obj.klass + v157;
                  v2->_size = v157 + 1;
                  v160[4] = DevilKudaSpr;
                }
              }
              rDevilFlag = QuestData->rDevilFlag;
              v144 = v143 - 7;
              ++v143;
            }
            while (v144 < SLODWORD(rDevilFlag->max_length));
LABEL_225:
            text = v1;
            v162 = ((char *)v162 + 136);
            *(u32 *)&v162[-1].isResultRun = 0;
            icon = v2;
            dispTime = 1.5;
            CheckClearFlag();
            return 1;
        }
      }
    }
LABEL_19:
    max_length = rItemID->max_length;
    v14 = v11 - 7;
    ++v11;
  }
  while (v14 < (s32)max_length);
  if ((s32)max_length >= 1)
  {
    v18 = 8;
    while (1)
    {
      v20 = *((u32 *)&rItemID->obj.klass + v18);
      if (v20)
      {
        v21 = *((u32 *)&QuestData->rItemNum->obj.klass + v18);
        if (v21)
          break;
      }
LABEL_27:
      rItemID = QuestData->rItemID;
      v19 = v18 - 7;
      ++v18;
      if (v19 >= SLODWORD(rItemID->max_length))
        goto LABEL_45;
    }
    datAddItem(v20, v21);
    v22 = *((u32 *)&QuestData->rItemID->obj.klass + v18);
    itfSetTextValue(0, 3, v22, 0);
    itfSetTextValue(1, 0, *((u32 *)&QuestData->rItemNum->obj.klass + v18), 0);
    v23 = itfGetText("QUEST_INFO_L0002");
    v24 = v1->_size;
    v25 = Method_System_Collections_Generic_List_string__Add__;
    ++v1->_version;
    v26 = v1->_items;
    if ((u32)v24 >= LODWORD(v26->max_length))
    {
      _AddWithResize(v1, v23, *(const MethodInfo_2DFC660 **)(*(u64 *)(v25[4] + 192) + 112));
    }
    else
    {
      v27 = &v26->obj.klass + v24;
      v1->_size = v24 + 1;
      v27[4] = v23;
    }
    v29 = tbldata[*((s32 *)&QuestData->rItemID->obj.klass + v18)]->iconType;
    v30 = get_Instance(0);
    v31 = GetItmIconSpr(v30, v29, 0);
    v32 = v2->_size;
    v33 = Method_System_Collections_Generic_List_Sprite__Add__;
    ++v2->_version;
    v34 = v2->_items;
    if ((u32)v32 >= LODWORD(v34->max_length))
    {
      _AddWithResize(v2, v31, *(const MethodInfo_2DFC660 **)(*(u64 *)(v33[4] + 192) + 112));
    }
    else
    {
      v35 = &v34->obj.klass + v32;
      v2->_size = v32 + 1;
      v35[4] = v31;
    }
    goto LABEL_27;
  }
LABEL_45:
  v36 = QuestData->rDevilFlag;
  if (SLODWORD(v36->max_length) >= 1)
  {
    v37 = 8;
    while (1)
    {
      v39 = *((u32 *)&v36->obj.klass + v37);
      if (v39)
      {
        if (!evtBitCheck(v39))
          break;
      }
LABEL_48:
      v36 = QuestData->rDevilFlag;
      v38 = v37 - 7;
      ++v37;
      if (v38 >= SLODWORD(v36->max_length))
        goto LABEL_66;
    }
    v41 = *((u32 *)&QuestData->rDevilFlag->obj.klass + v37);
    if (!v41)
    {
LABEL_54:
      v43 = GetDevilOpenText(IntPara);
      v44 = v1->_size;
      v45 = Method_System_Collections_Generic_List_string__Add__;
      ++v1->_version;
      v46 = v1->_items;
      if ((u32)v44 >= LODWORD(v46->max_length))
      {
        _AddWithResize(v1, v43, *(const MethodInfo_2DFC660 **)(*(u64 *)(v45[4] + 192) + 112));
      }
      else
      {
        v47 = &v46->obj.klass + v44;
        v1->_size = v44 + 1;
        v47[4] = v43;
      }
      v49 = GetDevilKudaSpr(IntPara);
      v50 = v2->_size;
      v51 = Method_System_Collections_Generic_List_Sprite__Add__;
      ++v2->_version;
      v52 = v2->_items;
      if ((u32)v50 >= LODWORD(v52->max_length))
      {
        _AddWithResize(v2, v49, *(const MethodInfo_2DFC660 **)(*(u64 *)(v51[4] + 192) + 112));
      }
      else
      {
        v53 = &v52->obj.klass + v50;
        v2->_size = v50 + 1;
        v53[4] = v49;
      }
      goto LABEL_48;
    }
    if ((u32)(v41 - 2618) >= 0xFFFFFFC6)
      evtBitKityouItemAdd(v41);
    v55 = (s64)GBWK->EventBit + 4 * (v41 / 32);
    *(u32 *)(v55 + 32) |= 1 << v41;
    goto LABEL_54;
  }
LABEL_66:
  rMoney = QuestData->rMoney;
  datAddMoney(rMoney);
  v57 = QuestData->rMoney;
  if (v57 >= 1)
  {
    itfSetTextValue(0, 0, v57, 1);
    v58 = itfGetText("QUEST_INFO_L0003");
    v59 = v1->_size;
    v60 = Method_System_Collections_Generic_List_string__Add__;
    ++v1->_version;
    v61 = v1->_items;
    if ((u32)v59 >= LODWORD(v61->max_length))
    {
      _AddWithResize(v1, v58, *(const MethodInfo_2DFC660 **)(*(u64 *)(v60[4] + 192) + 112));
    }
    else
    {
      v62 = &v61->obj.klass + v59;
      v1->_size = v59 + 1;
      v62[4] = v58;
    }
    v63 = Method_System_Collections_Generic_List_Sprite__Add__;
    v64 = v2->_size;
    ++v2->_version;
    v65 = v2->_items;
    if ((u32)v64 >= LODWORD(v65->max_length))
    {
      _AddWithResize(v2, 0, *(const MethodInfo_2DFC660 **)(*(u64 *)(v63[4] + 192) + 112));
      rKatana = QuestData->rKatana;
      if (!rKatana)
        goto LABEL_94;
      goto LABEL_79;
    }
    v66 = &v65->obj.klass + v64;
    v2->_size = v64 + 1;
    v66[4] = 0;
  }
  rKatana = QuestData->rKatana;
  if (!rKatana)
    goto LABEL_94;
LABEL_79:
  datAddItem(rKatana, 1);
  v68 = QuestData->rKatana;
  itfSetTextValue(0, 3, v68, 1);
  v69 = itfGetText("QUEST_INFO_L0002");
  v70 = v1->_size;
  v71 = Method_System_Collections_Generic_List_string__Add__;
  ++v1->_version;
  v72 = v1->_items;
  if ((u32)v70 >= LODWORD(v72->max_length))
  {
    _AddWithResize(v1, v69, *(const MethodInfo_2DFC660 **)(*(u64 *)(v71[4] + 192) + 112));
  }
  else
  {
    v73 = &v72->obj.klass + v70;
    v1->_size = v70 + 1;
    v73[4] = v69;
  }
  v75 = tbldata[QuestData->rKatana]->iconType;
  v76 = get_Instance(0);
  v77 = GetItmIconSpr(v76, v75, 0);
  v78 = v2->_size;
  v79 = Method_System_Collections_Generic_List_Sprite__Add__;
  ++v2->_version;
  v80 = v2->_items;
  if ((u32)v78 >= LODWORD(v80->max_length))
  {
    _AddWithResize(v2, v77, *(const MethodInfo_2DFC660 **)(*(u64 *)(v79[4] + 192) + 112));
    if (IntPara != 11)
      goto LABEL_95;
    goto LABEL_106;
  }
  v81 = &v80->obj.klass + v78;
  v2->_size = v78 + 1;
  v81[4] = v77;
LABEL_94:
  if (IntPara != 11)
  {
LABEL_95:
    if (IntPara != 42 && IntPara != 30)
      goto LABEL_130;
    spiritCnt = GBWK->player->spiritCnt;
    v84 = &"QUEST_INFO_L0020";
    if (spiritCnt <= 6)
      v84 = &"QUEST_INFO_L0019";
    v85 = itfGetText(*v84);
    v86 = v1->_size;
    v87 = Method_System_Collections_Generic_List_string__Add__;
    ++v1->_version;
    v88 = v1->_items;
    if ((u32)v86 >= LODWORD(v88->max_length))
    {
      _AddWithResize(v1, v85, *(const MethodInfo_2DFC660 **)(*(u64 *)(v87[4] + 192) + 112));
    }
    else
    {
      v89 = &v88->obj.klass + v86;
      v1->_size = v86 + 1;
      v89[4] = v85;
    }
    v95 = Method_System_Collections_Generic_List_Sprite__Add__;
    v96 = v2->_size;
    ++v2->_version;
    v97 = v2->_items;
    if ((u32)v96 >= LODWORD(v97->max_length))
    {
      _AddWithResize(v2, 0, *(const MethodInfo_2DFC660 **)(*(u64 *)(v95[4] + 192) + 112));
      goto LABEL_116;
    }
    else
    {
      v98 = &v97->obj.klass + v96;
      v2->_size = v96 + 1;
      v98[4] = 0;
      goto LABEL_116;
    }
LABEL_116:
    player = GBWK->player;
    v101 = player->spiritCnt;
    if (v101 <= 7)
    {
      player = GBWK->player;
      v101 = player->spiritCnt;
      player->spiritCnt = v101 + 1;
      goto LABEL_132;
    }
LABEL_130:
    goto LABEL_132;
  }
LABEL_106:
  v90 = itfGetText("QUEST_INFO_L0009");
  v91 = v1->_size;
  v92 = Method_System_Collections_Generic_List_string__Add__;
  ++v1->_version;
  v93 = v1->_items;
  if ((u32)v91 >= LODWORD(v93->max_length))
  {
    _AddWithResize(v1, v90, *(const MethodInfo_2DFC660 **)(*(u64 *)(v92[4] + 192) + 112));
  }
  else
  {
    v94 = &v93->obj.klass + v91;
    v1->_size = v91 + 1;
    v94[4] = v90;
  }
  v105 = Method_System_Collections_Generic_List_Sprite__Add__;
  v106 = v2->_size;
  ++v2->_version;
  v107 = v2->_items;
  if ((u32)v106 < LODWORD(v107->max_length))
  {
    v108 = &v107->obj.klass + v106;
    v2->_size = v106 + 1;
    v108[4] = 0;
    goto LABEL_130;
  }
  _AddWithResize(v2, 0, *(const MethodInfo_2DFC660 **)(*(u64 *)(v105[4] + 192) + 112));
LABEL_132:
  quest_rewardFlag = GBWK->quest_rewardFlag;
  if (quest_rewardFlag[IntPara])
  {
    goto LABEL_134;
  }
  quest_rewardFlag = GBWK->quest_rewardFlag;
  quest_rewardFlag[IntPara] = 1;
LABEL_134:
  GetLocalizeText("QUEST_INFO_L0001", 1);
  text = v1;
  v112 = ((char *)v112 + 136);
  *(u32 *)&v112[-1].isResultRun = 0;
  icon = v2;
  dispTime = 1.5;
  switch (IntPara)
  {
    case ' ':
    case '%':
      v115 = 9;
      goto LABEL_142;
    case '!':
    case '&':
      v115 = 0x100000003LL;
LABEL_142:
      returnMapBgm = 1;
      *(u64 *)&mapNo = v115;
LABEL_143:
      isResultRun = 1;
      step = 1;
      mQuest_id = IntPara;
      GBWK->quest_clearSave[IntPara] = 1;
      CheckClearFlag();
      QuestDataAssetKey = 0;
      QUESTDATA = 0;
      v122 = *((u64 *)Method_AtlUtil_AtSingleton_AtlEnemySymbolManager__get_Instance__ + 4);
      if ((*(u16 *)(v122 + 309) & 1) != 0)
      {
        v123 = *(u64 *)(*(u64 *)(v122 + 192) + 16);
        if ((*(u16 *)(v123 + 309) & 1) != 0)
          goto LABEL_154;
      }
      else
      {
        v123 = *(u64 *)(*(u64 *)(sub_42269C(v122) + 192) + 16);
        if ((*(u16 *)(v123 + 309) & 1) != 0)
        {
LABEL_154:
          v124 = **(void ***)(v123 + 184);
          if (!v124)
            return 1;
          goto LABEL_158;
        }
      }
      v124 = **(void ***)(sub_42269C(v123) + 184);
      if (!v124)
        return 1;
LABEL_158:
      CheckEvFlag(v124, 0);
      break;
    default:
      goto LABEL_143;
  }
  return 1;
}

// 0x1df5590: s32 GET_QUEST_NEED_ITEM_ID(void)
static inline s32 GET_QUEST_NEED_ITEM_ID(void) {
  s32 IntPara;
  s32 v2;
  QUEST_CLASS *QuestData;
  s32 v6;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  Init();
  QuestData = GetQuestData(IntPara);
  switch (v2)
  {
    case 1:
      v6 = QuestData->nItemID[0];
      goto LABEL_18;
    case 2:
      v6 = QuestData->nItemID[1];
      goto LABEL_18;
    case 3:
      v6 = QuestData->nItemID[2];
      goto LABEL_18;
    case 4:
      v6 = QuestData->nItemID[3];
      goto LABEL_18;
    case 5:
      v6 = QuestData->nItemID[4];
LABEL_18:
      scrSetIntReturnValue(v6);
      break;
    default:
      break;
  }
  QuestDataAssetKey = 0;
  QUESTDATA = 0;
  return 1;
}

// 0x1df5770: s32 GET_QUEST_NEED_ITEM_NUM(void)
static inline s32 GET_QUEST_NEED_ITEM_NUM(void) {
  s32 IntPara;
  s32 v2;
  QUEST_CLASS *QuestData;
  s32 v6;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  Init();
  QuestData = GetQuestData(IntPara);
  switch (v2)
  {
    case 1:
      v6 = QuestData->nItemNum[0];
      goto LABEL_18;
    case 2:
      v6 = QuestData->nItemNum[1];
      goto LABEL_18;
    case 3:
      v6 = QuestData->nItemNum[2];
      goto LABEL_18;
    case 4:
      v6 = QuestData->nItemNum[3];
      goto LABEL_18;
    case 5:
      v6 = QuestData->nItemNum[4];
LABEL_18:
      scrSetIntReturnValue(v6);
      break;
    default:
      break;
  }
  QuestDataAssetKey = 0;
  QUESTDATA = 0;
  return 1;
}

// 0x1df5950: s32 GET_QUEST_NEED_DEVIL_ID(void)
static inline s32 GET_QUEST_NEED_DEVIL_ID(void) {
  s32 IntPara;
  s32 v2;
  QUEST_CLASS *QuestData;
  s32 v11;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  Init();
  QuestData = GetQuestData(IntPara);
  if (v2 == 3)
  {
    v11 = QuestData->nDevilID[2];
    goto LABEL_20;
  }
  if (v2 == 2)
  {
    v11 = QuestData->nDevilID[1];
    goto LABEL_20;
  }
  if (v2 != 1)
  {
    goto LABEL_10;
  }
  v11 = QuestData->nDevilID[0];
LABEL_20:
  scrSetIntReturnValue(v11);
LABEL_10:
  QuestDataAssetKey = 0;
  QUESTDATA = 0;
  return 1;
}

// 0x1df5b20: s32 GET_QUEST_NEED_KATANA_ID(void)
static inline s32 GET_QUEST_NEED_KATANA_ID(void) {
  s32 IntPara;
  s32 v2;
  QUEST_CLASS *QuestData;
  s32 v6;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  Init();
  QuestData = GetQuestData(IntPara);
  switch (v2)
  {
    case 1:
      v6 = QuestData->nKatana[0];
      goto LABEL_20;
    case 2:
      v6 = QuestData->nKatana[1];
      goto LABEL_20;
    case 3:
      v6 = QuestData->nKatana[2];
      goto LABEL_20;
    case 4:
      v6 = QuestData->nKatana[3];
      goto LABEL_20;
    case 5:
      v6 = QuestData->nKatana[4];
      goto LABEL_20;
    case 6:
      v6 = QuestData->nKatana[5];
LABEL_20:
      scrSetIntReturnValue(v6);
      break;
    default:
      break;
  }
  QuestDataAssetKey = 0;
  QUESTDATA = 0;
  return 1;
}

// 0x1df5d20: s32 GET_QUEST_ENCOUNT_ID(void)
static inline s32 GET_QUEST_ENCOUNT_ID(void) {
  s32 IntPara;
  s32 v2;
  QUEST_CLASS *QuestData;
  s32 v11;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  Init();
  QuestData = GetQuestData(IntPara);
  if (v2 == 3)
  {
    v11 = QuestData->encountID[2];
    goto LABEL_20;
  }
  if (v2 == 2)
  {
    v11 = QuestData->encountID[1];
    goto LABEL_20;
  }
  if (v2 != 1)
  {
    goto LABEL_10;
  }
  v11 = QuestData->encountID[0];
LABEL_20:
  scrSetIntReturnValue(v11);
LABEL_10:
  QuestDataAssetKey = 0;
  QUESTDATA = 0;
  return 1;
}

// 0x1df5ef0: s32 GET_QUEST_REWARD_ITEM_ID(void)
static inline s32 GET_QUEST_REWARD_ITEM_ID(void) {
  s32 IntPara;
  s32 v2;
  QUEST_CLASS *QuestData;
  s32 v6;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  Init();
  QuestData = GetQuestData(IntPara);
  switch (v2)
  {
    case 1:
      v6 = QuestData->rItemID[0];
      goto LABEL_18;
    case 2:
      v6 = QuestData->rItemID[1];
      goto LABEL_18;
    case 3:
      v6 = QuestData->rItemID[2];
      goto LABEL_18;
    case 4:
      v6 = QuestData->rItemID[3];
      goto LABEL_18;
    case 5:
      v6 = QuestData->rItemID[4];
LABEL_18:
      scrSetIntReturnValue(v6);
      break;
    default:
      break;
  }
  QuestDataAssetKey = 0;
  QUESTDATA = 0;
  return 1;
}

// 0x1df60d0: s32 GET_QUEST_REWARD_ITEM_NUM(void)
static inline s32 GET_QUEST_REWARD_ITEM_NUM(void) {
  s32 IntPara;
  s32 v2;
  QUEST_CLASS *QuestData;
  s32 v6;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  Init();
  QuestData = GetQuestData(IntPara);
  switch (v2)
  {
    case 1:
      v6 = QuestData->rItemNum[0];
      goto LABEL_18;
    case 2:
      v6 = QuestData->rItemNum[1];
      goto LABEL_18;
    case 3:
      v6 = QuestData->rItemNum[2];
      goto LABEL_18;
    case 4:
      v6 = QuestData->rItemNum[3];
      goto LABEL_18;
    case 5:
      v6 = QuestData->rItemNum[4];
LABEL_18:
      scrSetIntReturnValue(v6);
      break;
    default:
      break;
  }
  QuestDataAssetKey = 0;
  QUESTDATA = 0;
  return 1;
}

// 0x1df62b0: s32 GET_QUEST_REWARD_DEVIL_FLAG(void)
static inline s32 GET_QUEST_REWARD_DEVIL_FLAG(void) {
  s32 IntPara;
  s32 v2;
  QUEST_CLASS *QuestData;
  s32 v5;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  Init();
  QuestData = GetQuestData(IntPara);
  if (v2 != 2)
  {
    if (v2 != 1)
      goto LABEL_14;
    v5 = QuestData->rDevilFlag[0];
    goto LABEL_13;
  }
  v5 = QuestData->rDevilFlag[1];
LABEL_13:
  scrSetIntReturnValue(v5);
LABEL_14:
  QuestDataAssetKey = 0;
  QUESTDATA = 0;
  return 1;
}

// 0x1df6450: s32 GET_QUEST_REWARD_MONEY(void)
static inline s32 GET_QUEST_REWARD_MONEY(void) {
  s32 IntPara;
  QUEST_CLASS *QuestData;

  IntPara = scrGetIntPara(0);
  Init();
  QuestData = GetQuestData(IntPara);
  scrSetIntReturnValue(QuestData->rMoney);
  QuestDataAssetKey = 0;
  QUESTDATA = 0;
  return 1;
}

// 0x1df6550: s32 GET_HAVE_SWORD_ID(void)
static inline s32 GET_HAVE_SWORD_ID(void) {
  s32 IntPara;
  s32 v3;
  s32 v4;

  IntPara = scrGetIntPara(0);
  v3 = (u16)GBWK->player->item[IntPara];
  if (v3)
    v4 = IntPara;
  else
    v4 = 0;
  scrSetIntReturnValue(v4);
  return 1;
}

// 0x1df1e00
void Init(void) {
  char *v2;
  void *Asset;
  s64 naturalAligment;
  void *v9;
  QUEST_CLASS *v10;
  s64 v11;
  s32 *v13;
  s64 v14;
  QUEST_CLASS *v15;
  QUEST_CLASS *TblDate;
  QUEST_CLASS *v17;
  s64 v18;
  s64 v19;
  Il2CppClass *v20;
  QUEST_CLASS *QUESTDATA_local;

  v2 = "quest_data";
  QuestDataAssetKey = "quest_data";
  Load(Dependent, QuestDataAssetKey, QuestDataAssetKey);
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  Asset = LoadAsset(_Ctrl_k__BackingField, QuestDataAssetKey, "QuestDataTable", 0);
  {
    if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_QuestDataTable)
      v9 = Asset;
    else
      v9 = 0;
  }
  else
  {
    v9 = 0;
  }
  v10 = NewSpecific(QUEST_CLASS, 0x2Eu);
  QUESTDATA = v10;
  v11 = NewSpecific(QUEST_CLASS, v9->_arrQuest->_size);
  v13 = v11;
  if (v9->_arrQuest->_size >= 1)
  {
    v14 = 0;
    v15 = (v11 + 32);
    do
    {
      TblDate = GetTblDate(v9, v14);
      v17 = TblDate;
      if (TblDate)
        QueryInterface(TblDate, *(void **)(*(u64 *)v13 + 64));
      v15 = v17;
      ++v14;
      ++v15;
    }
    while (v14 < v9->_arrQuest->_size);
  }
  if (v13[6] >= 1)
  {
    v18 = 0;
    v19 = 8;
    do
    {
      v20 = *(Il2CppClass **)&v13[v19];
      QUESTDATA_local = QUESTDATA;
      if (!v20)
      *(Il2CppClass **)((char *)&QUESTDATA_local->obj.klass + v19 * 4) = v20;
      ++v18;
      v19 += 2;
    }
    while (v18 < v13[6]);
  }
  Unload(Dependent, QuestDataAssetKey, 0);
}

// 0x1df22e0
void Delete(void) {
  QuestDataAssetKey = 0;
  QUESTDATA = 0;
}

// 0x1df2360
QUEST_CLASS *GetQuestData(s32 ID) {
  QUEST_CLASS *QUESTDATA_local;

  QUESTDATA_local = (QUEST_CLASS *)QUESTDATA;
  if (!QUESTDATA_local)
    return QUESTDATA_local;
  QUESTDATA_local = *((QUEST_CLASS *)&QUESTDATA_local->edFlag + ID);
  if (!QUESTDATA_local)
    return QUESTDATA_local;
  return QUESTDATA_local;
}

// 0x1df2460
void QuestClearReward(s32 _id) {
  QUEST_CLASS *QuestData;
  s32 *rItemID;
  QUEST_CLASS *v7;
  s64 v8;
  s64 v11;
  s32 v12;
  s32 v13;
  s64 v14;
  il2cpp_array_size_t max_length;
  s64 v16;
  s64 v17;
  s32 v18;
  s32 v19;
  s32 *rDevilFlag;
  s64 v21;
  s64 v23;
  s64 v24;
  s32 v25;
  s32 v26;
  s32 rMoney;
  s32 rKatana;
  bool *quest_readFlag;

  Init();
  QuestData = GetQuestData(id);
  rItemID = QuestData->rItemID;
  v7 = QuestData;
  if (SLODWORD(rItemID->max_length) >= 1)
  {
    v8 = 8;
    do
    {
      rItemID = v7->rItemID;
      v11 = *((s32 *)&rItemID->obj.klass + v8);
      v12 = GBWK->player->item[v11];
      v13 = *((u32 *)&v7->rItemNum->obj.klass + v8);
      if (v13 + v12 > datGetItemMaxNum(v11))
        return;
      rItemID = v7->rItemID;
      v14 = v8 - 7;
      ++v8;
      max_length = rItemID->max_length;
    }
    while (v14 < (s32)max_length);
    if ((s32)max_length >= 1)
    {
      v16 = 8;
      do
      {
        v18 = *((u32 *)&rItemID->obj.klass + v16);
        if (v18)
        {
          v19 = *((u32 *)&v7->rItemNum->obj.klass + v16);
          if (v19)
          {
            datAddItem(v18, v19);
            rItemID = v7->rItemID;
          }
        }
        v17 = v16 - 7;
        ++v16;
      }
      while (v17 < SLODWORD(rItemID->max_length));
    }
  }
  rDevilFlag = v7->rDevilFlag;
  if (SLODWORD(rDevilFlag->max_length) >= 1)
  {
    v21 = 8;
    do
    {
      v25 = *((u32 *)&rDevilFlag->obj.klass + v21);
      if (v25 && !evtBitCheck(v25))
      {
        v26 = *((u32 *)&v7->rDevilFlag->obj.klass + v21);
        if (v26)
        {
          if ((u32)(v26 - 2618) >= 0xFFFFFFC6)
            evtBitKityouItemAdd(v26);
          v23 = (s64)GBWK->EventBit + 4 * (v26 / 32);
          *(u32 *)(v23 + 32) |= 1 << v26;
        }
      }
      rDevilFlag = v7->rDevilFlag;
      v24 = v21 - 7;
      ++v21;
    }
    while (v24 < SLODWORD(rDevilFlag->max_length));
  }
  rMoney = v7->rMoney;
  datAddMoney(rMoney);
  rKatana = v7->rKatana;
  if (rKatana)
  {
    datAddItem(rKatana, 1);
  }
  QuestDataAssetKey = 0;
  QUESTDATA = 0;
  quest_readFlag = GBWK->quest_readFlag;
  if (!quest_readFlag[id])
  {
    quest_readFlag = GBWK->quest_readFlag;
    quest_readFlag[id] = 1;
  }
}

// 0x1df3f30
static char *GetDevilOpenText(s32 ID) {
  char *result;
  char **v5;
  char **v6;
  char *LocalizeText;

  result = "";
  if (ID <= 29)
  {
    switch (ID)
    {
      case 19:
        v5 = &"<DEP_03>";
        v6 = &"QUEST_INFO_L0010";
        break;
      case 23:
        v5 = &"<DEP_05>";
        v6 = &"QUEST_INFO_L0011";
        break;
      case 29:
        v5 = &"<DEP_07>";
        v6 = &"QUEST_INFO_L0012";
        break;
      default:
        return result;
    }
LABEL_15:
    LocalizeText = GetLocalizeText(*v6, 1);
    return Replace_54838864(LocalizeText, *v5, "", 0);
  }
  switch (ID)
  {
    case 31:
      v5 = &"<DEP_06>";
      v6 = &"QUEST_INFO_L0013";
      goto LABEL_15;
    case 35:
      v5 = &"<DEP_06>";
      v6 = &"QUEST_INFO_L0014";
      goto LABEL_15;
    case 40:
      v5 = &"<DEP_07>";
      v6 = &"QUEST_INFO_L0015";
      goto LABEL_15;
    case 43:
      v5 = &"<DEP_06>";
      v6 = &"QUEST_INFO_L0016";
      goto LABEL_15;
    case 44:
      v5 = &"<DEP_01>";
      v6 = &"QUEST_INFO_L0017";
      goto LABEL_15;
    case 45:
      v5 = &"<DEP_02>";
      v6 = &"QUEST_INFO_L0018";
      goto LABEL_15;
    default:
      return result;
  }
  return result;
}

// 0x1df4220
static void *GetDevilKudaSpr(s32 ID) {
  s32 v3;
  void *Instance;

  if (ID > 29)
  {
    switch (ID)
    {
      case 31:
      case 35:
      case 43:
        v3 = 6;
        goto LABEL_7;
      case 40:
        goto LABEL_11;
      case 44:
        v3 = 1;
        goto LABEL_7;
      case 45:
        v3 = 2;
        goto LABEL_7;
      default:
        return 0;
    }
  }
  switch (ID)
  {
    case 19:
      v3 = 3;
      goto LABEL_7;
    case 23:
      v3 = 5;
LABEL_7:
      Instance = get_Instance(0);
      return GetKudaIconSpr(Instance, v3, 0);
    case 29:
LABEL_11:
      v3 = 7;
      goto LABEL_7;
  }
  return 0;
}

// 0x1df47c0
s32 GetQuestType(s32 _id) {
  s32 type;

  Init();
  type = GetQuestData(id)->type;
  QuestDataAssetKey = 0;
  QUESTDATA = 0;
  return type;
}

// 0x1df4890
s32 GetQuestCategory(s32 _id) {
  s32 category;

  Init();
  category = GetQuestData(id)->category;
  QuestDataAssetKey = 0;
  QUESTDATA = 0;
  return category;
}

// 0x1df4960
s32 GetQuestNeedItemID(s32 _id, s32 _no) {
  QUEST_CLASS *QuestData;
  s32 v7;
  s32 result;

  QuestData = GetQuestData(id);
  v7 = no - 1;
  switch (v7)
  {
    case 0:
      result = QuestData->nItemID[0];
      break;
    case 1:
      result = QuestData->nItemID[1];
      break;
    case 2:
      result = QuestData->nItemID[2];
      break;
    case 3:
      result = QuestData->nItemID[3];
      break;
    case 4:
      result = QuestData->nItemID[4];
      break;
    default:
      return 0;
  }
  return result;
}

// 0x1df4a90
s32 GetQuestNeedItemNum(s32 _id, s32 _no) {
  QUEST_CLASS *QuestData;
  s32 v7;
  s32 result;

  QuestData = GetQuestData(id);
  v7 = no - 1;
  switch (v7)
  {
    case 0:
      result = QuestData->nItemNum[0];
      break;
    case 1:
      result = QuestData->nItemNum[1];
      break;
    case 2:
      result = QuestData->nItemNum[2];
      break;
    case 3:
      result = QuestData->nItemNum[3];
      break;
    case 4:
      result = QuestData->nItemNum[4];
      break;
    default:
      return 0;
  }
  return result;
}

// 0x1df4bc0
s32 GetQuestNeedDevilID(s32 _id, s32 _no) {
  QUEST_CLASS *QuestData;
  s32 v8;

  Init();
  QuestData = GetQuestData(id);
  if (no == 3)
  {
    v8 = QuestData->nDevilID[2];
    goto LABEL_16;
  }
  if (no == 2)
  {
    v8 = QuestData->nDevilID[1];
    goto LABEL_16;
  }
  else if (no == 1)
  {
    v8 = QuestData->nDevilID[0];
    goto LABEL_16;
  }
  else
  {
    v8 = 0;
    goto LABEL_16;
  }
LABEL_16:
  QuestDataAssetKey = 0;
  QUESTDATA = 0;
  return v8;
}

// 0x1df4d40
s32 GetQuestNeedKatanaID(s32 _id, s32 _no) {
  QUEST_CLASS *QuestData;
  s32 v8;
  s32 v9;

  Init();
  QuestData = GetQuestData(id);
  v8 = no - 1;
  goto LABEL_4;
  if ((u32)(no - 1) <= 5)
  {
LABEL_4:
    switch (v8)
    {
      case 0:
        v9 = QuestData->nKatana[0];
        break;
      case 1:
        v9 = QuestData->nKatana[1];
        break;
      case 2:
        v9 = QuestData->nKatana[2];
        break;
      case 3:
        v9 = QuestData->nKatana[3];
        break;
      case 4:
        v9 = QuestData->nKatana[4];
        break;
      case 5:
        v9 = QuestData->nKatana[5];
        break;
      default:
        goto LABEL_9;
    }
    goto LABEL_21;
  }
LABEL_9:
  v9 = 0;
LABEL_21:
  QuestDataAssetKey = 0;
  QUESTDATA = 0;
  return v9;
}

// 0x1df4f10
s32 GetQuestEncountID(s32 _id, s32 _no) {
  QUEST_CLASS *QuestData;
  s32 v8;

  Init();
  QuestData = GetQuestData(id);
  if (no == 3)
  {
    v8 = QuestData->encountID[2];
    goto LABEL_16;
  }
  if (no == 2)
  {
    v8 = QuestData->encountID[1];
    goto LABEL_16;
  }
  else if (no == 1)
  {
    v8 = QuestData->encountID[0];
    goto LABEL_16;
  }
  else
  {
    v8 = 0;
    goto LABEL_16;
  }
LABEL_16:
  QuestDataAssetKey = 0;
  QUESTDATA = 0;
  return v8;
}

// 0x1df5090
s32 GetQuestRewardItemID(s32 _id, s32 _no) {
  QUEST_CLASS *QuestData;
  s32 v7;
  s32 result;

  QuestData = GetQuestData(id);
  v7 = no - 1;
  switch (v7)
  {
    case 0:
      result = QuestData->rItemID[0];
      break;
    case 1:
      result = QuestData->rItemID[1];
      break;
    case 2:
      result = QuestData->rItemID[2];
      break;
    case 3:
      result = QuestData->rItemID[3];
      break;
    case 4:
      result = QuestData->rItemID[4];
      break;
    default:
      return 0;
  }
  return result;
}

// 0x1df51c0
s32 GetQuestRewardItemNum(s32 _id, s32 _no) {
  QUEST_CLASS *QuestData;
  s32 v7;
  s32 result;

  QuestData = GetQuestData(id);
  v7 = no - 1;
  switch (v7)
  {
    case 0:
      result = QuestData->rItemNum[0];
      break;
    case 1:
      result = QuestData->rItemNum[1];
      break;
    case 2:
      result = QuestData->rItemNum[2];
      break;
    case 3:
      result = QuestData->rItemNum[3];
      break;
    case 4:
      result = QuestData->rItemNum[4];
      break;
    default:
      return 0;
  }
  return result;
}

// 0x1df52f0
s32 GetQuestRewardDevilFlag(s32 _id, s32 _no) {
  QUEST_CLASS *QuestData;
  s32 v8;

  Init();
  QuestData = GetQuestData(id);
  if (no == 2)
  {
    v8 = QuestData->rDevilFlag[1];
    goto LABEL_13;
  }
  if (no == 1)
  {
    v8 = QuestData->rDevilFlag[0];
    goto LABEL_13;
  }
  else
  {
    v8 = 0;
    goto LABEL_13;
  }
LABEL_13:
  QuestDataAssetKey = 0;
  QUESTDATA = 0;
  return v8;
}

// 0x1df5450
s32 GetQuestRewardMoney(s32 _id) {
  return GetQuestData(id)->rMoney;
}

// 0x1df54c0
s32 GetQuestRewardKatana(s32 _id) {
  s32 rKatana;

  Init();
  rKatana = GetQuestData(id)->rKatana;
  QuestDataAssetKey = 0;
  QUESTDATA = 0;
  return rKatana;
}

// 0x1df6620
bool ChackRewardReceive(s32 _id) {
  QUEST_CLASS *QuestData;
  s32 *rItemID;
  QUEST_CLASS *v7;
  s64 i;
  s64 v9;
  s32 v10;
  s32 v11;
  s32 v13;

  Init();
  QuestData = GetQuestData(id);
  rItemID = QuestData->rItemID;
  if (SLODWORD(rItemID->max_length) < 1)
    return 1;
  v7 = QuestData;
  for (i = 8; ; ++i)
  {
    v10 = *((u32 *)&rItemID->obj.klass + i);
    if (!v10)
      goto LABEL_7;
    v11 = *((u32 *)&v7->rItemNum->obj.klass + i);
    if (!v11)
      goto LABEL_7;
    v10 = *((u32 *)&v7->rItemID->obj.klass + i);
    v11 = *((u32 *)&v7->rItemNum->obj.klass + i);
    v13 = GBWK->player->item[v10];
    if (v11 + v13 > datGetItemMaxNum(v10))
      break;
    rItemID = v7->rItemID;
LABEL_7:
    v9 = i - 7;
    if (v9 >= SLODWORD(rItemID->max_length))
      return 1;
  }
  return 0;
}

// 0x1df4420
s32 CheckClearFlag(void) {
  s32 v1;
  s64 v2;
  s32 v4;
  bool *quest_clearSave;
  void *achievementTbl_k__BackingField;
  Project_DefineAchievementID_string__c *klass;
  s64 v10;
  Project_DefineAchievementID_string__c **p_offset;
  s64 v12;
  char *v13;
  void *v16;
  Project_DefineAchievementID_string__c *v17;
  s64 v18;
  Project_DefineAchievementID_string__c **v19;
  s64 v20;
  char *v21;
  void *v24;
  Project_DefineAchievementID_string__c *v25;
  s64 v26;
  Project_DefineAchievementID_string__c **v27;
  s64 v28;
  char *v29;

  v1 = 0;
  v2 = 33;
  while (1)
  {
    quest_clearSave = GBWK->quest_clearSave;
    if (v2 - 32 >= SLODWORD(quest_clearSave->max_length))
      break;
    quest_clearSave = GBWK->quest_clearSave;
    v4 = *((u8 *)&quest_clearSave->obj.klass + v2++);
    v1 += v4;
  }
  if (v1 >= 1)
  {
    achievementTbl_k__BackingField = _achievementTbl_k__BackingField;
    klass = achievementTbl_k__BackingField->klass;
    v10 = *(u16 *)&achievementTbl_k__BackingField->klass->_2.rank;
    if (!*(u16 *)&achievementTbl_k__BackingField->klass->_2.rank)
      goto LABEL_22;
    goto LABEL_19;
    if (!*(u16 *)&achievementTbl_k__BackingField->klass->_2.rank)
    {
LABEL_22:
      v12 = sub_4227F4(achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 0x28u);
      goto LABEL_24;
    }
LABEL_19:
    p_offset = &klass->_1.interfaceOffsets->offset;
    while (*(p_offset - 1) != Project_DefineAchievementID_string_)
    {
      p_offset += 2;
      if (!--v10)
        goto LABEL_22;
    }
    v12 = (&klass[1]._1.fields + 2 * *(u32 *)p_offset);
LABEL_24:
    v13 = (*v12)(achievementTbl_k__BackingField, *(u64 *)(v12 + 8));
    Unlock_2(v13);
    if (v1 < 45)
      goto LABEL_39;
    v16 = _achievementTbl_k__BackingField;
    v17 = v16->klass;
    v18 = *(u16 *)&v16->klass->_2.rank;
    if (!*(u16 *)&v16->klass->_2.rank)
      goto LABEL_36;
    goto LABEL_33;
    if (!*(u16 *)&v16->klass->_2.rank)
    {
LABEL_36:
      v20 = sub_4227F4(v16, Project_DefineAchievementID_string_, 0x29u);
LABEL_38:
      v21 = (*v20)(v16, *(u64 *)(v20 + 8));
      Unlock_2(v21);
      goto LABEL_39;
    }
LABEL_33:
    v19 = &v17->_1.interfaceOffsets->offset;
    while (*(v19 - 1) != Project_DefineAchievementID_string_)
    {
      v19 += 2;
      if (!--v18)
        goto LABEL_36;
    }
    v20 = (&v17[1]._1.properties + 2 * *(u32 *)v19);
    goto LABEL_38;
  }
LABEL_39:
  v24 = _achievementTbl_k__BackingField;
  v25 = v24->klass;
  v26 = *(u16 *)&v24->klass->_2.rank;
  if (!*(u16 *)&v24->klass->_2.rank)
    goto LABEL_50;
  goto LABEL_47;
  if (!*(u16 *)&v24->klass->_2.rank)
  {
LABEL_50:
    v28 = sub_4227F4(v24, Project_DefineAchievementID_string_, 0x29u);
    goto LABEL_52;
  }
LABEL_47:
  v27 = &v25->_1.interfaceOffsets->offset;
  while (*(v27 - 1) != Project_DefineAchievementID_string_)
  {
    v27 += 2;
    if (!--v26)
      goto LABEL_50;
  }
  v28 = (&v25[1]._1.properties + 2 * *(u32 *)v27);
LABEL_52:
  v29 = (*v28)(v24, *(u64 *)(v28 + 8));
  ProgressUnlock_3(v29, v1, 45);
  return 0;
}

// 0x1df6770
void DrawCherryBlossomEff(void) {
  if (!hEff)
    return;
  dds3EffectSetRGBA(hEff, 0x80808080);
  OT = 8;
  dds3EffectDraw(hEff);
  OT = 12;
}

// 0x1df68c0
void LoadCherryBlossomEff(const sdfVector4_t *effPos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v7;
  f32 v8;
  f32 v9;
  f32 *static_fields;
  fileHandle_t *v12;
  void *topPtr;
  void *data;
  effHandle_t *EPL;
  sdfVector4_t v18;

  w = effPos->w;
  z = effPos->z;
  y = effPos->y;
  x = effPos->x;
  v7 = y * -100.0;
  v8 = z * -100.0;
  v9 = (f32)(x + -5.0) * -100.0;
  static_fields[27] = v9;
  static_fields[28] = v7;
  static_fields[29] = v8;
  v12 = fileLoad("fld_all", "EFF_TES");
  fileSync(v12);
  topPtr = v12->topPtr;
  data = topPtr[1].klass->_1.byval_arg.data;
  EPL = dds3EffectLoadEPL(data);
  hEff = EPL;
  fileHandleFree(v12);
  Reset(hEff, 0);
  v18.x = v9;
  v18.y = v7;
  v18.z = v8;
  v18.w = w * -100.0;
  dds3EffectSetPosition(hEff, v18);
  dds3EffectSetLoop(hEff, 1u);
  dds3EffectSetScale(hEff, 1.5);
}

// 0x1df6ae0
void DeleteCherryBlossomEff(void) {
  if (hEff)
    goto LABEL_4;
  return;
  if (hEff)
  {
LABEL_4:
    Delete(hEff);
    hEff = 0;
    return;
  }
}

// 0x1df6be0
bool CheckResultRun(void) {
  return isResultRun;
}

// 0x1df3eb0
void StartQuestResult(s32 quest_id) {
  mQuest_id = quest_id;
  isResultRun = 1;
  step = 1;
}

// 0x1df4370
void SetPopUp(void *txt, f32 time, void *spr) {
  struct Quest *static_fields;

  text = txt;
  static_fields = ((char *)static_fields + 136);
  *(u32 *)&static_fields[-1].isResultRun = 0;
  icon = spr;
  dispTime = time;
}

// 0x1df6c60
void SetPopUpOver(char *txt, f32 time, void *spr) {
  struct Quest *static_fields;

  textSingle = txt;
  static_fields = ((char *)static_fields + 152);
  HIDWORD(static_fields[-1].iconSingle) = 1;
  iconSingle = spr;
  dispTime = time;
}

// 0x1df6d10
void StartPopup(void) {
  s32 v2;
  void *v3;
  char *v4;
  void *v5;
  char *LocalizeText;
  void *v9;

  goto LABEL_3;
LABEL_16:
  if (instance)
  {
    LocalizeText = GetLocalizeText("QUEST_INFO_L0001", 1);
    ReqDrawGetRewardTextSingle(instance, LocalizeText, 1.5, 0, 0);
  }
  v9 = instance;
  if (!v9)
    return;
  ReqDrawGetRewardTextL(v9, text, dispTime, icon, 0);
  return;
LABEL_3:
  v2 = (u8)byte_5756E7C;
  if (!popType)
    goto LABEL_16;
  v3 = instance;
  if (v3)
  {
    v4 = GetLocalizeText("QUEST_INFO_L0001", 1);
    ReqDrawGetRewardTextSingle(v3, v4, 1.5, 0, 0);
  }
  v5 = instance;
  if (!v5)
    return;
  ReqDrawGetRewardTextSingle(v5, textSingle, dispTime, iconSingle, 0);
}

// 0x1df3e30
void SetReturnMapBgm(s32 map, s32 floor, bool flag) {
  mapNo = map;
  floorNo = floor;
  returnMapBgm = flag;
}

// 0x1df6fb0
static s32 GetFldCamera(void) {
  void *v6;
  void *camera;
  void *v11;

  if (op_Equality(fldCam, 0, 0))
    goto LABEL_9;
  v6 = fldCam;
  camera = cameraObject->_camera;
  if (op_Inequality(v6, camera, 0))
    goto LABEL_9;
  return 0;
  if (op_Inequality(v6, camera, 0))
  {
LABEL_9:
    v11 = cameraObject->_camera;
    fldCam = v11;
    return 1;
  }
  return 0;
}

// 0x1df71b0
static void SetCameraStack(void *setCam) {
  void *UniversalAdditionalCameraData;
  void *cameraStack;
  void *v10;
  u64 *v11;
  s64 size;
  void *items;
  Il2CppClass **v14;

  if (op_Equality(fldCam, 0, 0))
    return;
  if (op_Equality(setCam, 0, 0))
    return;
  UniversalAdditionalCameraData = GetUniversalAdditionalCameraData(fldCam, 0);
  cameraStack = get_cameraStack(UniversalAdditionalCameraData, 0);
  if (!_Contains(cameraStack, setCam))
  {
    v10 = get_cameraStack(UniversalAdditionalCameraData, 0);
    v11 = Method_System_Collections_Generic_List_Camera__Add__;
    size = v10->_size;
    ++v10->_version;
    items = v10->_items;
    if ((u32)size >= LODWORD(items->max_length))
    {
      _AddWithResize(v10, setCam, *(const MethodInfo_2DFC660 **)(*(u64 *)(v11[4] + 192) + 112));
    }
    else
    {
      v14 = &items->obj.klass + size;
      v10->_size = size + 1;
      v14[4] = setCam;
    }
  }
}

// 0x1df73b0
static void DeleteCameraStack(void *deleteCam) {
  void *UniversalAdditionalCameraData;
  s32 v9;
  s32 v10;
  void *cameraStack;
  Il2CppObject *Item;
  void *v13;

  if (op_Equality(fldCam, 0, 0))
    return;
  if (op_Equality(deleteCam, 0, 0))
    return;
  UniversalAdditionalCameraData = GetUniversalAdditionalCameraData(fldCam, 0);
  if (get_cameraStack(UniversalAdditionalCameraData, 0)->_size >= 1)
  {
    v9 = 0;
    v10 = -1;
    do
    {
      cameraStack = get_cameraStack(UniversalAdditionalCameraData, 0);
      Item = _get_Item(cameraStack, v9);
      if (op_Equality(Item, deleteCam, 0))
        v10 = v9;
      ++v9;
    }
    while (v9 < get_cameraStack(UniversalAdditionalCameraData, 0)->_size);
    if (v10 != -1)
    {
      v13 = get_cameraStack(UniversalAdditionalCameraData, 0);
      _RemoveAt(v13, v10);
    }
  }
}

// 0x1df7600
static void SetResultCameraPos(const sdfVector4_t *camPos) {
  f32 z;
  f32 y;
  f32 x;
  f32 v7;
  f32 v8;
  f32 v9;
  void *transform;
  sdfVector3_t v11;

  z = camPos->z;
  y = camPos->y;
  x = camPos->x;
  v7 = y + gapCamPos.y;
  v8 = x + gapCamPos.x;
  v9 = z + gapCamPos.z;
  transform = get_transform(cherryBlossomCam, 0);
  v11.y = v7;
  v11.z = v9;
  v11.x = v8;
  set_position(transform, v11, 0);
}

// 0x1df76b0
static void SetFieldUiActive(bool active) {
  void *destUpdateObj;

  fldFieldDispUI(active);
  if (active)
  {
    evtMoonEnableDraw();
LABEL_13:
    itfPreDrawActionWndDisp(active);
    if (active)
      return;
    goto LABEL_16;
  }
  evtMoonDisableDraw(1);
  goto LABEL_13;
LABEL_16:
  if (!evtBitCheck(2223))
  {
    destUpdateObj = fldUI->destUpdateObj;
    fldSetupObject(destUpdateObj, 0);
    return;
  }
}

// 0x1df7830
void MainProcess(void) {
  s32 v7;
  f32 v8;
  f32 v10;
  f32 v13;
  f32 v14;

  if (!step)
    return;
  if (step != 5)
  {
    if (fieldUiDisable)
    {
      if (fldProcCheckFlag(0x40u))
      {
        fldReleaseUnitPadOnly();
        SetFieldUiActive(0);
        GuideDispStop(0);
      }
    }
  }
  switch (step)
  {
    case 1:
      QuestResultInit();
      goto LABEL_44;
    case 2:
      EffectIn();
      goto LABEL_44;
    case 3:
      QuestResultDraw();
      goto LABEL_44;
    case 4:
      EffectOut();
      goto LABEL_42;
    case 5:
      QuestResultEnd();
LABEL_44:
      v7 = step;
      if (!v7)
        goto LABEL_74;
      if (v7 == 1)
        goto LABEL_74;
      v7 = step;
      if (v7 != 5)
      {
        v8 = *(f32 *)&_get_Instance()[4].monitor;
        v10 = v8 / 60.0;
        if (v10 <= timer)
        {
          if (sePlay)
          {
            sBtlPlaySE(0x10025u);
            sePlay = 0;
          }
        }
        v13 = *((f32 *)&_get_Instance()[4].monitor + 1);
        v14 = v13 / 60.0;
        if (v14 <= timer)
        {
          if (voicePlay)
          {
            sndVoicePlayFile("PVA02A_10_016", 0);
            voicePlay = 0;
          }
        }
      }
LABEL_74:
      if (timer < 5.0)
        return;
      if (fieldUiDisable)
      {
        isResultRun = 0;
        StartPopup();
        fldRegistUnitPad();
        SetFieldUiActive(1);
        fieldUiDisable = 0;
      }
      break;
    default:
LABEL_42:
      goto LABEL_44;
  }
}

// 0x1df7d10
static void QuestResultInit(void) {
  Il2CppObject *Instance;
  Il2CppObject *v3;
  char *LocalizeText;
  char *v5;
  char *v6;
  char *v7;
  char *v9;
  char *v10;
  char **v11;
  char *v12;
  Il2CppObject *v14;
  char *v15;
  char *v16;
  char *v17;
  Il2CppObject *v18;
  void *monitor;
  struct Quest *static_fields;
  f32 x;
  f32 y;
  f32 z;
  f32 v27;
  f32 v28;
  f32 v29;
  void *transform;
  Il2CppClass *klass;
  f32 v38;
  const MethodInfo_32670E0 *v39;
  f32 v40;
  const MethodInfo_32670E0 *v41;
  f32 v42;
  f32 v44;
  s32 data;
  sdfVector3_t v52;

  fldReleaseUnitPadOnly();
  Instance = _get_Instance();
  ResultObjActive(Instance, 1);
  v3 = _get_Instance();
  LocalizeText = GetLocalizeText("QUEST_INFO_L0001", 1);
  (*(v3[4].klass->_1.image + 171))(v3[4].klass, LocalizeText, *((u64 *)v3[4].klass->_1.image + 172));
  v5 = "";
  v6 = GetLocalizeText("QUEST_TITLE_L0050", 1);
  v7 = Concat_54766928(v5, v6, 0);
  v9 = ToString_55996800((u32)Quest->static_fields + 184, "d2", 0);
  v10 = Concat_54766928(v7, v9, 0);
  v11 = &"　";
  if (GetLanguageTYPE() != 2)
  {
    if (GetLanguageTYPE() != 1)
      v11 = &" ";
  }
  v12 = Concat_54766928(v10, *v11, 0);
  data = mQuest_id;
  v14 = Box(s32, &data);
  v15 = Format("QUEST_TITLE_L{0:D4}", v14, 0);
  v16 = GetLocalizeText(v15, 1);
  v17 = Concat_54766928(v12, v16, 0);
  v18 = _get_Instance();
  (*(v18[7].klass->_1.image + 171))(v18[7].klass, v17, *((u64 *)v18[7].klass->_1.image + 172));
  monitor = _get_Instance()[5].monitor;
  cherryBlossomCam = monitor;
  x = effPos.x;
  y = effPos.y;
  z = effPos.z;
  v27 = y + gapCamPos.y;
  v28 = x + gapCamPos.x;
  v29 = z + gapCamPos.z;
  transform = get_transform(cherryBlossomCam, 0);
  v52.x = v28;
  v52.y = v27;
  v52.z = v29;
  set_position(transform, v52, 0);
  klass = _get_Instance()[5].klass;
  bgCam = klass;
  if (GetFldCamera())
  {
    SetCameraStack(bgCam);
    SetCameraStack(cherryBlossomCam);
  }
  LoadCherryBlossomEff(*((sdfVector4_t *)*((const MethodInfo *)Quest + 2).virtualMethodPointer + 5));
  v38 = *(f32 *)&_get_Instance()[6].klass;
  v39 = Method_Project_SingletonMonoBehaviour_QuestResultManager__get_Instance__;
  lifeTime = v38 / 60.0;
  v40 = *((f32 *)&_get_Instance(v39)[6].klass + 1) / 60.0;
  v41 = Method_Project_SingletonMonoBehaviour_QuestResultManager__get_Instance__;
  inTime = v40;
  v42 = *(f32 *)&_get_Instance(v41)[6].monitor / 60.0;
  v44 = lifeTime + inTime;
  *(u16 *)&sePlay = 257;
  outTime = v42;
  totalTime = (f32)(v42 + v44) + 0.2;
  SetFieldUiActive(0);
  GuideDispStop(0);
  fieldUiDisable = 1;
  sndSeLoadId(220);
  if (sndSeStatus() == 2)
  {
    if (returnMapBgm)
    {
      if (mapNo != -1)
      {
        if (floorNo != -1)
        {
          at3_bgm_request_flag = 1;
          sndBgmFadeOut();
        }
      }
    }
    sndSePlay(0);
    step = 2;
    return;
  }
}

// 0x1df82f0
static void EffectIn(void) {
  f32 v2;
  f32 v5;
  f32 v6;
  f32 y;
  f32 z;
  f32 v10;
  f32 v12;
  Il2CppObject *Instance;
  sdfVector4_t v17;

  v2 = 0.0;
  v5 = timer + VRF_DeltaTime;
  timer = v5;
  if (inTime != 0.0)
  {
    v6 = v5 / inTime;
    v2 = v6 <= 1.0 ? v6 : 1.0;
    if (v6 < 0.0)
      v2 = 0.0;
  }
  y = slidePos.y;
  z = slidePos.z;
  if (v2 >= 0.0)
    v10 = v2;
  else
    v10 = 0.0;
  ratio = v10;
  if (v10 <= 1.0)
    v12 = 500.0 - (f32)(v10 * 500.0);
  else
    v12 = 0.0;
  slidePos.x = v12;
  v17.w = 0.0;
  v17.x = v12;
  v17.y = y;
  v17.z = z;
  dds3EffectSetPosition(hEff, v17);
  DrawCherryBlossomEff();
  if (timer >= (f32)(inTime + 0.2))
  {
    Instance = _get_Instance();
    ResultObjAnimOn(Instance);
    step = 3;
  }
}

// 0x1df8490
static void QuestResultDraw(void) {
  *((f32 *)*((const MethodInfo *)Quest + 2).virtualMethodPointer + 18) = *((f32 *)*((const MethodInfo *)Quest + 2).virtualMethodPointer + 18)
                                              + VRF_DeltaTime;
  if (GetFldCamera())
  {
    SetCameraStack(cherryBlossomCam);
    SetCameraStack(bgCam);
  }
  DrawCherryBlossomEff();
  if (timer >= lifeTime)
  {
    step = 4;
  }
}

// 0x1df85a0
static void EffectOut(void) {
  f32 v2;
  f32 v5;
  f32 v6;
  f32 y;
  f32 z;
  f32 v10;
  f32 v12;
  s32 BgmId;
  sdfVector4_t v19;

  v2 = 0.0;
  v5 = timer + VRF_DeltaTime;
  timer = v5;
  if (outTime != 0.0)
  {
    v6 = v5 / outTime;
    v2 = v6 <= 1.0 ? v6 : 1.0;
    if (v6 < 0.0)
      v2 = 0.0;
  }
  y = slidePos.y;
  z = slidePos.z;
  if (v2 >= 0.0)
    v10 = v2;
  else
    v10 = 0.0;
  ratio = v10;
  if (v10 <= 1.0)
    v12 = (f32)(v10 * 500.0) + 0.0;
  else
    v12 = 500.0;
  slidePos.x = v12;
  v19.w = 0.0;
  v19.x = v12;
  v19.y = y;
  v19.z = z;
  dds3EffectSetPosition(hEff, v19);
  DrawCherryBlossomEff();
  if ((f32)(totalTime + 2.0) <= timer)
  {
    if (returnMapBgm)
    {
      if (mapNo != -1)
      {
        if (floorNo != -1)
        {
          mapSeKankyoFadeOut(1);
          mapSeKankyoFadeIn(1);
          BgmId = mapSoundGetBgmId(mapNo, floorNo);
          sndBgmLoadId_XF(BgmId);
          sndBgmPlay(BgmId, 0);
          returnMapBgm = 0;
        }
      }
    }
  }
  if ((f32)(totalTime + 4.6) <= timer)
  {
    step = 5;
  }
}

// 0x1df8850
static void QuestResultEnd(void) {
  struct Quest *static_fields;

  DeleteCameraStack(cherryBlossomCam);
  DeleteCameraStack(bgCam);
  DeleteCherryBlossomEff();
  fldCam = 0;
  static_fields = ((char *)static_fields + 32);
  LOWORD(effPos.z) = 0;
  bgCam = 0;
  cherryBlossomCam = 0;
  returnMapBgm = 0;
  *(u64 *)&lifeTime = 0;
  *(u64 *)&outTime = 0;
  timer = 0.0;
  *(u64 *)&mapNo = -1;
  step = 0;
}
