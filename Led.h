/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#ifndef NUMBERGUESSGAME_LED_H
#define NUMBERGUESSGAME_LED_H

#include <Arduino.h>

/**
 * Led class.
 */
class Led {
public:
    /**
     * Constant for the lowest brightness value of the LED.
     */
    static const int BRIGHTNESS_LOW;

    /**
     * Constant for the highest brightness value of the LED.
     */
    static const int BRIGHTNESS_HIGH;

    /**
     * Status LED pin.
     * This is the status LED on the Arduino board itself, usually connected to port 13.
     */
    static const uint8_t STATUS_LED_PIN;

    /**
     * Status LED mode.
     * Define whether the status LED is in analog or digital mode.
     */
    static const bool STATUS_LED_ANALOG;

private:
    /**
     * The pin used for the LED.
     */
    uint8_t pin;

    /**
     * The current boolean state of the LED.
     */
    bool state;

    /**
     * True if the analog mode of this LED is enabled, false if not.
     */
    bool analogMode;

    /**
     * The default fade duration for the LED.
     */
    int fadeDuration;

    /**
     * Animation field: From brightness.
     */
    int fromBrightness;

    /**
     * Animation field: To brightness.
     */
    int toBrightness;

    /**
     * Animation field: From time.
     */
    long fromTime;

    /**
     * Animation field: To time.
     */
    long toTime;

    /**
     * The current brightness of the LED, this field is animated.
     */
    int brightness;

public:
    /**
     * Constructor.
     */
    Led();

    /**
     * Constructor.
     *
     * @param pin The pin of the LED.
     * @param analogMode True if the analog mode of this LES is enabled, false if not.
     */
    Led(uint8_t pin, bool analogMode);

    /**
     * Set up the pin of the LED.
     */
    void setupPin();

    /**
     * Get the pin of the LED.
     */
    uint8_t getPin();

    /**
     * Check whether this LED is in analog mode.
     *
     * @return True if in analog mode, false otherwise.
     */
    bool inAnalogMode();

    /**
     * Set whether the LED is in analog mode.
     *
     * @param analogMode True if the led is in analog mode, false otherwise.
     */
    void setAnalogMode(bool analogMode);

    /**
     * Get the fade duration in milliseconds.
     *
     * @return Fade duration.
     */
    int getFadeDuration();

    /**
     * Set the fade duration in milliseconds.
     *
     * @param fadeDuration Fade duration.
     */
    void setFadeDuration(int fadeDuration);

    /**
     * Update the current LED state.
     * This method should be called often, to update the LED animator.
     */
    void update();

    /**
     * Get the current boolean state of the LED. This value isn't animated.
     *
     * @return LED state.
     */
    bool getState();

    /**
     * Set the current boolean state of the LED.
     * This will automatically animate analog LEDs with the specified duration.
     *
     * @param state LED state.
     */
    void setState(bool state);

    /**
     * Fade the LED if it's in analog mode to the specified brightness with the default delay.
     *
     * @param brightness The brightness.
     */
    void fade(int brightness);

    /**
     * Fade the LED if it's in analog mode to the specified brightness with the specified delay.
     *
     * @param brightness The brightness.
     * @param duration The fade duration.
     */
    void fade(int brightness, int duration);

    /**
     * Check whether the LED is currently fading or animating.
     *
     * @return True if fading, false if not.
     */
    bool isFading();

    /**
     * Get the current brightness level of the LED.
     * This value is animated.
     */
    int getBrightness();

    /**
     * Set the current brightness level of the LED.
     * This value might be overwritten if the LED is currently being animated.
     */
    void setBrightness(int brightness);
};

#endif //NUMBERGUESSGAME_LED_H
