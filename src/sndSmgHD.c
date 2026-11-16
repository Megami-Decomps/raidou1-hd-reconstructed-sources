#include "types.h"
#include "cfg.h"
#include "sdfsound.h"
#include "sndsmghd.h"

static void *_smgtable;
static void *_devilsmg_e;

// 0x21f0090
char *sndGetSmgName(s32 smg_no) {
  u32 v3;
  char *v4;
  char *v5;
  char *v6;
  char **v7;
  void *devilsmg_e;
  char **v14;
  u32 v15;

  v3 = smg_no & 0xFFFF0000;
  if ((smg_no & 0xFFFF0000) - 150929409 < 0xFE00FFFF)
  {
    if (v3 - 98566160 >= 0xFE1FFFF0 || v3 - 99942416 >= 0xFFFAFFF0)
    {
      v15 = (u32)(smg_no - 0x4000000) >> 16;
      v5 = ToString_55996800((s32)&v15, "X3", 0);
      v7 = &"D/D";
    }
    else
    {
      if (v3 - 367001616 >= 0xFE1FFFF0 || v3 - 368377872 >= 0xFFFAFFF0)
      {
        if (object___ContainsKey(_devilsmg_e, v3))
        {
          devilsmg_e = _devilsmg_e;
          return object___get_Item(devilsmg_e, v3);
        }
        return 0;
      }
      if (v3 - 186449921 < 0xFEE2FFFF)
      {
        if (v3 - 0x2000000 < 0x18F0001)
        {
          v4 = "";
          if (v3 <= 0x3610000)
          {
            if (v3 <= 0x3510000)
            {
              if (v3 <= 0x3050000)
              {
                if (v3 <= 0x2930000)
                {
                  if (v3 == 43122688)
                  {
                    v15 = 146;
                    goto LABEL_133;
                  }
                  if (v3 == 43188224)
                  {
                    v15 = 147;
                    goto LABEL_133;
                  }
                }
                else
                {
                  switch (v3)
                  {
                    case 0x2940000u:
                      v15 = 148;
                      goto LABEL_133;
                    case 0x2950000u:
                      v15 = 149;
                      goto LABEL_133;
                    case 0x3050000u:
                      v15 = 261;
                      goto LABEL_133;
                  }
                }
              }
              else if (v3 <= 0x3140000)
              {
                if (v3 == 51576832)
                {
                  v15 = 275;
                  goto LABEL_133;
                }
                if (v3 == 51642368)
                {
                  v15 = 276;
                  goto LABEL_133;
                }
              }
              else
              {
                switch (v3)
                {
                  case 0x3150000u:
                    v15 = 277;
                    goto LABEL_133;
                  case 0x32E0000u:
                    v15 = 302;
                    goto LABEL_133;
                  case 0x3510000u:
                    v15 = 337;
                    goto LABEL_133;
                }
              }
            }
            else if (v3 <= 0x3560000)
            {
              if (v3 <= 0x3530000)
              {
                if (v3 == 55705600)
                {
                  v15 = 338;
                  goto LABEL_133;
                }
                if (v3 == 55771136)
                {
                  v15 = 339;
                  goto LABEL_133;
                }
              }
              else
              {
                switch (v3)
                {
                  case 0x3540000u:
                    v15 = 340;
                    goto LABEL_133;
                  case 0x3550000u:
                    v15 = 341;
                    goto LABEL_133;
                  case 0x3560000u:
                    v15 = 342;
                    goto LABEL_133;
                }
              }
            }
            else
            {
              if (v3 > 0x35A0000)
              {
                if (v3 == 56295424)
                {
                  v15 = 347;
                  v14 = &"VICE/VICE15b";
                }
                else
                {
                  if (v3 != 56360960)
                  {
                    if (v3 == 56688640)
                      v15 = 353;
                    else
                      v15 = (u32)(smg_no - 0x2000000) >> 16;
LABEL_133:
                    if (IsNullOrEmpty(v4, 0))
                    {
                      v5 = ToString_55996800((s32)&v15, "X3", 0);
                      v7 = &"VICE/VICE";
                      goto LABEL_135;
                    }
                    return v4;
                  }
                  v15 = 348;
                  v14 = &"VICE/VICE15c";
                }
LABEL_132:
                v4 = *v14;
                goto LABEL_133;
              }
              if (v3 == 56164352)
              {
                v15 = 345;
                goto LABEL_133;
              }
              if (v3 == 56229888)
              {
                v15 = 346;
                v14 = &"VICE/VICE15a";
                goto LABEL_132;
              }
            }
            v15 = (u32)(smg_no - 0x2000000) >> 16;
            goto LABEL_133;
          }
          if (v3 <= 0x3720000)
          {
            if (v3 <= 0x36B0000)
            {
              if (v3 <= 0x3660000)
              {
                if (v3 == 56754176)
                {
                  v15 = 354;
                  goto LABEL_133;
                }
                if (v3 == 57016320)
                {
                  v15 = 358;
                  goto LABEL_133;
                }
              }
              else
              {
                switch (v3)
                {
                  case 0x3670000u:
                    v15 = 359;
                    goto LABEL_133;
                  case 0x3680000u:
                    v15 = 360;
                    goto LABEL_133;
                  case 0x36B0000u:
                    v15 = 363;
                    v14 = &"VICE/VICE16b";
                    goto LABEL_132;
                }
              }
              v15 = (u32)(smg_no - 0x2000000) >> 16;
              goto LABEL_133;
            }
            if (v3 <= 0x36E0000)
            {
              if (v3 == 57409536)
              {
                v15 = 364;
                v14 = &"VICE/VICE16c";
              }
              else
              {
                if (v3 != 57540608)
                {
                  v15 = (u32)(smg_no - 0x2000000) >> 16;
                  goto LABEL_133;
                }
                v15 = 366;
                v14 = &"VICE/VICE16e";
              }
              goto LABEL_132;
            }
            switch (v3)
            {
              case 0x3700000u:
                v15 = 368;
                goto LABEL_133;
              case 0x3710000u:
                v15 = 369;
                goto LABEL_133;
              case 0x3720000u:
                v15 = 370;
                goto LABEL_133;
            }
          }
          else
          {
            if (v3 > 0x37B0000)
            {
              if (v3 <= 0x37F0000)
              {
                if (v3 == 58458112)
                {
                  v15 = 380;
                  v14 = &"VICE/VICE17c";
                  goto LABEL_132;
                }
                if (v3 == 58654720)
                {
                  v15 = 383;
                  v14 = &"VICE/VICE17f";
                  goto LABEL_132;
                }
LABEL_60:
                v15 = (u32)(smg_no - 0x2000000) >> 16;
                goto LABEL_133;
              }
LABEL_44:
              switch (v3)
              {
                case 0x3800000u:
                  v15 = 384;
                  goto LABEL_133;
                case 0x3810000u:
                  v15 = 385;
                  goto LABEL_133;
                case 0x3820000u:
                  v15 = 386;
                  goto LABEL_133;
              }
              goto LABEL_60;
            }
            if (v3 > 0x3760000)
            {
              switch (v3)
              {
                case 0x3770000u:
                  v15 = 375;
                  goto LABEL_133;
                case 0x37A0000u:
                  v15 = 378;
                  v14 = &"VICE/VICE17a";
                  break;
                case 0x37B0000u:
                  v15 = 379;
                  v14 = &"VICE/VICE17b";
                  break;
                default:
                  v15 = (u32)(smg_no - 0x2000000) >> 16;
                  goto LABEL_133;
              }
              goto LABEL_132;
            }
            if (v3 == 57999360)
            {
              v15 = 373;
              goto LABEL_133;
            }
            if (v3 == 58064896)
            {
              v15 = 374;
              goto LABEL_133;
            }
          }
          v15 = (u32)(smg_no - 0x2000000) >> 16;
          goto LABEL_133;
        }
        if (v3 - 66387969 >= 0xFFFAFFFF)
        {
          v4 = "";
          goto LABEL_44;
        }
        if (object___ContainsKey(_smgtable, v3))
        {
          devilsmg_e = _smgtable;
          return object___get_Item(devilsmg_e, v3);
        }
        return 0;
      }
      v15 = (u32)(smg_no - 167772160) >> 16;
      v5 = ToString_55996800((s32)&v15, "X3", 0);
      v7 = &"ITEM/ITEM";
    }
LABEL_135:
    v6 = *v7;
    return Concat_54766928(v6, v5, 0);
  }
  v15 = (u32)(smg_no - 117440512) >> 16;
  v5 = ToString_55996800((s32)&v15, "X3", 0);
  v6 = "SKIL/SKIL";
  return Concat_54766928(v6, v5, 0);
}

// 0x21f09c0
u32 sndGetDevilEnglish(u32 seno) {
  if (!cfgGetConfigAUDIO(6, 0))
    return seno;
  if (p2sdMidiRegister(seno + 0x10000000))
    seno += 0x10000000;
  return seno;
}
