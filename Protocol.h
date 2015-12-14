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

    static const char CHAR_PACKET_BEGIN = 1;
    static const char CHAR_PACKET_END = 2;
    static const char CHAR_PACKET_SEPARATOR = 3;
    static const char CHAR_PACKET_DATA_SEPARATOR = 4;
    static const char CHAR_PACKET_DATA_ARRAY_SEPARATOR = 5;

    static const char DATA_ARR_TYPE_UNKNOWN = 0;
    static const char DATA_ARR_TYPE_INT = 1;
    static const char DATA_ARR_TYPE_BOOL = 2;
    static const char DATA_ARR_TYPE_STR = 3;

	static const int PACKET_TYPE_UNKNOWN = 0;
	static const int PACKET_TYPE_CONNECT = 1;
	static const int PACKET_TYPE_CONNECT_REQ = 2;
	static const int PACKET_TYPE_DISCONNECT = 3;
	static const int PACKET_TYPE_DISCONNECT_REC = 4;
	static const int PACKET_TYPE_PING = 5;
	static const int PACKET_TYPE_PING_REC = 6;
	static const int PACKET_TYPE_HEARTBEAT = 7;
	static const int PACKET_TYPE_MOTOR_SET = 10;
	static const int PACKET_TYPE_MOTOR_UPDATE = 11;
};

#endif
