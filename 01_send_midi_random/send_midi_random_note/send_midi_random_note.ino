//teensy send midi random note

int channel = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {

  //receive USB midi
  //usbMIDI.read();

  //usbMIDI.sendNoteOn(note, velocity, channel);
  int note = int(random(127));
  usbMIDI.sendNoteOn(note, 127, channel);
  delay(1000);
}
