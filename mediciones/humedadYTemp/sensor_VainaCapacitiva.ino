// Sensor Humedad de tierra
int sensorPin0 = A0;    //entrada señal al arduino desde el sensor de humedar intraterrestre
int pinIntraH = 8;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {

  // Serial
  Serial.begin(9600);

  //pin del sensor de humedad intraterrestre
  pinMode(pinIntraH, OUTPUT);
}

//15:25 17:05

void loop() {

  //Sensor de humedad intraterrestre
  digitalWrite(pinIntraH, HIGH);
  delay(2000);
  
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin0);
  // turn the ledPin on
  digitalWrite(pinIntraH, LOW);

  Serial.print("Humidity earth: ");
  Serial.println(sensorValue);
 
  // stop the program for <sensorValue> milliseconds:
  delay(8000);
}
