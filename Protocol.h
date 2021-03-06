/**
 * NumberGuessGame
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#ifndef SWAIProtocol_h
#define SWAIProtocol_h

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Log.h"
#include "Packet.h"
#include "StringUtils.h"

/**
 * Protocol class.
 */
class Protocol {
public:
    /**
     * Character to define the beginning of a packet.
     */
    static const char CHAR_PACKET_BEGIN = 0x01;

    /**
     * Character to define the end of a packet.
     */
    static const char CHAR_PACKET_END = 0x02;

    /**
     * Character to define the separators of a packet.
     */
    static const char CHAR_PACKET_SEPARATOR = 0x03;

    /**
     * Character to define the data separators of a packet.
     */
    static const char CHAR_PACKET_DATA_SEPARATOR = 0x04;

    /**
     * Character to define the data array separators of a packet.
     */
    static const char CHAR_PACKET_DATA_ARRAY_SEPARATOR = 0x05;

    /**
     * ID to define the integer array type.
     */
    static const uint8_t DATA_ARR_TYPE_INT = 0x01;

    /**
     * ID to define the boolean array type.
     */
    static const uint8_t DATA_ARR_TYPE_BOOL = 0x02;

    /**
     * ID to define the String array type.
     */
    static const uint8_t DATA_ARR_TYPE_STR = 0x03;

    /**
     * Value to define the unknown packet type.
     */
    static const int PACKET_TYPE_UNKNOWN = 0;

    /**
     * Value to define the connection request type.
     */
    static const int PACKET_TYPE_CONNECTION_REQUEST = 1;

    /**
     * Value to define the connection accept type.
     */
    static const int PACKET_TYPE_CONNECTION_ACCEPT = 2;

    /**
     * Value to define the game start type.
     */
    static const int PACKET_TYPE_GAME_START = 3;

    /**
     * Value to define the game answer type.
     */
    static const int PACKET_TYPE_GAME_ANSWER = 4;

    /**
     * Value to define the game results type.
     */
    static const int PACKET_TYPE_GAME_RESULTS = 5;

	/**
	 * Serialize a packet as a string.
	 *
	 * @param packet Packet to serialize.
	 *
	 * @return Serialized packet.
	 */
    static String serialize(Packet packet);

    /**
     * Deserialize a packet from a string.
     *
     * @param str Packet as a string.
     *
     * @return The deserialized packet.
     */
    static Packet deserialize(String str);
};

#endif
