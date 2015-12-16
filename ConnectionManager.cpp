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
bool ConnectionManager::connecting = false;
bool ConnectionManager::connected = false;
uint8_t ConnectionManager::gameNumber = 0;
uint8_t ConnectionManager::otherInputAnswer = 0;
long ConnectionManager::otherInputDuration = 0;
bool ConnectionManager::receivedResult = false;
bool ConnectionManager::gameResultWin = false;
uint8_t ConnectionManager::resultAnswerSelf = 0;
uint8_t ConnectionManager::resultAnswerOther = 0;

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

bool ConnectionManager::isConnecting() {
    return ConnectionManager::connecting;
}

void ConnectionManager::setConnecting(bool connecting) {
    ConnectionManager::connecting = connecting;
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

uint8_t ConnectionManager::getOtherInputAnswer() {
    return ConnectionManager::otherInputAnswer;
}

bool ConnectionManager::hasOtherInputAnswer() {
    return getOtherInputAnswer() > 0;
}

void ConnectionManager::setOtherInputAnswer(uint8_t otherInputAnswer) {
    ConnectionManager::otherInputAnswer = otherInputAnswer;
}

void ConnectionManager::resetOtherInputAnswer() {
    ConnectionManager::setOtherInputAnswer(0);
}

long ConnectionManager::getOtherInputDuration() {
    return ConnectionManager::otherInputDuration;
}

bool ConnectionManager::hasOtherInputDuration() {
    return getOtherInputDuration() > 0;
}

void ConnectionManager::setOtherInputDuration(long otherInputDuration) {
    ConnectionManager::otherInputDuration = otherInputDuration;
}

void ConnectionManager::resetOtherInputDuration() {
    ConnectionManager::setOtherInputDuration(0);
}

bool ConnectionManager::hasReceivedResult() {
    return ConnectionManager::receivedResult;
}

bool ConnectionManager::hasWonGame() {
    return ConnectionManager::gameResultWin;
}

uint8_t ConnectionManager::getResultAnswerSelf() {
    return ConnectionManager::resultAnswerSelf;
}

uint8_t ConnectionManager::getResultAnswerOther() {
    return ConnectionManager::resultAnswerOther;
}

void ConnectionManager::setResult(bool won, uint8_t answerSelf, uint8_t answerOther) {
    ConnectionManager::receivedResult = true;
    ConnectionManager::gameResultWin = won;
    ConnectionManager::resultAnswerSelf = answerSelf;
    ConnectionManager::resultAnswerOther = answerOther;
}

void ConnectionManager::clearResult() {
    ConnectionManager::receivedResult = false;
    ConnectionManager::gameResultWin = false;
    ConnectionManager::resultAnswerSelf = 0;
    ConnectionManager::resultAnswerOther = 0;
}
