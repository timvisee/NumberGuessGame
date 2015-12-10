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
Led greenLed(GREEN_LED_PIN);
/** Red LED instance. */
Led redLed(RED_LED_PIN);

/** Button instance. */
Button btn(BUTTON_PIN);

/** Timer instance. */
Timer timer;

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
        screenLeds[i] = Led(SCREEN_LED_PINS[i]);

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



    greenLed.setAnalogMode(true);

    greenLed.setState(!greenLed.getState());
    smartDelay(500);

    return;



    // Show the actual number, and wait for a little while
    showNumber(num);
    delay(LED_DURATION);
    showNumber(0);

    // Start the timer
    timer.start(TIMER_WAIT_DELAY);

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
        // Enable the green LED
        greenLed.setState(true);

        // FLash the answer
        for(int i = 0; i < 3; i++) {
            /*showNumber(num);
            delay(100);
            showNumber(0);
            delay(100);*/
            for(int i = 0; i < 256; i++) {
                analogWrite(redLed.getPin(), i);
                delay(1);
            }
            for(int i = 255; i >= 0; i--) {
                analogWrite(redLed.getPin(), i);
                delay(1);
            }
        }

    } else {
        redLed.setState(true);
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
    return random(pow(2, SCREEN_LED_COUNT));
}