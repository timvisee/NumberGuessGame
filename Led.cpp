#include "Led.h"

// Constants
const int Led::BRIGHTNESS_LOW = 0;
const int Led::BRIGHTNESS_HIGH = 255;

Led::Led() { }

Led::Led(int pin, bool analogMode) {
    // Set the default variable values
    this->state = false;
    this->analogMode = analogMode;
    this->fadeDuration = 180;
    this->fromBrightness = 0;
    this->fromTime = -1;
    this->toBrightness = 0;
    this->toTime = -1;
    this->brightness = 0;

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

int Led::getFadeDuration() {
    return this->fadeDuration;
}

void Led::setFadeDuration(int fadeDuration) {
    this->fadeDuration = fadeDuration;
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
    double factor = (double) timeDeltaPos / (double) timeDelta;

    // Determine the brightness value
    int brightness = this->fromBrightness + (brightnessDelta * factor);

    // Set the brightness of the led
    this->setBrightness(brightness);
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

    else
        this->fade(state ? BRIGHTNESS_HIGH : BRIGHTNESS_LOW);
}

void Led::fade(int brightness) {
    this->fade(brightness, this->getFadeDuration());
}

void Led::fade(int brightness, int duration) {
    // Set the animation variables
    this->fromBrightness = this->getBrightness();
    this->toBrightness = brightness;
    this->fromTime = millis();
    this->toTime = millis() + duration;

    // Update
    this->update();

    // Update the state flag
    this->state = ((double) brightness / (double) (BRIGHTNESS_HIGH - BRIGHTNESS_LOW)) >= 0.5;
}

int Led::getBrightness() {
    return this->brightness;
}

void Led::setBrightness(int brightness) {
    // Store the brightness
    this->brightness = brightness;

    // Set the actual brightness
    analogWrite(this->pin, brightness);
}