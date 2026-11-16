// Namespace: 
public class fld.Save_t // TypeDefIndex: 1698
{
	// Fields
	public byte[] takara; // 0x10
	public short tmnltype; // 0x18
	public short tmnlid; // 0x1A
	public int AnahoriCnt; // 0x1C
	public int[] pub; // 0x20
	public byte[][] automapmask; // 0x28
	public byte[] kiretsu; // 0x30
	public bool kiretsuClr; // 0x38

	// Methods

	// RVA: 0x1B46620 Offset: 0x1B46F98 VA: 0x1B46620
	public void .ctor() { }
}

// Namespace: Project
public class fld // TypeDefIndex: 1797
{
	// Fields
	public const int MAPOBJCLEAR_MAX = 64;
	public const int MAPTAKARA_MAX = 256;
	public const int TAKARA_SIZE = 32;
	private static int CamTableIdx; // 0x20
	public static float CamKakudoY; // 0x24

	// Methods

	// RVA: 0x1A3B820 Offset: 0x1A3C198 VA: 0x1A3B820
	public static void CallFieldResult() { }
}

// Namespace: Project
public class SKIL176 // TypeDefIndex: 4805
{
	// Fields
	public const int SMG = 141950976;
	public const int SE00 = 141950976;
	public const int SE01 = 141950977;
	public const int SE02 = 141950978;

	// Methods

	// RVA: 0x21EC190 Offset: 0x21ECB08 VA: 0x21EC190
	public void .ctor() { }
}

// Namespace: Project.libsdf
public class sdf3DViewportPacket_t : sdfGrPacketHeader_t // TypeDefIndex: 5481
{
	// Fields
	public sdfCamera cameraObject; // 0x20
	private sdf3DViewportPacket_t traceSrc; // 0x28

	// Methods

	// RVA: 0x225C140 Offset: 0x225CAB8 VA: 0x225C140
	public void SetTrace(sdf3DViewportPacket_t src) { }

	// RVA: 0x225C150 Offset: 0x225CAC8 VA: 0x225C150 Slot: 4
	public override void OtClose(sdfGrPacketHeader_t.Param param) { }

	// RVA: 0x225C250 Offset: 0x225CBC8 VA: 0x225C250
	public void .ctor() { }
}

// Namespace: Project.libsdf
public abstract class sdfGrPacketHeader_t // TypeDefIndex: 5498
{
	// Fields
	public sdfGrPacketHeader_t next; // 0x10
	public int ctxt; // 0x18

	// Methods

	// RVA: 0x225D530 Offset: 0x225DEA8 VA: 0x225D530 Slot: 4
	public virtual void OtClose(sdfGrPacketHeader_t.Param param) { }

	// RVA: 0x225D540 Offset: 0x225DEB8 VA: 0x225D540
	protected void .ctor() { }
}

// Namespace: Project.Kernel
public class dds3KernelCore // TypeDefIndex: 5680
{
	// Fields
	private static dds3ProcessID_t startinglistf; // 0x0
	private static dds3ProcessID_t startinglistl; // 0x8
	private static int startinglistcnt; // 0x10
	private static dds3ProcessID_t endinglistf; // 0x18
	private static dds3ProcessID_t endinglistl; // 0x20
	private static int endinglistcnt; // 0x28
	private static dds3ProcessID_t runninglistf; // 0x30
	private static dds3ProcessID_t runninglistl; // 0x38
	private static int runninglistcnt; // 0x40
	private static dds3ProcessID_t runprocess; // 0x48
	private static int uua_count; // 0x50
	private static int un_scene_max; // 0x54
	private static AsyncOperation[] unSceneOp; // 0x58

	// Methods

	// RVA: 0x2284790 Offset: 0x2285108 VA: 0x2284790
	private void .ctor() { }

	// RVA: 0x22847A0 Offset: 0x2285118 VA: 0x22847A0
	public static void Init() { }

	// RVA: 0x2284890 Offset: 0x2285208 VA: 0x2284890
	private static void _EndProcess(dds3ProcessID_t setp) { }

	// RVA: 0x2284950 Offset: 0x22852C8 VA: 0x2284950
	private static void DeleteProcessList(dds3ProcessID_t setp) { }

	// RVA: 0x2284BF0 Offset: 0x2285568 VA: 0x2284BF0
	private static void AddProcessList(dds3ProcessID_t setp) { }

	// RVA: 0x2285260 Offset: 0x2285BD8 VA: 0x2285260
	private static void _StartProcess(dds3ProcessID_t setp) { }

	// RVA: 0x22852E0 Offset: 0x2285C58 VA: 0x22852E0
	private static void StartingProcess() { }

}

// Namespace: Project.Kernel
public sealed class dds3ProcessFunc_t : MulticastDelegate // TypeDefIndex: 5682
{
	// Methods

	// RVA: 0x2283730 Offset: 0x22840A8 VA: 0x2283730
	public void .ctor(object object, IntPtr method) { }

	// RVA: 0x22876E0 Offset: 0x2288058 VA: 0x22876E0 Slot: 12
	public virtual dds3ProcessFunc_t Invoke(dds3ProcessID_t UnnamedParameter) { }

	// RVA: 0x2287700 Offset: 0x2288078 VA: 0x2287700 Slot: 13
	public virtual IAsyncResult BeginInvoke(dds3ProcessID_t UnnamedParameter, AsyncCallback callback, object object) { }

	// RVA: 0x2287730 Offset: 0x22880A8 VA: 0x2287730 Slot: 14
	public virtual dds3ProcessFunc_t EndInvoke(IAsyncResult result) { }
}

// Namespace: Project.Kernel
public sealed class shutdownfuncDelegate : MulticastDelegate // TypeDefIndex: 5684
{
	// Methods

	// RVA: 0x2284170 Offset: 0x2284AE8 VA: 0x2284170
	public void .ctor(object object, IntPtr method) { }

	// RVA: 0x22878C0 Offset: 0x2288238 VA: 0x22878C0 Slot: 12
	public virtual void Invoke(dds3ProcessID_t id) { }

	// RVA: 0x22878E0 Offset: 0x2288258 VA: 0x22878E0 Slot: 13
	public virtual IAsyncResult BeginInvoke(dds3ProcessID_t id, AsyncCallback callback, object object) { }

	// RVA: 0x2287910 Offset: 0x2288288 VA: 0x2287910 Slot: 14
	public virtual void EndInvoke(IAsyncResult result) { }
}

// Namespace: Project.Kernel
public class dds3ProcessID_t // TypeDefIndex: 5685
{
	// Fields
	public string name; // 0x10
	public int nameHash; // 0x18
	public uint flag; // 0x1C
	public DDS3_PRIORITY priority; // 0x20
	public uint starttime; // 0x24
	public uint runtime; // 0x28
	public int id; // 0x2C
	public int starttimer; // 0x30
	public int shutdowntimer; // 0x34
	public dds3ProcessFunc_t processfunc; // 0x38
	public shutdownfuncDelegate shutdownfunc; // 0x40
	public object workdata; // 0x48
	public dds3ProcessID_t next; // 0x50
	public dds3ProcessID_t prev; // 0x58
	public dds3ProcessID_t parent; // 0x60
	public dds3ProcessID_t child; // 0x68
	public dds3ProcessID_t sibling; // 0x70

	// Methods

	// RVA: 0x2287920 Offset: 0x2288298 VA: 0x2287920
	public dds3ProcessID_t Clone() { }

	// RVA: 0x2286AD0 Offset: 0x2287448 VA: 0x2286AD0
	public void .ctor() { }
}

// Namespace: Project.Kernel
public enum DDS3_PRIORITY // TypeDefIndex: 5715
{
	// Fields
	public int value__; // 0x0
	public const DDS3_PRIORITY KERNELPROC = 0;
	public const DDS3_PRIORITY GLOBALWORK = 1;
	public const DDS3_PRIORITY USERPROC = 1000;
}

// Namespace: Project
public enum BOOK_CMDTYPE // TypeDefIndex: 395
{
	// Fields
	public int value__; // 0x0
	public const BOOK_CMDTYPE NORMAL = 0;
	public const BOOK_CMDTYPE VAL = 1;
}
