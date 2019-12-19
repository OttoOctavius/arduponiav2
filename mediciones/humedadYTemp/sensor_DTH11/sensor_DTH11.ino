#include <DHT.h>
#include <DHT_U.h>

// ------------------------------------|
// Enviroment humidity and temperature |
// ------------------------------------|

#define DHTPIN 10 //entrada señal al arduino desde el sensor de humedar y temperatura
#define DHTTYPE 11

int sensorEnviromentPin = 9;

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// --------------------------------------
void setup() {

  // Serial
  Serial.begin(9600);

  //pin del sensor de humedad intraterrestre
  pinMode(sensorEnviromentPin, OUTPUT);
  digitalWrite(sensorEnviromentPin, HIGH);
  // Init DHT
  dht.begin();

}

void sensordht(){
  // Reading temperature and humidity
  float humidity = dht.readHumidity();
  // Read temperature as Celsius
  float temperature = dht.readTemperature();

  // Display
  Serial.print("Temperature C:");
  Serial.print(temperature);
  Serial.println();

  Serial.print("Humidity:");
  Serial.print(humidity);
  Serial.println();
}

void loop() {
  sensordht();
  // stop the program for <sensorValue> milliseconds:
  delay(8000);
}
