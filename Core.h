/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#ifndef NUMBERGUESSGAME_CORE_H
#define NUMBERGUESSGAME_CORE_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Globals.h"
#include "Core.h"
#include "Button.h"
#include "Timer.h"
#include "Led.h"

/**
 * Core class.
 */
class Core {
private:

    /**
     * Screen LED instances.
     */
//    Led screenLeds[SCREEN_LED_COUNT];
    Led * screenLeds;

    /**
     * Green LED instance.
     */
    Led greenLed;

    /**
     * Red LED instance.
     */
    Led redLed;

    /**
     * Status LED instance.
     */
    Led statusLed;

    /**
     * Button instance.
     */
    Button btn;

    /**
     * Software serial instance, to communicate to the other Arduino when doing a multiplayer game.
     */
    SoftwareSerial other;

public:
    /**
     * Constructor.
     */
    Core();

    /**
     * Called once on set up.
     */
    void setup();

    /**
     * Called each loop.
     */
    void loop();

    void connect();
    void update();
    void smartDelay(int delay);
    void showStartupAnimation();
    void showSlideAnimation();
    void showNumber(int number);
    void showNumber(int number, int brightness, int duration);
    long generateRandomNumber();
};

#endif //NUMBERGUESSGAME_CORE_H
