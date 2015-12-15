/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 *
 * This project requires some external libraries to be installed, in the Arduino libraries directory.
 * - Arduino:
 *   The default Arduino libraries, installed with the Arduino installer.
 * - AltSoftSerial:
 *   Requires manual installation on the system, see:
 *   https://github.com/PaulStoffregen/AltSoftSerial
 * - StandardCplusplus:
 *   Requires manual installation on the system, see:
 *   https://github.com/maniacbug/StandardCplusplus
 * - MemoryFree:
 *   Requires manual installation on the system, see:
 *   https://github.com/maniacbug/MemoryFree
 *
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#include <Arduino.h>
#include "Core.h"

/**
 * Core instance. For all basic logic.
 */
Core core;

/**
 * Called once on set up.
 */
void setup() {
    // Route the setup call to the Core class
    core.setup();
}

/**
 * Called each loop.
 */
void loop() {
    // Route the loop call to the Core class
    core.loop();
}