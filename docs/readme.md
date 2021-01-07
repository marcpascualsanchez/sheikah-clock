# Sheikah Clock
## Abstract
Arduino based clock + weather display, with rgb leds. Retrieves data from (openweathermap)[https://openweathermap.org/] over HTTP using an ESP WiFi module.

## Details
There are (9 different main weathers)[https://openweathermap.org/weather-conditions]. Each one is represented by an icon, which code is received by the (openweathermap)[https://openweathermap.org/] API.

In the clock, each icon is represented by the blue-lighted weather emblem. There are 7 positions, following the (sheikah plate design)[blob:https://web.telegram.org/e5807c23-0650-42d6-b40b-7d963ef8d7bd]. Each of the points represent one position. The position map to the (9 different weathers)[https://openweathermap.org/weather-conditions] are represented in the plain-schema in `./docs` (no Sheikah map points is mapped to (01)clear sky).