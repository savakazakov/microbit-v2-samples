#include "MicroBit.h"
#include "MicroBitRadar.h"
#include "CodalDmesg.h"
#include <string>

MicroBit uBit;
MicroBitRadar* radar;

void onPressedA(MicroBitEvent e)
{
    // 8 kHz.
    uBit.io.speaker.setAnalogPeriodUs(125);
    uBit.io.speaker.setAnalogValue(512);
}

void onReleasedA(MicroBitEvent e)
{
    uBit.io.speaker.setAnalogValue(0);
}

void onPressedB(MicroBitEvent e)
{
    // 2.7 kHz.
    // uBit.io.speaker.setAnalogPeriodUs(370);
    // uBit.io.speaker.setAnalogValue(512);
    radar->pingTest();
}

void onReleasedB(MicroBitEvent e)
{
    // uBit.io.speaker.setAnalogValue(0);
}

int main()
{
    uBit.display.print("S");
    uBit.serial.printf("uBit constructed!\n"); // REMOVE PRINTING.
    uBit.init();
    uBit.serial.printf("After uBit.init()\n"); // REMOVE PRINTING.

    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, DEVICE_BUTTON_EVT_UP, onReleasedA, MESSAGE_BUS_LISTENER_IMMEDIATE);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, DEVICE_BUTTON_EVT_DOWN, onPressedA, MESSAGE_BUS_LISTENER_IMMEDIATE);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, DEVICE_BUTTON_EVT_UP, onReleasedB, MESSAGE_BUS_LISTENER_IMMEDIATE);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, DEVICE_BUTTON_EVT_DOWN, onPressedB, MESSAGE_BUS_LISTENER_IMMEDIATE);

    uBit.serial.printf("Before initializing radar.\n"); // REMOVE PRINTING.

    // Create and initialise the radar object.
    radar = new MicroBitRadar(&uBit);
    radar->init();

    // TODO configure this:
    uBit.audio.micFilter->setBeta(1.0f);

    // radar->fft_test();

    uBit.serial.printf("After initializing radar.\n"); // REMOVE PRINTING.

    while (true)
    {
        uBit.sleep(2000);

        DMESG("In loop\n");
    }
}