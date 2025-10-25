#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

// Define the pins for the NRF24L01 transceiver
#define CE_PIN 9
#define CNS_PIN 10

// Create an RF24 object
RF24 radio(CE_PIN, CNS_PIN);

// Define the address for the transceiver
const byte address[6] = "00001";

// Servo object to control the servo motor
Servo myServo;

// Define pins for motor ESCs and servo
const int escThrottlePin = 3;
const int escYawPin = 5;
const int escPitchPin = 6;
const int escRollPin = 9;
const int servoPin = 11;

// Variables to store received data
int throttle = 1500;
int yaw = 1500;
int pitch = 1500;
int roll = 1500;
bool servo_toggled = false;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
 
  // Initialize the RF24 radio
  radio.begin();
 
  // Set the address for reading data
  radio.openReadingPipe(0, address);
 
  // Set the radio to receive mode
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();
 
  // Attach the servo to the pin
  myServo.attach(servoPin);
 
  // Initialize the ESCs
  pinMode(escThrottlePin, OUTPUT);
  pinMode(escYawPin, OUTPUT);
  pinMode(escPitchPin, OUTPUT);
  pinMode(escRollPin, OUTPUT);
}

void loop() {
  // Check if there is data available to be read
  if (radio.available()) {
    // Buffer to store the received data
    char receivedData[32] = "";
   
    // Read the data into the buffer
    radio.read(&receivedData, sizeof(receivedData));
   
    // Print the received data for debugging
    Serial.println(receivedData);
   
    // Parse the received data
    parseData(receivedData);
   
    // Control the ESCs and servo based on the received data
    controlMotorsAndServo();
  }
}

// Function to parse the received data
void parseData(char* data) {
  // Split the received string into components
  char* token = strtok(data, ",");
 
  if (token != NULL) throttle = atoi(token);
  token = strtok(NULL, ",");
  if (token != NULL) yaw = atoi(token);
  token = strtok(NULL, ",");
  if (token != NULL) pitch = atoi(token);
  token = strtok(NULL, ",");
  token = strtok(NULL, ",");
  if (token != NULL) roll = atoi(token);
  token = strtok(NULL, ",");
  if (token != NULL) servo_toggled = atoi(token);
}

// Function to control the ESCs and the servo
void controlMotorsAndServo() {
  // Send the throttle, yaw, pitch, and roll values to the ESCs
  analogWrite(escThrottlePin, map(throttle, 1000, 2000, 0, 255));
  analogWrite(escYawPin, map(yaw, 1000, 2000, 0, 255));
  analogWrite(escPitchPin, map(pitch, 1000, 2000, 0, 255));
  analogWrite(escRollPin, map(roll, 1000, 2000, 0, 255));
 
  // Toggle the servo if the command was received
  if (servo_toggled) {
    myServo.write(90);  // Move servo to 90 degrees
  } else {
    myServo.write(0);   // Move servo back to 0 degrees
  }
}