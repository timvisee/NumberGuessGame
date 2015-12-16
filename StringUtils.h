/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#ifndef NUMBERGUESSGAME_STRINGUTILS_H
#define NUMBERGUESSGAME_STRINGUTILS_H

#include <Arduino.h>
#include "Globals.h"

/**
 * StringUtils class.
 * A class for some generic string utilities.
 */
class StringUtils {
public:
    /**
     * Split a string by the specified split character.
     *
     * @param str String to split.
     * @param splitChar The character to split the string at.
     *
     * @return A vector of string parts.
     */
    static String *split(String str, char splitChar);

    /**
     * Split a string by the specified split character.
     * If the maximum number of parts is reached, the remaining string parts will be put into the last part of the vector.
     *
     * @param str String to split.
     * @param splitChar The character to split the string at.
     * @param max The maximum number of parts.
     *
     * @return A vector of string parts.
     */
    static String *split(String str, char splitChar, int max);

    /**
     * Get the number of specific characters in a string.
     *
     * @param str The string to count the characters in.
     * @param c Type of character to count.
     * @param escapeChar True to escape characters prefixed with a backslash, false if not.
     *
     * @return The number of characters, in the string.
     */
    static int getCharacterCountEscaped(String str, char c);

    /**
     * Get the number of specific characters in a string.
     *
     * @param str The string to count the characters in.
     * @param c Type of character to count.
     * @param escapeChar The character used to escape chars prefixed with this character.
     *
     * @return The number of characters, in the string.
     */
    static int getCharacterCountEscaped(String str, char c, char escapeChar);

    /**
     * Check whether a string only contains numeric characters (digits).
     * The string must be at least one character long, or false will be returned.
     *
     * @param str String to check.
     *
     * @return True if all characters are numeric (digits), false otherwise.
     */
    static bool isNumeric(String str);

    /**
     * Check whether a string only contains numeric characters (digits).
     * The specified length must be at least one, or false will be returned.
     * If the length is greater than the actual string, false will be returned.
     *
     * @param str String to check.
     * @param len Length of the string to check, from the beginning of the string.
     *
     * @return True if all characters are numeric (digits), false otherwise.
     */
    static bool isNumeric(String str, int len);

    /**
     * Format a long value to have a minimum of the specified number of digits.
     *
     * @param number The number to format.
     * @param minDigits Minimum of digits.
     *
     * @return Formatted string.
     */
    static String formatLong(long number, uint8_t minDigits);
};

#endif // NUMBERGUESSGAME_STRINGUTILS_H
