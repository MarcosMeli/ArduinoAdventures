#include <Me_ServoDriver.h>
#include <Me_BaseShield.h>
#include <SoftwareSerial.h>
#include <Me_InfraredReceiverDecode.h>
#include <Me_BaseShieldMotorDriver.h>

#include <Servo.h>

Me_BaseShieldMotorDriver baseShieldMotorDriver;// use M1 and M2 ports on BaseShield
Me_InfraredReceiverDecode infraredReceiverDecode(PORT_3);
Me_ServoDriver servoDriver(PORT_1);//can ONLY be PORT_1,PORT_2 

int leftSpeed = 250;
int rightSpeed = 250;

void setup()
{
    Serial.begin(9600);
    baseShieldMotorDriver.begin();
    infraredReceiverDecode.begin();
    servoDriver.beginServo1();
    servoDriver.beginServo2();
    servoDriver.writeServo1(20);
 
}

void loop()
{
    if(infraredReceiverDecode.available())
    {
        switch(infraredReceiverDecode.read())
        {
            case IR_BUTTON_PLUS: 
                 runForward();
                 while(infraredReceiverDecode.buttonState());
                 runStop();
                 break;
            case IR_BUTTON_PREVIOUS: 
                 runLeft();
                 while(infraredReceiverDecode.buttonState());
                 runStop();
                 break;
            case IR_BUTTON_NEXT: 
                 runRight();
                 while(infraredReceiverDecode.buttonState());
                 runStop();
                 break;
            case IR_BUTTON_MINUS: 
                 runBack();
                 while(infraredReceiverDecode.buttonState());
                 runStop();
                 break;
            case IR_BUTTON_2: 
                 while(infraredReceiverDecode.buttonState())
                   servoAdd(1,1);
                 break;
            case IR_BUTTON_8: 
                while(infraredReceiverDecode.buttonState())
                   servoAdd(1,-1);
                  break;
            default:break;
        }
    }
}

void runForward()
{
    Serial.println("run forward");
    baseShieldMotorDriver.runMotors(leftSpeed,rightSpeed);
}
int servo1minpos = 50;
int servo1pos = servo1minpos;
int servo2pos = 25;

void servo1Add(int grads)
{
    servo1pos = servo1pos+grads;
    if (servo1pos > 90)
       servo1pos = 90;
    if (servo1pos < servo1minpos)
       servo1pos = servo1minpos;
      servoDriver.writeServo1(servo1pos);
      delay(40);
}

void servo2Add(int grads)
{
    servo2pos = servo2pos+grads;
    if (servo2pos > 120)
       servo2pos = 120;
    if (servo2pos < 10)
       servo2pos = 10;
      servoDriver.writeServo2(servo2pos);
      delay(40);
}


void runLeft()
{
    Serial.println("run left");
    baseShieldMotorDriver.runMotors(leftSpeed/1.5,-rightSpeed/1.5);
}
void runRight()
{
    Serial.println("run right");
    baseShieldMotorDriver.runMotors(-leftSpeed/1.5,rightSpeed/1.5);
}
void runStop()
{
    Serial.println("run stop");
    baseShieldMotorDriver.stopMotors();
}
void runBack()
{
    Serial.println("run back");
    baseShieldMotorDriver.runMotors(-leftSpeed,-rightSpeed);
}

