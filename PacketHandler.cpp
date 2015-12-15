/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#include "PacketHandler.h"

// Initialize class members
AltSoftSerial PacketHandler::con = AltSoftSerial(); // TODO: Initialize something here?
bool PacketHandler::skipNext = false;
String PacketHandler::buff = "";

void PacketHandler::setConnectionStream(AltSoftSerial &con) {
	PacketHandler::con = con;
}

void PacketHandler::sendPacket(Packet packet) {
	// Serialize and send the packet
    PacketHandler::sendPacket(Protocol::serialize(packet));

    // Debug send packets
//    Log::debug("P> S: " + String(packet.getPacketType()));
}

void PacketHandler::sendPacket(String packet) {
    // Set the status of the activity LED
	// FIXME: sm.setActivityStatus(SWAIStatusManager::ACTIVITY_BLINK);

	// Convert the serialized packet into a char array
	char *charArr = new char[packet.length() + 1];
	charArr[packet.length()] = 0;
	memcpy(charArr, packet.c_str(), packet.length());

	// Serialize and send the packet
    PacketHandler::con.write(charArr);
	
    // Disable the activity LED
	// FIXME: sm.setActivityStatus(SWAIStatusManager::ACTIVITY_OFF);

    // Delete the char array from memory
    delete charArr;
}

void PacketHandler::receive(char data) {
    if(PacketHandler::skipNext) {
        PacketHandler::buff.concat(data);
        PacketHandler::skipNext = false;

    } else {
		// Check whether the next character should be skipped due to a backslash
        if(data == '\\')
            PacketHandler::skipNext = true;

		// Check whether the current packet is ending
        else if(data == Protocol::CHAR_PACKET_END) {
            // Deserialize the packet and call a method to handle the received packet
            PacketHandler::receivedPacket(Protocol::deserialize(PacketHandler::buff));

            // Clear the receive buffer
            PacketHandler::buff = "";
        }

		// Check whether a new packet is beginning
        else if(data == Protocol::CHAR_PACKET_BEGIN)
            PacketHandler::buff = "";

        else {
            PacketHandler::buff.concat(data);
        }
    }
}

void PacketHandler::receivedPacket(Packet packet) {
    // Debug received packets
//    Log::debug("P> R: " + String(packet.getPacketType()));

    // Debug: Some code to print and debug the received packets!
//    Serial.print("[PACKET] Packet received, type: ");
//    Serial.println(packet.getPacketType());

    // Code to print the packet contents
//    Serial.println("Integers:");
//    for(int i = 0s; i < packet.getIntegersCount(); i++) {
//        Serial.print(" - ");
//        Serial.println(packet.getIntegers()[i]);
//    }
//
//    Serial.println("Booleans:");
//    for(int i = 0; i < packet.getBooleansCount(); i++) {
//        Serial.print(" - ");
//        Serial.println(packet.getBooleans()[i]);
//    }
//
//    Serial.println("Strings:");
//    for(int i = 0; i < packet.getStringsCount(); i++) {
//        Serial.print(" - ");
//        Serial.println(packet.getStrings()[i]);
//    }

    // Handle the packet
    switch(packet.getPacketType()) {
	case Protocol::PACKET_TYPE_CONNECTION_REQUEST:
        Log::info("Con req");
		break;

	default:
//        Log::warning("P> Unknwn pckt!");
		break;
	}

    // Destroy the packet
    packet.destroy();
}