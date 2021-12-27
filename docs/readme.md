# Sheikah Clock
## Abstract
Arduino based clock + weather display, with rgb leds. Retrieves data from [openweathermap](https://openweathermap.org/) over HTTP using an ESP WiFi module.

## Details
There are [9 different main weathers](https://openweathermap.org/weather-conditions). Each one is represented by an icon, which code is received by the [openweathermap](https://openweathermap.org/) API.

In the clock, each icon is represented by the blue-lighted weather emblem. There are 7 positions, following the [sheikah plate design](blob:https://web.telegram.org/e5807c23-0650-42d6-b40b-7d963ef8d7bd). Each of the points represent one position. The position map to the [9 different weathers](https://openweathermap.org/weather-conditions) are represented in the plain-schema in `./docs` (no Sheikah map points is mapped to (01)clear sky).

## Configure the clock
The device has three buttons. One to either start and end the time configuration (blue), and the other two to add and substract minutes and hours. To accept, press again the configuration button (blue).

### Technical details
#### LED strip
From 0 to 20, leds that will turn blue for each weather. Only one cut will be needed, from the SNOW weather (last led is 15) to RAIN2.

WEATHER | LED light id*
--- | ---
CLEAR |                []
MIST |                 [0, 1, 2]
CLOUDS (1) |           [3]
CLOUDS (2&3) |         [4, 5, 6, 7, 8]
RAIN (1) |             [9, 10, 11, 12, 13, 18]
RAIN (3) |             [13, 14, 15, 16]
RAIN (2) |             [17]
SNOW |                 [19, 20]

*(by order from the power source until the end of the strip)