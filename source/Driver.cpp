#include "MicroBit.h"
#include "MicroBitRadar.h"
#include "CodalDmesg.h"
#include "MicroBitAudioProcessor.h"
#include "arm_math.h"

MicroBit uBit;
MicroBitRadar *radar;

void onPressedA(MicroBitEvent e)
{
    uBit.io.speaker.setAnalogPeriodUs(125);
    uBit.io.speaker.setAnalogValue(512);
}

void onReleasedA(MicroBitEvent e)
{
    uBit.io.speaker.setAnalogValue(0);
}

void onPressedB(MicroBitEvent e)
{
    uBit.io.speaker.setAnalogPeriodUs(370);
    uBit.io.speaker.setAnalogValue(100);
}

void onReleasedB(MicroBitEvent e)
{
    uBit.io.speaker.setAnalogValue(0);
}

int main()
{
    uBit.init();
    uBit.display.scroll(":)");
    DMESG(":)\n");

    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, DEVICE_BUTTON_EVT_UP, onReleasedA,
                      MESSAGE_BUS_LISTENER_IMMEDIATE);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, DEVICE_BUTTON_EVT_DOWN, onPressedA,
                      MESSAGE_BUS_LISTENER_IMMEDIATE);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, DEVICE_BUTTON_EVT_UP, onReleasedB,
                      MESSAGE_BUS_LISTENER_IMMEDIATE);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, DEVICE_BUTTON_EVT_DOWN, onPressedB,
                      MESSAGE_BUS_LISTENER_IMMEDIATE);

    // io.speaker.setAnalogValue(512);
    // 2.7 kHz.
    // uBit.io.speaker.setAnalogPeriodUs(370);
    // TODO: Read more about this.
    uBit.io.speaker.setHighDrive(true);

    // 8 kHz.
    // uBit.io.speaker.setAnalogPeriodUs(125);
    // uBit.io.speaker.setHighDrive(true);

    radar = new codal::MicroBitRadar();

    radar->fft_test();

    while (1)
    {
        uBit.sleep(2000);
        // display.scroll("X");
        DMESG("In loop\n");

        // DMESGF("Test1\n");
        // DMESGN("Test2\n");
        // uBit.serial.printf("Temperature\n");
    }
}