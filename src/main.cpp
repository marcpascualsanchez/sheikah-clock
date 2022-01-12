#include <Arduino.h>
#include "WiFiConnection/WiFiConnection.h"
#include "Clock/Clock.h"
#include "Display/Display.h"
#include "RGBLeds/RGBLeds.h"

bool isAPIRequestDone = false;
bool isTemperatureShowed = false;
bool isTimeShowed = true;
uint8_t lastMinute;
ts currentTime;
uint8_t tickCount = 0;

WiFiConnection connectionController;
Clock clockController;
Display displayController;
RGBLeds rgbLedsController;
EConfigState lastConfigState;

void getAPILoop();
void display(ts time);

void setup()
{
  Serial.begin(9600);
  delay(1000);
  Serial.println("Setting up modules...");
  clockController.setup();
  displayController.setup();
  currentTime = clockController.getTime();
  displayController.displayNumber(clockController.getFormattedTime(currentTime));
  rgbLedsController.setup();
  connectionController.setup();
  Serial.println("Modules ready");
}

void loop()
{
  tickCount += 1;
  if (tickCount == 0)
  {
    currentTime = clockController.getTime();
    lastMinute = currentTime.min;
    isTimeShowed = false;
  }

  if (currentTime.min % 5 == 0)
  {
    if (!isAPIRequestDone)
    {
      getAPILoop();
    }
  }
  else
  {
    isAPIRequestDone = false;
  }

  if (connectionController.isForceApiRequest) {
    getAPILoop();
    connectionController.isForceApiRequest = false;
  }

  clockController.checkButtons();
  // Only display new sec if has changed
  display(currentTime);
  rgbLedsController.displayLeds(false);
  lastConfigState = clockController.configState;
}

void getAPILoop()
{
  if (!connectionController.isWiFiConnected)
  {
    return;
  }
  connectionController.makeAPIRequest();
  string weather = connectionController.getWeather();
  rgbLedsController.setWeather(weather);
  rgbLedsController.displayLeds(true);
  isAPIRequestDone = true;
}

void display(ts time)
{
  // STATUS: configuring active
  if (clockController.configState != INACTIVE)
  {
    if (clockController.configState != lastConfigState)
    {
      displayController.clear();
    }
    // TODO: set brightness high and low every x time when configState is active -> make user understand its configuring
    if (clockController.configState == MINUTE)
    {
      displayController.displayOnlyMinutes(clockController.configuredMinute);
    }
    else if (clockController.configState == HOUR)
    {
      displayController.displayOnlyHours(clockController.configuredHour);
    }
    // pampallugues
    if (time.sec % 2 == 0)
    {
      displayController.setBrightness(1);
    }
    else
    {
      displayController.setBrightness(2);
    }
  }
  else
  {
    if (time.sec != 0 && (time.sec % 30 == 0 || time.sec % 31 == 0 || time.sec % 32 == 0))
    {
      if (!isTemperatureShowed)
      {
        displayController.displayTemperature(connectionController.getTemperatureInt());
        isTemperatureShowed = true;
        isTimeShowed = false;
      }
    }
    else if (!isTimeShowed || lastMinute != currentTime.min)
    {
      displayController.displayNumber(clockController.getFormattedTime(currentTime)); // real time
      isTemperatureShowed = false;
      isTimeShowed = true;
    }
  }
  // clockController.log();
}
