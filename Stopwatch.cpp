/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#include "Stopwatch.h"

Stopwatch::Stopwatch() {
    reset();
}

Stopwatch::Stopwatch(bool start) {
    // Start the stopwatch, or initialize
    if(start)
        start();
    else
        reset();
}

void Stopwatch::start() {
    this->time = millis();
}

bool Stopwatch::isStarted() {
    return this->time >= 0;
}

void Stopwatch::reset() {
    this->time = -1L;
}

long Stopwatch::getTime() {
    // Make sure the stopwatch is started
    if(!isStarted())
        return 0L;

    // Return the time
    return millis() - this->time;
}