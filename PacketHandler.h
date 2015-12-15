/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#ifndef SWAIPacketHandler_h
#define SWAIPacketHandler_h

#include <Arduino.h>
#include <AltSoftSerial.h>
#include "Globals.h"
#include "Log.h"
#include "Packet.h"
#include "Protocol.h"

/**
 * PacketHandler class.
 */
class PacketHandler {
private:
    /**
     * Serial connection used for communication.
     */
    static AltSoftSerial con;

    /**
     * Whether to skip parsing the next received byte.
     */
    static bool skipNext;

    /**
     * The current received buffer.
     */
    static String buff;

public:
    /**
     * Set the current connection stream.
     *
     * @param con The connection stream.
     */
    static void setConnectionStream(AltSoftSerial &con);

    /**
     * Send a packet.
     *
     * @param Packet to send.
     */
    static void sendPacket(Packet packet);

    /**
     * Send a packet as a string.
     *
     * @param Packet to send.
     */
    static void sendPacket(String packet);

    /**
     * Called when a byte is received.
     *
     * @param c Received byte.
     */
    static void receive(char data);

    /**
     * Called when a full packet is received.
     *
     * @param packet The received packet.
     */
    static void receivedPacket(Packet packet);
};

#endif
