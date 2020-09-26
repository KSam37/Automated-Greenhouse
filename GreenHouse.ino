#include <StopWatch.h>
#include <dht.h>
#include <LiquidCrystal_I2C.h>
#define DHT22_PIN 2   //define DHT pin
//#define MoistureSensor1 A0 
#define Pump_Pin 5
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
dht DHT;
StopWatch stopwatch;
int loopCount = 1;
//float sensorValue1 = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);                      //initializes the LCD and specifies the dimensions
  pinMode(Pump_Pin, OUTPUT);
  stopwatch.start();
}

void loop() {
 //starts timer and resets after 24 hours
 if (stopwatch.sec() > 86400) {
  stopwatch.restart();
  lcd.clear();
 }
  
  //temp and humidity
  int chk = DHT.read22(DHT22_PIN);
  float temp = DHT.temperature;
  float tempf = (temp * 1.8) + 32;
  float humi = DHT.humidity;
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(tempf);
  lcd.print(" F");
  lcd.setCursor(0,1);
  //zlcd.print(stopwatch.sec());
  lcd.print("Humi: ");
  lcd.print(humi);
  lcd.print(" %");
 
   
  //fan control
   if (stopwatch.sec() < 60) {
    analogWrite(3, 100);
   }
   else {
     analogWrite(3,LOW);
   }
   
   if (DHT.humidity > 80 || tempf > 90) {
    analogWrite(3, 100);
   }

   //soil moisture sensor
   //for (int i = 0; i <= 100; i++) 
   //{ 
   // sensorValue1 = sensorValue1 + analogRead(A0); 
   // delay(1); 
   //} 
   //sensorValue1 = sensorValue1/100.0;  
   //Serial.println(sensorValue1); 

   //pump control
   if (stopwatch.sec() < 9) {
    analogWrite(Pump_Pin, 120);
   }
   else {
    analogWrite(Pump_Pin, LOW);
   }

   delay (2000);
  }
