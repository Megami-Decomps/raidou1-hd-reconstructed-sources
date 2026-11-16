#include "types.h"
#include "localize.h"

#define KEY_event_msg "event_msg."

typedef struct EvtMsgDat EvtMsgDat;
typedef struct UIfontSize UIfontSize;

struct EvtMsgDat {
    char *key;
    char *filename;
    void *data;
};

void *fileList;
static void *dataDic;
static LanguageID id;
static char *tag;
static char *appendix;
static UIfontSize *uifontsize_tbl;

static void Remove(s32 index);
static char *eStr(s32 eventno);

// 0x1cf3a00
LanguageID GetLanguageID(void) {
  char *Desired;
  s32 v4;
  bool v5;

  if (id < 5)
    goto LABEL_4;
  Desired = GetDesired(0);
  if (op_Equality(Desired, "en-US", 0))
  {
    v4 = 0;
    goto LABEL_11;
  }
  if (op_Equality(Desired, "fr", 0))
  {
    v4 = 1;
  }
  else if (op_Equality(Desired, "it", 0))
  {
    v4 = 2;
  }
  else if (op_Equality(Desired, "de", 0))
  {
    v4 = 3;
  }
  else
  {
    v5 = op_Equality(Desired, "es", 0);
    if (v5)
      v4 = 4;
    else
      v4 = 0;
  }
LABEL_11:
  id = v4;
  return id;
LABEL_4:
  return id;
}

// 0x1cf3c10
LanguageTYPE GetLanguageTYPE(void) {
  GetLanguageID();
  return 0;
}

// 0x1cf3c90
char *GetLanguageTag(void) {
  char *v3;
  System_Enum_o v5;

  if (!tag)
  {
    *(u32 *)&v5.System_ValueType_Fields = GetLanguageID();
    v5.klass = (System_Enum_c *)LanguageID;
    v5.monitor = -1;
    v3 = ToString(&v5, 0);
    tag = v3;
    return tag;
  }
  return tag;
}

// 0x1cf3da0
char *GetAppendix(void) {
  char *LanguageTag;
  char *v4;

  if (!appendix)
  {
    LanguageTag = GetLanguageTag();
    v4 = Concat_54766928("_", LanguageTag, 0);
    appendix = v4;
    return appendix;
  }
  return appendix;
}

// 0x1cf3ea0
s32 GetLanguage(void) {
  s32 result;

  result = GetLanguageID();
  if ((u32)(result - 1) >= 4)
    return 0;
  return result;
}

// 0x1cf3f00
void LoadDefault(void *list) {
  Il2CppObject *current;
  System_Collections_Generic_List_Enumerator_T__o v5;

  memset(&v5, 0, sizeof(v5));
  _GetEnumerator(&v5, list);
  while (_MoveNext(&v5))
  {
    current = v5._current;
    LoadLocalizeText();
  }
  _Dispose(&v5);
}

// 0x1cf4060
void LoadLocalizeText(void *data) {
  __int128 v4;
  Il2CppObject *current;
  Il2CppClass *klass;
  System_Collections_Generic_List_Enumerator_T__o v10;
  System_Collections_Generic_List_Enumerator_T__o v11;

  if (!op_Inequality(data, 0, 0))
    return;
  _GetEnumerator(&v10, data->_TextMsgData);
  v4 = *(_OWORD *)&v10._list;
  v10._list = 0;
  *(u64 *)&v10._index = &v11;
  v11._current = v10._current;
  *(_OWORD *)&v11._list = v4;
  while (_MoveNext(&v11))
  {
    current = v11._current;
    klass = v11._current[1].klass;
    if (klass && SLODWORD(klass->_1.name) >= 1)
    {
      klass = current[1].klass;
      if (object___ContainsKey(dataDic, klass))
      {
        object___Remove(dataDic, current[1].klass);
      }
      object___Add(dataDic, current[1].klass, current[1].monitor);
    }
  }
  _Dispose(&v11);
}

// 0x1cf4300
void LoadLocalizeText_2(char *key, char *filename) {
  void *Ctrl_k__BackingField;
  char *Appendix;
  char *v13;
  void *Asset;
  s64 naturalAligment;
  void *v16;
  void *fileList_local;
  u64 *v20;
  s32 size;
  EvtMsgDat *items;
  __int128 v23;
  char *v24;
  const MethodInfo_2EEBD00 *v26;
  EvtMsgDat target;
  EvtMsgDat v28;

  if (!IsLoad(Dependent, key, 0))
    return;
  if ((ContainsFileName(filename) & 0x80000000) == 0)
    return;
  Ctrl_k__BackingField = _Ctrl_k__BackingField;
  Appendix = GetAppendix();
  v13 = Concat_54766928(filename, Appendix, 0);
  Asset = LoadAsset(Ctrl_k__BackingField, key, v13, 0);
  {
    v16 = 0;
    goto LABEL_18;
  }
  if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == TextMsgData)
    v16 = Asset;
  else
    v16 = 0;
LABEL_18:
  if (!op_Inequality(v16, 0, 0))
    return;
  fileList_local = fileList;
  target.data = 0;
  *(_OWORD *)&target.key = key;
  target.filename = filename;
  target.data = (void *)v16;
  v20 = Method_System_Collections_Generic_List_Localize_EvtMsgDat__Add__;
  size = fileList_local->_size;
  ++fileList_local->_version;
  items = fileList_local->_items;
  if ((u32)size >= LODWORD(items->max_length))
  {
    v26 = *(const MethodInfo_2EEBD00 **)(*(u64 *)(v20[4] + 192) + 112);
    v28 = target;
    _AddWithResize(fileList_local, &v28, v26);
  }
  else
  {
    v23 = *(_OWORD *)&target.key;
    fileList_local->_size = size + 1;
    v24 = (char *)items + 24 * size;
    *((u64 *)v24 + 6) = target.data;
    *((_OWORD *)v24 + 2) = v23;
  }
  LoadLocalizeText();
}

// 0x1cf47f0
void LoadLocalizeText_3(char *key) {
  char *AllAssetNames;
  char *v6;
  s64 v7;
  char **m_Items;
  char *v9;
  char *FileNameWithoutExtension;
  char *v12;

  if (!IsLoad(Dependent, key, 0))
    return;
  AllAssetNames = GetAllAssetNames(_Ctrl_k__BackingField, key, 0);
  if (SLODWORD(AllAssetNames->max_length) >= 1)
  {
    v6 = AllAssetNames;
    v7 = 0;
    m_Items = AllAssetNames;
    do
    {
      v9 = m_Items[v7];
      FileNameWithoutExtension = GetFileNameWithoutExtension(v9, 0);
      v12 = Substring_54838176(FileNameWithoutExtension, 0, FileNameWithoutExtension->_stringLength - 3, 0);
      LoadLocalizeText_2(key, v12);
      ++v7;
    }
    while (v7 < SLODWORD(v6->max_length));
  }
}

// 0x1cf49c0
static void Remove(s32 index) {
  Il2CppObject *current;
  s64 v5;
  EvtMsgDat v8;
  System_Collections_Generic_List_Enumerator_T__o v9;

  memset(&v9, 0, sizeof(v9));
  if ((index & 0x80000000) == 0)
  {
    _get_Item(&v8, fileList, index);
    _GetEnumerator(&v9, v8.data->_TextMsgData);
    v8.key = 0;
    v8.filename = &v9;
    while (_MoveNext(&v9))
    {
      current = v9._current;
      v5 = *(s64 *)((char *)&v9._current->klass + (u64)sub_10);
      if (v5 && *(s32 *)(v5 + 16) >= 1)
      {
        v5 = *(u64 *)((char *)sub_10 + (u64)current);
        object___Remove(dataDic, v5);
      }
    }
    _Dispose(&v9);
    _RemoveAt(fileList, index);
  }
}

// 0x1cf4be0
void Remove_2(char *filename) {
}

// 0x1cf4c70
void RemoveKey(char *key) {
  s32 size;
  EvtMsgDat a;

  size = fileList->_size;
  if (size - 1 < 0)
    return;
  goto LABEL_10;
  do
  {
LABEL_10:
    _get_Item(&a, fileList, --size);
    if (op_Equality(a.key, key, 0))
    {
      Remove(size);
    }
  }
  while (size > 0);
}

// 0x1ce4660
char *GetLocalizeText(char *ID, bool label) {
  char *v4;
  char *v5;
  char **v8;
  Il2CppObject *value;

  value = 0;
  if (!ID)
    return Empty;
  if (ID->_stringLength < 1)
    return Empty;
  v4 = Replace_54838864(ID, "<", Empty, 0);
  v5 = Replace_54838864(v4, ">", Empty, 0);
  if (Equals_54828848(v5, "nulldata", 5, 0))
    return Empty;
  if (!object___TryGetValue(dataDic, v5, &value))
  {
    v8 = &"(not found)";
    return Concat_54766928(v5, *v8, 0);
  }
  if (op_Equality(value, "null", 0) || op_Equality(value, "NULL", 0))
  {
    return Empty;
  }
  if (op_Equality(value, Empty, 0))
  {
    v8 = &"(no data)";
    return Concat_54766928(v5, *v8, 0);
  }
  return value;
}

// 0x1cf4da0
bool ContainsLabel(char *ID) {
  char *v3;
  Il2CppObject *v4;
  Il2CppObject *value;

  value = 0;
  v3 = Replace_54838864(ID, "<", Empty, 0);
  v4 = Replace_54838864(v3, ">", Empty, 0);
  return object___TryGetValue(dataDic, v4, &value)
      && !op_Equality(value, "null", 0)
      && !op_Equality(value, "NULL", 0);
}

// 0x1cf4660
s32 ContainsFileName(char *name) {
  Il2CppObject *v3;
  char *Appendix;
  char *v6;
  void *v8;

  v3 = Allocate(Project_Localize___c__DisplayClass20_0);
  _ctor(v3, 0);
  Appendix = GetAppendix();
  v6 = Replace_54838864(name, Appendix, "", 0);
  v3[1].klass = v6;
  v8 = Allocate(System_Predicate_Localize_EvtMsgDat_);
  __ctor(v8, v3, Method_Project_Localize___c__DisplayClass20_0__ContainsFileName_b__0__, 0);
  return _FindIndex(fileList, v8);
}

// 0x1cf4f30
s32 ContainsKeyName(char *key) {
  Il2CppObject *v3;
  void *v6;

  v3 = Allocate(Project_Localize___c__DisplayClass21_0);
  _ctor(v3, 0);
  v3[1].klass = key;
  v6 = Allocate(System_Predicate_Localize_EvtMsgDat_);
  __ctor(v6, v3, Method_Project_Localize___c__DisplayClass21_0__ContainsKeyName_b__0__, 0);
  return _FindIndex(fileList, v6);
}

// 0x1cf5050
void *GetList(void) {
  return fileList;
}

// 0x1cf50d0
static char *eStr(s32 eventno) {
  s32 v3;
  char *v5;
  s32 v7;

  v3 = eventno / 10;
  if (eventno == 812 || eventno == 816)
    v3 = 66;
  if (eventno == 663)
    v3 = 62;
  v7 = v3;
  v5 = ToString_55996800((s32)&v7, "d2", 0);
  return Concat_54831728("E", v5, "X", 0);
}

// 0x1cf51b0
void LoadPM1LocalizeText(s32 eventno) {
  s32 v5;
  char *v7;
  char *v8;
  s32 v10;

  Load(Dependent, "event_msg.", "event_msg.");
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  v5 = eventno / 10;
  if (eventno == 812 || eventno == 816)
    v5 = 66;
  if (eventno == 663)
    v5 = 62;
  v10 = v5;
  v7 = ToString_55996800((s32)&v10, "d2", 0);
  v8 = Concat_54831728("E", v7, "X", 0);
  LoadLocalizeText_2("event_msg.", v8);
  Unload(Dependent, "event_msg.", 0);
}

// 0x1cf53a0
void RemovePM1LocalizeText(s32 eventno) {
  s32 v3;
  char *v5;
  char *v7;
  s32 v8;
  s32 v10;

  v3 = eventno / 10;
  if (eventno == 812 || eventno == 816)
    v3 = 66;
  if (eventno == 663)
    v3 = 62;
  v10 = v3;
  v5 = ToString_55996800((s32)&v10, "d2", 0);
  v7 = Concat_54831728("E", v5, "X", 0);
  v8 = ContainsFileName(v7);
  Remove(v8);
}

// 0x1cf5500
void UIFontSizeInit(void) {
  void *Asset;
  s64 naturalAligment;
  void *v5;
  s32 Length;
  UIfontSize *v7;
  s64 v10;
  s64 v11;
  s64 v12;
  UIfontSize *uifontsize_tbl_local;
  UIfontSize *FontSizeTbl;
  UIfontSize *v16;

  Asset = LoadAsset(_Ctrl_k__BackingField, "common", "ui_fontsize", 0);
  {
    if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_FontSizeTbl)
      v5 = Asset;
    else
      v5 = 0;
  }
  else
  {
    v5 = 0;
  }
  Length = GetLength(v5, 0);
  v7 = NewSpecific(UIfontSize, Length);
  uifontsize_tbl = v7;
  if (Length < 1)
    return;
  v10 = 0;
  v11 = Length;
  v12 = 32;
  do
  {
    uifontsize_tbl_local = uifontsize_tbl;
    FontSizeTbl = GetFontSizeTbl(v5, v10, 0);
    v16 = FontSizeTbl;
    *(Il2CppClass **)((char *)&uifontsize_tbl_local->obj.klass + v12) = v16;
    ++v10;
    v12 += 8;
  }
  while (v11 != v10);
}

// 0x1cf5760
UIfontSize *GetUIfontSize(s32 id, s32 all_lang, s32 type_lang) {
  UIfontSize *uifontsize_tbl_local;
  s64 i;
  UIfontSize *v11;
  s32 v12;
  s32 v13;

  uifontsize_tbl_local = (UIfontSize *)uifontsize_tbl;
  if (!uifontsize_tbl_local)
    return uifontsize_tbl_local;
  for (i = 4; ; ++i)
  {
    v11 = uifontsize_tbl;
    if (i - 4 >= SLODWORD(v11->max_length))
      return 0;
    v12 = *(u32 *)(*((u64 *)&v11->obj.klass + i) + 20);
    v13 = v12 - 1000;
    if (v12 < 1000)
    {
      if (v12 != all_lang)
        continue;
      goto LABEL_19;
    }
    if (v13 != type_lang)
      continue;
LABEL_19:
    uifontsize_tbl_local = *((UIfontSize *)&uifontsize_tbl->obj.klass + i);
    if (uifontsize_tbl_local->id == id)
      break;
  }
  return uifontsize_tbl_local;
}
