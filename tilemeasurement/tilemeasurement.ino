#include <HX711.h>

//////////////////////////////////
// BOARD SETUP
//////////////////////////////////

//either 1 or 2 sensors are connected
#define SENSOR_COUNT 1
//the cc channel of the first sensor
#define CC0_NUM 1
//if there is a second channel
#define CC1_NUM 2
//if there is a thirdchannel
#define CC2_NUM 3

//the midi channel that the CC is sent on
#define MIDI_CHANNEL 1

//values over map to 127 on the CC output
#define SENSOR_THRESH 1

//////////////////////////////////
// END BOARD SETUP
//////////////////////////////////


int scaleValue0 = 0;
int scaleValue1 = 0;
int scaleValue2 = 0;

int lastSend = 0;

#define calibration_factor -7050.0 //This value is obtained using the SparkFun_HX711_Calibration sketch
#define CLK  2
#define DOUT1  3
#define DOUT2  4
#define DOUT3  5

HX711 scale0(DOUT1, CLK);

#if SENSOR_COUNT > 1
  HX711 scale1(DOUT2, CLK);
#endif

#if SENSOR_COUNT > 2
  HX711 scale2(DOUT3, CLK);
#endif

void setup() {

//  Serial.begin(9600);
  scale0.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale0.tare();  //Assuming there is no weight on the scale at start up, reset the scale to 0

  #if SENSOR_COUNT > 1
    scale1.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
    scale1.tare();  //Assuming there is no weight on the scale at start up, reset the scale to 0
  #endif

  #if SENSOR_COUNT > 2
    scale2.set_scale(calibration_factor);
    scale2.tare();
  #endif
}

int sendIfDifferent(int channel, HX711 scale, int prevValue){
  int value = map(scale.get_units(), 6, 50, 0, 127);
  value = max(value, 0);
  if (value != prevValue){
    usbMIDI.sendControlChange(channel, value, MIDI_CHANNEL);
    return value;
  }
  return prevValue;
}

void loop() {

  scaleValue0 = sendIfDifferent(CC0_NUM, scale0, scaleValue0);

  //resent a heart beat every 500 ms
  if (millis() - lastSend > 500){
    lastSend = millis();
    usbMIDI.sendControlChange(CC0_NUM, scaleValue0, MIDI_CHANNEL);
  }

  #if SENSOR_COUNT > 1
    scaleValue1 = sendIfDifferent(CC1_NUM, scale1, scaleValue1);
  #endif

  #if SENSOR_COUNT > 2
    scaleValue2 = sendIfDifferent(CC2_NUM, scale2, scaleValue2);
  #endif


  delay(5);
}
