/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#ifndef NUMBERGUESSGAME_BUTTONMANAGER_H
#define NUMBERGUESSGAME_BUTTONMANAGER_H

#include <Arduino.h>
#include "Globals.h"
#include "Button.h"

/**
 * Button manager class.
 */
class ButtonManager {
public:
    /**
     * Main button instance.
     */
    static Button button;
};

#endif //NUMBERGUESSGAME_BUTTONMANAGER_H
