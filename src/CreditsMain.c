#include "types.h"
#include "creditsmain.h"
#include "dds3_pad.h"
#include "dds3kerneldraw.h"
#include "dds3vrf.h"
#include "sndat3.h"

typedef enum {
    CreditsMain_DisplayObj_None = -1,
    CreditsMain_DisplayObj_Caption1 = 0,
    CreditsMain_DisplayObj_Caption2 = 1,
    CreditsMain_DisplayObj_Name1 = 2,
    CreditsMain_DisplayObj_Name2 = 3,
} CreditsMain_DisplayObj;

typedef struct Credits_t Credits_t;

static f32 scroll_speed;
static s32 credits_item_count;
static f32 init_positoin_y;
static f32 now_count;
bool is_end;
static bool is_start_fade;
static s32 staffobj_cnt1;
static s32 staffobj_cnt2;
static s32 centerobj_cnt;
static s32 jobobj_cnt1;
static s32 jobobj_cnt2;
static s32 logoobj_cnt;
static s32 logocenter_cnt;
static s32 staffobj_max;
static s32 centerobj_max;
static s32 jobobj_max;
static s32 logoobj_max;
static char *loading_str;
static void *staffNameTM1;
static void *staffNameTM2;
static void *centerCaptionTM;
static void *jobCaptionTM1;
static void *jobCaptionTM2;
static void *copywriter;
static f32 cap2CenterPos;
static f32 cap2RightPos;
Credits_t *CreditsData;
static void *creditsUIInstance;
static s32 orgScreenH;
static f32 logoEndPosOffset;
static f32 textEndPosOffset;

static void CreditsInit(void);
static void CreditsDestroy(void);
static void FirstCalcProcess(void);
static void CalcProcess(void);
static void DrawProcess(void);
static void ParentRegister(void);
static void DrawText(void);
static bool CheckBlank(s32 itemCount);
static void TextScroll(void *text);
static void AddText(void *text, CreditsMain_DisplayObj obj);

// 0x223b0a0
static void CreditsInit(void) {
  struct CreditsMain *v5;
  void *Instance;
  void *v9;
  void *v11;
  void *v13;
  void *v15;
  void *v17;
  void *v19;
  void *v21;
  void *Asset;
  s64 naturalAligment;
  void *v28;
  Credits_t *v29;
  s64 v31;
  s64 v32;
  Il2CppClass *v33;
  Credits_t *CreditsData_local;
  void *klass;
  Il2CppObject *Item;
  s64 v38;
  s64 i;
  UnityEngine_Object_c *v40;
  UnityEngine_Object_c **v41;
  creditsUI_CreditsLogo_t *creditsImages;
  void *v45;
  void *Ctrl_k__BackingField;
  void *v50;
  s64 v52;
  s64 v53;
  Credits_t *v56;
  s64 v58;

  *(u64 *)&scroll_speed = 0;
  *(u64 *)&staffobj_cnt1 = 0;
  *(u64 *)&jobobj_cnt2 = 0;
  *(u64 *)&centerobj_cnt = 0;
  logocenter_cnt = 0;
  *(u64 *)&init_positoin_y = 3293544448LL;
  copywriter = 0;
  finalImage = 0;
  credits_ui_obj = 0;
  loading_str = 0;
  v5 = ((char *)v5 + 64);
  LOWORD(v5[-1].logoImage) = 0;
  Instance = get_Instance();
  creditsUIInstance = Instance;
  v9 = NewSpecific(TMPro_TextMeshProUGUI, staffobj_max);
  staffNameTM1 = v9;
  v11 = NewSpecific(TMPro_TextMeshProUGUI, staffobj_max);
  staffNameTM2 = v11;
  v13 = NewSpecific(TMPro_TextMeshProUGUI, centerobj_max);
  centerCaptionTM = v13;
  v15 = NewSpecific(TMPro_TextMeshProUGUI, jobobj_max);
  jobCaptionTM1 = v15;
  v17 = NewSpecific(TMPro_TextMeshProUGUI, jobobj_max);
  jobCaptionTM2 = v17;
  v19 = NewSpecific(UnityEngine_UI_Image, logoobj_max);
  logoImage = v19;
  v21 = NewSpecific(UnityEngine_UI_Image, logoobj_max);
  logoImageCenter = v21;
  Load(Dependent, "credits_data", "credits_data");
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  Asset = LoadAsset(_Ctrl_k__BackingField, "credits_data", "CreditsDataTable", 0);
  {
    if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_creditsDataTable)
      v28 = Asset;
    else
      v28 = 0;
  }
  else
  {
    v28 = 0;
  }
  v29 = NewSpecific(Credits_t, (u32)v28[1].klass->_1.namespaze);
  CreditsData = v29;
  if (SLODWORD(v28[1].klass->_1.namespaze) >= 1)
  {
    v31 = 0;
    v32 = 32;
    do
    {
      CreditsData_local = CreditsData;
      klass = v28[1].klass;
      if (v31 < klass->_size)
      {
        Item = _get_Item(klass, v31);
        v33 = Item;
        goto LABEL_24;
      }
      v33 = 0;
LABEL_24:
      *(Il2CppClass **)((char *)&CreditsData_local->obj.klass + v32) = v33;
      ++v31;
      v32 += 8;
    }
    while (v31 < SLODWORD(v28[1].klass->_1.namespaze));
  }
  v38 = 0;
  for (i = 32; ; i += 16)
  {
    creditsImages = creditsUIInstance->creditsImages;
    if (v38 >= SLODWORD(creditsImages->max_length))
      break;
    v45 = *(void *)((char *)&creditsImages->obj.klass + i);
    if (!op_Equality(v45, 0, 0))
      goto LABEL_36;
    Ctrl_k__BackingField = _Ctrl_k__BackingField;
    v50 = LoadAsset(Ctrl_k__BackingField, "credits_data", *(char **)((char *)&creditsUIInstance->creditsImages->obj.monitor + i), 0);
      v50 = 0;
    v40 = v50[9].klass;
    v41 = ((char *)creditsUIInstance->creditsImages + i);
    *v41 = v40;
LABEL_36:
    ++v38;
  }
  Unload(_Ctrl_k__BackingField, "credits_data", 0);
  v52 = 4;
  while (2)
  {
    v56 = CreditsData;
    if (v52 - 4 < SLODWORD(v56->max_length))
    {
      if (op_Equality(*(char **)(*((u64 *)&v56->obj.klass + v52) + 24), "", 0))
      {
        goto LABEL_68;
      }
      goto LABEL_77;
LABEL_68:
      v58 = *((u64 *)&CreditsData->obj.klass + v52);
      *(u64 *)(v58 + 24) = 0;
LABEL_77:
      if (op_Equality(*(char **)(*((u64 *)&CreditsData->obj.klass + v52) + 32), "", 0))
      {
        v53 = *((u64 *)&CreditsData->obj.klass + v52);
        *(u64 *)(v53 + 32) = 0;
      }
      ++v52;
      continue;
    }
    break;
  }
  FirstCalcProcess(CreditsMain);
}

// 0x223c9c0
static void CreditsDestroy(void) {
  struct CreditsMain *v5;
  s64 i;
  s64 v14;
  s64 v15;

  *(u64 *)&scroll_speed = 0;
  *(u64 *)&staffobj_cnt1 = 0;
  *(u64 *)&jobobj_cnt2 = 0;
  *(u64 *)&centerobj_cnt = 0;
  logocenter_cnt = 0;
  *(u64 *)&init_positoin_y = 3267887104LL;
  copywriter = 0;
  (finalImage->klass->vtable._23_set_color.methodPtr)(finalImage, finalImage->klass->vtable._23_set_color.255.0, 255.0, 255.0, 0.0);
  set_sprite(finalImage, 0, 0);
  finalImage = 0;
  credits_ui_obj = 0;
  loading_str = 0;
  v5 = ((char *)v5 + 64);
  LOWORD(v5[-1].logoImage) = 0;
  staffNameTM1 = 0;
  staffNameTM2 = 0;
  centerCaptionTM = 0;
  jobCaptionTM1 = 0;
  jobCaptionTM2 = 0;
  creditsUIInstance = 0;
  CreditsData = 0;
  for (i = 4; ; ++i)
  {
    if (i - 4 >= logoobj_max)
      break;
    v14 = *((u64 *)&logoImage->obj.klass + i);
    (*(*(u64 *)v14 + 680))(v14, *(u64 *)(*(u64 *)v14 + 688), 255.0, 255.0, 255.0, 0.0);
    set_sprite(*((void *)&logoImage->obj.klass + i), 0, 0);
    v15 = *((u64 *)&logoImageCenter->obj.klass + i);
    (*(*(u64 *)v15 + 680))(v15, *(u64 *)(*(u64 *)v15 + 688), 255.0, 255.0, 255.0, 0.0);
    set_sprite(*((void *)&logoImageCenter->obj.klass + i), 0, 0);
  }
  logoImage = 0;
  logoImageCenter = 0;
}

// 0x223bb40
static void FirstCalcProcess(void) {
  s64 v3;
  s64 i;
  Il2CppObject *v7;
  char *v8;
  void *logoImage_local;
  void *transform;
  void *v13;
  void *gameObject;
  Il2CppObject *Component_object;
  Il2CppObject *v16;
  s64 v17;
  s64 j;
  s64 v20;
  Il2CppObject *v21;
  char *v22;
  void *logoImageCenter_local;
  void *v26;
  void *v27;
  void *v28;
  Il2CppObject *v29;
  Il2CppObject *v30;
  s64 v31;
  s64 k;
  s64 v33;
  Il2CppObject *v36;
  char *v37;
  void *staffNameTM1_local;
  void *v41;
  void *v42;
  void *v43;
  Il2CppObject *v44;
  Il2CppObject *v45;
  s64 v46;
  s64 m;
  s64 v48;
  s64 v50;
  Il2CppObject *v51;
  char *v52;
  void *staffNameTM2_local;
  void *v56;
  void *v57;
  void *v58;
  Il2CppObject *v59;
  Il2CppObject *v60;
  s64 v61;
  s64 n;
  s64 v63;
  Il2CppObject *v66;
  char *v67;
  void *centerCaptionTM_local;
  void *v71;
  void *v72;
  void *v73;
  Il2CppObject *v74;
  Il2CppObject *v75;
  s64 v76;
  s64 ii;
  s64 v78;
  Il2CppObject *v81;
  char *v82;
  void *jobCaptionTM1_local;
  void *v86;
  void *v87;
  void *v88;
  Il2CppObject *v89;
  Il2CppObject *v90;
  s64 v91;
  s64 jj;
  s64 v93;
  s64 v96;
  Il2CppObject *v97;
  char *v98;
  void *jobCaptionTM2_local;
  void *v102;
  void *v103;
  void *v104;
  Il2CppObject *v105;
  Il2CppObject *v106;
  Il2CppMethodPointer virtualMethodPointer;
  char *v117;
  void *v118;
  void *v119;
  void *v120;
  Il2CppObject *v121;
  char *v125;
  void *v126;
  void *v127;
  void *v128;
  Il2CppObject *v129;
  s32 data;

  ParentRegister();
  v3 = 0;
  for (i = 32; ; i += 8)
  {
    if (v3 >= logoobj_max)
      break;
    if (logoobj_cnt < (s32)logoobj_max)
      goto LABEL_12;
    goto LABEL_9000;
    if (logoobj_cnt < logoobj_max)
    {
LABEL_12:
      goto LABEL_13;
    }
LABEL_9000:
    logoobj_cnt = 0;
LABEL_13:
    data = logoobj_cnt;
    v7 = Box(s32, &data);
    v8 = Format("LogoImage/Logo_Image{0}", v7, 0);
    loading_str = v8;
    logoImage_local = logoImage;
    transform = get_transform(credits_ui_obj, 0);
    v13 = Find(transform, loading_str, 0);
    gameObject = get_gameObject(v13, 0);
    Component_object = GetComponent_object_(gameObject);
    v16 = Component_object;
    *(Il2CppClass **)((char *)&logoImage_local->obj.klass + i) = v16;
    ++v3;
    ++logoobj_cnt;
  }
  v17 = 0;
  for (j = 32; ; j += 8)
  {
    v20 = logoobj_max;
    if (v17 >= v20)
      break;
    if (logocenter_cnt < (s32)v20)
      goto LABEL_29;
    goto LABEL_9001;
    if (logocenter_cnt < logoobj_max)
    {
LABEL_29:
      goto LABEL_30;
    }
LABEL_9001:
    logocenter_cnt = 0;
LABEL_30:
    data = logocenter_cnt;
    v21 = Box(s32, &data);
    v22 = Format("LogoImageCenter/Logo_Image{0}", v21, 0);
    loading_str = v22;
    logoImageCenter_local = logoImageCenter;
    v26 = get_transform(credits_ui_obj, 0);
    v27 = Find(v26, loading_str, 0);
    v28 = get_gameObject(v27, 0);
    v29 = GetComponent_object_(v28);
    v30 = v29;
    *(Il2CppClass **)((char *)&logoImageCenter_local->obj.klass + j) = v30;
    ++v17;
    ++logocenter_cnt;
  }
  v31 = 0;
  for (k = 32; ; k += 8)
  {
    if (v31 >= staffobj_max)
      break;
    if (staffobj_cnt1 < (s32)staffobj_max)
      goto LABEL_46;
    goto LABEL_9002;
    if (staffobj_cnt1 < staffobj_max)
    {
LABEL_46:
      goto LABEL_47;
    }
LABEL_9002:
    staffobj_cnt1 = 0;
LABEL_47:
    data = staffobj_cnt1;
    v36 = Box(s32, &data);
    v37 = Format("StaffNameTM01/Staff_Name{0}", v36, 0);
    loading_str = v37;
    staffNameTM1_local = staffNameTM1;
    v41 = get_transform(credits_ui_obj, 0);
    v42 = Find(v41, loading_str, 0);
    v43 = get_gameObject(v42, 0);
    v44 = GetComponent_object_(v43);
    v45 = v44;
    *(Il2CppClass **)((char *)&staffNameTM1_local->obj.klass + k) = v45;
    v33 = *(s64 *)((char *)&staffNameTM1->obj.klass + k);
    (*(*(u64 *)v33 + 1368))(v33, "", *(u64 *)(*(u64 *)v33 + 1376));
    ++v31;
    ++staffobj_cnt1;
  }
  v46 = 0;
  for (m = 32; ; m += 8)
  {
    v50 = staffobj_max;
    if (v46 >= v50)
      break;
    if (staffobj_cnt2 <= (s32)v50)
      goto LABEL_63;
    goto LABEL_9003;
    if (staffobj_cnt2 <= staffobj_max)
    {
LABEL_63:
      goto LABEL_64;
    }
LABEL_9003:
    staffobj_cnt2 = 0;
LABEL_64:
    data = staffobj_cnt2;
    v51 = Box(s32, &data);
    v52 = Format("StaffNameTM02/Staff_Name{0}", v51, 0);
    loading_str = v52;
    staffNameTM2_local = staffNameTM2;
    v56 = get_transform(credits_ui_obj, 0);
    v57 = Find(v56, loading_str, 0);
    v58 = get_gameObject(v57, 0);
    v59 = GetComponent_object_(v58);
    v60 = v59;
    *(Il2CppClass **)((char *)&staffNameTM2_local->obj.klass + m) = v60;
    v48 = *(s64 *)((char *)&staffNameTM2->obj.klass + m);
    (*(*(u64 *)v48 + 1368))(v48, "", *(u64 *)(*(u64 *)v48 + 1376));
    ++v46;
    ++staffobj_cnt2;
  }
  v61 = 0;
  for (n = 32; ; n += 8)
  {
    if (v61 >= centerobj_max)
      break;
    if (centerobj_cnt < (s32)centerobj_max)
      goto LABEL_80;
    goto LABEL_9004;
    if (centerobj_cnt < centerobj_max)
    {
LABEL_80:
      goto LABEL_81;
    }
LABEL_9004:
    centerobj_cnt = 0;
LABEL_81:
    data = centerobj_cnt;
    v66 = Box(s32, &data);
    v67 = Format("CenterCaptionTM/Center_Caption{0}", v66, 0);
    loading_str = v67;
    centerCaptionTM_local = centerCaptionTM;
    v71 = get_transform(credits_ui_obj, 0);
    v72 = Find(v71, loading_str, 0);
    v73 = get_gameObject(v72, 0);
    v74 = GetComponent_object_(v73);
    v75 = v74;
    *(Il2CppClass **)((char *)&centerCaptionTM_local->obj.klass + n) = v75;
    v63 = *(s64 *)((char *)&centerCaptionTM->obj.klass + n);
    (*(*(u64 *)v63 + 1368))(v63, "", *(u64 *)(*(u64 *)v63 + 1376));
    ++v61;
    ++centerobj_cnt;
  }
  v76 = 0;
  for (ii = 32; ; ii += 8)
  {
    if (v76 >= jobobj_max)
      break;
    if (jobobj_cnt1 < (s32)jobobj_max)
      goto LABEL_97;
    goto LABEL_9005;
    if (jobobj_cnt1 < jobobj_max)
    {
LABEL_97:
      goto LABEL_98;
    }
LABEL_9005:
    jobobj_cnt1 = 0;
LABEL_98:
    data = jobobj_cnt1;
    v81 = Box(s32, &data);
    v82 = Format("JobCaptioinTM01/Job_Caption{0}", v81, 0);
    loading_str = v82;
    jobCaptionTM1_local = jobCaptionTM1;
    v86 = get_transform(credits_ui_obj, 0);
    v87 = Find(v86, loading_str, 0);
    v88 = get_gameObject(v87, 0);
    v89 = GetComponent_object_(v88);
    v90 = v89;
    *(Il2CppClass **)((char *)&jobCaptionTM1_local->obj.klass + ii) = v90;
    v78 = *(s64 *)((char *)&jobCaptionTM1->obj.klass + ii);
    (*(*(u64 *)v78 + 1368))(v78, "", *(u64 *)(*(u64 *)v78 + 1376));
    ++v76;
    ++jobobj_cnt1;
  }
  v91 = 0;
  for (jj = 32; ; jj += 8)
  {
    v96 = jobobj_max;
    if (v91 >= v96)
      break;
    if (jobobj_cnt2 < (s32)v96)
      goto LABEL_114;
    goto LABEL_9006;
    if (jobobj_cnt2 < jobobj_max)
    {
LABEL_114:
      goto LABEL_115;
    }
LABEL_9006:
    jobobj_cnt2 = 0;
LABEL_115:
    data = jobobj_cnt2;
    v97 = Box(s32, &data);
    v98 = Format("JobCaptioinTM02/Job_Caption{0}", v97, 0);
    loading_str = v98;
    jobCaptionTM2_local = jobCaptionTM2;
    v102 = get_transform(credits_ui_obj, 0);
    v103 = Find(v102, loading_str, 0);
    v104 = get_gameObject(v103, 0);
    v105 = GetComponent_object_(v104);
    v106 = v105;
    *(Il2CppClass **)((char *)&jobCaptionTM2_local->obj.klass + jj) = v106;
    v93 = *(s64 *)((char *)&jobCaptionTM2->obj.klass + jj);
    (*(*(u64 *)v93 + 1368))(v93, "", *(u64 *)(*(u64 *)v93 + 1376));
    ++v91;
    ++jobobj_cnt2;
  }
  goto LABEL_126;
LABEL_127:
  goto LABEL_128;
LABEL_129:
  if (!op_Equality(finalImage, 0, 0))
    goto LABEL_130;
  v125 = "FinalLogoImage";
  loading_str = "FinalLogoImage";
  v126 = get_transform(credits_ui_obj, 0);
  v127 = Find(v126, loading_str, 0);
  v128 = get_gameObject(v127, 0);
  v129 = GetComponent_object_(v128);
  finalImage = v129;
  set_sprite(finalImage, 0, 0);
  goto LABEL_9007;
LABEL_126:
  if (!op_Equality(copywriter, 0, 0))
    goto LABEL_127;
  v117 = "CopywriterText";
  loading_str = "CopywriterText";
  v118 = get_transform(credits_ui_obj, 0);
  v119 = Find(v118, loading_str, 0);
  v120 = get_gameObject(v119, 0);
  v121 = GetComponent_object_(v120);
  copywriter = v121;
  (copywriter->klass->vtable._66_set_text.methodPtr)(copywriter, "", copywriter->klass->vtable._66_set_text.method);
LABEL_128:
  goto LABEL_129;
LABEL_130:
LABEL_9007:
  virtualMethodPointer = *((MethodInfo *)CreditsMain + 2).virtualMethodPointer;
  *(u64 *)((char *)virtualMethodPointer + 28) = 0;
  *(u64 *)((char *)virtualMethodPointer + 20) = 0;
  *((u32 *)virtualMethodPointer + 11) = 0;
  *(u64 *)((char *)virtualMethodPointer + 36) = 0;
  DrawText(CreditsMain);
}

// 0x223ded0
static void CalcProcess(void) {
  s32 max_length;
  s32 height;
  s32 v5;
  bool v7;
  s64 v10;
  void *v13;
  s64 v14;
  void *v16;
  void *rectTransform;
  void *v20;
  f32 x;
  void *v22;
  s64 i;
  void *v26;
  s64 v27;
  void *v29;
  void *v32;
  void *v33;
  f32 v34;
  void *v35;
  s64 j;
  s64 k;
  s64 m;
  s64 n;
  s64 ii;
  u32 v46;
  void *v49;
  void *m_Sprite;
  char *v54;
  void *v56;
  void *v57;
  f32 v58;
  void *v59;
  void *v62;
  void *v63;
  f32 v64;
  void *v65;
  f32 v67;
  f32 wait_time;
  void *Instance;
  u32 frame_num;
  f32 y;
  f32 v75;
  f32 v76;
  sdfVector2_t v77;
  sdfVector2_t v78;
  sdfVector2_t v79;
  sdfVector2_t v80;

  max_length = CreditsData->max_length;
  height = get_height(0);
  if (height >= 0)
    v5 = height;
  else
    v5 = height + 1;
  scroll_speed = (f32)(50 * max_length + (v5 >> 1) - 200)
                                                            / creditsUIInstance->scroll_time;
  v7 = CHECK_PRESS(4096, 1);
  if (v7)
  {
    scroll_speed = scroll_speed
                                    * creditsUIInstance->speed_rate;
  }
  else
  {
    goto LABEL_20;
  }
LABEL_20:
  v10 = 4;
  scroll_speed = scroll_speed
                                  * VRF_DeltaTime;
  while (1)
  {
    if (v10 - 4 >= logoobj_max)
      break;
    v13 = *(void *)(*((u64 *)&logoImage->obj.klass + v10) + 216);
    v14 = 8 * v10;
    if (!op_Inequality(v13, 0, 0))
    {
      goto LABEL_30;
    }
    rectTransform = get_rectTransform(*(void *)((char *)&logoImage->obj.klass + v14), 0);
    v20 = get_rectTransform(*(void *)((char *)&logoImage->obj.klass + v14), 0);
    x = get_anchoredPosition(v20, 0).x;
    v22 = get_rectTransform(*(void *)((char *)&logoImage->obj.klass + v14), 0);
    v77.y = COERCE_FLOAT(LODWORD(get_anchoredPosition(v22, 0).y))
                 + scroll_speed;
    v77.x = x;
    set_anchoredPosition(rectTransform, v77, 0);
LABEL_30:
    v16 = get_rectTransform(*((void *)&logoImage->obj.klass + v10), 0);
    y = get_anchoredPosition(v16, 0).y;
    if ((f32)(y - logoEndPosOffset) >= (f32)((f32)orgScreenH * 0.5))
    {
      (*(**(u64 **)((char *)&logoImage->obj.klass + v14) + 680))(*(Il2CppClass **)((char *)&logoImage->obj.klass + v14), *(u64 *)(**(u64 **)((char *)&logoImage->obj.klass + v14) + 688), 255.0, 255.0, 255.0, 0.0);
      set_sprite(*(void *)((char *)&logoImage->obj.klass + v14), 0, 0);
    }
    ++v10;
  }
  for (i = 4; ; ++i)
  {
    if (i - 4 >= logoobj_max)
      break;
    v26 = *(void *)(*((u64 *)&logoImageCenter->obj.klass + i) + 216);
    v27 = 8 * i;
    if (!op_Inequality(v26, 0, 0))
    {
      goto LABEL_49;
    }
    v32 = get_rectTransform(*(void *)((char *)&logoImageCenter->obj.klass + v27), 0);
    v33 = get_rectTransform(*(void *)((char *)&logoImageCenter->obj.klass + v27), 0);
    v34 = get_anchoredPosition(v33, 0).x;
    v35 = get_rectTransform(*(void *)((char *)&logoImageCenter->obj.klass + v27), 0);
    v78.y = COERCE_FLOAT(LODWORD(get_anchoredPosition(v35, 0).y))
                 + scroll_speed;
    v78.x = v34;
    set_anchoredPosition(v32, v78, 0);
LABEL_49:
    v29 = get_rectTransform(*((void *)&logoImageCenter->obj.klass + i), 0);
    v75 = get_anchoredPosition(v29, 0).y;
    if ((f32)(v75 - logoEndPosOffset) >= (f32)((f32)orgScreenH * 0.5))
    {
      (*(**(u64 **)((char *)&logoImageCenter->obj.klass + v27) + 680))(*(Il2CppClass **)((char *)&logoImageCenter->obj.klass + v27), *(u64 *)(**(u64 **)((char *)&logoImageCenter->obj.klass + v27) + 688), 255.0, 255.0, 255.0, 0.0);
      set_sprite(*(void *)((char *)&logoImageCenter->obj.klass + v27), 0, 0);
    }
  }
  for (j = 0; ; ++j)
  {
    if (j >= staffobj_max)
      break;
    TextScroll(staffNameTM1[j]);
  }
  for (k = 0; ; ++k)
  {
    if (k >= staffobj_max)
      break;
    TextScroll(staffNameTM2[k]);
  }
  for (m = 0; ; ++m)
  {
    if (m >= centerobj_max)
      break;
    TextScroll(centerCaptionTM[m]);
  }
  for (n = 0; ; ++n)
  {
    if (n >= jobobj_max)
      break;
    TextScroll(jobCaptionTM1[n]);
  }
  for (ii = 0; ; ++ii)
  {
    if (ii >= jobobj_max)
      break;
    TextScroll(jobCaptionTM2[ii]);
  }
  if (!v46)
  {
LABEL_95:
    goto LABEL_96;
LABEL_104:
    m_Sprite = finalImage->m_Sprite;
    if (!op_Inequality(m_Sprite, 0, 0))
    {
LABEL_108:
      v54 = (copywriter->klass->vtable._65_get_text.methodPtr)(copywriter, copywriter->klass->vtable._65_get_text.method);
      if (op_Inequality(v54, "", 0))
      {
        v56 = get_rectTransform(copywriter, 0);
        v57 = get_rectTransform(copywriter, 0);
        v58 = get_anchoredPosition(v57, 0).x;
        v59 = get_rectTransform(copywriter, 0);
        v79.y = COERCE_FLOAT(LODWORD(get_anchoredPosition(v59, 0).y))
                     + scroll_speed;
        v79.x = v58;
        set_anchoredPosition(v56, v79, 0);
      }
      init_positoin_y = init_positoin_y + scroll_speed;
      return;
    }
    v62 = get_rectTransform(finalImage, 0);
    v63 = get_rectTransform(finalImage, 0);
    v64 = get_anchoredPosition(v63, 0).x;
    v65 = get_rectTransform(finalImage, 0);
    v80.y = COERCE_FLOAT(LODWORD(get_anchoredPosition(v65, 0).y))
                 + scroll_speed;
    v80.x = v64;
    set_anchoredPosition(v62, v80, 0);
    goto LABEL_108;
  }
  goto LABEL_95;
LABEL_96:
  if (credits_item_count < SLODWORD(CreditsData->max_length))
    goto LABEL_104;
  v49 = get_rectTransform(finalImage, 0);
  v76 = get_anchoredPosition(v49, 0).y;
  if (v76 < 0.0)
    goto LABEL_104;
  v67 = now_count + VRF_DeltaTime;
  wait_time = creditsUIInstance->wait_time;
  now_count = v67;
  if (v67 >= wait_time)
  {
    if (!is_start_fade)
    {
      Instance = get_Instance(0);
      ChangeFadeOutTime(Instance, 10 * creditsUIInstance->bgm_fadeout_frame, 0);
      sndBgmStop();
      frame_num = creditsUIInstance->frame_num;
      dds3FadeOut(0, 0, 0, frame_num);
      is_start_fade = 1;
    }
  }
  if (!dds3FadeCheck())
  {
    if (is_start_fade)
    {
      is_end = 1;
    }
  }
}

// 0x223ec60
static void DrawProcess(void) {
  DrawText(CreditsMain);
}

// 0x223cc80
static void ParentRegister(void) {
  void *v5;

  if (!op_Equality(credits_ui_obj, 0, 0))
    return;
  v5 = Find("Credits");
  credits_ui_obj = v5;
}

// 0x223cdb0
static void DrawText(void) {
  s32 v6;
  void *m_Sprite;
  bool v12;
  void *v14;
  char *v16;
  s64 v17;
  s64 v18;
  void *v19;
  void *v20;
  void *v21;
  f32 v22;
  f32 v24;
  f32 v25;
  void *v26;
  void *v27;
  f32 v28;
  void *v29;
  u32 v31;
  creditsUI_CreditsLogo_t *v32;
  s32 v34;
  s32 v35;
  u32 v37;
  Credits_t *v38;
  void *v39;
  char *v41;
  s64 v42;
  s64 j;
  void *v44;
  void *v45;
  void *v46;
  f32 v47;
  f32 v49;
  f32 v50;
  void *v51;
  void *v52;
  f32 v53;
  void *v54;
  u32 v56;
  creditsUI_CreditsLogo_t *v57;
  s32 v60;
  void *v63;
  f32 v64;
  s32 v67;
  s32 v68;
  void *v70;
  s32 v72;
  s32 v73;
  void *v75;
  s32 v78;
  s64 v80;
  void *v81;
  char *v82;
  void *v85;
  f32 v86;
  s32 v88;
  s32 v90;
  char *v91;
  void *rectTransform;
  void *v93;
  f32 x;
  f32 between_line;
  void *v98;
  void *v99;
  f32 y;
  void *v101;
  char *v103;
  s64 v104;
  s64 i;
  void *v106;
  void *v107;
  f32 v108;
  f32 v110;
  f32 v111;
  void *v112;
  void *v113;
  f32 v114;
  void *v115;
  u32 v117;
  creditsUI_CreditsLogo_t *creditsImages;
  void *v120;
  s32 v122;
  s32 v123;
  f32 v124;
  f32 v125;
  f32 v126;
  f32 v127;
  f32 v128;
  sdfVector2_t v129;
  sdfVector2_t v130;
  sdfVector2_t v131;
  sdfVector2_t v132;

  while (1)
  {
LABEL_5:
    if (credits_item_count >= SLODWORD(CreditsData->max_length))
      return;
    v6 = credits_item_count;
    if (v6 == LODWORD(CreditsData->max_length) - 1)
    {
      v91 = Format("{0}", CreditsData[credits_item_count]->caption2, 0);
      (copywriter->klass->vtable._66_set_text.methodPtr)(copywriter, v91, copywriter->klass->vtable._66_set_text.method);
      rectTransform = get_rectTransform(copywriter, 0);
      v93 = get_rectTransform(copywriter, 0);
      x = get_anchoredPosition(v93, 0).x;
      between_line = creditsUIInstance->between_line;
      v98 = get_rectTransform(copywriter, 0);
      v131.y = (f32)(init_positoin_y - between_line)
                    + COERCE_FLOAT(LODWORD(get_sizeDelta(v98, 0).y));
      v131.x = x;
      set_anchoredPosition(rectTransform, v131, 0);
      v99 = get_rectTransform(copywriter, 0);
      y = get_anchoredPosition(v99, 0).y;
      v101 = get_rectTransform(copywriter, 0);
      v127 = get_sizeDelta(v101, 0).y;
      init_positoin_y = y - v127;
LABEL_177:
      ++credits_item_count;
      return;
    }
    if (CreditsData[credits_item_count]->dispControlFlg != 4)
      goto LABEL_27;
    m_Sprite = finalImage->m_Sprite;
LABEL_26:
    v12 = op_Equality(m_Sprite, 0, 0);
    if (!v12)
      goto LABEL_27;
    v103 = Format("{0}", CreditsData[credits_item_count]->caption2, 0);
    v104 = 0;
    for (i = 0; ; ++i)
    {
      creditsImages = creditsUIInstance->creditsImages;
      if (i >= SLODWORD(creditsImages->max_length))
      {
        goto LABEL_177;
      }
      if (v117)
      {
        if (!op_Equality(v103, creditsImages[v104].name, 0))
          goto LABEL_156;
      }
      else
      {
        if (!op_Equality(v103, creditsUIInstance->creditsImages[v104].name, 0))
          goto LABEL_156;
      }
      (finalImage->klass->vtable._23_set_color.methodPtr)(finalImage, finalImage->klass->vtable._23_set_color.255.0, 255.0, 255.0, 1.0);
      set_sprite(finalImage, creditsUIInstance->creditsImages[v104].image, 0);
      v106 = get_rectTransform(finalImage, 0);
      v107 = get_rectTransform(finalImage, 0);
      v108 = get_anchoredPosition(v107, 0).x;
      v110 = init_positoin_y;
      v111 = creditsUIInstance->between_line;
      v112 = get_rectTransform(finalImage, 0);
      v132.y = (f32)(v110 - v111)
                    + COERCE_FLOAT(LODWORD(get_sizeDelta(v112, 0).y));
      v132.x = v108;
      set_anchoredPosition(v106, v132, 0);
      v113 = get_rectTransform(finalImage, 0);
      v114 = get_anchoredPosition(v113, 0).y;
      v115 = get_rectTransform(finalImage, 0);
      init_positoin_y = v114
                                                                   - COERCE_FLOAT(LODWORD(get_sizeDelta(v115, 0).y));
LABEL_156:
      ++v104;
    }
    goto LABEL_26;
LABEL_27:
    if (CreditsData[credits_item_count]->dispControlFlg == 2)
      break;
LABEL_55:
    v38 = CreditsData[credits_item_count];
    if (v38->dispControlFlg == 3)
    {
      v39 = logoImageCenter[logocenter_cnt]->m_Sprite;
      if (!op_Equality(v39, 0, 0))
        return;
      v41 = Format("{0}", CreditsData[credits_item_count]->caption2, 0);
      v42 = 0;
      for (j = 0; ; ++j)
      {
        v57 = creditsUIInstance->creditsImages;
        if (j >= SLODWORD(v57->max_length))
        {
          ++credits_item_count;
          v60 = logocenter_cnt + 1;
          logocenter_cnt = v60;
          if (v60 > logoobj_max)
          {
            logocenter_cnt = 0;
          }
          goto LABEL_5;
        }
        if (v56)
        {
          if (!op_Equality(v41, v57[v42].name, 0))
            goto LABEL_67;
        }
        else
        {
          if (!op_Equality(v41, creditsUIInstance->creditsImages[v42].name, 0))
            goto LABEL_67;
        }
        v44 = logoImageCenter[logocenter_cnt];
        (v44->klass->vtable._23_set_color.methodPtr)(v44, v44->klass->vtable._23_set_color.255.0, 255.0, 255.0, 1.0);
        set_sprite(logoImageCenter[logocenter_cnt], creditsUIInstance->creditsImages[v42].image, 0);
        v45 = get_rectTransform(logoImageCenter[logocenter_cnt], 0);
        v46 = get_rectTransform(logoImageCenter[logocenter_cnt], 0);
        v47 = get_anchoredPosition(v46, 0).x;
        v49 = init_positoin_y;
        v50 = creditsUIInstance->between_line;
        v51 = get_rectTransform(logoImageCenter[logocenter_cnt], 0);
        v130.y = (f32)(v49 - v50)
                      + COERCE_FLOAT(LODWORD(get_sizeDelta(v51, 0).y));
        v130.x = v47;
        set_anchoredPosition(v45, v130, 0);
        v52 = get_rectTransform(logoImageCenter[logocenter_cnt], 0);
        v53 = get_anchoredPosition(v52, 0).y;
        v54 = get_rectTransform(logoImageCenter[logocenter_cnt], 0);
        init_positoin_y = v53
                                                                     - COERCE_FLOAT(LODWORD(get_sizeDelta(v54, 0).y));
LABEL_67:
        ++v42;
      }
    }
    if (v37)
    {
      if (v38->caption1)
        goto LABEL_89;
LABEL_99:
      if (!CheckBlank(credits_item_count))
        return;
      if (CreditsData[credits_item_count]->caption1)
      {
        AddText(jobCaptionTM1[jobobj_cnt1], 0);
        v63 = get_rectTransform(jobCaptionTM1[jobobj_cnt1], 0);
        v124 = get_anchoredPosition(v63, 0).y;
        v64 = v124;
        v67 = jobobj_cnt1 + 1;
        jobobj_cnt1 = v67;
        if (v67 >= jobobj_max)
        {
          jobobj_cnt1 = 0;
        }
        v68 = 1;
      }
      else
      {
        v68 = 0;
        v64 = 0.0;
      }
      if (CreditsData[credits_item_count]->caption2)
      {
        AddText(jobCaptionTM2[jobobj_cnt2], 1);
        v70 = get_rectTransform(jobCaptionTM2[jobobj_cnt2], 0);
        v125 = get_anchoredPosition(v70, 0).y;
        v64 = v125;
        v72 = jobobj_max;
        v73 = jobobj_cnt2 + 1;
        jobobj_cnt2 = v73;
        if (v73 >= v72)
        {
          jobobj_cnt2 = 0;
        }
        ++v68;
      }
      if (CreditsData[credits_item_count]->name1)
      {
        AddText(staffNameTM1[staffobj_cnt1], 2);
        v75 = get_rectTransform(staffNameTM1[staffobj_cnt1], 0);
        v126 = get_anchoredPosition(v75, 0).y;
        v64 = v126;
        v78 = staffobj_cnt1 + 1;
        staffobj_cnt1 = v78;
        if (v78 >= staffobj_max)
        {
          staffobj_cnt1 = 0;
        }
        v68 = 1;
      }
      v80 = credits_item_count;
      if (CreditsData[v80]->name2)
      {
        AddText(staffNameTM2[staffobj_cnt2], 3);
        v120 = get_rectTransform(staffNameTM2[staffobj_cnt2], 0);
        v128 = get_anchoredPosition(v120, 0).y;
        v64 = v128;
        v122 = staffobj_max;
        v123 = staffobj_cnt2 + 1;
        staffobj_cnt2 = v123;
        if (v123 >= v122)
        {
          staffobj_cnt2 = 0;
        }
LABEL_174:
        init_positoin_y = v64;
        goto LABEL_177;
      }
      if (v68)
        goto LABEL_174;
      LODWORD(v80) = credits_item_count;
      credits_item_count = v80 + 1;
      init_positoin_y = init_positoin_y - creditsUIInstance->between_line;
    }
    else
    {
      v38 = CreditsData[credits_item_count];
      if (!v38->caption1)
        goto LABEL_99;
LABEL_89:
      if (v38->caption2)
        goto LABEL_99;
      if (v38->name1)
        goto LABEL_99;
      if (v38->name2)
        goto LABEL_99;
      v81 = centerCaptionTM[centerobj_cnt];
      v82 = (v81->klass->vtable._65_get_text.methodPtr)(v81, v81->klass->vtable._65_get_text.method);
      if (!op_Equality(v82, "", 0))
        return;
      AddText(centerCaptionTM[centerobj_cnt], 1);
      v85 = get_rectTransform(centerCaptionTM[centerobj_cnt], 0);
      v86 = get_anchoredPosition(v85, 0).y;
      v88 = credits_item_count;
      init_positoin_y = v86;
      credits_item_count = v88 + 1;
      v90 = centerobj_cnt + 1;
      centerobj_cnt = v90;
      if (v90 >= centerobj_max)
      {
        centerobj_cnt = 0;
      }
    }
  }
  v14 = logoImage[logoobj_cnt]->m_Sprite;
  if (op_Equality(v14, 0, 0))
  {
    v16 = Format("{0}", CreditsData[credits_item_count]->caption2, 0);
    v17 = 0;
    v18 = 0;
    while (2)
    {
      v32 = creditsUIInstance->creditsImages;
      if (v18 >= SLODWORD(v32->max_length))
      {
        v34 = logoobj_max;
        ++credits_item_count;
        v35 = logoobj_cnt + 1;
        logoobj_cnt = v35;
        if (v35 > v34)
        {
          logoobj_cnt = 0;
        }
        goto LABEL_55;
      }
      if (v31)
      {
        if (op_Equality(v16, v32[v17].name, 0))
        {
LABEL_47:
          v19 = logoImage[logoobj_cnt];
          (v19->klass->vtable._23_set_color.methodPtr)(v19, v19->klass->vtable._23_set_color.255.0, 255.0, 255.0, 1.0);
          set_sprite(logoImage[logoobj_cnt], creditsUIInstance->creditsImages[v17].image, 0);
          v20 = get_rectTransform(logoImage[logoobj_cnt], 0);
          v21 = get_rectTransform(logoImage[logoobj_cnt], 0);
          v22 = get_anchoredPosition(v21, 0).x;
          v24 = init_positoin_y;
          v25 = creditsUIInstance->between_line;
          v26 = get_rectTransform(logoImage[logoobj_cnt], 0);
          v129.y = (f32)(v24 - v25)
                        + COERCE_FLOAT(LODWORD(get_sizeDelta(v26, 0).y));
          v129.x = v22;
          set_anchoredPosition(v20, v129, 0);
          v27 = get_rectTransform(logoImage[logoobj_cnt], 0);
          v28 = get_anchoredPosition(v27, 0).y;
          v29 = get_rectTransform(logoImage[logoobj_cnt], 0);
          init_positoin_y = v28
                                                                       - COERCE_FLOAT(LODWORD(get_sizeDelta(v29, 0).y));
        }
      }
      else
      {
        if (op_Equality(v16, creditsUIInstance->creditsImages[v17].name, 0))
        {
          goto LABEL_47;
        }
      }
      ++v18;
      ++v17;
      continue;
    }
  }
}

// 0x223efd0
static bool CheckBlank(s32 itemCount) {
  void *v5;
  char *v6;
  void *v11;
  char *v12;
  void *v13;
  char *v14;
  void *v15;
  char *v16;

  if (CreditsData[itemCount]->caption1)
  {
    v5 = jobCaptionTM1[jobobj_cnt1];
    v6 = (v5->klass->vtable._65_get_text.methodPtr)(v5, v5->klass->vtable._65_get_text.method);
    if (op_Inequality(v6, "", 0))
      return 0;
  }
  if (!CreditsData[itemCount]->caption2)
  {
    goto LABEL_14;
  }
  v11 = jobCaptionTM2[jobobj_cnt2];
  v12 = (v11->klass->vtable._65_get_text.methodPtr)(v11, v11->klass->vtable._65_get_text.method);
  if (op_Inequality(v12, "", 0))
    return 0;
LABEL_14:
  if (!CreditsData[itemCount]->name1)
  {
    goto LABEL_16;
  }
  v13 = staffNameTM1[staffobj_cnt1];
  v14 = (v13->klass->vtable._65_get_text.methodPtr)(v13, v13->klass->vtable._65_get_text.method);
  if (op_Inequality(v14, "", 0))
    return 0;
LABEL_16:
  if (!CreditsData[itemCount]->name2)
    return 1;
  v15 = staffNameTM2[staffobj_cnt2];
  v16 = (v15->klass->vtable._65_get_text.methodPtr)(v15, v15->klass->vtable._65_get_text.method);
  return !op_Inequality(v16, "", 0);
}

// 0x223eae0
static void TextScroll(void *text) {
  char *v3;
  void *rectTransform;
  void *v5;
  f32 x;
  void *v7;
  f32 v9;
  void *v10;
  f32 v12;
  f32 y;
  f32 v14;
  sdfVector2_t v15;

  v3 = (text->klass->vtable._65_get_text.methodPtr)(text, text->klass->vtable._65_get_text.method);
  if (op_Inequality(v3, "", 0))
  {
    rectTransform = get_rectTransform(text, 0);
    v5 = get_rectTransform(text, 0);
    x = get_anchoredPosition(v5, 0).x;
    v7 = get_rectTransform(text, 0);
    y = get_anchoredPosition(v7, 0).y;
    v9 = y;
    v15.y = v9 + scroll_speed;
    v15.x = x;
    set_anchoredPosition(rectTransform, v15, 0);
  }
  v10 = get_rectTransform(text, 0);
  v14 = get_anchoredPosition(v10, 0).y;
  v12 = v14;
  if ((f32)(v12 - textEndPosOffset) > (f32)((f32)orgScreenH * 0.5))
    (text->klass->vtable._66_set_text.methodPtr)(text, "", text->klass->vtable._66_set_text.method);
}

// 0x223ecd0
static void AddText(void *text, CreditsMain_DisplayObj obj) {
  Il2CppObject *caption1;
  f32 cap2CenterPos_local;
  char *v8;
  s32 v11;
  void *transform;
  void *v18;
  void *v19;
  void *rectTransform;
  void *v21;
  f32 v23;
  f32 x;
  sdfVector2_t v25;
  sdfVector3_t v26;

  switch (obj)
  {
    case 0:
      caption1 = CreditsData[credits_item_count]->caption1;
      goto LABEL_25;
    case 1:
      v8 = Format("{0}", CreditsData[credits_item_count]->caption2, 0);
      if (CreditsData[credits_item_count]->dispControlFlg == 1)
        v11 = 514;
      else
        v11 = 516;
      set_alignment(jobCaptionTM2[jobobj_cnt2], v11, 0);
      if (CreditsData[credits_item_count]->dispControlFlg == 1)
      {
        cap2CenterPos_local = cap2CenterPos;
      }
      else
      {
        cap2CenterPos_local = cap2RightPos;
      }
      break;
    case 2:
      caption1 = CreditsData[credits_item_count]->name1;
      goto LABEL_25;
    case 3:
      caption1 = CreditsData[credits_item_count]->name2;
LABEL_25:
      v8 = Format("{0}", caption1, 0);
      transform = get_transform(text, 0);
      cap2CenterPos_local = get_localPosition(transform, 0).x;
      break;
    default:
      cap2CenterPos_local = 0.0;
      v8 = "";
      break;
  }
  (text->klass->vtable._66_set_text.methodPtr)(text, v8, text->klass->vtable._66_set_text.method);
  v18 = get_transform(text, 0);
  v19 = get_transform(text, 0);
  v26.y = get_localPosition(v19, 0).y;
  v26.z = 0.0;
  v26.x = cap2CenterPos_local;
  set_localPosition(v18, v26, 0);
  rectTransform = get_rectTransform(text, 0);
  v21 = get_rectTransform(text, 0);
  x = get_anchoredPosition(v21, 0).x;
  v23 = x;
  v25.y = init_positoin_y - creditsUIInstance->between_line;
  v25.x = v23;
  set_anchoredPosition(rectTransform, v25, 0);
}

// 0x223bab0
s32 GetCreditsTableMax(void) {
  return CreditsData->max_length;
}

// 0x223f2b0
bool IsEndCredits(void) {
  return is_end;
}
