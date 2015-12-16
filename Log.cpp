/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#include "Log.h"

const String Log::INFO_PREFIX = "I> ";
const String Log::WARNING_PREFIX = "W> ";
const String Log::ERROR_PREFIX = "E> ";
const String Log::DEBUG_PREFIX = "D> ";
bool Log::logDebug = false;
bool Log::logInit = false;

void Log::init() {
    // Make sure the logger hasn't been initialized already
    if(Log::isInit())
        return;

    // Begin the serial connection, with the proper baud rate
    Serial.begin(SERIAL_USB_BAUD);

    // Enable/disable the debug mode
    Log::setDebug(DEBUG);

    // Set the initialization flag
    Log::logInit = true;
}

bool Log::isInit() {
    return Log::logInit;
}

void Log::log(String msg) {
    // Log the message to the console
    Serial.println(msg);
    Serial.flush();
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

void Log::debug(String msg) {
    // Only show debug messages, if enabled
    if(Log::logDebug)
        Log::log(DEBUG_PREFIX, msg);
}

bool Log::isDebug() {
    return Log::logDebug;
}

void Log::setDebug(bool debug) {
    Log::logDebug = debug;
}