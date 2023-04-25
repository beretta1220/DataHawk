/*
  Using Arduino UNO R3
 
  
  GPS Position Logger
  gps-position-logger.ino
  Read GPS data from BN-220 or any serial GPS sensor
  Requires TinyGPS++ Library
  Save to SD or microSD card
 
  GPS
  VCC - 5V
  RX - 3
  TX - 4
  GND

  Sound Detector
  Envelope - A0
  VCC - 5V
  Gate - 2
  GND

  MicroSD
  VCC - 5V
  CS - 8
  DI - 11
  SCK - 13
  DO - 12
  CD - 9
  GND
  
*/


  /*********************************
   GPS POSITION LOGGER LAT/LONG/UTC
    *******************************/

// Include required libraries
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>

// GPS Connections
static const int RXPin = 4, TXPin = 3;
 
// GPS Baud rate (change if required)
static const uint32_t GPSBaud = 9600;
 
// SD Card Select pin
const int chipSelect = 8;
 
// Write LED
const int recLED = 7;
 
// String to hold GPS data
String gpstext;
 
// GPS write delay counter variables
// Change gpsttlcount as required
int gpscount = 0;
int gpsttlcount = 7; //
 
// TinyGPS++ object
TinyGPSPlus gps;
 
// SoftwareSerial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

  /*********************************
   SOUND DETECTOR
   *******************************/

const unsigned long soundLoggingInterval = 1000; // interval for sound logging (in milliseconds)
unsigned long lastSoundLogTime = 0; // initialize last sound logging time
   
const int soundPin = A0; // Sound sensor analog input pin
int soundValue = 0; // Sound sensor analog value
float dB = 0; // Decibel reading variable

// File to log sound data
File soundDataFile; // "why was commented out?"

// Define hardware connections
#define PIN_GATE_IN 2
#define IRQ_GATE_IN  0
#define PIN_LED_OUT 6 // 13 -> 6
#define PIN_ANALOG_IN A0

// soundISR()
// This function is installed as an interrupt service routine for the pin
// change interrupt.  When digital input 2 changes state, this routine
// is called.
// It queries the state of that pin, and sets the onboard LED to reflect that 
// pin's state.
void soundISR()
{
  int pin_val;

  pin_val = digitalRead(PIN_GATE_IN);
  digitalWrite(PIN_LED_OUT, pin_val);   
}

 
void setup() {
  /*********************************
   GPS POSITION LOGGER LAT/LONG/UTC
    *******************************/
 
  // Set LED pin as output
  pinMode(recLED, OUTPUT);
 
  // Start Serial Monitor for debugging
  Serial.begin(115200);
 
  // Start SoftwareSerial
  ss.begin(GPSBaud);
 
  // Initialize SD card
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present for GPS");
    //don't do anything more:
    while (1);
  }
  Serial.println("card initialized for GPS.");
 
  // Blink LED so we know we are ready for GPS
  digitalWrite(recLED, HIGH);
  delay(500);
  digitalWrite(recLED, LOW);
  delay(500);
  digitalWrite(recLED, HIGH);
  delay(500);
  digitalWrite(recLED, LOW);
  delay(500);
  digitalWrite(recLED, HIGH);
  delay(500);
  digitalWrite(recLED, LOW);

  // Header
    //Serial.println(F("Latitude  Longitude   Date   UTC"));
    //Serial.println(F(" (deg)      (deg)               "));
    //Serial.println(F("--------------------------------"));

  /*********************************
   SOUND DETECTOR
    *******************************/
   // Serial.begin(115200);

  //  Configure LED pin as output
  pinMode(PIN_LED_OUT, OUTPUT);

  // configure input to interrupt
  pinMode(PIN_GATE_IN, INPUT);
  attachInterrupt(IRQ_GATE_IN, soundISR, CHANGE);

  // Display status
  Serial.println("Sound Initialized");
 
}

void processGPSData() 
{
  // code to process GPS data here
}
 
void logSoundData() {
int soundValue;

  // Check the envelope input
  soundValue = analogRead(PIN_ANALOG_IN);

}

void loop() {
 logGPSandSOUND();
 
 /****************
  * check the current time and trigger the sound logging function at the specified interval:
  * ***************************/
  
  // Check if GPS data is available and process it
  while (ss.available() > 0) {
    if (gps.encode(ss.read())) {
      processGPSData();
    }
  }
  
}
