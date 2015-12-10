#ifndef NUMBERGUESSGAME_LED_H
#define NUMBERGUESSGAME_LED_H

#include <Arduino.h>

class Led {
private:
    int pin;
    bool state;
    bool analogMode;
    int fadeDuration;

    int fromBrightness;
    int toBrightness;
    long fromTime;
    long toTime;
    int brightness;

    static const int BRIGHTNESS_LOW;
    static const int BRIGHTNESS_HIGH;

public:
    Led();

    Led(int pin, bool analogMode);

    void setupPin();

    int getPin();

    bool inAnalogMode();

    void setAnalogMode(bool analogMode);

    int getFadeDuration();

    void setFadeDuration(int fadeDuration);

    void update();

    bool getState();

    void setState(bool state);

    int getBrightness();

    void setBrightness(int brightness);
};


#endif //NUMBERGUESSGAME_LED_H
