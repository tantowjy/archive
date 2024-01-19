#include <DHT.h>
#define PIN_POMPA 32           // pin untuk pompa air
#define PIN_SOIL 15            // pin untuk soil moisture
#define PIN_SOIL_POWER 2       // pin power untuk soil moisture
#define PIN_WATER_LVL 4        // pin untuk water level
#define PIN_WATER_LVL_POWER 16 // pin power untuk water level
#define PIN_DHT  23            // pin untuk DHT11
#define DHT_SENSOR_TYPE DHT11  // jenis sensor dht yang digunakan

#define SoilBasah 1800  // nilai maksimum untuk tanah basah
#define SoilKering 3500 // nilai minimum untuk tanah kering

DHT dht_sensor(PIN_DHT, DHT_SENSOR_TYPE);

int val = 0;

void setup() {
  Serial.begin(115200);
  pinMode(PIN_POMPA, OUTPUT);

  pinMode(PIN_SOIL_POWER, OUTPUT);
  digitalWrite(PIN_SOIL_POWER, LOW);

  pinMode(PIN_WATER_LVL_POWER, OUTPUT);
  digitalWrite(PIN_WATER_LVL_POWER, LOW);

  dht_sensor.begin(); // inisialisasi sensor DHT
}

void loop() {
  // Mengukur kondisi kelembaban tanah
  digitalWrite(PIN_SOIL_POWER, HIGH);
  delay(10);
  int moisture = analogRead(PIN_SOIL);
  digitalWrite(PIN_SOIL_POWER, LOW);
	Serial.print("Analog Output: ");
	Serial.println(moisture);

  // Mengukur level ketersedian air
  digitalWrite(PIN_WATER_LVL_POWER, HIGH);
  delay(10);
  val = analogRead(PIN_WATER_LVL);
  digitalWrite(PIN_WATER_LVL_POWER, LOW);
  Serial.print("Water level: ");
  Serial.println(val);
  Serial.print("Water level: ");
  Serial.print(val/21);
  Serial.println(" %");

  // Mengukur suhu dan kelembapan lingkungan
  float humi  = dht_sensor.readHumidity();
  float tempC = dht_sensor.readTemperature();
  if ( isnan(tempC) || isnan(humi)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Humidity: ");
    Serial.print(humi);
    Serial.print("%");
    Serial.print("  |  ");
    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.println("°C");
  }

  // Status kondisi tanah dan pompa
  if (moisture < SoilBasah) {
    Serial.println("Status: Tanah basah");
    pompaOFF();
  } else if (moisture >= SoilBasah && moisture < SoilKering) {
    Serial.println("Status: Kelembaban tanah bagus");
    pompaOFF();
  } else {
    Serial.println("Status: Tanah kering");
    pompaON();
  }

  delay(3000);
}

void pompaOFF(){
  digitalWrite(PIN_POMPA, LOW); // pompa air mati
  delay(4000);
}

void pompaON(){
  digitalWrite(PIN_POMPA, HIGH); // pompa air nyala
  delay(4000);
}
