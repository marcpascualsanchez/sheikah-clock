#include "ds3231.h"
#include <Wire.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3
TM1637Display display(CLK, DIO);

struct ts t;

void setupDisplay()
{
    display.setBrightness(5); // From 0 to up to 7
}

void setupClock()
{
    Wire.begin();
    DS3231_init(0);
    t.hour = 21;
    t.min = 15;
    t.sec = 0;
    t.mday = 25;
    t.mon = 10;
    t.year = 2020;
    DS3231_set(t);
}

void setup()
{
    Serial.begin(9600);
    setupDisplay();
    setupClock();
}

void loop()
{
    DS3231_get(&t);
    int totalHour = (t.hour * 100) + t.min;
    Serial.print("hour");
    Serial.print(t.hour);
    Serial.print("\n");
    Serial.print("min");
    Serial.print(t.min);
    Serial.print("\n");
    Serial.print("sec");
    Serial.print(t.sec);
    Serial.print("\n");
    display.showNumberDecEx(totalHour, 0b01000000, true); // second param as 0b01000000 for 00:00 format
    delay(500);
}
