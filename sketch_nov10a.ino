// Blynk Libs
//
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include<ArduinoJson.h>
#include<SoftwareSerial.h>

SoftwareSerial s(D6,D5); // RX, TX

BlynkTimer timer;


// WIFI Authentication
char auth[] = "6I6q8-ai22sWGQ0i9BezkAtC1lh2I80H";
char ssid[] = "Saket";
char pass[] = "saket123";

void setup() {
  Blynk.begin(auth, ssid, pass);
  Serial.begin(9600);
  s.begin(9600);
  while(!Serial) continue;
  timer.setInterval(1000L, myTimerEvent);
}

long tempSensorValue;
long coSensorValue;
long gasSensorValue;

void myTimerEvent()
{
  Serial.println(tempSensorValue);
  Serial.println(coSensorValue);
  Serial.println(gasSensorValue);
  if(gasSensorValue > 250) {
    Blynk.notify("Air quality is very dangerous!!");  
  }

  if(coSensorValue > 150) {
    Blynk.notify("Air quality is very dangerous!!");  
  }

  if(tempSensorValue> 1500) {
    Blynk.notify("Temperature is very high!!");  
  }
  
  Blynk.virtualWrite(V0, tempSensorValue);
  Blynk.virtualWrite(V1, coSensorValue);
  Blynk.virtualWrite(V2, gasSensorValue);
}


void loop() {
  StaticJsonDocument<1000> jsonBuffer;  
  DeserializationError error = deserializeJson(jsonBuffer, s);
  Serial.println("Json Data Received!");
  tempSensorValue = jsonBuffer["tempSensorValue"];
  coSensorValue = jsonBuffer["coSensorValue"];
  gasSensorValue = jsonBuffer["gasSensorValue"];
  delay(200);
  timer.run();
  Blynk.run();
}
