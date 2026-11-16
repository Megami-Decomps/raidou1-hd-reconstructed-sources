# Raidou HD reconstructed source code and headers

This repo contains a reconstruction of the source structure of Devil Summoner: Raidou
Kuzunoha vs. the Soulless Army, based on the IL2CPP metadata of Raidou HD (Switch).
Raidou HD is a C-to-C# port of the PS2 game. It shares its engine with SMT3 HD
(see the SMT3 reconstruction), and like that port it keeps most of the original C structure:
modules became static classes, structs became classes, `#define` groups became constant
classes. Some examples from the Il2CppDumper output:
```
struct Project_Kernel_dds3ProcessID_t_Fields {
	struct System_String_o* name;
	int32_t nameHash;
	uint32_t flag;
	int32_t priority;
	...
	struct Project_Kernel_dds3ProcessFunc_t_o* processfunc;
	struct Project_Kernel_shutdownfuncDelegate_o* shutdownfunc;
	Il2CppObject* workdata;
	struct Project_Kernel_dds3ProcessID_t_o* next;
	...
};

Project_Kernel_dds3ProcessID_t_o* Project_Kernel_dds3KernelCore__StartProcess (System_String_o* namestr,
  int32_t priority, int32_t starttimer, int32_t shutdowntimer, Project_Kernel_dds3ProcessFunc_t_o* processfunc,
  Project_Kernel_shutdownfuncDelegate_o* shutdownfunc, Il2CppObject* data, const MethodInfo* method);
```
These are reconstructed as
```
// kernel.h
typedef void *(*dds3ProcessFunc_t)(dds3ProcessID_t *UnnamedParameter);

struct dds3ProcessID_t {
    char *name;
    s32 nameHash;
    u32 flag;
    DDS3_PRIORITY priority;
    ...
    dds3ProcessFunc_t processfunc;
    shutdownfuncDelegate shutdownfunc;
    void *workdata;
    dds3ProcessID_t *next;
    ...
};

// dds3kernelcore.h
dds3ProcessID_t *dds3StartProcess(char *namestr, DDS3_PRIORITY priority, s32 starttimer,
    s32 shutdowntimer, dds3ProcessFunc_t processfunc, shutdownfuncDelegate shutdownfunc, void *data);
```

The port often dropped a function's module prefix (`dds3KernelCore.StartProcess`). It is put
back on public functions from the SMT3 reconstruction or the Raidou PS2 function names
(739 functions, flag `R` in `symbols.txt`), else inferred from the module's prefix (5278,
flag `I`). ALLCAPS methods were function-like macros and are emitted as `#define`s (1000,
flag `M`). Classes the port added in C# (anything with instance methods or a Unity base) are
left out; private functions and statics are `static`, public ones are declared in the
module's header.

With `--source`/`--bodies` function bodies come from a Hex-Rays export of the Switch binary,
stripped of IL2CPP scaffolding: class-init and metadata guards are folded, static members are
named, casts that only restate a type are dropped, strings are inlined. Of 12446 functions,
8322 bodies are clean, 4098 keep Hex-Rays `goto`s, offsets or `sub_` calls, and 26 not in the
export stay stubs.

Contents:

- `include/`: headers. Case-insensitive name families (`sBtl`, `sbtl`, `SBTL`) share one
  header (`sbtl.h`) with their public prototypes, `extern`s, `#define`s and macros. Other
  types go to the SMT3 header defining the same name, else their namespace header
  (`kernel.h`, `libsdf.h`, `field.h`, ...). Unreferenced enums and constant groups are
  collected in `enums.h` and `defines.h`.
- `src/`: one `.c` per module, with its statics and functions.
- `symbols.txt`: function address map.
- `tools/`: the generator (`raidoudump`). See `tools/raidou/DESIGN.md` for how it works and
  `tools/inputs/README.md` for the inputs and the command line.
