#include <Servo.h> //To include Servo library
 
Servo tracker;  // create servo object to control a servo 
int eastLDRPin = 0;  //Assign analogue pins
int westLDRPin = 1;
int eastLDR = 0;   //Create variables for the east and west sensor values
int westLDR = 0;
int error = 0;
int calibration = 35;  //Calibration offset to set error to zero when both sensors receive an equal amount of light
int trackerPos = 90;    //Create a variable to store the servo position
 
void setup() 
{ 
  tracker.attach(11);  // attaches the servo on pin 11 to the servo object
  tracker.write(90);
  Serial.begin(9600);
}
void loop() 
{ 
  eastLDR = calibration + analogRead(eastLDRPin);    //Read the value of each of the east and west sensors

  westLDR = analogRead(westLDRPin);
  Serial.println(analogRead(A0));
  Serial.println(analogRead(A1));
  if(eastLDR<50 && westLDR<50)  //Check if both sensors detect very little light, night time

  {
    while(trackerPos<=140)  //Move the tracker all the way back to face east for sunrise
    {
      trackerPos++;
      tracker.write(trackerPos);
      delay(100);
    }
  }
  error = eastLDR - westLDR;          //Determine the difference between the two sensors.

  if(error>30)        //If the error is positive and greater than 15 then move the tracker in the east direction

  {
    if(trackerPos<=140)    //Check that the tracker is not at the end of its limit in the east direction

    {
      trackerPos++;
      tracker.write(trackerPos);  //Move the tracker to the east
    }
  }
  else if(error<-30)  //If the error is negative and less than -15 then move the tracker in the west direction

  {
    if(trackerPos>40)  //Check that the tracker is not at the end of its limit in the west direction
    {
      trackerPos--;
      tracker.write(trackerPos);
  //Move the tracker to the west
    }
  }
 if(error<30&&error>-30&&eastLDR>50&&westLDR>50)    //If equal light is falling on the sensors
{
 
tracker.write(90);
  
 }
delay(100);
}
