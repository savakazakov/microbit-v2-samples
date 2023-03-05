#ifndef RADAR
#define RADAR

// Substitute this for the components that are needed by the Radar component.
#include "MicroBit.h"
// #include "Timer.h"
// #include "MicroBitDevice.h"
// #include "CodalDmesg.h"

void onPressedA(MicroBitEvent e);
void onReleasedA(MicroBitEvent e);
void onPressedB(MicroBitEvent e);
void onReleasedB(MicroBitEvent e);

#endif