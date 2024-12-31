#define ACTIVATE   LOW
#define DEACTIVATE HIGH


#include "internet.h"
#include "mqtt.h"
#include "my_server.h"



const uint8_t switchPins[16] = {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37};


bool switchStates[16] = {false};


void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("[Main] Setup start");

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }
  for (int i=0; i<16; i++) {
    pinMode(switchPins[i], OUTPUT);
    digitalWrite(switchPins[i], DEACTIVATE);
    switchStates[i] = false;
  }
  Serial.println("[Main] Setup complete");
}

void loop() {
  internetLoop();
  mqttLoop();
  serverLoop();
}
