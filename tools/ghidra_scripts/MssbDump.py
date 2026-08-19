# Dump symbols, decompiled C, or data types from the MSSB Ghidra project.
# Usage (headless): -postScript MssbDump.py <mode> [targets...] <outfile>
#   modes: symbols | data | types | decomp
# @category MSSB
import os
from ghidra.app.decompiler import DecompInterface
from ghidra.util.task import ConsoleTaskMonitor
from ghidra.program.model.symbol import SymbolType

args = list(getScriptArgs())
mode = args[0]
out = args[-1]
fp = open(out, "w")
fm = currentProgram.getFunctionManager()

def wa(a):
    return "0x%08x" % a.getOffset()

if mode == "symbols":
    for f in fm.getFunctions(True):
        fp.write("%s\t%d\t%s\n" % (wa(f.getEntryPoint()), f.getBody().getNumAddresses(), f.getName()))

elif mode == "data":
    # Every defined (typed) data item, plus its label. Ghidra auto-labels typed
    # data as e.g. cameraData_ARRAY_807b2b94 with DEFAULT source, so filtering on
    # symbol source would throw away exactly the type info we want.
    listing = currentProgram.getListing()
    for d in listing.getDefinedData(True):
        s = d.getPrimarySymbol()
        nm = s.getName() if s is not None else ""
        fp.write("%s\t%d\t%s\t%s\n" % (wa(d.getAddress()), d.getLength(),
                                       d.getDataType().getName(), nm))

elif mode == "types":
    from ghidra.program.model.data import Composite, Enum, Union
    dtm = currentProgram.getDataTypeManager()
    want = set(args[1:-1])
    it = dtm.getAllDataTypes()
    while it.hasNext():
        d = it.next()
        nm = d.getName()
        if want and nm not in want:
            continue
        if isinstance(d, Composite):
            kind = "UNION" if isinstance(d, Union) else "STRUCT"
            fp.write("%s\t%s\t0x%x\n" % (kind, nm, d.getLength()))
            for c in d.getComponents():
                fn = c.getFieldName() or ""
                cm = c.getComment() or ""
                fp.write("\t0x%04x\t0x%x\t%s\t%s\t%s\n" % (
                    c.getOffset(), c.getLength(), c.getDataType().getName(), fn, cm))
        elif isinstance(d, Enum):
            fp.write("ENUM\t%s\t0x%x\n" % (nm, d.getLength()))
            for k in d.getNames():
                fp.write("\t%s\t0x%x\n" % (k, d.getValue(k)))

elif mode == "decomp":
    di = DecompInterface()
    di.openProgram(currentProgram)
    mon = ConsoleTaskMonitor()
    for t in args[1:-1]:
        f = None
        if t.startswith("0x"):
            a = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(long(t, 16))
            f = fm.getFunctionContaining(a)
        else:
            for g in fm.getFunctions(True):
                if g.getName() == t:
                    f = g
                    break
        if f is None:
            fp.write("=== %s: NOT FOUND ===\n" % t)
            continue
        fp.write("=== %s @ %s size=%d ===\n" % (f.getName(), wa(f.getEntryPoint()), f.getBody().getNumAddresses()))
        r = di.decompileFunction(f, 180, mon)
        if r.decompileCompleted():
            # Jython's text-mode write turns \n into \r\n; the decompiler already
            # emits \r\n, which would otherwise come out as \r\r\n (double-spaced).
            c = r.getDecompiledFunction().getC()
            fp.write(c.replace("\r\n", "\n").replace("\r", "\n"))
        else:
            fp.write("(decompile failed: %s)\n" % r.getErrorMessage())
        fp.write("\n")
fp.close()
print("WROTE " + out)
