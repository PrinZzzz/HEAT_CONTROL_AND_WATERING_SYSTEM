#include <Wire.h>
#include <DS3231.h>
#include <dht.h>
dht DHT;
#define DHT11_PIN 7
DS3231 clock;
RTCDateTime dt;
int motor = 12;
int fan = 11;
int led = 10;
void setup()
{
  Serial.begin(9600);
  Serial.println("Initialize DS3231");
  clock.begin();
  pinMode(motor,OUTPUT);
  pinMode(fan,OUTPUT);
  pinMode(led,OUTPUT);
}

void loop()
{
  int chk = DHT.read11(DHT11_PIN);
  int temp = DHT.temperature;
  int hum = DHT.humidity;
  dt = clock.getDateTime();
  Serial.print("Date and Time: "); Serial.print(dt.year); Serial.print("-"); Serial.print(dt.month); Serial.print("-"); Serial.print(dt.day); Serial.print(" "); Serial.print(dt.hour);   Serial.print(":"); Serial.print(dt.minute); Serial.print(":"); Serial.print(dt.second); Serial.println("");
  Serial.print("Temperature = "); Serial.print(DHT.temperature); Serial.println(" °C");
  Serial.print("Humidity = "); Serial.print(DHT.humidity); Serial.println(" %");
  delay(1000);
  // sample best humidity is 40 - 60 % 
  if (DHT.humidity <= 40){
    digitalWrite(fan,LOW);
    }
   else if (DHT.humidity >= 60){
      digitalWrite(led,LOW);
      }
  // sample best temperature is 20 - 40 C 
     else if (DHT.temperature <= 20){
      digitalWrite(led,LOW);
        }
       else if (DHT.temperature >= 40){
        digitalWrite(fan,LOW);
          }
  //pag else if dapat una yung mababa tapos pataas
  else if (dt.hour == 14 && dt.minute == 04 && dt.second == 00)
  {
    digitalWrite(motor,LOW);
    digitalWrite(fan,LOW);
    digitalWrite(led,LOW);
    Serial.print("Morning watering");
    delay(10000); // 10 seconds
    }
    else if (dt.hour == 14 && dt.minute == 04 && dt.second == 20)
    {
    digitalWrite(motor,LOW);
    digitalWrite(led,LOW);
    Serial.print("Afternoon watering");
    delay(10000); // 10 seconds
      }
      else if (dt.hour == 14 && dt.minute == 04 && dt.second == 40)
      {
    digitalWrite(motor,LOW);
    Serial.print("Evening watering");
    delay(10000); // 10 seconds
        }
        else
          {
          digitalWrite(motor,HIGH);
          digitalWrite(fan,HIGH);
          digitalWrite(led,HIGH);
            }
}
