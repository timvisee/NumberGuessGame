/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#include "Stopwatch.h"

Stopwatch::Stopwatch() {
    this->time = -1L;
}

Stopwatch::Stopwatch(bool start) {
    // Start the stopwatch, or initialize
    if(start)
        this->time = millis();
    else
        this->time = -1L;
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