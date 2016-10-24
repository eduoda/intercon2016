/** 
 * Demo: wemos + rele + lampada
 */

#include <ESP8266WiFi.h>

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

#include <BlynkSimpleEsp8266.h>
#define BLYNK_AUTH "********************************"


BLYNK_CONNECTED() {
  Blynk.syncAll();
}

void setup() {
  Serial.begin(115200);

  WiFiManager wifiManager;
  //wifiManager.resetSettings();

  if (!wifiManager.autoConnect("timao eo","********")) {
    Serial.println("Timeout :P");
    ESP.reset();
    delay(1000);
  }
  Serial.println("Connected!");

  Blynk.config(BLYNK_AUTH);
}


void loop() {
  Blynk.run();
}

