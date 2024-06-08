#include <Arduino.h>
#include <DHT.h>
#include <Firebase_ESP_Client.h>
#include <WiFi.h>

/* FIREBASE SETUP */

#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define WIFI_SSID "**************"
#define WIFI_PASSWORD "**************"
#define API_KEY "**************"
#define DATABASE_URL "**************"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

/* HARDWARE SETUP */
#define PIN_POMPA 26 
#define PIN_SOIL 33 //15
#define PIN_SOIL_POWER 25 //2
#define PIN_WATER_LVL 32 //4
#define PIN_WATER_LVL_POWER 27 //35 //16
#define PIN_DHT 23
#define DHT_SENSOR_TYPE DHT11

#define SoilBasah 1800  // nilai max untuk tanah basah
#define SoilKering 3500 // nilai min untuk tanah kering

DHT dht_sensor(PIN_DHT, DHT_SENSOR_TYPE);

unsigned long sendDataPrevMillis = 0;
int val = 0;
//int moisture;
int waterlvl;
bool signupOK = false;

void setup(){
  Serial.begin(115200);

  /* FIREBASE SIGNUP */
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  // Assign the api key (required)
  config.api_key = API_KEY;

  // Assign the RTDB URL (required)
  config.database_url = DATABASE_URL;

  // Sign up
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  // Assign the callback function for the long running token generation task
  config.token_status_callback = tokenStatusCallback;
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  /* HARDWARE */
  pinMode(PIN_POMPA, OUTPUT);

  pinMode(PIN_SOIL_POWER, OUTPUT);
  digitalWrite(PIN_SOIL_POWER, LOW);

  pinMode(PIN_WATER_LVL_POWER, OUTPUT);
  digitalWrite(PIN_WATER_LVL_POWER, LOW);

  // Inisialisasi sensor DHT
  dht_sensor.begin();
}

void loop(){
  // Mengukur kondisi kelembaban tanah
  digitalWrite(PIN_SOIL_POWER, HIGH);
  delay(10);
  int moisture = analogRead(PIN_SOIL);
  digitalWrite(PIN_SOIL_POWER, LOW);
  Serial.println(moisture);
  Firebase.RTDB.setInt(&fbdo, "sensor/soilanalog", moisture);
  /*if (Firebase.RTDB.getInt(&fbdo, "/sensor/soilanalog")) {
    moisture = fbdo.intData();
    Serial.println(moisture);
  } else {
    Serial.println(fbdo.errorReason());
  } */

  // Mengukur level ketersedian air
  digitalWrite(PIN_WATER_LVL_POWER, HIGH);
  delay(10);
  val = analogRead(PIN_WATER_LVL);
  waterlvl = val/21;
  digitalWrite(PIN_WATER_LVL_POWER, LOW);
  Serial.print("Water level: ");
  Serial.print(waterlvl);
  Serial.println(" %");

  // Mengukur suhu dan kelembapan lingkungan
  float humi  = dht_sensor.readHumidity();
  float tempC = dht_sensor.readTemperature();

  // Get & post data ke firebase
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();

    // mengirim data sensor ke firebase
    Firebase.RTDB.setInt(&fbdo, "sensor/waterlvl", waterlvl);
    /* if (Firebase.RTDB.getInt(&fbdo, "/sensor/waterlvl")) {
      waterlvl = fbdo.intData();
      Serial.println(waterlvl);
    } else {
      Serial.println(fbdo.errorReason());
    } */

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
      Firebase.RTDB.setFloat(&fbdo, "sensor/humidity", humi);
      Firebase.RTDB.setFloat(&fbdo, "sensor/temperature", tempC);
    }

    // penyiraman otomatis berdasarkan data sensor
    if (moisture < SoilBasah) {
      Serial.println("Basah");
      pompaOFF();
      Firebase.RTDB.setString(&fbdo, "sensor/soilmoisture", "Basah");
      Firebase.RTDB.setString(&fbdo, "sensor/pomp", "Mati");
    } else if (moisture >= SoilBasah && moisture < SoilKering) {
      Serial.println("Bagus");
      pompaOFF();
      Firebase.RTDB.setString(&fbdo, "sensor/soilmoisture", "Bagus");
      Firebase.RTDB.setString(&fbdo, "sensor/pomp", "Mati");
    } else {
      Serial.println("Kering");
      Firebase.RTDB.setString(&fbdo, "sensor/soilmoisture", "Kering");
      if (waterlvl > 35) {
        pompaON();
        Firebase.RTDB.setString(&fbdo, "sensor/pomp", "Menyala");
      } else {
        pompaOFF();
        Firebase.RTDB.setString(&fbdo, "sensor/pomp", "Mati");
        //pompaON();
        //Firebase.RTDB.setString(&fbdo, "sensor/pomp", "Menyala");
      }
    }

  }

  delay(1000);
}

void pompaOFF(){
  digitalWrite(PIN_POMPA, LOW);
  delay(3000);
}

void pompaON(){
  digitalWrite(PIN_POMPA, HIGH);
  delay(3000);
}
