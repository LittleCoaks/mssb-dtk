#!/usr/bin/env python3

###
# Generates build files for the project.
# This file also includes the project configuration,
# such as compiler flags and the object matching status.
#
# Usage:
#   python3 configure.py
#   ninja
#
# Append --help to see available options.
###

import argparse
import sys
from pathlib import Path
from typing import Any, Dict, List

from tools.project import (
    Object,
    ProgressCategory,
    ProjectConfig,
    calculate_progress,
    generate_build,
    is_windows,
)

# Game versions
DEFAULT_VERSION = 0
VERSIONS = [
    "GYQE01",  # 0
    "US_DEMO",  # 1
    "JP_DEMO",  # 2
]

parser = argparse.ArgumentParser()
parser.add_argument(
    "mode",
    choices=["configure", "progress"],
    default="configure",
    help="script mode (default: configure)",
    nargs="?",
)
parser.add_argument(
    "-v",
    "--version",
    choices=VERSIONS,
    type=str.upper,
    default=VERSIONS[DEFAULT_VERSION],
    help="version to build",
)
parser.add_argument(
    "--build-dir",
    metavar="DIR",
    type=Path,
    default=Path("build"),
    help="base build directory (default: build)",
)
parser.add_argument(
    "--binutils",
    metavar="BINARY",
    type=Path,
    help="path to binutils (optional)",
)
parser.add_argument(
    "--compilers",
    metavar="DIR",
    type=Path,
    help="path to compilers (optional)",
)
parser.add_argument(
    "--map",
    action="store_true",
    help="generate map file(s)",
)
parser.add_argument(
    "--debug",
    action="store_true",
    help="build with debug info (non-matching)",
)
if not is_windows():
    parser.add_argument(
        "--wrapper",
        metavar="BINARY",
        type=Path,
        help="path to wibo or wine (optional)",
    )
parser.add_argument(
    "--dtk",
    metavar="BINARY | DIR",
    type=Path,
    help="path to decomp-toolkit binary or source (optional)",
)
parser.add_argument(
    "--objdiff",
    metavar="BINARY | DIR",
    type=Path,
    help="path to objdiff-cli binary or source (optional)",
)
parser.add_argument(
    "--sjiswrap",
    metavar="EXE",
    type=Path,
    help="path to sjiswrap.exe (optional)",
)
parser.add_argument(
    "--ninja",
    metavar="BINARY",
    type=Path,
    help="path to ninja binary (optional)"
)
parser.add_argument(
    "--verbose",
    action="store_true",
    help="print verbose output",
)
parser.add_argument(
    "--non-matching",
    dest="non_matching",
    action="store_true",
    help="builds equivalent (but non-matching) or modded objects",
)
parser.add_argument(
    "--warn",
    dest="warn",
    type=str,
    choices=["all", "off", "error"],
    help="how to handle warnings",
)
parser.add_argument(
    "--no-progress",
    dest="progress",
    action="store_false",
    help="disable progress calculation",
)
args = parser.parse_args()

config = ProjectConfig()
config.version = str(args.version)
version_num = VERSIONS.index(config.version)

# Apply arguments
config.build_dir = args.build_dir
config.dtk_path = args.dtk
config.objdiff_path = args.objdiff
config.binutils_path = args.binutils
config.compilers_path = args.compilers
config.generate_map = args.map
config.non_matching = args.non_matching
config.sjiswrap_path = args.sjiswrap
config.ninja_path = args.ninja
config.progress = args.progress
if not is_windows():
    config.wrapper = args.wrapper
# Don't build asm unless we're --non-matching
if not config.non_matching:
    config.asm_dir = None

# Tool versions
config.binutils_tag = "2.42-1"
config.compilers_tag = "20250812"
config.dtk_tag = "v1.7.1"
config.objdiff_tag = "v3.7.3"
config.sjiswrap_tag = "v1.2.2"
config.wibo_tag = "1.0.0-beta.5"

# Project
config.config_path = Path("config") / config.version / "config.yml"
config.check_sha_path = Path("config") / config.version / "build.sha1"
config.asflags = [
    "-mgekko",
    "--strip-local-absolute",
    "-I include",
    f"-I build/{config.version}/include",
    f"--defsym BUILD_VERSION={version_num}",
]
config.ldflags = [
    "-fp hardware",
    "-nodefaults",
]
if args.debug:
    config.ldflags.append("-g")  # Or -gdwarf-2 for Wii linkers
if args.map:
    config.ldflags.append("-mapunused")
    # config.ldflags.append("-listclosure") # For Wii linkers

# Use for any additional files that should cause a re-configure when modified
config.reconfig_deps = []

# Optional numeric ID for decomp.me preset
# Can be overridden in libraries or objects
config.scratch_preset_id = None

# Base flags, common to most GC/Wii games.
# Generally leave untouched, with overrides added below.
cflags_base = [
    "-proc gekko",
    "-nodefaults",
    "-Cpp_exceptions off",
    "-RTTI off",
    "-fp hard",
    "-fp_contract on",
    "-O4,p",
    "-maxerrors 1",
    "-enum int",
    "-inline auto",
    "-str reuse,readonly",
    "-nosyspath",
    "-use_lmw_stmw on",
    "-sdata 8",
    "-sdata2 8",
    "-DVERNUM={version_num}",
    "-i include",
    "-i include/stl"
]

# Debug flags
if args.debug:
    # Or -sym dwarf-2 for Wii compilers
    cflags_base.extend(["-sym on", "-DDEBUG=1"])
else:
    cflags_base.append("-DNDEBUG=1")

# Warning flags
if args.warn == "all":
    cflags_base.append("-W all")
elif args.warn == "off":
    cflags_base.append("-W off")
elif args.warn == "error":
    cflags_base.append("-W error")

# Metrowerks library flags
cflags_runtime = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-gccinc",
    "-common off",
    "-inline auto",
]

# REL flags
cflags_rel = [
    *cflags_base,
    "-sdata 0",
    "-sdata2 0",
    "-O4,p",
    "-sym on",
    "-inline deferred",
    # "-pool off",
    "-requireprotos",
    "-fp_contract on",
]

config.linker_version = "GC/1.3.2"


# Helper function for Dolphin libraries
def DolphinLib(lib_name: str, objects: List[Object], flags: list[str] = cflags_base, extra_cflags: list[str] = []) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.2.5n",
        "cflags": flags + extra_cflags,
        "host": False,
        "objects": objects,
    }

def RuntimeLib(lib_name:str, objects:List[object], flags :list[str]= cflags_base, extra_cflags:list[str]=[]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/2.6",
        "cflags": flags + extra_cflags,
        "host": False,
        "objects": objects,
    }
def MusyxLib(lib_name:str, objects:List[object], flags :list[str]= cflags_base, extra_cflags:list[str]=[]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.3.2",
        "cflags": flags + extra_cflags,
        "host": False,
        "objects": objects,
    }
def DebuggerLib(lib_name:str, objects:List[object], flags :list[str]= cflags_base, extra_cflags:list[str]=[]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.2.5",
        "cflags": flags + extra_cflags,
        "host": False,
        "objects": objects,
    }
def TRKLib(lib_name:str, objects:List[object], flags :list[str]= cflags_base, extra_cflags:list[str]=[]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/2.6",
        "cflags": flags + extra_cflags,
        "host": False,
        "objects": objects,
    }

# Helper function for REL script objects
def Rel(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        # "progress_category": lib_name,
        "mw_version": "GC/2.6",
        "cflags": cflags_rel,
        "host": True,
        "objects": objects,
    }

Matching = True                   # Object matches and should be linked
NonMatching = False               # Object does not match and should not be linked
Equivalent = config.non_matching  # Object should be linked when configured with --non-matching

config.warn_missing_config = True
config.warn_missing_source = False
config.libs = [
    RuntimeLib(
        "Runtime",
        [
            Object(Matching, "Dolphin/Runtime/__va_arg.c"),
            Object(Matching, "Dolphin/Runtime/global_destructor_chain.c"),
            Object(Matching, "Dolphin/Runtime/runtime.c"),
            Object(Matching, "Dolphin/Runtime/__init_cpp_exceptions.cpp"),
            Object(Matching, "Dolphin/Runtime/Gecko_ExceptionPPC.cp",
                extra_cflags=["-inline deferred", "-Cpp_exceptions on"],
            ),
            Object(Matching, "Dolphin/Runtime/GCN_mem_alloc.c"),
            Object(Matching, "Dolphin/Runtime/__mem.c", 
                   extra_cflags=["-inline deferred"]),
        ],
    ),
    RuntimeLib(
        "MSL_C",
        [
            Object(Matching, "Dolphin/MSL_C/PPC_EABI/abort_exit.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common/alloc.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common/ansi_files.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common_Embedded/ansi_fp.c",
                   extra_cflags=["-inline deferred", "-str pool"],
            ),
            Object(Matching, "Dolphin/MSL_C/MSL_Common/buffer_io.c"),
            Object(Matching, "Dolphin/MSL_C/PPC_EABI/critical_regions.gamecube.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common/ctype.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common/direct_io.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common/errno.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common/file_io.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common/FILE_POS.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common/mbstring.c",
                   extra_cflags=["-inline noauto,deferred"],
            ),
            Object(Matching, "Dolphin/MSL_C/MSL_Common/mem.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common/mem_funcs.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common/misc_io.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common/printf.c",
                   extra_cflags=["-inline deferred", "-str pool"],
            ),
            Object(Matching, "Dolphin/MSL_C/MSL_Common/rand.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common/string.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common/wchar_io.c"),
            Object(Matching, "Dolphin/MSL_C/PPC_EABI/uart_console_io_gcn.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common_Embedded/Math/Double_precision/e_acos.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common_Embedded/Math/Double_precision/e_asin.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common_Embedded/Math/Double_precision/e_atan2.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common_Embedded/Math/Double_precision/e_fmod.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common_Embedded/Math/Double_precision/e_pow.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common_Embedded/Math/Double_precision/e_rem_pio2.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common_Embedded/Math/Double_precision/k_cos.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common_Embedded/Math/Double_precision/k_rem_pio2.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common_Embedded/Math/Double_precision/k_sin.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common_Embedded/Math/Double_precision/k_tan.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common_Embedded/Math/Double_precision/s_atan.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common_Embedded/Math/Double_precision/s_copysign.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common_Embedded/Math/Double_precision/s_cos.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common_Embedded/Math/Double_precision/s_floor.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common_Embedded/Math/Double_precision/s_frexp.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common_Embedded/Math/Double_precision/s_ldexp.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common_Embedded/Math/Double_precision/s_modf.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common_Embedded/Math/Double_precision/s_sin.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common_Embedded/Math/Double_precision/s_tan.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common_Embedded/Math/Double_precision/w_acos.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common_Embedded/Math/Double_precision/w_asin.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common_Embedded/Math/Double_precision/w_atan2.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common_Embedded/Math/Double_precision/w_exp.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common_Embedded/Math/Double_precision/w_fmod.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common_Embedded/Math/Double_precision/w_pow.c"),
            Object(Matching, "Dolphin/MSL_C/MSL_Common_Embedded/Math/Double_precision/e_sqrt.c"),
            Object(Matching, "Dolphin/MSL_C/PPC_EABI/math_ppc.c"),
        ],
        extra_cflags=["-inline deferred"]
    ),
    DolphinLib(
        "base",
        [
            Object(Matching, "Dolphin/base/PPCArch.c"),
        ],
    ),
    DolphinLib(
        "OS",
        [
            Object(Matching, "Dolphin/os/OS.c"),
            Object(Matching, "Dolphin/os/OSAlarm.c"),
            Object(Matching, "Dolphin/os/OSAlloc.c"),
            Object(Matching, "Dolphin/os/OSArena.c"),
            Object(Matching, "Dolphin/os/OSAudioSystem.c"),
            Object(Matching, "Dolphin/os/OSCache.c"),
            Object(Matching, "Dolphin/os/OSContext.c"),
            Object(Matching, "Dolphin/os/OSError.c"),
            Object(NonMatching, "Dolphin/os/OSExec.c"),
            Object(Matching, "Dolphin/os/OSFont.c"),
            Object(Matching, "Dolphin/os/OSInterrupt.c"),
            Object(Matching, "Dolphin/os/OSLink.c"),
            Object(Matching, "Dolphin/os/OSMemory.c"),
            Object(Matching, "Dolphin/os/OSMessage.c"),
            Object(Matching, "Dolphin/os/OSMutex.c"),
            Object(Matching, "Dolphin/os/OSReboot.c"),
            Object(Matching, "Dolphin/os/OSReset.c"),
            Object(Matching, "Dolphin/os/OSResetSW.c"),
            Object(Matching, "Dolphin/os/OSRtc.c"),
            Object(Matching, "Dolphin/os/OSSemaphore.c"),
            Object(Matching, "Dolphin/os/OSSync.c"),
            Object(Matching, "Dolphin/os/OSThread.c"),
            Object(Matching, "Dolphin/os/OSTime.c"),
            Object(Matching, "Dolphin/os/__ppc_eabi_init.cpp"),
        ],
        extra_cflags=["-str noreadonly", "-sym on"]
    ),
    DolphinLib(
        "db",
        [
            Object(Matching, "Dolphin/db/db.c")
        ],
        extra_cflags=["-str noreadonly"]
    ),
    DolphinLib(
        "mtx",
        [
            Object(Matching, "Dolphin/mtx/mtx.c"),
            Object(Matching, "Dolphin/mtx/mtxvec.c"),
            Object(Matching, "Dolphin/mtx/mtx44.c"),
            Object(Matching, "Dolphin/mtx/mtx44vec.c"),
            Object(Matching, "Dolphin/mtx/vec.c"),
            Object(Matching, "Dolphin/mtx/quat.c"),
            Object(Matching, "Dolphin/mtx/psmtx.c"),
        ],
        extra_cflags=["-fp_contract off"]
    ),
    DolphinLib(
        "dvd",
        [
            Object(Matching, "Dolphin/dvd/dvdlow.c"),
            Object(Matching, "Dolphin/dvd/dvdfs.c"),
            Object(Matching, "Dolphin/dvd/dvd.c"),
            Object(Matching, "Dolphin/dvd/dvdqueue.c"),
            Object(Matching, "Dolphin/dvd/dvderror.c"),
            Object(Matching, "Dolphin/dvd/dvdidutils.c"),
            Object(Matching, "Dolphin/dvd/dvdfatal.c"),
            Object(Matching, "Dolphin/dvd/fstload.c"),
        ],
        extra_cflags=["-str noreadonly"]
    ),
    DolphinLib(
        "vi",
        [
            Object(Matching, "Dolphin/vi/vi.c")
        ],
        extra_cflags=["-str noreadonly"]
    ),
    DolphinLib(
        "pad",
        [
            Object(Matching, "Dolphin/pad/Padclamp.c"),
            Object(Matching, "Dolphin/pad/Pad.c"),
        ],
        extra_cflags=["-str noreadonly"]
    ),
    DolphinLib(
        "ai",
        [
            Object(Matching, "Dolphin/ai/ai.c"),
        ],
        extra_cflags=["-str noreadonly"]
    ),
    DolphinLib(
        "ar",
        [
            Object(Matching, "Dolphin/ar/ar.c"),
            Object(Matching, "Dolphin/ar/arq.c"),
        ],
        extra_cflags=["-str noreadonly"]
    ),
    DolphinLib(
        "dsp",
        [
            Object(Matching, "Dolphin/dsp/dsp.c"),
            Object(Matching, "Dolphin/dsp/dsp_debug.c"),
            Object(Matching, "Dolphin/dsp/dsp_task.c"),
        ],
        extra_cflags=["-str noreadonly"]
    ),
    DolphinLib(
        "card",
        [
            Object(Matching, "Dolphin/card/CARDBios.c"),
            Object(Matching, "Dolphin/card/CARDUnlock.c"),
            Object(Matching, "Dolphin/card/CARDRdwr.c"),
            Object(Matching, "Dolphin/card/CARDBlock.c"),
            Object(Matching, "Dolphin/card/CARDDir.c"),
            Object(Matching, "Dolphin/card/CARDCheck.c"),
            Object(Matching, "Dolphin/card/CARDMount.c"),
            Object(Matching, "Dolphin/card/CARDFormat.c"),
            Object(Matching, "Dolphin/card/CARDOpen.c"),
            Object(Matching, "Dolphin/card/CARDCreate.c"),
            Object(Matching, "Dolphin/card/CARDRead.c"),
            Object(Matching, "Dolphin/card/CARDWrite.c"),
            Object(Matching, "Dolphin/card/CARDDelete.c"),
            Object(Matching, "Dolphin/card/CARDStat.c"),
            Object(Matching, "Dolphin/card/CARDStatEx.c"),
            Object(Matching, "Dolphin/card/CARDNet.c"),
        ],
        extra_cflags=["-str noreadonly"]
    ),
    
    DolphinLib(
        "gx",
        [
            Object(Matching, "Dolphin/gx/GXInit.c"),
            Object(Matching, "Dolphin/gx/GXFifo.c"),
            Object(Matching, "Dolphin/gx/GXAttr.c"),
            Object(Matching, "Dolphin/gx/GXMisc.c"),
            Object(Matching, "Dolphin/gx/GXGeometry.c"),
            Object(Matching, "Dolphin/gx/GXFrameBuf.c"),
            Object(Matching, "Dolphin/gx/GXLight.c"),
            Object(Matching, "Dolphin/gx/GXTexture.c"),
            Object(Matching, "Dolphin/gx/GXBump.c"),
            Object(Matching, "Dolphin/gx/GXTev.c"),
            Object(Matching, "Dolphin/gx/GXPixel.c"),
            Object(Matching, "Dolphin/gx/GXDraw.c"),
            Object(Matching, "Dolphin/gx/GXDisplayList.c"),
            Object(Matching, "Dolphin/gx/GXTransform.c"),
            Object(Matching, "Dolphin/gx/GXPerf.c"),
        ],
        extra_cflags=["-common off", "-str noreadonly", "-fp_contract off"]
    ),
    TRKLib(
        "TRK",
        [
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/mainloop.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/nubevent.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/nubinit.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/msg.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/msgbuf.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/serpoll.c",
                   extra_cflags=["-inline deferred", "-sdata 8"]),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/usr_put.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/dispatch.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/msghndlr.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/support.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/mutex_TRK.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/notify.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/flush_cache.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/mem_TRK.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/targimpl.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/targsupp.c",
                   extra_cflags=["-inline deferred", "-func_align 16"]),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/mpc_7xx_603e.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/dolphin_trk.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/main_TRK.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/dolphin_trk_glue.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/targcont.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/target_options.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/mslsupp.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/UDP_stubs.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/ddh/main.c",
                   extra_cflags=["-inline deferred", "-sdata 8"]),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/CircleBuffer.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/gdev/main.c",
                   extra_cflags=["-inline deferred", "-sdata 8"]),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/MWTRACE.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/MWCriticalSection_gc.cpp"),
        ],
        extra_cflags=["-inline deferred", "-sdata 0", "-sdata2 0"]
    ),
    DolphinLib(
        "amcstubs",
        [
            Object(Matching, "Dolphin/amcstubs/AmcExi2Stubs.c"),
        ]
    ),
    DolphinLib(
        "odenotstub",
        [
            Object(Matching, "Dolphin/odenotstub/odenotstub.c"),
        ]
    ),
    DebuggerLib(
        "OdemuExi2",
        [
            Object(Matching, "Dolphin/OdemuExi2/DebuggerDriver.c"),
        ]
    ),
    DolphinLib(
        "exi",
        [
            Object(Matching, "Dolphin/exi/EXIBios.c"),
            Object(Matching, "Dolphin/exi/EXIUart.c"),
        ],
        extra_cflags=["-str noreadonly"]
    ),
    DolphinLib(
        "si",
        [
            Object(Matching, "Dolphin/si/SIBios.c"),
            Object(Matching, "Dolphin/si/SISamplingRate.c"),
        ],
        extra_cflags=["-str noreadonly"]
    ),
    {
        "lib": "unk",
        "mw_version": "GC/2.6",
        "cflags": cflags_base + ["-O4,p", "-sym on"],
        "host": False,
        "objects": [
            Object(NonMatching, "Unknown/File_0x800a6304.c", extra_cflags=["-cpp_exceptions on"]),
            Object(NonMatching, "Unknown/File_0x800a64e0.c", extra_cflags=["-cpp_exceptions on"]),
            Object(NonMatching, "Unknown/File_0x80008fd0.c"),
            Object(NonMatching, "Unknown/File_0x80009180.c"),
            Object(NonMatching, "Unknown/File_0x800096dc.c"),
            Object(NonMatching, "Unknown/File_0x800097a0.c"),
            Object(NonMatching, "Unknown/File_0x80009e94.c"),
            Object(NonMatching, "Unknown/File_0x8000a1e8.c"),
            Object(NonMatching, "Unknown/File_0x8000ba3c.c"),
            Object(NonMatching, "Unknown/File_0x8000c194.c"),
            Object(NonMatching, "Unknown/File_0x8000d164.c"),
            Object(NonMatching, "Unknown/File_0x8000d838.c"),
            Object(NonMatching, "Unknown/File_0x8000e900.c"),
            Object(NonMatching, "Unknown/File_0x8000ef1c.c"),
            Object(NonMatching, "Unknown/File_0x8000f48c.c"),
            Object(Matching, "text/text_channel.c", extra_cflags=["-cpp_exceptions on"]),
            Object(NonMatching, "text/text_width.c", extra_cflags=["-cpp_exceptions on"]),
            Object(Matching, "text/text_block.c"),
            Object(Matching, "text/text_alloc.c", extra_cflags=["-cpp_exceptions on"]),
            Object(NonMatching, "text/sprite_draw.c", extra_cflags=["-cpp_exceptions on"]),
            Object(NonMatching, "text/text_draw.c", extra_cflags=["-cpp_exceptions on"]),
            Object(Matching, "text/text_draw_conditional.c", extra_cflags=["-cpp_exceptions on"]),
            Object(Matching, "text/text_init.c"),
            Object(NonMatching, "Unknown/File_0x800127f8.c"),
            Object(NonMatching, "Unknown/File_0x80013680.c"),
            Object(NonMatching, "Unknown/File_0x80014d4c.c"),
            Object(NonMatching, "Unknown/File_0x80014e50.c"),
            Object(NonMatching, "Unknown/File_0x80014f40.c"),
            Object(NonMatching, "Unknown/File_0x8001594c.c"),
            Object(NonMatching, "Unknown/File_0x80018024.c"),
            Object(NonMatching, "Unknown/File_0x80018270.c"),
            Object(NonMatching, "Unknown/File_0x8001a6b0.c"),
            Object(NonMatching, "Unknown/File_0x8001b2d0.c"),
            Object(NonMatching, "Unknown/File_0x8001b728.c"),
            Object(NonMatching, "Unknown/File_0x8001b80c.c"),
            Object(NonMatching, "Unknown/File_0x8001b918.c"),
            Object(NonMatching, "Unknown/File_0x8001c588.c"),
            Object(NonMatching, "Unknown/File_0x8001c67c.c"),
            Object(NonMatching, "Unknown/File_0x8001c920.c"),
            Object(NonMatching, "Unknown/File_0x8001cbd4.c"),
            Object(NonMatching, "Unknown/File_0x8001ce74.c"),
            Object(NonMatching, "Unknown/File_0x8001d0d0.c"),
            Object(NonMatching, "Unknown/File_0x8001d110.c"),
            Object(NonMatching, "Unknown/File_0x8001d148.c"),
            Object(NonMatching, "Unknown/File_0x8001d180.c"),
            Object(NonMatching, "Unknown/File_0x8001e460.c"),
            Object(NonMatching, "Unknown/File_0x8001f228.c"),
            Object(NonMatching, "Unknown/File_0x8001f4c0.c"),
            Object(NonMatching, "Unknown/File_0x8001f5e8.c"),
            Object(NonMatching, "Unknown/File_0x8001fc4c.c"),
            Object(NonMatching, "Unknown/File_0x80020048.c"),
            Object(NonMatching, "Unknown/File_0x800203e0.c"),
            Object(NonMatching, "Unknown/File_0x800204cc.c"),
            Object(NonMatching, "Unknown/File_0x80021308.c"),
            Object(NonMatching, "Unknown/File_0x80021410.c"),
            Object(NonMatching, "Unknown/File_0x800219b4.c"),
            Object(NonMatching, "Unknown/File_0x80021ca4.c"),
            Object(NonMatching, "Unknown/File_0x80022634.c"),
            Object(NonMatching, "Unknown/File_0x80022dac.c"),
            Object(NonMatching, "Unknown/File_0x800232e0.c"),
            Object(NonMatching, "Unknown/File_0x8002360c.c"),
            Object(NonMatching, "Unknown/File_0x8002399c.c"),
            Object(NonMatching, "Unknown/File_0x80023b04.c"),
            Object(NonMatching, "Unknown/File_0x80023b90.c"),
            Object(NonMatching, "Unknown/File_0x80024184.c"),
            Object(NonMatching, "Unknown/File_0x80024404.c"),
            Object(NonMatching, "Unknown/File_0x800247e4.c"),
            Object(NonMatching, "Unknown/File_0x80024974.c"),
            Object(NonMatching, "Unknown/File_0x800249d8.c"),
            Object(NonMatching, "Unknown/File_0x80024b00.c"),
            Object(NonMatching, "Unknown/File_0x80024bb4.c"),
            Object(NonMatching, "Unknown/File_0x80025c58.c"),
            Object(NonMatching, "Unknown/File_0x80025ddc.c"),
            Object(NonMatching, "Unknown/File_0x800263fc.c"),
            Object(NonMatching, "Unknown/File_0x80033794.c"),
            Object(NonMatching, "Unknown/File_0x80033f64.c"),
            Object(NonMatching, "Unknown/File_0x80034220.c"),
            Object(NonMatching, "Unknown/File_0x8003452c.c"),
            Object(NonMatching, "Unknown/File_0x800348c8.c"),
            Object(NonMatching, "Unknown/File_0x80034cec.c"),
            Object(NonMatching, "Unknown/File_0x80034e20.c"),
            Object(NonMatching, "Unknown/File_0x80034f50.c"),
            Object(NonMatching, "Unknown/File_0x80035168.c"),
            Object(NonMatching, "Unknown/File_0x80035838.c"),
            Object(NonMatching, "Unknown/File_0x80035ca4.c"),
            Object(NonMatching, "Unknown/File_0x800363d8.c"),
            Object(NonMatching, "Unknown/File_0x8003649c.c"),
            Object(NonMatching, "Unknown/File_0x80039aa8.c"),
            Object(NonMatching, "Unknown/File_0x8003a538.c"),
            Object(NonMatching, "Unknown/File_0x8003ad84.c"),
            Object(NonMatching, "Unknown/File_0x8003c00c.c"),
            Object(NonMatching, "Unknown/File_0x8004207c.c"),
            Object(NonMatching, "Unknown/File_0x80042598.c"),
            Object(NonMatching, "Unknown/File_0x800426dc.c"),
            Object(NonMatching, "Unknown/File_0x80042bf0.c"),
            Object(NonMatching, "Unknown/File_0x80042c44.c"),
            Object(NonMatching, "Unknown/File_0x80042d38.c"),
            Object(NonMatching, "Unknown/File_0x80042de8.c"),
            Object(NonMatching, "Unknown/File_0x8004338c.c"),
            Object(NonMatching, "Unknown/File_0x80043880.c"),
            Object(NonMatching, "Unknown/File_0x80044c98.c"),
            Object(NonMatching, "Unknown/File_0x8004617c.c"),
            Object(NonMatching, "Unknown/File_0x80047ce0.c"),
            Object(NonMatching, "Unknown/File_0x80047fe4.c"),
            Object(NonMatching, "Unknown/File_0x800486e0.c"),
            Object(NonMatching, "Unknown/File_0x80048764.c"),
            Object(NonMatching, "Unknown/File_0x80048eb8.c"),
            Object(NonMatching, "Unknown/File_0x80049220.c"),
            Object(NonMatching, "Unknown/File_0x800494cc.c"),
            Object(NonMatching, "Unknown/File_0x80049878.c"),
            Object(NonMatching, "Unknown/File_0x80049c80.c"),
            Object(NonMatching, "Unknown/File_0x80049d8c.c"),
            Object(NonMatching, "Unknown/File_0x8004a1bc.c"),
            Object(NonMatching, "Unknown/File_0x8004a2bc.c"),
            Object(NonMatching, "Unknown/File_0x8004abd8.c"),
            Object(NonMatching, "Unknown/File_0x8004ac00.c"),
            Object(NonMatching, "Unknown/File_0x8004ad54.c"),
            Object(NonMatching, "Unknown/File_0x8004b7f4.c"),
            Object(NonMatching, "Unknown/File_0x8004c094.c"),
            Object(NonMatching, "Unknown/File_0x8004ca6c.c"),
            Object(NonMatching, "Unknown/File_0x8004cc18.c"),
            Object(NonMatching, "Unknown/File_0x8004d57c.c"),
            Object(NonMatching, "Unknown/File_0x8004d93c.c"),
            Object(NonMatching, "Unknown/File_0x8004e504.c"),
            Object(NonMatching, "Unknown/File_0x8004e5b4.c"),
            Object(NonMatching, "Unknown/File_0x8004e62c.c"),
            Object(NonMatching, "Unknown/File_0x8004ee84.c"),
            Object(NonMatching, "Unknown/File_0x80050138.c"),
            Object(NonMatching, "Unknown/File_0x800506e8.c"),
            Object(NonMatching, "Unknown/File_0x80050760.c"),
            Object(NonMatching, "Unknown/File_0x80050fe8.c"),
            Object(NonMatching, "Unknown/File_0x8005268c.c"),
            Object(NonMatching, "Unknown/File_0x80052694.c"),
            Object(NonMatching, "Unknown/File_0x80052734.c"),
            Object(NonMatching, "Unknown/File_0x800527c4.c"),
            Object(NonMatching, "Unknown/File_0x80052968.c"),
            Object(NonMatching, "Unknown/File_0x80052f98.c"),
            Object(NonMatching, "Unknown/File_0x80056120.c"),
            Object(NonMatching, "Unknown/File_0x800569c8.c"),
            Object(NonMatching, "Unknown/File_0x80056ae4.c"),
            Object(NonMatching, "Unknown/File_0x80056f70.c"),
            Object(NonMatching, "Unknown/File_0x800572c0.c"),
            Object(NonMatching, "Unknown/File_0x800576f0.c"),
            Object(NonMatching, "Unknown/File_0x80057c08.c"),
            Object(NonMatching, "Unknown/File_0x80058050.c"),
            Object(NonMatching, "Unknown/File_0x80058394.c"),
            Object(NonMatching, "Unknown/File_0x80059b38.c"),
            Object(NonMatching, "Unknown/File_0x8005a350.c"),
            Object(NonMatching, "Unknown/File_0x8005af68.c"),
            Object(NonMatching, "Unknown/File_0x8005b298.c"),
            Object(NonMatching, "Unknown/File_0x8005bb5c.c"),
            Object(NonMatching, "Unknown/File_0x8005bf40.c"),
            Object(NonMatching, "Unknown/File_0x8005c2b0.c"),
            Object(NonMatching, "Unknown/File_0x80060184.c"),
            Object(NonMatching, "Unknown/File_0x80061b9c.c"),
            Object(NonMatching, "Unknown/File_0x8006236c.c"),
            Object(NonMatching, "Unknown/File_0x80062578.c"),
            Object(NonMatching, "Unknown/File_0x800625a4.c"),
            Object(NonMatching, "Unknown/File_0x80062674.c"),
            Object(NonMatching, "Unknown/File_0x800628d4.c"),
            Object(NonMatching, "Unknown/File_0x80062a50.c"),
            Object(NonMatching, "Unknown/File_0x80062a94.c"),
            Object(NonMatching, "Unknown/File_0x80063958.c"),
            Object(NonMatching, "Unknown/File_0x80064344.c"),
            Object(NonMatching, "Unknown/File_0x80064430.c"),
            Object(NonMatching, "Unknown/File_0x80064754.c"),
            Object(NonMatching, "Unknown/File_0x80064a04.c"),
            Object(NonMatching, "Unknown/File_0x80065dec.c"),
            Object(NonMatching, "Unknown/File_0x800671fc.c"),
            Object(NonMatching, "Unknown/File_0x80067264.c"),
            Object(NonMatching, "Unknown/File_0x800675c4.c"),
            Object(NonMatching, "Unknown/File_0x800678cc.c"),
            Object(NonMatching, "Unknown/File_0x80067ac8.c"),
            Object(NonMatching, "Unknown/File_0x80067f70.c"),
            Object(NonMatching, "Unknown/File_0x80068838.c"),
            Object(NonMatching, "Unknown/File_0x80069854.c"),
            Object(NonMatching, "Unknown/File_0x800698f8.c"),
            Object(NonMatching, "Unknown/File_0x80069a98.c"),
            Object(NonMatching, "Unknown/File_0x8006c48c.c"),
            Object(NonMatching, "Unknown/File_0x8006c7c4.c"),
            Object(NonMatching, "Unknown/File_0x8006c9d8.c"),
            Object(NonMatching, "Unknown/File_0x8006cbe4.c"),
            Object(NonMatching, "Unknown/File_0x8006cca4.c"),
            Object(NonMatching, "Unknown/File_0x80091450.c"),
            Object(NonMatching, "Unknown/File_0x800a6900.c"),
            Object(NonMatching, "Unknown/File_0x800a70dc.c"),
            Object(NonMatching, "Unknown/File_0x800a7544.c"),
            Object(NonMatching, "Unknown/File_0x800a7568.c"),
            Object(NonMatching, "Unknown/File_0x800a75ec.c"),
            Object(NonMatching, "Unknown/File_0x800a7670.c"),
            Object(NonMatching, "Unknown/File_0x800a76bc.c"),
            Object(NonMatching, "Unknown/File_0x800a7c08.c"),
            Object(NonMatching, "Unknown/File_0x800a80e8.c"),
            Object(NonMatching, "Unknown/File_0x800a8cbc.c"),
            Object(NonMatching, "Unknown/File_0x800a983c.c"),
            Object(NonMatching, "Unknown/File_0x800aaee4.c"),
            Object(NonMatching, "Unknown/File_0x800ac508.c"),
            Object(NonMatching, "Unknown/File_0x800acf14.c"),
            Object(NonMatching, "Unknown/File_0x800adf60.c"),
            Object(NonMatching, "Unknown/File_0x800ae298.c"),
            Object(NonMatching, "Unknown/File_0x800aeb18.c"),
            Object(NonMatching, "Unknown/File_0x800aed34.c"),
            Object(NonMatching, "Unknown/File_0x800b0724.c"),
            Object(NonMatching, "Unknown/File_0x800b07fc.c"),
            Object(NonMatching, "Unknown/File_0x800b0834.c"),
            Object(NonMatching, "Unknown/File_0x800b0938.c"),
            Object(NonMatching, "Unknown/File_0x800b099c.c"),
            Object(NonMatching, "Unknown/File_0x800b0a14.c"),
            Object(Matching, "Unknown/File_0x800b0cb8.c", extra_cflags=["-cpp_exceptions on"]),
            Object(NonMatching, "Unknown/File_0x800b0d68.c"),
            Object(NonMatching, "Unknown/File_0x800b12a4.c"),
            Object(NonMatching, "Unknown/File_0x800b1314.c"),
            Object(NonMatching, "Unknown/File_0x800b1350.c"),
            Object(NonMatching, "Unknown/File_0x800b1500.c"),
            Object(NonMatching, "Unknown/File_0x800b2160.c"),
            Object(NonMatching, "Unknown/File_0x800b2ac8.c"),
            Object(NonMatching, "Unknown/File_0x800b2b4c.c"),
            Object(NonMatching, "Unknown/File_0x800b2b74.c"),
            Object(NonMatching, "Unknown/File_0x800b2c44.c"),
            Object(NonMatching, "Unknown/File_0x800b2cbc.c"),
            Object(NonMatching, "Unknown/File_0x800b34b4.c"),
            Object(NonMatching, "Unknown/File_0x800b37a4.c"),
            Object(NonMatching, "Unknown/File_0x800b4048.c"),
            Object(NonMatching, "Unknown/File_0x800b4084.c"),
            Object(NonMatching, "Unknown/File_0x800b43a0.c"),
            Object(NonMatching, "Unknown/File_0x800b472c.c"),
            Object(NonMatching, "Unknown/File_0x800b4908.c"),
            Object(NonMatching, "Unknown/File_0x800b4b38.c"),
            Object(NonMatching, "Unknown/File_0x800b4bc8.c"),
            Object(NonMatching, "Unknown/File_0x800b4d64.c"),
            Object(NonMatching, "Unknown/File_0x800b4e9c.c"),
            Object(NonMatching, "Unknown/File_0x800b4f9c.c"),
            Object(NonMatching, "Unknown/File_0x800b4fec.c"),
            Object(NonMatching, "Unknown/File_0x800b508c.c"),
            Object(NonMatching, "Unknown/File_0x800b516c.c"),
            Object(NonMatching, "Unknown/File_0x800b560c.c"),
            Object(NonMatching, "Unknown/File_0x800b5da8.c"),
            Object(NonMatching, "Unknown/File_0x800b63dc.c"),
            Object(NonMatching, "Unknown/File_0x800b6e0c.c"),
            Object(NonMatching, "Unknown/File_0x800b71c0.c"),
            Object(NonMatching, "Unknown/File_0x800b7718.c"),
            Object(NonMatching, "Unknown/File_0x800b79a0.c"),
            Object(NonMatching, "Unknown/File_0x800b79d0.c"),
            Object(NonMatching, "Unknown/File_0x800b9974.c"),
            Object(NonMatching, "Unknown/File_0x800b99c4.c"),
            Object(NonMatching, "Unknown/File_0x800b9a30.c"),
            Object(NonMatching, "Unknown/File_0x800b9a9c.c"),
            Object(NonMatching, "Unknown/File_0x800ba44c.c"),
            Object(NonMatching, "Unknown/File_0x800ba848.c"),
            Object(NonMatching, "Unknown/File_0x800bbb2c.c"),
            Object(NonMatching, "Unknown/File_0x800bbf5c.c"),
            Object(NonMatching, "Unknown/File_0x800bc0c4.c"),
            Object(NonMatching, "Unknown/File_0x800bc7e8.c"),
            Object(NonMatching, "Unknown/File_0x800bc824.c"),
            Object(NonMatching, "Unknown/File_0x800bc834.c"),
            Object(NonMatching, "Unknown/File_0x800bc860.c"),
            Object(NonMatching, "Unknown/File_0x800bcab8.c"),
            Object(NonMatching, "Unknown/File_0x800bcb44.c"),
            Object(NonMatching, "Unknown/File_0x800bcd60.c"),
            Object(NonMatching, "Unknown/File_0x800bce38.c"),
            Object(NonMatching, "Unknown/File_0x800bcef8.c"),
            Object(NonMatching, "Unknown/File_0x800bd190.c"),
            Object(NonMatching, "Unknown/File_0x800bd208.c"),
            Object(NonMatching, "Unknown/File_0x800bd240.c"),
            Object(NonMatching, "Unknown/File_0x800bd278.c"),
            Object(NonMatching, "Unknown/File_0x800bd2b0.c"),
            Object(NonMatching, "Unknown/File_0x800bd300.c"),
            Object(NonMatching, "Unknown/File_0x800bd3a0.c"),
            Object(NonMatching, "Unknown/File_0x800bd3cc.c"),
            Object(NonMatching, "Unknown/File_0x800bd3ec.c"),
            Object(NonMatching, "Unknown/File_0x800bda94.c"),
            Object(NonMatching, "Unknown/File_0x800bdc88.c"),
            Object(NonMatching, "Unknown/File_0x800bdd74.c"),
            Object(NonMatching, "Unknown/File_0x800bea04.c"),
            Object(NonMatching, "Unknown/File_0x800beb3c.c"),
            Object(NonMatching, "Unknown/File_0x800bf008.c"),
            Object(NonMatching, "Unknown/File_0x800bf038.c"),
            Object(NonMatching, "Unknown/File_0x800bf074.c"),
            Object(NonMatching, "Unknown/File_0x800bf1a4.c"),
            Object(NonMatching, "Unknown/File_0x800bf204.c"),
            Object(NonMatching, "Unknown/File_0x800bf2a8.c"),
            Object(NonMatching, "Unknown/File_0x800bf89c.c"),
            Object(NonMatching, "Unknown/File_0x800bfe90.c"),
        ],
    },
    {
        "lib": "C3",
        "mw_version": "GC/1.3.2",
        "cflags": cflags_base + ["-O4,p", "-sym on", "-cpp_exceptions on"],
        "host": False,
        "objects": [
            Object(NonMatching, "C3/control/control.c", extra_cflags=["-inline deferred"]),
        ],
    },
    MusyxLib(
        "musyx",
        [
            Object(Matching, "Musyx/seq.c"),
            Object(NonMatching, "Musyx/synth.c"),
            Object(Matching, "Musyx/seq_api.c"),
            Object(Matching, "Musyx/snd_synthapi.c"),
            Object(NonMatching, "Musyx/stream.c"),
            Object(NonMatching, "Musyx/synthdata.c"),
            Object(NonMatching, "Musyx/synthmacros.c"),
            Object(NonMatching, "Musyx/synthvoice.c"),
            Object(Matching, "Musyx/synth_ac.c"),
            Object(NonMatching, "Musyx/synth_adsr.c"),
            Object(NonMatching, "Musyx/synth_vsamples.c"),
            Object(NonMatching, "Musyx/s_data.c"),
            Object(NonMatching, "Musyx/hw_dspctrl.c"),
            Object(NonMatching, "Musyx/hw_volconv.c"),
            Object(NonMatching, "Musyx/snd3d.c"),
            Object(Matching, "Musyx/snd_init.c"),
            Object(NonMatching, "Musyx/snd_math.c"),
            Object(NonMatching, "Musyx/snd_midictrl.c"),
            Object(NonMatching, "Musyx/snd_service.c"),
            Object(NonMatching, "Musyx/hardware.c"),
            Object(NonMatching, "Musyx/hw_aramdma.c"),
            Object(NonMatching, "Musyx/hw_dolphin.c"),
            Object(Matching, "Musyx/hw_memory.c"),
            Object(Matching, "Musyx/reverb_fx.c"),
            Object(Matching, "Musyx/reverb.c"),
            Object(Matching, "Musyx/chorus_fx.c"),
        ],
        flags=[
            "-proc gekko",
            "-nodefaults",
            "-Cpp_exceptions off",
            "-RTTI off",
            "-fp hard",
            "-fp_contract on",
            "-O4,p",
            "-maxerrors 1",
            "-enum int",
            "-inline auto",
            "-str reuse",
            "-nosyspath",
            "-i include",
            "-i include/stl",
            f"-DVERSION={version_num}",
            "-DNONMATCHING=0",],
        extra_cflags=["-str reuse,pool,readonly",
                      "-fp_contract off", 
                      "-use_lmw_stmw off"]
    ),
    Rel(
        "game",
        [
            Object(NonMatching, "game/match_setup/rep_0.c"),
            Object(NonMatching, "game/match_setup/loading_state.c"),
            Object(NonMatching, "game/ball/collision_primitives.c"),
            Object(NonMatching, "game/baserunning/runner_base_rounding.c"),
            Object(NonMatching, "game/hud/stadium_draw.c"),
            Object(NonMatching, "game/ball/ball_physics.c"),
            Object(NonMatching, "game/batting/batter.c"),
            Object(NonMatching, "game/camera/camera.c"),
            Object(NonMatching, "game/match_setup/ai_defaults.c"),
            Object(NonMatching, "game/batting/batter_ai.c"),
            Object(NonMatching, "game/pitching/pitcher_ai.c"),
            Object(NonMatching, "game/data_only/rep_9B0.c"),
            Object(NonMatching, "game/match_setup/versus_screens.c"),
            Object(NonMatching, "game/data_only/rep_A78.c"),
            Object(NonMatching, "game/fielding/fielder_catch.c"),
            Object(NonMatching, "game/data_only/rep_CC8.c"),
            Object(NonMatching, "game/data_only/rep_D18.c"),
            Object(NonMatching, "game/data_only/rep_D68.c"),
            Object(NonMatching, "game/data_only/rep_DB8.c"),
            Object(NonMatching, "game/animation/animation_dispatch.c"),
            Object(NonMatching, "game/ball/ball_visuals.c"),
            Object(NonMatching, "game/batting/star_hit_sprites.c"),
            Object(NonMatching, "game/fielding/fielder_orientation.c"),
            Object(NonMatching, "game/match_setup/transition_init.c"),
            Object(NonMatching, "game/fielding/offence_animation.c"),
            Object(NonMatching, "game/match_setup/controller_input.c"),
            Object(NonMatching, "game/match_setup/roster_init.c"),
            Object(NonMatching, "game/pitching/pitcher.c"),
            Object(NonMatching, "game/baserunning/play_result_tracking.c"),
            Object(NonMatching, "game/match_setup/replay_inputs.c"),
            Object(NonMatching, "game/baserunning/runner.c"),
            Object(NonMatching, "game/sound/m_sound.c"),
            Object(NonMatching, "game/hud/rep_1610.c"),
            Object(NonMatching, "game/data_only/rep_1668.c"),
            Object(NonMatching, "game/hud/hud_scoreboard.c"),
            Object(NonMatching, "game/data_only/rep_1720.c"),
            Object(NonMatching, "game/hud/hud_gauges.c"),
            Object(NonMatching, "game/ball/ball_trajectory.c"),
            Object(NonMatching, "game/math/game_math.c", extra_cflags=["-inline deferred,auto", "-fp_contract on"]),
            Object(NonMatching, "game/fielding/fielder_ai.c"),
            Object(NonMatching, "game/data_only/rep_1A80.c"),
            Object(NonMatching, "game/data_only/rep_1AD0.c"),
            Object(NonMatching, "game/data_only/rep_1B20.c"),
            Object(NonMatching, "game/match_setup/player_control_transition.c"),
            Object(NonMatching, "game/data_only/rep_1BC8.c"),
            Object(NonMatching, "game/data_only/rep_1C18.c"),
            Object(NonMatching, "game/data_only/rep_1C68.c"),
            Object(NonMatching, "game/ball/foul_detection.c"),
            Object(NonMatching, "game/stadium/stadium_framework.c"),
            Object(NonMatching, "game/animation/scene_effects.c"),
            Object(NonMatching, "game/batting/charge_effects.c"),
            Object(NonMatching, "game/stadium/stadium_bowser_castle.c"),
            Object(NonMatching, "game/hud/rep_21F8.c"),
            Object(NonMatching, "game/stadium/stadium_mario.c"),
            Object(NonMatching, "game/pitching/perfect_pitch_gfx.c"),
            Object(NonMatching, "game/pitching/pitcher_fire_effect.c"),
            Object(NonMatching, "game/stadium/rep_23E8.c"),
            Object(NonMatching, "game/stadium/stadium_wario_palace.c"),
            Object(NonMatching, "game/minigame/toy_field.c"),
            Object(NonMatching, "game/minigame/minigame_fielder_anim.c"),
            Object(NonMatching, "game/stadium/stadium_yoshi_park.c"),
            Object(NonMatching, "game/stadium/stadium_toy_field.c"),
            Object(NonMatching, "game/minigame/toy_field_offscreen.c"),
            Object(NonMatching, "game/stadium/stadium_dk_jungle.c"),
            Object(NonMatching, "game/stadium/stadium_peach_garden.c"),
            Object(NonMatching, "game/math/rep_3090.c"),
            Object(NonMatching, "game/data_only/rep_31A0.c"),
            Object(NonMatching, "game/minigame/bobomb_derby.c"),
            Object(NonMatching, "game/minigame/wall_ball.c"),
            Object(NonMatching, "game/minigame/pitching_machine.c"),
            Object(NonMatching, "game/hud/rep_3448.c"),
            Object(NonMatching, "game/minigame/barrel_batter.c"),
            Object(NonMatching, "game/minigame/star_dash.c"),
            Object(NonMatching, "game/minigame/chain_chomp_sprint.c"),
            Object(NonMatching, "game/minigame/piranha_panic.c"),
            Object(NonMatching, "game/minigame/rep_3880.c"),
            Object(NonMatching, "game/data_only/rep_3A48.c"),
            Object(NonMatching, "game/data_only/rep_3A98.c"),
            Object(NonMatching, "game/batting/star_swing_peach_daisy.c"),
            Object(NonMatching, "game/data_only/rep_3B70.c"),
            Object(NonMatching, "game/data_only/rep_3BD8.c"),
            Object(NonMatching, "game/data_only/rep_3C28.c"),
            Object(NonMatching, "game/data_only/rep_3C80.c"),
            Object(NonMatching, "game/data_only/rep_3CE0.c"),
            Object(NonMatching, "game/data_only/rep_3D50.c"),
            Object(NonMatching, "game/match_setup/star_missions.c"),
            Object(NonMatching, "game/data_only/rep_3E00.c"),
            Object(NonMatching, "game/animation/magikoopa_star_anim.c"),
            Object(NonMatching, "game/animation/actor_transform.c"),
            Object(NonMatching, "game/stadium/kinoko.c"),
            Object(NonMatching, "game/ball/ball_fielder_collision.c"),
            Object(NonMatching, "game/hud/rep_4138.c"),
        ]
    ),
     Rel(
        "menus",
        [
            Object(NonMatching, "menus/rep_0010.c"),
            Object(NonMatching, "menus/rep_0060.c"),
            Object(NonMatching, "menus/rep_00B0.c"),
            Object(NonMatching, "menus/rep_0100.c"),
            Object(NonMatching, "menus/rep_0150.c"),
            Object(NonMatching, "menus/rep_01A0.c"),
            Object(Matching, "menus/yd_step.c"),
            Object(NonMatching, "menus/rep_0278.c"),
            Object(NonMatching, "menus/rep_02C8.c"),
            Object(NonMatching, "menus/rep_0318.c"),
            Object(NonMatching, "menus/rep_0398.c"),
            Object(NonMatching, "menus/rep_03E8.c"),
            Object(NonMatching, "menus/rep_0438.c"),
            Object(NonMatching, "menus/captain_select/captain_select.c"),
            Object(NonMatching, "menus/rep_0568.c"),
            Object(NonMatching, "menus/rep_05F0.c"),
            Object(NonMatching, "menus/rep_0640.c"),
            Object(NonMatching, "menus/rep_0690.c"),
            Object(NonMatching, "menus/rep_06E0.c"),
            Object(NonMatching, "menus/rep_0730.c"),
            Object(NonMatching, "menus/rep_0788.c"),
            Object(NonMatching, "menus/rep_07F0.c"),
            Object(NonMatching, "menus/rep_0840.c"),
            Object(NonMatching, "menus/rep_0898.c"),
            Object(NonMatching, "menus/rep_08E8.c"),
            Object(NonMatching, "menus/rep_09B8.c"),
            Object(NonMatching, "menus/rep_0A08.c"),
            Object(NonMatching, "menus/rep_0A58.c"),
            Object(NonMatching, "menus/rep_0AB0.c"),
            Object(NonMatching, "menus/rep_0B08.c"),
            Object(NonMatching, "menus/rep_0C50.c"),
            Object(NonMatching, "menus/rep_0CA0.c"),
            Object(NonMatching, "menus/rep_0CF0.c"),
            Object(NonMatching, "menus/rep_0D40.c"),
            Object(NonMatching, "menus/rep_0D90.c"),
            Object(NonMatching, "menus/rep_0DE0.c"),
            Object(NonMatching, "menus/rep_0F10.c"),
            Object(NonMatching, "menus/rep_0F60.c"),
            Object(NonMatching, "menus/rep_0FD8.c"),
            Object(NonMatching, "menus/rep_1028.c"),
            Object(NonMatching, "menus/rep_10C0.c"),
            Object(NonMatching, "menus/rep_11C0.c"),
            Object(NonMatching, "menus/shared.c"),
            Object(NonMatching, "menus/shared/auto_0005979C.c"),
            Object(NonMatching, "menus/shared/auto_0005E104.c"),
            Object(NonMatching, "menus/shared/auto_0008F0F4.c"),
            Object(NonMatching, "menus/shared/auto_0008F27C.c"),
            Object(NonMatching, "menus/shared/auto_0008F3D4.c"),
            Object(NonMatching, "menus/shared/auto_0008F528.c"),
            Object(NonMatching, "menus/shared/auto_0008F7B0.c"),
            Object(NonMatching, "menus/shared/auto_0008F838.c"),
            Object(NonMatching, "menus/shared/auto_0008F8C0.c"),
            Object(NonMatching, "menus/shared/auto_0008F948.c"),
            Object(NonMatching, "menus/shared/auto_0008F9D0.c"),
            Object(NonMatching, "menus/shared/auto_0008FA58.c"),
            Object(NonMatching, "menus/shared/auto_0008FAE0.c"),
            Object(NonMatching, "menus/shared/auto_0008FB68.c"),
            Object(NonMatching, "menus/shared/auto_0008FBF8.c"),
            Object(NonMatching, "menus/shared/auto_0008FC88.c"),
            Object(NonMatching, "menus/shared/auto_0008FDB0.c"),
            Object(NonMatching, "menus/shared/auto_0008FE9C.c"),
            Object(NonMatching, "menus/shared/auto_0009007C.c"),
            Object(NonMatching, "menus/shared/auto_0009033C.c"),
            Object(NonMatching, "menus/shared/auto_000903A8.c"),
            Object(NonMatching, "menus/shared/auto_00090428.c"),
            Object(NonMatching, "menus/shared/auto_000904A8.c"),
            Object(NonMatching, "menus/shared/auto_00090538.c"),
            Object(NonMatching, "menus/shared/auto_00090698.c"),
            Object(NonMatching, "menus/shared/auto_00090718.c"),
            Object(NonMatching, "menus/shared/auto_00090888.c"),
            Object(NonMatching, "menus/shared/auto_0009094C.c"),
            Object(NonMatching, "menus/shared/auto_00090A2C.c"),
            Object(NonMatching, "menus/shared/auto_00090ABC.c"),
            Object(NonMatching, "menus/shared/auto_00090C4C.c"),
            Object(NonMatching, "menus/shared/auto_00090CD0.c"),
            Object(NonMatching, "menus/shared/auto_00090DE4.c"),
            Object(NonMatching, "menus/shared/auto_00090EC4.c"),
            Object(NonMatching, "menus/shared/auto_00091058.c"),
            Object(NonMatching, "menus/shared/auto_00091218.c"),
            Object(NonMatching, "menus/shared/auto_000912A8.c"),
            Object(NonMatching, "menus/shared/auto_00091488.c"),
            Object(NonMatching, "menus/shared/auto_00091518.c"),
            Object(NonMatching, "menus/shared/auto_000916F8.c"),
            Object(NonMatching, "menus/shared/auto_00091788.c"),
            Object(NonMatching, "menus/shared/auto_000919CC.c"),
            Object(NonMatching, "menus/shared/auto_00091C4C.c"),
            Object(NonMatching, "menus/shared/auto_00091D74.c"),
        ]
    ),
    Rel(
        "challenge",
        [
            Object(NonMatching, "challenge/rep_0010.c"),
            Object(NonMatching, "challenge/rep_00B0.c"),
            Object(NonMatching, "challenge/rep_0138.c"),
            Object(NonMatching, "challenge/rep_0250.c"),
            Object(NonMatching, "challenge/rep_02A8.c"),
            Object(NonMatching, "challenge/rep_0610.c"),
            Object(NonMatching, "challenge/rep_74A0.c"),
            Object(NonMatching, "challenge/rep_7730.c"),
            Object(NonMatching, "challenge/rep_7920.c"),
            Object(NonMatching, "challenge/rep_7978.c"),
            Object(NonMatching, "challenge/rep_7A28.c"),
            Object(NonMatching, "challenge/rep_7BA0.c"),
            Object(NonMatching, "challenge/rep_7BF0.c"),
        ]
    )
]

# Optional callback to adjust link order. This can be used to add, remove, or reorder objects.
# This is called once per module, with the module ID and the current link order.
#
# For example, this adds "dummy.c" to the end of the DOL link order if configured with --non-matching.
# "dummy.c" *must* be configured as a Matching (or Equivalent) object in order to be linked.
def link_order_callback(module_id: int, objects: List[str]) -> List[str]:
    # Don't modify the link order for matching builds
    if not config.non_matching:
        return objects
    if module_id == 0:  # DOL
        return objects + ["dummy.c"]
    return objects

# Uncomment to enable the link order callback.
# config.link_order_callback = link_order_callback

# the rels don't strip their unused functions/data
config.rel_strip_partial = False

# Optional extra categories for progress tracking
# Adjust as desired for your project
config.progress_categories = [
    # ProgressCategory("game", "Game Code"),
    # ProgressCategory("sdk", "SDK Code"),
]
# config.progress_each_module = args.verbose
config.progress_each_module = True
config.progress_modules = False
# Optional extra arguments to `objdiff-cli report generate`
config.progress_report_args = [
    # Marks relocations as mismatching if the target value is different
    # Default is "functionRelocDiffs=none", which is most lenient
    # "--config functionRelocDiffs=data_value",
]

if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
elif args.mode == "progress":
    # Print progress information
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
