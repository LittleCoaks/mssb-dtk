#ifndef __UNKNOWN_FILE_0X8004E504_H_
#define __UNKNOWN_FILE_0X8004E504_H_

#include "mssbTypes.h"

// With isCharID clear each portN is a grid slot; set, each is a character
// whose grid slot is looked up. A negative value leaves that port alone.
void storeCursorLocOrCharIDs(BOOL isCharID, int port0, int port1, int port2, int port3);

#endif // !__UNKNOWN_FILE_0X8004E504_H_
