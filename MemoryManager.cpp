/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#include "MemoryManager.h"

// Static field initialization
Timer MemoryManager::memoryTimer = Timer(MEMORY_REPORT_INTERVAL, true);

void MemoryManager::reportMemory() {
    // Get the current memory available (bytes)
    int memFree = freeMemory();

    // Initialize the logger if it hasn't been initialized yet
    Log::init();

    // Report the number of available memory
    // TODO: Log::info("M> " + String(memFree) + " b free"); Enable this again?
}

void MemoryManager::update() {
    // Make sure the timer is finished
    if(!MemoryManager::memoryTimer.isFinished())
        return;

    // Restart the timer
    MemoryManager::memoryTimer.start();

    // Report the memory to the log
    MemoryManager::reportMemory();
}
