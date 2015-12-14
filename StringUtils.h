/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#ifndef NUMBERGUESSGAME_STRINGUTILS_H
#define NUMBERGUESSGAME_STRINGUTILS_H

#include "Arduino.h"
#include "StandardCplusplus.h"
#include <vector>

/**
 * StringUtils class.
 * A class for some generic string utilities.
 */
class StringUtils {
public:
    // TODO: Remove the 'smart' parameter, because it isn't used?
	/**
	 * Split a string by the specified split character.
	 *
	 * @param str String to split.
	 * @param splitChar The character to split the string at.
	 * @param smart
	 *
	 * @return A vector of string parts.
	 */
    static std::vector<String> split(String str, char splitChar);

	/**
	 * Get the number of specific characters in a string.
	 *
	 * @param str The string to count the characters in.
	 * @param c Type of character to count.
	 *
	 * @return The number of characters, in the string.
	 */
	static int getCharacterCount(String str, char c);
};

#endif // NUMBERGUESSGAME_STRINGUTILS_H
