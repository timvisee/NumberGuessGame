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
#include <AltSoftSerial.h>
#include <MemoryFree.h>
#include "Globals.h"
#include "PacketHandler.h"
#include "Random.h"
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
    Button button;

    /**
     * Software serial instance, to communicate to the other Arduino when doing a multiplayer game.
     */
    // DEBUG: SoftwareSerial con;
    AltSoftSerial con;

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
    void showSeekAnimation();
    void showNumber(int number);
    void showNumber(int number, int brightness, int duration);
    long generateRandomNumber();
    void memoryReport();
};

#endif //NUMBERGUESSGAME_CORE_H
