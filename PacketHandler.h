#ifndef SWAIPacketHandler_h
#define SWAIPacketHandler_h

#include <Arduino.h>
#include <AltSoftSerial.h>
#include <StandardCplusplus.h>
#include <vector>
#include "Globals.h"
#include "Packet.h"
#include "Protocol.h"


class PacketHandler {
private:
	static AltSoftSerial con;
	static bool skipNext;
	static String buff;

public:
	static void setConnectionStream(AltSoftSerial &con);
	static void sendPacket(Packet packet);
	static void sendPacket(String packet);
	static void receive(char c);
	static void receivedPacket(Packet packet);
};

#endif
