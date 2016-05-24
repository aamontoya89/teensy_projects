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

#include <HX711.h>

#define calibration_factor -7050.0 //This value is obtained using the SparkFun_HX711_Calibration sketch

#define CLK  2
#define DOUT1  3
#define DOUT2  4

int sendControl1 = 1;
int sendChannel1 = 1;
int sendValue1 = 120;

int sendControl2 = 2;
int sendChannel2 = 1;
int sendValue2 = 120;

HX711 scale1(DOUT1, CLK);
HX711 scale2(DOUT2, CLK);

void setup() {
  //Serial.begin(9600);
  Serial.begin(115200);

  scale1.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale1.tare();  //Assuming there is no weight on the scale at start up, reset the scale to 0

  scale2.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale2.tare();  //Assuming there is no weight on the scale at start up, reset the scale to 0
}

void loop() {

  sendValue1 = int(map(scale1.get_units(), 0, 300, 0, 128));
  sendValue2 = int(map(scale2.get_units(), 0, 300, 0, 128));

  usbMIDI.sendControlChange(sendControl1, sendValue1, sendChannel1);
  delay(500);

  usbMIDI.sendControlChange(sendControl2, sendValue2, sendChannel2);
  delay(500);

}
