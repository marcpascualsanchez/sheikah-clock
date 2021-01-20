#include "Clock.h"

void Clock::setupClock()
{
    pinMode(CONFIG_BUTTON, INPUT);
    pinMode(ADD_BUTTON, INPUT);
    pinMode(MINUS_BUTTON, INPUT);
    Wire.begin();
    DS3231_init(0);
    DS3231_set(t);
}

void Clock::setTime(ts time)
{
    DS3231_set(t);
}

int Clock::getHour()
{
    DS3231_get(&t);
    int totalHour = (t.hour * 100) + t.min;
    return totalHour;
}

void Clock::checkButtons()
{
    digitalRead(CONFIG_BUTTON);
    if (configButtonState == HIGH)
    {
        if (configState == INACTIVE)
        {
            configState = HOUR;
        }
        else if (configState == MINUTE)
        {
            // Set configured hour to clock
            ts configuredTime;
            configuredTime.hour = currentHour;
            configuredTime.min = currentMinute;
            configuredTime.sec = 0;
            setTime(configuredTime);
            configState = INACTIVE;
        }
        else
        {
            // Set configure hour mode
            configState = MINUTE;
        }
    }
}