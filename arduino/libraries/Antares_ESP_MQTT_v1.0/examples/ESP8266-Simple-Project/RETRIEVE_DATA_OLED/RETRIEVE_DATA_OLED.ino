#include <AntaresESPMQTT.h>    // Import the AntaresESPMQTT library for communication with Antares
#include <Adafruit_SSD1306.h>  // Import the Adafruit_SSD1306 library for controlling the OLED display

#define ACCESSKEY "your-access-key"    // Replace with your Antares account access key
#define WIFISSID "your-wifi-ssid"      // Replace with your Wi-Fi SSID
#define PASSWORD "your-wifi-password"  // Replace with your Wi-Fi password

#define projectName "your-project-name"  // Antares project name
#define deviceName "your-project-name"   // Name of the device

AntaresESPMQTT antares(ACCESSKEY);  // Initialize the AntaresESPMQTT object with the access key

#define SCREEN_WIDTH 128  // OLED display width
#define SCREEN_HEIGHT 64  // OLED display height
#define OLED_RESET -1     // OLED display reset pin

String testData;       // Store received Postman data
String lastData = "";  // Store last received Postman data

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);  // Initialize the display object

void callback(char topic[], byte payload[], unsigned int length) {
  antares.get(topic, payload, length);

  Serial.println("New Message!");
  Serial.println("Topic: " + antares.getTopic());
  Serial.println("Payload: " + antares.getPayload());

  testData = antares.getString("Test");
  Serial.println("Received: " + testData);
  if (testData != "null") {
    if (lastData != testData) {
      lastData = testData;
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
  Serial.begin(115200);                        // Start serial communication at baud rate 115200
  antares.setDebug(true);                      // Enable debug mode for Antares
  antares.wifiConnection(WIFISSID, PASSWORD);  // Connect to Wi-Fi using SSID and password
  antares.setMqttServer();                     // Set up the Antares MQTT server
  antares.setCallback(callback);               // Set the callback function for MQTT messages

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Initialize the OLED display
    Serial.println(F("SSD1306 allocation failed"));  // Display a message if OLED initialization fails
    for (;;)
      ;  // Halt the program
  }

  display.clearDisplay();                  // Clear the OLED display
  display.setTextSize(1);                  // Set text size
  display.setTextColor(SSD1306_WHITE);     // Set text color
  display.setCursor(0, 0);                 // Set text cursor position
  display.println("Waiting for data...");  // Display initial message
  display.display();                       // Show the message on the display
}

void loop() {
  antares.checkMqttConnection();  // Check MQTT connection to Antares
}