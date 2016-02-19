#include <SoftwareSerial.h>

int clockInt = 0;            // digital pin 2 is now interrupt 0
int masterClock = 0;         // counts rising edge clock signals
int seconds = 0;             // variable
int minutes = 0;             // variable
int ledPin = 13;
int ledState = LOW;



void setup() {
  // put your setup code here, to run once:
  attachInterrupt(clockInt, clockCounter, CHANGE);
  //  clockInt is our interrupt, clockCounter function is called when
  //  invoked on a RISING clock edge
  analogReference(DEFAULT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  analogWrite(0, 127);   // this starts our PWM 'clock' with a 50% duty cycle
}


void clockCounter()      // called by interrupt
{
  Serial.println("Look im in an interupt");
  masterClock ++;        // with each clock rise add 1 to masterclock count
  if(masterClock == 489) // 490Hz reached     
  {                         
    seconds ++;          // after one 490Hz cycle add 1 second ;)
    masterClock = 0;     // Reset after 1 second is reached
    tone(13, 100, 500);  // using tone to pulse LED without delay call ;)
  }
  return;
}
void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("clocks are dumb");
 
  if(seconds == 60)      // NOW GETTING IN TO REAL TIME KEEPING
  {
    minutes ++;          // increment minutes by 1
    seconds = 0;         // reset the seconds variable
    Serial.print("Minutes = ");
    Serial.println(minutes);
  }
}
