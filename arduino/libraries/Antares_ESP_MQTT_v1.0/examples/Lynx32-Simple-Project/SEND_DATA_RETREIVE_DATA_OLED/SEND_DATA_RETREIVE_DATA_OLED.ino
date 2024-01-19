// Include necessary libraries
#include <AntaresESPMQTT.h>   // Include AntaresESP32HTTP library for Antares platform communication
#include <Adafruit_SSD1306.h>   // Include Adafruit_SSD1306 library for OLED display
#include "DHT.h"               // Include DHT library for temperature and humidity sensor

#define DHTPIN 14               // Define the pin connected to the DHT sensor
#define DHTTYPE DHT11           // Set the DHT sensor type as DHT11

#define ACCESSKEY "YOUR-ACCESS-KEY"       // Replace with your Antares account access key
#define WIFISSID "YOUR-WIFI-SSID"         // Replace with your Wi-Fi SSID
#define PASSWORD "YOUR-WIFI-PASSWORD"     // Replace with your Wi-Fi password

#define projectName "YOUR-APPLICATION-NAME"          // Antares project name
#define deviceNameSensor "YOUR-DEVICE-NAME-1"   // Name of the device sending sensor data
#define deviceNameMQTT "YOUR-DEVICE-NAME-2"     // Name of the device receiving data

AntaresESPMQTT antares(ACCESSKEY); // Create AntaresESP32HTTP object
DHT dht(DHTPIN, DHTTYPE);            // Create DHT object for sensor readings

#define SCREEN_WIDTH 128          // Set OLED screen width
#define SCREEN_HEIGHT 64          // Set OLED screen height
#define OLED_RESET -1             // Define OLED reset pin, not used in this case

const unsigned long interval = 5000; // Interval for sending sensor data (5 seconds)
const unsigned long interval2 = 10000; // Interval for receiving Postman data (10 seconds)
unsigned long previousMillis = 0;     // Store the last time sensor data was sent
unsigned long previousMillis2 = 0;    // Store the last time Postman data was received

String testData;             // Store received Postman data
String lastData = "";        // Store last received Postman data

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // Create OLED display object

bool showSensorData = true;  // Flag to control displaying sensor data

void callback(char topic[], byte payload[], unsigned int length) {
  antares.get(topic, payload, length);

  Serial.println("New Message!");
  Serial.println("Topic: " + antares.getTopic());
  Serial.println("Payload: " + antares.getPayload());

  testData = antares.getString("Test");
  Serial.println("Received: " + testData);
  if (testData!="null")
  {
    if (lastData!=testData)
    {
      lastData=testData;
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 0);
      display.println("Received: " + testData);
      display.display();
    }
  }
}

void setup() {
  Serial.begin(115200);                 // Initialize serial communication
  antares.setDebug(true);               // Enable debugging for Antares
  antares.wifiConnection(WIFISSID, PASSWORD);
  antares.setMqttServer();
  antares.setCallback(callback);

  dht.begin();                          // Initialize DHT sensor

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Initialize OLED display
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  display.clearDisplay();               // Clear the display buffer
  display.display();                    // Display the cleared buffer
}

void loop() {
   /*
    Check if we're still connected to the MQTT broker/server.
    If disconnected, the device will try to reconnect.
   */
  antares.checkMqttConnection();
  // Send sensor data
  if (millis() - previousMillis > interval) {
    previousMillis = millis();

    float hum = dht.readHumidity();      // Read humidity from DHT sensor
    float temp = dht.readTemperature();  // Read temperature from DHT sensor

    if (isnan(hum) || isnan(temp)) {     // Check if sensor reading is valid
      Serial.println("Failed to read DHT sensor!");
      return;
    }

    // Add temperature and humidity data to the storage buffer
    antares.add("temperature", temp);
    antares.add("humidity", hum);

    // Send data from the storage buffer to Antares
    antares.publish(projectName, deviceNameSensor);

    // Display temperature and humidity on OLED
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Temp: " + String(temp) + " *C");
    display.println("Humidity: " + String(hum) + " %");
    display.display();
  }
  
  // Receive and display latest data
  if (millis() - previousMillis2 > interval2) {
    previousMillis2 = millis();
    antares.retrieveLastData(projectName,deviceNameMQTT);
   }
}
