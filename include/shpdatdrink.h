#pragma once
#include "types.h"

typedef struct tagSHP_GUEST_WK tagSHP_GUEST_WK;

s32 shpCnvIdChar2Guest(s32 a_charId);
tagSHP_GUEST_WK *shpGetAddrGuestWork(s32 a_guestId);
s32 shpDrinkGetGiveProcedure(s32 a_charId, s32 a_drinkId);
s32 shpDrinkGive(s32 a_charId, s32 a_drinkId);
