#ifndef DISPLAY_H
#define DISPLAY_H

#include <TM1637Display.h>

#define CLK 2
#define DIO 0

class Display
{
public:
    void setup();
    void clear();
    void displayNumber(int number);
    void displayTemperature(int temperature);
    void setBrightness(uint8_t brightnessLevel);
    void displayOnlyMinutes(int minutes);
    void displayOnlyHours(int hours);
};

#endif