# Raidou HD IL2CPP dump -> C sources

`raidoudump` turns the Il2CppDumper output of Raidou HD (Switch) into C headers, module
sources and a symbol map laid out like the original C code base.

## Background

Raidou HD is a C# port of the PS2 game's C code, built with IL2CPP. The port keeps most of
the C structure: each C module became a static class (`Project.Kernel.dds3KernelCore`), each
C struct a class with only instance fields, each `#define` group a class of constants. It
shares its engine (`libsdf`, `dds3Kernel`, field, battle) with SMT3 HD, whose
reconstruction (~/projects/smt3hd-reconstructed-sources) is used to place types in headers
and to restore function names.

Unlike SMT3 HD, Raidou's IL2CPP build has no `_H_` header markers, but it does keep C#
namespaces (`Project.Kernel`, `Project.libsdf`, ...) and `dump.cs` keeps enum types,
constant values and method and field visibility. Where the port differs from the PS2 code,
the generator emits the native C form.

## Inputs

| File | Used for |
|---|---|
| `il2cpp.h` | struct layouts (`<T>_Fields`, `<T>_StaticFields`), base classes |
| `dump.cs` | namespaces, nesting, kinds, constants, enum-typed fields and parameters, method order and visibility |
| `script.json` | every method with its address and C signature, string literals |
| `smt3_index.json` | SMT3 header of each type and macro, SMT3 function names per module |
| `ps2_names.txt` | optional (`--ps2-names`): function names of the Raidou PS2 IDB, prefix evidence |
| `array_lengths.json` | optional, beside `il2cpp.h`: array counts observed at runtime |
| `raidouhd_main.elf.c` | optional Hex-Rays export: array sizes, call graph, shared statics, bodies |

`global-metadata.dat` is not read: `dump.cs` already has every constant value.

`ps2_names.txt` has one `<hex address> <name>` line per function of the Raidou PS2 IDB, with
names propagated from SMT3; `sub_`, `nullsub_` and `j_` names are ignored.
`array_lengths.json` is `{"<il2cpp class>": {"<field>": [count, is_value]}}`; no heap scan
has been made for Raidou yet, so the file is absent and the code path idle.

## Catalog

Every `Project.*` type in `dump.cs` is classified (`build_catalog`). A nested type has an
empty namespace in `dump.cs`; it takes the namespace of its outermost type.

| Kind | Rule | Emitted as |
|---|---|---|
| enum | C# enum | `typedef enum { ... } T;` |
| delegate | base is `MulticastDelegate` | function pointer typedef from its `Invoke` signature |
| module | has a game method or a static field | statics and functions in a `.c` |
| struct | instance fields only | `struct T { ... };` |
| define | constants only | a `#define` group |

Interfaces, compiler-made types (`<>c`, `DisplayClass`, `PrivateImplementationDetails`) and
C#-only methods (constructors, accessors, operators, `Equals`, `Invoke`, ...) are dropped.
Game base classes are flattened into the struct, base members first. A class that derives
from a game struct and adds no fields is `typedef struct Base Derived;` (21 of them).

Name clashes: a type keeps its innermost name unless another type shares it, then the dotted
path joined by `_`, then the namespace prefix too. A trailing `_` only avoided a clash in C#
(`SBTL_`, `goh_`): it is dropped when the bare name is free.

### Port classes

Methods with a `this` receiver are C#, not the C game. A class with an instance method (its
own or a game base's), or deriving from a runtime class (`MonoBehaviour`,
`ScriptableObject`, ...), is a port class (`drop_port_classes`). One with instance fields
that kept code refers to stays as a plain struct; the rest go, with all their methods. Of
925 port classes, 595 are dropped and 330 kept as structs; 4517 methods go.

Exception: a class without a base and with more than twice as many static game methods as
instance methods is a C module that gained a few C# helpers (`itf`: 787 static, 3 instance;
`rstInit`: 32 and 1). It stays a module and only its instance methods go.

Members typed as a UnityEngine class (`GameObject`, `Texture2D`, ...) are dropped: the
remaster added them to records that have no such member on the PS2. Unity math types map to
`sdf*` and stay. A struct holding only such members has no fields left and is not emitted;
code that refers to it keeps an opaque `typedef struct T T;`.

### Families

Top-level classes are grouped by name without case and trailing `_` (`families.family_key`):
`sBtl`, `sbtl`, `SBTL` and `SBTL_` are family `sbtl`. 28 families have several members. A
family with a module, or with several members, gets the header `<key>.h`:

| Member | Example | Goes to |
|---|---|---|
| class with static game methods | `sBtl`, `sBtlUnit` | `<Name>.c` (the family's main module) |
| class with only static fields | `sbtl` | defined in the main module's `.c`, `extern` in `<key>.h` when public |
| ALLCAPS class with constants | `SBTL` | `#define`s in `<key>.h` |
| ALLCAPS class with methods | `SBTL`, `EFF` | function-like macros in `<key>.h` |
| ALLCAPS enum and other data types | `SBTLMAIN` | `<key>.h` |

The main module is the family's non-ALLCAPS class with the most static game methods. A `.c`
includes its family header.

## Routing

Modules go to their code file: their own `<Module>.c`, their outermost enclosing module's
`.c` when nested, or the family's main module's `.c` for an ALLCAPS or method-less class. A
data type (struct, enum, delegate, constant group) goes to the first match of:

1. its family header, for a top-level type of a family with a header;
2. the SMT3 header defining the same type name (or, for a constant group, one of its macros);
3. its namespace header (`Kernel` -> `kernel.h`, `libsdf` -> `libsdf.h`, `Field_EnemySymbol`
   -> `fieldEnemySymbol.h`, any other `Ns` -> `ns.h`);
4. nested in a module: that module's `.c` when only it uses the type, else the module's
   family header;
5. the one file that references it (a `.c` and its own family header count as one);
6. unreferenced top-level enum -> `enums.h`, constant group -> `defines.h`;
7. `<Type>.h`.

Steps 4 and 5 iterate to a fixed point, since moving a type changes which file its own
references come from. Header names are made unique without case (the lowercase spelling
wins), so the tree checks out on a case-insensitive file system. Current output: 1083
headers, 457 sources; `enums.h` holds 311 enums.

## Members and signatures

| il2cpp.h form | C |
|---|---|
| `System_Int32` etc. | `s32` (`s8` .. `u64`, `f32`, `f64`, `bool`) |
| `System_String_o*` | `char *` |
| `UnityEngine_Vector4_o`, `Matrix4x4_o`, `Quaternion_o`, `Color_o` | `sdfVector4_t`, `sdfMatrix4_t`, ... from `types.h` |
| `<T>_array*` | `T *` (one pointer to the elements), with the count when known (`T name[N]`) |
| game type `_o*` | `T *` (forward-declared struct tag) |
| delegate `_o*` | the typedef itself, already a pointer |
| unknown runtime or generic type | `void *` |

Parameters follow the original C calling forms:

| Parameter | C |
|---|---|
| `T_o** p` (a class by `ref`) | `T *p`: the C code passed the struct pointer |
| `Il2CppObject** p` | `void *p` |
| `System_String_o** s` | `char **s` (a string by reference stays a pointer to one) |
| `UnityEngine_Vector4_o v` (math value) | `const sdfVector4_t *v`; returns stay by value |
| `D_o** d` (delegate by reference) | `D *d` |

il2cpp.h spells an enum field, parameter or return as its integer type; where `dump.cs`
names a game enum there, the enum type is put back. Float constants are written with a comma
decimal in `dump.cs` and are converted. Signatures drop the `MethodInfo` argument; `__this`
becomes `this`.

Enum members keep their C# names unless one of them is also a member of another enum, a
define, a function name or `NULL` (C has one namespace for them): then every member of that
enum takes the enum's name as a prefix, as the game's own enums do (`NONE` in `BOOK_CMDFLAG`
-> `BOOK_CMDFLAG_NONE`, `_3D` -> `X_3D`; `unique_enum_members`). A struct embedded by value in another
struct of the same file is emitted first. A type whose name ends in `_u` is a `union`.

## Linkage

Visibility in `dump.cs` gives C linkage. A public static method is a global function with its
prototype in the family header; a private or internal one is `static` in its `.c`, with a
forward declaration at the top. A public static field is defined in the `.c` and declared
`extern` in the family header; a private one is `static`. With `--source`, a private static
that a function in another file touches (`hexrays.static_field_uses`, which follows locals
holding the class pointer) is made a global the same way, and the user's file includes the
header.

## Function names

The port turned C functions into methods and often dropped the module prefix
(`sdfDraw.TagLinkOtHead` was `sdfDrawTagLinkOtHead`). It stripped the leading camel-case
words the function shared with the class name, so the C name is `P+M` with `P` a run of
leading camel words of the class (`families.camel_prefixes`, `prefix_fits`).

Only public, non-macro functions of a module `X.c` get a prefix; private ones were file
locals and stay bare. In order (`restore_prefixes`):

1. SMT3 `X.c` has `P+M` and `P` is a leading run of words of `X` (flag `R`). When several
   SMT3 symbols could claim `M`, the longest method wins.
2. `P+M` is any SMT3 symbol or a name in `ps2_names.txt`, and `M` does not start with the
   class word that follows `P` (flag `R`). The longest `P` wins. This drops matches like
   `SndPtnTest`+`Process` in `sndManager`.
3. The module's system prefix (flag `I`): the prefix most often restored in `X.c` by 1-2,
   else the longest proper camel prefix of `X` that is itself a game module family
   (`sBtlDraw` -> `sBtl`), else the leading lowercase and digit run of at least two
   characters (`dds3`). Skipped when SMT3 `X.c` or `ps2_names.txt` has `M` bare.

Rules 2 and 3 skip a name another function already holds.

ALLCAPS methods (`families.is_macro_name`: ALLCAPS words, at most two lowercase letters,
so `GET_PER_SRCtoDES` counts) and every method of an ALLCAPS class were function-like
macros (flag `M`). They are never prefixed and go to a `// macros` section: the family
header for an ALLCAPS class, the module's `.c` for a method of a module. A macro is
`#define NAME(args) (expr)` for a body that is one `return`, `do { ... } while (0)` for a
`void` body, else a `static inline` function; a stub is its call graph as a comma
expression.

Names are then made unique per file: overloads get `_2`, `_3` in `dump.cs` order, and a
nested class's method that clashes with another class's gets the class name prefix.
Current output: 11446 functions (739 `R`, 5278 `I`, 5429 bare) and 1000 macros.

## symbols.txt

One row per function and macro, ordered by address:

```
0x022847a0  dds3Init  dds3KernelCore.c  Project.Kernel.dds3KernelCore$$Init  R
0x018bea70  cfgBtnTagConfigLoad  cfg.c  Project.cfg$$BtnTagConfigLoad  I
0x018cd760  ABTN  ConfigGamePad.c  Project.ConfigGamePad$$ABTN  M
```

Columns: address, C name, file defining it, Raidou linker name, flag: `R` prefix restored
from SMT3 or the PS2 names, `I` prefix inferred from the module's system prefix, `M` macro.

## Recovery from the Hex-Rays export

`--source raidouhd_main.elf.c` (made by `tools/export_idb_inputs.py`) adds:

- **Array counts.** A C array became an allocation in a constructor
  (`il2cpp::NewSpecific(T___TypeInfo, N)`, directly or through a local); `N` becomes the
  array count. These win over `array_lengths.json`. Without a count the field stays a
  pointer, which keeps it one word wide.
- **Call graph.** Each stub body calls its callees with zero arguments, so the graph is
  visible without bodies. Functions are matched by the `//----- (ADDR)` separators, so
  overloads resolve.
- **Shared statics**, see Linkage.
- **Bodies** (`--bodies`). Hex-Rays output stripped of IL2CPP noise, with game type names
  cleaned, calls renamed to the C names above and `StringLiteral_<n>` replaced by its text
  (`n` is the 1-based index into `script.json` `ScriptString`, the numbering
  `tools/apply_il2cpp_to_idb.py` gives the IDA names). Bodies with an unbalanced brace stay
  stubs.

Definitions are found by the `//----- (ADDR)` separators (or `__fastcall` on the header;
`hexrays.iter_functions`). Array counts, the call graph, shared statics and bodies all read
the same per-function text.

The export comes from a database prepared like SMT3's (`tools/ida_prepare_export.py`): GOT
slots are typed, so bodies name `X_TypeInfo`, `StringLiteral_<n>` and `Method_*` directly,
and the IL2CPP runtime helpers carry their SMT3 names and prototypes (`il2cpp::NewSpecific`,
`il2cpp::TypeInitializer`, `j_il2cpp::Allocate`, ...). Each body is first normalized
(`hexrays.normalize`):

- **Class pointer locals.** A local that only ever holds one class pointer
  (`v3 = X_TypeInfo;`) or its address is replaced by it, so `v3->static_fields->G` is a
  static access like any other.
- **Allocation results.** An allocation whose result Hex-Rays lost (`NewSpecific(...);`
  followed by a store of an unassigned register) gets the register back.
- **Static members.** `*(T *)(X->static_fields + N)` is named from the layout of
  `X_StaticFields` in `il2cpp.h` (`layout.Layout`): the member starting at `N` whose size
  matches the access width, or the outermost one for an address. Accesses that start inside
  a member stay raw.
- **Allocated objects.** A local Hex-Rays left `__int64` that only ever holds
  `j_il2cpp::Allocate(X_TypeInfo)` is declared `X_o *`, and its raw accesses name the
  members of `X_o` from the same layout: `*(T *)(v + N)` is `v->fields.f` when `T` agrees
  with the member's type, `(T)v->fields.f` when only the type differs (signedness, pointer
  read as an integer), and `*(T *)&v->fields.f` when the bits are reinterpreted (a merged
  store of two fields, a float written as an integer, a read-modify-write that changes
  type); `(T *)(v + N)` is `(T *)&v->fields.f`. An offset inside a member stays
  `(char *)v + N`. The `System_Object___ctor(v, 0)` straight after the allocation, a no-op,
  goes. A local that is reassigned, has its address taken or takes part in arithmetic is
  left alone. A `NewSpecific` array local is typed `X_array *`, and its element accesses
  (`*(T *)(v + 32 + k*S)`, `*(T *)(v + S * i + 32)`) become `v->m_Items[k]` and
  `v->m_Items[i]`. A local whose every value is `*(_QWORD *)(w + N)`, loaded from an object
  pointer member of a typed local `w`, takes that member's type.

Casts come next (`casts.py`, the export is made with "Show casts"). A cast is dropped when
it restates the operand's declared type, the assignment target's type, a call argument or a
call through a function pointer; casts that change width or signedness and every
dereference cast stay and are mapped to repo types (`*(_DWORD *)p` -> `*(u32 *)p`,
`(unsigned int)x` -> `(u32)x`). Wrapped statements are joined first, `40LL` becomes `40`
when it fits, exponent float literals are written out, and Unity `VectorN`/`Matrix4x4`
`get/set_Item_impl` calls with a constant index become member access (`v.x`, `m.m12`).

What the body cleaner does then (`hexrays._clean_body`):

- Metadata init blocks, `TypeInitializer` lines, exception throws and `MethodInfo` temps go.
  Deleting the only statement of a braceless `if`/`for`/`while` drops the guard too. An
  array-store or cast check whose body only jumps to the throw goes with its jump; one that
  guards real code loses only its condition. `nullptr` is written `0`, as in SMT3's sources.
- Class-init (`cctor_finished`) and metadata (`byte_X`) guards are folded as if the class
  and its metadata were initialised. A braced guard keeps its initialised arm; when the
  arms are tail-duplicated copies one is kept and jumps into the other's labels are
  renamed. A guard without `else` on the uninitialised path keeps its body minus the init
  call (it reloads what the init changed). An arm that is dropped but defines a label stays
  behind a `goto` over it, so no jump loses its target. A braceless guard keeps or drops its
  statement the same way.
- Statements after an unconditional `return`/`goto`/`break`/`continue` up to the next label
  or block end go, as do `goto L;` straight before `L:`, labels nothing jumps to, and
  `if (c) goto L; T; if (c) { L: X } T` (the shape a dropped arm leaves), which becomes
  `if (c) { X } T`. This repeats until nothing changes.
- `X->static_fields->G`, and the same through a local holding the class pointer or its
  static block, is the global `G`. A local named after the global it was loaded from is
  dropped when it only copies it, else renamed `G_local`.
- `->fields.` is dropped and `x->m_Items[i]` is `x[i]` (the array header is gone).
- Local types get the prototype mapping (`X_o *` -> `X *`, `T_array *` -> `T *`).
  A parameter or local that lost a pointer level (`T_o **`) loses its dereferences
  (`(*p)->f` -> `p->f`), `&v` passed to a callee slot that lost a level becomes `v`, and a
  Unity math parameter is used through its pointer (`pos.x` -> `pos->x`).
- A call one argument past its callee's arity loses the trailing `MethodInfo` (`0`, a
  `Method_*` name or another bare name), with arguments split at top-level commas so nested
  calls are handled too.
- `__int32`, `_DWORD`, `int32_t`, `unsigned int` and the like become `s32`/`u32`/...;
  unused locals go.
- An `if` whose body was all scaffolding keeps its condition: `if (c) {} else S` becomes
  `if (!c) S`, and `if (c) {}` keeps the calls in `c` (`if (a && f()) {}` -> `if (a) f();`).
  A class init woven into a condition (`if (a && f() && !X->cctor_finished)
  TypeInitializer(X);`) is folded the same way, to `if (a) f();`. Throw helpers and
  exception constructors are scaffolding; a game function named `..._Exception` is not.

## Testing

`raidou/tests/fixtures` holds real snippets of the three inputs (`dds3KernelCore`,
`dds3ProcessID_t`, `DDS3_PRIORITY`, `sdf3DViewportPacket_t`, `fld`, `SKIL176`, ...), carved
by `tools/carve_fixtures.py` and then trimmed by hand. `fixtures/families` holds the family,
macro, linkage, prefix and port-class cases (`sBtl`/`sbtl`/`SBTL`/`SBTL_`, `itf`,
`EventBg`, ...), carved by `tools/carve_family_fixtures.py inputs
raidou/tests/fixtures/families`. The `export_*.c` fixtures are whole functions copied from
the Raidou export (`test_export.py`); the `body_*.c` ones are SMT3 Hex-Rays bodies with the
names put in Raidou form.
Small synthetic inputs in `test_raidoudump.py` cover parameter types, derived structs,
UnityEngine members, unions and shared statics.

Tests cover `dump.cs` parsing, catalog kinds, families, port classes, routing, enum and
delegate recovery, prefix rules, naming, `symbols.txt`, Hex-Rays recovery and an
end-to-end run. From `tools/`:

```sh
uvx --with pytest pytest -q
uvx ruff check raidou
uvx pyright raidou
```
