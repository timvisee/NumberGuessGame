#include "ConnectionManager.h"

// Initialize class members
bool ConnectionManager::compCon = false;
bool ConnectionManager::robotCon = false;

bool ConnectionManager::isComputerConnected() {
	return compCon;
}

void ConnectionManager::setComputerConnected(bool c) {
	compCon = c;
}

bool ConnectionManager::isRobotConnected() {
	return robotCon;
}

void ConnectionManager::setRobotConnected(bool c) {
	robotCon = c;
}