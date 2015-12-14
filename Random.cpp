/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#include "Random.h"

static int Random::nextInt(int max) {
    return this->nextInt(0, max);
}

static int Random::nextInt(int min, int max) {
    return (int) random((long) min, (long) max);
}

static int Random::randomize() {
    // Define the new seed variable
    unsigned int seed = 1;

    // Create a semi-random number to use as seed
    for(int i = 0; i < 6; i++)
        seed *= analogRead(i);

    // Set the actual seed
    this->setSeed(analogRead(0));
}

static void Random::setSeed(unsigned int seed) {
    // Set the seed in the Arduino library
    randomSeed(seed);
}