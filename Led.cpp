#include "Led.h"

Led::Led(int pin) {
    // Set the default variable values
    this->state = false;

    // Set the button pin
    this->pin = pin;
}

void Led::setupPin() {
    pinMode(this->pin, OUTPUT);
}

int Led::getPin() {
    return this->pin;
}

bool Led::getState() {
    return this->state;
}

void Led::setState(bool state) {
    // Set the state
    this->state = state;

    // Update the led
    digitalWrite(this->pin, state ? HIGH : LOW);
}