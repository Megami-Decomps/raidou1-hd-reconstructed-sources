#include "types.h"
#include "itf.h"
#include "localize.h"
#include "wordwrap.h"

static s32 MAXLINE;
static s32 MAXWIDTH;
static s32 LINE_NORMAL;
static s32 WIDTH_NORMAL;
static f32 SET_W_EFIGS;
static f32 SET_W_AS;
static f32 SET_W_JA;
static s32 line;
static void *MsgText;
static s32 line_max;
static s32 width_max;
static void *MessMeshPro;
static void *MeshPro;
static f32 textWidth;
static f32 MessWidth;
static f32 ZensyoWidth;
static bool NameMasageflag;

static s32 _append_text(char *text, s32 num, bool spc);
static s32 _isTag(char *message, s32 *index, s32 *len);
static char *TextTagUndo(char *txt);

// 0x1c968a0
void InitializeWordwrap(void *text) {
  f32 SET_W_EFIGS_local;
  s32 LanguageTYPE;
  struct Wordwrap *v9;

  SET_W_EFIGS_local = SET_W_EFIGS;
  LanguageTYPE = GetLanguageTYPE();
  if (!LanguageTYPE)
  {
    SET_W_EFIGS_local = SET_W_EFIGS;
    goto LABEL_24;
  }
  if (LanguageTYPE == 1)
  {
    SET_W_EFIGS_local = SET_W_AS;
  }
  else if (LanguageTYPE == 2)
  {
    SET_W_EFIGS_local = SET_W_JA;
  }
  else
  {
  }
LABEL_24:
  MessMeshPro = text;
  v9 = ((char *)v9 + 48);
  SET_W_AS = SET_W_EFIGS_local;
}

// 0x1c96a20
char *ConvertNBSP(char *text) {
  GetLanguage();
  if ((u32)(GetLanguageTYPE() - 1) >= 2)
    return Replace_54838864(text, " ", " ", 0);
  else
    return text;
}

// 0x1c96af0
char *Convert(char *text, bool spc, s32 SetLine, f32 SetWidth) {
  char *v10;
  u16 *v11;
  char *v12;
  s64 v21;
  char *v22;
  char *v23;
  s32 stringLength;
  char *v26;
  s32 isTag;
  s32 v29;
  char *v30;
  char *v32;
  s32 v33;
  s32 len;
  s32 index;

  GetLanguage();
  if ((u32)(GetLanguageTYPE() - 1) < 2 || IsNullOrEmpty(text, 0))
    return text;
  index = 0;
  v10 = Replace_54838864(text, "\n", "<BR>", 0);
  v11 = NewSpecific(char, 1u);
  v11[0] = 32;
  v12 = Split_54841536(v10, v11, 0);
  len = 0;
  line = 0;
  if ((SetLine & 0x80000000) != 0)
  {
    line_max = LINE_NORMAL;
    goto LABEL_12;
  }
  line_max = SetLine;
  goto LABEL_12;
LABEL_23:
  goto LABEL_25;
LABEL_12:
  width_max = WIDTH_NORMAL;
  if (SetWidth >= 0.0)
    goto LABEL_23;
  SetWidth = MessWidth;
LABEL_25:
  textWidth = SetWidth;
  MeshPro = MessMeshPro;
  Clear(MsgText);
  if (SLODWORD(v12->max_length) >= 1)
  {
    v21 = 0;
    do
    {
      v22 = v12[v21];
      v23 = ConvertNBSP(v22);
LABEL_32:
      stringLength = v23->_stringLength;
      v26 = v23;
      index = 0;
      while (1)
      {
        isTag = _isTag(v26, &index, &len);
        if (!isTag)
          break;
        if (isTag == 2)
        {
          v29 = index;
          v30 = Substring_54838176(v26, 0, index - 4, 0);
          v32 = Concat_54766928(v30, "\n", 0);
          v33 = v30->_stringLength;
          if (_append_text(v32, v33 + 1, 0) != 1)
          {
            v23 = Substring_54838176(v26, v29, v26->_stringLength - v29, 0);
            goto LABEL_32;
          }
          break;
        }
        stringLength -= len;
      }
      if (_append_text(v26, stringLength, 1) == 1)
        break;
      ++v21;
    }
    while (v21 < SLODWORD(v12->max_length));
  }
  if (!get_Length(MsgText, 0) && spc)
  {
    Append_56602800(MsgText, " ", 0);
  }
  NameMasageflag = 0;
  Replace_56644208(MsgText, 0xFF1Cu, 0x3Cu, 0);
  Replace_56644208(MsgText, 0xFF1Eu, 0x3Eu, 0);
  return ((char *(void *, const MethodInfo *))MsgText->klass->vtable._3_ToString.methodPtr)(MsgText, MsgText->klass->vtable._3_ToString.method);
}

// 0x1c97470
static s32 _append_text(char *text, s32 num, bool spc) {
  char *v5;
  char *v6;
  char *v7;
  char *v8;
  char *v9;
  char *v10;
  char *v11;
  char *v12;
  char *v13;
  char *v14;
  char *v15;
  char *v16;
  char *v17;
  char *v18;
  char *v19;
  char *v20;
  char *v21;
  char *v22;
  char *v23;
  char *v24;
  s32 v25;
  char *v26;
  char *v27;
  s32 result;
  void *v33;
  char *v34;
  s32 v38;
  char **v40;
  f32 x;

  v5 = TextTagUndo(text);
  v6 = (MsgText->klass->vtable._3_ToString.methodPtr)(MsgText, MsgText->klass->vtable._3_ToString.method);
  v7 = Concat_54766928(v6, v5, 0);
  v8 = Replace(v7, "<BTN_", "＜BTN_", 0);
  v9 = Replace(v8, "<BST_", "＜BST_", 0);
  v10 = Replace(v9, "<ICN_", "＜ICN_", 0);
  v11 = Replace(v10, "<ITM_", "＜ITM_", 0);
  v12 = Replace(v11, "<SKL_", "＜SKL_", 0);
  v13 = Replace(v12, "<DEP_", "＜DEP_", 0);
  v14 = Replace(v13, "<MNE_", "＜MNE_", 0);
  v15 = Replace(v14, "<RAI_", "＜RAI_", 0);
  v16 = Replace(v15, "<[^>]*?>", "", 0);
  v17 = Replace(v16, "＜BTN_", "<BTN_", 0);
  v18 = Replace(v17, "＜BST_", "<BST_", 0);
  v19 = Replace(v18, "＜ICN_", "<ICN_", 0);
  v20 = Replace(v19, "＜ITM_", "<ITM_", 0);
  v21 = Replace(v20, "＜SKL_", "<SKL_", 0);
  v22 = Replace(v21, "＜DEP_", "<DEP_", 0);
  v23 = Replace(v22, "＜MNE_", "<MNE_", 0);
  v24 = Replace(v23, "＜RAI_", "<RAI_", 0);
  v25 = num;
  v26 = v24;
  if (!num)
    v25 = !IsNullOrEmpty(v24, 0);
  v27 = itfTextBtnConvert(v26, 0);
  x = GetPreferredValues_60221776(MeshPro, v27, 0).x;
  if (x >= textWidth)
  {
    Append_56602800(MsgText, "\n", 0);
    v38 = line + 1;
    line = v38;
    if (v38 == line_max)
      return 1;
    v40 = &" ";
    if (!spc)
      v40 = &"";
    v34 = Concat_54766928(v5, *v40, 0);
    v33 = MsgText;
    goto LABEL_30;
  }
  Append_56602800(MsgText, v5, 0);
  result = 0;
  if (v25 && spc)
  {
    v33 = MsgText;
    v34 = " ";
LABEL_30:
    Append_56602800(v33, v34, 0);
    return 0;
  }
  return result;
}

// 0x1c96f80
static s32 _isTag(char *message, s32 *index, s32 *len) {
  s32 v7;
  s32 v8;
  s32 v9;
  s32 v10;
  s32 v11;
  char *v12;
  char *v13;
  s32 v14;
  s32 v15;
  s32 result;

  *len = 0;
  v7 = IndexOf_54850576(message, 0x3Cu, *index, 0);
  if (v7 == -1)
    return 0;
  v8 = v7;
  result = -1;
  v9 = IndexOf_54850576(message, 0x3Eu, v7, 0);
  if (v9 == -1)
    return 0;
  v10 = v9;
  if (v9 - *index - 3 < 0)
    return 0;
  v11 = v9 - v8 - 3;
  if (v11 < 0)
    return 0;
  v12 = Substring_54838176(message, v8 + 3, v11, 0);
  v13 = Substring_54838176(message, v8, 3, 0);
  if (Equals_54828848(v13, "<FO", 5, 0))
  {
    v14 = 0;
  }
  else if (Equals_54828848(v13, "<CO", 5, 0))
  {
    v14 = 1;
  }
  else if (Equals_54828848(v13, "<TP", 5, 0))
  {
    v14 = 2;
  }
  else if (Equals_54828848(v13, "<SP", 5, 0))
  {
    v14 = 3;
  }
  else if (Equals_54828848(v13, "<WA", 5, 0))
  {
    v14 = 4;
  }
  else
  {
    v14 = 5;
    if (!Equals_54828848(v13, "<RE", 5, 0))
    {
      if (Equals_54828848(v13, "<NW", 5, 0))
      {
        v14 = 6;
      }
      else if (Equals_54828848(v13, "<AD", 5, 0))
      {
        v14 = 7;
      }
      else if (Equals_54828848(v13, "<KU", 5, 0))
      {
        v14 = 8;
      }
      else if (Equals_54828848(v13, "<BR", 5, 0))
      {
        v14 = 9;
      }
      else if (Equals_54828848(v13, "<li", 5, 0))
      {
        v14 = 10;
      }
      else if (Equals_54828848(v13, "<mw", 5, 0))
      {
        v14 = 11;
      }
      else if (Equals_54828848(v13, "<IT", 5, 0))
      {
        v14 = 12;
      }
      else if (Equals_54828848(v13, "<NB", 5, 0))
      {
        v14 = 13;
      }
      else if (Equals_54828848(v13, "<BT", 5, 0))
      {
        v14 = 14;
      }
      else if (Equals_54828848(v13, "<BS", 5, 0))
      {
        v14 = 15;
      }
      else if (Equals_54828848(v13, "<IC", 5, 0))
      {
        v14 = 16;
      }
      else
      {
        v14 = -1;
      }
    }
  }
  if (TryParse(v12, &result, 0))
  {
    if (v14 < 4)
    {
      v15 = v10 + 1;
      *index = v10 + 1;
      if (v14 == -1)
        return 0;
      goto LABEL_48;
    }
    if ((u32)v14 < 0xA)
      return 0;
  }
  else
  {
    if (v14 < 0)
    {
      *index = v10 + 1;
      return 0;
    }
    if ((u32)v14 <= 3)
      return 0;
  }
  v15 = v10 + 1;
  *index = v10 + 1;
LABEL_48:
  *len = v15 - v8;
  if (v14 == 9)
    return 2;
  else
    return 1;
}

// 0x1c979d0
static char *TextTagUndo(char *txt) {
  s32 isTag;
  s32 stringLength;
  char *v7;
  s32 v9;
  char *v11;
  char *v13;
  char *v14;
  char *v15;
  char *v16;
  char *v17;
  char *v18;
  char *v19;
  char *v20;
  char *v21;
  char *v22;
  s32 len;
  s32 index;

  index = 0;
  isTag = _isTag(txt, &index, &len);
  stringLength = txt->_stringLength;
  if (isTag)
  {
    if (stringLength >= 5 && get_Chars(txt, 4, 0) == 60)
    {
      NameMasageflag = 0;
      v7 = Replace(txt, "<", "＜", 0);
      txt = Replace(v7, ">", "＞", 0);
      NameMasageflag = 1;
    }
  }
  else if (stringLength >= 1)
  {
    v9 = 0;
    do
    {
      if (get_Chars(txt, v9, 0) == 60)
      {
        NameMasageflag = 0;
        v11 = Replace(txt, "<", "＜", 0);
        txt = Replace(v11, ">", "＞", 0);
        NameMasageflag = 1;
      }
      ++v9;
    }
    while (v9 < txt->_stringLength);
  }
  v13 = Replace(txt, "＜FO＞", "<FO>", 0);
  v14 = Replace(v13, "＜TP＞", "<TP>", 0);
  v15 = Replace(v14, "＜WA＞", "<WA>", 0);
  v16 = Replace(v15, "＜RE＞", "<RE>", 0);
  v17 = Replace(v16, "＜NW＞", "<NW>", 0);
  v18 = Replace(v17, "＜AD＞", "<AD>", 0);
  v19 = Replace(v18, "＜BR＞", "<BR>", 0);
  v20 = Replace(v19, "＜KU＞", "<KU>", 0);
  v21 = Replace(v20, "＜CO", "<CO", 0);
  v22 = Replace(v21, "＜SP", "<SP", 0);
  return Replace(v22, "＞", ">", 0);
}
