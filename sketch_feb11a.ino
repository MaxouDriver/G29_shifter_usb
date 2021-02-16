#include <Joystick.h>

// Create the Joystick
Joystick_ Joystick;

#define MAX_LEFT_REGION        635
#define MIN_RIGHT_REGION       720

int gear=0;                          // Default value is neutral

void setup() {
   // G29 shifter analog inputs configuration 
  pinMode(A0, INPUT_PULLUP);   // X axis
  pinMode(A2, INPUT_PULLUP);   // Y axis

  pinMode(2, INPUT); 

  // Initialize Joystick Library
  Joystick.begin();
}

void loop() {

  int x=analogRead(0);                 // X axis
  int y=analogRead(2);                 // Y axis

  Serial.println(x);
  Serial.println(y);

  int _tempGear = 0;

    if(x<MAX_LEFT_REGION)                  // Shifter on the left
    {
      if(y>500) _tempGear=1;
      if(y<200) _tempGear=2;
    }
    else if(x>MIN_RIGHT_REGION)             // Shifter on the right
    {
      if(y>600) _tempGear=5;
      if(y<300) _tempGear=6;
     
    }
    else                               // Shifter in the middle
    {
      if(y>540) _tempGear=3;
      if(y<250) _tempGear=4;
    }


  //If the gear has changed, unactivate last gear and activate next one
   if (_tempGear != gear ){
      Joystick.setButton(gear-1, LOW);
      gear = _tempGear;
      Joystick.setButton(gear-1, HIGH);
   }
   delay(50);
}
