#ifndef NUMBERGUESSGAME_TIMER_H
#define NUMBERGUESSGAME_TIMER_H

#include <Arduino.h>

class Timer {
private:
    int timeoutDelay;
    long timeout;

public:
    Timer(int timeout);

    int getTimeoutDelay();

    void setTimeoutDelay(int timeout);

    void start();

    void start(int timeoutDelay);

    bool isFinished();

    void stop();
};


#endif //NUMBERGUESSGAME_TIMER_H
