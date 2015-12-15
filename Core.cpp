/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#include "Core.h"

Core::Core() :
        greenLed(GREEN_LED_PIN, GREEN_LED_ANALOG),
        redLed(RED_LED_PIN, RED_LED_ANALOG),
        statusLed(Led::STATUS_LED_PIN, Led::STATUS_LED_ANALOG),
        button(BUTTON_PIN),
        con() {

    // Initialize the screen LED array
    this->screenLeds = new Led[SCREEN_LED_COUNT];

    // Construct the screen LED instances
    for(int i = 0; i < SCREEN_LED_COUNT; i++)
        screenLeds[i] = Led(SCREEN_LED_PINS[i], SCREEN_LED_ANALOG);
}

void Core::setup() {
    // Initial startup delay
    delay(200);

    // Enable all serial connections
    Serial.begin(SERIAL_USB_BAUD);
    con.begin(SERIAL_MULTIPLAYER_BAUD);

    // Set the proper stream in the packet handler
    PacketHandler::setConnectionStream(con);

    // Randomize the random seed
    Random::randomize();

    // Set up the answer LED pins
    for(int i = 0; i < SCREEN_LED_COUNT; i++)
        screenLeds[i].setupPin();

    // Set up all other LEDs
    greenLed.setupPin();
    redLed.setupPin();
    statusLed.setupPin();

    // Set up the button pin
    button.setupPin();

    // Show a startup animation
    showStartupAnimation();

    // Wait a little before starting
    smartDelay(START_DELAY);

    // Connect to the other Arduino
    connect();
}

void Core::loop() {
    // Generate a random number
    int num = (int) generateRandomNumber();

    // Show the number as binary for the specified duration
    showNumber(num);
    smartDelay(ANSWER_VISIBLE_DURATION);
    showNumber(0);

    // Start the timer
    Timer timer(INPUT_TIMEOUT);
    timer.start();

    // Define a variable to store the number in the user has entered
    int answer = 0;

    // Use a while loop to handle the button presses
    while(!timer.isFinished() || answer <= 0) {
        // Pulse the green light
        if(!greenLed.isFading()) {
            // Fade the lights in or out
            if(greenLed.getBrightness() <= PULSE_BRIGHTNESS_LOW) {
                greenLed.fade(PULSE_BRIGHTNESS_HIGH, PULSE_DURATION);

                // Only fade red out if it is currently on
                if(redLed.getBrightness() != Led::BRIGHTNESS_LOW)
                    redLed.fade(PULSE_BRIGHTNESS_LOW, PULSE_DURATION);

            } else if(greenLed.getBrightness() >= PULSE_BRIGHTNESS_HIGH) {
                greenLed.fade(PULSE_BRIGHTNESS_LOW, PULSE_DURATION);
                redLed.fade(PULSE_BRIGHTNESS_HIGH, PULSE_DURATION);
            }
        }

        // Update everything
        update();

        // Handle button presses
        if(button.isPressedOnce()) {
            // Increase the answer
            answer++;

            // Reset the answer
            timer.start();

            // Show some feedback, a button is pressed
            for(int i = 0; i < SCREEN_LED_COUNT; i++)
                screenLeds[i].fade(FEEDBACK_BRIGHTNESS_HIGH, FEEDBACK_VISIBLE_DURATION);
            smartDelay(FEEDBACK_VISIBLE_DURATION);
            for(int i = 0; i < SCREEN_LED_COUNT; i++)
                screenLeds[i].fade(FEEDBACK_BRIGHTNESS_LOW, FEEDBACK_VISIBLE_DURATION);
        }
    }

    // Stop the timer
    timer.stop();

    // Turn of the green LED
    greenLed.setState(false);
    redLed.setState(false);

    // Wait a second before showing the input
    smartDelay(500);

    // Show the result the user has entered
    showNumber(answer);
    smartDelay(USER_INPUT_VISIBLE_DURATION);

    // Verify the answer
    if(num == answer)
        greenLed.setState(true);
    else
        redLed.setState(true);

    // Wait before turning all LEDs off again
    smartDelay(1500);

    // Disable all LEDs
    showNumber(0);
    greenLed.setState(false);
    redLed.setState(false);

    // Show the slide animation before continuing to the next wave
    smartDelay(200);
    showSlideAnimation();
    smartDelay(400);
}

/**
 * Connect to a second Arduino, before starting a game.
 */
void Core::connect() {
//    // Set up a timer to connect
//    Timer connectTimer(0);
//    connectTimer.start(0);
//
//    // Loop and ask for a connection request, until a connection has been made
//    while(true) {
//        // Send a new connection request if one hasn't been send for half a second
//        if(connectTimer.isFinished()) {
//            // Enable the green status LED
//            greenLed.setState(true);
//
//            // Send a connection request
//            con.print("C");
//
//            // Restart the connect timer
//            connectTimer.start(1000);
//
//            smartDelay(100);
//
//            greenLed.setState(false);
//        }
//
//        // Update everything
//        update();
//    }
}

Timer testPacketTimer(3000, true);

/**
 * Update method, should be called often to update things like the animation controllers of the LEDs.
 */
void Core::update() {
    // Update the screen LEDs
    for(short i = 0; i < SCREEN_LED_COUNT; i++)
        screenLeds[i].update();

    // Update the green and red LED
    greenLed.update();
    redLed.update();

    // Update the button state
    button.update();

    // Handle received data from the multiplayer connection
    // TODO: Only if multiplayer is enabled?
    while(con.available()) {
        // Enable the activity light
        statusLed.setState(true);

        // Handle the new data
        while(con.available())
            PacketHandler::receive((char) con.read());

        // Disable the activity light
        statusLed.setState(false);
    }

    // DEBUG: Send a test packet
    if(testPacketTimer.isFinished()) {
        // Create a test packet
        Packet testPacket(2, 3);

        // Create a vector with a string and add it to the packet
        std::vector<String> strs;
        strs.push_back("Str!");
        testPacket.setStrings(strs);

        // Send the actual packet
        PacketHandler::sendPacket(testPacket);

        // Reset the timer
        testPacketTimer.start();
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
        update();
}

/**
 * Show the startup animation.
 */
void Core::showStartupAnimation() {
    // Show the slide animation
    showSlideAnimation();
}

/**
 * Show the slide animation.
 */
void Core::showSlideAnimation() {
    // Enable the LEDs
    for(int i = 0; i < SCREEN_LED_COUNT + 2; i++) {
        // Handle the LED
        if(i < SCREEN_LED_COUNT)
            screenLeds[i].fade(Led::BRIGHTNESS_HIGH, 250);
        else if(i == SCREEN_LED_COUNT)
            greenLed.fade(Led::BRIGHTNESS_HIGH, 250);
        else if(i == SCREEN_LED_COUNT + 1)
            redLed.fade(Led::BRIGHTNESS_HIGH, 250);

        // Wait a little before handling the next LED
        smartDelay(75);
    }

    // Disable the LEDs
    for(int i = 0; i < SCREEN_LED_COUNT + 2; i++) {
        // Handle the LED
        if(i < SCREEN_LED_COUNT)
            screenLeds[i].fade(Led::BRIGHTNESS_LOW, 250);
        else if(i == SCREEN_LED_COUNT)
            greenLed.fade(Led::BRIGHTNESS_LOW, 250);
        else if(i == SCREEN_LED_COUNT + 1)
            redLed.fade(Led::BRIGHTNESS_LOW, 250);

        // Wait a little before handling the next LED
        smartDelay(75);
    }
}

/**
 * Show a number, using the four LEDs.
 *
 * @param number The number to show the LEDs for.
 */
void Core::showNumber(int number) {
    for(byte i = 0; i < SCREEN_LED_COUNT; i++) {
        screenLeds[i].setState((bool) (number & 1));
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
void Core::showNumber(int number, int brightness, int duration) {
    for(byte i = 0; i < SCREEN_LED_COUNT; i++) {
        // Turn the LED on or off, based on the number with the specified brightness and duration
        if(number & 1)
            screenLeds[i].fade(brightness, duration);
        else
            screenLeds[i].setState(false);

        number /= 2;
    }
}

/**
 * Generate a random number, that is suitable for the number of available LEDs.
 *
 * @return Random number.
 */
long Core::generateRandomNumber() {
    return Random::nextInt((int) (pow(2, SCREEN_LED_COUNT) - 1)) + 1;
}