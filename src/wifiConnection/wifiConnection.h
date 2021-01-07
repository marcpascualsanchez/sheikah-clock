#ifndef wifi_connection_h
#define wifi_connection_h

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
using std::string;

/* Set these to your desired credentials. */
const char *ssid = "MIWIFI_2G_ZzGA"; //ENTER YOUR WIFI SETTINGS
const char *password = "pascualsanchez937525520";
const std::string lat = "41.4926947";
const std::string lon = "2.3570073";
const std::string baseURL = "http://api.openweathermap.org/data/2.5/onecall";
const std::string appID = "fdcc7faa093ed6c4ff18ab74330ed00b";

enum weather
{
    SUNNY = 0,
    RAINY,
    SNOW,
}

class WifiConnection
{
private:
    weather currentWeather;
    int currentTemperature;
public:
    void setup();
    void makeAPIRequest();
    weather getWeather();
    int getTemperature();
};

#endif