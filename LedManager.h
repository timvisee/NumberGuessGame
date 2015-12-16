/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#ifndef NUMBERGUESSGAME_LEDMANAGER_H
#define NUMBERGUESSGAME_LEDMANAGER_H

#include <Arduino.h>
#include "Globals.h"
#include "Led.h"

/**
 * Led manager class.
 */
class LedManager {
public:
    /**
     * Screen LED instances.
     */
    static Led * screenLeds;

    /**
     * Green LED instance.
     */
    static Led greenLed;

    /**
     * Red LED instance.
     */
    static Led redLed;

    /**
     * Status LED instance.
     */
    static Led statusLed;
};

// Initialize static fields
Led *LedManager::screenLeds = new Led[4];
Led LedManager::greenLed = Led();
Led LedManager::redLed = Led();
Led LedManager::statusLed = Led();

#endif //NUMBERGUESSGAME_LEDMANAGER_H
