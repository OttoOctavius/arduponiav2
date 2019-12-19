#include <DHT.h>
#include <DHT_U.h>
#include "SparkFun_AS7265X.h"
AS7265X sensor;
// -------------------------------------------|
// Enviroment humidity and temperature Sensor |
// -------------------------------------------|

#define DHTPIN 10 //entrada señal al arduino desde el sensor de humedar y temperatura
#define DHTTYPE 11

int sensorEnviromentPin = 9;
// Reading temperature and humidity
float humidity;
// Read temperature as Celsius
float temperature;

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);
// --------------------------------------END


// ----------------------|
// Earth humidity sensor |
// ----------------------|


//Dry: (520 430], Wet: (430 350], Water: (350 260] rangos de humedad de vainaEarth

int dry = 520;
int intervals = (dry - 260)/3;
int sensorPin0 = A0;    //entrada señal al arduino desde el sensor de humedar intraterrestre
int pinIntraH = 8;      // select the pin for the LED
int earthHumidityValue = 0;  // variable to store the value coming from the sensor

//-----------------------|
// Relay for bomb        |
//-----------------------|
int pinRelay = 36;

//-----------------------|
// Time for debugging    |
//-----------------------|
long tiempo = 0;
long acumulado = 0;
// ----------------------END

void setupEnviromentSensor() {

  //pin del sensor de humedad intraterrestre
  pinMode(sensorEnviromentPin, OUTPUT);
  digitalWrite(sensorEnviromentPin, HIGH);
  // Init DHT
  dht.begin();

}

void setupEarthSensor() {
  pinMode(LED_BUILTIN, OUTPUT);
  //pin del sensor de humedad intraterrestre
  pinMode(pinIntraH, OUTPUT);
}

void setupEspectometer() {
  delay(1000);
  
  if(sensor.begin() == false)
  {
    Serial.println("Reset the Arduino Shinji, Spectometer not working :/");
    while(1);
  }
  //Led status
  sensor.disableIndicator();
  //LED. 0 = White, 1 = IR, 2 = UV
  sensor.disableBulb(0);
  sensor.disableBulb(1);
  sensor.disableBulb(2);
  Serial.print("Using channels:");
  Serial.println("A,B,C,D,E,F,G,H,R,I,S,J,T,U,V,W,K,L");
  //El orden de canales es por longitud de onda, no alfabetico
}

void setup() {

  //habilito pin para relay que acciona la bomba
  pinMode(pinRelay,OUTPUT);
  
  // Serial
  Serial.begin(9600);

  setupEnviromentSensor();
  setupEarthSensor();
  setupEspectometer();
}

void sensordhtRead(){
  // Reading temperature and humidity
  humidity = dht.readHumidity();
  // Read temperature as Celsius
  temperature = dht.readTemperature();
}

void sensordhtWriteValues() {
  // Display
  Serial.print("Enviroment Temperature C:");
  Serial.print(temperature);
  Serial.println();

  Serial.print("Enviroment Humidity:");
  Serial.println(humidity);
  Serial.println();
}

void sensorEarthRead() {
  digitalWrite(LED_BUILTIN, HIGH);
  //Sensor de humedad intraterrestre
  digitalWrite(pinIntraH, HIGH);
  delay(2000);
}

void sensorEarthWriteValues() {
  // read the value from the sensor:
  earthHumidityValue = analogRead(sensorPin0);
  // turn the ledPin on
  digitalWrite(pinIntraH, LOW);

  Serial.println("--Earth Sensor Start--");
  Serial.print("Humedad:");
  Serial.println(earthHumidityValue);
  Serial.println("--Earth Sensor End--");
  Serial.println();
}

float NDVI(){
  //float RED = sensor.getCalibratedS() + sensor.getCalibratedJ() + sensor.getCalibratedT();
  //float IR = sensor.getCalibratedH() + sensor.getCalibratedR() + sensor.getCalibratedI();00
  float IR = sensor.getCalibratedR();
  float RED = sensor.getCalibratedJ();
  return ((IR - RED) / (IR + RED))*100;
}

void sensorSpectometerWriteValues(){
  Serial.print("Values Spectometer:");
  Serial.print(sensor.getCalibratedA());
  Serial.print(",");
  Serial.print(sensor.getCalibratedB());
  Serial.print(",");
  Serial.print(sensor.getCalibratedC());
  Serial.print(",");
  Serial.print(sensor.getCalibratedD());
  Serial.print(",");
  Serial.print(sensor.getCalibratedE());
  Serial.print(",");
  Serial.print(sensor.getCalibratedF());
  Serial.print(",");
  Serial.print(sensor.getCalibratedG());
  Serial.print(",");
  Serial.print(sensor.getCalibratedH());
  Serial.print(",");

  Serial.print(sensor.getCalibratedR());
  Serial.print(",");
  Serial.print(sensor.getCalibratedI());
  Serial.print(",");
  Serial.print(sensor.getCalibratedS());
  Serial.print(",");  
  Serial.print(sensor.getCalibratedJ());
  Serial.print(",");
  Serial.print(sensor.getCalibratedT());
  Serial.print(",");
  Serial.print(sensor.getCalibratedU());
  Serial.print(",");
  Serial.print(sensor.getCalibratedV());
  Serial.print(",");
  Serial.print(sensor.getCalibratedW());
  Serial.print(",");  
  Serial.print(sensor.getCalibratedK());
  Serial.print(",");
  Serial.print(sensor.getCalibratedL());
  Serial.print(",");
  Serial.print(NDVI());
  Serial.print(",");
  Serial.println(sensor.getTemperature());

  Serial.println();
  Serial.print("Temp Spectometer:");
  Serial.println(sensor.getTemperature());
  
  sensor.disableBulb(0);
  sensor.disableBulb(1);
  sensor.disableBulb(2);
}

bool verifyHumidityEarth() {
  return earthHumidityValue < (dry - intervals);//(earthHumidityValue < dry && earthHumidityValue > (dry - intervals));
}

void loop() {
  sensor.takeMeasurements();
  sensor.enableBulb(0);
  sensor.enableBulb(1);
  sensor.enableBulb(2);
  
  sensorEarthRead();
  sensordhtRead();

  sensordhtWriteValues();
  sensorEarthWriteValues();
  sensorSpectometerWriteValues();
  
  Serial.print("Tiempo:");
  Serial.println(tiempo+acumulado);
  
  if(!verifyHumidityEarth() || NDVI() < 50.0){
  digitalWrite(pinRelay, HIGH);
  delay(1000);
  digitalWrite(pinRelay, LOW);
  acumulado += tiempo + 1;
  tiempo = 0;
  }
  
  digitalWrite(LED_BUILTIN, LOW);
  delay(8000);
  tiempo+=10;
}
