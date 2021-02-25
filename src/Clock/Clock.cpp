#include "Clock.h"

void Clock::setup()
{
    pinMode(CONFIG_BUTTON, INPUT);
    pinMode(ADD_BUTTON, INPUT);
    pinMode(MINUS_BUTTON, INPUT);
    Wire.begin();
    DS3231_init(0);
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
    if (configButtonState == HIGH && configButtonState != lastConfigButtonState)
    {
        if (configState == INACTIVE)
        {
            configuredMinute = t.min;
            configState = MINUTE;
        }
        else if (configState == MINUTE)
        {
            configuredHour = t.hour;
            configState = HOUR;
        }
        else if (configState == HOUR)
        {
            // Set configured hour to clock
            t.hour = configuredHour;
            t.min = configuredMinute;
            t.sec = 0;
            setTime(t);
            configState = INACTIVE;
        }
    }
    lastConfigButtonState = configButtonState;
}

void Clock::setCurrentMinute(int addition) {
    configuredMinute += addition;
    if (configuredMinute > 59) {
        configuredMinute = 0;
    } else if (configuredMinute < 0) {
        configuredMinute = 59;
    }
}

void Clock::setCurrentHour(int addition) {
    configuredHour += addition;
    if (configuredHour > 23) {
        configuredHour = 0;
    } else if (configuredHour < 0) {
        configuredHour = 23;
    }
}

void Clock::checkAddMinusButtons()
{
    minusButtonState = digitalRead(MINUS_BUTTON);
    addButtonState = digitalRead(ADD_BUTTON);
    if (minusButtonState == HIGH  && minusButtonState != lastMinusButtonState) {
        if (configState == MINUTE)
        {
            setCurrentMinute(-1);
        }
        else if(configState == HOUR)
        {
            // Set configure hour mode
            setCurrentHour(-1);
        }
    }
    lastMinusButtonState = minusButtonState;
    if (addButtonState == HIGH && addButtonState != lastAddButtonState) {
        if (configState == MINUTE)
        {
            setCurrentMinute(1);
        }
        else if(configState == HOUR)
        {
            // Set configure hour mode
            setCurrentHour(1);
        }
    }
    lastAddButtonState = addButtonState;
}

void Clock::checkButtons()
{
    checkConfigButton();
    checkAddMinusButtons();
}

void Clock::log() {
    DS3231_get(&t);
    Serial.print("hour");
    Serial.print(t.hour);
    Serial.print("\n");
    Serial.print("min");
    Serial.print(t.min);
    Serial.print("\n");
    Serial.print("sec");
    Serial.print(t.sec);
    Serial.print("\n");
}
