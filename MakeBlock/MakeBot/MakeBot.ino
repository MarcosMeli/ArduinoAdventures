/*************************************************************************
* File Name          : TestSlaveBluetoothBySoftSerial.ino
* Author             : Steve
* Updated            : Evan
* Version            : V1.0.1
* Date               : 5/17/2013
* Description        : Example for Makeblock Electronic modules of Me -
                       Bluetooth. The module can only be connected to the
                       port 3, 4, 5, 6 of Me - Base Shield.
* License            : CC-BY-SA 3.0
* Copyright (C) 2013 Maker Works Technology Co., Ltd. All right reserved.
* http://www.makeblock.cc/
**************************************************************************/
#include <Makeblock.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

/*
Blue module can only be connected to port 3, 4, 5, 6 of base shield.
*/
MeBluetooth bluetooth(PORT_4);
MeDCMotor MotorL(M1);
MeDCMotor MotorR(M2);
MeServo servoDriver1(PORT_2,DEV1);

int moveSpeed = 190;
boolean leftflag, rightflag;
int minSpeed = 55;
int factor = 23;


void setup()
{
//  Serial.begin(9600);
  bluetooth.begin(9600);
  //Serial.println("Bluetooth Start!");
  servoDriver1.begin();
}
int pos1 = 80;

void loop()
{
  char inDat;
  char outDat;
  servoDriver1.write(pos1);
  
  if (bluetooth.available())
  {
    inDat = bluetooth.read();

    if (inDat == 'X')
    {
      pos1 -= 3;
    }
    else if (inDat == 'C')
    {
      pos1 += 3;
    }
    else if (inDat == 'U')
    {
      Forward();
      delay(40);
    }
    else if (inDat == 'D')
    {
      Backward();
      delay(40);
    } else if (inDat == 'L')
    {
      TurnLeft();
      delay(40);
    }else if (inDat == 'R')
    {
      TurnRight();
      delay(40);
    }
    else 
    {
      Stop();
    }
  }
  //Stop();
}

void Stop()
{
  MotorL.run(0);
  MotorR.run(0);
}

void Forward()
{
  MotorL.run(moveSpeed);
  MotorR.run(moveSpeed);
}
void Backward()
{
  MotorL.run(-moveSpeed);
  MotorR.run(-moveSpeed);
}
void TurnLeft()
{
  MotorL.run(-moveSpeed);
  MotorR.run(moveSpeed);
}
void TurnRight()
{
  MotorL.run(moveSpeed);
  MotorR.run(-moveSpeed);
}

