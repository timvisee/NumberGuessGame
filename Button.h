/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#ifndef NUMBERGUESSGAME_BUTTON_H
#define NUMBERGUESSGAME_BUTTON_H

#include <Arduino.h>

/**
 * Button class.
 */
class Button {
private:
    /**
     * Button pin.
     */
    uint8_t pin;

    /**
     * Last state of the button, as boolean.
     */
    bool lastState;

    /**
     * Flag, whether the button has been pressed once.
     */
    bool pressedOnce;

    /**
     * Flag, whether the button has been released once.
     */
    bool releasedOnce;

    /**
     * The lock delay, in milliseconds.
     */
    long lockDelay;

    /**
     * The lock until in milliseconds, represents millis().
     */
    long lockUntil;

public:
    /**
     * Constructor.
     *
     * @param The pin of the button.
     */
    Button(uint8_t pin);

    /**
     * Set up the pin of the button.
     */
    void setupPin();

    /**
     * Update the button state.
     * Required before the use of various methods.
     */
    void update();

    /**
     * Get the button pin.
     *
     * @return Button pin.
     */
    uint8_t getPin();

    /**
     * Check whether the button is currently pressed.
     *
     * @return True if pressed, false if not.
     */
    bool isPressed();

    /**
     * Check whether the button has been pressed once.
     * This flag is reset when this method is called.
     *
     * @return True if button is pressed once, false otherwise.
     */
    bool isPressedOnce();

    /**
     * Check whether the button has been released once.
     * This flag is reset when this method is called.
     *
     * @return True if the button is released once, false otherwise.
     */
    bool isReleasedOnce();

    /**
     * Get the current lock delay in milliseconds.
     *
     * @return Lock delay.
     */
    long getLockDelay();

    /**
     * Set the lock delay in milliseconds.
     *
     * @param lockDelay The lock delay.
     */
    void setLockDelay(long lockDelay);

    /**
     * Get the locked until time in milliseconds.
     *
     * @return Locked until time.
     */
    long getLockedUntil();

    /**
     * Update the lock until time.
     */
    void updateLockedUntil();

    /**
     * Check whether the button is currently locked until the specified time.
     *
     * @return True if locked, false if not.
     */
    bool isLockedUntil();
};

#endif //NUMBERGUESSGAME_BUTTON_H
