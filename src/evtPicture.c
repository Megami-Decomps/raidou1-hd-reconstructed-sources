#include "types.h"
#include "CutInType.h"
#include "EVT_PICTURE_TYPE.h"
#include "achievement.h"
#include "callbackDelegate.h"
#include "cmpitem.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "evtbit.h"
#include "evtpicture.h"
#include "file.h"
#include "itfmisc.h"
#include "kernel.h"
#include "movie.h"
#include "sbtlcontinue.h"
#include "scr.h"
#include "sdfdraw.h"
#include "sdfsystem.h"

#define ANIMATION_FRAME 5
#define ANIMATION_FADE 30

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct evtPictureProcessData_t evtPictureProcessData_t;
typedef struct fileHandle_t fileHandle_t;

DDS3_OT gPictureOtEx;
static bool zyarEnd;
static void *uiObj;
static bool updateFlag;
s32 msg_logFlag;

static s32 GetGameObj(void);
static bool SkipChk(evtPictureProcessData_t *data);
static evtPictureProcessData_t *InitProcessData(void);
static void LoadTexture(evtPictureProcessData_t *data, char *texpath);
static s32 GetNowFrame(evtPictureProcessData_t *data);
static void Animation(evtPictureProcessData_t *data);
static void Draw(evtPictureProcessData_t *data);
static void DissolveCalc(evtPictureProcessData_t *data, void *img);
static bool IsEventTitle(evtPictureProcessData_t *data);
static dds3ProcessFunc_t Process1(dds3ProcessID_t *id);
static void Shutdown(dds3ProcessID_t *id);
static void LoadTexCallback(fileHandle_t *fh, void *pParam);

// 0x1a27e80
void evtPictureSetUI(void *obj) {
  uiObj = obj;
}

// 0x1a27ee0
static s32 GetGameObj(void) {
  s64 v1;
  s64 max_length;

  if ((s32)uiObj->pictureObj->max_length < 1)
  {
LABEL_7:
    LODWORD(v1) = 0;
  }
  else
  {
    v1 = 0;
    max_length = (u32)uiObj->pictureObj->max_length;
    while (get_activeSelf(uiObj->pictureObj[v1], 0))
    {
      if (max_length == ++v1)
        goto LABEL_7;
    }
  }
  return v1;
}

// 0x1a27f90
bool *evtPictureGameObjDisp(bool disp, bool *act) {
  bool *v5;

  v5 = NewSpecific(bool, 4u);
  if (disp)
  {
    updateFlag = 0;
    if (act[0] && !get_activeSelf(uiObj->pictureObj[0], 0))
    {
      SetActive(uiObj->pictureObj[0], 1, 0);
    }
    if (act[1] && !get_activeSelf(uiObj->pictureObj[1], 0))
    {
      SetActive(uiObj->pictureObj[1], 1, 0);
    }
    if (act[2] && !get_activeSelf(uiObj->pictureObj[2], 0))
    {
      SetActive(uiObj->pictureObj[2], 1, 0);
    }
    if (!act[3] || get_activeSelf(uiObj->pictureObj[3], 0))
    {
      return v5;
    }
  }
  else
  {
    updateFlag = 1;
    if (get_activeSelf(uiObj->pictureObj[0], 0))
    {
      v5[0] = 1;
      SetActive(uiObj->pictureObj[0], 0, 0);
    }
    if (get_activeSelf(uiObj->pictureObj[1], 0))
    {
      v5[1] = 1;
      SetActive(uiObj->pictureObj[1], 0, 0);
    }
    if (get_activeSelf(uiObj->pictureObj[2], 0))
    {
      v5[2] = 1;
      SetActive(uiObj->pictureObj[2], 0, 0);
    }
    if (!get_activeSelf(uiObj->pictureObj[3], 0))
      return v5;
    v5[3] = 1;
  }
  SetActive(uiObj->pictureObj[3], disp, 0);
  return v5;
}

// 0x1a28250
static bool SkipChk(evtPictureProcessData_t *data) {
  void *tex3d;
  void *tex2d;

  if (!data->ui_mode)
  {
    tex2d = data->tex2d;
    if (op_Equality(data->tex2d, 0, 0))
      return 0;
    if ((data->tex2d->klass->vtable._5_get_width.methodPtr)(data->tex2d, data->tex2d->klass->vtable._5_get_width.method) == 1920 && (data->tex2d->klass->vtable._7_get_height.methodPtr)(data->tex2d, data->tex2d->klass->vtable._7_get_height.method) == 1080)
    {
      return 0;
    }
    goto LABEL_18;
  }
  tex3d = data->tex3d;
  if (op_Equality(data->tex3d, 0, 0))
    return 0;
  if ((data->tex3d->klass->vtable._5_get_width.methodPtr)(data->tex3d, data->tex3d->klass->vtable._5_get_width.method) == 1920 && (data->tex3d->klass->vtable._7_get_height.methodPtr)(data->tex3d, data->tex3d->klass->vtable._7_get_height.method) == 1080)
  {
    return 0;
  }
LABEL_18:
  return scrIsEventSkip(0);
}

// 0x1a283e0
void evtPictureDrawOn(dds3ProcessID_t *id) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *ida;

  ida = id;
  ProcessData = dds3GetProcessData(ida);
  if (!ProcessData)
  LODWORD(ProcessData[1].klass) |= 1u;
}

// 0x1a284c0
void evtPictureDrawOff(dds3ProcessID_t *id) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *ida;

  ida = id;
  ProcessData = dds3GetProcessData(ida);
  if (!ProcessData)
  LODWORD(ProcessData[1].klass) &= ~1u;
}

// 0x1a285a0
void KillProcess(dds3ProcessID_t *id) {
  dds3ProcessID_t *ida;

  ida = id;
  dds3KillProcess(ida, 1);
}

// 0x1a28610
static evtPictureProcessData_t *InitProcessData(void) {
  evtPictureProcessData_t *v1;
  s64 v14;
  s64 max_length;
  sdfIVector4_t v17;
  sdfIVector4_t v18;
  sdfIVector4_t v19;
  sdfIVector4_t v20;
  sdfIVector4_t v21;
  sdfIVector4_t v22;
  sdfIVector4_t v23;
  sdfIVector4_t v24;
  sdfIVector4_t v25;
  sdfIVector4_t v26;
  sdfIVector4_t v27;
  sdfIVector4_t v28;

  v1 = (evtPictureProcessData_t *)Allocate(evtPictureProcessData_t);
  _ctor(v1, 0);
  v1->flag = 0;
  v1->tex2d = 0;
  v1->tex3d = 0;
  *(u64 *)&v17.z = 0;
  *(u64 *)&v17.x = &v1->xy;
  set_Item(v17, 0, 0);
  *(u64 *)&v18.x = &v1->xy;
  *(u64 *)&v18.z = 1;
  set_Item(v18, 0, 0);
  *(u64 *)&v19.x = &v1->xy;
  *(u64 *)&v19.z = 2;
  set_Item(v19, 0x2000, 0);
  *(u64 *)&v20.x = &v1->xy;
  *(u64 *)&v20.z = 3;
  set_Item(v20, 3584, 0);
  *(u64 *)&v21.z = 0;
  *(u64 *)&v21.x = &v1->uv;
  set_Item(v21, 0, 0);
  *(u64 *)&v22.x = &v1->uv;
  *(u64 *)&v22.z = 1;
  set_Item(v22, 0, 0);
  *(u64 *)&v23.x = &v1->uv;
  *(u64 *)&v23.z = 2;
  set_Item(v23, 0x2000, 0);
  *(u64 *)&v24.x = &v1->uv;
  *(u64 *)&v24.z = 3;
  set_Item(v24, 7168, 0);
  *(u64 *)&v25.z = 0;
  *(u64 *)&v25.x = &v1->col;
  set_Item(v25, 128, 0);
  *(u64 *)&v26.x = &v1->col;
  *(u64 *)&v26.z = 1;
  set_Item(v26, 128, 0);
  *(u64 *)&v27.x = &v1->col;
  *(u64 *)&v27.z = 2;
  set_Item(v27, 128, 0);
  *(u64 *)&v28.x = &v1->col;
  *(u64 *)&v28.z = 3;
  set_Item(v28, 127, 0);
  if ((s32)uiObj->pictureObj->max_length < 1)
  {
LABEL_9:
    LODWORD(v14) = 0;
  }
  else
  {
    v14 = 0;
    max_length = (u32)uiObj->pictureObj->max_length;
    while (get_activeSelf(uiObj->pictureObj[v14], 0))
    {
      if (max_length == ++v14)
        goto LABEL_9;
    }
  }
  v1->GameObjectIdx = v14;
  v1->draw1st = 0;
  v1->drawGouto = 0;
  return v1;
}

// 0x1a28830
static void LoadTexture(evtPictureProcessData_t *data, char *texpath) {
  ;
}

// 0x1a28840
static s32 GetNowFrame(evtPictureProcessData_t *data) {
  s32 *p_now;
  s32 *m_Items;

  p_now = data->p_now;
  if (p_now)
    m_Items = p_now;
  else
    m_Items = &data->now2;
  return *m_Items;
}

// 0x1a28860
static void Animation(evtPictureProcessData_t *data) {
  s32 *p_now;
  u32 type;
  s32 v4;
  s32 *m_Items;
  s32 v7;
  s32 v8;
  s32 v9;
  s32 in_timer;
  s32 end;
  s32 v12;
  s32 v13;
  s32 v14;
  s64 v15;
  s32 v16;
  s64 v17;
  s32 v19;
  s32 v20;
  s32 v21;
  s32 v24;
  s32 v27;
  s32 v30;
  s32 v33;
  s32 v36;
  s32 v39;
  s32 v42;
  s32 v43;
  s32 out_timer;
  u64 v45[2];
  sdfIVector4_t v46;
  sdfIVector4_t v47;
  sdfIVector4_t v48;
  sdfIVector4_t v49;
  sdfIVector4_t v50;
  sdfIVector4_t v51;
  sdfIVector4_t v52;
  sdfIVector4_t v53;
  sdfIVector4_t v54;
  sdfIVector4_t v55;
  sdfIVector4_t v56;
  sdfIVector4_t v57;
  sdfIVector4_t v58;
  sdfIVector4_t v59;
  sdfIVector4_t v60;

  p_now = data->p_now;
  type = data->type;
  v4 = type & 0xFFFFFF;
  v45[0] = 0;
  v45[1] = 0;
  if (p_now)
    m_Items = p_now;
  else
    m_Items = &data->now2;
  if (!v4)
    return;
  if (v4 != 100)
  {
    in_timer = data->in_timer;
    if (in_timer <= 4)
    {
      if (BYTE2(type) > 2u)
        goto LABEL_22;
      data->in_timer = in_timer + 1;
      if (SkipChk(data))
      {
        data->in_timer = 5;
        goto LABEL_22;
      }
      v43 = data->in_timer << 8;
    }
    else
    {
      end = data->end;
      v12 = *m_Items;
      if (data->start == end && end == v12)
        goto LABEL_22;
      if ((u16)type == 2)
        return;
      if ((u16)type != 1)
        goto LABEL_22;
      if (end - v12 + 4 > 4)
      {
        data->out_timer = 0;
        goto LABEL_22;
      }
      out_timer = data->out_timer;
      if (out_timer <= 4)
        data->out_timer = out_timer + 1;
      if (SkipChk(data))
      {
        v14 = 0;
        data->out_timer = 5;
        goto LABEL_23;
      }
      v43 = 1280 - (data->out_timer << 8);
    }
    v14 = v43 / 5;
    goto LABEL_23;
  }
  if ((data->flag & 4) != 0)
  {
    v13 = data->out_timer;
    if (v13 <= 29)
    {
      data->out_timer = v13 + 1;
      v9 = 7424 - (v13 << 8);
      goto LABEL_18;
    }
LABEL_22:
    v14 = 256;
    goto LABEL_23;
  }
  v7 = data->in_timer;
  if (v7 > 29)
    goto LABEL_22;
  v8 = v7 + 1;
  data->in_timer = v8;
  v9 = v8 << 8;
LABEL_18:
  v14 = v9 / 30;
LABEL_23:
  if (data->ui_mode)
    v15 = 48;
  else
    v15 = 24;
  v16 = (*(**(u64 **)((char *)&data->klass + v15) + 392))(*(evtPictureProcessData_t **)((char *)&data->klass + v15), *(u64 *)(**(u64 **)((char *)&data->klass + v15) + 400));
  if (data->ui_mode)
    v17 = 48;
  else
    v17 = 24;
  v19 = (*(**(u64 **)((char *)&data->klass + v17) + 424))(*(evtPictureProcessData_t **)((char *)&data->klass + v17), *(u64 *)(**(u64 **)((char *)&data->klass + v17) + 432));
  if ((type & 0xFF0000) == 0x10000)
  {
    v21 = 150;
    v20 = -15;
  }
  else if ((type & 0xFF0000) == 0x20000)
  {
    v20 = v16 + 15;
    v21 = 150;
  }
  else
  {
    v20 = 0;
    v21 = 0;
  }
  *(u64 *)&v46.x = v45;
  *(u64 *)&v46.z = 0;
  set_Item(v46, v20, 0);
  *(u64 *)&v47.x = v45;
  *(u64 *)&v47.z = 1;
  set_Item(v47, v21, 0);
  *(u64 *)&v48.x = v45;
  *(u64 *)&v48.z = 0;
  v24 = get_Item(v48, 0) - v16;
  *(u64 *)&v49.x = v45;
  *(u64 *)&v49.z = 2;
  set_Item(v49, v24, 0);
  *(u64 *)&v50.x = v45;
  *(u64 *)&v50.z = 1;
  v27 = get_Item(v50, 0) - v19;
  *(u64 *)&v51.x = v45;
  *(u64 *)&v51.z = 3;
  set_Item(v51, v27, 0);
  *(u64 *)&v52.x = v45;
  *(u64 *)&v52.z = 0;
  v30 = get_Item(v52, 0) * (256 - v14);
  *(u64 *)&v53.z = 0;
  *(u64 *)&v53.x = &data->ofs_xy;
  set_Item(v53, v30 / 256, 0);
  *(u64 *)&v54.x = v45;
  *(u64 *)&v54.z = 1;
  v33 = get_Item(v54, 0) * (256 - v14);
  *(u64 *)&v55.z = 1;
  *(u64 *)&v55.x = &data->ofs_xy;
  set_Item(v55, v33 / 256, 0);
  *(u64 *)&v56.x = v45;
  *(u64 *)&v56.z = 2;
  v36 = get_Item(v56, 0) * (256 - v14);
  *(u64 *)&v57.z = 2;
  *(u64 *)&v57.x = &data->ofs_xy;
  set_Item(v57, v36 / 256, 0);
  *(u64 *)&v58.x = v45;
  *(u64 *)&v58.z = 3;
  v39 = get_Item(v58, 0) * (256 - v14);
  *(u64 *)&v59.z = 3;
  *(u64 *)&v59.x = &data->ofs_xy;
  set_Item(v59, v39 / 256, 0);
  v42 = v14 << 7;
  *(u64 *)&v60.z = 3;
  if ((v14 & 0x1000000) != 0)
    v42 = (v14 << 7) + 255;
  *(u64 *)&v60.x = &data->col;
  set_Item(v60, v42 >> 8, 0);
}

// 0x1a28bf0
void evtPictureOtEx(DDS3_OT ot) {
  gPictureOtEx = ot;
}

// 0x1a28c50
void evtPictureAchievementUnlock(evtPictureProcessData_t *data) {
  u32 uid;
  void *v5;
  void *achievementTbl_k__BackingField;
  Project_DefineAchievementID_string__c *klass;
  s64 v9;
  Project_DefineAchievementID_string__c **p_offset;
  s64 v11;
  char *v12;
  void *v13;
  void *v14;
  void *v16;
  Project_DefineAchievementID_string__c *v17;
  s64 v18;
  Project_DefineAchievementID_string__c **v19;
  s64 v20;
  char *v21;
  void *v22;
  void *v23;
  void *v25;
  Project_DefineAchievementID_string__c *v26;
  s64 v27;
  Project_DefineAchievementID_string__c **v28;
  s64 v29;
  char *v30;
  void *v31;
  void *v32;
  void *v34;
  Project_DefineAchievementID_string__c *v35;
  s64 v36;
  Project_DefineAchievementID_string__c **v37;
  s64 v38;
  char *v39;
  void *v40;
  void *v41;
  void *v44;
  Project_DefineAchievementID_string__c *v45;
  s64 v46;
  Project_DefineAchievementID_string__c **v47;
  s64 v48;
  char *v49;
  void *v50;
  void *v51;
  void *v53;
  Project_DefineAchievementID_string__c *v54;
  s64 v55;
  Project_DefineAchievementID_string__c **v56;
  s64 v57;
  char *v58;
  void *v59;
  void *v60;
  void *v62;
  Project_DefineAchievementID_string__c *v63;
  s64 v64;
  Project_DefineAchievementID_string__c **v65;
  s64 v66;
  char *v67;
  void *v68;
  void *v69;
  void *v72;
  Project_DefineAchievementID_string__c *v73;
  s64 v74;
  Project_DefineAchievementID_string__c **v75;
  s64 v76;
  char *v77;
  void *v78;
  void *v79;
  void *v82;
  Project_DefineAchievementID_string__c *v83;
  s64 v84;
  Project_DefineAchievementID_string__c **v85;
  s64 v86;
  char *v87;
  void *v88;
  void *v89;
  void *v91;
  Project_DefineAchievementID_string__c *v92;
  s64 v93;
  Project_DefineAchievementID_string__c **v94;
  s64 v95;
  char *v96;
  void *v97;
  void *v98;
  void *v100;
  Project_DefineAchievementID_string__c *v101;
  s64 v102;
  Project_DefineAchievementID_string__c **v103;
  s64 v104;
  char *v105;
  void *v106;
  void *v107;
  void *v110;
  Project_DefineAchievementID_string__c *v111;
  s64 v112;
  Project_DefineAchievementID_string__c **v113;
  s64 v114;
  char *v115;
  void *v116;
  void *v117;
  void *v120;
  Project_DefineAchievementID_string__c *v121;
  s64 v122;
  Project_DefineAchievementID_string__c **v123;
  s64 v124;
  char *v125;
  void *v126;
  void *v127;
  void *v130;
  Project_DefineAchievementID_string__c *v131;
  s64 v132;
  Project_DefineAchievementID_string__c **v133;
  s64 v134;
  char *v135;
  void *v136;
  void *v137;
  void *v139;
  Project_DefineAchievementID_string__c *v140;
  s64 v141;
  Project_DefineAchievementID_string__c **v142;
  s64 v143;
  char *v144;
  void *v145;
  void *v146;
  void *v148;
  Project_DefineAchievementID_string__c *v149;
  s64 v150;
  Project_DefineAchievementID_string__c **v151;
  s64 v152;
  char *v153;
  void *v154;
  void *v155;
  void *v158;
  Project_DefineAchievementID_string__c *v159;
  s64 v160;
  Project_DefineAchievementID_string__c **v161;
  s64 v162;
  char *v163;
  void *v164;
  void *v165;
  void *v168;
  Project_DefineAchievementID_string__c *v169;
  s64 v170;
  Project_DefineAchievementID_string__c **v171;
  s64 v172;
  char *v173;
  void *v174;
  void *v175;
  void *v178;
  Project_DefineAchievementID_string__c *v179;
  s64 v180;
  Project_DefineAchievementID_string__c **v181;
  s64 v182;
  char *v183;
  void *v184;
  void *v185;
  void *v188;
  Project_DefineAchievementID_string__c *v189;
  s64 v190;
  Project_DefineAchievementID_string__c **v191;
  s64 v192;
  char *v193;
  void *v194;
  void *v195;
  void *v197;
  Project_DefineAchievementID_string__c *v198;
  s64 v199;
  Project_DefineAchievementID_string__c **v200;
  s64 v201;
  char *v202;
  void *v203;
  void *v204;
  void *v206;
  Project_DefineAchievementID_string__c *v207;
  s64 v208;
  Project_DefineAchievementID_string__c **v209;
  s64 v210;
  char *v211;
  void *v212;
  void *v213;
  void *v216;
  Project_DefineAchievementID_string__c *v217;
  s64 v218;
  Project_DefineAchievementID_string__c **v219;
  s64 v220;
  char *v221;
  void *v222;
  void *v223;
  void *v226;
  Project_DefineAchievementID_string__c *v227;
  s64 v228;
  Project_DefineAchievementID_string__c **v229;
  s64 v230;
  char *v231;
  void *v232;
  void *v233;
  void *v236;
  Project_DefineAchievementID_string__c *v237;
  s64 v238;
  Project_DefineAchievementID_string__c **v239;
  s64 v240;
  char *v241;
  void *v242;
  void *v243;
  void *v246;
  Project_DefineAchievementID_string__c *v247;
  s64 v248;
  Project_DefineAchievementID_string__c **v249;
  s64 v250;
  char *v251;
  void *v252;
  void *v253;
  void *v256;
  Project_DefineAchievementID_string__c *v257;
  s64 v258;
  Project_DefineAchievementID_string__c **v259;
  s64 v260;
  char *v261;
  void *v262;
  void *v263;
  void *v265;
  Project_DefineAchievementID_string__c *v266;
  s64 v267;
  Project_DefineAchievementID_string__c **v268;
  s64 v269;
  char *v270;
  void *v271;
  void *v272;
  void *v274;
  Project_DefineAchievementID_string__c *v275;
  s64 v276;
  Project_DefineAchievementID_string__c **v277;
  s64 v278;
  char *v279;
  void *v280;
  void *v281;
  void *v284;
  Project_DefineAchievementID_string__c *v285;
  s64 v286;
  Project_DefineAchievementID_string__c **v287;
  s64 v288;
  char *v289;
  void *v290;
  void *v291;
  void *v294;
  Project_DefineAchievementID_string__c *v295;
  s64 v296;
  Project_DefineAchievementID_string__c **v297;
  s64 v298;
  char *v299;
  void *v300;
  void *v301;
  void *v304;
  Project_DefineAchievementID_string__c *v305;
  s64 v306;
  Project_DefineAchievementID_string__c **v307;
  s64 v308;
  char *v309;
  void *v310;
  void *v311;
  void *v314;
  Project_DefineAchievementID_string__c *v315;
  s64 v316;
  Project_DefineAchievementID_string__c **v317;
  s64 v318;
  char *v319;
  void *v320;
  void *v321;
  void *v324;
  Project_DefineAchievementID_string__c *v325;
  s64 v326;
  Project_DefineAchievementID_string__c **v327;
  s64 v328;
  char *v329;
  void *v330;
  void *v331;
  void *v334;
  Project_DefineAchievementID_string__c *v335;
  s64 v336;
  Project_DefineAchievementID_string__c **v337;
  s64 v338;
  char *v339;
  void *v340;
  void *v341;
  void *v343;
  Project_DefineAchievementID_string__c *v344;
  s64 v345;
  Project_DefineAchievementID_string__c **v346;
  s64 v347;
  char *v348;
  void *v349;
  void *v350;
  void *v352;
  Project_DefineAchievementID_string__c *v353;
  s64 v354;
  Project_DefineAchievementID_string__c **v355;
  s64 v356;
  char *v357;
  void *v358;
  void *v359;
  void *v362;
  Project_DefineAchievementID_string__c *v363;
  s64 v364;
  Project_DefineAchievementID_string__c **v365;
  s64 v366;
  char *v367;
  void *v368;
  void *v369;
  void *v372;
  Project_DefineAchievementID_string__c *v373;
  s64 v374;
  Project_DefineAchievementID_string__c **v375;
  s64 v376;
  char *v377;
  void *v378;
  void *v379;
  void *v382;
  Project_DefineAchievementID_string__c *v383;
  s64 v384;
  Project_DefineAchievementID_string__c **v385;
  s64 v386;
  char *v387;
  void *v388;
  void *v389;
  void *v392;
  Project_DefineAchievementID_string__c *v393;
  s64 v394;
  Project_DefineAchievementID_string__c **v395;
  s64 v396;
  char *v397;
  void *v398;
  void *v399;
  void *v402;
  Project_DefineAchievementID_string__c *v403;
  s64 v404;
  Project_DefineAchievementID_string__c **v405;
  s64 v406;
  char *v407;
  void *v408;
  void *v409;
  void *v412;
  Project_DefineAchievementID_string__c *v413;
  s64 v414;
  Project_DefineAchievementID_string__c **v415;
  s64 v416;
  char *v417;
  void *v418;
  void *v419;
  void *v422;
  Project_DefineAchievementID_string__c *v423;
  s64 v424;
  Project_DefineAchievementID_string__c **v425;
  s64 v426;
  char *v427;
  void *v428;
  void *v429;
  void *v431;
  Project_DefineAchievementID_string__c *v432;
  s64 v433;
  Project_DefineAchievementID_string__c **v434;
  s64 v435;
  char *v436;
  void *v437;
  void *v438;
  void *v440;
  Project_DefineAchievementID_string__c *v441;
  s64 v442;
  Project_DefineAchievementID_string__c **v443;
  s64 v444;
  char *v445;
  void *v446;
  void *v447;
  void *v450;
  Project_DefineAchievementID_string__c *v451;
  s64 v452;
  Project_DefineAchievementID_string__c **v453;
  s64 v454;
  char *v455;
  void *v456;
  void *v457;
  void *v460;
  Project_DefineAchievementID_string__c *v461;
  s64 v462;
  Project_DefineAchievementID_string__c **v463;
  s64 v464;
  char *v465;
  void *v466;
  void *v467;
  void *v470;
  Project_DefineAchievementID_string__c *v471;
  s64 v472;
  Project_DefineAchievementID_string__c **v473;
  s64 v474;
  char *v475;
  void *v476;
  void *v477;
  void *v480;
  Project_DefineAchievementID_string__c *v481;
  s64 v482;
  Project_DefineAchievementID_string__c **v483;
  s64 v484;
  char *v485;
  void *v486;
  void *v487;
  void *v490;
  Project_DefineAchievementID_string__c *v491;
  s64 v492;
  Project_DefineAchievementID_string__c **v493;
  s64 v494;
  char *v495;
  void *v496;
  void *v497;
  void *v500;
  Project_DefineAchievementID_string__c *v501;
  s64 v502;
  Project_DefineAchievementID_string__c **v503;
  s64 v504;
  char *v505;
  void *v506;
  void *v507;
  void *v510;
  Project_DefineAchievementID_string__c *v511;
  s64 v512;
  Project_DefineAchievementID_string__c **v513;
  s64 v514;
  char *v515;
  void *v516;
  void *v517;
  void *v520;
  Project_DefineAchievementID_string__c *v521;
  s64 v522;
  Project_DefineAchievementID_string__c **v523;
  s64 v524;
  char *v525;
  void *v526;
  void *v527;
  void *v529;
  Project_DefineAchievementID_string__c *v530;
  s64 v531;
  Project_DefineAchievementID_string__c **v532;
  s64 v533;
  char *v534;
  void *v535;
  void *v536;
  void *v538;
  Project_DefineAchievementID_string__c *v539;
  s64 v540;
  Project_DefineAchievementID_string__c **v541;
  s64 v542;
  char *v543;
  void *v544;
  void *v545;
  void *v548;
  Project_DefineAchievementID_string__c *v549;
  s64 v550;
  Project_DefineAchievementID_string__c **v551;
  s64 v552;
  char *v553;
  void *v554;
  void *v555;
  void *v558;
  Project_DefineAchievementID_string__c *v559;
  s64 v560;
  Project_DefineAchievementID_string__c **v561;
  s64 v562;
  char *v563;
  void *v564;
  void *v565;
  void *v568;
  Project_DefineAchievementID_string__c *v569;
  s64 v570;
  Project_DefineAchievementID_string__c **v571;
  s64 v572;
  char *v573;
  void *v574;
  void *v575;
  void *v578;
  Project_DefineAchievementID_string__c *v579;
  s64 v580;
  Project_DefineAchievementID_string__c **v581;
  s64 v582;
  char *v583;
  void *v584;
  void *v585;
  void *v588;
  Project_DefineAchievementID_string__c *v589;
  s64 v590;
  Project_DefineAchievementID_string__c **v591;
  s64 v592;
  char *v593;
  void *v594;
  void *v595;
  void *v598;
  Project_DefineAchievementID_string__c *v599;
  s64 v600;
  Project_DefineAchievementID_string__c **v601;
  s64 v602;
  char *v603;
  void *v604;
  void *v605;
  void *v608;
  Project_DefineAchievementID_string__c *v609;
  s64 v610;
  Project_DefineAchievementID_string__c **v611;
  s64 v612;
  char *v613;
  void *v614;
  void *v615;
  void *v618;
  Project_DefineAchievementID_string__c *v619;
  s64 v620;
  Project_DefineAchievementID_string__c **v621;
  s64 v622;
  char *v623;
  void *v624;
  void *v625;
  void *v628;
  Project_DefineAchievementID_string__c *v629;
  s64 v630;
  Project_DefineAchievementID_string__c **v631;
  s64 v632;
  char *v633;
  void *v634;
  void *v635;
  evtPictureProcessData_t *v637;
  void *v639;
  Project_DefineAchievementID_string__c *v640;
  s64 v641;
  Project_DefineAchievementID_string__c **v642;
  s64 v643;
  char *v644;
  void *v645;
  void *v646;
  void *v648;
  Project_DefineAchievementID_string__c *v649;
  s64 v650;
  Project_DefineAchievementID_string__c **v651;
  s64 v652;
  char *v653;
  void *v654;
  void *v655;
  void *v658;
  Project_DefineAchievementID_string__c *v659;
  s64 v660;
  void *v661;
  void *v662;
  void *v665;
  Project_DefineAchievementID_string__c *v666;
  s64 v667;
  Project_DefineAchievementID_string__c **v668;
  s64 v669;
  char *v670;
  void *v671;
  void *v672;
  void *v675;
  Project_DefineAchievementID_string__c *v676;
  s64 v677;
  Project_DefineAchievementID_string__c **v678;
  s64 v679;
  char *v680;
  void *v681;
  void *v682;
  void *v685;
  Project_DefineAchievementID_string__c *v686;
  s64 v687;
  Project_DefineAchievementID_string__c **v688;
  s64 v689;
  char *v690;
  void *v691;
  void *v692;
  void *v695;
  Project_DefineAchievementID_string__c *v696;
  s64 v697;
  Project_DefineAchievementID_string__c **v698;
  s64 v699;
  char *v700;
  void *v701;
  void *v702;
  void *v705;
  Project_DefineAchievementID_string__c *v706;
  s64 v707;
  Project_DefineAchievementID_string__c **v708;
  s64 v709;
  char *v710;
  void *v711;
  void *v712;
  void *v715;
  Project_DefineAchievementID_string__c *v716;
  s64 v717;
  Project_DefineAchievementID_string__c **v718;
  s64 v719;
  char *v720;
  void *v721;
  void *v722;
  void *v725;
  Project_DefineAchievementID_string__c *v726;
  s64 v727;
  Project_DefineAchievementID_string__c **v728;
  s64 v729;
  char *v730;
  void *v731;
  void *v732;
  void *v735;
  Project_DefineAchievementID_string__c *v736;
  s64 v737;
  Project_DefineAchievementID_string__c **v738;
  s64 v739;
  char *v740;
  void *v741;
  void *v742;
  void *v745;
  Project_DefineAchievementID_string__c *v746;
  s64 v747;
  Project_DefineAchievementID_string__c **v748;
  s64 v749;
  char *v750;
  void *v751;
  void *v752;
  void *v755;
  Project_DefineAchievementID_string__c *v756;
  s64 v757;
  Project_DefineAchievementID_string__c **v758;
  s64 v759;
  char *v760;
  void *v761;
  void *v762;
  void *v765;
  Project_DefineAchievementID_string__c *v766;
  s64 v767;
  Project_DefineAchievementID_string__c **v768;
  s64 v769;
  char *v770;
  Project_DefineAchievementID_string__c **v771;
  s64 v772;
  char *v773;
  evtPictureProcessData_t *v774;

  if (data->draw1st == 51)
  {
    uid = data->uid;
    if (uid != 83)
    {
      v774 = data;
      if (uid != 85)
        goto LABEL_6;
      goto LABEL_34;
    }
    v5 = Allocate(System_Action_string_);
    __ctor(v5, 0, Method_Project_Achievement_Unlock___83873840, 0);
    achievementTbl_k__BackingField = _achievementTbl_k__BackingField;
    klass = achievementTbl_k__BackingField->klass;
    v9 = *(u16 *)&achievementTbl_k__BackingField->klass->_2.rank;
    if (*(u16 *)&achievementTbl_k__BackingField->klass->_2.rank)
    {
      p_offset = &klass->_1.interfaceOffsets->offset;
      while (*(p_offset - 1) != Project_DefineAchievementID_string_)
      {
        p_offset += 2;
        if (!--v9)
          goto LABEL_28;
      }
      v11 = &klass->vtable[*(u32 *)p_offset + 2];
    }
    else
    {
LABEL_28:
      v11 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 2u);
    }
    v12 = (*v11)(achievementTbl_k__BackingField, *(u64 *)(v11 + 8));
    AddFunc_36447680(manager, v5, v12, 0);
    uid = data->uid;
    v774 = data;
    if (uid != 85)
    {
LABEL_6:
      if (uid != 87)
        goto LABEL_7;
      goto LABEL_61;
    }
LABEL_34:
    v13 = manager;
    v14 = Allocate(System_Action_string_);
    __ctor(v14, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v16 = _achievementTbl_k__BackingField;
    v17 = v16->klass;
    v18 = *(u16 *)&v16->klass->_2.rank;
    if (*(u16 *)&v16->klass->_2.rank)
    {
      v19 = &v17->_1.interfaceOffsets->offset;
      while (*(v19 - 1) != Project_DefineAchievementID_string_)
      {
        v19 += 2;
        if (!--v18)
          goto LABEL_43;
      }
      v20 = &v17->vtable[*(u32 *)v19 + 3];
    }
    else
    {
LABEL_43:
      v20 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 3u);
    }
    v21 = (*v20)(v16, *(u64 *)(v20 + 8));
    AddFunc_36447680(v13, v14, v21, 0);
    v22 = manager;
    v23 = Allocate(System_Action_string_);
    __ctor(v23, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v25 = _achievementTbl_k__BackingField;
    v26 = v25->klass;
    v27 = *(u16 *)&v25->klass->_2.rank;
    if (*(u16 *)&v25->klass->_2.rank)
    {
      v28 = &v26->_1.interfaceOffsets->offset;
      while (*(v28 - 1) != Project_DefineAchievementID_string_)
      {
        v28 += 2;
        if (!--v27)
          goto LABEL_56;
      }
      v29 = &v26->vtable[*(u32 *)v28 + 2];
    }
    else
    {
LABEL_56:
      v29 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 2u);
    }
    v30 = (*v29)(v25, *(u64 *)(v29 + 8));
    AddFunc_36447680(v22, v23, v30, 0);
    uid = v774->uid;
    if (uid != 87)
    {
LABEL_7:
      if (uid != 89)
        goto LABEL_8;
      goto LABEL_101;
    }
LABEL_61:
    v31 = manager;
    v32 = Allocate(System_Action_string_);
    __ctor(v32, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v34 = _achievementTbl_k__BackingField;
    v35 = v34->klass;
    v36 = *(u16 *)&v34->klass->_2.rank;
    if (*(u16 *)&v34->klass->_2.rank)
    {
      v37 = &v35->_1.interfaceOffsets->offset;
      while (*(v37 - 1) != Project_DefineAchievementID_string_)
      {
        v37 += 2;
        if (!--v36)
          goto LABEL_70;
      }
      v38 = &v35->vtable[*(u32 *)v37 + 4];
    }
    else
    {
LABEL_70:
      v38 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 4u);
    }
    v39 = (*v38)(v34, *(u64 *)(v38 + 8));
    AddFunc_36447680(v31, v32, v39, 0);
    v40 = manager;
    v41 = Allocate(System_Action_string_);
    __ctor(v41, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v44 = _achievementTbl_k__BackingField;
    v45 = v44->klass;
    v46 = *(u16 *)&v44->klass->_2.rank;
    if (!*(u16 *)&v44->klass->_2.rank)
      goto LABEL_86;
    goto LABEL_83;
    if (!*(u16 *)&v44->klass->_2.rank)
    {
LABEL_86:
      v48 = sub_4227F4(v44, Project_DefineAchievementID_string_, 2u);
      goto LABEL_88;
    }
LABEL_83:
    v47 = &v45->_1.interfaceOffsets->offset;
    while (*(v47 - 1) != Project_DefineAchievementID_string_)
    {
      v47 += 2;
      if (!--v46)
        goto LABEL_86;
    }
    v48 = &v45->vtable[*(u32 *)v47 + 2];
LABEL_88:
    v49 = (*v48)(v44, *(u64 *)(v48 + 8));
    AddFunc_36447680(v40, v41, v49, 0);
    v50 = manager;
    v51 = Allocate(System_Action_string_);
    __ctor(v51, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v53 = _achievementTbl_k__BackingField;
    v54 = v53->klass;
    v55 = *(u16 *)&v53->klass->_2.rank;
    if (*(u16 *)&v53->klass->_2.rank)
    {
      v56 = &v54->_1.interfaceOffsets->offset;
      while (*(v56 - 1) != Project_DefineAchievementID_string_)
      {
        v56 += 2;
        if (!--v55)
          goto LABEL_96;
      }
      v57 = &v54->vtable[*(u32 *)v56 + 3];
    }
    else
    {
LABEL_96:
      v57 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 3u);
    }
    v58 = (*v57)(v53, *(u64 *)(v57 + 8));
    AddFunc_36447680(v50, v51, v58, 0);
    uid = v774->uid;
    if (uid != 89)
    {
LABEL_8:
      if (uid != 91)
        goto LABEL_9;
      goto LABEL_154;
    }
LABEL_101:
    v59 = manager;
    v60 = Allocate(System_Action_string_);
    __ctor(v60, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v62 = _achievementTbl_k__BackingField;
    v63 = v62->klass;
    v64 = *(u16 *)&v62->klass->_2.rank;
    if (*(u16 *)&v62->klass->_2.rank)
    {
      v65 = &v63->_1.interfaceOffsets->offset;
      while (*(v65 - 1) != Project_DefineAchievementID_string_)
      {
        v65 += 2;
        if (!--v64)
          goto LABEL_110;
      }
      v66 = &v63->vtable[*(u32 *)v65 + 5];
    }
    else
    {
LABEL_110:
      v66 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 5u);
    }
    v67 = (*v66)(v62, *(u64 *)(v66 + 8));
    AddFunc_36447680(v59, v60, v67, 0);
    v68 = manager;
    v69 = Allocate(System_Action_string_);
    __ctor(v69, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v72 = _achievementTbl_k__BackingField;
    v73 = v72->klass;
    v74 = *(u16 *)&v72->klass->_2.rank;
    if (!*(u16 *)&v72->klass->_2.rank)
      goto LABEL_126;
    goto LABEL_123;
    if (!*(u16 *)&v72->klass->_2.rank)
    {
LABEL_126:
      v76 = sub_4227F4(v72, Project_DefineAchievementID_string_, 2u);
      goto LABEL_128;
    }
LABEL_123:
    v75 = &v73->_1.interfaceOffsets->offset;
    while (*(v75 - 1) != Project_DefineAchievementID_string_)
    {
      v75 += 2;
      if (!--v74)
        goto LABEL_126;
    }
    v76 = &v73->vtable[*(u32 *)v75 + 2];
LABEL_128:
    v77 = (*v76)(v72, *(u64 *)(v76 + 8));
    AddFunc_36447680(v68, v69, v77, 0);
    v78 = manager;
    v79 = Allocate(System_Action_string_);
    __ctor(v79, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v82 = _achievementTbl_k__BackingField;
    v83 = v82->klass;
    v84 = *(u16 *)&v82->klass->_2.rank;
    if (!*(u16 *)&v82->klass->_2.rank)
      goto LABEL_139;
    goto LABEL_136;
    if (!*(u16 *)&v82->klass->_2.rank)
    {
LABEL_139:
      v86 = sub_4227F4(v82, Project_DefineAchievementID_string_, 3u);
      goto LABEL_141;
    }
LABEL_136:
    v85 = &v83->_1.interfaceOffsets->offset;
    while (*(v85 - 1) != Project_DefineAchievementID_string_)
    {
      v85 += 2;
      if (!--v84)
        goto LABEL_139;
    }
    v86 = &v83->vtable[*(u32 *)v85 + 3];
LABEL_141:
    v87 = (*v86)(v82, *(u64 *)(v86 + 8));
    AddFunc_36447680(v78, v79, v87, 0);
    v88 = manager;
    v89 = Allocate(System_Action_string_);
    __ctor(v89, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v91 = _achievementTbl_k__BackingField;
    v92 = v91->klass;
    v93 = *(u16 *)&v91->klass->_2.rank;
    if (*(u16 *)&v91->klass->_2.rank)
    {
      v94 = &v92->_1.interfaceOffsets->offset;
      while (*(v94 - 1) != Project_DefineAchievementID_string_)
      {
        v94 += 2;
        if (!--v93)
          goto LABEL_149;
      }
      v95 = &v92->vtable[*(u32 *)v94 + 4];
    }
    else
    {
LABEL_149:
      v95 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 4u);
    }
    v96 = (*v95)(v91, *(u64 *)(v95 + 8));
    AddFunc_36447680(v88, v89, v96, 0);
    uid = v774->uid;
    if (uid != 91)
    {
LABEL_9:
      if (uid != 93)
        goto LABEL_10;
      goto LABEL_220;
    }
LABEL_154:
    v97 = manager;
    v98 = Allocate(System_Action_string_);
    __ctor(v98, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v100 = _achievementTbl_k__BackingField;
    v101 = v100->klass;
    v102 = *(u16 *)&v100->klass->_2.rank;
    if (*(u16 *)&v100->klass->_2.rank)
    {
      v103 = &v101->_1.interfaceOffsets->offset;
      while (*(v103 - 1) != Project_DefineAchievementID_string_)
      {
        v103 += 2;
        if (!--v102)
          goto LABEL_163;
      }
      v104 = &v101->vtable[*(u32 *)v103 + 6];
    }
    else
    {
LABEL_163:
      v104 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 6u);
    }
    v105 = (*v104)(v100, *(u64 *)(v104 + 8));
    AddFunc_36447680(v97, v98, v105, 0);
    v106 = manager;
    v107 = Allocate(System_Action_string_);
    __ctor(v107, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v110 = _achievementTbl_k__BackingField;
    v111 = v110->klass;
    v112 = *(u16 *)&v110->klass->_2.rank;
    if (!*(u16 *)&v110->klass->_2.rank)
      goto LABEL_179;
    goto LABEL_176;
    if (!*(u16 *)&v110->klass->_2.rank)
    {
LABEL_179:
      v114 = sub_4227F4(v110, Project_DefineAchievementID_string_, 2u);
      goto LABEL_181;
    }
LABEL_176:
    v113 = &v111->_1.interfaceOffsets->offset;
    while (*(v113 - 1) != Project_DefineAchievementID_string_)
    {
      v113 += 2;
      if (!--v112)
        goto LABEL_179;
    }
    v114 = &v111->vtable[*(u32 *)v113 + 2];
LABEL_181:
    v115 = (*v114)(v110, *(u64 *)(v114 + 8));
    AddFunc_36447680(v106, v107, v115, 0);
    v116 = manager;
    v117 = Allocate(System_Action_string_);
    __ctor(v117, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v120 = _achievementTbl_k__BackingField;
    v121 = v120->klass;
    v122 = *(u16 *)&v120->klass->_2.rank;
    if (!*(u16 *)&v120->klass->_2.rank)
      goto LABEL_192;
    goto LABEL_189;
    if (!*(u16 *)&v120->klass->_2.rank)
    {
LABEL_192:
      v124 = sub_4227F4(v120, Project_DefineAchievementID_string_, 3u);
      goto LABEL_194;
    }
LABEL_189:
    v123 = &v121->_1.interfaceOffsets->offset;
    while (*(v123 - 1) != Project_DefineAchievementID_string_)
    {
      v123 += 2;
      if (!--v122)
        goto LABEL_192;
    }
    v124 = &v121->vtable[*(u32 *)v123 + 3];
LABEL_194:
    v125 = (*v124)(v120, *(u64 *)(v124 + 8));
    AddFunc_36447680(v116, v117, v125, 0);
    v126 = manager;
    v127 = Allocate(System_Action_string_);
    __ctor(v127, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v130 = _achievementTbl_k__BackingField;
    v131 = v130->klass;
    v132 = *(u16 *)&v130->klass->_2.rank;
    if (!*(u16 *)&v130->klass->_2.rank)
      goto LABEL_205;
    goto LABEL_202;
    if (!*(u16 *)&v130->klass->_2.rank)
    {
LABEL_205:
      v134 = sub_4227F4(v130, Project_DefineAchievementID_string_, 4u);
      goto LABEL_207;
    }
LABEL_202:
    v133 = &v131->_1.interfaceOffsets->offset;
    while (*(v133 - 1) != Project_DefineAchievementID_string_)
    {
      v133 += 2;
      if (!--v132)
        goto LABEL_205;
    }
    v134 = &v131->vtable[*(u32 *)v133 + 4];
LABEL_207:
    v135 = (*v134)(v130, *(u64 *)(v134 + 8));
    AddFunc_36447680(v126, v127, v135, 0);
    v136 = manager;
    v137 = Allocate(System_Action_string_);
    __ctor(v137, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v139 = _achievementTbl_k__BackingField;
    v140 = v139->klass;
    v141 = *(u16 *)&v139->klass->_2.rank;
    if (*(u16 *)&v139->klass->_2.rank)
    {
      v142 = &v140->_1.interfaceOffsets->offset;
      while (*(v142 - 1) != Project_DefineAchievementID_string_)
      {
        v142 += 2;
        if (!--v141)
          goto LABEL_215;
      }
      v143 = &v140->vtable[*(u32 *)v142 + 5];
    }
    else
    {
LABEL_215:
      v143 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 5u);
    }
    v144 = (*v143)(v139, *(u64 *)(v143 + 8));
    AddFunc_36447680(v136, v137, v144, 0);
    uid = v774->uid;
    if (uid != 93)
    {
LABEL_10:
      if (uid != 95)
        goto LABEL_11;
      goto LABEL_299;
    }
LABEL_220:
    v145 = manager;
    v146 = Allocate(System_Action_string_);
    __ctor(v146, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v148 = _achievementTbl_k__BackingField;
    v149 = v148->klass;
    v150 = *(u16 *)&v148->klass->_2.rank;
    if (*(u16 *)&v148->klass->_2.rank)
    {
      v151 = &v149->_1.interfaceOffsets->offset;
      while (*(v151 - 1) != Project_DefineAchievementID_string_)
      {
        v151 += 2;
        if (!--v150)
          goto LABEL_229;
      }
      v152 = &v149->vtable[*(u32 *)v151 + 7];
    }
    else
    {
LABEL_229:
      v152 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 7u);
    }
    v153 = (*v152)(v148, *(u64 *)(v152 + 8));
    AddFunc_36447680(v145, v146, v153, 0);
    v154 = manager;
    v155 = Allocate(System_Action_string_);
    __ctor(v155, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v158 = _achievementTbl_k__BackingField;
    v159 = v158->klass;
    v160 = *(u16 *)&v158->klass->_2.rank;
    if (!*(u16 *)&v158->klass->_2.rank)
      goto LABEL_245;
    goto LABEL_242;
    if (!*(u16 *)&v158->klass->_2.rank)
    {
LABEL_245:
      v162 = sub_4227F4(v158, Project_DefineAchievementID_string_, 2u);
      goto LABEL_247;
    }
LABEL_242:
    v161 = &v159->_1.interfaceOffsets->offset;
    while (*(v161 - 1) != Project_DefineAchievementID_string_)
    {
      v161 += 2;
      if (!--v160)
        goto LABEL_245;
    }
    v162 = &v159->vtable[*(u32 *)v161 + 2];
LABEL_247:
    v163 = (*v162)(v158, *(u64 *)(v162 + 8));
    AddFunc_36447680(v154, v155, v163, 0);
    v164 = manager;
    v165 = Allocate(System_Action_string_);
    __ctor(v165, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v168 = _achievementTbl_k__BackingField;
    v169 = v168->klass;
    v170 = *(u16 *)&v168->klass->_2.rank;
    if (!*(u16 *)&v168->klass->_2.rank)
      goto LABEL_258;
    goto LABEL_255;
    if (!*(u16 *)&v168->klass->_2.rank)
    {
LABEL_258:
      v172 = sub_4227F4(v168, Project_DefineAchievementID_string_, 3u);
      goto LABEL_260;
    }
LABEL_255:
    v171 = &v169->_1.interfaceOffsets->offset;
    while (*(v171 - 1) != Project_DefineAchievementID_string_)
    {
      v171 += 2;
      if (!--v170)
        goto LABEL_258;
    }
    v172 = &v169->vtable[*(u32 *)v171 + 3];
LABEL_260:
    v173 = (*v172)(v168, *(u64 *)(v172 + 8));
    AddFunc_36447680(v164, v165, v173, 0);
    v174 = manager;
    v175 = Allocate(System_Action_string_);
    __ctor(v175, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v178 = _achievementTbl_k__BackingField;
    v179 = v178->klass;
    v180 = *(u16 *)&v178->klass->_2.rank;
    if (!*(u16 *)&v178->klass->_2.rank)
      goto LABEL_271;
    goto LABEL_268;
    if (!*(u16 *)&v178->klass->_2.rank)
    {
LABEL_271:
      v182 = sub_4227F4(v178, Project_DefineAchievementID_string_, 4u);
      goto LABEL_273;
    }
LABEL_268:
    v181 = &v179->_1.interfaceOffsets->offset;
    while (*(v181 - 1) != Project_DefineAchievementID_string_)
    {
      v181 += 2;
      if (!--v180)
        goto LABEL_271;
    }
    v182 = &v179->vtable[*(u32 *)v181 + 4];
LABEL_273:
    v183 = (*v182)(v178, *(u64 *)(v182 + 8));
    AddFunc_36447680(v174, v175, v183, 0);
    v184 = manager;
    v185 = Allocate(System_Action_string_);
    __ctor(v185, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v188 = _achievementTbl_k__BackingField;
    v189 = v188->klass;
    v190 = *(u16 *)&v188->klass->_2.rank;
    if (!*(u16 *)&v188->klass->_2.rank)
      goto LABEL_284;
    goto LABEL_281;
    if (!*(u16 *)&v188->klass->_2.rank)
    {
LABEL_284:
      v192 = sub_4227F4(v188, Project_DefineAchievementID_string_, 5u);
      goto LABEL_286;
    }
LABEL_281:
    v191 = &v189->_1.interfaceOffsets->offset;
    while (*(v191 - 1) != Project_DefineAchievementID_string_)
    {
      v191 += 2;
      if (!--v190)
        goto LABEL_284;
    }
    v192 = &v189->vtable[*(u32 *)v191 + 5];
LABEL_286:
    v193 = (*v192)(v188, *(u64 *)(v192 + 8));
    AddFunc_36447680(v184, v185, v193, 0);
    v194 = manager;
    v195 = Allocate(System_Action_string_);
    __ctor(v195, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v197 = _achievementTbl_k__BackingField;
    v198 = v197->klass;
    v199 = *(u16 *)&v197->klass->_2.rank;
    if (*(u16 *)&v197->klass->_2.rank)
    {
      v200 = &v198->_1.interfaceOffsets->offset;
      while (*(v200 - 1) != Project_DefineAchievementID_string_)
      {
        v200 += 2;
        if (!--v199)
          goto LABEL_294;
      }
      v201 = &v198->vtable[*(u32 *)v200 + 6];
    }
    else
    {
LABEL_294:
      v201 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 6u);
    }
    v202 = (*v201)(v197, *(u64 *)(v201 + 8));
    AddFunc_36447680(v194, v195, v202, 0);
    uid = v774->uid;
    if (uid != 95)
    {
LABEL_11:
      if (uid != 97)
        goto LABEL_12;
      goto LABEL_391;
    }
LABEL_299:
    v203 = manager;
    v204 = Allocate(System_Action_string_);
    __ctor(v204, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v206 = _achievementTbl_k__BackingField;
    v207 = v206->klass;
    v208 = *(u16 *)&v206->klass->_2.rank;
    if (*(u16 *)&v206->klass->_2.rank)
    {
      v209 = &v207->_1.interfaceOffsets->offset;
      while (*(v209 - 1) != Project_DefineAchievementID_string_)
      {
        v209 += 2;
        if (!--v208)
          goto LABEL_308;
      }
      v210 = &v207->vtable[*(u32 *)v209 + 8];
    }
    else
    {
LABEL_308:
      v210 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 8u);
    }
    v211 = (*v210)(v206, *(u64 *)(v210 + 8));
    AddFunc_36447680(v203, v204, v211, 0);
    v212 = manager;
    v213 = Allocate(System_Action_string_);
    __ctor(v213, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v216 = _achievementTbl_k__BackingField;
    v217 = v216->klass;
    v218 = *(u16 *)&v216->klass->_2.rank;
    if (!*(u16 *)&v216->klass->_2.rank)
      goto LABEL_324;
    goto LABEL_321;
    if (!*(u16 *)&v216->klass->_2.rank)
    {
LABEL_324:
      v220 = sub_4227F4(v216, Project_DefineAchievementID_string_, 2u);
      goto LABEL_326;
    }
LABEL_321:
    v219 = &v217->_1.interfaceOffsets->offset;
    while (*(v219 - 1) != Project_DefineAchievementID_string_)
    {
      v219 += 2;
      if (!--v218)
        goto LABEL_324;
    }
    v220 = &v217->vtable[*(u32 *)v219 + 2];
LABEL_326:
    v221 = (*v220)(v216, *(u64 *)(v220 + 8));
    AddFunc_36447680(v212, v213, v221, 0);
    v222 = manager;
    v223 = Allocate(System_Action_string_);
    __ctor(v223, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v226 = _achievementTbl_k__BackingField;
    v227 = v226->klass;
    v228 = *(u16 *)&v226->klass->_2.rank;
    if (!*(u16 *)&v226->klass->_2.rank)
      goto LABEL_337;
    goto LABEL_334;
    if (!*(u16 *)&v226->klass->_2.rank)
    {
LABEL_337:
      v230 = sub_4227F4(v226, Project_DefineAchievementID_string_, 3u);
      goto LABEL_339;
    }
LABEL_334:
    v229 = &v227->_1.interfaceOffsets->offset;
    while (*(v229 - 1) != Project_DefineAchievementID_string_)
    {
      v229 += 2;
      if (!--v228)
        goto LABEL_337;
    }
    v230 = &v227->vtable[*(u32 *)v229 + 3];
LABEL_339:
    v231 = (*v230)(v226, *(u64 *)(v230 + 8));
    AddFunc_36447680(v222, v223, v231, 0);
    v232 = manager;
    v233 = Allocate(System_Action_string_);
    __ctor(v233, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v236 = _achievementTbl_k__BackingField;
    v237 = v236->klass;
    v238 = *(u16 *)&v236->klass->_2.rank;
    if (!*(u16 *)&v236->klass->_2.rank)
      goto LABEL_350;
    goto LABEL_347;
    if (!*(u16 *)&v236->klass->_2.rank)
    {
LABEL_350:
      v240 = sub_4227F4(v236, Project_DefineAchievementID_string_, 4u);
      goto LABEL_352;
    }
LABEL_347:
    v239 = &v237->_1.interfaceOffsets->offset;
    while (*(v239 - 1) != Project_DefineAchievementID_string_)
    {
      v239 += 2;
      if (!--v238)
        goto LABEL_350;
    }
    v240 = &v237->vtable[*(u32 *)v239 + 4];
LABEL_352:
    v241 = (*v240)(v236, *(u64 *)(v240 + 8));
    AddFunc_36447680(v232, v233, v241, 0);
    v242 = manager;
    v243 = Allocate(System_Action_string_);
    __ctor(v243, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v246 = _achievementTbl_k__BackingField;
    v247 = v246->klass;
    v248 = *(u16 *)&v246->klass->_2.rank;
    if (!*(u16 *)&v246->klass->_2.rank)
      goto LABEL_363;
    goto LABEL_360;
    if (!*(u16 *)&v246->klass->_2.rank)
    {
LABEL_363:
      v250 = sub_4227F4(v246, Project_DefineAchievementID_string_, 5u);
      goto LABEL_365;
    }
LABEL_360:
    v249 = &v247->_1.interfaceOffsets->offset;
    while (*(v249 - 1) != Project_DefineAchievementID_string_)
    {
      v249 += 2;
      if (!--v248)
        goto LABEL_363;
    }
    v250 = &v247->vtable[*(u32 *)v249 + 5];
LABEL_365:
    v251 = (*v250)(v246, *(u64 *)(v250 + 8));
    AddFunc_36447680(v242, v243, v251, 0);
    v252 = manager;
    v253 = Allocate(System_Action_string_);
    __ctor(v253, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v256 = _achievementTbl_k__BackingField;
    v257 = v256->klass;
    v258 = *(u16 *)&v256->klass->_2.rank;
    if (!*(u16 *)&v256->klass->_2.rank)
      goto LABEL_376;
    goto LABEL_373;
    if (!*(u16 *)&v256->klass->_2.rank)
    {
LABEL_376:
      v260 = sub_4227F4(v256, Project_DefineAchievementID_string_, 6u);
      goto LABEL_378;
    }
LABEL_373:
    v259 = &v257->_1.interfaceOffsets->offset;
    while (*(v259 - 1) != Project_DefineAchievementID_string_)
    {
      v259 += 2;
      if (!--v258)
        goto LABEL_376;
    }
    v260 = &v257->vtable[*(u32 *)v259 + 6];
LABEL_378:
    v261 = (*v260)(v256, *(u64 *)(v260 + 8));
    AddFunc_36447680(v252, v253, v261, 0);
    v262 = manager;
    v263 = Allocate(System_Action_string_);
    __ctor(v263, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v265 = _achievementTbl_k__BackingField;
    v266 = v265->klass;
    v267 = *(u16 *)&v265->klass->_2.rank;
    if (*(u16 *)&v265->klass->_2.rank)
    {
      v268 = &v266->_1.interfaceOffsets->offset;
      while (*(v268 - 1) != Project_DefineAchievementID_string_)
      {
        v268 += 2;
        if (!--v267)
          goto LABEL_386;
      }
      v269 = &v266->vtable[*(u32 *)v268 + 7];
    }
    else
    {
LABEL_386:
      v269 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 7u);
    }
    v270 = (*v269)(v265, *(u64 *)(v269 + 8));
    AddFunc_36447680(v262, v263, v270, 0);
    uid = v774->uid;
    if (uid != 97)
    {
LABEL_12:
      if (uid != 99)
        goto LABEL_13;
      goto LABEL_496;
    }
LABEL_391:
    v271 = manager;
    v272 = Allocate(System_Action_string_);
    __ctor(v272, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v274 = _achievementTbl_k__BackingField;
    v275 = v274->klass;
    v276 = *(u16 *)&v274->klass->_2.rank;
    if (*(u16 *)&v274->klass->_2.rank)
    {
      v277 = &v275->_1.interfaceOffsets->offset;
      while (*(v277 - 1) != Project_DefineAchievementID_string_)
      {
        v277 += 2;
        if (!--v276)
          goto LABEL_400;
      }
      v278 = &v275->vtable[*(u32 *)v277 + 9];
    }
    else
    {
LABEL_400:
      v278 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 9u);
    }
    v279 = (*v278)(v274, *(u64 *)(v278 + 8));
    AddFunc_36447680(v271, v272, v279, 0);
    v280 = manager;
    v281 = Allocate(System_Action_string_);
    __ctor(v281, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v284 = _achievementTbl_k__BackingField;
    v285 = v284->klass;
    v286 = *(u16 *)&v284->klass->_2.rank;
    if (!*(u16 *)&v284->klass->_2.rank)
      goto LABEL_416;
    goto LABEL_413;
    if (!*(u16 *)&v284->klass->_2.rank)
    {
LABEL_416:
      v288 = sub_4227F4(v284, Project_DefineAchievementID_string_, 2u);
      goto LABEL_418;
    }
LABEL_413:
    v287 = &v285->_1.interfaceOffsets->offset;
    while (*(v287 - 1) != Project_DefineAchievementID_string_)
    {
      v287 += 2;
      if (!--v286)
        goto LABEL_416;
    }
    v288 = &v285->vtable[*(u32 *)v287 + 2];
LABEL_418:
    v289 = (*v288)(v284, *(u64 *)(v288 + 8));
    AddFunc_36447680(v280, v281, v289, 0);
    v290 = manager;
    v291 = Allocate(System_Action_string_);
    __ctor(v291, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v294 = _achievementTbl_k__BackingField;
    v295 = v294->klass;
    v296 = *(u16 *)&v294->klass->_2.rank;
    if (!*(u16 *)&v294->klass->_2.rank)
      goto LABEL_429;
    goto LABEL_426;
    if (!*(u16 *)&v294->klass->_2.rank)
    {
LABEL_429:
      v298 = sub_4227F4(v294, Project_DefineAchievementID_string_, 3u);
      goto LABEL_431;
    }
LABEL_426:
    v297 = &v295->_1.interfaceOffsets->offset;
    while (*(v297 - 1) != Project_DefineAchievementID_string_)
    {
      v297 += 2;
      if (!--v296)
        goto LABEL_429;
    }
    v298 = &v295->vtable[*(u32 *)v297 + 3];
LABEL_431:
    v299 = (*v298)(v294, *(u64 *)(v298 + 8));
    AddFunc_36447680(v290, v291, v299, 0);
    v300 = manager;
    v301 = Allocate(System_Action_string_);
    __ctor(v301, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v304 = _achievementTbl_k__BackingField;
    v305 = v304->klass;
    v306 = *(u16 *)&v304->klass->_2.rank;
    if (!*(u16 *)&v304->klass->_2.rank)
      goto LABEL_442;
    goto LABEL_439;
    if (!*(u16 *)&v304->klass->_2.rank)
    {
LABEL_442:
      v308 = sub_4227F4(v304, Project_DefineAchievementID_string_, 4u);
      goto LABEL_444;
    }
LABEL_439:
    v307 = &v305->_1.interfaceOffsets->offset;
    while (*(v307 - 1) != Project_DefineAchievementID_string_)
    {
      v307 += 2;
      if (!--v306)
        goto LABEL_442;
    }
    v308 = &v305->vtable[*(u32 *)v307 + 4];
LABEL_444:
    v309 = (*v308)(v304, *(u64 *)(v308 + 8));
    AddFunc_36447680(v300, v301, v309, 0);
    v310 = manager;
    v311 = Allocate(System_Action_string_);
    __ctor(v311, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v314 = _achievementTbl_k__BackingField;
    v315 = v314->klass;
    v316 = *(u16 *)&v314->klass->_2.rank;
    if (!*(u16 *)&v314->klass->_2.rank)
      goto LABEL_455;
    goto LABEL_452;
    if (!*(u16 *)&v314->klass->_2.rank)
    {
LABEL_455:
      v318 = sub_4227F4(v314, Project_DefineAchievementID_string_, 5u);
      goto LABEL_457;
    }
LABEL_452:
    v317 = &v315->_1.interfaceOffsets->offset;
    while (*(v317 - 1) != Project_DefineAchievementID_string_)
    {
      v317 += 2;
      if (!--v316)
        goto LABEL_455;
    }
    v318 = &v315->vtable[*(u32 *)v317 + 5];
LABEL_457:
    v319 = (*v318)(v314, *(u64 *)(v318 + 8));
    AddFunc_36447680(v310, v311, v319, 0);
    v320 = manager;
    v321 = Allocate(System_Action_string_);
    __ctor(v321, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v324 = _achievementTbl_k__BackingField;
    v325 = v324->klass;
    v326 = *(u16 *)&v324->klass->_2.rank;
    if (!*(u16 *)&v324->klass->_2.rank)
      goto LABEL_468;
    goto LABEL_465;
    if (!*(u16 *)&v324->klass->_2.rank)
    {
LABEL_468:
      v328 = sub_4227F4(v324, Project_DefineAchievementID_string_, 6u);
      goto LABEL_470;
    }
LABEL_465:
    v327 = &v325->_1.interfaceOffsets->offset;
    while (*(v327 - 1) != Project_DefineAchievementID_string_)
    {
      v327 += 2;
      if (!--v326)
        goto LABEL_468;
    }
    v328 = &v325->vtable[*(u32 *)v327 + 6];
LABEL_470:
    v329 = (*v328)(v324, *(u64 *)(v328 + 8));
    AddFunc_36447680(v320, v321, v329, 0);
    v330 = manager;
    v331 = Allocate(System_Action_string_);
    __ctor(v331, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v334 = _achievementTbl_k__BackingField;
    v335 = v334->klass;
    v336 = *(u16 *)&v334->klass->_2.rank;
    if (!*(u16 *)&v334->klass->_2.rank)
      goto LABEL_481;
    goto LABEL_478;
    if (!*(u16 *)&v334->klass->_2.rank)
    {
LABEL_481:
      v338 = sub_4227F4(v334, Project_DefineAchievementID_string_, 7u);
      goto LABEL_483;
    }
LABEL_478:
    v337 = &v335->_1.interfaceOffsets->offset;
    while (*(v337 - 1) != Project_DefineAchievementID_string_)
    {
      v337 += 2;
      if (!--v336)
        goto LABEL_481;
    }
    v338 = &v335->vtable[*(u32 *)v337 + 7];
LABEL_483:
    v339 = (*v338)(v334, *(u64 *)(v338 + 8));
    AddFunc_36447680(v330, v331, v339, 0);
    v340 = manager;
    v341 = Allocate(System_Action_string_);
    __ctor(v341, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v343 = _achievementTbl_k__BackingField;
    v344 = v343->klass;
    v345 = *(u16 *)&v343->klass->_2.rank;
    if (*(u16 *)&v343->klass->_2.rank)
    {
      v346 = &v344->_1.interfaceOffsets->offset;
      while (*(v346 - 1) != Project_DefineAchievementID_string_)
      {
        v346 += 2;
        if (!--v345)
          goto LABEL_491;
      }
      v347 = &v344->vtable[*(u32 *)v346 + 8];
    }
    else
    {
LABEL_491:
      v347 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 8u);
    }
    v348 = (*v347)(v343, *(u64 *)(v347 + 8));
    AddFunc_36447680(v340, v341, v348, 0);
    uid = v774->uid;
    if (uid != 99)
    {
LABEL_13:
      if (uid != 101)
        goto LABEL_14;
      goto LABEL_614;
    }
LABEL_496:
    v349 = manager;
    v350 = Allocate(System_Action_string_);
    __ctor(v350, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v352 = _achievementTbl_k__BackingField;
    v353 = v352->klass;
    v354 = *(u16 *)&v352->klass->_2.rank;
    if (*(u16 *)&v352->klass->_2.rank)
    {
      v355 = &v353->_1.interfaceOffsets->offset;
      while (*(v355 - 1) != Project_DefineAchievementID_string_)
      {
        v355 += 2;
        if (!--v354)
          goto LABEL_505;
      }
      v356 = &v353->vtable[*(u32 *)v355 + 10];
    }
    else
    {
LABEL_505:
      v356 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 0xAu);
    }
    v357 = (*v356)(v352, *(u64 *)(v356 + 8));
    AddFunc_36447680(v349, v350, v357, 0);
    v358 = manager;
    v359 = Allocate(System_Action_string_);
    __ctor(v359, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v362 = _achievementTbl_k__BackingField;
    v363 = v362->klass;
    v364 = *(u16 *)&v362->klass->_2.rank;
    if (!*(u16 *)&v362->klass->_2.rank)
      goto LABEL_521;
    goto LABEL_518;
    if (!*(u16 *)&v362->klass->_2.rank)
    {
LABEL_521:
      v366 = sub_4227F4(v362, Project_DefineAchievementID_string_, 2u);
      goto LABEL_523;
    }
LABEL_518:
    v365 = &v363->_1.interfaceOffsets->offset;
    while (*(v365 - 1) != Project_DefineAchievementID_string_)
    {
      v365 += 2;
      if (!--v364)
        goto LABEL_521;
    }
    v366 = &v363->vtable[*(u32 *)v365 + 2];
LABEL_523:
    v367 = (*v366)(v362, *(u64 *)(v366 + 8));
    AddFunc_36447680(v358, v359, v367, 0);
    v368 = manager;
    v369 = Allocate(System_Action_string_);
    __ctor(v369, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v372 = _achievementTbl_k__BackingField;
    v373 = v372->klass;
    v374 = *(u16 *)&v372->klass->_2.rank;
    if (!*(u16 *)&v372->klass->_2.rank)
      goto LABEL_534;
    goto LABEL_531;
    if (!*(u16 *)&v372->klass->_2.rank)
    {
LABEL_534:
      v376 = sub_4227F4(v372, Project_DefineAchievementID_string_, 3u);
      goto LABEL_536;
    }
LABEL_531:
    v375 = &v373->_1.interfaceOffsets->offset;
    while (*(v375 - 1) != Project_DefineAchievementID_string_)
    {
      v375 += 2;
      if (!--v374)
        goto LABEL_534;
    }
    v376 = &v373->vtable[*(u32 *)v375 + 3];
LABEL_536:
    v377 = (*v376)(v372, *(u64 *)(v376 + 8));
    AddFunc_36447680(v368, v369, v377, 0);
    v378 = manager;
    v379 = Allocate(System_Action_string_);
    __ctor(v379, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v382 = _achievementTbl_k__BackingField;
    v383 = v382->klass;
    v384 = *(u16 *)&v382->klass->_2.rank;
    if (!*(u16 *)&v382->klass->_2.rank)
      goto LABEL_547;
    goto LABEL_544;
    if (!*(u16 *)&v382->klass->_2.rank)
    {
LABEL_547:
      v386 = sub_4227F4(v382, Project_DefineAchievementID_string_, 4u);
      goto LABEL_549;
    }
LABEL_544:
    v385 = &v383->_1.interfaceOffsets->offset;
    while (*(v385 - 1) != Project_DefineAchievementID_string_)
    {
      v385 += 2;
      if (!--v384)
        goto LABEL_547;
    }
    v386 = &v383->vtable[*(u32 *)v385 + 4];
LABEL_549:
    v387 = (*v386)(v382, *(u64 *)(v386 + 8));
    AddFunc_36447680(v378, v379, v387, 0);
    v388 = manager;
    v389 = Allocate(System_Action_string_);
    __ctor(v389, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v392 = _achievementTbl_k__BackingField;
    v393 = v392->klass;
    v394 = *(u16 *)&v392->klass->_2.rank;
    if (!*(u16 *)&v392->klass->_2.rank)
      goto LABEL_560;
    goto LABEL_557;
    if (!*(u16 *)&v392->klass->_2.rank)
    {
LABEL_560:
      v396 = sub_4227F4(v392, Project_DefineAchievementID_string_, 5u);
      goto LABEL_562;
    }
LABEL_557:
    v395 = &v393->_1.interfaceOffsets->offset;
    while (*(v395 - 1) != Project_DefineAchievementID_string_)
    {
      v395 += 2;
      if (!--v394)
        goto LABEL_560;
    }
    v396 = &v393->vtable[*(u32 *)v395 + 5];
LABEL_562:
    v397 = (*v396)(v392, *(u64 *)(v396 + 8));
    AddFunc_36447680(v388, v389, v397, 0);
    v398 = manager;
    v399 = Allocate(System_Action_string_);
    __ctor(v399, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v402 = _achievementTbl_k__BackingField;
    v403 = v402->klass;
    v404 = *(u16 *)&v402->klass->_2.rank;
    if (!*(u16 *)&v402->klass->_2.rank)
      goto LABEL_573;
    goto LABEL_570;
    if (!*(u16 *)&v402->klass->_2.rank)
    {
LABEL_573:
      v406 = sub_4227F4(v402, Project_DefineAchievementID_string_, 6u);
      goto LABEL_575;
    }
LABEL_570:
    v405 = &v403->_1.interfaceOffsets->offset;
    while (*(v405 - 1) != Project_DefineAchievementID_string_)
    {
      v405 += 2;
      if (!--v404)
        goto LABEL_573;
    }
    v406 = &v403->vtable[*(u32 *)v405 + 6];
LABEL_575:
    v407 = (*v406)(v402, *(u64 *)(v406 + 8));
    AddFunc_36447680(v398, v399, v407, 0);
    v408 = manager;
    v409 = Allocate(System_Action_string_);
    __ctor(v409, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v412 = _achievementTbl_k__BackingField;
    v413 = v412->klass;
    v414 = *(u16 *)&v412->klass->_2.rank;
    if (!*(u16 *)&v412->klass->_2.rank)
      goto LABEL_586;
    goto LABEL_583;
    if (!*(u16 *)&v412->klass->_2.rank)
    {
LABEL_586:
      v416 = sub_4227F4(v412, Project_DefineAchievementID_string_, 7u);
      goto LABEL_588;
    }
LABEL_583:
    v415 = &v413->_1.interfaceOffsets->offset;
    while (*(v415 - 1) != Project_DefineAchievementID_string_)
    {
      v415 += 2;
      if (!--v414)
        goto LABEL_586;
    }
    v416 = &v413->vtable[*(u32 *)v415 + 7];
LABEL_588:
    v417 = (*v416)(v412, *(u64 *)(v416 + 8));
    AddFunc_36447680(v408, v409, v417, 0);
    v418 = manager;
    v419 = Allocate(System_Action_string_);
    __ctor(v419, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v422 = _achievementTbl_k__BackingField;
    v423 = v422->klass;
    v424 = *(u16 *)&v422->klass->_2.rank;
    if (!*(u16 *)&v422->klass->_2.rank)
      goto LABEL_599;
    goto LABEL_596;
    if (!*(u16 *)&v422->klass->_2.rank)
    {
LABEL_599:
      v426 = sub_4227F4(v422, Project_DefineAchievementID_string_, 8u);
      goto LABEL_601;
    }
LABEL_596:
    v425 = &v423->_1.interfaceOffsets->offset;
    while (*(v425 - 1) != Project_DefineAchievementID_string_)
    {
      v425 += 2;
      if (!--v424)
        goto LABEL_599;
    }
    v426 = &v423->vtable[*(u32 *)v425 + 8];
LABEL_601:
    v427 = (*v426)(v422, *(u64 *)(v426 + 8));
    AddFunc_36447680(v418, v419, v427, 0);
    v428 = manager;
    v429 = Allocate(System_Action_string_);
    __ctor(v429, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v431 = _achievementTbl_k__BackingField;
    v432 = v431->klass;
    v433 = *(u16 *)&v431->klass->_2.rank;
    if (*(u16 *)&v431->klass->_2.rank)
    {
      v434 = &v432->_1.interfaceOffsets->offset;
      while (*(v434 - 1) != Project_DefineAchievementID_string_)
      {
        v434 += 2;
        if (!--v433)
          goto LABEL_609;
      }
      v435 = &v432->vtable[*(u32 *)v434 + 9];
    }
    else
    {
LABEL_609:
      v435 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 9u);
    }
    v436 = (*v435)(v431, *(u64 *)(v435 + 8));
    AddFunc_36447680(v428, v429, v436, 0);
    uid = v774->uid;
    if (uid != 101)
    {
LABEL_14:
      if (uid != 103)
        goto LABEL_15;
      goto LABEL_745;
    }
LABEL_614:
    v437 = manager;
    v438 = Allocate(System_Action_string_);
    __ctor(v438, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v440 = _achievementTbl_k__BackingField;
    v441 = v440->klass;
    v442 = *(u16 *)&v440->klass->_2.rank;
    if (*(u16 *)&v440->klass->_2.rank)
    {
      v443 = &v441->_1.interfaceOffsets->offset;
      while (*(v443 - 1) != Project_DefineAchievementID_string_)
      {
        v443 += 2;
        if (!--v442)
          goto LABEL_623;
      }
      v444 = (&v441->_1.interfaceOffsets + 2 * *(u32 *)v443 + 39);
    }
    else
    {
LABEL_623:
      v444 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 0xBu);
    }
    v445 = (*v444)(v440, *(u64 *)(v444 + 8));
    AddFunc_36447680(v437, v438, v445, 0);
    v446 = manager;
    v447 = Allocate(System_Action_string_);
    __ctor(v447, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v450 = _achievementTbl_k__BackingField;
    v451 = v450->klass;
    v452 = *(u16 *)&v450->klass->_2.rank;
    if (!*(u16 *)&v450->klass->_2.rank)
      goto LABEL_639;
    goto LABEL_636;
    if (!*(u16 *)&v450->klass->_2.rank)
    {
LABEL_639:
      v454 = sub_4227F4(v450, Project_DefineAchievementID_string_, 2u);
      goto LABEL_641;
    }
LABEL_636:
    v453 = &v451->_1.interfaceOffsets->offset;
    while (*(v453 - 1) != Project_DefineAchievementID_string_)
    {
      v453 += 2;
      if (!--v452)
        goto LABEL_639;
    }
    v454 = &v451->vtable[*(u32 *)v453 + 2];
LABEL_641:
    v455 = (*v454)(v450, *(u64 *)(v454 + 8));
    AddFunc_36447680(v446, v447, v455, 0);
    v456 = manager;
    v457 = Allocate(System_Action_string_);
    __ctor(v457, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v460 = _achievementTbl_k__BackingField;
    v461 = v460->klass;
    v462 = *(u16 *)&v460->klass->_2.rank;
    if (!*(u16 *)&v460->klass->_2.rank)
      goto LABEL_652;
    goto LABEL_649;
    if (!*(u16 *)&v460->klass->_2.rank)
    {
LABEL_652:
      v464 = sub_4227F4(v460, Project_DefineAchievementID_string_, 3u);
      goto LABEL_654;
    }
LABEL_649:
    v463 = &v461->_1.interfaceOffsets->offset;
    while (*(v463 - 1) != Project_DefineAchievementID_string_)
    {
      v463 += 2;
      if (!--v462)
        goto LABEL_652;
    }
    v464 = &v461->vtable[*(u32 *)v463 + 3];
LABEL_654:
    v465 = (*v464)(v460, *(u64 *)(v464 + 8));
    AddFunc_36447680(v456, v457, v465, 0);
    v466 = manager;
    v467 = Allocate(System_Action_string_);
    __ctor(v467, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v470 = _achievementTbl_k__BackingField;
    v471 = v470->klass;
    v472 = *(u16 *)&v470->klass->_2.rank;
    if (!*(u16 *)&v470->klass->_2.rank)
      goto LABEL_665;
    goto LABEL_662;
    if (!*(u16 *)&v470->klass->_2.rank)
    {
LABEL_665:
      v474 = sub_4227F4(v470, Project_DefineAchievementID_string_, 4u);
      goto LABEL_667;
    }
LABEL_662:
    v473 = &v471->_1.interfaceOffsets->offset;
    while (*(v473 - 1) != Project_DefineAchievementID_string_)
    {
      v473 += 2;
      if (!--v472)
        goto LABEL_665;
    }
    v474 = &v471->vtable[*(u32 *)v473 + 4];
LABEL_667:
    v475 = (*v474)(v470, *(u64 *)(v474 + 8));
    AddFunc_36447680(v466, v467, v475, 0);
    v476 = manager;
    v477 = Allocate(System_Action_string_);
    __ctor(v477, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v480 = _achievementTbl_k__BackingField;
    v481 = v480->klass;
    v482 = *(u16 *)&v480->klass->_2.rank;
    if (!*(u16 *)&v480->klass->_2.rank)
      goto LABEL_678;
    goto LABEL_675;
    if (!*(u16 *)&v480->klass->_2.rank)
    {
LABEL_678:
      v484 = sub_4227F4(v480, Project_DefineAchievementID_string_, 5u);
      goto LABEL_680;
    }
LABEL_675:
    v483 = &v481->_1.interfaceOffsets->offset;
    while (*(v483 - 1) != Project_DefineAchievementID_string_)
    {
      v483 += 2;
      if (!--v482)
        goto LABEL_678;
    }
    v484 = &v481->vtable[*(u32 *)v483 + 5];
LABEL_680:
    v485 = (*v484)(v480, *(u64 *)(v484 + 8));
    AddFunc_36447680(v476, v477, v485, 0);
    v486 = manager;
    v487 = Allocate(System_Action_string_);
    __ctor(v487, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v490 = _achievementTbl_k__BackingField;
    v491 = v490->klass;
    v492 = *(u16 *)&v490->klass->_2.rank;
    if (!*(u16 *)&v490->klass->_2.rank)
      goto LABEL_691;
    goto LABEL_688;
    if (!*(u16 *)&v490->klass->_2.rank)
    {
LABEL_691:
      v494 = sub_4227F4(v490, Project_DefineAchievementID_string_, 6u);
      goto LABEL_693;
    }
LABEL_688:
    v493 = &v491->_1.interfaceOffsets->offset;
    while (*(v493 - 1) != Project_DefineAchievementID_string_)
    {
      v493 += 2;
      if (!--v492)
        goto LABEL_691;
    }
    v494 = &v491->vtable[*(u32 *)v493 + 6];
LABEL_693:
    v495 = (*v494)(v490, *(u64 *)(v494 + 8));
    AddFunc_36447680(v486, v487, v495, 0);
    v496 = manager;
    v497 = Allocate(System_Action_string_);
    __ctor(v497, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v500 = _achievementTbl_k__BackingField;
    v501 = v500->klass;
    v502 = *(u16 *)&v500->klass->_2.rank;
    if (!*(u16 *)&v500->klass->_2.rank)
      goto LABEL_704;
    goto LABEL_701;
    if (!*(u16 *)&v500->klass->_2.rank)
    {
LABEL_704:
      v504 = sub_4227F4(v500, Project_DefineAchievementID_string_, 7u);
      goto LABEL_706;
    }
LABEL_701:
    v503 = &v501->_1.interfaceOffsets->offset;
    while (*(v503 - 1) != Project_DefineAchievementID_string_)
    {
      v503 += 2;
      if (!--v502)
        goto LABEL_704;
    }
    v504 = &v501->vtable[*(u32 *)v503 + 7];
LABEL_706:
    v505 = (*v504)(v500, *(u64 *)(v504 + 8));
    AddFunc_36447680(v496, v497, v505, 0);
    v506 = manager;
    v507 = Allocate(System_Action_string_);
    __ctor(v507, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v510 = _achievementTbl_k__BackingField;
    v511 = v510->klass;
    v512 = *(u16 *)&v510->klass->_2.rank;
    if (!*(u16 *)&v510->klass->_2.rank)
      goto LABEL_717;
    goto LABEL_714;
    if (!*(u16 *)&v510->klass->_2.rank)
    {
LABEL_717:
      v514 = sub_4227F4(v510, Project_DefineAchievementID_string_, 8u);
      goto LABEL_719;
    }
LABEL_714:
    v513 = &v511->_1.interfaceOffsets->offset;
    while (*(v513 - 1) != Project_DefineAchievementID_string_)
    {
      v513 += 2;
      if (!--v512)
        goto LABEL_717;
    }
    v514 = &v511->vtable[*(u32 *)v513 + 8];
LABEL_719:
    v515 = (*v514)(v510, *(u64 *)(v514 + 8));
    AddFunc_36447680(v506, v507, v515, 0);
    v516 = manager;
    v517 = Allocate(System_Action_string_);
    __ctor(v517, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v520 = _achievementTbl_k__BackingField;
    v521 = v520->klass;
    v522 = *(u16 *)&v520->klass->_2.rank;
    if (!*(u16 *)&v520->klass->_2.rank)
      goto LABEL_730;
    goto LABEL_727;
    if (!*(u16 *)&v520->klass->_2.rank)
    {
LABEL_730:
      v524 = sub_4227F4(v520, Project_DefineAchievementID_string_, 9u);
      goto LABEL_732;
    }
LABEL_727:
    v523 = &v521->_1.interfaceOffsets->offset;
    while (*(v523 - 1) != Project_DefineAchievementID_string_)
    {
      v523 += 2;
      if (!--v522)
        goto LABEL_730;
    }
    v524 = &v521->vtable[*(u32 *)v523 + 9];
LABEL_732:
    v525 = (*v524)(v520, *(u64 *)(v524 + 8));
    AddFunc_36447680(v516, v517, v525, 0);
    v526 = manager;
    v527 = Allocate(System_Action_string_);
    __ctor(v527, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v529 = _achievementTbl_k__BackingField;
    v530 = v529->klass;
    v531 = *(u16 *)&v529->klass->_2.rank;
    if (*(u16 *)&v529->klass->_2.rank)
    {
      v532 = &v530->_1.interfaceOffsets->offset;
      while (*(v532 - 1) != Project_DefineAchievementID_string_)
      {
        v532 += 2;
        if (!--v531)
          goto LABEL_740;
      }
      v533 = &v530->vtable[*(u32 *)v532 + 10];
    }
    else
    {
LABEL_740:
      v533 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 0xAu);
    }
    v534 = (*v533)(v529, *(u64 *)(v533 + 8));
    AddFunc_36447680(v526, v527, v534, 0);
    uid = v774->uid;
    if (uid != 103)
    {
LABEL_15:
      if (uid != 105)
        goto LABEL_16;
      goto LABEL_890;
    }
LABEL_745:
    v535 = manager;
    v536 = Allocate(System_Action_string_);
    __ctor(v536, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v538 = _achievementTbl_k__BackingField;
    v539 = v538->klass;
    v540 = *(u16 *)&v538->klass->_2.rank;
    if (*(u16 *)&v538->klass->_2.rank)
    {
      v541 = &v539->_1.interfaceOffsets->offset;
      while (*(v541 - 1) != Project_DefineAchievementID_string_)
      {
        v541 += 2;
        if (!--v540)
          goto LABEL_754;
      }
      v542 = &(&v539->rgctx_data)[2 * *(u32 *)v541 + 39];
    }
    else
    {
LABEL_754:
      v542 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 0xCu);
    }
    v543 = (*v542)(v538, *(u64 *)(v542 + 8));
    AddFunc_36447680(v535, v536, v543, 0);
    v544 = manager;
    v545 = Allocate(System_Action_string_);
    __ctor(v545, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v548 = _achievementTbl_k__BackingField;
    v549 = v548->klass;
    v550 = *(u16 *)&v548->klass->_2.rank;
    if (!*(u16 *)&v548->klass->_2.rank)
      goto LABEL_770;
    goto LABEL_767;
    if (!*(u16 *)&v548->klass->_2.rank)
    {
LABEL_770:
      v552 = sub_4227F4(v548, Project_DefineAchievementID_string_, 2u);
      goto LABEL_772;
    }
LABEL_767:
    v551 = &v549->_1.interfaceOffsets->offset;
    while (*(v551 - 1) != Project_DefineAchievementID_string_)
    {
      v551 += 2;
      if (!--v550)
        goto LABEL_770;
    }
    v552 = &v549->vtable[*(u32 *)v551 + 2];
LABEL_772:
    v553 = (*v552)(v548, *(u64 *)(v552 + 8));
    AddFunc_36447680(v544, v545, v553, 0);
    v554 = manager;
    v555 = Allocate(System_Action_string_);
    __ctor(v555, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v558 = _achievementTbl_k__BackingField;
    v559 = v558->klass;
    v560 = *(u16 *)&v558->klass->_2.rank;
    if (!*(u16 *)&v558->klass->_2.rank)
      goto LABEL_783;
    goto LABEL_780;
    if (!*(u16 *)&v558->klass->_2.rank)
    {
LABEL_783:
      v562 = sub_4227F4(v558, Project_DefineAchievementID_string_, 3u);
      goto LABEL_785;
    }
LABEL_780:
    v561 = &v559->_1.interfaceOffsets->offset;
    while (*(v561 - 1) != Project_DefineAchievementID_string_)
    {
      v561 += 2;
      if (!--v560)
        goto LABEL_783;
    }
    v562 = &v559->vtable[*(u32 *)v561 + 3];
LABEL_785:
    v563 = (*v562)(v558, *(u64 *)(v562 + 8));
    AddFunc_36447680(v554, v555, v563, 0);
    v564 = manager;
    v565 = Allocate(System_Action_string_);
    __ctor(v565, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v568 = _achievementTbl_k__BackingField;
    v569 = v568->klass;
    v570 = *(u16 *)&v568->klass->_2.rank;
    if (!*(u16 *)&v568->klass->_2.rank)
      goto LABEL_796;
    goto LABEL_793;
    if (!*(u16 *)&v568->klass->_2.rank)
    {
LABEL_796:
      v572 = sub_4227F4(v568, Project_DefineAchievementID_string_, 4u);
      goto LABEL_798;
    }
LABEL_793:
    v571 = &v569->_1.interfaceOffsets->offset;
    while (*(v571 - 1) != Project_DefineAchievementID_string_)
    {
      v571 += 2;
      if (!--v570)
        goto LABEL_796;
    }
    v572 = &v569->vtable[*(u32 *)v571 + 4];
LABEL_798:
    v573 = (*v572)(v568, *(u64 *)(v572 + 8));
    AddFunc_36447680(v564, v565, v573, 0);
    v574 = manager;
    v575 = Allocate(System_Action_string_);
    __ctor(v575, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v578 = _achievementTbl_k__BackingField;
    v579 = v578->klass;
    v580 = *(u16 *)&v578->klass->_2.rank;
    if (!*(u16 *)&v578->klass->_2.rank)
      goto LABEL_809;
    goto LABEL_806;
    if (!*(u16 *)&v578->klass->_2.rank)
    {
LABEL_809:
      v582 = sub_4227F4(v578, Project_DefineAchievementID_string_, 5u);
      goto LABEL_811;
    }
LABEL_806:
    v581 = &v579->_1.interfaceOffsets->offset;
    while (*(v581 - 1) != Project_DefineAchievementID_string_)
    {
      v581 += 2;
      if (!--v580)
        goto LABEL_809;
    }
    v582 = &v579->vtable[*(u32 *)v581 + 5];
LABEL_811:
    v583 = (*v582)(v578, *(u64 *)(v582 + 8));
    AddFunc_36447680(v574, v575, v583, 0);
    v584 = manager;
    v585 = Allocate(System_Action_string_);
    __ctor(v585, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v588 = _achievementTbl_k__BackingField;
    v589 = v588->klass;
    v590 = *(u16 *)&v588->klass->_2.rank;
    if (!*(u16 *)&v588->klass->_2.rank)
      goto LABEL_822;
    goto LABEL_819;
    if (!*(u16 *)&v588->klass->_2.rank)
    {
LABEL_822:
      v592 = sub_4227F4(v588, Project_DefineAchievementID_string_, 6u);
      goto LABEL_824;
    }
LABEL_819:
    v591 = &v589->_1.interfaceOffsets->offset;
    while (*(v591 - 1) != Project_DefineAchievementID_string_)
    {
      v591 += 2;
      if (!--v590)
        goto LABEL_822;
    }
    v592 = &v589->vtable[*(u32 *)v591 + 6];
LABEL_824:
    v593 = (*v592)(v588, *(u64 *)(v592 + 8));
    AddFunc_36447680(v584, v585, v593, 0);
    v594 = manager;
    v595 = Allocate(System_Action_string_);
    __ctor(v595, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v598 = _achievementTbl_k__BackingField;
    v599 = v598->klass;
    v600 = *(u16 *)&v598->klass->_2.rank;
    if (!*(u16 *)&v598->klass->_2.rank)
      goto LABEL_835;
    goto LABEL_832;
    if (!*(u16 *)&v598->klass->_2.rank)
    {
LABEL_835:
      v602 = sub_4227F4(v598, Project_DefineAchievementID_string_, 7u);
      goto LABEL_837;
    }
LABEL_832:
    v601 = &v599->_1.interfaceOffsets->offset;
    while (*(v601 - 1) != Project_DefineAchievementID_string_)
    {
      v601 += 2;
      if (!--v600)
        goto LABEL_835;
    }
    v602 = &v599->vtable[*(u32 *)v601 + 7];
LABEL_837:
    v603 = (*v602)(v598, *(u64 *)(v602 + 8));
    AddFunc_36447680(v594, v595, v603, 0);
    v604 = manager;
    v605 = Allocate(System_Action_string_);
    __ctor(v605, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v608 = _achievementTbl_k__BackingField;
    v609 = v608->klass;
    v610 = *(u16 *)&v608->klass->_2.rank;
    if (!*(u16 *)&v608->klass->_2.rank)
      goto LABEL_848;
    goto LABEL_845;
    if (!*(u16 *)&v608->klass->_2.rank)
    {
LABEL_848:
      v612 = sub_4227F4(v608, Project_DefineAchievementID_string_, 8u);
      goto LABEL_850;
    }
LABEL_845:
    v611 = &v609->_1.interfaceOffsets->offset;
    while (*(v611 - 1) != Project_DefineAchievementID_string_)
    {
      v611 += 2;
      if (!--v610)
        goto LABEL_848;
    }
    v612 = &v609->vtable[*(u32 *)v611 + 8];
LABEL_850:
    v613 = (*v612)(v608, *(u64 *)(v612 + 8));
    AddFunc_36447680(v604, v605, v613, 0);
    v614 = manager;
    v615 = Allocate(System_Action_string_);
    __ctor(v615, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v618 = _achievementTbl_k__BackingField;
    v619 = v618->klass;
    v620 = *(u16 *)&v618->klass->_2.rank;
    if (!*(u16 *)&v618->klass->_2.rank)
      goto LABEL_861;
    goto LABEL_858;
    if (!*(u16 *)&v618->klass->_2.rank)
    {
LABEL_861:
      v622 = sub_4227F4(v618, Project_DefineAchievementID_string_, 9u);
      goto LABEL_863;
    }
LABEL_858:
    v621 = &v619->_1.interfaceOffsets->offset;
    while (*(v621 - 1) != Project_DefineAchievementID_string_)
    {
      v621 += 2;
      if (!--v620)
        goto LABEL_861;
    }
    v622 = &v619->vtable[*(u32 *)v621 + 9];
LABEL_863:
    v623 = (*v622)(v618, *(u64 *)(v622 + 8));
    AddFunc_36447680(v614, v615, v623, 0);
    v624 = manager;
    v625 = Allocate(System_Action_string_);
    __ctor(v625, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v628 = _achievementTbl_k__BackingField;
    v629 = v628->klass;
    v630 = *(u16 *)&v628->klass->_2.rank;
    if (!*(u16 *)&v628->klass->_2.rank)
      goto LABEL_874;
    goto LABEL_871;
    if (!*(u16 *)&v628->klass->_2.rank)
    {
LABEL_874:
      v632 = sub_4227F4(v628, Project_DefineAchievementID_string_, 0xAu);
      goto LABEL_876;
    }
LABEL_871:
    v631 = &v629->_1.interfaceOffsets->offset;
    while (*(v631 - 1) != Project_DefineAchievementID_string_)
    {
      v631 += 2;
      if (!--v630)
        goto LABEL_874;
    }
    v632 = &v629->vtable[*(u32 *)v631 + 10];
LABEL_876:
    v633 = (*v632)(v628, *(u64 *)(v632 + 8));
    AddFunc_36447680(v624, v625, v633, 0);
    v634 = manager;
    v635 = Allocate(System_Action_string_);
    __ctor(v635, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v637 = v774;
    v639 = _achievementTbl_k__BackingField;
    v640 = v639->klass;
    v641 = *(u16 *)&v639->klass->_2.rank;
    if (!*(u16 *)&v639->klass->_2.rank)
      goto LABEL_887;
    goto LABEL_884;
    if (!*(u16 *)&v639->klass->_2.rank)
    {
LABEL_887:
      v643 = sub_4227F4(v639, Project_DefineAchievementID_string_, 0xBu);
      goto LABEL_889;
    }
LABEL_884:
    v642 = &v640->_1.interfaceOffsets->offset;
    while (*(v642 - 1) != Project_DefineAchievementID_string_)
    {
      v642 += 2;
      if (!--v641)
        goto LABEL_887;
    }
    v643 = (&v640->_1.interfaceOffsets + 2 * *(u32 *)v642 + 39);
LABEL_889:
    v644 = (*v643)(v639, *(u64 *)(v643 + 8));
    AddFunc_36447680(v634, v635, v644, 0);
    if (v637->uid != 105)
    {
LABEL_16:
LABEL_17:
      StartActions(manager, 5.0, 0);
      return;
    }
LABEL_890:
    v645 = manager;
    v646 = Allocate(System_Action_string_);
    __ctor(v646, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v648 = _achievementTbl_k__BackingField;
    v649 = v648->klass;
    v650 = *(u16 *)&v648->klass->_2.rank;
    if (*(u16 *)&v648->klass->_2.rank)
    {
      v651 = &v649->_1.interfaceOffsets->offset;
      while (*(v651 - 1) != Project_DefineAchievementID_string_)
      {
        v651 += 2;
        if (!--v650)
          goto LABEL_899;
      }
      v652 = &v649->vtable[*(u32 *)v651 + 13];
    }
    else
    {
LABEL_899:
      v652 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 0xDu);
    }
    v653 = (*v652)(v648, *(u64 *)(v652 + 8));
    AddFunc_36447680(v645, v646, v653, 0);
    if (!sBtlIsSuperRaido())
    {
LABEL_907:
      v654 = manager;
      v655 = Allocate(System_Action_string_);
      __ctor(v655, 0, Method_Project_Achievement_Unlock___83873840, 0);
      v658 = _achievementTbl_k__BackingField;
      v659 = v658->klass;
      v660 = *(u16 *)&v658->klass->_2.rank;
      if (!*(u16 *)&v658->klass->_2.rank)
        goto LABEL_926;
      goto LABEL_923;
      if (!*(u16 *)&v658->klass->_2.rank)
      {
LABEL_926:
        v669 = sub_4227F4(v658, Project_DefineAchievementID_string_, 2u);
        goto LABEL_928;
      }
LABEL_923:
      v668 = &v659->_1.interfaceOffsets->offset;
      while (*(v668 - 1) != Project_DefineAchievementID_string_)
      {
        v668 += 2;
        if (!--v660)
          goto LABEL_926;
      }
      v669 = &v659->vtable[*(u32 *)v668 + 2];
LABEL_928:
      v670 = (*v669)(v658, *(u64 *)(v669 + 8));
      AddFunc_36447680(v654, v655, v670, 0);
      v671 = manager;
      v672 = Allocate(System_Action_string_);
      __ctor(v672, 0, Method_Project_Achievement_Unlock___83873840, 0);
      v675 = _achievementTbl_k__BackingField;
      v676 = v675->klass;
      v677 = *(u16 *)&v675->klass->_2.rank;
      if (!*(u16 *)&v675->klass->_2.rank)
        goto LABEL_939;
      goto LABEL_936;
      if (!*(u16 *)&v675->klass->_2.rank)
      {
LABEL_939:
        v679 = sub_4227F4(v675, Project_DefineAchievementID_string_, 3u);
        goto LABEL_941;
      }
LABEL_936:
      v678 = &v676->_1.interfaceOffsets->offset;
      while (*(v678 - 1) != Project_DefineAchievementID_string_)
      {
        v678 += 2;
        if (!--v677)
          goto LABEL_939;
      }
      v679 = &v676->vtable[*(u32 *)v678 + 3];
LABEL_941:
      v680 = (*v679)(v675, *(u64 *)(v679 + 8));
      AddFunc_36447680(v671, v672, v680, 0);
      v681 = manager;
      v682 = Allocate(System_Action_string_);
      __ctor(v682, 0, Method_Project_Achievement_Unlock___83873840, 0);
      v685 = _achievementTbl_k__BackingField;
      v686 = v685->klass;
      v687 = *(u16 *)&v685->klass->_2.rank;
      if (!*(u16 *)&v685->klass->_2.rank)
        goto LABEL_952;
      goto LABEL_949;
      if (!*(u16 *)&v685->klass->_2.rank)
      {
LABEL_952:
        v689 = sub_4227F4(v685, Project_DefineAchievementID_string_, 4u);
        goto LABEL_954;
      }
LABEL_949:
      v688 = &v686->_1.interfaceOffsets->offset;
      while (*(v688 - 1) != Project_DefineAchievementID_string_)
      {
        v688 += 2;
        if (!--v687)
          goto LABEL_952;
      }
      v689 = &v686->vtable[*(u32 *)v688 + 4];
LABEL_954:
      v690 = (*v689)(v685, *(u64 *)(v689 + 8));
      AddFunc_36447680(v681, v682, v690, 0);
      v691 = manager;
      v692 = Allocate(System_Action_string_);
      __ctor(v692, 0, Method_Project_Achievement_Unlock___83873840, 0);
      v695 = _achievementTbl_k__BackingField;
      v696 = v695->klass;
      v697 = *(u16 *)&v695->klass->_2.rank;
      if (!*(u16 *)&v695->klass->_2.rank)
        goto LABEL_965;
      goto LABEL_962;
      if (!*(u16 *)&v695->klass->_2.rank)
      {
LABEL_965:
        v699 = sub_4227F4(v695, Project_DefineAchievementID_string_, 5u);
        goto LABEL_967;
      }
LABEL_962:
      v698 = &v696->_1.interfaceOffsets->offset;
      while (*(v698 - 1) != Project_DefineAchievementID_string_)
      {
        v698 += 2;
        if (!--v697)
          goto LABEL_965;
      }
      v699 = &v696->vtable[*(u32 *)v698 + 5];
LABEL_967:
      v700 = (*v699)(v695, *(u64 *)(v699 + 8));
      AddFunc_36447680(v691, v692, v700, 0);
      v701 = manager;
      v702 = Allocate(System_Action_string_);
      __ctor(v702, 0, Method_Project_Achievement_Unlock___83873840, 0);
      v705 = _achievementTbl_k__BackingField;
      v706 = v705->klass;
      v707 = *(u16 *)&v705->klass->_2.rank;
      if (!*(u16 *)&v705->klass->_2.rank)
        goto LABEL_978;
      goto LABEL_975;
      if (!*(u16 *)&v705->klass->_2.rank)
      {
LABEL_978:
        v709 = sub_4227F4(v705, Project_DefineAchievementID_string_, 6u);
        goto LABEL_980;
      }
LABEL_975:
      v708 = &v706->_1.interfaceOffsets->offset;
      while (*(v708 - 1) != Project_DefineAchievementID_string_)
      {
        v708 += 2;
        if (!--v707)
          goto LABEL_978;
      }
      v709 = &v706->vtable[*(u32 *)v708 + 6];
LABEL_980:
      v710 = (*v709)(v705, *(u64 *)(v709 + 8));
      AddFunc_36447680(v701, v702, v710, 0);
      v711 = manager;
      v712 = Allocate(System_Action_string_);
      __ctor(v712, 0, Method_Project_Achievement_Unlock___83873840, 0);
      v715 = _achievementTbl_k__BackingField;
      v716 = v715->klass;
      v717 = *(u16 *)&v715->klass->_2.rank;
      if (!*(u16 *)&v715->klass->_2.rank)
        goto LABEL_991;
      goto LABEL_988;
      if (!*(u16 *)&v715->klass->_2.rank)
      {
LABEL_991:
        v719 = sub_4227F4(v715, Project_DefineAchievementID_string_, 7u);
        goto LABEL_993;
      }
LABEL_988:
      v718 = &v716->_1.interfaceOffsets->offset;
      while (*(v718 - 1) != Project_DefineAchievementID_string_)
      {
        v718 += 2;
        if (!--v717)
          goto LABEL_991;
      }
      v719 = &v716->vtable[*(u32 *)v718 + 7];
LABEL_993:
      v720 = (*v719)(v715, *(u64 *)(v719 + 8));
      AddFunc_36447680(v711, v712, v720, 0);
      v721 = manager;
      v722 = Allocate(System_Action_string_);
      __ctor(v722, 0, Method_Project_Achievement_Unlock___83873840, 0);
      v725 = _achievementTbl_k__BackingField;
      v726 = v725->klass;
      v727 = *(u16 *)&v725->klass->_2.rank;
      if (!*(u16 *)&v725->klass->_2.rank)
        goto LABEL_1004;
      goto LABEL_1001;
      if (!*(u16 *)&v725->klass->_2.rank)
      {
LABEL_1004:
        v729 = sub_4227F4(v725, Project_DefineAchievementID_string_, 8u);
        goto LABEL_1006;
      }
LABEL_1001:
      v728 = &v726->_1.interfaceOffsets->offset;
      while (*(v728 - 1) != Project_DefineAchievementID_string_)
      {
        v728 += 2;
        if (!--v727)
          goto LABEL_1004;
      }
      v729 = &v726->vtable[*(u32 *)v728 + 8];
LABEL_1006:
      v730 = (*v729)(v725, *(u64 *)(v729 + 8));
      AddFunc_36447680(v721, v722, v730, 0);
      v731 = manager;
      v732 = Allocate(System_Action_string_);
      __ctor(v732, 0, Method_Project_Achievement_Unlock___83873840, 0);
      v735 = _achievementTbl_k__BackingField;
      v736 = v735->klass;
      v737 = *(u16 *)&v735->klass->_2.rank;
      if (!*(u16 *)&v735->klass->_2.rank)
        goto LABEL_1017;
      goto LABEL_1014;
      if (!*(u16 *)&v735->klass->_2.rank)
      {
LABEL_1017:
        v739 = sub_4227F4(v735, Project_DefineAchievementID_string_, 9u);
        goto LABEL_1019;
      }
LABEL_1014:
      v738 = &v736->_1.interfaceOffsets->offset;
      while (*(v738 - 1) != Project_DefineAchievementID_string_)
      {
        v738 += 2;
        if (!--v737)
          goto LABEL_1017;
      }
      v739 = &v736->vtable[*(u32 *)v738 + 9];
LABEL_1019:
      v740 = (*v739)(v735, *(u64 *)(v739 + 8));
      AddFunc_36447680(v731, v732, v740, 0);
      v741 = manager;
      v742 = Allocate(System_Action_string_);
      __ctor(v742, 0, Method_Project_Achievement_Unlock___83873840, 0);
      v745 = _achievementTbl_k__BackingField;
      v746 = v745->klass;
      v747 = *(u16 *)&v745->klass->_2.rank;
      if (!*(u16 *)&v745->klass->_2.rank)
        goto LABEL_1030;
      goto LABEL_1027;
      if (!*(u16 *)&v745->klass->_2.rank)
      {
LABEL_1030:
        v749 = sub_4227F4(v745, Project_DefineAchievementID_string_, 0xAu);
        goto LABEL_1032;
      }
LABEL_1027:
      v748 = &v746->_1.interfaceOffsets->offset;
      while (*(v748 - 1) != Project_DefineAchievementID_string_)
      {
        v748 += 2;
        if (!--v747)
          goto LABEL_1030;
      }
      v749 = &v746->vtable[*(u32 *)v748 + 10];
LABEL_1032:
      v750 = (*v749)(v745, *(u64 *)(v749 + 8));
      AddFunc_36447680(v741, v742, v750, 0);
      v751 = manager;
      v752 = Allocate(System_Action_string_);
      __ctor(v752, 0, Method_Project_Achievement_Unlock___83873840, 0);
      v755 = _achievementTbl_k__BackingField;
      v756 = v755->klass;
      v757 = *(u16 *)&v755->klass->_2.rank;
      if (!*(u16 *)&v755->klass->_2.rank)
        goto LABEL_1043;
      goto LABEL_1040;
      if (!*(u16 *)&v755->klass->_2.rank)
      {
LABEL_1043:
        v759 = sub_4227F4(v755, Project_DefineAchievementID_string_, 0xBu);
        goto LABEL_1045;
      }
LABEL_1040:
      v758 = &v756->_1.interfaceOffsets->offset;
      while (*(v758 - 1) != Project_DefineAchievementID_string_)
      {
        v758 += 2;
        if (!--v757)
          goto LABEL_1043;
      }
      v759 = (&v756->_1.interfaceOffsets + 2 * *(u32 *)v758 + 39);
LABEL_1045:
      v760 = (*v759)(v755, *(u64 *)(v759 + 8));
      AddFunc_36447680(v751, v752, v760, 0);
      v761 = manager;
      v762 = Allocate(System_Action_string_);
      __ctor(v762, 0, Method_Project_Achievement_Unlock___83873840, 0);
      v765 = _achievementTbl_k__BackingField;
      v766 = v765->klass;
      v767 = *(u16 *)&v765->klass->_2.rank;
      if (!*(u16 *)&v765->klass->_2.rank)
        goto LABEL_1056;
      goto LABEL_1053;
      if (!*(u16 *)&v765->klass->_2.rank)
      {
LABEL_1056:
        v769 = sub_4227F4(v765, Project_DefineAchievementID_string_, 0xCu);
        goto LABEL_1058;
      }
LABEL_1053:
      v768 = &v766->_1.interfaceOffsets->offset;
      while (*(v768 - 1) != Project_DefineAchievementID_string_)
      {
        v768 += 2;
        if (!--v767)
          goto LABEL_1056;
      }
      v769 = &(&v766->rgctx_data)[2 * *(u32 *)v768 + 39];
LABEL_1058:
      v770 = (*v769)(v765, *(u64 *)(v769 + 8));
      AddFunc_36447680(v761, v762, v770, 0);
      goto LABEL_17;
    }
    v661 = manager;
    v662 = Allocate(System_Action_string_);
    __ctor(v662, 0, Method_Project_Achievement_Unlock___83873840, 0);
    v665 = _achievementTbl_k__BackingField;
    v666 = v665->klass;
    v667 = *(u16 *)&v665->klass->_2.rank;
    if (!*(u16 *)&v665->klass->_2.rank)
      goto LABEL_1066;
    goto LABEL_1063;
    if (!*(u16 *)&v665->klass->_2.rank)
    {
LABEL_1066:
      v772 = sub_4227F4(v665, Project_DefineAchievementID_string_, 0xEu);
      goto LABEL_1068;
    }
LABEL_1063:
    v771 = &v666->_1.interfaceOffsets->offset;
    while (*(v771 - 1) != Project_DefineAchievementID_string_)
    {
      v771 += 2;
      if (!--v667)
        goto LABEL_1066;
    }
    v772 = &v666->vtable[*(u32 *)v771 + 14];
LABEL_1068:
    v773 = (*v772)(v665, *(u64 *)(v772 + 8));
    AddFunc_36447680(v661, v662, v773, 0);
    goto LABEL_907;
  }
}

// 0x1a2e5d0
static void Draw(evtPictureProcessData_t *data) {
  u32 uid;
  u32 v4;
  s32 v6;
  s32 ui_mode;
  sdfDrawTag_t *v9;
  s32 v10;
  s32 gPictureOtEx_local;
  f32 v12;
  f32 v14;
  void *p_defaultCameraScreen;
  void *v17;
  s32 Item;
  s32 v20;
  f32 v21;
  f32 v22;
  s32 v25;
  s32 v27;
  long f64 v28;
  f32 v29;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 v34;
  f32 v35;
  f32 v36;
  void *mesh;
  s32 v39;
  s32 v41;
  s32 v43;
  s32 v45;
  s32 v46;
  u32 v47;
  void *v49;
  Il2CppObject *Component_object;
  s32 v52;
  Il2CppObject *v53;
  s32 v54;
  s32 v55;
  s32 cutInType;
  f32 v57;
  s32 v60;
  s32 v62;
  s32 v65;
  s32 v67;
  s32 v70;
  s32 v72;
  s32 v75;
  s32 v77;
  s32 v80;
  s32 v81;
  u32 v83;
  s32 v85;
  s32 v86;
  u32 v88;
  s32 v90;
  s32 v91;
  u32 v93;
  s32 v95;
  s32 v96;
  u32 v98;
  s32 v99;
  s32 v101;
  s32 v102;
  s32 v103;
  s32 v104;
  s32 v105;
  u32 v106;
  s32 width;
  s32 v109;
  s32 v110;
  s32 height;
  s32 v112;
  f32 v113;
  f32 v114;
  f32 v115;
  f32 v116;
  s64 v117;
  s64 v118;
  sdfIVector4_t v119;
  sdfIVector4_t v120;
  sdfIVector4_t v121;
  sdfIVector4_t v122;
  sdfIVector4_t v123;
  sdfIVector4_t v124;
  sdfIVector4_t v125;
  sdfIVector4_t v126;
  sdfIVector4_t v127;
  sdfIVector4_t v128;
  sdfIVector4_t v129;
  sdfIVector4_t v130;
  sdfIVector4_t v131;
  sdfIVector4_t v132;
  sdfIVector4_t v133;
  sdfIVector4_t v134;
  sdfIVector4_t v135;
  sdfIVector4_t v136;
  sdfIVector4_t v137;
  sdfIVector4_t v138;
  sdfIVector4_t v139;
  sdfIVector4_t v140;
  sdfIVector4_t v141;
  sdfIVector4_t v142;
  sdfIVector4_t v143;
  sdfIVector4_t v144;
  sdfIVector4_t v145;
  sdfIVector4_t v146;
  sdfIVector4_t v147;
  sdfIVector4_t v148;
  sdfIVector4_t v149;
  sdfVector2_t v150;
  sdfVector2_t v151;
  sdfVector2_t v152;
  sdfVector3_t v153;
  sdfVector3_t v154;
  sdfVector4_t v155;

  uid = data->uid;
  v117 = 0;
  v118 = 0;
  if (uid == 3 && !data->drawGouto)
  {
    if (*((u8 *)*((MethodInfo *)cmpItem + 2).virtualMethodPointer + 200))
    {
      v6 = evtPictureUseGoutoAnim();
      if (v6 == 19)
        zyarEnd = 1;
LABEL_23:
      SetInteger(uiObj->gouto_face_anim, "anim", v6, 0);
      data->drawGouto = 1;
      if (data->draw1st)
        goto LABEL_24;
      goto LABEL_6;
    }
    v6 = 1;
    goto LABEL_23;
  }
  if (data->draw1st)
    goto LABEL_24;
LABEL_6:
  v4 = data->uid - 80;
  if (v4 <= 0x18 && ((1 << v4) & 0x1555555) != 0)
  {
    moviePlay(32, 0, 1);
  }
LABEL_24:
  evtPictureAchievementUnlock(data);
  ui_mode = data->ui_mode;
  ++data->draw1st;
  if (ui_mode)
  {
    v9 = Allocate(sdfDrawTag_t);
    _ctor(v9, 0);
    if ((data->type & 0x1000000) != 0)
      v10 = 92;
    else
      v10 = 109;
    if (gPictureOtEx)
      gPictureOtEx_local = gPictureOtEx;
    else
      gPictureOtEx_local = v10;
    sdfDrawTagInit(v9);
    itfMiscDrawAlphaPrim(v9, 0, 0);
    v12 = (f32)(data->tex3d->klass->vtable._5_get_width.methodPtr)(data->tex3d, data->tex3d->klass->vtable._5_get_width.method)
        / 960.0;
    v14 = (f32)(data->tex3d->klass->vtable._7_get_height.methodPtr)(data->tex3d, data->tex3d->klass->vtable._7_get_height.method)
        / 540.0;
    p_defaultCameraScreen = &defaultCameraScreen;
    *(u64 *)&v119.x = &data->xy;
    *(u64 *)&v119.z = 0;
    v17 = p_defaultCameraScreen;
    Item = get_Item(v119, 0);
    *(u64 *)&v120.z = 0;
    *(u64 *)&v120.x = &data->ofs_xy;
    v20 = get_Item(v120, 0);
    v21 = X_36118416(v17, Item + 16 * v20 + 28672, 0);
    *(u64 *)&v121.x = &data->xy;
    *(u64 *)&v121.z = 1;
    v22 = v21;
    v25 = get_Item(v121, 0);
    *(u64 *)&v122.x = &data->ofs_xy;
    *(u64 *)&v122.z = 1;
    v27 = get_Item(v122, 0);
    v29 = Y_36118480(defaultCameraScreen, v25 + 8 * v27 + 30976, 0);
    v30 = 0.0;
    if ((data->flag & 0x10) != 0)
      v31 = v14 * 0.5;
    else
      v31 = 0.0;
    if ((data->flag & 0x10) != 0)
      v32 = v12 * -0.5;
    else
      v32 = 0.0;
    *(f32 *)&v28 = v12 * -0.5;
    if ((data->tex3d->klass->vtable._5_get_width.methodPtr)(data->tex3d, data->tex3d->klass->vtable._5_get_width.v28) == 1920 && (data->tex3d->klass->vtable._7_get_height.methodPtr)(data->tex3d, data->tex3d->klass->vtable._7_get_height.method) == 1080)
    {
      v29 = 1.0;
      v33 = -1.0;
    }
    else
    {
      v33 = v29 - v14;
      if (data->uid == 3)
      {
        v32 = v32 + 0.09583333;
        v30 = v31 + -0.044444446;
      }
      else
      {
        v30 = v31;
      }
    }
    v34 = v12 + v22;
    v35 = v32 + data->drawPosOffx;
    v36 = v30 + data->drawPosOffy;
    (data->mesh->edit->klass->vtable._4_unknown.methodPtr)(data->mesh->edit, data->mesh->edit->klass->vtable._4_unknown.method);
    mesh = data->mesh;
    *(u64 *)&v123.z = 0;
    *(u64 *)&v123.x = &data->col;
    v39 = get_Item(v123, 0);
    *(u64 *)&v124.x = &data->col;
    *(u64 *)&v124.z = 1;
    v41 = get_Item(v124, 0);
    *(u64 *)&v125.x = &data->col;
    *(u64 *)&v125.z = 2;
    v43 = get_Item(v125, 0);
    *(u64 *)&v126.x = &data->col;
    *(u64 *)&v126.z = 3;
    v45 = get_Item(v126, 0);
    v46 = v39 | (v41 << 8);
    v47 = (v43 << 16) | (v45 << 24) | v46;
    v155.y = (f32)BYTE1(v46) * 0.0078125;
    v155.z = (f32)BYTE2(v47) * 0.0078125;
    v155.w = (f32)HIBYTE(v47) * 0.0078125;
    v155.x = (f32)(u8)v39 * 0.0078125;
    SetSquareCol_36172464(mesh, 0, v155, 0);
    SetSquarePos(data->mesh, 0, v22 + v35, v29 + v36, v34 + v35, v33 + v36, 0);
    SetSquareUV_36173248(data->mesh, 0, 0);
    SetRange_36166880(data->mesh, 0xFFFu, 0);
    SetSquareIndex_36173424(data->mesh, 0);
    SetMarker(data->mesh, 0);
    (data->mesh->klass->vtable._7_SetTexture.methodPtr)(data->mesh, data->tex3d, data->mesh->klass->vtable._7_SetTexture.method);
    (data->mesh->edit->klass->vtable._5_unknown.methodPtr)(data->mesh->edit, data->mesh->edit->klass->vtable._5_unknown.method);
    sdfDrawTagLink(v9, data->mesh->packet);
    sdfDrawTagLinkOt(Ot[gPictureOtEx_local], v9);
  }
  else if (data->uid != 3)
  {
    v49 = uiObj->pictureObj[data->GameObjectIdx];
    Component_object = GetComponent_object_(v49);
    if (!updateFlag && !get_activeSelf(v49, 0))
    {
      SetActive(v49, 1, 0);
      set_sprite(Component_object, data->sprite, 0);
      (Component_object->klass->vtable[33].methodPtr)(Component_object, 0, Component_object->klass->vtable[33].method);
    }
    *(u64 *)&v127.x = &data->col;
    *(u64 *)&v127.z = 3;
    v52 = get_Item(v127, 0);
    (Component_object->klass->vtable[23].methodPtr)(Component_object, Component_object->klass->vtable[23].1.0, 1.0, 1.0, (f32)v52 * 0.0078125);
    v53 = GetComponent_object_(v49);
    v54 = (data->tex2d->klass->vtable._5_get_width.methodPtr)(data->tex2d, data->tex2d->klass->vtable._5_get_width.method);
    v55 = (data->tex2d->klass->vtable._7_get_height.methodPtr)(data->tex2d, data->tex2d->klass->vtable._7_get_height.method);
    v150.x = (f32)v54;
    v150.y = (f32)v55;
    set_sizeDelta(v53, v150, 0);
    cutInType = data->cutInType;
    v153.x = 1.6;
    v57 = 2.0;
    if (cutInType == 1)
      v57 = 1.7;
    v153.z = 0.0;
    if (cutInType != 2)
      v153.x = v57;
    v153.y = v153.x;
    set_localScale(v53, v153, 0);
    *(u64 *)&v128.z = 0;
    *(u64 *)&v128.x = &data->xy;
    v117 = 0;
    v118 = 0;
    v60 = get_Item(v128, 0);
    *(u64 *)&v129.z = 0;
    *(u64 *)&v129.x = &data->ofs_xy;
    v62 = v60 + 16 * get_Item(v129, 0);
    *(u64 *)&v130.x = &v117;
    *(u64 *)&v130.z = 0;
    set_Item(v130, v62, 0);
    *(u64 *)&v131.x = &data->xy;
    *(u64 *)&v131.z = 1;
    v65 = get_Item(v131, 0);
    *(u64 *)&v132.x = &data->ofs_xy;
    *(u64 *)&v132.z = 1;
    v67 = v65 + 8 * get_Item(v132, 0);
    *(u64 *)&v133.x = &v117;
    *(u64 *)&v133.z = 1;
    set_Item(v133, v67, 0);
    *(u64 *)&v134.x = &data->xy;
    *(u64 *)&v134.z = 2;
    v70 = get_Item(v134, 0);
    *(u64 *)&v135.x = &data->ofs_xy;
    *(u64 *)&v135.z = 2;
    v72 = v70 + 16 * get_Item(v135, 0);
    *(u64 *)&v136.x = &v117;
    *(u64 *)&v136.z = 2;
    set_Item(v136, v72, 0);
    *(u64 *)&v137.x = &data->xy;
    *(u64 *)&v137.z = 3;
    v75 = get_Item(v137, 0);
    *(u64 *)&v138.x = &data->ofs_xy;
    *(u64 *)&v138.z = 3;
    v77 = v75 + 8 * get_Item(v138, 0);
    *(u64 *)&v139.x = &v117;
    *(u64 *)&v139.z = 3;
    set_Item(v139, v77, 0);
    if ((data->flag & 0x10) != 0)
    {
      *(u64 *)&v140.x = &v117;
      *(u64 *)&v140.z = 0;
      v80 = get_Item(v140, 0);
      v81 = (data->tex2d->klass->vtable._5_get_width.methodPtr)(data->tex2d, data->tex2d->klass->vtable._5_get_width.method);
      if (v81 >= 0)
        v83 = v81;
      else
        v83 = v81 + 1;
      *(u64 *)&v146.x = &v117;
      *(u64 *)&v146.z = 0;
      set_Item(v146, v80 - 16 * (v83 >> 1), 0);
      *(u64 *)&v141.x = &v117;
      *(u64 *)&v141.z = 1;
      v85 = get_Item(v141, 0);
      v86 = (data->tex2d->klass->vtable._7_get_height.methodPtr)(data->tex2d, data->tex2d->klass->vtable._7_get_height.method);
      if (v86 >= 0)
        v88 = v86;
      else
        v88 = v86 + 1;
      *(u64 *)&v147.x = &v117;
      *(u64 *)&v147.z = 1;
      set_Item(v147, v85 - 8 * (v88 >> 1), 0);
      *(u64 *)&v142.x = &v117;
      *(u64 *)&v142.z = 2;
      v90 = get_Item(v142, 0);
      v91 = (data->tex2d->klass->vtable._5_get_width.methodPtr)(data->tex2d, data->tex2d->klass->vtable._5_get_width.method);
      if (v91 >= 0)
        v93 = v91;
      else
        v93 = v91 + 1;
      *(u64 *)&v148.x = &v117;
      *(u64 *)&v148.z = 2;
      set_Item(v148, v90 - 16 * (v93 >> 1), 0);
      *(u64 *)&v143.x = &v117;
      *(u64 *)&v143.z = 3;
      v95 = get_Item(v143, 0);
      v96 = (data->tex2d->klass->vtable._7_get_height.methodPtr)(data->tex2d, data->tex2d->klass->vtable._7_get_height.method);
      if (v96 >= 0)
        v98 = v96;
      else
        v98 = v96 + 1;
      *(u64 *)&v149.x = &v117;
      *(u64 *)&v149.z = 3;
      set_Item(v149, v95 - 8 * (v98 >> 1), 0);
    }
    *(u64 *)&v144.x = &v117;
    *(u64 *)&v144.z = 0;
    v99 = get_Item(v144, 0);
    *(u64 *)&v145.x = &v117;
    *(u64 *)&v145.z = 1;
    v101 = get_Item(v145, 0);
    v102 = (data->tex2d->klass->vtable._5_get_width.methodPtr)(data->tex2d, data->tex2d->klass->vtable._5_get_width.method);
    if (v102 >= 0)
      v103 = v102;
    else
      v103 = v102 + 1;
    v104 = (data->tex2d->klass->vtable._7_get_height.methodPtr)(data->tex2d, data->tex2d->klass->vtable._7_get_height.method);
    if (v104 >= 0)
      v105 = v104;
    else
      v105 = v104 + 1;
    v106 = data->uid - 80;
    if (v106 <= 0x18 && ((1 << v106) & 0x1555555) != 0)
    {
      get_width(0);
      get_height(0);
      v151.x = 0.0;
      v151.y = 0.0;
      set_anchoredPosition(v53, v151, 0);
      DissolveCalc(data, Component_object);
    }
    else if ((data->tex2d->klass->vtable._5_get_width.methodPtr)(data->tex2d, data->tex2d->klass->vtable._5_get_width.method) == 1920 && (data->tex2d->klass->vtable._7_get_height.methodPtr)(data->tex2d, data->tex2d->klass->vtable._7_get_height.method) == 1080)
    {
      width = get_width(0);
      if (width >= 0)
        v109 = width;
      else
        v109 = width + 1;
      v110 = v109 >> 1;
      height = get_height(0);
      if (height >= 0)
        v112 = height;
      else
        v112 = height + 1;
      v154.z = 0.0;
      v154.y = (f32)(v112 >> 1);
      v154.x = (f32)v110;
      set_position(v53, v154, 0);
    }
    else
    {
      if ((data->tex2d->klass->vtable._5_get_width.methodPtr)(data->tex2d, data->tex2d->klass->vtable._5_get_width.method) == 337 && (data->tex2d->klass->vtable._7_get_height.methodPtr)(data->tex2d, data->tex2d->klass->vtable._7_get_height.method) == 288)
      {
        v114 = -240.0;
      }
      else
      {
        v114 = -384.0;
      }
      v115 = v114;
      if (data->cutInType == 3)
        v115 = v114 + 90.0;
      v116 = (f32)((f32)(v105 >> 1) - (f32)((f32)(v101 >> 3) + -112.0)) + v115;
      v113 = (f32)((f32)(v99 >> 4) + -256.0) + (f32)(v103 >> 1);
      v152.x = v113 + v113;
      v152.y = v116 + v116;
      set_anchoredPosition(v53, v152, 0);
    }
  }
}

// 0x1a2f240
static void DissolveCalc(evtPictureProcessData_t *data, void *img) {
  MethodInfo *v5;
  void *dissolveMat;
  _BOOL8 v7;
  void *Instance;
  void *v9;
  _BOOL8 HasProperty_60811712;
  s32 draw1st;
  void *v12;
  f32 *p_disoolvePar;
  s32 v14;
  void *v15;
  s32 startFrame;
  void *v17;
  f32 disoolvePar;
  f32 v19;
  void *v20;

  v5 = (img->klass->vtable._32_get_material.methodPtr)(img, img->klass->vtable._32_get_material.method);
  dissolveMat = get_Instance(v5)->dissolveMat;
  v7 = op_Inequality(v5, dissolveMat, 0);
  if (v7)
  {
    Instance = get_Instance(v7);
    (img->klass->vtable._33_set_material.methodPtr)(img, Instance->dissolveMat, img->klass->vtable._33_set_material.method);
  }
  v9 = (img->klass->vtable._32_get_material.methodPtr)(img, img->klass->vtable._32_get_material.method);
  HasProperty_60811712 = HasProperty_60811712(v9, "_AlphaClipThreshold", 0);
  if (HasProperty_60811712)
  {
    draw1st = data->draw1st;
    v12 = get_Instance(HasProperty_60811712);
    if (draw1st >= v12->startFrame)
    {
      v14 = data->draw1st;
      v15 = get_Instance(v12);
      startFrame = v15->startFrame;
      v17 = get_Instance(v15);
      if (v14 - startFrame >= v17->playFrame || (disoolvePar = data->disoolvePar, v19 = disoolvePar + (f32)(-1.0 / (f32)get_Instance(v17)->playFrame), v19 < 0.0))
      {
        v19 = 0.0;
      }
      data->disoolvePar = v19;
      p_disoolvePar = &data->disoolvePar;
    }
    else
    {
      data->disoolvePar = 1.0;
      p_disoolvePar = &data->disoolvePar;
    }
    v20 = (img->klass->vtable._32_get_material.methodPtr)(img, img->klass->vtable._32_get_material.method);
    SetFloat(v20, "_AlphaClipThreshold", *p_disoolvePar, 0);
  }
}

// 0x1a2f220
static bool IsEventTitle(evtPictureProcessData_t *data) {
  u32 uid;

  uid = data->uid;
  return (uid & 1) == 0 && uid - 80 < 0x19;
}

// 0x1a2f4f0
void evtPictureSetDrawPosOffSet(dds3ProcessID_t *id, f32 ox, f32 oy) {
  f32 *ProcessData;
  dds3ProcessID_t *ida;

  ida = id;
  ProcessData = dds3GetProcessData(ida);
  if (!ProcessData)
  ProcessData[44] = ox;
  ProcessData[45] = oy;
}

// 0x1a2f5e0
static dds3ProcessFunc_t Process1(dds3ProcessID_t *id) {
  Il2CppObject *ProcessData;
  s32 klass_high;
  void *klass;
  bool v9;
  u32 v13;
  dds3ProcessFunc_t v14;
  Il2CppObject *monitor;
  Il2CppObject *v16;
  s32 v17;
  s32 v18;
  s32 v19;
  bool v20;
  s32 v21;
  dds3ProcessID_t *ida;

  ida = id;
  ProcessData = dds3GetProcessData(ida);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if (((s64)ProcessData[1].klass & 1) == 0)
    return 0;
  klass_high = HIDWORD(ProcessData[1].klass);
  if (LODWORD(ProcessData[10].monitor))
  {
    klass = ProcessData[3].klass;
    goto LABEL_14;
  }
  klass = ProcessData[1].monitor;
LABEL_14:
  v9 = op_Inequality(klass, 0, 0);
  if (msg_logFlag == 1)
  {
    HIDWORD(ProcessData[10].monitor) = 0;
    msg_logFlag = 0;
  }
  if (v9)
  {
    if (((s64)ProcessData[1].klass & 8) != 0)
    {
      v14 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
      _ctor(v14, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      return v14;
    }
    Animation(ProcessData);
    Draw();
  }
  if ((klass_high & 0xFFFFFF) == 0)
    return 0;
  if ((klass_high & 0xFFFFFF) == 0x64)
  {
    v13 = ProcessData[1].klass;
    if ((v13 & 4) != 0 && WORD1(ProcessData[10].klass) == 30)
      goto LABEL_23;
    return 0;
  }
  monitor = ProcessData[8].monitor;
  if (monitor)
    v16 = monitor + 2;
  else
    v16 = ProcessData + 9;
  v17 = v16->klass;
  if (SLODWORD(v16->klass) < SLODWORD(ProcessData[8].klass))
    LODWORD(ProcessData[1].klass) |= 8u;
  if ((u16)klass_high == 1)
    v18 = 5;
  else
    v18 = 0;
  if (SkipChk(ProcessData))
  {
    v19 = HIDWORD(ProcessData[8].klass) + v18;
    v13 = ProcessData[1].klass;
    if (HIDWORD(ProcessData[9].klass) == 3)
      v19 += (v13 >> 2) & 1;
    v20 = v19 < HIDWORD(ProcessData[8].klass) + v18;
    if ((v13 & 2) == 0)
    {
LABEL_39:
      if (!v20)
      {
LABEL_23:
        LODWORD(ProcessData[1].klass) = v13 | 8;
        return 0;
      }
      return 0;
    }
  }
  else
  {
    v13 = ProcessData[1].klass;
    v20 = v17 < HIDWORD(ProcessData[8].klass) + v18;
    if ((v13 & 2) == 0)
      goto LABEL_39;
  }
  if (v20)
  {
    if ((v13 & 4) == 0)
      return 0;
  }
  else
  {
    v21 = v13 | 8;
    LODWORD(ProcessData[1].klass) = v21;
    if ((v21 & 4) == 0)
      return 0;
  }
  ++LODWORD(ProcessData[9].klass);
  return 0;
}

// 0x1a2f910
static void Shutdown(dds3ProcessID_t *id) {
  Il2CppObject *ProcessData;
  u32 v5;
  void *klass;
  u32 v8;
  void *p_monitor;
  void *monitor;
  void *v11;
  Il2CppObject *v12;
  void *v13;
  void *gameObject;
  s32 v16;
  s32 v18;
  dds3ProcessID_t *ida;

  ida = id;
  ProcessData = dds3GetProcessData(ida);
  if (!ProcessData)
  v5 = HIDWORD(ProcessData[9].klass) - 80;
  if (v5 <= 0x18 && ((1 << v5) & 0x1555555) != 0)
  {
    movieStop(0);
  }
  if (LODWORD(ProcessData[10].monitor))
  {
    klass = ProcessData[3].klass;
    goto LABEL_17;
  }
  klass = ProcessData[1].monitor;
LABEL_17:
  if (op_Inequality(klass, 0, 0))
  {
    ProcessData[1].monitor = 0;
    ProcessData[3].klass = 0;
  }
  if (!LODWORD(ProcessData[10].monitor))
  {
    v12 = ProcessData + 2;
    v13 = ProcessData[2].klass;
    if (v8)
    {
      if (!op_Inequality(v13, 0, 0))
        goto LABEL_31;
    }
    else
    {
      if (!op_Inequality(v13, 0, 0))
      {
LABEL_31:
        SetActive(uiObj->pictureObj[SLODWORD(ProcessData[2].monitor)], 0, 0);
        if (HIDWORD(ProcessData[9].klass) == 3)
          goto LABEL_37;
        goto LABEL_23;
      }
    }
    v12->klass = 0;
    goto LABEL_31;
  }
  p_monitor = &ProcessData[3].monitor;
  monitor = ProcessData[3].monitor;
  if (v8)
  {
    if (!op_Inequality(monitor, 0, 0))
      goto LABEL_22;
    goto LABEL_34;
  }
  if (op_Inequality(monitor, 0, 0))
  {
LABEL_34:
    gameObject = get_gameObject(p_monitor, 0);
    DestroyImmediate_61008224(gameObject, 0);
    p_monitor = 0;
    if (HIDWORD(ProcessData[9].klass) == 3)
      goto LABEL_37;
LABEL_23:
    v11 = ProcessData[9].monitor;
    if (!v11)
      return;
    goto LABEL_24;
  }
LABEL_22:
  if (HIDWORD(ProcessData[9].klass) != 3)
    goto LABEL_23;
LABEL_37:
  if (!*((u8 *)*((MethodInfo *)cmpItem + 2).virtualMethodPointer + 200))
  {
    SetInteger(uiObj->gouto_face_anim, "anim", 2, 0);
    goto LABEL_47;
  }
  v16 = evtPictureUseGoutoAnim() - 1;
  if (zyarEnd)
    v18 = 20;
  else
    v18 = v16;
  SetInteger(uiObj->gouto_face_anim, "anim", v18, 0);
  zyarEnd = 0;
LABEL_47:
  cmpResetUseNekozyar();
  v11 = ProcessData[9].monitor;
  if (!v11)
    return;
LABEL_24:
  (*(v11 + 3))(*((u64 *)v11 + 8), HIDWORD(ProcessData[9].klass), *((u64 *)v11 + 5));
  return;
}

// 0x1a2fe30
dds3ProcessID_t *StartProcess(DDS3_PRIORITY priority, char *texpath) {
  Il2CppObject *inited;
  dds3ProcessFunc_t v5;
  shutdownfuncDelegate v6;

  inited = InitProcessData();
  v5 = Allocate(dds3ProcessFunc_t);
  _ctor(v5, 0, Method_Project_evtPicture_Process1__, 0);
  v6 = Allocate(shutdownfuncDelegate);
  _ctor(v6, 0, Method_Project_evtPicture_Shutdown__, 0);
  return dds3StartProcess("Picture", priority, 1, 1, v5, v6, inited);
}

// 0x1a2ff60
dds3ProcessID_t *evtPictureStartProcess2(DDS3_PRIORITY priority, u8 *texdata) {
  Il2CppObject *inited;
  dds3ProcessFunc_t v5;
  shutdownfuncDelegate v6;

  inited = InitProcessData();
  v5 = Allocate(dds3ProcessFunc_t);
  _ctor(v5, 0, Method_Project_evtPicture_Process1__, 0);
  v6 = Allocate(shutdownfuncDelegate);
  _ctor(v6, 0, Method_Project_evtPicture_Shutdown__, 0);
  return dds3StartProcess("Picture", priority, 1, 1, v5, v6, inited);
}

// 0x1a30090
static void LoadTexCallback(fileHandle_t *fh, void *pParam) {
  s64 naturalAligment;
  void *topPtr;
  s64 v9;
  void *v10;
  void **v12;
  void *v13;
  void **p_monitor;
  void *transform;
  void *v17;
  void *v18;
  s32 v19;
  f32 v20;
  Project_fileHandle_t_Parm_c *_61051600;
  void *v22;
  s32 Item;
  s32 v25;
  s32 v28;
  s32 v29;
  s32 v33;
  s32 v35;
  sdfIVector4_t v37;
  sdfIVector4_t v38;
  sdfIVector4_t v39;
  sdfIVector4_t v40;
  sdfIVector4_t v41;
  sdfIVector4_t v42;
  sdfIVector4_t v43;
  sdfIVector4_t v44;
  UnityEngine_Rect_o v45;

  if (LODWORD(pParam[10].monitor))
  {
    topPtr = fh->topPtr;
    if (topPtr)
    {
      if (topPtr->klass->_2.naturalAligment < (u32)v9)
        goto LABEL_18;
      if (topPtr->klass->_2.typeHierarchy[v9 - 1] != UnityEngine_Texture)
        goto LABEL_18;
      pParam[3].klass = (Project_fileHandle_t_Parm_c *)topPtr;
      v10 = pParam + 3;
      if (topPtr->klass->_2.naturalAligment < (u32)v9 || topPtr->klass->_2.typeHierarchy[v9 - 1] != UnityEngine_Texture)
      {
        goto LABEL_18;
      }
      goto LABEL_21;
    }
    pParam[3].klass = 0;
    v10 = pParam + 3;
LABEL_21:
    v13 = Make("standard", 0);
    pParam[3].monitor = v13;
    p_monitor = &pParam[3].monitor;
    transform = get_transform(*p_monitor, 0);
    v17 = get_transform(hook, 0);
    SetParent_61042560(transform, v17, 0, 0);
    SetAutoHide(*p_monitor, 1, 0);
    InitSquare(*p_monitor, 1, 0);
    *((u32 *)*p_monitor + 29) = 0;
    fileHandleFree(fh);
    return;
  }
  topPtr = fh->topPtr;
  if (topPtr)
  {
    if (topPtr->klass != UnityEngine_Texture2D || (pParam[1].monitor = topPtr, v12 = &pParam[1].monitor, topPtr->klass != UnityEngine_Texture2D))
    {
LABEL_18:
    }
    goto LABEL_28;
  }
  pParam[1].monitor = 0;
  v12 = &pParam[1].monitor;
LABEL_28:
  v18 = *v12;
  v19 = (*(*(u64 *)*v12 + 392))(*v12, *(u64 *)(*(u64 *)*v12 + 400));
  v20 = (*(*(u64 *)*v12 + 424))(*v12, *(u64 *)(*(u64 *)*v12 + 432));
  v45.m_XMin = 0.0;
  v45.m_YMin = 0.0;
  v45.m_Width = (f32)v19;
  v45.m_Height = v20;
  _61051600 = Create_61051600(v18, v45, zeroVector, 0);
  pParam[2].klass = _61051600;
  v22 = pParam + 2;
  fileHandleFree(fh);
  *(u64 *)&v37.z = 0;
  *(u64 *)&v37.x = v22 + 2;
  Item = get_Item(v37, 0);
  v25 = Item
      + 16
      * (*(*(u64 *)v22[-1].monitor + 392))(v22[-1].monitor, *(u64 *)(*(u64 *)v22[-1].monitor + 400));
  *(u64 *)&v38.x = v22 + 2;
  *(u64 *)&v38.z = 2;
  set_Item(v38, v25, 0);
  *(u64 *)&v39.x = v22 + 2;
  *(u64 *)&v39.z = 1;
  v28 = get_Item(v39, 0);
  v29 = v28
      + 8
      * (*(*(u64 *)v22[-1].monitor + 424))(v22[-1].monitor, *(u64 *)(*(u64 *)v22[-1].monitor + 432));
  *(u64 *)&v40.x = v22 + 2;
  *(u64 *)&v40.z = 3;
  set_Item(v40, v29, 0);
  *(u64 *)&v41.z = 0;
  *(u64 *)&v41.x = v22 + 3;
  set_Item(v41, 0, 0);
  *(u64 *)&v42.x = v22 + 3;
  *(u64 *)&v42.z = 1;
  set_Item(v42, 0, 0);
  v33 = 16
      * (*(*(u64 *)v22[-1].monitor + 392))(v22[-1].monitor, *(u64 *)(*(u64 *)v22[-1].monitor + 400));
  *(u64 *)&v43.x = v22 + 3;
  *(u64 *)&v43.z = 2;
  set_Item(v43, v33, 0);
  v35 = 16
      * (*(*(u64 *)v22[-1].monitor + 424))(v22[-1].monitor, *(u64 *)(*(u64 *)v22[-1].monitor + 432));
  *(u64 *)&v44.x = v22 + 3;
  *(u64 *)&v44.z = 3;
  set_Item(v44, v35, 0);
}

// 0x1a304c0
fileHandle_t *evtPictureLoadStartTexFile(char *pFileName, char *pBundle, evtPictureProcessData_t *data) {
  fileEndCallback_t v7;

  data->tex2d = 0;
  data->tex3d = 0;
  v7 = Allocate(fileEndCallback_t);
  _ctor(v7, 0, Method_Project_evtPicture_LoadTexCallback__, 0);
  return fileLoadEx(pBundle, pFileName, v7, data);
}

// 0x1a305b0
bool evtPictureLoadCheckProcess(dds3ProcessID_t *id) {
  Il2CppObject *ProcessData;
  void *monitor;
  dds3ProcessID_t *ida;

  ida = id;
  ProcessData = dds3GetProcessData(ida);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if (!LODWORD(ProcessData[10].monitor))
  {
    monitor = ProcessData[1].monitor;
    return op_Inequality(monitor, 0, 0);
  }
  monitor = ProcessData[3].klass;
  return op_Inequality(monitor, 0, 0);
}

// 0x1a306e0
s32 evtPictureSetDrawPos(dds3ProcessID_t *id, s32 x, s32 y) {
  Il2CppObject *ProcessData;
  Il2CppObject *v10;
  s32 v12;
  void **p_monitor;
  void *monitor;
  s32 v16;
  s32 v18;
  dds3ProcessID_t *ida;
  sdfIVector4_t v22;
  sdfIVector4_t v23;
  sdfIVector4_t v24;
  sdfIVector4_t v25;
  sdfIVector4_t v26;

  ida = id;
  ProcessData = dds3GetProcessData(ida);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v10 = ProcessData + 4;
  *(u64 *)&v22.z = 0;
  *(u64 *)&v22.x = ProcessData + 4;
  set_Item(v22, 16 * x, 0);
  *(u64 *)&v23.x = ProcessData + 4;
  *(u64 *)&v23.z = 1;
  set_Item(v23, 8 * y, 0);
  if (LODWORD(ProcessData[10].monitor))
  {
    v12 = (*(ProcessData[3].klass->_1.image + 49))(ProcessData[3].klass, *((u64 *)ProcessData[3].klass->_1.image + 50))
        + x;
    *(u64 *)&v24.x = ProcessData + 4;
    *(u64 *)&v24.z = 2;
    set_Item(v24, 16 * v12, 0);
    p_monitor = &ProcessData[1].monitor;
  }
  else
  {
    monitor = ProcessData[1].monitor;
    p_monitor = &ProcessData[1].monitor;
    v16 = (*(*(u64 *)monitor + 392))(monitor, *(u64 *)(*(u64 *)monitor + 400))
        + x;
    *(u64 *)&v25.x = v10;
    *(u64 *)&v25.z = 2;
    set_Item(v25, 16 * v16, 0);
  }
  v18 = (*(*(u64 *)*p_monitor + 424))(*p_monitor, *(u64 *)(*(u64 *)*p_monitor + 432))
      + y;
  *(u64 *)&v26.x = v10;
  *(u64 *)&v26.z = 3;
  set_Item(v26, 8 * v18, 0);
  return 1;
}

// 0x1a30890
s32 evtPictureSetDrawCol(dds3ProcessID_t *id, s32 r, s32 g, s32 b, s32 a) {
  Il2CppObject *ProcessData;
  s64 v14;
  dds3ProcessID_t *ida;
  sdfIVector4_t v20;
  sdfIVector4_t v21;
  sdfIVector4_t v22;
  sdfIVector4_t v23;

  ida = id;
  ProcessData = dds3GetProcessData(ida);
  if (!ProcessData)
  *(u64 *)&v20.z = 0;
  *(u64 *)&v20.x = ProcessData + 6;
  v14 = *(u64 *)&v20.x;
  set_Item(v20, r, 0);
  *(u64 *)&v21.x = v14;
  *(u64 *)&v21.z = 1;
  set_Item(v21, g, 0);
  *(u64 *)&v22.x = v14;
  *(u64 *)&v22.z = 2;
  set_Item(v22, b, 0);
  *(u64 *)&v23.x = v14;
  *(u64 *)&v23.z = 3;
  set_Item(v23, a, 0);
  return 1;
}

// 0x1a309e0
s32 evtPictureSetEndProcess(dds3ProcessID_t *id) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *ida;

  ida = id;
  ProcessData = dds3GetProcessData(ida);
  if (!ProcessData)
  LODWORD(ProcessData[1].klass) |= 8u;
  return 1;
}

// 0x1a30ac0
dds3ProcessID_t *evtPictureStartProcess3(DDS3_PRIORITY priority, char *texpath, char *bname) {
  evtPictureProcessData_t *inited;
  dds3ProcessFunc_t v9;
  shutdownfuncDelegate v10;

  inited = InitProcessData();
  evtPictureLoadStartTexFile(texpath, bname, inited);
  v9 = Allocate(dds3ProcessFunc_t);
  _ctor(v9, 0, Method_Project_evtPicture_Process1__, 0);
  v10 = Allocate(shutdownfuncDelegate);
  _ctor(v10, 0, Method_Project_evtPicture_Shutdown__, 0);
  return dds3StartProcess("Picture", priority, 1, 1, v9, v10, inited);
}

// 0x1a30c10
dds3ProcessID_t *evtPictureStartProcess4(s32 x, s32 y, DDS3_PRIORITY priority, s32 start, s32 end, s32 *p_now, EVT_PICTURE_TYPE type, u32 uid, callbackDelegate callback, char *texpath, char *bname, s32 ui_mode, CutInType cutInType) {
  evtPictureProcessData_t *inited;
  dds3ProcessFunc_t v24;
  shutdownfuncDelegate v25;
  sdfIVector4_t v29;
  sdfIVector4_t v30;

  inited = InitProcessData();
  *(u64 *)&v29.z = 0;
  inited->flag |= 0x11u;
  *(u64 *)&v29.x = &inited->xy;
  set_Item(v29, x, 0);
  *(u64 *)&v30.x = &inited->xy;
  *(u64 *)&v30.z = 1;
  set_Item(v30, y, 0);
  inited->start = start;
  inited->end = end;
  inited->p_now = p_now;
  inited->callback = callback;
  inited->type = type;
  inited->uid = uid;
  inited->ui_mode = ui_mode;
  inited->cutInType = cutInType;
  evtPictureLoadStartTexFile(texpath, bname, inited);
  v24 = Allocate(dds3ProcessFunc_t);
  _ctor(v24, 0, Method_Project_evtPicture_Process1__, 0);
  v25 = Allocate(shutdownfuncDelegate);
  _ctor(v25, 0, Method_Project_evtPicture_Shutdown__, 0);
  return dds3StartProcess("Picture", priority, 0, 0, v24, v25, inited);
}

// 0x1a2f190
void evtPictureApeGouto(void) {
  s32 v1;

  v1 = evtPictureUseGoutoAnim();
  if (v1 == 19)
    zyarEnd = 1;
  SetInteger(uiObj->gouto_face_anim, "anim", v1, 0);
}

// 0x1a2fd90
void evtPictureExtGouto(void) {
  s32 v1;
  s32 v3;

  v1 = evtPictureUseGoutoAnim() - 1;
  if (zyarEnd)
    v3 = 20;
  else
    v3 = v1;
  SetInteger(uiObj->gouto_face_anim, "anim", v3, 0);
  zyarEnd = 0;
}

// 0x1a30e20
s32 evtPictureUseGoutoAnim(void) {
  if (!evtBitCheck(2084))
    return 3;
  if (!evtBitCheck(2085))
    return 5;
  if (!evtBitCheck(2086))
    return 7;
  if (!evtBitCheck(2087))
    return 9;
  if (!evtBitCheck(2088))
    return 11;
  if (!evtBitCheck(2089))
    return 13;
  if (!evtBitCheck(2090))
    return 15;
  if (!evtBitCheck(2091))
    return 17;
  if (evtBitCheck(2092))
    return 20;
  return 19;
}
