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
#include "ButtonManager.h"
#include "Button.h"
#include "ConnectionManager.h"
#include "PacketHandler.h"
#include "Random.h"
#include "Timer.h"
#include "Stopwatch.h"

/**
 * Core class.
 */
class Core {
private:
    /**
     * Software serial instance, to communicate to the other Arduino when doing a multiplayer game.
     */
    AltSoftSerial con;

    /**
     * Timer to decide whether to continue in the connection method.
     */
    Timer connectTimerWait;

    /**
     * The current game number.
     */
    uint8_t gameNumber;

    /**
     * Flag whether the device has been fully started or not.
     */
    bool started;

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
    void gameLogic();

    /**
     * Connect to an arduino when in multiplayer mode.
     */
    void connect();

    /**
     * Method used to update all game logic.
     */
    void updateLogic();

    /**
     * A smart delay method, to efficiently execute the update call while waiting.
     */
    void smartDelay(int delay);

    /**
     * Play the startup animation on the screen.
     */
    void playStartupAnimation();

    /**
     * Play the slide animation on the screen.
     */
    void playSlideAnimation();

    /**
     * Play the seek animation on the screen.
     */
    void playSeekAnimation();

    /**
     * Show a number on the screen.
     */
    void showNumber(uint8_t number);

    /**
     * Generate a new game number.
     *
     * @return Generated number.
     */
    uint8_t generateNewGameNumber();
};

#endif //NUMBERGUESSGAME_CORE_H
