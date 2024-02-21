void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) 
  {
  // Читаем полученные данные и сохраняем их в переменной
  String data = Serial.readString();
  // char data = Serial.read();
  // int data = Serial.read();
  // int data = Serial.parseInt();
  // int idata = data.toInt();
  // Отправляем ответ обратно в Serial порт
  // Serial.println("Получено: " + data);
  if (data == "1")
    {
      Serial.println("xyu");
      digitalWrite(13, HIGH);   // зажигаем светодиод
      delay(5000);              // ждем секунду
      digitalWrite(13, LOW);    // выключаем светодиод
      delay(1000); 
    }
  }
}
