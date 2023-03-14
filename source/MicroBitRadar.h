#ifndef MICROBIT_RADAR_H
#define MICROBIT_RADAR_H

// Substitute this for the components that are needed by the Radar component.
#include "MicroBit.h"
// #include "CodalDmesg.h"
// #include "MicroBitAudioProcessor.h"
// #include "StreamNormalizer.h"
// #include "Tests.h"
// #include "arm_math.h"
// #include "Timer.h"
// #include "MicroBitDevice.h"
// #include "CodalDmesg.h"

// #define MICROBIT_UBIT_AS_STATIC_OBJECT

// #ifdef MICROBIT_UBIT_AS_STATIC_OBJECT
// extern MicroBit uBit;
// #else
// extern MicroBit &uBit;
// #endif

// Status Flags
// #define MICROBIT_AUDIO_STATUS_DEEPSLEEP 0x0001
// #define CONFIG_DEFAULT_MICROPHONE_GAIN 0.1f

// Configurable options
// #ifndef CONFIG_AUDIO_MIXER_OUTPUT_LATENCY_US
// #define CONFIG_AUDIO_MIXER_OUTPUT_LATENCY_US                                                       
//     (uint32_t)((CONFIG_MIXER_BUFFER_SIZE / 2) * (1000000.0f / 44100.0f))
// #endif

namespace codal
{
    /**
     * Class definition for MicroBitRadar
     */
    class MicroBitRadar/*  : public CodalComponent */
    {
        public:
        // static MicroBitRadar *instance;                     // Primary instance of MicroBitRadar, on demand activated.
        // TODO: Make sure everything that is public, needs to be public.
        MicroBit* uBit;

        // FFT stuff.
        // static NRF52ADCChannel *mic;                // mic
        // static StreamNormalizer *processor;
        // static MicroBitAudioProcessor *fft;

        private:
        // bool speakerEnabled;                    // State of on board speaker
        // bool pinEnabled;                        // State of on auxiliary output pin
        // NRF52Pin *pin;                          // Auxiliary pin to route audio to
        // NRF52Pin &speaker;                      // Primary pin for onboard speaker
        // SoundEmojiSynthesizer synth;            // Synthesizer used bfor SoundExpressions
        // MixerChannel *soundExpressionChannel;   // Mixer channel associated with sound expression audio
        // NRF52PWM *pwm;                          // PWM driver used for sound generation (mixer output)
        // NRF52ADC &adc;                          // ADC from MicroBitConstructor
        // NRF52Pin &microphone;                   // Microphone pin passed from MicroBit constructor
        // NRF52Pin &runmic;                       // Runmic pin passed from MicroBit constructor

        // int micDriverTimeout;

        public:

        /**
         * Constructor.
         */
        MicroBitRadar(MicroBit* uBit);

        /**
         * Destructor.
         */
        ~MicroBitRadar();

        /**
         * TODO: Refine this comment.
         * TODO: Make sure I need periodic callback.
         * A periodic callback.
         * Used to trigger the radar algorithm.
         */
        virtual void periodicCallback();


        void init(/* MicroBit uBit, MicroBitRadio radio */);
        void radioTest();

        /**
         * Creates an example MicroBitAudioProcessor and then queries it for
         * results. Currently configured to use 1024 samples with 8bit signed data.
         */
        void fft_test();

        // TODO: Add all functions that I would like the radar to service.
        // Think about the API.
    };
}

#endif