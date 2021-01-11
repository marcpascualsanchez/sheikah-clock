#include <Arduino.h>
#include "WiFiConnection/WiFiConnection.h"

using namespace std;

WiFiConnection connection;

void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("Starting...");
  connection.setup();
}

void loop()
{
  connection.makeAPIRequest();
  float temp = connection.getTemperature();
  string icon = connection.getWeather();
  Serial.println("Temperature: ");
  Serial.println(temp);
  Serial.println("Icon: ");
  Serial.println(icon.c_str());
  delay(30000);
}
