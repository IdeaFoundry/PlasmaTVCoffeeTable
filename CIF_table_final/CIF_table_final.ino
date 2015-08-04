/**
 * * Columbus Idea Foundry Plasma TV Table
 * Main code to operate LED strips based off of photoresistor readings
 * 
 * Written by Karsten Look
 * Last updated 6/8/2015
 */
const int sensorPins[] = {A0, A1, A2, A3};
//const int sensorDefaults[] = {85, 60, 40, 70};
const int sensorDefaults[] = {40, 60, 20, 60};
int sensorCmp[4];
const int pins[] = {11, 9, 6, 10, 5};
int vals[] = {0, 0, 0, 0};


void setup() {
  for (int i = 0; i < 4; i++) {
    sensorCmp[i] = sensorDefaults[i]; //restore to normal operation
  }

  for (int i = 0; i < 5; i++) {
    pinMode(pins[i], OUTPUT);
  }
  for (int i = 0; i < 4; i++) {
    pinMode(sensorPins[i], INPUT);
  }

  Serial.begin(9600);
  Serial.println("restart");
}
unsigned long interval = 0;
const int del = 1000;
int rnd = 0;
unsigned long dim = 0;
int sensorValue;
//unsigned long on = 0;

boolean state = true;
unsigned long border = 0;
int borderVal = 0;
unsigned long lastOn = 0;
boolean dead = false;
int timeOn = 0;

void loop() {
  for (int i = 0; i < 4; i++) {
    sensorValue = analogRead(sensorPins[i]);
    
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(sensorValue);
    Serial.print(", ");
    
    if (dead && i == 0) {
      if (sensorValue > sensorDefaults[i]) {
        //and has been for at least 1 second.
        for (int j = 0; j < 4; j++) {
          sensorCmp[j] = sensorDefaults[j]; //restore to normal operation
        }
        dead = false;
      }
    }

    if (sensorValue < sensorCmp[i]) {
      vals[i] = 255;

      if (millis() - lastOn < 1000) { //If the lights were on less than a second ago
        timeOn = timeOn + millis() - lastOn;
      }
      lastOn = millis();

    }
    else { //if it is too bright, reset the on timer
      if(i == 0){
        timeOn = 0;
      }
    }
  }
  Serial.println();
  /*
  Serial.print("lastOn diff: ");
  Serial.print(millis() - lastOn);
//  Serial.print(", on diff: ");
//  Serial.print(millis() - on);
  Serial.print(", time on: ");
  Serial.println(timeOn);
*/

    if (timeOn > 5000) { //if the lights have been on for 5 seconds and are still on
      for (int i = 0; i < 4; i++) {
        sensorCmp[i] = 0; // set the reaction value to zero
      }
      dead = true;
    }


  if (millis() - dim > 50) {
    for (int i = 0; i < 4; i++) {
      if (vals[i] > 10) {
        vals[i] = vals[i] - 10;
        analogWrite(pins[i], vals[i]);
      }
      else {
        digitalWrite(pins[i], LOW);
      }
      dim = millis();
    }
  }

  //border
  if (!dead) {
    if (state && (millis() - border > 2000)) {
      if (borderVal < 100) {
        borderVal++;
      }
      else {
        borderVal = borderVal + 5;
      }
      if (borderVal > 255) {
        borderVal = 255;
        state = !state;
      }
    }
    if (!state) {
      if (borderVal > 100) {
        borderVal = borderVal - 5;
      }
      else {
        borderVal--;
      }
      if (borderVal < 0) {
        state = !state;
        borderVal = 0;
        border = millis();
      }
    }
    /*
    Serial.print("border: ");
    Serial.print(border);
    Serial.print(" borderVal: ");
    Serial.println(borderVal);
    */
    analogWrite(pins[4], borderVal);
  }
  else {
    digitalWrite(pins[4], LOW);
  }
  /*
  //border test code
  if(millis() - border > 1000){
    digitalWrite(pins[4], state);
    state = !state;
    border = millis();
  }
  */

  //  delay(1000);
}


