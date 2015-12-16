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
uint8_t ConnectionManager::gameNumber = 0;

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

uint8_t ConnectionManager::getGameNumber() {
    return ConnectionManager::gameNumber;
}

bool ConnectionManager::hasGameNumber() {
    return getGameNumber() > 0;
}

void ConnectionManager::setGameNumber(uint8_t gameNumber) {
    ConnectionManager::gameNumber = gameNumber;
}

void ConnectionManager::resetGameNumber() {
    ConnectionManager::setGameNumber(0);
}
