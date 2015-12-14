/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#ifndef NUMBERGUESSGAME_GLOBALS_H
#define NUMBERGUESSGAME_GLOBALS_H

#include <Arduino.h>

/**
 * Screen LED count.
 */
const int SCREEN_LED_COUNT = 4;

/**
 * Screen LED pins.
 */
const uint8_t SCREEN_LED_PINS[] = {3, 5, 6, 11};

/**
 * Define whether the screen LED is analog or digital.
 */
const bool SCREEN_LED_ANALOG = true;

/**
 * Green LED pin.
 */
const int GREEN_LED_PIN = 12;

/**
 * Define whether the green LED is analog or digital.
 */
const bool GREEN_LED_ANALOG = false;

/**
 * Red LED pin.
 */
const int RED_LED_PIN = 13;

/**
 * Define whether the green LED is analog or digital.
 */
const bool RED_LED_ANALOG = false;

/**
 * Button pin.
 */
const int BUTTON_PIN = 2;

/**
 * The delay in milliseconds for the game to start.
 */
const int START_DELAY = 1000;

/**
 * Pulse duration in milliseconds.
 */
const int PULSE_DURATION = 1000;

/**
 * Pulse brightness lowest.
 */
const int PULSE_BRIGHTNESS_LOW = 8;

/**
 * Pulse brightness highest.
 */
const int PULSE_BRIGHTNESS_HIGH = 80;

/**
 * The time in milliseconds to show the answer.
 */
const int ANSWER_VISIBLE_DURATION = 1500;

/**
 * The time in milliseconds for the input timeout.
 */
const int INPUT_TIMEOUT = 2000;

/**
 * The feedback low brightness value.
 */
const int FEEDBACK_BRIGHTNESS_LOW = 0;

/**
 * The feedback high brightness value.
 */
const int FEEDBACK_BRIGHTNESS_HIGH = 80;

/**
 * The feedback visible duration in milliseconds.
 */
const int FEEDBACK_VISIBLE_DURATION = 100;

/**
 * The number of milliseconds the user's input is visible.
 */
const int USER_INPUT_VISIBLE_DURATION = 1000;

/**
 * The USB serial baud rate.
 */
const int SERIAL_USB_BAUD = 9600;

/**
 * The multiplayer serial baud rate.
 */
// TODO: Tweak this rate!
const int SERIAL_MULTIPLAYER_BAUD = 19200;

/**
 * The serial RX (receive) pin used for multiplayer functionality.
 */
const int SERIAL_RX_PIN = 7;

/**
 * The serial TX (transmit) pin used for multiplayer functionality.
 */
const int SERIAL_TX_PIN = 8;

#endif //NUMBERGUESSGAME_GLOBALS_H
