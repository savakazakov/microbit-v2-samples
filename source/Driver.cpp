#include "MicroBit.h"
#include "MicroBitRadar.h"
#include "CodalDmesg.h"
#include <string>
// #include "MicroBitAudioProcessor.h"
// #include "arm_math.h"

MicroBit uBit;
MicroBitRadar* radar;

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
    uBit.serial.printf("uBit constructed!\n"); // REMOVE PRINTING.
    uBit.init();
    uBit.display.scroll(":)");
    uBit.serial.printf("After uBit.init()\n"); // REMOVE PRINTING.

    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, DEVICE_BUTTON_EVT_UP, onReleasedA,
                      MESSAGE_BUS_LISTENER_IMMEDIATE);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, DEVICE_BUTTON_EVT_DOWN, onPressedA,
                      MESSAGE_BUS_LISTENER_IMMEDIATE);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, DEVICE_BUTTON_EVT_UP, onReleasedB,
                      MESSAGE_BUS_LISTENER_IMMEDIATE);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, DEVICE_BUTTON_EVT_DOWN, onPressedB,
                      MESSAGE_BUS_LISTENER_IMMEDIATE);

    // uBit.messageBus.listen(MICROBIT_ID_RADIO, DEVICE_BUTTON_EVT_DOWN, onPressedB,
    //                        MESSAGE_BUS_LISTENER_IMMEDIATE);

    // io.speaker.setAnalogValue(512);
    // 2.7 kHz.
    // uBit.io.speaker.setAnalogPeriodUs(370);
    // TODO: Read more about this.


    uBit.serial.printf("Before initializing radar.\n"); // REMOVE PRINTING.

    // uBit.serial.printf("getSerialNumber = %d\n", (int)uBit.getSerialNumber()); // REMOVE PRINTING.
    uBit.serial.printf("microbit_serial_number = %d\n", (int)microbit_serial_number());            // REMOVE PRINTING.

    std::string str = std::to_string(microbit_serial_number());
    ManagedString ms = ManagedString(str.c_str());
    uBit.display.scroll(ms);
    
    // uBit.serial.printf("microbit_friendly_name = %s\n", microbit_friendly_name()); // REMOVE
    // PRINTING. microbit_serial_number(); microbit_friendly_name();
    radar = new MicroBitRadar(&uBit);
    radar->init();
        // radar->radioTest();

    uBit.serial.printf("After initializing radar.\n"); // REMOVE PRINTING.

    while (1)
    {
        uBit.sleep(1000);
        DMESG("In loop\n");

        radar->periodicCallback();
        radar->uBit->display.scroll("YES\n");
    }
}