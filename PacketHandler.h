#ifndef SWAIPacketHandler_h
#define SWAIPacketHandler_h

#include "Arduino.h"
#include "StandardCplusplus.h"
#include "Globals.h"
#include "Packet.h"
#include "Protocol.h"
#include "SWAIStatusManager.h"
#include "SWAIConnectionManager.h"
#include <vector>

class PacketHandler {
public:
	static void setComputerStream(Stream& s);
	static void setRobotStream(Stream& s);
	static void computerSendPacket(SWAIPacket p);
	static void computerSendPacket(String p);
	static void computerReceive(char c);
	static bool computerReceivedPacket(SWAIPacket p);
	static void robotSendPacket(SWAIPacket p);
	static void robotSendPacket(String p);
	static void robotReceive(char c);
	static bool robotReceivedPacket(SWAIPacket p);

private:
	static Stream& compStream;
	static Stream& robotStream;
	static bool compSkipNext;
	static String compBuff;
	static bool robotSkipNext;
	static String robotBuff;
};

#endif
