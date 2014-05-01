
// These constants won't change.  They're used to give names
// to the pins used:

#include <IRremote.h>

int DELAY = 100;
int VARATION = 0;
int DIRECTION = 1;
int MODE = 1;
boolean TurnedOn = true;
int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

int minAudio = 1024;
int maxAudio = 0;
int minCount = 0;
int outCount = 0;
int outCount2 = 0;
int currentLed = 2;
int currentModeIndex = 0;

void loop() {
  // read the analog in value:

  renderCurrentLed();

  moveNextStep();

  readRemoteControl();    

  delay(DELAY);                     
}

void renderCurrentLed()
{
  for(int i = 2; i <= 10;i++)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  
  if (TurnedOn)
    digitalWrite(currentLed, HIGH);
}

int mode1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
int mode2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1};
int mode3[] = {1, 9, 2, 8, 3, 7, 4, 6, 5, 6, 4, 7, 3, 8, 2, 9};
int mode4[] = {1, 3, 2, 4, 3, 5, 4, 6, 5, 7, 6, 8, 7, 9, 8, 1, 9, 2};
int mode5[] = {1, 9, 2, 8, 3, 7, 4, 6, 5, 4, 3, 2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 4, 7, 3, 8, 2, 9};
int mode6[] = {1, 2, 3, 2, 3, 4, 3, 4, 5, 4, 5, 6, 5, 6, 7, 6, 7, 8, 7, 8, 9, 8, 9, 1, 9};


void moveNextStep()
{
  int modeSize = 1;
  
  switch(MODE)
  {
    case 1:
        modeSize = sizeof(mode1)/sizeof(int); break;
    case 2:    
        modeSize = sizeof(mode2)/sizeof(int); break;
    case 3:    
        modeSize = sizeof(mode3)/sizeof(int); break;
    case 4:    
        modeSize = sizeof(mode4)/sizeof(int); break;
    case 5:    
        modeSize = sizeof(mode5)/sizeof(int); break;
    case 6:    
        modeSize = sizeof(mode6)/sizeof(int); break;
  }
  
  currentModeIndex += DIRECTION;
  
  if (currentModeIndex >= modeSize)
      currentModeIndex = 0;
  if (currentModeIndex < 0)
     currentModeIndex = 8;

  switch(MODE)
  {
    case 1:
        currentLed = mode1[currentModeIndex]; break;
    case 2:    
        currentLed = mode2[currentModeIndex]; break;
    case 3:    
        currentLed = mode3[currentModeIndex]; break;
    case 4:    
        currentLed = mode4[currentModeIndex]; break;
    case 5:    
        currentLed = mode5[currentModeIndex]; break;
    case 6:    
        currentLed = mode6[currentModeIndex]; break;
  }
  currentLed += 1;
}

void readRemoteControl()
{
  if (irrecv.decode(&results)) {
    int res = results.value;
    
    Serial.println(results.value, HEX);
    
    if (results.value == 0xFFA857 && DELAY < 2000)
        VARATION = 5;
    else if (results.value == 0xFF906F && DELAY > 8)
        VARATION = -5;
    else if (results.value == 0xFFFFFFFF && DELAY > 8 && DELAY < 2000)
        VARATION = VARATION;
    else
    {
        VARATION = 0;
        if (results.value == 0xFF02FD)
            DIRECTION = 1;
        else if (results.value == 0xFFC23D)
            DIRECTION = -1;
        else if (results.value == 0xFFA25D)
            TurnedOn = !TurnedOn;
        else if (results.value == 0xFF629D)
            MODE = 1 + (MODE) % 6;
            
    }
        
    DELAY += VARATION;
//    Serial.println(results.value);
    irrecv.resume(); // Receive the next value
    
  }
}
