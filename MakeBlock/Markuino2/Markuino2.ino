int motor1p = 11;
int motor1n = 10;

int motor2p = 6;
int motor2n = 9;

void setup() {
  Serial.begin(9600);

    pinMode(motor1p, OUTPUT);
    pinMode(motor1n, OUTPUT);
    pinMode(motor2p, OUTPUT);
    pinMode(motor2n, OUTPUT);
}

void loop() {
  // normalize to -1 to 1 values
  float valx = (float) analogRead(0);
  float valy = (float) analogRead(1);
  float x = valx / 512.0f - 1.0f;
  float y = valy / 512.0f - 1.0f; 
  float motor1speed = 0;
  float motor2speed = 0;
  
  // neutralzone;
  if (x < .1 && x > -0.1) x = 0;
  if (y < .1 && y > -0.1) y = 0;
  
  // Quadrants

  if (x >= 0 && y >= 0)
  {  // Q1
     motor1speed = max(x, y);
     motor2speed = y - x;
  }
  else if (x <= 0 && y >= 0)
  {  // Q2
     motor1speed = y + x;
     motor2speed = max(-x, y);
  }
  else if (x <= 0 && y <= 0)
  {  // Q3
     motor1speed = min(x, y);
     motor2speed = y - x;
  }
  else if (x >= 0 && y <= 0)
  {  // Q4
     motor1speed = x + y;
     motor2speed = min(-x, y);
  }
  
  Serial.print(motor1speed);
  Serial.print(" . ");
  Serial.println(motor2speed);
  
// delay(200);
// return;
  analogWrite(motor1p, 0);
  analogWrite(motor1n, 0);
  analogWrite(motor2p, 0);
  analogWrite(motor2n, 0);

  if (motor1speed >= 0)
    analogWrite(motor1p, (int) (motor1speed * 250.0f));
  else
    analogWrite(motor1n, (int) (-motor1speed * 250.0f));

  if (motor2speed >= 0)
    analogWrite(motor2p, (int) (motor2speed * 250.0f));
  else
    analogWrite(motor2n, (int) (-motor2speed * 250.0f));
  
  delay(25);
}

