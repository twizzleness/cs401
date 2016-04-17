#include <SoftwareSerial.h>

/**************************************************************************
 *                                                                         *
    W O R D C L O C K   - A clock that tells the time using words.
 *                                                                         *
   Hardware: Arduino Dumelove with a set of individual LEDs under a word
              stencil.
 *                                                                         *
     Copyright (C) 2009  Doug Jackson (doug@doughq.com)
 *                                                                         *
 ***************************************************************************
 *                                                                         *
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
 *                                                                         *
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
 *                                                                         *
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston,
   MA  02111-1307  USA
 *                                                                         *
 ***************************************************************************

   Revision History

   Date    By  What
   20001025 DRJ Initial Creation of Arduino Version
                        - based on Wordclock.c - from PIC version
*/


// Display output pin assignments

#define ONE     Display1=Display1 | (1<<0)
#define MINUTES Display1=Display1 | (1<<1)
#define ITIS    Display1=Display1 | (1<<2)
#define HTEN    Display1=Display1 | (1<<3)
#define MFIVE   Display1=Display1 | (1<<6)
#define HALF    Display1=Display1 | (1<<5)
#define TWO     Display1=Display1 | (1<<4)

#define PAST    Display2=Display2 | (1<<0)
#define SEVEN   Display2=Display2 | (1<<1)
#define TO      Display2=Display2 | (1<<2)
#define ELEVEN  Display2=Display2 | (1<<3)
#define SIX     Display2=Display2 | (1<<6)
#define THREE   Display2=Display2 | (1<<5)
#define TWELVE  Display2=Display2 | (1<<4)

#define QUARTER Display3=Display3 | (1<<0)
#define TWENTY  Display3=Display3 | (1<<1)
#define MTEN    Display3=Display3 | (1<<2)
#define EIGHT   Display3=Display3 | (1<<3)
#define NINE    Display3=Display3 | (1<<6)
#define HFIVE   Display3=Display3 | (1<<5)
#define FOUR    Display3=Display3 | (1<<4)

#define RAINY  Display4=Display4 | (1 << 0)
#define CLOUDY Display4=Display4 | (1 << 1)
#define SNOWY  Display4=Display4 | (1 << 2)
#define SUNNY  Display4=Display4 | (1 << 3)

SoftwareSerial esp8266(8, 9);



int  hour = 4, minute = 14, second = 40;
static unsigned long msTick = 0; // the number of Millisecond Ticks since we last
// incremented the second counter
int  count;
int selftestmode;
//char Display1=0, Display2=0, Display3=0;
unsigned long Display1 = 0, Display2 = 0, Display3 = 0, Display4 = 0;


// hardware constants
int LEDClockPin = 5;
int LEDDataPin = 4;
int LEDStrobePin = 4;
int FWDButtonPin = 6;
int REVButtonPin = 7;


void setup()
{
  // initialise the hardware
  // initialize the appropriate pins as outputs:
  pinMode(LEDClockPin, OUTPUT);
  pinMode(LEDDataPin, OUTPUT);
  pinMode(LEDStrobePin, OUTPUT);
  pinMode(FWDButtonPin, OUTPUT);
  pinMode(REVButtonPin, INPUT);


  esp8266.begin(9600);
  Serial.begin(9600);   // setup the serial port to 9600 baud

    
  SWversion();          // Display the version number of the software

  msTick = millis();    // Initialise the msTick counter
  selftest();                           /////////////////////////////////////////////////////////////////////////////////uncomment this later
  selftestmode = 0;

  getWeather();
  displaytime();        // display the current time
  
}

void ledsoff(void) {
  Display1 = 0;
  Display2 = 0;
  Display3 = 0;
  Display4 = 0;
}

void WriteLEDs(void) {
  // Now we write the actual values to the hardware
  shiftOut(LEDDataPin, LEDClockPin, MSBFIRST, Display4);
  shiftOut(LEDDataPin, LEDClockPin, MSBFIRST, Display3);
  shiftOut(LEDDataPin, LEDClockPin, MSBFIRST, Display2);
  shiftOut(LEDDataPin, LEDClockPin, MSBFIRST, Display1);
  digitalWrite(LEDStrobePin, HIGH);
  delay(2);
  digitalWrite(LEDStrobePin, LOW);

}
void WriteWeather(void) {
  // Now we write the actual values to the hardware
  shiftOut(LEDDataPin, LEDClockPin, MSBFIRST, Display4);
  shiftOut(LEDDataPin, LEDClockPin, MSBFIRST, Display3);
  shiftOut(LEDDataPin, LEDClockPin, MSBFIRST, Display2);
  shiftOut(LEDDataPin, LEDClockPin, MSBFIRST, Display1);
  digitalWrite(LEDStrobePin, HIGH);
  delay(2);
  digitalWrite(LEDStrobePin, LOW);

}

void selftest(void) {
  // start by clearing the display to a known state
  ledsoff(); ITIS; WriteLEDs(); delay(500); //correct
  ledsoff(); HALF; WriteLEDs(); delay(500);
  ledsoff(); MTEN; WriteLEDs(); delay(500);
  ledsoff(); QUARTER; WriteLEDs(); delay(500);
  ledsoff(); TWENTY; WriteLEDs(); delay(500);
  ledsoff(); MFIVE; WriteLEDs(); delay(500);
  ledsoff(); MINUTES; WriteLEDs(); delay(500);
  ledsoff(); TO; WriteLEDs(); delay(500);
  ledsoff(); PAST; WriteLEDs(); delay(500);
  ledsoff(); ONE; WriteLEDs(); delay(500);
  ledsoff(); TWO; WriteLEDs(); delay(500);
  ledsoff(); THREE; WriteLEDs(); delay(500);
  ledsoff(); FOUR; WriteLEDs(); delay(500);
  ledsoff(); HFIVE; WriteLEDs(); delay(500);
  ledsoff(); SIX; WriteLEDs(); delay(500);
  ledsoff(); SEVEN; WriteLEDs(); delay(500);
  ledsoff(); EIGHT; WriteLEDs(); delay(500);
  ledsoff(); NINE; WriteLEDs(); delay(500);
  ledsoff(); HTEN; WriteLEDs(); delay(500);
  ledsoff(); ELEVEN; WriteLEDs(); delay(500);
  ledsoff(); TWELVE; WriteLEDs(); delay(500);
  ledsoff(); RAINY; WriteLEDs(); delay(500);
  ledsoff(); SNOWY; WriteLEDs(); delay(500);
  ledsoff(); CLOUDY; WriteLEDs(); delay(500);
  ledsoff(); SUNNY; WriteLEDs(); delay(500);

  //ledsoff(); OCLOCK; WriteLEDs(); delay(500);
  // ledsoff(); DOUG; WriteLEDs(); delay(500);
  //ledsoff(); ARDUINO; WriteLEDs(); delay(500);
  for (int i = 0; i < 5; i++)
  {
    Display1 = 255; Display2 = 255; Display3 = 255, Display4 = 255;
    WriteLEDs(); delay(500);
    ledsoff(); WriteLEDs(); delay(500);
  }
}


void displaytime(void) {

  // start by clearing the display to a known state
  unsigned long temp = Display4;
  ledsoff();
  Display4 = temp;

  // Now, turn on the "It is" leds
  ITIS;
  Serial.print("It is ");

  // now we display the appropriate minute counter
  if ((minute > 4) && (minute < 10)) {
    MFIVE;
    MINUTES;
    Serial.print("Five Minutes ");
  }
  if ((minute > 9) && (minute < 15)) {
    MTEN;
    MINUTES;
    Serial.print("Ten Minutes ");
  }
  if ((minute > 14) && (minute < 20)) {
    QUARTER;
    Serial.print("Quarter ");
  }
  if ((minute > 19) && (minute < 25)) {
    TWENTY;
    MINUTES;
    Serial.print("Twenty Minutes ");
  }
  if ((minute > 24) && (minute < 30)) {
    TWENTY;
    MFIVE;
    MINUTES;
    Serial.print("Twenty Five Minutes ");
  }
  if ((minute > 29) && (minute < 35)) {
    HALF;
    Serial.print("Half ");
  }
  if ((minute > 34) && (minute < 40)) {
    TWENTY;
    MFIVE;
    MINUTES;
    Serial.print("Twenty Five Minutes ");
  }
  if ((minute > 39) && (minute < 45)) {
    TWENTY;
    MINUTES;
    Serial.print("Twenty Minutes ");
  }
  if ((minute > 44) && (minute < 50)) {
    QUARTER;
    Serial.print("Quarter ");
  }
  if ((minute > 49) && (minute < 55)) {
    MTEN;
    MINUTES;
    Serial.print("Ten Minutes ");
  }
  if (minute > 54) {
    MFIVE;
    MINUTES;
    Serial.print("Five Minutes ");
  }

  if ((minute < 5))
  {
    switch (hour) {
      case 1:
        ONE;
        Serial.print("One ");
        break;
      case 2:
        TWO;
        Serial.print("Two ");
        break;
      case 3:
        THREE;
        Serial.print("Three ");
        break;
      case 4:
        FOUR;
        Serial.print("Four ");
        break;
      case 5:
        HFIVE;
        Serial.print("Five ");
        break;
      case 6:
        SIX;
        Serial.print("Six ");
        break;
      case 7:
        SEVEN;
        Serial.print("Seven ");
        break;
      case 8:
        EIGHT;
        Serial.print("Eight ");
        break;
      case 9:
        NINE;
        Serial.print("Nine ");
        break;
      case 10:
        HTEN;
        Serial.print("Ten ");
        break;
      case 11:
        ELEVEN;
        Serial.print("Eleven ");
        break;
      case 12:
        TWELVE;
        Serial.print("Twelve ");
        break;
    }
    //  OCLOCK;
    //  Serial.println("O'Clock");
  }
  else if ((minute < 35) && (minute > 4))
  {
    PAST;
    Serial.print("Past ");
    switch (hour) {
      case 1:
        ONE;
        Serial.println("One ");
        break;
      case 2:
        TWO;
        Serial.println("Two ");
        break;
      case 3:
        THREE;
        Serial.println("Three ");
        break;
      case 4:
        FOUR;
        Serial.println("Four ");
        break;
      case 5:
        HFIVE;
        Serial.println("Five ");
        break;
      case 6:
        SIX;
        Serial.println("Six ");
        break;
      case 7:
        SEVEN;
        Serial.println("Seven ");
        break;
      case 8:
        EIGHT;
        Serial.println("Eight ");
        break;
      case 9:
        NINE;
        Serial.println("Nine ");
        break;
      case 10:
        HTEN;
        Serial.println("Ten ");
        break;
      case 11:
        ELEVEN;
        Serial.println("Eleven ");
        break;
      case 12:
        TWELVE;
        Serial.println("Twelve ");
        break;
    }
  }
  else
  {
    // if we are greater than 34 minutes past the hour then display
    // the next hour, as we will be displaying a 'to' sign
    TO;
    Serial.print("To ");
    switch (hour) {
      case 1:
        TWO;
        Serial.println("Two ");
        break;
      case 2:
        THREE;
        Serial.println("Three ");
        break;
      case 3:
        FOUR;
        Serial.println("Four ");
        break;
      case 4:
        HFIVE;
        Serial.println("Five ");
        break;
      case 5:
        SIX;
        Serial.println("Six ");
        break;
      case 6:
        SEVEN;
        Serial.println("Seven ");
        break;
      case 7:
        EIGHT;
        Serial.println("Eight ");
        break;
      case 8:
        NINE;
        Serial.println("Nine ");
        break;
      case 9:
        HTEN;
        Serial.println("Ten ");
        break;
      case 10:
        ELEVEN;
        Serial.println("Eleven ");
        break;
      case 11:
        TWELVE;
        Serial.println("Twelve ");
        break;
      case 12:
        ONE;
        Serial.println("One ");
        break;
    }
  }
  WriteLEDs();
}


void incrementtime(void) {
  // increment the time counters keeping care to rollover as required
  second = 0;
  if (++minute >= 60) {
    minute = 0;
    if (++hour == 13) {
      hour = 1;
    }
  }
  // debug outputs
  Serial.println();
  Serial.print(hour);
  Serial.print(",");
  Serial.print(minute);
  Serial.print(",");
  Serial.println(second);

}


void SWversion(void) {
  delay(2000);
  Serial.println();
  Serial.println("Wordclock -Arduino v1.0");
  Serial.println("(c)2009 Doug Jackson");
}


void loop(void)
{

  // heart of the timer - keep looking at the millisecond timer on the Arduino
  // and increment the seconds counter every 1000 ms
  if ( millis() - msTick > 999) {
    msTick = millis();
    second++;
    // Flash the onboard Pin13 Led so we know something is hapening!
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
  }



  //test to see if we need to increment the time counters
  if (second == 60)
  {
    incrementtime();
    displaytime();
  }

  // test to see if both buttons are being held down
  // if so  - start a self test till both buttons are held
  // down again.
  if ( digitalRead(FWDButtonPin) == 1 && digitalRead(REVButtonPin) == 1)
  {
    selftestmode = !selftestmode;
  }

  if (selftestmode) {
    for (int i = 0; i < 100; i++)
    {
      Display1 = 255; Display2 = 255; Display3 = 255;
      WriteLEDs(); delay(101 - i);
      ledsoff(); WriteLEDs(); delay(101 - i);
      if (digitalRead(FWDButtonPin) == 1) selftestmode = !selftestmode;

    }
    displaytime();

  }


  // test to see if a forward button is being held down
  // for time setting
  if ( (digitalRead(FWDButtonPin) == 1 ) && second != 1)
    // the forward button is down
    // and it has been more than one second since we
    // last looked
  {
    minute = (((minute / 5) * 5) + 5);
    second = 0;
    incrementtime();
    second++;  // Increment the second counter to ensure that the name
    // flash doesnt happen when setting time
    displaytime();
  }

  // test to see if the back button is being held down
  // for time setting
  if ((digitalRead(REVButtonPin) == 1 ) && second != 1)
  {
    minute = (((minute / 5) * 5) - 5);
    second = 0; // decrement the minute counter
    if (minute < 0) {
      minute = 55;
      if (--hour < 0) hour = 12;
    }
    incrementtime();
    second++;  // Increment the second counter to ensure that the name
    // flash doesnt happen when setting time
    displaytime();
  }
}

void getWeather() {
  Serial.println("AT+CIPSTART=\"TCP\",\"api.wunderground.com\",80");
  String cmd;
  int length;
  cmd = "AT+CIPSTART=\"TCP\",\"api.wunderground.com\",80";
    Serial.println(cmd);
  esp8266.println("AT+CIPSTART=\"TCP\",\"api.wunderground.com\",80");

  delay(4000);
  Serial.write(esp8266.read());
  if (esp8266.find("CONNECT")) {
    Serial.println("CONNECT found so your connected");
    //return false;
  }
  //GET http://api.wunderground.com/api/7287eb3ace065563/conditions/q/Canada/Regina.json HTTP/1.0\r\n\r\n
  char action[101] = "GET http://api.wunderground.com/api/7287eb3ace065563/conditions/q/Canada/Regina.json HTTP/1.0\r\n\r\n";
  //action = "GET http://api.wunderground.com/api/7287eb3ace065563/conditions/q/Canada/Regina.json HTTP/1.0\r\n\r\n";
  length = strlen(action);
  cmd = "AT+CIPSEND=";
  cmd += length;
  esp8266.print("AT+CIPSEND=");
  esp8266.println(length);
  Serial.print("AT+CIPSEND=");
  Serial.println(length);
  //    esp8266.println(action.length() + 4);
  //    Serial.println(action.length() + 4);

  delay(5000);
  if (esp8266.find(">")) {
    Serial.print(">");
  }
  else {
    esp8266.println("AT+CIPCLOSE");
    Serial.println(F("connect timeout"));
    //return false;
  }

  esp8266.println("GET http://api.wunderground.com/api/7287eb3ace065563/conditions/q/Canada/Regina.json HTTP/1.0\r\n\r\n");
  Serial.println("GET http://api.wunderground.com/api/7287eb3ace065563/conditions/q/Canada/Regina.json HTTP/1.0\r\n\r\n");
  delay(1800);
  char test[1000];
  int i = 0;
  while (i < 1000) {
    char c = esp8266.read();
    Serial.print(c);
    test[i] = c;
    // Serial.write(c);
    i++;
  }
  Serial.println("");
  for (int i = 0; i < 1000; i++) {
    Serial.print(test[i]);
  }
  Serial.println(" ");
  parser(test);
}

void parser(char test[]) {
  Display4 = 0;
  if (strstr(test, "Cloud") != NULL){
    Serial.println("Cloudy");
    CLOUDY;
  }
    if (strstr(test, "Overcast") != NULL){
    Serial.println("Cloudy");
    CLOUDY;
  }
  if (strstr(test, "Sun") != NULL){
    Serial.println("Sunny");
    SUNNY;
  }
  if (strstr(test, "Rain") != NULL){
    Serial.println("Rainy");
    RAINY;
  }
  if (strstr(test, "Snow") != NULL){
    Serial.println("Snowy");
    SNOWY;
  }
    if (strstr(test, "flurries") != NULL){
    Serial.println("Snowy");
    SNOWY;
  }

}


