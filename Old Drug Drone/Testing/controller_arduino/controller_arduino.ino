#include <SPI.h>
/*
This code is a test to determine the usability and range of a 2.4Ghz transceiver
This code is designed to be connected to computer through serial port and used in conjuction with python script 
found in parent directory
*/

#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
char dataToSend[1];

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  if (Serial.available() > 0) {
    char receivedChar = Serial.read();
    if (receivedChar == 'R') {
      dataToSend[0] = 'R';
      radio.write(&dataToSend, sizeof(dataToSend));
    }
  }
}
