void setup() {
  //Set the digital pins 12 and 3 to output for the buzzer and LED respectively
  pinMode(12, OUTPUT);
  pinMode(3, OUTPUT);

  //Begin serial communication at 1200 bps
  Serial.begin(9600);
}

void loop() {
  int waterSensor = 0;
  int lightSensor = 0;
  
  //The readings of the water and light sensors are stored in the appropriate variables (the water sensor is connected to A0 while the light sensor is connected to A2)
  waterSensor = analogRead(0);
  lightSensor = analogRead(2);

  Serial.print("The water level is at ");
  Serial.print(waterSensor);
  Serial.print("\nThe light level is at ");
  Serial.print(lightSensor);
  Serial.print("\n\n");

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
  if (lightSensor<200) {
    digitalWrite(3, HIGH);
  } else {
    digitalWrite(3, LOW);
  }
  delay(500);
}
