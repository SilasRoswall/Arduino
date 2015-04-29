int but1 = 2;
int but2 = 4;
int red1 = 10;
int red2 = 6;
int green1 = 5;
int green2 = 3;
int blue1 = 7;
int blue2 = 8;

enum toiletStates{
  FRI,
  TIL_OPTAGET,
  OPTAGET,
  TIL_STINKY,
  STINKY
};

toiletStates t1State;
tolietStates t2State;

unsigned long t1LockTime;
unsigned long t1StinkTime;
unsigned long t2LockTime;
unsigned long t2StinkTime;
// 1 min = 60000 milliseconds

//time before activating the stink alert
unsigned long timeToStink = 5000;//180000;
//time before the stink wears off
unsigned long timeToClear = 5000;//300000;

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
			digitalWrite(green1, HIGH);
			if(digitalRead(but1) == LOW) t1State = TIL_OPTAGET;
			break;

	case TIL_OPTAGET:
			t1LockTime = millis();
			t1State = OPTAGET;
			break;

	case OPTAGET:
			digitalWrite(red1, HIGH);
			digitalWrite(green1, 0);
			if(digitalRead(but1) == HIGH){
				if(millis() - t1LockTime > timeToStink) t1State = TIL_STINKY;
				else t1State = FRI;
				}
			break;

	case TIL_STINKY:
			t1StinkTime = millis();
			t1State = STINKY;
			break;

	case STINKY:
			digitalWrite(red1, HIGH);
			analogWrite(green1, 100);
			else if(millis() - t1StinkTime > timeToClear) t1State = FRI;
			if(digitalRead(but1) == LOW) t1State = TIL_OPTAGET;
			break;

  switch(t2State){
	case FRI:
			digitalWrite(red2, LOW);
			digitalWrite(green2, HIGH);
			if(digitalRead(but2) == LOW) t2State = TIL_OPTAGET;
			break;

	case TIL_OPTAGET:
			t2LockTime = millis();
			t2State = OPTAGET;
			break;

	case OPTAGET:
			digitalWrite(red2, HIGH);
			digitalWrite(green2, 0);
			if(digitalRead(but2) == HIGH){
				if(millis() - t2LockTime > timeToStink) t2State = TIL_STINKY;
				else t2State = FRI;
				}
			break;

	case TIL_STINKY:
			t2StinkTime = millis();
			t2State = STINKY;
			break;

	case STINKY:
			digitalWrite(red2, HIGH);
			analogWrite(green2, 100);
			else if(millis() - t2StinkTime > timeToClear) t2State = FRI;
			if(digitalRead(but2) == LOW) t2State = TIL_OPTAGET;
			break;
}