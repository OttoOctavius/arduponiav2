// Sensor Humedad de tierra
int sensorPin0 = A0;    //entrada señal al arduino desde el sensor de humedar intraterrestre
int pinIntraH = 8;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
int pinRelay = 36;

long tiempo = 0;
long acumulado = 0;

void setup() {

  // Serial
  Serial.begin(9600);
  pinMode(pinRelay,OUTPUT);
  
  pinMode(LED_BUILTIN, OUTPUT);
  //pin del sensor de humedad intraterrestre
  pinMode(pinIntraH, OUTPUT);
}

//15:25 17:05

void loop() {

  digitalWrite(LED_BUILTIN, HIGH);
  //Sensor de humedad intraterrestre
  digitalWrite(pinIntraH, HIGH);
  delay(2000);
  
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin0);
  // turn the ledPin on
  digitalWrite(pinIntraH, LOW);

  Serial.print(tiempo+acumulado);
  Serial.print(":");
  Serial.println(sensorValue);

  if(tiempo >= 3600*4){
  digitalWrite(pinRelay, HIGH);
  delay(3000);
  digitalWrite(pinRelay, LOW);
  acumulado += tiempo + 30;
  tiempo = 0; 
  }
  
  digitalWrite(LED_BUILTIN, LOW);
  delay(8000);
  tiempo+=10;
  
}
