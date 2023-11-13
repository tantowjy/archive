#include <AntaresESPHTTP.h>
#include "DHT.h"            // Library initiation for DHT11 sensor
#define DHTPIN 14           // Create a variable DHTPIN, pointing to pin 14
#define DHTTYPE DHT11       // Specify the DHT type to be DHT11

#define ACCESSKEY "YOUR-ACCESS-KEY"       // Replace with your Antares account access key
#define WIFISSID "YOUR-WIFI-SSID"         // Replace with your Wi-Fi SSID
#define PASSWORD "YOUR-WIFI-PASSWORD"     // Replace with your Wi-Fi password

#define projectName "YOUR-APPLICATION-NAME"   // Replace with the Antares application name that was created
#define deviceName "YOUR-DEVICE-NAME"     // Replace with the Antares device name that was created

const unsigned long interval = 10000;    // 10 s interval to send message
unsigned long previousMillis = 0;  // will store last time message sent


AntaresESPHTTP antares(ACCESSKEY);    // Create an object for interacting with Antares
DHT dht(DHTPIN, DHTTYPE);   // Create an object for the DHT11 sensor

void setup() {
  Serial.begin(115200);     // Initialize serial communication with baudrate 115200
  antares.setDebug(true);   // Turn on debugging. Set to "false" if you don't want messages to appear on the serial monitor
  antares.wifiConnection(WIFISSID, PASSWORD);  // Attempt to connect to Wi-Fi
  dht.begin();             // Initialize the DHT11 sensor
}

void loop() {

  if (millis() - previousMillis > interval) {
  previousMillis = millis();
  
  float hum = dht.readHumidity();      // Read the humidity value from the DHT11 sensor
  float temp = dht.readTemperature();  // Read the temperature value from the DHT11 sensor
  if (isnan(hum) || isnan(temp)) {     // Check if there's an error reading the sensor
      Serial.println("Failed to read DHT sensor!");
      return;
  }
  Serial.println("Temperature: " + (String)temp + " *C");  // Print the temperature in Celsius
  Serial.println("Humidity: " + (String)hum + " %");       // Print the humidity as a percentage

  // Add the temperature and humidity data to the storage buffer
  antares.add("temperature", temp);
  antares.add("humidity", hum);
  
  // Send the data from the storage buffer to Antares
  antares.send(projectName, deviceName);

  }
}
