#include "PacketHandler.h"

// Initialize class members
Stream&PacketHandler::compStream = Serial;
Stream&PacketHandler::robotStream = Serial;
bool PacketHandler::compSkipNext = false;
String PacketHandler::compBuff = "";
bool PacketHandler::robotSkipNext = false;
String PacketHandler::robotBuff = "";

void PacketHandler::setComputerStream(Stream& s) {
	PacketHandler::compStream = s;
}

void PacketHandler::setRobotStream(Stream& s) {
	PacketHandler::robotStream = s;
}

void PacketHandler::computerSendPacket(Packet p) {
	// Serialize and send the packet
	PacketHandler::computerSendPacket(Protocol::serialize(p));
}

void PacketHandler::computerSendPacket(String p) {
    // Set the status of the activity LED
	sm.setActivityStatus(SWAIStatusManager::ACTIVITY_BLINK);

	// Convert the serialized packet into a char array
	char *charArr=new char[p.length()+1];
	charArr[p.length()]=0;
	memcpy(charArr,p.c_str(),p.length());

	// Serialize and send the packet
	PacketHandler::compStream.write(charArr);
	
    // Disable the activity LED
	sm.setActivityStatus(SWAIStatusManager::ACTIVITY_OFF);
}

void PacketHandler::computerReceive(char c) {
    if(PacketHandler::compSkipNext) {
        PacketHandler::compBuff += c;
        PacketHandler::compSkipNext = false;
                
    } else {
		// Check whether the next character should be skipped due to a backslash
        if(c == '\\' && !PacketHandler::compSkipNext)
            PacketHandler::compSkipNext = true;
                   
		// Check whether the current packet is ending
        if(c == Protocol::CHAR_PACKET_END && !PacketHandler::compSkipNext) {
            if(PacketHandler::computerReceivedPacket(Protocol::deserialize(compBuff)))
				PacketHandler::robotSendPacket(PacketHandler::compBuff);
            PacketHandler::compBuff = "";
        }
                
		// Check whether a new packet is beginning
        if(c == Protocol::CHAR_PACKET_BEGIN && !PacketHandler::compSkipNext)
            PacketHandler::compBuff = "";
    }
}

bool PacketHandler::computerReceivedPacket(Packet p) {
	switch(p.getPacketType()) {
	case Protocol::PACKET_TYPE_CONNECT_REQ:
		// Send a connection confirm packet
		PacketHandler::computerSendPacket(Packet(0, Protocol::PACKET_TYPE_CONNECT));

	case Protocol::PACKET_TYPE_CONNECT:
		// Set the connected state to true
		SWAIConnectionManager::setComputerConnected(true);
		return false;
		
	case Protocol::PACKET_TYPE_DISCONNECT_REC:
		// Send a connection confirm packet
		PacketHandler::computerSendPacket(Packet(0, Protocol::PACKET_TYPE_DISCONNECT));

	case Protocol::PACKET_TYPE_DISCONNECT:
		// Set the connected state to false
		SWAIConnectionManager::setComputerConnected(false);
		break;

	default:
		break;
	}
	
	return true;
}

void PacketHandler::robotSendPacket(Packet p) {
	// Serialize and send the packet
	PacketHandler::robotSendPacket(Protocol::serialize(p));
}

void PacketHandler::robotSendPacket(String p) {
    // Set the status of the activity LED
	sm.setActivityStatus(SWAIStatusManager::ACTIVITY_BLINK);

	// Convert the serialized packet into a char array
	char *charArr=new char[p.length()+1];
	charArr[p.length()]=0;
	memcpy(charArr,p.c_str(),p.length());

	// Serialize and send the packet
	PacketHandler::robotStream.write(charArr);
	
    // Disable the activity LED
	sm.setActivityStatus(SWAIStatusManager::ACTIVITY_OFF);
}

void PacketHandler::robotReceive(char c) {
    if(PacketHandler::robotSkipNext) {
        PacketHandler::robotBuff += c;
        PacketHandler::robotSkipNext = false;
                
    } else {
		// Check whether the next character should be skipped due to a backslash
        if(c == '\\')
            PacketHandler::robotSkipNext = true;
                   
		// Check whether the current packet is ending
        if(c == Protocol::CHAR_PACKET_END) {
            if(PacketHandler::robotReceivedPacket(Protocol::deserialize(robotBuff)))
				computerSendPacket(PacketHandler::robotBuff);
            PacketHandler::robotBuff = "";
        }
                
		// Check whether a new packet is beginning
        if(c == Protocol::CHAR_PACKET_BEGIN)
            PacketHandler::robotBuff = "";
    }
}

bool PacketHandler::robotReceivedPacket(Packet p) {
	switch(p.getPacketType()) {
	case Protocol::PACKET_TYPE_CONNECT_REQ:
		// Send a connection confirm packet
		PacketHandler::robotSendPacket(Packet(0, Protocol::PACKET_TYPE_CONNECT));

	case Protocol::PACKET_TYPE_CONNECT:
		// Set the connected state to true
		SWAIConnectionManager::setRobotConnected(true);
		return false;
		
	case Protocol::PACKET_TYPE_DISCONNECT_REC:
		// Send a connection confirm packet
		PacketHandler::robotSendPacket(Packet(0, Protocol::PACKET_TYPE_DISCONNECT));

	case Protocol::PACKET_TYPE_DISCONNECT:
		// Set the connected state to false
		SWAIConnectionManager::setRobotConnected(false);
		break;

	default:
		break;
	}

	return true;
}