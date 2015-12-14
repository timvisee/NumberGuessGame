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

class StringUtils {
public:
    static std::vector<String> split(String s, char splitChar, bool smart);
	static int getCharacterCount(String s, char c);
};

#endif // NUMBERGUESSGAME_STRINGUTILS_H
