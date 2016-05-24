//multiple teensys

//midi channel
int sendChannel = 1;

//midi control number
int sendControl = 4;

//midi control value
int sendValue = 120;

void setup() {
 //begin serial communication
  Serial.begin(115200);
}

void loop() {
  
  //usbMIDI.sendControlChange(control, value, channel);
  sendValue = random(128);
  usbMIDI.sendControlChange(sendControl, sendValue, sendChannel);

  delay(1000);
}
