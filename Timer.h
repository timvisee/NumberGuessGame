/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#ifndef NUMBERGUESSGAME_TIMER_H
#define NUMBERGUESSGAME_TIMER_H

#include <Arduino.h>

/**
 * Timer class.
 */
class Timer {
private:
    /**
     * Timeout delay in milliseconds.
     * */
    int timeoutDelay;

    /**
     * Timeout as time in milliseconds, represents millis() value.
     * */
    long timeout;

public:
    /**
     * Constructor.
     */
    Timer();

    /**
     * Constructor.
     *
     * @param timeout Timeout in milliseconds.
     */
    Timer(int timeout);

    /**
     * Get the timeout delay in milliseconds.
     *
     * @return Timeout delay.
     */
    int getTimeoutDelay();

    /**
     * Set the timeout delay in milliseconds.
     *
     * @return Timeout delay.
     */
    void setTimeoutDelay(int timeout);

    /**
     * Start the timer.
     */
    void start();

    /**
     * Start the timer with the specified delay in milliseconds.
     * This also updates the default delay of this timer.
     */
    void start(int timeoutDelay);

    /**
     * Check whether the timer is finished.
     *
     * @return True if finished, false if not.
     */
    bool isFinished();

    /**
     * Stop the timer if it's currently active.
     */
    void stop();
};

#endif //NUMBERGUESSGAME_TIMER_H
