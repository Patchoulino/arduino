/*
  Simple example for receiving
  
  http://code.google.com/p/rc-switch/
*/
const int LED = 13;
int temp;

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Receiver on inerrupt 0 => that is pin #2
}

void loop() {
  if (mySwitch.available()) {
    
    int value = mySwitch.getReceivedValue();
    
    if (value == 0) {
      Serial.print("Unknown encoding");
    } else {
      int x = mySwitch.getReceivedValue();

      if(x != temp)
      {
        temp = x;
        
        Serial.print("Received: ");
        Serial.write(x);  //letter
        Serial.print("|");
        Serial.print(x);  //DEC
        Serial.println("");
        
        switch(x)
        {
          case 'E':
            digitalWrite(LED, HIGH);
            break;
          case 'A':
            digitalWrite(LED, LOW);
            break;
          case 'T':
            if(digitalRead(LED) == HIGH)
            {
              digitalWrite(LED, LOW);
            }
            else
            {
              digitalWrite(LED, HIGH);
            }
            break;
        }
      }
    }
    mySwitch.resetAvailable();
  }
}
