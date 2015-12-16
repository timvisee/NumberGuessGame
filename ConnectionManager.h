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

    /**
     * True if the result has been received.
     */
    static bool receivedResult;

    /**
     * If this device won.
     */
    static bool gameResultWin;

    /**
     * The answer of this device.
     */
    static uint8_t resultAnswerSelf;

    /**
     * The answer of the other device.
     */
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

    /**
     * Get the current game number.
     *
     * @return Game number.
     */
    static uint8_t getGameNumber();

    /**
     * Has a game number been set.
     *
     * @return True if set, false otherwise.
     */
    static bool hasGameNumber();

    /**
     * Set the current game number.
     *
     * @param gameNumber Game number.
     */
    static void setGameNumber(uint8_t gameNumber);

    /**
     * Reset the current game number.
     */
    static void resetGameNumber();

    /**
     * Get the answer the other device has entered, if available.
     *
     * @return Other's input.
     */
    static uint8_t getOtherInputAnswer();

    /**
     * Check whether the input of the other device is available.
     *
     * @return True if available, false otherwise.
     */
    static bool hasOtherInputAnswer();

    /**
     * Set the input that the other device has entered.
     *
     * @param otherInputAnswer Other's input.
     */
    static void setOtherInputAnswer(uint8_t otherInputAnswer);

    /**
     * Reset the input that the other device has entered.
     */
    static void resetOtherInputAnswer();

    /**
     * Get the duration it took for the other device to input.
     *
     * @return Input duration of other device.
     */
    static long getOtherInputDuration();

    /**
     * Check whether the input duration of the other device has been set.
     *
     * @return True if set, false otherwise.
     */
    static bool hasOtherInputDuration();

    /**
     * Set the input duration of the other device.
     *
     * @param otherInputDuration Duration.
     */
    static void setOtherInputDuration(long otherInputDuration);

    /**
     * Reset the input duration of the other device.
     */
    static void resetOtherInputDuration();

    /**
     * Check whether results have been received.
     *
     * @return True if received, false otherwise.
     */
    static bool hasReceivedResult();

    /**
     * Check whether this device won the game.
     *
     * @return True if the game has been won, false otherwise.
     */
    static bool hasWonGame();

    /**
     * Get the result of this device, processed by the master.
     *
     * @return Result of self.
     */
    static uint8_t getResultAnswerSelf();

    /**
     * Get the result of the other device, processed by the master.
     *
     * @return Result of master.
     */
    static uint8_t getResultAnswerOther();

    /**
     * Set the current results.
     *
     * @param won True if won, false if not.
     * @param answerSelf The answer this device has given.
     * @param answerOther The answer the other device has given.
     */
    static void setResult(bool won, uint8_t answerSelf, uint8_t answerOther);

    /**
     * Clear the current results.
     */
    static void clearResult();
};

#endif //NUMBERGUESSGAME_CONNECTIONMANAGER_H
