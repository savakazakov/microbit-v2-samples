// Substitute this for the exact header files at some point.
#include "MicroBit.h"
#include "samples/Tests.h"
#include "Button.h"
#include "CodalDmesg.h"
#include "MicroBitDisplay.h"
#include "MicroBitIO.h"

static const MatrixPoint ledMatrixPositions[5*5] =
{
    {0,0},{0,1},{0,2},{0,3},{0,4},
    {1,0},{1,1},{1,2},{1,3},{1,4},
    {2,0},{2,1},{2,2},{2,3},{2,4},
    {3,0},{3,1},{3,2},{3,3},{3,4},
    {4,0},{4,1},{4,2},{4,3},{4,4}
};

// MicroBit uBit;

adcTimer(NRF_TIMER2, TIMER2_IRQn),

    capTouchTimer(NRF_TIMER3, TIMER3_IRQn),

    NRF52Pin *ledRowPins[5] = {&io.row1, &io.row2, &io.row3, &io.row4, &io.row5};
NRF52Pin *ledColPins[5] = {&io.col1, &io.col2, &io.col3, &io.col4, &io.col5};
const MatrixMap ledMatrixMap = {5, 5, 5, 5, (Pin **)ledRowPins, (Pin **)ledColPins, ledMatrixPositions};
MicroBitDisplay display(ledMatrixMap);
MicroBitIO io;
MessageBus bus;

Button buttonA(io.P5, DEVICE_ID_BUTTON_A, DEVICE_BUTTON_ALL_EVENTS, ACTIVE_LOW);
Button buttonB(io.P11, DEVICE_ID_BUTTON_B, DEVICE_BUTTON_ALL_EVENTS, ACTIVE_LOW);
    // MicroBitDisplay display;

    int main()
{
    scheduler_init(bus);

    display.scroll(":)");
    
    // io.speaker.setAnalogValue(512);
    // // 2.7 kHz.
    // io.speaker.setAnalogPeriodUs(370);
    // // TODO: Read more about this.
    // io.speaker.setHighDrive(true);

    // // 8 kHz.
    // io.speaker.setAnalogPeriodUs(125);
    io.speaker.setHighDrive(true);

    while(1)
    {
        fiber_sleep(1000);
        DMESG("In loop\n");
    }
}

void onPressedA(MicroBitEvent e)
{
    io.speaker.setAnalogPeriodUs(370);
    io.speaker.setAnalogValue(512);
}

void onReleasedA(MicroBitEvent e)
{
    io.speaker.setAnalogValue(0);
}

void onPressedB(MicroBitEvent e)
{
    io.speaker.setAnalogPeriodUs(125);
    io.speaker.setAnalogValue(512);
}

void onReleasedB(MicroBitEvent e)
{
    io.speaker.setAnalogValue(0);
}