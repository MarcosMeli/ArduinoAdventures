
#include <Makeblock.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

/*
Blue module can only be connected to port 3, 4, 5, 6 of base shield.
*/
MeBluetooth bluetooth(PORT_5);
MeDCMotor MotorL(M1);
MeDCMotor MotorR(M2);
int moveSpeed = 200;


MeDCMotor motorHand(PORT_2);
MeEncoderMotor motor1(0x09, SLOT1);   //  Motor at slot1


// Controller

#define    STX          0x02
#define    ETX          0x03
#define    ledPin       13
#define    SLOW         750                            // Datafields refresh rate (ms)
#define    FAST         250                             // Datafields refresh rate (ms)

byte cmd[8] = {0, 0, 0, 0, 0, 0, 0, 0};                 // bytes received
byte buttonStatus = 0;                                  // first Byte sent to Android device
long previousMillis = 0;                                // will store last time Buttons status was updated
long sendInterval = SLOW;                               // interval between Buttons status transmission (milliseconds)
String displayStatus = "xxxx";                          // message to Android device


void setup()
{
  //Serial.begin(9600);
  bluetooth.begin(9600);
  while (bluetooth.available())  bluetooth.read();        // empty RX buffer
  motor1.begin();

}

void loop()
{
  char inDat;
  char outDat;
  if (bluetooth.available())
  {
    delay(2);
    cmd[0] =  bluetooth.read();
    if (cmd[0] == STX)  {
      int i = 1;
      while (bluetooth.available())  {
        delay(1);
        cmd[i] = bluetooth.read();
        if (cmd[i] > 127 || i > 7)                 break; // Communication error
        if ((cmd[i] == ETX) && (i == 2 || i == 7))   break; // Button or Joystick data
        i++;
      }
      if     (i == 2)          getButtonState(cmd[1]);  // 3 Bytes  ex: < STX "C" ETX >
      else if (i == 7)          getJoystickState(cmd);  // 6 Bytes  ex: < STX "200" "180" ETX >
    }
  }
}


bool WorkingWithHand = false;
bool HalfSpeed = false;

void getButtonState(int bStatus)  {
  switch (bStatus) {
    // -----------------  BUTTON #1  -----------------------
    case 'A':
      WorkingWithHand = true;
      break;
    case 'B':
      WorkingWithHand = false;
      break;
    // -----------------  BUTTON #2  -----------------------
    case 'C':
      HalfSpeed = true;
      break;
    case 'D':
      HalfSpeed = false;
      break;
  }
}

void getJoystickState(byte data[8])    {
  int joyX = (data[1] - 48) * 100 + (data[2] - 48) * 10 + (data[3] - 48); // obtain the Int from the ASCII representation
  int joyY = (data[4] - 48) * 100 + (data[5] - 48) * 10 + (data[6] - 48);
  joyX = joyX - 200;                                                  // Offset to avoid
  joyY = joyY - 200;                                                  // transmitting negative numbers

  if (joyX < -100 || joyX > 100 || joyY < -100 || joyY > 100)     return; // commmunication error

  //Serial.print("Joys:  ");
  //  Serial.print(joyX);
  //Serial.print(", ");
  //Serial.println(joyY);

  if (WorkingWithHand)
  {
    motorHand.run(int(joyX * 2.5));
    motor1.RunSpeed(joyY);
    
    MotorL.run(0);
    MotorR.run(0);
  }
  else
  {
    motorHand.run(0);
    int speedL = int(joyY * 2.2 - joyX * 1.5);
    int speedR = int(joyY * 2.2 + joyX * 1.5);

    if (HalfSpeed)
    {
      speedL = int (speedL * 0.5);
      speedR = int (speedR * 0.5);
    }
    MotorL.run(speedL);
    MotorR.run(speedR);
  }
}

