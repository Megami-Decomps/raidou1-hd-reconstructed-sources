#pragma once
#include "types.h"
#include "kernel.h"

typedef struct SequenceParameter SequenceParameter;

s32 main(DDS3_ADMINI_LIST startSequence, SequenceParameter *sequenceParameter);
