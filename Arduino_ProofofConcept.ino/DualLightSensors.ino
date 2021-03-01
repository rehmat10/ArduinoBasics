
int lSensor1Tripped = 0;
int lSensor2Tripped = 0;
int directionFound = 0;

void setup() {
  //Set the digital pins 12 and 3 to output for the buzzer and LED respectively
  pinMode(12, OUTPUT);
  pinMode(3, OUTPUT);

  
  
  //Begin serial communication at 1200 bps
  Serial.begin(9600);
}

void loop() {
  int waterSensor = 0;
  int lightSensor1 = 0;
  int lightSensor2 = 0;
  
  
  // The readings of the water and light sensors are stored in the appropriate variables (the water sensor is connected to A0 while the light sensor is connected to A2)
  //waterSensor = analogRead(0);
  lightSensor1 = analogRead(2);
  lightSensor2 = analogRead(4);

  Serial.print("A2: ");
  Serial.print(lightSensor1);
  Serial.print("    A4: ");
  Serial.print(lightSensor2);
  Serial.print("\n\n");
  
  // Direction is determined by which sensor is first tripped, meaning the object has come from that sensor's side. It only determines this once the other sensor is tripped as well
  // which is similuating the idea of an object passing through by hitting both sensors eventually. since we do not want it to think that the object is coming from the opposite direction
  // when it no longer infront of the first sensor but still infront of the second, the program waits for nothing to be in front of either sensor before checking for direction again
  if (directionFound == 0) {
    if (lightSensor1 < 200 && lightSensor2 < 200 && lSensor2Tripped + lSensor1Tripped == 0) {
      Serial.print("Unknown direction\n");
      // If we do not set direction to be found, then the moment the object leaves one sensor it will thing it is going the opposite direction
      directionFound = 1;
    }
    else if (lightSensor1 < 200 && lSensor2Tripped == 0) {
      lSensor1Tripped = 1;
    }
    else if (lightSensor2 < 200 && lSensor1Tripped == 0) {
      lSensor2Tripped = 1;
    }
  
    // Sensor 1 is tripped after Sensor 2
    if (lightSensor1 < 200 && lSensor2Tripped == 1) {
      Serial.print("Coming from A4\n");
      directionFound = 1;
    }
    // Sensor 2 is tripped after Sensor 1
    if (lightSensor2 < 200 && lSensor1Tripped == 1) {
      Serial.print("Coming from A2\n");
      directionFound = 1;
    }
  }

  // If nothing infront of either sensor, reset everything
  if (lightSensor1 >= 200 && lightSensor2 >= 200) {
    directionFound = 0;
    lSensor1Tripped = 0;
    lSensor2Tripped = 0;
  }
    

  /*Serial.print("The water level is at ");
  Serial.print(waterSensor);
  Serial.print("\nThe light level is at ");
  Serial.print(lightSensor);
  Serial.print("\n\n");*/

  //If the water level is high enough or low enough,the digital pin 12 will have voltage go through it, which is connected to the buzzer (not calibrated to the needs of the broccoli yet)
  /*if (waterSensor<50) {
    tone(12, 200);
    delay(500);
    noTone(12);
    delay(500);
  } else if (waterSensor>200){
    tone(12, 500);
    delay(200);
    noTone(12);
    delay(200);
  } else {
    noTone(12);
  }*/

  //If there is not enough sunlight, the digital pin 3 will have voltage passing through it, which is connected to the led (also not calibrated yet)
  /*if (lightSensor<200) {
    digitalWrite(3, HIGH);
  } else {
    digitalWrite(3, LOW);
  }
  delay(500);*/
  delay(500);
}
