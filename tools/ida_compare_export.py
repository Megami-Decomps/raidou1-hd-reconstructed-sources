"""Print a diff of selected functions (by address) between two Export-to-C files.

usage: ida_compare_export.py OLD.c NEW.c ADDR [ADDR...]
"""
import difflib
import re
import sys


def bodies(path, want):
    out, cur, buf = {}, None, []
    with open(path, encoding="utf8", errors="replace") as fh:
        for line in fh:
            m = re.match(r"^//----- \(([0-9A-F]{16})\)", line)
            if m:
                if cur in want:
                    out[cur] = buf
                cur, buf = int(m.group(1), 16), []
            elif cur is not None:
                buf.append(line)
        if cur in want:
            out[cur] = buf
    return out


old_p, new_p, *addrs = sys.argv[1:]
want = {int(a, 16) for a in addrs}
o, n = bodies(old_p, want), bodies(new_p, want)
for a in sorted(want):
    ob, nb = o.get(a, []), n.get(a, [])
    print("=" * 20, hex(a), "old %d lines, new %d lines" % (len(ob), len(nb)))
    d = list(difflib.unified_diff(ob, nb, "old", "new", n=0))
    print("".join(d[:80]) if len(nb) < 3000 else "(large)")
