#include "MicroBitRadar.h"
#include "CodalDmesg.h"
#include "arm_math.h"

using namespace codal;

MicroBitRadar *MicroBitRadar::instance = NULL;
NRF52ADCChannel *MicroBitRadar::mic = NULL;
StreamNormalizer *MicroBitRadar::processor = NULL;
MicroBitAudioProcessor *MicroBitRadar::fft = NULL;

/**
 * Constructor.
 *
 * Create the Radar component, which includes member variables
 * that represent various device drivers used for the calculations
 * performed by the radar component.
 */
MicroBitRadar::MicroBitRadar() :
    uBit()
{
    // If we are the first instance created, schedule it for on demand activation.
    // TODO: Make sure I need this.
    if (MicroBitRadar::instance == NULL)
        MicroBitRadar::instance = this;

    // Bring up internal speaker as high drive.
    // TODO: Make sure I need this.
    uBit.io.speaker.setHighDrive(true);

    // FFT stuff.
    if (MicroBitRadar::mic == NULL)
    {
        MicroBitRadar::mic = uBit.adc.getChannel(uBit.io.microphone);
        MicroBitRadar::mic->setGain(7, 0);
    }

    if (MicroBitRadar::processor == NULL)
    {
        MicroBitRadar::processor = new StreamNormalizer(mic->output, 1.0f, true, DATASTREAM_FORMAT_8BIT_SIGNED, 10);
    }

    if (MicroBitRadar::fft == NULL)
    {
        MicroBitRadar::fft = new MicroBitAudioProcessor(processor->output);
    }
}

codal::MicroBitRadar::~MicroBitRadar()
{
    
}

void codal::MicroBitRadar::fft_test()
{
    DMESG("START of FFT.");

    uBit.io.runmic.setDigitalValue(1);
    uBit.io.runmic.setHighDrive(true);

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