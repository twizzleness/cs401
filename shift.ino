//Pin connected to latch pin (ST_CP) of 74HC595
//const int latchPin = 8;
//Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 9;
////Pin connected to Data in (DS) of 74HC595
const int dataPin = 8;

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
//for(int i = 0; i < 3; i++){
//  shiftOut(dataPin, clockPin, MSBFIRST, B00000001 << i);
//  delay(125);
//}
//shiftOut(dataPin, clockPin, LSBFIRST, LOW);
  for(int i=0; i < 6000000; i++){
    if(i == 3000){
      turnLightsOn(B10001110);
    }
  }
}

void turnLightsOn(int value) {
  shiftOut(dataPin, clockPin, LSBFIRST, value);
  delay(125);
}
