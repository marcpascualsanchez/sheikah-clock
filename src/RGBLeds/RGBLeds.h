#ifndef RGBLED_h
#define RGBLED_h

#include <FastLED.h>
#include <array>
#include "../WiFiConnection/WiFiConnection.h"

#define COLOR_ORDER GRB
#define RGBLED_PIN 12
#define NUM_LEDS 19
#define LED_TYPE WS2812
#define MIN_BRIGHTNESS 32
#define MAX_BRIGHTNESS 128

// enum weather led ranges
const int CLEAR_SKY_LENGTH = 0;
const int FEW_CLOUDS_LENGTH = 4;
const int SCATTERED_CLOUDS_LENGTH = 7;
const int BROKEN_CLOUDS_LENGTH = 7;
const int MIST_LENGTH = 10;
const int SHOWER_RAIN_LENGTH = 3;
const int RAIN_LENGTH = 6;
const int THUNDERSTORM_LENGTH = 8;
const int SNOW_LENGTH = 10;

class RGBLeds
{
public:
    void setup();
    void displayLeds(boolean isChangeColor);
    void setWeather(string weather);
    void setColor();
    void resetColor();
    float getBreathBrightness();
    string currentWeather = RAIN;
    int breathStep = 1;
    unsigned int tickCounter = 0;
    // !!! WARNING: RGB is not the right order -> GRB
    // uint8_t activeColor[3] = {54, 14, 100}; // dark blue
    // uint8_t inactiveColor[3] = {85, 176, 0}; // orange
    uint8_t activeColor[3] = {14, 54, 100}; // dark blue
    uint8_t inactiveColor[3] = {176, 85, 0}; // orange
    int CLEAR_SKY_RANGE[CLEAR_SKY_LENGTH] = {};                                    // clear sky
    int FEW_CLOUDS_RANGE[FEW_CLOUDS_LENGTH] = {9, 8, 7, 3};                        // few clouds
    int SCATTERED_CLOUDS_RANGE[SCATTERED_CLOUDS_LENGTH] = {9, 8, 7, 6, 5, 4, 3};   // scattered clouds
    int BROKEN_CLOUDS_RANGE[BROKEN_CLOUDS_LENGTH] = {9, 8, 7, 6, 5, 4, 3};         // broken clouds
    int MIST_RANGE[MIST_LENGTH] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};                  // mist
    int SHOWER_RAIN_RANGE[SHOWER_RAIN_LENGTH] = {9, 10, 11};                       // shower rain
    int RAIN_RANGE[RAIN_LENGTH] = {9, 10, 11, 14, 15, 16};                         // rain
    int THUNDERSTORM_RANGE[THUNDERSTORM_LENGTH] = {9, 10, 11, 14, 15, 16, 17, 18}; // thunderstorm
    int SNOW_RANGE[SNOW_LENGTH] = {9, 10, 11, 12, 13, 14, 15, 16, 17, 18};         // snow
};

#endif