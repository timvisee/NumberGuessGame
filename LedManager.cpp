/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#include "LedManager.h"

Led *LedManager::screenLeds = new Led[SCREEN_LED_COUNT];
Led LedManager::greenLed = Led(GREEN_LED_PIN, GREEN_LED_ANALOG);
Led LedManager::redLed = Led(RED_LED_PIN, RED_LED_ANALOG);
Led LedManager::statusLed = Led(Led::STATUS_LED_PIN, Led::STATUS_LED_ANALOG);