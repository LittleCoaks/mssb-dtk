#include "Unknown/File_0x800a983c.h"
#include "Dolphin/pad.h"
#include "Dolphin/OS/OSSerial.h"

void initInputDevices(void) {
    PADInit();
    SISetSamplingRate(0);
}
