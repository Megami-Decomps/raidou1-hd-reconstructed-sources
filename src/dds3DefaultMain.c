#include "types.h"
#include "dds3defaultmain.h"
#include "kernel.h"
#include "sdfsystem.h"
#include "sdfth.h"

typedef struct SequenceParameter SequenceParameter;

static bool called;

// 0x229f1d0
s32 main(DDS3_ADMINI_LIST startSequence, SequenceParameter *sequenceParameter) {
  void *v6;

  if (called)
    return 0;
  sdfInit();
  v6 = Allocate(Project_Kernel_dds3KernelMain__KernelMain_d__33);
  v6->__1__state = 0;
  v6->sequenceParameter = sequenceParameter;
  v6->startSequence = startSequence;
  sdfThCreate(v6, 96);
  called = 1;
  return 0;
}
