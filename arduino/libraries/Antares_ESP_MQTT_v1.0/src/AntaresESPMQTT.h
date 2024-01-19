#ifndef AntaresESPMQTT_H
#define AntaresESPMQTT_H

#include <Arduino.h>
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include "PubSubClient.h"
#include "ArduinoJson.h"

class AntaresESPMQTT {

private:
    const char* _mqttServer = "mqtt.antares.id";
    const int _mqttPort = 1883;
    const int _secureMqttPort = 8883;
    bool _debug;
    String _accessKey;
    String _jsonDataString = "{}";
    String _jsonSubDataString;
    String _subscriptionTopic;
    String _receivedTopic;

public:
    AntaresESPMQTT(String accessKey);
    bool wifiConnection(String SSID, String wifiPassword);
    void setDebug(bool trueFalse);
    void printDebug(String text);
    String ipToString(IPAddress ip);
    /* Overloaded functions: Add data to temporary storage */
    void add(String key, int value);
    void add(String key, float value);
    void add(String key, double value);
    void add(String key, String value);
    /* Overloaded functions end */
    void printData();
    void publish(String projectName, String deviceName);
    void retrieveLastData(String projectName, String deviceName);
    /* Get subscription callback data*/
    int getInt(String key);
    float getFloat(String key);
    double getDouble(String key);
    String getString(String key);
    /* Get data end */

    String getTopic();
    String getPayload();

    void setMqttServer();
    void checkMqttConnection();
    void setCallback(std::function<void(char*, uint8_t*, unsigned int)> callbackFunc);
    String get(char* topic, byte* payload, unsigned int length);
};

#endif
