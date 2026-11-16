#include "types.h"
#include "libsdf.h"
#include "sdfth.h"
#include "sdfvsync.h"

static void *list;

static void Update(void);

// 0x225f320
void sdfThCreate(void *aStartFunc, SDF_TH_PRIO aPrio) {
  Item *v5;
  void *v6;
  void *v7;
  u64 *v8;
  s64 size;
  void *items;
  Il2CppClass **v11;
  s32 v12;

  v5 = Allocate(Item);
  v6 = Allocate(System_Collections_Generic_List_IEnumerator_);
  __ctor(v6);
  v5->func = v6;
  v5->enable = 1;
  _ctor(v5, 0);
  v7 = v5->func;
  v8 = Method_System_Collections_Generic_List_IEnumerator__Add__;
  size = v7->_size;
  ++v7->_version;
  items = v7->_items;
  if ((u32)size >= LODWORD(items->max_length))
  {
    _AddWithResize(v7, aStartFunc, *(const MethodInfo_2DFC660 **)(*(u64 *)(v8[4] + 192) + 112));
  }
  else
  {
    v7->_size = size + 1;
    v11 = &items->obj.klass + size;
    v11[4] = aStartFunc;
  }
  v5->prio = aPrio;
  v12 = 0;
  while (1)
  {
    if (v12 >= list->_size)
      break;
    if (SLODWORD(_get_Item(list, v12)[1].monitor) <= aPrio)
    {
      break;
    }
    ++v12;
  }
  _Insert(list, v12, v5);
}

// 0x2268a80
void *sdfThSleep(s32 aCycle) {
  void *v3;

  v3 = Allocate(Project_libsdf_sdfTh__Sleep_d__4);
  v3->__1__state = 0;
  v3->aCycle = aCycle;
  return v3;
}

// 0x2268510
void sdfThInit(void) {
  void *v1;
  void *v4;

  v1 = Allocate(System_Action);
  _ctor(v1, 0, Method_Project_libsdf_sdfTh_Update__, 0);
  Add(v1, 0);
  Count = 0;
  v4 = sdfThread();
  sdfThCreate(v4, 62);
}

// 0x2269240
static void Update(void) {
  s32 v1;
  bool v4;
  Il2CppObject *Item;
  Il2CppObject *v7;
  void *klass;
  s32 v9;
  Il2CppObject *v10;
  Il2CppClass *v11;
  Il2CppObject *v12;
  s64 v13;
  s32 *p_offset;
  s64 v15;
  char v16;
  void *v17;
  Il2CppObject *v18;
  Il2CppClass *v19;
  Il2CppObject *v20;
  s64 v21;
  System_Collections_IEnumerator_c **v22;
  s64 v23;
  void *v24;
  Il2CppObject *Interface;
  void *v26;
  u64 *v27;
  s64 size;
  void *items;
  Il2CppClass **v30;

  sdfBegin();
  do
  {
    v1 = list->_size - 1;
    if (v1 < 0)
      goto LABEL_11;
    do
    {
      Item = _get_Item(list, v1);
      if (BYTE4(Item[1].monitor))
      {
        v7 = Item;
        do
        {
          klass = v7[1].klass;
          v9 = klass->_size - 1;
          v10 = _get_Item(klass, v9);
          v11 = v10->klass;
          v12 = v10;
          v13 = *(u16 *)&v10->klass->_2.rank;
          if (*(u16 *)&v10->klass->_2.rank)
          {
            p_offset = &v11->_1.interfaceOffsets->offset;
            while (*((System_Collections_IEnumerator_c **)p_offset - 1) != System_Collections_IEnumerator)
            {
              p_offset += 4;
              if (!--v13)
                goto LABEL_29;
            }
            v15 = &v11->vtable[*p_offset];
          }
          else
          {
LABEL_29:
            v15 = sub_4227F4(v10, System_Collections_IEnumerator, 0);
          }
          v16 = (*v15)(v12, *(u64 *)(v15 + 8));
          v17 = v7[1].klass;
          if ((v16 & 1) != 0)
          {
            v18 = _get_Item(v17, v9);
            v19 = v18->klass;
            v20 = v18;
            v21 = *(u16 *)&v18->klass->_2.rank;
            if (*(u16 *)&v18->klass->_2.rank)
            {
              v22 = &v19->_1.interfaceOffsets->offset;
              while (*(v22 - 1) != System_Collections_IEnumerator)
              {
                v22 += 2;
                if (!--v21)
                  goto LABEL_36;
              }
              v23 = &v19->vtable[*(u32 *)v22 + 1];
            }
            else
            {
LABEL_36:
              v23 = sub_4227F4(v18, System_Collections_IEnumerator, 1u);
            }
            v24 = (*v23)(v20, *(u64 *)(v23 + 8));
            Interface = QueryInterface(v24, System_Collections_IEnumerator);
            if (!Interface)
              break;
            v26 = v7[1].klass;
            v27 = Method_System_Collections_Generic_List_IEnumerator__Add__;
            size = v26->_size;
            ++v26->_version;
            items = v26->_items;
            if ((u32)size >= LODWORD(items->max_length))
            {
              _AddWithResize(v26, Interface, *(const MethodInfo_2DFC660 **)(*(u64 *)(v27[4] + 192) + 112));
            }
            else
            {
              v26->_size = size + 1;
              v30 = &items->obj.klass + size;
              v30[4] = Interface;
            }
          }
          else
          {
            _RemoveAt(v17, v9);
            if (!v9)
            {
              _RemoveAt(list, v1);
              break;
            }
          }
        }
        while (BYTE4(v7[1].monitor));
      }
      v4 = __OFSUB__(v1--, 1);
    }
    while (v1 < 0 == v4);
LABEL_11:
    sdfStep();
    continue;
  }
  while (drawSkip);
}
