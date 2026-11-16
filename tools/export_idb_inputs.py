"""Export the reconstruction inputs from the IDA database (run inside IDA).

Writes to EXPORT_DIR: raidouhd_main.elf.h (local types) and
raidouhd_main.elf.map. Progress goes to export.log there. Set EXPORT_STEPS to a comma list (h,map) to run a subset. The .c comes from ida_prepare_export.py.
"""

import os
import time

import ida_loader
import ida_typeinf
import idc

EXPORT_DIR = os.environ.get("EXPORT_DIR", r"C:\Users\Chris\Downloads\RaidouSwitch\il2cpp_dump")
STEPS = set(os.environ.get("EXPORT_STEPS", "h,map").split(","))
STEM = os.path.join(EXPORT_DIR, "raidouhd_main.elf")
LOG = open(os.path.join(EXPORT_DIR, "export.log"), "a", encoding="utf-8")
T0 = time.time()


def log(msg):
    LOG.write(f"[{time.time() - T0:7.1f}s] {msg}\n")
    LOG.flush()


def export_types():
    lines = []

    class Sink(ida_typeinf.text_sink_t):
        def _print(self, s):
            lines.append(s)
            return 0

    ordinals = list(range(1, ida_typeinf.get_ordinal_limit(None)))
    ida_typeinf.print_decls(Sink(), None, ordinals, ida_typeinf.PDF_INCL_DEPS | ida_typeinf.PDF_DEF_FWD)
    with open(STEM + ".h", "w", encoding="utf-8") as fh:
        fh.write("".join(lines))
    log(f"types: {len(lines)} chunks")


def export_map():
    flags = ida_loader.GENFLG_MAPSEG | ida_loader.GENFLG_MAPNAME
    idc.gen_file(idc.OFILE_MAP, STEM + ".map", 0, idc.BADADDR, flags)
    log("map written")


if "h" in STEPS:
    export_types()
if "map" in STEPS:
    export_map()
log("finished")
LOG.close()
