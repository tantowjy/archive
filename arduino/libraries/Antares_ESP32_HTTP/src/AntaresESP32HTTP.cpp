#include "AntaresESP32HTTP.h"

AntaresESP32HTTP::AntaresESP32HTTP(String accessKey) {
    _accessKey = accessKey;
}

void AntaresESP32HTTP::getNonSecure(String projectName, String deviceName) {

    jsonGetString = "";
    _getSuccess = false;
    printDebug("[ANTARES] Connecting to " + _serverNoHttp + "\n");

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 8080;
    if (!client.connect(_serverChar, httpPort)) {
        printDebug("[ANTARES] Connection failed!\n");
        return;
    }

    // We now create a URI for the request
    String url = "/~/antares-cse/antares-id/"+ projectName +"/"+ deviceName +"/la";

    printDebug("Requesting URL: " + url + "\n");

    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + _serverNoHttp + "\r\n" +
                 "X-M2M-Origin: "+ _accessKey +"\r\n" +
                 "Content-Type: application/json;ty=4\r\n" +
                 "Accept: application/json\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println("[ANTARES] Client Timeout !\n");
            client.stop();
            return;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    while(client.available()) {
        while(client.read() != '{');
        String line = "{";
        line += client.readStringUntil('\r');
        DynamicJsonBuffer jsonBuffer;
        JsonObject& object = jsonBuffer.parseObject(line);
        String receivedData = object["m2m:cin"]["con"];
        JsonObject& dataJson = jsonBuffer.parseObject(receivedData);

        if(_debug) {
            dataJson.printTo(jsonGetString);
            dataJson.prettyPrintTo(Serial);
        }
    }

    printDebug("\n[ANTARES] Closing connection...\n");
    _getSuccess = true;
}

void AntaresESP32HTTP::get(String projectName, String deviceName) {

    jsonGetString = "";
    _getSuccess = false;
    printDebug("[ANTARES] Connecting to " + _serverNoHttp + "\n");

    // Use WiFiClient class to create TCP connections
    WiFiClientSecure client;

    client.setCACert(test_root_ca);

    const int httpPort = 8443;
    if (!client.connect(_serverChar, httpPort)) {
        printDebug("[ANTARES] Connection failed!\n");
        return;
    }

    // We now create a URI for the request
    String url = "/~/antares-cse/antares-id/"+ projectName +"/"+ deviceName +"/la";

    printDebug("Requesting URL: " + url + "\n");

    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + _serverNoHttp + "\r\n" +
                 "X-M2M-Origin: "+ _accessKey +"\r\n" +
                 "Content-Type: application/json;ty=4\r\n" +
                 "Accept: application/json\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println("[ANTARES] Client Timeout !\n");
            client.stop();
            return;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    while(client.available()) {
        while(client.read() != '{');
        String line = "{";
        line += client.readStringUntil('\r');
        DynamicJsonBuffer jsonBuffer;
        JsonObject& object = jsonBuffer.parseObject(line);
        String receivedData = object["m2m:cin"]["con"];
        JsonObject& dataJson = jsonBuffer.parseObject(receivedData);

        if(_debug) {
            dataJson.printTo(jsonGetString);
            dataJson.prettyPrintTo(Serial);
        }
    }

    printDebug("\n[ANTARES] Closing connection...\n");
    _getSuccess = true;
}

String AntaresESP32HTTP::getRaw(String projectName, String deviceName) {

    jsonGetString = "";
    _getSuccess = false;
    printDebug("[ANTARES] Connecting to " + _serverNoHttp + "\n");

    // Use WiFiClient class to create TCP connections
    WiFiClientSecure client;

    client.setCACert(test_root_ca);

    const int httpPort = 8443;
    if (!client.connect(_serverChar, httpPort)) {
        printDebug("[ANTARES] Connection failed!\n");
        return "Conn failed";
    }

    // We now create a URI for the request
    String url = "/~/antares-cse/antares-id/"+ projectName +"/"+ deviceName +"/la";

    printDebug("Requesting URL: " + url + "\n");

    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + _serverNoHttp + "\r\n" +
                 "X-M2M-Origin: "+ _accessKey +"\r\n" +
                 "Content-Type: application/json;ty=4\r\n" +
                 "Accept: application/json\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println("[ANTARES] Client Timeout !\n");
            client.stop();
            return "Timeout";
        }
    }

    String payload = "";
    // Read all the lines of the reply from server and print them to Serial
    while(client.available()) {
        while(client.read() != '{');
        String line = "{";
        line += client.readStringUntil('\r');
        DynamicJsonBuffer jsonBuffer;
        JsonObject& object = jsonBuffer.parseObject(line);
        String receivedData = object["m2m:cin"]["con"];
        payload = receivedData;
    }

    printDebug("\n[ANTARES] Closing connection...\n");
    _getSuccess = true;
    return payload;
}

String AntaresESP32HTTP::getRawNonSecure(String projectName, String deviceName) {
    jsonGetString = "";
    _getSuccess = false;
    printDebug("[ANTARES] Connecting to " + _serverNoHttp + "\n");

    // Use WiFiClient class to create TCP connections
    WiFiClient client;

    const int httpPort = 8443;
    if (!client.connect(_serverChar, _portNum)) {
        printDebug("[ANTARES] Connection failed!\n");
        return "Conn failed";
    }

    // We now create a URI for the request
    String url = "/~/antares-cse/antares-id/"+ projectName +"/"+ deviceName +"/la";

    printDebug("Requesting URL: " + url + "\n");

    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + _serverNoHttp + "\r\n" +
                 "X-M2M-Origin: "+ _accessKey +"\r\n" +
                 "Content-Type: application/json;ty=4\r\n" +
                 "Accept: application/json\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println("[ANTARES] Client Timeout !\n");
            client.stop();
            return "Timeout";
        }
    }

    String payload = "";
    // Read all the lines of the reply from server and print them to Serial
    while(client.available()) {
        while(client.read() != '{');
        String line = "{";
        line += client.readStringUntil('\r');
        DynamicJsonBuffer jsonBuffer;
        JsonObject& object = jsonBuffer.parseObject(line);
        String receivedData = object["m2m:cin"]["con"];
        payload = receivedData;
    }

    printDebug("\n[ANTARES] Closing connection...\n");
    _getSuccess = true;
    return payload;
}

bool AntaresESP32HTTP::getSuccess() {
    return _getSuccess;
}

void AntaresESP32HTTP::sendNonSecure(String projectName, String deviceName) {
    printDebug("[ANTARES] Connecting to " + _serverNoHttp + "\n");

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 8080;
    if (!client.connect(_serverChar, httpPort)) {
        printDebug("[ANTARES] Connection failed!\n");
        return;
    }

    // We now create a URI for the request
    String url = "/~/antares-cse/antares-id/"+ projectName + "/" + deviceName;

    jsonString.replace("\"", "\\\"");

    String body;
    body += "{";
    body += "\"m2m:cin\": {";
    body += "\"con\": \"" + jsonString + "\"";
    body += "}";
    body += "}";

    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(body);

    printDebug("Requesting URL: " + url + "\n");

    String req = "";
    req += "POST " + url + " HTTP/1.1\r\n";
    req += "Host: " + _serverNoHttp + "\r\n";
    req += "X-M2M-Origin: "+ _accessKey +"\r\n";
    req += "Accept: application/json\r\n";
    req += "Connection: close\r\n";
    req += "Content-Type: application/json;ty=4\r\n";
    req += "Content-Length:"+ String(body.length()) +"\r\n";
    req += "\r\n";
    req += body + "\r\n";

    // This will send the request to the server
    client.print(req);
    if(_debug) {
        Serial.println(req);
    }


    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println("[ANTARES] Client Timeout !\n");
            client.stop();
            return;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    String line = "";

    while(client.available()) {
        line += client.readStringUntil('\r');
    }

    // Check if response is successful
    if(line.indexOf("HTTP/1.1 201 Created") >= 0) {
        printDebug("[ANTARES] Created! Response: 201\n");
    }
    else {
        printDebug("[ANTARES] Creating data failed!\n");
    }

    printDebug("\n[ANTARES] Closing connection...\n");
    jsonString = "{}";
    _currentKey = "";
}

void AntaresESP32HTTP::send(String projectName, String deviceName) {
    printDebug("[ANTARES] Connecting to " + _serverNoHttp + "\n");

    // Use WiFiClient class to create TCP connections
    WiFiClientSecure client;

    client.setCACert(test_root_ca);

    const int httpPort = 8443;
    if (!client.connect(_serverChar, httpPort)) {
        printDebug("[ANTARES] Connection failed!\n");
        return;
    }

    // We now create a URI for the request
    String url = "/~/antares-cse/antares-id/"+ projectName + "/" + deviceName;

    jsonString.replace("\"", "\\\"");

    String body;
    body += "{";
    body += "\"m2m:cin\": {";
    body += "\"con\": \"" + jsonString + "\"";
    body += "}";
    body += "}";

    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(body);

    printDebug("Requesting URL: " + url + "\n");

    String req = "";
    req += "POST " + url + " HTTP/1.1\r\n";
    req += "Host: " + _serverNoHttp + "\r\n";
    req += "X-M2M-Origin: "+ _accessKey +"\r\n";
    req += "Accept: application/json\r\n";
    req += "Connection: close\r\n";
    req += "Content-Type: application/json;ty=4\r\n";
    req += "Content-Length:"+ String(body.length()) +"\r\n";
    req += "\r\n";
    req += body + "\r\n";

    // This will send the request to the server
    client.print(req);
    if(_debug) {
        Serial.println(req);
    }


    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println("[ANTARES] Client Timeout !\n");
            client.stop();
            return;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    String line = "";

    while(client.available()) {
        line += client.readStringUntil('\r');
    }

    // Check if response is successful
    if(line.indexOf("HTTP/1.1 201 Created") >= 0) {
        printDebug("[ANTARES] Created! Response: 201\n");
    }
    else {
        printDebug("[ANTARES] Creating data failed!\n");
    }

    printDebug("\n[ANTARES] Closing connection...\n");
    jsonString = "{}";
    _currentKey = "";
}

void AntaresESP32HTTP::sendRaw(String text, String projectName, String deviceName) {
    printDebug("[ANTARES] Connecting to " + _serverNoHttp + "\n");

    // Use WiFiClient class to create TCP connections
    WiFiClientSecure client;

    client.setCACert(test_root_ca);

    const int httpPort = 8443;
    if (!client.connect(_serverChar, httpPort)) {
        printDebug("[ANTARES] Connection failed!\n");
        return;
    }

    // We now create a URI for the request
    String url = "/~/antares-cse/antares-id/"+ projectName + "/" + deviceName;

    jsonString.replace("\"", "\\\"");

    String body;
    body += "{";
    body += "\"m2m:cin\": {";
    body += "\"con\": \"" + text + "\"";
    body += "}";
    body += "}";

    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(body);

    printDebug("Requesting URL: " + url + "\n");

    String req = "";
    req += "POST " + url + " HTTP/1.1\r\n";
    req += "Host: " + _serverNoHttp + "\r\n";
    req += "X-M2M-Origin: "+ _accessKey +"\r\n";
    req += "Accept: application/json\r\n";
    req += "Connection: close\r\n";
    req += "Content-Type: application/json;ty=4\r\n";
    req += "Content-Length:"+ String(body.length()) +"\r\n";
    req += "\r\n";
    req += body + "\r\n";

    // This will send the request to the server
    client.print(req);
    if(_debug) {
        Serial.println(req);
    }

    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println("[ANTARES] Client Timeout !\n");
            client.stop();
            return;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    String line = "";

    while(client.available()) {
        line += client.readStringUntil('\r');
    }

    // Check if response is successful
    if(line.indexOf("HTTP/1.1 201 Created") >= 0) {
        printDebug("[ANTARES] Created! Response: 201\n");
    }
    else {
        printDebug("[ANTARES] Creating data failed!\n");
    }

    printDebug("\n[ANTARES] Closing connection...\n");
    jsonString = "{}";
    _currentKey = "";
}

void AntaresESP32HTTP::sendRawNonSecure(String text, String projectName, String deviceName) {
    printDebug("[ANTARES] Connecting to " + _serverNoHttp + "\n");

    // Use WiFiClient class to create TCP connections
    WiFiClient client;

    const int httpPort = 8443;
    if (!client.connect(_serverChar, _portNum)) {
        printDebug("[ANTARES] Connection failed!\n");
        return;
    }

    // We now create a URI for the request
    String url = "/~/antares-cse/antares-id/"+ projectName + "/" + deviceName;

    jsonString.replace("\"", "\\\"");

    String body;
    body += "{";
    body += "\"m2m:cin\": {";
    body += "\"con\": \"" + text + "\"";
    body += "}";
    body += "}";

    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(body);

    printDebug("Requesting URL: " + url + "\n");

    String req = "";
    req += "POST " + url + " HTTP/1.1\r\n";
    req += "Host: " + _serverNoHttp + "\r\n";
    req += "X-M2M-Origin: "+ _accessKey +"\r\n";
    req += "Accept: application/json\r\n";
    req += "Connection: close\r\n";
    req += "Content-Type: application/json;ty=4\r\n";
    req += "Content-Length:"+ String(body.length()) +"\r\n";
    req += "\r\n";
    req += body + "\r\n";

    // This will send the request to the server
    client.print(req);
    if(_debug) {
        Serial.println(req);
    }

    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println("[ANTARES] Client Timeout !\n");
            client.stop();
            return;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    String line = "";

    while(client.available()) {
        line += client.readStringUntil('\r');
    }

    // Check if response is successful
    if(line.indexOf("HTTP/1.1 201 Created") >= 0) {
        printDebug("[ANTARES] Created! Response: 201\n");
    }
    else {
        printDebug("[ANTARES] Creating data failed!\n");
    }

    printDebug("\n[ANTARES] Closing connection...\n");
    jsonString = "{}";
    _currentKey = "";
}

void AntaresESP32HTTP::add(String key, String value) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonString);
    object[key] = value;
    String newInsert;
    object.printTo(newInsert);
    jsonString =  newInsert;
}

void AntaresESP32HTTP::add(String key, String key2, String value) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonString);
    if(_currentKey != key) {
        JsonObject& nested = object.createNestedObject(key);
        nested[key2] = value;
    }
    else {
        object[key][key2] = value;
    }
    String newInsert;
    object.printTo(newInsert);
    jsonString =  newInsert;
    _currentKey = key;
}

void AntaresESP32HTTP::add(String key, int value) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonString);
    object[key] = value;
    String newInsert;
    object.printTo(newInsert);
    jsonString =  newInsert;
}

void AntaresESP32HTTP::add(String key, String key2, int value) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonString);
    if(_currentKey != key) {
        JsonObject& nested = object.createNestedObject(key);
        nested[key2] = value;
    }
    else {
        object[key][key2] = value;
    }
    String newInsert;
    object.printTo(newInsert);
    jsonString =  newInsert;
    _currentKey = key;
}

void AntaresESP32HTTP::add(String key, float value) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonString);
    object[key] = value;
    String newInsert;
    object.printTo(newInsert);
    jsonString =  newInsert;
}

void AntaresESP32HTTP::add(String key, String key2, float value) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonString);
    if(_currentKey != key) {
        JsonObject& nested = object.createNestedObject(key);
        nested[key2] = value;
    }
    else {
        object[key][key2] = value;
    }
    String newInsert;
    object.printTo(newInsert);
    jsonString =  newInsert;
    _currentKey = key;
}

void AntaresESP32HTTP::add(String key, double value) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonString);
    object[key] = value;
    String newInsert;
    object.printTo(newInsert);
    jsonString =  newInsert;
}

void AntaresESP32HTTP::add(String key, String key2, double value) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonString);
    if(_currentKey != key) {
        JsonObject& nested = object.createNestedObject(key);
        nested[key2] = value;
    }
    else {
        object[key][key2] = value;
    }
    String newInsert;
    object.printTo(newInsert);
    jsonString =  newInsert;
    _currentKey = key;
}

String AntaresESP32HTTP::getString(String key) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonGetString);
    String value = object[key];
    return value;
}

String AntaresESP32HTTP::getString(String key, String key2) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonGetString);
    String value = object[key][key2];
    return value;
}

int AntaresESP32HTTP::getInt(String key) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonGetString);
    int value = object[key];
    return value;
}

int AntaresESP32HTTP::getInt(String key, String key2) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonGetString);
    int value = object[key][key2];
    return value;
}

float AntaresESP32HTTP::getFloat(String key) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonGetString);
    float value = object[key];
    return value;
}

float AntaresESP32HTTP::getFloat(String key, String key2) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonGetString);
    float value = object[key][key2];
    return value;
}

double AntaresESP32HTTP::getDouble(String key) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonGetString);
    double value = object[key];
    return value;
}

double AntaresESP32HTTP::getDouble(String key, String key2) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonGetString);
    double value = object[key][key2];
    return value;
}

void AntaresESP32HTTP::printData() {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& sendObject = jsonBuffer.parseObject(jsonString);
    JsonObject& getObject = jsonBuffer.parseObject(jsonGetString);
    printDebug("\n\n[ANTARES] Data to send: \n\n");
    sendObject.prettyPrintTo(Serial);
    printDebug("\n\n[ANTARES] Data available to get: \n\n");
    getObject.prettyPrintTo(Serial);
}

void AntaresESP32HTTP::printDebug(String text){
    if (_debug)
        Serial.print(text);
}

void AntaresESP32HTTP::setDebug(bool trueFalse){
    _debug = trueFalse;
}

String AntaresESP32HTTP::ipToString(IPAddress ip){
    String s="";
    for (int i=0; i<4; i++)
        s += i  ? "." + String(ip[i]) : String(ip[i]);
    return s;
}

bool AntaresESP32HTTP::wifiConnection(String SSID, String wifiPassword) {
    char ssidChar[sizeof(SSID)];
    char wifiPasswordChar[sizeof(SSID)];

    SSID.toCharArray(ssidChar, sizeof(SSID));
    wifiPassword.toCharArray(wifiPasswordChar, sizeof(wifiPassword));

    int count=0;
    _wifiSSID = ssidChar;
    _wifiPass = wifiPasswordChar;

    WiFi.begin(_wifiSSID, _wifiPass);
    printDebug("[ANTARES] Trying to connect to " + SSID + "...\n");

    // for (count=0;count<20;count++) {
    //     delay(500);
    //     printDebug(".");
    // }

    int counter = 0;
    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        printDebug(".");
        counter++;
        if(counter >= 10) {
            counter = 0;
            printDebug("[ANTARES] Could not connect to " + SSID + "! Retrying...\n");
        }
    }

    WiFi.setAutoReconnect(true);
    printDebug("\n[ANTARES] WiFi Connected!\n");
    printDebug("[ANTARES] IP Address: " + ipToString(WiFi.localIP()) + "\n");
    return true;
}

bool AntaresESP32HTTP::checkWifiConnection() {
    if(WiFi.status() != WL_CONNECTED) {
        printDebug("[ANTARES] WIFI RECONNECT...");
        return wifiConnection(_wifiSSID, _wifiPass);
    }
}
