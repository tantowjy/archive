#include <NTPClient.h>
#include <WiFiUdp.h>
#include <WiFi.h>

#define AOUT_PIN 15 // ESP32 pin GPIO36 (ADC0) that connects to AOUT pin of moisture sensor

// Replace with your network credentials
const char *ssid     = "PQR";
const char *password = "12345678";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

// Initialize a NTPClient to get time
  timeClient.begin();
  timeClient.setTimeOffset(0);
}

void loop() {
  timeClient.update();

  int currentHour = timeClient.getHours();
  Serial.print("Hour: ");
  Serial.println(currentHour);  

  int currentMinute = timeClient.getMinutes();
  Serial.print("Minutes: ");
  Serial.println(currentMinute); 
   
  int currentSecond = timeClient.getSeconds();
  Serial.print("Seconds: ");
  Serial.println(currentSecond);  

  int value = analogRead(AOUT_PIN); // read the analog value from sensor

  Serial.print("Moisture value: ");
  Serial.println(value);

  delay(2000);
}