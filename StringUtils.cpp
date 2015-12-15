/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#include "StringUtils.h"

std::vector<String> StringUtils::split(String str, char splitChar) {
    return StringUtils::split(str, splitChar, -1);
}

std::vector<String> StringUtils::split(String str, char splitChar, int max) {
    // Create a vector of string to add all parts into
	std::vector<String> strs;

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
    char charBuffer[16];

    while(idx != -1) {
        arg = str.substring((unsigned int) beginIdx, (unsigned int) idx);
        arg.toCharArray(charBuffer, 16);

        // add error handling for atoi:
        // TODO: Use atoi method? Like: http://stackoverflow.com/a/11916125/1000145
        strs.push_back(charBuffer);
        beginIdx = idx + 1;

        while(true) {
            idx = str.indexOf(splitChar, (unsigned int) beginIdx);

            // If the last part must be added now, set the index to infinity
            if(max != -1 && strs.size() >= max - 1) {
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

    strs.push_back(str.substring((unsigned int) beginIdx));

	// Return the string vector
	return strs;
}

int StringUtils::getCharacterCount(String str, char c) {
    // Create a variable to store the character count in
	int charCount = 0;

    // Compare each character in the string to the countable character, add the character if it is equal
    for(int i = 0; i < str.length(); i++)
        if(str.charAt((unsigned int) i) == c)
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
