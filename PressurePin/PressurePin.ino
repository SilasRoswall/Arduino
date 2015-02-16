int redPin = 13;
int yellowPin = 8;
int greenPin = 2;
int delayVal = 1000;

int pressPin = 0;                      //pressure sensor to Arduino A0
int initReading;                       //variable for the initial reading,
int reading;                           //variable for storing current pressure
boolean startUp;



void setup(){
  pinMode(redPin, OUTPUT); 
  pinMode(yellowPin, OUTPUT); 
  pinMode(greenPin, OUTPUT); 
  digitalWrite(redPin, HIGH);
	
initReading = 0;                    		//Initialize initReading.
reading = analogRead(pressPin); 		//Reading equals the value,
						//returned by the sensor.
startUp = true;                        		//Initialize the calibration switch to ‘on’
}	

	
void loop(){
calibrate();                                  	//calls the function defined below

reading = analogRead(pressPin); 		//Reading equals the value,
//from the sensor
	if(reading < initReading*.9){          	//If reading is less than 90%,
     		toGreen();			//of the initial sensor value,                                        											
		}else{
		toRed();}
}

void calibrate()                          //The first thing to do in the loop,
{
if(startUp == true)                      //if the calibration switch is on (which it is),
{
initReading = reading;                //set initReading equal to the sensor
//value.
startUp = false;                         //And shut of the calibration switch.
}
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
