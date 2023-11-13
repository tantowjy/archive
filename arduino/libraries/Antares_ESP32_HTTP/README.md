# Antares ESP32 HTTP  
<img src="http://i64.tinypic.com/2gsmuxc.jpg" width="300">  
This is the documentation for Antares ESP32 library.  

This library is meant to simplify the process of retrieving and deploying data to Antares IoT Platform's REST API using ESP32 with Arduino framework.  

This library has been tested with Arduino ESP32 version 1.0.1.

For dependencies, this library uses [bblanchon's ArduinoJson v5](https://github.com/bblanchon/ArduinoJson) and is already included in the bundle.    

For more information regarding the platform itself, please visit Antares' [official website](https://antares.id/).

## Installation  
**Arduino IDE** <img src="https://camo.githubusercontent.com/647cefc4a331bc5ab2a760d3c731b9d0b3f1259b/68747470733a2f2f7777772e61726475696e6f2e63632f66617669636f6e2e69636f" width="20">  
1. Install ESP32 Core for Arduino. For more information please refer to the ESP32 for Arduino's [installation manual](https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md)
2. Download the latest release and add this library into Arduino IDE (Sketch > Include Library > Add .ZIP Library...)  

## Examples
Please note that `AntaresStoreSecure` and `AntaresGetLatestSecure` are preferred than `AntaresStoreData` and `AntaresGetLatestSecure` because they use HTTPS (port 8443) rather than HTTP (port 8080).  

* **AntaresGetLatestData** - Fetch the latest data stored in a project device
* **AntaresGetLatestSecure** - Fetch the latest data stored in a project device through HTTPS  
* **AntaresStoreData** - Deploy data into a project device
* **AntaresStoreSecure** - Deploy data into a project device through HTTPS  

## API Reference

> Class `AntaresESP32HTTP`  

All methods and properties need to be insantiated in order to use them.

### Constructor
* `AntaresESP32HTTP(String ACCESSKEY)`
The constructor of class `AntaresESP32HTTP`. Put your Antares account access key as the parameter. The access key should be an Arduino `String` datatype.

### Get Latest Data
* `void get(String projectName, String deviceName)`  
**(Not recommended)** Fetch the latest data from your Antares project device through HTTP port 8080 (non-secure).   
The data will be stored in the `jsonGetString` property of class `AntaresESP32HTTP`  

* `void getSecure(String projectName, String deviceName)`  
**(Recommended)** Fetch the latest data from your Antares project device through HTTPS port 8443 (secure).   
The data will be stored in the `jsonGetString` property of class `AntaresESP32HTTP`  

* `void getSuccess()`  
Check if the latest data is successfully received.

* `String getString(String key)` or `String getString(String key, String key2)`     
Get `String` data by accessing the JSON `key` from `jsonGetString`.  

* `int getInt(String key)` or `int getInt(String key, String key2)`  
Get `int` data by accessing the JSON `key` from `jsonGetString`.  

* `float getFloat(String key)` or `float getFloat(String key, String key2)`  
Get `float` data by accessing the JSON `key` from `jsonGetString`.  

* `double getDouble(String key)` or `double getDouble(String key, String key2)`  
Get `double` data by accessing the JSON `key` from `jsonGetString`.  

### Store Data
* `void add(String key, value)` or `void add(String key, String key2, value)`   
Insert a JSON key-value data to the property `jsonString` of class `AntaresESP32HTTP`. The `value` parameter is overloaded. The supported data types for the value parameter are:
    * `String`
    * `int`
    * `float`
    * `double`  

* `void send(String projectName, String deviceName)`    
**(Not recommended)** Send the data stored in `jsonString` property of class `AntaresESP32HTTP` through HTTP port 8080 (non-secure).  

* `void sendSecure(String projectName, String deviceName)`  
**(Recommended)** Send the data stored in `jsonString` property of class `AntaresESP32HTTP` through HTTPS port 8443 (secure).  

<img src="https://upload.wikimedia.org/wikipedia/id/thumb/c/c4/Telkom_Indonesia_2013.svg/1200px-Telkom_Indonesia_2013.svg.png" width="200">  

**Powered by Telkom Indonesia**
