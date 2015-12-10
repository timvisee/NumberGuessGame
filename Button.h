//
// Created by Tim on 10-12-2015.
//

#ifndef NUMBERGUESSGAME_BUTTON_H
#define NUMBERGUESSGAME_BUTTON_H


class Button {
private:
    /** Button pin. */
    uint8_t pin;

    bool lastState;

    bool pressedOnce;
    bool releasedOnce;

    long lockDelay;
    long lockUntil;

public:
    Button(uint8_t pin);

    void setupPin();

    void update();

    uint8_t getPin();

    bool isPressed();

    bool isPressedOnce();

    bool isReleasedOnce();

    long getLockDelay();

    void setLockDelay(long lockDelay);

    long getLockedUntil();

    void updateLockedUntil();

    bool isLockedUntil();
};


#endif //NUMBERGUESSGAME_BUTTON_H
