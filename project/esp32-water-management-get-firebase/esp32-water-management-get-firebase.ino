#include <WiFi.h>
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

#define PIN_LEDRED 32
#define PIN_LEDBLUE 26
#define PIN_BUZZER 14

int temp;
int waterlevel;

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

  pinMode(PIN_LEDRED, OUTPUT);
  pinMode(PIN_LEDBLUE, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);

}

void loop() {
  if (Firebase.RTDB.getInt(&fbdo, "/data/temp")) {
    if (fbdo.dataType() == "int") {
      temp = fbdo.intData();
      Serial.println(temp);
    }
  } else {
    Serial.println(fbdo.errorReason());
  }
    
  if (Firebase.RTDB.getInt(&fbdo, "/data/waterlevel")) {
    if (fbdo.dataType() == "int") {
      waterlevel = fbdo.intData();
      Serial.println(waterlevel);
      if(waterlevel >= 30){
        digitalWrite(PIN_LEDBLUE, 1);
        Firebase.RTDB.setString(&fbdo, "/data/ledgreen", "ON");
        digitalWrite(PIN_LEDRED, 0);
        Firebase.RTDB.setString(&fbdo, "/data/ledred", "OFF");
      } else {
        digitalWrite(PIN_LEDRED, 1);
        Firebase.RTDB.setString(&fbdo, "/data/ledred", "ON");
        digitalWrite(PIN_LEDBLUE, 0);
        Firebase.RTDB.setString(&fbdo, "/data/ledgreen", "OFF");
      }
    }
  } else {
    Serial.println(fbdo.errorReason());
  }

  if(waterlevel < 30 || temp < 15) {
    tone(PIN_BUZZER, 1800);
    Firebase.RTDB.setString(&fbdo, "/data/buzzer", "ON");
  } else {
    tone(PIN_BUZZER, 0);
    Firebase.RTDB.setString(&fbdo, "/data/buzzer", "OFF");
  }

  delay(1000);
}
