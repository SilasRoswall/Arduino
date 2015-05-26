/*
WCtrack.ino
An arduino sketch that runs on an arduino pro micro board.
The system monitors the locks of 2 bathroom stalls in the Chomsky building at AU, and indicates the status of each stall using 2 RGB LEDs:
Green is available
Red is occupied
Yellow is stinky <- which is activated if a stall is locked for more than 'timeToStink' milliseconds (180000 = 3 minutes)
Stinky stalls time out to available stalls after 'timeToClear' milliseconds (300000 = 6 minutes)

The ardunino reads the stall states from buttons mounted in the door frames. The buttons are pressed when the doors are locked.

Transitions based on button inputs are handled by a switch/case based statemachine. One statemachine per stall.

Feel free to copy this code, suggestions for improvements are welcomed!

~418
*/

#define debounceDelayMs 50

//button mappings:
int stall1 = 2;
int stall2 = 4;

//RGB LED mappings:
int red1 = 10; //PWM
int green1 = 5; //PWM
int blue1 = 7;

int red2 = 6; //PWM
int green2 = 3; //PWM
int blue2 = 8;

//An enum to store the different states of the stalls, transitional states are used to store timer values for the stinky state calculations
enum toiletStates{
  FRI,
  TIL_OPTAGET,
  OPTAGET,
  TIL_STINKY,
  STINKY
};

//one instance for each stall:
toiletStates t1State;
toiletStates t2State;


unsigned long t1LockTime;
unsigned long t1StinkTime;
unsigned long t2LockTime;
unsigned long t2StinkTime;

// 1 min = 60000 milliseconds
unsigned long timeToStink = 180000; //time before activating the stink alert
unsigned long timeToClear = 300000; //time before the stink wears off

void setup(){

//I/O setup:
pinMode(red1, OUTPUT);
pinMode(red2, OUTPUT);
pinMode(green1, OUTPUT);
pinMode(green2, OUTPUT);
pinMode(blue1, OUTPUT);
pinMode(blue2, OUTPUT);
//The buttons connect the inputs to ground, so internal pull-up resistors can be used:
pinMode(stall1, INPUT_PULLUP);
pinMode(stall2, INPUT_PULLUP);
}


void loop(){

  delay(debounceDelayMs);
  //First toilet
  switch(t1State){
	case FRI:
			digitalWrite(red1, LOW);
			digitalWrite(green1, HIGH);
			if(digitalRead(stall1) == LOW) t1State = TIL_OPTAGET; //if stall is locked
			break;

	case TIL_OPTAGET:
			t1LockTime = millis(); //store current time
			t1State = OPTAGET;
			break;

	case OPTAGET:
			digitalWrite(red1, HIGH);
			digitalWrite(green1, 0);
			if(digitalRead(stall1) == HIGH){ //if stall is unlocked
				if(millis() - t1LockTime > timeToStink) t1State = TIL_STINKY; //if more than timeToStink time has passed since the door was locked.
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
			if(digitalRead(stall1) == LOW) t1State = TIL_OPTAGET; //if stall is locked.
			else if(millis() - t1StinkTime > timeToClear) t1State = FRI; //if more than timeToClear has passes since entering STINKY state
			break;
	}
  switch(t2State){
	case FRI:
			digitalWrite(red2, LOW);
			digitalWrite(green2, HIGH);
			if(digitalRead(stall2) == LOW) t2State = TIL_OPTAGET;
			break;

	case TIL_OPTAGET:
			t2LockTime = millis();
			t2State = OPTAGET;
			break;

	case OPTAGET:
			digitalWrite(red2, HIGH);
			digitalWrite(green2, 0);
			if(digitalRead(stall2) == HIGH){
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
			if(digitalRead(stall2) == LOW) t2State = TIL_OPTAGET;
			else if(millis() - t2StinkTime > timeToClear) t2State = FRI;
			break;
	}
}
