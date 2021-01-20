#ifndef DISPLAY_H
#define DISPLAY_H

#include <TM1637Display.h>

#define CLK 5
#define DIO 4

TM1637Display display(CLK, DIO);

class Display
{
    public:
        void setupDisplay();
        void displayNumber(int number);
};

#endif