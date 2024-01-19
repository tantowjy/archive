#include <AntaresESP32HTTP.h>

#define ACCESSKEY "e112c26b405394dc:2c6c8478a7dc4cf0"
#define WIFISSID "PQR"
#define PASSWORD "12345678"
#define projectName "IOT_K1"
#define deviceName "device"
#define pinLed1 5
#define pinLed2 18
#define pinLed3 19

AntaresESP32HTTP antares(ACCESSKEY);

void setup() {
    Serial.begin(115200);
    antares.setDebug(true);
    antares.wifiConnection(WIFISSID, PASSWORD);
    pinMode(pinLed1, OUTPUT);
    pinMode(pinLed2, OUTPUT);
    pinMode(pinLed3, OUTPUT);
}

void loop() {
  // Get the latest data from your Antares device
  antares.get(projectName, deviceName);

  // Check if we're actually getting data
  if(antares.getSuccess()) {
    int statusLed1 = antares.getInt("Led1");
    int statusLed2 = antares.getInt("Led2");
    int statusLed3 = antares.getInt("Led3");

    if(statusLed1 == 1){
      Serial.println("LED 1 ON");
      digitalWrite(pinLed1, 1);
    } else {
      Serial.println("LED 1 OFF");
      digitalWrite(pinLed1, 0);
    }

    if(statusLed2 == 1){
      Serial.println("LED 2 ON");
      digitalWrite(pinLed2, 1);
    } else {
      Serial.println("LED 2 OFF");
      digitalWrite(pinLed2, 0);
    }

    if(statusLed3 == 1){
      Serial.println("LED 3 ON");
      digitalWrite(pinLed3, 1);
    } else {
      Serial.println("LED 3 OFF");
      digitalWrite(pinLed3, 0);
    }

  }
  delay(2000);
}
