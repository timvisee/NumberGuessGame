/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#include "Packet.h"

Packet::Packet(int targetDeviceId, int packetType) {
	this->targetDeviceId = targetDeviceId;
	this->packetType = packetType;
}

Packet::Packet(int targetDeviceId, int packetType,
			   std::vector<int> ints,
			   std::vector<bool> bools,
			   std::vector<String> strs) {
	this->targetDeviceId = targetDeviceId;
	this->packetType = packetType;
	this->ints = ints;
	this->bools = bools;
	this->strs = strs;
}

int Packet::getTargetDeviceId() {
	return this->targetDeviceId;
}

void Packet::setTargetDeviceId(int id) {
	this->targetDeviceId = id;
}

int Packet::getPacketType() {
	return this->packetType;
}

void Packet::setPacketType(int type) {
	this->packetType = type;
}

std::vector<int> Packet::getIntegers() {
	return this->ints;
}

int Packet::getIntegersCount() {
	return this->ints.size();
}

bool Packet::hasIntegers() {
	return (getIntegersCount() > 0);
}

void Packet::setIntegers(std::vector<int> ints) {
	this->ints = ints;
}

std::vector<bool> Packet::getBooleans() {
	return this->bools;
}

int Packet::getBooleansCount() {
	return this->bools.size();
}

bool Packet::hasBooleans() {
	return (getBooleansCount() > 0);
}

void Packet::setBooleans(std::vector<bool> bools) {
	this->bools = bools;
}

std::vector<String> Packet::getStrings() {
	return this->strs;
}

int Packet::getStringsCount() {
	return this->strs.size();
}

bool Packet::hasStrings() {
	return (getStringsCount() > 0);
}

void Packet::setStrings(std::vector<String> strs) {
	this->strs = strs;
}

int Packet::getArrayCount() {
	// Count amount of arrays
	int arrCount = 0;
	if(hasIntegers() > 0)
		arrCount++;
	if(hasBooleans() > 0)
		arrCount++;
	if(hasStrings() > 0)
		arrCount++;

	// Return array count
	return arrCount;
}