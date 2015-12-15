/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#include "Log.h"

const String Log::INFO_PREFIX = "[INFO] ";
const String Log::WARNING_PREFIX = "[WARNING] ";
const String Log::ERROR_PREFIX = "[ERROR] ";

void Log::init() {
    // Begin the serial connection, with the proper baud rate
    Serial.begin(SERIAL_USB_BAUD);

    // Show a status message
    Log::info("Logger initialized!");
}

void Log::log(String msg) {
    // Log the message to the console
    Serial.println(msg);
}

void Log::log(String prefix, String msg) {
    Log::log(prefix + msg);
}

void Log::info(String msg) {
    Log::log(INFO_PREFIX, msg);
}

void Log::warning(String msg) {
    Log::log(WARNING_PREFIX, msg);
}

void Log::error(String msg) {
    Log::log(ERROR_PREFIX, msg);
}