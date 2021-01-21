#ifndef DISPLAY_H
#define DISPLAY_H

#include <TM1637Display.h>

#define CLK 5
#define DIO 4

class Display
{
public:
    void setup();
    void displayNumber(int number);
};

#endif