//multiple teensys

//midi channel
int sendChannel = 1;

//midi control number
int sendControl = 9;

//midi control value
int sendValue = 120;

void setup() {
 //begin serial communication
  Serial.begin(115200);
}

void loop() {
  
  //usbMIDI.sendControlChange(control, value, channel);
  usbMIDI.sendControlChange(sendControl, sendValue, sendChannel);

  delay(1000);
}
