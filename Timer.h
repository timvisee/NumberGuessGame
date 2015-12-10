#ifndef NUMBERGUESSGAME_TIMER_H
#define NUMBERGUESSGAME_TIMER_H


class Timer {
private:
    int timeout;

public:
    Timer(int timeout);

    int getTimeout();

    int setTimeout(int timeout);

    void start();

    bool isFinished();

    void stop();
};


#endif //NUMBERGUESSGAME_TIMER_H
