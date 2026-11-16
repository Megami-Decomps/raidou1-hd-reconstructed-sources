#pragma once
#include "types.h"
#include "kernel.h"

#define PROCNAME "titleProc"
#define PROCNAME_DRAW "titleDrawProc"
#define FILENAME_LOGO "/title/logo.tmx"
#define FILENAME_TITLE "/title/test01.tmx"
#define STAT_BACK_FILE "/title/test_1.tmx"
#define SPR_FILENAME "/sprite/test.spr"
#define MOT_FILENAME "/sprite/test.mot"
#define CALC_PROCESS_NAME "title_calc"
#define DRAW_PROCESS_NAME "title_draw"
#define SPR_FILE1 "atlus_lg.spr"
#define SPR_FILE2 "title000.spr"
#define SPR_FILE3 "title001.spr"
#define SPR_FILE4 "title002.spr"

typedef struct dds3ProcessID_t dds3ProcessID_t;

extern sdfVector4_t DrawTex_pos;
extern sdfVector4_t DrawTex_uv;
extern sdfVector4_t DrawTex_color;
extern s32 Draw_old;
extern s32 Draw_new;
extern s32 Draw_move;
extern s32 Draw_trig;
extern dds3ProcessID_t *proc_debug;
extern s32 TestPad_count;

void titleRelease(dds3ProcessID_t *proc);
void titleTestRelease(dds3ProcessID_t *proc);
s32 titleTestMain(dds3ProcessID_t *proc);
void titleDeleteDraw(dds3ProcessID_t *proc);
void titleInit(dds3ProcessID_t *proc);
void titleCallNameEntry(void);
bool titleGetPressAnyButton(void);
dds3ProcessFunc_t titleMain(dds3ProcessID_t *proc);
dds3ProcessFunc_t titleDraw(dds3ProcessID_t *proc);
dds3ProcessFunc_t titleProcess(dds3ProcessID_t *proc);
void titleShutdown(dds3ProcessID_t *proc);
void titleInitialize(dds3ProcessID_t *proc);
dds3ProcessFunc_t titleDrawProcess(dds3ProcessID_t *proc);
void titleReleaseDraw(dds3ProcessID_t *proc);
dds3ProcessID_t *titleStart(void);
void titleFinish(dds3ProcessID_t *proc);
void titleStartDebug(void);
void titleFinishDebug(void);
bool CheckDebug(void);
void titleTestCreateWorld(dds3ProcessID_t *proc);
void titleTestDeleteWorld(dds3ProcessID_t *proc);
void titleTestCreateModel(dds3ProcessID_t *proc);
void titleTestUpdateModelShadow(dds3ProcessID_t *proc);
void titleTestUpdateModel(dds3ProcessID_t *proc);
void titleTestInitEffectLineBall(dds3ProcessID_t *proc, const sdfVector4_t *pos);
void titleTestUpdateEffectLineBall(dds3ProcessID_t *proc);
void titleTestDrawEffectLineBall(dds3ProcessID_t *proc);
void titleTestInitEffectParticle(dds3ProcessID_t *proc, const sdfVector4_t *pos, const sdfVector4_t *vec);
void titleTestUpdateEffectParticle(dds3ProcessID_t *proc);
void titleTestPoint3To2(f32 x3, f32 y3, f32 z3, f32 x2, f32 y2);
void titleTestDrawEffectParticle(dds3ProcessID_t *proc);
void titleTestDrawStageLine(void);
void titleTestDrawStage(dds3ProcessID_t *proc);
void titleTestDraw(dds3ProcessID_t *proc);
bool titleTestGetPadAnalog(const sdfVector4_t *pPad, f32 pLength, f32 min);
s32 titleTestPad(dds3ProcessID_t *proc);
