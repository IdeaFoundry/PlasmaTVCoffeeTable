/**
 * Columbus Idea Foundry Plasma TV Coffee Table
 * Debug Code to read and report photoresistor values via serial
 * 
 * Written by Karsten Look
 * Last updated 6/1/2015
 */
const int sensorPins[] = {A0, A1, A2, A3};
const int sensorDefaults[] = {85, 60, 40, 70};
const int pins[] = {11, 9, 6, 10};
long timer[] = {0, 0, 0, 0};

const int timeOn = 2000;

void setup(){
  for(int i = 0; i < 4; i++){
    pinMode(pins[i], OUTPUT);
  }
  for(int i = 0; i < 4; i++){
    pinMode(sensorPins[i], INPUT);
  }
  Serial.begin(9600);
  Serial.println("Restart");
}

int sensorValue;

void loop(){
  for(int i = 0; i < 4; i++){
    sensorValue = analogRead(sensorPins[i]);
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(sensorValue);
    Serial.print(", ");
    if(sensorValue < sensorDefaults[i]){
      digitalWrite(pins[i], HIGH);
      timer[i] = millis();
    }
    else{
      if(millis() - timer[i] > timeOn){
        digitalWrite(pins[i], LOW);
      }
    }
  }
  Serial.println();
  delay(200);
}
