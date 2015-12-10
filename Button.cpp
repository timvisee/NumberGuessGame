/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#include <Arduino.h>
#include "Button.h"

Button::Button(uint8_t pin) {
    // Initialize the default values
    this->pressedOnce = false;
    this->releasedOnce = false;
    this->lockDelay = 25;
    this->lockUntil = -1L;

    // Set the button pin
    this->pin = pin;
}

void Button::setupPin() {
    pinMode(this->getPin(), INPUT);
}

void Button::update() {
    // Get the current button state
    bool curState = this->isPressed();

    // Update the button state it if has changed
    if(this->lastState != curState && !this->isLockedUntil()) {
        // Update the last state
        this->lastState = curState;

        // Update the pressed and released once flags
        if(curState) {
            this->pressedOnce = true;
            this->releasedOnce = false;
        } else {
            this->pressedOnce = false;
            this->releasedOnce = true;
        }

        // Lock the button for the specified delay
        this->updateLockedUntil();
    }
}

uint8_t Button::getPin() {
    return this->pin;
}

bool Button::isPressed() {
    return digitalRead(this->pin) == HIGH;
}

bool Button::isPressedOnce() {
    // Get the pressed once state
    bool state = this->pressedOnce;

    // Reset the state
    this->pressedOnce = false;

    // Return the state
    return state;
}

bool Button::isReleasedOnce() {
    // Get the pressed once state
    bool state = this->releasedOnce;

    // Reset the state
    this->releasedOnce = false;

    // Return the state
    return state;
}

long Button::getLockDelay() {
    return this->lockDelay;
}

void Button::setLockDelay(long lockDelay) {
    this->lockDelay = lockDelay;
}

long Button::getLockedUntil() {
    return this->lockUntil;
}

void Button::updateLockedUntil() {
    this->lockUntil = millis() + this->getLockDelay();
}

bool Button::isLockedUntil() {
    return this->lockUntil > millis() && this->lockUntil >= 0;
}
