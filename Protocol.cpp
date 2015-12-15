/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#include "Protocol.h"

String Protocol::serialize(Packet p) {
	// Create the serialization buffer
	String s = "";
    
	// Print the PACKAGE_BEGIN character
	s += CHAR_PACKET_BEGIN;

	// Print the target device ID
	s += p.getTargetDeviceId();

	// Print the packet separation char
	s += CHAR_PACKET_SEPARATOR;

	// Print the packet type
	s += p.getPacketType();

	// Print the packet separation char
	s += CHAR_PACKET_SEPARATOR;

	// Print the integer array, if it contains any items
	int intSize = p.getIntegersCount();
	if(intSize > 0) {
		// Print the integer type identifier
		s += DATA_ARR_TYPE_INT;
		s += CHAR_PACKET_DATA_ARRAY_SEPARATOR;

		// Print the count of items in this array
		s += intSize;
		s += CHAR_PACKET_DATA_ARRAY_SEPARATOR;

		// Get the integers
		int *intArr = p.getIntegers();

		// Print each number from the array
		for(int i = 0; i < intSize; i++) {
			// Print the current item of the array
			s += intArr[i];

			// Print the array data separator if it's not the last item
			if(i < intSize)
				s += CHAR_PACKET_DATA_ARRAY_SEPARATOR;
		}
	}

	// Print the boolean array, if it contains any items
	int boolSize = p.getBooleansCount();
	if(boolSize > 0) {
		// Print an array separator if any other array was being print before
		if(intSize > 0)
			s += CHAR_PACKET_DATA_SEPARATOR;

		// Print the boolean type identifier
		s += DATA_ARR_TYPE_BOOL;
		s += CHAR_PACKET_DATA_ARRAY_SEPARATOR;

		// Print the count of items in this array
		s += boolSize;
		s += CHAR_PACKET_DATA_ARRAY_SEPARATOR;

		// Get the booleans
		bool *boolArr = p.getBooleans();

		// Print each boolean from the array
		for(int i = 0; i < boolSize; i++) {
			// Print the current item of the array
			s += boolArr[i] ? "1" : "0";

			// Print the array data separator if it's not the last item
			if(i < boolSize - 1)
				s += CHAR_PACKET_DATA_ARRAY_SEPARATOR;
		}
	}

	// Print the string array, if it contains any items
	int strSize = p.getStringsCount();
	if(strSize > 0) {
		// Print an array separator if any other array was being print before
		if(intSize > 0 || boolSize > 0)
			s += CHAR_PACKET_DATA_SEPARATOR;

		// Print the string type identifier
		s += DATA_ARR_TYPE_STR;
		s += CHAR_PACKET_DATA_ARRAY_SEPARATOR;

		// Print the count of items in this array
		s += strSize;
		s += CHAR_PACKET_DATA_ARRAY_SEPARATOR;

		// Get the strings
		String *strArr = p.getStrings();

		// Print each string from the array
		for(int i = 0; i < strSize; i++) {
			// Print the current item of the array
			s += strArr[i];

			// Print the array data separator if it's not the last item
			if(i < strSize - 1)
				s += CHAR_PACKET_DATA_ARRAY_SEPARATOR;
		}
	}

	// Print the PACKET_END character
	s += CHAR_PACKET_END;

	// Return the serialized data
	return s;
}

Packet Protocol::deserialize(String s) {
	// Trim the serialized string
	s.trim();

	// Split the serialized packet
    uint8_t partsSize = (uint8_t) StringUtils::getCharacterCount(s, CHAR_PACKET_SEPARATOR);
    if(partsSize > 3)
        partsSize = 3;
	String *parts = StringUtils::split(s, CHAR_PACKET_SEPARATOR, 3);

    // DEBUG: Properly implement error checking!
	// Make sure either two or three parts are available 
	if(partsSize < 2 || partsSize > 3) {
        // Show an error message
        Serial.print("[ERROR] Malformed packet! (");
        Serial.print(partsSize);
        Serial.println(" packets)");

        for(int i = 0; i < partsSize; i++) {
            Serial.print(" - ");
            Serial.println(parts[i]);
        }

        // Return the base packet
        return Packet();
    }

    if(!StringUtils::isNumeric(parts[0])) {
        // Show an error message
        Serial.println("[ERROR] Malformed packet! (part 0 not numeric)");

        Serial.print(" - ");
        Serial.println(parts[0]);

        // Return the base packet
        return Packet();
    }

    if(!StringUtils::isNumeric(parts[1])) {
        // Show an error message
        Serial.println("[ERROR] Malformed packet! (part 1 not numeric)");

        Serial.print(" - ");
        Serial.println(parts[1]);

        // Return the base packet
        return Packet();
    }

	// Get the packet target device ID
    uint8_t targetDeviceId = (uint8_t) parts[0].toInt();

	// Get the packet ID
    uint8_t packetType = (uint8_t) parts[1].toInt();

	// Define the three data arrays
	uint8_t intSize = 0;
	int * intArr;
	uint8_t boolSize = 0;
	bool * boolArr;
	uint8_t strSize = 0;
	String * strArr;

	// Check whether there's any extra data available
	if(partsSize == 3) {
		// Get the serialized data string
		String dataStr = parts[2];

		// Split the data arrays into string parts
		String *dataParts = StringUtils::split(dataStr, CHAR_PACKET_DATA_SEPARATOR);
		uint8_t dataPartsSize = (uint8_t) StringUtils::getCharacterCount(dataStr, CHAR_PACKET_DATA_SEPARATOR);

		// Parse each array
		for(int dataIndex = 0; dataIndex < dataPartsSize; dataIndex++) {
			// Convert the object to a 
			String arrStr = dataParts[dataIndex];

			// Check whether this part has a length of null
			arrStr.trim();
			if(arrStr.length() == 0)
				continue;

			// Split the array string
			String *arrParts = StringUtils::split(arrStr, CHAR_PACKET_DATA_ARRAY_SEPARATOR);
            uint8_t arrPartsSize = (uint8_t) StringUtils::getCharacterCount(arrStr, CHAR_PACKET_DATA_ARRAY_SEPARATOR);

			// Get the array type
			String arrTypeStr = arrParts[0];
            byte arrType = (byte) arrTypeStr.toInt();

            // Get the size of the array
            String arrSizeStr = arrParts[1];
            int arrSize = (int) arrSizeStr.toInt();

            // Make sure the array doesn't go out of bound
            if(arrPartsSize < arrSize + 2) {
                // Show an error message, and return the default packet
                Serial.println("[ERROR] Malformed packet. Missing elements in data array!");
                return Packet();
            }

			// Parse the integer arrays
			if(arrType == DATA_ARR_TYPE_INT)
				for(int i = 0; i < arrSize; i++)
					intArr[intSize++] = (int) arrParts[i + 2].toInt();

			// Parse the boolean arrays
			if(arrType == DATA_ARR_TYPE_BOOL)
				for(int i = 0; i < arrSize; i++)
					boolArr[boolSize++] = (arrParts[i + 2] == "1");

			// Parse the string arrays
			if(arrType == DATA_ARR_TYPE_STR)
				for(int i = 0; i < arrSize; i++)
					strArr[strSize++] = arrParts[i + 2];
		}
	}

	// Construct and return a new packet
	// FIXME: Fix returned statement here!
	return Packet();
	/*return Packet(
		targetDeviceId, packetType,
		ints, bools, strs
		);*/
}