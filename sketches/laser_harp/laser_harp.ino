bool debug = true;

int num_notes = 6;
int note_state = 0; // note is on if bit in note's position is 1
int old_note_state = 0;
int photocell_threshold = 300;

int photocell_reading;

int note_pins[] = {0, 1, 2, 3, 4, 5};

int ps_print[6];

int note_index = 0;

///////////////////
int photocellPin = 2;     // the LDR and cap are connected to pin2
int photocellReading;     // the digital reading
int RCtime(int RCpin) {
  int reading = 0;  // start with 0
 
  // set the pin to an output and pull to LOW (ground)
  pinMode(RCpin, OUTPUT);
  digitalWrite(RCpin, LOW);
 
  // Now set the pin to an input and...
  pinMode(RCpin, INPUT);
  while (digitalRead(RCpin) == LOW) { // count how long it takes to rise up to HIGH
    reading++;      // increment to keep track of time 
 
    if (reading == 30000) {
      // if we got this far, the resistance is so high
      // its likely that nothing is connected! 
      break;           // leave the loop
    }
  }
  // OK either we maxed out at 30000 or hopefully got a reading, return the count
 
  return reading;
}
////////////////////

void setup() {
  Serial.begin(9600);      // open the serial port at 9600 bps
}

void loop() {
  /*
  note_state = 0;
  for (note_index = 0; note_index < num_notes; note_index++){
    photocell_reading = analogRead(note_pins[note_index]);
    
    if (debug){
      Serial.print(photocell_reading);
      Serial.print("\t");
    }
    
    if (photocell_reading < photocell_threshold){
      note_state = note_state + (1 << note_index);
    }
  } */

  photocellReading = RCtime(photocellPin);
  if (photocellReading == 30000){
    Serial.println("bad");
  }
  else {
    Serial.print(photocellReading);
    Serial.print(" boop\t");
  }

  //Serial.print("\t:   ");
  /*
  if ((old_note_state ^ note_state) and (!debug)){
    Serial.write(note_state);
    old_note_state = note_state;
  }*/
  if (debug){
    Serial.println();
    delay(500);
  }
}


