/*
  This code will send "Hello! " followed by an increasing number
  to your antares project device.
  For more information please visit https://antares.id/id/docs.html
*/

#include <AntaresESPHTTP.h>

#define ACCESSKEY "YOUR-ACCESS-KEY"       // Replace with your Antares account access key
#define WIFISSID "YOUR-WIFI-SSID"         // Replace with your Wi-Fi SSID
#define PASSWORD "YOUR-WIFI-PASSWORD"     // Replace with your Wi-Fi password

#define projectName "YOUR-APPLICATION-NAME"   // Replace with the Antares application name that was created
#define deviceName "YOUR-DEVICE-NAME"     // Replace with the Antares device name that was created

AntaresESPHTTP antares(ACCESSKEY);

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
