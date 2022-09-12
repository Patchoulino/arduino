/*********
  Para programar esta porquería se debe de resettear como si
  fuera un pinguino, justo cuando marque el IDE "uploading" 
  se debe conectar la alimentación
  FLASH SIZE 1M
  
*********/

//int pin = 2;

void setup() {
  // initialize GPIO 2 as an output.
  //pinMode(pin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT); 
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
  delay(1000);               // wait for a second
  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(1000);  
}
