// Include necessary libraries
#include <AntaresESPMQTT.h> // Include the ESP32 HTTP library
#include <Adafruit_SSD1306.h> // Include the OLED library

// Replace these with your own credentials
#define ACCESSKEY "YOUR-ACCESS-KEY"       // Replace with your Antares account access key
#define WIFISSID "YOUR-WIFI-SSID"         // Replace with your Wi-Fi SSID
#define PASSWORD "YOUR-WIFI-PASSWORD"     // Replace with your Wi-Fi password

#define projectName "YOUR-APPLICATION-NAME"   // Replace with the Antares application name that was created
#define deviceName "YOUR-DEVICE-NAME"     // Replace with the Antares device name that was created

#define relayPin 25
#define ledPin 12

const unsigned long interval = 10000;    // 10 s interval to send message
unsigned long previousMillis = 0;  // will store last time message sent

AntaresESPMQTT antares(ACCESSKEY);

void callback(char topic[], byte payload[], unsigned int length) {
  antares.get(topic, payload, length);

  Serial.println("New Message!");
  Serial.println("Topic: " + antares.getTopic());
  Serial.println("Payload: " + antares.getPayload());

  String relayValue = antares.getString("Relay"); // Change data field to "Relay"
  String ledValue = antares.getString("LED");     // Add reading for "LED" data field
  // Control relay based on received data
  if (relayValue == "1") {
  digitalWrite(relayPin, HIGH);
  } 
  else if (relayValue == "0") {
  digitalWrite(relayPin, LOW);
  }

  // Control LED based on received data
  if (ledValue == "1") {
  digitalWrite(ledPin, HIGH);
  } 
  else if (ledValue == "0") {
  digitalWrite(ledPin, LOW);
  }

  Serial.println("Received data - Relay: " + relayValue + " | LED: " + ledValue);
  
}

void setup() {
    Serial.begin(115200); // Initialize serial communication
    antares.setDebug(true); // Enable debugging for Antares
    antares.wifiConnection(WIFISSID, PASSWORD); // Connect to WiFi
    antares.setMqttServer();
    antares.setCallback(callback);
    pinMode(relayPin, OUTPUT); // Set relayPin as an output
    pinMode(ledPin, OUTPUT); // Set ledPin as an output
}

void loop() {
 /*
    Check if we're still connected to the MQTT broker/server.
    If disconnected, the device will try to reconnect.
   */
  antares.checkMqttConnection();
}
