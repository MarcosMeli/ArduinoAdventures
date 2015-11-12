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
int moveSpeed = 200;


MeEncoderMotor motor1(0x09, SLOT1);   //  Motor at slot1
MeDCMotor motorHand(PORT_2);



void setup()
{
  Serial.begin(9600);
  bluetooth.begin(9600);
  motor1.begin();

}

void loop()
{
  char inDat;
  char outDat;
  if (bluetooth.available())
  {
    inDat = bluetooth.read();
      Serial.print(inDat);

    if (inDat == '+') {
              MotorL.stop();
        MotorR.stop();

      while (inDat != '\n')
        inDat = bluetooth.read();
      inDat = bluetooth.read();
    }


    if (inDat >= '0' && inDat <= '9')
    {
      if (inDat == '1')
        Forward(20);
      else if (inDat == '2')
        Backward(20);
      else if (inDat == '3')
        TurnLeft(20);
      else if (inDat == '4')
        TurnRight(20);
      else
      {
        MotorL.stop();
        MotorR.stop();
      }

      if (inDat == '7')
      {
        motorHand.run(250);
      }
      else if (inDat == '8')
      {
        motorHand.run(-250);
      }
      else
        motorHand.stop();


      delay(20);
      
    }
    else
    {
      //Serial.print(inDat);
    }
  }

}


void Forward(int delayMs)
{
  MotorL.run(moveSpeed);
  MotorR.run(moveSpeed);
}
void Backward(int delayMs)
{
  MotorL.run(-moveSpeed);
  MotorR.run(-moveSpeed);
}

void TurnLeft(int delayMs)
{
  MotorL.run(-moveSpeed);
  MotorR.run(moveSpeed);
}
void TurnRight(int delayMs)
{
  MotorL.run(moveSpeed);
  MotorR.run(-moveSpeed);
}

