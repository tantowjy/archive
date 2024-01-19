#define sensorPower 16
#define sensorPin 4

int val = 0;

void setup() {
  pinMode(sensorPower, OUTPUT);
  digitalWrite(sensorPower, LOW);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(sensorPower, HIGH);
  delay(10);
  val = analogRead(sensorPin);
  digitalWrite(sensorPower, LOW);
  Serial.print("Water level: ");
  Serial.println(val);
  Serial.print("Water level: ");
  Serial.print(val/21);
  Serial.println(" %");
  delay(2000);
}