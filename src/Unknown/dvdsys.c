#include "Unknown/dvdsys.h"
#include "Dolphin/ar.h"
#include "Dolphin/dvd.h"
#include "Dolphin/OS/OSThread.h"
#include "Dolphin/OS/OSCache.h"
#include "Unknown/File_0x800a64e0.h"
#include "Unknown/File_0x800a7568.h"
#include "Unknown/File_0x800a75ec.h"
#include "Unknown/File_0x800a7670.h"
#include "Unknown/File_0x800acf14.h"

#define LS(type, off) (*(type*)((u8*)&lbl_803C6CF8 + (off)))
#define LS_VOL(type, off) (*(volatile type*)((u8*)&lbl_803C6CF8 + (off)))

extern u8 lbl_803C7420[0x398];
extern u8 lbl_802EAF80[0x2040];

void fn_800A68D4(u32 ptrToRequest);
void fn_800A7A80(s32 result, DVDFileInfo* fileInfo);
void* fn_800A77A0(void* param);
void fn_800A6F94(s32 result, DVDFileInfo* fileInfo);

void manageFileReadingProcess(void) {
    while (TRUE) {
        s32 driveStatus;
        OSSleepThread((OSThreadQueue*)(lbl_803C7420 + 0x5C));
        driveStatus = DVDGetDriveStatus();
        LS(u8, 0x722) = driveStatus;
        lbl_803C6CF8.driveStatusHandlers[(s8)(u8)driveStatus + 1]();

        if (LS(u8, 0x6D8) != 0 && LS(u8, 0x714) == 2 && LS(s32, 0x6D4) != 0) {
            if (LS(u8, 0x722) == 0) {
                LS(s32, 0x6D4) = LS(s32, 0x6D4) - 1;
            } else {
                LS(s32, 0x6D4) = LS(s32, 0x6D0);
            }
        }

        {
            switch (LS(u8, 0x714)) {
            case 2: {
                if (LS(u8, 0x717) == 0 || LS(u8, 0x717) == 3) {
                    if (gDataDecompressorValues.ShouldWriteDataFlag == 0) {
                        DCFlushRangeNoSync(LS(void*, 0x700), gDataDecompressorValues.CachedBytesToRead);
                        if (LS(void*, 0x6FC) != NULL) {
                            unkLoadingCleanupRelated(LS(void*, 0x6FC));
                            LS(void*, 0x6FC) = NULL;
                        }
                        LS(u16, 0x714) = 1;
                    } else {
                        if (gDataDecompressorValues.error == 0 &&
                            !(LS(u8, 0x6D8) != 0 && LS(s32, 0x6D4) == 0)) {
                            continue;
                        }
                        DVDCancel((DVDCommandBlock*)LS(void*, 0x6DC));
                        OSCancelThread(&gDataDecompressorValues.t);
                        StartThreadForReadingFromDisk();
                        OSCancelThread(&lbl_803C6CF8.thread2);
                        OSCreateThread(&lbl_803C6CF8.thread2, fn_800A77A0, NULL,
                                       lbl_802EAF80 + 0x1000, 0x1000, 8, 1);
                        OSResumeThread(&lbl_803C6CF8.thread2);
                        LS(u8, 0x714) = 1;
                        {
                            AssetLoadInstructions* instructions = LS(AssetLoadInstructions*, 0x71C);
                            OSReport("\nDecode Error Retry : EntryNo%d %x Err:%d\n",
                                     LS(s32, 0x718), instructions->diskLocation, (s8)gDataDecompressorValues.error);
                        }
                    }
                }
            } break;
            case 1: {
                s8 cbStatus = (s8)DVDGetCommandBlockStatus((DVDCommandBlock*)LS(void*, 0x6DC));
                if (cbStatus == 0 || cbStatus == 10) {
                    LS(s32, 0x6E8) = 0;
                    LS(void*, 0x708) = LS(void*, 0x6F8);
                    LS(s32, 0x6F0) = LS(s32, 0x6EC);
                    if (LS(u8, 0x6D8) != 0) {
                        LS(s32, 0x6D4) = LS(s32, 0x6D0);
                    }
                    DVDFastOpen(LS(s32, 0x718), LS(DVDFileInfo*, 0x6DC));
                    if (LS(u8, 0x717) == 0) {
                        SetReadParameters(LS(AssetLoadInstructions*, 0x71C), LS(void*, 0x6FC), LS(void*, 0x700), 1);
                    } else if (LS(u8, 0x717) == 3) {
                        SetReadParameters(LS(AssetLoadInstructions*, 0x71C), LS(void*, 0x6FC), LS(void*, 0x700), 2);
                        LS(s32, 0x6C0) = LS(s32, 0x6C4);
                    }

                    {
                        s32 len = LS(s32, 0x6F0);
                        if (len >= 0x8000) {
                            len = 0x8000;
                        }
                        LS(s32, 0x6F4) = len;
                    }

                    if (LS(u8, 0x717) == 3) {
                        u32 alignedLen;
                        u32 idx;
                        DCInvalidateRange(LS(void*, 0x708), LS(u32, 0x6F4));
                        idx = LS(u8, 0x6C8);
                        alignedLen = (LS(u32, 0x6F4) + 0x1F) & ~0x1F;
                        ARQPostRequest((ARQRequest*)((u8*)&lbl_803C6CF8 + 0x63C + (idx << 5)), 0x7D0, 1, 0,
                                       LS(u32, 0x6C0), LS(u32, 0x708), alignedLen, fn_800A68D4);
                        LS(u8, 0x6C8) = (idx + 1) & 3;
                        LS(u32, 0x6C0) = LS(u32, 0x6C0) + alignedLen;
                    } else {
                        DVDReadAsyncPrio(LS(DVDFileInfo*, 0x6DC), LS(void*, 0x6F8), LS(s32, 0x6F4),
                                         LS(s32, 0x6E4) + LS(s32, 0x6E8), fn_800A7A80, 2);
                    }
                    LS(u8, 0x714) = 2;
                }
            } break;
            case 3:
                LS(u16, 0x714) = 1;
                if (LS(void*, 0x6FC) != NULL) {
                    unkLoadingCleanupRelated(LS(void*, 0x6FC));
                    LS(void*, 0x6FC) = NULL;
                }
                break;
            default:
                break;
            }
        }
    }
}

void fn_800A6C80(void) {
    LS(u8, 0x714) = 0;
    LS(u8, 0x722) = 0;
    if (LS(s8, 0x715) != 1) {
        DVDCBCallback cancelCallback;
        if (LS(u8, 0x717) == 0 || LS(u8, 0x717) == 3) {
            cancelCallback = cancelReadCallback1;
        } else {
            cancelCallback = cancelReadCallback2;
        }
        DVDCancelAsync((DVDCommandBlock*)LS(void*, 0x6DC), cancelCallback);
        ARQRemoveOwnerRequest(0x7D0);
    }
    LS(s32, 0x6F0) = 0;
    LS(s32, 0x710) = 0;
}

void fn_800A6D10(s32 arg) {
    BOOL interrupts = OSDisableInterrupts();
    u32 pos = LS(u32, 0x708) + arg;
    LS(u32, 0x708) = pos;
    if (pos >= LS(u32, 0x700)) {
        LS(u32, 0x708) = pos - LS(u32, 0x70C);
    }
    LS(u32, 0x710) = LS(u32, 0x710) - arg;
    if (LS(u8, 0x723) != 0) {
        s32 readPtr = LS(s32, 0x704);
        s32 remaining;
        LS(u8, 0x714) = 4;
        LS(u8, 0x723) = 0;
        if ((u32)readPtr < LS(u32, 0x708)) {
            remaining = LS(u32, 0x708) - readPtr;
        } else {
            remaining = LS(u32, 0x700) - readPtr;
        }
        if (remaining > LS(s32, 0x6F0)) {
            remaining = LS(s32, 0x6F0);
        }
        if (remaining >= 0x4000) {
            remaining = 0x4000;
        }
        if (remaining != 0) {
            DVDReadAsyncPrio(LS(DVDFileInfo*, 0x6DC), (void*)readPtr, remaining,
                             LS(s32, 0x6E4) + LS(s32, 0x6E8), fn_800A6F94, 2);
        }
    }
    OSRestoreInterrupts(interrupts);
}

void fn_800A6E24(AssetLoadInstructions* instructions, void* dest, s32 length) {
    LS(u8, 0x714) = 0;
    LS(u8, 0x722) = 0;
    if (LS(s8, 0x715) != 1) {
        DVDCBCallback cancelCallback;
        if (LS(u8, 0x717) == 0 || LS(u8, 0x717) == 3) {
            cancelCallback = cancelReadCallback1;
        } else {
            cancelCallback = cancelReadCallback2;
        }
        DVDCancelAsync((DVDCommandBlock*)LS(void*, 0x6DC), cancelCallback);
        ARQRemoveOwnerRequest(0x7D0);
    }
    LS(void*, 0x71C) = instructions;
    LS(s32, 0x6E8) = 0;
    LS(s32, 0x6E4) = instructions->diskLocation;
    LS(u32, 0x6EC) = (instructions->compressedSize + 0x1F) & ~0x1F;
    LS(u32, 0x6F0) = LS(u32, 0x6EC);
    LS(void*, 0x704) = dest;
    LS(void*, 0x708) = dest;
    LS(void*, 0x6F8) = dest;
    LS(u32, 0x710) = 0;
    LS(u8, 0x723) = 0;
    LS(s32, 0x70C) = length;
    LS(void*, 0x700) = (u8*)dest + length;

    while (LS_VOL(u8, 0x715) != 1) {
    }

    DVDFastOpen(LS(s32, 0x718), LS(DVDFileInfo*, 0x6DC));
    LS(u16, 0x714) = 0x400;
    {
        s32 readPtr = LS(s32, 0x704);
        s32 remaining;
        if ((u32)readPtr < LS(u32, 0x708)) {
            remaining = LS(u32, 0x708) - readPtr;
        } else {
            remaining = LS(u32, 0x700) - readPtr;
        }
        if (remaining > LS(s32, 0x6F0)) {
            remaining = LS(s32, 0x6F0);
        }
        if (remaining >= 0x4000) {
            remaining = 0x4000;
        }
        if (remaining != 0) {
            DVDReadAsyncPrio(LS(DVDFileInfo*, 0x6DC), (void*)readPtr, remaining,
                             LS(s32, 0x6E4) + LS(s32, 0x6E8), fn_800A6F94, 2);
        }
    }
}

void fn_800A6F94(s32 result, DVDFileInfo* fileInfo) {
    if (result > 0) {
        LS(s32, 0x704) = LS(s32, 0x704) + result;
        LS(u32, 0x710) = LS(u32, 0x710) + result;
        LS(s32, 0x6E8) = LS(s32, 0x6E8) + result;
        LS(s32, 0x6F0) = LS(s32, 0x6F0) - result;
        if (LS(u32, 0x704) == LS(u32, 0x700)) {
            LS(void*, 0x704) = LS(void*, 0x6F8);
        }

        if (LS(u32, 0x710) == LS(u32, 0x70C)) {
            LS(u8, 0x723) = 1;
            LS(u8, 0x714) = 0;
        } else if (LS(u32, 0x6E8) == LS(u32, 0x6EC)) {
            LS(u16, 0x714) = 1;
        } else {
            s32 remaining;
            if (LS(u32, 0x704) < LS(u32, 0x708)) {
                remaining = LS(u32, 0x708) - LS(u32, 0x704);
            } else {
                remaining = LS(u32, 0x700) - LS(u32, 0x704);
            }
            if (remaining > LS(s32, 0x6F0)) {
                remaining = LS(s32, 0x6F0);
            }
            if (remaining >= 0x4000) {
                remaining = 0x4000;
            }
            if (remaining != 0) {
                DVDReadAsyncPrio(LS(DVDFileInfo*, 0x6DC), LS(void*, 0x704), remaining,
                                 LS(s32, 0x6E4) + LS(s32, 0x6E8), fn_800A6F94, 2);
            }
        }
    } else if (result == -3) {
        LS(u8, 0x714) = 0;
        DVDClose(fileInfo);
    }
}

void* ARAMTransfer(void* file, s32 arg1, s32 arg2, s32 arg3) {
    AssetLoadInstructions* instructions = (AssetLoadInstructions*)file;
    void* buffer = (void*)arg1;
    void* ret;
    u32 aligned;
    s32 loadType;

    LS(u8, 0x714) = 0;
    LS(u8, 0x722) = 0;
    if (LS(s8, 0x715) != 1) {
        DVDCBCallback cancelCallback;
        if (LS(u8, 0x717) == 0 || LS(u8, 0x717) == 3) {
            cancelCallback = cancelReadCallback1;
        } else {
            cancelCallback = cancelReadCallback2;
        }
        DVDCancelAsync((DVDCommandBlock*)LS(void*, 0x6DC), cancelCallback);
        ARQRemoveOwnerRequest(0x7D0);
    }

    LS(u16, 0x720) = (u16)instructions->compressionConstants;
    gDataDecompressorValues.compressedFlag = instructions->compressionFlag;
    LS(s32, 0x6E8) = 0;
    LS(s32, 0x6F4) = 0;
    LS(u32, 0x6E0) = *(u32*)((u8*)instructions + 4);
    LS(s32, 0x6E4) = instructions->diskLocation;
    LS(void*, 0x71C) = instructions;
    LS(u8, 0x717) = arg2;

    while (LS_VOL(u8, 0x715) != 1) {
    }

    DVDFastOpen(LS(s32, 0x718), LS(DVDFileInfo*, 0x6DC));
    aligned = (instructions->compressedSize + 0x1F) & ~0x1F;

    if (arg1 == 0) {
        s32 lt = LS(u8, 0x717);
        if (lt == 0 || lt == 3) {
            u32 size = LS(u32, 0x6E0) & 0x0FFFFFFF;
            buffer = _OSAllocFromHeap(0x20, (size + 0x1F) & ~0x1F);
        } else if (lt == 2) {
            OSPanic("dvdsys.c", 0x22A, "ARAM\x92\xbc\x90\xda\x93]\x91\x97\x82\xcc\x8f\xea\x8d\x87\x82\xcd\x93\xc7\x8d\x9e\x90\xe6\x83\x41\x83\x68\x83\x8c\x83\x58\x82\xaa\x95\x4b\x90\x7b\x82\xc5\x82\xb7\x81\x42\n");
        } else {
            buffer = _OSAllocFromHeap(0x20, aligned);
        }
    }

    if (arg3 == 0) {
        if (LS(u8, 0x717) == 3) {
            OSPanic("dvdsys.c", 0x234, "ARAM->RAM\x93]\x91\x97\x82\xcc\x8f\xea\x8d\x87\x82\xcd\x41\x52\x41\x4d\x83\x41\x83\x68\x83\x8c\x83\x58\x82\xaa\x95\x4b\x90\x7b\x82\xc5\x82\xb7\x81\x42\n");
        }
        if (LS(u8, 0x717) == 4) {
            OSPanic("dvdsys.c", 0x238, "ARAM->RAM\x93]\x91\x97\x82\xcc\x8f\xea\x8d\x87\x82\xcd\x41\x52\x41\x4d\x83\x41\x83\x68\x83\x8c\x83\x58\x82\xaa\x95\x4b\x90\x7b\x82\xc5\x82\xb7\x81\x42\n");
        }
    }

    LS(s32, 0x6EC) = aligned;
    LS(s32, 0x6F0) = aligned;
    LS(s32, 0x6F4) = (aligned < 0x8000) ? aligned : 0x8000;

    ret = buffer;
    loadType = LS(u8, 0x717);
    if (loadType == 0) {
        void* alloc;
        LS(void*, 0x700) = buffer;
        alloc = allocateAlignedMemoryBlock(0x20, 0x20000);
        LS(void*, 0x6FC) = alloc;
        buffer = alloc;
        SetReadParameters(instructions, alloc, LS(void*, 0x700), 1);
    } else if (loadType == 2) {
        void* alloc;
        OSInitSemaphore((OSSemaphore*)&lbl_803C6CF8._630, 3);
        LS(void*, 0x6C4) = buffer;
        LS(void*, 0x6C0) = buffer;
        alloc = allocateAlignedMemoryBlock(0x20, 0x20000);
        buffer = alloc;
        LS(void*, 0x6FC) = alloc;
        LS(void*, 0x6BC) = (u8*)alloc + 0x20000;
        LS(u8, 0x6C8) = 0;
    } else if (loadType == 3) {
        void* alloc;
        LS(s32, 0x6C4) = arg3;
        LS(s32, 0x6C0) = arg3;
        LS(void*, 0x700) = buffer;
        alloc = allocateAlignedMemoryBlock(0x20, 0x20000);
        LS(void*, 0x6FC) = alloc;
        LS(u8, 0x6C8) = 0;
        buffer = alloc;
        SetReadParameters(instructions, alloc, LS(void*, 0x700), 2);
    } else if (loadType == 4) {
        LS(s32, 0x6F4) = LS(s32, 0x6F0);
        LS(s32, 0x6C4) = arg3;
        LS(s32, 0x6C0) = arg3;
        LS(void*, 0x700) = buffer;
    }

    LS(void*, 0x6F8) = buffer;
    LS(void*, 0x708) = buffer;
    LS(u16, 0x714) = 0x200;
    loadType = LS(u8, 0x717);
    if (loadType == 3 || loadType == 4) {
        u32 idx;
        u32 alignedLen;
        DCInvalidateRange(LS(void*, 0x708), LS(u32, 0x6F4));
        idx = LS(u8, 0x6C8);
        alignedLen = (LS(u32, 0x6F4) + 0x1F) & ~0x1F;
        ARQPostRequest((ARQRequest*)((u8*)&lbl_803C6CF8 + 0x63C + (idx << 5)), 0x7D0, 1, 0,
                       LS(u32, 0x6C0), LS(u32, 0x708), alignedLen, fn_800A68D4);
        LS(u8, 0x6C8) = (idx + 1) & 3;
        LS(u32, 0x6C0) = LS(u32, 0x6C0) + alignedLen;
    } else {
        DVDReadAsyncPrio(LS(DVDFileInfo*, 0x6DC), buffer, LS(s32, 0x6F4), LS(s32, 0x6E4), fn_800A7A80, 2);
    }

    if (LS(u8, 0x6D8) != 0) {
        u32 t = aligned * 0xB4;
        u32 v = 0xB4;
        if ((t >> 21) >= 0xB4) {
            v = t >> 22;
        }
        LS(u32, 0x6D0) = v;
        LS(u32, 0x6D4) = v;
    }

    return ret;
}
