#include <Arduino.h>
#include "Button.h"
#include "Timer.h"

/** LED count. */
const int LED_COUNT = 4;
/** LED pins. */
const int LED_PINS[] = {8, 9, 10, 11};
/** Button pin. */
const int BUTTON_PIN = 2;

const int LED_DURATION = 1500;

const int TIMER_WAIT_DELAY = 2000;
const int TIMER_SHOW_ANSWER_DURATION = 500;

/** Button instance. */
Button btn(BUTTON_PIN);

/** Timer instance. */
Timer timer(TIMER_WAIT_DELAY);

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
    showNumber(0);

    // Start the timer
    timer.start();

    // Define a variable to store the number in the user has entered
    int answer = 0;

    // Use a while loop to handle the button presses
    while(!timer.isFinished()) {
        // Update the button state
        btn.update();

        // Handle button presses
        if(btn.isPressedOnce()) {
            // Increase the answer
            answer++;

            // Reset the answer
            timer.start();

            // Show some feedback, a button is pressed
            showNumber(15);
            delay(100);
            showNumber(0);
        }
    }

    // Stop the timer
    timer.stop();

    // Show the result the user has entered
    showNumber(answer);
    delay(TIMER_SHOW_ANSWER_DURATION);
    showNumber(0);
    delay(TIMER_SHOW_ANSWER_DURATION);

    // Verify the answer
    if(num == answer) {
        for(int i = 0; i < 16; i++) {
            showNumber(i);
            delay(100);
        }
    } else {
        showNumber(15);
        delay(100);
        showNumber(0);
        delay(100);

        showNumber(15);
        delay(100);
        showNumber(0);
        delay(100);

        showNumber(15);
        delay(100);
        showNumber(0);
        delay(100);
    }
}

/**
 * Show a number, using the four LEDs.
 *
 * @param number The number to show the LEDs for.
 */
void showNumber(int number) {
    for(byte i = 0; i < LED_COUNT; i++) {
        // Turn the LED on or off, based on the number
        digitalWrite(LED_PINS[i], number & 1);
        number /= 2;
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