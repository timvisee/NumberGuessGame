/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#ifndef NUMBERGUESSGAME_PACKET_H
#define NUMBERGUESSGAME_PACKET_H

#include <Arduino.h>

class Packet {
private:
    /**
     * Get ID of the target device.
     */
    byte targetDeviceId;

    /**
     * The type of the packet.
     */
    byte packetType;

    /**
     * The number of integers in this packet.
     */
	uint8_t intSize;

    /**
     * The array of integers.
     */
    int * intArr;

    /**
     * The number of booleans in this packet.
     */
    uint8_t boolSize;

    /**
     * The array of booleans.
     */
    bool * boolArr;

    /**
     * The number of strings in this packet.
     */
    uint8_t strSize;

    /**
     * The array of strings.
     */
    String * strArr;

public:
    /**
     * Constructor.
     */
	Packet();

    /**
     * Constructor.
     *
     * @param targetDeviceId ID of the target device.
     * @param packetType The type of the packet.
     */
	Packet(byte targetDeviceId, byte packetType);

    /**
     * Constructor.
     *
     * @param targetDeviceId ID of the target device.
     * @param packetType The type of the packet.
     * @param intArr The integer array.
     * @param intSize The size of the integer array.
     * @param boolArr The boolean array.
     * @param boolSize The size of the boolean array.
     * @param strArr The string array.
     * @param strSize The size of the string array.
     */
    Packet(byte targetDeviceId, byte packetType, int *intArr, uint8_t intSize, bool *boolArr, uint8_t boolSize,
String *strArr, uint8_t strSize);

    /**
     * Destructor.
     */
	~Packet();

    /**
     * Get the ID of the target device.
     *
     * @return Target device ID.
     */
    byte getTargetDeviceId();

    /**
     * Set the ID of the target device.
     *
     * @param id Target device ID.
     */
	void setTargetDeviceId(byte id);

    /**
     * Get the packet type ID.
     *
     * @return Packet type ID.
     */
    byte getPacketType();

    /**
     * Set the packet type ID.
     *
     * @param type Packet type ID.
     */
	void setPacketType(byte type);

    /**
     * Get the integers array.
     *
     * @return Integers.
     */
	int * getIntegers();

    /**
     * Get the number of integers in the integer array.
     *
     * @return Integer array size.
     */
	uint8_t getIntegersCount();

    /**
     * Check whether this packet has any integers.
     *
     * @return True if there are any integers, false otherwise.
     */
	bool hasIntegers();

    /**
     * Set the integers array.
     *
     * @param intArr Integer array.
     * @param size Integer array size.
     */
	void setIntegers(int * intArr, uint8_t size);
    
    /**
     * Get the booleans array.
     *
     * @return Booleans.
     */
	bool * getBooleans();

    /**
     * Get the number of booleans in the boolean array.
     *
     * @return Boolean array size.
     */
    uint8_t getBooleansCount();

    /**
     * Check whether this packet has any booleans.
     *
     * @return True if there are any booleans, false otherwise.
     */
	bool hasBooleans();

    /**
     * Set the booleans array.
     *
     * @param intArr Boolean array.
     * @param size Boolean array size.
     */
	void setBooleans(bool * boolArr, uint8_t size);

    /**
     * Get the strings array.
     *
     * @return Strings.
     */
	String * getStrings();

    /**
     * Get the number of strings in the string array.
     *
     * @return String array size.
     */
    uint8_t getStringsCount();

    /**
     * Check whether this packet has any strings.
     *
     * @return True if there are any strings, false otherwise.
     */
	bool hasStrings();

    /**
     * Set the strings array.
     *
     * @param intArr String array.
     * @param size String array size.
     */
	void setStrings(String * strArr, uint8_t size);

    /**
     * Get the number of different type of data arrays included in this packet.
     *
     * @return Data array type count.
     */
    uint8_t getArrayCount();
};

#endif // NUMBERGUESSGAME_PACKET_H