/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#ifndef NUMBERGUESSGAME_PACKET_H
#define NUMBERGUESSGAME_PACKET_H

#include "Arduino.h"
#include "StandardCplusplus.h"
#include <vector>

class Packet {
public:
	Packet(int targetDeviceId, int packetType);
	Packet(int targetDeviceId, int packetType,
		   std::vector<int> ints,
		   std::vector<bool> bools,
		   std::vector<String> strs);
	int getTargetDeviceId();
	void setTargetDeviceId(int id);
	int getPacketType();
	void setPacketType(int type);
	std::vector<int> getIntegers();
	int getIntegersCount();
	bool hasIntegers();
	void setIntegers(std::vector<int> ints);
	std::vector<bool> getBooleans();
	int getBooleansCount();
	bool hasBooleans();
	void setBooleans(std::vector<bool> bools);
	std::vector<String> getStrings();
	int getStringsCount();
	bool hasStrings();
	void setStrings(std::vector<String> strs);
	int getArrayCount();

private:
	int targetDeviceId;
	int packetType;
    std::vector<int> ints;
	std::vector<bool> bools;
	std::vector<String> strs;
};

#endif // NUMBERGUESSGAME_PACKET_H