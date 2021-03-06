#ifndef CLOCK_H
#define CLOCK_H

#include "ds3231.h"
#include <Wire.h>

#define CONFIG_BUTTON 14
#define ADD_BUTTON 13
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
        /** Config button */
        int lastConfigButtonState;
        int configButtonState;
        /** Add button */
        int lastAddButtonState;
        int addButtonState;
        /** Minus button */
        int lastMinusButtonState;
        int minusButtonState;
        int configuredMinute = 0;
        int configuredHour = 0;
        ts getTime();
        void setup();
        void setTime(ts time);
        void checkButtons();
        void checkConfigButton();
        void checkAddMinusButtons();
        int getFormattedTime(ts time);
        void setCurrentMinute(int addition);
        void setCurrentHour(int addition);
        void log();
};

#endif