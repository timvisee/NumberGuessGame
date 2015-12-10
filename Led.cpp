#include "Led.h"

// Constants
const int Led::BRIGHTNESS_LOW = 0;
const int Led::BRIGHTNESS_HIGH = 255;

Led::Led() { }

Led::Led(int pin) {
    // Set the default variable values
    this->state = false;
    this->analogMode = false;
    this->fromBrightness = 0;
    this->fromTime = -1;
    this->toBrightness = 0;
    this->toTime = -1;

    // Set the button pin
    this->pin = pin;
}

void Led::setupPin() {
    pinMode(this->pin, OUTPUT);
}

int Led::getPin() {
    return this->pin;
}

bool Led::inAnalogMode() {
    return this->analogMode;
}

void Led::setAnalogMode(bool analogMode) {
    this->analogMode = analogMode;
}

void Led::update() {
    // Make sure the LED is analog
    if(!this->inAnalogMode())
        return;

    // Get the time delta
    long timeDelta = this->toTime - this->fromTime;

    // Get the brightness delta
    int brightnessDelta = this->toBrightness - this->fromBrightness;

    // Calculate the delta position
    int timeDeltaPos = min(max(millis() - this->fromTime, 0), timeDelta);

    // Calculate the current time factor
    double factor = timeDeltaPos / timeDelta;

    // Determine the brightness value
    int brightness = this->fromBrightness + (brightnessDelta * factor);

    // Set the brightness of the led
    analogWrite(this->pin, brightness);
}

bool Led::getState() {
    return this->state;
}

void Led::setState(bool state) {
    // Set the state
    this->state = state;

    // Update the led
    if(!this->inAnalogMode())
        digitalWrite(this->pin, state ? HIGH : LOW);

    else {
        // TODO: Use the current brightness value!
        // TODO: Use some method for this!
        this->fromBrightness = !state ? BRIGHTNESS_HIGH : BRIGHTNESS_LOW;
        this->toBrightness = state ? BRIGHTNESS_HIGH : BRIGHTNESS_LOW;
        this->fromTime = millis();
        this->toTime = millis() + 500;

        // Update the LED
        update();
    }
}