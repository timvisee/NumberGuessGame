/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#include "Led.h"

const uint8_t Led::BRIGHTNESS_LOW = 0;
const uint8_t Led::BRIGHTNESS_HIGH = 255;
const uint8_t Led::STATUS_LED_PIN = 13;
const bool Led::STATUS_LED_ANALOG = false;

Led::Led() {
    this->pin = Led::STATUS_LED_PIN;
}

Led::Led(uint8_t pin, bool analogMode) {
    // Set the default variable values
    this->state = false;
    this->analogMode = analogMode;
    this->fadeDuration = 180;
    this->fromBrightness = 0;
    this->fromTime = -1;
    this->toBrightness = 0;
    this->toTime = -1;
    this->brightness = 0;

    // Set the LED pin
    this->pin = pin;
}

void Led::setupPin() {
    pinMode(this->pin, OUTPUT);
}

uint8_t Led::getPin() {
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
    unsigned long timeDelta = (unsigned long) (this->toTime - this->fromTime);

    // Get the brightness delta
    int brightnessDelta = this->toBrightness - this->fromBrightness;

    // Calculate the delta position
    int timeDeltaPos = (int) min(max(millis() - this->fromTime, 0), timeDelta);

    // Calculate the current time factor
    float factor = (float) timeDeltaPos / (float) timeDelta;

    // Determine the brightness value
    uint8_t brightness = (uint8_t) (this->fromBrightness + (brightnessDelta * factor));

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

void Led::fade(uint8_t brightness) {
    this->fade(brightness, this->getFadeDuration());
}

void Led::fade(uint8_t brightness, int duration) {
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

bool Led::isFading() {
    return (this->toTime > millis() && this->brightness != this->toBrightness);
}

uint8_t Led::getBrightness() {
    return this->brightness;
}

void Led::setBrightness(uint8_t brightness) {
    // Store the brightness
    this->brightness = brightness;

    // Set the actual brightness
    analogWrite(this->pin, brightness);
}

uint8_t Led::getToBrightness() {
    return this->toBrightness;
}

int Led::getFadeTimeLeft() {
    return (int) (this->toTime - millis());
}
