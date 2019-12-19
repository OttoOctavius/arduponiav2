#include <DHT.h>
#include <DHT_U.h>

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

void setup() {

  //habilito pin para relay que acciona la bomba
  pinMode(pinRelay,OUTPUT);
  
  // Serial
  Serial.begin(9600);

  setupEnviromentSensor();

  setupEarthSensor();

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

bool verifyHumidityEarth() {
  return (earthHumidityValue < dry && earthHumidityValue > (dry - intervals));
}

void loop() {
  sensorEarthRead();
  sensordhtRead();

  sensordhtWriteValues();
  sensorEarthWriteValues();

  Serial.print("Tiempo:");
  Serial.println(tiempo+acumulado);
  
  if(verifyHumidityEarth()){
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
