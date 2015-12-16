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
    LedManager::statusLed.setState(true);

	// Convert the serialized packet into a char array
	char *charArr = new char[packet.length() + 1];
	charArr[packet.length()] = 0;
	memcpy(charArr, packet.c_str(), packet.length());

	// Serialize and send the packet
    PacketHandler::con.write(charArr);
	
    // Disable the activity LED
    LedManager::statusLed.setState(false);

    // Delete the char array from memory
    delete charArr;
}

void PacketHandler::receive(char data) {
    // Enable the status LED
    LedManager::statusLed.setState(false);

    // Process the received data
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

        else
            PacketHandler::buff.concat(data);
    }

    // Disable the status LED
    LedManager::statusLed.setState(false);
}

void PacketHandler::receivedPacket(Packet packet) {
    // Debug received packets
//    Log::debug("P> R: " + String(packet.getPacketType()));

    // Handle the packet
    switch(packet.getPacketType()) {
        case Protocol::PACKET_TYPE_CONNECTION_REQUEST: {
            // Make sure the device isn't connected already and is in multiplayer mode
            if(ConnectionManager::isConnected() || !ConnectionManager::isMultiplayer() || !ConnectionManager::isConnecting())
                break;

            // Set the connected and master flag
            ConnectionManager::setConnected(true);
            ConnectionManager::setMaster(false);

            // Send a connected packet
            Packet connectPacket = Packet(1, Protocol::PACKET_TYPE_CONNECTION_ACCEPT);
            PacketHandler::sendPacket(connectPacket);
            connectPacket.destroy();
            break;
        }

        case Protocol::PACKET_TYPE_CONNECTION_ACCEPT: {
            // Make sure the device isn't connected already and is in multiplayer mode
            if(!ConnectionManager::isMultiplayer() || !ConnectionManager::isConnecting())
                break;

            // Set the connected and master flag
            ConnectionManager::setConnected(true);
            ConnectionManager::setMaster(true);
            break;
        }

        case Protocol::PACKET_TYPE_GAME_START: {
            // Make sure the device isn't connected already and is in multiplayer mode
            if(!ConnectionManager::isMultiplayer() || ConnectionManager::isMaster())
                break;

            // Get the game number
            ConnectionManager::setGameNumber((uint8_t) packet.getIntegers()[0]);
            break;
        }

	default:
        Log::warning("P> Unknwn pckt!");
		break;
	}

    // Destroy the packet
    packet.destroy();
}