/**
 * Baseado em https://github.com/H-LK/ESP8266-SSID-Text-Broadcast
 */
#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <SimpleTimer.h>

extern "C" {
  #include "user_interface.h"
}

#define QTD 10
#define MAXLEN 32
String text[QTD] = {
// .......... .......... .......... Max de 32 caracteres
  "O abestado, vai na talk do Oda",
  "Quem nao for eh mulher do padre",
  "IoT sem BS com o Oda, cola la!",
  "Conhece ESP8266? O Oda te conta",
  "Ja esta sabendo da fala do Oda?",
  "Pera, flood com ESP8266?!",
  "OMG! vai rola talk do Oda!",
  "Vem conhecer ESP8266 com o Oda",
  "Quer IoT? Pergunte-me como.",
  "IoT interessa? Assiste o Oda!"
};

SimpleTimer timer;

// Beacon Packet buffer
uint8_t packet[128] = { 0x80, 0x00, 0x00, 0x00,
                /*4*/   0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                /*10*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                /*16*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                /*22*/  0xc0, 0x6c,
                /*24*/  0x83, 0x51, 0xf7, 0x8f, 0x0f, 0x00, 0x00, 0x00,
                /*32*/  0x64, 0x00,
                /*34*/  0x01, 0x04,
                /* SSID */
                /*36*/  0x00
                };
uint8_t packet2[12] = { 0x01, 0x08, 0x82, 0x84,
                        0x8b, 0x96, 0x24, 0x30,
                        0x48, 0x6c, 0x03, 0x01,
                      };

void setup() {
  delay(500);

  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(1);

  Serial.begin(115200);
  
  pinMode(2, OUTPUT);
  timer.setInterval(2000, blinkled);
}

void blinkled(){
  digitalWrite(2, LOW);
  delay(50);
  digitalWrite(2, HIGH);
}

void loop() {
  timer.run();

  for(int idx=0; idx<QTD; idx++){
    packet[37] = text[idx].length() < MAXLEN ? text[idx].length() : MAXLEN;
    
    packet[50+packet[37]] = random(1,12);
    wifi_set_channel(packet[50+packet[37]]);

    for(int i=0;i<6;i++)
      packet[10+i] = packet[16+i] = random(256);

    for (int i = 0; i < packet[37]; i++){
      packet[38+i] = text[idx][i];
    }
    
    for (int i = 0; i < 12; i++)
      packet[38+packet[37]+i] = packet2[i];

    for(int i=0;i<3;i++)
      wifi_send_pkt_freedom(packet, 50+packet[37], 0);
      
    delay(1);
  }  
  delay(5);
}

