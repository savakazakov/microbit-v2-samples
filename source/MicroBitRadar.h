#ifndef MICROBIT_RADAR_H
#define MICROBIT_RADAR_H

// Substitute this for the components that are needed by the Radar component.
#include "MicroBit.h"
#include "CodalDmesg.h"
#include "MicroBitAudioProcessor.h"
#include "StreamNormalizer.h"
#include "Tests.h"
// #include "Timer.h"
// #include "MicroBitDevice.h"
// #include "CodalDmesg.h"

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
    class MicroBitRadar : public CodalComponent
    {
        public:
        static MicroBitRadar *instance;                     // Primary instance of MicroBitRadar, on demand activated.
        // TODO: Make sure everything that is public, needs to be public.
        NRFLowLevelTimer systemTimer;
        NRFLowLevelTimer adcTimer;
        NRFLowLevelTimer capTouchTimer;
        Timer timer;
        MessageBus messageBus;
        NRF52ADC adc;
        NRF52TouchSensor touchSensor;
        MicroBitIO io;
        NRF52Serial serial;
        MicroBitI2C _i2c; // Internal I2C for motion sensors
        MicroBitI2C i2c;  // External I2C for edge connector

        // MicroBitPowerManager power;
        // MicroBitUSBFlashManager flash;
        // NRF52FlashManager internalFlash;
        // MicroBitStorage storage; // Persistent key value store
        // NRF52Pin *ledRowPins[5];
        // NRF52Pin *ledColPins[5];
        // const MatrixMap ledMatrixMap;
        // MicroBitDisplay display;
        // Button buttonA;
        // Button buttonB;
        // MultiButton buttonAB;
        // TouchButton logo;
        MicroBitRadio radio;
        MicroBitThermometer thermometer;
        MicroBitAudio audio;

        // FFT stuff.
        static NRF52ADCChannel *mic;
        static StreamNormalizer *processor;
        static MicroBitAudioProcessor *fft;

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
        MicroBitRadar();

        /**
         * Destructor.
         */
        ~MicroBitRadar();

        /**
         * Demand request from a component to enable the default instance of this audio pipeline
         */
        static void requestActivation();

        /**
         * post-constructor initialisation method
         */
        int enable();

        /**
         * Shut down the radar component.
         */
        int disable();

        /**
         * Post constructor initialisation method.
         */
        int init();

        /**
         * TODO: Refine this comment.
         * TODO: Make sure I need periodic callback.
         * A periodic callback.
         * Used to trigger the radar algorithm.
         */
        virtual void periodicCallback();

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