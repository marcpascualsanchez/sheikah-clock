#include <Arduino.h>
#include "WiFiConnection/WiFiConnection.h"
#include "Clock/Clock.h"
#include "Display/Display.h"

bool isAPIRequestDone = false;
bool isTemperatureShowed = false;
WiFiConnection connectionController;
Clock clockController;
Display displayController;
EConfigState lastConfigState;

void getAPILoop();
void display(ts time);

void setup()
{
  Serial.begin(9600);
  delay(1000);
  Serial.println("Setting up modules...");
  connectionController.setup();
  clockController.setup();
  displayController.setup();
  getAPILoop();
  Serial.println("Modules ready");
}

void loop()
{
  ts currentTime = clockController.getTime();

  if (currentTime.min % 5 == 0)
  {
    if (!isAPIRequestDone)
    {
      getAPILoop();
      isAPIRequestDone = true;
    }
  }
  else
  {
    isAPIRequestDone = false;
  }

  clockController.checkButtons();
  display(currentTime);
  lastConfigState = clockController.configState;
}

void getAPILoop()
{
  connectionController.makeAPIRequest();
  // float temperature = connectionController.getTemperature();
  // Serial.println("Temperature: ");
  // Serial.println(temperature);
  // TODO: translate weather icon into rgb colors
  string icon = connectionController.getWeather();
  Serial.println("Icon: ");
  Serial.println(icon.c_str());
}

void display(ts time)
{
  if (clockController.configState != INACTIVE)
  {
    if (clockController.configState != lastConfigState) {
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
      }
    }
    else
    {
      displayController.displayNumber(clockController.getFormattedTime()); // real time
      isTemperatureShowed = false;
    }
    // clockController.log();
  }
}