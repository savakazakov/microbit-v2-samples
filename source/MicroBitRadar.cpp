#include "MicroBitRadar.h"
#include "CodalDmesg.h"
#include <string>

using namespace codal;

MicroBitRadar *MicroBitRadar::instance = NULL;

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

    PacketBuffer packetBuf = PacketBuffer(pl_bytes, (int) sizeof(Payload)); // Creates a PacketBuffer 3 bytes long.

    // // ##########################################################################################
    // uint8_t *packetPl = packetBuf.getBytes();

    // // Deserialise.
    // // Create a new struct to hold the converted bytes.
    // MicroBitRadar::Payload receivePlayload;

    // // Copy the bytes from the uint8_t pointer into the new struct.
    // memcpy(&receivePlayload, &packetPl, (int) sizeof(MicroBitRadar::Payload));

    // // std::string str = std::to_string(receivePlayload.serial);
    // // ManagedString ms = ManagedString(str.c_str());
    // // MicroBitRadar::instance->uBit->display.scrollAsync(ms);

    // uBit->serial.printf("Device id after processing = %d.\n", (int) receivePlayload.serial);         // REMOVE PRINTING.
    // uBit->serial.printf("(int) sizeof(MicroBitRadar::Payload) = %d.\n", (int) sizeof(MicroBitRadar::Payload)); // REMOVE PRINTING.

    // ##########################################################################################

    uBit->radio.datagram.send(packetBuf);

    uBit->serial.printf("Exiting radioTest in Radar.\n"); // REMOVE PRINTING.
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

    uBit->messageBus.listen(DEVICE_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onData, MESSAGE_BUS_LISTENER_REENTRANT);

    uBit->serial.printf("Exiting init in Radar.\n"); // REMOVE PRINTING.
}

static void onData(MicroBitEvent e)
{
    MicroBitRadar::instance->uBit->serial.printf("In onData in Radar.\n"); // REMOVE PRINTING.

    MicroBitRadar::instance->uBit->io.speaker.setAnalogValue(512);
    MicroBitRadar::instance->uBit->sleep(100);
    MicroBitRadar::instance->uBit->io.speaker.setAnalogValue(0);

    PacketBuffer packetBuf = MicroBitRadar::instance->uBit->radio.datagram.recv();
    uint8_t* packetPl = packetBuf.getBytes();

    // Deserialise.
    // Create a new struct to hold the converted bytes.
    MicroBitRadar::Payload payloadStruct;

    // Copy the bytes from the uint8_t pointer into the new struct.
    memcpy(&payloadStruct, &packetPl, (int) sizeof(MicroBitRadar::Payload));

    std::string str = std::to_string(payloadStruct.serial);
    ManagedString ms = ManagedString(str.c_str());
    MicroBitRadar::instance->uBit->display.scrollAsync(ms);

    MicroBitRadar::instance->uBit->serial.printf("Exiting onData in Radar.\n"); // REMOVE PRINTING.
}

/**
 * TODO: Make sure I need this.
*/
void MicroBitRadar::periodicCallback()
{
    DMESG("Callback!");
}