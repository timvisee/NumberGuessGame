/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#include "Core.h"
#include "MemoryManager.h"

Core::Core() : con(), connectTimerWait(2000, false) {
    // Set the started flag
    this->started = false;

    // Initialize the screen LED array
    LedManager::screenLeds = new Led[SCREEN_LED_COUNT];

    // Construct the screen LED instances
    for(int i = 0; i < SCREEN_LED_COUNT; i++)
        LedManager::screenLeds[i] = Led(SCREEN_LED_PINS[i], SCREEN_LED_ANALOG);

    // Set up the other LEDs
    LedManager::greenLed = Led(GREEN_LED_PIN, GREEN_LED_ANALOG);
    LedManager::redLed = Led(RED_LED_PIN, RED_LED_ANALOG);
    LedManager::statusLed = Led(Led::STATUS_LED_PIN, Led::STATUS_LED_ANALOG);

    // Initialize the button
    ButtonManager::button = Button(BUTTON_PIN);
}

void Core::setup() {
    // Initial startup delay
    delay(200);

    // Initialize the logger
    Log::init();

    // Enable the serial connection for multiplayer
    con.begin(SERIAL_MULTIPLAYER_BAUD);

    // Set the proper stream in the packet handler
    PacketHandler::setConnectionStream(con);

    // Randomize the random seed
    Random::randomize();

    // Set up the answer LED pins
    for(int i = 0; i < SCREEN_LED_COUNT; i++)
        LedManager::screenLeds[i].setupPin();

    // Set up all other LEDs
    LedManager::greenLed.setupPin();
    LedManager::redLed.setupPin();
    LedManager::statusLed.setupPin();

    // Set up the button pin
    ButtonManager::button.setupPin();

    // Show a startup animation
    playStartupAnimation();

    // Show a success message

    // The device has been started, update the flag
    this->started = true;

    // Connect to the other Arduino
    connect();
}

/**
 * Connect to a second Arduino, before starting a game.
 */
void Core::connect() {
    // Set up a timer to connect
    Timer connectTimer(2000, true);
    connectTimerWait.start();

    // Loop and ask for a connection request, until a connection has been made
    while(ConnectionManager::isMultiplayer() && !ConnectionManager::isConnected() || !connectTimerWait.isFinished()) {
        // Send a new connection request if one hasn't been send for half a second
        if(connectTimer.isFinished()) {
            // Set the connecting flag
            ConnectionManager::setConnecting(true);

            // Enable the green status LED
            LedManager::greenLed.setState(true);

            // Create a packet to send a connection request
            Packet packet = Packet(1, Protocol::PACKET_TYPE_CONNECTION_REQUEST);
            PacketHandler::sendPacket(packet);
            packet.destroy();

            // Restart the connect timer
            connectTimer.start(1000);

            LedManager::greenLed.setState(false);
        }

        // Pulse the green light
        if(!LedManager::screenLeds[1].isFading()) {
            uint8_t brightness = LedManager::screenLeds[1].getBrightness();

            // Fade the lights in or out
            if(brightness <= PULSE_BRIGHTNESS_LOW) {
                LedManager::screenLeds[1].fade(PULSE_BRIGHTNESS_HIGH, PULSE_DURATION);

                // Only fade red out if it is currently on
                if(brightness == Led::BRIGHTNESS_LOW)
                    LedManager::screenLeds[1].fade(PULSE_BRIGHTNESS_LOW, PULSE_DURATION);

            } else if(brightness >= PULSE_BRIGHTNESS_HIGH) {
                LedManager::screenLeds[1].fade(PULSE_BRIGHTNESS_LOW, PULSE_DURATION);
            }
        }

        // Pulse the green light
        if(!LedManager::screenLeds[2].isFading()) {
            uint8_t brightness = LedManager::screenLeds[2].getBrightness();

            // Fade the lights in or out
            if(brightness <= PULSE_BRIGHTNESS_LOW) {
                LedManager::screenLeds[2].fade(PULSE_BRIGHTNESS_HIGH, PULSE_DURATION);

                // Only fade red out if it is currently on
                if(brightness == Led::BRIGHTNESS_LOW)
                    LedManager::screenLeds[2].fade(LedManager::screenLeds[1].getToBrightness(), LedManager::screenLeds[1].getFadeTimeLeft());

            } else if(brightness >= PULSE_BRIGHTNESS_HIGH) {
                LedManager::screenLeds[2].fade(PULSE_BRIGHTNESS_LOW, PULSE_DURATION);
            }

        } else if(!ConnectionManager::isMultiplayer())
            LedManager::screenLeds[2].setState(false);

        // Handle button presses to switch between single- and multiplayer
        if(ButtonManager::button.isPressedOnce()) {
            // Switch between single and multiplayer
            ConnectionManager::setMultipayer(!ConnectionManager::isMultiplayer());

            // Reset the timer
            connectTimerWait.start();
        }

        // Update everything
        updateLogic();
    }

    // Set the connecting flag
    ConnectionManager::setConnecting(false);

    // Turn the status LED off
    LedManager::screenLeds[1].setState(false);
    LedManager::screenLeds[2].setState(false);

    // Wait a little before showing the device status
    smartDelay(500);

    // If multiplayer, show which device is the master
    if(ConnectionManager::isMultiplayer()) {
        // Turn on the status LEDs
        LedManager::screenLeds[0].setState(true);
        if(ConnectionManager::isMaster())
            LedManager::screenLeds[1].setState(true);

        // Wait a little
        smartDelay(500);

        // Turn off the status LEDs
        LedManager::screenLeds[0].setState(false);
        if(ConnectionManager::isMaster())
            LedManager::screenLeds[1].setState(false);
    }

    // Wait a second before starting the game
    smartDelay(START_DELAY);
}

void Core::gameLogic() {
    // Show the slide animation before showing the number
    playSlideAnimation();
    smartDelay(400);

    // Reset the game number
    gameNumber = 0;

    // Generate a random number if this is the master when playing multiplayer
    if(!ConnectionManager::isMultiplayer() || ConnectionManager::isMaster())
        gameNumber = generateNewGameNumber();

    // Send the number to the other client when playing multiplayer
    if(ConnectionManager::isMultiplayer() && ConnectionManager::isMaster()) {
        // Create a packet to send the game start in
        Packet connectPacket = Packet(1, Protocol::PACKET_TYPE_GAME_START);

        // Create an array with the game number, add it to the packet
        int *intArr = new int[1];
        intArr[0] = (int) gameNumber;
        connectPacket.setIntegers(intArr, 1);

        // Send the packet
        PacketHandler::sendPacket(connectPacket);

        // Destroy the packet afterwards
        connectPacket.destroy();
    }

    // Wait for a number to be received if this is the slave
    if(ConnectionManager::isMultiplayer() && !ConnectionManager::isMaster()) {
        // Wait for a number, and update in the meanwhile
        while(!ConnectionManager::hasGameNumber())
            updateLogic();

        // Get the number
        gameNumber = ConnectionManager::getGameNumber();
        ConnectionManager::resetGameNumber();
    }

    // Show the number as binary for the specified duration
    showNumber(gameNumber);
    smartDelay(ANSWER_VISIBLE_DURATION);
    showNumber(0);

    // Start a stopwatch to measure the time the user takes to input
//    Stopwatch inputStopwatch = Stopwatch(true);

    // Start the timer
    Timer timer(INPUT_TIMEOUT);
    timer.start();

    // Define a variable to store the number in the user has entered
    uint8_t userAnswer = 0;

    // Use a while loop to handle the button presses
    while(!timer.isFinished() || userAnswer <= 0) {
        // TODO: Remove this, or change it to use a different LED? (because the green and red don't support analog anymore)
        // Pulse the green light
        if(!LedManager::greenLed.isFading()) {
            // Fade the lights in or out
            if(LedManager::greenLed.getBrightness() <= PULSE_BRIGHTNESS_LOW) {
                LedManager::greenLed.fade(PULSE_BRIGHTNESS_HIGH, PULSE_DURATION);

                // Only fade red out if it is currently on
                if(LedManager::redLed.getBrightness() != Led::BRIGHTNESS_LOW)
                    LedManager::redLed.fade(PULSE_BRIGHTNESS_LOW, PULSE_DURATION);

            } else if(LedManager::greenLed.getBrightness() >= PULSE_BRIGHTNESS_HIGH) {
                LedManager::greenLed.fade(PULSE_BRIGHTNESS_LOW, PULSE_DURATION);
                LedManager::redLed.fade(PULSE_BRIGHTNESS_HIGH, PULSE_DURATION);
            }
        }

        // Update everything
        updateLogic();

        // Handle button presses
        if(ButtonManager::button.isPressedOnce()) {
            // Increase the answer
            userAnswer++;

            // Reset the answer
            timer.start();

            // Show some feedback, a button is pressed
            for(int i = 0; i < SCREEN_LED_COUNT; i++)
                LedManager::screenLeds[i].fade(FEEDBACK_BRIGHTNESS_HIGH, FEEDBACK_VISIBLE_DURATION);
            smartDelay(FEEDBACK_VISIBLE_DURATION);
            for(int i = 0; i < SCREEN_LED_COUNT; i++)
                LedManager::screenLeds[i].fade(FEEDBACK_BRIGHTNESS_LOW, FEEDBACK_VISIBLE_DURATION);
        }
    }

    // Measure the input duration
//    long userInputDuration = inputStopwatch.getTime();

    // Stop the timer
    timer.stop();

    // Turn off the pulsing LEDs
    LedManager::greenLed.setState(false);
    LedManager::redLed.setState(false);

    // Clear the current results
    ConnectionManager::clearResult();

    // Do some extra stuff if playing multiplayer
    if(ConnectionManager::isMultiplayer()) {
        // As a slave, send the result to the master.
        if(!ConnectionManager::isMaster()) {
            // Create the packet
            Packet connectPacket = Packet(1, Protocol::PACKET_TYPE_GAME_ANSWER);

            // Create an array with the answer, add it to the packet
            int *intArr = new int[1];
            intArr[0] = (int) userAnswer;
            connectPacket.setIntegers(intArr, 1);

            // Create an array with input duration, add it to the packet
//            String *strArr = new String[1];
//            strArr[0] = String(userInputDuration);
//            connectPacket.setStrings(strArr, 1);

            // Send the packet
            PacketHandler::sendPacket(connectPacket);

            // Destroy the packet afterwards
            connectPacket.destroy();

            // Wait for the results to be send, update in the meanwhile
            while(!ConnectionManager::hasReceivedResult())
                updateLogic();

        } else {
            // As master, wait for the result to be received, update in the meanwhile
            while(!ConnectionManager::hasOtherInputAnswer())
                updateLogic();

            // Store the values, reset them afterwards
            uint8_t otherUserInputAnswer = ConnectionManager::getOtherInputAnswer();
//            long otherUserInputDuration = ConnectionManager::getOtherInputDuration();
            ConnectionManager::resetOtherInputAnswer();
            ConnectionManager::resetOtherInputDuration();

            // Determine which player wins
            bool masterWin = (userAnswer == gameNumber);
            bool slaveWin = (otherUserInputAnswer == gameNumber);

            // If both players are correct, choose the fastest
//            if(masterWin && slaveWin) {
//                masterWin = (userInputDuration >= otherUserInputDuration);
//                slaveWin = (userInputDuration < otherUserInputDuration);
//            }

            // Create the packet
            Packet connectPacket = Packet(1, Protocol::PACKET_TYPE_GAME_RESULTS);

            // Create an array with the answer, add it to the packet
            int *intArr = new int[2];
            intArr[0] = (int) userAnswer;
            intArr[1] = (int) otherUserInputAnswer;
            connectPacket.setIntegers(intArr, 2);

            // Create an array with the answer, add it to the packet
            bool *boolArr = new bool[2];
            intArr[0] = (bool) masterWin;
            intArr[1] = (bool) slaveWin;
            connectPacket.setBooleans(boolArr, 2);

            // Create an array with input duration, add it to the packet
//            String *strArr = new String[2];
//            strArr[0] = String(userInputDuration);
//            strArr[1] = String(otherUserInputDuration);
//            connectPacket.setStrings(strArr, 2);

            // Send the packet
            PacketHandler::sendPacket(connectPacket);

            // Destroy the packet afterwards
            connectPacket.destroy();

            // Store the answers for this device
            ConnectionManager::setResult(masterWin, userAnswer, otherUserInputAnswer);
        }
    }

    // Wait a second before showing the input
    smartDelay(500);

    // Show the result the user has entered
    showNumber(userAnswer);
    smartDelay(USER_INPUT_VISIBLE_DURATION);
    showNumber(0);

    // Wait a second before showing the input
    smartDelay(1000);

    // Determine whether the user has won
    bool hasWon = (userAnswer == gameNumber);
    if(ConnectionManager::isMultiplayer())
        hasWon = ConnectionManager::hasWonGame();

    // Show the result
    if(hasWon) {
        // Turn on the green LED if available
        LedManager::greenLed.setState(true);
        smartDelay(250);

        // Animate the screen
        for(uint8_t j = 0; j < 3; j++) {
            for(uint8_t i = 0; i < SCREEN_LED_COUNT; i++)
                LedManager::screenLeds[i].setState(true);
            smartDelay(250);
            for(uint8_t i = 0; i < SCREEN_LED_COUNT; i++)
                LedManager::screenLeds[i].setState(false);
            smartDelay(250);
        }

        // Turn off the green LED
        smartDelay(250);
        LedManager::greenLed.setState(false);

    } else {
        // Turn on the red LED if available
        LedManager::redLed.setState(true);
        smartDelay(250);

        // Animate the screen
        for(uint8_t i = 0; i < SCREEN_LED_COUNT; i++)
            LedManager::screenLeds[i].fade(80, 500);
        smartDelay(500);
        for(uint8_t i = 0; i < SCREEN_LED_COUNT; i++)
            LedManager::screenLeds[i].fade(0, 1000);
        smartDelay(1000);

        // Turn off the red LED
        smartDelay(250);
        LedManager::redLed.setState(false);
    }

    // Wait a little for the slave to catch up
    smartDelay(250);
}

/**
 * Update method, should be called often to update things like the animation controllers of the LEDs.
 */
void Core::updateLogic() {
    // Update the screen LEDs
    for(short i = 0; i < SCREEN_LED_COUNT; i++)
        LedManager::screenLeds[i].update();

    // Update the green and red LED
    LedManager::greenLed.update();
    LedManager::redLed.update();

    // Update the button state
    ButtonManager::button.update();

    // Update the memory manager
    MemoryManager::update();

    // Only update the following if the device is started
    if(!this->started)
        return;

    // Handle received data from the multiplayer connection
    // TODO: Only if multiplayer is enabled?
    while(con.available()) {
        // Enable the activity light
        LedManager::statusLed.setState(true);

        // Handle the new data
        while(con.available())
            PacketHandler::receive((char) con.read());

        // Disable the activity light
        LedManager::statusLed.setState(false);
    }
}

/**
 * A smart delay method.
 * This method is similar to Arduino's delay method, but it keeps calling the update() method while the delay method is executed instead of freezing the Arduino.
 *
 * @param delay The delay in milliseconds to wait.
 */
void Core::smartDelay(int delay) {
    // Create a timer, to track the passed time
    Timer timer(delay);

    // Start the timer
    timer.start();

    // Call the update method until the timer has passed the specified delay
    while(!timer.isFinished())
        updateLogic();
}

/**
 * Show the startup animation.
 */
void Core::playStartupAnimation() {
    // Show the slide animation
    playSeekAnimation();
}

/**
 * Show the slide animation.
 */
void Core::playSlideAnimation() {
    // Enable the LEDs
    for(int i = 0; i < SCREEN_LED_COUNT + 2; i++) {
        // Handle the LED
        if(i < SCREEN_LED_COUNT)
            LedManager::screenLeds[i].fade(Led::BRIGHTNESS_HIGH, 250);
        else if(i == SCREEN_LED_COUNT)
            LedManager::greenLed.fade(Led::BRIGHTNESS_HIGH, 250);
        else if(i == SCREEN_LED_COUNT + 1)
            LedManager::redLed.fade(Led::BRIGHTNESS_HIGH, 250);

        // Wait a little before handling the next LED
        smartDelay(75);
    }

    // Disable the LEDs
    for(int i = 0; i < SCREEN_LED_COUNT + 2; i++) {
        // Handle the LED
        if(i < SCREEN_LED_COUNT)
            LedManager::screenLeds[i].fade(Led::BRIGHTNESS_LOW, 250);
        else if(i == SCREEN_LED_COUNT)
            LedManager::greenLed.fade(Led::BRIGHTNESS_LOW, 250);
        else if(i == SCREEN_LED_COUNT + 1)
            LedManager::redLed.fade(Led::BRIGHTNESS_LOW, 250);

        // Wait a little before handling the next LED
        smartDelay(75);
    }
}

/**
 * Show the seek animation.
 */
void Core::playSeekAnimation() {
    // Show the slide animation
    playSlideAnimation();

    // Enable the LEDs
    for(int i = SCREEN_LED_COUNT + 1; i >= 0; i--) {
        // Handle the LED
        if(i < SCREEN_LED_COUNT)
            LedManager::screenLeds[i].fade(Led::BRIGHTNESS_HIGH, 250);
        else if(i == SCREEN_LED_COUNT)
            LedManager::greenLed.fade(Led::BRIGHTNESS_HIGH, 250);
        else if(i == SCREEN_LED_COUNT + 1)
            LedManager::redLed.fade(Led::BRIGHTNESS_HIGH, 250);

        // Wait a little before handling the next LED
        smartDelay(75);
    }

    // Disable the LEDs
    for(int i = SCREEN_LED_COUNT + 1; i >= 0; i--) {
        // Handle the LED
        if(i < SCREEN_LED_COUNT)
            LedManager::screenLeds[i].fade(Led::BRIGHTNESS_LOW, 250);
        else if(i == SCREEN_LED_COUNT)
            LedManager::greenLed.fade(Led::BRIGHTNESS_LOW, 250);
        else if(i == SCREEN_LED_COUNT + 1)
            LedManager::redLed.fade(Led::BRIGHTNESS_LOW, 250);

        // Wait a little before handling the next LED
        smartDelay(75);
    }
}

/**
 * Show a number, using the four LEDs.
 *
 * @param number The number to show the LEDs for.
 */
void Core::showNumber(uint8_t number) {
    for(byte i = 0; i < SCREEN_LED_COUNT; i++) {
        LedManager::screenLeds[i].setState((bool) (number & 1));
        number /= 2;
    }
}

/**
 * Generate a random number, that is suitable for the number of available LEDs.
 *
 * @return Random number.
 */
uint8_t Core::generateNewGameNumber() {
    return (uint8_t) Random::nextInt((int) (pow(2, SCREEN_LED_COUNT) - 1)) + 1;
}