#define PI 3.1415926535897932384626433832795
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int encoderPinA = 2;
const int encoderPinB = 3;
volatile int encoderPos = 0;
volatile int lastEncoderPos = 0;
volatile boolean aState, aLastState;
unsigned long lastTime = 0;
const float radii = 0.127;
float velocity = 0.0;
float distance = 0.0;
float displacement = 0.0;

void setup() {
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderPinA), updateEncoder, CHANGE);
  aLastState = digitalRead(encoderPinA);

  Serial.begin(9600);
  lcd.init();
  lcd.setBacklight(HIGH);
}

void loop() {
  unsigned long currentTime = millis();
  unsigned long timeDiff = currentTime - lastTime;

  displacement = (encoderPos - lastEncoderPos) * ( (2 * PI * radii) / 2000);
  distance = distance + displacement;
  velocity = displacement * (1000.0 / timeDiff);
  
  lastEncoderPos = encoderPos;
  lastTime = currentTime;

  lcd.setCursor(0, 0);
  lcd.print("x: ");
  lcd.print(distance);
  lcd.print(" m        ");
  lcd.setCursor(0, 1);
  lcd.print("v: ");
  lcd.print(velocity);
  lcd.print(" m/s      ");

  delay(300);
}

void updateEncoder() {
  aState = digitalRead(encoderPinA);
  
  if (aState != aLastState) {
    if (digitalRead(encoderPinB) != aState) {
      encoderPos++;
    } else {
      encoderPos--;
    }
  }

  aLastState = aState;
}