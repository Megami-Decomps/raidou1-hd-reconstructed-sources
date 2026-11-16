#include "types.h"
#include "dds3assert.h"
#include "sdfassert.h"

static bool isFirst;

// 0x1d533a0
void dds3Disp(char *condition, char *stackTrace) {
  void *static_fields;
  void *Instance_k__BackingField;
  void *Message;
  void *Font;
  void *v13;
  void *v14;
  void *v15;
  char *v16;

  if (!isFirst)
    return;
  Instance_k__BackingField = static_fields;
  if (!op_Inequality(Instance_k__BackingField, 0, 0))
    return;
  SetDisp(ctrl, 1, 0);
  Message = get_Message(ctrl, 0);
  Font = GetFont(_Instance_k__BackingField, "BasicFont", 0);
  set_font(Message, Font, 0);
  v13 = get_Message(ctrl, 0);
  set_fontSize(v13, 28.0, 0);
  v14 = get_Message(ctrl, 0);
  set_parseCtrlCharacters(v14, 0, 0);
  v15 = get_Message(ctrl, 0);
  v16 = Concat_54831728(condition, "\n\n", stackTrace, 0);
  (v15->klass->vtable._66_set_text.methodPtr)(v15, v16, v15->klass->vtable._66_set_text.method);
  isFirst = 0;
}

// 0x1d53750
void dds3InitDisp(void) {
  sdfAssertFunc_t v1;

  v1 = Allocate(sdfAssertFunc_t);
  _ctor(v1, 0, Method_Project_dds3Assert_Disp__, 0);
  sdfSetFunc(v1);
}
