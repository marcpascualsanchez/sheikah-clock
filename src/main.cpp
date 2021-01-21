#include <Arduino.h>
#include "WiFiConnection/WiFiConnection.h"
#include "Clock/Clock.h"
#include "Display/Display.h"

bool isAPIRequestDone = false;
WiFiConnection connectionController;
Clock clockController;
Display displayController;

void setup()
{
  Serial.begin(9600);
  delay(1000);
  Serial.println("Setting up modules...");
  connectionController.setup();
  clockController.setup();
  displayController.setup();
  Serial.println("Modules ready");
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
  Serial.println("Displaying.....");
  // TODO: why does the clock not advance in time?
  displayController.displayNumber(clockController.getFormattedTime());
}
