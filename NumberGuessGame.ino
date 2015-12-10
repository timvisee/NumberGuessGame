#include <Arduino.h>
#include "Button.h"

/** LED count. */
const int LED_COUNT = 4;
/** LED pins. */
const int LED_PINS[] = {8, 9, 10, 11};
/** Button pin. */
const int BUTTON_PIN = 2;

const int LED_DURATION = 1500;

/** Button instance. */
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

int counter = 0;

/**
 * Called each loop.
 */
void loop() {
    // Generate a random number
    int num  = generateRandomNumber();

    // Show the actual number, and wait for a little while
    showNumber(num);
    delay(LED_DURATION);

    // Update the button state
    btn.update();



    // Increase the counter if the button is pressed
    if(btn.isPressedOnce())
        counter++;
}

/**
 * Show a number, using the four LEDs.
 */
void showNumber(int n) {
    for(byte i = 0; i < LED_COUNT; i++) {
        // Turn the LED on or off, based on the number
        digitalWrite(LED_PINS[i], n & 1);
        n /= 2;
    }
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
    return random(pow(2, LED_COUNT));
}