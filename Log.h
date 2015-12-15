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
#include "StringUtils.h"

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

public:
    /**
     * Initialize.
     */
    static void init();

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
};

#endif //NUMBERGUESSGAME_LOG_H
