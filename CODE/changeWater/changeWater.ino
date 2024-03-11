int motorpin_a1 = 10;
int motorpin_a2 = 11;
int motorpin_b1 = 12;
int motorpin_b2 = 13;
void setup() {
  // put your setup code here, to run once:
  pinMode(motorpin_a1, OUTPUT);
  pinMode(motorpin_a2, OUTPUT);  
  pinMode(motorpin_b1, OUTPUT);  
  pinMode(motorpin_b2, OUTPUT);
  pinMode(2, INPUT);
   
}
int TTT;

void loop() {
  TTT = digitalRead(2);
  if(TTT == 1)
  {
    analogWrite(motorpin_b2, LOW );
    analogWrite(motorpin_b1, 200 );
    analogWrite(motorpin_a2, LOW );
    analogWrite(motorpin_a1, 200 );
    delay(20000);
    analogWrite(motorpin_b2, LOW );
    analogWrite(motorpin_b1, LOW );
    analogWrite(motorpin_a2, LOW );
    analogWrite(motorpin_a1, LOW );
  }
}
