//to detect whether a person is dead or alive using xd-58c bpm sensor

//Author: Om Palsanawala
//date: 28 March, 2019
//Assigned by: Prof. Rutu Parekh


//Code shows 0 for not detecting pulse while connected to the finger tip - might be dead!
//Code shows 1 for detecting a pulse while connected to the finger tip - alive!


//  Variables
int PulseSensorPurplePin = 0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int LED13 = 13;   //  The on-board Arduino LED
bool on = false;

int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 550;
int t1, t2, t3;
int i = 1;
int d = 0;
int a = 0;
int j = 1;

// The SetUp Function:
void setup() {
   pinMode(LED13,OUTPUT);         // pin that will blink to your heartbeat!
   Serial.begin(115200);         // Set's up Serial Communication at certain speed.
}

// The Main Loop Function
void loop() {

  Signal = analogRead(PulseSensorPurplePin);  
  if(Signal > Threshold){ 
      Serial.println("disconnected.");
      on = false;
      digitalWrite(LED13,HIGH);
   } else {
     digitalWrite(LED13,LOW);
     if(Signal < 10)
      {
        on = true;
        Serial.println("connecting...");
      }
      if(i%4 == 1)
      {
        t1 = Signal;                                            
      }
      else if(i%4 == 2)
      {
        t2 = Signal;                                            
      }
      else if(i%4 == 3)
      {
        t3 = Signal;                                            
      }
      else if(i%4 == 0)
      {
        int t = max(abs(t1 - t2), abs(t2 - t3));

        if(t > 100 && on)
        {
          Serial.println("disconnected. Please hold properly...");
          on = false;
        }
        
        else if(t < 5 && on)
        {
//          Serial.println(0);
            d++;
        }
        
        else if(on && t > 5 && t < 50)
        {
//          Serial.println(1);
            a++;
        }                                             
      }
   }
   i = (i+1)%4;
   j = (j+1)%150;
   if(j == 0)
   {
    if(a >= d)
    {
      Serial.println("alive!");
    }
    else
    {
      Serial.println("dead!"); 
    }
    a = 0;
    d = 0;
   }
delay(50);
}
