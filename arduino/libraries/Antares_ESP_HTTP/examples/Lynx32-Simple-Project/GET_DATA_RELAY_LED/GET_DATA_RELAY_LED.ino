#include <AntaresESPHTTP.h>     // Include the AntaresESP32HTTP library

#define ACCESSKEY "YOUR-ACCESS-KEY"       // Replace with your Antares account access key
#define WIFISSID "YOUR-WIFI-SSID"         // Replace with your Wi-Fi SSID
#define PASSWORD "YOUR-WIFI-PASSWORD"     // Replace with your Wi-Fi password

#define projectName "YOUR-APPLICATION-NAME"   // Replace with the Antares application name that was created
#define deviceName "YOUR-DEVICE-NAME"     // Replace with the Antares device name that was created

AntaresESPHTTP antares(ACCESSKEY);   // Initialize AntaresESP32HTTP with the access key

#define relayPin  25    // Digital pin for controlling the relay
#define ledPin  12      // Digital pin for controlling the LED

const unsigned long interval = 10000;    // 10 seconds interval to send message
unsigned long previousMillis = 0;  // Will store the last time a message was sent

void setup() {
    Serial.begin(115200);   // Initialize serial communication
    antares.setDebug(true);  // Enable Antares library debug mode
    antares.wifiConnection(WIFISSID, PASSWORD);  // Connect to WiFi using provided SSID and password

    pinMode(relayPin, OUTPUT);  // Set relay pin as output
    pinMode(ledPin, OUTPUT);    // Set LED pin as output
}

void loop() {

    if (millis() - previousMillis > interval) {  // Check if it's time to send a message
        previousMillis = millis();               // Update the last sent time
        
        antares.get(projectName, deviceName);    // Get data from Antares
        
        if (antares.getSuccess()) {              // Check if data retrieval was successful
            String dataValue = antares.getString("Relay");  // Get the value of "Relay" data field
            String ledValue = antares.getString("LED");      // Get the value of "LED" data field

            // Control relay based on received data
            if (dataValue == "1") {
                digitalWrite(relayPin, HIGH);  // Turn on the relay
            } else if (dataValue == "0") {
                digitalWrite(relayPin, LOW);   // Turn off the relay
            }

            // Control LED based on received data
            if (ledValue == "1") {
                digitalWrite(ledPin, HIGH);    // Turn on the LED
            } else if (ledValue == "0") {
                digitalWrite(ledPin, LOW);     // Turn off the LED
            }

            Serial.println("Received data - Relay: " + dataValue + " | LED: " + ledValue);
        }
    }
}
