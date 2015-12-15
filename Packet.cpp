/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#include "Packet.h"

Packet::Packet() {
	this->targetDeviceId = 0;
	this->packetType = 0;
    this->intArr = NULL;
	this->intSize = 0;
    this->boolArr = NULL;
	this->boolSize = 0;
    this->strArr = NULL;
	this->strSize = 0;
}

Packet::Packet(byte targetDeviceId, byte packetType) {
	this->targetDeviceId = targetDeviceId;
	this->packetType = packetType;
    this->intArr = NULL;
    this->intSize = 0;
    this->boolArr = NULL;
    this->boolSize = 0;
    this->strArr = NULL;
    this->strSize = 0;
}

Packet::Packet(byte targetDeviceId, byte packetType, int *intArr, uint8_t intSize, bool *boolArr, uint8_t boolSize,
               String *strArr, uint8_t strSize) {
	this->targetDeviceId = targetDeviceId;
	this->packetType = packetType;
	this->intSize = intSize;
	this->intArr = intArr;
	this->boolSize = boolSize;
	this->boolArr = boolArr;
	this->strSize = strSize;
	this->strArr = strArr;
}

Packet::~Packet() {
    // Free all memory used by the array pointers
    // TODO: Should we enable this again? Or are these arrays already deleted after the packet definition?
//	  delete[] intArr;
//    delete[] boolArr;
//    delete[] strArr;
}

byte Packet::getTargetDeviceId() {
	return this->targetDeviceId;
}

void Packet::setTargetDeviceId(byte id) {
	this->targetDeviceId = id;
}

byte Packet::getPacketType() {
	return this->packetType;
}

void Packet::setPacketType(byte type) {
	this->packetType = type;
}

int * Packet::getIntegers() {
	return this->intArr;
}

uint8_t Packet::getIntegersCount() {
	return this->intSize;
}

bool Packet::hasIntegers() {
	return getIntegersCount() > 0;
}

void Packet::setIntegers(int * intArr, uint8_t size) {
    // Delete the current array from memory
    delete[] this->intArr;

    // Set the array and it's size
	this->intArr = intArr;
	this->intSize = size;
}

bool * Packet::getBooleans() {
	return this->boolArr;
}

uint8_t Packet::getBooleansCount() {
	return this->boolSize;
}

bool Packet::hasBooleans() {
	return getBooleansCount() > 0;
}

void Packet::setBooleans(bool * boolArr, uint8_t size) {
    // Delete the current array from memory
    delete[] this->boolArr;

    // Set the array and it's size
	this->boolArr = boolArr;
	this->boolSize = size;
}

String * Packet::getStrings() {
	return this->strArr;
}

uint8_t Packet::getStringsCount() {
	return this->strSize;
}

bool Packet::hasStrings() {
	return getStringsCount() > 0;
}

void Packet::setStrings(String * strArr, uint8_t size) {
    // Delete the current array from memory
    delete[] this->strArr;

    // Set the array and it's size
	this->strArr = strArr;
	this->strSize = size;
}

uint8_t Packet::getArrayCount() {
	// Count amount of arrays
	uint8_t arrCount = 0;
	if(hasIntegers() > 0)
		arrCount++;
	if(hasBooleans() > 0)
		arrCount++;
	if(hasStrings() > 0)
		arrCount++;

	// Return array count
	return arrCount;
}