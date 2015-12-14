/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#ifndef NUMBERGUESSGAME_RANDOM_H
#define NUMBERGUESSGAME_RANDOM_H

#include <Arduino.h>

/**
 * Random class.
 * A class to generate random numbers.
 */
class Random {
public:
    /**
     * Get a random number, from the specified minimum number to the specified maximum number.
     * The maximum number is excluded.
     *
     * @param min Minimum number (included).
     * @param max Maximum number (excluded).
     *
     * @return A random number.
     */
    static int nextInt(int min, int max);

    /**
     * Get a random number, from zero to the specified maximum number. The maximum number is excluded.
     *
     * @param max Maximum number (excluded).
     *
     * @return A random number.
     */
    static int nextInt(int max);

    /**
     * Randomize the current random seed.
     */
    static void randomize();

    /**
     * Set the current random seed.
     */
    static void setSeed(unsigned int seed);
};

#endif //NUMBERGUESSGAME_RANDOM_H
