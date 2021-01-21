#include "Display.h"

TM1637Display display(CLK, DIO);

void Display::setup()
{
  display.setBrightness(1); // From 0 to up to 7
}

void Display::displayNumber(int number)
{
  display.showNumberDecEx(number, 0b01000000, true); // mode to set the : brighten
}