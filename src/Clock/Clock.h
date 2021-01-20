#ifndef CLOCK_H
#define CLOCK_H

#include "ds3231.h"
#include <Wire.h>

#define CONFIG_BUTTON 14
#define ADD_BUTTON 15
#define MINUS_BUTTON 16

struct ts t;
enum configState {
    INACTIVE,
    MINUTE,
    HOUR
};

class Clock
{
    public:
        configState configState = INACTIVE;
        int configButtonState;
        int addButtonState;
        int minusButtonState;
        int currentMinute = 0;
        int currentHour = 0;
        void setupClock();
        void setTime(ts time);
        void checkButtons();
        int getHour();
};

#endif