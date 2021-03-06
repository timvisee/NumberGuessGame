/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#include "Protocol.h"

String Protocol::serialize(Packet packet) {
	// Create the serialization buffer
	String s = "";
    
	// Print the PACKAGE_BEGIN character
	s += CHAR_PACKET_BEGIN;

	// Print the target device ID
	s += packet.getTargetDeviceId();

	// Print the packet separation char
	s += CHAR_PACKET_SEPARATOR;

	// Print the packet type
	s += packet.getPacketType();

	// Print the packet separation char
	s += CHAR_PACKET_SEPARATOR;

	// Print the integer array, if it contains any items
	int intSize = packet.getIntegersCount();
	if(intSize > 0) {
		// Print the integer type identifier
		s += DATA_ARR_TYPE_INT;
		s += CHAR_PACKET_DATA_ARRAY_SEPARATOR;

		// Print the count of items in this array
		s += intSize;
		s += CHAR_PACKET_DATA_ARRAY_SEPARATOR;

		// Get the integers
		int *intArr = packet.getIntegers();

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
	int boolSize = packet.getBooleansCount();
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
		bool *boolArr = packet.getBooleans();

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
	int strSize = packet.getStringsCount();
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
		String *strArr = packet.getStrings();

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

Packet Protocol::deserialize(String str) {
	// Trim the serialized string
	str.trim();

	// Split the serialized packet
    uint8_t partsSize = (uint8_t) StringUtils::getCharacterCountEscaped(str, CHAR_PACKET_SEPARATOR) + 1;
    if(partsSize > 3)
        partsSize = 3;
	String *parts = StringUtils::split(str, CHAR_PACKET_SEPARATOR, 3);

    // DEBUG: Properly implement error checking!
	// Make sure either two or three parts are available
	if(partsSize < 2 || partsSize > 3) {
        // Show an error message
//        Log::error("[PROTOCOL] Malformed packet! Doesn't contain correct number of packet parts.");

        // Delete the parts array from memory
        delete[] parts;

        // Return the base packet
        return Packet();
    }

    if(!StringUtils::isNumeric(parts[0])) {
        // Show an error message
//        Log::error("[PROTOCOL] Malformed packet! Target device ID is not numeric.");

        // Delete the parts array from memory
        delete[] parts;

        // Return the base packet
        return Packet();
    }

    if(!StringUtils::isNumeric(parts[1])) {
        // Show an error message
//        Log::error("[PROTOCOL] Malformed packet! Packet type is not numeric.");

        // Delete the parts array from memory
        delete[] parts;

        // Return the base packet
        return Packet();
    }

	// Get the packet target device ID
    uint8_t targetDeviceId = (uint8_t) parts[0].toInt();

	// Get the packet ID
    uint8_t packetType = (uint8_t) parts[1].toInt();

	// Define the three data arrays
	uint8_t intSize = 0;
	int *intArr = NULL;
	uint8_t boolSize = 0;
	bool *boolArr = NULL;
	uint8_t strSize = 0;
	String *strArr = NULL;

	// Check whether there's any extra data available
	if(partsSize == 3) {
		// Get the serialized data string
		String dataStr = parts[2];

		// Split the data arrays into string parts
		String *dataParts = StringUtils::split(dataStr, CHAR_PACKET_DATA_SEPARATOR);
		uint8_t dataPartsSize = (uint8_t) StringUtils::getCharacterCountEscaped(dataStr, CHAR_PACKET_DATA_SEPARATOR) + 1;

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
            uint8_t arrPartsSize = (uint8_t) StringUtils::getCharacterCountEscaped(arrStr,
                                                                                   CHAR_PACKET_DATA_ARRAY_SEPARATOR) + 1;

			// Get the array type
			String arrTypeStr = arrParts[0];
            uint8_t arrType = (uint8_t) arrTypeStr.toInt();

            // Get the size of the array
            String arrSizeStr = arrParts[1];
            int arrSize = (int) arrSizeStr.toInt();

            // Make sure the array doesn't go out of bound
            if(arrPartsSize < arrSize + 2) {
                // Show an error message
//                Log::error("[PROTOCOL] Malformed packet! Invalid data array size.");

                // Delete all dynamic arrays from memory
                delete[] parts;
                delete[] arrParts;
                delete[] dataParts;
                delete[] intArr;
                delete[] boolArr;
                delete[] strArr;

                // Return the base packet
                return Packet();
            }

			// Parse the integer arrays
			if(arrType == DATA_ARR_TYPE_INT) {
                // Delete the current pointer from the memory
                delete[] intArr;

                // Create a new array
                intArr = new int[arrSize];

                // Fill the array
                for(int i = 0; i < arrSize; i++)
                    intArr[intSize++] = (int) arrParts[i + 2].toInt();
            }

			// Parse the boolean arrays
			if(arrType == DATA_ARR_TYPE_BOOL) {
                // Delete the current pointer from the memory
                delete[] boolArr;

                // Create a new array
                boolArr = new bool[arrSize];

                // Fill the array
                for(int i = 0; i < arrSize; i++)
                    boolArr[boolSize++] = (arrParts[i + 2] == "1");
            }

            // Parse the string arrays
			if(arrType == DATA_ARR_TYPE_STR) {
                // Delete the current pointer from the memory
                delete[] strArr;

                // Create a new array
                strArr = new String[arrSize];

                // Fill the array
                for(int i = 0; i < arrSize; i++)
                    strArr[strSize++] = arrParts[i + 2];
            }

            // Delete the parts array from memory
            delete[] arrParts;
		}

        // Delete the data parts array from memory
        delete[] dataParts;
	}

    // Delete the parts array from memory
    delete[] parts;

	// Construct and return a new packet
	return Packet(targetDeviceId, packetType, intArr, intSize, boolArr, boolSize, strArr, strSize);
}