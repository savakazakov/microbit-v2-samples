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
    radio(),
    thermometer(),
    audio(io.P0, io.speaker, adc, io.microphone, io.runmic)
{
    // Initialise the fiber scheduler.
    scheduler_init(messageBus);

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

    // FFT stuff.
    if(mic == NULL)
    {
        mic = adc.getChannel(io.microphone);
        mic->setGain(7, 0);
    }

    if(processor == NULL)
        processor = new StreamNormalizer(mic->output, 1.0f, true, DATASTREAM_FORMAT_8BIT_SIGNED, 10);

    if (fft == NULL)
        fft = new MicroBitAudioProcessor(processor->output);
}

codal::MicroBitRadar::~MicroBitRadar()
{
    
}

void codal::MicroBitRadar::fft_test()
{
    DMESG("START of FFT.");

    io.runmic.setDigitalValue(1);
    io.runmic.setHighDrive(true);

    // Start fft running
    fft->startRecording();

    while (1)
    {
        // TODO - de-noise : if last X samples are same - display ect.
        // The output values depend on the input type (DATASTREAM_FORMAT_8BIT_SIGNED) and the size
        // of the FFT - which is changed using the 'AUDIO_SAMPLES_NUMBER' in
        // MicroBitAudioProcessor.h default is 1024
        fiber_sleep(100);
        int freq = fft->getFrequency();
        DMESG("%s %d", "frequency: ", freq);
        if (freq > 0)
            uBit.display.print("?");
        if (freq > 530)
            uBit.display.print("C");
        if (freq > 600)
            uBit.display.print("D");
        if (freq > 680)
            uBit.display.print("E");
        if (freq > 710)
            uBit.display.print("F");
        if (freq > 800)
            uBit.display.print("G");
        if (freq > 900)
            uBit.display.print("A");
        if (freq > 1010)
            uBit.display.print("B");
        if (freq > 1050)
            uBit.display.print("?");
    }
}

/**
 * TODO: Make sure I need this.
*/
void MicroBitRadar::periodicCallback()
{
    DMESG("Callback!");
}