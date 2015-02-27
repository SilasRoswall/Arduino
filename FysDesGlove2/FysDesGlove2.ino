#include <tone.h>

const int ledCount = 10;
int power = 0;
int hold = 0;


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

  //charge the glove
  if(sensorValue > 800 && power < 10){
     digitalWrite(ledPins[power], HIGH);
     tone(6, (440*power)/2, 100);
     power++;
     delay(100);
  }
  
  //Full charge sound.
  if(power >= 10 && sensorValue > 800){
     tone(6, 440*10/2,400);
     hold++;
     delay(400);
  }
  
  //shot
  if(sensorValue < 700 && power == 10){
    shoot();
    delay(2500);
  }
  
  //decharge the glove
  if(sensorValue < 700 && power != 10 && power >= 0){
     digitalWrite(ledPins[power], LOW);
     tone(6, (440*power)/2, 100);
     power--;
     delay(50);
  }
  
  //overload
  if(hold >= 5){
     overload();
  } 

}

void shoot () {
  noTone(6);
  power = 0;
  //reset the overload function
  hold = 0;
  for(int thisLed = 0; thisLed < ledCount; thisLed++){
    digitalWrite(ledPins[thisLed], LOW);
  }
  digitalWrite(3, HIGH);
  delay(300);
  digitalWrite(3, LOW);
}


//overloading 
void overload(){
    hold = 0;
    power = 0;
    tone(6, 1300, 600);
    
    for(int thisLed = 10; thisLed >= 0; thisLed--){
    delay(50);
    digitalWrite(ledPins[thisLed], LOW);
    }
    
    for(int r = 0; r<8; r++){
      digitalWrite(4, HIGH);
      tone(6, 1200, 300);
      delay(300);
      digitalWrite(4, LOW);
      tone(6, 1000, 300);
      delay(300);
    }
}

//turn on all the lights <3
void writeAll(boolean state){
    for(int thisLed = 0; thisLed < ledCount; thisLed++){
    digitalWrite(ledPins[thisLed], state);
    }  
}
