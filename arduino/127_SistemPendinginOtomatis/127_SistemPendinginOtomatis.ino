#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(32, 16, 2);

int lm35 = A2;
int motor1 = 4;
int motor2 = 5;
float read = 0.0;
float voltage = 0.0;
float suhu = 0.0;

void setup() {
	Serial.begin(9600);
 	lcd.begin(16,2);
 	lcd.init();
	lcd.setBacklight(HIGH);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
}

void loop() {
  read = analogRead(lm35);
  voltage = (read / 1024) * 5;
  suhu = (voltage - 0.5008) * 100;
  
  lcd.setCursor(0,0);
  lcd.print("Suhu: ");
  lcd.print(suhu);
  lcd.print(" ");
  lcd.print(char(176));
  lcd.print("C  ");
  
  if (suhu > 30) {
  	//digitalWrite(enA, HIGH);
    digitalWrite(motor1, LOW);
  	digitalWrite(motor2, HIGH);
    lcd.setCursor(0,1); 
    lcd.print("Motor ON "); 
  } else {
    //digitalWrite(enA, LOW);
    digitalWrite(motor1, LOW);
  	digitalWrite(motor2, LOW);
    lcd.setCursor(0,1); 
    lcd.print("Motor OFF");
 	}
  
  delay(1000);
}