#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ACCESS_POINT_SSID = "ESP8266-Access-Point";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

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
  <h2>ESP8266 Server from %ACCESS_POINT_SSID%</h2>
  <p>
    <span class="dht-labels">Hey, remember you're cute</span>
  </p>
</body>
</html>)rawliteral";

String processor(const String& var){
  if(var == "ACCESS_POINT_SSID"){
    return String(ACCESS_POINT_SSID);
  }
  return String();
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(9600);
  
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ACCESS_POINT_SSID);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Print ESP8266 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", access_point_html, processor);
  });
  // Start server
  server.begin();
}
 
void loop(){  
  
}
