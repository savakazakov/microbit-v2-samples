#ifndef MICROBIT_RADAR_H
#define MICROBIT_RADAR_H

// Substitute this for the components that are needed by the Radar component.
#include "MicroBit.h"
#include "SerialStreamer.h"

// Speed of sound at 20 degrees Celsius in m/s (or millimeters/millisecond).
#define SOUND_VEL_MS                    343
// The maximum distance that is of mean to the application in meters.
#define MAX_DIST_MEASURE                20
// The maximum delay (in milliseconds) that is to be waited for a 
// sound signal to arrive after a radio signal has been observed.
#define MAX_SOUND_DELAY                 (int) (1000.0 * MAX_DIST_MEASURE / SOUND_VEL_MS) 

// The default MicroBitRadar communication parameters.
#define PRIMARY_RADAR_FREQUENCY         2700            // Translates to an analog period of 370 us.
#define PRIMARY_RADAR_PERIOD            370             // Translates to a frequency of 2700 Hz.
#define SECONDARY_RADAR_FREQUENCY       8000            // Translates to an analog period of 125 us.
#define SECONDARY_RADAR_PERIOD          125             // Translates to a frequency of 8000 Hz.
#define DUTY_CYCLE_50                   512             // Used to turn on the speaker.
#define DUTY_CYCLE_0                    0               // Used to turn on the speaker.
#define RADAR_THRESHOLD                 1000000         // Subject to calibration. Set to 1000000 if not sure
#define RADAR_ADC_FREQUENCY             100000          // In Hz.
#define RADAR_ADC_PERIOD                (1e6 / RADAR_ADC_FREQUENCY) // In microseconds.

// Events.
#define MICROBIT_RADAR_EVT_STOP_RECORDING 1

namespace codal
{
    /**
     * Class definition for MicroBitRadar
     */
    class MicroBitRadar/*  : public CodalComponent */
    {
        public:
        static MicroBitRadar*           instance; // Primary instance of MicroBitRadar, on demand activated.

        // TODO: Make sure everything that is public, needs to be public.
        MicroBit*                       uBit;
        CODAL_TIMESTAMP                 radioReceived = 0;
        CODAL_TIMESTAMP                 soundReceived = 0;
        
        // static NRF52ADCChannel *mic;
        // static SerialStreamer *streamer;
        // static StreamNormalizer *processor;
        // static LevelDetector *level;
        // static LevelDetectorSPL *levelSPL;
        // static MicroBitAudioProcessor *fft;

        // This has to be a max of 28 bytes
        typedef struct __attribute__((packed)) Payload
        {
            uint32_t serial;
        } Payload;

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
        // int testFreqCounter = 0;    // REMOVE
        // int testEventCodeCounter = 0;   // REMOVE

        /**
         * Constructor.
         */
        MicroBitRadar(MicroBit* uBit);

        /**
         * Destructor.
         */
        ~MicroBitRadar();

        /**
         * TODO: Make sure I need periodic callback.
         * A periodic callback.
         * Used to trigger the radar algorithm.
         */
        virtual void periodicCallback();

        void init();
        void radioTest();
        void micTest();
        void recordingTest();
        void distanceTest();
        void subscribeTest();
        void unsubscribeTest();

        /**
         * Creates an example MicroBitAudioProcessor and then queries it for
         * results. Currently configured to use 1024 samples with 8bit signed data.
         */
        void fftTest();

        friend void onRadarRadio(MicroBitEvent e);
        friend void onMaxSoundDelay(MicroBitEvent e);

        // TODO: Add all functions that I would like the radar to service.
        // Think about the API.
    };
}

#endif