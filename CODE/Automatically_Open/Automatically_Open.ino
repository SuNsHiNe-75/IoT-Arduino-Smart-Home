#include <AmebaServo.h>

// Variables
int TRIG_PIN = 10;
int ECHO_PIN = 11;
long duration, cm;
int count = 0, i;

// Functions
void Ping();
void showDis();
void Open();

AmebaServo myservo;

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  myservo.attach(13, 500, 2400);
  myservo.write(90); // Initialize.
}

void loop() {
  Ping();
  showDis();
  Open();
  delay(300);
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

void Open()
{
  if(cm <= 6)
  {
    count++;
    if(count >= 5)
    {
      myservo.write(0);
      delay(3000); // Keep open 3s.
    }
  }
  else
  {
    count = 0;
    myservo.write(90);
  }
    
}

void showDis()
{
  Serial.print("Distance: ");
  Serial.print(cm);
  Serial.println(" cm");
}
