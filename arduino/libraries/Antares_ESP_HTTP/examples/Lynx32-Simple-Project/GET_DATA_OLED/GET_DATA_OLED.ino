#include <AntaresESPHTTP.h>
#include <Adafruit_SSD1306.h> // Include the OLED library

#define ACCESSKEY "YOUR-ACCESS-KEY"       // Replace with your Antares account access key
#define WIFISSID "YOUR-WIFI-SSID"         // Replace with your Wi-Fi SSID
#define PASSWORD "YOUR-WIFI-PASSWORD"     // Replace with your Wi-Fi password

#define projectName "YOUR-APPLICATION-NAME"   // Replace with the Antares application name that was created
#define deviceName "YOUR-DEVICE-NAME"     // Replace with the Antares device name that was created

const unsigned long interval = 10000;    // 10 s interval to send message
unsigned long previousMillis = 0;  // will store last time message sent

AntaresESPHTTP antares(ACCESSKEY);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1 // Change this if your OLED module has a different reset pin

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // Create an OLED display object

void setup() {
  Serial.begin(115200);
  antares.setDebug(true);
  antares.wifiConnection(WIFISSID, PASSWORD);

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  // Clear the buffer and display the initial message
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Hallo Test");
  display.display();
  delay(2000); // Display the message for 2 seconds
}

void loop() {
   if (millis() - previousMillis > interval) {
    previousMillis = millis();
    
  // Get the latest data from your Antares device
  antares.get(projectName, deviceName);

  // Check if we're actually getting data
  if(antares.getSuccess()) {
  String test = antares.getString("Test");
  
  // Update the OLED display
  Serial.println("Received : " + test);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Received:" + test);
  display.display();
  }
  
  }
}
