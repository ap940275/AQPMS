#include<string.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
SoftwareSerial s(5,6);  //(RX, TX)


int gasSensor = A0;
int gasSensorValue;

int tempSensor = A2;
int tempSensorValue;

int coSensor = A1;
int coSensorValue;

void setup() {
  Serial.begin(9600);
  s.begin(9600);
}
  
void loop() {
  gasSensorValue = analogRead(gasSensor);
  tempSensorValue = analogRead(tempSensor);
  coSensor = analogRead(coSensorValue);
  StaticJsonDocument<1000> jsonBuffer;
  jsonBuffer["gasSensorValue"] = gasSensorValue;
  jsonBuffer["tempSensorValue"] = tempSensorValue;
  jsonBuffer["coSensorValue"] = coSensor;
  serializeJsonPretty(jsonBuffer, s);
  serializeJsonPretty(jsonBuffer, Serial);
  delay(1000);
}
