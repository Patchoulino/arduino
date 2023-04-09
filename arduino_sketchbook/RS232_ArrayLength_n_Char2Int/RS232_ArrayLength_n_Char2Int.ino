const int dig[] = {0,1,2,3,4,5,6,7,8,9};
int largo = sizeof(dig) / 2 - 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(largo);
  int chr = '5';
  chr = chr - '0';
  Serial.println(chr);
}

void loop() {
  // put your main code here, to run repeatedly:

}
