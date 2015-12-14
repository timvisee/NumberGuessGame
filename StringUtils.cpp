/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#include "StringUtils.h"

std::vector<String> StringUtils::split(String s, char splitChar, bool smart) {
	int splitCount = StringUtils::getCharacterCount(s, splitChar);
	std::vector<String> strs;

	int index = -1;
	int index2;
 
	for(int i = 0; i < splitCount - 1; i++) {
		index = s.indexOf(splitChar, index + 1);
		index2 = s.indexOf(splitChar, index + 1);
		
		// Ensure there isn't a backslash before the split char
		if(s.charAt(index - 1) == '\\')
			continue;

		if(index2 < 0)
			index2 = s.length() - 1;

		strs.push_back(s.substring(index, index2));
	}
	
	// Return the string vector
	return strs;
}

int StringUtils::getCharacterCount(String s, char c) {
	int returnValue = 0;
	int index = -1;
 
	while (index > -1) {
		index = s.indexOf(c, index + 1);
		if(index > -1)
			returnValue+=1;
	}
 
	return returnValue;
}