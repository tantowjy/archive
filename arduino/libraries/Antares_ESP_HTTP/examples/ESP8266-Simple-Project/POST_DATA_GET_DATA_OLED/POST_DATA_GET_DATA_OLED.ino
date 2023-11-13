#include <AntaresESPHTTP.h>    // Include the AntaresESP8266HTTP library
#include <Adafruit_SSD1306.h>  // Include the Adafruit SSD1306 library
#include "DHT.h"               // Include the DHT sensor library

#define DHTPIN D1      // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11  // Type of DHT sensor (DHT11 in this case)

#define ACCESSKEY "YOUR-ACCESS-KEY"    // Replace with your Antares account access key
#define WIFISSID "YOUR-WIFI-SSID"      // Replace with your Wi-Fi SSID
#define PASSWORD "YOUR-WIFI-PASSWORD"  // Replace with your Wi-Fi password

#define projectName "YOUR-APPLICATION-NAME"     // Antares project name
#define deviceNameSensor "YOUR-DEVICE-NAME-1"   // Name of the device sending sensor data
#define deviceNamePostman "YOUR-DEVICE-NAME-2"  // Name of the device receiving data

AntaresESPHTTP antares(ACCESSKEY);  // Initialize AntaresESP8266HTTP with the access key
DHT dht(DHTPIN, DHTTYPE);           // Initialize DHT sensor object

#define SCREEN_WIDTH 128  // OLED screen width in pixels
#define SCREEN_HEIGHT 64  // OLED screen height in pixels
#define OLED_RESET -1     // Reset pin for the OLED (not used in this case)

const unsigned long interval = 5000;    // Interval to send sensor data (5 seconds)
const unsigned long interval2 = 10000;  // Interval to get data from Antares (10 seconds)
unsigned long previousMillis = 0;       // Store the last time sensor data was sent
unsigned long previousMillis2 = 0;      // Store the last time data was received from Antares

String testData;       // String to hold received data from Antares
String lastData = "";  // String to store last received data

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);  // Initialize OLED display object

bool showSensorData = true;  // Boolean to control display of sensor data

void setup() {
  Serial.begin(115200);                        // Initialize serial communication
  antares.setDebug(true);                      // Enable Antares library debug mode
  antares.wifiConnection(WIFISSID, PASSWORD);  // Connect to WiFi using provided SSID and password
  dht.begin();                                 // Initialize the DHT sensor

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Initialize the OLED display
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  display.clearDisplay();  // Clear the OLED display buffer
  display.display();       // Display the cleared buffer
}

void loop() {

  if (millis() - previousMillis > interval) {  // Check if it's time to send sensor data
    previousMillis = millis();                 // Update the last sent time

    float hum = dht.readHumidity();      // Read humidity from the DHT sensor
    float temp = dht.readTemperature();  // Read temperature from the DHT sensor
    if (isnan(hum) || isnan(temp)) {
      Serial.println("Failed to read DHT sensor!");  // Print an error message if sensor reading fails
      return;
    }
    antares.add("temperature", temp);                    // Add temperature data to the Antares payload
    antares.add("humidity", hum);                        // Add humidity data to the Antares payload
    antares.send(projectName, deviceNameSensor);         // Send sensor data to Antares
    display.clearDisplay();                              // Clear the OLED display buffer
    display.setTextSize(1);                              // Set text size on the display
    display.setTextColor(SSD1306_WHITE);                 // Set text color to white
    display.setCursor(0, 0);                             // Set cursor position on the display
    display.println("Temp: " + String(temp) + " *C");    // Display temperature
    display.println("Humidity: " + String(hum) + " %");  // Display humidity
    display.display();                                   // Display the updated buffer on the OLED
  }

  if (millis() - previousMillis2 > interval2) {  // Check if it's time to get data from Antares
    previousMillis2 = millis();                  // Update the last received time

    antares.get(projectName, deviceNamePostman);  // Get data from Antares

    if (antares.getSuccess()) {                   // Check if data retrieval was successful
      testData = antares.getString("Test Data");  // Get the "Test Data" field from the response

      if (lastData != testData)  // Check if the received data is different from the last one
      {
        lastData = testData;                           // Update the last received data
        Serial.println("Received Data: " + testData);  // Print received data to the serial monitor
        display.clearDisplay();                        // Clear the OLED display buffer
        display.setTextSize(1);                        // Set text size on the display
        display.setTextColor(SSD1306_WHITE);           // Set text color to white
        display.setCursor(0, 0);                       // Set cursor position on the display
        display.println("Received:");                  // Display "Received:"
        display.println(testData);                     // Display the received data
        display.display();                             // Display the updated buffer on the OLED
        delay(2000);                                   // Display received data for 2 seconds
      }
    }
  }
}
