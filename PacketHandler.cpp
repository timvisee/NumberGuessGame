#include "PacketHandler.h"

// Initialize class members
SoftwareSerial PacketHandler::con = SoftwareSerial(7, 8);
bool PacketHandler::skipNext = false;
String PacketHandler::buff = "";

void PacketHandler::setConnectionStream(SoftwareSerial &con) {
	PacketHandler::con = con;
}

void PacketHandler::sendPacket(Packet p) {
	// Serialize and send the packet
    PacketHandler::sendPacket(Protocol::serialize(p));
}

void PacketHandler::sendPacket(String p) {
    // Set the status of the activity LED
	// TODO: sm.setActivityStatus(SWAIStatusManager::ACTIVITY_BLINK);

	// Convert the serialized packet into a char array
	char *charArr=new char[p.length()+1];
	charArr[p.length()]=0;
	memcpy(charArr,p.c_str(),p.length());

	// Serialize and send the packet
    PacketHandler::con.write(charArr);
	
    // Disable the activity LED
	// TODO: sm.setActivityStatus(SWAIStatusManager::ACTIVITY_OFF);
}

void PacketHandler::receive(char c) {
    if(PacketHandler::skipNext) {
        PacketHandler::buff += c;
        PacketHandler::skipNext = false;
                
    } else {
		// Check whether the next character should be skipped due to a backslash
        if(c == '\\')
            PacketHandler::skipNext = true;
                   
		// Check whether the current packet is ending
        if(c == Protocol::CHAR_PACKET_END) {
            // TODO: What is this used for?
            if(PacketHandler::receivedPacket(Protocol::deserialize(buff))) {}
//				computerSendPacket(PacketHandler::buff);
            PacketHandler::buff = "";
        }
                
		// Check whether a new packet is beginning
        if(c == Protocol::CHAR_PACKET_BEGIN)
            PacketHandler::buff = "";
    }
}

bool PacketHandler::receivedPacket(Packet p) {
	switch(p.getPacketType()) {
	case Protocol::PACKET_TYPE_CONNECT_REQ:
		// Send a connection confirm packet
        PacketHandler::sendPacket(Packet(0, Protocol::PACKET_TYPE_CONNECT));

	case Protocol::PACKET_TYPE_CONNECT:
		// Set the connected state to true
		ConnectionManager::setRobotConnected(true);
		return false;
		
	case Protocol::PACKET_TYPE_DISCONNECT_REC:
		// Send a connection confirm packet
        PacketHandler::sendPacket(Packet(0, Protocol::PACKET_TYPE_DISCONNECT));

	case Protocol::PACKET_TYPE_DISCONNECT:
		// Set the connected state to false
		ConnectionManager::setRobotConnected(false);
		break;

	default:
		break;
	}

	return true;
}