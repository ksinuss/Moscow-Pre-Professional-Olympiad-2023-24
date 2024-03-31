#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX
// Подключение пинов драйвера к пинам Arduino
// int ENA = 11;
int IN1 = 10;
int IN2 = 9;

void setup() {
  // Настройка пинов на вывод
  // pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  Serial.begin(9600);
  mySerial.begin(9600);

  // Установка скорости вращения мотора (0-255)
  // analogWrite(ENA, 255);
}

void loop() {
  if (mySerial.available() > 0) {
    char command = mySerial.read();

    if (command == '1') {
      // Поворот мотора вперед
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      delay(1000);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      delay(300);
  
      // Вращение назад
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      delay(1000);
    }

  // // Вращение вперед
  // digitalWrite(IN1, HIGH);
  // digitalWrite(IN2, LOW);
  // delay(100); // Вращение в течение 2 секунд
  
  // // Остановка на 1 секунду
  // digitalWrite(IN1, LOW);
  // digitalWrite(IN2, LOW);
  // delay(3000);
  
  // // Вращение назад
  // digitalWrite(IN1, LOW);
  // digitalWrite(IN2, HIGH);
  // delay(100); // Вращение в течение 2 секунд
  
  // // Остановка на 1 секунду
  // digitalWrite(IN1, LOW);
  // digitalWrite(IN2, LOW);
  // delay(3000);

  // Поворот мотора вперед
    // digitalWrite(ENA, HIGH);
    // digitalWrite(IN1, HIGH);
    // digitalWrite(IN2, LOW);
    
  }
}