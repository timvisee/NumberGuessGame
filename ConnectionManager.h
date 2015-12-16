/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#ifndef NUMBERGUESSGAME_CONNECTIONMANAGER_H
#define NUMBERGUESSGAME_CONNECTIONMANAGER_H

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
     * Connected flag.
     */
    static bool connected;

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
};

#endif //NUMBERGUESSGAME_CONNECTIONMANAGER_H
