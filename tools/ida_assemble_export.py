"""Join the chunk_*.c files from ida_prepare_export.export_all_start into one Export-to-C file.

usage: ida_assemble_export.py [CHUNK_DIR] [OUT.c]\ndefaults: inputs/chunks -> inputs/raidouhd_main.elf.c (next to this script)
Declarations are merged without duplicates; bodies keep chunk order.
"""
import glob
import os
import re
import sys

BODY = re.compile(r"^//----- \(", re.M)
FUNC_DECLS = "// Function declarations"
DATA_DECLS = "// Data declarations"
RULE = "//" + "-" * 73


def split_chunk(text):
    m = BODY.search(text)
    head, rest = (text[: m.start()], text[m.start():]) if m else (text, "")
    foot = ""
    k = rest.rfind("\n// nfuncs=")
    if k >= 0:
        rest, foot = rest[: k + 1], rest[k + 1:]
    i = head.find(FUNC_DECLS)
    j = head.find(DATA_DECLS)
    header = head[: head.rfind(RULE, 0, i)] if i >= 0 else head
    funcs = head[i + len(FUNC_DECLS): head.rfind(RULE, 0, j)] if i >= 0 and j >= 0 else ""
    data = head[j + len(DATA_DECLS):] if j >= 0 else ""
    return header, funcs, data, rest, foot


def main(chunk_dir, out_path):
    files = sorted(glob.glob(os.path.join(chunk_dir, "chunk_*.c")))
    seen_f, seen_d = set(), set()
    funcs, data, notes = [], [], []
    header = None
    total = 0
    with open(out_path + ".bodies", "w", encoding="latin-1", newline="") as bodies:
        for f in files:
            with open(f, encoding="latin-1", newline="") as fh:
                h, fn, d, body, foot = split_chunk(fh.read())
            header = header or h
            for line, seen, dst in ((fn, seen_f, funcs), (d, seen_d, data)):
                for ln in line.split("\n"):
                    if ln.strip() and ln not in seen:
                        seen.add(ln)
                        dst.append(ln)
            bodies.write(body)
            total += len(BODY.findall(body))
            notes += [ln for ln in foot.split("\n") if ln.startswith("// ") and "nfuncs=" not in ln and "ALL OK" not in ln]
    with open(out_path, "w", encoding="latin-1", newline="") as out, open(out_path + ".bodies", encoding="latin-1", newline="") as bodies:
        out.write(header or "")
        out.write("%s\n%s\n\n" % (RULE, FUNC_DECLS))
        out.write("\n".join(funcs) + "\n\n")
        out.write("%s\n%s\n\n" % (RULE, DATA_DECLS))
        out.write("\n".join(data) + "\n\n\n")
        while True:
            blk = bodies.read(1 << 24)
            if not blk:
                break
            out.write(blk)
        out.write("\n// %d function bodies in %d chunks\n" % (total, len(files)))
        out.write("\n".join(notes) + "\n")
    os.remove(out_path + ".bodies")
    print(total, "bodies,", len(funcs), "function decls,", len(data), "data decls")


if __name__ == "__main__":
    here = os.path.join(os.path.dirname(os.path.abspath(__file__)), "inputs")
    args = sys.argv[1:3]
    main(*(args + [os.path.join(here, "chunks"), os.path.join(here, "raidouhd_main.elf.c")][len(args):]))
