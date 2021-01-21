#include "Clock.h"

void Clock::setup()
{
    pinMode(CONFIG_BUTTON, INPUT);
    pinMode(ADD_BUTTON, INPUT);
    pinMode(MINUS_BUTTON, INPUT);
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

void Clock::setTime(ts time)
{
    DS3231_set(time);
}

ts Clock::getTime()
{
    DS3231_get(&t);
    return t;
}

int Clock::getFormattedTime()
{
    DS3231_get(&t);
    int totalHour = (t.hour * 100) + t.min;
    return totalHour;
}

void Clock::checkConfigButton()
{
    configButtonState = digitalRead(CONFIG_BUTTON);
    if (configButtonState == HIGH)
    {
        if (configState == INACTIVE)
        {
            configState = MINUTE;
        }
        else if (configState == HOUR)
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
            configState = INACTIVE;
        }
    }
}

void Clock::checkAddMinusButtons()
{
    minusButtonState = digitalRead(MINUS_BUTTON);
    addButtonState = digitalRead(ADD_BUTTON);
    if (minusButtonState == HIGH) {
        if (configState == MINUTE)
        {
            currentMinute--;
        }
        else if(configState == HOUR)
        {
            // Set configure hour mode
            currentHour--;
        }
    }
    if (addButtonState == HIGH) {
        if (configState == MINUTE)
        {
            currentMinute--;
        }
        else if(configState == HOUR)
        {
            // Set configure hour mode
            currentHour--;
        }
    }
}

void Clock::checkButtons()
{
    checkConfigButton();
    checkAddMinusButtons();
}
