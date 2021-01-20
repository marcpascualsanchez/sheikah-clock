#ifndef WIFI_CONNECTION_H
#define WIFI_CONNECTION_H

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

using string = std::string;

// enum weather
const string CLEAR_SKY = "01d";        // clear sky
const string FEW_CLOUDS = "02d";       // few clouds
const string SCATTERED_CLOUDS = "03d"; // scattered clouds
const string BROKEN_CLOUDS = "04d";    // broken clouds
const string SHOWER_RAIN = "09d";      // shower rain
const string RAIN = "10d";             // rain
const string THUNDERSTORM = "11d";     // thunderstorm
const string SNOW = "13d";             // snow
const string MIST = "50d";             // mist


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
        void setTemperature(float newTemperature);
};

#endif