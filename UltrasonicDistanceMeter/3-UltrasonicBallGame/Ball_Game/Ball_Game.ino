const int pingTriger = 8;
const int pingEcho = 9;
const int pingRelay = 10;

void setup() {
  Serial.begin(9600);
  pinMode(pingTriger, OUTPUT);
  pinMode(pingRelay, OUTPUT);
  pinMode(pingEcho, INPUT);
}

void loop() {

  float cm = calculateDistanceInCentimeters();  

if (cm < 3 0)
  digitalWrite(pingRelay, HIGH);
else
  digitalWrite(pingRelay, LOW);
  
  delay(100);
}


float calculateDistanceInCentimeters()
{
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(pingTriger, LOW);
  delayMicroseconds(2);
  digitalWrite(pingTriger, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingTriger, LOW);

  long duration = pulseIn(pingEcho, HIGH);
  
  return microsecondsToCentimeters(duration);;
}

float microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds * 1.0/ 29.034 / 2;
}


