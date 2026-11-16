#include "types.h"
#include "aw.h"
#include "aw_approach.h"
#include "aw_approachatk.h"
#include "aw_bullet.h"
#include "aw_bulletmuzzle.h"
#include "aw_bulletsmokep.h"
#include "aw_bulletsmoket.h"
#include "aw_camlockon.h"
#include "aw_camlockonout.h"
#include "aw_combibg.h"
#include "aw_combicam.h"
#include "aw_decoy.h"
#include "aw_down.h"
#include "aw_enemyhitback.h"
#include "aw_groundflame.h"
#include "aw_guntarget.h"
#include "aw_hitbackwave.h"
#include "aw_hitlight.h"
#include "aw_hits.h"
#include "aw_hitsscore.h"
#include "aw_jump.h"
#include "aw_jumpattack2l.h"
#include "aw_jumpkick1.h"
#include "aw_jumpkick2.h"
#include "aw_kudaopen.h"
#include "aw_kudasupport.h"
#include "aw_mag.h"
#include "aw_sbattle.h"
#include "aw_tuugitotu.h"
#include "aw_tuugizan.h"
#include "aw_xatk.h"
#include "aw_xatkblast.h"
#include "aw_xatkbullet.h"
#include "aw_xatkbullethit.h"
#include "aw_xatkcharge.h"
#include "aw_xatkchargel.h"
#include "aw_xatkcrack.h"
#include "aw_xatkdebug.h"
#include "aw_xatkgunimpct.h"
#include "aw_xatkhand.h"
#include "aw_xatkhatudo.h"
#include "aw_xatklaser.h"
#include "aw_xatkmuzzle.h"
#include "aw_xatkpad.h"
#include "aw_xatkparam.h"
#include "aw_xatkpoison.h"
#include "aw_xatkshadow.h"
#include "aw_xatksight.h"
#include "aw_xatksightl.h"
#include "aw_xatksmoke.h"

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

bool gHitDonePlayer;
bool *gHitDoneNakama;

// 0x1e4f950
void ProcStart(void) {
  gHitDonePlayer = 0;
  *(u16 *)gHitDoneNakama = 0;
}

// 0x1e4f9c0
void DeleteAll(void) {
  AllGetAndDelete();
  DelAW_ID(200, 1);
  DelAW_ID(201, 1);
  DelAW_ListType(3, 1);
  DelAW_ListType(4, 1);
  DelAW_ListType(1, 1);
  AW_HitsClrScoreWork();
  AW_XAtkClearBattleEnd_Pad();
  ClearBattleEnd();
  WorkFreeAllClear_BattleEnd();
}

// 0x1e4fc70
void DeleteAll_Event(void) {
  AllGetAndDelete();
  DelAW_ID(200, 1);
  DelAW_ID(201, 1);
  DelAW_ListType(4, 1);
  DelAW_ListType(1, 1);
  AW_HitsClrScoreWork();
}

// 0x1e4fdb0
void DeleteAll_Skill(void) {
  AllGetAndDelete();
  DelAW_ID(200, 1);
  DelAW_ID(201, 1);
  DelAW_ListType(1, 1);
  AW_HitsClrScoreWork();
}

// 0x1e4fee0
void DeleteAll_BossDead(void) {
  DelAW_ListType(4, 1);
}

// 0x1e4ff60
void DeleteAll_BossDYING(SBTLUNIT_WORK *wkBoss) {
  AW_XAtkDelete_BossDYING(wkBoss);
}

// 0x1e4fff0
void DeleteAll_MagWeapon(void) {
  DelAW_ID6(232, 233, 234, 235, 236, 237, 1);
}

// 0x1e50060
void DeleteAll_MenuItemUse(void) {
  DelAW_ID(200, 1);
  DelAW_ID(201, 1);
  DeleteAll();
  AW_ApproachDeleteAll();
  DelAW_ID(213, 1);
  DelAW_ID(238, 1);
  DelAW_ID(239, 1);
}

// 0x1e502d0
void InitBattle(void) {
  Init();
  AW_CamLockonInit();
  Init();
  Init();
  Init();
  Init();
  AW_BulletInit();
  Init();
  AW_JumpInit();
  Init();
  Init();
  Init();
  Init();
  Init();
  AW_ApproachInit();
  Init();
  Init();
  Init();
  Init();
  Init();
  Init();
  Init();
  Init();
  Init();
  Init();
  AW_HitsInit();
  Init();
  Init();
  Init();
  AW_XAtkBulletInit();
  Init();
  Init();
  Init();
  Init();
  AW_XAtkInit();
  Init();
  Init();
  AW_XAtkSightInit();
  Init();
  Init();
  Init();
  Init();
  AW_XAtkChargeInit();
  Init();
  Init();
  Init();
  Init();
  Init();
}
