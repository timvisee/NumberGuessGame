/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#include "StringUtils.h"

String *StringUtils::split(String str, char splitChar) {
    return StringUtils::split(str, splitChar, -1);
}

String *StringUtils::split(String str, char splitChar, int max) {
    // Count the number of elements the array will have
    uint8_t splitParts = (uint8_t) StringUtils::getCharacterCountEscaped(str, splitChar) + 1;
    if(splitParts > max && max >= 0)
        splitParts = (uint8_t) max;

    // Create a vector of string to add all parts into
	String *parts = new String[splitParts];
    uint8_t partsIndex = 0;

    // DEBUG: Finish this code below!
    int beginIdx = 0;
    int idx = 0;
    while(true) {
        idx = str.indexOf(splitChar, (unsigned int) idx);

        if(idx <= 0)
            break;

        if(str.charAt((unsigned int) (idx - 1)) != '\\')
            break;
    }

    String arg;
    char charBuffer[str.length()];

    while(idx != -1) {
        arg = str.substring((unsigned int) beginIdx, (unsigned int) idx);
        arg.toCharArray(charBuffer, str.length());

        // add error handling for atoi:
        // TODO: Use atoi method? Like: http://stackoverflow.com/a/11916125/1000145
        parts[partsIndex++] = (String) charBuffer;
        beginIdx = idx + 1;

        while(true) {
            idx = str.indexOf(splitChar, (unsigned int) beginIdx);

            // If the last part must be added now, set the index to infinity
            if(max != -1 && (partsIndex + 1) >= max) {
                idx = -1;
                break;
            }

            if(idx < 0)
                break;

            if(str.charAt((unsigned int) (idx - 1)) != '\\')
                break;

            beginIdx = idx + 1;
        }
    }

    // TODO: Should we still increase the partsIndex variable here?
    parts[partsIndex] = str.substring((unsigned int) beginIdx);

	// Return the string vector
	return parts;
}

int StringUtils::getCharacterCountEscaped(String str, char c) {
    // TODO: Make a constant of this escape char!
    return StringUtils::getCharacterCountEscaped(str, c, '\\');
}

int StringUtils::getCharacterCountEscaped(String str, char c, char escapeChar) {
    // Create a variable to store the character count in
	int charCount = 0;

    // TODO: Properly handle ignored characters with a backslash?

    // Compare each character in the string to the countable character, add the character if it is equal
    for(int i = 0; i < str.length(); i++)
        if(str.charAt((unsigned int) i) == c)
            if(i > 0 && str.charAt((unsigned int) i - 1) != escapeChar)
                charCount++;

    // Return the number of characters
	return charCount;
}

bool StringUtils::isNumeric(String str) {
    return StringUtils::isNumeric(str, str.length());
}

bool StringUtils::isNumeric(String str, int len) {
    // Make sure the length isn't greater than the length of the string
    if(len > str.length())
        return false;

    // Make sure at least one character is checked
    if(len < 1)
        return false;

    // Make sure all characters for the specified length are a digit, return false if nots
    for(int i = 0; i < len; i++)
        if(!isDigit(str.charAt((unsigned int) i)))
            return false;

    // All characters are a digit, return trues
    return true;
}

String StringUtils::formatLong(long number, uint8_t minDigits) {
    // Convert the number to a string
    String str = String(number);

    // Prefix the required number of zero's
    while(str.length() < minDigits)
        str = "0" + str;

    // Return the string
    return str;
}
