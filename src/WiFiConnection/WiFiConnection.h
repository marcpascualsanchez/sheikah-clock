#ifndef WIFI_CONNECTION_H
#define WIFI_CONNECTION_H
#define WEBSERVER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <EEPROM.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

using string = std::string;

// wifi connection
const string API_BASE_URL = "http://api.openweathermap.org/data/2.5/weather";
const string API_APP_ID = "fdcc7faa093ed6c4ff18ab74330ed00b";
const int maxConnectionRetries = 20;
// access point
const string ACCESS_POINT_SSID = "sheikah-clock";
// eeprom
const int FLASH_RESERVED_SIZE = 512;
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
        static bool isWiFiConnected;
        static bool isForceApiRequest;
        float currentTemperature = 0;
        static void connectToWiFiRouter();
        static void createAccessPoint();
        static String htmlProcessor(const String& var);
        void makeAPIRequest();
        string getWeather();
        void setWeather(string newWeather);
        float getTemperature();
        int getTemperatureInt();
        void setTemperature(float newTemperature);
};

#endif