
#include <Stepper.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

int stepCount = 0;   

void setup(){
             Serial.begin(9600);            
}
void loop(){
  if(Serial.available())
  {
    p=Serial.read();
    if(p=='a')
    {
       myStepper.step(1);
       Serial.write(p);
    }
  }
}
