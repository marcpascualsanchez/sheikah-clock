#ifndef CLOCK_H
#define CLOCK_H

#include "ds3231.h"
#include <Wire.h>

#define CONFIG_BUTTON 14
#define ADD_BUTTON 15
#define MINUS_BUTTON 16

/** There are only three states, only one can be activated (configStates)
 * The sequence is always lineal: INACTIVE -> MINUTE -> HOUR
*/
enum EConfigState {
    INACTIVE,
    MINUTE,
    HOUR
};

class Clock
{
    public:
        struct ts t;
        EConfigState configState = INACTIVE;
        int configButtonState;
        int addButtonState;
        int minusButtonState;
        int currentMinute = 0;
        int currentHour = 0;
        ts getTime();
        void setup();
        void setTime(ts time);
        void checkButtons();
        void checkConfigButton();
        void checkAddMinusButtons();
        int getFormattedTime();
};

#endif