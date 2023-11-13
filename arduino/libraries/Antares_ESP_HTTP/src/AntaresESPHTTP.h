#ifndef AntaresESPHTTP_H
#define AntaresESPHTTP_H

#include <Arduino.h>
#include <ArduinoJson.h>
#if defined(ESP32)
#include <WiFi.h>
#include <HTTPClient.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#endif
#include <WiFiClientSecure.h>
#include "AntaresCerts.h"

class AntaresESPHTTP {

public:
    AntaresESPHTTP(String accessKey);
    /*
      Overloaded functions start
      Antares::add()

      These functions are meant to push data into the
      JSON buffer string
    */
    void add(String key, String value);
    void add(String key, int value);
    void add(String key, float value);
    void add(String key, double value);

    // 2-level nested json
    void add(String key, String key2, String value);
    void add(String key, String key2, int value);
    void add(String key, String key2, float value);
    void add(String key, String key2, double value);

    /* Overloaded functions end */
    void send(String projectName, String deviceName); // Store data in buffer to database
    void sendRaw(String text, String projectName, String deviceName); // Store data in buffer to database
    void sendRawNonSecure(String text, String projectName, String deviceName); // Store data in buffer to database
    void sendNonSecure(String projectName, String deviceName); // Store data in buffer to database
    void printData(); // Print waiting list data to serial monitor
    void get(String projectName, String deviceName);
    String getRaw(String projectName, String deviceName);
    String getRawNonSecure(String projectName, String deviceName);
    void getNonSecure(String projectName, String deviceName);

    /*
      Antares::get() functions

      These functions are meant to fetch data from the
      JSON buffer.
    */
    String getString(String key);
    int getInt(String key);
    float getFloat(String key);
    double getDouble(String key);

    // 2-level nested json
    String getString(String key, String key2);
    int getInt(String key, String key2);
    float getFloat(String key, String key2);
    double getDouble(String key, String key2);

    /* Overloaded functions end */
    bool getSuccess();
    bool wifiConnection(String SSID, String wifiPassword);
    bool checkWifiConnection();
    void setDebug(bool trueFalse);

private:
    void printDebug(String text);
    String ipToString(IPAddress ip);
    String _accessKey;
    String _server = "http://platform.antares.id";
    String _serverNoHttp = "platform.antares.id";
    const char* _serverChar = "platform.antares.id";
    String _port = "8080";
    uint16_t _portNum = 8080;
    String _antaresCse = "antares-cse";
    String _antaresId = "antares-id";
    String _wifiSSID;
    String _wifiPass;
    bool _debug=false;
    bool _getSuccess;
    char* tempDebug;
    String jsonString = "{}";
    String jsonGetString;
    String _currentKey;
};

#endif
