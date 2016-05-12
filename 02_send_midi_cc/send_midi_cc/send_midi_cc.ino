//teensy send midi control change message

int sendControl = 9;
int sendValue = 120;
int sendChannel = 1;

void setup() {
 
  Serial.begin(115200);
  usbMIDI.setHandlePitchChange(OnPitchChange);
}

void loop() {
  
  //usbMIDI.sendControlChange(control, value, channel);
  usbMIDI.sendControlChange(sendControl, int(random(127)), sendChannel);

  delay(1000);
}

void OnPitchChange(byte channel, int pitch) {
  Serial.print("Pitch Change, ch=");
  Serial.print(channel, DEC);
  Serial.print(", pitch=");
  Serial.print(pitch, DEC);
  Serial.println();
}
