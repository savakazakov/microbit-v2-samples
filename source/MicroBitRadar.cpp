#include "MicroBitRadar.h"
#include "CodalDmesg.h"

using namespace codal;

MicroBitRadar* MicroBitRadar::instance = NULL;
// #define CODAL_DEBUG
// #define DEVICE_DBG

/**
 * Constructor.
 *
 * Create the Radar component, which includes member variables
 * that represent various device drivers used for the calculations
 * performed by the radar component.
 */
MicroBitRadar::MicroBitRadar() :
    systemTimer(NRF_TIMER1, TIMER1_IRQn),
    adcTimer(NRF_TIMER2, TIMER2_IRQn),
    capTouchTimer(NRF_TIMER3, TIMER3_IRQn),
    timer(systemTimer),
    messageBus(),
    adc(adcTimer, 91),
    touchSensor(capTouchTimer),
    io(adc, touchSensor),
    serial(io.usbTx, io.usbRx, NRF_UARTE0),
    _i2c(io.sda, io.scl),
    i2c(io.P20, io.P19),
    audio(io.P0, io.speaker, adc, io.microphone, io.runmic)
{
    // Clear our status
    // TODO: Make sure I need this.
    status = 0;

    // If we are the first instance created, schedule it for on demand activation.
    // TODO: Make sure I need this.
    if (MicroBitRadar::instance == NULL)
        MicroBitRadar::instance = this;

    // Add pullup resisitor to IRQ line (it's floating ACTIVE LO)
    // io.irq1.getDigitalValue();
    // io.irq1.setPull(PullMode::Up);
    // io.irq1.setActiveLo();

    // TODO: Make sure I need this.
    _i2c.setFrequency(400000);

    // Bring up internal speaker as high drive.
    // TODO: Make sure I need this.
    io.speaker.setHighDrive(true);
}

codal::MicroBitRadar::~MicroBitRadar()
{
    
}

/**
 * TODO: Make sure I need this.
*/
void MicroBitRadar::periodicCallback()
{
    DMESG("Callback!");
}