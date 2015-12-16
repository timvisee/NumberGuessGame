/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#ifndef NUMBERGUESSGAME_CONNECTIONMANAGER_H
#define NUMBERGUESSGAME_CONNECTIONMANAGER_H

#include <stdint.h>

/**
 * Connection manager class.
 */
class ConnectionManager {
private:
    /**
     * Multiplayer flag.
     */
    static bool multiplayer;

    /**
     * Master flag.
     * Whether this device is the master on the multiplayer network.
     */
    static bool master;

    /**
     * Whether the device is currently waiting for a connection.
     */
    static bool connecting;

    /**
     * Connected flag.
     */
    static bool connected;

    /**
     * Get the game number of the last game.
     */
    static uint8_t gameNumber;

    /**
     * The input answer of the other device.
     */
    static uint8_t otherInputAnswer;

    /**
     * The input answer duration of the other device.
     */
    static long otherInputDuration;

    static bool receivedResult;
    static bool gameResultWin;
    static uint8_t resultAnswerSelf;
    static uint8_t resultAnswerOther;

public:
    /**
     * Check whether multiplayer is enabled for this device.
     *
     * @return True if multiplayer, false otherwise.
     */
    static bool isMultiplayer();

    /**
     * Set whether the device is in multiplayer mode.
     *
     * @param multiplayer True if in multiplayer, false otherwise.
     */
    static void setMultipayer(bool multiplayer);

    /**
     * Check whether the this device is the master in the multiplayer network.
     *
     * @param True if master, false otherwise.
     */
    static bool isMaster();

    /**
     * Set whether this device is the master in the multiplayer network.
     *
     * @param master True if master, false if not.
     */
    static void setMaster(bool master);

    /**
     * Whether the device is currently waiting to connect.
     *
     * @return True if connecting, false otherwise.
     */
    static bool isConnecting();

    /**
     * Set whether the device is currently waiting for a connection.
     *
     * @param connecting True if connecting, false if not.
     */
    static void setConnecting(bool connecting);

    /**
     * Check whether the device is connected to another device in the multiplayer network.
     *
     * @return True if connected, false if not.
     */
    static bool isConnected();

    /**
     * Set whether this device is connected or not.
     *
     * @param connected True if connected, false otherwise.
     */
    static void setConnected(bool connected);

    static uint8_t getGameNumber();

    static bool hasGameNumber();

    static void setGameNumber(uint8_t gameNumber);

    static void resetGameNumber();

    static uint8_t getOtherInputAnswer();

    static bool hasOtherInputAnswer();

    static void setOtherInputAnswer(uint8_t otherInputAnswer);

    static void resetOtherInputAnswer();

    static long getOtherInputDuration();

    static bool hasOtherInputDuration();

    static void setOtherInputDuration(long otherInputDuration);

    static void resetOtherInputDuration();



    static bool hasReceivedResult();

    static bool hasWonGame();

    static uint8_t getResultAnswerSelf();

    static uint8_t getResultAnswerOther();

    static void setResult(bool won, uint8_t answerSelf, uint8_t answerOther);

    static void clearResult();
};

#endif //NUMBERGUESSGAME_CONNECTIONMANAGER_H
