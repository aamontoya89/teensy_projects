//teensy
//by david
//may 2018

//midi variables
int receivePitches[] = {61, 62, 63, 64};
int receiveVelocities[] = {0, 0, 0, 0};
int receiveChannel = 1;


void setup() {
  //WARNING: remember to match this baud rate in the terminal
  Serial.begin(115200);

  //callback to myNoteOn function
  //whenever teensy receives a note on message
  usbMIDI.setHandleNoteOn(myNoteOn);

}

void loop() {

  //do stuff with the data in receiveVelocities array
  //WARNING: do a lot of Serial.println so you can see the actual vales
  //assume nothing, trust no one

}

//declare function to handle new note on message from max
//WARNING: we are comparing bytes with ints
void myNoteOn(byte channel, byte note, byte velocity) {

  //check that it is channel 1
  //cast the byte value of channel to an integer
  //WARNING: maybe this casting is wrong??
  //check also the same for note and velocity
  //maybe try serial printing it
  if ((int)channel == receiveChannel) {

    //Serial.println("message on channel 1");

    //iterate through all the pitches
    //pitch is integers 0, 1, 2, 3
    for (int pitch = 0; pitch < sizeof(receivePitches); pitch++) {

      //update the corresponding velocity value
      //note is the byte value of the incoming value
      if ((int)note == receivePitches[pitch]) {
        receiveVelocities[pitch] = (int)velocity;
      }
    }
  }

}

