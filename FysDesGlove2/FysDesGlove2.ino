
#include <tone.h>
#include <IRremote.h>
//Pin 6 is used for sound.
//Pin 3 is used for IR sender.
//A1 is used for presure plate.

IRsend irsend;
const int ledCount = 10;
int power = 0;
int hold = 0;

//---- Connect the LED-BAR[10] from low to high.
int ledPins[] = { 
 // 4, 5, 7, 8, 9, 10, 16 ,14 ,15, A0 };   // an array of pin numbers to which LEDs are attached
4, 5, 7, 8, 9, 15, A0, 14, 16, 10 };

// raw poweron signal
unsigned int powerOn[148] = {4400,4250,550,1600,600,1550,600,1550,550,1600,550,500,550,550,550,1550,600,500,550,500,600,500,550,500,600,450,600,1550,600,1550,550,500,600,1550,550,550,550,500,600,500,550,500,550,500,600,500,550,1600,550,1550,600,1550,600,1550,600,1550,600,1550,550,1600,550,1550,600,500,550,500,600,500,550,500,550,550,550,500,600,450,600,500,550,500,550,1600,550,1600,550,500,600,500,550,1600,550,500,550,500,550,550,550,500,600,500,550,500,600,450,600,500,550,500,550,550,550,500,600,1550,600,450,600,500,550,500,550,550,550,500,600,450,600,500,550,500,600,1550,550,500,600,500,600,1550,550,500,600,500,550,500,550,500,600};


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
  int sensorValue = analogRead(A1);

  digitalWrite(3, HIGH);
  delay(2000);
  digitalWrite(3, LOW);
  irsend.sendRaw(powerOn,148,38);
   delay(2000);
    
  //charge the glove
  if(sensorValue < 800 && power < 10){
     digitalWrite(ledPins[power], HIGH);
     tone(6, (440*power)/2, 100);
     power++;
     delay(100);
  }
  
  //Full charge sound.
  if(power >= 10 && sensorValue < 800){
     tone(6, 440*10/2,400);
     hold++;
     delay(400);
  }
  
  //shot
  if(sensorValue > 700 && power == 10){
    shoot();
    delay(2500);
  }
  
  //decharge the glove
  if(sensorValue > 700 && power != 10 && power > 0){
     tone(6, (440*power)/2, 100);
     power--;
     digitalWrite(ledPins[power], LOW);
     delay(50);
  }
  
  //call the overload method
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
  //digitalWrite(3, HIGH);
  //delay(300);
  //digitalWrite(3, LOW);

}


//overloading will be reset power and hold, 
//and then play a anoying sound, turn of the lights and blink, before ready to use again.
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











/*
void loop() {

	while(!Serial.available());
	char rx=Serial.read();
	unsigned int rx_int=(unsigned int)rx;

	Serial.print("Sending ");
	Serial.println(rx);
	irsend.sendSony(rx_int,32); //8 bits
	//irsend.sendRaw(&rx,1,36);

}
*/
