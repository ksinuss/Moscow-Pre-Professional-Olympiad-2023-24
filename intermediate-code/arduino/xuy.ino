// инициализация для сервопривода
#include <Servo.h>
Servo servo; // create servo object to control a servo
int pos; // variable to store the servo position

// инициализация переменных для дальнейшего получения информации о грузах (распознавание)
String data = "";

void setup() 
{
  Serial.begin(9600);
  servo.attach(12);
  servo.write(110);
  pinMode(13, OUTPUT);
}

void loop() 
{
//  data = receive();
if (Serial.available() > 0) {
    // Читаем полученные данные и сохраняем их в переменной
    String data = Serial.readString();
    if (data == "1")
    {
      delay(100);
      servo.write(90);
      delay(100);
      digitalWrite(13, HIGH);   // зажигаем светодиод
      delay(10000);              // ждем секунду
      digitalWrite(13, LOW);    // выключаем светодиод
      delay(1000);
      data = "";
    }
}
}

String receive() // получение сигнала о заказе или распознавшихся грузах
{
  if (Serial.available())
  {
    String data = Serial.readString();
    return data;
  }
  else
  { return "";}
}
