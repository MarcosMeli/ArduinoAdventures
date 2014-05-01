

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int ledOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
boolean DEBUG = true;
int DELAY = 100;

void setup() {
  // initialize serial communications at 9600 bps:
  if (DEBUG)
    Serial.begin(9600); 
    
    if (DEBUG)
      DELAY = 100;
}

int minAudio = 0;
int maxAudio = 70;
int outCount = 0;
int outCount2 = 0;

void loop() {
  // read the analog in value:
  sensorValue = 1024 - analogRead(analogInPin);            
  
 
  if (sensorValue < minAudio)
  {
      minAudio = sensorValue;
  }
      
  if (sensorValue > maxAudio)
  {
      maxAudio = sensorValue;
  }
        
  // map it to the range of the analog out:
  outputValue = constrain(map(sensorValue, minAudio, maxAudio, 0, 255), 0, 255);  
  
  // change the analog out value:
//  analogWrite(analogOutPin, outputValue);           

  // print the results to the serial monitor:
  if (DEBUG)
  {
  Serial.print("sensor = " );                       
  Serial.print(sensorValue);      
  Serial.print("\t output = ");      
  Serial.print(outputValue);   
  Serial.print("\t min = ");      
  Serial.print(minAudio);   
  Serial.print("\t max = ");      
  Serial.println(maxAudio);   
  }
  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(DELAY);                     
}
