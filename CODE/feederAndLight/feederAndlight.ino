#include <Wire.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>
#include <Servo.h>   //載入函式庫，這是內建的，不用安裝

Servo myservo;  // 建立SERVO物件
// DS1302接線指示: 可依需求修改
// DS1302 CLK/SCLK --> 10
// DS1302 DAT/IO --> 9
// DS1302 RST/CE --> 8
// DS1302 VCC --> 3.3v - 5v
// DS1302 GND --> GND

int ledPin = 12;
const int analogPin = A1;
int sensorValue = 0;

ThreeWire myWire(9, 10, 8); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

void setup ()
{
  pinMode(ledPin, OUTPUT);
  myservo.attach(11);  // 設定要將伺服馬達接到哪一個PIN腳
  Serial.begin(9600);

  Serial.print("compiled: ");
  Serial.print(__DATE__);
  Serial.println(__TIME__);

  Rtc.Begin();

  //__DATE__，__TIME__，是程式碼編譯時的日期和時間
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  printDateTime(compiled);
  Serial.println();

  //判斷DS1302是否接好
  if (!Rtc.IsDateTimeValid())
  {
    // Common Causes:
    //    1) first time you ran and the device wasn't running yet
    //    2) the battery on the device is low or even missing

    Serial.println("RTC lost confidence in the DateTime!");
    Rtc.SetDateTime(compiled);
  }

  if (Rtc.GetIsWriteProtected())
  {
    Serial.println("RTC was write protected, enabling writing now");
    Rtc.SetIsWriteProtected(false);
  }

  if (!Rtc.GetIsRunning())
  {
    Serial.println("RTC was not actively running, starting now");
    Rtc.SetIsRunning(true);
  }

  //判斷DS1302上紀綠的時間和編譯時的時間，哪個比較新
  //如果編譯時間比較新，就進行設定，把DS1302上的時間改成新的時間
  //now：DS1302上紀綠的時間，compiled：編譯時的時間
  RtcDateTime now = Rtc.GetDateTime();
  if (now < compiled)
  {
    Serial.println("RTC is older than compile time!  (Updating DateTime)");
    //編譯時間比較新，把DS1302上的時間改成編譯的時間
    Rtc.SetDateTime(compiled);
  }
  else if (now > compiled)
  {
    Serial.println("RTC is newer than compile time. (this is expected)");
  }
  else if (now == compiled)
  {
    Serial.println("RTC is the same as compile time! (not expected but all is fine)");
  }
  
}

void loop ()
{
  RtcDateTime now = Rtc.GetDateTime();

  printDateTime(now);
  Serial.println();

  //判斷DS1302是否正常，如果不正常，一般是線沒接好，或是電池沒電了
  if (!now.IsValid())
  {
    Serial.println("RTC lost confidence in the DateTime!");
  }
  





  delay(10000); // 10秒更新一次
}

#define countof(a) (sizeof(a) / sizeof(a[0]))

//顯示完整年月日時間的副程式  
void printDateTime(const RtcDateTime& dt)
{
  char datestring[20];

// snprintf(datestring,
//             countof(datestring),
//             PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
//             dt.Month(),
//             dt.Day(),
//             dt.Year(),
//             dt.Hour(),
//             dt.Minute(),
//             dt.Second() );
  Serial.print(dt.Year());
  Serial.print("/");
  Serial.print(dt.Month());
  Serial.print("/");
  Serial.print(dt.Day());
  Serial.print(" ");
  Serial.print(dt.Hour());
  Serial.print(":");
  Serial.print(dt.Minute());
  Serial.print(":");
  Serial.println(dt.Second());
  //Serial.print(datestring);

  sensorValue = analogRead(analogPin);
  Serial.println(sensorValue);
  if(sensorValue > 450)
    digitalWrite(ledPin, HIGH);
  else
    digitalWrite(ledPin, LOW);




  if(dt.Hour()==10
  ){ // 自行設定何時餵食
  myservo.write(180); //旋轉到180度
  delay(300);
  myservo.write(90);
  delay(300);
  myservo.write(180); //旋轉到180度
  delay(300);
  myservo.write(90);
  delay(300);
  myservo.write(180); //旋轉到180度
  delay(300);
  myservo.write(90);
  delay(300);
  myservo.write(180); //旋轉到180度
  delay(300);
  myservo.write(90);
  delay(300);
  myservo.write(180); //旋轉到180度
  delay(300);
  myservo.write(90);
  delay(800);
  }
}
