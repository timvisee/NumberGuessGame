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
#include <StandardCplusplus.h>
#include <vector>

class Packet {
private:
    byte targetDeviceId;
    byte packetType;
	uint8_t intSize;
    int * intArr;
    uint8_t boolSize;
    bool * boolArr;
    uint8_t strSize;
    String * strArr;

public:
	Packet();
	Packet(byte targetDeviceId, byte packetType);
	Packet(byte targetDeviceId, byte packetType,
           uint8_t intSize, int * intArr,
           uint8_t boolSize, bool * boolArr,
           uint8_t strSize, String * strArr);
    byte getTargetDeviceId();
	void setTargetDeviceId(byte uint8_t);
    byte getPacketType();
	void setPacketType(byte uint8_t);
	int * getIntegers();
	uint8_t getIntegersCount();
	bool hasIntegers();
	void setIntegers(int * intArr, uint8_t size);
	bool * getBooleans();
    uint8_t getBooleansCount();
	bool hasBooleans();
	void setBooleans(bool * boolArr, uint8_t size);
	String * getStrings();
    uint8_t getStringsCount();
	bool hasStrings();
	void setStrings(String * strArr, uint8_t size);
    uint8_t getArrayCount();
};

#endif // NUMBERGUESSGAME_PACKET_H