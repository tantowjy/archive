/*
  This code will fetch and print the latest data from your antares project device.
  For more information please visit https://antares.id/id/docs.html
*/

#include <AntaresESP32HTTP.h>

#define ACCESSKEY "your-access-key"
#define WIFISSID "your-wifi-ssid"
#define PASSWORD "your-wifi-password"

#define projectName "your-project-name"
#define deviceName "your-project-name"

AntaresESP32HTTP antares(ACCESSKEY);

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
