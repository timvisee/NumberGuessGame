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
	int intsCount = p.getIntegersCount();
	if(intsCount > 0) {
		// Print the integer type identifier
		s += DATA_ARR_TYPE_INT;
		s += CHAR_PACKET_DATA_ARRAY_SEPARATOR;

		// Print the count of items in this array
		s += intsCount;
		s += CHAR_PACKET_DATA_ARRAY_SEPARATOR;

		// Get the integers
		std::vector<int> ints = p.getIntegers();

		// Print each number from the array
		for(int i = 0; i < intsCount; i++) {
			// Print the current item of the array
			s += ints[i];

			// Print the array data separator if it's not the last item
			if(i < intsCount)
				s += CHAR_PACKET_DATA_ARRAY_SEPARATOR;
		}
	}

	// Print the boolean array, if it contains any items
	int boolsCount = p.getBooleansCount();
	if(boolsCount > 0) {
		// Print an array separator if any other array was being print before
		if(intsCount > 0)
			s += CHAR_PACKET_DATA_SEPARATOR;

		// Print the boolean type identifier
		s += DATA_ARR_TYPE_BOOL;
		s += CHAR_PACKET_DATA_ARRAY_SEPARATOR;

		// Print the count of items in this array
		s += boolsCount;
		s += CHAR_PACKET_DATA_ARRAY_SEPARATOR;

		// Get the booleans
		std::vector<bool> bools = p.getBooleans();

		// Print each boolean from the array
		for(int i = 0; i < boolsCount; i++) {
			// Print the current item of the array
			s += bools[i] ? "1" : "0";

			// Print the array data separator if it's not the last item
			if(i < boolsCount - 1)
				s += CHAR_PACKET_DATA_ARRAY_SEPARATOR;
		}
	}

	// Print the string array, if it contains any items
	int strsCount = p.getStringsCount();
	if(strsCount > 0) {
		// Print an array separator if any other array was being print before
		if(intsCount > 0 || boolsCount > 0)
			s += CHAR_PACKET_DATA_SEPARATOR;

		// Print the string type identifier
		s += DATA_ARR_TYPE_STR;
		s += CHAR_PACKET_DATA_ARRAY_SEPARATOR;

		// Print the count of items in this array
		s += strsCount;
		s += CHAR_PACKET_DATA_ARRAY_SEPARATOR;

		// Get the strings
		std::vector<String> strs = p.getStrings();

		// Print each string from the array
		for(int i = 0; i < strsCount; i++) {
			// Print the current item of the array
			s += strs[i];

			// Print the array data separator if it's not the last item
			if(i < strsCount - 1)
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
	std::vector<String> parts = StringUtils::split(s, CHAR_PACKET_SEPARATOR, 3);

    // DEBUG: Properly implement error checking!
	// Make sure either two or three parts are available 
	if(parts.size() != 2 && parts.size() != 3) {
        // Show an error message
        Serial.print("[ERROR] Malformed packet! (");
        Serial.print(parts.size());
        Serial.println(" packets)");

        for(int i = 0; i < parts.size(); i++) {
            Serial.print(" - ");
            Serial.println(parts.at(i));
        }

        // Return the base packet
        return Packet();
    }

    if(!StringUtils::isNumeric(parts.at(0))) {
        // Show an error message
        Serial.println("[ERROR] Malformed packet! (part 0 not numeric)");

        Serial.print(" - ");
        Serial.println(parts.at(0));

        // Return the base packet
        return Packet();
    }

    if(!StringUtils::isNumeric(parts.at(1))) {
        // Show an error message
        Serial.println("[ERROR] Malformed packet! (part 1 not numeric)");

        Serial.print(" - ");
        Serial.println(parts.at(1));

        // Return the base packet
        return Packet();
    }

	// Get the packet target device ID
	int targetDeviceId = parts[0].toInt();

	// Get the packet ID
	int packetType = parts[1].toInt();

	// Define the three 
	std::vector<int> ints;
	std::vector<bool> bools;
	std::vector<String> strs;

	// Check whether there's any extra data available
	if(parts.size() == 3) {
		// Get the serialized data string
		String dataStr = parts[2];

		// Split the data arrays into string parts
		std::vector<String> dataParts = StringUtils::split(dataStr, CHAR_PACKET_DATA_SEPARATOR);

		// Parse each array
		for(int dataIndex = 0; dataIndex < dataParts.size(); dataIndex++) {
			// Convert the object to a 
			String arrStr = dataParts[dataIndex];

			// Check whether this part has a length of null
			arrStr.trim();
			if(arrStr.length() == 0)
				continue;

			// Split the array string
			std::vector<String> arrParts = StringUtils::split(arrStr, CHAR_PACKET_DATA_ARRAY_SEPARATOR);

			// Get the array type
			String arrTypeStr = arrParts.at(0);
            byte arrType = (byte) arrTypeStr.toInt();

            // Get the size of the array
            String arrSizeStr = arrParts.at(1);
            int arrSize = (int) arrSizeStr.toInt();

            // Make sure the array doesn't go out of bound
            if(arrParts.size() < arrSize + 2) {
                // Show an error message, and return the default packet
                Serial.println("[ERROR] Malformed packet. Missing elements in data array!");
                return Packet();
            }

			// Parse the integer arrays
			if(arrType == DATA_ARR_TYPE_INT)
				for(int i = 0; i < arrSize; i++)
					ints.push_back(arrParts[i + 2].toInt());

			// Parse the boolean arrays
			if(arrType == DATA_ARR_TYPE_BOOL)
				for(int i = 0; i < arrSize; i++)
					bools.push_back(arrParts[i + 2] == "1");

			// Parse the string arrays
			if(arrType == DATA_ARR_TYPE_STR)
				for(int i = 0; i < arrSize; i++)
					strs.push_back(arrParts[i + 2]);
		}
	}

	// Construct and return a new packet
	return Packet(
		targetDeviceId, packetType,
		ints, bools, strs
		);
}