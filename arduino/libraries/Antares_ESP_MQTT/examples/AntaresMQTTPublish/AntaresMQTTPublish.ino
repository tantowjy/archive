/*
    This is an example sketch to publish MQTT data to your
    Antares IoT Platform project device via ESP8266.

    MQTT server & port:
    platform.antares.id, port 1338

    MQTT topic:
    /oneM2M/req/your-access-key/antares-cse/json

    This sketch will deploy data to your Antares device
    and publish to the MQTT topic simultaneously.

    For more information, please visit https://antares.id/id/docs.html
*/

#include <AntaresESPMQTT.h>

#define ACCESSKEY "YOUR-ACCESS-KEY"       // Antares account access key
#define WIFISSID "YOUR-WIFI-SSID"         // Wi-Fi SSID to connect to
#define PASSWORD "YOUR-WIFI-PASSWORD"     // Wi-Fi password

#define projectName "YOUR-APPLICATION-NAME"   // Name of the application created in Antares
#define deviceName "YOUR-DEVICE-NAME"     // Name of the device created in Antares

AntaresESPMQTT antares(ACCESSKEY);

void setup() {
  Serial.begin(115200);
  antares.setDebug(true);
  antares.wifiConnection(WIFISSID, PASSWORD);
  antares.setMqttServer();
}

void loop() {
  /*
    Check if we're still connected to the MQTT broker/server.
    If disconnected, the device will try to reconnect.
   */
  antares.checkMqttConnection();

  // Variable init
  int temp = random(25,30) ;
  int hum = random(75,90);
  float windsp = float(random(20, 30))/3.33;
  float rainlv = float(random(0, 20))/6.99;
  String lat = "-6.8718189";
  String lon = "107.5872477";

  // Add variable to data storage buffer
  antares.add("temperature", temp);
  antares.add("humidity", hum);
  antares.add("wind_speed", windsp);
  antares.add("rain_level", rainlv);
  antares.add("latitude", lat);
  antares.add("longitude", lon);

  // Publish and print data
  antares.publish(projectName, deviceName);
  delay(5000);
}
