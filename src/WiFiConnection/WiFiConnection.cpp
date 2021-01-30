#include "WiFiConnection.h"

/* Set these to your desired credentials. */
const char *WiFiSSID = "MIWIFI_2G_ZzGA"; //ENTER YOUR WIFI SETTINGS
const char *WiFiPassword = "pascualsanchez937525520";
const string cityName = "premia%20de%20mar";
const string baseURL = "http://api.openweathermap.org/data/2.5/weather";
const string appID = "fdcc7faa093ed6c4ff18ab74330ed00b";

void WiFiConnection::setup()
{
    WiFi.mode(WIFI_OFF); //Prevents reconnection issue (taking too long to connect)
    delay(1000);
    WiFi.mode(WIFI_STA); //This line hides the viewing of ESP as wifi hotspot

    WiFi.begin(WiFiSSID, WiFiPassword); //Connect to your WiFi router
    Serial.println("");

    Serial.print("Connecting");
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    //If connection successful show IP address in serial monitor
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(WiFiSSID);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP()); //IP address assigned to your ESP
}

string WiFiConnection::getWeather()
{
    return currentWeather;
}

void WiFiConnection::setWeather(string newWeather)
{
    currentWeather = newWeather;
}

float WiFiConnection::getTemperature()
{
    return currentTemperature;
}

int WiFiConnection::getTemperatureInt()
{
    return round(currentTemperature);
}

void WiFiConnection::setTemperature(float newTemperature)
{
    currentTemperature = newTemperature;
}

void WiFiConnection::makeAPIRequest()
{
    HTTPClient http;
    // Example URL:
    // https://api.openweathermap.org/data/2.5/onecall?&units=metric&lat=41.4926947&lon=2.3570073&exclude=minutely,hourly,alerts&appid=fdcc7faa093ed6c4ff18ab74330ed00b

    string queryString = "q=" + cityName;
    queryString += "&appid=" + appID;
    queryString += "&units=metric";
    string targetURL = baseURL + "?" + queryString;

    Serial.println(targetURL.c_str());

    http.begin(targetURL.c_str()); // Specify request destination
    http.GET();                    // Send the request
    String payload = http.getString(); // Get the response payload
    StaticJsonDocument<900> payloadJSON;
    DeserializationError error = deserializeJson(payloadJSON, payload.c_str());

    if (error)
    {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.f_str());
        return;
    }

    JsonObject weather = payloadJSON["weather"][0];
    const char* icon = weather["icon"];
    setWeather(icon);
    JsonObject main = payloadJSON["main"];
    float temperature = main["temp"];
    setTemperature(temperature);
    http.end();
}
