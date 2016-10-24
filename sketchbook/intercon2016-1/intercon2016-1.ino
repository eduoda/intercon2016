/** 
 * Demo 1: witty + celular +  wifimanager
 */

//#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

#define BLYNK_AUTH "********************************"

#define LDR    A0
#define LED    15
#define BUTTON  4

SimpleTimer timer;

int foo;

BLYNK_CONNECTED() {
  Blynk.syncAll();
}

BLYNK_WRITE(V0){
  foo = param.asInt();
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
  Serial.println("Connectado!");

  Blynk.config(BLYNK_AUTH);
  
  pinMode(LDR, INPUT);
  timer.setInterval(500, doSomething);
}

void doSomething(){
  Serial.println(foo);
  Blynk.virtualWrite(1, millis()/1000);
  Blynk.virtualWrite(2, analogRead(LDR));
}

void loop() {
  Blynk.run();
  timer.run();
}

