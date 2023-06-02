#include "MicroBitRadar.h"
#include "CodalDmesg.h"

using namespace codal;

MicroBitRadar *MicroBitRadar::instance = NULL;
// NRF52ADCChannel *MicroBitRadar::mic = NULL;
// MicroBitAudioProcessor *MicroBitRadar::fft = NULL;
// SerialStreamer *MicroBitRadar::streamer = NULL;
// StreamNormalizer *MicroBitRadar::processor = NULL;
// LevelDetector *MicroBitRadar::level = NULL;
// LevelDetectorSPL *MicroBitRadar::levelSPL = NULL;

static void onRadarRadio(MicroBitEvent e);
static void onRadarSound(MicroBitEvent e);
static void onMaxSoundDelay(MicroBitEvent e);

/**
 * Constructor.
 *
 * Create the Radar component, which includes member variables
 * that represent various device drivers used for the calculations
 * performed by the radar component.
 */
MicroBitRadar::MicroBitRadar(MicroBit *uBit)
{
    MicroBitRadar::uBit = uBit;

    // If we are the first instance created, schedule it for on demand activation.
    if (MicroBitRadar::instance == NULL)
        MicroBitRadar::instance = this;
}

/**
 * Internal constructor-initialiser.
 * TODO: Fix this comment.
 * TODO: Add anything that needs to be initialised prior radaring here.
 */
void MicroBitRadar::init()
{
    // Bring up internal speaker as high drive.
    uBit->io.speaker.setHighDrive(true);
    uBit->radio.enable();

    // Make sure I know exactly what these do.
    uBit->io.runmic.setDigitalValue(1);
    uBit->io.runmic.setHighDrive(true);

    uBit->adc.setSamplePeriod(RADAR_ADC_PERIOD);
    // TODO: Check this works
    uBit->adc.setDmaBufferSize(1024);
    
    // Start listening on the MicroBitRadio.
    uBit->messageBus.listen(DEVICE_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onRadarRadio, MESSAGE_BUS_LISTENER_IMMEDIATE);

    // Subscribe for a specific sound signal frequency.
    uint8_t eventCode = uBit->audio.fft->subscribe(PRIMARY_RADAR_FREQUENCY, RADAR_THRESHOLD);
    uBit->messageBus.listen(DEVICE_ID_AUDIO_PROCESSOR, eventCode, onRadarSound, MESSAGE_BUS_LISTENER_IMMEDIATE);

    // Start listening for an indication to stop the MicroBitAudioProcessor.
    uBit->messageBus.listen(DEVICE_ID_RADAR, MICROBIT_RADAR_EVT_STOP_RECORDING, onMaxSoundDelay,
                            MESSAGE_BUS_LISTENER_IMMEDIATE);
}

MicroBitRadar::~MicroBitRadar() {}

/**
 * TODO: Fix this comment.
 */
// void MicroBitRadar::subscribeTest()
// {
//     uBit->display.print("S");
//     testFreqCounter++;
//     uint8_t eventCode = uBit->audio.fft->subscribe(testFreqCounter * 500, DEFAULT_RADAR_THRESHOLD);
//     DMESG("eventCode = %d\n", eventCode);
// }

/**
 * TODO: Fix this comment.
 */
// void MicroBitRadar::unsubscribeTest()
// {
//     uBit->display.print("U");
//     uBit->audio.fft->unsubscribe(testEventCodeCounter++);
// }

/**
 * TODO: Fix this comment.
*/
REAL_TIME_FUNC
inline void MicroBitRadar::radioTest()
{
    // Construct a payload with the device's serial number.
    Payload payloadStruct = {
                                microbit_serial_number()
                            };

    // Serialise the struct.
    uint8_t* plBytes = reinterpret_cast<uint8_t *>(&payloadStruct);

    // Creates a PacketBuffer 4 bytes long.
    PacketBuffer packetBuf = PacketBuffer(plBytes, (int) sizeof(Payload));

    uBit->radio.datagram.send(packetBuf);
}

/**
 * TODO: Fix this comment.
 * Creates an example MicroBitAudioProcessor and then queries it for results.
 * Currently configured to use 1024 samples with 8bit signed data.
 */
void MicroBitRadar::fftTest()
{
    uBit->display.print("F");

    // Start running the FFT.
    uBit->audio.fft->startRecording();

    DMESG("After start recording.");    // REMOVE
    DMESG("Sample period in microseconds = %d", uBit->adc.getSamplePeriod()); // REMOVE

    uBit->sleep(1000);                  // REMOVE

    while (1)
    {
        // TODO - de-noise : if last X samples are same - display ect.
        // The output values depend on the input type (DATASTREAM_FORMAT_8BIT_SIGNED) and the size
        // of the FFT - which is changed using the 'AUDIO_SAMPLES_NUMBER' in
        // MicroBitAudioProcessor.h default is 1024
        uBit->sleep(500);
        int freq = uBit->audio.fft->getFrequency();
        DMESG("Frequency: %d", freq);
    }
}

/**
 * TODO: Fix this comment.
 * Ping test.
 */
REAL_TIME_FUNC
void MicroBitRadar::distanceTest()
{
    uBit->io.speaker.setAnalogPeriodUs(PRIMARY_RADAR_PERIOD); // 58.75 us.

    // Construct a payload with the device's serial number.
    Payload payloadStruct = {
                                microbit_serial_number()
                            };

    // Serialise the struct.
    uint8_t* plBytes = reinterpret_cast<uint8_t *>(&payloadStruct);

    // Creates a PacketBuffer 4 bytes long and send it.
    PacketBuffer packetBuf = PacketBuffer(plBytes, (int) sizeof(Payload));
    uBit->radio.datagram.send(packetBuf);

    // Pulse a sound signal.
    uBit->io.speaker.setAnalogValue(DUTY_CYCLE_50); // 54.8 us.
    system_timer_wait_ms(100);
    uBit->io.speaker.setAnalogValue(DUTY_CYCLE_0);
}

/**
 * TODO: Finish this comment.
 * TODO: Make sure to filter useless radio communication.
*/
REAL_TIME_FUNC
static void onRadarRadio(MicroBitEvent e)
{
    // Take care of the time critical functionality first.
    MicroBitRadar::instance->radioReceived = system_timer_current_time_us();
    system_timer_event_after(MAX_SOUND_DELAY, DEVICE_ID_RADAR, MICROBIT_RADAR_EVT_STOP_RECORDING, CODAL_TIMER_EVENT_FLAGS_NONE); // ~26 us.

    // Start recording in the MicroBitAudioProcessor.
    MicroBitRadar::instance->uBit->audio.fft->startRecording(); // ~27 us.

    // TODO: Check if the radio communication is indeed a Radar datagram.

    // Get bytes from the datagram.
    PacketBuffer packetBuf = MicroBitRadar::instance->uBit->radio.datagram.recv();
    uint8_t* packetPl = packetBuf.getBytes();

    // Deserialise, i.e. create a new struct to hold the datagram bytes.
    MicroBitRadar::Payload payloadStruct;
    memcpy(&payloadStruct, packetPl, (int) sizeof(MicroBitRadar::Payload));
}

/**
 * TODO: Finish comment.
 */
REAL_TIME_FUNC
static void onRadarSound(MicroBitEvent e)
{
    // Save the timestamp for the MicroBitAudioProcessor event for further reference.
    MicroBitRadar::instance->soundReceived = e.timestamp;
    int64_t distance = (MicroBitRadar::instance->soundReceived - MicroBitRadar::instance->radioReceived) * SOUND_VEL_MS;

    // Print the distance in meters/second.
    DMESG("Distance = %d.%d meters.", (int) distance / 1000000, (int) distance % 100);

    // Stop recording after the first distance measurement.
    MicroBitRadar::instance->uBit->audio.fft->stopRecording();
}

REAL_TIME_FUNC
static void onMaxSoundDelay(MicroBitEvent e)
{
    MicroBitRadar::instance->uBit->audio.fft->stopRecording();
}

/**
 * TODO: Make sure I need this.
*/
void MicroBitRadar::periodicCallback()
{
    DMESG("Callback!");
}