// Library initialization
#include <AntaresESPMQTT.h>    // Library initiation for Antares ESP8266 MQTT
#include "DHT.h"               // Load DHT sensor library for reading temperature and humidity
#include <Adafruit_SSD1306.h>  // Load OLED display library

#define DHTPIN D1         // Define DHTPIN variable, pointing to pin D1
#define DHTTYPE DHT11     // Set DHT type to DHT11
#define SCREEN_WIDTH 128  // Define OLED screen width
#define SCREEN_HEIGHT 64  // Define OLED screen height

#define OLED_RESET -1        // Define OLED reset pin, set to -1 as it's not used
#define SCREEN_ADDRESS 0x3C  // Define OLED I2C address

#define ACCESSKEY "YOUR-ACCESS-KEY"    // Replace with your Antares account access key
#define WIFISSID "YOUR-WIFI-SSID"      // Replace with your Wi-Fi SSID
#define PASSWORD "YOUR-WIFI-PASSWORD"  // Replace with your Wi-Fi password

#define projectName "YOUR-APPLICATION-NAME"  // Replace with the Antares application name that was created
#define deviceName "YOUR-DEVICE-NAME"        // Replace with the Antares device name that was created

const unsigned long interval = 10000;  // 10 s interval to send message
unsigned long previousMillis = 0;      // will store last time message sent

AntaresESPMQTT antares(ACCESSKEY);                                         // Create an antares object for connecting to Antares
DHT dht(DHTPIN, DHTTYPE);                                                  // Create a dht object for the DHT sensor
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);  // Create a display object for the OLED screen

void setup() {
  Serial.begin(115200);                        // Initialize serial communication with baudrate 115200
  antares.setDebug(true);                      // Turn on debug mode. Set to "false" if you don't want messages to appear in the serial monitor
  antares.wifiConnection(WIFISSID, PASSWORD);  // Attempt to connect to Wi-Fi with the specified SSID and password
  antares.setMqttServer();
  dht.begin();  // Initialize the DHT sensor object

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));  // Check if the OLED is successfully initialized
    for (;;)
      ;
  }
  display.clearDisplay();                        // Clear the OLED display
  display.setTextColor(SSD1306_WHITE);           // Set text color to white
  display.setTextSize(1);                        // Set text size to 1
  display.setCursor(0, 0);                       // Set cursor position to (0, 0)
  display.println(F("Temperature & Humidity"));  // Display "Temperature & Humidity" text on the OLED
  display.display();                             // Show the text on the OLED
  delay(2000);                                   // Delay for 2 seconds
}

void loop() {
  antares.checkMqttConnection();
  // Check interval overflow
  if (millis() - previousMillis > interval) {
    previousMillis = millis();

    float hum = dht.readHumidity();                  // Read humidity value from the DHT sensor
    float temp = dht.readTemperature();              // Read temperature value from the DHT sensor
    if (isnan(hum) || isnan(temp)) {                 // Check if the sensor reading is invalid
      Serial.println("Failed to read DHT sensor!");  // If the reading is invalid, print an error message
      return;                                        // Exit the loop function and wait for the next cycle
    }
    display.clearDisplay();             // Clear the OLED display
    display.setTextSize(1);             // Set text size to 1
    display.setCursor(0, 0);            // Set cursor position to (0, 0)
    display.print(F("Temperature: "));  // Display "Temperature: " text on the OLED
    display.print(temp);                // Display temperature value on the OLED
    display.println(F(" C"));           // Display " C" (for Celsius) on the OLED
    display.print(F("Humidity: "));     // Display "Humidity: " text on the OLED
    display.print(hum);                 // Display humidity value on the OLED
    display.println(F(" %"));           // Display " %" (for percentage) on the OLED
    display.display();                  // Show the text on the OLED

    Serial.println("Temperature: " + (String)temp + " *C");  // Print temperature value to the serial monitor with "*C" format
    Serial.println("Humidity: " + (String)hum + " %");       // Print humidity value to the serial monitor with "%" format

    // Add variable data to the storage buffer in Antares
    antares.add("temperature", temp);
    antares.add("humidity", hum);

    // Send data from the storage buffer to Antares
    antares.publish(projectName, deviceName);
  }
}
