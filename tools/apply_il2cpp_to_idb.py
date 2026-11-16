"""Apply Il2CppDumper output (script.json, il2cpp.h) to the open IDA database.

Non-interactive version of Il2CppDumper's ida_with_struct_py3.py. Run inside IDA with
IL2CPP_DUMP_DIR set to the dumper's output directory. Progress goes to apply.log there.
"""

import json
import os
import time

import ida_auto
import ida_funcs
import ida_typeinf
import idaapi
import idc

DUMP_DIR = os.environ.get("IL2CPP_DUMP_DIR", r"C:\Users\Chris\Downloads\RaidouSwitch\il2cpp_dump")
LOG = open(os.path.join(DUMP_DIR, "apply.log"), "w", encoding="utf-8")
T0 = time.time()
BASE = idaapi.get_imagebase()


def log(msg):
    LOG.write(f"[{time.time() - T0:7.1f}s] {msg}\n")
    LOG.flush()


def set_name(ea, name):
    if not idc.set_name(ea, name, idc.SN_NOWARN | idc.SN_NOCHECK):
        idc.set_name(ea, f"{name}_{ea}", idc.SN_NOWARN | idc.SN_NOCHECK)


def apply_sig(ea, sig):
    tif = idc.parse_decl(sig, idc.PT_SILENT)
    if tif is None or not idc.apply_type(ea, tif, ida_typeinf.TINFO_DEFINITE):
        return False
    return True


def make_functions(addresses):
    for i in range(len(addresses) - 1):
        start = BASE + addresses[i]
        end = BASE + addresses[i + 1]
        nxt = idc.get_next_func(start)
        if nxt < end:
            end = nxt
        owner = ida_funcs.get_func(start)
        if owner is not None:
            if owner.start_ea == start:
                ida_funcs.del_func(start)
            else:  # earlier auto-analysis merged this method into the one before it
                ida_funcs.set_func_end(owner.start_ea, start)
        ida_funcs.add_func(start, end)
        if i % 20000 == 0:
            log(f"functions {i}/{len(addresses)}")


def main():
    ida_auto.enable_auto(False)
    hpath = os.path.join(DUMP_DIR, "il2cpp.h")
    log("parsing il2cpp.h")
    errors = idc.parse_decls(hpath, idc.PT_FILE | idc.PT_SILENT)
    log(f"parsed il2cpp.h, {errors} errors")

    data = json.loads(open(os.path.join(DUMP_DIR, "script.json"), "rb").read().decode("utf-8"))
    make_functions(data["Addresses"])

    methods = data["ScriptMethod"]
    for i, m in enumerate(methods):
        ea = BASE + m["Address"]
        set_name(ea, m["Name"])
        apply_sig(ea, m["Signature"])
        if i % 20000 == 0:
            log(f"methods {i}/{len(methods)}")
    misplaced = sum(
        1 for m in methods
        if (f := ida_funcs.get_func(BASE + m["Address"])) is None or f.start_ea != BASE + m["Address"]
    )
    log(f"methods done, {misplaced} not at a function start")

    for i, s in enumerate(data["ScriptString"], start=1):
        ea = BASE + s["Address"]
        idc.set_name(ea, f"StringLiteral_{i}", idc.SN_NOWARN)
        idc.set_cmt(ea, s["Value"], 1)
    log("strings done")

    for m in data["ScriptMetadata"]:
        ea = BASE + m["Address"]
        set_name(ea, m["Name"])
        idc.set_cmt(ea, m["Name"], 1)
        if m["Signature"] is not None:
            apply_sig(ea, m["Signature"])
    log("metadata done")

    for m in data["ScriptMetadataMethod"]:
        ea = BASE + m["Address"]
        set_name(ea, m["Name"])
        idc.set_cmt(ea, m["Name"], 1)
        idc.set_cmt(ea, f"{BASE + m['MethodAddress']:X}", 0)
    log("metadata methods done")

    ida_auto.enable_auto(True)
    log("finished")
    LOG.close()


main()
