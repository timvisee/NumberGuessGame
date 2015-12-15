#ifndef SWAIProtocol_h
#define SWAIProtocol_h

#include "Arduino.h"
#include "Packet.h"
#include "StringUtils.h"
#include "Stream.h"
#include "StandardCplusplus.h"
#include <SoftwareSerial.h>
#include <vector>

class Protocol {
public:
    static String serialize(Packet p);
	static Packet deserialize(String s);

    static const char CHAR_PACKET_BEGIN = 0x01;
    static const char CHAR_PACKET_END = 0x02;
    static const char CHAR_PACKET_SEPARATOR = 0x03;
    static const char CHAR_PACKET_DATA_SEPARATOR = 0x04;
    static const char CHAR_PACKET_DATA_ARRAY_SEPARATOR = 0x05;

    static const char DATA_ARR_TYPE_UNKNOWN = 0x00; // FIXME: Keep this one?
    static const char DATA_ARR_TYPE_INT = 0x01;
    static const char DATA_ARR_TYPE_BOOL = 0x02;
    static const char DATA_ARR_TYPE_STR = 0x03;

	static const int PACKET_TYPE_UNKNOWN = 0;
};

#endif
