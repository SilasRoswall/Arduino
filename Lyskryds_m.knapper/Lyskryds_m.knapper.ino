int redPin = 13;
int yellowPin = 8;
int greenPin = 2;
int delayVal = 1000;
const int redButton = 4;
const int greenButton = 7;

int redButtonState = 0;
int greenButtonState = 0;

void setup(){
  pinMode(redPin, OUTPUT); 
  pinMode(yellowPin, OUTPUT); 
  pinMode(greenPin, OUTPUT); 
  pinMode(redButton, INPUT);
  pinMode(greenButton, INPUT);
  digitalWrite(redPin, HIGH);
}

void loop(){
  
  redButtonState = digitalRead(redButton);
  greenButtonState = digitalRead(greenButton);
  
  if (redButtonState == HIGH) {     
    toRed();
  }
  if (greenButtonState == HIGH) {
    toGreen();
  }else{}
  
}

void toGreen(){
  //digitalWrite(redPin, HIGH); 
  //delay(delayVal*2);
  digitalWrite(yellowPin, HIGH); 
  delay(delayVal*1.5);
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, HIGH); 
}

void toRed(){
  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, HIGH);
  delay(delayVal*1.5);
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, HIGH);
}
