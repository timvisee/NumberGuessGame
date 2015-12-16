/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#ifndef NUMBERGUESSGAME_LOG_H
#define NUMBERGUESSGAME_LOG_H

#include <Arduino.h>
#include "Globals.h"
#include "StringUtils.h"\

/**
 * Log class.
 * A class to log messages to a console.
 */
class Log {
private:
    /**
     * Prefix for info messages.
     */
    static const String INFO_PREFIX;

    /**
     * Prefix for warning messages.
     */
    static const String WARNING_PREFIX;

    /**
     * Prefix for error messages.
     */
    static const String ERROR_PREFIX;

    /**
     * Prefix for debug messages.
     */
    static const String DEBUG_PREFIX;

    /**
     * True to show debug messages, false to ignore them.
     */
    static bool logDebug;

    /**
     * Remember whether the Log class is initialized.
     */
    static bool logInit;

public:
    /**
     * Initialize.
     */
    static void init();

    /**
     * Check whether the class is initialized or not. This is required before using the logger.
     */
    static bool isInit();

    /**
     * Log a message to the console.
     *
     * @param msg Message to log.
     */
    static void log(String msg);

    /**
     * Log a message to the console with prefix.
     *
     * @param prefix Prefix.
     * @param msg Message to log.
     */
    static void log(String prefix, String msg);

    /**
     * Log an info message to the console.
     *
     * @param msg Message to log.
     */
    static void info(String msg);

    /**
     * Log a warning message to the console.
     *
     * @param msg Message to log.
     */
    static void warning(String msg);

    /**
     * Log an error message to the console.
     *
     * @param msg Message to log.
     */
    static void error(String msg);

    /**
     * Log an debug message to the console.
     *
     * @param msg Message to log.
     */
    static void debug(String msg);

    /**
     * Check whether debug mode is enabled.
     *
     * @return True if debug mode is enabled, false otherwise.
     */
    static bool isDebug();

    /**
     * Set whether the debug mode is enabled.
     *
     * @param debug True to enable the debug mode, false otherwise.
     */
    static void setDebug(bool debug);
};

#endif //NUMBERGUESSGAME_LOG_H
