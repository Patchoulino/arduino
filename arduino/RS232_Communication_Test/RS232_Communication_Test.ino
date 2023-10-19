void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  int Byte_0;
  
  if (Serial.available()) 
  {
    Byte_0 = Serial.read();
    Serial.write(Byte_0);
  }
}
