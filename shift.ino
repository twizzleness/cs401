//Pin connected to latch pin (ST_CP) of 74HC595
//const int latchPin = 8;
//Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 12;
////Pin connected to Data in (DS) of 74HC595
const int dataPin = 11;

void setup() {
  // put your setup code here, to run once:
  //pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("reset");
}

void loop() {
  // put your main code here, to run repeatedly:
//  if (Serial.available() > 0) {
//    // ASCII '0' through '9' characters are
//    // represented by the values 48 through 57.
//    // so if the user types a number from 0 through 9 in ASCII, 
//    // you can subtract 48 to get the actual value:
//    int bitToSet = Serial.read() - 48;
//
//  // write to the shift register with the correct bit set high:
//    registerWrite(bitToSet, HIGH);
//  }
shiftOut(dataPin, clockPin, LSBFIRST, HIGH);
shiftOut(dataPin, clockPin, LSBFIRST, LOW);
}

void registerWrite(int whichPin, int whichState) {
  // the bits you want to send
  byte bitsToSend = 0;

  // turn off the output so the pins don't light up
  // while you're shifting bits:
 // digitalWrite(latchPin, LOW);

  // turn on the next highest bit in bitsToSend:
  bitWrite(bitsToSend, whichPin, whichState);

  // shift the bits out:
  shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend);

    // turn on the output so the LEDs can light up:
  //digitalWrite(latchPin, HIGH);
}
