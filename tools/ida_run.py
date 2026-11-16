"""Load tools/ida_prepare_export.py into the Raidou IDA instance as a module and run a statement.

usage: ida_run.py "statement using m." [TARGET]
TARGET is a port or a path fragment (default "RaidouSwitch"). A statement containing
"prepare()" reloads the module.
"""
import os
import sys

sys.path.insert(0, os.path.expanduser("~/.claude/skills/ida-instances/scripts"))
import ida  # noqa: E402

stmt = sys.argv[1]
target = sys.argv[2] if len(sys.argv) > 2 else "RaidouSwitch"
port = ida.resolve_target(target, ida.get_instances(ida.parse_ports(ida.DEFAULT_PORTS), True))
src = open(os.path.join(os.path.dirname(os.path.abspath(__file__)), "ida_prepare_export.py")).read()
reload = "prepare()" in stmt  # a reload drops the module that owns the Hex-Rays hook
if reload:
    code = (
        "import sys, types\n"
        "old = sys.modules.get('ida_prepare_export')\n"
        "if old is not None and getattr(old, '_hooks', None):\n"
        "    old._hooks.unhook()\n"
        "m = types.ModuleType('ida_prepare_export')\n"
        "exec(compile(%r, 'ida_prepare_export.py', 'exec'), m.__dict__)\n"
        "sys.modules['ida_prepare_export'] = m\n"
        "%s\n" % (src, stmt)
    )
else:
    code = "import sys\nm = sys.modules['ida_prepare_export']\n%s\n" % stmt
r = ida.run_python(port, code)
print(r.get("stdout", ""), r.get("stderr", ""), r.get("result", ""))
