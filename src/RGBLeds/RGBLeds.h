#ifndef RGBLED_h
#define RGBLED_h

#include <FastLED.h>
#include <array>
#include "../WiFiConnection/WiFiConnection.h"

#define RGBLED_PIN 12
#define NUM_LEDS 19
#define LED_TYPE WS2812
#define MIN_BRIGHTNESS 8
#define MAX_BRIGHTNESS 64

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
    void displayLeds();
    void setWeather(string weather);
    void setColor();
    void resetColor();
    string currentWeather = CLEAR_SKY;
    int tickCount = 0;
    int hue = 0;
    int divisor = 30;
    int activeColor[3] = {64, 127, 197}; // dark blue
    // int activeColor[3] = {90,184,244}; // light blue
    int inactiveColor[3] = {190, 126, 27}; // orange
    // int inactiveColor[3] = {235,197,25}; // yellow
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