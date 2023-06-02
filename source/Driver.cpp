#include "MicroBit.h"
#include "MicroBitRadar.h"
#include "CodalDmesg.h"
#include <string>

MicroBit uBit;
MicroBitRadar* radar;

void onPressedA(MicroBitEvent e)
{
    // 8 / 2.7 kHz.
    uBit.io.speaker.setAnalogPeriodUs(PRIMARY_RADAR_PERIOD);
    uBit.io.speaker.setAnalogValue(DUTY_CYCLE_50);
}

void onReleasedA(MicroBitEvent e)
{
    uBit.io.speaker.setAnalogValue(DUTY_CYCLE_0);
}

void onPressedB(MicroBitEvent e)
{
    radar->distanceTest();
}

void onReleasedB(MicroBitEvent e)
{

}

int main()
{
    uBit.display.print("S");
    uBit.init();

    // Register the button event handlers.
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, DEVICE_BUTTON_EVT_UP, onReleasedA, MESSAGE_BUS_LISTENER_IMMEDIATE);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, DEVICE_BUTTON_EVT_DOWN, onPressedA, MESSAGE_BUS_LISTENER_IMMEDIATE);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, DEVICE_BUTTON_EVT_UP, onReleasedB, MESSAGE_BUS_LISTENER_IMMEDIATE);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, DEVICE_BUTTON_EVT_DOWN, onPressedB, MESSAGE_BUS_LISTENER_IMMEDIATE);

    // Create and initialise the radar object.
    radar = new MicroBitRadar(&uBit);
    radar->init();

    // TODO: configure this. Move it to Radar.
    uBit.audio.micFilter->setBeta(1.0f);

    while (true)
    {
        uBit.sleep(2000);

        DMESG("In driver loop.\n");
    }
}