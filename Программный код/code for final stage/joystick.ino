const int pinX1 = A3;
const int pinY1 = A4;
const int pinB1 = 8;
const int pinX2 = A2;
const int pinY2 = A5;
const int pinB2 = 7;

void setup() {
  Serial.begin(9600);
  pinMode(pinB1, INPUT);
  pinMode(pinB2, INPUT);

}

void loop() {
  int xValue1 = analogRead(pinX1);
  int yValue1 = analogRead(pinY1);
  int bValue1 = digitalRead(pinB1);
  int xValue2 = analogRead(pinX2);
  int yValue2 = analogRead(pinY2);
  int bValue2 = digitalRead(pinB2);

  Serial.print("1X: ");
  Serial.print(xValue1);
  Serial.print(", 1Y: ");
  Serial.print(yValue1);
  Serial.print(", 1Button: ");
  Serial.println(bValue1);
  Serial.print("2X: ");
  Serial.print(xValue2);
  Serial.print(", 2Y: ");
  Serial.print(yValue2);
  Serial.print(", 2Button: ");
  Serial.println(bValue2);

  delay(500); // Задержка для стабилизации работы
}