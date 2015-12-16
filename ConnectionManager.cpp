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

bool ConnectionManager::isMultiplayer() {
    return ConnectionManager::multiplayer;
}

void ConnectionManager::setMultipayer(bool multiplayer) {
    ConnectionManager::multiplayer = multiplayer;
}

bool ConnectionManager::isMaster() {
    return ConnectionManager::master;
}

void ConnectionManager::setMaster(bool master) {
    ConnectionManager::master = master;
}

bool ConnectionManager::isConnected() {
    return ConnectionManager::connected;
}

void ConnectionManager::setConnected(bool connected) {
    ConnectionManager::connected = connected;
}
