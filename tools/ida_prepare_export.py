"""Prepare the Raidou HD main.elf IDB for a Hex-Rays "Export to C". Re-runnable; run inside IDA.

prepare(), export_sample(path), export_all_start(outdir), export_all_status().
Assemble chunks with tools/ida_assemble_export.py. Selection: game functions (Class$$method, not runtime).
"""
import json
import math
import os
import re
import struct
import time

import ida_bytes
import ida_funcs
import ida_hexrays
import ida_kernwin
import ida_lines
import ida_nalt
import ida_name
import ida_segment
import ida_typeinf
import idaapi
import idautils
import idc

EXPORT_DIR = r"C:\Users\Chris\Downloads\RaidouSwitch\il2cpp_dump"
DEFAULT_OUTDIR = EXPORT_DIR + "\\chunks"
SCRIPT_JSON = EXPORT_DIR + "\\script.json"

# Runtime/library prefixes of linker names (Class$$method). Everything else is game code.
RUNTIME = (
    "System.", "Mono.", "Microsoft.", "UnityEngine", "Unity.", "TMPro.", "Cinemachine.",
    "MagicaCloth.", "CriWare.", "nn.", "DynamicBone", "Newtonsoft.", "I18N", "Locale",
    "SR$$", "Il2Cpp", "<",
)

# (string literal, vector type, element type, get prototype, set prototype)
INDEX_STRINGS = [
    ("Invalid Vector2 index!", "Vector2", "UnityEngine_Vector2_o",
     "float __fastcall f(UnityEngine_Vector2_o *this, int32_t index);",
     "void __fastcall f(UnityEngine_Vector2_o *this, int32_t index, float value);"),
    ("Invalid Vector3 index!", "Vector3", "UnityEngine_Vector3_o",
     "float __fastcall f(UnityEngine_Vector3_o *this, int32_t index);",
     "void __fastcall f(UnityEngine_Vector3_o *this, int32_t index, float value);"),
    ("Invalid Vector4 index!", "Vector4", "UnityEngine_Vector4_o",
     "float __fastcall f(UnityEngine_Vector4_o *this, int32_t index);",
     "void __fastcall f(UnityEngine_Vector4_o *this, int32_t index, float value);"),
    ("Invalid matrix index!", "Matrix4x4", "UnityEngine_Matrix4x4_o",
     "float __fastcall f(UnityEngine_Matrix4x4_o *this, int32_t row, int32_t column);",
     "void __fastcall f(UnityEngine_Matrix4x4_o *this, int32_t row, int32_t column, float value);"),
]


def log(*a):
    print("[prepare]", *a)


def _set_proto(ea, proto):
    til = ida_typeinf.get_idati()
    tif = ida_typeinf.tinfo_t()
    pt = proto.replace(" f(", " %s(" % "f")
    if ida_typeinf.parse_decl(tif, til, pt, ida_typeinf.PT_SIL) is None:
        log("parse failed", hex(ea), proto)
        return False
    return ida_typeinf.apply_tinfo(ea, tif, ida_typeinf.TINFO_DEFINITE)


def is_game(ea):
    name = ida_name.get_name(ea)
    if "$$" not in name:
        return False
    return not name.startswith(RUNTIME)


def game_function_eas():
    return [ea for ea in idautils.Functions() if is_game(ea)]


def _string_eas(text):
    """Addresses of the StringLiteral slots whose value is text (from script.json)."""
    with open(SCRIPT_JSON, encoding="utf-8") as fh:
        data = json.load(fh)
    base = idaapi.get_imagebase()
    return [base + s["Address"] for s in data["ScriptString"] if s["Value"] == text]


def _stores_float(f):
    """A set_Item stores an S register; a get_Item only loads."""
    for h in idautils.Heads(f.start_ea, f.end_ea):
        if re.match(r"STR\s+S\d", idc.GetDisasm(h), re.I):
            return True
    return False


def type_helpers():
    """Type and rename the vector index helpers found through their error string xrefs."""
    for text, vec, _, get_proto, set_proto in INDEX_STRINGS:
        owners = set()
        for sea in _string_eas(text):
            for x in idautils.XrefsTo(sea, 0):
                f = ida_funcs.get_func(x.frm)
                if f:
                    owners.add(f.start_ea)
        if not owners:
            log("no xref to", repr(text), "-> skipped")
            continue
        for ea in sorted(owners):
            f = ida_funcs.get_func(ea)
            is_set = _stores_float(f)
            proto = set_proto if is_set else get_proto
            if "$$" in idc.get_func_name(ea):
                continue  # a named method with the index check inlined; script.json typed it
            new = "UnityEngine.%s$$%s_Item_impl" % (vec, "set" if is_set else "get")
            ida_name.set_name(ea, new, ida_name.SN_NOWARN | ida_name.SN_FORCE)
            ok = _set_proto(ea, proto)
            log(hex(ea), idc.get_func_name(ea), "typed" if ok else "TYPE FAILED")


def define_missing():
    """Make code and a function out of game methods in script.json that have no function start."""
    try:
        with open(SCRIPT_JSON, encoding="utf-8") as fh:
            data = json.load(fh)
    except OSError as e:
        log("define_missing: no script.json", e)
        return
    base = idaapi.get_imagebase()
    addrs = sorted(set(data["Addresses"]))
    nxt = {a: b for a, b in zip(addrs, addrs[1:])}
    for m in data["ScriptMethod"]:
        if m["Name"].startswith(RUNTIME) or "$$" not in m["Name"]:
            continue
        ea = base + m["Address"]
        f = ida_funcs.get_func(ea)
        if f is not None and f.start_ea == ea:
            continue
        end = base + nxt.get(m["Address"], m["Address"] + 4)
        ida_bytes.del_items(ea, ida_bytes.DELIT_SIMPLE, end - ea)
        cur = ea
        while cur < end:
            n = idc.create_insn(cur)
            if not n:
                break
            cur += n
        ida_funcs.add_func(ea, cur)
        idaapi.auto_wait()
        f = ida_funcs.get_func(ea)
        log("defined", hex(ea), m["Name"], f and hex(f.end_ea))


_CAST = re.compile(r"\(_(?:DWORD|QWORD|WORD|BYTE)\s*\*\)")


def _casts_in(eas):
    hf = ida_hexrays.hexrays_failure_t()
    for ea in eas:
        ida_hexrays.mark_cfunc_dirty(ea)
        cf = ida_hexrays.decompile(ea, hf)
        if cf is not None and _CAST.search(str(cf)):
            return True
    return False


def ensure_show_casts():
    """Turn on Hex-Rays "Show casts" (hx:ToggleShowCasts) if no sampled function shows a cast."""
    eas = game_function_eas()
    probes = eas[:: max(1, len(eas) // 40)][:40]
    if not probes:
        return
    if _casts_in(probes):
        log("casts already shown")
        return
    w = ida_hexrays.open_pseudocode(probes[0], 0)
    ida_kernwin.activate_widget(w.ct, True)
    ida_kernwin.process_ui_action("hx:ToggleShowCasts")
    log("casts toggled on:", _casts_in(probes))


# ---- full-precision float literals -------------------------------------

def fnum_value(f):
    w = list(f.fnum)
    mant = 0
    for i in range(3, 7):
        mant |= w[i] << (16 * (i - 3))
    exp = w[7] & 0x7FFF
    sign = -1.0 if w[7] & 0x8000 else 1.0
    if exp == 0 and mant == 0:
        return 0.0
    if exp == 0x7FFF:
        return None
    from fractions import Fraction
    v = Fraction(mant) * Fraction(2) ** (exp - 16383 - 63)
    return sign * float(v)


def to_f32(x):
    try:
        return struct.unpack("<f", struct.pack("<f", x))[0]
    except OverflowError:
        return None


def shortest_repr(value, nbytes):
    if nbytes == 4:
        v32 = to_f32(value)
        if v32 is None:
            return None
        for p in range(1, 10):
            s = "%.*g" % (p, v32)
            if to_f32(float(s)) == v32:
                break
    else:
        s = repr(float(value))
    if not re.search(r"[.eE]|inf|nan", s):
        s += ".0"
    return s


def sig_digits(tok):
    m = re.match(r"^-?(\d*)\.?(\d*)(?:[eE][-+]?\d+)?$", tok)
    if not m:
        return None
    digits = (m.group(1) + m.group(2)).lstrip("0")
    return max(len(digits), 1)


class _FnumCollector(ida_hexrays.ctree_visitor_t):
    def __init__(self):
        ida_hexrays.ctree_visitor_t.__init__(self, ida_hexrays.CV_FAST)
        self.vals = []

    def visit_expr(self, e):
        if e.op == ida_hexrays.cot_fnum:
            v = fnum_value(e.fpc)
            if v is not None:
                self.vals.append((abs(v), e.fpc.nbytes))
        return 0


FLOATS = {}   # function ea -> {(abs value, nbytes)}
STATS = {"replaced": 0, "kept": 0, "ambiguous": 0}

_FLOAT_TOK = re.compile(r"(?<![\w.])(\d+\.\d*(?:[eE][-+]?\d+)?|\.\d+)(?![\w.])")


def _match_token(tok, cands):
    sd = sig_digits(tok)
    if sd is None:
        return None
    try:
        tv = float(tok)
    except ValueError:
        return None
    hits = set()
    for v, nb in cands:
        if v == 0 or tv == 0:
            if v == tv:
                hits.add((v, nb))
        elif float("%.*g" % (sd, v)) == tv:
            hits.add((v, nb))
    if len(hits) != 1:
        STATS["ambiguous" if hits else "kept"] += 1
        return None
    v, nb = next(iter(hits))
    s = shortest_repr(v, nb)
    if s is not None:
        STATS["replaced"] += 1
    return s


def _fix_line(line, cands):
    # leave string literals and trailing // comments alone
    cut = len(line)
    k = line.find("//")
    if k >= 0:
        cut = k
    code = line[:cut]
    parts = re.split(r'("(?:[^"\\]|\\.)*")', code)
    for n in range(0, len(parts), 2):
        parts[n] = _FLOAT_TOK.sub(lambda m: _match_token(m.group(1), cands) or m.group(1), parts[n])
    return "".join(parts) + line[cut:]


def fix_floats_text(text):
    """Rewrite float literals in decompile_many output using the final ctree constants."""
    out, cur, ea = [], None, None
    for line in text.split("\n"):
        m = re.match(r"^//----- \(([0-9A-F]{16})\)", line)
        if m:
            ea = int(m.group(1), 16)
            cur = FLOATS.get(ea)
        elif cur and not line.startswith("//"):
            line = _fix_line(line, cur)
        out.append(line)
    return "\n".join(out)


class FloatHooks(ida_hexrays.Hexrays_Hooks):
    def maturity(self, cfunc, new_maturity):
        if new_maturity == ida_hexrays.CMAT_FINAL:
            try:
                col = _FnumCollector()
                col.apply_to(cfunc.body, None)
                if col.vals:
                    FLOATS[cfunc.entry_ea] = set(col.vals)
            except Exception as e:
                print("[floats] error", e)
        return 0


_hooks = None


def install_float_hooks():
    global _hooks
    if _hooks is not None:
        _hooks.unhook()
    _hooks = FloatHooks()
    _hooks.hook()
    log("float hook installed")


# ---- IL2CPP runtime helpers, GOT slots, calling convention -------------

# Codegen API thunks in this build, named as the SMT3 IDB names their counterparts. Class and
# metadata arguments are void * so TypeInfo symbols pass without casts.
HELPERS = [
    (0x3BD8B0, "il2cpp::InitializeMethodMetadata", "void __fastcall f(void *metadata);"),
    (0x3BD8D0, "il2cpp::InitializedMetadata", "void *__fastcall f(void *metadata);"),
    (0x3BDAA0, "il2cpp::TypeInitializer", "void __fastcall f(void *klass);"),
    (0x3BDC30, "j_il2cpp::Allocate", "__int64 __fastcall f(void *klass);"),
    (0x3BD9C0, "il2cpp::NewSpecific", "__int64 __fastcall f(void *klass, unsigned int length);"),
    (0x3BD7E0, "il2cpp::WriteBarrier", "void __fastcall f(void *target, void *object);"),
    (0x3BDAB0, "il2cpp::QueryInterface", "void *__fastcall f(void *object, void *klass);"),
    (0x3BDAC0, "il2cpp::Box", "void *__fastcall f(void *klass, void *data);"),
    (0x3BDAD0, "il2cpp::Unbox", "void *__fastcall f(void *object);"),
    (0x3BDA80, "Il2CppExceptionWrapper::ctor",
     "void __fastcall __noreturn f(void *exception, void *lastManagedFrame);"),
    (0x3BDFF0, "il2cpp::ThrowInvalidCastException", "void __fastcall __noreturn f(void *object);"),
    (0x3BDCB0, "il2cpp::ThrowArrayTypeMismatchException", "void *__fastcall f();"),
    (0x3BDC80, "il2cpp::SystemOverflowException", "void *__fastcall f();"),
]


def _proto_type(proto):
    tif = ida_typeinf.tinfo_t()
    ida_typeinf.parse_decl(tif, ida_typeinf.get_idati(), proto, ida_typeinf.PT_SIL)
    return str(tif)


def name_helpers():
    """Name and type the runtime helpers; skips an address whose name is neither sub_ nor ours."""
    for ea, name, proto in HELPERS:
        f = ida_funcs.get_func(ea)
        cur = ida_name.get_name(ea)
        if f is None or f.start_ea != ea or (cur != name and not cur.startswith("sub_")):
            log("helper %X: unexpected %r, skipped" % (ea, cur))
            continue
        if cur != name:
            ida_name.set_name(ea, name, ida_name.SN_NOCHECK | ida_name.SN_NOWARN | ida_name.SN_FORCE)
        if "__noreturn" in proto and not f.flags & ida_funcs.FUNC_NORET:
            f.flags |= ida_funcs.FUNC_NORET
            ida_funcs.update_func(f)
        # Applying a type re-plans every caller (minutes for 160k call sites), so only on change.
        if (idc.get_type(ea) or "") != _proto_type(proto) and not _set_proto(ea, proto):
            log("helper %X: type failed" % ea)
    log("helpers named:", len(HELPERS))


# Il2CppDumper metadata symbols a GOT slot can point at.
_METADATA = re.compile(r"^(?:StringLiteral_\d+|Method\$.*|Field\$.*|.*_TypeInfo|.*_var)$")


def _data_segments():
    out = []
    for s in idautils.Segments():
        seg = ida_segment.getseg(s)
        if idc.get_segm_name(s) == ".data":
            out.append((seg.start_ea, seg.end_ea))
    return out


def _slot_type(target, cache):
    """`T *const` for a target of type T (untyped: `_QWORD`), so Hex-Rays folds `*slot`."""
    if ida_name.get_name(target).startswith("StringLiteral_"):
        base = "System_String_o *"
    else:
        base = idc.get_type(target) or "_QWORD"
    if base not in cache:
        tif = ida_typeinf.tinfo_t()
        decl = "%s *const x;" % base
        ok = ida_typeinf.parse_decl(tif, ida_typeinf.get_idati(), decl, ida_typeinf.PT_SIL)
        cache[base] = tif if ok is not None else None
    return cache[base]


def type_got_slots():
    """The GOT sits inside .data, so Hex-Rays prints `*off_X`; a const slot type makes it fold
    to the symbol. StringLiteral_N targets are typed System_String_o * as well."""
    cache, n, bad = {}, 0, 0
    tstr = ida_typeinf.tinfo_t()
    ida_typeinf.parse_decl(tstr, ida_typeinf.get_idati(), "System_String_o *x;", ida_typeinf.PT_SIL)
    for lo, hi in _data_segments():
        for ea in range(lo, hi, 8):
            if not ida_name.get_name(ea).startswith("off_"):
                continue
            v = ida_bytes.get_qword(ea)
            tn = ida_name.get_name(v)
            if not tn or not _METADATA.match(tn) or (idc.get_type(ea) or "").endswith("*const"):
                continue
            if _out_of_time():
                log("GOT slots typed:", n, "failed:", bad, "(stopped at %X)" % ea)
                return False
            if tn.startswith("StringLiteral_") and not idc.get_type(v):
                ida_typeinf.apply_tinfo(v, tstr, ida_typeinf.TINFO_DEFINITE)
            tif = _slot_type(v, cache)
            if tif is not None and ida_typeinf.apply_tinfo(ea, tif, ida_typeinf.TINFO_DEFINITE):
                n += 1
            else:
                bad += 1
    log("GOT slots typed:", n, "failed:", bad)
    return True


def set_fastcall():
    """Function types applied from script.json carry no explicit calling convention, so the
    export omits `__fastcall`; make it explicit as SMT3's database has it."""
    n = 0
    for ea in idautils.Functions():
        tif = ida_typeinf.tinfo_t()
        if not ida_nalt.get_tinfo(tif, ea):
            continue
        fd = ida_typeinf.func_type_data_t()
        if not tif.get_func_details(fd) or fd.get_explicit_cc() != ida_typeinf.CM_CC_UNKNOWN:
            continue
        if _out_of_time():
            log("__fastcall set on", n, "functions (stopped at %X)" % ea)
            return False
        fd.set_cc(ida_typeinf.CM_CC_FASTCALL)
        new = ida_typeinf.tinfo_t()
        if new.create_func(fd) and ida_typeinf.apply_tinfo(ea, new, ida_typeinf.TINFO_DEFINITE):
            n += 1
    log("__fastcall set on", n, "functions")
    return True


# One IDA MCP call may run 60 s; slow steps stop at this deadline and resume on the next call.
_deadline = [0.0]


def _out_of_time():
    return time.time() > _deadline[0]


def prepare(budget=45):
    """Returns True when every step finished; otherwise run it again (done items are skipped).
    On a fresh database typing the helpers re-plans their callers and blocks IDA for minutes."""
    _deadline[0] = time.time() + budget
    ida_hexrays.init_hexrays_plugin()
    type_helpers()
    define_missing()
    name_helpers()
    done = type_got_slots() and set_fastcall()
    if done:
        ensure_show_casts()
    install_float_hooks()
    idaapi.auto_wait()
    log("done" if done else "not finished, run prepare() again")
    return done


# ---- export ------------------------------------------------------------

def export_chunk(path, eas):
    """decompile_many into path, then restore full-precision float literals."""
    for ea in eas:
        FLOATS.pop(ea, None)
        ida_hexrays.mark_cfunc_dirty(ea)
    flags = ida_hexrays.VDRUN_NEWFILE | ida_hexrays.VDRUN_SILENT
    ok = ida_hexrays.decompile_many(path, list(eas), flags)
    with open(path, encoding="latin-1", newline="") as fh:
        text = fh.read()
    with open(path, "w", encoding="latin-1", newline="") as fh:
        fh.write(fix_floats_text(text))
    return ok


def export_sample(path, eas=None):
    if eas is None:
        g = game_function_eas()
        eas = g[:: max(1, len(g) // 20)][:20]
    return export_chunk(path, eas)


_state = {}


def all_function_eas():
    return game_function_eas()


def export_all_start(outdir=DEFAULT_OUTDIR, chunk=200, per_tick_ms=3000):
    os.makedirs(outdir, exist_ok=True)
    eas = all_function_eas()
    _state.update(dict(outdir=outdir, eas=eas, pos=0, chunk=chunk, n=0, t0=time.time(), done=False, fails=0))
    done_chunks = sorted(f for f in os.listdir(outdir) if f.startswith("chunk_"))
    _state["n"] = len(done_chunks)
    _state["pos"] = len(done_chunks) * chunk   # resume after a restart

    def tick():
        s = _state
        t = time.time()
        while s["pos"] < len(s["eas"]) and (time.time() - t) * 1000 < per_tick_ms:
            part = s["eas"][s["pos"]:s["pos"] + s["chunk"]]
            path = os.path.join(s["outdir"], "chunk_%05d.c" % s["n"])
            export_chunk(path, part)
            s["pos"] += s["chunk"]
            s["n"] += 1
        with open(os.path.join(s["outdir"], "progress.json"), "w") as fh:
            json.dump(dict(pos=min(s["pos"], len(s["eas"])), total=len(s["eas"]), chunks=s["n"],
                           elapsed=time.time() - s["t0"], floats=STATS), fh)
        if s["pos"] >= len(s["eas"]):
            s["done"] = True
            return -1
        return 100

    _state["timer"] = ida_kernwin.register_timer(100, tick)
    log("export started", len(eas), "functions")


def export_all_status():
    s = _state
    return dict(pos=s.get("pos"), total=len(s.get("eas", [])), done=s.get("done"), floats=STATS)


if __name__ == "__main__":
    prepare()
