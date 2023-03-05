#include "Radar.h"

// MicroBitI2C i2c = MicroBitI2C(I2C_SDA0, I2C_SCL0);
// MicroBitAccelerometer accelerometer = MicroBitAccelerometer(i2c);
// MicroBitDisplay display;
// MessageBus bus;

// Timers required for the initialization of the IO component.
NRFLowLevelTimer systemTimer(NRF_TIMER1, TIMER1_IRQn);
NRFLowLevelTimer adcTimer(NRF_TIMER2, TIMER2_IRQn);
NRFLowLevelTimer capTouchTimer(NRF_TIMER3, TIMER3_IRQn);
Timer timer(systemTimer);

// Initializing the IO.
NRF52ADC adc(adcTimer, 91);
NRF52TouchSensor touchSensor(capTouchTimer);
MicroBitIO io(adc, touchSensor);

// Required for events.
MessageBus messageBus;

// For debugging purposes.
Button buttonA(io.P5, DEVICE_ID_BUTTON_A, DEVICE_BUTTON_ALL_EVENTS, ACTIVE_LOW);

// Initializing the display.
static const MatrixPoint ledMatrixPositions[5*5] =
{
    {0,0},{0,1},{0,2},{0,3},{0,4},
    {1,0},{1,1},{1,2},{1,3},{1,4},
    {2,0},{2,1},{2,2},{2,3},{2,4},
    {3,0},{3,1},{3,2},{3,3},{3,4},
    {4,0},{4,1},{4,2},{4,3},{4,4}
};
NRF52Pin *ledRowPins[5]{&io.row1, &io.row2, &io.row3, &io.row4, &io.row5};
NRF52Pin *ledColPins[5]{&io.col1, &io.col2, &io.col3, &io.col4, &io.col5};
const MatrixMap ledMatrixMap{5, 5, 5, 5, (Pin**)ledRowPins, (Pin**)ledColPins, ledMatrixPositions};
MicroBitDisplay display(ledMatrixMap);

int main()
{
    scheduler_init(messageBus);

    display.scroll(":)");

    // io.speaker.setAnalogValue(512);
    // // 2.7 kHz.
    // io.speaker.setAnalogPeriodUs(370);
    // // TODO: Read more about this.
    // io.speaker.setHighDrive(true);

    // // 8 kHz.
    // io.speaker.setAnalogPeriodUs(125);
    // io.speaker.setHighDrive(true);

    while (1)
    {
        fiber_sleep(1000);
        DMESG("In loop\n");
    }
}

// void onPressedA(MicroBitEvent e)
// {
//     io.speaker.setAnalogPeriodUs(370);
//     io.speaker.setAnalogValue(512);
// }

// void onReleasedA(MicroBitEvent e)
// {
//     io.speaker.setAnalogValue(0);
// }

// void onPressedB(MicroBitEvent e)
// {
//     io.speaker.setAnalogPeriodUs(125);
//     io.speaker.setAnalogValue(512);
// }

// void onReleasedB(MicroBitEvent e)
// {
//     io.speaker.setAnalogValue(0);
// }