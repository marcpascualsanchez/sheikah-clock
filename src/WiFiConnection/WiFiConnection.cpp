#include "WiFiConnection.h"

string WiFiSSID = "MIWIFI_2G_ZzGA";
string WiFiPassword = "pascualsanchez937525520";
string cityName = "premia%20de%20mar";
const string baseURL = "http://api.openweathermap.org/data/2.5/weather";
const string appID = "fdcc7faa093ed6c4ff18ab74330ed00b";
AsyncWebServer server(80);

// TODO: do form and send by query params
const char access_point_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .dht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
  </style>
</head>
<body>
  <h2>Sheikah clock</h2>
  <p>
    <span class="dht-labels">Fill the form to configurate the clock. This data will only be used by the clock to display the weather & temperature.</span>
  </p>
  <form action="/config">
    <label for="ssid">WiFi name</label><br>
    <input type="text" id="ssid" name="ssid" value="%WiFiSSID%"><br><br>
    <label for="pass">WiFi password</label><br>
    <input type="password" id="pass" name="pass" value="%WiFiPassword%"><br><br>
    <label for="city">City name</label><br>
    <input type="text" id="city" name="city" value="%cityName%"><br><br>
    <input type="submit" value="Save">
  </form>
</body>
</html>)rawliteral";

String processor(const String& var){
  if(var == "WiFiSSID"){
    return String(WiFiSSID.c_str());
  }
  if(var == "WiFiPassword"){
    return String(WiFiPassword.c_str());
  }
  if(var == "cityName"){
    return String(cityName.c_str());
  }
  return String();
}

void WiFiConnection::connectToWiFiRouter()
{
    WiFi.mode(WIFI_OFF); //Prevents reconnection issue (taking too long to connect)
    delay(1000);
    WiFi.mode(WIFI_STA); //This line hides the viewing of ESP as wifi hotspot

    WiFi.begin(); //Connect to your WiFi router
    Serial.println("");

    Serial.print("Connecting");
    // Wait for connection
    int connectionRetries = 0;
    while (WiFi.status() != WL_CONNECTED || connectionRetries <= maxConnectionRetries)
    {
        delay(500);
        Serial.print(".");
        connectionRetries++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("");
        Serial.print("Connected to ");
        Serial.println(WiFiSSID.c_str());
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        isWiFiConnected = true;
    } else {
        Serial.print("Could not connect to ");
        Serial.println(WiFiSSID.c_str());
        isWiFiConnected = false;
        WiFiConnection::createAccessPoint();
    }
}

string replaceCharWithString(string text, string target, string replacement)
{
    int pos;

    while ((pos = text.find(target)) != std::string::npos)
        text.replace(pos, target.length(), replacement);
    return text;
}

string removeSpecialCharacters(string text)
{
    for (int i = 0; i < text.size(); i++)
    {
        if ((text[i] < 'A' || text[i] > 'Z') && (text[i] < 'a' || text[i] > 'z') && text[i] != ' ')
        {
            text.erase(i, 1);
            i--;
        }
    }
    return text;
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

void savePersistentCityName(string newCityName)
{
    EEPROM.begin(FLASH_RESERVED_SIZE);
    string formattedCityName = replaceCharWithString(removeSpecialCharacters(newCityName), " ", "%20");
    EEPROM.put(0, formattedCityName);
    EEPROM.end();
}

void savePersistentConfig(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final){
    savePersistentCityName(request->getParam("city")->value().c_str());
    WiFiSSID = request->getParam("ssid")->value().c_str();
    WiFiPassword = request->getParam("pass")->value().c_str();
    // WiFiConnection::connectToWiFiRouter();
}

void WiFiConnection::createAccessPoint()
{
    Serial.print("Setting AP (Access Point)…");
    WiFi.softAP(ACCESS_POINT_SSID.c_str());
    Serial.println("Server will be up in IP address:");
    Serial.println(WiFi.softAPIP());
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", access_point_html, processor);
    });
    server.on("/config", HTTP_POST, [](AsyncWebServerRequest *request){
        request->send(200, "Successfully configured and connected");
        server.end();
    }, savePersistentConfig);
    server.begin();
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

    http.begin(targetURL.c_str());     // Specify request destination
    http.GET();                        // Send the request
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
    // The API returns different icons depending on day/night time,
    // last char refers to this so we remove it
    const char *iconChar = weather["icon"];
    string icon(iconChar);
    string parsedIcon = icon.substr(0, icon.size() - 1);
    setWeather(parsedIcon);
    Serial.println("Current weather is: ");
    Serial.println(parsedIcon.c_str());
    JsonObject main = payloadJSON["main"];
    float temperature = main["temp"];
    setTemperature(temperature);
    http.end();
}
