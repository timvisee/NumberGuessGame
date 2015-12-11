/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#include <Arduino.h>
#include "Button.h"
#include "Timer.h"
#include "Led.h"

/**Screen LED count. */
const int SCREEN_LED_COUNT = 4;
/** Screen LED pins. */
const int SCREEN_LED_PINS[] = {3, 5, 6, 9};
/** Green LED pin. */
const int GREEN_LED_PIN = 10;
/** Red LED pin */
const int RED_LED_PIN = 11;
/** Button pin. */
const int BUTTON_PIN = 2;
/** The delay in milliseconds for the game to start. */
const int START_DELAY = 2000;
/** Pulse duration in milliseconds. */
const int PULSE_DURATION = 1000;
/** Pulse brightness lowest. */
const int PULSE_BRIGHTNESS_LOW = 8;
/** Pulse brightness highest. */
const int PULSE_BRIGHTNESS_HIGH = 80;
/** The time in milliseconds to show the answer. */
const int ANSWER_VISIBLE_DURATION = 1500;
/** The time in milliseconds for the input timeout. */
const int INPUT_TIMEOUT = 2000;
/** The feedback low brightness value. */
const int FEEDBACK_BRIGHTNESS_LOW = 0;
/** The feedback high brightness value. */
const int FEEDBACK_BRIGHTNESS_HIGH = 10;
/** The feedback visible duration in milliseconds. */
const int FEEDBACK_VISIBLE_DURATION = 100;
/** The number of milliseconds the user's input is visible. */
const int USER_INPUT_VISIBLE_DURATION = 1000;

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

    // Show a startup animation
    showStartupAnimation();

    // Wait a little before starting
    smartDelay(START_DELAY);
}

/**
 * Called each loop.
 */
void loop() {
    // Generate a random number
    int num  = generateRandomNumber();

    // Show the number as binary for the specified duration
    showNumber(num);
    smartDelay(ANSWER_VISIBLE_DURATION);
    showNumber(0);

    // Start the timer
    Timer timer(INPUT_TIMEOUT);
    timer.start();

    // Define a variable to store the number in the user has entered
    int answer = 0;

    // Use a while loop to handle the button presses
    while(!timer.isFinished() || answer <= 0) {
        // Pulse the green light
        if(!greenLed.isFading()) {
            // Fade the lights in or out
            if(greenLed.getBrightness() <= PULSE_BRIGHTNESS_LOW) {
                greenLed.fade(PULSE_BRIGHTNESS_HIGH, PULSE_DURATION);

                // Only fade red out if it is currently on
                if(redLed.getBrightness() != Led::BRIGHTNESS_LOW)
                    redLed.fade(PULSE_BRIGHTNESS_LOW, PULSE_DURATION);

            } else if(greenLed.getBrightness() >= PULSE_BRIGHTNESS_HIGH) {
                greenLed.fade(PULSE_BRIGHTNESS_LOW, PULSE_DURATION);
                redLed.fade(PULSE_BRIGHTNESS_HIGH, PULSE_DURATION);
            }
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
                screenLeds[i].fade(FEEDBACK_BRIGHTNESS_HIGH, FEEDBACK_VISIBLE_DURATION);
            smartDelay(FEEDBACK_VISIBLE_DURATION);
            for(int i = 0; i < SCREEN_LED_COUNT; i++)
                screenLeds[i].fade(FEEDBACK_BRIGHTNESS_LOW, FEEDBACK_VISIBLE_DURATION);
        }
    }

    // Stop the timer
    timer.stop();

    // Turn of the green LED
    greenLed.setState(false);
    redLed.setState(false);

    // Wait a second before showing the input
    smartDelay(500);

    // Show the result the user has entered
    showNumber(answer);
    smartDelay(USER_INPUT_VISIBLE_DURATION);

    // Verify the answer
    if(num == answer)
        greenLed.setState(true);
    else
        redLed.setState(true);

    // Wait before turning all LEDs off again
    smartDelay(1500);

    // Disable all LEDs
    showNumber(0);
    greenLed.setState(false);
    redLed.setState(false);

    // Show the slide animation before continuing to the next wave
    smartDelay(200);
    showSlideAnimation();
    smartDelay(400);
}

/**
 * Update method, should be called often to update things like the animation controllers of the LEDs.
 */
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
 * Show the startup animation.
 */
void showStartupAnimation() {
    // Loop the animation three times
    for(int i = 0; i < 3; i++)
        showSlideAnimation();
}

/**
 * Show the slide animation.
 */
void showSlideAnimation() {
    // Enable the LEDs
    for(int i = 0; i < SCREEN_LED_COUNT + 2; i++) {
        // Handle the LED
        if(i < SCREEN_LED_COUNT)
            screenLeds[i].fade(Led::BRIGHTNESS_HIGH, 250);
        else if(i == SCREEN_LED_COUNT)
            greenLed.fade(Led::BRIGHTNESS_HIGH, 250);
        else if(i == SCREEN_LED_COUNT + 1)
            redLed.fade(Led::BRIGHTNESS_HIGH, 250);

        // Wait a little before handling the next LED
        smartDelay(75);
    }

    // Disable the LEDs
    for(int i = 0; i < SCREEN_LED_COUNT + 2; i++) {
        // Handle the LED
        if(i < SCREEN_LED_COUNT)
            screenLeds[i].fade(Led::BRIGHTNESS_LOW, 250);
        else if(i == SCREEN_LED_COUNT)
            greenLed.fade(Led::BRIGHTNESS_LOW, 250);
        else if(i == SCREEN_LED_COUNT + 1)
            redLed.fade(Led::BRIGHTNESS_LOW, 250);

        // Wait a little before handling the next LED
        smartDelay(75);
    }
}

/**
 * Show a number, using the four LEDs.
 *
 * @param number The number to show the LEDs for.
 */
void showNumber(int number) {
    for(byte i = 0; i < SCREEN_LED_COUNT; i++) {
        screenLeds[i].setState(number & 1);
        number /= 2;
    }
}

/**
 * Show a number, using the four LEDs, with a custom brightness and fade duration.
 *
 * @param number The number to show the LEDs for.
 * @param brightness The target brightness.
 * @param duration The target duration in milliseconds.
 */
void showNumber(int number, int brightness, int duration) {
    for(byte i = 0; i < SCREEN_LED_COUNT; i++) {
        // Turn the LED on or off, based on the number with the specified brightness and duration
        if(number & 1)
            screenLeds[i].fade(brightness, duration);
        else
            screenLeds[i].setState(false);

        number /= 2;
    }
}

/**
 * Generate a random number, that is suitable for the number of available LEDs.
 *
 * @return Random number.
 */
int generateRandomNumber() {
    return random(pow(2, SCREEN_LED_COUNT) - 1) + 1;
}