#ifndef INTERNET_H
#define INTERNET_H

#include <WiFi.h>

char ssid[50] = "Awstyn";
char password[50] = "password";

#define RETRY_AFTER 5000


uint32_t lastWiFiConnectionTry = 0;
bool internetConnected = false;


void internetConnect() {
  if(millis() - lastWiFiConnectionTry < RETRY_AFTER)
    return;
  Serial.print("[WiFi] Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  lastWiFiConnectionTry = millis();
}


void printInternetInfo() {
  Serial.println("[WiFi] Connected");
  Serial.print("Open browser and enter: http://");
  Serial.println(WiFi.localIP());
}


void internetLoop() {
  if(!internetConnected)
    internetConnect();
  if(WiFi.status() != WL_CONNECTED && internetConnected) {
    Serial.println("[WiFi] Disconnected");
    internetConnected = false;
  }
  else if(!internetConnected && WiFi.status() == WL_CONNECTED) {
    internetConnected = true;
    printInternetInfo();
  }
}


#endif // INTERNET_H