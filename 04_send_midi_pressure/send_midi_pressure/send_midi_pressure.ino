//teensy send midi note
//when a button toggles

/*
  Example using the SparkFun HX711 breakout board with a scale
  By: Nathan Seidle
  SparkFun Electronics
  Date: November 19th, 2014
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  This example demonstrates basic scale output. See the calibration sketch to get the calibration_factor for your
  specific load cell setup.

  This example code uses bogde's excellent library: https://github.com/bogde/HX711
  bogde's library is released under a GNU GENERAL PUBLIC LICENSE

  The HX711 does one thing well: read load cells. The breakout board is compatible with any wheat-stone bridge
  based load cell which should allow a user to measure everything from a few grams to tens of tons.
  Arduino pin 2 -> HX711 CLK
  3 -> DAT
  5V -> VCC
  GND -> GND

  The HX711 board can be powered from 2.7V to 5V so the Arduino 5V power should be fine.
*/

//library from https://github.com/aguegu/ardulibs/tree/master/hx711
#include "HX711.h"

#define calibration_factor -7050.0 //This value is obtained using the SparkFun_HX711_Calibration sketch

#define DOUT  3
#define CLK  2

HX711 scale(DOUT, CLK);

boolean buttonPressed = false;
int midiChannel = 1;
int note;

float reading;
float decisionValue = 100;

void setup() {

  Serial.begin(115200);

  pinMode(pinReading, INPUT);

  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare();  //Assuming there is no weight on the scale at start up, reset the scale to 0


}


void loop() {

  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);

  readPin();

  //usbMIDI.sendNoteOn(note, velocity, channel);
  usbMIDI.sendNoteOn(note, 127, midiChannel);
  delay(1000);
}


void readPin() {

  reading = scale.get_units();

  if (reading > decisionValue ) {
    note = 100;
  }
  else {
    note = 70;
  }
}
