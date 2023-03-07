#ifndef MICROBIT_RADAR_H
#define MICROBIT_RADAR_H

// Substitute this for the components that are needed by the Radar component.
#include "MicroBit.h"
#include "Timer.h"
#include "MicroBitDevice.h"
// #include "CodalDmesg.h"

// Status Flags
// #define MICROBIT_AUDIO_STATUS_DEEPSLEEP 0x0001
// #define CONFIG_DEFAULT_MICROPHONE_GAIN 0.1f

// Configurable options
// #ifndef CONFIG_AUDIO_MIXER_OUTPUT_LATENCY_US
// #define CONFIG_AUDIO_MIXER_OUTPUT_LATENCY_US                                                       \
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
        static MicroBitAudio *instance; // Primary instance of MicroBitAudio, on demand activated.
        Mixer2 mixer;                   // Multi channel audio mixer
        NRF52ADCChannel *mic;           // Microphone ADC Channel from uBit.IO
        StreamNormalizer *processor;    // Stream Normaliser instance
        StreamSplitter *splitter;       // Stream Splitter instance (8bit normalized output)
        StreamSplitter *rawSplitter;    // Stream Splitter instance (raw input)
        LevelDetector *level;           // Level Detector instance
        LevelDetectorSPL *levelSPL;     // Level Detector SPL instance
        LowPassFilter *micFilter;       // Low pass filter to remove high frequency noise on the mic

    private:
        bool speakerEnabled;                  // State of on board speaker
        bool pinEnabled;                      // State of on auxiliary output pin
        NRF52Pin *pin;                        // Auxiliary pin to route audio to
        NRF52Pin &speaker;                    // Primary pin for onboard speaker
        SoundEmojiSynthesizer synth;          // Synthesizer used bfor SoundExpressions
        MixerChannel *soundExpressionChannel; // Mixer channel associated with sound expression audio
        NRF52PWM *pwm;                        // PWM driver used for sound generation (mixer output)
        NRF52ADC &adc;                        // ADC from MicroBitConstructor
        NRF52Pin &microphone;                 // Microphone pin passed from MicroBit constructor
        NRF52Pin &runmic;                     // Runmic pin passed from MicroBit constructor

        int micDriverTimeout;

    public:
        SoundExpressions soundExpressions; // SoundExpression intepreter
        SoundOutputPin virtualOutputPin;   // Virtual PWM channel (backward compatibility).

        /**
         * Constructor.
         */
        MicroBitRadar();

        /**
         * Destructor.
         */
        ~MicroBitRadar();

        void onPressedA(MicroBitEvent e);

        void onReleasedA(MicroBitEvent e);

        void onPressedB(MicroBitEvent e);

        void onReleasedB(MicroBitEvent e);
    };
}

#endif