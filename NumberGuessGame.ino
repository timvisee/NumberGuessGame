#include <Arduino.h>
#include "Button.h"

/** LED count. */
const int LED_COUNT = 4;
/** LED pins. */
const int LED_PINS[] = {8, 9, 10, 11};
/** Button pin. */
const int BUTTON_PIN = 2;

Button btn(BUTTON_PIN);

/**
 * Called once on set up.
 */
void setup() {
    // Set up the LED pins
    for(int i = 0; i < LED_COUNT; i++)
        pinMode(LED_PINS[i], OUTPUT);

    // Set up the button
    btn.setupPin();

    // Enable serial port
    Serial.begin(9600);
}

/**
 * Called each loop.
 */
void loop() {
    // Generate a random number
    int num  = generateRandomNumber();

    // Update the button
    btn.update();

    if(btn.isPressedOnce())
        Serial.println("Pressed!");
    if(btn.isReleasedOnce())
        Serial.println("Released!");

    return;

//    for(int i = 0; i < LED_COUNT; i++) {
//        digitalWrite(LED_PINS[i], HIGH);
//
//        // Update the button state
//        btn.update();
//
//        if(btn.isPressed())
//            break;
//    }
//    for(int i = 0; i < LED_COUNT; i++) {
//        digitalWrite(LED_PINS[i], LOW);
//
//
//        if(!btn.isPressed())
//            break;
//    }
}

/**
 * Get the current button state.
 *
 * @return True if pressed, false if not.
 */
bool getButtonState() {
    return digitalRead(BUTTON_PIN) == HIGH;
}

/**
 * Generate a random number, that is suitable for the number of available LEDs.
 *
 * @return Random number.
 */
int generateRandomNumber() {
    random(0, LED_COUNT * LED_COUNT);
}