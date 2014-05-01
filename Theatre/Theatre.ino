/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led1 = 10;
int led2 = 9;
int led3 = 8;
int led4 = 7;
int led5 = 6;
int led6 = 5;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led1, OUTPUT);     
  pinMode(led2, OUTPUT);     
  pinMode(led3, OUTPUT);     
  pinMode(led4, OUTPUT);     
  pinMode(led5, OUTPUT);     
  pinMode(led6, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {

  for(int p = 1; p <= 255; p++)
  {
    for(int i = 5; i < 11; i++)
      analogWrite(i, p);
    delay(25);         
  }
  delay(800);         

  for(int l = 1; l < 6; l++)
  {
    for(int i = 5; i < 11; i++)
        digitalWrite(i, LOW);
    delay(200);         
    
    for(int i = 5; i < 11; i++)
        digitalWrite(i, HIGH);
        
    delay(200);         
  }
   
  for(int l = 1; l < 8; l++)
  {
    for(int j = 5; j < 11; j++)
    {
      delay(100);         
      for(int i = 5; i < 11; i++)
        digitalWrite(i, LOW);
      digitalWrite(j, HIGH);
    }
  } 

  for(int l = 1; l < 8; l++)
  {
      for(int i = 5; i < 11; i++)
        digitalWrite(i, LOW);

    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    delay(100);         
    digitalWrite(led2, HIGH);
    digitalWrite(led5, HIGH);
    delay(100);         
    digitalWrite(led1, HIGH);
    digitalWrite(led6, HIGH);
    delay(100);         
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    delay(100);         
    digitalWrite(led2, LOW);
    digitalWrite(led5, LOW);
    delay(100);         
    digitalWrite(led1, LOW);
    digitalWrite(led6, LOW);
    
  } 
  delay(500);         
  
  for(int l = 1; l < 8; l++)
  {
  for(int p = 1; p <= 255; p++)
  {
    for(int i = 5; i < 11; i++)
      analogWrite(i, p);
    delay(1);         
  }
  delay(100);         
  for(int p = 255; p >= 0; p--)
  {
    for(int i = 5; i < 11; i++)
      analogWrite(i, p);
    delay(1);         
  }
  delay(100);         
  }

 }
