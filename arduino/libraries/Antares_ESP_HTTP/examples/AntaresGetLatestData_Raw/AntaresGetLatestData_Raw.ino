/*
  This code will fetch and print the latest data from your antares project device.
  For more information please visit https://antares.id/id/docs.html
*/

#include <AntaresESPHTTP.h>

#define ACCESSKEY "YOUR-ACCESS-KEY"       // Replace with your Antares account access key
#define WIFISSID "YOUR-WIFI-SSID"         // Replace with your Wi-Fi SSID
#define PASSWORD "YOUR-WIFI-PASSWORD"     // Replace with your Wi-Fi password

#define projectName "YOUR-APPLICATION-NAME"   // Replace with the Antares application name that was created
#define deviceName "YOUR-DEVICE-NAME"     // Replace with the Antares device name that was created

AntaresESPHTTP antares(ACCESSKEY);

void setup() {
    Serial.begin(115200);
    antares.setDebug(true);
    antares.wifiConnection(WIFISSID, PASSWORD);
}

void loop() {
  // Get the latest data from your Antares device
  String data = antares.getRaw(projectName, deviceName);
  Serial.println(data);
  delay(5000);
}
