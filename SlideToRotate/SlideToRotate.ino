#include <Servo.h>

//static unsigned int volumeServoZero=45;
//static unsigned int volumeServoUp=38;
//static unsigned int volumeServoDown=50;

int servoRotationSpeed;

int softpotPin = A0; //analog pin 0
Servo myservo;

void setup(){
  pinMode(softpotPin, INPUT_PULLUP); //enable pullup resistor
  Serial.begin(9600);
  myservo.attach(9);
}

void loop(){
  
  servoSpeed();
  myservo.write(servoRotationSpeed);
  //myservo.write(softpotReading/360);
}

void servoSpeed(){
  int softpotReading = analogRead(softpotPin); 

  Serial.println(softpotReading);
  delay(250); //just here to slow down the output for easier reading

  
  if(softpotReading>1000) servoRotationSpeed = 90;
  else if (softpotReading>800) servoRotationSpeed = 100;
  else if (softpotReading>700) servoRotationSpeed = 105;
  else if (softpotReading>600) servoRotationSpeed = 110;
  else if (softpotReading>500) servoRotationSpeed = 115;
  else if (softpotReading>400) servoRotationSpeed = 120;
  else if (softpotReading>300) servoRotationSpeed = 125;
  else if (softpotReading>200) servoRotationSpeed = 130;
  else if (softpotReading>100) servoRotationSpeed = 135;
  else if (softpotReading>1) servoRotationSpeed = 140;

}

