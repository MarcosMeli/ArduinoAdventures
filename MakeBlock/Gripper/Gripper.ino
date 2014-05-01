#include <Makeblock.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

MeDCMotor Motor1(M1);  
MeJoystick joystick(PORT_3);

int x = 0;      // a variable for the Joystick's x value
int y = 0;      // a variable for the Joystick's y value

void setup() 
{
}

void loop()
{
   x = joystick.readX();  
   y = joystick.readY(); 

   Motor1.run(y);
   delay(10);
}

