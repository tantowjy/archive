#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <WiFiClient.h>
#include <WebSocketsServer.h>
#include "esp_camera.h"
#include <iostream>
#include <sstream>
#include "esp_http_server.h"

#define MOTOR_IN1    14
#define MOTOR_IN2    15
#define MOTOR_IN3    13
#define MOTOR_IN4    12
#define MOTOR_EN     2

#define LIGHT_PIN 4

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define STOP 0

#define RIGHT_MOTOR 0
#define LEFT_MOTOR 1

#define FORWARD 1
#define BACKWARD -1

// SSID & Password
const char* ssid = "**************";
const char* password = "*************";

WebServer server(80);  // Object of WebServer(HTTP port, 80 is default)
WebSocketsServer webSocketCarInput = WebSocketsServer(81);

const int PWMFreq = 1000; /* 1 KHz */
const int PWMResolution = 8;
const int PWMSpeedChannel = 2;
const int PWMLightChannel = 3;

int speed = 0;

#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

String htmlHomePage = R"HTMLHOMEPAGE(
<!DOCTYPE html>
<html>
  <head>
  <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no">
    <style>
    .arrows {
      font-size:40px;
      color:green;
    }
    .button {
      background-color:rgba(0, 0, 0, 0.942);
      border-radius:20%;
      padding: 10px 40px;
      box-shadow: 5px 5px #888888;
    }
    .button:active {
      transform: translate(5px,5px);
      box-shadow: none; 
    }

    .noselect {
      -webkit-touch-callout: none; /* iOS Safari */
        -webkit-user-select: none; /* Safari */
         -khtml-user-select: none; /* Konqueror HTML */
           -moz-user-select: none; /* Firefox */
            -ms-user-select: none; /* Internet Explorer/Edge */
                user-select: none; /* Non-prefixed version, currently
                                      supported by Chrome and Opera */
    }

    .slidecontainer {
      width: 100%;
    }

    .slider {
      -webkit-appearance: none;
      width: 100%;
      height: 15px;
      border-radius: 5px;
      background: #d3d3d3;
      outline: none;
      opacity: 0.7;
      -webkit-transition: .2s;
      transition: opacity .2s;
    }

    .slider:hover {
      opacity: 1;
    }
  
    .slider::-webkit-slider-thumb {
      -webkit-appearance: none;
      appearance: none;
      width: 25px;
      height: 25px;
      border-radius: 50%;
      background: green;
      cursor: pointer;
    }

    .slider::-moz-range-thumb {
      width: 25px;
      height: 25px;
      border-radius: 50%;
      background: green;
      cursor: pointer;
    }

    </style>
  
  </head>
  <body class="noselect" align="center" style="background-color:whitesmoke">
     
    <!--h2 style="color: teal;text-align:center;">Wi-Fi Camera &#128663; Control</h2-->
    
    <table id="mainTable" style="width:400px;margin:auto;table-layout:fixed" CELLSPACING=10>
      <tr>
        <td></td>
        <td>
          <button class="button" value="1" onmousedown="toggleCheckbox('1');" ontouchstart="toggleCheckbox('1');" onmouseup="toggleCheckbox('0');" ontouchend="toggleCheckbox('0');">
            <span class="arrows">&#8679;</span>
          </button>
        </td>
        <td></td>
      </tr>
      <tr>
        <td>
          <button class="button" value="3" onmousedown="toggleCheckbox('3');" ontouchstart="toggleCheckbox('3');" onmouseup="toggleCheckbox('0');" ontouchend="toggleCheckbox('0');">
            <span class="arrows">&#8678;</span>
          </button>
        </td>
        <td class="button"></td>    
        <td>
          <button class="button" value="4" onmousedown="toggleCheckbox('4');" ontouchstart="toggleCheckbox('4');" onmouseup="toggleCheckbox('0');" ontouchend="toggleCheckbox('0');">
            <span class="arrows">&#8680;</span>
          </button>
        </td>
      </tr>
      <tr>
        <td></td>
        <td>
          <button class="button" value="2" onmousedown="toggleCheckbox('2');" ontouchstart="toggleCheckbox('2');" onmouseup="toggleCheckbox('0');" ontouchend="toggleCheckbox('0');">
            <span class="arrows">&#8681;</span>
          </button>
        </td>
        <td></td>
      </tr>
      <tr/><tr/>
      <tr>
        <td style="text-align:left"><b>Speed:</b></td>
        <td colspan=2>
         <div class="slidecontainer">
            <input type="range" min="0" max="255" value="100" class="slider" id="Speed" oninput='sendButtonInput("Speed",value)'>
          </div>
        </td>
      </tr>        
      <tr>
        <td style="text-align:left"><b>Light:</b></td>
        <td colspan=2>
          <div class="slidecontainer">
            <input type="range" min="0" max="255" value="0" class="slider" id="Light" oninput='sendButtonInput("Light",value)'>
          </div>
        </td>   
      </tr>
    </table>
  
    <script>
      var webSocketCarInputUrl = "ws:\/\/" + window.location.hostname + ":81";     
      var websocketCarInput;
      
      function initCarInputWebSocket() 
      {
        websocketCarInput = new WebSocket(webSocketCarInputUrl);
        websocketCarInput.onopen = function(event)
        {
          var speedButton = document.getElementById("Speed");
          sendButtonInput("Speed", speedButton.value);
          var lightButton = document.getElementById("Light");
          sendButtonInput("Light", lightButton.value);

          document.querySelectorAll('.button').forEach(button => {
            button.addEventListener('mousedown', () => {
              sendButtonInput('MoveCar', button.value);
            });
            button.addEventListener('mouseup', () => {
              sendButtonInput('MoveCar', '0');
            });
            button.addEventListener('touchstart', () => {
              sendButtonInput('MoveCar', button.value);
            });
            button.addEventListener('touchend', () => {
              sendButtonInput('MoveCar', '0');
            });
          });
          
        };
        websocketCarInput.onclose   = function(event){setTimeout(initCarInputWebSocket, 2000);};
        websocketCarInput.onmessage = function(event){};        
      }
      
      function initWebSocket() 
      {
        initCarInputWebSocket();
      }

      function sendButtonInput(key, value) 
      {
        var data = key + "," + value;
        websocketCarInput.send(data);
      }
    
      window.onload = initWebSocket;
      document.getElementById("mainTable").addEventListener("touchend", function(event){
        event.preventDefault()
      });      
    </script>
  </body>    
</html>
)HTMLHOMEPAGE";

void moveCar(int inputValue, int inputSpeed) {
  analogWrite(MOTOR_EN, inputSpeed);
  if (inputValue == UP) {
    Serial.println("Forward");
    digitalWrite(MOTOR_IN1, 0);
    digitalWrite(MOTOR_IN2, 1);
    digitalWrite(MOTOR_IN3, 1);
    digitalWrite(MOTOR_IN4, 0);
  } else if (inputValue == DOWN) {
    Serial.println("Backward");
    digitalWrite(MOTOR_IN1, 1);
    digitalWrite(MOTOR_IN2, 0);
    digitalWrite(MOTOR_IN3, 0);
    digitalWrite(MOTOR_IN4, 1); 
  } else if (inputValue == LEFT) {
    Serial.println("Left");
    digitalWrite(MOTOR_IN1, 0);
    digitalWrite(MOTOR_IN2, 1);
    digitalWrite(MOTOR_IN3, 0);
    digitalWrite(MOTOR_IN4, 1);
  } else if (inputValue == RIGHT) {
    Serial.println("Right");
    digitalWrite(MOTOR_IN1, 1);
    digitalWrite(MOTOR_IN2, 0);
    digitalWrite(MOTOR_IN3, 1);
    digitalWrite(MOTOR_IN4, 0);  
  } else {
    digitalWrite(MOTOR_IN1, 0);
    digitalWrite(MOTOR_IN2, 0);
    digitalWrite(MOTOR_IN3, 0);
    digitalWrite(MOTOR_IN4, 0);      
  }
}

void onCarInputWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  if (type == WStype_TEXT) {
    String text = String((char *)payload);
    int index = text.indexOf(',');
    String key = text.substring(0, index);
    int value = text.substring(index + 1).toInt();

    if (key == "MoveCar") {
      // moveCar(value);
      moveCar(value, speed);
      Serial.print("MoveCar:");
      Serial.println(value);
    } else if (key == "Speed") {
      // ledcWrite(PWMSpeedChannel, value);
      speed = value;
      Serial.print("Speed:");
      Serial.println(value);
    } else if (key == "Light") {
      ledcWrite(PWMLightChannel, value);
      Serial.print("Light:");
      Serial.println(value);
    }
  }
}

void handle_root() {
  server.send(200, "text/html", htmlHomePage);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Try Connecting to ");
  Serial.println(ssid);

  // Connect to your wi-fi modem
  WiFi.begin(ssid, password);

  // Check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());  //Show ESP32 IP on serial

  // ledcSetup(PWMSpeedChannel, PWMFreq, PWMResolution);
  // ledcAttachPin(MOTOR_EN, PWMSpeedChannel);
  
  ledcSetup(PWMLightChannel, PWMFreq, PWMResolution);
  ledcAttachPin(LIGHT_PIN, PWMLightChannel);

  pinMode(MOTOR_EN, OUTPUT);
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(MOTOR_IN3, OUTPUT);
  pinMode(MOTOR_IN4, OUTPUT);
  
  server.on("/", handle_root);
  server.begin();
  Serial.println("HTTP server started");

  webSocketCarInput.begin();
  webSocketCarInput.onEvent(onCarInputWebSocketEvent);
}

void loop() {
  server.handleClient();
  webSocketCarInput.loop();
}
