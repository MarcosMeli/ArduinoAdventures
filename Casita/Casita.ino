#include <IRremote.h>

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;
int mainLed = 13;
int speakerPin = 4;

int ledFloor3 = 10;
int ledFloor3Value = 255;
int ledFloor3Status = 0;
int ledFloor2 = 9;
int ledFloor2Value = 255;
int ledFloor2Status = 0;
int ledFloor1 = 6;
int ledFloor1Value = 255;
int ledFloor1Status = 0;

/*************************************************
 * Public Constants
 *************************************************/
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_C4_1 260
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

int melody[] = {
   NOTE_C4_1,NOTE_C4, NOTE_D4, NOTE_C4,NOTE_F4,NOTE_E4,
   NOTE_C4_1,NOTE_C4,NOTE_D4,NOTE_C4,NOTE_G4,NOTE_F4,
   NOTE_C4_1,NOTE_C4,NOTE_C5,NOTE_A4,NOTE_F4,NOTE_E4,NOTE_D4,
   NOTE_AS4,NOTE_AS4,NOTE_A4,NOTE_F4,NOTE_G4,NOTE_F4};

int noteDurations[] = {
  6, 6, 3, 3,3,3,
  6, 6, 3, 3,3,3,
  6, 6, 3, 3,3,3,3, 
  6, 6, 3, 3,3,3 };

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(mainLed, OUTPUT);     
  pinMode(ledFloor1, OUTPUT);     
  pinMode(ledFloor2, OUTPUT);     
  pinMode(ledFloor3, OUTPUT);     

  analogWrite(ledFloor1, 255);
  analogWrite(ledFloor2, 255);
  analogWrite(ledFloor3, 255);
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    ProcessCommand(results);
    irrecv.resume(); // Receive the next value
  }
  
  ledFloor1Value += ledFloor1Status;
  ledFloor2Value += ledFloor2Status;
  ledFloor3Value += ledFloor3Status;
  
  if (ledFloor1Value == 0 ||
      ledFloor1Value == 255)
      ledFloor1Status = 0;

  if (ledFloor2Value == 0 ||
      ledFloor2Value == 255)
      ledFloor2Status = 0;
      
  if (ledFloor3Value == 0 ||
      ledFloor3Value == 255)
      ledFloor3Status = 0;
      
  analogWrite(ledFloor1, ledFloor1Value);
  analogWrite(ledFloor2, ledFloor2Value);
  analogWrite(ledFloor3, ledFloor3Value);

  delay(4
  .
  );
}

bool onStatus = false;

void ProcessCommand(decode_results results)
{

  if (results.value == 0xFFA25D)
  {
    onStatus = !onStatus;
    
    // ON OFF
    if (onStatus)
    {
      digitalWrite(mainLed, HIGH);
      ledFloor1Status = -1; 
      ledFloor2Status = -1; 
      ledFloor3Status = -1; 
    }
    else
    {
        ledFloor1Status = 1; 
        ledFloor2Status = 1; 
        ledFloor3Status = 1; 
        digitalWrite(mainLed, LOW);
    }
  }

  if (onStatus == false)
      return;


  if (results.value == 0xFF30CF)
  {
    if (ledFloor1Value > 0)
       ledFloor1Status = -1;
    else
       ledFloor1Status = 1;
  }
  
  if (results.value == 0xFF18E7)
  {
    if (ledFloor2Value > 0)
       ledFloor2Status = -1;
    else
       ledFloor2Status = 1;
  }

  if (results.value == 0xFF7A85)
  {
    if (ledFloor3Value > 0)
       ledFloor3Status = -1;
    else
       ledFloor3Status = 1;
  }

 if (results.value == 0xFFE21D)
 {
   playMelody();
 }
 
 

  if (results.value == 0xFF6897)
  {
     if (ledFloor1Value == 0 &&
     ledFloor2Value == 0 &&
     ledFloor3Value == 0)
     {
       ledFloor1Status = 1;
       ledFloor2Status = 1;
       ledFloor3Status = 1;
     }
     else
     {
       ledFloor1Status = -1;
       ledFloor2Status = -1;
       ledFloor3Status = -1;
     }

  }

}

void SlowTurnOn(int ledPin)
{
   for(int i = 1; i < 250; i++)
   {
      analogWrite(ledPin, i);
      delay(4);
   }
}

void SlowTurnOff(int ledPin)
{
   for(int i = 250; i >= 0; i--)
   {
      analogWrite(ledPin, i);
      delay(4);
   }
}

void playMelody() 
{
  for (int thisNote = 0; thisNote < 26; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    //tone(speakerPin, melody[thisNote],noteDuration);

    int pauseBetweenNotes = noteDuration + 50;      //delay between pulse
    delay(pauseBetweenNotes);
    
//    noTone(speakerPin);                // stop the tone playing
  }
}
