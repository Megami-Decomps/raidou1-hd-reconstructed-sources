#include "types.h"
#include "cfg.h"
#include "configgamepad.h"
#include "configgraphics.h"
#include "dat.h"
#include "dds3padmanager.h"
#include "libsdf.h"
#include "localize.h"
#include "scr.h"
#include "slmain.h"

static void *btntag_config;
static void *keyid_to_btntag;
static s32 **gConfigFlagBak;
static s32 gConfigChange;
static s32 **config_allInitdate;
s32 **sbtl_shortCutDefault;

static s32 GetConfigKeyID(s32 tbl_keyid);
static char *GetPadToSpriteTag(SDF_PADMAP pad);
static char *GetKeyid_to_Btntag(s32 keyid);
static char *BtnSpriteCalc(char *sprite_name);

// 0x18bea70
void cfgBtnTagConfigLoad(void) {
  void *Asset;
  s64 naturalAligment;
  void *v5;
  void *v6;
  s64 v8;

  Asset = LoadAsset(_Ctrl_k__BackingField, "common", "btntag_config", 0);
  if (!Asset)
  {
    v6 = 0;
    btntag_config = 0;
    goto LABEL_16;
  }
  if (Asset->klass->_2.naturalAligment >= (u32)naturalAligment)
  {
    if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_BtnTagConfig)
      v5 = Asset;
    else
      v5 = 0;
  }
  else
  {
    v5 = 0;
  }
  btntag_config = v5;
  if (Asset->klass->_2.naturalAligment >= (u32)v8)
  {
    if (Asset->klass->_2.typeHierarchy[v8 - 1] == Project_BtnTagConfig)
      v6 = Asset;
    else
      v6 = 0;
  }
  else
  {
    v6 = 0;
  }
LABEL_16:
}

// 0x18bec50
char *cfgGetBtnTagConfig(char *text_label, char *org_text) {
  char **v6;
  s32 v7;
  s64 (__fastcall **v8)();
  char *v9;
  char *v11;
  char *v12;
  char *v13;
  char *v15;
  char *v17;
  char *v18;
  char *v19;
  char *v20;
  char *v21;
  void *v23;
  void *itemtbl;
  Il2CppObject *Item;
  Il2CppObject *v26;
  s32 klass;
  char *PadToSpriteTag;
  char *v32;
  char *v33;
  char *v34;
  char *v36;
  char *v38;
  char *v39;
  char *v40;
  char **v41;
  s64 (__fastcall **v42)();
  char **v43;
  char *v44;
  s32 v45;
  s32 v46;
  char *monitor;
  s32 v48;
  char *v49;
  char *v50;
  char *v51;
  char *v52;
  u32 ConfigKeyID;
  char *v55;
  char *v57;
  char *v58;
  char *v59;
  char *v61;
  char *v63;
  char *v65;
  char *v67;
  char *v68;
  char *v69;
  char *v71;
  char *v73;
  s32 v75;
  Il2CppObject *v77;
  char *v79;
  char *v81;
  s32 v82;
  char *v86;
  char *v87;
  char *v89;
  char *v91;
  char *v92;
  char *v93;
  char *v95;
  char *v97;
  char *v98;
  char **v99;
  char *v100;
  char *v101;
  s32 v104;
  s32 ConfigGAMEPAD;
  char *Keyid_to_Btntag;
  char *v109;
  char *v110;
  char *v111;
  char *v113;
  char *v115;
  char *v116;
  char **v117;
  s32 v120;
  s32 v121;
  char *v123;
  char *v125;
  char *v126;
  char *v127;
  char *v129;
  char *v131;
  char *v133;
  char *v134;
  char *v135;
  char *v137;
  char *v138;
  char *v140;
  char *v141;
  char *v142;
  char *v143;
  char *v145;
  char *v146;
  char *v148;
  char *v149;
  char *v151;
  char *v152;
  char *v154;
  char *v156;
  char *v157;
  char *v159;
  char *v161;
  char *v162;
  char *v163;
  char **v164;
  char *v166;
  char **v167;
  s32 ConfigPadMap;
  s32 PadMapToKeyID;
  Il2CppObject *v172;
  char *v174;
  s32 v175;
  s32 v176;
  Il2CppObject *v178;
  char v180;
  s32 v181;

  v181 = 0;
  if (IsNullOrEmpty(org_text, 0))
  {
    org_text = GetLocalizeText(text_label, 1);
  }
  v180 = 0;
  v6 = &"+";
  v7 = 0;
  v8 = off_5755000;
  {
    if (((u8)v8[464] & 1) == 0)
      goto LABEL_18;
LABEL_15:
    if (v7 >= btntag_config->_itemtbl->_size)
      goto LABEL_148;
LABEL_19:
    v23 = btntag_config;
    itemtbl = v23->_itemtbl;
    if (itemtbl->_size <= v7)
      goto LABEL_12;
    Item = _get_Item(itemtbl, v7);
    if (!Item)
      goto LABEL_12;
    v26 = Item;
    if (!Equals_54828784(text_label, Item[1].klass, 0))
      goto LABEL_12;
    klass = v26[2].klass;
    if (klass <= -2)
    {
      v42 = v8;
      v43 = v6;
      v181 = 0;
      v44 = text_label;
      v45 = -klass;
      if (-klass >= 1)
      {
        do
        {
          v46 = IndexOf_54852384(org_text, v26[1].monitor, 0);
          if ((v46 & 0x80000000) == 0)
          {
            monitor = v26[1].monitor;
            v48 = v46;
            v49 = ToString_55996800((s32)&v181, "d1", 0);
            v50 = Concat_54766928(v49, ">", 0);
            v51 = Replace_54838864(monitor, ">", v50, 0);
            v52 = Remove(org_text, v48, *((u32 *)v26[1].monitor + 4), 0);
            org_text = Insert(v52, v48, v51, 0);
          }
          ++v181;
        }
        while (v181 < v45);
      }
      text_label = v44;
      v6 = v43;
      v8 = v42;
    }
    else
    {
      if ((u32)(klass + 1) > 1)
      {
        ConfigKeyID = GetConfigKeyID(klass);
        if (ConfigKeyID > 0xFFFFFFFD)
          goto LABEL_12;
        v75 = ConfigKeyID;
        v77 = object___get_Item(keyid_to_btntag, v75);
        if (op_Inequality(v77, "", 0))
        {
          org_text = Replace_54838864(org_text, v26[1].monitor, v77, 0);
          v180 = 1;
        }
        goto LABEL_12;
      }
      if (Equals_54828784(v26[1].monitor, "<BTN_R2>+<BTN_X>", 0))
      {
        PadToSpriteTag = GetPadToSpriteTag(28684);
        v32 = GetPadToSpriteTag(28674);
        v33 = Concat_54831728(PadToSpriteTag, *v6, v32, 0);
        v34 = Replace_54838864(org_text, v26[1].monitor, v33, 0);
        v36 = GetPadToSpriteTag(28684);
        v38 = GetPadToSpriteTag(28674);
        v39 = Concat_54831728(v36, *v6, v38, 0);
        v40 = Replace_54838864(v34, "<BTN_R2>+<BTN_X>", v39, 0);
        v41 = &"<BTN_R2>＋<BTN_X>";
LABEL_49:
        org_text = Replace_54838864(v40, *v41, v39, 0);
        v180 = 1;
        goto LABEL_12;
      }
      if (Equals_54828784(v26[1].monitor, "<BTN_R2>+<BTN_Y>", 0))
      {
        v55 = GetPadToSpriteTag(28684);
        v57 = GetPadToSpriteTag(28675);
        v58 = Concat_54831728(v55, *v6, v57, 0);
        v59 = Replace_54838864(org_text, v26[1].monitor, v58, 0);
        v61 = GetPadToSpriteTag(28684);
        v63 = GetPadToSpriteTag(28675);
        v39 = Concat_54831728(v61, *v6, v63, 0);
        v40 = Replace_54838864(v59, "<BTN_R2>+<BTN_Y>", v39, 0);
        v41 = &"<BTN_R2>＋<BTN_Y>";
        goto LABEL_49;
      }
      if (Equals_54828784(v26[1].monitor, "<BTN_R2>+<BTN_B>", 0))
      {
        v65 = GetPadToSpriteTag(28684);
        v67 = GetPadToSpriteTag(28673);
        v68 = Concat_54831728(v65, *v6, v67, 0);
        v69 = Replace_54838864(org_text, v26[1].monitor, v68, 0);
        v71 = GetPadToSpriteTag(28684);
        v73 = GetPadToSpriteTag(28673);
        v39 = Concat_54831728(v71, *v6, v73, 0);
        v40 = Replace_54838864(v69, "<BTN_R2>+<BTN_B>", v39, 0);
        v41 = &"<BTN_R2>＋<BTN_B>";
        goto LABEL_49;
      }
      if (Equals_54828784(v26[1].monitor, "<BTN_R2>+<BTN_A>", 0))
      {
        v9 = GetPadToSpriteTag(28684);
        v11 = GetPadToSpriteTag(28672);
        v12 = Concat_54831728(v9, *v6, v11, 0);
        v13 = Replace_54838864(org_text, v26[1].monitor, v12, 0);
        v15 = GetPadToSpriteTag(28684);
        v17 = GetPadToSpriteTag(28672);
        v18 = Concat_54831728(v15, *v6, v17, 0);
        v19 = Replace_54838864(v13, "<BTN_R2>+<BTN_A>", v18, 0);
        v20 = v18;
        v21 = "<BTN_R2>＋<BTN_A>";
        goto LABEL_11;
      }
      if (Equals_54828784(v26[1].monitor, "<BTN_R1>+<BTN_ARL>", 0))
      {
        v79 = Replace_54838864(org_text, "＋", *v6, 0);
        v81 = GetPadToSpriteTag(24587);
        v82 = 24582;
        goto LABEL_74;
      }
      if (Equals_54828784(v26[1].monitor, "<BTN_R1>+<BTN_ARU>", 0))
      {
        v79 = Replace_54838864(org_text, "＋", *v6, 0);
        v81 = GetPadToSpriteTag(24587);
        v82 = 24580;
        goto LABEL_74;
      }
      if (Equals_54828784(v26[1].monitor, "<BTN_R1>+<BTN_ARD>", 0))
      {
        v79 = Replace_54838864(org_text, "＋", *v6, 0);
        v81 = GetPadToSpriteTag(24587);
        v82 = 24581;
LABEL_74:
        v86 = GetPadToSpriteTag(v82);
        v87 = Concat_54831728(v81, *v6, v86, 0);
        v21 = v26[1].monitor;
        v20 = v87;
        v19 = v79;
LABEL_11:
        org_text = Replace_54838864(v19, v21, v20, 0);
        v180 = 1;
        goto LABEL_12;
      }
      if (Equals_54828784(v26[1].monitor, "<BTN_R2> + <BTN_DU>", 0))
      {
        v89 = GetPadToSpriteTag(28684);
        v91 = GetPadToSpriteTag(28676);
        v92 = Concat_54831728(v89, " + ", v91, 0);
        v93 = Replace_54838864(org_text, v26[1].monitor, v92, 0);
        v95 = GetPadToSpriteTag(28684);
        v97 = GetPadToSpriteTag(28676);
        v98 = Concat_54831728(v95, *v6, v97, 0);
        v99 = &"<BTN_R2>+<BTN_DU>";
        goto LABEL_79;
      }
      if (Equals_54828784(v26[1].monitor, "<BTN_Y>+<BTN_B>", 0))
      {
        v104 = cfgGetConfigGAMEPAD(10, 0) >> 16;
        ConfigGAMEPAD = (u16)cfgGetConfigGAMEPAD(10, 0);
        Keyid_to_Btntag = GetKeyid_to_Btntag(v104);
        v109 = GetKeyid_to_Btntag(ConfigGAMEPAD);
        v110 = Concat_54831728(Keyid_to_Btntag, " + ", v109, 0);
        v111 = Replace_54838864(org_text, v26[1].monitor, v110, 0);
        v113 = GetKeyid_to_Btntag(v104);
        v115 = GetKeyid_to_Btntag(ConfigGAMEPAD);
        v116 = Concat_54831728(v113, " + ", v115, 0);
        v101 = Replace_54838864(v111, "<BTN_Y>+<BTN_B>", v116, 0);
        v117 = &"<BTN_Y>＋<BTN_B>";
        goto LABEL_88;
      }
      if (Equals_54828784(v26[1].monitor, "<BTN_X>+<BTN_A>", 0))
      {
        v120 = cfgGetConfigGAMEPAD(11, 0) >> 16;
        v121 = (u16)cfgGetConfigGAMEPAD(11, 0);
        v123 = GetKeyid_to_Btntag(v120);
        v125 = GetKeyid_to_Btntag(v121);
        v126 = Concat_54831728(v123, " + ", v125, 0);
        v127 = Replace_54838864(org_text, v26[1].monitor, v126, 0);
        v129 = GetKeyid_to_Btntag(v120);
        v131 = GetKeyid_to_Btntag(v121);
        v116 = Concat_54831728(v129, " + ", v131, 0);
        v101 = Replace_54838864(v127, "<BTN_X>+<BTN_A>", v116, 0);
        v117 = &"<BTN_X>＋<BTN_A>";
LABEL_88:
        v100 = *v117;
        v98 = v116;
LABEL_89:
        org_text = Replace_54838864(v101, v100, v98, 0);
        goto LABEL_12;
      }
      if (Equals_54828784(v26[1].monitor, "<BTN_R2> + <BTN_DL> or <BTN_DR>", 0))
      {
        v133 = NewSpecific(string, 5u);
        v134 = GetPadToSpriteTag(28684);
        v133[0] = v134;
        v135 = " + ";
        v133[1] = " + ";
        v137 = GetPadToSpriteTag(28678);
        v133[2] = v137;
        v138 = " or ";
        v133[3] = " or ";
        v140 = GetPadToSpriteTag(28679);
        v133[4] = v140;
        v141 = Concat_54832608(v133, 0);
        v142 = Replace_54838864(org_text, v26[1].monitor, v141, 0);
        v143 = NewSpecific(string, 5u);
        v145 = GetPadToSpriteTag(28684);
        v143[0] = v145;
        v146 = " + ";
        v143[1] = " + ";
        v148 = GetPadToSpriteTag(28678);
        v143[2] = v148;
        v149 = " or ";
        v143[3] = " or ";
        v151 = GetPadToSpriteTag(28679);
        v143[4] = v151;
        v152 = Concat_54832608(v143, 0);
        org_text = Replace_54838864(v142, "<BTN_R2>+<BTN_DL> or <BTN_DR>", v152, 0);
      }
      else
      {
        if (Equals_54828784(v26[1].monitor, "<BTN_R2> + <BTN_DD>", 0))
        {
          v154 = GetPadToSpriteTag(28684);
          v156 = GetPadToSpriteTag(28677);
          v157 = Concat_54831728(v154, " + ", v156, 0);
          v93 = Replace_54838864(org_text, v26[1].monitor, v157, 0);
          v159 = GetPadToSpriteTag(28684);
          v161 = GetPadToSpriteTag(28677);
          v98 = Concat_54831728(v159, " + ", v161, 0);
          v99 = &"<BTN_R2>+<BTN_DD>";
LABEL_79:
          v100 = *v99;
          v101 = v93;
          goto LABEL_89;
        }
        if (Equals_54828784(v26[1].monitor, "<BTN_AL> or <BTN_D>", 0))
        {
          v162 = Replace_54838864(org_text, "<BTN_AL>", "<sprite name=button_ana_L>", 0);
          v163 = "<sprite name=button_jyuuji>";
          v164 = &"<BTN_D>";
LABEL_106:
          org_text = Replace_54838864(v162, *v164, v163, 0);
          goto LABEL_12;
        }
        if (Equals_54828784(v26[1].monitor, "<BTN_R1>+<BTN_AR>", 0))
        {
          v166 = GetPadToSpriteTag(24587);
          v162 = Replace_54838864(org_text, "<BTN_R1>", v166, 0);
          v163 = "<sprite name=button_ana_R>";
          v164 = &"<BTN_AR>";
          goto LABEL_106;
        }
        if (Equals_54828784(v26[1].monitor, "<BTN_AL>", 0))
        {
          v98 = "<sprite name=button_ana_L>";
          v167 = &"<BTN_AL>";
LABEL_147:
          v100 = *v167;
          v101 = org_text;
          goto LABEL_89;
        }
        if (Equals_54828784(v26[1].monitor, "<BTN_ALU>", 0))
        {
          v98 = "<sprite name=button_ana_L_u>";
          v167 = &"<BTN_ALU>";
          goto LABEL_147;
        }
        if (Equals_54828784(v26[1].monitor, "<BTN_ALD>", 0))
        {
          v98 = "<sprite name=button_ana_L_d>";
          v167 = &"<BTN_ALD>";
          goto LABEL_147;
        }
        if (Equals_54828784(v26[1].monitor, "<BTN_ALL>", 0))
        {
          v98 = "<sprite name=button_ana_L_l>";
          v167 = &"<BTN_ALL>";
          goto LABEL_147;
        }
        if (Equals_54828784(v26[1].monitor, "<BTN_ALR>", 0))
        {
          v98 = "<sprite name=button_ana_L_r>";
          v167 = &"<BTN_ALR>";
          goto LABEL_147;
        }
        if (Equals_54828784(v26[1].monitor, "<BTN_AR>", 0))
        {
          v98 = "<sprite name=button_ana_R>";
          v167 = &"<BTN_AR>";
          goto LABEL_147;
        }
        if (Equals_54828784(v26[1].monitor, "<BTN_ARU>", 0))
        {
          v98 = "<sprite name=button_ana_R_u>";
          v167 = &"<BTN_ARU>";
          goto LABEL_147;
        }
        if (Equals_54828784(v26[1].monitor, "<BTN_ARD>", 0))
        {
          v98 = "<sprite name=button_ana_R_d>";
          v167 = &"<BTN_ARD>";
          goto LABEL_147;
        }
        if (Equals_54828784(v26[1].monitor, "<BTN_ARL>", 0))
        {
          v98 = "<sprite name=button_ana_R_l>";
          v167 = &"<BTN_ARL>";
          goto LABEL_147;
        }
        if (Equals_54828784(v26[1].monitor, "<BTN_ARR>", 0))
        {
          v98 = "<sprite name=button_ana_R_r>";
          v167 = &"<BTN_ARR>";
          goto LABEL_147;
        }
      }
    }
LABEL_12:
    ++v7;
  }
  if (((u8)v8[464] & 1) != 0)
    goto LABEL_15;
LABEL_18:
  *((u8 *)v8 + 3712) = 1;
  if (v7 < btntag_config->_itemtbl->_size)
    goto LABEL_19;
LABEL_148:
  if ((v180 & 1) == 0)
  {
    ConfigPadMap = ConfigGameGetConfigPadMap(4096, 0);
    PadMapToKeyID = dds3PadGetPadMapToKeyID(ConfigPadMap);
    v172 = object___get_Item(keyid_to_btntag, PadMapToKeyID);
    v174 = Replace_54838864(org_text, "<BTN_A>", v172, 0);
    v175 = ConfigGameGetConfigPadMap(4097, 0);
    v176 = dds3PadGetPadMapToKeyID(v175);
    v178 = object___get_Item(keyid_to_btntag, v176);
    return Replace_54838864(v174, "<BTN_B>", v178, 0);
  }
  return org_text;
}

// 0x18c0650
static s32 GetConfigKeyID(s32 tbl_keyid) {
  dds3GlobalWork_t *v8;
  dds3GlobalWork_t *v10;
  dds3GlobalWork_t *v12;
  s32 ConfigPadMap;

  if (tbl_keyid <= 29183)
  {
    if (tbl_keyid != 28929)
    {
      if (tbl_keyid == 28931)
      {
        if (GBWK)
        {
          return SHIWORD(GBWK->config_data[3][10]);
        }
        return 0;
      }
LABEL_36:
      ConfigPadMap = ConfigGameGetConfigPadMap(tbl_keyid, 0);
      return dds3PadGetPadMapToKeyID(ConfigPadMap);
    }
    v10 = GBWK;
    if (v10)
    {
      v10 = GBWK;
      return LOWORD(v10->config_data[3][10]);
    }
    return 0;
  }
  if (tbl_keyid != 29184)
  {
    if (tbl_keyid != 29186)
      goto LABEL_36;
    v8 = GBWK;
    if (v8)
    {
      v8 = GBWK;
      return SHIWORD(v8->config_data[3][11]);
    }
    return 0;
  }
  v12 = GBWK;
  if (!v12)
    return 0;
  v12 = GBWK;
  return LOWORD(v12->config_data[3][11]);
}

// 0x18c0ba0
char *cfgGetBtnTagConfigSingle(char *btntag, char *text_label) {
  s32 v4;
  char v5;
  char *v6;
  char *v7;
  char *v8;
  char *v9;
  char **v10;
  char *monitor;
  void *v13;
  void *itemtbl;
  Il2CppObject *Item;
  Il2CppObject *v16;
  char *v17;
  char *v18;
  s32 ConfigKeyID;
  Il2CppObject *v22;
  char *v23;
  s32 v25;
  char **v27;
  s32 v29;
  Il2CppObject *v31;
  s32 v33;
  s32 klass;
  s32 v37;
  s32 ConfigPadMap;
  s32 PadMapToKeyID;
  Il2CppObject *v44;
  s32 v47;
  s32 v48;
  Il2CppObject *v50;
  s32 v53;
  s32 v54;
  Il2CppObject *v56;
  s32 v59;
  s32 v60;
  Il2CppObject *v62;
  s32 keyb;
  s32 key;
  Il2CppObject *keya;
  char *value;

  value = btntag;
  v4 = 0;
  v5 = 0;
  {
LABEL_12:
    if (v4 >= btntag_config->_itemtbl->_size)
      goto LABEL_67;
    v13 = btntag_config;
    itemtbl = v13->_itemtbl;
    if (itemtbl->_size <= v4)
      goto LABEL_9;
    Item = _get_Item(itemtbl, v4);
    if (Item)
    {
      v16 = Item;
      if (Equals_54828784(text_label, Item[1].klass, 0))
      {
        if (Equals_54828784(v16[1].monitor, "<BTN_ALU> <BTN_ALD> or <BTN_DU> <BTN_DD>", 0))
        {
          v6 = Replace_54838864(btntag, "<BTN_ALU>", "<sprite name=button_ana_L_u>", 0);
          v7 = Replace_54838864(v6, "<BTN_ALD>", "<sprite name=button_ana_L_d>", 0);
          v8 = Replace_54838864(v7, "<BTN_DU>", "<sprite name=button_jyuuji_U>", 0);
          v9 = "<sprite name=button_jyuuji_D>";
          v10 = &"<BTN_DD>";
          goto LABEL_7;
        }
        if (Equals_54828784(v16[1].monitor, "<BTN_ALL> <BTN_ALR> or <BTN_DL> <BTN_DR>", 0))
        {
          v17 = Replace_54838864(btntag, "<BTN_ALL>", "<sprite name=button_ana_L_l>", 0);
          v18 = Replace_54838864(v17, "<BTN_ALR>", "<sprite name=button_ana_L_r>", 0);
          v8 = Replace_54838864(v18, "<BTN_DL>", "<sprite name=button_jyuuji_L>", 0);
          v9 = "<sprite name=button_jyuuji_R>";
          v10 = &"<BTN_DR>";
LABEL_7:
          monitor = *v10;
          goto LABEL_8;
        }
        if (Equals_54828784(v16[1].monitor, "<BTN_X>+<BTN_A>", 0))
        {
          ConfigKeyID = GetConfigKeyID(29186);
          v22 = object___get_Item(keyid_to_btntag, ConfigKeyID);
          v23 = Replace_54838864(btntag, "<BTN_X>", v22, 0);
          v25 = GetConfigKeyID(29184);
          v9 = object___get_Item(keyid_to_btntag, v25);
          v27 = &"<BTN_A>";
          goto LABEL_53;
        }
        if (Equals_54828784(v16[1].monitor, "<BTN_Y>+<BTN_B>", 0))
        {
          v29 = GetConfigKeyID(28931);
          v31 = object___get_Item(keyid_to_btntag, v29);
          v23 = Replace_54838864(btntag, "<BTN_Y>", v31, 0);
          v33 = GetConfigKeyID(28929);
          v9 = object___get_Item(keyid_to_btntag, v33);
          v27 = &"<BTN_B>";
LABEL_53:
          monitor = *v27;
          v8 = v23;
LABEL_8:
          btntag = Replace_54838864(v8, monitor, v9, 0);
          v5 = 1;
          goto LABEL_9;
        }
        if (Equals_54828784(v16[1].monitor, value, 0))
        {
          klass = v16[2].klass;
          if ((u32)(klass + 1) >= 2)
          {
            keyb = v16[2].klass;
            klass = keyb;
            v37 = GetConfigKeyID(klass);
            if (v37 != -1)
            {
              key = v37;
              keya = object___get_Item(keyid_to_btntag, key);
              if (op_Inequality(keya, "", 0))
              {
                monitor = v16[1].monitor;
                v8 = btntag;
                v9 = keya;
                goto LABEL_8;
              }
            }
          }
        }
      }
    }
LABEL_9:
    ++v4;
  }
  goto LABEL_12;
LABEL_67:
  if ((v5 & 1) != 0)
    return btntag;
  if (Equals_54828784(value, "<BTN_A>", 0))
  {
    ConfigPadMap = ConfigGameGetConfigPadMap(4096, 0);
    PadMapToKeyID = dds3PadGetPadMapToKeyID(ConfigPadMap);
    v44 = object___get_Item(keyid_to_btntag, PadMapToKeyID);
    btntag = Replace_54838864(btntag, "<BTN_A>", v44, 0);
  }
  if (Equals_54828784(value, "<BTN_B>", 0))
  {
    v47 = ConfigGameGetConfigPadMap(4097, 0);
    v48 = dds3PadGetPadMapToKeyID(v47);
    v50 = object___get_Item(keyid_to_btntag, v48);
    btntag = Replace_54838864(btntag, "<BTN_B>", v50, 0);
  }
  if (Equals_54828784(value, "<BTN_X>", 0))
  {
    v53 = ConfigGameGetConfigPadMap(4098, 0);
    v54 = dds3PadGetPadMapToKeyID(v53);
    v56 = object___get_Item(keyid_to_btntag, v54);
    btntag = Replace_54838864(btntag, "<BTN_X>", v56, 0);
  }
  if (!Equals_54828784(value, "<BTN_Y>", 0))
    return btntag;
  v59 = ConfigGameGetConfigPadMap(4099, 0);
  v60 = dds3PadGetPadMapToKeyID(v59);
  v62 = object___get_Item(keyid_to_btntag, v60);
  return Replace_54838864(btntag, "<BTN_Y>", v62, 0);
}

// 0x18c0af0
s32 cfgGetPadToKeyID(SDF_PADMAP pad) {
  s32 ConfigPadMap;

  ConfigPadMap = ConfigGameGetConfigPadMap(pad, 0);
  return dds3PadGetPadMapToKeyID(ConfigPadMap);
}

// 0x18c0380
static char *GetPadToSpriteTag(SDF_PADMAP pad) {
  s32 ConfigPadMap;
  s32 PadMapToKeyID;

  ConfigPadMap = ConfigGameGetConfigPadMap(pad, 0);
  PadMapToKeyID = dds3PadGetPadMapToKeyID(ConfigPadMap);
  return object___get_Item(keyid_to_btntag, PadMapToKeyID);
}

// 0x18c05b0
static char *GetKeyid_to_Btntag(s32 keyid) {
  return object___get_Item(keyid_to_btntag, keyid);
}

// 0x18c0640
static char *BtnSpriteCalc(char *sprite_name) {
  return sprite_name;
}

// 0x18c37c0
void cfgBtnReWrite(void) {
  ;
}

// 0x18c37d0
s32 *cfgGetConfigInitTable(s32 tabpos) {
  s32 LanguageTYPE;
  _BOOL4 v6;

  LanguageTYPE = GetLanguageTYPE();
  if (!tabpos)
  {
    v6 = LanguageTYPE == 0;
    config_allInitdate[0][6] = v6;
    return config_allInitdate[tabpos];
  }
  if (tabpos != 3)
  {
    return config_allInitdate[tabpos];
  }
  return ConfigGameGetPriSet(0);
}

// 0x18c3b10
s32 *cfgGetBattleShortCutDefault(s32 _key) {
  return sbtl_shortCutDefault[key];
}

// 0x18c3b80
void cfgSystemToGwCopy(s32 **config_data) {
  s64 i;
  dds3SystemWork_t *SystemWork_local;
  s32 *v6;
  s32 *v7;
  s64 j;
  s32 *v9;
  s64 k;
  s32 *v11;
  s64 m;
  s32 *v13;

  for (i = 32; i != 1056; i += 4)
  {
    v6 = config_data[0];
    SystemWork_local = SystemWork;
    *(u32 *)((char *)&v6->obj.klass + i) = *(u32 *)((char *)&SystemWork_local->config_data_audio->obj.klass + i);
  }
  v7 = config_data[1];
  SystemWork_local = SystemWork;
  v7[0] = SystemWork_local->config_data_game[0];
  for (j = 40; j != 1056; j += 4)
  {
    v9 = config_data[1];
    *(u32 *)((char *)&v9->obj.klass + j) = *(u32 *)((char *)&SystemWork->config_data_game->obj.klass + j);
  }
  for (k = 32; k != 1056; k += 4)
  {
    v11 = config_data[2];
    *(u32 *)((char *)&v11->obj.klass + k) = *(u32 *)((char *)&SystemWork->config_data_graphics->obj.klass + k);
  }
  for (m = 32; m != 1056; m += 4)
  {
    v13 = config_data[3];
    *(u32 *)((char *)&v13->obj.klass + m) = *(u32 *)((char *)&SystemWork->config_data_gamepad->obj.klass + m);
  }
}

// 0x18c3d10
void cfgGwToSystemCopy(s32 **config_data) {
  s64 i;
  dds3SystemWork_t *SystemWork_local;
  s64 v6;
  s64 j;
  s64 k;

  for (i = 32; i != 1056; i += 4)
  {
    SystemWork_local = SystemWork;
    *(u32 *)((char *)&SystemWork_local->config_data_audio->obj.klass + i) = *(u32 *)((char *)&config_data[0]->obj.klass + i);
  }
  SystemWork_local = SystemWork;
  v6 = 40;
  SystemWork_local->config_data_game[0] = config_data[1][0];
  do
  {
    *(u32 *)((char *)&SystemWork->config_data_game->obj.klass + v6) = *(u32 *)((char *)&config_data[1]->obj.klass + v6);
    v6 += 4;
  }
  while (v6 != 1056);
  for (j = 32; j != 1056; j += 4)
  {
    *(u32 *)((char *)&SystemWork->config_data_graphics->obj.klass + j) = *(u32 *)((char *)&config_data[2]->obj.klass + j);
  }
  for (k = 32; k != 1056; k += 4)
  {
    *(u32 *)((char *)&SystemWork->config_data_gamepad->obj.klass + k) = *(u32 *)((char *)&config_data[3]->obj.klass + k);
  }
}

// 0x18c3ea0
void cfgInitGlobalWork(void) {
  s32 **config_data;

  config_data = GBWK->config_data;
  cfgSystemToGwCopy(config_data);
  GBWK->config_data[1][1] = 1;
  GBWK->pd_ver = version;
  cfgInitSbtlShortCut();
  BrightnessChange();
  ContrastChange();
}

// 0x18c4140
void cfgInitSbtlShortCut(void) {
  s32 *v3;
  il2cpp_array_size_t max_length;
  s64 v6;
  s64 v7;
  s64 v8;
  s32 v9;
  s32 *v11;
  il2cpp_array_size_t v12;
  s32 *v14;
  il2cpp_array_size_t v15;
  s32 *v17;
  il2cpp_array_size_t v18;
  s32 *v20;
  il2cpp_array_size_t v21;
  s64 v23;
  s64 v24;
  s64 v25;
  s32 v26;
  s64 v28;
  s64 v29;
  s64 v30;
  s32 v31;
  s64 v33;
  s64 v34;
  s64 v35;
  s32 v36;
  s64 v38;
  s64 v39;
  s64 v40;
  s32 v41;

  v3 = sbtl_shortCutDefault[0];
  max_length = v3->max_length;
  if ((s32)max_length >= 1)
  {
    v6 = 8;
    do
    {
      max_length = v3->max_length;
      v7 = 4 * v6;
      v8 = v6 - 7;
      v9 = *((u32 *)&v3->obj.klass + v6++);
      *(u32 *)((char *)&GBWK->sbtl_short_cut[0]->obj.klass + v7) = v9;
    }
    while (v8 < (s32)max_length);
  }
  v11 = sbtl_shortCutDefault[1];
  v12 = v11->max_length;
  if ((s32)v12 < 1)
  {
    goto LABEL_16;
  }
  v23 = 8;
  do
  {
    v12 = v11->max_length;
    v24 = 4 * v23;
    v25 = v23 - 7;
    v26 = *((u32 *)&v11->obj.klass + v23++);
    *(u32 *)((char *)&GBWK->sbtl_short_cut[1]->obj.klass + v24) = v26;
  }
  while (v25 < (s32)v12);
LABEL_16:
  v14 = sbtl_shortCutDefault[2];
  v15 = v14->max_length;
  if ((s32)v15 < 1)
  {
    goto LABEL_20;
  }
  v28 = 8;
  do
  {
    v15 = v14->max_length;
    v29 = 4 * v28;
    v30 = v28 - 7;
    v31 = *((u32 *)&v14->obj.klass + v28++);
    *(u32 *)((char *)&GBWK->sbtl_short_cut[2]->obj.klass + v29) = v31;
  }
  while (v30 < (s32)v15);
LABEL_20:
  v17 = sbtl_shortCutDefault[3];
  v18 = v17->max_length;
  if ((s32)v18 < 1)
  {
    goto LABEL_24;
  }
  v33 = 8;
  do
  {
    v18 = v17->max_length;
    v34 = 4 * v33;
    v35 = v33 - 7;
    v36 = *((u32 *)&v17->obj.klass + v33++);
    *(u32 *)((char *)&GBWK->sbtl_short_cut[3]->obj.klass + v34) = v36;
  }
  while (v35 < (s32)v18);
LABEL_24:
  v20 = sbtl_shortCutDefault[4];
  v21 = v20->max_length;
  if ((s32)v21 < 1)
    return;
  v38 = 8;
  do
  {
    v21 = v20->max_length;
    v39 = 4 * v38;
    v40 = v38 - 7;
    v41 = *((u32 *)&v20->obj.klass + v38++);
    *(u32 *)((char *)&GBWK->sbtl_short_cut[4]->obj.klass + v39) = v41;
  }
  while (v40 < (s32)v21);
}

// 0x18c4680
s32 cfgChkFlagChange(void) {
  Log("cfg.ChkFlagChangeが呼び出された！！");
  return gConfigChange != 0;
}

// 0x18c4750
void cfgCopyFlagGblToBak(void) {
  s64 v1;
  s32 **gConfigFlagBak_local;
  Il2CppClass *v4;
  Il2CppClass **v5;
  s64 i;
  s32 *v7;

  v1 = 0;
  do
  {
    gConfigFlagBak_local = gConfigFlagBak;
    if (!gConfigFlagBak_local[v1])
    {
      gConfigFlagBak_local = gConfigFlagBak;
      v4 = NewSpecific(s32, 0x100u);
      v5 = &gConfigFlagBak_local->obj.klass + v1;
      v5[4] = v4;
    }
    for (i = 32; i != 1056; i += 4)
    {
      v7 = gConfigFlagBak[v1];
      *(u32 *)((char *)&v7->obj.klass + i) = *(u32 *)((char *)&GBWK->config_data[v1]->obj.klass + i);
    }
    ++v1;
  }
  while (v1 != 6);
  gConfigChange = 0;
}

// 0x18c48f0
void cfgCopyFlagBakToGbl(void) {
  s64 v1;
  s32 *v3;
  s64 i;
  s32 *v6;
  s64 j;
  s32 *v8;
  s64 k;
  s32 *v10;
  s64 m;
  s32 *v12;
  s64 n;
  s32 *v15;

  v1 = 32;
  do
  {
    v3 = GBWK->config_data[0];
    *(u32 *)((char *)&v3->obj.klass + v1) = *(u32 *)((char *)&gConfigFlagBak[0]->obj.klass + v1);
    v1 += 4;
  }
  while (v1 != 1056);
  for (i = 32; i != 1056; i += 4)
  {
    v6 = GBWK->config_data[1];
    *(u32 *)((char *)&v6->obj.klass + i) = *(u32 *)((char *)&gConfigFlagBak[1]->obj.klass + i);
  }
  for (j = 32; j != 1056; j += 4)
  {
    v8 = GBWK->config_data[2];
    *(u32 *)((char *)&v8->obj.klass + j) = *(u32 *)((char *)&gConfigFlagBak[2]->obj.klass + j);
  }
  for (k = 32; k != 1056; k += 4)
  {
    v10 = GBWK->config_data[3];
    *(u32 *)((char *)&v10->obj.klass + k) = *(u32 *)((char *)&gConfigFlagBak[3]->obj.klass + k);
  }
  for (m = 32; m != 1056; m += 4)
  {
    v12 = GBWK->config_data[4];
    *(u32 *)((char *)&v12->obj.klass + m) = *(u32 *)((char *)&gConfigFlagBak[4]->obj.klass + m);
  }
  for (n = 32; n != 1056; n += 4)
  {
    v15 = GBWK->config_data[5];
    *(u32 *)((char *)&v15->obj.klass + n) = *(u32 *)((char *)&gConfigFlagBak[5]->obj.klass + n);
  }
  gConfigChange = 0;
}

// 0x18c4ca0
void cfgSetChange(void) {
  gConfigChange = 1;
  return;
}

// 0x18c4d30
s32 cfgScrCmd_GET_CONFIG_GAME(void) {
  s32 IntPara;
  s64 v2;
  s64 v3;
  s32 v5;

  IntPara = scrGetIntPara(0);
  v2 = 15;
  if (IntPara != 1)
    v2 = 0;
  if (IntPara)
    v3 = v2;
  else
    v3 = 14;
  v5 = GBWK->config_data[1][v3];
  scrSetIntReturnValue(v5);
  return 1;
}

// 0x18c4f10
s32 cfgGetConfigAUDIO(s32 type, s32 *config_data) {
  if (config_data)
    return config_data[type];
  return GBWK->config_data[0][type];
}

// 0x18c4e70
s32 cfgGetConfigGAME(s32 type, s32 *config_data) {
  if (config_data)
    return config_data[type];
  return GBWK->config_data[1][type];
}

// 0x18c4fb0
s32 cfgGetConfigGRAPHICS(s32 type, s32 *config_data) {
  if (config_data)
    return config_data[type];
  return GBWK->config_data[2][type];
}

// 0x18c5050
s32 cfgGetConfigDISPLAY(s32 type, s32 *config_data) {
  return 0;
}

// 0x18c04f0
s32 cfgGetConfigGAMEPAD(s32 type, s32 *config_data) {
  if (config_data)
    return config_data[type];
  if (GBWK)
  {
    config_data = GBWK->config_data[3];
    return config_data[type];
  }
  return 0;
}

// 0x18c5060
s32 cfgGetConfigKEYBOARD(s32 type) {
  return 0;
}

// 0x18c5070
void cfgSetConfigAUDIO(s32 type, s32 val, s32 *config_data) {
  if (config_data)
  {
    config_data[type] = val;
    return;
  }
  GBWK->config_data[0][type] = val;
}

// 0x18c40a0
void cfgSetConfigGAME(s32 type, s32 val, s32 *config_data) {
  if (config_data)
  {
    config_data[type] = val;
    return;
  }
  GBWK->config_data[1][type] = val;
}

// 0x18c5110
void cfgSetConfigGRAPHICS(s32 type, s32 val, s32 *config_data) {
  if (config_data)
  {
    config_data[type] = val;
    return;
  }
  GBWK->config_data[2][type] = val;
}

// 0x18c51b0
void cfgSetConfigDISPLAY(s32 type, s32 val, s32 *config_data) {
  ;
}

// 0x18c51c0
void cfgSetConfigGAMEPAD(s32 type, s32 val, s32 *config_data) {
  if (config_data)
  {
    config_data[type] = val;
    return;
  }
  GBWK->config_data[3][type] = val;
}

// 0x18c5260
void cfgSetConfigKEYBOARD(s32 type, s32 val, s32 *config_data) {
  ;
}
