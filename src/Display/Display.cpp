#include "Display.h"

TM1637Display display(CLK, DIO);

// Create degree Celsius symbol:
const uint8_t celsius[] = {
  SEG_A | SEG_B | SEG_F | SEG_G,  // Circle
  SEG_A | SEG_D | SEG_E | SEG_F   // C
};

void Display::setup()
{
  display.setBrightness(3); // From 0 to up to 7
}

void Display::clear()
{
  display.clear();
}

void Display::displayOnlyMinutes(int minutes)
{
  display.showNumberDec(minutes, false, 2, 2); // display two digits from position 0
}

void Display::displayOnlyHours(int hours)
{
  display.showNumberDec(hours, false, 2, 0); // display two digits from position 0
}

void Display::displayNumber(int number)
{
  display.showNumberDecEx(number, 0b01000000, true); // mode to set the : brighten
}

void Display::displayTemperature(int temperature)
{
  display.showNumberDec(temperature, false, 2, 0);
  display.setSegments(celsius, 2, 2);
}

void Display::setBrightness(uint8_t brightnessLevel)
{
  display.setBrightness(brightnessLevel); // From 0 to up to 7
}