#include <Stepper.h> // loading Stepper Libary ----> includes Microsteps
const int endstop = 53;
const int endstop2 = 52;
const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution for stepper
Stepper myStepper=Stepper(stepsPerRevolution, 40, 42, 44, 46); // initialization of the stepper Library on pins 8,9,10,11
void setup() 
{
Serial.begin(9600);
pinMode(endstop, INPUT_PULLUP);
pinMode(endstop2, INPUT_PULLUP);  
}
void loop() 
{
while (digitalRead(endstop)== LOW) // Upstairs // Downstairs22
{myStepper.setSpeed(7000);     // set the speed at 60 rpm:     
  myStepper.step(stepsPerRevolution);
  Serial.println("down");
}
while (digitalRead(endstop2)== LOW)// Upstairs // Downstairs22
{
  myStepper.setSpeed(7000);     // set the speed at 60 rpm:     
  myStepper.step(-stepsPerRevolution);
  Serial.println("up");
}
}
