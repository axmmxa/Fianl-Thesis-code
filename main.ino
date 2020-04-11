#include <Stepper.h> // loading Stepper Libary ----> includes Microsteps

const int s0 = 7; // int for the GY-31 Sensor
const int s1 = 6;
const int s2 = 5;
const int s3 = 4;
const int out = 3;

const int greenpin = 22;
const int redpin = 23;
const int resetpin = 26;

const int endstop = 13;    //stop button down
const int endstop2 = 12;   //stop button up 

const int RelaiPin = 52;  // int for RelaiPin 

//////////Stepper Settings 

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution for stepper
                                      
Stepper myStepper=Stepper(stepsPerRevolution, 40, 42, 44, 46); // initialization of the stepper Library on pins 8,9,10,11

                                     
void color(); // starting the color function which is defined at the end of the page 

int diff_n=1200;   //negative difference to color of initialization
int diff_p=1200;   //positive difference to color of initialization

long red=0;
long blue=0;
long green=0;

boolean ini=true;

int i=0, k=0, n=0, m=0;

int Rini[20];
int Gini[20];
int Bini[20];

long Rmvi=0, Gmvi=0, Bmvi=0;
void setup() 
{
   Serial.begin(9600);
   pinMode(s0, OUTPUT); // Pins for the GY-31 Sensor
   pinMode(s1, OUTPUT);
   pinMode(s2, OUTPUT);
   pinMode(s3, OUTPUT);
   pinMode(out, INPUT);

  pinMode(RelaiPin, OUTPUT); 

  pinMode(greenpin, INPUT_PULLUP);
  pinMode(redpin, INPUT_PULLUP);
  pinMode(resetpin, INPUT_PULLUP);

  pinMode(endstop, INPUT_PULLUP);
  pinMode(endstop2, INPUT_PULLUP);
  
  digitalWrite(s0, LOW);  // Settings for the frequency
  digitalWrite(s1, HIGH);
  digitalWrite(RelaiPin, LOW); 

  myStepper.setSpeed(150);     // set the speed at 60 rpm: 
  }
void loop() 
{
  if (digitalRead(greenpin)==HIGH)
  {
   digitalWrite(RelaiPin, HIGH)
     while (digitalRead(redpin) == LOW)
    { 
       digitalWrite(RelaiPin, HIGH); // Put the Relai Pin low, which is controlling the         conveyer-motor 

       if (digitalRead(endstop) == HIGH)
       { 
         digitalWrite(RelaiPin, LOW);
       }

       if (digitalRead(resetpin) == HIGH)
       { 
          digitalWrite(RelaiPin, LOW);
 while ( digitalRead(endstop2) == LOW)
                {
                  Serial.println("up // down ");    // change the direction of the motor
                  myStepper.step(-stepsPerRevolution);
                }
       }
   }
if (ini==true)

      {  
          delay(300);

          for (i = 0; i<20; i++) ///starting the initalization of the color from the belt
           {
             color(); 
             Rini[i]=red;
             Gini[i]=green;
             Bini[i]=blue;
           }

          for(k = 0; k<20; k++) 
           {
            Rmvi=Rmvi+Rini[k];
            Gmvi=Gmvi+Gini[k];
            Bmvi=Bmvi+Bini[k];
           }

            Rmvi=Rmvi/20;
            Gmvi=Gmvi/20;
            Bmvi=Bmvi/20;

          Serial.println("Redmiddle");
          Serial.println(Rmvi);
          Serial.println("Greenmiddle");
          Serial.println(Gmvi);
          Serial.println("Bluemiddle");
          Serial.println(Bmvi);
 
          ini=false;
  
      }         //End of the Initalization of the colour from the belt
//Compare the new color with the values of the initalization
 color();1
    if (red<Rmvi-diff_n || green<Gmvi-diff_n || blue<Bmvi-diff_n || red>Rmvi+diff_n || green>Gmvi+diff_n || blue>Bmvi+diff_n)
      { 
      color();
  if (red<Rmvi-diff_n || green<Gmvi-diff_n || blue<Bmvi-diff_n ||   red>Rmvi+diff_n || green>Gmvi+diff_n || blue>Bmvi+diff_n)
          { 
           color();
            if (red<Rmvi-diff_n || green<Gmvi-diff_n || blue<Bmvi-diff_n ||     red>Rmvi+diff_n || green>Gmvi+diff_n || blue>Bmvi+diff_n)
              { 
n++;
   Serial.println("part detacted");
              myStepper.step(stepsPerRevolution);
             }
           }
         }
while (red<Rmvi-diff_n || green<Gmvi-diff_n || blue<Bmvi-diff_n || red>Rmvi+diff_n || green>Gmvi+diff_n || blue>Bmvi+diff_n)
      { 
      color(); 
      Serial.println("while");
      }
Serial.println(n);
      Serial.println("rojo");
      Serial.println(red, DEC);
  
      Serial.println("verde");
      Serial.println(green);
      Serial.println("azul");
      Serial.println(blue);
     }
   else
   {   
    digitalWrite(RelaiPin, HIGH);
   }

}
/////////////////////color() function to read out and save the RGB-Values//////////////////////////
void color()  
{    
  digitalWrite(s2, LOW);  
  digitalWrite(s3, LOW);  
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s3, HIGH);  
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s2, HIGH);  
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
}
