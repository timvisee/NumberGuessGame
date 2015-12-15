/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#ifndef NUMBERGUESSGAME_STOPWATCH_H
#define NUMBERGUESSGAME_STOPWATCH_H

#include <Arduino.h>

/**
 * Stopwatch class.
 */
class Stopwatch {
private:
    /**
     * The time.
     */
    long time;

public:
    /**
     * Constructor.
     */
    Stopwatch();

    /**
     * Constructor.
     *
     * @param start True to start, false otherwise.
     */
    Stopwatch(bool start);

    /**
     * Start the stopwatch.
     */
    void start();

    /**
     * Check whether the stopwatch is started.
     *
     * @return True if started, false if not.
     */
    bool isStarted();

    /**
     * Reset the stopwatch.
     */
    void reset();

    /**
     * Get the stopwatch time since it started.
     * Zero will be returned if the stopwatch wasn't started.
     *
     * @return Time since the stopwatch has started, or zero.
     */
    long getTime();
};


#endif //NUMBERGUESSGAME_STOPWATCH_H
