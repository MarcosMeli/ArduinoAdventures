// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
Servo myservo2;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
    myservo2.attach(10);  // attaches the servo on pin 9 to the servo object 
} 
 
 
 int pos1 = 10;
 int pos2 = 10;
 
void loop() 
{ 
  int pX = analogRead(0);
  int pY = analogRead(1);
  
  if (abs(pX - 512) > 35)
    pos1 = pos1 + (pX - 511) * (3.0/512.0);
  if (abs(pY - 512) > 35)
    pos2 = pos2 + (pY - 511) * (3.0/512.0);
  
  pos1 = constrain(pos1, 10,160);
  pos2 = constrain(pos2, 10,160);

  myservo.write(pos1);              // tell servo to go to position in variable 'pos' 
  myservo2.write(pos2);              // tell servo to go to position in variable 'pos' 

  delay(20);
} 
