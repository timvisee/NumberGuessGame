#include "Timer.h"

Timer::Timer(int timeout) {
    // Set the timeout to it's default
    this->timeout = -1;

    // Set the timeout variable
    this->timeoutDelay = timeout;
}

int Timer::getTimeoutDelay() {
    return this->timeoutDelay;
}

void Timer::setTimeoutDelay(int timeout) {
    this->timeoutDelay = timeout;
}

void Timer::start() {
    this->timeout = millis() + this->getTimeoutDelay();
}

bool Timer::isFinished() {
    return this->timeout < millis() && this->timeout >= 0;
}

void Timer::stop() {
    this->timeout = -1;
}