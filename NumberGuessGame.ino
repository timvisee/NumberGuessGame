#include <Arduino.h>
#include "Button.h"
#include "Timer.h"
#include "Led.h"

/** Screen LED count. */
const int SCREEN_LED_COUNT = 4;
/** Screen LED pins. */
const int SCREEN_LED_PINS[] = {3, 5, 6, 9};
/** Green LED pin. */
const int GREEN_LED_PIN = 10;
/** Red LED pin */
const int RED_LED_PIN = 11;
/** Button pin. */
const int BUTTON_PIN = 2;



const int LED_DURATION = 1500;
const int TIMER_WAIT_DELAY = 2000;
const int TIMER_SHOW_ANSWER_DURATION = 500;



/** Screen LED instances. */
Led screenLeds[SCREEN_LED_COUNT];
/** Green LED instance. */
Led greenLed(GREEN_LED_PIN, true);
/** Red LED instance. */
Led redLed(RED_LED_PIN, true);

/** Button instance. */
Button btn(BUTTON_PIN);

/**
 * Called once on set up.
 */
void setup() {
    // Initial startup delay
    delay(200);

    // Enable serial port
    Serial.begin(9600);

    // Randomize the random seed
    randomSeed(analogRead(0));

    // Set up the answer LEDs
    for(int i = 0; i < SCREEN_LED_COUNT; i++) {
        // Construct the LED
        screenLeds[i] = Led(SCREEN_LED_PINS[i], true);

        // Set up the LED pin
        screenLeds[i].setupPin();
    }

    // Set up the green and red LED
    greenLed.setupPin();
    redLed.setupPin();

    // Set up the button pin
    btn.setupPin();
}

int counter = 0;

/**
 * Called each loop.
 */
void loop() {
    // Generate a random number
    int num  = generateRandomNumber();

    // Show the number as binary for the specified duration
    showNumber(num);
    smartDelay(LED_DURATION);
    showNumber(0);

    // Start the timer
    Timer timer(TIMER_WAIT_DELAY);
    timer.start();

    // Define a variable to store the number in the user has entered
    int answer = 0;

    // Use a while loop to handle the button presses
    while(!timer.isFinished() || answer <= 0) {
        // Fade the green light
        if(!greenLed.isFading()) {
            if(greenLed.getBrightness() <= 10)
                greenLed.fade(50, 1000);
            else if(greenLed.getBrightness() >= 50)
                greenLed.fade(10, 1000);
        }

        // Update everything
        update();

        // Handle button presses
        if(btn.isPressedOnce()) {
            // Increase the answer
            answer++;

            // Reset the answer
            timer.start();

            // Show some feedback, a button is pressed
            for(int i = 0; i < SCREEN_LED_COUNT; i++)
                screenLeds[i].fade(10, 100);
            smartDelay(100);
            for(int i = 0; i < SCREEN_LED_COUNT; i++)
                screenLeds[i].fade(0, 100);
        }
    }

    // Stop the timer
    timer.stop();

    // Turn of the green LED
    greenLed.setState(false);

    // Show the result the user has entered
    showNumber(answer);
    smartDelay(TIMER_SHOW_ANSWER_DURATION);
    showNumber(0);
    smartDelay(TIMER_SHOW_ANSWER_DURATION);

    // Verify the answer
    if(num == answer)
        // Enable the green LED
        greenLed.setState(true);

    else
        redLed.setState(true);

    smartDelay(1000);

    // Disable the green and red LED
    greenLed.setState(false);
    redLed.setState(false);
}

void update() {
    // Update the screen LEDs
    for(int i = 0; i < SCREEN_LED_COUNT; i++)
        screenLeds[i].update();

    // Update the green and red LED
    greenLed.update();
    redLed.update();

    // Update the button state
    btn.update();
}

/**
 * A smart delay method.
 * This method is similar to Arduino's delay method, but it keeps calling the update() method while the delay method is executed instead of freezing the Arduino.
 *
 * @param delay The delay in milliseconds to wait.
 */
void smartDelay(int delay) {
    // Create a timer, to track the passed time
    Timer timer(delay);

    // Start the timer
    timer.start();

    // Call the update method until the timer has passed the specified delay
    while(!timer.isFinished())
        update();
}

/**
 * Show a number, using the four LEDs.
 *
 * @param number The number to show the LEDs for.
 */
void showNumber(int number) {
    for(byte i = 0; i < SCREEN_LED_COUNT; i++) {
        // Turn the LED on or off, based on the number
        screenLeds[i].setState(number & 1);
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
    return random(pow(2, SCREEN_LED_COUNT) - 1) + 1;
}