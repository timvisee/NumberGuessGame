/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#include "ConnectionManager.h"

bool ConnectionManager::multiplayer = true;
bool ConnectionManager::master = true;
bool ConnectionManager::connected = false;
