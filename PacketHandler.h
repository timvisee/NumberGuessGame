#ifndef SWAIPacketHandler_h
#define SWAIPacketHandler_h

#include "Arduino.h"
#include "StandardCplusplus.h"
#include "Globals.h"
#include "Packet.h"
#include "Protocol.h"
#include "ConnectionManager.h"
#include <vector>

class PacketHandler {
private:
	static SoftwareSerial con;
	static bool skipNext;
	static String buff;

public:
	static void setConnectionStream(SoftwareSerial &con);
	static void sendPacket(Packet p);
	static void sendPacket(String p);
	static void receive(char c);
	static bool receivedPacket(Packet p);
};

#endif
