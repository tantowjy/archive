#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h" //Provide the token generation process info.
#include "addons/RTDBHelper.h" //Provide the RTDB payload printing info and other helper functions.

// Insert your network credentials
#define WIFI_SSID "****************"
#define WIFI_PASSWORD "****************"

// Insert Firebase project API Key
#define API_KEY "****************"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "****************" 

// Firebase Setup
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
bool signupOK = false;

#define PIN_RELAY 32
#define TRIG_PIN 26
#define ECHO_PIN 35
#define ONE_WIRE_BUS 33

// DS18B20 Sensor
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float duration_us, distance_cm, waterlevel;
float temp;

void setup() {
  // WIFI
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  // FIREBASE START //
  config.api_key = API_KEY;           // Assign the api key (required)
  config.database_url = DATABASE_URL; // Assign the RTDB URL (required)

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  } else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback; // Set callback

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  // FIREBASE END //
  
  // Relay
  pinMode(PIN_RELAY, OUTPUT);
  // Sensor Ultrasonik
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  //DS18B20
  sensors.begin();
}

void loop() {
  temp_Waterlevel();

  if(waterlevel < 30){
    isiTangki();
  } else {
    digitalWrite(PIN_RELAY, 0);
    Firebase.RTDB.setString(&fbdo, "/data/pomp", "OFF");
  }

  delay(100);
}

void isiTangki() {
  while (waterlevel < 100){
    digitalWrite(PIN_RELAY, 1);
    Firebase.RTDB.setString(&fbdo, "/data/pomp", "ON");

    temp_Waterlevel();
    delay(50);
  }
}

void temp_Waterlevel() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH);
  // calculate the distance
  distance_cm = 0.017 * duration_us;
  waterlevel = map(distance_cm, 10.15, 2.8, 0, 100);
  // Send waterlevel to Firebase
  Firebase.RTDB.setFloat(&fbdo, "/data/waterlevel", waterlevel);

  Serial.print("Level Air: ");
  Serial.print(waterlevel);
  Serial.println(" %");

  // Temperature Sensor
  sensors.requestTemperatures(); 
  temp = sensors.getTempCByIndex(0);
  Serial.print("Celsius temperature: ");
  Serial.println(temp);
  Firebase.RTDB.setFloat(&fbdo, "/data/temp", temp);
}