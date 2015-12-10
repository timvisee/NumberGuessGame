#ifndef NUMBERGUESSGAME_LED_H
#define NUMBERGUESSGAME_LED_H

#include <Arduino.h>

class Led {
private:
    int pin;
    bool state;
    bool analogMode;

    int fromBrightness;
    int toBrightness;
    long fromTime;
    long toTime;

    static const int BRIGHTNESS_LOW;
    static const int BRIGHTNESS_HIGH;

public:
    Led();

    Led(int pin);

    void setupPin();

    int getPin();

    bool inAnalogMode();

    void setAnalogMode(bool analogMode);

    void update();

    bool getState();

    void setState(bool state);
};


#endif //NUMBERGUESSGAME_LED_H
