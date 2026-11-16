#pragma once
#include "types.h"
#include "libsdf.h"

extern SDF_PAD ***PrivatePadMap;
extern u8 ***PrivatePadAnalog;
extern SDF_PAD **PrivatePadAnalogMap;
extern SDF_PAD ***PadMap;
extern SDF_PAD **PadAnalogMap;
extern u8 *PadActPow;
extern u8 *PadActPow_goal;
extern u32 *PadActFrame;
extern s32 *keyid_to_padmap;
extern u8 ***PadAnalog;

void dds3PadInitialize(void);
bool dds3PadIsInit(void);
void dds3PadUpdate(void);
u8 ***dds3PadGetAnalog(void);
u8 dds3PadGetAnalogLX(bool keyboard_input);
u8 dds3PadGetAnalogLY(bool keyboard_input);
u8 dds3PadGetAnalogRX(bool keyboard_input);
u8 dds3PadGetAnalogRY(bool keyboard_input);
bool dds3PadIsTypeCD(void);
s32 dds3PadGetNewID(SDF_PADMAP id);
s32 dds3PadGetButtonArrangement(void);
s32 dds3PadGetPadMapToKeyID(SDF_PADMAP id);
s32 dds3PadGetKeyIDToPadMap(s32 id);
void *dds3PadGetKeyIDPADMAP(void);
s32 dds3PadGetKeyIDToSprNo(s32 id);
void dds3PadAct(u32 mode, u8 pow, u32 frame);
void dds3PadActAllStop(void);
bool dds3PadIsAnyKey(void);
