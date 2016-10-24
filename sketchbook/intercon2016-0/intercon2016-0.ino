/** 
 * Demo 0: witty + celular
 * Selecao manual de rede
 */

//#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>

#define SSID "GTFO"
#define PASSWORD "********"
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
  
  Blynk.begin(BLYNK_AUTH, SSID, PASSWORD);

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

