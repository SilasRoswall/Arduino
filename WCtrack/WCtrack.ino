int but1 = 2;
int but2 = 4;
int red1 = 10;
int red2 = 6;
int green1 = 5;
int green2 = 3;
int blue1 = 7;
int blue2 = 8;

enum states{
  FRI,
  TIL_OPTAGET,
  OPTAGET,
  O2S,
  STINKY
};

states t1State;
states t2State;

unsigned long t1LockTime;
unsigned long t1CoolTime;
unsigned long t2LockTime;
unsigned long t2CoolTime;
// 1 min = 60000 milliseconds

//time before activating the stink alert
unsigned long stinkTime = 180000;
//time before the stink wears off
unsigned long coolTime = 300000;

void setup(){

pinMode(red1, OUTPUT);
pinMode(red2, OUTPUT);
pinMode(green1, OUTPUT);
pinMode(green2, OUTPUT);
pinMode(blue1, OUTPUT);
pinMode(blue2, OUTPUT);
pinMode(but1, INPUT_PULLUP);
pinMode(but2, INPUT_PULLUP);



}

void loop(){
  //First toilet
  switch(t1State){
    case FRI:
      digitalWrite(red1, LOW);
      analogWrite(green1, 255);
      if(digitalRead(but1) == LOW){
        t1State = TIL_OPTAGET;
      }
      break;
      
    case TIL_OPTAGET:
      t1LockTime = millis();
      t1State = OPTAGET;
      break;
      
    case OPTAGET:
      analogWrite(red1, 255);
      digitalWrite(green1, 0);
      if(digitalRead(but1) == HIGH){
        if(millis() - t1LockTime > stinkTime){
          t1State = O2S;
        }else{
          t1State = FRI;
        }
      }
      break;
      
    case O2S:
      t1CoolTime = millis();
      t1State = STINKY;
      break;
      
    case STINKY:
      if(digitalRead(but1) == LOW) t1State = OPTAGET;
      
      else if(millis() - t1CoolTime <= coolTime){
        analogWrite(red1, 255);
        analogWrite(green1, 100);
      } else {
        t1State = FRI;
      }
      break;
    
    
  }
  //Second toilet
  switch(t2State){
    case FRI:
      digitalWrite(red2, LOW);
      analogWrite(green2, 255);
      if(digitalRead(but2) == LOW){
        t2State = TIL_OPTAGET;
      }
      break;
      
    case TIL_OPTAGET:
      t2LockTime = millis();
      t2State = OPTAGET;
      break;
      
    case OPTAGET:
      analogWrite(red2, 255);
      digitalWrite(green2, 0);
      if(digitalRead(but2) == HIGH){
        if(millis() - t2LockTime > stinkTime){
          t2State = O2S;
        }else{
          t2State = FRI;
        }
      }
      break;
      
    case O2S:
      t2CoolTime = millis();
      t2State = STINKY;
      break;
      
    case STINKY:
      if(digitalRead(but2) == LOW) t2State = TIL_OPTAGET;
      else if(millis() - t2CoolTime <= coolTime){
        analogWrite(red2, 255);
        analogWrite(green2, 100);
      } else {
        t2State = FRI;
      }
      break;
    
    
  }
  
}
