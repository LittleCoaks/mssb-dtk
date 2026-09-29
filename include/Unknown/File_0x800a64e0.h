#ifndef __UNKNOWN_FILE_0X800A64E0_H_
#define __UNKNOWN_FILE_0X800A64E0_H_

#include "types.h"
#include "Dolphin/os.h"

typedef struct 
{
    u32 compressionConstants;

    struct {
        u8 compressionFlag:2;
        u8 unused:2;
        u32 originalDiskSize:28;
    };
    u32 diskLocation;
    u32 compressedSize;
} AssetLoadInstructions;

u32 ReadBits(u32 bits);

void SetReadParameters(AssetLoadInstructions * instructions, void* pCompressedData, void*pOutData, BOOL param_4);

void *ReadDataFromDisk(void * /* unused */);

void DecompressDiskData();

typedef struct
{
    OSThread t ATTRIBUTE_ALIGN(16);       // 0x000
    OSSemaphore s[2] ATTRIBUTE_ALIGN(16); // 0x320

    int BytesToRead;          // 0x338
    size_t CachedBytesToRead; // 0x33C
    int volatile ReadOffset;  // 0x340
    u32 bitBuffer;            // 0x344
    u8 * volatile DataWriteBottom;      // 0x348
    u8 *DataReadBottom;       // 0x34C
    u8 *CachedDataReadBottom; // 0x350
    void *DataReadTop;        // 0x354
    u8 * volatile DataWriteTop;         // 0x358
    void *pendingBlock;       // 0x35C

    s8 volatile segmentCount; // 0x360
    u8 BitsInBuffer;          // 0x361
    u8 LookBackSize;          // 0x362
    u8 RepetitionSize;        // 0x363
    u8 error;                 // 0x364
    s8 compressedFlag;        // 0x365
    u8 ShouldWriteDataFlag;   // 0x366
} DataVars;

extern DataVars gDataDecompressorValues;

void StartThreadForReadingFromDisk(void);

#endif // !__UNKNOWN_FILE_0X800A64E0_H_
