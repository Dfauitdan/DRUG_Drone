/*
This a test script to test connection over a 2.4Ghz transceiver
This code is desgined to be used on the drone and communicate through with the flight controller

*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
char receivedData[1];

int ledPin = 9;
bool ledState = false;

void setup() {
  pinMode(ledPin, OUTPUT);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    radio.read(&receivedData, sizeof(receivedData));
    if (receivedData[0] == 'R') {
      ledState = !ledState;
      digitalWrite(ledPin, ledState);
    }
  }
}
