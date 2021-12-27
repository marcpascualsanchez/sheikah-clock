#ifndef RGBLED_h
#define RGBLED_h

#include <FastLED.h>
#include <array>
#include "../WiFiConnection/WiFiConnection.h"

// !!! WARNING: RGB is not the right order -> GRB
#define COLOR_ORDER GRB
#define RGBLED_PIN 15
#define NUM_LEDS 25
#define LED_TYPE WS2812
#define MIN_BRIGHTNESS 32
#define MAX_BRIGHTNESS 128

// enum weather led ranges
const int CLEAR_SKY_LENGTH = 0;
const int FEW_CLOUDS_LENGTH = 1;
const int SCATTERED_CLOUDS_LENGTH = 6;
const int BROKEN_CLOUDS_LENGTH = 6;
const int MIST_LENGTH = 9;
const int SHOWER_RAIN_LENGTH = 11;
const int RAIN_LENGTH = 15;
const int THUNDERSTORM_LENGTH = 18;
const int SNOW_LENGTH = 15;

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
    // uint8_t activeColor[3] = {54, 14, 100}; // dark blue
    // uint8_t inactiveColor[3] = {85, 176, 0}; // orange
    uint8_t activeColor[3] = {14, 54, 150}; // dark blue
    uint8_t inactiveColor[3] = {220, 85, 0}; // orange
    int CLEAR_SKY_RANGE[CLEAR_SKY_LENGTH] = {};                                                                         // 01 clear sky
    int FEW_CLOUDS_RANGE[FEW_CLOUDS_LENGTH] = {3};                                                                      // 02 few clouds
    int SCATTERED_CLOUDS_RANGE[SCATTERED_CLOUDS_LENGTH] = {3, 4, 5, 6, 7, 8};                                           // 03 scattered clouds
    int BROKEN_CLOUDS_RANGE[BROKEN_CLOUDS_LENGTH] = {3, 4, 5, 6, 7, 8};                                                 // 04 broken clouds
    int MIST_RANGE[MIST_LENGTH] = {0, 1, 2, 3, 4, 5, 6, 7, 8};                                                          // 50 mist
    int SHOWER_RAIN_RANGE[SHOWER_RAIN_LENGTH] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 20};                                  // 09 shower rain
    int RAIN_RANGE[RAIN_LENGTH] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 20, 18, 19};                                // 10 rain
    int THUNDERSTORM_RANGE[THUNDERSTORM_LENGTH] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 20, 15, 16, 17, 18, 19};    // 11 thunderstorm
    int SNOW_RANGE[SNOW_LENGTH] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 20, 21, 22, 23, 24};                                // 13 snow
};

#endif