#ifndef NUMBERGUESSGAME_LED_H
#define NUMBERGUESSGAME_LED_H

#include <Arduino.h>

class Led {
private:
    int pin;
    bool state;

public:
    Led();

    Led(int pin);

    void setupPin();

    int getPin();

    bool getState();

    void setState(bool state);
};


#endif //NUMBERGUESSGAME_LED_H
