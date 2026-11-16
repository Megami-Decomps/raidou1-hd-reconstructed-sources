// Namespace: Project
public class SBTL // TypeDefIndex: 800
{
	// Fields
	public const int HAVESKILL_NUM = 17;
	public const float MTION_DEFSPD = 0,5;
	// Methods
	// RVA: 0x18F06D0 Offset: 0x18F1048 VA: 0x18F06D0
	public static int GETITEMPARA_LOW(int ipara) { }
	[Conditional("SBTL_PRINTFON")]
	// RVA: 0x18F0700 Offset: 0x18F1078 VA: 0x18F0700
	public static void PRINTF(string p) { }
}

// Namespace: Project
public class EventBg : MonoBehaviour // TypeDefIndex: 1584
{
	// Fields
	private static dds3Camera cam; // 0x0
	// Methods
	// RVA: 0x19E6BE0 Offset: 0x19E7558 VA: 0x19E6BE0
	private void Awake() { }
	// RVA: 0x19E6C80 Offset: 0x19E75F8 VA: 0x19E6C80
	private void OnDestroy() { }
	// RVA: 0x19E6CE0 Offset: 0x19E7658 VA: 0x19E6CE0
	public static void Set(bool act) { }
	// RVA: 0x19E6DF0 Offset: 0x19E7768 VA: 0x19E6DF0
	public void .ctor() { }
}

// Namespace: Project
public class SBTLMAIN_DATA // TypeDefIndex: 3113
{
	// Fields
	public Vector4 pos; // 0x10
	public int encountno; // 0x38
	// Methods
	// RVA: 0x1EBD760 Offset: 0x1EBE0D8 VA: 0x1EBD760
	public void ClassCopy(SBTLMAIN_DATA dst) { }
	// RVA: 0x1EBD7A0 Offset: 0x1EBE118 VA: 0x1EBD7A0
	public SBTLMAIN_DATA Clone() { }
}

// Namespace: Project
public class sBtl // TypeDefIndex: 3217
{
	// Fields
	private static int dbg_encount_bk; // 0x0
	private static BattleMap battleMap; // 0x8
	public static string ret_field_scene; // 0x10
	private const int ROULETTE_TOP = 195;
	// Methods
	// RVA: 0x1EC1700 Offset: 0x1EC2078 VA: 0x1EC1700
	public static float DEG_RAD(float x) { }
	// RVA: 0x1EC1940 Offset: 0x1EC22B8 VA: 0x1EC1940
	public static void LimitRange(ref int x, int l, int h) { }
	// RVA: 0x1EC1960 Offset: 0x1EC22D8 VA: 0x1EC1960
	public static void LimitRange(ref short x, short l, short h) { }
	// RVA: 0x1EC1980 Offset: 0x1EC22F8 VA: 0x1EC1980
	public static void LimitRange(ref uint x, uint l, uint h) { }
	// RVA: 0x1EC19A0 Offset: 0x1EC2318 VA: 0x1EC19A0
	public static void LimitRange(ref sbyte x, sbyte l, sbyte h) { }
	// RVA: 0x1EC19C0 Offset: 0x1EC2338 VA: 0x1EC19C0
	public static void LimitRange(ref float x, int l, int h) { }
	// RVA: 0x1EC3CB0 Offset: 0x1EC4628 VA: 0x1EC3CB0
	public static void Init(int mode, int encountno) { }
	// RVA: 0x1ECB260 Offset: 0x1ECBBD8 VA: 0x1ECB260
	public static bool Start(SBTLMAIN_DATA data, int flg) { }
	// RVA: 0x1ECBB20 Offset: 0x1ECC498 VA: 0x1ECBB20
	private static void Exit2Set(int i) { }
	// RVA: 0x1ECC350 Offset: 0x1ECCCC8 VA: 0x1ECC350
	public static void Exit2() { }
}

// Namespace: Project
public enum SBTL_ACTAIFLG // TypeDefIndex: 3222
{
	// Fields
	public int value__; // 0x0
	public const SBTL_ACTAIFLG CMBIN = 1;
	public const SBTL_ACTAIFLG STAND = 2;
	public const SBTL_ACTAIFLG SPRAT = 4;
	public const SBTL_ACTAIFLG RANKS = 8;
	public const SBTL_ACTAIFLG POINT = 16;
	public const SBTL_ACTAIFLG PUSH = 32;
	public const SBTL_ACTAIFLG PUSHOFF = 64;
	public const SBTL_ACTAIFLG LEADER = 128;
	public const SBTL_ACTAIFLG GROUP = 256;
	public const SBTL_ACTAIFLG SEARCH = 512;
	public const SBTL_ACTAIFLG USEPATH = 1024;
	public const SBTL_ACTAIFLG BTLNUM = 2048;
	public const SBTL_ACTAIFLG USETBL = 4096;
	public const SBTL_ACTAIFLG MVBEZ = 8192;
	public const SBTL_ACTAIFLG RENKEI = 16384;
	public const SBTL_ACTAIFLG SKIPSEARCH = 32768;
}

// Namespace: Project
public static class SBTL_ // TypeDefIndex: 3226
{
	// Methods
	// RVA: 0x1ECD0B0 Offset: 0x1ECDA28 VA: 0x1ECD0B0
	public static SBTL_ACTAIFLG ACTAIFLGMASK() { }
}

// Namespace: Project
public enum NEGO2 // TypeDefIndex: 3311
{
	// Fields
	public int value__; // 0x0
	public const NEGO2 REQMONEY = 0;
	public const NEGO2 REQITEM = 1;
	public const NEGO2 REQMAG = 2;
	public const NEGO2 REQHP = 3;
	public const NEGO2 REQNAKAMA = 4;
	public const NEGO2 REQMUSHI = 5;
	public const NEGO2 REQHOUGYOKU = 6;
	public const NEGO2 REQNUM = 7;
}

// Namespace: Project
public enum NEGO2_ // TypeDefIndex: 3312
{
	// Fields
	public int value__; // 0x0
	public const NEGO2_ REQ_MONEY = 1;
}

// Namespace: Project
public class sbtl // TypeDefIndex: 3322
{
	// Fields
	public static SBATTLE_WORK wk; // 0x0
	public static SBTLMAIN_DATA main_data; // 0x18
	public static uint frame_cnt; // 0x34
	// Methods
}

// Namespace: Project
public class SBATTLE_WORK // TypeDefIndex: 3336
{
	// Fields
	public E_SBTLMAIN_STEP step; // 0x750
	// Methods
}

// Namespace: 
public static class dds3KernelDraw.DDS3_DRAW_BISTA // TypeDefIndex: 5686
{
	// Fields
	public const uint TOTAL = 128;
	public const uint TOP_DEF = 49;
	public const uint BTM_DEF = 79;
	public const uint OFY = 0;
	public static short TOP; // 0x0
	public static short BTM; // 0x2
	// Methods
	// RVA: 0x2293550 Offset: 0x2293EC8 VA: 0x2293550
	private static void .cctor() { }
}

// Namespace: 
private class dds3KernelDraw.FIL_t // TypeDefIndex: 5687
{
	// Fields
	public Vector4[,] rgba; // 0x10
	// Methods
	// RVA: 0x22935B0 Offset: 0x2293F28 VA: 0x22935B0
	public void .ctor() { }
}

// Namespace: Project.Kernel
public class dds3KernelDraw // TypeDefIndex: 5699
{
	// Fields
	public static sdfGrOt_t[] Ot; // 0x0
	private static float finishBrightness; // 0x40
	public static bool QuakeFlag; // 0x2BC
	private static DDS3_FADETYPE fadetype; // 0x2DC
	// Properties
	// Methods
	// RVA: 0x2287D50 Offset: 0x22886C8 VA: 0x2287D50
	public static void InitDrawEnv() { }
	// RVA: 0x2288930 Offset: 0x22892A8 VA: 0x2288930
	public static void DrawEnvPush() { }
	// RVA: 0x2289470 Offset: 0x2289DE8 VA: 0x2289470
	public static void SetQuake(int frame, uint range) { }
	// RVA: 0x2289B30 Offset: 0x228A4A8 VA: 0x2289B30
	private static void FadeTypeSet(DDS3_FADETYPE eType) { }
	// RVA: 0x2288660 Offset: 0x2288FD8 VA: 0x2288660
	private static void SetFinish() { }
}

// Namespace: Project.Kernel
public enum DDS3_FADETYPE // TypeDefIndex: 5707
{
	// Fields
	public int value__; // 0x0
	public const DDS3_FADETYPE NON = 0;
	public const DDS3_FADETYPE FADEIN = 1;
	public const DDS3_FADETYPE FADEOUT = 2;
}

// Namespace: UnityEngine
public class MonoBehaviour : Behaviour // TypeDefIndex: 10415
{
	// Fields
	// Properties
	// Methods
}
