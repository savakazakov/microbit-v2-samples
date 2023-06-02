#include "MicroBit.h"
#include "Tests.h"

#include "MicroBitRadar.h"

/**
 * TODO: Fill this with tests.
*/

static void Test()
{
    
}

// #include "MicroBitRadar.h"
// #include "CodalDmesg.h"

// using namespace codal;

// MicroBitRadar *MicroBitRadar::instance = NULL;
// // NRF52ADCChannel *MicroBitRadar::mic = NULL;
// // MicroBitAudioProcessor *MicroBitRadar::fft = NULL;
// // SerialStreamer *MicroBitRadar::streamer = NULL;
// // StreamNormalizer *MicroBitRadar::processor = NULL;
// // LevelDetector *MicroBitRadar::level = NULL;
// // LevelDetectorSPL *MicroBitRadar::levelSPL = NULL;

// static void onRadarRadio(MicroBitEvent e);
// static void onRadarSound(MicroBitEvent e);

// /**
//  * Constructor.
//  *
//  * Create the Radar component, which includes member variables
//  * that represent various device drivers used for the calculations
//  * performed by the radar component.
//  */
// MicroBitRadar::MicroBitRadar(MicroBit *uBit)
// {
//     MicroBitRadar::uBit = uBit;

//     // If we are the first instance created, schedule it for on demand activation.
//     if (MicroBitRadar::instance == NULL)
//         MicroBitRadar::instance = this;
// }

// /**
//  * Internal constructor-initialiser.
//  * TODO: Fix this comment.
//  * TODO: Add anything that needs to be initialised prior radaring here.
//  */
// void MicroBitRadar::init()
// {
//     // Bring up internal speaker as high drive.
//     uBit->io.speaker.setHighDrive(true);
//     uBit->radio.enable();

//     // Make sure I know exactly what these do.
//     uBit->io.runmic.setDigitalValue(1);
//     uBit->io.runmic.setHighDrive(true);

//     // Start listening on the MicroBitRadio.
//     uBit->messageBus.listen(DEVICE_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onRadarRadio,
//                             MESSAGE_BUS_LISTENER_REENTRANT);

//     // Subscribe for a specific sound signal frequency.
//     uint8_t eventCode =
//         uBit->audio.fft->subscribe(PRIMARY_RADAR_FREQUENCY, DEFAULT_RADAR_THRESHOLD);
//     uBit->messageBus.listen(DEVICE_ID_AUDIO_PROCESSOR, eventCode, onRadarSound,
//                             MESSAGE_BUS_LISTENER_IMMEDIATE);
// }

// MicroBitRadar::~MicroBitRadar() {}

// /**
//  * TODO: Fix this comment.
//  */
// void MicroBitRadar::subscribeTest()
// {
//     uBit->display.print("S");

//     testFreqCounter++;

//     uint8_t eventCode = uBit->audio.fft->subscribe(testFreqCounter * 500, DEFAULT_RADAR_THRESHOLD);
//     DMESG("eventCode = %d\n", eventCode);
// }

// /**
//  * TODO: Fix this comment.
//  */
// void MicroBitRadar::unsubscribeTest()
// {
//     uBit->display.print("U");

//     uBit->audio.fft->unsubscribe(testEventCodeCounter++);
// }

// /**
//  * TODO: Fix this comment.
//  */
// void MicroBitRadar::radioTest()
// {
//     uBit->display.print("R");

//     // Construct a payload with the device's serial number.
//     Payload payloadStruct = {microbit_serial_number()};

//     // Serialise the struct.
//     uint8_t *plBytes = reinterpret_cast<uint8_t *>(&payloadStruct);

//     // Creates a PacketBuffer 4 bytes long.
//     PacketBuffer packetBuf = PacketBuffer(plBytes, (int)sizeof(Payload));

//     uBit->radio.datagram.send(packetBuf);
// }

// /**
//  * TODO: Fix this comment.
//  * Creates an example MicroBitAudioProcessor and then queries it for results.
//  * Currently configured to use 1024 samples with 8bit signed data.
//  */
// void MicroBitRadar::fftTest()
// {
//     uBit->display.print("F");

//     // Start running the FFT.
//     uBit->audio.fft->startRecording();

//     DMESG("After start recording.");                                          // REMOVE
//     DMESG("Sample period in microseconds = %d", uBit->adc.getSamplePeriod()); // REMOVE

//     uBit->sleep(1000); // REMOVE

//     while (1)
//     {
//         // TODO - de-noise : if last X samples are same - display ect.
//         // The output values depend on the input type (DATASTREAM_FORMAT_8BIT_SIGNED) and the size
//         // of the FFT - which is changed using the 'AUDIO_SAMPLES_NUMBER' in
//         // MicroBitAudioProcessor.h default is 1024
//         uBit->sleep(500);
//         int freq = uBit->audio.fft->getFrequency();
//         DMESG("Frequency: %d", freq);
//     }
// }

// /**
//  * TODO: Fix this comment.
//  * Ping test.
//  */
// void MicroBitRadar::distanceTest()
// {
//     uBit->display.print("D");

//     // Start running the FFT.
//     uBit->audio.fft->startRecording();

//     radioTest();

//     // Pulse 8kHz.
//     uBit->io.speaker.setAnalogPeriodUs(PRIMARY_RADAR_PERIOD);
//     uBit->io.speaker.setAnalogValue(DUTY_CYCLE_50);
//     system_timer_wait_ms(500);
//     uBit->io.speaker.setAnalogValue(DUTY_CYCLE_0);

//     DMESG("Sample period = %d microseconds.", uBit->adc.getSamplePeriod()); // REMOVE
// }

// /**
//  * TODO: Finish this comment.
//  * TODO: Make sure to filter useless radio communication.
//  */
// static void onRadarRadio(MicroBitEvent e)
// {
//     MicroBitRadar::instance->radioReceived = system_timer_current_time_us();

//     // TODO: Check if the radio communication is indeed a Radar datagram.

//     // Get bytes from the datagram.
//     PacketBuffer packetBuf = MicroBitRadar::instance->uBit->radio.datagram.recv();
//     uint8_t *packetPl = packetBuf.getBytes();

//     // Deserialise, i.e. create a new struct to hold the datagram bytes.
//     MicroBitRadar::Payload payloadStruct;
//     memcpy(&payloadStruct, packetPl, (int)sizeof(MicroBitRadar::Payload));

//     DMESG("This uBit's serial is %d.\n", microbit_serial_number()); // REMOVE PRINTING.
//     DMESG("Other uBit's serial is %d.\n", payloadStruct.serial);    // REMOVE PRINTING.
// }

// /**
//  * TODO: Finish comment.
//  */
// static void onRadarSound(MicroBitEvent e)
// {
//     DMESG("Printing event value = %d", (int)e.value);

//     // Divide by 1e-6. to get to seconds.
//     float timestampDiff =
//         (e.timestamp - MicroBitRadar::instance->radioReceived) /* / ((float32_t) 1e-6) */;

//     // Perform the distance calculation.
//     float distanceInMeters = timestampDiff * SOUND_VEL_MS;

//     char distStr[50];
//     int n = sprintf(distStr, "%f", (float)distanceInMeters);

//     DMESG("Distance = %d, s is %d long", (int)distanceInMeters, n);
//     // DMESG("Distance = %d, s is %d long", (int) distanceInMeters);

//     MicroBitRadar::instance->uBit->serial.printf(
//         "Exiting onRadarSound in Radar.\n"); // REMOVE PRINTING.
// }

// /**
//  * TODO: Make sure I need this.
//  */
// void MicroBitRadar::periodicCallback()
// {
//     DMESG("Callback!");
// }