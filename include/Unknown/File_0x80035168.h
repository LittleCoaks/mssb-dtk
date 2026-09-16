#ifndef __UNKNOWN_FILE_0X80035168_H_
#define __UNKNOWN_FILE_0X80035168_H_

#include "mssbTypes.h"
#include "Unknown/File_0x80034e20.h"

/* The 2D UI draw pass: walks menuGraphicsStructures[uiDrawLoopStart ..
 * uiDrawLoopEnd), steps each record's frame by rate per playMode, draws it,
 * then runs the text pass. */
void maybeProcessUIUpdates(void);

#endif // !__UNKNOWN_FILE_0X80035168_H_
