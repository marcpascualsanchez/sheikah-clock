#include <Arduino.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3

// The amount of time (in milliseconds) between tests
#define TEST_DELAY   1000

TM1637Display display(CLK, DIO);

int seconds = 666;

void setup()
{
  display.setBrightness(5); // From 0 to up to 7
}

void loop()
{
  display.showNumberDecEx(seconds, 0b01000000, true); // second param as 0b01000000 for 00:00 format
  seconds++;
  delay(TEST_DELAY);
}