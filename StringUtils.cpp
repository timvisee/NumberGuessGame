/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#include "StringUtils.h"

std::vector<String> StringUtils::split(String str, char splitChar) {
    // Create a vector of string to add all parts into
	std::vector<String> strs;

    // DEBUG: Finish this code below!
    int beginIdx = 0;
    int idx = str.indexOf(splitChar);

    String arg;
    char charBuffer[16];

    while(idx != -1) {
        arg = str.substring(beginIdx, idx);
        arg.toCharArray(charBuffer, 16);

        // add error handling for atoi:
        // TODO: Use atoi method? Like: http://stackoverflow.com/a/11916125/1000145
        strs.push_back(charBuffer);
        beginIdx = idx + 1;
        idx = str.indexOf(splitChar, beginIdx);
    }

    strs.push_back(str.substring(beginIdx));

    // DEBUG: Remove this bullshit code, what the fucking hell?OIJW)E(UR()_W@$#IRT)*(U
	/*int index = 0;
	int index2;
 
	//for(int i = 0; i < splitCount + 1; i++) {
    while(true) {
        if(index != 0)
		index = str.indexOf(splitChar, index + 1);
		index2 = str.indexOf(splitChar, index + 1);
		
		// Ensure there isn't a backslash before the split char
		if(str.charAt(index - 1) == '\\')
			continue;

		if(index2 < 0)
			index2 = str.length() - 1;

		strs.push_back(str.substring(index, index2));
	}*/

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
    // Make sure all characters for the specified length are a digit, return false if nots
    for(int i = 0; i < len; i++)
        if(!isDigit(str.charAt(i)))
            return false;

    // All characters are a digit, return trues
    return true;
}
