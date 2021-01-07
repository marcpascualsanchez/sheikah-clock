#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  delay(1000); // Let the module self-initialize
}

void loop() {
  Serial.println("Hello there!");
  delay(1000);
}
