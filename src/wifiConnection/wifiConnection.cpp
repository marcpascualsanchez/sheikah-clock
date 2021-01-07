#include "wifiConnection.h"

class WiFiConnection
{
    void setup()
    {
        WiFi.mode(WIFI_OFF); //Prevents reconnection issue (taking too long to connect)
        delay(1000);
        WiFi.mode(WIFI_STA); //This line hides the viewing of ESP as wifi hotspot

        WiFi.begin(ssid, password); //Connect to your WiFi router
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
        Serial.println(ssid);
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP()); //IP address assigned to your ESP
    }

    weather makeAPIRequest()
    {
        HTTPClient http; //Declare object of class HTTPClient

        // https://api.openweathermap.org/data/2.5/onecall?lat={lat}&lon={lon}&exclude={part}&appid={API key}
        // https://api.openweathermap.org/data/2.5/onecall?lat=41.4926947&lon=2.3570073&exclude=minutely,hourly,alerts&appid=fdcc7faa093ed6c4ff18ab74330ed00b

        string queryString = "lat=" + lat;
        queryString += "&lon=" + lon;
        queryString += "&appid=" + appID;
        queryString += "&exclude=current,minutely,hourly,alerts";
        string targetURL = baseURL + "?" + queryString;

        http.begin(targetURL.c_str()); //Specify request destination

        int httpCode = http.GET();         //Send the request
        String payload = http.getString(); //Get the response payload

        Serial.println(targetURL.c_str()); //Print HTTP return code
        Serial.println(httpCode);          //Print HTTP return code
        Serial.println(payload);           //Print request response payload

        http.end(); //Close connection

        delay(60000); //GET Data at every minute
    }
};
