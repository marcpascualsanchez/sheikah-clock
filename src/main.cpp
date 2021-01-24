#include <Arduino.h>
#include "WiFiConnection/WiFiConnection.h"
#include "Clock/Clock.h"
#include "Display/Display.h"

bool isAPIRequestDone = false;
bool isTemperatureShowed = false;
WiFiConnection connectionController;
Clock clockController;
Display displayController;

void getAPILopp();
void display();

void setup()
{
  Serial.begin(9600);
  delay(1000);
  Serial.println("Setting up modules...");
  // connectionController.setup();
  clockController.setup();
  displayController.setup();
  Serial.println("Modules ready");
}

void loop()
{
  ts currentTime = clockController.getTime();

  if (currentTime.min % 5 == 0)
  {
    if (!isAPIRequestDone)
    {
      // getAPILoop();
      isAPIRequestDone = true;
    }
  }
  else
  {
    isAPIRequestDone = false;
  }

  clockController.checkButtons();
  display();
}

void getAPILoop()
{
  connectionController.makeAPIRequest();
  float temperature = connectionController.getTemperature();
  string icon = connectionController.getWeather();
  Serial.println("Temperature: ");
  Serial.println(temperature);
  Serial.println("Icon: ");
  Serial.println(icon.c_str());
}

void display()
{
  if (clockController.configState != INACTIVE)
  {
    // TODO: set brightness high and low every x time when configState is active -> make user understand its configuring
    if (clockController.configState == MINUTE) {
      displayController.displayNumber(clockController.getFormattedConfiguredMinute());
    } else if (clockController.configState == HOUR) {
      displayController.displayNumber(clockController.getFormattedConfiguredHour());
    }
  }
  else
  {
    // TODO: show temperature without using delay (blocks buttons)
    displayController.displayNumber(clockController.getFormattedTime());
  }
}