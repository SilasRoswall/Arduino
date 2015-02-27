#include <tone.h>

const int ledCount = 10;
int power = 0;


int ledPins[] = { 
 4, 5, A1, 7, 8, 9, 10, 11 ,12 ,13 };   // an array of pin numbers to which LEDs are attached


void setup() {
  // loop over the pin array and set them all to output:
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT); 
  }
  
  //presure sensor
  Serial.begin(9600);
}

void loop(){
   // Read the input on analog pin 0:
  int sensorValue = analogRead(A0);

  if(sensorValue > 800 && power < 10){
     digitalWrite(ledPins[power], HIGH);
     tone(6, (440*power)/2, 100);
     power++;
     delay(100);
  }
  
  if(power >= 10 && sensorValue > 800){
     tone(6, 440*10/2); 
  }
  
  
  if(sensorValue < 500 && power == 10) shoot();

}

void shoot () {
  noTone(6);
  power = 0;
  for(int thisLed = 0; thisLed < ledCount; thisLed++){
    digitalWrite(ledPins[thisLed], LOW);
  }
  digitalWrite(3, HIGH);
  delay(300);
  digitalWrite(3, LOW);
}

