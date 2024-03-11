int TRIG_PIN = 10;
int ECHO_PIN = 11;
const int analogPin = A2; 
int sensorValue;
long duration, cm;
int buzzer = 12;
int dur_b = 200;
int aSo = 392, bDo = 523, bRe = 587, bMi = 659, bFa = 698;
int bSo = 784, bLa = 880, bSi = 988, bDDo = 1047;

void Ping();
void showDis();

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  Ping();
  showDis();
  sensorValue = analogRead(analogPin);
  Serial.print(sensorValue);
  if(cm < 10)
  {
    if(sensorValue > 850)
    {
      toAlice();
    }
  }
}

void Ping()
{
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  pinMode(ECHO_PIN, INPUT);
  duration = pulseIn(ECHO_PIN, HIGH);
  cm = (duration/2) / 29.1;
}

void showDis()
{
  Serial.print("Distance: ");
  Serial.print(cm);
  Serial.println(" cm");
}

void toAlice()
{
  tone(buzzer, bDo, dur_b);
  delay(400);
  tone(buzzer, bMi, dur_b);
  delay(400);
  tone(buzzer, bLa, dur_b);
  delay(400);
  tone(buzzer, bSi, dur_b);
  delay(700);

  tone(buzzer, bMi, dur_b);
  delay(400);
  tone(buzzer, bSo, dur_b);
  delay(400);
  tone(buzzer, bSi, dur_b);
  delay(400);
  tone(buzzer, bDDo, dur_b);
  delay(700);
}
