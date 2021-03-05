#ifndef WIFI_CONNECTION_H
#define WIFI_CONNECTION_H

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

using string = std::string;

// enum weather
const string CLEAR_SKY = "01";        // clear sky
const string FEW_CLOUDS = "02";       // few clouds
const string SCATTERED_CLOUDS = "03"; // scattered clouds
const string BROKEN_CLOUDS = "04";    // broken clouds
const string MIST = "50";             // mist
const string SHOWER_RAIN = "09";      // shower rain
const string RAIN = "10";             // rain
const string THUNDERSTORM = "11";     // thunderstorm
const string SNOW = "13";             // snow

class WiFiConnection
{
    public:
        string currentWeather = CLEAR_SKY;
        float currentTemperature = 0;
        void setup();
        void makeAPIRequest();
        string getWeather();
        void setWeather(string newWeather);
        float getTemperature();
        int getTemperatureInt();
        void setTemperature(float newTemperature);
};

#endif