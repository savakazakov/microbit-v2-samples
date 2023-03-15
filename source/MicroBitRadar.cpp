#include "MicroBitRadar.h"
#include "CodalDmesg.h"
#include <string>

using namespace codal;

MicroBitRadar *MicroBitRadar::instance = NULL;
NRF52ADCChannel *MicroBitRadar::mic = NULL;
SerialStreamer *MicroBitRadar::streamer = NULL;
StreamNormalizer *MicroBitRadar::processor = NULL;
LevelDetector *MicroBitRadar::level = NULL;
LevelDetectorSPL *MicroBitRadar::levelSPL = NULL;

static void onData(MicroBitEvent e);

    /**
     * Constructor.
     *
     * Create the Radar component, which includes member variables
     * that represent various device drivers used for the calculations
     * performed by the radar component.
     */
    MicroBitRadar::MicroBitRadar(MicroBit *uBit)
{
    uBit->serial.printf("In radar constructor\n"); // REMOVE PRINTING.
    MicroBitRadar::uBit = uBit;

    // If we are the first instance created, schedule it for on demand activation.
    // TODO: Make sure I need this.
    if (MicroBitRadar::instance == NULL)
        MicroBitRadar::instance = this;

    uBit->serial.printf("Out of radar constructor.\n"); // REMOVE PRINTING.
}

MicroBitRadar::~MicroBitRadar()
{
    
}

void MicroBitRadar::radioTest()
{
    uBit->serial.printf("In radioTest in Radar.\n"); // REMOVE PRINTING.

    uBit->serial.printf("Device id = %d.\n", microbit_serial_number()); // REMOVE PRINTING.
    uBit->serial.printf("(int) sizeof(Payload) = %d.\n", (int) sizeof(Payload)); // REMOVE PRINTING.

    // Construct a payload with the device's serial number.
    Payload payloadStruct = {
                                microbit_serial_number() // serial
                            };

    // Serialise the struct.
    uint8_t* pl_bytes = reinterpret_cast<uint8_t *>(&payloadStruct);

    PacketBuffer packetBuf = PacketBuffer(pl_bytes, (int) sizeof(Payload)); // Creates a PacketBuffer 4 bytes long.

    uBit->radio.datagram.send(packetBuf);

    uBit->serial.printf("Exiting radioTest in Radar.\n"); // REMOVE PRINTING.
}

void MicroBitRadar::micTest()
{
    if (mic == NULL)
    {
        mic = uBit->adc.getChannel(uBit->io.microphone);
        mic->setGain(7, 0); // Uncomment for v1.47.2
        // mic->setGain(7,1);        // Uncomment for v1.46.2
    }

    if (processor == NULL)
        processor = new StreamNormalizer(mic->output, 0.05f, true, DATASTREAM_FORMAT_8BIT_SIGNED);

    if (streamer == NULL)
        streamer = new SerialStreamer(processor->output, SERIAL_STREAM_MODE_BINARY);

    uBit->io.runmic.setDigitalValue(1);
    uBit->io.runmic.setHighDrive(true);
}

/**
 * Internal constructor-initialiser.
 * TODO: Add anything that needs to be initialised prior radaring here.
 */
void MicroBitRadar::init(/* MicroBit uBit, MicroBitRadio radio */)
{
    uBit->serial.printf("In init in Radar.\n"); // REMOVE PRINTING.

    // Bring up internal speaker as high drive.
    uBit->io.speaker.setHighDrive(true);
    uBit->radio.enable();

    // Make sure I know exactly what these do.
    uBit->io.runmic.setDigitalValue(1);
    uBit->io.runmic.setHighDrive(true);

    uBit->messageBus.listen(DEVICE_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onData, MESSAGE_BUS_LISTENER_REENTRANT);

    uBit->serial.printf("Exiting init in Radar.\n"); // REMOVE PRINTING.
}

static void onData(MicroBitEvent e)
{
    MicroBitRadar::instance->uBit->serial.printf("In onData in Radar.\n"); // REMOVE PRINTING.

    MicroBitRadar::instance->uBit->io.speaker.setAnalogValue(512); // REMOVE PRINTING.
    MicroBitRadar::instance->uBit->sleep(100);  // REMOVE PRINTING.
    MicroBitRadar::instance->uBit->io.speaker.setAnalogValue(0); // REMOVE PRINTING.

    PacketBuffer packetBuf = MicroBitRadar::instance->uBit->radio.datagram.recv();
    uint8_t* packetPl = packetBuf.getBytes();

    // Deserialise.
    // Create a new struct to hold the converted bytes.
    MicroBitRadar::Payload payloadStruct;

    // Copy the bytes from the uint8_t pointer into the new struct.
    memcpy(&payloadStruct, packetPl, (int) sizeof(MicroBitRadar::Payload));

    std::string str = std::to_string(payloadStruct.serial);
    MicroBitRadar::instance->uBit->serial.printf("Other uBit's serial is %s.\n", str.c_str()); // REMOVE PRINTING.

    MicroBitRadar::instance->uBit->serial.printf("Exiting onData in Radar.\n"); // REMOVE PRINTING.
}

/**
 * TODO: Make sure I need this.
*/
void MicroBitRadar::periodicCallback()
{
    DMESG("Callback!");
}