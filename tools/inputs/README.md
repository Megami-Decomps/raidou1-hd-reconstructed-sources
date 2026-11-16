# inputs/

Supplied by you, from a dump of your own copy (not in the repo):

| File | Required | Produced by |
|---|---|---|
| `il2cpp.h` | yes | Il2CppDumper (6.7.46) on the Switch `main` binary and `global-metadata.dat` |
| `dump.cs` | yes | the same Il2CppDumper run |
| `script.json` | yes | the same Il2CppDumper run |
| `raidouhd_main.elf.c` | no | Hex-Rays export of the game functions (`--source`, `--bodies`), steps below |
| `global-metadata.dat` | no | the game's own file; only Il2CppDumper reads it |
| `array_lengths.json` | no | a runtime heap scan of array lengths, `{"<il2cpp class>": {"<field>": [count, is_value]}}`; none exists for Raidou yet |

Committed beside the tools:

| File | Built by | Holds |
|---|---|---|
| `tools/smt3_index.json` | `python -m raidou.smt3index ~/projects/smt3hd-reconstructed-sources` | SMT3 header of each type and macro, SMT3 function names per module |
| `tools/ps2_names.txt` | exported from the Raidou PS2 IDB, names propagated from SMT3 | `<hex address> <name>` per PS2 function; prefix evidence for `--ps2-names` |

Test fixtures are carved from these inputs: `tools/carve_fixtures.py` for
`raidou/tests/fixtures`, and `python3 carve_family_fixtures.py inputs
raidou/tests/fixtures/families` (from `tools/`) for the family, macro, linkage, prefix and
port-class cases. `raidou/tests/fixtures/export_*.c` are single functions copied verbatim
from `raidouhd_main.elf.c`.

## IDA database and Hex-Rays export

Both scripts run inside IDA Pro (File > Script file) on a database of the Switch `main`
binary (`raidouhd_main.elf`):

1. `tools/apply_il2cpp_to_idb.py` applies the Il2CppDumper output to the database: it
   imports `il2cpp.h`, creates and names every function in `script.json` with its signature,
   and names string literals `StringLiteral_<n>` (1-based index into `ScriptString`). Set
   `IL2CPP_DUMP_DIR` to the dumper's output directory; progress goes to `apply.log` there.
2. `tools/export_idb_inputs.py` (optional) writes `raidouhd_main.elf.h` and `.map`, which
   `raidoudump` does not read. Set `EXPORT_DIR` for the output directory and `EXPORT_STEPS`
   (`h`, `map`) to run a subset. Progress goes to `export.log`.
3. Hex-Rays export of the game functions (those named `Class$$method`, runtime and library
   prefixes skipped). Run from `tools/` on the host, with the IDB open and idle:

   ```sh
   python3 ida_run.py "m.prepare()"          # types Vector/Matrix index helpers, defines missing
                                             # game functions, turns on Show casts, hooks floats
   python3 ida_run.py "m.export_all_start()" # chunks to il2cpp_dump\chunks (resumes after restart)
   python3 ida_run.py "print(m.export_all_status())"   # repeat until done is True
   python3 ida_assemble_export.py CHUNKS_DIR inputs/raidouhd_main.elf.c
   ```

   `ida_run.py` finds the IDA instance whose path contains `RaidouSwitch` (pass a port or
   another fragment as the second argument). `ida_compare_export.py OLD.c NEW.c ADDR...` diffs
   chosen functions between two exports. Chunks are copied from the Windows path to a host
   directory first if IDA runs on Windows.

Copy the `.c` here as `raidouhd_main.elf.c`.

The export must have casts shown (`hx:ToggleShowCasts`, set by `m.prepare()`) and float
literals at round-trip precision; the generator drops casts that only restate a type and
keeps those that change width or signedness. `m.prepare()` also readies the database the
way SMT3's is (`ida_prepare_export.py`): GOT slots pointing at TypeInfo, string literal,
`Method$` and `Field$` symbols are typed `T *const`, so bodies name the symbol instead of
`off_X`; the IL2CPP runtime helpers get SMT3's names and prototypes
(`il2cpp::InitializeMethodMetadata`, `il2cpp::TypeInitializer`, `il2cpp::NewSpecific`,
`j_il2cpp::Allocate`, `il2cpp::WriteBarrier`, ...); and every typed function gets an
explicit `__fastcall`. Its slow steps stop at a 45 s deadline, so run it until it returns
`True`. Delegate internals (`sub_3BD820` and neighbours) and PLT imports stay unnamed.

## Running

From `tools/`:

```sh
python3 -m raidou.raidoudump inputs -o .. --smt3 smt3_index.json --ps2-names ps2_names.txt \
    --stats --source inputs/raidouhd_main.elf.c --bodies
```

This writes `../include`, `../src` and `../symbols.txt`. Without `--source` every function is
a stub, arrays without a runtime count stay pointers, and private statics are not checked for
use from other files. Counts from a constructor allocation win over `array_lengths.json`.
`--smt3` also takes a checkout of the SMT3 repo. `--only kernel,dds3KernelCore` writes just
those files.
