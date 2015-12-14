/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#include "StringUtils.h"

std::vector<String> StringUtils::split(String str, char splitChar) {
	int splitCount = StringUtils::getCharacterCount(str, splitChar);
	std::vector<String> strs;

	int index = -1;
	int index2;
 
	for(int i = 0; i < splitCount - 1; i++) {
		index = str.indexOf(splitChar, index + 1);
		index2 = str.indexOf(splitChar, index + 1);
		
		// Ensure there isn't a backslash before the split char
		if(str.charAt(index - 1) == '\\')
			continue;

		if(index2 < 0)
			index2 = str.length() - 1;

		strs.push_back(str.substring(index, index2));
	}
	
	// Return the string vector
	return strs;
}

int StringUtils::getCharacterCount(String str, char c) {
	int returnValue = 0;
	int index = -1;
 
	while (index > -1) {
		index = str.indexOf(c, index + 1);
		if(index > -1)
			returnValue+=1;
	}
 
	return returnValue;
}