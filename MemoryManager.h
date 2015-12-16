/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#ifndef NUMBERGUESSGAME_MEMORYMANAGER_H
#define NUMBERGUESSGAME_MEMORYMANAGER_H

#include <MemoryFree.h>
#include "Globals.h"
#include "Log.h"
#include "Timer.h"

/**
 * MemoryManager class.
 */
class MemoryManager {
private:
    /**
     * Timer for the memory report.
     */
    static Timer memoryTimer;

public:
    /**
     * Report the current memory state to the console.
     */
    static void reportMemory();

    /**
     * Do an update call, to report the memory if the timer has reached.
     */
    static void update();
};

#endif //NUMBERGUESSGAME_MEMORYMANAGER_H
