/*

 */

// constants won't change. They're used here to 
// set pin numbers:
const int button_0 = 2;     // the number of the pushbutton pin
const int button_1 = A0;     // the number of the pushbutton pin
const int button_2 = A1;     // the number of the pushbutton pin
const int button_3 = A2;     // the number of the pushbutton pin
const int button_4 = A3;     // the number of the pushbutton pin
const int button_5 = A4;     // the number of the pushbutton pin
const int button_6 = A5;     // the number of the pushbutton pin
const int button_7 = 8;     // the number of the pushbutton pin
const int button_8 = 7;     // the number of the pushbutton pin

const int led_0 =  13;      // the number of the LED pin
const int led_1 =  12;      // the number of the LED pin
const int led_2 =  11;      // the number of the LED pin
const int led_3 =  10;      // the number of the LED pin
const int led_4 =  9;      // the number of the LED pin
const int led_5 =  6;      // the number of the LED pin
const int led_6 =  5;      // the number of the LED pin
const int led_7 =  4;      // the number of the LED pin
const int led_8 =  3;      // the number of the LED pin

// variables will change:
int buttonState_0 = 0;         // variable for reading the pushbutton status
int buttonState_1 = 0;         // variable for reading the pushbutton status
int buttonState_2 = 0;         // variable for reading the pushbutton status
int buttonState_3 = 0;         // variable for reading the pushbutton status
int buttonState_4 = 0;         // variable for reading the pushbutton status
int buttonState_5 = 0;         // variable for reading the pushbutton status
int buttonState_6 = 0;         // variable for reading the pushbutton status
int buttonState_7 = 0;         // variable for reading the pushbutton status
int buttonState_8 = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(led_0, OUTPUT);      
  pinMode(led_1, OUTPUT);      
  pinMode(led_2, OUTPUT);      
  pinMode(led_3, OUTPUT);      
  pinMode(led_4, OUTPUT);      
  pinMode(led_5, OUTPUT);      
  pinMode(led_6, OUTPUT);      
  pinMode(led_7, OUTPUT);      
  pinMode(led_8, OUTPUT);       
  // initialize the pushbutton pin as an input:
  pinMode(button_0, INPUT);     
  pinMode(button_1, INPUT);     
  pinMode(button_2, INPUT);     
  pinMode(button_3, INPUT);     
  pinMode(button_4, INPUT);     
  pinMode(button_5, INPUT);     
  pinMode(button_6, INPUT);     
  pinMode(button_7, INPUT);     
  pinMode(button_8, INPUT);     
}

void loop(){
  // read the state of the pushbutton value:
  buttonState_0 = digitalRead(button_0);
  buttonState_1 = digitalRead(button_1);
  buttonState_2 = digitalRead(button_2);
  buttonState_3 = digitalRead(button_3);
  buttonState_4 = digitalRead(button_4);
  buttonState_5 = digitalRead(button_5);
  buttonState_6 = digitalRead(button_6);
  buttonState_7 = digitalRead(button_7);
  buttonState_8 = digitalRead(button_8);

  // All buttons on shield are inverted!
  // LOW means it is being pressed
  if (buttonState_0 == LOW)
  {
    buttonState_1 = LOW;
    buttonState_2 = LOW;
    buttonState_3 = LOW;
    buttonState_4 = LOW;
    buttonState_5 = LOW;
    buttonState_6 = LOW;
    buttonState_7 = LOW;
    buttonState_8 = LOW;
  }

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState_1 == LOW)  
  {
    digitalWrite(led_1, HIGH);  
  }
  else
  {
    digitalWrite(led_1, LOW); 
  }
  
  if (buttonState_2 == LOW)
    digitalWrite(led_2, HIGH);  
  else
    digitalWrite(led_2, LOW); 
    
  if (buttonState_3 == LOW)   digitalWrite(led_3, HIGH);  
  else                         digitalWrite(led_3, LOW); 
  if (buttonState_4 == LOW)   digitalWrite(led_4, HIGH);  
  else                         digitalWrite(led_4, LOW); 
  if (buttonState_5 == LOW)   digitalWrite(led_5, HIGH);  
  else                         digitalWrite(led_5, LOW); 
  if (buttonState_6 == LOW)   digitalWrite(led_6, HIGH);  
  else                         digitalWrite(led_6, LOW); 
  if (buttonState_7 == LOW)   digitalWrite(led_7, HIGH);  
  else                         digitalWrite(led_7, LOW); 
  if (buttonState_8 == LOW)   digitalWrite(led_8, HIGH);  
  else                         digitalWrite(led_8, LOW); 
  
  // blink led 0
  digitalWrite(led_0,  !digitalRead(led_0));
  delay(100);
}
