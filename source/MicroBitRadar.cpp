#include "MicroBitRadar.h"
#include "CodalDmesg.h"

using namespace codal;
// #define CODAL_DEBUG
// #define DEVICE_DBG

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
Button buttonB(io.P11, DEVICE_ID_BUTTON_B, DEVICE_BUTTON_ALL_EVENTS, ACTIVE_LOW);

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

MicroBitI2C _i2c(io.sda, io.scl);                   // Internal I2C for motion sensors
MicroBitI2C i2c(io.P20, io.P19);                    // External I2C for edge connector

NRF52Serial serial(io.usbTx, io.usbRx, NRF_UARTE0);
MicroBitPowerManager power(_i2c, io, systemTimer);
MicroBitUSBFlashManager flash(_i2c, io, power);
NRF52FlashManager internalFlash(MICROBIT_STORAGE_PAGE, 1, MICROBIT_CODEPAGESIZE);
MicroBitStorage storage(internalFlash, 0);

MicroBitRadio radio;
MicroBitThermometer thermometer;
Accelerometer &accelerometer(MicroBitAccelerometer::autoDetect(_i2c));
Compass &compass(MicroBitCompass::autoDetect(_i2c));
MicroBitCompassCalibrator compassCalibrator(compass, accelerometer, display, storage);
MicroBitAudio audio(io.P0, io.speaker, adc, io.microphone, io.runmic);
MicroBitLog logger(flash, power, serial);

void microbit_dmesg_flush()
{
    // #if CONFIG_ENABLED(DMESG_SERIAL_DEBUG)
    // #if DEVICE_DMESG_BUFFER_SIZE > 0
        if (codalLogStore.ptr > 0 /* && microbit_device_instance */)
        {
            for (uint32_t i=0; i<codalLogStore.ptr; i++)
                /*( (MicroBit *)microbit_device_instance)-> */serial.putc(codalLogStore.buffer[i]);

            codalLogStore.ptr = 0;
        }
    // #endif
    // #endif
}

int main()
{
    scheduler_init(messageBus);

    // #if CONFIG_ENABLED(DMESG_SERIAL_DEBUG)
    // #if DEVICE_DMESG_BUFFER_SIZE > 0
    // codal_dmesg_set_flush_fn(microbit_dmesg_flush);
    // #endif
    // #endif

    display.scroll(":)");
    DMESG(":)\n");

    messageBus.listen(MICROBIT_ID_BUTTON_A, DEVICE_BUTTON_EVT_UP, onReleasedA,
                      MESSAGE_BUS_LISTENER_IMMEDIATE);
    messageBus.listen(MICROBIT_ID_BUTTON_A, DEVICE_BUTTON_EVT_DOWN, onPressedA,
                      MESSAGE_BUS_LISTENER_IMMEDIATE);
    messageBus.listen(MICROBIT_ID_BUTTON_B, DEVICE_BUTTON_EVT_UP, onReleasedB,
                      MESSAGE_BUS_LISTENER_IMMEDIATE);
    messageBus.listen(MICROBIT_ID_BUTTON_B, DEVICE_BUTTON_EVT_DOWN, onPressedB,
                      MESSAGE_BUS_LISTENER_IMMEDIATE);

    // io.speaker.setAnalogValue(512);
    // 2.7 kHz.
    io.speaker.setAnalogPeriodUs(370);
    // TODO: Read more about this.
    io.speaker.setHighDrive(true);

    // 8 kHz.
    io.speaker.setAnalogPeriodUs(125);
    io.speaker.setHighDrive(true);

    while (1)
    {
        fiber_sleep(2000);
        // display.scroll("X");
        DMESG("In loop\n");
        // DMESGF("Test1\n");
        // DMESGN("Test2\n");
        // serial.printf("Temperature\n");
    }
}

void onPressedA(MicroBitEvent e)
{
    io.speaker.setAnalogPeriodUs(125);
    io.speaker.setAnalogValue(512);
}

void onReleasedA(MicroBitEvent e)
{
    io.speaker.setAnalogValue(0);
}

void onPressedB(MicroBitEvent e)
{
    io.speaker.setAnalogPeriodUs(370);
    io.speaker.setAnalogValue(512);
}

void onReleasedB(MicroBitEvent e)
{
    io.speaker.setAnalogValue(0);
}

codal::MicroBitRadar::~MicroBitRadar()
{
    
}
