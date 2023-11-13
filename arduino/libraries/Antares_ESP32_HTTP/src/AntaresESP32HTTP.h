#ifndef AntaresESP32HTTP_H
#define AntaresESP32HTTP_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>

static const char* test_root_ca= \
    "-----BEGIN CERTIFICATE-----\n" \
    "MIIDdTCCAl2gAwIBAgILBAAAAAABFUtaw5QwDQYJKoZIhvcNAQEFBQAwVzELMAkG\n" \
    "A1UEBhMCQkUxGTAXBgNVBAoTEEdsb2JhbFNpZ24gbnYtc2ExEDAOBgNVBAsTB1Jv\n" \
    "b3QgQ0ExGzAZBgNVBAMTEkdsb2JhbFNpZ24gUm9vdCBDQTAeFw05ODA5MDExMjAw\n" \
    "MDBaFw0yODAxMjgxMjAwMDBaMFcxCzAJBgNVBAYTAkJFMRkwFwYDVQQKExBHbG9i\n" \
    "YWxTaWduIG52LXNhMRAwDgYDVQQLEwdSb290IENBMRswGQYDVQQDExJHbG9iYWxT\n" \
    "aWduIFJvb3QgQ0EwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDaDuaZ\n" \
    "jc6j40+Kfvvxi4Mla+pIH/EqsLmVEQS98GPR4mdmzxzdzxtIK+6NiY6arymAZavp\n" \
    "xy0Sy6scTHAHoT0KMM0VjU/43dSMUBUc71DuxC73/OlS8pF94G3VNTCOXkNz8kHp\n" \
    "1Wrjsok6Vjk4bwY8iGlbKk3Fp1S4bInMm/k8yuX9ifUSPJJ4ltbcdG6TRGHRjcdG\n" \
    "snUOhugZitVtbNV4FpWi6cgKOOvyJBNPc1STE4U6G7weNLWLBYy5d4ux2x8gkasJ\n" \
    "U26Qzns3dLlwR5EiUWMWea6xrkEmCMgZK9FGqkjWZCrXgzT/LCrBbBlDSgeF59N8\n" \
    "9iFo7+ryUp9/k5DPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNVHRMBAf8E\n" \
    "BTADAQH/MB0GA1UdDgQWBBRge2YaRQ2XyolQL30EzTSo//z9SzANBgkqhkiG9w0B\n" \
    "AQUFAAOCAQEA1nPnfE920I2/7LqivjTFKDK1fPxsnCwrvQmeU79rXqoRSLblCKOz\n" \
    "yj1hTdNGCbM+w6DjY1Ub8rrvrTnhQ7k4o+YviiY776BQVvnGCv04zcQLcFGUl5gE\n" \
    "38NflNUVyRRBnMRddWQVDf9VMOyGj/8N7yy5Y0b2qvzfvGn9LhJIZJrglfCm7ymP\n" \
    "AbEVtQwdpf5pLGkkeB6zpxxxYu7KyJesF12KwvhHhm4qxFYxldBniYUr+WymXUad\n" \
    "DKqC5JlR3XC321Y9YeRq4VzW9v493kHMB65jUr9TU/Qr6cf9tveCX4XSQRjbgbME\n" \
    "HMUfpIBvFSDJ3gyICh3WZlXi/EjJKSZp4A==\n" \
    "-----END CERTIFICATE-----\n";


class AntaresESP32HTTP {

public:
    AntaresESP32HTTP(String accessKey);
    String createDevice(String projectName, String deviceName);
    String retrieveAllDevice(String projectName,int limit=0);
    String storeData(String projectName, String deviceName, String nameData[], String valueData[], int sizeParameter);
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
    String retrieveAllData(String projectName, String deviceName,int limit=0);
    String retrieveLatestData(String projectName, String deviceName);
    void get(String projectName, String deviceName);
    String getRaw(String projectName, String deviceName);
    String getRawNonSecure(String projectName, String deviceName);
    void getNonSecure(String projectName, String deviceName);
    void getTest(String projectName, String deviceName);
    void getLatestTest(String projectName, String deviceName);

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
    void setServer(String domain,String port);
    void setAntaresCse(String nameAntaresCse);
    void setAntaresId(String nameAntaresId);

    void measureSize();
    void measureGetSize();
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
    char* _wifiSSID;
    char* _wifiPass;
    bool _debug=false;
    bool _getSuccess;
    char* tempDebug;
    String jsonString = "{}";
    String jsonGetString;
    String _currentKey;
};

#endif
