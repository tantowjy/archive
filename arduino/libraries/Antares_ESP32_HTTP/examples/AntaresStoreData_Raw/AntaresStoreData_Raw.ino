/*
  This code will send "Hello! " followed by an increasing number
  to your antares project device.
  For more information please visit https://antares.id/id/docs.html
*/

#include <AntaresESP32HTTP.h>

#define ACCESSKEY "your-access-key"
#define WIFISSID "your-wifi-ssid"
#define PASSWORD "your-wifi-password"

#define projectName "your-project-name"
#define deviceName "your-project-name"

AntaresESP32HTTP antares(ACCESSKEY);

int counter = 0;

void setup() {
  Serial.begin(115200);
  antares.setDebug(true);
  antares.wifiConnection(WIFISSID, PASSWORD);
}

void loop() {
  String text = "Hello! ";
  text += String(counter);
  Serial.println(text); // Print data to serial monitor
  antares.sendRaw(text, projectName, deviceName); // Store data from your Antares device
  counter++;
  delay(5000);
}
