/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#include "Core.h"
#include "MemoryManager.h"

Core::Core() : con() {
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
//    Log::info("Init");
//    Log::debug("Dbg on");

    // Show a startup message
//    Log::info("Strt...");

    // Enable the serial connection for multiplayer
//    Log::debug("Strt mp con...");
    con.begin(SERIAL_MULTIPLAYER_BAUD);

    // Set the proper stream in the packet handler
    PacketHandler::setConnectionStream(con);

    // Randomize the random seed
//    Log::debug("Rndmzng...");
    Random::randomize();

    // Set up the answer LED pins
//    Log::debug("Stp LEDs...");
    for(int i = 0; i < SCREEN_LED_COUNT; i++)
        LedManager::screenLeds[i].setupPin();

    // Set up all other LEDs
    LedManager::greenLed.setupPin();
    LedManager::redLed.setupPin();
    LedManager::statusLed.setupPin();

    // Set up the button pin
//    Log::debug("Stp btn...");
    ButtonManager::button.setupPin();

    // Show a startup animation
//    Log::debug("Anim...");
    showStartupAnimation();

    // Wait a little before starting
//    Log::debug("Waiting...");
    smartDelay(START_DELAY);

    // Show a success message
//    Log::info("Strt");

    // Connect to the other Arduino
//    Log::info("Con...");
    connect();
}

void Core::loop() {
    // Generate a random number
    uint8_t num = generateNewGameNumber();

    // Show the number as binary for the specified duration
    showNumber(num);
    smartDelay(ANSWER_VISIBLE_DURATION);
    showNumber(0);

    // Start the timer
    Timer timer(INPUT_TIMEOUT);
    timer.start();

    // Define a variable to store the number in the user has entered
    uint8_t answer = 0;

    // Use a while loop to handle the button presses
    while(!timer.isFinished() || answer <= 0) {
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
        update();

        // Handle button presses
        if(ButtonManager::button.isPressedOnce()) {
            // Increase the answer
            answer++;

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

    // Stop the timer
    timer.stop();

    // Turn of the green LED
    LedManager::greenLed.setState(false);
    LedManager::redLed.setState(false);

    // Wait a second before showing the input
    smartDelay(500);

    // Show the result the user has entered
    showNumber(answer);
    smartDelay(USER_INPUT_VISIBLE_DURATION);

    // Verify the answer
    if(num == answer)
        LedManager::greenLed.setState(true);
    else
        LedManager::redLed.setState(true);

    // Wait before turning all LEDs off again
    smartDelay(1500);

    // Disable all LEDs
    showNumber(0);
    LedManager::greenLed.setState(false);
    LedManager::redLed.setState(false);

    // Show the slide animation before continuing to the next wave
    smartDelay(200);
    showSlideAnimation();
    smartDelay(400);
}

/**
 * Connect to a second Arduino, before starting a game.
 */
void Core::connect() {
    // Set up a timer to connect
    Timer connectTimer(0);
    connectTimer.start(0);

    // Loop and ask for a connection request, until a connection has been made
    while(ConnectionManager::isMultiplayer() && !ConnectionManager::isConnected()) {
        // Send a new connection request if one hasn't been send for half a second
        if(connectTimer.isFinished()) {
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

        // Update everything
        update();
    }
}

/**
 * Update method, should be called often to update things like the animation controllers of the LEDs.
 */
void Core::update() {
    // Update the screen LEDs
    for(short i = 0; i < SCREEN_LED_COUNT; i++)
        LedManager::screenLeds[i].update();

    // Update the green and red LED
    LedManager::greenLed.update();
    LedManager::redLed.update();

    // Update the button state
    ButtonManager::button.update();

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

    // Update the memory manager
    MemoryManager::update();
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
        update();
}

/**
 * Show the startup animation.
 */
void Core::showStartupAnimation() {
    // Show the slide animation
    showSeekAnimation();
}

/**
 * Show the slide animation.
 */
void Core::showSlideAnimation() {
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
void Core::showSeekAnimation() {
    // Show the slide animation
    showSlideAnimation();

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
 * Show a number, using the four LEDs, with a custom brightness and fade duration.
 *
 * @param number The number to show the LEDs for.
 * @param brightness The target brightness.
 * @param duration The target duration in milliseconds.
 */
void Core::showNumber(uint8_t number, uint8_t brightness, int duration) {
    for(byte i = 0; i < SCREEN_LED_COUNT; i++) {
        // Turn the LED on or off, based on the number with the specified brightness and duration
        if(number & 1)
            LedManager::screenLeds[i].fade(brightness, duration);
        else
            LedManager::screenLeds[i].setState(false);

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

void Core::memoryReport() {
    Log::info("M> " + String(freeMemory()) + " B");
}
