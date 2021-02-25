#include "RGBLeds.h"

struct CRGB leds[NUM_LEDS];

void RGBLeds::setup()
{
    LEDS.addLeds<LED_TYPE, RGBLED_PIN>(leds, NUM_LEDS);
    FastLED.setBrightness(MAX_BRIGHTNESS);
    FastLED.clear();
    resetColor();
}

void RGBLeds::displayLeds()
{
    tickCount++;
    if (tickCount >= 5)
    {
        float breath = (exp(sin(millis() / 5000.0 * PI)) - 0.36787944) * 108.0;
        breath = map(breath, 0, 255, MIN_BRIGHTNESS, MAX_BRIGHTNESS);
        FastLED.setBrightness(breath);
        resetColor();
        setColor();
        FastLED.show();
        tickCount = 0;
    }
}

void RGBLeds::setWeather(string weather)
{
    currentWeather = weather;
}


void RGBLeds::resetColor()
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i].setRGB(inactiveColor[0], inactiveColor[1], inactiveColor[2]);
    }
}

// apparently there can not be string switches
// https://stackoverflow.com/questions/650162/why-the-switch-statement-cannot-be-applied-on-strings
void RGBLeds::setColor()
{
    int *currentWeatherRange;
    int currentWeatherRangeLength;
    if (CLEAR_SKY.compare(currentWeather) == 0)
    {
        currentWeatherRange = CLEAR_SKY_RANGE;
        currentWeatherRangeLength = CLEAR_SKY_LENGTH;
    }

    if (FEW_CLOUDS.compare(currentWeather) == 0)
    {
        currentWeatherRange = FEW_CLOUDS_RANGE;
        currentWeatherRangeLength = FEW_CLOUDS_LENGTH;
    }

    if (SCATTERED_CLOUDS.compare(currentWeather) == 0)
    {
        currentWeatherRange = SCATTERED_CLOUDS_RANGE;
        currentWeatherRangeLength = SCATTERED_CLOUDS_LENGTH;
    }

    if (BROKEN_CLOUDS.compare(currentWeather) == 0)
    {
        currentWeatherRange = BROKEN_CLOUDS_RANGE;
        currentWeatherRangeLength = BROKEN_CLOUDS_LENGTH;
    }

    if (MIST.compare(currentWeather) == 0)
    {
        currentWeatherRange = MIST_RANGE;
        currentWeatherRangeLength = MIST_LENGTH;
    }

    if (SHOWER_RAIN.compare(currentWeather) == 0)
    {
        currentWeatherRange = SHOWER_RAIN_RANGE;
        currentWeatherRangeLength = SHOWER_RAIN_LENGTH;
    }

    if (RAIN.compare(currentWeather) == 0)
    {
        currentWeatherRange = RAIN_RANGE;
        currentWeatherRangeLength = RAIN_LENGTH;
    }

    if (THUNDERSTORM.compare(currentWeather) == 0)
    {
        currentWeatherRange = THUNDERSTORM_RANGE;
        currentWeatherRangeLength = THUNDERSTORM_LENGTH;
    }

    if (SNOW.compare(currentWeather) == 0)
    {
        currentWeatherRange = SNOW_RANGE;
        currentWeatherRangeLength = SNOW_LENGTH;
    }

    for (int i = 0; i < currentWeatherRangeLength; i++)
    {
        int ledIndex = currentWeatherRange[i];
        leds[ledIndex].setRGB(activeColor[0], activeColor[1], activeColor[2]);
    }
}