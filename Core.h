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
#include "LedManager.h"
#include "Led.h"
#include "Button.h"
#include "PacketHandler.h"
#include "Random.h"
#include "Timer.h"

/**
 * Core class.
 */
class Core {
private:

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
    void showNumber(uint8_t number);
    void showNumber(uint8_t number, uint8_t brightness, int duration);
    long generateRandomNumber();
    void memoryReport();
};

#endif //NUMBERGUESSGAME_CORE_H
