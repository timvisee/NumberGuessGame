#ifndef NUMBERGUESSGAME_LED_H
#define NUMBERGUESSGAME_LED_H

#include <Arduino.h>

class Led {
public:
    static const int BRIGHTNESS_LOW;
    static const int BRIGHTNESS_HIGH;

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

    void fade(int brightness);

    void fade(int brightness, int duration);

    bool isFading();

    int getBrightness();

    void setBrightness(int brightness);
};


#endif //NUMBERGUESSGAME_LED_H
